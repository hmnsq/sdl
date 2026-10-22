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

#اگر_غیر_تعریف_شدہ SDL_windowsvideo_h_
#تعریف_کرو SDL_windowsvideo_h_

#شامل "../../core/windows/SDL_windows.h"

#شامل "../SDL_sysvideo.h"

#اگر_تعریف_شدہ HAVE_DXGI_H
#اگر_غیر_تعریف_شدہ __cplusplus
#تعریف_کرو CINTERFACE
#تعریف_کرو COBJMACROS
#اگر_ختم
#شامل <dxgi.h>
#اگر_ختم

#اگر defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#شامل <msctf.h>
#ورنہ
#شامل "SDL_msctf.h"
#اگر_ختم

#شامل <imm.h>

#تعریف_کرو MAX_CANDLIST   10
#تعریف_کرو MAX_CANDLENGTH 256
#تعریف_کرو MAX_CANDSIZE   (حجم(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#شامل "SDL_windowsclipboard.h"
#شامل "SDL_windowsevents.h"
#شامل "SDL_windowsgameinput.h"
#شامل "SDL_windowsopengl.h"

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#شامل "SDL_windowsshape.h"
#شامل "SDL_windowskeyboard.h"
#شامل "SDL_windowsmodes.h"
#شامل "SDL_windowsmouse.h"
#شامل "SDL_windowsopengles.h"
#اگر_ختم

#شامل "SDL_windowswindow.h"

#اگر_غیر_تعریف_شدہ USER_DEFAULT_SCREEN_DPI
#تعریف_کرو USER_DEFAULT_SCREEN_DPI 96
#اگر_ختم

#اگر WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#تعریف_کرو TWF_FINETOUCH 1
#تعریف_کرو TWF_WANTPALM  2

#تعریف_کرو TOUCHEVENTF_MOVE 0x0001
#تعریف_کرو TOUCHEVENTF_نیچے_کو 0x0002
#تعریف_کرو TOUCHEVENTF_اوپر   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

قسمتعریف ساخت _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_ماخذ;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_نقاب;
    DWORD dw_وقت;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
قسمتعریف ساخت DISPLAYCONFIG_راستہ_ماخذ_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 منوال_Info_Idx;
        ساخت
        {
            UINT32 clone_گروہ_Id : 16;
            UINT32 ماخذ_منوال_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 حالت_Flags;
} DISPLAYCONFIG_راستہ_ماخذ_INFO;

قسمتعریف ساخت DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

قسمتعریف ساخت DISPLAYCONFIG_راستہ_ہدف_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 منوال_Info_Idx;
        ساخت
        {
            UINT32 desktop_منوال_Info_Idx : 16;
            UINT32 ہدف_منوال_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_شرح_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جائزہ_سطر_Ordering;
    BOOL ہدف_دستیاب;
    UINT32 حالت_Flags;
} DISPLAYCONFIG_راستہ_ہدف_INFO;

قسمتعریف ساخت DISPLAYCONFIG_راستہ_INFO
{
    DISPLAYCONFIG_راستہ_ماخذ_INFO ماخذ_Info;
    DISPLAYCONFIG_راستہ_ہدف_INFO ہدف_Info;
    UINT32 flags;
} DISPLAYCONFIG_راستہ_INFO;

قسمتعریف شمار
{
    DISPLAYCONFIG_منوال_INFO_TYPE_ماخذ = 1,
    DISPLAYCONFIG_منوال_INFO_TYPE_ہدف = 2,
    DISPLAYCONFIG_منوال_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_منوال_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_منوال_INFO_TYPE;

قسمتعریف ساخت DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

قسمتعریف ساخت DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_شرح;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION فعال_سائز;
    DISPLAYCONFIG_2DREGION کل_سائز;

    اتحاد
    {
        ساخت
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جائزہ_سطر_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

قسمتعریف ساخت DISPLAYCONFIG_ماخذ_منوال
{
    UINT32 چوڑائی;
    UINT32 اونچائی;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_ماخذ_منوال;

قسمتعریف ساخت DISPLAYCONFIG_ہدف_منوال
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO ہدف_Video_Signal_Info;
} DISPLAYCONFIG_ہدف_منوال;

قسمتعریف ساخت DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL راستہ_ماخذ_سائز;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

قسمتعریف ساخت DISPLAYCONFIG_منوال_INFO
{
    DISPLAYCONFIG_منوال_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    اتحاد
    {
        DISPLAYCONFIG_ہدف_منوال ہدف_منوال;
        DISPLAYCONFIG_ماخذ_منوال ماخذ_منوال;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_منوال_INFO;

قسمتعریف شمار DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_اندرونی = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

قسمتعریف شمار
{
    DISPLAYCONFIG_DEVICE_INFO_GET_ماخذ_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_ہدف_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_ہدف_PREFERRED_منوال = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_ہدف_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_ہدف_بنیاد_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_سیٹ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

قسمتعریف ساخت DISPLAYCONFIG_DEVICE_INFO_سرخی
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 سائز;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_سرخی;

قسمتعریف ساخت DISPLAYCONFIG_ماخذ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_ماخذ_DEVICE_NAME;

قسمتعریف ساخت DISPLAYCONFIG_ہدف_DEVICE_NAME_FLAGS
{
    اتحاد
    {
        ساخت
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 قدر;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ہدف_DEVICE_NAME_FLAGS;

قسمتعریف ساخت DISPLAYCONFIG_ہدف_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرخی سرخی;
    DISPLAYCONFIG_ہدف_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_حاصل_ضرب_رمز_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_راستہ[128];
} DISPLAYCONFIG_ہدف_DEVICE_NAME;

#تعریف_کرو QDC_ONLY_فعال_PATHS 0x00000002

#اگر_ختم // WINVER < _WIN32_WINNT_WIN7

#اگر WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#تعریف_کرو اشارہ_گر_پیغام_FLAG_NEW 0x00000001
#تعریف_کرو اشارہ_گر_پیغام_FLAG_INRANGE 0x00000002
#تعریف_کرو اشارہ_گر_پیغام_FLAG_INCONTACT 0x00000004
#تعریف_کرو اشارہ_گر_پیغام_FLAG_FIRSTBUTTON 0x00000010
#تعریف_کرو اشارہ_گر_پیغام_FLAG_SECONDBUTTON 0x00000020
#تعریف_کرو اشارہ_گر_پیغام_FLAG_THIRDBUTTON 0x00000040
#تعریف_کرو اشارہ_گر_پیغام_FLAG_FOURTHBUTTON 0x00000080
#تعریف_کرو اشارہ_گر_پیغام_FLAG_FIFTHBUTTON 0x00000100
#تعریف_کرو اشارہ_گر_پیغام_FLAG_PRIMARY 0x00002000
#تعریف_کرو اشارہ_گر_پیغام_FLAG_CONFIDENCE 0x00004000
#تعریف_کرو اشارہ_گر_پیغام_FLAG_CANCELED 0x00008000

#تعریف_کرو GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#تعریف_کرو IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#تعریف_کرو IS_اشارہ_گر_INCONTACT_WPARAM(wParam) IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, اشارہ_گر_پیغام_FLAG_INCONTACT)
#تعریف_کرو IS_اشارہ_گر_FIRSTBUTTON_WPARAM(wParam) IS_اشارہ_گر_FLAG_سیٹ_WPARAM(wParam, اشارہ_گر_پیغام_FLAG_FIRSTBUTTON)

قسمتعریف DWORD اشارہ_گر_داخلہ_TYPE;

شمار لیبل_اشارہ_گر_داخلہ_TYPE
{
    PT_اشارہ_گر = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

قسمتعریف UINT32 اشارہ_گر_FLAGS;

قسمتعریف UINT32 PEN_FLAGS;
#تعریف_کرو PEN_FLAG_NONE 0x00000000
#تعریف_کرو PEN_FLAG_BARREL 0x00000001
#تعریف_کرو PEN_FLAG_INVERTED 0x00000002
#تعریف_کرو PEN_FLAG_ERASER 0x00000004

قسمتعریف UINT32 PEN_نقاب;
#تعریف_کرو PEN_نقاب_NONE 0x00000000
#تعریف_کرو PEN_نقاب_PRESSURE 0x00000001
#تعریف_کرو PEN_نقاب_ROTATION 0x00000002
#تعریف_کرو PEN_نقاب_TILT_X 0x00000004
#تعریف_کرو PEN_نقاب_TILT_Y 0x00000008

قسمتعریف شمار لیبل_اشارہ_گر_BUTTON_CHANGE_TYPE
{
    اشارہ_گر_CHANGE_NONE,
    اشارہ_گر_CHANGE_FIRSTBUTTON_نیچے_کو,
    اشارہ_گر_CHANGE_FIRSTBUTTON_اوپر,
    اشارہ_گر_CHANGE_SECONDBUTTON_نیچے_کو,
    اشارہ_گر_CHANGE_SECONDBUTTON_اوپر,
    اشارہ_گر_CHANGE_THIRDBUTTON_نیچے_کو,
    اشارہ_گر_CHANGE_THIRDBUTTON_اوپر,
    اشارہ_گر_CHANGE_FOURTHBUTTON_نیچے_کو,
    اشارہ_گر_CHANGE_FOURTHBUTTON_اوپر,
    اشارہ_گر_CHANGE_FIFTHBUTTON_نیچے_کو,
    اشارہ_گر_CHANGE_FIFTHBUTTON_اوپر
} اشارہ_گر_BUTTON_CHANGE_TYPE;

قسمتعریف ساخت لیبل_اشارہ_گر_INFO
{
    اشارہ_گر_داخلہ_TYPE اشارہ_گر_Type;
    UINT32 اشارہ_گر_Id;
    UINT32 چوکھٹا_Id;
    اشارہ_گر_FLAGS اشارہ_گر_Flags;
    HANDLE ماخذ_Device;
    HWND hwnd_ہدف;
    نقطہ_2 ptPixelLocation;
    نقطہ_2 ptHimetricLocation;
    نقطہ_2 ptPixelLocationRaw;
    نقطہ_2 ptHimetricLocationRaw;
    DWORD dw_وقت;
    UINT32 history_گنتی;
    INT32 داخلہ_ڈیٹا;
    DWORD dw_کلید_حالتیں;
    UINT64 Performance_گنتی;
    اشارہ_گر_BUTTON_CHANGE_TYPE ButtonChangeType;
} اشارہ_گر_INFO;

قسمتعریف ساخت لیبل_اشارہ_گر_PEN_INFO
{
    اشارہ_گر_INFO اشارہ_گر_Info;
    PEN_FLAGS penFlags;
    PEN_نقاب pen_نقاب;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} اشارہ_گر_PEN_INFO;

#اگر_ختم // WINVER < _WIN32_WINNT_WIN8

#اگر_غیر_تعریف_شدہ HAVE_SHELLSCALINGAPI_H

قسمتعریف شمار MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

قسمتعریف شمار PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_فی_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#ورنہ
#شامل <shellscalingapi.h>
#اگر_ختم

قسمتعریف ساخت ITaskbarList3 ITaskbarList3;

#اگر_غیر_تعریف_شدہ _DPI_AWARENESS_CONTEXTS_

قسمتعریف شمار DPI_AWARENESS
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

#اگر_ختم // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#اگر NTDDI_نسخہ < 0x0A000003
#تعریف_کرو DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#اگر_ختم // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#اگر NTDDI_نسخہ < 0x0A000006
#تعریف_کرو DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#اگر_ختم // NTDDI_VERSION < 0x0A000006

قسمتعریف BOOL (*PFNSHFullScreen)(HWND, DWORD);
قسمتعریف خالی (*PFCoordTransform)(SDL_کھڑکی *, نقطہ_2 *);

قسمتعریف ساخت
{
    خالی **lpVtbl;
    صحیح refcount;
    خالی *ڈیٹا;
} TSFSink;

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
قسمتعریف ساخت لیبل_INPUTCONTEXT2
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
#اگر_ختم

// Corner rounding support  (Win 11+)
#اگر_غیر_تعریف_شدہ DWMWA_کھڑکی_کونا_PREFERENCE
#تعریف_کرو DWMWA_کھڑکی_کونا_PREFERENCE 33
#اگر_ختم
قسمتعریف شمار {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_باری = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_کھڑکی_کونا_PREFERENCE;

// Border Color support (Win 11+)
#اگر_غیر_تعریف_شدہ DWMWA_BORDER_COLOR
#تعریف_کرو DWMWA_BORDER_COLOR 34
#اگر_ختم

#اگر_غیر_تعریف_شدہ DWMWA_COLOR_DEFAULT
#تعریف_کرو DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#اگر_ختم

#اگر_غیر_تعریف_شدہ DWMWA_COLOR_NONE
#تعریف_کرو DWMWA_COLOR_NONE 0xFFFFFFFE
#اگر_ختم

// Transparent window support
#اگر_غیر_تعریف_شدہ DWM_BB_ENABLE
#تعریف_کرو DWM_BB_ENABLE 0x00000001
#اگر_ختم
#اگر_غیر_تعریف_شدہ DWM_BB_BLURREGION
#تعریف_کرو DWM_BB_BLURREGION 0x00000002
#اگر_ختم
قسمتعریف ساخت
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

ساخت SDL_Video_ڈیٹا
{
    صحیح render;

    bool coinitialized;
#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#اگر_ختم // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_گنتی;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_بفر_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_راستہ_INFO*, UINT32 *, DISPLAYCONFIG_منوال_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_سرخی*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_داخلہ_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_داخلہ_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, صحیح );
    BOOL (WINAPI *رجسٹر_Touch_کھڑکی)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(خالی);
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
    BOOL (WINAPI *سیٹ_Process_DPIAware)( خالی );
    BOOL (WINAPI *سیٹ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *سیٹ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( خالی );
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
#اگر_ختم                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شدہ HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#اگر_ختم

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_انحراف;
    UINT rawinput_سائز;
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

    WIN_Game_داخلہ_ڈیٹا *gameinput_context;

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
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
    صحیح ime_composition_لمبائی;
    WCHAR ime_readingstring[16];
    صحیح ime_cursor;
    صحیح ime_selected_آغاز;
    صحیح ime_selected_لمبائی;

    bool ime_candidates_open;
    bool ime_update_candidates;
    حرف *ime_candidates[MAX_CANDLIST];
    صحیح ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    صحیح ime_candlistindexbase;
    bool ime_horizontal_candidates;
#اگر_ختم

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_غیر_تعریف_شدہ SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_اشاریہ, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_کھڑکی)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_تالا_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_تالا_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#اگر_ختم // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_کلید_state[256];
    UINT _SDL_WAKEUP;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#اگر_ختم
};

خارجی bool g_Windows_Enable_پیغام_Loop;
خارجی bool g_WindowsEnableMenuMnemonics;
خارجی bool g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden;

قسمتعریف ساخت IDirect3D9 IDirect3D9;
خارجی bool D3_D_بھرو_DLL(خالی **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

خارجی SDL_SystemTheme WIN_GetSystemTheme(خالی);
خارجی bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#اگر_ختم // SDL_windowsvideo_h_
