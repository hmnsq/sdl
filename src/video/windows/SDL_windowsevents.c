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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/scancodes_windows.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../main/SDL_main_callbacks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_hid.h"

// Dropfile support
#ਅਨ੍ਤਰ੍ਭਾਵ <shellapi.h>

// Device names
#ਅਨ੍ਤਰ੍ਭਾਵ <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#ਅਨ੍ਤਰ੍ਭਾਵ <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_TPCSHRD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <tpcshrd.h>
#ਜੇ_ਅੰਤ // HAVE_TPCSHRD_H

#ਜੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WMMSG_DEBUG
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WMMSG_DEBUG
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "wmmsg.h"
#ਜੇ_ਅੰਤ

#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ਅਨ੍ਤਰ੍ਭਾਵ <shobjidl.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_GDK
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/gdk/SDL_gdk.h"
#ਜੇ_ਅੰਤ

// #define HIGHDPI_DEBUG

// Undocumented window messages
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_NCUAHDRAWCAPTION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_NCUAHDRAWCAPTION 0xAE
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_NCUAHDRAWFRAME
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_NCUAHDRAWFRAME 0xAF
#ਜੇ_ਅੰਤ

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_XBUTTONDOWN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_XBUTTONDOWN 0x020B
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_XBUTTONUP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_XBUTTONUP 0x020C
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GET_XBUTTON_WPARAM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_XBUTTON_WPARAM(w) (HIWORD(w))
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_ਨਿਵੇਸ਼
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_ਨਿਵੇਸ਼ 0x00ff
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_TOUCH
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_TOUCH 0x0240
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_MOUSEHWHEEL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_MOUSEHWHEEL 0x020E
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ RI_MOUSE_HWHEEL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RI_MOUSE_HWHEEL 0x0800
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERUPDATE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERUPDATE 0x0245
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERDOWN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERDOWN 0x0246
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERUP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERUP 0x0247
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERENTER
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERENTER 0x0249
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERLEAVE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERLEAVE 0x024A
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POINTERCAPTURECHANGED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POINTERCAPTURECHANGED 0x024C
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_UNICHAR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_UNICHAR 0x0109
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_DPICHANGED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_DPICHANGED 0x02E0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_GETDPISCALEDSIZE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_GETDPISCALEDSIZE 0x02E4
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TOUCHEVENTF_PEN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHEVENTF_PEN 0x0040
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MAPVK_VK_ਮੰਜ਼ਿਲ_VSC_EX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAPVK_VK_ਮੰਜ਼ਿਲ_VSC_EX 4
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WC_ERR_INVALID_CHARS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WC_ERR_INVALID_CHARS 0x00000080
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IS_ਉੱਚਾ_SURROGATE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_ਉੱਚਾ_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USER_TIMER_MINIMUM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_TIMER_MINIMUM 0x0000000A
#ਜੇ_ਅੰਤ

// Used to compare Windows message timestamps
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN64
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool SDL_processing_messages;
ਸਥਿਰ DWORD ਸੁਨੇਹਾ_tick;
ਸਥਿਰ Uint64 timestamp_ਵਿੱਥ;

ਸਥਿਰ ਖਾਲੀ WIN_ਸੈੱਟ_ਸੁਨੇਹਾ_Tick(DWORD tick)
{
    ਸੁਨੇਹਾ_tick = tick;
}

ਸਥਿਰ Uint64 WIN_GetEventTimestamp(ਖਾਲੀ)
{
    ਅਚਲ Uint64 TIMESTAMP_WRAP_ਵਿੱਥ = SDL_MS_ਮੰਜ਼ਿਲ_NS(0x100000000LL);
    Uint64 timestamp, now;

    ਜੇ (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        ਵਾਪਸ 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_ਮੰਜ਼ਿਲ_NS(ਸੁਨੇਹਾ_tick);
    timestamp += timestamp_ਵਿੱਥ;
    ਜੇ (!timestamp_ਵਿੱਥ) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_ਵਿੱਥ = (now - timestamp);
        timestamp = now;
    } ਨਹੀਂਤਾਂ ਜੇ ((Sint64)(now - timestamp - TIMESTAMP_WRAP_ਵਿੱਥ) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_ਵਿੱਥ += TIMESTAMP_WRAP_ਵਿੱਥ;
        timestamp += TIMESTAMP_WRAP_ਵਿੱਥ;
    } ਨਹੀਂਤਾਂ ਜੇ (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_ਵਿੱਥ -= (timestamp - now);
        timestamp = now;
    }
    ਵਾਪਸ timestamp;
}

// A message hook called before TranslateMessage()
ਸਥਿਰ SDL_Windows_ਸੁਨੇਹਾ_Hook g_Windows_ਸੁਨੇਹਾ_Hook = ਨਿਰਾ;
ਸਥਿਰ ਖਾਲੀ *g_Windows_ਸੁਨੇਹਾ_Hook_ਅੰਕੜੇ = ਨਿਰਾ;

ਖਾਲੀ SDL_ਸੈੱਟ_Windows_ਸੁਨੇਹਾ_Hook(SDL_Windows_ਸੁਨੇਹਾ_Hook callback, ਖਾਲੀ *userdata)
{
    g_Windows_ਸੁਨੇਹਾ_Hook = callback;
    g_Windows_ਸੁਨੇਹਾ_Hook_ਅੰਕੜੇ = userdata;
}

ਸਥਿਰ SDL_Scancode Windows_ਜਾਂਚ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScan_ਕੋਡ(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_ਕੁੰਜੀ)
{
    SDL_Scancode ਕੋਡ;
    Uint8 ਸੂਚਕਾਂਕ;
    Uint16 ਕੁੰਜੀ_Flags = HIWORD(lParam);
    Uint16 ਜਾਂਚ_ਕੋਡ = LOBYTE(ਕੁੰਜੀ_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    ਜਾਂਚ_ਕੋਡ &= ~0x80;

    *virtual_ਕੁੰਜੀ = (ਜਾਂਚ_ਕੋਡ == 0);

    ਜੇ (ਜਾਂਚ_ਕੋਡ != 0) {
        ਜੇ ((ਕੁੰਜੀ_Flags & KF_EXTENDED) == KF_EXTENDED) {
            ਜਾਂਚ_ਕੋਡ = MAKEWORD(ਜਾਂਚ_ਕੋਡ, 0xe0);
        } ਨਹੀਂਤਾਂ ਜੇ (ਜਾਂਚ_ਕੋਡ == 0x45) {
            // Pause
            ਜਾਂਚ_ਕੋਡ = 0xe046;
        }
    } ਨਹੀਂਤਾਂ {
        Uint16 vk_ਕੋਡ = LOWORD(wParam);

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        ਜਾਂਚ_ਕੋਡ = LOWORD(Map_Virtual_ਕੁੰਜੀ(vk_ਕੋਡ, WIN_IsWindowsXP() ? MAPVK_VK_ਮੰਜ਼ਿਲ_VSC : MAPVK_VK_ਮੰਜ਼ਿਲ_VSC_EX));
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        ਜੇ (ਜਾਂਚ_ਕੋਡ == 0xe11d) {
            ਜਾਂਚ_ਕੋਡ = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    ਸੂਚਕਾਂਕ = LOBYTE(ਜਾਂਚ_ਕੋਡ) | (HIBYTE(ਜਾਂਚ_ਕੋਡ) ? 0x80 : 0x00);
    ਕੋਡ = windows_scancode_ਸਾਰਣੀ[ਸੂਚਕਾਂਕ];
    *rawcode = ਜਾਂਚ_ਕੋਡ;

    ਵਾਪਸ ਕੋਡ;
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਸਥਿਰ bool WIN_ShouldIgnoreFocusClick(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਵਾਪਸ !SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ਸਥਿਰ ਖਾਲੀ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_ਅਦਲਾ_ਬਦਲੀ_Buttons, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, Uint8 button, SDL_MouseID mouseID)
{
    ਜੇ (b_ਅਦਲਾ_ਬਦਲੀ_Buttons) {
        ਜੇ (button == SDL_BUTTON_ਖੱਬਾ) {
            button = SDL_BUTTON_ਸੱਜਾ;
        } ਨਹੀਂਤਾਂ ਜੇ (button == SDL_BUTTON_ਸੱਜਾ) {
            button = SDL_BUTTON_ਖੱਬਾ;
        }
    }

    ਜੇ (ਅੰਕੜੇ->focus_click_pending & SDL_BUTTON_ਨਕਾਬ(button)) {
        // Ignore the button click for activation
        ਜੇ (!bwParamMousePressed) {
            ਅੰਕੜੇ->focus_click_pending &= ~SDL_BUTTON_ਨਕਾਬ(button);
            WIN_UpdateClipCursor(ਅੰਕੜੇ->ਖਿੜਕੀ);
        }
        ਵਾਪਸ;
    }

    ਜੇ (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_ਨਕਾਬ(button))) {
        SDL_SendMouseButton(timestamp, ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID, button, true);
    } ਨਹੀਂਤਾਂ ਜੇ (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_ਨਕਾਬ(button))) {
        SDL_SendMouseButton(timestamp, ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ਸਥਿਰ ਖਾਲੀ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, SDL_MouseID mouseID)
{
    ਜੇ (wParam != ਅੰਕੜੇ->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(ਨਿਰਾ, ਨਿਰਾ);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, ਅੰਕੜੇ, SDL_BUTTON_ਖੱਬਾ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, ਅੰਕੜੇ, SDL_BUTTON_ਵਿਚਕਾਰ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, ਅੰਕੜੇ, SDL_BUTTON_ਸੱਜਾ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, ਅੰਕੜੇ, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, ਅੰਕੜੇ, SDL_BUTTON_X2, mouseID);

        ਅੰਕੜੇ->mouse_button_flags = wParam;
    }
}

ਸਥਿਰ ਖਾਲੀ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT ਕੁੰਜੀ_State;
    bool ਅਦਲਾ_ਬਦਲੀ_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(ਨਿਰਾ, ਨਿਰਾ);
    ਅਦਲਾ_ਬਦਲੀ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    ਕੁੰਜੀ_State = Get_Async_ਕੁੰਜੀ_State(VK_LBUTTON);
    ਜੇ (!(ਕੁੰਜੀ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ਅਦਲਾ_ਬਦਲੀ_Buttons, ਅੰਕੜੇ, SDL_BUTTON_ਖੱਬਾ, mouseID);
    }
    ਕੁੰਜੀ_State = Get_Async_ਕੁੰਜੀ_State(VK_RBUTTON);
    ਜੇ (!(ਕੁੰਜੀ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ਅਦਲਾ_ਬਦਲੀ_Buttons, ਅੰਕੜੇ, SDL_BUTTON_ਸੱਜਾ, mouseID);
    }
    ਕੁੰਜੀ_State = Get_Async_ਕੁੰਜੀ_State(VK_MBUTTON);
    ਜੇ (!(ਕੁੰਜੀ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ਅਦਲਾ_ਬਦਲੀ_Buttons, ਅੰਕੜੇ, SDL_BUTTON_ਵਿਚਕਾਰ, mouseID);
    }
    ਕੁੰਜੀ_State = Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON1);
    ਜੇ (!(ਕੁੰਜੀ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ਅਦਲਾ_ਬਦਲੀ_Buttons, ਅੰਕੜੇ, SDL_BUTTON_X1, mouseID);
    }
    ਕੁੰਜੀ_State = Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON2);
    ਜੇ (!(ਕੁੰਜੀ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, ਅਦਲਾ_ਬਦਲੀ_Buttons, ਅੰਕੜੇ, SDL_BUTTON_X2, mouseID);
    }
    ਅੰਕੜੇ->mouse_button_flags = (WPARAM)-1;
}

ਸਥਿਰ ਖਾਲੀ WIN_UpdateFocus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool expect_focus, LPPOINT pos)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == ਖਿੜਕੀ);
    bool has_focus = (Get_Foreground_ਖਿੜਕੀ() == hwnd);

    ਜੇ (had_focus == has_focus || has_focus != expect_focus) {
        ਵਾਪਸ;
    }

    ਜੇ (has_focus) {
        ਬਿੰਦੂ_2 cursorPos;

        ਜੇ (WIN_ShouldIgnoreFocusClick(ਅੰਕੜੇ) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
            bool ਅਦਲਾ_ਬਦਲੀ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            ਜੇ (Get_Async_ਕੁੰਜੀ_State(VK_LBUTTON)) {
                ਅੰਕੜੇ->focus_click_pending |= !ਅਦਲਾ_ਬਦਲੀ_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            ਜੇ (Get_Async_ਕੁੰਜੀ_State(VK_RBUTTON)) {
                ਅੰਕੜੇ->focus_click_pending |= !ਅਦਲਾ_ਬਦਲੀ_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            ਜੇ (Get_Async_ਕੁੰਜੀ_State(VK_MBUTTON)) {
                ਅੰਕੜੇ->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            ਜੇ (Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON1)) {
                ਅੰਕੜੇ->focus_click_pending |= SDL_BUTTON_X1_ਨਕਾਬ;
            }
            ਜੇ (Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON2)) {
                ਅੰਕੜੇ->focus_click_pending |= SDL_BUTTON_X2_ਨਕਾਬ;
            }
        }

        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ->keyboard_focus ? ਖਿੜਕੀ->keyboard_focus : ਖਿੜਕੀ);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        ਜੇ (!SDL_GetMouse()->relative_ਬਹੁਲਕ) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)cursorPos.x, (ਦਸ਼ਮਲਵ)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ਅੰਕੜੇ);
        WIN_UpdateClipCursor(ਖਿੜਕੀ);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(ਅੰਕੜੇ->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_ਕੁੰਜੀ_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_ਅੰਕ, (Get_ਕੁੰਜੀ_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_ਕੁੰਜੀ_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_ਖਿੜਕੀ_ICCProfile(ਅੰਕੜੇ->ਖਿੜਕੀ, true);
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->ਵਿੱਚ_ਖਿੜਕੀ_deactivation = true;

        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        ਜੇ (SDL_GetMouse()->relative_ਬਹੁਲਕ) {
            SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
        }
        WIN_Reset_Dead_ਕੁੰਜੀਆਂ();

        WIN_Unclip_Cursor_For_ਖਿੜਕੀ(ਖਿੜਕੀ);

        ਅੰਕੜੇ->ਵਿੱਚ_ਖਿੜਕੀ_deactivation = false;
    }
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ਸਥਿਰ bool Should_Generate_ਖਿੜਕੀ_Close_On_Alt_F4(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ਸਥਿਰ bool Should_Clear_ਖਿੜਕੀ_On_Erase_Background(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਚੋਣ (ਅੰਕੜੇ->hint_erase_background_ਬਹੁਲਕ) {
    ਹਾਲਤ SDL_ERASEBACKGROUNDMODE_NEVER:
        ਵਾਪਸ false;
    ਹਾਲਤ SDL_ERASEBACKGROUNDMODE_INITIAL:
        ਵਾਪਸ !ਅੰਕੜੇ->videodata->cleared;
    ਹਾਲਤ SDL_ERASEBACKGROUNDMODE_ALWAYS:
        ਵਾਪਸ true;
    ਮੂਲ:
        // Unexpected value, fallback to default behaviour
        ਵਾਪਸ !ਅੰਕੜੇ->videodata->cleared;
    }
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MI_WP_SIGNATURE      0xFF515700
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MI_WP_SIGNATURE_ਨਕਾਬ 0xFFFFFF00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_ਨਕਾਬ) == MI_WP_SIGNATURE

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    SDL_MOUSE_EVENT_ਸਰੋਤ_UNKNOWN,
    SDL_MOUSE_EVENT_ਸਰੋਤ_MOUSE,
    SDL_MOUSE_EVENT_ਸਰੋਤ_TOUCH,
    SDL_MOUSE_EVENT_ਸਰੋਤ_PEN,
} SDL_MOUSE_EVENT_ਸਰੋਤ;

ਸਥਿਰ SDL_MOUSE_EVENT_ਸਰੋਤ Get_Mouse_ਸੁਨੇਹਾ_ਸਰੋਤ(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    ਜੇ (IsTouchEvent(extrainfo)) {
        ਜੇ (extrainfo & 0x80) {
            ਵਾਪਸ SDL_MOUSE_EVENT_ਸਰੋਤ_TOUCH;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_MOUSE_EVENT_ਸਰੋਤ_PEN;
        }
    }
    ਵਾਪਸ SDL_MOUSE_EVENT_ਸਰੋਤ_MOUSE;
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ਸਥਿਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *WIN_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

    ਜੇ (_this) {
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
            ਜੇ (ਅੰਕੜੇ && ਅੰਕੜੇ->hwnd == hwnd) {
                ਵਾਪਸ ਅੰਕੜੇ;
            }
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(ਪੂਰਨ n_ਕੋਡ, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_ਅੰਕੜੇ = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    SDL_Scancode ਜਾਂਚ_ਕੋਡ;

    ਜੇ (n_ਕੋਡ < 0 || n_ਕੋਡ != HC_ACTION) {
        ਵਾਪਸ Call_ਅਗਲਾ_Hook_Ex(ਨਿਰਾ, n_ਕੋਡ, wParam, lParam);
    }
    ਜੇ (hook_ਅੰਕੜੇ->ਜਾਂਚ_ਕੋਡ == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        ਵਾਪਸ 1;
    }

    ਚੋਣ (hook_ਅੰਕੜੇ->vk_ਕੋਡ) {
    ਹਾਲਤ VK_LWIN:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_LGUI;
        ਰੋਕੋ;
    ਹਾਲਤ VK_RWIN:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_RGUI;
        ਰੋਕੋ;
    ਹਾਲਤ VK_LMENU:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_LALT;
        ਰੋਕੋ;
    ਹਾਲਤ VK_RMENU:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_RALT;
        ਰੋਕੋ;
    ਹਾਲਤ VK_LCONTROL:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_LCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ VK_RCONTROL:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_RCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ VK_SNAPSHOT:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_PRINTSCREEN;
        ਰੋਕੋ;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    ਹਾਲਤ VK_TAB:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_TAB;
        ਰੋਕੋ;
    ਹਾਲਤ VK_ESCAPE:
        ਜਾਂਚ_ਕੋਡ = SDL_SCANCODE_ESCAPE;
        ਰੋਕੋ;

    ਮੂਲ:
        ਵਾਪਸ Call_ਅਗਲਾ_Hook_Ex(ਨਿਰਾ, n_ਕੋਡ, wParam, lParam);
    }

    ਜੇ (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        ਜੇ (!ਅੰਕੜੇ->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, hook_ਅੰਕੜੇ->ਜਾਂਚ_ਕੋਡ, ਜਾਂਚ_ਕੋਡ, true);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!ਅੰਕੜੇ->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, hook_ਅੰਕੜੇ->ਜਾਂਚ_ਕੋਡ, ਜਾਂਚ_ਕੋਡ, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        ਜੇ (hook_ਅੰਕੜੇ->vk_ਕੋਡ <= 0xFF && ਅੰਕੜੇ->pre_hook_ਕੁੰਜੀ_state[hook_ਅੰਕੜੇ->vk_ਕੋਡ]) {
            ਅੰਕੜੇ->pre_hook_ਕੁੰਜੀ_state[hook_ਅੰਕੜੇ->vk_ਕੋਡ] = 0;
            ਵਾਪਸ Call_ਅਗਲਾ_Hook_Ex(ਨਿਰਾ, n_ਕੋਡ, wParam, lParam);
        }
    }

    ਵਾਪਸ 1;
}

ਸਥਿਰ bool WIN_ਅਦਲਾ_ਬਦਲੀ_Buttons(HANDLE hDevice)
{
    ਜੇ (hDevice == ਨਿਰਾ) {
        // Touchpad, already has buttons swapped
        ਵਾਪਸ false;
    }
    ਵਾਪਸ GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ਸਥਿਰ ਖਾਲੀ WIN_Handle_Raw_Mouse_ਨਿਵੇਸ਼(Uint64 timestamp, SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ਸਥਿਰ ਬਣਤਰ {
        USHORT usButtonFlags;
        Uint8 button;
        bool ਥੱਲੇ;
    } raw_buttons[] = {
        { RI_MOUSE_ਖੱਬਾ_BUTTON_ਥੱਲੇ, SDL_BUTTON_ਖੱਬਾ, true },
        { RI_MOUSE_ਖੱਬਾ_BUTTON_ਉੱਪਰ, SDL_BUTTON_ਖੱਬਾ, false },
        { RI_MOUSE_ਸੱਜਾ_BUTTON_ਥੱਲੇ, SDL_BUTTON_ਸੱਜਾ, true },
        { RI_MOUSE_ਸੱਜਾ_BUTTON_ਉੱਪਰ, SDL_BUTTON_ਸੱਜਾ, false },
        { RI_MOUSE_ਵਿਚਕਾਰ_BUTTON_ਥੱਲੇ, SDL_BUTTON_ਵਿਚਕਾਰ, true },
        { RI_MOUSE_ਵਿਚਕਾਰ_BUTTON_ਉੱਪਰ, SDL_BUTTON_ਵਿਚਕਾਰ, false },
        { RI_MOUSE_BUTTON_4_ਥੱਲੇ, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_ਉੱਪਰ, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_ਥੱਲੇ, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_ਉੱਪਰ, SDL_BUTTON_X2, false }
    };

    ਪੂਰਨ dx = (ਪੂਰਨ)rawmouse->l_ਆਖਰੀ_X;
    ਪੂਰਨ dy = (ਪੂਰਨ)rawmouse->l_ਆਖਰੀ_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    ਜੇ (!ਅੰਕੜੇ->raw_mouse_enabled) {
        ਵਾਪਸ;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = SDL_GetKeyboardFocus();
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    ਜੇ (!mouse) {
        ਵਾਪਸ;
    }

    ਜੇ (Get_Mouse_ਸੁਨੇਹਾ_ਸਰੋਤ(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_ਸਰੋਤ_MOUSE ||
        (SDL_Touch_Devices_ਉਪਲਬਧ() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        ਵਾਪਸ;
    }

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (haveMotion && !windowdata->ਵਿੱਚ_modal_loop) {
        ਜੇ (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, mouseID, true, (ਦਸ਼ਮਲਵ)dx, (ਦਸ਼ਮਲਵ)dy);
        } ਨਹੀਂਤਾਂ {
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
            ਪੂਰਨ w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            ਪੂਰਨ h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            ਪੂਰਨ x = raw_coordinates ? dx : (ਪੂਰਨ)(((ਦਸ਼ਮਲਵ)dx / 65535.0f) * w);
            ਪੂਰਨ y = raw_coordinates ? dy : (ਪੂਰਨ)(((ਦਸ਼ਮਲਵ)dy / 65535.0f) * h);
            ਪੂਰਨ relX, relY;

            /* Calculate relative motion */
            ਜੇ (ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.x == 0 && ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.y == 0) {
                ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.x = x;
                ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.y = y;
            }
            relX = x - ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.x;
            relY = y - ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.y;

            ਜੇ (remote_desktop) {
                ਜੇ (!windowdata->ਵਿੱਚ_title_click && !windowdata->focus_click_pending) {
                    ਸਥਿਰ ਪੂਰਨ wobble;
                    ਦਸ਼ਮਲਵ floatX = (ਦਸ਼ਮਲਵ)x / w;
                    ਦਸ਼ਮਲਵ floatY = (ਦਸ਼ਮਲਵ)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    ਜੇ (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        ਪੂਰਨ warpX = rect.ਖੱਬਾ + ((rect.ਸੱਜਾ - rect.ਖੱਬਾ) / 2) + wobble;
                        ਪੂਰਨ warpY = rect.ਸਿਖਰ + ((rect.bottom - rect.ਸਿਖਰ) / 2);

                        WIN_ਸੈੱਟ_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        ਜੇ (wobble > 1) {
                            wobble = -1;
                        }
                    } ਨਹੀਂਤਾਂ {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ਅਚਲ ਪੂਰਨ MAX_RELATIVE_MOTION = (h / 6);
                        ਜੇ (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, mouseID, true, (ਦਸ਼ਮਲਵ)relX, (ਦਸ਼ਮਲਵ)relY);
                        }
                    }
                }
            } ਨਹੀਂਤਾਂ ਜੇ (mouse->pen_mouse_events) {
                ਅਚਲ ਪੂਰਨ ਵੱਧ_ਤੋਂ_ਵੱਧ_TABLET_RELATIVE_MOTION = 32;
                ਜੇ (SDL_abs(relX) > ਵੱਧ_ਤੋਂ_ਵੱਧ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > ਵੱਧ_ਤੋਂ_ਵੱਧ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } ਨਹੀਂਤਾਂ {
                    SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, mouseID, true, (ਦਸ਼ਮਲਵ)relX, (ਦਸ਼ਮਲਵ)relY);
                }
            } ਨਹੀਂਤਾਂ {
                ਪੂਰਨ screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                ਪੂਰਨ screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                ਜੇ (!ਅੰਕੜੇ->raw_ਨਿਵੇਸ਼_fake_pen_id) {
                    ਅੰਕੜੇ->raw_ਨਿਵੇਸ਼_fake_pen_id = SDL_ਜੋੜੋ_Pen_Device(timestamp, "raw mouse input", ਖਿੜਕੀ, ਨਿਰਾ, (ਖਾਲੀ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, ਅੰਕੜੇ->raw_ਨਿਵੇਸ਼_fake_pen_id, ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ)(x + screen_x - ਖਿੜਕੀ->x), (ਦਸ਼ਮਲਵ)(y + screen_y - ਖਿੜਕੀ->y));
            }

            ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.x = x;
            ਅੰਕੜੇ->ਆਖਰੀ_raw_mouse_position.y = y;
        }
    }

    ਜੇ (haveButton) {
        ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            ਜੇ (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool ਥੱਲੇ = raw_buttons[i].ਥੱਲੇ;

                ਜੇ (button == SDL_BUTTON_ਖੱਬਾ) {
                    ਜੇ (WIN_ਅਦਲਾ_ਬਦਲੀ_Buttons(hDevice)) {
                        button = SDL_BUTTON_ਸੱਜਾ;
                    }
                } ਨਹੀਂਤਾਂ ਜੇ (button == SDL_BUTTON_ਸੱਜਾ) {
                    ਜੇ (WIN_ਅਦਲਾ_ਬਦਲੀ_Buttons(hDevice)) {
                        button = SDL_BUTTON_ਖੱਬਾ;
                    }
                }

                ਜੇ (windowdata->focus_click_pending & SDL_BUTTON_ਨਕਾਬ(button)) {
                    // Ignore the button click for activation
                    ਜੇ (!ਥੱਲੇ) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_ਨਕਾਬ(button);
                        WIN_UpdateClipCursor(ਖਿੜਕੀ);
                    }
                    ਜਾਰੀ;
                }

                SDL_SendMouseButton(timestamp, ਖਿੜਕੀ, mouseID, button, ਥੱਲੇ);
            }
        }

        ਜੇ (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ਅੰਕੜੇ;
            ਦਸ਼ਮਲਵ fAmount = (ਦਸ਼ਮਲਵ)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, ਖਿੜਕੀ, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
        } ਨਹੀਂਤਾਂ ਜੇ (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ਅੰਕੜੇ;
            ਦਸ਼ਮਲਵ fAmount = (ਦਸ਼ਮਲਵ)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, ਖਿੜਕੀ, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ਸਥਿਰ ਖਾਲੀ WIN_Handle_Raw_Keyboard_ਨਿਵੇਸ਼(Uint64 timestamp, SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    ਜੇ (!ਅੰਕੜੇ->raw_keyboard_enabled) {
        ਵਾਪਸ;
    }

    ਜੇ (rawkeyboard->Flags & RI_ਕੁੰਜੀ_E1) {
        // First key in a Ctrl+{key} sequence
        ਅੰਕੜੇ->pending_E1_ਕੁੰਜੀ_sequence = true;
        ਵਾਪਸ;
    }

    ਜੇ ((rawkeyboard->Flags & RI_ਕੁੰਜੀ_E0) && rawkeyboard->Make_ਕੋਡ == 0x2A) {
        // 0xE02A make code prefix, ignored
        ਵਾਪਸ;
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (!rawkeyboard->Make_ਕੋਡ) {
        rawkeyboard->Make_ਕੋਡ = LOWORD(Map_Virtual_ਕੁੰਜੀ(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_ਮੰਜ਼ਿਲ_VSC : MAPVK_VK_ਮੰਜ਼ਿਲ_VSC_EX));
    }
#ਜੇ_ਅੰਤ
    ਜੇ (!rawkeyboard->Make_ਕੋਡ) {
        ਵਾਪਸ;
    }

    bool ਥੱਲੇ;
    ਚੋਣ (rawkeyboard->ਸੁਨੇਹਾ_4) {
    ਹਾਲਤ WM_KEYDOWN:
    ਹਾਲਤ WM_SYSKEYDOWN:
        ਥੱਲੇ = true;
        ਰੋਕੋ;
    ਹਾਲਤ WM_KEYUP:
    ਹਾਲਤ WM_SYSKEYUP:
        ਥੱਲੇ = false;
        ਰੋਕੋ;
    ਮੂਲ:
        ਥੱਲੇ = !(rawkeyboard->Flags & RI_ਕੁੰਜੀ_BREAK);
        ਰੋਕੋ;
    }

    SDL_Scancode ਕੋਡ;
    USHORT rawcode = rawkeyboard->Make_ਕੋਡ;
    ਜੇ (ਅੰਕੜੇ->pending_E1_ਕੁੰਜੀ_sequence) {
        rawcode |= 0xE100;
        ਜੇ (rawkeyboard->Make_ਕੋਡ == 0x45) {
            // Ctrl+NumLock == Pause
            ਕੋਡ = SDL_SCANCODE_PAUSE;
        } ਨਹੀਂਤਾਂ {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            ਕੋਡ = SDL_SCANCODE_UNKNOWN;
        }
        ਅੰਕੜੇ->pending_E1_ਕੁੰਜੀ_sequence = false;
    } ਨਹੀਂਤਾਂ {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 ਸੂਚਕਾਂਕ = (Uint8)rawkeyboard->Make_ਕੋਡ;
        ਜੇ (rawkeyboard->Flags & RI_ਕੁੰਜੀ_E0) {
            rawcode |= 0xE000;
            ਸੂਚਕਾਂਕ |= 0x80;
        }
        ਕੋਡ = windows_scancode_ਸਾਰਣੀ[ਸੂਚਕਾਂਕ];
    }

    ਜੇ (ਥੱਲੇ) {
        SDL_ਖਿੜਕੀ *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        ਜੇ ((!ਅੰਕੜੇ->raw_keyboard_flag_inputsink && !focus) || (focus && focus->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ)) {
            ਵਾਪਸ;
        }
    }

    SDL_Send_Keyboard_ਕੁੰਜੀ(timestamp, keyboardID, rawcode, ਕੋਡ, ਥੱਲੇ);
}

ਖਾਲੀ WIN_Poll_Raw_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, Uint64 poll_ਸ਼ੁਰੂ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    UINT ਮਾਪ, i, ਗਿਣਤੀ_2, ਕੁੱਲ = 0;
    RAWINPUT *ਨਿਵੇਸ਼;
    Uint64 poll_ਅੰਤ;

    ਜੇ (ਅੰਕੜੇ->rawinput_ਵਿੱਥ == 0) {
        BOOL isWow64;

        ਅੰਕੜੇ->rawinput_ਵਿੱਥ = ਆਕਾਰ(RAWINPUTHEADER);
        ਜੇ (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            ਅੰਕੜੇ->rawinput_ਵਿੱਥ += 8;
        }
    }

    // Get all available events
    ਨਿਵੇਸ਼ = (RAWINPUT *)ਅੰਕੜੇ->rawinput;
    ਲਈ (;;) {
        ਮਾਪ = ਅੰਕੜੇ->rawinput_ਮਾਪ - (UINT)((BYTE *)ਨਿਵੇਸ਼ - ਅੰਕੜੇ->rawinput);
        ਗਿਣਤੀ_2 = Get_Raw_ਨਿਵੇਸ਼_ਬਫਰ(ਨਿਵੇਸ਼, &ਮਾਪ, ਆਕਾਰ(RAWINPUTHEADER));
        poll_ਅੰਤ = SDL_GetTicksNS();
        ਜੇ (ਗਿਣਤੀ_2 == 0 || ਗਿਣਤੀ_2 == (UINT)-1) {
            ਜੇ (!ਅੰਕੜੇ->rawinput || (ਗਿਣਤੀ_2 == (UINT)-1 && Get_ਆਖਰੀ_Error() == ERROR_INSUFFICIENT_ਬਫਰ)) {
                ਅਚਲ UINT RAWINPUT_ਬਫਰ_ਮਾਪ_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(ਅੰਕੜੇ->rawinput, ਅੰਕੜੇ->rawinput_ਮਾਪ + RAWINPUT_ਬਫਰ_ਮਾਪ_INCREMENT);
                ਜੇ (!rawinput) {
                    ਰੋਕੋ;
                }
                ਨਿਵੇਸ਼ = (RAWINPUT *)(rawinput + ((BYTE *)ਨਿਵੇਸ਼ - ਅੰਕੜੇ->rawinput));
                ਅੰਕੜੇ->rawinput = rawinput;
                ਅੰਕੜੇ->rawinput_ਮਾਪ += RAWINPUT_ਬਫਰ_ਮਾਪ_INCREMENT;
            } ਨਹੀਂਤਾਂ {
                ਰੋਕੋ;
            }
        } ਨਹੀਂਤਾਂ {
            ਕੁੱਲ += ਗਿਣਤੀ_2;

            // Advance input to the end of the buffer
            ਜਦੋਂ (ਗਿਣਤੀ_2--) {
                ਨਿਵੇਸ਼ = NEXTRAWINPUTBLOCK(ਨਿਵੇਸ਼);
            }
        }
    }

    ਜੇ (ਕੁੱਲ > 0) {
        Uint64 delta = poll_ਅੰਤ - poll_ਸ਼ੁਰੂ;
        UINT mouse_ਕੁੱਲ = 0;
        ਲਈ (i = 0, ਨਿਵੇਸ਼ = (RAWINPUT *)ਅੰਕੜੇ->rawinput; i < ਕੁੱਲ; ++i, ਨਿਵੇਸ਼ = NEXTRAWINPUTBLOCK(ਨਿਵੇਸ਼)) {
            ਜੇ (ਨਿਵੇਸ਼->ਸਿਰਲੇਖ.dwType == RIM_TYPEMOUSE) {
                mouse_ਕੁੱਲ += 1;
            }
        }
        ਪੂਰਨ mouse_ਸੂਚਕਾਂਕ = 0;
        ਲਈ (i = 0, ਨਿਵੇਸ਼ = (RAWINPUT *)ਅੰਕੜੇ->rawinput; i < ਕੁੱਲ; ++i, ਨਿਵੇਸ਼ = NEXTRAWINPUTBLOCK(ਨਿਵੇਸ਼)) {
            ਜੇ (ਨਿਵੇਸ਼->ਸਿਰਲੇਖ.dwType == RIM_TYPEMOUSE) {
                mouse_ਸੂਚਕਾਂਕ += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)ਨਿਵੇਸ਼ + ਅੰਕੜੇ->rawinput_ਵਿੱਥ);
                Uint64 ਸਮਾਂ = poll_ਅੰਤ - (delta * (mouse_ਕੁੱਲ - mouse_ਸੂਚਕਾਂਕ)) / mouse_ਕੁੱਲ;
                WIN_Handle_Raw_Mouse_ਨਿਵੇਸ਼(ਸਮਾਂ, ਅੰਕੜੇ, ਨਿਵੇਸ਼->ਸਿਰਲੇਖ.hDevice, rawmouse);
            } ਨਹੀਂਤਾਂ ਜੇ (ਨਿਵੇਸ਼->ਸਿਰਲੇਖ.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)ਨਿਵੇਸ਼ + ਅੰਕੜੇ->rawinput_ਵਿੱਥ);
                WIN_Handle_Raw_Keyboard_ਨਿਵੇਸ਼(poll_ਅੰਤ, ਅੰਕੜੇ, ਨਿਵੇਸ਼->ਸਿਰਲੇਖ.hDevice, rawkeyboard);
            }
        }
    }
    ਅੰਕੜੇ->ਆਖਰੀ_rawinput_poll = poll_ਅੰਤ;
}

ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Device_ID(Uint32 deviceID, Uint32 **list, ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਪੂਰਨ new_ਗਿਣਤੀ = (*ਗਿਣਤੀ_2 + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ਗਿਣਤੀ * ਆਕਾਰ(*new_list));
    ਜੇ (!new_list) {
        // Oh well, we'll drop this one
        ਵਾਪਸ;
    }
    new_list[new_ਗਿਣਤੀ - 1] = deviceID;

    *ਗਿਣਤੀ_2 = new_ਗਿਣਤੀ;
    *list = new_list;
}

ਸਥਿਰ bool HasDeviceID(Uint32 deviceID, ਅਚਲ Uint32 *list, ਪੂਰਨ ਗਿਣਤੀ_2)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; ++i) {
        ਜੇ (deviceID == list[i]) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਅੱਖਰ *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ਅਚਲ ਅੱਖਰ *instance, Uint16 vendor, Uint16 ਗੁਣਨਫਲ, ਅਚਲ ਅੱਖਰ *default_name, bool hid_loaded)
{
    ਅੱਖਰ *vendor_name = ਨਿਰਾ;
    ਅੱਖਰ *ਗੁਣਨਫਲ_name = ਨਿਰਾ;
    ਅੱਖਰ *name = ਨਿਰਾ;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    ਜੇ (hid_loaded) {
        ਅੱਖਰ devName[MAX_ਰਸਤਾ + 1];
        devName[0] = '\0';
        UINT cap = ਆਕਾਰ(devName) - 1;
        UINT len = Get_Raw_ਨਿਵੇਸ਼_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        ਜੇ (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, ਨਿਰਾ, OPEN_EXISTING, 0, ਨਿਰਾ);
            ਜੇ (hFile != INVALID_HANDLE_ਮੁੱਲ) {
                SDL_HidD_GetManufacturerString(hFile, vend, ਆਕਾਰ(vend));
                SDL_Hid_D_Get_ਗੁਣਨਫਲ_String(hFile, prod, ਆਕਾਰ(prod));
                CloseHandle(hFile);
            }
        }
    }

    ਜੇ (vend[0]) {
        vendor_name = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(vend);
    }

    ਜੇ (prod[0]) {
        ਗੁਣਨਫਲ_name = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(prod);
    } ਨਹੀਂਤਾਂ {
        SP_DEVINFO_ਅੰਕੜੇ ਅੰਕੜੇ;
        SDL_zero(ਅੰਕੜੇ);
        ਅੰਕੜੇ.cb_ਮਾਪ = ਆਕਾਰ(ਅੰਕੜੇ);
        ਲਈ (DWORD i = 0;; ++i) {
            ਜੇ (!ਤਿਆਰੀ_Di_Enum_Device_Info(devinfo, i, &ਅੰਕੜੇ)) {
                ਜੇ (Get_ਆਖਰੀ_Error() == ERROR_NO_ਹੋਰ_ਚੀਜ਼ਾਂ) {
                    ਰੋਕੋ;
                } ਨਹੀਂਤਾਂ {
                    ਜਾਰੀ;
                }
            }

            ਅੱਖਰ DeviceInstanceId[64];
            ਜੇ (!ਤਿਆਰੀ_Di_Get_Device_Instance_Id_A(devinfo, &ਅੰਕੜੇ, DeviceInstanceId, ਆਕਾਰ(DeviceInstanceId), ਨਿਰਾ))
                ਜਾਰੀ;

            ਜੇ (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD ਮਾਪ = 0;
                ਜੇ (ਤਿਆਰੀ_Di_Get_Device_Registry_Property_W(devinfo, &ਅੰਕੜੇ, SPDRP_DEVICEDESC, ਨਿਰਾ, (PBYTE)prod, ਆਕਾਰ(prod), &ਮਾਪ)) {
                    // Make sure the device description is null terminated
                    ਮਾਪ /= ਆਕਾਰ(*prod);
                    ਜੇ (ਮਾਪ >= SDL_arraysize(prod)) {
                        // Truncated description...
                        ਮਾਪ = (SDL_arraysize(prod) - 1);
                    }
                    prod[ਮਾਪ] = 0;

                    ਜੇ (vendor || ਗੁਣਨਫਲ) {
                        SDL_asprintf(&ਗੁਣਨਫਲ_name, "%S (0x%.4x/0x%.4x)", prod, vendor, ਗੁਣਨਫਲ);
                    } ਨਹੀਂਤਾਂ {
                        ਗੁਣਨਫਲ_name = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(prod);
                    }
                }
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (!ਗੁਣਨਫਲ_name && (vendor || ਗੁਣਨਫਲ)) {
        SDL_asprintf(&ਗੁਣਨਫਲ_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, ਗੁਣਨਫਲ);
    }
    name = SDL_CreateDeviceName(vendor, ਗੁਣਨਫਲ, vendor_name, ਗੁਣਨਫਲ_name, default_name);
    SDL_free(vendor_name);
    SDL_free(ਗੁਣਨਫਲ_name);

    ਵਾਪਸ name;
}

ਖਾਲੀ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = ਨਿਰਾ;
    UINT raw_device_ਗਿਣਤੀ = 0;
    ਪੂਰਨ old_keyboard_ਗਿਣਤੀ = 0;
    SDL_KeyboardID *old_keyboards = ਨਿਰਾ;
    ਪੂਰਨ new_keyboard_ਗਿਣਤੀ = 0;
    SDL_KeyboardID *new_keyboards = ਨਿਰਾ;
    ਪੂਰਨ old_mouse_ਗਿਣਤੀ = 0;
    SDL_MouseID *old_mice = ਨਿਰਾ;
    ਪੂਰਨ new_mouse_ਗਿਣਤੀ = 0;
    SDL_MouseID *new_mice = ਨਿਰਾ;

    ਜੇ (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->ਅੰਦਰੂਨੀ->detect_device_hotplug ||
        _this->ਅੰਦਰੂਨੀ->gameinput_context) {
        ਵਾਪਸ;
    }

    ਜੇ ((Get_Raw_ਨਿਵੇਸ਼_Device_List(ਨਿਰਾ, &raw_device_ਗਿਣਤੀ, ਆਕਾਰ(RAWINPUTDEVICELIST)) == -1) || (!raw_device_ਗਿਣਤੀ)) {
        ਵਾਪਸ; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(ਆਕਾਰ(RAWINPUTDEVICELIST) * raw_device_ਗਿਣਤੀ);
    ਜੇ (!raw_devices) {
        ਵਾਪਸ; // oh well.
    }

    raw_device_ਗਿਣਤੀ = Get_Raw_ਨਿਵੇਸ਼_Device_List(raw_devices, &raw_device_ਗਿਣਤੀ, ਆਕਾਰ(RAWINPUTDEVICELIST));
    ਜੇ (raw_device_ਗਿਣਤੀ == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = ਨਿਰਾ;
        ਵਾਪਸ; // oh well.
    }

    HDEVINFO devinfo = ਤਿਆਰੀ_Di_Get_Class_Devs_A(ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ਗਿਣਤੀ);
    old_mice = SDL_GetMice(&old_mouse_ਗਿਣਤੀ);

    ਲਈ (UINT i = 0; i < raw_device_ਗਿਣਤੀ; i++) {
        RID_DEVICE_INFO rdi;
        ਅੱਖਰ devName[MAX_ਰਸਤਾ] = { 0 };
        UINT rdi_ਮਾਪ = ਆਕਾਰ(rdi);
        UINT name_ਮਾਪ = SDL_arraysize(devName);
        ਪੂਰਨ vendor = 0, ਗੁਣਨਫਲ = 0;
        DWORD dwType = raw_devices[i].dwType;
        ਅੱਖਰ *instance, *ptr, *name;

        ਜੇ (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            ਜਾਰੀ;
        }

        rdi.cb_ਮਾਪ = ਆਕਾਰ(rdi);
        ਜੇ (Get_Raw_ਨਿਵੇਸ਼_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_ਮਾਪ) == ((UINT)-1) ||
            Get_Raw_ਨਿਵੇਸ਼_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_ਮਾਪ) == ((UINT)-1)) {
            ਜਾਰੀ;
        }

        // Extract the device instance
        instance = devName;
        ਜਦੋਂ (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        ਲਈ (ptr = instance; *ptr; ++ptr) {
            ਜੇ (*ptr == '#') {
                *ptr = '\\';
            }
            ਜੇ (*ptr == '{') {
                ਜੇ (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                ਰੋਕੋ;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &ਗੁਣਨਫਲ);

        ਚੋਣ (dwType) {
        ਹਾਲਤ RIM_TYPEKEYBOARD:
            ਜੇ (SDL_IsKeyboard((Uint16)vendor, (Uint16)ਗੁਣਨਫਲ, rdi.keyboard.dw_ਸੰਖਿਆ_ਦਾ_ਕੁੰਜੀਆਂ_ਕੁੱਲ)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                ਜੋੜੋ_Device_ID(keyboardID, &new_keyboards, &new_keyboard_ਗਿਣਤੀ);
                ਜੇ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ਗਿਣਤੀ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ਗੁਣਨਫਲ, "Keyboard", hid_loaded);
                    SDL_ਜੋੜੋ_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ RIM_TYPEMOUSE:
            ਜੇ (SDL_IsMouse((Uint16)vendor, (Uint16)ਗੁਣਨਫਲ)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                ਜੋੜੋ_Device_ID(mouseID, &new_mice, &new_mouse_ਗਿਣਤੀ);
                ਜੇ (!HasDeviceID(mouseID, old_mice, old_mouse_ਗਿਣਤੀ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ਗੁਣਨਫਲ, "Mouse", hid_loaded);
                    SDL_ਜੋੜੋ_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    ਲਈ (ਪੂਰਨ i = old_keyboard_ਗਿਣਤੀ; i--;) {
        ਜੇ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ਗਿਣਤੀ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ਲਈ (ਪੂਰਨ i = old_mouse_ਗਿਣਤੀ; i--;) {
        ਜੇ (!HasDeviceID(old_mice[i], new_mice, new_mouse_ਗਿਣਤੀ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    ਤਿਆਰੀ_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ਸਥਿਰ bool Skip_Alt_Gr_ਖੱਬਾ_Control(WPARAM wParam, LPARAM lParam)
{
    ਜੇ (wParam != VK_CONTROL) {
        ਵਾਪਸ false;
    }

    // Is this an extended key (i.e. right key)?
    ਜੇ (lParam & 0x01000000) {
        ਵਾਪਸ false;
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    ਸੁਨੇਹਾ_3 ਅਗਲਾ_ਸੁਨੇਹਾ;
    DWORD ਸੁਨੇਹਾ_ਸਮਾਂ = Get_ਸੁਨੇਹਾ_ਸਮਾਂ();
    ਜੇ (Peek_ਸੁਨੇਹਾ(&ਅਗਲਾ_ਸੁਨੇਹਾ, ਨਿਰਾ, 0, 0, PM_NOREMOVE)) {
        ਜੇ (ਅਗਲਾ_ਸੁਨੇਹਾ.ਸੁਨੇਹਾ == WM_KEYDOWN ||
            ਅਗਲਾ_ਸੁਨੇਹਾ.ਸੁਨੇਹਾ == WM_SYSKEYDOWN) {
            ਜੇ (ਅਗਲਾ_ਸੁਨੇਹਾ.wParam == VK_MENU && (ਅਗਲਾ_ਸੁਨੇਹਾ.lParam & 0x01000000) && ਅਗਲਾ_ਸੁਨੇਹਾ.ਸਮਾਂ == ਸੁਨੇਹਾ_ਸਮਾਂ) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                ਵਾਪਸ true;
            }
        }
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਵਾਪਸ false;
}

ਸਥਿਰ bool Dispatch_Modal_Loop_ਸੁਨੇਹਾ_Hook(HWND *hwnd, UINT *ਸੁਨੇਹਾ_2, WPARAM *wParam, LPARAM *lParam)
{
    ਸੁਨੇਹਾ_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.ਸੁਨੇਹਾ = *ਸੁਨੇਹਾ_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    ਜੇ (g_Windows_ਸੁਨੇਹਾ_Hook(g_Windows_ਸੁਨੇਹਾ_Hook_ਅੰਕੜੇ, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *ਸੁਨੇਹਾ_2 = dummy.ਸੁਨੇਹਾ;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

LRESULT CALLBACK WIN_ਖਿੜਕੀ_Proc(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM lParam)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    LRESULT return_ਕੋਡ = -1;

    // Get the window data for the window
    ਅੰਕੜੇ = WIN_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_From_HWND(hwnd);
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (!ਅੰਕੜੇ) {
        // Fallback
        ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)GetProp(hwnd, ਪਾਠ_2("SDL_WindowData"));
    }
#ਜੇ_ਅੰਤ
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ Call_ਖਿੜਕੀ_Proc(Def_ਖਿੜਕੀ_Proc, hwnd, ਸੁਨੇਹਾ_2, wParam, lParam);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WMMSG_DEBUG
    {
        ਅੱਖਰ ਸੁਨੇਹਾ[1024];
        ਜੇ (ਸੁਨੇਹਾ_2 > MAX_WMMSG) {
            SDL_snprintf(ਸੁਨੇਹਾ, ਆਕਾਰ(ਸੁਨੇਹਾ), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, ਸੁਨੇਹਾ_2, wParam, lParam);
        } ਨਹੀਂਤਾਂ {
            SDL_snprintf(ਸੁਨੇਹਾ, ਆਕਾਰ(ਸੁਨੇਹਾ), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[ਸੁਨੇਹਾ_2], wParam, lParam);
        }
        OutputDebugStringA(ਸੁਨੇਹਾ);
    }
#ਜੇ_ਅੰਤ // WMMSG_DEBUG


    ਜੇ (g_Windows_ਸੁਨੇਹਾ_Hook && ਅੰਕੜੇ->ਵਿੱਚ_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        ਜੇ (!Dispatch_Modal_Loop_ਸੁਨੇਹਾ_Hook(&hwnd, &ਸੁਨੇਹਾ_2, &wParam, &lParam)) {
            ਵਾਪਸ 0;
        }
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (WIN_HandleIMEMessage(hwnd, ਸੁਨੇਹਾ_2, wParam, &lParam, ਅੰਕੜੇ->videodata)) {
        ਵਾਪਸ 0;
    }
#ਜੇ_ਅੰਤ

    ਚੋਣ (ਸੁਨੇਹਾ_2) {

    ਹਾਲਤ WM_SHOWWINDOW:
    {
        ਜੇ (wParam) {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
        } ਨਹੀਂਤਾਂ {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HIDDEN, 0, 0);
        }
    } ਰੋਕੋ;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਹਾਲਤ WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        ਅੰਕੜੇ->postpone_clipcursor = true;
        ਅੰਕੜੇ->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        ਬਿੰਦੂ_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(ਅੰਕੜੇ->ਖਿੜਕੀ, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_NCUAHDRAWCAPTION:
    ਹਾਲਤ WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
            return_ਕੋਡ = 0;
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ਅਚਲ DWORD ਸੁਨੇਹਾ_Pos = Get_ਸੁਨੇਹਾ_Pos();
        ਬਿੰਦੂ_2 pos = { GET_X_LPARAM(ਸੁਨੇਹਾ_Pos), GET_Y_LPARAM(ਸੁਨੇਹਾ_Pos) };
        WIN_UpdateFocus(ਅੰਕੜੇ->ਖਿੜਕੀ, !!LOWORD(wParam), &pos);
    } ਰੋਕੋ;

    ਹਾਲਤ WM_MOUSEACTIVATE:
    {
        ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
            ਵਾਪਸ MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_ਖਿੜਕੀ *ਮਾਪਾ = ਅੰਕੜੇ->ਖਿੜਕੀ->ਮਾਪਾ;
        ਜਦੋਂ (ਮਾਪਾ) {
            ਜੇ ((ਮਾਪਾ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) &&
                (ਮਾਪਾ->flags & SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ)) {
                ਵਾਪਸ MA_NOACTIVATE;
            }
            ਮਾਪਾ = ਮਾਪਾ->ਮਾਪਾ;
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ਅਚਲ DWORD ਸੁਨੇਹਾ_Pos = Get_ਸੁਨੇਹਾ_Pos();
        ਬਿੰਦੂ_2 pos = { GET_X_LPARAM(ਸੁਨੇਹਾ_Pos), GET_Y_LPARAM(ਸੁਨੇਹਾ_Pos) };
        WIN_UpdateFocus(ਅੰਕੜੇ->ਖਿੜਕੀ, true, &pos);
    } ਰੋਕੋ;

    ਹਾਲਤ WM_KILLFOCUS:
    ਹਾਲਤ WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ਅਚਲ DWORD ਸੁਨੇਹਾ_Pos = Get_ਸੁਨੇਹਾ_Pos();
        ਬਿੰਦੂ_2 pos = { GET_X_LPARAM(ਸੁਨੇਹਾ_Pos), GET_Y_LPARAM(ਸੁਨੇਹਾ_Pos) };
        WIN_UpdateFocus(ਅੰਕੜੇ->ਖਿੜਕੀ, false, &pos);
    } ਰੋਕੋ;

    ਹਾਲਤ WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ਅਚਲ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE ਸੂਚਕ_type = PT_ਸੂਚਕ;
        ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type) {
            ਰੋਕੋ;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ਨਹੀਂਤਾਂ ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type(pointerid, &ਸੂਚਕ_type)) {
            ਰੋਕੋ;  // oh well.
        } ਨਹੀਂਤਾਂ ਜੇ (ਸੂਚਕ_type != PT_PEN) {
            ਰੋਕੋ;  // we only care about pens here.
        }

        ਖਾਲੀ *hpointer = (ਖਾਲੀ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ਅਚਲ SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle(hpointer);
        ਜੇ (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ਅੰਕੜੇ->ਖਿੜਕੀ, true, true);
        } ਨਹੀਂਤਾਂ {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_ਦੂਰੀ | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.ਅੰਕ_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_ਜੋੜੋ_Pen_Device(WIN_GetEventTimestamp(), ਨਿਰਾ, ਅੰਕੜੇ->ਖਿੜਕੀ, &info, hpointer, true);
        }
        return_ਕੋਡ = 0;
    } ਰੋਕੋ;

    ਹਾਲਤ WM_POINTERCAPTURECHANGED:
    ਹਾਲਤ WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ਅਚਲ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE ਸੂਚਕ_type = PT_ਸੂਚਕ;
        ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type) {
            ਰੋਕੋ;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ਨਹੀਂਤਾਂ ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type(pointerid, &ਸੂਚਕ_type)) {
            ਰੋਕੋ;  // oh well.
        } ਨਹੀਂਤਾਂ ਜੇ (ਸੂਚਕ_type != PT_PEN) {
            ਰੋਕੋ;  // we only care about pens here.
        }

        ਖਾਲੀ *hpointer = (ਖਾਲੀ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ਅਚਲ SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle(hpointer);
        ਜੇ (pen == 0) {
            ਰੋਕੋ;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        ਜੇ ((ਸੁਨੇਹਾ_2 == WM_POINTERCAPTURECHANGED) || !IS_ਸੂਚਕ_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ਅੰਕੜੇ->ਖਿੜਕੀ, false, false);
        }
        return_ਕੋਡ = 0;
    } ਰੋਕੋ;

    ਹਾਲਤ WM_POINTERDOWN:
    ਹਾਲਤ WM_POINTERUP:
    ਹਾਲਤ WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ਅਚਲ UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        ਸੂਚਕ_ਨਿਵੇਸ਼_TYPE ਸੂਚਕ_type = PT_ਸੂਚਕ;
        ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type || !ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Type(pointerid, &ਸੂਚਕ_type)) {
            ਰੋਕੋ;  // oh well.
        } ਨਹੀਂਤਾਂ ਜੇ ((ਸੁਨੇਹਾ_2 == WM_POINTERUPDATE) && (ਸੂਚਕ_type == PT_MOUSE)) {
            ਅੰਕੜੇ->ਆਖਰੀ_ਸੂਚਕ_update = lParam;
            return_ਕੋਡ = 0;
            ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ ਜੇ (ਸੂਚਕ_type != PT_PEN) {
            ਰੋਕੋ; // we only care about pens here.
        }

        ਖਾਲੀ *hpointer = (ਖਾਲੀ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ਅਚਲ SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle(hpointer);
        ਸੂਚਕ_PEN_INFO pen_info;
        ਜੇ (pen == 0) {
            ਰੋਕੋ;  // not a pen, or not a pen we already knew about.
        } ਨਹੀਂਤਾਂ ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Pen_Info || !ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Pen_Info(pointerid, &pen_info)) {
            ਰੋਕੋ;  // oh well.
        }

        ਅਚਲ Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

        ਅਚਲ bool istouching = IS_ਸੂਚਕ_INCONTACT_WPARAM(wParam) && IS_ਸੂਚਕ_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        ਜੇ (!istouching) {
            SDL_SendPenTouch(timestamp, pen, ਖਿੜਕੀ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ਅਚਲ ਸੂਚਕ_INFO *ਸੂਚਕ_info = &pen_info.ਸੂਚਕ_Info;
        RECT tablet_bounds, tablet_mapping;
        ਦਸ਼ਮਲਵ fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        ਜੇ (!ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Device_Rects || !ਅੰਕੜੇ->videodata->Get_ਸੂਚਕ_Device_Rects(ਸੂਚਕ_info->ਸਰੋਤ_Device, &tablet_bounds, &tablet_mapping)) {
            ਬਿੰਦੂ_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_ਮੰਜ਼ਿਲ_Client(ਅੰਕੜੇ->hwnd, &position);
            fx = (ਦਸ਼ਮਲਵ) position.x;
            fy = (ਦਸ਼ਮਲਵ) position.y;
        } ਨਹੀਂਤਾਂ {
            ਪੂਰਨ ix, iy;
            SDL_Get_ਖਿੜਕੀ_Position(ਖਿੜਕੀ, &ix, &iy);
            ਅਚਲ SDL_FPoint ਖਿੜਕੀ_pos = { (ਦਸ਼ਮਲਵ) ix, (ਦਸ਼ਮਲਵ) iy };

            ਅਚਲ ਦਸ਼ਮਲਵ facX = ਸੂਚਕ_info->ptHimetricLocationRaw.x / (ਦਸ਼ਮਲਵ) (tablet_bounds.ਸੱਜਾ );
            ਅਚਲ ਦਸ਼ਮਲਵ facY = ਸੂਚਕ_info->ptHimetricLocationRaw.y / (ਦਸ਼ਮਲਵ) (tablet_bounds.bottom);

            ਅਚਲ ਦਸ਼ਮਲਵ w = tablet_mapping.ਸੱਜਾ  - tablet_mapping.ਖੱਬਾ;
            ਅਚਲ ਦਸ਼ਮਲਵ h = tablet_mapping.bottom - tablet_mapping.ਸਿਖਰ;

            fx = (tablet_mapping.ਖੱਬਾ + (facX * w)) - ਖਿੜਕੀ_pos.x;
            fy = (tablet_mapping.ਸਿਖਰ  + (facY * h)) - ਖਿੜਕੀ_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, ਖਿੜਕੀ, fx, fy);
        SDL_SendPenButton(timestamp, pen, ਖਿੜਕੀ, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, ਖਿੜਕੀ, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        ਜੇ (pen_info.pen_ਨਕਾਬ & PEN_ਨਕਾਬ_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, ਖਿੜਕੀ, SDL_PEN_AXIS_PRESSURE, ((ਦਸ਼ਮਲਵ) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        ਜੇ (pen_info.pen_ਨਕਾਬ & PEN_ਨਕਾਬ_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, ਖਿੜਕੀ, SDL_PEN_AXIS_ROTATION, ((ਦਸ਼ਮਲਵ) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        ਜੇ (pen_info.pen_ਨਕਾਬ & PEN_ਨਕਾਬ_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, ਖਿੜਕੀ, SDL_PEN_AXIS_XTILT, ((ਦਸ਼ਮਲਵ) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        ਜੇ (pen_info.pen_ਨਕਾਬ & PEN_ਨਕਾਬ_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, ਖਿੜਕੀ, SDL_PEN_AXIS_YTILT, ((ਦਸ਼ਮਲਵ) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        ਜੇ (istouching) {
            SDL_SendPenTouch(timestamp, pen, ਖਿੜਕੀ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_ਕੋਡ = 0;
    } ਰੋਕੋ;

    ਹਾਲਤ WM_MOUSEMOVE:
    {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
            bool wish_clip_cursor = (
                ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ | SDL_ਖਿੜਕੀ_MOUSE_GRABBED) ||
                (ਖਿੜਕੀ->mouse_rect.w > 0 && ਖਿੜਕੀ->mouse_rect.h > 0)
            );
            ਜੇ (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                ਅੰਕੜੇ->clipcursor_queued = true;
            }
        }

        ਜੇ (!ਅੰਕੜੇ->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_ਮਾਪ = ਆਕਾਰ(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = ਅੰਕੜੇ->hwnd;

            ਜੇ (TrackMouseEvent(&trackMouseEvent)) {
                ਅੰਕੜੇ->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ਅੰਕੜੇ);
        }

        ਜੇ (!ਅੰਕੜੇ->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            ਜੇ (Get_Mouse_ਸੁਨੇਹਾ_ਸਰੋਤ((ULONG)Get_ਸੁਨੇਹਾ_Extra_Info()) == SDL_MOUSE_EVENT_ਸਰੋਤ_MOUSE &&
                lParam != ਅੰਕੜੇ->ਆਖਰੀ_ਸੂਚਕ_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)GET_X_LPARAM(lParam), (ਦਸ਼ਮਲਵ)GET_Y_LPARAM(lParam));
            }
        }

    } ਰੋਕੋ;

    ਹਾਲਤ WM_LBUTTONUP:
    ਹਾਲਤ WM_RBUTTONUP:
    ਹਾਲਤ WM_MBUTTONUP:
    ਹਾਲਤ WM_XBUTTONUP:
    ਹਾਲਤ WM_LBUTTONDOWN:
    ਹਾਲਤ WM_LBUTTONDBLCLK:
    ਹਾਲਤ WM_RBUTTONDOWN:
    ਹਾਲਤ WM_RBUTTONDBLCLK:
    ਹਾਲਤ WM_MBUTTONDOWN:
    ਹਾਲਤ WM_MBUTTONDBLCLK:
    ਹਾਲਤ WM_XBUTTONDOWN:
    ਹਾਲਤ WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        ਜੇ (!ਅੰਕੜੇ->videodata->raw_mouse_enabled) {
            ਜੇ (Get_Mouse_ਸੁਨੇਹਾ_ਸਰੋਤ((ULONG)Get_ਸੁਨੇਹਾ_Extra_Info()) == SDL_MOUSE_EVENT_ਸਰੋਤ_MOUSE &&
                lParam != ਅੰਕੜੇ->ਆਖਰੀ_ਸੂਚਕ_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, ਅੰਕੜੇ, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } ਰੋਕੋ;

#ਜੇ 0   // We handle raw input all at once instead of using a syscall for each mouse event
    ਹਾਲਤ WM_ਨਿਵੇਸ਼:
    {
        HRAWINPUT h_Raw_ਨਿਵੇਸ਼ = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT ਮਾਪ = ਆਕਾਰ(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ != SDL_GetKeyboardFocus()) {
            ਰੋਕੋ;
        }

        Get_Raw_ਨਿਵੇਸ਼_ਅੰਕੜੇ(h_Raw_ਨਿਵੇਸ਼, RID_ਨਿਵੇਸ਼, &inp, &ਮਾਪ, ਆਕਾਰ(RAWINPUTHEADER));
        ਜੇ (inp.ਸਿਰਲੇਖ.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_ਨਿਵੇਸ਼(WIN_GetEventTimestamp(), ਅੰਕੜੇ, inp.ਸਿਰਲੇਖ.hDevice, &inp.ਅੰਕੜੇ.mouse);
        } ਨਹੀਂਤਾਂ ਜੇ (inp.ਸਿਰਲੇਖ.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_ਨਿਵੇਸ਼(WIN_GetEventTimestamp(), ਅੰਕੜੇ, inp.ਸਿਰਲੇਖ.hDevice, &inp.ਅੰਕੜੇ.keyboard);
        }
    } ਰੋਕੋ;
#ਜੇ_ਅੰਤ

    ਹਾਲਤ WM_MOUSEWHEEL:
    ਹਾਲਤ WM_MOUSEHWHEEL:
    {
        ਜੇ (!ਅੰਕੜੇ->videodata->raw_mouse_enabled) {
            ਛੋਟਾ amount = GET_WHEEL_DELTA_WPARAM(wParam);
            ਦਸ਼ਮਲਵ fAmount = (ਦਸ਼ਮਲਵ)amount / WHEEL_DELTA;
            ਜੇ (ਸੁਨੇਹਾ_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
            } ਨਹੀਂਤਾਂ {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
            }
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_MOUSELEAVE:
        ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
            ਜੇ (SDL_GetMouseFocus() == ਅੰਕੜੇ->ਖਿੜਕੀ && !SDL_GetMouse()->relative_ਬਹੁਲਕ && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_ਸੁਨੇਹਾ_Pos();
                ਬਿੰਦੂ_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                ਜੇ (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)cursorPos.x, (ਦਸ਼ਮਲਵ)cursorPos.y);
                } ਨਹੀਂਤਾਂ {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    ਜੇ (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_TOUCH_MOUSEID, false, (ਦਸ਼ਮਲਵ)cursorPos.x, (ਦਸ਼ਮਲਵ)cursorPos.y);
                    } ਨਹੀਂਤਾਂ { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)cursorPos.x, (ਦਸ਼ਮਲਵ)cursorPos.y);
                    }
                }
            }

            ਜੇ (!SDL_GetMouse()->relative_ਬਹੁਲਕ) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        ਅੰਕੜੇ->mouse_tracked = false;

        return_ਕੋਡ = 0;
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਹਾਲਤ WM_KEYDOWN:
    ਹਾਲਤ WM_SYSKEYDOWN:
    {
        ਜੇ (Skip_Alt_Gr_ਖੱਬਾ_Control(wParam, lParam)) {
            return_ਕੋਡ = 0;
            ਰੋਕੋ;
        }

        bool virtual_ਕੁੰਜੀ = false;
        Uint16 rawcode = 0;
        SDL_Scancode ਕੋਡ = Windows_ਜਾਂਚ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScan_ਕੋਡ(lParam, wParam, &rawcode, &virtual_ਕੁੰਜੀ);

        // Detect relevant keyboard shortcuts
        ਜੇ (ਕੋਡ == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            ਜੇ (Should_Generate_ਖਿੜਕੀ_Close_On_Alt_F4()) {
                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
            }
        }

        ਜੇ (virtual_ਕੁੰਜੀ || !ਅੰਕੜੇ->videodata->raw_keyboard_enabled || ਅੰਕੜੇ->ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ) {
            SDL_Send_Keyboard_ਕੁੰਜੀ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ਕੋਡ, true);
        }
    }

        return_ਕੋਡ = 0;
        ਰੋਕੋ;

    ਹਾਲਤ WM_SYSKEYUP:
    ਹਾਲਤ WM_KEYUP:
    {
        ਜੇ (Skip_Alt_Gr_ਖੱਬਾ_Control(wParam, lParam)) {
            return_ਕੋਡ = 0;
            ਰੋਕੋ;
        }

        bool virtual_ਕੁੰਜੀ = false;
        Uint16 rawcode = 0;
        SDL_Scancode ਕੋਡ = Windows_ਜਾਂਚ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScan_ਕੋਡ(lParam, wParam, &rawcode, &virtual_ਕੁੰਜੀ);
        ਅਚਲ bool *keyboardState = SDL_GetKeyboardState(ਨਿਰਾ);

        ਜੇ (virtual_ਕੁੰਜੀ || !ਅੰਕੜੇ->videodata->raw_keyboard_enabled || ਅੰਕੜੇ->ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ) {
            ਜੇ (ਕੋਡ == SDL_SCANCODE_PRINTSCREEN && !keyboardState[ਕੋਡ]) {
                SDL_Send_Keyboard_ਕੁੰਜੀ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ਕੋਡ, true);
            }
            SDL_Send_Keyboard_ਕੁੰਜੀ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ਕੋਡ, false);
        }
    }
        return_ਕੋਡ = 0;
        ਰੋਕੋ;

    ਹਾਲਤ WM_UNICHAR:
        ਜੇ (wParam == UNICODE_NOCHAR) {
            return_ਕੋਡ = 1;
        } ਨਹੀਂਤਾਂ {
            ਜੇ (SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
                ਅੱਖਰ ਪਾਠ[5];
                ਅੱਖਰ *ਸਿਰਾ = SDL_UCS4_ਮੰਜ਼ਿਲ_UTF8((Uint32)wParam, ਪਾਠ);
                *ਸਿਰਾ = '\0';
                SDL_Send_Keyboard_ਪਾਠ(ਪਾਠ);
            }
            return_ਕੋਡ = 0;
        }
        ਰੋਕੋ;

    ਹਾਲਤ WM_CHAR:
        ਜੇ (SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            ਜੇ (IS_ਉੱਚਾ_SURROGATE(wParam)) {
                ਅੰਕੜੇ->ਉੱਚਾ_surrogate = (WCHAR)wParam;
            } ਨਹੀਂਤਾਂ {
                WCHAR utf16[3];

                utf16[0] = ਅੰਕੜੇ->ਉੱਚਾ_surrogate ? ਅੰਕੜੇ->ਉੱਚਾ_surrogate : (WCHAR)wParam;
                utf16[1] = ਅੰਕੜੇ->ਉੱਚਾ_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                ਅੱਖਰ utf8[5];
                ਪੂਰਨ ਨਤੀਜਾ = WIN_Wide_Char_ਮੰਜ਼ਿਲ_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, ਆਕਾਰ(utf8), ਨਿਰਾ, ਨਿਰਾ);
                ਜੇ (ਨਤੀਜਾ > 0) {
                    SDL_Send_Keyboard_ਪਾਠ(utf8);
                }
                ਅੰਕੜੇ->ਉੱਚਾ_surrogate = L'\0';
            }
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->ਉੱਚਾ_surrogate = L'\0';
        }

        return_ਕੋਡ = 0;
        ਰੋਕੋ;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WM_INPUTLANGCHANGE
    ਹਾਲਤ WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_ਕੋਡ = 1;
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ // WM_INPUTLANGCHANGE

    ਹਾਲਤ WM_NCLBUTTONDOWN:
    {
        ਅੰਕੜੇ->ਵਿੱਚ_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        ਜੇ (Send_ਸੁਨੇਹਾ(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            ਬਿੰਦੂ_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &cursorPos);
            Post_ਸੁਨੇਹਾ(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_CAPTURECHANGED:
    {
        ਅੰਕੜੇ->ਵਿੱਚ_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ਅੰਕੜੇ);
    } ਰੋਕੋ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WM_GETMINMAXINFO
    ਹਾਲਤ WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT ਮਾਪ;
        ਪੂਰਨ x, y;
        ਪੂਰਨ w, h;
        ਪੂਰਨ min_w, min_h;
        ਪੂਰਨ max_w, max_h;
        BOOL constrain_max_ਮਾਪ;

        // If this is an expected size change, allow it
        ਜੇ (ਅੰਕੜੇ->expected_resize) {
            ਰੋਕੋ;
        }

        // Get the current position of our window
        Get_ਖਿੜਕੀ_Rect(hwnd, &ਮਾਪ);
        x = ਮਾਪ.ਖੱਬਾ;
        y = ਮਾਪ.ਸਿਖਰ;

        // Calculate current size of our window
        SDL_Get_ਖਿੜਕੀ_ਮਾਪ(ਅੰਕੜੇ->ਖਿੜਕੀ, &w, &h);
        SDL_Get_ਖਿੜਕੀ_Minimum_ਮਾਪ(ਅੰਕੜੇ->ਖਿੜਕੀ, &min_w, &min_h);
        SDL_Get_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(ਅੰਕੜੇ->ਖਿੜਕੀ, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        ਜੇ (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_ਮਾਪ = TRUE;
        } ਨਹੀਂਤਾਂ {
            constrain_max_ਮਾਪ = FALSE;
        }

        ਜੇ (!(SDL_Get_ਖਿੜਕੀ_Flags(ਅੰਕੜੇ->ਖਿੜਕੀ) & SDL_ਖਿੜਕੀ_BORDERLESS) && !SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
            ਮਾਪ.ਸਿਖਰ = 0;
            ਮਾਪ.ਖੱਬਾ = 0;
            ਮਾਪ.bottom = h;
            ਮਾਪ.ਸੱਜਾ = w;
            WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(hwnd, &ਮਾਪ, 0);
            w = ਮਾਪ.ਸੱਜਾ - ਮਾਪ.ਖੱਬਾ;
            h = ਮਾਪ.bottom - ਮਾਪ.ਸਿਖਰ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#ਜੇ_ਅੰਤ
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        ਜੇ (SDL_Get_ਖਿੜਕੀ_Flags(ਅੰਕੜੇ->ਖਿੜਕੀ) & SDL_ਖਿੜਕੀ_RESIZABLE) {
            ਜੇ (SDL_Get_ਖਿੜਕੀ_Flags(ਅੰਕੜੇ->ਖਿੜਕੀ) & SDL_ਖਿੜਕੀ_BORDERLESS) {
                ਪੂਰਨ screenW = GetSystemMetrics(SM_CXSCREEN);
                ਪੂਰਨ screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_ਮਾਪ.x = SDL_max(w, screenW);
                info->pt_Max_ਮਾਪ.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_ਮਾਪ.x = (LONG)w + min_w;
            info->pt_Min_Track_ਮਾਪ.y = (LONG)h + min_h;
            ਜੇ (constrain_max_ਮਾਪ) {
                info->pt_Max_Track_ਮਾਪ.x = (LONG)w + max_w;
                info->pt_Max_Track_ਮਾਪ.y = (LONG)h + max_h;
            }
        } ਨਹੀਂਤਾਂ {
            info->pt_Max_ਮਾਪ.x = w;
            info->pt_Max_ਮਾਪ.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_ਮਾਪ.x = w;
            info->pt_Min_Track_ਮਾਪ.y = h;
            info->pt_Max_Track_ਮਾਪ.x = w;
            info->pt_Max_Track_ਮਾਪ.y = h;
        }
    }
        return_ਕੋਡ = 0;
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ // WM_GETMINMAXINFO

    ਹਾਲਤ WM_WINDOWPOSCHANGING:

        ਜੇ (ਅੰਕੜੇ->expected_resize) {
            return_ਕੋਡ = 0;
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਵਿੱਚ_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            ਜੇ (ਅੰਕੜੇ->ਆਖਰੀ_modal_ਚੌੜਾਈ == windowpos->cx && ਅੰਕੜੇ->ਆਖਰੀ_modal_ਉਚਾਈ == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            ਅੰਕੜੇ->ਆਖਰੀ_modal_ਚੌੜਾਈ = windowpos->cx;
            ਅੰਕੜੇ->ਆਖਰੀ_modal_ਉਚਾਈ = windowpos->cy;

            return_ਕੋਡ = 0;
        }
        ਰੋਕੋ;

    ਹਾਲਤ WM_WINDOWPOSCHANGED:
    {
        SDL_ਖਿੜਕੀ *win;
        ਅਚਲ SDL_DisplayID original_displayID = ਅੰਕੜੇ->ਖਿੜਕੀ->displayID;
        ਅਚਲ WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        ਪੂਰਨ x, y;
        ਪੂਰਨ w, h;

        ਜੇ (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        ਜੇ (iconic) {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
        } ਨਹੀਂਤਾਂ ਜੇ (zoomed) {
            ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
            }
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MAXIMIZED, 0, 0);
            ਅੰਕੜੇ->force_ws_maximizebox = true;
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED)) {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
                ਅੰਕੜੇ->force_ws_maximizebox = false;
                WIN_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_GetVideoDevice(), ਅੰਕੜੇ->ਖਿੜਕੀ, !!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE));
            }
        }

        ਜੇ (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        ਜੇ (iconic) {
            ਰੋਕੋ;
        }

        ਜੇ (ਅੰਕੜੇ->initializing) {
            ਰੋਕੋ;
        }

        ਜੇ (!ਅੰਕੜੇ->disable_move_ਮਾਪ_events) {
            ਜੇ (GetClientRect(hwnd, &rect) && WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
                Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT) &rect);
                Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.ਖੱਬਾ;
                y = rect.ਸਿਖਰ;

                SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(ਅੰਕੜੇ->ਖਿੜਕੀ, x, y, &x, &y);
                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            ਜੇ (GetClientRect(hwnd, &rect) && WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
                w = rect.ਸੱਜਾ;
                h = rect.bottom;

                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(ਅੰਕੜੇ->ਖਿੜਕੀ);

        // Update the window display position
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_ਖਿੜਕੀ_ICCProfile(ਅੰਕੜੇ->ਖਿੜਕੀ, true);
        }

        // Update the position of any child windows
        ਲਈ (win = ਅੰਕੜੇ->ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; win; win = win->ਅਗਲਾ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(win) && !(win->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
                WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } ਰੋਕੋ;

    ਹਾਲਤ WM_ENTERSIZEMOVE:
    ਹਾਲਤ WM_ENTERMENULOOP:
    {
        ਜੇ (g_Windows_ਸੁਨੇਹਾ_Hook) {
            ਜੇ (!Dispatch_Modal_Loop_ਸੁਨੇਹਾ_Hook(&hwnd, &ਸੁਨੇਹਾ_2, &wParam, &lParam)) {
                ਵਾਪਸ 0;
            }
        }

        ++ਅੰਕੜੇ->ਵਿੱਚ_modal_loop;
        ਜੇ (ਅੰਕੜੇ->ਵਿੱਚ_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_ਖਿੜਕੀ_Rect(ਅੰਕੜੇ->hwnd, &rect);
            ਅੰਕੜੇ->ਆਖਰੀ_modal_ਚੌੜਾਈ = rect.ਸੱਜਾ - rect.ਖੱਬਾ;
            ਅੰਕੜੇ->ਆਖਰੀ_modal_ਉਚਾਈ = rect.bottom - rect.ਸਿਖਰ;

            ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਖੱਬਾ = ਅੰਕੜੇ->ਖਿੜਕੀ->x;
            ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸੱਜਾ = ਅੰਕੜੇ->ਖਿੜਕੀ->x + ਅੰਕੜੇ->ਖਿੜਕੀ->w;
            ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸਿਖਰ = ਅੰਕੜੇ->ਖਿੜਕੀ->y;
            ਅੰਕੜੇ->initial_ਮਾਪ_rect.bottom = ਅੰਕੜੇ->ਖਿੜਕੀ->y + ਅੰਕੜੇ->ਖਿੜਕੀ->h;

            ਸੈੱਟ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, ਨਿਰਾ);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_TIMER:
    {
        ਜੇ (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_ਖਿੜਕੀ_ਜੀਵਤ_Resize_Update(ਅੰਕੜੇ->ਖਿੜਕੀ);

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ਜੇ 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            ਜੇ (ਅੰਕੜੇ->videodata->DwmFlush) {
                ਅੰਕੜੇ->videodata->DwmFlush();
            }
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
            ਵਾਪਸ 0;
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_EXITSIZEMOVE:
    ਹਾਲਤ WM_EXITMENULOOP:
    {
        --ਅੰਕੜੇ->ਵਿੱਚ_modal_loop;
        ਜੇ (ਅੰਕੜੇ->ਵਿੱਚ_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_SIZING:
        {
            WPARAM ਕਿਨਾਰਾ = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool ਤਾਲਾ_aspect_ਅਨੁਪਾਤ = (ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect == ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            ਦਸ਼ਮਲਵ new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect <= 0 && ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect <= 0) {
                ਰੋਕੋ;
            }

            // unadjust the dragRect from the window rect to the client rect
            ਸੈੱਟ_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&rc);
            ਜੇ (!Adjust_ਖਿੜਕੀ_Rect_Ex(&rc, Get_ਖਿੜਕੀ_Style(hwnd), GetMenu(hwnd) != ਨਿਰਾ, Get_ਖਿੜਕੀ_Ex_Style(hwnd))) {
                ਰੋਕੋ;
            }

            clientDragRect.ਖੱਬਾ -= rc.ਖੱਬਾ;
            clientDragRect.ਸਿਖਰ -= rc.ਸਿਖਰ;
            clientDragRect.ਸੱਜਾ -= rc.ਸੱਜਾ;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ਸੱਜਾ - clientDragRect.ਖੱਬਾ;
            h = clientDragRect.bottom - clientDragRect.ਸਿਖਰ;
            new_aspect = w / (ਦਸ਼ਮਲਵ)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            ਜੇ (ਤਾਲਾ_aspect_ਅਨੁਪਾਤ) {
                ਚੋਣ (ਕਿਨਾਰਾ) {
                ਹਾਲਤ WMSZ_ਖੱਬਾ:
                ਹਾਲਤ WMSZ_ਸੱਜਾ:
                    h = (ਪੂਰਨ)SDL_roundf(w / ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect);
                    ਰੋਕੋ;
                ਮੂਲ:
                    // resizing via corners or top or bottom
                    w = (ਪੂਰਨ)SDL_roundf(h * ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect);
                    ਰੋਕੋ;
                }
            } ਨਹੀਂਤਾਂ {
                ਚੋਣ (ਕਿਨਾਰਾ) {
                ਹਾਲਤ WMSZ_ਖੱਬਾ:
                ਹਾਲਤ WMSZ_ਸੱਜਾ:
                    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect > 0.0f && new_aspect > ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect) {
                        w = (ਪੂਰਨ)SDL_roundf(h * ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect);
                    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect > 0.0f && new_aspect < ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect) {
                        w = (ਪੂਰਨ)SDL_roundf(h * ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect);
                    }
                    ਰੋਕੋ;
                ਹਾਲਤ WMSZ_ਸਿਖਰ:
                ਹਾਲਤ WMSZ_BOTTOM:
                    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect > 0.0f && new_aspect < ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect) {
                        h = (ਪੂਰਨ)SDL_roundf(w / ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect);
                    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect > 0.0f && new_aspect > ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect) {
                        h = (ਪੂਰਨ)SDL_roundf(w / ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect);
                    }
                    ਰੋਕੋ;

                ਮੂਲ:
                    // resizing via corners
                    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect > 0.0f && new_aspect > ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect) {
                        w = (ਪੂਰਨ)SDL_roundf(h * ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect);
                    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect > 0.0f && new_aspect < ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect) {
                        h = (ਪੂਰਨ)SDL_roundf(w / ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect);
                    }
                    ਰੋਕੋ;
                }
            }

            ਚੋਣ (ਕਿਨਾਰਾ) {
            ਹਾਲਤ WMSZ_ਖੱਬਾ:
                clientDragRect.ਖੱਬਾ = clientDragRect.ਸੱਜਾ - w;
                ਜੇ (ਤਾਲਾ_aspect_ਅਨੁਪਾਤ) {
                    clientDragRect.ਸਿਖਰ = (ਅੰਕੜੇ->initial_ਮਾਪ_rect.bottom + ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸਿਖਰ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.ਸਿਖਰ;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_BOTTOMLEFT:
                clientDragRect.ਖੱਬਾ = clientDragRect.ਸੱਜਾ - w;
                clientDragRect.bottom = h + clientDragRect.ਸਿਖਰ;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_ਸੱਜਾ:
                clientDragRect.ਸੱਜਾ = w + clientDragRect.ਖੱਬਾ;
                ਜੇ (ਤਾਲਾ_aspect_ਅਨੁਪਾਤ) {
                    clientDragRect.ਸਿਖਰ = (ਅੰਕੜੇ->initial_ਮਾਪ_rect.bottom + ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸਿਖਰ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.ਸਿਖਰ;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_TOPRIGHT:
                clientDragRect.ਸੱਜਾ = w + clientDragRect.ਖੱਬਾ;
                clientDragRect.ਸਿਖਰ = clientDragRect.bottom - h;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_ਸਿਖਰ:
                ਜੇ (ਤਾਲਾ_aspect_ਅਨੁਪਾਤ) {
                    clientDragRect.ਖੱਬਾ = (ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸੱਜਾ + ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਖੱਬਾ - w) / 2;
                }
                clientDragRect.ਸੱਜਾ = w + clientDragRect.ਖੱਬਾ;
                clientDragRect.ਸਿਖਰ = clientDragRect.bottom - h;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_TOPLEFT:
                clientDragRect.ਖੱਬਾ = clientDragRect.ਸੱਜਾ - w;
                clientDragRect.ਸਿਖਰ = clientDragRect.bottom - h;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_BOTTOM:
                ਜੇ (ਤਾਲਾ_aspect_ਅਨੁਪਾਤ) {
                    clientDragRect.ਖੱਬਾ = (ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਸੱਜਾ + ਅੰਕੜੇ->initial_ਮਾਪ_rect.ਖੱਬਾ - w) / 2;
                }
                clientDragRect.ਸੱਜਾ = w + clientDragRect.ਖੱਬਾ;
                clientDragRect.bottom = h + clientDragRect.ਸਿਖਰ;
                ਰੋਕੋ;
            ਹਾਲਤ WMSZ_BOTTOMRIGHT:
                clientDragRect.ਸੱਜਾ = w + clientDragRect.ਖੱਬਾ;
                clientDragRect.bottom = h + clientDragRect.ਸਿਖਰ;
                ਰੋਕੋ;
            }

            // convert the client rect to a window rect
            ਜੇ (!Adjust_ਖਿੜਕੀ_Rect_Ex(&clientDragRect, Get_ਖਿੜਕੀ_Style(hwnd), GetMenu(hwnd) != ਨਿਰਾ, Get_ਖਿੜਕੀ_Ex_Style(hwnd))) {
                ਰੋਕੋ;
            }

            *dragRect = clientDragRect;
        }
        ਰੋਕੋ;

    ਹਾਲਤ WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        ਜੇ (hittest == HTCLIENT) {
            ਸੈੱਟ_Cursor(SDL_cursor);
            return_ਕੋਡ = TRUE;
        } ਨਹੀਂਤਾਂ ਜੇ (!g_ਖਿੜਕੀ_ਚੌਖਟਾ_Usable_While_Cursor_Hidden && !SDL_cursor) {
            ਸੈੱਟ_Cursor(ਨਿਰਾ);
            return_ਕੋਡ = TRUE;
        }
    } ਰੋਕੋ;

        // We were occluded, refresh our display
    ਹਾਲਤ WM_PAINT:
    {
        RECT rect;
        ਜੇ (GetUpdateRect(hwnd, &rect, FALSE)) {
            ਅਚਲ LONG style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            ਜੇ (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                ਸਿਰਾ_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, ਨਿਰਾ);
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
        }
    }
        return_ਕੋਡ = 0;
        ਰੋਕੋ;

        // We'll do our own drawing, prevent flicker
    ਹਾਲਤ WM_ERASEBKGND:
        ਜੇ (Should_Clear_ਖਿੜਕੀ_On_Erase_Background(ਅੰਕੜੇ)) {
            RECT client_rect;
            HBRUSH brush;
            ਅੰਕੜੇ->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        ਵਾਪਸ 1;

    ਹਾਲਤ WM_SYSCOMMAND:
    {
        ਜੇ (!g_WindowsEnableMenuMnemonics) {
            ਜੇ ((wParam & 0xFFF0) == SC_KEYMENU) {
                ਵਾਪਸ 0;
            }
        }

#ਜੇ defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        ਜੇ ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            ਜੇ (SDL_GetVideoDevice()->suspend_screensaver) {
                ਵਾਪਸ 0;
            }
        }
#ਜੇ_ਅੰਤ // System has screensaver support
    } ਰੋਕੋ;

    ਹਾਲਤ WM_CLOSE:
    {
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
    }
        return_ਕੋਡ = 0;
        ਰੋਕੋ;

    ਹਾਲਤ WM_TOUCH:
        ਜੇ (ਅੰਕੜੇ->videodata->Get_Touch_ਨਿਵੇਸ਼_Info && ਅੰਕੜੇ->videodata->Close_Touch_ਨਿਵੇਸ਼_Handle) {
            UINT i, ਅੰਕ_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, ਅੰਕ_inputs, &isstack);
            ਜੇ (inputs && ਅੰਕੜੇ->videodata->Get_Touch_ਨਿਵੇਸ਼_Info((HTOUCHINPUT)lParam, ਅੰਕ_inputs, inputs, ਆਕਾਰ(TOUCHINPUT))) {
                RECT rect;
                ਦਸ਼ਮਲਵ x, y;

                ਜੇ (!GetClientRect(hwnd, &rect) || !WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
                    ਜੇ (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    ਰੋਕੋ;
                }
                Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT)&rect);
                Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.ਸਿਖਰ *= 100;
                rect.ਖੱਬਾ *= 100;
                rect.bottom *= 100;
                rect.ਸੱਜਾ *= 100;

                ਲਈ (i = 0; i < ਅੰਕ_inputs; ++i) {
                    PTOUCHINPUT ਨਿਵੇਸ਼ = &inputs[i];
                    ਅਚਲ ਪੂਰਨ w = (rect.ਸੱਜਾ - rect.ਖੱਬਾ);
                    ਅਚਲ ਪੂਰਨ h = (rect.bottom - rect.ਸਿਖਰ);

                    ਅਚਲ SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)ਨਿਵੇਸ਼->h_ਸਰੋਤ);
                    ਅਚਲ SDL_FingerID fingerId = (ਨਿਵੇਸ਼->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    ਜੇ (SDL_ਜੋੜੋ_Touch(touchId, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, (ਨਿਵੇਸ਼->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        ਜਾਰੀ;
                    }

                    // Get the normalized coordinates for the window
                    ਜੇ (w <= 1) {
                        x = 0.5f;
                    } ਨਹੀਂਤਾਂ {
                        x = (ਦਸ਼ਮਲਵ)(ਨਿਵੇਸ਼->x - rect.ਖੱਬਾ) / (w - 1);
                    }
                    ਜੇ (h <= 1) {
                        y = 0.5f;
                    } ਨਹੀਂਤਾਂ {
                        y = (ਦਸ਼ਮਲਵ)(ਨਿਵੇਸ਼->y - rect.ਸਿਖਰ) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    ਜੇ (ਨਿਵੇਸ਼->dwFlags & TOUCHEVENTF_ਥੱਲੇ) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, 1.0f);
                    }
                    ਜੇ (ਨਿਵੇਸ਼->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, ਅੰਕੜੇ->ਖਿੜਕੀ, x, y, 1.0f);
                    }
                    ਜੇ (ਨਿਵੇਸ਼->dwFlags & TOUCHEVENTF_ਉੱਪਰ) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            ਅੰਕੜੇ->videodata->Close_Touch_ਨਿਵੇਸ਼_Handle((HTOUCHINPUT)lParam);
            ਵਾਪਸ 0;
        }
        ਰੋਕੋ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_TPCSHRD_H

    ਹਾਲਤ WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        ਵਾਪਸ TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#ਜੇ_ਅੰਤ // HAVE_TPCSHRD_H

    ਹਾਲਤ WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT ਗਿਣਤੀ_2 = DragQueryFile(drop, 0xFFFFFFFF, ਨਿਰਾ, 0);
        ਲਈ (i = 0; i < ਗਿਣਤੀ_2; ++i) {
            UINT ਮਾਪ = DragQueryFile(drop, i, ਨਿਰਾ, 0) + 1;
            LPTSTR ਬਫਰ_2 = (LPTSTR)SDL_malloc(ਆਕਾਰ(TCHAR) * ਮਾਪ);
            ਜੇ (ਬਫਰ_2) {
                ਜੇ (DragQueryFile(drop, i, ਬਫਰ_2, ਮਾਪ)) {
                    ਅੱਖਰ *file = WIN_String_ਮੰਜ਼ਿਲ_UTF8(ਬਫਰ_2);
                    SDL_SendDropFile(ਅੰਕੜੇ->ਖਿੜਕੀ, ਨਿਰਾ, file);
                    SDL_free(file);
                }
                SDL_free(ਬਫਰ_2);
            }
        }
        SDL_SendDropComplete(ਅੰਕੜੇ->ਖਿੜਕੀ);
        Drag_ਅੰਤ(drop);
        ਵਾਪਸ 0;
    }

    ਹਾਲਤ WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } ਰੋਕੋ;

    ਹਾਲਤ WM_NCCALCSIZE:
    {
        SDL_ਖਿੜਕੀ_Flags ਖਿੜਕੀ_flags = ਅੰਕੜੇ->ਖਿੜਕੀ->flags;
        ਜੇ (wParam == TRUE && (ਖਿੜਕੀ_flags & SDL_ਖਿੜਕੀ_BORDERLESS) && !(ਖਿੜਕੀ_flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            ਜੇ (Get_ਖਿੜਕੀ_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_ਖਿੜਕੀ(hwnd, MONITOR_DEFAULTTONULL);
                ਜੇ (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ਅਚਲ ਬਿੰਦੂ_2 pt = { ਅੰਕੜੇ->ਖਿੜਕੀ->windowed.x, ਅੰਕੜੇ->ਖਿੜਕੀ->windowed.y };
                    hMonitor = Monitor_From_ਬਿੰਦੂ(pt, MONITOR_DEFAULTTONEAREST);
                }
                ਜੇ (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_ਮਾਪ = ਆਕਾਰ(info);
                    ਜੇ (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } ਨਹੀਂਤਾਂ ਜੇ (!(ਖਿੜਕੀ_flags & SDL_ਖਿੜਕੀ_RESIZABLE) && !ਅੰਕੜੇ->force_ws_maximizebox) {
                ਪੂਰਨ w, h;
                ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending) {
                    w = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.w;
                    h = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.h;
                } ਨਹੀਂਤਾਂ {
                    w = ਅੰਕੜੇ->ਖਿੜਕੀ->floating.w;
                    h = ਅੰਕੜੇ->ਖਿੜਕੀ->floating.h;
                }
                params->rgrc[0].ਸੱਜਾ = params->rgrc[0].ਖੱਬਾ + w;
                params->rgrc[0].bottom = params->rgrc[0].ਸਿਖਰ + h;
            }
            ਵਾਪਸ 0;
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_NCHITTEST:
    {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TOOLTIP) {
            ਵਾਪਸ HTTRANSPARENT;
        }

        ਜੇ (ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) {
            ਬਿੰਦੂ_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            ਜੇ (Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &winpoint)) {
                SDL_ਬਿੰਦੂ ਬਿੰਦੂ;
                SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ rc;
                ਬਿੰਦੂ.x = winpoint.x;
                ਬਿੰਦੂ.y = winpoint.y;
                rc = ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test(ਖਿੜਕੀ, &ਬਿੰਦੂ, ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test_ਅੰਕੜੇ);
                ਚੋਣ (rc) {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POST_ਪ੍ਰਾਪਤੀ_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_TEST, 0, 0); \
        ਵਾਪਸ ret;                                                        \
    }
                ਹਾਲਤ SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(ਨਿਰਾ, ਨਿਰਾ);
                    ਜੇ (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
                        ਵਾਪਸ HTCLIENT;
                    }

                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTCAPTION);
                }
                ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTTOPLEFT);
                ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTTOP);
                ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTTOPRIGHT);
                ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTRIGHT);
                ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTBOTTOMRIGHT);
                ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTBOTTOM);
                ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTBOTTOMLEFT);
                ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ:
                    POST_ਪ੍ਰਾਪਤੀ_TEST(HTLEFT);
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ POST_ਪ੍ਰਾਪਤੀ_TEST
                ਹਾਲਤ SDL_HITTEST_ਸਾਧਾਰਨ:
                    ਵਾਪਸ HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } ਰੋਕੋ;

    ਹਾਲਤ WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        ਜੇ (ਅੰਕੜੇ->videodata->Get_Dpi_For_ਖਿੜਕੀ && ਅੰਕੜੇ->videodata->Adjust_ਖਿੜਕੀ_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ਅਚਲ ਪੂਰਨ ਅਗਲਾ_DPI = (ਪੂਰਨ)wParam;
            ਅਚਲ ਪੂਰਨ prevDPI = (ਪੂਰਨ)ਅੰਕੜੇ->videodata->Get_Dpi_For_ਖਿੜਕੀ(hwnd);
            ਮਾਪ_3 *ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ = (ਮਾਪ_3 *)lParam;

            ਪੂਰਨ ਚੌਖਟਾ_w, ਚੌਖਟਾ_h;
            ਪੂਰਨ query_client_w_win, query_client_h_win;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, ਅਗਲਾ_DPI, ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cx, ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cy);
#ਜੇ_ਅੰਤ

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) && !SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
                    WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                ਚੌਖਟਾ_w = -rect.ਖੱਬਾ + rect.ਸੱਜਾ;
                ਚੌਖਟਾ_h = -rect.ਸਿਖਰ + rect.bottom;

                query_client_w_win = ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cx - ਚੌਖਟਾ_w;
                query_client_h_win = ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cy - ਚੌਖਟਾ_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ਸੱਜਾ = query_client_w_win;
                rect.bottom = query_client_h_win;

                ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) && !SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
                    WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(hwnd, &rect, ਅਗਲਾ_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cx = rect.ਸੱਜਾ - rect.ਖੱਬਾ;
                ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cy = rect.bottom - rect.ਸਿਖਰ;
            }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cx, ਮਾਪ_ਵਿੱਚ_ਬਾਹਰਲਾ->cy);
#ਜੇ_ਅੰਤ
            ਵਾਪਸ TRUE;
        }
        ਰੋਕੋ;

    ਹਾਲਤ WM_DPICHANGED:
        // Windows 8.1+
        {
            ਅਚਲ ਪੂਰਨ newDPI = HIWORD(wParam);
            RECT *ਅਚਲ suggestedRect = (RECT *)lParam;
            ਪੂਰਨ w, h;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->ਖੱਬਾ, suggestedRect->ਸਿਖਰ, suggestedRect->ਸੱਜਾ - suggestedRect->ਖੱਬਾ, suggestedRect->bottom - suggestedRect->ਸਿਖਰ);
#ਜੇ_ਅੰਤ

            ਜੇ (ਅੰਕੜੇ->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#ਜੇ_ਅੰਤ
                ਵਾਪਸ 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ਸੱਜਾ = ਅੰਕੜੇ->ਖਿੜਕੀ->w;
                rect.bottom = ਅੰਕੜੇ->ਖਿੜਕੀ->h;

                ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS)) {
                    WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.ਸੱਜਾ - rect.ਖੱਬਾ;
                h = rect.bottom - rect.ਸਿਖਰ;
            }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    ਅੰਕੜੇ->ਖਿੜਕੀ->w, ਅੰਕੜੇ->ਖਿੜਕੀ->h,
                    suggestedRect->ਖੱਬਾ, suggestedRect->ਸਿਖਰ, w, h);
#ਜੇ_ਅੰਤ

            ਅੰਕੜੇ->expected_resize = true;
            ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd,
                         ਨਿਰਾ,
                         suggestedRect->ਖੱਬਾ,
                         suggestedRect->ਸਿਖਰ,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            ਅੰਕੜੇ->expected_resize = false;
            ਵਾਪਸ 0;
        }

    ਹਾਲਤ WM_SETTINGCHANGE:
        ਜੇ (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_ਸੈੱਟ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_ਬਹੁਲਕ_For_HWND(hwnd);
        }
        ਜੇ (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        ਜੇ (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        ਰੋਕੋ;
#ਨਹੀਂਤਾਂ
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    ਹਾਲਤ WM_ਮਾਪ:
    {
        RECT rect;
        ਪੂਰਨ w, h;

        ਜੇ (GetClientRect(hwnd, &rect) && WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
            w = rect.ਸੱਜਾ;
            h = rect.bottom;
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, w, h);
        }
    } ਰੋਕੋ;
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਮੂਲ:
        ਰੋਕੋ;
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (ਸੁਨੇਹਾ_2 && ਸੁਨੇਹਾ_2 == ਅੰਕੜੇ->videodata->WM_TASKBAR_BUTTON_CREATED) {
        ਅੰਕੜੇ->taskbar_button_created = true;
        WIN_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ(SDL_GetVideoDevice(), ਅੰਕੜੇ->ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ

    // If there's a window proc, assume it's going to handle messages
    ਜੇ (ਅੰਕੜੇ->wndproc) {
        ਵਾਪਸ Call_ਖਿੜਕੀ_Proc(ਅੰਕੜੇ->wndproc, hwnd, ਸੁਨੇਹਾ_2, wParam, lParam);
    } ਨਹੀਂਤਾਂ ਜੇ (return_ਕੋਡ >= 0) {
        ਵਾਪਸ return_ਕੋਡ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ Call_ਖਿੜਕੀ_Proc(Def_ਖਿੜਕੀ_Proc, hwnd, ਸੁਨੇਹਾ_2, wParam, lParam);
    }
}

ਪੂਰਨ WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    ਜੇ (g_Windows_Enable_ਸੁਨੇਹਾ_Loop) {
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_ਮੰਜ਼ਿਲ_MS(timeoutNS);
        ret = ਸੁਨੇਹਾ_Wait_For_ਗੁਣਜ_Objects(0, ਨਿਰਾ, FALSE, timeout, QS_ALLINPUT);
        ਜੇ (ret == WAIT_OBJECT_0) {
            ਵਾਪਸ 1;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ 0;
        }
#ਨਹੀਂਤਾਂ
        // MsgWaitForMultipleObjects is desktop-only.
        ਸੁਨੇਹਾ_3 ਸੁਨੇਹਾ_2;
        BOOL ਸੁਨੇਹਾ_ਨਤੀਜਾ;
        UINT_PTR timer_id = 0;
        ਜੇ (timeoutNS > 0) {
            timer_id = ਸੈੱਟ_Timer(ਨਿਰਾ, 0, (UINT)SDL_NS_ਮੰਜ਼ਿਲ_MS(timeoutNS), ਨਿਰਾ);
            ਸੁਨੇਹਾ_ਨਤੀਜਾ = Get_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, 0, 0, 0);
            KillTimer(ਨਿਰਾ, timer_id);
        } ਨਹੀਂਤਾਂ ਜੇ (timeoutNS == 0) {
            ਸੁਨੇਹਾ_ਨਤੀਜਾ = Peek_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, ਨਿਰਾ, 0, 0, PM_REMOVE);
        } ਨਹੀਂਤਾਂ {
            ਸੁਨੇਹਾ_ਨਤੀਜਾ = Get_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, 0, 0, 0);
        }
        ਜੇ (ਸੁਨੇਹਾ_ਨਤੀਜਾ) {
            ਜੇ (ਸੁਨੇਹਾ_2.ਸੁਨੇਹਾ == WM_TIMER && !ਸੁਨੇਹਾ_2.hwnd && ਸੁਨੇਹਾ_2.wParam == timer_id) {
                ਵਾਪਸ 0;
            }
            ਜੇ (g_Windows_ਸੁਨੇਹਾ_Hook) {
                ਜੇ (!g_Windows_ਸੁਨੇਹਾ_Hook(g_Windows_ਸੁਨੇਹਾ_Hook_ਅੰਕੜੇ, &ਸੁਨੇਹਾ_2)) {
                    ਵਾਪਸ 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
            Dispatch_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
            ਵਾਪਸ 1;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ 0;
        }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } ਨਹੀਂਤਾਂ {
        // Fail the wait so the caller falls back to polling
        ਵਾਪਸ -1;
    }
}

ਖਾਲੀ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Post_ਸੁਨੇਹਾ(ਅੰਕੜੇ->hwnd, ਅੰਕੜੇ->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
ਖਾਲੀ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    ਸੁਨੇਹਾ_3 ਸੁਨੇਹਾ_2;

    ਜੇ (g_Windows_Enable_ਸੁਨੇਹਾ_Loop) {
        SDL_processing_messages = true;

        ਜਦੋਂ (Peek_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_ਸੈੱਟ_ਸੁਨੇਹਾ_Tick(ਸੁਨੇਹਾ_2.ਸਮਾਂ);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
            Dispatch_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
        }

        SDL_processing_messages = false;
    }
}

ਖਾਲੀ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    ਸੁਨੇਹਾ_3 ਸੁਨੇਹਾ_2;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ਹਦਾਇਤ warning(ਧੱਕੋ)
#ਹਦਾਇਤ warning(disable : 28159)
#ਜੇ_ਅੰਤ
    DWORD ਸਿਰਾ_ticks = Get_Tick_ਗਿਣਤੀ() + 1;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਕੱਢੋ)
#ਜੇ_ਅੰਤ
    ਪੂਰਨ new_messages = 0;

    ਜੇ (_this->ਅੰਦਰੂਨੀ->gameinput_context) {
        WIN_Update_Game_ਨਿਵੇਸ਼(_this);
    }

    ਜੇ (g_Windows_Enable_ਸੁਨੇਹਾ_Loop) {
        SDL_processing_messages = true;

        ਜਦੋਂ (Peek_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, ਨਿਰਾ, 0, 0, PM_REMOVE)) {
            ਜੇ (g_Windows_ਸੁਨੇਹਾ_Hook) {
                ਜੇ (!g_Windows_ਸੁਨੇਹਾ_Hook(g_Windows_ਸੁਨੇਹਾ_Hook_ਅੰਕੜੇ, &ਸੁਨੇਹਾ_2)) {
                    ਜਾਰੀ;
                }
            }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            ਜੇ (ਸੁਨੇਹਾ_2.ਸੁਨੇਹਾ == WM_MOUSEMOVE && SDL_ਆਖਰੀ_warp_ਸਮਾਂ) {
                ਜੇ (!SDL_TICKS_PASSED(ਸੁਨੇਹਾ_2.ਸਮਾਂ, (SDL_ਆਖਰੀ_warp_ਸਮਾਂ + 1))) {
                    ਜਾਰੀ;
                }

                // This mouse message happened after the warp
                SDL_ਆਖਰੀ_warp_ਸਮਾਂ = 0;
            }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_ਸੈੱਟ_ਸੁਨੇਹਾ_Tick(ਸੁਨੇਹਾ_2.ਸਮਾਂ);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
            Dispatch_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            ਜੇ (SDL_TICKS_PASSED(ਸੁਨੇਹਾ_2.ਸਮਾਂ, ਸਿਰਾ_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ਅਚਲ ਪੂਰਨ MAX_NEW_MESSAGES = 3;
                ++new_messages;
                ਜੇ (new_messages > MAX_NEW_MESSAGES) {
                    ਰੋਕੋ;
                }
            }
        }

        SDL_processing_messages = false;
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ਅਚਲ bool *keystate = SDL_GetKeyboardState(ਨਿਰਾ);
    ਜੇ (keystate[SDL_SCANCODE_LSHIFT] && !(Get_ਕੁੰਜੀ_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    ਜੇ (keystate[SDL_SCANCODE_RSHIFT] && !(Get_ਕੁੰਜੀ_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_ਖਿੜਕੀ *focus_ਖਿੜਕੀ = SDL_GetKeyboardFocus();
    ਜੇ (!focus_ਖਿੜਕੀ || !(focus_ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED)) {
        ਜੇ (keystate[SDL_SCANCODE_LGUI] && !(Get_ਕੁੰਜੀ_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        ਜੇ (keystate[SDL_SCANCODE_RGUI] && !(Get_ਕੁੰਜੀ_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    ਜੇ (_this) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = _this->windows;
        ਜਦੋਂ (ਖਿੜਕੀ) {
            bool refresh_clipcursor = false;
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
            ਜੇ (ਅੰਕੜੇ) {
                refresh_clipcursor = ਅੰਕੜੇ->clipcursor_queued;
                ਅੰਕੜੇ->clipcursor_queued = false;    // Must be cleared unconditionally.
                ਅੰਕੜੇ->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            ਜੇ (refresh_clipcursor) {
                WIN_UpdateClipCursor(ਖਿੜਕੀ);
            }
            ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_ਖਿੜਕੀ = SDL_GetKeyboardFocus();
    ਜੇ (focus_ਖਿੜਕੀ && (focus_ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = focus_ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        ਜੇ (!ਅੰਕੜੇ->mouse_tracked) {
            ਬਿੰਦੂ_2 cursorPos;

            ਜੇ (GetCursorPos(&cursorPos) && Screen_ਮੰਜ਼ਿਲ_Client(ਅੰਕੜੇ->hwnd, &cursorPos)) {
                bool ਅਦਲਾ_ਬਦਲੀ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID, false, (ਦਸ਼ਮਲਵ)cursorPos.x, (ਦਸ਼ਮਲਵ)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID,
                                    !ਅਦਲਾ_ਬਦਲੀ_Buttons ? SDL_BUTTON_ਖੱਬਾ : SDL_BUTTON_ਸੱਜਾ,
                                    (Get_Async_ਕੁੰਜੀ_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID,
                                    !ਅਦਲਾ_ਬਦਲੀ_Buttons ? SDL_BUTTON_ਸੱਜਾ : SDL_BUTTON_ਖੱਬਾ,
                                    (Get_Async_ਕੁੰਜੀ_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID,
                                    SDL_BUTTON_ਵਿਚਕਾਰ,
                                    (Get_Async_ਕੁੰਜੀ_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ਅੰਕੜੇ->ਖਿੜਕੀ, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_GDK
    GDK_Dispatch_Task_ਕਤਾਰ();
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਪੂਰਨ app_registered = 0;
LPTSTR SDL_Appname = ਨਿਰਾ;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = ਨਿਰਾ;

ਸਥਿਰ ਖਾਲੀ WIN_Clean_ਰਜਿਸਟਰ_App(WNDCLASSEX wcex)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    ਜੇ (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#ਜੇ_ਅੰਤ
    SDL_free(SDL_Appname);
    SDL_Appname = ਨਿਰਾ;
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਸਥਿਰ BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (ਖਾਲੀ)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = ਲੱਦੋ_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    ਵਾਪਸ FALSE;
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_ਰਜਿਸਟਰ_App(ਅਚਲ ਅੱਖਰ *name, Uint32 style, ਖਾਲੀ *hInst)
{
    WNDCLASSEX wcex;
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਅਚਲ ਅੱਖਰ *hint;
#ਜੇ_ਅੰਤ

    // Only do this once...
    ਜੇ (app_registered) {
        ++app_registered;
        ਵਾਪਸ true;
    }
    SDL_assert(!SDL_Appname);
    ਜੇ (!name) {
        name = "SDL_app";
#ਜੇ defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#ਜੇ_ਅੰਤ
    }
    SDL_Appname = WIN_UTF8_ਮੰਜ਼ਿਲ_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(ਨਿਰਾ);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_ਮਾਪ = ਆਕਾਰ(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_ਖਿੜਕੀ_Proc;
    wcex.hInstance = SDL_Instance;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    ਜੇ (hint && *hint) {
        wcex.hIcon = ਲੱਦੋ_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        ਜੇ (hint && *hint) {
            wcex.hIconSm = ਲੱਦੋ_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } ਨਹੀਂਤਾਂ {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_ਨਾਂ(SDL_Instance, RT_ਸਮੂਹ_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਜੇ (!ਰਜਿਸਟਰ_Class_Ex(&wcex)) {
        WIN_Clean_ਰਜਿਸਟਰ_App(wcex);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't register application class");
    }

    app_registered = 1;
    ਵਾਪਸ true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
ਖਾਲੀ SDL_UnregisterApp(ਖਾਲੀ)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    ਜੇ (!app_registered) {
        ਵਾਪਸ;
    }
    --app_registered;
    ਜੇ (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = ਨਿਰਾ;
        wcex.hIconSm = ਨਿਰਾ;
        // Check for any registered window classes.
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ਜੇ (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#ਜੇ_ਅੰਤ
        WIN_Clean_ਰਜਿਸਟਰ_App(wcex);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
