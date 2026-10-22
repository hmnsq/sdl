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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS

#अगर_घोषित SDL_VIDEO_VULKAN
#समावेश "../SDL_vulkan_internal.h"
#पूर्ण_अगर
#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../SDL_hints_c.h"
#समावेश "../../core/windows/SDL_hid.h"

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowsframebuffer.h"
#समावेश "SDL_windowsmessagebox.h"
#समावेश "SDL_windowsrawinput.h"
#समावेश "SDL_windowsvulkan.h"

#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#समावेश <shobjidl.h>

#अगर_अघोषित __ITaskbarList3_FWD_DEFINED__
प्रकार काष्ठा ITaskbarList3 ITaskbarList3;
#पूर्ण_अगर

#अगर_अघोषित __ITaskbarList3_INTERFACE_DEFINED__
प्रकार क्रमागत TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_NORMAL = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

प्रकार क्रमागत THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

प्रकार क्रमागत THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#अगर defined(_MSC_VER)
#आशय warning(disable: 4103)
#पूर्ण_अगर
#आशय pack(धकेलो, 8)
प्रकार काष्ठा THUMBBUTTON
{
    THUMBBUTTONMASK dwMask;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

प्रकार काष्ठा THUMBBUTTON *LPTHUMBBUTTON;
#आशय pack(निकालो)

#अगर_अघोषित HIMAGELIST
काष्ठा _IMAGELIST;
प्रकार काष्ठा _IMAGELIST *HIMAGELIST;
#पूर्ण_अगर

प्रकार काष्ठा ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, व्योम **ppvObject);
    ULONG (__stdcall *AddRef)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *AddTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *SetActiveAlt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *MarkFullscreenWindow)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *Set_Progress_मूल्य)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_योग);
    HRESULT (__stdcall *SetProgressState)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *RegisterTab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *SetTabOrder)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_जोड़ो_Before);
    HRESULT (__stdcall *SetTabActive)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *ThumbBarAddButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarSetImageList)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *SetOverlayIcon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *SetThumbnailTooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *SetThumbnailClip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

काष्ठा ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#पूर्ण_अगर // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#पूर्ण_अगर

#अगर_घोषित SDL_GDK_TEXTINPUT
#समावेश "../gdk/SDL_gdktextinput.h"
#पूर्ण_अगर

// #define HIGHDPI_DEBUG

// Initialization/Query functions
अटल bool WIN_VideoInit(SDL_VideoDevice *_this);
अटल व्योम WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_WindowsEnableMessageLoop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_WindowFrameUsableWhileCursorHidden = true;

अटल व्योम SDLCALL UpdateWindowsRawKeyboard(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मूल्य, false);
    WIN_SetRawKeyboardEnabled(_this, enabled);
}

अटल व्योम SDLCALL UpdateWindowsRawKeyboardNoHotkeys(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मूल्य, false);
    WIN_SetRawKeyboardFlag_NoHotkeys(_this, enabled);
}

अटल व्योम SDLCALL UpdateWindowsRawKeyboardInputsink(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मूल्य, false);
    WIN_SetRawKeyboardFlag_Inputsink(_this, enabled);
}

अटल व्योम SDLCALL UpdateWindowsRawMouseNoLegacy(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मूल्य, false);
    WIN_SetRawMouseFlag_NoLegacy(_this, enabled);
}

अटल व्योम SDLCALL UpdateWindowsEnableMessageLoop(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    g_WindowsEnableMessageLoop = SDL_GetStringBoolean(new_मूल्य, true);
}

अटल व्योम SDLCALL UpdateWindowsEnableMenuMnemonics(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_मूल्य, false);
}

अटल व्योम SDLCALL UpdateWindowFrameUsableWhileCursorHidden(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    g_WindowFrameUsableWhileCursorHidden = SDL_GetStringBoolean(new_मूल्य, true);
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
अटल bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD परिणाम;
    अगर (_this->suspend_screensaver) {
        परिणाम = SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } अन्यथा {
        परिणाम = SetThreadExecutionState(ES_CONTINUOUS);
    }
    अगर (परिणाम == 0) {
        SDL_SetError("SetThreadExecutionState() failed");
        वापस false;
    }
    वापस true;
}
#पूर्ण_अगर

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
बाह्य व्योम D3D12_XBOX_GetResolution(Uint32 *width, Uint32 *height);
#पूर्ण_अगर

// Windows driver bootstrap functions

अटल व्योम WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;

    SDL_UnregisterApp();
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (तथ्य->userDLL) {
        SDL_UnloadObject(तथ्य->userDLL);
    }
    अगर (तथ्य->shcoreDLL) {
        SDL_UnloadObject(तथ्य->shcoreDLL);
    }
    अगर (तथ्य->dwmapiDLL) {
        SDL_UnloadObject(तथ्य->dwmapiDLL);
    }
#पूर्ण_अगर
#अगर_घोषित HAVE_DXGI_H
    अगर (तथ्य->pDXGIFactory) {
        IDXGIFactory_Release(तथ्य->pDXGIFactory);
    }
    अगर (तथ्य->dxgiDLL) {
        SDL_UnloadObject(तथ्य->dxgiDLL);
    }
#पूर्ण_अगर
    SDL_free(device->internal->rawinput);
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *WIN_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;

    SDL_RegisterApp(शून्य, 0, शून्य);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (device) {
        तथ्य = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    } अन्यथा {
        तथ्य = शून्य;
    }
    अगर (!तथ्य) {
        SDL_UnregisterApp();
        SDL_free(device);
        वापस शून्य;
    }
    device->internal = तथ्य;
    device->system_theme = WIN_GetSystemTheme();

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    तथ्य->userDLL = SDL_LoadObject("USER32.DLL");
    अगर (तथ्य->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        तथ्य->Close_Touch_निवेश_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_LoadFunction(तथ्य->userDLL, "CloseTouchInputHandle");
        तथ्य->Get_Touch_निवेश_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, पूर्णांक)) SDL_LoadFunction(तथ्य->userDLL, "GetTouchInputInfo");
        तथ्य->RegisterTouchWindow = (BOOL (WINAPI *)(HWND, ULONG))SDL_LoadFunction(तथ्य->userDLL, "RegisterTouchWindow");
        तथ्य->SetProcessDPIAware = (BOOL (WINAPI *)(व्योम))SDL_LoadFunction(तथ्य->userDLL, "SetProcessDPIAware");
        तथ्य->SetProcessDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(तथ्य->userDLL, "SetProcessDpiAwarenessContext");
        तथ्य->SetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(तथ्य->userDLL, "SetThreadDpiAwarenessContext");
        तथ्य->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(व्योम))SDL_LoadFunction(तथ्य->userDLL, "GetThreadDpiAwarenessContext");
        तथ्य->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(तथ्य->userDLL, "GetAwarenessFromDpiAwarenessContext");
        तथ्य->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_LoadFunction(तथ्य->userDLL, "EnableNonClientDpiScaling");
        तथ्य->AdjustWindowRectExForDpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_LoadFunction(तथ्य->userDLL, "AdjustWindowRectExForDpi");
        तथ्य->GetDpiForWindow = (UINT (WINAPI *)(HWND))SDL_LoadFunction(तथ्य->userDLL, "GetDpiForWindow");
        तथ्य->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_LoadFunction(तथ्य->userDLL, "AreDpiAwarenessContextsEqual");
        तथ्य->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_LoadFunction(तथ्य->userDLL, "IsValidDpiAwarenessContext");
        तथ्य->Get_Display_Config_बफर_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_LoadFunction(तथ्य->userDLL, "GetDisplayConfigBufferSizes");
        तथ्य->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_PATH_INFO*,UINT32 *,DISPLAYCONFIG_MODE_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_LoadFunction(तथ्य->userDLL, "QueryDisplayConfig");
        तथ्य->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_HEADER*))SDL_LoadFunction(तथ्य->userDLL, "DisplayConfigGetDeviceInfo");
        तथ्य->GetPointerType = (BOOL (WINAPI *)(UINT32, POINTER_निवेश_TYPE *))SDL_LoadFunction(तथ्य->userDLL, "GetPointerType");
        तथ्य->GetPointerPenInfo = (BOOL (WINAPI *)(UINT32, POINTER_PEN_INFO *))SDL_LoadFunction(तथ्य->userDLL, "GetPointerPenInfo");
        तथ्य->GetPointerDeviceRects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_LoadFunction(तथ्य->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }

    तथ्य->shcoreDLL = SDL_LoadObject("SHCORE.DLL");
    अगर (तथ्य->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        तथ्य->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_LoadFunction(तथ्य->shcoreDLL, "GetDpiForMonitor");
        तथ्य->SetProcessDpiAwareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_LoadFunction(तथ्य->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }

    तथ्य->dwmapiDLL = SDL_LoadObject("DWMAPI.DLL");
    अगर (तथ्य->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        तथ्य->DwmFlush = (HRESULT (WINAPI *)(व्योम))SDL_LoadFunction(तथ्य->dwmapiDLL, "DwmFlush");
        तथ्य->DwmEnableBlurBehindWindow = (HRESULT (WINAPI *)(HWND hwnd, स्थिर DWM_BLURBEHIND *pBlurBehind))SDL_LoadFunction(तथ्य->dwmapiDLL, "DwmEnableBlurBehindWindow");
        तथ्य->DwmSetWindowAttribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_LoadFunction(तथ्य->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }
#पूर्ण_अगर // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अगर_घोषित HAVE_DXGI_H
    तथ्य->dxgiDLL = SDL_LoadObject("DXGI.DLL");
    अगर (तथ्य->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        प्रकार HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, व्योम **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_LoadFunction(तथ्य->dxgiDLL, "CreateDXGIFactory");
        अगर (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (व्योम **)&तथ्य->pDXGIFactory);
        }
    }
#पूर्ण_अगर

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->SetDisplayMode = WIN_SetDisplayMode;
#पूर्ण_अगर
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#पूर्ण_अगर

    device->CreateSDLWindow = WIN_CreateWindow;
    device->SetWindowTitle = WIN_SetWindowTitle;
    device->SetWindowIcon = WIN_SetWindowIcon;
    device->SetWindowPosition = WIN_SetWindowPosition;
    device->Set_Window_आकार = WIN_Set_Window_आकार;
    device->Get_Window_Borders_आकार = WIN_Get_Window_Borders_आकार;
    device->Get_Window_आकार_In_Pixels = WIN_Get_Window_आकार_In_Pixels;
    device->SetWindowOpacity = WIN_SetWindowOpacity;
    device->ShowWindow = WIN_ShowWindow;
    device->HideWindow = WIN_HideWindow;
    device->RaiseWindow = WIN_RaiseWindow;
    device->MaximizeWindow = WIN_MaximizeWindow;
    device->MinimizeWindow = WIN_MinimizeWindow;
    device->RestoreWindow = WIN_RestoreWindow;
    device->SetWindowBordered = WIN_SetWindowBordered;
    device->SetWindowResizable = WIN_SetWindowResizable;
    device->Set_Window_Always_On_शीर्ष = WIN_Set_Window_Always_On_शीर्ष;
    device->SetWindowFullscreen = WIN_SetWindowFullscreen;
    device->SetWindowParent = WIN_SetWindowParent;
    device->SetWindowModal = WIN_SetWindowModal;
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->GetWindowICCProfile = WIN_GetWindowICCProfile;
    device->SetWindowMouseRect = WIN_SetWindowMouseRect;
    device->SetWindowMouseGrab = WIN_SetWindowMouseGrab;
    device->SetWindowKeyboardGrab = WIN_SetWindowKeyboardGrab;
#पूर्ण_अगर
    device->DestroyWindow = WIN_DestroyWindow;
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_OPENGL_WGL
    device->GL_LoadLibrary = WIN_GL_LoadLibrary;
    device->GL_GetProcAddress = WIN_GL_GetProcAddress;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
    device->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
    device->GL_SwapWindow = WIN_GL_SwapWindow;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = शून्य;
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#अगर_घोषित SDL_VIDEO_OPENGL_WGL
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#पूर्ण_अगर
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
#अगर_घोषित SDL_VIDEO_OPENGL_WGL
    }
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#पूर्ण_अगर

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Start_Text_निवेश = WIN_Start_Text_निवेश;
    device->Stop_Text_निवेश = WIN_Stop_Text_निवेश;
    device->Update_Text_निवेश_Area = WIN_Update_Text_निवेश_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->Set_Clipboard_तथ्य = WIN_Set_Clipboard_तथ्य;
    device->Get_Clipboard_तथ्य = WIN_Get_Clipboard_तथ्य;
    device->Has_Clipboard_तथ्य = WIN_Has_Clipboard_तथ्य;
#पूर्ण_अगर

#अगर_घोषित SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->Start_Text_निवेश = GDK_Start_Text_निवेश;
    device->Stop_Text_निवेश = GDK_Stop_Text_निवेश;
    device->Update_Text_निवेश_Area = GDK_Update_Text_निवेश_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#पूर्ण_अगर

    device->मुक्त = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    वापस device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_ShowMessageBox,
    #अन्यथा
    शून्य,
    #पूर्ण_अगर
    false
};

अटल BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->SetProcessDpiAwarenessContext) {
        तथ्य->dpi_unaware_context_declared = true;
        वापस तथ्य->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
    } अन्यथा अगर (तथ्य->SetProcessDpiAwareness) {
        // Windows 8.1
        वापस SUCCEEDED(तथ्य->SetProcessDpiAwareness(PROCESS_DPI_UNAWARE));
    }
#पूर्ण_अगर
    वापस FALSE;
}

अटल BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        वापस तथ्य->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } अन्यथा अगर (तथ्य->SetProcessDpiAwareness) {
        // Windows 8.1
        वापस SUCCEEDED(तथ्य->SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE));
    } अन्यथा अगर (तथ्य->SetProcessDPIAware) {
        // Windows Vista
        वापस तथ्य->SetProcessDPIAware();
    }
#पूर्ण_अगर
    वापस FALSE;
}

अटल BOOL WIN_DeclareDPIAwarePerMonitor(SDL_VideoDevice *_this)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->SetProcessDpiAwarenessContext) {
        // Windows 10, version 1607
        वापस तथ्य->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
    } अन्यथा अगर (तथ्य->SetProcessDpiAwareness) {
        // Windows 8.1
        वापस SUCCEEDED(तथ्य->SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE));
    } अन्यथा {
        // Older OS: fall back to system DPI aware
        वापस WIN_DeclareDPIAwareSystem(_this);
    }
#अन्यथा
    वापस FALSE;
#पूर्ण_अगर
}

अटल BOOL WIN_DeclareDPIAwarePerMonitorV2(SDL_VideoDevice *_this)
{
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    वापस FALSE;
#अन्यथा
    SDL_Video_तथ्य *तथ्य = _this->internal;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    अगर (तथ्य->SetProcessDpiAwarenessContext) {
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
        अगर (तथ्य->SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            वापस TRUE;
        } अन्यथा {
            वापस WIN_DeclareDPIAwarePerMonitor(_this);
        }
    } अन्यथा {
        // Older OS: fall back to per-monitor (or system)
        वापस WIN_DeclareDPIAwarePerMonitor(_this);
    }
#पूर्ण_अगर
}

#अगर_घोषित HIGHDPI_DEBUG
अटल स्थिर अक्षर *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->GetThreadDpiAwarenessContext && तथ्य->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = तथ्य->GetThreadDpiAwarenessContext();

        अगर (तथ्य->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            वापस "unaware";
        } अन्यथा अगर (तथ्य->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            वापस "system";
        } अन्यथा अगर (तथ्य->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE)) {
            वापस "permonitor";
        } अन्यथा अगर (तथ्य->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            वापस "permonitorv2";
        } अन्यथा अगर (तथ्य->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            वापस "unaware_gdiscaled";
        }
    }

    वापस "";
}
#पूर्ण_अगर

अटल व्योम WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    स्थिर अक्षर *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    अगर (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_DeclareDPIAwarePerMonitorV2(_this);
    } अन्यथा अगर (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_DeclareDPIAwarePerMonitor(_this);
    } अन्यथा अगर (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } अन्यथा अगर (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

अटल bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    HRESULT hr;

    hr = WIN_CoInitialize();
    अगर (SUCCEEDED(hr)) {
        तथ्य->coinitialized = true;

#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(शून्य);
        अगर (SUCCEEDED(hr)) {
            तथ्य->oleinitialized = true;
        } अन्यथा {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (अचिन्हित पूर्णांक)hr);
        }
#पूर्ण_अगर // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } अन्यथा {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (अचिन्हित पूर्णांक)hr);
    }

    WIN_InitDPIAwareness(_this);

#अगर_घोषित HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#पूर्ण_अगर

    अगर (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_निवेश(_this);
    }

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_DisplayMode mode;

        SDL_zero(mode);
        D3D12_XBOX_GetResolution(&mode.w, &mode.h);
        mode.refresh_rate = 60.0f;
        mode.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_AddBasicVideoDisplay(&mode);
    }
#अन्यथा // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (!WIN_InitModes(_this)) {
        वापस false;
    }

    _this->internal->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#पूर्ण_अगर

    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, शून्य);
    SDL_AddHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, शून्य);
    SDL_AddHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, शून्य);

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    तथ्य->_SDL_WAKEUP = RegisterWindowMessageA("_SDL_WAKEUP");
    तथ्य->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? RegisterWindowMessageA("TaskbarButtonCreated") : 0;
#पूर्ण_अगर

    वापस true;
}

व्योम WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, UpdateWindowsEnableMessageLoop, शून्य);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, शून्य);
    SDL_RemoveHintCallback(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, UpdateWindowFrameUsableWhileCursorHidden, शून्य);

    WIN_Quit_Raw_निवेश(_this);
    WIN_Quit_Game_निवेश(_this);

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    अगर (तथ्य->taskbar_list) {
        तथ्य->taskbar_list->lpVtbl->Release(तथ्य->taskbar_list);
        तथ्य->taskbar_list = शून्य;
    }

    अगर (तथ्य->oleinitialized) {
        OleUninitialize();
        तथ्य->oleinitialized = false;
    }
#पूर्ण_अगर // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    अगर (तथ्य->coinitialized) {
        WIN_CoUninitialize();
        तथ्य->coinitialized = false;
    }
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#घोषणा D3D_DEBUG_INFO
#समावेश <d3d9.h>

#अगर_घोषित D3D_DEBUG_INFO
#अगर_अघोषित D3D_SDK_VERSION
#घोषणा D3D_SDK_VERSION (32 | 0x80000000)
#पूर्ण_अगर
#अगर_अघोषित D3D9b_SDK_VERSION
#घोषणा D3D9b_SDK_VERSION (31 | 0x80000000)
#पूर्ण_अगर
#अन्यथा //
#अगर_अघोषित D3D_SDK_VERSION
#घोषणा D3D_SDK_VERSION 32
#पूर्ण_अगर
#अगर_अघोषित D3D9b_SDK_VERSION
#घोषणा D3D9b_SDK_VERSION 31
#पूर्ण_अगर
#पूर्ण_अगर

bool D3D_LoadDLL(व्योम **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_LoadObject("D3D9.DLL");
    अगर (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        प्रकार IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        प्रकार HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        अगर (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9Ex");
            अगर (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3D_SDK_VERSION, &pDirect3D9ExInterface);
                अगर (SUCCEEDED(hr)) {
                    स्थिर GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (व्योम **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    अगर (SUCCEEDED(hr)) {
                        वापस true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_LoadFunction(*pD3DDLL, "Direct3DCreate9");
        अगर (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3D_SDK_VERSION);
            अगर (*pDirect3D9Interface) {
                वापस true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = शून्य;
    }
    *pDirect3D9Interface = शून्य;
    वापस false;
}

पूर्णांक SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    व्योम *pD3DDLL;
    IDirect3D9 *pD3D;
    अगर (!D3D_LoadDLL(&pD3DDLL, &pD3D)) {
        SDL_SetError("Unable to create Direct3D interface");
        वापस -1;
    } अन्यथा {
        SDL_Display_तथ्य *p_तथ्य = SDL_Get_Display_Driver_तथ्य(displayID);
        पूर्णांक adapter_सूचकांक = D3DADAPTER_DEFAULT;

        अगर (!p_तथ्य) {
            SDL_SetError("Invalid display index");
            adapter_सूचकांक = -1; // make sure we return something invalid
        } अन्यथा {
            अक्षर *displayName = WIN_StringToUTF8W(p_तथ्य->DeviceName);
            अचिन्हित पूर्णांक गिनती = IDirect3_D9_Get_Adapter_गिनती(pD3D);
            अचिन्हित पूर्णांक i;
            क्रम (i = 0; i < गिनती; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                अगर (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_सूचकांक = i;
                    अवरोध;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        वापस adapter_सूचकांक;
    }
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णांक *adapter_सूचकांक, पूर्णांक *output_सूचकांक)
{
#अगर_अघोषित HAVE_DXGI_H
    अगर (adapter_सूचकांक) {
        *adapter_सूचकांक = -1;
    }
    अगर (output_सूचकांक) {
        *output_सूचकांक = -1;
    }
    वापस SDL_SetError("SDL was compiled without DXGI support due to missing dxgi.h header");
#अन्यथा
    स्थिर SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    स्थिर SDL_Video_तथ्य *videodata = videodevice ? videodevice->internal : शून्य;
    SDL_Display_तथ्य *p_तथ्य = SDL_Get_Display_Driver_तथ्य(displayID);
    पूर्णांक nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_सूचकांक) {
        वापस SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_सूचकांक) {
        वापस SDL_InvalidParamError("outputIndex");
    }

    *adapter_सूचकांक = -1;
    *output_सूचकांक = -1;

    अगर (!p_तथ्य) {
        वापस SDL_SetError("Invalid display index");
    }

    अगर (!videodata || !videodata->pDXGIFactory) {
        वापस SDL_SetError("Unable to create DXGI interface");
    }

    nAdapter = 0;
    जबतक (*adapter_सूचकांक == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        जबतक (*adapter_सूचकांक == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            अगर (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                अगर (SDL_wcscmp(outputDesc.DeviceName, p_तथ्य->DeviceName) == 0) {
                    *adapter_सूचकांक = nAdapter;
                    *output_सूचकांक = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    अगर (*adapter_सूचकांक == -1) {
        वापस SDL_SetError("Couldn't find matching adapter");
    }
    वापस true;
#पूर्ण_अगर
}

SDL_SystemTheme WIN_GetSystemTheme(व्योम)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_कुंजी;
    DWORD dwType = REG_DWORD;
    DWORD मूल्य = ~0U;
    DWORD लंबाई = माप(मूल्य);

    // Technically this isn't the system theme, but it's the preference for applications
    अगर (Reg_Open_कुंजी_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, कुंजी_READ, &h_कुंजी) == ERROR_SUCCESS) {
        अगर (Reg_Query_मूल्य_Ex_W(h_कुंजी, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&मूल्य, &लंबाई) == ERROR_SUCCESS) {
            अगर (मूल्य == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_कुंजी(h_कुंजी);
    }
    वापस theme;
}

bool WIN_IsPerMonitorV2DPIAware(SDL_VideoDevice *_this)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->AreDpiAwarenessContextsEqual && तथ्य->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        वापस तथ्य->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2, तथ्य->GetThreadDpiAwarenessContext());
    }
#पूर्ण_अगर
    वापस false;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
