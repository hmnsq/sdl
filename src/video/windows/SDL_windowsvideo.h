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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowsvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowsvideo_h_

#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h"

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __cplusplus
#ವ್ಯಾಖ್ಯಾನಿಸು CINTERFACE
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <dxgi.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ಅನ್ತರ್ಭಾವ <msctf.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ "SDL_msctf.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <imm.h>

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CANDLIST   10
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CANDLENGTH 256
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CANDSIZE   (ಗಾತ್ರ(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#ಅನ್ತರ್ಭಾವ "SDL_windowsclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsgameinput.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsopengl.h"

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ಅನ್ತರ್ಭಾವ "SDL_windowsshape.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowskeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsopengles.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USER_DEFAULT_SCREEN_DPI
#ವ್ಯಾಖ್ಯಾನಿಸು USER_DEFAULT_SCREEN_DPI 96
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#ವ್ಯಾಖ್ಯಾನಿಸು TWF_FINETOUCH 1
#ವ್ಯಾಖ್ಯಾನಿಸು TWF_WANTPALM  2

#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHEVENTF_MOVE 0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHEVENTF_ಕೆಳಕ್ಕೆ 0x0002
#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHEVENTF_ಮೇಲೆ   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_ಮೂಲ;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_ಮುಖವಾಡ;
    DWORD dw_ಸಮಯ;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಮಾರ್ಗ_ಮೂಲ_INFO
{
    LUID adapterId;
    UINT32 id;
    ಒಕ್ಕೂಟ
    {
        UINT32 ಬಹುಲಕ_Info_Idx;
        ರಚನೆ
        {
            UINT32 clone_ಗುಂಪು_Id : 16;
            UINT32 ಮೂಲ_ಬಹುಲಕ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 ಸ್ಥಿತಿ_Flags;
} DISPLAYCONFIG_ಮಾರ್ಗ_ಮೂಲ_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಮಾರ್ಗ_ಗುರಿ_INFO
{
    LUID adapterId;
    UINT32 id;
    ಒಕ್ಕೂಟ
    {
        UINT32 ಬಹುಲಕ_Info_Idx;
        ರಚನೆ
        {
            UINT32 desktop_ಬಹುಲಕ_Info_Idx : 16;
            UINT32 ಗುರಿ_ಬಹುಲಕ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_ದರ_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ ಪರಿಶೀಲನೆ_ಸಾಲು_Ordering;
    BOOL ಗುರಿ_ಲಭ್ಯ;
    UINT32 ಸ್ಥಿತಿ_Flags;
} DISPLAYCONFIG_ಮಾರ್ಗ_ಗುರಿ_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಮಾರ್ಗ_INFO
{
    DISPLAYCONFIG_ಮಾರ್ಗ_ಮೂಲ_INFO ಮೂಲ_Info;
    DISPLAYCONFIG_ಮಾರ್ಗ_ಗುರಿ_INFO ಗುರಿ_Info;
    UINT32 flags;
} DISPLAYCONFIG_ಮಾರ್ಗ_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE_ಮೂಲ = 1,
    DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE_ಗುರಿ = 2,
    DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_ದರ;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION ಸಕ್ರಿಯ_ಗಾತ್ರ;
    DISPLAYCONFIG_2DREGION ಒಟ್ಟು_ಗಾತ್ರ;

    ಒಕ್ಕೂಟ
    {
        ರಚನೆ
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ ಪರಿಶೀಲನೆ_ಸಾಲು_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಮೂಲ_ಬಹುಲಕ
{
    UINT32 ಅಗಲ;
    UINT32 ಎತ್ತರ;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_ಮೂಲ_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಗುರಿ_ಬಹುಲಕ
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO ಗುರಿ_Video_Signal_Info;
} DISPLAYCONFIG_ಗುರಿ_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL ಮಾರ್ಗ_ಮೂಲ_ಗಾತ್ರ;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಬಹುಲಕ_INFO
{
    DISPLAYCONFIG_ಬಹುಲಕ_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    ಒಕ್ಕೂಟ
    {
        DISPLAYCONFIG_ಗುರಿ_ಬಹುಲಕ ಗುರಿ_ಬಹುಲಕ;
        DISPLAYCONFIG_ಮೂಲ_ಬಹುಲಕ ಮೂಲ_ಬಹುಲಕ;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ಬಹುಲಕ_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_ಆಂತರಿಕ = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    DISPLAYCONFIG_DEVICE_INFO_GET_ಮೂಲ_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_ಗುರಿ_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_ಗುರಿ_PREFERRED_ಬಹುಲಕ = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_ಗಣ_ಗುರಿ_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_ಗುರಿ_ತಳ_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_ಗಣ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_ಗಣ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 ಗಾತ್ರ_2;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಮೂಲ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_ಮೂಲ_DEVICE_NAME;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME_FLAGS
{
    ಒಕ್ಕೂಟ
    {
        ರಚನೆ
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 ಮೌಲ್ಯ;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME_FLAGS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_ಗುಣಲಬ್ಧ_ಸಂಕೇತ_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_ಮಾರ್ಗ[128];
} DISPLAYCONFIG_ಗುರಿ_DEVICE_NAME;

#ವ್ಯಾಖ್ಯಾನಿಸು QDC_ONLY_ಸಕ್ರಿಯ_PATHS 0x00000002

#ಆದರೆ_ಅಂತ್ಯ // WINVER < _WIN32_WINNT_WIN7

#ಆದರೆ WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_NEW 0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_INRANGE 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_INCONTACT 0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_FIRSTBUTTON 0x00000010
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_SECONDBUTTON 0x00000020
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_THIRDBUTTON 0x00000040
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_FOURTHBUTTON 0x00000080
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_FIFTHBUTTON 0x00000100
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_PRIMARY 0x00002000
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_CONFIDENCE 0x00004000
#ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚಕ_ಸಂದೇಶ_FLAG_CANCELED 0x00008000

#ವ್ಯಾಖ್ಯಾನಿಸು GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#ವ್ಯಾಖ್ಯಾನಿಸು IS_ಸೂಚಕ_FLAG_ಗಣ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#ವ್ಯಾಖ್ಯಾನಿಸು IS_ಸೂಚಕ_INCONTACT_WPARAM(wParam) IS_ಸೂಚಕ_FLAG_ಗಣ_WPARAM(wParam, ಸೂಚಕ_ಸಂದೇಶ_FLAG_INCONTACT)
#ವ್ಯಾಖ್ಯಾನಿಸು IS_ಸೂಚಕ_FIRSTBUTTON_WPARAM(wParam) IS_ಸೂಚಕ_FLAG_ಗಣ_WPARAM(wParam, ಸೂಚಕ_ಸಂದೇಶ_FLAG_FIRSTBUTTON)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ DWORD ಸೂಚಕ_ಒಳಹರಿವು_TYPE;

ಎಣಿಕೆ ಟ್ಯಾಗ್_ಸೂಚಕ_ಒಳಹರಿವು_TYPE
{
    PT_ಸೂಚಕ = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ UINT32 ಸೂಚಕ_FLAGS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ UINT32 PEN_FLAGS;
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_FLAG_NONE 0x00000000
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_FLAG_BARREL 0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_FLAG_INVERTED 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_FLAG_ERASER 0x00000004

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ UINT32 PEN_ಮುಖವಾಡ;
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_ಮುಖವಾಡ_NONE 0x00000000
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_ಮುಖವಾಡ_PRESSURE 0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_ಮುಖವಾಡ_ROTATION 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_ಮುಖವಾಡ_TILT_X 0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು PEN_ಮುಖವಾಡ_TILT_Y 0x00000008

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ಟ್ಯಾಗ್_ಸೂಚಕ_BUTTON_CHANGE_TYPE
{
    ಸೂಚಕ_CHANGE_NONE,
    ಸೂಚಕ_CHANGE_FIRSTBUTTON_ಕೆಳಕ್ಕೆ,
    ಸೂಚಕ_CHANGE_FIRSTBUTTON_ಮೇಲೆ,
    ಸೂಚಕ_CHANGE_SECONDBUTTON_ಕೆಳಕ್ಕೆ,
    ಸೂಚಕ_CHANGE_SECONDBUTTON_ಮೇಲೆ,
    ಸೂಚಕ_CHANGE_THIRDBUTTON_ಕೆಳಕ್ಕೆ,
    ಸೂಚಕ_CHANGE_THIRDBUTTON_ಮೇಲೆ,
    ಸೂಚಕ_CHANGE_FOURTHBUTTON_ಕೆಳಕ್ಕೆ,
    ಸೂಚಕ_CHANGE_FOURTHBUTTON_ಮೇಲೆ,
    ಸೂಚಕ_CHANGE_FIFTHBUTTON_ಕೆಳಕ್ಕೆ,
    ಸೂಚಕ_CHANGE_FIFTHBUTTON_ಮೇಲೆ
} ಸೂಚಕ_BUTTON_CHANGE_TYPE;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಟ್ಯಾಗ್_ಸೂಚಕ_INFO
{
    ಸೂಚಕ_ಒಳಹರಿವು_TYPE ಸೂಚಕ_Type;
    UINT32 ಸೂಚಕ_Id;
    UINT32 ಚೌಕಟ್ಟು_Id;
    ಸೂಚಕ_FLAGS ಸೂಚಕ_Flags;
    HANDLE ಮೂಲ_Device;
    HWND hwnd_ಗುರಿ;
    ಬಿಂದು_2 ptPixelLocation;
    ಬಿಂದು_2 ptHimetricLocation;
    ಬಿಂದು_2 ptPixelLocationRaw;
    ಬಿಂದು_2 ptHimetricLocationRaw;
    DWORD dw_ಸಮಯ;
    UINT32 history_ಎಣಿಕೆ;
    INT32 ಒಳಹರಿವು_ದತ್ತಾಂಶ;
    DWORD dw_ಕೀಲಿ_ಸ್ಥಿತಿಗಳು;
    UINT64 Performance_ಎಣಿಕೆ;
    ಸೂಚಕ_BUTTON_CHANGE_TYPE ButtonChangeType;
} ಸೂಚಕ_INFO;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಟ್ಯಾಗ್_ಸೂಚಕ_PEN_INFO
{
    ಸೂಚಕ_INFO ಸೂಚಕ_Info;
    PEN_FLAGS penFlags;
    PEN_ಮುಖವಾಡ pen_ಮುಖವಾಡ;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} ಸೂಚಕ_PEN_INFO;

#ಆದರೆ_ಅಂತ್ಯ // WINVER < _WIN32_WINNT_WIN8

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_SHELLSCALINGAPI_H

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_ಪ್ರತಿ_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <shellscalingapi.h>
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITaskbarList3 ITaskbarList3;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _DPI_AWARENESS_CONTEXTS_

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_ಪ್ರತಿ_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#ವ್ಯಾಖ್ಯಾನಿಸು DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#ವ್ಯಾಖ್ಯಾನಿಸು DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#ವ್ಯಾಖ್ಯಾನಿಸು DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#ಆದರೆ_ಅಂತ್ಯ // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#ಆದರೆ NTDDI_ಆವೃತ್ತಿ < 0x0A000003
#ವ್ಯಾಖ್ಯಾನಿಸು DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#ಆದರೆ_ಅಂತ್ಯ // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#ಆದರೆ NTDDI_ಆವೃತ್ತಿ < 0x0A000006
#ವ್ಯಾಖ್ಯಾನಿಸು DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#ಆದರೆ_ಅಂತ್ಯ // NTDDI_VERSION < 0x0A000006

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ BOOL (*PFNSHFullScreen)(HWND, DWORD);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*PFCoordTransform)(SDL_ಕಿಟಕಿ *, ಬಿಂದು_2 *);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಶೂನ್ಯ **lpVtbl;
    ಪೂರ್ಣಾಂಕ refcount;
    ಶೂನ್ಯ *ದತ್ತಾಂಶ;
} TSFSink;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಟ್ಯಾಗ್_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    ಬಿಂದು_2 pt_ಸ್ಥಿತಿ_Wnd_Pos;
    ಬಿಂದು_2 ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    ಒಕ್ಕೂಟ
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_ಸಾಲು;
    HIMCC h_ಖಾಸಗಿ;
    DWORD dw_ಅಂಕೆ_ಸಂದೇಶ_Buf;
    HIMCC h_ಸಂದೇಶ_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#ಆದರೆ_ಅಂತ್ಯ

// Corner rounding support  (Win 11+)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWMWA_ಕಿಟಕಿ_ಮೂಲೆ_PREFERENCE
#ವ್ಯಾಖ್ಯಾನಿಸು DWMWA_ಕಿಟಕಿ_ಮೂಲೆ_PREFERENCE 33
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_ಸುತ್ತು = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_ಕಿಟಕಿ_ಮೂಲೆ_PREFERENCE;

// Border Color support (Win 11+)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWMWA_BORDER_COLOR
#ವ್ಯಾಖ್ಯಾನಿಸು DWMWA_BORDER_COLOR 34
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWMWA_COLOR_DEFAULT
#ವ್ಯಾಖ್ಯಾನಿಸು DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWMWA_COLOR_NONE
#ವ್ಯಾಖ್ಯಾನಿಸು DWMWA_COLOR_NONE 0xFFFFFFFE
#ಆದರೆ_ಅಂತ್ಯ

// Transparent window support
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWM_BB_ENABLE
#ವ್ಯಾಖ್ಯಾನಿಸು DWM_BB_ENABLE 0x00000001
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DWM_BB_BLURREGION
#ವ್ಯಾಖ್ಯಾನಿಸು DWM_BB_BLURREGION 0x00000002
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ render;

    bool coinitialized;
#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#ಆದರೆ_ಅಂತ್ಯ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_ಎಣಿಕೆ;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_ಬಫರ್_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_ಮಾರ್ಗ_INFO*, UINT32 *, DISPLAYCONFIG_ಬಹುಲಕ_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_ಶೀರ್ಷಿಕೆ*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_ಒಳಹರಿವು_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_ಒಳಹರಿವು_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, ಪೂರ್ಣಾಂಕ );
    BOOL (WINAPI *ರಿಜಿಸ್ಟರ್_Touch_ಕಿಟಕಿ)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(ಶೂನ್ಯ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_ಕಿಟಕಿ)(HWND hwnd, ಸ್ಥಿರಾಂಕ DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_ಗಣ_ಕಿಟಕಿ_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_ಸೂಚಕ_Type)(UINT32 ಸೂಚಕ_Id, ಸೂಚಕ_ಒಳಹರಿವು_TYPE *ಸೂಚಕ_Type);
    BOOL (WINAPI *Get_ಸೂಚಕ_Pen_Info)(UINT32 ಸೂಚಕ_Id, ಸೂಚಕ_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_ಸೂಚಕ_Device_Rects)(HANDLE device, RECT *ಸೂಚಕ_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *ಗಣ_Process_DPIAware)( ಶೂನ್ಯ );
    BOOL (WINAPI *ಗಣ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *ಗಣ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( ಶೂನ್ಯ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_ಕಿಟಕಿ_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_ಕಿಟಕಿ)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *ಗಣ_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#ಆದರೆ_ಅಂತ್ಯ                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#ಆದರೆ_ಅಂತ್ಯ

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_ಸ್ಥಾನಾಂತರ;
    UINT rawinput_ಗಾತ್ರ;
    UINT rawinput_ಎಣಿಕೆ;
    Uint64 ಕೊನೆಯ_rawinput_poll;
    SDL_ಬಿಂದು ಕೊನೆಯ_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_ಕೀಲಿ_sequence;
    SDL_PenID raw_ಒಳಹರಿವು_fake_pen_id;

    WIN_Game_ಒಳಹರಿವು_ದತ್ತಾಂಶ *gameinput_context;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_ಲಭ್ಯ;
    bool ime_ಆಂತರಿಕ_composition;
    bool ime_ಆಂತರಿಕ_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    ಪೂರ್ಣಾಂಕ ime_composition_ಉದ್ದಳತೆ;
    WCHAR ime_readingstring[16];
    ಪೂರ್ಣಾಂಕ ime_cursor;
    ಪೂರ್ಣಾಂಕ ime_selected_ಆರಂಭ;
    ಪೂರ್ಣಾಂಕ ime_selected_ಉದ್ದಳತೆ;

    bool ime_candidates_open;
    bool ime_update_candidates;
    ಅಕ್ಷರ *ime_candidates[MAX_CANDLIST];
    ಪೂರ್ಣಾಂಕ ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    ಪೂರ್ಣಾಂಕ ime_candlistindexbase;
    bool ime_horizontal_candidates;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_ಸೂಚ್ಯಂಕ, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_ಕಿಟಕಿ)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_ಬೀಗ_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_ಬೀಗ_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#ಆದರೆ_ಅಂತ್ಯ // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_ಕೀಲಿ_state[256];
    UINT _SDL_WAKEUP;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#ಆದರೆ_ಅಂತ್ಯ
};

ಬಾಹ್ಯ bool g_Windows_Enable_ಸಂದೇಶ_Loop;
ಬಾಹ್ಯ bool g_WindowsEnableMenuMnemonics;
ಬಾಹ್ಯ bool g_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IDirect3D9 IDirect3D9;
ಬಾಹ್ಯ bool D3_D_ತುಂಬು_DLL(ಶೂನ್ಯ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

ಬಾಹ್ಯ SDL_SystemTheme WIN_GetSystemTheme(ಶೂನ್ಯ);
ಬಾಹ್ಯ bool WIN_Is_ಪ್ರತಿ_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowsvideo_h_
