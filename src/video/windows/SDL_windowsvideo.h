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

#جے_بنا_تعریف SDL_windowsvideo_h_
#تعریف_کرو SDL_windowsvideo_h_

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "../SDL_sysvideo.h"

#جے_تعریف_شدہ HAVE_DXGI_H
#جے_بنا_تعریف __cplusplus
#تعریف_کرو CINTERFACE
#تعریف_کرو COBJMACROS
#جے_انت
#ضمن <dxgi.h>
#جے_انت

#إذا defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ضمن <msctf.h>
#وإلا
#ضمن "SDL_msctf.h"
#جے_انت

#ضمن <imm.h>

#تعریف_کرو MAX_CANDLIST   10
#تعریف_کرو MAX_CANDLENGTH 256
#تعریف_کرو MAX_CANDSIZE   (حجم(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

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
#جے_انت

#ضمن "SDL_windowswindow.h"

#جے_بنا_تعریف USER_DEFAULT_SCREEN_DPI
#تعریف_کرو USER_DEFAULT_SCREEN_DPI 96
#جے_انت

#إذا WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#تعریف_کرو TWF_FINETOUCH 1
#تعریف_کرو TWF_WANTPALM  2

#تعریف_کرو TOUCHEVENTF_MOVE 0x0001
#تعریف_کرو TOUCHEVENTF_تھلے 0x0002
#تعریف_کرو TOUCHEVENTF_اتے   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

تعريفنوع بنية _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_سروت;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_نقاب;
    DWORD dw_ویلا;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
تعريفنوع بنية DISPLAYCONFIG_رستہ_سروت_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 منوال_Info_Idx;
        بنية
        {
            UINT32 clone_گروہ_Id : 16;
            UINT32 سروت_منوال_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 حالت_Flags;
} DISPLAYCONFIG_رستہ_سروت_INFO;

تعريفنوع بنية DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

تعريفنوع بنية DISPLAYCONFIG_رستہ_نشانہ_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 منوال_Info_Idx;
        بنية
        {
            UINT32 desktop_منوال_Info_Idx : 16;
            UINT32 نشانہ_منوال_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_شرح_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جانچ_سطر_Ordering;
    BOOL نشانہ_دستیاب;
    UINT32 حالت_Flags;
} DISPLAYCONFIG_رستہ_نشانہ_INFO;

تعريفنوع بنية DISPLAYCONFIG_رستہ_INFO
{
    DISPLAYCONFIG_رستہ_سروت_INFO سروت_Info;
    DISPLAYCONFIG_رستہ_نشانہ_INFO نشانہ_Info;
    UINT32 flags;
} DISPLAYCONFIG_رستہ_INFO;

تعريفنوع تعداد
{
    DISPLAYCONFIG_منوال_INFO_TYPE_سروت = 1,
    DISPLAYCONFIG_منوال_INFO_TYPE_نشانہ = 2,
    DISPLAYCONFIG_منوال_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_منوال_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_منوال_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

تعريفنوع بنية DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_شرح;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION سرگرم_ناپ;
    DISPLAYCONFIG_2DREGION کل_ناپ;

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
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جانچ_سطر_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

تعريفنوع بنية DISPLAYCONFIG_سروت_منوال
{
    UINT32 چوڑائی;
    UINT32 اچائی;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_سروت_منوال;

تعريفنوع بنية DISPLAYCONFIG_نشانہ_منوال
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO نشانہ_Video_Signal_Info;
} DISPLAYCONFIG_نشانہ_منوال;

تعريفنوع بنية DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL رستہ_سروت_ناپ;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

تعريفنوع بنية DISPLAYCONFIG_منوال_INFO
{
    DISPLAYCONFIG_منوال_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    اتحاد
    {
        DISPLAYCONFIG_نشانہ_منوال نشانہ_منوال;
        DISPLAYCONFIG_سروت_منوال سروت_منوال;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_منوال_INFO;

تعريفنوع تعداد DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_اندرونی = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

تعريفنوع تعداد
{
    DISPLAYCONFIG_DEVICE_INFO_GET_سروت_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_نشانہ_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_نشانہ_PREFERRED_منوال = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_نشانہ_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_نشانہ_ادھار_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_DEVICE_INFO_سرخی
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 ناپ;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_سرخی;

تعريفنوع بنية DISPLAYCONFIG_سروت_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_سروت_DEVICE_NAME;

تعريفنوع بنية DISPLAYCONFIG_نشانہ_DEVICE_NAME_FLAGS
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
        UINT32 قدر;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_نشانہ_DEVICE_NAME_FLAGS;

تعريفنوع بنية DISPLAYCONFIG_نشانہ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
    DISPLAYCONFIG_نشانہ_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_ضرب_حاصل_کوڈ_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_رستہ[128];
} DISPLAYCONFIG_نشانہ_DEVICE_NAME;

#تعریف_کرو QDC_ONLY_سرگرم_PATHS 0x00000002

#جے_انت // WINVER < _WIN32_WINNT_WIN7

#إذا WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_NEW 0x00000001
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_INRANGE 0x00000002
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_INCONTACT 0x00000004
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_FIRSTBUTTON 0x00000010
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_SECONDBUTTON 0x00000020
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_THIRDBUTTON 0x00000040
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_FOURTHBUTTON 0x00000080
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_FIFTHBUTTON 0x00000100
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_PRIMARY 0x00002000
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_CONFIDENCE 0x00004000
#تعریف_کرو اشارہ_گر_سنیہا_FLAG_CANCELED 0x00008000

#تعریف_کرو GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#تعریف_کرو IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#تعریف_کرو IS_اشارہ_گر_INCONTACT_WPARAM(wParam) IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, اشارہ_گر_سنیہا_FLAG_INCONTACT)
#تعریف_کرو IS_اشارہ_گر_FIRSTBUTTON_WPARAM(wParam) IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, اشارہ_گر_سنیہا_FLAG_FIRSTBUTTON)

تعريفنوع DWORD اشارہ_گر_داخلہ_TYPE;

تعداد ٹیگ_اشارہ_گر_داخلہ_TYPE
{
    PT_اشارہ_گر = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

تعريفنوع UINT32 اشارہ_گر_FLAGS;

تعريفنوع UINT32 PEN_FLAGS;
#تعریف_کرو PEN_FLAG_NONE 0x00000000
#تعریف_کرو PEN_FLAG_BARREL 0x00000001
#تعریف_کرو PEN_FLAG_INVERTED 0x00000002
#تعریف_کرو PEN_FLAG_ERASER 0x00000004

تعريفنوع UINT32 PEN_نقاب;
#تعریف_کرو PEN_نقاب_NONE 0x00000000
#تعریف_کرو PEN_نقاب_PRESSURE 0x00000001
#تعریف_کرو PEN_نقاب_ROTATION 0x00000002
#تعریف_کرو PEN_نقاب_TILT_X 0x00000004
#تعریف_کرو PEN_نقاب_TILT_Y 0x00000008

تعريفنوع تعداد ٹیگ_اشارہ_گر_BUTTON_CHANGE_TYPE
{
    اشارہ_گر_CHANGE_NONE,
    اشارہ_گر_CHANGE_FIRSTBUTTON_تھلے,
    اشارہ_گر_CHANGE_FIRSTBUTTON_اتے,
    اشارہ_گر_CHANGE_SECONDBUTTON_تھلے,
    اشارہ_گر_CHANGE_SECONDBUTTON_اتے,
    اشارہ_گر_CHANGE_THIRDBUTTON_تھلے,
    اشارہ_گر_CHANGE_THIRDBUTTON_اتے,
    اشارہ_گر_CHANGE_FOURTHBUTTON_تھلے,
    اشارہ_گر_CHANGE_FOURTHBUTTON_اتے,
    اشارہ_گر_CHANGE_FIFTHBUTTON_تھلے,
    اشارہ_گر_CHANGE_FIFTHBUTTON_اتے
} اشارہ_گر_BUTTON_CHANGE_TYPE;

تعريفنوع بنية ٹیگ_اشارہ_گر_INFO
{
    اشارہ_گر_داخلہ_TYPE اشارہ_گر_Type;
    UINT32 اشارہ_گر_Id;
    UINT32 چوکھٹا_Id;
    اشارہ_گر_FLAGS اشارہ_گر_Flags;
    HANDLE سروت_Device;
    HWND hwnd_نشانہ;
    نقطہ_2 ptPixelLocation;
    نقطہ_2 ptHimetricLocation;
    نقطہ_2 ptPixelLocationRaw;
    نقطہ_2 ptHimetricLocationRaw;
    DWORD dw_ویلا;
    UINT32 history_گنتی;
    INT32 داخلہ_انکڑے;
    DWORD dw_کلید_حالتاں;
    UINT64 Performance_گنتی;
    اشارہ_گر_BUTTON_CHANGE_TYPE ButtonChangeType;
} اشارہ_گر_INFO;

تعريفنوع بنية ٹیگ_اشارہ_گر_PEN_INFO
{
    اشارہ_گر_INFO اشارہ_گر_Info;
    PEN_FLAGS penFlags;
    PEN_نقاب pen_نقاب;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} اشارہ_گر_PEN_INFO;

#جے_انت // WINVER < _WIN32_WINNT_WIN8

#جے_بنا_تعریف HAVE_SHELLSCALINGAPI_H

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
    PROCESS_فی_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#وإلا
#ضمن <shellscalingapi.h>
#جے_انت

تعريفنوع بنية ITaskbarList3 ITaskbarList3;

#جے_بنا_تعریف _DPI_AWARENESS_CONTEXTS_

تعريفنوع تعداد DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_فی_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#تعریف_کرو DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#تعریف_کرو DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#تعریف_کرو DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#جے_انت // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#إذا NTDDI_نسخہ < 0x0A000003
#تعریف_کرو DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#جے_انت // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#إذا NTDDI_نسخہ < 0x0A000006
#تعریف_کرو DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#جے_انت // NTDDI_VERSION < 0x0A000006

تعريفنوع BOOL (*PFNSHFullScreen)(HWND, DWORD);
تعريفنوع فراغ (*PFCoordTransform)(SDL_کھڑکی *, نقطہ_2 *);

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    فراغ *انکڑے;
} TSFSink;

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
تعريفنوع بنية ٹیگ_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    نقطہ_2 pt_حالت_Wnd_Pos;
    نقطہ_2 ptSoftKbdPos;
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
    HIMCC h_نجی;
    DWORD dw_عدد_پیغام_Buf;
    HIMCC h_پیغام_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#جے_انت

// Corner rounding support  (Win 11+)
#جے_بنا_تعریف DWMWA_کھڑکی_کونا_PREFERENCE
#تعریف_کرو DWMWA_کھڑکی_کونا_PREFERENCE 33
#جے_انت
تعريفنوع تعداد {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_گیڑا = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_کھڑکی_کونا_PREFERENCE;

// Border Color support (Win 11+)
#جے_بنا_تعریف DWMWA_BORDER_COLOR
#تعریف_کرو DWMWA_BORDER_COLOR 34
#جے_انت

#جے_بنا_تعریف DWMWA_COLOR_DEFAULT
#تعریف_کرو DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#جے_انت

#جے_بنا_تعریف DWMWA_COLOR_NONE
#تعریف_کرو DWMWA_COLOR_NONE 0xFFFFFFFE
#جے_انت

// Transparent window support
#جے_بنا_تعریف DWM_BB_ENABLE
#تعریف_کرو DWM_BB_ENABLE 0x00000001
#جے_انت
#جے_بنا_تعریف DWM_BB_BLURREGION
#تعریف_کرو DWM_BB_BLURREGION 0x00000002
#جے_انت
تعريفنوع بنية
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

بنية SDL_Video_انکڑے
{
    صحيح render;

    bool coinitialized;
#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#جے_انت // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_گنتی;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_بفر_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_رستہ_INFO*, UINT32 *, DISPLAYCONFIG_منوال_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_سرخی*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_داخلہ_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_داخلہ_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح );
    BOOL (WINAPI *رجسٹر_Touch_کھڑکی)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(فراغ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_کھڑکی)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_سیٹ_کھڑکی_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_اشارہ_گر_Type)(UINT32 اشارہ_گر_Id, اشارہ_گر_داخلہ_TYPE *اشارہ_گر_Type);
    BOOL (WINAPI *Get_اشارہ_گر_Pen_Info)(UINT32 اشارہ_گر_Id, اشارہ_گر_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_اشارہ_گر_Device_Rects)(HANDLE device, RECT *اشارہ_گر_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *سیٹ_Process_DPIAware)( فراغ );
    BOOL (WINAPI *سیٹ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *سیٹ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( فراغ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_کھڑکی_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_کھڑکی)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *سیٹ_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#جے_انت                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جے_تعریف_شدہ HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#جے_انت

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_وتھ;
    UINT rawinput_ناپ;
    UINT rawinput_گنتی;
    Uint64 آخری_rawinput_poll;
    SDL_نقطہ آخری_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_کلید_sequence;
    SDL_PenID raw_داخلہ_fake_pen_id;

    WIN_Game_داخلہ_انکڑے *gameinput_context;

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_دستیاب;
    bool ime_اندرونی_composition;
    bool ime_اندرونی_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    صحيح ime_composition_لمائی;
    WCHAR ime_readingstring[16];
    صحيح ime_cursor;
    صحيح ime_selected_شروع;
    صحيح ime_selected_لمائی;

    bool ime_candidates_open;
    bool ime_update_candidates;
    حرف *ime_candidates[MAX_CANDLIST];
    صحيح ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    صحيح ime_candlistindexbase;
    bool ime_horizontal_candidates;
#جے_انت

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جے_بنا_تعریف SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_اشاریہ, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_کھڑکی)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_جندرا_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_جندرا_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#جے_انت // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_کلید_state[256];
    UINT _SDL_WAKEUP;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#جے_انت
};

خارجي bool g_Windows_Enable_سنیہا_Loop;
خارجي bool g_WindowsEnableMenuMnemonics;
خارجي bool g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden;

تعريفنوع بنية IDirect3D9 IDirect3D9;
خارجي bool D3_D_لدو_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

خارجي SDL_SystemTheme WIN_GetSystemTheme(فراغ);
خارجي bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#جے_انت // SDL_windowsvideo_h_
