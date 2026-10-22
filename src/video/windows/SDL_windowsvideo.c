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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS

#నిర్వచితమైతే SDL_VIDEO_VULKAN
#అన్తర్భావ "../SDL_vulkan_internal.h"
#అయితే_ముగింపు
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../SDL_hints_c.h"
#అన్తర్భావ "../../core/windows/SDL_hid.h"

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowsframebuffer.h"
#అన్తర్భావ "SDL_windowsmessagebox.h"
#అన్తర్భావ "SDL_windowsrawinput.h"
#అన్తర్భావ "SDL_windowsvulkan.h"

#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#అన్తర్భావ <shobjidl.h>

#నిర్వచితం_కాకపోతే __ITaskbarList3_FWD_DEFINED__
రకనిర్వచనం నిర్మాణం ITaskbarList3 ITaskbarList3;
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే __ITaskbarList3_INTERFACE_DEFINED__
రకనిర్వచనం గణన TBPFLAG
{
    TBPF_NOPROGRESS = 0x0,
    TBPF_INDETERMINATE = 0x1,
    TBPF_సాధారణ = 0x2,
    TBPF_ERROR = 0x4,
    TBPF_PAUSED = 0x8
} TBPFLAG;

రకనిర్వచనం గణన THUMBBUTTONMASK
{
    THB_BITMAP = 0x1,
    THB_ICON = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS = 0x8
} THUMBBUTTONMASK;

రకనిర్వచనం గణన THUMBBUTTONFLAGS
{
    THBF_ENABLED = 0x0,
    THBF_DISABLED = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND = 0x4,
    THBF_HIDDEN = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

#ఒకవేళ defined(_MSC_VER)
#సూచన warning(disable: 4103)
#అయితే_ముగింపు
#సూచన pack(నెట్టు, 8)
రకనిర్వచనం నిర్మాణం THUMBBUTTON
{
    THUMBBUTTONMASK dw_ముసుగు;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;

రకనిర్వచనం నిర్మాణం THUMBBUTTON *LPTHUMBBUTTON;
#సూచన pack(తీయి)

#నిర్వచితం_కాకపోతే HIMAGELIST
నిర్మాణం _IMAGELIST;
రకనిర్వచనం నిర్మాణం _IMAGELIST *HIMAGELIST;
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం ITaskbarList3Vtbl
{
    HRESULT (__stdcall *QueryInterface)(ITaskbarList3 *This, REFIID riid, శూన్య **ppvObject);
    ULONG (__stdcall *కూడు_Ref)(ITaskbarList3 *This);
    ULONG (__stdcall *Release)(ITaskbarList3 *This);
    HRESULT (__stdcall *HrInit)(ITaskbarList3 *This);
    HRESULT (__stdcall *కూడు_Tab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *DeleteTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *ActivateTab)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *సమితి_చురుకైన_Alt)(ITaskbarList3 *This, HWND hwnd);
    HRESULT (__stdcall *Mark_Fullscreen_కిటికీ)(ITaskbarList3 *This, HWND hwnd, BOOL fFullscreen);
    HRESULT (__stdcall *సమితి_పురోగతి_విలువ)(ITaskbarList3 *This, HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ull_మొత్తం);
    HRESULT (__stdcall *సమితి_పురోగతి_State)(ITaskbarList3 *This, HWND hwnd, TBPFLAG tbpFlags);
    HRESULT (__stdcall *రిజిస్టరు_Tab)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI);
    HRESULT (__stdcall *UnregisterTab)(ITaskbarList3 *This, HWND hwndTab);
    HRESULT (__stdcall *సమితి_Tab_క్రమం)(ITaskbarList3 *This, HWND hwndTab, HWND hwnd_చొప్పించు_Before);
    HRESULT (__stdcall *సమితి_Tab_చురుకైన)(ITaskbarList3 *This, HWND hwndTab, HWND hwndMDI, DWORD dwReserved);
    HRESULT (__stdcall *Thumb_Bar_కూడు_Buttons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *ThumbBarUpdateButtons)(ITaskbarList3 *This, HWND hwnd, UINT cButtons, LPTHUMBBUTTON pButton);
    HRESULT (__stdcall *Thumb_Bar_సమితి_Image_List)(ITaskbarList3 *This, HWND hwnd, HIMAGELIST himl);
    HRESULT (__stdcall *సమితి_Overlay_Icon)(ITaskbarList3 *This, HWND hwnd, HICON hIcon, LPCWSTR pszDescription);
    HRESULT (__stdcall *సమితి_Thumbnail_Tooltip)(ITaskbarList3 *This, HWND hwnd, LPCWSTR pszTip);
    HRESULT (__stdcall *సమితి_Thumbnail_Clip)(ITaskbarList3 *This, HWND hwnd, RECT *prcClip);
} ITaskbarList3Vtbl;

నిర్మాణం ITaskbarList3
{
    ITaskbarList3Vtbl *lpVtbl;
};

#అయితే_ముగింపు // #ifndef __ITaskbarList3_INTERFACE_DEFINED__

#అయితే_ముగింపు

#నిర్వచితమైతే SDL_GDK_TEXTINPUT
#అన్తర్భావ "../gdk/SDL_gdktextinput.h"
#అయితే_ముగింపు

// #define HIGHDPI_DEBUG

// Initialization/Query functions
స్థిర bool WIN_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య WIN_VideoQuit(SDL_VideoDevice *_this);

// Hints
bool g_Windows_Enable_సందేశం_Loop = true;
bool g_WindowsEnableMenuMnemonics = false;
bool g_కిటికీ_చట్రం_Usable_While_Cursor_Hidden = true;

స్థిర శూన్య SDLCALL UpdateWindowsRawKeyboard(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_విలువ, false);
    WIN_సమితి_Raw_Keyboard_Enabled(_this, enabled);
}

స్థిర శూన్య SDLCALL UpdateWindowsRawKeyboardNoHotkeys(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_విలువ, false);
    WIN_సమితి_Raw_Keyboard_Flag_No_Hotkeys(_this, enabled);
}

స్థిర శూన్య SDLCALL UpdateWindowsRawKeyboardInputsink(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_విలువ, false);
    WIN_సమితి_Raw_Keyboard_Flag_Inputsink(_this, enabled);
}

స్థిర శూన్య SDLCALL UpdateWindowsRawMouseNoLegacy(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    bool enabled = SDL_GetStringBoolean(new_విలువ, false);
    WIN_సమితి_Raw_Mouse_Flag_No_Legacy(_this, enabled);
}

స్థిర శూన్య SDLCALL Update_Windows_Enable_సందేశం_Loop(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    g_Windows_Enable_సందేశం_Loop = SDL_GetStringBoolean(new_విలువ, true);
}

స్థిర శూన్య SDLCALL UpdateWindowsEnableMenuMnemonics(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    g_WindowsEnableMenuMnemonics = SDL_GetStringBoolean(new_విలువ, false);
}

స్థిర శూన్య SDLCALL Update_కిటికీ_చట్రం_Usable_While_Cursor_Hidden(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    g_కిటికీ_చట్రం_Usable_While_Cursor_Hidden = SDL_GetStringBoolean(new_విలువ, true);
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
స్థిర bool WIN_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    DWORD ఫలితం;
    ఒకవేళ (_this->suspend_screensaver) {
        ఫలితం = సమితి_Thread_Execution_State(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    } లేకపోతే {
        ఫలితం = సమితి_Thread_Execution_State(ES_CONTINUOUS);
    }
    ఒకవేళ (ఫలితం == 0) {
        SDL_సమితి_Error("SetThreadExecutionState() failed");
        తిరిగి false;
    }
    తిరిగి true;
}
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
బాహ్య శూన్య D3D12_XBOX_GetResolution(Uint32 *వెడల్పు, Uint32 *ఎత్తు);
#అయితే_ముగింపు

// Windows driver bootstrap functions

స్థిర శూన్య WIN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;

    SDL_UnregisterApp();
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (దత్తాంశం->userDLL) {
        SDL_UnloadObject(దత్తాంశం->userDLL);
    }
    ఒకవేళ (దత్తాంశం->shcoreDLL) {
        SDL_UnloadObject(దత్తాంశం->shcoreDLL);
    }
    ఒకవేళ (దత్తాంశం->dwmapiDLL) {
        SDL_UnloadObject(దత్తాంశం->dwmapiDLL);
    }
#అయితే_ముగింపు
#నిర్వచితమైతే HAVE_DXGI_H
    ఒకవేళ (దత్తాంశం->pDXGIFactory) {
        IDXGIFactory_Release(దత్తాంశం->pDXGIFactory);
    }
    ఒకవేళ (దత్తాంశం->dxgiDLL) {
        SDL_UnloadObject(దత్తాంశం->dxgiDLL);
    }
#అయితే_ముగింపు
    SDL_free(device->అంతర్గత->rawinput);
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *WIN_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;

    SDL_రిజిస్టరు_App(ఖాళీ, 0, ఖాళీ);

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (device) {
        దత్తాంశం = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    } లేకపోతే {
        దత్తాంశం = ఖాళీ;
    }
    ఒకవేళ (!దత్తాంశం) {
        SDL_UnregisterApp();
        SDL_free(device);
        తిరిగి ఖాళీ;
    }
    device->అంతర్గత = దత్తాంశం;
    device->system_theme = WIN_GetSystemTheme();

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    దత్తాంశం->userDLL = SDL_ఎక్కించు_Object("USER32.DLL");
    ఒకవేళ (దత్తాంశం->userDLL) {
        /* *INDENT-OFF* */ // clang-format off
        దత్తాంశం->Close_Touch_ఆదానం_Handle = (BOOL (WINAPI *)(HTOUCHINPUT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "CloseTouchInputHandle");
        దత్తాంశం->Get_Touch_ఆదానం_Info = (BOOL (WINAPI *)(HTOUCHINPUT, UINT, PTOUCHINPUT, పూర్ణాంకం)) SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetTouchInputInfo");
        దత్తాంశం->రిజిస్టరు_Touch_కిటికీ = (BOOL (WINAPI *)(HWND, ULONG))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "RegisterTouchWindow");
        దత్తాంశం->సమితి_Process_DPIAware = (BOOL (WINAPI *)(శూన్య))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "SetProcessDPIAware");
        దత్తాంశం->సమితి_Process_Dpi_Awareness_Context = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "SetProcessDpiAwarenessContext");
        దత్తాంశం->సమితి_Thread_Dpi_Awareness_Context = (DPI_AWARENESS_CONTEXT (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "SetThreadDpiAwarenessContext");
        దత్తాంశం->GetThreadDpiAwarenessContext = (DPI_AWARENESS_CONTEXT (WINAPI *)(శూన్య))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetThreadDpiAwarenessContext");
        దత్తాంశం->GetAwarenessFromDpiAwarenessContext = (DPI_AWARENESS (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetAwarenessFromDpiAwarenessContext");
        దత్తాంశం->EnableNonClientDpiScaling = (BOOL (WINAPI *)(HWND))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "EnableNonClientDpiScaling");
        దత్తాంశం->Adjust_కిటికీ_Rect_Ex_For_Dpi = (BOOL (WINAPI *)(LPRECT, DWORD, BOOL, DWORD, UINT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "AdjustWindowRectExForDpi");
        దత్తాంశం->Get_Dpi_For_కిటికీ = (UINT (WINAPI *)(HWND))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetDpiForWindow");
        దత్తాంశం->AreDpiAwarenessContextsEqual = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "AreDpiAwarenessContextsEqual");
        దత్తాంశం->IsValidDpiAwarenessContext = (BOOL (WINAPI *)(DPI_AWARENESS_CONTEXT))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "IsValidDpiAwarenessContext");
        దత్తాంశం->Get_Display_Config_బఫరు_Sizes = (LONG (WINAPI *)(UINT32,UINT32 *,UINT32 *))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetDisplayConfigBufferSizes");
        దత్తాంశం->QueryDisplayConfig = (LONG (WINAPI *)(UINT32,UINT32 *,DISPLAYCONFIG_మార్గం_INFO*,UINT32 *,DISPLAYCONFIG_బహుళకం_INFO*,DISPLAYCONFIG_TOPOLOGY_ID*))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "QueryDisplayConfig");
        దత్తాంశం->DisplayConfigGetDeviceInfo = (LONG (WINAPI *)(DISPLAYCONFIG_DEVICE_INFO_శీర్షిక*))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "DisplayConfigGetDeviceInfo");
        దత్తాంశం->Get_సూచిక_Type = (BOOL (WINAPI *)(UINT32, సూచిక_ఆదానం_TYPE *))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetPointerType");
        దత్తాంశం->Get_సూచిక_Pen_Info = (BOOL (WINAPI *)(UINT32, సూచిక_PEN_INFO *))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetPointerPenInfo");
        దత్తాంశం->Get_సూచిక_Device_Rects = (BOOL (WINAPI *)(HANDLE, RECT *, RECT *))SDL_ఎక్కించు_Function(దత్తాంశం->userDLL, "GetPointerDeviceRects");
        /* *INDENT-ON* */ // clang-format on
    } లేకపోతే {
        SDL_ClearError();
    }

    దత్తాంశం->shcoreDLL = SDL_ఎక్కించు_Object("SHCORE.DLL");
    ఒకవేళ (దత్తాంశం->shcoreDLL) {
        /* *INDENT-OFF* */ // clang-format off
        దత్తాంశం->GetDpiForMonitor = (HRESULT (WINAPI *)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *))SDL_ఎక్కించు_Function(దత్తాంశం->shcoreDLL, "GetDpiForMonitor");
        దత్తాంశం->సమితి_Process_Dpi_Awareness = (HRESULT (WINAPI *)(PROCESS_DPI_AWARENESS))SDL_ఎక్కించు_Function(దత్తాంశం->shcoreDLL, "SetProcessDpiAwareness");
        /* *INDENT-ON* */ // clang-format on
    } లేకపోతే {
        SDL_ClearError();
    }

    దత్తాంశం->dwmapiDLL = SDL_ఎక్కించు_Object("DWMAPI.DLL");
    ఒకవేళ (దత్తాంశం->dwmapiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        దత్తాంశం->DwmFlush = (HRESULT (WINAPI *)(శూన్య))SDL_ఎక్కించు_Function(దత్తాంశం->dwmapiDLL, "DwmFlush");
        దత్తాంశం->Dwm_Enable_Blur_Behind_కిటికీ = (HRESULT (WINAPI *)(HWND hwnd, స్థిరరాశి DWM_BLURBEHIND *pBlurBehind))SDL_ఎక్కించు_Function(దత్తాంశం->dwmapiDLL, "DwmEnableBlurBehindWindow");
        దత్తాంశం->Dwm_సమితి_కిటికీ_Attribute = (HRESULT (WINAPI *)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute))SDL_ఎక్కించు_Function(దత్తాంశం->dwmapiDLL, "DwmSetWindowAttribute");
        /* *INDENT-ON* */ // clang-format on
    } లేకపోతే {
        SDL_ClearError();
    }
#అయితే_ముగింపు // #if !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#నిర్వచితమైతే HAVE_DXGI_H
    దత్తాంశం->dxgiDLL = SDL_ఎక్కించు_Object("DXGI.DLL");
    ఒకవేళ (దత్తాంశం->dxgiDLL) {
        /* *INDENT-OFF* */ // clang-format off
        రకనిర్వచనం HRESULT (WINAPI *pfnCreateDXGI)(REFIID riid, శూన్య **ppFactory);
        /* *INDENT-ON* */ // clang-format on
        pfnCreateDXGI pCreateDXGI;

        pCreateDXGI = (pfnCreateDXGI)SDL_ఎక్కించు_Function(దత్తాంశం->dxgiDLL, "CreateDXGIFactory");
        ఒకవేళ (pCreateDXGI) {
            GUID dxgiGUID = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
            pCreateDXGI(&dxgiGUID, (శూన్య **)&దత్తాంశం->pDXGIFactory);
        }
    }
#అయితే_ముగింపు

    // Set the function pointers
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->RefreshDisplays = WIN_RefreshDisplays;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayUsableBounds = WIN_GetDisplayUsableBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->సమితి_Display_బహుళకం = WIN_సమితి_Display_బహుళకం;
#అయితే_ముగింపు
    device->PumpEvents = WIN_PumpEvents;
    device->WaitEventTimeout = WIN_WaitEventTimeout;
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->SendWakeupEvent = WIN_SendWakeupEvent;
    device->SuspendScreenSaver = WIN_SuspendScreenSaver;
#అయితే_ముగింపు

    device->CreateSDLWindow = WIN_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = WIN_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Icon = WIN_సమితి_కిటికీ_Icon;
    device->సమితి_కిటికీ_Position = WIN_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = WIN_సమితి_కిటికీ_కొలత;
    device->Get_కిటికీ_Borders_కొలత = WIN_Get_కిటికీ_Borders_కొలత;
    device->Get_కిటికీ_కొలత_లోపల_Pixels = WIN_Get_కిటికీ_కొలత_లోపల_Pixels;
    device->సమితి_కిటికీ_Opacity = WIN_సమితి_కిటికీ_Opacity;
    device->Show_కిటికీ = WIN_Show_కిటికీ;
    device->Hide_కిటికీ = WIN_Hide_కిటికీ;
    device->Raise_కిటికీ = WIN_Raise_కిటికీ;
    device->Maximize_కిటికీ = WIN_Maximize_కిటికీ;
    device->Minimize_కిటికీ = WIN_Minimize_కిటికీ;
    device->Restore_కిటికీ = WIN_Restore_కిటికీ;
    device->సమితి_కిటికీ_Bordered = WIN_సమితి_కిటికీ_Bordered;
    device->సమితి_కిటికీ_Resizable = WIN_సమితి_కిటికీ_Resizable;
    device->సమితి_కిటికీ_Always_On_శిఖరం = WIN_సమితి_కిటికీ_Always_On_శిఖరం;
    device->సమితి_కిటికీ_Fullscreen = WIN_సమితి_కిటికీ_Fullscreen;
    device->సమితి_కిటికీ_మాతృ = WIN_సమితి_కిటికీ_మాతృ;
    device->సమితి_కిటికీ_Modal = WIN_సమితి_కిటికీ_Modal;
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Get_కిటికీ_ICCProfile = WIN_Get_కిటికీ_ICCProfile;
    device->సమితి_కిటికీ_Mouse_Rect = WIN_సమితి_కిటికీ_Mouse_Rect;
    device->సమితి_కిటికీ_Mouse_Grab = WIN_సమితి_కిటికీ_Mouse_Grab;
    device->సమితి_కిటికీ_Keyboard_Grab = WIN_సమితి_కిటికీ_Keyboard_Grab;
#అయితే_ముగింపు
    device->Destroy_కిటికీ = WIN_Destroy_కిటికీ;
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->Create_కిటికీ_Framebuffer = WIN_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = WIN_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = WIN_Destroy_కిటికీ_Framebuffer;
    device->On_కిటికీ_Enter = WIN_On_కిటికీ_Enter;
    device->సమితి_కిటికీ_తగిలింది_Test = WIN_సమితి_కిటికీ_తగిలింది_Test;
    device->AcceptDragAndDrop = WIN_AcceptDragAndDrop;
    device->Flash_కిటికీ = WIN_Flash_కిటికీ;
    device->Apply_కిటికీ_పురోగతి = WIN_Apply_కిటికీ_పురోగతి;
    device->Show_కిటికీ_System_Menu = WIN_Show_కిటికీ_System_Menu;
    device->సమితి_కిటికీ_Focusable = WIN_సమితి_కిటికీ_Focusable;
    device->Update_కిటికీ_Shape = WIN_Update_కిటికీ_Shape;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
    device->GL_ఎక్కించు_Library = WIN_GL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = WIN_GL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = WIN_GL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = WIN_GL_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = WIN_GL_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = WIN_GL_DestroyContext;
    device->GL_GetEGLSurface = ఖాళీ;
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#అయితే_ముగింపు
        // Use EGL based functions
        device->GL_ఎక్కించు_Library = WIN_GLES_ఎక్కించు_Library;
        device->GL_Get_Proc_చిరునామా = WIN_GLES_Get_Proc_చిరునామా;
        device->GL_UnloadLibrary = WIN_GLES_UnloadLibrary;
        device->GL_CreateContext = WIN_GLES_CreateContext;
        device->GL_MakeCurrent = WIN_GLES_MakeCurrent;
        device->GL_సమితి_మార్పిడి_Interval = WIN_GLES_సమితి_మార్పిడి_Interval;
        device->GL_Get_మార్పిడి_Interval = WIN_GLES_Get_మార్పిడి_Interval;
        device->GL_మార్పిడి_కిటికీ = WIN_GLES_మార్పిడి_కిటికీ;
        device->GL_DestroyContext = WIN_GLES_DestroyContext;
        device->GL_GetEGLSurface = WIN_GLES_GetEGLSurface;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
    }
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = WIN_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = WIN_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = WIN_Vulkan_GetPresentationSupport;
#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    device->ప్రారంభం_పాఠ్యం_ఆదానం = WIN_ప్రారంభం_పాఠ్యం_ఆదానం;
    device->Stop_పాఠ్యం_ఆదానం = WIN_Stop_పాఠ్యం_ఆదానం;
    device->Update_పాఠ్యం_ఆదానం_Area = WIN_Update_పాఠ్యం_ఆదానం_Area;
    device->ClearComposition = WIN_ClearComposition;

    device->సమితి_Clipboard_దత్తాంశం = WIN_సమితి_Clipboard_దత్తాంశం;
    device->Get_Clipboard_దత్తాంశం = WIN_Get_Clipboard_దత్తాంశం;
    device->Has_Clipboard_దత్తాంశం = WIN_Has_Clipboard_దత్తాంశం;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_GDK_TEXTINPUT
    GDK_EnsureHints();

    device->ప్రారంభం_పాఠ్యం_ఆదానం = GDK_ప్రారంభం_పాఠ్యం_ఆదానం;
    device->Stop_పాఠ్యం_ఆదానం = GDK_Stop_పాఠ్యం_ఆదానం;
    device->Update_పాఠ్యం_ఆదానం_Area = GDK_Update_పాఠ్యం_ఆదానం_Area;
    device->ClearComposition = GDK_ClearComposition;

    device->HasScreenKeyboardSupport = GDK_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = GDK_ShowScreenKeyboard;
    device->HideScreenKeyboard = GDK_HideScreenKeyboard;
#అయితే_ముగింపు

    device->విడుదల = WIN_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_కిటికీ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    తిరిగి device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_CreateDevice,
    #ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_Show_సందేశం_Box,
    #లేకపోతే
    ఖాళీ,
    #అయితే_ముగింపు
    false
};

స్థిర BOOL WIN_DeclareDPIAwareUnaware(SDL_VideoDevice *_this)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness_Context) {
        దత్తాంశం->dpi_unaware_context_declared = true;
        తిరిగి దత్తాంశం->సమితి_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
    } లేకపోతే ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness) {
        // Windows 8.1
        తిరిగి SUCCEEDED(దత్తాంశం->సమితి_Process_Dpi_Awareness(PROCESS_DPI_UNAWARE));
    }
#అయితే_ముగింపు
    తిరిగి FALSE;
}

స్థిర BOOL WIN_DeclareDPIAwareSystem(SDL_VideoDevice *_this)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        తిరిగి దత్తాంశం->సమితి_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    } లేకపోతే ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness) {
        // Windows 8.1
        తిరిగి SUCCEEDED(దత్తాంశం->సమితి_Process_Dpi_Awareness(PROCESS_SYSTEM_DPI_AWARE));
    } లేకపోతే ఒకవేళ (దత్తాంశం->సమితి_Process_DPIAware) {
        // Windows Vista
        తిరిగి దత్తాంశం->సమితి_Process_DPIAware();
    }
#అయితే_ముగింపు
    తిరిగి FALSE;
}

స్థిర BOOL WIN_Declare_DPIAware_చొప్పున_Monitor(SDL_VideoDevice *_this)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness_Context) {
        // Windows 10, version 1607
        తిరిగి దత్తాంశం->సమితి_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE);
    } లేకపోతే ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness) {
        // Windows 8.1
        తిరిగి SUCCEEDED(దత్తాంశం->సమితి_Process_Dpi_Awareness(PROCESS_చొప్పున_MONITOR_DPI_AWARE));
    } లేకపోతే {
        // Older OS: fall back to system DPI aware
        తిరిగి WIN_DeclareDPIAwareSystem(_this);
    }
#లేకపోతే
    తిరిగి FALSE;
#అయితే_ముగింపు
}

స్థిర BOOL WIN_Declare_DPIAware_చొప్పున_Monitor_V2(SDL_VideoDevice *_this)
{
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    తిరిగి FALSE;
#లేకపోతే
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    // Declare DPI aware (may have been done in external code or a manifest, as well)
    ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness_Context) {
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
        ఒకవేళ (దత్తాంశం->సమితి_Process_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2)) {
            తిరిగి TRUE;
        } లేకపోతే {
            తిరిగి WIN_Declare_DPIAware_చొప్పున_Monitor(_this);
        }
    } లేకపోతే {
        // Older OS: fall back to per-monitor (or system)
        తిరిగి WIN_Declare_DPIAware_చొప్పున_Monitor(_this);
    }
#అయితే_ముగింపు
}

#నిర్వచితమైతే HIGHDPI_DEBUG
స్థిర స్థిరరాశి అక్షరం *WIN_GetDPIAwareness(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->GetThreadDpiAwarenessContext && దత్తాంశం->AreDpiAwarenessContextsEqual) {
        DPI_AWARENESS_CONTEXT context = దత్తాంశం->GetThreadDpiAwarenessContext();

        ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE)) {
            తిరిగి "unaware";
        } లేకపోతే ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
            తిరిగి "system";
        } లేకపోతే ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE)) {
            తిరిగి "permonitor";
        } లేకపోతే ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2)) {
            తిరిగి "permonitorv2";
        } లేకపోతే ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual(context, DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)) {
            తిరిగి "unaware_gdiscaled";
        }
    }

    తిరిగి "";
}
#అయితే_ముగింపు

స్థిర శూన్య WIN_InitDPIAwareness(SDL_VideoDevice *_this)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint("SDL_WINDOWS_DPI_AWARENESS");

    ఒకవేళ (!hint || SDL_strcmp(hint, "permonitorv2") == 0) {
        WIN_Declare_DPIAware_చొప్పున_Monitor_V2(_this);
    } లేకపోతే ఒకవేళ (SDL_strcmp(hint, "permonitor") == 0) {
        WIN_Declare_DPIAware_చొప్పున_Monitor(_this);
    } లేకపోతే ఒకవేళ (SDL_strcmp(hint, "system") == 0) {
        WIN_DeclareDPIAwareSystem(_this);
    } లేకపోతే ఒకవేళ (SDL_strcmp(hint, "unaware") == 0) {
        WIN_DeclareDPIAwareUnaware(_this);
    }
}

స్థిర bool WIN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    HRESULT hr;

    hr = WIN_CoInitialize();
    ఒకవేళ (SUCCEEDED(hr)) {
        దత్తాంశం->coinitialized = true;

#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
        hr = OleInitialize(ఖాళీ);
        ఒకవేళ (SUCCEEDED(hr)) {
            దత్తాంశం->oleinitialized = true;
        } లేకపోతే {
            SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OleInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (గుర్తులేని పూర్ణాంకం)hr);
        }
#అయితే_ముగింపు // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    } లేకపోతే {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "CoInitialize() failed: 0x%.8x, using fallback drag-n-drop functionality", (గుర్తులేని పూర్ణాంకం)hr);
    }

    WIN_InitDPIAwareness(_this);

#నిర్వచితమైతే HIGHDPI_DEBUG
    SDL_Log("DPI awareness: %s", WIN_GetDPIAwareness(_this));
#అయితే_ముగింపు

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_GAMEINPUT, false)) {
        WIN_Init_Game_ఆదానం(_this);
    }

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    // For Xbox, we just need to create the single display
    {
        SDL_Display_బహుళకం బహుళకం;

        SDL_zero(బహుళకం);
        D3D12_XBOX_GetResolution(&బహుళకం.w, &బహుళకం.h);
        బహుళకం.refresh_రేటు = 60.0f;
        బహుళకం.format = SDL_PIXELFORMAT_ARGB8888;

        SDL_కూడు_Basic_Video_Display(&బహుళకం);
    }
#లేకపోతే // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (!WIN_InitModes(_this)) {
        తిరిగి false;
    }

    _this->అంతర్గత->detect_device_hotplug = SDL_GetHintBoolean("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", true);

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);
    WIN_InitDeviceNotification();
#అయితే_ముగింపు

    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_RAW_MOUSE_NOLEGACY, UpdateWindowsRawMouseNoLegacy, _this);
    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_సందేశం_Loop, ఖాళీ);
    SDL_కూడు_Hint_Callback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ఖాళీ);
    SDL_కూడు_Hint_Callback(SDL_HINT_కిటికీ_చట్రం_USABLE_WHILE_CURSOR_HIDDEN, Update_కిటికీ_చట్రం_Usable_While_Cursor_Hidden, ఖాళీ);

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    దత్తాంశం->_SDL_WAKEUP = రిజిస్టరు_కిటికీ_సందేశం_A("_SDL_WAKEUP");
    దత్తాంశం->WM_TASKBAR_BUTTON_CREATED = WIN_IsWindows7OrGreater() ? రిజిస్టరు_కిటికీ_సందేశం_A("TaskbarButtonCreated") : 0;
#అయితే_ముగింపు

    తిరిగి true;
}

శూన్య WIN_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD, UpdateWindowsRawKeyboard, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_EXCLUDE_HOTKEYS, UpdateWindowsRawKeyboardNoHotkeys, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_RAW_KEYBOARD_INPUTSINK, UpdateWindowsRawKeyboardInputsink, _this);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, Update_Windows_Enable_సందేశం_Loop, ఖాళీ);
    SDL_RemoveHintCallback(SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS, UpdateWindowsEnableMenuMnemonics, ఖాళీ);
    SDL_RemoveHintCallback(SDL_HINT_కిటికీ_చట్రం_USABLE_WHILE_CURSOR_HIDDEN, Update_కిటికీ_చట్రం_Usable_While_Cursor_Hidden, ఖాళీ);

    WIN_Quit_Raw_ఆదానం(_this);
    WIN_Quit_Game_ఆదానం(_this);

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    WIN_QuitModes(_this);
    WIN_QuitDeviceNotification();
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);

    ఒకవేళ (దత్తాంశం->taskbar_list) {
        దత్తాంశం->taskbar_list->lpVtbl->Release(దత్తాంశం->taskbar_list);
        దత్తాంశం->taskbar_list = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->oleinitialized) {
        OleUninitialize();
        దత్తాంశం->oleinitialized = false;
    }
#అయితే_ముగింపు // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    ఒకవేళ (దత్తాంశం->coinitialized) {
        WIN_CoUninitialize();
        దత్తాంశం->coinitialized = false;
    }
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#నిర్వచించు D3D_DEBUG_INFO
#అన్తర్భావ <d3d9.h>

#నిర్వచితమైతే D3D_DEBUG_INFO
#నిర్వచితం_కాకపోతే D3_D_SDK_సంస్కరణ
#నిర్వచించు D3_D_SDK_సంస్కరణ (32 | 0x80000000)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే D3_D9b_SDK_సంస్కరణ
#నిర్వచించు D3_D9b_SDK_సంస్కరణ (31 | 0x80000000)
#అయితే_ముగింపు
#లేకపోతే //
#నిర్వచితం_కాకపోతే D3_D_SDK_సంస్కరణ
#నిర్వచించు D3_D_SDK_సంస్కరణ 32
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే D3_D9b_SDK_సంస్కరణ
#నిర్వచించు D3_D9b_SDK_సంస్కరణ 31
#అయితే_ముగింపు
#అయితే_ముగింపు

bool D3_D_ఎక్కించు_DLL(శూన్య **pD3DDLL, IDirect3D9 **pDirect3D9Interface)
{
    *pD3DDLL = SDL_ఎక్కించు_Object("D3D9.DLL");
    ఒకవేళ (*pD3DDLL) {
        /* *INDENT-OFF* */ // clang-format off
        రకనిర్వచనం IDirect3D9 *(WINAPI *pfnDirect3DCreate9)(UINT SDKVersion);
        రకనిర్వచనం HRESULT (WINAPI *pfnDirect3DCreate9Ex)(UINT SDKVersion, IDirect3D9Ex **ppD3D);
        /* *INDENT-ON* */ // clang-format on
        pfnDirect3DCreate9 pDirect3DCreate9;

        ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_WINDOWS_USE_D3D9EX, false)) {
            pfnDirect3DCreate9Ex pDirect3DCreate9Ex;

            pDirect3DCreate9Ex = (pfnDirect3DCreate9Ex)SDL_ఎక్కించు_Function(*pD3DDLL, "Direct3DCreate9Ex");
            ఒకవేళ (pDirect3DCreate9Ex) {
                IDirect3D9Ex *pDirect3D9ExInterface;
                HRESULT hr = pDirect3DCreate9Ex(D3_D_SDK_సంస్కరణ, &pDirect3D9ExInterface);
                ఒకవేళ (SUCCEEDED(hr)) {
                    స్థిరరాశి GUID IDirect3D9_GUID = { 0x81bdcbca, 0x64d4, 0x426d, { 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c } };
                    hr = IDirect3D9Ex_QueryInterface(pDirect3D9ExInterface, &IDirect3D9_GUID, (శూన్య **)pDirect3D9Interface);
                    IDirect3D9Ex_Release(pDirect3D9ExInterface);
                    ఒకవేళ (SUCCEEDED(hr)) {
                        తిరిగి true;
                    }
                }
            }
        }

        pDirect3DCreate9 = (pfnDirect3DCreate9)SDL_ఎక్కించు_Function(*pD3DDLL, "Direct3DCreate9");
        ఒకవేళ (pDirect3DCreate9) {
            *pDirect3D9Interface = pDirect3DCreate9(D3_D_SDK_సంస్కరణ);
            ఒకవేళ (*pDirect3D9Interface) {
                తిరిగి true;
            }
        }

        SDL_UnloadObject(*pD3DDLL);
        *pD3DDLL = ఖాళీ;
    }
    *pDirect3D9Interface = ఖాళీ;
    తిరిగి false;
}

పూర్ణాంకం SDL_Get_Direct3_D9_Adapter_సూచీ(SDL_DisplayID displayID)
{
    శూన్య *pD3DDLL;
    IDirect3D9 *pD3D;
    ఒకవేళ (!D3_D_ఎక్కించు_DLL(&pD3DDLL, &pD3D)) {
        SDL_సమితి_Error("Unable to create Direct3D interface");
        తిరిగి -1;
    } లేకపోతే {
        SDL_Display_దత్తాంశం *p_దత్తాంశం = SDL_Get_Display_Driver_దత్తాంశం(displayID);
        పూర్ణాంకం adapter_సూచీ = D3DADAPTER_DEFAULT;

        ఒకవేళ (!p_దత్తాంశం) {
            SDL_సమితి_Error("Invalid display index");
            adapter_సూచీ = -1; // make sure we return something invalid
        } లేకపోతే {
            అక్షరం *displayName = WIN_String_గమ్యం_UTF8_W(p_దత్తాంశం->DeviceName);
            గుర్తులేని పూర్ణాంకం లెక్క = IDirect3_D9_Get_Adapter_లెక్క(pD3D);
            గుర్తులేని పూర్ణాంకం i;
            కొరకు (i = 0; i < లెక్క; i++) {
                D3DADAPTER_IDENTIFIER9 id;
                IDirect3D9_GetAdapterIdentifier(pD3D, i, 0, &id);

                ఒకవేళ (SDL_strcmp(id.DeviceName, displayName) == 0) {
                    adapter_సూచీ = i;
                    ఆపు;
                }
            }
            SDL_free(displayName);
        }

        // free up the D3D stuff we inited
        IDirect3D9_Release(pD3D);
        SDL_UnloadObject(pD3DDLL);

        తిరిగి adapter_సూచీ;
    }
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, పూర్ణాంకం *adapter_సూచీ, పూర్ణాంకం *output_సూచీ)
{
#నిర్వచితం_కాకపోతే HAVE_DXGI_H
    ఒకవేళ (adapter_సూచీ) {
        *adapter_సూచీ = -1;
    }
    ఒకవేళ (output_సూచీ) {
        *output_సూచీ = -1;
    }
    తిరిగి SDL_సమితి_Error("SDL was compiled without DXGI support due to missing dxgi.h header");
#లేకపోతే
    స్థిరరాశి SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    స్థిరరాశి SDL_Video_దత్తాంశం *videodata = videodevice ? videodevice->అంతర్గత : ఖాళీ;
    SDL_Display_దత్తాంశం *p_దత్తాంశం = SDL_Get_Display_Driver_దత్తాంశం(displayID);
    పూర్ణాంకం nAdapter, nOutput;
    IDXGIAdapter *pDXGIAdapter;
    IDXGIOutput *pDXGIOutput;

    CHECK_PARAM(!adapter_సూచీ) {
        తిరిగి SDL_InvalidParamError("adapterIndex");
    }

    CHECK_PARAM(!output_సూచీ) {
        తిరిగి SDL_InvalidParamError("outputIndex");
    }

    *adapter_సూచీ = -1;
    *output_సూచీ = -1;

    ఒకవేళ (!p_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("Invalid display index");
    }

    ఒకవేళ (!videodata || !videodata->pDXGIFactory) {
        తిరిగి SDL_సమితి_Error("Unable to create DXGI interface");
    }

    nAdapter = 0;
    అయితే (*adapter_సూచీ == -1 && SUCCEEDED(IDXGIFactory_EnumAdapters(videodata->pDXGIFactory, nAdapter, &pDXGIAdapter))) {
        nOutput = 0;
        అయితే (*adapter_సూచీ == -1 && SUCCEEDED(IDXGIAdapter_EnumOutputs(pDXGIAdapter, nOutput, &pDXGIOutput))) {
            DXGI_OUTPUT_DESC outputDesc;
            ఒకవేళ (SUCCEEDED(IDXGIOutput_GetDesc(pDXGIOutput, &outputDesc))) {
                ఒకవేళ (SDL_wcscmp(outputDesc.DeviceName, p_దత్తాంశం->DeviceName) == 0) {
                    *adapter_సూచీ = nAdapter;
                    *output_సూచీ = nOutput;
                }
            }
            IDXGIOutput_Release(pDXGIOutput);
            nOutput++;
        }
        IDXGIAdapter_Release(pDXGIAdapter);
        nAdapter++;
    }

    ఒకవేళ (*adapter_సూచీ == -1) {
        తిరిగి SDL_సమితి_Error("Couldn't find matching adapter");
    }
    తిరిగి true;
#అయితే_ముగింపు
}

SDL_SystemTheme WIN_GetSystemTheme(శూన్య)
{
    SDL_SystemTheme theme = SDL_SYSTEM_THEME_LIGHT;
    HKEY h_కీలకం;
    DWORD dwType = REG_DWORD;
    DWORD విలువ = ~0U;
    DWORD నిడివి = పరిమాణం(విలువ);

    // Technically this isn't the system theme, but it's the preference for applications
    ఒకవేళ (Reg_Open_కీలకం_Ex_W(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, కీలకం_READ, &h_కీలకం) == ERROR_SUCCESS) {
        ఒకవేళ (Reg_Query_విలువ_Ex_W(h_కీలకం, L"AppsUseLightTheme", 0, &dwType, (LPBYTE)&విలువ, &నిడివి) == ERROR_SUCCESS) {
            ఒకవేళ (విలువ == 0) {
                theme = SDL_SYSTEM_THEME_DARK;
            }
        }
        Reg_Close_కీలకం(h_కీలకం);
    }
    తిరిగి theme;
}

bool WIN_Is_చొప్పున_Monitor_V2_DPIAware(SDL_VideoDevice *_this)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->AreDpiAwarenessContextsEqual && దత్తాంశం->GetThreadDpiAwarenessContext) {
        // Windows 10, version 1607
        తిరిగి దత్తాంశం->AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2, దత్తాంశం->GetThreadDpiAwarenessContext());
    }
#అయితే_ముగింపు
    తిరిగి false;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
