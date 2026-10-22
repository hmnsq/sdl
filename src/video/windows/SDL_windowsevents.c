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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"
#അന്തര്ഭാവ "../../events/scancodes_windows.h"
#അന്തര്ഭാവ "../../main/SDL_main_callbacks.h"
#അന്തര്ഭാവ "../../core/windows/SDL_hid.h"

// Dropfile support
#അന്തര്ഭാവ <shellapi.h>

// Device names
#അന്തര്ഭാവ <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#അന്തര്ഭാവ <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ifdef HAVE_TPCSHRD_H
#അന്തര്ഭാവ <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#എങ്കിൽ 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ "wmmsg.h"
#endif

#എങ്കിൽ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#അന്തര്ഭാവ <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#അന്തര്ഭാവ "../../core/gdk/SDL_gdk.h"
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
#ifndef WM_നിവേശം
#define WM_നിവേശം 0x00ff
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

#ifndef IS_മുകളിലെ_SURROGATE
#define IS_മുകളിലെ_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#endif

#ifndef USER_TIMER_MINIMUM
#define USER_TIMER_MINIMUM 0x0000000A
#endif

// Used to compare Windows message timestamps
#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#ifdef _WIN64
തരനിർവചനം Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

സ്ഥിതം bool SDL_processing_messages;
സ്ഥിതം DWORD message_tick;
സ്ഥിതം Uint64 timestamp_offset;

സ്ഥിതം ശൂന്യം WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

സ്ഥിതം Uint64 WIN_GetEventTimestamp(ശൂന്യം)
{
    സ്ഥിരം Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    എങ്കിൽ (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        തിരികെ 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    എങ്കിൽ (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } അല്ലെങ്കിൽ എങ്കിൽ ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } അല്ലെങ്കിൽ എങ്കിൽ (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    തിരികെ timestamp;
}

// A message hook called before TranslateMessage()
സ്ഥിതം SDL_WindowsMessageHook g_WindowsMessageHook = ശൂന്യ;
സ്ഥിതം ശൂന്യം *g_WindowsMessageHookData = ശൂന്യ;

ശൂന്യം SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ശൂന്യം *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

സ്ഥിതം SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_താക്കോൽ)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 താക്കോൽ_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(താക്കോൽ_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_താക്കോൽ = (scanCode == 0);

    എങ്കിൽ (scanCode != 0) {
        എങ്കിൽ ((താക്കോൽ_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } അല്ലെങ്കിൽ എങ്കിൽ (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } അല്ലെങ്കിൽ {
        Uint16 vkCode = LOWORD(wParam);

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_താക്കോൽ(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        എങ്കിൽ (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    തിരികെ code;
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
സ്ഥിതം bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    തിരികെ !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

സ്ഥിതം ശൂന്യം WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    എങ്കിൽ (bSwapButtons) {
        എങ്കിൽ (button == SDL_BUTTON_ഇടത്) {
            button = SDL_BUTTON_വലത്;
        } അല്ലെങ്കിൽ എങ്കിൽ (button == SDL_BUTTON_വലത്) {
            button = SDL_BUTTON_ഇടത്;
        }
    }

    എങ്കിൽ (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        എങ്കിൽ (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        തിരികെ;
    }

    എങ്കിൽ (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } അല്ലെങ്കിൽ എങ്കിൽ (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
സ്ഥിതം ശൂന്യം WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    എങ്കിൽ (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(ശൂന്യ, ശൂന്യ);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_ഇടത്, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_നടുവ്, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_വലത്, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

സ്ഥിതം ശൂന്യം WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT താക്കോൽ_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(ശൂന്യ, ശൂന്യ);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    താക്കോൽ_State = Get_Async_താക്കോൽ_State(VK_LBUTTON);
    എങ്കിൽ (!(താക്കോൽ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_ഇടത്, mouseID);
    }
    താക്കോൽ_State = Get_Async_താക്കോൽ_State(VK_RBUTTON);
    എങ്കിൽ (!(താക്കോൽ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_വലത്, mouseID);
    }
    താക്കോൽ_State = Get_Async_താക്കോൽ_State(VK_MBUTTON);
    എങ്കിൽ (!(താക്കോൽ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_നടുവ്, mouseID);
    }
    താക്കോൽ_State = Get_Async_താക്കോൽ_State(VK_XBUTTON1);
    എങ്കിൽ (!(താക്കോൽ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    താക്കോൽ_State = Get_Async_താക്കോൽ_State(VK_XBUTTON2);
    എങ്കിൽ (!(താക്കോൽ_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

സ്ഥിതം ശൂന്യം WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    എങ്കിൽ (had_focus == has_focus || has_focus != expect_focus) {
        തിരികെ;
    }

    എങ്കിൽ (has_focus) {
        POINT cursorPos;

        എങ്കിൽ (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            എങ്കിൽ (Get_Async_താക്കോൽ_State(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            എങ്കിൽ (Get_Async_താക്കോൽ_State(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            എങ്കിൽ (Get_Async_താക്കോൽ_State(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            എങ്കിൽ (Get_Async_താക്കോൽ_State(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            എങ്കിൽ (Get_Async_താക്കോൽ_State(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        എങ്കിൽ (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)cursorPos.x, (ദശാംശം)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(data->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_താക്കോൽ_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_അക്കം, (Get_താക്കോൽ_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_താക്കോൽ_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(data->window, true);
    } അല്ലെങ്കിൽ {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(ശൂന്യ);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        എങ്കിൽ (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(ശൂന്യ);
        }
        WIN_Reset_Dead_താക്കോലുകൾ();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

സ്ഥിതം bool ShouldGenerateWindowCloseOnAltF4(ശൂന്യം)
{
    തിരികെ SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

സ്ഥിതം bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    തിരഞ്ഞെടുപ്പ് (data->hint_erase_background_mode) {
    അവസ്ഥ SDL_ERASEBACKGROUNDMODE_NEVER:
        തിരികെ false;
    അവസ്ഥ SDL_ERASEBACKGROUNDMODE_INITIAL:
        തിരികെ !data->videodata->cleared;
    അവസ്ഥ SDL_ERASEBACKGROUNDMODE_ALWAYS:
        തിരികെ true;
    സ്ഥിരസ്ഥിതി:
        // Unexpected value, fallback to default behaviour
        തിരികെ !data->videodata->cleared;
    }
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

തരനിർവചനം എണ്ണൽ
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

സ്ഥിതം SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    എങ്കിൽ (IsTouchEvent(extrainfo)) {
        എങ്കിൽ (extrainfo & 0x80) {
            തിരികെ SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } അല്ലെങ്കിൽ {
            തിരികെ SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    തിരികെ SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

സ്ഥിതം SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    എങ്കിൽ (_this) {
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            എങ്കിൽ (data && data->hwnd == hwnd) {
                തിരികെ data;
            }
        }
    }
    തിരികെ ശൂന്യ;
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(പൂർണ്ണസംഖ്യ nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    എങ്കിൽ (nCode < 0 || nCode != HC_ACTION) {
        തിരികെ CallNextHookEx(ശൂന്യ, nCode, wParam, lParam);
    }
    എങ്കിൽ (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        തിരികെ 1;
    }

    തിരഞ്ഞെടുപ്പ് (hookData->vkCode) {
    അവസ്ഥ VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        നിർത്തുക;
    അവസ്ഥ VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        നിർത്തുക;
    അവസ്ഥ VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        നിർത്തുക;
    അവസ്ഥ VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        നിർത്തുക;
    അവസ്ഥ VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        നിർത്തുക;
    അവസ്ഥ VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        നിർത്തുക;
    അവസ്ഥ VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        നിർത്തുക;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    അവസ്ഥ VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        നിർത്തുക;
    അവസ്ഥ VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
        തിരികെ CallNextHookEx(ശൂന്യ, nCode, wParam, lParam);
    }

    എങ്കിൽ (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        എങ്കിൽ (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!data->raw_keyboard_enabled) {
            SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        എങ്കിൽ (hookData->vkCode <= 0xFF && data->pre_hook_താക്കോൽ_state[hookData->vkCode]) {
            data->pre_hook_താക്കോൽ_state[hookData->vkCode] = 0;
            തിരികെ CallNextHookEx(ശൂന്യ, nCode, wParam, lParam);
        }
    }

    തിരികെ 1;
}

സ്ഥിതം bool WIN_SwapButtons(HANDLE hDevice)
{
    എങ്കിൽ (hDevice == ശൂന്യ) {
        // Touchpad, already has buttons swapped
        തിരികെ false;
    }
    തിരികെ GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

സ്ഥിതം ശൂന്യം WIN_Handle_Raw_Mouse_നിവേശം(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    സ്ഥിതം ഘടന {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_ഇടത്_BUTTON_DOWN, SDL_BUTTON_ഇടത്, true },
        { RI_MOUSE_ഇടത്_BUTTON_UP, SDL_BUTTON_ഇടത്, false },
        { RI_MOUSE_വലത്_BUTTON_DOWN, SDL_BUTTON_വലത്, true },
        { RI_MOUSE_വലത്_BUTTON_UP, SDL_BUTTON_വലത്, false },
        { RI_MOUSE_നടുവ്_BUTTON_DOWN, SDL_BUTTON_നടുവ്, true },
        { RI_MOUSE_നടുവ്_BUTTON_UP, SDL_BUTTON_നടുവ്, false },
        { RI_MOUSE_BUTTON_4_DOWN, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_UP, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_DOWN, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_UP, SDL_BUTTON_X2, false }
    };

    പൂർണ്ണസംഖ്യ dx = (പൂർണ്ണസംഖ്യ)rawmouse->lLastX;
    പൂർണ്ണസംഖ്യ dy = (പൂർണ്ണസംഖ്യ)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    എങ്കിൽ (!data->raw_mouse_enabled) {
        തിരികെ;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    എങ്കിൽ (!window) {
        തിരികെ;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    എങ്കിൽ (!mouse) {
        തിരികെ;
    }

    എങ്കിൽ (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        തിരികെ;
    }

    SDL_WindowData *windowdata = window->internal;

    എങ്കിൽ (haveMotion && !windowdata->in_modal_loop) {
        എങ്കിൽ (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (ദശാംശം)dx, (ദശാംശം)dy);
        } അല്ലെങ്കിൽ {
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
            പൂർണ്ണസംഖ്യ w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            പൂർണ്ണസംഖ്യ h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            പൂർണ്ണസംഖ്യ x = raw_coordinates ? dx : (പൂർണ്ണസംഖ്യ)(((ദശാംശം)dx / 65535.0f) * w);
            പൂർണ്ണസംഖ്യ y = raw_coordinates ? dy : (പൂർണ്ണസംഖ്യ)(((ദശാംശം)dy / 65535.0f) * h);
            പൂർണ്ണസംഖ്യ relX, relY;

            /* Calculate relative motion */
            എങ്കിൽ (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            എങ്കിൽ (remote_desktop) {
                എങ്കിൽ (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    സ്ഥിതം പൂർണ്ണസംഖ്യ wobble;
                    ദശാംശം floatX = (ദശാംശം)x / w;
                    ദശാംശം floatY = (ദശാംശം)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    എങ്കിൽ (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        പൂർണ്ണസംഖ്യ warpX = rect.ഇടത് + ((rect.വലത് - rect.ഇടത്) / 2) + wobble;
                        പൂർണ്ണസംഖ്യ warpY = rect.മുകൾ + ((rect.bottom - rect.മുകൾ) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        എങ്കിൽ (wobble > 1) {
                            wobble = -1;
                        }
                    } അല്ലെങ്കിൽ {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        സ്ഥിരം പൂർണ്ണസംഖ്യ MAX_RELATIVE_MOTION = (h / 6);
                        എങ്കിൽ (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (ദശാംശം)relX, (ദശാംശം)relY);
                        }
                    }
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (mouse->pen_mouse_events) {
                സ്ഥിരം പൂർണ്ണസംഖ്യ MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                എങ്കിൽ (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } അല്ലെങ്കിൽ {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (ദശാംശം)relX, (ദശാംശം)relY);
                }
            } അല്ലെങ്കിൽ {
                പൂർണ്ണസംഖ്യ screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                പൂർണ്ണസംഖ്യ screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                എങ്കിൽ (!data->raw_നിവേശം_fake_pen_id) {
                    data->raw_നിവേശം_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, ശൂന്യ, (ശൂന്യം *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_നിവേശം_fake_pen_id, window, (ദശാംശം)(x + screen_x - window->x), (ദശാംശം)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    എങ്കിൽ (haveButton) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            എങ്കിൽ (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                എങ്കിൽ (button == SDL_BUTTON_ഇടത്) {
                    എങ്കിൽ (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_വലത്;
                    }
                } അല്ലെങ്കിൽ എങ്കിൽ (button == SDL_BUTTON_വലത്) {
                    എങ്കിൽ (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_ഇടത്;
                    }
                }

                എങ്കിൽ (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    എങ്കിൽ (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    തുടരുക;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        എങ്കിൽ (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            ദശാംശം fAmount = (ദശാംശം)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } അല്ലെങ്കിൽ എങ്കിൽ (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            ദശാംശം fAmount = (ദശാംശം)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

സ്ഥിതം ശൂന്യം WIN_Handle_Raw_Keyboard_നിവേശം(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    എങ്കിൽ (!data->raw_keyboard_enabled) {
        തിരികെ;
    }

    എങ്കിൽ (rawkeyboard->Flags & RI_താക്കോൽ_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_താക്കോൽ_sequence = true;
        തിരികെ;
    }

    എങ്കിൽ ((rawkeyboard->Flags & RI_താക്കോൽ_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        തിരികെ;
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_താക്കോൽ(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    എങ്കിൽ (!rawkeyboard->MakeCode) {
        തിരികെ;
    }

    bool down;
    തിരഞ്ഞെടുപ്പ് (rawkeyboard->Message) {
    അവസ്ഥ WM_KEYDOWN:
    അവസ്ഥ WM_SYSKEYDOWN:
        down = true;
        നിർത്തുക;
    അവസ്ഥ WM_KEYUP:
    അവസ്ഥ WM_SYSKEYUP:
        down = false;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        down = !(rawkeyboard->Flags & RI_താക്കോൽ_BREAK);
        നിർത്തുക;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    എങ്കിൽ (data->pending_E1_താക്കോൽ_sequence) {
        rawcode |= 0xE100;
        എങ്കിൽ (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } അല്ലെങ്കിൽ {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_താക്കോൽ_sequence = false;
    } അല്ലെങ്കിൽ {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        എങ്കിൽ (rawkeyboard->Flags & RI_താക്കോൽ_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    എങ്കിൽ (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        എങ്കിൽ ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_നിവേശം_active)) {
            തിരികെ;
        }
    }

    SDL_Send_Keyboard_താക്കോൽ(timestamp, keyboardID, rawcode, code, down);
}

ശൂന്യം WIN_Poll_Raw_നിവേശം(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, എണ്ണം, total = 0;
    RAWINPUT *നിവേശം;
    Uint64 poll_finish;

    എങ്കിൽ (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = വലുപ്പം(RAWINPUTHEADER);
        എങ്കിൽ (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    നിവേശം = (RAWINPUT *)data->rawinput;
    വേണ്ടി (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)നിവേശം - data->rawinput);
        എണ്ണം = Get_Raw_നിവേശം_Buffer(നിവേശം, &size, വലുപ്പം(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        എങ്കിൽ (എണ്ണം == 0 || എണ്ണം == (UINT)-1) {
            എങ്കിൽ (!data->rawinput || (എണ്ണം == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                സ്ഥിരം UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                എങ്കിൽ (!rawinput) {
                    നിർത്തുക;
                }
                നിവേശം = (RAWINPUT *)(rawinput + ((BYTE *)നിവേശം - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } അല്ലെങ്കിൽ {
                നിർത്തുക;
            }
        } അല്ലെങ്കിൽ {
            total += എണ്ണം;

            // Advance input to the end of the buffer
            ആകുമ്പോൾ (എണ്ണം--) {
                നിവേശം = NEXTRAWINPUTBLOCK(നിവേശം);
            }
        }
    }

    എങ്കിൽ (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        വേണ്ടി (i = 0, നിവേശം = (RAWINPUT *)data->rawinput; i < total; ++i, നിവേശം = NEXTRAWINPUTBLOCK(നിവേശം)) {
            എങ്കിൽ (നിവേശം->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        പൂർണ്ണസംഖ്യ mouse_index = 0;
        വേണ്ടി (i = 0, നിവേശം = (RAWINPUT *)data->rawinput; i < total; ++i, നിവേശം = NEXTRAWINPUTBLOCK(നിവേശം)) {
            എങ്കിൽ (നിവേശം->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)നിവേശം + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_Handle_Raw_Mouse_നിവേശം(time, data, നിവേശം->header.hDevice, rawmouse);
            } അല്ലെങ്കിൽ എങ്കിൽ (നിവേശം->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)നിവേശം + data->rawinput_offset);
                WIN_Handle_Raw_Keyboard_നിവേശം(poll_finish, data, നിവേശം->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

സ്ഥിതം ശൂന്യം AddDeviceID(Uint32 deviceID, Uint32 **list, പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    പൂർണ്ണസംഖ്യ new_എണ്ണം = (*എണ്ണം + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_എണ്ണം * വലുപ്പം(*new_list));
    എങ്കിൽ (!new_list) {
        // Oh well, we'll drop this one
        തിരികെ;
    }
    new_list[new_എണ്ണം - 1] = deviceID;

    *എണ്ണം = new_എണ്ണം;
    *list = new_list;
}

സ്ഥിതം bool HasDeviceID(Uint32 deviceID, സ്ഥിരം Uint32 *list, പൂർണ്ണസംഖ്യ എണ്ണം)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം; ++i) {
        എങ്കിൽ (deviceID == list[i]) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

സ്ഥിതം അക്ഷരം *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, സ്ഥിരം അക്ഷരം *instance, Uint16 vendor, Uint16 product, സ്ഥിരം അക്ഷരം *default_name, bool hid_loaded)
{
    അക്ഷരം *vendor_name = ശൂന്യ;
    അക്ഷരം *product_name = ശൂന്യ;
    അക്ഷരം *name = ശൂന്യ;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    എങ്കിൽ (hid_loaded) {
        അക്ഷരം devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = വലുപ്പം(devName) - 1;
        UINT len = Get_Raw_നിവേശം_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        എങ്കിൽ (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, ശൂന്യ, OPEN_EXISTING, 0, ശൂന്യ);
            എങ്കിൽ (hFile != INVALID_HANDLE_മൂല്യം) {
                SDL_HidD_GetManufacturerString(hFile, vend, വലുപ്പം(vend));
                SDL_HidD_GetProductString(hFile, prod, വലുപ്പം(prod));
                CloseHandle(hFile);
            }
        }
    }

    എങ്കിൽ (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    എങ്കിൽ (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } അല്ലെങ്കിൽ {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = വലുപ്പം(data);
        വേണ്ടി (DWORD i = 0;; ++i) {
            എങ്കിൽ (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                എങ്കിൽ (GetLastError() == ERROR_NO_MORE_ഇനങ്ങൾ) {
                    നിർത്തുക;
                } അല്ലെങ്കിൽ {
                    തുടരുക;
                }
            }

            അക്ഷരം DeviceInstanceId[64];
            എങ്കിൽ (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, വലുപ്പം(DeviceInstanceId), ശൂന്യ))
                തുടരുക;

            എങ്കിൽ (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                എങ്കിൽ (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, ശൂന്യ, (PBYTE)prod, വലുപ്പം(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= വലുപ്പം(*prod);
                    എങ്കിൽ (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    എങ്കിൽ (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } അല്ലെങ്കിൽ {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                നിർത്തുക;
            }
        }
    }

    എങ്കിൽ (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    തിരികെ name;
}

ശൂന്യം WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = ശൂന്യ;
    UINT raw_device_എണ്ണം = 0;
    പൂർണ്ണസംഖ്യ old_keyboard_എണ്ണം = 0;
    SDL_KeyboardID *old_keyboards = ശൂന്യ;
    പൂർണ്ണസംഖ്യ new_keyboard_എണ്ണം = 0;
    SDL_KeyboardID *new_keyboards = ശൂന്യ;
    പൂർണ്ണസംഖ്യ old_mouse_എണ്ണം = 0;
    SDL_MouseID *old_mice = ശൂന്യ;
    പൂർണ്ണസംഖ്യ new_mouse_എണ്ണം = 0;
    SDL_MouseID *new_mice = ശൂന്യ;

    എങ്കിൽ (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        തിരികെ;
    }

    എങ്കിൽ ((Get_Raw_നിവേശം_Device_List(ശൂന്യ, &raw_device_എണ്ണം, വലുപ്പം(RAWINPUTDEVICELIST)) == -1) || (!raw_device_എണ്ണം)) {
        തിരികെ; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(വലുപ്പം(RAWINPUTDEVICELIST) * raw_device_എണ്ണം);
    എങ്കിൽ (!raw_devices) {
        തിരികെ; // oh well.
    }

    raw_device_എണ്ണം = Get_Raw_നിവേശം_Device_List(raw_devices, &raw_device_എണ്ണം, വലുപ്പം(RAWINPUTDEVICELIST));
    എങ്കിൽ (raw_device_എണ്ണം == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = ശൂന്യ;
        തിരികെ; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(ശൂന്യ, ശൂന്യ, ശൂന്യ, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_എണ്ണം);
    old_mice = SDL_GetMice(&old_mouse_എണ്ണം);

    വേണ്ടി (UINT i = 0; i < raw_device_എണ്ണം; i++) {
        RID_DEVICE_INFO rdi;
        അക്ഷരം devName[MAX_PATH] = { 0 };
        UINT rdiSize = വലുപ്പം(rdi);
        UINT nameSize = SDL_arraysize(devName);
        പൂർണ്ണസംഖ്യ vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        അക്ഷരം *instance, *ptr, *name;

        എങ്കിൽ (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            തുടരുക;
        }

        rdi.cbSize = വലുപ്പം(rdi);
        എങ്കിൽ (Get_Raw_നിവേശം_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            Get_Raw_നിവേശം_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            തുടരുക;
        }

        // Extract the device instance
        instance = devName;
        ആകുമ്പോൾ (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        വേണ്ടി (ptr = instance; *ptr; ++ptr) {
            എങ്കിൽ (*ptr == '#') {
                *ptr = '\\';
            }
            എങ്കിൽ (*ptr == '{') {
                എങ്കിൽ (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                നിർത്തുക;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        തിരഞ്ഞെടുപ്പ് (dwType) {
        അവസ്ഥ RIM_TYPEKEYBOARD:
            എങ്കിൽ (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_സംഖ്യ_Of_താക്കോലുകൾ_Total)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_എണ്ണം);
                എങ്കിൽ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_എണ്ണം)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            നിർത്തുക;
        അവസ്ഥ RIM_TYPEMOUSE:
            എങ്കിൽ (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_എണ്ണം);
                എങ്കിൽ (!HasDeviceID(mouseID, old_mice, old_mouse_എണ്ണം)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = old_keyboard_എണ്ണം; i--;) {
        എങ്കിൽ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_എണ്ണം)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = old_mouse_എണ്ണം; i--;) {
        എങ്കിൽ (!HasDeviceID(old_mice[i], new_mice, new_mouse_എണ്ണം)) {
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
സ്ഥിതം bool Skip_Alt_Gr_ഇടത്_Control(WPARAM wParam, LPARAM lParam)
{
    എങ്കിൽ (wParam != VK_CONTROL) {
        തിരികെ false;
    }

    // Is this an extended key (i.e. right key)?
    എങ്കിൽ (lParam & 0x01000000) {
        തിരികെ false;
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    സന്ദേശം_2 next_സന്ദേശം;
    DWORD സന്ദേശം_time = GetMessageTime();
    എങ്കിൽ (PeekMessage(&next_സന്ദേശം, ശൂന്യ, 0, 0, PM_NOREMOVE)) {
        എങ്കിൽ (next_സന്ദേശം.message == WM_KEYDOWN ||
            next_സന്ദേശം.message == WM_SYSKEYDOWN) {
            എങ്കിൽ (next_സന്ദേശം.wParam == VK_MENU && (next_സന്ദേശം.lParam & 0x01000000) && next_സന്ദേശം.time == സന്ദേശം_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                തിരികെ true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    തിരികെ false;
}

സ്ഥിതം bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *സന്ദേശം, WPARAM *wParam, LPARAM *lParam)
{
    സന്ദേശം_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *സന്ദേശം;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    എങ്കിൽ (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *സന്ദേശം = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        തിരികെ true;
    }
    തിരികെ false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT സന്ദേശം, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    എങ്കിൽ (!data) {
        തിരികെ CallWindowProc(DefWindowProc, hwnd, സന്ദേശം, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        അക്ഷരം message[1024];
        എങ്കിൽ (സന്ദേശം > MAX_WMMSG) {
            SDL_snprintf(message, വലുപ്പം(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, സന്ദേശം, wParam, lParam);
        } അല്ലെങ്കിൽ {
            SDL_snprintf(message, വലുപ്പം(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[സന്ദേശം], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    എങ്കിൽ (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        എങ്കിൽ (!DispatchModalLoopMessageHook(&hwnd, &സന്ദേശം, &wParam, &lParam)) {
            തിരികെ 0;
        }
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (WIN_HandleIMEMessage(hwnd, സന്ദേശം, wParam, &lParam, data->videodata)) {
        തിരികെ 0;
    }
#endif

    തിരഞ്ഞെടുപ്പ് (സന്ദേശം) {

    അവസ്ഥ WM_SHOWWINDOW:
    {
        എങ്കിൽ (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } അല്ലെങ്കിൽ {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } നിർത്തുക;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    അവസ്ഥ WM_NCACTIVATE:
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
        എങ്കിൽ (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } നിർത്തുക;

    അവസ്ഥ WM_NCUAHDRAWCAPTION:
    അവസ്ഥ WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        എങ്കിൽ (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } നിർത്തുക;

    അവസ്ഥ WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        സ്ഥിരം DWORD സന്ദേശം_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(സന്ദേശം_Pos), GET_Y_LPARAM(സന്ദേശം_Pos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } നിർത്തുക;

    അവസ്ഥ WM_MOUSEACTIVATE:
    {
        എങ്കിൽ (SDL_WINDOW_IS_POPUP(data->window)) {
            തിരികെ MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        ആകുമ്പോൾ (parent) {
            എങ്കിൽ ((parent->flags & SDL_WINDOW_നിവേശം_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                തിരികെ MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } നിർത്തുക;

    അവസ്ഥ WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        സ്ഥിരം DWORD സന്ദേശം_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(സന്ദേശം_Pos), GET_Y_LPARAM(സന്ദേശം_Pos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } നിർത്തുക;

    അവസ്ഥ WM_KILLFOCUS:
    അവസ്ഥ WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        സ്ഥിരം DWORD സന്ദേശം_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(സന്ദേശം_Pos), GET_Y_LPARAM(സന്ദേശം_Pos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } നിർത്തുക;

    അവസ്ഥ WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        സ്ഥിരം UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_നിവേശം_TYPE pointer_type = PT_POINTER;
        എങ്കിൽ (!data->videodata->GetPointerType) {
            നിർത്തുക;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } അല്ലെങ്കിൽ എങ്കിൽ (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            നിർത്തുക;  // oh well.
        } അല്ലെങ്കിൽ എങ്കിൽ (pointer_type != PT_PEN) {
            നിർത്തുക;  // we only care about pens here.
        }

        ശൂന്യം *hpointer = (ശൂന്യം *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        സ്ഥിരം SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        എങ്കിൽ (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } അല്ലെങ്കിൽ {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_DISTANCE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.അക്കം_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_AddPenDevice(WIN_GetEventTimestamp(), ശൂന്യ, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } നിർത്തുക;

    അവസ്ഥ WM_POINTERCAPTURECHANGED:
    അവസ്ഥ WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        സ്ഥിരം UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_നിവേശം_TYPE pointer_type = PT_POINTER;
        എങ്കിൽ (!data->videodata->GetPointerType) {
            നിർത്തുക;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } അല്ലെങ്കിൽ എങ്കിൽ (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            നിർത്തുക;  // oh well.
        } അല്ലെങ്കിൽ എങ്കിൽ (pointer_type != PT_PEN) {
            നിർത്തുക;  // we only care about pens here.
        }

        ശൂന്യം *hpointer = (ശൂന്യം *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        സ്ഥിരം SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        എങ്കിൽ (pen == 0) {
            നിർത്തുക;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        എങ്കിൽ ((സന്ദേശം == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } നിർത്തുക;

    അവസ്ഥ WM_POINTERDOWN:
    അവസ്ഥ WM_POINTERUP:
    അവസ്ഥ WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        സ്ഥിരം UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_നിവേശം_TYPE pointer_type = PT_POINTER;
        എങ്കിൽ (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            നിർത്തുക;  // oh well.
        } അല്ലെങ്കിൽ എങ്കിൽ ((സന്ദേശം == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            നിർത്തുക;
        } അല്ലെങ്കിൽ എങ്കിൽ (pointer_type != PT_PEN) {
            നിർത്തുക; // we only care about pens here.
        }

        ശൂന്യം *hpointer = (ശൂന്യം *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        സ്ഥിരം SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        എങ്കിൽ (pen == 0) {
            നിർത്തുക;  // not a pen, or not a pen we already knew about.
        } അല്ലെങ്കിൽ എങ്കിൽ (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            നിർത്തുക;  // oh well.
        }

        സ്ഥിരം Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        സ്ഥിരം bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        എങ്കിൽ (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        സ്ഥിരം POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        ദശാംശം fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        എങ്കിൽ (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (ദശാംശം) position.x;
            fy = (ദശാംശം) position.y;
        } അല്ലെങ്കിൽ {
            പൂർണ്ണസംഖ്യ ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            സ്ഥിരം SDL_FPoint window_pos = { (ദശാംശം) ix, (ദശാംശം) iy };

            സ്ഥിരം ദശാംശം facX = pointer_info->ptHimetricLocationRaw.x / (ദശാംശം) (tablet_bounds.വലത് );
            സ്ഥിരം ദശാംശം facY = pointer_info->ptHimetricLocationRaw.y / (ദശാംശം) (tablet_bounds.bottom);

            സ്ഥിരം ദശാംശം w = tablet_mapping.വലത്  - tablet_mapping.ഇടത്;
            സ്ഥിരം ദശാംശം h = tablet_mapping.bottom - tablet_mapping.മുകൾ;

            fx = (tablet_mapping.ഇടത് + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.മുകൾ  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        എങ്കിൽ (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((ദശാംശം) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        എങ്കിൽ (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((ദശാംശം) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        എങ്കിൽ (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((ദശാംശം) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        എങ്കിൽ (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((ദശാംശം) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        എങ്കിൽ (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } നിർത്തുക;

    അവസ്ഥ WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        എങ്കിൽ (window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            എങ്കിൽ (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        എങ്കിൽ (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = വലുപ്പം(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            എങ്കിൽ (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        എങ്കിൽ (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            എങ്കിൽ (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)GET_X_LPARAM(lParam), (ദശാംശം)GET_Y_LPARAM(lParam));
            }
        }

    } നിർത്തുക;

    അവസ്ഥ WM_LBUTTONUP:
    അവസ്ഥ WM_RBUTTONUP:
    അവസ്ഥ WM_MBUTTONUP:
    അവസ്ഥ WM_XBUTTONUP:
    അവസ്ഥ WM_LBUTTONDOWN:
    അവസ്ഥ WM_LBUTTONDBLCLK:
    അവസ്ഥ WM_RBUTTONDOWN:
    അവസ്ഥ WM_RBUTTONDBLCLK:
    അവസ്ഥ WM_MBUTTONDOWN:
    അവസ്ഥ WM_MBUTTONDBLCLK:
    അവസ്ഥ WM_XBUTTONDOWN:
    അവസ്ഥ WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        എങ്കിൽ (!data->videodata->raw_mouse_enabled) {
            എങ്കിൽ (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } നിർത്തുക;

#എങ്കിൽ 0   // We handle raw input all at once instead of using a syscall for each mouse event
    അവസ്ഥ WM_നിവേശം:
    {
        HRAWINPUT h_Raw_നിവേശം = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = വലുപ്പം(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        എങ്കിൽ (data->window != SDL_GetKeyboardFocus()) {
            നിർത്തുക;
        }

        Get_Raw_നിവേശം_Data(h_Raw_നിവേശം, RID_നിവേശം, &inp, &size, വലുപ്പം(RAWINPUTHEADER));
        എങ്കിൽ (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_നിവേശം(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } അല്ലെങ്കിൽ എങ്കിൽ (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_നിവേശം(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } നിർത്തുക;
#endif

    അവസ്ഥ WM_MOUSEWHEEL:
    അവസ്ഥ WM_MOUSEHWHEEL:
    {
        എങ്കിൽ (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            ദശാംശം fAmount = (ദശാംശം)amount / WHEEL_DELTA;
            എങ്കിൽ (സന്ദേശം == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } അല്ലെങ്കിൽ {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } നിർത്തുക;

    അവസ്ഥ WM_MOUSELEAVE:
        എങ്കിൽ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            എങ്കിൽ (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                എങ്കിൽ (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)cursorPos.x, (ദശാംശം)cursorPos.y);
                } അല്ലെങ്കിൽ {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    എങ്കിൽ (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (ദശാംശം)cursorPos.x, (ദശാംശം)cursorPos.y);
                    } അല്ലെങ്കിൽ { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)cursorPos.x, (ദശാംശം)cursorPos.y);
                    }
                }
            }

            എങ്കിൽ (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(ശൂന്യ);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        നിർത്തുക;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    അവസ്ഥ WM_KEYDOWN:
    അവസ്ഥ WM_SYSKEYDOWN:
    {
        എങ്കിൽ (Skip_Alt_Gr_ഇടത്_Control(wParam, lParam)) {
            returnCode = 0;
            നിർത്തുക;
        }

        bool virtual_താക്കോൽ = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_താക്കോൽ);

        // Detect relevant keyboard shortcuts
        എങ്കിൽ (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            എങ്കിൽ (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        എങ്കിൽ (virtual_താക്കോൽ || !data->videodata->raw_keyboard_enabled || data->window->text_നിവേശം_active) {
            SDL_Send_Keyboard_താക്കോൽ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        നിർത്തുക;

    അവസ്ഥ WM_SYSKEYUP:
    അവസ്ഥ WM_KEYUP:
    {
        എങ്കിൽ (Skip_Alt_Gr_ഇടത്_Control(wParam, lParam)) {
            returnCode = 0;
            നിർത്തുക;
        }

        bool virtual_താക്കോൽ = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_താക്കോൽ);
        സ്ഥിരം bool *keyboardState = SDL_GetKeyboardState(ശൂന്യ);

        എങ്കിൽ (virtual_താക്കോൽ || !data->videodata->raw_keyboard_enabled || data->window->text_നിവേശം_active) {
            എങ്കിൽ (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_താക്കോൽ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_താക്കോൽ(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        നിർത്തുക;

    അവസ്ഥ WM_UNICHAR:
        എങ്കിൽ (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (SDL_Text_നിവേശം_Active(data->window)) {
                അക്ഷരം text[5];
                അക്ഷരം *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        നിർത്തുക;

    അവസ്ഥ WM_CHAR:
        എങ്കിൽ (SDL_Text_നിവേശം_Active(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            എങ്കിൽ (IS_മുകളിലെ_SURROGATE(wParam)) {
                data->മുകളിലെ_surrogate = (WCHAR)wParam;
            } അല്ലെങ്കിൽ {
                WCHAR utf16[3];

                utf16[0] = data->മുകളിലെ_surrogate ? data->മുകളിലെ_surrogate : (WCHAR)wParam;
                utf16[1] = data->മുകളിലെ_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                അക്ഷരം utf8[5];
                പൂർണ്ണസംഖ്യ result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, വലുപ്പം(utf8), ശൂന്യ, ശൂന്യ);
                എങ്കിൽ (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->മുകളിലെ_surrogate = L'\0';
            }
        } അല്ലെങ്കിൽ {
            data->മുകളിലെ_surrogate = L'\0';
        }

        returnCode = 0;
        നിർത്തുക;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    അവസ്ഥ WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        നിർത്തുക;
#endif // WM_INPUTLANGCHANGE

    അവസ്ഥ WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        എങ്കിൽ (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } നിർത്തുക;

    അവസ്ഥ WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } നിർത്തുക;

#ifdef WM_GETMINMAXINFO
    അവസ്ഥ WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        പൂർണ്ണസംഖ്യ x, y;
        പൂർണ്ണസംഖ്യ w, h;
        പൂർണ്ണസംഖ്യ min_w, min_h;
        പൂർണ്ണസംഖ്യ max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        എങ്കിൽ (data->expected_resize) {
            നിർത്തുക;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &size);
        x = size.ഇടത്;
        y = size.മുകൾ;

        // Calculate current size of our window
        SDL_GetWindowSize(data->window, &w, &h);
        SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
        SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        എങ്കിൽ (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } അല്ലെങ്കിൽ {
            constrain_max_size = FALSE;
        }

        എങ്കിൽ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
            size.മുകൾ = 0;
            size.ഇടത് = 0;
            size.bottom = h;
            size.വലത് = w;
            WIN_AdjustWindowRectForHWND(hwnd, &size, 0);
            w = size.വലത് - size.ഇടത്;
            h = size.bottom - size.മുകൾ;
#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#endif
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        എങ്കിൽ (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            എങ്കിൽ (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                പൂർണ്ണസംഖ്യ screenW = GetSystemMetrics(SM_CXSCREEN);
                പൂർണ്ണസംഖ്യ screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            എങ്കിൽ (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } അല്ലെങ്കിൽ {
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
        നിർത്തുക;
#endif // WM_GETMINMAXINFO

    അവസ്ഥ WM_WINDOWPOSCHANGING:

        എങ്കിൽ (data->expected_resize) {
            returnCode = 0;
        } അല്ലെങ്കിൽ എങ്കിൽ (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            എങ്കിൽ (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        നിർത്തുക;

    അവസ്ഥ WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        സ്ഥിരം SDL_DisplayID original_displayID = data->window->displayID;
        സ്ഥിരം WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        പൂർണ്ണസംഖ്യ x, y;
        പൂർണ്ണസംഖ്യ w, h;

        എങ്കിൽ (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        എങ്കിൽ (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } അല്ലെങ്കിൽ എങ്കിൽ (zoomed) {
            എങ്കിൽ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } അല്ലെങ്കിൽ എങ്കിൽ (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            എങ്കിൽ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        എങ്കിൽ (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        എങ്കിൽ (iconic) {
            നിർത്തുക;
        }

        എങ്കിൽ (data->initializing) {
            നിർത്തുക;
        }

        എങ്കിൽ (!data->disable_move_size_events) {
            എങ്കിൽ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.ഇടത്;
                y = rect.മുകൾ;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            എങ്കിൽ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.വലത്;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        എങ്കിൽ (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        വേണ്ടി (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            എങ്കിൽ (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } നിർത്തുക;

    അവസ്ഥ WM_ENTERSIZEMOVE:
    അവസ്ഥ WM_ENTERMENULOOP:
    {
        എങ്കിൽ (g_WindowsMessageHook) {
            എങ്കിൽ (!DispatchModalLoopMessageHook(&hwnd, &സന്ദേശം, &wParam, &lParam)) {
                തിരികെ 0;
            }
        }

        ++data->in_modal_loop;
        എങ്കിൽ (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.വലത് - rect.ഇടത്;
            data->last_modal_height = rect.bottom - rect.മുകൾ;

            data->initial_size_rect.ഇടത് = data->window->x;
            data->initial_size_rect.വലത് = data->window->x + data->window->w;
            data->initial_size_rect.മുകൾ = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, ശൂന്യ);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } നിർത്തുക;

    അവസ്ഥ WM_TIMER:
    {
        എങ്കിൽ (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#എങ്കിൽ 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            എങ്കിൽ (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            തിരികെ 0;
        }
    } നിർത്തുക;

    അവസ്ഥ WM_EXITSIZEMOVE:
    അവസ്ഥ WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        എങ്കിൽ (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } നിർത്തുക;

    അവസ്ഥ WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            ദശാംശം new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            എങ്കിൽ (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                നിർത്തുക;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            എങ്കിൽ (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != ശൂന്യ, GetWindowExStyle(hwnd))) {
                നിർത്തുക;
            }

            clientDragRect.ഇടത് -= rc.ഇടത്;
            clientDragRect.മുകൾ -= rc.മുകൾ;
            clientDragRect.വലത് -= rc.വലത്;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.വലത് - clientDragRect.ഇടത്;
            h = clientDragRect.bottom - clientDragRect.മുകൾ;
            new_aspect = w / (ദശാംശം)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            എങ്കിൽ (lock_aspect_ratio) {
                തിരഞ്ഞെടുപ്പ് (edge) {
                അവസ്ഥ WMSZ_ഇടത്:
                അവസ്ഥ WMSZ_വലത്:
                    h = (പൂർണ്ണസംഖ്യ)SDL_roundf(w / data->window->max_aspect);
                    നിർത്തുക;
                സ്ഥിരസ്ഥിതി:
                    // resizing via corners or top or bottom
                    w = (പൂർണ്ണസംഖ്യ)SDL_roundf(h * data->window->max_aspect);
                    നിർത്തുക;
                }
            } അല്ലെങ്കിൽ {
                തിരഞ്ഞെടുപ്പ് (edge) {
                അവസ്ഥ WMSZ_ഇടത്:
                അവസ്ഥ WMSZ_വലത്:
                    എങ്കിൽ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (പൂർണ്ണസംഖ്യ)SDL_roundf(h * data->window->max_aspect);
                    } അല്ലെങ്കിൽ എങ്കിൽ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (പൂർണ്ണസംഖ്യ)SDL_roundf(h * data->window->min_aspect);
                    }
                    നിർത്തുക;
                അവസ്ഥ WMSZ_മുകൾ:
                അവസ്ഥ WMSZ_BOTTOM:
                    എങ്കിൽ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (പൂർണ്ണസംഖ്യ)SDL_roundf(w / data->window->min_aspect);
                    } അല്ലെങ്കിൽ എങ്കിൽ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (പൂർണ്ണസംഖ്യ)SDL_roundf(w / data->window->max_aspect);
                    }
                    നിർത്തുക;

                സ്ഥിരസ്ഥിതി:
                    // resizing via corners
                    എങ്കിൽ (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (പൂർണ്ണസംഖ്യ)SDL_roundf(h * data->window->max_aspect);
                    } അല്ലെങ്കിൽ എങ്കിൽ (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (പൂർണ്ണസംഖ്യ)SDL_roundf(w / data->window->min_aspect);
                    }
                    നിർത്തുക;
                }
            }

            തിരഞ്ഞെടുപ്പ് (edge) {
            അവസ്ഥ WMSZ_ഇടത്:
                clientDragRect.ഇടത് = clientDragRect.വലത് - w;
                എങ്കിൽ (lock_aspect_ratio) {
                    clientDragRect.മുകൾ = (data->initial_size_rect.bottom + data->initial_size_rect.മുകൾ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.മുകൾ;
                നിർത്തുക;
            അവസ്ഥ WMSZ_BOTTOMLEFT:
                clientDragRect.ഇടത് = clientDragRect.വലത് - w;
                clientDragRect.bottom = h + clientDragRect.മുകൾ;
                നിർത്തുക;
            അവസ്ഥ WMSZ_വലത്:
                clientDragRect.വലത് = w + clientDragRect.ഇടത്;
                എങ്കിൽ (lock_aspect_ratio) {
                    clientDragRect.മുകൾ = (data->initial_size_rect.bottom + data->initial_size_rect.മുകൾ - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.മുകൾ;
                നിർത്തുക;
            അവസ്ഥ WMSZ_TOPRIGHT:
                clientDragRect.വലത് = w + clientDragRect.ഇടത്;
                clientDragRect.മുകൾ = clientDragRect.bottom - h;
                നിർത്തുക;
            അവസ്ഥ WMSZ_മുകൾ:
                എങ്കിൽ (lock_aspect_ratio) {
                    clientDragRect.ഇടത് = (data->initial_size_rect.വലത് + data->initial_size_rect.ഇടത് - w) / 2;
                }
                clientDragRect.വലത് = w + clientDragRect.ഇടത്;
                clientDragRect.മുകൾ = clientDragRect.bottom - h;
                നിർത്തുക;
            അവസ്ഥ WMSZ_TOPLEFT:
                clientDragRect.ഇടത് = clientDragRect.വലത് - w;
                clientDragRect.മുകൾ = clientDragRect.bottom - h;
                നിർത്തുക;
            അവസ്ഥ WMSZ_BOTTOM:
                എങ്കിൽ (lock_aspect_ratio) {
                    clientDragRect.ഇടത് = (data->initial_size_rect.വലത് + data->initial_size_rect.ഇടത് - w) / 2;
                }
                clientDragRect.വലത് = w + clientDragRect.ഇടത്;
                clientDragRect.bottom = h + clientDragRect.മുകൾ;
                നിർത്തുക;
            അവസ്ഥ WMSZ_BOTTOMRIGHT:
                clientDragRect.വലത് = w + clientDragRect.ഇടത്;
                clientDragRect.bottom = h + clientDragRect.മുകൾ;
                നിർത്തുക;
            }

            // convert the client rect to a window rect
            എങ്കിൽ (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != ശൂന്യ, GetWindowExStyle(hwnd))) {
                നിർത്തുക;
            }

            *dragRect = clientDragRect;
        }
        നിർത്തുക;

    അവസ്ഥ WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        എങ്കിൽ (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } അല്ലെങ്കിൽ എങ്കിൽ (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(ശൂന്യ);
            returnCode = TRUE;
        }
    } നിർത്തുക;

        // We were occluded, refresh our display
    അവസ്ഥ WM_PAINT:
    {
        RECT rect;
        എങ്കിൽ (GetUpdateRect(hwnd, &rect, FALSE)) {
            സ്ഥിരം LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            എങ്കിൽ (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, ശൂന്യ);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        നിർത്തുക;

        // We'll do our own drawing, prevent flicker
    അവസ്ഥ WM_ERASEBKGND:
        എങ്കിൽ (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        തിരികെ 1;

    അവസ്ഥ WM_SYSCOMMAND:
    {
        എങ്കിൽ (!g_WindowsEnableMenuMnemonics) {
            എങ്കിൽ ((wParam & 0xFFF0) == SC_KEYMENU) {
                തിരികെ 0;
            }
        }

#എങ്കിൽ defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        എങ്കിൽ ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            എങ്കിൽ (SDL_GetVideoDevice()->suspend_screensaver) {
                തിരികെ 0;
            }
        }
#endif // System has screensaver support
    } നിർത്തുക;

    അവസ്ഥ WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        നിർത്തുക;

    അവസ്ഥ WM_TOUCH:
        എങ്കിൽ (data->videodata->Get_Touch_നിവേശം_Info && data->videodata->Close_Touch_നിവേശം_Handle) {
            UINT i, അക്കം_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, അക്കം_inputs, &isstack);
            എങ്കിൽ (inputs && data->videodata->Get_Touch_നിവേശം_Info((HTOUCHINPUT)lParam, അക്കം_inputs, inputs, വലുപ്പം(TOUCHINPUT))) {
                RECT rect;
                ദശാംശം x, y;

                എങ്കിൽ (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    എങ്കിൽ (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    നിർത്തുക;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.മുകൾ *= 100;
                rect.ഇടത് *= 100;
                rect.bottom *= 100;
                rect.വലത് *= 100;

                വേണ്ടി (i = 0; i < അക്കം_inputs; ++i) {
                    PTOUCHINPUT നിവേശം = &inputs[i];
                    സ്ഥിരം പൂർണ്ണസംഖ്യ w = (rect.വലത് - rect.ഇടത്);
                    സ്ഥിരം പൂർണ്ണസംഖ്യ h = (rect.bottom - rect.മുകൾ);

                    സ്ഥിരം SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)നിവേശം->hSource);
                    സ്ഥിരം SDL_FingerID fingerId = (നിവേശം->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    എങ്കിൽ (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (നിവേശം->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        തുടരുക;
                    }

                    // Get the normalized coordinates for the window
                    എങ്കിൽ (w <= 1) {
                        x = 0.5f;
                    } അല്ലെങ്കിൽ {
                        x = (ദശാംശം)(നിവേശം->x - rect.ഇടത്) / (w - 1);
                    }
                    എങ്കിൽ (h <= 1) {
                        y = 0.5f;
                    } അല്ലെങ്കിൽ {
                        y = (ദശാംശം)(നിവേശം->y - rect.മുകൾ) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    എങ്കിൽ (നിവേശം->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    എങ്കിൽ (നിവേശം->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    എങ്കിൽ (നിവേശം->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->Close_Touch_നിവേശം_Handle((HTOUCHINPUT)lParam);
            തിരികെ 0;
        }
        നിർത്തുക;

#ifdef HAVE_TPCSHRD_H

    അവസ്ഥ WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        തിരികെ TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    അവസ്ഥ WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT എണ്ണം = DragQueryFile(drop, 0xFFFFFFFF, ശൂന്യ, 0);
        വേണ്ടി (i = 0; i < എണ്ണം; ++i) {
            UINT size = DragQueryFile(drop, i, ശൂന്യ, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(വലുപ്പം(TCHAR) * size);
            എങ്കിൽ (buffer) {
                എങ്കിൽ (DragQueryFile(drop, i, buffer, size)) {
                    അക്ഷരം *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, ശൂന്യ, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        തിരികെ 0;
    }

    അവസ്ഥ WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } നിർത്തുക;

    അവസ്ഥ WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        എങ്കിൽ (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            എങ്കിൽ (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                എങ്കിൽ (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    സ്ഥിരം POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                എങ്കിൽ (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = വലുപ്പം(info);
                    എങ്കിൽ (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                പൂർണ്ണസംഖ്യ w, h;
                എങ്കിൽ (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } അല്ലെങ്കിൽ {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].വലത് = params->rgrc[0].ഇടത് + w;
                params->rgrc[0].bottom = params->rgrc[0].മുകൾ + h;
            }
            തിരികെ 0;
        }
    } നിർത്തുക;

    അവസ്ഥ WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        എങ്കിൽ (window->flags & SDL_WINDOW_TOOLTIP) {
            തിരികെ HTTRANSPARENT;
        }

        എങ്കിൽ (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            എങ്കിൽ (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                തിരഞ്ഞെടുപ്പ് (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        തിരികെ ret;                                                        \
    }
                അവസ്ഥ SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(ശൂന്യ, ശൂന്യ);
                    എങ്കിൽ (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        തിരികെ HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ:
                    POST_HIT_TEST(HTTOP);
                അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                അവസ്ഥ SDL_HITTEST_RESIZE_വലത്:
                    POST_HIT_TEST(HTRIGHT);
                അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                അവസ്ഥ SDL_HITTEST_NORMAL:
                    തിരികെ HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } നിർത്തുക;

    അവസ്ഥ WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        എങ്കിൽ (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            സ്ഥിരം പൂർണ്ണസംഖ്യ nextDPI = (പൂർണ്ണസംഖ്യ)wParam;
            സ്ഥിരം പൂർണ്ണസംഖ്യ prevDPI = (പൂർണ്ണസംഖ്യ)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            പൂർണ്ണസംഖ്യ frame_w, frame_h;
            പൂർണ്ണസംഖ്യ query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                എങ്കിൽ (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, prevDPI);
                }

                frame_w = -rect.ഇടത് + rect.വലത്;
                frame_h = -rect.മുകൾ + rect.bottom;

                query_client_w_win = sizeInOut->cx - frame_w;
                query_client_h_win = sizeInOut->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.വലത് = query_client_w_win;
                rect.bottom = query_client_h_win;

                എങ്കിൽ (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.വലത് - rect.ഇടത്;
                sizeInOut->cy = rect.bottom - rect.മുകൾ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            തിരികെ TRUE;
        }
        നിർത്തുക;

    അവസ്ഥ WM_DPICHANGED:
        // Windows 8.1+
        {
            സ്ഥിരം പൂർണ്ണസംഖ്യ newDPI = HIWORD(wParam);
            RECT *സ്ഥിരം suggestedRect = (RECT *)lParam;
            പൂർണ്ണസംഖ്യ w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->ഇടത്, suggestedRect->മുകൾ, suggestedRect->വലത് - suggestedRect->ഇടത്, suggestedRect->bottom - suggestedRect->മുകൾ);
#endif

            എങ്കിൽ (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                തിരികെ 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.വലത് = data->window->w;
                rect.bottom = data->window->h;

                എങ്കിൽ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.വലത് - rect.ഇടത്;
                h = rect.bottom - rect.മുകൾ;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    data->window->w, data->window->h,
                    suggestedRect->ഇടത്, suggestedRect->മുകൾ, w, h);
#endif

            data->expected_resize = true;
            SetWindowPos(hwnd,
                         ശൂന്യ,
                         suggestedRect->ഇടത്,
                         suggestedRect->മുകൾ,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            തിരികെ 0;
        }

    അവസ്ഥ WM_SETTINGCHANGE:
        എങ്കിൽ (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        എങ്കിൽ (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        എങ്കിൽ (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        നിർത്തുക;
#അല്ലെങ്കിൽ
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    അവസ്ഥ WM_SIZE:
    {
        RECT rect;
        പൂർണ്ണസംഖ്യ w, h;

        എങ്കിൽ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.വലത്;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } നിർത്തുക;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (സന്ദേശം && സന്ദേശം == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    എങ്കിൽ (data->wndproc) {
        തിരികെ CallWindowProc(data->wndproc, hwnd, സന്ദേശം, wParam, lParam);
    } അല്ലെങ്കിൽ എങ്കിൽ (returnCode >= 0) {
        തിരികെ returnCode;
    } അല്ലെങ്കിൽ {
        തിരികെ CallWindowProc(DefWindowProc, hwnd, സന്ദേശം, wParam, lParam);
    }
}

പൂർണ്ണസംഖ്യ WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    എങ്കിൽ (g_WindowsEnableMessageLoop) {
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = സന്ദേശം_Wait_For_Multiple_Objects(0, ശൂന്യ, FALSE, timeout, QS_ALLINPUT);
        എങ്കിൽ (ret == WAIT_OBJECT_0) {
            തിരികെ 1;
        } അല്ലെങ്കിൽ {
            തിരികെ 0;
        }
#അല്ലെങ്കിൽ
        // MsgWaitForMultipleObjects is desktop-only.
        സന്ദേശം_2 സന്ദേശം;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        എങ്കിൽ (timeoutNS > 0) {
            timer_id = SetTimer(ശൂന്യ, 0, (UINT)SDL_NS_TO_MS(timeoutNS), ശൂന്യ);
            message_result = GetMessage(&സന്ദേശം, 0, 0, 0);
            KillTimer(ശൂന്യ, timer_id);
        } അല്ലെങ്കിൽ എങ്കിൽ (timeoutNS == 0) {
            message_result = PeekMessage(&സന്ദേശം, ശൂന്യ, 0, 0, PM_REMOVE);
        } അല്ലെങ്കിൽ {
            message_result = GetMessage(&സന്ദേശം, 0, 0, 0);
        }
        എങ്കിൽ (message_result) {
            എങ്കിൽ (സന്ദേശം.message == WM_TIMER && !സന്ദേശം.hwnd && സന്ദേശം.wParam == timer_id) {
                തിരികെ 0;
            }
            എങ്കിൽ (g_WindowsMessageHook) {
                എങ്കിൽ (!g_WindowsMessageHook(g_WindowsMessageHookData, &സന്ദേശം)) {
                    തിരികെ 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&സന്ദേശം);
            DispatchMessage(&സന്ദേശം);
            തിരികെ 1;
        } അല്ലെങ്കിൽ {
            തിരികെ 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } അല്ലെങ്കിൽ {
        // Fail the wait so the caller falls back to polling
        തിരികെ -1;
    }
}

ശൂന്യം WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
ശൂന്യം WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    സന്ദേശം_2 സന്ദേശം;

    എങ്കിൽ (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        ആകുമ്പോൾ (PeekMessage(&സന്ദേശം, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(സന്ദേശം.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&സന്ദേശം);
            DispatchMessage(&സന്ദേശം);
        }

        SDL_processing_messages = false;
    }
}

ശൂന്യം WIN_PumpEvents(SDL_VideoDevice *_this)
{
    സന്ദേശം_2 സന്ദേശം;
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(തള്ളുക)
#pragma warning(disable : 28159)
#endif
    DWORD end_ticks = Get_Tick_എണ്ണം() + 1;
#ifdef _MSC_VER
#pragma warning(എടുക്കുക)
#endif
    പൂർണ്ണസംഖ്യ new_messages = 0;

    എങ്കിൽ (_this->internal->gameinput_context) {
        WIN_Update_Game_നിവേശം(_this);
    }

    എങ്കിൽ (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        ആകുമ്പോൾ (PeekMessage(&സന്ദേശം, ശൂന്യ, 0, 0, PM_REMOVE)) {
            എങ്കിൽ (g_WindowsMessageHook) {
                എങ്കിൽ (!g_WindowsMessageHook(g_WindowsMessageHookData, &സന്ദേശം)) {
                    തുടരുക;
                }
            }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            എങ്കിൽ (സന്ദേശം.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                എങ്കിൽ (!SDL_TICKS_PASSED(സന്ദേശം.time, (SDL_last_warp_time + 1))) {
                    തുടരുക;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(സന്ദേശം.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&സന്ദേശം);
            DispatchMessage(&സന്ദേശം);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            എങ്കിൽ (SDL_TICKS_PASSED(സന്ദേശം.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                സ്ഥിരം പൂർണ്ണസംഖ്യ MAX_NEW_MESSAGES = 3;
                ++new_messages;
                എങ്കിൽ (new_messages > MAX_NEW_MESSAGES) {
                    നിർത്തുക;
                }
            }
        }

        SDL_processing_messages = false;
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    സ്ഥിരം bool *keystate = SDL_GetKeyboardState(ശൂന്യ);
    എങ്കിൽ (keystate[SDL_SCANCODE_LSHIFT] && !(Get_താക്കോൽ_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    എങ്കിൽ (keystate[SDL_SCANCODE_RSHIFT] && !(Get_താക്കോൽ_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    എങ്കിൽ (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        എങ്കിൽ (keystate[SDL_SCANCODE_LGUI] && !(Get_താക്കോൽ_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        എങ്കിൽ (keystate[SDL_SCANCODE_RGUI] && !(Get_താക്കോൽ_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    എങ്കിൽ (_this) {
        SDL_Window *window = _this->windows;
        ആകുമ്പോൾ (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            എങ്കിൽ (data) {
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
            എങ്കിൽ (refresh_clipcursor) {
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
    എങ്കിൽ (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        എങ്കിൽ (!data->mouse_tracked) {
            POINT cursorPos;

            എങ്കിൽ (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (ദശാംശം)cursorPos.x, (ദശാംശം)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_ഇടത് : SDL_BUTTON_വലത്,
                                    (Get_Async_താക്കോൽ_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_വലത് : SDL_BUTTON_ഇടത്,
                                    (Get_Async_താക്കോൽ_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_നടുവ്,
                                    (Get_Async_താക്കോൽ_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_താക്കോൽ_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), data->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_താക്കോൽ_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#endif
}

സ്ഥിതം പൂർണ്ണസംഖ്യ app_registered = 0;
LPTSTR SDL_Appname = ശൂന്യ;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = ശൂന്യ;

സ്ഥിതം ശൂന്യം WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    എങ്കിൽ (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = ശൂന്യ;
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
സ്ഥിതം BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (ശൂന്യം)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    തിരികെ FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(സ്ഥിരം അക്ഷരം *name, Uint32 style, ശൂന്യം *hInst)
{
    WNDCLASSEX wcex;
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    സ്ഥിരം അക്ഷരം *hint;
#endif

    // Only do this once...
    എങ്കിൽ (app_registered) {
        ++app_registered;
        തിരികെ true;
    }
    SDL_assert(!SDL_Appname);
    എങ്കിൽ (!name) {
        name = "SDL_app";
#എങ്കിൽ defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(ശൂന്യ);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = വലുപ്പം(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    എങ്കിൽ (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        എങ്കിൽ (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } അല്ലെങ്കിൽ {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    എങ്കിൽ (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        തിരികെ SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    തിരികെ true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
ശൂന്യം SDL_UnregisterApp(ശൂന്യം)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    എങ്കിൽ (!app_registered) {
        തിരികെ;
    }
    --app_registered;
    എങ്കിൽ (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = ശൂന്യ;
        wcex.hIconSm = ശൂന്യ;
        // Check for any registered window classes.
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        എങ്കിൽ (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
