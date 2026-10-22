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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

#جے_تعریف_شدہ SDL_VIDEO_VULKAN
#ضمن "../SDL_vulkan_internal.h"
#جے_انت
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

#جے_بنا_تعریف __ITaskbarList3_FWD_DEFINED__
تعريفنوع بنية ITaskbarList3 ITaskbarList3;
#جے_انت

#جے_بنا_تعریف __ITaskbarList3_INTERFACE_DEFINED__
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
#ہدایت warning(disable: 4103)
#جے_انت
#ہدایت pack(ڈالو, 8)
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
#ہدایت pack(نکالو)

#جے_بنا_تعریف HIMAGELIST
بنية _IMAGELIST;
تعريفنوع بنية _IMAGELIST *HIMAGELIST;
#جے_انت

تعريفنوع بنية ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, فراغ **ppvObject);
    ULONG (__stdcall *جوڑو_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *جوڑو_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *سیٹ_سرگرم_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_کھڑکی)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *سیٹ_ترقی_قدر)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_کل);
    HRESULT (__stdcall *سیٹ_ترقی_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *رجسٹر_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *سیٹ_Tab_ترتیب)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_داخل_کرو_Before);
    HRESULT (__stdcall *سیٹ_Tab_سرگرم)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_جوڑو_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_سیٹ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *سیٹ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *سیٹ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *سیٹ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

بنية ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#جے_انت // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#جے_انت

#جے_تعریف_شدہ SDL_GDK_TEXTINPUT
#ضمن "../gdk/SDL_gdktextinput.h"
#جے_انت

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ساكن bool WIN_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_سنیہا_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden = true;

ساكن فراغ SDLCALL UpdateWindowsRawKeyboard(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Enabled(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardNoHotkeys(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawKeyboardInputsink(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ساكن فراغ SDLCALL UpdateWindowsRawMouseNoLegacy(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ساكن فراغ SDLCALL Update_Windows_Enable_سنیہا_Loop(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_Windows_Enable_سنیہا_Loop = SDL_GetStringBoolean(new_قدر, true);
}

ساكن فراغ SDLCALL UpdateWindowsEnableMenuMnemonics(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_قدر, false);
}

ساكن فراغ SDLCALL Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_قدر, true);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD نتیجہ;
    إذا (_this->suspend_screensaver) {
        نتیجہ = سیٹ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } وإلا {
        نتیجہ = سیٹ_Thread_Execution_State(ES_CONTINUOUS);
    }
    إذا (نتیجہ == 0) {
        SDL_سیٹ_Error("SetThreadExecutionState() failed");
        أرجع false;
    }
    أرجع true;
}
#جے_انت

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
خارجي فراغ D3D12_XBOX_GetResolution(Uint32 *چوڑائی, Uint32 *اچائی);
#جے_انت

// Windows driver bootstrap functions

ساكن فراغ WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_انکڑے *انکڑے = device->اندرونی;

    SDL_UnregisterApp();
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (انکڑے->userDLL) {
        SDL_UnloadObject(انکڑے->userDLL);
    }
    إذا (انکڑے->shcoreDLL) {
        SDL_UnloadObject(انکڑے->shcoreDLL);
    }
    إذا (انکڑے->dwmapiDLL) {
        SDL_UnloadObject(انکڑے->dwmapiDLL);
    }
#جے_انت
#جے_تعریف_شدہ HAVE_DXGI_H
    إذا (انکڑے->pDXGIFactory) {
        IDXGIFactory_Release(انکڑے->pDXGIFactory);
    }
    إذا (انکڑے->dxgiDLL) {
        SDL_UnloadObject(انکڑے->dxgiDLL);
    }
#جے_انت
    SDL_free(device->اندرونی->rawinput);
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *WIN_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *انکڑے;

    SDL_رجسٹر_App(عدم, 0, عدم);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        انکڑے = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    } وإلا {
        انکڑے = عدم;
    }
    إذا (!انکڑے) {
        SDL_UnregisterApp();
        SDL_free(device);
        أرجع عدم;
    }
    device->اندرونی = انکڑے;
    device->system_theme = WIN_GetSystemTheme();

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    انکڑے->userDLL = SDL_لدو_Object("USER32.DLL");
    إذا (انکڑے->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        انکڑے->Close_Touch_داخلہ_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_لدو_Function(انکڑے->userDLL, "CloseTouchInputHandle");
        انکڑے->Get_Touch_داخلہ_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح)) SDL_لدو_Function(انکڑے->userDLL, "GetTouchInputInfo");
        انکڑے->رجسٹر_Touch_کھڑکی = (BOOL (WINAPI *)(HWND, ULONG))SDL_لدو_Function(انکڑے->userDLL, "RegisterTouchWindow");
        انکڑے->سیٹ_Process_DPIAware = (BOOL (WINAPI *)(فراغ))SDL_لدو_Function(انکڑے->userDLL, "SetProcessDPIAware");
        انکڑے->سیٹ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_لدو_Function(انکڑے->userDLL, "SetProcessDpiAwarenessContext");
        انکڑے->سیٹ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_لدو_Function(انکڑے->userDLL, "SetThreadDpiAwarenessContext");
        انکڑے->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(فراغ))SDL_لدو_Function(انکڑے->userDLL, "GetThreadDpiAwarenessContext");
        انکڑے->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_لدو_Function(انکڑے->userDLL, "GetAwarenessFromDpiAwarenessContext");
        انکڑے->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_لدو_Function(انکڑے->userDLL, "EnableNonClientDpiScaling");
        انکڑے->Adjust_کھڑکی_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_لدو_Function(انکڑے->userDLL, "AdjustWindowRectExForDpi");
        انکڑے->Get_Dpi_For_کھڑکی = (UINT (WINAPI *)(HWND))SDL_لدو_Function(انکڑے->userDLL, "GetDpiForWindow");
        انکڑے->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_لدو_Function(انکڑے->userDLL, "AreDpiAwarenessContextsEqual");
        انکڑے->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_لدو_Function(انکڑے->userDLL, "IsValidDpiAwarenessContext");
        انکڑے->Get_Display_Config_بفر_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_لدو_Function(انکڑے->userDLL, "GetDisplayConfigBufferSizes");
        انکڑے->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_رستہ_INFO*,UINT32 *,DISPLAYCONFIG_منوال_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_لدو_Function(انکڑے->userDLL, "QueryDisplayConfig");
        انکڑے->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_سرخی*))SDL_لدو_Function(انکڑے->userDLL, "DisplayConfigGetDeviceInfo");
        انکڑے->Get_اشارہ_گر_Type = (BOOL (WINAPI *)(UINT32, اشارہ_گر_داخلہ_TYPE *))SDL_لدو_Function(انکڑے->userDLL, "GetPointerType");
        انکڑے->Get_اشارہ_گر_Pen_Info = (BOOL (WINAPI *)(UINT32, اشارہ_گر_PEN_INFO *))SDL_لدو_Function(انکڑے->userDLL, "GetPointerPenInfo");
        انکڑے->Get_اشارہ_گر_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_لدو_Function(انکڑے->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    انکڑے->shcoreDLL = SDL_لدو_Object("SHCORE.DLL");
    إذا (انکڑے->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        انکڑے->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_لدو_Function(انکڑے->shcoreDLL, "GetDpiForMonitor");
        انکڑے->سیٹ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_لدو_Function(انکڑے->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }

    انکڑے->dwmapiDLL = SDL_لدو_Object("DWMAPI.DLL");
    إذا (انکڑے->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        انکڑے->DwmFlush = (HRESULT (WINAPI *)(فراغ))SDL_لدو_Function(انکڑے->dwmapiDLL, "DwmFlush");
        انکڑے->Dwm_Enable_Blur_Behind_کھڑکی = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_لدو_Function(انکڑے->dwmapiDLL, "DwmEnableBlurBehindWindow");
        انکڑے->Dwm_سیٹ_کھڑکی_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_لدو_Function(انکڑے->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } وإلا {
        SDL_ClearError();
    }
#جے_انت // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جے_تعریف_شدہ HAVE_DXGI_H
    انکڑے->dxgiDLL = SDL_لدو_Object("DXGI.DLL");
    إذا (انکڑے->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, فراغ **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_لدو_Function(انکڑے->dxgiDLL, "CreateDXGIFactory");
        إذا (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (فراغ **)&انکڑے->pDXGIFactory);
        }
    }
#جے_انت

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->سیٹ_Display_منوال = WIN_سیٹ_Display_منوال;
#جے_انت
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#جے_انت

    device->CreateSDLWindow = WIN_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = WIN_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = WIN_سیٹ_کھڑکی_Icon;
    device->سیٹ_کھڑکی_Position = WIN_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = WIN_سیٹ_کھڑکی_ناپ;
    device->Get_کھڑکی_Borders_ناپ = WIN_Get_کھڑکی_Borders_ناپ;
    device->Get_کھڑکی_ناپ_وچ_Pixels = WIN_Get_کھڑکی_ناپ_وچ_Pixels;
    device->سیٹ_کھڑکی_Opacity = WIN_سیٹ_کھڑکی_Opacity;
    device->Show_کھڑکی = WIN_Show_کھڑکی;
    device->Hide_کھڑکی = WIN_Hide_کھڑکی;
    device->Raise_کھڑکی = WIN_Raise_کھڑکی;
    device->Maximize_کھڑکی = WIN_Maximize_کھڑکی;
    device->Minimize_کھڑکی = WIN_Minimize_کھڑکی;
    device->Restore_کھڑکی = WIN_Restore_کھڑکی;
    device->سیٹ_کھڑکی_Bordered = WIN_سیٹ_کھڑکی_Bordered;
    device->سیٹ_کھڑکی_Resizable = WIN_سیٹ_کھڑکی_Resizable;
    device->سیٹ_کھڑکی_Always_On_چوٹی = WIN_سیٹ_کھڑکی_Always_On_چوٹی;
    device->سیٹ_کھڑکی_Fullscreen = WIN_سیٹ_کھڑکی_Fullscreen;
    device->سیٹ_کھڑکی_ماپا = WIN_سیٹ_کھڑکی_ماپا;
    device->سیٹ_کھڑکی_Modal = WIN_سیٹ_کھڑکی_Modal;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_کھڑکی_ICCProfile = WIN_Get_کھڑکی_ICCProfile;
    device->سیٹ_کھڑکی_Mouse_Rect = WIN_سیٹ_کھڑکی_Mouse_Rect;
    device->سیٹ_کھڑکی_Mouse_Grab = WIN_سیٹ_کھڑکی_Mouse_Grab;
    device->سیٹ_کھڑکی_Keyboard_Grab = WIN_سیٹ_کھڑکی_Keyboard_Grab;
#جے_انت
    device->Destroy_کھڑکی = WIN_Destroy_کھڑکی;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_کھڑکی_Framebuffer = WIN_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = WIN_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = WIN_Destroy_کھڑکی_Framebuffer;
    device->On_کھڑکی_Enter = WIN_On_کھڑکی_Enter;
    device->سیٹ_کھڑکی_کامیابی_Test = WIN_سیٹ_کھڑکی_کامیابی_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_کھڑکی = WIN_Flash_کھڑکی;
    device->Apply_کھڑکی_ترقی = WIN_Apply_کھڑکی_ترقی;
    device->Show_کھڑکی_System_Menu = WIN_Show_کھڑکی_System_Menu;
    device->سیٹ_کھڑکی_Focusable = WIN_سیٹ_کھڑکی_Focusable;
    device->Update_کھڑکی_Shape = WIN_Update_کھڑکی_Shape;
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    device->GL_لدو_Library = WIN_GL_لدو_Library;
    device->GL_Get_Proc_پتہ = WIN_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = WIN_GL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = WIN_GL_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = WIN_GL_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#جے_انت
        // Use EGL based functions
        device->GL_لدو_Library = WIN_GLES_لدو_Library;
        device->GL_Get_Proc_پتہ = WIN_GLES_Get_Proc_پتہ;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_سیٹ_وٹاندرا_Interval = WIN_GLES_سیٹ_وٹاندرا_Interval;
        device->GL_Get_وٹاندرا_Interval = WIN_GLES_Get_وٹاندرا_Interval;
        device->GL_وٹاندرا_کھڑکی = WIN_GLES_وٹاندرا_کھڑکی;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    }
#جے_انت
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_لدو_Library = WIN_Vulkan_لدو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#جے_انت

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->شروع_متن_داخلہ = WIN_شروع_متن_داخلہ;
    device->Stop_متن_داخلہ = WIN_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = WIN_Update_متن_داخلہ_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->سیٹ_Clipboard_انکڑے = WIN_سیٹ_Clipboard_انکڑے;
    device->Get_Clipboard_انکڑے = WIN_Get_Clipboard_انکڑے;
    device->Has_Clipboard_انکڑے = WIN_Has_Clipboard_انکڑے;
#جے_انت

#جے_تعریف_شدہ SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->شروع_متن_داخلہ = GDK_شروع_متن_داخلہ;
    device->Stop_متن_داخلہ = GDK_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = GDK_Update_متن_داخلہ_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#جے_انت

    device->حرر = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_سنیہا_Box,
    #وإلا
    عدم,
    #جے_انت
    false
};

