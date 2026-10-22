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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

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
#جے_انت

// Windows CE compatibility
#جے_بنا_تعریف SWP_NOCOPYBITS
#تعریف_کرو SWP_NOCOPYBITS 0
#جے_انت

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#جے_بنا_تعریف WM_POPUPSYSTEMMENU
#تعریف_کرو WM_POPUPSYSTEMMENU 0x313
#جے_انت

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

#تعریف_کرو STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#تعریف_کرو STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کرو STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کرو STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کرو STYLE_عام              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کرو STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#تعریف_کرو STYLE_نقاب                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_عام | STYLE_RESIZABLE)

ساكن DWORD Get_کھڑکی_Style(SDL_کھڑکی *کھڑکی)
{
    DWORD style = 0;

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        style |= WS_POPUP;
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وإلا {
        إذا (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
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
            style |= STYLE_عام;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        إذا (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            إذا (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        إذا (کھڑکی->اندرونی && کھڑکی->اندرونی->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    أرجع style;
}

ساكن DWORD Get_کھڑکی_Style_Ex(SDL_کھڑکی *کھڑکی)
{
    DWORD style = 0;

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی) || (کھڑکی->flags & SDL_کھڑکی_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی) || (کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    أرجع style;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن ITaskbarList3 *GetTaskbarList(SDL_کھڑکی *کھڑکی)
{
    ثابت SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_assert(انکڑے->taskbar_button_created);
    إذا (!انکڑے->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, عدم, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&انکڑے->videodata->taskbar_list);
        إذا (FAILED(ret)) {
            WIN_سیٹ_Error_From_HRESULT("Unable to create taskbar list", ret);
            أرجع عدم;
        }
        ITaskbarList3 *taskbarlist = انکڑے->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        إذا (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            انکڑے->videodata->taskbar_list = عدم;
            WIN_سیٹ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            أرجع عدم;
        }
    }
    أرجع انکڑے->videodata->taskbar_list;
}
#جے_انت

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساكن bool WIN_Adjust_کھڑکی_Rect_With_Style(SDL_کھڑکی *کھڑکی, DWORD style, DWORD styleEx, BOOL menu, صحيح *x, صحيح *y, صحيح *چوڑائی, صحيح *اچائی, SDL_کھڑکی_Rect rect_type)
{
    SDL_Video_انکڑے *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->اندرونی : عدم;
    RECT rect;

    // Client rect, in points
    بدل (rect_type) {
    حالة SDL_WINDOWRECT_CURRENT:
        SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, x, y);
        *چوڑائی = کھڑکی->w;
        *اچائی = کھڑکی->h;
        اكسر;
    حالة SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->windowed.x, کھڑکی->windowed.y, x, y);
        *چوڑائی = کھڑکی->windowed.w;
        *اچائی = کھڑکی->windowed.h;
        اكسر;
    حالة SDL_WINDOWRECT_FLOATING:
        SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->floating.x, کھڑکی->floating.y, x, y);
        *چوڑائی = کھڑکی->floating.w;
        *اچائی = کھڑکی->floating.h;
        اكسر;
    حالة SDL_WINDOWRECT_PENDING:
        SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->pending.x, کھڑکی->pending.y, x, y);
        *چوڑائی = کھڑکی->pending.w;
        *اچائی = کھڑکی->pending.h;
        اكسر;
    افتراضي:
        // Should never be here
        SDL_assert_release(false);
        *چوڑائی = 0;
        *اچائی = 0;
        اكسر;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.بایاں = 0;
    rect.چوٹی = 0;
    rect.دایاں = *چوڑائی;
    rect.bottom = *اچائی;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    إذا (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(کھڑکی)) {
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_کھڑکی_Rect_Ex(&rect, style, menu, 0);
#وإلا
        إذا (WIN_Is_فی_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            إذا (videodata) {
                UINT چوکھٹا_dpi;
                SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
                چوکھٹا_dpi = (انکڑے && videodata->Get_Dpi_For_کھڑکی) ? videodata->Get_Dpi_For_کھڑکی(انکڑے->hwnd) : USER_DEFAULT_SCREEN_DPI;
                إذا (videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, چوکھٹا_dpi) == 0) {
                    أرجع WIN_سیٹ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } وإلا {
            إذا (Adjust_کھڑکی_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                أرجع WIN_سیٹ_Error("AdjustWindowRectEx()");
            }
        }
#جے_انت
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.بایاں;
    *y += rect.چوٹی;
    *چوڑائی = (rect.دایاں - rect.بایاں);
    *اچائی = (rect.bottom - rect.چوٹی);

#جے_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.x : کھڑکی->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.y : کھڑکی->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.w : کھڑکی->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.h : کھڑکی->h),
            *x, *y, *چوڑائی, *اچائی, چوکھٹا_dpi);
#جے_انت
    أرجع true;
}

bool WIN_Adjust_کھڑکی_Rect(SDL_کھڑکی *کھڑکی, صحيح *x, صحيح *y, صحيح *چوڑائی, صحيح *اچائی, SDL_کھڑکی_Rect rect_type)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#جے_انت
    أرجع WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, menu, x, y, چوڑائی, اچائی, rect_type);
}

bool WIN_Adjust_کھڑکی_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکھٹا_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_انکڑے *videodata = videodevice ? videodevice->اندرونی : عدم;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#جے_انت

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_کھڑکی_Rect_Ex(lpRect, style, menu, styleEx);
#وإلا
    إذا (WIN_Is_فی_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        إذا (!چوکھٹا_dpi) {
            چوکھٹا_dpi = videodata->Get_Dpi_For_کھڑکی ? videodata->Get_Dpi_For_کھڑکی(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        إذا (!videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, چوکھٹا_dpi)) {
            أرجع WIN_سیٹ_Error("AdjustWindowRectExForDpi()");
        }
    } وإلا {
        إذا (!Adjust_کھڑکی_Rect_Ex(lpRect, style, menu, styleEx)) {
            أرجع WIN_سیٹ_Error("AdjustWindowRectEx()");
        }
    }
#جے_انت
    أرجع true;
}

bool WIN_سیٹ_کھڑکی_Position_اندرونی(SDL_کھڑکی *کھڑکی, UINT flags, SDL_کھڑکی_Rect rect_type)
{
    SDL_کھڑکی *بچہ_کھڑکی;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    HWND چوٹی;
    صحيح x, y;
    صحيح w, h;
    bool نتیجہ = true;

    // Figure out what the window area will be
    إذا (SDL_ShouldAllowTopmost() && (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
        چوٹی = HWND_TOPMOST;
    } وإلا {
        چوٹی = HWND_NOTOPMOST;
    }

    WIN_Adjust_کھڑکی_Rect(کھڑکی, &x, &y, &w, &h, rect_type);

    انکڑے->expected_resize = !(flags & SWP_NOSIZE);
    إذا (سیٹ_کھڑکی_Pos(hwnd, چوٹی, x, y, w, h, flags) == 0) {
        نتیجہ = WIN_سیٹ_Error("SetWindowPos()");
    }
    انکڑے->expected_resize = false;

    // Update any child windows
    لكل (بچہ_کھڑکی = کھڑکی->پہلا_بچہ; بچہ_کھڑکی; بچہ_کھڑکی = بچہ_کھڑکی->اگلا_sibling) {
        إذا (!بچہ_کھڑکی->اندرونی) {
            // This child window is not yet fully initialized.
            استمر;
        }
        إذا (!WIN_سیٹ_کھڑکی_Position_اندرونی(بچہ_کھڑکی, flags, SDL_WINDOWRECT_CURRENT)) {
            نتیجہ = false;
        }
    }
    أرجع نتیجہ;
}

ساكن SDL_کھڑکی_Erase_Background_منوال Get_Erase_Background_منوال_Hint(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_منوال);
    إذا (!hint)
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "never"))
        أرجع SDL_ERASEBACKGROUNDMODE_NEVER;

    إذا (SDL_strstr(hint, "initial"))
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "always"))
        أرجع SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحيح منوال = SDL_GetStringInteger(hint, 1);
    إذا (منوال < 0 || منوال > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    أرجع (SDL_کھڑکی_Erase_Background_منوال)منوال;
}

ساكن bool تیاری_کھڑکی_انکڑے(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, HWND hwnd, HWND ماپا)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے;

    // Allocate the window data
    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }
    انکڑے->کھڑکی = کھڑکی;
    انکڑے->hwnd = hwnd;
    انکڑے->ماپا = ماپا;
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    انکڑے->hdc = (HDC)انکڑے->hwnd;
#وإلا
    انکڑے->hdc = GetDC(hwnd);
#جے_انت
    انکڑے->hinstance = (HINSTANCE)Get_کھڑکی_Long_Ptr(hwnd, GWLP_HINSTANCE);
    انکڑے->mouse_button_flags = (WPARAM)-1;
    انکڑے->آخری_اشارہ_گر_update = (LPARAM)-1;
    انکڑے->videodata = videodata;
    انکڑے->initializing = true;
    انکڑے->hint_erase_background_منوال = Get_Erase_Background_منوال_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    انکڑے->cursor_ctrlock_rect.بایاں   = 0 - remote_desktop_adjustment;
    انکڑے->cursor_ctrlock_rect.چوٹی    = 0;
    انکڑے->cursor_ctrlock_rect.دایاں  = 1 + remote_desktop_adjustment;
    انکڑے->cursor_ctrlock_rect.bottom = 1;
#جے_انت

    إذا (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        انکڑے->copybits_flag = 0;
    } وإلا {
        انکڑے->copybits_flag = SWP_NOCOPYBITS;
    }

#جے_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", انکڑے->scaling_dpi);
#جے_انت

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    إذا (!سیٹ_Prop(hwnd, متن_2("SDL_WindowData"), انکڑے)) {
        ReleaseDC(hwnd, انکڑے->hdc);
        SDL_free(انکڑے);
        أرجع WIN_سیٹ_Error("SetProp() failed");
    }
#جے_انت

    کھڑکی->اندرونی = انکڑے;

    // Set up the window proc function
    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
#جے_تعریف_شدہ GWLP_WNDPROC
        انکڑے->wndproc = (WNDPROC)Get_کھڑکی_Long_Ptr(hwnd, GWLP_WNDPROC);
        إذا (انکڑے->wndproc != WIN_کھڑکی_Proc) {
            سیٹ_کھڑکی_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_کھڑکی_Proc);
        }
#وإلا
        انکڑے->wndproc = (WNDPROC)Get_کھڑکی_Long(hwnd, GWL_WNDPROC);
        إذا (انکڑے->wndproc != WIN_کھڑکی_Proc) {
            سیٹ_کھڑکی_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_کھڑکی_Proc);
        }
#جے_انت
    } وإلا {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
        إذا (style & WS_VISIBLE) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        } وإلا {
            کھڑکی->flags |= SDL_کھڑکی_HIDDEN;
        }
        إذا (style & WS_POPUP) {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
        } وإلا {
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        }
        إذا (style & WS_THICKFRAME) {
            کھڑکی->flags |= SDL_کھڑکی_RESIZABLE;
        } وإلا إذا (!(style & WS_POPUP)) {
            کھڑکی->flags &= ~SDL_کھڑکی_RESIZABLE;
        }
#جے_تعریف_شدہ WS_MAXIMIZE
        إذا (style & WS_MAXIMIZE) {
            کھڑکی->flags |= SDL_کھڑکی_MAXIMIZED;
        } وإلا
#جے_انت
        {
            کھڑکی->flags &= ~SDL_کھڑکی_MAXIMIZED;
        }
#جے_تعریف_شدہ WS_MINIMIZE
        إذا (style & WS_MINIMIZE) {
            کھڑکی->flags |= SDL_کھڑکی_MINIMIZED;
        } وإلا
#جے_انت
        {
            کھڑکی->flags &= ~SDL_کھڑکی_MINIMIZED;
        }
    }
    إذا (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        RECT rect;
        إذا (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
            صحيح w = rect.دایاں;
            صحيح h = rect.bottom;

            إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
                کھڑکی->floating.w = کھڑکی->windowed.w = کھڑکی->w = w;
                کھڑکی->floating.h = کھڑکی->windowed.h = کھڑکی->h = h;
            } وإلا إذا ((کھڑکی->windowed.w && کھڑکی->windowed.w != w) || (کھڑکی->windowed.h && کھڑکی->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحيح x, y;
                // Figure out what the window area will be
                WIN_Adjust_کھڑکی_Rect(کھڑکی, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                انکڑے->expected_resize = true;
                سیٹ_کھڑکی_Pos(hwnd, عدم, x, y, w, h, انکڑے->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                انکڑے->expected_resize = false;
            } وإلا {
                کھڑکی->w = w;
                کھڑکی->h = h;
            }
        }
    }
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        نقطہ_2 نقطہ;
        نقطہ.x = 0;
        نقطہ.y = 0;
        إذا (Client_منزل_Screen(hwnd, &نقطہ)) {
            إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
                کھڑکی->floating.x = کھڑکی->windowed.x = نقطہ.x;
                کھڑکی->floating.y = کھڑکی->windowed.y = نقطہ.y;
            }
            کھڑکی->x = نقطہ.x;
            کھڑکی->y = نقطہ.y;
        }
    }

    WIN_Update_کھڑکی_ICCProfile(کھڑکی, false);
#جے_انت

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
#وإلا
    إذا (GetFocus() == hwnd) {
        کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
        WIN_UpdateClipCursor(کھڑکی);
    }
#جے_انت

    إذا (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        WIN_سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, true);
    } وإلا {
        WIN_سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, false);
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    إذا (videodata->رجسٹر_Touch_کھڑکی) {
        videodata->رجسٹر_Touch_کھڑکی(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#جے_انت

    إذا (انکڑے->ماپا && !کھڑکی->ماپا) {
        انکڑے->destroy_ماپا_with_کھڑکی = true;
    }

    انکڑے->initializing = false;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحيح titleLen;
        bool isstack;

        titleLen = Get_کھڑکی_متن_لمائی(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        إذا (title) {
            titleLen = Get_کھڑکی_متن(hwnd, title, titleLen + 1);
        } وإلا {
            titleLen = 0;
        }
        إذا (titleLen > 0) {
            کھڑکی->title = WIN_String_منزل_UTF8(title);
        }
        إذا (title) {
            SDL_small_free(title, isstack);
        }
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_HWND_اشارہ_گر, انکڑے->hwnd);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_HDC_اشارہ_گر, انکڑے->hdc);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_INSTANCE_اشارہ_گر, انکڑے->hinstance);

    // All done!
    أرجع true;
}

ساكن فراغ Cleanup_کھڑکی_انکڑے(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (انکڑے->drop_نشانہ) {
            WIN_AcceptDragAndDrop(کھڑکی, false);
        }
        SDL_free(انکڑے->ICMFileName);
        إذا (انکڑے->keyboard_hook) {
            UnhookWindowsHookEx(انکڑے->keyboard_hook);
        }
        إذا (انکڑے->hicon) {
            DestroyIcon(انکڑے->hicon);
        }
        ReleaseDC(انکڑے->hwnd, انکڑے->hdc);
        RemoveProp(انکڑے->hwnd, متن_2("SDL_WindowData"));
#جے_انت
        إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            Destroy_کھڑکی(انکڑے->hwnd);
            إذا (انکڑے->destroy_ماپا_with_کھڑکی && انکڑے->ماپا) {
                Destroy_کھڑکی(انکڑے->ماپا);
            }
        } وإلا {
            // Restore any original event handler...
            إذا (انکڑے->wndproc) {
#جے_تعریف_شدہ GWLP_WNDPROC
                سیٹ_کھڑکی_Long_Ptr(انکڑے->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)انکڑے->wndproc);
#وإلا
                سیٹ_کھڑکی_Long(انکڑے->hwnd, GWL_WNDPROC,
                              (LONG_PTR)انکڑے->wndproc);
#جے_انت
            }
        }
        SDL_free(انکڑے);
    }
    کھڑکی->اندرونی = عدم;
}

ساكن فراغ WIN_ConstrainPopup(SDL_کھڑکی *کھڑکی, bool output_منزل_pending)
{
    // Possibly clamp popup windows to the output borders
    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->floating.x;
        صحيح abs_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->floating.y;
        ثابت صحيح چوڑائی = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
        ثابت صحيح اچائی = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
        صحيح وتھ_x = 0, وتھ_y = 0;

        إذا (کھڑکی->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = کھڑکی->ماپا; SDL_کھڑکی_IS_POPUP(w); w = w->ماپا) {
                وتھ_x += w->x;
                وتھ_y += w->y;
            }

            وتھ_x += w->x;
            وتھ_y += w->y;
            abs_x += وتھ_x;
            abs_y += وتھ_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_کھڑکی(w);
            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + چوڑائی > rect.x + rect.w) {
                abs_x -= (abs_x + چوڑائی) - (rect.x + rect.w);
            }
            إذا (abs_y + اچائی > rect.y + rect.h) {
                abs_y -= (abs_y + اچائی) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            کھڑکی->pending.x = abs_x - وتھ_x;
            کھڑکی->pending.y = abs_y - وتھ_y;
            کھڑکی->pending.w = چوڑائی;
            کھڑکی->pending.h = اچائی;
        } وإلا {
            کھڑکی->floating.x = abs_x - وتھ_x;
            کھڑکی->floating.y = abs_y - وتھ_y;
            کھڑکی->floating.w = چوڑائی;
            کھڑکی->floating.h = اچائی;
        }
    }
}

ساكن فراغ WIN_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_سرگرم_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the topmost parent
    طالما (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->ماپا;
    }

    toplevel->keyboard_focus = کھڑکی;

    إذا (سیٹ_سرگرم_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

bool WIN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    HWND hwnd = (HWND)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_HWND_اشارہ_گر, SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    HWND ماپا = عدم;
    إذا (hwnd) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;

        إذا (!تیاری_کھڑکی_انکڑے(_this, کھڑکی, hwnd, ماپا)) {
            أرجع false;
        }
    } وإلا {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحيح x, y;
        صحيح w, h;

        إذا (کھڑکی->flags & SDL_کھڑکی_UTILITY) {
            ماپا = Create_کھڑکی(SDL_Appname, متن_2(""), STYLE_BASIC, 0, 0, 32, 32, عدم, عدم, SDL_Instance, عدم);
        } وإلا إذا (کھڑکی->ماپا) {
            ماپا = کھڑکی->ماپا->اندرونی->hwnd;
        }

        style |= Get_کھڑکی_Style(کھڑکی);
        styleEx |= (DWORD)SDL_Get_نمبر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_STYLE_EX_نمبر, Get_کھڑکی_Style_Ex(کھڑکی));

        // Figure out what the window area will be
        WIN_ConstrainPopup(کھڑکی, false);
        WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_کھڑکی_Ex(styleEx, SDL_Appname, متن_2(""), style,
                              x, y, w, h, ماپا, عدم, SDL_Instance, عدم);
        إذا (!hwnd) {
            أرجع WIN_سیٹ_Error("Couldn't create window");
        }

        WIN_Update_Dark_منوال_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        إذا (!تیاری_کھڑکی_انکڑے(_this, کھڑکی, hwnd, ماپا)) {
            Destroy_کھڑکی(hwnd);
            إذا (ماپا) {
                Destroy_کھڑکی(ماپا);
            }
            أرجع false;
        }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_متن_داخلہ(_this, کھڑکی);
#جے_انت

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        سیٹ_کھڑکی_Pos(hwnd, عدم, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
            Show_کھڑکی(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    إذا (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) {
        إذا (videodata->Dwm_Enable_Blur_Behind_کھڑکی) {
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
            videodata->Dwm_Enable_Blur_Behind_کھڑکی(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_PIXEL_FORMAT_HWND_اشارہ_گر, عدم);
    إذا (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحيح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        إذا (!سیٹ_Pixel_Format(کھڑکی->اندرونی->hdc, pixel_format, &pfd)) {
            WIN_Destroy_کھڑکی(_this, کھڑکی);
            أرجع WIN_سیٹ_Error("SetPixelFormat()");
        }
    } وإلا {
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
            أرجع true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_ES2
        إذا ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_انکڑے || WIN_GL_UseEGL(_this))
#جے_انت // SDL_VIDEO_OPENGL_WGL
        ) {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            إذا (!WIN_GLES_تیاری_کھڑکی(_this, کھڑکی)) {
                WIN_Destroy_کھڑکی(_this, کھڑکی);
                أرجع false;
            }
            أرجع true;
#وإلا
            أرجع SDL_سیٹ_Error("Could not create GLES window surface (EGL support not configured)");
#جے_انت // SDL_VIDEO_OPENGL_EGL
        }
#جے_انت // SDL_VIDEO_OPENGL_ES2

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
        إذا (!WIN_GL_تیاری_کھڑکی(_this, کھڑکی)) {
            WIN_Destroy_کھڑکی(_this, کھڑکی);
            أرجع false;
        }
#وإلا
        أرجع SDL_سیٹ_Error("Could not create GL window (WGL support not configured)");
#جے_انت
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

فراغ WIN_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    LPTSTR title = WIN_UTF8_منزل_String(کھڑکی->title);
    سیٹ_کھڑکی_متن(hwnd, title);
    SDL_free(title);
#جے_انت
}

bool WIN_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    HICON hicon = عدم;
    BYTE *icon_bmp;
    صحيح icon_len, نقاب_len, صف_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool نتیجہ = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_ویلا_ASSERT(WIN_سیٹ_کھڑکی_Icon_ورتدا_BITMAPINFOHEADER_منزل_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    نقاب_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + نقاب_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    إذا (!icon_bmp) {
        أرجع false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_ناپ = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->bi_چوڑائی = SDL_Swap32LE(icon->w);
    bmi->bi_اچائی = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_ثنائی_ہندسہ_گنتی = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_ناپ_Image = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->bi_XPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_ورتیا = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[حجم(BITMAPINFOHEADER)];
    صف_len = icon->w * حجم(Uint32);
    y = icon->h;
    طالما (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, صف_len);
        dst += صف_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - نقاب_len, 0xFF, نقاب_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    إذا (!hicon) {
        أرجع SDL_سیٹ_Error("SetWindowIcon() failed, error %08X", (بنانشانی صحيح)Get_آخری_Error());
    }

    إذا (انکڑے->hicon) {
        DestroyIcon(انکڑے->hicon);
    }
    انکڑے->hicon = hicon;

    // Set the icon for the window
    Send_سنیہا(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_سنیہا(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    أرجع نتیجہ;
#وإلا
    أرجع SDL_Unsupported();
#جے_انت
}

bool WIN_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        إذا (!(کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED))) {
            WIN_ConstrainPopup(کھڑکی, true);
            أرجع WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی,
                                                 کھڑکی->اندرونی->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وإلا {
        أرجع SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, true);
    }

    أرجع true;
}

فراغ WIN_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED))) {
        WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, کھڑکی->اندرونی->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وإلا {
        // Can't resize the window
        کھڑکی->آخری_ناپ_pending = false;
    }
}

bool WIN_Get_کھڑکی_Borders_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *چوٹی = rcClient.چوٹی;
    *بایاں = rcClient.بایاں;
    *bottom = rcClient.bottom;
    *دایاں = rcClient.دایاں;

    أرجع true;
#وإلا  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    RECT rcClient, rc_کھڑکی;
    نقطہ_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    إذا (!GetClientRect(hwnd, &rcClient)) {
        أرجع SDL_سیٹ_Error("GetClientRect() failed, error %08X", (بنانشانی صحيح)Get_آخری_Error());
    }

    إذا (!Get_کھڑکی_Rect(hwnd, &rc_کھڑکی)) {
        أرجع SDL_سیٹ_Error("GetWindowRect() failed, error %08X", (بنانشانی صحيح)Get_آخری_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_کھڑکی.چوٹی;
    ptDiff.x = rc_کھڑکی.بایاں;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سیٹ_Error("ScreenToClient() failed, error %08X", (بنانشانی صحيح)Get_آخری_Error());
    }

    rc_کھڑکی.چوٹی = ptDiff.y;
    rc_کھڑکی.بایاں = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_کھڑکی.bottom;
    ptDiff.x = rc_کھڑکی.دایاں;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سیٹ_Error("ScreenToClient() failed, error %08X", (بنانشانی صحيح)Get_آخری_Error());
    }

    rc_کھڑکی.bottom = ptDiff.y;
    rc_کھڑکی.دایاں = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *چوٹی = rcClient.چوٹی - rc_کھڑکی.چوٹی;
    *بایاں = rcClient.بایاں - rc_کھڑکی.بایاں;
    *bottom = rc_کھڑکی.bottom - rcClient.bottom;
    *دایاں = rc_کھڑکی.دایاں - rcClient.دایاں;

    أرجع true;
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    ثابت SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    RECT rect;

    إذا (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
        *w = rect.دایاں;
        *h = rect.bottom;
    } وإلا إذا (کھڑکی->آخری_pixel_w && کھڑکی->آخری_pixel_h) {
        *w = کھڑکی->آخری_pixel_w;
        *h = کھڑکی->آخری_pixel_h;
    } وإلا {
        // Probably created minimized, use the restored size
        *w = کھڑکی->floating.w;
        *h = کھڑکی->floating.h;
    }
}

فراغ WIN_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true);

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Update our position in case our parent moved while we were hidden
        WIN_سیٹ_کھڑکی_Position(_this, کھڑکی);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    إذا (کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
            style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_نقاب;
            style |= Get_کھڑکی_Style(کھڑکی);
            سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        }
    }
    style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
    إذا (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    انکڑے->showing_کھڑکی = true;
    إذا (bActivate) {
        Show_کھڑکی(hwnd, SW_SHOW);
    } وإلا {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        سیٹ_کھڑکی_Pos(hwnd, عدم, 0, 0, 0, 0, کھڑکی->اندرونی->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    انکڑے->showing_کھڑکی = false;

    إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE) && bActivate) {
        WIN_سیٹ_Keyboard_Focus(کھڑکی, true);
    }
    إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        WIN_سیٹ_کھڑکی_Modal(_this, کھڑکی, true);
    }
}

فراغ WIN_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی->hwnd;

    إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        WIN_سیٹ_کھڑکی_Modal(_this, کھڑکی, false);
    }

    Show_کھڑکی(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
        WIN_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }
}

فراغ WIN_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
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
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = عدم;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    إذا (bForce) {
        hCurWnd = Get_Foreground_کھڑکی();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_کھڑکی_Thread_Process_Id(hCurWnd, عدم);
        Show_کھڑکی(hwnd, SW_RESTORE);
        Attach_Thread_داخلہ(dwCurID, dwMyID, TRUE);
        سیٹ_کھڑکی_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        إذا (!SDL_ShouldAllowTopmost() || !(کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
            سیٹ_کھڑکی_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    إذا (bActivate) {
        سیٹ_Foreground_کھڑکی(hwnd);
        إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
            WIN_سیٹ_Keyboard_Focus(کھڑکی, کھڑکی->ماپا == SDL_GetKeyboardFocus());
        }
    } وإلا {
        سیٹ_کھڑکی_Pos(hwnd, HWND_چوٹی, 0, 0, 0, 0, انکڑے->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    إذا (bForce) {
        Attach_Thread_داخلہ(dwCurID, dwMyID, FALSE);
        سیٹ_Focus(hwnd);
        سیٹ_سرگرم_کھڑکی(hwnd);
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        HWND hwnd = انکڑے->hwnd;
        انکڑے->expected_resize = true;
        Show_کھڑکی(hwnd, SW_MAXIMIZE);
        انکڑے->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        إذا (کھڑکی->max_w || کھڑکی->max_h) {
            صحيح fx, fy, fw, fh;

            کھڑکی->windowed.w = کھڑکی->max_w ? SDL_min(کھڑکی->w, کھڑکی->max_w) : کھڑکی->windowed.w;
            کھڑکی->windowed.h = کھڑکی->max_h ? SDL_min(کھڑکی->h, کھڑکی->max_h) : کھڑکی->windowed.h;
            WIN_Adjust_کھڑکی_Rect(کھڑکی, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            انکڑے->expected_resize = true;
            سیٹ_کھڑکی_Pos(hwnd, HWND_چوٹی, fx, fy, fw, fh, انکڑے->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            انکڑے->expected_resize = false;
        }
    } وإلا {
        انکڑے->windowed_منوال_was_maximized = true;
    }
}

فراغ WIN_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی->hwnd;
    Show_کھڑکی(hwnd, SW_MINIMIZE);
}

فراغ WIN_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    DWORD style;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);

    انکڑے->وچ_border_change = true;
    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
    WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, انکڑے->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    انکڑے->وچ_border_change = false;
}

فراغ WIN_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    DWORD style;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);

    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
}

فراغ WIN_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

فراغ WIN_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        إذا (!انکڑے->showing_کھڑکی || کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED)) {
            HWND hwnd = انکڑے->hwnd;
            انکڑے->expected_resize = true;
            Show_کھڑکی(hwnd, SW_RESTORE);
            انکڑے->expected_resize = false;
        }
    } وإلا {
        انکڑے->windowed_منوال_was_maximized = false;
    }
}

ساكن فراغ WIN_Update_کونا_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_کھڑکی_کونا_PREFERENCE کونا_Pref)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    إذا (videodata->Dwm_سیٹ_کھڑکی_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سیٹ_کھڑکی_Attribute(hwnd, DWMWA_کھڑکی_کونا_PREFERENCE, &کونا_Pref, حجم(کونا_Pref));
    }
#جے_انت
}

ساكن فراغ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    إذا (videodata->Dwm_سیٹ_کھڑکی_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سیٹ_کھڑکی_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#جے_انت
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_نتیجہ WIN_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_انکڑے *displaydata = display->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے ? انکڑے->hwnd : عدم;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND چوٹی;
    صحيح x, y;
    صحيح w, h;
    bool enterMaximized = false;

#جے_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحيح)fullscreen);
#جے_انت

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (SDL_ShouldAllowTopmost() && (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
        چوٹی = HWND_TOPMOST;
    } وإلا {
        چوٹی = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_ناپ = حجم(MONITORINFO);
    إذا (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_سیٹ_Error("GetMonitorInfo failed");
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

    إذا (fullscreen) {
        x = minfo.rcMonitor.بایاں;
        y = minfo.rcMonitor.چوٹی;
        w = minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        إذا (style & WS_MAXIMIZE) {
            انکڑے->windowed_منوال_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_کونا_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وإلا {
        BOOL menu;

        WIN_Update_کونا_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        إذا (انکڑے->windowed_منوال_was_maximized && !انکڑے->وچ_کھڑکی_deactivation) {
            enterMaximized = true;
            انکڑے->disable_move_ناپ_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
        WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        انکڑے->windowed_منوال_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        إذا (enterMaximized) {
            ثابت SDL_نقطہ windowed_نقطہ = { کھڑکی->windowed.x, کھڑکی->windowed.y };
            ثابت SDL_نقطہ floating_نقطہ = { کھڑکی->floating.x, کھڑکی->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_Get_Display_For_نقطہ(&floating_نقطہ);
            ثابت SDL_DisplayID windowed_display = SDL_Get_Display_For_نقطہ(&windowed_نقطہ);

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
    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
    انکڑے->expected_resize = true;
    سیٹ_کھڑکی_Pos(hwnd, چوٹی, x, y, w, h, انکڑے->copybits_flag | SWP_NOACTIVATE);
    انکڑے->expected_resize = false;
    انکڑے->disable_move_ناپ_events = false;

    إذا (enterMaximized) {
        WIN_Maximize_کھڑکی(_this, کھڑکی);
    }

    إذا (!fullscreen && انکڑے && انکڑے->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_سنیہا(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_سنیہا(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)انکڑے->hicon);
    }

#جے_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحيح)fullscreen, x, y, w, h);
#جے_انت

#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_Update_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, bool send_event)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);

    إذا (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, عدم, عدم, عدم);
        إذا (hdc) {
            WCHAR fileName[MAX_رستہ];
            DWORD file_Name_ناپ = SDL_arraysize(fileName);
            إذا (GetICMProfileW(hdc, &file_Name_ناپ, fileName)) {
                // fileNameSize includes '\0' on return
                إذا (!انکڑے->ICMFileName ||
                    SDL_wcscmp(انکڑے->ICMFileName, fileName) != 0) {
                    SDL_free(انکڑے->ICMFileName);
                    انکڑے->ICMFileName = SDL_wcsdup(fileName);
                    إذا (send_event) {
                        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلیا, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

فراغ *WIN_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    حرف *filename_utf8;
    فراغ *icc_Profile_انکڑے = عدم;

    filename_utf8 = WIN_String_منزل_UTF8_W(انکڑے->ICMFileName);
    إذا (filename_utf8) {
        icc_Profile_انکڑے = SDL_لدو_File(filename_utf8, ناپ);
        إذا (!icc_Profile_انکڑے) {
            SDL_سیٹ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    أرجع icc_Profile_انکڑے;
}

ساكن فراغ WIN_GrabKeyboard(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HMODULE module;

    إذا (انکڑے->keyboard_hook) {
        أرجع;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    إذا (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_پتہ,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        أرجع;
    }

    // Capture a snapshot of the current keyboard state before the hook
    إذا (!GetKeyboardState(انکڑے->videodata->pre_hook_کلید_state)) {
        أرجع;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    انکڑے->keyboard_hook = سیٹ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

فراغ WIN_UngrabKeyboard(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے->keyboard_hook) {
        UnhookWindowsHookEx(انکڑے->keyboard_hook);
        انکڑے->keyboard_hook = عدم;
    }
}

bool WIN_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    WIN_UpdateClipCursor(کھڑکی);
    أرجع true;
}

bool WIN_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    WIN_UpdateClipCursor(کھڑکی);
    أرجع true;
}

bool WIN_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    إذا (grabbed) {
        WIN_GrabKeyboard(کھڑکی);
    } وإلا {
        WIN_UngrabKeyboard(کھڑکی);
    }

    أرجع true;
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

فراغ WIN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Cleanup_کھڑکی_انکڑے(_this, کھڑکی);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_On_کھڑکی_Enter(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (!انکڑے || !انکڑے->hwnd) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, انکڑے->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساكن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    أرجع GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_منزل_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_منزل_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

فراغ WIN_Unclip_Cursor_For_کھڑکی(SDL_کھڑکی *کھڑکی) {
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    RECT rect;
    إذا (GetClipCursor(&rect) && SDL_memcmp(&rect, &انکڑے->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(عدم);
        SDL_zero(انکڑے->cursor_clipped_rect);
    }
}

فراغ WIN_UpdateClipCursor(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Video_انکڑے *videodata = انکڑے->videodata;
    إذا (انکڑے->وچ_title_click || انکڑے->focus_click_pending || انکڑے->postpone_clipcursor) {
        أرجع;
    }

    SDL_Rect mouse_rect = کھڑکی->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS);
    bool win_is_grabbed = (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED);
    bool win_وچ_relmode = (کھڑکی->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال);
    bool cursor_confine = win_وچ_relmode || win_is_grabbed || win_mouse_rect;

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
            current.بایاں != videodevice->desktop_bounds.x ||
            current.چوٹی  != videodevice->desktop_bounds.y
        )) {
            نقطہ_2 پہلا, دوجا;
            پہلا.x  = current.بایاں;
            پہلا.y  = current.چوٹی;
            دوجا.x = current.دایاں  - 1;
            دوجا.y = current.bottom - 1;
            إذا (!Pt_وچ_Rect(&انکڑے->cursor_clipped_rect, پہلا) ||
                !Pt_وچ_Rect(&انکڑے->cursor_clipped_rect, دوجا)) {
                أرجع;
            }
        }
        ClipCursor(عدم);
        SDL_zero(انکڑے->cursor_clipped_rect);
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
    bool جندرا_منزل_ctr = (mouse->relative_منوال && mouse->relative_منوال_center);

    RECT client;
    إذا (!GetClientScreenRect(انکڑے->hwnd, &client)) {
        أرجع;
    }

    RECT نشانہ = client;
    إذا (جندرا_منزل_ctr) {
        LONG cx = (client.بایاں + client.دایاں ) / 2;
        LONG cy = (client.چوٹی  + client.bottom) / 2;
        نشانہ = انکڑے->cursor_ctrlock_rect;
        نشانہ.بایاں   += cx;
        نشانہ.دایاں  += cx;
        نشانہ.چوٹی    += cy;
        نشانہ.bottom += cy;
    } وإلا إذا (win_mouse_rect) {
        RECT custom, overlap;
        custom.بایاں   = client.بایاں + mouse_rect.x;
        custom.چوٹی    = client.چوٹی  + mouse_rect.y;
        custom.دایاں  = client.بایاں + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.چوٹی  + mouse_rect.y + mouse_rect.h;
        إذا (IntersectRect(&overlap, &client, &custom)) {
            نشانہ = overlap;
        } وإلا إذا (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_کھڑکی(کھڑکی);
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
        إذا (videodata->سیٹ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_کھڑکی(انکڑے->hwnd, MONITOR_DEFAULTTONEAREST);
            إذا (hmon) {
                UINT hdpi_uint, vdpi_uint;
                إذا (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت عائم scale = (عائم)hdpi_uint / (عائم)USER_DEFAULT_SCREEN_DPI;
                    إذا (scale != SDL_floorf(scale)) {
                        إذا (نشانہ.بایاں < نشانہ.دایاں) {
                            نشانہ.بایاں += 1;
                        }
                        إذا (نشانہ.دایاں > نشانہ.بایاں) {
                            نشانہ.دایاں -= 1;
                        }
                        إذا (نشانہ.چوٹی < نشانہ.bottom) {
                            نشانہ.چوٹی += 1;
                        }
                        إذا (نشانہ.bottom > نشانہ.چوٹی) {
                            نشانہ.bottom -= 1;
                        }
                    }
                }
            }
            videodata->سیٹ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    إذا (GetClipCursor(&client) &&
        0 != SDL_memcmp(&نشانہ, &client, حجم(client)) &&
        ClipCursor(&نشانہ)) {
        انکڑے->cursor_clipped_rect = نشانہ; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع false;
#وإلا
    ثابت SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

    إذا (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        إذا (style & WS_EX_LAYERED) {
            إذا (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                أرجع WIN_سیٹ_Error("SetWindowLong()");
            }
        }
    } وإلا {
        ثابت BYTE alpha = (BYTE)((صحيح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        إذا (!(style & WS_EX_LAYERED)) {
            إذا (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                أرجع WIN_سیٹ_Error("SetWindowLong()");
            }
        }

        إذا (سیٹ_Layered_کھڑکی_گن(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            أرجع WIN_سیٹ_Error("SetLayeredWindowAttributes()");
        }
    }

    أرجع true;
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

ساكن STDMETHODIMP_(ULONG) SDLDrop_نشانہ_جوڑو_Ref(SDLDrop_نشانہ *نشانہ)
{
    أرجع ++نشانہ->refcount;
}

ساكن STDMETHODIMP_(ULONG) SDLDrop_نشانہ_Release(SDLDrop_نشانہ *نشانہ)
{
    --نشانہ->refcount;
    إذا (نشانہ->refcount == 0) {
        SDL_free(نشانہ);
        أرجع 0;
    }
    أرجع نشانہ->refcount;
}

ساكن STDMETHODIMP SDLDrop_نشانہ_Query_Interface(SDLDrop_نشانہ *نشانہ, REFIID riid, PVOID *ppv)
{
    إذا (ppv == عدم) {
        أرجع E_INVALIDARG;
    }

    *ppv = عدم;
    إذا (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_نشانہ)) {
        *ppv = (فراغ *)نشانہ;
    }
    إذا (*ppv) {
        SDLDrop_نشانہ_جوڑو_Ref(نشانہ);
        أرجع S_OK;
    }
    أرجع E_NOINTERFACE;
}

ساكن STDMETHODIMP SDLDrop_نشانہ_Drag_Enter(SDLDrop_نشانہ *نشانہ,
                                            IDataObject *p_انکڑے_Object, DWORD grf_کلید_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(نشانہ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, نشانہ->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(نشانہ->کھڑکی, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_نشانہ_Drag_Over(SDLDrop_نشانہ *نشانہ,
                                           DWORD grf_کلید_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(نشانہ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, نشانہ->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(نشانہ->کھڑکی, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_نشانہ_Drag_Leave(SDLDrop_نشانہ *نشانہ)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragLeave");
    SDL_SendDropComplete(نشانہ->کھڑکی);
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_نشانہ_Drop(SDLDrop_نشانہ *نشانہ,
                                       IDataObject *p_انکڑے_Object, DWORD grf_کلید_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(نشانہ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, نشانہ->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(نشانہ->کھڑکی, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_انکڑے_Object->lpVtbl->EnumFormatEtc(p_انکڑے_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        إذا (hres == S_OK) {
            FORMATETC fetc;
            طالما (pEnumFormatEtc->lpVtbl->اگلا_3(pEnumFormatEtc, 1, &fetc, عدم) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                إذا (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وإلا {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = نشانہ->format_file;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/uri-list";
        إذا (SUCCEEDED(p_انکڑے_Object->lpVtbl->Query_Get_انکڑے(p_انکڑے_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_انکڑے_Object->lpVtbl->Get_انکڑے(p_انکڑے_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_ناپ(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_جندرا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشانی لما)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بنانشانی لما)SDL_strlen(token), (بنانشانی لما)bsize, token);
                            SDL_SendDropFile(نشانہ->کھڑکی, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(نشانہ->کھڑکی);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = نشانہ->format_متن;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/plain;charset=utf-8";
        إذا (SUCCEEDED(p_انکڑے_Object->lpVtbl->Query_Get_انکڑے(p_انکڑے_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_انکڑے_Object->lpVtbl->Get_انکڑے(p_انکڑے_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_ناپ(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_جندرا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشانی لما)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بنانشانی لما)SDL_strlen(token), (بنانشانی لما)bsize, token);
                        SDL_Send_Drop_متن(نشانہ->کھڑکی, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(نشانہ->کھڑکی);
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
        إذا (SUCCEEDED(p_انکڑے_Object->lpVtbl->Query_Get_انکڑے(p_انکڑے_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_انکڑے_Object->lpVtbl->Get_انکڑے(p_انکڑے_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_ناپ(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_جندرا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشانی لما)bsize, بفر_2);
                إذا (بفر_2) {
                    بفر_2 = WIN_String_منزل_UTF8_W((ثابت wchar_t *)بفر_2);
                    إذا (بفر_2) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)بفر_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (بنانشانی لما)lbuffer, بفر_2);
                        حرف *متن = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)متن, بفر_2, lbuffer);
                        SDL_memset((Uint8 *)متن + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = عدم;
                        حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                        طالما (token != عدم) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (بنانشانی لما)SDL_strlen(token), (بنانشانی لما)lbuffer, token);
                            SDL_Send_Drop_متن(نشانہ->کھڑکی, (حرف *)token);
                            token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                        }
                        SDL_free(متن);
                        SDL_free((فراغ *)بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(نشانہ->کھڑکی);
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
        إذا (SUCCEEDED(p_انکڑے_Object->lpVtbl->Query_Get_انکڑے(p_انکڑے_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_انکڑے_Object->lpVtbl->Get_انکڑے(p_انکڑے_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_ناپ(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_جندرا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشانی لما)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بنانشانی لما)SDL_strlen(token), (بنانشانی لما)bsize, token);
                        SDL_Send_Drop_متن(نشانہ->کھڑکی, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(نشانہ->کھڑکی);
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
        إذا (SUCCEEDED(p_انکڑے_Object->lpVtbl->Query_Get_انکڑے(p_انکڑے_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_انکڑے_Object->lpVtbl->Get_انکڑے(p_انکڑے_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_ناپ(med.hGlobal);
                HDROP drop = (HDROP)Global_جندرا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشانی لما)bsize, drop);
                UINT گنتی = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
                لكل (UINT i = 0; i < گنتی; ++i) {
                    UINT ناپ = DragQueryFile(drop, i, عدم, 0) + 1;
                    LPTSTR بفر_2 = (LPTSTR)SDL_malloc(ناپ * حجم(TCHAR));
                    إذا (بفر_2) {
                        إذا (DragQueryFile(drop, i, بفر_2, ناپ)) {
                            حرف *file = WIN_String_منزل_UTF8(بفر_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بنانشانی لما)SDL_strlen(file), (بنانشانی لما)bsize, file);
                            SDL_SendDropFile(نشانہ->کھڑکی, عدم, file);
                            SDL_free(file);
                        }
                        SDL_free(بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(نشانہ->کھڑکی);
                أرجع S_OK;
            }
        }
    }

    SDL_SendDropComplete(نشانہ->کھڑکی);
    أرجع S_OK;
}

ساكن فراغ *vt_Drop_نشانہ[] = {
    (فراغ *)(SDLDrop_نشانہ_Query_Interface),
    (فراغ *)(SDLDrop_نشانہ_جوڑو_Ref),
    (فراغ *)(SDLDrop_نشانہ_Release),
    (فراغ *)(SDLDrop_نشانہ_Drag_Enter),
    (فراغ *)(SDLDrop_نشانہ_Drag_Over),
    (فراغ *)(SDLDrop_نشانہ_Drag_Leave),
    (فراغ *)(SDLDrop_نشانہ_Drop)
};

فراغ WIN_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    إذا (انکڑے->videodata->oleinitialized) {
        إذا (accept && !انکڑے->drop_نشانہ) {
            SDLDrop_نشانہ *drop_نشانہ = (SDLDrop_نشانہ *)SDL_calloc(1, حجم(SDLDrop_نشانہ));
            إذا (drop_نشانہ != عدم) {
                drop_نشانہ->lpVtbl = vt_Drop_نشانہ;
                drop_نشانہ->کھڑکی = کھڑکی;
                drop_نشانہ->hwnd = انکڑے->hwnd;
                drop_نشانہ->format_file = رجسٹر_Clipboard_Format_W(L"text/uri-list");
                drop_نشانہ->format_متن = رجسٹر_Clipboard_Format_W(L"text/plain;charset=utf-8");
                انکڑے->drop_نشانہ = drop_نشانہ;
                SDLDrop_نشانہ_جوڑو_Ref(drop_نشانہ);
                رجسٹر_Drag_Drop(انکڑے->hwnd, (LPDROPTARGET)drop_نشانہ);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             کھڑکی->id);
            }
        } وإلا إذا (!accept && انکڑے->drop_نشانہ) {
            RevokeDragDrop(انکڑے->hwnd);
            SDLDrop_نشانہ_Release(انکڑے->drop_نشانہ);
            انکڑے->drop_نشانہ = عدم;
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         کھڑکی->id);
        }
    } وإلا {
        DragAcceptFiles(انکڑے->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     کھڑکی->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_ناپ = حجم(desc);
    desc.hwnd = کھڑکی->اندرونی->hwnd;
    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_گنتی = 1;
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        اكسر;
    افتراضي:
        أرجع SDL_Unsupported();
    }

    Flash_کھڑکی_Ex(&desc);

    أرجع true;
}

bool WIN_Apply_کھڑکی_ترقی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    إذا (!انکڑے->taskbar_button_created) {
        أرجع true;
    }

    إذا (کھڑکی->ترقی_state == SDL_ترقی_STATE_NONE && !انکڑے->videodata->taskbar_list) {
        أرجع true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(کھڑکی);
    إذا (!taskbar_list) {
        أرجع false;
    }

    TBPFLAG tbpFlags;
    بدل (کھڑکی->ترقی_state) {
    حالة SDL_ترقی_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        اكسر;
    حالة SDL_ترقی_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        اكسر;
    حالة SDL_ترقی_STATE_عام:
        tbpFlags = TBPF_عام;
        اكسر;
    حالة SDL_ترقی_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        اكسر;
    حالة SDL_ترقی_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        اكسر;
    افتراضي:
        أرجع SDL_سیٹ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->سیٹ_ترقی_State(taskbar_list, انکڑے->hwnd, tbpFlags);
    إذا (FAILED(ret)) {
        أرجع WIN_سیٹ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    إذا (کھڑکی->ترقی_state >= SDL_ترقی_STATE_عام) {
        ret = taskbar_list->lpVtbl->سیٹ_ترقی_قدر(taskbar_list, انکڑے->hwnd, (ULONGLONG)(کھڑکی->ترقی_قدر * 10000.f), 10000);
        إذا (FAILED(ret)) {
            أرجع WIN_سیٹ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#جے_انت
    أرجع true;
}

فراغ WIN_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y)
{
    ثابت SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    نقطہ_2 pt;

    pt.x = x;
    pt.y = y;
    Client_منزل_Screen(انکڑے->hwnd, &pt);
    Send_سنیہا(انکڑے->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
        HWND hwnd = انکڑے->hwnd;
        ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        إذا (focusable) {
            إذا (style & WS_EX_NOACTIVATE) {
                إذا (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سیٹ_Error("SetWindowLong()");
                }
            }
        } وإلا {
            إذا (!(style & WS_EX_NOACTIVATE)) {
                إذا (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سیٹ_Error("SetWindowLong()");
                }
            }
        }
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            إذا (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                WIN_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کھڑکی)) {
                    WIN_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_انکڑے *بچہ_انکڑے = کھڑکی->اندرونی;
    ثابت LONG_PTR ماپا_hwnd = (LONG_PTR)(ماپا ? ماپا->اندرونی->hwnd : عدم);
    ثابت DWORD style = Get_کھڑکی_Long(بچہ_انکڑے->hwnd, GWL_STYLE);

    إذا (!(style & WS_بچہ)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        سیٹ_کھڑکی_Long_Ptr(بچہ_انکڑے->hwnd, GWLP_HWNDPARENT, ماپا_hwnd);
    } وإلا {
        سیٹ_ماپا(بچہ_انکڑے->hwnd, (HWND)ماپا_hwnd);
    }
#جے_انت /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    أرجع true;
}

bool WIN_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND ماپا_hwnd = کھڑکی->ماپا->اندرونی->hwnd;

    إذا (modal) {
        // Disable the parent window.
        Enable_کھڑکی(ماپا_hwnd, FALSE);
    } وإلا إذا (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
        // Re-enable the parent window
        Enable_کھڑکی(ماپا_hwnd, TRUE);
    }
#جے_انت // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS
