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

#اگر_تعریف_نشده SDL_windowsvideo_h_
#تعریف_کن SDL_windowsvideo_h_

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "../SDL_sysvideo.h"

#اگر_تعریف_شده HAVE_DXGI_H
#اگر_تعریف_نشده __cplusplus
#تعریف_کن CINTERFACE
#تعریف_کن COBJMACROS
#پایان_اگر
#ضمن <dxgi.h>
#پایان_اگر

#إذا defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ضمن <msctf.h>
#وإلا
#ضمن "SDL_msctf.h"
#پایان_اگر

#ضمن <imm.h>

#تعریف_کن MAX_CANDLIST   10
#تعریف_کن MAX_CANDLENGTH 256
#تعریف_کن MAX_CANDSIZE   (حجم(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#ضمن "SDL_windowsclipboard.h"
#ضمن "SDL_windowsevents.h"
#ضمن "SDL_windowsgameinput.h"
#ضمن "SDL_windowsopengl.h"

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ضمن "SDL_windowsshape.h"
#ضمن "SDL_windowskeyboard.h"
#ضمن "SDL_windowsmodes.h"
#ضمن "SDL_windowsmouse.h"
#ضمن "SDL_windowsopengles.h"
#پایان_اگر

#ضمن "SDL_windowswindow.h"

#اگر_تعریف_نشده USER_DEFAULT_SCREEN_DPI
#تعریف_کن USER_DEFAULT_SCREEN_DPI 96
#پایان_اگر

#إذا WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#تعریف_کن TWF_FINETOUCH 1
#تعریف_کن TWF_WANTPALM  2

#تعریف_کن TOUCHEVENTF_MOVE 0x0001
#تعریف_کن TOUCHEVENTF_پایین 0x0002
#تعریف_کن TOUCHEVENTF_به_بالا   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

تعريفنوع بنية _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_منبع;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_ماسک;
    DWORD dw_زمان;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
تعريفنوع بنية DISPLAYCONFIG_مسیر_منبع_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 نما_Info_Idx;
        بنية
        {
            UINT32 clone_گروه_Id : 16;
            UINT32 منبع_نما_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 وضعیت_Flags;
} DISPLAYCONFIG_مسیر_منبع_INFO;

تعريفنوع بنية DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

تعريفنوع بنية DISPLAYCONFIG_مسیر_هدف_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 نما_Info_Idx;
        بنية
        {
            UINT32 desktop_نما_Info_Idx : 16;
            UINT32 هدف_نما_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_نرخ_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ پیمایش_سطر_Ordering;
    BOOL هدف_موجود;
    UINT32 وضعیت_Flags;
} DISPLAYCONFIG_مسیر_هدف_INFO;

تعريفنوع بنية DISPLAYCONFIG_مسیر_INFO
{
    DISPLAYCONFIG_مسیر_منبع_INFO منبع_Info;
    DISPLAYCONFIG_مسیر_هدف_INFO هدف_Info;
    UINT32 flags;
} DISPLAYCONFIG_مسیر_INFO;

تعريفنوع تعداد
{
    DISPLAYCONFIG_نما_INFO_TYPE_منبع = 1,
    DISPLAYCONFIG_نما_INFO_TYPE_هدف = 2,
    DISPLAYCONFIG_نما_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_نما_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_نما_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

تعريفنوع بنية DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_نرخ;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION فعال_اندازه;
    DISPLAYCONFIG_2DREGION مجموع_اندازه;

    اتحاد
    {
        بنية
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ پیمایش_سطر_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

تعريفنوع بنية DISPLAYCONFIG_منبع_نما
{
    UINT32 عرض;
    UINT32 ارتفاع;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_منبع_نما;

تعريفنوع بنية DISPLAYCONFIG_هدف_نما
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO هدف_Video_Signal_Info;
} DISPLAYCONFIG_هدف_نما;

تعريفنوع بنية DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL مسیر_منبع_اندازه;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

تعريفنوع بنية DISPLAYCONFIG_نما_INFO
{
    DISPLAYCONFIG_نما_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    اتحاد
    {
        DISPLAYCONFIG_هدف_نما هدف_نما;
        DISPLAYCONFIG_منبع_نما منبع_نما;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_نما_INFO;

تعريفنوع تعداد DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_داخلی = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

تعريفنوع تعداد
{
    DISPLAYCONFIG_DEVICE_INFO_GET_منبع_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_PREFERRED_نما = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_مجموعه_هدف_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_پایه_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_مجموعه_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_مجموعه_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_DEVICE_INFO_سرآیند
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 اندازه;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_سرآیند;

تعريفنوع بنية DISPLAYCONFIG_منبع_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرآیند سرآیند;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_منبع_DEVICE_NAME;

تعريفنوع بنية DISPLAYCONFIG_هدف_DEVICE_NAME_FLAGS
{
    اتحاد
    {
        بنية
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 مقدار;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_هدف_DEVICE_NAME_FLAGS;

تعريفنوع بنية DISPLAYCONFIG_هدف_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرآیند سرآیند;
    DISPLAYCONFIG_هدف_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_حاصلضرب_کد_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_مسیر[128];
} DISPLAYCONFIG_هدف_DEVICE_NAME;

#تعریف_کن QDC_ONLY_فعال_PATHS 0x00000002

#پایان_اگر // WINVER < _WIN32_WINNT_WIN7

#إذا WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#تعریف_کن اشاره_گر_پیام_FLAG_NEW 0x00000001
#تعریف_کن اشاره_گر_پیام_FLAG_INRANGE 0x00000002
#تعریف_کن اشاره_گر_پیام_FLAG_INCONTACT 0x00000004
#تعریف_کن اشاره_گر_پیام_FLAG_FIRSTBUTTON 0x00000010
#تعریف_کن اشاره_گر_پیام_FLAG_SECONDBUTTON 0x00000020
#تعریف_کن اشاره_گر_پیام_FLAG_THIRDBUTTON 0x00000040
#تعریف_کن اشاره_گر_پیام_FLAG_FOURTHBUTTON 0x00000080
#تعریف_کن اشاره_گر_پیام_FLAG_FIFTHBUTTON 0x00000100
#تعریف_کن اشاره_گر_پیام_FLAG_PRIMARY 0x00002000
#تعریف_کن اشاره_گر_پیام_FLAG_CONFIDENCE 0x00004000
#تعریف_کن اشاره_گر_پیام_FLAG_CANCELED 0x00008000

#تعریف_کن GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#تعریف_کن IS_اشاره_گر_FLAG_مجموعه_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#تعریف_کن IS_اشاره_گر_INCONTACT_WPARAM(wParam) IS_اشاره_گر_FLAG_مجموعه_WPARAM(wParam, اشاره_گر_پیام_FLAG_INCONTACT)
#تعریف_کن IS_اشاره_گر_FIRSTBUTTON_WPARAM(wParam) IS_اشاره_گر_FLAG_مجموعه_WPARAM(wParam, اشاره_گر_پیام_FLAG_FIRSTBUTTON)

تعريفنوع DWORD اشاره_گر_درون_داد_TYPE;

تعداد برچسب_اشاره_گر_درون_داد_TYPE
{
    PT_اشاره_گر = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

تعريفنوع UINT32 اشاره_گر_FLAGS;

تعريفنوع UINT32 PEN_FLAGS;
#تعریف_کن PEN_FLAG_NONE 0x00000000
#تعریف_کن PEN_FLAG_BARREL 0x00000001
#تعریف_کن PEN_FLAG_INVERTED 0x00000002
#تعریف_کن PEN_FLAG_ERASER 0x00000004

تعريفنوع UINT32 PEN_ماسک;
#تعریف_کن PEN_ماسک_NONE 0x00000000
#تعریف_کن PEN_ماسک_PRESSURE 0x00000001
#تعریف_کن PEN_ماسک_ROTATION 0x00000002
#تعریف_کن PEN_ماسک_TILT_X 0x00000004
#تعریف_کن PEN_ماسک_TILT_Y 0x00000008

تعريفنوع تعداد برچسب_اشاره_گر_BUTTON_CHANGE_TYPE
{
    اشاره_گر_CHANGE_NONE,
    اشاره_گر_CHANGE_FIRSTBUTTON_پایین,
    اشاره_گر_CHANGE_FIRSTBUTTON_به_بالا,
    اشاره_گر_CHANGE_SECONDBUTTON_پایین,
    اشاره_گر_CHANGE_SECONDBUTTON_به_بالا,
    اشاره_گر_CHANGE_THIRDBUTTON_پایین,
    اشاره_گر_CHANGE_THIRDBUTTON_به_بالا,
    اشاره_گر_CHANGE_FOURTHBUTTON_پایین,
    اشاره_گر_CHANGE_FOURTHBUTTON_به_بالا,
    اشاره_گر_CHANGE_FIFTHBUTTON_پایین,
    اشاره_گر_CHANGE_FIFTHBUTTON_به_بالا
} اشاره_گر_BUTTON_CHANGE_TYPE;

تعريفنوع بنية برچسب_اشاره_گر_INFO
{
    اشاره_گر_درون_داد_TYPE اشاره_گر_Type;
    UINT32 اشاره_گر_Id;
    UINT32 قاب_Id;
    اشاره_گر_FLAGS اشاره_گر_Flags;
    HANDLE منبع_Device;
    HWND hwnd_هدف;
    نقطه_2 ptPixelLocation;
    نقطه_2 ptHimetricLocation;
    نقطه_2 ptPixelLocationRaw;
    نقطه_2 ptHimetricLocationRaw;
    DWORD dw_زمان;
    UINT32 history_شمار;
    INT32 درون_داد_داده;
    DWORD dw_کلید_حالتها;
    UINT64 Performance_شمار;
    اشاره_گر_BUTTON_CHANGE_TYPE ButtonChangeType;
} اشاره_گر_INFO;

تعريفنوع بنية برچسب_اشاره_گر_PEN_INFO
{
    اشاره_گر_INFO اشاره_گر_Info;
    PEN_FLAGS penFlags;
    PEN_ماسک pen_ماسک;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} اشاره_گر_PEN_INFO;

#پایان_اگر // WINVER < _WIN32_WINNT_WIN8

#اگر_تعریف_نشده HAVE_SHELLSCALINGAPI_H

تعريفنوع تعداد MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

تعريفنوع تعداد PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_در_هر_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#وإلا
#ضمن <shellscalingapi.h>
#پایان_اگر

تعريفنوع بنية ITaskbarList3 ITaskbarList3;

#اگر_تعریف_نشده _DPI_AWARENESS_CONTEXTS_

تعريفنوع تعداد DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_در_هر_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#تعریف_کن DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#تعریف_کن DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#تعریف_کن DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#پایان_اگر // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#إذا NTDDI_نسخه < 0x0A000003
#تعریف_کن DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#پایان_اگر // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#إذا NTDDI_نسخه < 0x0A000006
#تعریف_کن DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#پایان_اگر // NTDDI_VERSION < 0x0A000006

تعريفنوع BOOL (*PFNSHFullScreen)(HWND, DWORD);
تعريفنوع فراغ (*PFCoordTransform)(SDL_پنجره *, نقطه_2 *);

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    فراغ *داده;
} TSFSink;

#اگر_تعریف_نشده SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
تعريفنوع بنية برچسب_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    نقطه_2 pt_وضعیت_Wnd_Pos;
    نقطه_2 ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    اتحاد
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_سطر;
    HIMCC h_خصوصی;
    DWORD dw_رقم_پیام_Buf;
    HIMCC h_پیام_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#پایان_اگر

// Corner rounding support  (Win 11+)
#اگر_تعریف_نشده DWMWA_پنجره_گوشه_PREFERENCE
#تعریف_کن DWMWA_پنجره_گوشه_PREFERENCE 33
#پایان_اگر
تعريفنوع تعداد {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_دور = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_پنجره_گوشه_PREFERENCE;

// Border Color support (Win 11+)
#اگر_تعریف_نشده DWMWA_BORDER_COLOR
#تعریف_کن DWMWA_BORDER_COLOR 34
#پایان_اگر

#اگر_تعریف_نشده DWMWA_COLOR_DEFAULT
#تعریف_کن DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#پایان_اگر

#اگر_تعریف_نشده DWMWA_COLOR_NONE
#تعریف_کن DWMWA_COLOR_NONE 0xFFFFFFFE
#پایان_اگر

// Transparent window support
#اگر_تعریف_نشده DWM_BB_ENABLE
#تعریف_کن DWM_BB_ENABLE 0x00000001
#پایان_اگر
#اگر_تعریف_نشده DWM_BB_BLURREGION
#تعریف_کن DWM_BB_BLURREGION 0x00000002
#پایان_اگر
تعريفنوع بنية
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

بنية SDL_Video_داده
{
    صحيح render;

    bool coinitialized;
#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#پایان_اگر // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_شمار;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_میانگیر_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_مسیر_INFO*, UINT32 *, DISPLAYCONFIG_نما_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_سرآیند*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_درون_داد_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_درون_داد_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح );
    BOOL (WINAPI *ثبات_Touch_پنجره)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(فراغ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_پنجره)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_مجموعه_پنجره_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_اشاره_گر_Type)(UINT32 اشاره_گر_Id, اشاره_گر_درون_داد_TYPE *اشاره_گر_Type);
    BOOL (WINAPI *Get_اشاره_گر_Pen_Info)(UINT32 اشاره_گر_Id, اشاره_گر_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_اشاره_گر_Device_Rects)(HANDLE device, RECT *اشاره_گر_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *مجموعه_Process_DPIAware)( فراغ );
    BOOL (WINAPI *مجموعه_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *مجموعه_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( فراغ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_پنجره_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_پنجره)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *مجموعه_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#پایان_اگر                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شده HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#پایان_اگر

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_جابه_جایی;
    UINT rawinput_اندازه;
    UINT rawinput_شمار;
    Uint64 آخرین_rawinput_poll;
    SDL_نقطه آخرین_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_کلید_sequence;
    SDL_PenID raw_درون_داد_fake_pen_id;

    WIN_Game_درون_داد_داده *gameinput_context;

#اگر_تعریف_نشده SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_موجود;
    bool ime_داخلی_composition;
    bool ime_داخلی_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    صحيح ime_composition_درازی;
    WCHAR ime_readingstring[16];
    صحيح ime_cursor;
    صحيح ime_selected_شروع;
    صحيح ime_selected_درازی;

    bool ime_candidates_open;
    bool ime_update_candidates;
    حرف *ime_candidates[MAX_CANDLIST];
    صحيح ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    صحيح ime_candlistindexbase;
    bool ime_horizontal_candidates;
#پایان_اگر

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_نشده SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_شاخص, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_پنجره)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_قفل_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_قفل_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#پایان_اگر // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_کلید_state[256];
    UINT _SDL_WAKEUP;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#پایان_اگر
};

خارجي bool g_Windows_Enable_پیام_Loop;
خارجي bool g_WindowsEnableMenuMnemonics;
خارجي bool g_پنجره_قاب_Usable_While_Cursor_Hidden;

تعريفنوع بنية IDirect3D9 IDirect3D9;
خارجي bool D3_D_بارگیری_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

خارجي SDL_SystemTheme WIN_GetSystemTheme(فراغ);
خارجي bool WIN_Is_در_هر_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#پایان_اگر // SDL_windowsvideo_h_
