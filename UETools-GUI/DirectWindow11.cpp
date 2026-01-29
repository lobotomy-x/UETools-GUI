#include "DirectWindow11.h"






LRESULT WINAPI DirectWindow11::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_SIZE:
            if (GetDevice() && wParam != SIZE_MINIMIZED)
            {
                InvalidateRenderTargetView();
                GetSwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTargetView();
            }
            return 0;

        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;

        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;

        default:
            break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}




bool DirectWindow11::CreateDevice(HWND hWnd, const bool& HDR)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = 0;
    swapChainDesc.BufferDesc.Height = 0;
    swapChainDesc.BufferDesc.Format = HDR ? DXGI_FORMAT_R10G10B10A2_UNORM : DXGI_FORMAT_R8G8B8A8_UNORM; // Standard 32-bit RGBA.

    swapChainDesc.SampleDesc.Count = 1; // No MSAA.
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Back buffers used as render targets.
    swapChainDesc.BufferCount = 2; // Double-buffering.

    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // 60 Hz (vsync target).
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Allow fullscreen switch (legacy style).
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Legacy blt model swap effect.

    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = TRUE; // Start windowed.

    const UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    const D3D_FEATURE_LEVEL createDeviceFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL createDeviceOutFeatureLevel;

    /* Create Device + Swap Chain (hardware). */
    HRESULT createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);

    if (createDeviceAndSwapChainResult == DXGI_ERROR_UNSUPPORTED) // Fallback to WARP (software rasterizer) if no hardware support.
        createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);

    if (FAILED(createDeviceAndSwapChainResult))
        return false;

    CreateRenderTargetView(); // Create RTV for the Swap Chain back buffer.
    return true;
}

void DirectWindow11::CleanupDevice()
{
    if (GetRenderTargetView())
        InvalidateRenderTargetView();

    if (GetDeviceContext())
        InvalidateDeviceContext();

    if (GetSwapChain())
        InvalidateSwapChain();

    if (GetDevice())
        InvalidateDevice();
}




bool DirectWindow11::CreateRenderTargetView()
{
    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT backBufferResult = GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(backBufferResult))
        return false;

    HRESULT createRenderTargetViewResult = GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();
    if (FAILED(createRenderTargetViewResult))
        return false;

    return true;
}




void DirectWindow11::GetWindow()
{
    EnumWindows(EnumWind, NULL);
}

BOOL CALLBACK DirectWindow11::EnumWind(HWND hWindow, LPARAM lParam)
{
    DWORD procID;
    GetWindowThreadProcessId(hWindow, &procID);
    if (GetCurrentProcessId() != procID)
        return TRUE;

    if (!IsWindowValid(hWindow))
        return TRUE; // Skip non-eligible windows.

    SetTargetWindow(hWindow); // Store and mark as target, bring to foreground.
    return FALSE;  // Stop enumeration after finding the first match.
}

void DirectWindow11::MoveWindow(const HWND& hWindow, const bool& forceInvalidSize)
{
    RECT rect;
    if (hTargetWindow == nullptr)
        return;

    GetWindowRect(hTargetWindow, &rect);

    int lWindowWidth = forceInvalidSize ? 0 : rect.right - rect.left;
    int lWindowHeight = forceInvalidSize ? 0 : rect.bottom - rect.top;

    SetWindowPos(hWindow, nullptr, rect.left, rect.top, lWindowWidth, lWindowHeight, SWP_SHOWWINDOW);
}

BOOL DirectWindow11::IsWindowFocus(const HWND& hWindow)
{
    char lpCurrentWindowUsedClass[125];
    char lpCurrentWindowClass[125];
    char lpOverlayWindowClass[125];

    const HWND hCurrentWindowUsed = GetForegroundWindow();
    if (GetClassNameA(hCurrentWindowUsed, lpCurrentWindowUsedClass, sizeof(lpCurrentWindowUsedClass)) == 0)
        return FALSE;

    if (GetClassNameA(hTargetWindow, lpCurrentWindowClass, sizeof(lpCurrentWindowClass)) == 0)
        return FALSE;

    if (GetClassNameA(hWindow, lpOverlayWindowClass, sizeof(lpOverlayWindowClass)) == 0)
        return FALSE;

    // If the foreground window is neither the target nor the overlay, make overlay click-through.
    if (strcmp(lpCurrentWindowUsedClass, lpCurrentWindowClass) != 0 && strcmp(lpCurrentWindowUsedClass, lpOverlayWindowClass) != 0)
    {
        SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
        return FALSE;
    }

    return TRUE;
}

