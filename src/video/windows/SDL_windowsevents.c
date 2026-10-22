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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

#شامل "SDL_windowsvideo.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_touch_c.h"
#شامل "../../events/scancodes_windows.h"
#شامل "../../main/SDL_main_callbacks.h"
#شامل "../../core/windows/SDL_hid.h"

// Dropfile support
#شامل <shellapi.h>

// Device names
#شامل <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#شامل <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#اگر_تعریف_شدہ HAVE_TPCSHRD_H
#شامل <tpcshrd.h>
#اگر_ختم // HAVE_TPCSHRD_H

#اگر 0
#تعریف_کرو WMMSG_DEBUG
#اگر_ختم
#اگر_تعریف_شدہ WMMSG_DEBUG
#شامل <stdio.h>
#شامل "wmmsg.h"
#اگر_ختم

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#شامل <shobjidl.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_PLATFORM_GDK
#شامل "../../core/gdk/SDL_gdk.h"
#اگر_ختم

// #define HIGHDPI_DEBUG

// Undocumented window messages
#اگر_غیر_تعریف_شدہ WM_NCUAHDRAWCAPTION
#تعریف_کرو WM_NCUAHDRAWCAPTION 0xAE
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_NCUAHDRAWFRAME
#تعریف_کرو WM_NCUAHDRAWFRAME 0xAF
#اگر_ختم

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#اگر_غیر_تعریف_شدہ WM_XBUTTONDOWN
#تعریف_کرو WM_XBUTTONDOWN 0x020B
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_XBUTTONUP
#تعریف_کرو WM_XBUTTONUP 0x020C
#اگر_ختم
#اگر_غیر_تعریف_شدہ GET_XBUTTON_WPARAM
#تعریف_کرو GET_XBUTTON_WPARAM(w) (HIWORD(w))
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_داخلہ
#تعریف_کرو WM_داخلہ 0x00ff
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_TOUCH
#تعریف_کرو WM_TOUCH 0x0240
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_MOUSEHWHEEL
#تعریف_کرو WM_MOUSEHWHEEL 0x020E
#اگر_ختم
#اگر_غیر_تعریف_شدہ RI_MOUSE_HWHEEL
#تعریف_کرو RI_MOUSE_HWHEEL 0x0800
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERUPDATE
#تعریف_کرو WM_POINTERUPDATE 0x0245
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERDOWN
#تعریف_کرو WM_POINTERDOWN 0x0246
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERUP
#تعریف_کرو WM_POINTERUP 0x0247
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERENTER
#تعریف_کرو WM_POINTERENTER 0x0249
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERLEAVE
#تعریف_کرو WM_POINTERLEAVE 0x024A
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_POINTERCAPTURECHANGED
#تعریف_کرو WM_POINTERCAPTURECHANGED 0x024C
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_UNICHAR
#تعریف_کرو WM_UNICHAR 0x0109
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_DPICHANGED
#تعریف_کرو WM_DPICHANGED 0x02E0
#اگر_ختم
#اگر_غیر_تعریف_شدہ WM_GETDPISCALEDSIZE
#تعریف_کرو WM_GETDPISCALEDSIZE 0x02E4
#اگر_ختم
#اگر_غیر_تعریف_شدہ TOUCHEVENTF_PEN
#تعریف_کرو TOUCHEVENTF_PEN 0x0040
#اگر_ختم

#اگر_غیر_تعریف_شدہ MAPVK_VK_مقصد_VSC_EX
#تعریف_کرو MAPVK_VK_مقصد_VSC_EX 4
#اگر_ختم

#اگر_غیر_تعریف_شدہ WC_ERR_INVALID_CHARS
#تعریف_کرو WC_ERR_INVALID_CHARS 0x00000080
#اگر_ختم

#اگر_غیر_تعریف_شدہ IS_بلند_SURROGATE
#تعریف_کرو IS_بلند_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#اگر_ختم

#اگر_غیر_تعریف_شدہ USER_TIMER_MINIMUM
#تعریف_کرو USER_TIMER_MINIMUM 0x0000000A
#اگر_ختم

// Used to compare Windows message timestamps
#تعریف_کرو SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#اگر_تعریف_شدہ _WIN64
قسمتعریف Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#اگر_ختم

ساکن bool SDL_processing_messages;
ساکن DWORD پیغام_tick;
ساکن Uint64 timestamp_انحراف;

ساکن خالی WIN_سیٹ_پیغام_Tick(DWORD tick)
{
    پیغام_tick = tick;
}

ساکن Uint64 WIN_GetEventTimestamp(خالی)
{
    ثابت Uint64 TIMESTAMP_WRAP_انحراف = SDL_MS_مقصد_NS(0x100000000LL);
    Uint64 timestamp, now;

    اگر (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        واپس 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_مقصد_NS(پیغام_tick);
    timestamp += timestamp_انحراف;
    اگر (!timestamp_انحراف) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_انحراف = (now - timestamp);
        timestamp = now;
    } ورنہ اگر ((Sint64)(now - timestamp - TIMESTAMP_WRAP_انحراف) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_انحراف += TIMESTAMP_WRAP_انحراف;
        timestamp += TIMESTAMP_WRAP_انحراف;
    } ورنہ اگر (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_انحراف -= (timestamp - now);
        timestamp = now;
    }
    واپس timestamp;
}

// A message hook called before TranslateMessage()
ساکن SDL_Windows_پیغام_Hook g_Windows_پیغام_Hook = تہی;
ساکن خالی *g_Windows_پیغام_Hook_ڈیٹا = تہی;

خالی SDL_سیٹ_Windows_پیغام_Hook(SDL_Windows_پیغام_Hook callback, خالی *userdata)
{
    g_Windows_پیغام_Hook = callback;
    g_Windows_پیغام_Hook_ڈیٹا = userdata;
}

ساکن SDL_Scancode Windows_جائزہ_رمز_مقصد_SDLScan_رمز(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_کلید)
{
    SDL_Scancode رمز;
    Uint8 اشاریہ;
    Uint16 کلید_Flags = HIWORD(lParam);
    Uint16 جائزہ_رمز = LOBYTE(کلید_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    جائزہ_رمز &= ~0x80;

    *virtual_کلید = (جائزہ_رمز == 0);

    اگر (جائزہ_رمز != 0) {
        اگر ((کلید_Flags & KF_EXTENDED) == KF_EXTENDED) {
            جائزہ_رمز = MAKEWORD(جائزہ_رمز, 0xe0);
        } ورنہ اگر (جائزہ_رمز == 0x45) {
            // Pause
            جائزہ_رمز = 0xe046;
        }
    } ورنہ {
        Uint16 vk_رمز = LOWORD(wParam);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        جائزہ_رمز = LOWORD(Map_Virtual_کلید(vk_رمز, WIN_IsWindowsXP() ? MAPVK_VK_مقصد_VSC : MAPVK_VK_مقصد_VSC_EX));
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        اگر (جائزہ_رمز == 0xe11d) {
            جائزہ_رمز = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    اشاریہ = LOBYTE(جائزہ_رمز) | (HIBYTE(جائزہ_رمز) ? 0x80 : 0x00);
    رمز = windows_scancode_جدول[اشاریہ];
    *rawcode = جائزہ_رمز;

    واپس رمز;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساکن bool WIN_ShouldIgnoreFocusClick(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    واپس !SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساکن خالی WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_تبادلہ_Buttons, SDL_کھڑکی_ڈیٹا *ڈیٹا, Uint8 button, SDL_MouseID mouseID)
{
    اگر (b_تبادلہ_Buttons) {
        اگر (button == SDL_BUTTON_بایاں) {
            button = SDL_BUTTON_دایاں;
        } ورنہ اگر (button == SDL_BUTTON_دایاں) {
            button = SDL_BUTTON_بایاں;
        }
    }

    اگر (ڈیٹا->focus_click_pending & SDL_BUTTON_نقاب(button)) {
        // Ignore the button click for activation
        اگر (!bwParamMousePressed) {
            ڈیٹا->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
            WIN_UpdateClipCursor(ڈیٹا->کھڑکی);
        }
        واپس;
    }

    اگر (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, ڈیٹا->کھڑکی, mouseID, button, true);
    } ورنہ اگر (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_نقاب(button))) {
        SDL_SendMouseButton(timestamp, ڈیٹا->کھڑکی, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساکن خالی WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_کھڑکی_ڈیٹا *ڈیٹا, SDL_MouseID mouseID)
{
    اگر (wParam != ڈیٹا->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(تہی, تہی);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, ڈیٹا, SDL_BUTTON_بایاں, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, ڈیٹا, SDL_BUTTON_درمیان, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, ڈیٹا, SDL_BUTTON_دایاں, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, ڈیٹا, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, ڈیٹا, SDL_BUTTON_X2, mouseID);

        ڈیٹا->mouse_button_flags = wParam;
    }
}

ساکن خالی WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT کلید_State;
    bool تبادلہ_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(تہی, تہی);
    تبادلہ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    کلید_State = Get_Async_کلید_State(VK_LBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, تبادلہ_Buttons, ڈیٹا, SDL_BUTTON_بایاں, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_RBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, تبادلہ_Buttons, ڈیٹا, SDL_BUTTON_دایاں, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_MBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, تبادلہ_Buttons, ڈیٹا, SDL_BUTTON_درمیان, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON1);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, تبادلہ_Buttons, ڈیٹا, SDL_BUTTON_X1, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON2);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, تبادلہ_Buttons, ڈیٹا, SDL_BUTTON_X2, mouseID);
    }
    ڈیٹا->mouse_button_flags = (WPARAM)-1;
}

ساکن خالی WIN_UpdateFocus(SDL_کھڑکی *کھڑکی, bool expect_focus, LPPOINT pos)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == کھڑکی);
    bool has_focus = (Get_Foreground_کھڑکی() == hwnd);

    اگر (had_focus == has_focus || has_focus != expect_focus) {
        واپس;
    }

    اگر (has_focus) {
        نقطہ_2 cursorPos;

        اگر (WIN_ShouldIgnoreFocusClick(ڈیٹا) && !(کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            bool تبادلہ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            اگر (Get_Async_کلید_State(VK_LBUTTON)) {
                ڈیٹا->focus_click_pending |= !تبادلہ_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            اگر (Get_Async_کلید_State(VK_RBUTTON)) {
                ڈیٹا->focus_click_pending |= !تبادلہ_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            اگر (Get_Async_کلید_State(VK_MBUTTON)) {
                ڈیٹا->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            اگر (Get_Async_کلید_State(VK_XBUTTON1)) {
                ڈیٹا->focus_click_pending |= SDL_BUTTON_X1_نقاب;
            }
            اگر (Get_Async_کلید_State(VK_XBUTTON2)) {
                ڈیٹا->focus_click_pending |= SDL_BUTTON_X2_نقاب;
            }
        }

        SDL_سیٹ_Keyboard_Focus(کھڑکی->keyboard_focus ? کھڑکی->keyboard_focus : کھڑکی);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        اگر (!SDL_GetMouse()->relative_منوال) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_مقصد_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ڈیٹا);
        WIN_UpdateClipCursor(کھڑکی);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(ڈیٹا->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلید_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_عدد, (Get_کلید_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلید_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_کھڑکی_ICCProfile(ڈیٹا->کھڑکی, true);
    } ورنہ {
        ڈیٹا->اندر_کھڑکی_deactivation = true;

        SDL_سیٹ_Keyboard_Focus(تہی);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        اگر (SDL_GetMouse()->relative_منوال) {
            SDL_سیٹ_Mouse_Focus(تہی);
        }
        WIN_Reset_Dead_کلیدیں();

        WIN_Unclip_Cursor_For_کھڑکی(کھڑکی);

        ڈیٹا->اندر_کھڑکی_deactivation = false;
    }
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساکن bool Should_Generate_کھڑکی_Close_On_Alt_F4(خالی)
{
    واپس SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساکن bool Should_Clear_کھڑکی_On_Erase_Background(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    انتخاب (ڈیٹا->hint_erase_background_منوال) {
    حالت SDL_ERASEBACKGROUNDMODE_NEVER:
        واپس false;
    حالت SDL_ERASEBACKGROUNDMODE_INITIAL:
        واپس !ڈیٹا->videodata->cleared;
    حالت SDL_ERASEBACKGROUNDMODE_ALWAYS:
        واپس true;
    طےشدہ:
        // Unexpected value, fallback to default behaviour
        واپس !ڈیٹا->videodata->cleared;
    }
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#تعریف_کرو MI_WP_SIGNATURE      0xFF515700
#تعریف_کرو MI_WP_SIGNATURE_نقاب 0xFFFFFF00
#تعریف_کرو IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_نقاب) == MI_WP_SIGNATURE

قسمتعریف شمار
{
    SDL_MOUSE_EVENT_ماخذ_UNKNOWN,
    SDL_MOUSE_EVENT_ماخذ_MOUSE,
    SDL_MOUSE_EVENT_ماخذ_TOUCH,
    SDL_MOUSE_EVENT_ماخذ_PEN,
} SDL_MOUSE_EVENT_ماخذ;

ساکن SDL_MOUSE_EVENT_ماخذ Get_Mouse_پیغام_ماخذ(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    اگر (IsTouchEvent(extrainfo)) {
        اگر (extrainfo & 0x80) {
            واپس SDL_MOUSE_EVENT_ماخذ_TOUCH;
        } ورنہ {
            واپس SDL_MOUSE_EVENT_ماخذ_PEN;
        }
    }
    واپس SDL_MOUSE_EVENT_ماخذ_MOUSE;
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساکن SDL_کھڑکی_ڈیٹا *WIN_Get_کھڑکی_ڈیٹا_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_کھڑکی *کھڑکی;

    اگر (_this) {
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
            اگر (ڈیٹا && ڈیٹا->hwnd == hwnd) {
                واپس ڈیٹا;
            }
        }
    }
    واپس تہی;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحیح n_رمز, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_ڈیٹا = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_ڈیٹا *ڈیٹا = SDL_GetVideoDevice()->اندرونی_2;
    SDL_Scancode جائزہ_رمز;

    اگر (n_رمز < 0 || n_رمز != HC_ACTION) {
        واپس Call_اگلا_Hook_Ex(تہی, n_رمز, wParam, lParam);
    }
    اگر (hook_ڈیٹا->جائزہ_رمز == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        واپس 1;
    }

    انتخاب (hook_ڈیٹا->vk_رمز) {
    حالت VK_LWIN:
        جائزہ_رمز = SDL_SCANCODE_LGUI;
        توڑو;
    حالت VK_RWIN:
        جائزہ_رمز = SDL_SCANCODE_RGUI;
        توڑو;
    حالت VK_LMENU:
        جائزہ_رمز = SDL_SCANCODE_LALT;
        توڑو;
    حالت VK_RMENU:
        جائزہ_رمز = SDL_SCANCODE_RALT;
        توڑو;
    حالت VK_LCONTROL:
        جائزہ_رمز = SDL_SCANCODE_LCTRL;
        توڑو;
    حالت VK_RCONTROL:
        جائزہ_رمز = SDL_SCANCODE_RCTRL;
        توڑو;
    حالت VK_SNAPSHOT:
        جائزہ_رمز = SDL_SCANCODE_PRINTSCREEN;
        توڑو;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالت VK_TAB:
        جائزہ_رمز = SDL_SCANCODE_TAB;
        توڑو;
    حالت VK_ESCAPE:
        جائزہ_رمز = SDL_SCANCODE_ESCAPE;
        توڑو;

    طےشدہ:
        واپس Call_اگلا_Hook_Ex(تہی, n_رمز, wParam, lParam);
    }

    اگر (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        اگر (!ڈیٹا->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_ڈیٹا->جائزہ_رمز, جائزہ_رمز, true);
        }
    } ورنہ {
        اگر (!ڈیٹا->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hook_ڈیٹا->جائزہ_رمز, جائزہ_رمز, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        اگر (hook_ڈیٹا->vk_رمز <= 0xFF && ڈیٹا->pre_hook_کلید_state[hook_ڈیٹا->vk_رمز]) {
            ڈیٹا->pre_hook_کلید_state[hook_ڈیٹا->vk_رمز] = 0;
            واپس Call_اگلا_Hook_Ex(تہی, n_رمز, wParam, lParam);
        }
    }

    واپس 1;
}

ساکن bool WIN_تبادلہ_Buttons(HANDLE hDevice)
{
    اگر (hDevice == تہی) {
        // Touchpad, already has buttons swapped
        واپس false;
    }
    واپس GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساکن خالی WIN_Handle_Raw_Mouse_داخلہ(Uint64 timestamp, SDL_Video_ڈیٹا *ڈیٹا, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساکن ساخت {
        USHORT usButtonFlags;
        Uint8 button;
        bool نیچے_کو;
    } raw_buttons[] = {
        { RI_MOUSE_بایاں_BUTTON_نیچے_کو, SDL_BUTTON_بایاں, true },
        { RI_MOUSE_بایاں_BUTTON_اوپر, SDL_BUTTON_بایاں, false },
        { RI_MOUSE_دایاں_BUTTON_نیچے_کو, SDL_BUTTON_دایاں, true },
        { RI_MOUSE_دایاں_BUTTON_اوپر, SDL_BUTTON_دایاں, false },
        { RI_MOUSE_درمیان_BUTTON_نیچے_کو, SDL_BUTTON_درمیان, true },
        { RI_MOUSE_درمیان_BUTTON_اوپر, SDL_BUTTON_درمیان, false },
        { RI_MOUSE_BUTTON_4_نیچے_کو, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_اوپر, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_نیچے_کو, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_اوپر, SDL_BUTTON_X2, false }
    };

    صحیح dx = (صحیح)rawmouse->l_آخری_X;
    صحیح dy = (صحیح)rawmouse->l_آخری_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    اگر (!ڈیٹا->raw_mouse_enabled) {
        واپس;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_کھڑکی *کھڑکی = SDL_GetKeyboardFocus();
    اگر (!کھڑکی) {
        واپس;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    اگر (!mouse) {
        واپس;
    }

    اگر (Get_Mouse_پیغام_ماخذ(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_ماخذ_MOUSE ||
        (SDL_Touch_Devices_دستیاب() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        واپس;
    }

    SDL_کھڑکی_ڈیٹا *windowdata = کھڑکی->اندرونی_2;

    اگر (haveMotion && !windowdata->اندر_modal_loop) {
        اگر (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (اعشاری)dx, (اعشاری)dy);
        } ورنہ {
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
            صحیح w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            صحیح h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            صحیح x = raw_coordinates ? dx : (صحیح)(((اعشاری)dx / 65535.0f) * w);
            صحیح y = raw_coordinates ? dy : (صحیح)(((اعشاری)dy / 65535.0f) * h);
            صحیح relX, relY;

            /* Calculate relative motion */
            اگر (ڈیٹا->آخری_raw_mouse_position.x == 0 && ڈیٹا->آخری_raw_mouse_position.y == 0) {
                ڈیٹا->آخری_raw_mouse_position.x = x;
                ڈیٹا->آخری_raw_mouse_position.y = y;
            }
            relX = x - ڈیٹا->آخری_raw_mouse_position.x;
            relY = y - ڈیٹا->آخری_raw_mouse_position.y;

            اگر (remote_desktop) {
                اگر (!windowdata->اندر_title_click && !windowdata->focus_click_pending) {
                    ساکن صحیح wobble;
                    اعشاری floatX = (اعشاری)x / w;
                    اعشاری floatY = (اعشاری)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    اگر (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحیح warpX = rect.بایاں + ((rect.دایاں - rect.بایاں) / 2) + wobble;
                        صحیح warpY = rect.چوٹی + ((rect.bottom - rect.چوٹی) / 2);

                        WIN_سیٹ_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        اگر (wobble > 1) {
                            wobble = -1;
                        }
                    } ورنہ {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ثابت صحیح MAX_RELATIVE_MOTION = (h / 6);
                        اگر (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (اعشاری)relX, (اعشاری)relY);
                        }
                    }
                }
            } ورنہ اگر (mouse->pen_mouse_events) {
                ثابت صحیح زیادہ_سے_زیادہ_TABLET_RELATIVE_MOTION = 32;
                اگر (SDL_abs(relX) > زیادہ_سے_زیادہ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > زیادہ_سے_زیادہ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } ورنہ {
                    SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, true, (اعشاری)relX, (اعشاری)relY);
                }
            } ورنہ {
                صحیح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحیح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                اگر (!ڈیٹا->raw_داخلہ_fake_pen_id) {
                    ڈیٹا->raw_داخلہ_fake_pen_id = SDL_جوڑو_Pen_Device(timestamp, "raw mouse input", کھڑکی, تہی, (خالی *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, ڈیٹا->raw_داخلہ_fake_pen_id, کھڑکی, (اعشاری)(x + screen_x - کھڑکی->x), (اعشاری)(y + screen_y - کھڑکی->y));
            }

            ڈیٹا->آخری_raw_mouse_position.x = x;
            ڈیٹا->آخری_raw_mouse_position.y = y;
        }
    }

    اگر (haveButton) {
        برائے (صحیح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            اگر (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool نیچے_کو = raw_buttons[i].نیچے_کو;

                اگر (button == SDL_BUTTON_بایاں) {
                    اگر (WIN_تبادلہ_Buttons(hDevice)) {
                        button = SDL_BUTTON_دایاں;
                    }
                } ورنہ اگر (button == SDL_BUTTON_دایاں) {
                    اگر (WIN_تبادلہ_Buttons(hDevice)) {
                        button = SDL_BUTTON_بایاں;
                    }
                }

                اگر (windowdata->focus_click_pending & SDL_BUTTON_نقاب(button)) {
                    // Ignore the button click for activation
                    اگر (!نیچے_کو) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_نقاب(button);
                        WIN_UpdateClipCursor(کھڑکی);
                    }
                    جاری;
                }

                SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, نیچے_کو);
            }
        }

        اگر (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ڈیٹا;
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_معمول);
        } ورنہ اگر (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_ڈیٹا;
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_معمول);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساکن خالی WIN_Handle_Raw_Keyboard_داخلہ(Uint64 timestamp, SDL_Video_ڈیٹا *ڈیٹا, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    اگر (!ڈیٹا->raw_keyboard_enabled) {
        واپس;
    }

    اگر (rawkeyboard->Flags & RI_کلید_E1) {
        // First key in a Ctrl+{key} sequence
        ڈیٹا->pending_E1_کلید_sequence = true;
        واپس;
    }

    اگر ((rawkeyboard->Flags & RI_کلید_E0) && rawkeyboard->Make_رمز == 0x2A) {
        // 0xE02A make code prefix, ignored
        واپس;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!rawkeyboard->Make_رمز) {
        rawkeyboard->Make_رمز = LOWORD(Map_Virtual_کلید(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_مقصد_VSC : MAPVK_VK_مقصد_VSC_EX));
    }
#اگر_ختم
    اگر (!rawkeyboard->Make_رمز) {
        واپس;
    }

    bool نیچے_کو;
    انتخاب (rawkeyboard->پیغام_4) {
    حالت WM_KEYDOWN:
    حالت WM_SYSKEYDOWN:
        نیچے_کو = true;
        توڑو;
    حالت WM_KEYUP:
    حالت WM_SYSKEYUP:
        نیچے_کو = false;
        توڑو;
    طےشدہ:
        نیچے_کو = !(rawkeyboard->Flags & RI_کلید_BREAK);
        توڑو;
    }

    SDL_Scancode رمز;
    USHORT rawcode = rawkeyboard->Make_رمز;
    اگر (ڈیٹا->pending_E1_کلید_sequence) {
        rawcode |= 0xE100;
        اگر (rawkeyboard->Make_رمز == 0x45) {
            // Ctrl+NumLock == Pause
            رمز = SDL_SCANCODE_PAUSE;
        } ورنہ {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            رمز = SDL_SCANCODE_UNKNOWN;
        }
        ڈیٹا->pending_E1_کلید_sequence = false;
    } ورنہ {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 اشاریہ = (Uint8)rawkeyboard->Make_رمز;
        اگر (rawkeyboard->Flags & RI_کلید_E0) {
            rawcode |= 0xE000;
            اشاریہ |= 0x80;
        }
        رمز = windows_scancode_جدول[اشاریہ];
    }

    اگر (نیچے_کو) {
        SDL_کھڑکی *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        اگر ((!ڈیٹا->raw_keyboard_flag_inputsink && !focus) || (focus && focus->متن_داخلہ_فعال)) {
            واپس;
        }
    }

    SDL_Send_Keyboard_کلید(timestamp, keyboardID, rawcode, رمز, نیچے_کو);
}

خالی WIN_Poll_Raw_داخلہ(SDL_VideoDevice *_this, Uint64 poll_آغاز)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    UINT سائز, i, گنتی, کل = 0;
    RAWINPUT *داخلہ;
    Uint64 poll_اختتام;

    اگر (ڈیٹا->rawinput_انحراف == 0) {
        BOOL isWow64;

        ڈیٹا->rawinput_انحراف = حجم(RAWINPUTHEADER);
        اگر (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            ڈیٹا->rawinput_انحراف += 8;
        }
    }

    // Get all available events
    داخلہ = (RAWINPUT *)ڈیٹا->rawinput;
    برائے (;;) {
        سائز = ڈیٹا->rawinput_سائز - (UINT)((BYTE *)داخلہ - ڈیٹا->rawinput);
        گنتی = Get_Raw_داخلہ_بفر(داخلہ, &سائز, حجم(RAWINPUTHEADER));
        poll_اختتام = SDL_GetTicksNS();
        اگر (گنتی == 0 || گنتی == (UINT)-1) {
            اگر (!ڈیٹا->rawinput || (گنتی == (UINT)-1 && Get_آخری_Error() == ERROR_INSUFFICIENT_بفر)) {
                ثابت UINT RAWINPUT_بفر_سائز_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(ڈیٹا->rawinput, ڈیٹا->rawinput_سائز + RAWINPUT_بفر_سائز_INCREMENT);
                اگر (!rawinput) {
                    توڑو;
                }
                داخلہ = (RAWINPUT *)(rawinput + ((BYTE *)داخلہ - ڈیٹا->rawinput));
                ڈیٹا->rawinput = rawinput;
                ڈیٹا->rawinput_سائز += RAWINPUT_بفر_سائز_INCREMENT;
            } ورنہ {
                توڑو;
            }
        } ورنہ {
            کل += گنتی;

            // Advance input to the end of the buffer
            جب (گنتی--) {
                داخلہ = NEXTRAWINPUTBLOCK(داخلہ);
            }
        }
    }

    اگر (کل > 0) {
        Uint64 delta = poll_اختتام - poll_آغاز;
        UINT mouse_کل = 0;
        برائے (i = 0, داخلہ = (RAWINPUT *)ڈیٹا->rawinput; i < کل; ++i, داخلہ = NEXTRAWINPUTBLOCK(داخلہ)) {
            اگر (داخلہ->سرخی.dwType == RIM_TYPEMOUSE) {
                mouse_کل += 1;
            }
        }
        صحیح mouse_اشاریہ = 0;
        برائے (i = 0, داخلہ = (RAWINPUT *)ڈیٹا->rawinput; i < کل; ++i, داخلہ = NEXTRAWINPUTBLOCK(داخلہ)) {
            اگر (داخلہ->سرخی.dwType == RIM_TYPEMOUSE) {
                mouse_اشاریہ += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)داخلہ + ڈیٹا->rawinput_انحراف);
                Uint64 وقت = poll_اختتام - (delta * (mouse_کل - mouse_اشاریہ)) / mouse_کل;
                WIN_Handle_Raw_Mouse_داخلہ(وقت, ڈیٹا, داخلہ->سرخی.hDevice, rawmouse);
            } ورنہ اگر (داخلہ->سرخی.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)داخلہ + ڈیٹا->rawinput_انحراف);
                WIN_Handle_Raw_Keyboard_داخلہ(poll_اختتام, ڈیٹا, داخلہ->سرخی.hDevice, rawkeyboard);
            }
        }
    }
    ڈیٹا->آخری_rawinput_poll = poll_اختتام;
}

ساکن خالی جوڑو_Device_ID(Uint32 deviceID, Uint32 **list, صحیح *گنتی)
{
    صحیح new_گنتی = (*گنتی + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        واپس;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}

ساکن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحیح گنتی)
{
    برائے (صحیح i = 0; i < گنتی; ++i) {
        اگر (deviceID == list[i]) {
            واپس true;
        }
    }
    واپس false;
}

ساکن حرف *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت حرف *instance, Uint16 vendor, Uint16 حاصل_ضرب, ثابت حرف *default_name, bool hid_loaded)
{
    حرف *vendor_name = تہی;
    حرف *حاصل_ضرب_name = تہی;
    حرف *name = تہی;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    اگر (hid_loaded) {
        حرف devName[MAX_راستہ + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_داخلہ_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        اگر (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, تہی, OPEN_EXISTING, 0, تہی);
            اگر (hFile != INVALID_HANDLE_قدر) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_Hid_D_Get_حاصل_ضرب_String(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    اگر (vend[0]) {
        vendor_name = WIN_String_مقصد_UTF8_W(vend);
    }

    اگر (prod[0]) {
        حاصل_ضرب_name = WIN_String_مقصد_UTF8_W(prod);
    } ورنہ {
        SP_DEVINFO_ڈیٹا ڈیٹا;
        SDL_zero(ڈیٹا);
        ڈیٹا.cb_سائز = حجم(ڈیٹا);
        برائے (DWORD i = 0;; ++i) {
            اگر (!تیاری_Di_Enum_Device_Info(devinfo, i, &ڈیٹا)) {
                اگر (Get_آخری_Error() == ERROR_NO_مزید_اشیاء) {
                    توڑو;
                } ورنہ {
                    جاری;
                }
            }

            حرف DeviceInstanceId[64];
            اگر (!تیاری_Di_Get_Device_Instance_Id_A(devinfo, &ڈیٹا, DeviceInstanceId, حجم(DeviceInstanceId), تہی))
                جاری;

            اگر (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD سائز = 0;
                اگر (تیاری_Di_Get_Device_Registry_Property_W(devinfo, &ڈیٹا, SPDRP_DEVICEDESC, تہی, (PBYTE)prod, حجم(prod), &سائز)) {
                    // Make sure the device description is null terminated
                    سائز /= حجم(*prod);
                    اگر (سائز >= SDL_arraysize(prod)) {
                        // Truncated description...
                        سائز = (SDL_arraysize(prod) - 1);
                    }
                    prod[سائز] = 0;

                    اگر (vendor || حاصل_ضرب) {
                        SDL_asprintf(&حاصل_ضرب_name, "%S (0x%.4x/0x%.4x)", prod, vendor, حاصل_ضرب);
                    } ورنہ {
                        حاصل_ضرب_name = WIN_String_مقصد_UTF8_W(prod);
                    }
                }
                توڑو;
            }
        }
    }

    اگر (!حاصل_ضرب_name && (vendor || حاصل_ضرب)) {
        SDL_asprintf(&حاصل_ضرب_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, حاصل_ضرب);
    }
    name = SDL_CreateDeviceName(vendor, حاصل_ضرب, vendor_name, حاصل_ضرب_name, default_name);
    SDL_free(vendor_name);
    SDL_free(حاصل_ضرب_name);

    واپس name;
}

خالی WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = تہی;
    UINT raw_device_گنتی = 0;
    صحیح old_keyboard_گنتی = 0;
    SDL_KeyboardID *old_keyboards = تہی;
    صحیح new_keyboard_گنتی = 0;
    SDL_KeyboardID *new_keyboards = تہی;
    صحیح old_mouse_گنتی = 0;
    SDL_MouseID *old_mice = تہی;
    صحیح new_mouse_گنتی = 0;
    SDL_MouseID *new_mice = تہی;

    اگر (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->اندرونی_2->detect_device_hotplug ||
        _this->اندرونی_2->gameinput_context) {
        واپس;
    }

    اگر ((Get_Raw_داخلہ_Device_List(تہی, &raw_device_گنتی, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_گنتی)) {
        واپس; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_گنتی);
    اگر (!raw_devices) {
        واپس; // oh well.
    }

    raw_device_گنتی = Get_Raw_داخلہ_Device_List(raw_devices, &raw_device_گنتی, حجم(RAWINPUTDEVICELIST));
    اگر (raw_device_گنتی == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = تہی;
        واپس; // oh well.
    }

    HDEVINFO devinfo = تیاری_Di_Get_Class_Devs_A(تہی, تہی, تہی, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_گنتی);
    old_mice = SDL_GetMice(&old_mouse_گنتی);

    برائے (UINT i = 0; i < raw_device_گنتی; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_راستہ] = { 0 };
        UINT rdi_سائز = حجم(rdi);
        UINT name_سائز = SDL_arraysize(devName);
        صحیح vendor = 0, حاصل_ضرب = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        اگر (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            جاری;
        }

        rdi.cb_سائز = حجم(rdi);
        اگر (Get_Raw_داخلہ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_سائز) == ((UINT)-1) ||
            Get_Raw_داخلہ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_سائز) == ((UINT)-1)) {
            جاری;
        }

        // Extract the device instance
        instance = devName;
        جب (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        برائے (ptr = instance; *ptr; ++ptr) {
            اگر (*ptr == '#') {
                *ptr = '\\';
            }
            اگر (*ptr == '{') {
                اگر (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                توڑو;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &حاصل_ضرب);

        انتخاب (dwType) {
        حالت RIM_TYPEKEYBOARD:
            اگر (SDL_IsKeyboard((Uint16)vendor, (Uint16)حاصل_ضرب, rdi.keyboard.dw_نمبر_کا_کلیدیں_کل)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڑو_Device_ID(keyboardID, &new_keyboards, &new_keyboard_گنتی);
                اگر (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_گنتی)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Keyboard", hid_loaded);
                    SDL_جوڑو_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            توڑو;
        حالت RIM_TYPEMOUSE:
            اگر (SDL_IsMouse((Uint16)vendor, (Uint16)حاصل_ضرب)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                جوڑو_Device_ID(mouseID, &new_mice, &new_mouse_گنتی);
                اگر (!HasDeviceID(mouseID, old_mice, old_mouse_گنتی)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)حاصل_ضرب, "Mouse", hid_loaded);
                    SDL_جوڑو_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            توڑو;
        طےشدہ:
            توڑو;
        }
    }

    برائے (صحیح i = old_keyboard_گنتی; i--;) {
        اگر (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_گنتی)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    برائے (صحیح i = old_mouse_گنتی; i--;) {
        اگر (!HasDeviceID(old_mice[i], new_mice, new_mouse_گنتی)) {
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
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
ساکن bool Skip_Alt_Gr_بایاں_Control(WPARAM wParam, LPARAM lParam)
{
    اگر (wParam != VK_CONTROL) {
        واپس false;
    }

    // Is this an extended key (i.e. right key)?
    اگر (lParam & 0x01000000) {
        واپس false;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    پیغام_3 اگلا_پیغام;
    DWORD پیغام_وقت = Get_پیغام_وقت();
    اگر (Peek_پیغام(&اگلا_پیغام, تہی, 0, 0, PM_NOREMOVE)) {
        اگر (اگلا_پیغام.پیغام == WM_KEYDOWN ||
            اگلا_پیغام.پیغام == WM_SYSKEYDOWN) {
            اگر (اگلا_پیغام.wParam == VK_MENU && (اگلا_پیغام.lParam & 0x01000000) && اگلا_پیغام.وقت == پیغام_وقت) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                واپس true;
            }
        }
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    واپس false;
}

ساکن bool Dispatch_Modal_Loop_پیغام_Hook(HWND *hwnd, UINT *پیغام_2, WPARAM *wParam, LPARAM *lParam)
{
    پیغام_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.پیغام = *پیغام_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    اگر (g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_ڈیٹا, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *پیغام_2 = dummy.پیغام;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        واپس true;
    }
    واپس false;
}

LRESULT CALLBACK WIN_کھڑکی_Proc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    LRESULT return_رمز = -1;

    // Get the window data for the window
    ڈیٹا = WIN_Get_کھڑکی_ڈیٹا_From_HWND(hwnd);
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!ڈیٹا) {
        // Fallback
        ڈیٹا = (SDL_کھڑکی_ڈیٹا *)GetProp(hwnd, متن_2("SDL_WindowData"));
    }
#اگر_ختم
    اگر (!ڈیٹا) {
        واپس Call_کھڑکی_Proc(Def_کھڑکی_Proc, hwnd, پیغام_2, wParam, lParam);
    }

#اگر_تعریف_شدہ WMMSG_DEBUG
    {
        حرف پیغام[1024];
        اگر (پیغام_2 > MAX_WMMSG) {
            SDL_snprintf(پیغام, حجم(پیغام), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, پیغام_2, wParam, lParam);
        } ورنہ {
            SDL_snprintf(پیغام, حجم(پیغام), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[پیغام_2], wParam, lParam);
        }
        OutputDebugStringA(پیغام);
    }
#اگر_ختم // WMMSG_DEBUG


    اگر (g_Windows_پیغام_Hook && ڈیٹا->اندر_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        اگر (!Dispatch_Modal_Loop_پیغام_Hook(&hwnd, &پیغام_2, &wParam, &lParam)) {
            واپس 0;
        }
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (WIN_HandleIMEMessage(hwnd, پیغام_2, wParam, &lParam, ڈیٹا->videodata)) {
        واپس 0;
    }
#اگر_ختم

    انتخاب (پیغام_2) {

    حالت WM_SHOWWINDOW:
    {
        اگر (wParam) {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
        } ورنہ {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
        }
    } توڑو;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالت WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        ڈیٹا->postpone_clipcursor = true;
        ڈیٹا->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        نقطہ_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(ڈیٹا->کھڑکی, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } توڑو;

    حالت WM_NCUAHDRAWCAPTION:
    حالت WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            return_رمز = 0;
        }
    } توڑو;

    حالت WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(ڈیٹا->کھڑکی, !!LOWORD(wParam), &pos);
    } توڑو;

    حالت WM_MOUSEACTIVATE:
    {
        اگر (SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی)) {
            واپس MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_کھڑکی *والد = ڈیٹا->کھڑکی->والد;
        جب (والد) {
            اگر ((والد->flags & SDL_کھڑکی_داخلہ_FOCUS) &&
                (والد->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال)) {
                واپس MA_NOACTIVATE;
            }
            والد = والد->والد;
        }
    } توڑو;

    حالت WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(ڈیٹا->کھڑکی, true, &pos);
    } توڑو;

    حالت WM_KILLFOCUS:
    حالت WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیغام_Pos = Get_پیغام_Pos();
        نقطہ_2 pos = { GET_X_LPARAM(پیغام_Pos), GET_Y_LPARAM(پیغام_Pos) };
        WIN_UpdateFocus(ڈیٹا->کھڑکی, false, &pos);
    } توڑو;

    حالت WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Type) {
            توڑو;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ورنہ اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            توڑو;  // oh well.
        } ورنہ اگر (اشارہ_گر_type != PT_PEN) {
            توڑو;  // we only care about pens here.
        }

        خالی *hpointer = (خالی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle(hpointer);
        اگر (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ڈیٹا->کھڑکی, true, true);
        } ورنہ {
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
            SDL_جوڑو_Pen_Device(WIN_GetEventTimestamp(), تہی, ڈیٹا->کھڑکی, &info, hpointer, true);
        }
        return_رمز = 0;
    } توڑو;

    حالت WM_POINTERCAPTURECHANGED:
    حالت WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Type) {
            توڑو;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ورنہ اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            توڑو;  // oh well.
        } ورنہ اگر (اشارہ_گر_type != PT_PEN) {
            توڑو;  // we only care about pens here.
        }

        خالی *hpointer = (خالی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle(hpointer);
        اگر (pen == 0) {
            توڑو;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        اگر ((پیغام_2 == WM_POINTERCAPTURECHANGED) || !IS_اشارہ_گر_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, ڈیٹا->کھڑکی, false, false);
        }
        return_رمز = 0;
    } توڑو;

    حالت WM_POINTERDOWN:
    حالت WM_POINTERUP:
    حالت WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        اشارہ_گر_داخلہ_TYPE اشارہ_گر_type = PT_اشارہ_گر;
        اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Type || !ڈیٹا->videodata->Get_اشارہ_گر_Type(pointerid, &اشارہ_گر_type)) {
            توڑو;  // oh well.
        } ورنہ اگر ((پیغام_2 == WM_POINTERUPDATE) && (اشارہ_گر_type == PT_MOUSE)) {
            ڈیٹا->آخری_اشارہ_گر_update = lParam;
            return_رمز = 0;
            توڑو;
        } ورنہ اگر (اشارہ_گر_type != PT_PEN) {
            توڑو; // we only care about pens here.
        }

        خالی *hpointer = (خالی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle(hpointer);
        اشارہ_گر_PEN_INFO pen_info;
        اگر (pen == 0) {
            توڑو;  // not a pen, or not a pen we already knew about.
        } ورنہ اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Pen_Info || !ڈیٹا->videodata->Get_اشارہ_گر_Pen_Info(pointerid, &pen_info)) {
            توڑو;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

        ثابت bool istouching = IS_اشارہ_گر_INCONTACT_WPARAM(wParam) && IS_اشارہ_گر_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        اگر (!istouching) {
            SDL_SendPenTouch(timestamp, pen, کھڑکی, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت اشارہ_گر_INFO *اشارہ_گر_info = &pen_info.اشارہ_گر_Info;
        RECT tablet_bounds, tablet_mapping;
        اعشاری fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        اگر (!ڈیٹا->videodata->Get_اشارہ_گر_Device_Rects || !ڈیٹا->videodata->Get_اشارہ_گر_Device_Rects(اشارہ_گر_info->ماخذ_Device, &tablet_bounds, &tablet_mapping)) {
            نقطہ_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_مقصد_Client(ڈیٹا->hwnd, &position);
            fx = (اعشاری) position.x;
            fy = (اعشاری) position.y;
        } ورنہ {
            صحیح ix, iy;
            SDL_Get_کھڑکی_Position(کھڑکی, &ix, &iy);
            ثابت SDL_FPoint کھڑکی_pos = { (اعشاری) ix, (اعشاری) iy };

            ثابت اعشاری facX = اشارہ_گر_info->ptHimetricLocationRaw.x / (اعشاری) (tablet_bounds.دایاں );
            ثابت اعشاری facY = اشارہ_گر_info->ptHimetricLocationRaw.y / (اعشاری) (tablet_bounds.bottom);

            ثابت اعشاری w = tablet_mapping.دایاں  - tablet_mapping.بایاں;
            ثابت اعشاری h = tablet_mapping.bottom - tablet_mapping.چوٹی;

            fx = (tablet_mapping.بایاں + (facX * w)) - کھڑکی_pos.x;
            fy = (tablet_mapping.چوٹی  + (facY * h)) - کھڑکی_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, کھڑکی, fx, fy);
        SDL_SendPenButton(timestamp, pen, کھڑکی, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, کھڑکی, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        اگر (pen_info.pen_نقاب & PEN_نقاب_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_PRESSURE, ((اعشاری) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        اگر (pen_info.pen_نقاب & PEN_نقاب_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_ROTATION, ((اعشاری) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        اگر (pen_info.pen_نقاب & PEN_نقاب_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_XTILT, ((اعشاری) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        اگر (pen_info.pen_نقاب & PEN_نقاب_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, کھڑکی, SDL_PEN_AXIS_YTILT, ((اعشاری) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        اگر (istouching) {
            SDL_SendPenTouch(timestamp, pen, کھڑکی, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_رمز = 0;
    } توڑو;

    حالت WM_MOUSEMOVE:
    {
        SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

        اگر (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            bool wish_clip_cursor = (
                کھڑکی->flags & (SDL_کھڑکی_MOUSE_RELATIVE_منوال | SDL_کھڑکی_MOUSE_GRABBED) ||
                (کھڑکی->mouse_rect.w > 0 && کھڑکی->mouse_rect.h > 0)
            );
            اگر (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                ڈیٹا->clipcursor_queued = true;
            }
        }

        اگر (!ڈیٹا->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_سائز = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = ڈیٹا->hwnd;

            اگر (TrackMouseEvent(&trackMouseEvent)) {
                ڈیٹا->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ڈیٹا);
        }

        اگر (!ڈیٹا->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            اگر (Get_Mouse_پیغام_ماخذ((ULONG)Get_پیغام_Extra_Info()) == SDL_MOUSE_EVENT_ماخذ_MOUSE &&
                lParam != ڈیٹا->آخری_اشارہ_گر_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)GET_X_LPARAM(lParam), (اعشاری)GET_Y_LPARAM(lParam));
            }
        }

    } توڑو;

    حالت WM_LBUTTONUP:
    حالت WM_RBUTTONUP:
    حالت WM_MBUTTONUP:
    حالت WM_XBUTTONUP:
    حالت WM_LBUTTONDOWN:
    حالت WM_LBUTTONDBLCLK:
    حالت WM_RBUTTONDOWN:
    حالت WM_RBUTTONDBLCLK:
    حالت WM_MBUTTONDOWN:
    حالت WM_MBUTTONDBLCLK:
    حالت WM_XBUTTONDOWN:
    حالت WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        اگر (!ڈیٹا->videodata->raw_mouse_enabled) {
            اگر (Get_Mouse_پیغام_ماخذ((ULONG)Get_پیغام_Extra_Info()) == SDL_MOUSE_EVENT_ماخذ_MOUSE &&
                lParam != ڈیٹا->آخری_اشارہ_گر_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, ڈیٹا, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } توڑو;

#اگر 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالت WM_داخلہ:
    {
        HRAWINPUT h_Raw_داخلہ = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT سائز = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        اگر (ڈیٹا->کھڑکی != SDL_GetKeyboardFocus()) {
            توڑو;
        }

        Get_Raw_داخلہ_ڈیٹا(h_Raw_داخلہ, RID_داخلہ, &inp, &سائز, حجم(RAWINPUTHEADER));
        اگر (inp.سرخی.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_داخلہ(WIN_GetEventTimestamp(), ڈیٹا, inp.سرخی.hDevice, &inp.ڈیٹا.mouse);
        } ورنہ اگر (inp.سرخی.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_داخلہ(WIN_GetEventTimestamp(), ڈیٹا, inp.سرخی.hDevice, &inp.ڈیٹا.keyboard);
        }
    } توڑو;
#اگر_ختم

    حالت WM_MOUSEWHEEL:
    حالت WM_MOUSEHWHEEL:
    {
        اگر (!ڈیٹا->videodata->raw_mouse_enabled) {
            مختصر amount = GET_WHEEL_DELTA_WPARAM(wParam);
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            اگر (پیغام_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_معمول);
            } ورنہ {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_معمول);
            }
        }
    } توڑو;

    حالت WM_MOUSELEAVE:
        اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            اگر (SDL_GetMouseFocus() == ڈیٹا->کھڑکی && !SDL_GetMouse()->relative_منوال && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_پیغام_Pos();
                نقطہ_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_مقصد_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                اگر (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                } ورنہ {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    اگر (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, SDL_TOUCH_MOUSEID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                    } ورنہ { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                    }
                }
            }

            اگر (!SDL_GetMouse()->relative_منوال) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_سیٹ_Mouse_Focus(تہی);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        ڈیٹا->mouse_tracked = false;

        return_رمز = 0;
        توڑو;
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالت WM_KEYDOWN:
    حالت WM_SYSKEYDOWN:
    {
        اگر (Skip_Alt_Gr_بایاں_Control(wParam, lParam)) {
            return_رمز = 0;
            توڑو;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode رمز = Windows_جائزہ_رمز_مقصد_SDLScan_رمز(lParam, wParam, &rawcode, &virtual_کلید);

        // Detect relevant keyboard shortcuts
        اگر (رمز == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            اگر (Should_Generate_کھڑکی_Close_On_Alt_F4()) {
                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
            }
        }

        اگر (virtual_کلید || !ڈیٹا->videodata->raw_keyboard_enabled || ڈیٹا->کھڑکی->متن_داخلہ_فعال) {
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, رمز, true);
        }
    }

        return_رمز = 0;
        توڑو;

    حالت WM_SYSKEYUP:
    حالت WM_KEYUP:
    {
        اگر (Skip_Alt_Gr_بایاں_Control(wParam, lParam)) {
            return_رمز = 0;
            توڑو;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode رمز = Windows_جائزہ_رمز_مقصد_SDLScan_رمز(lParam, wParam, &rawcode, &virtual_کلید);
        ثابت bool *keyboardState = SDL_GetKeyboardState(تہی);

        اگر (virtual_کلید || !ڈیٹا->videodata->raw_keyboard_enabled || ڈیٹا->کھڑکی->متن_داخلہ_فعال) {
            اگر (رمز == SDL_SCANCODE_PRINTSCREEN && !keyboardState[رمز]) {
                SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, رمز, true);
            }
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, رمز, false);
        }
    }
        return_رمز = 0;
        توڑو;

    حالت WM_UNICHAR:
        اگر (wParam == UNICODE_NOCHAR) {
            return_رمز = 1;
        } ورنہ {
            اگر (SDL_متن_داخلہ_فعال(ڈیٹا->کھڑکی)) {
                حرف متن[5];
                حرف *انتہا = SDL_UCS4_مقصد_UTF8((Uint32)wParam, متن);
                *انتہا = '\0';
                SDL_Send_Keyboard_متن(متن);
            }
            return_رمز = 0;
        }
        توڑو;

    حالت WM_CHAR:
        اگر (SDL_متن_داخلہ_فعال(ڈیٹا->کھڑکی)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            اگر (IS_بلند_SURROGATE(wParam)) {
                ڈیٹا->بلند_surrogate = (WCHAR)wParam;
            } ورنہ {
                WCHAR utf16[3];

                utf16[0] = ڈیٹا->بلند_surrogate ? ڈیٹا->بلند_surrogate : (WCHAR)wParam;
                utf16[1] = ڈیٹا->بلند_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحیح نتیجہ = WIN_Wide_Char_مقصد_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), تہی, تہی);
                اگر (نتیجہ > 0) {
                    SDL_Send_Keyboard_متن(utf8);
                }
                ڈیٹا->بلند_surrogate = L'\0';
            }
        } ورنہ {
            ڈیٹا->بلند_surrogate = L'\0';
        }

        return_رمز = 0;
        توڑو;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#اگر_تعریف_شدہ WM_INPUTLANGCHANGE
    حالت WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_رمز = 1;
        توڑو;
#اگر_ختم // WM_INPUTLANGCHANGE

    حالت WM_NCLBUTTONDOWN:
    {
        ڈیٹا->اندر_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        اگر (Send_پیغام(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            نقطہ_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_مقصد_Client(hwnd, &cursorPos);
            Post_پیغام(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } توڑو;

    حالت WM_CAPTURECHANGED:
    {
        ڈیٹا->اندر_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), ڈیٹا);
    } توڑو;

#اگر_تعریف_شدہ WM_GETMINMAXINFO
    حالت WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT سائز;
        صحیح x, y;
        صحیح w, h;
        صحیح min_w, min_h;
        صحیح max_w, max_h;
        BOOL constrain_max_سائز;

        // If this is an expected size change, allow it
        اگر (ڈیٹا->expected_resize) {
            توڑو;
        }

        // Get the current position of our window
        Get_کھڑکی_Rect(hwnd, &سائز);
        x = سائز.بایاں;
        y = سائز.چوٹی;

        // Calculate current size of our window
        SDL_Get_کھڑکی_سائز(ڈیٹا->کھڑکی, &w, &h);
        SDL_Get_کھڑکی_Minimum_سائز(ڈیٹا->کھڑکی, &min_w, &min_h);
        SDL_Get_کھڑکی_زیادہ_سے_زیادہ_سائز(ڈیٹا->کھڑکی, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        اگر (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_سائز = TRUE;
        } ورنہ {
            constrain_max_سائز = FALSE;
        }

        اگر (!(SDL_Get_کھڑکی_Flags(ڈیٹا->کھڑکی) & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی)) {
            سائز.چوٹی = 0;
            سائز.بایاں = 0;
            سائز.bottom = h;
            سائز.دایاں = w;
            WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &سائز, 0);
            w = سائز.دایاں - سائز.بایاں;
            h = سائز.bottom - سائز.چوٹی;
#اگر_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#اگر_ختم
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        اگر (SDL_Get_کھڑکی_Flags(ڈیٹا->کھڑکی) & SDL_کھڑکی_RESIZABLE) {
            اگر (SDL_Get_کھڑکی_Flags(ڈیٹا->کھڑکی) & SDL_کھڑکی_BORDERLESS) {
                صحیح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحیح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_سائز.x = SDL_max(w, screenW);
                info->pt_Max_سائز.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_سائز.x = (LONG)w + min_w;
            info->pt_Min_Track_سائز.y = (LONG)h + min_h;
            اگر (constrain_max_سائز) {
                info->pt_Max_Track_سائز.x = (LONG)w + max_w;
                info->pt_Max_Track_سائز.y = (LONG)h + max_h;
            }
        } ورنہ {
            info->pt_Max_سائز.x = w;
            info->pt_Max_سائز.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_سائز.x = w;
            info->pt_Min_Track_سائز.y = h;
            info->pt_Max_Track_سائز.x = w;
            info->pt_Max_Track_سائز.y = h;
        }
    }
        return_رمز = 0;
        توڑو;
#اگر_ختم // WM_GETMINMAXINFO

    حالت WM_WINDOWPOSCHANGING:

        اگر (ڈیٹا->expected_resize) {
            return_رمز = 0;
        } ورنہ اگر (ڈیٹا->اندر_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            اگر (ڈیٹا->آخری_modal_چوڑائی == windowpos->cx && ڈیٹا->آخری_modal_اونچائی == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            ڈیٹا->آخری_modal_چوڑائی = windowpos->cx;
            ڈیٹا->آخری_modal_اونچائی = windowpos->cy;

            return_رمز = 0;
        }
        توڑو;

    حالت WM_WINDOWPOSCHANGED:
    {
        SDL_کھڑکی *win;
        ثابت SDL_DisplayID original_displayID = ڈیٹا->کھڑکی->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحیح x, y;
        صحیح w, h;

        اگر (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        اگر (iconic) {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        } ورنہ اگر (zoomed) {
            اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
            }
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MAXIMIZED, 0, 0);
            ڈیٹا->force_ws_maximizebox = true;
        } ورنہ اگر (ڈیٹا->کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED)) {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                ڈیٹا->force_ws_maximizebox = false;
                WIN_سیٹ_کھڑکی_Resizable(SDL_GetVideoDevice(), ڈیٹا->کھڑکی, !!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_RESIZABLE));
            }
        }

        اگر (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        اگر (iconic) {
            توڑو;
        }

        اگر (ڈیٹا->initializing) {
            توڑو;
        }

        اگر (!ڈیٹا->disable_move_سائز_events) {
            اگر (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
                Client_مقصد_Screen(hwnd, (LPPOINT) &rect);
                Client_مقصد_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.بایاں;
                y = rect.چوٹی;

                SDL_Global_مقصد_Relative_For_کھڑکی(ڈیٹا->کھڑکی, x, y, &x, &y);
                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            اگر (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
                w = rect.دایاں;
                h = rect.bottom;

                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(ڈیٹا->کھڑکی);

        // Update the window display position
        اگر (ڈیٹا->کھڑکی->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_کھڑکی_ICCProfile(ڈیٹا->کھڑکی, true);
        }

        // Update the position of any child windows
        برائے (win = ڈیٹا->کھڑکی->پہلا_بچہ; win; win = win->اگلا_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            اگر (SDL_کھڑکی_IS_POPUP(win) && !(win->flags & SDL_کھڑکی_HIDDEN)) {
                WIN_سیٹ_کھڑکی_Position_اندرونی(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } توڑو;

    حالت WM_ENTERSIZEMOVE:
    حالت WM_ENTERMENULOOP:
    {
        اگر (g_Windows_پیغام_Hook) {
            اگر (!Dispatch_Modal_Loop_پیغام_Hook(&hwnd, &پیغام_2, &wParam, &lParam)) {
                واپس 0;
            }
        }

        ++ڈیٹا->اندر_modal_loop;
        اگر (ڈیٹا->اندر_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_کھڑکی_Rect(ڈیٹا->hwnd, &rect);
            ڈیٹا->آخری_modal_چوڑائی = rect.دایاں - rect.بایاں;
            ڈیٹا->آخری_modal_اونچائی = rect.bottom - rect.چوٹی;

            ڈیٹا->initial_سائز_rect.بایاں = ڈیٹا->کھڑکی->x;
            ڈیٹا->initial_سائز_rect.دایاں = ڈیٹا->کھڑکی->x + ڈیٹا->کھڑکی->w;
            ڈیٹا->initial_سائز_rect.چوٹی = ڈیٹا->کھڑکی->y;
            ڈیٹا->initial_سائز_rect.bottom = ڈیٹا->کھڑکی->y + ڈیٹا->کھڑکی->h;

            سیٹ_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, تہی);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } توڑو;

    حالت WM_TIMER:
    {
        اگر (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_کھڑکی_زندہ_Resize_Update(ڈیٹا->کھڑکی);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#اگر 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            اگر (ڈیٹا->videodata->DwmFlush) {
                ڈیٹا->videodata->DwmFlush();
            }
#اگر_ختم
#اگر_ختم
            واپس 0;
        }
    } توڑو;

    حالت WM_EXITSIZEMOVE:
    حالت WM_EXITMENULOOP:
    {
        --ڈیٹا->اندر_modal_loop;
        اگر (ڈیٹا->اندر_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } توڑو;

    حالت WM_SIZING:
        {
            WPARAM کنارہ = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool تالا_aspect_تناسب = (ڈیٹا->کھڑکی->max_aspect == ڈیٹا->کھڑکی->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            اعشاری new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            اگر (ڈیٹا->کھڑکی->min_aspect <= 0 && ڈیٹا->کھڑکی->max_aspect <= 0) {
                توڑو;
            }

            // unadjust the dragRect from the window rect to the client rect
            سیٹ_Rect_خالی_خانے(&rc);
            اگر (!Adjust_کھڑکی_Rect_Ex(&rc, Get_کھڑکی_Style(hwnd), GetMenu(hwnd) != تہی, Get_کھڑکی_Ex_Style(hwnd))) {
                توڑو;
            }

            clientDragRect.بایاں -= rc.بایاں;
            clientDragRect.چوٹی -= rc.چوٹی;
            clientDragRect.دایاں -= rc.دایاں;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.دایاں - clientDragRect.بایاں;
            h = clientDragRect.bottom - clientDragRect.چوٹی;
            new_aspect = w / (اعشاری)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            اگر (تالا_aspect_تناسب) {
                انتخاب (کنارہ) {
                حالت WMSZ_بایاں:
                حالت WMSZ_دایاں:
                    h = (صحیح)SDL_roundf(w / ڈیٹا->کھڑکی->max_aspect);
                    توڑو;
                طےشدہ:
                    // resizing via corners or top or bottom
                    w = (صحیح)SDL_roundf(h * ڈیٹا->کھڑکی->max_aspect);
                    توڑو;
                }
            } ورنہ {
                انتخاب (کنارہ) {
                حالت WMSZ_بایاں:
                حالت WMSZ_دایاں:
                    اگر (ڈیٹا->کھڑکی->max_aspect > 0.0f && new_aspect > ڈیٹا->کھڑکی->max_aspect) {
                        w = (صحیح)SDL_roundf(h * ڈیٹا->کھڑکی->max_aspect);
                    } ورنہ اگر (ڈیٹا->کھڑکی->min_aspect > 0.0f && new_aspect < ڈیٹا->کھڑکی->min_aspect) {
                        w = (صحیح)SDL_roundf(h * ڈیٹا->کھڑکی->min_aspect);
                    }
                    توڑو;
                حالت WMSZ_چوٹی:
                حالت WMSZ_BOTTOM:
                    اگر (ڈیٹا->کھڑکی->min_aspect > 0.0f && new_aspect < ڈیٹا->کھڑکی->min_aspect) {
                        h = (صحیح)SDL_roundf(w / ڈیٹا->کھڑکی->min_aspect);
                    } ورنہ اگر (ڈیٹا->کھڑکی->max_aspect > 0.0f && new_aspect > ڈیٹا->کھڑکی->max_aspect) {
                        h = (صحیح)SDL_roundf(w / ڈیٹا->کھڑکی->max_aspect);
                    }
                    توڑو;

                طےشدہ:
                    // resizing via corners
                    اگر (ڈیٹا->کھڑکی->max_aspect > 0.0f && new_aspect > ڈیٹا->کھڑکی->max_aspect) {
                        w = (صحیح)SDL_roundf(h * ڈیٹا->کھڑکی->max_aspect);
                    } ورنہ اگر (ڈیٹا->کھڑکی->min_aspect > 0.0f && new_aspect < ڈیٹا->کھڑکی->min_aspect) {
                        h = (صحیح)SDL_roundf(w / ڈیٹا->کھڑکی->min_aspect);
                    }
                    توڑو;
                }
            }

            انتخاب (کنارہ) {
            حالت WMSZ_بایاں:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                اگر (تالا_aspect_تناسب) {
                    clientDragRect.چوٹی = (ڈیٹا->initial_سائز_rect.bottom + ڈیٹا->initial_سائز_rect.چوٹی - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                توڑو;
            حالت WMSZ_BOTTOMLEFT:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                توڑو;
            حالت WMSZ_دایاں:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                اگر (تالا_aspect_تناسب) {
                    clientDragRect.چوٹی = (ڈیٹا->initial_سائز_rect.bottom + ڈیٹا->initial_سائز_rect.چوٹی - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                توڑو;
            حالت WMSZ_TOPRIGHT:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                توڑو;
            حالت WMSZ_چوٹی:
                اگر (تالا_aspect_تناسب) {
                    clientDragRect.بایاں = (ڈیٹا->initial_سائز_rect.دایاں + ڈیٹا->initial_سائز_rect.بایاں - w) / 2;
                }
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                توڑو;
            حالت WMSZ_TOPLEFT:
                clientDragRect.بایاں = clientDragRect.دایاں - w;
                clientDragRect.چوٹی = clientDragRect.bottom - h;
                توڑو;
            حالت WMSZ_BOTTOM:
                اگر (تالا_aspect_تناسب) {
                    clientDragRect.بایاں = (ڈیٹا->initial_سائز_rect.دایاں + ڈیٹا->initial_سائز_rect.بایاں - w) / 2;
                }
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                توڑو;
            حالت WMSZ_BOTTOMRIGHT:
                clientDragRect.دایاں = w + clientDragRect.بایاں;
                clientDragRect.bottom = h + clientDragRect.چوٹی;
                توڑو;
            }

            // convert the client rect to a window rect
            اگر (!Adjust_کھڑکی_Rect_Ex(&clientDragRect, Get_کھڑکی_Style(hwnd), GetMenu(hwnd) != تہی, Get_کھڑکی_Ex_Style(hwnd))) {
                توڑو;
            }

            *dragRect = clientDragRect;
        }
        توڑو;

    حالت WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        اگر (hittest == HTCLIENT) {
            سیٹ_Cursor(SDL_cursor);
            return_رمز = TRUE;
        } ورنہ اگر (!g_کھڑکی_چوکھٹا_Usable_While_Cursor_Hidden && !SDL_cursor) {
            سیٹ_Cursor(تہی);
            return_رمز = TRUE;
        }
    } توڑو;

        // We were occluded, refresh our display
    حالت WM_PAINT:
    {
        RECT rect;
        اگر (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            اگر (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                انتہا_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, تہی);
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }
    }
        return_رمز = 0;
        توڑو;

        // We'll do our own drawing, prevent flicker
    حالت WM_ERASEBKGND:
        اگر (Should_Clear_کھڑکی_On_Erase_Background(ڈیٹا)) {
            RECT client_rect;
            HBRUSH brush;
            ڈیٹا->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        واپس 1;

    حالت WM_SYSCOMMAND:
    {
        اگر (!g_WindowsEnableMenuMnemonics) {
            اگر ((wParam & 0xFFF0) == SC_KEYMENU) {
                واپس 0;
            }
        }

#اگر defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        اگر ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            اگر (SDL_GetVideoDevice()->suspend_screensaver) {
                واپس 0;
            }
        }
#اگر_ختم // System has screensaver support
    } توڑو;

    حالت WM_CLOSE:
    {
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
    }
        return_رمز = 0;
        توڑو;

    حالت WM_TOUCH:
        اگر (ڈیٹا->videodata->Get_Touch_داخلہ_Info && ڈیٹا->videodata->Close_Touch_داخلہ_Handle) {
            UINT i, عدد_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, عدد_inputs, &isstack);
            اگر (inputs && ڈیٹا->videodata->Get_Touch_داخلہ_Info((HTOUCHINPUT)lParam, عدد_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                اعشاری x, y;

                اگر (!GetClientRect(hwnd, &rect) || !WIN_کھڑکی_Rect_Valid(&rect)) {
                    اگر (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    توڑو;
                }
                Client_مقصد_Screen(hwnd, (LPPOINT)&rect);
                Client_مقصد_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.چوٹی *= 100;
                rect.بایاں *= 100;
                rect.bottom *= 100;
                rect.دایاں *= 100;

                برائے (i = 0; i < عدد_inputs; ++i) {
                    PTOUCHINPUT داخلہ = &inputs[i];
                    ثابت صحیح w = (rect.دایاں - rect.بایاں);
                    ثابت صحیح h = (rect.bottom - rect.چوٹی);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)داخلہ->h_ماخذ);
                    ثابت SDL_FingerID fingerId = (داخلہ->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    اگر (SDL_جوڑو_Touch(touchId, SDL_TOUCH_DEVICE_براہ_راست, (داخلہ->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        جاری;
                    }

                    // Get the normalized coordinates for the window
                    اگر (w <= 1) {
                        x = 0.5f;
                    } ورنہ {
                        x = (اعشاری)(داخلہ->x - rect.بایاں) / (w - 1);
                    }
                    اگر (h <= 1) {
                        y = 0.5f;
                    } ورنہ {
                        y = (اعشاری)(داخلہ->y - rect.چوٹی) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    اگر (داخلہ->dwFlags & TOUCHEVENTF_نیچے_کو) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ڈیٹا->کھڑکی, SDL_EVENT_FINGER_نیچے_کو, x, y, 1.0f);
                    }
                    اگر (داخلہ->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, ڈیٹا->کھڑکی, x, y, 1.0f);
                    }
                    اگر (داخلہ->dwFlags & TOUCHEVENTF_اوپر) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, ڈیٹا->کھڑکی, SDL_EVENT_FINGER_اوپر, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            ڈیٹا->videodata->Close_Touch_داخلہ_Handle((HTOUCHINPUT)lParam);
            واپس 0;
        }
        توڑو;

#اگر_تعریف_شدہ HAVE_TPCSHRD_H

    حالت WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        واپس TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#اگر_ختم // HAVE_TPCSHRD_H

    حالت WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT گنتی = DragQueryFile(drop, 0xFFFFFFFF, تہی, 0);
        برائے (i = 0; i < گنتی; ++i) {
            UINT سائز = DragQueryFile(drop, i, تہی, 0) + 1;
            LPTSTR بفر_2 = (LPTSTR)SDL_malloc(حجم(TCHAR) * سائز);
            اگر (بفر_2) {
                اگر (DragQueryFile(drop, i, بفر_2, سائز)) {
                    حرف *file = WIN_String_مقصد_UTF8(بفر_2);
                    SDL_SendDropFile(ڈیٹا->کھڑکی, تہی, file);
                    SDL_free(file);
                }
                SDL_free(بفر_2);
            }
        }
        SDL_SendDropComplete(ڈیٹا->کھڑکی);
        Drag_اختتام(drop);
        واپس 0;
    }

    حالت WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } توڑو;

    حالت WM_NCCALCSIZE:
    {
        SDL_کھڑکی_Flags کھڑکی_flags = ڈیٹا->کھڑکی->flags;
        اگر (wParam == TRUE && (کھڑکی_flags & SDL_کھڑکی_BORDERLESS) && !(کھڑکی_flags & SDL_کھڑکی_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            اگر (Get_کھڑکی_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_کھڑکی(hwnd, MONITOR_DEFAULTTONULL);
                اگر (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت نقطہ_2 pt = { ڈیٹا->کھڑکی->windowed.x, ڈیٹا->کھڑکی->windowed.y };
                    hMonitor = Monitor_From_نقطہ(pt, MONITOR_DEFAULTTONEAREST);
                }
                اگر (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_سائز = حجم(info);
                    اگر (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } ورنہ اگر (!(کھڑکی_flags & SDL_کھڑکی_RESIZABLE) && !ڈیٹا->force_ws_maximizebox) {
                صحیح w, h;
                اگر (ڈیٹا->کھڑکی->آخری_سائز_pending) {
                    w = ڈیٹا->کھڑکی->pending.w;
                    h = ڈیٹا->کھڑکی->pending.h;
                } ورنہ {
                    w = ڈیٹا->کھڑکی->floating.w;
                    h = ڈیٹا->کھڑکی->floating.h;
                }
                params->rgrc[0].دایاں = params->rgrc[0].بایاں + w;
                params->rgrc[0].bottom = params->rgrc[0].چوٹی + h;
            }
            واپس 0;
        }
    } توڑو;

    حالت WM_NCHITTEST:
    {
        SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

        اگر (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
            واپس HTTRANSPARENT;
        }

        اگر (کھڑکی->کامیابی_test) {
            نقطہ_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            اگر (Screen_مقصد_Client(hwnd, &winpoint)) {
                SDL_نقطہ نقطہ;
                SDL_کامیابی_Test_نتیجہ rc;
                نقطہ.x = winpoint.x;
                نقطہ.y = winpoint.y;
                rc = کھڑکی->کامیابی_test(کھڑکی, &نقطہ, کھڑکی->کامیابی_test_ڈیٹا);
                انتخاب (rc) {
#تعریف_کرو POST_کامیابی_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_کامیابی_TEST, 0, 0); \
        واپس ret;                                                        \
    }
                حالت SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(تہی, تہی);
                    اگر (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_سیٹ_Mouse_Focus(کھڑکی);
                        واپس HTCLIENT;
                    }

                    POST_کامیابی_TEST(HTCAPTION);
                }
                حالت SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_کامیابی_TEST(HTTOPLEFT);
                حالت SDL_HITTEST_RESIZE_چوٹی:
                    POST_کامیابی_TEST(HTTOP);
                حالت SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_کامیابی_TEST(HTTOPRIGHT);
                حالت SDL_HITTEST_RESIZE_دایاں:
                    POST_کامیابی_TEST(HTRIGHT);
                حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_کامیابی_TEST(HTBOTTOMRIGHT);
                حالت SDL_HITTEST_RESIZE_BOTTOM:
                    POST_کامیابی_TEST(HTBOTTOM);
                حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_کامیابی_TEST(HTBOTTOMLEFT);
                حالت SDL_HITTEST_RESIZE_بایاں:
                    POST_کامیابی_TEST(HTLEFT);
#تعریف_منسوخ POST_کامیابی_TEST
                حالت SDL_HITTEST_معمول:
                    واپس HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } توڑو;

    حالت WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        اگر (ڈیٹا->videodata->Get_Dpi_For_کھڑکی && ڈیٹا->videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحیح اگلا_DPI = (صحیح)wParam;
            ثابت صحیح پچھلا_DPI = (صحیح)ڈیٹا->videodata->Get_Dpi_For_کھڑکی(hwnd);
            سائز_3 *سائز_اندر_برآمد = (سائز_3 *)lParam;

            صحیح چوکھٹا_w, چوکھٹا_h;
            صحیح query_client_w_win, query_client_h_win;

#اگر_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    پچھلا_DPI, اگلا_DPI, سائز_اندر_برآمد->cx, سائز_اندر_برآمد->cy);
#اگر_ختم

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, پچھلا_DPI);
                }

                چوکھٹا_w = -rect.بایاں + rect.دایاں;
                چوکھٹا_h = -rect.چوٹی + rect.bottom;

                query_client_w_win = سائز_اندر_برآمد->cx - چوکھٹا_w;
                query_client_h_win = سائز_اندر_برآمد->cy - چوکھٹا_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.دایاں = query_client_w_win;
                rect.bottom = query_client_h_win;

                اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, اگلا_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                سائز_اندر_برآمد->cx = rect.دایاں - rect.بایاں;
                سائز_اندر_برآمد->cy = rect.bottom - rect.چوٹی;
            }

#اگر_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", سائز_اندر_برآمد->cx, سائز_اندر_برآمد->cy);
#اگر_ختم
            واپس TRUE;
        }
        توڑو;

    حالت WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحیح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحیح w, h;

#اگر_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->بایاں, suggestedRect->چوٹی, suggestedRect->دایاں - suggestedRect->بایاں, suggestedRect->bottom - suggestedRect->چوٹی);
#اگر_ختم

            اگر (ڈیٹا->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#اگر_تعریف_شدہ HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#اگر_ختم
                واپس 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.دایاں = ڈیٹا->کھڑکی->w;
                rect.bottom = ڈیٹا->کھڑکی->h;

                اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
                    WIN_Adjust_کھڑکی_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.دایاں - rect.بایاں;
                h = rect.bottom - rect.چوٹی;
            }

#اگر_تعریف_شدہ HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    ڈیٹا->کھڑکی->w, ڈیٹا->کھڑکی->h,
                    suggestedRect->بایاں, suggestedRect->چوٹی, w, h);
#اگر_ختم

            ڈیٹا->expected_resize = true;
            سیٹ_کھڑکی_Pos(hwnd,
                         تہی,
                         suggestedRect->بایاں,
                         suggestedRect->چوٹی,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            ڈیٹا->expected_resize = false;
            واپس 0;
        }

    حالت WM_SETTINGCHANGE:
        اگر (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_سیٹ_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_منوال_For_HWND(hwnd);
        }
        اگر (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        اگر (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        توڑو;
#ورنہ
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    حالت WM_سائز:
    {
        RECT rect;
        صحیح w, h;

        اگر (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
            w = rect.دایاں;
            h = rect.bottom;
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, w, h);
        }
    } توڑو;
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    طےشدہ:
        توڑو;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (پیغام_2 && پیغام_2 == ڈیٹا->videodata->WM_TASKBAR_BUTTON_CREATED) {
        ڈیٹا->taskbar_button_created = true;
        WIN_Apply_کھڑکی_پیش_رفت(SDL_GetVideoDevice(), ڈیٹا->کھڑکی);
    }
#اگر_ختم

    // If there's a window proc, assume it's going to handle messages
    اگر (ڈیٹا->wndproc) {
        واپس Call_کھڑکی_Proc(ڈیٹا->wndproc, hwnd, پیغام_2, wParam, lParam);
    } ورنہ اگر (return_رمز >= 0) {
        واپس return_رمز;
    } ورنہ {
        واپس Call_کھڑکی_Proc(Def_کھڑکی_Proc, hwnd, پیغام_2, wParam, lParam);
    }
}

صحیح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    اگر (g_Windows_Enable_پیغام_Loop) {
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_مقصد_MS(timeoutNS);
        ret = پیغام_Wait_For_مضرب_Objects(0, تہی, FALSE, timeout, QS_ALLINPUT);
        اگر (ret == WAIT_OBJECT_0) {
            واپس 1;
        } ورنہ {
            واپس 0;
        }
#ورنہ
        // MsgWaitForMultipleObjects is desktop-only.
        پیغام_3 پیغام_2;
        BOOL پیغام_نتیجہ;
        UINT_PTR timer_id = 0;
        اگر (timeoutNS > 0) {
            timer_id = سیٹ_Timer(تہی, 0, (UINT)SDL_NS_مقصد_MS(timeoutNS), تہی);
            پیغام_نتیجہ = Get_پیغام(&پیغام_2, 0, 0, 0);
            KillTimer(تہی, timer_id);
        } ورنہ اگر (timeoutNS == 0) {
            پیغام_نتیجہ = Peek_پیغام(&پیغام_2, تہی, 0, 0, PM_REMOVE);
        } ورنہ {
            پیغام_نتیجہ = Get_پیغام(&پیغام_2, 0, 0, 0);
        }
        اگر (پیغام_نتیجہ) {
            اگر (پیغام_2.پیغام == WM_TIMER && !پیغام_2.hwnd && پیغام_2.wParam == timer_id) {
                واپس 0;
            }
            اگر (g_Windows_پیغام_Hook) {
                اگر (!g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_ڈیٹا, &پیغام_2)) {
                    واپس 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
            واپس 1;
        } ورنہ {
            واپس 0;
        }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } ورنہ {
        // Fail the wait so the caller falls back to polling
        واپس -1;
    }
}

خالی WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Post_پیغام(ڈیٹا->hwnd, ڈیٹا->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
خالی WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    پیغام_3 پیغام_2;

    اگر (g_Windows_Enable_پیغام_Loop) {
        SDL_processing_messages = true;

        جب (Peek_پیغام(&پیغام_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_سیٹ_پیغام_Tick(پیغام_2.وقت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
        }

        SDL_processing_messages = false;
    }
}

خالی WIN_PumpEvents(SDL_VideoDevice *_this)
{
    پیغام_3 پیغام_2;
#اگر_تعریف_شدہ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ہدایت warning(ڈالو)
#ہدایت warning(disable : 28159)
#اگر_ختم
    DWORD انتہا_ticks = Get_Tick_گنتی() + 1;
#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#اگر_ختم
    صحیح new_messages = 0;

    اگر (_this->اندرونی_2->gameinput_context) {
        WIN_Update_Game_داخلہ(_this);
    }

    اگر (g_Windows_Enable_پیغام_Loop) {
        SDL_processing_messages = true;

        جب (Peek_پیغام(&پیغام_2, تہی, 0, 0, PM_REMOVE)) {
            اگر (g_Windows_پیغام_Hook) {
                اگر (!g_Windows_پیغام_Hook(g_Windows_پیغام_Hook_ڈیٹا, &پیغام_2)) {
                    جاری;
                }
            }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            اگر (پیغام_2.پیغام == WM_MOUSEMOVE && SDL_آخری_warp_وقت) {
                اگر (!SDL_TICKS_PASSED(پیغام_2.وقت, (SDL_آخری_warp_وقت + 1))) {
                    جاری;
                }

                // This mouse message happened after the warp
                SDL_آخری_warp_وقت = 0;
            }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_سیٹ_پیغام_Tick(پیغام_2.وقت);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            اگر (SDL_TICKS_PASSED(پیغام_2.وقت, انتہا_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ثابت صحیح MAX_NEW_MESSAGES = 3;
                ++new_messages;
                اگر (new_messages > MAX_NEW_MESSAGES) {
                    توڑو;
                }
            }
        }

        SDL_processing_messages = false;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ثابت bool *keystate = SDL_GetKeyboardState(تہی);
    اگر (keystate[SDL_SCANCODE_LSHIFT] && !(Get_کلید_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    اگر (keystate[SDL_SCANCODE_RSHIFT] && !(Get_کلید_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_کھڑکی *focus_کھڑکی = SDL_GetKeyboardFocus();
    اگر (!focus_کھڑکی || !(focus_کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        اگر (keystate[SDL_SCANCODE_LGUI] && !(Get_کلید_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        اگر (keystate[SDL_SCANCODE_RGUI] && !(Get_کلید_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    اگر (_this) {
        SDL_کھڑکی *کھڑکی = _this->windows;
        جب (کھڑکی) {
            bool refresh_clipcursor = false;
            SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
            اگر (ڈیٹا) {
                refresh_clipcursor = ڈیٹا->clipcursor_queued;
                ڈیٹا->clipcursor_queued = false;    // Must be cleared unconditionally.
                ڈیٹا->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            اگر (refresh_clipcursor) {
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
    اگر (focus_کھڑکی && (focus_کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = focus_کھڑکی->اندرونی_2;

        اگر (!ڈیٹا->mouse_tracked) {
            نقطہ_2 cursorPos;

            اگر (GetCursorPos(&cursorPos) && Screen_مقصد_Client(ڈیٹا->hwnd, &cursorPos)) {
                bool تبادلہ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID,
                                    !تبادلہ_Buttons ? SDL_BUTTON_بایاں : SDL_BUTTON_دایاں,
                                    (Get_Async_کلید_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID,
                                    !تبادلہ_Buttons ? SDL_BUTTON_دایاں : SDL_BUTTON_بایاں,
                                    (Get_Async_کلید_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID,
                                    SDL_BUTTON_درمیان,
                                    (Get_Async_کلید_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_کلید_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), ڈیٹا->کھڑکی, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_کلید_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شدہ SDL_PLATFORM_GDK
    GDK_Dispatch_Task_قطار();
#اگر_ختم
}

ساکن صحیح app_registered = 0;
LPTSTR SDL_Appname = تہی;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = تہی;

ساکن خالی WIN_Clean_رجسٹر_App(WNDCLASSEX wcex)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    اگر (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#اگر_ختم
    SDL_free(SDL_Appname);
    SDL_Appname = تہی;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساکن BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (خالی)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = بھرو_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    واپس FALSE;
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_رجسٹر_App(ثابت حرف *name, Uint32 style, خالی *hInst)
{
    WNDCLASSEX wcex;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#اگر_ختم

    // Only do this once...
    اگر (app_registered) {
        ++app_registered;
        واپس true;
    }
    SDL_assert(!SDL_Appname);
    اگر (!name) {
        name = "SDL_app";
#اگر defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#اگر_ختم
    }
    SDL_Appname = WIN_UTF8_مقصد_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(تہی);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_سائز = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_کھڑکی_Proc;
    wcex.hInstance = SDL_Instance;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    اگر (hint && *hint) {
        wcex.hIcon = بھرو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        اگر (hint && *hint) {
            wcex.hIconSm = بھرو_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } ورنہ {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_نام(SDL_Instance, RT_گروہ_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    اگر (!رجسٹر_Class_Ex(&wcex)) {
        WIN_Clean_رجسٹر_App(wcex);
        واپس SDL_سیٹ_Error("Couldn't register application class");
    }

    app_registered = 1;
    واپس true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
خالی SDL_UnregisterApp(خالی)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    اگر (!app_registered) {
        واپس;
    }
    --app_registered;
    اگر (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = تہی;
        wcex.hIconSm = تہی;
        // Check for any registered window classes.
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#اگر_ختم
        WIN_Clean_رجسٹر_App(wcex);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
