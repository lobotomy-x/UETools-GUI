@echo off
setlocal enabledelayedexpansion

REM ============================================================================
REM build.bat  --  UETools-GUI for Dumper7 SDKs
REM
REM USAGE
REM   Drag a Dumper7 CppSDK folder onto this .bat, or run from a terminal:
REM       build.bat <path-to-CppSDK> [output-name]
REM
REM   The CppSDK folder is what Dumper7 produces -- it contains SDK.hpp at its
REM   top level and an SDK\ subfolder with all per-package .hpp/.cpp files.
REM
REM   On success the DLL lands at:
REM       <thisdir>\bin\UETools-<GameName>.dll
REM
REM   <GameName> comes from the CppSDK's parent folder by default (e.g. the
REM   folder named "GhostCppSDK" yields "UETools-GhostCppSDK.dll"). Pass a
REM   second argument to override.
REM
REM AUTO-DETECTION
REM   The script inspects the SDK and auto-enables:
REM     UE5               -- TObjectPtr / FTopLevelAssetPath found in headers
REM     ACTOR_TRACE       -- LineTraceSingle present in Engine_functions.cpp
REM     ACTOR_KIND        -- UPointLightComponent present in Engine_classes.hpp
REM     LEVEL_SEQUENCE    -- LevelSequence_classes.hpp exists in the SDK
REM   These are always on:
REM     SOFT_PATH, FREE_CAMERA, ACTORS_TRACKING, COLLISION_VISUALIZER,
REM     WAIT_FOR_TITLE_INIT
REM
REM SDK COMPILATION
REM   Basic.cpp and ALL *_functions.cpp files in the SDK are compiled.
REM   This avoids "unresolved external symbol" errors that occur when SDK
REM   classes call into a package not included in a hand-picked list.
REM
REM REQUIREMENTS
REM   Visual Studio 2022 (any edition) with the Desktop C++ workload,
REM   or VS Build Tools 2022.
REM ============================================================================

set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"

REM ---------------------------------------------------------------------------
REM Argument validation
REM ---------------------------------------------------------------------------
if "%~1"=="" goto :usage

set "SDK=%~1"
if "%SDK:~-1%"=="\" set "SDK=%SDK:~0,-1%"

if not exist "%SDK%\SDK.hpp" (
    echo [ERROR] %SDK% does not look like a Dumper7 CppSDK folder.
    echo         Expected SDK.hpp at the top level. Drop the folder named
    echo         "CppSDK" that Dumper7 produced -- not the per-game parent.
    goto :fail
)
if not exist "%SDK%\SDK\Basic.cpp" (
    echo [ERROR] Missing %SDK%\SDK\Basic.cpp -- SDK looks incomplete.
    goto :fail
)
if not exist "%SDK%\SDK\CoreUObject_functions.cpp" (
    echo [ERROR] Missing %SDK%\SDK\CoreUObject_functions.cpp -- SDK looks incomplete.
    goto :fail
)
if not exist "%SDK%\SDK\Engine_functions.cpp" (
    echo [ERROR] Missing %SDK%\SDK\Engine_functions.cpp -- SDK looks incomplete.
    goto :fail
)

REM ---------------------------------------------------------------------------
REM Output name  (sanitise spaces and Dumper7 '+' characters)
REM ---------------------------------------------------------------------------
set "OUT_NAME=%~2"
if "%OUT_NAME%"=="" (
    for %%G in ("%SDK%\..") do set "OUT_NAME=%%~nxG"
)
if "%OUT_NAME%"=="" set "OUT_NAME=UETools"
set "OUT_NAME=%OUT_NAME: =%"
set "OUT_NAME=%OUT_NAME:+=-%"
set "DLL_NAME=UETools-%OUT_NAME%"

REM ---------------------------------------------------------------------------
REM Locate Visual Studio via vswhere
REM ---------------------------------------------------------------------------
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo [ERROR] vswhere.exe not found.
    echo         Install Visual Studio 2022 ^(any edition^) with the Desktop C++ workload,
    echo         or VS Build Tools 2022.
    goto :fail
)
set "VSWHERE_TMP=%TEMP%\uetools_vsroot.txt"
"%VSWHERE%" -latest -requires Microsoft.VisualStudio.Workload.NativeDesktop -property installationPath >"%VSWHERE_TMP%" 2>nul
set "VS_ROOT="
if exist "%VSWHERE_TMP%" (
    set /p VS_ROOT=<"%VSWHERE_TMP%"
    del /q "%VSWHERE_TMP%" 2>nul
)
if not defined VS_ROOT (
    echo [ERROR] Visual Studio with Desktop C++ workload not found via vswhere.
    echo         Make sure "Desktop development with C++" is installed.
    goto :fail
)
set "VCVARS=%VS_ROOT%\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
    echo [ERROR] vcvars64.bat not found: %VCVARS%
    goto :fail
)

REM ---------------------------------------------------------------------------
REM Build directories
REM ---------------------------------------------------------------------------
if not exist "%ROOT%\bin"   mkdir "%ROOT%\bin"
if not exist "%ROOT%\build" mkdir "%ROOT%\build"
set "OBJ_DIR=%ROOT%\build\%OUT_NAME%"
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
set "STUB_DIR=%ROOT%\build\_stubs"
if not exist "%STUB_DIR%\SDK" mkdir "%STUB_DIR%\SDK"

REM ---------------------------------------------------------------------------
REM Feature detection
REM ---------------------------------------------------------------------------

REM UE5: TObjectPtr<> is exclusive to UE5; FTopLevelAssetPath is another marker.
set "IS_UE5=0"
if exist "%SDK%\SDK\Engine_classes.hpp" (
    findstr /r /m /c:"TObjectPtr" "%SDK%\SDK\Engine_classes.hpp" >nul 2>&1 && set "IS_UE5=1"
)
if !IS_UE5!==0 (
    if exist "%SDK%\SDK\CoreUObject_classes.hpp" (
        findstr /r /m /c:"FTopLevelAssetPath" "%SDK%\SDK\CoreUObject_classes.hpp" >nul 2>&1 && set "IS_UE5=1"
    )
)

REM ACTOR_TRACE: LineTraceSingle exists across engine versions but its parameter
REM layout sometimes differs; we opt-in only when the symbol is confirmed present.
set "HAS_ACTOR_TRACE=0"
findstr /c:"LineTraceSingle" "%SDK%\SDK\Engine_functions.cpp" >nul 2>&1 && set "HAS_ACTOR_TRACE=1"

REM ACTOR_KIND: point/spot light subsystem -- present in most full engine builds.
set "HAS_ACTOR_KIND=0"
if exist "%SDK%\SDK\Engine_classes.hpp" (
    findstr /c:"UPointLightComponent" "%SDK%\SDK\Engine_classes.hpp" >nul 2>&1 && set "HAS_ACTOR_KIND=1"
)

REM LEVEL_SEQUENCE: dedicated Sequencer package.
set "HAS_LEVEL_SEQUENCE=0"
if exist "%SDK%\SDK\LevelSequence_classes.hpp" set "HAS_LEVEL_SEQUENCE=1"

REM UMG (widget system): present in virtually every modern UE game.
REM If missing, create a minimal forward-declaration stub so the rest compiles.
set "HAS_UMG=1"
if not exist "%SDK%\SDK\UMG_classes.hpp" (
    set "HAS_UMG=0"
    echo [WARN] UMG_classes.hpp not found in this SDK.
    echo        Widget inspection will be unavailable. A minimal stub will be used
    echo        so the remaining features still compile.
    (
        echo #pragma once
        echo // Auto-generated stub: UMG package not present in this SDK dump.
        echo namespace SDK {
        echo     class UUserWidget;
        echo     class UPanelWidget;
        echo     enum ESlateVisibility { Visible, Collapsed, Hidden, HitTestInvisible, SelfHitTestInvisible };
        echo }
    ) > "%STUB_DIR%\SDK\UMG_classes.hpp"
)

REM LevelSequence_classes.hpp: unconditionally included by Unreal.h so a stub is
REM always generated when the real header is absent (actual usage is ifdef-gated).
if !HAS_LEVEL_SEQUENCE!==0 (
    > "%STUB_DIR%\SDK\LevelSequence_classes.hpp" echo #pragma once
)

REM ---------------------------------------------------------------------------
REM Summary
REM ---------------------------------------------------------------------------
echo.
echo === UETools-GUI ^(Dumper7^) build ==========================================
if !IS_UE5!==1 (
    echo Engine  : Unreal Engine 5
) else (
    echo Engine  : Unreal Engine 4
)
echo SDK     : %SDK%
echo Output  : %ROOT%\bin\%DLL_NAME%.dll
echo VS      : %VS_ROOT%
echo.
echo Features enabled:
echo   [x] SOFT_PATH
echo   [x] FREE_CAMERA
echo   [x] ACTORS_TRACKING
echo   [x] COLLISION_VISUALIZER
echo   [x] WAIT_FOR_TITLE_INIT
if !IS_UE5!==1      echo   [x] UE5
if !HAS_ACTOR_TRACE!==1 echo   [x] ACTOR_TRACE
if !HAS_ACTOR_KIND!==1  echo   [x] ACTOR_KIND
if !HAS_LEVEL_SEQUENCE!==1 echo   [x] LEVEL_SEQUENCE
if !HAS_UMG!==0 echo   [ ] (UMG -- stub only, widget features unavailable^)
echo ============================================================================
echo.

REM ---------------------------------------------------------------------------
REM Write the cl.exe helper batch
REM
REM We write a temporary helper rather than calling cl.exe inline because
REM mixing vcvars64 + cl.exe in a single cmd /c "" trips over quote escaping
REM with embedded paths.  The ^^ sequences below become ^ (line continuations)
REM inside the generated file.
REM ---------------------------------------------------------------------------
set "BUILD_HELPER=%ROOT%\build\_run_cl.bat"

>  "%BUILD_HELPER%" echo @echo off
>> "%BUILD_HELPER%" echo call "%VCVARS%" ^>nul
>> "%BUILD_HELPER%" echo if errorlevel 1 exit /b 1
>> "%BUILD_HELPER%" echo cl.exe /nologo /LD /std:c++20 /EHsc /MT /O2 /Oi /bigobj ^^

REM -- Preprocessor defines (fixed) --
>> "%BUILD_HELPER%" echo     /D WIN32_LEAN_AND_MEAN /D NOMINMAX /D NDEBUG /D _WINDOWS /D _USRDLL ^^
>> "%BUILD_HELPER%" echo     /D UNICODE /D _UNICODE ^^

REM -- Feature defines (always on) --
>> "%BUILD_HELPER%" echo     /D WAIT_FOR_TITLE_INIT ^^
>> "%BUILD_HELPER%" echo     /D SOFT_PATH ^^
>> "%BUILD_HELPER%" echo     /D FREE_CAMERA ^^
>> "%BUILD_HELPER%" echo     /D ACTORS_TRACKING ^^
>> "%BUILD_HELPER%" echo     /D COLLISION_VISUALIZER ^^

REM -- Feature defines (auto-detected) --
if !IS_UE5!==1         >> "%BUILD_HELPER%" echo     /D UE5 ^^
if !HAS_ACTOR_TRACE!==1 >> "%BUILD_HELPER%" echo     /D ACTOR_TRACE ^^
if !HAS_ACTOR_KIND!==1  >> "%BUILD_HELPER%" echo     /D ACTOR_KIND ^^
if !HAS_LEVEL_SEQUENCE!==1 >> "%BUILD_HELPER%" echo     /D LEVEL_SEQUENCE ^^

REM -- Warning suppression --
>> "%BUILD_HELPER%" echo     /W0 /wd4244 /wd4267 /wd4334 ^^

REM -- Include paths --
REM   UETools-GUI source first, then ImGui, then the game SDK (highest priority
REM   for all SDK\ headers), then the stub directory (fallback for absent headers).
>> "%BUILD_HELPER%" echo     /I "%ROOT%\UETools-GUI" ^^
>> "%BUILD_HELPER%" echo     /I "%ROOT%\SDKs\ImGui" ^^
>> "%BUILD_HELPER%" echo     /I "%SDK%" ^^
>> "%BUILD_HELPER%" echo     /I "%STUB_DIR%" ^^

REM -- Output locations --
>> "%BUILD_HELPER%" echo     /Fe"%ROOT%\bin\%DLL_NAME%.dll" /Fo"%OBJ_DIR%\\" /Fd"%OBJ_DIR%\\" ^^

REM -- UETools-GUI source files --
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\main.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\GUI.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\DirectWindow.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\Unreal.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\Math.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\Utilities.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\ConfigInstance.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\UETools-GUI\FileInstance.cpp" ^^

REM -- ImGui source files --
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_demo.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_draw.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_impl_dx11.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_impl_win32.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_tables.cpp" ^^
>> "%BUILD_HELPER%" echo     "%ROOT%\SDKs\ImGui\imgui_widgets.cpp" ^^

REM -- Game SDK: Basic.cpp (always present) --
>> "%BUILD_HELPER%" echo     "%SDK%\SDK\Basic.cpp" ^^

REM -- Game SDK: ALL *_functions.cpp files found in the SDK.
REM    Compiling every functions file avoids "unresolved external symbol" errors
REM    that occur when any SDK class calls into a package we didn't explicitly list.
for %%F in ("%SDK%\SDK\*_functions.cpp") do (
    >> "%BUILD_HELPER%" echo     "%%F" ^^
)

REM -- Linker (no ^^ on the last line) --
>> "%BUILD_HELPER%" echo     /link /SUBSYSTEM:WINDOWS /DLL /MACHINE:X64 /OPT:REF /OPT:ICF ^^
>> "%BUILD_HELPER%" echo     d3d11.lib dwmapi.lib user32.lib kernel32.lib advapi32.lib shell32.lib

REM ---------------------------------------------------------------------------
REM Run the build
REM ---------------------------------------------------------------------------
call "%BUILD_HELPER%"
if errorlevel 1 goto :build_failed

echo.
echo === Build complete ===
echo Output : %ROOT%\bin\%DLL_NAME%.dll
echo.
echo Inject this DLL into the running game process (any DLL injector).
echo Press Insert in-game to open / close the UETools-GUI menu.
echo.
exit /b 0

REM ---------------------------------------------------------------------------
:build_failed
echo.
echo [ERROR] Build failed. Common causes:
echo.
echo   Unresolved external symbol for an SDK function:
echo     A function body lives in a ^<Package^>_functions.cpp we did not compile.
echo     Open build\_run_cl.bat and add the relevant file from the game's SDK\
echo     folder, then run that helper directly to test.
echo.
echo   Incomplete type errors on SDK::UUserWidget / ESlateVisibility:
echo     The game's SDK has no UMG package.  Widget-related code in Unreal.h /
echo     GUI.h references those types unconditionally.  Guard that code with
echo     #ifdef SOFT_PATH or contact the UETools-GUI maintainer.
echo.
echo   Static assert / offset mismatch:
echo     SDK dump was generated for a different game version or engine build.
echo     Re-dump with Dumper-7 against the correct binary.
echo.
echo   Wrong engine version:
echo     If UE5 mode is wrong, check whether TObjectPtr appears in the SDK
echo     headers and toggle /D UE5 manually inside build\_run_cl.bat.
goto :fail

REM ---------------------------------------------------------------------------
:usage
echo.
echo USAGE
echo   Drag a Dumper7 CppSDK folder onto this script.
echo   Or run:   build.bat ^<path-to-CppSDK^> [output-name]
echo.
echo   The CppSDK folder must contain SDK.hpp at its top level plus
echo   an SDK\ subfolder with .hpp / .cpp files.
echo.
exit /b 1

REM ---------------------------------------------------------------------------
:fail
echo.
pause
exit /b 1
