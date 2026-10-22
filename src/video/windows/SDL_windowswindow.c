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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS

#समावेश "../../core/windows/SDL_windows.h"

#समावेश "../../SDL_hints_c.h"
#समावेश "../../events/SDL_dropevents_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_windowevents_c.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../SDL_sysvideo.h"

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowskeyboard.h"
#समावेश "SDL_windowswindow.h"

// Dropfile support
#समावेश <shellapi.h>

#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#समावेश <shobjidl.h>
#पूर्ण_अगर

// Windows CE compatibility
#अगर_अघोषित SWP_NOCOPYBITS
#घोषणा SWP_NOCOPYBITS 0
#पूर्ण_अगर

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#अगर_अघोषित WM_POPUPSYSTEMMENU
#घोषणा WM_POPUPSYSTEMMENU 0x313
#पूर्ण_अगर

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

#घोषणा STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#घोषणा STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#घोषणा STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#घोषणा STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#घोषणा STYLE_NORMAL              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#घोषणा STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#घोषणा STYLE_MASK                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_NORMAL | STYLE_RESIZABLE)

अटल DWORD GetWindowStyle(SDL_Window *window)
{
    DWORD style = 0;

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        style |= WS_POPUP;
    } अन्यथा अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } अन्यथा {
        अगर (window->flags & SDL_WINDOW_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            अगर (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
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
        अगर (window->flags & SDL_WINDOW_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            अगर (!(window->flags & SDL_WINDOW_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        अगर (window->internal && window->internal->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        अगर (window->flags & SDL_WINDOW_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    वापस style;
}

अटल DWORD GetWindowStyleEx(SDL_Window *window)
{
    DWORD style = 0;

    अगर (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    अगर (SDL_WINDOW_IS_POPUP(window) || (window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    वापस style;
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
अटल ITaskbarList3 *GetTaskbarList(SDL_Window *window)
{
    स्थिर SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_assert(तथ्य->taskbar_button_created);
    अगर (!तथ्य->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, शून्य, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&तथ्य->videodata->taskbar_list);
        अगर (FAILED(ret)) {
            WIN_SetErrorFromHRESULT("Unable to create taskbar list", ret);
            वापस शून्य;
        }
        ITaskbarList3 *taskbarlist = तथ्य->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        अगर (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            तथ्य->videodata->taskbar_list = शून्य;
            WIN_SetErrorFromHRESULT("Unable to initialize taskbar list", ret);
            वापस शून्य;
        }
    }
    वापस तथ्य->videodata->taskbar_list;
}
#पूर्ण_अगर

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
अटल bool WIN_AdjustWindowRectWithStyle(SDL_Window *window, DWORD style, DWORD styleEx, BOOL menu, पूर्णांक *x, पूर्णांक *y, पूर्णांक *width, पूर्णांक *height, SDL_WindowRect rect_type)
{
    SDL_Video_तथ्य *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->internal : शून्य;
    RECT rect;

    // Client rect, in points
    चयन (rect_type) {
    हाल SDL_WINDOWRECT_CURRENT:
        SDL_RelativeToGlobalForWindow(window, window->x, window->y, x, y);
        *width = window->w;
        *height = window->h;
        अवरोध;
    हाल SDL_WINDOWRECT_WINDOWED:
        SDL_RelativeToGlobalForWindow(window, window->windowed.x, window->windowed.y, x, y);
        *width = window->windowed.w;
        *height = window->windowed.h;
        अवरोध;
    हाल SDL_WINDOWRECT_FLOATING:
        SDL_RelativeToGlobalForWindow(window, window->floating.x, window->floating.y, x, y);
        *width = window->floating.w;
        *height = window->floating.h;
        अवरोध;
    हाल SDL_WINDOWRECT_PENDING:
        SDL_RelativeToGlobalForWindow(window, window->pending.x, window->pending.y, x, y);
        *width = window->pending.w;
        *height = window->pending.h;
        अवरोध;
    शेष:
        // Should never be here
        SDL_assert_release(false);
        *width = 0;
        *height = 0;
        अवरोध;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.बायाँ = 0;
    rect.शीर्ष = 0;
    rect.दायाँ = *width;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    अगर (!(window->flags & SDL_WINDOW_BORDERLESS) && !SDL_WINDOW_IS_POPUP(window)) {
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        AdjustWindowRectEx(&rect, style, menu, 0);
#अन्यथा
        अगर (WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            अगर (videodata) {
                UINT frame_dpi;
                SDL_Window_तथ्य *तथ्य = window->internal;
                frame_dpi = (तथ्य && videodata->GetDpiForWindow) ? videodata->GetDpiForWindow(तथ्य->hwnd) : USER_DEFAULT_SCREEN_DPI;
                अगर (videodata->AdjustWindowRectExForDpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    वापस WIN_SetError("AdjustWindowRectExForDpi()");
                }
            }
        } अन्यथा {
            अगर (AdjustWindowRectEx(&rect, style, menu, styleEx) == 0) {
                वापस WIN_SetError("AdjustWindowRectEx()");
            }
        }
#पूर्ण_अगर
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.बायाँ;
    *y += rect.शीर्ष;
    *width = (rect.दायाँ - rect.बायाँ);
    *height = (rect.bottom - rect.शीर्ष);

#अगर_घोषित HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.x : window->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.y : window->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.w : window->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? window->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? window->windowed.h : window->h),
            *x, *y, *width, *height, frame_dpi);
#पूर्ण_अगर
    वापस true;
}

bool WIN_AdjustWindowRect(SDL_Window *window, पूर्णांक *x, पूर्णांक *y, पूर्णांक *width, पूर्णांक *height, SDL_WindowRect rect_type)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != शून्य);
#पूर्ण_अगर
    वापस WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu, x, y, width, height, rect_type);
}

bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_तथ्य *videodata = videodevice ? videodevice->internal : शून्य;
    DWORD style, styleEx;
    BOOL menu;

    style = GetWindowLong(hwnd, GWL_STYLE);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != शून्य);
#पूर्ण_अगर

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    AdjustWindowRectEx(lpRect, style, menu, styleEx);
#अन्यथा
    अगर (WIN_IsPerMonitorV2DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        अगर (!frame_dpi) {
            frame_dpi = videodata->GetDpiForWindow ? videodata->GetDpiForWindow(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        अगर (!videodata->AdjustWindowRectExForDpi(lpRect, style, menu, styleEx, frame_dpi)) {
            वापस WIN_SetError("AdjustWindowRectExForDpi()");
        }
    } अन्यथा {
        अगर (!AdjustWindowRectEx(lpRect, style, menu, styleEx)) {
            वापस WIN_SetError("AdjustWindowRectEx()");
        }
    }
#पूर्ण_अगर
    वापस true;
}

bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type)
{
    SDL_Window *child_window;
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    HWND शीर्ष;
    पूर्णांक x, y;
    पूर्णांक w, h;
    bool परिणाम = true;

    // Figure out what the window area will be
    अगर (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
        शीर्ष = HWND_TOPMOST;
    } अन्यथा {
        शीर्ष = HWND_NOTOPMOST;
    }

    WIN_AdjustWindowRect(window, &x, &y, &w, &h, rect_type);

    तथ्य->expected_resize = !(flags & SWP_NOSIZE);
    अगर (SetWindowPos(hwnd, शीर्ष, x, y, w, h, flags) == 0) {
        परिणाम = WIN_SetError("SetWindowPos()");
    }
    तथ्य->expected_resize = false;

    // Update any child windows
    क्रम (child_window = window->first_child; child_window; child_window = child_window->अग्र_sibling) {
        अगर (!child_window->internal) {
            // This child window is not yet fully initialized.
            जारी;
        }
        अगर (!WIN_SetWindowPositionInternal(child_window, flags, SDL_WINDOWRECT_CURRENT)) {
            परिणाम = false;
        }
    }
    वापस परिणाम;
}

अटल SDL_WindowEraseBackgroundMode GetEraseBackgroundModeHint(व्योम)
{
    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE);
    अगर (!hint)
        वापस SDL_ERASEBACKGROUNDMODE_INITIAL;

    अगर (SDL_strstr(hint, "never"))
        वापस SDL_ERASEBACKGROUNDMODE_NEVER;

    अगर (SDL_strstr(hint, "initial"))
        वापस SDL_ERASEBACKGROUNDMODE_INITIAL;

    अगर (SDL_strstr(hint, "always"))
        वापस SDL_ERASEBACKGROUNDMODE_ALWAYS;

    पूर्णांक mode = SDL_GetStringInteger(hint, 1);
    अगर (mode < 0 || mode > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        वापस SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    वापस (SDL_WindowEraseBackgroundMode)mode;
}

अटल bool Setup_Window_तथ्य(SDL_VideoDevice *_this, SDL_Window *window, HWND hwnd, HWND parent)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_Window_तथ्य *तथ्य;

    // Allocate the window data
    तथ्य = (SDL_Window_तथ्य *)SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }
    तथ्य->window = window;
    तथ्य->hwnd = hwnd;
    तथ्य->parent = parent;
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    तथ्य->hdc = (HDC)तथ्य->hwnd;
#अन्यथा
    तथ्य->hdc = GetDC(hwnd);
#पूर्ण_अगर
    तथ्य->hinstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    तथ्य->mouse_button_flags = (WPARAM)-1;
    तथ्य->last_pointer_update = (LPARAM)-1;
    तथ्य->videodata = videodata;
    तथ्य->initializing = true;
    तथ्य->hint_erase_background_mode = GetEraseBackgroundModeHint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    तथ्य->cursor_ctrlock_rect.बायाँ   = 0 - remote_desktop_adjustment;
    तथ्य->cursor_ctrlock_rect.शीर्ष    = 0;
    तथ्य->cursor_ctrlock_rect.दायाँ  = 1 + remote_desktop_adjustment;
    तथ्य->cursor_ctrlock_rect.bottom = 1;
#पूर्ण_अगर

    अगर (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        तथ्य->copybits_flag = 0;
    } अन्यथा {
        तथ्य->copybits_flag = SWP_NOCOPYBITS;
    }

#अगर_घोषित HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", तथ्य->scaling_dpi);
#पूर्ण_अगर

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    अगर (!SetProp(hwnd, TEXT("SDL_WindowData"), तथ्य)) {
        ReleaseDC(hwnd, तथ्य->hdc);
        SDL_free(तथ्य);
        वापस WIN_SetError("SetProp() failed");
    }
#पूर्ण_अगर

    window->internal = तथ्य;

    // Set up the window proc function
    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
#अगर_घोषित GWLP_WNDPROC
        तथ्य->wndproc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        अगर (तथ्य->wndproc != WIN_WindowProc) {
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#अन्यथा
        तथ्य->wndproc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
        अगर (तथ्य->wndproc != WIN_WindowProc) {
            SetWindowLong(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_WindowProc);
        }
#पूर्ण_अगर
    } अन्यथा {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        अगर (style & WS_VISIBLE) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } अन्यथा {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        अगर (style & WS_POPUP) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        अगर (style & WS_THICKFRAME) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा अगर (!(style & WS_POPUP)) {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
#अगर_घोषित WS_MAXIMIZE
        अगर (style & WS_MAXIMIZE) {
            window->flags |= SDL_WINDOW_MAXIMIZED;
        } अन्यथा
#पूर्ण_अगर
        {
            window->flags &= ~SDL_WINDOW_MAXIMIZED;
        }
#अगर_घोषित WS_MINIMIZE
        अगर (style & WS_MINIMIZE) {
            window->flags |= SDL_WINDOW_MINIMIZED;
        } अन्यथा
#पूर्ण_अगर
        {
            window->flags &= ~SDL_WINDOW_MINIMIZED;
        }
    }
    अगर (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        RECT rect;
        अगर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
            पूर्णांक w = rect.दायाँ;
            पूर्णांक h = rect.bottom;

            अगर (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.w = window->windowed.w = window->w = w;
                window->floating.h = window->windowed.h = window->h = h;
            } अन्यथा अगर ((window->windowed.w && window->windowed.w != w) || (window->windowed.h && window->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                पूर्णांक x, y;
                // Figure out what the window area will be
                WIN_AdjustWindowRect(window, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                तथ्य->expected_resize = true;
                SetWindowPos(hwnd, शून्य, x, y, w, h, तथ्य->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                तथ्य->expected_resize = false;
            } अन्यथा {
                window->w = w;
                window->h = h;
            }
        }
    }
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        अगर (ClientToScreen(hwnd, &point)) {
            अगर (window->flags & SDL_WINDOW_EXTERNAL) {
                window->floating.x = window->windowed.x = point.x;
                window->floating.y = window->windowed.y = point.y;
            }
            window->x = point.x;
            window->y = point.y;
        }
    }

    WIN_UpdateWindowICCProfile(window, false);
#पूर्ण_अगर

#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    window->flags |= SDL_WINDOW_निवेश_FOCUS;
    SDL_SetKeyboardFocus(window);
#अन्यथा
    अगर (GetFocus() == hwnd) {
        window->flags |= SDL_WINDOW_निवेश_FOCUS;
        SDL_SetKeyboardFocus(window);
        WIN_UpdateClipCursor(window);
    }
#पूर्ण_अगर

    अगर (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) {
        WIN_Set_Window_Always_On_शीर्ष(_this, window, true);
    } अन्यथा {
        WIN_Set_Window_Always_On_शीर्ष(_this, window, false);
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    अगर (videodata->RegisterTouchWindow) {
        videodata->RegisterTouchWindow(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#पूर्ण_अगर

    अगर (तथ्य->parent && !window->parent) {
        तथ्य->destroy_parent_with_window = true;
    }

    तथ्य->initializing = false;

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        पूर्णांक titleLen;
        bool isstack;

        titleLen = Get_Window_Text_लंबाई(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        अगर (title) {
            titleLen = GetWindowText(hwnd, title, titleLen + 1);
        } अन्यथा {
            titleLen = 0;
        }
        अगर (titleLen > 0) {
            window->title = WIN_StringToUTF8(title);
        }
        अगर (title) {
            SDL_small_free(title, isstack);
        }
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, तथ्य->hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HDC_POINTER, तथ्य->hdc);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, तथ्य->hinstance);

    // All done!
    वापस true;
}

अटल व्योम Cleanup_Window_तथ्य(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य) {
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        अगर (तथ्य->drop_target) {
            WIN_AcceptDragAndDrop(window, false);
        }
        SDL_free(तथ्य->ICMFileName);
        अगर (तथ्य->keyboard_hook) {
            UnhookWindowsHookEx(तथ्य->keyboard_hook);
        }
        अगर (तथ्य->hicon) {
            DestroyIcon(तथ्य->hicon);
        }
        ReleaseDC(तथ्य->hwnd, तथ्य->hdc);
        RemoveProp(तथ्य->hwnd, TEXT("SDL_WindowData"));
#पूर्ण_अगर
        अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            DestroyWindow(तथ्य->hwnd);
            अगर (तथ्य->destroy_parent_with_window && तथ्य->parent) {
                DestroyWindow(तथ्य->parent);
            }
        } अन्यथा {
            // Restore any original event handler...
            अगर (तथ्य->wndproc) {
#अगर_घोषित GWLP_WNDPROC
                SetWindowLongPtr(तथ्य->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)तथ्य->wndproc);
#अन्यथा
                SetWindowLong(तथ्य->hwnd, GWL_WNDPROC,
                              (LONG_PTR)तथ्य->wndproc);
#पूर्ण_अगर
            }
        }
        SDL_free(तथ्य);
    }
    window->internal = शून्य;
}

अटल व्योम WIN_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Possibly clamp popup windows to the output borders
    अगर (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णांक abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        पूर्णांक abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        स्थिर पूर्णांक width = window->last_आकार_pending ? window->pending.w : window->floating.w;
        स्थिर पूर्णांक height = window->last_आकार_pending ? window->pending.h : window->floating.h;
        पूर्णांक offset_x = 0, offset_y = 0;

        अगर (window->constrain_popup) {
            // Calculate the total offset from the parents
            क्रम (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
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
            अगर (abs_x + width > rect.x + rect.w) {
                abs_x -= (abs_x + width) - (rect.x + rect.w);
            }
            अगर (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        अगर (output_to_pending) {
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

अटल व्योम WIN_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the topmost parent
    जबतक (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    अगर (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", शून्य));
    HWND parent = शून्य;
    अगर (hwnd) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        अगर (!Setup_Window_तथ्य(_this, window, hwnd, parent)) {
            वापस false;
        }
    } अन्यथा {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        पूर्णांक x, y;
        पूर्णांक w, h;

        अगर (window->flags & SDL_WINDOW_UTILITY) {
            parent = CreateWindow(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, शून्य, शून्य, SDL_Instance, शून्य);
        } अन्यथा अगर (window->parent) {
            parent = window->parent->internal->hwnd;
        }

        style |= GetWindowStyle(window);
        styleEx |= (DWORD)SDL_Get_संख्या_Property(create_props, SDL_PROP_WINDOW_CREATE_WIN32_STYLE_EX_संख्या, GetWindowStyleEx(window));

        // Figure out what the window area will be
        WIN_ConstrainPopup(window, false);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = CreateWindowEx(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, शून्य, SDL_Instance, शून्य);
        अगर (!hwnd) {
            वापस WIN_SetError("Couldn't create window");
        }

        WIN_UpdateDarkModeForHWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        अगर (!Setup_Window_तथ्य(_this, window, hwnd, parent)) {
            DestroyWindow(hwnd);
            अगर (parent) {
                DestroyWindow(parent);
            }
            वापस false;
        }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_निवेश(_this, window);
#पूर्ण_अगर

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        SetWindowPos(hwnd, शून्य, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        अगर (window->flags & SDL_WINDOW_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            window->flags &= ~SDL_WINDOW_HIDDEN;
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    अगर (window->flags & SDL_WINDOW_TRANSPARENT) {
        अगर (videodata->DwmEnableBlurBehindWindow) {
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

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, शून्य);
    अगर (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        पूर्णांक pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, माप(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        अगर (!SetPixelFormat(window->internal->hdc, pixel_format, &pfd)) {
            WIN_DestroyWindow(_this, window);
            वापस WIN_SetError("SetPixelFormat()");
        }
    } अन्यथा {
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        अगर (!(window->flags & SDL_WINDOW_OPENGL)) {
            वापस true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#अगर_घोषित SDL_VIDEO_OPENGL_ES2
        अगर ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#अगर_घोषित SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_तथ्य || WIN_GL_UseEGL(_this))
#पूर्ण_अगर // SDL_VIDEO_OPENGL_WGL
        ) {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
            अगर (!WIN_GLES_SetupWindow(_this, window)) {
                WIN_DestroyWindow(_this, window);
                वापस false;
            }
            वापस true;
#अन्यथा
            वापस SDL_SetError("Could not create GLES window surface (EGL support not configured)");
#पूर्ण_अगर // SDL_VIDEO_OPENGL_EGL
        }
#पूर्ण_अगर // SDL_VIDEO_OPENGL_ES2

#अगर_घोषित SDL_VIDEO_OPENGL_WGL
        अगर (!WIN_GL_SetupWindow(_this, window)) {
            WIN_DestroyWindow(_this, window);
            वापस false;
        }
#अन्यथा
        वापस SDL_SetError("Could not create GL window (WGL support not configured)");
#पूर्ण_अगर
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    वापस true;
}

व्योम WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    LPTSTR title = WIN_UTF8ToString(window->title);
    SetWindowText(hwnd, title);
    SDL_free(title);
#पूर्ण_अगर
}

bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    HICON hicon = शून्य;
    BYTE *icon_bmp;
    पूर्णांक icon_len, mask_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool परिणाम = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_SetWindowIcon_uses_BITMAPINFOHEADER_to_prepare_an_ICONIMAGE, माप(BITMAPINFOHEADER) == 40);
    mask_len = (icon->h * (icon->w + 7) / 8);
    icon_len = माप(BITMAPINFOHEADER) + icon->h * icon->w * माप(Uint32) + mask_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    अगर (!icon_bmp) {
        वापस false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_आकार = SDL_Swap32LE(माप(BITMAPINFOHEADER));
    bmi->biWidth = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_गिनती = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_आकार_Image = SDL_Swap32LE(icon->h * icon->w * माप(Uint32));
    bmi->biXPelsPerMeter = SDL_Swap32LE(0);
    bmi->biYPelsPerMeter = SDL_Swap32LE(0);
    bmi->biClrUsed = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[माप(BITMAPINFOHEADER)];
    row_len = icon->w * माप(Uint32);
    y = icon->h;
    जबतक (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - mask_len, 0xFF, mask_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    अगर (!hicon) {
        वापस SDL_SetError("SetWindowIcon() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    अगर (तथ्य->hicon) {
        DestroyIcon(तथ्य->hicon);
    }
    तथ्य->hicon = hicon;

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    वापस परिणाम;
#अन्यथा
    वापस SDL_Unsupported();
#पूर्ण_अगर
}

bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        अगर (!(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
            WIN_ConstrainPopup(window, true);
            वापस WIN_SetWindowPositionInternal(window,
                                                 window->internal->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } अन्यथा {
        वापस SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, true);
    }

    वापस true;
}

व्योम WIN_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        WIN_SetWindowPositionInternal(window, window->internal->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } अन्यथा {
        // Can't resize the window
        window->last_आकार_pending = false;
    }
}

bool WIN_Get_Window_Borders_आकार(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *बायाँ, पूर्णांक *bottom, पूर्णांक *दायाँ)
{
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *शीर्ष = rcClient.शीर्ष;
    *बायाँ = rcClient.बायाँ;
    *bottom = rcClient.bottom;
    *दायाँ = rcClient.दायाँ;

    वापस true;
#अन्यथा  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = window->internal->hwnd;
    RECT rcClient, rcWindow;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    अगर (!GetClientRect(hwnd, &rcClient)) {
        वापस SDL_SetError("GetClientRect() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    अगर (!GetWindowRect(hwnd, &rcWindow)) {
        वापस SDL_SetError("GetWindowRect() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rcWindow.शीर्ष;
    ptDiff.x = rcWindow.बायाँ;

    अगर (!ScreenToClient(hwnd, &ptDiff)) {
        वापस SDL_SetError("ScreenToClient() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    rcWindow.शीर्ष = ptDiff.y;
    rcWindow.बायाँ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rcWindow.bottom;
    ptDiff.x = rcWindow.दायाँ;

    अगर (!ScreenToClient(hwnd, &ptDiff)) {
        वापस SDL_SetError("ScreenToClient() failed, error %08X", (अचिन्हित पूर्णांक)GetLastError());
    }

    rcWindow.bottom = ptDiff.y;
    rcWindow.दायाँ = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *शीर्ष = rcClient.शीर्ष - rcWindow.शीर्ष;
    *बायाँ = rcClient.बायाँ - rcWindow.बायाँ;
    *bottom = rcWindow.bottom - rcClient.bottom;
    *दायाँ = rcWindow.दायाँ - rcClient.दायाँ;

    वापस true;
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

व्योम WIN_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    स्थिर SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    RECT rect;

    अगर (GetClientRect(hwnd, &rect) && WIN_WindowRectValid(&rect)) {
        *w = rect.दायाँ;
        *h = rect.bottom;
    } अन्यथा अगर (window->last_pixel_w && window->last_pixel_h) {
        *w = window->last_pixel_w;
        *h = window->last_pixel_h;
    } अन्यथा {
        // Probably created minimized, use the restored size
        *w = window->floating.w;
        *h = window->floating.h;
    }
}

व्योम WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        // Update our position in case our parent moved while we were hidden
        WIN_SetWindowPosition(_this, window);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    अगर (window->pending_flags & SDL_WINDOW_FULLSCREEN) {
        अगर (!(window->flags & SDL_WINDOW_BORDERLESS)) {
            window->flags |= SDL_WINDOW_BORDERLESS;
            style = GetWindowLong(hwnd, GWL_STYLE);
            style &= ~STYLE_MASK;
            style |= GetWindowStyle(window);
            SetWindowLong(hwnd, GWL_STYLE, style);
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
    }
    style = GetWindowLong(hwnd, GWL_EXSTYLE);
    अगर (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    तथ्य->showing_window = true;
    अगर (bActivate) {
        ShowWindow(hwnd, SW_SHOW);
    } अन्यथा {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        SetWindowPos(hwnd, शून्य, 0, 0, 0, 0, window->internal->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    तथ्य->showing_window = false;

    अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) && bActivate) {
        WIN_SetKeyboardFocus(window, true);
    }
    अगर (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, true);
    }
}

व्योम WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;

    अगर (window->flags & SDL_WINDOW_MODAL) {
        WIN_SetWindowModal(_this, window, false);
    }

    ShowWindow(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        WIN_SetKeyboardFocus(new_focus, set_focus);
    }
}

व्योम WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

    HWND hCurWnd = शून्य;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    अगर (bForce) {
        hCurWnd = GetForegroundWindow();
        dwMyID = GetCurrentThreadId();
        dwCurID = GetWindowThreadProcessId(hCurWnd, शून्य);
        ShowWindow(hwnd, SW_RESTORE);
        Attach_Thread_निवेश(dwCurID, dwMyID, TRUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        अगर (!SDL_ShouldAllowTopmost() || !(window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    अगर (bActivate) {
        SetForegroundWindow(hwnd);
        अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
            WIN_SetKeyboardFocus(window, window->parent == SDL_GetKeyboardFocus());
        }
    } अन्यथा {
        SetWindowPos(hwnd, HWND_शीर्ष, 0, 0, 0, 0, तथ्य->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    अगर (bForce) {
        Attach_Thread_निवेश(dwCurID, dwMyID, FALSE);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

व्योम WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        HWND hwnd = तथ्य->hwnd;
        तथ्य->expected_resize = true;
        ShowWindow(hwnd, SW_MAXIMIZE);
        तथ्य->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        अगर (window->max_w || window->max_h) {
            पूर्णांक fx, fy, fw, fh;

            window->windowed.w = window->max_w ? SDL_min(window->w, window->max_w) : window->windowed.w;
            window->windowed.h = window->max_h ? SDL_min(window->h, window->max_h) : window->windowed.h;
            WIN_AdjustWindowRect(window, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            तथ्य->expected_resize = true;
            SetWindowPos(hwnd, HWND_शीर्ष, fx, fy, fw, fh, तथ्य->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            तथ्य->expected_resize = false;
        }
    } अन्यथा {
        तथ्य->windowed_mode_was_maximized = true;
    }
}

व्योम WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    HWND hwnd = window->internal->hwnd;
    ShowWindow(hwnd, SW_MINIMIZE);
}

व्योम WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    तथ्य->in_border_change = true;
    SetWindowLong(hwnd, GWL_STYLE, style);
    WIN_SetWindowPositionInternal(window, तथ्य->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    तथ्य->in_border_change = false;
}

व्योम WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    DWORD style;

    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);

    SetWindowLong(hwnd, GWL_STYLE, style);
}

व्योम WIN_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष)
{
    WIN_SetWindowPositionInternal(window, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

व्योम WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        अगर (!तथ्य->showing_window || window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)) {
            HWND hwnd = तथ्य->hwnd;
            तथ्य->expected_resize = true;
            ShowWindow(hwnd, SW_RESTORE);
            तथ्य->expected_resize = false;
        }
    } अन्यथा {
        तथ्य->windowed_mode_was_maximized = false;
    }
}

अटल व्योम WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_WINDOW_CORNER_PREFERENCE cornerPref)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *videodata = _this->internal;
    अगर (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPref, माप(cornerPref));
    }
#पूर्ण_अगर
}

अटल व्योम WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_तथ्य *videodata = _this->internal;
    अगर (videodata->DwmSetWindowAttribute && WIN_IsWindows11OrGreater()) {
        videodata->DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, माप(colorRef));
    }
#पूर्ण_अगर
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_परिणाम WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_तथ्य *displaydata = display->internal;
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य ? तथ्य->hwnd : शून्य;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND शीर्ष;
    पूर्णांक x, y;
    पूर्णांक w, h;
    bool enterMaximized = false;

#अगर_घोषित HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (पूर्णांक)fullscreen);
#पूर्ण_अगर

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    अगर (SDL_ShouldAllowTopmost() && (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष)) {
        शीर्ष = HWND_TOPMOST;
    } अन्यथा {
        शीर्ष = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_आकार = माप(MONITORINFO);
    अगर (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_SetError("GetMonitorInfo failed");
        वापस SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~STYLE_MASK;
    style |= GetWindowStyle(window);
    styleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

    अगर (fullscreen) {
        x = minfo.rcMonitor.बायाँ;
        y = minfo.rcMonitor.शीर्ष;
        w = minfo.rcMonitor.दायाँ - minfo.rcMonitor.बायाँ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.शीर्ष;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        अगर (style & WS_MAXIMIZE) {
            तथ्य->windowed_mode_was_maximized = true;
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
        अगर (तथ्य->windowed_mode_was_maximized && !तथ्य->in_window_deactivation) {
            enterMaximized = true;
            तथ्य->disable_move_आकार_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != शून्य);
        WIN_AdjustWindowRectWithStyle(window, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        तथ्य->windowed_mode_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        अगर (enterMaximized) {
            स्थिर SDL_Point windowed_point = { window->windowed.x, window->windowed.y };
            स्थिर SDL_Point floating_point = { window->floating.x, window->floating.y };
            स्थिर SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            स्थिर SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            अगर (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                अगर (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } अन्यथा {
                    x = bounds.x;
                }
                अगर (h < bounds.h) {
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
    तथ्य->expected_resize = true;
    SetWindowPos(hwnd, शीर्ष, x, y, w, h, तथ्य->copybits_flag | SWP_NOACTIVATE);
    तथ्य->expected_resize = false;
    तथ्य->disable_move_आकार_events = false;

    अगर (enterMaximized) {
        WIN_MaximizeWindow(_this, window);
    }

    अगर (!fullscreen && तथ्य && तथ्य->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)तथ्य->hicon);
    }

#अगर_घोषित HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (पूर्णांक)fullscreen, x, y, w, h);
#पूर्ण_अगर

#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    वापस SDL_FULLSCREEN_SUCCEEDED;
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
व्योम WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);

    अगर (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, शून्य, शून्य, शून्य);
        अगर (hdc) {
            WCHAR fileName[MAX_PATH];
            DWORD file_Name_आकार = SDL_arraysize(fileName);
            अगर (GetICMProfileW(hdc, &file_Name_आकार, fileName)) {
                // fileNameSize includes '\0' on return
                अगर (!तथ्य->ICMFileName ||
                    SDL_wcscmp(तथ्य->ICMFileName, fileName) != 0) {
                    SDL_free(तथ्य->ICMFileName);
                    तथ्य->ICMFileName = SDL_wcsdup(fileName);
                    अगर (send_event) {
                        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

व्योम *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    अक्षर *filename_utf8;
    व्योम *icc_Profile_तथ्य = शून्य;

    filename_utf8 = WIN_StringToUTF8W(तथ्य->ICMFileName);
    अगर (filename_utf8) {
        icc_Profile_तथ्य = SDL_LoadFile(filename_utf8, आकार);
        अगर (!icc_Profile_तथ्य) {
            SDL_SetError("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    वापस icc_Profile_तथ्य;
}

अटल व्योम WIN_GrabKeyboard(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HMODULE module;

    अगर (तथ्य->keyboard_hook) {
        वापस;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    अगर (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        वापस;
    }

    // Capture a snapshot of the current keyboard state before the hook
    अगर (!GetKeyboardState(तथ्य->videodata->pre_hook_कुंजी_state)) {
        वापस;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    तथ्य->keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

व्योम WIN_UngrabKeyboard(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य->keyboard_hook) {
        UnhookWindowsHookEx(तथ्य->keyboard_hook);
        तथ्य->keyboard_hook = शून्य;
    }
}

bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    WIN_UpdateClipCursor(window);
    वापस true;
}

bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    WIN_UpdateClipCursor(window);
    वापस true;
}

bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    अगर (grabbed) {
        WIN_GrabKeyboard(window);
    } अन्यथा {
        WIN_UngrabKeyboard(window);
    }

    वापस true;
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

व्योम WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    Cleanup_Window_तथ्य(_this, window);
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
व्योम WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (!तथ्य || !तथ्य->hwnd) {
        // The window wasn't fully initialized
        वापस;
    }

    अगर (window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) {
        WIN_SetWindowPositionInternal(window, तथ्य->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

अटल BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    वापस GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           ClientToScreen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           ClientToScreen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

व्योम WIN_UnclipCursorForWindow(SDL_Window *window) {
    SDL_Window_तथ्य *तथ्य = window->internal;
    RECT rect;
    अगर (GetClipCursor(&rect) && SDL_memcmp(&rect, &तथ्य->cursor_clipped_rect, माप(rect)) == 0) {
        ClipCursor(शून्य);
        SDL_zero(तथ्य->cursor_clipped_rect);
    }
}

व्योम WIN_UpdateClipCursor(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Video_तथ्य *videodata = तथ्य->videodata;
    अगर (तथ्य->in_title_click || तथ्य->focus_click_pending || तथ्य->postpone_clipcursor) {
        वापस;
    }

    SDL_Rect mouse_rect = window->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (window->flags & SDL_WINDOW_निवेश_FOCUS);
    bool win_is_grabbed = (window->flags & SDL_WINDOW_MOUSE_GRABBED);
    bool win_in_relmode = (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);
    bool cursor_confine = win_in_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    अगर (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        अगर (!GetClipCursor(&current)) {
            वापस;
        }
        अगर (videodevice && (
            current.बायाँ != videodevice->desktop_bounds.x ||
            current.शीर्ष  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.बायाँ;
            first.y  = current.शीर्ष;
            second.x = current.दायाँ  - 1;
            second.y = current.bottom - 1;
            अगर (!PtInRect(&तथ्य->cursor_clipped_rect, first) ||
                !PtInRect(&तथ्य->cursor_clipped_rect, second)) {
                वापस;
            }
        }
        ClipCursor(शून्य);
        SDL_zero(तथ्य->cursor_clipped_rect);
        वापस;
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
    अगर (!GetClientScreenRect(तथ्य->hwnd, &client)) {
        वापस;
    }

    RECT target = client;
    अगर (lock_to_ctr) {
        LONG cx = (client.बायाँ + client.दायाँ ) / 2;
        LONG cy = (client.शीर्ष  + client.bottom) / 2;
        target = तथ्य->cursor_ctrlock_rect;
        target.बायाँ   += cx;
        target.दायाँ  += cx;
        target.शीर्ष    += cy;
        target.bottom += cy;
    } अन्यथा अगर (win_mouse_rect) {
        RECT custom, overlap;
        custom.बायाँ   = client.बायाँ + mouse_rect.x;
        custom.शीर्ष    = client.शीर्ष  + mouse_rect.y;
        custom.दायाँ  = client.बायाँ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.शीर्ष  + mouse_rect.y + mouse_rect.h;
        अगर (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } अन्यथा अगर (!win_is_grabbed) {
            WIN_UnclipCursorForWindow(window);
            वापस;
        }
    } अन्यथा अगर (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        अगर (videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
            HMONITOR hmon = MonitorFromWindow(तथ्य->hwnd, MONITOR_DEFAULTTONEAREST);
            अगर (hmon) {
                UINT hdpi_uint, vdpi_uint;
                अगर (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    स्थिर भग्न scale = (भग्न)hdpi_uint / (भग्न)USER_DEFAULT_SCREEN_DPI;
                    अगर (scale != SDL_floorf(scale)) {
                        अगर (target.बायाँ < target.दायाँ) {
                            target.बायाँ += 1;
                        }
                        अगर (target.दायाँ > target.बायाँ) {
                            target.दायाँ -= 1;
                        }
                        अगर (target.शीर्ष < target.bottom) {
                            target.शीर्ष += 1;
                        }
                        अगर (target.bottom > target.शीर्ष) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    अगर (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, माप(client)) &&
        ClipCursor(&target)) {
        तथ्य->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    वापस true; // just succeed, the real work is done elsewhere.
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity)
{
#अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    वापस false;
#अन्यथा
    स्थिर SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    स्थिर LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

    अगर (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        अगर (style & WS_EX_LAYERED) {
            अगर (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                वापस WIN_SetError("SetWindowLong()");
            }
        }
    } अन्यथा {
        स्थिर BYTE alpha = (BYTE)((पूर्णांक)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        अगर (!(style & WS_EX_LAYERED)) {
            अगर (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                वापस WIN_SetError("SetWindowLong()");
            }
        }

        अगर (SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            वापस WIN_SetError("SetLayeredWindowAttributes()");
        }
    }

    वापस true;
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

अटल स्थिर अक्षर *SDLGetClipboardFormatName(UINT cf, अक्षर *text, पूर्णांक len)
{
    चयन (cf) {
    हाल CF_TEXT:
        वापस "CF_TEXT";
    हाल CF_BITMAP:
        वापस "CF_BITMAP";
    हाल CF_METAFILEPICT:
        वापस "CF_METAFILEPICT";
    हाल CF_SYLK:
        वापस "CF_SYLK";
    हाल CF_DIF:
        वापस "CF_DIF";
    हाल CF_TIFF:
        वापस "CF_TIFF";
    हाल CF_OEMTEXT:
        वापस "CF_OEMTEXT";
    हाल CF_DIB:
        वापस "CF_DIB";
    हाल CF_PALETTE:
        वापस "CF_PALETTE";
    हाल CF_PENDATA:
        वापस "CF_PENDATA";
    हाल CF_RIFF:
        वापस "CF_RIFF";
    हाल CF_WAVE:
        वापस "CF_WAVE";
    हाल CF_UNICODETEXT:
        वापस "CF_UNICODETEXT";
    हाल CF_ENHMETAFILE:
        वापस "CF_ENHMETAFILE";
    हाल CF_HDROP:
        वापस "CF_HDROP";
    हाल CF_LOCALE:
        वापस "CF_LOCALE";
    हाल CF_DIBV5:
        वापस "CF_DIBV5";
    हाल CF_OWNERDISPLAY:
        वापस "CF_OWNERDISPLAY";
    हाल CF_DSPTEXT:
        वापस "CF_DSPTEXT";
    हाल CF_DSPBITMAP:
        वापस "CF_DSPBITMAP";
    हाल CF_DSPMETAFILEPICT:
        वापस "CF_DSPMETAFILEPICT";
    हाल CF_DSPENHMETAFILE:
        वापस "CF_DSPENHMETAFILE";
    शेष:
        अगर (GetClipboardFormatNameA(cf, text, len)) {
            वापस text;
        } अन्यथा {
            वापस शून्य;
        }
    }
}

अटल STDMETHODIMP_(ULONG) SDLDropTarget_AddRef(SDLDropTarget *target)
{
    वापस ++target->refcount;
}

अटल STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    अगर (target->refcount == 0) {
        SDL_free(target);
        वापस 0;
    }
    वापस target->refcount;
}

अटल STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    अगर (ppv == शून्य) {
        वापस E_INVALIDARG;
    }

    *ppv = शून्य;
    अगर (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (व्योम *)target;
    }
    अगर (*ppv) {
        SDLDropTarget_AddRef(target);
        वापस S_OK;
    }
    वापस E_NOINTERFACE;
}

अटल STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *p_तथ्य_Object, DWORD grf_कुंजी_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    अगर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    वापस S_OK;
}

अटल STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_कुंजी_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    अगर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    वापस S_OK;
}

अटल STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In DragLeave");
    SDL_SendDropComplete(target->window);
    वापस S_OK;
}

अटल STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *p_तथ्य_Object, DWORD grf_कुंजी_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    अगर (ScreenToClient(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->window->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->window, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_तथ्य_Object->lpVtbl->EnumFormatEtc(p_तथ्य_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        अगर (hres == S_OK) {
            FORMATETC fetc;
            जबतक (pEnumFormatEtc->lpVtbl->अग्र_3(pEnumFormatEtc, 1, &fetc, शून्य) == S_OK) {
                अक्षर name[257] = { 0 };
                स्थिर अक्षर *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                अगर (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } अन्यथा {
                    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_file;
        fetc.ptd = शून्य;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिर अक्षर *format_mime = "text/uri-list";
        अगर (SUCCEEDED(p_तथ्य_Object->lpVtbl->Query_Get_तथ्य(p_तथ्य_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_तथ्य_Object->lpVtbl->Get_तथ्य(p_तथ्य_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            अगर (SUCCEEDED(hres)) {
                स्थिर माप_प्रकार bsize = Global_आकार(med.hGlobal);
                स्थिर व्योम *बफर_2 = (व्योम *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, बफर_2);
                अगर (बफर_2) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + माप(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, माप(Uint32));
                    अक्षर *saveptr = शून्य;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    जबतक (token != शून्य) {
                        अगर (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                            SDL_SendDropFile(target->window, शून्य, token);
                        }
                        token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                वापस S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = target->format_text;
        fetc.ptd = शून्य;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिर अक्षर *format_mime = "text/plain;charset=utf-8";
        अगर (SUCCEEDED(p_तथ्य_Object->lpVtbl->Query_Get_तथ्य(p_तथ्य_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_तथ्य_Object->lpVtbl->Get_तथ्य(p_तथ्य_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            अगर (SUCCEEDED(hres)) {
                स्थिर माप_प्रकार bsize = Global_आकार(med.hGlobal);
                स्थिर व्योम *बफर_2 = (व्योम *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, बफर_2);
                अगर (बफर_2) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + माप(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, माप(Uint32));
                    अक्षर *saveptr = शून्य;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    जबतक (token != शून्य) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                        SDL_SendDropText(target->window, (अक्षर *)token);
                        token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                वापस S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = शून्य;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिर अक्षर *format_mime = "CF_UNICODETEXT";
        अगर (SUCCEEDED(p_तथ्य_Object->lpVtbl->Query_Get_तथ्य(p_तथ्य_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_तथ्य_Object->lpVtbl->Get_तथ्य(p_तथ्य_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            अगर (SUCCEEDED(hres)) {
                स्थिर माप_प्रकार bsize = Global_आकार(med.hGlobal);
                स्थिर व्योम *बफर_2 = (व्योम *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, बफर_2);
                अगर (बफर_2) {
                    बफर_2 = WIN_StringToUTF8W((स्थिर ब_अक्षर_प्रकार *)बफर_2);
                    अगर (बफर_2) {
                        स्थिर माप_प्रकार lbuffer = SDL_strlen((स्थिर अक्षर *)बफर_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)lbuffer, बफर_2);
                        अक्षर *text = (अक्षर *)SDL_malloc(lbuffer + माप(Uint32));
                        SDL_memcpy((Uint8 *)text, बफर_2, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, माप(Uint32));
                        अक्षर *saveptr = शून्य;
                        अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        जबतक (token != शून्य) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)lbuffer, token);
                            SDL_SendDropText(target->window, (अक्षर *)token);
                            token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((व्योम *)बफर_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                वापस S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_TEXT;
        fetc.ptd = शून्य;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिर अक्षर *format_mime = "CF_TEXT";
        अगर (SUCCEEDED(p_तथ्य_Object->lpVtbl->Query_Get_तथ्य(p_तथ्य_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_तथ्य_Object->lpVtbl->Get_तथ्य(p_तथ्य_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            अगर (SUCCEEDED(hres)) {
                स्थिर माप_प्रकार bsize = Global_आकार(med.hGlobal);
                स्थिर व्योम *बफर_2 = (व्योम *)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, बफर_2);
                अगर (बफर_2) {
                    अक्षर *text = (अक्षर *)SDL_malloc(bsize + माप(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, माप(Uint32));
                    अक्षर *saveptr = शून्य;
                    अक्षर *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    जबतक (token != शून्य) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिन्हित दीर्घ)SDL_strlen(token), (अचिन्हित दीर्घ)bsize, token);
                        SDL_SendDropText(target->window, (अक्षर *)token);
                        token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                वापस S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = शून्य;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        स्थिर अक्षर *format_mime = "CF_HDROP";
        अगर (SUCCEEDED(p_तथ्य_Object->lpVtbl->Query_Get_तथ्य(p_तथ्य_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_तथ्य_Object->lpVtbl->Get_तथ्य(p_तथ्य_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            अगर (SUCCEEDED(hres)) {
                स्थिर माप_प्रकार bsize = Global_आकार(med.hGlobal);
                HDROP drop = (HDROP)GlobalLock(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिन्हित दीर्घ)bsize, drop);
                UINT गिनती = DragQueryFile(drop, 0xFFFFFFFF, शून्य, 0);
                क्रम (UINT i = 0; i < गिनती; ++i) {
                    UINT आकार = DragQueryFile(drop, i, शून्य, 0) + 1;
                    LPTSTR बफर_2 = (LPTSTR)SDL_malloc(आकार * माप(TCHAR));
                    अगर (बफर_2) {
                        अगर (DragQueryFile(drop, i, बफर_2, आकार)) {
                            अक्षर *file = WIN_StringToUTF8(बफर_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिन्हित दीर्घ)SDL_strlen(file), (अचिन्हित दीर्घ)bsize, file);
                            SDL_SendDropFile(target->window, शून्य, file);
                            SDL_free(file);
                        }
                        SDL_free(बफर_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->window);
                वापस S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->window);
    वापस S_OK;
}

अटल व्योम *vtDropTarget[] = {
    (व्योम *)(SDLDropTarget_QueryInterface),
    (व्योम *)(SDLDropTarget_AddRef),
    (व्योम *)(SDLDropTarget_Release),
    (व्योम *)(SDLDropTarget_DragEnter),
    (व्योम *)(SDLDropTarget_DragOver),
    (व्योम *)(SDLDropTarget_DragLeave),
    (व्योम *)(SDLDropTarget_Drop)
};

व्योम WIN_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    अगर (तथ्य->videodata->oleinitialized) {
        अगर (accept && !तथ्य->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, माप(SDLDropTarget));
            अगर (drop_target != शून्य) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->window = window;
                drop_target->hwnd = तथ्य->hwnd;
                drop_target->format_file = RegisterClipboardFormatW(L"text/uri-list");
                drop_target->format_text = RegisterClipboardFormatW(L"text/plain;charset=utf-8");
                तथ्य->drop_target = drop_target;
                SDLDropTarget_AddRef(drop_target);
                RegisterDragDrop(तथ्य->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             window->id);
            }
        } अन्यथा अगर (!accept && तथ्य->drop_target) {
            RevokeDragDrop(तथ्य->hwnd);
            SDLDropTarget_Release(तथ्य->drop_target);
            तथ्य->drop_target = शून्य;
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         window->id);
        }
    } अन्यथा {
        DragAcceptFiles(तथ्य->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     window->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_आकार = माप(desc);
    desc.hwnd = window->internal->hwnd;
    चयन (operation) {
    हाल SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        अवरोध;
    हाल SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_गिनती = 1;
        अवरोध;
    हाल SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        अवरोध;
    शेष:
        वापस SDL_Unsupported();
    }

    FlashWindowEx(&desc);

    वापस true;
}

bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Window_तथ्य *तथ्य = window->internal;
    अगर (!तथ्य->taskbar_button_created) {
        वापस true;
    }

    अगर (window->progress_state == SDL_PROGRESS_STATE_NONE && !तथ्य->videodata->taskbar_list) {
        वापस true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(window);
    अगर (!taskbar_list) {
        वापस false;
    }

    TBPFLAG tbpFlags;
    चयन (window->progress_state) {
    हाल SDL_PROGRESS_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        अवरोध;
    हाल SDL_PROGRESS_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        अवरोध;
    हाल SDL_PROGRESS_STATE_NORMAL:
        tbpFlags = TBPF_NORMAL;
        अवरोध;
    हाल SDL_PROGRESS_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        अवरोध;
    हाल SDL_PROGRESS_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        अवरोध;
    शेष:
        वापस SDL_SetError("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->SetProgressState(taskbar_list, तथ्य->hwnd, tbpFlags);
    अगर (FAILED(ret)) {
        वापस WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    अगर (window->progress_state >= SDL_PROGRESS_STATE_NORMAL) {
        ret = taskbar_list->lpVtbl->Set_Progress_मूल्य(taskbar_list, तथ्य->hwnd, (ULONGLONG)(window->progress_मूल्य * 10000.f), 10000);
        अगर (FAILED(ret)) {
            वापस WIN_SetErrorFromHRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#पूर्ण_अगर
    वापस true;
}

व्योम WIN_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    स्थिर SDL_Window_तथ्य *तथ्य = window->internal;
    POINT pt;

    pt.x = x;
    pt.y = y;
    ClientToScreen(तथ्य->hwnd, &pt);
    SendMessage(तथ्य->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    अगर (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window_तथ्य *तथ्य = window->internal;
        HWND hwnd = तथ्य->hwnd;
        स्थिर LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        अगर (focusable) {
            अगर (style & WS_EX_NOACTIVATE) {
                अगर (SetWindowLong(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    वापस WIN_SetError("SetWindowLong()");
                }
            }
        } अन्यथा {
            अगर (!(style & WS_EX_NOACTIVATE)) {
                अगर (SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    वापस WIN_SetError("SetWindowLong()");
                }
            }
        }
    } अन्यथा अगर (window->flags & SDL_WINDOW_POPUP_MENU) {
        अगर (!(window->flags & SDL_WINDOW_HIDDEN)) {
            अगर (!focusable && (window->flags & SDL_WINDOW_निवेश_FOCUS)) {
                SDL_Window *new_focus;
                स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                WIN_SetKeyboardFocus(new_focus, set_focus);
            } अन्यथा अगर (focusable) {
                अगर (SDL_ShouldFocusPopup(window)) {
                    WIN_SetKeyboardFocus(window, true);
                }
            }
        }

        वापस true;
    }

    वापस true;
}
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Window_तथ्य *child_तथ्य = window->internal;
    स्थिर LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->internal->hwnd : शून्य);
    स्थिर DWORD style = GetWindowLong(child_तथ्य->hwnd, GWL_STYLE);

    अगर (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        SetWindowLongPtr(child_तथ्य->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } अन्यथा {
        SetParent(child_तथ्य->hwnd, (HWND)parent_hwnd);
    }
#पूर्ण_अगर /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    वापस true;
}

bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    स्थिर HWND parent_hwnd = window->parent->internal->hwnd;

    अगर (modal) {
        // Disable the parent window.
        EnableWindow(parent_hwnd, FALSE);
    } अन्यथा अगर (!(window->flags & SDL_WINDOW_HIDDEN)) {
        // Re-enable the parent window
        EnableWindow(parent_hwnd, TRUE);
    }
#पूर्ण_अगर // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS
