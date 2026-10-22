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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "../../SDL_hints_c.h"
#ضمن "../../events/SDL_dropevents_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowskeyboard.h"
#ضمن "SDL_windowswindow.h"

// Dropfile support
#ضمن <shellapi.h>

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ضمن <shobjidl.h>
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

ساكن DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    إذا (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } وإلا إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وإلا {
        إذا (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            إذا (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } وإلا {
                style |= STYLE_BORDERLESS;
            }
        } وإلا {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        إذا (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            إذا (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        إذا (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        إذا (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    أرجع style;
}

ساكن DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    إذا (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    إذا (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    أرجع style;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    ثابت SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    إذا (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, عدم, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        إذا (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            أرجع عدم;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        إذا (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = عدم;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            أرجع عدم;
        }
    }
    أرجع data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساكن bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, صحيح *x, صحيح *y, صحيح *width, صحيح *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : عدم;
    RECT rect;

    // Client rect, in points
    بدل (rect_type) {
    حالة SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        اكسر;
    حالة SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        اكسر;
    حالة SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        اكسر;
    حالة SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        اكسر;
    افتراضي:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        اكسر;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.کيري = 0;
    rect.اتس = 0;
    rect.کانن = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    إذا (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#وإلا
        إذا (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            إذا (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                إذا (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    أرجع WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } وإلا {
            إذا (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                أرجع WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.کيري;
    *y += rect.اتس;
    *width = (rect.کانن - rect.کيري);
    *height = (rect.bottom - rect.اتس);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    أرجع true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, صحيح *x, صحيح *y, صحيح *width, صحيح *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#endif
    أرجع WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : عدم;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#endif

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#وإلا
    إذا (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        إذا (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        إذا (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            أرجع WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } وإلا {
        إذا (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            أرجع WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    أرجع true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND اتس;
    صحيح x, y;
    صحيح w, h;
    bool result = true;

    // Figure out what the window area will be
    إذا (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_اتس)) {
        اتس = HWND_TOPMOST;
    } وإلا {
        اتس = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    إذا (SetWindowPos(hwnd, اتس, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    لكل (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        إذا (!child_window->internal) {
            // This child window is not yet fully initialized.
            استمر;
        }
        إذا (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    أرجع result;
}

ساكن SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    إذا (!hint)
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "never"))
        أرجع SDL_ERASEBACKGROUNDMODE_NEVER;

    إذا (SDL_strstr(hint, "initial"))
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "always"))
        أرجع SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحيح mode = SDL_GetStringInteger(hint, 1);
    إذا (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    أرجع (SDL_WindowEraseBackgroundMode)mode;
}

ساكن bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, حجم(*data));
    إذا (!data) {
        أرجع false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#وإلا
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.کيري   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.اتس    = 0;
    data->cursor_ctrlock_rect.کانن  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    إذا (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } وإلا {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    إذا (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        أرجع WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    إذا (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        إذا (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#وإلا
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        إذا (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } وإلا {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        إذا (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } وإلا {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        إذا (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } وإلا {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        إذا (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } وإلا إذا (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        إذا (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } وإلا
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        إذا (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } وإلا
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    إذا (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        إذا (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            صحيح w = rect.کانن;
            صحيح h = rect.bottom;

            إذا (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } وإلا إذا ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحيح x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, عدم, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } وإلا {
                window->w = w;
                window->h = h;
            }
        }
    }
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        إذا (ClientToScreen(hwnd, &point)) {
            إذا (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_ماسوقن_FOCUS;
    SDL_SetKeyboardFocus(window);
#وإلا
    إذا (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_ماسوقن_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    إذا (window->flags & SDL_WINDOW_ALWAYS_ON_اتس) {
        WIN_Set_Window_Always_On_اتس(_this, window, true);
    } وإلا {
        WIN_Set_Window_Always_On_اتس(_this, window, false);
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    إذا (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    إذا (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحيح titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        إذا (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } وإلا {
            titleLen = 0;
        }
        إذا (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        إذا (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    أرجع true;
}

ساكن فراغ CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    إذا (data) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        إذا (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        إذا (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        إذا (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            إذا (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } وإلا {
            // Restore any original event handler...
            إذا (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#وإلا
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = عدم;
}

ساكن فراغ WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    إذا (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        صحيح abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        ثابت صحيح width = window->last_size_pending ? window->pending.w : window->floating.w;
        ثابت صحيح height = window->last_size_pending ? window->pending.h : window->floating.h;
        صحيح offset_x = 0, offset_y = 0;

        إذا (window->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            إذا (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            إذا (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } وإلا {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

ساكن فراغ WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    طالما (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    إذا (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", عدم));
    HWND parent = عدم;
    إذا (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        إذا (!SetupWindowData(_this, window, hwnd, parent)) {
            أرجع false;
        }
    } وإلا {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحيح x, y;
        صحيح w, h;

        إذا (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, عدم, عدم, SDL_Instance, عدم);
        } وإلا إذا (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_نومبور_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_نومبور, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, عدم, SDL_Instance, عدم);
        إذا (!hwnd) {
            أرجع WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        إذا (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            إذا (parent) {
                DestroyWindow(parent);
            }
            أرجع false;
        }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_ماسوقن(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, عدم, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        إذا (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    إذا (window->flags & SDL_WINDOW_TRANSPARENT) {
        إذا (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, عدم);
    إذا (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحيح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        إذا (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            أرجع WIN_SetError("SetPixelFormat()");
        }
    } وإلا {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (!(window->flags & SDL_WINDOW_OPENGL)) {
            أرجع true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        إذا ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            إذا (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                أرجع false;
            }
            أرجع true;
#وإلا
            أرجع SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        إذا (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            أرجع false;
        }
#وإلا
        أرجع SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

فراغ WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = عدم;
    BYTE *icon_bmp;
    صحيح icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    إذا (!icon_bmp) {
        أرجع false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_کيراءن = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[حجم(BITMAPINFOHEADER)];
    row_len = icon->w * حجم(Uint32);
    y = icon->h;
    طالما (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    إذا (!hicon) {
        أرجع SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned صحيح)GetLastError());
    }

    إذا (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    أرجع result;
#وإلا
    أرجع SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        إذا (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            أرجع WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وإلا {
        أرجع SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    أرجع true;
}

فراغ WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    إذا (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وإلا {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, صحيح *اتس, صحيح *کيري, صحيح *bottom, صحيح *کانن)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *اتس = rcClient.اتس;
    *کيري = rcClient.کيري;
    *bottom = rcClient.bottom;
    *کانن = rcClient.کانن;

    أرجع true;
#وإلا  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    إذا (!GetClientRect(hwnd, &rcClient)) {
        أرجع SDL_SetError("GetClientRect() failed, error %08X", (unsigned صحيح)GetLastError());
    }

    إذا (!GetWindowRect(hwnd, &rcWindow)) {
        أرجع SDL_SetError("GetWindowRect() failed, error %08X", (unsigned صحيح)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.اتس;
    ptDiff.x = rcWindow.کيري;

    إذا (!ScreenToClient(hwnd, &ptDiff)) {
        أرجع SDL_SetError("ScreenToClient() failed, error %08X", (unsigned صحيح)GetLastError());
    }

    rcWindow.اتس = ptDiff.y;
    rcWindow.کيري = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.کانن;

    إذا (!ScreenToClient(hwnd, &ptDiff)) {
        أرجع SDL_SetError("ScreenToClient() failed, error %08X", (unsigned صحيح)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.کانن = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *اتس = rcClient.اتس - rcWindow.اتس;
    *کيري = rcClient.کيري - rcWindow.کيري;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *کانن = rcWindow.کانن - rcClient.کانن;

    أرجع true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحيح *w, صحيح *h)
{
    ثابت SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    إذا (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.کانن;
        *h = rect.bottom;
    } وإلا إذا (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } وإلا {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

فراغ WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    إذا (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    إذا (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        إذا (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    إذا (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    إذا (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } وإلا {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, عدم, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    إذا ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    إذا (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

فراغ WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    إذا (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    إذا ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ثابت bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

فراغ WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = عدم;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    إذا (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, عدم);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_ماسوقن(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        إذا (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_اتس)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    إذا (bActivate) {
        SetForegroundWindow(hwnd);
        إذا ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } وإلا {
        SetWindowPos(hwnd, HWND_اتس, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    إذا (bForce) {
        Attach_Thread_ماسوقن(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        إذا (window->max_w || window->max_h) {
            صحيح fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_اتس, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } وإلا {
        data->windowed_mode_was_maximized = true;
    }
}

فراغ WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

فراغ WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

فراغ WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

فراغ WIN_Set_Window_Always_On_اتس(SDL_VideoDevice *_this, SDL_Window *window, bool on_اتس)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

فراغ WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        إذا (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } وإلا {
        data->windowed_mode_was_maximized = false;
    }
}

ساكن فراغ WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    إذا (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, حجم(cornerPref));
    }
#endif
}

ساكن فراغ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    إذا (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : عدم;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND اتس;
    صحيح x, y;
    صحيح w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحيح)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_اتس)) {
        اتس = HWND_TOPMOST;
    } وإلا {
        اتس = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = حجم(MONITORINFO);
    إذا (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    إذا (fullscreen) {
        x = minfo.rcMonitor.کيري;
        y = minfo.rcMonitor.اتس;
        w = minfo.rcMonitor.کانن - minfo.rcMonitor.کيري;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.اتس;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        إذا (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وإلا {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        إذا (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
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
        إذا (enterMaximized) {
            ثابت SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            ثابت SDL_Point floating_point = { window->floating.x, window->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ثابت SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            إذا (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                إذا (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } وإلا {
                    x = bounds.x;
                }
                إذا (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } وإلا {
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
    SetWindowPos(hwnd, اتس, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    إذا (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    إذا (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحيح)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    إذا (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, عدم, عدم, عدم);
        إذا (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            إذا (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                إذا (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    إذا (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

فراغ *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    حرف *filename_utf8;
    فراغ *iccProfileData = عدم;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    إذا (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        إذا (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    أرجع iccProfileData;
}

ساكن فراغ WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    إذا (data->keyboard_hook) {
        أرجع;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    إذا (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        أرجع;
    }

    // Capture a snapshot of the current keyboard state before the hook
    إذا (!GetKeyboardState(data->videodata->pre_hook_کونچي_state)) {
        أرجع;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

فراغ WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    إذا (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = عدم;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    أرجع true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    أرجع true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    إذا (grabbed) {
        WIN_GrabKeyboard(window);
    } وإلا {
        WIN_UngrabKeyboard(window);
    }

    أرجع true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

فراغ WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    إذا (!data || !data->hwnd) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (window->flags & SDL_WINDOW_ALWAYS_ON_اتس) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساكن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    أرجع GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

فراغ WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    إذا (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(عدم);
        SDL_zero(data->cursor_clipped_rect);
    }
}

فراغ WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    إذا (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        أرجع;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_ماسوقن_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    إذا (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        إذا (!GetClipCursor(&current)) {
            أرجع;
        }
        إذا (videodevice && (
            current.کيري != videodevice->desktop_bounds.x ||
            current.اتس  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.کيري;
            first.y  = current.اتس;
            second.x = current.کانن  - 1;
            second.y = current.bottom - 1;
            إذا (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                أرجع;
            }
        }
        ClipCursor(عدم);
        SDL_zero(data->cursor_clipped_rect);
        أرجع;
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
    إذا (!GetClientScreenRect(data->hwnd, &client)) {
        أرجع;
    }

    RECT target = client;
    إذا (lock_to_ctr) {
        LONG cx = (client.کيري + client.کانن ) / 2;
        LONG cy = (client.اتس  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.کيري   += cx;
        target.کانن  += cx;
        target.اتس    += cy;
        target.bottom += cy;
    } وإلا إذا (win_mouse_rect) {
        RECT custom, overlap;
        custom.کيري   = client.کيري + mouse_rect.x;
        custom.اتس    = client.اتس  + mouse_rect.y;
        custom.کانن  = client.کيري + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.اتس  + mouse_rect.y + mouse_rect.h;
        إذا (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } وإلا إذا (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            أرجع;
        }
    } وإلا إذا (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        إذا (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            إذا (hmon) {
                UINT hdpi_uint, vdpi_uint;
                إذا (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت عائم scale = (عائم)hdpi_uint / (عائم)USER_DEFAULT_SCREEN_DPI;
                    إذا (scale != SDL_floorf(scale)) {
                        إذا (target.کيري < target.کانن) {
                            target.کيري += 1;
                        }
                        إذا (target.کانن > target.کيري) {
                            target.کانن -= 1;
                        }
                        إذا (target.اتس < target.bottom) {
                            target.اتس += 1;
                        }
                        إذا (target.bottom > target.اتس) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    إذا (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, حجم(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, عائم opacity)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع false;
#وإلا
    ثابت SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    إذا (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        إذا (style & WS_EX_LAYERED) {
            إذا (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                أرجع WIN_SetError("SetWindowLong()");
            }
        }
    } وإلا {
        ثابت BYTE alpha = (BYTE)((صحيح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        إذا (!(style & WS_EX_LAYERED)) {
            إذا (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                أرجع WIN_SetError("SetWindowLong()");
            }
        }

        إذا (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            أرجع WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    أرجع true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن ثابت حرف *SDLGetClipboardFormatName(UINT cf, حرف *text, صحيح len)
{
    بدل (cf) {
    حالة CF_TEXT:
        أرجع "CF_TEXT";
    حالة CF_BITMAP:
        أرجع "CF_BITMAP";
    حالة CF_METAFILEPICT:
        أرجع "CF_METAFILEPICT";
    حالة CF_SYLK:
        أرجع "CF_SYLK";
    حالة CF_DIF:
        أرجع "CF_DIF";
    حالة CF_TIFF:
        أرجع "CF_TIFF";
    حالة CF_OEMTEXT:
        أرجع "CF_OEMTEXT";
    حالة CF_DIB:
        أرجع "CF_DIB";
    حالة CF_PALETTE:
        أرجع "CF_PALETTE";
    حالة CF_PENDATA:
        أرجع "CF_PENDATA";
    حالة CF_RIFF:
        أرجع "CF_RIFF";
    حالة CF_WAVE:
        أرجع "CF_WAVE";
    حالة CF_UNICODETEXT:
        أرجع "CF_UNICODETEXT";
    حالة CF_ENHMETAFILE:
        أرجع "CF_ENHMETAFILE";
    حالة CF_HDROP:
        أرجع "CF_HDROP";
    حالة CF_LOCALE:
        أرجع "CF_LOCALE";
    حالة CF_DIBV5:
        أرجع "CF_DIBV5";
    حالة CF_OWNERDISPLAY:
        أرجع "CF_OWNERDISPLAY";
    حالة CF_DSPTEXT:
        أرجع "CF_DSPTEXT";
    حالة CF_DSPBITMAP:
        أرجع "CF_DSPBITMAP";
    حالة CF_DSPMETAFILEPICT:
        أرجع "CF_DSPMETAFILEPICT";
    حالة CF_DSPENHMETAFILE:
        أرجع "CF_DSPENHMETAFILE";
    افتراضي:
        إذا (GetClipboardFormatNameA(cf, text, len)) {
            أرجع text;
        } وإلا {
            أرجع عدم;
        }
    }
}

ساكن STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    أرجع ++target->refcount;
}

ساكن STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    إذا (target->refcount == 0) {
        SDL_free(target);
        أرجع 0;
    }
    أرجع target->refcount;
}

ساكن STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    إذا (ppv == عدم) {
        أرجع E_INVALIDARG;
    }

    *ppv = عدم;
    إذا (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (فراغ *)target;
    }
    إذا (*ppv) {
        SDLDropTarget_AddRef(target);
        أرجع S_OK;
    }
    أرجع E_NOINTERFACE;
}

ساكن STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_کونچي_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    إذا (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_کونچي_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    إذا (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_کونچي_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    إذا (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        إذا (hres == S_OK) {
            FORMATETC fetc;
            طالما (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, عدم) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                إذا (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وإلا {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/uri-list";
        إذا (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت فراغ *buffer = (فراغ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                إذا (buffer) {
                    حرف *text = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/plain;charset=utf-8";
        إذا (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت فراغ *buffer = (فراغ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                إذا (buffer) {
                    حرف *text = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_UNICODETEXT";
        إذا (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت فراغ *buffer = (فراغ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                إذا (buffer) {
                    buffer = WIN_StringToUTF8W((ثابت wchar_t *)buffer);
                    إذا (buffer) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        حرف *text = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = عدم;
                        حرف *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        طالما (token != عدم) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (حرف *)token);
                            token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((فراغ *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_TEXT";
        إذا (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت فراغ *buffer = (فراغ *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                إذا (buffer) {
                    حرف *text = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_HDROP";
        إذا (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT کيراءن = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
                لكل (UINT i = 0; i < کيراءن; ++i) {
                    UINT size = DragQueryFile(drop, i, عدم, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * حجم(TCHAR));
                    إذا (buffer) {
                        إذا (DragQueryFile(drop, i, buffer, size)) {
                            حرف *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, عدم, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                أرجع S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    أرجع S_OK;
}

ساكن فراغ *vtDropTarget[] = {
    (فراغ *)(SDLDropTarget_QueryInterface),
    (فراغ *)(SDLDropTarget_AddRef),
    (فراغ *)(SDLDropTarget_Release),
    (فراغ *)(SDLDropTarget_DragEnter),
    (فراغ *)(SDLDropTarget_DragOver),
    (فراغ *)(SDLDropTarget_DragLeave),
    (فراغ *)(SDLDropTarget_Drop)
};

فراغ WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    إذا (data->videodata->oleinitialized) {
        إذا (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, حجم(SDLDropTarget));
            إذا (drop_target != عدم) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } وإلا إذا (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = عدم;
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } وإلا {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = حجم(desc);
    desc.hwnd = window->internal->hwnd;
    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_کيراءن = 1;
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        اكسر;
    افتراضي:
        أرجع SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    أرجع true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    إذا (!data->taskbar_button_created) {
        أرجع true;
    }

    إذا (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        أرجع true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    إذا (!taskbar_list) {
        أرجع false;
    }

    TBPFLAG tbpFlags;
    بدل (window->progress_state) {
    حالة SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        اكسر;
    حالة SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        اكسر;
    حالة SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        اكسر;
    حالة SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        اكسر;
    حالة SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        اكسر;
    افتراضي:
        أرجع SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    إذا (FAILED(ret)) {
        أرجع WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    إذا (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_نيلاي(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_نيلاي * 10000.f), 10000);
        إذا (FAILED(ret)) {
            أرجع WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    أرجع true;
}

فراغ WIN_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y)
{
    ثابت SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    إذا (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        إذا (focusable) {
            إذا (style & WS_EX_NOACTIVATE) {
                إذا (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_SetError("SetWindowLong()");
                }
            }
        } وإلا {
            إذا (!(style & WS_EX_NOACTIVATE)) {
                إذا (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_SetError("SetWindowLong()");
                }
            }
        }
    } وإلا إذا (window->flags & SDL_WINDOW_POPUP_MENU) {
        إذا (!(window->flags & SDL_WINDOW_HIDDEN)) {
            إذا (!focusable && (window->flags & SDL_WINDOW_ماسوقن_FOCUS)) {
                SDL_Window *new_focus;
                ثابت bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    ثابت LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : عدم);
    ثابت DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    إذا (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } وإلا {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    أرجع true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND parent_hwnd = window->parent->internal->hwnd;

    إذا (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } وإلا إذا (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