ساكن BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->سیٹ_Process_Dpi_Awareness_Context) {
        انکڑے->dpi_unaware_context_declared = true;
        أرجع انکڑے->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } وإلا إذا (انکڑے->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(انکڑے->سیٹ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#جے_انت
    أرجع FALSE;
}

ساكن BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->سیٹ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع انکڑے->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } وإلا إذا (انکڑے->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(انکڑے->سیٹ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } وإلا إذا (انکڑے->سیٹ_Process_DPIAware) {
        // Windows Vista
        أرجع انکڑے->سیٹ_Process_DPIAware();
    }
#جے_انت
    أرجع FALSE;
}

ساكن BOOL WIN_Declare_DPIAware_فی_Monitor(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->سیٹ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        أرجع انکڑے->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE);
    } وإلا إذا (انکڑے->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        أرجع SUCCEEDED(انکڑے->سیٹ_Process_Dpi_Awareness(PROCESS_فی_MONITOR_DPI_AWARE));
    } وإلا {
        // Older OS: fall back to system DPI aware
        أرجع WIN_DeclareDPIAwareSystem(_this);
    }
#وإلا
    أرجع FALSE;
#جے_انت
}

ساكن BOOL WIN_Declare_DPIAware_فی_Monitor_V2(SDL_VideoDevice *_this)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع FALSE;
#وإلا
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    إذا (انکڑے->سیٹ_Process_Dpi_Awareness_Context) {
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
        إذا (انکڑے->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            أرجع TRUE;
        } وإلا {
            أرجع WIN_Declare_DPIAware_فی_Monitor(_this);
        }
    } وإلا {
        // Older OS: fall back to per-monitor (or system)
        أرجع WIN_Declare_DPIAware_فی_Monitor(_this);
    }
#جے_انت
}

#جے_تعریف_شدہ HIGHDPI_DEBUG
ساكن ثابت حرف *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->GetThreadDpiAwarenessContext && انکڑے->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = انکڑے->GetThreadDpiAwarenessContext();

        إذا (انکڑے->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            أرجع "unaware";
        } وإلا إذا (انکڑے->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            أرجع "system";
        } وإلا إذا (انکڑے->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE)) {
            أرجع "permonitor";
        } وإلا إذا (انکڑے->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            أرجع "permonitorv2";
        } وإلا إذا (انکڑے->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            أرجع "unaware_gdiscaled";
        }
    }

    أرجع "";
}
#جے_انت

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
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    HRESULT hr;

    hr = WIN_CoInitialize();
    إذا (SUCCEEDED(hr)) {
        انکڑے->coinitialized = true;

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(عدم);
        إذا (SUCCEEDED(hr)) {
            انکڑے->oleinitialized = true;
        } وإلا {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بنانشانی صحيح)hr);
        }
#جے_انت // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } وإلا {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (بنانشانی صحيح)hr);
    }

    WIN_InitDPIAwareness(_this);

#جے_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#جے_انت

    إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_داخلہ(_this);
    }

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_منوال منوال;

        SDL_zero(منوال);
        D3D12_XBOX_GetResolution(&منوال.w, &منوال.h);
        منوال.refresh_شرح = 60.0f;
        منوال.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_جوڑو_Basic_Video_Display(&منوال);
    }
#وإلا // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!WIN_InitModes(_this)) {
        أرجع false;
    }

    _this->اندرونی->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#جے_انت

    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_سنیہا_Loop, عدم);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_جوڑو_Hint_Callback(SDL_HINT_کھڑکی_چوکھٹا_USABLE_WHILE_CURSOR_HIDDEN, Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden, عدم);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    انکڑے->_SDL_WAKEUP = رجسٹر_کھڑکی_سنیہا_A("_SDL_WAKEUP");
    انکڑے->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? رجسٹر_کھڑکی_سنیہا_A("TaskbarButtonCreated") : 0;
#جے_انت

    أرجع true;
}

فراغ WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_سنیہا_Loop, عدم);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, عدم);
    SDL_RemoveHintCallback(SDL_HINT_کھڑکی_چوکھٹا_USABLE_WHILE_CURSOR_HIDDEN, Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden, عدم);

    WIN_Quit_Raw_داخلہ(_this);
    WIN_Quit_Game_داخلہ(_this);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    إذا (انکڑے->taskbar_list) {
        انکڑے->taskbar_list->lpVtbl->Release(انکڑے->taskbar_list);
        انکڑے->taskbar_list = عدم;
    }

    إذا (انکڑے->oleinitialized) {
        OleUninitialize();
        انکڑے->oleinitialized = false;
    }
#جے_انت // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    إذا (انکڑے->coinitialized) {
        WIN_CoUninitialize();
        انکڑے->coinitialized = false;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کرو D3D_DEBUG_INFO
#ضمن <d3d9.h>

#جے_تعریف_شدہ D3D_DEBUG_INFO
#جے_بنا_تعریف D3_D_SDK_نسخہ
#تعریف_کرو D3_D_SDK_نسخہ (32 | 0x80000000)
#جے_انت
#جے_بنا_تعریف D3_D9b_SDK_نسخہ
#تعریف_کرو D3_D9b_SDK_نسخہ (31 | 0x80000000)
#جے_انت
#وإلا //
#جے_بنا_تعریف D3_D_SDK_نسخہ
#تعریف_کرو D3_D_SDK_نسخہ 32
#جے_انت
#جے_بنا_تعریف D3_D9b_SDK_نسخہ
#تعریف_کرو D3_D9b_SDK_نسخہ 31
#جے_انت
#جے_انت

bool D3_D_لدو_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_لدو_Object("D3D9.DLL");
    إذا (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        تعريفنوع IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        تعريفنوع HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        إذا (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_لدو_Function(*pD3DDLL, "Direct3DCreate9Ex");
            إذا (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_نسخہ, &pDirect3D9ExInterface);
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

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_لدو_Function(*pD3DDLL, "Direct3DCreate9");
        إذا (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_نسخہ);
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

صحيح SDL_Get_Direct3_D9_Adapter_اشاریہ(SDL_DisplayID displayID)
{
    فراغ *pD3DDLL;
    IDirect3D9 *pD3D;
    إذا (!D3_D_لدو_DLL(&pD3DDLL, &pD3D)) {
        SDL_سیٹ_Error("Unable to create Direct3D interface");
        أرجع -1;
    } وإلا {
        SDL_Display_انکڑے *p_انکڑے = SDL_Get_Display_Driver_انکڑے(displayID);
        صحيح adapter_اشاریہ = D3DADAPTER_DEFAULT;

        إذا (!p_انکڑے) {
            SDL_سیٹ_Error("Invalid display index");
            adapter_اشاریہ = -1; // make sure we return something invalid
        } وإلا {
            حرف *displayName = WIN_String_منزل_UTF8_W(p_انکڑے->DeviceName);
            بنانشانی صحيح گنتی = IDirect3_D9_Get_Adapter_گنتی(pD3D);
            بنانشانی صحيح i;
            لكل (i = 0; i < گنتی; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                إذا (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_اشاریہ = i;
                    اكسر;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        أرجع adapter_اشاریہ;
    }
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحيح *adapter_اشاریہ, صحيح *output_اشاریہ)
{
#جے_بنا_تعریف HAVE_DXGI_H
    إذا (adapter_اشاریہ) {
        *adapter_اشاریہ = -1;
    }
    إذا (output_اشاریہ) {
        *output_اشاریہ = -1;
    }
    أرجع SDL_سیٹ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#وإلا
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_Video_انکڑے *videodata = videodevice ? videodevice->اندرونی : عدم;
    SDL_Display_انکڑے *p_انکڑے = SDL_Get_Display_Driver_انکڑے(displayID);
    صحيح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_اشاریہ) {
        أرجع SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_اشاریہ) {
        أرجع SDL_InvalidParamError("outputIndex");
    }

    *adapter_اشاریہ = -1;
    *output_اشاریہ = -1;

    إذا (!p_انکڑے) {
        أرجع SDL_سیٹ_Error("Invalid display index");
    }

    إذا (!videodata || !videodata->pDXGIFactory) {
        أرجع SDL_سیٹ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    طالما (*adapter_اشاریہ == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        طالما (*adapter_اشاریہ == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            إذا (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                إذا (SDL_wcscmp(outputDesc.DeviceName, p_انکڑے->DeviceName) == 0) {
                    *adapter_اشاریہ = nAdapter;
                    *output_اشاریہ = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    إذا (*adapter_اشاریہ == -1) {
        أرجع SDL_سیٹ_Error("Couldn't find matching adapter");
    }
    أرجع true;
#جے_انت
}

SDL_SystemTheme WIN_GetSystemTheme(فراغ)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_کلید;
    DWORD dwType = REG_DWORD;
    DWORD قدر = ~0U;
    DWORD لمائی = حجم(قدر);

    // Technically this isn't the system theme, but it's the preference for applications
    إذا (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, کلید_READ, &h_کلید) == ERROR_SUCCESS) {
        إذا (Reg_Query_قدر_Ex_W(h_کلید, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&قدر, &لمائی) == ERROR_SUCCESS) {
            إذا (قدر == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_کلید(h_کلید);
    }
    أرجع theme;
}

bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->AreDpiAwarenessContextsEqual && انکڑے->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        أرجع انکڑے->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2, انکڑے->GetThreadDpiAwarenessContext());
    }
#جے_انت
    أرجع false;
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS
