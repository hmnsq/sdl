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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

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
#جے_تعریف_شدہ HAVE_TPCSHRD_H
#ضمن <tpcshrd.h>
#جے_انت // HAVE_TPCSHRD_H

#إذا 0
#تعریف_کرو WMMSG_DEBUG
#جے_انت
#جے_تعریف_شدہ WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#جے_انت

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
#جے_انت

#جے_تعریف_شدہ SDL_PLATFORM_GDK
#ضمن "../../core/gdk/SDL_gdk.h"
#جے_انت

// #define HIGHDPI_DEBUG

// Undocumented window messages
#جے_بنا_تعریف WM_NCUAHDRAWCAPTION
#تعریف_کرو WM_NCUAHDRAWCAPTION 0xAE
#جے_انت
#جے_بنا_تعریف WM_NCUAHDRAWFRAME
#تعریف_کرو WM_NCUAHDRAWFRAME 0xAF
#جے_انت

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#جے_بنا_تعریف WM_XBUTTONDOWN
#تعریف_کرو WM_XBUTTONDOWN 0x020B
#جے_انت
#جے_بنا_تعریف WM_XBUTTONUP
#تعریف_کرو WM_XBUTTONUP 0x020C
#جے_انت
#جے_بنا_تعریف GET_XBUTTON_WPARAM
#تعریف_کرو GET_XBUTTON_WPARAM(w) (HIWORD(w))
#جے_انت
#جے_بنا_تعریف WM_داخلہ
#تعریف_کرو WM_داخلہ 0x00ff
#جے_انت
#جے_بنا_تعریف WM_TOUCH
#تعریف_کرو WM_TOUCH 0x0240
#جے_انت
#جے_بنا_تعریف WM_MOUSEHWHEEL
#تعریف_کرو WM_MOUSEHWHEEL 0x020E
#جے_انت
#جے_بنا_تعریف RI_MOUSE_HWHEEL
#تعریف_کرو RI_MOUSE_HWHEEL 0x0800
#جے_انت
#جے_بنا_تعریف WM_POINTERUPDATE
#تعریف_کرو WM_POINTERUPDATE 0x0245
#جے_انت
#جے_بنا_تعریف WM_POINTERDOWN
#تعریف_کرو WM_POINTERDOWN 0x0246
#جے_انت
#جے_بنا_تعریف WM_POINTERUP
#تعریف_کرو WM_POINTERUP 0x0247
#جے_انت
#جے_بنا_تعریف WM_POINTERENTER
#تعریف_کرو WM_POINTERENTER 0x0249
#جے_انت
#جے_بنا_تعریف WM_POINTERLEAVE
#تعریف_کرو WM_POINTERLEAVE 0x024A
#جے_انت
#جے_بنا_تعریف WM_POINTERCAPTURECHANGED
#تعریف_کرو WM_POINTERCAPTURECHANGED 0x024C
#جے_انت
#جے_بنا_تعریف WM_UNICHAR
#تعریف_کرو WM_UNICHAR 0x0109
#جے_انت
#جے_بنا_تعریف WM_DPICHANGED
#تعریف_کرو WM_DPICHANGED 0x02E0
#جے_انت
#جے_بنا_تعریف WM_GETDPISCALEDSIZE
#تعریف_کرو WM_GETDPISCALEDSIZE 0x02E4
#جے_انت
#جے_بنا_تعریف TOUCHEVENTF_PEN
#تعریف_کرو TOUCHEVENTF_PEN 0x0040
#جے_انت

#جے_بنا_تعریف MAPVK_VK_منزل_VSC_EX
#تعریف_کرو MAPVK_VK_منزل_VSC_EX 4
#جے_انت

#جے_بنا_تعریف WC_ERR_INVALID_CHARS
#تعریف_کرو WC_ERR_INVALID_CHARS 0x00000080
#جے_انت

#جے_بنا_تعریف IS_بلند_SURROGATE
#تعریف_کرو IS_بلند_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#جے_انت

#جے_بنا_تعریف USER_TIMER_MINIMUM
#تعریف_کرو USER_TIMER_MINIMUM 0x0000000A
#جے_انت

// Used to compare Windows message timestamps
#تعریف_کرو SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#جے_تعریف_شدہ _WIN64
تعريفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#جے_انت

ساكن bool SDL_processing_messages;
ساكن DWORD سنیہا_tick;
ساكن Uint64 timestamp_وتھ;

ساكن فراغ WIN_سیٹ_سنیہا_Tick(DWORD tick)
{
    سنیہا_tick = tick;
}

ساكن Uint64 WIN_GetEventTimestamp(فراغ)
{
    ثابت Uint64 TIMESTAMP_WRAP_وتھ = SDL_MS_منزل_NS(0x100000000LL);
    Uint64 timestamp, now;

    إذا (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        أرجع 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_منزل_NS(سنیہا_tick);
    timestamp += timestamp_وتھ;
    إذا (!timestamp_وتھ) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_وتھ = (now - timestamp);
        timestamp = now;
    } وإلا إذا ((Sint64)(now - timestamp - TIMESTAMP_WRAP_وتھ) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_وتھ += TIMESTAMP_WRAP_وتھ;
        timestamp += TIMESTAMP_WRAP_وتھ;
    } وإلا إذا (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_وتھ -= (timestamp - now);
        timestamp = now;
    }
    أرجع timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_Windows_سنیہا_Hook g_Windows_سنیہا_Hook = عدم;
ساكن فراغ *g_Windows_سنیہا_Hook_انکڑے = عدم;

فراغ SDL_سیٹ_Windows_سنیہا_Hook(SDL_Windows_سنیہا_Hook callback, فراغ *userdata)
{
    g_Windows_سنیہا_Hook = callback;
    g_Windows_سنیہا_Hook_انکڑے = userdata;
}

ساكن SDL_Scancode Windows_جانچ_کوڈ_منزل_SDLScan_کوڈ(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_کلید)
{
    SDL_Scancode کوڈ;
    Uint8 اشاریہ;
    Uint16 کلید_Flags = HIWORD(lParam);
    Uint16 جانچ_کوڈ = LOBYTE(کلید_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    جانچ_کوڈ &= ~0x80;

    *virtual_کلید = (جانچ_کوڈ == 0);

    إذا (جانچ_کوڈ != 0) {
        إذا ((کلید_Flags & KF_EXTENDED) == KF_EXTENDED) {
            جانچ_کوڈ = MAKEWORD(جانچ_کوڈ, 0xe0);
        } وإلا إذا (جانچ_کوڈ == 0x45) {
            // Pause
            جانچ_کوڈ = 0xe046;
        }
    } وإلا {
        Uint16 vk_کوڈ = LOWORD(wParam);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        جانچ_کوڈ = LOWORD(Map_Virtual_کلید(vk_کوڈ, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        إذا (جانچ_کوڈ == 0xe11d) {
            جانچ_کوڈ = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    اشاریہ = LOBYTE(جانچ_کوڈ) | (HIBYTE(جانچ_کوڈ) ? 0x80 : 0x00);
    کوڈ = windows_scancode_جدول[اشاریہ];
    *rawcode = جانچ_کوڈ;

    أرجع کوڈ;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_کھڑکی_انکڑے *انکڑے)
{
    أرجع !SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_وٹاندرا_Buttons, SDL_کھڑکی_انکڑے *انکڑے, Uint8 button, SDL_MouseID mouseID)
{
    إذا (b_وٹاندرا_Buttons) {
        إذا (button == SDL_BUTTON_بایاں) {
            button = SDL_BUTTON_دایاں;
        } وإلا إذا (button == SDL_BUTTON_دایاں) {
            button = SDL_BUTTON_بایاں;
        }
    }

    إذا (انکڑے->focus_click_pending & SDL_BUTTON_نقاب(button)) {
        // Ignore the button click for activation
        إذا (!bwParamMousePressed) {
            انکڑے->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
            WIN_UpdateClipCursor(انکڑے->کھڑکی);
        }
        أرجع;
    }

    إذا (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, انکڑے->کھڑکی, mouseID, button, true);
    } وإلا إذا (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, انکڑے->کھڑکی, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_کھڑکی_انکڑے *انکڑے, SDL_MouseID mouseID)
{
    إذا (wParam != انکڑے->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, انکڑے, SDL_BUTTON_بایاں, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, انکڑے, SDL_BUTTON_درمیان, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, انکڑے, SDL_BUTTON_دایاں, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, انکڑے, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, انکڑے, SDL_BUTTON_X2, mouseID);

        انکڑے->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_کھڑکی_انکڑے *انکڑے)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT کلید_State;
    bool وٹاندرا_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    وٹاندرا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    کلید_State = Get_Async_کلید_State(VK_LBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, وٹاندرا_Buttons, انکڑے, SDL_BUTTON_بایاں, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_RBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, وٹاندرا_Buttons, انکڑے, SDL_BUTTON_دایاں, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_MBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, وٹاندرا_Buttons, انکڑے, SDL_BUTTON_درمیان, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON1);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, وٹاندرا_Buttons, انکڑے, SDL_BUTTON_X1, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON2);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, وٹاندرا_Buttons, انکڑے, SDL_BUTTON_X2, mouseID);
    }
    انکڑے->mouse_button_flags = (WPARAM)-1;
}

ساكن فراغ WIN_UpdateFocus(SDL_کھڑکی *کھڑکی, bool expect_focus, LPPOINT pos)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == کھڑکی);
    bool has_focus = (Get_Foreground_کھڑکی() == hwnd);

    إذا (had_focus == has_focus || has_focus != expect_focus) {
        أرجع;
    }

    إذا (has_focus) {
        نقطہ_2 cursorPos;

        إذا (WIN_ShouldIgnoreFocusClick(انکڑے) && !(کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            bool وٹاندرا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            إذا (Get_Async_کلید_State(VK_LBUTTON)) {
                انکڑے->focus_click_pending |= !وٹاندرا_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            إذا (Get_Async_کلید_State(VK_RBUTTON)) {
                انکڑے->focus_click_pending |= !وٹاندرا_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            إذا (Get_Async_کلید_State(VK_MBUTTON)) {
                انکڑے->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            إذا (Get_Async_کلید_State(VK_XBUTTON1)) {
                انکڑے->focus_click_pending |= SDL_BUTTON_X1_نقاب;
            }
            إذا (Get_Async_کلید_State(VK_XBUTTON2)) {
                انکڑے->focus_click_pending |= SDL_BUTTON_X2_نقاب;
            }
        }

        SDL_سیٹ_Keyboard_Focus(کھڑکی->keyboard_focus ? کھڑکی->keyboard_focus : کھڑکی);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        إذا (!SDL_GetMouse()->relative_منوال) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_منزل_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), انکڑے);
        WIN_UpdateClipCursor(کھڑکی);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(انکڑے->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلید_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_عدد, (Get_کلید_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلید_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_کھڑکی_ICCProfile(انکڑے->کھڑکی, true);
    } وإلا {
        انکڑے->وچ_کھڑکی_deactivation = true;

        SDL_سیٹ_Keyboard_Focus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        إذا (SDL_GetMouse()->relative_منوال) {
            SDL_سیٹ_Mouse_Focus(عدم);
        }
        WIN_Reset_Dead_کلیدیں();

        WIN_Unclip_Cursor_For_کھڑکی(کھڑکی);

        انکڑے->وچ_کھڑکی_deactivation = false;
    }
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool Should_Generate_کھڑکی_Close_On_Alt_F4(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool Should_Clear_کھڑکی_On_Erase_Background(SDL_کھڑکی_انکڑے *انکڑے)
{
    بدل (انکڑے->hint_erase_background_منوال) {
    حالة SDL_ERASEBACKGROUNDMODE_NEVER:
        أرجع false;
    حالة SDL_ERASEBACKGROUNDMODE_INITIAL:
        أرجع !انکڑے->videodata->cleared;
    حالة SDL_ERASEBACKGROUNDMODE_ALWAYS:
        أرجع true;
    افتراضي:
        // Unexpected value, fallback to default behaviour
        أرجع !انکڑے->videodata->cleared;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#تعریف_کرو MI_WP_SIGNATURE      0xFF515700
#تعریف_کرو MI_WP_SIGNATURE_نقاب 0xFFFFFF00
#تعریف_کرو IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_نقاب) == MI_WP_SIGNATURE

تعريفنوع تعداد
{
    SDL_MOUSE_EVENT_سروت_UNKNOWN,
    SDL_MOUSE_EVENT_سروت_MOUSE,
    SDL_MOUSE_EVENT_سروت_TOUCH,
    SDL_MOUSE_EVENT_سروت_PEN,
} SDL_MOUSE_EVENT_سروت;

ساكن SDL_MOUSE_EVENT_سروت Get_Mouse_سنیہا_سروت(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    إذا (IsTouchEvent(extrainfo)) {
        إذا (extrainfo & 0x80) {
            أرجع SDL_MOUSE_EVENT_سروت_TOUCH;
        } وإلا {
            أرجع SDL_MOUSE_EVENT_سروت_PEN;
        }
    }
    أرجع SDL_MOUSE_EVENT_سروت_MOUSE;
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_کھڑکی_انکڑے *WIN_Get_کھڑکی_انکڑے_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_کھڑکی *کھڑکی;

    إذا (_this) {
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
            إذا (انکڑے && انکڑے->hwnd == hwnd) {
                أرجع انکڑے;
            }
        }
    }
    أرجع عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح n_کوڈ, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_انکڑے = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_انکڑے *انکڑے = SDL_GetVideoDevice()->اندرونی;
    SDL_Scancode جانچ_کوڈ;

    إذا (n_کوڈ < 0 || n_کوڈ != HC_ACTION) {
        أرجع Call_اگلا_Hook_Ex(عدم, n_کوڈ, wParam, lParam);
    }
    إذا (hook_انکڑے->جانچ_کوڈ == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        أرجع 1;
    }

    بدل (hook_انکڑے->vk_کوڈ) {
    حالة VK_LWIN:
        جانچ_کوڈ = SDL_SCANCODE_LGUI;
        اكسر;
    حالة VK_RWIN:
        جانچ_کوڈ = SDL_SCANCODE_RGUI;
        اكسر;
    حالة VK_LMENU:
        جانچ_کوڈ = SDL_SCANCODE_LALT;
        اكسر;
    حالة VK_RMENU:
        جانچ_کوڈ = SDL_SCANCODE_RALT;
        اكسر;
    حالة VK_LCONTROL:
        جانچ_کوڈ = SDL_SCANCODE_LCTRL;
        اكسر;
    حالة VK_RCONTROL:
        جانچ_کوڈ = SDL_SCANCODE_RCTRL;
        اكسر;
    حالة VK_SNAPSHOT:
        جانچ_کوڈ = SDL_SCANCODE_PRINTSCREEN;
        اكسر;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالة VK_TAB:
        جانچ_کوڈ = SDL_SCANCODE_TAB;
        اكسر;
    حالة VK_ESCAPE:
        جانچ_کوڈ = SDL_SCANCODE_ESCAPE;
        اكسر;

    افتراضي:
        أرجع Call_اگلا_Hook_Ex(عدم, n_کوڈ, wParam, lParam);
    }

    إذا (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        إذا (!انکڑے->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_انکڑے->جانچ_کوڈ, جانچ_کوڈ, true);
        }
    } وإلا {
        إذا (!انکڑے->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_انکڑے->جانچ_کوڈ, جانچ_کوڈ, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        إذا (hook_انکڑے->vk_کوڈ <= 0xFF && انکڑے->pre_hook_کلید_state[hook_انکڑے->vk_کوڈ]) {
            انکڑے->pre_hook_کلید_state[hook_انکڑے->vk_کوڈ] = 0;
            أرجع Call_اگلا_Hook_Ex(عدم, n_کوڈ, wParam, lParam);
        }
    }

    أرجع 1;
}

ساكن bool WIN_وٹاندرا_Buttons(HANDLE hDevice)
{
    إذا (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        أرجع false;
    }
    أرجع GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_Handle_Raw_Mouse_داخلہ(Uint64 timestamp, SDL_Video_انکڑے *انکڑے, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool تھلے;
    } raw_buttons[] = {
        { RI_MOUSE_بایاں_BUTTON_تھلے, SDL_BUTTON_بایاں, true },
        { RI_MOUSE_بایاں_BUTTON_اتے, SDL_BUTTON_بایاں, false },
        { RI_MOUSE_دایاں_BUTTON_تھلے, SDL_BUTTON_دایاں, true },
        { RI_MOUSE_دایاں_BUTTON_اتے, SDL_BUTTON_دایاں, false },
        { RI_MOUSE_درمیان_BUTTON_تھلے, SDL_BUTTON_درمیان, true },
        { RI_MOUSE_درمیان_BUTTON_اتے, SDL_BUTTON_درمیان, false },
        { RI_MOUSE_BUTTON_4_تھلے, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_اتے, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_تھلے, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_اتے, SDL_BUTTON_X2, false }
    };

    صحيح dx = (صحيح)rawmouse->l_آخری_X;
    صحيح dy = (صحيح)rawmouse->l_آخری_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    إذا (!انکڑے->raw_mouse_enabled) {
        أرجع;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_کھڑکی *کھڑکی = SDL_GetKeyboardFocus();
    إذا (!کھڑکی) {
        أرجع;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse) {
        أرجع;
    }

    إذا (Get_Mouse_سنیہا_سروت(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_سروت_MOUSE ||
        (SDL_Touch_Devices_دستیاب() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        أرجع;
    }

    SDL_کھڑکی_انکڑے *windowdata = کھڑکی->اندرونی;

    إذا (haveMotion && !windowdata->وچ_modal_loop) {
        إذا (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (عائم)dx, (عائم)dy);
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
            إذا (انکڑے->آخری_raw_mouse_position.x == 0 && انکڑے->آخری_raw_mouse_position.y == 0) {
                انکڑے->آخری_raw_mouse_position.x = x;
                انکڑے->آخری_raw_mouse_position.y = y;
            }
            relX = x - انکڑے->آخری_raw_mouse_position.x;
            relY = y - انکڑے->آخری_raw_mouse_position.y;

            إذا (remote_desktop) {
                إذا (!windowdata->وچ_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    إذا (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.بایاں + ((rect.دایاں - rect.بایاں) / 2) + wobble;
                        صحيح warpY = rect.چوٹی + ((rect.bottom - rect.چوٹی) / 2);

                        WIN_سیٹ_Cursor_Pos(warpX, warpY);

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
                            SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } وإلا إذا (mouse->pen_mouse_events) {
                ثابت صحيح ودھ_توں_ودھ_TABLET_RELATIVE_MOTION = 32;
                إذا (SDL_abs(relX) > ودھ_توں_ودھ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > ودھ_توں_ودھ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وإلا {
                    SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } وإلا {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                إذا (!انکڑے->raw_داخلہ_fake_pen_id) {
                    انکڑے->raw_داخلہ_fake_pen_id = SDL_جوڑو_Pen_Device(timestamp, "raw mouse input", کھڑکی, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, انکڑے->raw_داخلہ_fake_pen_id, کھڑکی, (عائم)(x + screen_x - کھڑکی->x), (عائم)(y + screen_y - کھڑکی->y));
            }

            انکڑے->آخری_raw_mouse_position.x = x;
            انکڑے->آخری_raw_mouse_position.y = y;
        }
    }

    إذا (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            إذا (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool تھلے = raw_buttons[i].تھلے;

                إذا (button == SDL_BUTTON_بایاں) {
                    إذا (WIN_وٹاندرا_Buttons(hDevice)) {
                        button = SDL_BUTTON_دایاں;
                    }
                } وإلا إذا (button == SDL_BUTTON_دایاں) {
                    إذا (WIN_وٹاندرا_Buttons(hDevice)) {
                        button = SDL_BUTTON_بایاں;
                    }
                }

                إذا (windowdata->focus_click_pending & SDL_BUTTON_نقاب(button)) {
                    // Ignore the button click for activation
                    إذا (!تھلے) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
                        WIN_UpdateClipCursor(کھڑکی);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, تھلے);
            }
        }

        إذا (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_انکڑے;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_عام);
        } وإلا إذا (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_انکڑے;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_عام);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_Handle_Raw_Keyboard_داخلہ(Uint64 timestamp, SDL_Video_انکڑے *انکڑے, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    إذا (!انکڑے->raw_keyboard_enabled) {
        أرجع;
    }

    إذا (rawkeyboard->Flags & RI_کلید_E1) {
        // First key in a Ctrl+{key} sequence
        انکڑے->pending_E1_کلید_sequence = true;
        أرجع;
    }

    إذا ((rawkeyboard->Flags & RI_کلید_E0) && rawkeyboard->Make_کوڈ == 0x2A) {
        // 0xE02A make code prefix, ignored
        أرجع;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!rawkeyboard->Make_کوڈ) {
        rawkeyboard->Make_کوڈ = LOWORD(Map_Virtual_کلید(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_منزل_VSC : MAPVK_VK_منزل_VSC_EX));
    }
#جے_انت
    إذا (!rawkeyboard->Make_کوڈ) {
        أرجع;
    }

    bool تھلے;
    بدل (rawkeyboard->سنیہا_2) {
    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
        تھلے = true;
        اكسر;
    حالة WM_KEYUP:
    حالة WM_SYSKEYUP:
        تھلے = false;
        اكسر;
    افتراضي:
        تھلے = !(rawkeyboard->Flags & RI_کلید_BREAK);
        اكسر;
    }

    SDL_Scancode کوڈ;
    USHORT rawcode = rawkeyboard->Make_کوڈ;
    إذا (انکڑے->pending_E1_کلید_sequence) {
        rawcode |= 0xE100;
        إذا (rawkeyboard->Make_کوڈ == 0x45) {
            // Ctrl+NumLock == Pause
            کوڈ = SDL_SCANCODE_PAUSE;
        } وإلا {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            کوڈ = SDL_SCANCODE_UNKNOWN;
        }
        انکڑے->pending_E1_کلید_sequence = false;
    } وإلا {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 اشاریہ = (Uint8)rawkeyboard->Make_کوڈ;
        إذا (rawkeyboard->Flags & RI_کلید_E0) {
            rawcode |= 0xE000;
            اشاریہ |= 0x80;
        }
        کوڈ = windows_scancode_جدول[اشاریہ];
    }

    إذا (تھلے) {
        SDL_کھڑکی *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        إذا ((!انکڑے->raw_keyboard_flag_inputsink && !focus) || (focus && focus->متن_داخلہ_سرگرم)) {
            أرجع;
        }
    }

    SDL_Send_Keyboard_کلید(timestamp, keyboardID, rawcode, کوڈ, تھلے);
}

فراغ WIN_Poll_Raw_داخلہ(SDL_VideoDevice *_this, Uint64 poll_شروع)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    UINT ناپ, i, گنتی, کل = 0;
    RAWINPUT *داخلہ;
    Uint64 poll_انت;

    إذا (انکڑے->rawinput_وتھ == 0) {
        BOOL isWow64;

        انکڑے->rawinput_وتھ = حجم(RAWINPUTHEADER);
        إذا (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            انکڑے->rawinput_وتھ += 8;
        }
    }

    // Get all available events
    داخلہ = (RAWINPUT *)انکڑے->rawinput;
    لكل (;;) {
        ناپ = انکڑے->rawinput_ناپ - (UINT)((BYTE *)داخلہ - انکڑے->rawinput);
        گنتی = Get_Raw_داخلہ_بفر(داخلہ, &ناپ, حجم(RAWINPUTHEADER));
        poll_انت = SDL_GetTicksNS();
        إذا (گنتی == 0 || گنتی == (UINT)-1) {
            إذا (!انکڑے->rawinput || (گنتی == (UINT)-1 && Get_آخری_Error() == ERROR_INSUFFICIENT_بفر)) {
                ثابت UINT RAWINPUT_بفر_ناپ_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(انکڑے->rawinput, انکڑے->rawinput_ناپ + RAWINPUT_بفر_ناپ_INCREMENT);
                إذا (!rawinput) {
                    اكسر;
                }
                داخلہ = (RAWINPUT *)(rawinput + ((BYTE *)داخلہ - انکڑے->rawinput));
                انکڑے->rawinput = rawinput;
                انکڑے->rawinput_ناپ += RAWINPUT_بفر_ناپ_INCREMENT;
            } وإلا {
                اكسر;
            }
        } وإلا {
            کل += گنتی;

            // Advance input to the end of the buffer
            طالما (گنتی--) {
                داخلہ = NEXTRAWINPUTBLOCK(داخلہ);
            }
        }
    }

    إذا (کل > 0) {
        Uint64 delta = poll_انت - poll_شروع;
        UINT mouse_کل = 0;
        لكل (i = 0, داخلہ = (RAWINPUT *)انکڑے->rawinput; i < کل; ++i, داخلہ = NEXTRAWINPUTBLOCK(داخلہ)) {
            إذا (داخلہ->سرخی.dwType == RIM_TYPEMOUSE) {
                mouse_کل += 1;
            }
        }
        صحيح mouse_اشاریہ = 0;
        لكل (i = 0, داخلہ = (RAWINPUT *)انکڑے->rawinput; i < کل; ++i, داخلہ = NEXTRAWINPUTBLOCK(داخلہ)) {
            إذا (داخلہ->سرخی.dwType == RIM_TYPEMOUSE) {
                mouse_اشاریہ += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)داخلہ + انکڑے->rawinput_وتھ);
                Uint64 ویلا = poll_انت - (delta * (mouse_کل - mouse_اشاریہ)) / mouse_کل;
                WIN_Handle_Raw_Mouse_داخلہ(ویلا, انکڑے, داخلہ->سرخی.hDevice, rawmouse);
            } وإلا إذا (داخلہ->سرخی.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)داخلہ + انکڑے->rawinput_وتھ);
                WIN_Handle_Raw_Keyboard_داخلہ(poll_انت, انکڑے, داخلہ->سرخی.hDevice, rawkeyboard);
            }
        }
    }
    انکڑے->آخری_rawinput_poll = poll_انت;
}

ساكن فراغ جوڑو_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *گنتی)
{
    صحيح new_گنتی = (*گنتی + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح گنتی)
{
    لكل (صحيح i = 0; i < گنتی; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن حرف *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت حرف *instance, Uint16 vendor, Uint16 ضرب_حاصل, ثابت حرف *default_name, bool hid_loaded)
{
    حرف *vendor_name = عدم;
    حرف *ضرب_حاصل_name = عدم;
    حرف *name = عدم;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    إذا (hid_loaded) {
        حرف devName[MAX_رستہ + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_داخلہ_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        إذا (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            إذا (hFile != INVALID_HANDLE_قدر) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_Hid_D_Get_ضرب_حاصل_String(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    إذا (vend[0]) {
        vendor_name = WIN_String_منزل_UTF8_W(vend);
    }

    إذا (prod[0]) {
        ضرب_حاصل_name = WIN_String_منزل_UTF8_W(prod);
    } وإلا {
        SP_DEVINFO_انکڑے انکڑے;
        SDL_zero(انکڑے);
        انکڑے.cb_ناپ = حجم(انکڑے);
        لكل (DWORD i = 0;; ++i) {
            إذا (!تیاری_Di_Enum_Device_Info(devinfo, i, &انکڑے)) {
                إذا (Get_آخری_Error() == ERROR_NO_ہور_اشیاء) {
                    اكسر;
                } وإلا {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            إذا (!تیاری_Di_Get_Device_Instance_Id_A(devinfo, &انکڑے, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            إذا (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD ناپ = 0;
                إذا (تیاری_Di_Get_Device_Registry_Property_W(devinfo, &انکڑے, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &ناپ)) {
                    // Make sure the device description is null terminated
                    ناپ /= حجم(*prod);
                    إذا (ناپ >= SDL_arraysize(prod)) {
                        // Truncated description...
                        ناپ = (SDL_arraysize(prod) - 1);
                    }
                    prod[ناپ] = 0;

                    إذا (vendor || ضرب_حاصل) {
                        SDL_asprintf(&ضرب_حاصل_name, "%S (0x%.4x/0x%.4x)", prod, vendor, ضرب_حاصل);
                    } وإلا {
                        ضرب_حاصل_name = WIN_String_منزل_UTF8_W(prod);
                    }
                }
                اكسر;
            }
        }
    }

    إذا (!ضرب_حاصل_name && (vendor || ضرب_حاصل)) {
        SDL_asprintf(&ضرب_حاصل_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, ضرب_حاصل);
    }
    name = SDL_CreateDeviceName(vendor, ضرب_حاصل, vendor_name, ضرب_حاصل_name, default_name);
    SDL_free(vendor_name);
    SDL_free(ضرب_حاصل_name);

    أرجع name;
}

فراغ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = عدم;
    UINT raw_device_گنتی = 0;
    صحيح old_keyboard_گنتی = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_گنتی = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_گنتی = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_گنتی = 0;
    SDL_MouseID *new_mice = عدم;

    إذا (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->اندرونی->detect_device_hotplug ||
        _this->اندرونی->gameinput_context) {
        أرجع;
    }

    إذا ((Get_Raw_داخلہ_Device_List(عدم, &raw_device_گنتی, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_گنتی)) {
        أرجع; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_گنتی);
    إذا (!raw_devices) {
        أرجع; // oh well.
    }

    raw_device_گنتی = Get_Raw_داخلہ_Device_List(raw_devices, &raw_device_گنتی, حجم(RAWINPUTDEVICELIST));
    إذا (raw_device_گنتی == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        أرجع; // oh well.
    }

    HDEVINFO devinfo = تیاری_Di_Get_Class_Devs_A(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_گنتی);
    old_mice = SDL_GetMice(&old_mouse_گنتی);

    لكل (UINT i = 0; i < raw_device_گنتی; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_رستہ] = { 0 };
        UINT rdi_ناپ = حجم(rdi);
        UINT name_ناپ = SDL_arraysize(devName);
        صحيح vendor = 0, ضرب_حاصل = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        إذا (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cb_ناپ = حجم(rdi);
        إذا (Get_Raw_داخلہ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_ناپ) == ((UINT)-1) ||
            Get_Raw_داخلہ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_ناپ) == ((UINT)-1)) {
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

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &ضرب_حاصل);

        بدل (dwType) {
        حالة RIM_TYPEKEYBOARD:
            إذا (SDL_IsKeyboard((Uint16)vendor, (Uint16)ضرب_حاصل, rdi.keyboard.dw_نمبر_دا_کلیدیں_کل)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڑو_Device_ID(keyboardID, &new_keyboards, &new_keyboard_گنتی);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_گنتی)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ضرب_حاصل, "Keyboard", hid_loaded);
                    SDL_جوڑو_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            إذا (SDL_IsMouse((Uint16)vendor, (Uint16)ضرب_حاصل)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڑو_Device_ID(mouseID, &new_mice, &new_mouse_گنتی);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_گنتی)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)ضرب_حاصل, "Mouse", hid_loaded);
                    SDL_جوڑو_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    لكل (صحيح i = old_keyboard_گنتی; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_گنتی)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_گنتی; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_گنتی)) {
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
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ساكن bool Skip_Alt_Gr_بایاں_Control(WPARAM wParam, LPARAM lParam)
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
    پیغام_2 اگلا_پیغام;
    DWORD پیغام_ویلا = Get_سنیہا_ویلا();
    إذا (Peek_سنیہا(&اگلا_پیغام, عدم, 0, 0, PM_NOREMOVE)) {
        إذا (اگلا_پیغام.سنیہا == WM_KEYDOWN ||
            اگلا_پیغام.سنیہا == WM_SYSKEYDOWN) {
            إذا (اگلا_پیغام.wParam == VK_MENU && (اگلا_پیغام.lParam & 0x01000000) && اگلا_پیغام.ویلا == پیغام_ویلا) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                أرجع true;
            }
        }
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع false;
}

ساكن bool Dispatch_Modal_Loop_سنیہا_Hook(HWND *hwnd, UINT *پیغام, WPARAM *wParam, LPARAM *lParam)
{
    پیغام_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.سنیہا = *پیغام;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    إذا (g_Windows_سنیہا_Hook(g_Windows_سنیہا_Hook_انکڑے, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *پیغام = dummy.سنیہا;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        أرجع true;
    }
    أرجع false;
}

LRESULT CALLBACK WIN_کھڑکی_Proc(HWND hwnd, UINT پیغام, WPARAM wParam, LPARAM lParam)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    LRESULT return_کوڈ = -1;

    // Get the window data for the window
    انکڑے = WIN_Get_کھڑکی_انکڑے_From_HWND(hwnd);
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!انکڑے) {
        // Fallback
        انکڑے = (SDL_کھڑکی_انکڑے *)GetProp(hwnd, متن_2("SDL_WindowData"));
    }
#جے_انت
    إذا (!انکڑے) {
        أرجع Call_کھڑکی_Proc(Def_کھڑکی_Proc, hwnd, پیغام, wParam, lParam);
    }

#جے_تعریف_شدہ WMMSG_DEBUG
    {
        حرف سنیہا[1024];
        إذا (پیغام > MAX_WMMSG) {
            SDL_snprintf(سنیہا, حجم(سنیہا), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, پیغام, wParam, lParam);
        } وإلا {
            SDL_snprintf(سنیہا, حجم(سنیہا), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[پیغام], wParam, lParam);
        }
        OutputDebugStringA(سنیہا);
    }
#جے_انت // WMMSG_DEBUG


    إذا (g_Windows_سنیہا_Hook && انکڑے->وچ_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        إذا (!Dispatch_Modal_Loop_سنیہا_Hook(&hwnd, &پیغام, &wParam, &lParam)) {
            أرجع 0;
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (WIN_HandleIMEMessage(hwnd, پیغام, wParam, &lParam, انکڑے->videodata)) {
        أرجع 0;
    }
#جے_انت

    بدل (پیغام) {

    حالة WM_SHOWWINDOW:
    {
        إذا (wParam) {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
        } وإلا {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
        }
    } اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالة WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        انکڑے->postpone_clipcursor = true;
        انکڑے->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        نقطہ_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(انکڑے->کھڑکی, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
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
        إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            return_کوڈ = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD پیغام_Pos = Get_سنیہا_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(انکڑے->کھڑکی, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        إذا (SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی)) {
            أرجع MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_کھڑکی *ماپا = انکڑے->کھڑکی->ماپا;
        طالما (ماپا) {
            إذا ((ماپا->flags & SDL_کھڑکی_داخلہ_FOCUS) &&
                (ماپا->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال)) {
                أرجع MA_NOACTIVATE;
            }
            ماپا = ماپا->ماپا;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_سنیہا_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(انکڑے->کھڑکی, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_سنیہا_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(انکڑے->کھڑکی, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        إذا (!انکڑے->videodata->Get_اشارہ_گر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!انکڑے->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشارہ_گر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_لبھو_Pen_By_Handle(hpointer);
        إذا (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, انکڑے->کھڑکی, true, true);
        } وإلا {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_فاصلہ | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.عدد_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_جوڑو_Pen_Device(WIN_GetEventTimestamp(), عدم, انکڑے->کھڑکی, &info, hpointer, true);
        }
        return_کوڈ = 0;
    } اكسر;

    حالة WM_POINTERCAPTURECHANGED:
    حالة WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        إذا (!انکڑے->videodata->Get_اشارہ_گر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!انکڑے->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشارہ_گر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_لبھو_Pen_By_Handle(hpointer);
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        إذا ((پیغام == WM_POINTERCAPTURECHANGED) || !IS_اشارہ_گر_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, انکڑے->کھڑکی, false, false);
        }
        return_کوڈ = 0;
    } اكسر;

    حالة WM_POINTERDOWN:
    حالة WM_POINTERUP:
    حالة WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        إذا (!انکڑے->videodata->Get_اشارہ_گر_Type || !انکڑے->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا ((پیغام == WM_POINTERUPDATE) && (اشارہ_گر_type == PT_MOUSE)) {
            انکڑے->آخری_اشارہ_گر_update = lParam;
            return_کوڈ = 0;
            اكسر;
        } وإلا إذا (اشارہ_گر_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_لبھو_Pen_By_Handle(hpointer);
        اشارہ_گر_PEN_INFO pen_info;
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } وإلا إذا (!انکڑے->videodata->Get_اشارہ_گر_Pen_Info || !انکڑے->videodata->Get_اشارہ_گر_Pen_Info(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

        ثابت bool istouching = IS_اشارہ_گر_INCONTACT_WPARAM(wParam) && IS_اشارہ_گر_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        إذا (!istouching) {
            SDL_SendPenTouch(timestamp, pen, کھڑکی, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت اشارہ_گر_INFO *اشارہ_گر_info = &pen_info.اشارہ_گر_Info;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        إذا (!انکڑے->videodata->Get_اشارہ_گر_Device_Rects || !انکڑے->videodata->Get_اشارہ_گر_Device_Rects(اشارہ_گر_info->سروت_Device, &tablet_bounds, &tablet_mapping)) {
            نقطہ_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_منزل_Client(انکڑے->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } وإلا {
            صحيح ix, iy;
            SDL_Get_کھڑکی_Position(کھڑکی, &ix, &iy);
            ثابت SDL_FPoint کھڑکی_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = اشارہ_گر_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.دایاں );
            ثابت عائم facY = اشارہ_گر_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.دایاں  - tablet_mapping.بایاں;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.چوٹی;

            fx = (tablet_mapping.بایاں + (facX * w)) - کھڑکی_pos.x;
            fy = (tablet_mapping.چوٹی  + (facY * h)) - کھڑکی_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, کھڑکی, fx, fy);
        SDL_SendPenButton(timestamp, pen, کھڑکی, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, کھڑکی, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        إذا (pen_info.pen_نقاب & PEN_نقاب_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        إذا (pen_info.pen_نقاب & PEN_نقاب_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        إذا (istouching) {
            SDL_SendPenTouch(timestamp, pen, کھڑکی, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_کوڈ = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

        إذا (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            bool wish_clip_cursor = (
                کھڑکی->flags & (SDL_کھڑکی_MOUSE_RELATIVE_منوال | SDL_کھڑکی_MOUSE_GRABBED) ||
                (کھڑکی->mouse_rect.w > 0 && کھڑکی->mouse_rect.h > 0)
            );
            إذا (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                انکڑے->clipcursor_queued = true;
            }
        }

        إذا (!انکڑے->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_ناپ = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = انکڑے->hwnd;

            إذا (TrackMouseEvent(&trackMouseEvent)) {
                انکڑے->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), انکڑے);
        }

        إذا (!انکڑے->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            إذا (Get_Mouse_سنیہا_سروت((ULONG)Get_سنیہا_Extra_Info()) == SDL_MOUSE_EVENT_سروت_MOUSE &&
                lParam != انکڑے->آخری_اشارہ_گر_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)GET_X_LPARAM(lParam), (عائم)GET_Y_LPARAM(lParam));
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
        إذا (!انکڑے->videodata->raw_mouse_enabled) {
            إذا (Get_Mouse_سنیہا_سروت((ULONG)Get_سنیہا_Extra_Info()) == SDL_MOUSE_EVENT_سروت_MOUSE &&
                lParam != انکڑے->آخری_اشارہ_گر_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, انکڑے, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#إذا 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_داخلہ:
    {
        HRAWINPUT h_Raw_داخلہ = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT ناپ = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        إذا (انکڑے->کھڑکی != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        Get_Raw_داخلہ_انکڑے(h_Raw_داخلہ, RID_داخلہ, &inp, &ناپ, حجم(RAWINPUTHEADER));
        إذا (inp.سرخی.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_داخلہ(WIN_GetEventTimestamp(), انکڑے, inp.سرخی.hDevice, &inp.انکڑے.mouse);
        } وإلا إذا (inp.سرخی.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_داخلہ(WIN_GetEventTimestamp(), انکڑے, inp.سرخی.hDevice, &inp.انکڑے.keyboard);
        }
    } اكسر;
#جے_انت

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        إذا (!انکڑے->videodata->raw_mouse_enabled) {
            چھوٹا amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            إذا (پیغام == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_عام);
            } وإلا {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_عام);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            إذا (SDL_GetMouseFocus() == انکڑے->کھڑکی && !SDL_GetMouse()->relative_منوال && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_سنیہا_Pos();
                نقطہ_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_منزل_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                إذا (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } وإلا {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    إذا (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), انکڑے->کھڑکی, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } وإلا { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            إذا (!SDL_GetMouse()->relative_منوال) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_سیٹ_Mouse_Focus(عدم);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        انکڑے->mouse_tracked = false;

        return_کوڈ = 0;
        اكسر;
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
    {
        إذا (Skip_Alt_Gr_بایاں_Control(wParam, lParam)) {
            return_کوڈ = 0;
            اكسر;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode کوڈ = Windows_جانچ_کوڈ_منزل_SDLScan_کوڈ(lParam, wParam, &rawcode, &virtual_کلید);

        // Detect relevant keyboard shortcuts
        إذا (کوڈ == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            إذا (Should_Generate_کھڑکی_Close_On_Alt_F4()) {
                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
            }
        }

        إذا (virtual_کلید || !انکڑے->videodata->raw_keyboard_enabled || انکڑے->کھڑکی->متن_داخلہ_سرگرم) {
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوڈ, true);
        }
    }

        return_کوڈ = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        إذا (Skip_Alt_Gr_بایاں_Control(wParam, lParam)) {
            return_کوڈ = 0;
            اكسر;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode کوڈ = Windows_جانچ_کوڈ_منزل_SDLScan_کوڈ(lParam, wParam, &rawcode, &virtual_کلید);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        إذا (virtual_کلید || !انکڑے->videodata->raw_keyboard_enabled || انکڑے->کھڑکی->متن_داخلہ_سرگرم) {
            إذا (کوڈ == SDL_SCANCODE_PRINTSCREEN && !keyboardState[کوڈ]) {
                SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوڈ, true);
            }
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کوڈ, false);
        }
    }
        return_کوڈ = 0;
        اكسر;

    حالة WM_UNICHAR:
        إذا (wParam == UNICODE_NOCHAR) {
            return_کوڈ = 1;
        } وإلا {
            إذا (SDL_متن_داخلہ_سرگرم(انکڑے->کھڑکی)) {
                حرف متن[5];
                حرف *سرا = SDL_UCS4_منزل_UTF8((Uint32)wParam, متن);
                *سرا = '\0';
                SDL_Send_Keyboard_متن(متن);
            }
            return_کوڈ = 0;
        }
        اكسر;

    حالة WM_CHAR:
        إذا (SDL_متن_داخلہ_سرگرم(انکڑے->کھڑکی)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            إذا (IS_بلند_SURROGATE(wParam)) {
                انکڑے->بلند_surrogate = (WCHAR)wParam;
            } وإلا {
                WCHAR utf16[3];

                utf16[0] = انکڑے->بلند_surrogate ? انکڑے->بلند_surrogate : (WCHAR)wParam;
                utf16[1] = انکڑے->بلند_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح نتیجہ = WIN_Wide_Char_منزل_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                إذا (نتیجہ > 0) {
                    SDL_Send_Keyboard_متن(utf8);
                }
                انکڑے->بلند_surrogate = L'\0';
            }
        } وإلا {
            انکڑے->بلند_surrogate = L'\0';
        }

        return_کوڈ = 0;
        اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#جے_تعریف_شدہ WM_INPUTLANGCHANGE
    حالة WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_کوڈ = 1;
        اكسر;
#جے_انت // WM_INPUTLANGCHANGE

    حالة WM_NCLBUTTONDOWN:
    {
        انکڑے->وچ_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        إذا (Send_سنیہا(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            نقطہ_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_منزل_Client(hwnd, &cursorPos);
            Post_سنیہا(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } اكسر;

    حالة WM_CAPTURECHANGED:
    {
        انکڑے->وچ_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), انکڑے);
    } اكسر;

#جے_تعریف_شدہ WM_GETMINMAXINFO
    حالة WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT ناپ;
        صحيح x, y;
        صحيح w, h;
        صحيح min_w, min_h;
        صحيح max_w, max_h;
        BOOL constrain_max_ناپ;

        // If this is an expected size change, allow it
        إذا (انکڑے->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        Get_کھڑکی_Rect(hwnd, &ناپ);
        x = ناپ.بایاں;
        y = ناپ.چوٹی;

        // Calculate current size of our window
        SDL_Get_کھڑکی_ناپ(انکڑے->کھڑکی, &w, &h);
        SDL_Get_کھڑکی_Minimum_ناپ(انکڑے->کھڑکی, &min_w, &min_h);
        SDL_Get_کھڑکی_ودھ_توں_ودھ_ناپ(انکڑے->کھڑکی, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        إذا (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_ناپ = TRUE;
        } وإلا {
            constrain_max_ناپ = FALSE;
        }

        إذا (!(SDL_Get_کھڑکی_Flags(انکڑے->کھڑکی) & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی)) {
            ناپ.چوٹی = 0;
            ناپ.بایاں = 0;
            ناپ.bottom = h;
            ناپ.دایاں = w;
            WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &ناپ, 0);
            w = ناپ.دایاں - ناپ.بایاں;
            h = ناپ.bottom - ناپ.چوٹی;
#جے_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#جے_انت
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        إذا (SDL_Get_کھڑکی_Flags(انکڑے->کھڑکی) & SDL_کھڑکی_RESIZABLE) {
            إذا (SDL_Get_کھڑکی_Flags(انکڑے->کھڑکی) & SDL_کھڑکی_BORDERLESS) {
                صحيح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحيح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_ناپ.x = SDL_max(w, screenW);
                info->pt_Max_ناپ.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_ناپ.x = (LONG)w + min_w;
            info->pt_Min_Track_ناپ.y = (LONG)h + min_h;
            إذا (constrain_max_ناپ) {
                info->pt_Max_Track_ناپ.x = (LONG)w + max_w;
                info->pt_Max_Track_ناپ.y = (LONG)h + max_h;
            }
        } وإلا {
            info->pt_Max_ناپ.x = w;
            info->pt_Max_ناپ.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_ناپ.x = w;
            info->pt_Min_Track_ناپ.y = h;
            info->pt_Max_Track_ناپ.x = w;
            info->pt_Max_Track_ناپ.y = h;
        }
    }
        return_کوڈ = 0;
        اكسر;
#جے_انت // WM_GETMINMAXINFO

    حالة WM_WINDOWPOSCHANGING:

        إذا (انکڑے->expected_resize) {
            return_کوڈ = 0;
        } وإلا إذا (انکڑے->وچ_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            إذا (انکڑے->آخری_modal_چوڑائی == windowpos->cx && انکڑے->آخری_modal_اچائی == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            انکڑے->آخری_modal_چوڑائی = windowpos->cx;
            انکڑے->آخری_modal_اچائی = windowpos->cy;

            return_کوڈ = 0;
        }
        اكسر;

    حالة WM_WINDOWPOSCHANGED:
    {
        SDL_کھڑکی *win;
        ثابت SDL_DisplayID original_displayID = انکڑے->کھڑکی->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحيح x, y;
        صحيح w, h;

        إذا (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        إذا (iconic) {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        } وإلا إذا (zoomed) {
            إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
            }
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MAXIMIZED, 0, 0);
            انکڑے->force_ws_maximizebox = true;
        } وإلا إذا (انکڑے->کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED)) {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                انکڑے->force_ws_maximizebox = false;
                WIN_سیٹ_کھڑکی_Resizable(SDL_GetVideoDevice(), انکڑے->کھڑکی, !!(انکڑے->کھڑکی->flags & SDL_کھڑکی_RESIZABLE));
            }
        }

        إذا (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        إذا (iconic) {
            اكسر;
        }

        إذا (انکڑے->initializing) {
            اكسر;
        }

        إذا (!انکڑے->disable_move_ناپ_events) {
            إذا (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
                Client_منزل_Screen(hwnd, (LPPOINT) &rect);
                Client_منزل_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.بایاں;
                y = rect.چوٹی;

                SDL_Global_منزل_Relative_For_کھڑکی(انکڑے->کھڑکی, x, y, &x, &y);
                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            إذا (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
                w = rect.دایاں;
                h = rect.bottom;

                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(انکڑے->کھڑکی);

        // Update the window display position
        إذا (انکڑے->کھڑکی->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_کھڑکی_ICCProfile(انکڑے->کھڑکی, true);
        }

        // Update the position of any child windows
        لكل (win = انکڑے->کھڑکی->پہلا_بچہ; win; win = win->اگلا_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_کھڑکی_IS_POPUP(win) && !(win->flags & SDL_کھڑکی_HIDDEN)) {
                WIN_سیٹ_کھڑکی_Position_اندرونی(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        إذا (g_Windows_سنیہا_Hook) {
            إذا (!Dispatch_Modal_Loop_سنیہا_Hook(&hwnd, &پیغام, &wParam, &lParam)) {
                أرجع 0;
            }
        }

        ++انکڑے->وچ_modal_loop;
        إذا (انکڑے->وچ_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_کھڑکی_Rect(انکڑے->hwnd, &rect);
            انکڑے->آخری_modal_چوڑائی = rect.دایاں - rect.بایاں;
            انکڑے->آخری_modal_اچائی = rect.bottom - rect.چوٹی;

            انکڑے->initial_ناپ_rect.بایاں = انکڑے->کھڑکی->x;
            انکڑے->initial_ناپ_rect.دایاں = انکڑے->کھڑکی->x + انکڑے->کھڑکی->w;
            انکڑے->initial_ناپ_rect.چوٹی = انکڑے->کھڑکی->y;
            انکڑے->initial_ناپ_rect.bottom = انکڑے->کھڑکی->y + انکڑے->کھڑکی->h;

            سیٹ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        إذا (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_کھڑکی_جیوندا_Resize_Update(انکڑے->کھڑکی);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#إذا 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            إذا (انکڑے->videodata->DwmFlush) {
                انکڑے->videodata->DwmFlush();
            }
#جے_انت
#جے_انت
            أرجع 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --انکڑے->وچ_modal_loop;
        إذا (انکڑے->وچ_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } اكسر;

    حالة WM_SIZING:
        {
            WPARAM کنارا = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool جندرا_aspect_تناسب = (انکڑے->کھڑکی->max_aspect == انکڑے->کھڑکی->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            عائم new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            إذا (انکڑے->کھڑکی->min_aspect <= 0 && انکڑے->کھڑکی->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            سیٹ_Rect_خالی_تھاواں(&rc);
            إذا (!Adjust_کھڑکی_Rect_Ex(&rc, Get_کھڑکی_Style(hwnd), GetMenu(hwnd) != عدم, Get_کھڑکی_Ex_Style(hwnd))) {
                اكسر;
            }

            clientDragRect.بایاں -= rc.بایاں;
            clientDragRect.چوٹی -= rc.چوٹی;
            clientDragRect.دایاں -= rc.دایاں;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.دایاں - clientDragRect.بایاں;
            h = clientDragRect.bottom - clientDragRect.چوٹی;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            إذا (جندرا_aspect_تناسب) {
                بدل (کنارا) {
                حالة WMSZ_بایاں:
                حالة WMSZ_دایاں:
                    h = (صحيح)SDL_roundf(w / انکڑے->کھڑکی->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * انکڑے->کھڑکی->max_aspect);
                    اكسر;
                }
            } وإلا {
                بدل (کنارا) {
                حالة WMSZ_بایاں:
                حالة WMSZ_دایاں:
                    إذا (انکڑے->کھڑکی->max_aspect > 0.0f && new_aspect > انکڑے->کھڑکی->max_aspect) {
                        w = (صحيح)SDL_roundf(h * انکڑے->کھڑکی->max_aspect);
                    } وإلا إذا (انکڑے->کھڑکی->min_aspect > 0.0f && new_aspect < انکڑے->کھڑکی->min_aspect) {
                        w = (صحيح)SDL_roundf(h * انکڑے->کھڑکی->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_چوٹی:
                حالة WMSZ_BOTTOM:
                    إذا (انکڑے->کھڑکی->min_aspect > 0.0f && new_aspect < انکڑے->کھڑکی->min_aspect) {
                        h = (صحيح)SDL_roundf(w / انکڑے->کھڑکی->min_aspect);
                    } وإلا إذا (انکڑے->کھڑکی->max_aspect > 0.0f && new_aspect > انکڑے->کھڑکی->max_aspect) {
                        h = (صحيح)SDL_roundf(w / انکڑے->کھڑکی->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    إذا (انکڑے->کھڑکی->max_aspect > 0.0f && new_aspect > انکڑے->کھڑکی->max_aspect) {
                        w = (صحيح)SDL_roundf(h * انکڑے->کھڑکی->max_aspect);
                    } وإلا إذا (انکڑے->کھڑکی->min_aspect > 0.0f && new_aspect < انکڑے->کھڑکی->min_aspect) {
                        h = (صحيح)SDL_roundf(w / انکڑے->کھڑکی->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (کنارا) {
            حالة WMSZ_بایاں:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                إذا (جندرا_aspect_تناسب) {
                    clientDragRect.چوٹی = (انکڑے->initial_ناپ_rect.bottom + انکڑے->initial_ناپ_rect.چوٹی - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                اكسر;
            حالة WMSZ_دایاں:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                إذا (جندرا_aspect_تناسب) {
                    clientDragRect.چوٹی = (انکڑے->initial_ناپ_rect.bottom + انکڑے->initial_ناپ_rect.چوٹی - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_چوٹی:
                إذا (جندرا_aspect_تناسب) {
                    clientDragRect.بایاں = (انکڑے->initial_ناپ_rect.دایاں + انکڑے->initial_ناپ_rect.بایاں - w) / 2;
                }
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                إذا (جندرا_aspect_تناسب) {
                    clientDragRect.بایاں = (انکڑے->initial_ناپ_rect.دایاں + انکڑے->initial_ناپ_rect.بایاں - w) / 2;
                }
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                اكسر;
            }

            // convert the client rect to a window rect
            إذا (!Adjust_کھڑکی_Rect_Ex(&clientDragRect, Get_کھڑکی_Style(hwnd), GetMenu(hwnd) != عدم, Get_کھڑکی_Ex_Style(hwnd))) {
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
            سیٹ_Cursor(SDL_cursor);
            return_کوڈ = TRUE;
        } وإلا إذا (!g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden && !SDL_cursor) {
            سیٹ_Cursor(عدم);
            return_کوڈ = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        إذا (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            إذا (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                سرا_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, عدم);
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }
    }
        return_کوڈ = 0;
        اكسر;

        // We'll do our own drawing, prevent flicker
    حالة WM_ERASEBKGND:
        إذا (Should_Clear_کھڑکی_On_Erase_Background(انکڑے)) {
            RECT client_rect;
            HBRUSH brush;
            انکڑے->videodata->cleared = true;
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
#جے_انت // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
    }
        return_کوڈ = 0;
        اكسر;

    حالة WM_TOUCH:
        إذا (انکڑے->videodata->Get_Touch_داخلہ_Info && انکڑے->videodata->Close_Touch_داخلہ_Handle) {
            UINT i, عدد_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, عدد_inputs, &isstack);
            إذا (inputs && انکڑے->videodata->Get_Touch_داخلہ_Info((HTOUCHINPUT)lParam, عدد_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                إذا (!GetClientRect(hwnd, &rect) || !WIN_کھڑکی_Rect_Valid(&rect)) {
                    إذا (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                Client_منزل_Screen(hwnd, (LPPOINT)&rect);
                Client_منزل_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.چوٹی *= 100;
                rect.بایاں *= 100;
                rect.bottom *= 100;
                rect.دایاں *= 100;

                لكل (i = 0; i < عدد_inputs; ++i) {
                    PTOUCHINPUT داخلہ = &inputs[i];
                    ثابت صحيح w = (rect.دایاں - rect.بایاں);
                    ثابت صحيح h = (rect.bottom - rect.چوٹی);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)داخلہ->h_سروت);
                    ثابت SDL_FingerID fingerId = (داخلہ->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    إذا (SDL_جوڑو_Touch(touchId, SDL_TOUCH_DEVICE_سدھا, (داخلہ->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    إذا (w <= 1) {
                        x = 0.5f;
                    } وإلا {
                        x = (عائم)(داخلہ->x - rect.بایاں) / (w - 1);
                    }
                    إذا (h <= 1) {
                        y = 0.5f;
                    } وإلا {
                        y = (عائم)(داخلہ->y - rect.چوٹی) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    إذا (داخلہ->dwFlags & TOUCHEVENTF_تھلے) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, انکڑے->کھڑکی, SDL_EVENT_FINGER_تھلے, x, y, 1.0f);
                    }
                    إذا (داخلہ->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, انکڑے->کھڑکی, x, y, 1.0f);
                    }
                    إذا (داخلہ->dwFlags & TOUCHEVENTF_اتے) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, انکڑے->کھڑکی, SDL_EVENT_FINGER_اتے, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            انکڑے->videodata->Close_Touch_داخلہ_Handle((HTOUCHINPUT)lParam);
            أرجع 0;
        }
        اكسر;

#جے_تعریف_شدہ HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        أرجع TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#جے_انت // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT گنتی = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < گنتی; ++i) {
            UINT ناپ = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR بفر_2 = (LPTSTR)SDL_malloc(حجم(TCHAR) * ناپ);
            إذا (بفر_2) {
                إذا (DragQueryFile(drop, i, بفر_2, ناپ)) {
                    حرف *file = WIN_String_منزل_UTF8(بفر_2);
                    SDL_SendDropFile(انکڑے->کھڑکی, عدم, file);
                    SDL_free(file);
                }
                SDL_free(بفر_2);
            }
        }
        SDL_SendDropComplete(انکڑے->کھڑکی);
        Drag_انت(drop);
        أرجع 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_کھڑکی_Flags کھڑکی_flags = انکڑے->کھڑکی->flags;
        إذا (wParam == TRUE && (کھڑکی_flags & SDL_کھڑکی_BORDERLESS) && !(کھڑکی_flags & SDL_کھڑکی_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            إذا (Get_کھڑکی_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_کھڑکی(hwnd, MONITOR_DEFAULTTONULL);
                إذا (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت نقطہ_2 pt = { انکڑے->کھڑکی->windowed.x, انکڑے->کھڑکی->windowed.y };
                    hMonitor = Monitor_From_نقطہ(pt, MONITOR_DEFAULTTONEAREST);
                }
                إذا (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_ناپ = حجم(info);
                    إذا (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وإلا إذا (!(کھڑکی_flags & SDL_کھڑکی_RESIZABLE) && !انکڑے->force_ws_maximizebox) {
                صحيح w, h;
                إذا (انکڑے->کھڑکی->آخری_ناپ_pending) {
                    w = انکڑے->کھڑکی->pending.w;
                    h = انکڑے->کھڑکی->pending.h;
                } وإلا {
                    w = انکڑے->کھڑکی->floating.w;
                    h = انکڑے->کھڑکی->floating.h;
                }
                params->rgrc[0].دایاں = params->rgrc[0].بایاں + w;
                params->rgrc[0].bottom = params->rgrc[0].چوٹی + h;
            }
            أرجع 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

        إذا (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
            أرجع HTTRANSPARENT;
        }

        إذا (کھڑکی->کامیابی_test) {
            نقطہ_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            إذا (Screen_منزل_Client(hwnd, &winpoint)) {
                SDL_نقطہ نقطہ;
                SDL_کامیابی_Test_نتیجہ rc;
                نقطہ.x = winpoint.x;
                نقطہ.y = winpoint.y;
                rc = کھڑکی->کامیابی_test(کھڑکی, &نقطہ, کھڑکی->کامیابی_test_انکڑے);
                بدل (rc) {
#تعریف_کرو POST_کامیابی_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_کامیابی_TEST, 0, 0); \
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
                        SDL_سیٹ_Mouse_Focus(کھڑکی);
                        أرجع HTCLIENT;
                    }

                    POST_کامیابی_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_کامیابی_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_چوٹی:
                    POST_کامیابی_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_کامیابی_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_دایاں:
                    POST_کامیابی_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_کامیابی_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_کامیابی_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_کامیابی_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_بایاں:
                    POST_کامیابی_TEST(HTLEFT);
#تعریف_رد POST_کامیابی_TEST
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
        إذا (انکڑے->videodata->Get_Dpi_For_کھڑکی && انکڑے->videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحيح اگلا_DPI = (صحيح)wParam;
            ثابت صحيح prevDPI = (صحيح)انکڑے->videodata->Get_Dpi_For_کھڑکی(hwnd);
            ناپ_3 *ناپ_وچ_باہرلا = (ناپ_3 *)lParam;

            صحيح چوکھٹا_w, چوکھٹا_h;
            صحيح query_client_w_win, query_client_h_win;

#جے_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, اگلا_DPI, ناپ_وچ_باہرلا->cx, ناپ_وچ_باہرلا->cy);
#جے_انت

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                چوکھٹا_w = -rect.بایاں + rect.دایاں;
                چوکھٹا_h = -rect.چوٹی + rect.bottom;

                query_client_w_win = ناپ_وچ_باہرلا->cx - چوکھٹا_w;
                query_client_h_win = ناپ_وچ_باہرلا->cy - چوکھٹا_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.دایاں = query_client_w_win;
                rect.bottom = query_client_h_win;

                إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, اگلا_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                ناپ_وچ_باہرلا->cx = rect.دایاں - rect.بایاں;
                ناپ_وچ_باہرلا->cy = rect.bottom - rect.چوٹی;
            }

#جے_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", ناپ_وچ_باہرلا->cx, ناپ_وچ_باہرلا->cy);
#جے_انت
            أرجع TRUE;
        }
        اكسر;

    حالة WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحيح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحيح w, h;

#جے_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->بایاں, suggestedRect->چوٹی, suggestedRect->دایاں - suggestedRect->بایاں, suggestedRect->bottom - suggestedRect->چوٹی);
#جے_انت

            إذا (انکڑے->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#جے_تعریف_شدہ HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#جے_انت
                أرجع 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.دایاں = انکڑے->کھڑکی->w;
                rect.bottom = انکڑے->کھڑکی->h;

                إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.دایاں - rect.بایاں;
                h = rect.bottom - rect.چوٹی;
            }

#جے_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    انکڑے->کھڑکی->w, انکڑے->کھڑکی->h,
                    suggestedRect->بایاں, suggestedRect->چوٹی, w, h);
#جے_انت

            انکڑے->expected_resize = true;
            سیٹ_کھڑکی_Pos(hwnd,
                         عدم,
                         suggestedRect->بایاں,
                         suggestedRect->چوٹی,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            انکڑے->expected_resize = false;
            أرجع 0;
        }

    حالة WM_SETTINGCHANGE:
        إذا (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_سیٹ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_منوال_For_HWND(hwnd);
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
    حالة WM_ناپ:
    {
        RECT rect;
        صحيح w, h;

        إذا (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
            w = rect.دایاں;
            h = rect.bottom;
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, w, h);
        }
    } اكسر;
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (پیغام && پیغام == انکڑے->videodata->WM_TASKBAR_BUTTON_CREATED) {
        انکڑے->taskbar_button_created = true;
        WIN_Apply_کھڑکی_ترقی(SDL_GetVideoDevice(), انکڑے->کھڑکی);
    }
#جے_انت

    // If there's a window proc, assume it's going to handle messages
    إذا (انکڑے->wndproc) {
        أرجع Call_کھڑکی_Proc(انکڑے->wndproc, hwnd, پیغام, wParam, lParam);
    } وإلا إذا (return_کوڈ >= 0) {
        أرجع return_کوڈ;
    } وإلا {
        أرجع Call_کھڑکی_Proc(Def_کھڑکی_Proc, hwnd, پیغام, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    إذا (g_Windows_Enable_سنیہا_Loop) {
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
        پیغام_2 پیغام;
        BOOL سنیہا_نتیجہ;
        UINT_PTR timer_id = 0;
        إذا (timeoutNS > 0) {
            timer_id = سیٹ_Timer(عدم, 0, (UINT)SDL_NS_منزل_MS(timeoutNS), عدم);
            سنیہا_نتیجہ = Get_سنیہا(&پیغام, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } وإلا إذا (timeoutNS == 0) {
            سنیہا_نتیجہ = Peek_سنیہا(&پیغام, عدم, 0, 0, PM_REMOVE);
        } وإلا {
            سنیہا_نتیجہ = Get_سنیہا(&پیغام, 0, 0, 0);
        }
        إذا (سنیہا_نتیجہ) {
            إذا (پیغام.سنیہا == WM_TIMER && !پیغام.hwnd && پیغام.wParam == timer_id) {
                أرجع 0;
            }
            إذا (g_Windows_سنیہا_Hook) {
                إذا (!g_Windows_سنیہا_Hook(g_Windows_سنیہا_Hook_انکڑے, &پیغام)) {
                    أرجع 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_سنیہا(&پیغام);
            Dispatch_سنیہا(&پیغام);
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وإلا {
        // Fail the wait so the caller falls back to polling
        أرجع -1;
    }
}

فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Post_سنیہا(انکڑے->hwnd, انکڑے->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    پیغام_2 پیغام;

    إذا (g_Windows_Enable_سنیہا_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_سنیہا(&پیغام, hwnd, 0, 0, PM_REMOVE)) {
            WIN_سیٹ_سنیہا_Tick(پیغام.ویلا);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_سنیہا(&پیغام);
            Dispatch_سنیہا(&پیغام);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    پیغام_2 پیغام;
#جے_تعریف_شدہ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ہدایت warning(ڈالو)
#ہدایت warning(disable : 28159)
#جے_انت
    DWORD سرا_ticks = Get_Tick_گنتی() + 1;
#جے_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#جے_انت
    صحيح new_messages = 0;

    إذا (_this->اندرونی->gameinput_context) {
        WIN_Update_Game_داخلہ(_this);
    }

    إذا (g_Windows_Enable_سنیہا_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_سنیہا(&پیغام, عدم, 0, 0, PM_REMOVE)) {
            إذا (g_Windows_سنیہا_Hook) {
                إذا (!g_Windows_سنیہا_Hook(g_Windows_سنیہا_Hook_انکڑے, &پیغام)) {
                    استمر;
                }
            }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            إذا (پیغام.سنیہا == WM_MOUSEMOVE && SDL_آخری_warp_ویلا) {
                إذا (!SDL_TICKS_PASSED(پیغام.ویلا, (SDL_آخری_warp_ویلا + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_آخری_warp_ویلا = 0;
            }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_سیٹ_سنیہا_Tick(پیغام.ویلا);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_سنیہا(&پیغام);
            Dispatch_سنیہا(&پیغام);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            إذا (SDL_TICKS_PASSED(پیغام.ویلا, سرا_ticks)) {
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
    إذا (keystate[SDL_SCANCODE_LSHIFT] && !(Get_کلید_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    إذا (keystate[SDL_SCANCODE_RSHIFT] && !(Get_کلید_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_کھڑکی *focus_کھڑکی = SDL_GetKeyboardFocus();
    إذا (!focus_کھڑکی || !(focus_کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        إذا (keystate[SDL_SCANCODE_LGUI] && !(Get_کلید_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        إذا (keystate[SDL_SCANCODE_RGUI] && !(Get_کلید_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    إذا (_this) {
        SDL_کھڑکی *کھڑکی = _this->windows;
        طالما (کھڑکی) {
            bool refresh_clipcursor = false;
            SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
            إذا (انکڑے) {
                refresh_clipcursor = انکڑے->clipcursor_queued;
                انکڑے->clipcursor_queued = false;    // Must be cleared unconditionally.
                انکڑے->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
                WIN_UpdateClipCursor(کھڑکی);
            }
            کھڑکی = کھڑکی->اگلا;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_کھڑکی = SDL_GetKeyboardFocus();
    إذا (focus_کھڑکی && (focus_کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
        SDL_کھڑکی_انکڑے *انکڑے = focus_کھڑکی->اندرونی;

        إذا (!انکڑے->mouse_tracked) {
            نقطہ_2 cursorPos;

            إذا (GetCursorPos(&cursorPos) && Screen_منزل_Client(انکڑے->hwnd, &cursorPos)) {
                bool وٹاندرا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID,
                                    !وٹاندرا_Buttons ? SDL_BUTTON_بایاں : SDL_BUTTON_دایاں,
                                    (Get_Async_کلید_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID,
                                    !وٹاندرا_Buttons ? SDL_BUTTON_دایاں : SDL_BUTTON_بایاں,
                                    (Get_Async_کلید_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID,
                                    SDL_BUTTON_درمیان,
                                    (Get_Async_کلید_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_کلید_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), انکڑے->کھڑکی, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_کلید_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#جے_تعریف_شدہ SDL_PLATFORM_GDK
    GDK_Dispatch_Task_قطار();
#جے_انت
}

ساكن صحيح app_registered = 0;
LPTSTR SDL_Appname = عدم;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = عدم;

ساكن فراغ WIN_Clean_رجسٹر_App(WNDCLASSEX wcex)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    إذا (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#جے_انت
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
    wcex->hIcon = لدو_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    أرجع FALSE;
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_رجسٹر_App(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#جے_انت

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
#جے_انت
    }
    SDL_Appname = WIN_UTF8_منزل_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(عدم);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_ناپ = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_کھڑکی_Proc;
    wcex.hInstance = SDL_Instance;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    إذا (hint && *hint) {
        wcex.hIcon = لدو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        إذا (hint && *hint) {
            wcex.hIconSm = لدو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وإلا {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_ناں(SDL_Instance, RT_گروہ_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    إذا (!رجسٹر_Class_Ex(&wcex)) {
        WIN_Clean_رجسٹر_App(wcex);
        أرجع SDL_سیٹ_Error("Couldn't register application class");
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
#جے_انت
        WIN_Clean_رجسٹر_App(wcex);
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS
