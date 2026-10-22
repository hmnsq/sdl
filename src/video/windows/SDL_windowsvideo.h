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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_windowsvideo_h_
#define SDL_windowsvideo_h_

#അന്തര്ഭാവ "../../core/windows/SDL_windows.h"

#അന്തര്ഭാവ "../SDL_sysvideo.h"

#ifdef HAVE_DXGI_H
#ifndef __cplusplus
#define CINTERFACE
#define COBJMACROS
#endif
#അന്തര്ഭാവ <dxgi.h>
#endif

#എങ്കിൽ defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#അന്തര്ഭാവ <msctf.h>
#അല്ലെങ്കിൽ
#അന്തര്ഭാവ "SDL_msctf.h"
#endif

#അന്തര്ഭാവ <imm.h>

#define MAX_CANDLIST   10
#define MAX_CANDLENGTH 256
#define MAX_CANDSIZE   (വലുപ്പം(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#അന്തര്ഭാവ "SDL_windowsclipboard.h"
#അന്തര്ഭാവ "SDL_windowsevents.h"
#അന്തര്ഭാവ "SDL_windowsgameinput.h"
#അന്തര്ഭാവ "SDL_windowsopengl.h"

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#അന്തര്ഭാവ "SDL_windowsshape.h"
#അന്തര്ഭാവ "SDL_windowskeyboard.h"
#അന്തര്ഭാവ "SDL_windowsmodes.h"
#അന്തര്ഭാവ "SDL_windowsmouse.h"
#അന്തര്ഭാവ "SDL_windowsopengles.h"
#endif

#അന്തര്ഭാവ "SDL_windowswindow.h"

#ifndef USER_DEFAULT_SCREEN_DPI
#define USER_DEFAULT_SCREEN_DPI 96
#endif

#എങ്കിൽ WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#define TWF_FINETOUCH 1
#define TWF_WANTPALM  2

#define TOUCHEVENTF_MOVE 0x0001
#define TOUCHEVENTF_DOWN 0x0002
#define TOUCHEVENTF_UP   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

തരനിർവചനം ഘടന _TOUCHINPUT
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
തരനിർവചനം ഘടന DISPLAYCONFIG_PATH_SOURCE_INFO
{
    LUID adapterId;
    UINT32 id;
    സംഘം
    {
        UINT32 modeInfoIdx;
        ഘടന
        {
            UINT32 cloneGroupId : 16;
            UINT32 sourceModeInfoIdx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 statusFlags;
} DISPLAYCONFIG_PATH_SOURCE_INFO;

തരനിർവചനം ഘടന DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

തരനിർവചനം ഘടന DISPLAYCONFIG_PATH_TARGET_INFO
{
    LUID adapterId;
    UINT32 id;
    സംഘം
    {
        UINT32 modeInfoIdx;
        ഘടന
        {
            UINT32 desktopModeInfoIdx : 16;
            UINT32 targetModeInfoIdx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refreshRate;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ scan_വരി_Ordering;
    BOOL targetAvailable;
    UINT32 statusFlags;
} DISPLAYCONFIG_PATH_TARGET_INFO;

തരനിർവചനം ഘടന DISPLAYCONFIG_PATH_INFO
{
    DISPLAYCONFIG_PATH_SOURCE_INFO sourceInfo;
    DISPLAYCONFIG_PATH_TARGET_INFO targetInfo;
    UINT32 flags;
} DISPLAYCONFIG_PATH_INFO;

തരനിർവചനം എണ്ണൽ
{
    DISPLAYCONFIG_MODE_INFO_TYPE_SOURCE = 1,
    DISPLAYCONFIG_MODE_INFO_TYPE_TARGET = 2,
    DISPLAYCONFIG_MODE_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_MODE_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_MODE_INFO_TYPE;

തരനിർവചനം ഘടന DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

തരനിർവചനം ഘടന DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixelRate;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION activeSize;
    DISPLAYCONFIG_2DREGION totalSize;

    സംഘം
    {
        ഘടന
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ scan_വരി_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

തരനിർവചനം ഘടന DISPLAYCONFIG_SOURCE_MODE
{
    UINT32 width;
    UINT32 height;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_SOURCE_MODE;

തരനിർവചനം ഘടന DISPLAYCONFIG_TARGET_MODE
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO targetVideoSignalInfo;
} DISPLAYCONFIG_TARGET_MODE;

തരനിർവചനം ഘടന DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL PathSourceSize;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

തരനിർവചനം ഘടന DISPLAYCONFIG_MODE_INFO
{
    DISPLAYCONFIG_MODE_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    സംഘം
    {
        DISPLAYCONFIG_TARGET_MODE targetMode;
        DISPLAYCONFIG_SOURCE_MODE sourceMode;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_MODE_INFO;

തരനിർവചനം എണ്ണൽ DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_INTERNAL = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

തരനിർവചനം എണ്ണൽ
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

തരനിർവചനം ഘടന DISPLAYCONFIG_DEVICE_INFO_HEADER
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 size;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_HEADER;

തരനിർവചനം ഘടന DISPLAYCONFIG_SOURCE_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_HEADER header;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_SOURCE_DEVICE_NAME;

തരനിർവചനം ഘടന DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS
{
    സംഘം
    {
        ഘടന
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 മൂല്യം;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS;

തരനിർവചനം ഘടന DISPLAYCONFIG_TARGET_DEVICE_NAME
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

#define QDC_ONLY_ACTIVE_PATHS 0x00000002

#endif // WINVER < _WIN32_WINNT_WIN7

#എങ്കിൽ WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#define POINTER_MESSAGE_FLAG_NEW 0x00000001
#define POINTER_MESSAGE_FLAG_INRANGE 0x00000002
#define POINTER_MESSAGE_FLAG_INCONTACT 0x00000004
#define POINTER_MESSAGE_FLAG_FIRSTBUTTON 0x00000010
#define POINTER_MESSAGE_FLAG_SECONDBUTTON 0x00000020
#define POINTER_MESSAGE_FLAG_THIRDBUTTON 0x00000040
#define POINTER_MESSAGE_FLAG_FOURTHBUTTON 0x00000080
#define POINTER_MESSAGE_FLAG_FIFTHBUTTON 0x00000100
#define POINTER_MESSAGE_FLAG_PRIMARY 0x00002000
#define POINTER_MESSAGE_FLAG_CONFIDENCE 0x00004000
#define POINTER_MESSAGE_FLAG_CANCELED 0x00008000

#define GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#define IS_POINTER_FLAG_SET_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#define IS_POINTER_INCONTACT_WPARAM(wParam) IS_POINTER_FLAG_SET_WPARAM(wParam, POINTER_MESSAGE_FLAG_INCONTACT)
#define IS_POINTER_FIRSTBUTTON_WPARAM(wParam) IS_POINTER_FLAG_SET_WPARAM(wParam, POINTER_MESSAGE_FLAG_FIRSTBUTTON)

തരനിർവചനം DWORD POINTER_നിവേശം_TYPE;

എണ്ണൽ tag_POINTER_നിവേശം_TYPE
{
    PT_POINTER = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

തരനിർവചനം UINT32 POINTER_FLAGS;

തരനിർവചനം UINT32 PEN_FLAGS;
#define PEN_FLAG_NONE 0x00000000
#define PEN_FLAG_BARREL 0x00000001
#define PEN_FLAG_INVERTED 0x00000002
#define PEN_FLAG_ERASER 0x00000004

തരനിർവചനം UINT32 PEN_MASK;
#define PEN_MASK_NONE 0x00000000
#define PEN_MASK_PRESSURE 0x00000001
#define PEN_MASK_ROTATION 0x00000002
#define PEN_MASK_TILT_X 0x00000004
#define PEN_MASK_TILT_Y 0x00000008

തരനിർവചനം എണ്ണൽ tagPOINTER_BUTTON_CHANGE_TYPE
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

തരനിർവചനം ഘടന tagPOINTER_INFO
{
    POINTER_നിവേശം_TYPE pointerType;
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
    UINT32 history_എണ്ണം;
    INT32 നിവേശം_Data;
    DWORD dw_താക്കോൽ_States;
    UINT64 Performance_എണ്ണം;
    POINTER_BUTTON_CHANGE_TYPE ButtonChangeType;
} POINTER_INFO;

തരനിർവചനം ഘടന tagPOINTER_PEN_INFO
{
    POINTER_INFO pointerInfo;
    PEN_FLAGS penFlags;
    PEN_MASK penMask;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} POINTER_PEN_INFO;

#endif // WINVER < _WIN32_WINNT_WIN8

#ifndef HAVE_SHELLSCALINGAPI_H

തരനിർവചനം എണ്ണൽ MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

തരനിർവചനം എണ്ണൽ PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#അല്ലെങ്കിൽ
#അന്തര്ഭാവ <shellscalingapi.h>
#endif

തരനിർവചനം ഘടന ITaskbarList3 ITaskbarList3;

#ifndef _DPI_AWARENESS_CONTEXTS_

തരനിർവചനം എണ്ണൽ DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_PER_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#define DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#endif // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#എങ്കിൽ NTDDI_VERSION < 0x0A000003
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#endif // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#എങ്കിൽ NTDDI_VERSION < 0x0A000006
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#endif // NTDDI_VERSION < 0x0A000006

തരനിർവചനം BOOL (*PFNSHFullScreen)(HWND, DWORD);
തരനിർവചനം ശൂന്യം (*PFCoordTransform)(SDL_Window *, POINT *);

തരനിർവചനം ഘടന
{
    ശൂന്യം **lpVtbl;
    പൂർണ്ണസംഖ്യ refcount;
    ശൂന്യം *data;
} TSFSink;

#ifndef SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
തരനിർവചനം ഘടന tagINPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    POINT ptStatusWndPos;
    POINT ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    സംഘം
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_വരി;
    HIMCC hPrivate;
    DWORD dw_അക്കം_സന്ദേശം_Buf;
    HIMCC h_സന്ദേശം_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#endif

// Corner rounding support  (Win 11+)
#ifndef DWMWA_WINDOW_CORNER_PREFERENCE
#define DWMWA_WINDOW_CORNER_PREFERENCE 33
#endif
തരനിർവചനം എണ്ണൽ {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_ROUND = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_WINDOW_CORNER_PREFERENCE;

// Border Color support (Win 11+)
#ifndef DWMWA_BORDER_COLOR
#define DWMWA_BORDER_COLOR 34
#endif

#ifndef DWMWA_COLOR_DEFAULT
#define DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#endif

#ifndef DWMWA_COLOR_NONE
#define DWMWA_COLOR_NONE 0xFFFFFFFE
#endif

// Transparent window support
#ifndef DWM_BB_ENABLE
#define DWM_BB_ENABLE 0x00000001
#endif
#ifndef DWM_BB_BLURREGION
#define DWM_BB_BLURREGION 0x00000002
#endif
തരനിർവചനം ഘടന
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

ഘടന SDL_VideoData
{
    പൂർണ്ണസംഖ്യ render;

    bool coinitialized;
#എങ്കിൽ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#endif // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_എണ്ണം;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *GetDisplayConfigBufferSizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_PATH_INFO*, UINT32 *, DISPLAYCONFIG_MODE_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_HEADER*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_നിവേശം_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_നിവേശം_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, പൂർണ്ണസംഖ്യ );
    BOOL (WINAPI *RegisterTouchWindow)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(ശൂന്യം);
    HRESULT (WINAPI *DwmEnableBlurBehindWindow)(HWND hwnd, സ്ഥിരം DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *DwmSetWindowAttribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *GetPointerType)(UINT32 pointerId, POINTER_നിവേശം_TYPE *pointerType);
    BOOL (WINAPI *GetPointerPenInfo)(UINT32 pointerId, POINTER_PEN_INFO *penInfo);
    BOOL (WINAPI *GetPointerDeviceRects)(HANDLE device, RECT *pointerDeviceRect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *SetProcessDPIAware)( ശൂന്യം );
    BOOL (WINAPI *SetProcessDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *SetThreadDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( ശൂന്യം );
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
#endif                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#endif

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_offset;
    UINT rawinput_size;
    UINT rawinput_എണ്ണം;
    Uint64 last_rawinput_poll;
    SDL_Point last_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_താക്കോൽ_sequence;
    SDL_PenID raw_നിവേശം_fake_pen_id;

    WIN_Game_നിവേശം_Data *gameinput_context;

#ifndef SDL_DISABLE_WINDOWS_IME
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
    പൂർണ്ണസംഖ്യ ime_composition_length;
    WCHAR ime_readingstring[16];
    പൂർണ്ണസംഖ്യ ime_cursor;
    പൂർണ്ണസംഖ്യ ime_selected_start;
    പൂർണ്ണസംഖ്യ ime_selected_length;

    bool ime_candidates_open;
    bool ime_update_candidates;
    അക്ഷരം *ime_candidates[MAX_CANDLIST];
    പൂർണ്ണസംഖ്യ ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    പൂർണ്ണസംഖ്യ ime_candlistindexbase;
    bool ime_horizontal_candidates;
#endif

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifndef SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pnErrorIndex, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *ShowReadingWindow)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *ImmLockIMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *ImmLockIMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#endif // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_താക്കോൽ_state[256];
    UINT _SDL_WAKEUP;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#endif
};

ബാഹ്യ bool g_WindowsEnableMessageLoop;
ബാഹ്യ bool g_WindowsEnableMenuMnemonics;
ബാഹ്യ bool g_WindowFrameUsableWhileCursorHidden;

തരനിർവചനം ഘടന IDirect3D9 IDirect3D9;
ബാഹ്യ bool D3D_LoadDLL(ശൂന്യം **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

ബാഹ്യ SDL_SystemTheme WIN_GetSystemTheme(ശൂന്യം);
ബാഹ്യ bool WIN_IsPerMonitorV2DPIAware(SDL_VideoDevice *_this);

#endif // SDL_windowsvideo_h_
