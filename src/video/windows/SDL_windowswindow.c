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

#include "../../core/windows/SDL_windows.h"

#include "../../SDL_hints_c.h"
#include "../../events/SDL_dropevents_c.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_windowevents_c.h"
#include "../SDL_pixels_c.h"
#include "../SDL_sysvideo.h"

#include "SDL_windowsvideo.h"
#include "SDL_windowskeyboard.h"
#include "SDL_windowswindow.h"

// Dropfile support
#include <shellapi.h>

#ᬬᬾᬦ᭄ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#include <shobjidl.h>
#endif

// Windows CE compatibility
#ifndef SWP_NOCOPYBITS
#define SWP_NOCOPYBITS 0
#endif

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#ifndef WM_POPUPSYSTEMMENU
#define WM_POPUPSYSTEMMENU 0x313
#endif

// #define HIGHDPI_DEBUG

/* For borderless Windows, still want the following flag:
   - WS_MINIMIZEBOX: window will respond to Windows minimize commands sent to all windows, such as windows key + m, shaking title bar, etc.
   Additionally, non-fullscreen windows can add:
   - WS_CAPTION: this seems to enable the Windows minimize animation
   - WS_SYSMENU: enables system context menu on task bar
   This will also cause the task bar to overlap the window and other windowed behaviors, so only use this for windows that shouldn't appear to be fullscreen
   - WS_THICKFRAME: allows hit-testing to resize window (doesn't actually add a frame to a borderless window).
   - WS_MAXIMIZEBOX: window will respond to Windows maximize commands sent to all windows, and the window will fill the usable desktop area rather than the whole screen
 */

#define STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#define STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#define STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#define STYLE_NORMAL              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#define STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define STYLE_MASK                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_NORMAL | STYLE_RESIZABLE)

static DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ᬬᬾᬦ᭄ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ᬮᬶᬬ {
                style |= STYLE_BORDERLESS;
            }
        } ᬮᬶᬬ {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ᬬᬾᬦ᭄ (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ᬯᬮᬶ style;
}

static DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ᬯᬮᬶ style;
}

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
static ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    const SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    ᬬᬾᬦ᭄ (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, NULL, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        ᬬᬾᬦ᭄ (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            ᬯᬮᬶ NULL;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ᬬᬾᬦ᭄ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = NULL;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            ᬯᬮᬶ NULL;
        }
    }
    ᬯᬮᬶ data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
static bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, puur_naa_nka *x, puur_naa_nka *y, puur_naa_nka *width, puur_naa_nka *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : NULL;
    RECT rect;

    // Client rect, in points
    switch (rect_type) {
    pak_sa SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        bha_nga;
    pak_sa SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        bha_nga;
    pak_sa SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        bha_nga;
    pak_sa SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        bha_nga;
    default:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        bha_nga;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.left = 0;
    rect.top = 0;
    rect.right = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#ᬮᬶᬬ
        ᬬᬾᬦ᭄ (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ᬬᬾᬦ᭄ (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ᬬᬾᬦ᭄ (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    ᬯᬮᬶ WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } ᬮᬶᬬ {
            ᬬᬾᬦ᭄ (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                ᬯᬮᬶ WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.left;
    *y += rect.top;
    *width = (rect.right - rect.left);
    *height = (rect.bottom - rect.top);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    ᬯᬮᬶ true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, puur_naa_nka *x, puur_naa_nka *y, puur_naa_nka *width, puur_naa_nka *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ᬮᬶᬬ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != NULL);
#endif
    ᬯᬮᬶ WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : NULL;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ᬮᬶᬬ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != NULL);
#endif

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#ᬮᬶᬬ
    ᬬᬾᬦ᭄ (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ᬬᬾᬦ᭄ (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ᬬᬾᬦ᭄ (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            ᬯᬮᬶ WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            ᬯᬮᬶ WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    ᬯᬮᬶ true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND top;
    puur_naa_nka x, y;
    puur_naa_nka w, h;
    bool result = true;

    // Figure out what the window area will be
    ᬬᬾᬦ᭄ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_TOP)) {
        top = HWND_TOPMOST;
    } ᬮᬶᬬ {
        top = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    ᬬᬾᬦ᭄ (SetWindowPos(hwnd, top, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    for (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        ᬬᬾᬦ᭄ (!child_window->internal) {
            // This child window is not yet fully initialized.
            continue;
        }
        ᬬᬾᬦ᭄ (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    ᬯᬮᬶ result;
}

static SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(void)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    ᬬᬾᬦ᭄ (!hint)
        ᬯᬮᬶ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ᬬᬾᬦ᭄ (SDL_strstr(hint, "never"))
        ᬯᬮᬶ SDL_ERASEBACKGROUNDMODE_NEVER;

    ᬬᬾᬦ᭄ (SDL_strstr(hint, "initial"))
        ᬯᬮᬶ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ᬬᬾᬦ᭄ (SDL_strstr(hint, "always"))
        ᬯᬮᬶ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    puur_naa_nka mode = SDL_GetStringInteger(hint, 1);
    ᬬᬾᬦ᭄ (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ᬯᬮᬶ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ᬯᬮᬶ (SDL_WindowEraseBackgroundMode)mode;
}

static bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, parimaa_na(*data));
    ᬬᬾᬦ᭄ (!data) {
        ᬯᬮᬶ false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#ᬮᬶᬬ
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.left   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.top    = 0;
    data->cursor_ctrlock_rect.right  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    ᬬᬾᬦ᭄ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } ᬮᬶᬬ {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ᬬᬾᬦ᭄ (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        ᬯᬮᬶ WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        ᬬᬾᬦ᭄ (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#ᬮᬶᬬ
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        ᬬᬾᬦ᭄ (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } ᬮᬶᬬ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        ᬬᬾᬦ᭄ (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } ᬮᬶᬬ {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        ᬬᬾᬦ᭄ (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } ᬮᬶᬬ {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        ᬬᬾᬦ᭄ (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        ᬬᬾᬦ᭄ (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } ᬮᬶᬬ
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        ᬬᬾᬦ᭄ (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } ᬮᬶᬬ
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        ᬬᬾᬦ᭄ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            puur_naa_nka w = rect.right;
            puur_naa_nka h = rect.bottom;

            ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } ᬮᬶᬬ ᬬᬾᬦ᭄ ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                puur_naa_nka x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, NULL, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } ᬮᬶᬬ {
                window->w = w;
                window->h = h;
            }
        }
    }
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        ᬬᬾᬦ᭄ (ClientToScreen(hwnd, &point)) {
            ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_INPUT_FOCUS;
    SDL_SetKeyboardFocus(window);
#ᬮᬶᬬ
    ᬬᬾᬦ᭄ (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_INPUT_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_ALWAYS_ON_TOP) {
        WIN_SetWindowAlwaysOnTop(_this, window, true);
    } ᬮᬶᬬ {
        WIN_SetWindowAlwaysOnTop(_this, window, false);
    }

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ᬬᬾᬦ᭄ (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    ᬬᬾᬦ᭄ (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        puur_naa_nka titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ᬬᬾᬦ᭄ (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } ᬮᬶᬬ {
            titleLen = 0;
        }
        ᬬᬾᬦ᭄ (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        ᬬᬾᬦ᭄ (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    ᬯᬮᬶ true;
}

static void CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ᬬᬾᬦ᭄ (data) {
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ᬬᬾᬦ᭄ (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        ᬬᬾᬦ᭄ (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        ᬬᬾᬦ᭄ (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            ᬬᬾᬦ᭄ (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } ᬮᬶᬬ {
            // Restore any original event handler...
            ᬬᬾᬦ᭄ (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#ᬮᬶᬬ
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = NULL;
}

static void WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        puur_naa_nka abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        puur_naa_nka abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        const puur_naa_nka width = window->last_size_pending ? window->pending.w : window->floating.w;
        const puur_naa_nka height = window->last_size_pending ? window->pending.h : window->floating.h;
        puur_naa_nka offset_x = 0, offset_y = 0;

        ᬬᬾᬦ᭄ (window->constrain_popup) {
            // Calculate the total offset from the parents
            for (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
                offset_x += w->x;
                offset_y += w->y;
            }

            offset_x += w->x;
            offset_y += w->y;
            abs_x += offset_x;
            abs_y += offset_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_GetDisplayForWindow(w);
            SDL_GetDisplayBounds(displayID, &rect);
            ᬬᬾᬦ᭄ (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            ᬬᬾᬦ᭄ (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ᬬᬾᬦ᭄ (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } ᬮᬶᬬ {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

static void WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    ᬲᭂᬤᭂᬮ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    ᬬᬾᬦ᭄ (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", NULL));
    HWND parent = NULL;
    ᬬᬾᬦ᭄ (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        ᬬᬾᬦ᭄ (!SetupWindowData(_this, window, hwnd, parent)) {
            ᬯᬮᬶ false;
        }
    } ᬮᬶᬬ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        puur_naa_nka x, y;
        puur_naa_nka w, h;

        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, NULL, NULL, SDL_Instance, NULL);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_GetNumberProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_NUMBER, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, NULL, SDL_Instance, NULL);
        ᬬᬾᬦ᭄ (!hwnd) {
            ᬯᬮᬶ WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ᬬᬾᬦ᭄ (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            ᬬᬾᬦ᭄ (parent) {
                DestroyWindow(parent);
            }
            ᬯᬮᬶ false;
        }

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_StopTextInput(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_TRANSPARENT) {
        ᬬᬾᬦ᭄ (videodata->DwmEnableBlurBehindWindow) {
            /* The region indicates which part of the window will be blurred and rest will be transparent. This
               is because the alpha value of the window will be used for non-blurred areas
               We can use (-1, -1, 0, 0) boundary to make sure no pixels are being blurred
            */
            HRGN rgn = CreateRectRgn(-1, -1, 0, 0);
            DWM_BLURBEHIND bb;
            bb.flags = (DWM_BB_ENABLE | DWM_BB_BLURREGION);
            bb.enable = TRUE;
            bb.blur_region = rgn;
            bb.transition_on_maxed = FALSE;
            videodata->DwmEnableBlurBehindWindow(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, NULL);
    ᬬᬾᬦ᭄ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        puur_naa_nka pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, parimaa_na(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ᬬᬾᬦ᭄ (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            ᬯᬮᬶ WIN_SetError("SetPixelFormat()");
        }
    } ᬮᬶᬬ {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ᬯᬮᬶ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        ᬬᬾᬦ᭄ ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            ᬬᬾᬦ᭄ (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                ᬯᬮᬶ false;
            }
            ᬯᬮᬶ true;
#ᬮᬶᬬ
            ᬯᬮᬶ SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        ᬬᬾᬦ᭄ (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            ᬯᬮᬶ false;
        }
#ᬮᬶᬬ
        ᬯᬮᬶ SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ᬯᬮᬶ true;
}

void WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = NULL;
    BYTE *icon_bmp;
    puur_naa_nka icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, parimaa_na(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = parimaa_na(BITMAPINFOHEADER) + icon->h * icon->w * parimaa_na(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ᬬᬾᬦ᭄ (!icon_bmp) {
        ᬯᬮᬶ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(parimaa_na(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->biBitCount = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * parimaa_na(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[parimaa_na(BITMAPINFOHEADER)];
    row_len = icon->w * parimaa_na(Uint32);
    y = icon->h;
    ᬲᭂᬤᭂᬮ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ᬬᬾᬦ᭄ (!hicon) {
        ᬯᬮᬶ SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned puur_naa_nka)GetLastError());
    }

    ᬬᬾᬦ᭄ (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ᬯᬮᬶ result;
#ᬮᬶᬬ
    ᬯᬮᬶ SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ᬬᬾᬦ᭄ (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            ᬯᬮᬶ WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ᬯᬮᬶ true;
}

void WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    ᬬᬾᬦ᭄ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ᬮᬶᬬ {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka *top, puur_naa_nka *left, puur_naa_nka *bottom, puur_naa_nka *right)
{
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *top = rcClient.top;
    *left = rcClient.left;
    *bottom = rcClient.bottom;
    *right = rcClient.right;

    ᬯᬮᬶ true;
#ᬮᬶᬬ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ᬬᬾᬦ᭄ (!GetClientRect(hwnd, &rcClient)) {
        ᬯᬮᬶ SDL_SetError("GetClientRect() failed, error %08X", (unsigned puur_naa_nka)GetLastError());
    }

    ᬬᬾᬦ᭄ (!GetWindowRect(hwnd, &rcWindow)) {
        ᬯᬮᬶ SDL_SetError("GetWindowRect() failed, error %08X", (unsigned puur_naa_nka)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.top;
    ptDiff.x = rcWindow.left;

    ᬬᬾᬦ᭄ (!ScreenToClient(hwnd, &ptDiff)) {
        ᬯᬮᬶ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned puur_naa_nka)GetLastError());
    }

    rcWindow.top = ptDiff.y;
    rcWindow.left = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.right;

    ᬬᬾᬦ᭄ (!ScreenToClient(hwnd, &ptDiff)) {
        ᬯᬮᬶ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned puur_naa_nka)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.right = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *top = rcClient.top - rcWindow.top;
    *left = rcClient.left - rcWindow.left;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *right = rcWindow.right - rcClient.right;

    ᬯᬮᬶ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

void WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka *w, puur_naa_nka *h)
{
    const SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    ᬬᬾᬦ᭄ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.right;
        *h = rect.bottom;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } ᬮᬶᬬ {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

void WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ᬬᬾᬦ᭄ (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    ᬬᬾᬦ᭄ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    ᬬᬾᬦ᭄ (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } ᬮᬶᬬ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

void WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        const bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

void WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* If desired, raise the window more forcefully.
     * Technique taken from http://stackoverflow.com/questions/916259/ .
     * Specifically, http://stackoverflow.com/a/34414846 .
     *
     * The issue is that Microsoft has gone through a lot of trouble to make it
     * nearly impossible to programmatically move a window to the foreground,
     * for "security" reasons. Apparently, the following song-and-dance gets
     * around their objections. */
    bool bForce = SDL_GetHintBoolean(SDL_HINT_FORCE_RAISEWINDOW, false);
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = NULL;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ᬬᬾᬦ᭄ (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, NULL);
        ShowWindow(hwnd, SW_RESTORE);
        AttachThreadInput(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ᬬᬾᬦ᭄ (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_TOP)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ᬬᬾᬦ᭄ (bActivate) {
        SetForegroundWindow(hwnd);
        ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } ᬮᬶᬬ {
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ᬬᬾᬦ᭄ (bForce) {
        AttachThreadInput(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

void WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ᬬᬾᬦ᭄ (window->max_w || window->max_h) {
            puur_naa_nka fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_TOP, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } ᬮᬶᬬ {
        data->windowed_mode_was_maximized = true;
    }
}

void WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

void WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    data->in_border_change = true;
    SetWindowLong(hwnd, GWL_STYLE, style);
    WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    data->in_border_change = false;
}

void WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

void WIN_SetWindowAlwaysOnTop(SDL_VideoDevice *_this, SDL_Window *window, bool on_top)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

void WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ᬬᬾᬦ᭄ (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } ᬮᬶᬬ {
        data->windowed_mode_was_maximized = false;
    }
}

static void WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ᬬᬾᬦ᭄ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, parimaa_na(cornerPref));
    }
#endif
}

static void WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ᬬᬾᬦ᭄ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, parimaa_na(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : NULL;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND top;
    puur_naa_nka x, y;
    puur_naa_nka w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (puur_naa_nka)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ᬯᬮᬶ SDL_FULLSCREEN_SUCCEEDED;
    }

    ᬬᬾᬦ᭄ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_TOP)) {
        top = HWND_TOPMOST;
    } ᬮᬶᬬ {
        top = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = parimaa_na(MONITORINFO);
    ᬬᬾᬦ᭄ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        ᬯᬮᬶ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    ᬬᬾᬦ᭄ (fullscreen) {
        x = minfo.rcMonitor.left;
        y = minfo.rcMonitor.top;
        w = minfo.rcMonitor.right - minfo.rcMonitor.left;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.top;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ᬬᬾᬦ᭄ (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ᬮᬶᬬ {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ᬬᬾᬦ᭄ (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != NULL);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        data->windowed_mode_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        ᬬᬾᬦ᭄ (enterMaximized) {
            const SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            const SDL_Point floating_point = { window->floating.x, window->floating.y };
            const SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            const SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            ᬬᬾᬦ᭄ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ᬬᬾᬦ᭄ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ᬮᬶᬬ {
                    x = bounds.x;
                }
                ᬬᬾᬦ᭄ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ᬮᬶᬬ {
                    y = bounds.y;
                }
            }
        }
    }

    /* Always reset the window to the base floating size before possibly re-applying the maximized state,
     * otherwise, the base floating size can seemingly be lost in some cases.
     */
    SetWindowLong(hwnd, GWL_STYLE, style);
    data->expected_resize = true;
    SetWindowPos(hwnd, top, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    ᬬᬾᬦ᭄ (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    ᬬᬾᬦ᭄ (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (puur_naa_nka)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ᬯᬮᬶ SDL_FULLSCREEN_SUCCEEDED;
}

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
void WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    ᬬᬾᬦ᭄ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, NULL, NULL, NULL);
        ᬬᬾᬦ᭄ (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            ᬬᬾᬦ᭄ (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                ᬬᬾᬦ᭄ (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    ᬬᬾᬦ᭄ (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

void *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    var_na *filename_utf8;
    void *iccProfileData = NULL;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    ᬬᬾᬦ᭄ (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        ᬬᬾᬦ᭄ (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ᬯᬮᬶ iccProfileData;
}

static void WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    ᬬᬾᬦ᭄ (data->keyboard_hook) {
        ᬯᬮᬶ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ᬬᬾᬦ᭄ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ᬯᬮᬶ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ᬬᬾᬦ᭄ (!GetKeyboardState(data->videodata->pre_hook_key_state)) {
        ᬯᬮᬶ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

void WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ᬬᬾᬦ᭄ (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = NULL;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    ᬯᬮᬶ true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    ᬯᬮᬶ true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    ᬬᬾᬦ᭄ (grabbed) {
        WIN_GrabKeyboard(window);
    } ᬮᬶᬬ {
        WIN_UngrabKeyboard(window);
    }

    ᬯᬮᬶ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

void WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
void WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ᬬᬾᬦ᭄ (!data || !data->hwnd) {
        // The window wasn't fully initialized
        ᬯᬮᬶ;
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_ALWAYS_ON_TOP) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

static BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ᬯᬮᬶ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

void WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    ᬬᬾᬦ᭄ (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, parimaa_na(rect)) == 0) {
        ClipCursor(NULL);
        SDL_zero(data->cursor_clipped_rect);
    }
}

void WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    ᬬᬾᬦ᭄ (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        ᬯᬮᬶ;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_INPUT_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ᬬᬾᬦ᭄ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ᬬᬾᬦ᭄ (!GetClipCursor(&current)) {
            ᬯᬮᬶ;
        }
        ᬬᬾᬦ᭄ (videodevice && (
            current.left != videodevice->desktop_bounds.x ||
            current.top  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.left;
            first.y  = current.top;
            second.x = current.right  - 1;
            second.y = current.bottom - 1;
            ᬬᬾᬦ᭄ (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                ᬯᬮᬶ;
            }
        }
        ClipCursor(NULL);
        SDL_zero(data->cursor_clipped_rect);
        ᬯᬮᬶ;
    }

    // if (!win_have_focus || !cursor_confine) {
    //     RECT current;
    //     SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    //     if (GetClipCursor(&current) && (!videodevice ||
    //         current.left   != videodevice->desktop_bounds.x ||
    //         current.top    != videodevice->desktop_bounds.y ||
    //         current.right  != videodevice->desktop_bounds.x + videodevice->desktop_bounds.w ||
    //         current.bottom != videodevice->desktop_bounds.y + videodevice->desktop_bounds.h )) {
    //         ClipCursor(NULL);
    //         SDL_zero(data->cursor_clipped_rect);
    //     }
    //     return;
    // }

    SDL_Mouse *mouse = SDL_GetMouse();
    bool lock_to_ctr = (mouse->relative_mode && mouse->relative_mode_center);

    RECT client;
    ᬬᬾᬦ᭄ (!GetClientScreenRect(data->hwnd, &client)) {
        ᬯᬮᬶ;
    }

    RECT target = client;
    ᬬᬾᬦ᭄ (lock_to_ctr) {
        LONG cx = (client.left + client.right ) / 2;
        LONG cy = (client.top  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.left   += cx;
        target.right  += cx;
        target.top    += cy;
        target.bottom += cy;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (win_mouse_rect) {
        RECT custom, overlap;
        custom.left   = client.left + mouse_rect.x;
        custom.top    = client.top  + mouse_rect.y;
        custom.right  = client.left + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.top  + mouse_rect.y + mouse_rect.h;
        ᬬᬾᬦ᭄ (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            ᬯᬮᬶ;
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ᬬᬾᬦ᭄ (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            ᬬᬾᬦ᭄ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ᬬᬾᬦ᭄ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    const float scale = (float)hdpi_uint / (float)USER_DEFAULT_SCREEN_DPI;
                    ᬬᬾᬦ᭄ (scale != SDL_floorf(scale)) {
                        ᬬᬾᬦ᭄ (target.left < target.right) {
                            target.left += 1;
                        }
                        ᬬᬾᬦ᭄ (target.right > target.left) {
                            target.right -= 1;
                        }
                        ᬬᬾᬦ᭄ (target.top < target.bottom) {
                            target.top += 1;
                        }
                        ᬬᬾᬦ᭄ (target.bottom > target.top) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ᬬᬾᬦ᭄ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, parimaa_na(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    ᬯᬮᬶ true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, float opacity)
{
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ᬯᬮᬶ false;
#ᬮᬶᬬ
    const SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    const LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    ᬬᬾᬦ᭄ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ᬬᬾᬦ᭄ (style & WS_EX_LAYERED) {
            ᬬᬾᬦ᭄ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ᬯᬮᬶ WIN_SetError("SetWindowLong()");
            }
        }
    } ᬮᬶᬬ {
        const BYTE alpha = (BYTE)((puur_naa_nka)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ᬬᬾᬦ᭄ (!(style & WS_EX_LAYERED)) {
            ᬬᬾᬦ᭄ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ᬯᬮᬶ WIN_SetError("SetWindowLong()");
            }
        }

        ᬬᬾᬦ᭄ (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ᬯᬮᬶ WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    ᬯᬮᬶ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

static const var_na *SDLGetClipboardFormatName(UINT cf, var_na *text, puur_naa_nka len)
{
    switch (cf) {
    pak_sa CF_TEXT:
        ᬯᬮᬶ "CF_TEXT";
    pak_sa CF_BITMAP:
        ᬯᬮᬶ "CF_BITMAP";
    pak_sa CF_METAFILEPICT:
        ᬯᬮᬶ "CF_METAFILEPICT";
    pak_sa CF_SYLK:
        ᬯᬮᬶ "CF_SYLK";
    pak_sa CF_DIF:
        ᬯᬮᬶ "CF_DIF";
    pak_sa CF_TIFF:
        ᬯᬮᬶ "CF_TIFF";
    pak_sa CF_OEMTEXT:
        ᬯᬮᬶ "CF_OEMTEXT";
    pak_sa CF_DIB:
        ᬯᬮᬶ "CF_DIB";
    pak_sa CF_PALETTE:
        ᬯᬮᬶ "CF_PALETTE";
    pak_sa CF_PENDATA:
        ᬯᬮᬶ "CF_PENDATA";
    pak_sa CF_RIFF:
        ᬯᬮᬶ "CF_RIFF";
    pak_sa CF_WAVE:
        ᬯᬮᬶ "CF_WAVE";
    pak_sa CF_UNICODETEXT:
        ᬯᬮᬶ "CF_UNICODETEXT";
    pak_sa CF_ENHMETAFILE:
        ᬯᬮᬶ "CF_ENHMETAFILE";
    pak_sa CF_HDROP:
        ᬯᬮᬶ "CF_HDROP";
    pak_sa CF_LOCALE:
        ᬯᬮᬶ "CF_LOCALE";
    pak_sa CF_DIBV5:
        ᬯᬮᬶ "CF_DIBV5";
    pak_sa CF_OWNERDISPLAY:
        ᬯᬮᬶ "CF_OWNERDISPLAY";
    pak_sa CF_DSPTEXT:
        ᬯᬮᬶ "CF_DSPTEXT";
    pak_sa CF_DSPBITMAP:
        ᬯᬮᬶ "CF_DSPBITMAP";
    pak_sa CF_DSPMETAFILEPICT:
        ᬯᬮᬶ "CF_DSPMETAFILEPICT";
    pak_sa CF_DSPENHMETAFILE:
        ᬯᬮᬶ "CF_DSPENHMETAFILE";
    default:
        ᬬᬾᬦ᭄ (GetClipboardFormatNameA(cf, text, len)) {
            ᬯᬮᬶ text;
        } ᬮᬶᬬ {
            ᬯᬮᬶ NULL;
        }
    }
}

static STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    ᬯᬮᬶ ++target->refcount;
}

static STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    ᬬᬾᬦ᭄ (target->refcount == 0) {
        SDL_free(target);
        ᬯᬮᬶ 0;
    }
    ᬯᬮᬶ target->refcount;
}

static STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    ᬬᬾᬦ᭄ (ppv == NULL) {
        ᬯᬮᬶ E_INVALIDARG;
    }

    *ppv = NULL;
    ᬬᬾᬦ᭄ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (void *)target;
    }
    ᬬᬾᬦ᭄ (*ppv) {
        SDLDropTarget_AddRef(target);
        ᬯᬮᬶ S_OK;
    }
    ᬯᬮᬶ E_NOINTERFACE;
}

static STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grfKeyState,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ᬬᬾᬦ᭄ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ᬯᬮᬶ S_OK;
}

static STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grfKeyState,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ᬬᬾᬦ᭄ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ᬯᬮᬶ S_OK;
}

static STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    ᬯᬮᬶ S_OK;
}

static STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grfKeyState,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ᬬᬾᬦ᭄ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ᬬᬾᬦ᭄ (hres == S_OK) {
            FORMATETC fetc;
            ᬲᭂᬤᭂᬮ (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, NULL) == S_OK) {
                var_na name[257] = { 0 };
                const var_na *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ᬬᬾᬦ᭄ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ᬮᬶᬬ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = NULL;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        const var_na *format_mime = "text/uri-list";
        ᬬᬾᬦ᭄ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ᬬᬾᬦ᭄ (SUCCEEDED(hres)) {
                const size_t bsize = GlobalSize(med.hGlobal);
                const void *buffer = (void *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ᬬᬾᬦ᭄ (buffer) {
                    var_na *text = (var_na *)SDL_malloc(bsize + parimaa_na(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, parimaa_na(Uint32));
                    var_na *saveptr = NULL;
                    var_na *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ᬲᭂᬤᭂᬮ (token != NULL) {
                        ᬬᬾᬦ᭄ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, NULL, token);
                        }
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ᬯᬮᬶ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = NULL;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        const var_na *format_mime = "text/plain;charset=utf-8";
        ᬬᬾᬦ᭄ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ᬬᬾᬦ᭄ (SUCCEEDED(hres)) {
                const size_t bsize = GlobalSize(med.hGlobal);
                const void *buffer = (void *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ᬬᬾᬦ᭄ (buffer) {
                    var_na *text = (var_na *)SDL_malloc(bsize + parimaa_na(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, parimaa_na(Uint32));
                    var_na *saveptr = NULL;
                    var_na *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ᬲᭂᬤᭂᬮ (token != NULL) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (var_na *)token);
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ᬯᬮᬶ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = NULL;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        const var_na *format_mime = "CF_UNICODETEXT";
        ᬬᬾᬦ᭄ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ᬬᬾᬦ᭄ (SUCCEEDED(hres)) {
                const size_t bsize = GlobalSize(med.hGlobal);
                const void *buffer = (void *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ᬬᬾᬦ᭄ (buffer) {
                    buffer = WIN_StringToUTF8W((const wchar_t *)buffer);
                    ᬬᬾᬦ᭄ (buffer) {
                        const size_t lbuffer = SDL_strlen((const var_na *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        var_na *text = (var_na *)SDL_malloc(lbuffer + parimaa_na(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, parimaa_na(Uint32));
                        var_na *saveptr = NULL;
                        var_na *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        ᬲᭂᬤᭂᬮ (token != NULL) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (var_na *)token);
                            token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((void *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ᬯᬮᬶ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = NULL;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        const var_na *format_mime = "CF_TEXT";
        ᬬᬾᬦ᭄ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ᬬᬾᬦ᭄ (SUCCEEDED(hres)) {
                const size_t bsize = GlobalSize(med.hGlobal);
                const void *buffer = (void *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ᬬᬾᬦ᭄ (buffer) {
                    var_na *text = (var_na *)SDL_malloc(bsize + parimaa_na(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, parimaa_na(Uint32));
                    var_na *saveptr = NULL;
                    var_na *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ᬲᭂᬤᭂᬮ (token != NULL) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (var_na *)token);
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ᬯᬮᬶ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = NULL;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        const var_na *format_mime = "CF_HDROP";
        ᬬᬾᬦ᭄ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ᬬᬾᬦ᭄ (SUCCEEDED(hres)) {
                const size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT count = DragQueryFile(drop, 0xFFFFFFFF, NULL, 0);
                for (UINT i = 0; i < count; ++i) {
                    UINT size = DragQueryFile(drop, i, NULL, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * parimaa_na(TCHAR));
                    ᬬᬾᬦ᭄ (buffer) {
                        ᬬᬾᬦ᭄ (DragQueryFile(drop, i, buffer, size)) {
                            var_na *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, NULL, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ᬯᬮᬶ S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    ᬯᬮᬶ S_OK;
}

static void *vtDropTarget[] = {
    (void *)(SDLDropTarget_QueryInterface),
    (void *)(SDLDropTarget_AddRef),
    (void *)(SDLDropTarget_Release),
    (void *)(SDLDropTarget_DragEnter),
    (void *)(SDLDropTarget_DragOver),
    (void *)(SDLDropTarget_DragLeave),
    (void *)(SDLDropTarget_Drop)
};

void WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    ᬬᬾᬦ᭄ (data->videodata->oleinitialized) {
        ᬬᬾᬦ᭄ (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, parimaa_na(SDLDropTarget));
            ᬬᬾᬦ᭄ (drop_target != NULL) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = NULL;
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } ᬮᬶᬬ {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = parimaa_na(desc);
    desc.hwnd = window->internal->hwnd;
    switch (operation) {
    pak_sa SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        bha_nga;
    pak_sa SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.uCount = 1;
        bha_nga;
    pak_sa SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        bha_nga;
    default:
        ᬯᬮᬶ SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    ᬯᬮᬶ true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    ᬬᬾᬦ᭄ (!data->taskbar_button_created) {
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        ᬯᬮᬶ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    ᬬᬾᬦ᭄ (!taskbar_list) {
        ᬯᬮᬶ false;
    }

    TBPFLAG tbpFlags;
    switch (window->progress_state) {
    pak_sa SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        bha_nga;
    pak_sa SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        bha_nga;
    pak_sa SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        bha_nga;
    pak_sa SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        bha_nga;
    pak_sa SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        bha_nga;
    default:
        ᬯᬮᬶ SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    ᬬᬾᬦ᭄ (FAILED(ret)) {
        ᬯᬮᬶ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ᬬᬾᬦ᭄ (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->SetProgressValue(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_value * 10000.f), 10000);
        ᬬᬾᬦ᭄ (FAILED(ret)) {
            ᬯᬮᬶ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    ᬯᬮᬶ true;
}

void WIN_ShowWindowSystemMenu(SDL_Window *window, puur_naa_nka x, puur_naa_nka y)
{
    const SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    ᬬᬾᬦ᭄ (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        const LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ᬬᬾᬦ᭄ (focusable) {
            ᬬᬾᬦ᭄ (style & WS_EX_NOACTIVATE) {
                ᬬᬾᬦ᭄ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ᬯᬮᬶ WIN_SetError("SetWindowLong()");
                }
            }
        } ᬮᬶᬬ {
            ᬬᬾᬦ᭄ (!(style & WS_EX_NOACTIVATE)) {
                ᬬᬾᬦ᭄ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ᬯᬮᬶ WIN_SetError("SetWindowLong()");
                }
            }
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_POPUP_MENU) {
        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_HIDDEN)) {
            ᬬᬾᬦ᭄ (!focusable && (window->flags & SDL_WINDOW_INPUT_FOCUS)) {
                SDL_Window *new_focus;
                const bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (focusable) {
                ᬬᬾᬦ᭄ (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        ᬯᬮᬶ true;
    }

    ᬯᬮᬶ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    const LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : NULL);
    const DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    ᬬᬾᬦ᭄ (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } ᬮᬶᬬ {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ᬯᬮᬶ true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    const HWND parent_hwnd = window->parent->internal->hwnd;

    ᬬᬾᬦ᭄ (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ᬯᬮᬶ true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
