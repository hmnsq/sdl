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

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#अन्तर्भाव "../../core/windows/SDL_windows.h"

#अन्तर्भाव "../../SDL_hints_c.h"
#अन्तर्भाव "../../events/SDL_dropevents_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowskeyboard.h"
#अन्तर्भाव "SDL_windowswindow.h"

// Dropfile support
#अन्तर्भाव <shellapi.h>

#जर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#अन्तर्भाव <shobjidl.h>
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

स्थिर DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    जर (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } अन्यथा जर (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } अन्यथा {
        जर (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            जर (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } अन्यथा {
                style |= STYLE_BORDERLESS;
            }
        } अन्यथा {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        जर (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            जर (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        जर (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        जर (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    परत style;
}

स्थिर DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    जर (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    जर (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    परत style;
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    स्थिरांक SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    जर (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, रिक्त, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        जर (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            परत रिक्त;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        जर (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = रिक्त;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            परत रिक्त;
        }
    }
    परत data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
स्थिर bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, पूर्णांक *x, पूर्णांक *y, पूर्णांक *width, पूर्णांक *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : रिक्त;
    RECT rect;

    // Client rect, in points
    निवड (rect_type) {
    स्थिती SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        थांबा;
    स्थिती SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        थांबा;
    स्थिती SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        थांबा;
    स्थिती SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        थांबा;
    पूर्वनिर्धारित:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        थांबा;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.डावा = 0;
    rect.शीर्ष = 0;
    rect.उजवा = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    जर (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#अन्यथा
        जर (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            जर (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                जर (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    परत WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } अन्यथा {
            जर (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                परत WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.डावा;
    *y += rect.शीर्ष;
    *width = (rect.उजवा - rect.डावा);
    *height = (rect.bottom - rect.शीर्ष);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    परत true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, पूर्णांक *x, पूर्णांक *y, पूर्णांक *width, पूर्णांक *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
#endif
    परत WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : रिक्त;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
#endif

#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#अन्यथा
    जर (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        जर (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        जर (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            परत WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } अन्यथा {
        जर (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            परत WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    परत true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND शीर्ष;
    पूर्णांक x, y;
    पूर्णांक w, h;
    bool result = true;

    // Figure out what the window area will be
    जर (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
        शीर्ष = HWND_TOPMOST;
    } अन्यथा {
        शीर्ष = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    जर (SetWindowPos(hwnd, शीर्ष, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    साठी (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        जर (!child_window->internal) {
            // This child window is not yet fully initialized.
            सुरूठेवा;
        }
        जर (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    परत result;
}

स्थिर SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(शून्य)
{
    स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    जर (!hint)
        परत SDL_ERASEBACKGROUNDMODE_INITIAL;

    जर (SDL_strstr(hint, "never"))
        परत SDL_ERASEBACKGROUNDMODE_NEVER;

    जर (SDL_strstr(hint, "initial"))
        परत SDL_ERASEBACKGROUNDMODE_INITIAL;

    जर (SDL_strstr(hint, "always"))
        परत SDL_ERASEBACKGROUNDMODE_ALWAYS;

    पूर्णांक mode = SDL_GetStringInteger(hint, 1);
    जर (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        परत SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    परत (SDL_WindowEraseBackgroundMode)mode;
}

स्थिर bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, आकार(*data));
    जर (!data) {
        परत false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#अन्यथा
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.डावा   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.शीर्ष    = 0;
    data->cursor_ctrlock_rect.उजवा  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    जर (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } अन्यथा {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    जर (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        परत WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    जर (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        जर (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#अन्यथा
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        जर (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } अन्यथा {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        जर (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } अन्यथा {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        जर (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        जर (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा जर (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        जर (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } अन्यथा
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        जर (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } अन्यथा
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    जर (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        जर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            पूर्णांक w = rect.उजवा;
            पूर्णांक h = rect.bottom;

            जर (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } अन्यथा जर ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                पूर्णांक x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, रिक्त, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } अन्यथा {
                window->w = w;
                window->h = h;
            }
        }
    }
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        जर (ClientToScreen(hwnd, &point)) {
            जर (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_आदान_FOCUS;
    SDL_SetKeyboardFocus(window);
#अन्यथा
    जर (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_आदान_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    जर (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) {
        WIN_Set_Window_Always_On_शीर्ष(_this, window, true);
    } अन्यथा {
        WIN_Set_Window_Always_On_शीर्ष(_this, window, false);
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    जर (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    जर (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    जर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        पूर्णांक titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        जर (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } अन्यथा {
            titleLen = 0;
        }
        जर (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        जर (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    परत true;
}

स्थिर शून्य CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    जर (data) {
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        जर (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        जर (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        जर (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        जर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            जर (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } अन्यथा {
            // Restore any original event handler...
            जर (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#अन्यथा
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = रिक्त;
}

स्थिर शून्य WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    जर (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णांक abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        पूर्णांक abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        स्थिरांक पूर्णांक width = window->last_size_pending ? window->pending.w : window->floating.w;
        स्थिरांक पूर्णांक height = window->last_size_pending ? window->pending.h : window->floating.h;
        पूर्णांक offset_x = 0, offset_y = 0;

        जर (window->constrain_popup) {
            // Calculate the total offset from the parents
            साठी (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            जर (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            जर (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        जर (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } अन्यथा {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

स्थिर शून्य WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    पर्यंत (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    जर (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    HWND parent = रिक्त;
    जर (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        जर (!SetupWindowData(_this, window, hwnd, parent)) {
            परत false;
        }
    } अन्यथा {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        पूर्णांक x, y;
        पूर्णांक w, h;

        जर (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, रिक्त, रिक्त, SDL_Instance, रिक्त);
        } अन्यथा जर (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_संख्या_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_संख्या, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, रिक्त, SDL_Instance, रिक्त);
        जर (!hwnd) {
            परत WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        जर (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            जर (parent) {
                DestroyWindow(parent);
            }
            परत false;
        }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_आदान(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, रिक्त, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        जर (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    जर (window->flags & SDL_WINDOW_TRANSPARENT) {
        जर (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, रिक्त);
    जर (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        पूर्णांक pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, आकार(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        जर (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            परत WIN_SetError("SetPixelFormat()");
        }
    } अन्यथा {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        जर (!(window->flags & SDL_WINDOW_OPENGL)) {
            परत true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        जर ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            जर (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                परत false;
            }
            परत true;
#अन्यथा
            परत SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        जर (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            परत false;
        }
#अन्यथा
        परत SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    परत true;
}

शून्य WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = रिक्त;
    BYTE *icon_bmp;
    पूर्णांक icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, आकार(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = आकार(BITMAPINFOHEADER) + icon->h * icon->w * आकार(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    जर (!icon_bmp) {
        परत false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(आकार(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_मोजणी = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * आकार(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[आकार(BITMAPINFOHEADER)];
    row_len = icon->w * आकार(Uint32);
    y = icon->h;
    पर्यंत (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    जर (!hicon) {
        परत SDL_SetError("SetWindowIcon() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    जर (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    परत result;
#अन्यथा
    परत SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    जर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        जर (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            परत WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } अन्यथा {
        परत SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    परत true;
}

शून्य WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    जर (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } अन्यथा {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *डावा, पूर्णांक *bottom, पूर्णांक *उजवा)
{
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *शीर्ष = rcClient.शीर्ष;
    *डावा = rcClient.डावा;
    *bottom = rcClient.bottom;
    *उजवा = rcClient.उजवा;

    परत true;
#अन्यथा  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    जर (!GetClientRect(hwnd, &rcClient)) {
        परत SDL_SetError("GetClientRect() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    जर (!GetWindowRect(hwnd, &rcWindow)) {
        परत SDL_SetError("GetWindowRect() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.शीर्ष;
    ptDiff.x = rcWindow.डावा;

    जर (!ScreenToClient(hwnd, &ptDiff)) {
        परत SDL_SetError("ScreenToClient() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    rcWindow.शीर्ष = ptDiff.y;
    rcWindow.डावा = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.उजवा;

    जर (!ScreenToClient(hwnd, &ptDiff)) {
        परत SDL_SetError("ScreenToClient() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.उजवा = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *शीर्ष = rcClient.शीर्ष - rcWindow.शीर्ष;
    *डावा = rcClient.डावा - rcWindow.डावा;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *उजवा = rcWindow.उजवा - rcClient.उजवा;

    परत true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

शून्य WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    स्थिरांक SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    जर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.उजवा;
        *h = rect.bottom;
    } अन्यथा जर (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } अन्यथा {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

शून्य WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    जर (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    जर (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        जर (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    जर (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    जर (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } अन्यथा {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, रिक्त, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    जर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    जर (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

शून्य WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    जर (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    जर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        स्थिरांक bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

शून्य WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = रिक्त;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    जर (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, रिक्त);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_आदान(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        जर (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    जर (bActivate) {
        SetForegroundWindow(hwnd);
        जर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } अन्यथा {
        SetWindowPos(hwnd, HWND_शीर्ष, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    जर (bForce) {
        Attach_Thread_आदान(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

शून्य WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    जर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        जर (window->max_w || window->max_h) {
            पूर्णांक fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_शीर्ष, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } अन्यथा {
        data->windowed_mode_was_maximized = true;
    }
}

शून्य WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

शून्य WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

शून्य WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

शून्य WIN_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

शून्य WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    जर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        जर (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } अन्यथा {
        data->windowed_mode_was_maximized = false;
    }
}

स्थिर शून्य WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    जर (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, आकार(cornerPref));
    }
#endif
}

स्थिर शून्य WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    जर (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, आकार(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : रिक्त;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND शीर्ष;
    पूर्णांक x, y;
    पूर्णांक w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (पूर्णांक)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    जर (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        परत SDL_FULLSCREEN_SUCCEEDED;
    }

    जर (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
        शीर्ष = HWND_TOPMOST;
    } अन्यथा {
        शीर्ष = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = आकार(MONITORINFO);
    जर (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        परत SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    जर (fullscreen) {
        x = minfo.rcMonitor.डावा;
        y = minfo.rcMonitor.शीर्ष;
        w = minfo.rcMonitor.उजवा - minfo.rcMonitor.डावा;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        जर (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } अन्यथा {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        जर (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
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
        जर (enterMaximized) {
            स्थिरांक SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            स्थिरांक SDL_Point floating_point = { window->floating.x, window->floating.y };
            स्थिरांक SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            स्थिरांक SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            जर (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                जर (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } अन्यथा {
                    x = bounds.x;
                }
                जर (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } अन्यथा {
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
    SetWindowPos(hwnd, शीर्ष, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    जर (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    जर (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (पूर्णांक)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    परत SDL_FULLSCREEN_SUCCEEDED;
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
शून्य WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    जर (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, रिक्त, रिक्त, रिक्त);
        जर (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            जर (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                जर (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    जर (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

शून्य *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *size)
{
    SDL_WindowData *data = window->internal;
    अक्षर *filename_utf8;
    शून्य *iccProfileData = रिक्त;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    जर (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        जर (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    परत iccProfileData;
}

स्थिर शून्य WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    जर (data->keyboard_hook) {
        परत;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    जर (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        परत;
    }

    // Capture a snapshot of the current keyboard state before the hook
    जर (!GetKeyboardState(data->videodata->pre_hook_किल्ली_state)) {
        परत;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

शून्य WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    जर (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = रिक्त;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    परत true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    परत true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    जर (grabbed) {
        WIN_GrabKeyboard(window);
    } अन्यथा {
        WIN_UngrabKeyboard(window);
    }

    परत true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

शून्य WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
शून्य WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    जर (!data || !data->hwnd) {
        // The window wasn't fully initialized
        परत;
    }

    जर (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

स्थिर BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    परत GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

शून्य WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    जर (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, आकार(rect)) == 0) {
        ClipCursor(रिक्त);
        SDL_zero(data->cursor_clipped_rect);
    }
}

शून्य WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    जर (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        परत;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_आदान_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    जर (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        जर (!GetClipCursor(&current)) {
            परत;
        }
        जर (videodevice && (
            current.डावा != videodevice->desktop_bounds.x ||
            current.शीर्ष  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.डावा;
            first.y  = current.शीर्ष;
            second.x = current.उजवा  - 1;
            second.y = current.bottom - 1;
            जर (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                परत;
            }
        }
        ClipCursor(रिक्त);
        SDL_zero(data->cursor_clipped_rect);
        परत;
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
    जर (!GetClientScreenRect(data->hwnd, &client)) {
        परत;
    }

    RECT target = client;
    जर (lock_to_ctr) {
        LONG cx = (client.डावा + client.उजवा ) / 2;
        LONG cy = (client.शीर्ष  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.डावा   += cx;
        target.उजवा  += cx;
        target.शीर्ष    += cy;
        target.bottom += cy;
    } अन्यथा जर (win_mouse_rect) {
        RECT custom, overlap;
        custom.डावा   = client.डावा + mouse_rect.x;
        custom.शीर्ष    = client.शीर्ष  + mouse_rect.y;
        custom.उजवा  = client.डावा + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.शीर्ष  + mouse_rect.y + mouse_rect.h;
        जर (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } अन्यथा जर (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            परत;
        }
    } अन्यथा जर (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        जर (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            जर (hmon) {
                UINT hdpi_uint, vdpi_uint;
                जर (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    स्थिरांक दशांश scale = (दशांश)hdpi_uint / (दशांश)USER_DEFAULT_SCREEN_DPI;
                    जर (scale != SDL_floorf(scale)) {
                        जर (target.डावा < target.उजवा) {
                            target.डावा += 1;
                        }
                        जर (target.उजवा > target.डावा) {
                            target.उजवा -= 1;
                        }
                        जर (target.शीर्ष < target.bottom) {
                            target.शीर्ष += 1;
                        }
                        जर (target.bottom > target.शीर्ष) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    जर (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, आकार(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    परत true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, दशांश opacity)
{
#जर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    परत false;
#अन्यथा
    स्थिरांक SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    स्थिरांक LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    जर (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        जर (style & WS_EX_LAYERED) {
            जर (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                परत WIN_SetError("SetWindowLong()");
            }
        }
    } अन्यथा {
        स्थिरांक BYTE alpha = (BYTE)((पूर्णांक)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        जर (!(style & WS_EX_LAYERED)) {
            जर (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                परत WIN_SetError("SetWindowLong()");
            }
        }

        जर (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            परत WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    परत true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर स्थिरांक अक्षर *SDLGetClipboardFormatName(UINT cf, अक्षर *text, पूर्णांक len)
{
    निवड (cf) {
    स्थिती CF_TEXT:
        परत "CF_TEXT";
    स्थिती CF_BITMAP:
        परत "CF_BITMAP";
    स्थिती CF_METAFILEPICT:
        परत "CF_METAFILEPICT";
    स्थिती CF_SYLK:
        परत "CF_SYLK";
    स्थिती CF_DIF:
        परत "CF_DIF";
    स्थिती CF_TIFF:
        परत "CF_TIFF";
    स्थिती CF_OEMTEXT:
        परत "CF_OEMTEXT";
    स्थिती CF_DIB:
        परत "CF_DIB";
    स्थिती CF_PALETTE:
        परत "CF_PALETTE";
    स्थिती CF_PENDATA:
        परत "CF_PENDATA";
    स्थिती CF_RIFF:
        परत "CF_RIFF";
    स्थिती CF_WAVE:
        परत "CF_WAVE";
    स्थिती CF_UNICODETEXT:
        परत "CF_UNICODETEXT";
    स्थिती CF_ENHMETAFILE:
        परत "CF_ENHMETAFILE";
    स्थिती CF_HDROP:
        परत "CF_HDROP";
    स्थिती CF_LOCALE:
        परत "CF_LOCALE";
    स्थिती CF_DIBV5:
        परत "CF_DIBV5";
    स्थिती CF_OWNERDISPLAY:
        परत "CF_OWNERDISPLAY";
    स्थिती CF_DSPTEXT:
        परत "CF_DSPTEXT";
    स्थिती CF_DSPBITMAP:
        परत "CF_DSPBITMAP";
    स्थिती CF_DSPMETAFILEPICT:
        परत "CF_DSPMETAFILEPICT";
    स्थिती CF_DSPENHMETAFILE:
        परत "CF_DSPENHMETAFILE";
    पूर्वनिर्धारित:
        जर (GetClipboardFormatNameA(cf, text, len)) {
            परत text;
        } अन्यथा {
            परत रिक्त;
        }
    }
}

स्थिर STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    परत ++target->refcount;
}

स्थिर STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    जर (target->refcount == 0) {
        SDL_free(target);
        परत 0;
    }
    परत target->refcount;
}

स्थिर STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    जर (ppv == रिक्त) {
        परत E_INVALIDARG;
    }

    *ppv = रिक्त;
    जर (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (शून्य *)target;
    }
    जर (*ppv) {
        SDLDropTarget_AddRef(target);
        परत S_OK;
    }
    परत E_NOINTERFACE;
}

स्थिर STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_किल्ली_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    जर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    परत S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_किल्ली_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    जर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    परत S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    परत S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_किल्ली_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    जर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        जर (hres == S_OK) {
            FORMATETC fetc;
            पर्यंत (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, रिक्त) == S_OK) {
                अक्षर name[257] = { 0 };
                स्थिरांक अक्षर *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                जर (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } अन्यथा {
                    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = रिक्त;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिरांक अक्षर *format_mime = "text/uri-list";
        जर (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            जर (SUCCEEDED(hres)) {
                स्थिरांक माप_प्रकार bsize = GlobalSize(med.hGlobal);
                स्थिरांक शून्य *buffer = (शून्य *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, buffer);
                जर (buffer) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + आकार(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, आकार(Uint32));
                    अक्षर *saveptr = रिक्त;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    पर्यंत (token != रिक्त) {
                        जर (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                            SDL_SendDropFile(target->window, रिक्त, token);
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                परत S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = रिक्त;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिरांक अक्षर *format_mime = "text/plain;charset=utf-8";
        जर (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            जर (SUCCEEDED(hres)) {
                स्थिरांक माप_प्रकार bsize = GlobalSize(med.hGlobal);
                स्थिरांक शून्य *buffer = (शून्य *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, buffer);
                जर (buffer) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + आकार(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, आकार(Uint32));
                    अक्षर *saveptr = रिक्त;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    पर्यंत (token != रिक्त) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                        SDL_SendDropText(target->window, (अक्षर *)token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                परत S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = रिक्त;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिरांक अक्षर *format_mime = "CF_UNICODETEXT";
        जर (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            जर (SUCCEEDED(hres)) {
                स्थिरांक माप_प्रकार bsize = GlobalSize(med.hGlobal);
                स्थिरांक शून्य *buffer = (शून्य *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, buffer);
                जर (buffer) {
                    buffer = WIN_StringToUTF8W((स्थिरांक ब_अक्षर_प्रकार *)buffer);
                    जर (buffer) {
                        स्थिरांक माप_प्रकार lbuffer = SDL_strlen((स्थिरांक अक्षर *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)lbuffer, buffer);
                        अक्षर *text = (अक्षर *)SDL_malloc(lbuffer + आकार(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, आकार(Uint32));
                        अक्षर *saveptr = रिक्त;
                        अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        पर्यंत (token != रिक्त) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)lbuffer, token);
                            SDL_SendDropText(target->window, (अक्षर *)token);
                            token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((शून्य *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                परत S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = रिक्त;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिरांक अक्षर *format_mime = "CF_TEXT";
        जर (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            जर (SUCCEEDED(hres)) {
                स्थिरांक माप_प्रकार bsize = GlobalSize(med.hGlobal);
                स्थिरांक शून्य *buffer = (शून्य *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, buffer);
                जर (buffer) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + आकार(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, आकार(Uint32));
                    अक्षर *saveptr = रिक्त;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    पर्यंत (token != रिक्त) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                        SDL_SendDropText(target->window, (अक्षर *)token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                परत S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = रिक्त;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिरांक अक्षर *format_mime = "CF_HDROP";
        जर (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            जर (SUCCEEDED(hres)) {
                स्थिरांक माप_प्रकार bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, drop);
                UINT मोजणी = DragQueryFile(drop, 0xFFFFFFFF, रिक्त, 0);
                साठी (UINT i = 0; i < मोजणी; ++i) {
                    UINT size = DragQueryFile(drop, i, रिक्त, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * आकार(TCHAR));
                    जर (buffer) {
                        जर (DragQueryFile(drop, i, buffer, size)) {
                            अक्षर *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(file), (अचिन्हित दीर्घ)bsize, file);
                            SDL_SendDropFile(target->window, रिक्त, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                परत S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    परत S_OK;
}

स्थिर शून्य *vtDropTarget[] = {
    (शून्य *)(SDLDropTarget_QueryInterface),
    (शून्य *)(SDLDropTarget_AddRef),
    (शून्य *)(SDLDropTarget_Release),
    (शून्य *)(SDLDropTarget_DragEnter),
    (शून्य *)(SDLDropTarget_DragOver),
    (शून्य *)(SDLDropTarget_DragLeave),
    (शून्य *)(SDLDropTarget_Drop)
};

शून्य WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    जर (data->videodata->oleinitialized) {
        जर (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, आकार(SDLDropTarget));
            जर (drop_target != रिक्त) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } अन्यथा जर (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = रिक्त;
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } अन्यथा {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = आकार(desc);
    desc.hwnd = window->internal->hwnd;
    निवड (operation) {
    स्थिती SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        थांबा;
    स्थिती SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_मोजणी = 1;
        थांबा;
    स्थिती SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        थांबा;
    पूर्वनिर्धारित:
        परत SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    परत true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    जर (!data->taskbar_button_created) {
        परत true;
    }

    जर (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        परत true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    जर (!taskbar_list) {
        परत false;
    }

    TBPFLAG tbpFlags;
    निवड (window->progress_state) {
    स्थिती SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        थांबा;
    स्थिती SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        थांबा;
    स्थिती SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        थांबा;
    स्थिती SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        थांबा;
    स्थिती SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        थांबा;
    पूर्वनिर्धारित:
        परत SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    जर (FAILED(ret)) {
        परत WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    जर (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_मूल्य(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_मूल्य * 10000.f), 10000);
        जर (FAILED(ret)) {
            परत WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    परत true;
}

शून्य WIN_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    स्थिरांक SDL_WindowData *data = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(data->hwnd, &pt);
    SendMessage(data->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    जर (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        स्थिरांक LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        जर (focusable) {
            जर (style & WS_EX_NOACTIVATE) {
                जर (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    परत WIN_SetError("SetWindowLong()");
                }
            }
        } अन्यथा {
            जर (!(style & WS_EX_NOACTIVATE)) {
                जर (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    परत WIN_SetError("SetWindowLong()");
                }
            }
        }
    } अन्यथा जर (window->flags & SDL_WINDOW_POPUP_MENU) {
        जर (!(window->flags & SDL_WINDOW_HIDDEN)) {
            जर (!focusable && (window->flags & SDL_WINDOW_आदान_FOCUS)) {
                SDL_Window *new_focus;
                स्थिरांक bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } अन्यथा जर (focusable) {
                जर (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        परत true;
    }

    परत true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    स्थिरांक LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : रिक्त);
    स्थिरांक DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    जर (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } अन्यथा {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    परत true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    स्थिरांक HWND parent_hwnd = window->parent->internal->hwnd;

    जर (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } अन्यथा जर (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    परत true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
