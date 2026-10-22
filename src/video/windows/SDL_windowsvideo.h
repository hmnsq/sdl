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

#جيڪڏهن_وصف_نه_ٿيل SDL_windowsvideo_h_
#وصف_ڪريو SDL_windowsvideo_h_

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "../SDL_sysvideo.h"

#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
#جيڪڏهن_وصف_نه_ٿيل __cplusplus
#وصف_ڪريو CINTERFACE
#وصف_ڪريو COBJMACROS
#جيڪڏهن_پورو
#ضمن <dxgi.h>
#جيڪڏهن_پورو

#إذا defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ضمن <msctf.h>
#وإلا
#ضمن "SDL_msctf.h"
#جيڪڏهن_پورو

#ضمن <imm.h>

#وصف_ڪريو MAX_CANDLIST   10
#وصف_ڪريو MAX_CANDLENGTH 256
#وصف_ڪريو MAX_CANDSIZE   (حجم(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

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
#جيڪڏهن_پورو

#ضمن "SDL_windowswindow.h"

#جيڪڏهن_وصف_نه_ٿيل USER_DEFAULT_SCREEN_DPI
#وصف_ڪريو USER_DEFAULT_SCREEN_DPI 96
#جيڪڏهن_پورو

#إذا WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#وصف_ڪريو TWF_FINETOUCH 1
#وصف_ڪريو TWF_WANTPALM  2

#وصف_ڪريو TOUCHEVENTF_MOVE 0x0001
#وصف_ڪريو TOUCHEVENTF_هيٺ_ڏانهن 0x0002
#وصف_ڪريو TOUCHEVENTF_مٿي   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

تعريفنوع بنية _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_ذريعو;
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
تعريفنوع بنية DISPLAYCONFIG_رستو_ذريعو_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 گهڻائي_Info_Idx;
        بنية
        {
            UINT32 clone_گروهه_Id : 16;
            UINT32 ذريعو_گهڻائي_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 حالت_Flags;
} DISPLAYCONFIG_رستو_ذريعو_INFO;

تعريفنوع بنية DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

تعريفنوع بنية DISPLAYCONFIG_رستو_هدف_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 گهڻائي_Info_Idx;
        بنية
        {
            UINT32 desktop_گهڻائي_Info_Idx : 16;
            UINT32 هدف_گهڻائي_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_شرح_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جاچ_سٽ_Ordering;
    BOOL هدف_موجود;
    UINT32 حالت_Flags;
} DISPLAYCONFIG_رستو_هدف_INFO;

تعريفنوع بنية DISPLAYCONFIG_رستو_INFO
{
    DISPLAYCONFIG_رستو_ذريعو_INFO ذريعو_Info;
    DISPLAYCONFIG_رستو_هدف_INFO هدف_Info;
    UINT32 flags;
} DISPLAYCONFIG_رستو_INFO;

تعريفنوع تعداد
{
    DISPLAYCONFIG_گهڻائي_INFO_TYPE_ذريعو = 1,
    DISPLAYCONFIG_گهڻائي_INFO_TYPE_هدف = 2,
    DISPLAYCONFIG_گهڻائي_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_گهڻائي_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_گهڻائي_INFO_TYPE;

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
    DISPLAYCONFIG_2DREGION سرگرم_سائيز;
    DISPLAYCONFIG_2DREGION ڪل_سائيز;

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
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ جاچ_سٽ_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

تعريفنوع بنية DISPLAYCONFIG_ذريعو_گهڻائي
{
    UINT32 ويڪر;
    UINT32 اوچائي;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_ذريعو_گهڻائي;

تعريفنوع بنية DISPLAYCONFIG_هدف_گهڻائي
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO هدف_Video_Signal_Info;
} DISPLAYCONFIG_هدف_گهڻائي;

تعريفنوع بنية DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL رستو_ذريعو_سائيز;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

تعريفنوع بنية DISPLAYCONFIG_گهڻائي_INFO
{
    DISPLAYCONFIG_گهڻائي_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    اتحاد
    {
        DISPLAYCONFIG_هدف_گهڻائي هدف_گهڻائي;
        DISPLAYCONFIG_ذريعو_گهڻائي ذريعو_گهڻائي;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_گهڻائي_INFO;

تعريفنوع تعداد DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_اندروني = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

تعريفنوع تعداد
{
    DISPLAYCONFIG_DEVICE_INFO_GET_ذريعو_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_PREFERRED_گهڻائي = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_سيٽ_هدف_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_هدف_بنياد_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_سيٽ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_سيٽ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_DEVICE_INFO_سرو
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 سائيز;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_سرو;

تعريفنوع بنية DISPLAYCONFIG_ذريعو_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرو سرو;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_ذريعو_DEVICE_NAME;

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
        UINT32 قدر;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_هدف_DEVICE_NAME_FLAGS;

تعريفنوع بنية DISPLAYCONFIG_هدف_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرو سرو;
    DISPLAYCONFIG_هدف_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_حاصل_ضرب_ڪوڊ_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_رستو[128];
} DISPLAYCONFIG_هدف_DEVICE_NAME;

#وصف_ڪريو QDC_ONLY_سرگرم_PATHS 0x00000002

#جيڪڏهن_پورو // WINVER < _WIN32_WINNT_WIN7

#إذا WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#وصف_ڪريو اشارو_پيغام_FLAG_NEW 0x00000001
#وصف_ڪريو اشارو_پيغام_FLAG_INRANGE 0x00000002
#وصف_ڪريو اشارو_پيغام_FLAG_INCONTACT 0x00000004
#وصف_ڪريو اشارو_پيغام_FLAG_FIRSTBUTTON 0x00000010
#وصف_ڪريو اشارو_پيغام_FLAG_SECONDBUTTON 0x00000020
#وصف_ڪريو اشارو_پيغام_FLAG_THIRDBUTTON 0x00000040
#وصف_ڪريو اشارو_پيغام_FLAG_FOURTHBUTTON 0x00000080
#وصف_ڪريو اشارو_پيغام_FLAG_FIFTHBUTTON 0x00000100
#وصف_ڪريو اشارو_پيغام_FLAG_PRIMARY 0x00002000
#وصف_ڪريو اشارو_پيغام_FLAG_CONFIDENCE 0x00004000
#وصف_ڪريو اشارو_پيغام_FLAG_CANCELED 0x00008000

#وصف_ڪريو GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#وصف_ڪريو IS_اشارو_FLAG_سيٽ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#وصف_ڪريو IS_اشارو_INCONTACT_WPARAM(wParam) IS_اشارو_FLAG_سيٽ_WPARAM(wParam, اشارو_پيغام_FLAG_INCONTACT)
#وصف_ڪريو IS_اشارو_FIRSTBUTTON_WPARAM(wParam) IS_اشارو_FLAG_سيٽ_WPARAM(wParam, اشارو_پيغام_FLAG_FIRSTBUTTON)

تعريفنوع DWORD اشارو_داخلا_TYPE;

تعداد ٽيگ_اشارو_داخلا_TYPE
{
    PT_اشارو = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

تعريفنوع UINT32 اشارو_FLAGS;

تعريفنوع UINT32 PEN_FLAGS;
#وصف_ڪريو PEN_FLAG_NONE 0x00000000
#وصف_ڪريو PEN_FLAG_BARREL 0x00000001
#وصف_ڪريو PEN_FLAG_INVERTED 0x00000002
#وصف_ڪريو PEN_FLAG_ERASER 0x00000004

تعريفنوع UINT32 PEN_نقاب;
#وصف_ڪريو PEN_نقاب_NONE 0x00000000
#وصف_ڪريو PEN_نقاب_PRESSURE 0x00000001
#وصف_ڪريو PEN_نقاب_ROTATION 0x00000002
#وصف_ڪريو PEN_نقاب_TILT_X 0x00000004
#وصف_ڪريو PEN_نقاب_TILT_Y 0x00000008

تعريفنوع تعداد ٽيگ_اشارو_BUTTON_CHANGE_TYPE
{
    اشارو_CHANGE_NONE,
    اشارو_CHANGE_FIRSTBUTTON_هيٺ_ڏانهن,
    اشارو_CHANGE_FIRSTBUTTON_مٿي,
    اشارو_CHANGE_SECONDBUTTON_هيٺ_ڏانهن,
    اشارو_CHANGE_SECONDBUTTON_مٿي,
    اشارو_CHANGE_THIRDBUTTON_هيٺ_ڏانهن,
    اشارو_CHANGE_THIRDBUTTON_مٿي,
    اشارو_CHANGE_FOURTHBUTTON_هيٺ_ڏانهن,
    اشارو_CHANGE_FOURTHBUTTON_مٿي,
    اشارو_CHANGE_FIFTHBUTTON_هيٺ_ڏانهن,
    اشارو_CHANGE_FIFTHBUTTON_مٿي
} اشارو_BUTTON_CHANGE_TYPE;

تعريفنوع بنية ٽيگ_اشارو_INFO
{
    اشارو_داخلا_TYPE اشارو_Type;
    UINT32 اشارو_Id;
    UINT32 چوکٺو_Id;
    اشارو_FLAGS اشارو_Flags;
    HANDLE ذريعو_Device;
    HWND hwnd_هدف;
    نقطو_2 ptPixelLocation;
    نقطو_2 ptHimetricLocation;
    نقطو_2 ptPixelLocationRaw;
    نقطو_2 ptHimetricLocationRaw;
    DWORD dw_وقت;
    UINT32 history_ڳڻپ;
    INT32 داخلا_معلومات;
    DWORD dw_ڪنجي_حالتون;
    UINT64 Performance_ڳڻپ;
    اشارو_BUTTON_CHANGE_TYPE ButtonChangeType;
} اشارو_INFO;

تعريفنوع بنية ٽيگ_اشارو_PEN_INFO
{
    اشارو_INFO اشارو_Info;
    PEN_FLAGS penFlags;
    PEN_نقاب pen_نقاب;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} اشارو_PEN_INFO;

#جيڪڏهن_پورو // WINVER < _WIN32_WINNT_WIN8

#جيڪڏهن_وصف_نه_ٿيل HAVE_SHELLSCALINGAPI_H

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
    PROCESS_في_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#وإلا
#ضمن <shellscalingapi.h>
#جيڪڏهن_پورو

تعريفنوع بنية ITaskbarList3 ITaskbarList3;

#جيڪڏهن_وصف_نه_ٿيل _DPI_AWARENESS_CONTEXTS_

تعريفنوع تعداد DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_في_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#وصف_ڪريو DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#وصف_ڪريو DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#وصف_ڪريو DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#جيڪڏهن_پورو // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#إذا NTDDI_نسخو < 0x0A000003
#وصف_ڪريو DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#جيڪڏهن_پورو // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#إذا NTDDI_نسخو < 0x0A000006
#وصف_ڪريو DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#جيڪڏهن_پورو // NTDDI_VERSION < 0x0A000006

تعريفنوع BOOL (*PFNSHFullScreen)(HWND, DWORD);
تعريفنوع فراغ (*PFCoordTransform)(SDL_دري *, نقطو_2 *);

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    فراغ *معلومات;
} TSFSink;

#جيڪڏهن_وصف_نه_ٿيل SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
تعريفنوع بنية ٽيگ_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    نقطو_2 pt_حالت_Wnd_Pos;
    نقطو_2 ptSoftKbdPos;
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
    HIMCC h_Guide_سٽ;
    HIMCC h_ذاتي;
    DWORD dw_انگ_نياپو_Buf;
    HIMCC h_نياپو_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#جيڪڏهن_پورو

// Corner rounding support  (Win 11+)
#جيڪڏهن_وصف_نه_ٿيل DWMWA_دري_ڪنڊ_PREFERENCE
#وصف_ڪريو DWMWA_دري_ڪنڊ_PREFERENCE 33
#جيڪڏهن_پورو
تعريفنوع تعداد {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_ڦيرو = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_دري_ڪنڊ_PREFERENCE;

// Border Color support (Win 11+)
#جيڪڏهن_وصف_نه_ٿيل DWMWA_BORDER_COLOR
#وصف_ڪريو DWMWA_BORDER_COLOR 34
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل DWMWA_COLOR_DEFAULT
#وصف_ڪريو DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل DWMWA_COLOR_NONE
#وصف_ڪريو DWMWA_COLOR_NONE 0xFFFFFFFE
#جيڪڏهن_پورو

// Transparent window support
#جيڪڏهن_وصف_نه_ٿيل DWM_BB_ENABLE
#وصف_ڪريو DWM_BB_ENABLE 0x00000001
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل DWM_BB_BLURREGION
#وصف_ڪريو DWM_BB_BLURREGION 0x00000002
#جيڪڏهن_پورو
تعريفنوع بنية
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

بنية SDL_Video_معلومات
{
    صحيح render;

    bool coinitialized;
#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#جيڪڏهن_پورو // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_ڳڻپ;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_بفر_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_رستو_INFO*, UINT32 *, DISPLAYCONFIG_گهڻائي_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_سرو*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_داخلا_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_داخلا_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح );
    BOOL (WINAPI *رجسٽر_Touch_دري)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(فراغ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_دري)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_سيٽ_دري_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_اشارو_Type)(UINT32 اشارو_Id, اشارو_داخلا_TYPE *اشارو_Type);
    BOOL (WINAPI *Get_اشارو_Pen_Info)(UINT32 اشارو_Id, اشارو_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_اشارو_Device_Rects)(HANDLE device, RECT *اشارو_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *سيٽ_Process_DPIAware)( فراغ );
    BOOL (WINAPI *سيٽ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *سيٽ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( فراغ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_دري_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_دري)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *سيٽ_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#جيڪڏهن_پورو                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جيڪڏهن_وصف_ٿيل HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#جيڪڏهن_پورو

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_وٿي;
    UINT rawinput_سائيز;
    UINT rawinput_ڳڻپ;
    Uint64 آخري_rawinput_poll;
    SDL_نقطو آخري_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_ڪنجي_sequence;
    SDL_PenID raw_داخلا_fake_pen_id;

    WIN_Game_داخلا_معلومات *gameinput_context;

#جيڪڏهن_وصف_نه_ٿيل SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_موجود;
    bool ime_اندروني_composition;
    bool ime_اندروني_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    صحيح ime_composition_ڊيگهائي;
    WCHAR ime_readingstring[16];
    صحيح ime_cursor;
    صحيح ime_selected_شروعات;
    صحيح ime_selected_ڊيگهائي;

    bool ime_candidates_open;
    bool ime_update_candidates;
    حرف *ime_candidates[MAX_CANDLIST];
    صحيح ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    صحيح ime_candlistindexbase;
    bool ime_horizontal_candidates;
#جيڪڏهن_پورو

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جيڪڏهن_وصف_نه_ٿيل SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_اشاريو, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_دري)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_تالو_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_تالو_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#جيڪڏهن_پورو // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_ڪنجي_state[256];
    UINT _SDL_WAKEUP;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#جيڪڏهن_پورو
};

خارجي bool g_Windows_Enable_پيغام_Loop;
خارجي bool g_WindowsEnableMenuMnemonics;
خارجي bool g_دري_چوکٺو_Usable_While_Cursor_Hidden;

تعريفنوع بنية IDirect3D9 IDirect3D9;
خارجي bool D3_D_ڀريو_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

خارجي SDL_SystemTheme WIN_GetSystemTheme(فراغ);
خارجي bool WIN_Is_في_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#جيڪڏهن_پورو // SDL_windowsvideo_h_
