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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS

#అన్తర్భావ "../../core/windows/SDL_windows.h"

#అన్తర్భావ "../../SDL_hints_c.h"
#అన్తర్భావ "../../events/SDL_dropevents_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowskeyboard.h"
#అన్తర్భావ "SDL_windowswindow.h"

// Dropfile support
#అన్తర్భావ <shellapi.h>

#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#అన్తర్భావ <shobjidl.h>
#అయితే_ముగింపు

// Windows CE compatibility
#నిర్వచితం_కాకపోతే SWP_NOCOPYBITS
#నిర్వచించు SWP_NOCOPYBITS 0
#అయితే_ముగింపు

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#నిర్వచితం_కాకపోతే WM_POPUPSYSTEMMENU
#నిర్వచించు WM_POPUPSYSTEMMENU 0x313
#అయితే_ముగింపు

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

#నిర్వచించు STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#నిర్వచించు STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#నిర్వచించు STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#నిర్వచించు STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#నిర్వచించు STYLE_సాధారణ              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#నిర్వచించు STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#నిర్వచించు STYLE_ముసుగు                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_సాధారణ | STYLE_RESIZABLE)

స్థిర DWORD Get_కిటికీ_Style(SDL_కిటికీ *కిటికీ)
{
    DWORD style = 0;

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        style |= WS_POPUP;
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } లేకపోతే {
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ఒకవేళ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } లేకపోతే {
                style |= STYLE_BORDERLESS;
            }
        } లేకపోతే {
            style |= STYLE_సాధారణ;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ఒకవేళ (కిటికీ->అంతర్గత && కిటికీ->అంతర్గత->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    తిరిగి style;
}

స్థిర DWORD Get_కిటికీ_Style_Ex(SDL_కిటికీ *కిటికీ)
{
    DWORD style = 0;

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ) || (కిటికీ->flags & SDL_కిటికీ_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ) || (కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    తిరిగి style;
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
స్థిర ITaskbarList3 *GetTaskbarList(SDL_కిటికీ *కిటికీ)
{
    స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_assert(దత్తాంశం->taskbar_button_created);
    ఒకవేళ (!దత్తాంశం->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ఖాళీ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&దత్తాంశం->videodata->taskbar_list);
        ఒకవేళ (FAILED(ret)) {
            WIN_సమితి_Error_From_HRESULT("Unable to create taskbar list", ret);
            తిరిగి ఖాళీ;
        }
        ITaskbarList3 *taskbarlist = దత్తాంశం->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ఒకవేళ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            దత్తాంశం->videodata->taskbar_list = ఖాళీ;
            WIN_సమితి_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            తిరిగి ఖాళీ;
        }
    }
    తిరిగి దత్తాంశం->videodata->taskbar_list;
}
#అయితే_ముగింపు

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
స్థిర bool WIN_Adjust_కిటికీ_Rect_With_Style(SDL_కిటికీ *కిటికీ, DWORD style, DWORD styleEx, BOOL menu, పూర్ణాంకం *x, పూర్ణాంకం *y, పూర్ణాంకం *వెడల్పు, పూర్ణాంకం *ఎత్తు, SDL_కిటికీ_Rect rect_type)
{
    SDL_Video_దత్తాంశం *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->అంతర్గత : ఖాళీ;
    RECT rect;

    // Client rect, in points
    ఎంపిక (rect_type) {
    స్థితి SDL_WINDOWRECT_CURRENT:
        SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->x, కిటికీ->y, x, y);
        *వెడల్పు = కిటికీ->w;
        *ఎత్తు = కిటికీ->h;
        ఆపు;
    స్థితి SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->windowed.x, కిటికీ->windowed.y, x, y);
        *వెడల్పు = కిటికీ->windowed.w;
        *ఎత్తు = కిటికీ->windowed.h;
        ఆపు;
    స్థితి SDL_WINDOWRECT_FLOATING:
        SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->floating.x, కిటికీ->floating.y, x, y);
        *వెడల్పు = కిటికీ->floating.w;
        *ఎత్తు = కిటికీ->floating.h;
        ఆపు;
    స్థితి SDL_WINDOWRECT_PENDING:
        SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->pending.x, కిటికీ->pending.y, x, y);
        *వెడల్పు = కిటికీ->pending.w;
        *ఎత్తు = కిటికీ->pending.h;
        ఆపు;
    అప్రమేయ:
        // Should never be here
        SDL_assert_release(false);
        *వెడల్పు = 0;
        *ఎత్తు = 0;
        ఆపు;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ఎడమ = 0;
    rect.శిఖరం = 0;
    rect.కుడి = *వెడల్పు;
    rect.bottom = *ఎత్తు;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_BORDERLESS) && !SDL_కిటికీ_IS_POPUP(కిటికీ)) {
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_కిటికీ_Rect_Ex(&rect, style, menu, 0);
#లేకపోతే
        ఒకవేళ (WIN_Is_చొప్పున_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ఒకవేళ (videodata) {
                UINT చట్రం_dpi;
                SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
                చట్రం_dpi = (దత్తాంశం && videodata->Get_Dpi_For_కిటికీ) ? videodata->Get_Dpi_For_కిటికీ(దత్తాంశం->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ఒకవేళ (videodata->Adjust_కిటికీ_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, చట్రం_dpi) == 0) {
                    తిరిగి WIN_సమితి_Error("AdjustWindowRectExForDpi()");
                }
            }
        } లేకపోతే {
            ఒకవేళ (Adjust_కిటికీ_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                తిరిగి WIN_సమితి_Error("AdjustWindowRectEx()");
            }
        }
#అయితే_ముగింపు
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ఎడమ;
    *y += rect.శిఖరం;
    *వెడల్పు = (rect.కుడి - rect.ఎడమ);
    *ఎత్తు = (rect.bottom - rect.శిఖరం);

#నిర్వచితమైతే HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? కిటికీ->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? కిటికీ->windowed.x : కిటికీ->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? కిటికీ->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? కిటికీ->windowed.y : కిటికీ->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? కిటికీ->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? కిటికీ->windowed.w : కిటికీ->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? కిటికీ->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? కిటికీ->windowed.h : కిటికీ->h),
            *x, *y, *వెడల్పు, *ఎత్తు, చట్రం_dpi);
#అయితే_ముగింపు
    తిరిగి true;
}

bool WIN_Adjust_కిటికీ_Rect(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *x, పూర్ణాంకం *y, పూర్ణాంకం *వెడల్పు, పూర్ణాంకం *ఎత్తు, SDL_కిటికీ_Rect rect_type)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
    styleEx = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#లేకపోతే
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ఖాళీ);
#అయితే_ముగింపు
    తిరిగి WIN_Adjust_కిటికీ_Rect_With_Style(కిటికీ, style, styleEx, menu, x, y, వెడల్పు, ఎత్తు, rect_type);
}

bool WIN_Adjust_కిటికీ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT చట్రం_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *videodata = videodevice ? videodevice->అంతర్గత : ఖాళీ;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
    styleEx = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#లేకపోతే
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ఖాళీ);
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_కిటికీ_Rect_Ex(lpRect, style, menu, styleEx);
#లేకపోతే
    ఒకవేళ (WIN_Is_చొప్పున_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ఒకవేళ (!చట్రం_dpi) {
            చట్రం_dpi = videodata->Get_Dpi_For_కిటికీ ? videodata->Get_Dpi_For_కిటికీ(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ఒకవేళ (!videodata->Adjust_కిటికీ_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, చట్రం_dpi)) {
            తిరిగి WIN_సమితి_Error("AdjustWindowRectExForDpi()");
        }
    } లేకపోతే {
        ఒకవేళ (!Adjust_కిటికీ_Rect_Ex(lpRect, style, menu, styleEx)) {
            తిరిగి WIN_సమితి_Error("AdjustWindowRectEx()");
        }
    }
#అయితే_ముగింపు
    తిరిగి true;
}

bool WIN_సమితి_కిటికీ_Position_అంతర్గత(SDL_కిటికీ *కిటికీ, UINT flags, SDL_కిటికీ_Rect rect_type)
{
    SDL_కిటికీ *బిడ్డ_కిటికీ;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    HWND శిఖరం;
    పూర్ణాంకం x, y;
    పూర్ణాంకం w, h;
    bool ఫలితం = true;

    // Figure out what the window area will be
    ఒకవేళ (SDL_ShouldAllowTopmost() && (కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం)) {
        శిఖరం = HWND_TOPMOST;
    } లేకపోతే {
        శిఖరం = HWND_NOTOPMOST;
    }

    WIN_Adjust_కిటికీ_Rect(కిటికీ, &x, &y, &w, &h, rect_type);

    దత్తాంశం->expected_resize = !(flags & SWP_NOSIZE);
    ఒకవేళ (సమితి_కిటికీ_Pos(hwnd, శిఖరం, x, y, w, h, flags) == 0) {
        ఫలితం = WIN_సమితి_Error("SetWindowPos()");
    }
    దత్తాంశం->expected_resize = false;

    // Update any child windows
    కొరకు (బిడ్డ_కిటికీ = కిటికీ->మొదటి_బిడ్డ; బిడ్డ_కిటికీ; బిడ్డ_కిటికీ = బిడ్డ_కిటికీ->తదుపరి_sibling) {
        ఒకవేళ (!బిడ్డ_కిటికీ->అంతర్గత) {
            // This child window is not yet fully initialized.
            కొనసాగు;
        }
        ఒకవేళ (!WIN_సమితి_కిటికీ_Position_అంతర్గత(బిడ్డ_కిటికీ, flags, SDL_WINDOWRECT_CURRENT)) {
            ఫలితం = false;
        }
    }
    తిరిగి ఫలితం;
}

స్థిర SDL_కిటికీ_Erase_Background_బహుళకం Get_Erase_Background_బహుళకం_Hint(శూన్య)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_బహుళకం);
    ఒకవేళ (!hint)
        తిరిగి SDL_ERASEBACKGROUNDMODE_INITIAL;

    ఒకవేళ (SDL_strstr(hint, "never"))
        తిరిగి SDL_ERASEBACKGROUNDMODE_NEVER;

    ఒకవేళ (SDL_strstr(hint, "initial"))
        తిరిగి SDL_ERASEBACKGROUNDMODE_INITIAL;

    ఒకవేళ (SDL_strstr(hint, "always"))
        తిరిగి SDL_ERASEBACKGROUNDMODE_ALWAYS;

    పూర్ణాంకం బహుళకం = SDL_GetStringInteger(hint, 1);
    ఒకవేళ (బహుళకం < 0 || బహుళకం > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        తిరిగి SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    తిరిగి (SDL_కిటికీ_Erase_Background_బహుళకం)బహుళకం;
}

స్థిర bool అమరిక_కిటికీ_దత్తాంశం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, HWND hwnd, HWND మాతృ)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    // Allocate the window data
    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }
    దత్తాంశం->కిటికీ = కిటికీ;
    దత్తాంశం->hwnd = hwnd;
    దత్తాంశం->మాతృ = మాతృ;
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    దత్తాంశం->hdc = (HDC)దత్తాంశం->hwnd;
#లేకపోతే
    దత్తాంశం->hdc = GetDC(hwnd);
#అయితే_ముగింపు
    దత్తాంశం->hinstance = (HINSTANCE)Get_కిటికీ_Long_Ptr(hwnd, GWLP_HINSTANCE);
    దత్తాంశం->mouse_button_flags = (WPARAM)-1;
    దత్తాంశం->చివరి_సూచిక_update = (LPARAM)-1;
    దత్తాంశం->videodata = videodata;
    దత్తాంశం->initializing = true;
    దత్తాంశం->hint_erase_background_బహుళకం = Get_Erase_Background_బహుళకం_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    దత్తాంశం->cursor_ctrlock_rect.ఎడమ   = 0 - remote_desktop_adjustment;
    దత్తాంశం->cursor_ctrlock_rect.శిఖరం    = 0;
    దత్తాంశం->cursor_ctrlock_rect.కుడి  = 1 + remote_desktop_adjustment;
    దత్తాంశం->cursor_ctrlock_rect.bottom = 1;
#అయితే_ముగింపు

    ఒకవేళ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        దత్తాంశం->copybits_flag = 0;
    } లేకపోతే {
        దత్తాంశం->copybits_flag = SWP_NOCOPYBITS;
    }

#నిర్వచితమైతే HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", దత్తాంశం->scaling_dpi);
#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ఒకవేళ (!సమితి_Prop(hwnd, పాఠ్యం_2("SDL_WindowData"), దత్తాంశం)) {
        ReleaseDC(hwnd, దత్తాంశం->hdc);
        SDL_free(దత్తాంశం);
        తిరిగి WIN_సమితి_Error("SetProp() failed");
    }
#అయితే_ముగింపు

    కిటికీ->అంతర్గత = దత్తాంశం;

    // Set up the window proc function
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
#నిర్వచితమైతే GWLP_WNDPROC
        దత్తాంశం->wndproc = (WNDPROC)Get_కిటికీ_Long_Ptr(hwnd, GWLP_WNDPROC);
        ఒకవేళ (దత్తాంశం->wndproc != WIN_కిటికీ_Proc) {
            సమితి_కిటికీ_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_కిటికీ_Proc);
        }
#లేకపోతే
        దత్తాంశం->wndproc = (WNDPROC)Get_కిటికీ_Long(hwnd, GWL_WNDPROC);
        ఒకవేళ (దత్తాంశం->wndproc != WIN_కిటికీ_Proc) {
            సమితి_కిటికీ_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_కిటికీ_Proc);
        }
#అయితే_ముగింపు
    } లేకపోతే {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
        ఒకవేళ (style & WS_VISIBLE) {
            కిటికీ->flags &= ~SDL_కిటికీ_HIDDEN;
        } లేకపోతే {
            కిటికీ->flags |= SDL_కిటికీ_HIDDEN;
        }
        ఒకవేళ (style & WS_POPUP) {
            కిటికీ->flags |= SDL_కిటికీ_BORDERLESS;
        } లేకపోతే {
            కిటికీ->flags &= ~SDL_కిటికీ_BORDERLESS;
        }
        ఒకవేళ (style & WS_THICKFRAME) {
            కిటికీ->flags |= SDL_కిటికీ_RESIZABLE;
        } లేకపోతే ఒకవేళ (!(style & WS_POPUP)) {
            కిటికీ->flags &= ~SDL_కిటికీ_RESIZABLE;
        }
#నిర్వచితమైతే WS_MAXIMIZE
        ఒకవేళ (style & WS_MAXIMIZE) {
            కిటికీ->flags |= SDL_కిటికీ_MAXIMIZED;
        } లేకపోతే
#అయితే_ముగింపు
        {
            కిటికీ->flags &= ~SDL_కిటికీ_MAXIMIZED;
        }
#నిర్వచితమైతే WS_MINIMIZE
        ఒకవేళ (style & WS_MINIMIZE) {
            కిటికీ->flags |= SDL_కిటికీ_MINIMIZED;
        } లేకపోతే
#అయితే_ముగింపు
        {
            కిటికీ->flags &= ~SDL_కిటికీ_MINIMIZED;
        }
    }
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        RECT rect;
        ఒకవేళ (GetClientRect(hwnd, &rect) && WIN_కిటికీ_Rect_Valid(&rect)) {
            పూర్ణాంకం w = rect.కుడి;
            పూర్ణాంకం h = rect.bottom;

            ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
                కిటికీ->floating.w = కిటికీ->windowed.w = కిటికీ->w = w;
                కిటికీ->floating.h = కిటికీ->windowed.h = కిటికీ->h = h;
            } లేకపోతే ఒకవేళ ((కిటికీ->windowed.w && కిటికీ->windowed.w != w) || (కిటికీ->windowed.h && కిటికీ->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                పూర్ణాంకం x, y;
                // Figure out what the window area will be
                WIN_Adjust_కిటికీ_Rect(కిటికీ, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                దత్తాంశం->expected_resize = true;
                సమితి_కిటికీ_Pos(hwnd, ఖాళీ, x, y, w, h, దత్తాంశం->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                దత్తాంశం->expected_resize = false;
            } లేకపోతే {
                కిటికీ->w = w;
                కిటికీ->h = h;
            }
        }
    }
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        బిందువు_2 బిందువు;
        బిందువు.x = 0;
        బిందువు.y = 0;
        ఒకవేళ (Client_గమ్యం_Screen(hwnd, &బిందువు)) {
            ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
                కిటికీ->floating.x = కిటికీ->windowed.x = బిందువు.x;
                కిటికీ->floating.y = కిటికీ->windowed.y = బిందువు.y;
            }
            కిటికీ->x = బిందువు.x;
            కిటికీ->y = బిందువు.y;
        }
    }

    WIN_Update_కిటికీ_ICCProfile(కిటికీ, false);
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    కిటికీ->flags |= SDL_కిటికీ_ఆదానం_FOCUS;
    SDL_సమితి_Keyboard_Focus(కిటికీ);
#లేకపోతే
    ఒకవేళ (GetFocus() == hwnd) {
        కిటికీ->flags |= SDL_కిటికీ_ఆదానం_FOCUS;
        SDL_సమితి_Keyboard_Focus(కిటికీ);
        WIN_UpdateClipCursor(కిటికీ);
    }
#అయితే_ముగింపు

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం) {
        WIN_సమితి_కిటికీ_Always_On_శిఖరం(_this, కిటికీ, true);
    } లేకపోతే {
        WIN_సమితి_కిటికీ_Always_On_శిఖరం(_this, కిటికీ, false);
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ఒకవేళ (videodata->రిజిస్టరు_Touch_కిటికీ) {
        videodata->రిజిస్టరు_Touch_కిటికీ(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం->మాతృ && !కిటికీ->మాతృ) {
        దత్తాంశం->destroy_మాతృ_with_కిటికీ = true;
    }

    దత్తాంశం->initializing = false;

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        పూర్ణాంకం titleLen;
        bool isstack;

        titleLen = Get_కిటికీ_పాఠ్యం_నిడివి(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ఒకవేళ (title) {
            titleLen = Get_కిటికీ_పాఠ్యం(hwnd, title, titleLen + 1);
        } లేకపోతే {
            titleLen = 0;
        }
        ఒకవేళ (titleLen > 0) {
            కిటికీ->title = WIN_String_గమ్యం_UTF8(title);
        }
        ఒకవేళ (title) {
            SDL_small_free(title, isstack);
        }
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WIN32_HWND_సూచిక, దత్తాంశం->hwnd);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WIN32_HDC_సూచిక, దత్తాంశం->hdc);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WIN32_INSTANCE_సూచిక, దత్తాంశం->hinstance);

    // All done!
    తిరిగి true;
}

స్థిర శూన్య Cleanup_కిటికీ_దత్తాంశం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం) {
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ఒకవేళ (దత్తాంశం->drop_లక్ష్యం) {
            WIN_AcceptDragAndDrop(కిటికీ, false);
        }
        SDL_free(దత్తాంశం->ICMFileName);
        ఒకవేళ (దత్తాంశం->keyboard_hook) {
            UnhookWindowsHookEx(దత్తాంశం->keyboard_hook);
        }
        ఒకవేళ (దత్తాంశం->hicon) {
            DestroyIcon(దత్తాంశం->hicon);
        }
        ReleaseDC(దత్తాంశం->hwnd, దత్తాంశం->hdc);
        RemoveProp(దత్తాంశం->hwnd, పాఠ్యం_2("SDL_WindowData"));
#అయితే_ముగింపు
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
            Destroy_కిటికీ(దత్తాంశం->hwnd);
            ఒకవేళ (దత్తాంశం->destroy_మాతృ_with_కిటికీ && దత్తాంశం->మాతృ) {
                Destroy_కిటికీ(దత్తాంశం->మాతృ);
            }
        } లేకపోతే {
            // Restore any original event handler...
            ఒకవేళ (దత్తాంశం->wndproc) {
#నిర్వచితమైతే GWLP_WNDPROC
                సమితి_కిటికీ_Long_Ptr(దత్తాంశం->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)దత్తాంశం->wndproc);
#లేకపోతే
                సమితి_కిటికీ_Long(దత్తాంశం->hwnd, GWL_WNDPROC,
                              (LONG_PTR)దత్తాంశం->wndproc);
#అయితే_ముగింపు
            }
        }
        SDL_free(దత్తాంశం);
    }
    కిటికీ->అంతర్గత = ఖాళీ;
}

స్థిర శూన్య WIN_ConstrainPopup(SDL_కిటికీ *కిటికీ, bool output_గమ్యం_pending)
{
    // Possibly clamp popup windows to the output borders
    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        SDL_కిటికీ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        పూర్ణాంకం abs_x = కిటికీ->చివరి_position_pending ? కిటికీ->pending.x : కిటికీ->floating.x;
        పూర్ణాంకం abs_y = కిటికీ->చివరి_position_pending ? కిటికీ->pending.y : కిటికీ->floating.y;
        స్థిరరాశి పూర్ణాంకం వెడల్పు = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->floating.w;
        స్థిరరాశి పూర్ణాంకం ఎత్తు = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->floating.h;
        పూర్ణాంకం స్థానభ్రంశం_x = 0, స్థానభ్రంశం_y = 0;

        ఒకవేళ (కిటికీ->constrain_popup) {
            // Calculate the total offset from the parents
            కొరకు (w = కిటికీ->మాతృ; SDL_కిటికీ_IS_POPUP(w); w = w->మాతృ) {
                స్థానభ్రంశం_x += w->x;
                స్థానభ్రంశం_y += w->y;
            }

            స్థానభ్రంశం_x += w->x;
            స్థానభ్రంశం_y += w->y;
            abs_x += స్థానభ్రంశం_x;
            abs_y += స్థానభ్రంశం_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_కిటికీ(w);
            SDL_GetDisplayBounds(displayID, &rect);
            ఒకవేళ (abs_x + వెడల్పు > rect.x + rect.w) {
                abs_x -= (abs_x + వెడల్పు) - (rect.x + rect.w);
            }
            ఒకవేళ (abs_y + ఎత్తు > rect.y + rect.h) {
                abs_y -= (abs_y + ఎత్తు) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ఒకవేళ (output_గమ్యం_pending) {
            కిటికీ->pending.x = abs_x - స్థానభ్రంశం_x;
            కిటికీ->pending.y = abs_y - స్థానభ్రంశం_y;
            కిటికీ->pending.w = వెడల్పు;
            కిటికీ->pending.h = ఎత్తు;
        } లేకపోతే {
            కిటికీ->floating.x = abs_x - స్థానభ్రంశం_x;
            కిటికీ->floating.y = abs_y - స్థానభ్రంశం_y;
            కిటికీ->floating.w = వెడల్పు;
            కిటికీ->floating.h = ఎత్తు;
        }
    }
}

స్థిర శూన్య WIN_సమితి_Keyboard_Focus(SDL_కిటికీ *కిటికీ, bool సమితి_చురుకైన_focus)
{
    SDL_కిటికీ *toplevel = కిటికీ;

    // Find the topmost parent
    అయితే (SDL_కిటికీ_IS_POPUP(toplevel)) {
        toplevel = toplevel->మాతృ;
    }

    toplevel->keyboard_focus = కిటికీ;

    ఒకవేళ (సమితి_చురుకైన_focus && !కిటికీ->is_hiding && !కిటికీ->is_destroying) {
        SDL_సమితి_Keyboard_Focus(కిటికీ);
    }
}

bool WIN_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    HWND hwnd = (HWND)SDL_Get_సూచిక_Property(create_props, SDL_PROP_కిటికీ_CREATE_WIN32_HWND_సూచిక, SDL_Get_సూచిక_Property(create_props, "sdl2-compat.external_window", ఖాళీ));
    HWND మాతృ = ఖాళీ;
    ఒకవేళ (hwnd) {
        కిటికీ->flags |= SDL_కిటికీ_EXTERNAL;

        ఒకవేళ (!అమరిక_కిటికీ_దత్తాంశం(_this, కిటికీ, hwnd, మాతృ)) {
            తిరిగి false;
        }
    } లేకపోతే {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        పూర్ణాంకం x, y;
        పూర్ణాంకం w, h;

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_UTILITY) {
            మాతృ = Create_కిటికీ(SDL_Appname, పాఠ్యం_2(""), STYLE_BASIC, 0, 0, 32, 32, ఖాళీ, ఖాళీ, SDL_Instance, ఖాళీ);
        } లేకపోతే ఒకవేళ (కిటికీ->మాతృ) {
            మాతృ = కిటికీ->మాతృ->అంతర్గత->hwnd;
        }

        style |= Get_కిటికీ_Style(కిటికీ);
        styleEx |= (DWORD)SDL_Get_సంఖ్య_Property(create_props, SDL_PROP_కిటికీ_CREATE_WIN32_STYLE_EX_సంఖ్య, Get_కిటికీ_Style_Ex(కిటికీ));

        // Figure out what the window area will be
        WIN_ConstrainPopup(కిటికీ, false);
        WIN_Adjust_కిటికీ_Rect_With_Style(కిటికీ, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_కిటికీ_Ex(styleEx, SDL_Appname, పాఠ్యం_2(""), style,
                              x, y, w, h, మాతృ, ఖాళీ, SDL_Instance, ఖాళీ);
        ఒకవేళ (!hwnd) {
            తిరిగి WIN_సమితి_Error("Couldn't create window");
        }

        WIN_Update_Dark_బహుళకం_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ఒకవేళ (!అమరిక_కిటికీ_దత్తాంశం(_this, కిటికీ, hwnd, మాతృ)) {
            Destroy_కిటికీ(hwnd);
            ఒకవేళ (మాతృ) {
                Destroy_కిటికీ(మాతృ);
            }
            తిరిగి false;
        }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_పాఠ్యం_ఆదానం(_this, కిటికీ);
#అయితే_ముగింపు

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        సమితి_కిటికీ_Pos(hwnd, ఖాళీ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            కిటికీ->flags &= ~SDL_కిటికీ_HIDDEN;
            Show_కిటికీ(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) {
        ఒకవేళ (videodata->Dwm_Enable_Blur_Behind_కిటికీ) {
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
            videodata->Dwm_Enable_Blur_Behind_కిటికీ(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_సూచిక_Property(create_props, SDL_PROP_కిటికీ_CREATE_WIN32_PIXEL_FORMAT_HWND_సూచిక, ఖాళీ);
    ఒకవేళ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        పూర్ణాంకం pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, పరిమాణం(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ఒకవేళ (!సమితి_Pixel_Format(కిటికీ->అంతర్గత->hdc, pixel_format, &pfd)) {
            WIN_Destroy_కిటికీ(_this, కిటికీ);
            తిరిగి WIN_సమితి_Error("SetPixelFormat()");
        }
    } లేకపోతే {
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
            తిరిగి true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#నిర్వచితమైతే SDL_VIDEO_OPENGL_ES2
        ఒకవేళ ((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_దత్తాంశం || WIN_GL_UseEGL(_this))
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_WGL
        ) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
            ఒకవేళ (!WIN_GLES_అమరిక_కిటికీ(_this, కిటికీ)) {
                WIN_Destroy_కిటికీ(_this, కిటికీ);
                తిరిగి false;
            }
            తిరిగి true;
#లేకపోతే
            తిరిగి SDL_సమితి_Error("Could not create GLES window surface (EGL support not configured)");
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_EGL
        }
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_ES2

#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
        ఒకవేళ (!WIN_GL_అమరిక_కిటికీ(_this, కిటికీ)) {
            WIN_Destroy_కిటికీ(_this, కిటికీ);
            తిరిగి false;
        }
#లేకపోతే
        తిరిగి SDL_సమితి_Error("Could not create GL window (WGL support not configured)");
#అయితే_ముగింపు
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    తిరిగి true;
}

శూన్య WIN_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    LPTSTR title = WIN_UTF8_గమ్యం_String(కిటికీ->title);
    సమితి_కిటికీ_పాఠ్యం(hwnd, title);
    SDL_free(title);
#అయితే_ముగింపు
}

bool WIN_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    HICON hicon = ఖాళీ;
    BYTE *icon_bmp;
    పూర్ణాంకం icon_len, ముసుగు_len, అడ్డువరుస_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool ఫలితం = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_సమయం_ASSERT(WIN_సమితి_కిటికీ_Icon_ఉపయోగిస్తుంది_BITMAPINFOHEADER_గమ్యం_prepare_an_ICONIMAGE, పరిమాణం(BITMAPINFOHEADER) == 40);
    ముసుగు_len = (icon->h * (icon->w + 7) / 8);
    icon_len = పరిమాణం(BITMAPINFOHEADER) + icon->h * icon->w * పరిమాణం(Uint32) + ముసుగు_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ఒకవేళ (!icon_bmp) {
        తిరిగి false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_కొలత = SDL_Swap32LE(పరిమాణం(BITMAPINFOHEADER));
    bmi->bi_వెడల్పు = SDL_Swap32LE(icon->w);
    bmi->bi_ఎత్తు = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_బిట్టు_లెక్క = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_కొలత_Image = SDL_Swap32LE(icon->h * icon->w * పరిమాణం(Uint32));
    bmi->bi_XPels_చొప్పున_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_చొప్పున_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_వాడిన = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[పరిమాణం(BITMAPINFOHEADER)];
    అడ్డువరుస_len = icon->w * పరిమాణం(Uint32);
    y = icon->h;
    అయితే (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, అడ్డువరుస_len);
        dst += అడ్డువరుస_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - ముసుగు_len, 0xFF, ముసుగు_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ఒకవేళ (!hicon) {
        తిరిగి SDL_సమితి_Error("SetWindowIcon() failed, error %08X", (గుర్తులేని పూర్ణాంకం)Get_చివరి_Error());
    }

    ఒకవేళ (దత్తాంశం->hicon) {
        DestroyIcon(దత్తాంశం->hicon);
    }
    దత్తాంశం->hicon = hicon;

    // Set the icon for the window
    Send_సందేశం(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_సందేశం(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    తిరిగి ఫలితం;
#లేకపోతే
    తిరిగి SDL_Unsupported();
#అయితే_ముగింపు
}

bool WIN_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        ఒకవేళ (!(కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED))) {
            WIN_ConstrainPopup(కిటికీ, true);
            తిరిగి WIN_సమితి_కిటికీ_Position_అంతర్గత(కిటికీ,
                                                 కిటికీ->అంతర్గత->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } లేకపోతే {
        తిరిగి SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_ENTER, true);
    }

    తిరిగి true;
}

శూన్య WIN_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (!(కిటికీ->flags & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED))) {
        WIN_సమితి_కిటికీ_Position_అంతర్గత(కిటికీ, కిటికీ->అంతర్గత->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } లేకపోతే {
        // Can't resize the window
        కిటికీ->చివరి_కొలత_pending = false;
    }
}

bool WIN_Get_కిటికీ_Borders_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి)
{
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *శిఖరం = rcClient.శిఖరం;
    *ఎడమ = rcClient.ఎడమ;
    *bottom = rcClient.bottom;
    *కుడి = rcClient.కుడి;

    తిరిగి true;
#లేకపోతే  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    RECT rcClient, rc_కిటికీ;
    బిందువు_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ఒకవేళ (!GetClientRect(hwnd, &rcClient)) {
        తిరిగి SDL_సమితి_Error("GetClientRect() failed, error %08X", (గుర్తులేని పూర్ణాంకం)Get_చివరి_Error());
    }

    ఒకవేళ (!Get_కిటికీ_Rect(hwnd, &rc_కిటికీ)) {
        తిరిగి SDL_సమితి_Error("GetWindowRect() failed, error %08X", (గుర్తులేని పూర్ణాంకం)Get_చివరి_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_కిటికీ.శిఖరం;
    ptDiff.x = rc_కిటికీ.ఎడమ;

    ఒకవేళ (!Screen_గమ్యం_Client(hwnd, &ptDiff)) {
        తిరిగి SDL_సమితి_Error("ScreenToClient() failed, error %08X", (గుర్తులేని పూర్ణాంకం)Get_చివరి_Error());
    }

    rc_కిటికీ.శిఖరం = ptDiff.y;
    rc_కిటికీ.ఎడమ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_కిటికీ.bottom;
    ptDiff.x = rc_కిటికీ.కుడి;

    ఒకవేళ (!Screen_గమ్యం_Client(hwnd, &ptDiff)) {
        తిరిగి SDL_సమితి_Error("ScreenToClient() failed, error %08X", (గుర్తులేని పూర్ణాంకం)Get_చివరి_Error());
    }

    rc_కిటికీ.bottom = ptDiff.y;
    rc_కిటికీ.కుడి = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *శిఖరం = rcClient.శిఖరం - rc_కిటికీ.శిఖరం;
    *ఎడమ = rcClient.ఎడమ - rc_కిటికీ.ఎడమ;
    *bottom = rc_కిటికీ.bottom - rcClient.bottom;
    *కుడి = rc_కిటికీ.కుడి - rcClient.కుడి;

    తిరిగి true;
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

శూన్య WIN_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    RECT rect;

    ఒకవేళ (GetClientRect(hwnd, &rect) && WIN_కిటికీ_Rect_Valid(&rect)) {
        *w = rect.కుడి;
        *h = rect.bottom;
    } లేకపోతే ఒకవేళ (కిటికీ->చివరి_pixel_w && కిటికీ->చివరి_pixel_h) {
        *w = కిటికీ->చివరి_pixel_w;
        *h = కిటికీ->చివరి_pixel_h;
    } లేకపోతే {
        // Probably created minimized, use the restored size
        *w = కిటికీ->floating.w;
        *h = కిటికీ->floating.h;
    }
}

శూన్య WIN_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_కిటికీ_ACTIVATE_WHEN_SHOWN, true);

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        // Update our position in case our parent moved while we were hidden
        WIN_సమితి_కిటికీ_Position(_this, కిటికీ);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ఒకవేళ (కిటికీ->pending_flags & SDL_కిటికీ_FULLSCREEN) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_BORDERLESS)) {
            కిటికీ->flags |= SDL_కిటికీ_BORDERLESS;
            style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_ముసుగు;
            style |= Get_కిటికీ_Style(కిటికీ);
            సమితి_కిటికీ_Long(hwnd, GWL_STYLE, style);
            కిటికీ->flags &= ~SDL_కిటికీ_BORDERLESS;
        }
    }
    style = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);
    ఒకవేళ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    దత్తాంశం->showing_కిటికీ = true;
    ఒకవేళ (bActivate) {
        Show_కిటికీ(hwnd, SW_SHOW);
    } లేకపోతే {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        సమితి_కిటికీ_Pos(hwnd, ఖాళీ, 0, 0, 0, 0, కిటికీ->అంతర్గత->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    దత్తాంశం->showing_కిటికీ = false;

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE) && bActivate) {
        WIN_సమితి_Keyboard_Focus(కిటికీ, true);
    }
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        WIN_సమితి_కిటికీ_Modal(_this, కిటికీ, true);
    }
}

శూన్య WIN_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        WIN_సమితి_కిటికీ_Modal(_this, కిటికీ, false);
    }

    Show_కిటికీ(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
        SDL_కిటికీ *new_focus;
        స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(కిటికీ, &new_focus);
        WIN_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
    }
}

శూన్య WIN_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* If desired, raise the window more forcefully.
     * Technique taken from http://stackoverflow.com/questions/916259/ .
     * Specifically, http://stackoverflow.com/a/34414846 .
     *
     * The issue is that Microsoft has gone through a lot of trouble to make it
     * nearly impossible to programmatically move a window to the foreground,
     * for "security" reasons. Apparently, the following song-and-dance gets
     * around their objections. */
    bool bForce = SDL_GetHintBoolean(SDL_HINT_FORCE_RAISEWINDOW, false);
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_కిటికీ_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = ఖాళీ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    ఒకవేళ (bForce) {
        hCurWnd = Get_Foreground_కిటికీ();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_కిటికీ_Thread_Process_Id(hCurWnd, ఖాళీ);
        Show_కిటికీ(hwnd, SW_RESTORE);
        Attach_Thread_ఆదానం(dwCurID, dwMyID, TRUE);
        సమితి_కిటికీ_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ఒకవేళ (!SDL_ShouldAllowTopmost() || !(కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం)) {
            సమితి_కిటికీ_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ఒకవేళ (bActivate) {
        సమితి_Foreground_కిటికీ(hwnd);
        ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
            WIN_సమితి_Keyboard_Focus(కిటికీ, కిటికీ->మాతృ == SDL_GetKeyboardFocus());
        }
    } లేకపోతే {
        సమితి_కిటికీ_Pos(hwnd, HWND_శిఖరం, 0, 0, 0, 0, దత్తాంశం->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ఒకవేళ (bForce) {
        Attach_Thread_ఆదానం(dwCurID, dwMyID, FALSE);
        సమితి_Focus(hwnd);
        సమితి_చురుకైన_కిటికీ(hwnd);
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

శూన్య WIN_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        HWND hwnd = దత్తాంశం->hwnd;
        దత్తాంశం->expected_resize = true;
        Show_కిటికీ(hwnd, SW_MAXIMIZE);
        దత్తాంశం->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ఒకవేళ (కిటికీ->max_w || కిటికీ->max_h) {
            పూర్ణాంకం fx, fy, fw, fh;

            కిటికీ->windowed.w = కిటికీ->max_w ? SDL_min(కిటికీ->w, కిటికీ->max_w) : కిటికీ->windowed.w;
            కిటికీ->windowed.h = కిటికీ->max_h ? SDL_min(కిటికీ->h, కిటికీ->max_h) : కిటికీ->windowed.h;
            WIN_Adjust_కిటికీ_Rect(కిటికీ, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            దత్తాంశం->expected_resize = true;
            సమితి_కిటికీ_Pos(hwnd, HWND_శిఖరం, fx, fy, fw, fh, దత్తాంశం->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            దత్తాంశం->expected_resize = false;
        }
    } లేకపోతే {
        దత్తాంశం->windowed_బహుళకం_was_maximized = true;
    }
}

శూన్య WIN_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    HWND hwnd = కిటికీ->అంతర్గత->hwnd;
    Show_కిటికీ(hwnd, SW_MINIMIZE);
}

శూన్య WIN_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    DWORD style;

    style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ముసుగు;
    style |= Get_కిటికీ_Style(కిటికీ);

    దత్తాంశం->లోపల_border_change = true;
    సమితి_కిటికీ_Long(hwnd, GWL_STYLE, style);
    WIN_సమితి_కిటికీ_Position_అంతర్గత(కిటికీ, దత్తాంశం->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    దత్తాంశం->లోపల_border_change = false;
}

శూన్య WIN_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    DWORD style;

    style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ముసుగు;
    style |= Get_కిటికీ_Style(కిటికీ);

    సమితి_కిటికీ_Long(hwnd, GWL_STYLE, style);
}

శూన్య WIN_సమితి_కిటికీ_Always_On_శిఖరం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం)
{
    WIN_సమితి_కిటికీ_Position_అంతర్గత(కిటికీ, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

శూన్య WIN_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        ఒకవేళ (!దత్తాంశం->showing_కిటికీ || కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED)) {
            HWND hwnd = దత్తాంశం->hwnd;
            దత్తాంశం->expected_resize = true;
            Show_కిటికీ(hwnd, SW_RESTORE);
            దత్తాంశం->expected_resize = false;
        }
    } లేకపోతే {
        దత్తాంశం->windowed_బహుళకం_was_maximized = false;
    }
}

స్థిర శూన్య WIN_Update_మూల_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_కిటికీ_మూల_PREFERENCE మూల_Pref)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    ఒకవేళ (videodata->Dwm_సమితి_కిటికీ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_సమితి_కిటికీ_Attribute(hwnd, DWMWA_కిటికీ_మూల_PREFERENCE, &మూల_Pref, పరిమాణం(మూల_Pref));
    }
#అయితే_ముగింపు
}

స్థిర శూన్య WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    ఒకవేళ (videodata->Dwm_సమితి_కిటికీ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_సమితి_కిటికీ_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, పరిమాణం(colorRef));
    }
#అయితే_ముగింపు
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_ఫలితం WIN_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం ? దత్తాంశం->hwnd : ఖాళీ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND శిఖరం;
    పూర్ణాంకం x, y;
    పూర్ణాంకం w, h;
    bool enterMaximized = false;

#నిర్వచితమైతే HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (పూర్ణాంకం)fullscreen);
#అయితే_ముగింపు

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && !fullscreen) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    ఒకవేళ (SDL_ShouldAllowTopmost() && (కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం)) {
        శిఖరం = HWND_TOPMOST;
    } లేకపోతే {
        శిఖరం = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_కొలత = పరిమాణం(MONITORINFO);
    ఒకవేళ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_సమితి_Error("GetMonitorInfo failed");
        తిరిగి SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_కిటికీ_Event(కిటికీ, fullscreen ? SDL_EVENT_కిటికీ_ENTER_FULLSCREEN : SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
    style = Get_కిటికీ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ముసుగు;
    style |= Get_కిటికీ_Style(కిటికీ);
    styleEx = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);

    ఒకవేళ (fullscreen) {
        x = minfo.rcMonitor.ఎడమ;
        y = minfo.rcMonitor.శిఖరం;
        w = minfo.rcMonitor.కుడి - minfo.rcMonitor.ఎడమ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.శిఖరం;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ఒకవేళ (style & WS_MAXIMIZE) {
            దత్తాంశం->windowed_బహుళకం_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_మూల_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } లేకపోతే {
        BOOL menu;

        WIN_Update_మూల_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ఒకవేళ (దత్తాంశం->windowed_బహుళకం_was_maximized && !దత్తాంశం->లోపల_కిటికీ_deactivation) {
            enterMaximized = true;
            దత్తాంశం->disable_move_కొలత_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ఖాళీ);
        WIN_Adjust_కిటికీ_Rect_With_Style(కిటికీ, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        దత్తాంశం->windowed_బహుళకం_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        ఒకవేళ (enterMaximized) {
            స్థిరరాశి SDL_బిందువు windowed_బిందువు = { కిటికీ->windowed.x, కిటికీ->windowed.y };
            స్థిరరాశి SDL_బిందువు floating_బిందువు = { కిటికీ->floating.x, కిటికీ->floating.y };
            స్థిరరాశి SDL_DisplayID floating_display = SDL_Get_Display_For_బిందువు(&floating_బిందువు);
            స్థిరరాశి SDL_DisplayID windowed_display = SDL_Get_Display_For_బిందువు(&windowed_బిందువు);

            ఒకవేళ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ఒకవేళ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } లేకపోతే {
                    x = bounds.x;
                }
                ఒకవేళ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } లేకపోతే {
                    y = bounds.y;
                }
            }
        }
    }

    /* Always reset the window to the base floating size before possibly re-applying the maximized state,
     * otherwise, the base floating size can seemingly be lost in some cases.
     */
    సమితి_కిటికీ_Long(hwnd, GWL_STYLE, style);
    దత్తాంశం->expected_resize = true;
    సమితి_కిటికీ_Pos(hwnd, శిఖరం, x, y, w, h, దత్తాంశం->copybits_flag | SWP_NOACTIVATE);
    దత్తాంశం->expected_resize = false;
    దత్తాంశం->disable_move_కొలత_events = false;

    ఒకవేళ (enterMaximized) {
        WIN_Maximize_కిటికీ(_this, కిటికీ);
    }

    ఒకవేళ (!fullscreen && దత్తాంశం && దత్తాంశం->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_సందేశం(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_సందేశం(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)దత్తాంశం->hicon);
    }

#నిర్వచితమైతే HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (పూర్ణాంకం)fullscreen, x, y, w, h);
#అయితే_ముగింపు

#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    తిరిగి SDL_FULLSCREEN_SUCCEEDED;
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
శూన్య WIN_Update_కిటికీ_ICCProfile(SDL_కిటికీ *కిటికీ, bool send_event)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);

    ఒకవేళ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ఖాళీ, ఖాళీ, ఖాళీ);
        ఒకవేళ (hdc) {
            WCHAR fileName[MAX_మార్గం];
            DWORD file_Name_కొలత = SDL_arraysize(fileName);
            ఒకవేళ (GetICMProfileW(hdc, &file_Name_కొలత, fileName)) {
                // fileNameSize includes '\0' on return
                ఒకవేళ (!దత్తాంశం->ICMFileName ||
                    SDL_wcscmp(దత్తాంశం->ICMFileName, fileName) != 0) {
                    SDL_free(దత్తాంశం->ICMFileName);
                    దత్తాంశం->ICMFileName = SDL_wcsdup(fileName);
                    ఒకవేళ (send_event) {
                        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_ICCPROF_మారింది, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

శూన్య *WIN_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    అక్షరం *filename_utf8;
    శూన్య *icc_Profile_దత్తాంశం = ఖాళీ;

    filename_utf8 = WIN_String_గమ్యం_UTF8_W(దత్తాంశం->ICMFileName);
    ఒకవేళ (filename_utf8) {
        icc_Profile_దత్తాంశం = SDL_ఎక్కించు_File(filename_utf8, కొలత);
        ఒకవేళ (!icc_Profile_దత్తాంశం) {
            SDL_సమితి_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    తిరిగి icc_Profile_దత్తాంశం;
}

స్థిర శూన్య WIN_GrabKeyboard(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HMODULE module;

    ఒకవేళ (దత్తాంశం->keyboard_hook) {
        తిరిగి;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ఒకవేళ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_చిరునామా,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        తిరిగి;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ఒకవేళ (!GetKeyboardState(దత్తాంశం->videodata->pre_hook_కీలకం_state)) {
        తిరిగి;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    దత్తాంశం->keyboard_hook = సమితి_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

శూన్య WIN_UngrabKeyboard(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం->keyboard_hook) {
        UnhookWindowsHookEx(దత్తాంశం->keyboard_hook);
        దత్తాంశం->keyboard_hook = ఖాళీ;
    }
}

bool WIN_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    WIN_UpdateClipCursor(కిటికీ);
    తిరిగి true;
}

bool WIN_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    WIN_UpdateClipCursor(కిటికీ);
    తిరిగి true;
}

bool WIN_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    ఒకవేళ (grabbed) {
        WIN_GrabKeyboard(కిటికీ);
    } లేకపోతే {
        WIN_UngrabKeyboard(కిటికీ);
    }

    తిరిగి true;
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

శూన్య WIN_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    Cleanup_కిటికీ_దత్తాంశం(_this, కిటికీ);
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
శూన్య WIN_On_కిటికీ_Enter(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (!దత్తాంశం || !దత్తాంశం->hwnd) {
        // The window wasn't fully initialized
        తిరిగి;
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం) {
        WIN_సమితి_కిటికీ_Position_అంతర్గత(కిటికీ, దత్తాంశం->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

స్థిర BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    తిరిగి GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_గమ్యం_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_గమ్యం_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

శూన్య WIN_Unclip_Cursor_For_కిటికీ(SDL_కిటికీ *కిటికీ) {
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    RECT rect;
    ఒకవేళ (GetClipCursor(&rect) && SDL_memcmp(&rect, &దత్తాంశం->cursor_clipped_rect, పరిమాణం(rect)) == 0) {
        ClipCursor(ఖాళీ);
        SDL_zero(దత్తాంశం->cursor_clipped_rect);
    }
}

శూన్య WIN_UpdateClipCursor(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Video_దత్తాంశం *videodata = దత్తాంశం->videodata;
    ఒకవేళ (దత్తాంశం->లోపల_title_click || దత్తాంశం->focus_click_pending || దత్తాంశం->postpone_clipcursor) {
        తిరిగి;
    }

    SDL_Rect mouse_rect = కిటికీ->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS);
    bool win_is_grabbed = (కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED);
    bool win_లోపల_relmode = (కిటికీ->flags & SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం);
    bool cursor_confine = win_లోపల_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ఒకవేళ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ఒకవేళ (!GetClipCursor(&current)) {
            తిరిగి;
        }
        ఒకవేళ (videodevice && (
            current.ఎడమ != videodevice->desktop_bounds.x ||
            current.శిఖరం  != videodevice->desktop_bounds.y
        )) {
            బిందువు_2 మొదటి, రెండవ;
            మొదటి.x  = current.ఎడమ;
            మొదటి.y  = current.శిఖరం;
            రెండవ.x = current.కుడి  - 1;
            రెండవ.y = current.bottom - 1;
            ఒకవేళ (!Pt_లోపల_Rect(&దత్తాంశం->cursor_clipped_rect, మొదటి) ||
                !Pt_లోపల_Rect(&దత్తాంశం->cursor_clipped_rect, రెండవ)) {
                తిరిగి;
            }
        }
        ClipCursor(ఖాళీ);
        SDL_zero(దత్తాంశం->cursor_clipped_rect);
        తిరిగి;
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
    bool తాళం_గమ్యం_ctr = (mouse->relative_బహుళకం && mouse->relative_బహుళకం_center);

    RECT client;
    ఒకవేళ (!GetClientScreenRect(దత్తాంశం->hwnd, &client)) {
        తిరిగి;
    }

    RECT లక్ష్యం = client;
    ఒకవేళ (తాళం_గమ్యం_ctr) {
        LONG cx = (client.ఎడమ + client.కుడి ) / 2;
        LONG cy = (client.శిఖరం  + client.bottom) / 2;
        లక్ష్యం = దత్తాంశం->cursor_ctrlock_rect;
        లక్ష్యం.ఎడమ   += cx;
        లక్ష్యం.కుడి  += cx;
        లక్ష్యం.శిఖరం    += cy;
        లక్ష్యం.bottom += cy;
    } లేకపోతే ఒకవేళ (win_mouse_rect) {
        RECT custom, overlap;
        custom.ఎడమ   = client.ఎడమ + mouse_rect.x;
        custom.శిఖరం    = client.శిఖరం  + mouse_rect.y;
        custom.కుడి  = client.ఎడమ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.శిఖరం  + mouse_rect.y + mouse_rect.h;
        ఒకవేళ (IntersectRect(&overlap, &client, &custom)) {
            లక్ష్యం = overlap;
        } లేకపోతే ఒకవేళ (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_కిటికీ(కిటికీ);
            తిరిగి;
        }
    } లేకపోతే ఒకవేళ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ఒకవేళ (videodata->సమితి_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_కిటికీ(దత్తాంశం->hwnd, MONITOR_DEFAULTTONEAREST);
            ఒకవేళ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ఒకవేళ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    స్థిరరాశి దశాంశం scale = (దశాంశం)hdpi_uint / (దశాంశం)USER_DEFAULT_SCREEN_DPI;
                    ఒకవేళ (scale != SDL_floorf(scale)) {
                        ఒకవేళ (లక్ష్యం.ఎడమ < లక్ష్యం.కుడి) {
                            లక్ష్యం.ఎడమ += 1;
                        }
                        ఒకవేళ (లక్ష్యం.కుడి > లక్ష్యం.ఎడమ) {
                            లక్ష్యం.కుడి -= 1;
                        }
                        ఒకవేళ (లక్ష్యం.శిఖరం < లక్ష్యం.bottom) {
                            లక్ష్యం.శిఖరం += 1;
                        }
                        ఒకవేళ (లక్ష్యం.bottom > లక్ష్యం.శిఖరం) {
                            లక్ష్యం.bottom -= 1;
                        }
                    }
                }
            }
            videodata->సమితి_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ఒకవేళ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&లక్ష్యం, &client, పరిమాణం(client)) &&
        ClipCursor(&లక్ష్యం)) {
        దత్తాంశం->cursor_clipped_rect = లక్ష్యం; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled)
{
    తిరిగి true; // just succeed, the real work is done elsewhere.
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity)
{
#ఒకవేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    తిరిగి false;
#లేకపోతే
    స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    స్థిరరాశి LONG style = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);

    ఒకవేళ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ఒకవేళ (style & WS_EX_LAYERED) {
            ఒకవేళ (సమితి_కిటికీ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                తిరిగి WIN_సమితి_Error("SetWindowLong()");
            }
        }
    } లేకపోతే {
        స్థిరరాశి BYTE alpha = (BYTE)((పూర్ణాంకం)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ఒకవేళ (!(style & WS_EX_LAYERED)) {
            ఒకవేళ (సమితి_కిటికీ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                తిరిగి WIN_సమితి_Error("SetWindowLong()");
            }
        }

        ఒకవేళ (సమితి_Layered_కిటికీ_లక్షణాలు(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            తిరిగి WIN_సమితి_Error("SetLayeredWindowAttributes()");
        }
    }

    తిరిగి true;
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

స్థిర స్థిరరాశి అక్షరం *SDLGetClipboardFormatName(UINT cf, అక్షరం *పాఠ్యం, పూర్ణాంకం len)
{
    ఎంపిక (cf) {
    స్థితి CF_పాఠ్యం:
        తిరిగి "CF_TEXT";
    స్థితి CF_BITMAP:
        తిరిగి "CF_BITMAP";
    స్థితి CF_METAFILEPICT:
        తిరిగి "CF_METAFILEPICT";
    స్థితి CF_SYLK:
        తిరిగి "CF_SYLK";
    స్థితి CF_DIF:
        తిరిగి "CF_DIF";
    స్థితి CF_TIFF:
        తిరిగి "CF_TIFF";
    స్థితి CF_OEMTEXT:
        తిరిగి "CF_OEMTEXT";
    స్థితి CF_DIB:
        తిరిగి "CF_DIB";
    స్థితి CF_PALETTE:
        తిరిగి "CF_PALETTE";
    స్థితి CF_PENDATA:
        తిరిగి "CF_PENDATA";
    స్థితి CF_RIFF:
        తిరిగి "CF_RIFF";
    స్థితి CF_WAVE:
        తిరిగి "CF_WAVE";
    స్థితి CF_UNICODETEXT:
        తిరిగి "CF_UNICODETEXT";
    స్థితి CF_ENHMETAFILE:
        తిరిగి "CF_ENHMETAFILE";
    స్థితి CF_HDROP:
        తిరిగి "CF_HDROP";
    స్థితి CF_LOCALE:
        తిరిగి "CF_LOCALE";
    స్థితి CF_DIBV5:
        తిరిగి "CF_DIBV5";
    స్థితి CF_OWNERDISPLAY:
        తిరిగి "CF_OWNERDISPLAY";
    స్థితి CF_DSPTEXT:
        తిరిగి "CF_DSPTEXT";
    స్థితి CF_DSPBITMAP:
        తిరిగి "CF_DSPBITMAP";
    స్థితి CF_DSPMETAFILEPICT:
        తిరిగి "CF_DSPMETAFILEPICT";
    స్థితి CF_DSPENHMETAFILE:
        తిరిగి "CF_DSPENHMETAFILE";
    అప్రమేయ:
        ఒకవేళ (GetClipboardFormatNameA(cf, పాఠ్యం, len)) {
            తిరిగి పాఠ్యం;
        } లేకపోతే {
            తిరిగి ఖాళీ;
        }
    }
}

స్థిర STDMETHODIMP_(ULONG) SDLDrop_లక్ష్యం_కూడు_Ref(SDLDrop_లక్ష్యం *లక్ష్యం)
{
    తిరిగి ++లక్ష్యం->refcount;
}

స్థిర STDMETHODIMP_(ULONG) SDLDrop_లక్ష్యం_Release(SDLDrop_లక్ష్యం *లక్ష్యం)
{
    --లక్ష్యం->refcount;
    ఒకవేళ (లక్ష్యం->refcount == 0) {
        SDL_free(లక్ష్యం);
        తిరిగి 0;
    }
    తిరిగి లక్ష్యం->refcount;
}

స్థిర STDMETHODIMP SDLDrop_లక్ష్యం_Query_Interface(SDLDrop_లక్ష్యం *లక్ష్యం, REFIID riid, PVOID *ppv)
{
    ఒకవేళ (ppv == ఖాళీ) {
        తిరిగి E_INVALIDARG;
    }

    *ppv = ఖాళీ;
    ఒకవేళ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_లక్ష్యం)) {
        *ppv = (శూన్య *)లక్ష్యం;
    }
    ఒకవేళ (*ppv) {
        SDLDrop_లక్ష్యం_కూడు_Ref(లక్ష్యం);
        తిరిగి S_OK;
    }
    తిరిగి E_NOINTERFACE;
}

స్థిర STDMETHODIMP SDLDrop_లక్ష్యం_Drag_Enter(SDLDrop_లక్ష్యం *లక్ష్యం,
                                            IDataObject *p_దత్తాంశం_Object, DWORD grf_కీలకం_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    బిందువు_2 pnt = { pt.x, pt.y };
    ఒకవేళ (Screen_గమ్యం_Client(లక్ష్యం->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, లక్ష్యం->కిటికీ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(లక్ష్యం->కిటికీ, pnt.x, pnt.y);
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    తిరిగి S_OK;
}

స్థిర STDMETHODIMP SDLDrop_లక్ష్యం_Drag_Over(SDLDrop_లక్ష్యం *లక్ష్యం,
                                           DWORD grf_కీలకం_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    బిందువు_2 pnt = { pt.x, pt.y };
    ఒకవేళ (Screen_గమ్యం_Client(లక్ష్యం->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, లక్ష్యం->కిటికీ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(లక్ష్యం->కిటికీ, pnt.x, pnt.y);
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    తిరిగి S_OK;
}

స్థిర STDMETHODIMP SDLDrop_లక్ష్యం_Drag_Leave(SDLDrop_లక్ష్యం *లక్ష్యం)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In DragLeave");
    SDL_SendDropComplete(లక్ష్యం->కిటికీ);
    తిరిగి S_OK;
}

స్థిర STDMETHODIMP SDLDrop_లక్ష్యం_Drop(SDLDrop_లక్ష్యం *లక్ష్యం,
                                       IDataObject *p_దత్తాంశం_Object, DWORD grf_కీలకం_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    బిందువు_2 pnt = { pt.x, pt.y };
    ఒకవేళ (Screen_గమ్యం_Client(లక్ష్యం->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, లక్ష్యం->కిటికీ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(లక్ష్యం->కిటికీ, pnt.x, pnt.y);
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_దత్తాంశం_Object->lpVtbl->EnumFormatEtc(p_దత్తాంశం_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ఒకవేళ (hres == S_OK) {
            FORMATETC fetc;
            అయితే (pEnumFormatEtc->lpVtbl->తదుపరి_3(pEnumFormatEtc, 1, &fetc, ఖాళీ) == S_OK) {
                అక్షరం name[257] = { 0 };
                స్థిరరాశి అక్షరం *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ఒకవేళ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } లేకపోతే {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = లక్ష్యం->format_file;
        fetc.ptd = ఖాళీ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        స్థిరరాశి అక్షరం *format_mime = "text/uri-list";
        ఒకవేళ (SUCCEEDED(p_దత్తాంశం_Object->lpVtbl->Query_Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_దత్తాంశం_Object->lpVtbl->Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ఒకవేళ (SUCCEEDED(hres)) {
                స్థిరరాశి size_t bsize = Global_కొలత(med.hGlobal);
                స్థిరరాశి శూన్య *బఫరు_2 = (శూన్య *)Global_తాళం(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)bsize, బఫరు_2);
                ఒకవేళ (బఫరు_2) {
                    అక్షరం *పాఠ్యం = (అక్షరం *)SDL_malloc(bsize + పరిమాణం(Uint32));
                    SDL_memcpy((Uint8 *)పాఠ్యం, బఫరు_2, bsize);
                    SDL_memset((Uint8 *)పాఠ్యం + bsize, 0, పరిమాణం(Uint32));
                    అక్షరం *saveptr = ఖాళీ;
                    అక్షరం *token = SDL_strtok_r(పాఠ్యం, "\r\n", &saveptr);
                    అయితే (token != ఖాళీ) {
                        ఒకవేళ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (గుర్తులేని దీర్ఘ)SDL_strlen(token), (గుర్తులేని దీర్ఘ)bsize, token);
                            SDL_SendDropFile(లక్ష్యం->కిటికీ, ఖాళీ, token);
                        }
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    SDL_free(పాఠ్యం);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(లక్ష్యం->కిటికీ);
                తిరిగి S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = లక్ష్యం->format_పాఠ్యం;
        fetc.ptd = ఖాళీ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        స్థిరరాశి అక్షరం *format_mime = "text/plain;charset=utf-8";
        ఒకవేళ (SUCCEEDED(p_దత్తాంశం_Object->lpVtbl->Query_Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_దత్తాంశం_Object->lpVtbl->Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ఒకవేళ (SUCCEEDED(hres)) {
                స్థిరరాశి size_t bsize = Global_కొలత(med.hGlobal);
                స్థిరరాశి శూన్య *బఫరు_2 = (శూన్య *)Global_తాళం(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)bsize, బఫరు_2);
                ఒకవేళ (బఫరు_2) {
                    అక్షరం *పాఠ్యం = (అక్షరం *)SDL_malloc(bsize + పరిమాణం(Uint32));
                    SDL_memcpy((Uint8 *)పాఠ్యం, బఫరు_2, bsize);
                    SDL_memset((Uint8 *)పాఠ్యం + bsize, 0, పరిమాణం(Uint32));
                    అక్షరం *saveptr = ఖాళీ;
                    అక్షరం *token = SDL_strtok_r(పాఠ్యం, "\r\n", &saveptr);
                    అయితే (token != ఖాళీ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (గుర్తులేని దీర్ఘ)SDL_strlen(token), (గుర్తులేని దీర్ఘ)bsize, token);
                        SDL_Send_Drop_పాఠ్యం(లక్ష్యం->కిటికీ, (అక్షరం *)token);
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    SDL_free(పాఠ్యం);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(లక్ష్యం->కిటికీ);
                తిరిగి S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ఖాళీ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        స్థిరరాశి అక్షరం *format_mime = "CF_UNICODETEXT";
        ఒకవేళ (SUCCEEDED(p_దత్తాంశం_Object->lpVtbl->Query_Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_దత్తాంశం_Object->lpVtbl->Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ఒకవేళ (SUCCEEDED(hres)) {
                స్థిరరాశి size_t bsize = Global_కొలత(med.hGlobal);
                స్థిరరాశి శూన్య *బఫరు_2 = (శూన్య *)Global_తాళం(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)bsize, బఫరు_2);
                ఒకవేళ (బఫరు_2) {
                    బఫరు_2 = WIN_String_గమ్యం_UTF8_W((స్థిరరాశి wchar_t *)బఫరు_2);
                    ఒకవేళ (బఫరు_2) {
                        స్థిరరాశి size_t lbuffer = SDL_strlen((స్థిరరాశి అక్షరం *)బఫరు_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)lbuffer, బఫరు_2);
                        అక్షరం *పాఠ్యం = (అక్షరం *)SDL_malloc(lbuffer + పరిమాణం(Uint32));
                        SDL_memcpy((Uint8 *)పాఠ్యం, బఫరు_2, lbuffer);
                        SDL_memset((Uint8 *)పాఠ్యం + lbuffer, 0, పరిమాణం(Uint32));
                        అక్షరం *saveptr = ఖాళీ;
                        అక్షరం *token = SDL_strtok_r(పాఠ్యం, "\r\n", &saveptr);
                        అయితే (token != ఖాళీ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (గుర్తులేని దీర్ఘ)SDL_strlen(token), (గుర్తులేని దీర్ఘ)lbuffer, token);
                            SDL_Send_Drop_పాఠ్యం(లక్ష్యం->కిటికీ, (అక్షరం *)token);
                            token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                        }
                        SDL_free(పాఠ్యం);
                        SDL_free((శూన్య *)బఫరు_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(లక్ష్యం->కిటికీ);
                తిరిగి S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_పాఠ్యం;
        fetc.ptd = ఖాళీ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        స్థిరరాశి అక్షరం *format_mime = "CF_TEXT";
        ఒకవేళ (SUCCEEDED(p_దత్తాంశం_Object->lpVtbl->Query_Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_దత్తాంశం_Object->lpVtbl->Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ఒకవేళ (SUCCEEDED(hres)) {
                స్థిరరాశి size_t bsize = Global_కొలత(med.hGlobal);
                స్థిరరాశి శూన్య *బఫరు_2 = (శూన్య *)Global_తాళం(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)bsize, బఫరు_2);
                ఒకవేళ (బఫరు_2) {
                    అక్షరం *పాఠ్యం = (అక్షరం *)SDL_malloc(bsize + పరిమాణం(Uint32));
                    SDL_memcpy((Uint8 *)పాఠ్యం, బఫరు_2, bsize);
                    SDL_memset((Uint8 *)పాఠ్యం + bsize, 0, పరిమాణం(Uint32));
                    అక్షరం *saveptr = ఖాళీ;
                    అక్షరం *token = SDL_strtok_r(పాఠ్యం, "\r\n", &saveptr);
                    అయితే (token != ఖాళీ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (గుర్తులేని దీర్ఘ)SDL_strlen(token), (గుర్తులేని దీర్ఘ)bsize, token);
                        SDL_Send_Drop_పాఠ్యం(లక్ష్యం->కిటికీ, (అక్షరం *)token);
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    SDL_free(పాఠ్యం);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(లక్ష్యం->కిటికీ);
                తిరిగి S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ఖాళీ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        స్థిరరాశి అక్షరం *format_mime = "CF_HDROP";
        ఒకవేళ (SUCCEEDED(p_దత్తాంశం_Object->lpVtbl->Query_Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_దత్తాంశం_Object->lpVtbl->Get_దత్తాంశం(p_దత్తాంశం_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ఒకవేళ (SUCCEEDED(hres)) {
                స్థిరరాశి size_t bsize = Global_కొలత(med.hGlobal);
                HDROP drop = (HDROP)Global_తాళం(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (గుర్తులేని దీర్ఘ)bsize, drop);
                UINT లెక్క = DragQueryFile(drop, 0xFFFFFFFF, ఖాళీ, 0);
                కొరకు (UINT i = 0; i < లెక్క; ++i) {
                    UINT కొలత = DragQueryFile(drop, i, ఖాళీ, 0) + 1;
                    LPTSTR బఫరు_2 = (LPTSTR)SDL_malloc(కొలత * పరిమాణం(TCHAR));
                    ఒకవేళ (బఫరు_2) {
                        ఒకవేళ (DragQueryFile(drop, i, బఫరు_2, కొలత)) {
                            అక్షరం *file = WIN_String_గమ్యం_UTF8(బఫరు_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (గుర్తులేని దీర్ఘ)SDL_strlen(file), (గుర్తులేని దీర్ఘ)bsize, file);
                            SDL_SendDropFile(లక్ష్యం->కిటికీ, ఖాళీ, file);
                            SDL_free(file);
                        }
                        SDL_free(బఫరు_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(లక్ష్యం->కిటికీ);
                తిరిగి S_OK;
            }
        }
    }

    SDL_SendDropComplete(లక్ష్యం->కిటికీ);
    తిరిగి S_OK;
}

స్థిర శూన్య *vt_Drop_లక్ష్యం[] = {
    (శూన్య *)(SDLDrop_లక్ష్యం_Query_Interface),
    (శూన్య *)(SDLDrop_లక్ష్యం_కూడు_Ref),
    (శూన్య *)(SDLDrop_లక్ష్యం_Release),
    (శూన్య *)(SDLDrop_లక్ష్యం_Drag_Enter),
    (శూన్య *)(SDLDrop_లక్ష్యం_Drag_Over),
    (శూన్య *)(SDLDrop_లక్ష్యం_Drag_Leave),
    (శూన్య *)(SDLDrop_లక్ష్యం_Drop)
};

శూన్య WIN_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    ఒకవేళ (దత్తాంశం->videodata->oleinitialized) {
        ఒకవేళ (accept && !దత్తాంశం->drop_లక్ష్యం) {
            SDLDrop_లక్ష్యం *drop_లక్ష్యం = (SDLDrop_లక్ష్యం *)SDL_calloc(1, పరిమాణం(SDLDrop_లక్ష్యం));
            ఒకవేళ (drop_లక్ష్యం != ఖాళీ) {
                drop_లక్ష్యం->lpVtbl = vt_Drop_లక్ష్యం;
                drop_లక్ష్యం->కిటికీ = కిటికీ;
                drop_లక్ష్యం->hwnd = దత్తాంశం->hwnd;
                drop_లక్ష్యం->format_file = రిజిస్టరు_Clipboard_Format_W(L"text/uri-list");
                drop_లక్ష్యం->format_పాఠ్యం = రిజిస్టరు_Clipboard_Format_W(L"text/plain;charset=utf-8");
                దత్తాంశం->drop_లక్ష్యం = drop_లక్ష్యం;
                SDLDrop_లక్ష్యం_కూడు_Ref(drop_లక్ష్యం);
                రిజిస్టరు_Drag_Drop(దత్తాంశం->hwnd, (LPDROPTARGET)drop_లక్ష్యం);
                SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             కిటికీ->id);
            }
        } లేకపోతే ఒకవేళ (!accept && దత్తాంశం->drop_లక్ష్యం) {
            RevokeDragDrop(దత్తాంశం->hwnd);
            SDLDrop_లక్ష్యం_Release(దత్తాంశం->drop_లక్ష్యం);
            దత్తాంశం->drop_లక్ష్యం = ఖాళీ;
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         కిటికీ->id);
        }
    } లేకపోతే {
        DragAcceptFiles(దత్తాంశం->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     కిటికీ->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_కొలత = పరిమాణం(desc);
    desc.hwnd = కిటికీ->అంతర్గత->hwnd;
    ఎంపిక (operation) {
    స్థితి SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ఆపు;
    స్థితి SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_లెక్క = 1;
        ఆపు;
    స్థితి SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ఆపు;
    అప్రమేయ:
        తిరిగి SDL_Unsupported();
    }

    Flash_కిటికీ_Ex(&desc);

    తిరిగి true;
}

bool WIN_Apply_కిటికీ_పురోగతి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    ఒకవేళ (!దత్తాంశం->taskbar_button_created) {
        తిరిగి true;
    }

    ఒకవేళ (కిటికీ->పురోగతి_state == SDL_పురోగతి_STATE_NONE && !దత్తాంశం->videodata->taskbar_list) {
        తిరిగి true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(కిటికీ);
    ఒకవేళ (!taskbar_list) {
        తిరిగి false;
    }

    TBPFLAG tbpFlags;
    ఎంపిక (కిటికీ->పురోగతి_state) {
    స్థితి SDL_పురోగతి_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ఆపు;
    స్థితి SDL_పురోగతి_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ఆపు;
    స్థితి SDL_పురోగతి_STATE_సాధారణ:
        tbpFlags = TBPF_సాధారణ;
        ఆపు;
    స్థితి SDL_పురోగతి_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ఆపు;
    స్థితి SDL_పురోగతి_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ఆపు;
    అప్రమేయ:
        తిరిగి SDL_సమితి_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->సమితి_పురోగతి_State(taskbar_list, దత్తాంశం->hwnd, tbpFlags);
    ఒకవేళ (FAILED(ret)) {
        తిరిగి WIN_సమితి_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ఒకవేళ (కిటికీ->పురోగతి_state >= SDL_పురోగతి_STATE_సాధారణ) {
        ret = taskbar_list->lpVtbl->సమితి_పురోగతి_విలువ(taskbar_list, దత్తాంశం->hwnd, (ULONGLONG)(కిటికీ->పురోగతి_విలువ * 10000.f), 10000);
        ఒకవేళ (FAILED(ret)) {
            తిరిగి WIN_సమితి_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#అయితే_ముగింపు
    తిరిగి true;
}

శూన్య WIN_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y)
{
    స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    బిందువు_2 pt;

    pt.x = x;
    pt.y = y;
    Client_గమ్యం_Screen(దత్తాంశం->hwnd, &pt);
    Send_సందేశం(దత్తాంశం->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable)
{
    ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        HWND hwnd = దత్తాంశం->hwnd;
        స్థిరరాశి LONG style = Get_కిటికీ_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ఒకవేళ (focusable) {
            ఒకవేళ (style & WS_EX_NOACTIVATE) {
                ఒకవేళ (సమితి_కిటికీ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    తిరిగి WIN_సమితి_Error("SetWindowLong()");
                }
            }
        } లేకపోతే {
            ఒకవేళ (!(style & WS_EX_NOACTIVATE)) {
                ఒకవేళ (సమితి_కిటికీ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    తిరిగి WIN_సమితి_Error("SetWindowLong()");
                }
            }
        }
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
            ఒకవేళ (!focusable && (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
                SDL_కిటికీ *new_focus;
                స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(కిటికీ, &new_focus);
                WIN_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
            } లేకపోతే ఒకవేళ (focusable) {
                ఒకవేళ (SDL_ShouldFocusPopup(కిటికీ)) {
                    WIN_సమితి_Keyboard_Focus(కిటికీ, true);
                }
            }
        }

        తిరిగి true;
    }

    తిరిగి true;
}
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_కిటికీ_దత్తాంశం *బిడ్డ_దత్తాంశం = కిటికీ->అంతర్గత;
    స్థిరరాశి LONG_PTR మాతృ_hwnd = (LONG_PTR)(మాతృ ? మాతృ->అంతర్గత->hwnd : ఖాళీ);
    స్థిరరాశి DWORD style = Get_కిటికీ_Long(బిడ్డ_దత్తాంశం->hwnd, GWL_STYLE);

    ఒకవేళ (!(style & WS_బిడ్డ)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        సమితి_కిటికీ_Long_Ptr(బిడ్డ_దత్తాంశం->hwnd, GWLP_HWNDPARENT, మాతృ_hwnd);
    } లేకపోతే {
        సమితి_మాతృ(బిడ్డ_దత్తాంశం->hwnd, (HWND)మాతృ_hwnd);
    }
#అయితే_ముగింపు /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    తిరిగి true;
}

bool WIN_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal)
{
#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    స్థిరరాశి HWND మాతృ_hwnd = కిటికీ->మాతృ->అంతర్గత->hwnd;

    ఒకవేళ (modal) {
        // Disable the parent window.
        Enable_కిటికీ(మాతృ_hwnd, FALSE);
    } లేకపోతే ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
        // Re-enable the parent window
        Enable_కిటికీ(మాతృ_hwnd, TRUE);
    }
#అయితే_ముగింపు // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS
