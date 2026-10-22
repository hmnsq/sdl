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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS

#اگر_تعریف_شده SDL_VIDEO_VULKAN
#ضمن "../SDL_vulkan_internal.h"
#پایان_اگر
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

#اگر_تعریف_نشده __ITaskbarList3_FWD_DEFINED__
تعريفنوع بنية ITaskbarList3 ITaskbarList3;
#پایان_اگر

#اگر_تعریف_نشده __ITaskbarList3_INTERFACE_DEFINED__
تعريفنوع تعداد TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_نرمال = 0x2,
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
#رهنمود warning(disable: 4103)
#پایان_اگر
#رهنمود pack(افزودن, 8)
تعريفنوع بنية THUMBBUTTON
{
    THUMBBUTTONMASK dw_ماسک;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

تعريفنوع بنية THUMBBUTTON *LPTHUMBBUTTON;
#رهنمود pack(برداشت)

#اگر_تعریف_نشده HIMAGELIST
بنية _IMAGELIST;
تعريفنوع بنية _IMAGELIST *HIMAGELIST;
#پایان_اگر

تعريفنوع بنية ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, فراغ **ppvObject);
    ULONG (__stdcall *جمع_کن_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *جمع_کن_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *مجموعه_فعال_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_پنجره)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *مجموعه_پیشرفت_مقدار)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_مجموع);
    HRESULT (__stdcall *مجموعه_پیشرفت_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *ثبات_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *مجموعه_Tab_ترتیب)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_درج_Before);
    HRESULT (__stdcall *مجموعه_Tab_فعال)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_جمع_کن_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_مجموعه_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *مجموعه_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *مجموعه_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *مجموعه_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

بنية ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#پایان_اگر // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#پایان_اگر

#اگر_تعریف_شده SDL_GDK_TEXTINPUT
#ضمن "../gdk/SDL_gdktextinput.h"
#پایان_اگر

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ساكن bool WIN_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_پیام_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_پنجره_قاب_Usable_While_Cursor_Hidden = true;

