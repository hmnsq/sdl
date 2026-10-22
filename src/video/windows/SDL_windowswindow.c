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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS

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
#پایان_اگر

// Windows CE compatibility
#اگر_تعریف_نشده SWP_NOCOPYBITS
#تعریف_کن SWP_NOCOPYBITS 0
#پایان_اگر

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#اگر_تعریف_نشده WM_POPUPSYSTEMMENU
#تعریف_کن WM_POPUPSYSTEMMENU 0x313
#پایان_اگر

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

#تعریف_کن STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#تعریف_کن STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کن STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#تعریف_کن STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کن STYLE_نرمال              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کن STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#تعریف_کن STYLE_ماسک                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_نرمال | STYLE_RESIZABLE)

ساكن DWORD Get_پنجره_Style(SDL_پنجره *پنجره)
{
    DWORD style = 0;

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        style |= WS_POPUP;
    } وإلا إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } وإلا {
        إذا (پنجره->flags & SDL_پنجره_BORDERLESS) {
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
            style |= STYLE_نرمال;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        إذا (پنجره->flags & SDL_پنجره_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            إذا (!(پنجره->flags & SDL_پنجره_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        إذا (پنجره->داخلی && پنجره->داخلی->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    أرجع style;
}

ساكن DWORD Get_پنجره_Style_Ex(SDL_پنجره *پنجره)
{
    DWORD style = 0;

    إذا (SDL_پنجره_IS_POPUP(پنجره) || (پنجره->flags & SDL_پنجره_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    إذا (SDL_پنجره_IS_POPUP(پنجره) || (پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    أرجع style;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساكن ITaskbarList3 *GetTaskbarList(SDL_پنجره *پنجره)
{
    ثابت SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_assert(داده->taskbar_button_created);
    إذا (!داده->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, عدم, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&داده->videodata->taskbar_list);
        إذا (FAILED(ret)) {
            WIN_مجموعه_Error_From_HRESULT("Unable to create taskbar list", ret);
            أرجع عدم;
        }
        ITaskbarList3 *taskbarlist = داده->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        إذا (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            داده->videodata->taskbar_list = عدم;
            WIN_مجموعه_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            أرجع عدم;
        }
    }
    أرجع داده->videodata->taskbar_list;
}
#پایان_اگر

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساكن bool WIN_Adjust_پنجره_Rect_With_Style(SDL_پنجره *پنجره, DWORD style, DWORD styleEx, BOOL menu, صحيح *x, صحيح *y, صحيح *عرض, صحيح *ارتفاع, SDL_پنجره_Rect rect_type)
{
    SDL_Video_داده *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->داخلی : عدم;
    RECT rect;

    // Client rect, in points
    بدل (rect_type) {
    حالة SDL_WINDOWRECT_CURRENT:
        SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->x, پنجره->y, x, y);
        *عرض = پنجره->w;
        *ارتفاع = پنجره->h;
        اكسر;
    حالة SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->windowed.x, پنجره->windowed.y, x, y);
        *عرض = پنجره->windowed.w;
        *ارتفاع = پنجره->windowed.h;
        اكسر;
    حالة SDL_WINDOWRECT_FLOATING:
        SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->floating.x, پنجره->floating.y, x, y);
        *عرض = پنجره->floating.w;
        *ارتفاع = پنجره->floating.h;
        اكسر;
    حالة SDL_WINDOWRECT_PENDING:
        SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->pending.x, پنجره->pending.y, x, y);
        *عرض = پنجره->pending.w;
        *ارتفاع = پنجره->pending.h;
        اكسر;
    افتراضي:
        // Should never be here
        SDL_assert_release(false);
        *عرض = 0;
        *ارتفاع = 0;
        اكسر;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.چپ = 0;
    rect.بالاترین = 0;
    rect.راست = *عرض;
    rect.bottom = *ارتفاع;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    إذا (!(پنجره->flags & SDL_پنجره_BORDERLESS) && !SDL_پنجره_IS_POPUP(پنجره)) {
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_پنجره_Rect_Ex(&rect, style, menu, 0);
#وإلا
        إذا (WIN_Is_در_هر_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            إذا (videodata) {
                UINT قاب_dpi;
                SDL_پنجره_داده *داده = پنجره->داخلی;
                قاب_dpi = (داده && videodata->Get_Dpi_For_پنجره) ? videodata->Get_Dpi_For_پنجره(داده->hwnd) : USER_DEFAULT_SCREEN_DPI;
                إذا (videodata->Adjust_پنجره_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, قاب_dpi) == 0) {
                    أرجع WIN_مجموعه_Error("AdjustWindowRectExForDpi()");
                }
            }
        } وإلا {
            إذا (Adjust_پنجره_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                أرجع WIN_مجموعه_Error("AdjustWindowRectEx()");
            }
        }
#پایان_اگر
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.چپ;
    *y += rect.بالاترین;
    *عرض = (rect.راست - rect.چپ);
    *ارتفاع = (rect.bottom - rect.بالاترین);

#اگر_تعریف_شده HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? پنجره->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? پنجره->windowed.x : پنجره->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? پنجره->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? پنجره->windowed.y : پنجره->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? پنجره->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? پنجره->windowed.w : پنجره->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? پنجره->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? پنجره->windowed.h : پنجره->h),
            *x, *y, *عرض, *ارتفاع, قاب_dpi);
#پایان_اگر
    أرجع true;
}

bool WIN_Adjust_پنجره_Rect(SDL_پنجره *پنجره, صحيح *x, صحيح *y, صحيح *عرض, صحيح *ارتفاع, SDL_پنجره_Rect rect_type)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_پنجره_Long(hwnd, GWL_STYLE);
    styleEx = Get_پنجره_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#پایان_اگر
    أرجع WIN_Adjust_پنجره_Rect_With_Style(پنجره, style, styleEx, menu, x, y, عرض, ارتفاع, rect_type);
}

bool WIN_Adjust_پنجره_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT قاب_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_داده *videodata = videodevice ? videodevice->داخلی : عدم;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_پنجره_Long(hwnd, GWL_STYLE);
    styleEx = Get_پنجره_Long(hwnd, GWL_EXSTYLE);
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#وإلا
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
#پایان_اگر

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_پنجره_Rect_Ex(lpRect, style, menu, styleEx);
#وإلا
    إذا (WIN_Is_در_هر_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        إذا (!قاب_dpi) {
            قاب_dpi = videodata->Get_Dpi_For_پنجره ? videodata->Get_Dpi_For_پنجره(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        إذا (!videodata->Adjust_پنجره_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, قاب_dpi)) {
            أرجع WIN_مجموعه_Error("AdjustWindowRectExForDpi()");
        }
    } وإلا {
        إذا (!Adjust_پنجره_Rect_Ex(lpRect, style, menu, styleEx)) {
            أرجع WIN_مجموعه_Error("AdjustWindowRectEx()");
        }
    }
#پایان_اگر
    أرجع true;
}

bool WIN_مجموعه_پنجره_Position_داخلی(SDL_پنجره *پنجره, UINT flags, SDL_پنجره_Rect rect_type)
{
    SDL_پنجره *فرزند_پنجره;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    HWND بالاترین;
    صحيح x, y;
    صحيح w, h;
    bool نتیجه = true;

    // Figure out what the window area will be
    إذا (SDL_ShouldAllowTopmost() && (پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین)) {
        بالاترین = HWND_TOPMOST;
    } وإلا {
        بالاترین = HWND_NOTOPMOST;
    }

    WIN_Adjust_پنجره_Rect(پنجره, &x, &y, &w, &h, rect_type);

    داده->expected_resize = !(flags & SWP_NOSIZE);
    إذا (مجموعه_پنجره_Pos(hwnd, بالاترین, x, y, w, h, flags) == 0) {
        نتیجه = WIN_مجموعه_Error("SetWindowPos()");
    }
    داده->expected_resize = false;

    // Update any child windows
    لكل (فرزند_پنجره = پنجره->اولی_فرزند; فرزند_پنجره; فرزند_پنجره = فرزند_پنجره->بعدی_sibling) {
        إذا (!فرزند_پنجره->داخلی) {
            // This child window is not yet fully initialized.
            استمر;
        }
        إذا (!WIN_مجموعه_پنجره_Position_داخلی(فرزند_پنجره, flags, SDL_WINDOWRECT_CURRENT)) {
            نتیجه = false;
        }
    }
    أرجع نتیجه;
}

ساكن SDL_پنجره_Erase_Background_نما Get_Erase_Background_نما_Hint(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_نما);
    إذا (!hint)
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "never"))
        أرجع SDL_ERASEBACKGROUNDMODE_NEVER;

    إذا (SDL_strstr(hint, "initial"))
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;

    إذا (SDL_strstr(hint, "always"))
        أرجع SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحيح نما = SDL_GetStringInteger(hint, 1);
    إذا (نما < 0 || نما > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        أرجع SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    أرجع (SDL_پنجره_Erase_Background_نما)نما;
}

ساكن bool راهاندازی_پنجره_داده(SDL_VideoDevice *_this, SDL_پنجره *پنجره, HWND hwnd, HWND والد)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_پنجره_داده *داده;

    // Allocate the window data
    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        أرجع false;
    }
    داده->پنجره = پنجره;
    داده->hwnd = hwnd;
    داده->والد = والد;
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    داده->hdc = (HDC)داده->hwnd;
#وإلا
    داده->hdc = GetDC(hwnd);
#پایان_اگر
    داده->hinstance = (HINSTANCE)Get_پنجره_Long_Ptr(hwnd, GWLP_HINSTANCE);
    داده->mouse_button_flags = (WPARAM)-1;
    داده->آخرین_اشاره_گر_update = (LPARAM)-1;
    داده->videodata = videodata;
    داده->initializing = true;
    داده->hint_erase_background_نما = Get_Erase_Background_نما_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    داده->cursor_ctrlock_rect.چپ   = 0 - remote_desktop_adjustment;
    داده->cursor_ctrlock_rect.بالاترین    = 0;
    داده->cursor_ctrlock_rect.راست  = 1 + remote_desktop_adjustment;
    داده->cursor_ctrlock_rect.bottom = 1;
#پایان_اگر

    إذا (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        داده->copybits_flag = 0;
    } وإلا {
        داده->copybits_flag = SWP_NOCOPYBITS;
    }

#اگر_تعریف_شده HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", داده->scaling_dpi);
#پایان_اگر

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    إذا (!مجموعه_Prop(hwnd, متن_2("SDL_WindowData"), داده)) {
        ReleaseDC(hwnd, داده->hdc);
        SDL_free(داده);
        أرجع WIN_مجموعه_Error("SetProp() failed");
    }
#پایان_اگر

    پنجره->داخلی = داده;

    // Set up the window proc function
    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
#اگر_تعریف_شده GWLP_WNDPROC
        داده->wndproc = (WNDPROC)Get_پنجره_Long_Ptr(hwnd, GWLP_WNDPROC);
        إذا (داده->wndproc != WIN_پنجره_Proc) {
            مجموعه_پنجره_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_پنجره_Proc);
        }
#وإلا
        داده->wndproc = (WNDPROC)Get_پنجره_Long(hwnd, GWL_WNDPROC);
        إذا (داده->wndproc != WIN_پنجره_Proc) {
            مجموعه_پنجره_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_پنجره_Proc);
        }
#پایان_اگر
    } وإلا {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_پنجره_Long(hwnd, GWL_STYLE);
        إذا (style & WS_VISIBLE) {
            پنجره->flags &= ~SDL_پنجره_HIDDEN;
        } وإلا {
            پنجره->flags |= SDL_پنجره_HIDDEN;
        }
        إذا (style & WS_POPUP) {
            پنجره->flags |= SDL_پنجره_BORDERLESS;
        } وإلا {
            پنجره->flags &= ~SDL_پنجره_BORDERLESS;
        }
        إذا (style & WS_THICKFRAME) {
            پنجره->flags |= SDL_پنجره_RESIZABLE;
        } وإلا إذا (!(style & WS_POPUP)) {
            پنجره->flags &= ~SDL_پنجره_RESIZABLE;
        }
#اگر_تعریف_شده WS_MAXIMIZE
        إذا (style & WS_MAXIMIZE) {
            پنجره->flags |= SDL_پنجره_MAXIMIZED;
        } وإلا
#پایان_اگر
        {
            پنجره->flags &= ~SDL_پنجره_MAXIMIZED;
        }
#اگر_تعریف_شده WS_MINIMIZE
        إذا (style & WS_MINIMIZE) {
            پنجره->flags |= SDL_پنجره_MINIMIZED;
        } وإلا
#پایان_اگر
        {
            پنجره->flags &= ~SDL_پنجره_MINIMIZED;
        }
    }
    إذا (!(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        RECT rect;
        إذا (GetClientRect(hwnd, &rect) && WIN_پنجره_Rect_Valid(&rect)) {
            صحيح w = rect.راست;
            صحيح h = rect.bottom;

            إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
                پنجره->floating.w = پنجره->windowed.w = پنجره->w = w;
                پنجره->floating.h = پنجره->windowed.h = پنجره->h = h;
            } وإلا إذا ((پنجره->windowed.w && پنجره->windowed.w != w) || (پنجره->windowed.h && پنجره->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحيح x, y;
                // Figure out what the window area will be
                WIN_Adjust_پنجره_Rect(پنجره, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                داده->expected_resize = true;
                مجموعه_پنجره_Pos(hwnd, عدم, x, y, w, h, داده->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                داده->expected_resize = false;
            } وإلا {
                پنجره->w = w;
                پنجره->h = h;
            }
        }
    }
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (!(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        نقطه_2 نقطه;
        نقطه.x = 0;
        نقطه.y = 0;
        إذا (Client_مقصد_Screen(hwnd, &نقطه)) {
            إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
                پنجره->floating.x = پنجره->windowed.x = نقطه.x;
                پنجره->floating.y = پنجره->windowed.y = نقطه.y;
            }
            پنجره->x = نقطه.x;
            پنجره->y = نقطه.y;
        }
    }

    WIN_Update_پنجره_ICCProfile(پنجره, false);
#پایان_اگر

#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    پنجره->flags |= SDL_پنجره_درون_داد_FOCUS;
    SDL_مجموعه_Keyboard_Focus(پنجره);
#وإلا
    إذا (GetFocus() == hwnd) {
        پنجره->flags |= SDL_پنجره_درون_داد_FOCUS;
        SDL_مجموعه_Keyboard_Focus(پنجره);
        WIN_UpdateClipCursor(پنجره);
    }
#پایان_اگر

    إذا (پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین) {
        WIN_مجموعه_پنجره_Always_On_بالاترین(_this, پنجره, true);
    } وإلا {
        WIN_مجموعه_پنجره_Always_On_بالاترین(_this, پنجره, false);
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    إذا (videodata->ثبات_Touch_پنجره) {
        videodata->ثبات_Touch_پنجره(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#پایان_اگر

    إذا (داده->والد && !پنجره->والد) {
        داده->destroy_والد_with_پنجره = true;
    }

    داده->initializing = false;

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحيح titleLen;
        bool isstack;

        titleLen = Get_پنجره_متن_درازی(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        إذا (title) {
            titleLen = Get_پنجره_متن(hwnd, title, titleLen + 1);
        } وإلا {
            titleLen = 0;
        }
        إذا (titleLen > 0) {
            پنجره->title = WIN_String_مقصد_UTF8(title);
        }
        إذا (title) {
            SDL_small_free(title, isstack);
        }
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WIN32_HWND_اشاره_گر, داده->hwnd);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WIN32_HDC_اشاره_گر, داده->hdc);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WIN32_INSTANCE_اشاره_گر, داده->hinstance);

    // All done!
    أرجع true;
}

ساكن فراغ Cleanup_پنجره_داده(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده) {
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (داده->drop_هدف) {
            WIN_AcceptDragAndDrop(پنجره, false);
        }
        SDL_free(داده->ICMFileName);
        إذا (داده->keyboard_hook) {
            UnhookWindowsHookEx(داده->keyboard_hook);
        }
        إذا (داده->hicon) {
            DestroyIcon(داده->hicon);
        }
        ReleaseDC(داده->hwnd, داده->hdc);
        RemoveProp(داده->hwnd, متن_2("SDL_WindowData"));
#پایان_اگر
        إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
            Destroy_پنجره(داده->hwnd);
            إذا (داده->destroy_والد_with_پنجره && داده->والد) {
                Destroy_پنجره(داده->والد);
            }
        } وإلا {
            // Restore any original event handler...
            إذا (داده->wndproc) {
#اگر_تعریف_شده GWLP_WNDPROC
                مجموعه_پنجره_Long_Ptr(داده->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)داده->wndproc);
#وإلا
                مجموعه_پنجره_Long(داده->hwnd, GWL_WNDPROC,
                              (LONG_PTR)داده->wndproc);
#پایان_اگر
            }
        }
        SDL_free(داده);
    }
    پنجره->داخلی = عدم;
}

ساكن فراغ WIN_ConstrainPopup(SDL_پنجره *پنجره, bool output_مقصد_pending)
{
    // Possibly clamp popup windows to the output borders
    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        SDL_پنجره *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = پنجره->آخرین_position_pending ? پنجره->pending.x : پنجره->floating.x;
        صحيح abs_y = پنجره->آخرین_position_pending ? پنجره->pending.y : پنجره->floating.y;
        ثابت صحيح عرض = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->floating.w;
        ثابت صحيح ارتفاع = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->floating.h;
        صحيح جابه_جایی_x = 0, جابه_جایی_y = 0;

        إذا (پنجره->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = پنجره->والد; SDL_پنجره_IS_POPUP(w); w = w->والد) {
                جابه_جایی_x += w->x;
                جابه_جایی_y += w->y;
            }

            جابه_جایی_x += w->x;
            جابه_جایی_y += w->y;
            abs_x += جابه_جایی_x;
            abs_y += جابه_جایی_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_پنجره(w);
            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + عرض > rect.x + rect.w) {
                abs_x -= (abs_x + عرض) - (rect.x + rect.w);
            }
            إذا (abs_y + ارتفاع > rect.y + rect.h) {
                abs_y -= (abs_y + ارتفاع) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_مقصد_pending) {
            پنجره->pending.x = abs_x - جابه_جایی_x;
            پنجره->pending.y = abs_y - جابه_جایی_y;
            پنجره->pending.w = عرض;
            پنجره->pending.h = ارتفاع;
        } وإلا {
            پنجره->floating.x = abs_x - جابه_جایی_x;
            پنجره->floating.y = abs_y - جابه_جایی_y;
            پنجره->floating.w = عرض;
            پنجره->floating.h = ارتفاع;
        }
    }
}

ساكن فراغ WIN_مجموعه_Keyboard_Focus(SDL_پنجره *پنجره, bool مجموعه_فعال_focus)
{
    SDL_پنجره *toplevel = پنجره;

    // Find the topmost parent
    طالما (SDL_پنجره_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = پنجره;

    إذا (مجموعه_فعال_focus && !پنجره->is_hiding && !پنجره->is_destroying) {
        SDL_مجموعه_Keyboard_Focus(پنجره);
    }
}

bool WIN_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_Video_داده *videodata = _this->داخلی;
    HWND hwnd = (HWND)SDL_Get_اشاره_گر_Property(create_props, SDL_PROP_پنجره_CREATE_WIN32_HWND_اشاره_گر, SDL_Get_اشاره_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    HWND والد = عدم;
    إذا (hwnd) {
        پنجره->flags |= SDL_پنجره_EXTERNAL;

        إذا (!راهاندازی_پنجره_داده(_this, پنجره, hwnd, والد)) {
            أرجع false;
        }
    } وإلا {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحيح x, y;
        صحيح w, h;

        إذا (پنجره->flags & SDL_پنجره_UTILITY) {
            والد = Create_پنجره(SDL_Appname, متن_2(""), STYLE_BASIC, 0, 0, 32, 32, عدم, عدم, SDL_Instance, عدم);
        } وإلا إذا (پنجره->والد) {
            والد = پنجره->والد->داخلی->hwnd;
        }

        style |= Get_پنجره_Style(پنجره);
        styleEx |= (DWORD)SDL_Get_عدد_Property(create_props, SDL_PROP_پنجره_CREATE_WIN32_STYLE_EX_عدد, Get_پنجره_Style_Ex(پنجره));

        // Figure out what the window area will be
        WIN_ConstrainPopup(پنجره, false);
        WIN_Adjust_پنجره_Rect_With_Style(پنجره, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_پنجره_Ex(styleEx, SDL_Appname, متن_2(""), style,
                              x, y, w, h, والد, عدم, SDL_Instance, عدم);
        إذا (!hwnd) {
            أرجع WIN_مجموعه_Error("Couldn't create window");
        }

        WIN_Update_Dark_نما_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        إذا (!راهاندازی_پنجره_داده(_this, پنجره, hwnd, والد)) {
            Destroy_پنجره(hwnd);
            إذا (والد) {
                Destroy_پنجره(والد);
            }
            أرجع false;
        }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_متن_درون_داد(_this, پنجره);
#پایان_اگر

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        مجموعه_پنجره_Pos(hwnd, عدم, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            پنجره->flags &= ~SDL_پنجره_HIDDEN;
            Show_پنجره(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    إذا (پنجره->flags & SDL_پنجره_TRANSPARENT) {
        إذا (videodata->Dwm_Enable_Blur_Behind_پنجره) {
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
            videodata->Dwm_Enable_Blur_Behind_پنجره(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_اشاره_گر_Property(create_props, SDL_PROP_پنجره_CREATE_WIN32_PIXEL_FORMAT_HWND_اشاره_گر, عدم);
    إذا (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحيح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        إذا (!مجموعه_Pixel_Format(پنجره->داخلی->hdc, pixel_format, &pfd)) {
            WIN_Destroy_پنجره(_this, پنجره);
            أرجع WIN_مجموعه_Error("SetPixelFormat()");
        }
    } وإلا {
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        إذا (!(پنجره->flags & SDL_پنجره_OPENGL)) {
            أرجع true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#اگر_تعریف_شده SDL_VIDEO_OPENGL_ES2
        إذا ((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_داده || WIN_GL_UseEGL(_this))
#پایان_اگر // SDL_VIDEO_OPENGL_WGL
        ) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
            إذا (!WIN_GLES_راهاندازی_پنجره(_this, پنجره)) {
                WIN_Destroy_پنجره(_this, پنجره);
                أرجع false;
            }
            أرجع true;
#وإلا
            أرجع SDL_مجموعه_Error("Could not create GLES window surface (EGL support not configured)");
#پایان_اگر // SDL_VIDEO_OPENGL_EGL
        }
#پایان_اگر // SDL_VIDEO_OPENGL_ES2

#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
        إذا (!WIN_GL_راهاندازی_پنجره(_this, پنجره)) {
            WIN_Destroy_پنجره(_this, پنجره);
            أرجع false;
        }
#وإلا
        أرجع SDL_مجموعه_Error("Could not create GL window (WGL support not configured)");
#پایان_اگر
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

فراغ WIN_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = پنجره->داخلی->hwnd;
    LPTSTR title = WIN_UTF8_مقصد_String(پنجره->title);
    مجموعه_پنجره_متن(hwnd, title);
    SDL_free(title);
#پایان_اگر
}

bool WIN_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    HICON hicon = عدم;
    BYTE *icon_bmp;
    صحيح icon_len, ماسک_len, ردیف_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool نتیجه = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_زمان_ASSERT(WIN_مجموعه_پنجره_Icon_استفاده_میکند_BITMAPINFOHEADER_مقصد_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    ماسک_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + ماسک_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    إذا (!icon_bmp) {
        أرجع false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_اندازه = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->bi_عرض = SDL_Swap32LE(icon->w);
    bmi->bi_ارتفاع = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_بیت_شمار = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_اندازه_Image = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->bi_XPels_در_هر_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_در_هر_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_استفاده_شده = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[حجم(BITMAPINFOHEADER)];
    ردیف_len = icon->w * حجم(Uint32);
    y = icon->h;
    طالما (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, ردیف_len);
        dst += ردیف_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - ماسک_len, 0xFF, ماسک_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    إذا (!hicon) {
        أرجع SDL_مجموعه_Error("SetWindowIcon() failed, error %08X", (بیعلامت صحيح)Get_آخرین_Error());
    }

    إذا (داده->hicon) {
        DestroyIcon(داده->hicon);
    }
    داده->hicon = hicon;

    // Set the icon for the window
    Send_پیام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_پیام(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    أرجع نتیجه;
#وإلا
    أرجع SDL_Unsupported();
#پایان_اگر
}

bool WIN_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        إذا (!(پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED))) {
            WIN_ConstrainPopup(پنجره, true);
            أرجع WIN_مجموعه_پنجره_Position_داخلی(پنجره,
                                                 پنجره->داخلی->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } وإلا {
        أرجع SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_ENTER, true);
    }

    أرجع true;
}

فراغ WIN_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (!(پنجره->flags & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED))) {
        WIN_مجموعه_پنجره_Position_داخلی(پنجره, پنجره->داخلی->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } وإلا {
        // Can't resize the window
        پنجره->آخرین_اندازه_pending = false;
    }
}

bool WIN_Get_پنجره_Borders_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *بالاترین, صحيح *چپ, صحيح *bottom, صحيح *راست)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = پنجره->داخلی->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *بالاترین = rcClient.بالاترین;
    *چپ = rcClient.چپ;
    *bottom = rcClient.bottom;
    *راست = rcClient.راست;

    أرجع true;
#وإلا  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = پنجره->داخلی->hwnd;
    RECT rcClient, rc_پنجره;
    نقطه_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    إذا (!GetClientRect(hwnd, &rcClient)) {
        أرجع SDL_مجموعه_Error("GetClientRect() failed, error %08X", (بیعلامت صحيح)Get_آخرین_Error());
    }

    إذا (!Get_پنجره_Rect(hwnd, &rc_پنجره)) {
        أرجع SDL_مجموعه_Error("GetWindowRect() failed, error %08X", (بیعلامت صحيح)Get_آخرین_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_پنجره.بالاترین;
    ptDiff.x = rc_پنجره.چپ;

    إذا (!Screen_مقصد_Client(hwnd, &ptDiff)) {
        أرجع SDL_مجموعه_Error("ScreenToClient() failed, error %08X", (بیعلامت صحيح)Get_آخرین_Error());
    }

    rc_پنجره.بالاترین = ptDiff.y;
    rc_پنجره.چپ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_پنجره.bottom;
    ptDiff.x = rc_پنجره.راست;

    إذا (!Screen_مقصد_Client(hwnd, &ptDiff)) {
        أرجع SDL_مجموعه_Error("ScreenToClient() failed, error %08X", (بیعلامت صحيح)Get_آخرین_Error());
    }

    rc_پنجره.bottom = ptDiff.y;
    rc_پنجره.راست = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *بالاترین = rcClient.بالاترین - rc_پنجره.بالاترین;
    *چپ = rcClient.چپ - rc_پنجره.چپ;
    *bottom = rc_پنجره.bottom - rcClient.bottom;
    *راست = rc_پنجره.راست - rcClient.راست;

    أرجع true;
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    ثابت SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    RECT rect;

    إذا (GetClientRect(hwnd, &rect) && WIN_پنجره_Rect_Valid(&rect)) {
        *w = rect.راست;
        *h = rect.bottom;
    } وإلا إذا (پنجره->آخرین_pixel_w && پنجره->آخرین_pixel_h) {
        *w = پنجره->آخرین_pixel_w;
        *h = پنجره->آخرین_pixel_h;
    } وإلا {
        // Probably created minimized, use the restored size
        *w = پنجره->floating.w;
        *h = پنجره->floating.h;
    }
}

فراغ WIN_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_پنجره_ACTIVATE_WHEN_SHOWN, true);

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        // Update our position in case our parent moved while we were hidden
        WIN_مجموعه_پنجره_Position(_this, پنجره);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    إذا (پنجره->pending_flags & SDL_پنجره_FULLSCREEN) {
        إذا (!(پنجره->flags & SDL_پنجره_BORDERLESS)) {
            پنجره->flags |= SDL_پنجره_BORDERLESS;
            style = Get_پنجره_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_ماسک;
            style |= Get_پنجره_Style(پنجره);
            مجموعه_پنجره_Long(hwnd, GWL_STYLE, style);
            پنجره->flags &= ~SDL_پنجره_BORDERLESS;
        }
    }
    style = Get_پنجره_Long(hwnd, GWL_EXSTYLE);
    إذا (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    داده->showing_پنجره = true;
    إذا (bActivate) {
        Show_پنجره(hwnd, SW_SHOW);
    } وإلا {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        مجموعه_پنجره_Pos(hwnd, عدم, 0, 0, 0, 0, پنجره->داخلی->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    داده->showing_پنجره = false;

    إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE) && bActivate) {
        WIN_مجموعه_Keyboard_Focus(پنجره, true);
    }
    إذا (پنجره->flags & SDL_پنجره_MODAL) {
        WIN_مجموعه_پنجره_Modal(_this, پنجره, true);
    }
}

فراغ WIN_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    HWND hwnd = پنجره->داخلی->hwnd;

    إذا (پنجره->flags & SDL_پنجره_MODAL) {
        WIN_مجموعه_پنجره_Modal(_this, پنجره, false);
    }

    Show_پنجره(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
        SDL_پنجره *new_focus;
        ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(پنجره, &new_focus);
        WIN_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
    }
}

فراغ WIN_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
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
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_پنجره_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = عدم;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    إذا (bForce) {
        hCurWnd = Get_Foreground_پنجره();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_پنجره_Thread_Process_Id(hCurWnd, عدم);
        Show_پنجره(hwnd, SW_RESTORE);
        Attach_Thread_درون_داد(dwCurID, dwMyID, TRUE);
        مجموعه_پنجره_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        إذا (!SDL_ShouldAllowTopmost() || !(پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین)) {
            مجموعه_پنجره_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    إذا (bActivate) {
        مجموعه_Foreground_پنجره(hwnd);
        إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
            WIN_مجموعه_Keyboard_Focus(پنجره, پنجره->والد == SDL_GetKeyboardFocus());
        }
    } وإلا {
        مجموعه_پنجره_Pos(hwnd, HWND_بالاترین, 0, 0, 0, 0, داده->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    إذا (bForce) {
        Attach_Thread_درون_داد(dwCurID, dwMyID, FALSE);
        مجموعه_Focus(hwnd);
        مجموعه_فعال_پنجره(hwnd);
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

فراغ WIN_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        HWND hwnd = داده->hwnd;
        داده->expected_resize = true;
        Show_پنجره(hwnd, SW_MAXIMIZE);
        داده->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        إذا (پنجره->max_w || پنجره->max_h) {
            صحيح fx, fy, fw, fh;

            پنجره->windowed.w = پنجره->max_w ? SDL_min(پنجره->w, پنجره->max_w) : پنجره->windowed.w;
            پنجره->windowed.h = پنجره->max_h ? SDL_min(پنجره->h, پنجره->max_h) : پنجره->windowed.h;
            WIN_Adjust_پنجره_Rect(پنجره, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            داده->expected_resize = true;
            مجموعه_پنجره_Pos(hwnd, HWND_بالاترین, fx, fy, fw, fh, داده->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            داده->expected_resize = false;
        }
    } وإلا {
        داده->windowed_نما_was_maximized = true;
    }
}

فراغ WIN_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    HWND hwnd = پنجره->داخلی->hwnd;
    Show_پنجره(hwnd, SW_MINIMIZE);
}

فراغ WIN_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    DWORD style;

    style = Get_پنجره_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_پنجره_Style(پنجره);

    داده->درون_border_change = true;
    مجموعه_پنجره_Long(hwnd, GWL_STYLE, style);
    WIN_مجموعه_پنجره_Position_داخلی(پنجره, داده->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    داده->درون_border_change = false;
}

فراغ WIN_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    DWORD style;

    style = Get_پنجره_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_پنجره_Style(پنجره);

    مجموعه_پنجره_Long(hwnd, GWL_STYLE, style);
}

فراغ WIN_مجموعه_پنجره_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool on_بالاترین)
{
    WIN_مجموعه_پنجره_Position_داخلی(پنجره, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

فراغ WIN_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        إذا (!داده->showing_پنجره || پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED)) {
            HWND hwnd = داده->hwnd;
            داده->expected_resize = true;
            Show_پنجره(hwnd, SW_RESTORE);
            داده->expected_resize = false;
        }
    } وإلا {
        داده->windowed_نما_was_maximized = false;
    }
}

ساكن فراغ WIN_Update_گوشه_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_پنجره_گوشه_PREFERENCE گوشه_Pref)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *videodata = _this->داخلی;
    إذا (videodata->Dwm_مجموعه_پنجره_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_مجموعه_پنجره_Attribute(hwnd, DWMWA_پنجره_گوشه_PREFERENCE, &گوشه_Pref, حجم(گوشه_Pref));
    }
#پایان_اگر
}

ساكن فراغ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_داده *videodata = _this->داخلی;
    إذا (videodata->Dwm_مجموعه_پنجره_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_مجموعه_پنجره_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#پایان_اگر
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_نتیجه WIN_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_داده *displaydata = display->داخلی;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده ? داده->hwnd : عدم;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND بالاترین;
    صحيح x, y;
    صحيح w, h;
    bool enterMaximized = false;

#اگر_تعریف_شده HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحيح)fullscreen);
#پایان_اگر

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (SDL_ShouldAllowTopmost() && (پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین)) {
        بالاترین = HWND_TOPMOST;
    } وإلا {
        بالاترین = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_اندازه = حجم(MONITORINFO);
    إذا (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_مجموعه_Error("GetMonitorInfo failed");
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_پنجره_Event(پنجره, fullscreen ? SDL_EVENT_پنجره_ENTER_FULLSCREEN : SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
    style = Get_پنجره_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ماسک;
    style |= Get_پنجره_Style(پنجره);
    styleEx = Get_پنجره_Long(hwnd, GWL_EXSTYLE);

    إذا (fullscreen) {
        x = minfo.rcMonitor.چپ;
        y = minfo.rcMonitor.بالاترین;
        w = minfo.rcMonitor.راست - minfo.rcMonitor.چپ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.بالاترین;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        إذا (style & WS_MAXIMIZE) {
            داده->windowed_نما_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_گوشه_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } وإلا {
        BOOL menu;

        WIN_Update_گوشه_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        إذا (داده->windowed_نما_was_maximized && !داده->درون_پنجره_deactivation) {
            enterMaximized = true;
            داده->disable_move_اندازه_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != عدم);
        WIN_Adjust_پنجره_Rect_With_Style(پنجره, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        داده->windowed_نما_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        إذا (enterMaximized) {
            ثابت SDL_نقطه windowed_نقطه = { پنجره->windowed.x, پنجره->windowed.y };
            ثابت SDL_نقطه floating_نقطه = { پنجره->floating.x, پنجره->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_Get_Display_For_نقطه(&floating_نقطه);
            ثابت SDL_DisplayID windowed_display = SDL_Get_Display_For_نقطه(&windowed_نقطه);

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
    مجموعه_پنجره_Long(hwnd, GWL_STYLE, style);
    داده->expected_resize = true;
    مجموعه_پنجره_Pos(hwnd, بالاترین, x, y, w, h, داده->copybits_flag | SWP_NOACTIVATE);
    داده->expected_resize = false;
    داده->disable_move_اندازه_events = false;

    إذا (enterMaximized) {
        WIN_Maximize_پنجره(_this, پنجره);
    }

    إذا (!fullscreen && داده && داده->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_پیام(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_پیام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)داده->hicon);
    }

#اگر_تعریف_شده HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحيح)fullscreen, x, y, w, h);
#پایان_اگر

#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_Update_پنجره_ICCProfile(SDL_پنجره *پنجره, bool send_event)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);

    إذا (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, عدم, عدم, عدم);
        إذا (hdc) {
            WCHAR fileName[MAX_مسیر];
            DWORD file_Name_اندازه = SDL_arraysize(fileName);
            إذا (GetICMProfileW(hdc, &file_Name_اندازه, fileName)) {
                // fileNameSize includes '\0' on return
                إذا (!داده->ICMFileName ||
                    SDL_wcscmp(داده->ICMFileName, fileName) != 0) {
                    SDL_free(داده->ICMFileName);
                    داده->ICMFileName = SDL_wcsdup(fileName);
                    إذا (send_event) {
                        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_ICCPROF_تغییریافته, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

فراغ *WIN_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    حرف *filename_utf8;
    فراغ *icc_Profile_داده = عدم;

    filename_utf8 = WIN_String_مقصد_UTF8_W(داده->ICMFileName);
    إذا (filename_utf8) {
        icc_Profile_داده = SDL_بارگیری_File(filename_utf8, اندازه);
        إذا (!icc_Profile_داده) {
            SDL_مجموعه_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    أرجع icc_Profile_داده;
}

ساكن فراغ WIN_GrabKeyboard(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HMODULE module;

    إذا (داده->keyboard_hook) {
        أرجع;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    إذا (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_آدرس,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        أرجع;
    }

    // Capture a snapshot of the current keyboard state before the hook
    إذا (!GetKeyboardState(داده->videodata->pre_hook_کلید_state)) {
        أرجع;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    داده->keyboard_hook = مجموعه_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

فراغ WIN_UngrabKeyboard(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده->keyboard_hook) {
        UnhookWindowsHookEx(داده->keyboard_hook);
        داده->keyboard_hook = عدم;
    }
}

bool WIN_مجموعه_پنجره_Mouse_Rect(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    WIN_UpdateClipCursor(پنجره);
    أرجع true;
}

bool WIN_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    WIN_UpdateClipCursor(پنجره);
    أرجع true;
}

bool WIN_مجموعه_پنجره_Keyboard_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    إذا (grabbed) {
        WIN_GrabKeyboard(پنجره);
    } وإلا {
        WIN_UngrabKeyboard(پنجره);
    }

    أرجع true;
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

فراغ WIN_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    Cleanup_پنجره_داده(_this, پنجره);
}

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
فراغ WIN_On_پنجره_Enter(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (!داده || !داده->hwnd) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین) {
        WIN_مجموعه_پنجره_Position_داخلی(پنجره, داده->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساكن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    أرجع GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_مقصد_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_مقصد_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

فراغ WIN_Unclip_Cursor_For_پنجره(SDL_پنجره *پنجره) {
    SDL_پنجره_داده *داده = پنجره->داخلی;
    RECT rect;
    إذا (GetClipCursor(&rect) && SDL_memcmp(&rect, &داده->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(عدم);
        SDL_zero(داده->cursor_clipped_rect);
    }
}

فراغ WIN_UpdateClipCursor(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Video_داده *videodata = داده->videodata;
    إذا (داده->درون_title_click || داده->focus_click_pending || داده->postpone_clipcursor) {
        أرجع;
    }

    SDL_Rect mouse_rect = پنجره->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (پنجره->flags & SDL_پنجره_درون_داد_FOCUS);
    bool win_is_grabbed = (پنجره->flags & SDL_پنجره_MOUSE_GRABBED);
    bool win_درون_relmode = (پنجره->flags & SDL_پنجره_MOUSE_RELATIVE_نما);
    bool cursor_confine = win_درون_relmode || win_is_grabbed || win_mouse_rect;

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
            current.چپ != videodevice->desktop_bounds.x ||
            current.بالاترین  != videodevice->desktop_bounds.y
        )) {
            نقطه_2 اولی, دومی;
            اولی.x  = current.چپ;
            اولی.y  = current.بالاترین;
            دومی.x = current.راست  - 1;
            دومی.y = current.bottom - 1;
            إذا (!Pt_درون_Rect(&داده->cursor_clipped_rect, اولی) ||
                !Pt_درون_Rect(&داده->cursor_clipped_rect, دومی)) {
                أرجع;
            }
        }
        ClipCursor(عدم);
        SDL_zero(داده->cursor_clipped_rect);
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
    bool قفل_مقصد_ctr = (mouse->relative_نما && mouse->relative_نما_center);

    RECT client;
    إذا (!GetClientScreenRect(داده->hwnd, &client)) {
        أرجع;
    }

    RECT هدف = client;
    إذا (قفل_مقصد_ctr) {
        LONG cx = (client.چپ + client.راست ) / 2;
        LONG cy = (client.بالاترین  + client.bottom) / 2;
        هدف = داده->cursor_ctrlock_rect;
        هدف.چپ   += cx;
        هدف.راست  += cx;
        هدف.بالاترین    += cy;
        هدف.bottom += cy;
    } وإلا إذا (win_mouse_rect) {
        RECT custom, overlap;
        custom.چپ   = client.چپ + mouse_rect.x;
        custom.بالاترین    = client.بالاترین  + mouse_rect.y;
        custom.راست  = client.چپ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.بالاترین  + mouse_rect.y + mouse_rect.h;
        إذا (IntersectRect(&overlap, &client, &custom)) {
            هدف = overlap;
        } وإلا إذا (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_پنجره(پنجره);
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
        إذا (videodata->مجموعه_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_پنجره(داده->hwnd, MONITOR_DEFAULTTONEAREST);
            إذا (hmon) {
                UINT hdpi_uint, vdpi_uint;
                إذا (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت عائم scale = (عائم)hdpi_uint / (عائم)USER_DEFAULT_SCREEN_DPI;
                    إذا (scale != SDL_floorf(scale)) {
                        إذا (هدف.چپ < هدف.راست) {
                            هدف.چپ += 1;
                        }
                        إذا (هدف.راست > هدف.چپ) {
                            هدف.راست -= 1;
                        }
                        إذا (هدف.بالاترین < هدف.bottom) {
                            هدف.بالاترین += 1;
                        }
                        إذا (هدف.bottom > هدف.بالاترین) {
                            هدف.bottom -= 1;
                        }
                    }
                }
            }
            videodata->مجموعه_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    إذا (GetClipCursor(&client) &&
        0 != SDL_memcmp(&هدف, &client, حجم(client)) &&
        ClipCursor(&هدف)) {
        داده->cursor_clipped_rect = هدف; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity)
{
#إذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    أرجع false;
#وإلا
    ثابت SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    ثابت LONG style = Get_پنجره_Long(hwnd, GWL_EXSTYLE);

    إذا (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        إذا (style & WS_EX_LAYERED) {
            إذا (مجموعه_پنجره_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                أرجع WIN_مجموعه_Error("SetWindowLong()");
            }
        }
    } وإلا {
        ثابت BYTE alpha = (BYTE)((صحيح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        إذا (!(style & WS_EX_LAYERED)) {
            إذا (مجموعه_پنجره_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                أرجع WIN_مجموعه_Error("SetWindowLong()");
            }
        }

        إذا (مجموعه_Layered_پنجره_صفات(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            أرجع WIN_مجموعه_Error("SetLayeredWindowAttributes()");
        }
    }

    أرجع true;
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
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

ساكن STDMETHODIMP_(ULONG) SDLDrop_هدف_جمع_کن_Ref(SDLDrop_هدف *هدف)
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
        SDLDrop_هدف_جمع_کن_Ref(هدف);
        أرجع S_OK;
    }
    أرجع E_NOINTERFACE;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Enter(SDLDrop_هدف *هدف,
                                            IDataObject *p_داده_Object, DWORD grf_کلید_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطه_2 pnt = { pt.x, pt.y };
    إذا (Screen_مقصد_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->پنجره->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->پنجره, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Over(SDLDrop_هدف *هدف,
                                           DWORD grf_کلید_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطه_2 pnt = { pt.x, pt.y };
    إذا (Screen_مقصد_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->پنجره->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->پنجره, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drag_Leave(SDLDrop_هدف *هدف)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In DragLeave");
    SDL_SendDropComplete(هدف->پنجره);
    أرجع S_OK;
}

ساكن STDMETHODIMP SDLDrop_هدف_Drop(SDLDrop_هدف *هدف,
                                       IDataObject *p_داده_Object, DWORD grf_کلید_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    نقطه_2 pnt = { pt.x, pt.y };
    إذا (Screen_مقصد_Client(هدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, هدف->پنجره->id, pnt.x, pnt.y);
        SDL_SendDropPosition(هدف->پنجره, pnt.x, pnt.y);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_داده_Object->lpVtbl->EnumFormatEtc(p_داده_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        إذا (hres == S_OK) {
            FORMATETC fetc;
            طالما (pEnumFormatEtc->lpVtbl->بعدی_3(pEnumFormatEtc, 1, &fetc, عدم) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                إذا (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } وإلا {
                    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
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
        إذا (SUCCEEDED(p_داده_Object->lpVtbl->Query_Get_داده(p_داده_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_داده_Object->lpVtbl->Get_داده(p_داده_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *میانگیر_2 = (فراغ *)Global_قفل(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بیعلامت دراز)bsize, میانگیر_2);
                إذا (میانگیر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, میانگیر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بیعلامت دراز)SDL_strlen(token), (بیعلامت دراز)bsize, token);
                            SDL_SendDropFile(هدف->پنجره, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->پنجره);
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
        إذا (SUCCEEDED(p_داده_Object->lpVtbl->Query_Get_داده(p_داده_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_داده_Object->lpVtbl->Get_داده(p_داده_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *میانگیر_2 = (فراغ *)Global_قفل(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بیعلامت دراز)bsize, میانگیر_2);
                إذا (میانگیر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, میانگیر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بیعلامت دراز)SDL_strlen(token), (بیعلامت دراز)bsize, token);
                        SDL_Send_Drop_متن(هدف->پنجره, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->پنجره);
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
        إذا (SUCCEEDED(p_داده_Object->lpVtbl->Query_Get_داده(p_داده_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_داده_Object->lpVtbl->Get_داده(p_داده_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *میانگیر_2 = (فراغ *)Global_قفل(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بیعلامت دراز)bsize, میانگیر_2);
                إذا (میانگیر_2) {
                    میانگیر_2 = WIN_String_مقصد_UTF8_W((ثابت wchar_t *)میانگیر_2);
                    إذا (میانگیر_2) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)میانگیر_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (بیعلامت دراز)lbuffer, میانگیر_2);
                        حرف *متن = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)متن, میانگیر_2, lbuffer);
                        SDL_memset((Uint8 *)متن + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = عدم;
                        حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                        طالما (token != عدم) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (بیعلامت دراز)SDL_strlen(token), (بیعلامت دراز)lbuffer, token);
                            SDL_Send_Drop_متن(هدف->پنجره, (حرف *)token);
                            token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                        }
                        SDL_free(متن);
                        SDL_free((فراغ *)میانگیر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->پنجره);
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
        إذا (SUCCEEDED(p_داده_Object->lpVtbl->Query_Get_داده(p_داده_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_داده_Object->lpVtbl->Get_داده(p_داده_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                ثابت فراغ *میانگیر_2 = (فراغ *)Global_قفل(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بیعلامت دراز)bsize, میانگیر_2);
                إذا (میانگیر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, میانگیر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    طالما (token != عدم) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (بیعلامت دراز)SDL_strlen(token), (بیعلامت دراز)bsize, token);
                        SDL_Send_Drop_متن(هدف->پنجره, (حرف *)token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->پنجره);
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
        إذا (SUCCEEDED(p_داده_Object->lpVtbl->Query_Get_داده(p_داده_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_داده_Object->lpVtbl->Get_داده(p_داده_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            إذا (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_اندازه(med.hGlobal);
                HDROP drop = (HDROP)Global_قفل(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (بیعلامت دراز)bsize, drop);
                UINT شمار = DragQueryFile(drop, 0xFFFFFFFF, عدم, 0);
                لكل (UINT i = 0; i < شمار; ++i) {
                    UINT اندازه = DragQueryFile(drop, i, عدم, 0) + 1;
                    LPTSTR میانگیر_2 = (LPTSTR)SDL_malloc(اندازه * حجم(TCHAR));
                    إذا (میانگیر_2) {
                        إذا (DragQueryFile(drop, i, میانگیر_2, اندازه)) {
                            حرف *file = WIN_String_مقصد_UTF8(میانگیر_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (بیعلامت دراز)SDL_strlen(file), (بیعلامت دراز)bsize, file);
                            SDL_SendDropFile(هدف->پنجره, عدم, file);
                            SDL_free(file);
                        }
                        SDL_free(میانگیر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(هدف->پنجره);
                أرجع S_OK;
            }
        }
    }

    SDL_SendDropComplete(هدف->پنجره);
    أرجع S_OK;
}

ساكن فراغ *vt_Drop_هدف[] = {
    (فراغ *)(SDLDrop_هدف_Query_Interface),
    (فراغ *)(SDLDrop_هدف_جمع_کن_Ref),
    (فراغ *)(SDLDrop_هدف_Release),
    (فراغ *)(SDLDrop_هدف_Drag_Enter),
    (فراغ *)(SDLDrop_هدف_Drag_Over),
    (فراغ *)(SDLDrop_هدف_Drag_Leave),
    (فراغ *)(SDLDrop_هدف_Drop)
};

فراغ WIN_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    إذا (داده->videodata->oleinitialized) {
        إذا (accept && !داده->drop_هدف) {
            SDLDrop_هدف *drop_هدف = (SDLDrop_هدف *)SDL_calloc(1, حجم(SDLDrop_هدف));
            إذا (drop_هدف != عدم) {
                drop_هدف->lpVtbl = vt_Drop_هدف;
                drop_هدف->پنجره = پنجره;
                drop_هدف->hwnd = داده->hwnd;
                drop_هدف->format_file = ثبات_Clipboard_Format_W(L"text/uri-list");
                drop_هدف->format_متن = ثبات_Clipboard_Format_W(L"text/plain;charset=utf-8");
                داده->drop_هدف = drop_هدف;
                SDLDrop_هدف_جمع_کن_Ref(drop_هدف);
                ثبات_Drag_Drop(داده->hwnd, (LPDROPTARGET)drop_هدف);
                SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             پنجره->id);
            }
        } وإلا إذا (!accept && داده->drop_هدف) {
            RevokeDragDrop(داده->hwnd);
            SDLDrop_هدف_Release(داده->drop_هدف);
            داده->drop_هدف = عدم;
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         پنجره->id);
        }
    } وإلا {
        DragAcceptFiles(داده->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     پنجره->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_اندازه = حجم(desc);
    desc.hwnd = پنجره->داخلی->hwnd;
    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_شمار = 1;
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        اكسر;
    افتراضي:
        أرجع SDL_Unsupported();
    }

    Flash_پنجره_Ex(&desc);

    أرجع true;
}

bool WIN_Apply_پنجره_پیشرفت(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_پنجره_داده *داده = پنجره->داخلی;
    إذا (!داده->taskbar_button_created) {
        أرجع true;
    }

    إذا (پنجره->پیشرفت_state == SDL_پیشرفت_STATE_NONE && !داده->videodata->taskbar_list) {
        أرجع true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(پنجره);
    إذا (!taskbar_list) {
        أرجع false;
    }

    TBPFLAG tbpFlags;
    بدل (پنجره->پیشرفت_state) {
    حالة SDL_پیشرفت_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        اكسر;
    حالة SDL_پیشرفت_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        اكسر;
    حالة SDL_پیشرفت_STATE_نرمال:
        tbpFlags = TBPF_نرمال;
        اكسر;
    حالة SDL_پیشرفت_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        اكسر;
    حالة SDL_پیشرفت_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        اكسر;
    افتراضي:
        أرجع SDL_مجموعه_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->مجموعه_پیشرفت_State(taskbar_list, داده->hwnd, tbpFlags);
    إذا (FAILED(ret)) {
        أرجع WIN_مجموعه_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    إذا (پنجره->پیشرفت_state >= SDL_پیشرفت_STATE_نرمال) {
        ret = taskbar_list->lpVtbl->مجموعه_پیشرفت_مقدار(taskbar_list, داده->hwnd, (ULONGLONG)(پنجره->پیشرفت_مقدار * 10000.f), 10000);
        إذا (FAILED(ret)) {
            أرجع WIN_مجموعه_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#پایان_اگر
    أرجع true;
}

فراغ WIN_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y)
{
    ثابت SDL_پنجره_داده *داده = پنجره->داخلی;
    نقطه_2 pt;

    pt.x = x;
    pt.y = y;
    Client_مقصد_Screen(داده->hwnd, &pt);
    Send_پیام(داده->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable)
{
    إذا (!SDL_پنجره_IS_POPUP(پنجره)) {
        SDL_پنجره_داده *داده = پنجره->داخلی;
        HWND hwnd = داده->hwnd;
        ثابت LONG style = Get_پنجره_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        إذا (focusable) {
            إذا (style & WS_EX_NOACTIVATE) {
                إذا (مجموعه_پنجره_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_مجموعه_Error("SetWindowLong()");
                }
            }
        } وإلا {
            إذا (!(style & WS_EX_NOACTIVATE)) {
                إذا (مجموعه_پنجره_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    أرجع WIN_مجموعه_Error("SetWindowLong()");
                }
            }
        }
    } وإلا إذا (پنجره->flags & SDL_پنجره_POPUP_MENU) {
        إذا (!(پنجره->flags & SDL_پنجره_HIDDEN)) {
            إذا (!focusable && (پنجره->flags & SDL_پنجره_درون_داد_FOCUS)) {
                SDL_پنجره *new_focus;
                ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(پنجره, &new_focus);
                WIN_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(پنجره)) {
                    WIN_مجموعه_Keyboard_Focus(پنجره, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_پنجره_داده *فرزند_داده = پنجره->داخلی;
    ثابت LONG_PTR والد_hwnd = (LONG_PTR)(والد ? والد->داخلی->hwnd : عدم);
    ثابت DWORD style = Get_پنجره_Long(فرزند_داده->hwnd, GWL_STYLE);

    إذا (!(style & WS_فرزند)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        مجموعه_پنجره_Long_Ptr(فرزند_داده->hwnd, GWLP_HWNDPARENT, والد_hwnd);
    } وإلا {
        مجموعه_والد(فرزند_داده->hwnd, (HWND)والد_hwnd);
    }
#پایان_اگر /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    أرجع true;
}

bool WIN_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal)
{
#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND والد_hwnd = پنجره->والد->داخلی->hwnd;

    إذا (modal) {
        // Disable the parent window.
        Enable_پنجره(والد_hwnd, FALSE);
    } وإلا إذا (!(پنجره->flags & SDL_پنجره_HIDDEN)) {
        // Re-enable the parent window
        Enable_پنجره(والد_hwnd, TRUE);
    }
#پایان_اگر // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS
