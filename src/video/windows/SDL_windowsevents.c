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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/scancodes_windows.h"
#ಅನ್ತರ್ಭಾವ "../../main/SDL_main_callbacks.h"
#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_hid.h"

// Dropfile support
#ಅನ್ತರ್ಭಾವ <shellapi.h>

// Device names
#ಅನ್ತರ್ಭಾವ <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#ಅನ್ತರ್ಭಾವ <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_TPCSHRD_H
#ಅನ್ತರ್ಭಾವ <tpcshrd.h>
#ಆದರೆ_ಅಂತ್ಯ // HAVE_TPCSHRD_H

#ಆದರೆ 0
#ವ್ಯಾಖ್ಯಾನಿಸು WMMSG_DEBUG
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WMMSG_DEBUG
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "wmmsg.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ಅನ್ತರ್ಭಾವ <shobjidl.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_GDK
#ಅನ್ತರ್ಭಾವ "../../core/gdk/SDL_gdk.h"
#ಆದರೆ_ಅಂತ್ಯ

// #define HIGHDPI_DEBUG

// Undocumented window messages
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_NCUAHDRAWCAPTION
#ವ್ಯಾಖ್ಯಾನಿಸು WM_NCUAHDRAWCAPTION 0xAE
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_NCUAHDRAWFRAME
#ವ್ಯಾಖ್ಯಾನಿಸು WM_NCUAHDRAWFRAME 0xAF
#ಆದರೆ_ಅಂತ್ಯ

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_XBUTTONDOWN
#ವ್ಯಾಖ್ಯಾನಿಸು WM_XBUTTONDOWN 0x020B
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_XBUTTONUP
#ವ್ಯಾಖ್ಯಾನಿಸು WM_XBUTTONUP 0x020C
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GET_XBUTTON_WPARAM
#ವ್ಯಾಖ್ಯಾನಿಸು GET_XBUTTON_WPARAM(w) (HIWORD(w))
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_ಒಳಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು WM_ಒಳಹರಿವು 0x00ff
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_TOUCH
#ವ್ಯಾಖ್ಯಾನಿಸು WM_TOUCH 0x0240
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_MOUSEHWHEEL
#ವ್ಯಾಖ್ಯಾನಿಸು WM_MOUSEHWHEEL 0x020E
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ RI_MOUSE_HWHEEL
#ವ್ಯಾಖ್ಯಾನಿಸು RI_MOUSE_HWHEEL 0x0800
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERUPDATE
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERUPDATE 0x0245
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERDOWN
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERDOWN 0x0246
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERUP
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERUP 0x0247
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERENTER
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERENTER 0x0249
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERLEAVE
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERLEAVE 0x024A
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POINTERCAPTURECHANGED
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POINTERCAPTURECHANGED 0x024C
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_UNICHAR
#ವ್ಯಾಖ್ಯಾನಿಸು WM_UNICHAR 0x0109
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_DPICHANGED
#ವ್ಯಾಖ್ಯಾನಿಸು WM_DPICHANGED 0x02E0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_GETDPISCALEDSIZE
#ವ್ಯಾಖ್ಯಾನಿಸು WM_GETDPISCALEDSIZE 0x02E4
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TOUCHEVENTF_PEN
#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHEVENTF_PEN 0x0040
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MAPVK_VK_ಗಮ್ಯ_VSC_EX
#ವ್ಯಾಖ್ಯಾನಿಸು MAPVK_VK_ಗಮ್ಯ_VSC_EX 4
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WC_ERR_INVALID_CHARS
#ವ್ಯಾಖ್ಯಾನಿಸು WC_ERR_INVALID_CHARS 0x00000080
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IS_ಮೇಲಿನ_SURROGATE
#ವ್ಯಾಖ್ಯಾನಿಸು IS_ಮೇಲಿನ_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USER_TIMER_MINIMUM
#ವ್ಯಾಖ್ಯಾನಿಸು USER_TIMER_MINIMUM 0x0000000A
#ಆದರೆ_ಅಂತ್ಯ

// Used to compare Windows message timestamps
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN64
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool SDL_processing_messages;
ಸ್ಥಿರ DWORD ಸಂದೇಶ_tick;
ಸ್ಥಿರ Uint64 timestamp_ಸ್ಥಾನಾಂತರ;

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ಗಣ_ಸಂದೇಶ_Tick(DWORD tick)
{
    ಸಂದೇಶ_tick = tick;
}

ಸ್ಥಿರ Uint64 WIN_GetEventTimestamp(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ Uint64 TIMESTAMP_WRAP_ಸ್ಥಾನಾಂತರ = SDL_MS_ಗಮ್ಯ_NS(0x100000000LL);
    Uint64 timestamp, now;

    ಆದರೆ (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        ಹಿಂತಿರುಗಿ 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_ಗಮ್ಯ_NS(ಸಂದೇಶ_tick);
    timestamp += timestamp_ಸ್ಥಾನಾಂತರ;
    ಆದರೆ (!timestamp_ಸ್ಥಾನಾಂತರ) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_ಸ್ಥಾನಾಂತರ = (now - timestamp);
        timestamp = now;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((Sint64)(now - timestamp - TIMESTAMP_WRAP_ಸ್ಥಾನಾಂತರ) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_ಸ್ಥಾನಾಂತರ += TIMESTAMP_WRAP_ಸ್ಥಾನಾಂತರ;
        timestamp += TIMESTAMP_WRAP_ಸ್ಥಾನಾಂತರ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_ಸ್ಥಾನಾಂತರ -= (timestamp - now);
        timestamp = now;
    }
    ಹಿಂತಿರುಗಿ timestamp;
}

// A message hook called before TranslateMessage()
ಸ್ಥಿರ SDL_Windows_ಸಂದೇಶ_Hook g_Windows_ಸಂದೇಶ_Hook = ಖಾಲಿ;
ಸ್ಥಿರ ಶೂನ್ಯ *g_Windows_ಸಂದೇಶ_Hook_ದತ್ತಾಂಶ = ಖಾಲಿ;

ಶೂನ್ಯ SDL_ಗಣ_Windows_ಸಂದೇಶ_Hook(SDL_Windows_ಸಂದೇಶ_Hook callback, ಶೂನ್ಯ *userdata)
{
    g_Windows_ಸಂದೇಶ_Hook = callback;
    g_Windows_ಸಂದೇಶ_Hook_ದತ್ತಾಂಶ = userdata;
}

ಸ್ಥಿರ SDL_Scancode Windows_ಪರಿಶೀಲನೆ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScan_ಸಂಕೇತ(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_ಕೀಲಿ)
{
    SDL_Scancode ಸಂಕೇತ_2;
    Uint8 ಸೂಚ್ಯಂಕ;
    Uint16 ಕೀಲಿ_Flags = HIWORD(lParam);
    Uint16 ಪರಿಶೀಲನೆ_ಸಂಕೇತ = LOBYTE(ಕೀಲಿ_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    ಪರಿಶೀಲನೆ_ಸಂಕೇತ &= ~0x80;

    *virtual_ಕೀಲಿ = (ಪರಿಶೀಲನೆ_ಸಂಕೇತ == 0);

    ಆದರೆ (ಪರಿಶೀಲನೆ_ಸಂಕೇತ != 0) {
        ಆದರೆ ((ಕೀಲಿ_Flags & KF_EXTENDED) == KF_EXTENDED) {
            ಪರಿಶೀಲನೆ_ಸಂಕೇತ = MAKEWORD(ಪರಿಶೀಲನೆ_ಸಂಕೇತ, 0xe0);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಪರಿಶೀಲನೆ_ಸಂಕೇತ == 0x45) {
            // Pause
            ಪರಿಶೀಲನೆ_ಸಂಕೇತ = 0xe046;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        Uint16 vk_ಸಂಕೇತ = LOWORD(wParam);

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = LOWORD(Map_Virtual_ಕೀಲಿ(vk_ಸಂಕೇತ, WIN_IsWindowsXP() ? MAPVK_VK_ಗಮ್ಯ_VSC : MAPVK_VK_ಗಮ್ಯ_VSC_EX));
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        ಆದರೆ (ಪರಿಶೀಲನೆ_ಸಂಕೇತ == 0xe11d) {
            ಪರಿಶೀಲನೆ_ಸಂಕೇತ = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    ಸೂಚ್ಯಂಕ = LOBYTE(ಪರಿಶೀಲನೆ_ಸಂಕೇತ) | (HIBYTE(ಪರಿಶೀಲನೆ_ಸಂಕೇತ) ? 0x80 : 0x00);
    ಸಂಕೇತ_2 = windows_scancode_ಕೋಷ್ಟಕ[ಸೂಚ್ಯಂಕ];
    *rawcode = ಪರಿಶೀಲನೆ_ಸಂಕೇತ;

    ಹಿಂತಿರುಗಿ ಸಂಕೇತ_2;
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಸ್ಥಿರ bool WIN_ShouldIgnoreFocusClick(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಹಿಂತಿರುಗಿ !SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_ಅದಲುಬದಲು_Buttons, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, Uint8 button, SDL_MouseID mouseID)
{
    ಆದರೆ (b_ಅದಲುಬದಲು_Buttons) {
        ಆದರೆ (button == SDL_BUTTON_ಎಡ) {
            button = SDL_BUTTON_ಬಲ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (button == SDL_BUTTON_ಬಲ) {
            button = SDL_BUTTON_ಎಡ;
        }
    }

    ಆದರೆ (ದತ್ತಾಂಶ->focus_click_pending & SDL_BUTTON_ಮುಖವಾಡ(button)) {
        // Ignore the button click for activation
        ಆದರೆ (!bwParamMousePressed) {
            ದತ್ತಾಂಶ->focus_click_pending &= ~SDL_BUTTON_ಮುಖವಾಡ(button);
            WIN_UpdateClipCursor(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
        }
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_ಮುಖವಾಡ(button))) {
        SDL_SendMouseButton(timestamp, ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID, button, true);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_ಮುಖವಾಡ(button))) {
        SDL_SendMouseButton(timestamp, ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ಸ್ಥಿರ ಶೂನ್ಯ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, SDL_MouseID mouseID)
{
    ಆದರೆ (wParam != ದತ್ತಾಂಶ->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(ಖಾಲಿ, ಖಾಲಿ);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, ದತ್ತಾಂಶ, SDL_BUTTON_ಎಡ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, ದತ್ತಾಂಶ, SDL_BUTTON_ಮಧ್ಯ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, ದತ್ತಾಂಶ, SDL_BUTTON_ಬಲ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, ದತ್ತಾಂಶ, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, ದತ್ತಾಂಶ, SDL_BUTTON_X2, mouseID);

        ದತ್ತಾಂಶ->mouse_button_flags = wParam;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT ಕೀಲಿ_State;
    bool ಅದಲುಬದಲು_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(ಖಾಲಿ, ಖಾಲಿ);
    ಅದಲುಬದಲು_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    ಕೀಲಿ_State = Get_Async_ಕೀಲಿ_State(VK_LBUTTON);
    ಆದರೆ (!(ಕೀಲಿ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ಅದಲುಬದಲು_Buttons, ದತ್ತಾಂಶ, SDL_BUTTON_ಎಡ, mouseID);
    }
    ಕೀಲಿ_State = Get_Async_ಕೀಲಿ_State(VK_RBUTTON);
    ಆದರೆ (!(ಕೀಲಿ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ಅದಲುಬದಲು_Buttons, ದತ್ತಾಂಶ, SDL_BUTTON_ಬಲ, mouseID);
    }
    ಕೀಲಿ_State = Get_Async_ಕೀಲಿ_State(VK_MBUTTON);
    ಆದರೆ (!(ಕೀಲಿ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ಅದಲುಬದಲು_Buttons, ದತ್ತಾಂಶ, SDL_BUTTON_ಮಧ್ಯ, mouseID);
    }
    ಕೀಲಿ_State = Get_Async_ಕೀಲಿ_State(VK_XBUTTON1);
    ಆದರೆ (!(ಕೀಲಿ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ಅದಲುಬದಲು_Buttons, ದತ್ತಾಂಶ, SDL_BUTTON_X1, mouseID);
    }
    ಕೀಲಿ_State = Get_Async_ಕೀಲಿ_State(VK_XBUTTON2);
    ಆದರೆ (!(ಕೀಲಿ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ಅದಲುಬದಲು_Buttons, ದತ್ತಾಂಶ, SDL_BUTTON_X2, mouseID);
    }
    ದತ್ತಾಂಶ->mouse_button_flags = (WPARAM)-1;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_UpdateFocus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool expect_focus, LPPOINT pos)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == ಕಿಟಕಿ);
    bool has_focus = (Get_Foreground_ಕಿಟಕಿ() == hwnd);

    ಆದರೆ (had_focus == has_focus || has_focus != expect_focus) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (has_focus) {
        ಬಿಂದು_2 cursorPos;

        ಆದರೆ (WIN_ShouldIgnoreFocusClick(ದತ್ತಾಂಶ) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
            bool ಅದಲುಬದಲು_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            ಆದರೆ (Get_Async_ಕೀಲಿ_State(VK_LBUTTON)) {
                ದತ್ತಾಂಶ->focus_click_pending |= !ಅದಲುಬದಲು_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            ಆದರೆ (Get_Async_ಕೀಲಿ_State(VK_RBUTTON)) {
                ದತ್ತಾಂಶ->focus_click_pending |= !ಅದಲುಬದಲು_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            ಆದರೆ (Get_Async_ಕೀಲಿ_State(VK_MBUTTON)) {
                ದತ್ತಾಂಶ->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            ಆದರೆ (Get_Async_ಕೀಲಿ_State(VK_XBUTTON1)) {
                ದತ್ತಾಂಶ->focus_click_pending |= SDL_BUTTON_X1_ಮುಖವಾಡ;
            }
            ಆದರೆ (Get_Async_ಕೀಲಿ_State(VK_XBUTTON2)) {
                ದತ್ತಾಂಶ->focus_click_pending |= SDL_BUTTON_X2_ಮುಖವಾಡ;
            }
        }

        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ->keyboard_focus ? ಕಿಟಕಿ->keyboard_focus : ಕಿಟಕಿ);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        ಆದರೆ (!SDL_GetMouse()->relative_ಬಹುಲಕ) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_ಗಮ್ಯ_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)cursorPos.x, (ದಶಮಾಂಶ)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ);
        WIN_UpdateClipCursor(ಕಿಟಕಿ);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(ದತ್ತಾಂಶ->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_ಕೀಲಿ_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_ಅಂಕೆ, (Get_ಕೀಲಿ_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_ಕೀಲಿ_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_ಕಿಟಕಿ_ICCProfile(ದತ್ತಾಂಶ->ಕಿಟಕಿ, true);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->ಒಳ_ಕಿಟಕಿ_deactivation = true;

        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        ಆದರೆ (SDL_GetMouse()->relative_ಬಹುಲಕ) {
            SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
        }
        WIN_Reset_Dead_ಕೀಲಿಗಳು();

        WIN_Unclip_Cursor_For_ಕಿಟಕಿ(ಕಿಟಕಿ);

        ದತ್ತಾಂಶ->ಒಳ_ಕಿಟಕಿ_deactivation = false;
    }
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಸ್ಥಿರ bool Should_Generate_ಕಿಟಕಿ_Close_On_Alt_F4(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ಸ್ಥಿರ bool Should_Clear_ಕಿಟಕಿ_On_Erase_Background(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಆಯ್ಕೆ (ದತ್ತಾಂಶ->hint_erase_background_ಬಹುಲಕ) {
    ಸ್ಥಿತಿ SDL_ERASEBACKGROUNDMODE_NEVER:
        ಹಿಂತಿರುಗಿ false;
    ಸ್ಥಿತಿ SDL_ERASEBACKGROUNDMODE_INITIAL:
        ಹಿಂತಿರುಗಿ !ದತ್ತಾಂಶ->videodata->cleared;
    ಸ್ಥಿತಿ SDL_ERASEBACKGROUNDMODE_ALWAYS:
        ಹಿಂತಿರುಗಿ true;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Unexpected value, fallback to default behaviour
        ಹಿಂತಿರುಗಿ !ದತ್ತಾಂಶ->videodata->cleared;
    }
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#ವ್ಯಾಖ್ಯಾನಿಸು MI_WP_SIGNATURE      0xFF515700
#ವ್ಯಾಖ್ಯಾನಿಸು MI_WP_SIGNATURE_ಮುಖವಾಡ 0xFFFFFF00
#ವ್ಯಾಖ್ಯಾನಿಸು IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_ಮುಖವಾಡ) == MI_WP_SIGNATURE

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    SDL_MOUSE_EVENT_ಮೂಲ_UNKNOWN,
    SDL_MOUSE_EVENT_ಮೂಲ_MOUSE,
    SDL_MOUSE_EVENT_ಮೂಲ_TOUCH,
    SDL_MOUSE_EVENT_ಮೂಲ_PEN,
} SDL_MOUSE_EVENT_ಮೂಲ;

ಸ್ಥಿರ SDL_MOUSE_EVENT_ಮೂಲ Get_Mouse_ಸಂದೇಶ_ಮೂಲ(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    ಆದರೆ (IsTouchEvent(extrainfo)) {
        ಆದರೆ (extrainfo & 0x80) {
            ಹಿಂತಿರುಗಿ SDL_MOUSE_EVENT_ಮೂಲ_TOUCH;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_MOUSE_EVENT_ಮೂಲ_PEN;
        }
    }
    ಹಿಂತಿರುಗಿ SDL_MOUSE_EVENT_ಮೂಲ_MOUSE;
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಸ್ಥಿರ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *WIN_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    ಆದರೆ (_this) {
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
            ಆದರೆ (ದತ್ತಾಂಶ && ದತ್ತಾಂಶ->hwnd == hwnd) {
                ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ;
            }
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(ಪೂರ್ಣಾಂಕ n_ಸಂಕೇತ, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_ದತ್ತಾಂಶ = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    SDL_Scancode ಪರಿಶೀಲನೆ_ಸಂಕೇತ;

    ಆದರೆ (n_ಸಂಕೇತ < 0 || n_ಸಂಕೇತ != HC_ACTION) {
        ಹಿಂತಿರುಗಿ Call_ಮುಂದಿನ_Hook_Ex(ಖಾಲಿ, n_ಸಂಕೇತ, wParam, lParam);
    }
    ಆದರೆ (hook_ದತ್ತಾಂಶ->ಪರಿಶೀಲನೆ_ಸಂಕೇತ == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        ಹಿಂತಿರುಗಿ 1;
    }

    ಆಯ್ಕೆ (hook_ದತ್ತಾಂಶ->vk_ಸಂಕೇತ) {
    ಸ್ಥಿತಿ VK_LWIN:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_LGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_RWIN:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_RGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_LMENU:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_LALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_RMENU:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_RALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_LCONTROL:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_LCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_RCONTROL:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_RCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_SNAPSHOT:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_PRINTSCREEN;
        ನಿಲ್ಲಿಸು;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    ಸ್ಥಿತಿ VK_TAB:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_TAB;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_ESCAPE:
        ಪರಿಶೀಲನೆ_ಸಂಕೇತ = SDL_SCANCODE_ESCAPE;
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ Call_ಮುಂದಿನ_Hook_Ex(ಖಾಲಿ, n_ಸಂಕೇತ, wParam, lParam);
    }

    ಆದರೆ (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        ಆದರೆ (!ದತ್ತಾಂಶ->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, hook_ದತ್ತಾಂಶ->ಪರಿಶೀಲನೆ_ಸಂಕೇತ, ಪರಿಶೀಲನೆ_ಸಂಕೇತ, true);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!ದತ್ತಾಂಶ->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, hook_ದತ್ತಾಂಶ->ಪರಿಶೀಲನೆ_ಸಂಕೇತ, ಪರಿಶೀಲನೆ_ಸಂಕೇತ, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        ಆದರೆ (hook_ದತ್ತಾಂಶ->vk_ಸಂಕೇತ <= 0xFF && ದತ್ತಾಂಶ->pre_hook_ಕೀಲಿ_state[hook_ದತ್ತಾಂಶ->vk_ಸಂಕೇತ]) {
            ದತ್ತಾಂಶ->pre_hook_ಕೀಲಿ_state[hook_ದತ್ತಾಂಶ->vk_ಸಂಕೇತ] = 0;
            ಹಿಂತಿರುಗಿ Call_ಮುಂದಿನ_Hook_Ex(ಖಾಲಿ, n_ಸಂಕೇತ, wParam, lParam);
        }
    }

    ಹಿಂತಿರುಗಿ 1;
}

ಸ್ಥಿರ bool WIN_ಅದಲುಬದಲು_Buttons(HANDLE hDevice)
{
    ಆದರೆ (hDevice == ಖಾಲಿ) {
        // Touchpad, already has buttons swapped
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Handle_Raw_Mouse_ಒಳಹರಿವು(Uint64 timestamp, SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ಸ್ಥಿರ ರಚನೆ {
        USHORT usButtonFlags;
        Uint8 button;
        bool ಕೆಳಕ್ಕೆ;
    } raw_buttons[] = {
        { RI_MOUSE_ಎಡ_BUTTON_ಕೆಳಕ್ಕೆ, SDL_BUTTON_ಎಡ, true },
        { RI_MOUSE_ಎಡ_BUTTON_ಮೇಲೆ, SDL_BUTTON_ಎಡ, false },
        { RI_MOUSE_ಬಲ_BUTTON_ಕೆಳಕ್ಕೆ, SDL_BUTTON_ಬಲ, true },
        { RI_MOUSE_ಬಲ_BUTTON_ಮೇಲೆ, SDL_BUTTON_ಬಲ, false },
        { RI_MOUSE_ಮಧ್ಯ_BUTTON_ಕೆಳಕ್ಕೆ, SDL_BUTTON_ಮಧ್ಯ, true },
        { RI_MOUSE_ಮಧ್ಯ_BUTTON_ಮೇಲೆ, SDL_BUTTON_ಮಧ್ಯ, false },
        { RI_MOUSE_BUTTON_4_ಕೆಳಕ್ಕೆ, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_ಮೇಲೆ, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_ಕೆಳಕ್ಕೆ, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_ಮೇಲೆ, SDL_BUTTON_X2, false }
    };

    ಪೂರ್ಣಾಂಕ dx = (ಪೂರ್ಣಾಂಕ)rawmouse->l_ಕೊನೆಯ_X;
    ಪೂರ್ಣಾಂಕ dy = (ಪೂರ್ಣಾಂಕ)rawmouse->l_ಕೊನೆಯ_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    ಆದರೆ (!ದತ್ತಾಂಶ->raw_mouse_enabled) {
        ಹಿಂತಿರುಗಿ;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = SDL_GetKeyboardFocus();
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    ಆದರೆ (!mouse) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (Get_Mouse_ಸಂದೇಶ_ಮೂಲ(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_ಮೂಲ_MOUSE ||
        (SDL_Touch_Devices_ಲಭ್ಯ() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (haveMotion && !windowdata->ಒಳ_modal_loop) {
        ಆದರೆ (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, mouseID, true, (ದಶಮಾಂಶ)dx, (ದಶಮಾಂಶ)dy);
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* This is absolute motion, either using a tablet or mouse over RDP

                Notes on how RDP appears to work, as of Windows 10 2004:
                - SetCursorPos() calls are cached, with multiple calls coalesced into a single call that's sent to the RDP client. If the last call to SetCursorPos() has the same value as the last one that was sent to the client, it appears to be ignored and not sent. This means that we need to jitter the SetCursorPos() position slightly in order for the recentering to work correctly.
                - User mouse motion is coalesced with SetCursorPos(), so the WM_INPUT positions we see will not necessarily match the position we requested with SetCursorPos().
                - SetCursorPos() outside of the bounds of the focus window appears not to do anything.
                - SetCursorPos() while the cursor is NULL doesn't do anything

                We handle this by creating a safe area within the application window, and when the mouse leaves that safe area, we warp back to the opposite side. Any single motion > 50% of the safe area is assumed to be a warp and ignored.
            */
            bool remote_desktop = (GetSystemMetrics(SM_REMOTESESSION) == TRUE);
            bool virtual_desktop = ((rawmouse->usFlags & MOUSE_VIRTUAL_DESKTOP) != 0);
            bool raw_coordinates = ((rawmouse->usFlags & 0x40) != 0);
            ಪೂರ್ಣಾಂಕ w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            ಪೂರ್ಣಾಂಕ h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            ಪೂರ್ಣಾಂಕ x = raw_coordinates ? dx : (ಪೂರ್ಣಾಂಕ)(((ದಶಮಾಂಶ)dx / 65535.0f) * w);
            ಪೂರ್ಣಾಂಕ y = raw_coordinates ? dy : (ಪೂರ್ಣಾಂಕ)(((ದಶಮಾಂಶ)dy / 65535.0f) * h);
            ಪೂರ್ಣಾಂಕ relX, relY;

            /* Calculate relative motion */
            ಆದರೆ (ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.x == 0 && ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.y == 0) {
                ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.x = x;
                ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.y = y;
            }
            relX = x - ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.x;
            relY = y - ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.y;

            ಆದರೆ (remote_desktop) {
                ಆದರೆ (!windowdata->ಒಳ_title_click && !windowdata->focus_click_pending) {
                    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ wobble;
                    ದಶಮಾಂಶ floatX = (ದಶಮಾಂಶ)x / w;
                    ದಶಮಾಂಶ floatY = (ದಶಮಾಂಶ)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    ಆದರೆ (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        ಪೂರ್ಣಾಂಕ warpX = rect.ಎಡ + ((rect.ಬಲ - rect.ಎಡ) / 2) + wobble;
                        ಪೂರ್ಣಾಂಕ warpY = rect.ತುದಿ + ((rect.bottom - rect.ತುದಿ) / 2);

                        WIN_ಗಣ_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        ಆದರೆ (wobble > 1) {
                            wobble = -1;
                        }
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ MAX_RELATIVE_MOTION = (h / 6);
                        ಆದರೆ (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, mouseID, true, (ದಶಮಾಂಶ)relX, (ದಶಮಾಂಶ)relY);
                        }
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (mouse->pen_mouse_events) {
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗರಿಷ್ಠ_TABLET_RELATIVE_MOTION = 32;
                ಆದರೆ (SDL_abs(relX) > ಗರಿಷ್ಠ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > ಗರಿಷ್ಠ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } ಇಲ್ಲದಿದ್ದರೆ {
                    SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, mouseID, true, (ದಶಮಾಂಶ)relX, (ದಶಮಾಂಶ)relY);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಪೂರ್ಣಾಂಕ screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                ಪೂರ್ಣಾಂಕ screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                ಆದರೆ (!ದತ್ತಾಂಶ->raw_ಒಳಹರಿವು_fake_pen_id) {
                    ದತ್ತಾಂಶ->raw_ಒಳಹರಿವು_fake_pen_id = SDL_ಕೂಡಿಸು_Pen_Device(timestamp, "raw mouse input", ಕಿಟಕಿ, ಖಾಲಿ, (ಶೂನ್ಯ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, ದತ್ತಾಂಶ->raw_ಒಳಹರಿವು_fake_pen_id, ಕಿಟಕಿ, (ದಶಮಾಂಶ)(x + screen_x - ಕಿಟಕಿ->x), (ದಶಮಾಂಶ)(y + screen_y - ಕಿಟಕಿ->y));
            }

            ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.x = x;
            ದತ್ತಾಂಶ->ಕೊನೆಯ_raw_mouse_position.y = y;
        }
    }

    ಆದರೆ (haveButton) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            ಆದರೆ (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool ಕೆಳಕ್ಕೆ = raw_buttons[i].ಕೆಳಕ್ಕೆ;

                ಆದರೆ (button == SDL_BUTTON_ಎಡ) {
                    ಆದರೆ (WIN_ಅದಲುಬದಲು_Buttons(hDevice)) {
                        button = SDL_BUTTON_ಬಲ;
                    }
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (button == SDL_BUTTON_ಬಲ) {
                    ಆದರೆ (WIN_ಅದಲುಬದಲು_Buttons(hDevice)) {
                        button = SDL_BUTTON_ಎಡ;
                    }
                }

                ಆದರೆ (windowdata->focus_click_pending & SDL_BUTTON_ಮುಖವಾಡ(button)) {
                    // Ignore the button click for activation
                    ಆದರೆ (!ಕೆಳಕ್ಕೆ) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_ಮುಖವಾಡ(button);
                        WIN_UpdateClipCursor(ಕಿಟಕಿ);
                    }
                    ಮುಂದುವರಿ;
                }

                SDL_SendMouseButton(timestamp, ಕಿಟಕಿ, mouseID, button, ಕೆಳಕ್ಕೆ);
            }
        }

        ಆದರೆ (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ದತ್ತಾಂಶ;
            ದಶಮಾಂಶ fAmount = (ದಶಮಾಂಶ)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, ಕಿಟಕಿ, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ದತ್ತಾಂಶ;
            ದಶಮಾಂಶ fAmount = (ದಶಮಾಂಶ)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, ಕಿಟಕಿ, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Handle_Raw_Keyboard_ಒಳಹರಿವು(Uint64 timestamp, SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    ಆದರೆ (!ದತ್ತಾಂಶ->raw_keyboard_enabled) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (rawkeyboard->Flags & RI_ಕೀಲಿ_E1) {
        // First key in a Ctrl+{key} sequence
        ದತ್ತಾಂಶ->pending_E1_ಕೀಲಿ_sequence = true;
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ ((rawkeyboard->Flags & RI_ಕೀಲಿ_E0) && rawkeyboard->Make_ಸಂಕೇತ == 0x2A) {
        // 0xE02A make code prefix, ignored
        ಹಿಂತಿರುಗಿ;
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (!rawkeyboard->Make_ಸಂಕೇತ) {
        rawkeyboard->Make_ಸಂಕೇತ = LOWORD(Map_Virtual_ಕೀಲಿ(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_ಗಮ್ಯ_VSC : MAPVK_VK_ಗಮ್ಯ_VSC_EX));
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!rawkeyboard->Make_ಸಂಕೇತ) {
        ಹಿಂತಿರುಗಿ;
    }

    bool ಕೆಳಕ್ಕೆ;
    ಆಯ್ಕೆ (rawkeyboard->ಸಂದೇಶ_4) {
    ಸ್ಥಿತಿ WM_KEYDOWN:
    ಸ್ಥಿತಿ WM_SYSKEYDOWN:
        ಕೆಳಕ್ಕೆ = true;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WM_KEYUP:
    ಸ್ಥಿತಿ WM_SYSKEYUP:
        ಕೆಳಕ್ಕೆ = false;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಕೆಳಕ್ಕೆ = !(rawkeyboard->Flags & RI_ಕೀಲಿ_BREAK);
        ನಿಲ್ಲಿಸು;
    }

    SDL_Scancode ಸಂಕೇತ_2;
    USHORT rawcode = rawkeyboard->Make_ಸಂಕೇತ;
    ಆದರೆ (ದತ್ತಾಂಶ->pending_E1_ಕೀಲಿ_sequence) {
        rawcode |= 0xE100;
        ಆದರೆ (rawkeyboard->Make_ಸಂಕೇತ == 0x45) {
            // Ctrl+NumLock == Pause
            ಸಂಕೇತ_2 = SDL_SCANCODE_PAUSE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            ಸಂಕೇತ_2 = SDL_SCANCODE_UNKNOWN;
        }
        ದತ್ತಾಂಶ->pending_E1_ಕೀಲಿ_sequence = false;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 ಸೂಚ್ಯಂಕ = (Uint8)rawkeyboard->Make_ಸಂಕೇತ;
        ಆದರೆ (rawkeyboard->Flags & RI_ಕೀಲಿ_E0) {
            rawcode |= 0xE000;
            ಸೂಚ್ಯಂಕ |= 0x80;
        }
        ಸಂಕೇತ_2 = windows_scancode_ಕೋಷ್ಟಕ[ಸೂಚ್ಯಂಕ];
    }

    ಆದರೆ (ಕೆಳಕ್ಕೆ) {
        SDL_ಕಿಟಕಿ *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        ಆದರೆ ((!ದತ್ತಾಂಶ->raw_keyboard_flag_inputsink && !focus) || (focus && focus->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ)) {
            ಹಿಂತಿರುಗಿ;
        }
    }

    SDL_Send_Keyboard_ಕೀಲಿ(timestamp, keyboardID, rawcode, ಸಂಕೇತ_2, ಕೆಳಕ್ಕೆ);
}

ಶೂನ್ಯ WIN_Poll_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this, Uint64 poll_ಆರಂಭ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    UINT ಗಾತ್ರ_2, i, ಎಣಿಕೆ_2, ಒಟ್ಟು = 0;
    RAWINPUT *ಒಳಹರಿವು;
    Uint64 poll_ಮುಕ್ತಾಯ;

    ಆದರೆ (ದತ್ತಾಂಶ->rawinput_ಸ್ಥಾನಾಂತರ == 0) {
        BOOL isWow64;

        ದತ್ತಾಂಶ->rawinput_ಸ್ಥಾನಾಂತರ = ಗಾತ್ರ(RAWINPUTHEADER);
        ಆದರೆ (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            ದತ್ತಾಂಶ->rawinput_ಸ್ಥಾನಾಂತರ += 8;
        }
    }

    // Get all available events
    ಒಳಹರಿವು = (RAWINPUT *)ದತ್ತಾಂಶ->rawinput;
    ಗಾಗಿ (;;) {
        ಗಾತ್ರ_2 = ದತ್ತಾಂಶ->rawinput_ಗಾತ್ರ - (UINT)((BYTE *)ಒಳಹರಿವು - ದತ್ತಾಂಶ->rawinput);
        ಎಣಿಕೆ_2 = Get_Raw_ಒಳಹರಿವು_ಬಫರ್(ಒಳಹರಿವು, &ಗಾತ್ರ_2, ಗಾತ್ರ(RAWINPUTHEADER));
        poll_ಮುಕ್ತಾಯ = SDL_GetTicksNS();
        ಆದರೆ (ಎಣಿಕೆ_2 == 0 || ಎಣಿಕೆ_2 == (UINT)-1) {
            ಆದರೆ (!ದತ್ತಾಂಶ->rawinput || (ಎಣಿಕೆ_2 == (UINT)-1 && Get_ಕೊನೆಯ_Error() == ERROR_INSUFFICIENT_ಬಫರ್)) {
                ಸ್ಥಿರಾಂಕ UINT RAWINPUT_ಬಫರ್_ಗಾತ್ರ_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(ದತ್ತಾಂಶ->rawinput, ದತ್ತಾಂಶ->rawinput_ಗಾತ್ರ + RAWINPUT_ಬಫರ್_ಗಾತ್ರ_INCREMENT);
                ಆದರೆ (!rawinput) {
                    ನಿಲ್ಲಿಸು;
                }
                ಒಳಹರಿವು = (RAWINPUT *)(rawinput + ((BYTE *)ಒಳಹರಿವು - ದತ್ತಾಂಶ->rawinput));
                ದತ್ತಾಂಶ->rawinput = rawinput;
                ದತ್ತಾಂಶ->rawinput_ಗಾತ್ರ += RAWINPUT_ಬಫರ್_ಗಾತ್ರ_INCREMENT;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಒಟ್ಟು += ಎಣಿಕೆ_2;

            // Advance input to the end of the buffer
            ಆಗ (ಎಣಿಕೆ_2--) {
                ಒಳಹರಿವು = NEXTRAWINPUTBLOCK(ಒಳಹರಿವು);
            }
        }
    }

    ಆದರೆ (ಒಟ್ಟು > 0) {
        Uint64 delta = poll_ಮುಕ್ತಾಯ - poll_ಆರಂಭ;
        UINT mouse_ಒಟ್ಟು = 0;
        ಗಾಗಿ (i = 0, ಒಳಹರಿವು = (RAWINPUT *)ದತ್ತಾಂಶ->rawinput; i < ಒಟ್ಟು; ++i, ಒಳಹರಿವು = NEXTRAWINPUTBLOCK(ಒಳಹರಿವು)) {
            ಆದರೆ (ಒಳಹರಿವು->ಶೀರ್ಷಿಕೆ.dwType == RIM_TYPEMOUSE) {
                mouse_ಒಟ್ಟು += 1;
            }
        }
        ಪೂರ್ಣಾಂಕ mouse_ಸೂಚ್ಯಂಕ = 0;
        ಗಾಗಿ (i = 0, ಒಳಹರಿವು = (RAWINPUT *)ದತ್ತಾಂಶ->rawinput; i < ಒಟ್ಟು; ++i, ಒಳಹರಿವು = NEXTRAWINPUTBLOCK(ಒಳಹರಿವು)) {
            ಆದರೆ (ಒಳಹರಿವು->ಶೀರ್ಷಿಕೆ.dwType == RIM_TYPEMOUSE) {
                mouse_ಸೂಚ್ಯಂಕ += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)ಒಳಹರಿವು + ದತ್ತಾಂಶ->rawinput_ಸ್ಥಾನಾಂತರ);
                Uint64 ಸಮಯ = poll_ಮುಕ್ತಾಯ - (delta * (mouse_ಒಟ್ಟು - mouse_ಸೂಚ್ಯಂಕ)) / mouse_ಒಟ್ಟು;
                WIN_Handle_Raw_Mouse_ಒಳಹರಿವು(ಸಮಯ, ದತ್ತಾಂಶ, ಒಳಹರಿವು->ಶೀರ್ಷಿಕೆ.hDevice, rawmouse);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಒಳಹರಿವು->ಶೀರ್ಷಿಕೆ.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)ಒಳಹರಿವು + ದತ್ತಾಂಶ->rawinput_ಸ್ಥಾನಾಂತರ);
                WIN_Handle_Raw_Keyboard_ಒಳಹರಿವು(poll_ಮುಕ್ತಾಯ, ದತ್ತಾಂಶ, ಒಳಹರಿವು->ಶೀರ್ಷಿಕೆ.hDevice, rawkeyboard);
            }
        }
    }
    ದತ್ತಾಂಶ->ಕೊನೆಯ_rawinput_poll = poll_ಮುಕ್ತಾಯ;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Device_ID(Uint32 deviceID, Uint32 **list, ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಪೂರ್ಣಾಂಕ new_ಎಣಿಕೆ = (*ಎಣಿಕೆ_2 + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ಎಣಿಕೆ * ಗಾತ್ರ(*new_list));
    ಆದರೆ (!new_list) {
        // Oh well, we'll drop this one
        ಹಿಂತಿರುಗಿ;
    }
    new_list[new_ಎಣಿಕೆ - 1] = deviceID;

    *ಎಣಿಕೆ_2 = new_ಎಣಿಕೆ;
    *list = new_list;
}

ಸ್ಥಿರ bool HasDeviceID(Uint32 deviceID, ಸ್ಥಿರಾಂಕ Uint32 *list, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; ++i) {
        ಆದರೆ (deviceID == list[i]) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಅಕ್ಷರ *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *instance, Uint16 vendor, Uint16 ಗುಣಲಬ್ಧ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *default_name, bool hid_loaded)
{
    ಅಕ್ಷರ *vendor_name = ಖಾಲಿ;
    ಅಕ್ಷರ *ಗುಣಲಬ್ಧ_name = ಖಾಲಿ;
    ಅಕ್ಷರ *name = ಖಾಲಿ;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    ಆದರೆ (hid_loaded) {
        ಅಕ್ಷರ devName[MAX_ಮಾರ್ಗ + 1];
        devName[0] = '\0';
        UINT cap = ಗಾತ್ರ(devName) - 1;
        UINT len = Get_Raw_ಒಳಹರಿವು_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        ಆದರೆ (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, ಖಾಲಿ, OPEN_EXISTING, 0, ಖಾಲಿ);
            ಆದರೆ (hFile != INVALID_HANDLE_ಮೌಲ್ಯ) {
                SDL_HidD_GetManufacturerString(hFile, vend, ಗಾತ್ರ(vend));
                SDL_Hid_D_Get_ಗುಣಲಬ್ಧ_String(hFile, prod, ಗಾತ್ರ(prod));
                CloseHandle(hFile);
            }
        }
    }

    ಆದರೆ (vend[0]) {
        vendor_name = WIN_String_ಗಮ್ಯ_UTF8_W(vend);
    }

    ಆದರೆ (prod[0]) {
        ಗುಣಲಬ್ಧ_name = WIN_String_ಗಮ್ಯ_UTF8_W(prod);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SP_DEVINFO_ದತ್ತಾಂಶ ದತ್ತಾಂಶ;
        SDL_zero(ದತ್ತಾಂಶ);
        ದತ್ತಾಂಶ.cb_ಗಾತ್ರ = ಗಾತ್ರ(ದತ್ತಾಂಶ);
        ಗಾಗಿ (DWORD i = 0;; ++i) {
            ಆದರೆ (!ಸಿದ್ಧತೆ_Di_Enum_Device_Info(devinfo, i, &ದತ್ತಾಂಶ)) {
                ಆದರೆ (Get_ಕೊನೆಯ_Error() == ERROR_NO_ಇನ್ನಷ್ಟು_ವಸ್ತುಗಳು) {
                    ನಿಲ್ಲಿಸು;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಮುಂದುವರಿ;
                }
            }

            ಅಕ್ಷರ DeviceInstanceId[64];
            ಆದರೆ (!ಸಿದ್ಧತೆ_Di_Get_Device_Instance_Id_A(devinfo, &ದತ್ತಾಂಶ, DeviceInstanceId, ಗಾತ್ರ(DeviceInstanceId), ಖಾಲಿ))
                ಮುಂದುವರಿ;

            ಆದರೆ (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD ಗಾತ್ರ_2 = 0;
                ಆದರೆ (ಸಿದ್ಧತೆ_Di_Get_Device_Registry_Property_W(devinfo, &ದತ್ತಾಂಶ, SPDRP_DEVICEDESC, ಖಾಲಿ, (PBYTE)prod, ಗಾತ್ರ(prod), &ಗಾತ್ರ_2)) {
                    // Make sure the device description is null terminated
                    ಗಾತ್ರ_2 /= ಗಾತ್ರ(*prod);
                    ಆದರೆ (ಗಾತ್ರ_2 >= SDL_arraysize(prod)) {
                        // Truncated description...
                        ಗಾತ್ರ_2 = (SDL_arraysize(prod) - 1);
                    }
                    prod[ಗಾತ್ರ_2] = 0;

                    ಆದರೆ (vendor || ಗುಣಲಬ್ಧ) {
                        SDL_asprintf(&ಗುಣಲಬ್ಧ_name, "%S (0x%.4x/0x%.4x)", prod, vendor, ಗುಣಲಬ್ಧ);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಗುಣಲಬ್ಧ_name = WIN_String_ಗಮ್ಯ_UTF8_W(prod);
                    }
                }
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (!ಗುಣಲಬ್ಧ_name && (vendor || ಗುಣಲಬ್ಧ)) {
        SDL_asprintf(&ಗುಣಲಬ್ಧ_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, ಗುಣಲಬ್ಧ);
    }
    name = SDL_CreateDeviceName(vendor, ಗುಣಲಬ್ಧ, vendor_name, ಗುಣಲಬ್ಧ_name, default_name);
    SDL_free(vendor_name);
    SDL_free(ಗುಣಲಬ್ಧ_name);

    ಹಿಂತಿರುಗಿ name;
}

ಶೂನ್ಯ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = ಖಾಲಿ;
    UINT raw_device_ಎಣಿಕೆ = 0;
    ಪೂರ್ಣಾಂಕ old_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *old_keyboards = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ new_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *new_keyboards = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ old_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *old_mice = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ new_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *new_mice = ಖಾಲಿ;

    ಆದರೆ (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->ಆಂತರಿಕ->detect_device_hotplug ||
        _this->ಆಂತರಿಕ->gameinput_context) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ ((Get_Raw_ಒಳಹರಿವು_Device_List(ಖಾಲಿ, &raw_device_ಎಣಿಕೆ, ಗಾತ್ರ(RAWINPUTDEVICELIST)) == -1) || (!raw_device_ಎಣಿಕೆ)) {
        ಹಿಂತಿರುಗಿ; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(ಗಾತ್ರ(RAWINPUTDEVICELIST) * raw_device_ಎಣಿಕೆ);
    ಆದರೆ (!raw_devices) {
        ಹಿಂತಿರುಗಿ; // oh well.
    }

    raw_device_ಎಣಿಕೆ = Get_Raw_ಒಳಹರಿವು_Device_List(raw_devices, &raw_device_ಎಣಿಕೆ, ಗಾತ್ರ(RAWINPUTDEVICELIST));
    ಆದರೆ (raw_device_ಎಣಿಕೆ == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ; // oh well.
    }

    HDEVINFO devinfo = ಸಿದ್ಧತೆ_Di_Get_Class_Devs_A(ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ಎಣಿಕೆ);
    old_mice = SDL_GetMice(&old_mouse_ಎಣಿಕೆ);

    ಗಾಗಿ (UINT i = 0; i < raw_device_ಎಣಿಕೆ; i++) {
        RID_DEVICE_INFO rdi;
        ಅಕ್ಷರ devName[MAX_ಮಾರ್ಗ] = { 0 };
        UINT rdi_ಗಾತ್ರ = ಗಾತ್ರ(rdi);
        UINT name_ಗಾತ್ರ = SDL_arraysize(devName);
        ಪೂರ್ಣಾಂಕ vendor = 0, ಗುಣಲಬ್ಧ = 0;
        DWORD dwType = raw_devices[i].dwType;
        ಅಕ್ಷರ *instance, *ptr, *name;

        ಆದರೆ (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            ಮುಂದುವರಿ;
        }

        rdi.cb_ಗಾತ್ರ = ಗಾತ್ರ(rdi);
        ಆದರೆ (Get_Raw_ಒಳಹರಿವು_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_ಗಾತ್ರ) == ((UINT)-1) ||
            Get_Raw_ಒಳಹರಿವು_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_ಗಾತ್ರ) == ((UINT)-1)) {
            ಮುಂದುವರಿ;
        }

        // Extract the device instance
        instance = devName;
        ಆಗ (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        ಗಾಗಿ (ptr = instance; *ptr; ++ptr) {
            ಆದರೆ (*ptr == '#') {
                *ptr = '\\';
            }
            ಆದರೆ (*ptr == '{') {
                ಆದರೆ (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                ನಿಲ್ಲಿಸು;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &ಗುಣಲಬ್ಧ);

        ಆಯ್ಕೆ (dwType) {
        ಸ್ಥಿತಿ RIM_TYPEKEYBOARD:
            ಆದರೆ (SDL_IsKeyboard((Uint16)vendor, (Uint16)ಗುಣಲಬ್ಧ, rdi.keyboard.dw_ಸಂಖ್ಯೆ_ದ_ಕೀಲಿಗಳು_ಒಟ್ಟು)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                ಕೂಡಿಸು_Device_ID(keyboardID, &new_keyboards, &new_keyboard_ಎಣಿಕೆ);
                ಆದರೆ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ಎಣಿಕೆ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ಗುಣಲಬ್ಧ, "Keyboard", hid_loaded);
                    SDL_ಕೂಡಿಸು_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ RIM_TYPEMOUSE:
            ಆದರೆ (SDL_IsMouse((Uint16)vendor, (Uint16)ಗುಣಲಬ್ಧ)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                ಕೂಡಿಸು_Device_ID(mouseID, &new_mice, &new_mouse_ಎಣಿಕೆ);
                ಆದರೆ (!HasDeviceID(mouseID, old_mice, old_mouse_ಎಣಿಕೆ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ಗುಣಲಬ್ಧ, "Mouse", hid_loaded);
                    SDL_ಕೂಡಿಸು_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = old_keyboard_ಎಣಿಕೆ; i--;) {
        ಆದರೆ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ಎಣಿಕೆ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = old_mouse_ಎಣಿಕೆ; i--;) {
        ಆದರೆ (!HasDeviceID(old_mice[i], new_mice, new_mouse_ಎಣಿಕೆ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    ಸಿದ್ಧತೆ_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ಸ್ಥಿರ bool Skip_Alt_Gr_ಎಡ_Control(WPARAM wParam, LPARAM lParam)
{
    ಆದರೆ (wParam != VK_CONTROL) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Is this an extended key (i.e. right key)?
    ಆದರೆ (lParam & 0x01000000) {
        ಹಿಂತಿರುಗಿ false;
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    ಸಂದೇಶ_3 ಮುಂದಿನ_ಸಂದೇಶ;
    DWORD ಸಂದೇಶ_ಸಮಯ = Get_ಸಂದೇಶ_ಸಮಯ();
    ಆದರೆ (Peek_ಸಂದೇಶ(&ಮುಂದಿನ_ಸಂದೇಶ, ಖಾಲಿ, 0, 0, PM_NOREMOVE)) {
        ಆದರೆ (ಮುಂದಿನ_ಸಂದೇಶ.ಸಂದೇಶ == WM_KEYDOWN ||
            ಮುಂದಿನ_ಸಂದೇಶ.ಸಂದೇಶ == WM_SYSKEYDOWN) {
            ಆದರೆ (ಮುಂದಿನ_ಸಂದೇಶ.wParam == VK_MENU && (ಮುಂದಿನ_ಸಂದೇಶ.lParam & 0x01000000) && ಮುಂದಿನ_ಸಂದೇಶ.ಸಮಯ == ಸಂದೇಶ_ಸಮಯ) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                ಹಿಂತಿರುಗಿ true;
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool Dispatch_Modal_Loop_ಸಂದೇಶ_Hook(HWND *hwnd, UINT *ಸಂದೇಶ_2, WPARAM *wParam, LPARAM *lParam)
{
    ಸಂದೇಶ_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.ಸಂದೇಶ = *ಸಂದೇಶ_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    ಆದರೆ (g_Windows_ಸಂದೇಶ_Hook(g_Windows_ಸಂದೇಶ_Hook_ದತ್ತಾಂಶ, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *ಸಂದೇಶ_2 = dummy.ಸಂದೇಶ;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

LRESULT CALLBACK WIN_ಕಿಟಕಿ_Proc(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM lParam)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    LRESULT return_ಸಂಕೇತ = -1;

    // Get the window data for the window
    ದತ್ತಾಂಶ = WIN_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_From_HWND(hwnd);
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        // Fallback
        ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)GetProp(hwnd, ಪಠ್ಯ_2("SDL_WindowData"));
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ Call_ಕಿಟಕಿ_Proc(Def_ಕಿಟಕಿ_Proc, hwnd, ಸಂದೇಶ_2, wParam, lParam);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WMMSG_DEBUG
    {
        ಅಕ್ಷರ ಸಂದೇಶ[1024];
        ಆದರೆ (ಸಂದೇಶ_2 > MAX_WMMSG) {
            SDL_snprintf(ಸಂದೇಶ, ಗಾತ್ರ(ಸಂದೇಶ), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, ಸಂದೇಶ_2, wParam, lParam);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_snprintf(ಸಂದೇಶ, ಗಾತ್ರ(ಸಂದೇಶ), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[ಸಂದೇಶ_2], wParam, lParam);
        }
        OutputDebugStringA(ಸಂದೇಶ);
    }
#ಆದರೆ_ಅಂತ್ಯ // WMMSG_DEBUG


    ಆದರೆ (g_Windows_ಸಂದೇಶ_Hook && ದತ್ತಾಂಶ->ಒಳ_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        ಆದರೆ (!Dispatch_Modal_Loop_ಸಂದೇಶ_Hook(&hwnd, &ಸಂದೇಶ_2, &wParam, &lParam)) {
            ಹಿಂತಿರುಗಿ 0;
        }
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (WIN_HandleIMEMessage(hwnd, ಸಂದೇಶ_2, wParam, &lParam, ದತ್ತಾಂಶ->videodata)) {
        ಹಿಂತಿರುಗಿ 0;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆಯ್ಕೆ (ಸಂದೇಶ_2) {

    ಸ್ಥಿತಿ WM_SHOWWINDOW:
    {
        ಆದರೆ (wParam) {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HIDDEN, 0, 0);
        }
    } ನಿಲ್ಲಿಸು;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಸ್ಥಿತಿ WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        ದತ್ತಾಂಶ->postpone_clipcursor = true;
        ದತ್ತಾಂಶ->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        ಬಿಂದು_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(ದತ್ತಾಂಶ->ಕಿಟಕಿ, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_NCUAHDRAWCAPTION:
    ಸ್ಥಿತಿ WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
            return_ಸಂಕೇತ = 0;
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ಸ್ಥಿರಾಂಕ DWORD ಸಂದೇಶ_Pos = Get_ಸಂದೇಶ_Pos();
        ಬಿಂದು_2 pos = { GET_X_LPARAM(ಸಂದೇಶ_Pos), GET_Y_LPARAM(ಸಂದೇಶ_Pos) };
        WIN_UpdateFocus(ದತ್ತಾಂಶ->ಕಿಟಕಿ, !!LOWORD(wParam), &pos);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_MOUSEACTIVATE:
    {
        ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_ಕಿಟಕಿ *ಪೋಷಕ = ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಪೋಷಕ;
        ಆಗ (ಪೋಷಕ) {
            ಆದರೆ ((ಪೋಷಕ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) &&
                (ಪೋಷಕ->flags & SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ)) {
                ಹಿಂತಿರುಗಿ MA_NOACTIVATE;
            }
            ಪೋಷಕ = ಪೋಷಕ->ಪೋಷಕ;
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ಸ್ಥಿರಾಂಕ DWORD ಸಂದೇಶ_Pos = Get_ಸಂದೇಶ_Pos();
        ಬಿಂದು_2 pos = { GET_X_LPARAM(ಸಂದೇಶ_Pos), GET_Y_LPARAM(ಸಂದೇಶ_Pos) };
        WIN_UpdateFocus(ದತ್ತಾಂಶ->ಕಿಟಕಿ, true, &pos);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_KILLFOCUS:
    ಸ್ಥಿತಿ WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ಸ್ಥಿರಾಂಕ DWORD ಸಂದೇಶ_Pos = Get_ಸಂದೇಶ_Pos();
        ಬಿಂದು_2 pos = { GET_X_LPARAM(ಸಂದೇಶ_Pos), GET_Y_LPARAM(ಸಂದೇಶ_Pos) };
        WIN_UpdateFocus(ದತ್ತಾಂಶ->ಕಿಟಕಿ, false, &pos);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ಸ್ಥಿರಾಂಕ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ಸೂಚಕ_ಒಳಹರಿವು_TYPE ಸೂಚಕ_type = PT_ಸೂಚಕ;
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type) {
            ನಿಲ್ಲಿಸು;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type(pointerid, &ಸೂಚಕ_type)) {
            ನಿಲ್ಲಿಸು;  // oh well.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸೂಚಕ_type != PT_PEN) {
            ನಿಲ್ಲಿಸು;  // we only care about pens here.
        }

        ಶೂನ್ಯ *hpointer = (ಶೂನ್ಯ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ಸ್ಥಿರಾಂಕ SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle(hpointer);
        ಆದರೆ (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ದತ್ತಾಂಶ->ಕಿಟಕಿ, true, true);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_ದೂರ | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.ಅಂಕೆ_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_ಕೂಡಿಸು_Pen_Device(WIN_GetEventTimestamp(), ಖಾಲಿ, ದತ್ತಾಂಶ->ಕಿಟಕಿ, &info, hpointer, true);
        }
        return_ಸಂಕೇತ = 0;
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_POINTERCAPTURECHANGED:
    ಸ್ಥಿತಿ WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ಸ್ಥಿರಾಂಕ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ಸೂಚಕ_ಒಳಹರಿವು_TYPE ಸೂಚಕ_type = PT_ಸೂಚಕ;
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type) {
            ನಿಲ್ಲಿಸು;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type(pointerid, &ಸೂಚಕ_type)) {
            ನಿಲ್ಲಿಸು;  // oh well.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸೂಚಕ_type != PT_PEN) {
            ನಿಲ್ಲಿಸು;  // we only care about pens here.
        }

        ಶೂನ್ಯ *hpointer = (ಶೂನ್ಯ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ಸ್ಥಿರಾಂಕ SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle(hpointer);
        ಆದರೆ (pen == 0) {
            ನಿಲ್ಲಿಸು;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        ಆದರೆ ((ಸಂದೇಶ_2 == WM_POINTERCAPTURECHANGED) || !IS_ಸೂಚಕ_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ದತ್ತಾಂಶ->ಕಿಟಕಿ, false, false);
        }
        return_ಸಂಕೇತ = 0;
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_POINTERDOWN:
    ಸ್ಥಿತಿ WM_POINTERUP:
    ಸ್ಥಿತಿ WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ಸ್ಥಿರಾಂಕ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ಸೂಚಕ_ಒಳಹರಿವು_TYPE ಸೂಚಕ_type = PT_ಸೂಚಕ;
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type || !ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Type(pointerid, &ಸೂಚಕ_type)) {
            ನಿಲ್ಲಿಸು;  // oh well.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಸಂದೇಶ_2 == WM_POINTERUPDATE) && (ಸೂಚಕ_type == PT_MOUSE)) {
            ದತ್ತಾಂಶ->ಕೊನೆಯ_ಸೂಚಕ_update = lParam;
            return_ಸಂಕೇತ = 0;
            ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸೂಚಕ_type != PT_PEN) {
            ನಿಲ್ಲಿಸು; // we only care about pens here.
        }

        ಶೂನ್ಯ *hpointer = (ಶೂನ್ಯ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ಸ್ಥಿರಾಂಕ SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle(hpointer);
        ಸೂಚಕ_PEN_INFO pen_info;
        ಆದರೆ (pen == 0) {
            ನಿಲ್ಲಿಸು;  // not a pen, or not a pen we already knew about.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Pen_Info || !ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Pen_Info(pointerid, &pen_info)) {
            ನಿಲ್ಲಿಸು;  // oh well.
        }

        ಸ್ಥಿರಾಂಕ Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

        ಸ್ಥಿರಾಂಕ bool istouching = IS_ಸೂಚಕ_INCONTACT_WPARAM(wParam) && IS_ಸೂಚಕ_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        ಆದರೆ (!istouching) {
            SDL_SendPenTouch(timestamp, pen, ಕಿಟಕಿ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ಸ್ಥಿರಾಂಕ ಸೂಚಕ_INFO *ಸೂಚಕ_info = &pen_info.ಸೂಚಕ_Info;
        RECT tablet_bounds, tablet_mapping;
        ದಶಮಾಂಶ fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Device_Rects || !ದತ್ತಾಂಶ->videodata->Get_ಸೂಚಕ_Device_Rects(ಸೂಚಕ_info->ಮೂಲ_Device, &tablet_bounds, &tablet_mapping)) {
            ಬಿಂದು_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_ಗಮ್ಯ_Client(ದತ್ತಾಂಶ->hwnd, &position);
            fx = (ದಶಮಾಂಶ) position.x;
            fy = (ದಶಮಾಂಶ) position.y;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ ix, iy;
            SDL_Get_ಕಿಟಕಿ_Position(ಕಿಟಕಿ, &ix, &iy);
            ಸ್ಥಿರಾಂಕ SDL_FPoint ಕಿಟಕಿ_pos = { (ದಶಮಾಂಶ) ix, (ದಶಮಾಂಶ) iy };

            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ facX = ಸೂಚಕ_info->ptHimetricLocationRaw.x / (ದಶಮಾಂಶ) (tablet_bounds.ಬಲ );
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ facY = ಸೂಚಕ_info->ptHimetricLocationRaw.y / (ದಶಮಾಂಶ) (tablet_bounds.bottom);

            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ w = tablet_mapping.ಬಲ  - tablet_mapping.ಎಡ;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ h = tablet_mapping.bottom - tablet_mapping.ತುದಿ;

            fx = (tablet_mapping.ಎಡ + (facX * w)) - ಕಿಟಕಿ_pos.x;
            fy = (tablet_mapping.ತುದಿ  + (facY * h)) - ಕಿಟಕಿ_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, ಕಿಟಕಿ, fx, fy);
        SDL_SendPenButton(timestamp, pen, ಕಿಟಕಿ, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, ಕಿಟಕಿ, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        ಆದರೆ (pen_info.pen_ಮುಖವಾಡ & PEN_ಮುಖವಾಡ_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, ಕಿಟಕಿ, SDL_PEN_AXIS_PRESSURE, ((ದಶಮಾಂಶ) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        ಆದರೆ (pen_info.pen_ಮುಖವಾಡ & PEN_ಮುಖವಾಡ_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, ಕಿಟಕಿ, SDL_PEN_AXIS_ROTATION, ((ದಶಮಾಂಶ) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        ಆದರೆ (pen_info.pen_ಮುಖವಾಡ & PEN_ಮುಖವಾಡ_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, ಕಿಟಕಿ, SDL_PEN_AXIS_XTILT, ((ದಶಮಾಂಶ) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        ಆದರೆ (pen_info.pen_ಮುಖವಾಡ & PEN_ಮುಖವಾಡ_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, ಕಿಟಕಿ, SDL_PEN_AXIS_YTILT, ((ದಶಮಾಂಶ) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        ಆದರೆ (istouching) {
            SDL_SendPenTouch(timestamp, pen, ಕಿಟಕಿ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_ಸಂಕೇತ = 0;
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_MOUSEMOVE:
    {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
            bool wish_clip_cursor = (
                ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ | SDL_ಕಿಟಕಿ_MOUSE_GRABBED) ||
                (ಕಿಟಕಿ->mouse_rect.w > 0 && ಕಿಟಕಿ->mouse_rect.h > 0)
            );
            ಆದರೆ (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                ದತ್ತಾಂಶ->clipcursor_queued = true;
            }
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_ಗಾತ್ರ = ಗಾತ್ರ(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = ದತ್ತಾಂಶ->hwnd;

            ಆದರೆ (TrackMouseEvent(&trackMouseEvent)) {
                ದತ್ತಾಂಶ->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ);
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            ಆದರೆ (Get_Mouse_ಸಂದೇಶ_ಮೂಲ((ULONG)Get_ಸಂದೇಶ_Extra_Info()) == SDL_MOUSE_EVENT_ಮೂಲ_MOUSE &&
                lParam != ದತ್ತಾಂಶ->ಕೊನೆಯ_ಸೂಚಕ_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)GET_X_LPARAM(lParam), (ದಶಮಾಂಶ)GET_Y_LPARAM(lParam));
            }
        }

    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_LBUTTONUP:
    ಸ್ಥಿತಿ WM_RBUTTONUP:
    ಸ್ಥಿತಿ WM_MBUTTONUP:
    ಸ್ಥಿತಿ WM_XBUTTONUP:
    ಸ್ಥಿತಿ WM_LBUTTONDOWN:
    ಸ್ಥಿತಿ WM_LBUTTONDBLCLK:
    ಸ್ಥಿತಿ WM_RBUTTONDOWN:
    ಸ್ಥಿತಿ WM_RBUTTONDBLCLK:
    ಸ್ಥಿತಿ WM_MBUTTONDOWN:
    ಸ್ಥಿತಿ WM_MBUTTONDBLCLK:
    ಸ್ಥಿತಿ WM_XBUTTONDOWN:
    ಸ್ಥಿತಿ WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->raw_mouse_enabled) {
            ಆದರೆ (Get_Mouse_ಸಂದೇಶ_ಮೂಲ((ULONG)Get_ಸಂದೇಶ_Extra_Info()) == SDL_MOUSE_EVENT_ಮೂಲ_MOUSE &&
                lParam != ದತ್ತಾಂಶ->ಕೊನೆಯ_ಸೂಚಕ_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, ದತ್ತಾಂಶ, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } ನಿಲ್ಲಿಸು;

#ಆದರೆ 0   // We handle raw input all at once instead of using a syscall for each mouse event
    ಸ್ಥಿತಿ WM_ಒಳಹರಿವು:
    {
        HRAWINPUT h_Raw_ಒಳಹರಿವು = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT ಗಾತ್ರ_2 = ಗಾತ್ರ(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ != SDL_GetKeyboardFocus()) {
            ನಿಲ್ಲಿಸು;
        }

        Get_Raw_ಒಳಹರಿವು_ದತ್ತಾಂಶ(h_Raw_ಒಳಹರಿವು, RID_ಒಳಹರಿವು, &inp, &ಗಾತ್ರ_2, ಗಾತ್ರ(RAWINPUTHEADER));
        ಆದರೆ (inp.ಶೀರ್ಷಿಕೆ.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_ಒಳಹರಿವು(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ, inp.ಶೀರ್ಷಿಕೆ.hDevice, &inp.ದತ್ತಾಂಶ.mouse);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (inp.ಶೀರ್ಷಿಕೆ.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_ಒಳಹರಿವು(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ, inp.ಶೀರ್ಷಿಕೆ.hDevice, &inp.ದತ್ತಾಂಶ.keyboard);
        }
    } ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

    ಸ್ಥಿತಿ WM_MOUSEWHEEL:
    ಸ್ಥಿತಿ WM_MOUSEHWHEEL:
    {
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->raw_mouse_enabled) {
            ಗಿಡ್ಡ amount = GET_WHEEL_DELTA_WPARAM(wParam);
            ದಶಮಾಂಶ fAmount = (ದಶಮಾಂಶ)amount / WHEEL_DELTA;
            ಆದರೆ (ಸಂದೇಶ_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
            }
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_MOUSELEAVE:
        ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
            ಆದರೆ (SDL_GetMouseFocus() == ದತ್ತಾಂಶ->ಕಿಟಕಿ && !SDL_GetMouse()->relative_ಬಹುಲಕ && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_ಸಂದೇಶ_Pos();
                ಬಿಂದು_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_ಗಮ್ಯ_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                ಆದರೆ (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)cursorPos.x, (ದಶಮಾಂಶ)cursorPos.y);
                } ಇಲ್ಲದಿದ್ದರೆ {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    ಆದರೆ (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_TOUCH_MOUSEID, false, (ದಶಮಾಂಶ)cursorPos.x, (ದಶಮಾಂಶ)cursorPos.y);
                    } ಇಲ್ಲದಿದ್ದರೆ { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)cursorPos.x, (ದಶಮಾಂಶ)cursorPos.y);
                    }
                }
            }

            ಆದರೆ (!SDL_GetMouse()->relative_ಬಹುಲಕ) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        ದತ್ತಾಂಶ->mouse_tracked = false;

        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಸ್ಥಿತಿ WM_KEYDOWN:
    ಸ್ಥಿತಿ WM_SYSKEYDOWN:
    {
        ಆದರೆ (Skip_Alt_Gr_ಎಡ_Control(wParam, lParam)) {
            return_ಸಂಕೇತ = 0;
            ನಿಲ್ಲಿಸು;
        }

        bool virtual_ಕೀಲಿ = false;
        Uint16 rawcode = 0;
        SDL_Scancode ಸಂಕೇತ_2 = Windows_ಪರಿಶೀಲನೆ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScan_ಸಂಕೇತ(lParam, wParam, &rawcode, &virtual_ಕೀಲಿ);

        // Detect relevant keyboard shortcuts
        ಆದರೆ (ಸಂಕೇತ_2 == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            ಆದರೆ (Should_Generate_ಕಿಟಕಿ_Close_On_Alt_F4()) {
                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
            }
        }

        ಆದರೆ (virtual_ಕೀಲಿ || !ದತ್ತಾಂಶ->videodata->raw_keyboard_enabled || ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ) {
            SDL_Send_Keyboard_ಕೀಲಿ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ಸಂಕೇತ_2, true);
        }
    }

        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_SYSKEYUP:
    ಸ್ಥಿತಿ WM_KEYUP:
    {
        ಆದರೆ (Skip_Alt_Gr_ಎಡ_Control(wParam, lParam)) {
            return_ಸಂಕೇತ = 0;
            ನಿಲ್ಲಿಸು;
        }

        bool virtual_ಕೀಲಿ = false;
        Uint16 rawcode = 0;
        SDL_Scancode ಸಂಕೇತ_2 = Windows_ಪರಿಶೀಲನೆ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScan_ಸಂಕೇತ(lParam, wParam, &rawcode, &virtual_ಕೀಲಿ);
        ಸ್ಥಿರಾಂಕ bool *keyboardState = SDL_GetKeyboardState(ಖಾಲಿ);

        ಆದರೆ (virtual_ಕೀಲಿ || !ದತ್ತಾಂಶ->videodata->raw_keyboard_enabled || ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ) {
            ಆದರೆ (ಸಂಕೇತ_2 == SDL_SCANCODE_PRINTSCREEN && !keyboardState[ಸಂಕೇತ_2]) {
                SDL_Send_Keyboard_ಕೀಲಿ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ಸಂಕೇತ_2, true);
            }
            SDL_Send_Keyboard_ಕೀಲಿ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ಸಂಕೇತ_2, false);
        }
    }
        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_UNICHAR:
        ಆದರೆ (wParam == UNICODE_NOCHAR) {
            return_ಸಂಕೇತ = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
                ಅಕ್ಷರ ಪಠ್ಯ[5];
                ಅಕ್ಷರ *ಕೊನೆ = SDL_UCS4_ಗಮ್ಯ_UTF8((Uint32)wParam, ಪಠ್ಯ);
                *ಕೊನೆ = '\0';
                SDL_Send_Keyboard_ಪಠ್ಯ(ಪಠ್ಯ);
            }
            return_ಸಂಕೇತ = 0;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_CHAR:
        ಆದರೆ (SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            ಆದರೆ (IS_ಮೇಲಿನ_SURROGATE(wParam)) {
                ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate = (WCHAR)wParam;
            } ಇಲ್ಲದಿದ್ದರೆ {
                WCHAR utf16[3];

                utf16[0] = ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate ? ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate : (WCHAR)wParam;
                utf16[1] = ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                ಅಕ್ಷರ utf8[5];
                ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = WIN_Wide_Char_ಗಮ್ಯ_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, ಗಾತ್ರ(utf8), ಖಾಲಿ, ಖಾಲಿ);
                ಆದರೆ (ಫಲಿತಾಂಶ > 0) {
                    SDL_Send_Keyboard_ಪಠ್ಯ(utf8);
                }
                ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate = L'\0';
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->ಮೇಲಿನ_surrogate = L'\0';
        }

        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WM_INPUTLANGCHANGE
    ಸ್ಥಿತಿ WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_ಸಂಕೇತ = 1;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ // WM_INPUTLANGCHANGE

    ಸ್ಥಿತಿ WM_NCLBUTTONDOWN:
    {
        ದತ್ತಾಂಶ->ಒಳ_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        ಆದರೆ (Send_ಸಂದೇಶ(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            ಬಿಂದು_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_ಗಮ್ಯ_Client(hwnd, &cursorPos);
            Post_ಸಂದೇಶ(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_CAPTURECHANGED:
    {
        ದತ್ತಾಂಶ->ಒಳ_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ);
    } ನಿಲ್ಲಿಸು;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WM_GETMINMAXINFO
    ಸ್ಥಿತಿ WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT ಗಾತ್ರ_2;
        ಪೂರ್ಣಾಂಕ x, y;
        ಪೂರ್ಣಾಂಕ w, h;
        ಪೂರ್ಣಾಂಕ min_w, min_h;
        ಪೂರ್ಣಾಂಕ max_w, max_h;
        BOOL constrain_max_ಗಾತ್ರ;

        // If this is an expected size change, allow it
        ಆದರೆ (ದತ್ತಾಂಶ->expected_resize) {
            ನಿಲ್ಲಿಸು;
        }

        // Get the current position of our window
        Get_ಕಿಟಕಿ_Rect(hwnd, &ಗಾತ್ರ_2);
        x = ಗಾತ್ರ_2.ಎಡ;
        y = ಗಾತ್ರ_2.ತುದಿ;

        // Calculate current size of our window
        SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, &w, &h);
        SDL_Get_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, &min_w, &min_h);
        SDL_Get_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        ಆದರೆ (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_ಗಾತ್ರ = TRUE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            constrain_max_ಗಾತ್ರ = FALSE;
        }

        ಆದರೆ (!(SDL_Get_ಕಿಟಕಿ_Flags(ದತ್ತಾಂಶ->ಕಿಟಕಿ) & SDL_ಕಿಟಕಿ_BORDERLESS) && !SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
            ಗಾತ್ರ_2.ತುದಿ = 0;
            ಗಾತ್ರ_2.ಎಡ = 0;
            ಗಾತ್ರ_2.bottom = h;
            ಗಾತ್ರ_2.ಬಲ = w;
            WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(hwnd, &ಗಾತ್ರ_2, 0);
            w = ಗಾತ್ರ_2.ಬಲ - ಗಾತ್ರ_2.ಎಡ;
            h = ಗಾತ್ರ_2.bottom - ಗಾತ್ರ_2.ತುದಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#ಆದರೆ_ಅಂತ್ಯ
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        ಆದರೆ (SDL_Get_ಕಿಟಕಿ_Flags(ದತ್ತಾಂಶ->ಕಿಟಕಿ) & SDL_ಕಿಟಕಿ_RESIZABLE) {
            ಆದರೆ (SDL_Get_ಕಿಟಕಿ_Flags(ದತ್ತಾಂಶ->ಕಿಟಕಿ) & SDL_ಕಿಟಕಿ_BORDERLESS) {
                ಪೂರ್ಣಾಂಕ screenW = GetSystemMetrics(SM_CXSCREEN);
                ಪೂರ್ಣಾಂಕ screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_ಗಾತ್ರ.x = SDL_max(w, screenW);
                info->pt_Max_ಗಾತ್ರ.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_ಗಾತ್ರ.x = (LONG)w + min_w;
            info->pt_Min_Track_ಗಾತ್ರ.y = (LONG)h + min_h;
            ಆದರೆ (constrain_max_ಗಾತ್ರ) {
                info->pt_Max_Track_ಗಾತ್ರ.x = (LONG)w + max_w;
                info->pt_Max_Track_ಗಾತ್ರ.y = (LONG)h + max_h;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            info->pt_Max_ಗಾತ್ರ.x = w;
            info->pt_Max_ಗಾತ್ರ.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_ಗಾತ್ರ.x = w;
            info->pt_Min_Track_ಗಾತ್ರ.y = h;
            info->pt_Max_Track_ಗಾತ್ರ.x = w;
            info->pt_Max_Track_ಗಾತ್ರ.y = h;
        }
    }
        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ // WM_GETMINMAXINFO

    ಸ್ಥಿತಿ WM_WINDOWPOSCHANGING:

        ಆದರೆ (ದತ್ತಾಂಶ->expected_resize) {
            return_ಸಂಕೇತ = 0;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಒಳ_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            ಆದರೆ (ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಅಗಲ == windowpos->cx && ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಎತ್ತರ == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಅಗಲ = windowpos->cx;
            ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಎತ್ತರ = windowpos->cy;

            return_ಸಂಕೇತ = 0;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_WINDOWPOSCHANGED:
    {
        SDL_ಕಿಟಕಿ *win;
        ಸ್ಥಿರಾಂಕ SDL_DisplayID original_displayID = ದತ್ತಾಂಶ->ಕಿಟಕಿ->displayID;
        ಸ್ಥಿರಾಂಕ WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        ಪೂರ್ಣಾಂಕ x, y;
        ಪೂರ್ಣಾಂಕ w, h;

        ಆದರೆ (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        ಆದರೆ (iconic) {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (zoomed) {
            ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
            }
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MAXIMIZED, 0, 0);
            ದತ್ತಾಂಶ->force_ws_maximizebox = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED)) {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
                ದತ್ತಾಂಶ->force_ws_maximizebox = false;
                WIN_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_GetVideoDevice(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, !!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE));
            }
        }

        ಆದರೆ (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        ಆದರೆ (iconic) {
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->initializing) {
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->disable_move_ಗಾತ್ರ_events) {
            ಆದರೆ (GetClientRect(hwnd, &rect) && WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
                Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT) &rect);
                Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.ಎಡ;
                y = rect.ತುದಿ;

                SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, x, y, &x, &y);
                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            ಆದರೆ (GetClientRect(hwnd, &rect) && WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
                w = rect.ಬಲ;
                h = rect.bottom;

                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(ದತ್ತಾಂಶ->ಕಿಟಕಿ);

        // Update the window display position
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_ಕಿಟಕಿ_ICCProfile(ದತ್ತಾಂಶ->ಕಿಟಕಿ, true);
        }

        // Update the position of any child windows
        ಗಾಗಿ (win = ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; win; win = win->ಮುಂದಿನ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(win) && !(win->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
                WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_ENTERSIZEMOVE:
    ಸ್ಥಿತಿ WM_ENTERMENULOOP:
    {
        ಆದರೆ (g_Windows_ಸಂದೇಶ_Hook) {
            ಆದರೆ (!Dispatch_Modal_Loop_ಸಂದೇಶ_Hook(&hwnd, &ಸಂದೇಶ_2, &wParam, &lParam)) {
                ಹಿಂತಿರುಗಿ 0;
            }
        }

        ++ದತ್ತಾಂಶ->ಒಳ_modal_loop;
        ಆದರೆ (ದತ್ತಾಂಶ->ಒಳ_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_ಕಿಟಕಿ_Rect(ದತ್ತಾಂಶ->hwnd, &rect);
            ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಅಗಲ = rect.ಬಲ - rect.ಎಡ;
            ದತ್ತಾಂಶ->ಕೊನೆಯ_modal_ಎತ್ತರ = rect.bottom - rect.ತುದಿ;

            ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಎಡ = ದತ್ತಾಂಶ->ಕಿಟಕಿ->x;
            ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಬಲ = ದತ್ತಾಂಶ->ಕಿಟಕಿ->x + ದತ್ತಾಂಶ->ಕಿಟಕಿ->w;
            ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ತುದಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ->y;
            ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.bottom = ದತ್ತಾಂಶ->ಕಿಟಕಿ->y + ದತ್ತಾಂಶ->ಕಿಟಕಿ->h;

            ಗಣ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, ಖಾಲಿ);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_TIMER:
    {
        ಆದರೆ (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_ಕಿಟಕಿ_ಜೀವಂತ_Resize_Update(ದತ್ತಾಂಶ->ಕಿಟಕಿ);

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ಆದರೆ 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            ಆದರೆ (ದತ್ತಾಂಶ->videodata->DwmFlush) {
                ದತ್ತಾಂಶ->videodata->DwmFlush();
            }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ 0;
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_EXITSIZEMOVE:
    ಸ್ಥಿತಿ WM_EXITMENULOOP:
    {
        --ದತ್ತಾಂಶ->ಒಳ_modal_loop;
        ಆದರೆ (ದತ್ತಾಂಶ->ಒಳ_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_SIZING:
        {
            WPARAM ಅಂಚು = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool ಬೀಗ_aspect_ಅನುಪಾತ = (ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect == ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            ದಶಮಾಂಶ new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect <= 0 && ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect <= 0) {
                ನಿಲ್ಲಿಸು;
            }

            // unadjust the dragRect from the window rect to the client rect
            ಗಣ_Rect_ಖಾಲಿಗಳು(&rc);
            ಆದರೆ (!Adjust_ಕಿಟಕಿ_Rect_Ex(&rc, Get_ಕಿಟಕಿ_Style(hwnd), GetMenu(hwnd) != ಖಾಲಿ, Get_ಕಿಟಕಿ_Ex_Style(hwnd))) {
                ನಿಲ್ಲಿಸು;
            }

            clientDragRect.ಎಡ -= rc.ಎಡ;
            clientDragRect.ತುದಿ -= rc.ತುದಿ;
            clientDragRect.ಬಲ -= rc.ಬಲ;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ಬಲ - clientDragRect.ಎಡ;
            h = clientDragRect.bottom - clientDragRect.ತುದಿ;
            new_aspect = w / (ದಶಮಾಂಶ)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            ಆದರೆ (ಬೀಗ_aspect_ಅನುಪಾತ) {
                ಆಯ್ಕೆ (ಅಂಚು) {
                ಸ್ಥಿತಿ WMSZ_ಎಡ:
                ಸ್ಥಿತಿ WMSZ_ಬಲ:
                    h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(w / ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect);
                    ನಿಲ್ಲಿಸು;
                ಪೂರ್ವನಿಯೋಜಿತ:
                    // resizing via corners or top or bottom
                    w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(h * ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect);
                    ನಿಲ್ಲಿಸು;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆಯ್ಕೆ (ಅಂಚು) {
                ಸ್ಥಿತಿ WMSZ_ಎಡ:
                ಸ್ಥಿತಿ WMSZ_ಬಲ:
                    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect > 0.0f && new_aspect > ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect) {
                        w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(h * ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect > 0.0f && new_aspect < ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect) {
                        w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(h * ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect);
                    }
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ WMSZ_ತುದಿ:
                ಸ್ಥಿತಿ WMSZ_BOTTOM:
                    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect > 0.0f && new_aspect < ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect) {
                        h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(w / ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect > 0.0f && new_aspect > ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect) {
                        h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(w / ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect);
                    }
                    ನಿಲ್ಲಿಸು;

                ಪೂರ್ವನಿಯೋಜಿತ:
                    // resizing via corners
                    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect > 0.0f && new_aspect > ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect) {
                        w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(h * ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect > 0.0f && new_aspect < ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect) {
                        h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(w / ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect);
                    }
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆಯ್ಕೆ (ಅಂಚು) {
            ಸ್ಥಿತಿ WMSZ_ಎಡ:
                clientDragRect.ಎಡ = clientDragRect.ಬಲ - w;
                ಆದರೆ (ಬೀಗ_aspect_ಅನುಪಾತ) {
                    clientDragRect.ತುದಿ = (ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.bottom + ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ತುದಿ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.ತುದಿ;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_BOTTOMLEFT:
                clientDragRect.ಎಡ = clientDragRect.ಬಲ - w;
                clientDragRect.bottom = h + clientDragRect.ತುದಿ;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_ಬಲ:
                clientDragRect.ಬಲ = w + clientDragRect.ಎಡ;
                ಆದರೆ (ಬೀಗ_aspect_ಅನುಪಾತ) {
                    clientDragRect.ತುದಿ = (ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.bottom + ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ತುದಿ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.ತುದಿ;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_TOPRIGHT:
                clientDragRect.ಬಲ = w + clientDragRect.ಎಡ;
                clientDragRect.ತುದಿ = clientDragRect.bottom - h;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_ತುದಿ:
                ಆದರೆ (ಬೀಗ_aspect_ಅನುಪಾತ) {
                    clientDragRect.ಎಡ = (ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಬಲ + ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಎಡ - w) / 2;
                }
                clientDragRect.ಬಲ = w + clientDragRect.ಎಡ;
                clientDragRect.ತುದಿ = clientDragRect.bottom - h;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_TOPLEFT:
                clientDragRect.ಎಡ = clientDragRect.ಬಲ - w;
                clientDragRect.ತುದಿ = clientDragRect.bottom - h;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_BOTTOM:
                ಆದರೆ (ಬೀಗ_aspect_ಅನುಪಾತ) {
                    clientDragRect.ಎಡ = (ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಬಲ + ದತ್ತಾಂಶ->initial_ಗಾತ್ರ_rect.ಎಡ - w) / 2;
                }
                clientDragRect.ಬಲ = w + clientDragRect.ಎಡ;
                clientDragRect.bottom = h + clientDragRect.ತುದಿ;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ WMSZ_BOTTOMRIGHT:
                clientDragRect.ಬಲ = w + clientDragRect.ಎಡ;
                clientDragRect.bottom = h + clientDragRect.ತುದಿ;
                ನಿಲ್ಲಿಸು;
            }

            // convert the client rect to a window rect
            ಆದರೆ (!Adjust_ಕಿಟಕಿ_Rect_Ex(&clientDragRect, Get_ಕಿಟಕಿ_Style(hwnd), GetMenu(hwnd) != ಖಾಲಿ, Get_ಕಿಟಕಿ_Ex_Style(hwnd))) {
                ನಿಲ್ಲಿಸು;
            }

            *dragRect = clientDragRect;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        ಆದರೆ (hittest == HTCLIENT) {
            ಗಣ_Cursor(SDL_cursor);
            return_ಸಂಕೇತ = TRUE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!g_ಕಿಟಕಿ_ಚೌಕಟ್ಟು_Usable_While_Cursor_Hidden && !SDL_cursor) {
            ಗಣ_Cursor(ಖಾಲಿ);
            return_ಸಂಕೇತ = TRUE;
        }
    } ನಿಲ್ಲಿಸು;

        // We were occluded, refresh our display
    ಸ್ಥಿತಿ WM_PAINT:
    {
        RECT rect;
        ಆದರೆ (GetUpdateRect(hwnd, &rect, FALSE)) {
            ಸ್ಥಿರಾಂಕ LONG style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            ಆದರೆ (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                ಕೊನೆ_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, ಖಾಲಿ);
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
        }
    }
        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;

        // We'll do our own drawing, prevent flicker
    ಸ್ಥಿತಿ WM_ERASEBKGND:
        ಆದರೆ (Should_Clear_ಕಿಟಕಿ_On_Erase_Background(ದತ್ತಾಂಶ)) {
            RECT client_rect;
            HBRUSH brush;
            ದತ್ತಾಂಶ->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        ಹಿಂತಿರುಗಿ 1;

    ಸ್ಥಿತಿ WM_SYSCOMMAND:
    {
        ಆದರೆ (!g_WindowsEnableMenuMnemonics) {
            ಆದರೆ ((wParam & 0xFFF0) == SC_KEYMENU) {
                ಹಿಂತಿರುಗಿ 0;
            }
        }

#ಆದರೆ defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        ಆದರೆ ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            ಆದರೆ (SDL_GetVideoDevice()->suspend_screensaver) {
                ಹಿಂತಿರುಗಿ 0;
            }
        }
#ಆದರೆ_ಅಂತ್ಯ // System has screensaver support
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_CLOSE:
    {
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
    }
        return_ಸಂಕೇತ = 0;
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_TOUCH:
        ಆದರೆ (ದತ್ತಾಂಶ->videodata->Get_Touch_ಒಳಹರಿವು_Info && ದತ್ತಾಂಶ->videodata->Close_Touch_ಒಳಹರಿವು_Handle) {
            UINT i, ಅಂಕೆ_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, ಅಂಕೆ_inputs, &isstack);
            ಆದರೆ (inputs && ದತ್ತಾಂಶ->videodata->Get_Touch_ಒಳಹರಿವು_Info((HTOUCHINPUT)lParam, ಅಂಕೆ_inputs, inputs, ಗಾತ್ರ(TOUCHINPUT))) {
                RECT rect;
                ದಶಮಾಂಶ x, y;

                ಆದರೆ (!GetClientRect(hwnd, &rect) || !WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
                    ಆದರೆ (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    ನಿಲ್ಲಿಸು;
                }
                Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT)&rect);
                Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.ತುದಿ *= 100;
                rect.ಎಡ *= 100;
                rect.bottom *= 100;
                rect.ಬಲ *= 100;

                ಗಾಗಿ (i = 0; i < ಅಂಕೆ_inputs; ++i) {
                    PTOUCHINPUT ಒಳಹರಿವು = &inputs[i];
                    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ w = (rect.ಬಲ - rect.ಎಡ);
                    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ h = (rect.bottom - rect.ತುದಿ);

                    ಸ್ಥಿರಾಂಕ SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)ಒಳಹರಿವು->h_ಮೂಲ);
                    ಸ್ಥಿರಾಂಕ SDL_FingerID fingerId = (ಒಳಹರಿವು->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    ಆದರೆ (SDL_ಕೂಡಿಸು_Touch(touchId, SDL_TOUCH_DEVICE_ನೇರ, (ಒಳಹರಿವು->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        ಮುಂದುವರಿ;
                    }

                    // Get the normalized coordinates for the window
                    ಆದರೆ (w <= 1) {
                        x = 0.5f;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        x = (ದಶಮಾಂಶ)(ಒಳಹರಿವು->x - rect.ಎಡ) / (w - 1);
                    }
                    ಆದರೆ (h <= 1) {
                        y = 0.5f;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        y = (ದಶಮಾಂಶ)(ಒಳಹರಿವು->y - rect.ತುದಿ) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    ಆದರೆ (ಒಳಹರಿವು->dwFlags & TOUCHEVENTF_ಕೆಳಕ್ಕೆ) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, 1.0f);
                    }
                    ಆದರೆ (ಒಳಹರಿವು->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, ದತ್ತಾಂಶ->ಕಿಟಕಿ, x, y, 1.0f);
                    }
                    ಆದರೆ (ಒಳಹರಿವು->dwFlags & TOUCHEVENTF_ಮೇಲೆ) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            ದತ್ತಾಂಶ->videodata->Close_Touch_ಒಳಹರಿವು_Handle((HTOUCHINPUT)lParam);
            ಹಿಂತಿರುಗಿ 0;
        }
        ನಿಲ್ಲಿಸು;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_TPCSHRD_H

    ಸ್ಥಿತಿ WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        ಹಿಂತಿರುಗಿ TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#ಆದರೆ_ಅಂತ್ಯ // HAVE_TPCSHRD_H

    ಸ್ಥಿತಿ WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT ಎಣಿಕೆ_2 = DragQueryFile(drop, 0xFFFFFFFF, ಖಾಲಿ, 0);
        ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2; ++i) {
            UINT ಗಾತ್ರ_2 = DragQueryFile(drop, i, ಖಾಲಿ, 0) + 1;
            LPTSTR ಬಫರ್_2 = (LPTSTR)SDL_malloc(ಗಾತ್ರ(TCHAR) * ಗಾತ್ರ_2);
            ಆದರೆ (ಬಫರ್_2) {
                ಆದರೆ (DragQueryFile(drop, i, ಬಫರ್_2, ಗಾತ್ರ_2)) {
                    ಅಕ್ಷರ *file = WIN_String_ಗಮ್ಯ_UTF8(ಬಫರ್_2);
                    SDL_SendDropFile(ದತ್ತಾಂಶ->ಕಿಟಕಿ, ಖಾಲಿ, file);
                    SDL_free(file);
                }
                SDL_free(ಬಫರ್_2);
            }
        }
        SDL_SendDropComplete(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
        Drag_ಮುಕ್ತಾಯ(drop);
        ಹಿಂತಿರುಗಿ 0;
    }

    ಸ್ಥಿತಿ WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_NCCALCSIZE:
    {
        SDL_ಕಿಟಕಿ_Flags ಕಿಟಕಿ_flags = ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags;
        ಆದರೆ (wParam == TRUE && (ಕಿಟಕಿ_flags & SDL_ಕಿಟಕಿ_BORDERLESS) && !(ಕಿಟಕಿ_flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            ಆದರೆ (Get_ಕಿಟಕಿ_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_ಕಿಟಕಿ(hwnd, MONITOR_DEFAULTTONULL);
                ಆದರೆ (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ಸ್ಥಿರಾಂಕ ಬಿಂದು_2 pt = { ದತ್ತಾಂಶ->ಕಿಟಕಿ->windowed.x, ದತ್ತಾಂಶ->ಕಿಟಕಿ->windowed.y };
                    hMonitor = Monitor_From_ಬಿಂದು(pt, MONITOR_DEFAULTTONEAREST);
                }
                ಆದರೆ (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_ಗಾತ್ರ = ಗಾತ್ರ(info);
                    ಆದರೆ (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(ಕಿಟಕಿ_flags & SDL_ಕಿಟಕಿ_RESIZABLE) && !ದತ್ತಾಂಶ->force_ws_maximizebox) {
                ಪೂರ್ಣಾಂಕ w, h;
                ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending) {
                    w = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.w;
                    h = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.h;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    w = ದತ್ತಾಂಶ->ಕಿಟಕಿ->floating.w;
                    h = ದತ್ತಾಂಶ->ಕಿಟಕಿ->floating.h;
                }
                params->rgrc[0].ಬಲ = params->rgrc[0].ಎಡ + w;
                params->rgrc[0].bottom = params->rgrc[0].ತುದಿ + h;
            }
            ಹಿಂತಿರುಗಿ 0;
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_NCHITTEST:
    {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TOOLTIP) {
            ಹಿಂತಿರುಗಿ HTTRANSPARENT;
        }

        ಆದರೆ (ಕಿಟಕಿ->ದೊರಕಿತು_test) {
            ಬಿಂದು_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            ಆದರೆ (Screen_ಗಮ್ಯ_Client(hwnd, &winpoint)) {
                SDL_ಬಿಂದು ಬಿಂದು;
                SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ rc;
                ಬಿಂದು.x = winpoint.x;
                ಬಿಂದು.y = winpoint.y;
                rc = ಕಿಟಕಿ->ದೊರಕಿತು_test(ಕಿಟಕಿ, &ಬಿಂದು, ಕಿಟಕಿ->ದೊರಕಿತು_test_ದತ್ತಾಂಶ);
                ಆಯ್ಕೆ (rc) {
#ವ್ಯಾಖ್ಯಾನಿಸು POST_ದೊರಕಿತು_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ದೊರಕಿತು_TEST, 0, 0); \
        ಹಿಂತಿರುಗಿ ret;                                                        \
    }
                ಸ್ಥಿತಿ SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(ಖಾಲಿ, ಖಾಲಿ);
                    ಆದರೆ (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
                        ಹಿಂತಿರುಗಿ HTCLIENT;
                    }

                    POST_ದೊರಕಿತು_TEST(HTCAPTION);
                }
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_ದೊರಕಿತು_TEST(HTTOPLEFT);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ:
                    POST_ದೊರಕಿತು_TEST(HTTOP);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_ದೊರಕಿತು_TEST(HTTOPRIGHT);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ:
                    POST_ದೊರಕಿತು_TEST(HTRIGHT);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_ದೊರಕಿತು_TEST(HTBOTTOMRIGHT);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM:
                    POST_ದೊರಕಿತು_TEST(HTBOTTOM);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_ದೊರಕಿತು_TEST(HTBOTTOMLEFT);
                ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ:
                    POST_ದೊರಕಿತು_TEST(HTLEFT);
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು POST_ದೊರಕಿತು_TEST
                ಸ್ಥಿತಿ SDL_HITTEST_ಸಾಮಾನ್ಯ:
                    ಹಿಂತಿರುಗಿ HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        ಆದರೆ (ದತ್ತಾಂಶ->videodata->Get_Dpi_For_ಕಿಟಕಿ && ದತ್ತಾಂಶ->videodata->Adjust_ಕಿಟಕಿ_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಮುಂದಿನ_DPI = (ಪೂರ್ಣಾಂಕ)wParam;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ prevDPI = (ಪೂರ್ಣಾಂಕ)ದತ್ತಾಂಶ->videodata->Get_Dpi_For_ಕಿಟಕಿ(hwnd);
            ಗಾತ್ರ_4 *ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು = (ಗಾತ್ರ_4 *)lParam;

            ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_w, ಚೌಕಟ್ಟು_h;
            ಪೂರ್ಣಾಂಕ query_client_w_win, query_client_h_win;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, ಮುಂದಿನ_DPI, ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cx, ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cy);
#ಆದರೆ_ಅಂತ್ಯ

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) && !SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
                    WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                ಚೌಕಟ್ಟು_w = -rect.ಎಡ + rect.ಬಲ;
                ಚೌಕಟ್ಟು_h = -rect.ತುದಿ + rect.bottom;

                query_client_w_win = ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cx - ಚೌಕಟ್ಟು_w;
                query_client_h_win = ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cy - ಚೌಕಟ್ಟು_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ಬಲ = query_client_w_win;
                rect.bottom = query_client_h_win;

                ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) && !SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
                    WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(hwnd, &rect, ಮುಂದಿನ_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cx = rect.ಬಲ - rect.ಎಡ;
                ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cy = rect.bottom - rect.ತುದಿ;
            }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cx, ಗಾತ್ರ_ಒಳ_ಹೊರಹೋಗು->cy);
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ TRUE;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ WM_DPICHANGED:
        // Windows 8.1+
        {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ newDPI = HIWORD(wParam);
            RECT *ಸ್ಥಿರಾಂಕ suggestedRect = (RECT *)lParam;
            ಪೂರ್ಣಾಂಕ w, h;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->ಎಡ, suggestedRect->ತುದಿ, suggestedRect->ಬಲ - suggestedRect->ಎಡ, suggestedRect->bottom - suggestedRect->ತುದಿ);
#ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ (ದತ್ತಾಂಶ->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ಬಲ = ದತ್ತಾಂಶ->ಕಿಟಕಿ->w;
                rect.bottom = ದತ್ತಾಂಶ->ಕಿಟಕಿ->h;

                ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS)) {
                    WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.ಬಲ - rect.ಎಡ;
                h = rect.bottom - rect.ತುದಿ;
            }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    ದತ್ತಾಂಶ->ಕಿಟಕಿ->w, ದತ್ತಾಂಶ->ಕಿಟಕಿ->h,
                    suggestedRect->ಎಡ, suggestedRect->ತುದಿ, w, h);
#ಆದರೆ_ಅಂತ್ಯ

            ದತ್ತಾಂಶ->expected_resize = true;
            ಗಣ_ಕಿಟಕಿ_Pos(hwnd,
                         ಖಾಲಿ,
                         suggestedRect->ಎಡ,
                         suggestedRect->ತುದಿ,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            ದತ್ತಾಂಶ->expected_resize = false;
            ಹಿಂತಿರುಗಿ 0;
        }

    ಸ್ಥಿತಿ WM_SETTINGCHANGE:
        ಆದರೆ (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_ಗಣ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_ಬಹುಲಕ_For_HWND(hwnd);
        }
        ಆದರೆ (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        ಆದರೆ (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        ನಿಲ್ಲಿಸು;
#ಇಲ್ಲದಿದ್ದರೆ
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    ಸ್ಥಿತಿ WM_ಗಾತ್ರ:
    {
        RECT rect;
        ಪೂರ್ಣಾಂಕ w, h;

        ಆದರೆ (GetClientRect(hwnd, &rect) && WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
            w = rect.ಬಲ;
            h = rect.bottom;
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, w, h);
        }
    } ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (ಸಂದೇಶ_2 && ಸಂದೇಶ_2 == ದತ್ತಾಂಶ->videodata->WM_TASKBAR_BUTTON_CREATED) {
        ದತ್ತಾಂಶ->taskbar_button_created = true;
        WIN_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ(SDL_GetVideoDevice(), ದತ್ತಾಂಶ->ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    // If there's a window proc, assume it's going to handle messages
    ಆದರೆ (ದತ್ತಾಂಶ->wndproc) {
        ಹಿಂತಿರುಗಿ Call_ಕಿಟಕಿ_Proc(ದತ್ತಾಂಶ->wndproc, hwnd, ಸಂದೇಶ_2, wParam, lParam);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (return_ಸಂಕೇತ >= 0) {
        ಹಿಂತಿರುಗಿ return_ಸಂಕೇತ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ Call_ಕಿಟಕಿ_Proc(Def_ಕಿಟಕಿ_Proc, hwnd, ಸಂದೇಶ_2, wParam, lParam);
    }
}

ಪೂರ್ಣಾಂಕ WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    ಆದರೆ (g_Windows_Enable_ಸಂದೇಶ_Loop) {
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_ಗಮ್ಯ_MS(timeoutNS);
        ret = ಸಂದೇಶ_Wait_For_ಅಪವರ್ತ್ಯ_Objects(0, ಖಾಲಿ, FALSE, timeout, QS_ALLINPUT);
        ಆದರೆ (ret == WAIT_OBJECT_0) {
            ಹಿಂತಿರುಗಿ 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ 0;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        // MsgWaitForMultipleObjects is desktop-only.
        ಸಂದೇಶ_3 ಸಂದೇಶ_2;
        BOOL ಸಂದೇಶ_ಫಲಿತಾಂಶ;
        UINT_PTR timer_id = 0;
        ಆದರೆ (timeoutNS > 0) {
            timer_id = ಗಣ_Timer(ಖಾಲಿ, 0, (UINT)SDL_NS_ಗಮ್ಯ_MS(timeoutNS), ಖಾಲಿ);
            ಸಂದೇಶ_ಫಲಿತಾಂಶ = Get_ಸಂದೇಶ(&ಸಂದೇಶ_2, 0, 0, 0);
            KillTimer(ಖಾಲಿ, timer_id);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (timeoutNS == 0) {
            ಸಂದೇಶ_ಫಲಿತಾಂಶ = Peek_ಸಂದೇಶ(&ಸಂದೇಶ_2, ಖಾಲಿ, 0, 0, PM_REMOVE);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸಂದೇಶ_ಫಲಿತಾಂಶ = Get_ಸಂದೇಶ(&ಸಂದೇಶ_2, 0, 0, 0);
        }
        ಆದರೆ (ಸಂದೇಶ_ಫಲಿತಾಂಶ) {
            ಆದರೆ (ಸಂದೇಶ_2.ಸಂದೇಶ == WM_TIMER && !ಸಂದೇಶ_2.hwnd && ಸಂದೇಶ_2.wParam == timer_id) {
                ಹಿಂತಿರುಗಿ 0;
            }
            ಆದರೆ (g_Windows_ಸಂದೇಶ_Hook) {
                ಆದರೆ (!g_Windows_ಸಂದೇಶ_Hook(g_Windows_ಸಂದೇಶ_Hook_ದತ್ತಾಂಶ, &ಸಂದೇಶ_2)) {
                    ಹಿಂತಿರುಗಿ 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ಸಂದೇಶ(&ಸಂದೇಶ_2);
            Dispatch_ಸಂದೇಶ(&ಸಂದೇಶ_2);
            ಹಿಂತಿರುಗಿ 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ 0;
        }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Fail the wait so the caller falls back to polling
        ಹಿಂತಿರುಗಿ -1;
    }
}

ಶೂನ್ಯ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Post_ಸಂದೇಶ(ದತ್ತಾಂಶ->hwnd, ದತ್ತಾಂಶ->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
ಶೂನ್ಯ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    ಸಂದೇಶ_3 ಸಂದೇಶ_2;

    ಆದರೆ (g_Windows_Enable_ಸಂದೇಶ_Loop) {
        SDL_processing_messages = true;

        ಆಗ (Peek_ಸಂದೇಶ(&ಸಂದೇಶ_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_ಗಣ_ಸಂದೇಶ_Tick(ಸಂದೇಶ_2.ಸಮಯ);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ಸಂದೇಶ(&ಸಂದೇಶ_2);
            Dispatch_ಸಂದೇಶ(&ಸಂದೇಶ_2);
        }

        SDL_processing_messages = false;
    }
}

ಶೂನ್ಯ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    ಸಂದೇಶ_3 ಸಂದೇಶ_2;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ಸೂಚನೆ warning(ತಳ್ಳು)
#ಸೂಚನೆ warning(disable : 28159)
#ಆದರೆ_ಅಂತ್ಯ
    DWORD ಕೊನೆ_ticks = Get_Tick_ಎಣಿಕೆ() + 1;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning(ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ new_messages = 0;

    ಆದರೆ (_this->ಆಂತರಿಕ->gameinput_context) {
        WIN_Update_Game_ಒಳಹರಿವು(_this);
    }

    ಆದರೆ (g_Windows_Enable_ಸಂದೇಶ_Loop) {
        SDL_processing_messages = true;

        ಆಗ (Peek_ಸಂದೇಶ(&ಸಂದೇಶ_2, ಖಾಲಿ, 0, 0, PM_REMOVE)) {
            ಆದರೆ (g_Windows_ಸಂದೇಶ_Hook) {
                ಆದರೆ (!g_Windows_ಸಂದೇಶ_Hook(g_Windows_ಸಂದೇಶ_Hook_ದತ್ತಾಂಶ, &ಸಂದೇಶ_2)) {
                    ಮುಂದುವರಿ;
                }
            }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            ಆದರೆ (ಸಂದೇಶ_2.ಸಂದೇಶ == WM_MOUSEMOVE && SDL_ಕೊನೆಯ_warp_ಸಮಯ) {
                ಆದರೆ (!SDL_TICKS_PASSED(ಸಂದೇಶ_2.ಸಮಯ, (SDL_ಕೊನೆಯ_warp_ಸಮಯ + 1))) {
                    ಮುಂದುವರಿ;
                }

                // This mouse message happened after the warp
                SDL_ಕೊನೆಯ_warp_ಸಮಯ = 0;
            }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_ಗಣ_ಸಂದೇಶ_Tick(ಸಂದೇಶ_2.ಸಮಯ);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ಸಂದೇಶ(&ಸಂದೇಶ_2);
            Dispatch_ಸಂದೇಶ(&ಸಂದೇಶ_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            ಆದರೆ (SDL_TICKS_PASSED(ಸಂದೇಶ_2.ಸಮಯ, ಕೊನೆ_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ MAX_NEW_MESSAGES = 3;
                ++new_messages;
                ಆದರೆ (new_messages > MAX_NEW_MESSAGES) {
                    ನಿಲ್ಲಿಸು;
                }
            }
        }

        SDL_processing_messages = false;
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ಸ್ಥಿರಾಂಕ bool *keystate = SDL_GetKeyboardState(ಖಾಲಿ);
    ಆದರೆ (keystate[SDL_SCANCODE_LSHIFT] && !(Get_ಕೀಲಿ_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    ಆದರೆ (keystate[SDL_SCANCODE_RSHIFT] && !(Get_ಕೀಲಿ_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_ಕಿಟಕಿ *focus_ಕಿಟಕಿ = SDL_GetKeyboardFocus();
    ಆದರೆ (!focus_ಕಿಟಕಿ || !(focus_ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED)) {
        ಆದರೆ (keystate[SDL_SCANCODE_LGUI] && !(Get_ಕೀಲಿ_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        ಆದರೆ (keystate[SDL_SCANCODE_RGUI] && !(Get_ಕೀಲಿ_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    ಆದರೆ (_this) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = _this->windows;
        ಆಗ (ಕಿಟಕಿ) {
            bool refresh_clipcursor = false;
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
            ಆದರೆ (ದತ್ತಾಂಶ) {
                refresh_clipcursor = ದತ್ತಾಂಶ->clipcursor_queued;
                ದತ್ತಾಂಶ->clipcursor_queued = false;    // Must be cleared unconditionally.
                ದತ್ತಾಂಶ->postpone_clipcursor = false;  // Must be cleared unconditionally.
                                                    // Must happen before UpdateClipCursor.
                                                    // Although its occurrence currently
                                                    // always coincides with the queuing of
                                                    // clipcursor, it is logically distinct
                                                    // and this coincidence might no longer
                                                    // be true in the future.
                                                    // Ergo this placement concordantly
                                                    // conveys its unconditionality
                                                    // vis-a-vis the queuing of clipcursor.
            }
            ಆದರೆ (refresh_clipcursor) {
                WIN_UpdateClipCursor(ಕಿಟಕಿ);
            }
            ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_ಕಿಟಕಿ = SDL_GetKeyboardFocus();
    ಆದರೆ (focus_ಕಿಟಕಿ && (focus_ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = focus_ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಆದರೆ (!ದತ್ತಾಂಶ->mouse_tracked) {
            ಬಿಂದು_2 cursorPos;

            ಆದರೆ (GetCursorPos(&cursorPos) && Screen_ಗಮ್ಯ_Client(ದತ್ತಾಂಶ->hwnd, &cursorPos)) {
                bool ಅದಲುಬದಲು_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID, false, (ದಶಮಾಂಶ)cursorPos.x, (ದಶಮಾಂಶ)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID,
                                    !ಅದಲುಬದಲು_Buttons ? SDL_BUTTON_ಎಡ : SDL_BUTTON_ಬಲ,
                                    (Get_Async_ಕೀಲಿ_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID,
                                    !ಅದಲುಬದಲು_Buttons ? SDL_BUTTON_ಬಲ : SDL_BUTTON_ಎಡ,
                                    (Get_Async_ಕೀಲಿ_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID,
                                    SDL_BUTTON_ಮಧ್ಯ,
                                    (Get_Async_ಕೀಲಿ_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_ಕೀಲಿ_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ದತ್ತಾಂಶ->ಕಿಟಕಿ, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_ಕೀಲಿ_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_GDK
    GDK_Dispatch_Task_ಸರತಿ();
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ app_registered = 0;
LPTSTR SDL_Appname = ಖಾಲಿ;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = ಖಾಲಿ;

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Clean_ರಿಜಿಸ್ಟರ್_App(WNDCLASSEX wcex)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    ಆದರೆ (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#ಆದರೆ_ಅಂತ್ಯ
    SDL_free(SDL_Appname);
    SDL_Appname = ಖಾಲಿ;
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಸ್ಥಿರ BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (ಶೂನ್ಯ)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = ತುಂಬು_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    ಹಿಂತಿರುಗಿ FALSE;
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_ರಿಜಿಸ್ಟರ್_App(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, Uint32 style, ಶೂನ್ಯ *hInst)
{
    WNDCLASSEX wcex;
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;
#ಆದರೆ_ಅಂತ್ಯ

    // Only do this once...
    ಆದರೆ (app_registered) {
        ++app_registered;
        ಹಿಂತಿರುಗಿ true;
    }
    SDL_assert(!SDL_Appname);
    ಆದರೆ (!name) {
        name = "SDL_app";
#ಆದರೆ defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#ಆದರೆ_ಅಂತ್ಯ
    }
    SDL_Appname = WIN_UTF8_ಗಮ್ಯ_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(ಖಾಲಿ);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_ಗಾತ್ರ = ಗಾತ್ರ(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_ಕಿಟಕಿ_Proc;
    wcex.hInstance = SDL_Instance;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    ಆದರೆ (hint && *hint) {
        wcex.hIcon = ತುಂಬು_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        ಆದರೆ (hint && *hint) {
            wcex.hIconSm = ತುಂಬು_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_ಹೆಸರುಗಳು(SDL_Instance, RT_ಗುಂಪು_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಆದರೆ (!ರಿಜಿಸ್ಟರ್_Class_Ex(&wcex)) {
        WIN_Clean_ರಿಜಿಸ್ಟರ್_App(wcex);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't register application class");
    }

    app_registered = 1;
    ಹಿಂತಿರುಗಿ true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
ಶೂನ್ಯ SDL_UnregisterApp(ಶೂನ್ಯ)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    ಆದರೆ (!app_registered) {
        ಹಿಂತಿರುಗಿ;
    }
    --app_registered;
    ಆದರೆ (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = ಖಾಲಿ;
        wcex.hIconSm = ಖಾಲಿ;
        // Check for any registered window classes.
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ಆದರೆ (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#ಆದರೆ_ಅಂತ್ಯ
        WIN_Clean_ರಿಜಿಸ್ಟರ್_App(wcex);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
