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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h"

#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_dropevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowskeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

// Dropfile support
#ಅನ್ತರ್ಭಾವ <shellapi.h>

#ಯದಿ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ಅನ್ತರ್ಭಾವ <shobjidl.h>
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

ಸ್ಥಿರ DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    ಯದಿ (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } ಅನ್ಯಥಾ ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ಅನ್ಯಥಾ {
        ಯದಿ (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ಯದಿ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ಅನ್ಯಥಾ {
                style |= STYLE_BORDERLESS;
            }
        } ಅನ್ಯಥಾ {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ಯದಿ (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ಯದಿ (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ಯದಿ (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ಯದಿ (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ಪ್ರತ್ಯಾಗಮ style;
}

ಸ್ಥಿರ DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    ಯದಿ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ಯದಿ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ಪ್ರತ್ಯಾಗಮ style;
}

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಸ್ಥಿರ ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    ಧ್ರುವ SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    ಯದಿ (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ರಿಕ್ತ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        ಯದಿ (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ಯದಿ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = ರಿಕ್ತ;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }
    ಪ್ರತ್ಯಾಗಮ data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ಸ್ಥಿರ bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, ಪೂರ್ಣಾಙ್ಕ *x, ಪೂರ್ಣಾಙ್ಕ *y, ಪೂರ್ಣಾಙ್ಕ *width, ಪೂರ್ಣಾಙ್ಕ *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : ರಿಕ್ತ;
    RECT rect;

    // Client rect, in points
    ವಿಕಲ್ಪ (rect_type) {
    ಪಕ್ಷ SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        ಭಙ್ಗ;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ಎಡ = 0;
    rect.ತುದಿ = 0;
    rect.ಬಲ = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ಯದಿ (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#ಅನ್ಯಥಾ
        ಯದಿ (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ಯದಿ (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ಯದಿ (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    ಪ್ರತ್ಯಾಗಮ WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                ಪ್ರತ್ಯಾಗಮ WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ಎಡ;
    *y += rect.ತುದಿ;
    *width = (rect.ಬಲ - rect.ಎಡ);
    *height = (rect.bottom - rect.ತುದಿ);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *x, ಪೂರ್ಣಾಙ್ಕ *y, ಪೂರ್ಣಾಙ್ಕ *width, ಪೂರ್ಣಾಙ್ಕ *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ಅನ್ಯಥಾ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ರಿಕ್ತ);
#endif
    ಪ್ರತ್ಯಾಗಮ WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : ರಿಕ್ತ;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ಅನ್ಯಥಾ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ರಿಕ್ತ);
#endif

#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#ಅನ್ಯಥಾ
    ಯದಿ (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ಯದಿ (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ಯದಿ (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            ಪ್ರತ್ಯಾಗಮ WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            ಪ್ರತ್ಯಾಗಮ WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND ತುದಿ;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಪೂರ್ಣಾಙ್ಕ w, h;
    bool result = true;

    // Figure out what the window area will be
    ಯದಿ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ)) {
        ತುದಿ = HWND_TOPMOST;
    } ಅನ್ಯಥಾ {
        ತುದಿ = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    ಯದಿ (SetWindowPos(hwnd, ತುದಿ, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    ಪ್ರತಿ (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        ಯದಿ (!child_window->internal) {
            // This child window is not yet fully initialized.
            ಅನುವರ್ತ;
        }
        ಯದಿ (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(ಶೂನ್ಯ)
{
    ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    ಯದಿ (!hint)
        ಪ್ರತ್ಯಾಗಮ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ಯದಿ (SDL_strstr(hint, "never"))
        ಪ್ರತ್ಯಾಗಮ SDL_ERASEBACKGROUNDMODE_NEVER;

    ಯದಿ (SDL_strstr(hint, "initial"))
        ಪ್ರತ್ಯಾಗಮ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ಯದಿ (SDL_strstr(hint, "always"))
        ಪ್ರತ್ಯಾಗಮ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    ಪೂರ್ಣಾಙ್ಕ mode = SDL_GetStringInteger(hint, 1);
    ಯದಿ (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ಪ್ರತ್ಯಾಗಮ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ಪ್ರತ್ಯಾಗಮ (SDL_WindowEraseBackgroundMode)mode;
}

ಸ್ಥಿರ bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#ಅನ್ಯಥಾ
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.ಎಡ   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.ತುದಿ    = 0;
    data->cursor_ctrlock_rect.ಬಲ  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    ಯದಿ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } ಅನ್ಯಥಾ {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ಯದಿ (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        ಯದಿ (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#ಅನ್ಯಥಾ
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        ಯದಿ (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } ಅನ್ಯಥಾ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        ಯದಿ (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } ಅನ್ಯಥಾ {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        ಯದಿ (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } ಅನ್ಯಥಾ {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        ಯದಿ (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ಅನ್ಯಥಾ ಯದಿ (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        ಯದಿ (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } ಅನ್ಯಥಾ
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        ಯದಿ (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } ಅನ್ಯಥಾ
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    ಯದಿ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        ಯದಿ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            ಪೂರ್ಣಾಙ್ಕ w = rect.ಬಲ;
            ಪೂರ್ಣಾಙ್ಕ h = rect.bottom;

            ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } ಅನ್ಯಥಾ ಯದಿ ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                ಪೂರ್ಣಾಙ್ಕ x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, ರಿಕ್ತ, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } ಅನ್ಯಥಾ {
                window->w = w;
                window->h = h;
            }
        }
    }
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಯದಿ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        ಯದಿ (ClientToScreen(hwnd, &point)) {
            ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_ಒಳಹರಿವು_FOCUS;
    SDL_SetKeyboardFocus(window);
#ಅನ್ಯಥಾ
    ಯದಿ (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_ಒಳಹರಿವು_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    ಯದಿ (window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ) {
        WIN_Set_Window_Always_On_ತುದಿ(_this, window, true);
    } ಅನ್ಯಥಾ {
        WIN_Set_Window_Always_On_ತುದಿ(_this, window, false);
    }

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ಯದಿ (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    ಯದಿ (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        ಪೂರ್ಣಾಙ್ಕ titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ಯದಿ (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } ಅನ್ಯಥಾ {
            titleLen = 0;
        }
        ಯದಿ (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        ಯದಿ (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (data) {
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ಯದಿ (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        ಯದಿ (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        ಯದಿ (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        ಯದಿ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            ಯದಿ (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } ಅನ್ಯಥಾ {
            // Restore any original event handler...
            ಯದಿ (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#ಅನ್ಯಥಾ
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    ಯದಿ (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ಪೂರ್ಣಾಙ್ಕ abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        ಪೂರ್ಣಾಙ್ಕ abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ width = window->last_size_pending ? window->pending.w : window->floating.w;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ height = window->last_size_pending ? window->pending.h : window->floating.h;
        ಪೂರ್ಣಾಙ್ಕ offset_x = 0, offset_y = 0;

        ಯದಿ (window->constrain_popup) {
            // Calculate the total offset from the parents
            ಪ್ರತಿ (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            ಯದಿ (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            ಯದಿ (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ಯದಿ (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } ಅನ್ಯಥಾ {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    ಯಾವತ್ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    ಯದಿ (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", ರಿಕ್ತ));
    HWND parent = ರಿಕ್ತ;
    ಯದಿ (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        ಯದಿ (!SetupWindowData(_this, window, hwnd, parent)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        ಪೂರ್ಣಾಙ್ಕ x, y;
        ಪೂರ್ಣಾಙ್ಕ w, h;

        ಯದಿ (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, ರಿಕ್ತ, ರಿಕ್ತ, SDL_Instance, ರಿಕ್ತ);
        } ಅನ್ಯಥಾ ಯದಿ (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_ಸಂಖ್ಯೆ_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_ಸಂಖ್ಯೆ, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, ರಿಕ್ತ, SDL_Instance, ರಿಕ್ತ);
        ಯದಿ (!hwnd) {
            ಪ್ರತ್ಯಾಗಮ WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ಯದಿ (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            ಯದಿ (parent) {
                DestroyWindow(parent);
            }
            ಪ್ರತ್ಯಾಗಮ false;
        }

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_ಒಳಹರಿವು(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, ರಿಕ್ತ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ಯದಿ (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ಯದಿ (window->flags & SDL_WINDOW_TRANSPARENT) {
        ಯದಿ (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, ರಿಕ್ತ);
    ಯದಿ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        ಪೂರ್ಣಾಙ್ಕ pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, ಪರಿಮಾಣ(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ಯದಿ (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetPixelFormat()");
        }
    } ಅನ್ಯಥಾ {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ಯದಿ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        ಯದಿ ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            ಯದಿ (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                ಪ್ರತ್ಯಾಗಮ false;
            }
            ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        ಯದಿ (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            ಪ್ರತ್ಯಾಗಮ false;
        }
#ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = ರಿಕ್ತ;
    BYTE *icon_bmp;
    ಪೂರ್ಣಾಙ್ಕ icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, ಪರಿಮಾಣ(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = ಪರಿಮಾಣ(BITMAPINFOHEADER) + icon->h * icon->w * ಪರಿಮಾಣ(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ಯದಿ (!icon_bmp) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(ಪರಿಮಾಣ(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_ಎಣಿಕೆ = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * ಪರಿಮಾಣ(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[ಪರಿಮಾಣ(BITMAPINFOHEADER)];
    row_len = icon->w * ಪರಿಮಾಣ(Uint32);
    y = icon->h;
    ಯಾವತ್ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ಯದಿ (!hicon) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned ಪೂರ್ಣಾಙ್ಕ)GetLastError());
    }

    ಯದಿ (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ಪ್ರತ್ಯಾಗಮ result;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ಯದಿ (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            ಪ್ರತ್ಯಾಗಮ WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಯದಿ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ಅನ್ಯಥಾ {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *ತುದಿ, ಪೂರ್ಣಾಙ್ಕ *ಎಡ, ಪೂರ್ಣಾಙ್ಕ *bottom, ಪೂರ್ಣಾಙ್ಕ *ಬಲ)
{
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *ತುದಿ = rcClient.ತುದಿ;
    *ಎಡ = rcClient.ಎಡ;
    *bottom = rcClient.bottom;
    *ಬಲ = rcClient.ಬಲ;

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ಯದಿ (!GetClientRect(hwnd, &rcClient)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("GetClientRect() failed, error %08X", (unsigned ಪೂರ್ಣಾಙ್ಕ)GetLastError());
    }

    ಯದಿ (!GetWindowRect(hwnd, &rcWindow)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("GetWindowRect() failed, error %08X", (unsigned ಪೂರ್ಣಾಙ್ಕ)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.ತುದಿ;
    ptDiff.x = rcWindow.ಎಡ;

    ಯದಿ (!ScreenToClient(hwnd, &ptDiff)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned ಪೂರ್ಣಾಙ್ಕ)GetLastError());
    }

    rcWindow.ತುದಿ = ptDiff.y;
    rcWindow.ಎಡ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.ಬಲ;

    ಯದಿ (!ScreenToClient(hwnd, &ptDiff)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned ಪೂರ್ಣಾಙ್ಕ)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.ಬಲ = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *ತುದಿ = rcClient.ತುದಿ - rcWindow.ತುದಿ;
    *ಎಡ = rcClient.ಎಡ - rcWindow.ಎಡ;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *ಬಲ = rcWindow.ಬಲ - rcClient.ಬಲ;

    ಪ್ರತ್ಯಾಗಮ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ಶೂನ್ಯ WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h)
{
    ಧ್ರುವ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    ಯದಿ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.ಬಲ;
        *h = rect.bottom;
    } ಅನ್ಯಥಾ ಯದಿ (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } ಅನ್ಯಥಾ {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

ಶೂನ್ಯ WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    ಯದಿ (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ಯದಿ (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        ಯದಿ (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    ಯದಿ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    ಯದಿ (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } ಅನ್ಯಥಾ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, ರಿಕ್ತ, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    ಯದಿ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    ಯದಿ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

ಶೂನ್ಯ WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    ಯದಿ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ಯದಿ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ಧ್ರುವ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

ಶೂನ್ಯ WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = ರಿಕ್ತ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ಯದಿ (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, ರಿಕ್ತ);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_ಒಳಹರಿವು(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ಯದಿ (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ಯದಿ (bActivate) {
        SetForegroundWindow(hwnd);
        ಯದಿ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } ಅನ್ಯಥಾ {
        SetWindowPos(hwnd, HWND_ತುದಿ, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ಯದಿ (bForce) {
        Attach_Thread_ಒಳಹರಿವು(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ಶೂನ್ಯ WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ಯದಿ (window->max_w || window->max_h) {
            ಪೂರ್ಣಾಙ್ಕ fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_ತುದಿ, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } ಅನ್ಯಥಾ {
        data->windowed_mode_was_maximized = true;
    }
}

ಶೂನ್ಯ WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

ಶೂನ್ಯ WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

ಶೂನ್ಯ WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

ಶೂನ್ಯ WIN_Set_Window_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ತುದಿ)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

ಶೂನ್ಯ WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ಯದಿ (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } ಅನ್ಯಥಾ {
        data->windowed_mode_was_maximized = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ಯದಿ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, ಪರಿಮಾಣ(cornerPref));
    }
#endif
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ಯದಿ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, ಪರಿಮಾಣ(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : ರಿಕ್ತ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND ತುದಿ;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಪೂರ್ಣಾಙ್ಕ w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (ಪೂರ್ಣಾಙ್ಕ)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಯದಿ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ)) {
        ತುದಿ = HWND_TOPMOST;
    } ಅನ್ಯಥಾ {
        ತುದಿ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = ಪರಿಮಾಣ(MONITORINFO);
    ಯದಿ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    ಯದಿ (fullscreen) {
        x = minfo.rcMonitor.ಎಡ;
        y = minfo.rcMonitor.ತುದಿ;
        w = minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ಯದಿ (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ಅನ್ಯಥಾ {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ಯದಿ (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ರಿಕ್ತ);
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
        ಯದಿ (enterMaximized) {
            ಧ್ರುವ SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            ಧ್ರುವ SDL_Point floating_point = { window->floating.x, window->floating.y };
            ಧ್ರುವ SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ಧ್ರುವ SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            ಯದಿ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ಯದಿ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ಅನ್ಯಥಾ {
                    x = bounds.x;
                }
                ಯದಿ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ಅನ್ಯಥಾ {
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
    SetWindowPos(hwnd, ತುದಿ, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    ಯದಿ (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    ಯದಿ (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (ಪೂರ್ಣಾಙ್ಕ)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
}

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಶೂನ್ಯ WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    ಯದಿ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
        ಯದಿ (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            ಯದಿ (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                ಯದಿ (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    ಯದಿ (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

ಶೂನ್ಯ *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    ವರ್ಣ *filename_utf8;
    ಶೂನ್ಯ *iccProfileData = ರಿಕ್ತ;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    ಯದಿ (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        ಯದಿ (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ಪ್ರತ್ಯಾಗಮ iccProfileData;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    ಯದಿ (data->keyboard_hook) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ಯದಿ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ಯದಿ (!GetKeyboardState(data->videodata->pre_hook_ಕೀಲಿ_state)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

ಶೂನ್ಯ WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = ರಿಕ್ತ;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    ಯದಿ (grabbed) {
        WIN_GrabKeyboard(window);
    } ಅನ್ಯಥಾ {
        WIN_UngrabKeyboard(window);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಶೂನ್ಯ WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಶೂನ್ಯ WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (!data || !data->hwnd) {
        // The window wasn't fully initialized
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ಸ್ಥಿರ BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ಪ್ರತ್ಯಾಗಮ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

ಶೂನ್ಯ WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    ಯದಿ (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, ಪರಿಮಾಣ(rect)) == 0) {
        ClipCursor(ರಿಕ್ತ);
        SDL_zero(data->cursor_clipped_rect);
    }
}

ಶೂನ್ಯ WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    ಯದಿ (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ಯದಿ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ಯದಿ (!GetClipCursor(&current)) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (videodevice && (
            current.ಎಡ != videodevice->desktop_bounds.x ||
            current.ತುದಿ  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.ಎಡ;
            first.y  = current.ತುದಿ;
            second.x = current.ಬಲ  - 1;
            second.y = current.bottom - 1;
            ಯದಿ (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                ಪ್ರತ್ಯಾಗಮ;
            }
        }
        ClipCursor(ರಿಕ್ತ);
        SDL_zero(data->cursor_clipped_rect);
        ಪ್ರತ್ಯಾಗಮ;
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
    ಯದಿ (!GetClientScreenRect(data->hwnd, &client)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    RECT target = client;
    ಯದಿ (lock_to_ctr) {
        LONG cx = (client.ಎಡ + client.ಬಲ ) / 2;
        LONG cy = (client.ತುದಿ  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.ಎಡ   += cx;
        target.ಬಲ  += cx;
        target.ತುದಿ    += cy;
        target.bottom += cy;
    } ಅನ್ಯಥಾ ಯದಿ (win_mouse_rect) {
        RECT custom, overlap;
        custom.ಎಡ   = client.ಎಡ + mouse_rect.x;
        custom.ತುದಿ    = client.ತುದಿ  + mouse_rect.y;
        custom.ಬಲ  = client.ಎಡ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.ತುದಿ  + mouse_rect.y + mouse_rect.h;
        ಯದಿ (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } ಅನ್ಯಥಾ ಯದಿ (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            ಪ್ರತ್ಯಾಗಮ;
        }
    } ಅನ್ಯಥಾ ಯದಿ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ಯದಿ (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            ಯದಿ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ಯದಿ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ಧ್ರುವ ಭಿನ್ನ scale = (ಭಿನ್ನ)hdpi_uint / (ಭಿನ್ನ)USER_DEFAULT_SCREEN_DPI;
                    ಯದಿ (scale != SDL_floorf(scale)) {
                        ಯದಿ (target.ಎಡ < target.ಬಲ) {
                            target.ಎಡ += 1;
                        }
                        ಯದಿ (target.ಬಲ > target.ಎಡ) {
                            target.ಬಲ -= 1;
                        }
                        ಯದಿ (target.ತುದಿ < target.bottom) {
                            target.ತುದಿ += 1;
                        }
                        ಯದಿ (target.bottom > target.ತುದಿ) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ಯದಿ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, ಪರಿಮಾಣ(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ಭಿನ್ನ opacity)
{
#ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ಪ್ರತ್ಯಾಗಮ false;
#ಅನ್ಯಥಾ
    ಧ್ರುವ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ಧ್ರುವ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    ಯದಿ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ಯದಿ (style & WS_EX_LAYERED) {
            ಯದಿ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetWindowLong()");
            }
        }
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ BYTE alpha = (BYTE)((ಪೂರ್ಣಾಙ್ಕ)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ಯದಿ (!(style & WS_EX_LAYERED)) {
            ಯದಿ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetWindowLong()");
            }
        }

        ಯದಿ (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *SDLGetClipboardFormatName(UINT cf, ವರ್ಣ *text, ಪೂರ್ಣಾಙ್ಕ len)
{
    ವಿಕಲ್ಪ (cf) {
    ಪಕ್ಷ CF_TEXT:
        ಪ್ರತ್ಯಾಗಮ "CF_TEXT";
    ಪಕ್ಷ CF_BITMAP:
        ಪ್ರತ್ಯಾಗಮ "CF_BITMAP";
    ಪಕ್ಷ CF_METAFILEPICT:
        ಪ್ರತ್ಯಾಗಮ "CF_METAFILEPICT";
    ಪಕ್ಷ CF_SYLK:
        ಪ್ರತ್ಯಾಗಮ "CF_SYLK";
    ಪಕ್ಷ CF_DIF:
        ಪ್ರತ್ಯಾಗಮ "CF_DIF";
    ಪಕ್ಷ CF_TIFF:
        ಪ್ರತ್ಯಾಗಮ "CF_TIFF";
    ಪಕ್ಷ CF_OEMTEXT:
        ಪ್ರತ್ಯಾಗಮ "CF_OEMTEXT";
    ಪಕ್ಷ CF_DIB:
        ಪ್ರತ್ಯಾಗಮ "CF_DIB";
    ಪಕ್ಷ CF_PALETTE:
        ಪ್ರತ್ಯಾಗಮ "CF_PALETTE";
    ಪಕ್ಷ CF_PENDATA:
        ಪ್ರತ್ಯಾಗಮ "CF_PENDATA";
    ಪಕ್ಷ CF_RIFF:
        ಪ್ರತ್ಯಾಗಮ "CF_RIFF";
    ಪಕ್ಷ CF_WAVE:
        ಪ್ರತ್ಯಾಗಮ "CF_WAVE";
    ಪಕ್ಷ CF_UNICODETEXT:
        ಪ್ರತ್ಯಾಗಮ "CF_UNICODETEXT";
    ಪಕ್ಷ CF_ENHMETAFILE:
        ಪ್ರತ್ಯಾಗಮ "CF_ENHMETAFILE";
    ಪಕ್ಷ CF_HDROP:
        ಪ್ರತ್ಯಾಗಮ "CF_HDROP";
    ಪಕ್ಷ CF_LOCALE:
        ಪ್ರತ್ಯಾಗಮ "CF_LOCALE";
    ಪಕ್ಷ CF_DIBV5:
        ಪ್ರತ್ಯಾಗಮ "CF_DIBV5";
    ಪಕ್ಷ CF_OWNERDISPLAY:
        ಪ್ರತ್ಯಾಗಮ "CF_OWNERDISPLAY";
    ಪಕ್ಷ CF_DSPTEXT:
        ಪ್ರತ್ಯಾಗಮ "CF_DSPTEXT";
    ಪಕ್ಷ CF_DSPBITMAP:
        ಪ್ರತ್ಯಾಗಮ "CF_DSPBITMAP";
    ಪಕ್ಷ CF_DSPMETAFILEPICT:
        ಪ್ರತ್ಯಾಗಮ "CF_DSPMETAFILEPICT";
    ಪಕ್ಷ CF_DSPENHMETAFILE:
        ಪ್ರತ್ಯಾಗಮ "CF_DSPENHMETAFILE";
    ಸ್ವಭಾವ:
        ಯದಿ (GetClipboardFormatNameA(cf, text, len)) {
            ಪ್ರತ್ಯಾಗಮ text;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }
}

ಸ್ಥಿರ STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    ಪ್ರತ್ಯಾಗಮ ++target->refcount;
}

ಸ್ಥಿರ STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    ಯದಿ (target->refcount == 0) {
        SDL_free(target);
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ target->refcount;
}

ಸ್ಥಿರ STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    ಯದಿ (ppv == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ E_INVALIDARG;
    }

    *ppv = ರಿಕ್ತ;
    ಯದಿ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (ಶೂನ್ಯ *)target;
    }
    ಯದಿ (*ppv) {
        SDLDropTarget_AddRef(target);
        ಪ್ರತ್ಯಾಗಮ S_OK;
    }
    ಪ್ರತ್ಯಾಗಮ E_NOINTERFACE;
}

ಸ್ಥಿರ STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_ಕೀಲಿ_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ಯದಿ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ಪ್ರತ್ಯಾಗಮ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_ಕೀಲಿ_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ಯದಿ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ಪ್ರತ್ಯಾಗಮ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    ಪ್ರತ್ಯಾಗಮ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_ಕೀಲಿ_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ಯದಿ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ಯದಿ (hres == S_OK) {
            FORMATETC fetc;
            ಯಾವತ್ (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, ರಿಕ್ತ) == S_OK) {
                ವರ್ಣ name[257] = { 0 };
                ಧ್ರುವ ವರ್ಣ *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ಯದಿ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ಅನ್ಯಥಾ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = ರಿಕ್ತ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಧ್ರುವ ವರ್ಣ *format_mime = "text/uri-list";
        ಯದಿ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಯದಿ (SUCCEEDED(hres)) {
                ಧ್ರುವ size_t bsize = GlobalSize(med.hGlobal);
                ಧ್ರುವ ಶೂನ್ಯ *buffer = (ಶೂನ್ಯ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ಯದಿ (buffer) {
                    ವರ್ಣ *text = (ವರ್ಣ *)SDL_malloc(bsize + ಪರಿಮಾಣ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ಪರಿಮಾಣ(Uint32));
                    ವರ್ಣ *saveptr = ರಿಕ್ತ;
                    ವರ್ಣ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ಯಾವತ್ (token != ರಿಕ್ತ) {
                        ಯದಿ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, ರಿಕ್ತ, token);
                        }
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ಪ್ರತ್ಯಾಗಮ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = ರಿಕ್ತ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಧ್ರುವ ವರ್ಣ *format_mime = "text/plain;charset=utf-8";
        ಯದಿ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಯದಿ (SUCCEEDED(hres)) {
                ಧ್ರುವ size_t bsize = GlobalSize(med.hGlobal);
                ಧ್ರುವ ಶೂನ್ಯ *buffer = (ಶೂನ್ಯ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ಯದಿ (buffer) {
                    ವರ್ಣ *text = (ವರ್ಣ *)SDL_malloc(bsize + ಪರಿಮಾಣ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ಪರಿಮಾಣ(Uint32));
                    ವರ್ಣ *saveptr = ರಿಕ್ತ;
                    ವರ್ಣ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ಯಾವತ್ (token != ರಿಕ್ತ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ವರ್ಣ *)token);
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ಪ್ರತ್ಯಾಗಮ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ರಿಕ್ತ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಧ್ರುವ ವರ್ಣ *format_mime = "CF_UNICODETEXT";
        ಯದಿ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಯದಿ (SUCCEEDED(hres)) {
                ಧ್ರುವ size_t bsize = GlobalSize(med.hGlobal);
                ಧ್ರುವ ಶೂನ್ಯ *buffer = (ಶೂನ್ಯ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ಯದಿ (buffer) {
                    buffer = WIN_StringToUTF8W((ಧ್ರುವ wchar_t *)buffer);
                    ಯದಿ (buffer) {
                        ಧ್ರುವ size_t lbuffer = SDL_strlen((ಧ್ರುವ ವರ್ಣ *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        ವರ್ಣ *text = (ವರ್ಣ *)SDL_malloc(lbuffer + ಪರಿಮಾಣ(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, ಪರಿಮಾಣ(Uint32));
                        ವರ್ಣ *saveptr = ರಿಕ್ತ;
                        ವರ್ಣ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        ಯಾವತ್ (token != ರಿಕ್ತ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (ವರ್ಣ *)token);
                            token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((ಶೂನ್ಯ *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ಪ್ರತ್ಯಾಗಮ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = ರಿಕ್ತ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಧ್ರುವ ವರ್ಣ *format_mime = "CF_TEXT";
        ಯದಿ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಯದಿ (SUCCEEDED(hres)) {
                ಧ್ರುವ size_t bsize = GlobalSize(med.hGlobal);
                ಧ್ರುವ ಶೂನ್ಯ *buffer = (ಶೂನ್ಯ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ಯದಿ (buffer) {
                    ವರ್ಣ *text = (ವರ್ಣ *)SDL_malloc(bsize + ಪರಿಮಾಣ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ಪರಿಮಾಣ(Uint32));
                    ವರ್ಣ *saveptr = ರಿಕ್ತ;
                    ವರ್ಣ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ಯಾವತ್ (token != ರಿಕ್ತ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ವರ್ಣ *)token);
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ಪ್ರತ್ಯಾಗಮ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ರಿಕ್ತ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಧ್ರುವ ವರ್ಣ *format_mime = "CF_HDROP";
        ಯದಿ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಯದಿ (SUCCEEDED(hres)) {
                ಧ್ರುವ size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT ಎಣಿಕೆ = DragQueryFile(drop, 0xFFFFFFFF, ರಿಕ್ತ, 0);
                ಪ್ರತಿ (UINT i = 0; i < ಎಣಿಕೆ; ++i) {
                    UINT size = DragQueryFile(drop, i, ರಿಕ್ತ, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * ಪರಿಮಾಣ(TCHAR));
                    ಯದಿ (buffer) {
                        ಯದಿ (DragQueryFile(drop, i, buffer, size)) {
                            ವರ್ಣ *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, ರಿಕ್ತ, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ಪ್ರತ್ಯಾಗಮ S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    ಪ್ರತ್ಯಾಗಮ S_OK;
}

ಸ್ಥಿರ ಶೂನ್ಯ *vtDropTarget[] = {
    (ಶೂನ್ಯ *)(SDLDropTarget_QueryInterface),
    (ಶೂನ್ಯ *)(SDLDropTarget_AddRef),
    (ಶೂನ್ಯ *)(SDLDropTarget_Release),
    (ಶೂನ್ಯ *)(SDLDropTarget_DragEnter),
    (ಶೂನ್ಯ *)(SDLDropTarget_DragOver),
    (ಶೂನ್ಯ *)(SDLDropTarget_DragLeave),
    (ಶೂನ್ಯ *)(SDLDropTarget_Drop)
};

ಶೂನ್ಯ WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    ಯದಿ (data->videodata->oleinitialized) {
        ಯದಿ (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, ಪರಿಮಾಣ(SDLDropTarget));
            ಯದಿ (drop_target != ರಿಕ್ತ) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } ಅನ್ಯಥಾ ಯದಿ (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = ರಿಕ್ತ;
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } ಅನ್ಯಥಾ {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = ಪರಿಮಾಣ(desc);
    desc.hwnd = window->internal->hwnd;
    ವಿಕಲ್ಪ (operation) {
    ಪಕ್ಷ SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_ಎಣಿಕೆ = 1;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    ಯದಿ (!data->taskbar_button_created) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    ಯದಿ (!taskbar_list) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    TBPFLAG tbpFlags;
    ವಿಕಲ್ಪ (window->progress_state) {
    ಪಕ್ಷ SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    ಯದಿ (FAILED(ret)) {
        ಪ್ರತ್ಯಾಗಮ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ಯದಿ (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_ಮೌಲ್ಯ(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_ಮೌಲ್ಯ * 10000.f), 10000);
        ಯದಿ (FAILED(ret)) {
            ಪ್ರತ್ಯಾಗಮ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_ShowWindowSystemMenu(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    ಧ್ರುವ SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    ಯದಿ (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        ಧ್ರುವ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ಯದಿ (focusable) {
            ಯದಿ (style & WS_EX_NOACTIVATE) {
                ಯದಿ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetWindowLong()");
                }
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (!(style & WS_EX_NOACTIVATE)) {
                ಯದಿ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetWindowLong()");
                }
            }
        }
    } ಅನ್ಯಥಾ ಯದಿ (window->flags & SDL_WINDOW_POPUP_MENU) {
        ಯದಿ (!(window->flags & SDL_WINDOW_HIDDEN)) {
            ಯದಿ (!focusable && (window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS)) {
                SDL_Window *new_focus;
                ಧ್ರುವ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } ಅನ್ಯಥಾ ಯದಿ (focusable) {
                ಯದಿ (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    ಧ್ರುವ LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : ರಿಕ್ತ);
    ಧ್ರುವ DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    ಯದಿ (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } ಅನ್ಯಥಾ {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಧ್ರುವ HWND parent_hwnd = window->parent->internal->hwnd;

    ಯದಿ (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } ಅನ್ಯಥಾ ಯದಿ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
