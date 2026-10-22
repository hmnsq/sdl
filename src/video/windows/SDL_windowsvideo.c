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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS

#که_تعریف_شوی SDL_VIDEO_VULKAN
#ضمن "../SDL_vulkan_internal.h"
#د_که_پای
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

#که_نه_تعریف_شوی __ITaskbarList3_FWD_DEFINED__
تعريفنوع بنية ITaskbarList3 ITaskbarList3;
#د_که_پای

#که_نه_تعریف_شوی __ITaskbarList3_INTERFACE_DEFINED__
تعريفنوع تعداد TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_نورمال = 0x2,
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
#لارښوونه warning(disable: 4103)
#د_که_پای
#لارښوونه pack(ټېل, 8)
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
#لارښوونه pack(راوباسه)

#که_نه_تعریف_شوی HIMAGELIST
بنية _IMAGELIST;
تعريفنوع بنية _IMAGELIST *HIMAGELIST;
#د_که_پای

تعريفنوع بنية ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, فراغ **ppvObject);
    ULONG (__stdcall *جمع_کړه_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *جمع_کړه_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *سېټ_فعال_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_کړکۍ)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *سېټ_پرمختګ_ارزښت)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_ټول);
    HRESULT (__stdcall *سېټ_پرمختګ_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *ثبتوونکی_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *سېټ_Tab_ترتیب)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_ورننباسه_Before);
    HRESULT (__stdcall *سېټ_Tab_فعال)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_جمع_کړه_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_سېټ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *سېټ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *سېټ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *سېټ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

بنية ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#د_که_پای // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#د_که_پای

#که_تعریف_شوی SDL_GDK_TEXTINPUT
#ضمن "../gdk/SDL_gdktextinput.h"
#د_که_پای

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ساكن bool WIN_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_پیغام_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden = true;

ساكن فراغ SDLCALL UpdateWindowsRawKeyboard(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ارزښت, false);
    WIN_سېټ_Raw_Keyboard_Enabled(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ارزښت, false);
    WIN_سېټ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardInputsink(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ارزښت, false);
    WIN_سېټ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawMouseNoLegacy(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_ارزښت, false);
    WIN_سېټ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ساكن فراغ SDLCALL Update_Windows_Enable_پیغام_Loop(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    g_Windows_Enable_پیغام_Loop = SDL_GetStringBoolean(new_ارزښت, true);
}

ساكن فراغ SDLCALL UpdateWindowsEnableMenuMnemonics(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_ارزښت, false);
}

ساكن فراغ SDLCALL Update_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    g_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_ارزښت, true);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD پایله;
    إذا (_this->suspend_screensaver) {
        پایله = سېټ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } وإلا {
        پایله = سېټ_Thread_Execution_State(ES_CONTINUOUS);
    }
    إذا (پایله == 0) {
        SDL_سېټ_Error("SetThreadExecutionState() failed");
        أرجع false;
    }
    أرجع true;
}
#د_که_پای

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
خارجي فراغ D3D12_XBOX_GetResolution(Uint32 *پلنوالی, Uint32 *لوړوالی);
#د_که_پای

// Windows driver bootstrap functions

ساكن فراغ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;

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
#د_که_پای
#که_تعریف_شوی HAVE_DXGI_H
    إذا (معلومات->pDXGIFactory) {
        IDXGIFactory_Release(معلومات->pDXGIFactory);
    }
    إذا (معلومات->dxgiDLL) {
        SDL_UnloadObject(معلومات->dxgiDLL);
    }
#د_که_پای
    SDL_free(device->دننی->rawinput);
    SDL_free(device->دننی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *WIN_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;

    SDL_ثبتوونکی_App(عدم, 0, عدم);

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
    device->دننی = معلومات;
    device->system_theme = WIN_GetSystemTheme();

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->userDLL = SDL_بارول_Object("USER32.DLL");
    إذا (معلومات->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->Close_Touch_ننوت_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_بارول_Function(معلومات->userDLL, "CloseTouchInputHandle");
        معلومات->Get_Touch_ننوت_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح)) SDL_بارول_Function(معلومات->userDLL, "GetTouchInputInfo");
        معلومات->ثبتوونکی_Touch_کړکۍ = (BOOL (WINAPI *)(HWND, ULONG))SDL_بارول_Function(معلومات->userDLL, "RegisterTouchWindow");
        معلومات->سېټ_Process_DPIAware = (BOOL (WINAPI *)(فراغ))SDL_بارول_Function(معلومات->userDLL, "SetProcessDPIAware");
        معلومات->سېټ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارول_Function(معلومات->userDLL, "SetProcessDpiAwarenessContext");
        معلومات->سېټ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارول_Function(معلومات->userDLL, "SetThreadDpiAwarenessContext");
        معلومات->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(فراغ))SDL_بارول_Function(معلومات->userDLL, "GetThreadDpiAwarenessContext");
        معلومات->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارول_Function(معلومات->userDLL, "GetAwarenessFromDpiAwarenessContext");
        معلومات->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_بارول_Function(معلومات->userDLL, "EnableNonClientDpiScaling");
        معلومات->Adjust_کړکۍ_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_بارول_Function(معلومات->userDLL, "AdjustWindowRectExForDpi");
        معلومات->Get_Dpi_For_کړکۍ = (UINT (WINAPI *)(HWND))SDL_بارول_Function(معلومات->userDLL, "GetDpiForWindow");
        معلومات->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_بارول_Function(معلومات->userDLL, "AreDpiAwarenessContextsEqual");
        معلومات->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بارول_Function(معلومات->userDLL, "IsValidDpiAwarenessContext");
        معلومات->Get_Display_Config_بفر_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_بارول_Function(معلومات->userDLL, "GetDisplayConfigBufferSizes");
        معلومات->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_لار_INFO*,UINT32 *,DISPLAYCONFIG_ډېرپېښ_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_بارول_Function(معلومات->userDLL, "QueryDisplayConfig");
        معلومات->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_سرلیک*))SDL_بارول_Function(معلومات->userDLL, "DisplayConfigGetDeviceInfo");
        معلومات->Get_اشاره_ګر_Type = (BOOL (WINAPI *)(UINT32, اشاره_ګر_ننوت_TYPE *))SDL_بارول_Function(معلومات->userDLL, "GetPointerType");
        معلومات->Get_اشاره_ګر_Pen_Info = (BOOL (WINAPI *)(UINT32, اشاره_ګر_PEN_INFO *))SDL_بارول_Function(معلومات->userDLL, "GetPointerPenInfo");
        معلومات->Get_اشاره_ګر_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_بارول_Function(معلومات->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    معلومات->shcoreDLL = SDL_بارول_Object("SHCORE.DLL");
    إذا (معلومات->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_بارول_Function(معلومات->shcoreDLL, "GetDpiForMonitor");
        معلومات->سېټ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_بارول_Function(معلومات->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    معلومات->dwmapiDLL = SDL_بارول_Object("DWMAPI.DLL");
    إذا (معلومات->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        معلومات->DwmFlush = (HRESULT (WINAPI *)(فراغ))SDL_بارول_Function(معلومات->dwmapiDLL, "DwmFlush");
        معلومات->Dwm_Enable_Blur_Behind_کړکۍ = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_بارول_Function(معلومات->dwmapiDLL, "DwmEnableBlurBehindWindow");
        معلومات->Dwm_سېټ_کړکۍ_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_بارول_Function(معلومات->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }
#د_که_پای // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#که_تعریف_شوی HAVE_DXGI_H
    معلومات->dxgiDLL = SDL_بارول_Object("DXGI.DLL");
    إذا (معلومات->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, فراغ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_بارول_Function(معلومات->dxgiDLL, "CreateDXGIFactory");
        إذا (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (فراغ **)&معلومات->pDXGIFactory);
        }
    }
#د_که_پای

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = WIN_سېټ_Display_ډېرپېښ;
#د_که_پای
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#د_که_پای

    device->CreateSDLWindow = WIN_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = WIN_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Icon = WIN_سېټ_کړکۍ_Icon;
    device->سېټ_کړکۍ_Position = WIN_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = WIN_سېټ_کړکۍ_اندازه;
    device->Get_کړکۍ_Borders_اندازه = WIN_Get_کړکۍ_Borders_اندازه;
    device->Get_کړکۍ_اندازه_دننه_Pixels = WIN_Get_کړکۍ_اندازه_دننه_Pixels;
    device->سېټ_کړکۍ_Opacity = WIN_سېټ_کړکۍ_Opacity;
    device->Show_کړکۍ = WIN_Show_کړکۍ;
    device->Hide_کړکۍ = WIN_Hide_کړکۍ;
    device->Raise_کړکۍ = WIN_Raise_کړکۍ;
    device->Maximize_کړکۍ = WIN_Maximize_کړکۍ;
    device->Minimize_کړکۍ = WIN_Minimize_کړکۍ;
    device->Restore_کړکۍ = WIN_Restore_کړکۍ;
    device->سېټ_کړکۍ_Bordered = WIN_سېټ_کړکۍ_Bordered;
    device->سېټ_کړکۍ_Resizable = WIN_سېټ_کړکۍ_Resizable;
    device->سېټ_کړکۍ_Always_On_سر = WIN_سېټ_کړکۍ_Always_On_سر;
    device->سېټ_کړکۍ_Fullscreen = WIN_سېټ_کړکۍ_Fullscreen;
    device->سېټ_کړکۍ_پلار = WIN_سېټ_کړکۍ_پلار;
    device->سېټ_کړکۍ_Modal = WIN_سېټ_کړکۍ_Modal;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_کړکۍ_ICCProfile = WIN_Get_کړکۍ_ICCProfile;
    device->سېټ_کړکۍ_Mouse_Rect = WIN_سېټ_کړکۍ_Mouse_Rect;
    device->سېټ_کړکۍ_Mouse_Grab = WIN_سېټ_کړکۍ_Mouse_Grab;
    device->سېټ_کړکۍ_Keyboard_Grab = WIN_سېټ_کړکۍ_Keyboard_Grab;
#د_که_پای
    device->Destroy_کړکۍ = WIN_Destroy_کړکۍ;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_کړکۍ_Framebuffer = WIN_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = WIN_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = WIN_Destroy_کړکۍ_Framebuffer;
    device->On_کړکۍ_Enter = WIN_On_کړکۍ_Enter;
    device->سېټ_کړکۍ_موندنه_Test = WIN_سېټ_کړکۍ_موندنه_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_کړکۍ = WIN_Flash_کړکۍ;
    device->Apply_کړکۍ_پرمختګ = WIN_Apply_کړکۍ_پرمختګ;
    device->Show_کړکۍ_System_Menu = WIN_Show_کړکۍ_System_Menu;
    device->سېټ_کړکۍ_Focusable = WIN_سېټ_کړکۍ_Focusable;
    device->Update_کړکۍ_Shape = WIN_Update_کړکۍ_Shape;
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
    device->GL_بارول_Library = WIN_GL_بارول_Library;
    device->GL_Get_Proc_پته = WIN_GL_Get_Proc_پته;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = WIN_GL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = WIN_GL_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = WIN_GL_بدلون_کړکۍ;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#د_که_پای
        // Use EGL based functions
        device->GL_بارول_Library = WIN_GLES_بارول_Library;
        device->GL_Get_Proc_پته = WIN_GLES_Get_Proc_پته;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_سېټ_بدلون_Interval = WIN_GLES_سېټ_بدلون_Interval;
        device->GL_Get_بدلون_Interval = WIN_GLES_Get_بدلون_Interval;
        device->GL_بدلون_کړکۍ = WIN_GLES_بدلون_کړکۍ;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
    }
#د_که_پای
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_VULKAN
    device->Vulkan_بارول_Library = WIN_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#د_که_پای

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->پیل_متن_ننوت = WIN_پیل_متن_ننوت;
    device->Stop_متن_ننوت = WIN_Stop_متن_ننوت;
    device->Update_متن_ننوت_Area = WIN_Update_متن_ننوت_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->سېټ_Clipboard_معلومات = WIN_سېټ_Clipboard_معلومات;
    device->Get_Clipboard_معلومات = WIN_Get_Clipboard_معلومات;
    device->Has_Clipboard_معلومات = WIN_Has_Clipboard_معلومات;
#د_که_پای

#که_تعریف_شوی SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->پیل_متن_ننوت = GDK_پیل_متن_ننوت;
    device->Stop_متن_ننوت = GDK_Stop_متن_ننوت;
    device->Update_متن_ننوت_Area = GDK_Update_متن_ننوت_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#د_که_پای

    device->حرر = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کړکۍ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_پیغام_Box,
    #وإلا
    عدم,
    #د_که_پای
    false
};

ساكن BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->سېټ_Process_Dpi_Awareness_Context) {
        معلومات->dpi_unaware_context_declared = true;
        أرجع معلومات->سېټ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } وإلا إذا (معلومات->سېټ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سېټ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#د_که_پای
    أرجع FALSE;
}

ساكن BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->سېټ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع معلومات->سېټ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } وإلا إذا (معلومات->سېټ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سېټ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } وإلا إذا (معلومات->سېټ_Process_DPIAware) {
        // Windows Vista
        أرجع معلومات->سېټ_Process_DPIAware();
    }
#د_که_پای
    أرجع FALSE;
}

ساكن BOOL WIN_Declare_DPIAware_فی_Monitor(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->سېټ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع معلومات->سېټ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE);
    } وإلا إذا (معلومات->سېټ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(معلومات->سېټ_Process_Dpi_Awareness(PROCESS_فی_MONITOR_DPI_AWARE));
    } وإلا {
        // Older OS: fall back to system DPI aware
        أرجع WIN_DeclareDPIAwareSystem(_this);
    }
#وإلا
    أرجع FALSE;
#د_که_پای
}

ساكن BOOL WIN_Declare_DPIAware_فی_Monitor_V2(SDL_VideoDevice *_this)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع FALSE;
#وإلا
    SDL_Video_معلومات *معلومات = _this->دننی;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    إذا (معلومات->سېټ_Process_Dpi_Awareness_Context) {
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
        إذا (معلومات->سېټ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            أرجع TRUE;
        } وإلا {
            أرجع WIN_Declare_DPIAware_فی_Monitor(_this);
        }
    } وإلا {
        // Older OS: fall back to per-monitor (or system)
        أرجع WIN_Declare_DPIAware_فی_Monitor(_this);
    }
#د_که_پای
}

#که_تعریف_شوی HIGHDPI_DEBUG
ساكن ثابت حرف *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->GetThreadDpiAwarenessContext && معلومات->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = معلومات->GetThreadDpiAwarenessContext();

        إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            أرجع "unaware";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            أرجع "system";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE)) {
            أرجع "permonitor";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            أرجع "permonitorv2";
        } وإلا إذا (معلومات->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            أرجع "unaware_gdiscaled";
        }
    }

    أرجع "";
}
#د_که_پای

ساكن فراغ WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ثابت حرف *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    إذا (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_فی_Monitor_V2(_this);
    } وإلا إذا (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_فی_Monitor(_this);
    } وإلا إذا (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } وإلا إذا (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ساكن bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    HRESULT hr;

    hr = WIN_CoInitialize();
    إذا (SUCCEEDED(hr)) {
        معلومات->coinitialized = true;

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(عدم);
        إذا (SUCCEEDED(hr)) {
            معلومات->oleinitialized = true;
        } وإلا {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بینښه صحيح)hr);
        }
#د_که_پای // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } وإلا {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بینښه صحيح)hr);
    }

    WIN_InitDPIAwareness(_this);

#که_تعریف_شوی HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#د_که_پای

    إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_ننوت(_this);
    }

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_ډېرپېښ ډېرپېښ;

        SDL_zero(ډېرپېښ);
        D3D12_XBOX_GetResolution(&ډېرپېښ.w, &ډېرپېښ.h);
        ډېرپېښ.refresh_شرح = 60.0f;
        ډېرپېښ.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ);
    }
#وإلا // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!WIN_InitModes(_this)) {
        أرجع false;
    }

    _this->دننی->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#د_که_پای

    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیغام_Loop, عدم);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_جمع_کړه_Hint_Callback(SDL_HINT_کړکۍ_چوکاټ_USABLE_WHILE_CURSOR_HIDDEN, Update_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden, عدم);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->_SDL_WAKEUP = ثبتوونکی_کړکۍ_پیغام_A("_SDL_WAKEUP");
    معلومات->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? ثبتوونکی_کړکۍ_پیغام_A("TaskbarButtonCreated") : 0;
#د_که_پای

    أرجع true;
}

فراغ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیغام_Loop, عدم);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_RemoveHintCallback(SDL_HINT_کړکۍ_چوکاټ_USABLE_WHILE_CURSOR_HIDDEN, Update_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden, عدم);

    WIN_Quit_Raw_ننوت(_this);
    WIN_Quit_Game_ننوت(_this);

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
#د_که_پای // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    إذا (معلومات->coinitialized) {
        WIN_CoUninitialize();
        معلومات->coinitialized = false;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کړه D3D_DEBUG_INFO
#ضمن <d3d9.h>

#که_تعریف_شوی D3D_DEBUG_INFO
#که_نه_تعریف_شوی D3_D_SDK_نسخه
#تعریف_کړه D3_D_SDK_نسخه (32 | 0x80000000)
#د_که_پای
#که_نه_تعریف_شوی D3_D9b_SDK_نسخه
#تعریف_کړه D3_D9b_SDK_نسخه (31 | 0x80000000)
#د_که_پای
#وإلا //
#که_نه_تعریف_شوی D3_D_SDK_نسخه
#تعریف_کړه D3_D_SDK_نسخه 32
#د_که_پای
#که_نه_تعریف_شوی D3_D9b_SDK_نسخه
#تعریف_کړه D3_D9b_SDK_نسخه 31
#د_که_پای
#د_که_پای

bool D3_D_بارول_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_بارول_Object("D3D9.DLL");
    إذا (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        تعريفنوع HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_بارول_Function(*pD3DDLL, "Direct3DCreate9Ex");
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

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_بارول_Function(*pD3DDLL, "Direct3DCreate9");
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
    إذا (!D3_D_بارول_DLL(&pD3DDLL, &pD3D)) {
        SDL_سېټ_Error("Unable to create Direct3D interface");
        أرجع -1;
    } وإلا {
        SDL_Display_معلومات *p_معلومات = SDL_Get_Display_Driver_معلومات(displayID);
        صحيح adapter_شاخص = D3DADAPTER_DEFAULT;

        إذا (!p_معلومات) {
            SDL_سېټ_Error("Invalid display index");
            adapter_شاخص = -1; // make sure we return something invalid
        } وإلا {
            حرف *displayName = WIN_String_منزل_UTF8_W(p_معلومات->DeviceName);
            بینښه صحيح شمېر = IDirect3_D9_Get_Adapter_شمېر(pD3D);
            بینښه صحيح i;
            لكل (i = 0; i < شمېر; i++) {
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
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحيح *adapter_شاخص, صحيح *output_شاخص)
{
#که_نه_تعریف_شوی HAVE_DXGI_H
    إذا (adapter_شاخص) {
        *adapter_شاخص = -1;
    }
    إذا (output_شاخص) {
        *output_شاخص = -1;
    }
    أرجع SDL_سېټ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#وإلا
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_Video_معلومات *videodata = videodevice ? videodevice->دننی : عدم;
    SDL_Display_معلومات *p_معلومات = SDL_Get_Display_Driver_معلومات(displayID);
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

    إذا (!p_معلومات) {
        أرجع SDL_سېټ_Error("Invalid display index");
    }

    إذا (!videodata || !videodata->pDXGIFactory) {
        أرجع SDL_سېټ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    طالما (*adapter_شاخص == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (*adapter_شاخص == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, p_معلومات->DeviceName) == 0) {
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
        أرجع SDL_سېټ_Error("Couldn't find matching adapter");
    }
    أرجع true;
#د_که_پای
}

SDL_SystemTheme WIN_GetSystemTheme(فراغ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_کلی;
    DWORD dwType = REG_DWORD;
    DWORD ارزښت = ~0U;
    DWORD اوږدتیا = حجم(ارزښت);

    // Technically this isn't the system theme, but it's the preference for applications
    إذا (Reg_Open_کلی_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, کلی_READ, &h_کلی) == ERROR_SUCCESS) {
        إذا (Reg_Query_ارزښت_Ex_W(h_کلی, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&ارزښت, &اوږدتیا) == ERROR_SUCCESS) {
            إذا (ارزښت == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_کلی(h_کلی);
    }
    أرجع theme;
}

bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->AreDpiAwarenessContextsEqual && معلومات->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        أرجع معلومات->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2, معلومات->GetThreadDpiAwarenessContext());
    }
#د_که_پای
    أرجع false;
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS
