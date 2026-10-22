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

#که_نه_تعریف_شوی SDL_windowsvideo_h_
#تعریف_کړه SDL_windowsvideo_h_

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "../SDL_sysvideo.h"

#که_تعریف_شوی HAVE_DXGI_H
#که_نه_تعریف_شوی __cplusplus
#تعریف_کړه CINTERFACE
#تعریف_کړه COBJMACROS
#د_که_پای
#ضمن <dxgi.h>
#د_که_پای

#إذا defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ضمن <msctf.h>
#وإلا
#ضمن "SDL_msctf.h"
#د_که_پای

#ضمن <imm.h>

#تعریف_کړه MAX_CANDLIST   10
#تعریف_کړه MAX_CANDLENGTH 256
#تعریف_کړه MAX_CANDSIZE   (حجم(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

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
#د_که_پای

#ضمن "SDL_windowswindow.h"

#که_نه_تعریف_شوی USER_DEFAULT_SCREEN_DPI
#تعریف_کړه USER_DEFAULT_SCREEN_DPI 96
#د_که_پای

#إذا WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#تعریف_کړه TWF_FINETOUCH 1
#تعریف_کړه TWF_WANTPALM  2

#تعریف_کړه TOUCHEVENTF_MOVE 0x0001
#تعریف_کړه TOUCHEVENTF_ښکته 0x0002
#تعریف_کړه TOUCHEVENTF_پورته   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

تعريفنوع بنية _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_سرچینه;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_ماسک;
    DWORD dw_وخت;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
تعريفنوع بنية DISPLAYCONFIG_لار_سرچینه_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 ډېرپېښ_Info_Idx;
        بنية
        {
            UINT32 clone_ډله_Id : 16;
            UINT32 سرچینه_ډېرپېښ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 حالت_Flags;
} DISPLAYCONFIG_لار_سرچینه_INFO;

تعريفنوع بنية DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

تعريفنوع بنية DISPLAYCONFIG_لار_موخه_INFO
{
    LUID adapterId;
    UINT32 id;
    اتحاد
    {
        UINT32 ډېرپېښ_Info_Idx;
        بنية
        {
            UINT32 desktop_ډېرپېښ_Info_Idx : 16;
            UINT32 موخه_ډېرپېښ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_شرح_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ لټون_کرښه_Ordering;
    BOOL موخه_شته;
    UINT32 حالت_Flags;
} DISPLAYCONFIG_لار_موخه_INFO;

تعريفنوع بنية DISPLAYCONFIG_لار_INFO
{
    DISPLAYCONFIG_لار_سرچینه_INFO سرچینه_Info;
    DISPLAYCONFIG_لار_موخه_INFO موخه_Info;
    UINT32 flags;
} DISPLAYCONFIG_لار_INFO;

تعريفنوع تعداد
{
    DISPLAYCONFIG_ډېرپېښ_INFO_TYPE_سرچینه = 1,
    DISPLAYCONFIG_ډېرپېښ_INFO_TYPE_موخه = 2,
    DISPLAYCONFIG_ډېرپېښ_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_ډېرپېښ_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_ډېرپېښ_INFO_TYPE;

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
    DISPLAYCONFIG_2DREGION فعال_اندازه;
    DISPLAYCONFIG_2DREGION ټول_اندازه;

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
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ لټون_کرښه_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

تعريفنوع بنية DISPLAYCONFIG_سرچینه_ډېرپېښ
{
    UINT32 پلنوالی;
    UINT32 لوړوالی;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_سرچینه_ډېرپېښ;

تعريفنوع بنية DISPLAYCONFIG_موخه_ډېرپېښ
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO موخه_Video_Signal_Info;
} DISPLAYCONFIG_موخه_ډېرپېښ;

تعريفنوع بنية DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL لار_سرچینه_اندازه;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

تعريفنوع بنية DISPLAYCONFIG_ډېرپېښ_INFO
{
    DISPLAYCONFIG_ډېرپېښ_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    اتحاد
    {
        DISPLAYCONFIG_موخه_ډېرپېښ موخه_ډېرپېښ;
        DISPLAYCONFIG_سرچینه_ډېرپېښ سرچینه_ډېرپېښ;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ډېرپېښ_INFO;

تعريفنوع تعداد DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_دننی = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

تعريفنوع تعداد
{
    DISPLAYCONFIG_DEVICE_INFO_GET_سرچینه_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_موخه_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_موخه_PREFERRED_ډېرپېښ = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_سېټ_موخه_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_موخه_بنسټ_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_سېټ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_سېټ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

تعريفنوع بنية DISPLAYCONFIG_DEVICE_INFO_سرلیک
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 اندازه;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_سرلیک;

تعريفنوع بنية DISPLAYCONFIG_سرچینه_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرلیک سرلیک;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_سرچینه_DEVICE_NAME;

تعريفنوع بنية DISPLAYCONFIG_موخه_DEVICE_NAME_FLAGS
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
        UINT32 ارزښت;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_موخه_DEVICE_NAME_FLAGS;

تعريفنوع بنية DISPLAYCONFIG_موخه_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_سرلیک سرلیک;
    DISPLAYCONFIG_موخه_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_حاصل_ضرب_کوډ_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_لار[128];
} DISPLAYCONFIG_موخه_DEVICE_NAME;

#تعریف_کړه QDC_ONLY_فعال_PATHS 0x00000002

#د_که_پای // WINVER < _WIN32_WINNT_WIN7

#إذا WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#تعریف_کړه اشاره_ګر_پیغام_FLAG_NEW 0x00000001
#تعریف_کړه اشاره_ګر_پیغام_FLAG_INRANGE 0x00000002
#تعریف_کړه اشاره_ګر_پیغام_FLAG_INCONTACT 0x00000004
#تعریف_کړه اشاره_ګر_پیغام_FLAG_FIRSTBUTTON 0x00000010
#تعریف_کړه اشاره_ګر_پیغام_FLAG_SECONDBUTTON 0x00000020
#تعریف_کړه اشاره_ګر_پیغام_FLAG_THIRDBUTTON 0x00000040
#تعریف_کړه اشاره_ګر_پیغام_FLAG_FOURTHBUTTON 0x00000080
#تعریف_کړه اشاره_ګر_پیغام_FLAG_FIFTHBUTTON 0x00000100
#تعریف_کړه اشاره_ګر_پیغام_FLAG_PRIMARY 0x00002000
#تعریف_کړه اشاره_ګر_پیغام_FLAG_CONFIDENCE 0x00004000
#تعریف_کړه اشاره_ګر_پیغام_FLAG_CANCELED 0x00008000

#تعریف_کړه GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#تعریف_کړه IS_اشاره_ګر_FLAG_سېټ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#تعریف_کړه IS_اشاره_ګر_INCONTACT_WPARAM(wParam) IS_اشاره_ګر_FLAG_سېټ_WPARAM(wParam, اشاره_ګر_پیغام_FLAG_INCONTACT)
#تعریف_کړه IS_اشاره_ګر_FIRSTBUTTON_WPARAM(wParam) IS_اشاره_ګر_FLAG_سېټ_WPARAM(wParam, اشاره_ګر_پیغام_FLAG_FIRSTBUTTON)

تعريفنوع DWORD اشاره_ګر_ننوت_TYPE;

تعداد نښان_اشاره_ګر_ننوت_TYPE
{
    PT_اشاره_ګر = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

تعريفنوع UINT32 اشاره_ګر_FLAGS;

تعريفنوع UINT32 PEN_FLAGS;
#تعریف_کړه PEN_FLAG_NONE 0x00000000
#تعریف_کړه PEN_FLAG_BARREL 0x00000001
#تعریف_کړه PEN_FLAG_INVERTED 0x00000002
#تعریف_کړه PEN_FLAG_ERASER 0x00000004

تعريفنوع UINT32 PEN_ماسک;
#تعریف_کړه PEN_ماسک_NONE 0x00000000
#تعریف_کړه PEN_ماسک_PRESSURE 0x00000001
#تعریف_کړه PEN_ماسک_ROTATION 0x00000002
#تعریف_کړه PEN_ماسک_TILT_X 0x00000004
#تعریف_کړه PEN_ماسک_TILT_Y 0x00000008

تعريفنوع تعداد نښان_اشاره_ګر_BUTTON_CHANGE_TYPE
{
    اشاره_ګر_CHANGE_NONE,
    اشاره_ګر_CHANGE_FIRSTBUTTON_ښکته,
    اشاره_ګر_CHANGE_FIRSTBUTTON_پورته,
    اشاره_ګر_CHANGE_SECONDBUTTON_ښکته,
    اشاره_ګر_CHANGE_SECONDBUTTON_پورته,
    اشاره_ګر_CHANGE_THIRDBUTTON_ښکته,
    اشاره_ګر_CHANGE_THIRDBUTTON_پورته,
    اشاره_ګر_CHANGE_FOURTHBUTTON_ښکته,
    اشاره_ګر_CHANGE_FOURTHBUTTON_پورته,
    اشاره_ګر_CHANGE_FIFTHBUTTON_ښکته,
    اشاره_ګر_CHANGE_FIFTHBUTTON_پورته
} اشاره_ګر_BUTTON_CHANGE_TYPE;

تعريفنوع بنية نښان_اشاره_ګر_INFO
{
    اشاره_ګر_ننوت_TYPE اشاره_ګر_Type;
    UINT32 اشاره_ګر_Id;
    UINT32 چوکاټ_Id;
    اشاره_ګر_FLAGS اشاره_ګر_Flags;
    HANDLE سرچینه_Device;
    HWND hwnd_موخه;
    ټکی_2 ptPixelLocation;
    ټکی_2 ptHimetricLocation;
    ټکی_2 ptPixelLocationRaw;
    ټکی_2 ptHimetricLocationRaw;
    DWORD dw_وخت;
    UINT32 history_شمېر;
    INT32 ننوت_معلومات;
    DWORD dw_کلی_حالتونه;
    UINT64 Performance_شمېر;
    اشاره_ګر_BUTTON_CHANGE_TYPE ButtonChangeType;
} اشاره_ګر_INFO;

تعريفنوع بنية نښان_اشاره_ګر_PEN_INFO
{
    اشاره_ګر_INFO اشاره_ګر_Info;
    PEN_FLAGS penFlags;
    PEN_ماسک pen_ماسک;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} اشاره_ګر_PEN_INFO;

#د_که_پای // WINVER < _WIN32_WINNT_WIN8

#که_نه_تعریف_شوی HAVE_SHELLSCALINGAPI_H

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
#د_که_پای

تعريفنوع بنية ITaskbarList3 ITaskbarList3;

#که_نه_تعریف_شوی _DPI_AWARENESS_CONTEXTS_

تعريفنوع تعداد DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_فی_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#تعریف_کړه DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#تعریف_کړه DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#تعریف_کړه DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#د_که_پای // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#إذا NTDDI_نسخه < 0x0A000003
#تعریف_کړه DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#د_که_پای // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#إذا NTDDI_نسخه < 0x0A000006
#تعریف_کړه DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#د_که_پای // NTDDI_VERSION < 0x0A000006

تعريفنوع BOOL (*PFNSHFullScreen)(HWND, DWORD);
تعريفنوع فراغ (*PFCoordTransform)(SDL_کړکۍ *, ټکی_2 *);

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    فراغ *معلومات;
} TSFSink;

#که_نه_تعریف_شوی SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
تعريفنوع بنية نښان_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    ټکی_2 pt_حالت_Wnd_Pos;
    ټکی_2 ptSoftKbdPos;
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
    HIMCC h_Guide_کرښه;
    HIMCC h_شخصي;
    DWORD dw_عدد_پیغام_Buf;
    HIMCC h_پیغام_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#د_که_پای

// Corner rounding support  (Win 11+)
#که_نه_تعریف_شوی DWMWA_کړکۍ_کونج_PREFERENCE
#تعریف_کړه DWMWA_کړکۍ_کونج_PREFERENCE 33
#د_که_پای
تعريفنوع تعداد {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_پړاو = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_کړکۍ_کونج_PREFERENCE;

// Border Color support (Win 11+)
#که_نه_تعریف_شوی DWMWA_BORDER_COLOR
#تعریف_کړه DWMWA_BORDER_COLOR 34
#د_که_پای

#که_نه_تعریف_شوی DWMWA_COLOR_DEFAULT
#تعریف_کړه DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#د_که_پای

#که_نه_تعریف_شوی DWMWA_COLOR_NONE
#تعریف_کړه DWMWA_COLOR_NONE 0xFFFFFFFE
#د_که_پای

// Transparent window support
#که_نه_تعریف_شوی DWM_BB_ENABLE
#تعریف_کړه DWM_BB_ENABLE 0x00000001
#د_که_پای
#که_نه_تعریف_شوی DWM_BB_BLURREGION
#تعریف_کړه DWM_BB_BLURREGION 0x00000002
#د_که_پای
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
#د_که_پای // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_شمېر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_بفر_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_لار_INFO*, UINT32 *, DISPLAYCONFIG_ډېرپېښ_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_سرلیک*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_ننوت_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_ننوت_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, صحيح );
    BOOL (WINAPI *ثبتوونکی_Touch_کړکۍ)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(فراغ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_کړکۍ)(HWND hwnd, ثابت DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_سېټ_کړکۍ_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_اشاره_ګر_Type)(UINT32 اشاره_ګر_Id, اشاره_ګر_ننوت_TYPE *اشاره_ګر_Type);
    BOOL (WINAPI *Get_اشاره_ګر_Pen_Info)(UINT32 اشاره_ګر_Id, اشاره_ګر_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_اشاره_ګر_Device_Rects)(HANDLE device, RECT *اشاره_ګر_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *سېټ_Process_DPIAware)( فراغ );
    BOOL (WINAPI *سېټ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *سېټ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( فراغ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_کړکۍ_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_کړکۍ)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *سېټ_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#د_که_پای                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#که_تعریف_شوی HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#د_که_پای

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_دننه_واټن;
    UINT rawinput_اندازه;
    UINT rawinput_شمېر;
    Uint64 وروستی_rawinput_poll;
    SDL_ټکی وروستی_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_کلی_sequence;
    SDL_PenID raw_ننوت_fake_pen_id;

    WIN_Game_ننوت_معلومات *gameinput_context;

#که_نه_تعریف_شوی SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_شته;
    bool ime_دننی_composition;
    bool ime_دننی_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    صحيح ime_composition_اوږدتیا;
    WCHAR ime_readingstring[16];
    صحيح ime_cursor;
    صحيح ime_selected_پیل;
    صحيح ime_selected_اوږدتیا;

    bool ime_candidates_open;
    bool ime_update_candidates;
    حرف *ime_candidates[MAX_CANDLIST];
    صحيح ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    صحيح ime_candlistindexbase;
    bool ime_horizontal_candidates;
#د_که_پای

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#که_نه_تعریف_شوی SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_شاخص, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_کړکۍ)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_قلف_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_قلف_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#د_که_پای // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_کلی_state[256];
    UINT _SDL_WAKEUP;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#د_که_پای
};

خارجي bool g_Windows_Enable_پیغام_Loop;
خارجي bool g_WindowsEnableMenuMnemonics;
خارجي bool g_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden;

تعريفنوع بنية IDirect3D9 IDirect3D9;
خارجي bool D3_D_بارول_DLL(فراغ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

خارجي SDL_SystemTheme WIN_GetSystemTheme(فراغ);
خارجي bool WIN_Is_فی_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#د_که_پای // SDL_windowsvideo_h_
