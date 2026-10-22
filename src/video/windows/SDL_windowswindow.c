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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS

#شامل "../../core/windows/SDL_windows.h"

#شامل "../../SDL_hints_c.h"
#شامل "../../events/SDL_dropevents_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../SDL_pixels_c.h"
#شامل "../SDL_sysvideo.h"

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowskeyboard.h"
#شامل "SDL_windowswindow.h"

// Dropfile support
#شامل <shellapi.h>

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#شامل <shobjidl.h>
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

ایستا DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    اگر (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } وگرنه اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وگرنه {
        اگر (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            اگر (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } وگرنه {
                style |= STYLE_BORDERLESS;
            }
        } وگرنه {
            style |= STYLE_NORMAL;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        اگر (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            اگر (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        اگر (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        اگر (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    بازگشت style;
}

ایستا DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    اگر (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    اگر (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    بازگشت style;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ایستا ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    ثابت SDL_WindowData *data = window->internal;
    SDL_assert(data->taskbar_button_created);
    اگر (!data->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, پوچ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&data->videodata->taskbar_list);
        اگر (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            بازگشت پوچ;
        }
        ITaskbarList3 *taskbarlist = data->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        اگر (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            data->videodata->taskbar_list = پوچ;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            بازگشت پوچ;
        }
    }
    بازگشت data->videodata->taskbar_list;
}
#endif

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ایستا bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, صحیح *x, صحیح *y, صحیح *width, صحیح *height, SDL_WindowRect rect_type)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : پوچ;
    RECT rect;

    // Client rect, in points
    انتخاب (rect_type) {
    حالت SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        بشکن;
    حالت SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        بشکن;
    حالت SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        بشکن;
    حالت SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        بشکن;
    پیشفرض:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        بشکن;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.چپ = 0;
    rect.بالاترین = 0;
    rect.راست = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    اگر (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#وگرنه
        اگر (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            اگر (videodata) {
                UINT frame_dpi;
                SDL_WindowData *data = window->internal;
                frame_dpi = (data && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(data->hwnd) : USER_DEFAULT_SCREEN_DPI;
                اگر (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    بازگشت WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } وگرنه {
            اگر (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                بازگشت WIN_SetError("AdjustWindowRectEx()");
            }
        }
#endif
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.چپ;
    *y += rect.بالاترین;
    *width = (rect.راست - rect.چپ);
    *height = (rect.bottom - rect.بالاترین);

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#endif
    بازگشت true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, صحیح *x, صحیح *y, صحیح *width, صحیح *height, SDL_WindowRect rect_type)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وگرنه
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != پوچ);
#endif
    بازگشت WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_VideoData *videodata = videodevice ? videodevice->internal : پوچ;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وگرنه
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != پوچ);
#endif

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#وگرنه
    اگر (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        اگر (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        اگر (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            بازگشت WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } وگرنه {
        اگر (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            بازگشت WIN_SetError("AdjustWindowRectEx()");
        }
    }
#endif
    بازگشت true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HWND بالاترین;
    صحیح x, y;
    صحیح w, h;
    bool result = true;

    // Figure out what the window area will be
    اگر (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین)) {
        بالاترین = HWND_TOPMOST;
    } وگرنه {
        بالاترین = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    data->expected_resize = !(flags & SWP_NOSIZE);
    اگر (SetWindowPos(hwnd, بالاترین, x, y, w, h, flags) == 0) {
        result = WIN_SetError("SetWindowPos()");
    }
    data->expected_resize = false;

    // Update any child windows
    برای (child_window = window->first_child; child_window; child_window = child_window->next_sibling) {
        اگر (!child_window->internal) {
            // This child window is not yet fully initialized.
            ادامه;
        }
        اگر (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            result = false;
        }
    }
    بازگشت result;
}

ایستا SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(تهی)
{
    ثابت نویسه *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    اگر (!hint)
        بازگشت SDL_ERASEBACKGROUNDMODE_INITIAL;

    اگر (SDL_strstr(hint, "never"))
        بازگشت SDL_ERASEBACKGROUNDMODE_NEVER;

    اگر (SDL_strstr(hint, "initial"))
        بازگشت SDL_ERASEBACKGROUNDMODE_INITIAL;

    اگر (SDL_strstr(hint, "always"))
        بازگشت SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحیح mode = SDL_GetStringInteger(hint, 1);
    اگر (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        بازگشت SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    بازگشت (SDL_WindowEraseBackgroundMode)mode;
}

ایستا bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, اندازه(*data));
    اگر (!data) {
        بازگشت false;
    }
    data->window = window;
    data->hwnd = hwnd;
    data->parent = parent;
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    data->hdc = (HDC)data->hwnd;
#وگرنه
    data->hdc = GetDC(hwnd);
#endif
    data->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    data->mouse_button_flags = (WPARAM)-1;
    data->last_pointer_update = (LPARAM)-1;
    data->videodata = videodata;
    data->initializing = true;
    data->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    data->cursor_ctrlock_rect.چپ   = 0 - remote_desktop_adjustment;
    data->cursor_ctrlock_rect.بالاترین    = 0;
    data->cursor_ctrlock_rect.راست  = 1 + remote_desktop_adjustment;
    data->cursor_ctrlock_rect.bottom = 1;
#endif

    اگر (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        data->copybits_flag = 0;
    } وگرنه {
        data->copybits_flag = SWP_NOCOPYBITS;
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", data->scaling_dpi);
#endif

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    اگر (!SetProp(hwnd, TEXT("SDL_WindowData"), data)) {
        ReleaseDC(hwnd, data->hdc);
        SDL_free(data);
        بازگشت WIN_SetError("SetProp() failed");
    }
#endif

    window->internal = data;

    // Set up the window proc function
    اگر (window->flags & SDL_WINDOW_EXTERNAL) {
#ifdef GWLP_WNDPROC
        data->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        اگر (data->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#وگرنه
        data->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        اگر (data->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#endif
    } وگرنه {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        اگر (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } وگرنه {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        اگر (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } وگرنه {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        اگر (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } وگرنه اگر (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#ifdef WS_MAXIMIZE
        اگر (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } وگرنه
#endif
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#ifdef WS_MINIMIZE
        اگر (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } وگرنه
#endif
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    اگر (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        اگر (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            صحیح w = rect.راست;
            صحیح h = rect.bottom;

            اگر (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } وگرنه اگر ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحیح x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                data->expected_resize = true;
                SetWindowPos(hwnd, پوچ, x, y, w, h, data->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                data->expected_resize = false;
            } وگرنه {
                window->w = w;
                window->h = h;
            }
        }
    }
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        اگر (ClientToScreen(hwnd, &point)) {
            اگر (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#endif

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_درون_داد_FOCUS;
    SDL_SetKeyboardFocus(window);
#وگرنه
    اگر (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_درون_داد_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#endif

    اگر (window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین) {
        WIN_Set_Window_Always_On_بالاترین(_this, window, true);
    } وگرنه {
        WIN_Set_Window_Always_On_بالاترین(_this, window, false);
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    اگر (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#endif

    اگر (data->parent && !window->parent) {
        data->destroy_parent_with_window = true;
    }

    data->initializing = false;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحیح titleLen;
        bool isstack;

        titleLen = GetWindowTextLength(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        اگر (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } وگرنه {
            titleLen = 0;
        }
        اگر (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        اگر (title) {
            SDL_small_free(title, isstack);
        }
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, data->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, data->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, data->hinstance);

    // All done!
    بازگشت true;
}

ایستا تهی CleanupWindowData(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    اگر (data) {
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (data->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(data->ICMFileName);
        اگر (data->keyboard_hook) {
            UnhookWindowsHookEx(data->keyboard_hook);
        }
        اگر (data->hicon) {
            DestroyIcon(data->hicon);
        }
        ReleaseDC(data->hwnd, data->hdc);
        RemoveProp(data->hwnd, TEXT("SDL_WindowData"));
#endif
        اگر (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(data->hwnd);
            اگر (data->destroy_parent_with_window && data->parent) {
                DestroyWindow(data->parent);
            }
        } وگرنه {
            // Restore any original event handler...
            اگر (data->wndproc) {
#ifdef GWLP_WNDPROC
                SetWindowLongPtr(data->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)data->wndproc);
#وگرنه
                SetWindowLong(data->hwnd, GWL_WNDPROC,
                              (LONG_PTR)data->wndproc);
#endif
            }
        }
        SDL_free(data);
    }
    window->internal = پوچ;
}

ایستا تهی WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    اگر (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحیح abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        صحیح abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        ثابت صحیح width = window->last_size_pending ? window->pending.w : window->floating.w;
        ثابت صحیح height = window->last_size_pending ? window->pending.h : window->floating.h;
        صحیح offset_x = 0, offset_y = 0;

        اگر (window->constrain_popup) {
            // Calculate the total offset from the parents
            برای (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            اگر (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            اگر (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        اگر (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
            window->pending.w = width;
            window->pending.h = height;
        } وگرنه {
            window->floating.x = abs_x - offset_x;
            window->floating.y = abs_y - offset_y;
            window->floating.w = width;
            window->floating.h = height;
        }
    }
}

ایستا تهی WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    وقتی (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    اگر (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", پوچ));
    HWND parent = پوچ;
    اگر (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        اگر (!SetupWindowData(_this, window, hwnd, parent)) {
            بازگشت false;
        }
    } وگرنه {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحیح x, y;
        صحیح w, h;

        اگر (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, پوچ, پوچ, SDL_Instance, پوچ);
        } وگرنه اگر (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_عدد_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_عدد, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, پوچ, SDL_Instance, پوچ);
        اگر (!hwnd) {
            بازگشت WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        اگر (!SetupWindowData(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            اگر (parent) {
                DestroyWindow(parent);
            }
            بازگشت false;
        }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_درون_داد(_this, window);
#endif

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, پوچ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        اگر (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    اگر (window->flags & SDL_WINDOW_TRANSPARENT) {
        اگر (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, پوچ);
    اگر (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحیح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, اندازه(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        اگر (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            بازگشت WIN_SetError("SetPixelFormat()");
        }
    } وگرنه {
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (!(window->flags & SDL_WINDOW_OPENGL)) {
            بازگشت true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ifdef SDL_VIDEO_OPENGL_ES2
        اگر ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_data || WIN_GL_UseEGL(_this))
#endif // SDL_VIDEO_OPENGL_WGL
        ) {
#ifdef SDL_VIDEO_OPENGL_EGL
            اگر (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                بازگشت false;
            }
            بازگشت true;
#وگرنه
            بازگشت SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#endif // SDL_VIDEO_OPENGL_EGL
        }
#endif // SDL_VIDEO_OPENGL_ES2

#ifdef SDL_VIDEO_OPENGL_WGL
        اگر (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            بازگشت false;
        }
#وگرنه
        بازگشت SDL_SetError("Could not create GL window (WGL support not configured)");
#endif
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    بازگشت true;
}

تهی WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#endif
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    HICON hicon = پوچ;
    BYTE *icon_bmp;
    صحیح icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool result = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, اندازه(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = اندازه(BITMAPINFOHEADER) + icon->h * icon->w * اندازه(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    اگر (!icon_bmp) {
        بازگشت false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->biSize = SDL_Swap32LE(اندازه(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_شمار = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->biSizeImage = SDL_Swap32LE(icon->h * icon->w * اندازه(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[اندازه(BITMAPINFOHEADER)];
    row_len = icon->w * اندازه(Uint32);
    y = icon->h;
    وقتی (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    اگر (!hicon) {
        بازگشت SDL_SetError("SetWindowIcon() failed, error %08X", (unsigned صحیح)GetLastError());
    }

    اگر (data->hicon) {
        DestroyIcon(data->hicon);
    }
    data->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    بازگشت result;
#وگرنه
    بازگشت SDL_Unsupported();
#endif
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        اگر (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            بازگشت WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وگرنه {
        بازگشت SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    بازگشت true;
}

تهی WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    اگر (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وگرنه {
        // Can't resize the window
        window->last_size_pending = false;
    }
}

bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, صحیح *بالاترین, صحیح *چپ, صحیح *bottom, صحیح *راست)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *بالاترین = rcClient.بالاترین;
    *چپ = rcClient.چپ;
    *bottom = rcClient.bottom;
    *راست = rcClient.راست;

    بازگشت true;
#وگرنه  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    اگر (!GetClientRect(hwnd, &rcClient)) {
        بازگشت SDL_SetError("GetClientRect() failed, error %08X", (unsigned صحیح)GetLastError());
    }

    اگر (!GetWindowRect(hwnd, &rcWindow)) {
        بازگشت SDL_SetError("GetWindowRect() failed, error %08X", (unsigned صحیح)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.بالاترین;
    ptDiff.x = rcWindow.چپ;

    اگر (!ScreenToClient(hwnd, &ptDiff)) {
        بازگشت SDL_SetError("ScreenToClient() failed, error %08X", (unsigned صحیح)GetLastError());
    }

    rcWindow.بالاترین = ptDiff.y;
    rcWindow.چپ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.راست;

    اگر (!ScreenToClient(hwnd, &ptDiff)) {
        بازگشت SDL_SetError("ScreenToClient() failed, error %08X", (unsigned صحیح)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.راست = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *بالاترین = rcClient.بالاترین - rcWindow.بالاترین;
    *چپ = rcClient.چپ - rcWindow.چپ;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *راست = rcWindow.راست - rcClient.راست;

    بازگشت true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

تهی WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحیح *w, صحیح *h)
{
    ثابت SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    RECT rect;

    اگر (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.راست;
        *h = rect.bottom;
    } وگرنه اگر (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } وگرنه {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

تهی WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    اگر (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    اگر (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        اگر (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    اگر (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    data->showing_window = true;
    اگر (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } وگرنه {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, پوچ, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    data->showing_window = false;

    اگر ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    اگر (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

تهی WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    اگر (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    اگر ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ثابت bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

تهی WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = پوچ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    اگر (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, پوچ);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_درون_داد(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        اگر (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    اگر (bActivate) {
        SetForegroundWindow(hwnd);
        اگر ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } وگرنه {
        SetWindowPos(hwnd, HWND_بالاترین, 0, 0, 0, 0, data->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    اگر (bForce) {
        Attach_Thread_درون_داد(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

تهی WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = data->hwnd;
        data->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        data->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        اگر (window->max_w || window->max_h) {
            صحیح fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            data->expected_resize = true;
            SetWindowPos(hwnd, HWND_بالاترین, fx, fy, fw, fh, data->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            data->expected_resize = false;
        }
    } وگرنه {
        data->windowed_mode_was_maximized = true;
    }
}

تهی WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

تهی WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
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

تهی WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

تهی WIN_Set_Window_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_Window *window, bool on_بالاترین)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

تهی WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        اگر (!data->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = data->hwnd;
            data->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            data->expected_resize = false;
        }
    } وگرنه {
        data->windowed_mode_was_maximized = false;
    }
}

ایستا تهی WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    اگر (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, اندازه(cornerPref));
    }
#endif
}

ایستا تهی WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_VideoData *videodata = _this->internal;
    اگر (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, اندازه(colorRef));
    }
#endif
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_DisplayData *displaydata = display->internal;
    SDL_WindowData *data = window->internal;
    HWND hwnd = data ? data->hwnd : پوچ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND بالاترین;
    صحیح x, y;
    صحیح w, h;
    bool enterMaximized = false;

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحیح)fullscreen);
#endif

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        بازگشت SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین)) {
        بالاترین = HWND_TOPMOST;
    } وگرنه {
        بالاترین = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cbSize = اندازه(MONITORINFO);
    اگر (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        بازگشت SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    اگر (fullscreen) {
        x = minfo.rcMonitor.چپ;
        y = minfo.rcMonitor.بالاترین;
        w = minfo.rcMonitor.راست - minfo.rcMonitor.چپ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        اگر (style & WS_MAXIMIZE) {
            data->windowed_mode_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وگرنه {
        BOOL menu;

        WIN_UpdateCornerRoundingForHWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        اگر (data->windowed_mode_was_maximized && !data->in_window_deactivation) {
            enterMaximized = true;
            data->disable_move_size_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != پوچ);
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
        اگر (enterMaximized) {
            ثابت SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            ثابت SDL_Point floating_point = { window->floating.x, window->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ثابت SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            اگر (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                اگر (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } وگرنه {
                    x = bounds.x;
                }
                اگر (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } وگرنه {
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
    SetWindowPos(hwnd, بالاترین, x, y, w, h, data->copybits_flag | SWP_NOACTIVATE);
    data->expected_resize = false;
    data->disable_move_size_events = false;

    اگر (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    اگر (!fullscreen && data && data->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)data->hicon);
    }

#ifdef HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحیح)fullscreen, x, y, w, h);
#endif

#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    بازگشت SDL_FULLSCREEN_SUCCEEDED;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
تهی WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);

    اگر (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, پوچ, پوچ, پوچ);
        اگر (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD fileNameSize = SDL_arraysize(fileName);
            اگر (GetICMProfileW(hdc, &fileNameSize, fileName)) {
                // fileNameSize includes '\0' on return
                اگر (!data->ICMFileName ||
                    SDL_wcscmp(data->ICMFileName, fileName) != 0) {
                    SDL_free(data->ICMFileName);
                    data->ICMFileName = SDL_wcsdup(fileName);
                    اگر (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

تهی *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    نویسه *filename_utf8;
    تهی *iccProfileData = پوچ;

    filename_utf8 = WIN_StringToUTF8W(data->ICMFileName);
    اگر (filename_utf8) {
        iccProfileData = SDL_LoadFile(filename_utf8, size);
        اگر (!iccProfileData) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    بازگشت iccProfileData;
}

ایستا تهی WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    HMODULE module;

    اگر (data->keyboard_hook) {
        بازگشت;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    اگر (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        بازگشت;
    }

    // Capture a snapshot of the current keyboard state before the hook
    اگر (!GetKeyboardState(data->videodata->pre_hook_کلید_state)) {
        بازگشت;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    data->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

تهی WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    اگر (data->keyboard_hook) {
        UnhookWindowsHookEx(data->keyboard_hook);
        data->keyboard_hook = پوچ;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    بازگشت true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    بازگشت true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    اگر (grabbed) {
        WIN_GrabKeyboard(window);
    } وگرنه {
        WIN_UngrabKeyboard(window);
    }

    بازگشت true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

تهی WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    CleanupWindowData(_this, window);
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
تهی WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    اگر (!data || !data->hwnd) {
        // The window wasn't fully initialized
        بازگشت;
    }

    اگر (window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین) {
        WIN_SetWindowPositionInternal(window, data->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ایستا BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    بازگشت GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

تهی WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_WindowData *data = window->internal;
    RECT rect;
    اگر (GetClipCursor(&rect) && SDL_memcmp(&rect, &data->cursor_clipped_rect, اندازه(rect)) == 0) {
        ClipCursor(پوچ);
        SDL_zero(data->cursor_clipped_rect);
    }
}

تهی WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = data->videodata;
    اگر (data->in_title_click || data->focus_click_pending || data->postpone_clipcursor) {
        بازگشت;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_درون_داد_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    اگر (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        اگر (!GetClipCursor(&current)) {
            بازگشت;
        }
        اگر (videodevice && (
            current.چپ != videodevice->desktop_bounds.x ||
            current.بالاترین  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.چپ;
            first.y  = current.بالاترین;
            second.x = current.راست  - 1;
            second.y = current.bottom - 1;
            اگر (!PtInRect(&data->cursor_clipped_rect, first) ||
                !PtInRect(&data->cursor_clipped_rect, second)) {
                بازگشت;
            }
        }
        ClipCursor(پوچ);
        SDL_zero(data->cursor_clipped_rect);
        بازگشت;
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
    اگر (!GetClientScreenRect(data->hwnd, &client)) {
        بازگشت;
    }

    RECT target = client;
    اگر (lock_to_ctr) {
        LONG cx = (client.چپ + client.راست ) / 2;
        LONG cy = (client.بالاترین  + client.bottom) / 2;
        target = data->cursor_ctrlock_rect;
        target.چپ   += cx;
        target.راست  += cx;
        target.بالاترین    += cy;
        target.bottom += cy;
    } وگرنه اگر (win_mouse_rect) {
        RECT custom, overlap;
        custom.چپ   = client.چپ + mouse_rect.x;
        custom.بالاترین    = client.بالاترین  + mouse_rect.y;
        custom.راست  = client.چپ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.بالاترین  + mouse_rect.y + mouse_rect.h;
        اگر (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } وگرنه اگر (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            بازگشت;
        }
    } وگرنه اگر (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        اگر (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(data->hwnd, MONITOR_DEFAULTTONEAREST);
            اگر (hmon) {
                UINT hdpi_uint, vdpi_uint;
                اگر (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت اعشاری scale = (اعشاری)hdpi_uint / (اعشاری)USER_DEFAULT_SCREEN_DPI;
                    اگر (scale != SDL_floorf(scale)) {
                        اگر (target.چپ < target.راست) {
                            target.چپ += 1;
                        }
                        اگر (target.راست > target.چپ) {
                            target.راست -= 1;
                        }
                        اگر (target.بالاترین < target.bottom) {
                            target.بالاترین += 1;
                        }
                        اگر (target.bottom > target.بالاترین) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    اگر (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, اندازه(client)) &&
        ClipCursor(&target)) {
        data->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    بازگشت true; // just succeed, the real work is done elsewhere.
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, اعشاری opacity)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    بازگشت false;
#وگرنه
    ثابت SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    اگر (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        اگر (style & WS_EX_LAYERED) {
            اگر (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                بازگشت WIN_SetError("SetWindowLong()");
            }
        }
    } وگرنه {
        ثابت BYTE alpha = (BYTE)((صحیح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        اگر (!(style & WS_EX_LAYERED)) {
            اگر (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                بازگشت WIN_SetError("SetWindowLong()");
            }
        }

        اگر (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            بازگشت WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    بازگشت true;
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ایستا ثابت نویسه *SDLGetClipboardFormatName(UINT cf, نویسه *text, صحیح len)
{
    انتخاب (cf) {
    حالت CF_TEXT:
        بازگشت "CF_TEXT";
    حالت CF_BITMAP:
        بازگشت "CF_BITMAP";
    حالت CF_METAFILEPICT:
        بازگشت "CF_METAFILEPICT";
    حالت CF_SYLK:
        بازگشت "CF_SYLK";
    حالت CF_DIF:
        بازگشت "CF_DIF";
    حالت CF_TIFF:
        بازگشت "CF_TIFF";
    حالت CF_OEMTEXT:
        بازگشت "CF_OEMTEXT";
    حالت CF_DIB:
        بازگشت "CF_DIB";
    حالت CF_PALETTE:
        بازگشت "CF_PALETTE";
    حالت CF_PENDATA:
        بازگشت "CF_PENDATA";
    حالت CF_RIFF:
        بازگشت "CF_RIFF";
    حالت CF_WAVE:
        بازگشت "CF_WAVE";
    حالت CF_UNICODETEXT:
        بازگشت "CF_UNICODETEXT";
    حالت CF_ENHMETAFILE:
        بازگشت "CF_ENHMETAFILE";
    حالت CF_HDROP:
        بازگشت "CF_HDROP";
    حالت CF_LOCALE:
        بازگشت "CF_LOCALE";
    حالت CF_DIBV5:
        بازگشت "CF_DIBV5";
    حالت CF_OWNERDISPLAY:
        بازگشت "CF_OWNERDISPLAY";
    حالت CF_DSPTEXT:
        بازگشت "CF_DSPTEXT";
    حالت CF_DSPBITMAP:
        بازگشت "CF_DSPBITMAP";
    حالت CF_DSPMETAFILEPICT:
        بازگشت "CF_DSPMETAFILEPICT";
    حالت CF_DSPENHMETAFILE:
        بازگشت "CF_DSPENHMETAFILE";
    پیشفرض:
        اگر (GetClipboardFormatNameA(cf, text, len)) {
            بازگشت text;
        } وگرنه {
            بازگشت پوچ;
        }
    }
}

ایستا STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    بازگشت ++target->refcount;
}

ایستا STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    اگر (target->refcount == 0) {
        SDL_free(target);
        بازگشت 0;
    }
    بازگشت target->refcount;
}

ایستا STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    اگر (ppv == پوچ) {
        بازگشت E_INVALIDARG;
    }

    *ppv = پوچ;
    اگر (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (تهی *)target;
    }
    اگر (*ppv) {
        SDLDropTarget_AddRef(target);
        بازگشت S_OK;
    }
    بازگشت E_NOINTERFACE;
}

ایستا STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *pDataObject, DWORD grf_کلید_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    اگر (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    بازگشت S_OK;
}

ایستا STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_کلید_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    اگر (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    بازگشت S_OK;
}

ایستا STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    بازگشت S_OK;
}

ایستا STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *pDataObject, DWORD grf_کلید_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    اگر (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = pDataObject->lpVtbl->EnumFormatEtc(pDataObject, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        اگر (hres == S_OK) {
            FORMATETC fetc;
            وقتی (pEnumFormatEtc->lpVtbl->Next(pEnumFormatEtc, 1, &fetc, پوچ) == S_OK) {
                نویسه name[257] = { 0 };
                ثابت نویسه *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                اگر (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وگرنه {
                    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = پوچ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت نویسه *format_mime = "text/uri-list";
        اگر (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت تهی *buffer = (تهی *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                اگر (buffer) {
                    نویسه *text = (نویسه *)SDL_malloc(bsize + اندازه(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, اندازه(Uint32));
                    نویسه *saveptr = پوچ;
                    نویسه *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    وقتی (token != پوچ) {
                        اگر (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                            SDL_SendDropFile(target->window, پوچ, token);
                        }
                        token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                بازگشت S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = پوچ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت نویسه *format_mime = "text/plain;charset=utf-8";
        اگر (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت تهی *buffer = (تهی *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                اگر (buffer) {
                    نویسه *text = (نویسه *)SDL_malloc(bsize + اندازه(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, اندازه(Uint32));
                    نویسه *saveptr = پوچ;
                    نویسه *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    وقتی (token != پوچ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (نویسه *)token);
                        token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                بازگشت S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = پوچ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت نویسه *format_mime = "CF_UNICODETEXT";
        اگر (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت تهی *buffer = (تهی *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                اگر (buffer) {
                    buffer = WIN_StringToUTF8W((ثابت wchar_t *)buffer);
                    اگر (buffer) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت نویسه *)buffer);
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (unsigned long)lbuffer, buffer);
                        نویسه *text = (نویسه *)SDL_malloc(lbuffer + اندازه(Uint32));
                        SDL_memcpy((Uint8 *)text, buffer, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, اندازه(Uint32));
                        نویسه *saveptr = پوچ;
                        نویسه *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        وقتی (token != پوچ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(token), (unsigned long)lbuffer, token);
                            SDL_SendDropText(target->window, (نویسه *)token);
                            token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((تهی *)buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                بازگشت S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = پوچ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت نویسه *format_mime = "CF_TEXT";
        اگر (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                ثابت تهی *buffer = (تهی *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, buffer);
                اگر (buffer) {
                    نویسه *text = (نویسه *)SDL_malloc(bsize + اندازه(Uint32));
                    SDL_memcpy((Uint8 *)text, buffer, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, اندازه(Uint32));
                    نویسه *saveptr = پوچ;
                    نویسه *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    وقتی (token != پوچ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (unsigned long)SDL_strlen(token), (unsigned long)bsize, token);
                        SDL_SendDropText(target->window, (نویسه *)token);
                        token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                بازگشت S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = پوچ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت نویسه *format_mime = "CF_HDROP";
        اگر (SUCCEEDED(pDataObject->lpVtbl->QueryGetData(pDataObject, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = pDataObject->lpVtbl->GetData(pDataObject, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = GlobalSize(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (unsigned long)bsize, drop);
                UINT شمار = DragQueryFile(drop, 0xFFFFFFFF, پوچ, 0);
                برای (UINT i = 0; i < شمار; ++i) {
                    UINT size = DragQueryFile(drop, i, پوچ, 0) + 1;
                    LPTSTR buffer = (LPTSTR)SDL_malloc(size * اندازه(TCHAR));
                    اگر (buffer) {
                        اگر (DragQueryFile(drop, i, buffer, size)) {
                            نویسه *file = WIN_StringToUTF8(buffer);
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (unsigned long)SDL_strlen(file), (unsigned long)bsize, file);
                            SDL_SendDropFile(target->window, پوچ, file);
                            SDL_free(file);
                        }
                        SDL_free(buffer);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                بازگشت S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    بازگشت S_OK;
}

ایستا تهی *vtDropTarget[] = {
    (تهی *)(SDLDropTarget_QueryInterface),
    (تهی *)(SDLDropTarget_AddRef),
    (تهی *)(SDLDropTarget_Release),
    (تهی *)(SDLDropTarget_DragEnter),
    (تهی *)(SDLDropTarget_DragOver),
    (تهی *)(SDLDropTarget_DragLeave),
    (تهی *)(SDLDropTarget_Drop)
};

تهی WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    اگر (data->videodata->oleinitialized) {
        اگر (accept && !data->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, اندازه(SDLDropTarget));
            اگر (drop_target != پوچ) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = data->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                data->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(data->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } وگرنه اگر (!accept && data->drop_target) {
            RevokeDragDrop(data->hwnd);
            SDLDropTarget_Release(data->drop_target);
            data->drop_target = پوچ;
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } وگرنه {
        DragAcceptFiles(data->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cbSize = اندازه(desc);
    desc.hwnd = window->internal->hwnd;
    انتخاب (operation) {
    حالت SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        بشکن;
    حالت SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_شمار = 1;
        بشکن;
    حالت SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        بشکن;
    پیشفرض:
        بازگشت SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    بازگشت true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *data = window->internal;
    اگر (!data->taskbar_button_created) {
        بازگشت true;
    }

    اگر (window->progress_state == SDL_PROGRESS_STATE_NONE && !data->videodata->taskbar_list) {
        بازگشت true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    اگر (!taskbar_list) {
        بازگشت false;
    }

    TBPFLAG tbpFlags;
    انتخاب (window->progress_state) {
    حالت SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        بشکن;
    حالت SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        بشکن;
    حالت SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        بشکن;
    حالت SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        بشکن;
    حالت SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        بشکن;
    پیشفرض:
        بازگشت SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, data->hwnd, tbpFlags);
    اگر (FAILED(ret)) {
        بازگشت WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    اگر (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_مقدار(taskbar_list, data->hwnd, (ULONGLONG)(window->progress_مقدار * 10000.f), 10000);
        اگر (FAILED(ret)) {
            بازگشت WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#endif
    بازگشت true;
}

تهی WIN_ShowWindowSystemMenu(SDL_Window *window, صحیح x, صحیح y)
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
    اگر (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        HWND hwnd = data->hwnd;
        ثابت LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        اگر (focusable) {
            اگر (style & WS_EX_NOACTIVATE) {
                اگر (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    بازگشت WIN_SetError("SetWindowLong()");
                }
            }
        } وگرنه {
            اگر (!(style & WS_EX_NOACTIVATE)) {
                اگر (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    بازگشت WIN_SetError("SetWindowLong()");
                }
            }
        }
    } وگرنه اگر (window->flags & SDL_WINDOW_POPUP_MENU) {
        اگر (!(window->flags & SDL_WINDOW_HIDDEN)) {
            اگر (!focusable && (window->flags & SDL_WINDOW_درون_داد_FOCUS)) {
                SDL_Window *new_focus;
                ثابت bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } وگرنه اگر (focusable) {
                اگر (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        بازگشت true;
    }

    بازگشت true;
}
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_WindowData *child_data = window->internal;
    ثابت LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : پوچ);
    ثابت DWORD style = GetWindowLong(child_data->hwnd, GWL_STYLE);

    اگر (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_data->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } وگرنه {
        SetParent(child_data->hwnd, (HWND)parent_hwnd);
    }
#endif /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    بازگشت true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND parent_hwnd = window->parent->internal->hwnd;

    اگر (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } وگرنه اگر (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#endif // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    بازگشت true;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS
