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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

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
#اگر_ختم

// Windows CE compatibility
#اگر_غیر_تعریف_شدہ SWP_NOCOPYBITS
#تعریف_کرو SWP_NOCOPYBITS 0
#اگر_ختم

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#اگر_غیر_تعریف_شدہ WM_POPUPSYSTEMMENU
#تعریف_کرو WM_POPUPSYSTEMMENU 0x313
#اگر_ختم

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
#تعریف_کرو STYLE_معمول              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#تعریف_کرو STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#تعریف_کرو STYLE_نقاب                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_معمول | STYLE_RESIZABLE)

ساکن DWORD Get_کھڑکی_Style(SDL_کھڑکی *کھڑکی)
{
    DWORD style = 0;

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        style |= WS_POPUP;
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ورنہ {
        اگر (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            اگر (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ورنہ {
                style |= STYLE_BORDERLESS;
            }
        } ورنہ {
            style |= STYLE_معمول;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        اگر (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            اگر (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        اگر (کھڑکی->اندرونی_2 && کھڑکی->اندرونی_2->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    واپس style;
}

ساکن DWORD Get_کھڑکی_Style_Ex(SDL_کھڑکی *کھڑکی)
{
    DWORD style = 0;

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی) || (کھڑکی->flags & SDL_کھڑکی_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی) || (کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    واپس style;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ساکن ITaskbarList3 *GetTaskbarList(SDL_کھڑکی *کھڑکی)
{
    ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_assert(ڈیٹا->taskbar_button_created);
    اگر (!ڈیٹا->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, تہی, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&ڈیٹا->videodata->taskbar_list);
        اگر (FAILED(ret)) {
            WIN_سیٹ_Error_From_HRESULT("Unable to create taskbar list", ret);
            واپس تہی;
        }
        ITaskbarList3 *taskbarlist = ڈیٹا->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        اگر (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            ڈیٹا->videodata->taskbar_list = تہی;
            WIN_سیٹ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            واپس تہی;
        }
    }
    واپس ڈیٹا->videodata->taskbar_list;
}
#اگر_ختم

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ساکن bool WIN_Adjust_کھڑکی_Rect_With_Style(SDL_کھڑکی *کھڑکی, DWORD style, DWORD styleEx, BOOL menu, صحیح *x, صحیح *y, صحیح *چوڑائی, صحیح *اونچائی, SDL_کھڑکی_Rect rect_type)
{
    SDL_Video_ڈیٹا *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->اندرونی_2 : تہی;
    RECT rect;

    // Client rect, in points
    انتخاب (rect_type) {
    حالت SDL_WINDOWRECT_CURRENT:
        SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, x, y);
        *چوڑائی = کھڑکی->w;
        *اونچائی = کھڑکی->h;
        توڑو;
    حالت SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->windowed.x, کھڑکی->windowed.y, x, y);
        *چوڑائی = کھڑکی->windowed.w;
        *اونچائی = کھڑکی->windowed.h;
        توڑو;
    حالت SDL_WINDOWRECT_FLOATING:
        SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->floating.x, کھڑکی->floating.y, x, y);
        *چوڑائی = کھڑکی->floating.w;
        *اونچائی = کھڑکی->floating.h;
        توڑو;
    حالت SDL_WINDOWRECT_PENDING:
        SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->pending.x, کھڑکی->pending.y, x, y);
        *چوڑائی = کھڑکی->pending.w;
        *اونچائی = کھڑکی->pending.h;
        توڑو;
    طےشدہ:
        // Should never be here
        SDL_assert_release(false);
        *چوڑائی = 0;
        *اونچائی = 0;
        توڑو;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.بایاں = 0;
    rect.چوٹی = 0;
    rect.دایاں = *چوڑائی;
    rect.bottom = *اونچائی;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    اگر (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !SDL_کھڑکی_IS_POPUP(کھڑکی)) {
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_کھڑکی_Rect_Ex(&rect, style, menu, 0);
#ورنہ
        اگر (WIN_Is_فی_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            اگر (videodata) {
                UINT چوکھٹا_dpi;
                SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
                چوکھٹا_dpi = (ڈیٹا && videodata->Get_Dpi_For_کھڑکی) ? videodata->Get_Dpi_For_کھڑکی(ڈیٹا->hwnd) : USER_DEFAULT_SCREEN_DPI;
                اگر (videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, چوکھٹا_dpi) == 0) {
                    واپس WIN_سیٹ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } ورنہ {
            اگر (Adjust_کھڑکی_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                واپس WIN_سیٹ_Error("AdjustWindowRectEx()");
            }
        }
#اگر_ختم
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.بایاں;
    *y += rect.چوٹی;
    *چوڑائی = (rect.دایاں - rect.بایاں);
    *اونچائی = (rect.bottom - rect.چوٹی);

#اگر_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.x : کھڑکی->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.y : کھڑکی->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.w : کھڑکی->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? کھڑکی->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? کھڑکی->windowed.h : کھڑکی->h),
            *x, *y, *چوڑائی, *اونچائی, چوکھٹا_dpi);
#اگر_ختم
    واپس true;
}

bool WIN_Adjust_کھڑکی_Rect(SDL_کھڑکی *کھڑکی, صحیح *x, صحیح *y, صحیح *چوڑائی, صحیح *اونچائی, SDL_کھڑکی_Rect rect_type)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ورنہ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != تہی);
#اگر_ختم
    واپس WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, menu, x, y, چوڑائی, اونچائی, rect_type);
}

bool WIN_Adjust_کھڑکی_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکھٹا_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *videodata = videodevice ? videodevice->اندرونی_2 : تہی;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ورنہ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != تہی);
#اگر_ختم

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_کھڑکی_Rect_Ex(lpRect, style, menu, styleEx);
#ورنہ
    اگر (WIN_Is_فی_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        اگر (!چوکھٹا_dpi) {
            چوکھٹا_dpi = videodata->Get_Dpi_For_کھڑکی ? videodata->Get_Dpi_For_کھڑکی(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        اگر (!videodata->Adjust_کھڑکی_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, چوکھٹا_dpi)) {
            واپس WIN_سیٹ_Error("AdjustWindowRectExForDpi()");
        }
    } ورنہ {
        اگر (!Adjust_کھڑکی_Rect_Ex(lpRect, style, menu, styleEx)) {
            واپس WIN_سیٹ_Error("AdjustWindowRectEx()");
        }
    }
#اگر_ختم
    واپس true;
}

