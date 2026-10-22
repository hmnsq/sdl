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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS

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
#اگر_تعریف_شده HAVE_TPCSHRD_H
#ضمن <tpcshrd.h>
#پایان_اگر // HAVE_TPCSHRD_H

#إذا 0
#تعریف_کن WMMSG_DEBUG
#پایان_اگر
#اگر_تعریف_شده WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#پایان_اگر

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
#پایان_اگر

#اگر_تعریف_شده SDL_PLATFORM_GDK
#ضمن "../../core/gdk/SDL_gdk.h"
#پایان_اگر

// #define HIGHDPI_DEBUG

// Undocumented window messages
#اگر_تعریف_نشده WM_NCUAHDRAWCAPTION
#تعریف_کن WM_NCUAHDRAWCAPTION 0xAE
#پایان_اگر
#اگر_تعریف_نشده WM_NCUAHDRAWFRAME
#تعریف_کن WM_NCUAHDRAWFRAME 0xAF
#پایان_اگر

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#اگر_تعریف_نشده WM_XBUTTONDOWN
#تعریف_کن WM_XBUTTONDOWN 0x020B
#پایان_اگر
#اگر_تعریف_نشده WM_XBUTTONUP
#تعریف_کن WM_XBUTTONUP 0x020C
#پایان_اگر
#اگر_تعریف_نشده GET_XBUTTON_WPARAM
#تعریف_کن GET_XBUTTON_WPARAM(w) (HIWORD(w))
#پایان_اگر
#اگر_تعریف_نشده WM_درون_داد
#تعریف_کن WM_درون_داد 0x00ff
#پایان_اگر
#اگر_تعریف_نشده WM_TOUCH
#تعریف_کن WM_TOUCH 0x0240
#پایان_اگر
#اگر_تعریف_نشده WM_MOUSEHWHEEL
#تعریف_کن WM_MOUSEHWHEEL 0x020E
#پایان_اگر
#اگر_تعریف_نشده RI_MOUSE_HWHEEL
#تعریف_کن RI_MOUSE_HWHEEL 0x0800
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERUPDATE
#تعریف_کن WM_POINTERUPDATE 0x0245
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERDOWN
#تعریف_کن WM_POINTERDOWN 0x0246
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERUP
#تعریف_کن WM_POINTERUP 0x0247
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERENTER
#تعریف_کن WM_POINTERENTER 0x0249
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERLEAVE
#تعریف_کن WM_POINTERLEAVE 0x024A
#پایان_اگر
#اگر_تعریف_نشده WM_POINTERCAPTURECHANGED
#تعریف_کن WM_POINTERCAPTURECHANGED 0x024C
#پایان_اگر
#اگر_تعریف_نشده WM_UNICHAR
#تعریف_کن WM_UNICHAR 0x0109
#پایان_اگر
#اگر_تعریف_نشده WM_DPICHANGED
#تعریف_کن WM_DPICHANGED 0x02E0
#پایان_اگر
#اگر_تعریف_نشده WM_GETDPISCALEDSIZE
#تعریف_کن WM_GETDPISCALEDSIZE 0x02E4
#پایان_اگر
#اگر_تعریف_نشده TOUCHEVENTF_PEN
#تعریف_کن TOUCHEVENTF_PEN 0x0040
#پایان_اگر

#اگر_تعریف_نشده MAPVK_VK_مقصد_VSC_EX
#تعریف_کن MAPVK_VK_مقصد_VSC_EX 4
#پایان_اگر

#اگر_تعریف_نشده WC_ERR_INVALID_CHARS
#تعریف_کن WC_ERR_INVALID_CHARS 0x00000080
#پایان_اگر

#اگر_تعریف_نشده IS_بالا_SURROGATE
#تعریف_کن IS_بالا_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#پایان_اگر

#اگر_تعریف_نشده USER_TIMER_MINIMUM
#تعریف_کن USER_TIMER_MINIMUM 0x0000000A
#پایان_اگر

// Used to compare Windows message timestamps
#تعریف_کن SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#اگر_تعریف_شده _WIN64
تعريفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#پایان_اگر

ساكن bool SDL_processing_messages;
ساكن DWORD پیام_tick;
ساكن Uint64 timestamp_جابه_جایی;

ساكن فراغ WIN_مجموعه_پیام_Tick(DWORD tick)
{
    پیام_tick = tick;
}

ساكن Uint64 WIN_GetEventTimestamp(فراغ)
{
    ثابت Uint64 TIMESTAMP_WRAP_جابه_جایی = SDL_MS_مقصد_NS(0x100000000LL);
    Uint64 timestamp, now;

    إذا (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        أرجع 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_مقصد_NS(پیام_tick);
    timestamp += timestamp_جابه_جایی;
    إذا (!timestamp_جابه_جایی) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_جابه_جایی = (now - timestamp);
        timestamp = now;
    } وإلا إذا ((Sint64)(now - timestamp - TIMESTAMP_WRAP_جابه_جایی) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_جابه_جایی += TIMESTAMP_WRAP_جابه_جایی;
        timestamp += TIMESTAMP_WRAP_جابه_جایی;
    } وإلا إذا (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_جابه_جایی -= (timestamp - now);
        timestamp = now;
    }
    أرجع timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_Windows_پیام_Hook g_Windows_پیام_Hook = عدم;
ساكن فراغ *g_Windows_پیام_Hook_داده = عدم;

فراغ SDL_مجموعه_Windows_پیام_Hook(SDL_Windows_پیام_Hook callback, فراغ *userdata)
{
    g_Windows_پیام_Hook = callback;
    g_Windows_پیام_Hook_داده = userdata;
}

ساكن SDL_Scancode Windows_پیمایش_کد_مقصد_SDLScan_کد(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_کلید)
{
    SDL_Scancode کد;
    Uint8 شاخص;
    Uint16 کلید_Flags = HIWORD(lParam);
    Uint16 پیمایش_کد = LOBYTE(کلید_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    پیمایش_کد &= ~0x80;

    *virtual_کلید = (پیمایش_کد == 0);

    إذا (پیمایش_کد != 0) {
        إذا ((کلید_Flags & KF_EXTENDED) == KF_EXTENDED) {
            پیمایش_کد = MAKEWORD(پیمایش_کد, 0xe0);
        } وإلا إذا (پیمایش_کد == 0x45) {
            // Pause
            پیمایش_کد = 0xe046;
        }
    } وإلا {
        Uint16 vk_کد = LOWORD(wParam);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        پیمایش_کد = LOWORD(Map_Virtual_کلید(vk_کد, WIN_IsWindowsXP() ? MAPVK_VK_مقصد_VSC : MAPVK_VK_مقصد_VSC_EX));
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        إذا (پیمایش_کد == 0xe11d) {
            پیمایش_کد = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    شاخص = LOBYTE(پیمایش_کد) | (HIBYTE(پیمایش_کد) ? 0x80 : 0x00);
    کد = windows_scancode_جدول[شاخص];
    *rawcode = پیمایش_کد;

    أرجع کد;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_پنجره_داده *داده)
{
    أرجع !SDL_پنجره_IS_POPUP(داده->پنجره) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_جابجا_Buttons, SDL_پنجره_داده *داده, Uint8 button, SDL_MouseID mouseID)
{
    إذا (b_جابجا_Buttons) {
        إذا (button == SDL_BUTTON_چپ) {
            button = SDL_BUTTON_راست;
        } وإلا إذا (button == SDL_BUTTON_راست) {
            button = SDL_BUTTON_چپ;
        }
    }

    إذا (داده->focus_click_pending & SDL_BUTTON_ماسک(button)) {
        // Ignore the button click for activation
        إذا (!bwParamMousePressed) {
            داده->focus_click_pending &= ~SDL_BUTTON_ماسک(button);
            WIN_UpdateClipCursor(داده->پنجره);
        }
        أرجع;
    }

    إذا (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_ماسک(button))) {
        SDL_SendMouseButton(timestamp, داده->پنجره, mouseID, button, true);
    } وإلا إذا (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_ماسک(button))) {
        SDL_SendMouseButton(timestamp, داده->پنجره, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_پنجره_داده *داده, SDL_MouseID mouseID)
{
    إذا (wParam != داده->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, داده, SDL_BUTTON_چپ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, داده, SDL_BUTTON_میانه, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, داده, SDL_BUTTON_راست, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, داده, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, داده, SDL_BUTTON_X2, mouseID);

        داده->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_پنجره_داده *داده)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT کلید_State;
    bool جابجا_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    جابجا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    کلید_State = Get_Async_کلید_State(VK_LBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, جابجا_Buttons, داده, SDL_BUTTON_چپ, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_RBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, جابجا_Buttons, داده, SDL_BUTTON_راست, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_MBUTTON);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, جابجا_Buttons, داده, SDL_BUTTON_میانه, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON1);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, جابجا_Buttons, داده, SDL_BUTTON_X1, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON2);
    إذا (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, جابجا_Buttons, داده, SDL_BUTTON_X2, mouseID);
    }
    داده->mouse_button_flags = (WPARAM)-1;
}

ساكن فراغ WIN_UpdateFocus(SDL_پنجره *پنجره, bool expect_focus, LPPOINT pos)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == پنجره);
    bool has_focus = (Get_Foreground_پنجره() == hwnd);

    إذا (had_focus == has_focus || has_focus != expect_focus) {
        أرجع;
    }

    إذا (has_focus) {
        نقطه_2 cursorPos;

        إذا (WIN_ShouldIgnoreFocusClick(داده) && !(پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
            bool جابجا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            إذا (Get_Async_کلید_State(VK_LBUTTON)) {
                داده->focus_click_pending |= !جابجا_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            إذا (Get_Async_کلید_State(VK_RBUTTON)) {
                داده->focus_click_pending |= !جابجا_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            إذا (Get_Async_کلید_State(VK_MBUTTON)) {
                داده->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            إذا (Get_Async_کلید_State(VK_XBUTTON1)) {
                داده->focus_click_pending |= SDL_BUTTON_X1_ماسک;
            }
            إذا (Get_Async_کلید_State(VK_XBUTTON2)) {
                داده->focus_click_pending |= SDL_BUTTON_X2_ماسک;
            }
        }

        SDL_مجموعه_Keyboard_Focus(پنجره->keyboard_focus ? پنجره->keyboard_focus : پنجره);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        إذا (!SDL_GetMouse()->relative_نما) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_مقصد_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), داده);
        WIN_UpdateClipCursor(پنجره);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(داده->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلید_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_رقم, (Get_کلید_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلید_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_پنجره_ICCProfile(داده->پنجره, true);
    } وإلا {
        داده->درون_پنجره_deactivation = true;

        SDL_مجموعه_Keyboard_Focus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        إذا (SDL_GetMouse()->relative_نما) {
            SDL_مجموعه_Mouse_Focus(عدم);
        }
        WIN_Reset_Dead_کلیدها();

        WIN_Unclip_Cursor_For_پنجره(پنجره);

        داده->درون_پنجره_deactivation = false;
    }
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool Should_Generate_پنجره_Close_On_Alt_F4(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool Should_Clear_پنجره_On_Erase_Background(SDL_پنجره_داده *داده)
{
    بدل (داده->hint_erase_background_نما) {
    حالة SDL_ERASEBACKGROUNDMODE_NEVER:
        أرجع false;
    حالة SDL_ERASEBACKGROUNDMODE_INITIAL:
        أرجع !داده->videodata->cleared;
    حالة SDL_ERASEBACKGROUNDMODE_ALWAYS:
        أرجع true;
    افتراضي:
        // Unexpected value, fallback to default behaviour
        أرجع !داده->videodata->cleared;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#تعریف_کن MI_WP_SIGNATURE      0xFF515700
#تعریف_کن MI_WP_SIGNATURE_ماسک 0xFFFFFF00
#تعریف_کن IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_ماسک) == MI_WP_SIGNATURE

تعريفنوع تعداد
{
    SDL_MOUSE_EVENT_منبع_UNKNOWN,
    SDL_MOUSE_EVENT_منبع_MOUSE,
    SDL_MOUSE_EVENT_منبع_TOUCH,
    SDL_MOUSE_EVENT_منبع_PEN,
} SDL_MOUSE_EVENT_منبع;

ساكن SDL_MOUSE_EVENT_منبع Get_Mouse_پیام_منبع(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    إذا (IsTouchEvent(extrainfo)) {
        إذا (extrainfo & 0x80) {
            أرجع SDL_MOUSE_EVENT_منبع_TOUCH;
        } وإلا {
            أرجع SDL_MOUSE_EVENT_منبع_PEN;
        }
    }
    أرجع SDL_MOUSE_EVENT_منبع_MOUSE;
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_پنجره_داده *WIN_Get_پنجره_داده_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_پنجره *پنجره;

    إذا (_this) {
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            SDL_پنجره_داده *داده = پنجره->داخلی;
            إذا (داده && داده->hwnd == hwnd) {
                أرجع داده;
            }
        }
    }
    أرجع عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح n_کد, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_داده = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_داده *داده = SDL_GetVideoDevice()->داخلی;
    SDL_Scancode پیمایش_کد;

    إذا (n_کد < 0 || n_کد != HC_ACTION) {
        أرجع Call_بعدی_Hook_Ex(عدم, n_کد, wParam, lParam);
    }
    إذا (hook_داده->پیمایش_کد == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        أرجع 1;
    }

    بدل (hook_داده->vk_کد) {
    حالة VK_LWIN:
        پیمایش_کد = SDL_SCANCODE_LGUI;
        اكسر;
    حالة VK_RWIN:
        پیمایش_کد = SDL_SCANCODE_RGUI;
        اكسر;
    حالة VK_LMENU:
        پیمایش_کد = SDL_SCANCODE_LALT;
        اكسر;
    حالة VK_RMENU:
        پیمایش_کد = SDL_SCANCODE_RALT;
        اكسر;
    حالة VK_LCONTROL:
        پیمایش_کد = SDL_SCANCODE_LCTRL;
        اكسر;
    حالة VK_RCONTROL:
        پیمایش_کد = SDL_SCANCODE_RCTRL;
        اكسر;
    حالة VK_SNAPSHOT:
        پیمایش_کد = SDL_SCANCODE_PRINTSCREEN;
        اكسر;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالة VK_TAB:
        پیمایش_کد = SDL_SCANCODE_TAB;
        اكسر;
    حالة VK_ESCAPE:
        پیمایش_کد = SDL_SCANCODE_ESCAPE;
        اكسر;

    افتراضي:
        أرجع Call_بعدی_Hook_Ex(عدم, n_کد, wParam, lParam);
    }

    إذا (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        إذا (!داده->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_داده->پیمایش_کد, پیمایش_کد, true);
        }
    } وإلا {
        إذا (!داده->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_داده->پیمایش_کد, پیمایش_کد, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        إذا (hook_داده->vk_کد <= 0xFF && داده->pre_hook_کلید_state[hook_داده->vk_کد]) {
            داده->pre_hook_کلید_state[hook_داده->vk_کد] = 0;
            أرجع Call_بعدی_Hook_Ex(عدم, n_کد, wParam, lParam);
        }
    }

    أرجع 1;
}

ساكن bool WIN_جابجا_Buttons(HANDLE hDevice)
{
    إذا (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        أرجع false;
    }
    أرجع GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_Handle_Raw_Mouse_درون_داد(Uint64 timestamp, SDL_Video_داده *داده, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool پایین;
    } raw_buttons[] = {
        { RI_MOUSE_چپ_BUTTON_پایین, SDL_BUTTON_چپ, true },
        { RI_MOUSE_چپ_BUTTON_به_بالا, SDL_BUTTON_چپ, false },
        { RI_MOUSE_راست_BUTTON_پایین, SDL_BUTTON_راست, true },
        { RI_MOUSE_راست_BUTTON_به_بالا, SDL_BUTTON_راست, false },
        { RI_MOUSE_میانه_BUTTON_پایین, SDL_BUTTON_میانه, true },
        { RI_MOUSE_میانه_BUTTON_به_بالا, SDL_BUTTON_میانه, false },
        { RI_MOUSE_BUTTON_4_پایین, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_به_بالا, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_پایین, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_به_بالا, SDL_BUTTON_X2, false }
    };

    صحيح dx = (صحيح)rawmouse->l_آخرین_X;
    صحيح dy = (صحيح)rawmouse->l_آخرین_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    إذا (!داده->raw_mouse_enabled) {
        أرجع;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_پنجره *پنجره = SDL_GetKeyboardFocus();
    إذا (!پنجره) {
        أرجع;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse) {
        أرجع;
    }

    إذا (Get_Mouse_پیام_منبع(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_منبع_MOUSE ||
        (SDL_Touch_Devices_موجود() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        أرجع;
    }

    SDL_پنجره_داده *windowdata = پنجره->داخلی;

    إذا (haveMotion && !windowdata->درون_modal_loop) {
        إذا (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, پنجره, mouseID, true, (عائم)dx, (عائم)dy);
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
            إذا (داده->آخرین_raw_mouse_position.x == 0 && داده->آخرین_raw_mouse_position.y == 0) {
                داده->آخرین_raw_mouse_position.x = x;
                داده->آخرین_raw_mouse_position.y = y;
            }
            relX = x - داده->آخرین_raw_mouse_position.x;
            relY = y - داده->آخرین_raw_mouse_position.y;

            إذا (remote_desktop) {
                إذا (!windowdata->درون_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    إذا (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.چپ + ((rect.راست - rect.چپ) / 2) + wobble;
                        صحيح warpY = rect.بالاترین + ((rect.bottom - rect.بالاترین) / 2);

                        WIN_مجموعه_Cursor_Pos(warpX, warpY);

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
                            SDL_SendMouseMotion(timestamp, پنجره, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } وإلا إذا (mouse->pen_mouse_events) {
                ثابت صحيح بیشینه_TABLET_RELATIVE_MOTION = 32;
                إذا (SDL_abs(relX) > بیشینه_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > بیشینه_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وإلا {
                    SDL_SendMouseMotion(timestamp, پنجره, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } وإلا {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                إذا (!داده->raw_درون_داد_fake_pen_id) {
                    داده->raw_درون_داد_fake_pen_id = SDL_جمع_کن_Pen_Device(timestamp, "raw mouse input", پنجره, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, داده->raw_درون_داد_fake_pen_id, پنجره, (عائم)(x + screen_x - پنجره->x), (عائم)(y + screen_y - پنجره->y));
            }

            داده->آخرین_raw_mouse_position.x = x;
            داده->آخرین_raw_mouse_position.y = y;
        }
    }

    إذا (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            إذا (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool پایین = raw_buttons[i].پایین;

                إذا (button == SDL_BUTTON_چپ) {
                    إذا (WIN_جابجا_Buttons(hDevice)) {
                        button = SDL_BUTTON_راست;
                    }
                } وإلا إذا (button == SDL_BUTTON_راست) {
                    إذا (WIN_جابجا_Buttons(hDevice)) {
                        button = SDL_BUTTON_چپ;
                    }
                }

                إذا (windowdata->focus_click_pending & SDL_BUTTON_ماسک(button)) {
                    // Ignore the button click for activation
                    إذا (!پایین) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_ماسک(button);
                        WIN_UpdateClipCursor(پنجره);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, پنجره, mouseID, button, پایین);
            }
        }

        إذا (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_داده;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, پنجره, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_نرمال);
        } وإلا إذا (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_داده;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, پنجره, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_نرمال);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_Handle_Raw_Keyboard_درون_داد(Uint64 timestamp, SDL_Video_داده *داده, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    إذا (!داده->raw_keyboard_enabled) {
        أرجع;
    }

    إذا (rawkeyboard->Flags & RI_کلید_E1) {
        // First key in a Ctrl+{key} sequence
        داده->pending_E1_کلید_sequence = true;
        أرجع;
    }

    إذا ((rawkeyboard->Flags & RI_کلید_E0) && rawkeyboard->Make_کد == 0x2A) {
        // 0xE02A make code prefix, ignored
        أرجع;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!rawkeyboard->Make_کد) {
        rawkeyboard->Make_کد = LOWORD(Map_Virtual_کلید(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_مقصد_VSC : MAPVK_VK_مقصد_VSC_EX));
    }
#پایان_اگر
    إذا (!rawkeyboard->Make_کد) {
        أرجع;
    }

    bool پایین;
    بدل (rawkeyboard->پیام_4) {
    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
        پایین = true;
        اكسر;
    حالة WM_KEYUP:
    حالة WM_SYSKEYUP:
        پایین = false;
        اكسر;
    افتراضي:
        پایین = !(rawkeyboard->Flags & RI_کلید_BREAK);
        اكسر;
    }

    SDL_Scancode کد;
    USHORT rawcode = rawkeyboard->Make_کد;
    إذا (داده->pending_E1_کلید_sequence) {
        rawcode |= 0xE100;
        إذا (rawkeyboard->Make_کد == 0x45) {
            // Ctrl+NumLock == Pause
            کد = SDL_SCANCODE_PAUSE;
        } وإلا {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            کد = SDL_SCANCODE_UNKNOWN;
        }
        داده->pending_E1_کلید_sequence = false;
    } وإلا {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 شاخص = (Uint8)rawkeyboard->Make_کد;
        إذا (rawkeyboard->Flags & RI_کلید_E0) {
            rawcode |= 0xE000;
            شاخص |= 0x80;
        }
        کد = windows_scancode_جدول[شاخص];
    }

    إذا (پایین) {
        SDL_پنجره *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        إذا ((!داده->raw_keyboard_flag_inputsink && !focus) || (focus && focus->متن_درون_داد_فعال)) {
            أرجع;
        }
    }

    SDL_Send_Keyboard_کلید(timestamp, keyboardID, rawcode, کد, پایین);
}

فراغ WIN_Poll_Raw_درون_داد(SDL_VideoDevice *_this, Uint64 poll_شروع)
{
    SDL_Video_داده *داده = _this->داخلی;
    UINT اندازه, i, شمار, مجموع = 0;
    RAWINPUT *درون_داد;
    Uint64 poll_پایان;

    إذا (داده->rawinput_جابه_جایی == 0) {
        BOOL isWow64;

        داده->rawinput_جابه_جایی = حجم(RAWINPUTHEADER);
        إذا (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            داده->rawinput_جابه_جایی += 8;
        }
    }

    // Get all available events
    درون_داد = (RAWINPUT *)داده->rawinput;
    لكل (;;) {
        اندازه = داده->rawinput_اندازه - (UINT)((BYTE *)درون_داد - داده->rawinput);
        شمار = Get_Raw_درون_داد_میانگیر(درون_داد, &اندازه, حجم(RAWINPUTHEADER));
        poll_پایان = SDL_GetTicksNS();
        إذا (شمار == 0 || شمار == (UINT)-1) {
            إذا (!داده->rawinput || (شمار == (UINT)-1 && Get_آخرین_Error() == ERROR_INSUFFICIENT_میانگیر)) {
                ثابت UINT RAWINPUT_میانگیر_اندازه_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(داده->rawinput, داده->rawinput_اندازه + RAWINPUT_میانگیر_اندازه_INCREMENT);
                إذا (!rawinput) {
                    اكسر;
                }
                درون_داد = (RAWINPUT *)(rawinput + ((BYTE *)درون_داد - داده->rawinput));
                داده->rawinput = rawinput;
                داده->rawinput_اندازه += RAWINPUT_میانگیر_اندازه_INCREMENT;
            } وإلا {
                اكسر;
            }
        } وإلا {
            مجموع += شمار;

            // Advance input to the end of the buffer
            طالما (شمار--) {
                درون_داد = NEXTRAWINPUTBLOCK(درون_داد);
            }
        }
    }

    إذا (مجموع > 0) {
        Uint64 delta = poll_پایان - poll_شروع;
        UINT mouse_مجموع = 0;
        لكل (i = 0, درون_داد = (RAWINPUT *)داده->rawinput; i < مجموع; ++i, درون_داد = NEXTRAWINPUTBLOCK(درون_داد)) {
            إذا (درون_داد->سرآیند.dwType == RIM_TYPEMOUSE) {
                mouse_مجموع += 1;
            }
        }
        صحيح mouse_شاخص = 0;
        لكل (i = 0, درون_داد = (RAWINPUT *)داده->rawinput; i < مجموع; ++i, درون_داد = NEXTRAWINPUTBLOCK(درون_داد)) {
            إذا (درون_داد->سرآیند.dwType == RIM_TYPEMOUSE) {
                mouse_شاخص += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)درون_داد + داده->rawinput_جابه_جایی);
                Uint64 زمان = poll_پایان - (delta * (mouse_مجموع - mouse_شاخص)) / mouse_مجموع;
                WIN_Handle_Raw_Mouse_درون_داد(زمان, داده, درون_داد->سرآیند.hDevice, rawmouse);
            } وإلا إذا (درون_داد->سرآیند.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)درون_داد + داده->rawinput_جابه_جایی);
                WIN_Handle_Raw_Keyboard_درون_داد(poll_پایان, داده, درون_داد->سرآیند.hDevice, rawkeyboard);
            }
        }
    }
    داده->آخرین_rawinput_poll = poll_پایان;
}

ساكن فراغ جمع_کن_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *شمار)
{
    صحيح new_شمار = (*شمار + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمار * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح شمار)
{
    لكل (صحيح i = 0; i < شمار; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن حرف *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت حرف *instance, Uint16 vendor, Uint16 حاصلضرب, ثابت حرف *default_name, bool hid_loaded)
{
    حرف *vendor_name = عدم;
    حرف *حاصلضرب_name = عدم;
    حرف *name = عدم;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    إذا (hid_loaded) {
        حرف devName[MAX_مسیر + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_درون_داد_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        إذا (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            إذا (hFile != INVALID_HANDLE_مقدار) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_Hid_D_Get_حاصلضرب_String(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    إذا (vend[0]) {
        vendor_name = WIN_String_مقصد_UTF8_W(vend);
    }

    إذا (prod[0]) {
        حاصلضرب_name = WIN_String_مقصد_UTF8_W(prod);
    } وإلا {
        SP_DEVINFO_داده داده;
        SDL_zero(داده);
        داده.cb_اندازه = حجم(داده);
        لكل (DWORD i = 0;; ++i) {
            إذا (!راهاندازی_Di_Enum_Device_Info(devinfo, i, &داده)) {
                إذا (Get_آخرین_Error() == ERROR_NO_بیشتر_اقلام) {
                    اكسر;
                } وإلا {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            إذا (!راهاندازی_Di_Get_Device_Instance_Id_A(devinfo, &داده, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            إذا (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD اندازه = 0;
                إذا (راهاندازی_Di_Get_Device_Registry_Property_W(devinfo, &داده, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &اندازه)) {
                    // Make sure the device description is null terminated
                    اندازه /= حجم(*prod);
                    إذا (اندازه >= SDL_arraysize(prod)) {
                        // Truncated description...
                        اندازه = (SDL_arraysize(prod) - 1);
                    }
                    prod[اندازه] = 0;

                    إذا (vendor || حاصلضرب) {
                        SDL_asprintf(&حاصلضرب_name, "%S (0x%.4x/0x%.4x)", prod, vendor, حاصلضرب);
                    } وإلا {
                        حاصلضرب_name = WIN_String_مقصد_UTF8_W(prod);
                    }
                }
                اكسر;
            }
        }
    }

    إذا (!حاصلضرب_name && (vendor || حاصلضرب)) {
        SDL_asprintf(&حاصلضرب_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, حاصلضرب);
    }
    name = SDL_CreateDeviceName(vendor, حاصلضرب, vendor_name, حاصلضرب_name, default_name);
    SDL_free(vendor_name);
    SDL_free(حاصلضرب_name);

    أرجع name;
}

فراغ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = عدم;
    UINT raw_device_شمار = 0;
    صحيح old_keyboard_شمار = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_شمار = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_شمار = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_شمار = 0;
    SDL_MouseID *new_mice = عدم;

    إذا (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->داخلی->detect_device_hotplug ||
        _this->داخلی->gameinput_context) {
        أرجع;
    }

    إذا ((Get_Raw_درون_داد_Device_List(عدم, &raw_device_شمار, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_شمار)) {
        أرجع; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_شمار);
    إذا (!raw_devices) {
        أرجع; // oh well.
    }

    raw_device_شمار = Get_Raw_درون_داد_Device_List(raw_devices, &raw_device_شمار, حجم(RAWINPUTDEVICELIST));
    إذا (raw_device_شمار == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        أرجع; // oh well.
    }

    HDEVINFO devinfo = راهاندازی_Di_Get_Class_Devs_A(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمار);
    old_mice = SDL_GetMice(&old_mouse_شمار);

    لكل (UINT i = 0; i < raw_device_شمار; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_مسیر] = { 0 };
        UINT rdi_اندازه = حجم(rdi);
        UINT name_اندازه = SDL_arraysize(devName);
        صحيح vendor = 0, حاصلضرب = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        إذا (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cb_اندازه = حجم(rdi);
        إذا (Get_Raw_درون_داد_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_اندازه) == ((UINT)-1) ||
            Get_Raw_درون_داد_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_اندازه) == ((UINT)-1)) {
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

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &حاصلضرب);

        بدل (dwType) {
        حالة RIM_TYPEKEYBOARD:
            إذا (SDL_IsKeyboard((Uint16)vendor, (Uint16)حاصلضرب, rdi.keyboard.dw_عدد_از_کلیدها_مجموع)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جمع_کن_Device_ID(keyboardID, &new_keyboards, &new_keyboard_شمار);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمار)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصلضرب, "Keyboard", hid_loaded);
                    SDL_جمع_کن_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            إذا (SDL_IsMouse((Uint16)vendor, (Uint16)حاصلضرب)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جمع_کن_Device_ID(mouseID, &new_mice, &new_mouse_شمار);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_شمار)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصلضرب, "Mouse", hid_loaded);
                    SDL_جمع_کن_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    لكل (صحيح i = old_keyboard_شمار; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمار)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_شمار; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمار)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    راهاندازی_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ساكن bool Skip_Alt_Gr_چپ_Control(WPARAM wParam, LPARAM lParam)
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
    پیام_3 بعدی_پیام;
    DWORD پیام_زمان = Get_پیام_زمان();
    إذا (Peek_پیام(&بعدی_پیام, عدم, 0, 0, PM_NOREMOVE)) {
        إذا (بعدی_پیام.پیام == WM_KEYDOWN ||
            بعدی_پیام.پیام == WM_SYSKEYDOWN) {
            إذا (بعدی_پیام.wParam == VK_MENU && (بعدی_پیام.lParam & 0x01000000) && بعدی_پیام.زمان == پیام_زمان) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                أرجع true;
            }
        }
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع false;
}

ساكن bool Dispatch_Modal_Loop_پیام_Hook(HWND *hwnd, UINT *پیام_2, WPARAM *wParam, LPARAM *lParam)
{
    پیام_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.پیام = *پیام_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    إذا (g_Windows_پیام_Hook(g_Windows_پیام_Hook_داده, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *پیام_2 = dummy.پیام;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        أرجع true;
    }
    أرجع false;
}

LRESULT CALLBACK WIN_پنجره_Proc(HWND hwnd, UINT پیام_2, WPARAM wParam, LPARAM lParam)
{
    SDL_پنجره_داده *داده;
    LRESULT return_کد = -1;

    // Get the window data for the window
    داده = WIN_Get_پنجره_داده_From_HWND(hwnd);
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!داده) {
        // Fallback
        داده = (SDL_پنجره_داده *)GetProp(hwnd, متن_2("SDL_WindowData"));
    }
#پایان_اگر
    إذا (!داده) {
        أرجع Call_پنجره_Proc(Def_پنجره_Proc, hwnd, پیام_2, wParam, lParam);
    }

#اگر_تعریف_شده WMMSG_DEBUG
    {
        حرف پیام[1024];
        إذا (پیام_2 > MAX_WMMSG) {
            SDL_snprintf(پیام, حجم(پیام), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, پیام_2, wParam, lParam);
        } وإلا {
            SDL_snprintf(پیام, حجم(پیام), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[پیام_2], wParam, lParam);
        }
        OutputDebugStringA(پیام);
    }
#پایان_اگر // WMMSG_DEBUG


    إذا (g_Windows_پیام_Hook && داده->درون_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        إذا (!Dispatch_Modal_Loop_پیام_Hook(&hwnd, &پیام_2, &wParam, &lParam)) {
            أرجع 0;
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (WIN_HandleIMEMessage(hwnd, پیام_2, wParam, &lParam, داده->videodata)) {
        أرجع 0;
    }
#پایان_اگر

    بدل (پیام_2) {

    حالة WM_SHOWWINDOW:
    {
        إذا (wParam) {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
        } وإلا {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_HIDDEN, 0, 0);
        }
    } اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالة WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        داده->postpone_clipcursor = true;
        داده->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        نقطه_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(داده->پنجره, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        إذا (داده->پنجره->flags & SDL_پنجره_BORDERLESS) {
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
        إذا (داده->پنجره->flags & SDL_پنجره_BORDERLESS) {
            return_کد = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD پیام_Pos = Get_پیام_Pos();
        نقطه_2 pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(داده->پنجره, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        إذا (SDL_پنجره_IS_POPUP(داده->پنجره)) {
            أرجع MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_پنجره *والد = داده->پنجره->والد;
        طالما (والد) {
            إذا ((والد->flags & SDL_پنجره_درون_داد_FOCUS) &&
                (والد->flags & SDL_پنجره_MOUSE_RELATIVE_نما)) {
                أرجع MA_NOACTIVATE;
            }
            والد = والد->والد;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیام_Pos = Get_پیام_Pos();
        نقطه_2 pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(داده->پنجره, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیام_Pos = Get_پیام_Pos();
        نقطه_2 pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(داده->پنجره, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_گر_درون_داد_TYPE اشاره_گر_type = PT_اشاره_گر;
        إذا (!داده->videodata->Get_اشاره_گر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!داده->videodata->Get_اشاره_گر_Type(pointerid, &اشاره_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشاره_گر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle(hpointer);
        إذا (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, داده->پنجره, true, true);
        } وإلا {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_فاصله | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.رقم_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_جمع_کن_Pen_Device(WIN_GetEventTimestamp(), عدم, داده->پنجره, &info, hpointer, true);
        }
        return_کد = 0;
    } اكسر;

    حالة WM_POINTERCAPTURECHANGED:
    حالة WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_گر_درون_داد_TYPE اشاره_گر_type = PT_اشاره_گر;
        إذا (!داده->videodata->Get_اشاره_گر_Type) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!داده->videodata->Get_اشاره_گر_Type(pointerid, &اشاره_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا (اشاره_گر_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle(hpointer);
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        إذا ((پیام_2 == WM_POINTERCAPTURECHANGED) || !IS_اشاره_گر_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, داده->پنجره, false, false);
        }
        return_کد = 0;
    } اكسر;

    حالة WM_POINTERDOWN:
    حالة WM_POINTERUP:
    حالة WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشاره_گر_درون_داد_TYPE اشاره_گر_type = PT_اشاره_گر;
        إذا (!داده->videodata->Get_اشاره_گر_Type || !داده->videodata->Get_اشاره_گر_Type(pointerid, &اشاره_گر_type)) {
            اكسر;  // oh well.
        } وإلا إذا ((پیام_2 == WM_POINTERUPDATE) && (اشاره_گر_type == PT_MOUSE)) {
            داده->آخرین_اشاره_گر_update = lParam;
            return_کد = 0;
            اكسر;
        } وإلا إذا (اشاره_گر_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle(hpointer);
        اشاره_گر_PEN_INFO pen_info;
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } وإلا إذا (!داده->videodata->Get_اشاره_گر_Pen_Info || !داده->videodata->Get_اشاره_گر_Pen_Info(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_پنجره *پنجره = داده->پنجره;

        ثابت bool istouching = IS_اشاره_گر_INCONTACT_WPARAM(wParam) && IS_اشاره_گر_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        إذا (!istouching) {
            SDL_SendPenTouch(timestamp, pen, پنجره, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت اشاره_گر_INFO *اشاره_گر_info = &pen_info.اشاره_گر_Info;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        إذا (!داده->videodata->Get_اشاره_گر_Device_Rects || !داده->videodata->Get_اشاره_گر_Device_Rects(اشاره_گر_info->منبع_Device, &tablet_bounds, &tablet_mapping)) {
            نقطه_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_مقصد_Client(داده->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } وإلا {
            صحيح ix, iy;
            SDL_Get_پنجره_Position(پنجره, &ix, &iy);
            ثابت SDL_FPoint پنجره_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = اشاره_گر_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.راست );
            ثابت عائم facY = اشاره_گر_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.راست  - tablet_mapping.چپ;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.بالاترین;

            fx = (tablet_mapping.چپ + (facX * w)) - پنجره_pos.x;
            fy = (tablet_mapping.بالاترین  + (facY * h)) - پنجره_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, پنجره, fx, fy);
        SDL_SendPenButton(timestamp, pen, پنجره, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, پنجره, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        إذا (pen_info.pen_ماسک & PEN_ماسک_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, پنجره, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, پنجره, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, پنجره, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        إذا (pen_info.pen_ماسک & PEN_ماسک_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, پنجره, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        إذا (istouching) {
            SDL_SendPenTouch(timestamp, pen, پنجره, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_کد = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_پنجره *پنجره = داده->پنجره;

        إذا (پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
            bool wish_clip_cursor = (
                پنجره->flags & (SDL_پنجره_MOUSE_RELATIVE_نما | SDL_پنجره_MOUSE_GRABBED) ||
                (پنجره->mouse_rect.w > 0 && پنجره->mouse_rect.h > 0)
            );
            إذا (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                داده->clipcursor_queued = true;
            }
        }

        إذا (!داده->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_اندازه = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = داده->hwnd;

            إذا (TrackMouseEvent(&trackMouseEvent)) {
                داده->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), داده);
        }

        إذا (!داده->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            إذا (Get_Mouse_پیام_منبع((ULONG)Get_پیام_Extra_Info()) == SDL_MOUSE_EVENT_منبع_MOUSE &&
                lParam != داده->آخرین_اشاره_گر_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)GET_X_LPARAM(lParam), (عائم)GET_Y_LPARAM(lParam));
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
        إذا (!داده->videodata->raw_mouse_enabled) {
            إذا (Get_Mouse_پیام_منبع((ULONG)Get_پیام_Extra_Info()) == SDL_MOUSE_EVENT_منبع_MOUSE &&
                lParam != داده->آخرین_اشاره_گر_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, داده, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#إذا 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_درون_داد:
    {
        HRAWINPUT h_Raw_درون_داد = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT اندازه = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        إذا (داده->پنجره != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        Get_Raw_درون_داد_داده(h_Raw_درون_داد, RID_درون_داد, &inp, &اندازه, حجم(RAWINPUTHEADER));
        إذا (inp.سرآیند.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_درون_داد(WIN_GetEventTimestamp(), داده, inp.سرآیند.hDevice, &inp.داده.mouse);
        } وإلا إذا (inp.سرآیند.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_درون_داد(WIN_GetEventTimestamp(), داده, inp.سرآیند.hDevice, &inp.داده.keyboard);
        }
    } اكسر;
#پایان_اگر

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        إذا (!داده->videodata->raw_mouse_enabled) {
            کوتاه amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            إذا (پیام_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), داده->پنجره, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_نرمال);
            } وإلا {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), داده->پنجره, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_نرمال);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        إذا (!(داده->پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
            إذا (SDL_GetMouseFocus() == داده->پنجره && !SDL_GetMouse()->relative_نما && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_پیام_Pos();
                نقطه_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_مقصد_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                إذا (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), داده->پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } وإلا {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    إذا (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), داده->پنجره, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } وإلا { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), داده->پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            إذا (!SDL_GetMouse()->relative_نما) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_مجموعه_Mouse_Focus(عدم);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        داده->mouse_tracked = false;

        return_کد = 0;
        اكسر;
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
    {
        إذا (Skip_Alt_Gr_چپ_Control(wParam, lParam)) {
            return_کد = 0;
            اكسر;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode کد = Windows_پیمایش_کد_مقصد_SDLScan_کد(lParam, wParam, &rawcode, &virtual_کلید);

        // Detect relevant keyboard shortcuts
        إذا (کد == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            إذا (Should_Generate_پنجره_Close_On_Alt_F4()) {
                SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
            }
        }

        إذا (virtual_کلید || !داده->videodata->raw_keyboard_enabled || داده->پنجره->متن_درون_داد_فعال) {
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کد, true);
        }
    }

        return_کد = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        إذا (Skip_Alt_Gr_چپ_Control(wParam, lParam)) {
            return_کد = 0;
            اكسر;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode کد = Windows_پیمایش_کد_مقصد_SDLScan_کد(lParam, wParam, &rawcode, &virtual_کلید);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        إذا (virtual_کلید || !داده->videodata->raw_keyboard_enabled || داده->پنجره->متن_درون_داد_فعال) {
            إذا (کد == SDL_SCANCODE_PRINTSCREEN && !keyboardState[کد]) {
                SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کد, true);
            }
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, کد, false);
        }
    }
        return_کد = 0;
        اكسر;

    حالة WM_UNICHAR:
        إذا (wParam == UNICODE_NOCHAR) {
            return_کد = 1;
        } وإلا {
            إذا (SDL_متن_درون_داد_فعال(داده->پنجره)) {
                حرف متن[5];
                حرف *انتها = SDL_UCS4_مقصد_UTF8((Uint32)wParam, متن);
                *انتها = '\0';
                SDL_Send_Keyboard_متن(متن);
            }
            return_کد = 0;
        }
        اكسر;

    حالة WM_CHAR:
        إذا (SDL_متن_درون_داد_فعال(داده->پنجره)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            إذا (IS_بالا_SURROGATE(wParam)) {
                داده->بالا_surrogate = (WCHAR)wParam;
            } وإلا {
                WCHAR utf16[3];

                utf16[0] = داده->بالا_surrogate ? داده->بالا_surrogate : (WCHAR)wParam;
                utf16[1] = داده->بالا_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح نتیجه = WIN_Wide_Char_مقصد_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                إذا (نتیجه > 0) {
                    SDL_Send_Keyboard_متن(utf8);
                }
                داده->بالا_surrogate = L'\0';
            }
        } وإلا {
            داده->بالا_surrogate = L'\0';
        }

        return_کد = 0;
        اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#اگر_تعریف_شده WM_INPUTLANGCHANGE
    حالة WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_کد = 1;
        اكسر;
#پایان_اگر // WM_INPUTLANGCHANGE

    حالة WM_NCLBUTTONDOWN:
    {
        داده->درون_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        إذا (Send_پیام(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            نقطه_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_مقصد_Client(hwnd, &cursorPos);
            Post_پیام(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } اكسر;

    حالة WM_CAPTURECHANGED:
    {
        داده->درون_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), داده);
    } اكسر;

#اگر_تعریف_شده WM_GETMINMAXINFO
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
        إذا (داده->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        Get_پنجره_Rect(hwnd, &اندازه);
        x = اندازه.چپ;
        y = اندازه.بالاترین;

        // Calculate current size of our window
        SDL_Get_پنجره_اندازه(داده->پنجره, &w, &h);
        SDL_Get_پنجره_Minimum_اندازه(داده->پنجره, &min_w, &min_h);
        SDL_Get_پنجره_بیشینه_اندازه(داده->پنجره, &max_w, &max_h);

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

        إذا (!(SDL_Get_پنجره_Flags(داده->پنجره) & SDL_پنجره_BORDERLESS) && !SDL_پنجره_IS_POPUP(داده->پنجره)) {
            اندازه.بالاترین = 0;
            اندازه.چپ = 0;
            اندازه.bottom = h;
            اندازه.راست = w;
            WIN_Adjust_پنجره_Rect_For_HWND(hwnd, &اندازه, 0);
            w = اندازه.راست - اندازه.چپ;
            h = اندازه.bottom - اندازه.بالاترین;
#اگر_تعریف_شده HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#پایان_اگر
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        إذا (SDL_Get_پنجره_Flags(داده->پنجره) & SDL_پنجره_RESIZABLE) {
            إذا (SDL_Get_پنجره_Flags(داده->پنجره) & SDL_پنجره_BORDERLESS) {
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
        return_کد = 0;
        اكسر;
#پایان_اگر // WM_GETMINMAXINFO

    حالة WM_WINDOWPOSCHANGING:

        إذا (داده->expected_resize) {
            return_کد = 0;
        } وإلا إذا (داده->درون_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            إذا (داده->آخرین_modal_عرض == windowpos->cx && داده->آخرین_modal_ارتفاع == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            داده->آخرین_modal_عرض = windowpos->cx;
            داده->آخرین_modal_ارتفاع = windowpos->cy;

            return_کد = 0;
        }
        اكسر;

    حالة WM_WINDOWPOSCHANGED:
    {
        SDL_پنجره *win;
        ثابت SDL_DisplayID original_displayID = داده->پنجره->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحيح x, y;
        صحيح w, h;

        إذا (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        إذا (iconic) {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
        } وإلا إذا (zoomed) {
            إذا (داده->پنجره->flags & SDL_پنجره_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
            }
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MAXIMIZED, 0, 0);
            داده->force_ws_maximizebox = true;
        } وإلا إذا (داده->پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED)) {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            إذا (!(داده->پنجره->flags & SDL_پنجره_FULLSCREEN)) {
                داده->force_ws_maximizebox = false;
                WIN_مجموعه_پنجره_Resizable(SDL_GetVideoDevice(), داده->پنجره, !!(داده->پنجره->flags & SDL_پنجره_RESIZABLE));
            }
        }

        إذا (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        إذا (iconic) {
            اكسر;
        }

        إذا (داده->initializing) {
            اكسر;
        }

        إذا (!داده->disable_move_اندازه_events) {
            إذا (GetClientRect(hwnd, &rect) && WIN_پنجره_Rect_Valid(&rect)) {
                Client_مقصد_Screen(hwnd, (LPPOINT) &rect);
                Client_مقصد_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.چپ;
                y = rect.بالاترین;

                SDL_Global_مقصد_Relative_For_پنجره(داده->پنجره, x, y, &x, &y);
                SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            إذا (GetClientRect(hwnd, &rect) && WIN_پنجره_Rect_Valid(&rect)) {
                w = rect.راست;
                h = rect.bottom;

                SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(داده->پنجره);

        // Update the window display position
        إذا (داده->پنجره->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_پنجره_ICCProfile(داده->پنجره, true);
        }

        // Update the position of any child windows
        لكل (win = داده->پنجره->اولی_فرزند; win; win = win->بعدی_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_پنجره_IS_POPUP(win) && !(win->flags & SDL_پنجره_HIDDEN)) {
                WIN_مجموعه_پنجره_Position_داخلی(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        إذا (g_Windows_پیام_Hook) {
            إذا (!Dispatch_Modal_Loop_پیام_Hook(&hwnd, &پیام_2, &wParam, &lParam)) {
                أرجع 0;
            }
        }

        ++داده->درون_modal_loop;
        إذا (داده->درون_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_پنجره_Rect(داده->hwnd, &rect);
            داده->آخرین_modal_عرض = rect.راست - rect.چپ;
            داده->آخرین_modal_ارتفاع = rect.bottom - rect.بالاترین;

            داده->initial_اندازه_rect.چپ = داده->پنجره->x;
            داده->initial_اندازه_rect.راست = داده->پنجره->x + داده->پنجره->w;
            داده->initial_اندازه_rect.بالاترین = داده->پنجره->y;
            داده->initial_اندازه_rect.bottom = داده->پنجره->y + داده->پنجره->h;

            مجموعه_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        إذا (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_پنجره_زنده_Resize_Update(داده->پنجره);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#إذا 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            إذا (داده->videodata->DwmFlush) {
                داده->videodata->DwmFlush();
            }
#پایان_اگر
#پایان_اگر
            أرجع 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --داده->درون_modal_loop;
        إذا (داده->درون_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } اكسر;

    حالة WM_SIZING:
        {
            WPARAM یال = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool قفل_aspect_نسبت = (داده->پنجره->max_aspect == داده->پنجره->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            عائم new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            إذا (داده->پنجره->min_aspect <= 0 && داده->پنجره->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            مجموعه_Rect_خالی(&rc);
            إذا (!Adjust_پنجره_Rect_Ex(&rc, Get_پنجره_Style(hwnd), GetMenu(hwnd) != عدم, Get_پنجره_Ex_Style(hwnd))) {
                اكسر;
            }

            clientDragRect.چپ -= rc.چپ;
            clientDragRect.بالاترین -= rc.بالاترین;
            clientDragRect.راست -= rc.راست;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.راست - clientDragRect.چپ;
            h = clientDragRect.bottom - clientDragRect.بالاترین;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            إذا (قفل_aspect_نسبت) {
                بدل (یال) {
                حالة WMSZ_چپ:
                حالة WMSZ_راست:
                    h = (صحيح)SDL_roundf(w / داده->پنجره->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * داده->پنجره->max_aspect);
                    اكسر;
                }
            } وإلا {
                بدل (یال) {
                حالة WMSZ_چپ:
                حالة WMSZ_راست:
                    إذا (داده->پنجره->max_aspect > 0.0f && new_aspect > داده->پنجره->max_aspect) {
                        w = (صحيح)SDL_roundf(h * داده->پنجره->max_aspect);
                    } وإلا إذا (داده->پنجره->min_aspect > 0.0f && new_aspect < داده->پنجره->min_aspect) {
                        w = (صحيح)SDL_roundf(h * داده->پنجره->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_بالاترین:
                حالة WMSZ_BOTTOM:
                    إذا (داده->پنجره->min_aspect > 0.0f && new_aspect < داده->پنجره->min_aspect) {
                        h = (صحيح)SDL_roundf(w / داده->پنجره->min_aspect);
                    } وإلا إذا (داده->پنجره->max_aspect > 0.0f && new_aspect > داده->پنجره->max_aspect) {
                        h = (صحيح)SDL_roundf(w / داده->پنجره->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    إذا (داده->پنجره->max_aspect > 0.0f && new_aspect > داده->پنجره->max_aspect) {
                        w = (صحيح)SDL_roundf(h * داده->پنجره->max_aspect);
                    } وإلا إذا (داده->پنجره->min_aspect > 0.0f && new_aspect < داده->پنجره->min_aspect) {
                        h = (صحيح)SDL_roundf(w / داده->پنجره->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (یال) {
            حالة WMSZ_چپ:
                clientDragRect.چپ = clientDragRect.راست - w;
                إذا (قفل_aspect_نسبت) {
                    clientDragRect.بالاترین = (داده->initial_اندازه_rect.bottom + داده->initial_اندازه_rect.بالاترین - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.چپ = clientDragRect.راست - w;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                اكسر;
            حالة WMSZ_راست:
                clientDragRect.راست = w + clientDragRect.چپ;
                إذا (قفل_aspect_نسبت) {
                    clientDragRect.بالاترین = (داده->initial_اندازه_rect.bottom + داده->initial_اندازه_rect.بالاترین - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_بالاترین:
                إذا (قفل_aspect_نسبت) {
                    clientDragRect.چپ = (داده->initial_اندازه_rect.راست + داده->initial_اندازه_rect.چپ - w) / 2;
                }
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.چپ = clientDragRect.راست - w;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                إذا (قفل_aspect_نسبت) {
                    clientDragRect.چپ = (داده->initial_اندازه_rect.راست + داده->initial_اندازه_rect.چپ - w) / 2;
                }
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                اكسر;
            }

            // convert the client rect to a window rect
            إذا (!Adjust_پنجره_Rect_Ex(&clientDragRect, Get_پنجره_Style(hwnd), GetMenu(hwnd) != عدم, Get_پنجره_Ex_Style(hwnd))) {
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
            مجموعه_Cursor(SDL_cursor);
            return_کد = TRUE;
        } وإلا إذا (!g_پنجره_قاب_Usable_While_Cursor_Hidden && !SDL_cursor) {
            مجموعه_Cursor(عدم);
            return_کد = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        إذا (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = Get_پنجره_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            إذا (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                انتها_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, عدم);
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
        }
    }
        return_کد = 0;
        اكسر;

        // We'll do our own drawing, prevent flicker
    حالة WM_ERASEBKGND:
        إذا (Should_Clear_پنجره_On_Erase_Background(داده)) {
            RECT client_rect;
            HBRUSH brush;
            داده->videodata->cleared = true;
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
#پایان_اگر // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
    }
        return_کد = 0;
        اكسر;

    حالة WM_TOUCH:
        إذا (داده->videodata->Get_Touch_درون_داد_Info && داده->videodata->Close_Touch_درون_داد_Handle) {
            UINT i, رقم_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, رقم_inputs, &isstack);
            إذا (inputs && داده->videodata->Get_Touch_درون_داد_Info((HTOUCHINPUT)lParam, رقم_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                إذا (!GetClientRect(hwnd, &rect) || !WIN_پنجره_Rect_Valid(&rect)) {
                    إذا (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                Client_مقصد_Screen(hwnd, (LPPOINT)&rect);
                Client_مقصد_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.بالاترین *= 100;
                rect.چپ *= 100;
                rect.bottom *= 100;
                rect.راست *= 100;

                لكل (i = 0; i < رقم_inputs; ++i) {
                    PTOUCHINPUT درون_داد = &inputs[i];
                    ثابت صحيح w = (rect.راست - rect.چپ);
                    ثابت صحيح h = (rect.bottom - rect.بالاترین);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)درون_داد->h_منبع);
                    ثابت SDL_FingerID fingerId = (درون_داد->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    إذا (SDL_جمع_کن_Touch(touchId, SDL_TOUCH_DEVICE_مستقیم, (درون_داد->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    إذا (w <= 1) {
                        x = 0.5f;
                    } وإلا {
                        x = (عائم)(درون_داد->x - rect.چپ) / (w - 1);
                    }
                    إذا (h <= 1) {
                        y = 0.5f;
                    } وإلا {
                        y = (عائم)(درون_داد->y - rect.بالاترین) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    إذا (درون_داد->dwFlags & TOUCHEVENTF_پایین) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, داده->پنجره, SDL_EVENT_FINGER_پایین, x, y, 1.0f);
                    }
                    إذا (درون_داد->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, داده->پنجره, x, y, 1.0f);
                    }
                    إذا (درون_داد->dwFlags & TOUCHEVENTF_به_بالا) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, داده->پنجره, SDL_EVENT_FINGER_به_بالا, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            داده->videodata->Close_Touch_درون_داد_Handle((HTOUCHINPUT)lParam);
            أرجع 0;
        }
        اكسر;

#اگر_تعریف_شده HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        أرجع TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#پایان_اگر // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT شمار = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < شمار; ++i) {
            UINT اندازه = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR میانگیر_2 = (LPTSTR)SDL_malloc(حجم(TCHAR) * اندازه);
            إذا (میانگیر_2) {
                إذا (DragQueryFile(drop, i, میانگیر_2, اندازه)) {
                    حرف *file = WIN_String_مقصد_UTF8(میانگیر_2);
                    SDL_SendDropFile(داده->پنجره, عدم, file);
                    SDL_free(file);
                }
                SDL_free(میانگیر_2);
            }
        }
        SDL_SendDropComplete(داده->پنجره);
        Drag_پایان(drop);
        أرجع 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_پنجره_Flags پنجره_flags = داده->پنجره->flags;
        إذا (wParam == TRUE && (پنجره_flags & SDL_پنجره_BORDERLESS) && !(پنجره_flags & SDL_پنجره_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            إذا (Get_پنجره_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_پنجره(hwnd, MONITOR_DEFAULTTONULL);
                إذا (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت نقطه_2 pt = { داده->پنجره->windowed.x, داده->پنجره->windowed.y };
                    hMonitor = Monitor_From_نقطه(pt, MONITOR_DEFAULTTONEAREST);
                }
                إذا (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_اندازه = حجم(info);
                    إذا (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وإلا إذا (!(پنجره_flags & SDL_پنجره_RESIZABLE) && !داده->force_ws_maximizebox) {
                صحيح w, h;
                إذا (داده->پنجره->آخرین_اندازه_pending) {
                    w = داده->پنجره->pending.w;
                    h = داده->پنجره->pending.h;
                } وإلا {
                    w = داده->پنجره->floating.w;
                    h = داده->پنجره->floating.h;
                }
                params->rgrc[0].راست = params->rgrc[0].چپ + w;
                params->rgrc[0].bottom = params->rgrc[0].بالاترین + h;
            }
            أرجع 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_پنجره *پنجره = داده->پنجره;

        إذا (پنجره->flags & SDL_پنجره_TOOLTIP) {
            أرجع HTTRANSPARENT;
        }

        إذا (پنجره->اصابت_test) {
            نقطه_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            إذا (Screen_مقصد_Client(hwnd, &winpoint)) {
                SDL_نقطه نقطه;
                SDL_اصابت_Test_نتیجه rc;
                نقطه.x = winpoint.x;
                نقطه.y = winpoint.y;
                rc = پنجره->اصابت_test(پنجره, &نقطه, پنجره->اصابت_test_داده);
                بدل (rc) {
#تعریف_کن POST_اصابت_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_اصابت_TEST, 0, 0); \
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
                        SDL_مجموعه_Mouse_Focus(پنجره);
                        أرجع HTCLIENT;
                    }

                    POST_اصابت_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_اصابت_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_بالاترین:
                    POST_اصابت_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_اصابت_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_راست:
                    POST_اصابت_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_اصابت_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_اصابت_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_اصابت_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_چپ:
                    POST_اصابت_TEST(HTLEFT);
#لغو_تعریف POST_اصابت_TEST
                حالة SDL_HITTEST_نرمال:
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
        إذا (داده->videodata->Get_Dpi_For_پنجره && داده->videodata->Adjust_پنجره_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحيح بعدی_DPI = (صحيح)wParam;
            ثابت صحيح prevDPI = (صحيح)داده->videodata->Get_Dpi_For_پنجره(hwnd);
            اندازه_3 *اندازه_درون_بیرون = (اندازه_3 *)lParam;

            صحيح قاب_w, قاب_h;
            صحيح query_client_w_win, query_client_h_win;

#اگر_تعریف_شده HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, بعدی_DPI, اندازه_درون_بیرون->cx, اندازه_درون_بیرون->cy);
#پایان_اگر

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                إذا (!(داده->پنجره->flags & SDL_پنجره_BORDERLESS) && !SDL_پنجره_IS_POPUP(داده->پنجره)) {
                    WIN_Adjust_پنجره_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                قاب_w = -rect.چپ + rect.راست;
                قاب_h = -rect.بالاترین + rect.bottom;

                query_client_w_win = اندازه_درون_بیرون->cx - قاب_w;
                query_client_h_win = اندازه_درون_بیرون->cy - قاب_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.راست = query_client_w_win;
                rect.bottom = query_client_h_win;

                إذا (!(داده->پنجره->flags & SDL_پنجره_BORDERLESS) && !SDL_پنجره_IS_POPUP(داده->پنجره)) {
                    WIN_Adjust_پنجره_Rect_For_HWND(hwnd, &rect, بعدی_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                اندازه_درون_بیرون->cx = rect.راست - rect.چپ;
                اندازه_درون_بیرون->cy = rect.bottom - rect.بالاترین;
            }

#اگر_تعریف_شده HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", اندازه_درون_بیرون->cx, اندازه_درون_بیرون->cy);
#پایان_اگر
            أرجع TRUE;
        }
        اكسر;

    حالة WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحيح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحيح w, h;

#اگر_تعریف_شده HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->چپ, suggestedRect->بالاترین, suggestedRect->راست - suggestedRect->چپ, suggestedRect->bottom - suggestedRect->بالاترین);
#پایان_اگر

            إذا (داده->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#اگر_تعریف_شده HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#پایان_اگر
                أرجع 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.راست = داده->پنجره->w;
                rect.bottom = داده->پنجره->h;

                إذا (!(داده->پنجره->flags & SDL_پنجره_BORDERLESS)) {
                    WIN_Adjust_پنجره_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.راست - rect.چپ;
                h = rect.bottom - rect.بالاترین;
            }

#اگر_تعریف_شده HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    داده->پنجره->w, داده->پنجره->h,
                    suggestedRect->چپ, suggestedRect->بالاترین, w, h);
#پایان_اگر

            داده->expected_resize = true;
            مجموعه_پنجره_Pos(hwnd,
                         عدم,
                         suggestedRect->چپ,
                         suggestedRect->بالاترین,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            داده->expected_resize = false;
            أرجع 0;
        }

    حالة WM_SETTINGCHANGE:
        إذا (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_مجموعه_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_نما_For_HWND(hwnd);
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

        إذا (GetClientRect(hwnd, &rect) && WIN_پنجره_Rect_Valid(&rect)) {
            w = rect.راست;
            h = rect.bottom;
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESIZED, w, h);
        }
    } اكسر;
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (پیام_2 && پیام_2 == داده->videodata->WM_TASKBAR_BUTTON_CREATED) {
        داده->taskbar_button_created = true;
        WIN_Apply_پنجره_پیشرفت(SDL_GetVideoDevice(), داده->پنجره);
    }
#پایان_اگر

    // If there's a window proc, assume it's going to handle messages
    إذا (داده->wndproc) {
        أرجع Call_پنجره_Proc(داده->wndproc, hwnd, پیام_2, wParam, lParam);
    } وإلا إذا (return_کد >= 0) {
        أرجع return_کد;
    } وإلا {
        أرجع Call_پنجره_Proc(Def_پنجره_Proc, hwnd, پیام_2, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    إذا (g_Windows_Enable_پیام_Loop) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_مقصد_MS(timeoutNS);
        ret = پیام_Wait_For_مضرب_Objects(0, عدم, FALSE, timeout, QS_ALLINPUT);
        إذا (ret == WAIT_OBJECT_0) {
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#وإلا
        // MsgWaitForMultipleObjects is desktop-only.
        پیام_3 پیام_2;
        BOOL پیام_نتیجه;
        UINT_PTR timer_id = 0;
        إذا (timeoutNS > 0) {
            timer_id = مجموعه_Timer(عدم, 0, (UINT)SDL_NS_مقصد_MS(timeoutNS), عدم);
            پیام_نتیجه = Get_پیام(&پیام_2, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } وإلا إذا (timeoutNS == 0) {
            پیام_نتیجه = Peek_پیام(&پیام_2, عدم, 0, 0, PM_REMOVE);
        } وإلا {
            پیام_نتیجه = Get_پیام(&پیام_2, 0, 0, 0);
        }
        إذا (پیام_نتیجه) {
            إذا (پیام_2.پیام == WM_TIMER && !پیام_2.hwnd && پیام_2.wParam == timer_id) {
                أرجع 0;
            }
            إذا (g_Windows_پیام_Hook) {
                إذا (!g_Windows_پیام_Hook(g_Windows_پیام_Hook_داده, &پیام_2)) {
                    أرجع 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیام(&پیام_2);
            Dispatch_پیام(&پیام_2);
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وإلا {
        // Fail the wait so the caller falls back to polling
        أرجع -1;
    }
}

فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Post_پیام(داده->hwnd, داده->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    پیام_3 پیام_2;

    إذا (g_Windows_Enable_پیام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پیام(&پیام_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_مجموعه_پیام_Tick(پیام_2.زمان);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیام(&پیام_2);
            Dispatch_پیام(&پیام_2);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    پیام_3 پیام_2;
#اگر_تعریف_شده _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#رهنمود warning(افزودن)
#رهنمود warning(disable : 28159)
#پایان_اگر
    DWORD انتها_ticks = Get_Tick_شمار() + 1;
#اگر_تعریف_شده _MSC_VER
#رهنمود warning(برداشت)
#پایان_اگر
    صحيح new_messages = 0;

    إذا (_this->داخلی->gameinput_context) {
        WIN_Update_Game_درون_داد(_this);
    }

    إذا (g_Windows_Enable_پیام_Loop) {
        SDL_processing_messages = true;

        طالما (Peek_پیام(&پیام_2, عدم, 0, 0, PM_REMOVE)) {
            إذا (g_Windows_پیام_Hook) {
                إذا (!g_Windows_پیام_Hook(g_Windows_پیام_Hook_داده, &پیام_2)) {
                    استمر;
                }
            }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            إذا (پیام_2.پیام == WM_MOUSEMOVE && SDL_آخرین_warp_زمان) {
                إذا (!SDL_TICKS_PASSED(پیام_2.زمان, (SDL_آخرین_warp_زمان + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_آخرین_warp_زمان = 0;
            }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_مجموعه_پیام_Tick(پیام_2.زمان);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیام(&پیام_2);
            Dispatch_پیام(&پیام_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            إذا (SDL_TICKS_PASSED(پیام_2.زمان, انتها_ticks)) {
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
    SDL_پنجره *focus_پنجره = SDL_GetKeyboardFocus();
    إذا (!focus_پنجره || !(focus_پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED)) {
        إذا (keystate[SDL_SCANCODE_LGUI] && !(Get_کلید_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        إذا (keystate[SDL_SCANCODE_RGUI] && !(Get_کلید_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    إذا (_this) {
        SDL_پنجره *پنجره = _this->windows;
        طالما (پنجره) {
            bool refresh_clipcursor = false;
            SDL_پنجره_داده *داده = پنجره->داخلی;
            إذا (داده) {
                refresh_clipcursor = داده->clipcursor_queued;
                داده->clipcursor_queued = false;    // Must be cleared unconditionally.
                داده->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
                WIN_UpdateClipCursor(پنجره);
            }
            پنجره = پنجره->بعدی;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_پنجره = SDL_GetKeyboardFocus();
    إذا (focus_پنجره && (focus_پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
        SDL_پنجره_داده *داده = focus_پنجره->داخلی;

        إذا (!داده->mouse_tracked) {
            نقطه_2 cursorPos;

            إذا (GetCursorPos(&cursorPos) && Screen_مقصد_Client(داده->hwnd, &cursorPos)) {
                bool جابجا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), داده->پنجره, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), داده->پنجره, mouseID,
                                    !جابجا_Buttons ? SDL_BUTTON_چپ : SDL_BUTTON_راست,
                                    (Get_Async_کلید_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), داده->پنجره, mouseID,
                                    !جابجا_Buttons ? SDL_BUTTON_راست : SDL_BUTTON_چپ,
                                    (Get_Async_کلید_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), داده->پنجره, mouseID,
                                    SDL_BUTTON_میانه,
                                    (Get_Async_کلید_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), داده->پنجره, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_کلید_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), داده->پنجره, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_کلید_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شده SDL_PLATFORM_GDK
    GDK_Dispatch_Task_صف();
#پایان_اگر
}

ساكن صحيح app_registered = 0;
LPTSTR SDL_Appname = عدم;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = عدم;

ساكن فراغ WIN_Clean_ثبات_App(WNDCLASSEX wcex)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    إذا (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#پایان_اگر
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
    wcex->hIcon = بارگیری_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    أرجع FALSE;
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_ثبات_App(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#پایان_اگر

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
#پایان_اگر
    }
    SDL_Appname = WIN_UTF8_مقصد_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(عدم);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_اندازه = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_پنجره_Proc;
    wcex.hInstance = SDL_Instance;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    إذا (hint && *hint) {
        wcex.hIcon = بارگیری_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        إذا (hint && *hint) {
            wcex.hIconSm = بارگیری_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وإلا {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_نامها(SDL_Instance, RT_گروه_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    إذا (!ثبات_Class_Ex(&wcex)) {
        WIN_Clean_ثبات_App(wcex);
        أرجع SDL_مجموعه_Error("Couldn't register application class");
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
#پایان_اگر
        WIN_Clean_ثبات_App(wcex);
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS
