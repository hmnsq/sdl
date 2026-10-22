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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS

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
#د_که_پای

// Windows CE compatibility
#که_نه_تعریف_شوی SWP_NOCOPYBITS
#تعریف_کړه SWP_NOCOPYBITS 0
#د_که_پای

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#که_نه_تعریف_شوی WM_POPUPSYSTEMMENU
#تعریف_کړه WM_POPUPSYSTEMMENU 0x313
#د_که_پای

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

#تعریف_کړه STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#تعریف_کړه STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کړه STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کړه STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کړه STYLE_نورمال              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کړه STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#تعریف_کړه STYLE_ماسک                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_نورمال | STYLE_RESIZABLE)

ساكن DWORD Get_کړکۍ_Style(SDL_کړکۍ *کړکۍ)
{
    DWORD style = 0;

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        style |= WS_POPUP;
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وإلا {
        إذا (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
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
            style |= STYLE_نورمال;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        إذا (کړکۍ->flags & SDL_کړکۍ_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            إذا (!(کړکۍ->flags & SDL_کړکۍ_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        إذا (کړکۍ->دننی && کړکۍ->دننی->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    أرجع style;
}

ساكن DWORD Get_کړکۍ_Style_Ex(SDL_کړکۍ *کړکۍ)
{
    DWORD style = 0;

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ) || (کړکۍ->flags & SDL_کړکۍ_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ) || (کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    أرجع style;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن ITaskbarList3 *GetTaskbarList(SDL_کړکۍ *کړکۍ)
{
    ثابت SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_assert(معلومات->taskbar_button_created);
    إذا (!معلومات->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, عدم, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&معلومات->videodata->taskbar_list);
        إذا (FAILED(ret)) {
            WIN_سېټ_Error_From_HRESULT("Unable to create taskbar list", ret);
            أرجع عدم;
        }
        ITaskbarList3 *taskbarlist = معلومات->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        إذا (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            معلومات->videodata->taskbar_list = عدم;
            WIN_سېټ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            أرجع عدم;
        }
    }
    أرجع معلومات->videodata->taskbar_list;
}
#د_که_پای

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساكن bool WIN_Adjust_کړکۍ_Rect_With_Style(SDL_کړکۍ *کړکۍ, DWORD style, DWORD styleEx, BOOL menu, صحيح *x, صحيح *y, صحيح *پلنوالی, صحيح *لوړوالی, SDL_کړکۍ_Rect rect_type)
{
    SDL_Video_معلومات *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->دننی : عدم;
    RECT rect;

    // Client rect, in points
    بدل (rect_type) {
    حالة SDL_WINDOWRECT_CURRENT:
        SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->x, کړکۍ->y, x, y);
        *پلنوالی = کړکۍ->w;
        *لوړوالی = کړکۍ->h;
        اكسر;
    حالة SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->windowed.x, کړکۍ->windowed.y, x, y);
        *پلنوالی = کړکۍ->windowed.w;
        *لوړوالی = کړکۍ->windowed.h;
        اكسر;
    حالة SDL_WINDOWRECT_FLOATING:
        SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->floating.x, کړکۍ->floating.y, x, y);
        *پلنوالی = کړکۍ->floating.w;
        *لوړوالی = کړکۍ->floating.h;
        اكسر;
    حالة SDL_WINDOWRECT_PENDING:
        SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->pending.x, کړکۍ->pending.y, x, y);
        *پلنوالی = کړکۍ->pending.w;
        *لوړوالی = کړکۍ->pending.h;
        اكسر;
    افتراضي:
        // Should never be here
        SDL_assert_release(false);
        *پلنوالی = 0;
        *لوړوالی = 0;
        اكسر;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.کیڼ = 0;
    rect.سر = 0;
    rect.ښی = *پلنوالی;
    rect.bottom = *لوړوالی;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    إذا (!(کړکۍ->flags & SDL_کړکۍ_BORDERLESS) && !SDL_کړکۍ_IS_POPUP(کړکۍ)) {
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_کړکۍ_Rect_Ex(&rect, style, menu, 0);
#وإلا
        إذا (WIN_Is_فی_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            إذا (videodata) {
                UINT چوکاټ_dpi;
                SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
                چوکاټ_dpi = (معلومات && videodata->Get_Dpi_For_کړکۍ) ? videodata->Get_Dpi_For_کړکۍ(معلومات->hwnd) : USER_DEFAULT_SCREEN_DPI;
                إذا (videodata->Adjust_کړکۍ_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, چوکاټ_dpi) == 0) {
                    أرجع WIN_سېټ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } وإلا {
            إذا (Adjust_کړکۍ_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                أرجع WIN_سېټ_Error("AdjustWindowRectEx()");
            }
        }
#د_که_پای
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.کیڼ;
    *y += rect.سر;
    *پلنوالی = (rect.ښی - rect.کیڼ);
    *لوړوالی = (rect.bottom - rect.سر);

#که_تعریف_شوی HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? کړکۍ->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? کړکۍ->windowed.x : کړکۍ->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کړکۍ->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? کړکۍ->windowed.y : کړکۍ->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کړکۍ->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? کړکۍ->windowed.w : کړکۍ->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کړکۍ->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? کړکۍ->windowed.h : کړکۍ->h),
            *x, *y, *پلنوالی, *لوړوالی, چوکاټ_dpi);
#د_که_پای
    أرجع true;
}

bool WIN_Adjust_کړکۍ_Rect(SDL_کړکۍ *کړکۍ, صحيح *x, صحيح *y, صحيح *پلنوالی, صحيح *لوړوالی, SDL_کړکۍ_Rect rect_type)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
    styleEx = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#د_که_پای
    أرجع WIN_Adjust_کړکۍ_Rect_With_Style(کړکۍ, style, styleEx, menu, x, y, پلنوالی, لوړوالی, rect_type);
}

bool WIN_Adjust_کړکۍ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکاټ_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_معلومات *videodata = videodevice ? videodevice->دننی : عدم;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
    styleEx = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#د_که_پای

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_کړکۍ_Rect_Ex(lpRect, style, menu, styleEx);
#وإلا
    إذا (WIN_Is_فی_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        إذا (!چوکاټ_dpi) {
            چوکاټ_dpi = videodata->Get_Dpi_For_کړکۍ ? videodata->Get_Dpi_For_کړکۍ(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        إذا (!videodata->Adjust_کړکۍ_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, چوکاټ_dpi)) {
            أرجع WIN_سېټ_Error("AdjustWindowRectExForDpi()");
        }
    } وإلا {
        إذا (!Adjust_کړکۍ_Rect_Ex(lpRect, style, menu, styleEx)) {
            أرجع WIN_سېټ_Error("AdjustWindowRectEx()");
        }
    }
#د_که_پای
    أرجع true;
}

bool WIN_سېټ_کړکۍ_Position_دننی(SDL_کړکۍ *کړکۍ, UINT flags, SDL_کړکۍ_Rect rect_type)
{
    SDL_کړکۍ *ماشوم_کړکۍ;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    HWND سر;
    صحيح x, y;
    صحيح w, h;
    bool پایله = true;

    // Figure out what the window area will be
    إذا (SDL_ShouldAllowTopmost() && (کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر)) {
        سر = HWND_TOPMOST;
    } وإلا {
        سر = HWND_NOTOPMOST;
    }

    WIN_Adjust_کړکۍ_Rect(کړکۍ, &x, &y, &w, &h, rect_type);

    معلومات->expected_resize = !(flags & SWP_NOSIZE);
    إذا (سېټ_کړکۍ_Pos(hwnd, سر, x, y, w, h, flags) == 0) {
        پایله = WIN_سېټ_Error("SetWindowPos()");
    }
    معلومات->expected_resize = false;

    // Update any child windows
    لكل (ماشوم_کړکۍ = کړکۍ->لومړی_ماشوم; ماشوم_کړکۍ; ماشوم_کړکۍ = ماشوم_کړکۍ->بل_sibling) {
        إذا (!ماشوم_کړکۍ->دننی) {
            // This child window is not yet fully initialized.
            استمر;
        }
        إذا (!WIN_سېټ_کړکۍ_Position_دننی(ماشوم_کړکۍ, flags, SDL_WINDOWRECT_CURRENT)) {
            پایله = false;
        }
    }
    أرجع پایله;
}

ساكن SDL_کړکۍ_Erase_Background_ډېرپېښ Get_Erase_Background_ډېرپېښ_Hint(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_ډېرپېښ);
    إذا (!hint)
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "never"))
        أرجع SDL_ERASEBACKGROUNDMODE_NEVER;

    إذا (SDL_strstr(hint, "initial"))
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "always"))
        أرجع SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحيح ډېرپېښ = SDL_GetStringInteger(hint, 1);
    إذا (ډېرپېښ < 0 || ډېرپېښ > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    أرجع (SDL_کړکۍ_Erase_Background_ډېرپېښ)ډېرپېښ;
}

ساكن bool تیاری_کړکۍ_معلومات(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, HWND hwnd, HWND پلار)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_کړکۍ_معلومات *معلومات;

    // Allocate the window data
    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }
    معلومات->کړکۍ = کړکۍ;
    معلومات->hwnd = hwnd;
    معلومات->پلار = پلار;
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->hdc = (HDC)معلومات->hwnd;
#وإلا
    معلومات->hdc = GetDC(hwnd);
#د_که_پای
    معلومات->hinstance = (HINSTANCE)Get_کړکۍ_Long_Ptr(hwnd, GWLP_HINSTANCE);
    معلومات->mouse_button_flags = (WPARAM)-1;
    معلومات->وروستی_اشاره_ګر_update = (LPARAM)-1;
    معلومات->videodata = videodata;
    معلومات->initializing = true;
    معلومات->hint_erase_background_ډېرپېښ = Get_Erase_Background_ډېرپېښ_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    معلومات->cursor_ctrlock_rect.کیڼ   = 0 - remote_desktop_adjustment;
    معلومات->cursor_ctrlock_rect.سر    = 0;
    معلومات->cursor_ctrlock_rect.ښی  = 1 + remote_desktop_adjustment;
    معلومات->cursor_ctrlock_rect.bottom = 1;
#د_که_پای

    إذا (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        معلومات->copybits_flag = 0;
    } وإلا {
        معلومات->copybits_flag = SWP_NOCOPYBITS;
    }

#که_تعریف_شوی HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", معلومات->scaling_dpi);
#د_که_پای

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    إذا (!سېټ_Prop(hwnd, متن_2("SDL_WindowData"), معلومات)) {
        ReleaseDC(hwnd, معلومات->hdc);
        SDL_free(معلومات);
        أرجع WIN_سېټ_Error("SetProp() failed");
    }
#د_که_پای

    کړکۍ->دننی = معلومات;

    // Set up the window proc function
    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
#که_تعریف_شوی GWLP_WNDPROC
        معلومات->wndproc = (WNDPROC)Get_کړکۍ_Long_Ptr(hwnd, GWLP_WNDPROC);
        إذا (معلومات->wndproc != WIN_کړکۍ_Proc) {
            سېټ_کړکۍ_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_کړکۍ_Proc);
        }
#وإلا
        معلومات->wndproc = (WNDPROC)Get_کړکۍ_Long(hwnd, GWL_WNDPROC);
        إذا (معلومات->wndproc != WIN_کړکۍ_Proc) {
            سېټ_کړکۍ_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_کړکۍ_Proc);
        }
#د_که_پای
    } وإلا {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
        إذا (style & WS_VISIBLE) {
            کړکۍ->flags &= ~SDL_کړکۍ_HIDDEN;
        } وإلا {
            کړکۍ->flags |= SDL_کړکۍ_HIDDEN;
        }
        إذا (style & WS_POPUP) {
            کړکۍ->flags |= SDL_کړکۍ_BORDERLESS;
        } وإلا {
            کړکۍ->flags &= ~SDL_کړکۍ_BORDERLESS;
        }
        إذا (style & WS_THICKFRAME) {
            کړکۍ->flags |= SDL_کړکۍ_RESIZABLE;
        } وإلا إذا (!(style & WS_POPUP)) {
            کړکۍ->flags &= ~SDL_کړکۍ_RESIZABLE;
        }
#که_تعریف_شوی WS_MAXIMIZE
        إذا (style & WS_MAXIMIZE) {
            کړکۍ->flags |= SDL_کړکۍ_MAXIMIZED;
        } وإلا
#د_که_پای
        {
            کړکۍ->flags &= ~SDL_کړکۍ_MAXIMIZED;
        }
#که_تعریف_شوی WS_MINIMIZE
        إذا (style & WS_MINIMIZE) {
            کړکۍ->flags |= SDL_کړکۍ_MINIMIZED;
        } وإلا
#د_که_پای
        {
            کړکۍ->flags &= ~SDL_کړکۍ_MINIMIZED;
        }
    }
    إذا (!(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        RECT rect;
        إذا (GetClientRect(hwnd, &rect) && WIN_کړکۍ_Rect_Valid(&rect)) {
            صحيح w = rect.ښی;
            صحيح h = rect.bottom;

            إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
                کړکۍ->floating.w = کړکۍ->windowed.w = کړکۍ->w = w;
                کړکۍ->floating.h = کړکۍ->windowed.h = کړکۍ->h = h;
            } وإلا إذا ((کړکۍ->windowed.w && کړکۍ->windowed.w != w) || (کړکۍ->windowed.h && کړکۍ->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحيح x, y;
                // Figure out what the window area will be
                WIN_Adjust_کړکۍ_Rect(کړکۍ, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                معلومات->expected_resize = true;
                سېټ_کړکۍ_Pos(hwnd, عدم, x, y, w, h, معلومات->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                معلومات->expected_resize = false;
            } وإلا {
                کړکۍ->w = w;
                کړکۍ->h = h;
            }
        }
    }
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        ټکی_2 ټکی;
        ټکی.x = 0;
        ټکی.y = 0;
        إذا (Client_منزل_Screen(hwnd, &ټکی)) {
            إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
                کړکۍ->floating.x = کړکۍ->windowed.x = ټکی.x;
                کړکۍ->floating.y = کړکۍ->windowed.y = ټکی.y;
            }
            کړکۍ->x = ټکی.x;
            کړکۍ->y = ټکی.y;
        }
    }

    WIN_Update_کړکۍ_ICCProfile(کړکۍ, false);
#د_که_پای

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    کړکۍ->flags |= SDL_کړکۍ_ننوت_FOCUS;
    SDL_سېټ_Keyboard_Focus(کړکۍ);
#وإلا
    إذا (GetFocus() == hwnd) {
        کړکۍ->flags |= SDL_کړکۍ_ننوت_FOCUS;
        SDL_سېټ_Keyboard_Focus(کړکۍ);
        WIN_UpdateClipCursor(کړکۍ);
    }
#د_که_پای

    إذا (کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر) {
        WIN_سېټ_کړکۍ_Always_On_سر(_this, کړکۍ, true);
    } وإلا {
        WIN_سېټ_کړکۍ_Always_On_سر(_this, کړکۍ, false);
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    إذا (videodata->ثبتوونکی_Touch_کړکۍ) {
        videodata->ثبتوونکی_Touch_کړکۍ(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#د_که_پای

    إذا (معلومات->پلار && !کړکۍ->پلار) {
        معلومات->destroy_پلار_with_کړکۍ = true;
    }

    معلومات->initializing = false;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحيح titleLen;
        bool isstack;

        titleLen = Get_کړکۍ_متن_اوږدتیا(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        إذا (title) {
            titleLen = Get_کړکۍ_متن(hwnd, title, titleLen + 1);
        } وإلا {
            titleLen = 0;
        }
        إذا (titleLen > 0) {
            کړکۍ->title = WIN_String_منزل_UTF8(title);
        }
        إذا (title) {
            SDL_small_free(title, isstack);
        }
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WIN32_HWND_اشاره_ګر, معلومات->hwnd);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WIN32_HDC_اشاره_ګر, معلومات->hdc);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WIN32_INSTANCE_اشاره_ګر, معلومات->hinstance);

    // All done!
    أرجع true;
}

ساكن فراغ Cleanup_کړکۍ_معلومات(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (معلومات->drop_موخه) {
            WIN_AcceptDragAndDrop(کړکۍ, false);
        }
        SDL_free(معلومات->ICMFileName);
        إذا (معلومات->keyboard_hook) {
            UnhookWindowsHookEx(معلومات->keyboard_hook);
        }
        إذا (معلومات->hicon) {
            DestroyIcon(معلومات->hicon);
        }
        ReleaseDC(معلومات->hwnd, معلومات->hdc);
        RemoveProp(معلومات->hwnd, متن_2("SDL_WindowData"));
#د_که_پای
        إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
            Destroy_کړکۍ(معلومات->hwnd);
            إذا (معلومات->destroy_پلار_with_کړکۍ && معلومات->پلار) {
                Destroy_کړکۍ(معلومات->پلار);
            }
        } وإلا {
            // Restore any original event handler...
            إذا (معلومات->wndproc) {
#که_تعریف_شوی GWLP_WNDPROC
                سېټ_کړکۍ_Long_Ptr(معلومات->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)معلومات->wndproc);
#وإلا
                سېټ_کړکۍ_Long(معلومات->hwnd, GWL_WNDPROC,
                              (LONG_PTR)معلومات->wndproc);
#د_که_پای
            }
        }
        SDL_free(معلومات);
    }
    کړکۍ->دننی = عدم;
}

ساكن فراغ WIN_ConstrainPopup(SDL_کړکۍ *کړکۍ, bool output_منزل_pending)
{
    // Possibly clamp popup windows to the output borders
    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        SDL_کړکۍ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = کړکۍ->وروستی_position_pending ? کړکۍ->pending.x : کړکۍ->floating.x;
        صحيح abs_y = کړکۍ->وروستی_position_pending ? کړکۍ->pending.y : کړکۍ->floating.y;
        ثابت صحيح پلنوالی = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->floating.w;
        ثابت صحيح لوړوالی = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->floating.h;
        صحيح دننه_واټن_x = 0, دننه_واټن_y = 0;

        إذا (کړکۍ->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = کړکۍ->پلار; SDL_کړکۍ_IS_POPUP(w); w = w->پلار) {
                دننه_واټن_x += w->x;
                دننه_واټن_y += w->y;
            }

            دننه_واټن_x += w->x;
            دننه_واټن_y += w->y;
            abs_x += دننه_واټن_x;
            abs_y += دننه_واټن_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_کړکۍ(w);
            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + پلنوالی > rect.x + rect.w) {
                abs_x -= (abs_x + پلنوالی) - (rect.x + rect.w);
            }
            إذا (abs_y + لوړوالی > rect.y + rect.h) {
                abs_y -= (abs_y + لوړوالی) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            کړکۍ->pending.x = abs_x - دننه_واټن_x;
            کړکۍ->pending.y = abs_y - دننه_واټن_y;
            کړکۍ->pending.w = پلنوالی;
            کړکۍ->pending.h = لوړوالی;
        } وإلا {
            کړکۍ->floating.x = abs_x - دننه_واټن_x;
            کړکۍ->floating.y = abs_y - دننه_واټن_y;
            کړکۍ->floating.w = پلنوالی;
            کړکۍ->floating.h = لوړوالی;
        }
    }
}

ساكن فراغ WIN_سېټ_Keyboard_Focus(SDL_کړکۍ *کړکۍ, bool سېټ_فعال_focus)
{
    SDL_کړکۍ *toplevel = کړکۍ;

    // Find the topmost parent
    طالما (SDL_کړکۍ_IS_POPUP(toplevel)) {
        toplevel = toplevel->پلار;
    }

    toplevel->keyboard_focus = کړکۍ;

    إذا (سېټ_فعال_focus && !کړکۍ->is_hiding && !کړکۍ->is_destroying) {
        SDL_سېټ_Keyboard_Focus(کړکۍ);
    }
}

bool WIN_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    HWND hwnd = (HWND)SDL_Get_اشاره_ګر_Property(create_props, SDL_PROP_کړکۍ_CREATE_WIN32_HWND_اشاره_ګر, SDL_Get_اشاره_ګر_Property(create_props, "sdl2-compat.external_window", عدم));
    HWND پلار = عدم;
    إذا (hwnd) {
        کړکۍ->flags |= SDL_کړکۍ_EXTERNAL;

        إذا (!تیاری_کړکۍ_معلومات(_this, کړکۍ, hwnd, پلار)) {
            أرجع false;
        }
    } وإلا {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحيح x, y;
        صحيح w, h;

        إذا (کړکۍ->flags & SDL_کړکۍ_UTILITY) {
            پلار = Create_کړکۍ(SDL_Appname, متن_2(""), STYLE_BASIC, 0, 0, 32, 32, عدم, عدم, SDL_Instance, عدم);
        } وإلا إذا (کړکۍ->پلار) {
            پلار = کړکۍ->پلار->دننی->hwnd;
        }

        style |= Get_کړکۍ_Style(کړکۍ);
        styleEx |= (DWORD)SDL_Get_شمېره_Property(create_props, SDL_PROP_کړکۍ_CREATE_WIN32_STYLE_EX_شمېره, Get_کړکۍ_Style_Ex(کړکۍ));

        // Figure out what the window area will be
        WIN_ConstrainPopup(کړکۍ, false);
        WIN_Adjust_کړکۍ_Rect_With_Style(کړکۍ, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_کړکۍ_Ex(styleEx, SDL_Appname, متن_2(""), style,
                              x, y, w, h, پلار, عدم, SDL_Instance, عدم);
        إذا (!hwnd) {
            أرجع WIN_سېټ_Error("Couldn't create window");
        }

        WIN_Update_Dark_ډېرپېښ_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        إذا (!تیاری_کړکۍ_معلومات(_this, کړکۍ, hwnd, پلار)) {
            Destroy_کړکۍ(hwnd);
            إذا (پلار) {
                Destroy_کړکۍ(پلار);
            }
            أرجع false;
        }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_متن_ننوت(_this, کړکۍ);
#د_که_پای

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        سېټ_کړکۍ_Pos(hwnd, عدم, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            کړکۍ->flags &= ~SDL_کړکۍ_HIDDEN;
            Show_کړکۍ(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    إذا (کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) {
        إذا (videodata->Dwm_Enable_Blur_Behind_کړکۍ) {
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
            videodata->Dwm_Enable_Blur_Behind_کړکۍ(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_اشاره_ګر_Property(create_props, SDL_PROP_کړکۍ_CREATE_WIN32_PIXEL_FORMAT_HWND_اشاره_ګر, عدم);
    إذا (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحيح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        إذا (!سېټ_Pixel_Format(کړکۍ->دننی->hdc, pixel_format, &pfd)) {
            WIN_Destroy_کړکۍ(_this, کړکۍ);
            أرجع WIN_سېټ_Error("SetPixelFormat()");
        }
    } وإلا {
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (!(کړکۍ->flags & SDL_کړکۍ_OPENGL)) {
            أرجع true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#که_تعریف_شوی SDL_VIDEO_OPENGL_ES2
        إذا ((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_معلومات || WIN_GL_UseEGL(_this))
#د_که_پای // SDL_VIDEO_OPENGL_WGL
        ) {
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
            إذا (!WIN_GLES_تیاری_کړکۍ(_this, کړکۍ)) {
                WIN_Destroy_کړکۍ(_this, کړکۍ);
                أرجع false;
            }
            أرجع true;
#وإلا
            أرجع SDL_سېټ_Error("Could not create GLES window surface (EGL support not configured)");
#د_که_پای // SDL_VIDEO_OPENGL_EGL
        }
#د_که_پای // SDL_VIDEO_OPENGL_ES2

#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
        إذا (!WIN_GL_تیاری_کړکۍ(_this, کړکۍ)) {
            WIN_Destroy_کړکۍ(_this, کړکۍ);
            أرجع false;
        }
#وإلا
        أرجع SDL_سېټ_Error("Could not create GL window (WGL support not configured)");
#د_که_پای
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

فراغ WIN_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کړکۍ->دننی->hwnd;
    LPTSTR title = WIN_UTF8_منزل_String(کړکۍ->title);
    سېټ_کړکۍ_متن(hwnd, title);
    SDL_free(title);
#د_که_پای
}

bool WIN_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    HICON hicon = عدم;
    BYTE *icon_bmp;
    صحيح icon_len, ماسک_len, لیکه_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool پایله = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_وخت_ASSERT(WIN_سېټ_کړکۍ_Icon_کاروي_BITMAPINFOHEADER_منزل_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    ماسک_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + ماسک_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    إذا (!icon_bmp) {
        أرجع false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_اندازه = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->bi_پلنوالی = SDL_Swap32LE(icon->w);
    bmi->bi_لوړوالی = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_بټ_شمېر = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_اندازه_Image = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->bi_XPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_کارول_شوی = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[حجم(BITMAPINFOHEADER)];
    لیکه_len = icon->w * حجم(Uint32);
    y = icon->h;
    طالما (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, لیکه_len);
        dst += لیکه_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - ماسک_len, 0xFF, ماسک_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    إذا (!hicon) {
        أرجع SDL_سېټ_Error("SetWindowIcon() failed, error %08X", (بینښه صحيح)Get_وروستی_Error());
    }

    إذا (معلومات->hicon) {
        DestroyIcon(معلومات->hicon);
    }
    معلومات->hicon = hicon;

    // Set the icon for the window
    Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_پیغام(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    أرجع پایله;
#وإلا
    أرجع SDL_Unsupported();
#د_که_پای
}

bool WIN_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        إذا (!(کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED))) {
            WIN_ConstrainPopup(کړکۍ, true);
            أرجع WIN_سېټ_کړکۍ_Position_دننی(کړکۍ,
                                                 کړکۍ->دننی->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وإلا {
        أرجع SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_ENTER, true);
    }

    أرجع true;
}

فراغ WIN_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (!(کړکۍ->flags & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED))) {
        WIN_سېټ_کړکۍ_Position_دننی(کړکۍ, کړکۍ->دننی->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وإلا {
        // Can't resize the window
        کړکۍ->وروستی_اندازه_pending = false;
    }
}

bool WIN_Get_کړکۍ_Borders_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کړکۍ->دننی->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *سر = rcClient.سر;
    *کیڼ = rcClient.کیڼ;
    *bottom = rcClient.bottom;
    *ښی = rcClient.ښی;

    أرجع true;
#وإلا  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کړکۍ->دننی->hwnd;
    RECT rcClient, rc_کړکۍ;
    ټکی_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    إذا (!GetClientRect(hwnd, &rcClient)) {
        أرجع SDL_سېټ_Error("GetClientRect() failed, error %08X", (بینښه صحيح)Get_وروستی_Error());
    }

    إذا (!Get_کړکۍ_Rect(hwnd, &rc_کړکۍ)) {
        أرجع SDL_سېټ_Error("GetWindowRect() failed, error %08X", (بینښه صحيح)Get_وروستی_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_کړکۍ.سر;
    ptDiff.x = rc_کړکۍ.کیڼ;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سېټ_Error("ScreenToClient() failed, error %08X", (بینښه صحيح)Get_وروستی_Error());
    }

    rc_کړکۍ.سر = ptDiff.y;
    rc_کړکۍ.کیڼ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_کړکۍ.bottom;
    ptDiff.x = rc_کړکۍ.ښی;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سېټ_Error("ScreenToClient() failed, error %08X", (بینښه صحيح)Get_وروستی_Error());
    }

    rc_کړکۍ.bottom = ptDiff.y;
    rc_کړکۍ.ښی = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *سر = rcClient.سر - rc_کړکۍ.سر;
    *کیڼ = rcClient.کیڼ - rc_کړکۍ.کیڼ;
    *bottom = rc_کړکۍ.bottom - rcClient.bottom;
    *ښی = rc_کړکۍ.ښی - rcClient.ښی;

    أرجع true;
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    ثابت SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    RECT rect;

    إذا (GetClientRect(hwnd, &rect) && WIN_کړکۍ_Rect_Valid(&rect)) {
        *w = rect.ښی;
        *h = rect.bottom;
    } وإلا إذا (کړکۍ->وروستی_pixel_w && کړکۍ->وروستی_pixel_h) {
        *w = کړکۍ->وروستی_pixel_w;
        *h = کړکۍ->وروستی_pixel_h;
    } وإلا {
        // Probably created minimized, use the restored size
        *w = کړکۍ->floating.w;
        *h = کړکۍ->floating.h;
    }
}

فراغ WIN_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کړکۍ_ACTIVATE_WHEN_SHOWN, true);

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        // Update our position in case our parent moved while we were hidden
        WIN_سېټ_کړکۍ_Position(_this, کړکۍ);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    إذا (کړکۍ->pending_flags & SDL_کړکۍ_FULLSCREEN) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_BORDERLESS)) {
            کړکۍ->flags |= SDL_کړکۍ_BORDERLESS;
            style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_ماسک;
            style |= Get_کړکۍ_Style(کړکۍ);
            سېټ_کړکۍ_Long(hwnd, GWL_STYLE, style);
            کړکۍ->flags &= ~SDL_کړکۍ_BORDERLESS;
        }
    }
    style = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);
    إذا (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    معلومات->showing_کړکۍ = true;
    إذا (bActivate) {
        Show_کړکۍ(hwnd, SW_SHOW);
    } وإلا {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        سېټ_کړکۍ_Pos(hwnd, عدم, 0, 0, 0, 0, کړکۍ->دننی->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    معلومات->showing_کړکۍ = false;

    إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE) && bActivate) {
        WIN_سېټ_Keyboard_Focus(کړکۍ, true);
    }
    إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        WIN_سېټ_کړکۍ_Modal(_this, کړکۍ, true);
    }
}

فراغ WIN_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    HWND hwnd = کړکۍ->دننی->hwnd;

    إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        WIN_سېټ_کړکۍ_Modal(_this, کړکۍ, false);
    }

    Show_کړکۍ(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
        SDL_کړکۍ *new_focus;
        ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(کړکۍ, &new_focus);
        WIN_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
    }
}

فراغ WIN_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
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
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کړکۍ_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = عدم;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    إذا (bForce) {
        hCurWnd = Get_Foreground_کړکۍ();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_کړکۍ_Thread_Process_Id(hCurWnd, عدم);
        Show_کړکۍ(hwnd, SW_RESTORE);
        Attach_Thread_ننوت(dwCurID, dwMyID, TRUE);
        سېټ_کړکۍ_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        إذا (!SDL_ShouldAllowTopmost() || !(کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر)) {
            سېټ_کړکۍ_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    إذا (bActivate) {
        سېټ_Foreground_کړکۍ(hwnd);
        إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
            WIN_سېټ_Keyboard_Focus(کړکۍ, کړکۍ->پلار == SDL_GetKeyboardFocus());
        }
    } وإلا {
        سېټ_کړکۍ_Pos(hwnd, HWND_سر, 0, 0, 0, 0, معلومات->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    إذا (bForce) {
        Attach_Thread_ننوت(dwCurID, dwMyID, FALSE);
        سېټ_Focus(hwnd);
        سېټ_فعال_کړکۍ(hwnd);
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        HWND hwnd = معلومات->hwnd;
        معلومات->expected_resize = true;
        Show_کړکۍ(hwnd, SW_MAXIMIZE);
        معلومات->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        إذا (کړکۍ->max_w || کړکۍ->max_h) {
            صحيح fx, fy, fw, fh;

            کړکۍ->windowed.w = کړکۍ->max_w ? SDL_min(کړکۍ->w, کړکۍ->max_w) : کړکۍ->windowed.w;
            کړکۍ->windowed.h = کړکۍ->max_h ? SDL_min(کړکۍ->h, کړکۍ->max_h) : کړکۍ->windowed.h;
            WIN_Adjust_کړکۍ_Rect(کړکۍ, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            معلومات->expected_resize = true;
            سېټ_کړکۍ_Pos(hwnd, HWND_سر, fx, fy, fw, fh, معلومات->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            معلومات->expected_resize = false;
        }
    } وإلا {
        معلومات->windowed_ډېرپېښ_was_maximized = true;
    }
}

فراغ WIN_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    HWND hwnd = کړکۍ->دننی->hwnd;
    Show_کړکۍ(hwnd, SW_MINIMIZE);
}

فراغ WIN_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_کړکۍ_Style(کړکۍ);

    معلومات->دننه_border_change = true;
    سېټ_کړکۍ_Long(hwnd, GWL_STYLE, style);
    WIN_سېټ_کړکۍ_Position_دننی(کړکۍ, معلومات->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    معلومات->دننه_border_change = false;
}

فراغ WIN_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_کړکۍ_Style(کړکۍ);

    سېټ_کړکۍ_Long(hwnd, GWL_STYLE, style);
}

فراغ WIN_سېټ_کړکۍ_Always_On_سر(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر)
{
    WIN_سېټ_کړکۍ_Position_دننی(کړکۍ, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

فراغ WIN_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        إذا (!معلومات->showing_کړکۍ || کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED)) {
            HWND hwnd = معلومات->hwnd;
            معلومات->expected_resize = true;
            Show_کړکۍ(hwnd, SW_RESTORE);
            معلومات->expected_resize = false;
        }
    } وإلا {
        معلومات->windowed_ډېرپېښ_was_maximized = false;
    }
}

ساكن فراغ WIN_Update_کونج_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_کړکۍ_کونج_PREFERENCE کونج_Pref)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *videodata = _this->دننی;
    إذا (videodata->Dwm_سېټ_کړکۍ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سېټ_کړکۍ_Attribute(hwnd, DWMWA_کړکۍ_کونج_PREFERENCE, &کونج_Pref, حجم(کونج_Pref));
    }
#د_که_پای
}

ساكن فراغ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *videodata = _this->دننی;
    إذا (videodata->Dwm_سېټ_کړکۍ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سېټ_کړکۍ_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#د_که_پای
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_پایله WIN_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_معلومات *displaydata = display->دننی;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات ? معلومات->hwnd : عدم;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND سر;
    صحيح x, y;
    صحيح w, h;
    bool enterMaximized = false;

#که_تعریف_شوی HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحيح)fullscreen);
#د_که_پای

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (SDL_ShouldAllowTopmost() && (کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر)) {
        سر = HWND_TOPMOST;
    } وإلا {
        سر = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    إذا (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_سېټ_Error("GetMonitorInfo failed");
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کړکۍ_Event(کړکۍ, fullscreen ? SDL_EVENT_کړکۍ_ENTER_FULLSCREEN : SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
    style = Get_کړکۍ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_کړکۍ_Style(کړکۍ);
    styleEx = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);

    إذا (fullscreen) {
        x = minfo.rcMonitor.کیڼ;
        y = minfo.rcMonitor.سر;
        w = minfo.rcMonitor.ښی - minfo.rcMonitor.کیڼ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.سر;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        إذا (style & WS_MAXIMIZE) {
            معلومات->windowed_ډېرپېښ_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_کونج_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وإلا {
        BOOL menu;

        WIN_Update_کونج_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        إذا (معلومات->windowed_ډېرپېښ_was_maximized && !معلومات->دننه_کړکۍ_deactivation) {
            enterMaximized = true;
            معلومات->disable_move_اندازه_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
        WIN_Adjust_کړکۍ_Rect_With_Style(کړکۍ, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        معلومات->windowed_ډېرپېښ_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        إذا (enterMaximized) {
            ثابت SDL_ټکی windowed_ټکی = { کړکۍ->windowed.x, کړکۍ->windowed.y };
            ثابت SDL_ټکی floating_ټکی = { کړکۍ->floating.x, کړکۍ->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_Get_Display_For_ټکی(&floating_ټکی);
            ثابت SDL_DisplayID windowed_display = SDL_Get_Display_For_ټکی(&windowed_ټکی);

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
    سېټ_کړکۍ_Long(hwnd, GWL_STYLE, style);
    معلومات->expected_resize = true;
    سېټ_کړکۍ_Pos(hwnd, سر, x, y, w, h, معلومات->copybits_flag | SWP_NOACTIVATE);
    معلومات->expected_resize = false;
    معلومات->disable_move_اندازه_events = false;

    إذا (enterMaximized) {
        WIN_Maximize_کړکۍ(_this, کړکۍ);
    }

    إذا (!fullscreen && معلومات && معلومات->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)معلومات->hicon);
    }

#که_تعریف_شوی HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحيح)fullscreen, x, y, w, h);
#د_که_پای

#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_Update_کړکۍ_ICCProfile(SDL_کړکۍ *کړکۍ, bool send_event)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);

    إذا (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, عدم, عدم, عدم);
        إذا (hdc) {
            WCHAR fileName[MAX_لار];
            DWORD file_Name_اندازه = SDL_arraysize(fileName);
            إذا (GetICMProfileW(hdc, &file_Name_اندازه, fileName)) {
                // fileNameSize includes '\0' on return
                إذا (!معلومات->ICMFileName ||
                    SDL_wcscmp(معلومات->ICMFileName, fileName) != 0) {
                    SDL_free(معلومات->ICMFileName);
                    معلومات->ICMFileName = SDL_wcsdup(fileName);
                    إذا (send_event) {
                        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_ICCPROF_بدل_شوی, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

فراغ *WIN_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    حرف *filename_utf8;
    فراغ *icc_Profile_معلومات = عدم;

    filename_utf8 = WIN_String_منزل_UTF8_W(معلومات->ICMFileName);
    إذا (filename_utf8) {
        icc_Profile_معلومات = SDL_بارول_File(filename_utf8, اندازه);
        إذا (!icc_Profile_معلومات) {
            SDL_سېټ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    أرجع icc_Profile_معلومات;
}

ساكن فراغ WIN_GrabKeyboard(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HMODULE module;

    إذا (معلومات->keyboard_hook) {
        أرجع;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    إذا (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_پته,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        أرجع;
    }

    // Capture a snapshot of the current keyboard state before the hook
    إذا (!GetKeyboardState(معلومات->videodata->pre_hook_کلی_state)) {
        أرجع;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    معلومات->keyboard_hook = سېټ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

فراغ WIN_UngrabKeyboard(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات->keyboard_hook) {
        UnhookWindowsHookEx(معلومات->keyboard_hook);
        معلومات->keyboard_hook = عدم;
    }
}

bool WIN_سېټ_کړکۍ_Mouse_Rect(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    WIN_UpdateClipCursor(کړکۍ);
    أرجع true;
}

bool WIN_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    WIN_UpdateClipCursor(کړکۍ);
    أرجع true;
}

bool WIN_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    إذا (grabbed) {
        WIN_GrabKeyboard(کړکۍ);
    } وإلا {
        WIN_UngrabKeyboard(کړکۍ);
    }

    أرجع true;
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

فراغ WIN_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    Cleanup_کړکۍ_معلومات(_this, کړکۍ);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_On_کړکۍ_Enter(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (!معلومات || !معلومات->hwnd) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر) {
        WIN_سېټ_کړکۍ_Position_دننی(کړکۍ, معلومات->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساكن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    أرجع GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_منزل_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_منزل_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

فراغ WIN_Unclip_Cursor_For_کړکۍ(SDL_کړکۍ *کړکۍ) {
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    RECT rect;
    إذا (GetClipCursor(&rect) && SDL_memcmp(&rect, &معلومات->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(عدم);
        SDL_zero(معلومات->cursor_clipped_rect);
    }
}

فراغ WIN_UpdateClipCursor(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Video_معلومات *videodata = معلومات->videodata;
    إذا (معلومات->دننه_title_click || معلومات->focus_click_pending || معلومات->postpone_clipcursor) {
        أرجع;
    }

    SDL_Rect mouse_rect = کړکۍ->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS);
    bool win_is_grabbed = (کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED);
    bool win_دننه_relmode = (کړکۍ->flags & SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ);
    bool cursor_confine = win_دننه_relmode || win_is_grabbed || win_mouse_rect;

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
            current.کیڼ != videodevice->desktop_bounds.x ||
            current.سر  != videodevice->desktop_bounds.y
        )) {
            ټکی_2 لومړی, دوهم;
            لومړی.x  = current.کیڼ;
            لومړی.y  = current.سر;
            دوهم.x = current.ښی  - 1;
            دوهم.y = current.bottom - 1;
            إذا (!Pt_دننه_Rect(&معلومات->cursor_clipped_rect, لومړی) ||
                !Pt_دننه_Rect(&معلومات->cursor_clipped_rect, دوهم)) {
                أرجع;
            }
        }
        ClipCursor(عدم);
        SDL_zero(معلومات->cursor_clipped_rect);
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
    bool قلف_منزل_ctr = (mouse->relative_ډېرپېښ && mouse->relative_ډېرپېښ_center);

    RECT client;
    إذا (!GetClientScreenRect(معلومات->hwnd, &client)) {
        أرجع;
    }

    RECT موخه = client;
    إذا (قلف_منزل_ctr) {
        LONG cx = (client.کیڼ + client.ښی ) / 2;
        LONG cy = (client.سر  + client.bottom) / 2;
        موخه = معلومات->cursor_ctrlock_rect;
        موخه.کیڼ   += cx;
        موخه.ښی  += cx;
        موخه.سر    += cy;
        موخه.bottom += cy;
    } وإلا إذا (win_mouse_rect) {
        RECT custom, overlap;
        custom.کیڼ   = client.کیڼ + mouse_rect.x;
        custom.سر    = client.سر  + mouse_rect.y;
        custom.ښی  = client.کیڼ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.سر  + mouse_rect.y + mouse_rect.h;
        إذا (IntersectRect(&overlap, &client, &custom)) {
            موخه = overlap;
        } وإلا إذا (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_کړکۍ(کړکۍ);
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
        إذا (videodata->سېټ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_کړکۍ(معلومات->hwnd, MONITOR_DEFAULTTONEAREST);
            إذا (hmon) {
                UINT hdpi_uint, vdpi_uint;
                إذا (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت عائم scale = (عائم)hdpi_uint / (عائم)USER_DEFAULT_SCREEN_DPI;
                    إذا (scale != SDL_floorf(scale)) {
                        إذا (موخه.کیڼ < موخه.ښی) {
                            موخه.کیڼ += 1;
                        }
                        إذا (موخه.ښی > موخه.کیڼ) {
                            موخه.ښی -= 1;
                        }
                        إذا (موخه.سر < موخه.bottom) {
                            موخه.سر += 1;
                        }
                        إذا (موخه.bottom > موخه.سر) {
                            موخه.bottom -= 1;
                        }
                    }
                }
            }
            videodata->سېټ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    إذا (GetClipCursor(&client) &&
        0 != SDL_memcmp(&موخه, &client, حجم(client)) &&
        ClipCursor(&موخه)) {
        معلومات->cursor_clipped_rect = موخه; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع false;
#وإلا
    ثابت SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    ثابت LONG style = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);

    إذا (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        إذا (style & WS_EX_LAYERED) {
            إذا (سېټ_کړکۍ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                أرجع WIN_سېټ_Error("SetWindowLong()");
            }
        }
    } وإلا {
        ثابت BYTE alpha = (BYTE)((صحيح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        إذا (!(style & WS_EX_LAYERED)) {
            إذا (سېټ_کړکۍ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                أرجع WIN_سېټ_Error("SetWindowLong()");
            }
        }

        إذا (سېټ_Layered_کړکۍ_ځانګړتیاوې(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            أرجع WIN_سېټ_Error("SetLayeredWindowAttributes()");
        }
    }

    أرجع true;
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساكن ثابت حرف *SDLGetClipboardFormatName(UINT cf, حرف *متن, صحيح len)
{
    بدل (cf) {
    حالة CF_متن:
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
        إذا (GetClipboardFormatNameA(cf, متن, len)) {
            أرجع متن;
        } وإلا {
            أرجع عدم;
        }
    }
}

ساكن STDMETHODIMP_(ULONG) SDLDrop_موخه_جمع_کړه_Ref(SDLDrop_موخه *موخه)
{
    أرجع ++موخه->refcount;
}

ساكن STDMETHODIMP_(ULONG) SDLDrop_موخه_Release(SDLDrop_موخه *موخه)
{
    --موخه->refcount;
    إذا (موخه->refcount == 0) {
        SDL_free(موخه);
        أرجع 0;
    }
    أرجع موخه->refcount;
}

ساكن STDMETHODIMP SDLDrop_موخه_Query_Interface(SDLDrop_موخه *موخه, REFIID riid, PVOID *ppv)
{
    إذا (ppv == عدم) {
        أرجع E_INVALIDARG;
    }

    *ppv = عدم;
    إذا (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_موخه)) {
        *ppv = (فراغ *)موخه;
    }
    إذا (*ppv) {
        SDLDrop_موخه_جمع_کړه_Ref(موخه);
        أرجع S_OK;
    }
    أرجع E_NOINTERFACE;
}

ساكن STDMETHODIMP SDLDrop_موخه_Drag_Enter(SDLDrop_موخه *موخه,
                                            IDataObject *p_معلومات_Object, DWORD grf_کلی_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ټکی_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(موخه->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, موخه->کړکۍ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(موخه->کړکۍ, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_موخه_Drag_Over(SDLDrop_موخه *موخه,
                                           DWORD grf_کلی_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ټکی_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(موخه->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, موخه->کړکۍ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(موخه->کړکۍ, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_موخه_Drag_Leave(SDLDrop_موخه *موخه)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In DragLeave");
    SDL_SendDropComplete(موخه->کړکۍ);
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_موخه_Drop(SDLDrop_موخه *موخه,
                                       IDataObject *p_معلومات_Object, DWORD grf_کلی_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    ټکی_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(موخه->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, موخه->کړکۍ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(موخه->کړکۍ, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_معلومات_Object->lpVtbl->EnumFormatEtc(p_معلومات_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        إذا (hres == S_OK) {
            FORMATETC fetc;
            طالما (pEnumFormatEtc->lpVtbl->بل_3(pEnumFormatEtc, 1, &fetc, عدم) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                إذا (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وإلا {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = موخه->format_file;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/uri-list";
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_قلف(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بینښه اوږد)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بینښه اوږد)SDL_strlen(token), (بینښه اوږد)bsize, token);
                            SDL_SendDropFile(موخه->کړکۍ, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(موخه->کړکۍ);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = موخه->format_متن;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/plain;charset=utf-8";
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_قلف(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بینښه اوږد)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بینښه اوږد)SDL_strlen(token), (بینښه اوږد)bsize, token);
                        SDL_Send_Drop_متن(موخه->کړکۍ, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(موخه->کړکۍ);
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
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_قلف(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بینښه اوږد)bsize, بفر_2);
                إذا (بفر_2) {
                    بفر_2 = WIN_String_منزل_UTF8_W((ثابت wchar_t *)بفر_2);
                    إذا (بفر_2) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)بفر_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (بینښه اوږد)lbuffer, بفر_2);
                        حرف *متن = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)متن, بفر_2, lbuffer);
                        SDL_memset((Uint8 *)متن + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = عدم;
                        حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                        طالما (token != عدم) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (بینښه اوږد)SDL_strlen(token), (بینښه اوږد)lbuffer, token);
                            SDL_Send_Drop_متن(موخه->کړکۍ, (حرف *)token);
                            token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                        }
                        SDL_free(متن);
                        SDL_free((فراغ *)بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(موخه->کړکۍ);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_متن;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_TEXT";
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_قلف(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بینښه اوږد)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بینښه اوږد)SDL_strlen(token), (بینښه اوږد)bsize, token);
                        SDL_Send_Drop_متن(موخه->کړکۍ, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(موخه->کړکۍ);
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
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                HDROP drop = (HDROP)Global_قلف(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بینښه اوږد)bsize, drop);
                UINT شمېر = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
                لكل (UINT i = 0; i < شمېر; ++i) {
                    UINT اندازه = DragQueryFile(drop, i, عدم, 0) + 1;
                    LPTSTR بفر_2 = (LPTSTR)SDL_malloc(اندازه * حجم(TCHAR));
                    إذا (بفر_2) {
                        إذا (DragQueryFile(drop, i, بفر_2, اندازه)) {
                            حرف *file = WIN_String_منزل_UTF8(بفر_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بینښه اوږد)SDL_strlen(file), (بینښه اوږد)bsize, file);
                            SDL_SendDropFile(موخه->کړکۍ, عدم, file);
                            SDL_free(file);
                        }
                        SDL_free(بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(موخه->کړکۍ);
                أرجع S_OK;
            }
        }
    }

    SDL_SendDropComplete(موخه->کړکۍ);
    أرجع S_OK;
}

ساكن فراغ *vt_Drop_موخه[] = {
    (فراغ *)(SDLDrop_موخه_Query_Interface),
    (فراغ *)(SDLDrop_موخه_جمع_کړه_Ref),
    (فراغ *)(SDLDrop_موخه_Release),
    (فراغ *)(SDLDrop_موخه_Drag_Enter),
    (فراغ *)(SDLDrop_موخه_Drag_Over),
    (فراغ *)(SDLDrop_موخه_Drag_Leave),
    (فراغ *)(SDLDrop_موخه_Drop)
};

فراغ WIN_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    إذا (معلومات->videodata->oleinitialized) {
        إذا (accept && !معلومات->drop_موخه) {
            SDLDrop_موخه *drop_موخه = (SDLDrop_موخه *)SDL_calloc(1, حجم(SDLDrop_موخه));
            إذا (drop_موخه != عدم) {
                drop_موخه->lpVtbl = vt_Drop_موخه;
                drop_موخه->کړکۍ = کړکۍ;
                drop_موخه->hwnd = معلومات->hwnd;
                drop_موخه->format_file = ثبتوونکی_Clipboard_Format_W(L"text/uri-list");
                drop_موخه->format_متن = ثبتوونکی_Clipboard_Format_W(L"text/plain;charset=utf-8");
                معلومات->drop_موخه = drop_موخه;
                SDLDrop_موخه_جمع_کړه_Ref(drop_موخه);
                ثبتوونکی_Drag_Drop(معلومات->hwnd, (LPDROPTARGET)drop_موخه);
                SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             کړکۍ->id);
            }
        } وإلا إذا (!accept && معلومات->drop_موخه) {
            RevokeDragDrop(معلومات->hwnd);
            SDLDrop_موخه_Release(معلومات->drop_موخه);
            معلومات->drop_موخه = عدم;
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         کړکۍ->id);
        }
    } وإلا {
        DragAcceptFiles(معلومات->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     کړکۍ->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_اندازه = حجم(desc);
    desc.hwnd = کړکۍ->دننی->hwnd;
    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_شمېر = 1;
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        اكسر;
    افتراضي:
        أرجع SDL_Unsupported();
    }

    Flash_کړکۍ_Ex(&desc);

    أرجع true;
}

bool WIN_Apply_کړکۍ_پرمختګ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    إذا (!معلومات->taskbar_button_created) {
        أرجع true;
    }

    إذا (کړکۍ->پرمختګ_state == SDL_پرمختګ_STATE_NONE && !معلومات->videodata->taskbar_list) {
        أرجع true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(کړکۍ);
    إذا (!taskbar_list) {
        أرجع false;
    }

    TBPFLAG tbpFlags;
    بدل (کړکۍ->پرمختګ_state) {
    حالة SDL_پرمختګ_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        اكسر;
    حالة SDL_پرمختګ_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        اكسر;
    حالة SDL_پرمختګ_STATE_نورمال:
        tbpFlags = TBPF_نورمال;
        اكسر;
    حالة SDL_پرمختګ_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        اكسر;
    حالة SDL_پرمختګ_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        اكسر;
    افتراضي:
        أرجع SDL_سېټ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->سېټ_پرمختګ_State(taskbar_list, معلومات->hwnd, tbpFlags);
    إذا (FAILED(ret)) {
        أرجع WIN_سېټ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    إذا (کړکۍ->پرمختګ_state >= SDL_پرمختګ_STATE_نورمال) {
        ret = taskbar_list->lpVtbl->سېټ_پرمختګ_ارزښت(taskbar_list, معلومات->hwnd, (ULONGLONG)(کړکۍ->پرمختګ_ارزښت * 10000.f), 10000);
        إذا (FAILED(ret)) {
            أرجع WIN_سېټ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#د_که_پای
    أرجع true;
}

فراغ WIN_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y)
{
    ثابت SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    ټکی_2 pt;

    pt.x = x;
    pt.y = y;
    Client_منزل_Screen(معلومات->hwnd, &pt);
    Send_پیغام(معلومات->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable)
{
    إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
        HWND hwnd = معلومات->hwnd;
        ثابت LONG style = Get_کړکۍ_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        إذا (focusable) {
            إذا (style & WS_EX_NOACTIVATE) {
                إذا (سېټ_کړکۍ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سېټ_Error("SetWindowLong()");
                }
            }
        } وإلا {
            إذا (!(style & WS_EX_NOACTIVATE)) {
                إذا (سېټ_کړکۍ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سېټ_Error("SetWindowLong()");
                }
            }
        }
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
            إذا (!focusable && (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS)) {
                SDL_کړکۍ *new_focus;
                ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(کړکۍ, &new_focus);
                WIN_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کړکۍ)) {
                    WIN_سېټ_Keyboard_Focus(کړکۍ, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کړکۍ_معلومات *ماشوم_معلومات = کړکۍ->دننی;
    ثابت LONG_PTR پلار_hwnd = (LONG_PTR)(پلار ? پلار->دننی->hwnd : عدم);
    ثابت DWORD style = Get_کړکۍ_Long(ماشوم_معلومات->hwnd, GWL_STYLE);

    إذا (!(style & WS_ماشوم)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        سېټ_کړکۍ_Long_Ptr(ماشوم_معلومات->hwnd, GWLP_HWNDPARENT, پلار_hwnd);
    } وإلا {
        سېټ_پلار(ماشوم_معلومات->hwnd, (HWND)پلار_hwnd);
    }
#د_که_پای /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    أرجع true;
}

bool WIN_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND پلار_hwnd = کړکۍ->پلار->دننی->hwnd;

    إذا (modal) {
        // Disable the parent window.
        Enable_کړکۍ(پلار_hwnd, FALSE);
    } وإلا إذا (!(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
        // Re-enable the parent window
        Enable_کړکۍ(پلار_hwnd, TRUE);
    }
#د_که_پای // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS
