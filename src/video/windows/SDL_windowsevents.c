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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#include "SDL_windowsvideo.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_touch_c.h"
#include "../../events/scancodes_windows.h"
#include "../../main/SDL_main_callbacks.h"
#include "../../core/windows/SDL_hid.h"

// Dropfile support
#include <shellapi.h>

// Device names
#include <setupapi.h>

// For GET_X_LPARAM, GET_Y_LPARAM.
#include <windowsx.h>

// For WM_TABLET_QUERYSYSTEMGESTURESTATUS et. al.
#ifdef HAVE_TPCSHRD_H
#include <tpcshrd.h>
#endif // HAVE_TPCSHRD_H

#ако 0
#define WMMSG_DEBUG
#endif
#ifdef WMMSG_DEBUG
#include <stdio.h>
#include "wmmsg.h"
#endif

#ако !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#include <shobjidl.h>
#endif

#ifdef SDL_PLATFORM_GDK
#include "../../core/gdk/SDL_gdk.h"
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
typedef Uint64 QWORD; // Needed for NEXTRAWINPUTBLOCK()
#endif

static bool SDL_processing_messages;
static DWORD message_tick;
static Uint64 timestamp_offset;

static void WIN_SetMessageTick(DWORD tick)
{
    message_tick = tick;
}

static Uint64 WIN_GetEventTimestamp(void)
{
    const Uint64 TIMESTAMP_WRAP_OFFSET = SDL_MS_TO_NS(0x100000000LL);
    Uint64 timestamp, now;

    ако (!SDL_processing_messages) {
        // message_tick isn't valid, just use the current time
        врати 0;
    }

    now = SDL_GetTicksNS();
    timestamp = SDL_MS_TO_NS(message_tick);
    timestamp += timestamp_offset;
    ако (!timestamp_offset) {
        // Initializing timestamp offset
        //SDL_Log("Initializing timestamp offset");
        timestamp_offset = (now - timestamp);
        timestamp = now;
    } инако ако ((Sint64)(now - timestamp - TIMESTAMP_WRAP_OFFSET) >= 0) {
        // The windows message tick wrapped
        //SDL_Log("Adjusting timestamp offset for wrapping tick");
        timestamp_offset += TIMESTAMP_WRAP_OFFSET;
        timestamp += TIMESTAMP_WRAP_OFFSET;
    } инако ако (timestamp > now) {
        // We got a newer timestamp, but it can't be newer than now, so adjust our offset
        //SDL_Log("Adjusting timestamp offset, %.2f ms newer", (double)(timestamp - now) / SDL_NS_PER_MS);
        timestamp_offset -= (timestamp - now);
        timestamp = now;
    }
    врати timestamp;
}

// A message hook called before TranslateMessage()
static SDL_WindowsMessageHook g_WindowsMessageHook = NULL;
static void *g_WindowsMessageHookData = NULL;

void SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, void *userdata)
{
    g_WindowsMessageHook = callback;
    g_WindowsMessageHookData = userdata;
}

static SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam, Uint16 *rawcode, bool *virtual_key)
{
    SDL_Scancode code;
    Uint8 index;
    Uint16 keyFlags = HIWORD(lParam);
    Uint16 scanCode = LOBYTE(keyFlags);

    /* On-Screen Keyboard can send wrong scan codes with high-order bit set (key break code).
     * Strip high-order bit. */
    scanCode &= ~0x80;

    *virtual_key = (scanCode == 0);

    ако (scanCode != 0) {
        ако ((keyFlags & KF_EXTENDED) == KF_EXTENDED) {
            scanCode = MAKEWORD(scanCode, 0xe0);
        } инако ако (scanCode == 0x45) {
            // Pause
            scanCode = 0xe046;
        }
    } инако {
        Uint16 vkCode = LOWORD(wParam);

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        /* Windows may not report scan codes for some buttons (multimedia buttons etc).
         * Get scan code from the VK code.*/
        scanCode = LOWORD(MapVirtualKey(vkCode, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

        /* Pause/Break key have a special scan code with 0xe1 prefix.
         * Use Pause scan code that is used in Win32. */
        ако (scanCode == 0xe11d) {
            scanCode = 0xe046;
        }
    }

    // Pack scan code into one byte to make the index.
    index = LOBYTE(scanCode) | (HIBYTE(scanCode) ? 0x80 : 0x00);
    code = windows_scancode_table[index];
    *rawcode = scanCode;

    врати code;
}

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
static bool WIN_ShouldIgnoreFocusClick(SDL_WindowData *data)
{
    врати !SDL_WINDOW_IS_POPUP(data->window) &&
           !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
}

static void WIN_CheckWParamMouseButton(Uint64 timestamp, bool bwParamMousePressed, Uint32 mouseFlags, bool bSwapButtons, SDL_WindowData *data, Uint8 button, SDL_MouseID mouseID)
{
    ако (bSwapButtons) {
        ако (button == SDL_BUTTON_LEFT) {
            button = SDL_BUTTON_RIGHT;
        } инако ако (button == SDL_BUTTON_RIGHT) {
            button = SDL_BUTTON_LEFT;
        }
    }

    ако (data->focus_click_pending & SDL_BUTTON_MASK(button)) {
        // Ignore the button click for activation
        ако (!bwParamMousePressed) {
            data->focus_click_pending &= ~SDL_BUTTON_MASK(button);
            WIN_UpdateClipCursor(data->window);
        }
        врати;
    }

    ако (bwParamMousePressed && !(mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, true);
    } инако ако (!bwParamMousePressed && (mouseFlags & SDL_BUTTON_MASK(button))) {
        SDL_SendMouseButton(timestamp, data->window, mouseID, button, false);
    }
}

/*
 * Some windows systems fail to send a WM_LBUTTONDOWN sometimes, but each mouse move contains the current button state also
 *  so this function reconciles our view of the world with the current buttons reported by windows
 */
static void WIN_CheckWParamMouseButtons(Uint64 timestamp, WPARAM wParam, SDL_WindowData *data, SDL_MouseID mouseID)
{
    ако (wParam != data->mouse_button_flags) {
        SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(NULL, NULL);

        // WM_LBUTTONDOWN and friends handle button swapping for us. No need to check SM_SWAPBUTTON here.
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_LBUTTON), mouseFlags, false, data, SDL_BUTTON_LEFT, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_MBUTTON), mouseFlags, false, data, SDL_BUTTON_MIDDLE, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_RBUTTON), mouseFlags, false, data, SDL_BUTTON_RIGHT, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON1), mouseFlags, false, data, SDL_BUTTON_X1, mouseID);
        WIN_CheckWParamMouseButton(timestamp, (wParam & MK_XBUTTON2), mouseFlags, false, data, SDL_BUTTON_X2, mouseID);

        data->mouse_button_flags = wParam;
    }
}

static void WIN_CheckAsyncMouseRelease(Uint64 timestamp, SDL_WindowData *data)
{
    SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;
    Uint32 mouseFlags;
    SHORT keyState;
    bool swapButtons;

    /* mouse buttons may have changed state here, we need to resync them,
       but we will get a WM_MOUSEMOVE right away which will fix things up if in non raw mode also
    */
    mouseFlags = SDL_GetMouseState(NULL, NULL);
    swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    keyState = GetAsyncKeyState(VK_LBUTTON);
    ако (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_LEFT, mouseID);
    }
    keyState = GetAsyncKeyState(VK_RBUTTON);
    ако (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_RIGHT, mouseID);
    }
    keyState = GetAsyncKeyState(VK_MBUTTON);
    ако (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_MIDDLE, mouseID);
    }
    keyState = GetAsyncKeyState(VK_XBUTTON1);
    ако (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X1, mouseID);
    }
    keyState = GetAsyncKeyState(VK_XBUTTON2);
    ако (!(keyState & 0x8000)) {
        WIN_CheckWParamMouseButton(timestamp, false, mouseFlags, swapButtons, data, SDL_BUTTON_X2, mouseID);
    }
    data->mouse_button_flags = (WPARAM)-1;
}

static void WIN_UpdateFocus(SDL_Window *window, bool expect_focus, LPPOINT pos)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    bool had_focus = (SDL_GetKeyboardFocus() == window);
    bool has_focus = (GetForegroundWindow() == hwnd);

    ако (had_focus == has_focus || has_focus != expect_focus) {
        врати;
    }

    ако (has_focus) {
        POINT cursorPos;

        ако (WIN_ShouldIgnoreFocusClick(data) && !(window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
            ако (GetAsyncKeyState(VK_LBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_LMASK : SDL_BUTTON_RMASK;
            }
            ако (GetAsyncKeyState(VK_RBUTTON)) {
                data->focus_click_pending |= !swapButtons ? SDL_BUTTON_RMASK : SDL_BUTTON_LMASK;
            }
            ако (GetAsyncKeyState(VK_MBUTTON)) {
                data->focus_click_pending |= SDL_BUTTON_MMASK;
            }
            ако (GetAsyncKeyState(VK_XBUTTON1)) {
                data->focus_click_pending |= SDL_BUTTON_X1MASK;
            }
            ако (GetAsyncKeyState(VK_XBUTTON2)) {
                data->focus_click_pending |= SDL_BUTTON_X2MASK;
            }
        }

        SDL_SetKeyboardFocus(window->keyboard_focus ? window->keyboard_focus : window);

        // In relative mode we are guaranteed to have mouse focus if we have keyboard focus
        ако (!SDL_GetMouse()->relative_mode) {
            cursorPos.x = pos->x;
            cursorPos.y = pos->y;
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (float)cursorPos.x, (float)cursorPos.y);
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
    } инако {
        data->in_window_deactivation = true;

        SDL_SetKeyboardFocus(NULL);
        // In relative mode we are guaranteed to not have mouse focus if we don't have keyboard focus
        ако (SDL_GetMouse()->relative_mode) {
            SDL_SetMouseFocus(NULL);
        }
        WIN_ResetDeadKeys();

        WIN_UnclipCursorForWindow(window);

        data->in_window_deactivation = false;
    }
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

static bool ShouldGenerateWindowCloseOnAltF4(void)
{
    врати SDL_GetHintBoolean(SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4, true);
}

static bool ShouldClearWindowOnEraseBackground(SDL_WindowData *data)
{
    switch (data->hint_erase_background_mode) {
    case SDL_ERASEBACKGROUNDMODE_NEVER:
        врати false;
    case SDL_ERASEBACKGROUNDMODE_INITIAL:
        врати !data->videodata->cleared;
    case SDL_ERASEBACKGROUNDMODE_ALWAYS:
        врати true;
    default:
        // Unexpected value, fallback to default behaviour
        врати !data->videodata->cleared;
    }
}

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
// We want to generate mouse events from mouse and pen, and touch events from touchscreens
#define MI_WP_SIGNATURE      0xFF515700
#define MI_WP_SIGNATURE_MASK 0xFFFFFF00
#define IsTouchEvent(dw)     ((dw)&MI_WP_SIGNATURE_MASK) == MI_WP_SIGNATURE

typedef enum
{
    SDL_MOUSE_EVENT_SOURCE_UNKNOWN,
    SDL_MOUSE_EVENT_SOURCE_MOUSE,
    SDL_MOUSE_EVENT_SOURCE_TOUCH,
    SDL_MOUSE_EVENT_SOURCE_PEN,
} SDL_MOUSE_EVENT_SOURCE;

static SDL_MOUSE_EVENT_SOURCE GetMouseMessageSource(ULONG extrainfo)
{
    // Mouse data (ignoring synthetic mouse events generated for touchscreens)
    /* Versions below Vista will set the low 7 bits to the Mouse ID and don't use bit 7:
       Check bits 8-31 for the signature (which will indicate a Tablet PC Pen or Touch Device).
       Only check bit 7 when Vista and up(Cleared=Pen, Set=Touch(which we need to filter out)),
       when the signature is set. The Mouse ID will be zero for an actual mouse. */
    ако (IsTouchEvent(extrainfo)) {
        ако (extrainfo & 0x80) {
            врати SDL_MOUSE_EVENT_SOURCE_TOUCH;
        } инако {
            врати SDL_MOUSE_EVENT_SOURCE_PEN;
        }
    }
    врати SDL_MOUSE_EVENT_SOURCE_MOUSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

static SDL_WindowData *WIN_GetWindowDataFromHWND(HWND hwnd)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    SDL_Window *window;

    ако (_this) {
        за (window = _this->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            ако (data && data->hwnd == hwnd) {
                врати data;
            }
        }
    }
    врати NULL;
}

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
LRESULT CALLBACK
WIN_KeyboardHookProc(цео nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *hookData = (KBDLLHOOKSTRUCT *)lParam;
    SDL_VideoData *data = SDL_GetVideoDevice()->internal;
    SDL_Scancode scanCode;

    ако (nCode < 0 || nCode != HC_ACTION) {
        врати CallNextHookEx(NULL, nCode, wParam, lParam);
    }
    ако (hookData->scanCode == 0x21d) {
        // Skip fake LCtrl when RAlt is pressed
        врати 1;
    }

    switch (hookData->vkCode) {
    case VK_LWIN:
        scanCode = SDL_SCANCODE_LGUI;
        break;
    case VK_RWIN:
        scanCode = SDL_SCANCODE_RGUI;
        break;
    case VK_LMENU:
        scanCode = SDL_SCANCODE_LALT;
        break;
    case VK_RMENU:
        scanCode = SDL_SCANCODE_RALT;
        break;
    case VK_LCONTROL:
        scanCode = SDL_SCANCODE_LCTRL;
        break;
    case VK_RCONTROL:
        scanCode = SDL_SCANCODE_RCTRL;
        break;
    case VK_SNAPSHOT:
        scanCode = SDL_SCANCODE_PRINTSCREEN;
        break;

    // These are required to intercept Alt+Tab and Alt+Esc on Windows 7
    case VK_TAB:
        scanCode = SDL_SCANCODE_TAB;
        break;
    case VK_ESCAPE:
        scanCode = SDL_SCANCODE_ESCAPE;
        break;

    default:
        врати CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    ако (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        ако (!data->raw_keyboard_enabled) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, true);
        }
    } инако {
        ако (!data->raw_keyboard_enabled) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, hookData->scanCode, scanCode, false);
        }

        /* If the key was down prior to our hook being installed, allow the
           key up message to pass normally the first time. This ensures other
           windows have a consistent view of the key state, and avoids keys
           being stuck down in those windows if they are down when the grab
           happens and raised while grabbed. */
        ако (hookData->vkCode <= 0xFF && data->pre_hook_key_state[hookData->vkCode]) {
            data->pre_hook_key_state[hookData->vkCode] = 0;
            врати CallNextHookEx(NULL, nCode, wParam, lParam);
        }
    }

    врати 1;
}

static bool WIN_SwapButtons(HANDLE hDevice)
{
    ако (hDevice == NULL) {
        // Touchpad, already has buttons swapped
        врати false;
    }
    врати GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

static void WIN_HandleRawMouseInput(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWMOUSE *rawmouse)
{
    static struct {
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

    цео dx = (цео)rawmouse->lLastX;
    цео dy = (цео)rawmouse->lLastY;
    bool haveMotion = (dx || dy);
    bool haveButton = (rawmouse->usButtonFlags != 0);
    bool isAbsolute = ((rawmouse->usFlags & MOUSE_MOVE_ABSOLUTE) != 0);
    SDL_MouseID mouseID = (SDL_MouseID)(uintptr_t)hDevice;

    // Check whether relative mode should also receive events from the rawinput stream
    ако (!data->raw_mouse_enabled) {
        врати;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    SDL_Window *window = SDL_GetKeyboardFocus();
    ако (!window) {
        врати;
    }

    SDL_Mouse *mouse = SDL_GetMouse();
    ако (!mouse) {
        врати;
    }

    ако (GetMouseMessageSource(rawmouse->ulExtraInformation) != SDL_MOUSE_EVENT_SOURCE_MOUSE ||
        (SDL_TouchDevicesAvailable() && (rawmouse->ulExtraInformation & 0x80) == 0x80)) {
        врати;
    }

    SDL_WindowData *windowdata = window->internal;

    ако (haveMotion && !windowdata->in_modal_loop) {
        ако (!isAbsolute) {
            SDL_SendMouseMotion(timestamp, window, mouseID, true, (float)dx, (float)dy);
        } инако {
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
            цео w = GetSystemMetrics(virtual_desktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
            цео h = GetSystemMetrics(virtual_desktop ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
            цео x = raw_coordinates ? dx : (цео)(((float)dx / 65535.0f) * w);
            цео y = raw_coordinates ? dy : (цео)(((float)dy / 65535.0f) * h);
            цео relX, relY;

            /* Calculate relative motion */
            ако (data->last_raw_mouse_position.x == 0 && data->last_raw_mouse_position.y == 0) {
                data->last_raw_mouse_position.x = x;
                data->last_raw_mouse_position.y = y;
            }
            relX = x - data->last_raw_mouse_position.x;
            relY = y - data->last_raw_mouse_position.y;

            ако (remote_desktop) {
                ако (!windowdata->in_title_click && !windowdata->focus_click_pending) {
                    static цео wobble;
                    float floatX = (float)x / w;
                    float floatY = (float)y / h;

                    /* See if the mouse is at the edge of the screen, or in the RDP title bar area */
                    ако (floatX <= 0.01f || floatX >= 0.99f || floatY <= 0.01f || floatY >= 0.99f || y < 32) {
                        /* Wobble the cursor position so it's not ignored if the last warp didn't have any effect */
                        RECT rect = windowdata->cursor_clipped_rect;
                        цео warpX = rect.left + ((rect.right - rect.left) / 2) + wobble;
                        цео warpY = rect.top + ((rect.bottom - rect.top) / 2);

                        WIN_SetCursorPos(warpX, warpY);

                        ++wobble;
                        ако (wobble > 1) {
                            wobble = -1;
                        }
                    } инако {
                        /* Send relative motion if we didn't warp last frame (had good position data)
                           We also sometimes get large deltas due to coalesced mouse motion and warping,
                           so ignore those.
                         */
                        const цео MAX_RELATIVE_MOTION = (h / 6);
                        ако (SDL_abs(relX) < MAX_RELATIVE_MOTION &&
                            SDL_abs(relY) < MAX_RELATIVE_MOTION) {
                            SDL_SendMouseMotion(timestamp, window, mouseID, true, (float)relX, (float)relY);
                        }
                    }
                }
            } инако ако (mouse->pen_mouse_events) {
                const цео MAXIMUM_TABLET_RELATIVE_MOTION = 32;
                ако (SDL_abs(relX) > MAXIMUM_TABLET_RELATIVE_MOTION ||
                    SDL_abs(relY) > MAXIMUM_TABLET_RELATIVE_MOTION) {
                    /* Ignore this motion, probably a pen lift and drop */
                } инако {
                    SDL_SendMouseMotion(timestamp, window, mouseID, true, (float)relX, (float)relY);
                }
            } инако {
                цео screen_x = virtual_desktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                цео screen_y = virtual_desktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;

                ако (!data->raw_input_fake_pen_id) {
                    data->raw_input_fake_pen_id = SDL_AddPenDevice(timestamp, "raw mouse input", window, NULL, (void *)(size_t)-1, true);
                }
                SDL_SendPenMotion(timestamp, data->raw_input_fake_pen_id, window, (float)(x + screen_x - window->x), (float)(y + screen_y - window->y));
            }

            data->last_raw_mouse_position.x = x;
            data->last_raw_mouse_position.y = y;
        }
    }

    ако (haveButton) {
        за (цео i = 0; i < SDL_arraysize(raw_buttons); ++i) {
            ако (rawmouse->usButtonFlags & raw_buttons[i].usButtonFlags) {
                Uint8 button = raw_buttons[i].button;
                bool down = raw_buttons[i].down;

                ако (button == SDL_BUTTON_LEFT) {
                    ако (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_RIGHT;
                    }
                } инако ако (button == SDL_BUTTON_RIGHT) {
                    ако (WIN_SwapButtons(hDevice)) {
                        button = SDL_BUTTON_LEFT;
                    }
                }

                ако (windowdata->focus_click_pending & SDL_BUTTON_MASK(button)) {
                    // Ignore the button click for activation
                    ако (!down) {
                        windowdata->focus_click_pending &= ~SDL_BUTTON_MASK(button);
                        WIN_UpdateClipCursor(window);
                    }
                    continue;
                }

                SDL_SendMouseButton(timestamp, window, mouseID, button, down);
            }
        }

        ако (rawmouse->usButtonFlags & RI_MOUSE_WHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            float fAmount = (float)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
        } инако ако (rawmouse->usButtonFlags & RI_MOUSE_HWHEEL) {
            SHORT amount = (SHORT)rawmouse->usButtonData;
            float fAmount = (float)amount / WHEEL_DELTA;
            SDL_SendMouseWheel(timestamp, window, mouseID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
        }

        /* Invalidate the mouse button flags. If we don't do this then disabling raw input
           will cause held down mouse buttons to persist when released. */
        windowdata->mouse_button_flags = (WPARAM)-1;
    }
}

static void WIN_HandleRawKeyboardInput(Uint64 timestamp, SDL_VideoData *data, HANDLE hDevice, RAWKEYBOARD *rawkeyboard)
{
    SDL_KeyboardID keyboardID = (SDL_KeyboardID)(uintptr_t)hDevice;

    ако (!data->raw_keyboard_enabled) {
        врати;
    }

    ако (rawkeyboard->Flags & RI_KEY_E1) {
        // First key in a Ctrl+{key} sequence
        data->pending_E1_key_sequence = true;
        врати;
    }

    ако ((rawkeyboard->Flags & RI_KEY_E0) && rawkeyboard->MakeCode == 0x2A) {
        // 0xE02A make code prefix, ignored
        врати;
    }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ако (!rawkeyboard->MakeCode) {
        rawkeyboard->MakeCode = LOWORD(MapVirtualKey(rawkeyboard->VKey, WIN_IsWindowsXP() ? MAPVK_VK_TO_VSC : MAPVK_VK_TO_VSC_EX));
    }
#endif
    ако (!rawkeyboard->MakeCode) {
        врати;
    }

    bool down;
    switch (rawkeyboard->Message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        down = true;
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        down = false;
        break;
    default:
        down = !(rawkeyboard->Flags & RI_KEY_BREAK);
        break;
    }

    SDL_Scancode code;
    USHORT rawcode = rawkeyboard->MakeCode;
    ако (data->pending_E1_key_sequence) {
        rawcode |= 0xE100;
        ако (rawkeyboard->MakeCode == 0x45) {
            // Ctrl+NumLock == Pause
            code = SDL_SCANCODE_PAUSE;
        } инако {
            // Ctrl+ScrollLock == Break (no SDL scancode?)
            code = SDL_SCANCODE_UNKNOWN;
        }
        data->pending_E1_key_sequence = false;
    } инако {
        // The code is in the lower 7 bits, the high bit is set for the E0 prefix
        Uint8 index = (Uint8)rawkeyboard->MakeCode;
        ако (rawkeyboard->Flags & RI_KEY_E0) {
            rawcode |= 0xE000;
            index |= 0x80;
        }
        code = windows_scancode_table[index];
    }

    ако (down) {
        SDL_Window *focus = SDL_GetKeyboardFocus();
        // With input sink flag we want to receive input even if not focused
        ако ((!data->raw_keyboard_flag_inputsink && !focus) || (focus && focus->text_input_active)) {
            врати;
        }
    }

    SDL_SendKeyboardKey(timestamp, keyboardID, rawcode, code, down);
}

void WIN_PollRawInput(SDL_VideoDevice *_this, Uint64 poll_start)
{
    SDL_VideoData *data = _this->internal;
    UINT size, i, count, total = 0;
    RAWINPUT *input;
    Uint64 poll_finish;

    ако (data->rawinput_offset == 0) {
        BOOL isWow64;

        data->rawinput_offset = sizeof(RAWINPUTHEADER);
        ако (IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64) {
            // We're going to get 64-bit data, so use the 64-bit RAWINPUTHEADER size
            data->rawinput_offset += 8;
        }
    }

    // Get all available events
    input = (RAWINPUT *)data->rawinput;
    за (;;) {
        size = data->rawinput_size - (UINT)((BYTE *)input - data->rawinput);
        count = GetRawInputBuffer(input, &size, sizeof(RAWINPUTHEADER));
        poll_finish = SDL_GetTicksNS();
        ако (count == 0 || count == (UINT)-1) {
            ако (!data->rawinput || (count == (UINT)-1 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
                const UINT RAWINPUT_BUFFER_SIZE_INCREMENT = 96;   // 2 64-bit raw mouse packets
                BYTE *rawinput = (BYTE *)SDL_realloc(data->rawinput, data->rawinput_size + RAWINPUT_BUFFER_SIZE_INCREMENT);
                ако (!rawinput) {
                    break;
                }
                input = (RAWINPUT *)(rawinput + ((BYTE *)input - data->rawinput));
                data->rawinput = rawinput;
                data->rawinput_size += RAWINPUT_BUFFER_SIZE_INCREMENT;
            } инако {
                break;
            }
        } инако {
            total += count;

            // Advance input to the end of the buffer
            док (count--) {
                input = NEXTRAWINPUTBLOCK(input);
            }
        }
    }

    ако (total > 0) {
        Uint64 delta = poll_finish - poll_start;
        UINT mouse_total = 0;
        за (i = 0, input = (RAWINPUT *)data->rawinput; i < total; ++i, input = NEXTRAWINPUTBLOCK(input)) {
            ако (input->header.dwType == RIM_TYPEMOUSE) {
                mouse_total += 1;
            }
        }
        цео mouse_index = 0;
        за (i = 0, input = (RAWINPUT *)data->rawinput; i < total; ++i, input = NEXTRAWINPUTBLOCK(input)) {
            ако (input->header.dwType == RIM_TYPEMOUSE) {
                mouse_index += 1; // increment first so that it starts at one
                RAWMOUSE *rawmouse = (RAWMOUSE *)((BYTE *)input + data->rawinput_offset);
                Uint64 time = poll_finish - (delta * (mouse_total - mouse_index)) / mouse_total;
                WIN_HandleRawMouseInput(time, data, input->header.hDevice, rawmouse);
            } инако ако (input->header.dwType == RIM_TYPEKEYBOARD) {
                RAWKEYBOARD *rawkeyboard = (RAWKEYBOARD *)((BYTE *)input + data->rawinput_offset);
                WIN_HandleRawKeyboardInput(poll_finish, data, input->header.hDevice, rawkeyboard);
            }
        }
    }
    data->last_rawinput_poll = poll_finish;
}

static void AddDeviceID(Uint32 deviceID, Uint32 **list, цео *count)
{
    цео new_count = (*count + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_count * sizeof(*new_list));
    ако (!new_list) {
        // Oh well, we'll drop this one
        врати;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}

static bool HasDeviceID(Uint32 deviceID, const Uint32 *list, цео count)
{
    за (цео i = 0; i < count; ++i) {
        ако (deviceID == list[i]) {
            врати true;
        }
    }
    врати false;
}

static char *GetDeviceName(HANDLE hDevice, HDEVINFO devinfo, const char *instance, Uint16 vendor, Uint16 product, const char *default_name, bool hid_loaded)
{
    char *vendor_name = NULL;
    char *product_name = NULL;
    char *name = NULL;

    // These are 126 for USB, but can be longer for Bluetooth devices
    WCHAR vend[256], prod[256];
    vend[0] = 0;
    prod[0] = 0;

    ако (hid_loaded) {
        char devName[MAX_PATH + 1];
        devName[0] = '\0';
        UINT cap = sizeof(devName) - 1;
        UINT len = GetRawInputDeviceInfoA(hDevice, RIDI_DEVICENAME, devName, &cap);
        ако (len != (UINT)-1) {
            devName[len] = '\0';

            // important: for devices with exclusive access mode as per
            // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
            // they can only be opened with a desired access of none instead of generic read.
            HANDLE hFile = CreateFileA(devName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
            ако (hFile != INVALID_HANDLE_VALUE) {
                SDL_HidD_GetManufacturerString(hFile, vend, sizeof(vend));
                SDL_HidD_GetProductString(hFile, prod, sizeof(prod));
                CloseHandle(hFile);
            }
        }
    }

    ако (vend[0]) {
        vendor_name = WIN_StringToUTF8W(vend);
    }

    ако (prod[0]) {
        product_name = WIN_StringToUTF8W(prod);
    } инако {
        SP_DEVINFO_DATA data;
        SDL_zero(data);
        data.cbSize = sizeof(data);
        за (DWORD i = 0;; ++i) {
            ако (!SetupDiEnumDeviceInfo(devinfo, i, &data)) {
                ако (GetLastError() == ERROR_NO_MORE_ITEMS) {
                    break;
                } инако {
                    continue;
                }
            }

            char DeviceInstanceId[64];
            ако (!SetupDiGetDeviceInstanceIdA(devinfo, &data, DeviceInstanceId, sizeof(DeviceInstanceId), NULL))
                continue;

            ако (SDL_strcasecmp(instance, DeviceInstanceId) == 0) {
                DWORD size = 0;
                ако (SetupDiGetDeviceRegistryPropertyW(devinfo, &data, SPDRP_DEVICEDESC, NULL, (PBYTE)prod, sizeof(prod), &size)) {
                    // Make sure the device description is null terminated
                    size /= sizeof(*prod);
                    ако (size >= SDL_arraysize(prod)) {
                        // Truncated description...
                        size = (SDL_arraysize(prod) - 1);
                    }
                    prod[size] = 0;

                    ако (vendor || product) {
                        SDL_asprintf(&product_name, "%S (0x%.4x/0x%.4x)", prod, vendor, product);
                    } инако {
                        product_name = WIN_StringToUTF8W(prod);
                    }
                }
                break;
            }
        }
    }

    ако (!product_name && (vendor || product)) {
        SDL_asprintf(&product_name, "%s (0x%.4x/0x%.4x)", default_name, vendor, product);
    }
    name = SDL_CreateDeviceName(vendor, product, vendor_name, product_name, default_name);
    SDL_free(vendor_name);
    SDL_free(product_name);

    врати name;
}

void WIN_CheckKeyboardAndMouseHotplug(bool hid_loaded)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    PRAWINPUTDEVICELIST raw_devices = NULL;
    UINT raw_device_count = 0;
    цео old_keyboard_count = 0;
    SDL_KeyboardID *old_keyboards = NULL;
    цео new_keyboard_count = 0;
    SDL_KeyboardID *new_keyboards = NULL;
    цео old_mouse_count = 0;
    SDL_MouseID *old_mice = NULL;
    цео new_mouse_count = 0;
    SDL_MouseID *new_mice = NULL;

    ако (!_this ||
        SDL_strcmp(_this->name, "windows") != 0 ||
        !_this->internal->detect_device_hotplug ||
        _this->internal->gameinput_context) {
        врати;
    }

    ако ((GetRawInputDeviceList(NULL, &raw_device_count, sizeof(RAWINPUTDEVICELIST)) == -1) || (!raw_device_count)) {
        врати; // oh well.
    }

    raw_devices = (PRAWINPUTDEVICELIST)SDL_malloc(sizeof(RAWINPUTDEVICELIST) * raw_device_count);
    ако (!raw_devices) {
        врати; // oh well.
    }

    raw_device_count = GetRawInputDeviceList(raw_devices, &raw_device_count, sizeof(RAWINPUTDEVICELIST));
    ако (raw_device_count == (UINT)-1) {
        SDL_free(raw_devices);
        raw_devices = NULL;
        врати; // oh well.
    }

    HDEVINFO devinfo = SetupDiGetClassDevsA(NULL, NULL, NULL, (DIGCF_ALLCLASSES | DIGCF_PRESENT));

    old_keyboards = SDL_GetKeyboards(&old_keyboard_count);
    old_mice = SDL_GetMice(&old_mouse_count);

    за (UINT i = 0; i < raw_device_count; i++) {
        RID_DEVICE_INFO rdi;
        char devName[MAX_PATH] = { 0 };
        UINT rdiSize = sizeof(rdi);
        UINT nameSize = SDL_arraysize(devName);
        цео vendor = 0, product = 0;
        DWORD dwType = raw_devices[i].dwType;
        char *instance, *ptr, *name;

        ако (dwType != RIM_TYPEKEYBOARD && dwType != RIM_TYPEMOUSE) {
            continue;
        }

        rdi.cbSize = sizeof(rdi);
        ако (GetRawInputDeviceInfoA(raw_devices[i].hDevice, RIDI_DEVICEINFO, &rdi, &rdiSize) == ((UINT)-1) ||
            GetRawInputDeviceInfoA(raw_devices[i].hDevice, RIDI_DEVICENAME, devName, &nameSize) == ((UINT)-1)) {
            continue;
        }

        // Extract the device instance
        instance = devName;
        док (*instance == '\\' || *instance == '?') {
            ++instance;
        }
        за (ptr = instance; *ptr; ++ptr) {
            ако (*ptr == '#') {
                *ptr = '\\';
            }
            ако (*ptr == '{') {
                ако (ptr > instance && ptr[-1] == '\\') {
                    --ptr;
                }
                break;
            }
        }
        *ptr = '\0';

        SDL_sscanf(instance, "HID\\VID_%X&PID_%X&", &vendor, &product);

        switch (dwType) {
        case RIM_TYPEKEYBOARD:
            ако (SDL_IsKeyboard((Uint16)vendor, (Uint16)product, rdi.keyboard.dwNumberOfKeysTotal)) {
                SDL_KeyboardID keyboardID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_count);
                ако (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_count)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Keyboard", hid_loaded);
                    SDL_AddKeyboard(keyboardID, name);
                    SDL_free(name);
                }
            }
            break;
        case RIM_TYPEMOUSE:
            ако (SDL_IsMouse((Uint16)vendor, (Uint16)product)) {
                SDL_MouseID mouseID = (Uint32)(uintptr_t)raw_devices[i].hDevice;
                AddDeviceID(mouseID, &new_mice, &new_mouse_count);
                ако (!HasDeviceID(mouseID, old_mice, old_mouse_count)) {
                    name = GetDeviceName(raw_devices[i].hDevice, devinfo, instance, (Uint16)vendor, (Uint16)product, "Mouse", hid_loaded);
                    SDL_AddMouse(mouseID, name);
                    SDL_free(name);
                }
            }
            break;
        default:
            break;
        }
    }

    за (цео i = old_keyboard_count; i--;) {
        ако (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_count)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    за (цео i = old_mouse_count; i--;) {
        ако (!HasDeviceID(old_mice[i], new_mice, new_mouse_count)) {
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
static bool SkipAltGrLeftControl(WPARAM wParam, LPARAM lParam)
{
    ако (wParam != VK_CONTROL) {
        врати false;
    }

    // Is this an extended key (i.e. right key)?
    ако (lParam & 0x01000000) {
        врати false;
    }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
    // want the RALT message, so we try to see if the next message
    // is a RALT message. In that case, this is a false LCTRL!
    MSG next_msg;
    DWORD msg_time = GetMessageTime();
    ако (PeekMessage(&next_msg, NULL, 0, 0, PM_NOREMOVE)) {
        ако (next_msg.message == WM_KEYDOWN ||
            next_msg.message == WM_SYSKEYDOWN) {
            ако (next_msg.wParam == VK_MENU && (next_msg.lParam & 0x01000000) && next_msg.time == msg_time) {
                // Next message is a RALT down message, which means that this is NOT a proper LCTRL message!
                врати true;
            }
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    врати false;
}

static bool DispatchModalLoopMessageHook(HWND *hwnd, UINT *msg, WPARAM *wParam, LPARAM *lParam)
{
    MSG dummy;

    SDL_zero(dummy);
    dummy.hwnd = *hwnd;
    dummy.message = *msg;
    dummy.wParam = *wParam;
    dummy.lParam = *lParam;
    ако (g_WindowsMessageHook(g_WindowsMessageHookData, &dummy)) {
        // Can't modify the hwnd, but everything else is fair game
        *msg = dummy.message;
        *wParam = dummy.wParam;
        *lParam = dummy.lParam;
        врати true;
    }
    врати false;
}

LRESULT CALLBACK WIN_WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SDL_WindowData *data;
    LRESULT returnCode = -1;

    // Get the window data for the window
    data = WIN_GetWindowDataFromHWND(hwnd);
#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ако (!data) {
        // Fallback
        data = (SDL_WindowData *)GetProp(hwnd, TEXT("SDL_WindowData"));
    }
#endif
    ако (!data) {
        врати CallWindowProc(DefWindowProc, hwnd, msg, wParam, lParam);
    }

#ifdef WMMSG_DEBUG
    {
        char message[1024];
        ако (msg > MAX_WMMSG) {
            SDL_snprintf(message, sizeof(message), "Received windows message: %p UNKNOWN (%d) -- 0x%x, 0x%x\r\n", hwnd, msg, wParam, lParam);
        } инако {
            SDL_snprintf(message, sizeof(message), "Received windows message: %p %s -- 0x%x, 0x%x\r\n", hwnd, wmtab[msg], wParam, lParam);
        }
        OutputDebugStringA(message);
    }
#endif // WMMSG_DEBUG


    ако (g_WindowsMessageHook && data->in_modal_loop) {
        // Synthesize a message for window hooks so they can modify the message if desired
        ако (!DispatchModalLoopMessageHook(&hwnd, &msg, &wParam, &lParam)) {
            врати 0;
        }
    }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ако (WIN_HandleIMEMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
        врати 0;
    }
#endif

    switch (msg) {

    case WM_SHOWWINDOW:
    {
        ако (wParam) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        } инако {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }
    } break;

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    case WM_NCACTIVATE:
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
        ако (data->window->flags & SDL_WINDOW_BORDERLESS) {
            lParam = -1; // According to MSDN, DefWindowProc will draw a title bar if lParam != -1
        }
    } break;

    case WM_NCUAHDRAWCAPTION:
    case WM_NCUAHDRAWFRAME:
    {
        /* These messages are undocumented. They are responsible for redrawing the window frame and
           caption. Notably, WM_NCUAHDRAWCAPTION is sent when calling SetWindowText on a window.
           For borderless windows, we don't want to draw a frame or caption, so we should stop
           that from happening. */
        ако (data->window->flags & SDL_WINDOW_BORDERLESS) {
            returnCode = 0;
        }
    } break;

    case WM_ACTIVATE:
    {
        // Update the focus in case we changed focus to a child window and then away from the application
        const DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, !!LOWORD(wParam), &pos);
    } break;

    case WM_MOUSEACTIVATE:
    {
        ако (SDL_WINDOW_IS_POPUP(data->window)) {
            врати MA_NOACTIVATE;
        }

        // Check parents to see if they are in relative mouse mode and focused
        SDL_Window *parent = data->window->parent;
        док (parent) {
            ако ((parent->flags & SDL_WINDOW_INPUT_FOCUS) &&
                (parent->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE)) {
                врати MA_NOACTIVATE;
            }
            parent = parent->parent;
        }
    } break;

    case WM_SETFOCUS:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        const DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, true, &pos);
    } break;

    case WM_KILLFOCUS:
    case WM_ENTERIDLE:
    {
        // Update the focus in case it's changing between top-level windows in the same application
        const DWORD msgPos = GetMessagePos();
        POINT pos = { GET_X_LPARAM(msgPos), GET_Y_LPARAM(msgPos) };
        WIN_UpdateFocus(data->window, false, &pos);
    } break;

    case WM_POINTERENTER:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        const UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ако (!data->videodata->GetPointerType) {
            break;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } инако ако (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            break;  // oh well.
        } инако ако (pointer_type != PT_PEN) {
            break;  // we only care about pens here.
        }

        void *hpointer = (void *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        const SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        ако (pen) {
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, true, true);
        } инако {
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
            SDL_AddPenDevice(WIN_GetEventTimestamp(), NULL, data->window, &info, hpointer, true);
        }
        returnCode = 0;
    } break;

    case WM_POINTERCAPTURECHANGED:
    case WM_POINTERLEAVE:
    {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        const UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ако (!data->videodata->GetPointerType) {
            break;  // Not on Windows8 or later? We shouldn't get this event, but just in case...
        } инако ако (!data->videodata->GetPointerType(pointerid, &pointer_type)) {
            break;  // oh well.
        } инако ако (pointer_type != PT_PEN) {
            break;  // we only care about pens here.
        }

        void *hpointer = (void *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        const SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        ако (pen == 0) {
            break;  // not a pen, or not a pen we already knew about.
        }

        // if this just left the _window_, we don't care. If this is no longer visible to the tablet, time to remove it!
        ако ((msg == WM_POINTERCAPTURECHANGED) || !IS_POINTER_INCONTACT_WPARAM(wParam)) {
            // technically this isn't just _proximity_ but maybe just leaving the window. Good enough. WinTab apparently has real proximity info.
            SDL_SendPenProximity(WIN_GetEventTimestamp(), pen, data->window, false, false);
        }
        returnCode = 0;
    } break;

    case WM_POINTERDOWN:
    case WM_POINTERUP:
    case WM_POINTERUPDATE: {
        // NOTE: GET_POINTERID_WPARAM(wParam) is not a tool ID! It changes for each new WM_POINTERENTER, like a finger ID on a touch display. We can't identify a specific pen through these events.
        const UINT32 pointerid = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointer_type = PT_POINTER;
        ако (!data->videodata->GetPointerType || !data->videodata->GetPointerType(pointerid, &pointer_type)) {
            break;  // oh well.
        } инако ако ((msg == WM_POINTERUPDATE) && (pointer_type == PT_MOUSE)) {
            data->last_pointer_update = lParam;
            returnCode = 0;
            break;
        } инако ако (pointer_type != PT_PEN) {
            break; // we only care about pens here.
        }

        void *hpointer = (void *)(size_t)1; // just something > 0. We're using this one ID any possible pen.
        const SDL_PenID pen = SDL_FindPenByHandle(hpointer);
        POINTER_PEN_INFO pen_info;
        ако (pen == 0) {
            break;  // not a pen, or not a pen we already knew about.
        } инако ако (!data->videodata->GetPointerPenInfo || !data->videodata->GetPointerPenInfo(pointerid, &pen_info)) {
            break;  // oh well.
        }

        const Uint64 timestamp = WIN_GetEventTimestamp();
        SDL_Window *window = data->window;

        const bool istouching = IS_POINTER_INCONTACT_WPARAM(wParam) && IS_POINTER_FIRSTBUTTON_WPARAM(wParam);

        // if lifting off, do it first, so any motion changes don't cause app issues.
        ако (!istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, false);
        }

        const POINTER_INFO *pointer_info = &pen_info.pointerInfo;
        RECT tablet_bounds, tablet_mapping;
        float fx, fy;

        // try to get a more-precise position than is stored in lParam...GetPointerDeviceRects is available starting in Windows 8.
        // we might need to cache this somewhere (and if we cache it, we will need to update it if the display changes)...for now we'll see if GetPointerDeviceRect is fast enough.
        ако (!data->videodata->GetPointerDeviceRects || !data->videodata->GetPointerDeviceRects(pointer_info->sourceDevice, &tablet_bounds, &tablet_mapping)) {
            POINT position = { (LONG) GET_X_LPARAM(lParam), (LONG) GET_Y_LPARAM(lParam) };
            ScreenToClient(data->hwnd, &position);
            fx = (float) position.x;
            fy = (float) position.y;
        } инако {
            цео ix, iy;
            SDL_GetWindowPosition(window, &ix, &iy);
            const SDL_FPoint window_pos = { (float) ix, (float) iy };

            const float facX = pointer_info->ptHimetricLocationRaw.x / (float) (tablet_bounds.right );
            const float facY = pointer_info->ptHimetricLocationRaw.y / (float) (tablet_bounds.bottom);

            const float w = tablet_mapping.right  - tablet_mapping.left;
            const float h = tablet_mapping.bottom - tablet_mapping.top;

            fx = (tablet_mapping.left + (facX * w)) - window_pos.x;
            fy = (tablet_mapping.top  + (facY * h)) - window_pos.y;
        }

        SDL_SendPenMotion(timestamp, pen, window, fx, fy);
        SDL_SendPenButton(timestamp, pen, window, 1, (pen_info.penFlags & PEN_FLAG_BARREL) != 0);
        SDL_SendPenButton(timestamp, pen, window, 2, (pen_info.penFlags & PEN_FLAG_ERASER) != 0);

        ако (pen_info.penMask & PEN_MASK_PRESSURE) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_PRESSURE, ((float) pen_info.pressure) / 1024.0f);  // pen_info.pressure is in the range 0..1024.
        }

        ако (pen_info.penMask & PEN_MASK_ROTATION) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_ROTATION, ((float) pen_info.rotation));  // it's already in the range of 0 to 359.
        }

        ако (pen_info.penMask & PEN_MASK_TILT_X) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_XTILT, ((float) pen_info.tiltX));  // it's already in the range of -90 to 90..
        }

        ако (pen_info.penMask & PEN_MASK_TILT_Y) {
            SDL_SendPenAxis(timestamp, pen, window, SDL_PEN_AXIS_YTILT, ((float) pen_info.tiltY));  // it's already in the range of -90 to 90..
        }

        // if setting down, do it last, so the pen is positioned correctly from the first contact.
        ако (istouching) {
            SDL_SendPenTouch(timestamp, pen, window, (pen_info.penFlags & PEN_FLAG_INVERTED) != 0, true);
        }

        returnCode = 0;
    } break;

    case WM_MOUSEMOVE:
    {
        SDL_Window *window = data->window;

        ако (window->flags & SDL_WINDOW_INPUT_FOCUS) {
            bool wish_clip_cursor = (
                window->flags & (SDL_WINDOW_MOUSE_RELATIVE_MODE | SDL_WINDOW_MOUSE_GRABBED) ||
                (window->mouse_rect.w > 0 && window->mouse_rect.h > 0)
            );
            ако (wish_clip_cursor) { // queue clipcursor refresh on pump finish
                data->clipcursor_queued = true;
            }
        }

        ако (!data->mouse_tracked) {
            TRACKMOUSEEVENT trackMouseEvent;

            trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
            trackMouseEvent.dwFlags = TME_LEAVE;
            trackMouseEvent.hwndTrack = data->hwnd;

            ако (TrackMouseEvent(&trackMouseEvent)) {
                data->mouse_tracked = true;
            }

            WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
        }

        ако (!data->videodata->raw_mouse_enabled) {
            // Only generate mouse events for real mouse
            ако (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                SDL_SendMouseMotion(WIN_GetEventTimestamp(), window, SDL_GLOBAL_MOUSE_ID, false, (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
            }
        }

    } break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONDBLCLK:
    {
        /* SDL_Mouse *mouse = SDL_GetMouse(); */
        ако (!data->videodata->raw_mouse_enabled) {
            ако (GetMouseMessageSource((ULONG)GetMessageExtraInfo()) == SDL_MOUSE_EVENT_SOURCE_MOUSE &&
                lParam != data->last_pointer_update) {
                WIN_CheckWParamMouseButtons(WIN_GetEventTimestamp(), wParam, data, SDL_GLOBAL_MOUSE_ID);
            }
        }
    } break;

#ако 0   // We handle raw input all at once instead of using a syscall for each mouse event
    case WM_INPUT:
    {
        HRAWINPUT hRawInput = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = sizeof(inp);

        // Relative mouse motion is delivered to the window with keyboard focus
        ако (data->window != SDL_GetKeyboardFocus()) {
            break;
        }

        GetRawInputData(hRawInput, RID_INPUT, &inp, &size, sizeof(RAWINPUTHEADER));
        ако (inp.header.dwType == RIM_TYPEMOUSE) {
            WIN_HandleRawMouseInput(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.mouse);
        } инако ако (inp.header.dwType == RIM_TYPEKEYBOARD) {
            WIN_HandleRawKeyboardInput(WIN_GetEventTimestamp(), data, inp.header.hDevice, &inp.data.keyboard);
        }
    } break;
#endif

    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
    {
        ако (!data->videodata->raw_mouse_enabled) {
            short amount = GET_WHEEL_DELTA_WPARAM(wParam);
            float fAmount = (float)amount / WHEEL_DELTA;
            ако (msg == WM_MOUSEWHEEL) {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, 0.0f, fAmount, SDL_MOUSEWHEEL_NORMAL);
            } инако {
                SDL_SendMouseWheel(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, fAmount, 0.0f, SDL_MOUSEWHEEL_NORMAL);
            }
        }
    } break;

    case WM_MOUSELEAVE:
        ако (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            ако (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode && !IsIconic(hwnd)) {
                SDL_Mouse *mouse;
                DWORD pos = GetMessagePos();
                POINT cursorPos;
                cursorPos.x = GET_X_LPARAM(pos);
                cursorPos.y = GET_Y_LPARAM(pos);
                ScreenToClient(hwnd, &cursorPos);
                mouse = SDL_GetMouse();
                ако (!mouse->was_touch_mouse_events) { // we're not a touch handler causing a mouse leave?
                    SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (float)cursorPos.x, (float)cursorPos.y);
                } инако {                                       // touch handling?
                    mouse->was_touch_mouse_events = false; // not anymore
                    ако (mouse->touch_mouse_events) {           // convert touch to mouse events
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_TOUCH_MOUSEID, false, (float)cursorPos.x, (float)cursorPos.y);
                    } инако { // normal handling
                        SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, SDL_GLOBAL_MOUSE_ID, false, (float)cursorPos.x, (float)cursorPos.y);
                    }
                }
            }

            ако (!SDL_GetMouse()->relative_mode) {
                // When WM_MOUSELEAVE is fired we can be assured that the cursor has left the window
                SDL_SetMouseFocus(NULL);
            }
        }

        // Once we get WM_MOUSELEAVE we're guaranteed that the window is no longer tracked
        data->mouse_tracked = false;

        returnCode = 0;
        break;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
        ако (SkipAltGrLeftControl(wParam, lParam)) {
            returnCode = 0;
            break;
        }

        bool virtual_key = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_key);

        // Detect relevant keyboard shortcuts
        ако (code == SDL_SCANCODE_F4 && (SDL_GetModState() & SDL_KMOD_ALT)) {
            // ALT+F4: Close window
            ако (ShouldGenerateWindowCloseOnAltF4()) {
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            }
        }

        ако (virtual_key || !data->videodata->raw_keyboard_enabled || data->window->text_input_active) {
            SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
        }
    }

        returnCode = 0;
        break;

    case WM_SYSKEYUP:
    case WM_KEYUP:
    {
        ако (SkipAltGrLeftControl(wParam, lParam)) {
            returnCode = 0;
            break;
        }

        bool virtual_key = false;
        Uint16 rawcode = 0;
        SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam, &rawcode, &virtual_key);
        const bool *keyboardState = SDL_GetKeyboardState(NULL);

        ако (virtual_key || !data->videodata->raw_keyboard_enabled || data->window->text_input_active) {
            ако (code == SDL_SCANCODE_PRINTSCREEN && !keyboardState[code]) {
                SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, true);
            }
            SDL_SendKeyboardKey(WIN_GetEventTimestamp(), SDL_GLOBAL_KEYBOARD_ID, rawcode, code, false);
        }
    }
        returnCode = 0;
        break;

    case WM_UNICHAR:
        ако (wParam == UNICODE_NOCHAR) {
            returnCode = 1;
        } инако {
            ако (SDL_TextInputActive(data->window)) {
                char text[5];
                char *end = SDL_UCS4ToUTF8((Uint32)wParam, text);
                *end = '\0';
                SDL_SendKeyboardText(text);
            }
            returnCode = 0;
        }
        break;

    case WM_CHAR:
        ако (SDL_TextInputActive(data->window)) {
            /* Characters outside Unicode Basic Multilingual Plane (BMP)
             * are coded as so called "surrogate pair" in two separate UTF-16 character events.
             * Cache high surrogate until next character event. */
            ако (IS_HIGH_SURROGATE(wParam)) {
                data->high_surrogate = (WCHAR)wParam;
            } инако {
                WCHAR utf16[3];

                utf16[0] = data->high_surrogate ? data->high_surrogate : (WCHAR)wParam;
                utf16[1] = data->high_surrogate ? (WCHAR)wParam : L'\0';
                utf16[2] = L'\0';

                char utf8[5];
                цео result = WIN_WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16, -1, utf8, sizeof(utf8), NULL, NULL);
                ако (result > 0) {
                    SDL_SendKeyboardText(utf8);
                }
                data->high_surrogate = L'\0';
            }
        } инако {
            data->high_surrogate = L'\0';
        }

        returnCode = 0;
        break;

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ifdef WM_INPUTLANGCHANGE
    case WM_INPUTLANGCHANGE:
    {
        WIN_UpdateKeymap(true);
    }
        returnCode = 1;
        break;
#endif // WM_INPUTLANGCHANGE

    case WM_NCLBUTTONDOWN:
    {
        data->in_title_click = true;

        // Fix for 500ms hang after user clicks on the title bar, but before moving mouse
        // Reference: https://gamedev.net/forums/topic/672094-keeping-things-moving-during-win32-moveresize-events/5254386/
        ако (SendMessage(hwnd, WM_NCHITTEST, wParam, lParam) == HTCAPTION) {
            POINT cursorPos;
            GetCursorPos(&cursorPos); // want the most current pos so as to not cause position change
            ScreenToClient(hwnd, &cursorPos);
            PostMessage(hwnd, WM_MOUSEMOVE, 0, cursorPos.x | (((Uint32)((Sint16)cursorPos.y)) << 16));
        }
    } break;

    case WM_CAPTURECHANGED:
    {
        data->in_title_click = false;

        // The mouse may have been released during a modal loop
        WIN_CheckAsyncMouseRelease(WIN_GetEventTimestamp(), data);
    } break;

#ifdef WM_GETMINMAXINFO
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO *info;
        RECT size;
        цео x, y;
        цео w, h;
        цео min_w, min_h;
        цео max_w, max_h;
        BOOL constrain_max_size;

        // If this is an expected size change, allow it
        ако (data->expected_resize) {
            break;
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
        ако (max_w && max_h) {
            max_w -= w;
            max_h -= h;
            constrain_max_size = TRUE;
        } инако {
            constrain_max_size = FALSE;
        }

        ако (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
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
        ако (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
            ако (SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS) {
                цео screenW = GetSystemMetrics(SM_CXSCREEN);
                цео screenH = GetSystemMetrics(SM_CYSCREEN);
                info->ptMaxSize.x = SDL_max(w, screenW);
                info->ptMaxSize.y = SDL_max(h, screenH);
                info->ptMaxPosition.x = SDL_min(0, ((screenW - w) / 2));
                info->ptMaxPosition.y = SDL_min(0, ((screenH - h) / 2));
            }
            info->ptMinTrackSize.x = (LONG)w + min_w;
            info->ptMinTrackSize.y = (LONG)h + min_h;
            ако (constrain_max_size) {
                info->ptMaxTrackSize.x = (LONG)w + max_w;
                info->ptMaxTrackSize.y = (LONG)h + max_h;
            }
        } инако {
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
        break;
#endif // WM_GETMINMAXINFO

    case WM_WINDOWPOSCHANGING:

        ако (data->expected_resize) {
            returnCode = 0;
        } инако ако (data->in_modal_loop) {
            WINDOWPOS *windowpos = (WINDOWPOS *)lParam;

            /* While in a modal loop, the size may only be updated if the window is being resized interactively.
             * Set the SWP_NOSIZE flag if the reported size hasn't changed from the last WM_WINDOWPOSCHANGING
             * event, or a size set programmatically may end up being overwritten by old size data.
             */
            ако (data->last_modal_width == windowpos->cx && data->last_modal_height == windowpos->cy) {
                windowpos->flags |= SWP_NOSIZE;
            }

            data->last_modal_width = windowpos->cx;
            data->last_modal_height = windowpos->cy;

            returnCode = 0;
        }
        break;

    case WM_WINDOWPOSCHANGED:
    {
        SDL_Window *win;
        const SDL_DisplayID original_displayID = data->window->displayID;
        const WINDOWPOS *windowpos = (WINDOWPOS *)lParam;
        bool iconic;
        bool zoomed;
        RECT rect;
        цео x, y;
        цео w, h;

        ако (windowpos->flags & SWP_SHOWWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
        }

        // These must be set after sending SDL_EVENT_WINDOW_SHOWN as that may apply pending
        // window operations that change the window state.
        iconic = IsIconic(hwnd);
        zoomed = IsZoomed(hwnd);

        ако (iconic) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        } инако ако (zoomed) {
            ако (data->window->flags & SDL_WINDOW_MINIMIZED) {
                // If going from minimized to maximized, send the restored event first.
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
            }
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
            data->force_ws_maximizebox = true;
        } инако ако (data->window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

            /* If resizable was forced on for the maximized window, clear the style flags now,
             * but not if the window is fullscreen, as this needs to be preserved in that case.
             */
            ако (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->force_ws_maximizebox = false;
                WIN_SetWindowResizable(SDL_GetVideoDevice(), data->window, !!(data->window->flags & SDL_WINDOW_RESIZABLE));
            }
        }

        ако (windowpos->flags & SWP_HIDEWINDOW) {
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
        }

        // When the window is minimized it's resized to the dock icon size, ignore this
        ако (iconic) {
            break;
        }

        ако (data->initializing) {
            break;
        }

        ако (!data->disable_move_size_events) {
            ако (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                ClientToScreen(hwnd, (LPPOINT) &rect);
                ClientToScreen(hwnd, (LPPOINT) &rect + 1);

                x = rect.left;
                y = rect.top;

                SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);
            }

            // Moving the window from one display to another can change the size of the window (in the handling of SDL_EVENT_WINDOW_MOVED), so we need to re-query the bounds
            ако (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
                w = rect.right;
                h = rect.bottom;

                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
            }
        }

        WIN_UpdateClipCursor(data->window);

        // Update the window display position
        ако (data->window->displayID != original_displayID) {
            // Display changed, check ICC profile
            WIN_UpdateWindowICCProfile(data->window, true);
        }

        // Update the position of any child windows
        за (win = data->window->first_child; win; win = win->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ако (SDL_WINDOW_IS_POPUP(win) && !(win->flags & SDL_WINDOW_HIDDEN)) {
                WIN_SetWindowPositionInternal(win, SWP_NOCOPYBITS | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
            }
        }

    } break;

    case WM_ENTERSIZEMOVE:
    case WM_ENTERMENULOOP:
    {
        ако (g_WindowsMessageHook) {
            ако (!DispatchModalLoopMessageHook(&hwnd, &msg, &wParam, &lParam)) {
                врати 0;
            }
        }

        ++data->in_modal_loop;
        ако (data->in_modal_loop == 1) {
            RECT rect;
            SDL_zero(rect);
            GetWindowRect(data->hwnd, &rect);
            data->last_modal_width = rect.right - rect.left;
            data->last_modal_height = rect.bottom - rect.top;

            data->initial_size_rect.left = data->window->x;
            data->initial_size_rect.right = data->window->x + data->window->w;
            data->initial_size_rect.top = data->window->y;
            data->initial_size_rect.bottom = data->window->y + data->window->h;

            SetTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks, USER_TIMER_MINIMUM, NULL);

            // Reset the keyboard, as we won't get any key up events during the modal loop
            SDL_ResetKeyboard();
        }
    } break;

    case WM_TIMER:
    {
        ако (wParam == (UINT_PTR)SDL_IterateMainCallbacks) {
            SDL_OnWindowLiveResizeUpdate(data->window);

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
#ако 0 // This locks up the Windows compositor when called by Steam; disabling until we understand why
            // Make sure graphics operations are complete for smooth refresh
            ако (data->videodata->DwmFlush) {
                data->videodata->DwmFlush();
            }
#endif
#endif
            врати 0;
        }
    } break;

    case WM_EXITSIZEMOVE:
    case WM_EXITMENULOOP:
    {
        --data->in_modal_loop;
        ако (data->in_modal_loop == 0) {
            KillTimer(hwnd, (UINT_PTR)SDL_IterateMainCallbacks);
        }
    } break;

    case WM_SIZING:
        {
            WPARAM edge = wParam;
            RECT* dragRect = (RECT*)lParam;
            RECT clientDragRect = *dragRect;
            bool lock_aspect_ratio = (data->window->max_aspect == data->window->min_aspect) ? true : false;
            RECT rc;
            LONG w, h;
            float new_aspect;

            // if aspect ratio constraints are not enabled then skip this message
            ако (data->window->min_aspect <= 0 && data->window->max_aspect <= 0) {
                break;
            }

            // unadjust the dragRect from the window rect to the client rect
            SetRectEmpty(&rc);
            ако (!AdjustWindowRectEx(&rc, GetWindowStyle(hwnd), GetMenu(hwnd) != NULL, GetWindowExStyle(hwnd))) {
                break;
            }

            clientDragRect.left -= rc.left;
            clientDragRect.top -= rc.top;
            clientDragRect.right -= rc.right;
            clientDragRect.bottom -= rc.bottom;

            w = clientDragRect.right - clientDragRect.left;
            h = clientDragRect.bottom - clientDragRect.top;
            new_aspect = w / (float)h;

            // handle the special case in which the min ar and max ar are the same so the window can size symmetrically
            ако (lock_aspect_ratio) {
                switch (edge) {
                case WMSZ_LEFT:
                case WMSZ_RIGHT:
                    h = (цео)SDL_roundf(w / data->window->max_aspect);
                    break;
                default:
                    // resizing via corners or top or bottom
                    w = (цео)SDL_roundf(h * data->window->max_aspect);
                    break;
                }
            } инако {
                switch (edge) {
                case WMSZ_LEFT:
                case WMSZ_RIGHT:
                    ако (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (цео)SDL_roundf(h * data->window->max_aspect);
                    } инако ако (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        w = (цео)SDL_roundf(h * data->window->min_aspect);
                    }
                    break;
                case WMSZ_TOP:
                case WMSZ_BOTTOM:
                    ако (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (цео)SDL_roundf(w / data->window->min_aspect);
                    } инако ако (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        h = (цео)SDL_roundf(w / data->window->max_aspect);
                    }
                    break;

                default:
                    // resizing via corners
                    ако (data->window->max_aspect > 0.0f && new_aspect > data->window->max_aspect) {
                        w = (цео)SDL_roundf(h * data->window->max_aspect);
                    } инако ако (data->window->min_aspect > 0.0f && new_aspect < data->window->min_aspect) {
                        h = (цео)SDL_roundf(w / data->window->min_aspect);
                    }
                    break;
                }
            }

            switch (edge) {
            case WMSZ_LEFT:
                clientDragRect.left = clientDragRect.right - w;
                ако (lock_aspect_ratio) {
                    clientDragRect.top = (data->initial_size_rect.bottom + data->initial_size_rect.top - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.top;
                break;
            case WMSZ_BOTTOMLEFT:
                clientDragRect.left = clientDragRect.right - w;
                clientDragRect.bottom = h + clientDragRect.top;
                break;
            case WMSZ_RIGHT:
                clientDragRect.right = w + clientDragRect.left;
                ако (lock_aspect_ratio) {
                    clientDragRect.top = (data->initial_size_rect.bottom + data->initial_size_rect.top - h) / 2;
                }
                clientDragRect.bottom = h + clientDragRect.top;
                break;
            case WMSZ_TOPRIGHT:
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.top = clientDragRect.bottom - h;
                break;
            case WMSZ_TOP:
                ако (lock_aspect_ratio) {
                    clientDragRect.left = (data->initial_size_rect.right + data->initial_size_rect.left - w) / 2;
                }
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.top = clientDragRect.bottom - h;
                break;
            case WMSZ_TOPLEFT:
                clientDragRect.left = clientDragRect.right - w;
                clientDragRect.top = clientDragRect.bottom - h;
                break;
            case WMSZ_BOTTOM:
                ако (lock_aspect_ratio) {
                    clientDragRect.left = (data->initial_size_rect.right + data->initial_size_rect.left - w) / 2;
                }
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.bottom = h + clientDragRect.top;
                break;
            case WMSZ_BOTTOMRIGHT:
                clientDragRect.right = w + clientDragRect.left;
                clientDragRect.bottom = h + clientDragRect.top;
                break;
            }

            // convert the client rect to a window rect
            ако (!AdjustWindowRectEx(&clientDragRect, GetWindowStyle(hwnd), GetMenu(hwnd) != NULL, GetWindowExStyle(hwnd))) {
                break;
            }

            *dragRect = clientDragRect;
        }
        break;

    case WM_SETCURSOR:
    {
        Uint16 hittest;

        hittest = LOWORD(lParam);
        ако (hittest == HTCLIENT) {
            SetCursor(SDL_cursor);
            returnCode = TRUE;
        } инако ако (!g_WindowFrameUsableWhileCursorHidden && !SDL_cursor) {
            SetCursor(NULL);
            returnCode = TRUE;
        }
    } break;

        // We were occluded, refresh our display
    case WM_PAINT:
    {
        RECT rect;
        ако (GetUpdateRect(hwnd, &rect, FALSE)) {
            const LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

            /* Composited windows will continue to receive WM_PAINT messages for update
               regions until the window is actually painted through Begin/EndPaint */
            ако (style & WS_EX_COMPOSITED) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
            }

            ValidateRect(hwnd, NULL);
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }
        returnCode = 0;
        break;

        // We'll do our own drawing, prevent flicker
    case WM_ERASEBKGND:
        ако (ShouldClearWindowOnEraseBackground(data)) {
            RECT client_rect;
            HBRUSH brush;
            data->videodata->cleared = true;
            GetClientRect(hwnd, &client_rect);
            brush = CreateSolidBrush(0);
            FillRect(GetDC(hwnd), &client_rect, brush);
            DeleteObject(brush);
        }
        врати 1;

    case WM_SYSCOMMAND:
    {
        ако (!g_WindowsEnableMenuMnemonics) {
            ако ((wParam & 0xFFF0) == SC_KEYMENU) {
                врати 0;
            }
        }

#ако defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
        // Don't start the screensaver or blank the monitor in fullscreen apps
        ако ((wParam & 0xFFF0) == SC_SCREENSAVE ||
            (wParam & 0xFFF0) == SC_MONITORPOWER) {
            ако (SDL_GetVideoDevice()->suspend_screensaver) {
                врати 0;
            }
        }
#endif // System has screensaver support
    } break;

    case WM_CLOSE:
    {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
    }
        returnCode = 0;
        break;

    case WM_TOUCH:
        ако (data->videodata->GetTouchInputInfo && data->videodata->CloseTouchInputHandle) {
            UINT i, num_inputs = LOWORD(wParam);
            bool isstack;
            PTOUCHINPUT inputs = SDL_small_alloc(TOUCHINPUT, num_inputs, &isstack);
            ако (inputs && data->videodata->GetTouchInputInfo((HTOUCHINPUT)lParam, num_inputs, inputs, sizeof(TOUCHINPUT))) {
                RECT rect;
                float x, y;

                ако (!GetClientRect(hwnd, &rect) || !WIN_WindowRectValid(&rect)) {
                    ако (inputs) {
                        SDL_small_free(inputs, isstack);
                    }
                    break;
                }
                ClientToScreen(hwnd, (LPPOINT)&rect);
                ClientToScreen(hwnd, (LPPOINT)&rect + 1);
                rect.top *= 100;
                rect.left *= 100;
                rect.bottom *= 100;
                rect.right *= 100;

                за (i = 0; i < num_inputs; ++i) {
                    PTOUCHINPUT input = &inputs[i];
                    const цео w = (rect.right - rect.left);
                    const цео h = (rect.bottom - rect.top);

                    const SDL_TouchID touchId = (SDL_TouchID)((uintptr_t)input->hSource);
                    const SDL_FingerID fingerId = (input->dwID + 1);

                    /* TODO: Can we use GetRawInputDeviceInfo and HID info to
                       determine if this is a direct or indirect touch device?
                     */
                    ако (SDL_AddTouch(touchId, SDL_TOUCH_DEVICE_DIRECT, (input->dwFlags & TOUCHEVENTF_PEN) == TOUCHEVENTF_PEN ? "pen" : "touch") < 0) {
                        continue;
                    }

                    // Get the normalized coordinates for the window
                    ако (w <= 1) {
                        x = 0.5f;
                    } инако {
                        x = (float)(input->x - rect.left) / (w - 1);
                    }
                    ако (h <= 1) {
                        y = 0.5f;
                    } инако {
                        y = (float)(input->y - rect.top) / (h - 1);
                    }

                    // FIXME: Should we use the input->dwTime field for the tick source of the timestamp?
                    ако (input->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
                    }
                    ако (input->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(WIN_GetEventTimestamp(), touchId, fingerId, data->window, x, y, 1.0f);
                    }
                    ако (input->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(WIN_GetEventTimestamp(), touchId, fingerId, data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
                    }
                }
            }
            SDL_small_free(inputs, isstack);

            data->videodata->CloseTouchInputHandle((HTOUCHINPUT)lParam);
            врати 0;
        }
        break;

#ifdef HAVE_TPCSHRD_H

    case WM_TABLET_QUERYSYSTEMGESTURESTATUS:
        /* See https://msdn.microsoft.com/en-us/library/windows/desktop/bb969148(v=vs.85).aspx .
         * If we're handling our own touches, we don't want any gestures.
         * Not all of these settings are documented.
         * The use of the undocumented ones was suggested by https://github.com/bjarkeck/GCGJ/blob/master/Monogame/Windows/WinFormsGameForm.cs . */
        врати TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_TOUCHUIFORCEON | TABLET_DISABLE_TOUCHUIFORCEOFF | TABLET_DISABLE_TOUCHSWITCH | TABLET_DISABLE_FLICKS | TABLET_DISABLE_SMOOTHSCROLLING | TABLET_DISABLE_FLICKFALLBACKKEYS; // disables press and hold (right-click) gesture
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen up (waves)
                                                                                                                                                                                                                                                                                                         // disables UI feedback on pen button down (circle)
                                                                                                                                                                                                                                                                                                         // disables pen flicks (back, forward, drag down, drag up)

#endif // HAVE_TPCSHRD_H

    case WM_DROPFILES:
    {
        UINT i;
        HDROP drop = (HDROP)wParam;
        UINT count = DragQueryFile(drop, 0xFFFFFFFF, NULL, 0);
        за (i = 0; i < count; ++i) {
            UINT size = DragQueryFile(drop, i, NULL, 0) + 1;
            LPTSTR buffer = (LPTSTR)SDL_malloc(sizeof(TCHAR) * size);
            ако (buffer) {
                ако (DragQueryFile(drop, i, buffer, size)) {
                    char *file = WIN_StringToUTF8(buffer);
                    SDL_SendDropFile(data->window, NULL, file);
                    SDL_free(file);
                }
                SDL_free(buffer);
            }
        }
        SDL_SendDropComplete(data->window);
        DragFinish(drop);
        врати 0;
    }

    case WM_DISPLAYCHANGE:
    {
        // Reacquire displays if any were added or removed
        WIN_RefreshDisplays(SDL_GetVideoDevice());
    } break;

    case WM_NCCALCSIZE:
    {
        SDL_WindowFlags window_flags = data->window->flags;
        ако (wParam == TRUE && (window_flags & SDL_WINDOW_BORDERLESS) && !(window_flags & SDL_WINDOW_FULLSCREEN)) {
            // When borderless, need to tell windows that the size of the non-client area is 0
            NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
            WINDOWPLACEMENT placement;
            ако (GetWindowPlacement(hwnd, &placement) && placement.showCmd == SW_MAXIMIZE) {
                // Maximized borderless windows should use the monitor work area.
                HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                ако (!hMonitor) {
                    // The returned monitor can be null when restoring from minimized, so use the last coordinates.
                    const POINT pt = { data->window->windowed.x, data->window->windowed.y };
                    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                }
                ако (hMonitor) {
                    MONITORINFO info;
                    SDL_zero(info);
                    info.cbSize = sizeof(info);
                    ако (GetMonitorInfo(hMonitor, &info)) {
                        params->rgrc[0] = info.rcWork;
                    }
                }
            } инако ако (!(window_flags & SDL_WINDOW_RESIZABLE) && !data->force_ws_maximizebox) {
                цео w, h;
                ако (data->window->last_size_pending) {
                    w = data->window->pending.w;
                    h = data->window->pending.h;
                } инако {
                    w = data->window->floating.w;
                    h = data->window->floating.h;
                }
                params->rgrc[0].right = params->rgrc[0].left + w;
                params->rgrc[0].bottom = params->rgrc[0].top + h;
            }
            врати 0;
        }
    } break;

    case WM_NCHITTEST:
    {
        SDL_Window *window = data->window;

        ако (window->flags & SDL_WINDOW_TOOLTIP) {
            врати HTTRANSPARENT;
        }

        ако (window->hit_test) {
            POINT winpoint;
            winpoint.x = GET_X_LPARAM(lParam);
            winpoint.y = GET_Y_LPARAM(lParam);
            ако (ScreenToClient(hwnd, &winpoint)) {
                SDL_Point point;
                SDL_HitTestResult rc;
                point.x = winpoint.x;
                point.y = winpoint.y;
                rc = window->hit_test(window, &point, window->hit_test_data);
                switch (rc) {
#define POST_HIT_TEST(ret)                                                 \
    {                                                                      \
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0); \
        врати ret;                                                        \
    }
                case SDL_HITTEST_DRAGGABLE:
                {
                    /* If the mouse button state is something other than none or left button down,
                     * return HTCLIENT, or Windows will eat the button press.
                     */
                    SDL_MouseButtonFlags buttonState = SDL_GetGlobalMouseState(NULL, NULL);
                    ако (buttonState && !(buttonState & SDL_BUTTON_LMASK)) {
                        // Set focus in case it was lost while previously moving over a draggable area.
                        SDL_SetMouseFocus(window);
                        врати HTCLIENT;
                    }

                    POST_HIT_TEST(HTCAPTION);
                }
                case SDL_HITTEST_RESIZE_TOPLEFT:
                    POST_HIT_TEST(HTTOPLEFT);
                case SDL_HITTEST_RESIZE_TOP:
                    POST_HIT_TEST(HTTOP);
                case SDL_HITTEST_RESIZE_TOPRIGHT:
                    POST_HIT_TEST(HTTOPRIGHT);
                case SDL_HITTEST_RESIZE_RIGHT:
                    POST_HIT_TEST(HTRIGHT);
                case SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                    POST_HIT_TEST(HTBOTTOMRIGHT);
                case SDL_HITTEST_RESIZE_BOTTOM:
                    POST_HIT_TEST(HTBOTTOM);
                case SDL_HITTEST_RESIZE_BOTTOMLEFT:
                    POST_HIT_TEST(HTBOTTOMLEFT);
                case SDL_HITTEST_RESIZE_LEFT:
                    POST_HIT_TEST(HTLEFT);
#undef POST_HIT_TEST
                case SDL_HITTEST_NORMAL:
                    врати HTCLIENT;
                }
            }
            // If we didn't return, this will call DefWindowProc below.
        }
    } break;

    case WM_GETDPISCALEDSIZE:
        // Windows 10 Creators Update+
        /* Documented as only being sent to windows that are per-monitor V2 DPI aware.

           Experimentation shows it's only sent during interactive dragging, not in response to
           SetWindowPos. */
        ако (data->videodata->GetDpiForWindow && data->videodata->AdjustWindowRectExForDpi) {
            /* Windows expects applications to scale their window rects linearly
               when dragging between monitors with different DPI's.
               e.g. a 100x100 window dragged to a 200% scaled monitor
               becomes 200x200.

               For SDL, we instead want the client size to scale linearly.
               This is not the same as the window rect scaling linearly,
               because Windows doesn't scale the non-client area (titlebar etc.)
               linearly. So, we need to handle this message to request custom
               scaling. */

            const цео nextDPI = (цео)wParam;
            const цео prevDPI = (цео)data->videodata->GetDpiForWindow(hwnd);
            SIZE *sizeInOut = (SIZE *)lParam;

            цео frame_w, frame_h;
            цео query_client_w_win, query_client_h_win;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: current DPI: %d potential DPI: %d input size: (%dx%d)",
                    prevDPI, nextDPI, sizeInOut->cx, sizeInOut->cy);
#endif

            // Subtract the window frame size that would have been used at prevDPI
            {
                RECT rect = { 0 };

                ако (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
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

                ако (!(data->window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(data->window)) {
                    WIN_AdjustWindowRectForHWND(hwnd, &rect, nextDPI);
                }

                // This is supposed to control the suggested rect param of WM_DPICHANGED
                sizeInOut->cx = rect.right - rect.left;
                sizeInOut->cy = rect.bottom - rect.top;
            }

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_GETDPISCALEDSIZE: output size: (%dx%d)", sizeInOut->cx, sizeInOut->cy);
#endif
            врати TRUE;
        }
        break;

    case WM_DPICHANGED:
        // Windows 8.1+
        {
            const цео newDPI = HIWORD(wParam);
            RECT *const suggestedRect = (RECT *)lParam;
            цео w, h;

#ifdef HIGHDPI_DEBUG
            SDL_Log("WM_DPICHANGED: to %d\tsuggested rect: (%d, %d), (%dx%d)", newDPI,
                    suggestedRect->left, suggestedRect->top, suggestedRect->right - suggestedRect->left, suggestedRect->bottom - suggestedRect->top);
#endif

            ако (data->expected_resize) {
                /* This DPI change is coming from an explicit SetWindowPos call within SDL.
                   Assume all call sites are calculating the DPI-aware frame correctly, so
                   we don't need to do any further adjustment. */
#ifdef HIGHDPI_DEBUG
                SDL_Log("WM_DPICHANGED: Doing nothing, assuming window is already sized correctly");
#endif
                врати 0;
            }

            // Interactive user-initiated resizing/movement
            {
                /* Calculate the new frame w/h such that
                   the client area size is maintained. */
                RECT rect = { 0 };
                rect.right = data->window->w;
                rect.bottom = data->window->h;

                ако (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
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
                         NULL,
                         suggestedRect->left,
                         suggestedRect->top,
                         w,
                         h,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
            врати 0;
        }

    case WM_SETTINGCHANGE:
        ако (wParam == 0 && lParam != 0 && SDL_wcscmp((wchar_t *)lParam, L"ImmersiveColorSet") == 0) {
            SDL_SetSystemTheme(WIN_GetSystemTheme());
            WIN_UpdateDarkModeForHWND(hwnd);
        }
        ако (wParam == SPI_SETMOUSE || wParam == SPI_SETMOUSESPEED) {
            WIN_UpdateMouseSystemScale();
        }
        ако (wParam == SPI_SETWORKAREA) {
            WIN_UpdateDisplayUsableBounds(SDL_GetVideoDevice());
        }
        break;
#инако
    // Xbox does not support WM_WINDOWPOSCHANGED, so use WM_SIZE instead to detect window resizes
    case WM_SIZE:
    {
        RECT rect;
        цео w, h;

        ако (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            w = rect.right;
            h = rect.bottom;
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, w, h);
        }
    } break;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    default:
        break;
    }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ако (msg && msg == data->videodata->WM_TASKBAR_BUTTON_CREATED) {
        data->taskbar_button_created = true;
        WIN_ApplyWindowProgress(SDL_GetVideoDevice(), data->window);
    }
#endif

    // If there's a window proc, assume it's going to handle messages
    ако (data->wndproc) {
        врати CallWindowProc(data->wndproc, hwnd, msg, wParam, lParam);
    } инако ако (returnCode >= 0) {
        врати returnCode;
    } инако {
        врати CallWindowProc(DefWindowProc, hwnd, msg, wParam, lParam);
    }
}

цео WIN_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    ако (g_WindowsEnableMessageLoop) {
#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        DWORD timeout, ret;
        timeout = timeoutNS < 0 ? INFINITE : (DWORD)SDL_NS_TO_MS(timeoutNS);
        ret = MsgWaitForMultipleObjects(0, NULL, FALSE, timeout, QS_ALLINPUT);
        ако (ret == WAIT_OBJECT_0) {
            врати 1;
        } инако {
            врати 0;
        }
#инако
        // MsgWaitForMultipleObjects is desktop-only.
        MSG msg;
        BOOL message_result;
        UINT_PTR timer_id = 0;
        ако (timeoutNS > 0) {
            timer_id = SetTimer(NULL, 0, (UINT)SDL_NS_TO_MS(timeoutNS), NULL);
            message_result = GetMessage(&msg, 0, 0, 0);
            KillTimer(NULL, timer_id);
        } инако ако (timeoutNS == 0) {
            message_result = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        } инако {
            message_result = GetMessage(&msg, 0, 0, 0);
        }
        ако (message_result) {
            ако (msg.message == WM_TIMER && !msg.hwnd && msg.wParam == timer_id) {
                врати 0;
            }
            ако (g_WindowsMessageHook) {
                ако (!g_WindowsMessageHook(g_WindowsMessageHookData, &msg)) {
                    врати 1;
                }
            }
            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            врати 1;
        } инако {
            врати 0;
        }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    } инако {
        // Fail the wait so the caller falls back to polling
        врати -1;
    }
}

void WIN_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    PostMessage(data->hwnd, data->videodata->_SDL_WAKEUP, 0, 0);
}

// Simplified event pump for using when creating and destroying windows
void WIN_PumpEventsForHWND(SDL_VideoDevice *_this, HWND hwnd)
{
    MSG msg;

    ако (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        док (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            WIN_SetMessageTick(msg.time);

            // Always translate the message in case it's a non-SDL window (e.g. with Qt integration)
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        SDL_processing_messages = false;
    }
}

void WIN_PumpEvents(SDL_VideoDevice *_this)
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
    цео new_messages = 0;

    ако (_this->internal->gameinput_context) {
        WIN_UpdateGameInput(_this);
    }

    ако (g_WindowsEnableMessageLoop) {
        SDL_processing_messages = true;

        док (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            ако (g_WindowsMessageHook) {
                ако (!g_WindowsMessageHook(g_WindowsMessageHookData, &msg)) {
                    continue;
                }
            }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
            // Don't dispatch any mouse motion queued prior to or including the last mouse warp
            ако (msg.message == WM_MOUSEMOVE && SDL_last_warp_time) {
                ако (!SDL_TICKS_PASSED(msg.time, (SDL_last_warp_time + 1))) {
                    continue;
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
            ако (SDL_TICKS_PASSED(msg.time, end_ticks)) {
                /* We might get a few new messages generated by the Steam overlay or other application hooks
                   In this case those messages will be processed before any pending input, so we want to continue after those messages.
                   (thanks to Peter Deayton for his investigation here)
                 */
                const цео MAX_NEW_MESSAGES = 3;
                ++new_messages;
                ако (new_messages > MAX_NEW_MESSAGES) {
                    break;
                }
            }
        }

        SDL_processing_messages = false;
    }

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* Windows loses a shift KEYUP event when you have both pressed at once and let go of one.
       You won't get a KEYUP until both are released, and that keyup will only be for the second
       key you released. Take heroic measures and check the keystate as of the last handled event,
       and if we think a key is pressed when Windows doesn't, unstick it in SDL's state. */
    const bool *keystate = SDL_GetKeyboardState(NULL);
    ако (keystate[SDL_SCANCODE_LSHIFT] && !(GetKeyState(VK_LSHIFT) & 0x8000)) {
        SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LSHIFT, false);
    }
    ако (keystate[SDL_SCANCODE_RSHIFT] && !(GetKeyState(VK_RSHIFT) & 0x8000)) {
        SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RSHIFT, false);
    }

    /* The Windows key state gets lost when using Windows+Space or Windows+G shortcuts and
       not grabbing the keyboard. Note: If we *are* grabbing the keyboard, GetKeyState()
       will return inaccurate results for VK_LWIN and VK_RWIN but we don't need it anyway. */
    SDL_Window *focusWindow = SDL_GetKeyboardFocus();
    ако (!focusWindow || !(focusWindow->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ако (keystate[SDL_SCANCODE_LGUI] && !(GetKeyState(VK_LWIN) & 0x8000)) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_LGUI, false);
        }
        ако (keystate[SDL_SCANCODE_RGUI] && !(GetKeyState(VK_RWIN) & 0x8000)) {
            SDL_SendKeyboardKey(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_RGUI, false);
        }
    }

    // fire queued clipcursor refreshes
    ако (_this) {
        SDL_Window *window = _this->windows;
        док (window) {
            bool refresh_clipcursor = false;
            SDL_WindowData *data = window->internal;
            ако (data) {
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
            ако (refresh_clipcursor) {
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
    ако (focusWindow && (focusWindow->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_WindowData *data = focusWindow->internal;

        ако (!data->mouse_tracked) {
            POINT cursorPos;

            ако (GetCursorPos(&cursorPos) && ScreenToClient(data->hwnd, &cursorPos)) {
                bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;
                SDL_MouseID mouseID = SDL_GLOBAL_MOUSE_ID;

                SDL_SendMouseMotion(WIN_GetEventTimestamp(), data->window, mouseID, false, (float)cursorPos.x, (float)cursorPos.y);
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

static цео app_registered = 0;
LPTSTR SDL_Appname = NULL;
Uint32 SDL_Appstyle = 0;
HINSTANCE SDL_Instance = NULL;

static void WIN_CleanRegisterApp(WNDCLASSEX wcex)
{
#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ако (wcex.hIcon) {
        DestroyIcon(wcex.hIcon);
    }
    ако (wcex.hIconSm) {
        DestroyIcon(wcex.hIconSm);
    }
#endif
    SDL_free(SDL_Appname);
    SDL_Appname = NULL;
}

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
static BOOL CALLBACK WIN_ResourceNameCallback(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG_PTR lParam)
{
    WNDCLASSEX *wcex = (WNDCLASSEX *)lParam;

    (void)lpType; // We already know that the resource type is RT_GROUP_ICON.

    /* We leave hIconSm as NULL as it will allow Windows to automatically
       choose the appropriate small icon size to suit the current DPI. */
    wcex->hIcon = LoadIcon(hModule, lpName);

    // Do not bother enumerating any more.
    врати FALSE;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

// Register the class for this application
bool SDL_RegisterApp(const char *name, Uint32 style, void *hInst)
{
    WNDCLASSEX wcex;
#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    const char *hint;
#endif

    // Only do this once...
    ако (app_registered) {
        ++app_registered;
        врати true;
    }
    SDL_assert(!SDL_Appname);
    ако (!name) {
        name = "SDL_app";
#ако defined(CS_BYTEALIGNCLIENT) || defined(CS_OWNDC)
        style = (CS_BYTEALIGNCLIENT | CS_OWNDC);
#endif
    }
    SDL_Appname = WIN_UTF8ToString(name);
    SDL_Appstyle = style;
    SDL_Instance = hInst ? (HINSTANCE)hInst : GetModuleHandle(NULL);

    // Register the application class
    SDL_zero(wcex);
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpszClassName = SDL_Appname;
    wcex.style = SDL_Appstyle;
    wcex.lpfnWndProc = WIN_WindowProc;
    wcex.hInstance = SDL_Instance;

#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON);
    ако (hint && *hint) {
        wcex.hIcon = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));

        hint = SDL_GetHint(SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL);
        ако (hint && *hint) {
            wcex.hIconSm = LoadIcon(SDL_Instance, MAKEINTRESOURCE(SDL_atoi(hint)));
        }
    } инако {
        // Use the first icon as a default icon, like in the Explorer.
        EnumResourceNames(SDL_Instance, RT_GROUP_ICON, WIN_ResourceNameCallback, (LONG_PTR)&wcex);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ако (!RegisterClassEx(&wcex)) {
        WIN_CleanRegisterApp(wcex);
        врати SDL_SetError("Couldn't register application class");
    }

    app_registered = 1;
    врати true;
}

// Unregisters the windowclass registered in SDL_RegisterApp above.
void SDL_UnregisterApp(void)
{
    WNDCLASSEX wcex;

    // SDL_RegisterApp might not have been called before
    ако (!app_registered) {
        врати;
    }
    --app_registered;
    ако (app_registered == 0) {
        // Ensure the icons are initialized.
        wcex.hIcon = NULL;
        wcex.hIconSm = NULL;
        // Check for any registered window classes.
#ако !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ако (GetClassInfoEx(SDL_Instance, SDL_Appname, &wcex)) {
            UnregisterClass(SDL_Appname, SDL_Instance);
        }
#endif
        WIN_CleanRegisterApp(wcex);
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