BOOL DirectWindow11::IsWindowValid(const HWND& hWindow)
{
    DWORD styles, ex_styles;
    RECT rect;

    if (!IsWindowVisible(hWindow) ||
        (IsIconic(hWindow) || IsWindowCloaked(hWindow)))
        return FALSE;

    GetClientRect(hWindow, &rect);
    styles = (DWORD)GetWindowLongPtr(hWindow, GWL_STYLE);
    ex_styles = (DWORD)GetWindowLongPtr(hWindow, GWL_EXSTYLE);

    if (ex_styles & WS_EX_TOOLWINDOW)
        return FALSE;
    if (styles & WS_CHILD)
        return FALSE;
    if (rect.bottom == 0 || rect.right == 0)
        return FALSE;

    return TRUE;
}

BOOL DirectWindow11::IsWindowCloaked(const HWND& hWindow)
{
    DWORD cloaked;
    const HRESULT hr = DwmGetWindowAttribute(hWindow, DWMWA_CLOAKED, &cloaked,
        sizeof(cloaked));
    return SUCCEEDED(hr) && cloaked;
}

void DirectWindow11::SetTargetWindow(const HWND& hWindow)
{
    hTargetWindow = hWindow;
    SetForegroundWindow(hTargetWindow);
    GetWindowThreadProcessId(hTargetWindow, &dTargetPID);
    bTargetSet = TRUE;
}

BOOL DirectWindow11::IsWindowAlive()
{
    DWORD dCurrentPID;

    if (hTargetWindow == nullptr)
        return FALSE;

    if (!IsWindow(hTargetWindow))
        return FALSE;

    GetWindowThreadProcessId(hTargetWindow, &dCurrentPID);

    if (dCurrentPID != dTargetPID)
        return FALSE;

    return TRUE;
}




void DirectWindow11::Create()
{
    /* 
        Swap default font with new "ProggyVector-minimal.ttf". 
        imgui_draw.cpp -> ImFontAtlas::AddFontDefault(...)
        {
            return AddFontDefaultVector(font_cfg);
        }

        Runtime alternative being:
        ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->AddFontDefaultVector();
    */

    /* Enable per - monitor DPI awareness so ImGui scales appropriately on HiDPI displays. */
    ImGui_ImplWin32_EnableDpiAwareness();

    /* Get the main window of the process. */
    if (hTargetWindow == nullptr)
        GetWindow();

    WNDCLASSEX wc;

    /* Fill window class. Note: not zero-initialized; all fields are explicitly assigned. */
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)); // Solid background; will be fully transparent via layering.
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpfnWndProc = WndProc; // Our static WndProc.
    wc.lpszClassName = L"UETools-GUI"; // Window class name.
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW; // Redraw on size changes.

    ::RegisterClassEx(&wc);

    /* Create a layered, click-through (initially), always-on-top popup that spans the screen. */
    const HWND hwnd = ::CreateWindowExW
    (
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, 
        wc.lpszClassName, L"UETools-GUI", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
        nullptr, nullptr, wc.hInstance, nullptr
    );

    /* Make the layered window fully opaque alpha (we'll clear to transparent in the render path). */
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    /* Extend the glass/transparent frame into the client area for per-pixel transparency. */
    const MARGINS margin = { -1, 0, 0, 0 };
    DwmExtendFrameIntoClientArea(hwnd, &margin);

    /* Initialize D3D11 device/ctx/swapchain. */
    if (!CreateDevice(hwnd))
    {
        CleanupDevice();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);




    // =================
    // |  IMGUI SETUP  |
    // =================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard navigation.

    ImGui::StyleColorsDark();

    /* Scale the font size depending of the screen size. */
    const HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info = {};
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(monitor, &info);
    const int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;

    if (monitor_height > 1080)
    {
        const float fScale = 2.0f;
        ImFontConfig cfg;
        cfg.SizePixels = 13 * fScale; // Increase default font size for >1080p monitors.
        ImGui::GetIO().Fonts->AddFontDefault(&cfg);
    }

    /* Avoid writing imgui.ini to disk (no persistence). */
    ImGui::GetIO().IniFilename = nullptr; 

    /* Bind platform/renderer backends. */
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext());

    /* Clear color (RGBA). Alpha 0 => fully transparent when clearing the RTV. */
    const ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    bInit = true;




    // =================
    // |  RENDER LOOP  |
    // =================
    bool bDone = false;
    while (!bDone)
    {
        static const float color_transparent[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

        MSG msg;
        /* Process all pending messages; exit if WM_QUIT arrives. */
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                bDone = true;
        }

        /* Check if the targeted window is still up. */
        if (!IsWindowAlive() && bTargetSet)
            bDone = true;

        if (bDone)
            break;

        bool isMenuActive = GUI::GetIsMenuActive();
        static bool lastIsMenuActive = !isMenuActive; // Small trick to encourage initial SetWindowLong(). W/o it game wouldn't receive any inputs.

        bool isInFocus = IsWindowFocus(hwnd) && bTargetSet;
        if (isInFocus)
        {
            /* External: Keybindings processing lives here. */
            Inputs::Keybindings::Process();
        }

        /* Move the window on top of the targeted window and handle resize. */
        if (hTargetWindow != nullptr)
#ifdef INACTIVE_ZERO_SIZE
            /*
            * Windows 11 24H2
            * Set ImGui overlay to size of zero on both axis (X - Width & Y - Height) when menu isn't active.
            * We'll rely on such a stupid compromise until solution for updated Desktop Window Manager (DWM) is discovered.
            * 
            * Developer of Lossless Scaling (https://store.steampowered.com/app/993090/Lossless_Scaling/) did run
            * into similar issue and was able to find a workaround, although it took a few weeks if not months.
            */
            MoveWindow(hwnd, !isMenuActive || !isInFocus);
#else
            MoveWindow(hwnd);
#endif
        else
            continue;

        /* Clear overlay when the targeted window is not in focus. */
        if (isInFocus == false)
        {
            lastIsMenuActive = !isMenuActive; // Small trick to make sure ImGui wouldn't loose focus after ALT + TAB'ing. W/o it menu woudn't receive any inputs.

            /* Clear to fully transparent so overlay is invisible when target is not focused. */
            GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
            GetDeviceContext()->ClearRenderTargetView(renderTargetView, color_transparent);
            
            GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0); // VSync (interval 1).

            continue;
        }

        /* Start a new ImGui frame and draw GUI content. */
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            GUI::Draw(); // External: GUI rendering lives here.
        }
        ImGui::EndFrame();

        
        if (isMenuActive != lastIsMenuActive)
        {
            if (isMenuActive)
            {
                /* Remove TRANSPARENT and NOACTIVATE. */
                LONG ex = GetWindowLong(hwnd, GWL_EXSTYLE);
                ex &= ~WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE;
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLong(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos
                (
                    hwnd, nullptr, 0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
                );

                /* Activate the overlay so the game stops receiving input. */
                DWORD gameTid = GetWindowThreadProcessId(hTargetWindow, nullptr);
                DWORD myTid = GetCurrentThreadId();
                AttachThreadInput(myTid, gameTid, TRUE);
                SetForegroundWindow(hwnd);
                SetActiveWindow(hwnd);
                SetFocus(hwnd);
                AttachThreadInput(myTid, gameTid, FALSE);

                /* Capture the mouse (all WM_MOUSE messages go to us). */
                if (GetCapture() != hwnd)
                    SetCapture(hwnd);

                /* If the game hides the cursor, draw the ImGui cursor. */
                ImGui::GetIO().MouseDrawCursor = true;
            }
            else
            {
                /* Restore click-through behavior for the overlay. */
                LONG ex = GetWindowLong(hwnd, GWL_EXSTYLE);
                ex |= WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE; // keep without NOACTIVATE so clicking can activate
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLong(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos
                (
                    hwnd, nullptr, 0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
                );

                if (GetCapture() == hwnd)
                    ReleaseCapture();

                ImGui::GetIO().MouseDrawCursor = false;

                /* Return focus to the game. */
                if (IsWindow(hTargetWindow))
                    SetForegroundWindow(hTargetWindow);
            }

            lastIsMenuActive = isMenuActive;
        }
        



        // =================
        // |  RENDER PASS  |
        // =================
        ImGui::Render();
        GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
        GetDeviceContext()->ClearRenderTargetView(renderTargetView, color_transparent);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0); // VSync (interval 1).
    }




    // ==============
    // |  SHUTDOWN  |
    // ==============
    bInit = false;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDevice();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)FreeLibrary, GetApplicationModule(), NULL, nullptr);
}