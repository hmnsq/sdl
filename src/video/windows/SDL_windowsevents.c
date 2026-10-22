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

#ifdef SDL_VIDEO_DRIVER_WINDOWS

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
#ifdef HAVE_TPCSHRD_H
#شامل <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#اگر 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#شامل <stdio.h>
#شامل "wmmsg.h"
#endif

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#شامل <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#شامل "../../core/gdk/SDL_gdk.h"
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
#ifndef WM_درون_داد
#define WM_درون_داد 0x00ff
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

#ifndef IS_بالا_SURROGATE
#define IS_بالا_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
تعریفنوع Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

ایستا bool SDL_processing_messages;
ایستا DWORD message_tick;
ایستا Uint64 timestamp_offset;

ایستا تهی WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

ایستا Uint64 WIN_GetEventTimestamp(تهی)
{
    ثابت Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    اگر (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        بازگشت 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    اگر (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } وگرنه اگر ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } وگرنه اگر (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    بازگشت timestamp;
}

// A message hook called before TranslateMessage()
ایستا SDL_WindowsMessageHook g_WindowsMessageHook = پوچ;
ایستا تهی *g_WindowsMessageHookData = پوچ;

تهی SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, تهی *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

ایستا SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_کلید)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 کلید_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(کلید_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_کلید = (scanCode == 0);

    اگر (scanCode != 0) {
        اگر ((کلید_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } وگرنه اگر (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } وگرنه {
        Uint16 vkCode = LOWORD(wParam);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_کلید(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        اگر (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    بازگشت code;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ایستا bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    بازگشت !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

ایستا تهی WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    اگر (bSwapButtons) {
        اگر (button == SDL_BUTTON_چپ) {
            button = SDL_BUTTON_راست;
        } وگرنه اگر (button == SDL_BUTTON_راست) {
            button = SDL_BUTTON_چپ;
        }
    }

    اگر (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        اگر (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        بازگشت;
    }

    اگر (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } وگرنه اگر (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
ایستا تهی WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    اگر (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(پوچ, پوچ);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_چپ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_میانه, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_راست, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

ایستا تهی WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT کلید_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(پوچ, پوچ);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    کلید_State = Get_Async_کلید_State(VK_LBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_چپ, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_RBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_راست, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_MBUTTON);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_میانه, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON1);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    کلید_State = Get_Async_کلید_State(VK_XBUTTON2);
    اگر (!(کلید_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

ایستا تهی WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    اگر (had_focus == has_focus || has_focus != expect_focus) {
        بازگشت;
    }

    اگر (has_focus) {
        POINT cursorPos;

        اگر (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            اگر (Get_Async_کلید_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            اگر (Get_Async_کلید_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            اگر (Get_Async_کلید_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            اگر (Get_Async_کلید_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            اگر (Get_Async_کلید_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        اگر (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_کلید_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_رقم, (Get_کلید_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_کلید_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } وگرنه {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(پوچ);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        اگر (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(پوچ);
        }
        WIN_Reset_Dead_کلیدها();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ایستا bool ShouldGenerateWindowCloseOnAltF4(تهی)
{
    بازگشت SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

ایستا bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    انتخاب (data->hint_erase_background_mode) {
    حالت SDL_ERASEBACKGROUNDMODE_NEVER:
        بازگشت false;
    حالت SDL_ERASEBACKGROUNDMODE_INITIAL:
        بازگشت !data->videodata->cleared;
    حالت SDL_ERASEBACKGROUNDMODE_ALWAYS:
        بازگشت true;
    پیشفرض:
        // Unexpected value, fallback to default behaviour
        بازگشت !data->videodata->cleared;
    }
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

تعریفنوع شمارش
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

ایستا SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    اگر (IsTouchEvent(extrainfo)) {
        اگر (extrainfo & 0x80) {
            بازگشت SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } وگرنه {
            بازگشت SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    بازگشت SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ایستا SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    اگر (_this) {
        برای (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            اگر (data && data->hwnd == hwnd) {
                بازگشت data;
            }
        }
    }
    بازگشت پوچ;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(صحیح nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    اگر (nCode < 0 || nCode != HC_ACTION) {
        بازگشت CallNextHookEx(پوچ, nCode, wParam, lParam);
    }
    اگر (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        بازگشت 1;
    }

    انتخاب (hookData->vkCode) {
    حالت VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        بشکن;
    حالت VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        بشکن;
    حالت VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        بشکن;
    حالت VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        بشکن;
    حالت VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        بشکن;
    حالت VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        بشکن;
    حالت VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        بشکن;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    حالت VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        بشکن;
    حالت VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        بشکن;

    پیشفرض:
        بازگشت CallNextHookEx(پوچ, nCode, wParam, lParam);
    }

    اگر (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        اگر (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } وگرنه {
        اگر (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        اگر (hookData->vkCode <= 0xFF && data->pre_hook_کلید_state[hookData->vkCode]) {
            data->pre_hook_کلید_state[hookData->vkCode] = 0;
            بازگشت CallNextHookEx(پوچ, nCode, wParam, lParam);
        }
    }

    بازگشت 1;
}

ایستا bool WIN_SwapButtons(HANDLE hDevice)
{
    اگر (hDevice == پوچ) {
        // Touchpad, already has buttons swapped
        بازگشت false;
    }
    بازگشت GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

ایستا تهی WIN_Handle_Raw_Mouse_درون_داد(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    ایستا ساختار {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_چپ_BUTTON_DOWN, SDL_BUTTON_چپ, true },
        { RI_MOUSE_چپ_BUTTON_UP, SDL_BUTTON_چپ, false },
        { RI_MOUSE_راست_BUTTON_DOWN, SDL_BUTTON_راست, true },
        { RI_MOUSE_راست_BUTTON_UP, SDL_BUTTON_راست, false },
        { RI_MOUSE_میانه_BUTTON_DOWN, SDL_BUTTON_میانه, true },
        { RI_MOUSE_میانه_BUTTON_UP, SDL_BUTTON_میانه, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    صحیح dx = (صحیح)rawmouse->lLastX;
    صحیح dy = (صحیح)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    اگر (!data->raw_mouse_enabled) {
        بازگشت;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    اگر (!window) {
        بازگشت;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    اگر (!mouse) {
        بازگشت;
    }

    اگر (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        بازگشت;
    }

    SDL_WindowData *windowdata = window->internal;

    اگر (haveMotion && !windowdata->in_modal_loop) {
        اگر (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (اعشاری)dx, (اعشاری)dy);
        } وگرنه {
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
            اگر (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            اگر (remote_desktop) {
                اگر (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    ایستا صحیح wobble;
                    اعشاری floatX = (اعشاری)x / w;
                    اعشاری floatY = (اعشاری)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    اگر (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        صحیح warpX = rect.چپ + ((rect.راست - rect.چپ) / 2) + wobble;
                        صحیح warpY = rect.بالاترین + ((rect.bottom - rect.بالاترین) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        اگر (wobble > 1) {
                            wobble = -1;
                        }
                    } وگرنه {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ثابت صحیح MAX_RELATIVE_MOTION = (h / 6);
                        اگر (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (اعشاری)relX, (اعشاری)relY);
                        }
                    }
                }
            } وگرنه اگر (mouse->pen_mouse_events) {
                ثابت صحیح MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                اگر (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } وگرنه {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (اعشاری)relX, (اعشاری)relY);
                }
            } وگرنه {
                صحیح screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                صحیح screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                اگر (!data->raw_درون_داد_fake_pen_id) {
                    data->raw_درون_داد_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, پوچ, (تهی *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_درون_داد_fake_pen_id, window, (اعشاری)(x + screen_x - window->x), (اعشاری)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    اگر (haveButton) {
        برای (صحیح i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            اگر (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                اگر (button == SDL_BUTTON_چپ) {
                    اگر (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_راست;
                    }
                } وگرنه اگر (button == SDL_BUTTON_راست) {
                    اگر (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_چپ;
                    }
                }

                اگر (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    اگر (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    ادامه;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        اگر (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } وگرنه اگر (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

ایستا تهی WIN_Handle_Raw_Keyboard_درون_داد(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    اگر (!data->raw_keyboard_enabled) {
        بازگشت;
    }

    اگر (rawkeyboard->Flags & RI_کلید_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_کلید_sequence = true;
        بازگشت;
    }

    اگر ((rawkeyboard->Flags & RI_کلید_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        بازگشت;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_کلید(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    اگر (!rawkeyboard->MakeCode) {
        بازگشت;
    }

    bool down;
    انتخاب (rawkeyboard->Message) {
    حالت WM_KEYDOWN:
    حالت WM_SYSKEYDOWN:
        down = true;
        بشکن;
    حالت WM_KEYUP:
    حالت WM_SYSKEYUP:
        down = false;
        بشکن;
    پیشفرض:
        down = !(rawkeyboard->Flags & RI_کلید_BREAK);
        بشکن;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    اگر (data->pending_E1_کلید_sequence) {
        rawcode |= 0xE100;
        اگر (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } وگرنه {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_کلید_sequence = false;
    } وگرنه {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        اگر (rawkeyboard->Flags & RI_کلید_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    اگر (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        اگر ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_درون_داد_active)) {
            بازگشت;
        }
    }

    SDL_Send_Keyboard_کلید(timestamp, keyboardID, rawcode, code, down);
}

تهی WIN_Poll_Raw_درون_داد(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, شمار, total = 0;
    RAWINPUT *درون_داد;
    Uint64 poll_finish;

    اگر (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = اندازه(RAWINPUTHEADER);
        اگر (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    درون_داد = (RAWINPUT *)data->rawinput;
    برای (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)درون_داد - data->rawinput);
        شمار = Get_Raw_درون_داد_Buffer(درون_داد, &size, اندازه(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        اگر (شمار == 0 || شمار == (UINT)-1) {
            اگر (!data->rawinput || (شمار == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                ثابت UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                اگر (!rawinput) {
                    بشکن;
                }
                درون_داد = (RAWINPUT *)(rawinput + ((BYTE *)درون_داد - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } وگرنه {
                بشکن;
            }
        } وگرنه {
            total += شمار;

            // Advance input to the end of the buffer
            وقتی (شمار--) {
                درون_داد = NEXTRAWINPUTBLOCK(درون_داد);
            }
        }
    }

    اگر (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        برای (i = 0, درون_داد = (RAWINPUT *)data->rawinput; i < total; ++i, درون_داد = NEXTRAWINPUTBLOCK(درون_داد)) {
            اگر (درون_داد->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        صحیح mouse_index = 0;
        برای (i = 0, درون_داد = (RAWINPUT *)data->rawinput; i < total; ++i, درون_داد = NEXTRAWINPUTBLOCK(درون_داد)) {
            اگر (درون_داد->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)درون_داد + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_درون_داد(time, data, درون_داد->header.hDevice, rawmouse);
            } وگرنه اگر (درون_داد->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)درون_داد + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_درون_داد(poll_finish, data, درون_داد->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

ایستا تهی AddDeviceID(Uint32 deviceID, Uint32 **list, صحیح *شمار)
{
    صحیح new_شمار = (*شمار + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمار * اندازه(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        بازگشت;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}

ایستا bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحیح شمار)
{
    برای (صحیح i = 0; i < شمار; ++i) {
        اگر (deviceID == list[i]) {
            بازگشت true;
        }
    }
    بازگشت false;
}

ایستا نویسه *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ثابت نویسه *instance, Uint16 vendor, Uint16 product, ثابت نویسه *default_name, bool hid_loaded)
{
    نویسه *vendor_name = پوچ;
    نویسه *product_name = پوچ;
    نویسه *name = پوچ;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    اگر (hid_loaded) {
        نویسه devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = اندازه(devName) - 1;
        UINT len = Get_Raw_درون_داد_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        اگر (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, پوچ, OPEN_EXISTING, 0, پوچ);
            اگر (hFile != INVALID_HANDLE_مقدار) {
                SDL_HidD_GetManufacturerString(hFile, vend, اندازه(vend));
                SDL_HidD_GetProductString(hFile, prod, اندازه(prod));
                CloseHandle(hFile);
            }
        }
    }

    اگر (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    اگر (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } وگرنه {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = اندازه(data);
        برای (DWORD i = 0;; ++i) {
            اگر (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                اگر (GetLastError() == ERROR_NO_MORE_اقلام) {
                    بشکن;
                } وگرنه {
                    ادامه;
                }
            }

            نویسه DeviceInstanceId[64];
            اگر (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, اندازه(DeviceInstanceId), پوچ))
                ادامه;

            اگر (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                اگر (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, پوچ, (PBYTE)prod, اندازه(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= اندازه(*prod);
                    اگر (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    اگر (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } وگرنه {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                بشکن;
            }
        }
    }

    اگر (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    بازگشت name;
}

تهی WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = پوچ;
    UINT raw_device_شمار = 0;
    صحیح old_keyboard_شمار = 0;
    SDL_KeyboardID *old_keyboards = پوچ;
    صحیح new_keyboard_شمار = 0;
    SDL_KeyboardID *new_keyboards = پوچ;
    صحیح old_mouse_شمار = 0;
    SDL_MouseID *old_mice = پوچ;
    صحیح new_mouse_شمار = 0;
    SDL_MouseID *new_mice = پوچ;

    اگر (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        بازگشت;
    }

    اگر ((Get_Raw_درون_داد_Device_List(پوچ, &raw_device_شمار, اندازه(RAWINPUTDEVICELIST)) == -1) || (!raw_device_شمار)) {
        بازگشت; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(اندازه(RAWINPUTDEVICELIST) * raw_device_شمار);
    اگر (!raw_devices) {
        بازگشت; // oh well.
    }

    raw_device_شمار = Get_Raw_درون_داد_Device_List(raw_devices, &raw_device_شمار, اندازه(RAWINPUTDEVICELIST));
    اگر (raw_device_شمار == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = پوچ;
        بازگشت; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(پوچ, پوچ, پوچ, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمار);
    old_mice = SDL_GetMice(&old_mouse_شمار);

    برای (UINT i = 0; i < raw_device_شمار; i++) {
        RID_DEVICE_INFO rdi;
        نویسه devName[MAX_PATH] = { 0 };
        UINT rdiSize = اندازه(rdi);
        UINT nameSize = SDL_arraysize(devName);
        صحیح vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        نویسه *instance, *ptr, *name;

        اگر (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            ادامه;
        }

        rdi.cbSize = اندازه(rdi);
        اگر (Get_Raw_درون_داد_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_درون_داد_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            ادامه;
        }

        // Extract the device instance
        instance = devName;
        وقتی (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        برای (ptr = instance; *ptr; ++ptr) {
            اگر (*ptr == '#') {
                *ptr = '\\';
            }
            اگر (*ptr == '{') {
                اگر (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                بشکن;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        انتخاب (dwType) {
        حالت RIM_TYPEKEYBOARD:
            اگر (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_عدد_Of_کلیدها_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_شمار);
                اگر (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمار)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            بشکن;
        حالت RIM_TYPEMOUSE:
            اگر (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_شمار);
                اگر (!HasDeviceID(mouseID, old_mice, old_mouse_شمار)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            بشکن;
        پیشفرض:
            بشکن;
        }
    }

    برای (صحیح i = old_keyboard_شمار; i--;) {
        اگر (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمار)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    برای (صحیح i = old_mouse_شمار; i--;) {
        اگر (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمار)) {
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
ایستا bool Skip_Alt_Gr_چپ_Control(WPARAM wParam, LPARAM lParam)
{
    اگر (wParam != VK_CONTROL) {
        بازگشت false;
    }

    // Is this an extended key (i.e. right key)?
    اگر (lParam & 0x01000000) {
        بازگشت false;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    پیام_2 next_پیام;
    DWORD پیام_time = GetMessageTime();
    اگر (PeekMessage(&next_پیام, پوچ, 0, 0, PM_NOREMOVE)) {
        اگر (next_پیام.message == WM_KEYDOWN ||
            next_پیام.message == WM_SYSKEYDOWN) {
            اگر (next_پیام.wParam == VK_MENU && (next_پیام.lParam & 0x01000000) && next_پیام.time == پیام_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                بازگشت true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    بازگشت false;
}

ایستا bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *پیام, WPARAM *wParam, LPARAM *lParam)
{
    پیام_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *پیام;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    اگر (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *پیام = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        بازگشت true;
    }
    بازگشت false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT پیام, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    اگر (!data) {
        بازگشت CallWindowProc(DefWindowProc, hwnd, پیام, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        نویسه message[1024];
        اگر (پیام > MAX_WMMSG) {
            SDL_snprintf(message, اندازه(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, پیام, wParam, lParam);
        } وگرنه {
            SDL_snprintf(message, اندازه(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[پیام], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    اگر (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        اگر (!DispatchModalLoopMessageHook(&hwnd, &پیام, &wParam, &lParam)) {
            بازگشت 0;
        }
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (WIN_HandleIMEMessage(hwnd, پیام, wParam, &lParam, data->videodata)) {
        بازگشت 0;
    }
#endif

    انتخاب (پیام) {

    حالت WM_SHOWWINDOW:
    {
        اگر (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } وگرنه {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } بشکن;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    حالت WM_NCACTIVATE:
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
        اگر (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } بشکن;

    حالت WM_NCUAHDRAWCAPTION:
    حالت WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        اگر (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } بشکن;

    حالت WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ثابت DWORD پیام_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } بشکن;

    حالت WM_MOUSEACTIVATE:
    {
        اگر (SDL_WINDOW_IS_POPUP(data->window)) {
            بازگشت MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        وقتی (parent) {
            اگر ((parent->flags & SDL_WINDOW_درون_داد_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                بازگشت MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } بشکن;

    حالت WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیام_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } بشکن;

    حالت WM_KILLFOCUS:
    حالت WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ثابت DWORD پیام_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(پیام_Pos), GET_Y_LPARAM(پیام_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } بشکن;

    حالت WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_درون_داد_TYPE pointer_type = PT_POINTER;
        اگر (!data->videodata->GetPointerType) {
            بشکن;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وگرنه اگر (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            بشکن;  // oh well.
        } وگرنه اگر (pointer_type != PT_PEN) {
            بشکن;  // we only care about pens here.
        }

        تهی *hpointer = (تهی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        اگر (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } وگرنه {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.رقم_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), پوچ, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } بشکن;

    حالت WM_POINTERCAPTURECHANGED:
    حالت WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_درون_داد_TYPE pointer_type = PT_POINTER;
        اگر (!data->videodata->GetPointerType) {
            بشکن;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } وگرنه اگر (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            بشکن;  // oh well.
        } وگرنه اگر (pointer_type != PT_PEN) {
            بشکن;  // we only care about pens here.
        }

        تهی *hpointer = (تهی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        اگر (pen == 0) {
            بشکن;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        اگر ((پیام == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } بشکن;

    حالت WM_POINTERDOWN:
    حالت WM_POINTERUP:
    حالت WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ثابت UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_درون_داد_TYPE pointer_type = PT_POINTER;
        اگر (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            بشکن;  // oh well.
        } وگرنه اگر ((پیام == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            بشکن;
        } وگرنه اگر (pointer_type != PT_PEN) {
            بشکن; // we only care about pens here.
        }

        تهی *hpointer = (تهی *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ثابت SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        اگر (pen == 0) {
            بشکن;  // not a pen, or not a pen we already knew about.
        } وگرنه اگر (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            بشکن;  // oh well.
        }

        ثابت Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        ثابت bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        اگر (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ثابت POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        اعشاری fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        اگر (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (اعشاری) position.x;
            fy = (اعشاری) position.y;
        } وگرنه {
            صحیح ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            ثابت SDL_FPoint window_pos = { (اعشاری) ix, (اعشاری) iy };

            ثابت اعشاری facX = pointer_info->ptHimetricLocationRaw.x / (اعشاری) (tablet_bounds.راست );
            ثابت اعشاری facY = pointer_info->ptHimetricLocationRaw.y / (اعشاری) (tablet_bounds.bottom);

            ثابت اعشاری w = tablet_mapping.راست  - tablet_mapping.چپ;
            ثابت اعشاری h = tablet_mapping.bottom - tablet_mapping.بالاترین;

            fx = (tablet_mapping.چپ + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.بالاترین  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        اگر (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((اعشاری) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        اگر (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((اعشاری) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        اگر (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((اعشاری) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        اگر (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((اعشاری) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        اگر (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } بشکن;

    حالت WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        اگر (window->flags & SDL_WINDOW_درون_داد_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            اگر (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        اگر (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = اندازه(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            اگر (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        اگر (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            اگر (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)GET_X_LPARAM(lParam), (اعشاری)GET_Y_LPARAM(lParam));
            }
        }

    } بشکن;

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
        اگر (!data->videodata->raw_mouse_enabled) {
            اگر (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } بشکن;

#اگر 0   // We handle raw input all at once instead of using a syscall for each mouse event
    حالت WM_درون_داد:
    {
        HRAWINPUT h_Raw_درون_داد = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = اندازه(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        اگر (data->window != SDL_GetKeyboardFocus()) {
            بشکن;
        }

        Get_Raw_درون_داد_Data(h_Raw_درون_داد, RID_درون_داد, &inp, &size, اندازه(RAWINPUTHEADER));
        اگر (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_درون_داد(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } وگرنه اگر (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_درون_داد(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } بشکن;
#endif

    حالت WM_MOUSEWHEEL:
    حالت WM_MOUSEHWHEEL:
    {
        اگر (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            اعشاری fAmount = (اعشاری)amount / WHEEL_DELTA;
            اگر (پیام == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } وگرنه {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } بشکن;

    حالت WM_MOUSELEAVE:
        اگر (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            اگر (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                اگر (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                } وگرنه {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    اگر (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                    } وگرنه { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                    }
                }
            }

            اگر (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(پوچ);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        بشکن;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    حالت WM_KEYDOWN:
    حالت WM_SYSKEYDOWN:
    {
        اگر (Skip_Alt_Gr_چپ_Control(wParam, lParam)) {
            returnCode = 0;
            بشکن;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_کلید);

        // Detect relevant keyboard shortcuts
        اگر (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            اگر (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        اگر (virtual_کلید || !data->videodata->raw_keyboard_enabled || data->window->text_درون_داد_active) {
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        بشکن;

    حالت WM_SYSKEYUP:
    حالت WM_KEYUP:
    {
        اگر (Skip_Alt_Gr_چپ_Control(wParam, lParam)) {
            returnCode = 0;
            بشکن;
        }

        bool virtual_کلید = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_کلید);
        ثابت bool *keyboardState = SDL_GetKeyboardState(پوچ);

        اگر (virtual_کلید || !data->videodata->raw_keyboard_enabled || data->window->text_درون_داد_active) {
            اگر (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_کلید(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        بشکن;

    حالت WM_UNICHAR:
        اگر (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } وگرنه {
            اگر (SDL_Text_درون_داد_Active(data->window)) {
                نویسه text[5];
                نویسه *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        بشکن;

    حالت WM_CHAR:
        اگر (SDL_Text_درون_داد_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            اگر (IS_بالا_SURROGATE(wParam)) {
                data->بالا_surrogate = (WCHAR)wParam;
            } وگرنه {
                WCHAR utf16[3];

                utf16[0] = data->بالا_surrogate ? data->بالا_surrogate : (WCHAR)wParam;
                utf16[1] = data->بالا_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                نویسه utf8[5];
                صحیح result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, اندازه(utf8), پوچ, پوچ);
                اگر (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->بالا_surrogate = L'\0';
            }
        } وگرنه {
            data->بالا_surrogate = L'\0';
        }

        returnCode = 0;
        بشکن;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    حالت WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        بشکن;
#endif // WM_INPUTLANGCHANGE

    حالت WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        اگر (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } بشکن;

    حالت WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } بشکن;

#ifdef WM_GETMINMAXINFO
    حالت WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        صحیح x, y;
        صحیح w, h;
        صحیح min_w, min_h;
        صحیح max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        اگر (data->expected_resize) {
            بشکن;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.چپ;
        y = size.بالاترین;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        اگر (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } وگرنه {
            constrain_max_size = FALSE;
        }

        اگر (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.بالاترین = 0;
            size.چپ = 0;
            size.bottom = h;
            size.راست = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.راست - size.چپ;
            h = size.bottom - size.بالاترین;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        اگر (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            اگر (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                صحیح screenW = GetSystemMetrics(SM_CXSCREEN);
                صحیح screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            اگر (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } وگرنه {
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
        بشکن;
#endif // WM_GETMINMAXINFO

    حالت WM_WINDOWPOSCHANGING:

        اگر (data->expected_resize) {
            returnCode = 0;
        } وگرنه اگر (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            اگر (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        بشکن;

    حالت WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        ثابت SDL_DisplayID original_displayID = data->window->displayID;
        ثابت WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        صحیح x, y;
        صحیح w, h;

        اگر (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        اگر (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } وگرنه اگر (zoomed) {
            اگر (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } وگرنه اگر (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            اگر (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        اگر (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        اگر (iconic) {
            بشکن;
        }

        اگر (data->initializing) {
            بشکن;
        }

        اگر (!data->disable_move_size_events) {
            اگر (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.چپ;
                y = rect.بالاترین;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            اگر (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.راست;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        اگر (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        برای (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            اگر (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } بشکن;

    حالت WM_ENTERSIZEMOVE:
    حالت WM_ENTERMENULOOP:
    {
        اگر (g_WindowsMessageHook) {
            اگر (!DispatchModalLoopMessageHook(&hwnd, &پیام, &wParam, &lParam)) {
                بازگشت 0;
            }
        }

        ++data->in_modal_loop;
        اگر (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.راست - rect.چپ;
            data->last_modal_height = rect.bottom - rect.بالاترین;

            data->initial_size_rect.چپ = data->window->x;
            data->initial_size_rect.راست = data->window->x + data->window->w;
            data->initial_size_rect.بالاترین = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, پوچ);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } بشکن;

    حالت WM_TIMER:
    {
        اگر (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#اگر 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            اگر (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            بازگشت 0;
        }
    } بشکن;

    حالت WM_EXITSIZEMOVE:
    حالت WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        اگر (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } بشکن;

    حالت WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            اعشاری new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            اگر (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                بشکن;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            اگر (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != پوچ, GetWindowExStyle(hwnd))) {
                بشکن;
            }

            clientDragRect.چپ -= rc.چپ;
            clientDragRect.بالاترین -= rc.بالاترین;
            clientDragRect.راست -= rc.راست;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.راست - clientDragRect.چپ;
            h = clientDragRect.bottom - clientDragRect.بالاترین;
            new_aspect = w / (اعشاری)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            اگر (lock_aspect_ratio) {
                انتخاب (edge) {
                حالت WMSZ_چپ:
                حالت WMSZ_راست:
                    h = (صحیح)SDL_roundf(w / data->window->max_aspect);
                    بشکن;
                پیشفرض:
                    // resizing via corners or top or bottom
                    w = (صحیح)SDL_roundf(h * data->window->max_aspect);
                    بشکن;
                }
            } وگرنه {
                انتخاب (edge) {
                حالت WMSZ_چپ:
                حالت WMSZ_راست:
                    اگر (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحیح)SDL_roundf(h * data->window->max_aspect);
                    } وگرنه اگر (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (صحیح)SDL_roundf(h * data->window->min_aspect);
                    }
                    بشکن;
                حالت WMSZ_بالاترین:
                حالت WMSZ_BOTTOM:
                    اگر (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحیح)SDL_roundf(w / data->window->min_aspect);
                    } وگرنه اگر (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (صحیح)SDL_roundf(w / data->window->max_aspect);
                    }
                    بشکن;

                پیشفرض:
                    // resizing via corners
                    اگر (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (صحیح)SDL_roundf(h * data->window->max_aspect);
                    } وگرنه اگر (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (صحیح)SDL_roundf(w / data->window->min_aspect);
                    }
                    بشکن;
                }
            }

            انتخاب (edge) {
            حالت WMSZ_چپ:
                clientDragRect.چپ = clientDragRect.راست - w;
                اگر (lock_aspect_ratio) {
                    clientDragRect.بالاترین = (data->initial_size_rect.bottom + data->initial_size_rect.بالاترین - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                بشکن;
            حالت WMSZ_BOTTOMLEFT:
                clientDragRect.چپ = clientDragRect.راست - w;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                بشکن;
            حالت WMSZ_راست:
                clientDragRect.راست = w + clientDragRect.چپ;
                اگر (lock_aspect_ratio) {
                    clientDragRect.بالاترین = (data->initial_size_rect.bottom + data->initial_size_rect.بالاترین - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                بشکن;
            حالت WMSZ_TOPRIGHT:
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                بشکن;
            حالت WMSZ_بالاترین:
                اگر (lock_aspect_ratio) {
                    clientDragRect.چپ = (data->initial_size_rect.راست + data->initial_size_rect.چپ - w) / 2;
                }
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                بشکن;
            حالت WMSZ_TOPLEFT:
                clientDragRect.چپ = clientDragRect.راست - w;
                clientDragRect.بالاترین = clientDragRect.bottom - h;
                بشکن;
            حالت WMSZ_BOTTOM:
                اگر (lock_aspect_ratio) {
                    clientDragRect.چپ = (data->initial_size_rect.راست + data->initial_size_rect.چپ - w) / 2;
                }
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                بشکن;
            حالت WMSZ_BOTTOMRIGHT:
                clientDragRect.راست = w + clientDragRect.چپ;
                clientDragRect.bottom = h + clientDragRect.بالاترین;
                بشکن;
            }

            // convert the client rect to a window rect
            اگر (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != پوچ, GetWindowExStyle(hwnd))) {
                بشکن;
            }

            *dragRect = clientDragRect;
        }
        بشکن;

    حالت WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        اگر (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } وگرنه اگر (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(پوچ);
            returnCode = TRUE;
        }
    } بشکن;

        // We were occluded, refresh our display
    حالت WM_PAINT:
    {
        RECT rect;
        اگر (GetUpdateRect(hwnd, &rect, FALSE)) {
            ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            اگر (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, پوچ);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        بشکن;

        // We'll do our own drawing, prevent flicker
    حالت WM_ERASEBKGND:
        اگر (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        بازگشت 1;

    حالت WM_SYSCOMMAND:
    {
        اگر (!g_WindowsEnableMenuMnemonics) {
            اگر ((wParam & 0xFFF0) == SC_KEYMENU) {
                بازگشت 0;
            }
        }

#اگر defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        اگر ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            اگر (SDL_GetVideoDevice()->suspend_screensaver) {
                بازگشت 0;
            }
        }
#endif // System has screensaver support
    } بشکن;

    حالت WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        بشکن;

    حالت WM_TOUCH:
        اگر (data->videodata->Get_Touch_درون_داد_Info && data->videodata->Close_Touch_درون_داد_Handle) {
            UINT i, رقم_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, رقم_inputs, &isstack);
            اگر (inputs && data->videodata->Get_Touch_درون_داد_Info((HTOUCHINPUT)lParam, رقم_inputs, inputs, اندازه(TOUCHINPUT))) {
                RECT rect;
                اعشاری x, y;

                اگر (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    اگر (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    بشکن;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.بالاترین *= 100;
                rect.چپ *= 100;
                rect.bottom *= 100;
                rect.راست *= 100;

                برای (i = 0; i < رقم_inputs; ++i) {
                    PTOUCHINPUT درون_داد = &inputs[i];
                    ثابت صحیح w = (rect.راست - rect.چپ);
                    ثابت صحیح h = (rect.bottom - rect.بالاترین);

                    ثابت SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)درون_داد->hSource);
                    ثابت SDL_FingerID fingerId = (درون_داد->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    اگر (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (درون_داد->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        ادامه;
                    }

                    // Get the normalized coordinates for the window
                    اگر (w <= 1) {
                        x = 0.5f;
                    } وگرنه {
                        x = (اعشاری)(درون_داد->x - rect.چپ) / (w - 1);
                    }
                    اگر (h <= 1) {
                        y = 0.5f;
                    } وگرنه {
                        y = (اعشاری)(درون_داد->y - rect.بالاترین) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    اگر (درون_داد->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    اگر (درون_داد->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    اگر (درون_داد->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_درون_داد_Handle((HTOUCHINPUT)lParam);
            بازگشت 0;
        }
        بشکن;

#ifdef HAVE_TPCSHRD_H

    حالت WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        بازگشت TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    حالت WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT شمار = DragQueryFile(drop, 0xFFFFFFFF, پوچ, 0);
        برای (i = 0; i < شمار; ++i) {
            UINT size = DragQueryFile(drop, i, پوچ, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(اندازه(TCHAR) * size);
            اگر (buffer) {
                اگر (DragQueryFile(drop, i, buffer, size)) {
                    نویسه *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, پوچ, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        بازگشت 0;
    }

    حالت WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } بشکن;

    حالت WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        اگر (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            اگر (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                اگر (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ثابت POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                اگر (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = اندازه(info);
                    اگر (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } وگرنه اگر (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                صحیح w, h;
                اگر (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } وگرنه {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].راست = params->rgrc[0].چپ + w;
                params->rgrc[0].bottom = params->rgrc[0].بالاترین + h;
            }
            بازگشت 0;
        }
    } بشکن;

    حالت WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        اگر (window->flags & SDL_WINDOW_TOOLTIP) {
            بازگشت HTTRANSPARENT;
        }

        اگر (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            اگر (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                انتخاب (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        بازگشت ret;                                                        \
    }
                حالت SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(پوچ, پوچ);
                    اگر (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        بازگشت HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                حالت SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                حالت SDL_HITTEST_RESIZE_بالاترین:
                    POST_HIT_TEST(HTTOP);
                حالت SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                حالت SDL_HITTEST_RESIZE_راست:
                    POST_HIT_TEST(HTRIGHT);
                حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                حالت SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                حالت SDL_HITTEST_RESIZE_چپ:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                حالت SDL_HITTEST_NORMAL:
                    بازگشت HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } بشکن;

    حالت WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        اگر (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ثابت صحیح nextDPI = (صحیح)wParam;
            ثابت صحیح prevDPI = (صحیح)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            صحیح frame_w, frame_h;
            صحیح query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                اگر (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.چپ + rect.راست;
                frame_h = -rect.بالاترین + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.راست = query_client_w_win;
                rect.bottom = query_client_h_win;

                اگر (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.راست - rect.چپ;
                sizeInOut->cy = rect.bottom - rect.بالاترین;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            بازگشت TRUE;
        }
        بشکن;

    حالت WM_DPICHANGED:
        // Windows 8.1+
        {
            ثابت صحیح newDPI = HIWORD(wParam);
            RECT *ثابت suggestedRect = (RECT *)lParam;
            صحیح w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->چپ, suggestedRect->بالاترین, suggestedRect->راست - suggestedRect->چپ, suggestedRect->bottom - suggestedRect->بالاترین);
#endif

            اگر (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                بازگشت 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.راست = data->window->w;
                rect.bottom = data->window->h;

                اگر (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.راست - rect.چپ;
                h = rect.bottom - rect.بالاترین;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->چپ, suggestedRect->بالاترین, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         پوچ,
                         suggestedRect->چپ,
                         suggestedRect->بالاترین,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            بازگشت 0;
        }

    حالت WM_SETTINGCHANGE:
        اگر (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        اگر (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        اگر (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        بشکن;
#وگرنه
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    حالت WM_SIZE:
    {
        RECT rect;
        صحیح w, h;

        اگر (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.راست;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } بشکن;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    پیشفرض:
        بشکن;
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (پیام && پیام == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    اگر (data->wndproc) {
        بازگشت CallWindowProc(data->wndproc, hwnd, پیام, wParam, lParam);
    } وگرنه اگر (returnCode >= 0) {
        بازگشت returnCode;
    } وگرنه {
        بازگشت CallWindowProc(DefWindowProc, hwnd, پیام, wParam, lParam);
    }
}

صحیح WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    اگر (g_WindowsEnableMessageLoop) {
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = پیام_Wait_For_Multiple_Objects(0, پوچ, FALSE, timeout, QS_ALLINPUT);
        اگر (ret == WAIT_OBJECT_0) {
            بازگشت 1;
        } وگرنه {
            بازگشت 0;
        }
#وگرنه
        // MsgWaitForMultipleObjects is desktop-only.
        پیام_2 پیام;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        اگر (timeoutNS > 0) {
            timer_id = SetTimer(پوچ, 0, (UINT)SDL_NS_TO_MS(timeoutNS), پوچ);
            message_result = GetMessage(&پیام, 0, 0, 0);
            KillTimer(پوچ, timer_id);
        } وگرنه اگر (timeoutNS == 0) {
            message_result = PeekMessage(&پیام, پوچ, 0, 0, PM_REMOVE);
        } وگرنه {
            message_result = GetMessage(&پیام, 0, 0, 0);
        }
        اگر (message_result) {
            اگر (پیام.message == WM_TIMER && !پیام.hwnd && پیام.wParam == timer_id) {
                بازگشت 0;
            }
            اگر (g_WindowsMessageHook) {
                اگر (!g_WindowsMessageHook(g_WindowsMessageHookData, &پیام)) {
                    بازگشت 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&پیام);
            DispatchMessage(&پیام);
            بازگشت 1;
        } وگرنه {
            بازگشت 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } وگرنه {
        // Fail the wait so the caller falls back to polling
        بازگشت -1;
    }
}

تهی WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
تهی WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    پیام_2 پیام;

    اگر (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        وقتی (PeekMessage(&پیام, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(پیام.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&پیام);
            DispatchMessage(&پیام);
        }

        SDL_processing_messages = false;
    }
}

تهی WIN_PumpEvents(SDL_VideoDevice *_this)
{
    پیام_2 پیام;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(افزودن)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_شمار() + 1;
#ifdef _MSC_VER
#pragma warning(برداشت)
#endif
    صحیح new_messages = 0;

    اگر (_this->internal->gameinput_context) {
        WIN_Update_Game_درون_داد(_this);
    }

    اگر (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        وقتی (PeekMessage(&پیام, پوچ, 0, 0, PM_REMOVE)) {
            اگر (g_WindowsMessageHook) {
                اگر (!g_WindowsMessageHook(g_WindowsMessageHookData, &پیام)) {
                    ادامه;
                }
            }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            اگر (پیام.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                اگر (!SDL_TICKS_PASSED(پیام.time, (SDL_last_warp_time + 1))) {
                    ادامه;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(پیام.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&پیام);
            DispatchMessage(&پیام);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            اگر (SDL_TICKS_PASSED(پیام.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ثابت صحیح MAX_NEW_MESSAGES = 3;
                ++new_messages;
                اگر (new_messages > MAX_NEW_MESSAGES) {
                    بشکن;
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
    ثابت bool *keystate = SDL_GetKeyboardState(پوچ);
    اگر (keystate[SDL_SCANCODE_LSHIFT] && !(Get_کلید_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    اگر (keystate[SDL_SCANCODE_RSHIFT] && !(Get_کلید_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    اگر (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        اگر (keystate[SDL_SCANCODE_LGUI] && !(Get_کلید_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        اگر (keystate[SDL_SCANCODE_RGUI] && !(Get_کلید_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    اگر (_this) {
        SDL_Window *window = _this->windows;
        وقتی (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            اگر (data) {
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
            اگر (refresh_clipcursor) {
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
    اگر (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        اگر (!data->mouse_tracked) {
            POINT cursorPos;

            اگر (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (اعشاری)cursorPos.x, (اعشاری)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_چپ : SDL_BUTTON_راست,
                                    (Get_Async_کلید_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_راست : SDL_BUTTON_چپ,
                                    (Get_Async_کلید_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_میانه,
                                    (Get_Async_کلید_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_کلید_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_کلید_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

ایستا صحیح app_registered = 0;
LPTSTR SDL_Appname = پوچ;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = پوچ;

ایستا تهی WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    اگر (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = پوچ;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ایستا BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (تهی)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    بازگشت FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(ثابت نویسه *name, Uint32 style, تهی *hInst)
{
    WNDCLASSEX wcex;
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت نویسه *hint;
#endif

    // Only do this once...
    اگر (app_registered) {
        ++app_registered;
        بازگشت true;
    }
    SDL_assert(!SDL_Appname);
    اگر (!name) {
        name = "SDL_app";
#اگر defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(پوچ);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = اندازه(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    اگر (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        اگر (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } وگرنه {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    اگر (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        بازگشت SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    بازگشت true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
تهی SDL_UnregisterApp(تهی)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    اگر (!app_registered) {
        بازگشت;
    }
    --app_registered;
    اگر (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = پوچ;
        wcex.hIconSm = پوچ;
        // Check for any registered window classes.
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
