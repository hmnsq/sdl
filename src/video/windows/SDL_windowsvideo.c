/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
#ಅನ್ತರ್ಭಾವ "../SDL_vulkan_internal.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_hid.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsframebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsmessagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsrawinput.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsvulkan.h"

#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ಅನ್ತರ್ಭಾವ <shobjidl.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ITaskbarList3_FWD_DEFINED__
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITaskbarList3 ITaskbarList3;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ITaskbarList3_INTERFACE_DEFINED__
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_ಸಾಮಾನ್ಯ = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#ಆದರೆ defined(_MSC_VER)
#ಸೂಚನೆ warning(disable: 4103)
#ಆದರೆ_ಅಂತ್ಯ
#ಸೂಚನೆ pack(ತಳ್ಳು, 8)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ THUMBBUTTON
{
    THUMBBUTTONMASK dw_ಮುಖವಾಡ;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ THUMBBUTTON *LPTHUMBBUTTON;
#ಸೂಚನೆ pack(ತೆಗೆ)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HIMAGELIST
ರಚನೆ _IMAGELIST;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _IMAGELIST *HIMAGELIST;
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, ಶೂನ್ಯ **ppvObject);
    ULONG (__stdcall *ಕೂಡಿಸು_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *ಕೂಡಿಸು_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ಗಣ_ಸಕ್ರಿಯ_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_ಕಿಟಕಿ)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *ಗಣ_ಪ್ರಗತಿ_ಮೌಲ್ಯ)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_ಒಟ್ಟು);
    HRESULT (__stdcall *ಗಣ_ಪ್ರಗತಿ_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *ರಿಜಿಸ್ಟರ್_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *ಗಣ_Tab_ಕ್ರಮ)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_ಸೇರಿಸು_Before);
    HRESULT (__stdcall *ಗಣ_Tab_ಸಕ್ರಿಯ)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_ಕೂಡಿಸು_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_ಗಣ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *ಗಣ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *ಗಣ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *ಗಣ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

ರಚನೆ ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#ಆದರೆ_ಅಂತ್ಯ // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_GDK_TEXTINPUT
#ಅನ್ತರ್ಭಾವ "../gdk/SDL_gdktextinput.h"
#ಆದರೆ_ಅಂತ್ಯ

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ಸ್ಥಿರ bool WIN_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_ಸಂದೇಶ_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden = true;

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL UpdateWindowsRawKeyboard(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
    WIN_ಗಣ_Raw_Keyboard_Enabled(_this, enabled);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
    WIN_ಗಣ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL UpdateWindowsRawKeyboardInputsink(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
    WIN_ಗಣ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL UpdateWindowsRawMouseNoLegacy(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
    WIN_ಗಣ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL Update_Windows_Enable_ಸಂದೇಶ_Loop(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    g_Windows_Enable_ಸಂದೇಶ_Loop = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, true);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL UpdateWindowsEnableMenuMnemonics(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL Update_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    g_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, true);
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಸ್ಥಿರ bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD ಫಲಿತಾಂಶ;
    ಆದರೆ (_this->suspend_screensaver) {
        ಫಲಿತಾಂಶ = ಗಣ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = ಗಣ_Thread_Execution_State(ES_CONTINUOUS);
    }
    ಆದರೆ (ಫಲಿತಾಂಶ == 0) {
        SDL_ಗಣ_Error("SetThreadExecutionState() failed");
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
ಬಾಹ್ಯ ಶೂನ್ಯ D3D12_XBOX_GetResolution(Uint32 *ಅಗಲ, Uint32 *ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ

// Windows driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;

    SDL_UnregisterApp();
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (ದತ್ತಾಂಶ->userDLL) {
        SDL_UnloadObject(ದತ್ತಾಂಶ->userDLL);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->shcoreDLL) {
        SDL_UnloadObject(ದತ್ತಾಂಶ->shcoreDLL);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->dwmapiDLL) {
        SDL_UnloadObject(ದತ್ತಾಂಶ->dwmapiDLL);
    }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    ಆದರೆ (ದತ್ತಾಂಶ->pDXGIFactory) {
        IDXGIFactory_Release(ದತ್ತಾಂಶ->pDXGIFactory);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->dxgiDLL) {
        SDL_UnloadObject(ದತ್ತಾಂಶ->dxgiDLL);
    }
#ಆದರೆ_ಅಂತ್ಯ
    SDL_free(device->ಆಂತರಿಕ->rawinput);
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *WIN_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    SDL_ರಿಜಿಸ್ಟರ್_App(ಖಾಲಿ, 0, ಖಾಲಿ);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (device) {
        ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ = ಖಾಲಿ;
    }
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_UnregisterApp();
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    device->system_theme = WIN_GetSystemTheme();

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ದತ್ತಾಂಶ->userDLL = SDL_ತುಂಬು_Object("USER32.DLL");
    ಆದರೆ (ದತ್ತಾಂಶ->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ದತ್ತಾಂಶ->Close_Touch_ಒಳಹರಿವು_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "CloseTouchInputHandle");
        ದತ್ತಾಂಶ->Get_Touch_ಒಳಹರಿವು_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, ಪೂರ್ಣಾಂಕ)) SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetTouchInputInfo");
        ದತ್ತಾಂಶ->ರಿಜಿಸ್ಟರ್_Touch_ಕಿಟಕಿ = (BOOL (WINAPI *)(HWND, ULONG))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "RegisterTouchWindow");
        ದತ್ತಾಂಶ->ಗಣ_Process_DPIAware = (BOOL (WINAPI *)(ಶೂನ್ಯ))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "SetProcessDPIAware");
        ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "SetProcessDpiAwarenessContext");
        ದತ್ತಾಂಶ->ಗಣ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "SetThreadDpiAwarenessContext");
        ದತ್ತಾಂಶ->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(ಶೂನ್ಯ))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetThreadDpiAwarenessContext");
        ದತ್ತಾಂಶ->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetAwarenessFromDpiAwarenessContext");
        ದತ್ತಾಂಶ->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "EnableNonClientDpiScaling");
        ದತ್ತಾಂಶ->Adjust_ಕಿಟಕಿ_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "AdjustWindowRectExForDpi");
        ದತ್ತಾಂಶ->Get_Dpi_For_ಕಿಟಕಿ = (UINT (WINAPI *)(HWND))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetDpiForWindow");
        ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "AreDpiAwarenessContextsEqual");
        ದತ್ತಾಂಶ->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "IsValidDpiAwarenessContext");
        ದತ್ತಾಂಶ->Get_Display_Config_ಬಫರ್_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetDisplayConfigBufferSizes");
        ದತ್ತಾಂಶ->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_ಮಾರ್ಗ_INFO*,UINT32 *,DISPLAYCONFIG_ಬಹುಲಕ_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "QueryDisplayConfig");
        ದತ್ತಾಂಶ->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ*))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "DisplayConfigGetDeviceInfo");
        ದತ್ತಾಂಶ->Get_ಸೂಚಕ_Type = (BOOL (WINAPI *)(UINT32, ಸೂಚಕ_ಒಳಹರಿವು_TYPE *))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetPointerType");
        ದತ್ತಾಂಶ->Get_ಸೂಚಕ_Pen_Info = (BOOL (WINAPI *)(UINT32, ಸೂಚಕ_PEN_INFO *))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetPointerPenInfo");
        ದತ್ತಾಂಶ->Get_ಸೂಚಕ_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ClearError();
    }

    ದತ್ತಾಂಶ->shcoreDLL = SDL_ತುಂಬು_Object("SHCORE.DLL");
    ಆದರೆ (ದತ್ತಾಂಶ->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ದತ್ತಾಂಶ->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->shcoreDLL, "GetDpiForMonitor");
        ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ClearError();
    }

    ದತ್ತಾಂಶ->dwmapiDLL = SDL_ತುಂಬು_Object("DWMAPI.DLL");
    ಆದರೆ (ದತ್ತಾಂಶ->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ದತ್ತಾಂಶ->DwmFlush = (HRESULT (WINAPI *)(ಶೂನ್ಯ))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->dwmapiDLL, "DwmFlush");
        ದತ್ತಾಂಶ->Dwm_Enable_Blur_Behind_ಕಿಟಕಿ = (HRESULT (WINAPI *)(HWND hwnd, ಸ್ಥಿರಾಂಕ DWM_BLURBEHIND *pBlurBehind))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->dwmapiDLL, "DwmEnableBlurBehindWindow");
        ದತ್ತಾಂಶ->Dwm_ಗಣ_ಕಿಟಕಿ_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ClearError();
    }
#ಆದರೆ_ಅಂತ್ಯ // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    ದತ್ತಾಂಶ->dxgiDLL = SDL_ತುಂಬು_Object("DXGI.DLL");
    ಆದರೆ (ದತ್ತಾಂಶ->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, ಶೂನ್ಯ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->dxgiDLL, "CreateDXGIFactory");
        ಆದರೆ (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (ಶೂನ್ಯ **)&ದತ್ತಾಂಶ->pDXGIFactory);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = WIN_ಗಣ_Display_ಬಹುಲಕ;
#ಆದರೆ_ಅಂತ್ಯ
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#ಆದರೆ_ಅಂತ್ಯ

    device->CreateSDLWindow = WIN_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = WIN_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Icon = WIN_ಗಣ_ಕಿಟಕಿ_Icon;
    device->ಗಣ_ಕಿಟಕಿ_Position = WIN_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = WIN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ = WIN_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ;
    device->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels = WIN_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels;
    device->ಗಣ_ಕಿಟಕಿ_Opacity = WIN_ಗಣ_ಕಿಟಕಿ_Opacity;
    device->Show_ಕಿಟಕಿ = WIN_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = WIN_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = WIN_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = WIN_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = WIN_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = WIN_Restore_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Bordered = WIN_ಗಣ_ಕಿಟಕಿ_Bordered;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = WIN_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ = WIN_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = WIN_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ = WIN_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ;
    device->ಗಣ_ಕಿಟಕಿ_Modal = WIN_ಗಣ_ಕಿಟಕಿ_Modal;
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_ಕಿಟಕಿ_ICCProfile = WIN_Get_ಕಿಟಕಿ_ICCProfile;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Rect = WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Rect;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Grab = WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Grab;
    device->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab = WIN_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab;
#ಆದರೆ_ಅಂತ್ಯ
    device->Destroy_ಕಿಟಕಿ = WIN_Destroy_ಕಿಟಕಿ;
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_ಕಿಟಕಿ_Framebuffer = WIN_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = WIN_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = WIN_Destroy_ಕಿಟಕಿ_Framebuffer;
    device->On_ಕಿಟಕಿ_Enter = WIN_On_ಕಿಟಕಿ_Enter;
    device->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test = WIN_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_ಕಿಟಕಿ = WIN_Flash_ಕಿಟಕಿ;
    device->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ = WIN_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ;
    device->Show_ಕಿಟಕಿ_System_Menu = WIN_Show_ಕಿಟಕಿ_System_Menu;
    device->ಗಣ_ಕಿಟಕಿ_Focusable = WIN_ಗಣ_ಕಿಟಕಿ_Focusable;
    device->Update_ಕಿಟಕಿ_Shape = WIN_Update_ಕಿಟಕಿ_Shape;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
    device->GL_ತುಂಬು_Library = WIN_GL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = WIN_GL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = WIN_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = WIN_GL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = WIN_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ಆದರೆ_ಅಂತ್ಯ
        // Use EGL based functions
        device->GL_ತುಂಬು_Library = WIN_GLES_ತುಂಬು_Library;
        device->GL_Get_Proc_ವಿಳಾಸ = WIN_GLES_Get_Proc_ವಿಳಾಸ;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = WIN_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
        device->GL_Get_ಅದಲುಬದಲು_Interval = WIN_GLES_Get_ಅದಲುಬದಲು_Interval;
        device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = WIN_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = WIN_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು = WIN_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Stop_ಪಠ್ಯ_ಒಳಹರಿವು = WIN_Stop_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area = WIN_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->ಗಣ_Clipboard_ದತ್ತಾಂಶ = WIN_ಗಣ_Clipboard_ದತ್ತಾಂಶ;
    device->Get_Clipboard_ದತ್ತಾಂಶ = WIN_Get_Clipboard_ದತ್ತಾಂಶ;
    device->Has_Clipboard_ದತ್ತಾಂಶ = WIN_Has_Clipboard_ದತ್ತಾಂಶ;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು = GDK_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Stop_ಪಠ್ಯ_ಒಳಹರಿವು = GDK_Stop_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area = GDK_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#ಆದರೆ_ಅಂತ್ಯ

    device->ಬಿಡುಗಡೆ = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_ಕಿಟಕಿ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_ಸಂದೇಶ_Box,
    #ಇಲ್ಲದಿದ್ದರೆ
    ಖಾಲಿ,
    #ಆದರೆ_ಅಂತ್ಯ
    false
};

ಸ್ಥಿರ BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context) {
        ದತ್ತಾಂಶ->dpi_unaware_context_declared = true;
        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness) {
        // Windows 8.1
        ಹಿಂತಿರುಗಿ SUCCEEDED(ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ FALSE;
}

ಸ್ಥಿರ BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness) {
        // Windows 8.1
        ಹಿಂತಿರುಗಿ SUCCEEDED(ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_DPIAware) {
        // Windows Vista
        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->ಗಣ_Process_DPIAware();
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ FALSE;
}

ಸ್ಥಿರ BOOL WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor(SDL_VideoDevice *_this)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness) {
        // Windows 8.1
        ಹಿಂತಿರುಗಿ SUCCEEDED(ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness(PROCESS_ಪ್ರತಿ_MONITOR_DPI_AWARE));
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Older OS: fall back to system DPI aware
        ಹಿಂತಿರುಗಿ WIN_DeclareDPIAwareSystem(_this);
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ FALSE;
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ BOOL WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor_V2(SDL_VideoDevice *_this)
{
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ಹಿಂತಿರುಗಿ FALSE;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607

        /* NOTE: SetThreadDpiAwarenessContext doesn't work here with OpenGL - the OpenGL contents
           end up still getting OS scaled. (tested on Windows 10 21H1 19043.1348, NVIDIA 496.49)

           NOTE: Enabling DPI awareness through Windows Explorer
           (right click .exe -> Properties -> Compatibility -> High DPI Settings ->
           check "Override high DPI Scaling behaviour", select Application) gives
           a DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE context (at least on Windows 10 21H1), and
           setting DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 will fail.

           NOTE: Entering exclusive fullscreen in a DPI_AWARENESS_CONTEXT_UNAWARE process
           appears to cause Windows to change the .exe manifest to DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE
           on future launches. This means attempting to use DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
           will fail in the future until you manually clear the "Override high DPI Scaling behaviour"
           setting in Windows Explorer (tested on Windows 10 21H2).
         */
        ಆದರೆ (ದತ್ತಾಂಶ->ಗಣ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2)) {
            ಹಿಂತಿರುಗಿ TRUE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor(_this);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Older OS: fall back to per-monitor (or system)
        ಹಿಂತಿರುಗಿ WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor(_this);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->GetThreadDpiAwarenessContext && ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = ದತ್ತಾಂಶ->GetThreadDpiAwarenessContext();

        ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            ಹಿಂತಿರುಗಿ "unaware";
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            ಹಿಂತಿರುಗಿ "system";
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE)) {
            ಹಿಂತಿರುಗಿ "permonitor";
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2)) {
            ಹಿಂತಿರುಗಿ "permonitorv2";
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            ಹಿಂತಿರುಗಿ "unaware_gdiscaled";
        }
    }

    ಹಿಂತಿರುಗಿ "";
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    ಆದರೆ (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor_V2(_this);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_ಪ್ರತಿ_Monitor(_this);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ಸ್ಥಿರ bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    HRESULT hr;

    hr = WIN_CoInitialize();
    ಆದರೆ (SUCCEEDED(hr)) {
        ದತ್ತಾಂಶ->coinitialized = true;

#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(ಖಾಲಿ);
        ಆದರೆ (SUCCEEDED(hr)) {
            ದತ್ತಾಂಶ->oleinitialized = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)hr);
        }
#ಆದರೆ_ಅಂತ್ಯ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)hr);
    }

    WIN_InitDPIAwareness(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_ಒಳಹರಿವು(_this);
    }

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

        SDL_zero(ಬಹುಲಕ);
        D3D12_XBOX_GetResolution(&ಬಹುಲಕ.w, &ಬಹುಲಕ.h);
        ಬಹುಲಕ.refresh_ದರ = 60.0f;
        ಬಹುಲಕ.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ);
    }
#ಇಲ್ಲದಿದ್ದರೆ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (!WIN_InitModes(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    _this->ಆಂತರಿಕ->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#ಆದರೆ_ಅಂತ್ಯ

    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_ಸಂದೇಶ_Loop, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_USABLE_WHILE_CURSOR_HIDDEN, Update_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden, ಖಾಲಿ);

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ದತ್ತಾಂಶ->_SDL_WAKEUP = ರಿಜಿಸ್ಟರ್_ಕಿಟಕಿ_ಸಂದೇಶ_A("_SDL_WAKEUP");
    ದತ್ತಾಂಶ->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? ರಿಜಿಸ್ಟರ್_ಕಿಟಕಿ_ಸಂದೇಶ_A("TaskbarButtonCreated") : 0;
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_ಸಂದೇಶ_Loop, ಖಾಲಿ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ಖಾಲಿ);
    SDL_RemoveHintCallback(SDL_HINT_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_USABLE_WHILE_CURSOR_HIDDEN, Update_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden, ಖಾಲಿ);

    WIN_Quit_Raw_ಒಳಹರಿವು(_this);
    WIN_Quit_Game_ಒಳಹರಿವು(_this);

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    ಆದರೆ (ದತ್ತಾಂಶ->taskbar_list) {
        ದತ್ತಾಂಶ->taskbar_list->lpVtbl->Release(ದತ್ತಾಂಶ->taskbar_list);
        ದತ್ತಾಂಶ->taskbar_list = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->oleinitialized) {
        OleUninitialize();
        ದತ್ತಾಂಶ->oleinitialized = false;
    }
#ಆದರೆ_ಅಂತ್ಯ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    ಆದರೆ (ದತ್ತಾಂಶ->coinitialized) {
        WIN_CoUninitialize();
        ದತ್ತಾಂಶ->coinitialized = false;
    }
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ವ್ಯಾಖ್ಯಾನಿಸು D3D_DEBUG_INFO
#ಅನ್ತರ್ಭಾವ <d3d9.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ D3D_DEBUG_INFO
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D_SDK_ಆವೃತ್ತಿ
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D_SDK_ಆವೃತ್ತಿ (32 | 0x80000000)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D9b_SDK_ಆವೃತ್ತಿ
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D9b_SDK_ಆವೃತ್ತಿ (31 | 0x80000000)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ //
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D_SDK_ಆವೃತ್ತಿ
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D_SDK_ಆವೃತ್ತಿ 32
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D9b_SDK_ಆವೃತ್ತಿ
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D9b_SDK_ಆವೃತ್ತಿ 31
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

bool D3_D_ತುಂಬು_DLL(ಶೂನ್ಯ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_ತುಂಬು_Object("D3D9.DLL");
    ಆದರೆ (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_ತುಂಬು_Function(*pD3DDLL, "Direct3DCreate9Ex");
            ಆದರೆ (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_ಆವೃತ್ತಿ, &pDirect3D9ExInterface);
                ಆದರೆ (SUCCEEDED(hr)) {
                    ಸ್ಥಿರಾಂಕ GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (ಶೂನ್ಯ **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    ಆದರೆ (SUCCEEDED(hr)) {
                        ಹಿಂತಿರುಗಿ true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_ತುಂಬು_Function(*pD3DDLL, "Direct3DCreate9");
        ಆದರೆ (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_ಆವೃತ್ತಿ);
            ಆದರೆ (*pDirect3D9Interface) {
                ಹಿಂತಿರುಗಿ true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = ಖಾಲಿ;
    }
    *pDirect3D9Interface = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

ಪೂರ್ಣಾಂಕ SDL_Get_Direct3_D9_Adapter_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID)
{
    ಶೂನ್ಯ *pD3DDLL;
    IDirect3D9 *pD3D;
    ಆದರೆ (!D3_D_ತುಂಬು_DLL(&pD3DDLL, &pD3D)) {
        SDL_ಗಣ_Error("Unable to create Direct3D interface");
        ಹಿಂತಿರುಗಿ -1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Display_ದತ್ತಾಂಶ *p_ದತ್ತಾಂಶ = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(displayID);
        ಪೂರ್ಣಾಂಕ adapter_ಸೂಚ್ಯಂಕ = D3DADAPTER_DEFAULT;

        ಆದರೆ (!p_ದತ್ತಾಂಶ) {
            SDL_ಗಣ_Error("Invalid display index");
            adapter_ಸೂಚ್ಯಂಕ = -1; // make sure we return something invalid
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಅಕ್ಷರ *displayName = WIN_String_ಗಮ್ಯ_UTF8_W(p_ದತ್ತಾಂಶ->DeviceName);
            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = IDirect3_D9_Get_Adapter_ಎಣಿಕೆ(pD3D);
            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
            ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                ಆದರೆ (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_ಸೂಚ್ಯಂಕ = i;
                    ನಿಲ್ಲಿಸು;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        ಹಿಂತಿರುಗಿ adapter_ಸೂಚ್ಯಂಕ;
    }
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ಪೂರ್ಣಾಂಕ *adapter_ಸೂಚ್ಯಂಕ, ಪೂರ್ಣಾಂಕ *output_ಸೂಚ್ಯಂಕ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_DXGI_H
    ಆದರೆ (adapter_ಸೂಚ್ಯಂಕ) {
        *adapter_ಸೂಚ್ಯಂಕ = -1;
    }
    ಆದರೆ (output_ಸೂಚ್ಯಂಕ) {
        *output_ಸೂಚ್ಯಂಕ = -1;
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರಾಂಕ SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *videodata = videodevice ? videodevice->ಆಂತರಿಕ : ಖಾಲಿ;
    SDL_Display_ದತ್ತಾಂಶ *p_ದತ್ತಾಂಶ = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(displayID);
    ಪೂರ್ಣಾಂಕ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_ಸೂಚ್ಯಂಕ) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_ಸೂಚ್ಯಂಕ) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("outputIndex");
    }

    *adapter_ಸೂಚ್ಯಂಕ = -1;
    *output_ಸೂಚ್ಯಂಕ = -1;

    ಆದರೆ (!p_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid display index");
    }

    ಆದರೆ (!videodata || !videodata->pDXGIFactory) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    ಆಗ (*adapter_ಸೂಚ್ಯಂಕ == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ಆಗ (*adapter_ಸೂಚ್ಯಂಕ == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ಆದರೆ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ಆದರೆ (SDL_wcscmp(outputDesc.DeviceName, p_ದತ್ತಾಂಶ->DeviceName) == 0) {
                    *adapter_ಸೂಚ್ಯಂಕ = nAdapter;
                    *output_ಸೂಚ್ಯಂಕ = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    ಆದರೆ (*adapter_ಸೂಚ್ಯಂಕ == -1) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find matching adapter");
    }
    ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ
}

SDL_SystemTheme WIN_GetSystemTheme(ಶೂನ್ಯ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_ಕೀಲಿ;
    DWORD dwType = REG_DWORD;
    DWORD ಮೌಲ್ಯ = ~0U;
    DWORD ಉದ್ದಳತೆ = ಗಾತ್ರ(ಮೌಲ್ಯ);

    // Technically this isn't the system theme, but it's the preference for applications
    ಆದರೆ (Reg_Open_ಕೀಲಿ_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, ಕೀಲಿ_READ, &h_ಕೀಲಿ) == ERROR_SUCCESS) {
        ಆದರೆ (Reg_Query_ಮೌಲ್ಯ_Ex_W(h_ಕೀಲಿ, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&ಮೌಲ್ಯ, &ಉದ್ದಳತೆ) == ERROR_SUCCESS) {
            ಆದರೆ (ಮೌಲ್ಯ == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_ಕೀಲಿ(h_ಕೀಲಿ);
    }
    ಹಿಂತಿರುಗಿ theme;
}

bool WIN_Is_ಪ್ರತಿ_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual && ದತ್ತಾಂಶ->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2, ದತ್ತಾಂಶ->GetThreadDpiAwarenessContext());
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ false;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
