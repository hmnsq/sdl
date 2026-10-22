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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#অন্তর্ভাৱ "../../core/windows/SDL_windows.h"

#অন্তর্ভাৱ "../../SDL_hints_c.h"
#অন্তর্ভাৱ "../../events/SDL_dropevents_c.h"
#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/SDL_windowevents_c.h"
#অন্তর্ভাৱ "../SDL_pixels_c.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"

#অন্তর্ভাৱ "SDL_windowsvideo.h"
#অন্তর্ভাৱ "SDL_windowskeyboard.h"
#অন্তর্ভাৱ "SDL_windowswindow.h"

// Dropfile support
#অন্তর্ভাৱ <shellapi.h>

#যদি !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#অন্তর্ভাৱ <shobjidl.h>
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

স্থির DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } অন্যথা যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } অন্যথা {
        যদি (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            যদি (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } অন্যথা {
                style |= STYLE_BORDERLESS;
            }
        } অন্যথা {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        যদি (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            যদি (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        যদি (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        যদি (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ঘূৰাই style;
}

স্থির DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    যদি (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    যদি (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ঘূৰাই style;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
স্থির ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    ধ্রুৱ SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    যদি (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, রিক্ত, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        যদি (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            ঘূৰাই রিক্ত;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        যদি (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = রিক্ত;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            ঘূৰাই রিক্ত;
        }
    }
    ঘূৰাই data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
স্থির bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, পূর্ণাঙ্ক *x, পূর্ণাঙ্ক *y, পূর্ণাঙ্ক *width, পূর্ণাঙ্ক *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : রিক্ত;
    RECT rect;

    // Client rect, in points
    ৱিকল্প (rect_type) {
    পক্ষ SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        ভঙ্গ;
    পক্ষ SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        ভঙ্গ;
    পক্ষ SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        ভঙ্গ;
    পক্ষ SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        ভঙ্গ;
    স্ৱভাৱ:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        ভঙ্গ;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.বাম = 0;
    rect.শীৰ্ষ = 0;
    rect.ডান = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    যদি (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#অন্যথা
        যদি (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            যদি (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                যদি (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    ঘূৰাই WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } অন্যথা {
            যদি (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                ঘূৰাই WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.বাম;
    *y += rect.শীৰ্ষ;
    *width = (rect.ডান - rect.বাম);
    *height = (rect.bottom - rect.শীৰ্ষ);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    ঘূৰাই true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, পূর্ণাঙ্ক *x, পূর্ণাঙ্ক *y, পূর্ণাঙ্ক *width, পূর্ণাঙ্ক *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#অন্যথা
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != রিক্ত);
#endif
    ঘূৰাই WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : রিক্ত;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#অন্যথা
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != রিক্ত);
#endif

#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#অন্যথা
    যদি (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        যদি (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        যদি (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            ঘূৰাই WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } অন্যথা {
        যদি (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            ঘূৰাই WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    ঘূৰাই true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND শীৰ্ষ;
    পূর্ণাঙ্ক x, y;
    পূর্ণাঙ্ক w, h;
    bool result = true;

    // Figure out what the window area will be
    যদি (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_শীৰ্ষ)) {
        শীৰ্ষ = HWND_TOPMOST;
    } অন্যথা {
        শীৰ্ষ = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    যদি (SetWindowPos(hwnd, শীৰ্ষ, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    বাবে (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        যদি (!child_window->internal) {
            // This child window is not yet fully initialized.
            অনুৱর্ত;
        }
        যদি (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    ঘূৰাই result;
}

স্থির SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(শূন্য)
{
    ধ্রুৱ ৱর্ণ *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    যদি (!hint)
        ঘূৰাই SDL_ERASEBACKGROUNDMODE_INITIAL;

    যদি (SDL_strstr(hint, "never"))
        ঘূৰাই SDL_ERASEBACKGROUNDMODE_NEVER;

    যদি (SDL_strstr(hint, "initial"))
        ঘূৰাই SDL_ERASEBACKGROUNDMODE_INITIAL;

    যদি (SDL_strstr(hint, "always"))
        ঘূৰাই SDL_ERASEBACKGROUNDMODE_ALWAYS;

    পূর্ণাঙ্ক mode = SDL_GetStringInteger(hint, 1);
    যদি (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ঘূৰাই SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ঘূৰাই (SDL_WindowEraseBackgroundMode)mode;
}

স্থির bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, পরিমাণ(*data));
    যদি (!data) {
        ঘূৰাই false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#অন্যথা
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.বাম   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.শীৰ্ষ    = 0;
    data->cursor_ctrlock_rect.ডান  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    যদি (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } অন্যথা {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    যদি (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        ঘূৰাই WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        যদি (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#অন্যথা
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        যদি (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } অন্যথা {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        যদি (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } অন্যথা {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        যদি (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        যদি (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } অন্যথা যদি (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        যদি (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } অন্যথা
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        যদি (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } অন্যথা
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    যদি (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            পূর্ণাঙ্ক w = rect.ডান;
            পূর্ণাঙ্ক h = rect.bottom;

            যদি (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } অন্যথা যদি ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                পূর্ণাঙ্ক x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, রিক্ত, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } অন্যথা {
                window->w = w;
                window->h = h;
            }
        }
    }
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        যদি (ClientToScreen(hwnd, &point)) {
            যদি (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_প্ৰবেশ_FOCUS;
    SDL_SetKeyboardFocus(window);
#অন্যথা
    যদি (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_প্ৰবেশ_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    যদি (window->flags & SDL_WINDOW_ALWAYS_ON_শীৰ্ষ) {
        WIN_Set_Window_Always_On_শীৰ্ষ(_this, window, true);
    } অন্যথা {
        WIN_Set_Window_Always_On_শীৰ্ষ(_this, window, false);
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    যদি (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    যদি (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        পূর্ণাঙ্ক titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        যদি (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } অন্যথা {
            titleLen = 0;
        }
        যদি (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        যদি (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    ঘূৰাই true;
}

স্থির শূন্য CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    যদি (data) {
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        যদি (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        যদি (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        যদি (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            যদি (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } অন্যথা {
            // Restore any original event handler...
            যদি (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#অন্যথা
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = রিক্ত;
}

স্থির শূন্য WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    যদি (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        পূর্ণাঙ্ক abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        পূর্ণাঙ্ক abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        ধ্রুৱ পূর্ণাঙ্ক width = window->last_size_pending ? window->pending.w : window->floating.w;
        ধ্রুৱ পূর্ণাঙ্ক height = window->last_size_pending ? window->pending.h : window->floating.h;
        পূর্ণাঙ্ক offset_x = 0, offset_y = 0;

        যদি (window->constrain_popup) {
            // Calculate the total offset from the parents
            বাবে (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            যদি (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            যদি (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        যদি (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } অন্যথা {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

স্থির শূন্য WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    যেতিয়ালৈ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    যদি (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", রিক্ত));
    HWND parent = রিক্ত;
    যদি (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        যদি (!SetupWindowData(_this, window, hwnd, parent)) {
            ঘূৰাই false;
        }
    } অন্যথা {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        পূর্ণাঙ্ক x, y;
        পূর্ণাঙ্ক w, h;

        যদি (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, রিক্ত, রিক্ত, SDL_Instance, রিক্ত);
        } অন্যথা যদি (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_সংখ্যা_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_সংখ্যা, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, রিক্ত, SDL_Instance, রিক্ত);
        যদি (!hwnd) {
            ঘূৰাই WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        যদি (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            যদি (parent) {
                DestroyWindow(parent);
            }
            ঘূৰাই false;
        }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_প্ৰবেশ(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, রিক্ত, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        যদি (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    যদি (window->flags & SDL_WINDOW_TRANSPARENT) {
        যদি (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, রিক্ত);
    যদি (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        পূর্ণাঙ্ক pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, পরিমাণ(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        যদি (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            ঘূৰাই WIN_SetError("SetPixelFormat()");
        }
    } অন্যথা {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
            ঘূৰাই true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        যদি ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            যদি (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                ঘূৰাই false;
            }
            ঘূৰাই true;
#অন্যথা
            ঘূৰাই SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        যদি (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            ঘূৰাই false;
        }
#অন্যথা
        ঘূৰাই SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ঘূৰাই true;
}

শূন্য WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = রিক্ত;
    BYTE *icon_bmp;
    পূর্ণাঙ্ক icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, পরিমাণ(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = পরিমাণ(BITMAPINFOHEADER) + icon->h * icon->w * পরিমাণ(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    যদি (!icon_bmp) {
        ঘূৰাই false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(পরিমাণ(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_গুনতি = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * পরিমাণ(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[পরিমাণ(BITMAPINFOHEADER)];
    row_len = icon->w * পরিমাণ(Uint32);
    y = icon->h;
    যেতিয়ালৈ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    যদি (!hicon) {
        ঘূৰাই SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned পূর্ণাঙ্ক)GetLastError());
    }

    যদি (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ঘূৰাই result;
#অন্যথা
    ঘূৰাই SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        যদি (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            ঘূৰাই WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } অন্যথা {
        ঘূৰাই SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ঘূৰাই true;
}

শূন্য WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } অন্যথা {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *শীৰ্ষ, পূর্ণাঙ্ক *বাম, পূর্ণাঙ্ক *bottom, পূর্ণাঙ্ক *ডান)
{
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *শীৰ্ষ = rcClient.শীৰ্ষ;
    *বাম = rcClient.বাম;
    *bottom = rcClient.bottom;
    *ডান = rcClient.ডান;

    ঘূৰাই true;
#অন্যথা  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    যদি (!GetClientRect(hwnd, &rcClient)) {
        ঘূৰাই SDL_SetError("GetClientRect() failed, error %08X", (unsigned পূর্ণাঙ্ক)GetLastError());
    }

    যদি (!GetWindowRect(hwnd, &rcWindow)) {
        ঘূৰাই SDL_SetError("GetWindowRect() failed, error %08X", (unsigned পূর্ণাঙ্ক)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.শীৰ্ষ;
    ptDiff.x = rcWindow.বাম;

    যদি (!ScreenToClient(hwnd, &ptDiff)) {
        ঘূৰাই SDL_SetError("ScreenToClient() failed, error %08X", (unsigned পূর্ণাঙ্ক)GetLastError());
    }

    rcWindow.শীৰ্ষ = ptDiff.y;
    rcWindow.বাম = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.ডান;

    যদি (!ScreenToClient(hwnd, &ptDiff)) {
        ঘূৰাই SDL_SetError("ScreenToClient() failed, error %08X", (unsigned পূর্ণাঙ্ক)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.ডান = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *শীৰ্ষ = rcClient.শীৰ্ষ - rcWindow.শীৰ্ষ;
    *বাম = rcClient.বাম - rcWindow.বাম;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *ডান = rcWindow.ডান - rcClient.ডান;

    ঘূৰাই true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

শূন্য WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h)
{
    ধ্রুৱ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    যদি (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.ডান;
        *h = rect.bottom;
    } অন্যথা যদি (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } অন্যথা {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

শূন্য WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    যদি (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        যদি (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    যদি (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    যদি (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } অন্যথা {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, রিক্ত, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    যদি (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

শূন্য WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    যদি (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ধ্রুৱ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

শূন্য WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = রিক্ত;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    যদি (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, রিক্ত);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_প্ৰবেশ(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        যদি (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_শীৰ্ষ)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    যদি (bActivate) {
        SetForegroundWindow(hwnd);
        যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } অন্যথা {
        SetWindowPos(hwnd, HWND_শীৰ্ষ, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    যদি (bForce) {
        Attach_Thread_প্ৰবেশ(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

শূন্য WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        যদি (window->max_w || window->max_h) {
            পূর্ণাঙ্ক fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_শীৰ্ষ, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } অন্যথা {
        data->windowed_mode_was_maximized = true;
    }
}

শূন্য WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

শূন্য WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

শূন্য WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

শূন্য WIN_Set_Window_Always_On_শীৰ্ষ(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীৰ্ষ)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

শূন্য WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        যদি (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } অন্যথা {
        data->windowed_mode_was_maximized = false;
    }
}

স্থির শূন্য WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    যদি (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, পরিমাণ(cornerPref));
    }
#endif
}

স্থির শূন্য WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    যদি (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, পরিমাণ(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : রিক্ত;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND শীৰ্ষ;
    পূর্ণাঙ্ক x, y;
    পূর্ণাঙ্ক w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (পূর্ণাঙ্ক)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
    }

    যদি (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_শীৰ্ষ)) {
        শীৰ্ষ = HWND_TOPMOST;
    } অন্যথা {
        শীৰ্ষ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = পরিমাণ(MONITORINFO);
    যদি (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        ঘূৰাই SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    যদি (fullscreen) {
        x = minfo.rcMonitor.বাম;
        y = minfo.rcMonitor.শীৰ্ষ;
        w = minfo.rcMonitor.ডান - minfo.rcMonitor.বাম;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.শীৰ্ষ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        যদি (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } অন্যথা {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        যদি (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != রিক্ত);
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
        যদি (enterMaximized) {
            ধ্রুৱ SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            ধ্রুৱ SDL_Point floating_point = { window->floating.x, window->floating.y };
            ধ্রুৱ SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ধ্রুৱ SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            যদি (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                যদি (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } অন্যথা {
                    x = bounds.x;
                }
                যদি (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } অন্যথা {
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
    SetWindowPos(hwnd, শীৰ্ষ, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    যদি (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    যদি (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (পূর্ণাঙ্ক)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
শূন্য WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    যদি (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, রিক্ত, রিক্ত, রিক্ত);
        যদি (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            যদি (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                যদি (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    যদি (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

শূন্য *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    ৱর্ণ *filename_utf8;
    শূন্য *iccProfileData = রিক্ত;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    যদি (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        যদি (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ঘূৰাই iccProfileData;
}

স্থির শূন্য WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    যদি (data->keyboard_hook) {
        ঘূৰাই;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    যদি (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ঘূৰাই;
    }

    // Capture a snapshot of the current keyboard state before the hook
    যদি (!GetKeyboardState(data->videodata->pre_hook_চাবি_state)) {
        ঘূৰাই;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

শূন্য WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    যদি (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = রিক্ত;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    ঘূৰাই true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    ঘূৰাই true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    যদি (grabbed) {
        WIN_GrabKeyboard(window);
    } অন্যথা {
        WIN_UngrabKeyboard(window);
    }

    ঘূৰাই true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

শূন্য WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
শূন্য WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    যদি (!data || !data->hwnd) {
        // The window wasn't fully initialized
        ঘূৰাই;
    }

    যদি (window->flags & SDL_WINDOW_ALWAYS_ON_শীৰ্ষ) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

স্থির BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ঘূৰাই GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

শূন্য WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    যদি (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, পরিমাণ(rect)) == 0) {
        ClipCursor(রিক্ত);
        SDL_zero(data->cursor_clipped_rect);
    }
}

শূন্য WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    যদি (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        ঘূৰাই;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_প্ৰবেশ_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    যদি (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        যদি (!GetClipCursor(&current)) {
            ঘূৰাই;
        }
        যদি (videodevice && (
            current.বাম != videodevice->desktop_bounds.x ||
            current.শীৰ্ষ  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.বাম;
            first.y  = current.শীৰ্ষ;
            second.x = current.ডান  - 1;
            second.y = current.bottom - 1;
            যদি (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                ঘূৰাই;
            }
        }
        ClipCursor(রিক্ত);
        SDL_zero(data->cursor_clipped_rect);
        ঘূৰাই;
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
    যদি (!GetClientScreenRect(data->hwnd, &client)) {
        ঘূৰাই;
    }

    RECT target = client;
    যদি (lock_to_ctr) {
        LONG cx = (client.বাম + client.ডান ) / 2;
        LONG cy = (client.শীৰ্ষ  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.বাম   += cx;
        target.ডান  += cx;
        target.শীৰ্ষ    += cy;
        target.bottom += cy;
    } অন্যথা যদি (win_mouse_rect) {
        RECT custom, overlap;
        custom.বাম   = client.বাম + mouse_rect.x;
        custom.শীৰ্ষ    = client.শীৰ্ষ  + mouse_rect.y;
        custom.ডান  = client.বাম + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.শীৰ্ষ  + mouse_rect.y + mouse_rect.h;
        যদি (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } অন্যথা যদি (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            ঘূৰাই;
        }
    } অন্যথা যদি (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        যদি (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            যদি (hmon) {
                UINT hdpi_uint, vdpi_uint;
                যদি (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ধ্রুৱ ভিন্ন scale = (ভিন্ন)hdpi_uint / (ভিন্ন)USER_DEFAULT_SCREEN_DPI;
                    যদি (scale != SDL_floorf(scale)) {
                        যদি (target.বাম < target.ডান) {
                            target.বাম += 1;
                        }
                        যদি (target.ডান > target.বাম) {
                            target.ডান -= 1;
                        }
                        যদি (target.শীৰ্ষ < target.bottom) {
                            target.শীৰ্ষ += 1;
                        }
                        যদি (target.bottom > target.শীৰ্ষ) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    যদি (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, পরিমাণ(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    ঘূৰাই true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ভিন্ন opacity)
{
#যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ঘূৰাই false;
#অন্যথা
    ধ্রুৱ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ধ্রুৱ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    যদি (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        যদি (style & WS_EX_LAYERED) {
            যদি (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ঘূৰাই WIN_SetError("SetWindowLong()");
            }
        }
    } অন্যথা {
        ধ্রুৱ BYTE alpha = (BYTE)((পূর্ণাঙ্ক)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        যদি (!(style & WS_EX_LAYERED)) {
            যদি (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ঘূৰাই WIN_SetError("SetWindowLong()");
            }
        }

        যদি (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ঘূৰাই WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    ঘূৰাই true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

স্থির ধ্রুৱ ৱর্ণ *SDLGetClipboardFormatName(UINT cf, ৱর্ণ *text, পূর্ণাঙ্ক len)
{
    ৱিকল্প (cf) {
    পক্ষ CF_TEXT:
        ঘূৰাই "CF_TEXT";
    পক্ষ CF_BITMAP:
        ঘূৰাই "CF_BITMAP";
    পক্ষ CF_METAFILEPICT:
        ঘূৰাই "CF_METAFILEPICT";
    পক্ষ CF_SYLK:
        ঘূৰাই "CF_SYLK";
    পক্ষ CF_DIF:
        ঘূৰাই "CF_DIF";
    পক্ষ CF_TIFF:
        ঘূৰাই "CF_TIFF";
    পক্ষ CF_OEMTEXT:
        ঘূৰাই "CF_OEMTEXT";
    পক্ষ CF_DIB:
        ঘূৰাই "CF_DIB";
    পক্ষ CF_PALETTE:
        ঘূৰাই "CF_PALETTE";
    পক্ষ CF_PENDATA:
        ঘূৰাই "CF_PENDATA";
    পক্ষ CF_RIFF:
        ঘূৰাই "CF_RIFF";
    পক্ষ CF_WAVE:
        ঘূৰাই "CF_WAVE";
    পক্ষ CF_UNICODETEXT:
        ঘূৰাই "CF_UNICODETEXT";
    পক্ষ CF_ENHMETAFILE:
        ঘূৰাই "CF_ENHMETAFILE";
    পক্ষ CF_HDROP:
        ঘূৰাই "CF_HDROP";
    পক্ষ CF_LOCALE:
        ঘূৰাই "CF_LOCALE";
    পক্ষ CF_DIBV5:
        ঘূৰাই "CF_DIBV5";
    পক্ষ CF_OWNERDISPLAY:
        ঘূৰাই "CF_OWNERDISPLAY";
    পক্ষ CF_DSPTEXT:
        ঘূৰাই "CF_DSPTEXT";
    পক্ষ CF_DSPBITMAP:
        ঘূৰাই "CF_DSPBITMAP";
    পক্ষ CF_DSPMETAFILEPICT:
        ঘূৰাই "CF_DSPMETAFILEPICT";
    পক্ষ CF_DSPENHMETAFILE:
        ঘূৰাই "CF_DSPENHMETAFILE";
    স্ৱভাৱ:
        যদি (GetClipboardFormatNameA(cf, text, len)) {
            ঘূৰাই text;
        } অন্যথা {
            ঘূৰাই রিক্ত;
        }
    }
}

স্থির STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    ঘূৰাই ++target->refcount;
}

স্থির STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    যদি (target->refcount == 0) {
        SDL_free(target);
        ঘূৰাই 0;
    }
    ঘূৰাই target->refcount;
}

স্থির STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    যদি (ppv == রিক্ত) {
        ঘূৰাই E_INVALIDARG;
    }

    *ppv = রিক্ত;
    যদি (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (শূন্য *)target;
    }
    যদি (*ppv) {
        SDLDropTarget_AddRef(target);
        ঘূৰাই S_OK;
    }
    ঘূৰাই E_NOINTERFACE;
}

স্থির STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_চাবি_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    যদি (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ঘূৰাই S_OK;
}

স্থির STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_চাবি_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    যদি (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ঘূৰাই S_OK;
}

স্থির STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    ঘূৰাই S_OK;
}

স্থির STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_চাবি_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    যদি (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        যদি (hres == S_OK) {
            FORMATETC fetc;
            যেতিয়ালৈ (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, রিক্ত) == S_OK) {
                ৱর্ণ name[257] = { 0 };
                ধ্রুৱ ৱর্ণ *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                যদি (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } অন্যথা {
                    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = রিক্ত;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ধ্রুৱ ৱর্ণ *format_mime = "text/uri-list";
        যদি (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            যদি (SUCCEEDED(hres)) {
                ধ্রুৱ size_t bsize = GlobalSize(med.hGlobal);
                ধ্রুৱ শূন্য *buffer = (শূন্য *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                যদি (buffer) {
                    ৱর্ণ *text = (ৱর্ণ *)SDL_malloc(bsize + পরিমাণ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, পরিমাণ(Uint32));
                    ৱর্ণ *saveptr = রিক্ত;
                    ৱর্ণ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    যেতিয়ালৈ (token != রিক্ত) {
                        যদি (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, রিক্ত, token);
                        }
                        token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ঘূৰাই S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = রিক্ত;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ধ্রুৱ ৱর্ণ *format_mime = "text/plain;charset=utf-8";
        যদি (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            যদি (SUCCEEDED(hres)) {
                ধ্রুৱ size_t bsize = GlobalSize(med.hGlobal);
                ধ্রুৱ শূন্য *buffer = (শূন্য *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                যদি (buffer) {
                    ৱর্ণ *text = (ৱর্ণ *)SDL_malloc(bsize + পরিমাণ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, পরিমাণ(Uint32));
                    ৱর্ণ *saveptr = রিক্ত;
                    ৱর্ণ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    যেতিয়ালৈ (token != রিক্ত) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ৱর্ণ *)token);
                        token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ঘূৰাই S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = রিক্ত;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ধ্রুৱ ৱর্ণ *format_mime = "CF_UNICODETEXT";
        যদি (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            যদি (SUCCEEDED(hres)) {
                ধ্রুৱ size_t bsize = GlobalSize(med.hGlobal);
                ধ্রুৱ শূন্য *buffer = (শূন্য *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                যদি (buffer) {
                    buffer = WIN_StringToUTF8W((ধ্রুৱ wchar_t *)buffer);
                    যদি (buffer) {
                        ধ্রুৱ size_t lbuffer = SDL_strlen((ধ্রুৱ ৱর্ণ *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        ৱর্ণ *text = (ৱর্ণ *)SDL_malloc(lbuffer + পরিমাণ(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, পরিমাণ(Uint32));
                        ৱর্ণ *saveptr = রিক্ত;
                        ৱর্ণ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        যেতিয়ালৈ (token != রিক্ত) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (ৱর্ণ *)token);
                            token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((শূন্য *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ঘূৰাই S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = রিক্ত;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ধ্রুৱ ৱর্ণ *format_mime = "CF_TEXT";
        যদি (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            যদি (SUCCEEDED(hres)) {
                ধ্রুৱ size_t bsize = GlobalSize(med.hGlobal);
                ধ্রুৱ শূন্য *buffer = (শূন্য *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                যদি (buffer) {
                    ৱর্ণ *text = (ৱর্ণ *)SDL_malloc(bsize + পরিমাণ(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, পরিমাণ(Uint32));
                    ৱর্ণ *saveptr = রিক্ত;
                    ৱর্ণ *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    যেতিয়ালৈ (token != রিক্ত) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ৱর্ণ *)token);
                        token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ঘূৰাই S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = রিক্ত;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ধ্রুৱ ৱর্ণ *format_mime = "CF_HDROP";
        যদি (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            যদি (SUCCEEDED(hres)) {
                ধ্রুৱ size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT গুনতি = DragQueryFile(drop, 0xFFFFFFFF, রিক্ত, 0);
                বাবে (UINT i = 0; i < গুনতি; ++i) {
                    UINT size = DragQueryFile(drop, i, রিক্ত, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * পরিমাণ(TCHAR));
                    যদি (buffer) {
                        যদি (DragQueryFile(drop, i, buffer, size)) {
                            ৱর্ণ *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, রিক্ত, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ঘূৰাই S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    ঘূৰাই S_OK;
}

স্থির শূন্য *vtDropTarget[] = {
    (শূন্য *)(SDLDropTarget_QueryInterface),
    (শূন্য *)(SDLDropTarget_AddRef),
    (শূন্য *)(SDLDropTarget_Release),
    (শূন্য *)(SDLDropTarget_DragEnter),
    (শূন্য *)(SDLDropTarget_DragOver),
    (শূন্য *)(SDLDropTarget_DragLeave),
    (শূন্য *)(SDLDropTarget_Drop)
};

শূন্য WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    যদি (data->videodata->oleinitialized) {
        যদি (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, পরিমাণ(SDLDropTarget));
            যদি (drop_target != রিক্ত) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } অন্যথা যদি (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = রিক্ত;
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } অন্যথা {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = পরিমাণ(desc);
    desc.hwnd = window->internal->hwnd;
    ৱিকল্প (operation) {
    পক্ষ SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ভঙ্গ;
    পক্ষ SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_গুনতি = 1;
        ভঙ্গ;
    পক্ষ SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ভঙ্গ;
    স্ৱভাৱ:
        ঘূৰাই SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    ঘূৰাই true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    যদি (!data->taskbar_button_created) {
        ঘূৰাই true;
    }

    যদি (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        ঘূৰাই true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    যদি (!taskbar_list) {
        ঘূৰাই false;
    }

    TBPFLAG tbpFlags;
    ৱিকল্প (window->progress_state) {
    পক্ষ SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ভঙ্গ;
    পক্ষ SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ভঙ্গ;
    পক্ষ SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        ভঙ্গ;
    পক্ষ SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ভঙ্গ;
    পক্ষ SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ভঙ্গ;
    স্ৱভাৱ:
        ঘূৰাই SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    যদি (FAILED(ret)) {
        ঘূৰাই WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    যদি (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_মান(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_মান * 10000.f), 10000);
        যদি (FAILED(ret)) {
            ঘূৰাই WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    ঘূৰাই true;
}

শূন্য WIN_ShowWindowSystemMenu(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    ধ্রুৱ SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    যদি (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        ধ্রুৱ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        যদি (focusable) {
            যদি (style & WS_EX_NOACTIVATE) {
                যদি (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ঘূৰাই WIN_SetError("SetWindowLong()");
                }
            }
        } অন্যথা {
            যদি (!(style & WS_EX_NOACTIVATE)) {
                যদি (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ঘূৰাই WIN_SetError("SetWindowLong()");
                }
            }
        }
    } অন্যথা যদি (window->flags & SDL_WINDOW_POPUP_MENU) {
        যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
            যদি (!focusable && (window->flags & SDL_WINDOW_প্ৰবেশ_FOCUS)) {
                SDL_Window *new_focus;
                ধ্রুৱ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } অন্যথা যদি (focusable) {
                যদি (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        ঘূৰাই true;
    }

    ঘূৰাই true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    ধ্রুৱ LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : রিক্ত);
    ধ্রুৱ DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    যদি (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } অন্যথা {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ঘূৰাই true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ধ্রুৱ HWND parent_hwnd = window->parent->internal->hwnd;

    যদি (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } অন্যথা যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ঘূৰাই true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
