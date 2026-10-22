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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#அந்தர்பாவ "../../core/windows/SDL_windows.h"

#அந்தர்பாவ "../../SDL_hints_c.h"
#அந்தர்பாவ "../../events/SDL_dropevents_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_windowevents_c.h"
#அந்தர்பாவ "../SDL_pixels_c.h"
#அந்தர்பாவ "../SDL_sysvideo.h"

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "SDL_windowskeyboard.h"
#அந்தர்பாவ "SDL_windowswindow.h"

// Dropfile support
#அந்தர்பாவ <shellapi.h>

#எனில் !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#அந்தர்பாவ <shobjidl.h>
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

நிலையான DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    எனில் (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } இல்லையெனில் எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } இல்லையெனில் {
        எனில் (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            எனில் (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } இல்லையெனில் {
                style |= STYLE_BORDERLESS;
            }
        } இல்லையெனில் {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        எனில் (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            எனில் (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        எனில் (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        எனில் (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    திரும்பு style;
}

நிலையான DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    எனில் (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    எனில் (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    திரும்பு style;
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
நிலையான ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    மாறிலி SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    எனில் (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, வெற்று, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        எனில் (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            திரும்பு வெற்று;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        எனில் (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = வெற்று;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            திரும்பு வெற்று;
        }
    }
    திரும்பு data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
நிலையான bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, முழு *x, முழு *y, முழு *width, முழு *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : வெற்று;
    RECT rect;

    // Client rect, in points
    தேர்வு (rect_type) {
    நிலை SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        நிறுத்து;
    நிலை SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        நிறுத்து;
    நிலை SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        நிறுத்து;
    நிலை SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        நிறுத்து;
    இயல்பு:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        நிறுத்து;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.இடது = 0;
    rect.உச்சி = 0;
    rect.வலது = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    எனில் (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#இல்லையெனில்
        எனில் (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            எனில் (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                எனில் (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    திரும்பு WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } இல்லையெனில் {
            எனில் (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                திரும்பு WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.இடது;
    *y += rect.உச்சி;
    *width = (rect.வலது - rect.இடது);
    *height = (rect.bottom - rect.உச்சி);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    திரும்பு true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, முழு *x, முழு *y, முழு *width, முழு *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#இல்லையெனில்
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != வெற்று);
#endif
    திரும்பு WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : வெற்று;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#இல்லையெனில்
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != வெற்று);
#endif

#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#இல்லையெனில்
    எனில் (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        எனில் (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        எனில் (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            திரும்பு WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } இல்லையெனில் {
        எனில் (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            திரும்பு WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    திரும்பு true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND உச்சி;
    முழு x, y;
    முழு w, h;
    bool result = true;

    // Figure out what the window area will be
    எனில் (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி)) {
        உச்சி = HWND_TOPMOST;
    } இல்லையெனில் {
        உச்சி = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    எனில் (SetWindowPos(hwnd, உச்சி, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    க்கு (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        எனில் (!child_window->internal) {
            // This child window is not yet fully initialized.
            தொடர்;
        }
        எனில் (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    திரும்பு result;
}

நிலையான SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(வெறுமை)
{
    மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    எனில் (!hint)
        திரும்பு SDL_ERASEBACKGROUNDMODE_INITIAL;

    எனில் (SDL_strstr(hint, "never"))
        திரும்பு SDL_ERASEBACKGROUNDMODE_NEVER;

    எனில் (SDL_strstr(hint, "initial"))
        திரும்பு SDL_ERASEBACKGROUNDMODE_INITIAL;

    எனில் (SDL_strstr(hint, "always"))
        திரும்பு SDL_ERASEBACKGROUNDMODE_ALWAYS;

    முழு mode = SDL_GetStringInteger(hint, 1);
    எனில் (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        திரும்பு SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    திரும்பு (SDL_WindowEraseBackgroundMode)mode;
}

நிலையான bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, அளவு(*data));
    எனில் (!data) {
        திரும்பு false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#இல்லையெனில்
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.இடது   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.உச்சி    = 0;
    data->cursor_ctrlock_rect.வலது  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    எனில் (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } இல்லையெனில் {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    எனில் (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        திரும்பு WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        எனில் (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#இல்லையெனில்
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        எனில் (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } இல்லையெனில் {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        எனில் (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } இல்லையெனில் {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        எனில் (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } இல்லையெனில் {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        எனில் (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } இல்லையெனில் எனில் (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        எனில் (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } இல்லையெனில்
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        எனில் (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } இல்லையெனில்
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    எனில் (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        எனில் (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            முழு w = rect.வலது;
            முழு h = rect.bottom;

            எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } இல்லையெனில் எனில் ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                முழு x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, வெற்று, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } இல்லையெனில் {
                window->w = w;
                window->h = h;
            }
        }
    }
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        எனில் (ClientToScreen(hwnd, &point)) {
            எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_உள்ளீடு_FOCUS;
    SDL_SetKeyboardFocus(window);
#இல்லையெனில்
    எனில் (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_உள்ளீடு_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    எனில் (window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி) {
        WIN_Set_Window_Always_On_உச்சி(_this, window, true);
    } இல்லையெனில் {
        WIN_Set_Window_Always_On_உச்சி(_this, window, false);
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    எனில் (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    எனில் (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        முழு titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        எனில் (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } இல்லையெனில் {
            titleLen = 0;
        }
        எனில் (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        எனில் (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    திரும்பு true;
}

நிலையான வெறுமை CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (data) {
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        எனில் (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        எனில் (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        எனில் (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        எனில் (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            எனில் (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } இல்லையெனில் {
            // Restore any original event handler...
            எனில் (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#இல்லையெனில்
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = வெற்று;
}

நிலையான வெறுமை WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    எனில் (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        முழு abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        முழு abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        மாறிலி முழு width = window->last_size_pending ? window->pending.w : window->floating.w;
        மாறிலி முழு height = window->last_size_pending ? window->pending.h : window->floating.h;
        முழு offset_x = 0, offset_y = 0;

        எனில் (window->constrain_popup) {
            // Calculate the total offset from the parents
            க்கு (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            எனில் (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            எனில் (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        எனில் (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } இல்லையெனில் {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

நிலையான வெறுமை WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    போது (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    எனில் (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", வெற்று));
    HWND parent = வெற்று;
    எனில் (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        எனில் (!SetupWindowData(_this, window, hwnd, parent)) {
            திரும்பு false;
        }
    } இல்லையெனில் {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        முழு x, y;
        முழு w, h;

        எனில் (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, வெற்று, வெற்று, SDL_Instance, வெற்று);
        } இல்லையெனில் எனில் (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_எண்_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_எண், GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, வெற்று, SDL_Instance, வெற்று);
        எனில் (!hwnd) {
            திரும்பு WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        எனில் (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            எனில் (parent) {
                DestroyWindow(parent);
            }
            திரும்பு false;
        }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_உள்ளீடு(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, வெற்று, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        எனில் (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    எனில் (window->flags & SDL_WINDOW_TRANSPARENT) {
        எனில் (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, வெற்று);
    எனில் (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        முழு pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, அளவு(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        எனில் (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            திரும்பு WIN_SetError("SetPixelFormat()");
        }
    } இல்லையெனில் {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        எனில் (!(window->flags & SDL_WINDOW_OPENGL)) {
            திரும்பு true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        எனில் ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            எனில் (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                திரும்பு false;
            }
            திரும்பு true;
#இல்லையெனில்
            திரும்பு SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        எனில் (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            திரும்பு false;
        }
#இல்லையெனில்
        திரும்பு SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    திரும்பு true;
}

வெறுமை WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = வெற்று;
    BYTE *icon_bmp;
    முழு icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, அளவு(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = அளவு(BITMAPINFOHEADER) + icon->h * icon->w * அளவு(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    எனில் (!icon_bmp) {
        திரும்பு false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(அளவு(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_மொத்தம் = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * அளவு(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[அளவு(BITMAPINFOHEADER)];
    row_len = icon->w * அளவு(Uint32);
    y = icon->h;
    போது (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    எனில் (!hicon) {
        திரும்பு SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned முழு)GetLastError());
    }

    எனில் (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    திரும்பு result;
#இல்லையெனில்
    திரும்பு SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        எனில் (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            திரும்பு WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } இல்லையெனில் {
        திரும்பு SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    திரும்பு true;
}

வெறுமை WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    எனில் (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } இல்லையெனில் {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, முழு *உச்சி, முழு *இடது, முழு *bottom, முழு *வலது)
{
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *உச்சி = rcClient.உச்சி;
    *இடது = rcClient.இடது;
    *bottom = rcClient.bottom;
    *வலது = rcClient.வலது;

    திரும்பு true;
#இல்லையெனில்  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    எனில் (!GetClientRect(hwnd, &rcClient)) {
        திரும்பு SDL_SetError("GetClientRect() failed, error %08X", (unsigned முழு)GetLastError());
    }

    எனில் (!GetWindowRect(hwnd, &rcWindow)) {
        திரும்பு SDL_SetError("GetWindowRect() failed, error %08X", (unsigned முழு)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.உச்சி;
    ptDiff.x = rcWindow.இடது;

    எனில் (!ScreenToClient(hwnd, &ptDiff)) {
        திரும்பு SDL_SetError("ScreenToClient() failed, error %08X", (unsigned முழு)GetLastError());
    }

    rcWindow.உச்சி = ptDiff.y;
    rcWindow.இடது = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.வலது;

    எனில் (!ScreenToClient(hwnd, &ptDiff)) {
        திரும்பு SDL_SetError("ScreenToClient() failed, error %08X", (unsigned முழு)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.வலது = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *உச்சி = rcClient.உச்சி - rcWindow.உச்சி;
    *இடது = rcClient.இடது - rcWindow.இடது;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *வலது = rcWindow.வலது - rcClient.வலது;

    திரும்பு true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

வெறுமை WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, முழு *w, முழு *h)
{
    மாறிலி SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    எனில் (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.வலது;
        *h = rect.bottom;
    } இல்லையெனில் எனில் (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } இல்லையெனில் {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

வெறுமை WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    எனில் (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    எனில் (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        எனில் (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    எனில் (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    எனில் (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } இல்லையெனில் {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, வெற்று, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    எனில் ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    எனில் (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

வெறுமை WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    எனில் (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    எனில் ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        மாறிலி bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

வெறுமை WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = வெற்று;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    எனில் (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, வெற்று);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_உள்ளீடு(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        எனில் (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    எனில் (bActivate) {
        SetForegroundWindow(hwnd);
        எனில் ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } இல்லையெனில் {
        SetWindowPos(hwnd, HWND_உச்சி, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    எனில் (bForce) {
        Attach_Thread_உள்ளீடு(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

வெறுமை WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        எனில் (window->max_w || window->max_h) {
            முழு fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_உச்சி, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } இல்லையெனில் {
        data->windowed_mode_was_maximized = true;
    }
}

வெறுமை WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

வெறுமை WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

வெறுமை WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

வெறுமை WIN_Set_Window_Always_On_உச்சி(SDL_VideoDevice *_this, SDL_Window *window, bool on_உச்சி)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

வெறுமை WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        எனில் (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } இல்லையெனில் {
        data->windowed_mode_was_maximized = false;
    }
}

நிலையான வெறுமை WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    எனில் (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, அளவு(cornerPref));
    }
#endif
}

நிலையான வெறுமை WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    எனில் (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, அளவு(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : வெற்று;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND உச்சி;
    முழு x, y;
    முழு w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (முழு)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        திரும்பு SDL_FULLSCREEN_SUCCEEDED;
    }

    எனில் (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி)) {
        உச்சி = HWND_TOPMOST;
    } இல்லையெனில் {
        உச்சி = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = அளவு(MONITORINFO);
    எனில் (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        திரும்பு SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    எனில் (fullscreen) {
        x = minfo.rcMonitor.இடது;
        y = minfo.rcMonitor.உச்சி;
        w = minfo.rcMonitor.வலது - minfo.rcMonitor.இடது;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.உச்சி;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        எனில் (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } இல்லையெனில் {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        எனில் (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != வெற்று);
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
        எனில் (enterMaximized) {
            மாறிலி SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            மாறிலி SDL_Point floating_point = { window->floating.x, window->floating.y };
            மாறிலி SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            மாறிலி SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            எனில் (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                எனில் (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } இல்லையெனில் {
                    x = bounds.x;
                }
                எனில் (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } இல்லையெனில் {
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
    SetWindowPos(hwnd, உச்சி, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    எனில் (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    எனில் (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (முழு)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    திரும்பு SDL_FULLSCREEN_SUCCEEDED;
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
வெறுமை WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    எனில் (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, வெற்று, வெற்று, வெற்று);
        எனில் (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            எனில் (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                எனில் (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    எனில் (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

வெறுமை *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    எழுத்து *filename_utf8;
    வெறுமை *iccProfileData = வெற்று;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    எனில் (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        எனில் (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    திரும்பு iccProfileData;
}

நிலையான வெறுமை WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    எனில் (data->keyboard_hook) {
        திரும்பு;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    எனில் (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        திரும்பு;
    }

    // Capture a snapshot of the current keyboard state before the hook
    எனில் (!GetKeyboardState(data->videodata->pre_hook_சாவி_state)) {
        திரும்பு;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

வெறுமை WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = வெற்று;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    திரும்பு true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    திரும்பு true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    எனில் (grabbed) {
        WIN_GrabKeyboard(window);
    } இல்லையெனில் {
        WIN_UngrabKeyboard(window);
    }

    திரும்பு true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

வெறுமை WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
வெறுமை WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (!data || !data->hwnd) {
        // The window wasn't fully initialized
        திரும்பு;
    }

    எனில் (window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

நிலையான BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    திரும்பு GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

வெறுமை WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    எனில் (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, அளவு(rect)) == 0) {
        ClipCursor(வெற்று);
        SDL_zero(data->cursor_clipped_rect);
    }
}

வெறுமை WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    எனில் (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        திரும்பு;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_உள்ளீடு_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    எனில் (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        எனில் (!GetClipCursor(&current)) {
            திரும்பு;
        }
        எனில் (videodevice && (
            current.இடது != videodevice->desktop_bounds.x ||
            current.உச்சி  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.இடது;
            first.y  = current.உச்சி;
            second.x = current.வலது  - 1;
            second.y = current.bottom - 1;
            எனில் (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                திரும்பு;
            }
        }
        ClipCursor(வெற்று);
        SDL_zero(data->cursor_clipped_rect);
        திரும்பு;
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
    எனில் (!GetClientScreenRect(data->hwnd, &client)) {
        திரும்பு;
    }

    RECT target = client;
    எனில் (lock_to_ctr) {
        LONG cx = (client.இடது + client.வலது ) / 2;
        LONG cy = (client.உச்சி  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.இடது   += cx;
        target.வலது  += cx;
        target.உச்சி    += cy;
        target.bottom += cy;
    } இல்லையெனில் எனில் (win_mouse_rect) {
        RECT custom, overlap;
        custom.இடது   = client.இடது + mouse_rect.x;
        custom.உச்சி    = client.உச்சி  + mouse_rect.y;
        custom.வலது  = client.இடது + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.உச்சி  + mouse_rect.y + mouse_rect.h;
        எனில் (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } இல்லையெனில் எனில் (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            திரும்பு;
        }
    } இல்லையெனில் எனில் (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        எனில் (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            எனில் (hmon) {
                UINT hdpi_uint, vdpi_uint;
                எனில் (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    மாறிலி தசம scale = (தசம)hdpi_uint / (தசம)USER_DEFAULT_SCREEN_DPI;
                    எனில் (scale != SDL_floorf(scale)) {
                        எனில் (target.இடது < target.வலது) {
                            target.இடது += 1;
                        }
                        எனில் (target.வலது > target.இடது) {
                            target.வலது -= 1;
                        }
                        எனில் (target.உச்சி < target.bottom) {
                            target.உச்சி += 1;
                        }
                        எனில் (target.bottom > target.உச்சி) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    எனில் (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, அளவு(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    திரும்பு true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, தசம opacity)
{
#எனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    திரும்பு false;
#இல்லையெனில்
    மாறிலி SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    மாறிலி LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    எனில் (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        எனில் (style & WS_EX_LAYERED) {
            எனில் (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                திரும்பு WIN_SetError("SetWindowLong()");
            }
        }
    } இல்லையெனில் {
        மாறிலி BYTE alpha = (BYTE)((முழு)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        எனில் (!(style & WS_EX_LAYERED)) {
            எனில் (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                திரும்பு WIN_SetError("SetWindowLong()");
            }
        }

        எனில் (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            திரும்பு WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    திரும்பு true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

நிலையான மாறிலி எழுத்து *SDLGetClipboardFormatName(UINT cf, எழுத்து *text, முழு len)
{
    தேர்வு (cf) {
    நிலை CF_TEXT:
        திரும்பு "CF_TEXT";
    நிலை CF_BITMAP:
        திரும்பு "CF_BITMAP";
    நிலை CF_METAFILEPICT:
        திரும்பு "CF_METAFILEPICT";
    நிலை CF_SYLK:
        திரும்பு "CF_SYLK";
    நிலை CF_DIF:
        திரும்பு "CF_DIF";
    நிலை CF_TIFF:
        திரும்பு "CF_TIFF";
    நிலை CF_OEMTEXT:
        திரும்பு "CF_OEMTEXT";
    நிலை CF_DIB:
        திரும்பு "CF_DIB";
    நிலை CF_PALETTE:
        திரும்பு "CF_PALETTE";
    நிலை CF_PENDATA:
        திரும்பு "CF_PENDATA";
    நிலை CF_RIFF:
        திரும்பு "CF_RIFF";
    நிலை CF_WAVE:
        திரும்பு "CF_WAVE";
    நிலை CF_UNICODETEXT:
        திரும்பு "CF_UNICODETEXT";
    நிலை CF_ENHMETAFILE:
        திரும்பு "CF_ENHMETAFILE";
    நிலை CF_HDROP:
        திரும்பு "CF_HDROP";
    நிலை CF_LOCALE:
        திரும்பு "CF_LOCALE";
    நிலை CF_DIBV5:
        திரும்பு "CF_DIBV5";
    நிலை CF_OWNERDISPLAY:
        திரும்பு "CF_OWNERDISPLAY";
    நிலை CF_DSPTEXT:
        திரும்பு "CF_DSPTEXT";
    நிலை CF_DSPBITMAP:
        திரும்பு "CF_DSPBITMAP";
    நிலை CF_DSPMETAFILEPICT:
        திரும்பு "CF_DSPMETAFILEPICT";
    நிலை CF_DSPENHMETAFILE:
        திரும்பு "CF_DSPENHMETAFILE";
    இயல்பு:
        எனில் (GetClipboardFormatNameA(cf, text, len)) {
            திரும்பு text;
        } இல்லையெனில் {
            திரும்பு வெற்று;
        }
    }
}

நிலையான STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    திரும்பு ++target->refcount;
}

நிலையான STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    எனில் (target->refcount == 0) {
        SDL_free(target);
        திரும்பு 0;
    }
    திரும்பு target->refcount;
}

நிலையான STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    எனில் (ppv == வெற்று) {
        திரும்பு E_INVALIDARG;
    }

    *ppv = வெற்று;
    எனில் (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (வெறுமை *)target;
    }
    எனில் (*ppv) {
        SDLDropTarget_AddRef(target);
        திரும்பு S_OK;
    }
    திரும்பு E_NOINTERFACE;
}

நிலையான STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_சாவி_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    எனில் (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    திரும்பு S_OK;
}

நிலையான STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_சாவி_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    எனில் (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    திரும்பு S_OK;
}

நிலையான STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    திரும்பு S_OK;
}

நிலையான STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_சாவி_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    எனில் (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        எனில் (hres == S_OK) {
            FORMATETC fetc;
            போது (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, வெற்று) == S_OK) {
                எழுத்து name[257] = { 0 };
                மாறிலி எழுத்து *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                எனில் (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } இல்லையெனில் {
                    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = வெற்று;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        மாறிலி எழுத்து *format_mime = "text/uri-list";
        எனில் (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            எனில் (SUCCEEDED(hres)) {
                மாறிலி size_t bsize = GlobalSize(med.hGlobal);
                மாறிலி வெறுமை *buffer = (வெறுமை *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                எனில் (buffer) {
                    எழுத்து *text = (எழுத்து *)SDL_malloc(bsize + அளவு(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, அளவு(Uint32));
                    எழுத்து *saveptr = வெற்று;
                    எழுத்து *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    போது (token != வெற்று) {
                        எனில் (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, வெற்று, token);
                        }
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                திரும்பு S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = வெற்று;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        மாறிலி எழுத்து *format_mime = "text/plain;charset=utf-8";
        எனில் (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            எனில் (SUCCEEDED(hres)) {
                மாறிலி size_t bsize = GlobalSize(med.hGlobal);
                மாறிலி வெறுமை *buffer = (வெறுமை *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                எனில் (buffer) {
                    எழுத்து *text = (எழுத்து *)SDL_malloc(bsize + அளவு(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, அளவு(Uint32));
                    எழுத்து *saveptr = வெற்று;
                    எழுத்து *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    போது (token != வெற்று) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (எழுத்து *)token);
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                திரும்பு S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = வெற்று;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        மாறிலி எழுத்து *format_mime = "CF_UNICODETEXT";
        எனில் (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            எனில் (SUCCEEDED(hres)) {
                மாறிலி size_t bsize = GlobalSize(med.hGlobal);
                மாறிலி வெறுமை *buffer = (வெறுமை *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                எனில் (buffer) {
                    buffer = WIN_StringToUTF8W((மாறிலி wchar_t *)buffer);
                    எனில் (buffer) {
                        மாறிலி size_t lbuffer = SDL_strlen((மாறிலி எழுத்து *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        எழுத்து *text = (எழுத்து *)SDL_malloc(lbuffer + அளவு(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, அளவு(Uint32));
                        எழுத்து *saveptr = வெற்று;
                        எழுத்து *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        போது (token != வெற்று) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (எழுத்து *)token);
                            token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((வெறுமை *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                திரும்பு S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = வெற்று;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        மாறிலி எழுத்து *format_mime = "CF_TEXT";
        எனில் (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            எனில் (SUCCEEDED(hres)) {
                மாறிலி size_t bsize = GlobalSize(med.hGlobal);
                மாறிலி வெறுமை *buffer = (வெறுமை *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                எனில் (buffer) {
                    எழுத்து *text = (எழுத்து *)SDL_malloc(bsize + அளவு(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, அளவு(Uint32));
                    எழுத்து *saveptr = வெற்று;
                    எழுத்து *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    போது (token != வெற்று) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (எழுத்து *)token);
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                திரும்பு S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = வெற்று;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        மாறிலி எழுத்து *format_mime = "CF_HDROP";
        எனில் (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            எனில் (SUCCEEDED(hres)) {
                மாறிலி size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT மொத்தம் = DragQueryFile(drop, 0xFFFFFFFF, வெற்று, 0);
                க்கு (UINT i = 0; i < மொத்தம்; ++i) {
                    UINT size = DragQueryFile(drop, i, வெற்று, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * அளவு(TCHAR));
                    எனில் (buffer) {
                        எனில் (DragQueryFile(drop, i, buffer, size)) {
                            எழுத்து *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, வெற்று, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                திரும்பு S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    திரும்பு S_OK;
}

நிலையான வெறுமை *vtDropTarget[] = {
    (வெறுமை *)(SDLDropTarget_QueryInterface),
    (வெறுமை *)(SDLDropTarget_AddRef),
    (வெறுமை *)(SDLDropTarget_Release),
    (வெறுமை *)(SDLDropTarget_DragEnter),
    (வெறுமை *)(SDLDropTarget_DragOver),
    (வெறுமை *)(SDLDropTarget_DragLeave),
    (வெறுமை *)(SDLDropTarget_Drop)
};

வெறுமை WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    எனில் (data->videodata->oleinitialized) {
        எனில் (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, அளவு(SDLDropTarget));
            எனில் (drop_target != வெற்று) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } இல்லையெனில் எனில் (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = வெற்று;
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } இல்லையெனில் {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = அளவு(desc);
    desc.hwnd = window->internal->hwnd;
    தேர்வு (operation) {
    நிலை SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        நிறுத்து;
    நிலை SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_மொத்தம் = 1;
        நிறுத்து;
    நிலை SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        நிறுத்து;
    இயல்பு:
        திரும்பு SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    திரும்பு true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    எனில் (!data->taskbar_button_created) {
        திரும்பு true;
    }

    எனில் (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        திரும்பு true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    எனில் (!taskbar_list) {
        திரும்பு false;
    }

    TBPFLAG tbpFlags;
    தேர்வு (window->progress_state) {
    நிலை SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        நிறுத்து;
    நிலை SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        நிறுத்து;
    நிலை SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        நிறுத்து;
    நிலை SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        நிறுத்து;
    நிலை SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        நிறுத்து;
    இயல்பு:
        திரும்பு SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    எனில் (FAILED(ret)) {
        திரும்பு WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    எனில் (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_மதிப்பு(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_மதிப்பு * 10000.f), 10000);
        எனில் (FAILED(ret)) {
            திரும்பு WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    திரும்பு true;
}

வெறுமை WIN_ShowWindowSystemMenu(SDL_Window *window, முழு x, முழு y)
{
    மாறிலி SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    எனில் (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        மாறிலி LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        எனில் (focusable) {
            எனில் (style & WS_EX_NOACTIVATE) {
                எனில் (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    திரும்பு WIN_SetError("SetWindowLong()");
                }
            }
        } இல்லையெனில் {
            எனில் (!(style & WS_EX_NOACTIVATE)) {
                எனில் (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    திரும்பு WIN_SetError("SetWindowLong()");
                }
            }
        }
    } இல்லையெனில் எனில் (window->flags & SDL_WINDOW_POPUP_MENU) {
        எனில் (!(window->flags & SDL_WINDOW_HIDDEN)) {
            எனில் (!focusable && (window->flags & SDL_WINDOW_உள்ளீடு_FOCUS)) {
                SDL_Window *new_focus;
                மாறிலி bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } இல்லையெனில் எனில் (focusable) {
                எனில் (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        திரும்பு true;
    }

    திரும்பு true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    மாறிலி LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : வெற்று);
    மாறிலி DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    எனில் (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } இல்லையெனில் {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    திரும்பு true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    மாறிலி HWND parent_hwnd = window->parent->internal->hwnd;

    எனில் (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } இல்லையெனில் எனில் (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
