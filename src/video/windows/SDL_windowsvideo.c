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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#ifdef SDL_VIDEO_VULKAN
#شامل "../SDL_vulkan_internal.h"
#endif
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../SDL_hints_c.h"
#شامل "../../core/windows/SDL_hid.h"

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsframebuffer.h"
#شامل "SDL_windowsmessagebox.h"
#شامل "SDL_windowsrawinput.h"
#شامل "SDL_windowsvulkan.h"

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#شامل <shobjidl.h>

#ifndef __ITaskbarList3_FWD_DEFINED__
تعریفنوع ساختار ITaskbarList3 ITaskbarList3;
#endif

#ifndef __ITaskbarList3_INTERFACE_DEFINED__
تعریفنوع شمارش TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_NORMAL = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

تعریفنوع شمارش THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

تعریفنوع شمارش THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#اگر defined(_MSC_VER)
#pragma warning(disable: 4103)
#endif
#pragma pack(افزودن, 8)
تعریفنوع ساختار THUMBBUTTON
{
    THUMBBUTTONMASK dwMask;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

تعریفنوع ساختار THUMBBUTTON *LPTHUMBBUTTON;
#pragma pack(برداشت)

#ifndef HIMAGELIST
ساختار _IMAGELIST;
تعریفنوع ساختار _IMAGELIST *HIMAGELIST;
#endif

تعریفنوع ساختار ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, تهی **ppvObject);
    ULONG (__stdcall *AddRef)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *AddTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *SetActiveAlt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *MarkFullscreenWindow)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *Set_Progress_مقدار)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal);
    HRESULT (__stdcall *SetProgressState)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *RegisterTab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *SetTabOrder)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_درج_Before);
    HRESULT (__stdcall *SetTabActive)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *ThumbBarAddButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarSetImageList)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *SetOverlayIcon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *SetThumbnailTooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *SetThumbnailClip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

ساختار ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#endif // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#endif

#ifdef SDL_GDK_TEXTINPUT
#شامل "../gdk/SDL_gdktextinput.h"
#endif

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ایستا bool WIN_VideoInit(SDL_VideoDevice *_this);
ایستا تهی WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_WindowsEnableMessageLoop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_WindowFrameUsableWhileCursorHidden = true;

ایستا تهی SDLCALL UpdateWindowsRawKeyboard(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_SetRawKeyboardEnabled(_this, enabled);
}

ایستا تهی SDLCALL UpdateWindowsRawKeyboardNoHotkeys(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_SetRawKeyboardFlag_NoHotkeys(_this, enabled);
}

ایستا تهی SDLCALL UpdateWindowsRawKeyboardInputsink(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_SetRawKeyboardFlag_Inputsink(_this, enabled);
}

ایستا تهی SDLCALL UpdateWindowsRawMouseNoLegacy(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_SetRawMouseFlag_NoLegacy(_this, enabled);
}

ایستا تهی SDLCALL UpdateWindowsEnableMessageLoop(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    g_WindowsEnableMessageLoop = SDL_GetStringBoolean(new_مقدار, true);
}

ایستا تهی SDLCALL UpdateWindowsEnableMenuMnemonics(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_مقدار, false);
}

ایستا تهی SDLCALL UpdateWindowFrameUsableWhileCursorHidden(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    g_WindowFrameUsableWhileCursorHidden = SDL_GetStringBoolean(new_مقدار, true);
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ایستا bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD result;
    اگر (_this->suspend_screensaver) {
        result = SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } وگرنه {
        result = SetThreadExecutionState(ES_CONTINUOUS);
    }
    اگر (result == 0) {
        SDL_SetError("SetThreadExecutionState() failed");
        بازگشت false;
    }
    بازگشت true;
}
#endif

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
بیرونی تهی D3D12_XBOX_GetResolution(Uint32 *width, Uint32 *height);
#endif

// Windows driver bootstrap functions

ایستا تهی WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

    SDL_UnregisterApp();
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (data->userDLL) {
        SDL_UnloadObject(data->userDLL);
    }
    اگر (data->shcoreDLL) {
        SDL_UnloadObject(data->shcoreDLL);
    }
    اگر (data->dwmapiDLL) {
        SDL_UnloadObject(data->dwmapiDLL);
    }
#endif
#ifdef HAVE_DXGI_H
    اگر (data->pDXGIFactory) {
        IDXGIFactory_Release(data->pDXGIFactory);
    }
    اگر (data->dxgiDLL) {
        SDL_UnloadObject(data->dxgiDLL);
    }
#endif
    SDL_free(device->internal->rawinput);
    SDL_free(device->internal);
    SDL_free(device);
}

ایستا SDL_VideoDevice *WIN_CreateDevice(تهی)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    SDL_RegisterApp(پوچ, 0, پوچ);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, اندازه(SDL_VideoDevice));
    اگر (device) {
        data = (SDL_VideoData *)SDL_calloc(1, اندازه(SDL_VideoData));
    } وگرنه {
        data = پوچ;
    }
    اگر (!data) {
        SDL_UnregisterApp();
        SDL_free(device);
        بازگشت پوچ;
    }
    device->internal = data;
    device->system_theme = WIN_GetSystemTheme();

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    data->userDLL = SDL_LoadObject("USER32.DLL");
    اگر (data->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->Close_Touch_درون_داد_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_LoadFunction(data->userDLL, "CloseTouchInputHandle");
        data->Get_Touch_درون_داد_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحیح)) SDL_LoadFunction(data->userDLL, "GetTouchInputInfo");
        data->RegisterTouchWindow = (BOOL (WINAPI *)(HWND, ULONG))SDL_LoadFunction(data->userDLL, "RegisterTouchWindow");
        data->SetProcessDPIAware = (BOOL (WINAPI *)(تهی))SDL_LoadFunction(data->userDLL, "SetProcessDPIAware");
        data->SetProcessDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "SetProcessDpiAwarenessContext");
        data->SetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "SetThreadDpiAwarenessContext");
        data->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(تهی))SDL_LoadFunction(data->userDLL, "GetThreadDpiAwarenessContext");
        data->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "GetAwarenessFromDpiAwarenessContext");
        data->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_LoadFunction(data->userDLL, "EnableNonClientDpiScaling");
        data->AdjustWindowRectExForDpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_LoadFunction(data->userDLL, "AdjustWindowRectExForDpi");
        data->GetDpiForWindow = (UINT (WINAPI *)(HWND))SDL_LoadFunction(data->userDLL, "GetDpiForWindow");
        data->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "AreDpiAwarenessContextsEqual");
        data->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "IsValidDpiAwarenessContext");
        data->GetDisplayConfigBufferSizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_LoadFunction(data->userDLL, "GetDisplayConfigBufferSizes");
        data->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_PATH_INFO*,UINT32 *,DISPLAYCONFIG_MODE_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_LoadFunction(data->userDLL, "QueryDisplayConfig");
        data->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_HEADER*))SDL_LoadFunction(data->userDLL, "DisplayConfigGetDeviceInfo");
        data->GetPointerType = (BOOL (WINAPI *)(UINT32, POINTER_درون_داد_TYPE *))SDL_LoadFunction(data->userDLL, "GetPointerType");
        data->GetPointerPenInfo = (BOOL (WINAPI *)(UINT32, POINTER_PEN_INFO *))SDL_LoadFunction(data->userDLL, "GetPointerPenInfo");
        data->GetPointerDeviceRects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_LoadFunction(data->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } وگرنه {
        SDL_ClearError();
    }

    data->shcoreDLL = SDL_LoadObject("SHCORE.DLL");
    اگر (data->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_LoadFunction(data->shcoreDLL, "GetDpiForMonitor");
        data->SetProcessDpiAwareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_LoadFunction(data->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } وگرنه {
        SDL_ClearError();
    }

    data->dwmapiDLL = SDL_LoadObject("DWMAPI.DLL");
    اگر (data->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->DwmFlush = (HRESULT (WINAPI *)(تهی))SDL_LoadFunction(data->dwmapiDLL, "DwmFlush");
        data->DwmEnableBlurBehindWindow = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_LoadFunction(data->dwmapiDLL, "DwmEnableBlurBehindWindow");
        data->DwmSetWindowAttribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_LoadFunction(data->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } وگرنه {
        SDL_ClearError();
    }
#endif // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_DXGI_H
    data->dxgiDLL = SDL_LoadObject("DXGI.DLL");
    اگر (data->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعریفنوع HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, تهی **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_LoadFunction(data->dxgiDLL, "CreateDXGIFactory");
        اگر (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (تهی **)&data->pDXGIFactory);
        }
    }
#endif

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->SetDisplayMode = WIN_SetDisplayMode;
#endif
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#endif

    device->CreateSDLWindow = WIN_CreateWindow;
    device->SetWindowTitle = WIN_SetWindowTitle;
    device->SetWindowIcon = WIN_SetWindowIcon;
    device->SetWindowPosition = WIN_SetWindowPosition;
    device->SetWindowSize = WIN_SetWindowSize;
    device->GetWindowBordersSize = WIN_GetWindowBordersSize;
    device->GetWindowSizeInPixels = WIN_GetWindowSizeInPixels;
    device->SetWindowOpacity = WIN_SetWindowOpacity;
    device->ShowWindow = WIN_ShowWindow;
    device->HideWindow = WIN_HideWindow;
    device->RaiseWindow = WIN_RaiseWindow;
    device->MaximizeWindow = WIN_MaximizeWindow;
    device->MinimizeWindow = WIN_MinimizeWindow;
    device->RestoreWindow = WIN_RestoreWindow;
    device->SetWindowBordered = WIN_SetWindowBordered;
    device->SetWindowResizable = WIN_SetWindowResizable;
    device->Set_Window_Always_On_بالاترین = WIN_Set_Window_Always_On_بالاترین;
    device->SetWindowFullscreen = WIN_SetWindowFullscreen;
    device->SetWindowParent = WIN_SetWindowParent;
    device->SetWindowModal = WIN_SetWindowModal;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->GetWindowICCProfile = WIN_GetWindowICCProfile;
    device->SetWindowMouseRect = WIN_SetWindowMouseRect;
    device->SetWindowMouseGrab = WIN_SetWindowMouseGrab;
    device->SetWindowKeyboardGrab = WIN_SetWindowKeyboardGrab;
#endif
    device->DestroyWindow = WIN_DestroyWindow;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->CreateWindowFramebuffer = WIN_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = WIN_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = WIN_DestroyWindowFramebuffer;
    device->OnWindowEnter = WIN_OnWindowEnter;
    device->SetWindowHitTest = WIN_SetWindowHitTest;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->FlashWindow = WIN_FlashWindow;
    device->ApplyWindowProgress = WIN_ApplyWindowProgress;
    device->ShowWindowSystemMenu = WIN_ShowWindowSystemMenu;
    device->SetWindowFocusable = WIN_SetWindowFocusable;
    device->UpdateWindowShape = WIN_UpdateWindowShape;
#endif

#ifdef SDL_VIDEO_OPENGL_WGL
    device->GL_LoadLibrary = WIN_GL_LoadLibrary;
    device->GL_GetProcAddress = WIN_GL_GetProcAddress;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
    device->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
    device->GL_SwapWindow = WIN_GL_SwapWindow;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = پوچ;
#endif
#ifdef SDL_VIDEO_OPENGL_EGL
#ifdef SDL_VIDEO_OPENGL_WGL
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#endif
        // Use EGL based functions
        device->GL_LoadLibrary = WIN_GLES_LoadLibrary;
        device->GL_GetProcAddress = WIN_GLES_GetProcAddress;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_SetSwapInterval = WIN_GLES_SetSwapInterval;
        device->GL_GetSwapInterval = WIN_GLES_GetSwapInterval;
        device->GL_SwapWindow = WIN_GLES_SwapWindow;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#ifdef SDL_VIDEO_OPENGL_WGL
    }
#endif
#endif
#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#endif

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Start_Text_درون_داد = WIN_Start_Text_درون_داد;
    device->Stop_Text_درون_داد = WIN_Stop_Text_درون_داد;
    device->Update_Text_درون_داد_Area = WIN_Update_Text_درون_داد_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->SetClipboardData = WIN_SetClipboardData;
    device->GetClipboardData = WIN_GetClipboardData;
    device->HasClipboardData = WIN_HasClipboardData;
#endif

#ifdef SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->Start_Text_درون_داد = GDK_Start_Text_درون_داد;
    device->Stop_Text_درون_داد = GDK_Stop_Text_درون_داد;
    device->Update_Text_درون_داد_Area = GDK_Update_Text_درون_داد_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#endif

    device->آزاد = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    بازگشت device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_ShowMessageBox,
    #وگرنه
    پوچ,
    #endif
    false
};

ایستا BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    اگر (data->SetProcessDpiAwarenessContext) {
        data->dpi_unaware_context_declared = true;
        بازگشت data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
    } وگرنه اگر (data->SetProcessDpiAwareness) {
        // Windows 8.1
        بازگشت SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_DPI_UNAWARE));
    }
#endif
    بازگشت FALSE;
}

ایستا BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    اگر (data->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        بازگشت data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } وگرنه اگر (data->SetProcessDpiAwareness) {
        // Windows 8.1
        بازگشت SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE));
    } وگرنه اگر (data->SetProcessDPIAware) {
        // Windows Vista
        بازگشت data->SetProcessDPIAware();
    }
#endif
    بازگشت FALSE;
}

ایستا BOOL WIN_DeclareDPIAwarePerMonitor(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    اگر (data->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        بازگشت data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
    } وگرنه اگر (data->SetProcessDpiAwareness) {
        // Windows 8.1
        بازگشت SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE));
    } وگرنه {
        // Older OS: fall back to system DPI aware
        بازگشت WIN_DeclareDPIAwareSystem(_this);
    }
#وگرنه
    بازگشت FALSE;
#endif
}

ایستا BOOL WIN_DeclareDPIAwarePerMonitorV2(SDL_VideoDevice *_this)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    بازگشت FALSE;
#وگرنه
    SDL_VideoData *data = _this->internal;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    اگر (data->SetProcessDpiAwarenessContext) {
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
        اگر (data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            بازگشت TRUE;
        } وگرنه {
            بازگشت WIN_DeclareDPIAwarePerMonitor(_this);
        }
    } وگرنه {
        // Older OS: fall back to per-monitor (or system)
        بازگشت WIN_DeclareDPIAwarePerMonitor(_this);
    }
#endif
}

#ifdef HIGHDPI_DEBUG
ایستا ثابت نویسه *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    اگر (data->GetThreadDpiAwarenessContext && data->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = data->GetThreadDpiAwarenessContext();

        اگر (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            بازگشت "unaware";
        } وگرنه اگر (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            بازگشت "system";
        } وگرنه اگر (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE)) {
            بازگشت "permonitor";
        } وگرنه اگر (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            بازگشت "permonitorv2";
        } وگرنه اگر (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            بازگشت "unaware_gdiscaled";
        }
    }

    بازگشت "";
}
#endif

ایستا تهی WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ثابت نویسه *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    اگر (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_DeclareDPIAwarePerMonitorV2(_this);
    } وگرنه اگر (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_DeclareDPIAwarePerMonitor(_this);
    } وگرنه اگر (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } وگرنه اگر (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ایستا bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    HRESULT hr;

    hr = WIN_CoInitialize();
    اگر (SUCCEEDED(hr)) {
        data->coinitialized = true;

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(پوچ);
        اگر (SUCCEEDED(hr)) {
            data->oleinitialized = true;
        } وگرنه {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (unsigned صحیح)hr);
        }
#endif // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } وگرنه {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (unsigned صحیح)hr);
    }

    WIN_InitDPIAwareness(_this);

#ifdef HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#endif

    اگر (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_درون_داد(_this);
    }

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_DisplayMode mode;

        SDL_zero(mode);
        D3D12_XBOX_GetResolution(&mode.w, &mode.h);
        mode.refresh_rate = 60.0f;
        mode.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_AddBasicVideoDisplay(&mode);
    }
#وگرنه // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!WIN_InitModes(_this)) {
        بازگشت false;
    }

    _this->internal->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#endif

    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, پوچ);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, پوچ);
    SDL_AddHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, پوچ);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    data->_SDL_WAKEUP = RegisterWindowMessageA("_SDL_WAKEUP");
    data->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? RegisterWindowMessageA("TaskbarButtonCreated") : 0;
#endif

    بازگشت true;
}

تهی WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, پوچ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, پوچ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, پوچ);

    WIN_Quit_Raw_درون_داد(_this);
    WIN_Quit_Game_درون_داد(_this);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    اگر (data->taskbar_list) {
        data->taskbar_list->lpVtbl->Release(data->taskbar_list);
        data->taskbar_list = پوچ;
    }

    اگر (data->oleinitialized) {
        OleUninitialize();
        data->oleinitialized = false;
    }
#endif // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    اگر (data->coinitialized) {
        WIN_CoUninitialize();
        data->coinitialized = false;
    }
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#define D3D_DEBUG_INFO
#شامل <d3d9.h>

#ifdef D3D_DEBUG_INFO
#ifndef D3D_SDK_VERSION
#define D3D_SDK_VERSION (32 | 0x80000000)
#endif
#ifndef D3D9b_SDK_VERSION
#define D3D9b_SDK_VERSION (31 | 0x80000000)
#endif
#وگرنه //
#ifndef D3D_SDK_VERSION
#define D3D_SDK_VERSION 32
#endif
#ifndef D3D9b_SDK_VERSION
#define D3D9b_SDK_VERSION 31
#endif
#endif

bool D3D_LoadDLL(تهی **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_LoadObject("D3D9.DLL");
    اگر (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعریفنوع IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        تعریفنوع HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        اگر (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9Ex");
            اگر (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3D_SDK_VERSION, &pDirect3D9ExInterface);
                اگر (SUCCEEDED(hr)) {
                    ثابت GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (تهی **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    اگر (SUCCEEDED(hr)) {
                        بازگشت true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9");
        اگر (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3D_SDK_VERSION);
            اگر (*pDirect3D9Interface) {
                بازگشت true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = پوچ;
    }
    *pDirect3D9Interface = پوچ;
    بازگشت false;
}

صحیح SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    تهی *pD3DDLL;
    IDirect3D9 *pD3D;
    اگر (!D3D_LoadDLL(&pD3DDLL, &pD3D)) {
        SDL_SetError("Unable to create Direct3D interface");
        بازگشت -1;
    } وگرنه {
        SDL_DisplayData *pData = SDL_GetDisplayDriverData(displayID);
        صحیح adapterIndex = D3DADAPTER_DEFAULT;

        اگر (!pData) {
            SDL_SetError("Invalid display index");
            adapterIndex = -1; // make sure we return something invalid
        } وگرنه {
            نویسه *displayName = WIN_StringToUTF8W(pData->DeviceName);
            unsigned صحیح شمار = IDirect3_D9_Get_Adapter_شمار(pD3D);
            unsigned صحیح i;
            برای (i = 0; i < شمار; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                اگر (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapterIndex = i;
                    بشکن;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        بازگشت adapterIndex;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحیح *adapterIndex, صحیح *outputIndex)
{
#ifndef HAVE_DXGI_H
    اگر (adapterIndex) {
        *adapterIndex = -1;
    }
    اگر (outputIndex) {
        *outputIndex = -1;
    }
    بازگشت SDL_SetError("SDL was compiled without DXGI support due to missing dxgi.h header");
#وگرنه
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_VideoData *videodata = videodevice ? videodevice->internal : پوچ;
    SDL_DisplayData *pData = SDL_GetDisplayDriverData(displayID);
    صحیح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapterIndex) {
        بازگشت SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!outputIndex) {
        بازگشت SDL_InvalidParamError("outputIndex");
    }

    *adapterIndex = -1;
    *outputIndex = -1;

    اگر (!pData) {
        بازگشت SDL_SetError("Invalid display index");
    }

    اگر (!videodata || !videodata->pDXGIFactory) {
        بازگشت SDL_SetError("Unable to create DXGI interface");
    }

    nAdapter = 0;
    وقتی (*adapterIndex == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        وقتی (*adapterIndex == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            اگر (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                اگر (SDL_wcscmp(outputDesc.DeviceName, pData->DeviceName) == 0) {
                    *adapterIndex = nAdapter;
                    *outputIndex = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    اگر (*adapterIndex == -1) {
        بازگشت SDL_SetError("Couldn't find matching adapter");
    }
    بازگشت true;
#endif
}

SDL_SystemTheme WIN_GetSystemTheme(تهی)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_کلید;
    DWORD dwType = REG_DWORD;
    DWORD مقدار = ~0U;
    DWORD length = اندازه(مقدار);

    // Technically this isn't the system theme, but it's the preference for applications
    اگر (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, کلید_READ, &h_کلید) == ERROR_SUCCESS) {
        اگر (Reg_Query_مقدار_Ex_W(h_کلید, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&مقدار, &length) == ERROR_SUCCESS) {
            اگر (مقدار == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_کلید(h_کلید);
    }
    بازگشت theme;
}

bool WIN_IsPerMonitorV2DPIAware(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    اگر (data->AreDpiAwarenessContextsEqual && data->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        بازگشت data->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2, data->GetThreadDpiAwarenessContext());
    }
#endif
    بازگشت false;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
