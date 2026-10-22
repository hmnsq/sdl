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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

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

#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#अन्तर्भाव <shobjidl.h>
#यदि_अन्तः

// Windows CE compatibility
#यदि_अपरिभाषितम् SWP_NOCOPYBITS
#परिभाषय SWP_NOCOPYBITS 0
#यदि_अन्तः

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#यदि_अपरिभाषितम् WM_POPUPSYSTEMMENU
#परिभाषय WM_POPUPSYSTEMMENU 0x313
#यदि_अन्तः

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

#परिभाषय STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#परिभाषय STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#परिभाषय STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#परिभाषय STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#परिभाषय STYLE_प्रसामान्यम्              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#परिभाषय STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#परिभाषय STYLE_आवरणम्                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_प्रसामान्यम् | STYLE_RESIZABLE)

स्थिर DWORD Get_गवाक्षः_Style(SDL_गवाक्षः *गवाक्षः)
{
    DWORD style = 0;

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        style |= WS_POPUP;
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } अन्यथा {
        यदि (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            यदि (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } अन्यथा {
                style |= STYLE_BORDERLESS;
            }
        } अन्यथा {
            style |= STYLE_प्रसामान्यम्;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        यदि (गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            यदि (!(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        यदि (गवाक्षः->आन्तरिकम् && गवाक्षः->आन्तरिकम्->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    प्रत्यागम style;
}

स्थिर DWORD Get_गवाक्षः_Style_Ex(SDL_गवाक्षः *गवाक्षः)
{
    DWORD style = 0;

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः) || (गवाक्षः->flags & SDL_गवाक्षः_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः) || (गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    प्रत्यागम style;
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
स्थिर ITaskbarList3 *GetTaskbarList(SDL_गवाक्षः *गवाक्षः)
{
    ध्रुव SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_assert(दत्त->taskbar_button_created);
    यदि (!दत्त->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, रिक्त, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&दत्त->videodata->taskbar_list);
        यदि (FAILED(ret)) {
            WIN_समुच्चयः_Error_From_HRESULT("Unable to create taskbar list", ret);
            प्रत्यागम रिक्त;
        }
        ITaskbarList3 *taskbarlist = दत्त->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        यदि (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            दत्त->videodata->taskbar_list = रिक्त;
            WIN_समुच्चयः_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            प्रत्यागम रिक्त;
        }
    }
    प्रत्यागम दत्त->videodata->taskbar_list;
}
#यदि_अन्तः

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
स्थिर bool WIN_Adjust_गवाक्षः_Rect_With_Style(SDL_गवाक्षः *गवाक्षः, DWORD style, DWORD styleEx, BOOL menu, पूर्णाङ्क *x, पूर्णाङ्क *y, पूर्णाङ्क *विस्तारः, पूर्णाङ्क *height, SDL_गवाक्षः_Rect rect_type)
{
    SDL_Video_दत्त *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->आन्तरिकम् : रिक्त;
    RECT rect;

    // Client rect, in points
    विकल्प (rect_type) {
    पक्ष SDL_WINDOWRECT_CURRENT:
        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->x, गवाक्षः->y, x, y);
        *विस्तारः = गवाक्षः->w;
        *height = गवाक्षः->h;
        भङ्ग;
    पक्ष SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->windowed.x, गवाक्षः->windowed.y, x, y);
        *विस्तारः = गवाक्षः->windowed.w;
        *height = गवाक्षः->windowed.h;
        भङ्ग;
    पक्ष SDL_WINDOWRECT_FLOATING:
        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->floating.x, गवाक्षः->floating.y, x, y);
        *विस्तारः = गवाक्षः->floating.w;
        *height = गवाक्षः->floating.h;
        भङ्ग;
    पक्ष SDL_WINDOWRECT_PENDING:
        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->pending.x, गवाक्षः->pending.y, x, y);
        *विस्तारः = गवाक्षः->pending.w;
        *height = गवाक्षः->pending.h;
        भङ्ग;
    स्वभाव:
        // Should never be here
        SDL_assert_release(false);
        *विस्तारः = 0;
        *height = 0;
        भङ्ग;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.वामः = 0;
    rect.शिखरम् = 0;
    rect.दक्षिणः = *विस्तारः;
    rect.bottom = *height;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) && !SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_गवाक्षः_Rect_Ex(&rect, style, menu, 0);
#अन्यथा
        यदि (WIN_Is_प्रत्येकम्_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            यदि (videodata) {
                UINT frame_dpi;
                SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
                frame_dpi = (दत्त && videodata->Get_Dpi_For_गवाक्षः) ? videodata->Get_Dpi_For_गवाक्षः(दत्त->hwnd) : USER_DEFAULT_SCREEN_DPI;
                यदि (videodata->Adjust_गवाक्षः_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, frame_dpi) == 0) {
                    प्रत्यागम WIN_समुच्चयः_Error("AdjustWindowRectExForDpi()");
                }
            }
        } अन्यथा {
            यदि (Adjust_गवाक्षः_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                प्रत्यागम WIN_समुच्चयः_Error("AdjustWindowRectEx()");
            }
        }
#यदि_अन्तः
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.वामः;
    *y += rect.शिखरम्;
    *विस्तारः = (rect.दक्षिणः - rect.वामः);
    *height = (rect.bottom - rect.शिखरम्);

#यदि_परिभाषितम् HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? गवाक्षः->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? गवाक्षः->windowed.x : गवाक्षः->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? गवाक्षः->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? गवाक्षः->windowed.y : गवाक्षः->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? गवाक्षः->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? गवाक्षः->windowed.w : गवाक्षः->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? गवाक्षः->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? गवाक्षः->windowed.h : गवाक्षः->h),
            *x, *y, *विस्तारः, *height, frame_dpi);
#यदि_अन्तः
    प्रत्यागम true;
}

bool WIN_Adjust_गवाक्षः_Rect(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *x, पूर्णाङ्क *y, पूर्णाङ्क *विस्तारः, पूर्णाङ्क *height, SDL_गवाक्षः_Rect rect_type)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
    styleEx = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
#यदि_अन्तः
    प्रत्यागम WIN_Adjust_गवाक्षः_Rect_With_Style(गवाक्षः, style, styleEx, menu, x, y, विस्तारः, height, rect_type);
}

bool WIN_Adjust_गवाक्षः_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_दत्त *videodata = videodevice ? videodevice->आन्तरिकम् : रिक्त;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
    styleEx = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#अन्यथा
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
#यदि_अन्तः

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_गवाक्षः_Rect_Ex(lpRect, style, menu, styleEx);
#अन्यथा
    यदि (WIN_Is_प्रत्येकम्_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        यदि (!frame_dpi) {
            frame_dpi = videodata->Get_Dpi_For_गवाक्षः ? videodata->Get_Dpi_For_गवाक्षः(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        यदि (!videodata->Adjust_गवाक्षः_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, frame_dpi)) {
            प्रत्यागम WIN_समुच्चयः_Error("AdjustWindowRectExForDpi()");
        }
    } अन्यथा {
        यदि (!Adjust_गवाक्षः_Rect_Ex(lpRect, style, menu, styleEx)) {
            प्रत्यागम WIN_समुच्चयः_Error("AdjustWindowRectEx()");
        }
    }
#यदि_अन्तः
    प्रत्यागम true;
}

bool WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(SDL_गवाक्षः *गवाक्षः, UINT flags, SDL_गवाक्षः_Rect rect_type)
{
    SDL_गवाक्षः *child_गवाक्षः;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    HWND शिखरम्;
    पूर्णाङ्क x, y;
    पूर्णाङ्क w, h;
    bool परिणाम = true;

    // Figure out what the window area will be
    यदि (SDL_ShouldAllowTopmost() && (गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्)) {
        शिखरम् = HWND_TOPMOST;
    } अन्यथा {
        शिखरम् = HWND_NOTOPMOST;
    }

    WIN_Adjust_गवाक्षः_Rect(गवाक्षः, &x, &y, &w, &h, rect_type);

    दत्त->expected_resize = !(flags & SWP_NOSIZE);
    यदि (समुच्चयः_गवाक्षः_Pos(hwnd, शिखरम्, x, y, w, h, flags) == 0) {
        परिणाम = WIN_समुच्चयः_Error("SetWindowPos()");
    }
    दत्त->expected_resize = false;

    // Update any child windows
    प्रति (child_गवाक्षः = गवाक्षः->first_child; child_गवाक्षः; child_गवाक्षः = child_गवाक्षः->अग्र_sibling) {
        यदि (!child_गवाक्षः->आन्तरिकम्) {
            // This child window is not yet fully initialized.
            अनुवर्त;
        }
        यदि (!WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(child_गवाक्षः, flags, SDL_WINDOWRECT_CURRENT)) {
            परिणाम = false;
        }
    }
    प्रत्यागम परिणाम;
}

