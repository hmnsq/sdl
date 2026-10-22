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

#यदि_अपरिभाषितम् SDL_windowsvideo_h_
#परिभाषय SDL_windowsvideo_h_

#अन्तर्भाव "../../core/windows/SDL_windows.h"

#अन्तर्भाव "../SDL_sysvideo.h"

#यदि_परिभाषितम् HAVE_DXGI_H
#यदि_अपरिभाषितम् __cplusplus
#परिभाषय CINTERFACE
#परिभाषय COBJMACROS
#यदि_अन्तः
#अन्तर्भाव <dxgi.h>
#यदि_अन्तः

#यदि defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#अन्तर्भाव <msctf.h>
#अन्यथा
#अन्तर्भाव "SDL_msctf.h"
#यदि_अन्तः

#अन्तर्भाव <imm.h>

#परिभाषय MAX_CANDLIST   10
#परिभाषय MAX_CANDLENGTH 256
#परिभाषय MAX_CANDSIZE   (परिमाण(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#अन्तर्भाव "SDL_windowsclipboard.h"
#अन्तर्भाव "SDL_windowsevents.h"
#अन्तर्भाव "SDL_windowsgameinput.h"
#अन्तर्भाव "SDL_windowsopengl.h"

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#अन्तर्भाव "SDL_windowsshape.h"
#अन्तर्भाव "SDL_windowskeyboard.h"
#अन्तर्भाव "SDL_windowsmodes.h"
#अन्तर्भाव "SDL_windowsmouse.h"
#अन्तर्भाव "SDL_windowsopengles.h"
#यदि_अन्तः

#अन्तर्भाव "SDL_windowswindow.h"

#यदि_अपरिभाषितम् USER_DEFAULT_SCREEN_DPI
#परिभाषय USER_DEFAULT_SCREEN_DPI 96
#यदि_अन्तः

#यदि WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#परिभाषय TWF_FINETOUCH 1
#परिभाषय TWF_WANTPALM  2

#परिभाषय TOUCHEVENTF_MOVE 0x0001
#परिभाषय TOUCHEVENTF_अधस्तात् 0x0002
#परिभाषय TOUCHEVENTF_ऊर्ध्वम्   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

प्रकारनिर्देश संरचना _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE hSource;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_आवरणम्;
    DWORD dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
प्रकारनिर्देश संरचना DISPLAYCONFIG_मार्गः_SOURCE_INFO
{
    LUID adapterId;
    UINT32 id;
    सङ्घ
    {
        UINT32 बहुलकम्_Info_Idx;
        संरचना
        {
            UINT32 clone_गणः_Id : 16;
            UINT32 source_बहुलकम्_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 स्थितिः_Flags;
} DISPLAYCONFIG_मार्गः_SOURCE_INFO;

प्रकारनिर्देश संरचना DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

प्रकारनिर्देश संरचना DISPLAYCONFIG_मार्गः_TARGET_INFO
{
    LUID adapterId;
    UINT32 id;
    सङ्घ
    {
        UINT32 बहुलकम्_Info_Idx;
        संरचना
        {
            UINT32 desktop_बहुलकम्_Info_Idx : 16;
            UINT32 target_बहुलकम्_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_दरः_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ अवलोकनम्_पङ्क्तिः_Ordering;
    BOOL target_उपलब्धम्;
    UINT32 स्थितिः_Flags;
} DISPLAYCONFIG_मार्गः_TARGET_INFO;

प्रकारनिर्देश संरचना DISPLAYCONFIG_मार्गः_INFO
{
    DISPLAYCONFIG_मार्गः_SOURCE_INFO sourceInfo;
    DISPLAYCONFIG_मार्गः_TARGET_INFO targetInfo;
    UINT32 flags;
} DISPLAYCONFIG_मार्गः_INFO;

प्रकारनिर्देश गणना
{
    DISPLAYCONFIG_बहुलकम्_INFO_TYPE_SOURCE = 1,
    DISPLAYCONFIG_बहुलकम्_INFO_TYPE_TARGET = 2,
    DISPLAYCONFIG_बहुलकम्_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_बहुलकम्_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_बहुलकम्_INFO_TYPE;

प्रकारनिर्देश संरचना DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

प्रकारनिर्देश संरचना DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_दरः;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION सक्रिय_आकार;
    DISPLAYCONFIG_2DREGION योग_आकार;

    सङ्घ
    {
        संरचना
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ अवलोकनम्_पङ्क्तिः_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

प्रकारनिर्देश संरचना DISPLAYCONFIG_SOURCE_बहुलकम्
{
    UINT32 विस्तारः;
    UINT32 height;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_SOURCE_बहुलकम्;

प्रकारनिर्देश संरचना DISPLAYCONFIG_TARGET_बहुलकम्
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO targetVideoSignalInfo;
} DISPLAYCONFIG_TARGET_बहुलकम्;

प्रकारनिर्देश संरचना DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL मार्गः_Source_आकार;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

प्रकारनिर्देश संरचना DISPLAYCONFIG_बहुलकम्_INFO
{
    DISPLAYCONFIG_बहुलकम्_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    सङ्घ
    {
        DISPLAYCONFIG_TARGET_बहुलकम् target_बहुलकम्;
        DISPLAYCONFIG_SOURCE_बहुलकम् source_बहुलकम्;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_बहुलकम्_INFO;

प्रकारनिर्देश गणना DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_आन्तरिकम् = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

प्रकारनिर्देश गणना
{
    DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_PREFERRED_बहुलकम् = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_समुच्चयः_TARGET_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_आधारः_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_समुच्चयः_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_समुच्चयः_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

प्रकारनिर्देश संरचना DISPLAYCONFIG_DEVICE_INFO_शीर्षकम्
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 आकार;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_शीर्षकम्;

प्रकारनिर्देश संरचना DISPLAYCONFIG_SOURCE_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_शीर्षकम् शीर्षकम्;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_SOURCE_DEVICE_NAME;

प्रकारनिर्देश संरचना DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS
{
    सङ्घ
    {
        संरचना
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 मानम्;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS;

प्रकारनिर्देश संरचना DISPLAYCONFIG_TARGET_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_शीर्षकम् शीर्षकम्;
    DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_गुणनफलम्_संहिता_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_मार्गः[128];
} DISPLAYCONFIG_TARGET_DEVICE_NAME;

#परिभाषय QDC_ONLY_सक्रिय_PATHS 0x00000002

#यदि_अन्तः // WINVER < _WIN32_WINNT_WIN7

#यदि WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#परिभाषय POINTER_सन्देशः_FLAG_NEW 0x00000001
#परिभाषय POINTER_सन्देशः_FLAG_INRANGE 0x00000002
#परिभाषय POINTER_सन्देशः_FLAG_INCONTACT 0x00000004
#परिभाषय POINTER_सन्देशः_FLAG_FIRSTBUTTON 0x00000010
#परिभाषय POINTER_सन्देशः_FLAG_SECONDBUTTON 0x00000020
#परिभाषय POINTER_सन्देशः_FLAG_THIRDBUTTON 0x00000040
#परिभाषय POINTER_सन्देशः_FLAG_FOURTHBUTTON 0x00000080
#परिभाषय POINTER_सन्देशः_FLAG_FIFTHBUTTON 0x00000100
#परिभाषय POINTER_सन्देशः_FLAG_PRIMARY 0x00002000
#परिभाषय POINTER_सन्देशः_FLAG_CONFIDENCE 0x00004000
#परिभाषय POINTER_सन्देशः_FLAG_CANCELED 0x00008000

#परिभाषय GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#परिभाषय IS_POINTER_FLAG_समुच्चयः_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#परिभाषय IS_POINTER_INCONTACT_WPARAM(wParam) IS_POINTER_FLAG_समुच्चयः_WPARAM(wParam, POINTER_सन्देशः_FLAG_INCONTACT)
#परिभाषय IS_POINTER_FIRSTBUTTON_WPARAM(wParam) IS_POINTER_FLAG_समुच्चयः_WPARAM(wParam, POINTER_सन्देशः_FLAG_FIRSTBUTTON)

प्रकारनिर्देश DWORD POINTER_निवेशः_TYPE;

गणना चिह्नकम्_POINTER_निवेशः_TYPE
{
    PT_POINTER = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

प्रकारनिर्देश UINT32 POINTER_FLAGS;

प्रकारनिर्देश UINT32 PEN_FLAGS;
#परिभाषय PEN_FLAG_NONE 0x00000000
#परिभाषय PEN_FLAG_BARREL 0x00000001
#परिभाषय PEN_FLAG_INVERTED 0x00000002
#परिभाषय PEN_FLAG_ERASER 0x00000004

प्रकारनिर्देश UINT32 PEN_आवरणम्;
#परिभाषय PEN_आवरणम्_NONE 0x00000000
#परिभाषय PEN_आवरणम्_PRESSURE 0x00000001
#परिभाषय PEN_आवरणम्_ROTATION 0x00000002
#परिभाषय PEN_आवरणम्_TILT_X 0x00000004
#परिभाषय PEN_आवरणम्_TILT_Y 0x00000008

प्रकारनिर्देश गणना चिह्नकम्_POINTER_BUTTON_CHANGE_TYPE
{
    POINTER_CHANGE_NONE,
    POINTER_CHANGE_FIRSTBUTTON_अधस्तात्,
    POINTER_CHANGE_FIRSTBUTTON_ऊर्ध्वम्,
    POINTER_CHANGE_SECONDBUTTON_अधस्तात्,
    POINTER_CHANGE_SECONDBUTTON_ऊर्ध्वम्,
    POINTER_CHANGE_THIRDBUTTON_अधस्तात्,
    POINTER_CHANGE_THIRDBUTTON_ऊर्ध्वम्,
    POINTER_CHANGE_FOURTHBUTTON_अधस्तात्,
    POINTER_CHANGE_FOURTHBUTTON_ऊर्ध्वम्,
    POINTER_CHANGE_FIFTHBUTTON_अधस्तात्,
    POINTER_CHANGE_FIFTHBUTTON_ऊर्ध्वम्
} POINTER_BUTTON_CHANGE_TYPE;

प्रकारनिर्देश संरचना चिह्नकम्_POINTER_INFO
{
    POINTER_निवेशः_TYPE pointerType;
    UINT32 pointerId;
    UINT32 frameId;
    POINTER_FLAGS pointerFlags;
    HANDLE sourceDevice;
    HWND hwndTarget;
    POINT ptPixelLocation;
    POINT ptHimetricLocation;
    POINT ptPixelLocationRaw;
    POINT ptHimetricLocationRaw;
    DWORD dwTime;
    UINT32 history_गणनम्;
    INT32 निवेशः_दत्त;
    DWORD dw_कुञ्चिका_अवस्थाः;
    UINT64 Performance_गणनम्;
    POINTER_BUTTON_CHANGE_TYPE ButtonChangeType;
} POINTER_INFO;

प्रकारनिर्देश संरचना चिह्नकम्_POINTER_PEN_INFO
{
    POINTER_INFO pointerInfo;
    PEN_FLAGS penFlags;
    PEN_आवरणम् pen_आवरणम्;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} POINTER_PEN_INFO;

#यदि_अन्तः // WINVER < _WIN32_WINNT_WIN8

#यदि_अपरिभाषितम् HAVE_SHELLSCALINGAPI_H

प्रकारनिर्देश गणना MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

प्रकारनिर्देश गणना PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_प्रत्येकम्_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#अन्यथा
#अन्तर्भाव <shellscalingapi.h>
#यदि_अन्तः

प्रकारनिर्देश संरचना ITaskbarList3 ITaskbarList3;

#यदि_अपरिभाषितम् _DPI_AWARENESS_CONTEXTS_

प्रकारनिर्देश गणना DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_प्रत्येकम्_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#परिभाषय DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#परिभाषय DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#परिभाषय DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#यदि_अन्तः // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#यदि NTDDI_संस्करणम् < 0x0A000003
#परिभाषय DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#यदि_अन्तः // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#यदि NTDDI_संस्करणम् < 0x0A000006
#परिभाषय DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#यदि_अन्तः // NTDDI_VERSION < 0x0A000006

प्रकारनिर्देश BOOL (*PFNSHFullScreen)(HWND, DWORD);
प्रकारनिर्देश शून्य (*PFCoordTransform)(SDL_गवाक्षः *, POINT *);

प्रकारनिर्देश संरचना
{
    शून्य **lpVtbl;
    पूर्णाङ्क refcount;
    शून्य *दत्त;
} TSFSink;

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
प्रकारनिर्देश संरचना चिह्नकम्_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    POINT pt_स्थितिः_Wnd_Pos;
    POINT ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    सङ्घ
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_पङ्क्तिः;
    HIMCC h_वैयक्तिकम्;
    DWORD dw_अङ्कः_सन्देशः_Buf;
    HIMCC h_सन्देशः_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#यदि_अन्तः

// Corner rounding support  (Win 11+)
#यदि_अपरिभाषितम् DWMWA_गवाक्षः_CORNER_PREFERENCE
#परिभाषय DWMWA_गवाक्षः_CORNER_PREFERENCE 33
#यदि_अन्तः
प्रकारनिर्देश गणना {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_आवर्तनम् = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_गवाक्षः_CORNER_PREFERENCE;

// Border Color support (Win 11+)
#यदि_अपरिभाषितम् DWMWA_BORDER_COLOR
#परिभाषय DWMWA_BORDER_COLOR 34
#यदि_अन्तः

#यदि_अपरिभाषितम् DWMWA_COLOR_DEFAULT
#परिभाषय DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#यदि_अन्तः

#यदि_अपरिभाषितम् DWMWA_COLOR_NONE
#परिभाषय DWMWA_COLOR_NONE 0xFFFFFFFE
#यदि_अन्तः

// Transparent window support
#यदि_अपरिभाषितम् DWM_BB_ENABLE
#परिभाषय DWM_BB_ENABLE 0x00000001
#यदि_अन्तः
#यदि_अपरिभाषितम् DWM_BB_BLURREGION
#परिभाषय DWM_BB_BLURREGION 0x00000002
#यदि_अन्तः
प्रकारनिर्देश संरचना
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

संरचना SDL_Video_दत्त
{
    पूर्णाङ्क render;

    bool coinitialized;
#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#यदि_अन्तः // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_गणनम्;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_बफर_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_मार्गः_INFO*, UINT32 *, DISPLAYCONFIG_बहुलकम्_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_शीर्षकम्*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_निवेशः_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_निवेशः_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, पूर्णाङ्क );
    BOOL (WINAPI *पञ्जिकाकोशः_Touch_गवाक्षः)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(शून्य);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_गवाक्षः)(HWND hwnd, ध्रुव DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_समुच्चयः_गवाक्षः_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *GetPointerType)(UINT32 pointerId, POINTER_निवेशः_TYPE *pointerType);
    BOOL (WINAPI *GetPointerPenInfo)(UINT32 pointerId, POINTER_PEN_INFO *penInfo);
    BOOL (WINAPI *GetPointerDeviceRects)(HANDLE device, RECT *pointerDeviceRect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *समुच्चयः_Process_DPIAware)( शून्य );
    BOOL (WINAPI *समुच्चयः_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *समुच्चयः_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( शून्य );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_गवाक्षः_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_गवाक्षः)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *समुच्चयः_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#यदि_अन्तः                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#यदि_परिभाषितम् HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#यदि_अन्तः

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_विस्थापनम्;
    UINT rawinput_आकार;
    UINT rawinput_गणनम्;
    Uint64 चरमः_rawinput_poll;
    SDL_Point चरमः_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_कुञ्चिका_sequence;
    SDL_PenID raw_निवेशः_fake_pen_id;

    WIN_Game_निवेशः_दत्त *gameinput_context;

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_उपलब्धम्;
    bool ime_आन्तरिकम्_composition;
    bool ime_आन्तरिकम्_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    पूर्णाङ्क ime_composition_दीर्घता;
    WCHAR ime_readingstring[16];
    पूर्णाङ्क ime_cursor;
    पूर्णाङ्क ime_selected_start;
    पूर्णाङ्क ime_selected_दीर्घता;

    bool ime_candidates_open;
    bool ime_update_candidates;
    वर्ण *ime_candidates[MAX_CANDLIST];
    पूर्णाङ्क ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    पूर्णाङ्क ime_candlistindexbase;
    bool ime_horizontal_candidates;
#यदि_अन्तः

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#यदि_अपरिभाषितम् SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_सूचकांक, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_गवाक्षः)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_तालकम्_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_तालकम्_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#यदि_अन्तः // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_कुञ्चिका_state[256];
    UINT _SDL_WAKEUP;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#यदि_अन्तः
};

बाह्य bool g_Windows_Enable_सन्देशः_Loop;
बाह्य bool g_WindowsEnableMenuMnemonics;
बाह्य bool g_गवाक्षः_Frame_Usable_While_Cursor_Hidden;

प्रकारनिर्देश संरचना IDirect3D9 IDirect3D9;
बाह्य bool D3_D_आरोपय_DLL(शून्य **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

बाह्य SDL_SystemTheme WIN_GetSystemTheme(शून्य);
बाह्य bool WIN_Is_प्रत्येकम्_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_windowsvideo_h_
