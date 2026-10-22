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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_vulkan_internal.h"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_hid.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsframebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsmessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsrawinput.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvulkan.h"

#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ਅਨ੍ਤਰ੍ਭਾਵ <shobjidl.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ITaskbarList3_FWD_DEFINED__
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITaskbarList3 ITaskbarList3;
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ITaskbarList3_INTERFACE_DEFINED__
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_ਸਾਧਾਰਨ = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#ਜੇ defined(_MSC_VER)
#ਹਦਾਇਤ warning(disable: 4103)
#ਜੇ_ਅੰਤ
#ਹਦਾਇਤ pack(ਧੱਕੋ, 8)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ THUMBBUTTON
{
    THUMBBUTTONMASK dw_ਨਕਾਬ;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ THUMBBUTTON *LPTHUMBBUTTON;
#ਹਦਾਇਤ pack(ਕੱਢੋ)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HIMAGELIST
ਬਣਤਰ _IMAGELIST;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _IMAGELIST *HIMAGELIST;
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, ਖਾਲੀ **ppvObject);
    ULONG (__stdcall *ਜੋੜੋ_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *ਜੋੜੋ_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ਸੈੱਟ_ਸਰਗਰਮ_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_ਖਿੜਕੀ)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *ਸੈੱਟ_ਤਰੱਕੀ_ਮੁੱਲ)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_ਕੁੱਲ);
    HRESULT (__stdcall *ਸੈੱਟ_ਤਰੱਕੀ_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *ਰਜਿਸਟਰ_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *ਸੈੱਟ_Tab_ਕ੍ਰਮ)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_ਪਾਓ_Before);
    HRESULT (__stdcall *ਸੈੱਟ_Tab_ਸਰਗਰਮ)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_ਜੋੜੋ_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_ਸੈੱਟ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *ਸੈੱਟ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *ਸੈੱਟ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *ਸੈੱਟ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

ਬਣਤਰ ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#ਜੇ_ਅੰਤ // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_GDK_TEXTINPUT
#ਅਨ੍ਤਰ੍ਭਾਵ "../gdk/SDL_gdktextinput.h"
#ਜੇ_ਅੰਤ

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ਸਥਿਰ bool WIN_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_ਸੁਨੇਹਾ_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden = true;

ਸਥਿਰ ਖਾਲੀ SDLCALL UpdateWindowsRawKeyboard(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
    WIN_ਸੈੱਟ_Raw_Keyboard_Enabled(_this, enabled);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
    WIN_ਸੈੱਟ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL UpdateWindowsRawKeyboardInputsink(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
    WIN_ਸੈੱਟ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL UpdateWindowsRawMouseNoLegacy(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
    WIN_ਸੈੱਟ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL Update_Windows_Enable_ਸੁਨੇਹਾ_Loop(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    g_Windows_Enable_ਸੁਨੇਹਾ_Loop = SDL_GetStringBoolean(new_ਮੁੱਲ, true);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL UpdateWindowsEnableMenuMnemonics(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
}

ਸਥਿਰ ਖਾਲੀ SDLCALL Update_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    g_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_ਮੁੱਲ, true);
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਸਥਿਰ bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD ਨਤੀਜਾ;
    ਜੇ (_this->suspend_screensaver) {
        ਨਤੀਜਾ = ਸੈੱਟ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = ਸੈੱਟ_Thread_Execution_State(ES_CONTINUOUS);
    }
    ਜੇ (ਨਤੀਜਾ == 0) {
        SDL_ਸੈੱਟ_Error("SetThreadExecutionState() failed");
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
ਬਾਹਰੀ ਖਾਲੀ D3D12_XBOX_GetResolution(Uint32 *ਚੌੜਾਈ, Uint32 *ਉਚਾਈ);
#ਜੇ_ਅੰਤ

// Windows driver bootstrap functions

ਸਥਿਰ ਖਾਲੀ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;

    SDL_UnregisterApp();
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (ਅੰਕੜੇ->userDLL) {
        SDL_UnloadObject(ਅੰਕੜੇ->userDLL);
    }
    ਜੇ (ਅੰਕੜੇ->shcoreDLL) {
        SDL_UnloadObject(ਅੰਕੜੇ->shcoreDLL);
    }
    ਜੇ (ਅੰਕੜੇ->dwmapiDLL) {
        SDL_UnloadObject(ਅੰਕੜੇ->dwmapiDLL);
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    ਜੇ (ਅੰਕੜੇ->pDXGIFactory) {
        IDXGIFactory_Release(ਅੰਕੜੇ->pDXGIFactory);
    }
    ਜੇ (ਅੰਕੜੇ->dxgiDLL) {
        SDL_UnloadObject(ਅੰਕੜੇ->dxgiDLL);
    }
#ਜੇ_ਅੰਤ
    SDL_free(device->ਅੰਦਰੂਨੀ->rawinput);
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *WIN_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;

    SDL_ਰਜਿਸਟਰ_App(ਨਿਰਾ, 0, ਨਿਰਾ);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (device) {
        ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ = ਨਿਰਾ;
    }
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_UnregisterApp();
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }
    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    device->system_theme = WIN_GetSystemTheme();

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਅੰਕੜੇ->userDLL = SDL_ਲੱਦੋ_Object("USER32.DLL");
    ਜੇ (ਅੰਕੜੇ->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ਅੰਕੜੇ->Close_Touch_ਨਿਵੇਸ਼_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "CloseTouchInputHandle");
        ਅੰਕੜੇ->Get_Touch_ਨਿਵੇਸ਼_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, ਪੂਰਨ)) SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetTouchInputInfo");
        ਅੰਕੜੇ->ਰਜਿਸਟਰ_Touch_ਖਿੜਕੀ = (BOOL (WINAPI *)(HWND, ULONG))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "RegisterTouchWindow");
        ਅੰਕੜੇ->ਸੈੱਟ_Process_DPIAware = (BOOL (WINAPI *)(ਖਾਲੀ))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "SetProcessDPIAware");
        ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "SetProcessDpiAwarenessContext");
        ਅੰਕੜੇ->ਸੈੱਟ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "SetThreadDpiAwarenessContext");
        ਅੰਕੜੇ->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(ਖਾਲੀ))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetThreadDpiAwarenessContext");
        ਅੰਕੜੇ->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetAwarenessFromDpiAwarenessContext");
        ਅੰਕੜੇ->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "EnableNonClientDpiScaling");
        ਅੰਕੜੇ->Adjust_ਖਿੜਕੀ_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "AdjustWindowRectExForDpi");
        ਅੰਕੜੇ->Get_Dpi_For_ਖਿੜਕੀ = (UINT (WINAPI *)(HWND))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetDpiForWindow");
        ਅੰਕੜੇ->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "AreDpiAwarenessContextsEqual");
        ਅੰਕੜੇ->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "IsValidDpiAwarenessContext");
        ਅੰਕੜੇ->Get_Display_Config_ਬਫਰ_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetDisplayConfigBufferSizes");
        ਅੰਕੜੇ->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_ਰਸਤਾ_INFO*,UINT32 *,DISPLAYCONFIG_ਬਹੁਲਕ_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "QueryDisplayConfig");
        ਅੰਕੜੇ->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ*))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "DisplayConfigGetDeviceInfo");
        ਅੰਕੜੇ->Get_ਸੂਚਕ_Type = (BOOL (WINAPI *)(UINT32, ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE *))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetPointerType");
        ਅੰਕੜੇ->Get_ਸੂਚਕ_Pen_Info = (BOOL (WINAPI *)(UINT32, ਸੂਚਕ_PEN_INFO *))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetPointerPenInfo");
        ਅੰਕੜੇ->Get_ਸੂਚਕ_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } ਨਹੀਂਤਾਂ {
        SDL_ClearError();
    }

    ਅੰਕੜੇ->shcoreDLL = SDL_ਲੱਦੋ_Object("SHCORE.DLL");
    ਜੇ (ਅੰਕੜੇ->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ਅੰਕੜੇ->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->shcoreDLL, "GetDpiForMonitor");
        ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } ਨਹੀਂਤਾਂ {
        SDL_ClearError();
    }

    ਅੰਕੜੇ->dwmapiDLL = SDL_ਲੱਦੋ_Object("DWMAPI.DLL");
    ਜੇ (ਅੰਕੜੇ->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ਅੰਕੜੇ->DwmFlush = (HRESULT (WINAPI *)(ਖਾਲੀ))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->dwmapiDLL, "DwmFlush");
        ਅੰਕੜੇ->Dwm_Enable_Blur_Behind_ਖਿੜਕੀ = (HRESULT (WINAPI *)(HWND hwnd, ਅਚਲ DWM_BLURBEHIND *pBlurBehind))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->dwmapiDLL, "DwmEnableBlurBehindWindow");
        ਅੰਕੜੇ->Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } ਨਹੀਂਤਾਂ {
        SDL_ClearError();
    }
#ਜੇ_ਅੰਤ // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    ਅੰਕੜੇ->dxgiDLL = SDL_ਲੱਦੋ_Object("DXGI.DLL");
    ਜੇ (ਅੰਕੜੇ->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, ਖਾਲੀ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->dxgiDLL, "CreateDXGIFactory");
        ਜੇ (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (ਖਾਲੀ **)&ਅੰਕੜੇ->pDXGIFactory);
        }
    }
#ਜੇ_ਅੰਤ

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = WIN_ਸੈੱਟ_Display_ਬਹੁਲਕ;
#ਜੇ_ਅੰਤ
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#ਜੇ_ਅੰਤ

    device->CreateSDLWindow = WIN_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Icon = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Icon;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Get_ਖਿੜਕੀ_Borders_ਮਾਪ = WIN_Get_ਖਿੜਕੀ_Borders_ਮਾਪ;
    device->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels = WIN_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Opacity = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Opacity;
    device->Show_ਖਿੜਕੀ = WIN_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = WIN_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = WIN_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = WIN_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = WIN_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = WIN_Restore_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Bordered = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Bordered;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ = WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Modal = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Modal;
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_ਖਿੜਕੀ_ICCProfile = WIN_Get_ਖਿੜਕੀ_ICCProfile;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab;
#ਜੇ_ਅੰਤ
    device->Destroy_ਖਿੜਕੀ = WIN_Destroy_ਖਿੜਕੀ;
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_ਖਿੜਕੀ_Framebuffer = WIN_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = WIN_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = WIN_Destroy_ਖਿੜਕੀ_Framebuffer;
    device->On_ਖਿੜਕੀ_Enter = WIN_On_ਖਿੜਕੀ_Enter;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test = WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_ਖਿੜਕੀ = WIN_Flash_ਖਿੜਕੀ;
    device->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ = WIN_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ;
    device->Show_ਖਿੜਕੀ_System_Menu = WIN_Show_ਖਿੜਕੀ_System_Menu;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Focusable = WIN_ਸੈੱਟ_ਖਿੜਕੀ_Focusable;
    device->Update_ਖਿੜਕੀ_Shape = WIN_Update_ਖਿੜਕੀ_Shape;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
    device->GL_ਲੱਦੋ_Library = WIN_GL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = WIN_GL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = WIN_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = ਨਿਰਾ;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ਜੇ_ਅੰਤ
        // Use EGL based functions
        device->GL_ਲੱਦੋ_Library = WIN_GLES_ਲੱਦੋ_Library;
        device->GL_Get_Proc_ਪਤਾ = WIN_GLES_Get_Proc_ਪਤਾ;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
        device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
        device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = WIN_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = WIN_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼ = WIN_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Stop_ਪਾਠ_ਨਿਵੇਸ਼ = WIN_Stop_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area = WIN_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->ਸੈੱਟ_Clipboard_ਅੰਕੜੇ = WIN_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ;
    device->Get_Clipboard_ਅੰਕੜੇ = WIN_Get_Clipboard_ਅੰਕੜੇ;
    device->Has_Clipboard_ਅੰਕੜੇ = WIN_Has_Clipboard_ਅੰਕੜੇ;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼ = GDK_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Stop_ਪਾਠ_ਨਿਵੇਸ਼ = GDK_Stop_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area = GDK_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#ਜੇ_ਅੰਤ

    device->ਮੁਕਤ = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_ਖਿੜਕੀ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ਵਾਪਸ device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_ਸੁਨੇਹਾ_Box,
    #ਨਹੀਂਤਾਂ
    ਨਿਰਾ,
    #ਜੇ_ਅੰਤ
    false
};

ਸਥਿਰ BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context) {
        ਅੰਕੜੇ->dpi_unaware_context_declared = true;
        ਵਾਪਸ ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness) {
        // Windows 8.1
        ਵਾਪਸ SUCCEEDED(ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ FALSE;
}

ਸਥਿਰ BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        ਵਾਪਸ ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness) {
        // Windows 8.1
        ਵਾਪਸ SUCCEEDED(ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_DPIAware) {
        // Windows Vista
        ਵਾਪਸ ਅੰਕੜੇ->ਸੈੱਟ_Process_DPIAware();
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ FALSE;
}

ਸਥਿਰ BOOL WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor(SDL_VideoDevice *_this)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        ਵਾਪਸ ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE);
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness) {
        // Windows 8.1
        ਵਾਪਸ SUCCEEDED(ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness(PROCESS_ਪ੍ਰਤੀ_MONITOR_DPI_AWARE));
    } ਨਹੀਂਤਾਂ {
        // Older OS: fall back to system DPI aware
        ਵਾਪਸ WIN_DeclareDPIAwareSystem(_this);
    }
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ FALSE;
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ BOOL WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor_V2(SDL_VideoDevice *_this)
{
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ਵਾਪਸ FALSE;
#ਨਹੀਂਤਾਂ
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context) {
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
        ਜੇ (ਅੰਕੜੇ->ਸੈੱਟ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2)) {
            ਵਾਪਸ TRUE;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor(_this);
        }
    } ਨਹੀਂਤਾਂ {
        // Older OS: fall back to per-monitor (or system)
        ਵਾਪਸ WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor(_this);
    }
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->GetThreadDpiAwarenessContext && ਅੰਕੜੇ->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = ਅੰਕੜੇ->GetThreadDpiAwarenessContext();

        ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            ਵਾਪਸ "unaware";
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            ਵਾਪਸ "system";
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE)) {
            ਵਾਪਸ "permonitor";
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2)) {
            ਵਾਪਸ "permonitorv2";
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            ਵਾਪਸ "unaware_gdiscaled";
        }
    }

    ਵਾਪਸ "";
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    ਜੇ (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor_V2(_this);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_ਪ੍ਰਤੀ_Monitor(_this);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ਸਥਿਰ bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    HRESULT hr;

    hr = WIN_CoInitialize();
    ਜੇ (SUCCEEDED(hr)) {
        ਅੰਕੜੇ->coinitialized = true;

#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(ਨਿਰਾ);
        ਜੇ (SUCCEEDED(hr)) {
            ਅੰਕੜੇ->oleinitialized = true;
        } ਨਹੀਂਤਾਂ {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)hr);
        }
#ਜੇ_ਅੰਤ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } ਨਹੀਂਤਾਂ {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)hr);
    }

    WIN_InitDPIAwareness(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#ਜੇ_ਅੰਤ

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_ਨਿਵੇਸ਼(_this);
    }

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

        SDL_zero(ਬਹੁਲਕ);
        D3D12_XBOX_GetResolution(&ਬਹੁਲਕ.w, &ਬਹੁਲਕ.h);
        ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;
        ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ);
    }
#ਨਹੀਂਤਾਂ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (!WIN_InitModes(_this)) {
        ਵਾਪਸ false;
    }

    _this->ਅੰਦਰੂਨੀ->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#ਜੇ_ਅੰਤ

    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_ਸੁਨੇਹਾ_Loop, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_ਖਿੜਕੀ_ਚੌਖਟਾ_USABLE_WHILE_CURSOR_HIDDEN, Update_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden, ਨਿਰਾ);

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਅੰਕੜੇ->_SDL_WAKEUP = ਰਜਿਸਟਰ_ਖਿੜਕੀ_ਸੁਨੇਹਾ_A("_SDL_WAKEUP");
    ਅੰਕੜੇ->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? ਰਜਿਸਟਰ_ਖਿੜਕੀ_ਸੁਨੇਹਾ_A("TaskbarButtonCreated") : 0;
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_ਸੁਨੇਹਾ_Loop, ਨਿਰਾ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ਨਿਰਾ);
    SDL_RemoveHintCallback(SDL_HINT_ਖਿੜਕੀ_ਚੌਖਟਾ_USABLE_WHILE_CURSOR_HIDDEN, Update_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden, ਨਿਰਾ);

    WIN_Quit_Raw_ਨਿਵੇਸ਼(_this);
    WIN_Quit_Game_ਨਿਵੇਸ਼(_this);

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    ਜੇ (ਅੰਕੜੇ->taskbar_list) {
        ਅੰਕੜੇ->taskbar_list->lpVtbl->Release(ਅੰਕੜੇ->taskbar_list);
        ਅੰਕੜੇ->taskbar_list = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->oleinitialized) {
        OleUninitialize();
        ਅੰਕੜੇ->oleinitialized = false;
    }
#ਜੇ_ਅੰਤ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    ਜੇ (ਅੰਕੜੇ->coinitialized) {
        WIN_CoUninitialize();
        ਅੰਕੜੇ->coinitialized = false;
    }
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D_DEBUG_INFO
#ਅਨ੍ਤਰ੍ਭਾਵ <d3d9.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ D3D_DEBUG_INFO
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D_SDK_ਸੰਸਕਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D_SDK_ਸੰਸਕਰਣ (32 | 0x80000000)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D9b_SDK_ਸੰਸਕਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D9b_SDK_ਸੰਸਕਰਣ (31 | 0x80000000)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ //
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D_SDK_ਸੰਸਕਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D_SDK_ਸੰਸਕਰਣ 32
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D9b_SDK_ਸੰਸਕਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D9b_SDK_ਸੰਸਕਰਣ 31
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

bool D3_D_ਲੱਦੋ_DLL(ਖਾਲੀ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_ਲੱਦੋ_Object("D3D9.DLL");
    ਜੇ (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        ਜੇ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_ਲੱਦੋ_Function(*pD3DDLL, "Direct3DCreate9Ex");
            ਜੇ (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_ਸੰਸਕਰਣ, &pDirect3D9ExInterface);
                ਜੇ (SUCCEEDED(hr)) {
                    ਅਚਲ GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (ਖਾਲੀ **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    ਜੇ (SUCCEEDED(hr)) {
                        ਵਾਪਸ true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_ਲੱਦੋ_Function(*pD3DDLL, "Direct3DCreate9");
        ਜੇ (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_ਸੰਸਕਰਣ);
            ਜੇ (*pDirect3D9Interface) {
                ਵਾਪਸ true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = ਨਿਰਾ;
    }
    *pDirect3D9Interface = ਨਿਰਾ;
    ਵਾਪਸ false;
}

ਪੂਰਨ SDL_Get_Direct3_D9_Adapter_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID)
{
    ਖਾਲੀ *pD3DDLL;
    IDirect3D9 *pD3D;
    ਜੇ (!D3_D_ਲੱਦੋ_DLL(&pD3DDLL, &pD3D)) {
        SDL_ਸੈੱਟ_Error("Unable to create Direct3D interface");
        ਵਾਪਸ -1;
    } ਨਹੀਂਤਾਂ {
        SDL_Display_ਅੰਕੜੇ *p_ਅੰਕੜੇ = SDL_Get_Display_Driver_ਅੰਕੜੇ(displayID);
        ਪੂਰਨ adapter_ਸੂਚਕਾਂਕ = D3DADAPTER_DEFAULT;

        ਜੇ (!p_ਅੰਕੜੇ) {
            SDL_ਸੈੱਟ_Error("Invalid display index");
            adapter_ਸੂਚਕਾਂਕ = -1; // make sure we return something invalid
        } ਨਹੀਂਤਾਂ {
            ਅੱਖਰ *displayName = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(p_ਅੰਕੜੇ->DeviceName);
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਗਿਣਤੀ_2 = IDirect3_D9_Get_Adapter_ਗਿਣਤੀ(pD3D);
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
            ਲਈ (i = 0; i < ਗਿਣਤੀ_2; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                ਜੇ (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_ਸੂਚਕਾਂਕ = i;
                    ਰੋਕੋ;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        ਵਾਪਸ adapter_ਸੂਚਕਾਂਕ;
    }
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ਪੂਰਨ *adapter_ਸੂਚਕਾਂਕ, ਪੂਰਨ *output_ਸੂਚਕਾਂਕ)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    ਜੇ (adapter_ਸੂਚਕਾਂਕ) {
        *adapter_ਸੂਚਕਾਂਕ = -1;
    }
    ਜੇ (output_ਸੂਚਕਾਂਕ) {
        *output_ਸੂਚਕਾਂਕ = -1;
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#ਨਹੀਂਤਾਂ
    ਅਚਲ SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *videodata = videodevice ? videodevice->ਅੰਦਰੂਨੀ : ਨਿਰਾ;
    SDL_Display_ਅੰਕੜੇ *p_ਅੰਕੜੇ = SDL_Get_Display_Driver_ਅੰਕੜੇ(displayID);
    ਪੂਰਨ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_ਸੂਚਕਾਂਕ) {
        ਵਾਪਸ SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_ਸੂਚਕਾਂਕ) {
        ਵਾਪਸ SDL_InvalidParamError("outputIndex");
    }

    *adapter_ਸੂਚਕਾਂਕ = -1;
    *output_ਸੂਚਕਾਂਕ = -1;

    ਜੇ (!p_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid display index");
    }

    ਜੇ (!videodata || !videodata->pDXGIFactory) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    ਜਦੋਂ (*adapter_ਸੂਚਕਾਂਕ == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ਜਦੋਂ (*adapter_ਸੂਚਕਾਂਕ == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ਜੇ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ਜੇ (SDL_wcscmp(outputDesc.DeviceName, p_ਅੰਕੜੇ->DeviceName) == 0) {
                    *adapter_ਸੂਚਕਾਂਕ = nAdapter;
                    *output_ਸੂਚਕਾਂਕ = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    ਜੇ (*adapter_ਸੂਚਕਾਂਕ == -1) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find matching adapter");
    }
    ਵਾਪਸ true;
#ਜੇ_ਅੰਤ
}

SDL_SystemTheme WIN_GetSystemTheme(ਖਾਲੀ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_ਕੁੰਜੀ;
    DWORD dwType = REG_DWORD;
    DWORD ਮੁੱਲ = ~0U;
    DWORD ਲੰਮਾਈ = ਆਕਾਰ(ਮੁੱਲ);

    // Technically this isn't the system theme, but it's the preference for applications
    ਜੇ (Reg_Open_ਕੁੰਜੀ_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, ਕੁੰਜੀ_READ, &h_ਕੁੰਜੀ) == ERROR_SUCCESS) {
        ਜੇ (Reg_Query_ਮੁੱਲ_Ex_W(h_ਕੁੰਜੀ, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&ਮੁੱਲ, &ਲੰਮਾਈ) == ERROR_SUCCESS) {
            ਜੇ (ਮੁੱਲ == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_ਕੁੰਜੀ(h_ਕੁੰਜੀ);
    }
    ਵਾਪਸ theme;
}

bool WIN_Is_ਪ੍ਰਤੀ_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->AreDpiAwarenessContextsEqual && ਅੰਕੜੇ->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        ਵਾਪਸ ਅੰਕੜੇ->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2, ਅੰਕੜੇ->GetThreadDpiAwarenessContext());
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ false;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
