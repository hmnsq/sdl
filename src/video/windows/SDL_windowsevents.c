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

#ifdef SDL_VIDEO_DRIVER_WINDOWS

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
#ifdef HAVE_TPCSHRD_H
#ضمن <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#ܐܢ 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#endif

#ܐܢ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#ضمن "../../core/gdk/SDL_gdk.h"
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
#ifndef WM_INPUT
#define WM_INPUT 0x00ff
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

#ifndef IS_HIGH_SURROGATE
#define IS_HIGH_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
تعريفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

ساكن bool SDL_processing_messages;
ساكن DWORD message_tick;
ساكن Uint64 timestamp_offset;

ساكن فراغ WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

ساكن Uint64 WIN_GetEventTimestamp(فراغ)
{
    ثابت Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    ܐܢ (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        ܦܢܐ 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    ܐܢ (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } ܐܚܪܢܐ ܐܢ ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } ܐܚܪܢܐ ܐܢ (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    ܦܢܐ timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_WindowsMessageHook g_WindowsMessageHook = عدم;
ساكن فراغ *g_WindowsMessageHookData = عدم;

فراغ SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, فراغ *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

ساكن SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_key)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 keyFlags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(keyFlags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_key = (scanCode == 0);

    ܐܢ (scanCode != 0) {
        ܐܢ ((keyFlags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } ܐܚܪܢܐ ܐܢ (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } ܐܚܪܢܐ {
        Uint16 vkCode = LOWORD(wParam);

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(MapVirtualKey(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        ܐܢ (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    ܦܢܐ code;
}

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    ܦܢܐ !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    ܐܢ (bSwapButtons) {
        ܐܢ (button == SDL_BUTTON_LEFT) {
            button = SDL_BUTTON_RIGHT;
        } ܐܚܪܢܐ ܐܢ (button == SDL_BUTTON_RIGHT) {
            button = SDL_BUTTON_LEFT;
        }
    }

    ܐܢ (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        ܐܢ (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        ܦܢܐ;
    }

    ܐܢ (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } ܐܚܪܢܐ ܐܢ (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    ܐܢ (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_LEFT, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_MIDDLE, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_RIGHT, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT keyState;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    keyState = GetAsyncKeyState(VK_LBUTTON);
    ܐܢ (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_LEFT, mouseID);
    }
    keyState = GetAsyncKeyState(VK_RBUTTON);
    ܐܢ (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_RIGHT, mouseID);
    }
    keyState = GetAsyncKeyState(VK_MBUTTON);
    ܐܢ (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_MIDDLE, mouseID);
    }
    keyState = GetAsyncKeyState(VK_XBUTTON1);
    ܐܢ (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    keyState = GetAsyncKeyState(VK_XBUTTON2);
    ܐܢ (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

ساكن فراغ WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    ܐܢ (had_focus == has_focus || has_focus != expect_focus) {
        ܦܢܐ;
    }

    ܐܢ (has_focus) {
        POINT cursorPos;

        ܐܢ (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            ܐܢ (GetAsyncKeyState(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            ܐܢ (GetAsyncKeyState(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            ܐܢ (GetAsyncKeyState(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            ܐܢ (GetAsyncKeyState(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            ܐܢ (GetAsyncKeyState(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        ܐܢ (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (GetKeyState(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_NUM, (GetKeyState(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (GetKeyState(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } ܐܚܪܢܐ {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        ܐܢ (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(عدم);
        }
        WIN_ResetDeadKeys();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool ShouldGenerateWindowCloseOnAltF4(فراغ)
{
    ܦܢܐ SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    بدل (data->hint_erase_background_mode) {
    حالة SDL_ERASEBACKGROUNDMODE_NEVER:
        ܦܢܐ false;
    حالة SDL_ERASEBACKGROUNDMODE_INITIAL:
        ܦܢܐ !data->videodata->cleared;
    حالة SDL_ERASEBACKGROUNDMODE_ALWAYS:
        ܦܢܐ true;
    افتراضي:
        // Unexpected value, fallback to default behaviour
        ܦܢܐ !data->videodata->cleared;
    }
}

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

تعريفنوع تعداد
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

ساكن SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    ܐܢ (IsTouchEvent(extrainfo)) {
        ܐܢ (extrainfo & 0x80) {
            ܦܢܐ SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } ܐܚܪܢܐ {
            ܦܢܐ SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    ܦܢܐ SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    ܐܢ (_this) {
        لكل (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            ܐܢ (data && data->hwnd == hwnd) {
                ܦܢܐ data;
            }
        }
    }
    ܦܢܐ عدم;
}

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    ܐܢ (nCode < 0 || nCode != HC_ACTION) {
        ܦܢܐ CallNextHookEx(عدم, nCode, wParam, lParam);
    }
    ܐܢ (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        ܦܢܐ 1;
    }

    بدل (hookData->vkCode) {
    حالة VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        اكسر;
    حالة VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        اكسر;
    حالة VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        اكسر;
    حالة VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        اكسر;
    حالة VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        اكسر;
    حالة VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        اكسر;
    حالة VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        اكسر;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالة VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        اكسر;
    حالة VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        اكسر;

    افتراضي:
        ܦܢܐ CallNextHookEx(عدم, nCode, wParam, lParam);
    }

    ܐܢ (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        ܐܢ (!data->raw_keyboard_enabled) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } ܐܚܪܢܐ {
        ܐܢ (!data->raw_keyboard_enabled) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        ܐܢ (hookData->vkCode <= 0xFF && data->pre_hook_key_state[hookData->vkCode]) {
            data->pre_hook_key_state[hookData->vkCode] = 0;
            ܦܢܐ CallNextHookEx(عدم, nCode, wParam, lParam);
        }
    }

    ܦܢܐ 1;
}

ساكن bool WIN_SwapButtons(HANDLE hDevice)
{
    ܐܢ (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        ܦܢܐ false;
    }
    ܦܢܐ GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_HandleRawMouseInput(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_LEFT_BUTTON_DOWN, SDL_BUTTON_LEFT, true },
        { RI_MOUSE_LEFT_BUTTON_UP, SDL_BUTTON_LEFT, false },
        { RI_MOUSE_RIGHT_BUTTON_DOWN, SDL_BUTTON_RIGHT, true },
        { RI_MOUSE_RIGHT_BUTTON_UP, SDL_BUTTON_RIGHT, false },
        { RI_MOUSE_MIDDLE_BUTTON_DOWN, SDL_BUTTON_MIDDLE, true },
        { RI_MOUSE_MIDDLE_BUTTON_UP, SDL_BUTTON_MIDDLE, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    صحيح dx = (صحيح)rawmouse->lLastX;
    صحيح dy = (صحيح)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    ܐܢ (!data->raw_mouse_enabled) {
        ܦܢܐ;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    ܐܢ (!window) {
        ܦܢܐ;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    ܐܢ (!mouse) {
        ܦܢܐ;
    }

    ܐܢ (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        ܦܢܐ;
    }

    SDL_WindowData *windowdata = window->internal;

    ܐܢ (haveMotion && !windowdata->in_modal_loop) {
        ܐܢ (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)dx, (عائم)dy);
        } ܐܚܪܢܐ {
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
            ܐܢ (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            ܐܢ (remote_desktop) {
                ܐܢ (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    ܐܢ (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.left + ((rect.right - rect.left) / 2) + wobble;
                        صحيح warpY = rect.top + ((rect.bottom - rect.top) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        ܐܢ (wobble > 1) {
                            wobble = -1;
                        }
                    } ܐܚܪܢܐ {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ثابت صحيح MAX_RELATIVE_MOTION = (h / 6);
                        ܐܢ (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } ܐܚܪܢܐ ܐܢ (mouse->pen_mouse_events) {
                ثابت صحيح MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                ܐܢ (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } ܐܚܪܢܐ {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } ܐܚܪܢܐ {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                ܐܢ (!data->raw_input_fake_pen_id) {
                    data->raw_input_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_input_fake_pen_id, window, (عائم)(x + screen_x - window->x), (عائم)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    ܐܢ (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            ܐܢ (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                ܐܢ (button == SDL_BUTTON_LEFT) {
                    ܐܢ (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_RIGHT;
                    }
                } ܐܚܪܢܐ ܐܢ (button == SDL_BUTTON_RIGHT) {
                    ܐܢ (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_LEFT;
                    }
                }

                ܐܢ (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    ܐܢ (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        ܐܢ (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } ܐܚܪܢܐ ܐܢ (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_HandleRawKeyboardInput(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    ܐܢ (!data->raw_keyboard_enabled) {
        ܦܢܐ;
    }

    ܐܢ (rawkeyboard->Flags & RI_KEY_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_key_sequence = true;
        ܦܢܐ;
    }

    ܐܢ ((rawkeyboard->Flags & RI_KEY_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        ܦܢܐ;
    }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ܐܢ (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(MapVirtualKey(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    ܐܢ (!rawkeyboard->MakeCode) {
        ܦܢܐ;
    }

    bool down;
    بدل (rawkeyboard->Message) {
    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
        down = true;
        اكسر;
    حالة WM_KEYUP:
    حالة WM_SYSKEYUP:
        down = false;
        اكسر;
    افتراضي:
        down = !(rawkeyboard->Flags & RI_KEY_BREAK);
        اكسر;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    ܐܢ (data->pending_E1_key_sequence) {
        rawcode |= 0xE100;
        ܐܢ (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } ܐܚܪܢܐ {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_key_sequence = false;
    } ܐܚܪܢܐ {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        ܐܢ (rawkeyboard->Flags & RI_KEY_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    ܐܢ (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        ܐܢ ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_input_active)) {
            ܦܢܐ;
        }
    }

    SDL_SendKeyboardKey(timestamp, keyboardID, rawcode, code, down);
}

فراغ WIN_PollRawInput(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, count, total = 0;
    RAWINPUT *input;
    Uint64 poll_finish;

    ܐܢ (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = حجم(RAWINPUTHEADER);
        ܐܢ (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    input = (RAWINPUT *)data->rawinput;
    لكل (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)input - data->rawinput);
        count = GetRawInputBuffer(input, &size, حجم(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        ܐܢ (count == 0 || count == (UINT)-1) {
            ܐܢ (!data->rawinput || (count == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                ثابت UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                ܐܢ (!rawinput) {
                    اكسر;
                }
                input = (RAWINPUT *)(rawinput + ((BYTE *)input - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } ܐܚܪܢܐ {
                اكسر;
            }
        } ܐܚܪܢܐ {
            total += count;

            // Advance input to the end of the buffer
            ܟܡܐ (count--) {
                input = NEXTRAWINPUTBLOCK(input);
            }
        }
    }

    ܐܢ (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        لكل (i = 0, input = (RAWINPUT *)data->rawinput; i < total; ++i, input = NEXTRAWINPUTBLOCK(input)) {
            ܐܢ (input->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        صحيح mouse_index = 0;
        لكل (i = 0, input = (RAWINPUT *)data->rawinput; i < total; ++i, input = NEXTRAWINPUTBLOCK(input)) {
            ܐܢ (input->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)input + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_HandleRawMouseInput(time, data, input->header.hDevice, rawmouse);
            } ܐܚܪܢܐ ܐܢ (input->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)input + data->rawinput_offset);
                WIN_HandleRawKeyboardInput(poll_finish, data, input->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

ساكن فراغ AddDeviceID(Uint32 deviceID, Uint32 **list, صحيح *count)
{
    صحيح new_count = (*count + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_count * حجم(*new_list));
    ܐܢ (!new_list) {
        // Oh well, we'll drop this one
        ܦܢܐ;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح count)
{
    لكل (صحيح i = 0; i < count; ++i) {
        ܐܢ (deviceID == list[i]) {
            ܦܢܐ true;
        }
    }
    ܦܢܐ false;
}

ساكن حرف *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت حرف *instance, Uint16 vendor, Uint16 product, ثابت حرف *default_name, bool hid_loaded)
{
    حرف *vendor_name = عدم;
    حرف *product_name = عدم;
    حرف *name = عدم;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    ܐܢ (hid_loaded) {
        حرف devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = GetRawInputDeviceInfoA(hDevice, RIDI_DEVICENAME, devName, &cap);
        ܐܢ (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            ܐܢ (hFile != INVALID_HANDLE_VALUE) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_HidD_GetProductString(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    ܐܢ (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    ܐܢ (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } ܐܚܪܢܐ {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = حجم(data);
        لكل (DWORD i = 0;; ++i) {
            ܐܢ (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                ܐܢ (GetLastError() == ERROR_NO_MORE_ITEMS) {
                    اكسر;
                } ܐܚܪܢܐ {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            ܐܢ (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            ܐܢ (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                ܐܢ (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= حجم(*prod);
                    ܐܢ (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    ܐܢ (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } ܐܚܪܢܐ {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                اكسر;
            }
        }
    }

    ܐܢ (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    ܦܢܐ name;
}

فراغ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = عدم;
    UINT raw_device_count = 0;
    صحيح old_keyboard_count = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_count = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_count = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_count = 0;
    SDL_MouseID *new_mice = عدم;

    ܐܢ (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        ܦܢܐ;
    }

    ܐܢ ((GetRawInputDeviceList(عدم, &raw_device_count, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_count)) {
        ܦܢܐ; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_count);
    ܐܢ (!raw_devices) {
        ܦܢܐ; // oh well.
    }

    raw_device_count = GetRawInputDeviceList(raw_devices, &raw_device_count, حجم(RAWINPUTDEVICELIST));
    ܐܢ (raw_device_count == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        ܦܢܐ; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_count);
    old_mice = SDL_GetMice(&old_mouse_count);

    لكل (UINT i = 0; i < raw_device_count; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_PATH] = { 0 };
        UINT rdiSize = حجم(rdi);
        UINT nameSize = SDL_arraysize(devName);
        صحيح vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        ܐܢ (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cbSize = حجم(rdi);
        ܐܢ (GetRawInputDeviceInfoA(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            GetRawInputDeviceInfoA(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            استمر;
        }

        // Extract the device instance
        instance = devName;
        ܟܡܐ (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        لكل (ptr = instance; *ptr; ++ptr) {
            ܐܢ (*ptr == '#') {
                *ptr = '\\';
            }
            ܐܢ (*ptr == '{') {
                ܐܢ (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                اكسر;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        بدل (dwType) {
        حالة RIM_TYPEKEYBOARD:
            ܐܢ (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dwNumberOfKeysTotal)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_count);
                ܐܢ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_count)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            ܐܢ (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_count);
                ܐܢ (!HasDeviceID(mouseID, old_mice, old_mouse_count)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }
    }

    لكل (صحيح i = old_keyboard_count; i--;) {
        ܐܢ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_count)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_count; i--;) {
        ܐܢ (!HasDeviceID(old_mice[i], new_mice, new_mouse_count)) {
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
ساكن bool SkipAltGrLeftControl(WPARAM wParam, LPARAM lParam)
{
    ܐܢ (wParam != VK_CONTROL) {
        ܦܢܐ false;
    }

    // Is this an extended key (i.e. right key)?
    ܐܢ (lParam & 0x01000000) {
        ܦܢܐ false;
    }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    MSG next_msg;
    DWORD msg_time = GetMessageTime();
    ܐܢ (PeekMessage(&next_msg, عدم, 0, 0, PM_NOREMOVE)) {
        ܐܢ (next_msg.message == WM_KEYDOWN ||
            next_msg.message == WM_SYSKEYDOWN) {
            ܐܢ (next_msg.wParam == VK_MENU && (next_msg.lParam & 0x01000000) && next_msg.time == msg_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                ܦܢܐ true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ܦܢܐ false;
}

ساكن bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *msg, WPARAM *wParam, LPARAM *lParam)
{
    MSG dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *msg;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    ܐܢ (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *msg = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ܐܢ (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    ܐܢ (!data) {
        ܦܢܐ CallWindowProc(DefWindowProc, hwnd, msg, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        حرف message[1024];
        ܐܢ (msg > MAX_WMMSG) {
            SDL_snprintf(message, حجم(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, msg, wParam, lParam);
        } ܐܚܪܢܐ {
            SDL_snprintf(message, حجم(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[msg], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    ܐܢ (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        ܐܢ (!DispatchModalLoopMessageHook(&hwnd, &msg, &wParam, &lParam)) {
            ܦܢܐ 0;
        }
    }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ܐܢ (WIN_HandleIMEMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
        ܦܢܐ 0;
    }
#endif

    بدل (msg) {

    حالة WM_SHOWWINDOW:
    {
        ܐܢ (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } ܐܚܪܢܐ {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } اكسر;

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالة WM_NCACTIVATE:
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
        ܐܢ (data->window->flags & SDL_WINDOW_BORDERLESS) {
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
        ܐܢ (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        ܐܢ (SDL_WINDOW_IS_POPUP(data->window)) {
            ܦܢܐ MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        ܟܡܐ (parent) {
            ܐܢ ((parent->flags & SDL_WINDOW_INPUT_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                ܦܢܐ MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ܐܢ (!data->videodata->GetPointerType) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ܐܚܪܢܐ ܐܢ (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } ܐܚܪܢܐ ܐܢ (pointer_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        ܐܢ (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } ܐܚܪܢܐ {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.num_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), عدم, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } اكسر;

    حالة WM_POINTERCAPTURECHANGED:
    حالة WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ܐܢ (!data->videodata->GetPointerType) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } ܐܚܪܢܐ ܐܢ (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } ܐܚܪܢܐ ܐܢ (pointer_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        ܐܢ (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        ܐܢ ((msg == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } اكسر;

    حالة WM_POINTERDOWN:
    حالة WM_POINTERUP:
    حالة WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ܐܢ (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } ܐܚܪܢܐ ܐܢ ((msg == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            اكسر;
        } ܐܚܪܢܐ ܐܢ (pointer_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        ܐܢ (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } ܐܚܪܢܐ ܐܢ (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        ثابت bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        ܐܢ (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        ܐܢ (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } ܐܚܪܢܐ {
            صحيح ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            ثابت SDL_FPoint window_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = pointer_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.right );
            ثابت عائم facY = pointer_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.right  - tablet_mapping.left;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.top;

            fx = (tablet_mapping.left + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.top  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        ܐܢ (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        ܐܢ (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        ܐܢ (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        ܐܢ (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        ܐܢ (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        ܐܢ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            ܐܢ (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        ܐܢ (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            ܐܢ (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        ܐܢ (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            ܐܢ (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (عائم)GET_X_LPARAM(lParam), (عائم)GET_Y_LPARAM(lParam));
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
        ܐܢ (!data->videodata->raw_mouse_enabled) {
            ܐܢ (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#ܐܢ 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_INPUT:
    {
        HRAWINPUT hRawInput = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        ܐܢ (data->window != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        GetRawInputData(hRawInput, RID_INPUT, &inp, &size, حجم(RAWINPUTHEADER));
        ܐܢ (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_HandleRawMouseInput(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } ܐܚܪܢܐ ܐܢ (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_HandleRawKeyboardInput(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } اكسر;
#endif

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        ܐܢ (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            ܐܢ (msg == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } ܐܚܪܢܐ {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        ܐܢ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            ܐܢ (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                ܐܢ (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } ܐܚܪܢܐ {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    ܐܢ (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } ܐܚܪܢܐ { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            ܐܢ (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(عدم);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        اكسر;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالة WM_KEYDOWN:
    حالة WM_SYSKEYDOWN:
    {
        ܐܢ (SkipAltGrLeftControl(wParam, lParam)) {
            returnCode = 0;
            اكسر;
        }

        bool virtual_key = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_key);

        // Detect relevant keyboard shortcuts
        ܐܢ (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            ܐܢ (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        ܐܢ (virtual_key || !data->videodata->raw_keyboard_enabled || data->window->text_input_active) {
            SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        ܐܢ (SkipAltGrLeftControl(wParam, lParam)) {
            returnCode = 0;
            اكسر;
        }

        bool virtual_key = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_key);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        ܐܢ (virtual_key || !data->videodata->raw_keyboard_enabled || data->window->text_input_active) {
            ܐܢ (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        اكسر;

    حالة WM_UNICHAR:
        ܐܢ (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } ܐܚܪܢܐ {
            ܐܢ (SDL_TextInputActive(data->window)) {
                حرف text[5];
                حرف *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        اكسر;

    حالة WM_CHAR:
        ܐܢ (SDL_TextInputActive(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            ܐܢ (IS_HIGH_SURROGATE(wParam)) {
                data->high_surrogate = (WCHAR)wParam;
            } ܐܚܪܢܐ {
                WCHAR utf16[3];

                utf16[0] = data->high_surrogate ? data->high_surrogate : (WCHAR)wParam;
                utf16[1] = data->high_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                ܐܢ (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->high_surrogate = L'\0';
            }
        } ܐܚܪܢܐ {
            data->high_surrogate = L'\0';
        }

        returnCode = 0;
        اكسر;

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    حالة WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        اكسر;
#endif // WM_INPUTLANGCHANGE

    حالة WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        ܐܢ (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } اكسر;

    حالة WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } اكسر;

#ifdef WM_GETMINMAXINFO
    حالة WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        صحيح x, y;
        صحيح w, h;
        صحيح min_w, min_h;
        صحيح max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        ܐܢ (data->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.left;
        y = size.top;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        ܐܢ (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } ܐܚܪܢܐ {
            constrain_max_size = FALSE;
        }

        ܐܢ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.top = 0;
            size.left = 0;
            size.bottom = h;
            size.right = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.right - size.left;
            h = size.bottom - size.top;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        ܐܢ (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            ܐܢ (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                صحيح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحيح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            ܐܢ (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } ܐܚܪܢܐ {
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
        اكسر;
#endif // WM_GETMINMAXINFO

    حالة WM_WINDOWPOSCHANGING:

        ܐܢ (data->expected_resize) {
            returnCode = 0;
        } ܐܚܪܢܐ ܐܢ (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            ܐܢ (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        اكسر;

    حالة WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        ثابت SDL_DisplayID original_displayID = data->window->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحيح x, y;
        صحيح w, h;

        ܐܢ (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        ܐܢ (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } ܐܚܪܢܐ ܐܢ (zoomed) {
            ܐܢ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } ܐܚܪܢܐ ܐܢ (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            ܐܢ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        ܐܢ (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        ܐܢ (iconic) {
            اكسر;
        }

        ܐܢ (data->initializing) {
            اكسر;
        }

        ܐܢ (!data->disable_move_size_events) {
            ܐܢ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.left;
                y = rect.top;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            ܐܢ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.right;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        ܐܢ (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        لكل (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ܐܢ (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        ܐܢ (g_WindowsMessageHook) {
            ܐܢ (!DispatchModalLoopMessageHook(&hwnd, &msg, &wParam, &lParam)) {
                ܦܢܐ 0;
            }
        }

        ++data->in_modal_loop;
        ܐܢ (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.right - rect.left;
            data->last_modal_height = rect.bottom - rect.top;

            data->initial_size_rect.left = data->window->x;
            data->initial_size_rect.right = data->window->x + data->window->w;
            data->initial_size_rect.top = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        ܐܢ (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ܐܢ 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            ܐܢ (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            ܦܢܐ 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        ܐܢ (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } اكسر;

    حالة WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            عائم new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            ܐܢ (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            ܐܢ (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != عدم, GetWindowExStyle(hwnd))) {
                اكسر;
            }

            clientDragRect.left -= rc.left;
            clientDragRect.top -= rc.top;
            clientDragRect.right -= rc.right;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.right - clientDragRect.left;
            h = clientDragRect.bottom - clientDragRect.top;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            ܐܢ (lock_aspect_ratio) {
                بدل (edge) {
                حالة WMSZ_LEFT:
                حالة WMSZ_RIGHT:
                    h = (صحيح)SDL_roundf(w / data->window->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    اكسر;
                }
            } ܐܚܪܢܐ {
                بدل (edge) {
                حالة WMSZ_LEFT:
                حالة WMSZ_RIGHT:
                    ܐܢ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    } ܐܚܪܢܐ ܐܢ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_TOP:
                حالة WMSZ_BOTTOM:
                    ܐܢ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->min_aspect);
                    } ܐܚܪܢܐ ܐܢ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    ܐܢ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    } ܐܚܪܢܐ ܐܢ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (edge) {
            حالة WMSZ_LEFT:
                clientDragRect.left = clientDragRect.right - w;
                ܐܢ (lock_aspect_ratio) {
                    clientDragRect.top = (data->initial_size_rect.bottom + data->initial_size_rect.top - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.top;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.left = clientDragRect.right - w;
                clientDragRect.bottom = h + clientDragRect.top;
                اكسر;
            حالة WMSZ_RIGHT:
                clientDragRect.right = w + clientDragRect.left;
                ܐܢ (lock_aspect_ratio) {
                    clientDragRect.top = (data->initial_size_rect.bottom + data->initial_size_rect.top - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.top;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.top = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOP:
                ܐܢ (lock_aspect_ratio) {
                    clientDragRect.left = (data->initial_size_rect.right + data->initial_size_rect.left - w) / 2;
                }
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.top = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.left = clientDragRect.right - w;
                clientDragRect.top = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                ܐܢ (lock_aspect_ratio) {
                    clientDragRect.left = (data->initial_size_rect.right + data->initial_size_rect.left - w) / 2;
                }
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.bottom = h + clientDragRect.top;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.bottom = h + clientDragRect.top;
                اكسر;
            }

            // convert the client rect to a window rect
            ܐܢ (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != عدم, GetWindowExStyle(hwnd))) {
                اكسر;
            }

            *dragRect = clientDragRect;
        }
        اكسر;

    حالة WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        ܐܢ (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } ܐܚܪܢܐ ܐܢ (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(عدم);
            returnCode = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        ܐܢ (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            ܐܢ (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, عدم);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        اكسر;

        // We'll do our own drawing, prevent flicker
    حالة WM_ERASEBKGND:
        ܐܢ (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        ܦܢܐ 1;

    حالة WM_SYSCOMMAND:
    {
        ܐܢ (!g_WindowsEnableMenuMnemonics) {
            ܐܢ ((wParam & 0xFFF0) == SC_KEYMENU) {
                ܦܢܐ 0;
            }
        }

#ܐܢ defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        ܐܢ ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            ܐܢ (SDL_GetVideoDevice()->suspend_screensaver) {
                ܦܢܐ 0;
            }
        }
#endif // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        اكسر;

    حالة WM_TOUCH:
        ܐܢ (data->videodata->GetTouchInputInfo && data->videodata->CloseTouchInputHandle) {
            UINT i, num_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, num_inputs, &isstack);
            ܐܢ (inputs && data->videodata->GetTouchInputInfo((HTOUCHINPUT)lParam, num_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                ܐܢ (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    ܐܢ (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.top *= 100;
                rect.left *= 100;
                rect.bottom *= 100;
                rect.right *= 100;

                لكل (i = 0; i < num_inputs; ++i) {
                    PTOUCHINPUT input = &inputs[i];
                    ثابت صحيح w = (rect.right - rect.left);
                    ثابت صحيح h = (rect.bottom - rect.top);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)input->hSource);
                    ثابت SDL_FingerID fingerId = (input->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    ܐܢ (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (input->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    ܐܢ (w <= 1) {
                        x = 0.5f;
                    } ܐܚܪܢܐ {
                        x = (عائم)(input->x - rect.left) / (w - 1);
                    }
                    ܐܢ (h <= 1) {
                        y = 0.5f;
                    } ܐܚܪܢܐ {
                        y = (عائم)(input->y - rect.top) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    ܐܢ (input->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    ܐܢ (input->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    ܐܢ (input->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->CloseTouchInputHandle((HTOUCHINPUT)lParam);
            ܦܢܐ 0;
        }
        اكسر;

#ifdef HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        ܦܢܐ TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT count = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < count; ++i) {
            UINT size = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(حجم(TCHAR) * size);
            ܐܢ (buffer) {
                ܐܢ (DragQueryFile(drop, i, buffer, size)) {
                    حرف *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, عدم, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        ܦܢܐ 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        ܐܢ (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            ܐܢ (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                ܐܢ (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                ܐܢ (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = حجم(info);
                    ܐܢ (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } ܐܚܪܢܐ ܐܢ (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                صحيح w, h;
                ܐܢ (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } ܐܚܪܢܐ {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].right = params->rgrc[0].left + w;
                params->rgrc[0].bottom = params->rgrc[0].top + h;
            }
            ܦܢܐ 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        ܐܢ (window->flags & SDL_WINDOW_TOOLTIP) {
            ܦܢܐ HTTRANSPARENT;
        }

        ܐܢ (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            ܐܢ (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                بدل (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        ܦܢܐ ret;                                                        \
    }
                حالة SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(عدم, عدم);
                    ܐܢ (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        ܦܢܐ HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_TOP:
                    POST_HIT_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_RIGHT:
                    POST_HIT_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_LEFT:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                حالة SDL_HITTEST_NORMAL:
                    ܦܢܐ HTCLIENT;
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
        ܐܢ (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحيح nextDPI = (صحيح)wParam;
            ثابت صحيح prevDPI = (صحيح)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            صحيح frame_w, frame_h;
            صحيح query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                ܐܢ (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.left + rect.right;
                frame_h = -rect.top + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.right = query_client_w_win;
                rect.bottom = query_client_h_win;

                ܐܢ (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.right - rect.left;
                sizeInOut->cy = rect.bottom - rect.top;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            ܦܢܐ TRUE;
        }
        اكسر;

    حالة WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحيح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحيح w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->left, suggestedRect->top, suggestedRect->right - suggestedRect->left, suggestedRect->bottom - suggestedRect->top);
#endif

            ܐܢ (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                ܦܢܐ 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.right = data->window->w;
                rect.bottom = data->window->h;

                ܐܢ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.right - rect.left;
                h = rect.bottom - rect.top;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->left, suggestedRect->top, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         عدم,
                         suggestedRect->left,
                         suggestedRect->top,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            ܦܢܐ 0;
        }

    حالة WM_SETTINGCHANGE:
        ܐܢ (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        ܐܢ (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        ܐܢ (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        اكسر;
#ܐܚܪܢܐ
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    حالة WM_SIZE:
    {
        RECT rect;
        صحيح w, h;

        ܐܢ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.right;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } اكسر;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ܐܢ (msg && msg == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    ܐܢ (data->wndproc) {
        ܦܢܐ CallWindowProc(data->wndproc, hwnd, msg, wParam, lParam);
    } ܐܚܪܢܐ ܐܢ (returnCode >= 0) {
        ܦܢܐ returnCode;
    } ܐܚܪܢܐ {
        ܦܢܐ CallWindowProc(DefWindowProc, hwnd, msg, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    ܐܢ (g_WindowsEnableMessageLoop) {
#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = MsgWaitForMultipleObjects(0, عدم, FALSE, timeout, QS_ALLINPUT);
        ܐܢ (ret == WAIT_OBJECT_0) {
            ܦܢܐ 1;
        } ܐܚܪܢܐ {
            ܦܢܐ 0;
        }
#ܐܚܪܢܐ
        // MsgWaitForMultipleObjects is desktop-only.
        MSG msg;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        ܐܢ (timeoutNS > 0) {
            timer_id = SetTimer(عدم, 0, (UINT)SDL_NS_TO_MS(timeoutNS), عدم);
            message_result = GetMessage(&msg, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } ܐܚܪܢܐ ܐܢ (timeoutNS == 0) {
            message_result = PeekMessage(&msg, عدم, 0, 0, PM_REMOVE);
        } ܐܚܪܢܐ {
            message_result = GetMessage(&msg, 0, 0, 0);
        }
        ܐܢ (message_result) {
            ܐܢ (msg.message == WM_TIMER && !msg.hwnd && msg.wParam == timer_id) {
                ܦܢܐ 0;
            }
            ܐܢ (g_WindowsMessageHook) {
                ܐܢ (!g_WindowsMessageHook(g_WindowsMessageHookData, &msg)) {
                    ܦܢܐ 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            ܦܢܐ 1;
        } ܐܚܪܢܐ {
            ܦܢܐ 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } ܐܚܪܢܐ {
        // Fail the wait so the caller falls back to polling
        ܦܢܐ -1;
    }
}

فراغ WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
فراغ WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    MSG msg;

    ܐܢ (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        ܟܡܐ (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(msg.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    MSG msg;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(push)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = GetTickCount() + 1;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    صحيح new_messages = 0;

    ܐܢ (_this->internal->gameinput_context) {
        WIN_UpdateGameInput(_this);
    }

    ܐܢ (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        ܟܡܐ (PeekMessage(&msg, عدم, 0, 0, PM_REMOVE)) {
            ܐܢ (g_WindowsMessageHook) {
                ܐܢ (!g_WindowsMessageHook(g_WindowsMessageHookData, &msg)) {
                    استمر;
                }
            }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            ܐܢ (msg.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                ܐܢ (!SDL_TICKS_PASSED(msg.time, (SDL_last_warp_time + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(msg.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            ܐܢ (SDL_TICKS_PASSED(msg.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ثابت صحيح MAX_NEW_MESSAGES = 3;
                ++new_messages;
                ܐܢ (new_messages > MAX_NEW_MESSAGES) {
                    اكسر;
                }
            }
        }

        SDL_processing_messages = false;
    }

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    ܐܢ (keystate[SDL_SCANCODE_LSHIFT] && !(GetKeyState(VK_LSHIFT) & 0x8000)) {
        SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    ܐܢ (keystate[SDL_SCANCODE_RSHIFT] && !(GetKeyState(VK_RSHIFT) & 0x8000)) {
        SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    ܐܢ (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ܐܢ (keystate[SDL_SCANCODE_LGUI] && !(GetKeyState(VK_LWIN) & 0x8000)) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        ܐܢ (keystate[SDL_SCANCODE_RGUI] && !(GetKeyState(VK_RWIN) & 0x8000)) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    ܐܢ (_this) {
        SDL_Window *window = _this->windows;
        ܟܡܐ (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            ܐܢ (data) {
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
            ܐܢ (refresh_clipcursor) {
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
    ܐܢ (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        ܐܢ (!data->mouse_tracked) {
            POINT cursorPos;

            ܐܢ (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_LEFT : SDL_BUTTON_RIGHT,
                                    (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_RIGHT : SDL_BUTTON_LEFT,
                                    (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_MIDDLE,
                                    (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

ساكن صحيح app_registered = 0;
LPTSTR SDL_Appname = عدم;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = عدم;

ساكن فراغ WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ܐܢ (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    ܐܢ (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = عدم;
}

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (فراغ)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    ܦܢܐ FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#endif

    // Only do this once...
    ܐܢ (app_registered) {
        ++app_registered;
        ܦܢܐ true;
    }
    SDL_assert(!SDL_Appname);
    ܐܢ (!name) {
        name = "SDL_app";
#ܐܢ defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(عدم);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = حجم(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    ܐܢ (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        ܐܢ (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } ܐܚܪܢܐ {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ܐܢ (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        ܦܢܐ SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    ܦܢܐ true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
فراغ SDL_UnregisterApp(فراغ)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    ܐܢ (!app_registered) {
        ܦܢܐ;
    }
    --app_registered;
    ܐܢ (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = عدم;
        wcex.hIconSm = عدم;
        // Check for any registered window classes.
#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ܐܢ (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
