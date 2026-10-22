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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#ifdef SDL_VIDEO_VULKAN
#അന്തര്ഭാവ "../SDL_vulkan_internal.h"
#endif
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../SDL_hints_c.h"
#അന്തര്ഭാവ "../../core/windows/SDL_hid.h"

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "SDL_windowsframebuffer.h"
#അന്തര്ഭാവ "SDL_windowsmessagebox.h"
#അന്തര്ഭാവ "SDL_windowsrawinput.h"
#അന്തര്ഭാവ "SDL_windowsvulkan.h"

#എങ്കിൽ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#അന്തര്ഭാവ <shobjidl.h>

#ifndef __ITaskbarList3_FWD_DEFINED__
തരനിർവചനം ഘടന ITaskbarList3 ITaskbarList3;
#endif

#ifndef __ITaskbarList3_INTERFACE_DEFINED__
തരനിർവചനം എണ്ണൽ TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_NORMAL = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

തരനിർവചനം എണ്ണൽ THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

തരനിർവചനം എണ്ണൽ THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#എങ്കിൽ defined(_MSC_VER)
#pragma warning(disable: 4103)
#endif
#pragma pack(തള്ളുക, 8)
തരനിർവചനം ഘടന THUMBBUTTON
{
    THUMBBUTTONMASK dwMask;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

തരനിർവചനം ഘടന THUMBBUTTON *LPTHUMBBUTTON;
#pragma pack(എടുക്കുക)

#ifndef HIMAGELIST
ഘടന _IMAGELIST;
തരനിർവചനം ഘടന _IMAGELIST *HIMAGELIST;
#endif

തരനിർവചനം ഘടന ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, ശൂന്യം **ppvObject);
    ULONG (__stdcall *AddRef)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *AddTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *SetActiveAlt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *MarkFullscreenWindow)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *Set_Progress_മൂല്യം)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal);
    HRESULT (__stdcall *SetProgressState)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *RegisterTab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *SetTabOrder)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_തിരുകുക_Before);
    HRESULT (__stdcall *SetTabActive)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *ThumbBarAddButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarSetImageList)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *SetOverlayIcon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *SetThumbnailTooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *SetThumbnailClip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

ഘടന ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#endif // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#endif

#ifdef SDL_GDK_TEXTINPUT
#അന്തര്ഭാവ "../gdk/SDL_gdktextinput.h"
#endif

// #define HIGHDPI_DEBUG

// Initialization/Query functions
സ്ഥിതം bool WIN_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_WindowsEnableMessageLoop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_WindowFrameUsableWhileCursorHidden = true;

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsRawKeyboard(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_മൂല്യം, false);
    WIN_SetRawKeyboardEnabled(_this, enabled);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsRawKeyboardNoHotkeys(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_മൂല്യം, false);
    WIN_SetRawKeyboardFlag_NoHotkeys(_this, enabled);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsRawKeyboardInputsink(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_മൂല്യം, false);
    WIN_SetRawKeyboardFlag_Inputsink(_this, enabled);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsRawMouseNoLegacy(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_മൂല്യം, false);
    WIN_SetRawMouseFlag_NoLegacy(_this, enabled);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsEnableMessageLoop(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    g_WindowsEnableMessageLoop = SDL_GetStringBoolean(new_മൂല്യം, true);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowsEnableMenuMnemonics(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_മൂല്യം, false);
}

സ്ഥിതം ശൂന്യം SDLCALL UpdateWindowFrameUsableWhileCursorHidden(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    g_WindowFrameUsableWhileCursorHidden = SDL_GetStringBoolean(new_മൂല്യം, true);
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
സ്ഥിതം bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD result;
    എങ്കിൽ (_this->suspend_screensaver) {
        result = SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } അല്ലെങ്കിൽ {
        result = SetThreadExecutionState(ES_CONTINUOUS);
    }
    എങ്കിൽ (result == 0) {
        SDL_SetError("SetThreadExecutionState() failed");
        തിരികെ false;
    }
    തിരികെ true;
}
#endif

#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
ബാഹ്യ ശൂന്യം D3D12_XBOX_GetResolution(Uint32 *width, Uint32 *height);
#endif

// Windows driver bootstrap functions

സ്ഥിതം ശൂന്യം WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

    SDL_UnregisterApp();
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (data->userDLL) {
        SDL_UnloadObject(data->userDLL);
    }
    എങ്കിൽ (data->shcoreDLL) {
        SDL_UnloadObject(data->shcoreDLL);
    }
    എങ്കിൽ (data->dwmapiDLL) {
        SDL_UnloadObject(data->dwmapiDLL);
    }
#endif
#ifdef HAVE_DXGI_H
    എങ്കിൽ (data->pDXGIFactory) {
        IDXGIFactory_Release(data->pDXGIFactory);
    }
    എങ്കിൽ (data->dxgiDLL) {
        SDL_UnloadObject(data->dxgiDLL);
    }
#endif
    SDL_free(device->internal->rawinput);
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *WIN_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    SDL_RegisterApp(ശൂന്യ, 0, ശൂന്യ);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (device) {
        data = (SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    } അല്ലെങ്കിൽ {
        data = ശൂന്യ;
    }
    എങ്കിൽ (!data) {
        SDL_UnregisterApp();
        SDL_free(device);
        തിരികെ ശൂന്യ;
    }
    device->internal = data;
    device->system_theme = WIN_GetSystemTheme();

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    data->userDLL = SDL_LoadObject("USER32.DLL");
    എങ്കിൽ (data->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->Close_Touch_നിവേശം_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_LoadFunction(data->userDLL, "CloseTouchInputHandle");
        data->Get_Touch_നിവേശം_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, പൂർണ്ണസംഖ്യ)) SDL_LoadFunction(data->userDLL, "GetTouchInputInfo");
        data->RegisterTouchWindow = (BOOL (WINAPI *)(HWND, ULONG))SDL_LoadFunction(data->userDLL, "RegisterTouchWindow");
        data->SetProcessDPIAware = (BOOL (WINAPI *)(ശൂന്യം))SDL_LoadFunction(data->userDLL, "SetProcessDPIAware");
        data->SetProcessDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "SetProcessDpiAwarenessContext");
        data->SetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "SetThreadDpiAwarenessContext");
        data->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(ശൂന്യം))SDL_LoadFunction(data->userDLL, "GetThreadDpiAwarenessContext");
        data->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "GetAwarenessFromDpiAwarenessContext");
        data->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_LoadFunction(data->userDLL, "EnableNonClientDpiScaling");
        data->AdjustWindowRectExForDpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_LoadFunction(data->userDLL, "AdjustWindowRectExForDpi");
        data->GetDpiForWindow = (UINT (WINAPI *)(HWND))SDL_LoadFunction(data->userDLL, "GetDpiForWindow");
        data->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "AreDpiAwarenessContextsEqual");
        data->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(data->userDLL, "IsValidDpiAwarenessContext");
        data->GetDisplayConfigBufferSizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_LoadFunction(data->userDLL, "GetDisplayConfigBufferSizes");
        data->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_PATH_INFO*,UINT32 *,DISPLAYCONFIG_MODE_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_LoadFunction(data->userDLL, "QueryDisplayConfig");
        data->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_HEADER*))SDL_LoadFunction(data->userDLL, "DisplayConfigGetDeviceInfo");
        data->GetPointerType = (BOOL (WINAPI *)(UINT32, POINTER_നിവേശം_TYPE *))SDL_LoadFunction(data->userDLL, "GetPointerType");
        data->GetPointerPenInfo = (BOOL (WINAPI *)(UINT32, POINTER_PEN_INFO *))SDL_LoadFunction(data->userDLL, "GetPointerPenInfo");
        data->GetPointerDeviceRects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_LoadFunction(data->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } അല്ലെങ്കിൽ {
        SDL_ClearError();
    }

    data->shcoreDLL = SDL_LoadObject("SHCORE.DLL");
    എങ്കിൽ (data->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_LoadFunction(data->shcoreDLL, "GetDpiForMonitor");
        data->SetProcessDpiAwareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_LoadFunction(data->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } അല്ലെങ്കിൽ {
        SDL_ClearError();
    }

    data->dwmapiDLL = SDL_LoadObject("DWMAPI.DLL");
    എങ്കിൽ (data->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        data->DwmFlush = (HRESULT (WINAPI *)(ശൂന്യം))SDL_LoadFunction(data->dwmapiDLL, "DwmFlush");
        data->DwmEnableBlurBehindWindow = (HRESULT (WINAPI *)(HWND hwnd, സ്ഥിരം DWM_BLURBEHIND *pBlurBehind))SDL_LoadFunction(data->dwmapiDLL, "DwmEnableBlurBehindWindow");
        data->DwmSetWindowAttribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_LoadFunction(data->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } അല്ലെങ്കിൽ {
        SDL_ClearError();
    }
#endif // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_DXGI_H
    data->dxgiDLL = SDL_LoadObject("DXGI.DLL");
    എങ്കിൽ (data->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        തരനിർവചനം HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, ശൂന്യം **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_LoadFunction(data->dxgiDLL, "CreateDXGIFactory");
        എങ്കിൽ (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (ശൂന്യം **)&data->pDXGIFactory);
        }
    }
#endif

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->SetDisplayMode = WIN_SetDisplayMode;
#endif
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
    device->Set_Window_Always_On_മുകൾ = WIN_Set_Window_Always_On_മുകൾ;
    device->SetWindowFullscreen = WIN_SetWindowFullscreen;
    device->SetWindowParent = WIN_SetWindowParent;
    device->SetWindowModal = WIN_SetWindowModal;
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->GetWindowICCProfile = WIN_GetWindowICCProfile;
    device->SetWindowMouseRect = WIN_SetWindowMouseRect;
    device->SetWindowMouseGrab = WIN_SetWindowMouseGrab;
    device->SetWindowKeyboardGrab = WIN_SetWindowKeyboardGrab;
#endif
    device->DestroyWindow = WIN_DestroyWindow;
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
    device->GL_GetEGLSurface = ശൂന്യ;
#endif
#ifdef SDL_VIDEO_OPENGL_EGL
#ifdef SDL_VIDEO_OPENGL_WGL
    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
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

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Start_Text_നിവേശം = WIN_Start_Text_നിവേശം;
    device->Stop_Text_നിവേശം = WIN_Stop_Text_നിവേശം;
    device->Update_Text_നിവേശം_Area = WIN_Update_Text_നിവേശം_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->SetClipboardData = WIN_SetClipboardData;
    device->GetClipboardData = WIN_GetClipboardData;
    device->HasClipboardData = WIN_HasClipboardData;
#endif

#ifdef SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->Start_Text_നിവേശം = GDK_Start_Text_നിവേശം;
    device->Stop_Text_നിവേശം = GDK_Stop_Text_നിവേശം;
    device->Update_Text_നിവേശം_Area = GDK_Update_Text_നിവേശം_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#endif

    device->സ്വതന്ത്രം = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    തിരികെ device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_ShowMessageBox,
    #അല്ലെങ്കിൽ
    ശൂന്യ,
    #endif
    false
};

സ്ഥിതം BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->SetProcessDpiAwarenessContext) {
        data->dpi_unaware_context_declared = true;
        തിരികെ data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
    } അല്ലെങ്കിൽ എങ്കിൽ (data->SetProcessDpiAwareness) {
        // Windows 8.1
        തിരികെ SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_DPI_UNAWARE));
    }
#endif
    തിരികെ FALSE;
}

സ്ഥിതം BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        തിരികെ data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } അല്ലെങ്കിൽ എങ്കിൽ (data->SetProcessDpiAwareness) {
        // Windows 8.1
        തിരികെ SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE));
    } അല്ലെങ്കിൽ എങ്കിൽ (data->SetProcessDPIAware) {
        // Windows Vista
        തിരികെ data->SetProcessDPIAware();
    }
#endif
    തിരികെ FALSE;
}

സ്ഥിതം BOOL WIN_DeclareDPIAwarePerMonitor(SDL_VideoDevice *_this)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        തിരികെ data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
    } അല്ലെങ്കിൽ എങ്കിൽ (data->SetProcessDpiAwareness) {
        // Windows 8.1
        തിരികെ SUCCEEDED(data->SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE));
    } അല്ലെങ്കിൽ {
        // Older OS: fall back to system DPI aware
        തിരികെ WIN_DeclareDPIAwareSystem(_this);
    }
#അല്ലെങ്കിൽ
    തിരികെ FALSE;
#endif
}

സ്ഥിതം BOOL WIN_DeclareDPIAwarePerMonitorV2(SDL_VideoDevice *_this)
{
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    തിരികെ FALSE;
#അല്ലെങ്കിൽ
    SDL_VideoData *data = _this->internal;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    എങ്കിൽ (data->SetProcessDpiAwarenessContext) {
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
        എങ്കിൽ (data->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            തിരികെ TRUE;
        } അല്ലെങ്കിൽ {
            തിരികെ WIN_DeclareDPIAwarePerMonitor(_this);
        }
    } അല്ലെങ്കിൽ {
        // Older OS: fall back to per-monitor (or system)
        തിരികെ WIN_DeclareDPIAwarePerMonitor(_this);
    }
#endif
}

#ifdef HIGHDPI_DEBUG
സ്ഥിതം സ്ഥിരം അക്ഷരം *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->GetThreadDpiAwarenessContext && data->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = data->GetThreadDpiAwarenessContext();

        എങ്കിൽ (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            തിരികെ "unaware";
        } അല്ലെങ്കിൽ എങ്കിൽ (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            തിരികെ "system";
        } അല്ലെങ്കിൽ എങ്കിൽ (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE)) {
            തിരികെ "permonitor";
        } അല്ലെങ്കിൽ എങ്കിൽ (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            തിരികെ "permonitorv2";
        } അല്ലെങ്കിൽ എങ്കിൽ (data->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            തിരികെ "unaware_gdiscaled";
        }
    }

    തിരികെ "";
}
#endif

സ്ഥിതം ശൂന്യം WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    എങ്കിൽ (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_DeclareDPIAwarePerMonitorV2(_this);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_DeclareDPIAwarePerMonitor(_this);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

സ്ഥിതം bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    HRESULT hr;

    hr = WIN_CoInitialize();
    എങ്കിൽ (SUCCEEDED(hr)) {
        data->coinitialized = true;

#എങ്കിൽ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(ശൂന്യ);
        എങ്കിൽ (SUCCEEDED(hr)) {
            data->oleinitialized = true;
        } അല്ലെങ്കിൽ {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (unsigned പൂർണ്ണസംഖ്യ)hr);
        }
#endif // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } അല്ലെങ്കിൽ {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (unsigned പൂർണ്ണസംഖ്യ)hr);
    }

    WIN_InitDPIAwareness(_this);

#ifdef HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#endif

    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_നിവേശം(_this);
    }

#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_DisplayMode mode;

        SDL_zero(mode);
        D3D12_XBOX_GetResolution(&mode.w, &mode.h);
        mode.refresh_rate = 60.0f;
        mode.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_AddBasicVideoDisplay(&mode);
    }
#അല്ലെങ്കിൽ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (!WIN_InitModes(_this)) {
        തിരികെ false;
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
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, ശൂന്യ);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ശൂന്യ);
    SDL_AddHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, ശൂന്യ);

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    data->_SDL_WAKEUP = RegisterWindowMessageA("_SDL_WAKEUP");
    data->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? RegisterWindowMessageA("TaskbarButtonCreated") : 0;
#endif

    തിരികെ true;
}

ശൂന്യം WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, ശൂന്യ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ശൂന്യ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, ശൂന്യ);

    WIN_Quit_Raw_നിവേശം(_this);
    WIN_Quit_Game_നിവേശം(_this);

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    എങ്കിൽ (data->taskbar_list) {
        data->taskbar_list->lpVtbl->Release(data->taskbar_list);
        data->taskbar_list = ശൂന്യ;
    }

    എങ്കിൽ (data->oleinitialized) {
        OleUninitialize();
        data->oleinitialized = false;
    }
#endif // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    എങ്കിൽ (data->coinitialized) {
        WIN_CoUninitialize();
        data->coinitialized = false;
    }
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#define D3D_DEBUG_INFO
#അന്തര്ഭാവ <d3d9.h>

#ifdef D3D_DEBUG_INFO
#ifndef D3D_SDK_VERSION
#define D3D_SDK_VERSION (32 | 0x80000000)
#endif
#ifndef D3D9b_SDK_VERSION
#define D3D9b_SDK_VERSION (31 | 0x80000000)
#endif
#അല്ലെങ്കിൽ //
#ifndef D3D_SDK_VERSION
#define D3D_SDK_VERSION 32
#endif
#ifndef D3D9b_SDK_VERSION
#define D3D9b_SDK_VERSION 31
#endif
#endif

bool D3D_LoadDLL(ശൂന്യം **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_LoadObject("D3D9.DLL");
    എങ്കിൽ (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        തരനിർവചനം IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        തരനിർവചനം HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9Ex");
            എങ്കിൽ (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3D_SDK_VERSION, &pDirect3D9ExInterface);
                എങ്കിൽ (SUCCEEDED(hr)) {
                    സ്ഥിരം GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (ശൂന്യം **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    എങ്കിൽ (SUCCEEDED(hr)) {
                        തിരികെ true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9");
        എങ്കിൽ (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3D_SDK_VERSION);
            എങ്കിൽ (*pDirect3D9Interface) {
                തിരികെ true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = ശൂന്യ;
    }
    *pDirect3D9Interface = ശൂന്യ;
    തിരികെ false;
}

പൂർണ്ണസംഖ്യ SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    ശൂന്യം *pD3DDLL;
    IDirect3D9 *pD3D;
    എങ്കിൽ (!D3D_LoadDLL(&pD3DDLL, &pD3D)) {
        SDL_SetError("Unable to create Direct3D interface");
        തിരികെ -1;
    } അല്ലെങ്കിൽ {
        SDL_DisplayData *pData = SDL_GetDisplayDriverData(displayID);
        പൂർണ്ണസംഖ്യ adapterIndex = D3DADAPTER_DEFAULT;

        എങ്കിൽ (!pData) {
            SDL_SetError("Invalid display index");
            adapterIndex = -1; // make sure we return something invalid
        } അല്ലെങ്കിൽ {
            അക്ഷരം *displayName = WIN_StringToUTF8W(pData->DeviceName);
            unsigned പൂർണ്ണസംഖ്യ എണ്ണം = IDirect3_D9_Get_Adapter_എണ്ണം(pD3D);
            unsigned പൂർണ്ണസംഖ്യ i;
            വേണ്ടി (i = 0; i < എണ്ണം; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                എങ്കിൽ (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapterIndex = i;
                    നിർത്തുക;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        തിരികെ adapterIndex;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, പൂർണ്ണസംഖ്യ *adapterIndex, പൂർണ്ണസംഖ്യ *outputIndex)
{
#ifndef HAVE_DXGI_H
    എങ്കിൽ (adapterIndex) {
        *adapterIndex = -1;
    }
    എങ്കിൽ (outputIndex) {
        *outputIndex = -1;
    }
    തിരികെ SDL_SetError("SDL was compiled without DXGI support due to missing dxgi.h header");
#അല്ലെങ്കിൽ
    സ്ഥിരം SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    സ്ഥിരം SDL_VideoData *videodata = videodevice ? videodevice->internal : ശൂന്യ;
    SDL_DisplayData *pData = SDL_GetDisplayDriverData(displayID);
    പൂർണ്ണസംഖ്യ nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapterIndex) {
        തിരികെ SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!outputIndex) {
        തിരികെ SDL_InvalidParamError("outputIndex");
    }

    *adapterIndex = -1;
    *outputIndex = -1;

    എങ്കിൽ (!pData) {
        തിരികെ SDL_SetError("Invalid display index");
    }

    എങ്കിൽ (!videodata || !videodata->pDXGIFactory) {
        തിരികെ SDL_SetError("Unable to create DXGI interface");
    }

    nAdapter = 0;
    ആകുമ്പോൾ (*adapterIndex == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        ആകുമ്പോൾ (*adapterIndex == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            എങ്കിൽ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                എങ്കിൽ (SDL_wcscmp(outputDesc.DeviceName, pData->DeviceName) == 0) {
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

    എങ്കിൽ (*adapterIndex == -1) {
        തിരികെ SDL_SetError("Couldn't find matching adapter");
    }
    തിരികെ true;
#endif
}

SDL_SystemTheme WIN_GetSystemTheme(ശൂന്യം)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_താക്കോൽ;
    DWORD dwType = REG_DWORD;
    DWORD മൂല്യം = ~0U;
    DWORD length = വലുപ്പം(മൂല്യം);

    // Technically this isn't the system theme, but it's the preference for applications
    എങ്കിൽ (Reg_Open_താക്കോൽ_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, താക്കോൽ_READ, &h_താക്കോൽ) == ERROR_SUCCESS) {
        എങ്കിൽ (Reg_Query_മൂല്യം_Ex_W(h_താക്കോൽ, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&മൂല്യം, &length) == ERROR_SUCCESS) {
            എങ്കിൽ (മൂല്യം == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_താക്കോൽ(h_താക്കോൽ);
    }
    തിരികെ theme;
}

bool WIN_IsPerMonitorV2DPIAware(SDL_VideoDevice *_this)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->AreDpiAwarenessContextsEqual && data->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        തിരികെ data->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2, data->GetThreadDpiAwarenessContext());
    }
#endif
    തിരികെ false;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
