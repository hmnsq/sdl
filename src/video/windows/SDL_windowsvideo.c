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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
#شامل "../SDL_vulkan_internal.h"
#اگر_ختم
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

#اگر_غیر_تعریف_شدہ __ITaskbarList3_FWD_DEFINED__
قسمتعریف ساخت ITaskbarList3 ITaskbarList3;
#اگر_ختم

#اگر_غیر_تعریف_شدہ __ITaskbarList3_INTERFACE_DEFINED__
قسمتعریف شمار TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_معمول = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

قسمتعریف شمار THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

قسمتعریف شمار THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#اگر defined(_MSC_VER)
#ہدایت warning(disable: 4103)
#اگر_ختم
#ہدایت pack(ڈالو, 8)
قسمتعریف ساخت THUMBBUTTON
{
    THUMBBUTTONMASK dw_نقاب;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

قسمتعریف ساخت THUMBBUTTON *LPTHUMBBUTTON;
#ہدایت pack(نکالو)

#اگر_غیر_تعریف_شدہ HIMAGELIST
ساخت _IMAGELIST;
قسمتعریف ساخت _IMAGELIST *HIMAGELIST;
#اگر_ختم

قسمتعریف ساخت ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, خالی **ppvObject);
    ULONG (__stdcall *جوڑو_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *جوڑو_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *سیٹ_فعال_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_کھڑکی)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *سیٹ_پیش_رفت_قدر)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_کل);
    HRESULT (__stdcall *سیٹ_پیش_رفت_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *رجسٹر_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *سیٹ_Tab_ترتیب)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_داخل_کرو_Before);
    HRESULT (__stdcall *سیٹ_Tab_فعال)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_جوڑو_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_سیٹ_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *سیٹ_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *سیٹ_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *سیٹ_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

ساخت ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#اگر_ختم // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#اگر_ختم

#اگر_تعریف_شدہ SDL_GDK_TEXTINPUT
#شامل "../gdk/SDL_gdktextinput.h"
#اگر_ختم

// #define HIGHDPI_DEBUG

// Initialization/Query functions
ساکن bool WIN_VideoInit(SDL_VideoDevice *_this);
ساکن خالی WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_پیغام_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden = true;

ساکن خالی SDLCALL UpdateWindowsRawKeyboard(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Enabled(_this, enabled);
}

ساکن خالی SDLCALL UpdateWindowsRawKeyboardNoHotkeys(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

ساکن خالی SDLCALL UpdateWindowsRawKeyboardInputsink(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

ساکن خالی SDLCALL UpdateWindowsRawMouseNoLegacy(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_قدر, false);
    WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

ساکن خالی SDLCALL Update_Windows_Enable_پیغام_Loop(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_Windows_Enable_پیغام_Loop = SDL_GetStringBoolean(new_قدر, true);
}

ساکن خالی SDLCALL UpdateWindowsEnableMenuMnemonics(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_قدر, false);
}

ساکن خالی SDLCALL Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_قدر, true);
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساکن bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD نتیجہ;
    اگر (_this->suspend_screensaver) {
        نتیجہ = سیٹ_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } ورنہ {
        نتیجہ = سیٹ_Thread_Execution_State(ES_CONTINUOUS);
    }
    اگر (نتیجہ == 0) {
        SDL_سیٹ_Error("SetThreadExecutionState() failed");
        واپس false;
    }
    واپس true;
}
#اگر_ختم

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
خارجی خالی D3D12_XBOX_GetResolution(Uint32 *چوڑائی, Uint32 *اونچائی);
#اگر_ختم

// Windows driver bootstrap functions

ساکن خالی WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;

    SDL_UnregisterApp();
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (ڈیٹا->userDLL) {
        SDL_UnloadObject(ڈیٹا->userDLL);
    }
    اگر (ڈیٹا->shcoreDLL) {
        SDL_UnloadObject(ڈیٹا->shcoreDLL);
    }
    اگر (ڈیٹا->dwmapiDLL) {
        SDL_UnloadObject(ڈیٹا->dwmapiDLL);
    }
#اگر_ختم
#اگر_تعریف_شدہ HAVE_DXGI_H
    اگر (ڈیٹا->pDXGIFactory) {
        IDXGIFactory_Release(ڈیٹا->pDXGIFactory);
    }
    اگر (ڈیٹا->dxgiDLL) {
        SDL_UnloadObject(ڈیٹا->dxgiDLL);
    }
#اگر_ختم
    SDL_free(device->اندرونی_2->rawinput);
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *WIN_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;

    SDL_رجسٹر_App(تہی, 0, تہی);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (device) {
        ڈیٹا = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    } ورنہ {
        ڈیٹا = تہی;
    }
    اگر (!ڈیٹا) {
        SDL_UnregisterApp();
        SDL_free(device);
        واپس تہی;
    }
    device->اندرونی_2 = ڈیٹا;
    device->system_theme = WIN_GetSystemTheme();

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ڈیٹا->userDLL = SDL_بھرو_Object("USER32.DLL");
    اگر (ڈیٹا->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ڈیٹا->Close_Touch_داخلہ_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_بھرو_Function(ڈیٹا->userDLL, "CloseTouchInputHandle");
        ڈیٹا->Get_Touch_داخلہ_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, صحیح)) SDL_بھرو_Function(ڈیٹا->userDLL, "GetTouchInputInfo");
        ڈیٹا->رجسٹر_Touch_کھڑکی = (BOOL (WINAPI *)(HWND, ULONG))SDL_بھرو_Function(ڈیٹا->userDLL, "RegisterTouchWindow");
        ڈیٹا->سیٹ_Process_DPIAware = (BOOL (WINAPI *)(خالی))SDL_بھرو_Function(ڈیٹا->userDLL, "SetProcessDPIAware");
        ڈیٹا->سیٹ_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بھرو_Function(ڈیٹا->userDLL, "SetProcessDpiAwarenessContext");
        ڈیٹا->سیٹ_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بھرو_Function(ڈیٹا->userDLL, "SetThreadDpiAwarenessContext");
        ڈیٹا->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(خالی))SDL_بھرو_Function(ڈیٹا->userDLL, "GetThreadDpiAwarenessContext");
        ڈیٹا->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بھرو_Function(ڈیٹا->userDLL, "GetAwarenessFromDpiAwarenessContext");
        ڈیٹا->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_بھرو_Function(ڈیٹا->userDLL, "EnableNonClientDpiScaling");
        ڈیٹا->Adjust_کھڑکی_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_بھرو_Function(ڈیٹا->userDLL, "AdjustWindowRectExForDpi");
        ڈیٹا->Get_Dpi_For_کھڑکی = (UINT (WINAPI *)(HWND))SDL_بھرو_Function(ڈیٹا->userDLL, "GetDpiForWindow");
        ڈیٹا->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_بھرو_Function(ڈیٹا->userDLL, "AreDpiAwarenessContextsEqual");
        ڈیٹا->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_بھرو_Function(ڈیٹا->userDLL, "IsValidDpiAwarenessContext");
        ڈیٹا->Get_Display_Config_بفر_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_بھرو_Function(ڈیٹا->userDLL, "GetDisplayConfigBufferSizes");
        ڈیٹا->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_راستہ_INFO*,UINT32 *,DISPLAYCONFIG_منوال_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_بھرو_Function(ڈیٹا->userDLL, "QueryDisplayConfig");
        ڈیٹا->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_سرخی*))SDL_بھرو_Function(ڈیٹا->userDLL, "DisplayConfigGetDeviceInfo");
        ڈیٹا->Get_اشارہ_گر_Type = (BOOL (WINAPI *)(UINT32, اشارہ_گر_داخلہ_TYPE *))SDL_بھرو_Function(ڈیٹا->userDLL, "GetPointerType");
        ڈیٹا->Get_اشارہ_گر_Pen_Info = (BOOL (WINAPI *)(UINT32, اشارہ_گر_PEN_INFO *))SDL_بھرو_Function(ڈیٹا->userDLL, "GetPointerPenInfo");
        ڈیٹا->Get_اشارہ_گر_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_بھرو_Function(ڈیٹا->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } ورنہ {
        SDL_ClearError();
    }

    ڈیٹا->shcoreDLL = SDL_بھرو_Object("SHCORE.DLL");
    اگر (ڈیٹا->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ڈیٹا->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_بھرو_Function(ڈیٹا->shcoreDLL, "GetDpiForMonitor");
        ڈیٹا->سیٹ_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_بھرو_Function(ڈیٹا->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } ورنہ {
        SDL_ClearError();
    }

    ڈیٹا->dwmapiDLL = SDL_بھرو_Object("DWMAPI.DLL");
    اگر (ڈیٹا->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        ڈیٹا->DwmFlush = (HRESULT (WINAPI *)(خالی))SDL_بھرو_Function(ڈیٹا->dwmapiDLL, "DwmFlush");
        ڈیٹا->Dwm_Enable_Blur_Behind_کھڑکی = (HRESULT (WINAPI *)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind))SDL_بھرو_Function(ڈیٹا->dwmapiDLL, "DwmEnableBlurBehindWindow");
        ڈیٹا->Dwm_سیٹ_کھڑکی_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_بھرو_Function(ڈیٹا->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } ورنہ {
        SDL_ClearError();
    }
#اگر_ختم // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شدہ HAVE_DXGI_H
    ڈیٹا->dxgiDLL = SDL_بھرو_Object("DXGI.DLL");
    اگر (ڈیٹا->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        قسمتعریف HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, خالی **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_بھرو_Function(ڈیٹا->dxgiDLL, "CreateDXGIFactory");
        اگر (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (خالی **)&ڈیٹا->pDXGIFactory);
        }
    }
#اگر_ختم

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->سیٹ_Display_منوال = WIN_سیٹ_Display_منوال;
#اگر_ختم
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#اگر_ختم

    device->CreateSDLWindow = WIN_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = WIN_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = WIN_سیٹ_کھڑکی_Icon;
    device->سیٹ_کھڑکی_Position = WIN_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = WIN_سیٹ_کھڑکی_سائز;
    device->Get_کھڑکی_Borders_سائز = WIN_Get_کھڑکی_Borders_سائز;
    device->Get_کھڑکی_سائز_اندر_Pixels = WIN_Get_کھڑکی_سائز_اندر_Pixels;
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
    device->سیٹ_کھڑکی_والد = WIN_سیٹ_کھڑکی_والد;
    device->سیٹ_کھڑکی_Modal = WIN_سیٹ_کھڑکی_Modal;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_کھڑکی_ICCProfile = WIN_Get_کھڑکی_ICCProfile;
    device->سیٹ_کھڑکی_Mouse_Rect = WIN_سیٹ_کھڑکی_Mouse_Rect;
    device->سیٹ_کھڑکی_Mouse_Grab = WIN_سیٹ_کھڑکی_Mouse_Grab;
    device->سیٹ_کھڑکی_Keyboard_Grab = WIN_سیٹ_کھڑکی_Keyboard_Grab;
#اگر_ختم
    device->Destroy_کھڑکی = WIN_Destroy_کھڑکی;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_کھڑکی_Framebuffer = WIN_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = WIN_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = WIN_Destroy_کھڑکی_Framebuffer;
    device->On_کھڑکی_Enter = WIN_On_کھڑکی_Enter;
    device->سیٹ_کھڑکی_کامیابی_Test = WIN_سیٹ_کھڑکی_کامیابی_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_کھڑکی = WIN_Flash_کھڑکی;
    device->Apply_کھڑکی_پیش_رفت = WIN_Apply_کھڑکی_پیش_رفت;
    device->Show_کھڑکی_System_Menu = WIN_Show_کھڑکی_System_Menu;
    device->سیٹ_کھڑکی_Focusable = WIN_سیٹ_کھڑکی_Focusable;
    device->Update_کھڑکی_Shape = WIN_Update_کھڑکی_Shape;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    device->GL_بھرو_Library = WIN_GL_بھرو_Library;
    device->GL_Get_Proc_پتہ = WIN_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = WIN_GL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = WIN_GL_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = WIN_GL_تبادلہ_کھڑکی;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = تہی;
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#اگر_ختم
        // Use EGL based functions
        device->GL_بھرو_Library = WIN_GLES_بھرو_Library;
        device->GL_Get_Proc_پتہ = WIN_GLES_Get_Proc_پتہ;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_سیٹ_تبادلہ_Interval = WIN_GLES_سیٹ_تبادلہ_Interval;
        device->GL_Get_تبادلہ_Interval = WIN_GLES_Get_تبادلہ_Interval;
        device->GL_تبادلہ_کھڑکی = WIN_GLES_تبادلہ_کھڑکی;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    }
#اگر_ختم
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = WIN_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#اگر_ختم

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->آغاز_متن_داخلہ = WIN_آغاز_متن_داخلہ;
    device->Stop_متن_داخلہ = WIN_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = WIN_Update_متن_داخلہ_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->سیٹ_Clipboard_ڈیٹا = WIN_سیٹ_Clipboard_ڈیٹا;
    device->Get_Clipboard_ڈیٹا = WIN_Get_Clipboard_ڈیٹا;
    device->Has_Clipboard_ڈیٹا = WIN_Has_Clipboard_ڈیٹا;
#اگر_ختم

#اگر_تعریف_شدہ SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->آغاز_متن_داخلہ = GDK_آغاز_متن_داخلہ;
    device->Stop_متن_داخلہ = GDK_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = GDK_Update_متن_داخلہ_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#اگر_ختم

    device->آزاد = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    واپس device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_پیغام_Box,
    #ورنہ
    تہی,
    #اگر_ختم
    false
};

ساکن BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness_Context) {
        ڈیٹا->dpi_unaware_context_declared = true;
        واپس ڈیٹا->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } ورنہ اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        واپس SUCCEEDED(ڈیٹا->سیٹ_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#اگر_ختم
    واپس FALSE;
}

ساکن BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        واپس ڈیٹا->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } ورنہ اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        واپس SUCCEEDED(ڈیٹا->سیٹ_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } ورنہ اگر (ڈیٹا->سیٹ_Process_DPIAware) {
        // Windows Vista
        واپس ڈیٹا->سیٹ_Process_DPIAware();
    }
#اگر_ختم
    واپس FALSE;
}

ساکن BOOL WIN_Declare_DPIAware_فی_Monitor(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        واپس ڈیٹا->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE);
    } ورنہ اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness) {
        // Windows 8.1
        واپس SUCCEEDED(ڈیٹا->سیٹ_Process_Dpi_Awareness(PROCESS_فی_MONITOR_DPI_AWARE));
    } ورنہ {
        // Older OS: fall back to system DPI aware
        واپس WIN_DeclareDPIAwareSystem(_this);
    }
#ورنہ
    واپس FALSE;
#اگر_ختم
}

ساکن BOOL WIN_Declare_DPIAware_فی_Monitor_V2(SDL_VideoDevice *_this)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    واپس FALSE;
#ورنہ
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness_Context) {
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
        اگر (ڈیٹا->سیٹ_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            واپس TRUE;
        } ورنہ {
            واپس WIN_Declare_DPIAware_فی_Monitor(_this);
        }
    } ورنہ {
        // Older OS: fall back to per-monitor (or system)
        واپس WIN_Declare_DPIAware_فی_Monitor(_this);
    }
#اگر_ختم
}

#اگر_تعریف_شدہ HIGHDPI_DEBUG
ساکن ثابت حرف *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->GetThreadDpiAwarenessContext && ڈیٹا->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = ڈیٹا->GetThreadDpiAwarenessContext();

        اگر (ڈیٹا->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            واپس "unaware";
        } ورنہ اگر (ڈیٹا->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            واپس "system";
        } ورنہ اگر (ڈیٹا->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE)) {
            واپس "permonitor";
        } ورنہ اگر (ڈیٹا->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            واپس "permonitorv2";
        } ورنہ اگر (ڈیٹا->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            واپس "unaware_gdiscaled";
        }
    }

    واپس "";
}
#اگر_ختم

ساکن خالی WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ثابت حرف *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    اگر (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_فی_Monitor_V2(_this);
    } ورنہ اگر (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_فی_Monitor(_this);
    } ورنہ اگر (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } ورنہ اگر (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

ساکن bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    HRESULT hr;

    hr = WIN_CoInitialize();
    اگر (SUCCEEDED(hr)) {
        ڈیٹا->coinitialized = true;

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(تہی);
        اگر (SUCCEEDED(hr)) {
            ڈیٹا->oleinitialized = true;
        } ورنہ {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (غیرعلامتی صحیح)hr);
        }
#اگر_ختم // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } ورنہ {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (غیرعلامتی صحیح)hr);
    }

    WIN_InitDPIAwareness(_this);

#اگر_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#اگر_ختم

    اگر (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_داخلہ(_this);
    }

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_منوال منوال;

        SDL_zero(منوال);
        D3D12_XBOX_GetResolution(&منوال.w, &منوال.h);
        منوال.refresh_شرح = 60.0f;
        منوال.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_جوڑو_Basic_Video_Display(&منوال);
    }
#ورنہ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!WIN_InitModes(_this)) {
        واپس false;
    }

    _this->اندرونی_2->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#اگر_ختم

    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیغام_Loop, تہی);
    SDL_جوڑو_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, تہی);
    SDL_جوڑو_Hint_Callback(SDL_HINT_کھڑکی_چوکھٹا_USABLE_WHILE_CURSOR_HIDDEN, Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden, تہی);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ڈیٹا->_SDL_WAKEUP = رجسٹر_کھڑکی_پیغام_A("_SDL_WAKEUP");
    ڈیٹا->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? رجسٹر_کھڑکی_پیغام_A("TaskbarButtonCreated") : 0;
#اگر_ختم

    واپس true;
}

خالی WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_پیغام_Loop, تہی);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, تہی);
    SDL_RemoveHintCallback(SDL_HINT_کھڑکی_چوکھٹا_USABLE_WHILE_CURSOR_HIDDEN, Update_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden, تہی);

    WIN_Quit_Raw_داخلہ(_this);
    WIN_Quit_Game_داخلہ(_this);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    اگر (ڈیٹا->taskbar_list) {
        ڈیٹا->taskbar_list->lpVtbl->Release(ڈیٹا->taskbar_list);
        ڈیٹا->taskbar_list = تہی;
    }

    اگر (ڈیٹا->oleinitialized) {
        OleUninitialize();
        ڈیٹا->oleinitialized = false;
    }
#اگر_ختم // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    اگر (ڈیٹا->coinitialized) {
        WIN_CoUninitialize();
        ڈیٹا->coinitialized = false;
    }
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#تعریف_کرو D3D_DEBUG_INFO
#شامل <d3d9.h>

#اگر_تعریف_شدہ D3D_DEBUG_INFO
#اگر_غیر_تعریف_شدہ D3_D_SDK_نسخہ
#تعریف_کرو D3_D_SDK_نسخہ (32 | 0x80000000)
#اگر_ختم
#اگر_غیر_تعریف_شدہ D3_D9b_SDK_نسخہ
#تعریف_کرو D3_D9b_SDK_نسخہ (31 | 0x80000000)
#اگر_ختم
#ورنہ //
#اگر_غیر_تعریف_شدہ D3_D_SDK_نسخہ
#تعریف_کرو D3_D_SDK_نسخہ 32
#اگر_ختم
#اگر_غیر_تعریف_شدہ D3_D9b_SDK_نسخہ
#تعریف_کرو D3_D9b_SDK_نسخہ 31
#اگر_ختم
#اگر_ختم

bool D3_D_بھرو_DLL(خالی **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_بھرو_Object("D3D9.DLL");
    اگر (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        قسمتعریف IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        قسمتعریف HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        اگر (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_بھرو_Function(*pD3DDLL, "Direct3DCreate9Ex");
            اگر (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_نسخہ, &pDirect3D9ExInterface);
                اگر (SUCCEEDED(hr)) {
                    ثابت GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (خالی **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    اگر (SUCCEEDED(hr)) {
                        واپس true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_بھرو_Function(*pD3DDLL, "Direct3DCreate9");
        اگر (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_نسخہ);
            اگر (*pDirect3D9Interface) {
                واپس true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = تہی;
    }
    *pDirect3D9Interface = تہی;
    واپس false;
}

صحیح SDL_Get_Direct3_D9_Adapter_اشاریہ(SDL_DisplayID displayID)
{
    خالی *pD3DDLL;
    IDirect3D9 *pD3D;
    اگر (!D3_D_بھرو_DLL(&pD3DDLL, &pD3D)) {
        SDL_سیٹ_Error("Unable to create Direct3D interface");
        واپس -1;
    } ورنہ {
        SDL_Display_ڈیٹا *p_ڈیٹا = SDL_Get_Display_Driver_ڈیٹا(displayID);
        صحیح adapter_اشاریہ = D3DADAPTER_DEFAULT;

        اگر (!p_ڈیٹا) {
            SDL_سیٹ_Error("Invalid display index");
            adapter_اشاریہ = -1; // make sure we return something invalid
        } ورنہ {
            حرف *displayName = WIN_String_مقصد_UTF8_W(p_ڈیٹا->DeviceName);
            غیرعلامتی صحیح گنتی = IDirect3_D9_Get_Adapter_گنتی(pD3D);
            غیرعلامتی صحیح i;
            برائے (i = 0; i < گنتی; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                اگر (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_اشاریہ = i;
                    توڑو;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        واپس adapter_اشاریہ;
    }
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحیح *adapter_اشاریہ, صحیح *output_اشاریہ)
{
#اگر_غیر_تعریف_شدہ HAVE_DXGI_H
    اگر (adapter_اشاریہ) {
        *adapter_اشاریہ = -1;
    }
    اگر (output_اشاریہ) {
        *output_اشاریہ = -1;
    }
    واپس SDL_سیٹ_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#ورنہ
    ثابت SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ثابت SDL_Video_ڈیٹا *videodata = videodevice ? videodevice->اندرونی_2 : تہی;
    SDL_Display_ڈیٹا *p_ڈیٹا = SDL_Get_Display_Driver_ڈیٹا(displayID);
    صحیح nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_اشاریہ) {
        واپس SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_اشاریہ) {
        واپس SDL_InvalidParamError("outputIndex");
    }

    *adapter_اشاریہ = -1;
    *output_اشاریہ = -1;

    اگر (!p_ڈیٹا) {
        واپس SDL_سیٹ_Error("Invalid display index");
    }

    اگر (!videodata || !videodata->pDXGIFactory) {
        واپس SDL_سیٹ_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    جب (*adapter_اشاریہ == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        جب (*adapter_اشاریہ == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            اگر (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                اگر (SDL_wcscmp(outputDesc.DeviceName, p_ڈیٹا->DeviceName) == 0) {
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

    اگر (*adapter_اشاریہ == -1) {
        واپس SDL_سیٹ_Error("Couldn't find matching adapter");
    }
    واپس true;
#اگر_ختم
}

SDL_SystemTheme WIN_GetSystemTheme(خالی)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_کلید;
    DWORD dwType = REG_DWORD;
    DWORD قدر = ~0U;
    DWORD لمبائی = حجم(قدر);

    // Technically this isn't the system theme, but it's the preference for applications
    اگر (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, کلید_READ, &h_کلید) == ERROR_SUCCESS) {
        اگر (Reg_Query_قدر_Ex_W(h_کلید, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&قدر, &لمبائی) == ERROR_SUCCESS) {
            اگر (قدر == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_کلید(h_کلید);
    }
    واپس theme;
}

bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->AreDpiAwarenessContextsEqual && ڈیٹا->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        واپس ڈیٹا->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2, ڈیٹا->GetThreadDpiAwarenessContext());
    }
#اگر_ختم
    واپس false;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
