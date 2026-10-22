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
প্রকারনির্দেশ Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
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
    ধ্রুব Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    যদি (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        প্রত্যাগম 0;
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
    প্রত্যাগম timestamp;
}

// A message hook called before TranslateMessage()
স্থির SDL_WindowsMessageHook g_WindowsMessageHook = রিক্ত;
স্থির শূন্য *g_WindowsMessageHookData = রিক্ত;

শূন্য SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, শূন্য *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

স্থির SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_চাবি)
{
    SDL_Scancode code;
    Uint8 index;
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
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    প্রত্যাগম code;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
স্থির bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    প্রত্যাগম !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

স্থির শূন্য WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    যদি (bSwapButtons) {
        যদি (button == SDL_BUTTON_বাম) {
            button = SDL_BUTTON_ডান;
        } অন্যথা যদি (button == SDL_BUTTON_ডান) {
            button = SDL_BUTTON_বাম;
        }
    }

    যদি (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        যদি (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        প্রত্যাগম;
    }

    যদি (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } অন্যথা যদি (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
স্থির শূন্য WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    যদি (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(রিক্ত, রিক্ত);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_বাম, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_মধ্য, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_ডান, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

স্থির শূন্য WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT চাবি_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(রিক্ত, রিক্ত);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    চাবি_State = Get_Async_চাবি_State(VK_LBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_বাম, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_RBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_ডান, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_MBUTTON);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_মধ্য, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_XBUTTON1);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    চাবি_State = Get_Async_চাবি_State(VK_XBUTTON2);
    যদি (!(চাবি_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

স্থির শূন্য WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    যদি (had_focus == has_focus || has_focus != expect_focus) {
        প্রত্যাগম;
    }

    যদি (has_focus) {
        POINT cursorPos;

        যদি (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            যদি (Get_Async_চাবি_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            যদি (Get_Async_চাবি_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            যদি (Get_Async_চাবি_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            যদি (Get_Async_চাবি_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            যদি (Get_Async_চাবি_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        যদি (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (ভিন্ন)cursorPos.x, (ভিন্ন)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_চাবি_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_অঙ্ক, (Get_চাবি_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_চাবি_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } অন্যথা {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(রিক্ত);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        যদি (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(রিক্ত);
        }
        WIN_Reset_Dead_চাবিগুলি();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

স্থির bool ShouldGenerateWindowCloseOnAltF4(শূন্য)
{
    প্রত্যাগম SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

স্থির bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    বিকল্প (data->hint_erase_background_mode) {
    পক্ষ SDL_ERASEBACKGROUNDMODE_NEVER:
        প্রত্যাগম false;
    পক্ষ SDL_ERASEBACKGROUNDMODE_INITIAL:
        প্রত্যাগম !data->videodata->cleared;
    পক্ষ SDL_ERASEBACKGROUNDMODE_ALWAYS:
        প্রত্যাগম true;
    স্বভাব:
        // Unexpected value, fallback to default behaviour
        প্রত্যাগম !data->videodata->cleared;
    }
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

প্রকারনির্দেশ গণনা
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
            প্রত্যাগম SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } অন্যথা {
            প্রত্যাগম SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    প্রত্যাগম SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

স্থির SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    যদি (_this) {
        প্রতি (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            যদি (data && data->hwnd == hwnd) {
                প্রত্যাগম data;
            }
        }
    }
    প্রত্যাগম রিক্ত;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(পূর্ণাঙ্ক nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    যদি (nCode < 0 || nCode != HC_ACTION) {
        প্রত্যাগম CallNextHookEx(রিক্ত, nCode, wParam, lParam);
    }
    যদি (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        প্রত্যাগম 1;
    }

    বিকল্প (hookData->vkCode) {
    পক্ষ VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        ভঙ্গ;
    পক্ষ VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        ভঙ্গ;
    পক্ষ VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        ভঙ্গ;
    পক্ষ VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        ভঙ্গ;
    পক্ষ VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        ভঙ্গ;
    পক্ষ VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        ভঙ্গ;
    পক্ষ VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        ভঙ্গ;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    পক্ষ VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        ভঙ্গ;
    পক্ষ VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        ভঙ্গ;

    স্বভাব:
        প্রত্যাগম CallNextHookEx(রিক্ত, nCode, wParam, lParam);
    }

    যদি (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        যদি (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } অন্যথা {
        যদি (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        যদি (hookData->vkCode <= 0xFF && data->pre_hook_চাবি_state[hookData->vkCode]) {
            data->pre_hook_চাবি_state[hookData->vkCode] = 0;
            প্রত্যাগম CallNextHookEx(রিক্ত, nCode, wParam, lParam);
        }
    }

    প্রত্যাগম 1;
}

স্থির bool WIN_SwapButtons(HANDLE hDevice)
{
    যদি (hDevice == রিক্ত) {
        // Touchpad, already has buttons swapped
        প্রত্যাগম false;
    }
    প্রত্যাগম GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

স্থির শূন্য WIN_Handle_Raw_Mouse_প্রবেশ(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    স্থির সংরচনা {
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

    পূর্ণাঙ্ক dx = (পূর্ণাঙ্ক)rawmouse->lLastX;
    পূর্ণাঙ্ক dy = (পূর্ণাঙ্ক)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    যদি (!data->raw_mouse_enabled) {
        প্রত্যাগম;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    যদি (!window) {
        প্রত্যাগম;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    যদি (!mouse) {
        প্রত্যাগম;
    }

    যদি (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        প্রত্যাগম;
    }

    SDL_WindowData *windowdata = window->internal;

    যদি (haveMotion && !windowdata->in_modal_loop) {
        যদি (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (ভিন্ন)dx, (ভিন্ন)dy);
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
            পূর্ণাঙ্ক w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            পূর্ণাঙ্ক h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            পূর্ণাঙ্ক x = raw_coordinates ? dx : (পূর্ণাঙ্ক)(((ভিন্ন)dx / 65535.0f) * w);
            পূর্ণাঙ্ক y = raw_coordinates ? dy : (পূর্ণাঙ্ক)(((ভিন্ন)dy / 65535.0f) * h);
            পূর্ণাঙ্ক relX, relY;

            /* Calculate relative motion */
            যদি (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            যদি (remote_desktop) {
                যদি (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    স্থির পূর্ণাঙ্ক wobble;
                    ভিন্ন floatX = (ভিন্ন)x / w;
                    ভিন্ন floatY = (ভিন্ন)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    যদি (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        পূর্ণাঙ্ক warpX = rect.বাম + ((rect.ডান - rect.বাম) / 2) + wobble;
                        পূর্ণাঙ্ক warpY = rect.শীর্ষ + ((rect.bottom - rect.শীর্ষ) / 2);

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
                        ধ্রুব পূর্ণাঙ্ক MAX_RELATIVE_MOTION = (h / 6);
                        যদি (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (ভিন্ন)relX, (ভিন্ন)relY);
                        }
                    }
                }
            } অন্যথা যদি (mouse->pen_mouse_events) {
                ধ্রুব পূর্ণাঙ্ক MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                যদি (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } অন্যথা {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (ভিন্ন)relX, (ভিন্ন)relY);
                }
            } অন্যথা {
                পূর্ণাঙ্ক screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                পূর্ণাঙ্ক screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                যদি (!data->raw_প্রবেশ_fake_pen_id) {
                    data->raw_প্রবেশ_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, রিক্ত, (শূন্য *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_প্রবেশ_fake_pen_id, window, (ভিন্ন)(x + screen_x - window->x), (ভিন্ন)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    যদি (haveButton) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(raw_buttons); ++i) {
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
                    অনুবর্ত;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        যদি (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            ভিন্ন fAmount = (ভিন্ন)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } অন্যথা যদি (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            ভিন্ন fAmount = (ভিন্ন)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

স্থির শূন্য WIN_Handle_Raw_Keyboard_প্রবেশ(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    যদি (!data->raw_keyboard_enabled) {
        প্রত্যাগম;
    }

    যদি (rawkeyboard->Flags & RI_চাবি_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_চাবি_sequence = true;
        প্রত্যাগম;
    }

    যদি ((rawkeyboard->Flags & RI_চাবি_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        প্রত্যাগম;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_চাবি(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    যদি (!rawkeyboard->MakeCode) {
        প্রত্যাগম;
    }

    bool down;
    বিকল্প (rawkeyboard->Message) {
    পক্ষ WM_KEYDOWN:
    পক্ষ WM_SYSKEYDOWN:
        down = true;
        ভঙ্গ;
    পক্ষ WM_KEYUP:
    পক্ষ WM_SYSKEYUP:
        down = false;
        ভঙ্গ;
    স্বভাব:
        down = !(rawkeyboard->Flags & RI_চাবি_BREAK);
        ভঙ্গ;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    যদি (data->pending_E1_চাবি_sequence) {
        rawcode |= 0xE100;
        যদি (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } অন্যথা {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_চাবি_sequence = false;
    } অন্যথা {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        যদি (rawkeyboard->Flags & RI_চাবি_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    যদি (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        যদি ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_প্রবেশ_active)) {
            প্রত্যাগম;
        }
    }

    SDL_Send_Keyboard_চাবি(timestamp, keyboardID, rawcode, code, down);
}

শূন্য WIN_Poll_Raw_প্রবেশ(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, গুনতি, total = 0;
    RAWINPUT *প্রবেশ;
    Uint64 poll_finish;

    যদি (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = পরিমাণ(RAWINPUTHEADER);
        যদি (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    প্রবেশ = (RAWINPUT *)data->rawinput;
    প্রতি (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)প্রবেশ - data->rawinput);
        গুনতি = Get_Raw_প্রবেশ_Buffer(প্রবেশ, &size, পরিমাণ(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        যদি (গুনতি == 0 || গুনতি == (UINT)-1) {
            যদি (!data->rawinput || (গুনতি == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                ধ্রুব UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                যদি (!rawinput) {
                    ভঙ্গ;
                }
                প্রবেশ = (RAWINPUT *)(rawinput + ((BYTE *)প্রবেশ - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } অন্যথা {
                ভঙ্গ;
            }
        } অন্যথা {
            total += গুনতি;

            // Advance input to the end of the buffer
            যাবত্ (গুনতি--) {
                প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ);
            }
        }
    }

    যদি (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        প্রতি (i = 0, প্রবেশ = (RAWINPUT *)data->rawinput; i < total; ++i, প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ)) {
            যদি (প্রবেশ->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        পূর্ণাঙ্ক mouse_index = 0;
        প্রতি (i = 0, প্রবেশ = (RAWINPUT *)data->rawinput; i < total; ++i, প্রবেশ = NEXTRAWINPUTBLOCK(প্রবেশ)) {
            যদি (প্রবেশ->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)প্রবেশ + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_প্রবেশ(time, data, প্রবেশ->header.hDevice, rawmouse);
            } অন্যথা যদি (প্রবেশ->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)প্রবেশ + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_প্রবেশ(poll_finish, data, প্রবেশ->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

স্থির শূন্য AddDeviceID(Uint32 deviceID, Uint32 **list, পূর্ণাঙ্ক *গুনতি)
{
    পূর্ণাঙ্ক new_গুনতি = (*গুনতি + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_গুনতি * পরিমাণ(*new_list));
    যদি (!new_list) {
        // Oh well, we'll drop this one
        প্রত্যাগম;
    }
    new_list[new_গুনতি - 1] = deviceID;

    *গুনতি = new_গুনতি;
    *list = new_list;
}

স্থির bool HasDeviceID(Uint32 deviceID, ধ্রুব Uint32 *list, পূর্ণাঙ্ক গুনতি)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < গুনতি; ++i) {
        যদি (deviceID == list[i]) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম false;
}

স্থির বর্ণ *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ধ্রুব বর্ণ *instance, Uint16 vendor, Uint16 product, ধ্রুব বর্ণ *default_name, bool hid_loaded)
{
    বর্ণ *vendor_name = রিক্ত;
    বর্ণ *product_name = রিক্ত;
    বর্ণ *name = রিক্ত;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    যদি (hid_loaded) {
        বর্ণ devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = পরিমাণ(devName) - 1;
        UINT len = Get_Raw_প্রবেশ_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        যদি (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, রিক্ত, OPEN_EXISTING, 0, রিক্ত);
            যদি (hFile != INVALID_HANDLE_মান) {
                SDL_HidD_GetManufacturerString(hFile, vend, পরিমাণ(vend));
                SDL_HidD_GetProductString(hFile, prod, পরিমাণ(prod));
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
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = পরিমাণ(data);
        প্রতি (DWORD i = 0;; ++i) {
            যদি (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                যদি (GetLastError() == ERROR_NO_MORE_বস্তুসমূহ) {
                    ভঙ্গ;
                } অন্যথা {
                    অনুবর্ত;
                }
            }

            বর্ণ DeviceInstanceId[64];
            যদি (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, পরিমাণ(DeviceInstanceId), রিক্ত))
                অনুবর্ত;

            যদি (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                যদি (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, রিক্ত, (PBYTE)prod, পরিমাণ(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= পরিমাণ(*prod);
                    যদি (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    যদি (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } অন্যথা {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                ভঙ্গ;
            }
        }
    }

    যদি (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    প্রত্যাগম name;
}

শূন্য WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = রিক্ত;
    UINT raw_device_গুনতি = 0;
    পূর্ণাঙ্ক old_keyboard_গুনতি = 0;
    SDL_KeyboardID *old_keyboards = রিক্ত;
    পূর্ণাঙ্ক new_keyboard_গুনতি = 0;
    SDL_KeyboardID *new_keyboards = রিক্ত;
    পূর্ণাঙ্ক old_mouse_গুনতি = 0;
    SDL_MouseID *old_mice = রিক্ত;
    পূর্ণাঙ্ক new_mouse_গুনতি = 0;
    SDL_MouseID *new_mice = রিক্ত;

    যদি (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        প্রত্যাগম;
    }

    যদি ((Get_Raw_প্রবেশ_Device_List(রিক্ত, &raw_device_গুনতি, পরিমাণ(RAWINPUTDEVICELIST)) == -1) || (!raw_device_গুনতি)) {
        প্রত্যাগম; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(পরিমাণ(RAWINPUTDEVICELIST) * raw_device_গুনতি);
    যদি (!raw_devices) {
        প্রত্যাগম; // oh well.
    }

    raw_device_গুনতি = Get_Raw_প্রবেশ_Device_List(raw_devices, &raw_device_গুনতি, পরিমাণ(RAWINPUTDEVICELIST));
    যদি (raw_device_গুনতি == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = রিক্ত;
        প্রত্যাগম; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(রিক্ত, রিক্ত, রিক্ত, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_গুনতি);
    old_mice = SDL_GetMice(&old_mouse_গুনতি);

    প্রতি (UINT i = 0; i < raw_device_গুনতি; i++) {
        RID_DEVICE_INFO rdi;
        বর্ণ devName[MAX_PATH] = { 0 };
        UINT rdiSize = পরিমাণ(rdi);
        UINT nameSize = SDL_arraysize(devName);
        পূর্ণাঙ্ক vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        বর্ণ *instance, *ptr, *name;

        যদি (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            অনুবর্ত;
        }

        rdi.cbSize = পরিমাণ(rdi);
        যদি (Get_Raw_প্রবেশ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_প্রবেশ_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            অনুবর্ত;
        }

        // Extract the device instance
        instance = devName;
        যাবত্ (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        প্রতি (ptr = instance; *ptr; ++ptr) {
            যদি (*ptr == '#') {
                *ptr = '\\';
            }
            যদি (*ptr == '{') {
                যদি (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                ভঙ্গ;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        বিকল্প (dwType) {
        পক্ষ RIM_TYPEKEYBOARD:
            যদি (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_সংখ্যা_Of_চাবিগুলি_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_গুনতি);
                যদি (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_গুনতি)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            ভঙ্গ;
        পক্ষ RIM_TYPEMOUSE:
            যদি (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_গুনতি);
                যদি (!HasDeviceID(mouseID, old_mice, old_mouse_গুনতি)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
        }
    }

    প্রতি (পূর্ণাঙ্ক i = old_keyboard_গুনতি; i--;) {
        যদি (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_গুনতি)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    প্রতি (পূর্ণাঙ্ক i = old_mouse_গুনতি; i--;) {
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
        প্রত্যাগম false;
    }

    // Is this an extended key (i.e. right key)?
    যদি (lParam & 0x01000000) {
        প্রত্যাগম false;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    বার্তা_2 next_বার্তা;
    DWORD বার্তা_time = GetMessageTime();
    যদি (PeekMessage(&next_বার্তা, রিক্ত, 0, 0, PM_NOREMOVE)) {
        যদি (next_বার্তা.message == WM_KEYDOWN ||
            next_বার্তা.message == WM_SYSKEYDOWN) {
            যদি (next_বার্তা.wParam == VK_MENU && (next_বার্তা.lParam & 0x01000000) && next_বার্তা.time == বার্তা_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                প্রত্যাগম true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    প্রত্যাগম false;
}

স্থির bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *বার্তা, WPARAM *wParam, LPARAM *lParam)
{
    বার্তা_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *বার্তা;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    যদি (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *বার্তা = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    যদি (!data) {
        প্রত্যাগম CallWindowProc(DefWindowProc, hwnd, বার্তা, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        বর্ণ message[1024];
        যদি (বার্তা > MAX_WMMSG) {
            SDL_snprintf(message, পরিমাণ(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, বার্তা, wParam, lParam);
        } অন্যথা {
            SDL_snprintf(message, পরিমাণ(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[বার্তা], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    যদি (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        যদি (!DispatchModalLoopMessageHook(&hwnd, &বার্তা, &wParam, &lParam)) {
            প্রত্যাগম 0;
        }
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (WIN_HandleIMEMessage(hwnd, বার্তা, wParam, &lParam, data->videodata)) {
        প্রত্যাগম 0;
    }
#endif

    বিকল্প (বার্তা) {

    পক্ষ WM_SHOWWINDOW:
    {
        যদি (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } অন্যথা {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } ভঙ্গ;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    পক্ষ WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        data->postpone_clipcursor = true;
        data->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        POINT pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(data->window, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        যদি (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } ভঙ্গ;

    পক্ষ WM_NCUAHDRAWCAPTION:
    পক্ষ WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        যদি (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } ভঙ্গ;

    পক্ষ WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ধ্রুব DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } ভঙ্গ;

    পক্ষ WM_MOUSEACTIVATE:
    {
        যদি (SDL_WINDOW_IS_POPUP(data->window)) {
            প্রত্যাগম MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        যাবত্ (parent) {
            যদি ((parent->flags & SDL_WINDOW_প্রবেশ_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                প্রত্যাগম MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } ভঙ্গ;

    পক্ষ WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ধ্রুব DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } ভঙ্গ;

    পক্ষ WM_KILLFOCUS:
    পক্ষ WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ধ্রুব DWORD বার্তা_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(বার্তা_Pos), GET_Y_LPARAM(বার্তা_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } ভঙ্গ;

    পক্ষ WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুব UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!data->videodata->GetPointerType) {
            ভঙ্গ;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } অন্যথা যদি (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            ভঙ্গ;  // oh well.
        } অন্যথা যদি (pointer_type != PT_PEN) {
            ভঙ্গ;  // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুব SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        যদি (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
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
            SDL_AddPenDevice(WIN_GetEventTimestamp(), রিক্ত, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } ভঙ্গ;

    পক্ষ WM_POINTERCAPTURECHANGED:
    পক্ষ WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুব UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!data->videodata->GetPointerType) {
            ভঙ্গ;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } অন্যথা যদি (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            ভঙ্গ;  // oh well.
        } অন্যথা যদি (pointer_type != PT_PEN) {
            ভঙ্গ;  // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুব SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        যদি (pen == 0) {
            ভঙ্গ;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        যদি ((বার্তা == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } ভঙ্গ;

    পক্ষ WM_POINTERDOWN:
    পক্ষ WM_POINTERUP:
    পক্ষ WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ধ্রুব UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_প্রবেশ_TYPE pointer_type = PT_POINTER;
        যদি (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            ভঙ্গ;  // oh well.
        } অন্যথা যদি ((বার্তা == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            ভঙ্গ;
        } অন্যথা যদি (pointer_type != PT_PEN) {
            ভঙ্গ; // we only care about pens here.
        }

        শূন্য *hpointer = (শূন্য *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ধ্রুব SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        যদি (pen == 0) {
            ভঙ্গ;  // not a pen, or not a pen we already knew about.
        } অন্যথা যদি (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            ভঙ্গ;  // oh well.
        }

        ধ্রুব Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        ধ্রুব bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        যদি (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ধ্রুব POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        ভিন্ন fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        যদি (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (ভিন্ন) position.x;
            fy = (ভিন্ন) position.y;
        } অন্যথা {
            পূর্ণাঙ্ক ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            ধ্রুব SDL_FPoint window_pos = { (ভিন্ন) ix, (ভিন্ন) iy };

            ধ্রুব ভিন্ন facX = pointer_info->ptHimetricLocationRaw.x / (ভিন্ন) (tablet_bounds.ডান );
            ধ্রুব ভিন্ন facY = pointer_info->ptHimetricLocationRaw.y / (ভিন্ন) (tablet_bounds.bottom);

            ধ্রুব ভিন্ন w = tablet_mapping.ডান  - tablet_mapping.বাম;
            ধ্রুব ভিন্ন h = tablet_mapping.bottom - tablet_mapping.শীর্ষ;

            fx = (tablet_mapping.বাম + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.শীর্ষ  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        যদি (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((ভিন্ন) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        যদি (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((ভিন্ন) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        যদি (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((ভিন্ন) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        যদি (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((ভিন্ন) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        যদি (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } ভঙ্গ;

    পক্ষ WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        যদি (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            যদি (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        যদি (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = পরিমাণ(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            যদি (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        যদি (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            যদি (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (ভিন্ন)GET_X_LPARAM(lParam), (ভিন্ন)GET_Y_LPARAM(lParam));
            }
        }

    } ভঙ্গ;

    পক্ষ WM_LBUTTONUP:
    পক্ষ WM_RBUTTONUP:
    পক্ষ WM_MBUTTONUP:
    পক্ষ WM_XBUTTONUP:
    পক্ষ WM_LBUTTONDOWN:
    পক্ষ WM_LBUTTONDBLCLK:
    পক্ষ WM_RBUTTONDOWN:
    পক্ষ WM_RBUTTONDBLCLK:
    পক্ষ WM_MBUTTONDOWN:
    পক্ষ WM_MBUTTONDBLCLK:
    পক্ষ WM_XBUTTONDOWN:
    পক্ষ WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        যদি (!data->videodata->raw_mouse_enabled) {
            যদি (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } ভঙ্গ;

#যদি 0   // We handle raw input all at once instead of using a syscall for each mouse event
    পক্ষ WM_প্রবেশ:
    {
        HRAWINPUT h_Raw_প্রবেশ = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = পরিমাণ(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        যদি (data->window != SDL_GetKeyboardFocus()) {
            ভঙ্গ;
        }

        Get_Raw_প্রবেশ_Data(h_Raw_প্রবেশ, RID_প্রবেশ, &inp, &size, পরিমাণ(RAWINPUTHEADER));
        যদি (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_প্রবেশ(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } অন্যথা যদি (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_প্রবেশ(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } ভঙ্গ;
#endif

    পক্ষ WM_MOUSEWHEEL:
    পক্ষ WM_MOUSEHWHEEL:
    {
        যদি (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            ভিন্ন fAmount = (ভিন্ন)amount / WHEEL_DELTA;
            যদি (বার্তা == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } অন্যথা {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } ভঙ্গ;

    পক্ষ WM_MOUSELEAVE:
        যদি (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            যদি (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                যদি (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (ভিন্ন)cursorPos.x, (ভিন্ন)cursorPos.y);
                } অন্যথা {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    যদি (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (ভিন্ন)cursorPos.x, (ভিন্ন)cursorPos.y);
                    } অন্যথা { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (ভিন্ন)cursorPos.x, (ভিন্ন)cursorPos.y);
                    }
                }
            }

            যদি (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(রিক্ত);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        ভঙ্গ;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    পক্ষ WM_KEYDOWN:
    পক্ষ WM_SYSKEYDOWN:
    {
        যদি (Skip_Alt_Gr_বাম_Control(wParam, lParam)) {
            returnCode = 0;
            ভঙ্গ;
        }

        bool virtual_চাবি = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_চাবি);

        // Detect relevant keyboard shortcuts
        যদি (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            যদি (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        যদি (virtual_চাবি || !data->videodata->raw_keyboard_enabled || data->window->text_প্রবেশ_active) {
            SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        ভঙ্গ;

    পক্ষ WM_SYSKEYUP:
    পক্ষ WM_KEYUP:
    {
        যদি (Skip_Alt_Gr_বাম_Control(wParam, lParam)) {
            returnCode = 0;
            ভঙ্গ;
        }

        bool virtual_চাবি = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_চাবি);
        ধ্রুব bool *keyboardState = SDL_GetKeyboardState(রিক্ত);

        যদি (virtual_চাবি || !data->videodata->raw_keyboard_enabled || data->window->text_প্রবেশ_active) {
            যদি (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_চাবি(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        ভঙ্গ;

    পক্ষ WM_UNICHAR:
        যদি (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } অন্যথা {
            যদি (SDL_Text_প্রবেশ_Active(data->window)) {
                বর্ণ text[5];
                বর্ণ *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        ভঙ্গ;

    পক্ষ WM_CHAR:
        যদি (SDL_Text_প্রবেশ_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            যদি (IS_উপরের_SURROGATE(wParam)) {
                data->উপরের_surrogate = (WCHAR)wParam;
            } অন্যথা {
                WCHAR utf16[3];

                utf16[0] = data->উপরের_surrogate ? data->উপরের_surrogate : (WCHAR)wParam;
                utf16[1] = data->উপরের_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                বর্ণ utf8[5];
                পূর্ণাঙ্ক result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, পরিমাণ(utf8), রিক্ত, রিক্ত);
                যদি (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->উপরের_surrogate = L'\0';
            }
        } অন্যথা {
            data->উপরের_surrogate = L'\0';
        }

        returnCode = 0;
        ভঙ্গ;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    পক্ষ WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        ভঙ্গ;
#endif // WM_INPUTLANGCHANGE

    পক্ষ WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        যদি (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } ভঙ্গ;

    পক্ষ WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } ভঙ্গ;

#ifdef WM_GETMINMAXINFO
    পক্ষ WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        পূর্ণাঙ্ক x, y;
        পূর্ণাঙ্ক w, h;
        পূর্ণাঙ্ক min_w, min_h;
        পূর্ণাঙ্ক max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        যদি (data->expected_resize) {
            ভঙ্গ;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.বাম;
        y = size.শীর্ষ;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        যদি (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } অন্যথা {
            constrain_max_size = FALSE;
        }

        যদি (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.শীর্ষ = 0;
            size.বাম = 0;
            size.bottom = h;
            size.ডান = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.ডান - size.বাম;
            h = size.bottom - size.শীর্ষ;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        যদি (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            যদি (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                পূর্ণাঙ্ক screenW = GetSystemMetrics(SM_CXSCREEN);
                পূর্ণাঙ্ক screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            যদি (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } অন্যথা {
            info->ptMaxSize.x = w;
            info->ptMaxSize.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->ptMinTrackSize.x = w;
            info->ptMinTrackSize.y = h;
            info->ptMaxTrackSize.x = w;
            info->ptMaxTrackSize.y = h;
        }
    }
        returnCode = 0;
        ভঙ্গ;
#endif // WM_GETMINMAXINFO

    পক্ষ WM_WINDOWPOSCHANGING:

        যদি (data->expected_resize) {
            returnCode = 0;
        } অন্যথা যদি (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            যদি (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        ভঙ্গ;

    পক্ষ WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        ধ্রুব SDL_DisplayID original_displayID = data->window->displayID;
        ধ্রুব WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        পূর্ণাঙ্ক x, y;
        পূর্ণাঙ্ক w, h;

        যদি (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        যদি (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } অন্যথা যদি (zoomed) {
            যদি (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } অন্যথা যদি (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            যদি (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        যদি (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        যদি (iconic) {
            ভঙ্গ;
        }

        যদি (data->initializing) {
            ভঙ্গ;
        }

        যদি (!data->disable_move_size_events) {
            যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.বাম;
                y = rect.শীর্ষ;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.ডান;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        যদি (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        প্রতি (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            যদি (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } ভঙ্গ;

    পক্ষ WM_ENTERSIZEMOVE:
    পক্ষ WM_ENTERMENULOOP:
    {
        যদি (g_WindowsMessageHook) {
            যদি (!DispatchModalLoopMessageHook(&hwnd, &বার্তা, &wParam, &lParam)) {
                প্রত্যাগম 0;
            }
        }

        ++data->in_modal_loop;
        যদি (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.ডান - rect.বাম;
            data->last_modal_height = rect.bottom - rect.শীর্ষ;

            data->initial_size_rect.বাম = data->window->x;
            data->initial_size_rect.ডান = data->window->x + data->window->w;
            data->initial_size_rect.শীর্ষ = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, রিক্ত);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } ভঙ্গ;

    পক্ষ WM_TIMER:
    {
        যদি (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#যদি 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            যদি (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            প্রত্যাগম 0;
        }
    } ভঙ্গ;

    পক্ষ WM_EXITSIZEMOVE:
    পক্ষ WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        যদি (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } ভঙ্গ;

    পক্ষ WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            ভিন্ন new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            যদি (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                ভঙ্গ;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            যদি (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != রিক্ত, GetWindowExStyle(hwnd))) {
                ভঙ্গ;
            }

            clientDragRect.বাম -= rc.বাম;
            clientDragRect.শীর্ষ -= rc.শীর্ষ;
            clientDragRect.ডান -= rc.ডান;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.ডান - clientDragRect.বাম;
            h = clientDragRect.bottom - clientDragRect.শীর্ষ;
            new_aspect = w / (ভিন্ন)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            যদি (lock_aspect_ratio) {
                বিকল্প (edge) {
                পক্ষ WMSZ_বাম:
                পক্ষ WMSZ_ডান:
                    h = (পূর্ণাঙ্ক)SDL_roundf(w / data->window->max_aspect);
                    ভঙ্গ;
                স্বভাব:
                    // resizing via corners or top or bottom
                    w = (পূর্ণাঙ্ক)SDL_roundf(h * data->window->max_aspect);
                    ভঙ্গ;
                }
            } অন্যথা {
                বিকল্প (edge) {
                পক্ষ WMSZ_বাম:
                পক্ষ WMSZ_ডান:
                    যদি (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (পূর্ণাঙ্ক)SDL_roundf(h * data->window->max_aspect);
                    } অন্যথা যদি (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (পূর্ণাঙ্ক)SDL_roundf(h * data->window->min_aspect);
                    }
                    ভঙ্গ;
                পক্ষ WMSZ_শীর্ষ:
                পক্ষ WMSZ_BOTTOM:
                    যদি (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (পূর্ণাঙ্ক)SDL_roundf(w / data->window->min_aspect);
                    } অন্যথা যদি (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (পূর্ণাঙ্ক)SDL_roundf(w / data->window->max_aspect);
                    }
                    ভঙ্গ;

                স্বভাব:
                    // resizing via corners
                    যদি (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (পূর্ণাঙ্ক)SDL_roundf(h * data->window->max_aspect);
                    } অন্যথা যদি (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (পূর্ণাঙ্ক)SDL_roundf(w / data->window->min_aspect);
                    }
                    ভঙ্গ;
                }
            }

            বিকল্প (edge) {
            পক্ষ WMSZ_বাম:
                clientDragRect.বাম = clientDragRect.ডান - w;
                যদি (lock_aspect_ratio) {
                    clientDragRect.শীর্ষ = (data->initial_size_rect.bottom + data->initial_size_rect.শীর্ষ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                ভঙ্গ;
            পক্ষ WMSZ_BOTTOMLEFT:
                clientDragRect.বাম = clientDragRect.ডান - w;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                ভঙ্গ;
            পক্ষ WMSZ_ডান:
                clientDragRect.ডান = w + clientDragRect.বাম;
                যদি (lock_aspect_ratio) {
                    clientDragRect.শীর্ষ = (data->initial_size_rect.bottom + data->initial_size_rect.শীর্ষ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                ভঙ্গ;
            পক্ষ WMSZ_TOPRIGHT:
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                ভঙ্গ;
            পক্ষ WMSZ_শীর্ষ:
                যদি (lock_aspect_ratio) {
                    clientDragRect.বাম = (data->initial_size_rect.ডান + data->initial_size_rect.বাম - w) / 2;
                }
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                ভঙ্গ;
            পক্ষ WMSZ_TOPLEFT:
                clientDragRect.বাম = clientDragRect.ডান - w;
                clientDragRect.শীর্ষ = clientDragRect.bottom - h;
                ভঙ্গ;
            পক্ষ WMSZ_BOTTOM:
                যদি (lock_aspect_ratio) {
                    clientDragRect.বাম = (data->initial_size_rect.ডান + data->initial_size_rect.বাম - w) / 2;
                }
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                ভঙ্গ;
            পক্ষ WMSZ_BOTTOMRIGHT:
                clientDragRect.ডান = w + clientDragRect.বাম;
                clientDragRect.bottom = h + clientDragRect.শীর্ষ;
                ভঙ্গ;
            }

            // convert the client rect to a window rect
            যদি (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != রিক্ত, GetWindowExStyle(hwnd))) {
                ভঙ্গ;
            }

            *dragRect = clientDragRect;
        }
        ভঙ্গ;

    পক্ষ WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        যদি (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } অন্যথা যদি (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(রিক্ত);
            returnCode = TRUE;
        }
    } ভঙ্গ;

        // We were occluded, refresh our display
    পক্ষ WM_PAINT:
    {
        RECT rect;
        যদি (GetUpdateRect(hwnd, &rect, FALSE)) {
            ধ্রুব LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            যদি (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, রিক্ত);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        ভঙ্গ;

        // We'll do our own drawing, prevent flicker
    পক্ষ WM_ERASEBKGND:
        যদি (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        প্রত্যাগম 1;

    পক্ষ WM_SYSCOMMAND:
    {
        যদি (!g_WindowsEnableMenuMnemonics) {
            যদি ((wParam & 0xFFF0) == SC_KEYMENU) {
                প্রত্যাগম 0;
            }
        }

#যদি defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        যদি ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            যদি (SDL_GetVideoDevice()->suspend_screensaver) {
                প্রত্যাগম 0;
            }
        }
#endif // System has screensaver support
    } ভঙ্গ;

    পক্ষ WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        ভঙ্গ;

    পক্ষ WM_TOUCH:
        যদি (data->videodata->Get_Touch_প্রবেশ_Info && data->videodata->Close_Touch_প্রবেশ_Handle) {
            UINT i, অঙ্ক_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, অঙ্ক_inputs, &isstack);
            যদি (inputs && data->videodata->Get_Touch_প্রবেশ_Info((HTOUCHINPUT)lParam, অঙ্ক_inputs, inputs, পরিমাণ(TOUCHINPUT))) {
                RECT rect;
                ভিন্ন x, y;

                যদি (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    যদি (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    ভঙ্গ;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.শীর্ষ *= 100;
                rect.বাম *= 100;
                rect.bottom *= 100;
                rect.ডান *= 100;

                প্রতি (i = 0; i < অঙ্ক_inputs; ++i) {
                    PTOUCHINPUT প্রবেশ = &inputs[i];
                    ধ্রুব পূর্ণাঙ্ক w = (rect.ডান - rect.বাম);
                    ধ্রুব পূর্ণাঙ্ক h = (rect.bottom - rect.শীর্ষ);

                    ধ্রুব SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)প্রবেশ->hSource);
                    ধ্রুব SDL_FingerID fingerId = (প্রবেশ->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    যদি (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (প্রবেশ->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        অনুবর্ত;
                    }

                    // Get the normalized coordinates for the window
                    যদি (w <= 1) {
                        x = 0.5f;
                    } অন্যথা {
                        x = (ভিন্ন)(প্রবেশ->x - rect.বাম) / (w - 1);
                    }
                    যদি (h <= 1) {
                        y = 0.5f;
                    } অন্যথা {
                        y = (ভিন্ন)(প্রবেশ->y - rect.শীর্ষ) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    যদি (প্রবেশ->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_প্রবেশ_Handle((HTOUCHINPUT)lParam);
            প্রত্যাগম 0;
        }
        ভঙ্গ;

#ifdef HAVE_TPCSHRD_H

    পক্ষ WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        প্রত্যাগম TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    পক্ষ WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT গুনতি = DragQueryFile(drop, 0xFFFFFFFF, রিক্ত, 0);
        প্রতি (i = 0; i < গুনতি; ++i) {
            UINT size = DragQueryFile(drop, i, রিক্ত, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(পরিমাণ(TCHAR) * size);
            যদি (buffer) {
                যদি (DragQueryFile(drop, i, buffer, size)) {
                    বর্ণ *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, রিক্ত, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        প্রত্যাগম 0;
    }

    পক্ষ WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } ভঙ্গ;

    পক্ষ WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        যদি (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            যদি (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                যদি (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ধ্রুব POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                যদি (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = পরিমাণ(info);
                    যদি (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } অন্যথা যদি (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                পূর্ণাঙ্ক w, h;
                যদি (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } অন্যথা {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].ডান = params->rgrc[0].বাম + w;
                params->rgrc[0].bottom = params->rgrc[0].শীর্ষ + h;
            }
            প্রত্যাগম 0;
        }
    } ভঙ্গ;

    পক্ষ WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        যদি (window->flags & SDL_WINDOW_TOOLTIP) {
            প্রত্যাগম HTTRANSPARENT;
        }

        যদি (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            যদি (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                বিকল্প (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        প্রত্যাগম ret;                                                        \
    }
                পক্ষ SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(রিক্ত, রিক্ত);
                    যদি (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        প্রত্যাগম HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                পক্ষ SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                পক্ষ SDL_HITTEST_RESIZE_শীর্ষ:
                    POST_HIT_TEST(HTTOP);
                পক্ষ SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                পক্ষ SDL_HITTEST_RESIZE_ডান:
                    POST_HIT_TEST(HTRIGHT);
                পক্ষ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                পক্ষ SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                পক্ষ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                পক্ষ SDL_HITTEST_RESIZE_বাম:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                পক্ষ SDL_HITTEST_NORMAL:
                    প্রত্যাগম HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } ভঙ্গ;

    পক্ষ WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        যদি (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ধ্রুব পূর্ণাঙ্ক nextDPI = (পূর্ণাঙ্ক)wParam;
            ধ্রুব পূর্ণাঙ্ক prevDPI = (পূর্ণাঙ্ক)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            পূর্ণাঙ্ক frame_w, frame_h;
            পূর্ণাঙ্ক query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                যদি (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.বাম + rect.ডান;
                frame_h = -rect.শীর্ষ + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.ডান = query_client_w_win;
                rect.bottom = query_client_h_win;

                যদি (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.ডান - rect.বাম;
                sizeInOut->cy = rect.bottom - rect.শীর্ষ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            প্রত্যাগম TRUE;
        }
        ভঙ্গ;

    পক্ষ WM_DPICHANGED:
        // Windows 8.1+
        {
            ধ্রুব পূর্ণাঙ্ক newDPI = HIWORD(wParam);
            RECT *ধ্রুব suggestedRect = (RECT *)lParam;
            পূর্ণাঙ্ক w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->বাম, suggestedRect->শীর্ষ, suggestedRect->ডান - suggestedRect->বাম, suggestedRect->bottom - suggestedRect->শীর্ষ);
#endif

            যদি (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                প্রত্যাগম 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.ডান = data->window->w;
                rect.bottom = data->window->h;

                যদি (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.ডান - rect.বাম;
                h = rect.bottom - rect.শীর্ষ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->বাম, suggestedRect->শীর্ষ, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         রিক্ত,
                         suggestedRect->বাম,
                         suggestedRect->শীর্ষ,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            প্রত্যাগম 0;
        }

    পক্ষ WM_SETTINGCHANGE:
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
        ভঙ্গ;
#অন্যথা
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    পক্ষ WM_SIZE:
    {
        RECT rect;
        পূর্ণাঙ্ক w, h;

        যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.ডান;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } ভঙ্গ;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    স্বভাব:
        ভঙ্গ;
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (বার্তা && বার্তা == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    যদি (data->wndproc) {
        প্রত্যাগম CallWindowProc(data->wndproc, hwnd, বার্তা, wParam, lParam);
    } অন্যথা যদি (returnCode >= 0) {
        প্রত্যাগম returnCode;
    } অন্যথা {
        প্রত্যাগম CallWindowProc(DefWindowProc, hwnd, বার্তা, wParam, lParam);
    }
}

পূর্ণাঙ্ক WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    যদি (g_WindowsEnableMessageLoop) {
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = বার্তা_Wait_For_Multiple_Objects(0, রিক্ত, FALSE, timeout, QS_ALLINPUT);
        যদি (ret == WAIT_OBJECT_0) {
            প্রত্যাগম 1;
        } অন্যথা {
            প্রত্যাগম 0;
        }
#অন্যথা
        // MsgWaitForMultipleObjects is desktop-only.
        বার্তা_2 বার্তা;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        যদি (timeoutNS > 0) {
            timer_id = SetTimer(রিক্ত, 0, (UINT)SDL_NS_TO_MS(timeoutNS), রিক্ত);
            message_result = GetMessage(&বার্তা, 0, 0, 0);
            KillTimer(রিক্ত, timer_id);
        } অন্যথা যদি (timeoutNS == 0) {
            message_result = PeekMessage(&বার্তা, রিক্ত, 0, 0, PM_REMOVE);
        } অন্যথা {
            message_result = GetMessage(&বার্তা, 0, 0, 0);
        }
        যদি (message_result) {
            যদি (বার্তা.message == WM_TIMER && !বার্তা.hwnd && বার্তা.wParam == timer_id) {
                প্রত্যাগম 0;
            }
            যদি (g_WindowsMessageHook) {
                যদি (!g_WindowsMessageHook(g_WindowsMessageHookData, &বার্তা)) {
                    প্রত্যাগম 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&বার্তা);
            DispatchMessage(&বার্তা);
            প্রত্যাগম 1;
        } অন্যথা {
            প্রত্যাগম 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } অন্যথা {
        // Fail the wait so the caller falls back to polling
        প্রত্যাগম -1;
    }
}

শূন্য WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
শূন্য WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    বার্তা_2 বার্তা;

    যদি (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        যাবত্ (PeekMessage(&বার্তা, hwnd, 0, 0, PM_REMOVE)) {
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
    পূর্ণাঙ্ক new_messages = 0;

    যদি (_this->internal->gameinput_context) {
        WIN_Update_Game_প্রবেশ(_this);
    }

    যদি (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        যাবত্ (PeekMessage(&বার্তা, রিক্ত, 0, 0, PM_REMOVE)) {
            যদি (g_WindowsMessageHook) {
                যদি (!g_WindowsMessageHook(g_WindowsMessageHookData, &বার্তা)) {
                    অনুবর্ত;
                }
            }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            যদি (বার্তা.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                যদি (!SDL_TICKS_PASSED(বার্তা.time, (SDL_last_warp_time + 1))) {
                    অনুবর্ত;
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
                ধ্রুব পূর্ণাঙ্ক MAX_NEW_MESSAGES = 3;
                ++new_messages;
                যদি (new_messages > MAX_NEW_MESSAGES) {
                    ভঙ্গ;
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
    ধ্রুব bool *keystate = SDL_GetKeyboardState(রিক্ত);
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
        যাবত্ (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            যদি (data) {
                refresh_clipcursor = data->clipcursor_queued;
                data->clipcursor_queued = false;    // Must be cleared unconditionally.
                data->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            window = window->next;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focusWindow = SDL_GetKeyboardFocus();
    যদি (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        যদি (!data->mouse_tracked) {
            POINT cursorPos;

            যদি (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (ভিন্ন)cursorPos.x, (ভিন্ন)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_বাম : SDL_BUTTON_ডান,
                                    (Get_Async_চাবি_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_ডান : SDL_BUTTON_বাম,
                                    (Get_Async_চাবি_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_মধ্য,
                                    (Get_Async_চাবি_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_চাবি_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
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

স্থির পূর্ণাঙ্ক app_registered = 0;
LPTSTR SDL_Appname = রিক্ত;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = রিক্ত;

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
    SDL_Appname = রিক্ত;
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
    প্রত্যাগম FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(ধ্রুব বর্ণ *name, Uint32 style, শূন্য *hInst)
{
    WNDCLASSEX wcex;
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ধ্রুব বর্ণ *hint;
#endif

    // Only do this once...
    যদি (app_registered) {
        ++app_registered;
        প্রত্যাগম true;
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
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(রিক্ত);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = পরিমাণ(WNDCLASSEX);
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
        প্রত্যাগম SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    প্রত্যাগম true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
শূন্য SDL_UnregisterApp(শূন্য)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    যদি (!app_registered) {
        প্রত্যাগম;
    }
    --app_registered;
    যদি (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = রিক্ত;
        wcex.hIconSm = রিক্ত;
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
