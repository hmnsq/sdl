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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS

#समावेश "SDL_windowsvideo.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_touch_c.h"
#समावेश "../../events/scancodes_windows.h"
#समावेश "../../main/SDL_main_callbacks.h"
#समावेश "../../core/windows/SDL_hid.h"

// Dropfile support
#समावेश <shellapi.h>

// Device names
#समावेश <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#समावेश <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#अगर_घोषित HAVE_TPCSHRD_H
#समावेश <tpcshrd.h>
#पूर्ण_अगर // HAVE_TPCSHRD_H

#अगर 0
#घोषणा WMMSG_DEBUG
#पूर्ण_अगर
#अगर_घोषित WMMSG_DEBUG
#समावेश <stdio.h>
#समावेश "wmmsg.h"
#पूर्ण_अगर

#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#समावेश <shobjidl.h>
#पूर्ण_अगर

#अगर_घोषित SDL_PLATFORM_GDK
#समावेश "../../core/gdk/SDL_gdk.h"
#पूर्ण_अगर

// #define HIGHDPI_DEBUG

// Undocumented window messages
#अगर_अघोषित WM_NCUAHDRAWCAPTION
#घोषणा WM_NCUAHDRAWCAPTION 0xAE
#पूर्ण_अगर
#अगर_अघोषित WM_NCUAHDRAWFRAME
#घोषणा WM_NCUAHDRAWFRAME 0xAF
#पूर्ण_अगर

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#अगर_अघोषित WM_XBUTTONDOWN
#घोषणा WM_XBUTTONDOWN 0x020B
#पूर्ण_अगर
#अगर_अघोषित WM_XBUTTONUP
#घोषणा WM_XBUTTONUP 0x020C
#पूर्ण_अगर
#अगर_अघोषित GET_XBUTTON_WPARAM
#घोषणा GET_XBUTTON_WPARAM(w) (HIWORD(w))
#पूर्ण_अगर
#अगर_अघोषित WM_निवेश
#घोषणा WM_निवेश 0x00ff
#पूर्ण_अगर
#अगर_अघोषित WM_TOUCH
#घोषणा WM_TOUCH 0x0240
#पूर्ण_अगर
#अगर_अघोषित WM_MOUSEHWHEEL
#घोषणा WM_MOUSEHWHEEL 0x020E
#पूर्ण_अगर
#अगर_अघोषित RI_MOUSE_HWHEEL
#घोषणा RI_MOUSE_HWHEEL 0x0800
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERUPDATE
#घोषणा WM_POINTERUPDATE 0x0245
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERDOWN
#घोषणा WM_POINTERDOWN 0x0246
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERUP
#घोषणा WM_POINTERUP 0x0247
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERENTER
#घोषणा WM_POINTERENTER 0x0249
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERLEAVE
#घोषणा WM_POINTERLEAVE 0x024A
#पूर्ण_अगर
#अगर_अघोषित WM_POINTERCAPTURECHANGED
#घोषणा WM_POINTERCAPTURECHANGED 0x024C
#पूर्ण_अगर
#अगर_अघोषित WM_UNICHAR
#घोषणा WM_UNICHAR 0x0109
#पूर्ण_अगर
#अगर_अघोषित WM_DPICHANGED
#घोषणा WM_DPICHANGED 0x02E0
#पूर्ण_अगर
#अगर_अघोषित WM_GETDPISCALEDSIZE
#घोषणा WM_GETDPISCALEDSIZE 0x02E4
#पूर्ण_अगर
#अगर_अघोषित TOUCHEVENTF_PEN
#घोषणा TOUCHEVENTF_PEN 0x0040
#पूर्ण_अगर

#अगर_अघोषित MAPVK_VK_TO_VSC_EX
#घोषणा MAPVK_VK_TO_VSC_EX 4
#पूर्ण_अगर

#अगर_अघोषित WC_ERR_INVALID_CHARS
#घोषणा WC_ERR_INVALID_CHARS 0x00000080
#पूर्ण_अगर

#अगर_अघोषित IS_ऊपरी_SURROGATE
#घोषणा IS_ऊपरी_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#पूर्ण_अगर

#अगर_अघोषित USER_TIMER_MINIMUM
#घोषणा USER_TIMER_MINIMUM 0x0000000A
#पूर्ण_अगर

// Used to compare Windows message timestamps
#घोषणा SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#अगर_घोषित _WIN64
प्रकार Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#पूर्ण_अगर

अटल bool SDL_processing_messages;
अटल DWORD message_tick;
अटल Uint64 timestamp_offset;

अटल व्योम WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

अटल Uint64 WIN_GetEventTimestamp(व्योम)
{
    स्थिर Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    अगर (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        वापस 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    अगर (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } अन्यथा अगर ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } अन्यथा अगर (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    वापस timestamp;
}

// A message hook called before TranslateMessage()
अटल SDL_WindowsMessageHook g_WindowsMessageHook = शून्य;
अटल व्योम *g_Windows_Message_Hook_तथ्य = शून्य;

व्योम SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, व्योम *userdata)
{
    g_WindowsMessageHook = callback;
    g_Windows_Message_Hook_तथ्य = userdata;
}

अटल SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_कुंजी)
{
    SDL_Scancode code;
    Uint8 सूचकांक;
    Uint16 कुंजी_Flags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(कुंजी_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_कुंजी = (scanCode == 0);

    अगर (scanCode != 0) {
        अगर ((कुंजी_Flags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } अन्यथा अगर (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } अन्यथा {
        Uint16 vkCode = LOWORD(wParam);

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(Map_Virtual_कुंजी(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        अगर (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    सूचकांक = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[सूचकांक];
    *rawcode = scanCode;

    वापस code;
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
अटल bool WIN_ShouldIgnoreFocusClick(SDL_Window_तथ्य *तथ्य)
{
    वापस !SDL_WINDOW_IS_POPUP(तथ्य->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

अटल व्योम WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_Window_तथ्य *तथ्य, Uint8 button, SDL_MouseID mouseID)
{
    अगर (bSwapButtons) {
        अगर (button == SDL_BUTTON_बायाँ) {
            button = SDL_BUTTON_दायाँ;
        } अन्यथा अगर (button == SDL_BUTTON_दायाँ) {
            button = SDL_BUTTON_बायाँ;
        }
    }

    अगर (तथ्य->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        अगर (!bwParamMousePressed) {
            तथ्य->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(तथ्य->window);
        }
        वापस;
    }

    अगर (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, तथ्य->window, mouseID, button, true);
    } अन्यथा अगर (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, तथ्य->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
अटल व्योम WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_Window_तथ्य *तथ्य, SDL_MouseID mouseID)
{
    अगर (wParam != तथ्य->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(शून्य, शून्य);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, तथ्य, SDL_BUTTON_बायाँ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, तथ्य, SDL_BUTTON_मध्य, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, तथ्य, SDL_BUTTON_दायाँ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, तथ्य, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, तथ्य, SDL_BUTTON_X2, mouseID);

        तथ्य->mouse_button_flags = wParam;
    }
}

अटल व्योम WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_Window_तथ्य *तथ्य)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT कुंजी_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(शून्य, शून्य);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    कुंजी_State = Get_Async_कुंजी_State(VK_LBUTTON);
    अगर (!(कुंजी_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, तथ्य, SDL_BUTTON_बायाँ, mouseID);
    }
    कुंजी_State = Get_Async_कुंजी_State(VK_RBUTTON);
    अगर (!(कुंजी_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, तथ्य, SDL_BUTTON_दायाँ, mouseID);
    }
    कुंजी_State = Get_Async_कुंजी_State(VK_MBUTTON);
    अगर (!(कुंजी_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, तथ्य, SDL_BUTTON_मध्य, mouseID);
    }
    कुंजी_State = Get_Async_कुंजी_State(VK_XBUTTON1);
    अगर (!(कुंजी_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, तथ्य, SDL_BUTTON_X1, mouseID);
    }
    कुंजी_State = Get_Async_कुंजी_State(VK_XBUTTON2);
    अगर (!(कुंजी_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, तथ्य, SDL_BUTTON_X2, mouseID);
    }
    तथ्य->mouse_button_flags = (WPARAM)-1;
}

अटल व्योम WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    अगर (had_focus == has_focus || has_focus != expect_focus) {
        वापस;
    }

    अगर (has_focus) {
        POINT cursorPos;

        अगर (WIN_ShouldIgnoreFocusClick(तथ्य) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            अगर (Get_Async_कुंजी_State(VK_LBUTTON)) {
                तथ्य->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            अगर (Get_Async_कुंजी_State(VK_RBUTTON)) {
                तथ्य->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            अगर (Get_Async_कुंजी_State(VK_MBUTTON)) {
                तथ्य->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            अगर (Get_Async_कुंजी_State(VK_XBUTTON1)) {
                तथ्य->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            अगर (Get_Async_कुंजी_State(VK_XBUTTON2)) {
                तथ्य->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        अगर (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (भग्न)cursorPos.x, (भग्न)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), तथ्य);
        WIN_UpdateClipCursor(window);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(तथ्य->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_कुंजी_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_अंक, (Get_कुंजी_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_कुंजी_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_UpdateWindowICCProfile(तथ्य->window, true);
    } अन्यथा {
        तथ्य->in_window_deactivation = true;

        SDL_SetKeyboardFocus(शून्य);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        अगर (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(शून्य);
        }
        WIN_Reset_Dead_कुंजियाँ();

        WIN_UnclipCursorForWindow(window);

        तथ्य->in_window_deactivation = false;
    }
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

अटल bool ShouldGenerateWindowCloseOnAltF4(व्योम)
{
    वापस SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

अटल bool ShouldClearWindowOnEraseBackground(SDL_Window_तथ्य *तथ्य)
{
    चयन (तथ्य->hint_erase_background_mode) {
    हाल SDL_ERASEBACKGROUNDMODE_NEVER:
        वापस false;
    हाल SDL_ERASEBACKGROUNDMODE_INITIAL:
        वापस !तथ्य->videodata->cleared;
    हाल SDL_ERASEBACKGROUNDMODE_ALWAYS:
        वापस true;
    शेष:
        // Unexpected value, fallback to default behaviour
        वापस !तथ्य->videodata->cleared;
    }
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#घोषणा MI_WP_SIGNATURE      0xFF515700
#घोषणा MI_WP_SIGNATURE_MASK 0xFFFFFF00
#घोषणा IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

प्रकार क्रमागत
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

अटल SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    अगर (IsTouchEvent(extrainfo)) {
        अगर (extrainfo & 0x80) {
            वापस SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } अन्यथा {
            वापस SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    वापस SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

अटल SDL_Window_तथ्य *WIN_Get_Window_तथ्य_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    अगर (_this) {
        क्रम (window = _this->windows; window; window = window->अग्र) {
            SDL_Window_तथ्य *तथ्य = window->internal;
            अगर (तथ्य && तथ्य->hwnd == hwnd) {
                वापस तथ्य;
            }
        }
    }
    वापस शून्य;
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(पूर्णांक nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_तथ्य = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_तथ्य *तथ्य = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    अगर (nCode < 0 || nCode != HC_ACTION) {
        वापस Call_अग्र_Hook_Ex(शून्य, nCode, wParam, lParam);
    }
    अगर (hook_तथ्य->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        वापस 1;
    }

    चयन (hook_तथ्य->vkCode) {
    हाल VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        अवरोध;
    हाल VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        अवरोध;
    हाल VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        अवरोध;
    हाल VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        अवरोध;
    हाल VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        अवरोध;
    हाल VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        अवरोध;
    हाल VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        अवरोध;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    हाल VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        अवरोध;
    हाल VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        अवरोध;

    शेष:
        वापस Call_अग्र_Hook_Ex(शून्य, nCode, wParam, lParam);
    }

    अगर (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        अगर (!तथ्य->raw_keyboard_enabled) {
            SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, hook_तथ्य->scanCode, scanCode, true);
        }
    } अन्यथा {
        अगर (!तथ्य->raw_keyboard_enabled) {
            SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, hook_तथ्य->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        अगर (hook_तथ्य->vkCode <= 0xFF && तथ्य->pre_hook_कुंजी_state[hook_तथ्य->vkCode]) {
            तथ्य->pre_hook_कुंजी_state[hook_तथ्य->vkCode] = 0;
            वापस Call_अग्र_Hook_Ex(शून्य, nCode, wParam, lParam);
        }
    }

    वापस 1;
}

अटल bool WIN_SwapButtons(HANDLE hDevice)
{
    अगर (hDevice == शून्य) {
        // Touchpad, already has buttons swapped
        वापस false;
    }
    वापस GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

अटल व्योम WIN_Handle_Raw_Mouse_निवेश(Uint64 timestamp, SDL_Video_तथ्य *तथ्य, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    अटल काष्ठा {
        USHORT usButtonFlags;
        Uint8 button;
        bool down;
    } raw_buttons[] = {
        { RI_MOUSE_बायाँ_BUTTON_DOWN, SDL_BUTTON_बायाँ, true },
        { RI_MOUSE_बायाँ_BUTTON_UP, SDL_BUTTON_बायाँ, false },
        { RI_MOUSE_दायाँ_BUTTON_DOWN, SDL_BUTTON_दायाँ, true },
        { RI_MOUSE_दायाँ_BUTTON_UP, SDL_BUTTON_दायाँ, false },
        { RI_MOUSE_मध्य_BUTTON_DOWN, SDL_BUTTON_मध्य, true },
        { RI_MOUSE_मध्य_BUTTON_UP, SDL_BUTTON_मध्य, false },
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
    अगर (!तथ्य->raw_mouse_enabled) {
        वापस;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    अगर (!window) {
        वापस;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    अगर (!mouse) {
        वापस;
    }

    अगर (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        वापस;
    }

    SDL_Window_तथ्य *windowdata = window->internal;

    अगर (haveMotion && !windowdata->in_modal_loop) {
        अगर (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (भग्न)dx, (भग्न)dy);
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
            पूर्णांक x = raw_coordinates ? dx : (पूर्णांक)(((भग्न)dx / 65535.0f) * w);
            पूर्णांक y = raw_coordinates ? dy : (पूर्णांक)(((भग्न)dy / 65535.0f) * h);
            पूर्णांक relX, relY;

            /* Calculate relative motion */
            अगर (तथ्य->last_raw_mouse_position.x == 0 && तथ्य->last_raw_mouse_position.y == 0) {
                तथ्य->last_raw_mouse_position.x = x;
                तथ्य->last_raw_mouse_position.y = y;
            }
            relX = x - तथ्य->last_raw_mouse_position.x;
            relY = y - तथ्य->last_raw_mouse_position.y;

            अगर (remote_desktop) {
                अगर (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    अटल पूर्णांक wobble;
                    भग्न floatX = (भग्न)x / w;
                    भग्न floatY = (भग्न)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    अगर (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        पूर्णांक warpX = rect.बायाँ + ((rect.दायाँ - rect.बायाँ) / 2) + wobble;
                        पूर्णांक warpY = rect.शीर्ष + ((rect.bottom - rect.शीर्ष) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        अगर (wobble > 1) {
                            wobble = -1;
                        }
                    } अन्यथा {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        स्थिर पूर्णांक MAX_RELATIVE_MOTION = (h / 6);
                        अगर (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (भग्न)relX, (भग्न)relY);
                        }
                    }
                }
            } अन्यथा अगर (mouse->pen_mouse_events) {
                स्थिर पूर्णांक MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                अगर (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } अन्यथा {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (भग्न)relX, (भग्न)relY);
                }
            } अन्यथा {
                पूर्णांक screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                पूर्णांक screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                अगर (!तथ्य->raw_निवेश_fake_pen_id) {
                    तथ्य->raw_निवेश_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, शून्य, (व्योम *)(माप_प्रकार)-1, true);
                }
                SDL_SendPenMotion(timestamp, तथ्य->raw_निवेश_fake_pen_id, window, (भग्न)(x + screen_x - window->x), (भग्न)(y + screen_y - window->y));
            }

            तथ्य->last_raw_mouse_position.x = x;
            तथ्य->last_raw_mouse_position.y = y;
        }
    }

    अगर (haveButton) {
        क्रम (पूर्णांक i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            अगर (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                अगर (button == SDL_BUTTON_बायाँ) {
                    अगर (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_दायाँ;
                    }
                } अन्यथा अगर (button == SDL_BUTTON_दायाँ) {
                    अगर (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_बायाँ;
                    }
                }

                अगर (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    अगर (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    जारी;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        अगर (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_तथ्य;
            भग्न fAmount = (भग्न)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } अन्यथा अगर (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_तथ्य;
            भग्न fAmount = (भग्न)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

अटल व्योम WIN_Handle_Raw_Keyboard_निवेश(Uint64 timestamp, SDL_Video_तथ्य *तथ्य, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    अगर (!तथ्य->raw_keyboard_enabled) {
        वापस;
    }

    अगर (rawkeyboard->Flags & RI_कुंजी_E1) {
        // First key in a Ctrl+{key} sequence
        तथ्य->pending_E1_कुंजी_sequence = true;
        वापस;
    }

    अगर ((rawkeyboard->Flags & RI_कुंजी_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        वापस;
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(Map_Virtual_कुंजी(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#पूर्ण_अगर
    अगर (!rawkeyboard->MakeCode) {
        वापस;
    }

    bool down;
    चयन (rawkeyboard->Message) {
    हाल WM_KEYDOWN:
    हाल WM_SYSKEYDOWN:
        down = true;
        अवरोध;
    हाल WM_KEYUP:
    हाल WM_SYSKEYUP:
        down = false;
        अवरोध;
    शेष:
        down = !(rawkeyboard->Flags & RI_कुंजी_BREAK);
        अवरोध;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    अगर (तथ्य->pending_E1_कुंजी_sequence) {
        rawcode |= 0xE100;
        अगर (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } अन्यथा {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        तथ्य->pending_E1_कुंजी_sequence = false;
    } अन्यथा {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 सूचकांक = (Uint8)rawkeyboard->MakeCode;
        अगर (rawkeyboard->Flags & RI_कुंजी_E0) {
            rawcode |= 0xE000;
            सूचकांक |= 0x80;
        }
        code = windows_scancode_table[सूचकांक];
    }

    अगर (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        अगर ((!तथ्य->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_निवेश_active)) {
            वापस;
        }
    }

    SDL_Send_Keyboard_कुंजी(timestamp, keyboardID, rawcode, code, down);
}

व्योम WIN_Poll_Raw_निवेश(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    UINT आकार, i, गिनती, योग = 0;
    RAWINPUT *निवेश;
    Uint64 poll_finish;

    अगर (तथ्य->rawinput_offset == 0) {
        BOOL isWow64;

        तथ्य->rawinput_offset = माप(RAWINPUTHEADER);
        अगर (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            तथ्य->rawinput_offset += 8;
        }
    }

    // Get all available events
    निवेश = (RAWINPUT *)तथ्य->rawinput;
    क्रम (;;) {
        आकार = तथ्य->rawinput_आकार - (UINT)((BYTE *)निवेश - तथ्य->rawinput);
        गिनती = Get_Raw_निवेश_बफर(निवेश, &आकार, माप(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        अगर (गिनती == 0 || गिनती == (UINT)-1) {
            अगर (!तथ्य->rawinput || (गिनती == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_बफर)) {
                स्थिर UINT RAWINPUT_बफर_आकार_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(तथ्य->rawinput, तथ्य->rawinput_आकार + RAWINPUT_बफर_आकार_INCREMENT);
                अगर (!rawinput) {
                    अवरोध;
                }
                निवेश = (RAWINPUT *)(rawinput + ((BYTE *)निवेश - तथ्य->rawinput));
                तथ्य->rawinput = rawinput;
                तथ्य->rawinput_आकार += RAWINPUT_बफर_आकार_INCREMENT;
            } अन्यथा {
                अवरोध;
            }
        } अन्यथा {
            योग += गिनती;

            // Advance input to the end of the buffer
            जबतक (गिनती--) {
                निवेश = NEXTRAWINPUTBLOCK(निवेश);
            }
        }
    }

    अगर (योग > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_योग = 0;
        क्रम (i = 0, निवेश = (RAWINPUT *)तथ्य->rawinput; i < योग; ++i, निवेश = NEXTRAWINPUTBLOCK(निवेश)) {
            अगर (निवेश->header.dwType == RIM_TYPEMOUSE) {
                mouse_योग += 1;
            }
        }
        पूर्णांक mouse_सूचकांक = 0;
        क्रम (i = 0, निवेश = (RAWINPUT *)तथ्य->rawinput; i < योग; ++i, निवेश = NEXTRAWINPUTBLOCK(निवेश)) {
            अगर (निवेश->header.dwType == RIM_TYPEMOUSE) {
                mouse_सूचकांक += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)निवेश + तथ्य->rawinput_offset);
                Uint64 समय = poll_finish - (delta * (mouse_योग - mouse_सूचकांक)) / mouse_योग;
                WIN_Handle_Raw_Mouse_निवेश(समय, तथ्य, निवेश->header.hDevice, rawmouse);
            } अन्यथा अगर (निवेश->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)निवेश + तथ्य->rawinput_offset);
                WIN_Handle_Raw_Keyboard_निवेश(poll_finish, तथ्य, निवेश->header.hDevice, rawkeyboard);
            }
        }
    }
    तथ्य->last_rawinput_poll = poll_finish;
}

अटल व्योम AddDeviceID(Uint32 deviceID, Uint32 **list, पूर्णांक *गिनती)
{
    पूर्णांक new_गिनती = (*गिनती + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_गिनती * माप(*new_list));
    अगर (!new_list) {
        // Oh well, we'll drop this one
        वापस;
    }
    new_list[new_गिनती - 1] = deviceID;

    *गिनती = new_गिनती;
    *list = new_list;
}

अटल bool HasDeviceID(Uint32 deviceID, स्थिर Uint32 *list, पूर्णांक गिनती)
{
    क्रम (पूर्णांक i = 0; i < गिनती; ++i) {
        अगर (deviceID == list[i]) {
            वापस true;
        }
    }
    वापस false;
}

अटल अक्षर *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, स्थिर अक्षर *instance, Uint16 vendor, Uint16 product, स्थिर अक्षर *default_name, bool hid_loaded)
{
    अक्षर *vendor_name = शून्य;
    अक्षर *product_name = शून्य;
    अक्षर *name = शून्य;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    अगर (hid_loaded) {
        अक्षर devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = माप(devName) - 1;
        UINT len = Get_Raw_निवेश_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        अगर (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, शून्य, OPEN_EXISTING, 0, शून्य);
            अगर (hFile != INVALID_HANDLE_मूल्य) {
                SDL_HidD_GetManufacturerString(hFile, vend, माप(vend));
                SDL_HidD_GetProductString(hFile, prod, माप(prod));
                CloseHandle(hFile);
            }
        }
    }

    अगर (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    अगर (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } अन्यथा {
        SP_DEVINFO_तथ्य तथ्य;
        SDL_zero(तथ्य);
        तथ्य.cb_आकार = माप(तथ्य);
        क्रम (DWORD i = 0;; ++i) {
            अगर (!SetupDiEnumDeviceInfo(devinfo, i, &तथ्य)) {
                अगर (GetLastError() == ERROR_NO_MORE_वस्तुएँ) {
                    अवरोध;
                } अन्यथा {
                    जारी;
                }
            }

            अक्षर DeviceInstanceId[64];
            अगर (!SetupDiGetDeviceInstanceIdA(devinfo, &तथ्य, DeviceInstanceId, माप(DeviceInstanceId), शून्य))
                जारी;

            अगर (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD आकार = 0;
                अगर (SetupDiGetDeviceRegistryPropertyW(devinfo, &तथ्य, SPDRP_DEVICEDESC, शून्य, (PBYTE)prod, माप(prod), &आकार)) {
                    // Make sure the device description is null terminated
                    आकार /= माप(*prod);
                    अगर (आकार >= SDL_arraysize(prod)) {
                        // Truncated description...
                        आकार = (SDL_arraysize(prod) - 1);
                    }
                    prod[आकार] = 0;

                    अगर (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } अन्यथा {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                अवरोध;
            }
        }
    }

    अगर (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    वापस name;
}

व्योम WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = शून्य;
    UINT raw_device_गिनती = 0;
    पूर्णांक old_keyboard_गिनती = 0;
    SDL_KeyboardID *old_keyboards = शून्य;
    पूर्णांक new_keyboard_गिनती = 0;
    SDL_KeyboardID *new_keyboards = शून्य;
    पूर्णांक old_mouse_गिनती = 0;
    SDL_MouseID *old_mice = शून्य;
    पूर्णांक new_mouse_गिनती = 0;
    SDL_MouseID *new_mice = शून्य;

    अगर (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        वापस;
    }

    अगर ((Get_Raw_निवेश_Device_List(शून्य, &raw_device_गिनती, माप(RAWINPUTDEVICELIST)) == -1) || (!raw_device_गिनती)) {
        वापस; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(माप(RAWINPUTDEVICELIST) * raw_device_गिनती);
    अगर (!raw_devices) {
        वापस; // oh well.
    }

    raw_device_गिनती = Get_Raw_निवेश_Device_List(raw_devices, &raw_device_गिनती, माप(RAWINPUTDEVICELIST));
    अगर (raw_device_गिनती == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = शून्य;
        वापस; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(शून्य, शून्य, शून्य, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_गिनती);
    old_mice = SDL_GetMice(&old_mouse_गिनती);

    क्रम (UINT i = 0; i < raw_device_गिनती; i++) {
        RID_DEVICE_INFO rdi;
        अक्षर devName[MAX_PATH] = { 0 };
        UINT rdi_आकार = माप(rdi);
        UINT name_आकार = SDL_arraysize(devName);
        पूर्णांक vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        अक्षर *instance, *ptr, *name;

        अगर (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            जारी;
        }

        rdi.cb_आकार = माप(rdi);
        अगर (Get_Raw_निवेश_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_आकार) == ((UINT)-1) ||
            Get_Raw_निवेश_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_आकार) == ((UINT)-1)) {
            जारी;
        }

        // Extract the device instance
        instance = devName;
        जबतक (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        क्रम (ptr = instance; *ptr; ++ptr) {
            अगर (*ptr == '#') {
                *ptr = '\\';
            }
            अगर (*ptr == '{') {
                अगर (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                अवरोध;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        चयन (dwType) {
        हाल RIM_TYPEKEYBOARD:
            अगर (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dw_संख्या_Of_कुंजियाँ_योग)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_गिनती);
                अगर (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_गिनती)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            अवरोध;
        हाल RIM_TYPEMOUSE:
            अगर (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_गिनती);
                अगर (!HasDeviceID(mouseID, old_mice, old_mouse_गिनती)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            अवरोध;
        शेष:
            अवरोध;
        }
    }

    क्रम (पूर्णांक i = old_keyboard_गिनती; i--;) {
        अगर (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_गिनती)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    क्रम (पूर्णांक i = old_mouse_गिनती; i--;) {
        अगर (!HasDeviceID(old_mice[i], new_mice, new_mouse_गिनती)) {
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
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
अटल bool Skip_Alt_Gr_बायाँ_Control(WPARAM wParam, LPARAM lParam)
{
    अगर (wParam != VK_CONTROL) {
        वापस false;
    }

    // Is this an extended key (i.e. right key)?
    अगर (lParam & 0x01000000) {
        वापस false;
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    संदेश_2 अग्र_संदेश;
    DWORD संदेश_time = GetMessageTime();
    अगर (PeekMessage(&अग्र_संदेश, शून्य, 0, 0, PM_NOREMOVE)) {
        अगर (अग्र_संदेश.message == WM_KEYDOWN ||
            अग्र_संदेश.message == WM_SYSKEYDOWN) {
            अगर (अग्र_संदेश.wParam == VK_MENU && (अग्र_संदेश.lParam & 0x01000000) && अग्र_संदेश.समय == संदेश_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                वापस true;
            }
        }
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    वापस false;
}

अटल bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *संदेश, WPARAM *wParam, LPARAM *lParam)
{
    संदेश_2 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *संदेश;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    अगर (g_WindowsMessageHook(g_Windows_Message_Hook_तथ्य, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *संदेश = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        वापस true;
    }
    वापस false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam)
{
    SDL_Window_तथ्य *तथ्य;
    LRESULT returnCode = -1;

    // Get the window data for the window
    तथ्य = WIN_Get_Window_तथ्य_From_HWND(hwnd);
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (!तथ्य) {
        // Fallback
        तथ्य = (SDL_Window_तथ्य *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#पूर्ण_अगर
    अगर (!तथ्य) {
        वापस CallWindowProc(DefWindowProc, hwnd, संदेश, wParam, lParam);
    }

#अगर_घोषित WMMSG_DEBUG
    {
        अक्षर message[1024];
        अगर (संदेश > MAX_WMMSG) {
            SDL_snprintf(message, माप(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, संदेश, wParam, lParam);
        } अन्यथा {
            SDL_snprintf(message, माप(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[संदेश], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#पूर्ण_अगर // WMMSG_DEBUG


    अगर (g_WindowsMessageHook && तथ्य->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        अगर (!DispatchModalLoopMessageHook(&hwnd, &संदेश, &wParam, &lParam)) {
            वापस 0;
        }
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (WIN_HandleIMEMessage(hwnd, संदेश, wParam, &lParam, तथ्य->videodata)) {
        वापस 0;
    }
#पूर्ण_अगर

    चयन (संदेश) {

    हाल WM_SHOWWINDOW:
    {
        अगर (wParam) {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } अन्यथा {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } अवरोध;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    हाल WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        तथ्य->postpone_clipcursor = true;
        तथ्य->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        POINT pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(तथ्य->window, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        अगर (तथ्य->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } अवरोध;

    हाल WM_NCUAHDRAWCAPTION:
    हाल WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        अगर (तथ्य->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } अवरोध;

    हाल WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        स्थिर DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(तथ्य->window, !!LOWORD(wParam), &pos);
    } अवरोध;

    हाल WM_MOUSEACTIVATE:
    {
        अगर (SDL_WINDOW_IS_POPUP(तथ्य->window)) {
            वापस MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = तथ्य->window->parent;
        जबतक (parent) {
            अगर ((parent->flags & SDL_WINDOW_निवेश_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                वापस MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } अवरोध;

    हाल WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        स्थिर DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(तथ्य->window, true, &pos);
    } अवरोध;

    हाल WM_KILLFOCUS:
    हाल WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        स्थिर DWORD संदेश_Pos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(संदेश_Pos), GET_Y_LPARAM(संदेश_Pos) };
        WIN_UpdateFocus(तथ्य->window, false, &pos);
    } अवरोध;

    हाल WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिर UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेश_TYPE pointer_type = PT_POINTER;
        अगर (!तथ्य->videodata->GetPointerType) {
            अवरोध;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा अगर (!तथ्य->videodata->GetPointerType(pointerid, &pointer_type)) {
            अवरोध;  // oh well.
        } अन्यथा अगर (pointer_type != PT_PEN) {
            अवरोध;  // we only care about pens here.
        }

        व्योम *hpointer = (व्योम *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिर SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        अगर (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, तथ्य->window, true, true);
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
            SDL_AddPenDevice(WIN_GetEventTimestamp(), शून्य, तथ्य->window, &info, hpointer, true);
        }
        returnCode = 0;
    } अवरोध;

    हाल WM_POINTERCAPTURECHANGED:
    हाल WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिर UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेश_TYPE pointer_type = PT_POINTER;
        अगर (!तथ्य->videodata->GetPointerType) {
            अवरोध;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा अगर (!तथ्य->videodata->GetPointerType(pointerid, &pointer_type)) {
            अवरोध;  // oh well.
        } अन्यथा अगर (pointer_type != PT_PEN) {
            अवरोध;  // we only care about pens here.
        }

        व्योम *hpointer = (व्योम *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिर SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        अगर (pen == 0) {
            अवरोध;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        अगर ((संदेश == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, तथ्य->window, false, false);
        }
        returnCode = 0;
    } अवरोध;

    हाल WM_POINTERDOWN:
    हाल WM_POINTERUP:
    हाल WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        स्थिर UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेश_TYPE pointer_type = PT_POINTER;
        अगर (!तथ्य->videodata->GetPointerType || !तथ्य->videodata->GetPointerType(pointerid, &pointer_type)) {
            अवरोध;  // oh well.
        } अन्यथा अगर ((संदेश == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            तथ्य->last_pointer_update = lParam;
            returnCode = 0;
            अवरोध;
        } अन्यथा अगर (pointer_type != PT_PEN) {
            अवरोध; // we only care about pens here.
        }

        व्योम *hpointer = (व्योम *)(माप_प्रकार)1; // just something > 0. We're using this one ID any possible pen.
        स्थिर SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        अगर (pen == 0) {
            अवरोध;  // not a pen, or not a pen we already knew about.
        } अन्यथा अगर (!तथ्य->videodata->GetPointerPenInfo || !तथ्य->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            अवरोध;  // oh well.
        }

        स्थिर Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = तथ्य->window;

        स्थिर bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        अगर (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        स्थिर POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        भग्न fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        अगर (!तथ्य->videodata->GetPointerDeviceRects || !तथ्य->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(तथ्य->hwnd, &position);
            fx = (भग्न) position.x;
            fy = (भग्न) position.y;
        } अन्यथा {
            पूर्णांक ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            स्थिर SDL_FPoint window_pos = { (भग्न) ix, (भग्न) iy };

            स्थिर भग्न facX = pointer_info->ptHimetricLocationRaw.x / (भग्न) (tablet_bounds.दायाँ );
            स्थिर भग्न facY = pointer_info->ptHimetricLocationRaw.y / (भग्न) (tablet_bounds.bottom);

            स्थिर भग्न w = tablet_mapping.दायाँ  - tablet_mapping.बायाँ;
            स्थिर भग्न h = tablet_mapping.bottom - tablet_mapping.शीर्ष;

            fx = (tablet_mapping.बायाँ + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.शीर्ष  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        अगर (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((भग्न) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        अगर (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((भग्न) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        अगर (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((भग्न) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        अगर (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((भग्न) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        अगर (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } अवरोध;

    हाल WM_MOUSEMOVE:
    {
        SDL_Window *window = तथ्य->window;

        अगर (window->flags & SDL_WINDOW_निवेश_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            अगर (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                तथ्य->clipcursor_queued = true;
            }
        }

        अगर (!तथ्य->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_आकार = माप(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = तथ्य->hwnd;

            अगर (TrackMouseEvent(&trackMouseEvent)) {
                तथ्य->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), तथ्य);
        }

        अगर (!तथ्य->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            अगर (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != तथ्य->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (भग्न)GET_X_LPARAM(lParam), (भग्न)GET_Y_LPARAM(lParam));
            }
        }

    } अवरोध;

    हाल WM_LBUTTONUP:
    हाल WM_RBUTTONUP:
    हाल WM_MBUTTONUP:
    हाल WM_XBUTTONUP:
    हाल WM_LBUTTONDOWN:
    हाल WM_LBUTTONDBLCLK:
    हाल WM_RBUTTONDOWN:
    हाल WM_RBUTTONDBLCLK:
    हाल WM_MBUTTONDOWN:
    हाल WM_MBUTTONDBLCLK:
    हाल WM_XBUTTONDOWN:
    हाल WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        अगर (!तथ्य->videodata->raw_mouse_enabled) {
            अगर (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != तथ्य->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, तथ्य, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } अवरोध;

#अगर 0   // We handle raw input all at once instead of using a syscall for each mouse event
    हाल WM_निवेश:
    {
        HRAWINPUT h_Raw_निवेश = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT आकार = माप(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        अगर (तथ्य->window != SDL_GetKeyboardFocus()) {
            अवरोध;
        }

        Get_Raw_निवेश_तथ्य(h_Raw_निवेश, RID_निवेश, &inp, &आकार, माप(RAWINPUTHEADER));
        अगर (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_निवेश(WIN_GetEventTimestamp(), तथ्य, inp.header.hDevice, &inp.तथ्य.mouse);
        } अन्यथा अगर (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_निवेश(WIN_GetEventTimestamp(), तथ्य, inp.header.hDevice, &inp.तथ्य.keyboard);
        }
    } अवरोध;
#पूर्ण_अगर

    हाल WM_MOUSEWHEEL:
    हाल WM_MOUSEHWHEEL:
    {
        अगर (!तथ्य->videodata->raw_mouse_enabled) {
            लघु amount = GET_WHEEL_DELTA_WPARAM(wParam);
            भग्न fAmount = (भग्न)amount / WHEEL_DELTA;
            अगर (संदेश == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), तथ्य->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } अन्यथा {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), तथ्य->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } अवरोध;

    हाल WM_MOUSELEAVE:
        अगर (!(तथ्य->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            अगर (SDL_GetMouseFocus() == तथ्य->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                अगर (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), तथ्य->window, SDL_GLOBAL_MOUSE_ID, false, (भग्न)cursorPos.x, (भग्न)cursorPos.y);
                } अन्यथा {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    अगर (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), तथ्य->window, SDL_TOUCH_MOUSEID, false, (भग्न)cursorPos.x, (भग्न)cursorPos.y);
                    } अन्यथा { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), तथ्य->window, SDL_GLOBAL_MOUSE_ID, false, (भग्न)cursorPos.x, (भग्न)cursorPos.y);
                    }
                }
            }

            अगर (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(शून्य);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        तथ्य->mouse_tracked = false;

        returnCode = 0;
        अवरोध;
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    हाल WM_KEYDOWN:
    हाल WM_SYSKEYDOWN:
    {
        अगर (Skip_Alt_Gr_बायाँ_Control(wParam, lParam)) {
            returnCode = 0;
            अवरोध;
        }

        bool virtual_कुंजी = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_कुंजी);

        // Detect relevant keyboard shortcuts
        अगर (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            अगर (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        अगर (virtual_कुंजी || !तथ्य->videodata->raw_keyboard_enabled || तथ्य->window->text_निवेश_active) {
            SDL_Send_Keyboard_कुंजी(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        अवरोध;

    हाल WM_SYSKEYUP:
    हाल WM_KEYUP:
    {
        अगर (Skip_Alt_Gr_बायाँ_Control(wParam, lParam)) {
            returnCode = 0;
            अवरोध;
        }

        bool virtual_कुंजी = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_कुंजी);
        स्थिर bool *keyboardState = SDL_GetKeyboardState(शून्य);

        अगर (virtual_कुंजी || !तथ्य->videodata->raw_keyboard_enabled || तथ्य->window->text_निवेश_active) {
            अगर (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_Send_Keyboard_कुंजी(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_Send_Keyboard_कुंजी(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        अवरोध;

    हाल WM_UNICHAR:
        अगर (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } अन्यथा {
            अगर (SDL_Text_निवेश_Active(तथ्य->window)) {
                अक्षर text[5];
                अक्षर *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        अवरोध;

    हाल WM_CHAR:
        अगर (SDL_Text_निवेश_Active(तथ्य->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            अगर (IS_ऊपरी_SURROGATE(wParam)) {
                तथ्य->ऊपरी_surrogate = (WCHAR)wParam;
            } अन्यथा {
                WCHAR utf16[3];

                utf16[0] = तथ्य->ऊपरी_surrogate ? तथ्य->ऊपरी_surrogate : (WCHAR)wParam;
                utf16[1] = तथ्य->ऊपरी_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                अक्षर utf8[5];
                पूर्णांक परिणाम = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, माप(utf8), शून्य, शून्य);
                अगर (परिणाम > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                तथ्य->ऊपरी_surrogate = L'\0';
            }
        } अन्यथा {
            तथ्य->ऊपरी_surrogate = L'\0';
        }

        returnCode = 0;
        अवरोध;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#अगर_घोषित WM_INPUTLANGCHANGE
    हाल WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        अवरोध;
#पूर्ण_अगर // WM_INPUTLANGCHANGE

    हाल WM_NCLBUTTONDOWN:
    {
        तथ्य->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        अगर (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } अवरोध;

    हाल WM_CAPTURECHANGED:
    {
        तथ्य->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), तथ्य);
    } अवरोध;

#अगर_घोषित WM_GETMINMAXINFO
    हाल WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT आकार;
        पूर्णांक x, y;
        पूर्णांक w, h;
        पूर्णांक min_w, min_h;
        पूर्णांक max_w, max_h;
        BOOL constrain_max_आकार;

        // If this is an expected size change, allow it
        अगर (तथ्य->expected_resize) {
            अवरोध;
        }

        // Get the current position of our window
        GetWindowRect(hwnd, &आकार);
        x = आकार.बायाँ;
        y = आकार.शीर्ष;

        // Calculate current size of our window
        SDL_Get_Window_आकार(तथ्य->window, &w, &h);
        SDL_Get_Window_Minimum_आकार(तथ्य->window, &min_w, &min_h);
        SDL_Get_Window_Maximum_आकार(तथ्य->window, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        अगर (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_आकार = TRUE;
        } अन्यथा {
            constrain_max_आकार = FALSE;
        }

        अगर (!(SDL_GetWindowFlags(तथ्य->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(तथ्य->window)) {
            आकार.शीर्ष = 0;
            आकार.बायाँ = 0;
            आकार.bottom = h;
            आकार.दायाँ = w;
            WIN_AdjustWindowRectForHWND(hwnd, &आकार, 0);
            w = आकार.दायाँ - आकार.बायाँ;
            h = आकार.bottom - आकार.शीर्ष;
#अगर_घोषित HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#पूर्ण_अगर
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        अगर (SDL_GetWindowFlags(तथ्य->window) & SDL_WINDOW_RESIZABLE) {
            अगर (SDL_GetWindowFlags(तथ्य->window) & SDL_WINDOW_BORDERLESS) {
                पूर्णांक screenW = GetSystemMetrics(SM_CXSCREEN);
                पूर्णांक screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_आकार.x = SDL_max(w, screenW);
                info->pt_Max_आकार.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_आकार.x = (LONG)w + min_w;
            info->pt_Min_Track_आकार.y = (LONG)h + min_h;
            अगर (constrain_max_आकार) {
                info->pt_Max_Track_आकार.x = (LONG)w + max_w;
                info->pt_Max_Track_आकार.y = (LONG)h + max_h;
            }
        } अन्यथा {
            info->pt_Max_आकार.x = w;
            info->pt_Max_आकार.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_आकार.x = w;
            info->pt_Min_Track_आकार.y = h;
            info->pt_Max_Track_आकार.x = w;
            info->pt_Max_Track_आकार.y = h;
        }
    }
        returnCode = 0;
        अवरोध;
#पूर्ण_अगर // WM_GETMINMAXINFO

    हाल WM_WINDOWPOSCHANGING:

        अगर (तथ्य->expected_resize) {
            returnCode = 0;
        } अन्यथा अगर (तथ्य->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            अगर (तथ्य->last_modal_width == windowpos->cx && तथ्य->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            तथ्य->last_modal_width = windowpos->cx;
            तथ्य->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        अवरोध;

    हाल WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        स्थिर SDL_DisplayID original_displayID = तथ्य->window->displayID;
        स्थिर WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        पूर्णांक x, y;
        पूर्णांक w, h;

        अगर (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        अगर (iconic) {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } अन्यथा अगर (zoomed) {
            अगर (तथ्य->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            तथ्य->force_ws_maximizebox = true;
        } अन्यथा अगर (तथ्य->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            अगर (!(तथ्य->window->flags & SDL_WINDOW_FULLSCREEN)) {
                तथ्य->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), तथ्य->window, !!(तथ्य->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        अगर (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        अगर (iconic) {
            अवरोध;
        }

        अगर (तथ्य->initializing) {
            अवरोध;
        }

        अगर (!तथ्य->disable_move_आकार_events) {
            अगर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.बायाँ;
                y = rect.शीर्ष;

                SDL_GlobalToRelativeForWindow(तथ्य->window, x, y, &x, &y);
                SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            अगर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.दायाँ;
                h = rect.bottom;

                SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(तथ्य->window);

        // Update the window display position
        अगर (तथ्य->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(तथ्य->window, true);
        }

        // Update the position of any child windows
        क्रम (win = तथ्य->window->first_child; win; win = win->अग्र_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            अगर (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } अवरोध;

    हाल WM_ENTERSIZEMOVE:
    हाल WM_ENTERMENULOOP:
    {
        अगर (g_WindowsMessageHook) {
            अगर (!DispatchModalLoopMessageHook(&hwnd, &संदेश, &wParam, &lParam)) {
                वापस 0;
            }
        }

        ++तथ्य->in_modal_loop;
        अगर (तथ्य->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(तथ्य->hwnd, &rect);
            तथ्य->last_modal_width = rect.दायाँ - rect.बायाँ;
            तथ्य->last_modal_height = rect.bottom - rect.शीर्ष;

            तथ्य->initial_आकार_rect.बायाँ = तथ्य->window->x;
            तथ्य->initial_आकार_rect.दायाँ = तथ्य->window->x + तथ्य->window->w;
            तथ्य->initial_आकार_rect.शीर्ष = तथ्य->window->y;
            तथ्य->initial_आकार_rect.bottom = तथ्य->window->y + तथ्य->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, शून्य);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } अवरोध;

    हाल WM_TIMER:
    {
        अगर (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(तथ्य->window);

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#अगर 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            अगर (तथ्य->videodata->DwmFlush) {
                तथ्य->videodata->DwmFlush();
            }
#पूर्ण_अगर
#पूर्ण_अगर
            वापस 0;
        }
    } अवरोध;

    हाल WM_EXITSIZEMOVE:
    हाल WM_EXITMENULOOP:
    {
        --तथ्य->in_modal_loop;
        अगर (तथ्य->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } अवरोध;

    हाल WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (तथ्य->window->max_aspect == तथ्य->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            भग्न new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            अगर (तथ्य->window->min_aspect <= 0 && तथ्य->window->max_aspect <= 0) {
                अवरोध;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            अगर (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != शून्य, GetWindowExStyle(hwnd))) {
                अवरोध;
            }

            clientDragRect.बायाँ -= rc.बायाँ;
            clientDragRect.शीर्ष -= rc.शीर्ष;
            clientDragRect.दायाँ -= rc.दायाँ;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.दायाँ - clientDragRect.बायाँ;
            h = clientDragRect.bottom - clientDragRect.शीर्ष;
            new_aspect = w / (भग्न)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            अगर (lock_aspect_ratio) {
                चयन (edge) {
                हाल WMSZ_बायाँ:
                हाल WMSZ_दायाँ:
                    h = (पूर्णांक)SDL_roundf(w / तथ्य->window->max_aspect);
                    अवरोध;
                शेष:
                    // resizing via corners or top or bottom
                    w = (पूर्णांक)SDL_roundf(h * तथ्य->window->max_aspect);
                    अवरोध;
                }
            } अन्यथा {
                चयन (edge) {
                हाल WMSZ_बायाँ:
                हाल WMSZ_दायाँ:
                    अगर (तथ्य->window->max_aspect > 0.0f && new_aspect > तथ्य->window->max_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * तथ्य->window->max_aspect);
                    } अन्यथा अगर (तथ्य->window->min_aspect > 0.0f && new_aspect < तथ्य->window->min_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * तथ्य->window->min_aspect);
                    }
                    अवरोध;
                हाल WMSZ_शीर्ष:
                हाल WMSZ_BOTTOM:
                    अगर (तथ्य->window->min_aspect > 0.0f && new_aspect < तथ्य->window->min_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / तथ्य->window->min_aspect);
                    } अन्यथा अगर (तथ्य->window->max_aspect > 0.0f && new_aspect > तथ्य->window->max_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / तथ्य->window->max_aspect);
                    }
                    अवरोध;

                शेष:
                    // resizing via corners
                    अगर (तथ्य->window->max_aspect > 0.0f && new_aspect > तथ्य->window->max_aspect) {
                        w = (पूर्णांक)SDL_roundf(h * तथ्य->window->max_aspect);
                    } अन्यथा अगर (तथ्य->window->min_aspect > 0.0f && new_aspect < तथ्य->window->min_aspect) {
                        h = (पूर्णांक)SDL_roundf(w / तथ्य->window->min_aspect);
                    }
                    अवरोध;
                }
            }

            चयन (edge) {
            हाल WMSZ_बायाँ:
                clientDragRect.बायाँ = clientDragRect.दायाँ - w;
                अगर (lock_aspect_ratio) {
                    clientDragRect.शीर्ष = (तथ्य->initial_आकार_rect.bottom + तथ्य->initial_आकार_rect.शीर्ष - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                अवरोध;
            हाल WMSZ_BOTTOMLEFT:
                clientDragRect.बायाँ = clientDragRect.दायाँ - w;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                अवरोध;
            हाल WMSZ_दायाँ:
                clientDragRect.दायाँ = w + clientDragRect.बायाँ;
                अगर (lock_aspect_ratio) {
                    clientDragRect.शीर्ष = (तथ्य->initial_आकार_rect.bottom + तथ्य->initial_आकार_rect.शीर्ष - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                अवरोध;
            हाल WMSZ_TOPRIGHT:
                clientDragRect.दायाँ = w + clientDragRect.बायाँ;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                अवरोध;
            हाल WMSZ_शीर्ष:
                अगर (lock_aspect_ratio) {
                    clientDragRect.बायाँ = (तथ्य->initial_आकार_rect.दायाँ + तथ्य->initial_आकार_rect.बायाँ - w) / 2;
                }
                clientDragRect.दायाँ = w + clientDragRect.बायाँ;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                अवरोध;
            हाल WMSZ_TOPLEFT:
                clientDragRect.बायाँ = clientDragRect.दायाँ - w;
                clientDragRect.शीर्ष = clientDragRect.bottom - h;
                अवरोध;
            हाल WMSZ_BOTTOM:
                अगर (lock_aspect_ratio) {
                    clientDragRect.बायाँ = (तथ्य->initial_आकार_rect.दायाँ + तथ्य->initial_आकार_rect.बायाँ - w) / 2;
                }
                clientDragRect.दायाँ = w + clientDragRect.बायाँ;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                अवरोध;
            हाल WMSZ_BOTTOMRIGHT:
                clientDragRect.दायाँ = w + clientDragRect.बायाँ;
                clientDragRect.bottom = h + clientDragRect.शीर्ष;
                अवरोध;
            }

            // convert the client rect to a window rect
            अगर (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != शून्य, GetWindowExStyle(hwnd))) {
                अवरोध;
            }

            *dragRect = clientDragRect;
        }
        अवरोध;

    हाल WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        अगर (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } अन्यथा अगर (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(शून्य);
            returnCode = TRUE;
        }
    } अवरोध;

        // We were occluded, refresh our display
    हाल WM_PAINT:
    {
        RECT rect;
        अगर (GetUpdateRect(hwnd, &rect, FALSE)) {
            स्थिर LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            अगर (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, शून्य);
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        अवरोध;

        // We'll do our own drawing, prevent flicker
    हाल WM_ERASEBKGND:
        अगर (ShouldClearWindowOnEraseBackground(तथ्य)) {
            RECT client_rect;
            HBRUSH brush;
            तथ्य->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        वापस 1;

    हाल WM_SYSCOMMAND:
    {
        अगर (!g_WindowsEnableMenuMnemonics) {
            अगर ((wParam & 0xFFF0) == SC_KEYMENU) {
                वापस 0;
            }
        }

#अगर defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        अगर ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            अगर (SDL_GetVideoDevice()->suspend_screensaver) {
                वापस 0;
            }
        }
#पूर्ण_अगर // System has screensaver support
    } अवरोध;

    हाल WM_CLOSE:
    {
        SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        अवरोध;

    हाल WM_TOUCH:
        अगर (तथ्य->videodata->Get_Touch_निवेश_Info && तथ्य->videodata->Close_Touch_निवेश_Handle) {
            UINT i, अंक_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, अंक_inputs, &isstack);
            अगर (inputs && तथ्य->videodata->Get_Touch_निवेश_Info((HTOUCHINPUT)lParam, अंक_inputs, inputs, माप(TOUCHINPUT))) {
                RECT rect;
                भग्न x, y;

                अगर (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    अगर (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    अवरोध;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.शीर्ष *= 100;
                rect.बायाँ *= 100;
                rect.bottom *= 100;
                rect.दायाँ *= 100;

                क्रम (i = 0; i < अंक_inputs; ++i) {
                    PTOUCHINPUT निवेश = &inputs[i];
                    स्थिर पूर्णांक w = (rect.दायाँ - rect.बायाँ);
                    स्थिर पूर्णांक h = (rect.bottom - rect.शीर्ष);

                    स्थिर SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)निवेश->hSource);
                    स्थिर SDL_FingerID fingerId = (निवेश->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    अगर (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (निवेश->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        जारी;
                    }

                    // Get the normalized coordinates for the window
                    अगर (w <= 1) {
                        x = 0.5f;
                    } अन्यथा {
                        x = (भग्न)(निवेश->x - rect.बायाँ) / (w - 1);
                    }
                    अगर (h <= 1) {
                        y = 0.5f;
                    } अन्यथा {
                        y = (भग्न)(निवेश->y - rect.शीर्ष) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    अगर (निवेश->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, तथ्य->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    अगर (निवेश->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, तथ्य->window, x, y, 1.0f);
                    }
                    अगर (निवेश->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, तथ्य->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            तथ्य->videodata->Close_Touch_निवेश_Handle((HTOUCHINPUT)lParam);
            वापस 0;
        }
        अवरोध;

#अगर_घोषित HAVE_TPCSHRD_H

    हाल WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        वापस TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#पूर्ण_अगर // HAVE_TPCSHRD_H

    हाल WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT गिनती = DragQueryFile(drop, 0xFFFFFFFF, शून्य, 0);
        क्रम (i = 0; i < गिनती; ++i) {
            UINT आकार = DragQueryFile(drop, i, शून्य, 0) + 1;
            LPTSTR बफर_2 = (LPTSTR)SDL_malloc(माप(TCHAR) * आकार);
            अगर (बफर_2) {
                अगर (DragQueryFile(drop, i, बफर_2, आकार)) {
                    अक्षर *file = WIN_StringToUTF8(बफर_2);
                    SDL_SendDropFile(तथ्य->window, शून्य, file);
                    SDL_free(file);
                }
                SDL_free(बफर_2);
            }
        }
        SDL_SendDropComplete(तथ्य->window);
        DragFinish(drop);
        वापस 0;
    }

    हाल WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } अवरोध;

    हाल WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = तथ्य->window->flags;
        अगर (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            अगर (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                अगर (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    स्थिर POINT pt = { तथ्य->window->windowed.x, तथ्य->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                अगर (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_आकार = माप(info);
                    अगर (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } अन्यथा अगर (!(window_flags & SDL_WINDOW_RESIZABLE) && !तथ्य->force_ws_maximizebox) {
                पूर्णांक w, h;
                अगर (तथ्य->window->last_आकार_pending) {
                    w = तथ्य->window->pending.w;
                    h = तथ्य->window->pending.h;
                } अन्यथा {
                    w = तथ्य->window->floating.w;
                    h = तथ्य->window->floating.h;
                }
                params->rgrc[0].दायाँ = params->rgrc[0].बायाँ + w;
                params->rgrc[0].bottom = params->rgrc[0].शीर्ष + h;
            }
            वापस 0;
        }
    } अवरोध;

    हाल WM_NCHITTEST:
    {
        SDL_Window *window = तथ्य->window;

        अगर (window->flags & SDL_WINDOW_TOOLTIP) {
            वापस HTTRANSPARENT;
        }

        अगर (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            अगर (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_Hit_Test_परिणाम rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_तथ्य);
                चयन (rc) {
#घोषणा POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        वापस ret;                                                        \
    }
                हाल SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(शून्य, शून्य);
                    अगर (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        वापस HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                हाल SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                हाल SDL_HITTEST_RESIZE_शीर्ष:
                    POST_HIT_TEST(HTTOP);
                हाल SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                हाल SDL_HITTEST_RESIZE_दायाँ:
                    POST_HIT_TEST(HTRIGHT);
                हाल SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                हाल SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                हाल SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                हाल SDL_HITTEST_RESIZE_बायाँ:
                    POST_HIT_TEST(HTLEFT);
#अघोषित POST_HIT_TEST
                हाल SDL_HITTEST_NORMAL:
                    वापस HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } अवरोध;

    हाल WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        अगर (तथ्य->videodata->GetDpiForWindow && तथ्य->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            स्थिर पूर्णांक अग्र_DPI = (पूर्णांक)wParam;
            स्थिर पूर्णांक पूर्व_DPI = (पूर्णांक)तथ्य->videodata->GetDpiForWindow(hwnd);
            आकार_3 *आकार_In_Out = (आकार_3 *)lParam;

            पूर्णांक frame_w, frame_h;
            पूर्णांक query_client_w_win, query_client_h_win;

#अगर_घोषित HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    पूर्व_DPI, अग्र_DPI, आकार_In_Out->cx, आकार_In_Out->cy);
#पूर्ण_अगर

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                अगर (!(तथ्य->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(तथ्य->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, पूर्व_DPI);
                }

                frame_w = -rect.बायाँ + rect.दायाँ;
                frame_h = -rect.शीर्ष + rect.bottom;

                query_client_w_win = आकार_In_Out->cx - frame_w;
                query_client_h_win = आकार_In_Out->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.दायाँ = query_client_w_win;
                rect.bottom = query_client_h_win;

                अगर (!(तथ्य->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(तथ्य->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, अग्र_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                आकार_In_Out->cx = rect.दायाँ - rect.बायाँ;
                आकार_In_Out->cy = rect.bottom - rect.शीर्ष;
            }

#अगर_घोषित HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", आकार_In_Out->cx, आकार_In_Out->cy);
#पूर्ण_अगर
            वापस TRUE;
        }
        अवरोध;

    हाल WM_DPICHANGED:
        // Windows 8.1+
        {
            स्थिर पूर्णांक newDPI = HIWORD(wParam);
            RECT *स्थिर suggestedRect = (RECT *)lParam;
            पूर्णांक w, h;

#अगर_घोषित HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->बायाँ, suggestedRect->शीर्ष, suggestedRect->दायाँ - suggestedRect->बायाँ, suggestedRect->bottom - suggestedRect->शीर्ष);
#पूर्ण_अगर

            अगर (तथ्य->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#अगर_घोषित HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#पूर्ण_अगर
                वापस 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.दायाँ = तथ्य->window->w;
                rect.bottom = तथ्य->window->h;

                अगर (!(तथ्य->window->flags & SDL_WINDOW_BORDERLESS)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, newDPI);
                }

                w = rect.दायाँ - rect.बायाँ;
                h = rect.bottom - rect.शीर्ष;
            }

#अगर_घोषित HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    तथ्य->window->w, तथ्य->window->h,
                    suggestedRect->बायाँ, suggestedRect->शीर्ष, w, h);
#पूर्ण_अगर

            तथ्य->expected_resize = true;
            SetWindowPos(hwnd,
                         शून्य,
                         suggestedRect->बायाँ,
                         suggestedRect->शीर्ष,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            तथ्य->expected_resize = false;
            वापस 0;
        }

    हाल WM_SETTINGCHANGE:
        अगर (wParam == 0 && lParam != 0 && SDL_wcscmp((ब_अक्षर_प्रकार *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        अगर (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        अगर (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        अवरोध;
#अन्यथा
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    हाल WM_आकार:
    {
        RECT rect;
        पूर्णांक w, h;

        अगर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.दायाँ;
            h = rect.bottom;
            SDL_SendWindowEvent(तथ्य->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } अवरोध;
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    शेष:
        अवरोध;
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (संदेश && संदेश == तथ्य->videodata->WM_TASKBAR_BUTTON_CREATED) {
        तथ्य->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), तथ्य->window);
    }
#पूर्ण_अगर

    // If there's a window proc, assume it's going to handle messages
    अगर (तथ्य->wndproc) {
        वापस CallWindowProc(तथ्य->wndproc, hwnd, संदेश, wParam, lParam);
    } अन्यथा अगर (returnCode >= 0) {
        वापस returnCode;
    } अन्यथा {
        वापस CallWindowProc(DefWindowProc, hwnd, संदेश, wParam, lParam);
    }
}

पूर्णांक WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    अगर (g_WindowsEnableMessageLoop) {
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = संदेश_Wait_For_Multiple_Objects(0, शून्य, FALSE, timeout, QS_ALLINPUT);
        अगर (ret == WAIT_OBJECT_0) {
            वापस 1;
        } अन्यथा {
            वापस 0;
        }
#अन्यथा
        // MsgWaitForMultipleObjects is desktop-only.
        संदेश_2 संदेश;
        BOOL message_परिणाम;
        UINT_PTR timer_id = 0;
        अगर (timeoutNS > 0) {
            timer_id = SetTimer(शून्य, 0, (UINT)SDL_NS_TO_MS(timeoutNS), शून्य);
            message_परिणाम = GetMessage(&संदेश, 0, 0, 0);
            KillTimer(शून्य, timer_id);
        } अन्यथा अगर (timeoutNS == 0) {
            message_परिणाम = PeekMessage(&संदेश, शून्य, 0, 0, PM_REMOVE);
        } अन्यथा {
            message_परिणाम = GetMessage(&संदेश, 0, 0, 0);
        }
        अगर (message_परिणाम) {
            अगर (संदेश.message == WM_TIMER && !संदेश.hwnd && संदेश.wParam == timer_id) {
                वापस 0;
            }
            अगर (g_WindowsMessageHook) {
                अगर (!g_WindowsMessageHook(g_Windows_Message_Hook_तथ्य, &संदेश)) {
                    वापस 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
            वापस 1;
        } अन्यथा {
            वापस 0;
        }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } अन्यथा {
        // Fail the wait so the caller falls back to polling
        वापस -1;
    }
}

व्योम WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    PostMessage(तथ्य->hwnd, तथ्य->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
व्योम WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    संदेश_2 संदेश;

    अगर (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        जबतक (PeekMessage(&संदेश, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(संदेश.समय);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
        }

        SDL_processing_messages = false;
    }
}

व्योम WIN_PumpEvents(SDL_VideoDevice *_this)
{
    संदेश_2 संदेश;
#अगर_घोषित _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#आशय warning(धकेलो)
#आशय warning(disable : 28159)
#पूर्ण_अगर
    DWORD end_ticks = Get_Tick_गिनती() + 1;
#अगर_घोषित _MSC_VER
#आशय warning(निकालो)
#पूर्ण_अगर
    पूर्णांक new_messages = 0;

    अगर (_this->internal->gameinput_context) {
        WIN_Update_Game_निवेश(_this);
    }

    अगर (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        जबतक (PeekMessage(&संदेश, शून्य, 0, 0, PM_REMOVE)) {
            अगर (g_WindowsMessageHook) {
                अगर (!g_WindowsMessageHook(g_Windows_Message_Hook_तथ्य, &संदेश)) {
                    जारी;
                }
            }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            अगर (संदेश.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                अगर (!SDL_TICKS_PASSED(संदेश.समय, (SDL_last_warp_time + 1))) {
                    जारी;
                }

                // This mouse message happened after the warp
                SDL_last_warp_time = 0;
            }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_SetMessageTick(संदेश.समय);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            अगर (SDL_TICKS_PASSED(संदेश.समय, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                स्थिर पूर्णांक MAX_NEW_MESSAGES = 3;
                ++new_messages;
                अगर (new_messages > MAX_NEW_MESSAGES) {
                    अवरोध;
                }
            }
        }

        SDL_processing_messages = false;
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    स्थिर bool *keystate = SDL_GetKeyboardState(शून्य);
    अगर (keystate[SDL_SCANCODE_LSHIFT] && !(Get_कुंजी_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    अगर (keystate[SDL_SCANCODE_RSHIFT] && !(Get_कुंजी_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    अगर (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        अगर (keystate[SDL_SCANCODE_LGUI] && !(Get_कुंजी_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        अगर (keystate[SDL_SCANCODE_RGUI] && !(Get_कुंजी_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    अगर (_this) {
        SDL_Window *window = _this->windows;
        जबतक (window) {
            bool refresh_clipcursor = false;
            SDL_Window_तथ्य *तथ्य = window->internal;
            अगर (तथ्य) {
                refresh_clipcursor = तथ्य->clipcursor_queued;
                तथ्य->clipcursor_queued = false;    // Must be cleared unconditionally.
                तथ्य->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            अगर (refresh_clipcursor) {
                WIN_UpdateClipCursor(window);
            }
            window = window->अग्र;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focusWindow = SDL_GetKeyboardFocus();
    अगर (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_Window_तथ्य *तथ्य = focusWindow->internal;

        अगर (!तथ्य->mouse_tracked) {
            POINT cursorPos;

            अगर (GetCursorPos(&cursorPos) && ScreenToClient(तथ्य->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), तथ्य->window, mouseID, false, (भग्न)cursorPos.x, (भग्न)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), तथ्य->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_बायाँ : SDL_BUTTON_दायाँ,
                                    (Get_Async_कुंजी_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), तथ्य->window, mouseID,
                                    !swapButtons ? SDL_BUTTON_दायाँ : SDL_BUTTON_बायाँ,
                                    (Get_Async_कुंजी_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), तथ्य->window, mouseID,
                                    SDL_BUTTON_मध्य,
                                    (Get_Async_कुंजी_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), तथ्य->window, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_कुंजी_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), तथ्य->window, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_कुंजी_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अगर_घोषित SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#पूर्ण_अगर
}

अटल पूर्णांक app_registered = 0;
LPTSTR SDL_Appname = शून्य;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = शून्य;

अटल व्योम WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    अगर (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#पूर्ण_अगर
    SDL_free(SDL_Appname);
    SDL_Appname = शून्य;
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
अटल BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (व्योम)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    वापस FALSE;
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(स्थिर अक्षर *name, Uint32 style, व्योम *hInst)
{
    WNDCLASSEX wcex;
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    स्थिर अक्षर *hint;
#पूर्ण_अगर

    // Only do this once...
    अगर (app_registered) {
        ++app_registered;
        वापस true;
    }
    SDL_assert(!SDL_Appname);
    अगर (!name) {
        name = "SDL_app";
#अगर defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#पूर्ण_अगर
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(शून्य);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_आकार = माप(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    अगर (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        अगर (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } अन्यथा {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    अगर (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        वापस SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    वापस true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
व्योम SDL_UnregisterApp(व्योम)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    अगर (!app_registered) {
        वापस;
    }
    --app_registered;
    अगर (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = शून्य;
        wcex.hIconSm = शून्य;
        // Check for any registered window classes.
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        अगर (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#पूर्ण_अगर
        WIN_CleanRegisterApp(wcex);
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