bool WIN_سیٹ_کھڑکی_Position_اندرونی(SDL_کھڑکی *کھڑکی, UINT flags, SDL_کھڑکی_Rect rect_type)
{
    SDL_کھڑکی *بچہ_کھڑکی;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    HWND چوٹی;
    صحیح x, y;
    صحیح w, h;
    bool نتیجہ = true;

    // Figure out what the window area will be
    اگر (SDL_ShouldAllowTopmost() && (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
        چوٹی = HWND_TOPMOST;
    } ورنہ {
        چوٹی = HWND_NOTOPMOST;
    }

    WIN_Adjust_کھڑکی_Rect(کھڑکی, &x, &y, &w, &h, rect_type);

    ڈیٹا->expected_resize = !(flags & SWP_NOSIZE);
    اگر (سیٹ_کھڑکی_Pos(hwnd, چوٹی, x, y, w, h, flags) == 0) {
        نتیجہ = WIN_سیٹ_Error("SetWindowPos()");
    }
    ڈیٹا->expected_resize = false;

    // Update any child windows
    برائے (بچہ_کھڑکی = کھڑکی->پہلا_بچہ; بچہ_کھڑکی; بچہ_کھڑکی = بچہ_کھڑکی->اگلا_sibling) {
        اگر (!بچہ_کھڑکی->اندرونی_2) {
            // This child window is not yet fully initialized.
            جاری;
        }
        اگر (!WIN_سیٹ_کھڑکی_Position_اندرونی(بچہ_کھڑکی, flags, SDL_WINDOWRECT_CURRENT)) {
            نتیجہ = false;
        }
    }
    واپس نتیجہ;
}

ساکن SDL_کھڑکی_Erase_Background_منوال Get_Erase_Background_منوال_Hint(خالی)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_منوال);
    اگر (!hint)
        واپس SDL_ERASEBACKGROUNDMODE_INITIAL;

    اگر (SDL_strstr(hint, "never"))
        واپس SDL_ERASEBACKGROUNDMODE_NEVER;

    اگر (SDL_strstr(hint, "initial"))
        واپس SDL_ERASEBACKGROUNDMODE_INITIAL;

    اگر (SDL_strstr(hint, "always"))
        واپس SDL_ERASEBACKGROUNDMODE_ALWAYS;

    صحیح منوال = SDL_GetStringInteger(hint, 1);
    اگر (منوال < 0 || منوال > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        واپس SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    واپس (SDL_کھڑکی_Erase_Background_منوال)منوال;
}

ساکن bool تیاری_کھڑکی_ڈیٹا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, HWND hwnd, HWND والد)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    // Allocate the window data
    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }
    ڈیٹا->کھڑکی = کھڑکی;
    ڈیٹا->hwnd = hwnd;
    ڈیٹا->والد = والد;
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ڈیٹا->hdc = (HDC)ڈیٹا->hwnd;
#ورنہ
    ڈیٹا->hdc = GetDC(hwnd);
#اگر_ختم
    ڈیٹا->hinstance = (HINSTANCE)Get_کھڑکی_Long_Ptr(hwnd, GWLP_HINSTANCE);
    ڈیٹا->mouse_button_flags = (WPARAM)-1;
    ڈیٹا->آخری_اشارہ_گر_update = (LPARAM)-1;
    ڈیٹا->videodata = videodata;
    ڈیٹا->initializing = true;
    ڈیٹا->hint_erase_background_منوال = Get_Erase_Background_منوال_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    ڈیٹا->cursor_ctrlock_rect.بایاں   = 0 - remote_desktop_adjustment;
    ڈیٹا->cursor_ctrlock_rect.چوٹی    = 0;
    ڈیٹا->cursor_ctrlock_rect.دایاں  = 1 + remote_desktop_adjustment;
    ڈیٹا->cursor_ctrlock_rect.bottom = 1;
#اگر_ختم

    اگر (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        ڈیٹا->copybits_flag = 0;
    } ورنہ {
        ڈیٹا->copybits_flag = SWP_NOCOPYBITS;
    }

#اگر_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", ڈیٹا->scaling_dpi);
#اگر_ختم

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    اگر (!سیٹ_Prop(hwnd, متن_2("SDL_WindowData"), ڈیٹا)) {
        ReleaseDC(hwnd, ڈیٹا->hdc);
        SDL_free(ڈیٹا);
        واپس WIN_سیٹ_Error("SetProp() failed");
    }
#اگر_ختم

    کھڑکی->اندرونی_2 = ڈیٹا;

    // Set up the window proc function
    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
#اگر_تعریف_شدہ GWLP_WNDPROC
        ڈیٹا->wndproc = (WNDPROC)Get_کھڑکی_Long_Ptr(hwnd, GWLP_WNDPROC);
        اگر (ڈیٹا->wndproc != WIN_کھڑکی_Proc) {
            سیٹ_کھڑکی_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_کھڑکی_Proc);
        }
#ورنہ
        ڈیٹا->wndproc = (WNDPROC)Get_کھڑکی_Long(hwnd, GWL_WNDPROC);
        اگر (ڈیٹا->wndproc != WIN_کھڑکی_Proc) {
            سیٹ_کھڑکی_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_کھڑکی_Proc);
        }
#اگر_ختم
    } ورنہ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
        اگر (style & WS_VISIBLE) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        } ورنہ {
            کھڑکی->flags |= SDL_کھڑکی_HIDDEN;
        }
        اگر (style & WS_POPUP) {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
        } ورنہ {
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        }
        اگر (style & WS_THICKFRAME) {
            کھڑکی->flags |= SDL_کھڑکی_RESIZABLE;
        } ورنہ اگر (!(style & WS_POPUP)) {
            کھڑکی->flags &= ~SDL_کھڑکی_RESIZABLE;
        }
#اگر_تعریف_شدہ WS_MAXIMIZE
        اگر (style & WS_MAXIMIZE) {
            کھڑکی->flags |= SDL_کھڑکی_MAXIMIZED;
        } ورنہ
#اگر_ختم
        {
            کھڑکی->flags &= ~SDL_کھڑکی_MAXIMIZED;
        }
#اگر_تعریف_شدہ WS_MINIMIZE
        اگر (style & WS_MINIMIZE) {
            کھڑکی->flags |= SDL_کھڑکی_MINIMIZED;
        } ورنہ
#اگر_ختم
        {
            کھڑکی->flags &= ~SDL_کھڑکی_MINIMIZED;
        }
    }
    اگر (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        RECT rect;
        اگر (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
            صحیح w = rect.دایاں;
            صحیح h = rect.bottom;

            اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
                کھڑکی->floating.w = کھڑکی->windowed.w = کھڑکی->w = w;
                کھڑکی->floating.h = کھڑکی->windowed.h = کھڑکی->h = h;
            } ورنہ اگر ((کھڑکی->windowed.w && کھڑکی->windowed.w != w) || (کھڑکی->windowed.h && کھڑکی->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                صحیح x, y;
                // Figure out what the window area will be
                WIN_Adjust_کھڑکی_Rect(کھڑکی, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                ڈیٹا->expected_resize = true;
                سیٹ_کھڑکی_Pos(hwnd, تہی, x, y, w, h, ڈیٹا->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                ڈیٹا->expected_resize = false;
            } ورنہ {
                کھڑکی->w = w;
                کھڑکی->h = h;
            }
        }
    }
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        نقطہ_2 نقطہ;
        نقطہ.x = 0;
        نقطہ.y = 0;
        اگر (Client_مقصد_Screen(hwnd, &نقطہ)) {
            اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
                کھڑکی->floating.x = کھڑکی->windowed.x = نقطہ.x;
                کھڑکی->floating.y = کھڑکی->windowed.y = نقطہ.y;
            }
            کھڑکی->x = نقطہ.x;
            کھڑکی->y = نقطہ.y;
        }
    }

    WIN_Update_کھڑکی_ICCProfile(کھڑکی, false);
#اگر_ختم

#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
#ورنہ
    اگر (GetFocus() == hwnd) {
        کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
        WIN_UpdateClipCursor(کھڑکی);
    }
#اگر_ختم

    اگر (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        WIN_سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, true);
    } ورنہ {
        WIN_سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, false);
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    اگر (videodata->رجسٹر_Touch_کھڑکی) {
        videodata->رجسٹر_Touch_کھڑکی(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#اگر_ختم

    اگر (ڈیٹا->والد && !کھڑکی->والد) {
        ڈیٹا->destroy_والد_with_کھڑکی = true;
    }

    ڈیٹا->initializing = false;

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        صحیح titleLen;
        bool isstack;

        titleLen = Get_کھڑکی_متن_لمبائی(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        اگر (title) {
            titleLen = Get_کھڑکی_متن(hwnd, title, titleLen + 1);
        } ورنہ {
            titleLen = 0;
        }
        اگر (titleLen > 0) {
            کھڑکی->title = WIN_String_مقصد_UTF8(title);
        }
        اگر (title) {
            SDL_small_free(title, isstack);
        }
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_HWND_اشارہ_گر, ڈیٹا->hwnd);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_HDC_اشارہ_گر, ڈیٹا->hdc);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WIN32_INSTANCE_اشارہ_گر, ڈیٹا->hinstance);

    // All done!
    واپس true;
}

ساکن خالی Cleanup_کھڑکی_ڈیٹا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا) {
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (ڈیٹا->drop_ہدف) {
            WIN_AcceptDragAndDrop(کھڑکی, false);
        }
        SDL_free(ڈیٹا->ICMFileName);
        اگر (ڈیٹا->keyboard_hook) {
            UnhookWindowsHookEx(ڈیٹا->keyboard_hook);
        }
        اگر (ڈیٹا->hicon) {
            DestroyIcon(ڈیٹا->hicon);
        }
        ReleaseDC(ڈیٹا->hwnd, ڈیٹا->hdc);
        RemoveProp(ڈیٹا->hwnd, متن_2("SDL_WindowData"));
#اگر_ختم
        اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            Destroy_کھڑکی(ڈیٹا->hwnd);
            اگر (ڈیٹا->destroy_والد_with_کھڑکی && ڈیٹا->والد) {
                Destroy_کھڑکی(ڈیٹا->والد);
            }
        } ورنہ {
            // Restore any original event handler...
            اگر (ڈیٹا->wndproc) {
#اگر_تعریف_شدہ GWLP_WNDPROC
                سیٹ_کھڑکی_Long_Ptr(ڈیٹا->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)ڈیٹا->wndproc);
#ورنہ
                سیٹ_کھڑکی_Long(ڈیٹا->hwnd, GWL_WNDPROC,
                              (LONG_PTR)ڈیٹا->wndproc);
#اگر_ختم
            }
        }
        SDL_free(ڈیٹا);
    }
    کھڑکی->اندرونی_2 = تہی;
}

ساکن خالی WIN_ConstrainPopup(SDL_کھڑکی *کھڑکی, bool output_مقصد_pending)
{
    // Possibly clamp popup windows to the output borders
    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحیح abs_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->floating.x;
        صحیح abs_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->floating.y;
        ثابت صحیح چوڑائی = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
        ثابت صحیح اونچائی = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
        صحیح انحراف_x = 0, انحراف_y = 0;

        اگر (کھڑکی->constrain_popup) {
            // Calculate the total offset from the parents
            برائے (w = کھڑکی->والد; SDL_کھڑکی_IS_POPUP(w); w = w->والد) {
                انحراف_x += w->x;
                انحراف_y += w->y;
            }

            انحراف_x += w->x;
            انحراف_y += w->y;
            abs_x += انحراف_x;
            abs_y += انحراف_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_کھڑکی(w);
            SDL_GetDisplayBounds(displayID, &rect);
            اگر (abs_x + چوڑائی > rect.x + rect.w) {
                abs_x -= (abs_x + چوڑائی) - (rect.x + rect.w);
            }
            اگر (abs_y + اونچائی > rect.y + rect.h) {
                abs_y -= (abs_y + اونچائی) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        اگر (output_مقصد_pending) {
            کھڑکی->pending.x = abs_x - انحراف_x;
            کھڑکی->pending.y = abs_y - انحراف_y;
            کھڑکی->pending.w = چوڑائی;
            کھڑکی->pending.h = اونچائی;
        } ورنہ {
            کھڑکی->floating.x = abs_x - انحراف_x;
            کھڑکی->floating.y = abs_y - انحراف_y;
            کھڑکی->floating.w = چوڑائی;
            کھڑکی->floating.h = اونچائی;
        }
    }
}

ساکن خالی WIN_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_فعال_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the topmost parent
    جب (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = کھڑکی;

    اگر (سیٹ_فعال_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

bool WIN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    HWND hwnd = (HWND)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_HWND_اشارہ_گر, SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", تہی));
    HWND والد = تہی;
    اگر (hwnd) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;

        اگر (!تیاری_کھڑکی_ڈیٹا(_this, کھڑکی, hwnd, والد)) {
            واپس false;
        }
    } ورنہ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        صحیح x, y;
        صحیح w, h;

        اگر (کھڑکی->flags & SDL_کھڑکی_UTILITY) {
            والد = Create_کھڑکی(SDL_Appname, متن_2(""), STYLE_BASIC, 0, 0, 32, 32, تہی, تہی, SDL_Instance, تہی);
        } ورنہ اگر (کھڑکی->والد) {
            والد = کھڑکی->والد->اندرونی_2->hwnd;
        }

        style |= Get_کھڑکی_Style(کھڑکی);
        styleEx |= (DWORD)SDL_Get_نمبر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_STYLE_EX_نمبر, Get_کھڑکی_Style_Ex(کھڑکی));

        // Figure out what the window area will be
        WIN_ConstrainPopup(کھڑکی, false);
        WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_کھڑکی_Ex(styleEx, SDL_Appname, متن_2(""), style,
                              x, y, w, h, والد, تہی, SDL_Instance, تہی);
        اگر (!hwnd) {
            واپس WIN_سیٹ_Error("Couldn't create window");
        }

        WIN_Update_Dark_منوال_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        اگر (!تیاری_کھڑکی_ڈیٹا(_this, کھڑکی, hwnd, والد)) {
            Destroy_کھڑکی(hwnd);
            اگر (والد) {
                Destroy_کھڑکی(والد);
            }
            واپس false;
        }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_متن_داخلہ(_this, کھڑکی);
#اگر_ختم

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        سیٹ_کھڑکی_Pos(hwnd, تہی, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
            Show_کھڑکی(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    اگر (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) {
        اگر (videodata->Dwm_Enable_Blur_Behind_کھڑکی) {
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

    HWND share_hwnd = (HWND)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WIN32_PIXEL_FORMAT_HWND_اشارہ_گر, تہی);
    اگر (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        صحیح pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, حجم(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        اگر (!سیٹ_Pixel_Format(کھڑکی->اندرونی_2->hdc, pixel_format, &pfd)) {
            WIN_Destroy_کھڑکی(_this, کھڑکی);
            واپس WIN_سیٹ_Error("SetPixelFormat()");
        }
    } ورنہ {
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        اگر (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
            واپس true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_ES2
        اگر ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_ڈیٹا || WIN_GL_UseEGL(_this))
#اگر_ختم // SDL_VIDEO_OPENGL_WGL
        ) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            اگر (!WIN_GLES_تیاری_کھڑکی(_this, کھڑکی)) {
                WIN_Destroy_کھڑکی(_this, کھڑکی);
                واپس false;
            }
            واپس true;
#ورنہ
            واپس SDL_سیٹ_Error("Could not create GLES window surface (EGL support not configured)");
#اگر_ختم // SDL_VIDEO_OPENGL_EGL
        }
#اگر_ختم // SDL_VIDEO_OPENGL_ES2

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
        اگر (!WIN_GL_تیاری_کھڑکی(_this, کھڑکی)) {
            WIN_Destroy_کھڑکی(_this, کھڑکی);
            واپس false;
        }
#ورنہ
        واپس SDL_سیٹ_Error("Could not create GL window (WGL support not configured)");
#اگر_ختم
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    واپس true;
}

خالی WIN_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    LPTSTR title = WIN_UTF8_مقصد_String(کھڑکی->title);
    سیٹ_کھڑکی_متن(hwnd, title);
    SDL_free(title);
#اگر_ختم
}

bool WIN_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    HICON hicon = تہی;
    BYTE *icon_bmp;
    صحیح icon_len, نقاب_len, صف_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool نتیجہ = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_وقت_ASSERT(WIN_سیٹ_کھڑکی_Icon_استعمال_کرتا_BITMAPINFOHEADER_مقصد_prepare_an_ICONIMAGE, حجم(BITMAPINFOHEADER) == 40);
    نقاب_len = (icon->h * (icon->w + 7) / 8);
    icon_len = حجم(BITMAPINFOHEADER) + icon->h * icon->w * حجم(Uint32) + نقاب_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    اگر (!icon_bmp) {
        واپس false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_سائز = SDL_Swap32LE(حجم(BITMAPINFOHEADER));
    bmi->bi_چوڑائی = SDL_Swap32LE(icon->w);
    bmi->bi_اونچائی = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_ثنائی_ہندسہ_گنتی = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_سائز_Image = SDL_Swap32LE(icon->h * icon->w * حجم(Uint32));
    bmi->bi_XPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_فی_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_مستعمل = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[حجم(BITMAPINFOHEADER)];
    صف_len = icon->w * حجم(Uint32);
    y = icon->h;
    جب (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, صف_len);
        dst += صف_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - نقاب_len, 0xFF, نقاب_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    اگر (!hicon) {
        واپس SDL_سیٹ_Error("SetWindowIcon() failed, error %08X", (غیرعلامتی صحیح)Get_آخری_Error());
    }

    اگر (ڈیٹا->hicon) {
        DestroyIcon(ڈیٹا->hicon);
    }
    ڈیٹا->hicon = hicon;

    // Set the icon for the window
    Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_پیغام(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    واپس نتیجہ;
#ورنہ
    واپس SDL_Unsupported();
#اگر_ختم
}

bool WIN_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        اگر (!(کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED))) {
            WIN_ConstrainPopup(کھڑکی, true);
            واپس WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی,
                                                 کھڑکی->اندرونی_2->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ورنہ {
        واپس SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, true);
    }

    واپس true;
}

خالی WIN_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED))) {
        WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, کھڑکی->اندرونی_2->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ورنہ {
        // Can't resize the window
        کھڑکی->آخری_سائز_pending = false;
    }
}

bool WIN_Get_کھڑکی_Borders_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *چوٹی = rcClient.چوٹی;
    *بایاں = rcClient.بایاں;
    *bottom = rcClient.bottom;
    *دایاں = rcClient.دایاں;

    واپس true;
#ورنہ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    RECT rcClient, rc_کھڑکی;
    نقطہ_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    اگر (!GetClientRect(hwnd, &rcClient)) {
        واپس SDL_سیٹ_Error("GetClientRect() failed, error %08X", (غیرعلامتی صحیح)Get_آخری_Error());
    }

    اگر (!Get_کھڑکی_Rect(hwnd, &rc_کھڑکی)) {
        واپس SDL_سیٹ_Error("GetWindowRect() failed, error %08X", (غیرعلامتی صحیح)Get_آخری_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_کھڑکی.چوٹی;
    ptDiff.x = rc_کھڑکی.بایاں;

    اگر (!Screen_مقصد_Client(hwnd, &ptDiff)) {
        واپس SDL_سیٹ_Error("ScreenToClient() failed, error %08X", (غیرعلامتی صحیح)Get_آخری_Error());
    }

    rc_کھڑکی.چوٹی = ptDiff.y;
    rc_کھڑکی.بایاں = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_کھڑکی.bottom;
    ptDiff.x = rc_کھڑکی.دایاں;

    اگر (!Screen_مقصد_Client(hwnd, &ptDiff)) {
        واپس SDL_سیٹ_Error("ScreenToClient() failed, error %08X", (غیرعلامتی صحیح)Get_آخری_Error());
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

    واپس true;
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

خالی WIN_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    RECT rect;

    اگر (GetClientRect(hwnd, &rect) && WIN_کھڑکی_Rect_Valid(&rect)) {
        *w = rect.دایاں;
        *h = rect.bottom;
    } ورنہ اگر (کھڑکی->آخری_pixel_w && کھڑکی->آخری_pixel_h) {
        *w = کھڑکی->آخری_pixel_w;
        *h = کھڑکی->آخری_pixel_h;
    } ورنہ {
        // Probably created minimized, use the restored size
        *w = کھڑکی->floating.w;
        *h = کھڑکی->floating.h;
    }
}

خالی WIN_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true);

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Update our position in case our parent moved while we were hidden
        WIN_سیٹ_کھڑکی_Position(_this, کھڑکی);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    اگر (کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
            style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_نقاب;
            style |= Get_کھڑکی_Style(کھڑکی);
            سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        }
    }
    style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);
    اگر (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    ڈیٹا->showing_کھڑکی = true;
    اگر (bActivate) {
        Show_کھڑکی(hwnd, SW_SHOW);
    } ورنہ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        سیٹ_کھڑکی_Pos(hwnd, تہی, 0, 0, 0, 0, کھڑکی->اندرونی_2->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    ڈیٹا->showing_کھڑکی = false;

    اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE) && bActivate) {
        WIN_سیٹ_Keyboard_Focus(کھڑکی, true);
    }
    اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        WIN_سیٹ_کھڑکی_Modal(_this, کھڑکی, true);
    }
}

خالی WIN_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;

    اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        WIN_سیٹ_کھڑکی_Modal(_this, کھڑکی, false);
    }

    Show_کھڑکی(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
        WIN_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }
}

خالی WIN_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
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
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = تہی;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    اگر (bForce) {
        hCurWnd = Get_Foreground_کھڑکی();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_کھڑکی_Thread_Process_Id(hCurWnd, تہی);
        Show_کھڑکی(hwnd, SW_RESTORE);
        Attach_Thread_داخلہ(dwCurID, dwMyID, TRUE);
        سیٹ_کھڑکی_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        اگر (!SDL_ShouldAllowTopmost() || !(کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
            سیٹ_کھڑکی_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    اگر (bActivate) {
        سیٹ_Foreground_کھڑکی(hwnd);
        اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
            WIN_سیٹ_Keyboard_Focus(کھڑکی, کھڑکی->والد == SDL_GetKeyboardFocus());
        }
    } ورنہ {
        سیٹ_کھڑکی_Pos(hwnd, HWND_چوٹی, 0, 0, 0, 0, ڈیٹا->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    اگر (bForce) {
        Attach_Thread_داخلہ(dwCurID, dwMyID, FALSE);
        سیٹ_Focus(hwnd);
        سیٹ_فعال_کھڑکی(hwnd);
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

خالی WIN_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        HWND hwnd = ڈیٹا->hwnd;
        ڈیٹا->expected_resize = true;
        Show_کھڑکی(hwnd, SW_MAXIMIZE);
        ڈیٹا->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        اگر (کھڑکی->max_w || کھڑکی->max_h) {
            صحیح fx, fy, fw, fh;

            کھڑکی->windowed.w = کھڑکی->max_w ? SDL_min(کھڑکی->w, کھڑکی->max_w) : کھڑکی->windowed.w;
            کھڑکی->windowed.h = کھڑکی->max_h ? SDL_min(کھڑکی->h, کھڑکی->max_h) : کھڑکی->windowed.h;
            WIN_Adjust_کھڑکی_Rect(کھڑکی, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            ڈیٹا->expected_resize = true;
            سیٹ_کھڑکی_Pos(hwnd, HWND_چوٹی, fx, fy, fw, fh, ڈیٹا->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            ڈیٹا->expected_resize = false;
        }
    } ورنہ {
        ڈیٹا->windowed_منوال_was_maximized = true;
    }
}

خالی WIN_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    HWND hwnd = کھڑکی->اندرونی_2->hwnd;
    Show_کھڑکی(hwnd, SW_MINIMIZE);
}

خالی WIN_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    DWORD style;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);

    ڈیٹا->اندر_border_change = true;
    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
    WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, ڈیٹا->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    ڈیٹا->اندر_border_change = false;
}

خالی WIN_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    DWORD style;

    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);

    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
}

خالی WIN_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

خالی WIN_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        اگر (!ڈیٹا->showing_کھڑکی || کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED)) {
            HWND hwnd = ڈیٹا->hwnd;
            ڈیٹا->expected_resize = true;
            Show_کھڑکی(hwnd, SW_RESTORE);
            ڈیٹا->expected_resize = false;
        }
    } ورنہ {
        ڈیٹا->windowed_منوال_was_maximized = false;
    }
}

ساکن خالی WIN_Update_کونا_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_کھڑکی_کونا_PREFERENCE کونا_Pref)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    اگر (videodata->Dwm_سیٹ_کھڑکی_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سیٹ_کھڑکی_Attribute(hwnd, DWMWA_کھڑکی_کونا_PREFERENCE, &کونا_Pref, حجم(کونا_Pref));
    }
#اگر_ختم
}

ساکن خالی WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    اگر (videodata->Dwm_سیٹ_کھڑکی_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_سیٹ_کھڑکی_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, حجم(colorRef));
    }
#اگر_ختم
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_نتیجہ WIN_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_ڈیٹا *displaydata = display->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا ? ڈیٹا->hwnd : تہی;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND چوٹی;
    صحیح x, y;
    صحیح w, h;
    bool enterMaximized = false;

#اگر_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (صحیح)fullscreen);
#اگر_ختم

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !fullscreen) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (SDL_ShouldAllowTopmost() && (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی)) {
        چوٹی = HWND_TOPMOST;
    } ورنہ {
        چوٹی = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_سائز = حجم(MONITORINFO);
    اگر (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_سیٹ_Error("GetMonitorInfo failed");
        واپس SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
    style = Get_کھڑکی_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_نقاب;
    style |= Get_کھڑکی_Style(کھڑکی);
    styleEx = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

    اگر (fullscreen) {
        x = minfo.rcMonitor.بایاں;
        y = minfo.rcMonitor.چوٹی;
        w = minfo.rcMonitor.دایاں - minfo.rcMonitor.بایاں;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.چوٹی;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        اگر (style & WS_MAXIMIZE) {
            ڈیٹا->windowed_منوال_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_کونا_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ورنہ {
        BOOL menu;

        WIN_Update_کونا_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        اگر (ڈیٹا->windowed_منوال_was_maximized && !ڈیٹا->اندر_کھڑکی_deactivation) {
            enterMaximized = true;
            ڈیٹا->disable_move_سائز_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != تہی);
        WIN_Adjust_کھڑکی_Rect_With_Style(کھڑکی, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        ڈیٹا->windowed_منوال_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        اگر (enterMaximized) {
            ثابت SDL_نقطہ windowed_نقطہ = { کھڑکی->windowed.x, کھڑکی->windowed.y };
            ثابت SDL_نقطہ floating_نقطہ = { کھڑکی->floating.x, کھڑکی->floating.y };
            ثابت SDL_DisplayID floating_display = SDL_Get_Display_For_نقطہ(&floating_نقطہ);
            ثابت SDL_DisplayID windowed_display = SDL_Get_Display_For_نقطہ(&windowed_نقطہ);

            اگر (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                اگر (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ورنہ {
                    x = bounds.x;
                }
                اگر (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ورنہ {
                    y = bounds.y;
                }
            }
        }
    }

    /* Always reset the window to the base floating size before possibly re-applying the maximized state,
     * otherwise, the base floating size can seemingly be lost in some cases.
     */
    سیٹ_کھڑکی_Long(hwnd, GWL_STYLE, style);
    ڈیٹا->expected_resize = true;
    سیٹ_کھڑکی_Pos(hwnd, چوٹی, x, y, w, h, ڈیٹا->copybits_flag | SWP_NOACTIVATE);
    ڈیٹا->expected_resize = false;
    ڈیٹا->disable_move_سائز_events = false;

    اگر (enterMaximized) {
        WIN_Maximize_کھڑکی(_this, کھڑکی);
    }

    اگر (!fullscreen && ڈیٹا && ڈیٹا->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_پیغام(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)ڈیٹا->hicon);
    }

#اگر_تعریف_شدہ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (صحیح)fullscreen, x, y, w, h);
#اگر_ختم

#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    واپس SDL_FULLSCREEN_SUCCEEDED;
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
خالی WIN_Update_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, bool send_event)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);

    اگر (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, تہی, تہی, تہی);
        اگر (hdc) {
            WCHAR fileName[MAX_راستہ];
            DWORD file_Name_سائز = SDL_arraysize(fileName);
            اگر (GetICMProfileW(hdc, &file_Name_سائز, fileName)) {
                // fileNameSize includes '\0' on return
                اگر (!ڈیٹا->ICMFileName ||
                    SDL_wcscmp(ڈیٹا->ICMFileName, fileName) != 0) {
                    SDL_free(ڈیٹا->ICMFileName);
                    ڈیٹا->ICMFileName = SDL_wcsdup(fileName);
                    اگر (send_event) {
                        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلا, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

خالی *WIN_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    حرف *filename_utf8;
    خالی *icc_Profile_ڈیٹا = تہی;

    filename_utf8 = WIN_String_مقصد_UTF8_W(ڈیٹا->ICMFileName);
    اگر (filename_utf8) {
        icc_Profile_ڈیٹا = SDL_بھرو_File(filename_utf8, سائز);
        اگر (!icc_Profile_ڈیٹا) {
            SDL_سیٹ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    واپس icc_Profile_ڈیٹا;
}

ساکن خالی WIN_GrabKeyboard(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HMODULE module;

    اگر (ڈیٹا->keyboard_hook) {
        واپس;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    اگر (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_پتہ,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        واپس;
    }

    // Capture a snapshot of the current keyboard state before the hook
    اگر (!GetKeyboardState(ڈیٹا->videodata->pre_hook_کلید_state)) {
        واپس;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    ڈیٹا->keyboard_hook = سیٹ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

خالی WIN_UngrabKeyboard(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا->keyboard_hook) {
        UnhookWindowsHookEx(ڈیٹا->keyboard_hook);
        ڈیٹا->keyboard_hook = تہی;
    }
}

bool WIN_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    WIN_UpdateClipCursor(کھڑکی);
    واپس true;
}

bool WIN_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    WIN_UpdateClipCursor(کھڑکی);
    واپس true;
}

bool WIN_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    اگر (grabbed) {
        WIN_GrabKeyboard(کھڑکی);
    } ورنہ {
        WIN_UngrabKeyboard(کھڑکی);
    }

    واپس true;
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

خالی WIN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Cleanup_کھڑکی_ڈیٹا(_this, کھڑکی);
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
خالی WIN_On_کھڑکی_Enter(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (!ڈیٹا || !ڈیٹا->hwnd) {
        // The window wasn't fully initialized
        واپس;
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        WIN_سیٹ_کھڑکی_Position_اندرونی(کھڑکی, ڈیٹا->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ساکن BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    واپس GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_مقصد_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_مقصد_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

خالی WIN_Unclip_Cursor_For_کھڑکی(SDL_کھڑکی *کھڑکی) {
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    RECT rect;
    اگر (GetClipCursor(&rect) && SDL_memcmp(&rect, &ڈیٹا->cursor_clipped_rect, حجم(rect)) == 0) {
        ClipCursor(تہی);
        SDL_zero(ڈیٹا->cursor_clipped_rect);
    }
}

خالی WIN_UpdateClipCursor(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Video_ڈیٹا *videodata = ڈیٹا->videodata;
    اگر (ڈیٹا->اندر_title_click || ڈیٹا->focus_click_pending || ڈیٹا->postpone_clipcursor) {
        واپس;
    }

    SDL_Rect mouse_rect = کھڑکی->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS);
    bool win_is_grabbed = (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED);
    bool win_اندر_relmode = (کھڑکی->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال);
    bool cursor_confine = win_اندر_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    اگر (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        اگر (!GetClipCursor(&current)) {
            واپس;
        }
        اگر (videodevice && (
            current.بایاں != videodevice->desktop_bounds.x ||
            current.چوٹی  != videodevice->desktop_bounds.y
        )) {
            نقطہ_2 پہلا, دوسرا;
            پہلا.x  = current.بایاں;
            پہلا.y  = current.چوٹی;
            دوسرا.x = current.دایاں  - 1;
            دوسرا.y = current.bottom - 1;
            اگر (!Pt_اندر_Rect(&ڈیٹا->cursor_clipped_rect, پہلا) ||
                !Pt_اندر_Rect(&ڈیٹا->cursor_clipped_rect, دوسرا)) {
                واپس;
            }
        }
        ClipCursor(تہی);
        SDL_zero(ڈیٹا->cursor_clipped_rect);
        واپس;
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
    bool تالا_مقصد_ctr = (mouse->relative_منوال && mouse->relative_منوال_center);

    RECT client;
    اگر (!GetClientScreenRect(ڈیٹا->hwnd, &client)) {
        واپس;
    }

    RECT ہدف = client;
    اگر (تالا_مقصد_ctr) {
        LONG cx = (client.بایاں + client.دایاں ) / 2;
        LONG cy = (client.چوٹی  + client.bottom) / 2;
        ہدف = ڈیٹا->cursor_ctrlock_rect;
        ہدف.بایاں   += cx;
        ہدف.دایاں  += cx;
        ہدف.چوٹی    += cy;
        ہدف.bottom += cy;
    } ورنہ اگر (win_mouse_rect) {
        RECT custom, overlap;
        custom.بایاں   = client.بایاں + mouse_rect.x;
        custom.چوٹی    = client.چوٹی  + mouse_rect.y;
        custom.دایاں  = client.بایاں + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.چوٹی  + mouse_rect.y + mouse_rect.h;
        اگر (IntersectRect(&overlap, &client, &custom)) {
            ہدف = overlap;
        } ورنہ اگر (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_کھڑکی(کھڑکی);
            واپس;
        }
    } ورنہ اگر (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        اگر (videodata->سیٹ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_کھڑکی(ڈیٹا->hwnd, MONITOR_DEFAULTTONEAREST);
            اگر (hmon) {
                UINT hdpi_uint, vdpi_uint;
                اگر (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ثابت اعشاری scale = (اعشاری)hdpi_uint / (اعشاری)USER_DEFAULT_SCREEN_DPI;
                    اگر (scale != SDL_floorf(scale)) {
                        اگر (ہدف.بایاں < ہدف.دایاں) {
                            ہدف.بایاں += 1;
                        }
                        اگر (ہدف.دایاں > ہدف.بایاں) {
                            ہدف.دایاں -= 1;
                        }
                        اگر (ہدف.چوٹی < ہدف.bottom) {
                            ہدف.چوٹی += 1;
                        }
                        اگر (ہدف.bottom > ہدف.چوٹی) {
                            ہدف.bottom -= 1;
                        }
                    }
                }
            }
            videodata->سیٹ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    اگر (GetClipCursor(&client) &&
        0 != SDL_memcmp(&ہدف, &client, حجم(client)) &&
        ClipCursor(&ہدف)) {
        ڈیٹا->cursor_clipped_rect = ہدف; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    واپس true; // just succeed, the real work is done elsewhere.
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity)
{
#اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    واپس false;
#ورنہ
    ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HWND hwnd = ڈیٹا->hwnd;
    ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

    اگر (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        اگر (style & WS_EX_LAYERED) {
            اگر (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                واپس WIN_سیٹ_Error("SetWindowLong()");
            }
        }
    } ورنہ {
        ثابت BYTE alpha = (BYTE)((صحیح)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        اگر (!(style & WS_EX_LAYERED)) {
            اگر (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                واپس WIN_سیٹ_Error("SetWindowLong()");
            }
        }

        اگر (سیٹ_Layered_کھڑکی_اوصاف(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            واپس WIN_سیٹ_Error("SetLayeredWindowAttributes()");
        }
    }

    واپس true;
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ساکن ثابت حرف *SDLGetClipboardFormatName(UINT cf, حرف *متن, صحیح len)
{
    انتخاب (cf) {
    حالت CF_متن:
        واپس "CF_TEXT";
    حالت CF_BITMAP:
        واپس "CF_BITMAP";
    حالت CF_METAFILEPICT:
        واپس "CF_METAFILEPICT";
    حالت CF_SYLK:
        واپس "CF_SYLK";
    حالت CF_DIF:
        واپس "CF_DIF";
    حالت CF_TIFF:
        واپس "CF_TIFF";
    حالت CF_OEMTEXT:
        واپس "CF_OEMTEXT";
    حالت CF_DIB:
        واپس "CF_DIB";
    حالت CF_PALETTE:
        واپس "CF_PALETTE";
    حالت CF_PENDATA:
        واپس "CF_PENDATA";
    حالت CF_RIFF:
        واپس "CF_RIFF";
    حالت CF_WAVE:
        واپس "CF_WAVE";
    حالت CF_UNICODETEXT:
        واپس "CF_UNICODETEXT";
    حالت CF_ENHMETAFILE:
        واپس "CF_ENHMETAFILE";
    حالت CF_HDROP:
        واپس "CF_HDROP";
    حالت CF_LOCALE:
        واپس "CF_LOCALE";
    حالت CF_DIBV5:
        واپس "CF_DIBV5";
    حالت CF_OWNERDISPLAY:
        واپس "CF_OWNERDISPLAY";
    حالت CF_DSPTEXT:
        واپس "CF_DSPTEXT";
    حالت CF_DSPBITMAP:
        واپس "CF_DSPBITMAP";
    حالت CF_DSPMETAFILEPICT:
        واپس "CF_DSPMETAFILEPICT";
    حالت CF_DSPENHMETAFILE:
        واپس "CF_DSPENHMETAFILE";
    طےشدہ:
        اگر (GetClipboardFormatNameA(cf, متن, len)) {
            واپس متن;
        } ورنہ {
            واپس تہی;
        }
    }
}

ساکن STDMETHODIMP_(ULONG) SDLDrop_ہدف_جوڑو_Ref(SDLDrop_ہدف *ہدف)
{
    واپس ++ہدف->refcount;
}

ساکن STDMETHODIMP_(ULONG) SDLDrop_ہدف_Release(SDLDrop_ہدف *ہدف)
{
    --ہدف->refcount;
    اگر (ہدف->refcount == 0) {
        SDL_free(ہدف);
        واپس 0;
    }
    واپس ہدف->refcount;
}

ساکن STDMETHODIMP SDLDrop_ہدف_Query_Interface(SDLDrop_ہدف *ہدف, REFIID riid, PVOID *ppv)
{
    اگر (ppv == تہی) {
        واپس E_INVALIDARG;
    }

    *ppv = تہی;
    اگر (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_ہدف)) {
        *ppv = (خالی *)ہدف;
    }
    اگر (*ppv) {
        SDLDrop_ہدف_جوڑو_Ref(ہدف);
        واپس S_OK;
    }
    واپس E_NOINTERFACE;
}

ساکن STDMETHODIMP SDLDrop_ہدف_Drag_Enter(SDLDrop_ہدف *ہدف,
                                            IDataObject *p_ڈیٹا_Object, DWORD grf_کلید_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    اگر (Screen_مقصد_Client(ہدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ہدف->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ہدف->کھڑکی, pnt.x, pnt.y);
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    واپس S_OK;
}

ساکن STDMETHODIMP SDLDrop_ہدف_Drag_Over(SDLDrop_ہدف *ہدف,
                                           DWORD grf_کلید_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    اگر (Screen_مقصد_Client(ہدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ہدف->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ہدف->کھڑکی, pnt.x, pnt.y);
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    واپس S_OK;
}

ساکن STDMETHODIMP SDLDrop_ہدف_Drag_Leave(SDLDrop_ہدف *ہدف)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In DragLeave");
    SDL_SendDropComplete(ہدف->کھڑکی);
    واپس S_OK;
}

ساکن STDMETHODIMP SDLDrop_ہدف_Drop(SDLDrop_ہدف *ہدف,
                                       IDataObject *p_ڈیٹا_Object, DWORD grf_کلید_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    نقطہ_2 pnt = { pt.x, pt.y };
    اگر (Screen_مقصد_Client(ہدف->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ہدف->کھڑکی->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ہدف->کھڑکی, pnt.x, pnt.y);
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_ڈیٹا_Object->lpVtbl->EnumFormatEtc(p_ڈیٹا_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        اگر (hres == S_OK) {
            FORMATETC fetc;
            جب (pEnumFormatEtc->lpVtbl->اگلا_3(pEnumFormatEtc, 1, &fetc, تہی) == S_OK) {
                حرف name[257] = { 0 };
                ثابت حرف *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                اگر (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ورنہ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ہدف->format_file;
        fetc.ptd = تہی;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/uri-list";
        اگر (SUCCEEDED(p_ڈیٹا_Object->lpVtbl->Query_Get_ڈیٹا(p_ڈیٹا_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ڈیٹا_Object->lpVtbl->Get_ڈیٹا(p_ڈیٹا_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائز(med.hGlobal);
                ثابت خالی *بفر_2 = (خالی *)Global_تالا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (غیرعلامتی طویل)bsize, بفر_2);
                اگر (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = تہی;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    جب (token != تہی) {
                        اگر (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (غیرعلامتی طویل)SDL_strlen(token), (غیرعلامتی طویل)bsize, token);
                            SDL_SendDropFile(ہدف->کھڑکی, تہی, token);
                        }
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ہدف->کھڑکی);
                واپس S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ہدف->format_متن;
        fetc.ptd = تہی;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "text/plain;charset=utf-8";
        اگر (SUCCEEDED(p_ڈیٹا_Object->lpVtbl->Query_Get_ڈیٹا(p_ڈیٹا_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ڈیٹا_Object->lpVtbl->Get_ڈیٹا(p_ڈیٹا_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائز(med.hGlobal);
                ثابت خالی *بفر_2 = (خالی *)Global_تالا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (غیرعلامتی طویل)bsize, بفر_2);
                اگر (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = تہی;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    جب (token != تہی) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (غیرعلامتی طویل)SDL_strlen(token), (غیرعلامتی طویل)bsize, token);
                        SDL_Send_Drop_متن(ہدف->کھڑکی, (حرف *)token);
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ہدف->کھڑکی);
                واپس S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = تہی;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_UNICODETEXT";
        اگر (SUCCEEDED(p_ڈیٹا_Object->lpVtbl->Query_Get_ڈیٹا(p_ڈیٹا_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ڈیٹا_Object->lpVtbl->Get_ڈیٹا(p_ڈیٹا_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائز(med.hGlobal);
                ثابت خالی *بفر_2 = (خالی *)Global_تالا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (غیرعلامتی طویل)bsize, بفر_2);
                اگر (بفر_2) {
                    بفر_2 = WIN_String_مقصد_UTF8_W((ثابت wchar_t *)بفر_2);
                    اگر (بفر_2) {
                        ثابت size_t lbuffer = SDL_strlen((ثابت حرف *)بفر_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (غیرعلامتی طویل)lbuffer, بفر_2);
                        حرف *متن = (حرف *)SDL_malloc(lbuffer + حجم(Uint32));
                        SDL_memcpy((Uint8 *)متن, بفر_2, lbuffer);
                        SDL_memset((Uint8 *)متن + lbuffer, 0, حجم(Uint32));
                        حرف *saveptr = تہی;
                        حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                        جب (token != تہی) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (غیرعلامتی طویل)SDL_strlen(token), (غیرعلامتی طویل)lbuffer, token);
                            SDL_Send_Drop_متن(ہدف->کھڑکی, (حرف *)token);
                            token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                        }
                        SDL_free(متن);
                        SDL_free((خالی *)بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ہدف->کھڑکی);
                واپس S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_متن;
        fetc.ptd = تہی;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_TEXT";
        اگر (SUCCEEDED(p_ڈیٹا_Object->lpVtbl->Query_Get_ڈیٹا(p_ڈیٹا_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ڈیٹا_Object->lpVtbl->Get_ڈیٹا(p_ڈیٹا_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائز(med.hGlobal);
                ثابت خالی *بفر_2 = (خالی *)Global_تالا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (غیرعلامتی طویل)bsize, بفر_2);
                اگر (بفر_2) {
                    حرف *متن = (حرف *)SDL_malloc(bsize + حجم(Uint32));
                    SDL_memcpy((Uint8 *)متن, بفر_2, bsize);
                    SDL_memset((Uint8 *)متن + bsize, 0, حجم(Uint32));
                    حرف *saveptr = تہی;
                    حرف *token = SDL_strtok_r(متن, "\r\n", &saveptr);
                    جب (token != تہی) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (غیرعلامتی طویل)SDL_strlen(token), (غیرعلامتی طویل)bsize, token);
                        SDL_Send_Drop_متن(ہدف->کھڑکی, (حرف *)token);
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    SDL_free(متن);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ہدف->کھڑکی);
                واپس S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = تہی;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ثابت حرف *format_mime = "CF_HDROP";
        اگر (SUCCEEDED(p_ڈیٹا_Object->lpVtbl->Query_Get_ڈیٹا(p_ڈیٹا_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ڈیٹا_Object->lpVtbl->Get_ڈیٹا(p_ڈیٹا_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            اگر (SUCCEEDED(hres)) {
                ثابت size_t bsize = Global_سائز(med.hGlobal);
                HDROP drop = (HDROP)Global_تالا(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (غیرعلامتی طویل)bsize, drop);
                UINT گنتی = DragQueryFile(drop, 0xFFFFFFFF, تہی, 0);
                برائے (UINT i = 0; i < گنتی; ++i) {
                    UINT سائز = DragQueryFile(drop, i, تہی, 0) + 1;
                    LPTSTR بفر_2 = (LPTSTR)SDL_malloc(سائز * حجم(TCHAR));
                    اگر (بفر_2) {
                        اگر (DragQueryFile(drop, i, بفر_2, سائز)) {
                            حرف *file = WIN_String_مقصد_UTF8(بفر_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (غیرعلامتی طویل)SDL_strlen(file), (غیرعلامتی طویل)bsize, file);
                            SDL_SendDropFile(ہدف->کھڑکی, تہی, file);
                            SDL_free(file);
                        }
                        SDL_free(بفر_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ہدف->کھڑکی);
                واپس S_OK;
            }
        }
    }

    SDL_SendDropComplete(ہدف->کھڑکی);
    واپس S_OK;
}

ساکن خالی *vt_Drop_ہدف[] = {
    (خالی *)(SDLDrop_ہدف_Query_Interface),
    (خالی *)(SDLDrop_ہدف_جوڑو_Ref),
    (خالی *)(SDLDrop_ہدف_Release),
    (خالی *)(SDLDrop_ہدف_Drag_Enter),
    (خالی *)(SDLDrop_ہدف_Drag_Over),
    (خالی *)(SDLDrop_ہدف_Drag_Leave),
    (خالی *)(SDLDrop_ہدف_Drop)
};

خالی WIN_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    اگر (ڈیٹا->videodata->oleinitialized) {
        اگر (accept && !ڈیٹا->drop_ہدف) {
            SDLDrop_ہدف *drop_ہدف = (SDLDrop_ہدف *)SDL_calloc(1, حجم(SDLDrop_ہدف));
            اگر (drop_ہدف != تہی) {
                drop_ہدف->lpVtbl = vt_Drop_ہدف;
                drop_ہدف->کھڑکی = کھڑکی;
                drop_ہدف->hwnd = ڈیٹا->hwnd;
                drop_ہدف->format_file = رجسٹر_Clipboard_Format_W(L"text/uri-list");
                drop_ہدف->format_متن = رجسٹر_Clipboard_Format_W(L"text/plain;charset=utf-8");
                ڈیٹا->drop_ہدف = drop_ہدف;
                SDLDrop_ہدف_جوڑو_Ref(drop_ہدف);
                رجسٹر_Drag_Drop(ڈیٹا->hwnd, (LPDROPTARGET)drop_ہدف);
                SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             کھڑکی->id);
            }
        } ورنہ اگر (!accept && ڈیٹا->drop_ہدف) {
            RevokeDragDrop(ڈیٹا->hwnd);
            SDLDrop_ہدف_Release(ڈیٹا->drop_ہدف);
            ڈیٹا->drop_ہدف = تہی;
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         کھڑکی->id);
        }
    } ورنہ {
        DragAcceptFiles(ڈیٹا->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     کھڑکی->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_سائز = حجم(desc);
    desc.hwnd = کھڑکی->اندرونی_2->hwnd;
    انتخاب (operation) {
    حالت SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        توڑو;
    حالت SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_گنتی = 1;
        توڑو;
    حالت SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        توڑو;
    طےشدہ:
        واپس SDL_Unsupported();
    }

    Flash_کھڑکی_Ex(&desc);

    واپس true;
}

bool WIN_Apply_کھڑکی_پیش_رفت(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    اگر (!ڈیٹا->taskbar_button_created) {
        واپس true;
    }

    اگر (کھڑکی->پیش_رفت_state == SDL_پیش_رفت_STATE_NONE && !ڈیٹا->videodata->taskbar_list) {
        واپس true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(کھڑکی);
    اگر (!taskbar_list) {
        واپس false;
    }

    TBPFLAG tbpFlags;
    انتخاب (کھڑکی->پیش_رفت_state) {
    حالت SDL_پیش_رفت_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        توڑو;
    حالت SDL_پیش_رفت_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        توڑو;
    حالت SDL_پیش_رفت_STATE_معمول:
        tbpFlags = TBPF_معمول;
        توڑو;
    حالت SDL_پیش_رفت_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        توڑو;
    حالت SDL_پیش_رفت_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        توڑو;
    طےشدہ:
        واپس SDL_سیٹ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->سیٹ_پیش_رفت_State(taskbar_list, ڈیٹا->hwnd, tbpFlags);
    اگر (FAILED(ret)) {
        واپس WIN_سیٹ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    اگر (کھڑکی->پیش_رفت_state >= SDL_پیش_رفت_STATE_معمول) {
        ret = taskbar_list->lpVtbl->سیٹ_پیش_رفت_قدر(taskbar_list, ڈیٹا->hwnd, (ULONGLONG)(کھڑکی->پیش_رفت_قدر * 10000.f), 10000);
        اگر (FAILED(ret)) {
            واپس WIN_سیٹ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#اگر_ختم
    واپس true;
}

خالی WIN_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y)
{
    ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    نقطہ_2 pt;

    pt.x = x;
    pt.y = y;
    Client_مقصد_Screen(ڈیٹا->hwnd, &pt);
    Send_پیغام(ڈیٹا->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        HWND hwnd = ڈیٹا->hwnd;
        ثابت LONG style = Get_کھڑکی_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        اگر (focusable) {
            اگر (style & WS_EX_NOACTIVATE) {
                اگر (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    واپس WIN_سیٹ_Error("SetWindowLong()");
                }
            }
        } ورنہ {
            اگر (!(style & WS_EX_NOACTIVATE)) {
                اگر (سیٹ_کھڑکی_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    واپس WIN_سیٹ_Error("SetWindowLong()");
                }
            }
        }
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            اگر (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                WIN_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } ورنہ اگر (focusable) {
                اگر (SDL_ShouldFocusPopup(کھڑکی)) {
                    WIN_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        واپس true;
    }

    واپس true;
}
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_کھڑکی_ڈیٹا *بچہ_ڈیٹا = کھڑکی->اندرونی_2;
    ثابت LONG_PTR والد_hwnd = (LONG_PTR)(والد ? والد->اندرونی_2->hwnd : تہی);
    ثابت DWORD style = Get_کھڑکی_Long(بچہ_ڈیٹا->hwnd, GWL_STYLE);

    اگر (!(style & WS_بچہ)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        سیٹ_کھڑکی_Long_Ptr(بچہ_ڈیٹا->hwnd, GWLP_HWNDPARENT, والد_hwnd);
    } ورنہ {
        سیٹ_والد(بچہ_ڈیٹا->hwnd, (HWND)والد_hwnd);
    }
#اگر_ختم /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    واپس true;
}

bool WIN_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ثابت HWND والد_hwnd = کھڑکی->والد->اندرونی_2->hwnd;

    اگر (modal) {
        // Disable the parent window.
        Enable_کھڑکی(والد_hwnd, FALSE);
    } ورنہ اگر (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
        // Re-enable the parent window
        Enable_کھڑکی(والد_hwnd, TRUE);
    }
#اگر_ختم // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS
