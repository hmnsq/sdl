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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_touch_c.h"
#অন্তর্ভাব "../../events/scancodes_windows.h"
#অন্তর্ভাব "../../main/SDL_main_callbacks.h"
#অন্তর্ভাব "../../core/windows/SDL_hid.h"

// Dropfile support
#অন্তর্ভাব <shellapi.h>

// Device names
#অন্তর্ভাব <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#অন্তর্ভাব <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ifdef HAVE_TPCSHRD_H
#অন্তর্ভাব <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#যদি 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "wmmsg.h"
#endif

#যদি !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#অন্তর্ভাব <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#অন্তর্ভাব "../../core/gdk/SDL_gdk.h"
#endif

// #define HIGHDPI_DEBUG

// Undocumented window messages
#ifndef WM_NCUAHDRAWCAPTION
#define WM_NCUAHDRAWCAPTION 0xAE
#endif
#ifndef WM_NCUAHDRAWFRAME
#define WM_NCUAHDRAWFRAME 0xAF
#endif

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 0x020B
#endif
#ifndef WM_XBUTTONUP
#define WM_XBUTTONUP 0x020C
#endif
#ifndef GET_XBUTTON_WPARAM
#define GET_XBUTTON_WPARAM(w) (HIWORD(w))
#endif
#ifndef WM_প্রবেশ
#define WM_প্রবেশ 0x00ff
#endif
#ifndef WM_TOUCH
#define WM_TOUCH 0x0240
#endif
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef RI_MOUSE_HWHEEL
#define RI_MOUSE_HWHEEL 0x0800
#endif
#ifndef WM_POINTERUPDATE
#define WM_POINTERUPDATE 0x0245
#endif
#ifndef WM_POINTERDOWN
#define WM_POINTERDOWN 0x0246
#endif
#ifndef WM_POINTERUP
#define WM_POINTERUP 0x0247
#endif
#ifndef WM_POINTERENTER
#define WM_POINTERENTER 0x0249
#endif
#ifndef WM_POINTERLEAVE
#define WM_POINTERLEAVE 0x024A
#endif
#ifndef WM_POINTERCAPTURECHANGED
#define WM_POINTERCAPTURECHANGED 0x024C
#endif
#ifndef WM_UNICHAR
#define WM_UNICHAR 0x0109
#endif
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif
#ifndef WM_GETDPISCALEDSIZE
#define WM_GETDPISCALEDSIZE 0x02E4
#endif
#ifndef TOUCHEVENTF_PEN
#define TOUCHEVENTF_PEN 0x0040
#endif

#ifndef MAPVK_VK_TO_VSC_EX
#define MAPVK_VK_TO_VSC_EX 4
#endif

#ifndef WC_ERR_INVALID_CHARS
#define WC_ERR_INVALID_CHARS 0x00000080
#endif

#ifndef IS_উপরের_SURROGATE
#define IS_উপরের_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
প্রকারলেখ Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

স্থির bool SDL_processing_messages;
স্থির DWORD message_tick;
স্থির Uint64 timestamp_offset;

স্থির শূন্য WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

স্থির Uint64 WIN_GetEventTimestamp(শূন্য)
{
    ধ্রুবক Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    যদি (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        ফেরত 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    যদি (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } অন্যথা যদি ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } অন্যথা যদি (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    ফেরত timestamp;
}

// A message hook called before TranslateMessage()
স্থির SDL_WindowsMessageHook g_WindowsMessageHook = ফাঁকা;
স্থির শূন্য *g_Windows_Message_Hook_তথ্য = ফাঁকা;

শূন্য SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, শূন্য *userdata)
{
    g_WindowsMessageHook = callback;
    g_Windows_Message_Hook_তথ্য = userdata;
}

স্থির SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_চাবি)
{
    SDL_Scancode code;
    Uint8 সূচক;
    Uint16 চাবি_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(চাবি_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_চাবি = (scanCode == 0);

    যদি (scanCode != 0) {
        যদি ((চাবি_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } অন্যথা যদি (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } অন্যথা {
        Uint16 vkCode = LOWORD(wParam);

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_চাবি(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        যদি (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    সূচক = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[সূচক];
    *rawcode = scanCode;

    ফেরত code;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
স্থির bool WIN_ShouldIgnoreFocusClick(SDL_Window_তথ্য *তথ্য)
{
    ফেরত !SDL_WINDOW_IS_POPUP(তথ্য->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

স্থির শূন্য WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_Window_তথ্য *তথ্য, Uint8 button, SDL_MouseID mouseID)
{
    যদি (bSwapButtons) {
        যদি (button == SDL_BUTTON_বাম) {
            button = SDL_BUTTON_ডান;
        } অন্যথা যদি (button == SDL_BUTTON_ডান) {
            button = SDL_BUTTON_বাম;
        }
    }

    যদি (তথ্য->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        যদি (!bwParamMousePressed) {
            তথ্য->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(তথ্য->window);
        }
        ফেরত;
    }

    যদি (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, তথ্য->window, mouseID, button, true);
    } অন্যথা যদি (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, তথ্য->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
স্থির শূন্য WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_Window_তথ্য *তথ্য, SDL_MouseID mouseID)
{
    যদি (wParam != তথ্য->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(ফাঁকা, ফাঁকা);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, তথ্য, SDL_BUTTON_বাম, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, তথ্য, SDL_BUTTON_মধ্য, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, তথ্য, SDL_BUTTON_ডান, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, তথ্য, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, তথ্য, SDL_BUTTON_X2, mouseID);

        তথ্য->mouse_button_flags = wParam;
    }
}

স্থির শূন্য WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_Window_তথ্য *তথ্য)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT চাবি_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(ফাঁকা, ফাঁকা);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    চাবি_State = Get_Async_চাবি_State(VK_LBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, তথ্য, SDL_BUTTON_বাম, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_RBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, তথ্য, SDL_BUTTON_ডান, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_MBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, তথ্য, SDL_BUTTON_মধ্য, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_XBUTTON1);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, তথ্য, SDL_BUTTON_X1, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_XBUTTON2);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, তথ্য, SDL_BUTTON_X2, mouseID);
    }
    তথ্য->mouse_button_flags = (WPARAM)-1;
}

স্থির শূন্য WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    HWND hwnd = তথ্য->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    যদি (had_focus == has_focus || has_focus != expect_focus) {
        ফেরত;
    }

    যদি (has_focus) {
        POINT cursorPos;

        যদি (WIN_ShouldIgnoreFocusClick(তথ্য) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            যদি (Get_Async_চাবি_State(VK_LBUTTON)) {
                তথ্য->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            যদি (Get_Async_চাবি_State(VK_RBUTTON)) {
                তথ্য->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            যদি (Get_Async_চাবি_State(VK_MBUTTON)) {
                তথ্য->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            যদি (Get_Async_চাবি_State(VK_XBUTTON1)) {
                তথ্য->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            যদি (Get_Async_চাবি_State(VK_XBUTTON2)) {
                তথ্য->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        যদি (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)cursorPos.x, (দশমিক)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), তথ্য);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(তথ্য->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_চাবি_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_অঙ্ক, (Get_চাবি_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_চাবি_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(তথ্য->window, true);
    } অন্যথা {
        তথ্য->in_window_deactivation = true;

        SDL_SetKeyboardFocus(ফাঁকা);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        যদি (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(ফাঁকা);
        }
        WIN_Reset_Dead_চাবিগুলি();

        WIN_UnclipCursorForWindow(window);

        তথ্য->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

স্থির bool ShouldGenerateWindowCloseOnAltF4(শূন্য)
{
    ফেরত SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

স্থির bool ShouldClearWindowOnEraseBackground(SDL_Window_তথ্য *তথ্য)
{
    নির্বাচন (তথ্য->hint_erase_background_mode) {
    ক্ষেত্র SDL_ERASEBACKGROUNDMODE_NEVER:
        ফেরত false;
    ক্ষেত্র SDL_ERASEBACKGROUNDMODE_INITIAL:
        ফেরত !তথ্য->videodata->cleared;
    ক্ষেত্র SDL_ERASEBACKGROUNDMODE_ALWAYS:
        ফেরত true;
    পূর্বনির্ধারিত:
        // Unexpected value, fallback to default behaviour
        ফেরত !তথ্য->videodata->cleared;
    }
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

প্রকারলেখ গণনা
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

স্থির SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    যদি (IsTouchEvent(extrainfo)) {
        যদি (extrainfo & 0x80) {
            ফেরত SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } অন্যথা {
            ফেরত SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    ফেরত SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

স্থির SDL_Window_তথ্য *WIN_Get_Window_তথ্য_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    যদি (_this) {
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            SDL_Window_তথ্য *তথ্য = window->internal;
            যদি (তথ্য && তথ্য->hwnd == hwnd) {
                ফেরত তথ্য;
            }
        }
    }
    ফেরত ফাঁকা;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(পূর্ণসংখ্যা nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_তথ্য = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_তথ্য *তথ্য = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    যদি (nCode < 0 || nCode != HC_ACTION) {
        ফেরত Call_পরবর্তী_Hook_Ex(ফাঁকা, nCode, wParam, lParam);
    }
    যদি (hook_তথ্য->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        ফেরত 1;
    }

    নির্বাচন (hook_তথ্য->vkCode) {
    ক্ষেত্র VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        বিরতি;
    ক্ষেত্র VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        বিরতি;
    ক্ষেত্র VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        বিরতি;
    ক্ষেত্র VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        বিরতি;
    ক্ষেত্র VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        বিরতি;
    ক্ষেত্র VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        বিরতি;
    ক্ষেত্র VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        বিরতি;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    ক্ষেত্র VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        বিরতি;
    ক্ষেত্র VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        বিরতি;

    পূর্বনির্ধারিত:
        ফেরত Call_পরবর্তী_Hook_Ex(ফাঁকা, nCode, wParam, lParam);
    }

    যদি (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        যদি (!তথ্য->raw_keyboard_enabled) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, hook_তথ্য->scanCode, scanCode, true);
        }
    } অন্যথা {
        যদি (!তথ্য->raw_keyboard_enabled) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, hook_তথ্য->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        যদি (hook_তথ্য->vkCode <= 0xFF && তথ্য->pre_hook_চাবি_state[hook_তথ্য->vkCode]) {
            তথ্য->pre_hook_চাবি_state[hook_তথ্য->vkCode] = 0;
            ফেরত Call_পরবর্তী_Hook_Ex(ফাঁকা, nCode, wParam, lParam);
        }
    }

    ফেরত 1;
}

স্থির bool WIN_SwapButtons(HANDLE hDevice)
{
    যদি (hDevice == ফাঁকা) {
        // Touchpad, already has buttons swapped
        ফেরত false;
    }
    ফেরত GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

স্থির শূন্য WIN_Handle_Raw_Mouse_প্রবেশ(Uint64 timestamp, SDL_Video_তথ্য *তথ্য, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    স্থির কাঠামো {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_বাম_BUTTON_DOWN, SDL_BUTTON_বাম, true },
        { RI_MOUSE_বাম_BUTTON_UP, SDL_BUTTON_বাম, false },
        { RI_MOUSE_ডান_BUTTON_DOWN, SDL_BUTTON_ডান, true },
        { RI_MOUSE_ডান_BUTTON_UP, SDL_BUTTON_ডান, false },
        { RI_MOUSE_মধ্য_BUTTON_DOWN, SDL_BUTTON_মধ্য, true },
        { RI_MOUSE_মধ্য_BUTTON_UP, SDL_BUTTON_মধ্য, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    পূর্ণসংখ্যা dx = (পূর্ণসংখ্যা)rawmouse->lLastX;
    পূর্ণসংখ্যা dy = (পূর্ণসংখ্যা)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    যদি (!তথ্য->raw_mouse_enabled) {
        ফেরত;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    যদি (!window) {
        ফেরত;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    যদি (!mouse) {
        ফেরত;
    }

    যদি (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        ফেরত;
    }

    SDL_Window_তথ্য *windowdata = window->internal;

    যদি (haveMotion && !windowdata->in_modal_loop) {
        যদি (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (দশমিক)dx, (দশমিক)dy);
        } অন্যথা {
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
            পূর্ণসংখ্যা w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            পূর্ণসংখ্যা h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            পূর্ণসংখ্যা x = raw_coordinates ? dx : (পূর্ণসংখ্যা)(((দশমিক)dx / 65535.0f) * w);
            পূর্ণসংখ্যা y = raw_coordinates ? dy : (পূর্ণসংখ্যা)(((দশমিক)dy / 65535.0f) * h);
            পূর্ণসংখ্যা relX, relY;

            /* Calculate relative motion */
            যদি (তথ্য->last_raw_mouse_position.x == 0 && তথ্য->last_raw_mouse_position.y == 0) {
                তথ্য->last_raw_mouse_position.x = x;
                তথ্য->last_raw_mouse_position.y = y;
            }
            relX = x - তথ্য->last_raw_mouse_position.x;
            relY = y - তথ্য->last_raw_mouse_position.y;

            যদি (remote_desktop) {
                যদি (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    স্থির পূর্ণসংখ্যা wobble;
                    দশমিক floatX = (দশমিক)x / w;
                    দশমিক floatY = (দশমিক)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    যদি (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        পূর্ণসংখ্যা warpX = rect.বাম + ((rect.ডান - rect.বাম) / 2) + wobble;
                        পূর্ণসংখ্যা warpY = rect.শীর্ষ + ((rect.bottom - rect.শীর্ষ) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        যদি (wobble > 1) {
                            wobble = -1;
                        }
                    } অন্যথা {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ধ্রুবক পূর্ণসংখ্যা MAX_RELATIVE_MOTION = (h / 6);
                        যদি (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (দশমিক)relX, (দশমিক)relY);
                        }
                    }
                }
            } অন্যথা যদি (mouse->pen_mouse_events) {
                ধ্রুবক পূর্ণসংখ্যা MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                যদি (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } অন্যথা {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (দশমিক)relX, (দশমিক)relY);
                }
            } অন্যথা {
                পূর্ণসংখ্যা screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                পূর্ণসংখ্যা screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                যদি (!তথ্য->raw_প্রবেশ_fake_pen_id) {
                    তথ্য->raw_প্রবেশ_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, ফাঁকা, (শূন্য *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, তথ্য->raw_প্রবেশ_fake_pen_id, window, (দশমিক)(x + screen_x - window->x), (দশমিক)(y + screen_y - window->y));
            }

            তথ্য->last_raw_mouse_position.x = x;
            তথ্য->last_raw_mouse_position.y = y;
        }
    }

    যদি (haveButton) {
        জন্য (পূর্ণসংখ্যা i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            যদি (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                যদি (button == SDL_BUTTON_বাম) {
                    যদি (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_ডান;
                    }
                } অন্যথা যদি (button == SDL_BUTTON_ডান) {
                    যদি (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_বাম;
                    }
                }

                যদি (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    যদি (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    চালু;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        যদি (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_তথ্য;
            দশমিক fAmount = (দশমিক)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } অন্যথা যদি (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_তথ্য;
            দশমিক fAmount = (দশমিক)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

স্থির শূন্য WIN_Handle_Raw_Keyboard_প্রবেশ(Uint64 timestamp, SDL_Video_তথ্য *তথ্য, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    যদি (!তথ্য->raw_keyboard_enabled) {
        ফেরত;
    }

    যদি (rawkeyboard->Flags & RI_চাবি_E1) {
        // First key in a Ctrl+{key} sequence
        তথ্য->pending_E1_চাবি_sequence = true;
        ফেরত;
    }

    যদি ((rawkeyboard->Flags & RI_চাবি_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        ফেরত;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_চাবি(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    যদি (!rawkeyboard->MakeCode) {
        ফেরত;
    }

    bool down;
    নির্বাচন (rawkeyboard->Message) {
    ক্ষেত্র WM_KEYDOWN:
    ক্ষেত্র WM_SYSKEYDOWN:
        down = true;
        বিরতি;
    ক্ষেত্র WM_KEYUP:
    ক্ষেত্র WM_SYSKEYUP:
        down = false;
        বিরতি;
    পূর্বনির্ধারিত:
        down = !(rawkeyboard->Flags & RI_চাবি_BREAK);
        বিরতি;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    যদি (তথ্য->pending_E1_চাবি_sequence) {
        rawcode |= 0xE100;
        যদি (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } অন্যথা {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        তথ্য->pending_E1_চাবি_sequence = false;
    } অন্যথা {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 সূচক = (Uint8)rawkeyboard->MakeCode;
        যদি (rawkeyboard->Flags & RI_চাবি_E0) {
            rawcode |= 0xE000;
            সূচক |= 0x80;
        }
        code = windows_scancode_table[সূচক];
    }

    যদি (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        যদি ((!তথ্য->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_প্রবেশ_active)) {
            ফেরত;
        }
    }

    SDL_Send_Keyboard_চাবি(timestamp, keyboardID, rawcode, code, down);
}

শূন্য WIN_Poll_Raw_প্রবেশ(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    UINT আকার_2, i, গুনতি, যোগ = 0;
    RAWINPUT *প্রবেশ;
    Uint64 poll_finish;

    যদি (তথ্য->rawinput_offset == 0) {
        BOOL isWow64;

        তথ্য->rawinput_offset = আকার(RAWINPUTHEADER);
        যদি (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            তথ্য->rawinput_offset += 8;
        }
    }

    // Get all available events
    প্রবেশ = (RAWINPUT *)তথ্য->rawinput;
    জন্য (;;) {
        আকার_2 = তথ্য->rawinput_আকার - (UINT)((BYTE *)প্রবেশ - তথ্য->rawinput);
        গুনতি = Get_Raw_প্রবেশ_বাফার(প্রবেশ, &আকার_2, আকার(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        যদি (গুনতি == 0 || গুনতি == (UINT)-1) {
            যদি (!তথ্য->rawinput || (গুনতি == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_বাফার)) {
                ধ্রুবক UINT RAWINPUT_বাফার_আকার_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(তথ্য->rawinput, তথ্য->rawinput_আকার + RAWINPUT_বাফার_আকার_INCREMENT);
                যদি (!rawinput) {
                    বিরতি;
                }
                প্রবেশ = (RAWINPUT *)(rawinput + ((BYTE *)প্রবেশ - তথ্য->rawinput));
                তথ্য->rawinput = rawinput;
                তথ্য->rawinput_আকার += RAWINPUT_বাফার_আকার_INCREMENT;
            } অন্যথা {
                বিরতি;
            }
        } অন্যথা {
            যোগ += গুনতি;

            // Advance input to the end of the buffer
            যখন (গুনতি--) {
                প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ);
            }
        }
    }

    যদি (যোগ > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_যোগ = 0;
        জন্য (i = 0, প্রবেশ = (RAWINPUT *)তথ্য->rawinput; i < যোগ; ++i, প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ)) {
            যদি (প্রবেশ->header.dwType == RIM_TYPEMOUSE) {
                mouse_যোগ += 1;
            }
        }
        পূর্ণসংখ্যা mouse_সূচক = 0;
        জন্য (i = 0, প্রবেশ = (RAWINPUT *)তথ্য->rawinput; i < যোগ; ++i, প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ)) {
            যদি (প্রবেশ->header.dwType == RIM_TYPEMOUSE) {
                mouse_সূচক += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)প্রবেশ + তথ্য->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_যোগ - mouse_সূচক)) / mouse_যোগ;
                WIN_Handle_Raw_Mouse_প্রবেশ(time, তথ্য, প্রবেশ->header.hDevice, rawmouse);
            } অন্যথা যদি (প্রবেশ->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)প্রবেশ + তথ্য->rawinput_offset);
                WIN_Handle_Raw_Keyboard_প্রবেশ(poll_finish, তথ্য, প্রবেশ->header.hDevice, rawkeyboard);
            }
        }
    }
    তথ্য->last_rawinput_poll = poll_finish;
}

স্থির শূন্য AddDeviceID(Uint32 deviceID, Uint32 **list, পূর্ণসংখ্যা *গুনতি)
{
    পূর্ণসংখ্যা new_গুনতি = (*গুনতি + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_গুনতি * আকার(*new_list));
    যদি (!new_list) {
        // Oh well, we'll drop this one
        ফেরত;
    }
    new_list[new_গুনতি - 1] = deviceID;

    *গুনতি = new_গুনতি;
    *list = new_list;
}

স্থির bool HasDeviceID(Uint32 deviceID, ধ্রুবক Uint32 *list, পূর্ণসংখ্যা গুনতি)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < গুনতি; ++i) {
        যদি (deviceID == list[i]) {
            ফেরত true;
        }
    }
    ফেরত false;
}

স্থির অক্ষর *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ধ্রুবক অক্ষর *instance, Uint16 vendor, Uint16 product, ধ্রুবক অক্ষর *default_name, bool hid_loaded)
{
    অক্ষর *vendor_name = ফাঁকা;
    অক্ষর *product_name = ফাঁকা;
    অক্ষর *name = ফাঁকা;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    যদি (hid_loaded) {
        অক্ষর devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = আকার(devName) - 1;
        UINT len = Get_Raw_প্রবেশ_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        যদি (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, ফাঁকা, OPEN_EXISTING, 0, ফাঁকা);
            যদি (hFile != INVALID_HANDLE_মান) {
                SDL_HidD_GetManufacturerString(hFile, vend, আকার(vend));
                SDL_HidD_GetProductString(hFile, prod, আকার(prod));
                CloseHandle(hFile);
            }
        }
    }

    যদি (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    যদি (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } অন্যথা {
        SP_DEVINFO_তথ্য তথ্য;
        SDL_zero(তথ্য);
        তথ্য.cb_আকার = আকার(তথ্য);
        জন্য (DWORD i = 0;; ++i) {
            যদি (!SetupDiEnumDeviceInfo(devinfo, i, &তথ্য)) {
                যদি (GetLastError() == ERROR_NO_MORE_বস্তুসমূহ) {
                    বিরতি;
                } অন্যথা {
                    চালু;
                }
            }

            অক্ষর DeviceInstanceId[64];
            যদি (!SetupDiGetDeviceInstanceIdA(devinfo, &তথ্য, DeviceInstanceId, আকার(DeviceInstanceId), ফাঁকা))
                চালু;

            যদি (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD আকার_2 = 0;
                যদি (SetupDiGetDeviceRegistryPropertyW(devinfo, &তথ্য, SPDRP_DEVICEDESC, ফাঁকা, (PBYTE)prod, আকার(prod), &আকার_2)) {
                    // Make sure the device description is null terminated
                    আকার_2 /= আকার(*prod);
                    যদি (আকার_2 >= SDL_arraysize(prod)) {
                        // Truncated description...
                        আকার_2 = (SDL_arraysize(prod) - 1);
                    }
                    prod[আকার_2] = 0;

                    যদি (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } অন্যথা {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                বিরতি;
            }
        }
    }

    যদি (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    ফেরত name;
}

শূন্য WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = ফাঁকা;
    UINT raw_device_গুনতি = 0;
    পূর্ণসংখ্যা old_keyboard_গুনতি = 0;
    SDL_KeyboardID *old_keyboards = ফাঁকা;
    পূর্ণসংখ্যা new_keyboard_গুনতি = 0;
    SDL_KeyboardID *new_keyboards = ফাঁকা;
    পূর্ণসংখ্যা old_mouse_গুনতি = 0;
    SDL_MouseID *old_mice = ফাঁকা;
    পূর্ণসংখ্যা new_mouse_গুনতি = 0;
    SDL_MouseID *new_mice = ফাঁকা;

    যদি (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        ফেরত;
    }

    যদি ((Get_Raw_প্রবেশ_Device_List(ফাঁকা, &raw_device_গুনতি, আকার(RAWINPUTDEVICELIST)) == -1) || (!raw_device_গুনতি)) {
        ফেরত; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(আকার(RAWINPUTDEVICELIST) * raw_device_গুনতি);
    যদি (!raw_devices) {
        ফেরত; // oh well.
    }

    raw_device_গুনতি = Get_Raw_প্রবেশ_Device_List(raw_devices, &raw_device_গুনতি, আকার(RAWINPUTDEVICELIST));
    যদি (raw_device_গুনতি == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = ফাঁকা;
        ফেরত; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(ফাঁকা, ফাঁকা, ফাঁকা, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_গুনতি);
    old_mice = SDL_GetMice(&old_mouse_গুনতি);

    জন্য (UINT i = 0; i < raw_device_গুনতি; i++) {
        RID_DEVICE_INFO rdi;
        অক্ষর devName[MAX_PATH] = { 0 };
        UINT rdi_আকার = আকার(rdi);
        UINT name_আকার = SDL_arraysize(devName);
        পূর্ণসংখ্যা vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        অক্ষর *instance, *ptr, *name;

        যদি (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            চালু;
        }

        rdi.cb_আকার = আকার(rdi);
        যদি (Get_Raw_প্রবেশ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_আকার) == ((UINT)-1) ||
            Get_Raw_প্রবেশ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_আকার) == ((UINT)-1)) {
            চালু;
        }

        // Extract the device instance
        instance = devName;
        যখন (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        জন্য (ptr = instance; *ptr; ++ptr) {
            যদি (*ptr == '#') {
                *ptr = '\\';
            }
            যদি (*ptr == '{') {
                যদি (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                বিরতি;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        নির্বাচন (dwType) {
        ক্ষেত্র RIM_TYPEKEYBOARD:
            যদি (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_সংখ্যা_Of_চাবিগুলি_যোগ)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_গুনতি);
                যদি (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_গুনতি)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            বিরতি;
        ক্ষেত্র RIM_TYPEMOUSE:
            যদি (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_গুনতি);
                যদি (!HasDeviceID(mouseID, old_mice, old_mouse_গুনতি)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            বিরতি;
        পূর্বনির্ধারিত:
            বিরতি;
        }
    }

    জন্য (পূর্ণসংখ্যা i = old_keyboard_গুনতি; i--;) {
        যদি (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_গুনতি)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    জন্য (পূর্ণসংখ্যা i = old_mouse_গুনতি; i--;) {
        যদি (!HasDeviceID(old_mice[i], new_mice, new_mouse_গুনতি)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    SetupDiDestroyDeviceInfoList(devinfo);

    SDL_free(raw_devices);
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
স্থির bool Skip_Alt_Gr_বাম_Control(WPARAM wParam, LPARAM lParam)
{
    যদি (wParam != VK_CONTROL) {
        ফেরত false;
    }

    // Is this an extended key (i.e. right key)?
    যদি (lParam & 0x01000000) {
        ফেরত false;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    বার্তা_2 পরবর্তী_বার্তা;
    DWORD বার্তা_time = GetMessageTime();
    যদি (PeekMessage(&পরবর্তী_বার্তা, ফাঁকা, 0, 0, PM_NOREMOVE)) {
        যদি (পরবর্তী_বার্তা.message == WM_KEYDOWN ||
            পরবর্তী_বার্তা.message == WM_SYSKEYDOWN) {
            যদি (পরবর্তী_বার্তা.wParam == VK_MENU && (পরবর্তী_বার্তা.lParam & 0x01000000) && পরবর্তী_বার্তা.time == বার্তা_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                ফেরত true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ফেরত false;
}

স্থির bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *বার্তা, WPARAM *wParam, LPARAM *lParam)
{
    বার্তা_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *বার্তা;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    যদি (g_WindowsMessageHook(g_Windows_Message_Hook_তথ্য, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *বার্তা = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        ফেরত true;
    }
    ফেরত false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM lParam)
{
    SDL_Window_তথ্য *তথ্য;
    LRESULT returnCode = -1;

    // Get the window data for the window
    তথ্য = WIN_Get_Window_তথ্য_From_HWND(hwnd);
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (!তথ্য) {
        // Fallback
        তথ্য = (SDL_Window_তথ্য *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    যদি (!তথ্য) {
        ফেরত CallWindowProc(DefWindowProc, hwnd, বার্তা, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        অক্ষর message[1024];
        যদি (বার্তা > MAX_WMMSG) {
            SDL_snprintf(message, আকার(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, বার্তা, wParam, lParam);
        } অন্যথা {
            SDL_snprintf(message, আকার(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[বার্তা], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    যদি (g_WindowsMessageHook && তথ্য->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        যদি (!DispatchModalLoopMessageHook(&hwnd, &বার্তা, &wParam, &lParam)) {
            ফেরত 0;
        }
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (WIN_HandleIMEMessage(hwnd, বার্তা, wParam, &lParam, তথ্য->videodata)) {
        ফেরত 0;
    }
#endif

    নির্বাচন (বার্তা) {

    ক্ষেত্র WM_SHOWWINDOW:
    {
        যদি (wParam) {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } অন্যথা {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } বিরতি;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ক্ষেত্র WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        তথ্য->postpone_clipcursor = true;
        তথ্য->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        POINT pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(তথ্য->window, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        যদি (তথ্য->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } বিরতি;

    ক্ষেত্র WM_NCUAHDRAWCAPTION:
    ক্ষেত্র WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        যদি (তথ্য->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } বিরতি;

    ক্ষেত্র WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ধ্রুবক DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(তথ্য->window, !!LOWORD(wParam), &pos);
    } বিরতি;

    ক্ষেত্র WM_MOUSEACTIVATE:
    {
        যদি (SDL_WINDOW_IS_POPUP(তথ্য->window)) {
            ফেরত MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = তথ্য->window->parent;
        যখন (parent) {
            যদি ((parent->flags & SDL_WINDOW_প্রবেশ_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                ফেরত MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } বিরতি;

    ক্ষেত্র WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ধ্রুবক DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(তথ্য->window, true, &pos);
    } বিরতি;

    ক্ষেত্র WM_KILLFOCUS:
    ক্ষেত্র WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ধ্রুবক DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(তথ্য->window, false, &pos);
    } বিরতি;

    ক্ষেত্র WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুবক UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!তথ্য->videodata->GetPointerType) {
            বিরতি;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } অন্যথা যদি (!তথ্য->videodata->GetPointerType(pointerid, &pointer_type)) {
            বিরতি;  // oh well.
        } অন্যথা যদি (pointer_type != PT_PEN) {
            বিরতি;  // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুবক SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        যদি (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, তথ্য->window, true, true);
        } অন্যথা {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.অঙ্ক_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), ফাঁকা, তথ্য->window, &info, hpointer, true);
        }
        returnCode = 0;
    } বিরতি;

    ক্ষেত্র WM_POINTERCAPTURECHANGED:
    ক্ষেত্র WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুবক UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!তথ্য->videodata->GetPointerType) {
            বিরতি;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } অন্যথা যদি (!তথ্য->videodata->GetPointerType(pointerid, &pointer_type)) {
            বিরতি;  // oh well.
        } অন্যথা যদি (pointer_type != PT_PEN) {
            বিরতি;  // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুবক SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        যদি (pen == 0) {
            বিরতি;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        যদি ((বার্তা == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, তথ্য->window, false, false);
        }
        returnCode = 0;
    } বিরতি;

    ক্ষেত্র WM_POINTERDOWN:
    ক্ষেত্র WM_POINTERUP:
    ক্ষেত্র WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুবক UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!তথ্য->videodata->GetPointerType || !তথ্য->videodata->GetPointerType(pointerid, &pointer_type)) {
            বিরতি;  // oh well.
        } অন্যথা যদি ((বার্তা == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            তথ্য->last_pointer_update = lParam;
            returnCode = 0;
            বিরতি;
        } অন্যথা যদি (pointer_type != PT_PEN) {
            বিরতি; // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুবক SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        যদি (pen == 0) {
            বিরতি;  // not a pen, or not a pen we already knew about.
        } অন্যথা যদি (!তথ্য->videodata->GetPointerPenInfo || !তথ্য->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            বিরতি;  // oh well.
        }

        ধ্রুবক Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = তথ্য->window;

        ধ্রুবক bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        যদি (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ধ্রুবক POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        দশমিক fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        যদি (!তথ্য->videodata->GetPointerDeviceRects || !তথ্য->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(তথ্য->hwnd, &position);
            fx = (দশমিক) position.x;
            fy = (দশমিক) position.y;
        } অন্যথা {
            পূর্ণসংখ্যা ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            ধ্রুবক SDL_FPoint window_pos = { (দশমিক) ix, (দশমিক) iy };

            ধ্রুবক দশমিক facX = pointer_info->ptHimetricLocationRaw.x / (দশমিক) (tablet_bounds.ডান );
            ধ্রুবক দশমিক facY = pointer_info->ptHimetricLocationRaw.y / (দশমিক) (tablet_bounds.bottom);

            ধ্রুবক দশমিক w = tablet_mapping.ডান  - tablet_mapping.বাম;
            ধ্রুবক দশমিক h = tablet_mapping.bottom - tablet_mapping.শীর্ষ;

            fx = (tablet_mapping.বাম + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.শীর্ষ  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        যদি (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((দশমিক) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        যদি (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((দশমিক) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        যদি (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((দশমিক) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        যদি (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((দশমিক) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        যদি (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } বিরতি;

    ক্ষেত্র WM_MOUSEMOVE:
    {
        SDL_Window *window = তথ্য->window;

        যদি (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            যদি (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                তথ্য->clipcursor_queued = true;
            }
        }

        যদি (!তথ্য->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_আকার = আকার(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = তথ্য->hwnd;

            যদি (TrackMouseEvent(&trackMouseEvent)) {
                তথ্য->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), তথ্য);
        }

        যদি (!তথ্য->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            যদি (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != তথ্য->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)GET_X_LPARAM(lParam), (দশমিক)GET_Y_LPARAM(lParam));
            }
        }

    } বিরতি;

    ক্ষেত্র WM_LBUTTONUP:
    ক্ষেত্র WM_RBUTTONUP:
    ক্ষেত্র WM_MBUTTONUP:
    ক্ষেত্র WM_XBUTTONUP:
    ক্ষেত্র WM_LBUTTONDOWN:
    ক্ষেত্র WM_LBUTTONDBLCLK:
    ক্ষেত্র WM_RBUTTONDOWN:
    ক্ষেত্র WM_RBUTTONDBLCLK:
    ক্ষেত্র WM_MBUTTONDOWN:
    ক্ষেত্র WM_MBUTTONDBLCLK:
    ক্ষেত্র WM_XBUTTONDOWN:
    ক্ষেত্র WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        যদি (!তথ্য->videodata->raw_mouse_enabled) {
            যদি (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != তথ্য->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, তথ্য, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } বিরতি;

#যদি 0   // We handle raw input all at once instead of using a syscall for each mouse event
    ক্ষেত্র WM_প্রবেশ:
    {
        HRAWINPUT h_Raw_প্রবেশ = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT আকার_2 = আকার(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        যদি (তথ্য->window != SDL_GetKeyboardFocus()) {
            বিরতি;
        }

        Get_Raw_প্রবেশ_তথ্য(h_Raw_প্রবেশ, RID_প্রবেশ, &inp, &আকার_2, আকার(RAWINPUTHEADER));
        যদি (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_প্রবেশ(WIN_GetEventTimestamp(), তথ্য, inp.header.hDevice, &inp.তথ্য.mouse);
        } অন্যথা যদি (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_প্রবেশ(WIN_GetEventTimestamp(), তথ্য, inp.header.hDevice, &inp.তথ্য.keyboard);
        }
    } বিরতি;
#endif

    ক্ষেত্র WM_MOUSEWHEEL:
    ক্ষেত্র WM_MOUSEHWHEEL:
    {
        যদি (!তথ্য->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            দশমিক fAmount = (দশমিক)amount / WHEEL_DELTA;
            যদি (বার্তা == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), তথ্য->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } অন্যথা {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), তথ্য->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } বিরতি;

    ক্ষেত্র WM_MOUSELEAVE:
        যদি (!(তথ্য->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            যদি (SDL_GetMouseFocus() == তথ্য->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                যদি (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), তথ্য->window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)cursorPos.x, (দশমিক)cursorPos.y);
                } অন্যথা {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    যদি (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), তথ্য->window, SDL_TOUCH_MOUSEID, false, (দশমিক)cursorPos.x, (দশমিক)cursorPos.y);
                    } অন্যথা { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), তথ্য->window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)cursorPos.x, (দশমিক)cursorPos.y);
                    }
                }
            }

            যদি (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(ফাঁকা);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        তথ্য->mouse_tracked = false;

        returnCode = 0;
        বিরতি;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ক্ষেত্র WM_KEYDOWN:
    ক্ষেত্র WM_SYSKEYDOWN:
    {
        যদি (Skip_Alt_Gr_বাম_Control(wParam, lParam)) {
            returnCode = 0;
            বিরতি;
        }

        bool virtual_চাবি = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_চাবি);

        // Detect relevant keyboard shortcuts
        যদি (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            যদি (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        যদি (virtual_চাবি || !তথ্য->videodata->raw_keyboard_enabled || তথ্য->window->text_প্রবেশ_active) {
            SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        বিরতি;

    ক্ষেত্র WM_SYSKEYUP:
    ক্ষেত্র WM_KEYUP:
    {
        যদি (Skip_Alt_Gr_বাম_Control(wParam, lParam)) {
            returnCode = 0;
            বিরতি;
        }

        bool virtual_চাবি = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_চাবি);
        ধ্রুবক bool *keyboardState = SDL_GetKeyboardState(ফাঁকা);

        যদি (virtual_চাবি || !তথ্য->videodata->raw_keyboard_enabled || তথ্য->window->text_প্রবেশ_active) {
            যদি (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        বিরতি;

    ক্ষেত্র WM_UNICHAR:
        যদি (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } অন্যথা {
            যদি (SDL_Text_প্রবেশ_Active(তথ্য->window)) {
                অক্ষর text[5];
                অক্ষর *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        বিরতি;

    ক্ষেত্র WM_CHAR:
        যদি (SDL_Text_প্রবেশ_Active(তথ্য->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            যদি (IS_উপরের_SURROGATE(wParam)) {
                তথ্য->উপরের_surrogate = (WCHAR)wParam;
            } অন্যথা {
                WCHAR utf16[3];

                utf16[0] = তথ্য->উপরের_surrogate ? তথ্য->উপরের_surrogate : (WCHAR)wParam;
                utf16[1] = তথ্য->উপরের_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                অক্ষর utf8[5];
                পূর্ণসংখ্যা ফলাফল = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, আকার(utf8), ফাঁকা, ফাঁকা);
                যদি (ফলাফল > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                তথ্য->উপরের_surrogate = L'\0';
            }
        } অন্যথা {
            তথ্য->উপরের_surrogate = L'\0';
        }

        returnCode = 0;
        বিরতি;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    ক্ষেত্র WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        বিরতি;
#endif // WM_INPUTLANGCHANGE

    ক্ষেত্র WM_NCLBUTTONDOWN:
    {
        তথ্য->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        যদি (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } বিরতি;

    ক্ষেত্র WM_CAPTURECHANGED:
    {
        তথ্য->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), তথ্য);
    } বিরতি;

#ifdef WM_GETMINMAXINFO
    ক্ষেত্র WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT আকার_2;
        পূর্ণসংখ্যা x, y;
        পূর্ণসংখ্যা w, h;
        পূর্ণসংখ্যা min_w, min_h;
        পূর্ণসংখ্যা max_w, max_h;
        BOOL constrain_max_আকার;

        // If this is an expected size change, allow it
        যদি (তথ্য->expected_resize) {
            বিরতি;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &আকার_2);
        x = আকার_2.বাম;
        y = আকার_2.শীর্ষ;

        // Calculate current size of our window
        SDL_Get_Window_আকার(তথ্য->window, &w, &h);
        SDL_Get_Window_Minimum_আকার(তথ্য->window, &min_w, &min_h);
        SDL_Get_Window_Maximum_আকার(তথ্য->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        যদি (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_আকার = TRUE;
        } অন্যথা {
            constrain_max_আকার = FALSE;
        }

        যদি (!(SDL_GetWindowFlags(তথ্য->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(তথ্য->window)) {
            আকার_2.শীর্ষ = 0;
            আকার_2.বাম = 0;
            আকার_2.bottom = h;
            আকার_2.ডান = w;
            WIN_AdjustWindowRectForHWND(hwnd, &আকার_2, 0);
            w = আকার_2.ডান - আকার_2.বাম;
            h = আকার_2.bottom - আকার_2.শীর্ষ;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        যদি (SDL_GetWindowFlags(তথ্য->window) & SDL_WINDOW_RESIZABLE) {
            যদি (SDL_GetWindowFlags(তথ্য->window) & SDL_WINDOW_BORDERLESS) {
                পূর্ণসংখ্যা screenW = GetSystemMetrics(SM_CXSCREEN);
                পূর্ণসংখ্যা screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_আকার.x = SDL_max(w, screenW);
                info->pt_Max_আকার.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_আকার.x = (LONG)w + min_w;
            info->pt_Min_Track_আকার.y = (LONG)h + min_h;
            যদি (constrain_max_আকার) {
                info->pt_Max_Track_আকার.x = (LONG)w + max_w;
                info->pt_Max_Track_আকার.y = (LONG)h + max_h;
            }
        } অন্যথা {
            info->pt_Max_আকার.x = w;
            info->pt_Max_আকার.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_আকার.x = w;
            info->pt_Min_Track_আকার.y = h;
            info->pt_Max_Track_আকার.x = w;
            info->pt_Max_Track_আকার.y = h;
        }
    }
        returnCode = 0;
        বিরতি;
#endif // WM_GETMINMAXINFO

    ক্ষেত্র WM_WINDOWPOSCHANGING:

        যদি (তথ্য->expected_resize) {
            returnCode = 0;
        } অন্যথা যদি (তথ্য->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            যদি (তথ্য->last_modal_width == windowpos->cx && তথ্য->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            তথ্য->last_modal_width = windowpos->cx;
            তথ্য->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        বিরতি;

    ক্ষেত্র WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        ধ্রুবক SDL_DisplayID original_displayID = তথ্য->window->displayID;
        ধ্রুবক WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        পূর্ণসংখ্যা x, y;
        পূর্ণসংখ্যা w, h;

        যদি (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        যদি (iconic) {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } অন্যথা যদি (zoomed) {
            যদি (তথ্য->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            তথ্য->force_ws_maximizebox = true;
        } অন্যথা যদি (তথ্য->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            যদি (!(তথ্য->window->flags & SDL_WINDOW_FULLSCREEN)) {
                তথ্য->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), তথ্য->window, !!(তথ্য->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        যদি (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        যদি (iconic) {
            বিরতি;
        }

        যদি (তথ্য->initializing) {
            বিরতি;
        }

        যদি (!তথ্য->disable_move_আকার_events) {
            যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.বাম;
                y = rect.শীর্ষ;

                SDL_GlobalToRelativeForWindow(তথ্য->window, x, y, &x, &y);
                SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.ডান;
                h = rect.bottom;

                SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(তথ্য->window);

        // Update the window display position
        যদি (তথ্য->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(তথ্য->window, true);
        }

        // Update the position of any child windows
        জন্য (win = তথ্য->window->first_child; win; win = win->পরবর্তী_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            যদি (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } বিরতি;

    ক্ষেত্র WM_ENTERSIZEMOVE:
    ক্ষেত্র WM_ENTERMENULOOP:
    {
        যদি (g_WindowsMessageHook) {
            যদি (!DispatchModalLoopMessageHook(&hwnd, &বার্তা, &wParam, &lParam)) {
                ফেরত 0;
            }
        }

        ++তথ্য->in_modal_loop;
        যদি (তথ্য->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(তথ্য->hwnd, &rect);
            তথ্য->last_modal_width = rect.ডান - rect.বাম;
            তথ্য->last_modal_height = rect.bottom - rect.শীর্ষ;

            তথ্য->initial_আকার_rect.বাম = তথ্য->window->x;
            তথ্য->initial_আকার_rect.ডান = তথ্য->window->x + তথ্য->window->w;
            তথ্য->initial_আকার_rect.শীর্ষ = তথ্য->window->y;
            তথ্য->initial_আকার_rect.bottom = তথ্য->window->y + তথ্য->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, ফাঁকা);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } বিরতি;

    ক্ষেত্র WM_TIMER:
    {
        যদি (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(তথ্য->window);

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#যদি 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            যদি (তথ্য->videodata->DwmFlush) {
                তথ্য->videodata->DwmFlush();
            }
#endif
#endif
            ফেরত 0;
        }
    } বিরতি;

    ক্ষেত্র WM_EXITSIZEMOVE:
    ক্ষেত্র WM_EXITMENULOOP:
    {
        --তথ্য->in_modal_loop;
        যদি (তথ্য->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } বিরতি;

    ক্ষেত্র WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (তথ্য->window->max_aspect == তথ্য->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            দশমিক new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            যদি (তথ্য->window->min_aspect <= 0 && তথ্য->window->max_aspect <= 0) {
                বিরতি;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            যদি (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != ফাঁকা, GetWindowExStyle(hwnd))) {
                বিরতি;
            }

            clientDragRect.বাম -= rc.বাম;
            clientDragRect.শীর্ষ -= rc.শীর্ষ;
            clientDragRect.ডান -= rc.ডান;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ডান - clientDragRect.বাম;
            h = clientDragRect.bottom - clientDragRect.শীর্ষ;
            new_aspect = w / (দশমিক)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            যদি (lock_aspect_ratio) {
                নির্বাচন (edge) {
                ক্ষেত্র WMSZ_বাম:
                ক্ষেত্র WMSZ_ডান:
                    h = (পূর্ণসংখ্যা)SDL_roundf(w / তথ্য->window->max_aspect);
                    বিরতি;
                পূর্বনির্ধারিত:
                    // resizing via corners or top or bottom
                    w = (পূর্ণসংখ্যা)SDL_roundf(h * তথ্য->window->max_aspect);
                    বিরতি;
                }
            } অন্যথা {
                নির্বাচন (edge) {
                ক্ষেত্র WMSZ_বাম:
                ক্ষেত্র WMSZ_ডান:
                    যদি (তথ্য->window->max_aspect > 0.0f && new_aspect > তথ্য->window->max_aspect) {
                        w = (পূর্ণসংখ্যা)SDL_roundf(h * তথ্য->window->max_aspect);
                    } অন্যথা যদি (তথ্য->window->min_aspect > 0.0f && new_aspect < তথ্য->window->min_aspect) {
                        w = (পূর্ণসংখ্যা)SDL_roundf(h * তথ্য->window->min_aspect);
                    }
                    বিরতি;
                ক্ষেত্র WMSZ_শীর্ষ:
                ক্ষেত্র WMSZ_BOTTOM:
                    যদি (তথ্য->window->min_aspect > 0.0f && new_aspect < তথ্য->window->min_aspect) {
                        h = (পূর্ণসংখ্যা)SDL_roundf(w / তথ্য->window->min_aspect);
                    } অন্যথা যদি (তথ্য->window->max_aspect > 0.0f && new_aspect > তথ্য->window->max_aspect) {
                        h = (পূর্ণসংখ্যা)SDL_roundf(w / তথ্য->window->max_aspect);
                    }
                    বিরতি;

                পূর্বনির্ধারিত:
                    // resizing via corners
                    যদি (তথ্য->window->max_aspect > 0.0f && new_aspect > তথ্য->window->max_aspect) {
                        w = (পূর্ণসংখ্যা)SDL_roundf(h * তথ্য->window->max_aspect);
                    } অন্যথা যদি (তথ্য->window->min_aspect > 0.0f && new_aspect < তথ্য->window->min_aspect) {
                        h = (পূর্ণসংখ্যা)SDL_roundf(w / তথ্য->window->min_aspect);
                    }
                    বিরতি;
                }
            }

            নির্বাচন (edge) {
            ক্ষেত্র WMSZ_বাম:
                clientDragRect.বাম = clientDragRect.ডান - w;
                যদি (lock_aspect_ratio) {
                    clientDragRect.শীর্ষ = (তথ্য->initial_আকার_rect.bottom + তথ্য->initial_আকার_rect.শীর্ষ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                বিরতি;
            ক্ষেত্র WMSZ_BOTTOMLEFT:
                clientDragRect.বাম = clientDragRect.ডান - w;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                বিরতি;
            ক্ষেত্র WMSZ_ডান:
                clientDragRect.ডান = w + clientDragRect.বাম;
                যদি (lock_aspect_ratio) {
                    clientDragRect.শীর্ষ = (তথ্য->initial_আকার_rect.bottom + তথ্য->initial_আকার_rect.শীর্ষ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                বিরতি;
            ক্ষেত্র WMSZ_TOPRIGHT:
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                বিরতি;
            ক্ষেত্র WMSZ_শীর্ষ:
                যদি (lock_aspect_ratio) {
                    clientDragRect.বাম = (তথ্য->initial_আকার_rect.ডান + তথ্য->initial_আকার_rect.বাম - w) / 2;
                }
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                বিরতি;
            ক্ষেত্র WMSZ_TOPLEFT:
                clientDragRect.বাম = clientDragRect.ডান - w;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                বিরতি;
            ক্ষেত্র WMSZ_BOTTOM:
                যদি (lock_aspect_ratio) {
                    clientDragRect.বাম = (তথ্য->initial_আকার_rect.ডান + তথ্য->initial_আকার_rect.বাম - w) / 2;
                }
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                বিরতি;
            ক্ষেত্র WMSZ_BOTTOMRIGHT:
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                বিরতি;
            }

            // convert the client rect to a window rect
            যদি (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != ফাঁকা, GetWindowExStyle(hwnd))) {
                বিরতি;
            }

            *dragRect = clientDragRect;
        }
        বিরতি;

    ক্ষেত্র WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        যদি (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } অন্যথা যদি (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(ফাঁকা);
            returnCode = TRUE;
        }
    } বিরতি;

        // We were occluded, refresh our display
    ক্ষেত্র WM_PAINT:
    {
        RECT rect;
        যদি (GetUpdateRect(hwnd, &rect, FALSE)) {
            ধ্রুবক LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            যদি (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, ফাঁকা);
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        বিরতি;

        // We'll do our own drawing, prevent flicker
    ক্ষেত্র WM_ERASEBKGND:
        যদি (ShouldClearWindowOnEraseBackground(তথ্য)) {
            RECT client_rect;
            HBRUSH brush;
            তথ্য->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        ফেরত 1;

    ক্ষেত্র WM_SYSCOMMAND:
    {
        যদি (!g_WindowsEnableMenuMnemonics) {
            যদি ((wParam & 0xFFF0) == SC_KEYMENU) {
                ফেরত 0;
            }
        }

#যদি defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        যদি ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            যদি (SDL_GetVideoDevice()->suspend_screensaver) {
                ফেরত 0;
            }
        }
#endif // System has screensaver support
    } বিরতি;

    ক্ষেত্র WM_CLOSE:
    {
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        বিরতি;

    ক্ষেত্র WM_TOUCH:
        যদি (তথ্য->videodata->Get_Touch_প্রবেশ_Info && তথ্য->videodata->Close_Touch_প্রবেশ_Handle) {
            UINT i, অঙ্ক_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, অঙ্ক_inputs, &isstack);
            যদি (inputs && তথ্য->videodata->Get_Touch_প্রবেশ_Info((HTOUCHINPUT)lParam, অঙ্ক_inputs, inputs, আকার(TOUCHINPUT))) {
                RECT rect;
                দশমিক x, y;

                যদি (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    যদি (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    বিরতি;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.শীর্ষ *= 100;
                rect.বাম *= 100;
                rect.bottom *= 100;
                rect.ডান *= 100;

                জন্য (i = 0; i < অঙ্ক_inputs; ++i) {
                    PTOUCHINPUT প্রবেশ = &inputs[i];
                    ধ্রুবক পূর্ণসংখ্যা w = (rect.ডান - rect.বাম);
                    ধ্রুবক পূর্ণসংখ্যা h = (rect.bottom - rect.শীর্ষ);

                    ধ্রুবক SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)প্রবেশ->hSource);
                    ধ্রুবক SDL_FingerID fingerId = (প্রবেশ->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    যদি (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (প্রবেশ->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        চালু;
                    }

                    // Get the normalized coordinates for the window
                    যদি (w <= 1) {
                        x = 0.5f;
                    } অন্যথা {
                        x = (দশমিক)(প্রবেশ->x - rect.বাম) / (w - 1);
                    }
                    যদি (h <= 1) {
                        y = 0.5f;
                    } অন্যথা {
                        y = (দশমিক)(প্রবেশ->y - rect.শীর্ষ) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, তথ্য->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, তথ্য->window, x, y, 1.0f);
                    }
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, তথ্য->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            তথ্য->videodata->Close_Touch_প্রবেশ_Handle((HTOUCHINPUT)lParam);
            ফেরত 0;
        }
        বিরতি;

#ifdef HAVE_TPCSHRD_H

    ক্ষেত্র WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        ফেরত TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    ক্ষেত্র WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT গুনতি = DragQueryFile(drop, 0xFFFFFFFF, ফাঁকা, 0);
        জন্য (i = 0; i < গুনতি; ++i) {
            UINT আকার_2 = DragQueryFile(drop, i, ফাঁকা, 0) + 1;
            LPTSTR বাফার_2 = (LPTSTR)SDL_malloc(আকার(TCHAR) * আকার_2);
            যদি (বাফার_2) {
                যদি (DragQueryFile(drop, i, বাফার_2, আকার_2)) {
                    অক্ষর *file = WIN_StringToUTF8(বাফার_2);
                    SDL_SendDropFile(তথ্য->window, ফাঁকা, file);
                    SDL_free(file);
                }
                SDL_free(বাফার_2);
            }
        }
        SDL_SendDropComplete(তথ্য->window);
        DragFinish(drop);
        ফেরত 0;
    }

    ক্ষেত্র WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } বিরতি;

    ক্ষেত্র WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = তথ্য->window->flags;
        যদি (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            যদি (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                যদি (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ধ্রুবক POINT pt = { তথ্য->window->windowed.x, তথ্য->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                যদি (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_আকার = আকার(info);
                    যদি (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } অন্যথা যদি (!(window_flags & SDL_WINDOW_RESIZABLE) && !তথ্য->force_ws_maximizebox) {
                পূর্ণসংখ্যা w, h;
                যদি (তথ্য->window->last_আকার_pending) {
                    w = তথ্য->window->pending.w;
                    h = তথ্য->window->pending.h;
                } অন্যথা {
                    w = তথ্য->window->floating.w;
                    h = তথ্য->window->floating.h;
                }
                params->rgrc[0].ডান = params->rgrc[0].বাম + w;
                params->rgrc[0].bottom = params->rgrc[0].শীর্ষ + h;
            }
            ফেরত 0;
        }
    } বিরতি;

    ক্ষেত্র WM_NCHITTEST:
    {
        SDL_Window *window = তথ্য->window;

        যদি (window->flags & SDL_WINDOW_TOOLTIP) {
            ফেরত HTTRANSPARENT;
        }

        যদি (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            যদি (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_Hit_Test_ফলাফল rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_তথ্য);
                নির্বাচন (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        ফেরত ret;                                                        \
    }
                ক্ষেত্র SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(ফাঁকা, ফাঁকা);
                    যদি (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        ফেরত HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                ক্ষেত্র SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                ক্ষেত্র SDL_HITTEST_RESIZE_শীর্ষ:
                    POST_HIT_TEST(HTTOP);
                ক্ষেত্র SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                ক্ষেত্র SDL_HITTEST_RESIZE_ডান:
                    POST_HIT_TEST(HTRIGHT);
                ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                ক্ষেত্র SDL_HITTEST_RESIZE_বাম:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                ক্ষেত্র SDL_HITTEST_NORMAL:
                    ফেরত HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } বিরতি;

    ক্ষেত্র WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        যদি (তথ্য->videodata->GetDpiForWindow && তথ্য->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ধ্রুবক পূর্ণসংখ্যা পরবর্তী_DPI = (পূর্ণসংখ্যা)wParam;
            ধ্রুবক পূর্ণসংখ্যা পূর্ব_DPI = (পূর্ণসংখ্যা)তথ্য->videodata->GetDpiForWindow(hwnd);
            আকার_4 *আকার_In_Out = (আকার_4 *)lParam;

            পূর্ণসংখ্যা frame_w, frame_h;
            পূর্ণসংখ্যা query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    পূর্ব_DPI, পরবর্তী_DPI, আকার_In_Out->cx, আকার_In_Out->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                যদি (!(তথ্য->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(তথ্য->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, পূর্ব_DPI);
                }

                frame_w = -rect.বাম + rect.ডান;
                frame_h = -rect.শীর্ষ + rect.bottom;

                query_client_w_win = আকার_In_Out->cx - frame_w;
                query_client_h_win = আকার_In_Out->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ডান = query_client_w_win;
                rect.bottom = query_client_h_win;

                যদি (!(তথ্য->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(তথ্য->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, পরবর্তী_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                আকার_In_Out->cx = rect.ডান - rect.বাম;
                আকার_In_Out->cy = rect.bottom - rect.শীর্ষ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", আকার_In_Out->cx, আকার_In_Out->cy);
#endif
            ফেরত TRUE;
        }
        বিরতি;

    ক্ষেত্র WM_DPICHANGED:
        // Windows 8.1+
        {
            ধ্রুবক পূর্ণসংখ্যা newDPI = HIWORD(wParam);
            RECT *ধ্রুবক suggestedRect = (RECT *)lParam;
            পূর্ণসংখ্যা w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->বাম, suggestedRect->শীর্ষ, suggestedRect->ডান - suggestedRect->বাম, suggestedRect->bottom - suggestedRect->শীর্ষ);
#endif

            যদি (তথ্য->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                ফেরত 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ডান = তথ্য->window->w;
                rect.bottom = তথ্য->window->h;

                যদি (!(তথ্য->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.ডান - rect.বাম;
                h = rect.bottom - rect.শীর্ষ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    তথ্য->window->w, তথ্য->window->h,
                    suggestedRect->বাম, suggestedRect->শীর্ষ, w, h);
#endif

            তথ্য->expected_resize = true;
            SetWindowPos(hwnd,
                         ফাঁকা,
                         suggestedRect->বাম,
                         suggestedRect->শীর্ষ,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            তথ্য->expected_resize = false;
            ফেরত 0;
        }

    ক্ষেত্র WM_SETTINGCHANGE:
        যদি (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        যদি (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        যদি (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        বিরতি;
#অন্যথা
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    ক্ষেত্র WM_আকার:
    {
        RECT rect;
        পূর্ণসংখ্যা w, h;

        যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.ডান;
            h = rect.bottom;
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } বিরতি;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    পূর্বনির্ধারিত:
        বিরতি;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (বার্তা && বার্তা == তথ্য->videodata->WM_TASKBAR_BUTTON_CREATED) {
        তথ্য->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), তথ্য->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    যদি (তথ্য->wndproc) {
        ফেরত CallWindowProc(তথ্য->wndproc, hwnd, বার্তা, wParam, lParam);
    } অন্যথা যদি (returnCode >= 0) {
        ফেরত returnCode;
    } অন্যথা {
        ফেরত CallWindowProc(DefWindowProc, hwnd, বার্তা, wParam, lParam);
    }
}

পূর্ণসংখ্যা WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    যদি (g_WindowsEnableMessageLoop) {
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = বার্তা_Wait_For_Multiple_Objects(0, ফাঁকা, FALSE, timeout, QS_ALLINPUT);
        যদি (ret == WAIT_OBJECT_0) {
            ফেরত 1;
        } অন্যথা {
            ফেরত 0;
        }
#অন্যথা
        // MsgWaitForMultipleObjects is desktop-only.
        বার্তা_2 বার্তা;
        BOOL message_ফলাফল;
        UINT_PTR timer_id = 0;
        যদি (timeoutNS > 0) {
            timer_id = SetTimer(ফাঁকা, 0, (UINT)SDL_NS_TO_MS(timeoutNS), ফাঁকা);
            message_ফলাফল = GetMessage(&বার্তা, 0, 0, 0);
            KillTimer(ফাঁকা, timer_id);
        } অন্যথা যদি (timeoutNS == 0) {
            message_ফলাফল = PeekMessage(&বার্তা, ফাঁকা, 0, 0, PM_REMOVE);
        } অন্যথা {
            message_ফলাফল = GetMessage(&বার্তা, 0, 0, 0);
        }
        যদি (message_ফলাফল) {
            যদি (বার্তা.message == WM_TIMER && !বার্তা.hwnd && বার্তা.wParam == timer_id) {
                ফেরত 0;
            }
            যদি (g_WindowsMessageHook) {
                যদি (!g_WindowsMessageHook(g_Windows_Message_Hook_তথ্য, &বার্তা)) {
                    ফেরত 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&বার্তা);
            DispatchMessage(&বার্তা);
            ফেরত 1;
        } অন্যথা {
            ফেরত 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } অন্যথা {
        // Fail the wait so the caller falls back to polling
        ফেরত -1;
    }
}

শূন্য WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    PostMessage(তথ্য->hwnd, তথ্য->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
শূন্য WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    বার্তা_2 বার্তা;

    যদি (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        যখন (PeekMessage(&বার্তা, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(বার্তা.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&বার্তা);
            DispatchMessage(&বার্তা);
        }

        SDL_processing_messages = false;
    }
}

শূন্য WIN_PumpEvents(SDL_VideoDevice *_this)
{
    বার্তা_2 বার্তা;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ঠেলো)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_গুনতি() + 1;
#ifdef _MSC_VER
#pragma warning(বের_করো)
#endif
    পূর্ণসংখ্যা new_messages = 0;

    যদি (_this->internal->gameinput_context) {
        WIN_Update_Game_প্রবেশ(_this);
    }

    যদি (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        যখন (PeekMessage(&বার্তা, ফাঁকা, 0, 0, PM_REMOVE)) {
            যদি (g_WindowsMessageHook) {
                যদি (!g_WindowsMessageHook(g_Windows_Message_Hook_তথ্য, &বার্তা)) {
                    চালু;
                }
            }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            যদি (বার্তা.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                যদি (!SDL_TICKS_PASSED(বার্তা.time, (SDL_last_warp_time + 1))) {
                    চালু;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(বার্তা.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&বার্তা);
            DispatchMessage(&বার্তা);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            যদি (SDL_TICKS_PASSED(বার্তা.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ধ্রুবক পূর্ণসংখ্যা MAX_NEW_MESSAGES = 3;
                ++new_messages;
                যদি (new_messages > MAX_NEW_MESSAGES) {
                    বিরতি;
                }
            }
        }

        SDL_processing_messages = false;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ধ্রুবক bool *keystate = SDL_GetKeyboardState(ফাঁকা);
    যদি (keystate[SDL_SCANCODE_LSHIFT] && !(Get_চাবি_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    যদি (keystate[SDL_SCANCODE_RSHIFT] && !(Get_চাবি_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    যদি (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        যদি (keystate[SDL_SCANCODE_LGUI] && !(Get_চাবি_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        যদি (keystate[SDL_SCANCODE_RGUI] && !(Get_চাবি_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    যদি (_this) {
        SDL_Window *window = _this->windows;
        যখন (window) {
            bool refresh_clipcursor = false;
            SDL_Window_তথ্য *তথ্য = window->internal;
            যদি (তথ্য) {
                refresh_clipcursor = তথ্য->clipcursor_queued;
                তথ্য->clipcursor_queued = false;    // Must be cleared unconditionally.
                তথ্য->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            যদি (refresh_clipcursor) {
                WIN_UpdateClipCursor(window);
            }
            window = window->পরবর্তী;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focusWindow = SDL_GetKeyboardFocus();
    যদি (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_Window_তথ্য *তথ্য = focusWindow->internal;

        যদি (!তথ্য->mouse_tracked) {
            POINT cursorPos;

            যদি (GetCursorPos(&cursorPos) && ScreenToClient(তথ্য->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), তথ্য->window, mouseID, false, (দশমিক)cursorPos.x, (দশমিক)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), তথ্য->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_বাম : SDL_BUTTON_ডান,
                                    (Get_Async_চাবি_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), তথ্য->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_ডান : SDL_BUTTON_বাম,
                                    (Get_Async_চাবি_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), তথ্য->window, mouseID,
                                    SDL_BUTTON_মধ্য,
                                    (Get_Async_চাবি_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), তথ্য->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_চাবি_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), তথ্য->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_চাবি_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

স্থির পূর্ণসংখ্যা app_registered = 0;
LPTSTR SDL_Appname = ফাঁকা;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = ফাঁকা;

স্থির শূন্য WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    যদি (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = ফাঁকা;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
স্থির BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (শূন্য)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    ফেরত FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(ধ্রুবক অক্ষর *name, Uint32 style, শূন্য *hInst)
{
    WNDCLASSEX wcex;
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ধ্রুবক অক্ষর *hint;
#endif

    // Only do this once...
    যদি (app_registered) {
        ++app_registered;
        ফেরত true;
    }
    SDL_assert(!SDL_Appname);
    যদি (!name) {
        name = "SDL_app";
#যদি defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(ফাঁকা);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_আকার = আকার(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    যদি (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        যদি (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } অন্যথা {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    যদি (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        ফেরত SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    ফেরত true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
শূন্য SDL_UnregisterApp(শূন্য)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    যদি (!app_registered) {
        ফেরত;
    }
    --app_registered;
    যদি (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = ফাঁকা;
        wcex.hIconSm = ফাঁকা;
        // Check for any registered window classes.
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        যদি (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
