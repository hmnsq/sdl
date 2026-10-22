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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
#अन्तर्भाव "../SDL_vulkan_internal.h"
#यदि_अन्तः
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../SDL_hints_c.h"
#अन्तर्भाव "../../core/windows/SDL_hid.h"

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowsframebuffer.h"
#अन्तर्भाव "SDL_windowsmessagebox.h"
#अन्तर्भाव "SDL_windowsrawinput.h"
#अन्तर्भाव "SDL_windowsvulkan.h"

#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#अन्तर्भाव <shobjidl.h>

#यदि_अपरिभाषितम् __ITaskbarList3_FWD_DEFINED__
प्रकारनिर्देश संरचना ITaskbarList3 ITaskbarList3;
#यदि_अन्तः

#यदि_अपरिभाषितम् __ITaskbarList3_INTERFACE_DEFINED__
प्रकारनिर्देश गणना TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_प्रसामान्यम् = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

प्रकारनिर्देश गणना THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

प्रकारनिर्देश गणना THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#यदि defined(_MSC_VER)
#निर्देशः warning(disable: 4103)
#यदि_अन्तः
#निर्देशः pack(प्रक्षिप, 8)
प्रकारनिर्देश संरचना THUMBBUTTON
{
    THUMBBUTTONMASK dw_आवरणम्;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

प्रकारनिर्देश संरचना THUMBBUTTON *LPTHUMBBUTTON;
#निर्देशः pack(निष्कासय)

#यदि_अपरिभाषितम् HIMAGELIST
संरचना _IMAGELIST;
प्रकारनिर्देश संरचना _IMAGELIST *HIMAGELIST;
#यदि_अन्तः

प्रकारनिर्देश संरचना ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, शून्य **ppvObject);
    ULONG (__stdcall *सङ्कलय_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *सङ्कलय_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *समुच्चयः_सक्रिय_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_गवाक्षः)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *समुच्चयः_प्रगतिः_मानम्)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_योग);
    HRESULT (__stdcall *समुच्चयः_प्रगतिः_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *पञ्जिकाकोशः_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *समुच्चयः_Tab_क्रमः)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_निवेशय_Before);
    HRESULT (__stdcall *समुच्चयः_Tab_सक्रिय)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_सङ्कलय_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_समुच्चयः_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *समुच्चयः_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *समुच्चयः_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *समुच्चयः_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

संरचना ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#यदि_अन्तः // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#यदि_अन्तः

#यदि_परिभाषितम् SDL_GDK_TEXTINPUT
#अन्तर्भाव "../gdk/SDL_gdktextinput.h"
#यदि_अन्तः

// #define HIGHDPI_DEBUG

// Initialization/Query functions
स्थिर bool WIN_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_सन्देशः_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_गवाक्षः_Frame_Usable_While_Cursor_Hidden = true;

स्थिर शून्य SDLCALL UpdateWindowsRawKeyboard(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मानम्, false);
    WIN_समुच्चयः_Raw_Keyboard_Enabled(_this, enabled);
}

स्थिर शून्य SDLCALL UpdateWindowsRawKeyboardNoHotkeys(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मानम्, false);
    WIN_समुच्चयः_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

स्थिर शून्य SDLCALL UpdateWindowsRawKeyboardInputsink(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मानम्, false);
    WIN_समुच्चयः_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

स्थिर शून्य SDLCALL UpdateWindowsRawMouseNoLegacy(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_मानम्, false);
    WIN_समुच्चयः_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

स्थिर शून्य SDLCALL Update_Windows_Enable_सन्देशः_Loop(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    g_Windows_Enable_सन्देशः_Loop = SDL_GetStringBoolean(new_मानम्, true);
}

स्थिर शून्य SDLCALL UpdateWindowsEnableMenuMnemonics(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_मानम्, false);
}

स्थिर शून्य SDLCALL Update_गवाक्षः_Frame_Usable_While_Cursor_Hidden(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    g_गवाक्षः_Frame_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_मानम्, true);
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD परिणाम;
    यदि (_this->suspend_screensaver) {
        परिणाम = समुच्चयः_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } अन्यथा {
        परिणाम = समुच्चयः_Thread_Execution_State(ES_CONTINUOUS);
    }
    यदि (परिणाम == 0) {
        SDL_समुच्चयः_Error("SetThreadExecutionState() failed");
        प्रत्यागम false;
    }
    प्रत्यागम true;
}
#यदि_अन्तः

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
बाह्य शून्य D3D12_XBOX_GetResolution(Uint32 *विस्तारः, Uint32 *height);
#यदि_अन्तः

// Windows driver bootstrap functions

स्थिर शून्य WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;

    SDL_UnregisterApp();
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (दत्त->userDLL) {
        SDL_UnloadObject(दत्त->userDLL);
    }
    यदि (दत्त->shcoreDLL) {
        SDL_UnloadObject(दत्त->shcoreDLL);
    }
    यदि (दत्त->dwmapiDLL) {
        SDL_UnloadObject(दत्त->dwmapiDLL);
    }
#यदि_अन्तः
#यदि_परिभाषितम् HAVE_DXGI_H
    यदि (दत्त->pDXGIFactory) {
        IDXGIFactory_Release(दत्त->pDXGIFactory);
    }
    यदि (दत्त->dxgiDLL) {
        SDL_UnloadObject(दत्त->dxgiDLL);
    }
#यदि_अन्तः
    SDL_free(device->आन्तरिकम्->rawinput);
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *WIN_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;

    SDL_पञ्जिकाकोशः_App(रिक्त, 0, रिक्त);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (device) {
        दत्त = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    } अन्यथा {
        दत्त = रिक्त;
    }
    यदि (!दत्त) {
        SDL_UnregisterApp();
        SDL_free(device);
        प्रत्यागम रिक्त;
    }
    device->आन्तरिकम् = दत्त;
    device->system_theme = WIN_GetSystemTheme();

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    दत्त->userDLL = SDL_आरोपय_Object("USER32.DLL");
    यदि (दत्त->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        दत्त->Close_Touch_निवेशः_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_आरोपय_Function(दत्त->userDLL, "CloseTouchInputHandle");
        दत्त->Get_Touch_निवेशः_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, पूर्णाङ्क)) SDL_आरोपय_Function(दत्त->userDLL, "GetTouchInputInfo");
        दत्त->पञ्जिकाकोशः_Touch_गवाक्षः = (BOOL (WINAPI *)(HWND, ULONG))SDL_आरोपय_Function(दत्त->userDLL, "RegisterTouchWindow");
        दत्त->समुच्चयः_Process_DPIAware = (BOOL (WINAPI *)(शून्य))SDL_आरोपय_Function(दत्त->userDLL, "SetProcessDPIAware");
        दत्त->समुच्चयः_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_आरोपय_Function(दत्त->userDLL, "SetProcessDpiAwarenessContext");
        दत्त->समुच्चयः_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_आरोपय_Function(दत्त->userDLL, "SetThreadDpiAwarenessContext");
        दत्त->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(शून्य))SDL_आरोपय_Function(दत्त->userDLL, "GetThreadDpiAwarenessContext");
        दत्त->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_आरोपय_Function(दत्त->userDLL, "GetAwarenessFromDpiAwarenessContext");
        दत्त->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_आरोपय_Function(दत्त->userDLL, "EnableNonClientDpiScaling");
        दत्त->Adjust_गवाक्षः_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_आरोपय_Function(दत्त->userDLL, "AdjustWindowRectExForDpi");
        दत्त->Get_Dpi_For_गवाक्षः = (UINT (WINAPI *)(HWND))SDL_आरोपय_Function(दत्त->userDLL, "GetDpiForWindow");
        दत्त->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_आरोपय_Function(दत्त->userDLL, "AreDpiAwarenessContextsEqual");
        दत्त->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_आरोपय_Function(दत्त->userDLL, "IsValidDpiAwarenessContext");
        दत्त->Get_Display_Config_बफर_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_आरोपय_Function(दत्त->userDLL, "GetDisplayConfigBufferSizes");
        दत्त->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_मार्गः_INFO*,UINT32 *,DISPLAYCONFIG_बहुलकम्_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_आरोपय_Function(दत्त->userDLL, "QueryDisplayConfig");
        दत्त->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_शीर्षकम्*))SDL_आरोपय_Function(दत्त->userDLL, "DisplayConfigGetDeviceInfo");
        दत्त->GetPointerType = (BOOL (WINAPI *)(UINT32, POINTER_निवेशः_TYPE *))SDL_आरोपय_Function(दत्त->userDLL, "GetPointerType");
        दत्त->GetPointerPenInfo = (BOOL (WINAPI *)(UINT32, POINTER_PEN_INFO *))SDL_आरोपय_Function(दत्त->userDLL, "GetPointerPenInfo");
        दत्त->GetPointerDeviceRects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_आरोपय_Function(दत्त->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }

    दत्त->shcoreDLL = SDL_आरोपय_Object("SHCORE.DLL");
    यदि (दत्त->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        दत्त->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_आरोपय_Function(दत्त->shcoreDLL, "GetDpiForMonitor");
        दत्त->समुच्चयः_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_आरोपय_Function(दत्त->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }

    दत्त->dwmapiDLL = SDL_आरोपय_Object("DWMAPI.DLL");
    यदि (दत्त->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        दत्त->DwmFlush = (HRESULT (WINAPI *)(शून्य))SDL_आरोपय_Function(दत्त->dwmapiDLL, "DwmFlush");
        दत्त->Dwm_Enable_Blur_Behind_गवाक्षः = (HRESULT (WINAPI *)(HWND hwnd, ध्रुव DWM_BLURBEHIND *pBlurBehind))SDL_आरोपय_Function(दत्त->dwmapiDLL, "DwmEnableBlurBehindWindow");
        दत्त->Dwm_समुच्चयः_गवाक्षः_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_आरोपय_Function(दत्त->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } अन्यथा {
        SDL_ClearError();
    }
#यदि_अन्तः // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#यदि_परिभाषितम् HAVE_DXGI_H
    दत्त->dxgiDLL = SDL_आरोपय_Object("DXGI.DLL");
    यदि (दत्त->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        प्रकारनिर्देश HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, शून्य **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_आरोपय_Function(दत्त->dxgiDLL, "CreateDXGIFactory");
        यदि (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (शून्य **)&दत्त->pDXGIFactory);
        }
    }
#यदि_अन्तः

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = WIN_समुच्चयः_Display_बहुलकम्;
#यदि_अन्तः
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#यदि_अन्तः

    device->CreateSDLWindow = WIN_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = WIN_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Icon = WIN_समुच्चयः_गवाक्षः_Icon;
    device->समुच्चयः_गवाक्षः_Position = WIN_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = WIN_समुच्चयः_गवाक्षः_आकार;
    device->Get_गवाक्षः_Borders_आकार = WIN_Get_गवाक्षः_Borders_आकार;
    device->Get_गवाक्षः_आकार_अन्तर्_Pixels = WIN_Get_गवाक्षः_आकार_अन्तर्_Pixels;
    device->समुच्चयः_गवाक्षः_Opacity = WIN_समुच्चयः_गवाक्षः_Opacity;
    device->Show_गवाक्षः = WIN_Show_गवाक्षः;
    device->Hide_गवाक्षः = WIN_Hide_गवाक्षः;
    device->Raise_गवाक्षः = WIN_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = WIN_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = WIN_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = WIN_Restore_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Bordered = WIN_समुच्चयः_गवाक्षः_Bordered;
    device->समुच्चयः_गवाक्षः_Resizable = WIN_समुच्चयः_गवाक्षः_Resizable;
    device->समुच्चयः_गवाक्षः_Always_On_शिखरम् = WIN_समुच्चयः_गवाक्षः_Always_On_शिखरम्;
    device->समुच्चयः_गवाक्षः_Fullscreen = WIN_समुच्चयः_गवाक्षः_Fullscreen;
    device->समुच्चयः_गवाक्षः_Parent = WIN_समुच्चयः_गवाक्षः_Parent;
    device->समुच्चयः_गवाक्षः_Modal = WIN_समुच्चयः_गवाक्षः_Modal;
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_गवाक्षः_ICCProfile = WIN_Get_गवाक्षः_ICCProfile;
    device->समुच्चयः_गवाक्षः_Mouse_Rect = WIN_समुच्चयः_गवाक्षः_Mouse_Rect;
    device->समुच्चयः_गवाक्षः_Mouse_Grab = WIN_समुच्चयः_गवाक्षः_Mouse_Grab;
    device->समुच्चयः_गवाक्षः_Keyboard_Grab = WIN_समुच्चयः_गवाक्षः_Keyboard_Grab;
#यदि_अन्तः
    device->Destroy_गवाक्षः = WIN_Destroy_गवाक्षः;
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_गवाक्षः_Framebuffer = WIN_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = WIN_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = WIN_Destroy_गवाक्षः_Framebuffer;
    device->On_गवाक्षः_Enter = WIN_On_गवाक्षः_Enter;
    device->समुच्चयः_गवाक्षः_लब्धम्_Test = WIN_समुच्चयः_गवाक्षः_लब्धम्_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_गवाक्षः = WIN_Flash_गवाक्षः;
    device->Apply_गवाक्षः_प्रगतिः = WIN_Apply_गवाक्षः_प्रगतिः;
    device->Show_गवाक्षः_System_Menu = WIN_Show_गवाक्षः_System_Menu;
    device->समुच्चयः_गवाक्षः_Focusable = WIN_समुच्चयः_गवाक्षः_Focusable;
    device->Update_गवाक्षः_Shape = WIN_Update_गवाक्षः_Shape;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
    device->GL_आरोपय_Library = WIN_GL_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = WIN_GL_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = WIN_GL_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
    device->GL_Swap_गवाक्षः = WIN_GL_Swap_गवाक्षः;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = रिक्त;
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#यदि_अन्तः
        // Use EGL based functions
        device->GL_आरोपय_Library = WIN_GLES_आरोपय_Library;
        device->GL_Get_Proc_स्थानाङ्कः = WIN_GLES_Get_Proc_स्थानाङ्कः;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_समुच्चयः_Swap_Interval = WIN_GLES_समुच्चयः_Swap_Interval;
        device->GL_GetSwapInterval = WIN_GLES_GetSwapInterval;
        device->GL_Swap_गवाक्षः = WIN_GLES_Swap_गवाक्षः;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
    }
#यदि_अन्तः
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = WIN_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#यदि_अन्तः

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Start_Text_निवेशः = WIN_Start_Text_निवेशः;
    device->Stop_Text_निवेशः = WIN_Stop_Text_निवेशः;
    device->Update_Text_निवेशः_Area = WIN_Update_Text_निवेशः_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->समुच्चयः_Clipboard_दत्त = WIN_समुच्चयः_Clipboard_दत्त;
    device->Get_Clipboard_दत्त = WIN_Get_Clipboard_दत्त;
    device->Has_Clipboard_दत्त = WIN_Has_Clipboard_दत्त;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->Start_Text_निवेशः = GDK_Start_Text_निवेशः;
    device->Stop_Text_निवेशः = GDK_Stop_Text_निवेशः;
    device->Update_Text_निवेशः_Area = GDK_Update_Text_निवेशः_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#यदि_अन्तः

    device->मुक्त = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_गवाक्षः_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    प्रत्यागम device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_सन्देशः_Box,
    #अन्यथा
    रिक्त,
    #यदि_अन्तः
    false
};

स्थिर BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->समुच्चयः_Process_Dpi_Awareness_Context) {
        दत्त->dpi_unaware_context_declared = true;
        प्रत्यागम दत्त->समुच्चयः_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } अन्यथा यदि (दत्त->समुच्चयः_Process_Dpi_Awareness) {
        // Windows 8.1
        प्रत्यागम SUCCEEDED(दत्त->समुच्चयः_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#यदि_अन्तः
    प्रत्यागम FALSE;
}

स्थिर BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->समुच्चयः_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        प्रत्यागम दत्त->समुच्चयः_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } अन्यथा यदि (दत्त->समुच्चयः_Process_Dpi_Awareness) {
        // Windows 8.1
        प्रत्यागम SUCCEEDED(दत्त->समुच्चयः_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } अन्यथा यदि (दत्त->समुच्चयः_Process_DPIAware) {
        // Windows Vista
        प्रत्यागम दत्त->समुच्चयः_Process_DPIAware();
    }
#यदि_अन्तः
    प्रत्यागम FALSE;
}

स्थिर BOOL WIN_Declare_DPIAware_प्रत्येकम्_Monitor(SDL_VideoDevice *_this)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->समुच्चयः_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        प्रत्यागम दत्त->समुच्चयः_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE);
    } अन्यथा यदि (दत्त->समुच्चयः_Process_Dpi_Awareness) {
        // Windows 8.1
        प्रत्यागम SUCCEEDED(दत्त->समुच्चयः_Process_Dpi_Awareness(PROCESS_प्रत्येकम्_MONITOR_DPI_AWARE));
    } अन्यथा {
        // Older OS: fall back to system DPI aware
        प्रत्यागम WIN_DeclareDPIAwareSystem(_this);
    }
#अन्यथा
    प्रत्यागम FALSE;
#यदि_अन्तः
}

स्थिर BOOL WIN_Declare_DPIAware_प्रत्येकम्_Monitor_V2(SDL_VideoDevice *_this)
{
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    प्रत्यागम FALSE;
#अन्यथा
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    यदि (दत्त->समुच्चयः_Process_Dpi_Awareness_Context) {
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
        यदि (दत्त->समुच्चयः_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE_V2)) {
            प्रत्यागम TRUE;
        } अन्यथा {
            प्रत्यागम WIN_Declare_DPIAware_प्रत्येकम्_Monitor(_this);
        }
    } अन्यथा {
        // Older OS: fall back to per-monitor (or system)
        प्रत्यागम WIN_Declare_DPIAware_प्रत्येकम्_Monitor(_this);
    }
#यदि_अन्तः
}

#यदि_परिभाषितम् HIGHDPI_DEBUG
स्थिर ध्रुव वर्ण *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->GetThreadDpiAwarenessContext && दत्त->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = दत्त->GetThreadDpiAwarenessContext();

        यदि (दत्त->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            प्रत्यागम "unaware";
        } अन्यथा यदि (दत्त->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            प्रत्यागम "system";
        } अन्यथा यदि (दत्त->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE)) {
            प्रत्यागम "permonitor";
        } अन्यथा यदि (दत्त->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE_V2)) {
            प्रत्यागम "permonitorv2";
        } अन्यथा यदि (दत्त->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            प्रत्यागम "unaware_gdiscaled";
        }
    }

    प्रत्यागम "";
}
#यदि_अन्तः

स्थिर शून्य WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    ध्रुव वर्ण *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    यदि (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_प्रत्येकम्_Monitor_V2(_this);
    } अन्यथा यदि (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_प्रत्येकम्_Monitor(_this);
    } अन्यथा यदि (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } अन्यथा यदि (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

स्थिर bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    HRESULT hr;

    hr = WIN_CoInitialize();
    यदि (SUCCEEDED(hr)) {
        दत्त->coinitialized = true;

#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(रिक्त);
        यदि (SUCCEEDED(hr)) {
            दत्त->oleinitialized = true;
        } अन्यथा {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (अचिह्नित पूर्णाङ्क)hr);
        }
#यदि_अन्तः // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } अन्यथा {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (अचिह्नित पूर्णाङ्क)hr);
    }

    WIN_InitDPIAwareness(_this);

#यदि_परिभाषितम् HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#यदि_अन्तः

    यदि (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_निवेशः(_this);
    }

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_बहुलकम् बहुलकम्;

        SDL_zero(बहुलकम्);
        D3D12_XBOX_GetResolution(&बहुलकम्.w, &बहुलकम्.h);
        बहुलकम्.refresh_दरः = 60.0f;
        बहुलकम्.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्);
    }
#अन्यथा // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (!WIN_InitModes(_this)) {
        प्रत्यागम false;
    }

    _this->आन्तरिकम्->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#यदि_अन्तः

    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_सन्देशः_Loop, रिक्त);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, रिक्त);
    SDL_सङ्कलय_Hint_Callback(SDL_HINT_गवाक्षः_FRAME_USABLE_WHILE_CURSOR_HIDDEN, Update_गवाक्षः_Frame_Usable_While_Cursor_Hidden, रिक्त);

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    दत्त->_SDL_WAKEUP = पञ्जिकाकोशः_गवाक्षः_सन्देशः_A("_SDL_WAKEUP");
    दत्त->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? पञ्जिकाकोशः_गवाक्षः_सन्देशः_A("TaskbarButtonCreated") : 0;
#यदि_अन्तः

    प्रत्यागम true;
}

शून्य WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_सन्देशः_Loop, रिक्त);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, रिक्त);
    SDL_RemoveHintCallback(SDL_HINT_गवाक्षः_FRAME_USABLE_WHILE_CURSOR_HIDDEN, Update_गवाक्षः_Frame_Usable_While_Cursor_Hidden, रिक्त);

    WIN_Quit_Raw_निवेशः(_this);
    WIN_Quit_Game_निवेशः(_this);

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    यदि (दत्त->taskbar_list) {
        दत्त->taskbar_list->lpVtbl->Release(दत्त->taskbar_list);
        दत्त->taskbar_list = रिक्त;
    }

    यदि (दत्त->oleinitialized) {
        OleUninitialize();
        दत्त->oleinitialized = false;
    }
#यदि_अन्तः // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    यदि (दत्त->coinitialized) {
        WIN_CoUninitialize();
        दत्त->coinitialized = false;
    }
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#परिभाषय D3D_DEBUG_INFO
#अन्तर्भाव <d3d9.h>

#यदि_परिभाषितम् D3D_DEBUG_INFO
#यदि_अपरिभाषितम् D3_D_SDK_संस्करणम्
#परिभाषय D3_D_SDK_संस्करणम् (32 | 0x80000000)
#यदि_अन्तः
#यदि_अपरिभाषितम् D3_D9b_SDK_संस्करणम्
#परिभाषय D3_D9b_SDK_संस्करणम् (31 | 0x80000000)
#यदि_अन्तः
#अन्यथा //
#यदि_अपरिभाषितम् D3_D_SDK_संस्करणम्
#परिभाषय D3_D_SDK_संस्करणम् 32
#यदि_अन्तः
#यदि_अपरिभाषितम् D3_D9b_SDK_संस्करणम्
#परिभाषय D3_D9b_SDK_संस्करणम् 31
#यदि_अन्तः
#यदि_अन्तः

bool D3_D_आरोपय_DLL(शून्य **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_आरोपय_Object("D3D9.DLL");
    यदि (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        प्रकारनिर्देश IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        प्रकारनिर्देश HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        यदि (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_आरोपय_Function(*pD3DDLL, "Direct3DCreate9Ex");
            यदि (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_संस्करणम्, &pDirect3D9ExInterface);
                यदि (SUCCEEDED(hr)) {
                    ध्रुव GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (शून्य **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    यदि (SUCCEEDED(hr)) {
                        प्रत्यागम true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_आरोपय_Function(*pD3DDLL, "Direct3DCreate9");
        यदि (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_संस्करणम्);
            यदि (*pDirect3D9Interface) {
                प्रत्यागम true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = रिक्त;
    }
    *pDirect3D9Interface = रिक्त;
    प्रत्यागम false;
}

पूर्णाङ्क SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    शून्य *pD3DDLL;
    IDirect3D9 *pD3D;
    यदि (!D3_D_आरोपय_DLL(&pD3DDLL, &pD3D)) {
        SDL_समुच्चयः_Error("Unable to create Direct3D interface");
        प्रत्यागम -1;
    } अन्यथा {
        SDL_Display_दत्त *p_दत्त = SDL_Get_Display_Driver_दत्त(displayID);
        पूर्णाङ्क adapter_सूचकांक = D3DADAPTER_DEFAULT;

        यदि (!p_दत्त) {
            SDL_समुच्चयः_Error("Invalid display index");
            adapter_सूचकांक = -1; // make sure we return something invalid
        } अन्यथा {
            वर्ण *displayName = WIN_String_गन्तव्यम्_UTF8_W(p_दत्त->DeviceName);
            अचिह्नित पूर्णाङ्क गणनम् = IDirect3_D9_Get_Adapter_गणनम्(pD3D);
            अचिह्नित पूर्णाङ्क i;
            प्रति (i = 0; i < गणनम्; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                यदि (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_सूचकांक = i;
                    भङ्ग;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        प्रत्यागम adapter_सूचकांक;
    }
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णाङ्क *adapter_सूचकांक, पूर्णाङ्क *output_सूचकांक)
{
#यदि_अपरिभाषितम् HAVE_DXGI_H
    यदि (adapter_सूचकांक) {
        *adapter_सूचकांक = -1;
    }
    यदि (output_सूचकांक) {
        *output_सूचकांक = -1;
    }
    प्रत्यागम SDL_समुच्चयः_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#अन्यथा
    ध्रुव SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    ध्रुव SDL_Video_दत्त *videodata = videodevice ? videodevice->आन्तरिकम् : रिक्त;
    SDL_Display_दत्त *p_दत्त = SDL_Get_Display_Driver_दत्त(displayID);
    पूर्णाङ्क nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_सूचकांक) {
        प्रत्यागम SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_सूचकांक) {
        प्रत्यागम SDL_InvalidParamError("outputIndex");
    }

    *adapter_सूचकांक = -1;
    *output_सूचकांक = -1;

    यदि (!p_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid display index");
    }

    यदि (!videodata || !videodata->pDXGIFactory) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    यावत् (*adapter_सूचकांक == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        यावत् (*adapter_सूचकांक == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            यदि (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                यदि (SDL_wcscmp(outputDesc.DeviceName, p_दत्त->DeviceName) == 0) {
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

    यदि (*adapter_सूचकांक == -1) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't find matching adapter");
    }
    प्रत्यागम true;
#यदि_अन्तः
}

SDL_SystemTheme WIN_GetSystemTheme(शून्य)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_कुञ्चिका;
    DWORD dwType = REG_DWORD;
    DWORD मानम् = ~0U;
    DWORD दीर्घता = परिमाण(मानम्);

    // Technically this isn't the system theme, but it's the preference for applications
    यदि (Reg_Open_कुञ्चिका_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, कुञ्चिका_READ, &h_कुञ्चिका) == ERROR_SUCCESS) {
        यदि (Reg_Query_मानम्_Ex_W(h_कुञ्चिका, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&मानम्, &दीर्घता) == ERROR_SUCCESS) {
            यदि (मानम् == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_कुञ्चिका(h_कुञ्चिका);
    }
    प्रत्यागम theme;
}

bool WIN_Is_प्रत्येकम्_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->AreDpiAwarenessContextsEqual && दत्त->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        प्रत्यागम दत्त->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE_V2, दत्त->GetThreadDpiAwarenessContext());
    }
#यदि_अन्तः
    प्रत्यागम false;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
