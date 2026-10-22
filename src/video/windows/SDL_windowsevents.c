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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_touch_c.h"
#அந்தர்பாவ "../../events/scancodes_windows.h"
#அந்தர்பாவ "../../main/SDL_main_callbacks.h"
#அந்தர்பாவ "../../core/windows/SDL_hid.h"

// Dropfile support
#அந்தர்பாவ <shellapi.h>

// Device names
#அந்தர்பாவ <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#அந்தர்பாவ <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ifdef HAVE_TPCSHRD_H
#அந்தர்பாவ <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#எனில் 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ "wmmsg.h"
#endif

#எனில் !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#அந்தர்பாவ <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#அந்தர்பாவ "../../core/gdk/SDL_gdk.h"
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
#ifndef WM_உள்ளீடு
#define WM_உள்ளீடு 0x00ff
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

#ifndef IS_உயர்வு_SURROGATE
#define IS_உயர்வு_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
வகைவரை Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

நிலையான bool SDL_processing_messages;
நிலையான DWORD message_tick;
நிலையான Uint64 timestamp_offset;

நிலையான வெறுமை WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

நிலையான Uint64 WIN_GetEventTimestamp(வெறுமை)
{
    மாறிலி Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    எனில் (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        திரும்பு 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    எனில் (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } இல்லையெனில் எனில் ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } இல்லையெனில் எனில் (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    திரும்பு timestamp;
}

// A message hook called before TranslateMessage()
நிலையான SDL_WindowsMessageHook g_WindowsMessageHook = வெற்று;
நிலையான வெறுமை *g_WindowsMessageHookData = வெற்று;

வெறுமை SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, வெறுமை *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

நிலையான SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_சாவி)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 சாவி_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(சாவி_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_சாவி = (scanCode == 0);

    எனில் (scanCode != 0) {
        எனில் ((சாவி_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } இல்லையெனில் எனில் (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } இல்லையெனில் {
        Uint16 vkCode = LOWORD(wParam);

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_சாவி(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        எனில் (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    திரும்பு code;
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
நிலையான bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    திரும்பு !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

நிலையான வெறுமை WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    எனில் (bSwapButtons) {
        எனில் (button == SDL_BUTTON_இடது) {
            button = SDL_BUTTON_வலது;
        } இல்லையெனில் எனில் (button == SDL_BUTTON_வலது) {
            button = SDL_BUTTON_இடது;
        }
    }

    எனில் (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        எனில் (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        திரும்பு;
    }

    எனில் (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } இல்லையெனில் எனில் (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
நிலையான வெறுமை WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    எனில் (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(வெற்று, வெற்று);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_இடது, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_நடு, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_வலது, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

நிலையான வெறுமை WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT சாவி_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(வெற்று, வெற்று);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    சாவி_State = Get_Async_சாவி_State(VK_LBUTTON);
    எனில் (!(சாவி_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_இடது, mouseID);
    }
    சாவி_State = Get_Async_சாவி_State(VK_RBUTTON);
    எனில் (!(சாவி_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_வலது, mouseID);
    }
    சாவி_State = Get_Async_சாவி_State(VK_MBUTTON);
    எனில் (!(சாவி_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_நடு, mouseID);
    }
    சாவி_State = Get_Async_சாவி_State(VK_XBUTTON1);
    எனில் (!(சாவி_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    சாவி_State = Get_Async_சாவி_State(VK_XBUTTON2);
    எனில் (!(சாவி_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

நிலையான வெறுமை WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    எனில் (had_focus == has_focus || has_focus != expect_focus) {
        திரும்பு;
    }

    எனில் (has_focus) {
        POINT cursorPos;

        எனில் (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            எனில் (Get_Async_சாவி_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            எனில் (Get_Async_சாவி_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            எனில் (Get_Async_சாவி_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            எனில் (Get_Async_சாவி_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            எனில் (Get_Async_சாவி_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        எனில் (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (தசம)cursorPos.x, (தசம)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_சாவி_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_இலக்கம், (Get_சாவி_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_சாவி_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } இல்லையெனில் {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(வெற்று);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        எனில் (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(வெற்று);
        }
        WIN_Reset_Dead_சாவிகள்();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

நிலையான bool ShouldGenerateWindowCloseOnAltF4(வெறுமை)
{
    திரும்பு SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

நிலையான bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    தேர்வு (data->hint_erase_background_mode) {
    நிலை SDL_ERASEBACKGROUNDMODE_NEVER:
        திரும்பு false;
    நிலை SDL_ERASEBACKGROUNDMODE_INITIAL:
        திரும்பு !data->videodata->cleared;
    நிலை SDL_ERASEBACKGROUNDMODE_ALWAYS:
        திரும்பு true;
    இயல்பு:
        // Unexpected value, fallback to default behaviour
        திரும்பு !data->videodata->cleared;
    }
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

வகைவரை எண்ணிக்கை
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

நிலையான SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    எனில் (IsTouchEvent(extrainfo)) {
        எனில் (extrainfo & 0x80) {
            திரும்பு SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } இல்லையெனில் {
            திரும்பு SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    திரும்பு SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

நிலையான SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    எனில் (_this) {
        க்கு (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            எனில் (data && data->hwnd == hwnd) {
                திரும்பு data;
            }
        }
    }
    திரும்பு வெற்று;
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(முழு nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    எனில் (nCode < 0 || nCode != HC_ACTION) {
        திரும்பு CallNextHookEx(வெற்று, nCode, wParam, lParam);
    }
    எனில் (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        திரும்பு 1;
    }

    தேர்வு (hookData->vkCode) {
    நிலை VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        நிறுத்து;
    நிலை VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        நிறுத்து;
    நிலை VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        நிறுத்து;
    நிலை VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        நிறுத்து;
    நிலை VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        நிறுத்து;
    நிலை VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        நிறுத்து;
    நிலை VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        நிறுத்து;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    நிலை VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        நிறுத்து;
    நிலை VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        நிறுத்து;

    இயல்பு:
        திரும்பு CallNextHookEx(வெற்று, nCode, wParam, lParam);
    }

    எனில் (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        எனில் (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } இல்லையெனில் {
        எனில் (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        எனில் (hookData->vkCode <= 0xFF && data->pre_hook_சாவி_state[hookData->vkCode]) {
            data->pre_hook_சாவி_state[hookData->vkCode] = 0;
            திரும்பு CallNextHookEx(வெற்று, nCode, wParam, lParam);
        }
    }

    திரும்பு 1;
}

நிலையான bool WIN_SwapButtons(HANDLE hDevice)
{
    எனில் (hDevice == வெற்று) {
        // Touchpad, already has buttons swapped
        திரும்பு false;
    }
    திரும்பு GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

நிலையான வெறுமை WIN_Handle_Raw_Mouse_உள்ளீடு(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    நிலையான கட்டமைப்பு {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_இடது_BUTTON_DOWN, SDL_BUTTON_இடது, true },
        { RI_MOUSE_இடது_BUTTON_UP, SDL_BUTTON_இடது, false },
        { RI_MOUSE_வலது_BUTTON_DOWN, SDL_BUTTON_வலது, true },
        { RI_MOUSE_வலது_BUTTON_UP, SDL_BUTTON_வலது, false },
        { RI_MOUSE_நடு_BUTTON_DOWN, SDL_BUTTON_நடு, true },
        { RI_MOUSE_நடு_BUTTON_UP, SDL_BUTTON_நடு, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    முழு dx = (முழு)rawmouse->lLastX;
    முழு dy = (முழு)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    எனில் (!data->raw_mouse_enabled) {
        திரும்பு;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    எனில் (!window) {
        திரும்பு;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    எனில் (!mouse) {
        திரும்பு;
    }

    எனில் (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        திரும்பு;
    }

    SDL_WindowData *windowdata = window->internal;

    எனில் (haveMotion && !windowdata->in_modal_loop) {
        எனில் (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (தசம)dx, (தசம)dy);
        } இல்லையெனில் {
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
            முழு w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            முழு h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            முழு x = raw_coordinates ? dx : (முழு)(((தசம)dx / 65535.0f) * w);
            முழு y = raw_coordinates ? dy : (முழு)(((தசம)dy / 65535.0f) * h);
            முழு relX, relY;

            /* Calculate relative motion */
            எனில் (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            எனில் (remote_desktop) {
                எனில் (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    நிலையான முழு wobble;
                    தசம floatX = (தசம)x / w;
                    தசம floatY = (தசம)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    எனில் (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        முழு warpX = rect.இடது + ((rect.வலது - rect.இடது) / 2) + wobble;
                        முழு warpY = rect.உச்சி + ((rect.bottom - rect.உச்சி) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        எனில் (wobble > 1) {
                            wobble = -1;
                        }
                    } இல்லையெனில் {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        மாறிலி முழு MAX_RELATIVE_MOTION = (h / 6);
                        எனில் (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (தசம)relX, (தசம)relY);
                        }
                    }
                }
            } இல்லையெனில் எனில் (mouse->pen_mouse_events) {
                மாறிலி முழு MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                எனில் (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } இல்லையெனில் {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (தசம)relX, (தசம)relY);
                }
            } இல்லையெனில் {
                முழு screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                முழு screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                எனில் (!data->raw_உள்ளீடு_fake_pen_id) {
                    data->raw_உள்ளீடு_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, வெற்று, (வெறுமை *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_உள்ளீடு_fake_pen_id, window, (தசம)(x + screen_x - window->x), (தசம)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    எனில் (haveButton) {
        க்கு (முழு i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            எனில் (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                எனில் (button == SDL_BUTTON_இடது) {
                    எனில் (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_வலது;
                    }
                } இல்லையெனில் எனில் (button == SDL_BUTTON_வலது) {
                    எனில் (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_இடது;
                    }
                }

                எனில் (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    எனில் (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    தொடர்;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        எனில் (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            தசம fAmount = (தசம)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } இல்லையெனில் எனில் (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            தசம fAmount = (தசம)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

நிலையான வெறுமை WIN_Handle_Raw_Keyboard_உள்ளீடு(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    எனில் (!data->raw_keyboard_enabled) {
        திரும்பு;
    }

    எனில் (rawkeyboard->Flags & RI_சாவி_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_சாவி_sequence = true;
        திரும்பு;
    }

    எனில் ((rawkeyboard->Flags & RI_சாவி_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        திரும்பு;
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_சாவி(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    எனில் (!rawkeyboard->MakeCode) {
        திரும்பு;
    }

    bool down;
    தேர்வு (rawkeyboard->Message) {
    நிலை WM_KEYDOWN:
    நிலை WM_SYSKEYDOWN:
        down = true;
        நிறுத்து;
    நிலை WM_KEYUP:
    நிலை WM_SYSKEYUP:
        down = false;
        நிறுத்து;
    இயல்பு:
        down = !(rawkeyboard->Flags & RI_சாவி_BREAK);
        நிறுத்து;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    எனில் (data->pending_E1_சாவி_sequence) {
        rawcode |= 0xE100;
        எனில் (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } இல்லையெனில் {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_சாவி_sequence = false;
    } இல்லையெனில் {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        எனில் (rawkeyboard->Flags & RI_சாவி_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    எனில் (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        எனில் ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_உள்ளீடு_active)) {
            திரும்பு;
        }
    }

    SDL_Send_Keyboard_சாவி(timestamp, keyboardID, rawcode, code, down);
}

வெறுமை WIN_Poll_Raw_உள்ளீடு(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, மொத்தம், total = 0;
    RAWINPUT *உள்ளீடு;
    Uint64 poll_finish;

    எனில் (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = அளவு(RAWINPUTHEADER);
        எனில் (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    உள்ளீடு = (RAWINPUT *)data->rawinput;
    க்கு (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)உள்ளீடு - data->rawinput);
        மொத்தம் = Get_Raw_உள்ளீடு_Buffer(உள்ளீடு, &size, அளவு(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        எனில் (மொத்தம் == 0 || மொத்தம் == (UINT)-1) {
            எனில் (!data->rawinput || (மொத்தம் == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                மாறிலி UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                எனில் (!rawinput) {
                    நிறுத்து;
                }
                உள்ளீடு = (RAWINPUT *)(rawinput + ((BYTE *)உள்ளீடு - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } இல்லையெனில் {
                நிறுத்து;
            }
        } இல்லையெனில் {
            total += மொத்தம்;

            // Advance input to the end of the buffer
            போது (மொத்தம்--) {
                உள்ளீடு = NEXTRAWINPUTBLOCK(உள்ளீடு);
            }
        }
    }

    எனில் (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        க்கு (i = 0, உள்ளீடு = (RAWINPUT *)data->rawinput; i < total; ++i, உள்ளீடு = NEXTRAWINPUTBLOCK(உள்ளீடு)) {
            எனில் (உள்ளீடு->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        முழு mouse_index = 0;
        க்கு (i = 0, உள்ளீடு = (RAWINPUT *)data->rawinput; i < total; ++i, உள்ளீடு = NEXTRAWINPUTBLOCK(உள்ளீடு)) {
            எனில் (உள்ளீடு->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)உள்ளீடு + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_உள்ளீடு(time, data, உள்ளீடு->header.hDevice, rawmouse);
            } இல்லையெனில் எனில் (உள்ளீடு->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)உள்ளீடு + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_உள்ளீடு(poll_finish, data, உள்ளீடு->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

நிலையான வெறுமை AddDeviceID(Uint32 deviceID, Uint32 **list, முழு *மொத்தம்)
{
    முழு new_மொத்தம் = (*மொத்தம் + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_மொத்தம் * அளவு(*new_list));
    எனில் (!new_list) {
        // Oh well, we'll drop this one
        திரும்பு;
    }
    new_list[new_மொத்தம் - 1] = deviceID;

    *மொத்தம் = new_மொத்தம்;
    *list = new_list;
}

நிலையான bool HasDeviceID(Uint32 deviceID, மாறிலி Uint32 *list, முழு மொத்தம்)
{
    க்கு (முழு i = 0; i < மொத்தம்; ++i) {
        எனில் (deviceID == list[i]) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

நிலையான எழுத்து *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, மாறிலி எழுத்து *instance, Uint16 vendor, Uint16 product, மாறிலி எழுத்து *default_name, bool hid_loaded)
{
    எழுத்து *vendor_name = வெற்று;
    எழுத்து *product_name = வெற்று;
    எழுத்து *name = வெற்று;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    எனில் (hid_loaded) {
        எழுத்து devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = அளவு(devName) - 1;
        UINT len = Get_Raw_உள்ளீடு_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        எனில் (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, வெற்று, OPEN_EXISTING, 0, வெற்று);
            எனில் (hFile != INVALID_HANDLE_மதிப்பு) {
                SDL_HidD_GetManufacturerString(hFile, vend, அளவு(vend));
                SDL_HidD_GetProductString(hFile, prod, அளவு(prod));
                CloseHandle(hFile);
            }
        }
    }

    எனில் (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    எனில் (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } இல்லையெனில் {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = அளவு(data);
        க்கு (DWORD i = 0;; ++i) {
            எனில் (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                எனில் (GetLastError() == ERROR_NO_MORE_பொருட்கள்) {
                    நிறுத்து;
                } இல்லையெனில் {
                    தொடர்;
                }
            }

            எழுத்து DeviceInstanceId[64];
            எனில் (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, அளவு(DeviceInstanceId), வெற்று))
                தொடர்;

            எனில் (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                எனில் (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, வெற்று, (PBYTE)prod, அளவு(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= அளவு(*prod);
                    எனில் (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    எனில் (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } இல்லையெனில் {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                நிறுத்து;
            }
        }
    }

    எனில் (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    திரும்பு name;
}

வெறுமை WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = வெற்று;
    UINT raw_device_மொத்தம் = 0;
    முழு old_keyboard_மொத்தம் = 0;
    SDL_KeyboardID *old_keyboards = வெற்று;
    முழு new_keyboard_மொத்தம் = 0;
    SDL_KeyboardID *new_keyboards = வெற்று;
    முழு old_mouse_மொத்தம் = 0;
    SDL_MouseID *old_mice = வெற்று;
    முழு new_mouse_மொத்தம் = 0;
    SDL_MouseID *new_mice = வெற்று;

    எனில் (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        திரும்பு;
    }

    எனில் ((Get_Raw_உள்ளீடு_Device_List(வெற்று, &raw_device_மொத்தம், அளவு(RAWINPUTDEVICELIST)) == -1) || (!raw_device_மொத்தம்)) {
        திரும்பு; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(அளவு(RAWINPUTDEVICELIST) * raw_device_மொத்தம்);
    எனில் (!raw_devices) {
        திரும்பு; // oh well.
    }

    raw_device_மொத்தம் = Get_Raw_உள்ளீடு_Device_List(raw_devices, &raw_device_மொத்தம், அளவு(RAWINPUTDEVICELIST));
    எனில் (raw_device_மொத்தம் == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = வெற்று;
        திரும்பு; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(வெற்று, வெற்று, வெற்று, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_மொத்தம்);
    old_mice = SDL_GetMice(&old_mouse_மொத்தம்);

    க்கு (UINT i = 0; i < raw_device_மொத்தம்; i++) {
        RID_DEVICE_INFO rdi;
        எழுத்து devName[MAX_PATH] = { 0 };
        UINT rdiSize = அளவு(rdi);
        UINT nameSize = SDL_arraysize(devName);
        முழு vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        எழுத்து *instance, *ptr, *name;

        எனில் (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            தொடர்;
        }

        rdi.cbSize = அளவு(rdi);
        எனில் (Get_Raw_உள்ளீடு_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_உள்ளீடு_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            தொடர்;
        }

        // Extract the device instance
        instance = devName;
        போது (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        க்கு (ptr = instance; *ptr; ++ptr) {
            எனில் (*ptr == '#') {
                *ptr = '\\';
            }
            எனில் (*ptr == '{') {
                எனில் (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                நிறுத்து;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        தேர்வு (dwType) {
        நிலை RIM_TYPEKEYBOARD:
            எனில் (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_எண்_Of_சாவிகள்_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_மொத்தம்);
                எனில் (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_மொத்தம்)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            நிறுத்து;
        நிலை RIM_TYPEMOUSE:
            எனில் (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_மொத்தம்);
                எனில் (!HasDeviceID(mouseID, old_mice, old_mouse_மொத்தம்)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }
    }

    க்கு (முழு i = old_keyboard_மொத்தம்; i--;) {
        எனில் (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_மொத்தம்)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    க்கு (முழு i = old_mouse_மொத்தம்; i--;) {
        எனில் (!HasDeviceID(old_mice[i], new_mice, new_mouse_மொத்தம்)) {
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
நிலையான bool Skip_Alt_Gr_இடது_Control(WPARAM wParam, LPARAM lParam)
{
    எனில் (wParam != VK_CONTROL) {
        திரும்பு false;
    }

    // Is this an extended key (i.e. right key)?
    எனில் (lParam & 0x01000000) {
        திரும்பு false;
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    செய்தி_2 next_செய்தி;
    DWORD செய்தி_time = GetMessageTime();
    எனில் (PeekMessage(&next_செய்தி, வெற்று, 0, 0, PM_NOREMOVE)) {
        எனில் (next_செய்தி.message == WM_KEYDOWN ||
            next_செய்தி.message == WM_SYSKEYDOWN) {
            எனில் (next_செய்தி.wParam == VK_MENU && (next_செய்தி.lParam & 0x01000000) && next_செய்தி.time == செய்தி_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                திரும்பு true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    திரும்பு false;
}

நிலையான bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *செய்தி, WPARAM *wParam, LPARAM *lParam)
{
    செய்தி_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *செய்தி;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    எனில் (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *செய்தி = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        திரும்பு true;
    }
    திரும்பு false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT செய்தி, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    எனில் (!data) {
        திரும்பு CallWindowProc(DefWindowProc, hwnd, செய்தி, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        எழுத்து message[1024];
        எனில் (செய்தி > MAX_WMMSG) {
            SDL_snprintf(message, அளவு(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, செய்தி, wParam, lParam);
        } இல்லையெனில் {
            SDL_snprintf(message, அளவு(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[செய்தி], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    எனில் (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        எனில் (!DispatchModalLoopMessageHook(&hwnd, &செய்தி, &wParam, &lParam)) {
            திரும்பு 0;
        }
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (WIN_HandleIMEMessage(hwnd, செய்தி, wParam, &lParam, data->videodata)) {
        திரும்பு 0;
    }
#endif

    தேர்வு (செய்தி) {

    நிலை WM_SHOWWINDOW:
    {
        எனில் (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } இல்லையெனில் {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } நிறுத்து;

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    நிலை WM_NCACTIVATE:
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
        எனில் (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } நிறுத்து;

    நிலை WM_NCUAHDRAWCAPTION:
    நிலை WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        எனில் (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } நிறுத்து;

    நிலை WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        மாறிலி DWORD செய்தி_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(செய்தி_Pos), GET_Y_LPARAM(செய்தி_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } நிறுத்து;

    நிலை WM_MOUSEACTIVATE:
    {
        எனில் (SDL_WINDOW_IS_POPUP(data->window)) {
            திரும்பு MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        போது (parent) {
            எனில் ((parent->flags & SDL_WINDOW_உள்ளீடு_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                திரும்பு MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } நிறுத்து;

    நிலை WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        மாறிலி DWORD செய்தி_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(செய்தி_Pos), GET_Y_LPARAM(செய்தி_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } நிறுத்து;

    நிலை WM_KILLFOCUS:
    நிலை WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        மாறிலி DWORD செய்தி_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(செய்தி_Pos), GET_Y_LPARAM(செய்தி_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } நிறுத்து;

    நிலை WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        மாறிலி UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_உள்ளீடு_TYPE pointer_type = PT_POINTER;
        எனில் (!data->videodata->GetPointerType) {
            நிறுத்து;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } இல்லையெனில் எனில் (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            நிறுத்து;  // oh well.
        } இல்லையெனில் எனில் (pointer_type != PT_PEN) {
            நிறுத்து;  // we only care about pens here.
        }

        வெறுமை *hpointer = (வெறுமை *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        மாறிலி SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        எனில் (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } இல்லையெனில் {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.இலக்கம்_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), வெற்று, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } நிறுத்து;

    நிலை WM_POINTERCAPTURECHANGED:
    நிலை WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        மாறிலி UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_உள்ளீடு_TYPE pointer_type = PT_POINTER;
        எனில் (!data->videodata->GetPointerType) {
            நிறுத்து;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } இல்லையெனில் எனில் (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            நிறுத்து;  // oh well.
        } இல்லையெனில் எனில் (pointer_type != PT_PEN) {
            நிறுத்து;  // we only care about pens here.
        }

        வெறுமை *hpointer = (வெறுமை *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        மாறிலி SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        எனில் (pen == 0) {
            நிறுத்து;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        எனில் ((செய்தி == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } நிறுத்து;

    நிலை WM_POINTERDOWN:
    நிலை WM_POINTERUP:
    நிலை WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        மாறிலி UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_உள்ளீடு_TYPE pointer_type = PT_POINTER;
        எனில் (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            நிறுத்து;  // oh well.
        } இல்லையெனில் எனில் ((செய்தி == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            நிறுத்து;
        } இல்லையெனில் எனில் (pointer_type != PT_PEN) {
            நிறுத்து; // we only care about pens here.
        }

        வெறுமை *hpointer = (வெறுமை *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        மாறிலி SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        எனில் (pen == 0) {
            நிறுத்து;  // not a pen, or not a pen we already knew about.
        } இல்லையெனில் எனில் (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            நிறுத்து;  // oh well.
        }

        மாறிலி Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        மாறிலி bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        எனில் (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        மாறிலி POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        தசம fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        எனில் (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (தசம) position.x;
            fy = (தசம) position.y;
        } இல்லையெனில் {
            முழு ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            மாறிலி SDL_FPoint window_pos = { (தசம) ix, (தசம) iy };

            மாறிலி தசம facX = pointer_info->ptHimetricLocationRaw.x / (தசம) (tablet_bounds.வலது );
            மாறிலி தசம facY = pointer_info->ptHimetricLocationRaw.y / (தசம) (tablet_bounds.bottom);

            மாறிலி தசம w = tablet_mapping.வலது  - tablet_mapping.இடது;
            மாறிலி தசம h = tablet_mapping.bottom - tablet_mapping.உச்சி;

            fx = (tablet_mapping.இடது + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.உச்சி  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        எனில் (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((தசம) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        எனில் (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((தசம) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        எனில் (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((தசம) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        எனில் (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((தசம) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        எனில் (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } நிறுத்து;

    நிலை WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        எனில் (window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            எனில் (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        எனில் (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = அளவு(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            எனில் (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        எனில் (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            எனில் (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (தசம)GET_X_LPARAM(lParam), (தசம)GET_Y_LPARAM(lParam));
            }
        }

    } நிறுத்து;

    நிலை WM_LBUTTONUP:
    நிலை WM_RBUTTONUP:
    நிலை WM_MBUTTONUP:
    நிலை WM_XBUTTONUP:
    நிலை WM_LBUTTONDOWN:
    நிலை WM_LBUTTONDBLCLK:
    நிலை WM_RBUTTONDOWN:
    நிலை WM_RBUTTONDBLCLK:
    நிலை WM_MBUTTONDOWN:
    நிலை WM_MBUTTONDBLCLK:
    நிலை WM_XBUTTONDOWN:
    நிலை WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        எனில் (!data->videodata->raw_mouse_enabled) {
            எனில் (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } நிறுத்து;

#எனில் 0   // We handle raw input all at once instead of using a syscall for each mouse event
    நிலை WM_உள்ளீடு:
    {
        HRAWINPUT h_Raw_உள்ளீடு = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = அளவு(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        எனில் (data->window != SDL_GetKeyboardFocus()) {
            நிறுத்து;
        }

        Get_Raw_உள்ளீடு_Data(h_Raw_உள்ளீடு, RID_உள்ளீடு, &inp, &size, அளவு(RAWINPUTHEADER));
        எனில் (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_உள்ளீடு(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } இல்லையெனில் எனில் (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_உள்ளீடு(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } நிறுத்து;
#endif

    நிலை WM_MOUSEWHEEL:
    நிலை WM_MOUSEHWHEEL:
    {
        எனில் (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            தசம fAmount = (தசம)amount / WHEEL_DELTA;
            எனில் (செய்தி == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } இல்லையெனில் {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } நிறுத்து;

    நிலை WM_MOUSELEAVE:
        எனில் (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            எனில் (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                எனில் (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (தசம)cursorPos.x, (தசம)cursorPos.y);
                } இல்லையெனில் {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    எனில் (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (தசம)cursorPos.x, (தசம)cursorPos.y);
                    } இல்லையெனில் { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (தசம)cursorPos.x, (தசம)cursorPos.y);
                    }
                }
            }

            எனில் (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(வெற்று);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        நிறுத்து;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    நிலை WM_KEYDOWN:
    நிலை WM_SYSKEYDOWN:
    {
        எனில் (Skip_Alt_Gr_இடது_Control(wParam, lParam)) {
            returnCode = 0;
            நிறுத்து;
        }

        bool virtual_சாவி = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_சாவி);

        // Detect relevant keyboard shortcuts
        எனில் (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            எனில் (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        எனில் (virtual_சாவி || !data->videodata->raw_keyboard_enabled || data->window->text_உள்ளீடு_active) {
            SDL_Send_Keyboard_சாவி(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        நிறுத்து;

    நிலை WM_SYSKEYUP:
    நிலை WM_KEYUP:
    {
        எனில் (Skip_Alt_Gr_இடது_Control(wParam, lParam)) {
            returnCode = 0;
            நிறுத்து;
        }

        bool virtual_சாவி = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_சாவி);
        மாறிலி bool *keyboardState = SDL_GetKeyboardState(வெற்று);

        எனில் (virtual_சாவி || !data->videodata->raw_keyboard_enabled || data->window->text_உள்ளீடு_active) {
            எனில் (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_சாவி(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_சாவி(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        நிறுத்து;

    நிலை WM_UNICHAR:
        எனில் (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } இல்லையெனில் {
            எனில் (SDL_Text_உள்ளீடு_Active(data->window)) {
                எழுத்து text[5];
                எழுத்து *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        நிறுத்து;

    நிலை WM_CHAR:
        எனில் (SDL_Text_உள்ளீடு_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            எனில் (IS_உயர்வு_SURROGATE(wParam)) {
                data->உயர்வு_surrogate = (WCHAR)wParam;
            } இல்லையெனில் {
                WCHAR utf16[3];

                utf16[0] = data->உயர்வு_surrogate ? data->உயர்வு_surrogate : (WCHAR)wParam;
                utf16[1] = data->உயர்வு_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                எழுத்து utf8[5];
                முழு result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, அளவு(utf8), வெற்று, வெற்று);
                எனில் (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->உயர்வு_surrogate = L'\0';
            }
        } இல்லையெனில் {
            data->உயர்வு_surrogate = L'\0';
        }

        returnCode = 0;
        நிறுத்து;

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    நிலை WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        நிறுத்து;
#endif // WM_INPUTLANGCHANGE

    நிலை WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        எனில் (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } நிறுத்து;

    நிலை WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } நிறுத்து;

#ifdef WM_GETMINMAXINFO
    நிலை WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        முழு x, y;
        முழு w, h;
        முழு min_w, min_h;
        முழு max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        எனில் (data->expected_resize) {
            நிறுத்து;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.இடது;
        y = size.உச்சி;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        எனில் (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } இல்லையெனில் {
            constrain_max_size = FALSE;
        }

        எனில் (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.உச்சி = 0;
            size.இடது = 0;
            size.bottom = h;
            size.வலது = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.வலது - size.இடது;
            h = size.bottom - size.உச்சி;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        எனில் (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            எனில் (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                முழு screenW = GetSystemMetrics(SM_CXSCREEN);
                முழு screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            எனில் (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } இல்லையெனில் {
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
        நிறுத்து;
#endif // WM_GETMINMAXINFO

    நிலை WM_WINDOWPOSCHANGING:

        எனில் (data->expected_resize) {
            returnCode = 0;
        } இல்லையெனில் எனில் (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            எனில் (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        நிறுத்து;

    நிலை WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        மாறிலி SDL_DisplayID original_displayID = data->window->displayID;
        மாறிலி WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        முழு x, y;
        முழு w, h;

        எனில் (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        எனில் (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } இல்லையெனில் எனில் (zoomed) {
            எனில் (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } இல்லையெனில் எனில் (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            எனில் (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        எனில் (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        எனில் (iconic) {
            நிறுத்து;
        }

        எனில் (data->initializing) {
            நிறுத்து;
        }

        எனில் (!data->disable_move_size_events) {
            எனில் (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.இடது;
                y = rect.உச்சி;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            எனில் (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.வலது;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        எனில் (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        க்கு (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            எனில் (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } நிறுத்து;

    நிலை WM_ENTERSIZEMOVE:
    நிலை WM_ENTERMENULOOP:
    {
        எனில் (g_WindowsMessageHook) {
            எனில் (!DispatchModalLoopMessageHook(&hwnd, &செய்தி, &wParam, &lParam)) {
                திரும்பு 0;
            }
        }

        ++data->in_modal_loop;
        எனில் (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.வலது - rect.இடது;
            data->last_modal_height = rect.bottom - rect.உச்சி;

            data->initial_size_rect.இடது = data->window->x;
            data->initial_size_rect.வலது = data->window->x + data->window->w;
            data->initial_size_rect.உச்சி = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, வெற்று);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } நிறுத்து;

    நிலை WM_TIMER:
    {
        எனில் (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#எனில் 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            எனில் (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            திரும்பு 0;
        }
    } நிறுத்து;

    நிலை WM_EXITSIZEMOVE:
    நிலை WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        எனில் (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } நிறுத்து;

    நிலை WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            தசம new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            எனில் (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                நிறுத்து;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            எனில் (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != வெற்று, GetWindowExStyle(hwnd))) {
                நிறுத்து;
            }

            clientDragRect.இடது -= rc.இடது;
            clientDragRect.உச்சி -= rc.உச்சி;
            clientDragRect.வலது -= rc.வலது;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.வலது - clientDragRect.இடது;
            h = clientDragRect.bottom - clientDragRect.உச்சி;
            new_aspect = w / (தசம)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            எனில் (lock_aspect_ratio) {
                தேர்வு (edge) {
                நிலை WMSZ_இடது:
                நிலை WMSZ_வலது:
                    h = (முழு)SDL_roundf(w / data->window->max_aspect);
                    நிறுத்து;
                இயல்பு:
                    // resizing via corners or top or bottom
                    w = (முழு)SDL_roundf(h * data->window->max_aspect);
                    நிறுத்து;
                }
            } இல்லையெனில் {
                தேர்வு (edge) {
                நிலை WMSZ_இடது:
                நிலை WMSZ_வலது:
                    எனில் (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (முழு)SDL_roundf(h * data->window->max_aspect);
                    } இல்லையெனில் எனில் (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (முழு)SDL_roundf(h * data->window->min_aspect);
                    }
                    நிறுத்து;
                நிலை WMSZ_உச்சி:
                நிலை WMSZ_BOTTOM:
                    எனில் (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (முழு)SDL_roundf(w / data->window->min_aspect);
                    } இல்லையெனில் எனில் (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (முழு)SDL_roundf(w / data->window->max_aspect);
                    }
                    நிறுத்து;

                இயல்பு:
                    // resizing via corners
                    எனில் (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (முழு)SDL_roundf(h * data->window->max_aspect);
                    } இல்லையெனில் எனில் (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (முழு)SDL_roundf(w / data->window->min_aspect);
                    }
                    நிறுத்து;
                }
            }

            தேர்வு (edge) {
            நிலை WMSZ_இடது:
                clientDragRect.இடது = clientDragRect.வலது - w;
                எனில் (lock_aspect_ratio) {
                    clientDragRect.உச்சி = (data->initial_size_rect.bottom + data->initial_size_rect.உச்சி - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.உச்சி;
                நிறுத்து;
            நிலை WMSZ_BOTTOMLEFT:
                clientDragRect.இடது = clientDragRect.வலது - w;
                clientDragRect.bottom = h + clientDragRect.உச்சி;
                நிறுத்து;
            நிலை WMSZ_வலது:
                clientDragRect.வலது = w + clientDragRect.இடது;
                எனில் (lock_aspect_ratio) {
                    clientDragRect.உச்சி = (data->initial_size_rect.bottom + data->initial_size_rect.உச்சி - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.உச்சி;
                நிறுத்து;
            நிலை WMSZ_TOPRIGHT:
                clientDragRect.வலது = w + clientDragRect.இடது;
                clientDragRect.உச்சி = clientDragRect.bottom - h;
                நிறுத்து;
            நிலை WMSZ_உச்சி:
                எனில் (lock_aspect_ratio) {
                    clientDragRect.இடது = (data->initial_size_rect.வலது + data->initial_size_rect.இடது - w) / 2;
                }
                clientDragRect.வலது = w + clientDragRect.இடது;
                clientDragRect.உச்சி = clientDragRect.bottom - h;
                நிறுத்து;
            நிலை WMSZ_TOPLEFT:
                clientDragRect.இடது = clientDragRect.வலது - w;
                clientDragRect.உச்சி = clientDragRect.bottom - h;
                நிறுத்து;
            நிலை WMSZ_BOTTOM:
                எனில் (lock_aspect_ratio) {
                    clientDragRect.இடது = (data->initial_size_rect.வலது + data->initial_size_rect.இடது - w) / 2;
                }
                clientDragRect.வலது = w + clientDragRect.இடது;
                clientDragRect.bottom = h + clientDragRect.உச்சி;
                நிறுத்து;
            நிலை WMSZ_BOTTOMRIGHT:
                clientDragRect.வலது = w + clientDragRect.இடது;
                clientDragRect.bottom = h + clientDragRect.உச்சி;
                நிறுத்து;
            }

            // convert the client rect to a window rect
            எனில் (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != வெற்று, GetWindowExStyle(hwnd))) {
                நிறுத்து;
            }

            *dragRect = clientDragRect;
        }
        நிறுத்து;

    நிலை WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        எனில் (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } இல்லையெனில் எனில் (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(வெற்று);
            returnCode = TRUE;
        }
    } நிறுத்து;

        // We were occluded, refresh our display
    நிலை WM_PAINT:
    {
        RECT rect;
        எனில் (GetUpdateRect(hwnd, &rect, FALSE)) {
            மாறிலி LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            எனில் (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, வெற்று);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        நிறுத்து;

        // We'll do our own drawing, prevent flicker
    நிலை WM_ERASEBKGND:
        எனில் (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        திரும்பு 1;

    நிலை WM_SYSCOMMAND:
    {
        எனில் (!g_WindowsEnableMenuMnemonics) {
            எனில் ((wParam & 0xFFF0) == SC_KEYMENU) {
                திரும்பு 0;
            }
        }

#எனில் defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        எனில் ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            எனில் (SDL_GetVideoDevice()->suspend_screensaver) {
                திரும்பு 0;
            }
        }
#endif // System has screensaver support
    } நிறுத்து;

    நிலை WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        நிறுத்து;

    நிலை WM_TOUCH:
        எனில் (data->videodata->Get_Touch_உள்ளீடு_Info && data->videodata->Close_Touch_உள்ளீடு_Handle) {
            UINT i, இலக்கம்_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, இலக்கம்_inputs, &isstack);
            எனில் (inputs && data->videodata->Get_Touch_உள்ளீடு_Info((HTOUCHINPUT)lParam, இலக்கம்_inputs, inputs, அளவு(TOUCHINPUT))) {
                RECT rect;
                தசம x, y;

                எனில் (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    எனில் (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    நிறுத்து;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.உச்சி *= 100;
                rect.இடது *= 100;
                rect.bottom *= 100;
                rect.வலது *= 100;

                க்கு (i = 0; i < இலக்கம்_inputs; ++i) {
                    PTOUCHINPUT உள்ளீடு = &inputs[i];
                    மாறிலி முழு w = (rect.வலது - rect.இடது);
                    மாறிலி முழு h = (rect.bottom - rect.உச்சி);

                    மாறிலி SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)உள்ளீடு->hSource);
                    மாறிலி SDL_FingerID fingerId = (உள்ளீடு->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    எனில் (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (உள்ளீடு->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        தொடர்;
                    }

                    // Get the normalized coordinates for the window
                    எனில் (w <= 1) {
                        x = 0.5f;
                    } இல்லையெனில் {
                        x = (தசம)(உள்ளீடு->x - rect.இடது) / (w - 1);
                    }
                    எனில் (h <= 1) {
                        y = 0.5f;
                    } இல்லையெனில் {
                        y = (தசம)(உள்ளீடு->y - rect.உச்சி) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    எனில் (உள்ளீடு->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    எனில் (உள்ளீடு->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    எனில் (உள்ளீடு->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_உள்ளீடு_Handle((HTOUCHINPUT)lParam);
            திரும்பு 0;
        }
        நிறுத்து;

#ifdef HAVE_TPCSHRD_H

    நிலை WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        திரும்பு TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    நிலை WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT மொத்தம் = DragQueryFile(drop, 0xFFFFFFFF, வெற்று, 0);
        க்கு (i = 0; i < மொத்தம்; ++i) {
            UINT size = DragQueryFile(drop, i, வெற்று, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(அளவு(TCHAR) * size);
            எனில் (buffer) {
                எனில் (DragQueryFile(drop, i, buffer, size)) {
                    எழுத்து *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, வெற்று, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        திரும்பு 0;
    }

    நிலை WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } நிறுத்து;

    நிலை WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        எனில் (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            எனில் (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                எனில் (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    மாறிலி POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                எனில் (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = அளவு(info);
                    எனில் (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } இல்லையெனில் எனில் (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                முழு w, h;
                எனில் (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } இல்லையெனில் {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].வலது = params->rgrc[0].இடது + w;
                params->rgrc[0].bottom = params->rgrc[0].உச்சி + h;
            }
            திரும்பு 0;
        }
    } நிறுத்து;

    நிலை WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        எனில் (window->flags & SDL_WINDOW_TOOLTIP) {
            திரும்பு HTTRANSPARENT;
        }

        எனில் (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            எனில் (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                தேர்வு (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        திரும்பு ret;                                                        \
    }
                நிலை SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(வெற்று, வெற்று);
                    எனில் (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        திரும்பு HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                நிலை SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                நிலை SDL_HITTEST_RESIZE_உச்சி:
                    POST_HIT_TEST(HTTOP);
                நிலை SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                நிலை SDL_HITTEST_RESIZE_வலது:
                    POST_HIT_TEST(HTRIGHT);
                நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                நிலை SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                நிலை SDL_HITTEST_RESIZE_இடது:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                நிலை SDL_HITTEST_NORMAL:
                    திரும்பு HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } நிறுத்து;

    நிலை WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        எனில் (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            மாறிலி முழு nextDPI = (முழு)wParam;
            மாறிலி முழு prevDPI = (முழு)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            முழு frame_w, frame_h;
            முழு query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                எனில் (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.இடது + rect.வலது;
                frame_h = -rect.உச்சி + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.வலது = query_client_w_win;
                rect.bottom = query_client_h_win;

                எனில் (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.வலது - rect.இடது;
                sizeInOut->cy = rect.bottom - rect.உச்சி;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            திரும்பு TRUE;
        }
        நிறுத்து;

    நிலை WM_DPICHANGED:
        // Windows 8.1+
        {
            மாறிலி முழு newDPI = HIWORD(wParam);
            RECT *மாறிலி suggestedRect = (RECT *)lParam;
            முழு w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->இடது, suggestedRect->உச்சி, suggestedRect->வலது - suggestedRect->இடது, suggestedRect->bottom - suggestedRect->உச்சி);
#endif

            எனில் (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                திரும்பு 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.வலது = data->window->w;
                rect.bottom = data->window->h;

                எனில் (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.வலது - rect.இடது;
                h = rect.bottom - rect.உச்சி;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->இடது, suggestedRect->உச்சி, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         வெற்று,
                         suggestedRect->இடது,
                         suggestedRect->உச்சி,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            திரும்பு 0;
        }

    நிலை WM_SETTINGCHANGE:
        எனில் (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        எனில் (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        எனில் (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        நிறுத்து;
#இல்லையெனில்
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    நிலை WM_SIZE:
    {
        RECT rect;
        முழு w, h;

        எனில் (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.வலது;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } நிறுத்து;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    இயல்பு:
        நிறுத்து;
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (செய்தி && செய்தி == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    எனில் (data->wndproc) {
        திரும்பு CallWindowProc(data->wndproc, hwnd, செய்தி, wParam, lParam);
    } இல்லையெனில் எனில் (returnCode >= 0) {
        திரும்பு returnCode;
    } இல்லையெனில் {
        திரும்பு CallWindowProc(DefWindowProc, hwnd, செய்தி, wParam, lParam);
    }
}

முழு WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    எனில் (g_WindowsEnableMessageLoop) {
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = செய்தி_Wait_For_Multiple_Objects(0, வெற்று, FALSE, timeout, QS_ALLINPUT);
        எனில் (ret == WAIT_OBJECT_0) {
            திரும்பு 1;
        } இல்லையெனில் {
            திரும்பு 0;
        }
#இல்லையெனில்
        // MsgWaitForMultipleObjects is desktop-only.
        செய்தி_2 செய்தி;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        எனில் (timeoutNS > 0) {
            timer_id = SetTimer(வெற்று, 0, (UINT)SDL_NS_TO_MS(timeoutNS), வெற்று);
            message_result = GetMessage(&செய்தி, 0, 0, 0);
            KillTimer(வெற்று, timer_id);
        } இல்லையெனில் எனில் (timeoutNS == 0) {
            message_result = PeekMessage(&செய்தி, வெற்று, 0, 0, PM_REMOVE);
        } இல்லையெனில் {
            message_result = GetMessage(&செய்தி, 0, 0, 0);
        }
        எனில் (message_result) {
            எனில் (செய்தி.message == WM_TIMER && !செய்தி.hwnd && செய்தி.wParam == timer_id) {
                திரும்பு 0;
            }
            எனில் (g_WindowsMessageHook) {
                எனில் (!g_WindowsMessageHook(g_WindowsMessageHookData, &செய்தி)) {
                    திரும்பு 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&செய்தி);
            DispatchMessage(&செய்தி);
            திரும்பு 1;
        } இல்லையெனில் {
            திரும்பு 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } இல்லையெனில் {
        // Fail the wait so the caller falls back to polling
        திரும்பு -1;
    }
}

வெறுமை WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
வெறுமை WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    செய்தி_2 செய்தி;

    எனில் (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        போது (PeekMessage(&செய்தி, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(செய்தி.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&செய்தி);
            DispatchMessage(&செய்தி);
        }

        SDL_processing_messages = false;
    }
}

வெறுமை WIN_PumpEvents(SDL_VideoDevice *_this)
{
    செய்தி_2 செய்தி;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(தள்ளு)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_மொத்தம்() + 1;
#ifdef _MSC_VER
#pragma warning(எடு)
#endif
    முழு new_messages = 0;

    எனில் (_this->internal->gameinput_context) {
        WIN_Update_Game_உள்ளீடு(_this);
    }

    எனில் (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        போது (PeekMessage(&செய்தி, வெற்று, 0, 0, PM_REMOVE)) {
            எனில் (g_WindowsMessageHook) {
                எனில் (!g_WindowsMessageHook(g_WindowsMessageHookData, &செய்தி)) {
                    தொடர்;
                }
            }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            எனில் (செய்தி.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                எனில் (!SDL_TICKS_PASSED(செய்தி.time, (SDL_last_warp_time + 1))) {
                    தொடர்;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(செய்தி.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&செய்தி);
            DispatchMessage(&செய்தி);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            எனில் (SDL_TICKS_PASSED(செய்தி.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                மாறிலி முழு MAX_NEW_MESSAGES = 3;
                ++new_messages;
                எனில் (new_messages > MAX_NEW_MESSAGES) {
                    நிறுத்து;
                }
            }
        }

        SDL_processing_messages = false;
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    மாறிலி bool *keystate = SDL_GetKeyboardState(வெற்று);
    எனில் (keystate[SDL_SCANCODE_LSHIFT] && !(Get_சாவி_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    எனில் (keystate[SDL_SCANCODE_RSHIFT] && !(Get_சாவி_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    எனில் (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        எனில் (keystate[SDL_SCANCODE_LGUI] && !(Get_சாவி_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        எனில் (keystate[SDL_SCANCODE_RGUI] && !(Get_சாவி_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    எனில் (_this) {
        SDL_Window *window = _this->windows;
        போது (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            எனில் (data) {
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
            எனில் (refresh_clipcursor) {
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
    எனில் (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        எனில் (!data->mouse_tracked) {
            POINT cursorPos;

            எனில் (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (தசம)cursorPos.x, (தசம)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_இடது : SDL_BUTTON_வலது,
                                    (Get_Async_சாவி_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_வலது : SDL_BUTTON_இடது,
                                    (Get_Async_சாவி_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_நடு,
                                    (Get_Async_சாவி_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_சாவி_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_சாவி_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

நிலையான முழு app_registered = 0;
LPTSTR SDL_Appname = வெற்று;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = வெற்று;

நிலையான வெறுமை WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    எனில் (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = வெற்று;
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
நிலையான BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (வெறுமை)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    திரும்பு FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(மாறிலி எழுத்து *name, Uint32 style, வெறுமை *hInst)
{
    WNDCLASSEX wcex;
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    மாறிலி எழுத்து *hint;
#endif

    // Only do this once...
    எனில் (app_registered) {
        ++app_registered;
        திரும்பு true;
    }
    SDL_assert(!SDL_Appname);
    எனில் (!name) {
        name = "SDL_app";
#எனில் defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(வெற்று);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = அளவு(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    எனில் (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        எனில் (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } இல்லையெனில் {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    எனில் (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        திரும்பு SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    திரும்பு true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
வெறுமை SDL_UnregisterApp(வெறுமை)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    எனில் (!app_registered) {
        திரும்பு;
    }
    --app_registered;
    எனில் (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = வெற்று;
        wcex.hIconSm = வெற்று;
        // Check for any registered window classes.
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        எனில் (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
