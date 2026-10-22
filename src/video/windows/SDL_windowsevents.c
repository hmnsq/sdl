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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS

#ضمن "SDL_windowsvideo.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_touch_c.h"
#ضمن "../../events/scancodes_windows.h"
#ضمن "../../main/SDL_main_callbacks.h"
#ضمن "../../core/windows/SDL_hid.h"

// Dropfile support
#ضمن <shellapi.h>

// Device names
#ضمن <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#ضمن <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#جيڪڏهن_وصف_ٿيل HAVE_TPCSHRD_H
#ضمن <tpcshrd.h>
#جيڪڏهن_پورو // HAVE_TPCSHRD_H

#إذا 0
#وصف_ڪريو WMMSG_DEBUG
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#جيڪڏهن_پورو

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_GDK
#ضمن "../../core/gdk/SDL_gdk.h"
#جيڪڏهن_پورو

// #define HIGHDPI_DEBUG

// Undocumented window messages
#جيڪڏهن_وصف_نه_ٿيل WM_NCUAHDRAWCAPTION
#وصف_ڪريو WM_NCUAHDRAWCAPTION 0xAE
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_NCUAHDRAWFRAME
#وصف_ڪريو WM_NCUAHDRAWFRAME 0xAF
#جيڪڏهن_پورو

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#جيڪڏهن_وصف_نه_ٿيل WM_XBUTTONDOWN
#وصف_ڪريو WM_XBUTTONDOWN 0x020B
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_XBUTTONUP
#وصف_ڪريو WM_XBUTTONUP 0x020C
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل GET_XBUTTON_WPARAM
#وصف_ڪريو GET_XBUTTON_WPARAM(w) (HIWORD(w))
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_داخلا
#وصف_ڪريو WM_داخلا 0x00ff
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_TOUCH
#وصف_ڪريو WM_TOUCH 0x0240
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_MOUSEHWHEEL
#وصف_ڪريو WM_MOUSEHWHEEL 0x020E
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل RI_MOUSE_HWHEEL
#وصف_ڪريو RI_MOUSE_HWHEEL 0x0800
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERUPDATE
#وصف_ڪريو WM_POINTERUPDATE 0x0245
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERDOWN
#وصف_ڪريو WM_POINTERDOWN 0x0246
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERUP
#وصف_ڪريو WM_POINTERUP 0x0247
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERENTER
#وصف_ڪريو WM_POINTERENTER 0x0249
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERLEAVE
#وصف_ڪريو WM_POINTERLEAVE 0x024A
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_POINTERCAPTURECHANGED
#وصف_ڪريو WM_POINTERCAPTURECHANGED 0x024C
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_UNICHAR
#وصف_ڪريو WM_UNICHAR 0x0109
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_DPICHANGED
#وصف_ڪريو WM_DPICHANGED 0x02E0
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل WM_GETDPISCALEDSIZE
#وصف_ڪريو WM_GETDPISCALEDSIZE 0x02E4
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل TOUCHEVENTF_PEN
#وصف_ڪريو TOUCHEVENTF_PEN 0x0040
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل MAPVK_VK_منزل_VSC_EX
#وصف_ڪريو MAPVK_VK_منزل_VSC_EX 4
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل WC_ERR_INVALID_CHARS
#وصف_ڪريو WC_ERR_INVALID_CHARS 0x00000080
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل IS_مٿاهون_SURROGATE
#وصف_ڪريو IS_مٿاهون_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل USER_TIMER_MINIMUM
#وصف_ڪريو USER_TIMER_MINIMUM 0x0000000A
#جيڪڏهن_پورو

// Used to compare Windows message timestamps
#وصف_ڪريو SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#جيڪڏهن_وصف_ٿيل _WIN64
تعريفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#جيڪڏهن_پورو

ساكن bool SDL_processing_messages;
ساكن DWORD پيغام_tick;
ساكن Uint64 timestamp_وٿي;

ساكن فراغ WIN_سيٽ_پيغام_Tick(DWORD tick)
{
    پيغام_tick = tick;
}

ساكن Uint64 WIN_GetEventTimestamp(فراغ)
{
    ثابت Uint64 TIMESTAMP_WRAP_وٿي = SDL_MS_منزل_NS(0x100000000LL);
    Uint64 timestamp, now;

    إذا (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        أرجع 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_منزل_NS(پيغام_tick);
    timestamp += timestamp_وٿي;
    إذا (!timestamp_وٿي) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_وٿي = (now - timestamp);
        timestamp = now;
    } وإلا إذا ((Sint64)(now - timestamp - TIMESTAMP_WRAP_وٿي) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_وٿي += TIMESTAMP_WRAP_وٿي;
        timestamp += TIMESTAMP_WRAP_وٿي;
    } وإلا إذا (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_وٿي -= (timestamp - now);
        timestamp = now;
    }
    أرجع timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_Windows_پيغام_Hook g_Windows_پيغام_Hook = عدم;
ساكن فراغ *g_Windows_پيغام_Hook_معلومات = عدم;

فراغ SDL_سيٽ_Windows_پيغام_Hook(SDL_Windows_پيغام_Hook callback, فراغ *userdata)
{
    g_Windows_پيغام_Hook = callback;
    g_Windows_پيغام_Hook_معلومات = userdata;
}

ساكن SDL_Scancode Windows_جاچ_ڪوڊ_منزل_SDLScan_ڪوڊ(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_ڪنجي)
{
    SDL_Scancode ڪوڊ;
    Uint8 اشاريو;
    Uint16 ڪنجي_Flags = HIWORD(lParam);
    Uint16 جاچ_ڪوڊ = LOBYTE(ڪنجي_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    جاچ_ڪوڊ &= ~0x80;

    *virtual_ڪنجي = (جاچ_ڪوڊ == 0);

    إذا (جاچ_ڪوڊ != 0) {
        إذا ((ڪنجي_Flags & KF_EXTENDED) == KF_EXTENDED) {
            جاچ_ڪوڊ = MAKEWORD(جاچ_ڪوڊ, 0xe0);
        } وإلا إذا (جاچ_ڪوڊ == 0x45) {
            // Pause
            جاچ_ڪوڊ = 0xe046;
        }
    } وإلا {
        Uint16 vk_ڪوڊ = LOWORD(wParam);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        جاچ_ڪوڊ = LOWORD(Map_Virtual_ڪنجي(vk_ڪوڊ, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        إذا (جاچ_ڪوڊ == 0xe11d) {
            جاچ_ڪوڊ = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    اشاريو = LOBYTE(جاچ_ڪوڊ) | (HIBYTE(جاچ_ڪوڊ) ? 0x80 : 0x00);
    ڪوڊ = windows_scancode_جدول[اشاريو];
    *rawcode = جاچ_ڪوڊ;

    أرجع ڪوڊ;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_دري_معلومات *معلومات)
{
    أرجع !SDL_دري_IS_POPUP(معلومات->دري) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_مٽا_سٽا_Buttons, SDL_دري_معلومات *معلومات, Uint8 button, SDL_MouseID mouseID)
{
    إذا (b_مٽا_سٽا_Buttons) {
        إذا (button == SDL_BUTTON_کاٻو) {
            button = SDL_BUTTON_ساڄو;
        } وإلا إذا (button == SDL_BUTTON_ساڄو) {
            button = SDL_BUTTON_کاٻو;
        }
    }

    إذا (معلومات->focus_click_pending & SDL_BUTTON_نقاب(button)) {
        // Ignore the button click for activation
        إذا (!bwParamMousePressed) {
            معلومات->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
            WIN_UpdateClipCursor(معلومات->دري);
        }
        أرجع;
    }

    إذا (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, معلومات->دري, mouseID, button, true);
    } وإلا إذا (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, معلومات->دري, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_دري_معلومات *معلومات, SDL_MouseID mouseID)
{
    إذا (wParam != معلومات->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_کاٻو, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_وچ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_ساڄو, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, معلومات, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, معلومات, SDL_BUTTON_X2, mouseID);

        معلومات->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_دري_معلومات *معلومات)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT ڪنجي_State;
    bool مٽا_سٽا_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    مٽا_سٽا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    ڪنجي_State = Get_Async_ڪنجي_State(VK_LBUTTON);
    إذا (!(ڪنجي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, مٽا_سٽا_Buttons, معلومات, SDL_BUTTON_کاٻو, mouseID);
    }
    ڪنجي_State = Get_Async_ڪنجي_State(VK_RBUTTON);
    إذا (!(ڪنجي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, مٽا_سٽا_Buttons, معلومات, SDL_BUTTON_ساڄو, mouseID);
    }
    ڪنجي_State = Get_Async_ڪنجي_State(VK_MBUTTON);
    إذا (!(ڪنجي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, مٽا_سٽا_Buttons, معلومات, SDL_BUTTON_وچ, mouseID);
    }
    ڪنجي_State = Get_Async_ڪنجي_State(VK_XBUTTON1);
    إذا (!(ڪنجي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, مٽا_سٽا_Buttons, معلومات, SDL_BUTTON_X1, mouseID);
    }
    ڪنجي_State = Get_Async_ڪنجي_State(VK_XBUTTON2);
    إذا (!(ڪنجي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, مٽا_سٽا_Buttons, معلومات, SDL_BUTTON_X2, mouseID);
    }
    معلومات->mouse_button_flags = (WPARAM)-1;
}

ساكن فراغ WIN_UpdateFocus(SDL_دري *دري, bool expect_focus, LPPOINT pos)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == دري);
    bool has_focus = (Get_Foreground_دري() == hwnd);

    إذا (had_focus == has_focus || has_focus != expect_focus) {
        أرجع;
    }

    إذا (has_focus) {
        نقطو_2 cursorPos;

        إذا (WIN_ShouldIgnoreFocusClick(معلومات) && !(دري->flags & SDL_دري_MOUSE_CAPTURE)) {
            bool مٽا_سٽا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            إذا (Get_Async_ڪنجي_State(VK_LBUTTON)) {
                معلومات->focus_click_pending |= !مٽا_سٽا_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            إذا (Get_Async_ڪنجي_State(VK_RBUTTON)) {
                معلومات->focus_click_pending |= !مٽا_سٽا_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            إذا (Get_Async_ڪنجي_State(VK_MBUTTON)) {
                معلومات->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            إذا (Get_Async_ڪنجي_State(VK_XBUTTON1)) {
                معلومات->focus_click_pending |= SDL_BUTTON_X1_نقاب;
            }
            إذا (Get_Async_ڪنجي_State(VK_XBUTTON2)) {
                معلومات->focus_click_pending |= SDL_BUTTON_X2_نقاب;
            }
        }

        SDL_سيٽ_Keyboard_Focus(دري->keyboard_focus ? دري->keyboard_focus : دري);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        إذا (!SDL_GetMouse()->relative_گهڻائي) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_منزل_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
        WIN_UpdateClipCursor(دري);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(معلومات->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_ڪنجي_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_انگ, (Get_ڪنجي_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_ڪنجي_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_دري_ICCProfile(معلومات->دري, true);
    } وإلا {
        معلومات->اندريون_دري_deactivation = true;

        SDL_سيٽ_Keyboard_Focus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        إذا (SDL_GetMouse()->relative_گهڻائي) {
            SDL_سيٽ_Mouse_Focus(عدم);
        }
        WIN_Reset_Dead_ڪنجيون();

        WIN_Unclip_Cursor_For_دري(دري);

        معلومات->اندريون_دري_deactivation = false;
    }
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool Should_Generate_دري_Close_On_Alt_F4(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool Should_Clear_دري_On_Erase_Background(SDL_دري_معلومات *معلومات)
{
    بدل (معلومات->hint_erase_background_گهڻائي) {
    حالة SDL_ERASEBACKGROUNDMODE_NEVER:
        أرجع false;
    حالة SDL_ERASEBACKGROUNDMODE_INITIAL:
        أرجع !معلومات->videodata->cleared;
    حالة SDL_ERASEBACKGROUNDMODE_ALWAYS:
        أرجع true;
    افتراضي:
        // Unexpected value, fallback to default behaviour
        أرجع !معلومات->videodata->cleared;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#وصف_ڪريو MI_WP_SIGNATURE      0xFF515700
#وصف_ڪريو MI_WP_SIGNATURE_نقاب 0xFFFFFF00
#وصف_ڪريو IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_نقاب) == MI_WP_SIGNATURE

تعريفنوع تعداد
{
    SDL_MOUSE_EVENT_ذريعو_UNKNOWN,
    SDL_MOUSE_EVENT_ذريعو_MOUSE,
    SDL_MOUSE_EVENT_ذريعو_TOUCH,
    SDL_MOUSE_EVENT_ذريعو_PEN,
} SDL_MOUSE_EVENT_ذريعو;

ساكن SDL_MOUSE_EVENT_ذريعو Get_Mouse_پيغام_ذريعو(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    إذا (IsTouchEvent(extrainfo)) {
        إذا (extrainfo & 0x80) {
            أرجع SDL_MOUSE_EVENT_ذريعو_TOUCH;
        } وإلا {
            أرجع SDL_MOUSE_EVENT_ذريعو_PEN;
        }
    }
    أرجع SDL_MOUSE_EVENT_ذريعو_MOUSE;
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_دري_معلومات *WIN_Get_دري_معلومات_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_دري *دري;

    إذا (_this) {
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            SDL_دري_معلومات *معلومات = دري->اندروني;
            إذا (معلومات && معلومات->hwnd == hwnd) {
                أرجع معلومات;
            }
        }
    }
    أرجع عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح n_ڪوڊ, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_معلومات = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_معلومات *معلومات = SDL_GetVideoDevice()->اندروني;
    SDL_Scancode جاچ_ڪوڊ;

    إذا (n_ڪوڊ < 0 || n_ڪوڊ != HC_ACTION) {
        أرجع Call_ايندڙ_Hook_Ex(عدم, n_ڪوڊ, wParam, lParam);
    }
    إذا (hook_معلومات->جاچ_ڪوڊ == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        أرجع 1;
    }

    بدل (hook_معلومات->vk_ڪوڊ) {
    حالة VK_LWIN:
        جاچ_ڪوڊ = SDL_SCANCODE_LGUI;
        اكسر;
    حالة VK_RWIN:
        جاچ_ڪوڊ = SDL_SCANCODE_RGUI;
        اكسر;
    حالة VK_LMENU:
        جاچ_ڪوڊ = SDL_SCANCODE_LALT;
        اكسر;
    حالة VK_RMENU:
        جاچ_ڪوڊ = SDL_SCANCODE_RALT;
        اكسر;
    حالة VK_LCONTROL:
        جاچ_ڪوڊ = SDL_SCANCODE_LCTRL;
        اكسر;
    حالة VK_RCONTROL:
        جاچ_ڪوڊ = SDL_SCANCODE_RCTRL;
        اكسر;
    حالة VK_SNAPSHOT:
        جاچ_ڪوڊ = SDL_SCANCODE_PRINTSCREEN;
        اكسر;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالة VK_TAB:
        جاچ_ڪوڊ = SDL_SCANCODE_TAB;
        اكسر;
    حالة VK_ESCAPE:
        جاچ_ڪوڊ = SDL_SCANCODE_ESCAPE;
        اكسر;

    افتراضي:
        أرجع Call_ايندڙ_Hook_Ex(عدم, n_ڪوڊ, wParam, lParam);
    }

    إذا (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        إذا (!معلومات->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, hook_معلومات->جاچ_ڪوڊ, جاچ_ڪوڊ, true);
        }
    } وإلا {
        إذا (!معلومات->raw_keyboard_enabled) {
            SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, hook_معلومات->جاچ_ڪوڊ, جاچ_ڪوڊ, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        إذا (hook_معلومات->vk_ڪوڊ <= 0xFF && معلومات->pre_hook_ڪنجي_state[hook_معلومات->vk_ڪوڊ]) {
            معلومات->pre_hook_ڪنجي_state[hook_معلومات->vk_ڪوڊ] = 0;
            أرجع Call_ايندڙ_Hook_Ex(عدم, n_ڪوڊ, wParam, lParam);
        }
    }

    أرجع 1;
}

ساكن bool WIN_مٽا_سٽا_Buttons(HANDLE hDevice)
{
    إذا (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        أرجع false;
    }
    أرجع GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_Handle_Raw_Mouse_داخلا(Uint64 timestamp, SDL_Video_معلومات *معلومات, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool هيٺ_ڏانهن;
    } raw_buttons[] = {
        { RI_MOUSE_کاٻو_BUTTON_هيٺ_ڏانهن, SDL_BUTTON_کاٻو, true },
        { RI_MOUSE_کاٻو_BUTTON_مٿي, SDL_BUTTON_کاٻو, false },
        { RI_MOUSE_ساڄو_BUTTON_هيٺ_ڏانهن, SDL_BUTTON_ساڄو, true },
        { RI_MOUSE_ساڄو_BUTTON_مٿي, SDL_BUTTON_ساڄو, false },
        { RI_MOUSE_وچ_BUTTON_هيٺ_ڏانهن, SDL_BUTTON_وچ, true },
        { RI_MOUSE_وچ_BUTTON_مٿي, SDL_BUTTON_وچ, false },
        { RI_MOUSE_BUTTON_4_هيٺ_ڏانهن, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_مٿي, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_هيٺ_ڏانهن, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_مٿي, SDL_BUTTON_X2, false }
    };

    صحيح dx = (صحيح)rawmouse->l_آخري_X;
    صحيح dy = (صحيح)rawmouse->l_آخري_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    إذا (!معلومات->raw_mouse_enabled) {
        أرجع;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_دري *دري = SDL_GetKeyboardFocus();
    إذا (!دري) {
        أرجع;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse) {
        أرجع;
    }

    إذا (Get_Mouse_پيغام_ذريعو(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_ذريعو_MOUSE ||
        (SDL_Touch_Devices_موجود() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        أرجع;
    }

    SDL_دري_معلومات *windowdata = دري->اندروني;

    إذا (haveMotion && !windowdata->اندريون_modal_loop) {
        إذا (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, دري, mouseID, true, (عائم)dx, (عائم)dy);
        } وإلا {
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
            صحيح w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            صحيح h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            صحيح x = raw_coordinates ? dx : (صحيح)(((عائم)dx / 65535.0f) * w);
            صحيح y = raw_coordinates ? dy : (صحيح)(((عائم)dy / 65535.0f) * h);
            صحيح relX, relY;

            /* Calculate relative motion */
            إذا (معلومات->آخري_raw_mouse_position.x == 0 && معلومات->آخري_raw_mouse_position.y == 0) {
                معلومات->آخري_raw_mouse_position.x = x;
                معلومات->آخري_raw_mouse_position.y = y;
            }
            relX = x - معلومات->آخري_raw_mouse_position.x;
            relY = y - معلومات->آخري_raw_mouse_position.y;

            إذا (remote_desktop) {
                إذا (!windowdata->اندريون_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    إذا (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.کاٻو + ((rect.ساڄو - rect.کاٻو) / 2) + wobble;
                        صحيح warpY = rect.چوٽي + ((rect.bottom - rect.چوٽي) / 2);

                        WIN_سيٽ_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        إذا (wobble > 1) {
                            wobble = -1;
                        }
                    } وإلا {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ثابت صحيح MAX_RELATIVE_MOTION = (h / 6);
                        إذا (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, دري, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } وإلا إذا (mouse->pen_mouse_events) {
                ثابت صحيح وڌ_کان_وڌ_TABLET_RELATIVE_MOTION = 32;
                إذا (SDL_abs(relX) > وڌ_کان_وڌ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > وڌ_کان_وڌ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وإلا {
                    SDL_SendMouseMotion(timestamp, دري, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } وإلا {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                إذا (!معلومات->raw_داخلا_fake_pen_id) {
                    معلومات->raw_داخلا_fake_pen_id = SDL_جوڙيو_Pen_Device(timestamp, "raw mouse input", دري, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, معلومات->raw_داخلا_fake_pen_id, دري, (عائم)(x + screen_x - دري->x), (عائم)(y + screen_y - دري->y));
            }

            معلومات->آخري_raw_mouse_position.x = x;
            معلومات->آخري_raw_mouse_position.y = y;
        }
    }

    إذا (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            إذا (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool هيٺ_ڏانهن = raw_buttons[i].هيٺ_ڏانهن;

                إذا (button == SDL_BUTTON_کاٻو) {
                    إذا (WIN_مٽا_سٽا_Buttons(hDevice)) {
                        button = SDL_BUTTON_ساڄو;
                    }
                } وإلا إذا (button == SDL_BUTTON_ساڄو) {
                    إذا (WIN_مٽا_سٽا_Buttons(hDevice)) {
                        button = SDL_BUTTON_کاٻو;
                    }
                }

                إذا (windowdata->focus_click_pending & SDL_BUTTON_نقاب(button)) {
                    // Ignore the button click for activation
                    إذا (!هيٺ_ڏانهن) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
                        WIN_UpdateClipCursor(دري);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, دري, mouseID, button, هيٺ_ڏانهن);
            }
        }

        إذا (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_معلومات;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, دري, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_عام);
        } وإلا إذا (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_معلومات;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, دري, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_عام);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_Handle_Raw_Keyboard_داخلا(Uint64 timestamp, SDL_Video_معلومات *معلومات, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    إذا (!معلومات->raw_keyboard_enabled) {
        أرجع;
    }

    إذا (rawkeyboard->Flags & RI_ڪنجي_E1) {
        // First key in a Ctrl+{key} sequence
        معلومات->pending_E1_ڪنجي_sequence = true;
        أرجع;
    }

    إذا ((rawkeyboard->Flags & RI_ڪنجي_E0) && rawkeyboard->Make_ڪوڊ == 0x2A) {
        // 0xE02A make code prefix, ignored
        أرجع;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!rawkeyboard->Make_ڪوڊ) {
        rawkeyboard->Make_ڪوڊ = LOWORD(Map_Virtual_ڪنجي(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
    }
#جيڪڏهن_پورو
    إذا (!rawkeyboard->Make_ڪوڊ) {
        أرجع;
    }

    bool هيٺ_ڏانهن;
    بدل (rawkeyboard->پيغام_2) {
    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
        هيٺ_ڏانهن = true;
        اكسر;
    حالة WM_KEYUP:
    حالة WM_SYSKEYUP:
        هيٺ_ڏانهن = false;
        اكسر;
    افتراضي:
        هيٺ_ڏانهن = !(rawkeyboard->Flags & RI_ڪنجي_BREAK);
        اكسر;
    }

    SDL_Scancode ڪوڊ;
    USHORT rawcode = rawkeyboard->Make_ڪوڊ;
    إذا (معلومات->pending_E1_ڪنجي_sequence) {
        rawcode |= 0xE100;
        إذا (rawkeyboard->Make_ڪوڊ == 0x45) {
            // Ctrl+NumLock == Pause
            ڪوڊ = SDL_SCANCODE_PAUSE;
        } وإلا {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            ڪوڊ = SDL_SCANCODE_UNKNOWN;
        }
        معلومات->pending_E1_ڪنجي_sequence = false;
    } وإلا {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 اشاريو = (Uint8)rawkeyboard->Make_ڪوڊ;
        إذا (rawkeyboard->Flags & RI_ڪنجي_E0) {
            rawcode |= 0xE000;
            اشاريو |= 0x80;
        }
        ڪوڊ = windows_scancode_جدول[اشاريو];
    }

    إذا (هيٺ_ڏانهن) {
        SDL_دري *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        إذا ((!معلومات->raw_keyboard_flag_inputsink && !focus) || (focus && focus->متن_داخلا_سرگرم)) {
            أرجع;
        }
    }

    SDL_Send_Keyboard_ڪنجي(timestamp, keyboardID, rawcode, ڪوڊ, هيٺ_ڏانهن);
}

فراغ WIN_Poll_Raw_داخلا(SDL_VideoDevice *_this, Uint64 poll_شروعات)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    UINT سائيز, i, ڳڻپ, ڪل = 0;
    RAWINPUT *داخلا_2;
    Uint64 poll_پڄاڻي;

    إذا (معلومات->rawinput_وٿي == 0) {
        BOOL isWow64;

        معلومات->rawinput_وٿي = حجم(RAWINPUTHEADER);
        إذا (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            معلومات->rawinput_وٿي += 8;
        }
    }

    // Get all available events
    داخلا_2 = (RAWINPUT *)معلومات->rawinput;
    لكل (;;) {
        سائيز = معلومات->rawinput_سائيز - (UINT)((BYTE *)داخلا_2 - معلومات->rawinput);
        ڳڻپ = Get_Raw_داخلا_بفر(داخلا_2, &سائيز, حجم(RAWINPUTHEADER));
        poll_پڄاڻي = SDL_GetTicksNS();
        إذا (ڳڻپ == 0 || ڳڻپ == (UINT)-1) {
            إذا (!معلومات->rawinput || (ڳڻپ == (UINT)-1 && Get_آخري_Error() == ERROR_INSUFFICIENT_بفر)) {
                ثابت UINT RAWINPUT_بفر_سائيز_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(معلومات->rawinput, معلومات->rawinput_سائيز + RAWINPUT_بفر_سائيز_INCREMENT);
                إذا (!rawinput) {
                    اكسر;
                }
                داخلا_2 = (RAWINPUT *)(rawinput + ((BYTE *)داخلا_2 - معلومات->rawinput));
                معلومات->rawinput = rawinput;
                معلومات->rawinput_سائيز += RAWINPUT_بفر_سائيز_INCREMENT;
            } وإلا {
                اكسر;
            }
        } وإلا {
            ڪل += ڳڻپ;

            // Advance input to the end of the buffer
            طالما (ڳڻپ--) {
                داخلا_2 = NEXTRAWINPUTBLOCK(داخلا_2);
            }
        }
    }

    إذا (ڪل > 0) {
        Uint64 delta = poll_پڄاڻي - poll_شروعات;
        UINT mouse_ڪل = 0;
        لكل (i = 0, داخلا_2 = (RAWINPUT *)معلومات->rawinput; i < ڪل; ++i, داخلا_2 = NEXTRAWINPUTBLOCK(داخلا_2)) {
            إذا (داخلا_2->سرو.dwType == RIM_TYPEMOUSE) {
                mouse_ڪل += 1;
            }
        }
        صحيح mouse_اشاريو = 0;
        لكل (i = 0, داخلا_2 = (RAWINPUT *)معلومات->rawinput; i < ڪل; ++i, داخلا_2 = NEXTRAWINPUTBLOCK(داخلا_2)) {
            إذا (داخلا_2->سرو.dwType == RIM_TYPEMOUSE) {
                mouse_اشاريو += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)داخلا_2 + معلومات->rawinput_وٿي);
                Uint64 وقت = poll_پڄاڻي - (delta * (mouse_ڪل - mouse_اشاريو)) / mouse_ڪل;
                WIN_Handle_Raw_Mouse_داخلا(وقت, معلومات, داخلا_2->سرو.hDevice, rawmouse);
            } وإلا إذا (داخلا_2->سرو.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)داخلا_2 + معلومات->rawinput_وٿي);
                WIN_Handle_Raw_Keyboard_داخلا(poll_پڄاڻي, معلومات, داخلا_2->سرو.hDevice, rawkeyboard);
            }
        }
    }
    معلومات->آخري_rawinput_poll = poll_پڄاڻي;
}

ساكن فراغ جوڙيو_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *ڳڻپ)
{
    صحيح new_ڳڻپ = (*ڳڻپ + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ڳڻپ * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_ڳڻپ - 1] = deviceID;

    *ڳڻپ = new_ڳڻپ;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح ڳڻپ)
{
    لكل (صحيح i = 0; i < ڳڻپ; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن حرف *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت حرف *instance, Uint16 vendor, Uint16 حاصل_ضرب, ثابت حرف *default_name, bool hid_loaded)
{
    حرف *vendor_name = عدم;
    حرف *حاصل_ضرب_name = عدم;
    حرف *name = عدم;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    إذا (hid_loaded) {
        حرف devName[MAX_رستو + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_داخلا_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        إذا (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            إذا (hFile != INVALID_HANDLE_قدر) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_Hid_D_Get_حاصل_ضرب_String(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    إذا (vend[0]) {
        vendor_name = WIN_String_منزل_UTF8_W(vend);
    }

    إذا (prod[0]) {
        حاصل_ضرب_name = WIN_String_منزل_UTF8_W(prod);
    } وإلا {
        SP_DEVINFO_معلومات معلومات;
        SDL_zero(معلومات);
        معلومات.cb_سائيز = حجم(معلومات);
        لكل (DWORD i = 0;; ++i) {
            إذا (!تياري_Di_Enum_Device_Info(devinfo, i, &معلومات)) {
                إذا (Get_آخري_Error() == ERROR_NO_وڌيڪ_شيون) {
                    اكسر;
                } وإلا {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            إذا (!تياري_Di_Get_Device_Instance_Id_A(devinfo, &معلومات, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            إذا (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD سائيز = 0;
                إذا (تياري_Di_Get_Device_Registry_Property_W(devinfo, &معلومات, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &سائيز)) {
                    // Make sure the device description is null terminated
                    سائيز /= حجم(*prod);
                    إذا (سائيز >= SDL_arraysize(prod)) {
                        // Truncated description...
                        سائيز = (SDL_arraysize(prod) - 1);
                    }
                    prod[سائيز] = 0;

                    إذا (vendor || حاصل_ضرب) {
                        SDL_asprintf(&حاصل_ضرب_name, "%S (0x%.4x/0x%.4x)", prod, vendor, حاصل_ضرب);
                    } وإلا {
                        حاصل_ضرب_name = WIN_String_منزل_UTF8_W(prod);
                    }
                }
                اكسر;
            }
        }
    }

    إذا (!حاصل_ضرب_name && (vendor || حاصل_ضرب)) {
        SDL_asprintf(&حاصل_ضرب_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, حاصل_ضرب);
    }
    name = SDL_CreateDeviceName(vendor, حاصل_ضرب, vendor_name, حاصل_ضرب_name, default_name);
    SDL_free(vendor_name);
    SDL_free(حاصل_ضرب_name);

    أرجع name;
}

فراغ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = عدم;
    UINT raw_device_ڳڻپ = 0;
    صحيح old_keyboard_ڳڻپ = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_ڳڻپ = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_ڳڻپ = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_ڳڻپ = 0;
    SDL_MouseID *new_mice = عدم;

    إذا (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->اندروني->detect_device_hotplug ||
        _this->اندروني->gameinput_context) {
        أرجع;
    }

    إذا ((Get_Raw_داخلا_Device_List(عدم, &raw_device_ڳڻپ, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_ڳڻپ)) {
        أرجع; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_ڳڻپ);
    إذا (!raw_devices) {
        أرجع; // oh well.
    }

    raw_device_ڳڻپ = Get_Raw_داخلا_Device_List(raw_devices, &raw_device_ڳڻپ, حجم(RAWINPUTDEVICELIST));
    إذا (raw_device_ڳڻپ == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        أرجع; // oh well.
    }

    HDEVINFO devinfo = تياري_Di_Get_Class_Devs_A(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ڳڻپ);
    old_mice = SDL_GetMice(&old_mouse_ڳڻپ);

    لكل (UINT i = 0; i < raw_device_ڳڻپ; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_رستو] = { 0 };
        UINT rdi_سائيز = حجم(rdi);
        UINT name_سائيز = SDL_arraysize(devName);
        صحيح vendor = 0, حاصل_ضرب = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        إذا (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cb_سائيز = حجم(rdi);
        إذا (Get_Raw_داخلا_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_سائيز) == ((UINT)-1) ||
            Get_Raw_داخلا_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_سائيز) == ((UINT)-1)) {
            استمر;
        }

        // Extract the device instance
        instance = devName;
        طالما (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        لكل (ptr = instance; *ptr; ++ptr) {
            إذا (*ptr == '#') {
                *ptr = '\\';
            }
            إذا (*ptr == '{') {
                إذا (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                اكسر;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &حاصل_ضرب);

        بدل (dwType) {
        حالة RIM_TYPEKEYBOARD:
            إذا (SDL_IsKeyboard((Uint16)vendor, (Uint16)حاصل_ضرب, rdi.keyboard.dw_عدد_جو_ڪنجيون_ڪل)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڙيو_Device_ID(keyboardID, &new_keyboards, &new_keyboard_ڳڻپ);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ڳڻپ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Keyboard", hid_loaded);
                    SDL_جوڙيو_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            إذا (SDL_IsMouse((Uint16)vendor, (Uint16)حاصل_ضرب)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڙيو_Device_ID(mouseID, &new_mice, &new_mouse_ڳڻپ);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_ڳڻپ)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Mouse", hid_loaded);
                    SDL_جوڙيو_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    لكل (صحيح i = old_keyboard_ڳڻپ; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ڳڻپ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_ڳڻپ; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_ڳڻپ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    تياري_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ساكن bool Skip_Alt_Gr_کاٻو_Control(WPARAM wParam, LPARAM lParam)
{
    إذا (wParam != VK_CONTROL) {
        أرجع false;
    }

    // Is this an extended key (i.e. right key)?
    إذا (lParam & 0x01000000) {
        أرجع false;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    نياپو_2 ايندڙ_نياپو;
    DWORD نياپو_وقت = Get_پيغام_وقت();
    إذا (Peek_پيغام(&ايندڙ_نياپو, عدم, 0, 0, PM_NOREMOVE)) {
        إذا (ايندڙ_نياپو.پيغام == WM_KEYDOWN ||
            ايندڙ_نياپو.پيغام == WM_SYSKEYDOWN) {
            إذا (ايندڙ_نياپو.wParam == VK_MENU && (ايندڙ_نياپو.lParam & 0x01000000) && ايندڙ_نياپو.وقت == نياپو_وقت) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                أرجع true;
            }
        }
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع false;
}

ساكن bool Dispatch_Modal_Loop_پيغام_Hook(HWND *hwnd, UINT *نياپو, WPARAM *wParam, LPARAM *lParam)
{
    نياپو_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.پيغام = *نياپو;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    إذا (g_Windows_پيغام_Hook(g_Windows_پيغام_Hook_معلومات, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *نياپو = dummy.پيغام;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        أرجع true;
    }
    أرجع false;
}

LRESULT CALLBACK WIN_دري_Proc(HWND hwnd, UINT نياپو, WPARAM wParam, LPARAM lParam)
{
    SDL_دري_معلومات *معلومات;
    LRESULT return_ڪوڊ = -1;

    // Get the window data for the window
    معلومات = WIN_Get_دري_معلومات_From_HWND(hwnd);
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!معلومات) {
        // Fallback
        معلومات = (SDL_دري_معلومات *)GetProp(hwnd, متن_2("SDL_WindowData"));
    }
#جيڪڏهن_پورو
    إذا (!معلومات) {
        أرجع Call_دري_Proc(Def_دري_Proc, hwnd, نياپو, wParam, lParam);
    }

#جيڪڏهن_وصف_ٿيل WMMSG_DEBUG
    {
        حرف پيغام[1024];
        إذا (نياپو > MAX_WMMSG) {
            SDL_snprintf(پيغام, حجم(پيغام), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, نياپو, wParam, lParam);
        } وإلا {
            SDL_snprintf(پيغام, حجم(پيغام), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[نياپو], wParam, lParam);
        }
        OutputDebugStringA(پيغام);
    }
#جيڪڏهن_پورو // WMMSG_DEBUG


    إذا (g_Windows_پيغام_Hook && معلومات->اندريون_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        إذا (!Dispatch_Modal_Loop_پيغام_Hook(&hwnd, &نياپو, &wParam, &lParam)) {
            أرجع 0;
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (WIN_HandleIMEMessage(hwnd, نياپو, wParam, &lParam, معلومات->videodata)) {
        أرجع 0;
    }
#جيڪڏهن_پورو

    بدل (نياپو) {

    حالة WM_SHOWWINDOW:
    {
        إذا (wParam) {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_SHOWN, 0, 0);
        } وإلا {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_HIDDEN, 0, 0);
        }
    } اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالة WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        معلومات->postpone_clipcursor = true;
        معلومات->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        نقطو_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(معلومات->دري, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        إذا (معلومات->دري->flags & SDL_دري_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } اكسر;

    حالة WM_NCUAHDRAWCAPTION:
    حالة WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        إذا (معلومات->دري->flags & SDL_دري_BORDERLESS) {
            return_ڪوڊ = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD نياپو_Pos = Get_پيغام_Pos();
        نقطو_2 pos = { GET_X_LPARAM(نياپو_Pos), GET_Y_LPARAM(نياپو_Pos) };
        WIN_UpdateFocus(معلومات->دري, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        إذا (SDL_دري_IS_POPUP(معلومات->دري)) {
            أرجع MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_دري *والد = معلومات->دري->والد;
        طالما (والد) {
            إذا ((والد->flags & SDL_دري_داخلا_FOCUS) &&
                (والد->flags & SDL_دري_MOUSE_RELATIVE_گهڻائي)) {
                أرجع MA_NOACTIVATE;
            }
            والد = والد->والد;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD نياپو_Pos = Get_پيغام_Pos();
        نقطو_2 pos = { GET_X_LPARAM(نياپو_Pos), GET_Y_LPARAM(نياپو_Pos) };
        WIN_UpdateFocus(معلومات->دري, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD نياپو_Pos = Get_پيغام_Pos();
        نقطو_2 pos = { GET_X_LPARAM(نياپو_Pos), GET_Y_LPARAM(نياپو_Pos) };
        WIN_UpdateFocus(معلومات->دري, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارو_داخلا_TYPE اشارو_type = PT_اشارو;
        إذا (!معلومات->videodata->Get_اشارو_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!معلومات->videodata->Get_اشارو_Type(pointerid, &اشارو_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشارو_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڳوليو_Pen_By_Handle(hpointer);
        إذا (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, معلومات->دري, true, true);
        } وإلا {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_مفاصلو | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.انگ_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_جوڙيو_Pen_Device(WIN_GetEventTimestamp(), عدم, معلومات->دري, &info, hpointer, true);
        }
        return_ڪوڊ = 0;
    } اكسر;

    حالة WM_POINTERCAPTURECHANGED:
    حالة WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارو_داخلا_TYPE اشارو_type = PT_اشارو;
        إذا (!معلومات->videodata->Get_اشارو_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!معلومات->videodata->Get_اشارو_Type(pointerid, &اشارو_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشارو_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڳوليو_Pen_By_Handle(hpointer);
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        إذا ((نياپو == WM_POINTERCAPTURECHANGED) || !IS_اشارو_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, معلومات->دري, false, false);
        }
        return_ڪوڊ = 0;
    } اكسر;

    حالة WM_POINTERDOWN:
    حالة WM_POINTERUP:
    حالة WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارو_داخلا_TYPE اشارو_type = PT_اشارو;
        إذا (!معلومات->videodata->Get_اشارو_Type || !معلومات->videodata->Get_اشارو_Type(pointerid, &اشارو_type)) {
            اكسر;  // oh well.
        } وإلا إذا ((نياپو == WM_POINTERUPDATE) && (اشارو_type == PT_MOUSE)) {
            معلومات->آخري_اشارو_update = lParam;
            return_ڪوڊ = 0;
            اكسر;
        } وإلا إذا (اشارو_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڳوليو_Pen_By_Handle(hpointer);
        اشارو_PEN_INFO pen_info;
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } وإلا إذا (!معلومات->videodata->Get_اشارو_Pen_Info || !معلومات->videodata->Get_اشارو_Pen_Info(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_دري *دري = معلومات->دري;

        ثابت bool istouching = IS_اشارو_INCONTACT_WPARAM(wParam) && IS_اشارو_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        إذا (!istouching) {
            SDL_SendPenTouch(timestamp, pen, دري, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت اشارو_INFO *اشارو_info = &pen_info.اشارو_Info;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        إذا (!معلومات->videodata->Get_اشارو_Device_Rects || !معلومات->videodata->Get_اشارو_Device_Rects(اشارو_info->ذريعو_Device, &tablet_bounds, &tablet_mapping)) {
            نقطو_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_منزل_Client(معلومات->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } وإلا {
            صحيح ix, iy;
            SDL_Get_دري_Position(دري, &ix, &iy);
            ثابت SDL_FPoint دري_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = اشارو_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.ساڄو );
            ثابت عائم facY = اشارو_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.ساڄو  - tablet_mapping.کاٻو;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.چوٽي;

            fx = (tablet_mapping.کاٻو + (facX * w)) - دري_pos.x;
            fy = (tablet_mapping.چوٽي  + (facY * h)) - دري_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, دري, fx, fy);
        SDL_SendPenButton(timestamp, pen, دري, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, دري, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        إذا (pen_info.pen_نقاب & PEN_نقاب_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, دري, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, دري, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, دري, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, دري, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        إذا (istouching) {
            SDL_SendPenTouch(timestamp, pen, دري, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_ڪوڊ = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_دري *دري = معلومات->دري;

        إذا (دري->flags & SDL_دري_داخلا_FOCUS) {
            bool wish_clip_cursor = (
                دري->flags & (SDL_دري_MOUSE_RELATIVE_گهڻائي | SDL_دري_MOUSE_GRABBED) ||
                (دري->mouse_rect.w > 0 && دري->mouse_rect.h > 0)
            );
            إذا (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                معلومات->clipcursor_queued = true;
            }
        }

        إذا (!معلومات->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_سائيز = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = معلومات->hwnd;

            إذا (TrackMouseEvent(&trackMouseEvent)) {
                معلومات->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
        }

        إذا (!معلومات->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            إذا (Get_Mouse_پيغام_ذريعو((ULONG)Get_پيغام_Extra_Info()) == SDL_MOUSE_EVENT_ذريعو_MOUSE &&
                lParam != معلومات->آخري_اشارو_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)GET_X_LPARAM(lParam), (عائم)GET_Y_LPARAM(lParam));
            }
        }

    } اكسر;

    حالة WM_LBUTTONUP:
    حالة WM_RBUTTONUP:
    حالة WM_MBUTTONUP:
    حالة WM_XBUTTONUP:
    حالة WM_LBUTTONDOWN:
    حالة WM_LBUTTONDBLCLK:
    حالة WM_RBUTTONDOWN:
    حالة WM_RBUTTONDBLCLK:
    حالة WM_MBUTTONDOWN:
    حالة WM_MBUTTONDBLCLK:
    حالة WM_XBUTTONDOWN:
    حالة WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        إذا (!معلومات->videodata->raw_mouse_enabled) {
            إذا (Get_Mouse_پيغام_ذريعو((ULONG)Get_پيغام_Extra_Info()) == SDL_MOUSE_EVENT_ذريعو_MOUSE &&
                lParam != معلومات->آخري_اشارو_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, معلومات, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#إذا 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_داخلا:
    {
        HRAWINPUT h_Raw_داخلا = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT سائيز = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        إذا (معلومات->دري != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        Get_Raw_داخلا_معلومات(h_Raw_داخلا, RID_داخلا, &inp, &سائيز, حجم(RAWINPUTHEADER));
        إذا (inp.سرو.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_داخلا(WIN_GetEventTimestamp(), معلومات, inp.سرو.hDevice, &inp.معلومات.mouse);
        } وإلا إذا (inp.سرو.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_داخلا(WIN_GetEventTimestamp(), معلومات, inp.سرو.hDevice, &inp.معلومات.keyboard);
        }
    } اكسر;
#جيڪڏهن_پورو

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        إذا (!معلومات->videodata->raw_mouse_enabled) {
            ننڍو amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            إذا (نياپو == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), معلومات->دري, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_عام);
            } وإلا {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), معلومات->دري, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_عام);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        إذا (!(معلومات->دري->flags & SDL_دري_MOUSE_CAPTURE)) {
            إذا (SDL_GetMouseFocus() == معلومات->دري && !SDL_GetMouse()->relative_گهڻائي && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_پيغام_Pos();
                نقطو_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_منزل_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                إذا (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } وإلا {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    إذا (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->دري, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } وإلا { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            إذا (!SDL_GetMouse()->relative_گهڻائي) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_سيٽ_Mouse_Focus(عدم);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        معلومات->mouse_tracked = false;

        return_ڪوڊ = 0;
        اكسر;
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
    {
        إذا (Skip_Alt_Gr_کاٻو_Control(wParam, lParam)) {
            return_ڪوڊ = 0;
            اكسر;
        }

        bool virtual_ڪنجي = false;
        Uint16 rawcode = 0;
        SDL_Scancode ڪوڊ = Windows_جاچ_ڪوڊ_منزل_SDLScan_ڪوڊ(lParam, wParam, &rawcode, &virtual_ڪنجي);

        // Detect relevant keyboard shortcuts
        إذا (ڪوڊ == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            إذا (Should_Generate_دري_Close_On_Alt_F4()) {
                SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
            }
        }

        إذا (virtual_ڪنجي || !معلومات->videodata->raw_keyboard_enabled || معلومات->دري->متن_داخلا_سرگرم) {
            SDL_Send_Keyboard_ڪنجي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ڪوڊ, true);
        }
    }

        return_ڪوڊ = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        إذا (Skip_Alt_Gr_کاٻو_Control(wParam, lParam)) {
            return_ڪوڊ = 0;
            اكسر;
        }

        bool virtual_ڪنجي = false;
        Uint16 rawcode = 0;
        SDL_Scancode ڪوڊ = Windows_جاچ_ڪوڊ_منزل_SDLScan_ڪوڊ(lParam, wParam, &rawcode, &virtual_ڪنجي);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        إذا (virtual_ڪنجي || !معلومات->videodata->raw_keyboard_enabled || معلومات->دري->متن_داخلا_سرگرم) {
            إذا (ڪوڊ == SDL_SCANCODE_PRINTSCREEN && !keyboardState[ڪوڊ]) {
                SDL_Send_Keyboard_ڪنجي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ڪوڊ, true);
            }
            SDL_Send_Keyboard_ڪنجي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, ڪوڊ, false);
        }
    }
        return_ڪوڊ = 0;
        اكسر;

    حالة WM_UNICHAR:
        إذا (wParam == UNICODE_NOCHAR) {
            return_ڪوڊ = 1;
        } وإلا {
            إذا (SDL_متن_داخلا_سرگرم(معلومات->دري)) {
                حرف متن[5];
                حرف *پڇاڙي = SDL_UCS4_منزل_UTF8((Uint32)wParam, متن);
                *پڇاڙي = '\0';
                SDL_Send_Keyboard_متن(متن);
            }
            return_ڪوڊ = 0;
        }
        اكسر;

    حالة WM_CHAR:
        إذا (SDL_متن_داخلا_سرگرم(معلومات->دري)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            إذا (IS_مٿاهون_SURROGATE(wParam)) {
                معلومات->مٿاهون_surrogate = (WCHAR)wParam;
            } وإلا {
                WCHAR utf16[3];

                utf16[0] = معلومات->مٿاهون_surrogate ? معلومات->مٿاهون_surrogate : (WCHAR)wParam;
                utf16[1] = معلومات->مٿاهون_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح نتيجو = WIN_Wide_Char_منزل_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                إذا (نتيجو > 0) {
                    SDL_Send_Keyboard_متن(utf8);
                }
                معلومات->مٿاهون_surrogate = L'\0';
            }
        } وإلا {
            معلومات->مٿاهون_surrogate = L'\0';
        }

        return_ڪوڊ = 0;
        اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#جيڪڏهن_وصف_ٿيل WM_INPUTLANGCHANGE
    حالة WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_ڪوڊ = 1;
        اكسر;
#جيڪڏهن_پورو // WM_INPUTLANGCHANGE

    حالة WM_NCLBUTTONDOWN:
    {
        معلومات->اندريون_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        إذا (Send_پيغام(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            نقطو_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_منزل_Client(hwnd, &cursorPos);
            Post_پيغام(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } اكسر;

    حالة WM_CAPTURECHANGED:
    {
        معلومات->اندريون_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
    } اكسر;

#جيڪڏهن_وصف_ٿيل WM_GETMINMAXINFO
    حالة WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT سائيز;
        صحيح x, y;
        صحيح w, h;
        صحيح min_w, min_h;
        صحيح max_w, max_h;
        BOOL constrain_max_سائيز;

        // If this is an expected size change, allow it
        إذا (معلومات->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        Get_دري_Rect(hwnd, &سائيز);
        x = سائيز.کاٻو;
        y = سائيز.چوٽي;

        // Calculate current size of our window
        SDL_Get_دري_سائيز(معلومات->دري, &w, &h);
        SDL_Get_دري_Minimum_سائيز(معلومات->دري, &min_w, &min_h);
        SDL_Get_دري_وڌ_کان_وڌ_سائيز(معلومات->دري, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        إذا (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_سائيز = TRUE;
        } وإلا {
            constrain_max_سائيز = FALSE;
        }

        إذا (!(SDL_Get_دري_Flags(معلومات->دري) & SDL_دري_BORDERLESS) && !SDL_دري_IS_POPUP(معلومات->دري)) {
            سائيز.چوٽي = 0;
            سائيز.کاٻو = 0;
            سائيز.bottom = h;
            سائيز.ساڄو = w;
            WIN_Adjust_دري_Rect_For_HWND(hwnd, &سائيز, 0);
            w = سائيز.ساڄو - سائيز.کاٻو;
            h = سائيز.bottom - سائيز.چوٽي;
#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#جيڪڏهن_پورو
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        إذا (SDL_Get_دري_Flags(معلومات->دري) & SDL_دري_RESIZABLE) {
            إذا (SDL_Get_دري_Flags(معلومات->دري) & SDL_دري_BORDERLESS) {
                صحيح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحيح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_سائيز.x = SDL_max(w, screenW);
                info->pt_Max_سائيز.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_سائيز.x = (LONG)w + min_w;
            info->pt_Min_Track_سائيز.y = (LONG)h + min_h;
            إذا (constrain_max_سائيز) {
                info->pt_Max_Track_سائيز.x = (LONG)w + max_w;
                info->pt_Max_Track_سائيز.y = (LONG)h + max_h;
            }
        } وإلا {
            info->pt_Max_سائيز.x = w;
            info->pt_Max_سائيز.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_سائيز.x = w;
            info->pt_Min_Track_سائيز.y = h;
            info->pt_Max_Track_سائيز.x = w;
            info->pt_Max_Track_سائيز.y = h;
        }
    }
        return_ڪوڊ = 0;
        اكسر;
#جيڪڏهن_پورو // WM_GETMINMAXINFO

    حالة WM_WINDOWPOSCHANGING:

        إذا (معلومات->expected_resize) {
            return_ڪوڊ = 0;
        } وإلا إذا (معلومات->اندريون_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            إذا (معلومات->آخري_modal_ويڪر == windowpos->cx && معلومات->آخري_modal_اوچائي == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            معلومات->آخري_modal_ويڪر = windowpos->cx;
            معلومات->آخري_modal_اوچائي = windowpos->cy;

            return_ڪوڊ = 0;
        }
        اكسر;

    حالة WM_WINDOWPOSCHANGED:
    {
        SDL_دري *win;
        ثابت SDL_DisplayID original_displayID = معلومات->دري->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحيح x, y;
        صحيح w, h;

        إذا (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        إذا (iconic) {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
        } وإلا إذا (zoomed) {
            إذا (معلومات->دري->flags & SDL_دري_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);
            }
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MAXIMIZED, 0, 0);
            معلومات->force_ws_maximizebox = true;
        } وإلا إذا (معلومات->دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED)) {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            إذا (!(معلومات->دري->flags & SDL_دري_FULLSCREEN)) {
                معلومات->force_ws_maximizebox = false;
                WIN_سيٽ_دري_Resizable(SDL_GetVideoDevice(), معلومات->دري, !!(معلومات->دري->flags & SDL_دري_RESIZABLE));
            }
        }

        إذا (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        إذا (iconic) {
            اكسر;
        }

        إذا (معلومات->initializing) {
            اكسر;
        }

        إذا (!معلومات->disable_move_سائيز_events) {
            إذا (GetClientRect(hwnd, &rect) && WIN_دري_Rect_Valid(&rect)) {
                Client_منزل_Screen(hwnd, (LPPOINT) &rect);
                Client_منزل_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.کاٻو;
                y = rect.چوٽي;

                SDL_Global_منزل_Relative_For_دري(معلومات->دري, x, y, &x, &y);
                SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            إذا (GetClientRect(hwnd, &rect) && WIN_دري_Rect_Valid(&rect)) {
                w = rect.ساڄو;
                h = rect.bottom;

                SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(معلومات->دري);

        // Update the window display position
        إذا (معلومات->دري->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_دري_ICCProfile(معلومات->دري, true);
        }

        // Update the position of any child windows
        لكل (win = معلومات->دري->پهريون_ٻار; win; win = win->ايندڙ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_دري_IS_POPUP(win) && !(win->flags & SDL_دري_HIDDEN)) {
                WIN_سيٽ_دري_Position_اندروني(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        إذا (g_Windows_پيغام_Hook) {
            إذا (!Dispatch_Modal_Loop_پيغام_Hook(&hwnd, &نياپو, &wParam, &lParam)) {
                أرجع 0;
            }
        }

        ++معلومات->اندريون_modal_loop;
        إذا (معلومات->اندريون_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_دري_Rect(معلومات->hwnd, &rect);
            معلومات->آخري_modal_ويڪر = rect.ساڄو - rect.کاٻو;
            معلومات->آخري_modal_اوچائي = rect.bottom - rect.چوٽي;

            معلومات->initial_سائيز_rect.کاٻو = معلومات->دري->x;
            معلومات->initial_سائيز_rect.ساڄو = معلومات->دري->x + معلومات->دري->w;
            معلومات->initial_سائيز_rect.چوٽي = معلومات->دري->y;
            معلومات->initial_سائيز_rect.bottom = معلومات->دري->y + معلومات->دري->h;

            سيٽ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        إذا (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_دري_جيئرو_Resize_Update(معلومات->دري);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#إذا 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            إذا (معلومات->videodata->DwmFlush) {
                معلومات->videodata->DwmFlush();
            }
#جيڪڏهن_پورو
#جيڪڏهن_پورو
            أرجع 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --معلومات->اندريون_modal_loop;
        إذا (معلومات->اندريون_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } اكسر;

    حالة WM_SIZING:
        {
            WPARAM ڪنارو = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool تالو_aspect_تناسب = (معلومات->دري->max_aspect == معلومات->دري->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            عائم new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            إذا (معلومات->دري->min_aspect <= 0 && معلومات->دري->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            سيٽ_Rect_خالي_جايون(&rc);
            إذا (!Adjust_دري_Rect_Ex(&rc, Get_دري_Style(hwnd), GetMenu(hwnd) != عدم, Get_دري_Ex_Style(hwnd))) {
                اكسر;
            }

            clientDragRect.کاٻو -= rc.کاٻو;
            clientDragRect.چوٽي -= rc.چوٽي;
            clientDragRect.ساڄو -= rc.ساڄو;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ساڄو - clientDragRect.کاٻو;
            h = clientDragRect.bottom - clientDragRect.چوٽي;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            إذا (تالو_aspect_تناسب) {
                بدل (ڪنارو) {
                حالة WMSZ_کاٻو:
                حالة WMSZ_ساڄو:
                    h = (صحيح)SDL_roundf(w / معلومات->دري->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * معلومات->دري->max_aspect);
                    اكسر;
                }
            } وإلا {
                بدل (ڪنارو) {
                حالة WMSZ_کاٻو:
                حالة WMSZ_ساڄو:
                    إذا (معلومات->دري->max_aspect > 0.0f && new_aspect > معلومات->دري->max_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->دري->max_aspect);
                    } وإلا إذا (معلومات->دري->min_aspect > 0.0f && new_aspect < معلومات->دري->min_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->دري->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_چوٽي:
                حالة WMSZ_BOTTOM:
                    إذا (معلومات->دري->min_aspect > 0.0f && new_aspect < معلومات->دري->min_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->دري->min_aspect);
                    } وإلا إذا (معلومات->دري->max_aspect > 0.0f && new_aspect > معلومات->دري->max_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->دري->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    إذا (معلومات->دري->max_aspect > 0.0f && new_aspect > معلومات->دري->max_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->دري->max_aspect);
                    } وإلا إذا (معلومات->دري->min_aspect > 0.0f && new_aspect < معلومات->دري->min_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->دري->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (ڪنارو) {
            حالة WMSZ_کاٻو:
                clientDragRect.کاٻو = clientDragRect.ساڄو - w;
                إذا (تالو_aspect_تناسب) {
                    clientDragRect.چوٽي = (معلومات->initial_سائيز_rect.bottom + معلومات->initial_سائيز_rect.چوٽي - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٽي;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.کاٻو = clientDragRect.ساڄو - w;
                clientDragRect.bottom = h + clientDragRect.چوٽي;
                اكسر;
            حالة WMSZ_ساڄو:
                clientDragRect.ساڄو = w + clientDragRect.کاٻو;
                إذا (تالو_aspect_تناسب) {
                    clientDragRect.چوٽي = (معلومات->initial_سائيز_rect.bottom + معلومات->initial_سائيز_rect.چوٽي - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٽي;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.ساڄو = w + clientDragRect.کاٻو;
                clientDragRect.چوٽي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_چوٽي:
                إذا (تالو_aspect_تناسب) {
                    clientDragRect.کاٻو = (معلومات->initial_سائيز_rect.ساڄو + معلومات->initial_سائيز_rect.کاٻو - w) / 2;
                }
                clientDragRect.ساڄو = w + clientDragRect.کاٻو;
                clientDragRect.چوٽي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.کاٻو = clientDragRect.ساڄو - w;
                clientDragRect.چوٽي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                إذا (تالو_aspect_تناسب) {
                    clientDragRect.کاٻو = (معلومات->initial_سائيز_rect.ساڄو + معلومات->initial_سائيز_rect.کاٻو - w) / 2;
                }
                clientDragRect.ساڄو = w + clientDragRect.کاٻو;
                clientDragRect.bottom = h + clientDragRect.چوٽي;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.ساڄو = w + clientDragRect.کاٻو;
                clientDragRect.bottom = h + clientDragRect.چوٽي;
                اكسر;
            }

            // convert the client rect to a window rect
            إذا (!Adjust_دري_Rect_Ex(&clientDragRect, Get_دري_Style(hwnd), GetMenu(hwnd) != عدم, Get_دري_Ex_Style(hwnd))) {
                اكسر;
            }

            *dragRect = clientDragRect;
        }
        اكسر;

    حالة WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        إذا (hittest == HTCLIENT) {
            سيٽ_Cursor(SDL_cursor);
            return_ڪوڊ = TRUE;
        } وإلا إذا (!g_دري_چوکٺو_Usable_While_Cursor_Hidden && !SDL_cursor) {
            سيٽ_Cursor(عدم);
            return_ڪوڊ = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        إذا (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = Get_دري_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            إذا (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                پڇاڙي_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, عدم);
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_EXPOSED, 0, 0);
        }
    }
        return_ڪوڊ = 0;
        اكسر;

        // We'll do our own drawing, prevent flicker
    حالة WM_ERASEBKGND:
        إذا (Should_Clear_دري_On_Erase_Background(معلومات)) {
            RECT client_rect;
            HBRUSH brush;
            معلومات->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        أرجع 1;

    حالة WM_SYSCOMMAND:
    {
        إذا (!g_WindowsEnableMenuMnemonics) {
            إذا ((wParam & 0xFFF0) == SC_KEYMENU) {
                أرجع 0;
            }
        }

#إذا defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        إذا ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            إذا (SDL_GetVideoDevice()->suspend_screensaver) {
                أرجع 0;
            }
        }
#جيڪڏهن_پورو // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
    }
        return_ڪوڊ = 0;
        اكسر;

    حالة WM_TOUCH:
        إذا (معلومات->videodata->Get_Touch_داخلا_Info && معلومات->videodata->Close_Touch_داخلا_Handle) {
            UINT i, انگ_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, انگ_inputs, &isstack);
            إذا (inputs && معلومات->videodata->Get_Touch_داخلا_Info((HTOUCHINPUT)lParam, انگ_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                إذا (!GetClientRect(hwnd, &rect) || !WIN_دري_Rect_Valid(&rect)) {
                    إذا (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                Client_منزل_Screen(hwnd, (LPPOINT)&rect);
                Client_منزل_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.چوٽي *= 100;
                rect.کاٻو *= 100;
                rect.bottom *= 100;
                rect.ساڄو *= 100;

                لكل (i = 0; i < انگ_inputs; ++i) {
                    PTOUCHINPUT داخلا_2 = &inputs[i];
                    ثابت صحيح w = (rect.ساڄو - rect.کاٻو);
                    ثابت صحيح h = (rect.bottom - rect.چوٽي);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)داخلا_2->h_ذريعو);
                    ثابت SDL_FingerID fingerId = (داخلا_2->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    إذا (SDL_جوڙيو_Touch(touchId, SDL_TOUCH_DEVICE_سڌو, (داخلا_2->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    إذا (w <= 1) {
                        x = 0.5f;
                    } وإلا {
                        x = (عائم)(داخلا_2->x - rect.کاٻو) / (w - 1);
                    }
                    إذا (h <= 1) {
                        y = 0.5f;
                    } وإلا {
                        y = (عائم)(داخلا_2->y - rect.چوٽي) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    إذا (داخلا_2->dwFlags & TOUCHEVENTF_هيٺ_ڏانهن) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->دري, SDL_EVENT_FINGER_هيٺ_ڏانهن, x, y, 1.0f);
                    }
                    إذا (داخلا_2->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->دري, x, y, 1.0f);
                    }
                    إذا (داخلا_2->dwFlags & TOUCHEVENTF_مٿي) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->دري, SDL_EVENT_FINGER_مٿي, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            معلومات->videodata->Close_Touch_داخلا_Handle((HTOUCHINPUT)lParam);
            أرجع 0;
        }
        اكسر;

#جيڪڏهن_وصف_ٿيل HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        أرجع TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#جيڪڏهن_پورو // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT ڳڻپ = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < ڳڻپ; ++i) {
            UINT سائيز = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR بفر_2 = (LPTSTR)SDL_malloc(حجم(TCHAR) * سائيز);
            إذا (بفر_2) {
                إذا (DragQueryFile(drop, i, بفر_2, سائيز)) {
                    حرف *file = WIN_String_منزل_UTF8(بفر_2);
                    SDL_SendDropFile(معلومات->دري, عدم, file);
                    SDL_free(file);
                }
                SDL_free(بفر_2);
            }
        }
        SDL_SendDropComplete(معلومات->دري);
        Drag_پڄاڻي(drop);
        أرجع 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_دري_Flags دري_flags = معلومات->دري->flags;
        إذا (wParam == TRUE && (دري_flags & SDL_دري_BORDERLESS) && !(دري_flags & SDL_دري_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            إذا (Get_دري_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_دري(hwnd, MONITOR_DEFAULTTONULL);
                إذا (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت نقطو_2 pt = { معلومات->دري->windowed.x, معلومات->دري->windowed.y };
                    hMonitor = Monitor_From_نقطو(pt, MONITOR_DEFAULTTONEAREST);
                }
                إذا (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_سائيز = حجم(info);
                    إذا (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وإلا إذا (!(دري_flags & SDL_دري_RESIZABLE) && !معلومات->force_ws_maximizebox) {
                صحيح w, h;
                إذا (معلومات->دري->آخري_سائيز_pending) {
                    w = معلومات->دري->pending.w;
                    h = معلومات->دري->pending.h;
                } وإلا {
                    w = معلومات->دري->floating.w;
                    h = معلومات->دري->floating.h;
                }
                params->rgrc[0].ساڄو = params->rgrc[0].کاٻو + w;
                params->rgrc[0].bottom = params->rgrc[0].چوٽي + h;
            }
            أرجع 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_دري *دري = معلومات->دري;

        إذا (دري->flags & SDL_دري_TOOLTIP) {
            أرجع HTTRANSPARENT;
        }

        إذا (دري->ڪاميابي_test) {
            نقطو_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            إذا (Screen_منزل_Client(hwnd, &winpoint)) {
                SDL_نقطو نقطو;
                SDL_ڪاميابي_Test_نتيجو rc;
                نقطو.x = winpoint.x;
                نقطو.y = winpoint.y;
                rc = دري->ڪاميابي_test(دري, &نقطو, دري->ڪاميابي_test_معلومات);
                بدل (rc) {
#وصف_ڪريو POST_ڪاميابي_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_ڪاميابي_TEST, 0, 0); \
        أرجع ret;                                                        \
    }
                حالة SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(عدم, عدم);
                    إذا (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_سيٽ_Mouse_Focus(دري);
                        أرجع HTCLIENT;
                    }

                    POST_ڪاميابي_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_ڪاميابي_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_چوٽي:
                    POST_ڪاميابي_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_ڪاميابي_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_ساڄو:
                    POST_ڪاميابي_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_ڪاميابي_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_ڪاميابي_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_ڪاميابي_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_کاٻو:
                    POST_ڪاميابي_TEST(HTLEFT);
#وصف_رد POST_ڪاميابي_TEST
                حالة SDL_HITTEST_عام:
                    أرجع HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } اكسر;

    حالة WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        إذا (معلومات->videodata->Get_Dpi_For_دري && معلومات->videodata->Adjust_دري_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحيح ايندڙ_DPI = (صحيح)wParam;
            ثابت صحيح prevDPI = (صحيح)معلومات->videodata->Get_Dpi_For_دري(hwnd);
            سائيز_3 *سائيز_اندريون_ٻاهريون = (سائيز_3 *)lParam;

            صحيح چوکٺو_w, چوکٺو_h;
            صحيح query_client_w_win, query_client_h_win;

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, ايندڙ_DPI, سائيز_اندريون_ٻاهريون->cx, سائيز_اندريون_ٻاهريون->cy);
#جيڪڏهن_پورو

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                إذا (!(معلومات->دري->flags & SDL_دري_BORDERLESS) && !SDL_دري_IS_POPUP(معلومات->دري)) {
                    WIN_Adjust_دري_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                چوکٺو_w = -rect.کاٻو + rect.ساڄو;
                چوکٺو_h = -rect.چوٽي + rect.bottom;

                query_client_w_win = سائيز_اندريون_ٻاهريون->cx - چوکٺو_w;
                query_client_h_win = سائيز_اندريون_ٻاهريون->cy - چوکٺو_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ساڄو = query_client_w_win;
                rect.bottom = query_client_h_win;

                إذا (!(معلومات->دري->flags & SDL_دري_BORDERLESS) && !SDL_دري_IS_POPUP(معلومات->دري)) {
                    WIN_Adjust_دري_Rect_For_HWND(hwnd, &rect, ايندڙ_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                سائيز_اندريون_ٻاهريون->cx = rect.ساڄو - rect.کاٻو;
                سائيز_اندريون_ٻاهريون->cy = rect.bottom - rect.چوٽي;
            }

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", سائيز_اندريون_ٻاهريون->cx, سائيز_اندريون_ٻاهريون->cy);
#جيڪڏهن_پورو
            أرجع TRUE;
        }
        اكسر;

    حالة WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحيح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحيح w, h;

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->کاٻو, suggestedRect->چوٽي, suggestedRect->ساڄو - suggestedRect->کاٻو, suggestedRect->bottom - suggestedRect->چوٽي);
#جيڪڏهن_پورو

            إذا (معلومات->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#جيڪڏهن_پورو
                أرجع 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ساڄو = معلومات->دري->w;
                rect.bottom = معلومات->دري->h;

                إذا (!(معلومات->دري->flags & SDL_دري_BORDERLESS)) {
                    WIN_Adjust_دري_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.ساڄو - rect.کاٻو;
                h = rect.bottom - rect.چوٽي;
            }

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    معلومات->دري->w, معلومات->دري->h,
                    suggestedRect->کاٻو, suggestedRect->چوٽي, w, h);
#جيڪڏهن_پورو

            معلومات->expected_resize = true;
            سيٽ_دري_Pos(hwnd,
                         عدم,
                         suggestedRect->کاٻو,
                         suggestedRect->چوٽي,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            معلومات->expected_resize = false;
            أرجع 0;
        }

    حالة WM_SETTINGCHANGE:
        إذا (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_سيٽ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_گهڻائي_For_HWND(hwnd);
        }
        إذا (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        إذا (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        اكسر;
#وإلا
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    حالة WM_سائيز:
    {
        RECT rect;
        صحيح w, h;

        إذا (GetClientRect(hwnd, &rect) && WIN_دري_Rect_Valid(&rect)) {
            w = rect.ساڄو;
            h = rect.bottom;
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESIZED, w, h);
        }
    } اكسر;
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (نياپو && نياپو == معلومات->videodata->WM_TASKBAR_BUTTON_CREATED) {
        معلومات->taskbar_button_created = true;
        WIN_Apply_دري_ترقي(SDL_GetVideoDevice(), معلومات->دري);
    }
#جيڪڏهن_پورو

    // If there's a window proc, assume it's going to handle messages
    إذا (معلومات->wndproc) {
        أرجع Call_دري_Proc(معلومات->wndproc, hwnd, نياپو, wParam, lParam);
    } وإلا إذا (return_ڪوڊ >= 0) {
        أرجع return_ڪوڊ;
    } وإلا {
        أرجع Call_دري_Proc(Def_دري_Proc, hwnd, نياپو, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    إذا (g_Windows_Enable_پيغام_Loop) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_منزل_MS(timeoutNS);
        ret = نياپو_Wait_For_گڻو_Objects(0, عدم, FALSE, timeout, QS_ALLINPUT);
        إذا (ret == WAIT_OBJECT_0) {
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#وإلا
        // MsgWaitForMultipleObjects is desktop-only.
        نياپو_2 نياپو;
        BOOL پيغام_نتيجو;
        UINT_PTR timer_id = 0;
        إذا (timeoutNS > 0) {
            timer_id = سيٽ_Timer(عدم, 0, (UINT)SDL_NS_منزل_MS(timeoutNS), عدم);
            پيغام_نتيجو = Get_پيغام(&نياپو, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } وإلا إذا (timeoutNS == 0) {
            پيغام_نتيجو = Peek_پيغام(&نياپو, عدم, 0, 0, PM_REMOVE);
        } وإلا {
            پيغام_نتيجو = Get_پيغام(&نياپو, 0, 0, 0);
        }
        إذا (پيغام_نتيجو) {
            إذا (نياپو.پيغام == WM_TIMER && !نياپو.hwnd && نياپو.wParam == timer_id) {
                أرجع 0;
            }
            إذا (g_Windows_پيغام_Hook) {
                إذا (!g_Windows_پيغام_Hook(g_Windows_پيغام_Hook_معلومات, &نياپو)) {
                    أرجع 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پيغام(&نياپو);
            Dispatch_پيغام(&نياپو);
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وإلا {
        // Fail the wait so the caller falls back to polling
        أرجع -1;
    }
}

فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Post_پيغام(معلومات->hwnd, معلومات->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    نياپو_2 نياپو;

    إذا (g_Windows_Enable_پيغام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پيغام(&نياپو, hwnd, 0, 0, PM_REMOVE)) {
            WIN_سيٽ_پيغام_Tick(نياپو.وقت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پيغام(&نياپو);
            Dispatch_پيغام(&نياپو);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    نياپو_2 نياپو;
#جيڪڏهن_وصف_ٿيل _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#هدايت warning(ڌڪو)
#هدايت warning(disable : 28159)
#جيڪڏهن_پورو
    DWORD پڇاڙي_ticks = Get_Tick_ڳڻپ() + 1;
#جيڪڏهن_وصف_ٿيل _MSC_VER
#هدايت warning(ڪڍو)
#جيڪڏهن_پورو
    صحيح new_messages = 0;

    إذا (_this->اندروني->gameinput_context) {
        WIN_Update_Game_داخلا(_this);
    }

    إذا (g_Windows_Enable_پيغام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پيغام(&نياپو, عدم, 0, 0, PM_REMOVE)) {
            إذا (g_Windows_پيغام_Hook) {
                إذا (!g_Windows_پيغام_Hook(g_Windows_پيغام_Hook_معلومات, &نياپو)) {
                    استمر;
                }
            }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            إذا (نياپو.پيغام == WM_MOUSEMOVE && SDL_آخري_warp_وقت) {
                إذا (!SDL_TICKS_PASSED(نياپو.وقت, (SDL_آخري_warp_وقت + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_آخري_warp_وقت = 0;
            }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_سيٽ_پيغام_Tick(نياپو.وقت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پيغام(&نياپو);
            Dispatch_پيغام(&نياپو);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            إذا (SDL_TICKS_PASSED(نياپو.وقت, پڇاڙي_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ثابت صحيح MAX_NEW_MESSAGES = 3;
                ++new_messages;
                إذا (new_messages > MAX_NEW_MESSAGES) {
                    اكسر;
                }
            }
        }

        SDL_processing_messages = false;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    إذا (keystate[SDL_SCANCODE_LSHIFT] && !(Get_ڪنجي_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    إذا (keystate[SDL_SCANCODE_RSHIFT] && !(Get_ڪنجي_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_دري *focus_دري = SDL_GetKeyboardFocus();
    إذا (!focus_دري || !(focus_دري->flags & SDL_دري_KEYBOARD_GRABBED)) {
        إذا (keystate[SDL_SCANCODE_LGUI] && !(Get_ڪنجي_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        إذا (keystate[SDL_SCANCODE_RGUI] && !(Get_ڪنجي_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    إذا (_this) {
        SDL_دري *دري = _this->windows;
        طالما (دري) {
            bool refresh_clipcursor = false;
            SDL_دري_معلومات *معلومات = دري->اندروني;
            إذا (معلومات) {
                refresh_clipcursor = معلومات->clipcursor_queued;
                معلومات->clipcursor_queued = false;    // Must be cleared unconditionally.
                معلومات->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            إذا (refresh_clipcursor) {
                WIN_UpdateClipCursor(دري);
            }
            دري = دري->ايندڙ;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_دري = SDL_GetKeyboardFocus();
    إذا (focus_دري && (focus_دري->flags & SDL_دري_MOUSE_CAPTURE)) {
        SDL_دري_معلومات *معلومات = focus_دري->اندروني;

        إذا (!معلومات->mouse_tracked) {
            نقطو_2 cursorPos;

            إذا (GetCursorPos(&cursorPos) && Screen_منزل_Client(معلومات->hwnd, &cursorPos)) {
                bool مٽا_سٽا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->دري, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->دري, mouseID,
                                    !مٽا_سٽا_Buttons ? SDL_BUTTON_کاٻو : SDL_BUTTON_ساڄو,
                                    (Get_Async_ڪنجي_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->دري, mouseID,
                                    !مٽا_سٽا_Buttons ? SDL_BUTTON_ساڄو : SDL_BUTTON_کاٻو,
                                    (Get_Async_ڪنجي_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->دري, mouseID,
                                    SDL_BUTTON_وچ,
                                    (Get_Async_ڪنجي_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->دري, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_ڪنجي_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->دري, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_ڪنجي_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_GDK
    GDK_Dispatch_Task_قطار();
#جيڪڏهن_پورو
}

ساكن صحيح app_registered = 0;
LPTSTR SDL_Appname = عدم;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = عدم;

ساكن فراغ WIN_Clean_رجسٽر_App(WNDCLASSEX wcex)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    إذا (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#جيڪڏهن_پورو
    SDL_free(SDL_Appname);
    SDL_Appname = عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (فراغ)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = ڀريو_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    أرجع FALSE;
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_رجسٽر_App(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#جيڪڏهن_پورو

    // Only do this once...
    إذا (app_registered) {
        ++app_registered;
        أرجع true;
    }
    SDL_assert(!SDL_Appname);
    إذا (!name) {
        name = "SDL_app";
#إذا defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#جيڪڏهن_پورو
    }
    SDL_Appname = WIN_UTF8_منزل_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(عدم);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_سائيز = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_دري_Proc;
    wcex.hInstance = SDL_Instance;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    إذا (hint && *hint) {
        wcex.hIcon = ڀريو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        إذا (hint && *hint) {
            wcex.hIconSm = ڀريو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وإلا {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_نالا(SDL_Instance, RT_گروهه_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    إذا (!رجسٽر_Class_Ex(&wcex)) {
        WIN_Clean_رجسٽر_App(wcex);
        أرجع SDL_سيٽ_Error("Couldn't register application class");
    }

    app_registered = 1;
    أرجع true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
فراغ SDL_UnregisterApp(فراغ)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    إذا (!app_registered) {
        أرجع;
    }
    --app_registered;
    إذا (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = عدم;
        wcex.hIconSm = عدم;
        // Check for any registered window classes.
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#جيڪڏهن_پورو
        WIN_Clean_رجسٽر_App(wcex);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS
