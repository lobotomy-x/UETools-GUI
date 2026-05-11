#include "DirectWindow.h"






LRESULT WINAPI DirectWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) != 0)
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
        {
            if ((GetDevice() != nullptr) && (wParam != SIZE_MINIMIZED))
            {
                InvalidateRenderTargetView();
                GetSwapChain()->ResizeBuffers(0, static_cast<UINT>(LOWORD(lParam)), static_cast<UINT>(HIWORD(lParam)), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTargetView();
            }
            return 0;
        }

        case WM_SYSCOMMAND:
        {
            if ((wParam & 0xfff0) == SC_KEYMENU)
            {
                return 0;
            }
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        default:
        {
            break;
        }
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}




bool DirectWindow::CreateRenderTargetView()
{
    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT backBufferResult = GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

    if (FAILED(backBufferResult))
    {
        return false;
    }

    HRESULT createRenderTargetViewResult = GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    if (FAILED(createRenderTargetViewResult))
    {
        return false;
    }

    return true;
}

bool DirectWindow::CreateDevice(const HWND& hWnd, const bool& HDR)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = 0;
    swapChainDesc.BufferDesc.Height = 0;
    swapChainDesc.BufferDesc.Format = HDR ? DXGI_FORMAT_R10G10B10A2_UNORM : DXGI_FORMAT_R8G8B8A8_UNORM;

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;

    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = TRUE;

    const UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    const D3D_FEATURE_LEVEL createDeviceFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL createDeviceOutFeatureLevel;

    /* Create Device + Swap Chain (hardware). */
    HRESULT createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);

    if (createDeviceAndSwapChainResult == DXGI_ERROR_UNSUPPORTED) // Fallback to WARP if no hardware support.
    {
        createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);
    }

    if (FAILED(createDeviceAndSwapChainResult))
    {
        return false;
    }

    CreateRenderTargetView();
    return true;
}

void DirectWindow::CleanupDevice()
{
    InvalidateRenderTargetView();
    InvalidateDeviceContext();
    InvalidateSwapChain();
    InvalidateDevice();
}

void DirectWindow::SetTargetWindow(const HWND& hWindow)
{
    hTargetWindow = hWindow;
    SetForegroundWindow(hTargetWindow);
    GetWindowThreadProcessId(hTargetWindow, &dTargetPID);
    bTargetSet = true;
}

BOOL CALLBACK DirectWindow::EnumWind(HWND hWindow, LPARAM lParam)
{
    DWORD procID;
    GetWindowThreadProcessId(hWindow, &procID);

    if (GetCurrentProcessId() != procID)
    {
        return TRUE;
    }

    if (IsWindowValid(hWindow) == false) // Skip non-eligible windows.
    {
        return TRUE;
    }

    SetTargetWindow(hWindow);
    return FALSE; // Stop enumeration after finding the first match.
}

void DirectWindow::GetWindow()
{
    EnumWindows(EnumWind, 0);
}

void DirectWindow::MoveWindow(const HWND& hWindow, const bool& forceInvalidSize)
{
    if (hTargetWindow == nullptr)
    {
        return;
    }

    RECT rect;
    GetWindowRect(hTargetWindow, &rect);

    int lWindowWidth = forceInvalidSize ? 0 : rect.right - rect.left;
    int lWindowHeight = forceInvalidSize ? 0 : rect.bottom - rect.top;

    SetWindowPos(hWindow, nullptr, rect.left, rect.top, lWindowWidth, lWindowHeight, SWP_SHOWWINDOW);
}

bool DirectWindow::IsWindowFocus(const HWND& hWindow)
{
    char lpCurrentWindowUsedClass[125];
    char lpCurrentWindowClass[125];
    char lpOverlayWindowClass[125];

    const HWND hCurrentWindowUsed = GetForegroundWindow();

    if (GetClassNameA(hCurrentWindowUsed, lpCurrentWindowUsedClass, sizeof(lpCurrentWindowUsedClass)) == 0)
    {
        return false;
    }

    if (GetClassNameA(hTargetWindow, lpCurrentWindowClass, sizeof(lpCurrentWindowClass)) == 0)
    {
        return false;
    }

    if (GetClassNameA(hWindow, lpOverlayWindowClass, sizeof(lpOverlayWindowClass)) == 0)
    {
        return false;
    }

    if ((strcmp(lpCurrentWindowUsedClass, lpCurrentWindowClass) != 0) && (strcmp(lpCurrentWindowUsedClass, lpOverlayWindowClass) != 0))
    {
        SetWindowLongW(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
        return false;
    }

    return true;
}

bool DirectWindow::IsWindowValid(const HWND& hWindow)
{
    if ((IsWindowVisible(hWindow) == 0) || (IsIconic(hWindow) != 0) || (IsWindowCloaked(hWindow) == true))
    {
        return false;
    }

    RECT rect;
    GetClientRect(hWindow, &rect);

    DWORD styles = static_cast<DWORD>(GetWindowLongPtrW(hWindow, GWL_STYLE));
    DWORD exStyles = static_cast<DWORD>(GetWindowLongPtrW(hWindow, GWL_EXSTYLE));

    if (exStyles & WS_EX_TOOLWINDOW)
    {
        return false;
    }

    if (styles & WS_CHILD)
    {
        return false;
    }

    if ((rect.bottom == 0) || (rect.right == 0))
    {
        return false;
    }

    return true;
}

bool DirectWindow::IsWindowCloaked(const HWND& hWindow)
{
    DWORD cloaked = 0;
    HRESULT hr = DwmGetWindowAttribute(hWindow, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));

    if (SUCCEEDED(hr) && (cloaked != 0))
    {
        return true;
    }

    return false;
}

bool DirectWindow::IsWindowAlive()
{
    if (hTargetWindow == nullptr)
    {
        return false;
    }

    if (IsWindow(hTargetWindow) == 0)
    {
        return false;
    }

    DWORD dCurrentPID;
    GetWindowThreadProcessId(hTargetWindow, &dCurrentPID);

    if (dCurrentPID != dTargetPID)
    {
        return false;
    }

    return true;
}




void DirectWindow::Create()
{
    ImGui_ImplWin32_EnableDpiAwareness();

    if (hTargetWindow == nullptr)
    {
        GetWindow();
    }

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(RGB(0, 0, 0)));
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"UETools-GUI";
    wc.style = CS_VREDRAW | CS_HREDRAW;

    RegisterClassExW(&wc);

    const HWND hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
        wc.lpszClassName, L"UETools-GUI", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, wc.hInstance, nullptr
    );

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    const MARGINS margin = { -1, 0, 0, 0 };
    DwmExtendFrameIntoClientArea(hwnd, &margin);

    if (CreateDevice(hwnd) == false)
    {
        CleanupDevice();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    /* IMGUI SETUP */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    const HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info = {};
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfoW(monitor, &info);

    const int monitorHeight = info.rcMonitor.bottom - info.rcMonitor.top;

    if (monitorHeight > 1080)
    {
        const float fScale = 2.0f;
        ImFontConfig cfg;
        cfg.SizePixels = 13.0f * fScale;
        io.Fonts->AddFontDefault(&cfg);
    }

    io.IniFilename = nullptr;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext());

    bInit = true;

    /* RENDER LOOP */
    bool bDone = false;

    while (bDone == false)
    {
        static const float colorTransparent[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        MSG msg;

        while (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0)
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT)
            {
                bDone = true;
            }
        }

        if ((IsWindowAlive() == false) && (bTargetSet == true))
        {
            bDone = true;
        }

        if (bDone == true)
        {
            break;
        }

        bool isMenuActive = GUI::GetIsMenuActive();
        static bool lastIsMenuActive = !isMenuActive;

        bool isInFocus = IsWindowFocus(hwnd) && bTargetSet;
        GUI::SetIsTitleInFocus(isInFocus);

        if (hTargetWindow != nullptr)
        {
#ifdef INACTIVE_ZERO_SIZE
            MoveWindow(hwnd, (isMenuActive == false) || (isInFocus == false));
#else
            MoveWindow(hwnd);
#endif
        }
        else
        {
            continue;
        }

        if (isInFocus == false)
        {
            lastIsMenuActive = !isMenuActive;

            GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
            GetDeviceContext()->ClearRenderTargetView(renderTargetView, colorTransparent);
            GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0);

            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        GUI::Draw();

        ImGui::EndFrame();

        if (isMenuActive != lastIsMenuActive)
        {
            if (isMenuActive == true)
            {
                LONG ex = GetWindowLongW(hwnd, GWL_EXSTYLE);
                ex &= ~WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE;
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLongW(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                DWORD gameTid = GetWindowThreadProcessId(hTargetWindow, nullptr);
                DWORD myTid = GetCurrentThreadId();

                AttachThreadInput(myTid, gameTid, TRUE);
                SetForegroundWindow(hwnd);
                SetActiveWindow(hwnd);
                SetFocus(hwnd);
                AttachThreadInput(myTid, gameTid, FALSE);

                if (GetCapture() != hwnd)
                {
                    SetCapture(hwnd);
                }

                io.MouseDrawCursor = true;
            }
            else
            {
                LONG ex = GetWindowLongW(hwnd, GWL_EXSTYLE);
                ex |= WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE;
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLongW(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                if (GetCapture() == hwnd)
                {
                    ReleaseCapture();
                }

                io.MouseDrawCursor = false;

                if (IsWindow(hTargetWindow) != 0)
                {
                    SetForegroundWindow(hTargetWindow);
                }
            }

            lastIsMenuActive = isMenuActive;
        }

        ImGui::Render();
        GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
        GetDeviceContext()->ClearRenderTargetView(renderTargetView, colorTransparent);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0);
    }

    /* SHUTDOWN */
    bInit = false;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDevice();
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FreeLibrary), GetApplicationModule(), 0, nullptr);
}