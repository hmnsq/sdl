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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"
#అన్తర్భావ "../../events/scancodes_windows.h"
#అన్తర్భావ "../../main/SDL_main_callbacks.h"
#అన్తర్భావ "../../core/windows/SDL_hid.h"

// Dropfile support
#అన్తర్భావ <shellapi.h>

// Device names
#అన్తర్భావ <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#అన్తర్భావ <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#నిర్వచితమైతే HAVE_TPCSHRD_H
#అన్తర్భావ <tpcshrd.h>
#అయితే_ముగింపు // HAVE_TPCSHRD_H

#ఒకవేళ 0
#నిర్వచించు WMMSG_DEBUG
#అయితే_ముగింపు
#నిర్వచితమైతే WMMSG_DEBUG
#అన్తర్భావ <stdio.h>
#అన్తర్భావ "wmmsg.h"
#అయితే_ముగింపు

#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#అన్తర్భావ <shobjidl.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_PLATFORM_GDK
#అన్తర్భావ "../../core/gdk/SDL_gdk.h"
#అయితే_ముగింపు

// #define HIGHDPI_DEBUG

// Undocumented window messages
#నిర్వచితం_కాకపోతే WM_NCUAHDRAWCAPTION
#నిర్వచించు WM_NCUAHDRAWCAPTION 0xAE
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_NCUAHDRAWFRAME
#నిర్వచించు WM_NCUAHDRAWFRAME 0xAF
#అయితే_ముగింపు

// Make sure XBUTTON stuff is defined that isn't in older Platform SDKs...
#నిర్వచితం_కాకపోతే WM_XBUTTONDOWN
#నిర్వచించు WM_XBUTTONDOWN 0x020B
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_XBUTTONUP
#నిర్వచించు WM_XBUTTONUP 0x020C
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే GET_XBUTTON_WPARAM
#నిర్వచించు GET_XBUTTON_WPARAM(w) (HIWORD(w))
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_ఆదానం
#నిర్వచించు WM_ఆదానం 0x00ff
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_TOUCH
#నిర్వచించు WM_TOUCH 0x0240
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_MOUSEHWHEEL
#నిర్వచించు WM_MOUSEHWHEEL 0x020E
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే RI_MOUSE_HWHEEL
#నిర్వచించు RI_MOUSE_HWHEEL 0x0800
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERUPDATE
#నిర్వచించు WM_POINTERUPDATE 0x0245
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERDOWN
#నిర్వచించు WM_POINTERDOWN 0x0246
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERUP
#నిర్వచించు WM_POINTERUP 0x0247
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERENTER
#నిర్వచించు WM_POINTERENTER 0x0249
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERLEAVE
#నిర్వచించు WM_POINTERLEAVE 0x024A
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_POINTERCAPTURECHANGED
#నిర్వచించు WM_POINTERCAPTURECHANGED 0x024C
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_UNICHAR
#నిర్వచించు WM_UNICHAR 0x0109
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_DPICHANGED
#నిర్వచించు WM_DPICHANGED 0x02E0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే WM_GETDPISCALEDSIZE
#నిర్వచించు WM_GETDPISCALEDSIZE 0x02E4
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే TOUCHEVENTF_PEN
#నిర్వచించు TOUCHEVENTF_PEN 0x0040
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే MAPVK_VK_గమ్యం_VSC_EX
#నిర్వచించు MAPVK_VK_గమ్యం_VSC_EX 4
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WC_ERR_INVALID_CHARS
#నిర్వచించు WC_ERR_INVALID_CHARS 0x00000080
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే IS_ఎగువ_SURROGATE
#నిర్వచించు IS_ఎగువ_SURROGATE(x) (((x) >= 0xd800) && ((x) <= 0xdbff))
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే USER_TIMER_MINIMUM
#నిర్వచించు USER_TIMER_MINIMUM 0x0000000A
#అయితే_ముగింపు

// Used to compare Windows message timestamps
#నిర్వచించు SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

#నిర్వచితమైతే _WIN64
రకనిర్వచనం Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#అయితే_ముగింపు

స్థిర bool SDL_processing_messages;
స్థిర DWORD సందేశం_tick;
స్థిర Uint64 timestamp_స్థానభ్రంశం;

స్థిర శూన్య WIN_సమితి_సందేశం_Tick(DWORD tick)
{
    సందేశం_tick = tick;
}

స్థిర Uint64 WIN_GetEventTimestamp(శూన్య)
{
    స్థిరరాశి Uint64 TIMESTAMP_WRAP_స్థానభ్రంశం = SDL_MS_గమ్యం_NS(0x100000000LL);
    Uint64 timestamp, now;

    ఒకవేళ (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        తిరిగి 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_గమ్యం_NS(సందేశం_tick);
    timestamp += timestamp_స్థానభ్రంశం;
    ఒకవేళ (!timestamp_స్థానభ్రంశం) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_స్థానభ్రంశం = (now - timestamp);
        timestamp = now;
    } లేకపోతే ఒకవేళ ((Sint64)(now - timestamp - TIMESTAMP_WRAP_స్థానభ్రంశం) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_స్థానభ్రంశం += TIMESTAMP_WRAP_స్థానభ్రంశం;
        timestamp += TIMESTAMP_WRAP_స్థానభ్రంశం;
    } లేకపోతే ఒకవేళ (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_స్థానభ్రంశం -= (timestamp - now);
        timestamp = now;
    }
    తిరిగి timestamp;
}

// A message hook called before TranslateMessage()
స్థిర SDL_Windows_సందేశం_Hook g_Windows_సందేశం_Hook = ఖాళీ;
స్థిర శూన్య *g_Windows_సందేశం_Hook_దత్తాంశం = ఖాళీ;

శూన్య SDL_సమితి_Windows_సందేశం_Hook(SDL_Windows_సందేశం_Hook callback, శూన్య *userdata)
{
    g_Windows_సందేశం_Hook = callback;
    g_Windows_సందేశం_Hook_దత్తాంశం = userdata;
}

స్థిర SDL_Scancode Windows_పరిశీలన_సంకేతం_గమ్యం_SDLScan_సంకేతం(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_కీలకం)
{
    SDL_Scancode సంకేతం_2;
    Uint8 సూచీ;
    Uint16 కీలకం_Flags = HIWORD(lParam);
    Uint16 పరిశీలన_సంకేతం = LOBYTE(కీలకం_Flags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    పరిశీలన_సంకేతం &= ~0x80;

    *virtual_కీలకం = (పరిశీలన_సంకేతం == 0);

    ఒకవేళ (పరిశీలన_సంకేతం != 0) {
        ఒకవేళ ((కీలకం_Flags & KF_EXTENDED) == KF_EXTENDED) {
            పరిశీలన_సంకేతం = MAKEWORD(పరిశీలన_సంకేతం, 0xe0);
        } లేకపోతే ఒకవేళ (పరిశీలన_సంకేతం == 0x45) {
            // Pause
            పరిశీలన_సంకేతం = 0xe046;
        }
    } లేకపోతే {
        Uint16 vk_సంకేతం = LOWORD(wParam);

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        పరిశీలన_సంకేతం = LOWORD(Map_Virtual_కీలకం(vk_సంకేతం, WIN_IsWindowsXP() ? MAPVK_VK_గమ్యం_VSC : MAPVK_VK_గమ్యం_VSC_EX));
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        ఒకవేళ (పరిశీలన_సంకేతం == 0xe11d) {
            పరిశీలన_సంకేతం = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    సూచీ = LOBYTE(పరిశీలన_సంకేతం) | (HIBYTE(పరిశీలన_సంకేతం) ? 0x80 : 0x00);
    సంకేతం_2 = windows_scancode_పట్టిక[సూచీ];
    *rawcode = పరిశీలన_సంకేతం;

    తిరిగి సంకేతం_2;
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
స్థిర bool WIN_ShouldIgnoreFocusClick(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    తిరిగి !SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

స్థిర శూన్య WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool b_మార్పిడి_Buttons, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, Uint8 button, SDL_MouseID mouseID)
{
    ఒకవేళ (b_మార్పిడి_Buttons) {
        ఒకవేళ (button == SDL_BUTTON_ఎడమ) {
            button = SDL_BUTTON_కుడి;
        } లేకపోతే ఒకవేళ (button == SDL_BUTTON_కుడి) {
            button = SDL_BUTTON_ఎడమ;
        }
    }

    ఒకవేళ (దత్తాంశం->focus_click_pending & SDL_BUTTON_ముసుగు(button)) {
        // Ignore the button click for activation
        ఒకవేళ (!bwParamMousePressed) {
            దత్తాంశం->focus_click_pending &= ~SDL_BUTTON_ముసుగు(button);
            WIN_UpdateClipCursor(దత్తాంశం->కిటికీ);
        }
        తిరిగి;
    }

    ఒకవేళ (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_ముసుగు(button))) {
        SDL_SendMouseButton(timestamp, దత్తాంశం->కిటికీ, mouseID, button, true);
    } లేకపోతే ఒకవేళ (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_ముసుగు(button))) {
        SDL_SendMouseButton(timestamp, దత్తాంశం->కిటికీ, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
స్థిర శూన్య WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, SDL_MouseID mouseID)
{
    ఒకవేళ (wParam != దత్తాంశం->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(ఖాళీ, ఖాళీ);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, దత్తాంశం, SDL_BUTTON_ఎడమ, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, దత్తాంశం, SDL_BUTTON_మధ్య, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, దత్తాంశం, SDL_BUTTON_కుడి, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, దత్తాంశం, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, దత్తాంశం, SDL_BUTTON_X2, mouseID);

        దత్తాంశం->mouse_button_flags = wParam;
    }
}

స్థిర శూన్య WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT కీలకం_State;
    bool మార్పిడి_Buttons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(ఖాళీ, ఖాళీ);
    మార్పిడి_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    కీలకం_State = Get_Async_కీలకం_State(VK_LBUTTON);
    ఒకవేళ (!(కీలకం_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, మార్పిడి_Buttons, దత్తాంశం, SDL_BUTTON_ఎడమ, mouseID);
    }
    కీలకం_State = Get_Async_కీలకం_State(VK_RBUTTON);
    ఒకవేళ (!(కీలకం_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, మార్పిడి_Buttons, దత్తాంశం, SDL_BUTTON_కుడి, mouseID);
    }
    కీలకం_State = Get_Async_కీలకం_State(VK_MBUTTON);
    ఒకవేళ (!(కీలకం_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, మార్పిడి_Buttons, దత్తాంశం, SDL_BUTTON_మధ్య, mouseID);
    }
    కీలకం_State = Get_Async_కీలకం_State(VK_XBUTTON1);
    ఒకవేళ (!(కీలకం_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, మార్పిడి_Buttons, దత్తాంశం, SDL_BUTTON_X1, mouseID);
    }
    కీలకం_State = Get_Async_కీలకం_State(VK_XBUTTON2);
    ఒకవేళ (!(కీలకం_State & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, మార్పిడి_Buttons, దత్తాంశం, SDL_BUTTON_X2, mouseID);
    }
    దత్తాంశం->mouse_button_flags = (WPARAM)-1;
}

స్థిర శూన్య WIN_UpdateFocus(SDL_కిటికీ *కిటికీ, bool expect_focus, LPPOINT pos)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == కిటికీ);
    bool has_focus = (Get_Foreground_కిటికీ() == hwnd);

    ఒకవేళ (had_focus == has_focus || has_focus != expect_focus) {
        తిరిగి;
    }

    ఒకవేళ (has_focus) {
        బిందువు_2 cursorPos;

        ఒకవేళ (WIN_ShouldIgnoreFocusClick(దత్తాంశం) && !(కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
            bool మార్పిడి_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            ఒకవేళ (Get_Async_కీలకం_State(VK_LBUTTON)) {
                దత్తాంశం->focus_click_pending |= !మార్పిడి_Buttons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            ఒకవేళ (Get_Async_కీలకం_State(VK_RBUTTON)) {
                దత్తాంశం->focus_click_pending |= !మార్పిడి_Buttons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            ఒకవేళ (Get_Async_కీలకం_State(VK_MBUTTON)) {
                దత్తాంశం->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            ఒకవేళ (Get_Async_కీలకం_State(VK_XBUTTON1)) {
                దత్తాంశం->focus_click_pending |= SDL_BUTTON_X1_ముసుగు;
            }
            ఒకవేళ (Get_Async_కీలకం_State(VK_XBUTTON2)) {
                దత్తాంశం->focus_click_pending |= SDL_BUTTON_X2_ముసుగు;
            }
        }

        SDL_సమితి_Keyboard_Focus(కిటికీ->keyboard_focus ? కిటికీ->keyboard_focus : కిటికీ);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        ఒకవేళ (!SDL_GetMouse()->relative_బహుళకం) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            Screen_గమ్యం_Client(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)cursorPos.x, (దశాంశం)cursorPos.y);
        }

        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), దత్తాంశం);
        WIN_UpdateClipCursor(కిటికీ);

        /*
         * FIXME: Update keyboard state
         */
        WIN_CheckClipboardUpdate(దత్తాంశం->videodata);

        SDL_ToggleModState(SDL_KMOD_CAPS, (Get_కీలకం_State(VK_CAPITAL) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_అంకె, (Get_కీలకం_State(VK_NUMLOCK) & 0x0001) ? true : false);
        SDL_ToggleModState(SDL_KMOD_SCROLL, (Get_కీలకం_State(VK_SCROLL) & 0x0001) ? true : false);

        WIN_Update_కిటికీ_ICCProfile(దత్తాంశం->కిటికీ, true);
    } లేకపోతే {
        దత్తాంశం->లోపల_కిటికీ_deactivation = true;

        SDL_సమితి_Keyboard_Focus(ఖాళీ);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        ఒకవేళ (SDL_GetMouse()->relative_బహుళకం) {
            SDL_సమితి_Mouse_Focus(ఖాళీ);
        }
        WIN_Reset_Dead_కీలకాలు();

        WIN_Unclip_Cursor_For_కిటికీ(కిటికీ);

        దత్తాంశం->లోపల_కిటికీ_deactivation = false;
    }
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

స్థిర bool Should_Generate_కిటికీ_Close_On_Alt_F4(శూన్య)
{
    తిరిగి SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

స్థిర bool Should_Clear_కిటికీ_On_Erase_Background(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    ఎంపిక (దత్తాంశం->hint_erase_background_బహుళకం) {
    స్థితి SDL_ERASEBACKGROUNDMODE_NEVER:
        తిరిగి false;
    స్థితి SDL_ERASEBACKGROUNDMODE_INITIAL:
        తిరిగి !దత్తాంశం->videodata->cleared;
    స్థితి SDL_ERASEBACKGROUNDMODE_ALWAYS:
        తిరిగి true;
    అప్రమేయ:
        // Unexpected value, fallback to default behaviour
        తిరిగి !దత్తాంశం->videodata->cleared;
    }
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#నిర్వచించు MI_WP_SIGNATURE      0xFF515700
#నిర్వచించు MI_WP_SIGNATURE_ముసుగు 0xFFFFFF00
#నిర్వచించు IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_ముసుగు) == MI_WP_SIGNATURE

రకనిర్వచనం గణన
{
    SDL_MOUSE_EVENT_ఆధారం_UNKNOWN,
    SDL_MOUSE_EVENT_ఆధారం_MOUSE,
    SDL_MOUSE_EVENT_ఆధారం_TOUCH,
    SDL_MOUSE_EVENT_ఆధారం_PEN,
} SDL_MOUSE_EVENT_ఆధారం;

స్థిర SDL_MOUSE_EVENT_ఆధారం Get_Mouse_సందేశం_ఆధారం(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    ఒకవేళ (IsTouchEvent(extrainfo)) {
        ఒకవేళ (extrainfo & 0x80) {
            తిరిగి SDL_MOUSE_EVENT_ఆధారం_TOUCH;
        } లేకపోతే {
            తిరిగి SDL_MOUSE_EVENT_ఆధారం_PEN;
        }
    }
    తిరిగి SDL_MOUSE_EVENT_ఆధారం_MOUSE;
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

స్థిర SDL_కిటికీ_దత్తాంశం *WIN_Get_కిటికీ_దత్తాంశం_From_HWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_కిటికీ *కిటికీ;

    ఒకవేళ (_this) {
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
            ఒకవేళ (దత్తాంశం && దత్తాంశం->hwnd == hwnd) {
                తిరిగి దత్తాంశం;
            }
        }
    }
    తిరిగి ఖాళీ;
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(పూర్ణాంకం n_సంకేతం, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hook_దత్తాంశం = (KBDLLHOOKSTRUCT *)lParam;
    SDL_Video_దత్తాంశం *దత్తాంశం = SDL_GetVideoDevice()->అంతర్గత;
    SDL_Scancode పరిశీలన_సంకేతం;

    ఒకవేళ (n_సంకేతం < 0 || n_సంకేతం != HC_ACTION) {
        తిరిగి Call_తదుపరి_Hook_Ex(ఖాళీ, n_సంకేతం, wParam, lParam);
    }
    ఒకవేళ (hook_దత్తాంశం->పరిశీలన_సంకేతం == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        తిరిగి 1;
    }

    ఎంపిక (hook_దత్తాంశం->vk_సంకేతం) {
    స్థితి VK_LWIN:
        పరిశీలన_సంకేతం = SDL_SCANCODE_LGUI;
        ఆపు;
    స్థితి VK_RWIN:
        పరిశీలన_సంకేతం = SDL_SCANCODE_RGUI;
        ఆపు;
    స్థితి VK_LMENU:
        పరిశీలన_సంకేతం = SDL_SCANCODE_LALT;
        ఆపు;
    స్థితి VK_RMENU:
        పరిశీలన_సంకేతం = SDL_SCANCODE_RALT;
        ఆపు;
    స్థితి VK_LCONTROL:
        పరిశీలన_సంకేతం = SDL_SCANCODE_LCTRL;
        ఆపు;
    స్థితి VK_RCONTROL:
        పరిశీలన_సంకేతం = SDL_SCANCODE_RCTRL;
        ఆపు;
    స్థితి VK_SNAPSHOT:
        పరిశీలన_సంకేతం = SDL_SCANCODE_PRINTSCREEN;
        ఆపు;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    స్థితి VK_TAB:
        పరిశీలన_సంకేతం = SDL_SCANCODE_TAB;
        ఆపు;
    స్థితి VK_ESCAPE:
        పరిశీలన_సంకేతం = SDL_SCANCODE_ESCAPE;
        ఆపు;

    అప్రమేయ:
        తిరిగి Call_తదుపరి_Hook_Ex(ఖాళీ, n_సంకేతం, wParam, lParam);
    }

    ఒకవేళ (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        ఒకవేళ (!దత్తాంశం->raw_keyboard_enabled) {
            SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, hook_దత్తాంశం->పరిశీలన_సంకేతం, పరిశీలన_సంకేతం, true);
        }
    } లేకపోతే {
        ఒకవేళ (!దత్తాంశం->raw_keyboard_enabled) {
            SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, hook_దత్తాంశం->పరిశీలన_సంకేతం, పరిశీలన_సంకేతం, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        ఒకవేళ (hook_దత్తాంశం->vk_సంకేతం <= 0xFF && దత్తాంశం->pre_hook_కీలకం_state[hook_దత్తాంశం->vk_సంకేతం]) {
            దత్తాంశం->pre_hook_కీలకం_state[hook_దత్తాంశం->vk_సంకేతం] = 0;
            తిరిగి Call_తదుపరి_Hook_Ex(ఖాళీ, n_సంకేతం, wParam, lParam);
        }
    }

    తిరిగి 1;
}

స్థిర bool WIN_మార్పిడి_Buttons(HANDLE hDevice)
{
    ఒకవేళ (hDevice == ఖాళీ) {
        // Touchpad, already has buttons swapped
        తిరిగి false;
    }
    తిరిగి GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

స్థిర శూన్య WIN_Handle_Raw_Mouse_ఆదానం(Uint64 timestamp, SDL_Video_దత్తాంశం *దత్తాంశం, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    స్థిర నిర్మాణం {
        USHORT usButtonFlags;
        Uint8 button;
        bool కిందికి;
    } raw_buttons[] = {
        { RI_MOUSE_ఎడమ_BUTTON_కిందికి, SDL_BUTTON_ఎడమ, true },
        { RI_MOUSE_ఎడమ_BUTTON_పైకి, SDL_BUTTON_ఎడమ, false },
        { RI_MOUSE_కుడి_BUTTON_కిందికి, SDL_BUTTON_కుడి, true },
        { RI_MOUSE_కుడి_BUTTON_పైకి, SDL_BUTTON_కుడి, false },
        { RI_MOUSE_మధ్య_BUTTON_కిందికి, SDL_BUTTON_మధ్య, true },
        { RI_MOUSE_మధ్య_BUTTON_పైకి, SDL_BUTTON_మధ్య, false },
        { RI_MOUSE_BUTTON_4_కిందికి, SDL_BUTTON_X1, true },
        { RI_MOUSE_BUTTON_4_పైకి, SDL_BUTTON_X1, false },
        { RI_MOUSE_BUTTON_5_కిందికి, SDL_BUTTON_X2, true },
        { RI_MOUSE_BUTTON_5_పైకి, SDL_BUTTON_X2, false }
    };

    పూర్ణాంకం dx = (పూర్ణాంకం)rawmouse->l_చివరి_X;
    పూర్ణాంకం dy = (పూర్ణాంకం)rawmouse->l_చివరి_Y;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    ఒకవేళ (!దత్తాంశం->raw_mouse_enabled) {
        తిరిగి;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_కిటికీ *కిటికీ = SDL_GetKeyboardFocus();
    ఒకవేళ (!కిటికీ) {
        తిరిగి;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    ఒకవేళ (!mouse) {
        తిరిగి;
    }

    ఒకవేళ (Get_Mouse_సందేశం_ఆధారం(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_ఆధారం_MOUSE ||
        (SDL_Touch_Devices_అందుబాటు() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        తిరిగి;
    }

    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;

    ఒకవేళ (haveMotion && !windowdata->లోపల_modal_loop) {
        ఒకవేళ (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, కిటికీ, mouseID, true, (దశాంశం)dx, (దశాంశం)dy);
        } లేకపోతే {
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
            పూర్ణాంకం w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            పూర్ణాంకం h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            పూర్ణాంకం x = raw_coordinates ? dx : (పూర్ణాంకం)(((దశాంశం)dx / 65535.0f) * w);
            పూర్ణాంకం y = raw_coordinates ? dy : (పూర్ణాంకం)(((దశాంశం)dy / 65535.0f) * h);
            పూర్ణాంకం relX, relY;

            /* Calculate relative motion */
            ఒకవేళ (దత్తాంశం->చివరి_raw_mouse_position.x == 0 && దత్తాంశం->చివరి_raw_mouse_position.y == 0) {
                దత్తాంశం->చివరి_raw_mouse_position.x = x;
                దత్తాంశం->చివరి_raw_mouse_position.y = y;
            }
            relX = x - దత్తాంశం->చివరి_raw_mouse_position.x;
            relY = y - దత్తాంశం->చివరి_raw_mouse_position.y;

            ఒకవేళ (remote_desktop) {
                ఒకవేళ (!windowdata->లోపల_title_click && !windowdata->focus_click_pending) {
                    స్థిర పూర్ణాంకం wobble;
                    దశాంశం floatX = (దశాంశం)x / w;
                    దశాంశం floatY = (దశాంశం)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    ఒకవేళ (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        పూర్ణాంకం warpX = rect.ఎడమ + ((rect.కుడి - rect.ఎడమ) / 2) + wobble;
                        పూర్ణాంకం warpY = rect.శిఖరం + ((rect.bottom - rect.శిఖరం) / 2);

                        WIN_సమితి_Cursor_Pos(warpX, warpY);

                        ++wobble;
                        ఒకవేళ (wobble > 1) {
                            wobble = -1;
                        }
                    } లేకపోతే {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        స్థిరరాశి పూర్ణాంకం MAX_RELATIVE_MOTION = (h / 6);
                        ఒకవేళ (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, కిటికీ, mouseID, true, (దశాంశం)relX, (దశాంశం)relY);
                        }
                    }
                }
            } లేకపోతే ఒకవేళ (mouse->pen_mouse_events) {
                స్థిరరాశి పూర్ణాంకం గరిష్ఠ_TABLET_RELATIVE_MOTION = 32;
                ఒకవేళ (SDL_abs(relX) > గరిష్ఠ_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > గరిష్ఠ_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } లేకపోతే {
                    SDL_SendMouseMotion(timestamp, కిటికీ, mouseID, true, (దశాంశం)relX, (దశాంశం)relY);
                }
            } లేకపోతే {
                పూర్ణాంకం screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                పూర్ణాంకం screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                ఒకవేళ (!దత్తాంశం->raw_ఆదానం_fake_pen_id) {
                    దత్తాంశం->raw_ఆదానం_fake_pen_id = SDL_కూడు_Pen_Device(timestamp, "raw mouse input", కిటికీ, ఖాళీ, (శూన్య *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, దత్తాంశం->raw_ఆదానం_fake_pen_id, కిటికీ, (దశాంశం)(x + screen_x - కిటికీ->x), (దశాంశం)(y + screen_y - కిటికీ->y));
            }

            దత్తాంశం->చివరి_raw_mouse_position.x = x;
            దత్తాంశం->చివరి_raw_mouse_position.y = y;
        }
    }

    ఒకవేళ (haveButton) {
        కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            ఒకవేళ (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool కిందికి = raw_buttons[i].కిందికి;

                ఒకవేళ (button == SDL_BUTTON_ఎడమ) {
                    ఒకవేళ (WIN_మార్పిడి_Buttons(hDevice)) {
                        button = SDL_BUTTON_కుడి;
                    }
                } లేకపోతే ఒకవేళ (button == SDL_BUTTON_కుడి) {
                    ఒకవేళ (WIN_మార్పిడి_Buttons(hDevice)) {
                        button = SDL_BUTTON_ఎడమ;
                    }
                }

                ఒకవేళ (windowdata->focus_click_pending & SDL_BUTTON_ముసుగు(button)) {
                    // Ignore the button click for activation
                    ఒకవేళ (!కిందికి) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_ముసుగు(button);
                        WIN_UpdateClipCursor(కిటికీ);
                    }
                    కొనసాగు;
                }

                SDL_SendMouseButton(timestamp, కిటికీ, mouseID, button, కిందికి);
            }
        }

        ఒకవేళ (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_దత్తాంశం;
            దశాంశం fAmount = (దశాంశం)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, కిటికీ, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_సాధారణ);
        } లేకపోతే ఒకవేళ (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->us_Button_దత్తాంశం;
            దశాంశం fAmount = (దశాంశం)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, కిటికీ, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_సాధారణ);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

స్థిర శూన్య WIN_Handle_Raw_Keyboard_ఆదానం(Uint64 timestamp, SDL_Video_దత్తాంశం *దత్తాంశం, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    ఒకవేళ (!దత్తాంశం->raw_keyboard_enabled) {
        తిరిగి;
    }

    ఒకవేళ (rawkeyboard->Flags & RI_కీలకం_E1) {
        // First key in a Ctrl+{key} sequence
        దత్తాంశం->pending_E1_కీలకం_sequence = true;
        తిరిగి;
    }

    ఒకవేళ ((rawkeyboard->Flags & RI_కీలకం_E0) && rawkeyboard->Make_సంకేతం == 0x2A) {
        // 0xE02A make code prefix, ignored
        తిరిగి;
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (!rawkeyboard->Make_సంకేతం) {
        rawkeyboard->Make_సంకేతం = LOWORD(Map_Virtual_కీలకం(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_గమ్యం_VSC : MAPVK_VK_గమ్యం_VSC_EX));
    }
#అయితే_ముగింపు
    ఒకవేళ (!rawkeyboard->Make_సంకేతం) {
        తిరిగి;
    }

    bool కిందికి;
    ఎంపిక (rawkeyboard->సందేశం_4) {
    స్థితి WM_KEYDOWN:
    స్థితి WM_SYSKEYDOWN:
        కిందికి = true;
        ఆపు;
    స్థితి WM_KEYUP:
    స్థితి WM_SYSKEYUP:
        కిందికి = false;
        ఆపు;
    అప్రమేయ:
        కిందికి = !(rawkeyboard->Flags & RI_కీలకం_BREAK);
        ఆపు;
    }

    SDL_Scancode సంకేతం_2;
    USHORT rawcode = rawkeyboard->Make_సంకేతం;
    ఒకవేళ (దత్తాంశం->pending_E1_కీలకం_sequence) {
        rawcode |= 0xE100;
        ఒకవేళ (rawkeyboard->Make_సంకేతం == 0x45) {
            // Ctrl+NumLock == Pause
            సంకేతం_2 = SDL_SCANCODE_PAUSE;
        } లేకపోతే {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            సంకేతం_2 = SDL_SCANCODE_UNKNOWN;
        }
        దత్తాంశం->pending_E1_కీలకం_sequence = false;
    } లేకపోతే {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 సూచీ = (Uint8)rawkeyboard->Make_సంకేతం;
        ఒకవేళ (rawkeyboard->Flags & RI_కీలకం_E0) {
            rawcode |= 0xE000;
            సూచీ |= 0x80;
        }
        సంకేతం_2 = windows_scancode_పట్టిక[సూచీ];
    }

    ఒకవేళ (కిందికి) {
        SDL_కిటికీ *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        ఒకవేళ ((!దత్తాంశం->raw_keyboard_flag_inputsink && !focus) || (focus && focus->పాఠ్యం_ఆదానం_చురుకైన)) {
            తిరిగి;
        }
    }

    SDL_Send_Keyboard_కీలకం(timestamp, keyboardID, rawcode, సంకేతం_2, కిందికి);
}

శూన్య WIN_Poll_Raw_ఆదానం(SDL_VideoDevice *_this, Uint64 poll_ప్రారంభం)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    UINT కొలత, i, లెక్క, మొత్తం = 0;
    RAWINPUT *ఆదానం;
    Uint64 poll_ముగింపు;

    ఒకవేళ (దత్తాంశం->rawinput_స్థానభ్రంశం == 0) {
        BOOL isWow64;

        దత్తాంశం->rawinput_స్థానభ్రంశం = పరిమాణం(RAWINPUTHEADER);
        ఒకవేళ (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            దత్తాంశం->rawinput_స్థానభ్రంశం += 8;
        }
    }

    // Get all available events
    ఆదానం = (RAWINPUT *)దత్తాంశం->rawinput;
    కొరకు (;;) {
        కొలత = దత్తాంశం->rawinput_కొలత - (UINT)((BYTE *)ఆదానం - దత్తాంశం->rawinput);
        లెక్క = Get_Raw_ఆదానం_బఫరు(ఆదానం, &కొలత, పరిమాణం(RAWINPUTHEADER));
        poll_ముగింపు = SDL_GetTicksNS();
        ఒకవేళ (లెక్క == 0 || లెక్క == (UINT)-1) {
            ఒకవేళ (!దత్తాంశం->rawinput || (లెక్క == (UINT)-1 && Get_చివరి_Error() == ERROR_INSUFFICIENT_బఫరు)) {
                స్థిరరాశి UINT RAWINPUT_బఫరు_కొలత_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(దత్తాంశం->rawinput, దత్తాంశం->rawinput_కొలత + RAWINPUT_బఫరు_కొలత_INCREMENT);
                ఒకవేళ (!rawinput) {
                    ఆపు;
                }
                ఆదానం = (RAWINPUT *)(rawinput + ((BYTE *)ఆదానం - దత్తాంశం->rawinput));
                దత్తాంశం->rawinput = rawinput;
                దత్తాంశం->rawinput_కొలత += RAWINPUT_బఫరు_కొలత_INCREMENT;
            } లేకపోతే {
                ఆపు;
            }
        } లేకపోతే {
            మొత్తం += లెక్క;

            // Advance input to the end of the buffer
            అయితే (లెక్క--) {
                ఆదానం = NEXTRAWINPUTBLOCK(ఆదానం);
            }
        }
    }

    ఒకవేళ (మొత్తం > 0) {
        Uint64 delta = poll_ముగింపు - poll_ప్రారంభం;
        UINT mouse_మొత్తం = 0;
        కొరకు (i = 0, ఆదానం = (RAWINPUT *)దత్తాంశం->rawinput; i < మొత్తం; ++i, ఆదానం = NEXTRAWINPUTBLOCK(ఆదానం)) {
            ఒకవేళ (ఆదానం->శీర్షిక.dwType == RIM_TYPEMOUSE) {
                mouse_మొత్తం += 1;
            }
        }
        పూర్ణాంకం mouse_సూచీ = 0;
        కొరకు (i = 0, ఆదానం = (RAWINPUT *)దత్తాంశం->rawinput; i < మొత్తం; ++i, ఆదానం = NEXTRAWINPUTBLOCK(ఆదానం)) {
            ఒకవేళ (ఆదానం->శీర్షిక.dwType == RIM_TYPEMOUSE) {
                mouse_సూచీ += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)ఆదానం + దత్తాంశం->rawinput_స్థానభ్రంశం);
                Uint64 సమయం = poll_ముగింపు - (delta * (mouse_మొత్తం - mouse_సూచీ)) / mouse_మొత్తం;
                WIN_Handle_Raw_Mouse_ఆదానం(సమయం, దత్తాంశం, ఆదానం->శీర్షిక.hDevice, rawmouse);
            } లేకపోతే ఒకవేళ (ఆదానం->శీర్షిక.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)ఆదానం + దత్తాంశం->rawinput_స్థానభ్రంశం);
                WIN_Handle_Raw_Keyboard_ఆదానం(poll_ముగింపు, దత్తాంశం, ఆదానం->శీర్షిక.hDevice, rawkeyboard);
            }
        }
    }
    దత్తాంశం->చివరి_rawinput_poll = poll_ముగింపు;
}

స్థిర శూన్య కూడు_Device_ID(Uint32 deviceID, Uint32 **list, పూర్ణాంకం *లెక్క)
{
    పూర్ణాంకం new_లెక్క = (*లెక్క + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_లెక్క * పరిమాణం(*new_list));
    ఒకవేళ (!new_list) {
        // Oh well, we'll drop this one
        తిరిగి;
    }
    new_list[new_లెక్క - 1] = deviceID;

    *లెక్క = new_లెక్క;
    *list = new_list;
}

స్థిర bool HasDeviceID(Uint32 deviceID, స్థిరరాశి Uint32 *list, పూర్ణాంకం లెక్క)
{
    కొరకు (పూర్ణాంకం i = 0; i < లెక్క; ++i) {
        ఒకవేళ (deviceID == list[i]) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

స్థిర అక్షరం *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, స్థిరరాశి అక్షరం *instance, Uint16 vendor, Uint16 లబ్ధం, స్థిరరాశి అక్షరం *default_name, bool hid_loaded)
{
    అక్షరం *vendor_name = ఖాళీ;
    అక్షరం *లబ్ధం_name = ఖాళీ;
    అక్షరం *name = ఖాళీ;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    ఒకవేళ (hid_loaded) {
        అక్షరం devName[MAX_మార్గం + 1];
        devName[0] = '\0';
        UINT cap = పరిమాణం(devName) - 1;
        UINT len = Get_Raw_ఆదానం_Device_Info_A(hDevice, RIDI_DEVICENAME, devName, &cap);
        ఒకవేళ (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, ఖాళీ, OPEN_EXISTING, 0, ఖాళీ);
            ఒకవేళ (hFile != INVALID_HANDLE_విలువ) {
                SDL_HidD_GetManufacturerString(hFile, vend, పరిమాణం(vend));
                SDL_Hid_D_Get_లబ్ధం_String(hFile, prod, పరిమాణం(prod));
                CloseHandle(hFile);
            }
        }
    }

    ఒకవేళ (vend[0]) {
        vendor_name = WIN_String_గమ్యం_UTF8_W(vend);
    }

    ఒకవేళ (prod[0]) {
        లబ్ధం_name = WIN_String_గమ్యం_UTF8_W(prod);
    } లేకపోతే {
        SP_DEVINFO_దత్తాంశం దత్తాంశం;
        SDL_zero(దత్తాంశం);
        దత్తాంశం.cb_కొలత = పరిమాణం(దత్తాంశం);
        కొరకు (DWORD i = 0;; ++i) {
            ఒకవేళ (!అమరిక_Di_Enum_Device_Info(devinfo, i, &దత్తాంశం)) {
                ఒకవేళ (Get_చివరి_Error() == ERROR_NO_మరిన్ని_వస్తువులు) {
                    ఆపు;
                } లేకపోతే {
                    కొనసాగు;
                }
            }

            అక్షరం DeviceInstanceId[64];
            ఒకవేళ (!అమరిక_Di_Get_Device_Instance_Id_A(devinfo, &దత్తాంశం, DeviceInstanceId, పరిమాణం(DeviceInstanceId), ఖాళీ))
                కొనసాగు;

            ఒకవేళ (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD కొలత = 0;
                ఒకవేళ (అమరిక_Di_Get_Device_Registry_Property_W(devinfo, &దత్తాంశం, SPDRP_DEVICEDESC, ఖాళీ, (PBYTE)prod, పరిమాణం(prod), &కొలత)) {
                    // Make sure the device description is null terminated
                    కొలత /= పరిమాణం(*prod);
                    ఒకవేళ (కొలత >= SDL_arraysize(prod)) {
                        // Truncated description...
                        కొలత = (SDL_arraysize(prod) - 1);
                    }
                    prod[కొలత] = 0;

                    ఒకవేళ (vendor || లబ్ధం) {
                        SDL_asprintf(&లబ్ధం_name, "%S (0x%.4x/0x%.4x)", prod, vendor, లబ్ధం);
                    } లేకపోతే {
                        లబ్ధం_name = WIN_String_గమ్యం_UTF8_W(prod);
                    }
                }
                ఆపు;
            }
        }
    }

    ఒకవేళ (!లబ్ధం_name && (vendor || లబ్ధం)) {
        SDL_asprintf(&లబ్ధం_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, లబ్ధం);
    }
    name = SDL_CreateDeviceName(vendor, లబ్ధం, vendor_name, లబ్ధం_name, default_name);
    SDL_free(vendor_name);
    SDL_free(లబ్ధం_name);

    తిరిగి name;
}

శూన్య WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = ఖాళీ;
    UINT raw_device_లెక్క = 0;
    పూర్ణాంకం old_keyboard_లెక్క = 0;
    SDL_KeyboardID *old_keyboards = ఖాళీ;
    పూర్ణాంకం new_keyboard_లెక్క = 0;
    SDL_KeyboardID *new_keyboards = ఖాళీ;
    పూర్ణాంకం old_mouse_లెక్క = 0;
    SDL_MouseID *old_mice = ఖాళీ;
    పూర్ణాంకం new_mouse_లెక్క = 0;
    SDL_MouseID *new_mice = ఖాళీ;

    ఒకవేళ (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->అంతర్గత->detect_device_hotplug ||
        _this->అంతర్గత->gameinput_context) {
        తిరిగి;
    }

    ఒకవేళ ((Get_Raw_ఆదానం_Device_List(ఖాళీ, &raw_device_లెక్క, పరిమాణం(RAWINPUTDEVICELIST)) == -1) || (!raw_device_లెక్క)) {
        తిరిగి; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(పరిమాణం(RAWINPUTDEVICELIST) * raw_device_లెక్క);
    ఒకవేళ (!raw_devices) {
        తిరిగి; // oh well.
    }

    raw_device_లెక్క = Get_Raw_ఆదానం_Device_List(raw_devices, &raw_device_లెక్క, పరిమాణం(RAWINPUTDEVICELIST));
    ఒకవేళ (raw_device_లెక్క == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = ఖాళీ;
        తిరిగి; // oh well.
    }

    HDEVINFO devinfo = అమరిక_Di_Get_Class_Devs_A(ఖాళీ, ఖాళీ, ఖాళీ, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_లెక్క);
    old_mice = SDL_GetMice(&old_mouse_లెక్క);

    కొరకు (UINT i = 0; i < raw_device_లెక్క; i++) {
        RID_DEVICE_INFO rdi;
        అక్షరం devName[MAX_మార్గం] = { 0 };
        UINT rdi_కొలత = పరిమాణం(rdi);
        UINT name_కొలత = SDL_arraysize(devName);
        పూర్ణాంకం vendor = 0, లబ్ధం = 0;
        DWORD dwType = raw_devices[i].dwType;
        అక్షరం *instance, *ptr, *name;

        ఒకవేళ (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            కొనసాగు;
        }

        rdi.cb_కొలత = పరిమాణం(rdi);
        ఒకవేళ (Get_Raw_ఆదానం_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdi_కొలత) == ((UINT)-1) ||
            Get_Raw_ఆదానం_Device_Info_A(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &name_కొలత) == ((UINT)-1)) {
            కొనసాగు;
        }

        // Extract the device instance
        instance = devName;
        అయితే (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        కొరకు (ptr = instance; *ptr; ++ptr) {
            ఒకవేళ (*ptr == '#') {
                *ptr = '\\';
            }
            ఒకవేళ (*ptr == '{') {
                ఒకవేళ (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                ఆపు;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &లబ్ధం);

        ఎంపిక (dwType) {
        స్థితి RIM_TYPEKEYBOARD:
            ఒకవేళ (SDL_IsKeyboard((Uint16)vendor, (Uint16)లబ్ధం, rdi.keyboard.dw_సంఖ్య_యొక్క_కీలకాలు_మొత్తం)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                కూడు_Device_ID(keyboardID, &new_keyboards, &new_keyboard_లెక్క);
                ఒకవేళ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_లెక్క)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)లబ్ధం, "Keyboard", hid_loaded);
                    SDL_కూడు_Keyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            ఆపు;
        స్థితి RIM_TYPEMOUSE:
            ఒకవేళ (SDL_IsMouse((Uint16)vendor, (Uint16)లబ్ధం)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                కూడు_Device_ID(mouseID, &new_mice, &new_mouse_లెక్క);
                ఒకవేళ (!HasDeviceID(mouseID, old_mice, old_mouse_లెక్క)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)లబ్ధం, "Mouse", hid_loaded);
                    SDL_కూడు_Mouse(mouseID, name);
                    SDL_free(name);
                }
            }
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
    }

    కొరకు (పూర్ణాంకం i = old_keyboard_లెక్క; i--;) {
        ఒకవేళ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_లెక్క)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    కొరకు (పూర్ణాంకం i = old_mouse_లెక్క; i--;) {
        ఒకవేళ (!HasDeviceID(old_mice[i], new_mice, new_mouse_లెక్క)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);

    అమరిక_Di_Destroy_Device_Info_List(devinfo);

    SDL_free(raw_devices);
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Return true if spurious LCtrl is pressed
// LCtrl is sent when RAltGR is pressed
స్థిర bool Skip_Alt_Gr_ఎడమ_Control(WPARAM wParam, LPARAM lParam)
{
    ఒకవేళ (wParam != VK_CONTROL) {
        తిరిగి false;
    }

    // Is this an extended key (i.e. right key)?
    ఒకవేళ (lParam & 0x01000000) {
        తిరిగి false;
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    సందేశం_3 తదుపరి_సందేశం;
    DWORD సందేశం_సమయం = Get_సందేశం_సమయం();
    ఒకవేళ (Peek_సందేశం(&తదుపరి_సందేశం, ఖాళీ, 0, 0, PM_NOREMOVE)) {
        ఒకవేళ (తదుపరి_సందేశం.సందేశం == WM_KEYDOWN ||
            తదుపరి_సందేశం.సందేశం == WM_SYSKEYDOWN) {
            ఒకవేళ (తదుపరి_సందేశం.wParam == VK_MENU && (తదుపరి_సందేశం.lParam & 0x01000000) && తదుపరి_సందేశం.సమయం == సందేశం_సమయం) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                తిరిగి true;
            }
        }
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    తిరిగి false;
}

స్థిర bool Dispatch_Modal_Loop_సందేశం_Hook(HWND *hwnd, UINT *సందేశం_2, WPARAM *wParam, LPARAM *lParam)
{
    సందేశం_3 dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.సందేశం = *సందేశం_2;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    ఒకవేళ (g_Windows_సందేశం_Hook(g_Windows_సందేశం_Hook_దత్తాంశం, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *సందేశం_2 = dummy.సందేశం;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        తిరిగి true;
    }
    తిరిగి false;
}

LRESULT CALLBACK WIN_కిటికీ_Proc(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM lParam)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    LRESULT return_సంకేతం = -1;

    // Get the window data for the window
    దత్తాంశం = WIN_Get_కిటికీ_దత్తాంశం_From_HWND(hwnd);
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (!దత్తాంశం) {
        // Fallback
        దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)GetProp(hwnd, పాఠ్యం_2("SDL_WindowData"));
    }
#అయితే_ముగింపు
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి Call_కిటికీ_Proc(Def_కిటికీ_Proc, hwnd, సందేశం_2, wParam, lParam);
    }

#నిర్వచితమైతే WMMSG_DEBUG
    {
        అక్షరం సందేశం[1024];
        ఒకవేళ (సందేశం_2 > MAX_WMMSG) {
            SDL_snprintf(సందేశం, పరిమాణం(సందేశం), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, సందేశం_2, wParam, lParam);
        } లేకపోతే {
            SDL_snprintf(సందేశం, పరిమాణం(సందేశం), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[సందేశం_2], wParam, lParam);
        }
        OutputDebugStringA(సందేశం);
    }
#అయితే_ముగింపు // WMMSG_DEBUG


    ఒకవేళ (g_Windows_సందేశం_Hook && దత్తాంశం->లోపల_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        ఒకవేళ (!Dispatch_Modal_Loop_సందేశం_Hook(&hwnd, &సందేశం_2, &wParam, &lParam)) {
            తిరిగి 0;
        }
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (WIN_HandleIMEMessage(hwnd, సందేశం_2, wParam, &lParam, దత్తాంశం->videodata)) {
        తిరిగి 0;
    }
#అయితే_ముగింపు

    ఎంపిక (సందేశం_2) {

    స్థితి WM_SHOWWINDOW:
    {
        ఒకవేళ (wParam) {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
        } లేకపోతే {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_HIDDEN, 0, 0);
        }
    } ఆపు;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    స్థితి WM_NCACTIVATE:
    {
        // Don't immediately clip the cursor in case we're clicking minimize/maximize buttons
        దత్తాంశం->postpone_clipcursor = true;
        దత్తాంశం->clipcursor_queued = true;

        /* Update the focus here, since it's possible to get WM_ACTIVATE and WM_SETFOCUS without
           actually being the foreground window, but this appears to get called in all cases where
           the global foreground window changes to and from this window.

           The current cursor position is needed here, as the message position contains old
           coordinates if the pointer moved while an overlay was active. */
        బిందువు_2 pos = { 0, 0 };
        GetCursorPos(&pos);
        WIN_UpdateFocus(దత్తాంశం->కిటికీ, !!wParam, &pos);

        /* Handle borderless windows; this event is intended for drawing the titlebar, so we need
           to stop that from happening. */
        ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } ఆపు;

    స్థితి WM_NCUAHDRAWCAPTION:
    స్థితి WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
            return_సంకేతం = 0;
        }
    } ఆపు;

    స్థితి WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        స్థిరరాశి DWORD సందేశం_Pos = Get_సందేశం_Pos();
        బిందువు_2 pos = { GET_X_LPARAM(సందేశం_Pos), GET_Y_LPARAM(సందేశం_Pos) };
        WIN_UpdateFocus(దత్తాంశం->కిటికీ, !!LOWORD(wParam), &pos);
    } ఆపు;

    స్థితి WM_MOUSEACTIVATE:
    {
        ఒకవేళ (SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ)) {
            తిరిగి MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_కిటికీ *మాతృ = దత్తాంశం->కిటికీ->మాతృ;
        అయితే (మాతృ) {
            ఒకవేళ ((మాతృ->flags & SDL_కిటికీ_ఆదానం_FOCUS) &&
                (మాతృ->flags & SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం)) {
                తిరిగి MA_NOACTIVATE;
            }
            మాతృ = మాతృ->మాతృ;
        }
    } ఆపు;

    స్థితి WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        స్థిరరాశి DWORD సందేశం_Pos = Get_సందేశం_Pos();
        బిందువు_2 pos = { GET_X_LPARAM(సందేశం_Pos), GET_Y_LPARAM(సందేశం_Pos) };
        WIN_UpdateFocus(దత్తాంశం->కిటికీ, true, &pos);
    } ఆపు;

    స్థితి WM_KILLFOCUS:
    స్థితి WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        స్థిరరాశి DWORD సందేశం_Pos = Get_సందేశం_Pos();
        బిందువు_2 pos = { GET_X_LPARAM(సందేశం_Pos), GET_Y_LPARAM(సందేశం_Pos) };
        WIN_UpdateFocus(దత్తాంశం->కిటికీ, false, &pos);
    } ఆపు;

    స్థితి WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        స్థిరరాశి UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        సూచిక_ఆదానం_TYPE సూచిక_type = PT_సూచిక;
        ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Type) {
            ఆపు;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } లేకపోతే ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Type(pointerid, &సూచిక_type)) {
            ఆపు;  // oh well.
        } లేకపోతే ఒకవేళ (సూచిక_type != PT_PEN) {
            ఆపు;  // we only care about pens here.
        }

        శూన్య *hpointer = (శూన్య *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        స్థిరరాశి SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle(hpointer);
        ఒకవేళ (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, దత్తాంశం->కిటికీ, true, true);
        } లేకపోతే {
            // one can use GetPointerPenInfo() to get the current state of the pen, and check POINTER_PEN_INFO::penMask,
            //  but the docs aren't clear if these masks are _always_ set for pens with specific features, or if they
            //  could be unset at this moment because Windows is still deciding what capabilities the pen has, and/or
            //  doesn't yet have valid data for them. As such, just say everything that the interface supports is
            //  available...we don't expose this information through the public API at the moment anyhow.
            SDL_PenInfo info;
            SDL_zero(info);
            info.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_దూరం | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_ERASER;
            info.max_tilt = 90.0f;
            info.అంకె_buttons = 1;
            info.subtype = SDL_PEN_TYPE_PENCIL;
            SDL_కూడు_Pen_Device(WIN_GetEventTimestamp(), ఖాళీ, దత్తాంశం->కిటికీ, &info, hpointer, true);
        }
        return_సంకేతం = 0;
    } ఆపు;

    స్థితి WM_POINTERCAPTURECHANGED:
    స్థితి WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        స్థిరరాశి UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        సూచిక_ఆదానం_TYPE సూచిక_type = PT_సూచిక;
        ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Type) {
            ఆపు;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } లేకపోతే ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Type(pointerid, &సూచిక_type)) {
            ఆపు;  // oh well.
        } లేకపోతే ఒకవేళ (సూచిక_type != PT_PEN) {
            ఆపు;  // we only care about pens here.
        }

        శూన్య *hpointer = (శూన్య *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        స్థిరరాశి SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle(hpointer);
        ఒకవేళ (pen == 0) {
            ఆపు;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        ఒకవేళ ((సందేశం_2 == WM_POINTERCAPTURECHANGED) || !IS_సూచిక_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, దత్తాంశం->కిటికీ, false, false);
        }
        return_సంకేతం = 0;
    } ఆపు;

    స్థితి WM_POINTERDOWN:
    స్థితి WM_POINTERUP:
    స్థితి WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        స్థిరరాశి UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        సూచిక_ఆదానం_TYPE సూచిక_type = PT_సూచిక;
        ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Type || !దత్తాంశం->videodata->Get_సూచిక_Type(pointerid, &సూచిక_type)) {
            ఆపు;  // oh well.
        } లేకపోతే ఒకవేళ ((సందేశం_2 == WM_POINTERUPDATE) && (సూచిక_type == PT_MOUSE)) {
            దత్తాంశం->చివరి_సూచిక_update = lParam;
            return_సంకేతం = 0;
            ఆపు;
        } లేకపోతే ఒకవేళ (సూచిక_type != PT_PEN) {
            ఆపు; // we only care about pens here.
        }

        శూన్య *hpointer = (శూన్య *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        స్థిరరాశి SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle(hpointer);
        సూచిక_PEN_INFO pen_info;
        ఒకవేళ (pen == 0) {
            ఆపు;  // not a pen, or not a pen we already knew about.
        } లేకపోతే ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Pen_Info || !దత్తాంశం->videodata->Get_సూచిక_Pen_Info(pointerid, &pen_info)) {
            ఆపు;  // oh well.
        }

        స్థిరరాశి Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

        స్థిరరాశి bool istouching = IS_సూచిక_INCONTACT_WPARAM(wParam) && IS_సూచిక_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        ఒకవేళ (!istouching) {
            SDL_SendPenTouch(timestamp, pen, కిటికీ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        స్థిరరాశి సూచిక_INFO *సూచిక_info = &pen_info.సూచిక_Info;
        RECT tablet_bounds, tablet_mapping;
        దశాంశం fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        ఒకవేళ (!దత్తాంశం->videodata->Get_సూచిక_Device_Rects || !దత్తాంశం->videodata->Get_సూచిక_Device_Rects(సూచిక_info->ఆధారం_Device, &tablet_bounds, &tablet_mapping)) {
            బిందువు_2 position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            Screen_గమ్యం_Client(దత్తాంశం->hwnd, &position);
            fx = (దశాంశం) position.x;
            fy = (దశాంశం) position.y;
        } లేకపోతే {
            పూర్ణాంకం ix, iy;
            SDL_Get_కిటికీ_Position(కిటికీ, &ix, &iy);
            స్థిరరాశి SDL_FPoint కిటికీ_pos = { (దశాంశం) ix, (దశాంశం) iy };

            స్థిరరాశి దశాంశం facX = సూచిక_info->ptHimetricLocationRaw.x / (దశాంశం) (tablet_bounds.కుడి );
            స్థిరరాశి దశాంశం facY = సూచిక_info->ptHimetricLocationRaw.y / (దశాంశం) (tablet_bounds.bottom);

            స్థిరరాశి దశాంశం w = tablet_mapping.కుడి  - tablet_mapping.ఎడమ;
            స్థిరరాశి దశాంశం h = tablet_mapping.bottom - tablet_mapping.శిఖరం;

            fx = (tablet_mapping.ఎడమ + (facX * w)) - కిటికీ_pos.x;
            fy = (tablet_mapping.శిఖరం  + (facY * h)) - కిటికీ_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, కిటికీ, fx, fy);
        SDL_SendPenButton(timestamp, pen, కిటికీ, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, కిటికీ, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        ఒకవేళ (pen_info.pen_ముసుగు & PEN_ముసుగు_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, కిటికీ, SDL_PEN_AXIS_PRESSURE, ((దశాంశం) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        ఒకవేళ (pen_info.pen_ముసుగు & PEN_ముసుగు_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, కిటికీ, SDL_PEN_AXIS_ROTATION, ((దశాంశం) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        ఒకవేళ (pen_info.pen_ముసుగు & PEN_ముసుగు_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, కిటికీ, SDL_PEN_AXIS_XTILT, ((దశాంశం) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        ఒకవేళ (pen_info.pen_ముసుగు & PEN_ముసుగు_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, కిటికీ, SDL_PEN_AXIS_YTILT, ((దశాంశం) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        ఒకవేళ (istouching) {
            SDL_SendPenTouch(timestamp, pen, కిటికీ, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        return_సంకేతం = 0;
    } ఆపు;

    స్థితి WM_MOUSEMOVE:
    {
        SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
            bool wish_clip_cursor = (
                కిటికీ->flags & (SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం | SDL_కిటికీ_MOUSE_GRABBED) ||
                (కిటికీ->mouse_rect.w > 0 && కిటికీ->mouse_rect.h > 0)
            );
            ఒకవేళ (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                దత్తాంశం->clipcursor_queued = true;
            }
        }

        ఒకవేళ (!దత్తాంశం->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cb_కొలత = పరిమాణం(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = దత్తాంశం->hwnd;

            ఒకవేళ (TrackMouseEvent(&trackMouseEvent)) {
                దత్తాంశం->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), దత్తాంశం);
        }

        ఒకవేళ (!దత్తాంశం->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            ఒకవేళ (Get_Mouse_సందేశం_ఆధారం((ULONG)Get_సందేశం_Extra_Info()) == SDL_MOUSE_EVENT_ఆధారం_MOUSE &&
                lParam != దత్తాంశం->చివరి_సూచిక_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)GET_X_LPARAM(lParam), (దశాంశం)GET_Y_LPARAM(lParam));
            }
        }

    } ఆపు;

    స్థితి WM_LBUTTONUP:
    స్థితి WM_RBUTTONUP:
    స్థితి WM_MBUTTONUP:
    స్థితి WM_XBUTTONUP:
    స్థితి WM_LBUTTONDOWN:
    స్థితి WM_LBUTTONDBLCLK:
    స్థితి WM_RBUTTONDOWN:
    స్థితి WM_RBUTTONDBLCLK:
    స్థితి WM_MBUTTONDOWN:
    స్థితి WM_MBUTTONDBLCLK:
    స్థితి WM_XBUTTONDOWN:
    స్థితి WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        ఒకవేళ (!దత్తాంశం->videodata->raw_mouse_enabled) {
            ఒకవేళ (Get_Mouse_సందేశం_ఆధారం((ULONG)Get_సందేశం_Extra_Info()) == SDL_MOUSE_EVENT_ఆధారం_MOUSE &&
                lParam != దత్తాంశం->చివరి_సూచిక_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, దత్తాంశం, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } ఆపు;

#ఒకవేళ 0   // We handle raw input all at once instead of using a syscall for each mouse event
    స్థితి WM_ఆదానం:
    {
        HRAWINPUT h_Raw_ఆదానం = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT కొలత = పరిమాణం(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        ఒకవేళ (దత్తాంశం->కిటికీ != SDL_GetKeyboardFocus()) {
            ఆపు;
        }

        Get_Raw_ఆదానం_దత్తాంశం(h_Raw_ఆదానం, RID_ఆదానం, &inp, &కొలత, పరిమాణం(RAWINPUTHEADER));
        ఒకవేళ (inp.శీర్షిక.dwType == RIM_TYPEMOUSE) {
            WIN_Handle_Raw_Mouse_ఆదానం(WIN_GetEventTimestamp(), దత్తాంశం, inp.శీర్షిక.hDevice, &inp.దత్తాంశం.mouse);
        } లేకపోతే ఒకవేళ (inp.శీర్షిక.dwType == RIM_TYPEKEYBOARD) {
            WIN_Handle_Raw_Keyboard_ఆదానం(WIN_GetEventTimestamp(), దత్తాంశం, inp.శీర్షిక.hDevice, &inp.దత్తాంశం.keyboard);
        }
    } ఆపు;
#అయితే_ముగింపు

    స్థితి WM_MOUSEWHEEL:
    స్థితి WM_MOUSEHWHEEL:
    {
        ఒకవేళ (!దత్తాంశం->videodata->raw_mouse_enabled) {
            పొట్టి amount = GET_WHEEL_DELTA_WPARAM(wParam);
            దశాంశం fAmount = (దశాంశం)amount / WHEEL_DELTA;
            ఒకవేళ (సందేశం_2 == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_సాధారణ);
            } లేకపోతే {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_సాధారణ);
            }
        }
    } ఆపు;

    స్థితి WM_MOUSELEAVE:
        ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
            ఒకవేళ (SDL_GetMouseFocus() == దత్తాంశం->కిటికీ && !SDL_GetMouse()->relative_బహుళకం && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = Get_సందేశం_Pos();
                బిందువు_2 cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                Screen_గమ్యం_Client(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                ఒకవేళ (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)cursorPos.x, (దశాంశం)cursorPos.y);
                } లేకపోతే {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    ఒకవేళ (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, SDL_TOUCH_MOUSEID, false, (దశాంశం)cursorPos.x, (దశాంశం)cursorPos.y);
                    } లేకపోతే { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)cursorPos.x, (దశాంశం)cursorPos.y);
                    }
                }
            }

            ఒకవేళ (!SDL_GetMouse()->relative_బహుళకం) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_సమితి_Mouse_Focus(ఖాళీ);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        దత్తాంశం->mouse_tracked = false;

        return_సంకేతం = 0;
        ఆపు;
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    స్థితి WM_KEYDOWN:
    స్థితి WM_SYSKEYDOWN:
    {
        ఒకవేళ (Skip_Alt_Gr_ఎడమ_Control(wParam, lParam)) {
            return_సంకేతం = 0;
            ఆపు;
        }

        bool virtual_కీలకం = false;
        Uint16 rawcode = 0;
        SDL_Scancode సంకేతం_2 = Windows_పరిశీలన_సంకేతం_గమ్యం_SDLScan_సంకేతం(lParam, wParam, &rawcode, &virtual_కీలకం);

        // Detect relevant keyboard shortcuts
        ఒకవేళ (సంకేతం_2 == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            ఒకవేళ (Should_Generate_కిటికీ_Close_On_Alt_F4()) {
                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
            }
        }

        ఒకవేళ (virtual_కీలకం || !దత్తాంశం->videodata->raw_keyboard_enabled || దత్తాంశం->కిటికీ->పాఠ్యం_ఆదానం_చురుకైన) {
            SDL_Send_Keyboard_కీలకం(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, సంకేతం_2, true);
        }
    }

        return_సంకేతం = 0;
        ఆపు;

    స్థితి WM_SYSKEYUP:
    స్థితి WM_KEYUP:
    {
        ఒకవేళ (Skip_Alt_Gr_ఎడమ_Control(wParam, lParam)) {
            return_సంకేతం = 0;
            ఆపు;
        }

        bool virtual_కీలకం = false;
        Uint16 rawcode = 0;
        SDL_Scancode సంకేతం_2 = Windows_పరిశీలన_సంకేతం_గమ్యం_SDLScan_సంకేతం(lParam, wParam, &rawcode, &virtual_కీలకం);
        స్థిరరాశి bool *keyboardState = SDL_GetKeyboardState(ఖాళీ);

        ఒకవేళ (virtual_కీలకం || !దత్తాంశం->videodata->raw_keyboard_enabled || దత్తాంశం->కిటికీ->పాఠ్యం_ఆదానం_చురుకైన) {
            ఒకవేళ (సంకేతం_2 == SDL_SCANCODE_PRINTSCREEN && !keyboardState[సంకేతం_2]) {
                SDL_Send_Keyboard_కీలకం(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, సంకేతం_2, true);
            }
            SDL_Send_Keyboard_కీలకం(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, సంకేతం_2, false);
        }
    }
        return_సంకేతం = 0;
        ఆపు;

    స్థితి WM_UNICHAR:
        ఒకవేళ (wParam == UNICODE_NOCHAR) {
            return_సంకేతం = 1;
        } లేకపోతే {
            ఒకవేళ (SDL_పాఠ్యం_ఆదానం_చురుకైన(దత్తాంశం->కిటికీ)) {
                అక్షరం పాఠ్యం[5];
                అక్షరం *చివర = SDL_UCS4_గమ్యం_UTF8((Uint32)wParam, పాఠ్యం);
                *చివర = '\0';
                SDL_Send_Keyboard_పాఠ్యం(పాఠ్యం);
            }
            return_సంకేతం = 0;
        }
        ఆపు;

    స్థితి WM_CHAR:
        ఒకవేళ (SDL_పాఠ్యం_ఆదానం_చురుకైన(దత్తాంశం->కిటికీ)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            ఒకవేళ (IS_ఎగువ_SURROGATE(wParam)) {
                దత్తాంశం->ఎగువ_surrogate = (WCHAR)wParam;
            } లేకపోతే {
                WCHAR utf16[3];

                utf16[0] = దత్తాంశం->ఎగువ_surrogate ? దత్తాంశం->ఎగువ_surrogate : (WCHAR)wParam;
                utf16[1] = దత్తాంశం->ఎగువ_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                అక్షరం utf8[5];
                పూర్ణాంకం ఫలితం = WIN_Wide_Char_గమ్యం_Multi_Byte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, పరిమాణం(utf8), ఖాళీ, ఖాళీ);
                ఒకవేళ (ఫలితం > 0) {
                    SDL_Send_Keyboard_పాఠ్యం(utf8);
                }
                దత్తాంశం->ఎగువ_surrogate = L'\0';
            }
        } లేకపోతే {
            దత్తాంశం->ఎగువ_surrogate = L'\0';
        }

        return_సంకేతం = 0;
        ఆపు;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#నిర్వచితమైతే WM_INPUTLANGCHANGE
    స్థితి WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        return_సంకేతం = 1;
        ఆపు;
#అయితే_ముగింపు // WM_INPUTLANGCHANGE

    స్థితి WM_NCLBUTTONDOWN:
    {
        దత్తాంశం->లోపల_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        ఒకవేళ (Send_సందేశం(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            బిందువు_2 cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            Screen_గమ్యం_Client(hwnd, &cursorPos);
            Post_సందేశం(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } ఆపు;

    స్థితి WM_CAPTURECHANGED:
    {
        దత్తాంశం->లోపల_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), దత్తాంశం);
    } ఆపు;

#నిర్వచితమైతే WM_GETMINMAXINFO
    స్థితి WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT కొలత;
        పూర్ణాంకం x, y;
        పూర్ణాంకం w, h;
        పూర్ణాంకం min_w, min_h;
        పూర్ణాంకం max_w, max_h;
        BOOL constrain_max_కొలత;

        // If this is an expected size change, allow it
        ఒకవేళ (దత్తాంశం->expected_resize) {
            ఆపు;
        }

        // Get the current position of our window
        Get_కిటికీ_Rect(hwnd, &కొలత);
        x = కొలత.ఎడమ;
        y = కొలత.శిఖరం;

        // Calculate current size of our window
        SDL_Get_కిటికీ_కొలత(దత్తాంశం->కిటికీ, &w, &h);
        SDL_Get_కిటికీ_Minimum_కొలత(దత్తాంశం->కిటికీ, &min_w, &min_h);
        SDL_Get_కిటికీ_గరిష్ఠ_కొలత(దత్తాంశం->కిటికీ, &max_w, &max_h);

        /* Store in min_w and min_h difference between current size and minimal
           size so we don't need to call AdjustWindowRectEx twice */
        min_w -= w;
        min_h -= h;
        ఒకవేళ (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_కొలత = TRUE;
        } లేకపోతే {
            constrain_max_కొలత = FALSE;
        }

        ఒకవేళ (!(SDL_Get_కిటికీ_Flags(దత్తాంశం->కిటికీ) & SDL_కిటికీ_BORDERLESS) && !SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ)) {
            కొలత.శిఖరం = 0;
            కొలత.ఎడమ = 0;
            కొలత.bottom = h;
            కొలత.కుడి = w;
            WIN_Adjust_కిటికీ_Rect_For_HWND(hwnd, &కొలత, 0);
            w = కొలత.కుడి - కొలత.ఎడమ;
            h = కొలత.bottom - కొలత.శిఖరం;
#నిర్వచితమైతే HIGHDPI_DEBUG
            SDL_Log("WM_GETMINMAXINFO: max window size: %dx%d using dpi: %u", w, h, dpi);
#అయితే_ముగింపు
        }

        // Fix our size to the current size
        info = (MINMAXINFO *)lParam;
        ఒకవేళ (SDL_Get_కిటికీ_Flags(దత్తాంశం->కిటికీ) & SDL_కిటికీ_RESIZABLE) {
            ఒకవేళ (SDL_Get_కిటికీ_Flags(దత్తాంశం->కిటికీ) & SDL_కిటికీ_BORDERLESS) {
                పూర్ణాంకం screenW = GetSystemMetrics(SM_CXSCREEN);
                పూర్ణాంకం screenH = GetSystemMetrics(SM_CYSCREEN);
                info->pt_Max_కొలత.x = SDL_max(w, screenW);
                info->pt_Max_కొలత.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->pt_Min_Track_కొలత.x = (LONG)w + min_w;
            info->pt_Min_Track_కొలత.y = (LONG)h + min_h;
            ఒకవేళ (constrain_max_కొలత) {
                info->pt_Max_Track_కొలత.x = (LONG)w + max_w;
                info->pt_Max_Track_కొలత.y = (LONG)h + max_h;
            }
        } లేకపోతే {
            info->pt_Max_కొలత.x = w;
            info->pt_Max_కొలత.y = h;
            info->ptMaxPosition.x = x;
            info->ptMaxPosition.y = y;
            info->pt_Min_Track_కొలత.x = w;
            info->pt_Min_Track_కొలత.y = h;
            info->pt_Max_Track_కొలత.x = w;
            info->pt_Max_Track_కొలత.y = h;
        }
    }
        return_సంకేతం = 0;
        ఆపు;
#అయితే_ముగింపు // WM_GETMINMAXINFO

    స్థితి WM_WINDOWPOSCHANGING:

        ఒకవేళ (దత్తాంశం->expected_resize) {
            return_సంకేతం = 0;
        } లేకపోతే ఒకవేళ (దత్తాంశం->లోపల_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            ఒకవేళ (దత్తాంశం->చివరి_modal_వెడల్పు == windowpos->cx && దత్తాంశం->చివరి_modal_ఎత్తు == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            దత్తాంశం->చివరి_modal_వెడల్పు = windowpos->cx;
            దత్తాంశం->చివరి_modal_ఎత్తు = windowpos->cy;

            return_సంకేతం = 0;
        }
        ఆపు;

    స్థితి WM_WINDOWPOSCHANGED:
    {
        SDL_కిటికీ *win;
        స్థిరరాశి SDL_DisplayID original_displayID = దత్తాంశం->కిటికీ->displayID;
        స్థిరరాశి WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        పూర్ణాంకం x, y;
        పూర్ణాంకం w, h;

        ఒకవేళ (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        ఒకవేళ (iconic) {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
        } లేకపోతే ఒకవేళ (zoomed) {
            ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
            }
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MAXIMIZED, 0, 0);
            దత్తాంశం->force_ws_maximizebox = true;
        } లేకపోతే ఒకవేళ (దత్తాంశం->కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED)) {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
                దత్తాంశం->force_ws_maximizebox = false;
                WIN_సమితి_కిటికీ_Resizable(SDL_GetVideoDevice(), దత్తాంశం->కిటికీ, !!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_RESIZABLE));
            }
        }

        ఒకవేళ (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        ఒకవేళ (iconic) {
            ఆపు;
        }

        ఒకవేళ (దత్తాంశం->initializing) {
            ఆపు;
        }

        ఒకవేళ (!దత్తాంశం->disable_move_కొలత_events) {
            ఒకవేళ (GetClientRect(hwnd, &rect) && WIN_కిటికీ_Rect_Valid(&rect)) {
                Client_గమ్యం_Screen(hwnd, (LPPOINT) &rect);
                Client_గమ్యం_Screen(hwnd, (LPPOINT) &rect + 1);

                x = rect.ఎడమ;
                y = rect.శిఖరం;

                SDL_Global_గమ్యం_Relative_For_కిటికీ(దత్తాంశం->కిటికీ, x, y, &x, &y);
                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            ఒకవేళ (GetClientRect(hwnd, &rect) && WIN_కిటికీ_Rect_Valid(&rect)) {
                w = rect.కుడి;
                h = rect.bottom;

                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(దత్తాంశం->కిటికీ);

        // Update the window display position
        ఒకవేళ (దత్తాంశం->కిటికీ->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_Update_కిటికీ_ICCProfile(దత్తాంశం->కిటికీ, true);
        }

        // Update the position of any child windows
        కొరకు (win = దత్తాంశం->కిటికీ->మొదటి_బిడ్డ; win; win = win->తదుపరి_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ఒకవేళ (SDL_కిటికీ_IS_POPUP(win) && !(win->flags & SDL_కిటికీ_HIDDEN)) {
                WIN_సమితి_కిటికీ_Position_అంతర్గత(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } ఆపు;

    స్థితి WM_ENTERSIZEMOVE:
    స్థితి WM_ENTERMENULOOP:
    {
        ఒకవేళ (g_Windows_సందేశం_Hook) {
            ఒకవేళ (!Dispatch_Modal_Loop_సందేశం_Hook(&hwnd, &సందేశం_2, &wParam, &lParam)) {
                తిరిగి 0;
            }
        }

        ++దత్తాంశం->లోపల_modal_loop;
        ఒకవేళ (దత్తాంశం->లోపల_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            Get_కిటికీ_Rect(దత్తాంశం->hwnd, &rect);
            దత్తాంశం->చివరి_modal_వెడల్పు = rect.కుడి - rect.ఎడమ;
            దత్తాంశం->చివరి_modal_ఎత్తు = rect.bottom - rect.శిఖరం;

            దత్తాంశం->initial_కొలత_rect.ఎడమ = దత్తాంశం->కిటికీ->x;
            దత్తాంశం->initial_కొలత_rect.కుడి = దత్తాంశం->కిటికీ->x + దత్తాంశం->కిటికీ->w;
            దత్తాంశం->initial_కొలత_rect.శిఖరం = దత్తాంశం->కిటికీ->y;
            దత్తాంశం->initial_కొలత_rect.bottom = దత్తాంశం->కిటికీ->y + దత్తాంశం->కిటికీ->h;

            సమితి_Timer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, ఖాళీ);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } ఆపు;

    స్థితి WM_TIMER:
    {
        ఒకవేళ (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_On_కిటికీ_సజీవ_Resize_Update(దత్తాంశం->కిటికీ);

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ఒకవేళ 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            ఒకవేళ (దత్తాంశం->videodata->DwmFlush) {
                దత్తాంశం->videodata->DwmFlush();
            }
#అయితే_ముగింపు
#అయితే_ముగింపు
            తిరిగి 0;
        }
    } ఆపు;

    స్థితి WM_EXITSIZEMOVE:
    స్థితి WM_EXITMENULOOP:
    {
        --దత్తాంశం->లోపల_modal_loop;
        ఒకవేళ (దత్తాంశం->లోపల_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } ఆపు;

    స్థితి WM_SIZING:
        {
            WPARAM అంచు = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool తాళం_aspect_నిష్పత్తి = (దత్తాంశం->కిటికీ->max_aspect == దత్తాంశం->కిటికీ->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            దశాంశం new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            ఒకవేళ (దత్తాంశం->కిటికీ->min_aspect <= 0 && దత్తాంశం->కిటికీ->max_aspect <= 0) {
                ఆపు;
            }

            // unadjust the dragRect from the window rect to the client rect
            సమితి_Rect_ఖాళీలు(&rc);
            ఒకవేళ (!Adjust_కిటికీ_Rect_Ex(&rc, Get_కిటికీ_Style(hwnd), GetMenu(hwnd) != ఖాళీ, Get_కిటికీ_Ex_Style(hwnd))) {
                ఆపు;
            }

            clientDragRect.ఎడమ -= rc.ఎడమ;
            clientDragRect.శిఖరం -= rc.శిఖరం;
            clientDragRect.కుడి -= rc.కుడి;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.కుడి - clientDragRect.ఎడమ;
            h = clientDragRect.bottom - clientDragRect.శిఖరం;
            new_aspect = w / (దశాంశం)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            ఒకవేళ (తాళం_aspect_నిష్పత్తి) {
                ఎంపిక (అంచు) {
                స్థితి WMSZ_ఎడమ:
                స్థితి WMSZ_కుడి:
                    h = (పూర్ణాంకం)SDL_roundf(w / దత్తాంశం->కిటికీ->max_aspect);
                    ఆపు;
                అప్రమేయ:
                    // resizing via corners or top or bottom
                    w = (పూర్ణాంకం)SDL_roundf(h * దత్తాంశం->కిటికీ->max_aspect);
                    ఆపు;
                }
            } లేకపోతే {
                ఎంపిక (అంచు) {
                స్థితి WMSZ_ఎడమ:
                స్థితి WMSZ_కుడి:
                    ఒకవేళ (దత్తాంశం->కిటికీ->max_aspect > 0.0f && new_aspect > దత్తాంశం->కిటికీ->max_aspect) {
                        w = (పూర్ణాంకం)SDL_roundf(h * దత్తాంశం->కిటికీ->max_aspect);
                    } లేకపోతే ఒకవేళ (దత్తాంశం->కిటికీ->min_aspect > 0.0f && new_aspect < దత్తాంశం->కిటికీ->min_aspect) {
                        w = (పూర్ణాంకం)SDL_roundf(h * దత్తాంశం->కిటికీ->min_aspect);
                    }
                    ఆపు;
                స్థితి WMSZ_శిఖరం:
                స్థితి WMSZ_BOTTOM:
                    ఒకవేళ (దత్తాంశం->కిటికీ->min_aspect > 0.0f && new_aspect < దత్తాంశం->కిటికీ->min_aspect) {
                        h = (పూర్ణాంకం)SDL_roundf(w / దత్తాంశం->కిటికీ->min_aspect);
                    } లేకపోతే ఒకవేళ (దత్తాంశం->కిటికీ->max_aspect > 0.0f && new_aspect > దత్తాంశం->కిటికీ->max_aspect) {
                        h = (పూర్ణాంకం)SDL_roundf(w / దత్తాంశం->కిటికీ->max_aspect);
                    }
                    ఆపు;

                అప్రమేయ:
                    // resizing via corners
                    ఒకవేళ (దత్తాంశం->కిటికీ->max_aspect > 0.0f && new_aspect > దత్తాంశం->కిటికీ->max_aspect) {
                        w = (పూర్ణాంకం)SDL_roundf(h * దత్తాంశం->కిటికీ->max_aspect);
                    } లేకపోతే ఒకవేళ (దత్తాంశం->కిటికీ->min_aspect > 0.0f && new_aspect < దత్తాంశం->కిటికీ->min_aspect) {
                        h = (పూర్ణాంకం)SDL_roundf(w / దత్తాంశం->కిటికీ->min_aspect);
                    }
                    ఆపు;
                }
            }

            ఎంపిక (అంచు) {
            స్థితి WMSZ_ఎడమ:
                clientDragRect.ఎడమ = clientDragRect.కుడి - w;
                ఒకవేళ (తాళం_aspect_నిష్పత్తి) {
                    clientDragRect.శిఖరం = (దత్తాంశం->initial_కొలత_rect.bottom + దత్తాంశం->initial_కొలత_rect.శిఖరం - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.శిఖరం;
                ఆపు;
            స్థితి WMSZ_BOTTOMLEFT:
                clientDragRect.ఎడమ = clientDragRect.కుడి - w;
                clientDragRect.bottom = h + clientDragRect.శిఖరం;
                ఆపు;
            స్థితి WMSZ_కుడి:
                clientDragRect.కుడి = w + clientDragRect.ఎడమ;
                ఒకవేళ (తాళం_aspect_నిష్పత్తి) {
                    clientDragRect.శిఖరం = (దత్తాంశం->initial_కొలత_rect.bottom + దత్తాంశం->initial_కొలత_rect.శిఖరం - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.శిఖరం;
                ఆపు;
            స్థితి WMSZ_TOPRIGHT:
                clientDragRect.కుడి = w + clientDragRect.ఎడమ;
                clientDragRect.శిఖరం = clientDragRect.bottom - h;
                ఆపు;
            స్థితి WMSZ_శిఖరం:
                ఒకవేళ (తాళం_aspect_నిష్పత్తి) {
                    clientDragRect.ఎడమ = (దత్తాంశం->initial_కొలత_rect.కుడి + దత్తాంశం->initial_కొలత_rect.ఎడమ - w) / 2;
                }
                clientDragRect.కుడి = w + clientDragRect.ఎడమ;
                clientDragRect.శిఖరం = clientDragRect.bottom - h;
                ఆపు;
            స్థితి WMSZ_TOPLEFT:
                clientDragRect.ఎడమ = clientDragRect.కుడి - w;
                clientDragRect.శిఖరం = clientDragRect.bottom - h;
                ఆపు;
            స్థితి WMSZ_BOTTOM:
                ఒకవేళ (తాళం_aspect_నిష్పత్తి) {
                    clientDragRect.ఎడమ = (దత్తాంశం->initial_కొలత_rect.కుడి + దత్తాంశం->initial_కొలత_rect.ఎడమ - w) / 2;
                }
                clientDragRect.కుడి = w + clientDragRect.ఎడమ;
                clientDragRect.bottom = h + clientDragRect.శిఖరం;
                ఆపు;
            స్థితి WMSZ_BOTTOMRIGHT:
                clientDragRect.కుడి = w + clientDragRect.ఎడమ;
                clientDragRect.bottom = h + clientDragRect.శిఖరం;
                ఆపు;
            }

            // convert the client rect to a window rect
            ఒకవేళ (!Adjust_కిటికీ_Rect_Ex(&clientDragRect, Get_కిటికీ_Style(hwnd), GetMenu(hwnd) != ఖాళీ, Get_కిటికీ_Ex_Style(hwnd))) {
                ఆపు;
            }

            *dragRect = clientDragRect;
        }
        ఆపు;

    స్థితి WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        ఒకవేళ (hittest == HTCLIENT) {
            సమితి_Cursor(SDL_cursor);
            return_సంకేతం = TRUE;
        } లేకపోతే ఒకవేళ (!g_కిటికీ_చట్రం_Usable_While_Cursor_Hidden && !SDL_cursor) {
            సమితి_Cursor(ఖాళీ);
            return_సంకేతం = TRUE;
        }
    } ఆపు;

        // We were occluded, refresh our display
    స్థితి WM_PAINT:
    {
        RECT rect;
        ఒకవేళ (GetUpdateRect(hwnd, &rect, FALSE)) {
            స్థిరరాశి LONG style = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            ఒకవేళ (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                చివర_Paint(hwnd, &ps);
            }

            ValidateRect(hwnd, ఖాళీ);
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
        }
    }
        return_సంకేతం = 0;
        ఆపు;

        // We'll do our own drawing, prevent flicker
    స్థితి WM_ERASEBKGND:
        ఒకవేళ (Should_Clear_కిటికీ_On_Erase_Background(దత్తాంశం)) {
            RECT client_rect;
            HBRUSH brush;
            దత్తాంశం->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        తిరిగి 1;

    స్థితి WM_SYSCOMMAND:
    {
        ఒకవేళ (!g_WindowsEnableMenuMnemonics) {
            ఒకవేళ ((wParam & 0xFFF0) == SC_KEYMENU) {
                తిరిగి 0;
            }
        }

#ఒకవేళ defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        ఒకవేళ ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            ఒకవేళ (SDL_GetVideoDevice()->suspend_screensaver) {
                తిరిగి 0;
            }
        }
#అయితే_ముగింపు // System has screensaver support
    } ఆపు;

    స్థితి WM_CLOSE:
    {
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
    }
        return_సంకేతం = 0;
        ఆపు;

    స్థితి WM_TOUCH:
        ఒకవేళ (దత్తాంశం->videodata->Get_Touch_ఆదానం_Info && దత్తాంశం->videodata->Close_Touch_ఆదానం_Handle) {
            UINT i, అంకె_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, అంకె_inputs, &isstack);
            ఒకవేళ (inputs && దత్తాంశం->videodata->Get_Touch_ఆదానం_Info((HTOUCHINPUT)lParam, అంకె_inputs, inputs, పరిమాణం(TOUCHINPUT))) {
                RECT rect;
                దశాంశం x, y;

                ఒకవేళ (!GetClientRect(hwnd, &rect) || !WIN_కిటికీ_Rect_Valid(&rect)) {
                    ఒకవేళ (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    ఆపు;
                }
                Client_గమ్యం_Screen(hwnd, (LPPOINT)&rect);
                Client_గమ్యం_Screen(hwnd, (LPPOINT)&rect + 1);
                rect.శిఖరం *= 100;
                rect.ఎడమ *= 100;
                rect.bottom *= 100;
                rect.కుడి *= 100;

                కొరకు (i = 0; i < అంకె_inputs; ++i) {
                    PTOUCHINPUT ఆదానం = &inputs[i];
                    స్థిరరాశి పూర్ణాంకం w = (rect.కుడి - rect.ఎడమ);
                    స్థిరరాశి పూర్ణాంకం h = (rect.bottom - rect.శిఖరం);

                    స్థిరరాశి SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)ఆదానం->h_ఆధారం);
                    స్థిరరాశి SDL_FingerID fingerId = (ఆదానం->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    ఒకవేళ (SDL_కూడు_Touch(touchId, SDL_TOUCH_DEVICE_ప్రత్యక్ష, (ఆదానం->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        కొనసాగు;
                    }

                    // Get the normalized coordinates for the window
                    ఒకవేళ (w <= 1) {
                        x = 0.5f;
                    } లేకపోతే {
                        x = (దశాంశం)(ఆదానం->x - rect.ఎడమ) / (w - 1);
                    }
                    ఒకవేళ (h <= 1) {
                        y = 0.5f;
                    } లేకపోతే {
                        y = (దశాంశం)(ఆదానం->y - rect.శిఖరం) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    ఒకవేళ (ఆదానం->dwFlags & TOUCHEVENTF_కిందికి) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, దత్తాంశం->కిటికీ, SDL_EVENT_FINGER_కిందికి, x, y, 1.0f);
                    }
                    ఒకవేళ (ఆదానం->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, దత్తాంశం->కిటికీ, x, y, 1.0f);
                    }
                    ఒకవేళ (ఆదానం->dwFlags & TOUCHEVENTF_పైకి) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, దత్తాంశం->కిటికీ, SDL_EVENT_FINGER_పైకి, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            దత్తాంశం->videodata->Close_Touch_ఆదానం_Handle((HTOUCHINPUT)lParam);
            తిరిగి 0;
        }
        ఆపు;

#నిర్వచితమైతే HAVE_TPCSHRD_H

    స్థితి WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        తిరిగి TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#అయితే_ముగింపు // HAVE_TPCSHRD_H

    స్థితి WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT లెక్క = DragQueryFile(drop, 0xFFFFFFFF, ఖాళీ, 0);
        కొరకు (i = 0; i < లెక్క; ++i) {
            UINT కొలత = DragQueryFile(drop, i, ఖాళీ, 0) + 1;
            LPTSTR బఫరు_2 = (LPTSTR)SDL_malloc(పరిమాణం(TCHAR) * కొలత);
            ఒకవేళ (బఫరు_2) {
                ఒకవేళ (DragQueryFile(drop, i, బఫరు_2, కొలత)) {
                    అక్షరం *file = WIN_String_గమ్యం_UTF8(బఫరు_2);
                    SDL_SendDropFile(దత్తాంశం->కిటికీ, ఖాళీ, file);
                    SDL_free(file);
                }
                SDL_free(బఫరు_2);
            }
        }
        SDL_SendDropComplete(దత్తాంశం->కిటికీ);
        Drag_ముగింపు(drop);
        తిరిగి 0;
    }

    స్థితి WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } ఆపు;

    స్థితి WM_NCCALCSIZE:
    {
        SDL_కిటికీ_Flags కిటికీ_flags = దత్తాంశం->కిటికీ->flags;
        ఒకవేళ (wParam == TRUE && (కిటికీ_flags & SDL_కిటికీ_BORDERLESS) && !(కిటికీ_flags & SDL_కిటికీ_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            ఒకవేళ (Get_కిటికీ_Placement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = Monitor_From_కిటికీ(hwnd, MONITOR_DEFAULTTONULL);
                ఒకవేళ (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    స్థిరరాశి బిందువు_2 pt = { దత్తాంశం->కిటికీ->windowed.x, దత్తాంశం->కిటికీ->windowed.y };
                    hMonitor = Monitor_From_బిందువు(pt, MONITOR_DEFAULTTONEAREST);
                }
                ఒకవేళ (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cb_కొలత = పరిమాణం(info);
                    ఒకవేళ (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } లేకపోతే ఒకవేళ (!(కిటికీ_flags & SDL_కిటికీ_RESIZABLE) && !దత్తాంశం->force_ws_maximizebox) {
                పూర్ణాంకం w, h;
                ఒకవేళ (దత్తాంశం->కిటికీ->చివరి_కొలత_pending) {
                    w = దత్తాంశం->కిటికీ->pending.w;
                    h = దత్తాంశం->కిటికీ->pending.h;
                } లేకపోతే {
                    w = దత్తాంశం->కిటికీ->floating.w;
                    h = దత్తాంశం->కిటికీ->floating.h;
                }
                params->rgrc[0].కుడి = params->rgrc[0].ఎడమ + w;
                params->rgrc[0].bottom = params->rgrc[0].శిఖరం + h;
            }
            తిరిగి 0;
        }
    } ఆపు;

    స్థితి WM_NCHITTEST:
    {
        SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TOOLTIP) {
            తిరిగి HTTRANSPARENT;
        }

        ఒకవేళ (కిటికీ->తగిలింది_test) {
            బిందువు_2 winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            ఒకవేళ (Screen_గమ్యం_Client(hwnd, &winpoint)) {
                SDL_బిందువు బిందువు;
                SDL_తగిలింది_Test_ఫలితం rc;
                బిందువు.x = winpoint.x;
                బిందువు.y = winpoint.y;
                rc = కిటికీ->తగిలింది_test(కిటికీ, &బిందువు, కిటికీ->తగిలింది_test_దత్తాంశం);
                ఎంపిక (rc) {
#నిర్వచించు POST_తగిలింది_TEST(ret)                                                 \
    {                                                                      \
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_తగిలింది_TEST, 0, 0); \
        తిరిగి ret;                                                        \
    }
                స్థితి SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(ఖాళీ, ఖాళీ);
                    ఒకవేళ (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_సమితి_Mouse_Focus(కిటికీ);
                        తిరిగి HTCLIENT;
                    }

                    POST_తగిలింది_TEST(HTCAPTION);
                }
                స్థితి SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_తగిలింది_TEST(HTTOPLEFT);
                స్థితి SDL_HITTEST_RESIZE_శిఖరం:
                    POST_తగిలింది_TEST(HTTOP);
                స్థితి SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_తగిలింది_TEST(HTTOPRIGHT);
                స్థితి SDL_HITTEST_RESIZE_కుడి:
                    POST_తగిలింది_TEST(HTRIGHT);
                స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_తగిలింది_TEST(HTBOTTOMRIGHT);
                స్థితి SDL_HITTEST_RESIZE_BOTTOM:
                    POST_తగిలింది_TEST(HTBOTTOM);
                స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_తగిలింది_TEST(HTBOTTOMLEFT);
                స్థితి SDL_HITTEST_RESIZE_ఎడమ:
                    POST_తగిలింది_TEST(HTLEFT);
#నిర్వచనం_రద్దు POST_తగిలింది_TEST
                స్థితి SDL_HITTEST_సాధారణ:
                    తిరిగి HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } ఆపు;

    స్థితి WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        ఒకవేళ (దత్తాంశం->videodata->Get_Dpi_For_కిటికీ && దత్తాంశం->videodata->Adjust_కిటికీ_Rect_Ex_For_Dpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            స్థిరరాశి పూర్ణాంకం తదుపరి_DPI = (పూర్ణాంకం)wParam;
            స్థిరరాశి పూర్ణాంకం prevDPI = (పూర్ణాంకం)దత్తాంశం->videodata->Get_Dpi_For_కిటికీ(hwnd);
            కొలత_3 *కొలత_లోపల_బహిర్గతం = (కొలత_3 *)lParam;

            పూర్ణాంకం చట్రం_w, చట్రం_h;
            పూర్ణాంకం query_client_w_win, query_client_h_win;

#నిర్వచితమైతే HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, తదుపరి_DPI, కొలత_లోపల_బహిర్గతం->cx, కొలత_లోపల_బహిర్గతం->cy);
#అయితే_ముగింపు

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS) && !SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ)) {
                    WIN_Adjust_కిటికీ_Rect_For_HWND(hwnd, &rect, prevDPI);
                }

                చట్రం_w = -rect.ఎడమ + rect.కుడి;
                చట్రం_h = -rect.శిఖరం + rect.bottom;

                query_client_w_win = కొలత_లోపల_బహిర్గతం->cx - చట్రం_w;
                query_client_h_win = కొలత_లోపల_బహిర్గతం->cy - చట్రం_h;
            }

            // Add the window frame size that would be used at nextDPI
            {
                RECT rect = { 0 };
                rect.కుడి = query_client_w_win;
                rect.bottom = query_client_h_win;

                ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS) && !SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ)) {
                    WIN_Adjust_కిటికీ_Rect_For_HWND(hwnd, &rect, తదుపరి_DPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                కొలత_లోపల_బహిర్గతం->cx = rect.కుడి - rect.ఎడమ;
                కొలత_లోపల_బహిర్గతం->cy = rect.bottom - rect.శిఖరం;
            }

#నిర్వచితమైతే HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", కొలత_లోపల_బహిర్గతం->cx, కొలత_లోపల_బహిర్గతం->cy);
#అయితే_ముగింపు
            తిరిగి TRUE;
        }
        ఆపు;

    స్థితి WM_DPICHANGED:
        // Windows 8.1+
        {
            స్థిరరాశి పూర్ణాంకం newDPI = HIWORD(wParam);
            RECT *స్థిరరాశి suggestedRect = (RECT *)lParam;
            పూర్ణాంకం w, h;

#నిర్వచితమైతే HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->ఎడమ, suggestedRect->శిఖరం, suggestedRect->కుడి - suggestedRect->ఎడమ, suggestedRect->bottom - suggestedRect->శిఖరం);
#అయితే_ముగింపు

            ఒకవేళ (దత్తాంశం->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#నిర్వచితమైతే HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#అయితే_ముగింపు
                తిరిగి 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.కుడి = దత్తాంశం->కిటికీ->w;
                rect.bottom = దత్తాంశం->కిటికీ->h;

                ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS)) {
                    WIN_Adjust_కిటికీ_Rect_For_HWND(hwnd, &rect, newDPI);
                }

                w = rect.కుడి - rect.ఎడమ;
                h = rect.bottom - rect.శిఖరం;
            }

#నిర్వచితమైతే HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: current SDL window size: (%dx%d)\tcalling SetWindowPos: (%d, %d), (%dx%d)",
                    దత్తాంశం->కిటికీ->w, దత్తాంశం->కిటికీ->h,
                    suggestedRect->ఎడమ, suggestedRect->శిఖరం, w, h);
#అయితే_ముగింపు

            దత్తాంశం->expected_resize = true;
            సమితి_కిటికీ_Pos(hwnd,
                         ఖాళీ,
                         suggestedRect->ఎడమ,
                         suggestedRect->శిఖరం,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            దత్తాంశం->expected_resize = false;
            తిరిగి 0;
        }

    స్థితి WM_SETTINGCHANGE:
        ఒకవేళ (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_సమితి_System_Theme(WIN_GetSystemTheme());
            WIN_Update_Dark_బహుళకం_For_HWND(hwnd);
        }
        ఒకవేళ (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        ఒకవేళ (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        ఆపు;
#లేకపోతే
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    స్థితి WM_కొలత:
    {
        RECT rect;
        పూర్ణాంకం w, h;

        ఒకవేళ (GetClientRect(hwnd, &rect) && WIN_కిటికీ_Rect_Valid(&rect)) {
            w = rect.కుడి;
            h = rect.bottom;
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESIZED, w, h);
        }
    } ఆపు;
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    అప్రమేయ:
        ఆపు;
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (సందేశం_2 && సందేశం_2 == దత్తాంశం->videodata->WM_TASKBAR_BUTTON_CREATED) {
        దత్తాంశం->taskbar_button_created = true;
        WIN_Apply_కిటికీ_పురోగతి(SDL_GetVideoDevice(), దత్తాంశం->కిటికీ);
    }
#అయితే_ముగింపు

    // If there's a window proc, assume it's going to handle messages
    ఒకవేళ (దత్తాంశం->wndproc) {
        తిరిగి Call_కిటికీ_Proc(దత్తాంశం->wndproc, hwnd, సందేశం_2, wParam, lParam);
    } లేకపోతే ఒకవేళ (return_సంకేతం >= 0) {
        తిరిగి return_సంకేతం;
    } లేకపోతే {
        తిరిగి Call_కిటికీ_Proc(Def_కిటికీ_Proc, hwnd, సందేశం_2, wParam, lParam);
    }
}

పూర్ణాంకం WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    ఒకవేళ (g_Windows_Enable_సందేశం_Loop) {
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_గమ్యం_MS(timeoutNS);
        ret = సందేశం_Wait_For_గుణిజం_Objects(0, ఖాళీ, FALSE, timeout, QS_ALLINPUT);
        ఒకవేళ (ret == WAIT_OBJECT_0) {
            తిరిగి 1;
        } లేకపోతే {
            తిరిగి 0;
        }
#లేకపోతే
        // MsgWaitForMultipleObjects is desktop-only.
        సందేశం_3 సందేశం_2;
        BOOL సందేశం_ఫలితం;
        UINT_PTR timer_id = 0;
        ఒకవేళ (timeoutNS > 0) {
            timer_id = సమితి_Timer(ఖాళీ, 0, (UINT)SDL_NS_గమ్యం_MS(timeoutNS), ఖాళీ);
            సందేశం_ఫలితం = Get_సందేశం(&సందేశం_2, 0, 0, 0);
            KillTimer(ఖాళీ, timer_id);
        } లేకపోతే ఒకవేళ (timeoutNS == 0) {
            సందేశం_ఫలితం = Peek_సందేశం(&సందేశం_2, ఖాళీ, 0, 0, PM_REMOVE);
        } లేకపోతే {
            సందేశం_ఫలితం = Get_సందేశం(&సందేశం_2, 0, 0, 0);
        }
        ఒకవేళ (సందేశం_ఫలితం) {
            ఒకవేళ (సందేశం_2.సందేశం == WM_TIMER && !సందేశం_2.hwnd && సందేశం_2.wParam == timer_id) {
                తిరిగి 0;
            }
            ఒకవేళ (g_Windows_సందేశం_Hook) {
                ఒకవేళ (!g_Windows_సందేశం_Hook(g_Windows_సందేశం_Hook_దత్తాంశం, &సందేశం_2)) {
                    తిరిగి 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_సందేశం(&సందేశం_2);
            Dispatch_సందేశం(&సందేశం_2);
            తిరిగి 1;
        } లేకపోతే {
            తిరిగి 0;
        }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } లేకపోతే {
        // Fail the wait so the caller falls back to polling
        తిరిగి -1;
    }
}

శూన్య WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Post_సందేశం(దత్తాంశం->hwnd, దత్తాంశం->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
శూన్య WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    సందేశం_3 సందేశం_2;

    ఒకవేళ (g_Windows_Enable_సందేశం_Loop) {
        SDL_processing_messages = true;

        అయితే (Peek_సందేశం(&సందేశం_2, hwnd, 0, 0, PM_REMOVE)) {
            WIN_సమితి_సందేశం_Tick(సందేశం_2.సమయం);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_సందేశం(&సందేశం_2);
            Dispatch_సందేశం(&సందేశం_2);
        }

        SDL_processing_messages = false;
    }
}

శూన్య WIN_PumpEvents(SDL_VideoDevice *_this)
{
    సందేశం_3 సందేశం_2;
#నిర్వచితమైతే _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#సూచన warning(నెట్టు)
#సూచన warning(disable : 28159)
#అయితే_ముగింపు
    DWORD చివర_ticks = Get_Tick_లెక్క() + 1;
#నిర్వచితమైతే _MSC_VER
#సూచన warning(తీయి)
#అయితే_ముగింపు
    పూర్ణాంకం new_messages = 0;

    ఒకవేళ (_this->అంతర్గత->gameinput_context) {
        WIN_Update_Game_ఆదానం(_this);
    }

    ఒకవేళ (g_Windows_Enable_సందేశం_Loop) {
        SDL_processing_messages = true;

        అయితే (Peek_సందేశం(&సందేశం_2, ఖాళీ, 0, 0, PM_REMOVE)) {
            ఒకవేళ (g_Windows_సందేశం_Hook) {
                ఒకవేళ (!g_Windows_సందేశం_Hook(g_Windows_సందేశం_Hook_దత్తాంశం, &సందేశం_2)) {
                    కొనసాగు;
                }
            }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            ఒకవేళ (సందేశం_2.సందేశం == WM_MOUSEMOVE && SDL_చివరి_warp_సమయం) {
                ఒకవేళ (!SDL_TICKS_PASSED(సందేశం_2.సమయం, (SDL_చివరి_warp_సమయం + 1))) {
                    కొనసాగు;
                }

                // This mouse message happened after the warp
                SDL_చివరి_warp_సమయం = 0;
            }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

            WIN_సమితి_సందేశం_Tick(సందేశం_2.సమయం);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            Translate_సందేశం(&సందేశం_2);
            Dispatch_సందేశం(&సందేశం_2);

            // Make sure we don't busy loop here forever if there are lots of events coming in
            ఒకవేళ (SDL_TICKS_PASSED(సందేశం_2.సమయం, చివర_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                స్థిరరాశి పూర్ణాంకం MAX_NEW_MESSAGES = 3;
                ++new_messages;
                ఒకవేళ (new_messages > MAX_NEW_MESSAGES) {
                    ఆపు;
                }
            }
        }

        SDL_processing_messages = false;
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    స్థిరరాశి bool *keystate = SDL_GetKeyboardState(ఖాళీ);
    ఒకవేళ (keystate[SDL_SCANCODE_LSHIFT] && !(Get_కీలకం_State(VK_LSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    ఒకవేళ (keystate[SDL_SCANCODE_RSHIFT] && !(Get_కీలకం_State(VK_RSHIFT) & 0x8000)) {
        SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_కిటికీ *focus_కిటికీ = SDL_GetKeyboardFocus();
    ఒకవేళ (!focus_కిటికీ || !(focus_కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED)) {
        ఒకవేళ (keystate[SDL_SCANCODE_LGUI] && !(Get_కీలకం_State(VK_LWIN) & 0x8000)) {
            SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        ఒకవేళ (keystate[SDL_SCANCODE_RGUI] && !(Get_కీలకం_State(VK_RWIN) & 0x8000)) {
            SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    ఒకవేళ (_this) {
        SDL_కిటికీ *కిటికీ = _this->windows;
        అయితే (కిటికీ) {
            bool refresh_clipcursor = false;
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
            ఒకవేళ (దత్తాంశం) {
                refresh_clipcursor = దత్తాంశం->clipcursor_queued;
                దత్తాంశం->clipcursor_queued = false;    // Must be cleared unconditionally.
                దత్తాంశం->postpone_clipcursor = false;  // Must be cleared unconditionally.
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
            ఒకవేళ (refresh_clipcursor) {
                WIN_UpdateClipCursor(కిటికీ);
            }
            కిటికీ = కిటికీ->తదుపరి;
        }
    }

    // Synchronize internal mouse capture state to the most current cursor state
    // since for whatever reason we are not depending exclusively on SetCapture/
    // ReleaseCapture to pipe in out-of-window mouse events.
    // Formerly WIN_UpdateMouseCapture().
    // TODO: can this go before clipcursor?
    focus_కిటికీ = SDL_GetKeyboardFocus();
    ఒకవేళ (focus_కిటికీ && (focus_కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = focus_కిటికీ->అంతర్గత;

        ఒకవేళ (!దత్తాంశం->mouse_tracked) {
            బిందువు_2 cursorPos;

            ఒకవేళ (GetCursorPos(&cursorPos) && Screen_గమ్యం_Client(దత్తాంశం->hwnd, &cursorPos)) {
                bool మార్పిడి_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID, false, (దశాంశం)cursorPos.x, (దశాంశం)cursorPos.y);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID,
                                    !మార్పిడి_Buttons ? SDL_BUTTON_ఎడమ : SDL_BUTTON_కుడి,
                                    (Get_Async_కీలకం_State(VK_LBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID,
                                    !మార్పిడి_Buttons ? SDL_BUTTON_కుడి : SDL_BUTTON_ఎడమ,
                                    (Get_Async_కీలకం_State(VK_RBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID,
                                    SDL_BUTTON_మధ్య,
                                    (Get_Async_కీలకం_State(VK_MBUTTON) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID,
                                    SDL_BUTTON_X1,
                                    (Get_Async_కీలకం_State(VK_XBUTTON1) & 0x8000) != 0);
                SDL_SendMouseButton(WIN_GetEventTimestamp(), దత్తాంశం->కిటికీ, mouseID,
                                    SDL_BUTTON_X2,
                                    (Get_Async_కీలకం_State(VK_XBUTTON2) & 0x8000) != 0);
            }
        }
    }

    WIN_UpdateIMECandidates(_this);

#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#నిర్వచితమైతే SDL_PLATFORM_GDK
    GDK_Dispatch_Task_వరుస();
#అయితే_ముగింపు
}

స్థిర పూర్ణాంకం app_registered = 0;
LPTSTR SDL_Appname = ఖాళీ;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = ఖాళీ;

స్థిర శూన్య WIN_Clean_రిజిస్టరు_App(WNDCLASSEX wcex)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    ఒకవేళ (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#అయితే_ముగింపు
    SDL_free(SDL_Appname);
    SDL_Appname = ఖాళీ;
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
స్థిర BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (శూన్య)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = ఎక్కించు_Icon(hModule, lpName);

    // Do not bother enumerating any more.
    తిరిగి FALSE;
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_రిజిస్టరు_App(స్థిరరాశి అక్షరం *name, Uint32 style, శూన్య *hInst)
{
    WNDCLASSEX wcex;
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    స్థిరరాశి అక్షరం *hint;
#అయితే_ముగింపు

    // Only do this once...
    ఒకవేళ (app_registered) {
        ++app_registered;
        తిరిగి true;
    }
    SDL_assert(!SDL_Appname);
    ఒకవేళ (!name) {
        name = "SDL_app";
#ఒకవేళ defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#అయితే_ముగింపు
    }
    SDL_Appname = WIN_UTF8_గమ్యం_String(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(ఖాళీ);

    // Register the application class
    SDL_zero(wcex);
    wcex.cb_కొలత = పరిమాణం(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_కిటికీ_Proc;
    wcex.hInstance = SDL_Instance;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    ఒకవేళ (hint && *hint) {
        wcex.hIcon = ఎక్కించు_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        ఒకవేళ (hint && *hint) {
            wcex.hIconSm = ఎక్కించు_Icon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } లేకపోతే {
        // Use the first icon as a default icon, like in the Explorer.
        Enum_Resource_పేర్లు(SDL_Instance, RT_సమూహం_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ఒకవేళ (!రిజిస్టరు_Class_Ex(&wcex)) {
        WIN_Clean_రిజిస్టరు_App(wcex);
        తిరిగి SDL_సమితి_Error("Couldn't register application class");
    }

    app_registered = 1;
    తిరిగి true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
శూన్య SDL_UnregisterApp(శూన్య)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    ఒకవేళ (!app_registered) {
        తిరిగి;
    }
    --app_registered;
    ఒకవేళ (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = ఖాళీ;
        wcex.hIconSm = ఖాళీ;
        // Check for any registered window classes.
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ఒకవేళ (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#అయితే_ముగింపు
        WIN_Clean_రిజిస్టరు_App(wcex);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
