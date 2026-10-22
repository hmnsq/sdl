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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
#ضمن "../SDL_vulkan_internal.h"
#جيڪڏهن_پورو
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../SDL_hints_c.h"
#ضمن "../../core/windows/SDL_hid.h"

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsframebuffer.h"
#ضمن "SDL_windowsmessagebox.h"
#ضمن "SDL_windowsrawinput.h"
#ضمن "SDL_windowsvulkan.h"

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>

#جيڪڏهن_وصف_نه_ٿيل __ITaskbarList3_FWD_DEFINED__
تعريفنوع بنية ITaskbarList3 ITaskbarList3;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل __ITaskbarList3_INTERFACE_DEFINED__
تعريفنوع تعداد TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_عام = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

تعريفنوع تعداد THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

تعريفنوع تعداد THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#إذا defined(_MSC_VER)
#هدايت warning(disable: 4103)
#جيڪڏهن_پورو
#هدايت pack(ڌڪو, 8)
تعريفنوع بنية THUMBBUTTON
{
    THUMBBUTTONMASK dw_نقاب;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

تعريفنوع بنية THUMBBUTTON *LPTHUMBBUTTON;
#هدايت pack(ڪڍو)

#جيڪڏهن_وصف_نه_ٿيل HIMAGELIST
بنية _IMAGELIST;
تعريفنوع بنية _IMAGELIST *HIMAGELIST;
#جيڪڏهن_پورو

تعريفنوع بنية ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, فراغ **ppvObject);
    ULONG (__stdcall *جوڙيو_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *جوڙيو_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *سيٽ_سرگرم_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_دري)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *سيٽ_ترقي_قدر)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_ڪل);
    HRESULT (__stdcall *سيٽ_ترقي_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *رجسٽر_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *سيٽ_Tab_ترتيب)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_وجهو_Before);
    HRESULT (__stdcall *سيٽ_Tab_سرگرم)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_جوڙيو_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_سيٽ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *سيٽ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *سيٽ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *سيٽ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

بنية ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#جيڪڏهن_پورو // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_GDK_TEXTINPUT
#ضمن "../gdk/SDL_gdktextinput.h"
#جيڪڏهن_پورو

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ساكن bool WIN_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_پيغام_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_دري_چوکٺو_Usable_While_Cursor_Hidden = true;

ساكن فراغ SDLCALL UpdateWindowsRawKeyboard(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سيٽ_Raw_Keyboard_Enabled(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سيٽ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardInputsink(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سيٽ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawMouseNoLegacy(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سيٽ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ساكن فراغ SDLCALL Update_Windows_Enable_پيغام_Loop(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_Windows_Enable_پيغام_Loop = SDL_GetStringBoolean(new_قدر, true);
}

ساكن فراغ SDLCALL UpdateWindowsEnableMenuMnemonics(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_قدر, false);
}

ساكن فراغ SDLCALL Update_دري_چوکٺو_Usable_While_Cursor_Hidden(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_دري_چوکٺو_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_قدر, true);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD نتيجو;
    إذا (_this->suspend_screensaver) {
        نتيجو = سيٽ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } وإلا {
        نتيجو = سيٽ_Thread_Execution_State(ES_CONTINUOUS);
    }
    إذا (نتيجو == 0) {
        SDL_سيٽ_Error("SetThreadExecutionState() failed");
        أرجع false;
    }
    أرجع true;
}
#جيڪڏهن_پورو

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
خارجي فراغ D3D12_XBOX_GetResolution(Uint32 *ويڪر, Uint32 *اوچائي);
#جيڪڏهن_پورو

// Windows driver bootstrap functions

ساكن فراغ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->اندروني;

    SDL_UnregisterApp();
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (معلومات->userDLL) {
        SDL_UnloadObject(معلومات->userDLL);
    }
    إذا (معلومات->shcoreDLL) {
        SDL_UnloadObject(معلومات->shcoreDLL);
    }
    إذا (معلومات->dwmapiDLL) {
        SDL_UnloadObject(معلومات->dwmapiDLL);
    }
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    إذا (معلومات->pDXGIFactory) {
        IDXGIFactory_Release(معلومات->pDXGIFactory);
    }
    إذا (معلومات->dxgiDLL) {
        SDL_UnloadObject(معلومات->dxgiDLL);
    }
#جيڪڏهن_پورو
    SDL_free(device->اندروني->rawinput);
    SDL_free(device->اندروني);
    SDL_free(device);
}

ساكن SDL_VideoDevice *WIN_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;

    SDL_رجسٽر_App(عدم, 0, عدم);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        معلومات = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    } وإلا {
        معلومات = عدم;
    }
    إذا (!معلومات) {
        SDL_UnregisterApp();
        SDL_free(device);
        أرجع عدم;
    }
    device->اندروني = معلومات;
    device->system_theme = WIN_GetSystemTheme();

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->userDLL = SDL_ڀريو_Object("USER32.DLL");
    إذا (معلومات->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->Close_Touch_داخلا_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_ڀريو_Function(معلومات->userDLL, "CloseTouchInputHandle");
        معلومات->Get_Touch_داخلا_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح)) SDL_ڀريو_Function(معلومات->userDLL, "GetTouchInputInfo");
        معلومات->رجسٽر_Touch_دري = (BOOL (WINAPI *)(HWND, ULONG))SDL_ڀريو_Function(معلومات->userDLL, "RegisterTouchWindow");
        معلومات->سيٽ_Process_DPIAware = (BOOL (WINAPI *)(فراغ))SDL_ڀريو_Function(معلومات->userDLL, "SetProcessDPIAware");
        معلومات->سيٽ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ڀريو_Function(معلومات->userDLL, "SetProcessDpiAwarenessContext");
        معلومات->سيٽ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ڀريو_Function(معلومات->userDLL, "SetThreadDpiAwarenessContext");
        معلومات->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(فراغ))SDL_ڀريو_Function(معلومات->userDLL, "GetThreadDpiAwarenessContext");
        معلومات->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ڀريو_Function(معلومات->userDLL, "GetAwarenessFromDpiAwarenessContext");
        معلومات->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_ڀريو_Function(معلومات->userDLL, "EnableNonClientDpiScaling");
        معلومات->Adjust_دري_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_ڀريو_Function(معلومات->userDLL, "AdjustWindowRectExForDpi");
        معلومات->Get_Dpi_For_دري = (UINT (WINAPI *)(HWND))SDL_ڀريو_Function(معلومات->userDLL, "GetDpiForWindow");
        معلومات->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_ڀريو_Function(معلومات->userDLL, "AreDpiAwarenessContextsEqual");
        معلومات->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ڀريو_Function(معلومات->userDLL, "IsValidDpiAwarenessContext");
        معلومات->Get_Display_Config_بفر_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_ڀريو_Function(معلومات->userDLL, "GetDisplayConfigBufferSizes");
        معلومات->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_رستو_INFO*,UINT32 *,DISPLAYCONFIG_گهڻائي_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_ڀريو_Function(معلومات->userDLL, "QueryDisplayConfig");
        معلومات->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_سرو*))SDL_ڀريو_Function(معلومات->userDLL, "DisplayConfigGetDeviceInfo");
        معلومات->Get_اشارو_Type = (BOOL (WINAPI *)(UINT32, اشارو_داخلا_TYPE *))SDL_ڀريو_Function(معلومات->userDLL, "GetPointerType");
        معلومات->Get_اشارو_Pen_Info = (BOOL (WINAPI *)(UINT32, اشارو_PEN_INFO *))SDL_ڀريو_Function(معلومات->userDLL, "GetPointerPenInfo");
        معلومات->Get_اشارو_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_ڀريو_Function(معلومات->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    معلومات->shcoreDLL = SDL_ڀريو_Object("SHCORE.DLL");
    إذا (معلومات->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_ڀريو_Function(معلومات->shcoreDLL, "GetDpiForMonitor");
        معلومات->سيٽ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_ڀريو_Function(معلومات->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    معلومات->dwmapiDLL = SDL_ڀريو_Object("DWMAPI.DLL");
    إذا (معلومات->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->DwmFlush = (HRESULT (WINAPI *)(فراغ))SDL_ڀريو_Function(معلومات->dwmapiDLL, "DwmFlush");
        معلومات->Dwm_Enable_Blur_Behind_دري = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_ڀريو_Function(معلومات->dwmapiDLL, "DwmEnableBlurBehindWindow");
        معلومات->Dwm_سيٽ_دري_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_ڀريو_Function(معلومات->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }
#جيڪڏهن_پورو // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    معلومات->dxgiDLL = SDL_ڀريو_Object("DXGI.DLL");
    إذا (معلومات->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, فراغ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_ڀريو_Function(معلومات->dxgiDLL, "CreateDXGIFactory");
        إذا (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (فراغ **)&معلومات->pDXGIFactory);
        }
    }
#جيڪڏهن_پورو

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->سيٽ_Display_گهڻائي = WIN_سيٽ_Display_گهڻائي;
#جيڪڏهن_پورو
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#جيڪڏهن_پورو

    device->CreateSDLWindow = WIN_Create_دري;
    device->سيٽ_دري_Title = WIN_سيٽ_دري_Title;
    device->سيٽ_دري_Icon = WIN_سيٽ_دري_Icon;
    device->سيٽ_دري_Position = WIN_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = WIN_سيٽ_دري_سائيز;
    device->Get_دري_Borders_سائيز = WIN_Get_دري_Borders_سائيز;
    device->Get_دري_سائيز_اندريون_Pixels = WIN_Get_دري_سائيز_اندريون_Pixels;
    device->سيٽ_دري_Opacity = WIN_سيٽ_دري_Opacity;
    device->Show_دري = WIN_Show_دري;
    device->Hide_دري = WIN_Hide_دري;
    device->Raise_دري = WIN_Raise_دري;
    device->Maximize_دري = WIN_Maximize_دري;
    device->Minimize_دري = WIN_Minimize_دري;
    device->Restore_دري = WIN_Restore_دري;
    device->سيٽ_دري_Bordered = WIN_سيٽ_دري_Bordered;
    device->سيٽ_دري_Resizable = WIN_سيٽ_دري_Resizable;
    device->سيٽ_دري_Always_On_چوٽي = WIN_سيٽ_دري_Always_On_چوٽي;
    device->سيٽ_دري_Fullscreen = WIN_سيٽ_دري_Fullscreen;
    device->سيٽ_دري_والد = WIN_سيٽ_دري_والد;
    device->سيٽ_دري_Modal = WIN_سيٽ_دري_Modal;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_دري_ICCProfile = WIN_Get_دري_ICCProfile;
    device->سيٽ_دري_Mouse_Rect = WIN_سيٽ_دري_Mouse_Rect;
    device->سيٽ_دري_Mouse_Grab = WIN_سيٽ_دري_Mouse_Grab;
    device->سيٽ_دري_Keyboard_Grab = WIN_سيٽ_دري_Keyboard_Grab;
#جيڪڏهن_پورو
    device->Destroy_دري = WIN_Destroy_دري;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_دري_Framebuffer = WIN_Create_دري_Framebuffer;
    device->Update_دري_Framebuffer = WIN_Update_دري_Framebuffer;
    device->Destroy_دري_Framebuffer = WIN_Destroy_دري_Framebuffer;
    device->On_دري_Enter = WIN_On_دري_Enter;
    device->سيٽ_دري_ڪاميابي_Test = WIN_سيٽ_دري_ڪاميابي_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_دري = WIN_Flash_دري;
    device->Apply_دري_ترقي = WIN_Apply_دري_ترقي;
    device->Show_دري_System_Menu = WIN_Show_دري_System_Menu;
    device->سيٽ_دري_Focusable = WIN_سيٽ_دري_Focusable;
    device->Update_دري_Shape = WIN_Update_دري_Shape;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
    device->GL_ڀريو_Library = WIN_GL_ڀريو_Library;
    device->GL_Get_Proc_پتو = WIN_GL_Get_Proc_پتو;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = WIN_GL_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = WIN_GL_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = WIN_GL_مٽا_سٽا_دري;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#جيڪڏهن_پورو
        // Use EGL based functions
        device->GL_ڀريو_Library = WIN_GLES_ڀريو_Library;
        device->GL_Get_Proc_پتو = WIN_GLES_Get_Proc_پتو;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_سيٽ_مٽا_سٽا_Interval = WIN_GLES_سيٽ_مٽا_سٽا_Interval;
        device->GL_Get_مٽا_سٽا_Interval = WIN_GLES_Get_مٽا_سٽا_Interval;
        device->GL_مٽا_سٽا_دري = WIN_GLES_مٽا_سٽا_دري;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
    }
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = WIN_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#جيڪڏهن_پورو

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->شروعات_متن_داخلا = WIN_شروعات_متن_داخلا;
    device->Stop_متن_داخلا = WIN_Stop_متن_داخلا;
    device->Update_متن_داخلا_Area = WIN_Update_متن_داخلا_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->سيٽ_Clipboard_معلومات = WIN_سيٽ_Clipboard_معلومات;
    device->Get_Clipboard_معلومات = WIN_Get_Clipboard_معلومات;
    device->Has_Clipboard_معلومات = WIN_Has_Clipboard_معلومات;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->شروعات_متن_داخلا = GDK_شروعات_متن_داخلا;
    device->Stop_متن_داخلا = GDK_Stop_متن_داخلا;
    device->Update_متن_داخلا_Area = GDK_Update_متن_داخلا_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#جيڪڏهن_پورو

    device->حرر = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_دري_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_پيغام_Box,
    #وإلا
    عدم,
    #جيڪڏهن_پورو
    false
};

ساكن BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->سيٽ_Process_Dpi_Awareness_Context) {
        معلومات->dpi_unaware_context_declared = true;
        أرجع معلومات->سيٽ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } وإلا إذا (معلومات->سيٽ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سيٽ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#جيڪڏهن_پورو
    أرجع FALSE;
}

ساكن BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->سيٽ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع معلومات->سيٽ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } وإلا إذا (معلومات->سيٽ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سيٽ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } وإلا إذا (معلومات->سيٽ_Process_DPIAware) {
        // Windows Vista
        أرجع معلومات->سيٽ_Process_DPIAware();
    }
#جيڪڏهن_پورو
    أرجع FALSE;
}

ساكن BOOL WIN_Declare_DPIAware_في_Monitor(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->سيٽ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع معلومات->سيٽ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE);
    } وإلا إذا (معلومات->سيٽ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سيٽ_Process_Dpi_Awareness(PROCESS_في_MONITOR_DPI_AWARE));
    } وإلا {
        // Older OS: fall back to system DPI aware
        أرجع WIN_DeclareDPIAwareSystem(_this);
    }
#وإلا
    أرجع FALSE;
#جيڪڏهن_پورو
}

ساكن BOOL WIN_Declare_DPIAware_في_Monitor_V2(SDL_VideoDevice *_this)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع FALSE;
#وإلا
    SDL_Video_معلومات *معلومات = _this->اندروني;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    إذا (معلومات->سيٽ_Process_Dpi_Awareness_Context) {
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
        إذا (معلومات->سيٽ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE_V2)) {
            أرجع TRUE;
        } وإلا {
            أرجع WIN_Declare_DPIAware_في_Monitor(_this);
        }
    } وإلا {
        // Older OS: fall back to per-monitor (or system)
        أرجع WIN_Declare_DPIAware_في_Monitor(_this);
    }
#جيڪڏهن_پورو
}

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
ساكن ثابت حرف *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->GetThreadDpiAwarenessContext && معلومات->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = معلومات->GetThreadDpiAwarenessContext();

        إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            أرجع "unaware";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            أرجع "system";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE)) {
            أرجع "permonitor";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE_V2)) {
            أرجع "permonitorv2";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            أرجع "unaware_gdiscaled";
        }
    }

    أرجع "";
}
#جيڪڏهن_پورو

ساكن فراغ WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ثابت حرف *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    إذا (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_في_Monitor_V2(_this);
    } وإلا إذا (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_في_Monitor(_this);
    } وإلا إذا (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } وإلا إذا (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ساكن bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    HRESULT hr;

    hr = WIN_CoInitialize();
    إذا (SUCCEEDED(hr)) {
        معلومات->coinitialized = true;

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(عدم);
        إذا (SUCCEEDED(hr)) {
            معلومات->oleinitialized = true;
        } وإلا {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بنانشان صحيح)hr);
        }
#جيڪڏهن_پورو // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } وإلا {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بنانشان صحيح)hr);
    }

    WIN_InitDPIAwareness(_this);

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#جيڪڏهن_پورو

    إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_داخلا(_this);
    }

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_گهڻائي گهڻائي;

        SDL_zero(گهڻائي);
        D3D12_XBOX_GetResolution(&گهڻائي.w, &گهڻائي.h);
        گهڻائي.refresh_شرح = 60.0f;
        گهڻائي.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_جوڙيو_Basic_Video_Display(&گهڻائي);
    }
#وإلا // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!WIN_InitModes(_this)) {
        أرجع false;
    }

    _this->اندروني->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#جيڪڏهن_پورو

    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پيغام_Loop, عدم);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_جوڙيو_Hint_Callback(SDL_HINT_دري_چوکٺو_USABLE_WHILE_CURSOR_HIDDEN, Update_دري_چوکٺو_Usable_While_Cursor_Hidden, عدم);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->_SDL_WAKEUP = رجسٽر_دري_پيغام_A("_SDL_WAKEUP");
    معلومات->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? رجسٽر_دري_پيغام_A("TaskbarButtonCreated") : 0;
#جيڪڏهن_پورو

    أرجع true;
}

فراغ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پيغام_Loop, عدم);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_RemoveHintCallback(SDL_HINT_دري_چوکٺو_USABLE_WHILE_CURSOR_HIDDEN, Update_دري_چوکٺو_Usable_While_Cursor_Hidden, عدم);

    WIN_Quit_Raw_داخلا(_this);
    WIN_Quit_Game_داخلا(_this);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    إذا (معلومات->taskbar_list) {
        معلومات->taskbar_list->lpVtbl->Release(معلومات->taskbar_list);
        معلومات->taskbar_list = عدم;
    }

    إذا (معلومات->oleinitialized) {
        OleUninitialize();
        معلومات->oleinitialized = false;
    }
#جيڪڏهن_پورو // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    إذا (معلومات->coinitialized) {
        WIN_CoUninitialize();
        معلومات->coinitialized = false;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#وصف_ڪريو D3D_DEBUG_INFO
#ضمن <d3d9.h>

#جيڪڏهن_وصف_ٿيل D3D_DEBUG_INFO
#جيڪڏهن_وصف_نه_ٿيل D3_D_SDK_نسخو
#وصف_ڪريو D3_D_SDK_نسخو (32 | 0x80000000)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل D3_D9b_SDK_نسخو
#وصف_ڪريو D3_D9b_SDK_نسخو (31 | 0x80000000)
#جيڪڏهن_پورو
#وإلا //
#جيڪڏهن_وصف_نه_ٿيل D3_D_SDK_نسخو
#وصف_ڪريو D3_D_SDK_نسخو 32
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل D3_D9b_SDK_نسخو
#وصف_ڪريو D3_D9b_SDK_نسخو 31
#جيڪڏهن_پورو
#جيڪڏهن_پورو

bool D3_D_ڀريو_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_ڀريو_Object("D3D9.DLL");
    إذا (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        تعريفنوع HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_ڀريو_Function(*pD3DDLL, "Direct3DCreate9Ex");
            إذا (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_نسخو, &pDirect3D9ExInterface);
                إذا (SUCCEEDED(hr)) {
                    ثابت GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (فراغ **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    إذا (SUCCEEDED(hr)) {
                        أرجع true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_ڀريو_Function(*pD3DDLL, "Direct3DCreate9");
        إذا (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_نسخو);
            إذا (*pDirect3D9Interface) {
                أرجع true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = عدم;
    }
    *pDirect3D9Interface = عدم;
    أرجع false;
}

صحيح SDL_Get_Direct3_D9_Adapter_اشاريو(SDL_DisplayID displayID)
{
    فراغ *pD3DDLL;
    IDirect3D9 *pD3D;
    إذا (!D3_D_ڀريو_DLL(&pD3DDLL, &pD3D)) {
        SDL_سيٽ_Error("Unable to create Direct3D interface");
        أرجع -1;
    } وإلا {
        SDL_Display_معلومات *p_معلومات = SDL_Get_Display_Driver_معلومات(displayID);
        صحيح adapter_اشاريو = D3DADAPTER_DEFAULT;

        إذا (!p_معلومات) {
            SDL_سيٽ_Error("Invalid display index");
            adapter_اشاريو = -1; // make sure we return something invalid
        } وإلا {
            حرف *displayName = WIN_String_منزل_UTF8_W(p_معلومات->DeviceName);
            بنانشان صحيح ڳڻپ = IDirect3_D9_Get_Adapter_ڳڻپ(pD3D);
            بنانشان صحيح i;
            لكل (i = 0; i < ڳڻپ; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                إذا (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_اشاريو = i;
                    اكسر;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        أرجع adapter_اشاريو;
    }
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحيح *adapter_اشاريو, صحيح *output_اشاريو)
{
#جيڪڏهن_وصف_نه_ٿيل HAVE_DXGI_H
    إذا (adapter_اشاريو) {
        *adapter_اشاريو = -1;
    }
    إذا (output_اشاريو) {
        *output_اشاريو = -1;
    }
    أرجع SDL_سيٽ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#وإلا
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_Video_معلومات *videodata = videodevice ? videodevice->اندروني : عدم;
    SDL_Display_معلومات *p_معلومات = SDL_Get_Display_Driver_معلومات(displayID);
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_اشاريو) {
        أرجع SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_اشاريو) {
        أرجع SDL_InvalidParamError("outputIndex");
    }

    *adapter_اشاريو = -1;
    *output_اشاريو = -1;

    إذا (!p_معلومات) {
        أرجع SDL_سيٽ_Error("Invalid display index");
    }

    إذا (!videodata || !videodata->pDXGIFactory) {
        أرجع SDL_سيٽ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    طالما (*adapter_اشاريو == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (*adapter_اشاريو == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, p_معلومات->DeviceName) == 0) {
                    *adapter_اشاريو = nAdapter;
                    *output_اشاريو = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    إذا (*adapter_اشاريو == -1) {
        أرجع SDL_سيٽ_Error("Couldn't find matching adapter");
    }
    أرجع true;
#جيڪڏهن_پورو
}

SDL_SystemTheme WIN_GetSystemTheme(فراغ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_ڪنجي;
    DWORD dwType = REG_DWORD;
    DWORD قدر = ~0U;
    DWORD ڊيگهائي = حجم(قدر);

    // Technically this isn't the system theme, but it's the preference for applications
    إذا (Reg_Open_ڪنجي_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, ڪنجي_READ, &h_ڪنجي) == ERROR_SUCCESS) {
        إذا (Reg_Query_قدر_Ex_W(h_ڪنجي, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&قدر, &ڊيگهائي) == ERROR_SUCCESS) {
            إذا (قدر == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_ڪنجي(h_ڪنجي);
    }
    أرجع theme;
}

bool WIN_Is_في_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->AreDpiAwarenessContextsEqual && معلومات->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        أرجع معلومات->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE_V2, معلومات->GetThreadDpiAwarenessContext());
    }
#جيڪڏهن_پورو
    أرجع false;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS
