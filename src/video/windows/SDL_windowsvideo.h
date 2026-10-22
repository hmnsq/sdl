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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_windowsvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_windowsvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_windows.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __cplusplus
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CINTERFACE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgi.h>
#ਜੇ_ਅੰਤ

#ਜੇ defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ਅਨ੍ਤਰ੍ਭਾਵ <msctf.h>
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_msctf.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <imm.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CANDLIST   10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CANDLENGTH 256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CANDSIZE   (ਆਕਾਰ(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsgameinput.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsopengl.h"

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsshape.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowskeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsopengles.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowswindow.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USER_DEFAULT_SCREEN_DPI
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_DEFAULT_SCREEN_DPI 96
#ਜੇ_ਅੰਤ

#ਜੇ WINVER < _WIN32_WINNT_WIN7
// Touch input definitions
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TWF_FINETOUCH 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TWF_WANTPALM  2

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHEVENTF_MOVE 0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHEVENTF_ਥੱਲੇ 0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHEVENTF_ਉੱਪਰ   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _TOUCHINPUT
{
    LONG x;
    LONG y;
    HANDLE h_ਸਰੋਤ;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dw_ਨਕਾਬ;
    DWORD dw_ਸਮਾਂ;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

// More-robust display information in Vista...
// This is a huge amount of data to be stuffing into three API calls. :(
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਰਸਤਾ_ਸਰੋਤ_INFO
{
    LUID adapterId;
    UINT32 id;
    ਸੰਘ
    {
        UINT32 ਬਹੁਲਕ_Info_Idx;
        ਬਣਤਰ
        {
            UINT32 clone_ਸਮੂਹ_Id : 16;
            UINT32 ਸਰੋਤ_ਬਹੁਲਕ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    UINT32 ਸਥਿਤੀ_Flags;
} DISPLAYCONFIG_ਰਸਤਾ_ਸਰੋਤ_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} DISPLAYCONFIG_RATIONAL;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਰਸਤਾ_ਨਿਸ਼ਾਨਾ_INFO
{
    LUID adapterId;
    UINT32 id;
    ਸੰਘ
    {
        UINT32 ਬਹੁਲਕ_Info_Idx;
        ਬਣਤਰ
        {
            UINT32 desktop_ਬਹੁਲਕ_Info_Idx : 16;
            UINT32 ਨਿਸ਼ਾਨਾ_ਬਹੁਲਕ_Info_Idx : 16;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT32 /*DISPLAYCONFIG_ROTATION*/ rotation;
    UINT32 /*DISPLAYCONFIG_SCALING*/ scaling;
    DISPLAYCONFIG_RATIONAL refresh_ਦਰ_2;
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ ਜਾਂਚ_ਸਤਰ_Ordering;
    BOOL ਨਿਸ਼ਾਨਾ_ਉਪਲਬਧ;
    UINT32 ਸਥਿਤੀ_Flags;
} DISPLAYCONFIG_ਰਸਤਾ_ਨਿਸ਼ਾਨਾ_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਰਸਤਾ_INFO
{
    DISPLAYCONFIG_ਰਸਤਾ_ਸਰੋਤ_INFO ਸਰੋਤ_Info;
    DISPLAYCONFIG_ਰਸਤਾ_ਨਿਸ਼ਾਨਾ_INFO ਨਿਸ਼ਾਨਾ_Info;
    UINT32 flags;
} DISPLAYCONFIG_ਰਸਤਾ_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE_ਸਰੋਤ = 1,
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE_ਨਿਸ਼ਾਨਾ = 2,
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE_DESKTOP_IMAGE = 3,
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_2DREGION
{
    UINT32 cx;
    UINT32 cy;
} DISPLAYCONFIG_2DREGION;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_VIDEO_SIGNAL_INFO
{
    UINT64 pixel_ਦਰ;
    DISPLAYCONFIG_RATIONAL hSyncFreq;
    DISPLAYCONFIG_RATIONAL vSyncFreq;
    DISPLAYCONFIG_2DREGION ਸਰਗਰਮ_ਮਾਪ;
    DISPLAYCONFIG_2DREGION ਕੁੱਲ_ਮਾਪ;

    ਸੰਘ
    {
        ਬਣਤਰ
        {
            UINT32 videoStandard : 16;

            // Vertical refresh frequency divider
            UINT32 vSyncFreqDivider : 6;

            UINT32 reserved : 10;
        } AdditionalSignalInfo;

        UINT32 videoStandard;
    } DUMMYUNIONNAME;

    // Scan line ordering (e.g. progressive, interlaced).
    UINT32 /*DISPLAYCONFIG_SCANLINE_ORDERING*/ ਜਾਂਚ_ਸਤਰ_Ordering;
} DISPLAYCONFIG_VIDEO_SIGNAL_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਸਰੋਤ_ਬਹੁਲਕ
{
    UINT32 ਚੌੜਾਈ;
    UINT32 ਉਚਾਈ;
    UINT32 /*DISPLAYCONFIG_PIXELFORMAT*/ pixelFormat;
    POINTL position;
} DISPLAYCONFIG_ਸਰੋਤ_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_ਬਹੁਲਕ
{
    DISPLAYCONFIG_VIDEO_SIGNAL_INFO ਨਿਸ਼ਾਨਾ_Video_Signal_Info;
} DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_DESKTOP_IMAGE_INFO
{
    POINTL ਰਸਤਾ_ਸਰੋਤ_ਮਾਪ;
    RECTL DesktopImageRegion;
    RECTL DesktopImageClip;
} DISPLAYCONFIG_DESKTOP_IMAGE_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਬਹੁਲਕ_INFO
{
    DISPLAYCONFIG_ਬਹੁਲਕ_INFO_TYPE infoType;
    UINT32 id;
    LUID adapterId;
    ਸੰਘ
    {
        DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_ਬਹੁਲਕ ਨਿਸ਼ਾਨਾ_ਬਹੁਲਕ;
        DISPLAYCONFIG_ਸਰੋਤ_ਬਹੁਲਕ ਸਰੋਤ_ਬਹੁਲਕ;
        DISPLAYCONFIG_DESKTOP_IMAGE_INFO desktopImageInfo;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ਬਹੁਲਕ_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ DISPLAYCONFIG_TOPOLOGY_ID
{
    DISPLAYCONFIG_TOPOLOGY_ਅੰਦਰੂਨੀ = 0x00000001,
    DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
    DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
    DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
    DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    DISPLAYCONFIG_DEVICE_INFO_GET_ਸਰੋਤ_NAME = 1,
    DISPLAYCONFIG_DEVICE_INFO_GET_ਨਿਸ਼ਾਨਾ_NAME = 2,
    DISPLAYCONFIG_DEVICE_INFO_GET_ਨਿਸ਼ਾਨਾ_PREFERRED_ਬਹੁਲਕ = 3,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME = 4,
    DISPLAYCONFIG_DEVICE_INFO_ਸੈੱਟ_ਨਿਸ਼ਾਨਾ_PERSISTENCE = 5,
    DISPLAYCONFIG_DEVICE_INFO_GET_ਨਿਸ਼ਾਨਾ_ਅਧਾਰ_TYPE = 6,
    DISPLAYCONFIG_DEVICE_INFO_GET_SUPPORT_VIRTUAL_RESOLUTION = 7,
    DISPLAYCONFIG_DEVICE_INFO_ਸੈੱਟ_SUPPORT_VIRTUAL_RESOLUTION = 8,
    DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO = 9,
    DISPLAYCONFIG_DEVICE_INFO_ਸੈੱਟ_ADVANCED_COLOR_STATE = 10,
    DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL = 11,
    DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_DEVICE_INFO_TYPE;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ
{
    DISPLAYCONFIG_DEVICE_INFO_TYPE type;
    UINT32 ਮਾਪ;
    LUID adapterId;
    UINT32 id;
} DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਸਰੋਤ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    WCHAR viewGdiDeviceName[CCHDEVICENAME];
} DISPLAYCONFIG_ਸਰੋਤ_DEVICE_NAME;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME_FLAGS
{
    ਸੰਘ
    {
        ਬਣਤਰ
        {
            UINT32 friendlyNameFromEdid : 1;
            UINT32 friendlyNameForced : 1;
            UINT32 edidIdsValid : 1;
            UINT32 reserved : 29;
        } DUMMYSTRUCTNAME;
        UINT32 ਮੁੱਲ;
    } DUMMYUNIONNAME;
} DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME_FLAGS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME
{
    DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME_FLAGS flags;
    UINT32 /*DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY*/ outputTechnology;
    UINT16 edidManufactureId;
    UINT16 edid_ਗੁਣਨਫਲ_ਕੋਡ_Id;
    UINT32 connectorInstance;
    WCHAR monitorFriendlyDeviceName[64];
    WCHAR monitor_Device_ਰਸਤਾ[128];
} DISPLAYCONFIG_ਨਿਸ਼ਾਨਾ_DEVICE_NAME;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QDC_ONLY_ਸਰਗਰਮ_PATHS 0x00000002

#ਜੇ_ਅੰਤ // WINVER < _WIN32_WINNT_WIN7

#ਜੇ WINVER < _WIN32_WINNT_WIN8
// Pen input definitions
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_NEW 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_INRANGE 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_INCONTACT 0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_FIRSTBUTTON 0x00000010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_SECONDBUTTON 0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_THIRDBUTTON 0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_FOURTHBUTTON 0x00000080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_FIFTHBUTTON 0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_PRIMARY 0x00002000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_CONFIDENCE 0x00004000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_CANCELED 0x00008000

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_POINTERID_WPARAM(wParam) (LOWORD(wParam))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_ਸੂਚਕ_FLAG_ਸੈੱਟ_WPARAM(wParam, flag) (((DWORD)HIWORD(wParam) & (flag)) == (flag))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_ਸੂਚਕ_INCONTACT_WPARAM(wParam) IS_ਸੂਚਕ_FLAG_ਸੈੱਟ_WPARAM(wParam, ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_INCONTACT)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_ਸੂਚਕ_FIRSTBUTTON_WPARAM(wParam) IS_ਸੂਚਕ_FLAG_ਸੈੱਟ_WPARAM(wParam, ਸੂਚਕ_ਸੁਨੇਹਾ_FLAG_FIRSTBUTTON)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ DWORD ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE;

ਗਿਣਤੀ ਟੈਗ_ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE
{
    PT_ਸੂਚਕ = 1,
    PT_TOUCH,
    PT_PEN,
    PT_MOUSE,
    PT_TOUCHPAD
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ UINT32 ਸੂਚਕ_FLAGS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ UINT32 PEN_FLAGS;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_FLAG_NONE 0x00000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_FLAG_BARREL 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_FLAG_INVERTED 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_FLAG_ERASER 0x00000004

ਕਿਸਮਪਰਿਭਾਸ਼ਾ UINT32 PEN_ਨਕਾਬ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ਨਕਾਬ_NONE 0x00000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ਨਕਾਬ_PRESSURE 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ਨਕਾਬ_ROTATION 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ਨਕਾਬ_TILT_X 0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ਨਕਾਬ_TILT_Y 0x00000008

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ਟੈਗ_ਸੂਚਕ_BUTTON_CHANGE_TYPE
{
    ਸੂਚਕ_CHANGE_NONE,
    ਸੂਚਕ_CHANGE_FIRSTBUTTON_ਥੱਲੇ,
    ਸੂਚਕ_CHANGE_FIRSTBUTTON_ਉੱਪਰ,
    ਸੂਚਕ_CHANGE_SECONDBUTTON_ਥੱਲੇ,
    ਸੂਚਕ_CHANGE_SECONDBUTTON_ਉੱਪਰ,
    ਸੂਚਕ_CHANGE_THIRDBUTTON_ਥੱਲੇ,
    ਸੂਚਕ_CHANGE_THIRDBUTTON_ਉੱਪਰ,
    ਸੂਚਕ_CHANGE_FOURTHBUTTON_ਥੱਲੇ,
    ਸੂਚਕ_CHANGE_FOURTHBUTTON_ਉੱਪਰ,
    ਸੂਚਕ_CHANGE_FIFTHBUTTON_ਥੱਲੇ,
    ਸੂਚਕ_CHANGE_FIFTHBUTTON_ਉੱਪਰ
} ਸੂਚਕ_BUTTON_CHANGE_TYPE;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਟੈਗ_ਸੂਚਕ_INFO
{
    ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE ਸੂਚਕ_Type;
    UINT32 ਸੂਚਕ_Id;
    UINT32 ਚੌਖਟਾ_Id;
    ਸੂਚਕ_FLAGS ਸੂਚਕ_Flags;
    HANDLE ਸਰੋਤ_Device;
    HWND hwnd_ਨਿਸ਼ਾਨਾ;
    ਬਿੰਦੂ_2 ptPixelLocation;
    ਬਿੰਦੂ_2 ptHimetricLocation;
    ਬਿੰਦੂ_2 ptPixelLocationRaw;
    ਬਿੰਦੂ_2 ptHimetricLocationRaw;
    DWORD dw_ਸਮਾਂ;
    UINT32 history_ਗਿਣਤੀ;
    INT32 ਨਿਵੇਸ਼_ਅੰਕੜੇ;
    DWORD dw_ਕੁੰਜੀ_ਹਾਲਤਾਂ;
    UINT64 Performance_ਗਿਣਤੀ;
    ਸੂਚਕ_BUTTON_CHANGE_TYPE ButtonChangeType;
} ਸੂਚਕ_INFO;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਟੈਗ_ਸੂਚਕ_PEN_INFO
{
    ਸੂਚਕ_INFO ਸੂਚਕ_Info;
    PEN_FLAGS penFlags;
    PEN_ਨਕਾਬ pen_ਨਕਾਬ;
    UINT32 pressure;
    UINT32 rotation;
    INT32 tiltX;
    INT32 tiltY;
} ਸੂਚਕ_PEN_INFO;

#ਜੇ_ਅੰਤ // WINVER < _WIN32_WINNT_WIN8

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_SHELLSCALINGAPI_H

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_ਪ੍ਰਤੀ_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <shellscalingapi.h>
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITaskbarList3 ITaskbarList3;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _DPI_AWARENESS_CONTEXTS_

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_ਪ੍ਰਤੀ_MONITOR_AWARE = 2
} DPI_AWARENESS;

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPI_AWARENESS_CONTEXT_UNAWARE           ((DPI_AWARENESS_CONTEXT)-1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPI_AWARENESS_CONTEXT_SYSTEM_AWARE      ((DPI_AWARENESS_CONTEXT)-2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE ((DPI_AWARENESS_CONTEXT)-3)

#ਜੇ_ਅੰਤ // _DPI_AWARENESS_CONTEXTS_

// Windows 10 Creators Update
#ਜੇ NTDDI_ਸੰਸਕਰਣ < 0x0A000003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#ਜੇ_ਅੰਤ // NTDDI_VERSION < 0x0A000003

// Windows 10 version 1809
#ਜੇ NTDDI_ਸੰਸਕਰਣ < 0x0A000006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED ((DPI_AWARENESS_CONTEXT)-5)
#ਜੇ_ਅੰਤ // NTDDI_VERSION < 0x0A000006

ਕਿਸਮਪਰਿਭਾਸ਼ਾ BOOL (*PFNSHFullScreen)(HWND, DWORD);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*PFCoordTransform)(SDL_ਖਿੜਕੀ *, ਬਿੰਦੂ_2 *);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਖਾਲੀ **lpVtbl;
    ਪੂਰਨ refcount;
    ਖਾਲੀ *ਅੰਕੜੇ;
} TSFSink;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
// Definition from Win98DDK version of IMM.H
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਟੈਗ_INPUTCONTEXT2
{
    HWND hWnd;
    BOOL fOpen;
    ਬਿੰਦੂ_2 pt_ਸਥਿਤੀ_Wnd_Pos;
    ਬਿੰਦੂ_2 ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    ਸੰਘ
    {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC h_Guide_ਸਤਰ;
    HIMCC h_ਨਿੱਜੀ;
    DWORD dw_ਅੰਕ_ਸੁਨੇਹਾ_Buf;
    HIMCC h_ਸੁਨੇਹਾ_Buf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;
#ਜੇ_ਅੰਤ

// Corner rounding support  (Win 11+)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWMWA_ਖਿੜਕੀ_ਕੋਨਾ_PREFERENCE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWMWA_ਖਿੜਕੀ_ਕੋਨਾ_PREFERENCE 33
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ {
    DWMWCP_DEFAULT = 0,
    DWMWCP_DONOTROUND = 1,
    DWMWCP_ਗੇੜਾ = 2,
    DWMWCP_ROUNDSMALL = 3
} DWM_ਖਿੜਕੀ_ਕੋਨਾ_PREFERENCE;

// Border Color support (Win 11+)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWMWA_BORDER_COLOR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWMWA_BORDER_COLOR 34
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWMWA_COLOR_DEFAULT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWMWA_COLOR_DEFAULT 0xFFFFFFFF
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWMWA_COLOR_NONE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWMWA_COLOR_NONE 0xFFFFFFFE
#ਜੇ_ਅੰਤ

// Transparent window support
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWM_BB_ENABLE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWM_BB_ENABLE 0x00000001
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DWM_BB_BLURREGION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DWM_BB_BLURREGION 0x00000002
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    DWORD flags;
    BOOL enable;
    HRGN blur_region;
    BOOL transition_on_maxed;
} DWM_BLURBEHIND;

// Private display data

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    ਪੂਰਨ render;

    bool coinitialized;
#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
    bool oleinitialized;
#ਜੇ_ਅੰਤ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

    DWORD clipboard_ਗਿਣਤੀ;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES) // Xbox doesn't support user32/shcore
    SDL_SharedObject *userDLL;

    // DisplayConfig functions
    /* *INDENT-OFF* */ // clang-format off
    LONG (WINAPI *Get_Display_Config_ਬਫਰ_Sizes)( UINT32, UINT32 *, UINT32 *);
    LONG (WINAPI *QueryDisplayConfig)( UINT32, UINT32 *, DISPLAYCONFIG_ਰਸਤਾ_INFO*, UINT32 *, DISPLAYCONFIG_ਬਹੁਲਕ_INFO*, DISPLAYCONFIG_TOPOLOGY_ID*);
    LONG (WINAPI *DisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_ਸਿਰਲੇਖ*);
    /* *INDENT-ON* */ // clang-format on

    // Touch input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Close_Touch_ਨਿਵੇਸ਼_Handle)( HTOUCHINPUT );
    BOOL (WINAPI *Get_Touch_ਨਿਵੇਸ਼_Info)( HTOUCHINPUT, UINT, PTOUCHINPUT, ਪੂਰਨ );
    BOOL (WINAPI *ਰਜਿਸਟਰ_Touch_ਖਿੜਕੀ)( HWND, ULONG );
    /* *INDENT-ON* */ // clang-format on

    // DWM functions
    SDL_SharedObject *dwmapiDLL;
    /* *INDENT-OFF* */ // clang-format off
    HRESULT (WINAPI *DwmFlush)(ਖਾਲੀ);
    HRESULT (WINAPI *Dwm_Enable_Blur_Behind_ਖਿੜਕੀ)(HWND hwnd, ਅਚਲ DWM_BLURBEHIND *pBlurBehind);
    HRESULT (WINAPI *Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    /* *INDENT-ON* */ // clang-format on

    // Pen input functions
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *Get_ਸੂਚਕ_Type)(UINT32 ਸੂਚਕ_Id, ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE *ਸੂਚਕ_Type);
    BOOL (WINAPI *Get_ਸੂਚਕ_Pen_Info)(UINT32 ਸੂਚਕ_Id, ਸੂਚਕ_PEN_INFO *penInfo);
    BOOL (WINAPI *Get_ਸੂਚਕ_Device_Rects)(HANDLE device, RECT *ਸੂਚਕ_Device_Rect, RECT *displayRect);
    /* *INDENT-ON* */ // clang-format on

    // DPI functions
    SDL_SharedObject *shcoreDLL;
    /* *INDENT-OFF* */ // clang-format off
    BOOL (WINAPI *ਸੈੱਟ_Process_DPIAware)( ਖਾਲੀ );
    BOOL (WINAPI *ਸੈੱਟ_Process_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *ਸੈੱਟ_Thread_Dpi_Awareness_Context)( DPI_AWARENESS_CONTEXT );
    DPI_AWARENESS_CONTEXT (WINAPI *GetThreadDpiAwarenessContext)( ਖਾਲੀ );
    DPI_AWARENESS (WINAPI *GetAwarenessFromDpiAwarenessContext)( DPI_AWARENESS_CONTEXT );
    BOOL (WINAPI *EnableNonClientDpiScaling)( HWND );
    BOOL (WINAPI *Adjust_ਖਿੜਕੀ_Rect_Ex_For_Dpi)( LPRECT, DWORD, BOOL, DWORD, UINT );
    UINT (WINAPI *Get_Dpi_For_ਖਿੜਕੀ)( HWND );
    BOOL (WINAPI *AreDpiAwarenessContextsEqual)(DPI_AWARENESS_CONTEXT, DPI_AWARENESS_CONTEXT);
    BOOL (WINAPI *IsValidDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    HRESULT (WINAPI *ਸੈੱਟ_Process_Dpi_Awareness)(PROCESS_DPI_AWARENESS dpiAwareness);
    /* *INDENT-ON* */ // clang-format on
#ਜੇ_ਅੰਤ                // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DXGI_H
    SDL_SharedObject *dxgiDLL;
    IDXGIFactory *pDXGIFactory;
#ਜੇ_ਅੰਤ

    bool cleared;
    bool dpi_unaware_context_declared;

    bool detect_device_hotplug;

    BYTE *rawinput;
    UINT rawinput_ਵਿੱਥ;
    UINT rawinput_ਮਾਪ;
    UINT rawinput_ਗਿਣਤੀ;
    Uint64 ਆਖਰੀ_rawinput_poll;
    SDL_ਬਿੰਦੂ ਆਖਰੀ_raw_mouse_position;
    bool raw_mouse_enabled;
    bool raw_mouse_flag_nolegacy;
    bool raw_keyboard_enabled;
    bool raw_keyboard_flag_nohotkeys;
    bool raw_keyboard_flag_inputsink;
    bool pending_E1_ਕੁੰਜੀ_sequence;
    SDL_PenID raw_ਨਿਵੇਸ਼_fake_pen_id;

    WIN_Game_ਨਿਵੇਸ਼_ਅੰਕੜੇ *gameinput_context;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    bool ime_initialized;
    bool ime_enabled;
    bool ime_ਉਪਲਬਧ;
    bool ime_ਅੰਦਰੂਨੀ_composition;
    bool ime_ਅੰਦਰੂਨੀ_candidates;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    bool ime_needs_clear_composition;
    HIMC ime_himc;

    WCHAR *ime_composition;
    ਪੂਰਨ ime_composition_ਲੰਮਾਈ;
    WCHAR ime_readingstring[16];
    ਪੂਰਨ ime_cursor;
    ਪੂਰਨ ime_selected_ਸ਼ੁਰੂ;
    ਪੂਰਨ ime_selected_ਲੰਮਾਈ;

    bool ime_candidates_open;
    bool ime_update_candidates;
    ਅੱਖਰ *ime_candidates[MAX_CANDLIST];
    ਪੂਰਨ ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    ਪੂਰਨ ime_candlistindexbase;
    bool ime_horizontal_candidates;
#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    COMPOSITIONFORM ime_composition_area;
    CANDIDATEFORM ime_candidate_area;
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_DISABLE_WINDOWS_IME
    HKL ime_hkl;
    SDL_SharedObject *ime_himm32;
    /* *INDENT-OFF* */ // clang-format off
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pn_Error_ਸੂਚਕਾਂਕ, BOOL *pfIsVertical, PUINT puMaxReadingLen);
    BOOL (WINAPI *Show_Reading_ਖਿੜਕੀ)(HIMC himc, BOOL bShow);
    LPINPUTCONTEXT2 (WINAPI *Imm_ਤਾਲਾ_IMC)(HIMC himc);
    BOOL (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *Imm_ਤਾਲਾ_IMCC)(HIMCC himcc);
    BOOL (WINAPI *ImmUnlockIMCC)(HIMCC himcc);
    /* *INDENT-ON* */ // clang-format on

#ਜੇ_ਅੰਤ // !SDL_DISABLE_WINDOWS_IME

    BYTE pre_hook_ਕੁੰਜੀ_state[256];
    UINT _SDL_WAKEUP;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    UINT WM_TASKBAR_BUTTON_CREATED;
    ITaskbarList3 *taskbar_list;
#ਜੇ_ਅੰਤ
};

ਬਾਹਰੀ bool g_Windows_Enable_ਸੁਨੇਹਾ_Loop;
ਬਾਹਰੀ bool g_WindowsEnableMenuMnemonics;
ਬਾਹਰੀ bool g_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IDirect3D9 IDirect3D9;
ਬਾਹਰੀ bool D3_D_ਲੱਦੋ_DLL(ਖਾਲੀ **pD3DDLL, IDirect3D9 **pDirect3D9Interface);

ਬਾਹਰੀ SDL_SystemTheme WIN_GetSystemTheme(ਖਾਲੀ);
ਬਾਹਰੀ bool WIN_Is_ਪ੍ਰਤੀ_Monitor_V2_DPIAware(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_windowsvideo_h_