ساكن فراغ SDLCALL UpdateWindowsRawKeyboard(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_مجموعه_Raw_Keyboard_Enabled(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_مجموعه_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardInputsink(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_مجموعه_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawMouseNoLegacy(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_مقدار, false);
    WIN_مجموعه_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ساكن فراغ SDLCALL Update_Windows_Enable_پیام_Loop(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    g_Windows_Enable_پیام_Loop = SDL_GetStringBoolean(new_مقدار, true);
}

ساكن فراغ SDLCALL UpdateWindowsEnableMenuMnemonics(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_مقدار, false);
}

ساكن فراغ SDLCALL Update_پنجره_قاب_Usable_While_Cursor_Hidden(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    g_پنجره_قاب_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_مقدار, true);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD نتیجه;
    إذا (_this->suspend_screensaver) {
        نتیجه = مجموعه_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } وإلا {
        نتیجه = مجموعه_Thread_Execution_State(ES_CONTINUOUS);
    }
    إذا (نتیجه == 0) {
        SDL_مجموعه_Error("SetThreadExecutionState() failed");
        أرجع false;
    }
    أرجع true;
}
#پایان_اگر

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
خارجي فراغ D3D12_XBOX_GetResolution(Uint32 *عرض, Uint32 *ارتفاع);
#پایان_اگر

// Windows driver bootstrap functions

ساكن فراغ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_داده *داده = device->داخلی;

    SDL_UnregisterApp();
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (داده->userDLL) {
        SDL_UnloadObject(داده->userDLL);
    }
    إذا (داده->shcoreDLL) {
        SDL_UnloadObject(داده->shcoreDLL);
    }
    إذا (داده->dwmapiDLL) {
        SDL_UnloadObject(داده->dwmapiDLL);
    }
#پایان_اگر
#اگر_تعریف_شده HAVE_DXGI_H
    إذا (داده->pDXGIFactory) {
        IDXGIFactory_Release(داده->pDXGIFactory);
    }
    إذا (داده->dxgiDLL) {
        SDL_UnloadObject(داده->dxgiDLL);
    }
#پایان_اگر
    SDL_free(device->داخلی->rawinput);
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *WIN_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *داده;

    SDL_ثبات_App(عدم, 0, عدم);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        داده = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    } وإلا {
        داده = عدم;
    }
    إذا (!داده) {
        SDL_UnregisterApp();
        SDL_free(device);
        أرجع عدم;
    }
    device->داخلی = داده;
    device->system_theme = WIN_GetSystemTheme();

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    داده->userDLL = SDL_بارگیری_Object("USER32.DLL");
    إذا (داده->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        داده->Close_Touch_درون_داد_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_بارگیری_Function(داده->userDLL, "CloseTouchInputHandle");
        داده->Get_Touch_درون_داد_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح)) SDL_بارگیری_Function(داده->userDLL, "GetTouchInputInfo");
        داده->ثبات_Touch_پنجره = (BOOL (WINAPI *)(HWND, ULONG))SDL_بارگیری_Function(داده->userDLL, "RegisterTouchWindow");
        داده->مجموعه_Process_DPIAware = (BOOL (WINAPI *)(فراغ))SDL_بارگیری_Function(داده->userDLL, "SetProcessDPIAware");
        داده->مجموعه_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارگیری_Function(داده->userDLL, "SetProcessDpiAwarenessContext");
        داده->مجموعه_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارگیری_Function(داده->userDLL, "SetThreadDpiAwarenessContext");
        داده->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(فراغ))SDL_بارگیری_Function(داده->userDLL, "GetThreadDpiAwarenessContext");
        داده->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارگیری_Function(داده->userDLL, "GetAwarenessFromDpiAwarenessContext");
        داده->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_بارگیری_Function(داده->userDLL, "EnableNonClientDpiScaling");
        داده->Adjust_پنجره_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_بارگیری_Function(داده->userDLL, "AdjustWindowRectExForDpi");
        داده->Get_Dpi_For_پنجره = (UINT (WINAPI *)(HWND))SDL_بارگیری_Function(داده->userDLL, "GetDpiForWindow");
        داده->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_بارگیری_Function(داده->userDLL, "AreDpiAwarenessContextsEqual");
        داده->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارگیری_Function(داده->userDLL, "IsValidDpiAwarenessContext");
        داده->Get_Display_Config_میانگیر_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_بارگیری_Function(داده->userDLL, "GetDisplayConfigBufferSizes");
        داده->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_مسیر_INFO*,UINT32 *,DISPLAYCONFIG_نما_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_بارگیری_Function(داده->userDLL, "QueryDisplayConfig");
        داده->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_سرآیند*))SDL_بارگیری_Function(داده->userDLL, "DisplayConfigGetDeviceInfo");
        داده->Get_اشاره_گر_Type = (BOOL (WINAPI *)(UINT32, اشاره_گر_درون_داد_TYPE *))SDL_بارگیری_Function(داده->userDLL, "GetPointerType");
        داده->Get_اشاره_گر_Pen_Info = (BOOL (WINAPI *)(UINT32, اشاره_گر_PEN_INFO *))SDL_بارگیری_Function(داده->userDLL, "GetPointerPenInfo");
        داده->Get_اشاره_گر_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_بارگیری_Function(داده->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    داده->shcoreDLL = SDL_بارگیری_Object("SHCORE.DLL");
    إذا (داده->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        داده->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_بارگیری_Function(داده->shcoreDLL, "GetDpiForMonitor");
        داده->مجموعه_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_بارگیری_Function(داده->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    داده->dwmapiDLL = SDL_بارگیری_Object("DWMAPI.DLL");
    إذا (داده->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        داده->DwmFlush = (HRESULT (WINAPI *)(فراغ))SDL_بارگیری_Function(داده->dwmapiDLL, "DwmFlush");
        داده->Dwm_Enable_Blur_Behind_پنجره = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_بارگیری_Function(داده->dwmapiDLL, "DwmEnableBlurBehindWindow");
        داده->Dwm_مجموعه_پنجره_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_بارگیری_Function(داده->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }
#پایان_اگر // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شده HAVE_DXGI_H
    داده->dxgiDLL = SDL_بارگیری_Object("DXGI.DLL");
    إذا (داده->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, فراغ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_بارگیری_Function(داده->dxgiDLL, "CreateDXGIFactory");
        إذا (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (فراغ **)&داده->pDXGIFactory);
        }
    }
#پایان_اگر

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->مجموعه_Display_نما = WIN_مجموعه_Display_نما;
#پایان_اگر
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#پایان_اگر

    device->CreateSDLWindow = WIN_Create_پنجره;
    device->مجموعه_پنجره_Title = WIN_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Icon = WIN_مجموعه_پنجره_Icon;
    device->مجموعه_پنجره_Position = WIN_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = WIN_مجموعه_پنجره_اندازه;
    device->Get_پنجره_Borders_اندازه = WIN_Get_پنجره_Borders_اندازه;
    device->Get_پنجره_اندازه_درون_Pixels = WIN_Get_پنجره_اندازه_درون_Pixels;
    device->مجموعه_پنجره_Opacity = WIN_مجموعه_پنجره_Opacity;
    device->Show_پنجره = WIN_Show_پنجره;
    device->Hide_پنجره = WIN_Hide_پنجره;
    device->Raise_پنجره = WIN_Raise_پنجره;
    device->Maximize_پنجره = WIN_Maximize_پنجره;
    device->Minimize_پنجره = WIN_Minimize_پنجره;
    device->Restore_پنجره = WIN_Restore_پنجره;
    device->مجموعه_پنجره_Bordered = WIN_مجموعه_پنجره_Bordered;
    device->مجموعه_پنجره_Resizable = WIN_مجموعه_پنجره_Resizable;
    device->مجموعه_پنجره_Always_On_بالاترین = WIN_مجموعه_پنجره_Always_On_بالاترین;
    device->مجموعه_پنجره_Fullscreen = WIN_مجموعه_پنجره_Fullscreen;
    device->مجموعه_پنجره_والد = WIN_مجموعه_پنجره_والد;
    device->مجموعه_پنجره_Modal = WIN_مجموعه_پنجره_Modal;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_پنجره_ICCProfile = WIN_Get_پنجره_ICCProfile;
    device->مجموعه_پنجره_Mouse_Rect = WIN_مجموعه_پنجره_Mouse_Rect;
    device->مجموعه_پنجره_Mouse_Grab = WIN_مجموعه_پنجره_Mouse_Grab;
    device->مجموعه_پنجره_Keyboard_Grab = WIN_مجموعه_پنجره_Keyboard_Grab;
#پایان_اگر
    device->Destroy_پنجره = WIN_Destroy_پنجره;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_پنجره_Framebuffer = WIN_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = WIN_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = WIN_Destroy_پنجره_Framebuffer;
    device->On_پنجره_Enter = WIN_On_پنجره_Enter;
    device->مجموعه_پنجره_اصابت_Test = WIN_مجموعه_پنجره_اصابت_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_پنجره = WIN_Flash_پنجره;
    device->Apply_پنجره_پیشرفت = WIN_Apply_پنجره_پیشرفت;
    device->Show_پنجره_System_Menu = WIN_Show_پنجره_System_Menu;
    device->مجموعه_پنجره_Focusable = WIN_مجموعه_پنجره_Focusable;
    device->Update_پنجره_Shape = WIN_Update_پنجره_Shape;
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
    device->GL_بارگیری_Library = WIN_GL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = WIN_GL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = WIN_GL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = WIN_GL_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = WIN_GL_جابجا_پنجره;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#پایان_اگر
        // Use EGL based functions
        device->GL_بارگیری_Library = WIN_GLES_بارگیری_Library;
        device->GL_Get_Proc_آدرس = WIN_GLES_Get_Proc_آدرس;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_مجموعه_جابجا_Interval = WIN_GLES_مجموعه_جابجا_Interval;
        device->GL_Get_جابجا_Interval = WIN_GLES_Get_جابجا_Interval;
        device->GL_جابجا_پنجره = WIN_GLES_جابجا_پنجره;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
    }
#پایان_اگر
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = WIN_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#پایان_اگر

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->شروع_متن_درون_داد = WIN_شروع_متن_درون_داد;
    device->Stop_متن_درون_داد = WIN_Stop_متن_درون_داد;
    device->Update_متن_درون_داد_Area = WIN_Update_متن_درون_داد_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->مجموعه_Clipboard_داده = WIN_مجموعه_Clipboard_داده;
    device->Get_Clipboard_داده = WIN_Get_Clipboard_داده;
    device->Has_Clipboard_داده = WIN_Has_Clipboard_داده;
#پایان_اگر

#اگر_تعریف_شده SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->شروع_متن_درون_داد = GDK_شروع_متن_درون_داد;
    device->Stop_متن_درون_داد = GDK_Stop_متن_درون_داد;
    device->Update_متن_درون_داد_Area = GDK_Update_متن_درون_داد_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#پایان_اگر

    device->حرر = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_پنجره_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_پیام_Box,
    #وإلا
    عدم,
    #پایان_اگر
    false
};

ساكن BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->مجموعه_Process_Dpi_Awareness_Context) {
        داده->dpi_unaware_context_declared = true;
        أرجع داده->مجموعه_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } وإلا إذا (داده->مجموعه_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(داده->مجموعه_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#پایان_اگر
    أرجع FALSE;
}

ساكن BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->مجموعه_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع داده->مجموعه_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } وإلا إذا (داده->مجموعه_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(داده->مجموعه_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } وإلا إذا (داده->مجموعه_Process_DPIAware) {
        // Windows Vista
        أرجع داده->مجموعه_Process_DPIAware();
    }
#پایان_اگر
    أرجع FALSE;
}

ساكن BOOL WIN_Declare_DPIAware_در_هر_Monitor(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->مجموعه_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع داده->مجموعه_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE);
    } وإلا إذا (داده->مجموعه_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(داده->مجموعه_Process_Dpi_Awareness(PROCESS_در_هر_MONITOR_DPI_AWARE));
    } وإلا {
        // Older OS: fall back to system DPI aware
        أرجع WIN_DeclareDPIAwareSystem(_this);
    }
#وإلا
    أرجع FALSE;
#پایان_اگر
}

ساكن BOOL WIN_Declare_DPIAware_در_هر_Monitor_V2(SDL_VideoDevice *_this)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع FALSE;
#وإلا
    SDL_Video_داده *داده = _this->داخلی;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    إذا (داده->مجموعه_Process_Dpi_Awareness_Context) {
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
        إذا (داده->مجموعه_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2)) {
            أرجع TRUE;
        } وإلا {
            أرجع WIN_Declare_DPIAware_در_هر_Monitor(_this);
        }
    } وإلا {
        // Older OS: fall back to per-monitor (or system)
        أرجع WIN_Declare_DPIAware_در_هر_Monitor(_this);
    }
#پایان_اگر
}

#اگر_تعریف_شده HIGHDPI_DEBUG
ساكن ثابت حرف *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->GetThreadDpiAwarenessContext && داده->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = داده->GetThreadDpiAwarenessContext();

        إذا (داده->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            أرجع "unaware";
        } وإلا إذا (داده->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            أرجع "system";
        } وإلا إذا (داده->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE)) {
            أرجع "permonitor";
        } وإلا إذا (داده->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2)) {
            أرجع "permonitorv2";
        } وإلا إذا (داده->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            أرجع "unaware_gdiscaled";
        }
    }

    أرجع "";
}
#پایان_اگر

ساكن فراغ WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ثابت حرف *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    إذا (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_در_هر_Monitor_V2(_this);
    } وإلا إذا (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_در_هر_Monitor(_this);
    } وإلا إذا (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } وإلا إذا (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ساكن bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    HRESULT hr;

    hr = WIN_CoInitialize();
    إذا (SUCCEEDED(hr)) {
        داده->coinitialized = true;

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(عدم);
        إذا (SUCCEEDED(hr)) {
            داده->oleinitialized = true;
        } وإلا {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بیعلامت صحيح)hr);
        }
#پایان_اگر // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } وإلا {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بیعلامت صحيح)hr);
    }

    WIN_InitDPIAwareness(_this);

#اگر_تعریف_شده HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#پایان_اگر

    إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_درون_داد(_this);
    }

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_نما نما;

        SDL_zero(نما);
        D3D12_XBOX_GetResolution(&نما.w, &نما.h);
        نما.refresh_نرخ = 60.0f;
        نما.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_جمع_کن_Basic_Video_Display(&نما);
    }
#وإلا // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!WIN_InitModes(_this)) {
        أرجع false;
    }

    _this->داخلی->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#پایان_اگر

    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیام_Loop, عدم);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_جمع_کن_Hint_Callback(SDL_HINT_پنجره_قاب_USABLE_WHILE_CURSOR_HIDDEN, Update_پنجره_قاب_Usable_While_Cursor_Hidden, عدم);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    داده->_SDL_WAKEUP = ثبات_پنجره_پیام_A("_SDL_WAKEUP");
    داده->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? ثبات_پنجره_پیام_A("TaskbarButtonCreated") : 0;
#پایان_اگر

    أرجع true;
}

فراغ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیام_Loop, عدم);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_RemoveHintCallback(SDL_HINT_پنجره_قاب_USABLE_WHILE_CURSOR_HIDDEN, Update_پنجره_قاب_Usable_While_Cursor_Hidden, عدم);

    WIN_Quit_Raw_درون_داد(_this);
    WIN_Quit_Game_درون_داد(_this);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    إذا (داده->taskbar_list) {
        داده->taskbar_list->lpVtbl->Release(داده->taskbar_list);
        داده->taskbar_list = عدم;
    }

    إذا (داده->oleinitialized) {
        OleUninitialize();
        داده->oleinitialized = false;
    }
#پایان_اگر // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    إذا (داده->coinitialized) {
        WIN_CoUninitialize();
        داده->coinitialized = false;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کن D3D_DEBUG_INFO
#ضمن <d3d9.h>

#اگر_تعریف_شده D3D_DEBUG_INFO
#اگر_تعریف_نشده D3_D_SDK_نسخه
#تعریف_کن D3_D_SDK_نسخه (32 | 0x80000000)
#پایان_اگر
#اگر_تعریف_نشده D3_D9b_SDK_نسخه
#تعریف_کن D3_D9b_SDK_نسخه (31 | 0x80000000)
#پایان_اگر
#وإلا //
#اگر_تعریف_نشده D3_D_SDK_نسخه
#تعریف_کن D3_D_SDK_نسخه 32
#پایان_اگر
#اگر_تعریف_نشده D3_D9b_SDK_نسخه
#تعریف_کن D3_D9b_SDK_نسخه 31
#پایان_اگر
#پایان_اگر

bool D3_D_بارگیری_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_بارگیری_Object("D3D9.DLL");
    إذا (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        تعريفنوع HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_بارگیری_Function(*pD3DDLL, "Direct3DCreate9Ex");
            إذا (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_نسخه, &pDirect3D9ExInterface);
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

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_بارگیری_Function(*pD3DDLL, "Direct3DCreate9");
        إذا (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_نسخه);
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

صحيح SDL_Get_Direct3_D9_Adapter_شاخص(SDL_DisplayID displayID)
{
    فراغ *pD3DDLL;
    IDirect3D9 *pD3D;
    إذا (!D3_D_بارگیری_DLL(&pD3DDLL, &pD3D)) {
        SDL_مجموعه_Error("Unable to create Direct3D interface");
        أرجع -1;
    } وإلا {
        SDL_Display_داده *p_داده = SDL_Get_Display_Driver_داده(displayID);
        صحيح adapter_شاخص = D3DADAPTER_DEFAULT;

        إذا (!p_داده) {
            SDL_مجموعه_Error("Invalid display index");
            adapter_شاخص = -1; // make sure we return something invalid
        } وإلا {
            حرف *displayName = WIN_String_مقصد_UTF8_W(p_داده->DeviceName);
            بیعلامت صحيح شمار = IDirect3_D9_Get_Adapter_شمار(pD3D);
            بیعلامت صحيح i;
            لكل (i = 0; i < شمار; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                إذا (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_شاخص = i;
                    اكسر;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        أرجع adapter_شاخص;
    }
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحيح *adapter_شاخص, صحيح *output_شاخص)
{
#اگر_تعریف_نشده HAVE_DXGI_H
    إذا (adapter_شاخص) {
        *adapter_شاخص = -1;
    }
    إذا (output_شاخص) {
        *output_شاخص = -1;
    }
    أرجع SDL_مجموعه_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#وإلا
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_Video_داده *videodata = videodevice ? videodevice->داخلی : عدم;
    SDL_Display_داده *p_داده = SDL_Get_Display_Driver_داده(displayID);
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_شاخص) {
        أرجع SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_شاخص) {
        أرجع SDL_InvalidParamError("outputIndex");
    }

    *adapter_شاخص = -1;
    *output_شاخص = -1;

    إذا (!p_داده) {
        أرجع SDL_مجموعه_Error("Invalid display index");
    }

    إذا (!videodata || !videodata->pDXGIFactory) {
        أرجع SDL_مجموعه_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    طالما (*adapter_شاخص == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (*adapter_شاخص == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, p_داده->DeviceName) == 0) {
                    *adapter_شاخص = nAdapter;
                    *output_شاخص = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    إذا (*adapter_شاخص == -1) {
        أرجع SDL_مجموعه_Error("Couldn't find matching adapter");
    }
    أرجع true;
#پایان_اگر
}

SDL_SystemTheme WIN_GetSystemTheme(فراغ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_کلید;
    DWORD dwType = REG_DWORD;
    DWORD مقدار = ~0U;
    DWORD درازی = حجم(مقدار);

    // Technically this isn't the system theme, but it's the preference for applications
    إذا (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, کلید_READ, &h_کلید) == ERROR_SUCCESS) {
        إذا (Reg_Query_مقدار_Ex_W(h_کلید, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&مقدار, &درازی) == ERROR_SUCCESS) {
            إذا (مقدار == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_کلید(h_کلید);
    }
    أرجع theme;
}

bool WIN_Is_در_هر_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->AreDpiAwarenessContextsEqual && داده->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        أرجع داده->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2, داده->GetThreadDpiAwarenessContext());
    }
#پایان_اگر
    أرجع false;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS
