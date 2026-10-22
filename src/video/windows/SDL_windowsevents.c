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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

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
#यदि_परिभाषितम् HAVE_TPCSHRD_H
#अन्तर्भाव <tpcshrd.h>
#यदि_अन्तः // HAVE_TPCSHRD_H

#यदि 0
#परिभाषय WMMSG_DEBUG
#यदि_अन्तः
#यदि_परिभाषितम् WMMSG_DEBUG
#अन्तर्भाव <stdio.h>
#अन्तर्भाव "wmmsg.h"
#यदि_अन्तः

#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#अन्तर्भाव <shobjidl.h>
#यदि_अन्तः

#यदि_परिभाषितम् SDL_PLATFORM_GDK
#अन्तर्भाव "../../core/gdk/SDL_gdk.h"
#यदि_अन्तः

// #define HIGHDPI_DEBUG

// Undocumented window messages
#यदि_अपरिभाषितम् WM_NCUAHDRAWCAPTION
#परिभाषय WM_NCUAHDRAWCAPTION 0xAE
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_NCUAHDRAWFRAME
#परिभाषय WM_NCUAHDRAWFRAME 0xAF
#यदि_अन्तः

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#यदि_अपरिभाषितम् WM_XBUTTONDOWN
#परिभाषय WM_XBUTTONDOWN 0x020B
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_XBUTTONUP
#परिभाषय WM_XBUTTONUP 0x020C
#यदि_अन्तः
#यदि_अपरिभाषितम् GET_XBUTTON_WPARAM
#परिभाषय GET_XBUTTON_WPARAM(w) (HIWORD(w))
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_निवेशः
#परिभाषय WM_निवेशः 0x00ff
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_TOUCH
#परिभाषय WM_TOUCH 0x0240
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_MOUSEHWHEEL
#परिभाषय WM_MOUSEHWHEEL 0x020E
#यदि_अन्तः
#यदि_अपरिभाषितम् RI_MOUSE_HWHEEL
#परिभाषय RI_MOUSE_HWHEEL 0x0800
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERUPDATE
#परिभाषय WM_POINTERUPDATE 0x0245
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERDOWN
#परिभाषय WM_POINTERDOWN 0x0246
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERUP
#परिभाषय WM_POINTERUP 0x0247
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERENTER
#परिभाषय WM_POINTERENTER 0x0249
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERLEAVE
#परिभाषय WM_POINTERLEAVE 0x024A
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_POINTERCAPTURECHANGED
#परिभाषय WM_POINTERCAPTURECHANGED 0x024C
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_UNICHAR
#परिभाषय WM_UNICHAR 0x0109
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_DPICHANGED
#परिभाषय WM_DPICHANGED 0x02E0
#यदि_अन्तः
#यदि_अपरिभाषितम् WM_GETDPISCALEDSIZE
#परिभाषय WM_GETDPISCALEDSIZE 0x02E4
#यदि_अन्तः
#यदि_अपरिभाषितम् TOUCHEVENTF_PEN
#परिभाषय TOUCHEVENTF_PEN 0x0040
#यदि_अन्तः

#यदि_अपरिभाषितम् MAPVK_VK_गन्तव्यम्_VSC_EX
#परिभाषय MAPVK_VK_गन्तव्यम्_VSC_EX 4
#यदि_अन्तः

#यदि_अपरिभाषितम् WC_ERR_INVALID_CHARS
#परिभाषय WC_ERR_INVALID_CHARS 0x00000080
#यदि_अन्तः

#यदि_अपरिभाषितम् IS_उच्चः_SURROGATE
#परिभाषय IS_उच्चः_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#यदि_अन्तः

#यदि_अपरिभाषितम् USER_TIMER_MINIMUM
#परिभाषय USER_TIMER_MINIMUM 0x0000000A
#यदि_अन्तः

// Used to compare Windows message timestamps
#परिभाषय SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#यदि_परिभाषितम् _WIN64
प्रकारनिर्देश Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#यदि_अन्तः

स्थिर bool SDL_processing_messages;
स्थिर DWORD सन्देशः_tick;
स्थिर Uint64 timestamp_विस्थापनम्;

स्थिर शून्य WIN_समुच्चयः_सन्देशः_Tick(DWORD tick)
{
    सन्देशः_tick = tick;
}

स्थिर Uint64 WIN_GetEventTimestamp(शून्य)
{
    ध्रुव Uint64 TIMESTAMP_WRAP_विस्थापनम् = SDL_MS_गन्तव्यम्_NS(0x100000000LL);
    Uint64 timestamp, now;

    यदि (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        प्रत्यागम 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_गन्तव्यम्_NS(सन्देशः_tick);
    timestamp += timestamp_विस्थापनम्;
    यदि (!timestamp_विस्थापनम्) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_विस्थापनम् = (now - timestamp);
        timestamp = now;
    } अन्यथा यदि ((Sint64)(now - timestamp - TIMESTAMP_WRAP_विस्थापनम्) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_विस्थापनम् += TIMESTAMP_WRAP_विस्थापनम्;
        timestamp += TIMESTAMP_WRAP_विस्थापनम्;
    } अन्यथा यदि (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_विस्थापनम् -= (timestamp - now);
        timestamp = now;
    }
    प्रत्यागम timestamp;
}

// A message hook called before TranslateMessage()
स्थिर SDL_Windows_सन्देशः_Hook g_Windows_सन्देशः_Hook = रिक्त;
स्थिर शून्य *g_Windows_सन्देशः_Hook_दत्त = रिक्त;

शून्य SDL_समुच्चयः_Windows_सन्देशः_Hook(SDL_Windows_सन्देशः_Hook callback, शून्य *userdata)
{
    g_Windows_सन्देशः_Hook = callback;
    g_Windows_सन्देशः_Hook_दत्त = userdata;
}

स्थिर SDL_Scancode Windows_अवलोकनम्_संहिता_गन्तव्यम्_SDLScan_संहिता(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_कुञ्चिका)
{
    SDL_Scancode संहिता;
    Uint8 सूचकांक;
    Uint16 कुञ्चिका_Flags = HIWORD(lParam);
    Uint16 अवलोकनम्_संहिता = LOBYTE(कुञ्चिका_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    अवलोकनम्_संहिता &= ~0x80;

    *virtual_कुञ्चिका = (अवलोकनम्_संहिता == 0);

    यदि (अवलोकनम्_संहिता != 0) {
        यदि ((कुञ्चिका_Flags & KF_EXTENDED) == KF_EXTENDED) {
            अवलोकनम्_संहिता = MAKEWORD(अवलोकनम्_संहिता, 0xe0);
        } अन्यथा यदि (अवलोकनम्_संहिता == 0x45) {
            // Pause
            अवलोकनम्_संहिता = 0xe046;
        }
    } अन्यथा {
        Uint16 vk_संहिता = LOWORD(wParam);

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        अवलोकनम्_संहिता = LOWORD(Map_Virtual_कुञ्चिका(vk_संहिता, WIN_IsWindowsXP() ? MAPVK_VK_गन्तव्यम्_VSC : MAPVK_VK_गन्तव्यम्_VSC_EX));
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        यदि (अवलोकनम्_संहिता == 0xe11d) {
            अवलोकनम्_संहिता = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    सूचकांक = LOBYTE(अवलोकनम्_संहिता) | (HIBYTE(अवलोकनम्_संहिता) ? 0x80 : 0x00);
    संहिता = windows_scancode_सारणी[सूचकांक];
    *rawcode = अवलोकनम्_संहिता;

    प्रत्यागम संहिता;
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर bool WIN_ShouldIgnoreFocusClick(SDL_गवाक्षः_दत्त *दत्त)
{
    प्रत्यागम !SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

स्थिर शून्य WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_गवाक्षः_दत्त *दत्त, Uint8 button, SDL_MouseID mouseID)
{
    यदि (bSwapButtons) {
        यदि (button == SDL_BUTTON_वामः) {
            button = SDL_BUTTON_दक्षिणः;
        } अन्यथा यदि (button == SDL_BUTTON_दक्षिणः) {
            button = SDL_BUTTON_वामः;
        }
    }

    यदि (दत्त->focus_click_pending & SDL_BUTTON_आवरणम्(button)) {
        // Ignore the button click for activation
        यदि (!bwParamMousePressed) {
            दत्त->focus_click_pending &= ~SDL_BUTTON_आवरणम्(button);
            WIN_UpdateClipCursor(दत्त->गवाक्षः);
        }
        प्रत्यागम;
    }

    यदि (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_आवरणम्(button))) {
        SDL_SendMouseButton(timestamp, दत्त->गवाक्षः, mouseID, button, true);
    } अन्यथा यदि (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_आवरणम्(button))) {
        SDL_SendMouseButton(timestamp, दत्त->गवाक्षः, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
स्थिर शून्य WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_गवाक्षः_दत्त *दत्त, SDL_MouseID mouseID)
{
    यदि (wParam != दत्त->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(रिक्त, रिक्त);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, दत्त, SDL_BUTTON_वामः, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, दत्त, SDL_BUTTON_मध्यः, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, दत्त, SDL_BUTTON_दक्षिणः, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, दत्त, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, दत्त, SDL_BUTTON_X2, mouseID);

        दत्त->mouse_button_flags = wParam;
    }
}

स्थिर शून्य WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_गवाक्षः_दत्त *दत्त)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT कुञ्चिका_State;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(रिक्त, रिक्त);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    कुञ्चिका_State = Get_Async_कुञ्चिका_State(VK_LBUTTON);
    यदि (!(कुञ्चिका_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, दत्त, SDL_BUTTON_वामः, mouseID);
    }
    कुञ्चिका_State = Get_Async_कुञ्चिका_State(VK_RBUTTON);
    यदि (!(कुञ्चिका_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, दत्त, SDL_BUTTON_दक्षिणः, mouseID);
    }
    कुञ्चिका_State = Get_Async_कुञ्चिका_State(VK_MBUTTON);
    यदि (!(कुञ्चिका_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, दत्त, SDL_BUTTON_मध्यः, mouseID);
    }
    कुञ्चिका_State = Get_Async_कुञ्चिका_State(VK_XBUTTON1);
    यदि (!(कुञ्चिका_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, दत्त, SDL_BUTTON_X1, mouseID);
    }
    कुञ्चिका_State = Get_Async_कुञ्चिका_State(VK_XBUTTON2);
    यदि (!(कुञ्चिका_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, दत्त, SDL_BUTTON_X2, mouseID);
    }
    दत्त->mouse_button_flags = (WPARAM)-1;
}

स्थिर शून्य WIN_UpdateFocus(SDL_गवाक्षः *गवाक्षः, bool expect_focus, LPPOINT pos)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == गवाक्षः);
    bool has_focus = (Get_Foreground_गवाक्षः() == hwnd);

    यदि (had_focus == has_focus || has_focus != expect_focus) {
        प्रत्यागम;
    }

    यदि (has_focus) {
        POINT cursorPos;

        यदि (WIN_ShouldIgnoreFocusClick(दत्त) && !(गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            यदि (Get_Async_कुञ्चिका_State(VK_LBUTTON)) {
                दत्त->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            यदि (Get_Async_कुञ्चिका_State(VK_RBUTTON)) {
                दत्त->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            यदि (Get_Async_कुञ्चिका_State(VK_MBUTTON)) {
                दत्त->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            यदि (Get_Async_कुञ्चिका_State(VK_XBUTTON1)) {
                दत्त->focus_click_pending |= SDL_BUTTON_X1_आवरणम्;
            }
            यदि (Get_Async_कुञ्चिका_State(VK_XBUTTON2)) {
                दत्त->focus_click_pending |= SDL_BUTTON_X2_आवरणम्;
            }
        }

        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः->keyboard_focus ? गवाक्षः->keyboard_focus : गवाक्षः);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        यदि (!SDL_GetMouse()->relative_बहुलकम्) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_गन्तव्यम्_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)cursorPos.x, (भिन्न)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), दत्त);
        WIN_UpdateClipCursor(गवाक्षः);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(दत्त->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_कुञ्चिका_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_अङ्कः, (Get_कुञ्चिका_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_कुञ्चिका_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_गवाक्षः_ICCProfile(दत्त->गवाक्षः, true);
    } अन्यथा {
        दत्त->अन्तर्_गवाक्षः_deactivation = true;

        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        यदि (SDL_GetMouse()->relative_बहुलकम्) {
            SDL_समुच्चयः_Mouse_Focus(रिक्त);
        }
        WIN_Reset_Dead_कुञ्चिकाः();

        WIN_Unclip_Cursor_For_गवाक्षः(गवाक्षः);

        दत्त->अन्तर्_गवाक्षः_deactivation = false;
    }
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर bool Should_Generate_गवाक्षः_Close_On_Alt_F4(शून्य)
{
    प्रत्यागम SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

स्थिर bool Should_Clear_गवाक्षः_On_Erase_Background(SDL_गवाक्षः_दत्त *दत्त)
{
    विकल्प (दत्त->hint_erase_background_बहुलकम्) {
    पक्ष SDL_ERASEBACKGROUNDMODE_NEVER:
        प्रत्यागम false;
    पक्ष SDL_ERASEBACKGROUNDMODE_INITIAL:
        प्रत्यागम !दत्त->videodata->cleared;
    पक्ष SDL_ERASEBACKGROUNDMODE_ALWAYS:
        प्रत्यागम true;
    स्वभाव:
        // Unexpected value, fallback to default behaviour
        प्रत्यागम !दत्त->videodata->cleared;
    }
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#परिभाषय MI_WP_SIGNATURE      0xFF515700
#परिभाषय MI_WP_SIGNATURE_आवरणम् 0xFFFFFF00
#परिभाषय IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_आवरणम्) == MI_WP_SIGNATURE

प्रकारनिर्देश गणना
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

स्थिर SDL_MOUSE_EVENT_SOURCE Get_Mouse_सन्देशः_Source(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    यदि (IsTouchEvent(extrainfo)) {
        यदि (extrainfo & 0x80) {
            प्रत्यागम SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } अन्यथा {
            प्रत्यागम SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    प्रत्यागम SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर SDL_गवाक्षः_दत्त *WIN_Get_गवाक्षः_दत्त_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_गवाक्षः *गवाक्षः;

    यदि (_this) {
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
            यदि (दत्त && दत्त->hwnd == hwnd) {
                प्रत्यागम दत्त;
            }
        }
    }
    प्रत्यागम रिक्त;
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(पूर्णाङ्क n_संहिता, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_दत्त = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_दत्त *दत्त = SDL_GetVideoDevice()->आन्तरिकम्;
    SDL_Scancode अवलोकनम्_संहिता;

    यदि (n_संहिता < 0 || n_संहिता != HC_ACTION) {
        प्रत्यागम Call_अग्र_Hook_Ex(रिक्त, n_संहिता, wParam, lParam);
    }
    यदि (hook_दत्त->अवलोकनम्_संहिता == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        प्रत्यागम 1;
    }

    विकल्प (hook_दत्त->vk_संहिता) {
    पक्ष VK_LWIN:
        अवलोकनम्_संहिता = SDL_SCANCODE_LGUI;
        भङ्ग;
    पक्ष VK_RWIN:
        अवलोकनम्_संहिता = SDL_SCANCODE_RGUI;
        भङ्ग;
    पक्ष VK_LMENU:
        अवलोकनम्_संहिता = SDL_SCANCODE_LALT;
        भङ्ग;
    पक्ष VK_RMENU:
        अवलोकनम्_संहिता = SDL_SCANCODE_RALT;
        भङ्ग;
    पक्ष VK_LCONTROL:
        अवलोकनम्_संहिता = SDL_SCANCODE_LCTRL;
        भङ्ग;
    पक्ष VK_RCONTROL:
        अवलोकनम्_संहिता = SDL_SCANCODE_RCTRL;
        भङ्ग;
    पक्ष VK_SNAPSHOT:
        अवलोकनम्_संहिता = SDL_SCANCODE_PRINTSCREEN;
        भङ्ग;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    पक्ष VK_TAB:
        अवलोकनम्_संहिता = SDL_SCANCODE_TAB;
        भङ्ग;
    पक्ष VK_ESCAPE:
        अवलोकनम्_संहिता = SDL_SCANCODE_ESCAPE;
        भङ्ग;

    स्वभाव:
        प्रत्यागम Call_अग्र_Hook_Ex(रिक्त, n_संहिता, wParam, lParam);
    }

    यदि (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        यदि (!दत्त->raw_keyboard_enabled) {
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, hook_दत्त->अवलोकनम्_संहिता, अवलोकनम्_संहिता, true);
        }
    } अन्यथा {
        यदि (!दत्त->raw_keyboard_enabled) {
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, hook_दत्त->अवलोकनम्_संहिता, अवलोकनम्_संहिता, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        यदि (hook_दत्त->vk_संहिता <= 0xFF && दत्त->pre_hook_कुञ्चिका_state[hook_दत्त->vk_संहिता]) {
            दत्त->pre_hook_कुञ्चिका_state[hook_दत्त->vk_संहिता] = 0;
            प्रत्यागम Call_अग्र_Hook_Ex(रिक्त, n_संहिता, wParam, lParam);
        }
    }

    प्रत्यागम 1;
}

स्थिर bool WIN_SwapButtons(HANDLE hDevice)
{
    यदि (hDevice == रिक्त) {
        // Touchpad, already has buttons swapped
        प्रत्यागम false;
    }
    प्रत्यागम GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

स्थिर शून्य WIN_Handle_Raw_Mouse_निवेशः(Uint64 timestamp, SDL_Video_दत्त *दत्त, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    स्थिर संरचना {
        USHORT usButtonFlags;
        Uint8 button;
        bool अधस्तात्;
    } raw_buttons[] = {
        { RI_MOUSE_वामः_BUTTON_अधस्तात्, SDL_BUTTON_वामः, true },
        { RI_MOUSE_वामः_BUTTON_ऊर्ध्वम्, SDL_BUTTON_वामः, false },
        { RI_MOUSE_दक्षिणः_BUTTON_अधस्तात्, SDL_BUTTON_दक्षिणः, true },
        { RI_MOUSE_दक्षिणः_BUTTON_ऊर्ध्वम्, SDL_BUTTON_दक्षिणः, false },
        { RI_MOUSE_मध्यः_BUTTON_अधस्तात्, SDL_BUTTON_मध्यः, true },
        { RI_MOUSE_मध्यः_BUTTON_ऊर्ध्वम्, SDL_BUTTON_मध्यः, false },
        { RI_MOUSE_BUTTON_4_अधस्तात्, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_ऊर्ध्वम्, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_अधस्तात्, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_ऊर्ध्वम्, SDL_BUTTON_X2, false }
    };

    पूर्णाङ्क dx = (पूर्णाङ्क)rawmouse->l_चरमः_X;
    पूर्णाङ्क dy = (पूर्णाङ्क)rawmouse->l_चरमः_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    यदि (!दत्त->raw_mouse_enabled) {
        प्रत्यागम;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_गवाक्षः *गवाक्षः = SDL_GetKeyboardFocus();
    यदि (!गवाक्षः) {
        प्रत्यागम;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    यदि (!mouse) {
        प्रत्यागम;
    }

    यदि (Get_Mouse_सन्देशः_Source(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_Touch_Devices_उपलब्धम्() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        प्रत्यागम;
    }

    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;

    यदि (haveMotion && !windowdata->अन्तर्_modal_loop) {
        यदि (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, गवाक्षः, mouseID, true, (भिन्न)dx, (भिन्न)dy);
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
            पूर्णाङ्क w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            पूर्णाङ्क h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            पूर्णाङ्क x = raw_coordinates ? dx : (पूर्णाङ्क)(((भिन्न)dx / 65535.0f) * w);
            पूर्णाङ्क y = raw_coordinates ? dy : (पूर्णाङ्क)(((भिन्न)dy / 65535.0f) * h);
            पूर्णाङ्क relX, relY;

            /* Calculate relative motion */
            यदि (दत्त->चरमः_raw_mouse_position.x == 0 && दत्त->चरमः_raw_mouse_position.y == 0) {
                दत्त->चरमः_raw_mouse_position.x = x;
                दत्त->चरमः_raw_mouse_position.y = y;
            }
            relX = x - दत्त->चरमः_raw_mouse_position.x;
            relY = y - दत्त->चरमः_raw_mouse_position.y;

            यदि (remote_desktop) {
                यदि (!windowdata->अन्तर्_title_click && !windowdata->focus_click_pending) {
                    स्थिर पूर्णाङ्क wobble;
                    भिन्न floatX = (भिन्न)x / w;
                    भिन्न floatY = (भिन्न)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    यदि (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        पूर्णाङ्क warpX = rect.वामः + ((rect.दक्षिणः - rect.वामः) / 2) + wobble;
                        पूर्णाङ्क warpY = rect.शिखरम् + ((rect.bottom - rect.शिखरम्) / 2);

                        WIN_समुच्चयः_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        यदि (wobble > 1) {
                            wobble = -1;
                        }
                    } अन्यथा {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        ध्रुव पूर्णाङ्क MAX_RELATIVE_MOTION = (h / 6);
                        यदि (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, गवाक्षः, mouseID, true, (भिन्न)relX, (भिन्न)relY);
                        }
                    }
                }
            } अन्यथा यदि (mouse->pen_mouse_events) {
                ध्रुव पूर्णाङ्क अधिकतमम्_TABLET_RELATIVE_MOTION = 32;
                यदि (SDL_abs(relX) > अधिकतमम्_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > अधिकतमम्_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } अन्यथा {
                    SDL_SendMouseMotion(timestamp, गवाक्षः, mouseID, true, (भिन्न)relX, (भिन्न)relY);
                }
            } अन्यथा {
                पूर्णाङ्क screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                पूर्णाङ्क screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                यदि (!दत्त->raw_निवेशः_fake_pen_id) {
                    दत्त->raw_निवेशः_fake_pen_id = SDL_सङ्कलय_Pen_Device(timestamp, "raw mouse input", गवाक्षः, रिक्त, (शून्य *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, दत्त->raw_निवेशः_fake_pen_id, गवाक्षः, (भिन्न)(x + screen_x - गवाक्षः->x), (भिन्न)(y + screen_y - गवाक्षः->y));
            }

            दत्त->चरमः_raw_mouse_position.x = x;
            दत्त->चरमः_raw_mouse_position.y = y;
        }
    }

    यदि (haveButton) {
        प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            यदि (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool अधस्तात् = raw_buttons[i].अधस्तात्;

                यदि (button == SDL_BUTTON_वामः) {
                    यदि (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_दक्षिणः;
                    }
                } अन्यथा यदि (button == SDL_BUTTON_दक्षिणः) {
                    यदि (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_वामः;
                    }
                }

                यदि (windowdata->focus_click_pending & SDL_BUTTON_आवरणम्(button)) {
                    // Ignore the button click for activation
                    यदि (!अधस्तात्) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_आवरणम्(button);
                        WIN_UpdateClipCursor(गवाक्षः);
                    }
                    अनुवर्त;
                }

                SDL_SendMouseButton(timestamp, गवाक्षः, mouseID, button, अधस्तात्);
            }
        }

        यदि (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_दत्त;
            भिन्न fAmount = (भिन्न)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, गवाक्षः, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_प्रसामान्यम्);
        } अन्यथा यदि (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_दत्त;
            भिन्न fAmount = (भिन्न)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, गवाक्षः, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_प्रसामान्यम्);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

स्थिर शून्य WIN_Handle_Raw_Keyboard_निवेशः(Uint64 timestamp, SDL_Video_दत्त *दत्त, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    यदि (!दत्त->raw_keyboard_enabled) {
        प्रत्यागम;
    }

    यदि (rawkeyboard->Flags & RI_कुञ्चिका_E1) {
        // First key in a Ctrl+{key} sequence
        दत्त->pending_E1_कुञ्चिका_sequence = true;
        प्रत्यागम;
    }

    यदि ((rawkeyboard->Flags & RI_कुञ्चिका_E0) && rawkeyboard->Make_संहिता == 0x2A) {
        // 0xE02A make code prefix, ignored
        प्रत्यागम;
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (!rawkeyboard->Make_संहिता) {
        rawkeyboard->Make_संहिता = LOWORD(Map_Virtual_कुञ्चिका(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_गन्तव्यम्_VSC : MAPVK_VK_गन्तव्यम्_VSC_EX));
    }
#यदि_अन्तः
    यदि (!rawkeyboard->Make_संहिता) {
        प्रत्यागम;
    }

    bool अधस्तात्;
    विकल्प (rawkeyboard->सन्देशः_4) {
    पक्ष WM_KEYDOWN:
    पक्ष WM_SYSKEYDOWN:
        अधस्तात् = true;
        भङ्ग;
    पक्ष WM_KEYUP:
    पक्ष WM_SYSKEYUP:
        अधस्तात् = false;
        भङ्ग;
    स्वभाव:
        अधस्तात् = !(rawkeyboard->Flags & RI_कुञ्चिका_BREAK);
        भङ्ग;
    }

    SDL_Scancode संहिता;
    USHORT rawcode = rawkeyboard->Make_संहिता;
    यदि (दत्त->pending_E1_कुञ्चिका_sequence) {
        rawcode |= 0xE100;
        यदि (rawkeyboard->Make_संहिता == 0x45) {
            // Ctrl+NumLock == Pause
            संहिता = SDL_SCANCODE_PAUSE;
        } अन्यथा {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            संहिता = SDL_SCANCODE_UNKNOWN;
        }
        दत्त->pending_E1_कुञ्चिका_sequence = false;
    } अन्यथा {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 सूचकांक = (Uint8)rawkeyboard->Make_संहिता;
        यदि (rawkeyboard->Flags & RI_कुञ्चिका_E0) {
            rawcode |= 0xE000;
            सूचकांक |= 0x80;
        }
        संहिता = windows_scancode_सारणी[सूचकांक];
    }

    यदि (अधस्तात्) {
        SDL_गवाक्षः *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        यदि ((!दत्त->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_निवेशः_सक्रिय)) {
            प्रत्यागम;
        }
    }

    SDL_Send_Keyboard_कुञ्चिका(timestamp, keyboardID, rawcode, संहिता, अधस्तात्);
}

शून्य WIN_Poll_Raw_निवेशः(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    UINT आकार, i, गणनम्, योग = 0;
    RAWINPUT *निवेशः;
    Uint64 poll_finish;

    यदि (दत्त->rawinput_विस्थापनम् == 0) {
        BOOL isWow64;

        दत्त->rawinput_विस्थापनम् = परिमाण(RAWINPUTHEADER);
        यदि (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            दत्त->rawinput_विस्थापनम् += 8;
        }
    }

    // Get all available events
    निवेशः = (RAWINPUT *)दत्त->rawinput;
    प्रति (;;) {
        आकार = दत्त->rawinput_आकार - (UINT)((BYTE *)निवेशः - दत्त->rawinput);
        गणनम् = Get_Raw_निवेशः_बफर(निवेशः, &आकार, परिमाण(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        यदि (गणनम् == 0 || गणनम् == (UINT)-1) {
            यदि (!दत्त->rawinput || (गणनम् == (UINT)-1 && Get_चरमः_Error() == ERROR_INSUFFICIENT_बफर)) {
                ध्रुव UINT RAWINPUT_बफर_आकार_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(दत्त->rawinput, दत्त->rawinput_आकार + RAWINPUT_बफर_आकार_INCREMENT);
                यदि (!rawinput) {
                    भङ्ग;
                }
                निवेशः = (RAWINPUT *)(rawinput + ((BYTE *)निवेशः - दत्त->rawinput));
                दत्त->rawinput = rawinput;
                दत्त->rawinput_आकार += RAWINPUT_बफर_आकार_INCREMENT;
            } अन्यथा {
                भङ्ग;
            }
        } अन्यथा {
            योग += गणनम्;

            // Advance input to the end of the buffer
            यावत् (गणनम्--) {
                निवेशः = NEXTRAWINPUTBLOCK(निवेशः);
            }
        }
    }

    यदि (योग > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_योग = 0;
        प्रति (i = 0, निवेशः = (RAWINPUT *)दत्त->rawinput; i < योग; ++i, निवेशः = NEXTRAWINPUTBLOCK(निवेशः)) {
            यदि (निवेशः->शीर्षकम्.dwType == RIM_TYPEMOUSE) {
                mouse_योग += 1;
            }
        }
        पूर्णाङ्क mouse_सूचकांक = 0;
        प्रति (i = 0, निवेशः = (RAWINPUT *)दत्त->rawinput; i < योग; ++i, निवेशः = NEXTRAWINPUTBLOCK(निवेशः)) {
            यदि (निवेशः->शीर्षकम्.dwType == RIM_TYPEMOUSE) {
                mouse_सूचकांक += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)निवेशः + दत्त->rawinput_विस्थापनम्);
                Uint64 time = poll_finish - (delta * (mouse_योग - mouse_सूचकांक)) / mouse_योग;
                WIN_Handle_Raw_Mouse_निवेशः(time, दत्त, निवेशः->शीर्षकम्.hDevice, rawmouse);
            } अन्यथा यदि (निवेशः->शीर्षकम्.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)निवेशः + दत्त->rawinput_विस्थापनम्);
                WIN_Handle_Raw_Keyboard_निवेशः(poll_finish, दत्त, निवेशः->शीर्षकम्.hDevice, rawkeyboard);
            }
        }
    }
    दत्त->चरमः_rawinput_poll = poll_finish;
}

स्थिर शून्य सङ्कलय_Device_ID(Uint32 deviceID, Uint32 **list, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क new_गणनम् = (*गणनम् + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_गणनम् * परिमाण(*new_list));
    यदि (!new_list) {
        // Oh well, we'll drop this one
        प्रत्यागम;
    }
    new_list[new_गणनम् - 1] = deviceID;

    *गणनम् = new_गणनम्;
    *list = new_list;
}

स्थिर bool HasDeviceID(Uint32 deviceID, ध्रुव Uint32 *list, पूर्णाङ्क गणनम्)
{
    प्रति (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        यदि (deviceID == list[i]) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

स्थिर वर्ण *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, ध्रुव वर्ण *instance, Uint16 vendor, Uint16 गुणनफलम्, ध्रुव वर्ण *default_name, bool hid_loaded)
{
    वर्ण *vendor_name = रिक्त;
    वर्ण *गुणनफलम्_name = रिक्त;
    वर्ण *name = रिक्त;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    यदि (hid_loaded) {
        वर्ण devName[MAX_मार्गः + 1];
        devName[0] = '\0';
        UINT cap = परिमाण(devName) - 1;
        UINT len = Get_Raw_निवेशः_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        यदि (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, रिक्त, OPEN_EXISTING, 0, रिक्त);
            यदि (hFile != INVALID_HANDLE_मानम्) {
                SDL_HidD_GetManufacturerString(hFile, vend, परिमाण(vend));
                SDL_Hid_D_Get_गुणनफलम्_String(hFile, prod, परिमाण(prod));
                CloseHandle(hFile);
            }
        }
    }

    यदि (vend[0]) {
        vendor_name = WIN_String_गन्तव्यम्_UTF8_W(vend);
    }

    यदि (prod[0]) {
        गुणनफलम्_name = WIN_String_गन्तव्यम्_UTF8_W(prod);
    } अन्यथा {
        SP_DEVINFO_दत्त दत्त;
        SDL_zero(दत्त);
        दत्त.cb_आकार = परिमाण(दत्त);
        प्रति (DWORD i = 0;; ++i) {
            यदि (!सज्जता_Di_Enum_Device_Info(devinfo, i, &दत्त)) {
                यदि (Get_चरमः_Error() == ERROR_NO_अधिकम्_वस्तूनि) {
                    भङ्ग;
                } अन्यथा {
                    अनुवर्त;
                }
            }

            वर्ण DeviceInstanceId[64];
            यदि (!सज्जता_Di_Get_Device_Instance_Id_A(devinfo, &दत्त, DeviceInstanceId, परिमाण(DeviceInstanceId), रिक्त))
                अनुवर्त;

            यदि (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD आकार = 0;
                यदि (सज्जता_Di_Get_Device_Registry_Property_W(devinfo, &दत्त, SPDRP_DEVICEDESC, रिक्त, (PBYTE)prod, परिमाण(prod), &आकार)) {
                    // Make sure the device description is null terminated
                    आकार /= परिमाण(*prod);
                    यदि (आकार >= SDL_arraysize(prod)) {
                        // Truncated description...
                        आकार = (SDL_arraysize(prod) - 1);
                    }
                    prod[आकार] = 0;

                    यदि (vendor || गुणनफलम्) {
                        SDL_asprintf(&गुणनफलम्_name, "%S (0x%.4x/0x%.4x)", prod, vendor, गुणनफलम्);
                    } अन्यथा {
                        गुणनफलम्_name = WIN_String_गन्तव्यम्_UTF8_W(prod);
                    }
                }
                भङ्ग;
            }
        }
    }

    यदि (!गुणनफलम्_name && (vendor || गुणनफलम्)) {
        SDL_asprintf(&गुणनफलम्_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, गुणनफलम्);
    }
    name = SDL_CreateDeviceName(vendor, गुणनफलम्, vendor_name, गुणनफलम्_name, default_name);
    SDL_free(vendor_name);
    SDL_free(गुणनफलम्_name);

    प्रत्यागम name;
}

शून्य WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = रिक्त;
    UINT raw_device_गणनम् = 0;
    पूर्णाङ्क old_keyboard_गणनम् = 0;
    SDL_KeyboardID *old_keyboards = रिक्त;
    पूर्णाङ्क new_keyboard_गणनम् = 0;
    SDL_KeyboardID *new_keyboards = रिक्त;
    पूर्णाङ्क old_mouse_गणनम् = 0;
    SDL_MouseID *old_mice = रिक्त;
    पूर्णाङ्क new_mouse_गणनम् = 0;
    SDL_MouseID *new_mice = रिक्त;

    यदि (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->आन्तरिकम्->detect_device_hotplug ||
        _this->आन्तरिकम्->gameinput_context) {
        प्रत्यागम;
    }

    यदि ((Get_Raw_निवेशः_Device_List(रिक्त, &raw_device_गणनम्, परिमाण(RAWINPUTDEVICELIST)) == -1) || (!raw_device_गणनम्)) {
        प्रत्यागम; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(परिमाण(RAWINPUTDEVICELIST) * raw_device_गणनम्);
    यदि (!raw_devices) {
        प्रत्यागम; // oh well.
    }

    raw_device_गणनम् = Get_Raw_निवेशः_Device_List(raw_devices, &raw_device_गणनम्, परिमाण(RAWINPUTDEVICELIST));
    यदि (raw_device_गणनम् == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = रिक्त;
        प्रत्यागम; // oh well.
    }

    HDEVINFO devinfo = सज्जता_Di_Get_Class_Devs_A(रिक्त, रिक्त, रिक्त, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_गणनम्);
    old_mice = SDL_GetMice(&old_mouse_गणनम्);

    प्रति (UINT i = 0; i < raw_device_गणनम्; i++) {
        RID_DEVICE_INFO rdi;
        वर्ण devName[MAX_मार्गः] = { 0 };
        UINT rdi_आकार = परिमाण(rdi);
        UINT name_आकार = SDL_arraysize(devName);
        पूर्णाङ्क vendor = 0, गुणनफलम् = 0;
        DWORD dwType = raw_devices[i].dwType;
        वर्ण *instance, *ptr, *name;

        यदि (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            अनुवर्त;
        }

        rdi.cb_आकार = परिमाण(rdi);
        यदि (Get_Raw_निवेशः_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_आकार) == ((UINT)-1) ||
            Get_Raw_निवेशः_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_आकार) == ((UINT)-1)) {
            अनुवर्त;
        }

        // Extract the device instance
        instance = devName;
        यावत् (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        प्रति (ptr = instance; *ptr; ++ptr) {
            यदि (*ptr == '#') {
                *ptr = '\\';
            }
            यदि (*ptr == '{') {
                यदि (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                भङ्ग;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &गुणनफलम्);

        विकल्प (dwType) {
        पक्ष RIM_TYPEKEYBOARD:
            यदि (SDL_IsKeyboard((Uint16)vendor, (Uint16)गुणनफलम्, rdi.keyboard.dw_सङ्ख्या_सम्बन्धि_कुञ्चिकाः_योग)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                सङ्कलय_Device_ID(keyboardID, &new_keyboards, &new_keyboard_गणनम्);
                यदि (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_गणनम्)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)गुणनफलम्, "Keyboard", hid_loaded);
                    SDL_सङ्कलय_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            भङ्ग;
        पक्ष RIM_TYPEMOUSE:
            यदि (SDL_IsMouse((Uint16)vendor, (Uint16)गुणनफलम्)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                सङ्कलय_Device_ID(mouseID, &new_mice, &new_mouse_गणनम्);
                यदि (!HasDeviceID(mouseID, old_mice, old_mouse_गणनम्)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)गुणनफलम्, "Mouse", hid_loaded);
                    SDL_सङ्कलय_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
    }

    प्रति (पूर्णाङ्क i = old_keyboard_गणनम्; i--;) {
        यदि (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_गणनम्)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    प्रति (पूर्णाङ्क i = old_mouse_गणनम्; i--;) {
        यदि (!HasDeviceID(old_mice[i], new_mice, new_mouse_गणनम्)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    सज्जता_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
स्थिर bool Skip_Alt_Gr_वामः_Control(WPARAM wParam, LPARAM lParam)
{
    यदि (wParam != VK_CONTROL) {
        प्रत्यागम false;
    }

    // Is this an extended key (i.e. right key)?
    यदि (lParam & 0x01000000) {
        प्रत्यागम false;
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    सन्देशः_3 अग्र_सन्देशः;
    DWORD सन्देशः_time = Get_सन्देशः_Time();
    यदि (Peek_सन्देशः(&अग्र_सन्देशः, रिक्त, 0, 0, PM_NOREMOVE)) {
        यदि (अग्र_सन्देशः.सन्देशः == WM_KEYDOWN ||
            अग्र_सन्देशः.सन्देशः == WM_SYSKEYDOWN) {
            यदि (अग्र_सन्देशः.wParam == VK_MENU && (अग्र_सन्देशः.lParam & 0x01000000) && अग्र_सन्देशः.time == सन्देशः_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                प्रत्यागम true;
            }
        }
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    प्रत्यागम false;
}

स्थिर bool Dispatch_Modal_Loop_सन्देशः_Hook(HWND *hwnd, UINT *सन्देशः_2, WPARAM *wParam, LPARAM *lParam)
{
    सन्देशः_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.सन्देशः = *सन्देशः_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    यदि (g_Windows_सन्देशः_Hook(g_Windows_सन्देशः_Hook_दत्त, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *सन्देशः_2 = dummy.सन्देशः;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

LRESULT CALLBACK WIN_गवाक्षः_Proc(HWND hwnd, UINT सन्देशः_2, WPARAM wParam, LPARAM lParam)
{
    SDL_गवाक्षः_दत्त *दत्त;
    LRESULT return_संहिता = -1;

    // Get the window data for the window
    दत्त = WIN_Get_गवाक्षः_दत्त_From_HWND(hwnd);
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (!दत्त) {
        // Fallback
        दत्त = (SDL_गवाक्षः_दत्त *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#यदि_अन्तः
    यदि (!दत्त) {
        प्रत्यागम Call_गवाक्षः_Proc(Def_गवाक्षः_Proc, hwnd, सन्देशः_2, wParam, lParam);
    }

#यदि_परिभाषितम् WMMSG_DEBUG
    {
        वर्ण सन्देशः[1024];
        यदि (सन्देशः_2 > MAX_WMMSG) {
            SDL_snprintf(सन्देशः, परिमाण(सन्देशः), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, सन्देशः_2, wParam, lParam);
        } अन्यथा {
            SDL_snprintf(सन्देशः, परिमाण(सन्देशः), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[सन्देशः_2], wParam, lParam);
        }
        OutputDebugStringA(सन्देशः);
    }
#यदि_अन्तः // WMMSG_DEBUG


    यदि (g_Windows_सन्देशः_Hook && दत्त->अन्तर्_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        यदि (!Dispatch_Modal_Loop_सन्देशः_Hook(&hwnd, &सन्देशः_2, &wParam, &lParam)) {
            प्रत्यागम 0;
        }
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (WIN_HandleIMEMessage(hwnd, सन्देशः_2, wParam, &lParam, दत्त->videodata)) {
        प्रत्यागम 0;
    }
#यदि_अन्तः

    विकल्प (सन्देशः_2) {

    पक्ष WM_SHOWWINDOW:
    {
        यदि (wParam) {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
        } अन्यथा {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_HIDDEN, 0, 0);
        }
    } भङ्ग;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    पक्ष WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        दत्त->postpone_clipcursor = true;
        दत्त->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        POINT pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(दत्त->गवाक्षः, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } भङ्ग;

    पक्ष WM_NCUAHDRAWCAPTION:
    पक्ष WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
            return_संहिता = 0;
        }
    } भङ्ग;

    पक्ष WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        ध्रुव DWORD सन्देशः_Pos = Get_सन्देशः_Pos();
        POINT pos = { GET_X_LPARAM(सन्देशः_Pos), GET_Y_LPARAM(सन्देशः_Pos) };
        WIN_UpdateFocus(दत्त->गवाक्षः, !!LOWORD(wParam), &pos);
    } भङ्ग;

    पक्ष WM_MOUSEACTIVATE:
    {
        यदि (SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः)) {
            प्रत्यागम MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_गवाक्षः *parent = दत्त->गवाक्षः->parent;
        यावत् (parent) {
            यदि ((parent->flags & SDL_गवाक्षः_निवेशः_FOCUS) &&
                (parent->flags & SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्)) {
                प्रत्यागम MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } भङ्ग;

    पक्ष WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ध्रुव DWORD सन्देशः_Pos = Get_सन्देशः_Pos();
        POINT pos = { GET_X_LPARAM(सन्देशः_Pos), GET_Y_LPARAM(सन्देशः_Pos) };
        WIN_UpdateFocus(दत्त->गवाक्षः, true, &pos);
    } भङ्ग;

    पक्ष WM_KILLFOCUS:
    पक्ष WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        ध्रुव DWORD सन्देशः_Pos = Get_सन्देशः_Pos();
        POINT pos = { GET_X_LPARAM(सन्देशः_Pos), GET_Y_LPARAM(सन्देशः_Pos) };
        WIN_UpdateFocus(दत्त->गवाक्षः, false, &pos);
    } भङ्ग;

    पक्ष WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ध्रुव UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेशः_TYPE pointer_type = PT_POINTER;
        यदि (!दत्त->videodata->GetPointerType) {
            भङ्ग;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा यदि (!दत्त->videodata->GetPointerType(pointerid, &pointer_type)) {
            भङ्ग;  // oh well.
        } अन्यथा यदि (pointer_type != PT_PEN) {
            भङ्ग;  // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ध्रुव SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        यदि (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, दत्त->गवाक्षः, true, true);
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
            info.अङ्कः_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_सङ्कलय_Pen_Device(WIN_GetEventTimestamp(), रिक्त, दत्त->गवाक्षः, &info, hpointer, true);
        }
        return_संहिता = 0;
    } भङ्ग;

    पक्ष WM_POINTERCAPTURECHANGED:
    पक्ष WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ध्रुव UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेशः_TYPE pointer_type = PT_POINTER;
        यदि (!दत्त->videodata->GetPointerType) {
            भङ्ग;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } अन्यथा यदि (!दत्त->videodata->GetPointerType(pointerid, &pointer_type)) {
            भङ्ग;  // oh well.
        } अन्यथा यदि (pointer_type != PT_PEN) {
            भङ्ग;  // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ध्रुव SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        यदि (pen == 0) {
            भङ्ग;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        यदि ((सन्देशः_2 == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, दत्त->गवाक्षः, false, false);
        }
        return_संहिता = 0;
    } भङ्ग;

    पक्ष WM_POINTERDOWN:
    पक्ष WM_POINTERUP:
    पक्ष WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        ध्रुव UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_निवेशः_TYPE pointer_type = PT_POINTER;
        यदि (!दत्त->videodata->GetPointerType || !दत्त->videodata->GetPointerType(pointerid, &pointer_type)) {
            भङ्ग;  // oh well.
        } अन्यथा यदि ((सन्देशः_2 == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            दत्त->चरमः_pointer_update = lParam;
            return_संहिता = 0;
            भङ्ग;
        } अन्यथा यदि (pointer_type != PT_PEN) {
            भङ्ग; // we only care about pens here.
        }

        शून्य *hpointer = (शून्य *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        ध्रुव SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        यदि (pen == 0) {
            भङ्ग;  // not a pen, or not a pen we already knew about.
        } अन्यथा यदि (!दत्त->videodata->GetPointerPenInfo || !दत्त->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            भङ्ग;  // oh well.
        }

        ध्रुव Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

        ध्रुव bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        यदि (!istouching) {
            SDL_SendPenTouch(timestamp, pen, गवाक्षः, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        ध्रुव POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        भिन्न fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        यदि (!दत्त->videodata->GetPointerDeviceRects || !दत्त->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_गन्तव्यम्_Client(दत्त->hwnd, &position);
            fx = (भिन्न) position.x;
            fy = (भिन्न) position.y;
        } अन्यथा {
            पूर्णाङ्क ix, iy;
            SDL_Get_गवाक्षः_Position(गवाक्षः, &ix, &iy);
            ध्रुव SDL_FPoint गवाक्षः_pos = { (भिन्न) ix, (भिन्न) iy };

            ध्रुव भिन्न facX = pointer_info->ptHimetricLocationRaw.x / (भिन्न) (tablet_bounds.दक्षिणः );
            ध्रुव भिन्न facY = pointer_info->ptHimetricLocationRaw.y / (भिन्न) (tablet_bounds.bottom);

            ध्रुव भिन्न w = tablet_mapping.दक्षिणः  - tablet_mapping.वामः;
            ध्रुव भिन्न h = tablet_mapping.bottom - tablet_mapping.शिखरम्;

            fx = (tablet_mapping.वामः + (facX * w)) - गवाक्षः_pos.x;
            fy = (tablet_mapping.शिखरम्  + (facY * h)) - गवाक्षः_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, गवाक्षः, fx, fy);
        SDL_SendPenButton(timestamp, pen, गवाक्षः, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, गवाक्षः, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        यदि (pen_info.pen_आवरणम् & PEN_आवरणम्_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, गवाक्षः, SDL_PEN_AXIS_PRESSURE, ((भिन्न) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        यदि (pen_info.pen_आवरणम् & PEN_आवरणम्_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, गवाक्षः, SDL_PEN_AXIS_ROTATION, ((भिन्न) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        यदि (pen_info.pen_आवरणम् & PEN_आवरणम्_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, गवाक्षः, SDL_PEN_AXIS_XTILT, ((भिन्न) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        यदि (pen_info.pen_आवरणम् & PEN_आवरणम्_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, गवाक्षः, SDL_PEN_AXIS_YTILT, ((भिन्न) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        यदि (istouching) {
            SDL_SendPenTouch(timestamp, pen, गवाक्षः, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_संहिता = 0;
    } भङ्ग;

    पक्ष WM_MOUSEMOVE:
    {
        SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

        यदि (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
            bool wish_clip_cursor = (
                गवाक्षः->flags & (SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम् | SDL_गवाक्षः_MOUSE_GRABBED) ||
                (गवाक्षः->mouse_rect.w > 0 && गवाक्षः->mouse_rect.h > 0)
            );
            यदि (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                दत्त->clipcursor_queued = true;
            }
        }

        यदि (!दत्त->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_आकार = परिमाण(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = दत्त->hwnd;

            यदि (TrackMouseEvent(&trackMouseEvent)) {
                दत्त->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), दत्त);
        }

        यदि (!दत्त->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            यदि (Get_Mouse_सन्देशः_Source((ULONG)Get_सन्देशः_Extra_Info()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != दत्त->चरमः_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)GET_X_LPARAM(lParam), (भिन्न)GET_Y_LPARAM(lParam));
            }
        }

    } भङ्ग;

    पक्ष WM_LBUTTONUP:
    पक्ष WM_RBUTTONUP:
    पक्ष WM_MBUTTONUP:
    पक्ष WM_XBUTTONUP:
    पक्ष WM_LBUTTONDOWN:
    पक्ष WM_LBUTTONDBLCLK:
    पक्ष WM_RBUTTONDOWN:
    पक्ष WM_RBUTTONDBLCLK:
    पक्ष WM_MBUTTONDOWN:
    पक्ष WM_MBUTTONDBLCLK:
    पक्ष WM_XBUTTONDOWN:
    पक्ष WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        यदि (!दत्त->videodata->raw_mouse_enabled) {
            यदि (Get_Mouse_सन्देशः_Source((ULONG)Get_सन्देशः_Extra_Info()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != दत्त->चरमः_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, दत्त, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } भङ्ग;

#यदि 0   // We handle raw input all at once instead of using a syscall for each mouse event
    पक्ष WM_निवेशः:
    {
        HRAWINPUT h_Raw_निवेशः = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT आकार = परिमाण(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        यदि (दत्त->गवाक्षः != SDL_GetKeyboardFocus()) {
            भङ्ग;
        }

        Get_Raw_निवेशः_दत्त(h_Raw_निवेशः, RID_निवेशः, &inp, &आकार, परिमाण(RAWINPUTHEADER));
        यदि (inp.शीर्षकम्.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_निवेशः(WIN_GetEventTimestamp(), दत्त, inp.शीर्षकम्.hDevice, &inp.दत्त.mouse);
        } अन्यथा यदि (inp.शीर्षकम्.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_निवेशः(WIN_GetEventTimestamp(), दत्त, inp.शीर्षकम्.hDevice, &inp.दत्त.keyboard);
        }
    } भङ्ग;
#यदि_अन्तः

    पक्ष WM_MOUSEWHEEL:
    पक्ष WM_MOUSEHWHEEL:
    {
        यदि (!दत्त->videodata->raw_mouse_enabled) {
            ह्रस्व amount = GET_WHEEL_DELTA_WPARAM(wParam);
            भिन्न fAmount = (भिन्न)amount / WHEEL_DELTA;
            यदि (सन्देशः_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_प्रसामान्यम्);
            } अन्यथा {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_प्रसामान्यम्);
            }
        }
    } भङ्ग;

    पक्ष WM_MOUSELEAVE:
        यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
            यदि (SDL_GetMouseFocus() == दत्त->गवाक्षः && !SDL_GetMouse()->relative_बहुलकम् && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_सन्देशः_Pos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_गन्तव्यम्_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                यदि (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)cursorPos.x, (भिन्न)cursorPos.y);
                } अन्यथा {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    यदि (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), दत्त->गवाक्षः, SDL_TOUCH_MOUSEID, false, (भिन्न)cursorPos.x, (भिन्न)cursorPos.y);
                    } अन्यथा { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)cursorPos.x, (भिन्न)cursorPos.y);
                    }
                }
            }

            यदि (!SDL_GetMouse()->relative_बहुलकम्) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_समुच्चयः_Mouse_Focus(रिक्त);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        दत्त->mouse_tracked = false;

        return_संहिता = 0;
        भङ्ग;
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    पक्ष WM_KEYDOWN:
    पक्ष WM_SYSKEYDOWN:
    {
        यदि (Skip_Alt_Gr_वामः_Control(wParam, lParam)) {
            return_संहिता = 0;
            भङ्ग;
        }

        bool virtual_कुञ्चिका = false;
        Uint16 rawcode = 0;
        SDL_Scancode संहिता = Windows_अवलोकनम्_संहिता_गन्तव्यम्_SDLScan_संहिता(lParam, wParam, &rawcode, &virtual_कुञ्चिका);

        // Detect relevant keyboard shortcuts
        यदि (संहिता == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            यदि (Should_Generate_गवाक्षः_Close_On_Alt_F4()) {
                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
            }
        }

        यदि (virtual_कुञ्चिका || !दत्त->videodata->raw_keyboard_enabled || दत्त->गवाक्षः->text_निवेशः_सक्रिय) {
            SDL_Send_Keyboard_कुञ्चिका(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, संहिता, true);
        }
    }

        return_संहिता = 0;
        भङ्ग;

    पक्ष WM_SYSKEYUP:
    पक्ष WM_KEYUP:
    {
        यदि (Skip_Alt_Gr_वामः_Control(wParam, lParam)) {
            return_संहिता = 0;
            भङ्ग;
        }

        bool virtual_कुञ्चिका = false;
        Uint16 rawcode = 0;
        SDL_Scancode संहिता = Windows_अवलोकनम्_संहिता_गन्तव्यम्_SDLScan_संहिता(lParam, wParam, &rawcode, &virtual_कुञ्चिका);
        ध्रुव bool *keyboardState = SDL_GetKeyboardState(रिक्त);

        यदि (virtual_कुञ्चिका || !दत्त->videodata->raw_keyboard_enabled || दत्त->गवाक्षः->text_निवेशः_सक्रिय) {
            यदि (संहिता == SDL_SCANCODE_PRINTSCREEN && !keyboardState[संहिता]) {
                SDL_Send_Keyboard_कुञ्चिका(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, संहिता, true);
            }
            SDL_Send_Keyboard_कुञ्चिका(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, संहिता, false);
        }
    }
        return_संहिता = 0;
        भङ्ग;

    पक्ष WM_UNICHAR:
        यदि (wParam == UNICODE_NOCHAR) {
            return_संहिता = 1;
        } अन्यथा {
            यदि (SDL_Text_निवेशः_सक्रिय(दत्त->गवाक्षः)) {
                वर्ण text[5];
                वर्ण *अन्तः = SDL_UCS4_गन्तव्यम्_UTF8((Uint32)wParam, text);
                *अन्तः = '\0';
                SDL_SendKeyboardText(text);
            }
            return_संहिता = 0;
        }
        भङ्ग;

    पक्ष WM_CHAR:
        यदि (SDL_Text_निवेशः_सक्रिय(दत्त->गवाक्षः)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            यदि (IS_उच्चः_SURROGATE(wParam)) {
                दत्त->उच्चः_surrogate = (WCHAR)wParam;
            } अन्यथा {
                WCHAR utf16[3];

                utf16[0] = दत्त->उच्चः_surrogate ? दत्त->उच्चः_surrogate : (WCHAR)wParam;
                utf16[1] = दत्त->उच्चः_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                वर्ण utf8[5];
                पूर्णाङ्क परिणाम = WIN_Wide_Char_गन्तव्यम्_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, परिमाण(utf8), रिक्त, रिक्त);
                यदि (परिणाम > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                दत्त->उच्चः_surrogate = L'\0';
            }
        } अन्यथा {
            दत्त->उच्चः_surrogate = L'\0';
        }

        return_संहिता = 0;
        भङ्ग;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#यदि_परिभाषितम् WM_INPUTLANGCHANGE
    पक्ष WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_संहिता = 1;
        भङ्ग;
#यदि_अन्तः // WM_INPUTLANGCHANGE

    पक्ष WM_NCLBUTTONDOWN:
    {
        दत्त->अन्तर्_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        यदि (Send_सन्देशः(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_गन्तव्यम्_Client(hwnd, &cursorPos);
            Post_सन्देशः(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } भङ्ग;

    पक्ष WM_CAPTURECHANGED:
    {
        दत्त->अन्तर्_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), दत्त);
    } भङ्ग;

#यदि_परिभाषितम् WM_GETMINMAXINFO
    पक्ष WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT आकार;
        पूर्णाङ्क x, y;
        पूर्णाङ्क w, h;
        पूर्णाङ्क min_w, min_h;
        पूर्णाङ्क max_w, max_h;
        BOOL constrain_max_आकार;

        // If this is an expected size change, allow it
        यदि (दत्त->expected_resize) {
            भङ्ग;
        }

        // Get the current position of our window
        Get_गवाक्षः_Rect(hwnd, &आकार);
        x = आकार.वामः;
        y = आकार.शिखरम्;

        // Calculate current size of our window
        SDL_Get_गवाक्षः_आकार(दत्त->गवाक्षः, &w, &h);
        SDL_Get_गवाक्षः_Minimum_आकार(दत्त->गवाक्षः, &min_w, &min_h);
        SDL_Get_गवाक्षः_अधिकतमम्_आकार(दत्त->गवाक्षः, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        यदि (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_आकार = TRUE;
        } अन्यथा {
            constrain_max_आकार = FALSE;
        }

        यदि (!(SDL_Get_गवाक्षः_Flags(दत्त->गवाक्षः) & SDL_गवाक्षः_BORDERLESS) && !SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः)) {
            आकार.शिखरम् = 0;
            आकार.वामः = 0;
            आकार.bottom = h;
            आकार.दक्षिणः = w;
            WIN_Adjust_गवाक्षः_Rect_For_HWND(hwnd, &आकार, 0);
            w = आकार.दक्षिणः - आकार.वामः;
            h = आकार.bottom - आकार.शिखरम्;
#यदि_परिभाषितम् HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#यदि_अन्तः
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        यदि (SDL_Get_गवाक्षः_Flags(दत्त->गवाक्षः) & SDL_गवाक्षः_RESIZABLE) {
            यदि (SDL_Get_गवाक्षः_Flags(दत्त->गवाक्षः) & SDL_गवाक्षः_BORDERLESS) {
                पूर्णाङ्क screenW = GetSystemMetrics(SM_CXSCREEN);
                पूर्णाङ्क screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_आकार.x = SDL_max(w, screenW);
                info->pt_Max_आकार.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_आकार.x = (LONG)w + min_w;
            info->pt_Min_Track_आकार.y = (LONG)h + min_h;
            यदि (constrain_max_आकार) {
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
        return_संहिता = 0;
        भङ्ग;
#यदि_अन्तः // WM_GETMINMAXINFO

    पक्ष WM_WINDOWPOSCHANGING:

        यदि (दत्त->expected_resize) {
            return_संहिता = 0;
        } अन्यथा यदि (दत्त->अन्तर्_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            यदि (दत्त->चरमः_modal_विस्तारः == windowpos->cx && दत्त->चरमः_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            दत्त->चरमः_modal_विस्तारः = windowpos->cx;
            दत्त->चरमः_modal_height = windowpos->cy;

            return_संहिता = 0;
        }
        भङ्ग;

    पक्ष WM_WINDOWPOSCHANGED:
    {
        SDL_गवाक्षः *win;
        ध्रुव SDL_DisplayID original_displayID = दत्त->गवाक्षः->displayID;
        ध्रुव WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        पूर्णाङ्क x, y;
        पूर्णाङ्क w, h;

        यदि (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        यदि (iconic) {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
        } अन्यथा यदि (zoomed) {
            यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
            }
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MAXIMIZED, 0, 0);
            दत्त->force_ws_maximizebox = true;
        } अन्यथा यदि (दत्त->गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED)) {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
                दत्त->force_ws_maximizebox = false;
                WIN_समुच्चयः_गवाक्षः_Resizable(SDL_GetVideoDevice(), दत्त->गवाक्षः, !!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE));
            }
        }

        यदि (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        यदि (iconic) {
            भङ्ग;
        }

        यदि (दत्त->initializing) {
            भङ्ग;
        }

        यदि (!दत्त->disable_move_आकार_events) {
            यदि (GetClientRect(hwnd, &rect) && WIN_गवाक्षः_Rect_Valid(&rect)) {
                Client_गन्तव्यम्_Screen(hwnd, (LPPOINT) &rect);
                Client_गन्तव्यम्_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.वामः;
                y = rect.शिखरम्;

                SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(दत्त->गवाक्षः, x, y, &x, &y);
                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            यदि (GetClientRect(hwnd, &rect) && WIN_गवाक्षः_Rect_Valid(&rect)) {
                w = rect.दक्षिणः;
                h = rect.bottom;

                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(दत्त->गवाक्षः);

        // Update the window display position
        यदि (दत्त->गवाक्षः->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_गवाक्षः_ICCProfile(दत्त->गवाक्षः, true);
        }

        // Update the position of any child windows
        प्रति (win = दत्त->गवाक्षः->first_child; win; win = win->अग्र_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            यदि (SDL_गवाक्षः_IS_POPUP(win) && !(win->flags & SDL_गवाक्षः_HIDDEN)) {
                WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } भङ्ग;

    पक्ष WM_ENTERSIZEMOVE:
    पक्ष WM_ENTERMENULOOP:
    {
        यदि (g_Windows_सन्देशः_Hook) {
            यदि (!Dispatch_Modal_Loop_सन्देशः_Hook(&hwnd, &सन्देशः_2, &wParam, &lParam)) {
                प्रत्यागम 0;
            }
        }

        ++दत्त->अन्तर्_modal_loop;
        यदि (दत्त->अन्तर्_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_गवाक्षः_Rect(दत्त->hwnd, &rect);
            दत्त->चरमः_modal_विस्तारः = rect.दक्षिणः - rect.वामः;
            दत्त->चरमः_modal_height = rect.bottom - rect.शिखरम्;

            दत्त->initial_आकार_rect.वामः = दत्त->गवाक्षः->x;
            दत्त->initial_आकार_rect.दक्षिणः = दत्त->गवाक्षः->x + दत्त->गवाक्षः->w;
            दत्त->initial_आकार_rect.शिखरम् = दत्त->गवाक्षः->y;
            दत्त->initial_आकार_rect.bottom = दत्त->गवाक्षः->y + दत्त->गवाक्षः->h;

            समुच्चयः_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, रिक्त);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } भङ्ग;

    पक्ष WM_TIMER:
    {
        यदि (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_गवाक्षः_जीवितम्_Resize_Update(दत्त->गवाक्षः);

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#यदि 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            यदि (दत्त->videodata->DwmFlush) {
                दत्त->videodata->DwmFlush();
            }
#यदि_अन्तः
#यदि_अन्तः
            प्रत्यागम 0;
        }
    } भङ्ग;

    पक्ष WM_EXITSIZEMOVE:
    पक्ष WM_EXITMENULOOP:
    {
        --दत्त->अन्तर्_modal_loop;
        यदि (दत्त->अन्तर्_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } भङ्ग;

    पक्ष WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool तालकम्_aspect_अनुपातः = (दत्त->गवाक्षः->max_aspect == दत्त->गवाक्षः->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            भिन्न new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            यदि (दत्त->गवाक्षः->min_aspect <= 0 && दत्त->गवाक्षः->max_aspect <= 0) {
                भङ्ग;
            }

            // unadjust the dragRect from the window rect to the client rect
            समुच्चयः_Rect_रिक्तानि(&rc);
            यदि (!Adjust_गवाक्षः_Rect_Ex(&rc, Get_गवाक्षः_Style(hwnd), GetMenu(hwnd) != रिक्त, Get_गवाक्षः_Ex_Style(hwnd))) {
                भङ्ग;
            }

            clientDragRect.वामः -= rc.वामः;
            clientDragRect.शिखरम् -= rc.शिखरम्;
            clientDragRect.दक्षिणः -= rc.दक्षिणः;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.दक्षिणः - clientDragRect.वामः;
            h = clientDragRect.bottom - clientDragRect.शिखरम्;
            new_aspect = w / (भिन्न)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            यदि (तालकम्_aspect_अनुपातः) {
                विकल्प (edge) {
                पक्ष WMSZ_वामः:
                पक्ष WMSZ_दक्षिणः:
                    h = (पूर्णाङ्क)SDL_roundf(w / दत्त->गवाक्षः->max_aspect);
                    भङ्ग;
                स्वभाव:
                    // resizing via corners or top or bottom
                    w = (पूर्णाङ्क)SDL_roundf(h * दत्त->गवाक्षः->max_aspect);
                    भङ्ग;
                }
            } अन्यथा {
                विकल्प (edge) {
                पक्ष WMSZ_वामः:
                पक्ष WMSZ_दक्षिणः:
                    यदि (दत्त->गवाक्षः->max_aspect > 0.0f && new_aspect > दत्त->गवाक्षः->max_aspect) {
                        w = (पूर्णाङ्क)SDL_roundf(h * दत्त->गवाक्षः->max_aspect);
                    } अन्यथा यदि (दत्त->गवाक्षः->min_aspect > 0.0f && new_aspect < दत्त->गवाक्षः->min_aspect) {
                        w = (पूर्णाङ्क)SDL_roundf(h * दत्त->गवाक्षः->min_aspect);
                    }
                    भङ्ग;
                पक्ष WMSZ_शिखरम्:
                पक्ष WMSZ_BOTTOM:
                    यदि (दत्त->गवाक्षः->min_aspect > 0.0f && new_aspect < दत्त->गवाक्षः->min_aspect) {
                        h = (पूर्णाङ्क)SDL_roundf(w / दत्त->गवाक्षः->min_aspect);
                    } अन्यथा यदि (दत्त->गवाक्षः->max_aspect > 0.0f && new_aspect > दत्त->गवाक्षः->max_aspect) {
                        h = (पूर्णाङ्क)SDL_roundf(w / दत्त->गवाक्षः->max_aspect);
                    }
                    भङ्ग;

                स्वभाव:
                    // resizing via corners
                    यदि (दत्त->गवाक्षः->max_aspect > 0.0f && new_aspect > दत्त->गवाक्षः->max_aspect) {
                        w = (पूर्णाङ्क)SDL_roundf(h * दत्त->गवाक्षः->max_aspect);
                    } अन्यथा यदि (दत्त->गवाक्षः->min_aspect > 0.0f && new_aspect < दत्त->गवाक्षः->min_aspect) {
                        h = (पूर्णाङ्क)SDL_roundf(w / दत्त->गवाक्षः->min_aspect);
                    }
                    भङ्ग;
                }
            }

            विकल्प (edge) {
            पक्ष WMSZ_वामः:
                clientDragRect.वामः = clientDragRect.दक्षिणः - w;
                यदि (तालकम्_aspect_अनुपातः) {
                    clientDragRect.शिखरम् = (दत्त->initial_आकार_rect.bottom + दत्त->initial_आकार_rect.शिखरम् - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शिखरम्;
                भङ्ग;
            पक्ष WMSZ_BOTTOMLEFT:
                clientDragRect.वामः = clientDragRect.दक्षिणः - w;
                clientDragRect.bottom = h + clientDragRect.शिखरम्;
                भङ्ग;
            पक्ष WMSZ_दक्षिणः:
                clientDragRect.दक्षिणः = w + clientDragRect.वामः;
                यदि (तालकम्_aspect_अनुपातः) {
                    clientDragRect.शिखरम् = (दत्त->initial_आकार_rect.bottom + दत्त->initial_आकार_rect.शिखरम् - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.शिखरम्;
                भङ्ग;
            पक्ष WMSZ_TOPRIGHT:
                clientDragRect.दक्षिणः = w + clientDragRect.वामः;
                clientDragRect.शिखरम् = clientDragRect.bottom - h;
                भङ्ग;
            पक्ष WMSZ_शिखरम्:
                यदि (तालकम्_aspect_अनुपातः) {
                    clientDragRect.वामः = (दत्त->initial_आकार_rect.दक्षिणः + दत्त->initial_आकार_rect.वामः - w) / 2;
                }
                clientDragRect.दक्षिणः = w + clientDragRect.वामः;
                clientDragRect.शिखरम् = clientDragRect.bottom - h;
                भङ्ग;
            पक्ष WMSZ_TOPLEFT:
                clientDragRect.वामः = clientDragRect.दक्षिणः - w;
                clientDragRect.शिखरम् = clientDragRect.bottom - h;
                भङ्ग;
            पक्ष WMSZ_BOTTOM:
                यदि (तालकम्_aspect_अनुपातः) {
                    clientDragRect.वामः = (दत्त->initial_आकार_rect.दक्षिणः + दत्त->initial_आकार_rect.वामः - w) / 2;
                }
                clientDragRect.दक्षिणः = w + clientDragRect.वामः;
                clientDragRect.bottom = h + clientDragRect.शिखरम्;
                भङ्ग;
            पक्ष WMSZ_BOTTOMRIGHT:
                clientDragRect.दक्षिणः = w + clientDragRect.वामः;
                clientDragRect.bottom = h + clientDragRect.शिखरम्;
                भङ्ग;
            }

            // convert the client rect to a window rect
            यदि (!Adjust_गवाक्षः_Rect_Ex(&clientDragRect, Get_गवाक्षः_Style(hwnd), GetMenu(hwnd) != रिक्त, Get_गवाक्षः_Ex_Style(hwnd))) {
                भङ्ग;
            }

            *dragRect = clientDragRect;
        }
        भङ्ग;

    पक्ष WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        यदि (hittest == HTCLIENT) {
            समुच्चयः_Cursor(SDL_cursor);
            return_संहिता = TRUE;
        } अन्यथा यदि (!g_गवाक्षः_Frame_Usable_While_Cursor_Hidden && !SDL_cursor) {
            समुच्चयः_Cursor(रिक्त);
            return_संहिता = TRUE;
        }
    } भङ्ग;

        // We were occluded, refresh our display
    पक्ष WM_PAINT:
    {
        RECT rect;
        यदि (GetUpdateRect(hwnd, &rect, FALSE)) {
            ध्रुव LONG style = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            यदि (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                अन्तः_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, रिक्त);
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
        }
    }
        return_संहिता = 0;
        भङ्ग;

        // We'll do our own drawing, prevent flicker
    पक्ष WM_ERASEBKGND:
        यदि (Should_Clear_गवाक्षः_On_Erase_Background(दत्त)) {
            RECT client_rect;
            HBRUSH brush;
            दत्त->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        प्रत्यागम 1;

    पक्ष WM_SYSCOMMAND:
    {
        यदि (!g_WindowsEnableMenuMnemonics) {
            यदि ((wParam & 0xFFF0) == SC_KEYMENU) {
                प्रत्यागम 0;
            }
        }

#यदि defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        यदि ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            यदि (SDL_GetVideoDevice()->suspend_screensaver) {
                प्रत्यागम 0;
            }
        }
#यदि_अन्तः // System has screensaver support
    } भङ्ग;

    पक्ष WM_CLOSE:
    {
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
    }
        return_संहिता = 0;
        भङ्ग;

    पक्ष WM_TOUCH:
        यदि (दत्त->videodata->Get_Touch_निवेशः_Info && दत्त->videodata->Close_Touch_निवेशः_Handle) {
            UINT i, अङ्कः_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, अङ्कः_inputs, &isstack);
            यदि (inputs && दत्त->videodata->Get_Touch_निवेशः_Info((HTOUCHINPUT)lParam, अङ्कः_inputs, inputs, परिमाण(TOUCHINPUT))) {
                RECT rect;
                भिन्न x, y;

                यदि (!GetClientRect(hwnd, &rect) || !WIN_गवाक्षः_Rect_Valid(&rect)) {
                    यदि (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    भङ्ग;
                }
                Client_गन्तव्यम्_Screen(hwnd, (LPPOINT)&rect);
                Client_गन्तव्यम्_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.शिखरम् *= 100;
                rect.वामः *= 100;
                rect.bottom *= 100;
                rect.दक्षिणः *= 100;

                प्रति (i = 0; i < अङ्कः_inputs; ++i) {
                    PTOUCHINPUT निवेशः = &inputs[i];
                    ध्रुव पूर्णाङ्क w = (rect.दक्षिणः - rect.वामः);
                    ध्रुव पूर्णाङ्क h = (rect.bottom - rect.शिखरम्);

                    ध्रुव SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)निवेशः->hSource);
                    ध्रुव SDL_FingerID fingerId = (निवेशः->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    यदि (SDL_सङ्कलय_Touch(touchId, SDL_TOUCH_DEVICE_प्रत्यक्षम्, (निवेशः->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        अनुवर्त;
                    }

                    // Get the normalized coordinates for the window
                    यदि (w <= 1) {
                        x = 0.5f;
                    } अन्यथा {
                        x = (भिन्न)(निवेशः->x - rect.वामः) / (w - 1);
                    }
                    यदि (h <= 1) {
                        y = 0.5f;
                    } अन्यथा {
                        y = (भिन्न)(निवेशः->y - rect.शिखरम्) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    यदि (निवेशः->dwFlags & TOUCHEVENTF_अधस्तात्) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, दत्त->गवाक्षः, SDL_EVENT_FINGER_अधस्तात्, x, y, 1.0f);
                    }
                    यदि (निवेशः->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, दत्त->गवाक्षः, x, y, 1.0f);
                    }
                    यदि (निवेशः->dwFlags & TOUCHEVENTF_ऊर्ध्वम्) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, दत्त->गवाक्षः, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            दत्त->videodata->Close_Touch_निवेशः_Handle((HTOUCHINPUT)lParam);
            प्रत्यागम 0;
        }
        भङ्ग;

#यदि_परिभाषितम् HAVE_TPCSHRD_H

    पक्ष WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        प्रत्यागम TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#यदि_अन्तः // HAVE_TPCSHRD_H

    पक्ष WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT गणनम् = DragQueryFile(drop, 0xFFFFFFFF, रिक्त, 0);
        प्रति (i = 0; i < गणनम्; ++i) {
            UINT आकार = DragQueryFile(drop, i, रिक्त, 0) + 1;
            LPTSTR बफर_2 = (LPTSTR)SDL_malloc(परिमाण(TCHAR) * आकार);
            यदि (बफर_2) {
                यदि (DragQueryFile(drop, i, बफर_2, आकार)) {
                    वर्ण *file = WIN_String_गन्तव्यम्_UTF8(बफर_2);
                    SDL_SendDropFile(दत्त->गवाक्षः, रिक्त, file);
                    SDL_free(file);
                }
                SDL_free(बफर_2);
            }
        }
        SDL_SendDropComplete(दत्त->गवाक्षः);
        DragFinish(drop);
        प्रत्यागम 0;
    }

    पक्ष WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } भङ्ग;

    पक्ष WM_NCCALCSIZE:
    {
        SDL_गवाक्षः_Flags गवाक्षः_flags = दत्त->गवाक्षः->flags;
        यदि (wParam == TRUE && (गवाक्षः_flags & SDL_गवाक्षः_BORDERLESS) && !(गवाक्षः_flags & SDL_गवाक्षः_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            यदि (Get_गवाक्षः_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_गवाक्षः(hwnd, MONITOR_DEFAULTTONULL);
                यदि (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    ध्रुव POINT pt = { दत्त->गवाक्षः->windowed.x, दत्त->गवाक्षः->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                यदि (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_आकार = परिमाण(info);
                    यदि (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } अन्यथा यदि (!(गवाक्षः_flags & SDL_गवाक्षः_RESIZABLE) && !दत्त->force_ws_maximizebox) {
                पूर्णाङ्क w, h;
                यदि (दत्त->गवाक्षः->चरमः_आकार_pending) {
                    w = दत्त->गवाक्षः->pending.w;
                    h = दत्त->गवाक्षः->pending.h;
                } अन्यथा {
                    w = दत्त->गवाक्षः->floating.w;
                    h = दत्त->गवाक्षः->floating.h;
                }
                params->rgrc[0].दक्षिणः = params->rgrc[0].वामः + w;
                params->rgrc[0].bottom = params->rgrc[0].शिखरम् + h;
            }
            प्रत्यागम 0;
        }
    } भङ्ग;

    पक्ष WM_NCHITTEST:
    {
        SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

        यदि (गवाक्षः->flags & SDL_गवाक्षः_TOOLTIP) {
            प्रत्यागम HTTRANSPARENT;
        }

        यदि (गवाक्षः->लब्धम्_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            यदि (Screen_गन्तव्यम्_Client(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_लब्धम्_Test_परिणाम rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = गवाक्षः->लब्धम्_test(गवाक्षः, &point, गवाक्षः->लब्धम्_test_दत्त);
                विकल्प (rc) {
#परिभाषय POST_लब्धम्_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_लब्धम्_TEST, 0, 0); \
        प्रत्यागम ret;                                                        \
    }
                पक्ष SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(रिक्त, रिक्त);
                    यदि (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
                        प्रत्यागम HTCLIENT;
                    }

                    POST_लब्धम्_TEST(HTCAPTION);
                }
                पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_लब्धम्_TEST(HTTOPLEFT);
                पक्ष SDL_HITTEST_RESIZE_शिखरम्:
                    POST_लब्धम्_TEST(HTTOP);
                पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_लब्धम्_TEST(HTTOPRIGHT);
                पक्ष SDL_HITTEST_RESIZE_दक्षिणः:
                    POST_लब्धम्_TEST(HTRIGHT);
                पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_लब्धम्_TEST(HTBOTTOMRIGHT);
                पक्ष SDL_HITTEST_RESIZE_BOTTOM:
                    POST_लब्धम्_TEST(HTBOTTOM);
                पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_लब्धम्_TEST(HTBOTTOMLEFT);
                पक्ष SDL_HITTEST_RESIZE_वामः:
                    POST_लब्धम्_TEST(HTLEFT);
#अपरिभाषय POST_लब्धम्_TEST
                पक्ष SDL_HITTEST_प्रसामान्यम्:
                    प्रत्यागम HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } भङ्ग;

    पक्ष WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        यदि (दत्त->videodata->Get_Dpi_For_गवाक्षः && दत्त->videodata->Adjust_गवाक्षः_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            ध्रुव पूर्णाङ्क अग्र_DPI = (पूर्णाङ्क)wParam;
            ध्रुव पूर्णाङ्क पूर्व_DPI = (पूर्णाङ्क)दत्त->videodata->Get_Dpi_For_गवाक्षः(hwnd);
            आकार_3 *आकार_अन्तर्_बहिर्गमनम् = (आकार_3 *)lParam;

            पूर्णाङ्क frame_w, frame_h;
            पूर्णाङ्क query_client_w_win, query_client_h_win;

#यदि_परिभाषितम् HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    पूर्व_DPI, अग्र_DPI, आकार_अन्तर्_बहिर्गमनम्->cx, आकार_अन्तर्_बहिर्गमनम्->cy);
#यदि_अन्तः

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) && !SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः)) {
                    WIN_Adjust_गवाक्षः_Rect_For_HWND(hwnd, &rect, पूर्व_DPI);
                }

                frame_w = -rect.वामः + rect.दक्षिणः;
                frame_h = -rect.शिखरम् + rect.bottom;

                query_client_w_win = आकार_अन्तर्_बहिर्गमनम्->cx - frame_w;
                query_client_h_win = आकार_अन्तर्_बहिर्गमनम्->cy - frame_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.दक्षिणः = query_client_w_win;
                rect.bottom = query_client_h_win;

                यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) && !SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः)) {
                    WIN_Adjust_गवाक्षः_Rect_For_HWND(hwnd, &rect, अग्र_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                आकार_अन्तर्_बहिर्गमनम्->cx = rect.दक्षिणः - rect.वामः;
                आकार_अन्तर्_बहिर्गमनम्->cy = rect.bottom - rect.शिखरम्;
            }

#यदि_परिभाषितम् HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", आकार_अन्तर्_बहिर्गमनम्->cx, आकार_अन्तर्_बहिर्गमनम्->cy);
#यदि_अन्तः
            प्रत्यागम TRUE;
        }
        भङ्ग;

    पक्ष WM_DPICHANGED:
        // Windows 8.1+
        {
            ध्रुव पूर्णाङ्क newDPI = HIWORD(wParam);
            RECT *ध्रुव suggestedRect = (RECT *)lParam;
            पूर्णाङ्क w, h;

#यदि_परिभाषितम् HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->वामः, suggestedRect->शिखरम्, suggestedRect->दक्षिणः - suggestedRect->वामः, suggestedRect->bottom - suggestedRect->शिखरम्);
#यदि_अन्तः

            यदि (दत्त->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#यदि_परिभाषितम् HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#यदि_अन्तः
                प्रत्यागम 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.दक्षिणः = दत्त->गवाक्षः->w;
                rect.bottom = दत्त->गवाक्षः->h;

                यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS)) {
                    WIN_Adjust_गवाक्षः_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.दक्षिणः - rect.वामः;
                h = rect.bottom - rect.शिखरम्;
            }

#यदि_परिभाषितम् HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    दत्त->गवाक्षः->w, दत्त->गवाक्षः->h,
                    suggestedRect->वामः, suggestedRect->शिखरम्, w, h);
#यदि_अन्तः

            दत्त->expected_resize = true;
            समुच्चयः_गवाक्षः_Pos(hwnd,
                         रिक्त,
                         suggestedRect->वामः,
                         suggestedRect->शिखरम्,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            दत्त->expected_resize = false;
            प्रत्यागम 0;
        }

    पक्ष WM_SETTINGCHANGE:
        यदि (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_समुच्चयः_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_बहुलकम्_For_HWND(hwnd);
        }
        यदि (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        यदि (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        भङ्ग;
#अन्यथा
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    पक्ष WM_आकार:
    {
        RECT rect;
        पूर्णाङ्क w, h;

        यदि (GetClientRect(hwnd, &rect) && WIN_गवाक्षः_Rect_Valid(&rect)) {
            w = rect.दक्षिणः;
            h = rect.bottom;
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, w, h);
        }
    } भङ्ग;
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    स्वभाव:
        भङ्ग;
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (सन्देशः_2 && सन्देशः_2 == दत्त->videodata->WM_TASKBAR_BUTTON_CREATED) {
        दत्त->taskbar_button_created = true;
        WIN_Apply_गवाक्षः_प्रगतिः(SDL_GetVideoDevice(), दत्त->गवाक्षः);
    }
#यदि_अन्तः

    // If there's a window proc, assume it's going to handle messages
    यदि (दत्त->wndproc) {
        प्रत्यागम Call_गवाक्षः_Proc(दत्त->wndproc, hwnd, सन्देशः_2, wParam, lParam);
    } अन्यथा यदि (return_संहिता >= 0) {
        प्रत्यागम return_संहिता;
    } अन्यथा {
        प्रत्यागम Call_गवाक्षः_Proc(Def_गवाक्षः_Proc, hwnd, सन्देशः_2, wParam, lParam);
    }
}

पूर्णाङ्क WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    यदि (g_Windows_Enable_सन्देशः_Loop) {
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_गन्तव्यम्_MS(timeoutNS);
        ret = सन्देशः_Wait_For_गुणजः_Objects(0, रिक्त, FALSE, timeout, QS_ALLINPUT);
        यदि (ret == WAIT_OBJECT_0) {
            प्रत्यागम 1;
        } अन्यथा {
            प्रत्यागम 0;
        }
#अन्यथा
        // MsgWaitForMultipleObjects is desktop-only.
        सन्देशः_3 सन्देशः_2;
        BOOL सन्देशः_परिणाम;
        UINT_PTR timer_id = 0;
        यदि (timeoutNS > 0) {
            timer_id = समुच्चयः_Timer(रिक्त, 0, (UINT)SDL_NS_गन्तव्यम्_MS(timeoutNS), रिक्त);
            सन्देशः_परिणाम = Get_सन्देशः(&सन्देशः_2, 0, 0, 0);
            KillTimer(रिक्त, timer_id);
        } अन्यथा यदि (timeoutNS == 0) {
            सन्देशः_परिणाम = Peek_सन्देशः(&सन्देशः_2, रिक्त, 0, 0, PM_REMOVE);
        } अन्यथा {
            सन्देशः_परिणाम = Get_सन्देशः(&सन्देशः_2, 0, 0, 0);
        }
        यदि (सन्देशः_परिणाम) {
            यदि (सन्देशः_2.सन्देशः == WM_TIMER && !सन्देशः_2.hwnd && सन्देशः_2.wParam == timer_id) {
                प्रत्यागम 0;
            }
            यदि (g_Windows_सन्देशः_Hook) {
                यदि (!g_Windows_सन्देशः_Hook(g_Windows_सन्देशः_Hook_दत्त, &सन्देशः_2)) {
                    प्रत्यागम 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_सन्देशः(&सन्देशः_2);
            Dispatch_सन्देशः(&सन्देशः_2);
            प्रत्यागम 1;
        } अन्यथा {
            प्रत्यागम 0;
        }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } अन्यथा {
        // Fail the wait so the caller falls back to polling
        प्रत्यागम -1;
    }
}

शून्य WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Post_सन्देशः(दत्त->hwnd, दत्त->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
शून्य WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    सन्देशः_3 सन्देशः_2;

    यदि (g_Windows_Enable_सन्देशः_Loop) {
        SDL_processing_messages = true;

        यावत् (Peek_सन्देशः(&सन्देशः_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_समुच्चयः_सन्देशः_Tick(सन्देशः_2.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_सन्देशः(&सन्देशः_2);
            Dispatch_सन्देशः(&सन्देशः_2);
        }

        SDL_processing_messages = false;
    }
}

शून्य WIN_PumpEvents(SDL_VideoDevice *_this)
{
    सन्देशः_3 सन्देशः_2;
#यदि_परिभाषितम् _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#निर्देशः warning(प्रक्षिप)
#निर्देशः warning(disable : 28159)
#यदि_अन्तः
    DWORD अन्तः_ticks = Get_Tick_गणनम्() + 1;
#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning(निष्कासय)
#यदि_अन्तः
    पूर्णाङ्क new_messages = 0;

    यदि (_this->आन्तरिकम्->gameinput_context) {
        WIN_Update_Game_निवेशः(_this);
    }

    यदि (g_Windows_Enable_सन्देशः_Loop) {
        SDL_processing_messages = true;

        यावत् (Peek_सन्देशः(&सन्देशः_2, रिक्त, 0, 0, PM_REMOVE)) {
            यदि (g_Windows_सन्देशः_Hook) {
                यदि (!g_Windows_सन्देशः_Hook(g_Windows_सन्देशः_Hook_दत्त, &सन्देशः_2)) {
                    अनुवर्त;
                }
            }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            यदि (सन्देशः_2.सन्देशः == WM_MOUSEMOVE && SDL_चरमः_warp_time) {
                यदि (!SDL_TICKS_PASSED(सन्देशः_2.time, (SDL_चरमः_warp_time + 1))) {
                    अनुवर्त;
                }

                // This mouse message happened after the warp
                SDL_चरमः_warp_time = 0;
            }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_समुच्चयः_सन्देशः_Tick(सन्देशः_2.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_सन्देशः(&सन्देशः_2);
            Dispatch_सन्देशः(&सन्देशः_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            यदि (SDL_TICKS_PASSED(सन्देशः_2.time, अन्तः_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                ध्रुव पूर्णाङ्क MAX_NEW_MESSAGES = 3;
                ++new_messages;
                यदि (new_messages > MAX_NEW_MESSAGES) {
                    भङ्ग;
                }
            }
        }

        SDL_processing_messages = false;
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    ध्रुव bool *keystate = SDL_GetKeyboardState(रिक्त);
    यदि (keystate[SDL_SCANCODE_LSHIFT] && !(Get_कुञ्चिका_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    यदि (keystate[SDL_SCANCODE_RSHIFT] && !(Get_कुञ्चिका_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_गवाक्षः *focus_गवाक्षः = SDL_GetKeyboardFocus();
    यदि (!focus_गवाक्षः || !(focus_गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED)) {
        यदि (keystate[SDL_SCANCODE_LGUI] && !(Get_कुञ्चिका_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        यदि (keystate[SDL_SCANCODE_RGUI] && !(Get_कुञ्चिका_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    यदि (_this) {
        SDL_गवाक्षः *गवाक्षः = _this->windows;
        यावत् (गवाक्षः) {
            bool refresh_clipcursor = false;
            SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
            यदि (दत्त) {
                refresh_clipcursor = दत्त->clipcursor_queued;
                दत्त->clipcursor_queued = false;    // Must be cleared unconditionally.
                दत्त->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            यदि (refresh_clipcursor) {
                WIN_UpdateClipCursor(गवाक्षः);
            }
            गवाक्षः = गवाक्षः->अग्र;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_गवाक्षः = SDL_GetKeyboardFocus();
    यदि (focus_गवाक्षः && (focus_गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
        SDL_गवाक्षः_दत्त *दत्त = focus_गवाक्षः->आन्तरिकम्;

        यदि (!दत्त->mouse_tracked) {
            POINT cursorPos;

            यदि (GetCursorPos(&cursorPos) && Screen_गन्तव्यम्_Client(दत्त->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID, false, (भिन्न)cursorPos.x, (भिन्न)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID,
                                    !swapButtons ? SDL_BUTTON_वामः : SDL_BUTTON_दक्षिणः,
                                    (Get_Async_कुञ्चिका_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID,
                                    !swapButtons ? SDL_BUTTON_दक्षिणः : SDL_BUTTON_वामः,
                                    (Get_Async_कुञ्चिका_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID,
                                    SDL_BUTTON_मध्यः,
                                    (Get_Async_कुञ्चिका_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_कुञ्चिका_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), दत्त->गवाक्षः, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_कुञ्चिका_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#यदि_परिभाषितम् SDL_PLATFORM_GDK
    GDK_DispatchTaskQueue();
#यदि_अन्तः
}

स्थिर पूर्णाङ्क app_registered = 0;
LPTSTR SDL_Appname = रिक्त;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = रिक्त;

स्थिर शून्य WIN_Clean_पञ्जिकाकोशः_App(WNDCLASSEX wcex)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    यदि (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#यदि_अन्तः
    SDL_free(SDL_Appname);
    SDL_Appname = रिक्त;
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (शून्य)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = आरोपय_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    प्रत्यागम FALSE;
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_पञ्जिकाकोशः_App(ध्रुव वर्ण *name, Uint32 style, शून्य *hInst)
{
    WNDCLASSEX wcex;
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ध्रुव वर्ण *hint;
#यदि_अन्तः

    // Only do this once...
    यदि (app_registered) {
        ++app_registered;
        प्रत्यागम true;
    }
    SDL_assert(!SDL_Appname);
    यदि (!name) {
        name = "SDL_app";
#यदि defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#यदि_अन्तः
    }
    SDL_Appname = WIN_UTF8_गन्तव्यम्_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(रिक्त);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_आकार = परिमाण(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_गवाक्षः_Proc;
    wcex.hInstance = SDL_Instance;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    यदि (hint && *hint) {
        wcex.hIcon = आरोपय_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        यदि (hint && *hint) {
            wcex.hIconSm = आरोपय_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } अन्यथा {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_नामानि(SDL_Instance, RT_गणः_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    यदि (!पञ्जिकाकोशः_Class_Ex(&wcex)) {
        WIN_Clean_पञ्जिकाकोशः_App(wcex);
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't register application class");
    }

    app_registered = 1;
    प्रत्यागम true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
शून्य SDL_UnregisterApp(शून्य)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    यदि (!app_registered) {
        प्रत्यागम;
    }
    --app_registered;
    यदि (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = रिक्त;
        wcex.hIconSm = रिक्त;
        // Check for any registered window classes.
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        यदि (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#यदि_अन्तः
        WIN_Clean_पञ्जिकाकोशः_App(wcex);
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
