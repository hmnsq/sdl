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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#ଅନ୍ତର୍ଭାଵ "../../core/windows/SDL_windows.h"

#ଅନ୍ତର୍ଭାଵ "../../SDL_hints_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_dropevents_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_windowevents_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowskeyboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowswindow.h"

// Dropfile support
#ଅନ୍ତର୍ଭାଵ <shellapi.h>

#ଯଦି !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ଅନ୍ତର୍ଭାଵ <shobjidl.h>
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

ସ୍ଥିର DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    ଯଦି (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ଅନ୍ୟଥା {
        ଯଦି (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ଯଦି (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ଅନ୍ୟଥା {
                style |= STYLE_BORDERLESS;
            }
        } ଅନ୍ୟଥା {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ଯଦି (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ଯଦି (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ଯଦି (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ଯଦି (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ଫେରନ୍ତୁ style;
}

ସ୍ଥିର DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    ଯଦି (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ଯଦି (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ଫେରନ୍ତୁ style;
}

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ସ୍ଥିର ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    ଅଚଳ SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    ଯଦି (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ଖାଲି, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        ଯଦି (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ଯଦି (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = ଖାଲି;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }
    ଫେରନ୍ତୁ data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ସ୍ଥିର bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : ଖାଲି;
    RECT rect;

    // Client rect, in points
    ବାଛ (rect_type) {
    ସ୍ଥିତି SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        ଭାଙ୍ଗ;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ବାମ = 0;
    rect.ଶୀର୍ଷ = 0;
    rect.ଡାହାଣ = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ଯଦି (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#ଅନ୍ୟଥା
        ଯଦି (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ଯଦି (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ଯଦି (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    ଫେରନ୍ତୁ WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } ଅନ୍ୟଥା {
            ଯଦି (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                ଫେରନ୍ତୁ WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ବାମ;
    *y += rect.ଶୀର୍ଷ;
    *width = (rect.ଡାହାଣ - rect.ବାମ);
    *height = (rect.bottom - rect.ଶୀର୍ଷ);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    ଫେରନ୍ତୁ true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ଅନ୍ୟଥା
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ଖାଲି);
#endif
    ଫେରନ୍ତୁ WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : ଖାଲି;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ଅନ୍ୟଥା
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ଖାଲି);
#endif

#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#ଅନ୍ୟଥା
    ଯଦି (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ଯଦି (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ଯଦି (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            ଫେରନ୍ତୁ WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } ଅନ୍ୟଥା {
        ଯଦି (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            ଫେରନ୍ତୁ WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    ଫେରନ୍ତୁ true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND ଶୀର୍ଷ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
    bool result = true;

    // Figure out what the window area will be
    ଯଦି (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ)) {
        ଶୀର୍ଷ = HWND_TOPMOST;
    } ଅନ୍ୟଥା {
        ଶୀର୍ଷ = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    ଯଦି (SetWindowPos(hwnd, ଶୀର୍ଷ, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    ପାଇଁ (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        ଯଦି (!child_window->internal) {
            // This child window is not yet fully initialized.
            ଜାରି;
        }
        ଯଦି (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(ଶୂନ୍ୟ)
{
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    ଯଦି (!hint)
        ଫେରନ୍ତୁ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ଯଦି (SDL_strstr(hint, "never"))
        ଫେରନ୍ତୁ SDL_ERASEBACKGROUNDMODE_NEVER;

    ଯଦି (SDL_strstr(hint, "initial"))
        ଫେରନ୍ତୁ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ଯଦି (SDL_strstr(hint, "always"))
        ଫେରନ୍ତୁ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mode = SDL_GetStringInteger(hint, 1);
    ଯଦି (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ଫେରନ୍ତୁ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ଫେରନ୍ତୁ (SDL_WindowEraseBackgroundMode)mode;
}

ସ୍ଥିର bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, ଆକାର(*data));
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#ଅନ୍ୟଥା
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.ବାମ   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.ଶୀର୍ଷ    = 0;
    data->cursor_ctrlock_rect.ଡାହାଣ  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    ଯଦି (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } ଅନ୍ୟଥା {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ଯଦି (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        ଫେରନ୍ତୁ WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        ଯଦି (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#ଅନ୍ୟଥା
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        ଯଦି (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } ଅନ୍ୟଥା {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        ଯଦି (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } ଅନ୍ୟଥା {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        ଯଦି (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } ଅନ୍ୟଥା {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        ଯଦି (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ଅନ୍ୟଥା ଯଦି (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        ଯଦି (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } ଅନ୍ୟଥା
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        ଯଦି (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } ଅନ୍ୟଥା
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    ଯଦି (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        ଯଦି (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = rect.ଡାହାଣ;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = rect.bottom;

            ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } ଅନ୍ୟଥା ଯଦି ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, ଖାଲି, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } ଅନ୍ୟଥା {
                window->w = w;
                window->h = h;
            }
        }
    }
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ଯଦି (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        ଯଦି (ClientToScreen(hwnd, &point)) {
            ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_ନିବେଶ_FOCUS;
    SDL_SetKeyboardFocus(window);
#ଅନ୍ୟଥା
    ଯଦି (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_ନିବେଶ_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    ଯଦି (window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ) {
        WIN_Set_Window_Always_On_ଶୀର୍ଷ(_this, window, true);
    } ଅନ୍ୟଥା {
        WIN_Set_Window_Always_On_ଶୀର୍ଷ(_this, window, false);
    }

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ଯଦି (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    ଯଦି (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ଯଦି (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } ଅନ୍ୟଥା {
            titleLen = 0;
        }
        ଯଦି (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        ଯଦି (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (data) {
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ଯଦି (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        ଯଦି (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        ଯଦି (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        ଯଦି (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            ଯଦି (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } ଅନ୍ୟଥା {
            // Restore any original event handler...
            ଯଦି (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#ଅନ୍ୟଥା
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    ଯଦି (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = window->last_size_pending ? window->pending.w : window->floating.w;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = window->last_size_pending ? window->pending.h : window->floating.h;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_x = 0, offset_y = 0;

        ଯଦି (window->constrain_popup) {
            // Calculate the total offset from the parents
            ପାଇଁ (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            ଯଦି (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            ଯଦି (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ଯଦି (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } ଅନ୍ୟଥା {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    ଯେତେବେଳେ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    ଯଦି (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", ଖାଲି));
    HWND parent = ଖାଲି;
    ଯଦି (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        ଯଦି (!SetupWindowData(_this, window, hwnd, parent)) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

        ଯଦି (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, ଖାଲି, ଖାଲି, SDL_Instance, ଖାଲି);
        } ଅନ୍ୟଥା ଯଦି (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_ସଂଖ୍ୟା_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_ସଂଖ୍ୟା, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, ଖାଲି, SDL_Instance, ଖାଲି);
        ଯଦି (!hwnd) {
            ଫେରନ୍ତୁ WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ଯଦି (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            ଯଦି (parent) {
                DestroyWindow(parent);
            }
            ଫେରନ୍ତୁ false;
        }

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_ନିବେଶ(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, ଖାଲି, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ଯଦି (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ଯଦି (window->flags & SDL_WINDOW_TRANSPARENT) {
        ଯଦି (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, ଖାଲି);
    ଯଦି (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, ଆକାର(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ଯଦି (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            ଫେରନ୍ତୁ WIN_SetError("SetPixelFormat()");
        }
    } ଅନ୍ୟଥା {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ଯଦି (!(window->flags & SDL_WINDOW_OPENGL)) {
            ଫେରନ୍ତୁ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        ଯଦି ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            ଯଦି (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                ଫେରନ୍ତୁ false;
            }
            ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
            ଫେରନ୍ତୁ SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        ଯଦି (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            ଫେରନ୍ତୁ false;
        }
#ଅନ୍ୟଥା
        ଫେରନ୍ତୁ SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = ଖାଲି;
    BYTE *icon_bmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, ଆକାର(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = ଆକାର(BITMAPINFOHEADER) + icon->h * icon->w * ଆକାର(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ଯଦି (!icon_bmp) {
        ଫେରନ୍ତୁ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(ଆକାର(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_ଗଣନା = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * ଆକାର(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[ଆକାର(BITMAPINFOHEADER)];
    row_len = icon->w * ଆକାର(Uint32);
    y = icon->h;
    ଯେତେବେଳେ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ଯଦି (!hicon) {
        ଫେରନ୍ତୁ SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)GetLastError());
    }

    ଯଦି (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ଫେରନ୍ତୁ result;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ଯଦି (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            ଫେରନ୍ତୁ WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଯଦି (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ଅନ୍ୟଥା {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bottom, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଡାହାଣ)
{
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *ଶୀର୍ଷ = rcClient.ଶୀର୍ଷ;
    *ବାମ = rcClient.ବାମ;
    *bottom = rcClient.bottom;
    *ଡାହାଣ = rcClient.ଡାହାଣ;

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ଯଦି (!GetClientRect(hwnd, &rcClient)) {
        ଫେରନ୍ତୁ SDL_SetError("GetClientRect() failed, error %08X", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)GetLastError());
    }

    ଯଦି (!GetWindowRect(hwnd, &rcWindow)) {
        ଫେରନ୍ତୁ SDL_SetError("GetWindowRect() failed, error %08X", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.ଶୀର୍ଷ;
    ptDiff.x = rcWindow.ବାମ;

    ଯଦି (!ScreenToClient(hwnd, &ptDiff)) {
        ଫେରନ୍ତୁ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)GetLastError());
    }

    rcWindow.ଶୀର୍ଷ = ptDiff.y;
    rcWindow.ବାମ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.ଡାହାଣ;

    ଯଦି (!ScreenToClient(hwnd, &ptDiff)) {
        ଫେରନ୍ତୁ SDL_SetError("ScreenToClient() failed, error %08X", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.ଡାହାଣ = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *ଶୀର୍ଷ = rcClient.ଶୀର୍ଷ - rcWindow.ଶୀର୍ଷ;
    *ବାମ = rcClient.ବାମ - rcWindow.ବାମ;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *ଡାହାଣ = rcWindow.ଡାହାଣ - rcClient.ଡାହାଣ;

    ଫେରନ୍ତୁ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ଶୂନ୍ୟ WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h)
{
    ଅଚଳ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    ଯଦି (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.ଡାହାଣ;
        *h = rect.bottom;
    } ଅନ୍ୟଥା ଯଦି (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } ଅନ୍ୟଥା {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

ଶୂନ୍ୟ WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    ଯଦି (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ଯଦି (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        ଯଦି (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    ଯଦି (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    ଯଦି (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } ଅନ୍ୟଥା {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, ଖାଲି, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    ଯଦି ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    ଯଦି (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

ଶୂନ୍ୟ WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    ଯଦି (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ଯଦି ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ଅଚଳ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

ଶୂନ୍ୟ WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = ଖାଲି;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ଯଦି (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, ଖାଲି);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_ନିବେଶ(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ଯଦି (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ଯଦି (bActivate) {
        SetForegroundWindow(hwnd);
        ଯଦି ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } ଅନ୍ୟଥା {
        SetWindowPos(hwnd, HWND_ଶୀର୍ଷ, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ଯଦି (bForce) {
        Attach_Thread_ନିବେଶ(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ଶୂନ୍ୟ WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ଯଦି (window->max_w || window->max_h) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_ଶୀର୍ଷ, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } ଅନ୍ୟଥା {
        data->windowed_mode_was_maximized = true;
    }
}

ଶୂନ୍ୟ WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

ଶୂନ୍ୟ WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

ଶୂନ୍ୟ WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

ଶୂନ୍ୟ WIN_Set_Window_Always_On_ଶୀର୍ଷ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ଶୀର୍ଷ)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

ଶୂନ୍ୟ WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        ଯଦି (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } ଅନ୍ୟଥା {
        data->windowed_mode_was_maximized = false;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ଯଦି (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, ଆକାର(cornerPref));
    }
#endif
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    ଯଦି (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, ଆକାର(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : ଖାଲି;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND ଶୀର୍ଷ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
    }

    ଯଦି (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ)) {
        ଶୀର୍ଷ = HWND_TOPMOST;
    } ଅନ୍ୟଥା {
        ଶୀର୍ଷ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = ଆକାର(MONITORINFO);
    ଯଦି (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    ଯଦି (fullscreen) {
        x = minfo.rcMonitor.ବାମ;
        y = minfo.rcMonitor.ଶୀର୍ଷ;
        w = minfo.rcMonitor.ଡାହାଣ - minfo.rcMonitor.ବାମ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.ଶୀର୍ଷ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ଯଦି (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ଅନ୍ୟଥା {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ଯଦି (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ଖାଲି);
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
        ଯଦି (enterMaximized) {
            ଅଚଳ SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            ଅଚଳ SDL_Point floating_point = { window->floating.x, window->floating.y };
            ଅଚଳ SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ଅଚଳ SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            ଯଦି (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ଯଦି (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ଅନ୍ୟଥା {
                    x = bounds.x;
                }
                ଯଦି (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ଅନ୍ୟଥା {
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
    SetWindowPos(hwnd, ଶୀର୍ଷ, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    ଯଦି (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    ଯଦି (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
}

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ଶୂନ୍ୟ WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    ଯଦି (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ଖାଲି, ଖାଲି, ଖାଲି);
        ଯଦି (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            ଯଦି (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                ଯଦି (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    ଯଦି (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

ଶୂନ୍ୟ *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    ଅକ୍ଷର *filename_utf8;
    ଶୂନ୍ୟ *iccProfileData = ଖାଲି;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    ଯଦି (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        ଯଦି (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ଫେରନ୍ତୁ iccProfileData;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    ଯଦି (data->keyboard_hook) {
        ଫେରନ୍ତୁ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ଯଦି (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ଫେରନ୍ତୁ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ଯଦି (!GetKeyboardState(data->videodata->pre_hook_ଚାବି_state)) {
        ଫେରନ୍ତୁ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

ଶୂନ୍ୟ WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = ଖାଲି;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    ଫେରନ୍ତୁ true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    ଫେରନ୍ତୁ true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    ଯଦି (grabbed) {
        WIN_GrabKeyboard(window);
    } ଅନ୍ୟଥା {
        WIN_UngrabKeyboard(window);
    }

    ଫେରନ୍ତୁ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ଶୂନ୍ୟ WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ଶୂନ୍ୟ WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (!data || !data->hwnd) {
        // The window wasn't fully initialized
        ଫେରନ୍ତୁ;
    }

    ଯଦି (window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ସ୍ଥିର BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ଫେରନ୍ତୁ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

ଶୂନ୍ୟ WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    ଯଦି (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, ଆକାର(rect)) == 0) {
        ClipCursor(ଖାଲି);
        SDL_zero(data->cursor_clipped_rect);
    }
}

ଶୂନ୍ୟ WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    ଯଦି (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        ଫେରନ୍ତୁ;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_ନିବେଶ_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ଯଦି (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ଯଦି (!GetClipCursor(&current)) {
            ଫେରନ୍ତୁ;
        }
        ଯଦି (videodevice && (
            current.ବାମ != videodevice->desktop_bounds.x ||
            current.ଶୀର୍ଷ  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.ବାମ;
            first.y  = current.ଶୀର୍ଷ;
            second.x = current.ଡାହାଣ  - 1;
            second.y = current.bottom - 1;
            ଯଦି (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                ଫେରନ୍ତୁ;
            }
        }
        ClipCursor(ଖାଲି);
        SDL_zero(data->cursor_clipped_rect);
        ଫେରନ୍ତୁ;
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
    ଯଦି (!GetClientScreenRect(data->hwnd, &client)) {
        ଫେରନ୍ତୁ;
    }

    RECT target = client;
    ଯଦି (lock_to_ctr) {
        LONG cx = (client.ବାମ + client.ଡାହାଣ ) / 2;
        LONG cy = (client.ଶୀର୍ଷ  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.ବାମ   += cx;
        target.ଡାହାଣ  += cx;
        target.ଶୀର୍ଷ    += cy;
        target.bottom += cy;
    } ଅନ୍ୟଥା ଯଦି (win_mouse_rect) {
        RECT custom, overlap;
        custom.ବାମ   = client.ବାମ + mouse_rect.x;
        custom.ଶୀର୍ଷ    = client.ଶୀର୍ଷ  + mouse_rect.y;
        custom.ଡାହାଣ  = client.ବାମ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.ଶୀର୍ଷ  + mouse_rect.y + mouse_rect.h;
        ଯଦି (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } ଅନ୍ୟଥା ଯଦି (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            ଫେରନ୍ତୁ;
        }
    } ଅନ୍ୟଥା ଯଦି (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ଯଦି (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            ଯଦି (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ଯଦି (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ଅଚଳ ଦଶମିକ scale = (ଦଶମିକ)hdpi_uint / (ଦଶମିକ)USER_DEFAULT_SCREEN_DPI;
                    ଯଦି (scale != SDL_floorf(scale)) {
                        ଯଦି (target.ବାମ < target.ଡାହାଣ) {
                            target.ବାମ += 1;
                        }
                        ଯଦି (target.ଡାହାଣ > target.ବାମ) {
                            target.ଡାହାଣ -= 1;
                        }
                        ଯଦି (target.ଶୀର୍ଷ < target.bottom) {
                            target.ଶୀର୍ଷ += 1;
                        }
                        ଯଦି (target.bottom > target.ଶୀର୍ଷ) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ଯଦି (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, ଆକାର(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    ଫେରନ୍ତୁ true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ opacity)
{
#ଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ଫେରନ୍ତୁ false;
#ଅନ୍ୟଥା
    ଅଚଳ SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ଅଚଳ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    ଯଦି (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ଯଦି (style & WS_EX_LAYERED) {
            ଯଦି (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ଫେରନ୍ତୁ WIN_SetError("SetWindowLong()");
            }
        }
    } ଅନ୍ୟଥା {
        ଅଚଳ BYTE alpha = (BYTE)((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ଯଦି (!(style & WS_EX_LAYERED)) {
            ଯଦି (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ଫେରନ୍ତୁ WIN_SetError("SetWindowLong()");
            }
        }

        ଯଦି (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ଫେରନ୍ତୁ WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    ଫେରନ୍ତୁ true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *SDLGetClipboardFormatName(UINT cf, ଅକ୍ଷର *text, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ବାଛ (cf) {
    ସ୍ଥିତି CF_TEXT:
        ଫେରନ୍ତୁ "CF_TEXT";
    ସ୍ଥିତି CF_BITMAP:
        ଫେରନ୍ତୁ "CF_BITMAP";
    ସ୍ଥିତି CF_METAFILEPICT:
        ଫେରନ୍ତୁ "CF_METAFILEPICT";
    ସ୍ଥିତି CF_SYLK:
        ଫେରନ୍ତୁ "CF_SYLK";
    ସ୍ଥିତି CF_DIF:
        ଫେରନ୍ତୁ "CF_DIF";
    ସ୍ଥିତି CF_TIFF:
        ଫେରନ୍ତୁ "CF_TIFF";
    ସ୍ଥିତି CF_OEMTEXT:
        ଫେରନ୍ତୁ "CF_OEMTEXT";
    ସ୍ଥିତି CF_DIB:
        ଫେରନ୍ତୁ "CF_DIB";
    ସ୍ଥିତି CF_PALETTE:
        ଫେରନ୍ତୁ "CF_PALETTE";
    ସ୍ଥିତି CF_PENDATA:
        ଫେରନ୍ତୁ "CF_PENDATA";
    ସ୍ଥିତି CF_RIFF:
        ଫେରନ୍ତୁ "CF_RIFF";
    ସ୍ଥିତି CF_WAVE:
        ଫେରନ୍ତୁ "CF_WAVE";
    ସ୍ଥିତି CF_UNICODETEXT:
        ଫେରନ୍ତୁ "CF_UNICODETEXT";
    ସ୍ଥିତି CF_ENHMETAFILE:
        ଫେରନ୍ତୁ "CF_ENHMETAFILE";
    ସ୍ଥିତି CF_HDROP:
        ଫେରନ୍ତୁ "CF_HDROP";
    ସ୍ଥିତି CF_LOCALE:
        ଫେରନ୍ତୁ "CF_LOCALE";
    ସ୍ଥିତି CF_DIBV5:
        ଫେରନ୍ତୁ "CF_DIBV5";
    ସ୍ଥିତି CF_OWNERDISPLAY:
        ଫେରନ୍ତୁ "CF_OWNERDISPLAY";
    ସ୍ଥିତି CF_DSPTEXT:
        ଫେରନ୍ତୁ "CF_DSPTEXT";
    ସ୍ଥିତି CF_DSPBITMAP:
        ଫେରନ୍ତୁ "CF_DSPBITMAP";
    ସ୍ଥିତି CF_DSPMETAFILEPICT:
        ଫେରନ୍ତୁ "CF_DSPMETAFILEPICT";
    ସ୍ଥିତି CF_DSPENHMETAFILE:
        ଫେରନ୍ତୁ "CF_DSPENHMETAFILE";
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଯଦି (GetClipboardFormatNameA(cf, text, len)) {
            ଫେରନ୍ତୁ text;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }
}

ସ୍ଥିର STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    ଫେରନ୍ତୁ ++target->refcount;
}

ସ୍ଥିର STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    ଯଦି (target->refcount == 0) {
        SDL_free(target);
        ଫେରନ୍ତୁ 0;
    }
    ଫେରନ୍ତୁ target->refcount;
}

ସ୍ଥିର STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    ଯଦି (ppv == ଖାଲି) {
        ଫେରନ୍ତୁ E_INVALIDARG;
    }

    *ppv = ଖାଲି;
    ଯଦି (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (ଶୂନ୍ୟ *)target;
    }
    ଯଦି (*ppv) {
        SDLDropTarget_AddRef(target);
        ଫେରନ୍ତୁ S_OK;
    }
    ଫେରନ୍ତୁ E_NOINTERFACE;
}

ସ୍ଥିର STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_ଚାବି_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ଯଦି (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ଫେରନ୍ତୁ S_OK;
}

ସ୍ଥିର STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_ଚାବି_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ଯଦି (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ଫେରନ୍ତୁ S_OK;
}

ସ୍ଥିର STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    ଫେରନ୍ତୁ S_OK;
}

ସ୍ଥିର STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_ଚାବି_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    ଯଦି (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ଯଦି (hres == S_OK) {
            FORMATETC fetc;
            ଯେତେବେଳେ (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, ଖାଲି) == S_OK) {
                ଅକ୍ଷର name[257] = { 0 };
                ଅଚଳ ଅକ୍ଷର *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ଯଦି (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ଅନ୍ୟଥା {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = ଖାଲି;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ଅଚଳ ଅକ୍ଷର *format_mime = "text/uri-list";
        ଯଦି (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ଯଦି (SUCCEEDED(hres)) {
                ଅଚଳ size_t bsize = GlobalSize(med.hGlobal);
                ଅଚଳ ଶୂନ୍ୟ *buffer = (ଶୂନ୍ୟ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ଯଦି (buffer) {
                    ଅକ୍ଷର *text = (ଅକ୍ଷର *)SDL_malloc(bsize + ଆକାର(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ଆକାର(Uint32));
                    ଅକ୍ଷର *saveptr = ଖାଲି;
                    ଅକ୍ଷର *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ଯେତେବେଳେ (token != ଖାଲି) {
                        ଯଦି (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, ଖାଲି, token);
                        }
                        token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ଫେରନ୍ତୁ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = ଖାଲି;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ଅଚଳ ଅକ୍ଷର *format_mime = "text/plain;charset=utf-8";
        ଯଦି (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ଯଦି (SUCCEEDED(hres)) {
                ଅଚଳ size_t bsize = GlobalSize(med.hGlobal);
                ଅଚଳ ଶୂନ୍ୟ *buffer = (ଶୂନ୍ୟ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ଯଦି (buffer) {
                    ଅକ୍ଷର *text = (ଅକ୍ଷର *)SDL_malloc(bsize + ଆକାର(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ଆକାର(Uint32));
                    ଅକ୍ଷର *saveptr = ଖାଲି;
                    ଅକ୍ଷର *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ଯେତେବେଳେ (token != ଖାଲି) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ଅକ୍ଷର *)token);
                        token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ଫେରନ୍ତୁ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ଖାଲି;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ଅଚଳ ଅକ୍ଷର *format_mime = "CF_UNICODETEXT";
        ଯଦି (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ଯଦି (SUCCEEDED(hres)) {
                ଅଚଳ size_t bsize = GlobalSize(med.hGlobal);
                ଅଚଳ ଶୂନ୍ୟ *buffer = (ଶୂନ୍ୟ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ଯଦି (buffer) {
                    buffer = WIN_StringToUTF8W((ଅଚଳ wchar_t *)buffer);
                    ଯଦି (buffer) {
                        ଅଚଳ size_t lbuffer = SDL_strlen((ଅଚଳ ଅକ୍ଷର *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        ଅକ୍ଷର *text = (ଅକ୍ଷର *)SDL_malloc(lbuffer + ଆକାର(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, ଆକାର(Uint32));
                        ଅକ୍ଷର *saveptr = ଖାଲି;
                        ଅକ୍ଷର *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        ଯେତେବେଳେ (token != ଖାଲି) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (ଅକ୍ଷର *)token);
                            token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((ଶୂନ୍ୟ *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ଫେରନ୍ତୁ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = ଖାଲି;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ଅଚଳ ଅକ୍ଷର *format_mime = "CF_TEXT";
        ଯଦି (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ଯଦି (SUCCEEDED(hres)) {
                ଅଚଳ size_t bsize = GlobalSize(med.hGlobal);
                ଅଚଳ ଶୂନ୍ୟ *buffer = (ଶୂନ୍ୟ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                ଯଦି (buffer) {
                    ଅକ୍ଷର *text = (ଅକ୍ଷର *)SDL_malloc(bsize + ଆକାର(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, ଆକାର(Uint32));
                    ଅକ୍ଷର *saveptr = ଖାଲି;
                    ଅକ୍ଷର *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    ଯେତେବେଳେ (token != ଖାଲି) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (ଅକ୍ଷର *)token);
                        token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ଫେରନ୍ତୁ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ଖାଲି;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ଅଚଳ ଅକ୍ଷର *format_mime = "CF_HDROP";
        ଯଦି (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ଯଦି (SUCCEEDED(hres)) {
                ଅଚଳ size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT ଗଣନା_2 = DragQueryFile(drop, 0xFFFFFFFF, ଖାଲି, 0);
                ପାଇଁ (UINT i = 0; i < ଗଣନା_2; ++i) {
                    UINT size = DragQueryFile(drop, i, ଖାଲି, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * ଆକାର(TCHAR));
                    ଯଦି (buffer) {
                        ଯଦି (DragQueryFile(drop, i, buffer, size)) {
                            ଅକ୍ଷର *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, ଖାଲି, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                ଫେରନ୍ତୁ S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    ଫେରନ୍ତୁ S_OK;
}

ସ୍ଥିର ଶୂନ୍ୟ *vtDropTarget[] = {
    (ଶୂନ୍ୟ *)(SDLDropTarget_QueryInterface),
    (ଶୂନ୍ୟ *)(SDLDropTarget_AddRef),
    (ଶୂନ୍ୟ *)(SDLDropTarget_Release),
    (ଶୂନ୍ୟ *)(SDLDropTarget_DragEnter),
    (ଶୂନ୍ୟ *)(SDLDropTarget_DragOver),
    (ଶୂନ୍ୟ *)(SDLDropTarget_DragLeave),
    (ଶୂନ୍ୟ *)(SDLDropTarget_Drop)
};

ଶୂନ୍ୟ WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    ଯଦି (data->videodata->oleinitialized) {
        ଯଦି (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, ଆକାର(SDLDropTarget));
            ଯଦି (drop_target != ଖାଲି) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } ଅନ୍ୟଥା ଯଦି (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = ଖାଲି;
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } ଅନ୍ୟଥା {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = ଆକାର(desc);
    desc.hwnd = window->internal->hwnd;
    ବାଛ (operation) {
    ସ୍ଥିତି SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_ଗଣନା = 1;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    ଫେରନ୍ତୁ true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    ଯଦି (!data->taskbar_button_created) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        ଫେରନ୍ତୁ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    ଯଦି (!taskbar_list) {
        ଫେରନ୍ତୁ false;
    }

    TBPFLAG tbpFlags;
    ବାଛ (window->progress_state) {
    ସ୍ଥିତି SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    ଯଦି (FAILED(ret)) {
        ଫେରନ୍ତୁ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ଯଦି (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_ମୂଲ୍ୟ(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_ମୂଲ୍ୟ * 10000.f), 10000);
        ଯଦି (FAILED(ret)) {
            ଫେରନ୍ତୁ WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ WIN_ShowWindowSystemMenu(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    ଅଚଳ SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    ଯଦି (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        ଅଚଳ LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ଯଦି (focusable) {
            ଯଦି (style & WS_EX_NOACTIVATE) {
                ଯଦି (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ଫେରନ୍ତୁ WIN_SetError("SetWindowLong()");
                }
            }
        } ଅନ୍ୟଥା {
            ଯଦି (!(style & WS_EX_NOACTIVATE)) {
                ଯଦି (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ଫେରନ୍ତୁ WIN_SetError("SetWindowLong()");
                }
            }
        }
    } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_POPUP_MENU) {
        ଯଦି (!(window->flags & SDL_WINDOW_HIDDEN)) {
            ଯଦି (!focusable && (window->flags & SDL_WINDOW_ନିବେଶ_FOCUS)) {
                SDL_Window *new_focus;
                ଅଚଳ bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } ଅନ୍ୟଥା ଯଦି (focusable) {
                ଯଦି (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        ଫେରନ୍ତୁ true;
    }

    ଫେରନ୍ତୁ true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    ଅଚଳ LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : ଖାଲି);
    ଅଚଳ DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    ଯଦି (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } ଅନ୍ୟଥା {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ଫେରନ୍ତୁ true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ଅଚଳ HWND parent_hwnd = window->parent->internal->hwnd;

    ଯଦି (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } ଅନ୍ୟଥା ଯଦି (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ଫେରନ୍ତୁ true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
