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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS

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
#جيڪڏهن_پورو

// Windows CE compatibility
#جيڪڏهن_وصف_نه_ٿيل SWP_NOCOPYBITS
#وصف_ڪريو SWP_NOCOPYBITS 0
#جيڪڏهن_پورو

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#جيڪڏهن_وصف_نه_ٿيل WM_POPUPSYSTEMMENU
#وصف_ڪريو WM_POPUPSYSTEMMENU 0x313
#جيڪڏهن_پورو

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

#وصف_ڪريو STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#وصف_ڪريو STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#وصف_ڪريو STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#وصف_ڪريو STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#وصف_ڪريو STYLE_عام              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#وصف_ڪريو STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#وصف_ڪريو STYLE_نقاب                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_عام | STYLE_RESIZABLE)

ساكن DWORD Get_دري_Style(SDL_دري *دري)
{
    DWORD style = 0;

    إذا (SDL_دري_IS_POPUP(دري)) {
        style |= WS_POPUP;
    } وإلا إذا (دري->flags & SDL_دري_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وإلا {
        إذا (دري->flags & SDL_دري_BORDERLESS) {
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
        إذا (دري->flags & SDL_دري_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            إذا (!(دري->flags & SDL_دري_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        إذا (دري->اندروني && دري->اندروني->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        إذا (دري->flags & SDL_دري_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    أرجع style;
}

ساكن DWORD Get_دري_Style_Ex(SDL_دري *دري)
{
    DWORD style = 0;

    إذا (SDL_دري_IS_POPUP(دري) || (دري->flags & SDL_دري_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    إذا (SDL_دري_IS_POPUP(دري) || (دري->flags & SDL_دري_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    أرجع style;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن ITaskbarList3 *GetTaskbarList(SDL_دري *دري)
{
    ثابت SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_assert(معلومات->taskbar_button_created);
    إذا (!معلومات->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, عدم, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&معلومات->videodata->taskbar_list);
        إذا (FAILED(ret)) {
            WIN_سيٽ_Error_From_HRESULT("Unable to create taskbar list", ret);
            أرجع عدم;
        }
        ITaskbarList3 *taskbarlist = معلومات->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        إذا (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            معلومات->videodata->taskbar_list = عدم;
            WIN_سيٽ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            أرجع عدم;
        }
    }
    أرجع معلومات->videodata->taskbar_list;
}
#جيڪڏهن_پورو

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساكن bool WIN_Adjust_دري_Rect_With_Style(SDL_دري *دري, DWORD style, DWORD styleEx, BOOL menu, صحيح *x, صحيح *y, صحيح *ويڪر, صحيح *اوچائي, SDL_دري_Rect rect_type)
{
    SDL_Video_معلومات *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->اندروني : عدم;
    RECT rect;

    // Client rect, in points
    بدل (rect_type) {
    حالة SDL_WINDOWRECT_CURRENT:
        SDL_Relative_منزل_Global_For_دري(دري, دري->x, دري->y, x, y);
        *ويڪر = دري->w;
        *اوچائي = دري->h;
        اكسر;
    حالة SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_منزل_Global_For_دري(دري, دري->windowed.x, دري->windowed.y, x, y);
        *ويڪر = دري->windowed.w;
        *اوچائي = دري->windowed.h;
        اكسر;
    حالة SDL_WINDOWRECT_FLOATING:
        SDL_Relative_منزل_Global_For_دري(دري, دري->floating.x, دري->floating.y, x, y);
        *ويڪر = دري->floating.w;
        *اوچائي = دري->floating.h;
        اكسر;
    حالة SDL_WINDOWRECT_PENDING:
        SDL_Relative_منزل_Global_For_دري(دري, دري->pending.x, دري->pending.y, x, y);
        *ويڪر = دري->pending.w;
        *اوچائي = دري->pending.h;
        اكسر;
    افتراضي:
        // Should never be here
        SDL_assert_release(false);
        *ويڪر = 0;
        *اوچائي = 0;
        اكسر;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.کاٻو = 0;
    rect.چوٽي = 0;
    rect.ساڄو = *ويڪر;
    rect.bottom = *اوچائي;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    إذا (!(دري->flags & SDL_دري_BORDERLESS) && !SDL_دري_IS_POPUP(دري)) {
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_دري_Rect_Ex(&rect, style, menu, 0);
#وإلا
        إذا (WIN_Is_في_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            إذا (videodata) {
                UINT چوکٺو_dpi;
                SDL_دري_معلومات *معلومات = دري->اندروني;
                چوکٺو_dpi = (معلومات && videodata->Get_Dpi_For_دري) ? videodata->Get_Dpi_For_دري(معلومات->hwnd) : USER_DEFAULT_SCREEN_DPI;
                إذا (videodata->Adjust_دري_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, چوکٺو_dpi) == 0) {
                    أرجع WIN_سيٽ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } وإلا {
            إذا (Adjust_دري_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                أرجع WIN_سيٽ_Error("AdjustWindowRectEx()");
            }
        }
#جيڪڏهن_پورو
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.کاٻو;
    *y += rect.چوٽي;
    *ويڪر = (rect.ساڄو - rect.کاٻو);
    *اوچائي = (rect.bottom - rect.چوٽي);

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? دري->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? دري->windowed.x : دري->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? دري->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? دري->windowed.y : دري->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? دري->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? دري->windowed.w : دري->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? دري->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? دري->windowed.h : دري->h),
            *x, *y, *ويڪر, *اوچائي, چوکٺو_dpi);
#جيڪڏهن_پورو
    أرجع true;
}

bool WIN_Adjust_دري_Rect(SDL_دري *دري, صحيح *x, صحيح *y, صحيح *ويڪر, صحيح *اوچائي, SDL_دري_Rect rect_type)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_دري_Long(hwnd, GWL_STYLE);
    styleEx = Get_دري_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#جيڪڏهن_پورو
    أرجع WIN_Adjust_دري_Rect_With_Style(دري, style, styleEx, menu, x, y, ويڪر, اوچائي, rect_type);
}

bool WIN_Adjust_دري_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکٺو_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_معلومات *videodata = videodevice ? videodevice->اندروني : عدم;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_دري_Long(hwnd, GWL_STYLE);
    styleEx = Get_دري_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#جيڪڏهن_پورو

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_دري_Rect_Ex(lpRect, style, menu, styleEx);
#وإلا
    إذا (WIN_Is_في_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        إذا (!چوکٺو_dpi) {
            چوکٺو_dpi = videodata->Get_Dpi_For_دري ? videodata->Get_Dpi_For_دري(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        إذا (!videodata->Adjust_دري_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, چوکٺو_dpi)) {
            أرجع WIN_سيٽ_Error("AdjustWindowRectExForDpi()");
        }
    } وإلا {
        إذا (!Adjust_دري_Rect_Ex(lpRect, style, menu, styleEx)) {
            أرجع WIN_سيٽ_Error("AdjustWindowRectEx()");
        }
    }
#جيڪڏهن_پورو
    أرجع true;
}

bool WIN_سيٽ_دري_Position_اندروني(SDL_دري *دري, UINT flags, SDL_دري_Rect rect_type)
{
    SDL_دري *ٻار_دري;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    HWND چوٽي;
    صحيح x, y;
    صحيح w, h;
    bool نتيجو = true;

    // Figure out what the window area will be
    إذا (SDL_ShouldAllowTopmost() && (دري->flags & SDL_دري_ALWAYS_ON_چوٽي)) {
        چوٽي = HWND_TOPMOST;
    } وإلا {
        چوٽي = HWND_NOTOPMOST;
    }

    WIN_Adjust_دري_Rect(دري, &x, &y, &w, &h, rect_type);

    معلومات->expected_resize = !(flags & SWP_NOSIZE);
    إذا (سيٽ_دري_Pos(hwnd, چوٽي, x, y, w, h, flags) == 0) {
        نتيجو = WIN_سيٽ_Error("SetWindowPos()");
    }
    معلومات->expected_resize = false;

    // Update any child windows
    لكل (ٻار_دري = دري->پهريون_ٻار; ٻار_دري; ٻار_دري = ٻار_دري->ايندڙ_sibling) {
        إذا (!ٻار_دري->اندروني) {
            // This child window is not yet fully initialized.
            استمر;
        }
        إذا (!WIN_سيٽ_دري_Position_اندروني(ٻار_دري, flags, SDL_WINDOWRECT_CURRENT)) {
            نتيجو = false;
        }
    }
    أرجع نتيجو;
}

ساكن SDL_دري_Erase_Background_گهڻائي Get_Erase_Background_گهڻائي_Hint(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_گهڻائي);
    إذا (!hint)
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "never"))
        أرجع SDL_ERASEBACKGROUNDMODE_NEVER;

    إذا (SDL_strstr(hint, "initial"))
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "always"))
        أرجع SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحيح گهڻائي = SDL_GetStringInteger(hint, 1);
    إذا (گهڻائي < 0 || گهڻائي > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    أرجع (SDL_دري_Erase_Background_گهڻائي)گهڻائي;
}

ساكن bool تياري_دري_معلومات(SDL_VideoDevice *_this, SDL_دري *دري, HWND hwnd, HWND والد)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_دري_معلومات *معلومات;

    // Allocate the window data
    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }
    معلومات->دري = دري;
    معلومات->hwnd = hwnd;
    معلومات->والد = والد;
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    معلومات->hdc = (HDC)معلومات->hwnd;
#وإلا
    معلومات->hdc = GetDC(hwnd);
#جيڪڏهن_پورو
    معلومات->hinstance = (HINSTANCE)Get_دري_Long_Ptr(hwnd, GWLP_HINSTANCE);
    معلومات->mouse_button_flags = (WPARAM)-1;
    معلومات->آخري_اشارو_update = (LPARAM)-1;
    معلومات->videodata = videodata;
    معلومات->initializing = true;
    معلومات->hint_erase_background_گهڻائي = Get_Erase_Background_گهڻائي_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    معلومات->cursor_ctrlock_rect.کاٻو   = 0 - remote_desktop_adjustment;
    معلومات->cursor_ctrlock_rect.چوٽي    = 0;
    معلومات->cursor_ctrlock_rect.ساڄو  = 1 + remote_desktop_adjustment;
    معلومات->cursor_ctrlock_rect.bottom = 1;
#جيڪڏهن_پورو

    إذا (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        معلومات->copybits_flag = 0;
    } وإلا {
        معلومات->copybits_flag = SWP_NOCOPYBITS;
    }

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", معلومات->scaling_dpi);
#جيڪڏهن_پورو

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    إذا (!سيٽ_Prop(hwnd, متن_2("SDL_WindowData"), معلومات)) {
        ReleaseDC(hwnd, معلومات->hdc);
        SDL_free(معلومات);
        أرجع WIN_سيٽ_Error("SetProp() failed");
    }
#جيڪڏهن_پورو

    دري->اندروني = معلومات;

    // Set up the window proc function
    إذا (دري->flags & SDL_دري_EXTERNAL) {
#جيڪڏهن_وصف_ٿيل GWLP_WNDPROC
        معلومات->wndproc = (WNDPROC)Get_دري_Long_Ptr(hwnd, GWLP_WNDPROC);
        إذا (معلومات->wndproc != WIN_دري_Proc) {
            سيٽ_دري_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_دري_Proc);
        }
#وإلا
        معلومات->wndproc = (WNDPROC)Get_دري_Long(hwnd, GWL_WNDPROC);
        إذا (معلومات->wndproc != WIN_دري_Proc) {
            سيٽ_دري_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_دري_Proc);
        }
#جيڪڏهن_پورو
    } وإلا {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_دري_Long(hwnd, GWL_STYLE);
        إذا (style & WS_VISIBLE) {
            دري->flags &= ~SDL_دري_HIDDEN;
        } وإلا {
            دري->flags |= SDL_دري_HIDDEN;
        }
        إذا (style & WS_POPUP) {
            دري->flags |= SDL_دري_BORDERLESS;
        } وإلا {
            دري->flags &= ~SDL_دري_BORDERLESS;
        }
        إذا (style & WS_THICKFRAME) {
            دري->flags |= SDL_دري_RESIZABLE;
        } وإلا إذا (!(style & WS_POPUP)) {
            دري->flags &= ~SDL_دري_RESIZABLE;
        }
#جيڪڏهن_وصف_ٿيل WS_MAXIMIZE
        إذا (style & WS_MAXIMIZE) {
            دري->flags |= SDL_دري_MAXIMIZED;
        } وإلا
#جيڪڏهن_پورو
        {
            دري->flags &= ~SDL_دري_MAXIMIZED;
        }
#جيڪڏهن_وصف_ٿيل WS_MINIMIZE
        إذا (style & WS_MINIMIZE) {
            دري->flags |= SDL_دري_MINIMIZED;
        } وإلا
#جيڪڏهن_پورو
        {
            دري->flags &= ~SDL_دري_MINIMIZED;
        }
    }
    إذا (!(دري->flags & SDL_دري_MINIMIZED)) {
        RECT rect;
        إذا (GetClientRect(hwnd, &rect) && WIN_دري_Rect_Valid(&rect)) {
            صحيح w = rect.ساڄو;
            صحيح h = rect.bottom;

            إذا (دري->flags & SDL_دري_EXTERNAL) {
                دري->floating.w = دري->windowed.w = دري->w = w;
                دري->floating.h = دري->windowed.h = دري->h = h;
            } وإلا إذا ((دري->windowed.w && دري->windowed.w != w) || (دري->windowed.h && دري->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحيح x, y;
                // Figure out what the window area will be
                WIN_Adjust_دري_Rect(دري, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                معلومات->expected_resize = true;
                سيٽ_دري_Pos(hwnd, عدم, x, y, w, h, معلومات->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                معلومات->expected_resize = false;
            } وإلا {
                دري->w = w;
                دري->h = h;
            }
        }
    }
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!(دري->flags & SDL_دري_MINIMIZED)) {
        نقطو_2 نقطو;
        نقطو.x = 0;
        نقطو.y = 0;
        إذا (Client_منزل_Screen(hwnd, &نقطو)) {
            إذا (دري->flags & SDL_دري_EXTERNAL) {
                دري->floating.x = دري->windowed.x = نقطو.x;
                دري->floating.y = دري->windowed.y = نقطو.y;
            }
            دري->x = نقطو.x;
            دري->y = نقطو.y;
        }
    }

    WIN_Update_دري_ICCProfile(دري, false);
#جيڪڏهن_پورو

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    دري->flags |= SDL_دري_داخلا_FOCUS;
    SDL_سيٽ_Keyboard_Focus(دري);
#وإلا
    إذا (GetFocus() == hwnd) {
        دري->flags |= SDL_دري_داخلا_FOCUS;
        SDL_سيٽ_Keyboard_Focus(دري);
        WIN_UpdateClipCursor(دري);
    }
#جيڪڏهن_پورو

    إذا (دري->flags & SDL_دري_ALWAYS_ON_چوٽي) {
        WIN_سيٽ_دري_Always_On_چوٽي(_this, دري, true);
    } وإلا {
        WIN_سيٽ_دري_Always_On_چوٽي(_this, دري, false);
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    إذا (videodata->رجسٽر_Touch_دري) {
        videodata->رجسٽر_Touch_دري(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#جيڪڏهن_پورو

    إذا (معلومات->والد && !دري->والد) {
        معلومات->destroy_والد_with_دري = true;
    }

    معلومات->initializing = false;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (دري->flags & SDL_دري_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحيح titleLen;
        bool isstack;

        titleLen = Get_دري_متن_ڊيگهائي(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        إذا (title) {
            titleLen = Get_دري_متن(hwnd, title, titleLen + 1);
        } وإلا {
            titleLen = 0;
        }
        إذا (titleLen > 0) {
            دري->title = WIN_String_منزل_UTF8(title);
        }
        إذا (title) {
            SDL_small_free(title, isstack);
        }
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WIN32_HWND_اشارو, معلومات->hwnd);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WIN32_HDC_اشارو, معلومات->hdc);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WIN32_INSTANCE_اشارو, معلومات->hinstance);

    // All done!
    أرجع true;
}

ساكن فراغ Cleanup_دري_معلومات(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (معلومات->drop_هدف) {
            WIN_AcceptDragAndDrop(دري, false);
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
#جيڪڏهن_پورو
        إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
            Destroy_دري(معلومات->hwnd);
            إذا (معلومات->destroy_والد_with_دري && معلومات->والد) {
                Destroy_دري(معلومات->والد);
            }
        } وإلا {
            // Restore any original event handler...
            إذا (معلومات->wndproc) {
#جيڪڏهن_وصف_ٿيل GWLP_WNDPROC
                سيٽ_دري_Long_Ptr(معلومات->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)معلومات->wndproc);
#وإلا
                سيٽ_دري_Long(معلومات->hwnd, GWL_WNDPROC,
                              (LONG_PTR)معلومات->wndproc);
#جيڪڏهن_پورو
            }
        }
        SDL_free(معلومات);
    }
    دري->اندروني = عدم;
}

ساكن فراغ WIN_ConstrainPopup(SDL_دري *دري, bool output_منزل_pending)
{
    // Possibly clamp popup windows to the output borders
    إذا (SDL_دري_IS_POPUP(دري)) {
        SDL_دري *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = دري->آخري_position_pending ? دري->pending.x : دري->floating.x;
        صحيح abs_y = دري->آخري_position_pending ? دري->pending.y : دري->floating.y;
        ثابت صحيح ويڪر = دري->آخري_سائيز_pending ? دري->pending.w : دري->floating.w;
        ثابت صحيح اوچائي = دري->آخري_سائيز_pending ? دري->pending.h : دري->floating.h;
        صحيح وٿي_x = 0, وٿي_y = 0;

        إذا (دري->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = دري->والد; SDL_دري_IS_POPUP(w); w = w->والد) {
                وٿي_x += w->x;
                وٿي_y += w->y;
            }

            وٿي_x += w->x;
            وٿي_y += w->y;
            abs_x += وٿي_x;
            abs_y += وٿي_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_دري(w);
            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + ويڪر > rect.x + rect.w) {
                abs_x -= (abs_x + ويڪر) - (rect.x + rect.w);
            }
            إذا (abs_y + اوچائي > rect.y + rect.h) {
                abs_y -= (abs_y + اوچائي) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            دري->pending.x = abs_x - وٿي_x;
            دري->pending.y = abs_y - وٿي_y;
            دري->pending.w = ويڪر;
            دري->pending.h = اوچائي;
        } وإلا {
            دري->floating.x = abs_x - وٿي_x;
            دري->floating.y = abs_y - وٿي_y;
            دري->floating.w = ويڪر;
            دري->floating.h = اوچائي;
        }
    }
}

ساكن فراغ WIN_سيٽ_Keyboard_Focus(SDL_دري *دري, bool سيٽ_سرگرم_focus)
{
    SDL_دري *toplevel = دري;

    // Find the topmost parent
    طالما (SDL_دري_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = دري;

    إذا (سيٽ_سرگرم_focus && !دري->is_hiding && !دري->is_destroying) {
        SDL_سيٽ_Keyboard_Focus(دري);
    }
}

bool WIN_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    HWND hwnd = (HWND)SDL_Get_اشارو_Property(create_props, SDL_PROP_دري_CREATE_WIN32_HWND_اشارو, SDL_Get_اشارو_Property(create_props, "sdl2-compat.external_window", عدم));
    HWND والد = عدم;
    إذا (hwnd) {
        دري->flags |= SDL_دري_EXTERNAL;

        إذا (!تياري_دري_معلومات(_this, دري, hwnd, والد)) {
            أرجع false;
        }
    } وإلا {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحيح x, y;
        صحيح w, h;

        إذا (دري->flags & SDL_دري_UTILITY) {
            والد = Create_دري(SDL_Appname, متن_2(""), STYLE_BASIC, 0, 0, 32, 32, عدم, عدم, SDL_Instance, عدم);
        } وإلا إذا (دري->والد) {
            والد = دري->والد->اندروني->hwnd;
        }

        style |= Get_دري_Style(دري);
        styleEx |= (DWORD)SDL_Get_عدد_Property(create_props, SDL_PROP_دري_CREATE_WIN32_STYLE_EX_عدد, Get_دري_Style_Ex(دري));

        // Figure out what the window area will be
        WIN_ConstrainPopup(دري, false);
        WIN_Adjust_دري_Rect_With_Style(دري, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_دري_Ex(styleEx, SDL_Appname, متن_2(""), style,
                              x, y, w, h, والد, عدم, SDL_Instance, عدم);
        إذا (!hwnd) {
            أرجع WIN_سيٽ_Error("Couldn't create window");
        }

        WIN_Update_Dark_گهڻائي_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        إذا (!تياري_دري_معلومات(_this, دري, hwnd, والد)) {
            Destroy_دري(hwnd);
            إذا (والد) {
                Destroy_دري(والد);
            }
            أرجع false;
        }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_متن_داخلا(_this, دري);
#جيڪڏهن_پورو

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        سيٽ_دري_Pos(hwnd, عدم, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        إذا (دري->flags & SDL_دري_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            دري->flags &= ~SDL_دري_HIDDEN;
            Show_دري(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    إذا (دري->flags & SDL_دري_TRANSPARENT) {
        إذا (videodata->Dwm_Enable_Blur_Behind_دري) {
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
            videodata->Dwm_Enable_Blur_Behind_دري(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_اشارو_Property(create_props, SDL_PROP_دري_CREATE_WIN32_PIXEL_FORMAT_HWND_اشارو, عدم);
    إذا (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحيح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        إذا (!سيٽ_Pixel_Format(دري->اندروني->hdc, pixel_format, &pfd)) {
            WIN_Destroy_دري(_this, دري);
            أرجع WIN_سيٽ_Error("SetPixelFormat()");
        }
    } وإلا {
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (!(دري->flags & SDL_دري_OPENGL)) {
            أرجع true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_ES2
        إذا ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_معلومات || WIN_GL_UseEGL(_this))
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_WGL
        ) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
            إذا (!WIN_GLES_تياري_دري(_this, دري)) {
                WIN_Destroy_دري(_this, دري);
                أرجع false;
            }
            أرجع true;
#وإلا
            أرجع SDL_سيٽ_Error("Could not create GLES window surface (EGL support not configured)");
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_EGL
        }
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_ES2

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
        إذا (!WIN_GL_تياري_دري(_this, دري)) {
            WIN_Destroy_دري(_this, دري);
            أرجع false;
        }
#وإلا
        أرجع SDL_سيٽ_Error("Could not create GL window (WGL support not configured)");
#جيڪڏهن_پورو
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

فراغ WIN_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = دري->اندروني->hwnd;
    LPTSTR title = WIN_UTF8_منزل_String(دري->title);
    سيٽ_دري_متن(hwnd, title);
    SDL_free(title);
#جيڪڏهن_پورو
}

bool WIN_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    HICON hicon = عدم;
    BYTE *icon_bmp;
    صحيح icon_len, نقاب_len, صف_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool نتيجو = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_وقت_ASSERT(WIN_سيٽ_دري_Icon_استعمال_ڪري_BITMAPINFOHEADER_منزل_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    نقاب_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + نقاب_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    إذا (!icon_bmp) {
        أرجع false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_سائيز = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->bi_ويڪر = SDL_Swap32LE(icon->w);
    bmi->bi_اوچائي = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_ٻٽو_انگ_ڳڻپ = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_سائيز_Image = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->bi_XPels_في_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_في_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_استعمال_ٿيل = SDL_Swap32LE(0);
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
        أرجع SDL_سيٽ_Error("SetWindowIcon() failed, error %08X", (بنانشان صحيح)Get_آخري_Error());
    }

    إذا (معلومات->hicon) {
        DestroyIcon(معلومات->hicon);
    }
    معلومات->hicon = hicon;

    // Set the icon for the window
    Send_پيغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_پيغام(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    أرجع نتيجو;
#وإلا
    أرجع SDL_Unsupported();
#جيڪڏهن_پورو
}

bool WIN_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        إذا (!(دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED))) {
            WIN_ConstrainPopup(دري, true);
            أرجع WIN_سيٽ_دري_Position_اندروني(دري,
                                                 دري->اندروني->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وإلا {
        أرجع SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_ENTER, true);
    }

    أرجع true;
}

فراغ WIN_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (!(دري->flags & (SDL_دري_FULLSCREEN | SDL_دري_MAXIMIZED))) {
        WIN_سيٽ_دري_Position_اندروني(دري, دري->اندروني->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وإلا {
        // Can't resize the window
        دري->آخري_سائيز_pending = false;
    }
}

bool WIN_Get_دري_Borders_سائيز(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = دري->اندروني->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *چوٽي = rcClient.چوٽي;
    *کاٻو = rcClient.کاٻو;
    *bottom = rcClient.bottom;
    *ساڄو = rcClient.ساڄو;

    أرجع true;
#وإلا  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = دري->اندروني->hwnd;
    RECT rcClient, rc_دري;
    نقطو_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    إذا (!GetClientRect(hwnd, &rcClient)) {
        أرجع SDL_سيٽ_Error("GetClientRect() failed, error %08X", (بنانشان صحيح)Get_آخري_Error());
    }

    إذا (!Get_دري_Rect(hwnd, &rc_دري)) {
        أرجع SDL_سيٽ_Error("GetWindowRect() failed, error %08X", (بنانشان صحيح)Get_آخري_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_دري.چوٽي;
    ptDiff.x = rc_دري.کاٻو;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سيٽ_Error("ScreenToClient() failed, error %08X", (بنانشان صحيح)Get_آخري_Error());
    }

    rc_دري.چوٽي = ptDiff.y;
    rc_دري.کاٻو = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_دري.bottom;
    ptDiff.x = rc_دري.ساڄو;

    إذا (!Screen_منزل_Client(hwnd, &ptDiff)) {
        أرجع SDL_سيٽ_Error("ScreenToClient() failed, error %08X", (بنانشان صحيح)Get_آخري_Error());
    }

    rc_دري.bottom = ptDiff.y;
    rc_دري.ساڄو = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *چوٽي = rcClient.چوٽي - rc_دري.چوٽي;
    *کاٻو = rcClient.کاٻو - rc_دري.کاٻو;
    *bottom = rc_دري.bottom - rcClient.bottom;
    *ساڄو = rc_دري.ساڄو - rcClient.ساڄو;

    أرجع true;
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h)
{
    ثابت SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    RECT rect;

    إذا (GetClientRect(hwnd, &rect) && WIN_دري_Rect_Valid(&rect)) {
        *w = rect.ساڄو;
        *h = rect.bottom;
    } وإلا إذا (دري->آخري_pixel_w && دري->آخري_pixel_h) {
        *w = دري->آخري_pixel_w;
        *h = دري->آخري_pixel_h;
    } وإلا {
        // Probably created minimized, use the restored size
        *w = دري->floating.w;
        *h = دري->floating.h;
    }
}

فراغ WIN_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_دري_ACTIVATE_WHEN_SHOWN, true);

    إذا (SDL_دري_IS_POPUP(دري)) {
        // Update our position in case our parent moved while we were hidden
        WIN_سيٽ_دري_Position(_this, دري);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    إذا (دري->pending_flags & SDL_دري_FULLSCREEN) {
        إذا (!(دري->flags & SDL_دري_BORDERLESS)) {
            دري->flags |= SDL_دري_BORDERLESS;
            style = Get_دري_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_نقاب;
            style |= Get_دري_Style(دري);
            سيٽ_دري_Long(hwnd, GWL_STYLE, style);
            دري->flags &= ~SDL_دري_BORDERLESS;
        }
    }
    style = Get_دري_Long(hwnd, GWL_EXSTYLE);
    إذا (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    معلومات->showing_دري = true;
    إذا (bActivate) {
        Show_دري(hwnd, SW_SHOW);
    } وإلا {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        سيٽ_دري_Pos(hwnd, عدم, 0, 0, 0, 0, دري->اندروني->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    معلومات->showing_دري = false;

    إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE) && bActivate) {
        WIN_سيٽ_Keyboard_Focus(دري, true);
    }
    إذا (دري->flags & SDL_دري_MODAL) {
        WIN_سيٽ_دري_Modal(_this, دري, true);
    }
}

فراغ WIN_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    HWND hwnd = دري->اندروني->hwnd;

    إذا (دري->flags & SDL_دري_MODAL) {
        WIN_سيٽ_دري_Modal(_this, دري, false);
    }

    Show_دري(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE)) {
        SDL_دري *new_focus;
        ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(دري, &new_focus);
        WIN_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
    }
}

فراغ WIN_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
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
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_دري_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = عدم;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    إذا (bForce) {
        hCurWnd = Get_Foreground_دري();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_دري_Thread_Process_Id(hCurWnd, عدم);
        Show_دري(hwnd, SW_RESTORE);
        Attach_Thread_داخلا(dwCurID, dwMyID, TRUE);
        سيٽ_دري_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        إذا (!SDL_ShouldAllowTopmost() || !(دري->flags & SDL_دري_ALWAYS_ON_چوٽي)) {
            سيٽ_دري_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    إذا (bActivate) {
        سيٽ_Foreground_دري(hwnd);
        إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE)) {
            WIN_سيٽ_Keyboard_Focus(دري, دري->والد == SDL_GetKeyboardFocus());
        }
    } وإلا {
        سيٽ_دري_Pos(hwnd, HWND_چوٽي, 0, 0, 0, 0, معلومات->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    إذا (bForce) {
        Attach_Thread_داخلا(dwCurID, dwMyID, FALSE);
        سيٽ_Focus(hwnd);
        سيٽ_سرگرم_دري(hwnd);
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        HWND hwnd = معلومات->hwnd;
        معلومات->expected_resize = true;
        Show_دري(hwnd, SW_MAXIMIZE);
        معلومات->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        إذا (دري->max_w || دري->max_h) {
            صحيح fx, fy, fw, fh;

            دري->windowed.w = دري->max_w ? SDL_min(دري->w, دري->max_w) : دري->windowed.w;
            دري->windowed.h = دري->max_h ? SDL_min(دري->h, دري->max_h) : دري->windowed.h;
            WIN_Adjust_دري_Rect(دري, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            معلومات->expected_resize = true;
            سيٽ_دري_Pos(hwnd, HWND_چوٽي, fx, fy, fw, fh, معلومات->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            معلومات->expected_resize = false;
        }
    } وإلا {
        معلومات->windowed_گهڻائي_was_maximized = true;
    }
}

فراغ WIN_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    HWND hwnd = دري->اندروني->hwnd;
    Show_دري(hwnd, SW_MINIMIZE);
}

فراغ WIN_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    style = Get_دري_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_دري_Style(دري);

    معلومات->اندريون_border_change = true;
    سيٽ_دري_Long(hwnd, GWL_STYLE, style);
    WIN_سيٽ_دري_Position_اندروني(دري, معلومات->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    معلومات->اندريون_border_change = false;
}

فراغ WIN_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    DWORD style;

    style = Get_دري_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_دري_Style(دري);

    سيٽ_دري_Long(hwnd, GWL_STYLE, style);
}

فراغ WIN_سيٽ_دري_Always_On_چوٽي(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي)
{
    WIN_سيٽ_دري_Position_اندروني(دري, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

فراغ WIN_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        إذا (!معلومات->showing_دري || دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED)) {
            HWND hwnd = معلومات->hwnd;
            معلومات->expected_resize = true;
            Show_دري(hwnd, SW_RESTORE);
            معلومات->expected_resize = false;
        }
    } وإلا {
        معلومات->windowed_گهڻائي_was_maximized = false;
    }
}

ساكن فراغ WIN_Update_ڪنڊ_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_دري_ڪنڊ_PREFERENCE ڪنڊ_Pref)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *videodata = _this->اندروني;
    إذا (videodata->Dwm_سيٽ_دري_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سيٽ_دري_Attribute(hwnd, DWMWA_دري_ڪنڊ_PREFERENCE, &ڪنڊ_Pref, حجم(ڪنڊ_Pref));
    }
#جيڪڏهن_پورو
}

ساكن فراغ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_معلومات *videodata = _this->اندروني;
    إذا (videodata->Dwm_سيٽ_دري_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سيٽ_دري_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#جيڪڏهن_پورو
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_نتيجو WIN_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_معلومات *displaydata = display->اندروني;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات ? معلومات->hwnd : عدم;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND چوٽي;
    صحيح x, y;
    صحيح w, h;
    bool enterMaximized = false;

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحيح)fullscreen);
#جيڪڏهن_پورو

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    إذا (!(دري->flags & SDL_دري_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (SDL_ShouldAllowTopmost() && (دري->flags & SDL_دري_ALWAYS_ON_چوٽي)) {
        چوٽي = HWND_TOPMOST;
    } وإلا {
        چوٽي = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_سائيز = حجم(MONITORINFO);
    إذا (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_سيٽ_Error("GetMonitorInfo failed");
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_دري_Event(دري, fullscreen ? SDL_EVENT_دري_ENTER_FULLSCREEN : SDL_EVENT_دري_LEAVE_FULLSCREEN, 0, 0);
    style = Get_دري_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_دري_Style(دري);
    styleEx = Get_دري_Long(hwnd, GWL_EXSTYLE);

    إذا (fullscreen) {
        x = minfo.rcMonitor.کاٻو;
        y = minfo.rcMonitor.چوٽي;
        w = minfo.rcMonitor.ساڄو - minfo.rcMonitor.کاٻو;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٽي;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        إذا (style & WS_MAXIMIZE) {
            معلومات->windowed_گهڻائي_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_ڪنڊ_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وإلا {
        BOOL menu;

        WIN_Update_ڪنڊ_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        إذا (معلومات->windowed_گهڻائي_was_maximized && !معلومات->اندريون_دري_deactivation) {
            enterMaximized = true;
            معلومات->disable_move_سائيز_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
        WIN_Adjust_دري_Rect_With_Style(دري, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        معلومات->windowed_گهڻائي_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        إذا (enterMaximized) {
            ثابت SDL_نقطو windowed_نقطو = { دري->windowed.x, دري->windowed.y };
            ثابت SDL_نقطو floating_نقطو = { دري->floating.x, دري->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_Get_Display_For_نقطو(&floating_نقطو);
            ثابت SDL_DisplayID windowed_display = SDL_Get_Display_For_نقطو(&windowed_نقطو);

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
    سيٽ_دري_Long(hwnd, GWL_STYLE, style);
    معلومات->expected_resize = true;
    سيٽ_دري_Pos(hwnd, چوٽي, x, y, w, h, معلومات->copybits_flag | SWP_NOACTIVATE);
    معلومات->expected_resize = false;
    معلومات->disable_move_سائيز_events = false;

    إذا (enterMaximized) {
        WIN_Maximize_دري(_this, دري);
    }

    إذا (!fullscreen && معلومات && معلومات->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_پيغام(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_پيغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)معلومات->hicon);
    }

#جيڪڏهن_وصف_ٿيل HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحيح)fullscreen, x, y, w, h);
#جيڪڏهن_پورو

#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_Update_دري_ICCProfile(SDL_دري *دري, bool send_event)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);

    إذا (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, عدم, عدم, عدم);
        إذا (hdc) {
            WCHAR fileName[MAX_رستو];
            DWORD file_Name_سائيز = SDL_arraysize(fileName);
            إذا (GetICMProfileW(hdc, &file_Name_سائيز, fileName)) {
                // fileNameSize includes '\0' on return
                إذا (!معلومات->ICMFileName ||
                    SDL_wcscmp(معلومات->ICMFileName, fileName) != 0) {
                    SDL_free(معلومات->ICMFileName);
                    معلومات->ICMFileName = SDL_wcsdup(fileName);
                    إذا (send_event) {
                        SDL_Send_دري_Event(دري, SDL_EVENT_دري_ICCPROF_بدليو, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

فراغ *WIN_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    حرف *filename_utf8;
    فراغ *icc_Profile_معلومات = عدم;

    filename_utf8 = WIN_String_منزل_UTF8_W(معلومات->ICMFileName);
    إذا (filename_utf8) {
        icc_Profile_معلومات = SDL_ڀريو_File(filename_utf8, سائيز);
        إذا (!icc_Profile_معلومات) {
            SDL_سيٽ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    أرجع icc_Profile_معلومات;
}

ساكن فراغ WIN_GrabKeyboard(SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
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
    إذا (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_پتو,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        أرجع;
    }

    // Capture a snapshot of the current keyboard state before the hook
    إذا (!GetKeyboardState(معلومات->videodata->pre_hook_ڪنجي_state)) {
        أرجع;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    معلومات->keyboard_hook = سيٽ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

فراغ WIN_UngrabKeyboard(SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات->keyboard_hook) {
        UnhookWindowsHookEx(معلومات->keyboard_hook);
        معلومات->keyboard_hook = عدم;
    }
}

bool WIN_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري)
{
    WIN_UpdateClipCursor(دري);
    أرجع true;
}

bool WIN_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    WIN_UpdateClipCursor(دري);
    أرجع true;
}

bool WIN_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    إذا (grabbed) {
        WIN_GrabKeyboard(دري);
    } وإلا {
        WIN_UngrabKeyboard(دري);
    }

    أرجع true;
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

فراغ WIN_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    Cleanup_دري_معلومات(_this, دري);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_On_دري_Enter(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (!معلومات || !معلومات->hwnd) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (دري->flags & SDL_دري_ALWAYS_ON_چوٽي) {
        WIN_سيٽ_دري_Position_اندروني(دري, معلومات->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساكن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    أرجع GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_منزل_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_منزل_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

فراغ WIN_Unclip_Cursor_For_دري(SDL_دري *دري) {
    SDL_دري_معلومات *معلومات = دري->اندروني;
    RECT rect;
    إذا (GetClipCursor(&rect) && SDL_memcmp(&rect, &معلومات->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(عدم);
        SDL_zero(معلومات->cursor_clipped_rect);
    }
}

فراغ WIN_UpdateClipCursor(SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Video_معلومات *videodata = معلومات->videodata;
    إذا (معلومات->اندريون_title_click || معلومات->focus_click_pending || معلومات->postpone_clipcursor) {
        أرجع;
    }

    SDL_Rect mouse_rect = دري->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (دري->flags & SDL_دري_داخلا_FOCUS);
    bool win_is_grabbed = (دري->flags & SDL_دري_MOUSE_GRABBED);
    bool win_اندريون_relmode = (دري->flags & SDL_دري_MOUSE_RELATIVE_گهڻائي);
    bool cursor_confine = win_اندريون_relmode || win_is_grabbed || win_mouse_rect;

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
            current.کاٻو != videodevice->desktop_bounds.x ||
            current.چوٽي  != videodevice->desktop_bounds.y
        )) {
            نقطو_2 پهريون, ٻيو;
            پهريون.x  = current.کاٻو;
            پهريون.y  = current.چوٽي;
            ٻيو.x = current.ساڄو  - 1;
            ٻيو.y = current.bottom - 1;
            إذا (!Pt_اندريون_Rect(&معلومات->cursor_clipped_rect, پهريون) ||
                !Pt_اندريون_Rect(&معلومات->cursor_clipped_rect, ٻيو)) {
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
    bool تالو_منزل_ctr = (mouse->relative_گهڻائي && mouse->relative_گهڻائي_center);

    RECT client;
    إذا (!GetClientScreenRect(معلومات->hwnd, &client)) {
        أرجع;
    }

    RECT هدف = client;
    إذا (تالو_منزل_ctr) {
        LONG cx = (client.کاٻو + client.ساڄو ) / 2;
        LONG cy = (client.چوٽي  + client.bottom) / 2;
        هدف = معلومات->cursor_ctrlock_rect;
        هدف.کاٻو   += cx;
        هدف.ساڄو  += cx;
        هدف.چوٽي    += cy;
        هدف.bottom += cy;
    } وإلا إذا (win_mouse_rect) {
        RECT custom, overlap;
        custom.کاٻو   = client.کاٻو + mouse_rect.x;
        custom.چوٽي    = client.چوٽي  + mouse_rect.y;
        custom.ساڄو  = client.کاٻو + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.چوٽي  + mouse_rect.y + mouse_rect.h;
        إذا (IntersectRect(&overlap, &client, &custom)) {
            هدف = overlap;
        } وإلا إذا (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_دري(دري);
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
        إذا (videodata->سيٽ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_في_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_دري(معلومات->hwnd, MONITOR_DEFAULTTONEAREST);
            إذا (hmon) {
                UINT hdpi_uint, vdpi_uint;
                إذا (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت عائم scale = (عائم)hdpi_uint / (عائم)USER_DEFAULT_SCREEN_DPI;
                    إذا (scale != SDL_floorf(scale)) {
                        إذا (هدف.کاٻو < هدف.ساڄو) {
                            هدف.کاٻو += 1;
                        }
                        إذا (هدف.ساڄو > هدف.کاٻو) {
                            هدف.ساڄو -= 1;
                        }
                        إذا (هدف.چوٽي < هدف.bottom) {
                            هدف.چوٽي += 1;
                        }
                        إذا (هدف.bottom > هدف.چوٽي) {
                            هدف.bottom -= 1;
                        }
                    }
                }
            }
            videodata->سيٽ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    إذا (GetClipCursor(&client) &&
        0 != SDL_memcmp(&هدف, &client, حجم(client)) &&
        ClipCursor(&هدف)) {
        معلومات->cursor_clipped_rect = هدف; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع false;
#وإلا
    ثابت SDL_دري_معلومات *معلومات = دري->اندروني;
    HWND hwnd = معلومات->hwnd;
    ثابت LONG style = Get_دري_Long(hwnd, GWL_EXSTYLE);

    إذا (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        إذا (style & WS_EX_LAYERED) {
            إذا (سيٽ_دري_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                أرجع WIN_سيٽ_Error("SetWindowLong()");
            }
        }
    } وإلا {
        ثابت BYTE alpha = (BYTE)((صحيح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        إذا (!(style & WS_EX_LAYERED)) {
            إذا (سيٽ_دري_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                أرجع WIN_سيٽ_Error("SetWindowLong()");
            }
        }

        إذا (سيٽ_Layered_دري_خاصيتون(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            أرجع WIN_سيٽ_Error("SetLayeredWindowAttributes()");
        }
    }

    أرجع true;
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

ساكن STDMETHODIMP_(ULONG) SDLDrop_هدف_جوڙيو_Ref(SDLDrop_هدف *هدف)
{
    أرجع ++هدف->refcount;
}

ساكن STDMETHODIMP_(ULONG) SDLDrop_هدف_Release(SDLDrop_هدف *هدف)
{
    --هدف->refcount;
    إذا (هدف->refcount == 0) {
        SDL_free(هدف);
        أرجع 0;
    }
    أرجع هدف->refcount;
}

ساكن STDMETHODIMP SDLDrop_هدف_Query_Interface(SDLDrop_هدف *هدف, REFIID riid, PVOID *ppv)
{
    إذا (ppv == عدم) {
        أرجع E_INVALIDARG;
    }

    *ppv = عدم;
    إذا (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_هدف)) {
        *ppv = (فراغ *)هدف;
    }
    إذا (*ppv) {
        SDLDrop_هدف_جوڙيو_Ref(هدف);
        أرجع S_OK;
    }
    أرجع E_NOINTERFACE;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Enter(SDLDrop_هدف *هدف,
                                            IDataObject *p_معلومات_Object, DWORD grf_ڪنجي_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطو_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->دري->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->دري, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Over(SDLDrop_هدف *هدف,
                                           DWORD grf_ڪنجي_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطو_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->دري->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->دري, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Leave(SDLDrop_هدف *هدف)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In DragLeave");
    SDL_SendDropComplete(هدف->دري);
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drop(SDLDrop_هدف *هدف,
                                       IDataObject *p_معلومات_Object, DWORD grf_ڪنجي_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    نقطو_2 pnt = { pt.x, pt.y };
    إذا (Screen_منزل_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->دري->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->دري, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_معلومات_Object->lpVtbl->EnumFormatEtc(p_معلومات_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        إذا (hres == S_OK) {
            FORMATETC fetc;
            طالما (pEnumFormatEtc->lpVtbl->ايندڙ_3(pEnumFormatEtc, 1, &fetc, عدم) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                إذا (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وإلا {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = هدف->format_file;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/uri-list";
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائيز(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_تالو(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشان ڊگهو)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بنانشان ڊگهو)SDL_strlen(token), (بنانشان ڊگهو)bsize, token);
                            SDL_SendDropFile(هدف->دري, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->دري);
                أرجع S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = هدف->format_متن;
        fetc.ptd = عدم;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/plain;charset=utf-8";
        إذا (SUCCEEDED(p_معلومات_Object->lpVtbl->Query_Get_معلومات(p_معلومات_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائيز(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_تالو(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشان ڊگهو)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بنانشان ڊگهو)SDL_strlen(token), (بنانشان ڊگهو)bsize, token);
                        SDL_Send_Drop_متن(هدف->دري, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->دري);
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
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائيز(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_تالو(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشان ڊگهو)bsize, بفر_2);
                إذا (بفر_2) {
                    بفر_2 = WIN_String_منزل_UTF8_W((ثابت wchar_t *)بفر_2);
                    إذا (بفر_2) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)بفر_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (بنانشان ڊگهو)lbuffer, بفر_2);
                        حرف *متن = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)متن, بفر_2, lbuffer);
                        SDL_memset((Uint8 *)متن + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = عدم;
                        حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                        طالما (token != عدم) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (بنانشان ڊگهو)SDL_strlen(token), (بنانشان ڊگهو)lbuffer, token);
                            SDL_Send_Drop_متن(هدف->دري, (حرف *)token);
                            token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                        }
                        SDL_free(متن);
                        SDL_free((فراغ *)بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->دري);
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
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائيز(med.hGlobal);
                ثابت فراغ *بفر_2 = (فراغ *)Global_تالو(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشان ڊگهو)bsize, بفر_2);
                إذا (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بنانشان ڊگهو)SDL_strlen(token), (بنانشان ڊگهو)bsize, token);
                        SDL_Send_Drop_متن(هدف->دري, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->دري);
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
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_معلومات_Object->lpVtbl->Get_معلومات(p_معلومات_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائيز(med.hGlobal);
                HDROP drop = (HDROP)Global_تالو(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بنانشان ڊگهو)bsize, drop);
                UINT ڳڻپ = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
                لكل (UINT i = 0; i < ڳڻپ; ++i) {
                    UINT سائيز = DragQueryFile(drop, i, عدم, 0) + 1;
                    LPTSTR بفر_2 = (LPTSTR)SDL_malloc(سائيز * حجم(TCHAR));
                    إذا (بفر_2) {
                        إذا (DragQueryFile(drop, i, بفر_2, سائيز)) {
                            حرف *file = WIN_String_منزل_UTF8(بفر_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بنانشان ڊگهو)SDL_strlen(file), (بنانشان ڊگهو)bsize, file);
                            SDL_SendDropFile(هدف->دري, عدم, file);
                            SDL_free(file);
                        }
                        SDL_free(بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->دري);
                أرجع S_OK;
            }
        }
    }

    SDL_SendDropComplete(هدف->دري);
    أرجع S_OK;
}

ساكن فراغ *vt_Drop_هدف[] = {
    (فراغ *)(SDLDrop_هدف_Query_Interface),
    (فراغ *)(SDLDrop_هدف_جوڙيو_Ref),
    (فراغ *)(SDLDrop_هدف_Release),
    (فراغ *)(SDLDrop_هدف_Drag_Enter),
    (فراغ *)(SDLDrop_هدف_Drag_Over),
    (فراغ *)(SDLDrop_هدف_Drag_Leave),
    (فراغ *)(SDLDrop_هدف_Drop)
};

فراغ WIN_AcceptDragAndDrop(SDL_دري *دري, bool accept)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    إذا (معلومات->videodata->oleinitialized) {
        إذا (accept && !معلومات->drop_هدف) {
            SDLDrop_هدف *drop_هدف = (SDLDrop_هدف *)SDL_calloc(1, حجم(SDLDrop_هدف));
            إذا (drop_هدف != عدم) {
                drop_هدف->lpVtbl = vt_Drop_هدف;
                drop_هدف->دري = دري;
                drop_هدف->hwnd = معلومات->hwnd;
                drop_هدف->format_file = رجسٽر_Clipboard_Format_W(L"text/uri-list");
                drop_هدف->format_متن = رجسٽر_Clipboard_Format_W(L"text/plain;charset=utf-8");
                معلومات->drop_هدف = drop_هدف;
                SDLDrop_هدف_جوڙيو_Ref(drop_هدف);
                رجسٽر_Drag_Drop(معلومات->hwnd, (LPDROPTARGET)drop_هدف);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             دري->id);
            }
        } وإلا إذا (!accept && معلومات->drop_هدف) {
            RevokeDragDrop(معلومات->hwnd);
            SDLDrop_هدف_Release(معلومات->drop_هدف);
            معلومات->drop_هدف = عدم;
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         دري->id);
        }
    } وإلا {
        DragAcceptFiles(معلومات->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     دري->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_سائيز = حجم(desc);
    desc.hwnd = دري->اندروني->hwnd;
    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_ڳڻپ = 1;
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        اكسر;
    افتراضي:
        أرجع SDL_Unsupported();
    }

    Flash_دري_Ex(&desc);

    أرجع true;
}

bool WIN_Apply_دري_ترقي(SDL_VideoDevice *_this, SDL_دري *دري)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_دري_معلومات *معلومات = دري->اندروني;
    إذا (!معلومات->taskbar_button_created) {
        أرجع true;
    }

    إذا (دري->ترقي_state == SDL_ترقي_STATE_NONE && !معلومات->videodata->taskbar_list) {
        أرجع true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(دري);
    إذا (!taskbar_list) {
        أرجع false;
    }

    TBPFLAG tbpFlags;
    بدل (دري->ترقي_state) {
    حالة SDL_ترقي_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        اكسر;
    حالة SDL_ترقي_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        اكسر;
    حالة SDL_ترقي_STATE_عام:
        tbpFlags = TBPF_عام;
        اكسر;
    حالة SDL_ترقي_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        اكسر;
    حالة SDL_ترقي_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        اكسر;
    افتراضي:
        أرجع SDL_سيٽ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->سيٽ_ترقي_State(taskbar_list, معلومات->hwnd, tbpFlags);
    إذا (FAILED(ret)) {
        أرجع WIN_سيٽ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    إذا (دري->ترقي_state >= SDL_ترقي_STATE_عام) {
        ret = taskbar_list->lpVtbl->سيٽ_ترقي_قدر(taskbar_list, معلومات->hwnd, (ULONGLONG)(دري->ترقي_قدر * 10000.f), 10000);
        إذا (FAILED(ret)) {
            أرجع WIN_سيٽ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#جيڪڏهن_پورو
    أرجع true;
}

فراغ WIN_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y)
{
    ثابت SDL_دري_معلومات *معلومات = دري->اندروني;
    نقطو_2 pt;

    pt.x = x;
    pt.y = y;
    Client_منزل_Screen(معلومات->hwnd, &pt);
    Send_پيغام(معلومات->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable)
{
    إذا (!SDL_دري_IS_POPUP(دري)) {
        SDL_دري_معلومات *معلومات = دري->اندروني;
        HWND hwnd = معلومات->hwnd;
        ثابت LONG style = Get_دري_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        إذا (focusable) {
            إذا (style & WS_EX_NOACTIVATE) {
                إذا (سيٽ_دري_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سيٽ_Error("SetWindowLong()");
                }
            }
        } وإلا {
            إذا (!(style & WS_EX_NOACTIVATE)) {
                إذا (سيٽ_دري_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_سيٽ_Error("SetWindowLong()");
                }
            }
        }
    } وإلا إذا (دري->flags & SDL_دري_POPUP_MENU) {
        إذا (!(دري->flags & SDL_دري_HIDDEN)) {
            إذا (!focusable && (دري->flags & SDL_دري_داخلا_FOCUS)) {
                SDL_دري *new_focus;
                ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(دري, &new_focus);
                WIN_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(دري)) {
                    WIN_سيٽ_Keyboard_Focus(دري, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_دري_معلومات *ٻار_معلومات = دري->اندروني;
    ثابت LONG_PTR والد_hwnd = (LONG_PTR)(والد ? والد->اندروني->hwnd : عدم);
    ثابت DWORD style = Get_دري_Long(ٻار_معلومات->hwnd, GWL_STYLE);

    إذا (!(style & WS_ٻار)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        سيٽ_دري_Long_Ptr(ٻار_معلومات->hwnd, GWLP_HWNDPARENT, والد_hwnd);
    } وإلا {
        سيٽ_والد(ٻار_معلومات->hwnd, (HWND)والد_hwnd);
    }
#جيڪڏهن_پورو /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    أرجع true;
}

bool WIN_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND والد_hwnd = دري->والد->اندروني->hwnd;

    إذا (modal) {
        // Disable the parent window.
        Enable_دري(والد_hwnd, FALSE);
    } وإلا إذا (!(دري->flags & SDL_دري_HIDDEN)) {
        // Re-enable the parent window
        Enable_دري(والد_hwnd, TRUE);
    }
#جيڪڏهن_پورو // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS
