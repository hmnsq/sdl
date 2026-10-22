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

#അന്തര്ഭാവ "../../core/windows/SDL_windows.h"

#അന്തര്ഭാവ "../../SDL_hints_c.h"
#അന്തര്ഭാവ "../../events/SDL_dropevents_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_windowevents_c.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "SDL_windowskeyboard.h"
#അന്തര്ഭാവ "SDL_windowswindow.h"

// Dropfile support
#അന്തര്ഭാവ <shellapi.h>

#എങ്കിൽ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#അന്തര്ഭാവ <shobjidl.h>
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

സ്ഥിതം DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            എങ്കിൽ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } അല്ലെങ്കിൽ {
                style |= STYLE_BORDERLESS;
            }
        } അല്ലെങ്കിൽ {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        എങ്കിൽ (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            എങ്കിൽ (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        എങ്കിൽ (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        എങ്കിൽ (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    തിരികെ style;
}

സ്ഥിതം DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    തിരികെ style;
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
സ്ഥിതം ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    സ്ഥിരം SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    എങ്കിൽ (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ശൂന്യ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        എങ്കിൽ (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            തിരികെ ശൂന്യ;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        എങ്കിൽ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = ശൂന്യ;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            തിരികെ ശൂന്യ;
        }
    }
    തിരികെ data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
സ്ഥിതം bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, പൂർണ്ണസംഖ്യ *x, പൂർണ്ണസംഖ്യ *y, പൂർണ്ണസംഖ്യ *width, പൂർണ്ണസംഖ്യ *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : ശൂന്യ;
    RECT rect;

    // Client rect, in points
    തിരഞ്ഞെടുപ്പ് (rect_type) {
    അവസ്ഥ SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        നിർത്തുക;
    അവസ്ഥ SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        നിർത്തുക;
    അവസ്ഥ SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        നിർത്തുക;
    അവസ്ഥ SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        നിർത്തുക;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ഇടത് = 0;
    rect.മുകൾ = 0;
    rect.വലത് = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    എങ്കിൽ (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#അല്ലെങ്കിൽ
        എങ്കിൽ (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            എങ്കിൽ (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                എങ്കിൽ (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    തിരികെ WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                തിരികെ WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ഇടത്;
    *y += rect.മുകൾ;
    *width = (rect.വലത് - rect.ഇടത്);
    *height = (rect.bottom - rect.മുകൾ);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    തിരികെ true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, പൂർണ്ണസംഖ്യ *x, പൂർണ്ണസംഖ്യ *y, പൂർണ്ണസംഖ്യ *width, പൂർണ്ണസംഖ്യ *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#അല്ലെങ്കിൽ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ശൂന്യ);
#endif
    തിരികെ WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : ശൂന്യ;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#അല്ലെങ്കിൽ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ശൂന്യ);
#endif

#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#അല്ലെങ്കിൽ
    എങ്കിൽ (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        എങ്കിൽ (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        എങ്കിൽ (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            തിരികെ WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            തിരികെ WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    തിരികെ true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND മുകൾ;
    പൂർണ്ണസംഖ്യ x, y;
    പൂർണ്ണസംഖ്യ w, h;
    bool result = true;

    // Figure out what the window area will be
    എങ്കിൽ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ)) {
        മുകൾ = HWND_TOPMOST;
    } അല്ലെങ്കിൽ {
        മുകൾ = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    എങ്കിൽ (SetWindowPos(hwnd, മുകൾ, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    വേണ്ടി (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        എങ്കിൽ (!child_window->internal) {
            // This child window is not yet fully initialized.
            തുടരുക;
        }
        എങ്കിൽ (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    തിരികെ result;
}

സ്ഥിതം SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(ശൂന്യം)
{
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    എങ്കിൽ (!hint)
        തിരികെ SDL_ERASEBACKGROUNDMODE_INITIAL;

    എങ്കിൽ (SDL_strstr(hint, "never"))
        തിരികെ SDL_ERASEBACKGROUNDMODE_NEVER;

    എങ്കിൽ (SDL_strstr(hint, "initial"))
        തിരികെ SDL_ERASEBACKGROUNDMODE_INITIAL;

    എങ്കിൽ (SDL_strstr(hint, "always"))
        തിരികെ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    പൂർണ്ണസംഖ്യ mode = SDL_GetStringInteger(hint, 1);
    എങ്കിൽ (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        തിരികെ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    തിരികെ (SDL_WindowEraseBackgroundMode)mode;
}

സ്ഥിതം bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(*data));
    എങ്കിൽ (!data) {
        തിരികെ false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#അല്ലെങ്കിൽ
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.ഇടത്   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.മുകൾ    = 0;
    data->cursor_ctrlock_rect.വലത്  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    എങ്കിൽ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } അല്ലെങ്കിൽ {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    എങ്കിൽ (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        തിരികെ WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        എങ്കിൽ (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#അല്ലെങ്കിൽ
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        എങ്കിൽ (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } അല്ലെങ്കിൽ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        എങ്കിൽ (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } അല്ലെങ്കിൽ {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        എങ്കിൽ (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } അല്ലെങ്കിൽ {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        എങ്കിൽ (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } അല്ലെങ്കിൽ എങ്കിൽ (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        എങ്കിൽ (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } അല്ലെങ്കിൽ
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        എങ്കിൽ (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } അല്ലെങ്കിൽ
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    എങ്കിൽ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        എങ്കിൽ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            പൂർണ്ണസംഖ്യ w = rect.വലത്;
            പൂർണ്ണസംഖ്യ h = rect.bottom;

            എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } അല്ലെങ്കിൽ എങ്കിൽ ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                പൂർണ്ണസംഖ്യ x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, ശൂന്യ, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } അല്ലെങ്കിൽ {
                window->w = w;
                window->h = h;
            }
        }
    }
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        എങ്കിൽ (ClientToScreen(hwnd, &point)) {
            എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_നിവേശം_FOCUS;
    SDL_SetKeyboardFocus(window);
#അല്ലെങ്കിൽ
    എങ്കിൽ (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_നിവേശം_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    എങ്കിൽ (window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ) {
        WIN_Set_Window_Always_On_മുകൾ(_this, window, true);
    } അല്ലെങ്കിൽ {
        WIN_Set_Window_Always_On_മുകൾ(_this, window, false);
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    എങ്കിൽ (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    എങ്കിൽ (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        പൂർണ്ണസംഖ്യ titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        എങ്കിൽ (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } അല്ലെങ്കിൽ {
            titleLen = 0;
        }
        എങ്കിൽ (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        എങ്കിൽ (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data) {
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        എങ്കിൽ (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        എങ്കിൽ (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        എങ്കിൽ (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            എങ്കിൽ (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } അല്ലെങ്കിൽ {
            // Restore any original event handler...
            എങ്കിൽ (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#അല്ലെങ്കിൽ
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = ശൂന്യ;
}

സ്ഥിതം ശൂന്യം WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        പൂർണ്ണസംഖ്യ abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        പൂർണ്ണസംഖ്യ abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        സ്ഥിരം പൂർണ്ണസംഖ്യ width = window->last_size_pending ? window->pending.w : window->floating.w;
        സ്ഥിരം പൂർണ്ണസംഖ്യ height = window->last_size_pending ? window->pending.h : window->floating.h;
        പൂർണ്ണസംഖ്യ offset_x = 0, offset_y = 0;

        എങ്കിൽ (window->constrain_popup) {
            // Calculate the total offset from the parents
            വേണ്ടി (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            എങ്കിൽ (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            എങ്കിൽ (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        എങ്കിൽ (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } അല്ലെങ്കിൽ {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

സ്ഥിതം ശൂന്യം WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    ആകുമ്പോൾ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    എങ്കിൽ (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", ശൂന്യ));
    HWND parent = ശൂന്യ;
    എങ്കിൽ (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        എങ്കിൽ (!SetupWindowData(_this, window, hwnd, parent)) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        പൂർണ്ണസംഖ്യ x, y;
        പൂർണ്ണസംഖ്യ w, h;

        എങ്കിൽ (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, ശൂന്യ, ശൂന്യ, SDL_Instance, ശൂന്യ);
        } അല്ലെങ്കിൽ എങ്കിൽ (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_സംഖ്യ_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_സംഖ്യ, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, ശൂന്യ, SDL_Instance, ശൂന്യ);
        എങ്കിൽ (!hwnd) {
            തിരികെ WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        എങ്കിൽ (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            എങ്കിൽ (parent) {
                DestroyWindow(parent);
            }
            തിരികെ false;
        }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_നിവേശം(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, ശൂന്യ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        എങ്കിൽ (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    എങ്കിൽ (window->flags & SDL_WINDOW_TRANSPARENT) {
        എങ്കിൽ (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, ശൂന്യ);
    എങ്കിൽ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        പൂർണ്ണസംഖ്യ pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, വലുപ്പം(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        എങ്കിൽ (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            തിരികെ WIN_SetError("SetPixelFormat()");
        }
    } അല്ലെങ്കിൽ {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        എങ്കിൽ (!(window->flags & SDL_WINDOW_OPENGL)) {
            തിരികെ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        എങ്കിൽ ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            എങ്കിൽ (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                തിരികെ false;
            }
            തിരികെ true;
#അല്ലെങ്കിൽ
            തിരികെ SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        എങ്കിൽ (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            തിരികെ false;
        }
#അല്ലെങ്കിൽ
        തിരികെ SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    തിരികെ true;
}

ശൂന്യം WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = ശൂന്യ;
    BYTE *icon_bmp;
    പൂർണ്ണസംഖ്യ icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, വലുപ്പം(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = വലുപ്പം(BITMAPINFOHEADER) + icon->h * icon->w * വലുപ്പം(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    എങ്കിൽ (!icon_bmp) {
        തിരികെ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(വലുപ്പം(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_എണ്ണം = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * വലുപ്പം(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[വലുപ്പം(BITMAPINFOHEADER)];
    row_len = icon->w * വലുപ്പം(Uint32);
    y = icon->h;
    ആകുമ്പോൾ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    എങ്കിൽ (!hicon) {
        തിരികെ SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned പൂർണ്ണസംഖ്യ)GetLastError());
    }

    എങ്കിൽ (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    തിരികെ result;
#അല്ലെങ്കിൽ
    തിരികെ SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        എങ്കിൽ (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            തിരികെ WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    തിരികെ true;
}

ശൂന്യം WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } അല്ലെങ്കിൽ {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *മുകൾ, പൂർണ്ണസംഖ്യ *ഇടത്, പൂർണ്ണസംഖ്യ *bottom, പൂർണ്ണസംഖ്യ *വലത്)
{
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *മുകൾ = rcClient.മുകൾ;
    *ഇടത് = rcClient.ഇടത്;
    *bottom = rcClient.bottom;
    *വലത് = rcClient.വലത്;

    തിരികെ true;
#അല്ലെങ്കിൽ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    എങ്കിൽ (!GetClientRect(hwnd, &rcClient)) {
        തിരികെ SDL_SetError("GetClientRect() failed, error %08X", (unsigned പൂർണ്ണസംഖ്യ)GetLastError());
    }

    എങ്കിൽ (!GetWindowRect(hwnd, &rcWindow)) {
        തിരികെ SDL_SetError("GetWindowRect() failed, error %08X", (unsigned പൂർണ്ണസംഖ്യ)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.മുകൾ;
    ptDiff.x = rcWindow.ഇടത്;

    എങ്കിൽ (!ScreenToClient(hwnd, &ptDiff)) {
        തിരികെ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned പൂർണ്ണസംഖ്യ)GetLastError());
    }

    rcWindow.മുകൾ = ptDiff.y;
    rcWindow.ഇടത് = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.വലത്;

    എങ്കിൽ (!ScreenToClient(hwnd, &ptDiff)) {
        തിരികെ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned പൂർണ്ണസംഖ്യ)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.വലത് = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *മുകൾ = rcClient.മുകൾ - rcWindow.മുകൾ;
    *ഇടത് = rcClient.ഇടത് - rcWindow.ഇടത്;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *വലത് = rcWindow.വലത് - rcClient.വലത്;

    തിരികെ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ശൂന്യം WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h)
{
    സ്ഥിരം SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    എങ്കിൽ (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.വലത്;
        *h = rect.bottom;
    } അല്ലെങ്കിൽ എങ്കിൽ (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } അല്ലെങ്കിൽ {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

ശൂന്യം WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    എങ്കിൽ (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        എങ്കിൽ (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    എങ്കിൽ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    എങ്കിൽ (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } അല്ലെങ്കിൽ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, ശൂന്യ, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    എങ്കിൽ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    എങ്കിൽ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

ശൂന്യം WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    എങ്കിൽ (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    എങ്കിൽ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        സ്ഥിരം bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

ശൂന്യം WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = ശൂന്യ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    എങ്കിൽ (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, ശൂന്യ);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_നിവേശം(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        എങ്കിൽ (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    എങ്കിൽ (bActivate) {
        SetForegroundWindow(hwnd);
        എങ്കിൽ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } അല്ലെങ്കിൽ {
        SetWindowPos(hwnd, HWND_മുകൾ, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    എങ്കിൽ (bForce) {
        Attach_Thread_നിവേശം(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ശൂന്യം WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        എങ്കിൽ (window->max_w || window->max_h) {
            പൂർണ്ണസംഖ്യ fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_മുകൾ, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } അല്ലെങ്കിൽ {
        data->windowed_mode_was_maximized = true;
    }
}

ശൂന്യം WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

ശൂന്യം WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

ശൂന്യം WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

ശൂന്യം WIN_Set_Window_Always_On_മുകൾ(SDL_VideoDevice *_this, SDL_Window *window, bool on_മുകൾ)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

ശൂന്യം WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        എങ്കിൽ (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } അല്ലെങ്കിൽ {
        data->windowed_mode_was_maximized = false;
    }
}

സ്ഥിതം ശൂന്യം WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    എങ്കിൽ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, വലുപ്പം(cornerPref));
    }
#endif
}

സ്ഥിതം ശൂന്യം WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    എങ്കിൽ (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, വലുപ്പം(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : ശൂന്യ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND മുകൾ;
    പൂർണ്ണസംഖ്യ x, y;
    പൂർണ്ണസംഖ്യ w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (പൂർണ്ണസംഖ്യ)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        തിരികെ SDL_FULLSCREEN_SUCCEEDED;
    }

    എങ്കിൽ (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ)) {
        മുകൾ = HWND_TOPMOST;
    } അല്ലെങ്കിൽ {
        മുകൾ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = വലുപ്പം(MONITORINFO);
    എങ്കിൽ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        തിരികെ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    എങ്കിൽ (fullscreen) {
        x = minfo.rcMonitor.ഇടത്;
        y = minfo.rcMonitor.മുകൾ;
        w = minfo.rcMonitor.വലത് - minfo.rcMonitor.ഇടത്;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.മുകൾ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        എങ്കിൽ (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } അല്ലെങ്കിൽ {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        എങ്കിൽ (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ശൂന്യ);
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
        എങ്കിൽ (enterMaximized) {
            സ്ഥിരം SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            സ്ഥിരം SDL_Point floating_point = { window->floating.x, window->floating.y };
            സ്ഥിരം SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            സ്ഥിരം SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            എങ്കിൽ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                എങ്കിൽ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } അല്ലെങ്കിൽ {
                    x = bounds.x;
                }
                എങ്കിൽ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } അല്ലെങ്കിൽ {
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
    SetWindowPos(hwnd, മുകൾ, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    എങ്കിൽ (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    എങ്കിൽ (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (പൂർണ്ണസംഖ്യ)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    തിരികെ SDL_FULLSCREEN_SUCCEEDED;
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ശൂന്യം WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    എങ്കിൽ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ശൂന്യ, ശൂന്യ, ശൂന്യ);
        എങ്കിൽ (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            എങ്കിൽ (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                എങ്കിൽ (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    എങ്കിൽ (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

ശൂന്യം *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    അക്ഷരം *filename_utf8;
    ശൂന്യം *iccProfileData = ശൂന്യ;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    എങ്കിൽ (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        എങ്കിൽ (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    തിരികെ iccProfileData;
}

സ്ഥിതം ശൂന്യം WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    എങ്കിൽ (data->keyboard_hook) {
        തിരികെ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    എങ്കിൽ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        തിരികെ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    എങ്കിൽ (!GetKeyboardState(data->videodata->pre_hook_താക്കോൽ_state)) {
        തിരികെ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

ശൂന്യം WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = ശൂന്യ;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    തിരികെ true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    തിരികെ true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    എങ്കിൽ (grabbed) {
        WIN_GrabKeyboard(window);
    } അല്ലെങ്കിൽ {
        WIN_UngrabKeyboard(window);
    }

    തിരികെ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ശൂന്യം WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ശൂന്യം WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (!data || !data->hwnd) {
        // The window wasn't fully initialized
        തിരികെ;
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

സ്ഥിതം BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    തിരികെ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

ശൂന്യം WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    എങ്കിൽ (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, വലുപ്പം(rect)) == 0) {
        ClipCursor(ശൂന്യ);
        SDL_zero(data->cursor_clipped_rect);
    }
}

ശൂന്യം WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    എങ്കിൽ (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        തിരികെ;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_നിവേശം_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    എങ്കിൽ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        എങ്കിൽ (!GetClipCursor(&current)) {
            തിരികെ;
        }
        എങ്കിൽ (videodevice && (
            current.ഇടത് != videodevice->desktop_bounds.x ||
            current.മുകൾ  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.ഇടത്;
            first.y  = current.മുകൾ;
            second.x = current.വലത്  - 1;
            second.y = current.bottom - 1;
            എങ്കിൽ (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                തിരികെ;
            }
        }
        ClipCursor(ശൂന്യ);
        SDL_zero(data->cursor_clipped_rect);
        തിരികെ;
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
    എങ്കിൽ (!GetClientScreenRect(data->hwnd, &client)) {
        തിരികെ;
    }

    RECT target = client;
    എങ്കിൽ (lock_to_ctr) {
        LONG cx = (client.ഇടത് + client.വലത് ) / 2;
        LONG cy = (client.മുകൾ  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.ഇടത്   += cx;
        target.വലത്  += cx;
        target.മുകൾ    += cy;
        target.bottom += cy;
    } അല്ലെങ്കിൽ എങ്കിൽ (win_mouse_rect) {
        RECT custom, overlap;
        custom.ഇടത്   = client.ഇടത് + mouse_rect.x;
        custom.മുകൾ    = client.മുകൾ  + mouse_rect.y;
        custom.വലത്  = client.ഇടത് + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.മുകൾ  + mouse_rect.y + mouse_rect.h;
        എങ്കിൽ (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } അല്ലെങ്കിൽ എങ്കിൽ (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            തിരികെ;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        എങ്കിൽ (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            എങ്കിൽ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                എങ്കിൽ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    സ്ഥിരം ദശാംശം scale = (ദശാംശം)hdpi_uint / (ദശാംശം)USER_DEFAULT_SCREEN_DPI;
                    എങ്കിൽ (scale != SDL_floorf(scale)) {
                        എങ്കിൽ (target.ഇടത് < target.വലത്) {
                            target.ഇടത് += 1;
                        }
                        എങ്കിൽ (target.വലത് > target.ഇടത്) {
                            target.വലത് -= 1;
                        }
                        എങ്കിൽ (target.മുകൾ < target.bottom) {
                            target.മുകൾ += 1;
                        }
                        എങ്കിൽ (target.bottom > target.മുകൾ) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    എങ്കിൽ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, വലുപ്പം(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    തിരികെ true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം opacity)
{
#എങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    തിരികെ false;
#അല്ലെങ്കിൽ
    സ്ഥിരം SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    സ്ഥിരം LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    എങ്കിൽ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        എങ്കിൽ (style & WS_EX_LAYERED) {
            എങ്കിൽ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                തിരികെ WIN_SetError("SetWindowLong()");
            }
        }
    } അല്ലെങ്കിൽ {
        സ്ഥിരം BYTE alpha = (BYTE)((പൂർണ്ണസംഖ്യ)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        എങ്കിൽ (!(style & WS_EX_LAYERED)) {
            എങ്കിൽ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                തിരികെ WIN_SetError("SetWindowLong()");
            }
        }

        എങ്കിൽ (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            തിരികെ WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    തിരികെ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

സ്ഥിതം സ്ഥിരം അക്ഷരം *SDLGetClipboardFormatName(UINT cf, അക്ഷരം *text, പൂർണ്ണസംഖ്യ len)
{
    തിരഞ്ഞെടുപ്പ് (cf) {
    അവസ്ഥ CF_TEXT:
        തിരികെ "CF_TEXT";
    അവസ്ഥ CF_BITMAP:
        തിരികെ "CF_BITMAP";
    അവസ്ഥ CF_METAFILEPICT:
        തിരികെ "CF_METAFILEPICT";
    അവസ്ഥ CF_SYLK:
        തിരികെ "CF_SYLK";
    അവസ്ഥ CF_DIF:
        തിരികെ "CF_DIF";
    അവസ്ഥ CF_TIFF:
        തിരികെ "CF_TIFF";
    അവസ്ഥ CF_OEMTEXT:
        തിരികെ "CF_OEMTEXT";
    അവസ്ഥ CF_DIB:
        തിരികെ "CF_DIB";
    അവസ്ഥ CF_PALETTE:
        തിരികെ "CF_PALETTE";
    അവസ്ഥ CF_PENDATA:
        തിരികെ "CF_PENDATA";
    അവസ്ഥ CF_RIFF:
        തിരികെ "CF_RIFF";
    അവസ്ഥ CF_WAVE:
        തിരികെ "CF_WAVE";
    അവസ്ഥ CF_UNICODETEXT:
        തിരികെ "CF_UNICODETEXT";
    അവസ്ഥ CF_ENHMETAFILE:
        തിരികെ "CF_ENHMETAFILE";
    അവസ്ഥ CF_HDROP:
        തിരികെ "CF_HDROP";
    അവസ്ഥ CF_LOCALE:
        തിരികെ "CF_LOCALE";
    അവസ്ഥ CF_DIBV5:
        തിരികെ "CF_DIBV5";
    അവസ്ഥ CF_OWNERDISPLAY:
        തിരികെ "CF_OWNERDISPLAY";
    അവസ്ഥ CF_DSPTEXT:
        തിരികെ "CF_DSPTEXT";
    അവസ്ഥ CF_DSPBITMAP:
        തിരികെ "CF_DSPBITMAP";
    അവസ്ഥ CF_DSPMETAFILEPICT:
        തിരികെ "CF_DSPMETAFILEPICT";
    അവസ്ഥ CF_DSPENHMETAFILE:
        തിരികെ "CF_DSPENHMETAFILE";
    സ്ഥിരസ്ഥിതി:
        എങ്കിൽ (GetClipboardFormatNameA(cf, text, len)) {
            തിരികെ text;
        } അല്ലെങ്കിൽ {
            തിരികെ ശൂന്യ;
        }
    }
}

സ്ഥിതം STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    തിരികെ ++target->refcount;
}

സ്ഥിതം STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    എങ്കിൽ (target->refcount == 0) {
        SDL_free(target);
        തിരികെ 0;
    }
    തിരികെ target->refcount;
}

സ്ഥിതം STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    എങ്കിൽ (ppv == ശൂന്യ) {
        തിരികെ E_INVALIDARG;
    }

    *ppv = ശൂന്യ;
    എങ്കിൽ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (ശൂന്യം *)target;
    }
    എങ്കിൽ (*ppv) {
        SDLDropTarget_AddRef(target);
        തിരികെ S_OK;
    }
    തിരികെ E_NOINTERFACE;
}

സ്ഥിതം STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_താക്കോൽ_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    എങ്കിൽ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    തിരികെ S_OK;
}

സ്ഥിതം STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_താക്കോൽ_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    എങ്കിൽ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    തിരികെ S_OK;
}

സ്ഥിതം STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    തിരികെ S_OK;
}

സ്ഥിതം STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_താക്കോൽ_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    എങ്കിൽ (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        എങ്കിൽ (hres == S_OK) {
            FORMATETC fetc;
            ആകുമ്പോൾ (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, ശൂന്യ) == S_OK) {
                അക്ഷരം name[257] = { 0 };
                സ്ഥിരം അക്ഷരം *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                എങ്കിൽ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } അല്ലെങ്കിൽ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = ശൂന്യ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        സ്ഥിരം അക്ഷരം *format_mime = "text/uri-list";
        എങ്കിൽ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            എങ്കിൽ (SUCCEEDED(hres)) {
                സ്ഥിരം size_t bsize = GlobalSize(med.hGlobal);
                സ്ഥിരം ശൂന്യം *buffer = (ശൂന്യം *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                എങ്കിൽ (buffer) {
                    അക്ഷരം *text = (അക്ഷരം *)SDL_malloc(bsize + വലുപ്പം(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, വലുപ്പം(Uint32));
                    അക്ഷരം *saveptr = ശൂന്യ;
                    അക്ഷരം *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token != ശൂന്യ) {
                        എങ്കിൽ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, ശൂന്യ, token);
                        }
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                തിരികെ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = ശൂന്യ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        സ്ഥിരം അക്ഷരം *format_mime = "text/plain;charset=utf-8";
        എങ്കിൽ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            എങ്കിൽ (SUCCEEDED(hres)) {
                സ്ഥിരം size_t bsize = GlobalSize(med.hGlobal);
                സ്ഥിരം ശൂന്യം *buffer = (ശൂന്യം *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                എങ്കിൽ (buffer) {
                    അക്ഷരം *text = (അക്ഷരം *)SDL_malloc(bsize + വലുപ്പം(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, വലുപ്പം(Uint32));
                    അക്ഷരം *saveptr = ശൂന്യ;
                    അക്ഷരം *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token != ശൂന്യ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (അക്ഷരം *)token);
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                തിരികെ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ശൂന്യ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        സ്ഥിരം അക്ഷരം *format_mime = "CF_UNICODETEXT";
        എങ്കിൽ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            എങ്കിൽ (SUCCEEDED(hres)) {
                സ്ഥിരം size_t bsize = GlobalSize(med.hGlobal);
                സ്ഥിരം ശൂന്യം *buffer = (ശൂന്യം *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                എങ്കിൽ (buffer) {
                    buffer = WIN_StringToUTF8W((സ്ഥിരം wchar_t *)buffer);
                    എങ്കിൽ (buffer) {
                        സ്ഥിരം size_t lbuffer = SDL_strlen((സ്ഥിരം അക്ഷരം *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        അക്ഷരം *text = (അക്ഷരം *)SDL_malloc(lbuffer + വലുപ്പം(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, വലുപ്പം(Uint32));
                        അക്ഷരം *saveptr = ശൂന്യ;
                        അക്ഷരം *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        ആകുമ്പോൾ (token != ശൂന്യ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (അക്ഷരം *)token);
                            token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((ശൂന്യം *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                തിരികെ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = ശൂന്യ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        സ്ഥിരം അക്ഷരം *format_mime = "CF_TEXT";
        എങ്കിൽ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            എങ്കിൽ (SUCCEEDED(hres)) {
                സ്ഥിരം size_t bsize = GlobalSize(med.hGlobal);
                സ്ഥിരം ശൂന്യം *buffer = (ശൂന്യം *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                എങ്കിൽ (buffer) {
                    അക്ഷരം *text = (അക്ഷരം *)SDL_malloc(bsize + വലുപ്പം(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, വലുപ്പം(Uint32));
                    അക്ഷരം *saveptr = ശൂന്യ;
                    അക്ഷരം *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token != ശൂന്യ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (അക്ഷരം *)token);
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                തിരികെ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ശൂന്യ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        സ്ഥിരം അക്ഷരം *format_mime = "CF_HDROP";
        എങ്കിൽ (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            എങ്കിൽ (SUCCEEDED(hres)) {
                സ്ഥിരം size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT എണ്ണം = DragQueryFile(drop, 0xFFFFFFFF, ശൂന്യ, 0);
                വേണ്ടി (UINT i = 0; i < എണ്ണം; ++i) {
                    UINT size = DragQueryFile(drop, i, ശൂന്യ, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * വലുപ്പം(TCHAR));
                    എങ്കിൽ (buffer) {
                        എങ്കിൽ (DragQueryFile(drop, i, buffer, size)) {
                            അക്ഷരം *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, ശൂന്യ, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                തിരികെ S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    തിരികെ S_OK;
}

സ്ഥിതം ശൂന്യം *vtDropTarget[] = {
    (ശൂന്യം *)(SDLDropTarget_QueryInterface),
    (ശൂന്യം *)(SDLDropTarget_AddRef),
    (ശൂന്യം *)(SDLDropTarget_Release),
    (ശൂന്യം *)(SDLDropTarget_DragEnter),
    (ശൂന്യം *)(SDLDropTarget_DragOver),
    (ശൂന്യം *)(SDLDropTarget_DragLeave),
    (ശൂന്യം *)(SDLDropTarget_Drop)
};

ശൂന്യം WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    എങ്കിൽ (data->videodata->oleinitialized) {
        എങ്കിൽ (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, വലുപ്പം(SDLDropTarget));
            എങ്കിൽ (drop_target != ശൂന്യ) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = ശൂന്യ;
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } അല്ലെങ്കിൽ {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = വലുപ്പം(desc);
    desc.hwnd = window->internal->hwnd;
    തിരഞ്ഞെടുപ്പ് (operation) {
    അവസ്ഥ SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        നിർത്തുക;
    അവസ്ഥ SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_എണ്ണം = 1;
        നിർത്തുക;
    അവസ്ഥ SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    തിരികെ true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    എങ്കിൽ (!data->taskbar_button_created) {
        തിരികെ true;
    }

    എങ്കിൽ (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        തിരികെ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    എങ്കിൽ (!taskbar_list) {
        തിരികെ false;
    }

    TBPFLAG tbpFlags;
    തിരഞ്ഞെടുപ്പ് (window->progress_state) {
    അവസ്ഥ SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        നിർത്തുക;
    അവസ്ഥ SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        നിർത്തുക;
    അവസ്ഥ SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        നിർത്തുക;
    അവസ്ഥ SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        നിർത്തുക;
    അവസ്ഥ SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    എങ്കിൽ (FAILED(ret)) {
        തിരികെ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    എങ്കിൽ (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_മൂല്യം(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_മൂല്യം * 10000.f), 10000);
        എങ്കിൽ (FAILED(ret)) {
            തിരികെ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    തിരികെ true;
}

ശൂന്യം WIN_ShowWindowSystemMenu(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    സ്ഥിരം SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        സ്ഥിരം LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        എങ്കിൽ (focusable) {
            എങ്കിൽ (style & WS_EX_NOACTIVATE) {
                എങ്കിൽ (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    തിരികെ WIN_SetError("SetWindowLong()");
                }
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (!(style & WS_EX_NOACTIVATE)) {
                എങ്കിൽ (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    തിരികെ WIN_SetError("SetWindowLong()");
                }
            }
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_POPUP_MENU) {
        എങ്കിൽ (!(window->flags & SDL_WINDOW_HIDDEN)) {
            എങ്കിൽ (!focusable && (window->flags & SDL_WINDOW_നിവേശം_FOCUS)) {
                SDL_Window *new_focus;
                സ്ഥിരം bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } അല്ലെങ്കിൽ എങ്കിൽ (focusable) {
                എങ്കിൽ (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        തിരികെ true;
    }

    തിരികെ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    സ്ഥിരം LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : ശൂന്യ);
    സ്ഥിരം DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    എങ്കിൽ (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } അല്ലെങ്കിൽ {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    തിരികെ true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    സ്ഥിരം HWND parent_hwnd = window->parent->internal->hwnd;

    എങ്കിൽ (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } അല്ലെങ്കിൽ എങ്കിൽ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
