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

#నిర్వచితం_కాకపోతే SDL_windowsvideo_h_
#నిర్వచించు SDL_windowsvideo_h_

#అన్తర్భావ "../../core/windows/SDL_windows.h"

#అన్తర్భావ "../SDL_sysvideo.h"

#నిర్వచితమైతే HAVE_DXGI_H
#నిర్వచితం_కాకపోతే __cplusplus
#నిర్వచించు CINTERFACE
#నిర్వచించు COBJMACROS
#అయితే_ముగింపు
#అన్తర్భావ <dxgi.h>
#అయితే_ముగింపు

#ఒకవేళ defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#అన్తర్భావ <msctf.h>
#లేకపోతే
#అన్తర్భావ "SDL_msctf.h"
#అయితే_ముగింపు

#అన్తర్భావ <imm.h>

#నిర్వచించు MAX_CANDLIST   10
#నిర్వచించు MAX_CANDLENGTH 256
#నిర్వచించు MAX_CANDSIZE   (పరిమాణం(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#అన్తర్భావ "SDL_windowsclipboard.h"
#అన్తర్భావ "SDL_windowsevents.h"
#అన్తర్భావ "SDL_windowsgameinput.h"
#అన్తర్భావ "SDL_windowsopengl.h"

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#అన్తర్భావ "SDL_windowsshape.h"
#అన్తర్భావ "SDL_windowskeyboard.h"
#అన్తర్భావ "SDL_windowsmodes.h"
#అన్తర్భావ "SDL_windowsmouse.h"
#అన్తర్భావ "SDL_windowsopengles.h"
#అయితే_ముగింపు

#అన్తర్భావ "SDL_windowswindow.h"

#నిర్వచితం_కాకపోతే USER_DEFAULT_SCREEN_DPI
#నిర్వచించు USER_DEFAULT_SCREEN_DPI 96
#అయితే_ముగింపు

#ఒకవేళ WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#నిర్వచించు TWF_FINETOUCH 1
#నిర్వచించు TWF_WANTPALM  2

#నిర్వచించు TOUCHEVENTF_MOVE 0x0001
#నిర్వచించు TOUCHEVENTF_కిందికి 0x0002
#నిర్వచించు TOUCHEVENTF_పైకి   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

రకనిర్వచనం నిర్మాణం _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_ఆధారం;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_ముసుగు;
    DWORD dw_సమయం;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_మార్గం_ఆధారం_INFO
{
    LUID adapterId;
    UINT32 id;
    సంఘం
    {
        UINT32 బహుళకం_Info_Idx;
        నిర్మాణం
        {
            UINT32 clone_సమూహం_Id : 16;
            UINT32 ఆధారం_బహుళకం_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 స్థితి_Flags;
} DISPLAYCONFIG_మార్గం_ఆధారం_INFO;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_మార్గం_లక్ష్యం_INFO
{
    LUID adapterId;
    UINT32 id;
    సంఘం
    {
        UINT32 బహుళకం_Info_Idx;
        నిర్మాణం
        {
            UINT32 desktop_బహుళకం_Info_Idx : 16;
            UINT32 లక్ష్యం_బహుళకం_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_రేటు_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ పరిశీలన_పంక్తి_Ordering;
    BOOL లక్ష్యం_అందుబాటు;
    UINT32 స్థితి_Flags;
} DISPLAYCONFIG_మార్గం_లక్ష్యం_INFO;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_మార్గం_INFO
{
    DISPLAYCONFIG_మార్గం_ఆధారం_INFO ఆధారం_Info;
    DISPLAYCONFIG_మార్గం_లక్ష్యం_INFO లక్ష్యం_Info;
    UINT32 flags;
} DISPLAYCONFIG_మార్గం_INFO;

రకనిర్వచనం గణన
{
    DISPLAYCONFIG_బహుళకం_INFO_TYPE_ఆధారం = 1,
    DISPLAYCONFIG_బహుళకం_INFO_TYPE_లక్ష్యం = 2,
    DISPLAYCONFIG_బహుళకం_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_బహుళకం_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_బహుళకం_INFO_TYPE;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_రేటు;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION చురుకైన_కొలత;
    DISPLAYCONFIG_2DREGION మొత్తం_కొలత;

    సంఘం
    {
        నిర్మాణం
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ పరిశీలన_పంక్తి_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_ఆధారం_బహుళకం
{
    UINT32 వెడల్పు;
    UINT32 ఎత్తు;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_ఆధారం_బహుళకం;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_లక్ష్యం_బహుళకం
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO లక్ష్యం_Video_Signal_Info;
} DISPLAYCONFIG_లక్ష్యం_బహుళకం;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL మార్గం_ఆధారం_కొలత;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_బహుళకం_INFO
{
    DISPLAYCONFIG_బహుళకం_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    సంఘం
    {
        DISPLAYCONFIG_లక్ష్యం_బహుళకం లక్ష్యం_బహుళకం;
        DISPLAYCONFIG_ఆధారం_బహుళకం ఆధారం_బహుళకం;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_బహుళకం_INFO;

రకనిర్వచనం గణన DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_అంతర్గత = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

రకనిర్వచనం గణన
{
    DISPLAYCONFIG_DEVICE_INFO_GET_ఆధారం_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_లక్ష్యం_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_లక్ష్యం_PREFERRED_బహుళకం = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_సమితి_లక్ష్యం_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_లక్ష్యం_పునాది_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_సమితి_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_సమితి_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_DEVICE_INFO_శీర్షిక
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 కొలత;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_శీర్షిక;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_ఆధారం_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_శీర్షిక శీర్షిక;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_ఆధారం_DEVICE_NAME;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME_FLAGS
{
    సంఘం
    {
        నిర్మాణం
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 విలువ;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME_FLAGS;

రకనిర్వచనం నిర్మాణం DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_శీర్షిక శీర్షిక;
    DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_లబ్ధం_సంకేతం_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_మార్గం[128];
} DISPLAYCONFIG_లక్ష్యం_DEVICE_NAME;

#నిర్వచించు QDC_ONLY_చురుకైన_PATHS 0x00000002

#అయితే_ముగింపు // WINVER < _WIN32_WINNT_WIN7

#ఒకవేళ WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#నిర్వచించు సూచిక_సందేశం_FLAG_NEW 0x00000001
#నిర్వచించు సూచిక_సందేశం_FLAG_INRANGE 0x00000002
#నిర్వచించు సూచిక_సందేశం_FLAG_INCONTACT 0x00000004
#నిర్వచించు సూచిక_సందేశం_FLAG_FIRSTBUTTON 0x00000010
#నిర్వచించు సూచిక_సందేశం_FLAG_SECONDBUTTON 0x00000020
#నిర్వచించు సూచిక_సందేశం_FLAG_THIRDBUTTON 0x00000040
#నిర్వచించు సూచిక_సందేశం_FLAG_FOURTHBUTTON 0x00000080
#నిర్వచించు సూచిక_సందేశం_FLAG_FIFTHBUTTON 0x00000100
#నిర్వచించు సూచిక_సందేశం_FLAG_PRIMARY 0x00002000
#నిర్వచించు సూచిక_సందేశం_FLAG_CONFIDENCE 0x00004000
#నిర్వచించు సూచిక_సందేశం_FLAG_CANCELED 0x00008000

#నిర్వచించు GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#నిర్వచించు IS_సూచిక_FLAG_సమితి_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#నిర్వచించు IS_సూచిక_INCONTACT_WPARAM(wParam) IS_సూచిక_FLAG_సమితి_WPARAM(wParam, సూచిక_సందేశం_FLAG_INCONTACT)
#నిర్వచించు IS_సూచిక_FIRSTBUTTON_WPARAM(wParam) IS_సూచిక_FLAG_సమితి_WPARAM(wParam, సూచిక_సందేశం_FLAG_FIRSTBUTTON)

రకనిర్వచనం DWORD సూచిక_ఆదానం_TYPE;

గణన ట్యాగ్_సూచిక_ఆదానం_TYPE
{
    PT_సూచిక = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

రకనిర్వచనం UINT32 సూచిక_FLAGS;

రకనిర్వచనం UINT32 PEN_FLAGS;
#నిర్వచించు PEN_FLAG_NONE 0x00000000
#నిర్వచించు PEN_FLAG_BARREL 0x00000001
#నిర్వచించు PEN_FLAG_INVERTED 0x00000002
#నిర్వచించు PEN_FLAG_ERASER 0x00000004

రకనిర్వచనం UINT32 PEN_ముసుగు;
#నిర్వచించు PEN_ముసుగు_NONE 0x00000000
#నిర్వచించు PEN_ముసుగు_PRESSURE 0x00000001
#నిర్వచించు PEN_ముసుగు_ROTATION 0x00000002
#నిర్వచించు PEN_ముసుగు_TILT_X 0x00000004
#నిర్వచించు PEN_ముసుగు_TILT_Y 0x00000008

రకనిర్వచనం గణన ట్యాగ్_సూచిక_BUTTON_CHANGE_TYPE
{
    సూచిక_CHANGE_NONE,
    సూచిక_CHANGE_FIRSTBUTTON_కిందికి,
    సూచిక_CHANGE_FIRSTBUTTON_పైకి,
    సూచిక_CHANGE_SECONDBUTTON_కిందికి,
    సూచిక_CHANGE_SECONDBUTTON_పైకి,
    సూచిక_CHANGE_THIRDBUTTON_కిందికి,
    సూచిక_CHANGE_THIRDBUTTON_పైకి,
    సూచిక_CHANGE_FOURTHBUTTON_కిందికి,
    సూచిక_CHANGE_FOURTHBUTTON_పైకి,
    సూచిక_CHANGE_FIFTHBUTTON_కిందికి,
    సూచిక_CHANGE_FIFTHBUTTON_పైకి
} సూచిక_BUTTON_CHANGE_TYPE;

రకనిర్వచనం నిర్మాణం ట్యాగ్_సూచిక_INFO
{
    సూచిక_ఆదానం_TYPE సూచిక_Type;
    UINT32 సూచిక_Id;
    UINT32 చట్రం_Id;
    సూచిక_FLAGS సూచిక_Flags;
    HANDLE ఆధారం_Device;
    HWND hwnd_లక్ష్యం;
    బిందువు_2 ptPixelLocation;
    బిందువు_2 ptHimetricLocation;
    బిందువు_2 ptPixelLocationRaw;
    బిందువు_2 ptHimetricLocationRaw;
    DWORD dw_సమయం;
    UINT32 history_లెక్క;
    INT32 ఆదానం_దత్తాంశం;
    DWORD dw_కీలకం_స్థితులు;
    UINT64 Performance_లెక్క;
    సూచిక_BUTTON_CHANGE_TYPE ButtonChangeType;
} సూచిక_INFO;

రకనిర్వచనం నిర్మాణం ట్యాగ్_సూచిక_PEN_INFO
{
    సూచిక_INFO సూచిక_Info;
    PEN_FLAGS penFlags;
    PEN_ముసుగు pen_ముసుగు;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} సూచిక_PEN_INFO;

#అయితే_ముగింపు // WINVER < _WIN32_WINNT_WIN8

#నిర్వచితం_కాకపోతే HAVE_SHELLSCALINGAPI_H

రకనిర్వచనం గణన MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

రకనిర్వచనం గణన PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_చొప్పున_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#లేకపోతే
#అన్తర్భావ <shellscalingapi.h>
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం ITaskbarList3 ITaskbarList3;

#నిర్వచితం_కాకపోతే _DPI_AWARENESS_CONTEXTS_

రకనిర్వచనం గణన DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_చొప్పున_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#నిర్వచించు DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#నిర్వచించు DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#నిర్వచించు DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#అయితే_ముగింపు // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#ఒకవేళ NTDDI_సంస్కరణ < 0x0A000003
#నిర్వచించు DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#అయితే_ముగింపు // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#ఒకవేళ NTDDI_సంస్కరణ < 0x0A000006
#నిర్వచించు DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#అయితే_ముగింపు // NTDDI_VERSION < 0x0A000006

రకనిర్వచనం BOOL (*PFNSHFullScreen)(HWND, DWORD);
రకనిర్వచనం శూన్య (*PFCoordTransform)(SDL_కిటికీ *, బిందువు_2 *);

రకనిర్వచనం నిర్మాణం
{
    శూన్య **lpVtbl;
    పూర్ణాంకం refcount;
    శూన్య *దత్తాంశం;
} TSFSink;

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
రకనిర్వచనం నిర్మాణం ట్యాగ్_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    బిందువు_2 pt_స్థితి_Wnd_Pos;
    బిందువు_2 ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    సంఘం
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_పంక్తి;
    HIMCC h_వ్యక్తిగత;
    DWORD dw_అంకె_సందేశం_Buf;
    HIMCC h_సందేశం_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#అయితే_ముగింపు

// Corner rounding support  (Win 11+)
#నిర్వచితం_కాకపోతే DWMWA_కిటికీ_మూల_PREFERENCE
#నిర్వచించు DWMWA_కిటికీ_మూల_PREFERENCE 33
#అయితే_ముగింపు
రకనిర్వచనం గణన {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_విడత = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_కిటికీ_మూల_PREFERENCE;

// Border Color support (Win 11+)
#నిర్వచితం_కాకపోతే DWMWA_BORDER_COLOR
#నిర్వచించు DWMWA_BORDER_COLOR 34
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DWMWA_COLOR_DEFAULT
#నిర్వచించు DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DWMWA_COLOR_NONE
#నిర్వచించు DWMWA_COLOR_NONE 0xFFFFFFFE
#అయితే_ముగింపు

// Transparent window support
#నిర్వచితం_కాకపోతే DWM_BB_ENABLE
#నిర్వచించు DWM_BB_ENABLE 0x00000001
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే DWM_BB_BLURREGION
#నిర్వచించు DWM_BB_BLURREGION 0x00000002
#అయితే_ముగింపు
రకనిర్వచనం నిర్మాణం
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

నిర్మాణం SDL_Video_దత్తాంశం
{
    పూర్ణాంకం render;

    bool coinitialized;
#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#అయితే_ముగింపు // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_లెక్క;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_బఫరు_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_మార్గం_INFO*, UINT32 *, DISPLAYCONFIG_బహుళకం_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_శీర్షిక*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_ఆదానం_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_ఆదానం_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, పూర్ణాంకం );
    BOOL (WINAPI *రిజిస్టరు_Touch_కిటికీ)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(శూన్య);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_కిటికీ)(HWND hwnd, స్థిరరాశి DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_సమితి_కిటికీ_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_సూచిక_Type)(UINT32 సూచిక_Id, సూచిక_ఆదానం_TYPE *సూచిక_Type);
    BOOL (WINAPI *Get_సూచిక_Pen_Info)(UINT32 సూచిక_Id, సూచిక_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_సూచిక_Device_Rects)(HANDLE device, RECT *సూచిక_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *సమితి_Process_DPIAware)( శూన్య );
    BOOL (WINAPI *సమితి_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *సమితి_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( శూన్య );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_కిటికీ_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_కిటికీ)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *సమితి_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#అయితే_ముగింపు                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#నిర్వచితమైతే HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#అయితే_ముగింపు

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_స్థానభ్రంశం;
    UINT rawinput_కొలత;
    UINT rawinput_లెక్క;
    Uint64 చివరి_rawinput_poll;
    SDL_బిందువు చివరి_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_కీలకం_sequence;
    SDL_PenID raw_ఆదానం_fake_pen_id;

    WIN_Game_ఆదానం_దత్తాంశం *gameinput_context;

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_అందుబాటు;
    bool ime_అంతర్గత_composition;
    bool ime_అంతర్గత_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    పూర్ణాంకం ime_composition_నిడివి;
    WCHAR ime_readingstring[16];
    పూర్ణాంకం ime_cursor;
    పూర్ణాంకం ime_selected_ప్రారంభం;
    పూర్ణాంకం ime_selected_నిడివి;

    bool ime_candidates_open;
    bool ime_update_candidates;
    అక్షరం *ime_candidates[MAX_CANDLIST];
    పూర్ణాంకం ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    పూర్ణాంకం ime_candlistindexbase;
    bool ime_horizontal_candidates;
#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#నిర్వచితం_కాకపోతే SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_సూచీ, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_కిటికీ)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_తాళం_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_తాళం_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#అయితే_ముగింపు // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_కీలకం_state[256];
    UINT _SDL_WAKEUP;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#అయితే_ముగింపు
};

బాహ్య bool g_Windows_Enable_సందేశం_Loop;
బాహ్య bool g_WindowsEnableMenuMnemonics;
బాహ్య bool g_కిటికీ_చట్రం_Usable_While_Cursor_Hidden;

రకనిర్వచనం నిర్మాణం IDirect3D9 IDirect3D9;
బాహ్య bool D3_D_ఎక్కించు_DLL(శూన్య **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

బాహ్య SDL_SystemTheme WIN_GetSystemTheme(శూన్య);
బాహ్య bool WIN_Is_చొప్పున_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_windowsvideo_h_