स्थिर SDL_गवाक्षः_Erase_Background_बहुलकम् Get_Erase_Background_बहुलकम्_Hint(शून्य)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_बहुलकम्);
    यदि (!hint)
        प्रत्यागम SDL_ERASEBACKGROUNDMODE_INITIAL;

    यदि (SDL_strstr(hint, "never"))
        प्रत्यागम SDL_ERASEBACKGROUNDMODE_NEVER;

    यदि (SDL_strstr(hint, "initial"))
        प्रत्यागम SDL_ERASEBACKGROUNDMODE_INITIAL;

    यदि (SDL_strstr(hint, "always"))
        प्रत्यागम SDL_ERASEBACKGROUNDMODE_ALWAYS;

    पूर्णाङ्क बहुलकम् = SDL_GetStringInteger(hint, 1);
    यदि (बहुलकम् < 0 || बहुलकम् > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        प्रत्यागम SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    प्रत्यागम (SDL_गवाक्षः_Erase_Background_बहुलकम्)बहुलकम्;
}

स्थिर bool सज्जता_गवाक्षः_दत्त(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, HWND hwnd, HWND parent)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त;

    // Allocate the window data
    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }
    दत्त->गवाक्षः = गवाक्षः;
    दत्त->hwnd = hwnd;
    दत्त->parent = parent;
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    दत्त->hdc = (HDC)दत्त->hwnd;
#अन्यथा
    दत्त->hdc = GetDC(hwnd);
#यदि_अन्तः
    दत्त->hinstance = (HINSTANCE)Get_गवाक्षः_Long_Ptr(hwnd, GWLP_HINSTANCE);
    दत्त->mouse_button_flags = (WPARAM)-1;
    दत्त->चरमः_pointer_update = (LPARAM)-1;
    दत्त->videodata = videodata;
    दत्त->initializing = true;
    दत्त->hint_erase_background_बहुलकम् = Get_Erase_Background_बहुलकम्_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    दत्त->cursor_ctrlock_rect.वामः   = 0 - remote_desktop_adjustment;
    दत्त->cursor_ctrlock_rect.शिखरम्    = 0;
    दत्त->cursor_ctrlock_rect.दक्षिणः  = 1 + remote_desktop_adjustment;
    दत्त->cursor_ctrlock_rect.bottom = 1;
#यदि_अन्तः

    यदि (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        दत्त->copybits_flag = 0;
    } अन्यथा {
        दत्त->copybits_flag = SWP_NOCOPYBITS;
    }

#यदि_परिभाषितम् HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", दत्त->scaling_dpi);
#यदि_अन्तः

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    यदि (!समुच्चयः_Prop(hwnd, TEXT("SDL_WindowData"), दत्त)) {
        ReleaseDC(hwnd, दत्त->hdc);
        SDL_free(दत्त);
        प्रत्यागम WIN_समुच्चयः_Error("SetProp() failed");
    }
#यदि_अन्तः

    गवाक्षः->आन्तरिकम् = दत्त;

    // Set up the window proc function
    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
#यदि_परिभाषितम् GWLP_WNDPROC
        दत्त->wndproc = (WNDPROC)Get_गवाक्षः_Long_Ptr(hwnd, GWLP_WNDPROC);
        यदि (दत्त->wndproc != WIN_गवाक्षः_Proc) {
            समुच्चयः_गवाक्षः_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_गवाक्षः_Proc);
        }
#अन्यथा
        दत्त->wndproc = (WNDPROC)Get_गवाक्षः_Long(hwnd, GWL_WNDPROC);
        यदि (दत्त->wndproc != WIN_गवाक्षः_Proc) {
            समुच्चयः_गवाक्षः_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_गवाक्षः_Proc);
        }
#यदि_अन्तः
    } अन्यथा {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
        यदि (style & WS_VISIBLE) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_HIDDEN;
        } अन्यथा {
            गवाक्षः->flags |= SDL_गवाक्षः_HIDDEN;
        }
        यदि (style & WS_POPUP) {
            गवाक्षः->flags |= SDL_गवाक्षः_BORDERLESS;
        } अन्यथा {
            गवाक्षः->flags &= ~SDL_गवाक्षः_BORDERLESS;
        }
        यदि (style & WS_THICKFRAME) {
            गवाक्षः->flags |= SDL_गवाक्षः_RESIZABLE;
        } अन्यथा यदि (!(style & WS_POPUP)) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_RESIZABLE;
        }
#यदि_परिभाषितम् WS_MAXIMIZE
        यदि (style & WS_MAXIMIZE) {
            गवाक्षः->flags |= SDL_गवाक्षः_MAXIMIZED;
        } अन्यथा
#यदि_अन्तः
        {
            गवाक्षः->flags &= ~SDL_गवाक्षः_MAXIMIZED;
        }
#यदि_परिभाषितम् WS_MINIMIZE
        यदि (style & WS_MINIMIZE) {
            गवाक्षः->flags |= SDL_गवाक्षः_MINIMIZED;
        } अन्यथा
#यदि_अन्तः
        {
            गवाक्षः->flags &= ~SDL_गवाक्षः_MINIMIZED;
        }
    }
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        RECT rect;
        यदि (GetClientRect(hwnd, &rect) && WIN_गवाक्षः_Rect_Valid(&rect)) {
            पूर्णाङ्क w = rect.दक्षिणः;
            पूर्णाङ्क h = rect.bottom;

            यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
                गवाक्षः->floating.w = गवाक्षः->windowed.w = गवाक्षः->w = w;
                गवाक्षः->floating.h = गवाक्षः->windowed.h = गवाक्षः->h = h;
            } अन्यथा यदि ((गवाक्षः->windowed.w && गवाक्षः->windowed.w != w) || (गवाक्षः->windowed.h && गवाक्षः->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                पूर्णाङ्क x, y;
                // Figure out what the window area will be
                WIN_Adjust_गवाक्षः_Rect(गवाक्षः, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                दत्त->expected_resize = true;
                समुच्चयः_गवाक्षः_Pos(hwnd, रिक्त, x, y, w, h, दत्त->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                दत्त->expected_resize = false;
            } अन्यथा {
                गवाक्षः->w = w;
                गवाक्षः->h = h;
            }
        }
    }
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        POINT point;
        point.x = 0;
        point.y = 0;
        यदि (Client_गन्तव्यम्_Screen(hwnd, &point)) {
            यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
                गवाक्षः->floating.x = गवाक्षः->windowed.x = point.x;
                गवाक्षः->floating.y = गवाक्षः->windowed.y = point.y;
            }
            गवाक्षः->x = point.x;
            गवाक्षः->y = point.y;
        }
    }

    WIN_Update_गवाक्षः_ICCProfile(गवाक्षः, false);
#यदि_अन्तः

#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    गवाक्षः->flags |= SDL_गवाक्षः_निवेशः_FOCUS;
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
#अन्यथा
    यदि (GetFocus() == hwnd) {
        गवाक्षः->flags |= SDL_गवाक्षः_निवेशः_FOCUS;
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
        WIN_UpdateClipCursor(गवाक्षः);
    }
#यदि_अन्तः

    यदि (गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्) {
        WIN_समुच्चयः_गवाक्षः_Always_On_शिखरम्(_this, गवाक्षः, true);
    } अन्यथा {
        WIN_समुच्चयः_गवाक्षः_Always_On_शिखरम्(_this, गवाक्षः, false);
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    यदि (videodata->पञ्जिकाकोशः_Touch_गवाक्षः) {
        videodata->पञ्जिकाकोशः_Touch_गवाक्षः(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#यदि_अन्तः

    यदि (दत्त->parent && !गवाक्षः->parent) {
        दत्त->destroy_parent_with_गवाक्षः = true;
    }

    दत्त->initializing = false;

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        पूर्णाङ्क titleLen;
        bool isstack;

        titleLen = Get_गवाक्षः_Text_दीर्घता(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        यदि (title) {
            titleLen = Get_गवाक्षः_Text(hwnd, title, titleLen + 1);
        } अन्यथा {
            titleLen = 0;
        }
        यदि (titleLen > 0) {
            गवाक्षः->title = WIN_String_गन्तव्यम्_UTF8(title);
        }
        यदि (title) {
            SDL_small_free(title, isstack);
        }
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WIN32_HWND_POINTER, दत्त->hwnd);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WIN32_HDC_POINTER, दत्त->hdc);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WIN32_INSTANCE_POINTER, दत्त->hinstance);

    // All done!
    प्रत्यागम true;
}

स्थिर शून्य Cleanup_गवाक्षः_दत्त(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त) {
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        यदि (दत्त->drop_target) {
            WIN_AcceptDragAndDrop(गवाक्षः, false);
        }
        SDL_free(दत्त->ICMFileName);
        यदि (दत्त->keyboard_hook) {
            UnhookWindowsHookEx(दत्त->keyboard_hook);
        }
        यदि (दत्त->hicon) {
            DestroyIcon(दत्त->hicon);
        }
        ReleaseDC(दत्त->hwnd, दत्त->hdc);
        RemoveProp(दत्त->hwnd, TEXT("SDL_WindowData"));
#यदि_अन्तः
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
            Destroy_गवाक्षः(दत्त->hwnd);
            यदि (दत्त->destroy_parent_with_गवाक्षः && दत्त->parent) {
                Destroy_गवाक्षः(दत्त->parent);
            }
        } अन्यथा {
            // Restore any original event handler...
            यदि (दत्त->wndproc) {
#यदि_परिभाषितम् GWLP_WNDPROC
                समुच्चयः_गवाक्षः_Long_Ptr(दत्त->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)दत्त->wndproc);
#अन्यथा
                समुच्चयः_गवाक्षः_Long(दत्त->hwnd, GWL_WNDPROC,
                              (LONG_PTR)दत्त->wndproc);
#यदि_अन्तः
            }
        }
        SDL_free(दत्त);
    }
    गवाक्षः->आन्तरिकम् = रिक्त;
}

स्थिर शून्य WIN_ConstrainPopup(SDL_गवाक्षः *गवाक्षः, bool output_गन्तव्यम्_pending)
{
    // Possibly clamp popup windows to the output borders
    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        SDL_गवाक्षः *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णाङ्क abs_x = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.x : गवाक्षः->floating.x;
        पूर्णाङ्क abs_y = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.y : गवाक्षः->floating.y;
        ध्रुव पूर्णाङ्क विस्तारः = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->floating.w;
        ध्रुव पूर्णाङ्क height = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->floating.h;
        पूर्णाङ्क विस्थापनम्_x = 0, विस्थापनम्_y = 0;

        यदि (गवाक्षः->constrain_popup) {
            // Calculate the total offset from the parents
            प्रति (w = गवाक्षः->parent; SDL_गवाक्षः_IS_POPUP(w); w = w->parent) {
                विस्थापनम्_x += w->x;
                विस्थापनम्_y += w->y;
            }

            विस्थापनम्_x += w->x;
            विस्थापनम्_y += w->y;
            abs_x += विस्थापनम्_x;
            abs_y += विस्थापनम्_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_गवाक्षः(w);
            SDL_GetDisplayBounds(displayID, &rect);
            यदि (abs_x + विस्तारः > rect.x + rect.w) {
                abs_x -= (abs_x + विस्तारः) - (rect.x + rect.w);
            }
            यदि (abs_y + height > rect.y + rect.h) {
                abs_y -= (abs_y + height) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        यदि (output_गन्तव्यम्_pending) {
            गवाक्षः->pending.x = abs_x - विस्थापनम्_x;
            गवाक्षः->pending.y = abs_y - विस्थापनम्_y;
            गवाक्षः->pending.w = विस्तारः;
            गवाक्षः->pending.h = height;
        } अन्यथा {
            गवाक्षः->floating.x = abs_x - विस्थापनम्_x;
            गवाक्षः->floating.y = abs_y - विस्थापनम्_y;
            गवाक्षः->floating.w = विस्तारः;
            गवाक्षः->floating.h = height;
        }
    }
}

स्थिर शून्य WIN_समुच्चयः_Keyboard_Focus(SDL_गवाक्षः *गवाक्षः, bool समुच्चयः_सक्रिय_focus)
{
    SDL_गवाक्षः *toplevel = गवाक्षः;

    // Find the topmost parent
    यावत् (SDL_गवाक्षः_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = गवाक्षः;

    यदि (समुच्चयः_सक्रिय_focus && !गवाक्षः->is_hiding && !गवाक्षः->is_destroying) {
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    }
}

bool WIN_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    HWND hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WIN32_HWND_POINTER, SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    HWND parent = रिक्त;
    यदि (hwnd) {
        गवाक्षः->flags |= SDL_गवाक्षः_EXTERNAL;

        यदि (!सज्जता_गवाक्षः_दत्त(_this, गवाक्षः, hwnd, parent)) {
            प्रत्यागम false;
        }
    } अन्यथा {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        पूर्णाङ्क x, y;
        पूर्णाङ्क w, h;

        यदि (गवाक्षः->flags & SDL_गवाक्षः_UTILITY) {
            parent = Create_गवाक्षः(SDL_Appname, TEXT(""), STYLE_BASIC, 0, 0, 32, 32, रिक्त, रिक्त, SDL_Instance, रिक्त);
        } अन्यथा यदि (गवाक्षः->parent) {
            parent = गवाक्षः->parent->आन्तरिकम्->hwnd;
        }

        style |= Get_गवाक्षः_Style(गवाक्षः);
        styleEx |= (DWORD)SDL_Get_सङ्ख्या_Property(create_props, SDL_PROP_गवाक्षः_CREATE_WIN32_STYLE_EX_सङ्ख्या, Get_गवाक्षः_Style_Ex(गवाक्षः));

        // Figure out what the window area will be
        WIN_ConstrainPopup(गवाक्षः, false);
        WIN_Adjust_गवाक्षः_Rect_With_Style(गवाक्षः, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_गवाक्षः_Ex(styleEx, SDL_Appname, TEXT(""), style,
                              x, y, w, h, parent, रिक्त, SDL_Instance, रिक्त);
        यदि (!hwnd) {
            प्रत्यागम WIN_समुच्चयः_Error("Couldn't create window");
        }

        WIN_Update_Dark_बहुलकम्_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        यदि (!सज्जता_गवाक्षः_दत्त(_this, गवाक्षः, hwnd, parent)) {
            Destroy_गवाक्षः(hwnd);
            यदि (parent) {
                Destroy_गवाक्षः(parent);
            }
            प्रत्यागम false;
        }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_Text_निवेशः(_this, गवाक्षः);
#यदि_अन्तः

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        समुच्चयः_गवाक्षः_Pos(hwnd, रिक्त, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            गवाक्षः->flags &= ~SDL_गवाक्षः_HIDDEN;
            Show_गवाक्षः(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    यदि (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) {
        यदि (videodata->Dwm_Enable_Blur_Behind_गवाक्षः) {
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
            videodata->Dwm_Enable_Blur_Behind_गवाक्षः(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_GetPointerProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, रिक्त);
    यदि (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        पूर्णाङ्क pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, परिमाण(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        यदि (!समुच्चयः_Pixel_Format(गवाक्षः->आन्तरिकम्->hdc, pixel_format, &pfd)) {
            WIN_Destroy_गवाक्षः(_this, गवाक्षः);
            प्रत्यागम WIN_समुच्चयः_Error("SetPixelFormat()");
        }
    } अन्यथा {
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
            प्रत्यागम true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_ES2
        यदि ((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_दत्त || WIN_GL_UseEGL(_this))
#यदि_अन्तः // SDL_VIDEO_OPENGL_WGL
        ) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
            यदि (!WIN_GLES_सज्जता_गवाक्षः(_this, गवाक्षः)) {
                WIN_Destroy_गवाक्षः(_this, गवाक्षः);
                प्रत्यागम false;
            }
            प्रत्यागम true;
#अन्यथा
            प्रत्यागम SDL_समुच्चयः_Error("Could not create GLES window surface (EGL support not configured)");
#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL
        }
#यदि_अन्तः // SDL_VIDEO_OPENGL_ES2

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
        यदि (!WIN_GL_सज्जता_गवाक्षः(_this, गवाक्षः)) {
            WIN_Destroy_गवाक्षः(_this, गवाक्षः);
            प्रत्यागम false;
        }
#अन्यथा
        प्रत्यागम SDL_समुच्चयः_Error("Could not create GL window (WGL support not configured)");
#यदि_अन्तः
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    प्रत्यागम true;
}

शून्य WIN_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    LPTSTR title = WIN_UTF8_गन्तव्यम्_String(गवाक्षः->title);
    समुच्चयः_गवाक्षः_Text(hwnd, title);
    SDL_free(title);
#यदि_अन्तः
}

bool WIN_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    HICON hicon = रिक्त;
    BYTE *icon_bmp;
    पूर्णाङ्क icon_len, आवरणम्_len, row_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool परिणाम = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_TIME_ASSERT(WIN_समुच्चयः_गवाक्षः_Icon_उपयुङ्क्ते_BITMAPINFOHEADER_गन्तव्यम्_prepare_an_ICONIMAGE, परिमाण(BITMAPINFOHEADER) == 40);
    आवरणम्_len = (icon->h * (icon->w + 7) / 8);
    icon_len = परिमाण(BITMAPINFOHEADER) + icon->h * icon->w * परिमाण(Uint32) + आवरणम्_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    यदि (!icon_bmp) {
        प्रत्यागम false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_आकार = SDL_Swap32LE(परिमाण(BITMAPINFOHEADER));
    bmi->bi_विस्तारः = SDL_Swap32LE(icon->w);
    bmi->biHeight = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_Bit_गणनम् = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_आकार_Image = SDL_Swap32LE(icon->h * icon->w * परिमाण(Uint32));
    bmi->bi_XPels_प्रत्येकम्_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_प्रत्येकम्_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_प्रयुक्तम् = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[परिमाण(BITMAPINFOHEADER)];
    row_len = icon->w * परिमाण(Uint32);
    y = icon->h;
    यावत् (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, row_len);
        dst += row_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - आवरणम्_len, 0xFF, आवरणम्_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    यदि (!hicon) {
        प्रत्यागम SDL_समुच्चयः_Error("SetWindowIcon() failed, error %08X", (अचिह्नित पूर्णाङ्क)Get_चरमः_Error());
    }

    यदि (दत्त->hicon) {
        DestroyIcon(दत्त->hicon);
    }
    दत्त->hicon = hicon;

    // Set the icon for the window
    Send_सन्देशः(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_सन्देशः(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    प्रत्यागम परिणाम;
#अन्यथा
    प्रत्यागम SDL_Unsupported();
#यदि_अन्तः
}

bool WIN_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        यदि (!(गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED))) {
            WIN_ConstrainPopup(गवाक्षः, true);
            प्रत्यागम WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(गवाक्षः,
                                                 गवाक्षः->आन्तरिकम्->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } अन्यथा {
        प्रत्यागम SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_ENTER, true);
    }

    प्रत्यागम true;
}

शून्य WIN_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (!(गवाक्षः->flags & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED))) {
        WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(गवाक्षः, गवाक्षः->आन्तरिकम्->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } अन्यथा {
        // Can't resize the window
        गवाक्षः->चरमः_आकार_pending = false;
    }
}

bool WIN_Get_गवाक्षः_Borders_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः)
{
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *शिखरम् = rcClient.शिखरम्;
    *वामः = rcClient.वामः;
    *bottom = rcClient.bottom;
    *दक्षिणः = rcClient.दक्षिणः;

    प्रत्यागम true;
#अन्यथा  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    RECT rcClient, rc_गवाक्षः;
    POINT ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    यदि (!GetClientRect(hwnd, &rcClient)) {
        प्रत्यागम SDL_समुच्चयः_Error("GetClientRect() failed, error %08X", (अचिह्नित पूर्णाङ्क)Get_चरमः_Error());
    }

    यदि (!Get_गवाक्षः_Rect(hwnd, &rc_गवाक्षः)) {
        प्रत्यागम SDL_समुच्चयः_Error("GetWindowRect() failed, error %08X", (अचिह्नित पूर्णाङ्क)Get_चरमः_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_गवाक्षः.शिखरम्;
    ptDiff.x = rc_गवाक्षः.वामः;

    यदि (!Screen_गन्तव्यम्_Client(hwnd, &ptDiff)) {
        प्रत्यागम SDL_समुच्चयः_Error("ScreenToClient() failed, error %08X", (अचिह्नित पूर्णाङ्क)Get_चरमः_Error());
    }

    rc_गवाक्षः.शिखरम् = ptDiff.y;
    rc_गवाक्षः.वामः = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_गवाक्षः.bottom;
    ptDiff.x = rc_गवाक्षः.दक्षिणः;

    यदि (!Screen_गन्तव्यम्_Client(hwnd, &ptDiff)) {
        प्रत्यागम SDL_समुच्चयः_Error("ScreenToClient() failed, error %08X", (अचिह्नित पूर्णाङ्क)Get_चरमः_Error());
    }

    rc_गवाक्षः.bottom = ptDiff.y;
    rc_गवाक्षः.दक्षिणः = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *शिखरम् = rcClient.शिखरम् - rc_गवाक्षः.शिखरम्;
    *वामः = rcClient.वामः - rc_गवाक्षः.वामः;
    *bottom = rc_गवाक्षः.bottom - rcClient.bottom;
    *दक्षिणः = rc_गवाक्षः.दक्षिणः - rcClient.दक्षिणः;

    प्रत्यागम true;
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

शून्य WIN_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    ध्रुव SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    RECT rect;

    यदि (GetClientRect(hwnd, &rect) && WIN_गवाक्षः_Rect_Valid(&rect)) {
        *w = rect.दक्षिणः;
        *h = rect.bottom;
    } अन्यथा यदि (गवाक्षः->चरमः_pixel_w && गवाक्षः->चरमः_pixel_h) {
        *w = गवाक्षः->चरमः_pixel_w;
        *h = गवाक्षः->चरमः_pixel_h;
    } अन्यथा {
        // Probably created minimized, use the restored size
        *w = गवाक्षः->floating.w;
        *h = गवाक्षः->floating.h;
    }
}

शून्य WIN_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ACTIVATE_WHEN_SHOWN, true);

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        // Update our position in case our parent moved while we were hidden
        WIN_समुच्चयः_गवाक्षः_Position(_this, गवाक्षः);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    यदि (गवाक्षः->pending_flags & SDL_गवाक्षः_FULLSCREEN) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS)) {
            गवाक्षः->flags |= SDL_गवाक्षः_BORDERLESS;
            style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_आवरणम्;
            style |= Get_गवाक्षः_Style(गवाक्षः);
            समुच्चयः_गवाक्षः_Long(hwnd, GWL_STYLE, style);
            गवाक्षः->flags &= ~SDL_गवाक्षः_BORDERLESS;
        }
    }
    style = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);
    यदि (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    दत्त->showing_गवाक्षः = true;
    यदि (bActivate) {
        Show_गवाक्षः(hwnd, SW_SHOW);
    } अन्यथा {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        समुच्चयः_गवाक्षः_Pos(hwnd, रिक्त, 0, 0, 0, 0, गवाक्षः->आन्तरिकम्->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    दत्त->showing_गवाक्षः = false;

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE) && bActivate) {
        WIN_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
    }
    यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        WIN_समुच्चयः_गवाक्षः_Modal(_this, गवाक्षः, true);
    }
}

शून्य WIN_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;

    यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        WIN_समुच्चयः_गवाक्षः_Modal(_this, गवाक्षः, false);
    }

    Show_गवाक्षः(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
        SDL_गवाक्षः *new_focus;
        ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(गवाक्षः, &new_focus);
        WIN_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
    }
}

शून्य WIN_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* If desired, raise the window more forcefully.
     * Technique taken from http://stackoverflow.com/questions/916259/ .
     * Specifically, http://stackoverflow.com/a/34414846 .
     *
     * The issue is that Microsoft has gone through a lot of trouble to make it
     * nearly impossible to programmatically move a window to the foreground,
     * for "security" reasons. Apparently, the following song-and-dance gets
     * around their objections. */
    bool bForce = SDL_GetHintBoolean(SDL_HINT_FORCE_RAISEWINDOW, false);
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = रिक्त;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    यदि (bForce) {
        hCurWnd = Get_Foreground_गवाक्षः();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_गवाक्षः_Thread_Process_Id(hCurWnd, रिक्त);
        Show_गवाक्षः(hwnd, SW_RESTORE);
        Attach_Thread_निवेशः(dwCurID, dwMyID, TRUE);
        समुच्चयः_गवाक्षः_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        यदि (!SDL_ShouldAllowTopmost() || !(गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्)) {
            समुच्चयः_गवाक्षः_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    यदि (bActivate) {
        समुच्चयः_Foreground_गवाक्षः(hwnd);
        यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
            WIN_समुच्चयः_Keyboard_Focus(गवाक्षः, गवाक्षः->parent == SDL_GetKeyboardFocus());
        }
    } अन्यथा {
        समुच्चयः_गवाक्षः_Pos(hwnd, HWND_शिखरम्, 0, 0, 0, 0, दत्त->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    यदि (bForce) {
        Attach_Thread_निवेशः(dwCurID, dwMyID, FALSE);
        समुच्चयः_Focus(hwnd);
        समुच्चयः_सक्रिय_गवाक्षः(hwnd);
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

शून्य WIN_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        HWND hwnd = दत्त->hwnd;
        दत्त->expected_resize = true;
        Show_गवाक्षः(hwnd, SW_MAXIMIZE);
        दत्त->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        यदि (गवाक्षः->max_w || गवाक्षः->max_h) {
            पूर्णाङ्क fx, fy, fw, fh;

            गवाक्षः->windowed.w = गवाक्षः->max_w ? SDL_min(गवाक्षः->w, गवाक्षः->max_w) : गवाक्षः->windowed.w;
            गवाक्षः->windowed.h = गवाक्षः->max_h ? SDL_min(गवाक्षः->h, गवाक्षः->max_h) : गवाक्षः->windowed.h;
            WIN_Adjust_गवाक्षः_Rect(गवाक्षः, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            दत्त->expected_resize = true;
            समुच्चयः_गवाक्षः_Pos(hwnd, HWND_शिखरम्, fx, fy, fw, fh, दत्त->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            दत्त->expected_resize = false;
        }
    } अन्यथा {
        दत्त->windowed_बहुलकम्_was_maximized = true;
    }
}

शून्य WIN_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    HWND hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    Show_गवाक्षः(hwnd, SW_MINIMIZE);
}

शून्य WIN_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    DWORD style;

    style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_आवरणम्;
    style |= Get_गवाक्षः_Style(गवाक्षः);

    दत्त->अन्तर्_border_change = true;
    समुच्चयः_गवाक्षः_Long(hwnd, GWL_STYLE, style);
    WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(गवाक्षः, दत्त->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    दत्त->अन्तर्_border_change = false;
}

शून्य WIN_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    DWORD style;

    style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_आवरणम्;
    style |= Get_गवाक्षः_Style(गवाक्षः);

    समुच्चयः_गवाक्षः_Long(hwnd, GWL_STYLE, style);
}

शून्य WIN_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्)
{
    WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(गवाक्षः, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

शून्य WIN_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        यदि (!दत्त->showing_गवाक्षः || गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED)) {
            HWND hwnd = दत्त->hwnd;
            दत्त->expected_resize = true;
            Show_गवाक्षः(hwnd, SW_RESTORE);
            दत्त->expected_resize = false;
        }
    } अन्यथा {
        दत्त->windowed_बहुलकम्_was_maximized = false;
    }
}

स्थिर शून्य WIN_UpdateCornerRoundingForHWND(SDL_VideoDevice *_this, HWND hwnd, DWM_गवाक्षः_CORNER_PREFERENCE cornerPref)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    यदि (videodata->Dwm_समुच्चयः_गवाक्षः_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_समुच्चयः_गवाक्षः_Attribute(hwnd, DWMWA_गवाक्षः_CORNER_PREFERENCE, &cornerPref, परिमाण(cornerPref));
    }
#यदि_अन्तः
}

स्थिर शून्य WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    यदि (videodata->Dwm_समुच्चयः_गवाक्षः_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_समुच्चयः_गवाक्षः_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, परिमाण(colorRef));
    }
#यदि_अन्तः
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_परिणाम WIN_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त ? दत्त->hwnd : रिक्त;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND शिखरम्;
    पूर्णाङ्क x, y;
    पूर्णाङ्क w, h;
    bool enterMaximized = false;

#यदि_परिभाषितम् HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (पूर्णाङ्क)fullscreen);
#यदि_अन्तः

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && !fullscreen) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (SDL_ShouldAllowTopmost() && (गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्)) {
        शिखरम् = HWND_TOPMOST;
    } अन्यथा {
        शिखरम् = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_आकार = परिमाण(MONITORINFO);
    यदि (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_समुच्चयः_Error("GetMonitorInfo failed");
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_गवाक्षः_Event(गवाक्षः, fullscreen ? SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN : SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
    style = Get_गवाक्षः_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_आवरणम्;
    style |= Get_गवाक्षः_Style(गवाक्षः);
    styleEx = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);

    यदि (fullscreen) {
        x = minfo.rcMonitor.वामः;
        y = minfo.rcMonitor.शिखरम्;
        w = minfo.rcMonitor.दक्षिणः - minfo.rcMonitor.वामः;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.शिखरम्;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        यदि (style & WS_MAXIMIZE) {
            दत्त->windowed_बहुलकम्_was_maximized = true;
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
        यदि (दत्त->windowed_बहुलकम्_was_maximized && !दत्त->अन्तर्_गवाक्षः_deactivation) {
            enterMaximized = true;
            दत्त->disable_move_आकार_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != रिक्त);
        WIN_Adjust_गवाक्षः_Rect_With_Style(गवाक्षः, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        दत्त->windowed_बहुलकम्_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        यदि (enterMaximized) {
            ध्रुव SDL_Point windowed_point = { गवाक्षः->windowed.x, गवाक्षः->windowed.y };
            ध्रुव SDL_Point floating_point = { गवाक्षः->floating.x, गवाक्षः->floating.y };
            ध्रुव SDL_DisplayID floating_display = SDL_GetDisplayForPoint(&floating_point);
            ध्रुव SDL_DisplayID windowed_display = SDL_GetDisplayForPoint(&windowed_point);

            यदि (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                यदि (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } अन्यथा {
                    x = bounds.x;
                }
                यदि (h < bounds.h) {
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
    समुच्चयः_गवाक्षः_Long(hwnd, GWL_STYLE, style);
    दत्त->expected_resize = true;
    समुच्चयः_गवाक्षः_Pos(hwnd, शिखरम्, x, y, w, h, दत्त->copybits_flag | SWP_NOACTIVATE);
    दत्त->expected_resize = false;
    दत्त->disable_move_आकार_events = false;

    यदि (enterMaximized) {
        WIN_Maximize_गवाक्षः(_this, गवाक्षः);
    }

    यदि (!fullscreen && दत्त && दत्त->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_सन्देशः(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_सन्देशः(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)दत्त->hicon);
    }

#यदि_परिभाषितम् HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (पूर्णाङ्क)fullscreen, x, y, w, h);
#यदि_अन्तः

#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
शून्य WIN_Update_गवाक्षः_ICCProfile(SDL_गवाक्षः *गवाक्षः, bool send_event)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);

    यदि (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, रिक्त, रिक्त, रिक्त);
        यदि (hdc) {
            WCHAR fileName[MAX_मार्गः];
            DWORD file_Name_आकार = SDL_arraysize(fileName);
            यदि (GetICMProfileW(hdc, &file_Name_आकार, fileName)) {
                // fileNameSize includes '\0' on return
                यदि (!दत्त->ICMFileName ||
                    SDL_wcscmp(दत्त->ICMFileName, fileName) != 0) {
                    SDL_free(दत्त->ICMFileName);
                    दत्त->ICMFileName = SDL_wcsdup(fileName);
                    यदि (send_event) {
                        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_ICCPROF_परिवर्तितम्, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

शून्य *WIN_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    वर्ण *filename_utf8;
    शून्य *icc_Profile_दत्त = रिक्त;

    filename_utf8 = WIN_String_गन्तव्यम्_UTF8_W(दत्त->ICMFileName);
    यदि (filename_utf8) {
        icc_Profile_दत्त = SDL_आरोपय_File(filename_utf8, आकार);
        यदि (!icc_Profile_दत्त) {
            SDL_समुच्चयः_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    प्रत्यागम icc_Profile_दत्त;
}

स्थिर शून्य WIN_GrabKeyboard(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HMODULE module;

    यदि (दत्त->keyboard_hook) {
        प्रत्यागम;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    यदि (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_स्थानाङ्कः,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        प्रत्यागम;
    }

    // Capture a snapshot of the current keyboard state before the hook
    यदि (!GetKeyboardState(दत्त->videodata->pre_hook_कुञ्चिका_state)) {
        प्रत्यागम;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    दत्त->keyboard_hook = समुच्चयः_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

शून्य WIN_UngrabKeyboard(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त->keyboard_hook) {
        UnhookWindowsHookEx(दत्त->keyboard_hook);
        दत्त->keyboard_hook = रिक्त;
    }
}

bool WIN_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    WIN_UpdateClipCursor(गवाक्षः);
    प्रत्यागम true;
}

bool WIN_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    WIN_UpdateClipCursor(गवाक्षः);
    प्रत्यागम true;
}

bool WIN_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    यदि (grabbed) {
        WIN_GrabKeyboard(गवाक्षः);
    } अन्यथा {
        WIN_UngrabKeyboard(गवाक्षः);
    }

    प्रत्यागम true;
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

शून्य WIN_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    Cleanup_गवाक्षः_दत्त(_this, गवाक्षः);
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
शून्य WIN_On_गवाक्षः_Enter(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (!दत्त || !दत्त->hwnd) {
        // The window wasn't fully initialized
        प्रत्यागम;
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्) {
        WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(गवाक्षः, दत्त->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

स्थिर BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    प्रत्यागम GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_गन्तव्यम्_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_गन्तव्यम्_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

शून्य WIN_Unclip_Cursor_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः) {
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    RECT rect;
    यदि (GetClipCursor(&rect) && SDL_memcmp(&rect, &दत्त->cursor_clipped_rect, परिमाण(rect)) == 0) {
        ClipCursor(रिक्त);
        SDL_zero(दत्त->cursor_clipped_rect);
    }
}

शून्य WIN_UpdateClipCursor(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Video_दत्त *videodata = दत्त->videodata;
    यदि (दत्त->अन्तर्_title_click || दत्त->focus_click_pending || दत्त->postpone_clipcursor) {
        प्रत्यागम;
    }

    SDL_Rect mouse_rect = गवाक्षः->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS);
    bool win_is_grabbed = (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED);
    bool win_अन्तर्_relmode = (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्);
    bool cursor_confine = win_अन्तर्_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    यदि (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        यदि (!GetClipCursor(&current)) {
            प्रत्यागम;
        }
        यदि (videodevice && (
            current.वामः != videodevice->desktop_bounds.x ||
            current.शिखरम्  != videodevice->desktop_bounds.y
        )) {
            POINT first, second;
            first.x  = current.वामः;
            first.y  = current.शिखरम्;
            second.x = current.दक्षिणः  - 1;
            second.y = current.bottom - 1;
            यदि (!Pt_अन्तर्_Rect(&दत्त->cursor_clipped_rect, first) ||
                !Pt_अन्तर्_Rect(&दत्त->cursor_clipped_rect, second)) {
                प्रत्यागम;
            }
        }
        ClipCursor(रिक्त);
        SDL_zero(दत्त->cursor_clipped_rect);
        प्रत्यागम;
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
    bool तालकम्_गन्तव्यम्_ctr = (mouse->relative_बहुलकम् && mouse->relative_बहुलकम्_center);

    RECT client;
    यदि (!GetClientScreenRect(दत्त->hwnd, &client)) {
        प्रत्यागम;
    }

    RECT target = client;
    यदि (तालकम्_गन्तव्यम्_ctr) {
        LONG cx = (client.वामः + client.दक्षिणः ) / 2;
        LONG cy = (client.शिखरम्  + client.bottom) / 2;
        target = दत्त->cursor_ctrlock_rect;
        target.वामः   += cx;
        target.दक्षिणः  += cx;
        target.शिखरम्    += cy;
        target.bottom += cy;
    } अन्यथा यदि (win_mouse_rect) {
        RECT custom, overlap;
        custom.वामः   = client.वामः + mouse_rect.x;
        custom.शिखरम्    = client.शिखरम्  + mouse_rect.y;
        custom.दक्षिणः  = client.वामः + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.शिखरम्  + mouse_rect.y + mouse_rect.h;
        यदि (IntersectRect(&overlap, &client, &custom)) {
            target = overlap;
        } अन्यथा यदि (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_गवाक्षः(गवाक्षः);
            प्रत्यागम;
        }
    } अन्यथा यदि (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        यदि (videodata->समुच्चयः_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_प्रत्येकम्_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_गवाक्षः(दत्त->hwnd, MONITOR_DEFAULTTONEAREST);
            यदि (hmon) {
                UINT hdpi_uint, vdpi_uint;
                यदि (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ध्रुव भिन्न scale = (भिन्न)hdpi_uint / (भिन्न)USER_DEFAULT_SCREEN_DPI;
                    यदि (scale != SDL_floorf(scale)) {
                        यदि (target.वामः < target.दक्षिणः) {
                            target.वामः += 1;
                        }
                        यदि (target.दक्षिणः > target.वामः) {
                            target.दक्षिणः -= 1;
                        }
                        यदि (target.शिखरम् < target.bottom) {
                            target.शिखरम् += 1;
                        }
                        यदि (target.bottom > target.शिखरम्) {
                            target.bottom -= 1;
                        }
                    }
                }
            }
            videodata->समुच्चयः_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    यदि (GetClipCursor(&client) &&
        0 != SDL_memcmp(&target, &client, परिमाण(client)) &&
        ClipCursor(&target)) {
        दत्त->cursor_clipped_rect = target; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled)
{
    प्रत्यागम true; // just succeed, the real work is done elsewhere.
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity)
{
#यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    प्रत्यागम false;
#अन्यथा
    ध्रुव SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    ध्रुव LONG style = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);

    यदि (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        यदि (style & WS_EX_LAYERED) {
            यदि (समुच्चयः_गवाक्षः_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                प्रत्यागम WIN_समुच्चयः_Error("SetWindowLong()");
            }
        }
    } अन्यथा {
        ध्रुव BYTE alpha = (BYTE)((पूर्णाङ्क)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        यदि (!(style & WS_EX_LAYERED)) {
            यदि (समुच्चयः_गवाक्षः_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                प्रत्यागम WIN_समुच्चयः_Error("SetWindowLong()");
            }
        }

        यदि (समुच्चयः_Layered_गवाक्षः_गुणाः(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            प्रत्यागम WIN_समुच्चयः_Error("SetLayeredWindowAttributes()");
        }
    }

    प्रत्यागम true;
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

स्थिर ध्रुव वर्ण *SDLGetClipboardFormatName(UINT cf, वर्ण *text, पूर्णाङ्क len)
{
    विकल्प (cf) {
    पक्ष CF_TEXT:
        प्रत्यागम "CF_TEXT";
    पक्ष CF_BITMAP:
        प्रत्यागम "CF_BITMAP";
    पक्ष CF_METAFILEPICT:
        प्रत्यागम "CF_METAFILEPICT";
    पक्ष CF_SYLK:
        प्रत्यागम "CF_SYLK";
    पक्ष CF_DIF:
        प्रत्यागम "CF_DIF";
    पक्ष CF_TIFF:
        प्रत्यागम "CF_TIFF";
    पक्ष CF_OEMTEXT:
        प्रत्यागम "CF_OEMTEXT";
    पक्ष CF_DIB:
        प्रत्यागम "CF_DIB";
    पक्ष CF_PALETTE:
        प्रत्यागम "CF_PALETTE";
    पक्ष CF_PENDATA:
        प्रत्यागम "CF_PENDATA";
    पक्ष CF_RIFF:
        प्रत्यागम "CF_RIFF";
    पक्ष CF_WAVE:
        प्रत्यागम "CF_WAVE";
    पक्ष CF_UNICODETEXT:
        प्रत्यागम "CF_UNICODETEXT";
    पक्ष CF_ENHMETAFILE:
        प्रत्यागम "CF_ENHMETAFILE";
    पक्ष CF_HDROP:
        प्रत्यागम "CF_HDROP";
    पक्ष CF_LOCALE:
        प्रत्यागम "CF_LOCALE";
    पक्ष CF_DIBV5:
        प्रत्यागम "CF_DIBV5";
    पक्ष CF_OWNERDISPLAY:
        प्रत्यागम "CF_OWNERDISPLAY";
    पक्ष CF_DSPTEXT:
        प्रत्यागम "CF_DSPTEXT";
    पक्ष CF_DSPBITMAP:
        प्रत्यागम "CF_DSPBITMAP";
    पक्ष CF_DSPMETAFILEPICT:
        प्रत्यागम "CF_DSPMETAFILEPICT";
    पक्ष CF_DSPENHMETAFILE:
        प्रत्यागम "CF_DSPENHMETAFILE";
    स्वभाव:
        यदि (GetClipboardFormatNameA(cf, text, len)) {
            प्रत्यागम text;
        } अन्यथा {
            प्रत्यागम रिक्त;
        }
    }
}

स्थिर STDMETHODIMP_(ULONG) SDLDrop_Target_सङ्कलय_Ref(SDLDropTarget *target)
{
    प्रत्यागम ++target->refcount;
}

स्थिर STDMETHODIMP_(ULONG) SDLDropTarget_Release(SDLDropTarget *target)
{
    --target->refcount;
    यदि (target->refcount == 0) {
        SDL_free(target);
        प्रत्यागम 0;
    }
    प्रत्यागम target->refcount;
}

स्थिर STDMETHODIMP SDLDropTarget_QueryInterface(SDLDropTarget *target, REFIID riid, PVOID *ppv)
{
    यदि (ppv == रिक्त) {
        प्रत्यागम E_INVALIDARG;
    }

    *ppv = रिक्त;
    यदि (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDropTarget)) {
        *ppv = (शून्य *)target;
    }
    यदि (*ppv) {
        SDLDrop_Target_सङ्कलय_Ref(target);
        प्रत्यागम S_OK;
    }
    प्रत्यागम E_NOINTERFACE;
}

स्थिर STDMETHODIMP SDLDropTarget_DragEnter(SDLDropTarget *target,
                                            IDataObject *p_दत्त_Object, DWORD grf_कुञ्चिका_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    यदि (Screen_गन्तव्यम्_Client(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->गवाक्षः->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->गवाक्षः, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    प्रत्यागम S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_DragOver(SDLDropTarget *target,
                                           DWORD grf_कुञ्चिका_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    यदि (Screen_गन्तव्यम्_Client(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->गवाक्षः->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->गवाक्षः, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    प्रत्यागम S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_DragLeave(SDLDropTarget *target)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In DragLeave");
    SDL_SendDropComplete(target->गवाक्षः);
    प्रत्यागम S_OK;
}

स्थिर STDMETHODIMP SDLDropTarget_Drop(SDLDropTarget *target,
                                       IDataObject *p_दत्त_Object, DWORD grf_कुञ्चिका_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    POINT pnt = { pt.x, pt.y };
    यदि (Screen_गन्तव्यम्_Client(target->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, target->गवाक्षः->id, pnt.x, pnt.y);
        SDL_SendDropPosition(target->गवाक्षः, pnt.x, pnt.y);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_दत्त_Object->lpVtbl->EnumFormatEtc(p_दत्त_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        यदि (hres == S_OK) {
            FORMATETC fetc;
            यावत् (pEnumFormatEtc->lpVtbl->अग्र_3(pEnumFormatEtc, 1, &fetc, रिक्त) == S_OK) {
                वर्ण name[257] = { 0 };
                ध्रुव वर्ण *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                यदि (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } अन्यथा {
                    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
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
        ध्रुव वर्ण *format_mime = "text/uri-list";
        यदि (SUCCEEDED(p_दत्त_Object->lpVtbl->Query_Get_दत्त(p_दत्त_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_दत्त_Object->lpVtbl->Get_दत्त(p_दत्त_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            यदि (SUCCEEDED(hres)) {
                ध्रुव size_t bsize = Global_आकार(med.hGlobal);
                ध्रुव शून्य *बफर_2 = (शून्य *)Global_तालकम्(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)bsize, बफर_2);
                यदि (बफर_2) {
                    वर्ण *text = (वर्ण *)SDL_malloc(bsize + परिमाण(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, परिमाण(Uint32));
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    यावत् (token != रिक्त) {
                        यदि (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिह्नित दीर्घ)SDL_strlen(token), (अचिह्नित दीर्घ)bsize, token);
                            SDL_SendDropFile(target->गवाक्षः, रिक्त, token);
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->गवाक्षः);
                प्रत्यागम S_OK;
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
        ध्रुव वर्ण *format_mime = "text/plain;charset=utf-8";
        यदि (SUCCEEDED(p_दत्त_Object->lpVtbl->Query_Get_दत्त(p_दत्त_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_दत्त_Object->lpVtbl->Get_दत्त(p_दत्त_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            यदि (SUCCEEDED(hres)) {
                ध्रुव size_t bsize = Global_आकार(med.hGlobal);
                ध्रुव शून्य *बफर_2 = (शून्य *)Global_तालकम्(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)bsize, बफर_2);
                यदि (बफर_2) {
                    वर्ण *text = (वर्ण *)SDL_malloc(bsize + परिमाण(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, परिमाण(Uint32));
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    यावत् (token != रिक्त) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिह्नित दीर्घ)SDL_strlen(token), (अचिह्नित दीर्घ)bsize, token);
                        SDL_SendDropText(target->गवाक्षः, (वर्ण *)token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->गवाक्षः);
                प्रत्यागम S_OK;
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
        ध्रुव वर्ण *format_mime = "CF_UNICODETEXT";
        यदि (SUCCEEDED(p_दत्त_Object->lpVtbl->Query_Get_दत्त(p_दत्त_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_दत्त_Object->lpVtbl->Get_दत्त(p_दत्त_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            यदि (SUCCEEDED(hres)) {
                ध्रुव size_t bsize = Global_आकार(med.hGlobal);
                ध्रुव शून्य *बफर_2 = (शून्य *)Global_तालकम्(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)bsize, बफर_2);
                यदि (बफर_2) {
                    बफर_2 = WIN_String_गन्तव्यम्_UTF8_W((ध्रुव wchar_t *)बफर_2);
                    यदि (बफर_2) {
                        ध्रुव size_t lbuffer = SDL_strlen((ध्रुव वर्ण *)बफर_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)lbuffer, बफर_2);
                        वर्ण *text = (वर्ण *)SDL_malloc(lbuffer + परिमाण(Uint32));
                        SDL_memcpy((Uint8 *)text, बफर_2, lbuffer);
                        SDL_memset((Uint8 *)text + lbuffer, 0, परिमाण(Uint32));
                        वर्ण *saveptr = रिक्त;
                        वर्ण *token = SDL_strtok_r(text, "\r\n", &saveptr);
                        यावत् (token != रिक्त) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (अचिह्नित दीर्घ)SDL_strlen(token), (अचिह्नित दीर्घ)lbuffer, token);
                            SDL_SendDropText(target->गवाक्षः, (वर्ण *)token);
                            token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                        }
                        SDL_free(text);
                        SDL_free((शून्य *)बफर_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->गवाक्षः);
                प्रत्यागम S_OK;
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
        ध्रुव वर्ण *format_mime = "CF_TEXT";
        यदि (SUCCEEDED(p_दत्त_Object->lpVtbl->Query_Get_दत्त(p_दत्त_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_दत्त_Object->lpVtbl->Get_दत्त(p_दत्त_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            यदि (SUCCEEDED(hres)) {
                ध्रुव size_t bsize = Global_आकार(med.hGlobal);
                ध्रुव शून्य *बफर_2 = (शून्य *)Global_तालकम्(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)bsize, बफर_2);
                यदि (बफर_2) {
                    वर्ण *text = (वर्ण *)SDL_malloc(bsize + परिमाण(Uint32));
                    SDL_memcpy((Uint8 *)text, बफर_2, bsize);
                    SDL_memset((Uint8 *)text + bsize, 0, परिमाण(Uint32));
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r(text, "\r\n", &saveptr);
                    यावत् (token != रिक्त) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (अचिह्नित दीर्घ)SDL_strlen(token), (अचिह्नित दीर्घ)bsize, token);
                        SDL_SendDropText(target->गवाक्षः, (वर्ण *)token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(text);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->गवाक्षः);
                प्रत्यागम S_OK;
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
        ध्रुव वर्ण *format_mime = "CF_HDROP";
        यदि (SUCCEEDED(p_दत्त_Object->lpVtbl->Query_Get_दत्त(p_दत्त_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_दत्त_Object->lpVtbl->Get_दत्त(p_दत्त_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            यदि (SUCCEEDED(hres)) {
                ध्रुव size_t bsize = Global_आकार(med.hGlobal);
                HDROP drop = (HDROP)Global_तालकम्(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (अचिह्नित दीर्घ)bsize, drop);
                UINT गणनम् = DragQueryFile(drop, 0xFFFFFFFF, रिक्त, 0);
                प्रति (UINT i = 0; i < गणनम्; ++i) {
                    UINT आकार = DragQueryFile(drop, i, रिक्त, 0) + 1;
                    LPTSTR बफर_2 = (LPTSTR)SDL_malloc(आकार * परिमाण(TCHAR));
                    यदि (बफर_2) {
                        यदि (DragQueryFile(drop, i, बफर_2, आकार)) {
                            वर्ण *file = WIN_String_गन्तव्यम्_UTF8(बफर_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (अचिह्नित दीर्घ)SDL_strlen(file), (अचिह्नित दीर्घ)bsize, file);
                            SDL_SendDropFile(target->गवाक्षः, रिक्त, file);
                            SDL_free(file);
                        }
                        SDL_free(बफर_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(target->गवाक्षः);
                प्रत्यागम S_OK;
            }
        }
    }

    SDL_SendDropComplete(target->गवाक्षः);
    प्रत्यागम S_OK;
}

स्थिर शून्य *vtDropTarget[] = {
    (शून्य *)(SDLDropTarget_QueryInterface),
    (शून्य *)(SDLDrop_Target_सङ्कलय_Ref),
    (शून्य *)(SDLDropTarget_Release),
    (शून्य *)(SDLDropTarget_DragEnter),
    (शून्य *)(SDLDropTarget_DragOver),
    (शून्य *)(SDLDropTarget_DragLeave),
    (शून्य *)(SDLDropTarget_Drop)
};

शून्य WIN_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    यदि (दत्त->videodata->oleinitialized) {
        यदि (accept && !दत्त->drop_target) {
            SDLDropTarget *drop_target = (SDLDropTarget *)SDL_calloc(1, परिमाण(SDLDropTarget));
            यदि (drop_target != रिक्त) {
                drop_target->lpVtbl = vtDropTarget;
                drop_target->गवाक्षः = गवाक्षः;
                drop_target->hwnd = दत्त->hwnd;
                drop_target->format_file = पञ्जिकाकोशः_Clipboard_Format_W(L"text/uri-list");
                drop_target->format_text = पञ्जिकाकोशः_Clipboard_Format_W(L"text/plain;charset=utf-8");
                दत्त->drop_target = drop_target;
                SDLDrop_Target_सङ्कलय_Ref(drop_target);
                पञ्जिकाकोशः_Drag_Drop(दत्त->hwnd, (LPDROPTARGET)drop_target);
                SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             गवाक्षः->id);
            }
        } अन्यथा यदि (!accept && दत्त->drop_target) {
            RevokeDragDrop(दत्त->hwnd);
            SDLDropTarget_Release(दत्त->drop_target);
            दत्त->drop_target = रिक्त;
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         गवाक्षः->id);
        }
    } अन्यथा {
        DragAcceptFiles(दत्त->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     गवाक्षः->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_आकार = परिमाण(desc);
    desc.hwnd = गवाक्षः->आन्तरिकम्->hwnd;
    विकल्प (operation) {
    पक्ष SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        भङ्ग;
    पक्ष SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_गणनम् = 1;
        भङ्ग;
    पक्ष SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_Unsupported();
    }

    Flash_गवाक्षः_Ex(&desc);

    प्रत्यागम true;
}

bool WIN_Apply_गवाक्षः_प्रगतिः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    यदि (!दत्त->taskbar_button_created) {
        प्रत्यागम true;
    }

    यदि (गवाक्षः->प्रगतिः_state == SDL_प्रगतिः_STATE_NONE && !दत्त->videodata->taskbar_list) {
        प्रत्यागम true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(गवाक्षः);
    यदि (!taskbar_list) {
        प्रत्यागम false;
    }

    TBPFLAG tbpFlags;
    विकल्प (गवाक्षः->प्रगतिः_state) {
    पक्ष SDL_प्रगतिः_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        भङ्ग;
    पक्ष SDL_प्रगतिः_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        भङ्ग;
    पक्ष SDL_प्रगतिः_STATE_प्रसामान्यम्:
        tbpFlags = TBPF_प्रसामान्यम्;
        भङ्ग;
    पक्ष SDL_प्रगतिः_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        भङ्ग;
    पक्ष SDL_प्रगतिः_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_समुच्चयः_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->समुच्चयः_प्रगतिः_State(taskbar_list, दत्त->hwnd, tbpFlags);
    यदि (FAILED(ret)) {
        प्रत्यागम WIN_समुच्चयः_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    यदि (गवाक्षः->प्रगतिः_state >= SDL_प्रगतिः_STATE_प्रसामान्यम्) {
        ret = taskbar_list->lpVtbl->समुच्चयः_प्रगतिः_मानम्(taskbar_list, दत्त->hwnd, (ULONGLONG)(गवाक्षः->प्रगतिः_मानम् * 10000.f), 10000);
        यदि (FAILED(ret)) {
            प्रत्यागम WIN_समुच्चयः_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#यदि_अन्तः
    प्रत्यागम true;
}

शून्य WIN_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y)
{
    ध्रुव SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    POINT pt;

    pt.x = x;
    pt.y = y;
    Client_गन्तव्यम्_Screen(दत्त->hwnd, &pt);
    Send_सन्देशः(दत्त->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable)
{
    यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        HWND hwnd = दत्त->hwnd;
        ध्रुव LONG style = Get_गवाक्षः_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        यदि (focusable) {
            यदि (style & WS_EX_NOACTIVATE) {
                यदि (समुच्चयः_गवाक्षः_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    प्रत्यागम WIN_समुच्चयः_Error("SetWindowLong()");
                }
            }
        } अन्यथा {
            यदि (!(style & WS_EX_NOACTIVATE)) {
                यदि (समुच्चयः_गवाक्षः_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    प्रत्यागम WIN_समुच्चयः_Error("SetWindowLong()");
                }
            }
        }
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
            यदि (!focusable && (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
                SDL_गवाक्षः *new_focus;
                ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(गवाक्षः, &new_focus);
                WIN_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
            } अन्यथा यदि (focusable) {
                यदि (SDL_ShouldFocusPopup(गवाक्षः)) {
                    WIN_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
                }
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम true;
}
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_गवाक्षः_दत्त *child_दत्त = गवाक्षः->आन्तरिकम्;
    ध्रुव LONG_PTR parent_hwnd = (LONG_PTR)(parent ? parent->आन्तरिकम्->hwnd : रिक्त);
    ध्रुव DWORD style = Get_गवाक्षः_Long(child_दत्त->hwnd, GWL_STYLE);

    यदि (!(style & WS_CHILD)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        समुच्चयः_गवाक्षः_Long_Ptr(child_दत्त->hwnd, GWLP_HWNDPARENT, parent_hwnd);
    } अन्यथा {
        समुच्चयः_Parent(child_दत्त->hwnd, (HWND)parent_hwnd);
    }
#यदि_अन्तः /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    प्रत्यागम true;
}

bool WIN_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal)
{
#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ध्रुव HWND parent_hwnd = गवाक्षः->parent->आन्तरिकम्->hwnd;

    यदि (modal) {
        // Disable the parent window.
        Enable_गवाक्षः(parent_hwnd, FALSE);
    } अन्यथा यदि (!(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
        // Re-enable the parent window
        Enable_गवाक्षः(parent_hwnd, TRUE);
    }
#यदि_अन्तः // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS
