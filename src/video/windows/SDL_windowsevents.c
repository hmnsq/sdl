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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS

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
#که_تعریف_شوی HAVE_TPCSHRD_H
#ضمن <tpcshrd.h>
#د_که_پای // HAVE_TPCSHRD_H

#إذا 0
#تعریف_کړه WMMSG_DEBUG
#د_که_پای
#که_تعریف_شوی WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#د_که_پای

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
#د_که_پای

#که_تعریف_شوی SDL_PLATFORM_GDK
#ضمن "../../core/gdk/SDL_gdk.h"
#د_که_پای

// #define HIGHDPI_DEBUG

// Undocumented window messages
#که_نه_تعریف_شوی WM_NCUAHDRAWCAPTION
#تعریف_کړه WM_NCUAHDRAWCAPTION 0xAE
#د_که_پای
#که_نه_تعریف_شوی WM_NCUAHDRAWFRAME
#تعریف_کړه WM_NCUAHDRAWFRAME 0xAF
#د_که_پای

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#که_نه_تعریف_شوی WM_XBUTTONDOWN
#تعریف_کړه WM_XBUTTONDOWN 0x020B
#د_که_پای
#که_نه_تعریف_شوی WM_XBUTTONUP
#تعریف_کړه WM_XBUTTONUP 0x020C
#د_که_پای
#که_نه_تعریف_شوی GET_XBUTTON_WPARAM
#تعریف_کړه GET_XBUTTON_WPARAM(w) (HIWORD(w))
#د_که_پای
#که_نه_تعریف_شوی WM_ننوت
#تعریف_کړه WM_ننوت 0x00ff
#د_که_پای
#که_نه_تعریف_شوی WM_TOUCH
#تعریف_کړه WM_TOUCH 0x0240
#د_که_پای
#که_نه_تعریف_شوی WM_MOUSEHWHEEL
#تعریف_کړه WM_MOUSEHWHEEL 0x020E
#د_که_پای
#که_نه_تعریف_شوی RI_MOUSE_HWHEEL
#تعریف_کړه RI_MOUSE_HWHEEL 0x0800
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERUPDATE
#تعریف_کړه WM_POINTERUPDATE 0x0245
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERDOWN
#تعریف_کړه WM_POINTERDOWN 0x0246
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERUP
#تعریف_کړه WM_POINTERUP 0x0247
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERENTER
#تعریف_کړه WM_POINTERENTER 0x0249
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERLEAVE
#تعریف_کړه WM_POINTERLEAVE 0x024A
#د_که_پای
#که_نه_تعریف_شوی WM_POINTERCAPTURECHANGED
#تعریف_کړه WM_POINTERCAPTURECHANGED 0x024C
#د_که_پای
#که_نه_تعریف_شوی WM_UNICHAR
#تعریف_کړه WM_UNICHAR 0x0109
#د_که_پای
#که_نه_تعریف_شوی WM_DPICHANGED
#تعریف_کړه WM_DPICHANGED 0x02E0
#د_که_پای
#که_نه_تعریف_شوی WM_GETDPISCALEDSIZE
#تعریف_کړه WM_GETDPISCALEDSIZE 0x02E4
#د_که_پای
#که_نه_تعریف_شوی TOUCHEVENTF_PEN
#تعریف_کړه TOUCHEVENTF_PEN 0x0040
#د_که_پای

#که_نه_تعریف_شوی MAPVK_VK_منزل_VSC_EX
#تعریف_کړه MAPVK_VK_منزل_VSC_EX 4
#د_که_پای

#که_نه_تعریف_شوی WC_ERR_INVALID_CHARS
#تعریف_کړه WC_ERR_INVALID_CHARS 0x00000080
#د_که_پای

#که_نه_تعریف_شوی IS_لوړ_SURROGATE
#تعریف_کړه IS_لوړ_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#د_که_پای

#که_نه_تعریف_شوی USER_TIMER_MINIMUM
#تعریف_کړه USER_TIMER_MINIMUM 0x0000000A
#د_که_پای

// Used to compare Windows message timestamps
#تعریف_کړه SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#که_تعریف_شوی _WIN64
تعريفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#د_که_پای

ساكن bool SDL_processing_messages;
ساكن DWORD پیغام_tick;
ساكن Uint64 timestamp_دننه_واټن;

ساكن فراغ WIN_سېټ_پیغام_Tick(DWORD tick)
{
    پیغام_tick = tick;
}

ساكن Uint64 WIN_GetEventTimestamp(فراغ)
{
    ثابت Uint64 TIMESTAMP_WRAP_دننه_واټن = SDL_MS_منزل_NS(0x100000000LL);
    Uint64 timestamp, now;

    إذا (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        أرجع 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_منزل_NS(پیغام_tick);
    timestamp += timestamp_دننه_واټن;
    إذا (!timestamp_دننه_واټن) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_دننه_واټن = (now - timestamp);
        timestamp = now;
    } وإلا إذا ((Sint64)(now - timestamp - TIMESTAMP_WRAP_دننه_واټن) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_دننه_واټن += TIMESTAMP_WRAP_دننه_واټن;
        timestamp += TIMESTAMP_WRAP_دننه_واټن;
    } وإلا إذا (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_دننه_واټن -= (timestamp - now);
        timestamp = now;
    }
    أرجع timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_Windows_پیغام_Hook g_Windows_پیغام_Hook = عدم;
ساكن فراغ *g_Windows_پیغام_Hook_معلومات = عدم;

فراغ SDL_سېټ_Windows_پیغام_Hook(SDL_Windows_پیغام_Hook callback, فراغ *userdata)
{
    g_Windows_پیغام_Hook = callback;
    g_Windows_پیغام_Hook_معلومات = userdata;
}

ساكن SDL_Scancode Windows_لټون_کوډ_منزل_SDLScan_کوډ(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_کلی)
{
    SDL_Scancode کوډ;
    Uint8 شاخص;
    Uint16 کلی_Flags = HIWORD(lParam);
    Uint16 لټون_کوډ = LOBYTE(کلی_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    لټون_کوډ &= ~0x80;

    *virtual_کلی = (لټون_کوډ == 0);

    إذا (لټون_کوډ != 0) {
        إذا ((کلی_Flags & KF_EXTENDED) == KF_EXTENDED) {
            لټون_کوډ = MAKEWORD(لټون_کوډ, 0xe0);
        } وإلا إذا (لټون_کوډ == 0x45) {
            // Pause
            لټون_کوډ = 0xe046;
        }
    } وإلا {
        Uint16 vk_کوډ = LOWORD(wParam);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        لټون_کوډ = LOWORD(Map_Virtual_کلی(vk_کوډ, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        إذا (لټون_کوډ == 0xe11d) {
            لټون_کوډ = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    شاخص = LOBYTE(لټون_کوډ) | (HIBYTE(لټون_کوډ) ? 0x80 : 0x00);
    کوډ = windows_scancode_جدول[شاخص];
    *rawcode = لټون_کوډ;

    أرجع کوډ;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_کړکۍ_معلومات *معلومات)
{
    أرجع !SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_بدلون_Buttons, SDL_کړکۍ_معلومات *معلومات, Uint8 button, SDL_MouseID mouseID)
{
    إذا (b_بدلون_Buttons) {
        إذا (button == SDL_BUTTON_کیڼ) {
            button = SDL_BUTTON_ښی;
        } وإلا إذا (button == SDL_BUTTON_ښی) {
            button = SDL_BUTTON_کیڼ;
        }
    }

    إذا (معلومات->focus_click_pending & SDL_BUTTON_ماسک(button)) {
        // Ignore the button click for activation
        إذا (!bwParamMousePressed) {
            معلومات->focus_click_pending &= ~SDL_BUTTON_ماسک(button);
            WIN_UpdateClipCursor(معلومات->کړکۍ);
        }
        أرجع;
    }

    إذا (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_ماسک(button))) {
        SDL_SendMouseButton(timestamp, معلومات->کړکۍ, mouseID, button, true);
    } وإلا إذا (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_ماسک(button))) {
        SDL_SendMouseButton(timestamp, معلومات->کړکۍ, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_کړکۍ_معلومات *معلومات, SDL_MouseID mouseID)
{
    إذا (wParam != معلومات->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_کیڼ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_منځ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, معلومات, SDL_BUTTON_ښی, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, معلومات, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, معلومات, SDL_BUTTON_X2, mouseID);

        معلومات->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_کړکۍ_معلومات *معلومات)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT کلی_State;
    bool بدلون_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    بدلون_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    کلی_State = Get_Async_کلی_State(VK_LBUTTON);
    إذا (!(کلی_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, بدلون_Buttons, معلومات, SDL_BUTTON_کیڼ, mouseID);
    }
    کلی_State = Get_Async_کلی_State(VK_RBUTTON);
    إذا (!(کلی_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, بدلون_Buttons, معلومات, SDL_BUTTON_ښی, mouseID);
    }
    کلی_State = Get_Async_کلی_State(VK_MBUTTON);
    إذا (!(کلی_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, بدلون_Buttons, معلومات, SDL_BUTTON_منځ, mouseID);
    }
    کلی_State = Get_Async_کلی_State(VK_XBUTTON1);
    إذا (!(کلی_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, بدلون_Buttons, معلومات, SDL_BUTTON_X1, mouseID);
    }
    کلی_State = Get_Async_کلی_State(VK_XBUTTON2);
    إذا (!(کلی_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, بدلون_Buttons, معلومات, SDL_BUTTON_X2, mouseID);
    }
    معلومات->mouse_button_flags = (WPARAM)-1;
}

ساكن فراغ WIN_UpdateFocus(SDL_کړکۍ *کړکۍ, bool expect_focus, LPPOINT pos)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == کړکۍ);
    bool has_focus = (Get_Foreground_کړکۍ() == hwnd);

    إذا (had_focus == has_focus || has_focus != expect_focus) {
        أرجع;
    }

    إذا (has_focus) {
        ټکی_2 cursorPos;

        إذا (WIN_ShouldIgnoreFocusClick(معلومات) && !(کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
            bool بدلون_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            إذا (Get_Async_کلی_State(VK_LBUTTON)) {
                معلومات->focus_click_pending |= !بدلون_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            إذا (Get_Async_کلی_State(VK_RBUTTON)) {
                معلومات->focus_click_pending |= !بدلون_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            إذا (Get_Async_کلی_State(VK_MBUTTON)) {
                معلومات->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            إذا (Get_Async_کلی_State(VK_XBUTTON1)) {
                معلومات->focus_click_pending |= SDL_BUTTON_X1_ماسک;
            }
            إذا (Get_Async_کلی_State(VK_XBUTTON2)) {
                معلومات->focus_click_pending |= SDL_BUTTON_X2_ماسک;
            }
        }

        SDL_سېټ_Keyboard_Focus(کړکۍ->keyboard_focus ? کړکۍ->keyboard_focus : کړکۍ);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        إذا (!SDL_GetMouse()->relative_ډېرپېښ) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_منزل_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
        WIN_UpdateClipCursor(کړکۍ);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(معلومات->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلی_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_عدد, (Get_کلی_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلی_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_کړکۍ_ICCProfile(معلومات->کړکۍ, true);
    } وإلا {
        معلومات->دننه_کړکۍ_deactivation = true;

        SDL_سېټ_Keyboard_Focus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        إذا (SDL_GetMouse()->relative_ډېرپېښ) {
            SDL_سېټ_Mouse_Focus(عدم);
        }
        WIN_Reset_Dead_کلیګانې();

        WIN_Unclip_Cursor_For_کړکۍ(کړکۍ);

        معلومات->دننه_کړکۍ_deactivation = false;
    }
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool Should_Generate_کړکۍ_Close_On_Alt_F4(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool Should_Clear_کړکۍ_On_Erase_Background(SDL_کړکۍ_معلومات *معلومات)
{
    بدل (معلومات->hint_erase_background_ډېرپېښ) {
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
#تعریف_کړه MI_WP_SIGNATURE      0xFF515700
#تعریف_کړه MI_WP_SIGNATURE_ماسک 0xFFFFFF00
#تعریف_کړه IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_ماسک) == MI_WP_SIGNATURE

تعريفنوع تعداد
{
    SDL_MOUSE_EVENT_سرچینه_UNKNOWN,
    SDL_MOUSE_EVENT_سرچینه_MOUSE,
    SDL_MOUSE_EVENT_سرچینه_TOUCH,
    SDL_MOUSE_EVENT_سرچینه_PEN,
} SDL_MOUSE_EVENT_سرچینه;

ساكن SDL_MOUSE_EVENT_سرچینه Get_Mouse_پیغام_سرچینه(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    إذا (IsTouchEvent(extrainfo)) {
        إذا (extrainfo & 0x80) {
            أرجع SDL_MOUSE_EVENT_سرچینه_TOUCH;
        } وإلا {
            أرجع SDL_MOUSE_EVENT_سرچینه_PEN;
        }
    }
    أرجع SDL_MOUSE_EVENT_سرچینه_MOUSE;
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_کړکۍ_معلومات *WIN_Get_کړکۍ_معلومات_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_کړکۍ *کړکۍ;

    إذا (_this) {
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
            إذا (معلومات && معلومات->hwnd == hwnd) {
                أرجع معلومات;
            }
        }
    }
    أرجع عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح n_کوډ, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_معلومات = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_معلومات *معلومات = SDL_GetVideoDevice()->دننی;
    SDL_Scancode لټون_کوډ;

    إذا (n_کوډ < 0 || n_کوډ != HC_ACTION) {
        أرجع Call_بل_Hook_Ex(عدم, n_کوډ, wParam, lParam);
    }
    إذا (hook_معلومات->لټون_کوډ == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        أرجع 1;
    }

    بدل (hook_معلومات->vk_کوډ) {
    حالة VK_LWIN:
        لټون_کوډ = SDL_SCANCODE_LGUI;
        اكسر;
    حالة VK_RWIN:
        لټون_کوډ = SDL_SCANCODE_RGUI;
        اكسر;
    حالة VK_LMENU:
        لټون_کوډ = SDL_SCANCODE_LALT;
        اكسر;
    حالة VK_RMENU:
        لټون_کوډ = SDL_SCANCODE_RALT;
        اكسر;
    حالة VK_LCONTROL:
        لټون_کوډ = SDL_SCANCODE_LCTRL;
        اكسر;
    حالة VK_RCONTROL:
        لټون_کوډ = SDL_SCANCODE_RCTRL;
        اكسر;
    حالة VK_SNAPSHOT:
        لټون_کوډ = SDL_SCANCODE_PRINTSCREEN;
        اكسر;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالة VK_TAB:
        لټون_کوډ = SDL_SCANCODE_TAB;
        اكسر;
    حالة VK_ESCAPE:
        لټون_کوډ = SDL_SCANCODE_ESCAPE;
        اكسر;

    افتراضي:
        أرجع Call_بل_Hook_Ex(عدم, n_کوډ, wParam, lParam);
    }

    إذا (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        إذا (!معلومات->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, hook_معلومات->لټون_کوډ, لټون_کوډ, true);
        }
    } وإلا {
        إذا (!معلومات->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, hook_معلومات->لټون_کوډ, لټون_کوډ, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        إذا (hook_معلومات->vk_کوډ <= 0xFF && معلومات->pre_hook_کلی_state[hook_معلومات->vk_کوډ]) {
            معلومات->pre_hook_کلی_state[hook_معلومات->vk_کوډ] = 0;
            أرجع Call_بل_Hook_Ex(عدم, n_کوډ, wParam, lParam);
        }
    }

    أرجع 1;
}

ساكن bool WIN_بدلون_Buttons(HANDLE hDevice)
{
    إذا (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        أرجع false;
    }
    أرجع GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_Handle_Raw_Mouse_ننوت(Uint64 timestamp, SDL_Video_معلومات *معلومات, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool ښکته;
    } raw_buttons[] = {
        { RI_MOUSE_کیڼ_BUTTON_ښکته, SDL_BUTTON_کیڼ, true },
        { RI_MOUSE_کیڼ_BUTTON_پورته, SDL_BUTTON_کیڼ, false },
        { RI_MOUSE_ښی_BUTTON_ښکته, SDL_BUTTON_ښی, true },
        { RI_MOUSE_ښی_BUTTON_پورته, SDL_BUTTON_ښی, false },
        { RI_MOUSE_منځ_BUTTON_ښکته, SDL_BUTTON_منځ, true },
        { RI_MOUSE_منځ_BUTTON_پورته, SDL_BUTTON_منځ, false },
        { RI_MOUSE_BUTTON_4_ښکته, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_پورته, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_ښکته, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_پورته, SDL_BUTTON_X2, false }
    };

    صحيح dx = (صحيح)rawmouse->l_وروستی_X;
    صحيح dy = (صحيح)rawmouse->l_وروستی_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    إذا (!معلومات->raw_mouse_enabled) {
        أرجع;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_کړکۍ *کړکۍ = SDL_GetKeyboardFocus();
    إذا (!کړکۍ) {
        أرجع;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse) {
        أرجع;
    }

    إذا (Get_Mouse_پیغام_سرچینه(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_سرچینه_MOUSE ||
        (SDL_Touch_Devices_شته() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        أرجع;
    }

    SDL_کړکۍ_معلومات *windowdata = کړکۍ->دننی;

    إذا (haveMotion && !windowdata->دننه_modal_loop) {
        إذا (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, کړکۍ, mouseID, true, (عائم)dx, (عائم)dy);
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
            إذا (معلومات->وروستی_raw_mouse_position.x == 0 && معلومات->وروستی_raw_mouse_position.y == 0) {
                معلومات->وروستی_raw_mouse_position.x = x;
                معلومات->وروستی_raw_mouse_position.y = y;
            }
            relX = x - معلومات->وروستی_raw_mouse_position.x;
            relY = y - معلومات->وروستی_raw_mouse_position.y;

            إذا (remote_desktop) {
                إذا (!windowdata->دننه_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    إذا (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.کیڼ + ((rect.ښی - rect.کیڼ) / 2) + wobble;
                        صحيح warpY = rect.سر + ((rect.bottom - rect.سر) / 2);

                        WIN_سېټ_Cursor_Pos(warpX, warpY);

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
                            SDL_SendMouseMotion(timestamp, کړکۍ, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } وإلا إذا (mouse->pen_mouse_events) {
                ثابت صحيح اعظمي_TABLET_RELATIVE_MOTION = 32;
                إذا (SDL_abs(relX) > اعظمي_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > اعظمي_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وإلا {
                    SDL_SendMouseMotion(timestamp, کړکۍ, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } وإلا {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                إذا (!معلومات->raw_ننوت_fake_pen_id) {
                    معلومات->raw_ننوت_fake_pen_id = SDL_جمع_کړه_Pen_Device(timestamp, "raw mouse input", کړکۍ, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, معلومات->raw_ننوت_fake_pen_id, کړکۍ, (عائم)(x + screen_x - کړکۍ->x), (عائم)(y + screen_y - کړکۍ->y));
            }

            معلومات->وروستی_raw_mouse_position.x = x;
            معلومات->وروستی_raw_mouse_position.y = y;
        }
    }

    إذا (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            إذا (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool ښکته = raw_buttons[i].ښکته;

                إذا (button == SDL_BUTTON_کیڼ) {
                    إذا (WIN_بدلون_Buttons(hDevice)) {
                        button = SDL_BUTTON_ښی;
                    }
                } وإلا إذا (button == SDL_BUTTON_ښی) {
                    إذا (WIN_بدلون_Buttons(hDevice)) {
                        button = SDL_BUTTON_کیڼ;
                    }
                }

                إذا (windowdata->focus_click_pending & SDL_BUTTON_ماسک(button)) {
                    // Ignore the button click for activation
                    إذا (!ښکته) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_ماسک(button);
                        WIN_UpdateClipCursor(کړکۍ);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, کړکۍ, mouseID, button, ښکته);
            }
        }

        إذا (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_معلومات;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کړکۍ, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_نورمال);
        } وإلا إذا (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_معلومات;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کړکۍ, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_نورمال);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_Handle_Raw_Keyboard_ننوت(Uint64 timestamp, SDL_Video_معلومات *معلومات, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    إذا (!معلومات->raw_keyboard_enabled) {
        أرجع;
    }

    إذا (rawkeyboard->Flags & RI_کلی_E1) {
        // First key in a Ctrl+{key} sequence
        معلومات->pending_E1_کلی_sequence = true;
        أرجع;
    }

    إذا ((rawkeyboard->Flags & RI_کلی_E0) && rawkeyboard->Make_کوډ == 0x2A) {
        // 0xE02A make code prefix, ignored
        أرجع;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!rawkeyboard->Make_کوډ) {
        rawkeyboard->Make_کوډ = LOWORD(Map_Virtual_کلی(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
    }
#د_که_پای
    إذا (!rawkeyboard->Make_کوډ) {
        أرجع;
    }

    bool ښکته;
    بدل (rawkeyboard->پیغام_4) {
    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
        ښکته = true;
        اكسر;
    حالة WM_KEYUP:
    حالة WM_SYSKEYUP:
        ښکته = false;
        اكسر;
    افتراضي:
        ښکته = !(rawkeyboard->Flags & RI_کلی_BREAK);
        اكسر;
    }

    SDL_Scancode کوډ;
    USHORT rawcode = rawkeyboard->Make_کوډ;
    إذا (معلومات->pending_E1_کلی_sequence) {
        rawcode |= 0xE100;
        إذا (rawkeyboard->Make_کوډ == 0x45) {
            // Ctrl+NumLock == Pause
            کوډ = SDL_SCANCODE_PAUSE;
        } وإلا {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            کوډ = SDL_SCANCODE_UNKNOWN;
        }
        معلومات->pending_E1_کلی_sequence = false;
    } وإلا {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 شاخص = (Uint8)rawkeyboard->Make_کوډ;
        إذا (rawkeyboard->Flags & RI_کلی_E0) {
            rawcode |= 0xE000;
            شاخص |= 0x80;
        }
        کوډ = windows_scancode_جدول[شاخص];
    }

    إذا (ښکته) {
        SDL_کړکۍ *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        إذا ((!معلومات->raw_keyboard_flag_inputsink && !focus) || (focus && focus->متن_ننوت_فعال)) {
            أرجع;
        }
    }

    SDL_Send_Keyboard_کلی(timestamp, keyboardID, rawcode, کوډ, ښکته);
}

فراغ WIN_Poll_Raw_ننوت(SDL_VideoDevice *_this, Uint64 poll_پیل)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    UINT اندازه, i, شمېر, ټول = 0;
    RAWINPUT *ننوت;
    Uint64 poll_پای;

    إذا (معلومات->rawinput_دننه_واټن == 0) {
        BOOL isWow64;

        معلومات->rawinput_دننه_واټن = حجم(RAWINPUTHEADER);
        إذا (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            معلومات->rawinput_دننه_واټن += 8;
        }
    }

    // Get all available events
    ننوت = (RAWINPUT *)معلومات->rawinput;
    لكل (;;) {
        اندازه = معلومات->rawinput_اندازه - (UINT)((BYTE *)ننوت - معلومات->rawinput);
        شمېر = Get_Raw_ننوت_بفر(ننوت, &اندازه, حجم(RAWINPUTHEADER));
        poll_پای = SDL_GetTicksNS();
        إذا (شمېر == 0 || شمېر == (UINT)-1) {
            إذا (!معلومات->rawinput || (شمېر == (UINT)-1 && Get_وروستی_Error() == ERROR_INSUFFICIENT_بفر)) {
                ثابت UINT RAWINPUT_بفر_اندازه_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(معلومات->rawinput, معلومات->rawinput_اندازه + RAWINPUT_بفر_اندازه_INCREMENT);
                إذا (!rawinput) {
                    اكسر;
                }
                ننوت = (RAWINPUT *)(rawinput + ((BYTE *)ننوت - معلومات->rawinput));
                معلومات->rawinput = rawinput;
                معلومات->rawinput_اندازه += RAWINPUT_بفر_اندازه_INCREMENT;
            } وإلا {
                اكسر;
            }
        } وإلا {
            ټول += شمېر;

            // Advance input to the end of the buffer
            طالما (شمېر--) {
                ننوت = NEXTRAWINPUTBLOCK(ننوت);
            }
        }
    }

    إذا (ټول > 0) {
        Uint64 delta = poll_پای - poll_پیل;
        UINT mouse_ټول = 0;
        لكل (i = 0, ننوت = (RAWINPUT *)معلومات->rawinput; i < ټول; ++i, ننوت = NEXTRAWINPUTBLOCK(ننوت)) {
            إذا (ننوت->سرلیک.dwType == RIM_TYPEMOUSE) {
                mouse_ټول += 1;
            }
        }
        صحيح mouse_شاخص = 0;
        لكل (i = 0, ننوت = (RAWINPUT *)معلومات->rawinput; i < ټول; ++i, ننوت = NEXTRAWINPUTBLOCK(ننوت)) {
            إذا (ننوت->سرلیک.dwType == RIM_TYPEMOUSE) {
                mouse_شاخص += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)ننوت + معلومات->rawinput_دننه_واټن);
                Uint64 وخت = poll_پای - (delta * (mouse_ټول - mouse_شاخص)) / mouse_ټول;
                WIN_Handle_Raw_Mouse_ننوت(وخت, معلومات, ننوت->سرلیک.hDevice, rawmouse);
            } وإلا إذا (ننوت->سرلیک.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)ننوت + معلومات->rawinput_دننه_واټن);
                WIN_Handle_Raw_Keyboard_ننوت(poll_پای, معلومات, ننوت->سرلیک.hDevice, rawkeyboard);
            }
        }
    }
    معلومات->وروستی_rawinput_poll = poll_پای;
}

ساكن فراغ جمع_کړه_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *شمېر)
{
    صحيح new_شمېر = (*شمېر + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمېر * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمېر - 1] = deviceID;

    *شمېر = new_شمېر;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح شمېر)
{
    لكل (صحيح i = 0; i < شمېر; ++i) {
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
        حرف devName[MAX_لار + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_ننوت_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        إذا (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            إذا (hFile != INVALID_HANDLE_ارزښت) {
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
        معلومات.cb_اندازه = حجم(معلومات);
        لكل (DWORD i = 0;; ++i) {
            إذا (!تیاری_Di_Enum_Device_Info(devinfo, i, &معلومات)) {
                إذا (Get_وروستی_Error() == ERROR_NO_نور_توکي) {
                    اكسر;
                } وإلا {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            إذا (!تیاری_Di_Get_Device_Instance_Id_A(devinfo, &معلومات, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            إذا (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD اندازه = 0;
                إذا (تیاری_Di_Get_Device_Registry_Property_W(devinfo, &معلومات, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &اندازه)) {
                    // Make sure the device description is null terminated
                    اندازه /= حجم(*prod);
                    إذا (اندازه >= SDL_arraysize(prod)) {
                        // Truncated description...
                        اندازه = (SDL_arraysize(prod) - 1);
                    }
                    prod[اندازه] = 0;

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
    UINT raw_device_شمېر = 0;
    صحيح old_keyboard_شمېر = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_شمېر = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_شمېر = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_شمېر = 0;
    SDL_MouseID *new_mice = عدم;

    إذا (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->دننی->detect_device_hotplug ||
        _this->دننی->gameinput_context) {
        أرجع;
    }

    إذا ((Get_Raw_ننوت_Device_List(عدم, &raw_device_شمېر, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_شمېر)) {
        أرجع; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_شمېر);
    إذا (!raw_devices) {
        أرجع; // oh well.
    }

    raw_device_شمېر = Get_Raw_ننوت_Device_List(raw_devices, &raw_device_شمېر, حجم(RAWINPUTDEVICELIST));
    إذا (raw_device_شمېر == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        أرجع; // oh well.
    }

    HDEVINFO devinfo = تیاری_Di_Get_Class_Devs_A(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمېر);
    old_mice = SDL_GetMice(&old_mouse_شمېر);

    لكل (UINT i = 0; i < raw_device_شمېر; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_لار] = { 0 };
        UINT rdi_اندازه = حجم(rdi);
        UINT name_اندازه = SDL_arraysize(devName);
        صحيح vendor = 0, حاصل_ضرب = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        إذا (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cb_اندازه = حجم(rdi);
        إذا (Get_Raw_ننوت_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_اندازه) == ((UINT)-1) ||
            Get_Raw_ننوت_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_اندازه) == ((UINT)-1)) {
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
            إذا (SDL_IsKeyboard((Uint16)vendor, (Uint16)حاصل_ضرب, rdi.keyboard.dw_شمېره_د_کلیګانې_ټول)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جمع_کړه_Device_ID(keyboardID, &new_keyboards, &new_keyboard_شمېر);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمېر)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Keyboard", hid_loaded);
                    SDL_جمع_کړه_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            إذا (SDL_IsMouse((Uint16)vendor, (Uint16)حاصل_ضرب)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جمع_کړه_Device_ID(mouseID, &new_mice, &new_mouse_شمېر);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_شمېر)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Mouse", hid_loaded);
                    SDL_جمع_کړه_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    لكل (صحيح i = old_keyboard_شمېر; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمېر)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_شمېر; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمېر)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    تیاری_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ساكن bool Skip_Alt_Gr_کیڼ_Control(WPARAM wParam, LPARAM lParam)
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
    پیغام_3 بل_پیغام;
    DWORD پیغام_وخت = Get_پیغام_وخت();
    إذا (Peek_پیغام(&بل_پیغام, عدم, 0, 0, PM_NOREMOVE)) {
        إذا (بل_پیغام.پیغام == WM_KEYDOWN ||
            بل_پیغام.پیغام == WM_SYSKEYDOWN) {
            إذا (بل_پیغام.wParam == VK_MENU && (بل_پیغام.lParam & 0x01000000) && بل_پیغام.وخت == پیغام_وخت) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                أرجع true;
            }
        }
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع false;
}

ساكن bool Dispatch_Modal_Loop_پیغام_Hook(HWND *hwnd, UINT *پیغام_2, WPARAM *wParam, LPARAM *lParam)
{
    پیغام_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.پیغام = *پیغام_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    إذا (g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_معلومات, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *پیغام_2 = dummy.پیغام;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        أرجع true;
    }
    أرجع false;
}

LRESULT CALLBACK WIN_کړکۍ_Proc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam)
{
    SDL_کړکۍ_معلومات *معلومات;
    LRESULT return_کوډ = -1;

    // Get the window data for the window
    معلومات = WIN_Get_کړکۍ_معلومات_From_HWND(hwnd);
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!معلومات) {
        // Fallback
        معلومات = (SDL_کړکۍ_معلومات *)GetProp(hwnd, متن_2("SDL_WindowData"));
    }
#د_که_پای
    إذا (!معلومات) {
        أرجع Call_کړکۍ_Proc(Def_کړکۍ_Proc, hwnd, پیغام_2, wParam, lParam);
    }

#که_تعریف_شوی WMMSG_DEBUG
    {
        حرف پیغام[1024];
        إذا (پیغام_2 > MAX_WMMSG) {
            SDL_snprintf(پیغام, حجم(پیغام), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, پیغام_2, wParam, lParam);
        } وإلا {
            SDL_snprintf(پیغام, حجم(پیغام), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[پیغام_2], wParam, lParam);
        }
        OutputDebugStringA(پیغام);
    }
#د_که_پای // WMMSG_DEBUG


    إذا (g_Windows_پیغام_Hook && معلومات->دننه_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        إذا (!Dispatch_Modal_Loop_پیغام_Hook(&hwnd, &پیغام_2, &wParam, &lParam)) {
            أرجع 0;
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (WIN_HandleIMEMessage(hwnd, پیغام_2, wParam, &lParam, معلومات->videodata)) {
        أرجع 0;
    }
#د_که_پای

    بدل (پیغام_2) {

    حالة WM_SHOWWINDOW:
    {
        إذا (wParam) {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
        } وإلا {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_HIDDEN, 0, 0);
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
        ټکی_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(معلومات->کړکۍ, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
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
        إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
            return_کوډ = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        ټکی_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(معلومات->کړکۍ, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        إذا (SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ)) {
            أرجع MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_کړکۍ *پلار = معلومات->کړکۍ->پلار;
        طالما (پلار) {
            إذا ((پلار->flags & SDL_کړکۍ_ننوت_FOCUS) &&
                (پلار->flags & SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ)) {
                أرجع MA_NOACTIVATE;
            }
            پلار = پلار->پلار;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        ټکی_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(معلومات->کړکۍ, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        ټکی_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(معلومات->کړکۍ, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_ګر_ننوت_TYPE اشاره_ګر_type = PT_اشاره_ګر;
        إذا (!معلومات->videodata->Get_اشاره_ګر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!معلومات->videodata->Get_اشاره_ګر_Type(pointerid, &اشاره_ګر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشاره_ګر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle(hpointer);
        إذا (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, معلومات->کړکۍ, true, true);
        } وإلا {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_واټن | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.عدد_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_جمع_کړه_Pen_Device(WIN_GetEventTimestamp(), عدم, معلومات->کړکۍ, &info, hpointer, true);
        }
        return_کوډ = 0;
    } اكسر;

    حالة WM_POINTERCAPTURECHANGED:
    حالة WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_ګر_ننوت_TYPE اشاره_ګر_type = PT_اشاره_ګر;
        إذا (!معلومات->videodata->Get_اشاره_ګر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!معلومات->videodata->Get_اشاره_ګر_Type(pointerid, &اشاره_ګر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشاره_ګر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle(hpointer);
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        إذا ((پیغام_2 == WM_POINTERCAPTURECHANGED) || !IS_اشاره_ګر_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, معلومات->کړکۍ, false, false);
        }
        return_کوډ = 0;
    } اكسر;

    حالة WM_POINTERDOWN:
    حالة WM_POINTERUP:
    حالة WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_ګر_ننوت_TYPE اشاره_ګر_type = PT_اشاره_ګر;
        إذا (!معلومات->videodata->Get_اشاره_ګر_Type || !معلومات->videodata->Get_اشاره_ګر_Type(pointerid, &اشاره_ګر_type)) {
            اكسر;  // oh well.
        } وإلا إذا ((پیغام_2 == WM_POINTERUPDATE) && (اشاره_ګر_type == PT_MOUSE)) {
            معلومات->وروستی_اشاره_ګر_update = lParam;
            return_کوډ = 0;
            اكسر;
        } وإلا إذا (اشاره_ګر_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle(hpointer);
        اشاره_ګر_PEN_INFO pen_info;
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } وإلا إذا (!معلومات->videodata->Get_اشاره_ګر_Pen_Info || !معلومات->videodata->Get_اشاره_ګر_Pen_Info(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

        ثابت bool istouching = IS_اشاره_ګر_INCONTACT_WPARAM(wParam) && IS_اشاره_ګر_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        إذا (!istouching) {
            SDL_SendPenTouch(timestamp, pen, کړکۍ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت اشاره_ګر_INFO *اشاره_ګر_info = &pen_info.اشاره_ګر_Info;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        إذا (!معلومات->videodata->Get_اشاره_ګر_Device_Rects || !معلومات->videodata->Get_اشاره_ګر_Device_Rects(اشاره_ګر_info->سرچینه_Device, &tablet_bounds, &tablet_mapping)) {
            ټکی_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_منزل_Client(معلومات->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } وإلا {
            صحيح ix, iy;
            SDL_Get_کړکۍ_Position(کړکۍ, &ix, &iy);
            ثابت SDL_FPoint کړکۍ_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = اشاره_ګر_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.ښی );
            ثابت عائم facY = اشاره_ګر_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.ښی  - tablet_mapping.کیڼ;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.سر;

            fx = (tablet_mapping.کیڼ + (facX * w)) - کړکۍ_pos.x;
            fy = (tablet_mapping.سر  + (facY * h)) - کړکۍ_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, کړکۍ, fx, fy);
        SDL_SendPenButton(timestamp, pen, کړکۍ, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, کړکۍ, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        إذا (pen_info.pen_ماسک & PEN_ماسک_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, کړکۍ, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, کړکۍ, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, کړکۍ, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, کړکۍ, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        إذا (istouching) {
            SDL_SendPenTouch(timestamp, pen, کړکۍ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_کوډ = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

        إذا (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
            bool wish_clip_cursor = (
                کړکۍ->flags & (SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ | SDL_کړکۍ_MOUSE_GRABBED) ||
                (کړکۍ->mouse_rect.w > 0 && کړکۍ->mouse_rect.h > 0)
            );
            إذا (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                معلومات->clipcursor_queued = true;
            }
        }

        إذا (!معلومات->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_اندازه = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = معلومات->hwnd;

            إذا (TrackMouseEvent(&trackMouseEvent)) {
                معلومات->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
        }

        إذا (!معلومات->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            إذا (Get_Mouse_پیغام_سرچینه((ULONG)Get_پیغام_Extra_Info()) == SDL_MOUSE_EVENT_سرچینه_MOUSE &&
                lParam != معلومات->وروستی_اشاره_ګر_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)GET_X_LPARAM(lParam), (عائم)GET_Y_LPARAM(lParam));
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
            إذا (Get_Mouse_پیغام_سرچینه((ULONG)Get_پیغام_Extra_Info()) == SDL_MOUSE_EVENT_سرچینه_MOUSE &&
                lParam != معلومات->وروستی_اشاره_ګر_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, معلومات, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#إذا 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_ننوت:
    {
        HRAWINPUT h_Raw_ننوت = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT اندازه = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        إذا (معلومات->کړکۍ != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        Get_Raw_ننوت_معلومات(h_Raw_ننوت, RID_ننوت, &inp, &اندازه, حجم(RAWINPUTHEADER));
        إذا (inp.سرلیک.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_ننوت(WIN_GetEventTimestamp(), معلومات, inp.سرلیک.hDevice, &inp.معلومات.mouse);
        } وإلا إذا (inp.سرلیک.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_ننوت(WIN_GetEventTimestamp(), معلومات, inp.سرلیک.hDevice, &inp.معلومات.keyboard);
        }
    } اكسر;
#د_که_پای

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        إذا (!معلومات->videodata->raw_mouse_enabled) {
            لنډ amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            إذا (پیغام_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_نورمال);
            } وإلا {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_نورمال);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
            إذا (SDL_GetMouseFocus() == معلومات->کړکۍ && !SDL_GetMouse()->relative_ډېرپېښ && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_پیغام_Pos();
                ټکی_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_منزل_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                إذا (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } وإلا {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    إذا (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->کړکۍ, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } وإلا { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            إذا (!SDL_GetMouse()->relative_ډېرپېښ) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_سېټ_Mouse_Focus(عدم);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        معلومات->mouse_tracked = false;

        return_کوډ = 0;
        اكسر;
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
    {
        إذا (Skip_Alt_Gr_کیڼ_Control(wParam, lParam)) {
            return_کوډ = 0;
            اكسر;
        }

        bool virtual_کلی = false;
        Uint16 rawcode = 0;
        SDL_Scancode کوډ = Windows_لټون_کوډ_منزل_SDLScan_کوډ(lParam, wParam, &rawcode, &virtual_کلی);

        // Detect relevant keyboard shortcuts
        إذا (کوډ == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            إذا (Should_Generate_کړکۍ_Close_On_Alt_F4()) {
                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
            }
        }

        إذا (virtual_کلی || !معلومات->videodata->raw_keyboard_enabled || معلومات->کړکۍ->متن_ننوت_فعال) {
            SDL_Send_Keyboard_کلی(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوډ, true);
        }
    }

        return_کوډ = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        إذا (Skip_Alt_Gr_کیڼ_Control(wParam, lParam)) {
            return_کوډ = 0;
            اكسر;
        }

        bool virtual_کلی = false;
        Uint16 rawcode = 0;
        SDL_Scancode کوډ = Windows_لټون_کوډ_منزل_SDLScan_کوډ(lParam, wParam, &rawcode, &virtual_کلی);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        إذا (virtual_کلی || !معلومات->videodata->raw_keyboard_enabled || معلومات->کړکۍ->متن_ننوت_فعال) {
            إذا (کوډ == SDL_SCANCODE_PRINTSCREEN && !keyboardState[کوډ]) {
                SDL_Send_Keyboard_کلی(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوډ, true);
            }
            SDL_Send_Keyboard_کلی(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوډ, false);
        }
    }
        return_کوډ = 0;
        اكسر;

    حالة WM_UNICHAR:
        إذا (wParam == UNICODE_NOCHAR) {
            return_کوډ = 1;
        } وإلا {
            إذا (SDL_متن_ننوت_فعال(معلومات->کړکۍ)) {
                حرف متن[5];
                حرف *پای_ټکی = SDL_UCS4_منزل_UTF8((Uint32)wParam, متن);
                *پای_ټکی = '\0';
                SDL_Send_Keyboard_متن(متن);
            }
            return_کوډ = 0;
        }
        اكسر;

    حالة WM_CHAR:
        إذا (SDL_متن_ننوت_فعال(معلومات->کړکۍ)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            إذا (IS_لوړ_SURROGATE(wParam)) {
                معلومات->لوړ_surrogate = (WCHAR)wParam;
            } وإلا {
                WCHAR utf16[3];

                utf16[0] = معلومات->لوړ_surrogate ? معلومات->لوړ_surrogate : (WCHAR)wParam;
                utf16[1] = معلومات->لوړ_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح پایله = WIN_Wide_Char_منزل_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                إذا (پایله > 0) {
                    SDL_Send_Keyboard_متن(utf8);
                }
                معلومات->لوړ_surrogate = L'\0';
            }
        } وإلا {
            معلومات->لوړ_surrogate = L'\0';
        }

        return_کوډ = 0;
        اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#که_تعریف_شوی WM_INPUTLANGCHANGE
    حالة WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_کوډ = 1;
        اكسر;
#د_که_پای // WM_INPUTLANGCHANGE

    حالة WM_NCLBUTTONDOWN:
    {
        معلومات->دننه_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        إذا (Send_پیغام(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            ټکی_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_منزل_Client(hwnd, &cursorPos);
            Post_پیغام(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } اكسر;

    حالة WM_CAPTURECHANGED:
    {
        معلومات->دننه_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), معلومات);
    } اكسر;

#که_تعریف_شوی WM_GETMINMAXINFO
    حالة WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT اندازه;
        صحيح x, y;
        صحيح w, h;
        صحيح min_w, min_h;
        صحيح max_w, max_h;
        BOOL constrain_max_اندازه;

        // If this is an expected size change, allow it
        إذا (معلومات->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        Get_کړکۍ_Rect(hwnd, &اندازه);
        x = اندازه.کیڼ;
        y = اندازه.سر;

        // Calculate current size of our window
        SDL_Get_کړکۍ_اندازه(معلومات->کړکۍ, &w, &h);
        SDL_Get_کړکۍ_Minimum_اندازه(معلومات->کړکۍ, &min_w, &min_h);
        SDL_Get_کړکۍ_اعظمي_اندازه(معلومات->کړکۍ, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        إذا (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_اندازه = TRUE;
        } وإلا {
            constrain_max_اندازه = FALSE;
        }

        إذا (!(SDL_Get_کړکۍ_Flags(معلومات->کړکۍ) & SDL_کړکۍ_BORDERLESS) && !SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ)) {
            اندازه.سر = 0;
            اندازه.کیڼ = 0;
            اندازه.bottom = h;
            اندازه.ښی = w;
            WIN_Adjust_کړکۍ_Rect_For_HWND(hwnd, &اندازه, 0);
            w = اندازه.ښی - اندازه.کیڼ;
            h = اندازه.bottom - اندازه.سر;
#که_تعریف_شوی HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#د_که_پای
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        إذا (SDL_Get_کړکۍ_Flags(معلومات->کړکۍ) & SDL_کړکۍ_RESIZABLE) {
            إذا (SDL_Get_کړکۍ_Flags(معلومات->کړکۍ) & SDL_کړکۍ_BORDERLESS) {
                صحيح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحيح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_اندازه.x = SDL_max(w, screenW);
                info->pt_Max_اندازه.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_اندازه.x = (LONG)w + min_w;
            info->pt_Min_Track_اندازه.y = (LONG)h + min_h;
            إذا (constrain_max_اندازه) {
                info->pt_Max_Track_اندازه.x = (LONG)w + max_w;
                info->pt_Max_Track_اندازه.y = (LONG)h + max_h;
            }
        } وإلا {
            info->pt_Max_اندازه.x = w;
            info->pt_Max_اندازه.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_اندازه.x = w;
            info->pt_Min_Track_اندازه.y = h;
            info->pt_Max_Track_اندازه.x = w;
            info->pt_Max_Track_اندازه.y = h;
        }
    }
        return_کوډ = 0;
        اكسر;
#د_که_پای // WM_GETMINMAXINFO

    حالة WM_WINDOWPOSCHANGING:

        إذا (معلومات->expected_resize) {
            return_کوډ = 0;
        } وإلا إذا (معلومات->دننه_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            إذا (معلومات->وروستی_modal_پلنوالی == windowpos->cx && معلومات->وروستی_modal_لوړوالی == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            معلومات->وروستی_modal_پلنوالی = windowpos->cx;
            معلومات->وروستی_modal_لوړوالی = windowpos->cy;

            return_کوډ = 0;
        }
        اكسر;

    حالة WM_WINDOWPOSCHANGED:
    {
        SDL_کړکۍ *win;
        ثابت SDL_DisplayID original_displayID = معلومات->کړکۍ->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحيح x, y;
        صحيح w, h;

        إذا (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        إذا (iconic) {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
        } وإلا إذا (zoomed) {
            إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
            }
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MAXIMIZED, 0, 0);
            معلومات->force_ws_maximizebox = true;
        } وإلا إذا (معلومات->کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED)) {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
                معلومات->force_ws_maximizebox = false;
                WIN_سېټ_کړکۍ_Resizable(SDL_GetVideoDevice(), معلومات->کړکۍ, !!(معلومات->کړکۍ->flags & SDL_کړکۍ_RESIZABLE));
            }
        }

        إذا (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        إذا (iconic) {
            اكسر;
        }

        إذا (معلومات->initializing) {
            اكسر;
        }

        إذا (!معلومات->disable_move_اندازه_events) {
            إذا (GetClientRect(hwnd, &rect) && WIN_کړکۍ_Rect_Valid(&rect)) {
                Client_منزل_Screen(hwnd, (LPPOINT) &rect);
                Client_منزل_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.کیڼ;
                y = rect.سر;

                SDL_Global_منزل_Relative_For_کړکۍ(معلومات->کړکۍ, x, y, &x, &y);
                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            إذا (GetClientRect(hwnd, &rect) && WIN_کړکۍ_Rect_Valid(&rect)) {
                w = rect.ښی;
                h = rect.bottom;

                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(معلومات->کړکۍ);

        // Update the window display position
        إذا (معلومات->کړکۍ->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_کړکۍ_ICCProfile(معلومات->کړکۍ, true);
        }

        // Update the position of any child windows
        لكل (win = معلومات->کړکۍ->لومړی_ماشوم; win; win = win->بل_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_کړکۍ_IS_POPUP(win) && !(win->flags & SDL_کړکۍ_HIDDEN)) {
                WIN_سېټ_کړکۍ_Position_دننی(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        إذا (g_Windows_پیغام_Hook) {
            إذا (!Dispatch_Modal_Loop_پیغام_Hook(&hwnd, &پیغام_2, &wParam, &lParam)) {
                أرجع 0;
            }
        }

        ++معلومات->دننه_modal_loop;
        إذا (معلومات->دننه_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_کړکۍ_Rect(معلومات->hwnd, &rect);
            معلومات->وروستی_modal_پلنوالی = rect.ښی - rect.کیڼ;
            معلومات->وروستی_modal_لوړوالی = rect.bottom - rect.سر;

            معلومات->initial_اندازه_rect.کیڼ = معلومات->کړکۍ->x;
            معلومات->initial_اندازه_rect.ښی = معلومات->کړکۍ->x + معلومات->کړکۍ->w;
            معلومات->initial_اندازه_rect.سر = معلومات->کړکۍ->y;
            معلومات->initial_اندازه_rect.bottom = معلومات->کړکۍ->y + معلومات->کړکۍ->h;

            سېټ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        إذا (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_کړکۍ_ژوندی_Resize_Update(معلومات->کړکۍ);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#إذا 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            إذا (معلومات->videodata->DwmFlush) {
                معلومات->videodata->DwmFlush();
            }
#د_که_پای
#د_که_پای
            أرجع 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --معلومات->دننه_modal_loop;
        إذا (معلومات->دننه_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } اكسر;

    حالة WM_SIZING:
        {
            WPARAM څنډه = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool قلف_aspect_نسبت = (معلومات->کړکۍ->max_aspect == معلومات->کړکۍ->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            عائم new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            إذا (معلومات->کړکۍ->min_aspect <= 0 && معلومات->کړکۍ->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            سېټ_Rect_تشه(&rc);
            إذا (!Adjust_کړکۍ_Rect_Ex(&rc, Get_کړکۍ_Style(hwnd), GetMenu(hwnd) != عدم, Get_کړکۍ_Ex_Style(hwnd))) {
                اكسر;
            }

            clientDragRect.کیڼ -= rc.کیڼ;
            clientDragRect.سر -= rc.سر;
            clientDragRect.ښی -= rc.ښی;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ښی - clientDragRect.کیڼ;
            h = clientDragRect.bottom - clientDragRect.سر;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            إذا (قلف_aspect_نسبت) {
                بدل (څنډه) {
                حالة WMSZ_کیڼ:
                حالة WMSZ_ښی:
                    h = (صحيح)SDL_roundf(w / معلومات->کړکۍ->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * معلومات->کړکۍ->max_aspect);
                    اكسر;
                }
            } وإلا {
                بدل (څنډه) {
                حالة WMSZ_کیڼ:
                حالة WMSZ_ښی:
                    إذا (معلومات->کړکۍ->max_aspect > 0.0f && new_aspect > معلومات->کړکۍ->max_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->کړکۍ->max_aspect);
                    } وإلا إذا (معلومات->کړکۍ->min_aspect > 0.0f && new_aspect < معلومات->کړکۍ->min_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->کړکۍ->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_سر:
                حالة WMSZ_BOTTOM:
                    إذا (معلومات->کړکۍ->min_aspect > 0.0f && new_aspect < معلومات->کړکۍ->min_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->کړکۍ->min_aspect);
                    } وإلا إذا (معلومات->کړکۍ->max_aspect > 0.0f && new_aspect > معلومات->کړکۍ->max_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->کړکۍ->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    إذا (معلومات->کړکۍ->max_aspect > 0.0f && new_aspect > معلومات->کړکۍ->max_aspect) {
                        w = (صحيح)SDL_roundf(h * معلومات->کړکۍ->max_aspect);
                    } وإلا إذا (معلومات->کړکۍ->min_aspect > 0.0f && new_aspect < معلومات->کړکۍ->min_aspect) {
                        h = (صحيح)SDL_roundf(w / معلومات->کړکۍ->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (څنډه) {
            حالة WMSZ_کیڼ:
                clientDragRect.کیڼ = clientDragRect.ښی - w;
                إذا (قلف_aspect_نسبت) {
                    clientDragRect.سر = (معلومات->initial_اندازه_rect.bottom + معلومات->initial_اندازه_rect.سر - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.سر;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.کیڼ = clientDragRect.ښی - w;
                clientDragRect.bottom = h + clientDragRect.سر;
                اكسر;
            حالة WMSZ_ښی:
                clientDragRect.ښی = w + clientDragRect.کیڼ;
                إذا (قلف_aspect_نسبت) {
                    clientDragRect.سر = (معلومات->initial_اندازه_rect.bottom + معلومات->initial_اندازه_rect.سر - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.سر;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.ښی = w + clientDragRect.کیڼ;
                clientDragRect.سر = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_سر:
                إذا (قلف_aspect_نسبت) {
                    clientDragRect.کیڼ = (معلومات->initial_اندازه_rect.ښی + معلومات->initial_اندازه_rect.کیڼ - w) / 2;
                }
                clientDragRect.ښی = w + clientDragRect.کیڼ;
                clientDragRect.سر = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.کیڼ = clientDragRect.ښی - w;
                clientDragRect.سر = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                إذا (قلف_aspect_نسبت) {
                    clientDragRect.کیڼ = (معلومات->initial_اندازه_rect.ښی + معلومات->initial_اندازه_rect.کیڼ - w) / 2;
                }
                clientDragRect.ښی = w + clientDragRect.کیڼ;
                clientDragRect.bottom = h + clientDragRect.سر;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.ښی = w + clientDragRect.کیڼ;
                clientDragRect.bottom = h + clientDragRect.سر;
                اكسر;
            }

            // convert the client rect to a window rect
            إذا (!Adjust_کړکۍ_Rect_Ex(&clientDragRect, Get_کړکۍ_Style(hwnd), GetMenu(hwnd) != عدم, Get_کړکۍ_Ex_Style(hwnd))) {
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
            سېټ_Cursor(SDL_cursor);
            return_کوډ = TRUE;
        } وإلا إذا (!g_کړکۍ_چوکاټ_Usable_While_Cursor_Hidden && !SDL_cursor) {
            سېټ_Cursor(عدم);
            return_کوډ = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        إذا (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            إذا (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                پای_ټکی_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, عدم);
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
        }
    }
        return_کوډ = 0;
        اكسر;

        // We'll do our own drawing, prevent flicker
    حالة WM_ERASEBKGND:
        إذا (Should_Clear_کړکۍ_On_Erase_Background(معلومات)) {
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
#د_که_پای // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
    }
        return_کوډ = 0;
        اكسر;

    حالة WM_TOUCH:
        إذا (معلومات->videodata->Get_Touch_ننوت_Info && معلومات->videodata->Close_Touch_ننوت_Handle) {
            UINT i, عدد_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, عدد_inputs, &isstack);
            إذا (inputs && معلومات->videodata->Get_Touch_ننوت_Info((HTOUCHINPUT)lParam, عدد_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                إذا (!GetClientRect(hwnd, &rect) || !WIN_کړکۍ_Rect_Valid(&rect)) {
                    إذا (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                Client_منزل_Screen(hwnd, (LPPOINT)&rect);
                Client_منزل_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.سر *= 100;
                rect.کیڼ *= 100;
                rect.bottom *= 100;
                rect.ښی *= 100;

                لكل (i = 0; i < عدد_inputs; ++i) {
                    PTOUCHINPUT ننوت = &inputs[i];
                    ثابت صحيح w = (rect.ښی - rect.کیڼ);
                    ثابت صحيح h = (rect.bottom - rect.سر);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)ننوت->h_سرچینه);
                    ثابت SDL_FingerID fingerId = (ننوت->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    إذا (SDL_جمع_کړه_Touch(touchId, SDL_TOUCH_DEVICE_مستقیم, (ننوت->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    إذا (w <= 1) {
                        x = 0.5f;
                    } وإلا {
                        x = (عائم)(ننوت->x - rect.کیڼ) / (w - 1);
                    }
                    إذا (h <= 1) {
                        y = 0.5f;
                    } وإلا {
                        y = (عائم)(ننوت->y - rect.سر) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    إذا (ننوت->dwFlags & TOUCHEVENTF_ښکته) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->کړکۍ, SDL_EVENT_FINGER_ښکته, x, y, 1.0f);
                    }
                    إذا (ننوت->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->کړکۍ, x, y, 1.0f);
                    }
                    إذا (ننوت->dwFlags & TOUCHEVENTF_پورته) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, معلومات->کړکۍ, SDL_EVENT_FINGER_پورته, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            معلومات->videodata->Close_Touch_ننوت_Handle((HTOUCHINPUT)lParam);
            أرجع 0;
        }
        اكسر;

#که_تعریف_شوی HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        أرجع TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#د_که_پای // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT شمېر = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < شمېر; ++i) {
            UINT اندازه = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR بفر_2 = (LPTSTR)SDL_malloc(حجم(TCHAR) * اندازه);
            إذا (بفر_2) {
                إذا (DragQueryFile(drop, i, بفر_2, اندازه)) {
                    حرف *file = WIN_String_منزل_UTF8(بفر_2);
                    SDL_SendDropFile(معلومات->کړکۍ, عدم, file);
                    SDL_free(file);
                }
                SDL_free(بفر_2);
            }
        }
        SDL_SendDropComplete(معلومات->کړکۍ);
        Drag_پای(drop);
        أرجع 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_کړکۍ_Flags کړکۍ_flags = معلومات->کړکۍ->flags;
        إذا (wParam == TRUE && (کړکۍ_flags & SDL_کړکۍ_BORDERLESS) && !(کړکۍ_flags & SDL_کړکۍ_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            إذا (Get_کړکۍ_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_کړکۍ(hwnd, MONITOR_DEFAULTTONULL);
                إذا (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت ټکی_2 pt = { معلومات->کړکۍ->windowed.x, معلومات->کړکۍ->windowed.y };
                    hMonitor = Monitor_From_ټکی(pt, MONITOR_DEFAULTTONEAREST);
                }
                إذا (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_اندازه = حجم(info);
                    إذا (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وإلا إذا (!(کړکۍ_flags & SDL_کړکۍ_RESIZABLE) && !معلومات->force_ws_maximizebox) {
                صحيح w, h;
                إذا (معلومات->کړکۍ->وروستی_اندازه_pending) {
                    w = معلومات->کړکۍ->pending.w;
                    h = معلومات->کړکۍ->pending.h;
                } وإلا {
                    w = معلومات->کړکۍ->floating.w;
                    h = معلومات->کړکۍ->floating.h;
                }
                params->rgrc[0].ښی = params->rgrc[0].کیڼ + w;
                params->rgrc[0].bottom = params->rgrc[0].سر + h;
            }
            أرجع 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

        إذا (کړکۍ->flags & SDL_کړکۍ_TOOLTIP) {
            أرجع HTTRANSPARENT;
        }

        إذا (کړکۍ->موندنه_test) {
            ټکی_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            إذا (Screen_منزل_Client(hwnd, &winpoint)) {
                SDL_ټکی ټکی;
                SDL_موندنه_Test_پایله rc;
                ټکی.x = winpoint.x;
                ټکی.y = winpoint.y;
                rc = کړکۍ->موندنه_test(کړکۍ, &ټکی, کړکۍ->موندنه_test_معلومات);
                بدل (rc) {
#تعریف_کړه POST_موندنه_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_موندنه_TEST, 0, 0); \
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
                        SDL_سېټ_Mouse_Focus(کړکۍ);
                        أرجع HTCLIENT;
                    }

                    POST_موندنه_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_موندنه_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_سر:
                    POST_موندنه_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_موندنه_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_ښی:
                    POST_موندنه_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_موندنه_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_موندنه_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_موندنه_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_کیڼ:
                    POST_موندنه_TEST(HTLEFT);
#تعریف_لغوه POST_موندنه_TEST
                حالة SDL_HITTEST_نورمال:
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
        إذا (معلومات->videodata->Get_Dpi_For_کړکۍ && معلومات->videodata->Adjust_کړکۍ_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحيح بل_DPI = (صحيح)wParam;
            ثابت صحيح prevDPI = (صحيح)معلومات->videodata->Get_Dpi_For_کړکۍ(hwnd);
            اندازه_3 *اندازه_دننه_بهر = (اندازه_3 *)lParam;

            صحيح چوکاټ_w, چوکاټ_h;
            صحيح query_client_w_win, query_client_h_win;

#که_تعریف_شوی HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, بل_DPI, اندازه_دننه_بهر->cx, اندازه_دننه_بهر->cy);
#د_که_پای

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS) && !SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ)) {
                    WIN_Adjust_کړکۍ_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                چوکاټ_w = -rect.کیڼ + rect.ښی;
                چوکاټ_h = -rect.سر + rect.bottom;

                query_client_w_win = اندازه_دننه_بهر->cx - چوکاټ_w;
                query_client_h_win = اندازه_دننه_بهر->cy - چوکاټ_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ښی = query_client_w_win;
                rect.bottom = query_client_h_win;

                إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS) && !SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ)) {
                    WIN_Adjust_کړکۍ_Rect_For_HWND(hwnd, &rect, بل_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                اندازه_دننه_بهر->cx = rect.ښی - rect.کیڼ;
                اندازه_دننه_بهر->cy = rect.bottom - rect.سر;
            }

#که_تعریف_شوی HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", اندازه_دننه_بهر->cx, اندازه_دننه_بهر->cy);
#د_که_پای
            أرجع TRUE;
        }
        اكسر;

    حالة WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحيح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحيح w, h;

#که_تعریف_شوی HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->کیڼ, suggestedRect->سر, suggestedRect->ښی - suggestedRect->کیڼ, suggestedRect->bottom - suggestedRect->سر);
#د_که_پای

            إذا (معلومات->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#که_تعریف_شوی HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#د_که_پای
                أرجع 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ښی = معلومات->کړکۍ->w;
                rect.bottom = معلومات->کړکۍ->h;

                إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS)) {
                    WIN_Adjust_کړکۍ_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.ښی - rect.کیڼ;
                h = rect.bottom - rect.سر;
            }

#که_تعریف_شوی HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    معلومات->کړکۍ->w, معلومات->کړکۍ->h,
                    suggestedRect->کیڼ, suggestedRect->سر, w, h);
#د_که_پای

            معلومات->expected_resize = true;
            سېټ_کړکۍ_Pos(hwnd,
                         عدم,
                         suggestedRect->کیڼ,
                         suggestedRect->سر,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            معلومات->expected_resize = false;
            أرجع 0;
        }

    حالة WM_SETTINGCHANGE:
        إذا (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_سېټ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_ډېرپېښ_For_HWND(hwnd);
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
    حالة WM_اندازه:
    {
        RECT rect;
        صحيح w, h;

        إذا (GetClientRect(hwnd, &rect) && WIN_کړکۍ_Rect_Valid(&rect)) {
            w = rect.ښی;
            h = rect.bottom;
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESIZED, w, h);
        }
    } اكسر;
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (پیغام_2 && پیغام_2 == معلومات->videodata->WM_TASKBAR_BUTTON_CREATED) {
        معلومات->taskbar_button_created = true;
        WIN_Apply_کړکۍ_پرمختګ(SDL_GetVideoDevice(), معلومات->کړکۍ);
    }
#د_که_پای

    // If there's a window proc, assume it's going to handle messages
    إذا (معلومات->wndproc) {
        أرجع Call_کړکۍ_Proc(معلومات->wndproc, hwnd, پیغام_2, wParam, lParam);
    } وإلا إذا (return_کوډ >= 0) {
        أرجع return_کوډ;
    } وإلا {
        أرجع Call_کړکۍ_Proc(Def_کړکۍ_Proc, hwnd, پیغام_2, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    إذا (g_Windows_Enable_پیغام_Loop) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_منزل_MS(timeoutNS);
        ret = پیغام_Wait_For_مضرب_Objects(0, عدم, FALSE, timeout, QS_ALLINPUT);
        إذا (ret == WAIT_OBJECT_0) {
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#وإلا
        // MsgWaitForMultipleObjects is desktop-only.
        پیغام_3 پیغام_2;
        BOOL پیغام_پایله;
        UINT_PTR timer_id = 0;
        إذا (timeoutNS > 0) {
            timer_id = سېټ_Timer(عدم, 0, (UINT)SDL_NS_منزل_MS(timeoutNS), عدم);
            پیغام_پایله = Get_پیغام(&پیغام_2, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } وإلا إذا (timeoutNS == 0) {
            پیغام_پایله = Peek_پیغام(&پیغام_2, عدم, 0, 0, PM_REMOVE);
        } وإلا {
            پیغام_پایله = Get_پیغام(&پیغام_2, 0, 0, 0);
        }
        إذا (پیغام_پایله) {
            إذا (پیغام_2.پیغام == WM_TIMER && !پیغام_2.hwnd && پیغام_2.wParam == timer_id) {
                أرجع 0;
            }
            إذا (g_Windows_پیغام_Hook) {
                إذا (!g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_معلومات, &پیغام_2)) {
                    أرجع 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وإلا {
        // Fail the wait so the caller falls back to polling
        أرجع -1;
    }
}

فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Post_پیغام(معلومات->hwnd, معلومات->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    پیغام_3 پیغام_2;

    إذا (g_Windows_Enable_پیغام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پیغام(&پیغام_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_سېټ_پیغام_Tick(پیغام_2.وخت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    پیغام_3 پیغام_2;
#که_تعریف_شوی _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#لارښوونه warning(ټېل)
#لارښوونه warning(disable : 28159)
#د_که_پای
    DWORD پای_ټکی_ticks = Get_Tick_شمېر() + 1;
#که_تعریف_شوی _MSC_VER
#لارښوونه warning(راوباسه)
#د_که_پای
    صحيح new_messages = 0;

    إذا (_this->دننی->gameinput_context) {
        WIN_Update_Game_ننوت(_this);
    }

    إذا (g_Windows_Enable_پیغام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پیغام(&پیغام_2, عدم, 0, 0, PM_REMOVE)) {
            إذا (g_Windows_پیغام_Hook) {
                إذا (!g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_معلومات, &پیغام_2)) {
                    استمر;
                }
            }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            إذا (پیغام_2.پیغام == WM_MOUSEMOVE && SDL_وروستی_warp_وخت) {
                إذا (!SDL_TICKS_PASSED(پیغام_2.وخت, (SDL_وروستی_warp_وخت + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_وروستی_warp_وخت = 0;
            }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_سېټ_پیغام_Tick(پیغام_2.وخت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            إذا (SDL_TICKS_PASSED(پیغام_2.وخت, پای_ټکی_ticks)) {
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
    إذا (keystate[SDL_SCANCODE_LSHIFT] && !(Get_کلی_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    إذا (keystate[SDL_SCANCODE_RSHIFT] && !(Get_کلی_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_کړکۍ *focus_کړکۍ = SDL_GetKeyboardFocus();
    إذا (!focus_کړکۍ || !(focus_کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED)) {
        إذا (keystate[SDL_SCANCODE_LGUI] && !(Get_کلی_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        إذا (keystate[SDL_SCANCODE_RGUI] && !(Get_کلی_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    إذا (_this) {
        SDL_کړکۍ *کړکۍ = _this->windows;
        طالما (کړکۍ) {
            bool refresh_clipcursor = false;
            SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
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
                WIN_UpdateClipCursor(کړکۍ);
            }
            کړکۍ = کړکۍ->بل;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_کړکۍ = SDL_GetKeyboardFocus();
    إذا (focus_کړکۍ && (focus_کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
        SDL_کړکۍ_معلومات *معلومات = focus_کړکۍ->دننی;

        إذا (!معلومات->mouse_tracked) {
            ټکی_2 cursorPos;

            إذا (GetCursorPos(&cursorPos) && Screen_منزل_Client(معلومات->hwnd, &cursorPos)) {
                bool بدلون_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID,
                                    !بدلون_Buttons ? SDL_BUTTON_کیڼ : SDL_BUTTON_ښی,
                                    (Get_Async_کلی_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID,
                                    !بدلون_Buttons ? SDL_BUTTON_ښی : SDL_BUTTON_کیڼ,
                                    (Get_Async_کلی_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID,
                                    SDL_BUTTON_منځ,
                                    (Get_Async_کلی_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_کلی_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), معلومات->کړکۍ, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_کلی_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#که_تعریف_شوی SDL_PLATFORM_GDK
    GDK_Dispatch_Task_کتار();
#د_که_پای
}

ساكن صحيح app_registered = 0;
LPTSTR SDL_Appname = عدم;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = عدم;

ساكن فراغ WIN_Clean_ثبتوونکی_App(WNDCLASSEX wcex)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    إذا (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#د_که_پای
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
    wcex->hIcon = بارول_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    أرجع FALSE;
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_ثبتوونکی_App(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#د_که_پای

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
#د_که_پای
    }
    SDL_Appname = WIN_UTF8_منزل_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(عدم);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_اندازه = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_کړکۍ_Proc;
    wcex.hInstance = SDL_Instance;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    إذا (hint && *hint) {
        wcex.hIcon = بارول_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        إذا (hint && *hint) {
            wcex.hIconSm = بارول_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وإلا {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_نومونه(SDL_Instance, RT_ډله_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    إذا (!ثبتوونکی_Class_Ex(&wcex)) {
        WIN_Clean_ثبتوونکی_App(wcex);
        أرجع SDL_سېټ_Error("Couldn't register application class");
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
#د_که_پای
        WIN_Clean_ثبتوونکی_App(wcex);
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS
