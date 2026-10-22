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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव "../../events/scancodes_windows.h"
#अन्तर्भाव "../../main/SDL_main_callbacks.h"
#अन्तर्भाव "../../core/windows/SDL_hid.h"

// Dropfile support
#अन्तर्भाव <shellapi.h>

// Device names
#अन्तर्भाव <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#अन्तर्भाव <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ifdef HAVE_TPCSHRD_H
#अन्तर्भाव <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#जर 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#अन्तर्भाव <stdio.h>
#अन्तर्भाव "wmmsg.h"
#endif

#जर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#अन्तर्भाव <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#अन्तर्भाव "../../core/gdk/SDL_gdk.h"
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
#ifndef WM_आदान
#define WM_आदान 0x00ff
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

#ifndef IS_वरचा_SURROGATE
#define IS_वरचा_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
प्रकारव्याख्या Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

स्थिर bool SDL_processing_messages;
स्थिर DWORD message_tick;
स्थिर Uint64 timestamp_offset;

स्थिर शून्य WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

स्थिर Uint64 WIN_GetEventTimestamp(शून्य)
{
    स्थिरांक Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    जर (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        परत 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    जर (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } अन्यथा जर ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } अन्यथा जर (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    परत timestamp;
}

// A message hook called before TranslateMessage()
स्थिर SDL_WindowsMessageHook g_WindowsMessageHook = रिक्त;
स्थिर शून्य *g_WindowsMessageHookData = रिक्त;

शून्य SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, शून्य *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

स्थिर SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_किल्ली)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 किल्ली_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(किल्ली_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_किल्ली = (scanCode == 0);

    जर (scanCode != 0) {
        जर ((किल्ली_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } अन्यथा जर (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } अन्यथा {
        Uint16 vkCode = LOWORD(wParam);

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_किल्ली(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        जर (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    परत code;
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    परत !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

स्थिर शून्य WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    जर (bSwapButtons) {
        जर (button == SDL_BUTTON_डावा) {
            button = SDL_BUTTON_उजवा;
        } अन्यथा जर (button == SDL_BUTTON_उजवा) {
            button = SDL_BUTTON_डावा;
        }
    }

    जर (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        जर (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        परत;
    }

    जर (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } अन्यथा जर (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
स्थिर शून्य WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    जर (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(रिक्त, रिक्त);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_डावा, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_मधला, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_उजवा, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

स्थिर शून्य WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT किल्ली_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(रिक्त, रिक्त);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    किल्ली_State = Get_Async_किल्ली_State(VK_LBUTTON);
    जर (!(किल्ली_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_डावा, mouseID);
    }
    किल्ली_State = Get_Async_किल्ली_State(VK_RBUTTON);
    जर (!(किल्ली_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_उजवा, mouseID);
    }
    किल्ली_State = Get_Async_किल्ली_State(VK_MBUTTON);
    जर (!(किल्ली_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_मधला, mouseID);
    }
    किल्ली_State = Get_Async_किल्ली_State(VK_XBUTTON1);
    जर (!(किल्ली_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    किल्ली_State = Get_Async_किल्ली_State(VK_XBUTTON2);
    जर (!(किल्ली_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

स्थिर शून्य WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    जर (had_focus == has_focus || has_focus != expect_focus) {
        परत;
    }

    जर (has_focus) {
        POINT cursorPos;

        जर (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            जर (Get_Async_किल्ली_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            जर (Get_Async_किल्ली_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            जर (Get_Async_किल्ली_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            जर (Get_Async_किल्ली_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            जर (Get_Async_किल्ली_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        जर (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (दशांश)cursorPos.x, (दशांश)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_किल्ली_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_अंक, (Get_किल्ली_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_किल्ली_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } अन्यथा {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(रिक्त);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        जर (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(रिक्त);
        }
        WIN_Reset_Dead_किल्ल्या();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर bool ShouldGenerateWindowCloseOnAltF4(शून्य)
{
    परत SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

स्थिर bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    निवड (data->hint_erase_background_mode) {
    स्थिती SDL_ERASEBACKGROUNDMODE_NEVER:
        परत false;
    स्थिती SDL_ERASEBACKGROUNDMODE_INITIAL:
        परत !data->videodata->cleared;
    स्थिती SDL_ERASEBACKGROUNDMODE_ALWAYS:
        परत true;
    पूर्वनिर्धारित:
        // Unexpected value, fallback to default behaviour
        परत !data->videodata->cleared;
    }
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

प्रकारव्याख्या गणना
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

स्थिर SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    जर (IsTouchEvent(extrainfo)) {
        जर (extrainfo & 0x80) {
            परत SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } अन्यथा {
            परत SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    परत SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    जर (_this) {
        साठी (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            जर (data && data->hwnd == hwnd) {
                परत data;
            }
        }
    }
    परत रिक्त;
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(पूर्णांक nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    जर (nCode < 0 || nCode != HC_ACTION) {
        परत CallNextHookEx(रिक्त, nCode, wParam, lParam);
    }
    जर (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        परत 1;
    }

    निवड (hookData->vkCode) {
    स्थिती VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        थांबा;
    स्थिती VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        थांबा;
    स्थिती VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        थांबा;
    स्थिती VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        थांबा;
    स्थिती VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        थांबा;
    स्थिती VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        थांबा;
    स्थिती VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        थांबा;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    स्थिती VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        थांबा;
    स्थिती VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        थांबा;

    पूर्वनिर्धारित:
        परत CallNextHookEx(रिक्त, nCode, wParam, lParam);
    }

    जर (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        जर (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } अन्यथा {
        जर (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        जर (hookData->vkCode <= 0xFF && data->pre_hook_किल्ली_state[hookData->vkCode]) {
            data->pre_hook_किल्ली_state[hookData->vkCode] = 0;
            परत CallNextHookEx(रिक्त, nCode, wParam, lParam);
        }
    }

    परत 1;
}

स्थिर bool WIN_SwapButtons(HANDLE hDevice)
{
    जर (hDevice == रिक्त) {
        // Touchpad, already has buttons swapped
        परत false;
    }
    परत GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

स्थिर शून्य WIN_Handle_Raw_Mouse_आदान(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    स्थिर संरचना {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_डावा_BUTTON_DOWN, SDL_BUTTON_डावा, true },
        { RI_MOUSE_डावा_BUTTON_UP, SDL_BUTTON_डावा, false },
        { RI_MOUSE_उजवा_BUTTON_DOWN, SDL_BUTTON_उजवा, true },
        { RI_MOUSE_उजवा_BUTTON_UP, SDL_BUTTON_उजवा, false },
        { RI_MOUSE_मधला_BUTTON_DOWN, SDL_BUTTON_मधला, true },
        { RI_MOUSE_मधला_BUTTON_UP, SDL_BUTTON_मधला, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    पूर्णांक dx = (पूर्णांक)rawmouse->lLastX;
    पूर्णांक dy = (पूर्णांक)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    जर (!data->raw_mouse_enabled) {
        परत;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    जर (!window) {
        परत;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    जर (!mouse) {
        परत;
    }

    जर (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        परत;
    }

    SDL_WindowData *windowdata = window->internal;

    जर (haveMotion && !windowdata->in_modal_loop) {
        जर (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (दशांश)dx, (दशांश)dy);
        } अन्यथा {
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
            पूर्णांक w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            पूर्णांक h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            पूर्णांक x = raw_coordinates ? dx : (पूर्णांक)(((दशांश)dx / 65535.0f) * w);
            पूर्णांक y = raw_coordinates ? dy : (पूर्णांक)(((दशांश)dy / 65535.0f) * h);
            पूर्णांक relX, relY;

            /* Calculate relative motion */
            जर (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            जर (remote_desktop) {
                जर (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    स्थिर पूर्णांक wobble;
                    दशांश floatX = (दशांश)x / w;
                    दशांश floatY = (दशांश)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    जर (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        पूर्णांक warpX = rect.डावा + ((rect.उजवा - rect.डावा) / 2) + wobble;
                        पूर्णांक warpY = rect.शीर्ष + ((rect.bottom - rect.शीर्ष) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        जर (wobble > 1) {
                            wobble = -1;
                        }
                    } अन्यथा {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        स्थिरांक पूर्णांक MAX_RELATIVE_MOTION = (h / 6);
                        जर (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (दशांश)relX, (दशांश)relY);
                        }
                    }
                }
            } अन्यथा जर (mouse->pen_mouse_events) {
                स्थिरांक पूर्णांक MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                जर (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } अन्यथा {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (दशांश)relX, (दशांश)relY);
                }
            } अन्यथा {
                पूर्णांक screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                पूर्णांक screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                जर (!data->raw_आदान_fake_pen_id) {
                    data->raw_आदान_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, रिक्त, (शून्य *)(माप_प्रकार)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_आदान_fake_pen_id, window, (दशांश)(x + screen_x - window->x), (दशांश)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    जर (haveButton) {
        साठी (पूर्णांक i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            जर (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                जर (button == SDL_BUTTON_डावा) {
                    जर (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_उजवा;
                    }
                } अन्यथा जर (button == SDL_BUTTON_उजवा) {
                    जर (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_डावा;
                    }
                }

                जर (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    जर (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    सुरूठेवा;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        जर (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            दशांश fAmount = (दशांश)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } अन्यथा जर (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            दशांश fAmount = (दशांश)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

स्थिर शून्य WIN_Handle_Raw_Keyboard_आदान(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    जर (!data->raw_keyboard_enabled) {
        परत;
    }

    जर (rawkeyboard->Flags & RI_किल्ली_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_किल्ली_sequence = true;
        परत;
    }

    जर ((rawkeyboard->Flags & RI_किल्ली_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        परत;
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_किल्ली(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    जर (!rawkeyboard->MakeCode) {
        परत;
    }

    bool down;
    निवड (rawkeyboard->Message) {
    स्थिती WM_KEYDOWN:
    स्थिती WM_SYSKEYDOWN:
        down = true;
        थांबा;
    स्थिती WM_KEYUP:
    स्थिती WM_SYSKEYUP:
        down = false;
        थांबा;
    पूर्वनिर्धारित:
        down = !(rawkeyboard->Flags & RI_किल्ली_BREAK);
        थांबा;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    जर (data->pending_E1_किल्ली_sequence) {
        rawcode |= 0xE100;
        जर (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } अन्यथा {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_किल्ली_sequence = false;
    } अन्यथा {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        जर (rawkeyboard->Flags & RI_किल्ली_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    जर (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        जर ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_आदान_active)) {
            परत;
        }
    }

    SDL_Send_Keyboard_किल्ली(timestamp, keyboardID, rawcode, code, down);
}

शून्य WIN_Poll_Raw_आदान(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, मोजणी, total = 0;
    RAWINPUT *आदान;
    Uint64 poll_finish;

    जर (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = आकार(RAWINPUTHEADER);
        जर (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    आदान = (RAWINPUT *)data->rawinput;
    साठी (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)आदान - data->rawinput);
        मोजणी = Get_Raw_आदान_Buffer(आदान, &size, आकार(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        जर (मोजणी == 0 || मोजणी == (UINT)-1) {
            जर (!data->rawinput || (मोजणी == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                स्थिरांक UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                जर (!rawinput) {
                    थांबा;
                }
                आदान = (RAWINPUT *)(rawinput + ((BYTE *)आदान - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } अन्यथा {
                थांबा;
            }
        } अन्यथा {
            total += मोजणी;

            // Advance input to the end of the buffer
            पर्यंत (मोजणी--) {
                आदान = NEXTRAWINPUTBLOCK(आदान);
            }
        }
    }

    जर (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        साठी (i = 0, आदान = (RAWINPUT *)data->rawinput; i < total; ++i, आदान = NEXTRAWINPUTBLOCK(आदान)) {
            जर (आदान->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        पूर्णांक mouse_index = 0;
        साठी (i = 0, आदान = (RAWINPUT *)data->rawinput; i < total; ++i, आदान = NEXTRAWINPUTBLOCK(आदान)) {
            जर (आदान->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)आदान + data->rawinput_offset);
                Uint64 समय = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_आदान(समय, data, आदान->header.hDevice, rawmouse);
            } अन्यथा जर (आदान->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)आदान + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_आदान(poll_finish, data, आदान->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

स्थिर शून्य AddDeviceID(Uint32 deviceID, Uint32 **list, पूर्णांक *मोजणी)
{
    पूर्णांक new_मोजणी = (*मोजणी + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_मोजणी * आकार(*new_list));
    जर (!new_list) {
        // Oh well, we'll drop this one
        परत;
    }
    new_list[new_मोजणी - 1] = deviceID;

    *मोजणी = new_मोजणी;
    *list = new_list;
}

स्थिर bool HasDeviceID(Uint32 deviceID, स्थिरांक Uint32 *list, पूर्णांक मोजणी)
{
    साठी (पूर्णांक i = 0; i < मोजणी; ++i) {
        जर (deviceID == list[i]) {
            परत true;
        }
    }
    परत false;
}

स्थिर अक्षर *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, स्थिरांक अक्षर *instance, Uint16 vendor, Uint16 product, स्थिरांक अक्षर *default_name, bool hid_loaded)
{
    अक्षर *vendor_name = रिक्त;
    अक्षर *product_name = रिक्त;
    अक्षर *name = रिक्त;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    जर (hid_loaded) {
        अक्षर devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = आकार(devName) - 1;
        UINT len = Get_Raw_आदान_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        जर (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, रिक्त, OPEN_EXISTING, 0, रिक्त);
            जर (hFile != INVALID_HANDLE_मूल्य) {
                SDL_HidD_GetManufacturerString(hFile, vend, आकार(vend));
                SDL_HidD_GetProductString(hFile, prod, आकार(prod));
                CloseHandle(hFile);
            }
        }
    }

    जर (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    जर (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } अन्यथा {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = आकार(data);
        साठी (DWORD i = 0;; ++i) {
            जर (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                जर (GetLastError() == ERROR_NO_MORE_वस्तुसंच) {
                    थांबा;
                } अन्यथा {
                    सुरूठेवा;
                }
            }

            अक्षर DeviceInstanceId[64];
            जर (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, आकार(DeviceInstanceId), रिक्त))
                सुरूठेवा;

            जर (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                जर (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, रिक्त, (PBYTE)prod, आकार(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= आकार(*prod);
                    जर (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    जर (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } अन्यथा {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                थांबा;
            }
        }
    }

    जर (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    परत name;
}

शून्य WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = रिक्त;
    UINT raw_device_मोजणी = 0;
    पूर्णांक old_keyboard_मोजणी = 0;
    SDL_KeyboardID *old_keyboards = रिक्त;
    पूर्णांक new_keyboard_मोजणी = 0;
    SDL_KeyboardID *new_keyboards = रिक्त;
    पूर्णांक old_mouse_मोजणी = 0;
    SDL_MouseID *old_mice = रिक्त;
    पूर्णांक new_mouse_मोजणी = 0;
    SDL_MouseID *new_mice = रिक्त;

    जर (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        परत;
    }

    जर ((Get_Raw_आदान_Device_List(रिक्त, &raw_device_मोजणी, आकार(RAWINPUTDEVICELIST)) == -1) || (!raw_device_मोजणी)) {
        परत; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(आकार(RAWINPUTDEVICELIST) * raw_device_मोजणी);
    जर (!raw_devices) {
        परत; // oh well.
    }

    raw_device_मोजणी = Get_Raw_आदान_Device_List(raw_devices, &raw_device_मोजणी, आकार(RAWINPUTDEVICELIST));
    जर (raw_device_मोजणी == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = रिक्त;
        परत; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(रिक्त, रिक्त, रिक्त, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_मोजणी);
    old_mice = SDL_GetMice(&old_mouse_मोजणी);

    साठी (UINT i = 0; i < raw_device_मोजणी; i++) {
        RID_DEVICE_INFO rdi;
        अक्षर devName[MAX_PATH] = { 0 };
        UINT rdiSize = आकार(rdi);
        UINT nameSize = SDL_arraysize(devName);
        पूर्णांक vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        अक्षर *instance, *ptr, *name;

        जर (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            सुरूठेवा;
        }

        rdi.cbSize = आकार(rdi);
        जर (Get_Raw_आदान_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_आदान_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            सुरूठेवा;
        }

        // Extract the device instance
        instance = devName;
        पर्यंत (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        साठी (ptr = instance; *ptr; ++ptr) {
            जर (*ptr == '#') {
                *ptr = '\\';
            }
            जर (*ptr == '{') {
                जर (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                थांबा;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        निवड (dwType) {
        स्थिती RIM_TYPEKEYBOARD:
            जर (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_संख्या_Of_किल्ल्या_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_मोजणी);
                जर (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_मोजणी)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            थांबा;
        स्थिती RIM_TYPEMOUSE:
            जर (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_मोजणी);
                जर (!HasDeviceID(mouseID, old_mice, old_mouse_मोजणी)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            थांबा;
        पूर्वनिर्धारित:
            थांबा;
        }
    }

    साठी (पूर्णांक i = old_keyboard_मोजणी; i--;) {
        जर (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_मोजणी)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    साठी (पूर्णांक i = old_mouse_मोजणी; i--;) {
        जर (!HasDeviceID(old_mice[i], new_mice, new_mouse_मोजणी)) {
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
स्थिर bool Skip_Alt_Gr_डावा_Control(WPARAM wParam, LPARAM lParam)
{
    जर (wParam != VK_CONTROL) {
        परत false;
    }

    // Is this an extended key (i.e. right key)?
    जर (lParam & 0x01000000) {
        परत false;
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    संदेश_2 next_संदेश;
    DWORD संदेश_time = GetMessageTime();
    जर (PeekMessage(&next_संदेश, रिक्त, 0, 0, PM_NOREMOVE)) {
        जर (next_संदेश.message == WM_KEYDOWN ||
            next_संदेश.message == WM_SYSKEYDOWN) {
            जर (next_संदेश.wParam == VK_MENU && (next_संदेश.lParam & 0x01000000) && next_संदेश.समय == संदेश_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                परत true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    परत false;
}

स्थिर bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *संदेश, WPARAM *wParam, LPARAM *lParam)
{
    संदेश_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *संदेश;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    जर (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *संदेश = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        परत true;
    }
    परत false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    जर (!data) {
        परत CallWindowProc(DefWindowProc, hwnd, संदेश, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        अक्षर message[1024];
        जर (संदेश > MAX_WMMSG) {
            SDL_snprintf(message, आकार(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, संदेश, wParam, lParam);
        } अन्यथा {
            SDL_snprintf(message, आकार(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[संदेश], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    जर (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        जर (!DispatchModalLoopMessageHook(&hwnd, &संदेश, &wParam, &lParam)) {
            परत 0;
        }
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (WIN_HandleIMEMessage(hwnd, संदेश, wParam, &lParam, data->videodata)) {
        परत 0;
    }
#endif

    निवड (संदेश) {

    स्थिती WM_SHOWWINDOW:
    {
        जर (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } अन्यथा {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } थांबा;

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    स्थिती WM_NCACTIVATE:
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
        जर (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } थांबा;

    स्थिती WM_NCUAHDRAWCAPTION:
    स्थिती WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        जर (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } थांबा;

    स्थिती WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        स्थिरांक DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } थांबा;

    स्थिती WM_MOUSEACTIVATE:
    {
        जर (SDL_WINDOW_IS_POPUP(data->window)) {
            परत MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        पर्यंत (parent) {
            जर ((parent->flags & SDL_WINDOW_आदान_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                परत MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } थांबा;

    स्थिती WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        स्थिरांक DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } थांबा;

    स्थिती WM_KILLFOCUS:
    स्थिती WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        स्थिरांक DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } थांबा;

    स्थिती WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिरांक UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_आदान_TYPE pointer_type = PT_POINTER;
        जर (!data->videodata->GetPointerType) {
            थांबा;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा जर (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            थांबा;  // oh well.
        } अन्यथा जर (pointer_type != PT_PEN) {
            थांबा;  // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिरांक SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        जर (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } अन्यथा {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.अंक_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), रिक्त, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } थांबा;

    स्थिती WM_POINTERCAPTURECHANGED:
    स्थिती WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिरांक UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_आदान_TYPE pointer_type = PT_POINTER;
        जर (!data->videodata->GetPointerType) {
            थांबा;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा जर (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            थांबा;  // oh well.
        } अन्यथा जर (pointer_type != PT_PEN) {
            थांबा;  // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिरांक SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        जर (pen == 0) {
            थांबा;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        जर ((संदेश == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } थांबा;

    स्थिती WM_POINTERDOWN:
    स्थिती WM_POINTERUP:
    स्थिती WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिरांक UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_आदान_TYPE pointer_type = PT_POINTER;
        जर (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            थांबा;  // oh well.
        } अन्यथा जर ((संदेश == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            थांबा;
        } अन्यथा जर (pointer_type != PT_PEN) {
            थांबा; // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिरांक SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        जर (pen == 0) {
            थांबा;  // not a pen, or not a pen we already knew about.
        } अन्यथा जर (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            थांबा;  // oh well.
        }

        स्थिरांक Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        स्थिरांक bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        जर (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        स्थिरांक POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        दशांश fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        जर (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (दशांश) position.x;
            fy = (दशांश) position.y;
        } अन्यथा {
            पूर्णांक ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            स्थिरांक SDL_FPoint window_pos = { (दशांश) ix, (दशांश) iy };

            स्थिरांक दशांश facX = pointer_info->ptHimetricLocationRaw.x / (दशांश) (tablet_bounds.उजवा );
            स्थिरांक दशांश facY = pointer_info->ptHimetricLocationRaw.y / (दशांश) (tablet_bounds.bottom);

            स्थिरांक दशांश w = tablet_mapping.उजवा  - tablet_mapping.डावा;
            स्थिरांक दशांश h = tablet_mapping.bottom - tablet_mapping.शीर्ष;

            fx = (tablet_mapping.डावा + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.शीर्ष  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        जर (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((दशांश) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        जर (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((दशांश) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        जर (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((दशांश) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        जर (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((दशांश) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        जर (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } थांबा;

    स्थिती WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        जर (window->flags & SDL_WINDOW_आदान_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            जर (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        जर (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = आकार(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            जर (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        जर (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            जर (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (दशांश)GET_X_LPARAM(lParam), (दशांश)GET_Y_LPARAM(lParam));
            }
        }

    } थांबा;

    स्थिती WM_LBUTTONUP:
    स्थिती WM_RBUTTONUP:
    स्थिती WM_MBUTTONUP:
    स्थिती WM_XBUTTONUP:
    स्थिती WM_LBUTTONDOWN:
    स्थिती WM_LBUTTONDBLCLK:
    स्थिती WM_RBUTTONDOWN:
    स्थिती WM_RBUTTONDBLCLK:
    स्थिती WM_MBUTTONDOWN:
    स्थिती WM_MBUTTONDBLCLK:
    स्थिती WM_XBUTTONDOWN:
    स्थिती WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        जर (!data->videodata->raw_mouse_enabled) {
            जर (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } थांबा;

#जर 0   // We handle raw input all at once instead of using a syscall for each mouse event
    स्थिती WM_आदान:
    {
        HRAWINPUT h_Raw_आदान = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = आकार(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        जर (data->window != SDL_GetKeyboardFocus()) {
            थांबा;
        }

        Get_Raw_आदान_Data(h_Raw_आदान, RID_आदान, &inp, &size, आकार(RAWINPUTHEADER));
        जर (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_आदान(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } अन्यथा जर (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_आदान(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } थांबा;
#endif

    स्थिती WM_MOUSEWHEEL:
    स्थिती WM_MOUSEHWHEEL:
    {
        जर (!data->videodata->raw_mouse_enabled) {
            लघु amount = GET_WHEEL_DELTA_WPARAM(wParam);
            दशांश fAmount = (दशांश)amount / WHEEL_DELTA;
            जर (संदेश == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } अन्यथा {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } थांबा;

    स्थिती WM_MOUSELEAVE:
        जर (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            जर (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                जर (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (दशांश)cursorPos.x, (दशांश)cursorPos.y);
                } अन्यथा {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    जर (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (दशांश)cursorPos.x, (दशांश)cursorPos.y);
                    } अन्यथा { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (दशांश)cursorPos.x, (दशांश)cursorPos.y);
                    }
                }
            }

            जर (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(रिक्त);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        थांबा;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    स्थिती WM_KEYDOWN:
    स्थिती WM_SYSKEYDOWN:
    {
        जर (Skip_Alt_Gr_डावा_Control(wParam, lParam)) {
            returnCode = 0;
            थांबा;
        }

        bool virtual_किल्ली = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_किल्ली);

        // Detect relevant keyboard shortcuts
        जर (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            जर (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        जर (virtual_किल्ली || !data->videodata->raw_keyboard_enabled || data->window->text_आदान_active) {
            SDL_Send_Keyboard_किल्ली(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        थांबा;

    स्थिती WM_SYSKEYUP:
    स्थिती WM_KEYUP:
    {
        जर (Skip_Alt_Gr_डावा_Control(wParam, lParam)) {
            returnCode = 0;
            थांबा;
        }

        bool virtual_किल्ली = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_किल्ली);
        स्थिरांक bool *keyboardState = SDL_GetKeyboardState(रिक्त);

        जर (virtual_किल्ली || !data->videodata->raw_keyboard_enabled || data->window->text_आदान_active) {
            जर (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_किल्ली(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_किल्ली(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        थांबा;

    स्थिती WM_UNICHAR:
        जर (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } अन्यथा {
            जर (SDL_Text_आदान_Active(data->window)) {
                अक्षर text[5];
                अक्षर *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        थांबा;

    स्थिती WM_CHAR:
        जर (SDL_Text_आदान_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            जर (IS_वरचा_SURROGATE(wParam)) {
                data->वरचा_surrogate = (WCHAR)wParam;
            } अन्यथा {
                WCHAR utf16[3];

                utf16[0] = data->वरचा_surrogate ? data->वरचा_surrogate : (WCHAR)wParam;
                utf16[1] = data->वरचा_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                अक्षर utf8[5];
                पूर्णांक result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, आकार(utf8), रिक्त, रिक्त);
                जर (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->वरचा_surrogate = L'\0';
            }
        } अन्यथा {
            data->वरचा_surrogate = L'\0';
        }

        returnCode = 0;
        थांबा;

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    स्थिती WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        थांबा;
#endif // WM_INPUTLANGCHANGE

    स्थिती WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        जर (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } थांबा;

    स्थिती WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } थांबा;

#ifdef WM_GETMINMAXINFO
    स्थिती WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        पूर्णांक x, y;
        पूर्णांक w, h;
        पूर्णांक min_w, min_h;
        पूर्णांक max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        जर (data->expected_resize) {
            थांबा;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.डावा;
        y = size.शीर्ष;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        जर (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } अन्यथा {
            constrain_max_size = FALSE;
        }

        जर (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.शीर्ष = 0;
            size.डावा = 0;
            size.bottom = h;
            size.उजवा = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.उजवा - size.डावा;
            h = size.bottom - size.शीर्ष;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        जर (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            जर (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                पूर्णांक screenW = GetSystemMetrics(SM_CXSCREEN);
                पूर्णांक screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            जर (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } अन्यथा {
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
        थांबा;
#endif // WM_GETMINMAXINFO

    स्थिती WM_WINDOWPOSCHANGING:

        जर (data->expected_resize) {
            returnCode = 0;
        } अन्यथा जर (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            जर (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        थांबा;

    स्थिती WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        स्थिरांक SDL_DisplayID original_displayID = data->window->displayID;
        स्थिरांक WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        पूर्णांक x, y;
        पूर्णांक w, h;

        जर (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        जर (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } अन्यथा जर (zoomed) {
            जर (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } अन्यथा जर (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            जर (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        जर (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        जर (iconic) {
            थांबा;
        }

        जर (data->initializing) {
            थांबा;
        }

        जर (!data->disable_move_size_events) {
            जर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.डावा;
                y = rect.शीर्ष;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            जर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.उजवा;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        जर (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        साठी (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            जर (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } थांबा;

    स्थिती WM_ENTERSIZEMOVE:
    स्थिती WM_ENTERMENULOOP:
    {
        जर (g_WindowsMessageHook) {
            जर (!DispatchModalLoopMessageHook(&hwnd, &संदेश, &wParam, &lParam)) {
                परत 0;
            }
        }

        ++data->in_modal_loop;
        जर (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.उजवा - rect.डावा;
            data->last_modal_height = rect.bottom - rect.शीर्ष;

            data->initial_size_rect.डावा = data->window->x;
            data->initial_size_rect.उजवा = data->window->x + data->window->w;
            data->initial_size_rect.शीर्ष = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, रिक्त);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } थांबा;

    स्थिती WM_TIMER:
    {
        जर (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#जर 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            जर (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            परत 0;
        }
    } थांबा;

    स्थिती WM_EXITSIZEMOVE:
    स्थिती WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        जर (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } थांबा;

    स्थिती WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            दशांश new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            जर (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                थांबा;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            जर (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != रिक्त, GetWindowExStyle(hwnd))) {
                थांबा;
            }

            clientDragRect.डावा -= rc.डावा;
            clientDragRect.शीर्ष -= rc.शीर्ष;
            clientDragRect.उजवा -= rc.उजवा;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.उजवा - clientDragRect.डावा;
            h = clientDragRect.bottom - clientDragRect.शीर्ष;
            new_aspect = w / (दशांश)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            जर (lock_aspect_ratio) {
                निवड (edge) {
                स्थिती WMSZ_डावा:
                स्थिती WMSZ_उजवा:
                    h = (पूर्णांक)SDL_roundf(w / data->window->max_aspect);
                    थांबा;
                पूर्वनिर्धारित:
                    // resizing via corners or top or bottom
                    w = (पूर्णांक)SDL_roundf(h * data->window->max_aspect);
                    थांबा;
                }
            } अन्यथा {
                निवड (edge) {
                स्थिती WMSZ_डावा:
                स्थिती WMSZ_उजवा:
                    जर (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * data->window->max_aspect);
                    } अन्यथा जर (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * data->window->min_aspect);
                    }
                    थांबा;
                स्थिती WMSZ_शीर्ष:
                स्थिती WMSZ_BOTTOM:
                    जर (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / data->window->min_aspect);
                    } अन्यथा जर (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / data->window->max_aspect);
                    }
                    थांबा;

                पूर्वनिर्धारित:
                    // resizing via corners
                    जर (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * data->window->max_aspect);
                    } अन्यथा जर (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / data->window->min_aspect);
                    }
                    थांबा;
                }
            }

            निवड (edge) {
            स्थिती WMSZ_डावा:
                clientDragRect.डावा = clientDragRect.उजवा - w;
                जर (lock_aspect_ratio) {
                    clientDragRect.शीर्ष = (data->initial_size_rect.bottom + data->initial_size_rect.शीर्ष - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                थांबा;
            स्थिती WMSZ_BOTTOMLEFT:
                clientDragRect.डावा = clientDragRect.उजवा - w;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                थांबा;
            स्थिती WMSZ_उजवा:
                clientDragRect.उजवा = w + clientDragRect.डावा;
                जर (lock_aspect_ratio) {
                    clientDragRect.शीर्ष = (data->initial_size_rect.bottom + data->initial_size_rect.शीर्ष - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                थांबा;
            स्थिती WMSZ_TOPRIGHT:
                clientDragRect.उजवा = w + clientDragRect.डावा;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                थांबा;
            स्थिती WMSZ_शीर्ष:
                जर (lock_aspect_ratio) {
                    clientDragRect.डावा = (data->initial_size_rect.उजवा + data->initial_size_rect.डावा - w) / 2;
                }
                clientDragRect.उजवा = w + clientDragRect.डावा;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                थांबा;
            स्थिती WMSZ_TOPLEFT:
                clientDragRect.डावा = clientDragRect.उजवा - w;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                थांबा;
            स्थिती WMSZ_BOTTOM:
                जर (lock_aspect_ratio) {
                    clientDragRect.डावा = (data->initial_size_rect.उजवा + data->initial_size_rect.डावा - w) / 2;
                }
                clientDragRect.उजवा = w + clientDragRect.डावा;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                थांबा;
            स्थिती WMSZ_BOTTOMRIGHT:
                clientDragRect.उजवा = w + clientDragRect.डावा;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                थांबा;
            }

            // convert the client rect to a window rect
            जर (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != रिक्त, GetWindowExStyle(hwnd))) {
                थांबा;
            }

            *dragRect = clientDragRect;
        }
        थांबा;

    स्थिती WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        जर (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } अन्यथा जर (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(रिक्त);
            returnCode = TRUE;
        }
    } थांबा;

        // We were occluded, refresh our display
    स्थिती WM_PAINT:
    {
        RECT rect;
        जर (GetUpdateRect(hwnd, &rect, FALSE)) {
            स्थिरांक LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            जर (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, रिक्त);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        थांबा;

        // We'll do our own drawing, prevent flicker
    स्थिती WM_ERASEBKGND:
        जर (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        परत 1;

    स्थिती WM_SYSCOMMAND:
    {
        जर (!g_WindowsEnableMenuMnemonics) {
            जर ((wParam & 0xFFF0) == SC_KEYMENU) {
                परत 0;
            }
        }

#जर defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        जर ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            जर (SDL_GetVideoDevice()->suspend_screensaver) {
                परत 0;
            }
        }
#endif // System has screensaver support
    } थांबा;

    स्थिती WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        थांबा;

    स्थिती WM_TOUCH:
        जर (data->videodata->Get_Touch_आदान_Info && data->videodata->Close_Touch_आदान_Handle) {
            UINT i, अंक_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, अंक_inputs, &isstack);
            जर (inputs && data->videodata->Get_Touch_आदान_Info((HTOUCHINPUT)lParam, अंक_inputs, inputs, आकार(TOUCHINPUT))) {
                RECT rect;
                दशांश x, y;

                जर (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    जर (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    थांबा;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.शीर्ष *= 100;
                rect.डावा *= 100;
                rect.bottom *= 100;
                rect.उजवा *= 100;

                साठी (i = 0; i < अंक_inputs; ++i) {
                    PTOUCHINPUT आदान = &inputs[i];
                    स्थिरांक पूर्णांक w = (rect.उजवा - rect.डावा);
                    स्थिरांक पूर्णांक h = (rect.bottom - rect.शीर्ष);

                    स्थिरांक SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)आदान->hSource);
                    स्थिरांक SDL_FingerID fingerId = (आदान->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    जर (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (आदान->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        सुरूठेवा;
                    }

                    // Get the normalized coordinates for the window
                    जर (w <= 1) {
                        x = 0.5f;
                    } अन्यथा {
                        x = (दशांश)(आदान->x - rect.डावा) / (w - 1);
                    }
                    जर (h <= 1) {
                        y = 0.5f;
                    } अन्यथा {
                        y = (दशांश)(आदान->y - rect.शीर्ष) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    जर (आदान->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    जर (आदान->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    जर (आदान->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_आदान_Handle((HTOUCHINPUT)lParam);
            परत 0;
        }
        थांबा;

#ifdef HAVE_TPCSHRD_H

    स्थिती WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        परत TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    स्थिती WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT मोजणी = DragQueryFile(drop, 0xFFFFFFFF, रिक्त, 0);
        साठी (i = 0; i < मोजणी; ++i) {
            UINT size = DragQueryFile(drop, i, रिक्त, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(आकार(TCHAR) * size);
            जर (buffer) {
                जर (DragQueryFile(drop, i, buffer, size)) {
                    अक्षर *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, रिक्त, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        परत 0;
    }

    स्थिती WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } थांबा;

    स्थिती WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        जर (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            जर (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                जर (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    स्थिरांक POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                जर (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = आकार(info);
                    जर (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } अन्यथा जर (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                पूर्णांक w, h;
                जर (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } अन्यथा {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].उजवा = params->rgrc[0].डावा + w;
                params->rgrc[0].bottom = params->rgrc[0].शीर्ष + h;
            }
            परत 0;
        }
    } थांबा;

    स्थिती WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        जर (window->flags & SDL_WINDOW_TOOLTIP) {
            परत HTTRANSPARENT;
        }

        जर (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            जर (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                निवड (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        परत ret;                                                        \
    }
                स्थिती SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(रिक्त, रिक्त);
                    जर (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        परत HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                स्थिती SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                स्थिती SDL_HITTEST_RESIZE_शीर्ष:
                    POST_HIT_TEST(HTTOP);
                स्थिती SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                स्थिती SDL_HITTEST_RESIZE_उजवा:
                    POST_HIT_TEST(HTRIGHT);
                स्थिती SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                स्थिती SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                स्थिती SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                स्थिती SDL_HITTEST_RESIZE_डावा:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                स्थिती SDL_HITTEST_NORMAL:
                    परत HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } थांबा;

    स्थिती WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        जर (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            स्थिरांक पूर्णांक nextDPI = (पूर्णांक)wParam;
            स्थिरांक पूर्णांक prevDPI = (पूर्णांक)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            पूर्णांक frame_w, frame_h;
            पूर्णांक query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                जर (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.डावा + rect.उजवा;
                frame_h = -rect.शीर्ष + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.उजवा = query_client_w_win;
                rect.bottom = query_client_h_win;

                जर (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.उजवा - rect.डावा;
                sizeInOut->cy = rect.bottom - rect.शीर्ष;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            परत TRUE;
        }
        थांबा;

    स्थिती WM_DPICHANGED:
        // Windows 8.1+
        {
            स्थिरांक पूर्णांक newDPI = HIWORD(wParam);
            RECT *स्थिरांक suggestedRect = (RECT *)lParam;
            पूर्णांक w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->डावा, suggestedRect->शीर्ष, suggestedRect->उजवा - suggestedRect->डावा, suggestedRect->bottom - suggestedRect->शीर्ष);
#endif

            जर (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                परत 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.उजवा = data->window->w;
                rect.bottom = data->window->h;

                जर (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.उजवा - rect.डावा;
                h = rect.bottom - rect.शीर्ष;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->डावा, suggestedRect->शीर्ष, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         रिक्त,
                         suggestedRect->डावा,
                         suggestedRect->शीर्ष,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            परत 0;
        }

    स्थिती WM_SETTINGCHANGE:
        जर (wParam == 0 && lParam != 0 && SDL_wcscmp((ब_अक्षर_प्रकार *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        जर (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        जर (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        थांबा;
#अन्यथा
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    स्थिती WM_SIZE:
    {
        RECT rect;
        पूर्णांक w, h;

        जर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.उजवा;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } थांबा;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    पूर्वनिर्धारित:
        थांबा;
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (संदेश && संदेश == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    जर (data->wndproc) {
        परत CallWindowProc(data->wndproc, hwnd, संदेश, wParam, lParam);
    } अन्यथा जर (returnCode >= 0) {
        परत returnCode;
    } अन्यथा {
        परत CallWindowProc(DefWindowProc, hwnd, संदेश, wParam, lParam);
    }
}

पूर्णांक WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    जर (g_WindowsEnableMessageLoop) {
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = संदेश_Wait_For_Multiple_Objects(0, रिक्त, FALSE, timeout, QS_ALLINPUT);
        जर (ret == WAIT_OBJECT_0) {
            परत 1;
        } अन्यथा {
            परत 0;
        }
#अन्यथा
        // MsgWaitForMultipleObjects is desktop-only.
        संदेश_2 संदेश;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        जर (timeoutNS > 0) {
            timer_id = SetTimer(रिक्त, 0, (UINT)SDL_NS_TO_MS(timeoutNS), रिक्त);
            message_result = GetMessage(&संदेश, 0, 0, 0);
            KillTimer(रिक्त, timer_id);
        } अन्यथा जर (timeoutNS == 0) {
            message_result = PeekMessage(&संदेश, रिक्त, 0, 0, PM_REMOVE);
        } अन्यथा {
            message_result = GetMessage(&संदेश, 0, 0, 0);
        }
        जर (message_result) {
            जर (संदेश.message == WM_TIMER && !संदेश.hwnd && संदेश.wParam == timer_id) {
                परत 0;
            }
            जर (g_WindowsMessageHook) {
                जर (!g_WindowsMessageHook(g_WindowsMessageHookData, &संदेश)) {
                    परत 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
            परत 1;
        } अन्यथा {
            परत 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } अन्यथा {
        // Fail the wait so the caller falls back to polling
        परत -1;
    }
}

शून्य WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
शून्य WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    संदेश_2 संदेश;

    जर (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        पर्यंत (PeekMessage(&संदेश, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(संदेश.समय);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
        }

        SDL_processing_messages = false;
    }
}

शून्य WIN_PumpEvents(SDL_VideoDevice *_this)
{
    संदेश_2 संदेश;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ढकला)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_मोजणी() + 1;
#ifdef _MSC_VER
#pragma warning(काढा)
#endif
    पूर्णांक new_messages = 0;

    जर (_this->internal->gameinput_context) {
        WIN_Update_Game_आदान(_this);
    }

    जर (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        पर्यंत (PeekMessage(&संदेश, रिक्त, 0, 0, PM_REMOVE)) {
            जर (g_WindowsMessageHook) {
                जर (!g_WindowsMessageHook(g_WindowsMessageHookData, &संदेश)) {
                    सुरूठेवा;
                }
            }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            जर (संदेश.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                जर (!SDL_TICKS_PASSED(संदेश.समय, (SDL_last_warp_time + 1))) {
                    सुरूठेवा;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(संदेश.समय);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            जर (SDL_TICKS_PASSED(संदेश.समय, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                स्थिरांक पूर्णांक MAX_NEW_MESSAGES = 3;
                ++new_messages;
                जर (new_messages > MAX_NEW_MESSAGES) {
                    थांबा;
                }
            }
        }

        SDL_processing_messages = false;
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    स्थिरांक bool *keystate = SDL_GetKeyboardState(रिक्त);
    जर (keystate[SDL_SCANCODE_LSHIFT] && !(Get_किल्ली_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    जर (keystate[SDL_SCANCODE_RSHIFT] && !(Get_किल्ली_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    जर (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        जर (keystate[SDL_SCANCODE_LGUI] && !(Get_किल्ली_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        जर (keystate[SDL_SCANCODE_RGUI] && !(Get_किल्ली_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    जर (_this) {
        SDL_Window *window = _this->windows;
        पर्यंत (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            जर (data) {
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
            जर (refresh_clipcursor) {
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
    जर (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        जर (!data->mouse_tracked) {
            POINT cursorPos;

            जर (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (दशांश)cursorPos.x, (दशांश)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_डावा : SDL_BUTTON_उजवा,
                                    (Get_Async_किल्ली_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_उजवा : SDL_BUTTON_डावा,
                                    (Get_Async_किल्ली_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_मधला,
                                    (Get_Async_किल्ली_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_किल्ली_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_किल्ली_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

स्थिर पूर्णांक app_registered = 0;
LPTSTR SDL_Appname = रिक्त;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = रिक्त;

स्थिर शून्य WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    जर (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = रिक्त;
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (शून्य)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    परत FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(स्थिरांक अक्षर *name, Uint32 style, शून्य *hInst)
{
    WNDCLASSEX wcex;
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    स्थिरांक अक्षर *hint;
#endif

    // Only do this once...
    जर (app_registered) {
        ++app_registered;
        परत true;
    }
    SDL_assert(!SDL_Appname);
    जर (!name) {
        name = "SDL_app";
#जर defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(रिक्त);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = आकार(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    जर (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        जर (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } अन्यथा {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    जर (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        परत SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    परत true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
शून्य SDL_UnregisterApp(शून्य)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    जर (!app_registered) {
        परत;
    }
    --app_registered;
    जर (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = रिक्त;
        wcex.hIconSm = रिक्त;
        // Check for any registered window classes.
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        जर (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
