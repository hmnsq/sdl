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

#إذا 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#ضمن <stdio.h>
#ضمن "wmmsg.h"
#endif

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
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
#ifndef WM_شغرو
#define WM_شغرو 0x00ff
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

#ifndef IS_سم_SURROGATE
#define IS_سم_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
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

    إذا (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        أرجع 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    إذا (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } وإلا إذا ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } وإلا إذا (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    أرجع timestamp;
}

// A message hook called before TranslateMessage()
ساكن SDL_WindowsMessageHook g_WindowsMessageHook = عدم;
ساكن فراغ *g_WindowsMessageHookData = عدم;

فراغ SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, فراغ *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

ساكن SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_مبودي)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 مبودي_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(مبودي_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_مبودي = (scanCode == 0);

    إذا (scanCode != 0) {
        إذا ((مبودي_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } وإلا إذا (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } وإلا {
        Uint16 vkCode = LOWORD(wParam);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_مبودي(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        إذا (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    أرجع code;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    أرجع !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ساكن فراغ WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    إذا (bSwapButtons) {
        إذا (button == SDL_BUTTON_هغو) {
            button = SDL_BUTTON_دام;
        } وإلا إذا (button == SDL_BUTTON_دام) {
            button = SDL_BUTTON_هغو;
        }
    }

    إذا (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        إذا (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        أرجع;
    }

    إذا (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } وإلا إذا (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ساكن فراغ WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    إذا (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(عدم, عدم);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_هغو, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_ڟكيا, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_دام, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

ساكن فراغ WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT مبودي_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(عدم, عدم);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    مبودي_State = Get_Async_مبودي_State(VK_LBUTTON);
    إذا (!(مبودي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_هغو, mouseID);
    }
    مبودي_State = Get_Async_مبودي_State(VK_RBUTTON);
    إذا (!(مبودي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_دام, mouseID);
    }
    مبودي_State = Get_Async_مبودي_State(VK_MBUTTON);
    إذا (!(مبودي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_ڟكيا, mouseID);
    }
    مبودي_State = Get_Async_مبودي_State(VK_XBUTTON1);
    إذا (!(مبودي_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    مبودي_State = Get_Async_مبودي_State(VK_XBUTTON2);
    إذا (!(مبودي_State & 0x8000)) {
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

    إذا (had_focus == has_focus || has_focus != expect_focus) {
        أرجع;
    }

    إذا (has_focus) {
        POINT cursorPos;

        إذا (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            إذا (Get_Async_مبودي_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            إذا (Get_Async_مبودي_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            إذا (Get_Async_مبودي_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            إذا (Get_Async_مبودي_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            إذا (Get_Async_مبودي_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        إذا (!SDL_GetMouse()->relative_mode) {
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

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_مبودي_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_لمب, (Get_مبودي_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_مبودي_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } وإلا {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(عدم);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        إذا (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(عدم);
        }
        WIN_Reset_Dead_مبوداي();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن bool ShouldGenerateWindowCloseOnAltF4(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ساكن bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    بدل (data->hint_erase_background_mode) {
    حالة SDL_ERASEBACKGROUNDMODE_NEVER:
        أرجع false;
    حالة SDL_ERASEBACKGROUNDMODE_INITIAL:
        أرجع !data->videodata->cleared;
    حالة SDL_ERASEBACKGROUNDMODE_ALWAYS:
        أرجع true;
    افتراضي:
        // Unexpected value, fallback to default behaviour
        أرجع !data->videodata->cleared;
    }
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
    إذا (IsTouchEvent(extrainfo)) {
        إذا (extrainfo & 0x80) {
            أرجع SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } وإلا {
            أرجع SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    أرجع SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    إذا (_this) {
        لكل (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            إذا (data && data->hwnd == hwnd) {
                أرجع data;
            }
        }
    }
    أرجع عدم;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحيح nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    إذا (nCode < 0 || nCode != HC_ACTION) {
        أرجع CallNextHookEx(عدم, nCode, wParam, lParam);
    }
    إذا (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        أرجع 1;
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
        أرجع CallNextHookEx(عدم, nCode, wParam, lParam);
    }

    إذا (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        إذا (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } وإلا {
        إذا (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        إذا (hookData->vkCode <= 0xFF && data->pre_hook_مبودي_state[hookData->vkCode]) {
            data->pre_hook_مبودي_state[hookData->vkCode] = 0;
            أرجع CallNextHookEx(عدم, nCode, wParam, lParam);
        }
    }

    أرجع 1;
}

ساكن bool WIN_SwapButtons(HANDLE hDevice)
{
    إذا (hDevice == عدم) {
        // Touchpad, already has buttons swapped
        أرجع false;
    }
    أرجع GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ساكن فراغ WIN_Handle_Raw_Mouse_شغرو(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ساكن بنية {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_هغو_BUTTON_DOWN, SDL_BUTTON_هغو, true },
        { RI_MOUSE_هغو_BUTTON_UP, SDL_BUTTON_هغو, false },
        { RI_MOUSE_دام_BUTTON_DOWN, SDL_BUTTON_دام, true },
        { RI_MOUSE_دام_BUTTON_UP, SDL_BUTTON_دام, false },
        { RI_MOUSE_ڟكيا_BUTTON_DOWN, SDL_BUTTON_ڟكيا, true },
        { RI_MOUSE_ڟكيا_BUTTON_UP, SDL_BUTTON_ڟكيا, false },
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
    إذا (!data->raw_mouse_enabled) {
        أرجع;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    إذا (!window) {
        أرجع;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse) {
        أرجع;
    }

    إذا (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        أرجع;
    }

    SDL_WindowData *windowdata = window->internal;

    إذا (haveMotion && !windowdata->in_modal_loop) {
        إذا (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)dx, (عائم)dy);
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
            إذا (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            إذا (remote_desktop) {
                إذا (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    ساكن صحيح wobble;
                    عائم floatX = (عائم)x / w;
                    عائم floatY = (عائم)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    إذا (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحيح warpX = rect.هغو + ((rect.دام - rect.هغو) / 2) + wobble;
                        صحيح warpY = rect.كولي + ((rect.bottom - rect.كولي) / 2);

                        WIN_SetCursorPos(warpX, warpY);

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
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)relX, (عائم)relY);
                        }
                    }
                }
            } وإلا إذا (mouse->pen_mouse_events) {
                ثابت صحيح MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                إذا (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وإلا {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (عائم)relX, (عائم)relY);
                }
            } وإلا {
                صحيح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحيح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                إذا (!data->raw_شغرو_fake_pen_id) {
                    data->raw_شغرو_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, عدم, (فراغ *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_شغرو_fake_pen_id, window, (عائم)(x + screen_x - window->x), (عائم)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    إذا (haveButton) {
        لكل (صحيح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            إذا (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                إذا (button == SDL_BUTTON_هغو) {
                    إذا (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_دام;
                    }
                } وإلا إذا (button == SDL_BUTTON_دام) {
                    إذا (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_هغو;
                    }
                }

                إذا (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    إذا (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    استمر;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        إذا (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } وإلا إذا (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ساكن فراغ WIN_Handle_Raw_Keyboard_شغرو(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    إذا (!data->raw_keyboard_enabled) {
        أرجع;
    }

    إذا (rawkeyboard->Flags & RI_مبودي_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_مبودي_sequence = true;
        أرجع;
    }

    إذا ((rawkeyboard->Flags & RI_مبودي_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        أرجع;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_مبودي(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    إذا (!rawkeyboard->MakeCode) {
        أرجع;
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
        down = !(rawkeyboard->Flags & RI_مبودي_BREAK);
        اكسر;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    إذا (data->pending_E1_مبودي_sequence) {
        rawcode |= 0xE100;
        إذا (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } وإلا {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_مبودي_sequence = false;
    } وإلا {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        إذا (rawkeyboard->Flags & RI_مبودي_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    إذا (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        إذا ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_شغرو_active)) {
            أرجع;
        }
    }

    SDL_Send_Keyboard_مبودي(timestamp, keyboardID, rawcode, code, down);
}

فراغ WIN_Poll_Raw_شغرو(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, كدي, total = 0;
    RAWINPUT *شغرو;
    Uint64 poll_finish;

    إذا (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = حجم(RAWINPUTHEADER);
        إذا (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    شغرو = (RAWINPUT *)data->rawinput;
    لكل (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)شغرو - data->rawinput);
        كدي = Get_Raw_شغرو_Buffer(شغرو, &size, حجم(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        إذا (كدي == 0 || كدي == (UINT)-1) {
            إذا (!data->rawinput || (كدي == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                ثابت UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                إذا (!rawinput) {
                    اكسر;
                }
                شغرو = (RAWINPUT *)(rawinput + ((BYTE *)شغرو - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } وإلا {
                اكسر;
            }
        } وإلا {
            total += كدي;

            // Advance input to the end of the buffer
            طالما (كدي--) {
                شغرو = NEXTRAWINPUTBLOCK(شغرو);
            }
        }
    }

    إذا (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        لكل (i = 0, شغرو = (RAWINPUT *)data->rawinput; i < total; ++i, شغرو = NEXTRAWINPUTBLOCK(شغرو)) {
            إذا (شغرو->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        صحيح mouse_index = 0;
        لكل (i = 0, شغرو = (RAWINPUT *)data->rawinput; i < total; ++i, شغرو = NEXTRAWINPUTBLOCK(شغرو)) {
            إذا (شغرو->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)شغرو + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_شغرو(time, data, شغرو->header.hDevice, rawmouse);
            } وإلا إذا (شغرو->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)شغرو + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_شغرو(poll_finish, data, شغرو->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

ساكن فراغ AddDeviceID(Uint32 deviceID, Uint32 **list, صحيح *كدي)
{
    صحيح new_كدي = (*كدي + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_كدي * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_كدي - 1] = deviceID;

    *كدي = new_كدي;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح كدي)
{
    لكل (صحيح i = 0; i < كدي; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
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

    إذا (hid_loaded) {
        حرف devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = حجم(devName) - 1;
        UINT len = Get_Raw_شغرو_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        إذا (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, عدم, OPEN_EXISTING, 0, عدم);
            إذا (hFile != INVALID_HANDLE_درج) {
                SDL_HidD_GetManufacturerString(hFile, vend, حجم(vend));
                SDL_HidD_GetProductString(hFile, prod, حجم(prod));
                CloseHandle(hFile);
            }
        }
    }

    إذا (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    إذا (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } وإلا {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = حجم(data);
        لكل (DWORD i = 0;; ++i) {
            إذا (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                إذا (GetLastError() == ERROR_NO_MORE_ابوبو) {
                    اكسر;
                } وإلا {
                    استمر;
                }
            }

            حرف DeviceInstanceId[64];
            إذا (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, حجم(DeviceInstanceId), عدم))
                استمر;

            إذا (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                إذا (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, عدم, (PBYTE)prod, حجم(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= حجم(*prod);
                    إذا (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    إذا (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } وإلا {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                اكسر;
            }
        }
    }

    إذا (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    أرجع name;
}

فراغ WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = عدم;
    UINT raw_device_كدي = 0;
    صحيح old_keyboard_كدي = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_كدي = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_كدي = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_كدي = 0;
    SDL_MouseID *new_mice = عدم;

    إذا (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        أرجع;
    }

    إذا ((Get_Raw_شغرو_Device_List(عدم, &raw_device_كدي, حجم(RAWINPUTDEVICELIST)) == -1) || (!raw_device_كدي)) {
        أرجع; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(حجم(RAWINPUTDEVICELIST) * raw_device_كدي);
    إذا (!raw_devices) {
        أرجع; // oh well.
    }

    raw_device_كدي = Get_Raw_شغرو_Device_List(raw_devices, &raw_device_كدي, حجم(RAWINPUTDEVICELIST));
    إذا (raw_device_كدي == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = عدم;
        أرجع; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(عدم, عدم, عدم, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_كدي);
    old_mice = SDL_GetMice(&old_mouse_كدي);

    لكل (UINT i = 0; i < raw_device_كدي; i++) {
        RID_DEVICE_INFO rdi;
        حرف devName[MAX_PATH] = { 0 };
        UINT rdiSize = حجم(rdi);
        UINT nameSize = SDL_arraysize(devName);
        صحيح vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        حرف *instance, *ptr, *name;

        إذا (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            استمر;
        }

        rdi.cbSize = حجم(rdi);
        إذا (Get_Raw_شغرو_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_شغرو_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
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

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        بدل (dwType) {
        حالة RIM_TYPEKEYBOARD:
            إذا (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_لمب_Of_مبوداي_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_كدي);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_كدي)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            اكسر;
        حالة RIM_TYPEMOUSE:
            إذا (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_كدي);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_كدي)) {
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

    لكل (صحيح i = old_keyboard_كدي; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_كدي)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_كدي; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_كدي)) {
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
ساكن bool Skip_Alt_Gr_هغو_Control(WPARAM wParam, LPARAM lParam)
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
    سكو_2 next_سكو;
    DWORD سكو_time = GetMessageTime();
    إذا (PeekMessage(&next_سكو, عدم, 0, 0, PM_NOREMOVE)) {
        إذا (next_سكو.message == WM_KEYDOWN ||
            next_سكو.message == WM_SYSKEYDOWN) {
            إذا (next_سكو.wParam == VK_MENU && (next_سكو.lParam & 0x01000000) && next_سكو.time == سكو_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                أرجع true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع false;
}

ساكن bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *سكو, WPARAM *wParam, LPARAM *lParam)
{
    سكو_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *سكو;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    إذا (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *سكو = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        أرجع true;
    }
    أرجع false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT سكو, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    إذا (!data) {
        أرجع CallWindowProc(DefWindowProc, hwnd, سكو, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        حرف message[1024];
        إذا (سكو > MAX_WMMSG) {
            SDL_snprintf(message, حجم(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, سكو, wParam, lParam);
        } وإلا {
            SDL_snprintf(message, حجم(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[سكو], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    إذا (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        إذا (!DispatchModalLoopMessageHook(&hwnd, &سكو, &wParam, &lParam)) {
            أرجع 0;
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (WIN_HandleIMEMessage(hwnd, سكو, wParam, &lParam, data->videodata)) {
        أرجع 0;
    }
#endif

    بدل (سكو) {

    حالة WM_SHOWWINDOW:
    {
        إذا (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } وإلا {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
        إذا (data->window->flags & SDL_WINDOW_BORDERLESS) {
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
        إذا (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } اكسر;

    حالة WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD سكو_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(سكو_Pos), GET_Y_LPARAM(سكو_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } اكسر;

    حالة WM_MOUSEACTIVATE:
    {
        إذا (SDL_WINDOW_IS_POPUP(data->window)) {
            أرجع MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        طالما (parent) {
            إذا ((parent->flags & SDL_WINDOW_شغرو_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                أرجع MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } اكسر;

    حالة WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD سكو_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(سكو_Pos), GET_Y_LPARAM(سكو_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } اكسر;

    حالة WM_KILLFOCUS:
    حالة WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD سكو_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(سكو_Pos), GET_Y_LPARAM(سكو_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } اكسر;

    حالة WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_شغرو_TYPE pointer_type = PT_POINTER;
        إذا (!data->videodata->GetPointerType) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } وإلا إذا (pointer_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        إذا (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } وإلا {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.لمب_buttons = 1;
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
        POINTER_شغرو_TYPE pointer_type = PT_POINTER;
        إذا (!data->videodata->GetPointerType) {
            اكسر;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وإلا إذا (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } وإلا إذا (pointer_type != PT_PEN) {
            اكسر;  // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        إذا ((سكو == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
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
        POINTER_شغرو_TYPE pointer_type = PT_POINTER;
        إذا (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            اكسر;  // oh well.
        } وإلا إذا ((سكو == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            اكسر;
        } وإلا إذا (pointer_type != PT_PEN) {
            اكسر; // we only care about pens here.
        }

        فراغ *hpointer = (فراغ *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        إذا (pen == 0) {
            اكسر;  // not a pen, or not a pen we already knew about.
        } وإلا إذا (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            اكسر;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        ثابت bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        إذا (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        عائم fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        إذا (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (عائم) position.x;
            fy = (عائم) position.y;
        } وإلا {
            صحيح ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            ثابت SDL_FPoint window_pos = { (عائم) ix, (عائم) iy };

            ثابت عائم facX = pointer_info->ptHimetricLocationRaw.x / (عائم) (tablet_bounds.دام );
            ثابت عائم facY = pointer_info->ptHimetricLocationRaw.y / (عائم) (tablet_bounds.bottom);

            ثابت عائم w = tablet_mapping.دام  - tablet_mapping.هغو;
            ثابت عائم h = tablet_mapping.bottom - tablet_mapping.كولي;

            fx = (tablet_mapping.هغو + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.كولي  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        إذا (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((عائم) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        إذا (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((عائم) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        إذا (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((عائم) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        إذا (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((عائم) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        إذا (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } اكسر;

    حالة WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        إذا (window->flags & SDL_WINDOW_شغرو_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            إذا (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        إذا (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = حجم(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            إذا (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        إذا (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            إذا (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
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
        إذا (!data->videodata->raw_mouse_enabled) {
            إذا (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } اكسر;

#إذا 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالة WM_شغرو:
    {
        HRAWINPUT h_Raw_شغرو = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = حجم(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        إذا (data->window != SDL_GetKeyboardFocus()) {
            اكسر;
        }

        Get_Raw_شغرو_Data(h_Raw_شغرو, RID_شغرو, &inp, &size, حجم(RAWINPUTHEADER));
        إذا (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_شغرو(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } وإلا إذا (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_شغرو(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } اكسر;
#endif

    حالة WM_MOUSEWHEEL:
    حالة WM_MOUSEHWHEEL:
    {
        إذا (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            عائم fAmount = (عائم)amount / WHEEL_DELTA;
            إذا (سكو == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } وإلا {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } اكسر;

    حالة WM_MOUSELEAVE:
        إذا (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            إذا (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                إذا (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                } وإلا {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    إذا (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    } وإلا { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                    }
                }
            }

            إذا (!SDL_GetMouse()->relative_mode) {
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
        إذا (Skip_Alt_Gr_هغو_Control(wParam, lParam)) {
            returnCode = 0;
            اكسر;
        }

        bool virtual_مبودي = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_مبودي);

        // Detect relevant keyboard shortcuts
        إذا (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            إذا (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        إذا (virtual_مبودي || !data->videodata->raw_keyboard_enabled || data->window->text_شغرو_active) {
            SDL_Send_Keyboard_مبودي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        اكسر;

    حالة WM_SYSKEYUP:
    حالة WM_KEYUP:
    {
        إذا (Skip_Alt_Gr_هغو_Control(wParam, lParam)) {
            returnCode = 0;
            اكسر;
        }

        bool virtual_مبودي = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_مبودي);
        ثابت bool *keyboardState = SDL_GetKeyboardState(عدم);

        إذا (virtual_مبودي || !data->videodata->raw_keyboard_enabled || data->window->text_شغرو_active) {
            إذا (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_مبودي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_مبودي(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        اكسر;

    حالة WM_UNICHAR:
        إذا (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } وإلا {
            إذا (SDL_Text_شغرو_Active(data->window)) {
                حرف text[5];
                حرف *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        اكسر;

    حالة WM_CHAR:
        إذا (SDL_Text_شغرو_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            إذا (IS_سم_SURROGATE(wParam)) {
                data->سم_surrogate = (WCHAR)wParam;
            } وإلا {
                WCHAR utf16[3];

                utf16[0] = data->سم_surrogate ? data->سم_surrogate : (WCHAR)wParam;
                utf16[1] = data->سم_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                حرف utf8[5];
                صحيح result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, حجم(utf8), عدم, عدم);
                إذا (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->سم_surrogate = L'\0';
            }
        } وإلا {
            data->سم_surrogate = L'\0';
        }

        returnCode = 0;
        اكسر;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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
        إذا (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
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
        إذا (data->expected_resize) {
            اكسر;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.هغو;
        y = size.كولي;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        إذا (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } وإلا {
            constrain_max_size = FALSE;
        }

        إذا (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.كولي = 0;
            size.هغو = 0;
            size.bottom = h;
            size.دام = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.دام - size.هغو;
            h = size.bottom - size.كولي;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        إذا (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            إذا (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                صحيح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحيح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            إذا (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } وإلا {
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

        إذا (data->expected_resize) {
            returnCode = 0;
        } وإلا إذا (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            إذا (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
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

        إذا (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        إذا (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } وإلا إذا (zoomed) {
            إذا (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } وإلا إذا (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            إذا (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        إذا (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        إذا (iconic) {
            اكسر;
        }

        إذا (data->initializing) {
            اكسر;
        }

        إذا (!data->disable_move_size_events) {
            إذا (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.هغو;
                y = rect.كولي;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            إذا (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.دام;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        إذا (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        لكل (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } اكسر;

    حالة WM_ENTERSIZEMOVE:
    حالة WM_ENTERMENULOOP:
    {
        إذا (g_WindowsMessageHook) {
            إذا (!DispatchModalLoopMessageHook(&hwnd, &سكو, &wParam, &lParam)) {
                أرجع 0;
            }
        }

        ++data->in_modal_loop;
        إذا (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.دام - rect.هغو;
            data->last_modal_height = rect.bottom - rect.كولي;

            data->initial_size_rect.هغو = data->window->x;
            data->initial_size_rect.دام = data->window->x + data->window->w;
            data->initial_size_rect.كولي = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, عدم);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } اكسر;

    حالة WM_TIMER:
    {
        إذا (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#إذا 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            إذا (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            أرجع 0;
        }
    } اكسر;

    حالة WM_EXITSIZEMOVE:
    حالة WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        إذا (data->in_modal_loop == 0) {
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
            إذا (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                اكسر;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            إذا (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != عدم, GetWindowExStyle(hwnd))) {
                اكسر;
            }

            clientDragRect.هغو -= rc.هغو;
            clientDragRect.كولي -= rc.كولي;
            clientDragRect.دام -= rc.دام;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.دام - clientDragRect.هغو;
            h = clientDragRect.bottom - clientDragRect.كولي;
            new_aspect = w / (عائم)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            إذا (lock_aspect_ratio) {
                بدل (edge) {
                حالة WMSZ_هغو:
                حالة WMSZ_دام:
                    h = (صحيح)SDL_roundf(w / data->window->max_aspect);
                    اكسر;
                افتراضي:
                    // resizing via corners or top or bottom
                    w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    اكسر;
                }
            } وإلا {
                بدل (edge) {
                حالة WMSZ_هغو:
                حالة WMSZ_دام:
                    إذا (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    } وإلا إذا (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->min_aspect);
                    }
                    اكسر;
                حالة WMSZ_كولي:
                حالة WMSZ_BOTTOM:
                    إذا (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->min_aspect);
                    } وإلا إذا (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->max_aspect);
                    }
                    اكسر;

                افتراضي:
                    // resizing via corners
                    إذا (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحيح)SDL_roundf(h * data->window->max_aspect);
                    } وإلا إذا (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحيح)SDL_roundf(w / data->window->min_aspect);
                    }
                    اكسر;
                }
            }

            بدل (edge) {
            حالة WMSZ_هغو:
                clientDragRect.هغو = clientDragRect.دام - w;
                إذا (lock_aspect_ratio) {
                    clientDragRect.كولي = (data->initial_size_rect.bottom + data->initial_size_rect.كولي - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.كولي;
                اكسر;
            حالة WMSZ_BOTTOMLEFT:
                clientDragRect.هغو = clientDragRect.دام - w;
                clientDragRect.bottom = h + clientDragRect.كولي;
                اكسر;
            حالة WMSZ_دام:
                clientDragRect.دام = w + clientDragRect.هغو;
                إذا (lock_aspect_ratio) {
                    clientDragRect.كولي = (data->initial_size_rect.bottom + data->initial_size_rect.كولي - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.كولي;
                اكسر;
            حالة WMSZ_TOPRIGHT:
                clientDragRect.دام = w + clientDragRect.هغو;
                clientDragRect.كولي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_كولي:
                إذا (lock_aspect_ratio) {
                    clientDragRect.هغو = (data->initial_size_rect.دام + data->initial_size_rect.هغو - w) / 2;
                }
                clientDragRect.دام = w + clientDragRect.هغو;
                clientDragRect.كولي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_TOPLEFT:
                clientDragRect.هغو = clientDragRect.دام - w;
                clientDragRect.كولي = clientDragRect.bottom - h;
                اكسر;
            حالة WMSZ_BOTTOM:
                إذا (lock_aspect_ratio) {
                    clientDragRect.هغو = (data->initial_size_rect.دام + data->initial_size_rect.هغو - w) / 2;
                }
                clientDragRect.دام = w + clientDragRect.هغو;
                clientDragRect.bottom = h + clientDragRect.كولي;
                اكسر;
            حالة WMSZ_BOTTOMRIGHT:
                clientDragRect.دام = w + clientDragRect.هغو;
                clientDragRect.bottom = h + clientDragRect.كولي;
                اكسر;
            }

            // convert the client rect to a window rect
            إذا (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != عدم, GetWindowExStyle(hwnd))) {
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
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } وإلا إذا (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(عدم);
            returnCode = TRUE;
        }
    } اكسر;

        // We were occluded, refresh our display
    حالة WM_PAINT:
    {
        RECT rect;
        إذا (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            إذا (style & WS_EX_COMPOSITED) {
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
        إذا (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
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
#endif // System has screensaver support
    } اكسر;

    حالة WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        اكسر;

    حالة WM_TOUCH:
        إذا (data->videodata->Get_Touch_شغرو_Info && data->videodata->Close_Touch_شغرو_Handle) {
            UINT i, لمب_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, لمب_inputs, &isstack);
            إذا (inputs && data->videodata->Get_Touch_شغرو_Info((HTOUCHINPUT)lParam, لمب_inputs, inputs, حجم(TOUCHINPUT))) {
                RECT rect;
                عائم x, y;

                إذا (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    إذا (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    اكسر;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.كولي *= 100;
                rect.هغو *= 100;
                rect.bottom *= 100;
                rect.دام *= 100;

                لكل (i = 0; i < لمب_inputs; ++i) {
                    PTOUCHINPUT شغرو = &inputs[i];
                    ثابت صحيح w = (rect.دام - rect.هغو);
                    ثابت صحيح h = (rect.bottom - rect.كولي);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)شغرو->hSource);
                    ثابت SDL_FingerID fingerId = (شغرو->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    إذا (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (شغرو->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        استمر;
                    }

                    // Get the normalized coordinates for the window
                    إذا (w <= 1) {
                        x = 0.5f;
                    } وإلا {
                        x = (عائم)(شغرو->x - rect.هغو) / (w - 1);
                    }
                    إذا (h <= 1) {
                        y = 0.5f;
                    } وإلا {
                        y = (عائم)(شغرو->y - rect.كولي) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    إذا (شغرو->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    إذا (شغرو->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    إذا (شغرو->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_شغرو_Handle((HTOUCHINPUT)lParam);
            أرجع 0;
        }
        اكسر;

#ifdef HAVE_TPCSHRD_H

    حالة WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        أرجع TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    حالة WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT كدي = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
        لكل (i = 0; i < كدي; ++i) {
            UINT size = DragQueryFile(drop, i, عدم, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(حجم(TCHAR) * size);
            إذا (buffer) {
                إذا (DragQueryFile(drop, i, buffer, size)) {
                    حرف *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, عدم, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        أرجع 0;
    }

    حالة WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } اكسر;

    حالة WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        إذا (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            إذا (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                إذا (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                إذا (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = حجم(info);
                    إذا (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وإلا إذا (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                صحيح w, h;
                إذا (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } وإلا {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].دام = params->rgrc[0].هغو + w;
                params->rgrc[0].bottom = params->rgrc[0].كولي + h;
            }
            أرجع 0;
        }
    } اكسر;

    حالة WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        إذا (window->flags & SDL_WINDOW_TOOLTIP) {
            أرجع HTTRANSPARENT;
        }

        إذا (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            إذا (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                بدل (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
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
                        SDL_SetMouseFocus(window);
                        أرجع HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                حالة SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                حالة SDL_HITTEST_RESIZE_كولي:
                    POST_HIT_TEST(HTTOP);
                حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                حالة SDL_HITTEST_RESIZE_دام:
                    POST_HIT_TEST(HTRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                حالة SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                حالة SDL_HITTEST_RESIZE_هغو:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                حالة SDL_HITTEST_NORMAL:
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
        إذا (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
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

                إذا (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.هغو + rect.دام;
                frame_h = -rect.كولي + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.دام = query_client_w_win;
                rect.bottom = query_client_h_win;

                إذا (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.دام - rect.هغو;
                sizeInOut->cy = rect.bottom - rect.كولي;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            أرجع TRUE;
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
                    suggestedRect->هغو, suggestedRect->كولي, suggestedRect->دام - suggestedRect->هغو, suggestedRect->bottom - suggestedRect->كولي);
#endif

            إذا (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                أرجع 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.دام = data->window->w;
                rect.bottom = data->window->h;

                إذا (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.دام - rect.هغو;
                h = rect.bottom - rect.كولي;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->هغو, suggestedRect->كولي, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         عدم,
                         suggestedRect->هغو,
                         suggestedRect->كولي,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            أرجع 0;
        }

    حالة WM_SETTINGCHANGE:
        إذا (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
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
    حالة WM_SIZE:
    {
        RECT rect;
        صحيح w, h;

        إذا (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.دام;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } اكسر;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    افتراضي:
        اكسر;
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (سكو && سكو == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    إذا (data->wndproc) {
        أرجع CallWindowProc(data->wndproc, hwnd, سكو, wParam, lParam);
    } وإلا إذا (returnCode >= 0) {
        أرجع returnCode;
    } وإلا {
        أرجع CallWindowProc(DefWindowProc, hwnd, سكو, wParam, lParam);
    }
}

صحيح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    إذا (g_WindowsEnableMessageLoop) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = سكو_Wait_For_Multiple_Objects(0, عدم, FALSE, timeout, QS_ALLINPUT);
        إذا (ret == WAIT_OBJECT_0) {
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#وإلا
        // MsgWaitForMultipleObjects is desktop-only.
        سكو_2 سكو;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        إذا (timeoutNS > 0) {
            timer_id = SetTimer(عدم, 0, (UINT)SDL_NS_TO_MS(timeoutNS), عدم);
            message_result = GetMessage(&سكو, 0, 0, 0);
            KillTimer(عدم, timer_id);
        } وإلا إذا (timeoutNS == 0) {
            message_result = PeekMessage(&سكو, عدم, 0, 0, PM_REMOVE);
        } وإلا {
            message_result = GetMessage(&سكو, 0, 0, 0);
        }
        إذا (message_result) {
            إذا (سكو.message == WM_TIMER && !سكو.hwnd && سكو.wParam == timer_id) {
                أرجع 0;
            }
            إذا (g_WindowsMessageHook) {
                إذا (!g_WindowsMessageHook(g_WindowsMessageHookData, &سكو)) {
                    أرجع 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&سكو);
            DispatchMessage(&سكو);
            أرجع 1;
        } وإلا {
            أرجع 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وإلا {
        // Fail the wait so the caller falls back to polling
        أرجع -1;
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
    سكو_2 سكو;

    إذا (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        طالما (PeekMessage(&سكو, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(سكو.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&سكو);
            DispatchMessage(&سكو);
        }

        SDL_processing_messages = false;
    }
}

فراغ WIN_PumpEvents(SDL_VideoDevice *_this)
{
    سكو_2 سكو;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(تور)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_كدي() + 1;
#ifdef _MSC_VER
#pragma warning(چرو)
#endif
    صحيح new_messages = 0;

    إذا (_this->internal->gameinput_context) {
        WIN_Update_Game_شغرو(_this);
    }

    إذا (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        طالما (PeekMessage(&سكو, عدم, 0, 0, PM_REMOVE)) {
            إذا (g_WindowsMessageHook) {
                إذا (!g_WindowsMessageHook(g_WindowsMessageHookData, &سكو)) {
                    استمر;
                }
            }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            إذا (سكو.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                إذا (!SDL_TICKS_PASSED(سكو.time, (SDL_last_warp_time + 1))) {
                    استمر;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(سكو.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&سكو);
            DispatchMessage(&سكو);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            إذا (SDL_TICKS_PASSED(سكو.time, end_ticks)) {
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
    إذا (keystate[SDL_SCANCODE_LSHIFT] && !(Get_مبودي_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    إذا (keystate[SDL_SCANCODE_RSHIFT] && !(Get_مبودي_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    إذا (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        إذا (keystate[SDL_SCANCODE_LGUI] && !(Get_مبودي_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        إذا (keystate[SDL_SCANCODE_RGUI] && !(Get_مبودي_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_مبودي(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    إذا (_this) {
        SDL_Window *window = _this->windows;
        طالما (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            إذا (data) {
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
            إذا (refresh_clipcursor) {
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
    إذا (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        إذا (!data->mouse_tracked) {
            POINT cursorPos;

            إذا (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (عائم)cursorPos.x, (عائم)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_هغو : SDL_BUTTON_دام,
                                    (Get_Async_مبودي_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_دام : SDL_BUTTON_هغو,
                                    (Get_Async_مبودي_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_ڟكيا,
                                    (Get_Async_مبودي_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_مبودي_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_مبودي_State(VK_XBUTTON2) & 0x8000) != 0);
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
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    إذا (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
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
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    أرجع FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    WNDCLASSEX wcex;
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت حرف *hint;
#endif

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

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    إذا (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        إذا (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وإلا {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    إذا (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        أرجع SDL_SetError("Couldn't register application class");
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
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
