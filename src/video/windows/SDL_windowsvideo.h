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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_windowsvideo_h_
#घोषणा SDL_windowsvideo_h_

#समावेश "../../core/windows/SDL_windows.h"

#समावेश "../SDL_sysvideo.h"

#अगर_घोषित HAVE_DXGI_H
#अगर_अघोषित __cplusplus
#घोषणा CINTERFACE
#घोषणा COBJMACROS
#पूर्ण_अगर
#समावेश <dxgi.h>
#पूर्ण_अगर

#अगर defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#समावेश <msctf.h>
#अन्यथा
#समावेश "SDL_msctf.h"
#पूर्ण_अगर

#समावेश <imm.h>

#घोषणा MAX_CANDLIST   10
#घोषणा MAX_CANDLENGTH 256
#घोषणा MAX_CANDSIZE   (माप(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#समावेश "SDL_windowsclipboard.h"
#समावेश "SDL_windowsevents.h"
#समावेश "SDL_windowsgameinput.h"
#समावेश "SDL_windowsopengl.h"

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#समावेश "SDL_windowsshape.h"
#समावेश "SDL_windowskeyboard.h"
#समावेश "SDL_windowsmodes.h"
#समावेश "SDL_windowsmouse.h"
#समावेश "SDL_windowsopengles.h"
#पूर्ण_अगर

#समावेश "SDL_windowswindow.h"

#अगर_अघोषित USER_DEFAULT_SCREEN_DPI
#घोषणा USER_DEFAULT_SCREEN_DPI 96
#पूर्ण_अगर

#अगर WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#घोषणा TWF_FINETOUCH 1
#घोषणा TWF_WANTPALM  2

#घोषणा TOUCHEVENTF_MOVE 0x0001
#घोषणा TOUCHEVENTF_DOWN 0x0002
#घोषणा TOUCHEVENTF_UP   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

प्रकार काष्ठा _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE hSource;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dwMask;
    DWORD dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
प्रकार काष्ठा DISPLAYCONFIG_PATH_SOURCE_INFO
{
    LUID adapterId;
    UINT32 id;
    जोड़
    {
        UINT32 modeInfoIdx;
        काष्ठा
        {
            UINT32 cloneGroupId : 16;
            UINT32 sourceModeInfoIdx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 statusFlags;
} DISPLAYCONFIG_PATH_SOURCE_INFO;

प्रकार काष्ठा DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

प्रकार काष्ठा DISPLAYCONFIG_PATH_TARGET_INFO
{
    LUID adapterId;
    UINT32 id;
    जोड़
    {
        UINT32 modeInfoIdx;
        काष्ठा
        {
            UINT32 desktopModeInfoIdx : 16;
            UINT32 targetModeInfoIdx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refreshRate;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ scan_पंक्ति_Ordering;
    BOOL targetAvailable;
    UINT32 statusFlags;
} DISPLAYCONFIG_PATH_TARGET_INFO;

प्रकार काष्ठा DISPLAYCONFIG_PATH_INFO
{
    DISPLAYCONFIG_PATH_SOURCE_INFO sourceInfo;
    DISPLAYCONFIG_PATH_TARGET_INFO targetInfo;
    UINT32 flags;
} DISPLAYCONFIG_PATH_INFO;

प्रकार क्रमागत
{
    DISPLAYCONFIG_MODE_INFO_TYPE_SOURCE = 1,
    DISPLAYCONFIG_MODE_INFO_TYPE_TARGET = 2,
    DISPLAYCONFIG_MODE_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_MODE_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_MODE_INFO_TYPE;

प्रकार काष्ठा DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

प्रकार काष्ठा DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixelRate;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION active_आकार;
    DISPLAYCONFIG_2DREGION योग_आकार;

    जोड़
    {
        काष्ठा
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ scan_पंक्ति_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

प्रकार काष्ठा DISPLAYCONFIG_SOURCE_MODE
{
    UINT32 width;
    UINT32 height;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_SOURCE_MODE;

प्रकार काष्ठा DISPLAYCONFIG_TARGET_MODE
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO targetVideoSignalInfo;
} DISPLAYCONFIG_TARGET_MODE;

प्रकार काष्ठा DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL Path_Source_आकार;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

प्रकार काष्ठा DISPLAYCONFIG_MODE_INFO
{
    DISPLAYCONFIG_MODE_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    जोड़
    {
        DISPLAYCONFIG_TARGET_MODE targetMode;
        DISPLAYCONFIG_SOURCE_MODE sourceMode;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_MODE_INFO;

प्रकार क्रमागत DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_INTERNAL = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

प्रकार क्रमागत
{
    DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_PREFERRED_MODE = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_SET_TARGET_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_BASE_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_SET_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_SET_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

प्रकार काष्ठा DISPLAYCONFIG_DEVICE_INFO_HEADER
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 आकार;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_HEADER;

प्रकार काष्ठा DISPLAYCONFIG_SOURCE_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_HEADER header;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_SOURCE_DEVICE_NAME;

प्रकार काष्ठा DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS
{
    जोड़
    {
        काष्ठा
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 मूल्य;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS;

प्रकार काष्ठा DISPLAYCONFIG_TARGET_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_HEADER header;
    DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edidProductCodeId;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitorDevicePath[128];
} DISPLAYCONFIG_TARGET_DEVICE_NAME;

#घोषणा QDC_ONLY_ACTIVE_PATHS 0x00000002

#पूर्ण_अगर // WINVER < _WIN32_WINNT_WIN7

#अगर WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#घोषणा POINTER_MESSAGE_FLAG_NEW 0x00000001
#घोषणा POINTER_MESSAGE_FLAG_INRANGE 0x00000002
#घोषणा POINTER_MESSAGE_FLAG_INCONTACT 0x00000004
#घोषणा POINTER_MESSAGE_FLAG_FIRSTBUTTON 0x00000010
#घोषणा POINTER_MESSAGE_FLAG_SECONDBUTTON 0x00000020
#घोषणा POINTER_MESSAGE_FLAG_THIRDBUTTON 0x00000040
#घोषणा POINTER_MESSAGE_FLAG_FOURTHBUTTON 0x00000080
#घोषणा POINTER_MESSAGE_FLAG_FIFTHBUTTON 0x00000100
#घोषणा POINTER_MESSAGE_FLAG_PRIMARY 0x00002000
#घोषणा POINTER_MESSAGE_FLAG_CONFIDENCE 0x00004000
#घोषणा POINTER_MESSAGE_FLAG_CANCELED 0x00008000

#घोषणा GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#घोषणा IS_POINTER_FLAG_SET_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#घोषणा IS_POINTER_INCONTACT_WPARAM(wParam) IS_POINTER_FLAG_SET_WPARAM(wParam, POINTER_MESSAGE_FLAG_INCONTACT)
#घोषणा IS_POINTER_FIRSTBUTTON_WPARAM(wParam) IS_POINTER_FLAG_SET_WPARAM(wParam, POINTER_MESSAGE_FLAG_FIRSTBUTTON)

प्रकार DWORD POINTER_निवेश_TYPE;

क्रमागत tag_POINTER_निवेश_TYPE
{
    PT_POINTER = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

प्रकार UINT32 POINTER_FLAGS;

प्रकार UINT32 PEN_FLAGS;
#घोषणा PEN_FLAG_NONE 0x00000000
#घोषणा PEN_FLAG_BARREL 0x00000001
#घोषणा PEN_FLAG_INVERTED 0x00000002
#घोषणा PEN_FLAG_ERASER 0x00000004

प्रकार UINT32 PEN_MASK;
#घोषणा PEN_MASK_NONE 0x00000000
#घोषणा PEN_MASK_PRESSURE 0x00000001
#घोषणा PEN_MASK_ROTATION 0x00000002
#घोषणा PEN_MASK_TILT_X 0x00000004
#घोषणा PEN_MASK_TILT_Y 0x00000008

प्रकार क्रमागत tagPOINTER_BUTTON_CHANGE_TYPE
{
    POINTER_CHANGE_NONE,
    POINTER_CHANGE_FIRSTBUTTON_DOWN,
    POINTER_CHANGE_FIRSTBUTTON_UP,
    POINTER_CHANGE_SECONDBUTTON_DOWN,
    POINTER_CHANGE_SECONDBUTTON_UP,
    POINTER_CHANGE_THIRDBUTTON_DOWN,
    POINTER_CHANGE_THIRDBUTTON_UP,
    POINTER_CHANGE_FOURTHBUTTON_DOWN,
    POINTER_CHANGE_FOURTHBUTTON_UP,
    POINTER_CHANGE_FIFTHBUTTON_DOWN,
    POINTER_CHANGE_FIFTHBUTTON_UP
} POINTER_BUTTON_CHANGE_TYPE;

प्रकार काष्ठा tagPOINTER_INFO
{
    POINTER_निवेश_TYPE pointerType;
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
    UINT32 history_गिनती;
    INT32 निवेश_तथ्य;
    DWORD dw_कुंजी_States;
    UINT64 Performance_गिनती;
    POINTER_BUTTON_CHANGE_TYPE ButtonChangeType;
} POINTER_INFO;

प्रकार काष्ठा tagPOINTER_PEN_INFO
{
    POINTER_INFO pointerInfo;
    PEN_FLAGS penFlags;
    PEN_MASK penMask;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} POINTER_PEN_INFO;

#पूर्ण_अगर // WINVER < _WIN32_WINNT_WIN8

#अगर_अघोषित HAVE_SHELLSCALINGAPI_H

प्रकार क्रमागत MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

प्रकार क्रमागत PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#अन्यथा
#समावेश <shellscalingapi.h>
#पूर्ण_अगर

प्रकार काष्ठा ITaskbarList3 ITaskbarList3;

#अगर_अघोषित _DPI_AWARENESS_CONTEXTS_

प्रकार क्रमागत DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_PER_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#घोषणा DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#घोषणा DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#घोषणा DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#पूर्ण_अगर // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#अगर NTDDI_VERSION < 0x0A000003
#घोषणा DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#पूर्ण_अगर // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#अगर NTDDI_VERSION < 0x0A000006
#घोषणा DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#पूर्ण_अगर // NTDDI_VERSION < 0x0A000006

प्रकार BOOL (*PFNSHFullScreen)(HWND, DWORD);
प्रकार व्योम (*PFCoordTransform)(SDL_Window *, POINT *);

प्रकार काष्ठा
{
    व्योम **lpVtbl;
    पूर्णांक refcount;
    व्योम *तथ्य;
} TSFSink;

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
प्रकार काष्ठा tagINPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    POINT ptStatusWndPos;
    POINT ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    जोड़
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_पंक्ति;
    HIMCC hPrivate;
    DWORD dw_अंक_संदेश_Buf;
    HIMCC h_संदेश_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#पूर्ण_अगर

// Corner rounding support  (Win 11+)
#अगर_अघोषित DWMWA_WINDOW_CORNER_PREFERENCE
#घोषणा DWMWA_WINDOW_CORNER_PREFERENCE 33
#पूर्ण_अगर
प्रकार क्रमागत {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_ROUND = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_WINDOW_CORNER_PREFERENCE;

// Border Color support (Win 11+)
#अगर_अघोषित DWMWA_BORDER_COLOR
#घोषणा DWMWA_BORDER_COLOR 34
#पूर्ण_अगर

#अगर_अघोषित DWMWA_COLOR_DEFAULT
#घोषणा DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#पूर्ण_अगर

#अगर_अघोषित DWMWA_COLOR_NONE
#घोषणा DWMWA_COLOR_NONE 0xFFFFFFFE
#पूर्ण_अगर

// Transparent window support
#अगर_अघोषित DWM_BB_ENABLE
#घोषणा DWM_BB_ENABLE 0x00000001
#पूर्ण_अगर
#अगर_अघोषित DWM_BB_BLURREGION
#घोषणा DWM_BB_BLURREGION 0x00000002
#पूर्ण_अगर
प्रकार काष्ठा
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

काष्ठा SDL_Video_तथ्य
{
    पूर्णांक render;

    bool coinitialized;
#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#पूर्ण_अगर // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_गिनती;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_बफर_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_PATH_INFO*, UINT32 *, DISPLAYCONFIG_MODE_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_HEADER*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_निवेश_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_निवेश_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, पूर्णांक );
    BOOL (WINAPI *RegisterTouchWindow)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(व्योम);
    HRESULT (WINAPI *DwmEnableBlurBehindWindow)(HWND hwnd, स्थिर DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *DwmSetWindowAttribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *GetPointerType)(UINT32 pointerId, POINTER_निवेश_TYPE *pointerType);
    BOOL (WINAPI *GetPointerPenInfo)(UINT32 pointerId, POINTER_PEN_INFO *penInfo);
    BOOL (WINAPI *GetPointerDeviceRects)(HANDLE device, RECT *pointerDeviceRect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *SetProcessDPIAware)( व्योम );
    BOOL (WINAPI *SetProcessDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *SetThreadDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( व्योम );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *AdjustWindowRectExForDpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *GetDpiForWindow)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#पूर्ण_अगर                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अगर_घोषित HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#पूर्ण_अगर

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_offset;
    UINT rawinput_आकार;
    UINT rawinput_गिनती;
    Uint64 last_rawinput_poll;
    SDL_Point last_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_कुंजी_sequence;
    SDL_PenID raw_निवेश_fake_pen_id;

    WIN_Game_निवेश_तथ्य *gameinput_context;

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_available;
    bool ime_internal_composition;
    bool ime_internal_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    पूर्णांक ime_composition_लंबाई;
    WCHAR ime_readingstring[16];
    पूर्णांक ime_cursor;
    पूर्णांक ime_selected_start;
    पूर्णांक ime_selected_लंबाई;

    bool ime_candidates_open;
    bool ime_update_candidates;
    अक्षर *ime_candidates[MAX_CANDLIST];
    पूर्णांक ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    पूर्णांक ime_candlistindexbase;
    bool ime_horizontal_candidates;
#पूर्ण_अगर

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अगर_अघोषित SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_सूचकांक, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *ShowReadingWindow)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *ImmLockIMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *ImmLockIMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#पूर्ण_अगर // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_कुंजी_state[256];
    UINT _SDL_WAKEUP;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#पूर्ण_अगर
};

बाह्य bool g_WindowsEnableMessageLoop;
बाह्य bool g_WindowsEnableMenuMnemonics;
बाह्य bool g_WindowFrameUsableWhileCursorHidden;

प्रकार काष्ठा IDirect3D9 IDirect3D9;
बाह्य bool D3D_LoadDLL(व्योम **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

बाह्य SDL_SystemTheme WIN_GetSystemTheme(व्योम);
बाह्य bool WIN_IsPerMonitorV2DPIAware(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_windowsvideo_h_
