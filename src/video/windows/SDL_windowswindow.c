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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_windows.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_dropevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowskeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowswindow.h"

// Dropfile support
#ਅਨ੍ਤਰ੍ਭਾਵ <shellapi.h>

#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ਅਨ੍ਤਰ੍ਭਾਵ <shobjidl.h>
#ਜੇ_ਅੰਤ

// Windows CE compatibility
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SWP_NOCOPYBITS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_NOCOPYBITS 0
#ਜੇ_ਅੰਤ

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WM_POPUPSYSTEMMENU
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WM_POPUPSYSTEMMENU 0x313
#ਜੇ_ਅੰਤ

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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_ਸਾਧਾਰਨ              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STYLE_ਨਕਾਬ                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_ਸਾਧਾਰਨ | STYLE_RESIZABLE)

ਸਥਿਰ DWORD Get_ਖਿੜਕੀ_Style(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    DWORD style = 0;

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        style |= WS_POPUP;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ਜੇ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ਨਹੀਂਤਾਂ {
                style |= STYLE_BORDERLESS;
            }
        } ਨਹੀਂਤਾਂ {
            style |= STYLE_ਸਾਧਾਰਨ;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ਵਾਪਸ style;
}

ਸਥਿਰ DWORD Get_ਖਿੜਕੀ_Style_Ex(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    DWORD style = 0;

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ) || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ) || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ਵਾਪਸ style;
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਸਥਿਰ ITaskbarList3 *GetTaskbarList(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_assert(ਅੰਕੜੇ->taskbar_button_created);
    ਜੇ (!ਅੰਕੜੇ->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ਨਿਰਾ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&ਅੰਕੜੇ->videodata->taskbar_list);
        ਜੇ (FAILED(ret)) {
            WIN_ਸੈੱਟ_Error_From_HRESULT("Unable to create taskbar list", ret);
            ਵਾਪਸ ਨਿਰਾ;
        }
        ITaskbarList3 *taskbarlist = ਅੰਕੜੇ->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ਜੇ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            ਅੰਕੜੇ->videodata->taskbar_list = ਨਿਰਾ;
            WIN_ਸੈੱਟ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            ਵਾਪਸ ਨਿਰਾ;
        }
    }
    ਵਾਪਸ ਅੰਕੜੇ->videodata->taskbar_list;
}
#ਜੇ_ਅੰਤ

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ਸਥਿਰ bool WIN_Adjust_ਖਿੜਕੀ_Rect_With_Style(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, DWORD style, DWORD styleEx, BOOL menu, ਪੂਰਨ *x, ਪੂਰਨ *y, ਪੂਰਨ *ਚੌੜਾਈ, ਪੂਰਨ *ਉਚਾਈ, SDL_ਖਿੜਕੀ_Rect rect_type)
{
    SDL_Video_ਅੰਕੜੇ *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ : ਨਿਰਾ;
    RECT rect;

    // Client rect, in points
    ਚੋਣ (rect_type) {
    ਹਾਲਤ SDL_WINDOWRECT_CURRENT:
        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->x, ਖਿੜਕੀ->y, x, y);
        *ਚੌੜਾਈ = ਖਿੜਕੀ->w;
        *ਉਚਾਈ = ਖਿੜਕੀ->h;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->windowed.x, ਖਿੜਕੀ->windowed.y, x, y);
        *ਚੌੜਾਈ = ਖਿੜਕੀ->windowed.w;
        *ਉਚਾਈ = ਖਿੜਕੀ->windowed.h;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WINDOWRECT_FLOATING:
        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.x, ਖਿੜਕੀ->floating.y, x, y);
        *ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
        *ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WINDOWRECT_PENDING:
        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->pending.x, ਖਿੜਕੀ->pending.y, x, y);
        *ਚੌੜਾਈ = ਖਿੜਕੀ->pending.w;
        *ਉਚਾਈ = ਖਿੜਕੀ->pending.h;
        ਰੋਕੋ;
    ਮੂਲ:
        // Should never be here
        SDL_assert_release(false);
        *ਚੌੜਾਈ = 0;
        *ਉਚਾਈ = 0;
        ਰੋਕੋ;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ਖੱਬਾ = 0;
    rect.ਸਿਖਰ = 0;
    rect.ਸੱਜਾ = *ਚੌੜਾਈ;
    rect.bottom = *ਉਚਾਈ;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) && !SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_ਖਿੜਕੀ_Rect_Ex(&rect, style, menu, 0);
#ਨਹੀਂਤਾਂ
        ਜੇ (WIN_Is_ਪ੍ਰਤੀ_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ਜੇ (videodata) {
                UINT ਚੌਖਟਾ_dpi;
                SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
                ਚੌਖਟਾ_dpi = (ਅੰਕੜੇ && videodata->Get_Dpi_For_ਖਿੜਕੀ) ? videodata->Get_Dpi_For_ਖਿੜਕੀ(ਅੰਕੜੇ->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ਜੇ (videodata->Adjust_ਖਿੜਕੀ_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, ਚੌਖਟਾ_dpi) == 0) {
                    ਵਾਪਸ WIN_ਸੈੱਟ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (Adjust_ਖਿੜਕੀ_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                ਵਾਪਸ WIN_ਸੈੱਟ_Error("AdjustWindowRectEx()");
            }
        }
#ਜੇ_ਅੰਤ
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ਖੱਬਾ;
    *y += rect.ਸਿਖਰ;
    *ਚੌੜਾਈ = (rect.ਸੱਜਾ - rect.ਖੱਬਾ);
    *ਉਚਾਈ = (rect.bottom - rect.ਸਿਖਰ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? ਖਿੜਕੀ->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? ਖਿੜਕੀ->windowed.x : ਖਿੜਕੀ->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ਖਿੜਕੀ->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? ਖਿੜਕੀ->windowed.y : ਖਿੜਕੀ->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ਖਿੜਕੀ->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? ਖਿੜਕੀ->windowed.w : ਖਿੜਕੀ->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ਖਿੜਕੀ->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? ਖਿੜਕੀ->windowed.h : ਖਿੜਕੀ->h),
            *x, *y, *ਚੌੜਾਈ, *ਉਚਾਈ, ਚੌਖਟਾ_dpi);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

bool WIN_Adjust_ਖਿੜਕੀ_Rect(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *x, ਪੂਰਨ *y, ਪੂਰਨ *ਚੌੜਾਈ, ਪੂਰਨ *ਉਚਾਈ, SDL_ਖਿੜਕੀ_Rect rect_type)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
    styleEx = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ਨਹੀਂਤਾਂ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ਨਿਰਾ);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ WIN_Adjust_ਖਿੜਕੀ_Rect_With_Style(ਖਿੜਕੀ, style, styleEx, menu, x, y, ਚੌੜਾਈ, ਉਚਾਈ, rect_type);
}

bool WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT ਚੌਖਟਾ_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *videodata = videodevice ? videodevice->ਅੰਦਰੂਨੀ : ਨਿਰਾ;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
    styleEx = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ਨਹੀਂਤਾਂ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ਨਿਰਾ);
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_ਖਿੜਕੀ_Rect_Ex(lpRect, style, menu, styleEx);
#ਨਹੀਂਤਾਂ
    ਜੇ (WIN_Is_ਪ੍ਰਤੀ_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ਜੇ (!ਚੌਖਟਾ_dpi) {
            ਚੌਖਟਾ_dpi = videodata->Get_Dpi_For_ਖਿੜਕੀ ? videodata->Get_Dpi_For_ਖਿੜਕੀ(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ਜੇ (!videodata->Adjust_ਖਿੜਕੀ_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, ਚੌਖਟਾ_dpi)) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("AdjustWindowRectExForDpi()");
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!Adjust_ਖਿੜਕੀ_Rect_Ex(lpRect, style, menu, styleEx)) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("AdjustWindowRectEx()");
        }
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, UINT flags, SDL_ਖਿੜਕੀ_Rect rect_type)
{
    SDL_ਖਿੜਕੀ *ਬੱਚਾ_ਖਿੜਕੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    HWND ਸਿਖਰ;
    ਪੂਰਨ x, y;
    ਪੂਰਨ w, h;
    bool ਨਤੀਜਾ = true;

    // Figure out what the window area will be
    ਜੇ (SDL_ShouldAllowTopmost() && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ)) {
        ਸਿਖਰ = HWND_TOPMOST;
    } ਨਹੀਂਤਾਂ {
        ਸਿਖਰ = HWND_NOTOPMOST;
    }

    WIN_Adjust_ਖਿੜਕੀ_Rect(ਖਿੜਕੀ, &x, &y, &w, &h, rect_type);

    ਅੰਕੜੇ->expected_resize = !(flags & SWP_NOSIZE);
    ਜੇ (ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, ਸਿਖਰ, x, y, w, h, flags) == 0) {
        ਨਤੀਜਾ = WIN_ਸੈੱਟ_Error("SetWindowPos()");
    }
    ਅੰਕੜੇ->expected_resize = false;

    // Update any child windows
    ਲਈ (ਬੱਚਾ_ਖਿੜਕੀ = ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; ਬੱਚਾ_ਖਿੜਕੀ; ਬੱਚਾ_ਖਿੜਕੀ = ਬੱਚਾ_ਖਿੜਕੀ->ਅਗਲਾ_sibling) {
        ਜੇ (!ਬੱਚਾ_ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
            // This child window is not yet fully initialized.
            ਜਾਰੀ;
        }
        ਜੇ (!WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਬੱਚਾ_ਖਿੜਕੀ, flags, SDL_WINDOWRECT_CURRENT)) {
            ਨਤੀਜਾ = false;
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ SDL_ਖਿੜਕੀ_Erase_Background_ਬਹੁਲਕ Get_Erase_Background_ਬਹੁਲਕ_Hint(ਖਾਲੀ)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_ਬਹੁਲਕ);
    ਜੇ (!hint)
        ਵਾਪਸ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ਜੇ (SDL_strstr(hint, "never"))
        ਵਾਪਸ SDL_ERASEBACKGROUNDMODE_NEVER;

    ਜੇ (SDL_strstr(hint, "initial"))
        ਵਾਪਸ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ਜੇ (SDL_strstr(hint, "always"))
        ਵਾਪਸ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    ਪੂਰਨ ਬਹੁਲਕ = SDL_GetStringInteger(hint, 1);
    ਜੇ (ਬਹੁਲਕ < 0 || ਬਹੁਲਕ > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ਵਾਪਸ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ਵਾਪਸ (SDL_ਖਿੜਕੀ_Erase_Background_ਬਹੁਲਕ)ਬਹੁਲਕ;
}

ਸਥਿਰ bool ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, HWND hwnd, HWND ਮਾਪਾ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Allocate the window data
    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    ਅੰਕੜੇ->ਖਿੜਕੀ = ਖਿੜਕੀ;
    ਅੰਕੜੇ->hwnd = hwnd;
    ਅੰਕੜੇ->ਮਾਪਾ = ਮਾਪਾ;
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ਅੰਕੜੇ->hdc = (HDC)ਅੰਕੜੇ->hwnd;
#ਨਹੀਂਤਾਂ
    ਅੰਕੜੇ->hdc = GetDC(hwnd);
#ਜੇ_ਅੰਤ
    ਅੰਕੜੇ->hinstance = (HINSTANCE)Get_ਖਿੜਕੀ_Long_Ptr(hwnd, GWLP_HINSTANCE);
    ਅੰਕੜੇ->mouse_button_flags = (WPARAM)-1;
    ਅੰਕੜੇ->ਆਖਰੀ_ਸੂਚਕ_update = (LPARAM)-1;
    ਅੰਕੜੇ->videodata = videodata;
    ਅੰਕੜੇ->initializing = true;
    ਅੰਕੜੇ->hint_erase_background_ਬਹੁਲਕ = Get_Erase_Background_ਬਹੁਲਕ_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    ਅੰਕੜੇ->cursor_ctrlock_rect.ਖੱਬਾ   = 0 - remote_desktop_adjustment;
    ਅੰਕੜੇ->cursor_ctrlock_rect.ਸਿਖਰ    = 0;
    ਅੰਕੜੇ->cursor_ctrlock_rect.ਸੱਜਾ  = 1 + remote_desktop_adjustment;
    ਅੰਕੜੇ->cursor_ctrlock_rect.bottom = 1;
#ਜੇ_ਅੰਤ

    ਜੇ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        ਅੰਕੜੇ->copybits_flag = 0;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->copybits_flag = SWP_NOCOPYBITS;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", ਅੰਕੜੇ->scaling_dpi);
#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ਜੇ (!ਸੈੱਟ_Prop(hwnd, ਪਾਠ_2("SDL_WindowData"), ਅੰਕੜੇ)) {
        ReleaseDC(hwnd, ਅੰਕੜੇ->hdc);
        SDL_free(ਅੰਕੜੇ);
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetProp() failed");
    }
#ਜੇ_ਅੰਤ

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    // Set up the window proc function
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GWLP_WNDPROC
        ਅੰਕੜੇ->wndproc = (WNDPROC)Get_ਖਿੜਕੀ_Long_Ptr(hwnd, GWLP_WNDPROC);
        ਜੇ (ਅੰਕੜੇ->wndproc != WIN_ਖਿੜਕੀ_Proc) {
            ਸੈੱਟ_ਖਿੜਕੀ_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_ਖਿੜਕੀ_Proc);
        }
#ਨਹੀਂਤਾਂ
        ਅੰਕੜੇ->wndproc = (WNDPROC)Get_ਖਿੜਕੀ_Long(hwnd, GWL_WNDPROC);
        ਜੇ (ਅੰਕੜੇ->wndproc != WIN_ਖਿੜਕੀ_Proc) {
            ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_ਖਿੜਕੀ_Proc);
        }
#ਜੇ_ਅੰਤ
    } ਨਹੀਂਤਾਂ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
        ਜੇ (style & WS_VISIBLE) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_HIDDEN;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_HIDDEN;
        }
        ਜੇ (style & WS_POPUP) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_BORDERLESS;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_BORDERLESS;
        }
        ਜੇ (style & WS_THICKFRAME) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_RESIZABLE;
        } ਨਹੀਂਤਾਂ ਜੇ (!(style & WS_POPUP)) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_RESIZABLE;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WS_MAXIMIZE
        ਜੇ (style & WS_MAXIMIZE) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MAXIMIZED;
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MAXIMIZED;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WS_MINIMIZE
        ਜੇ (style & WS_MINIMIZE) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MINIMIZED;
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MINIMIZED;
        }
    }
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        RECT rect;
        ਜੇ (GetClientRect(hwnd, &rect) && WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
            ਪੂਰਨ w = rect.ਸੱਜਾ;
            ਪੂਰਨ h = rect.bottom;

            ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
                ਖਿੜਕੀ->floating.w = ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->w = w;
                ਖਿੜਕੀ->floating.h = ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->h = h;
            } ਨਹੀਂਤਾਂ ਜੇ ((ਖਿੜਕੀ->windowed.w && ਖਿੜਕੀ->windowed.w != w) || (ਖਿੜਕੀ->windowed.h && ਖਿੜਕੀ->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                ਪੂਰਨ x, y;
                // Figure out what the window area will be
                WIN_Adjust_ਖਿੜਕੀ_Rect(ਖਿੜਕੀ, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                ਅੰਕੜੇ->expected_resize = true;
                ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, ਨਿਰਾ, x, y, w, h, ਅੰਕੜੇ->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                ਅੰਕੜੇ->expected_resize = false;
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ->w = w;
                ਖਿੜਕੀ->h = h;
            }
        }
    }
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        ਬਿੰਦੂ_2 ਬਿੰਦੂ;
        ਬਿੰਦੂ.x = 0;
        ਬਿੰਦੂ.y = 0;
        ਜੇ (Client_ਮੰਜ਼ਿਲ_Screen(hwnd, &ਬਿੰਦੂ)) {
            ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
                ਖਿੜਕੀ->floating.x = ਖਿੜਕੀ->windowed.x = ਬਿੰਦੂ.x;
                ਖਿੜਕੀ->floating.y = ਖਿੜਕੀ->windowed.y = ਬਿੰਦੂ.y;
            }
            ਖਿੜਕੀ->x = ਬਿੰਦੂ.x;
            ਖਿੜਕੀ->y = ਬਿੰਦੂ.y;
        }
    }

    WIN_Update_ਖਿੜਕੀ_ICCProfile(ਖਿੜਕੀ, false);
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS;
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
#ਨਹੀਂਤਾਂ
    ਜੇ (GetFocus() == hwnd) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS;
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
        WIN_UpdateClipCursor(ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ) {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(_this, ਖਿੜਕੀ, true);
    } ਨਹੀਂਤਾਂ {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(_this, ਖਿੜਕੀ, false);
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ਜੇ (videodata->ਰਜਿਸਟਰ_Touch_ਖਿੜਕੀ) {
        videodata->ਰਜਿਸਟਰ_Touch_ਖਿੜਕੀ(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ->ਮਾਪਾ && !ਖਿੜਕੀ->ਮਾਪਾ) {
        ਅੰਕੜੇ->destroy_ਮਾਪਾ_with_ਖਿੜਕੀ = true;
    }

    ਅੰਕੜੇ->initializing = false;

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        ਪੂਰਨ titleLen;
        bool isstack;

        titleLen = Get_ਖਿੜਕੀ_ਪਾਠ_ਲੰਮਾਈ(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ਜੇ (title) {
            titleLen = Get_ਖਿੜਕੀ_ਪਾਠ(hwnd, title, titleLen + 1);
        } ਨਹੀਂਤਾਂ {
            titleLen = 0;
        }
        ਜੇ (titleLen > 0) {
            ਖਿੜਕੀ->title = WIN_String_ਮੰਜ਼ਿਲ_UTF8(title);
        }
        ਜੇ (title) {
            SDL_small_free(title, isstack);
        }
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WIN32_HWND_ਸੂਚਕ, ਅੰਕੜੇ->hwnd);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WIN32_HDC_ਸੂਚਕ, ਅੰਕੜੇ->hdc);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WIN32_INSTANCE_ਸੂਚਕ, ਅੰਕੜੇ->hinstance);

    // All done!
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Cleanup_ਖਿੜਕੀ_ਅੰਕੜੇ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ) {
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ਜੇ (ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ) {
            WIN_AcceptDragAndDrop(ਖਿੜਕੀ, false);
        }
        SDL_free(ਅੰਕੜੇ->ICMFileName);
        ਜੇ (ਅੰਕੜੇ->keyboard_hook) {
            UnhookWindowsHookEx(ਅੰਕੜੇ->keyboard_hook);
        }
        ਜੇ (ਅੰਕੜੇ->hicon) {
            DestroyIcon(ਅੰਕੜੇ->hicon);
        }
        ReleaseDC(ਅੰਕੜੇ->hwnd, ਅੰਕੜੇ->hdc);
        RemoveProp(ਅੰਕੜੇ->hwnd, ਪਾਠ_2("SDL_WindowData"));
#ਜੇ_ਅੰਤ
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
            Destroy_ਖਿੜਕੀ(ਅੰਕੜੇ->hwnd);
            ਜੇ (ਅੰਕੜੇ->destroy_ਮਾਪਾ_with_ਖਿੜਕੀ && ਅੰਕੜੇ->ਮਾਪਾ) {
                Destroy_ਖਿੜਕੀ(ਅੰਕੜੇ->ਮਾਪਾ);
            }
        } ਨਹੀਂਤਾਂ {
            // Restore any original event handler...
            ਜੇ (ਅੰਕੜੇ->wndproc) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GWLP_WNDPROC
                ਸੈੱਟ_ਖਿੜਕੀ_Long_Ptr(ਅੰਕੜੇ->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)ਅੰਕੜੇ->wndproc);
#ਨਹੀਂਤਾਂ
                ਸੈੱਟ_ਖਿੜਕੀ_Long(ਅੰਕੜੇ->hwnd, GWL_WNDPROC,
                              (LONG_PTR)ਅੰਕੜੇ->wndproc);
#ਜੇ_ਅੰਤ
            }
        }
        SDL_free(ਅੰਕੜੇ);
    }
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ WIN_ConstrainPopup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool output_ਮੰਜ਼ਿਲ_pending)
{
    // Possibly clamp popup windows to the output borders
    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        SDL_ਖਿੜਕੀ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ਪੂਰਨ abs_x = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->floating.x;
        ਪੂਰਨ abs_y = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->floating.y;
        ਅਚਲ ਪੂਰਨ ਚੌੜਾਈ = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->floating.w;
        ਅਚਲ ਪੂਰਨ ਉਚਾਈ = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->floating.h;
        ਪੂਰਨ ਵਿੱਥ_x = 0, ਵਿੱਥ_y = 0;

        ਜੇ (ਖਿੜਕੀ->constrain_popup) {
            // Calculate the total offset from the parents
            ਲਈ (w = ਖਿੜਕੀ->ਮਾਪਾ; SDL_ਖਿੜਕੀ_IS_POPUP(w); w = w->ਮਾਪਾ) {
                ਵਿੱਥ_x += w->x;
                ਵਿੱਥ_y += w->y;
            }

            ਵਿੱਥ_x += w->x;
            ਵਿੱਥ_y += w->y;
            abs_x += ਵਿੱਥ_x;
            abs_y += ਵਿੱਥ_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_ਖਿੜਕੀ(w);
            SDL_GetDisplayBounds(displayID, &rect);
            ਜੇ (abs_x + ਚੌੜਾਈ > rect.x + rect.w) {
                abs_x -= (abs_x + ਚੌੜਾਈ) - (rect.x + rect.w);
            }
            ਜੇ (abs_y + ਉਚਾਈ > rect.y + rect.h) {
                abs_y -= (abs_y + ਉਚਾਈ) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ਜੇ (output_ਮੰਜ਼ਿਲ_pending) {
            ਖਿੜਕੀ->pending.x = abs_x - ਵਿੱਥ_x;
            ਖਿੜਕੀ->pending.y = abs_y - ਵਿੱਥ_y;
            ਖਿੜਕੀ->pending.w = ਚੌੜਾਈ;
            ਖਿੜਕੀ->pending.h = ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->floating.x = abs_x - ਵਿੱਥ_x;
            ਖਿੜਕੀ->floating.y = abs_y - ਵਿੱਥ_y;
            ਖਿੜਕੀ->floating.w = ਚੌੜਾਈ;
            ਖਿੜਕੀ->floating.h = ਉਚਾਈ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ WIN_ਸੈੱਟ_Keyboard_Focus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool ਸੈੱਟ_ਸਰਗਰਮ_focus)
{
    SDL_ਖਿੜਕੀ *toplevel = ਖਿੜਕੀ;

    // Find the topmost parent
    ਜਦੋਂ (SDL_ਖਿੜਕੀ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ਮਾਪਾ;
    }

    toplevel->keyboard_focus = ਖਿੜਕੀ;

    ਜੇ (ਸੈੱਟ_ਸਰਗਰਮ_focus && !ਖਿੜਕੀ->is_hiding && !ਖਿੜਕੀ->is_destroying) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    }
}

bool WIN_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    HWND hwnd = (HWND)SDL_Get_ਸੂਚਕ_Property(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WIN32_HWND_ਸੂਚਕ, SDL_Get_ਸੂਚਕ_Property(create_props, "sdl2-compat.external_window", ਨਿਰਾ));
    HWND ਮਾਪਾ = ਨਿਰਾ;
    ਜੇ (hwnd) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_EXTERNAL;

        ਜੇ (!ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(_this, ਖਿੜਕੀ, hwnd, ਮਾਪਾ)) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        ਪੂਰਨ x, y;
        ਪੂਰਨ w, h;

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_UTILITY) {
            ਮਾਪਾ = Create_ਖਿੜਕੀ(SDL_Appname, ਪਾਠ_2(""), STYLE_BASIC, 0, 0, 32, 32, ਨਿਰਾ, ਨਿਰਾ, SDL_Instance, ਨਿਰਾ);
        } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ) {
            ਮਾਪਾ = ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->hwnd;
        }

        style |= Get_ਖਿੜਕੀ_Style(ਖਿੜਕੀ);
        styleEx |= (DWORD)SDL_Get_ਸੰਖਿਆ_Property(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WIN32_STYLE_EX_ਸੰਖਿਆ, Get_ਖਿੜਕੀ_Style_Ex(ਖਿੜਕੀ));

        // Figure out what the window area will be
        WIN_ConstrainPopup(ਖਿੜਕੀ, false);
        WIN_Adjust_ਖਿੜਕੀ_Rect_With_Style(ਖਿੜਕੀ, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_ਖਿੜਕੀ_Ex(styleEx, SDL_Appname, ਪਾਠ_2(""), style,
                              x, y, w, h, ਮਾਪਾ, ਨਿਰਾ, SDL_Instance, ਨਿਰਾ);
        ਜੇ (!hwnd) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("Couldn't create window");
        }

        WIN_Update_Dark_ਬਹੁਲਕ_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ਜੇ (!ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(_this, ਖਿੜਕੀ, hwnd, ਮਾਪਾ)) {
            Destroy_ਖਿੜਕੀ(hwnd);
            ਜੇ (ਮਾਪਾ) {
                Destroy_ਖਿੜਕੀ(ਮਾਪਾ);
            }
            ਵਾਪਸ false;
        }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_ਪਾਠ_ਨਿਵੇਸ਼(_this, ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, ਨਿਰਾ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_HIDDEN;
            Show_ਖਿੜਕੀ(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) {
        ਜੇ (videodata->Dwm_Enable_Blur_Behind_ਖਿੜਕੀ) {
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
            videodata->Dwm_Enable_Blur_Behind_ਖਿੜਕੀ(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_ਸੂਚਕ_Property(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WIN32_PIXEL_FORMAT_HWND_ਸੂਚਕ, ਨਿਰਾ);
    ਜੇ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        ਪੂਰਨ pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, ਆਕਾਰ(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ਜੇ (!ਸੈੱਟ_Pixel_Format(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hdc, pixel_format, &pfd)) {
            WIN_Destroy_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetPixelFormat()");
        }
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
            ਵਾਪਸ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_ES2
        ਜੇ ((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_ਅੰਕੜੇ || WIN_GL_UseEGL(_this))
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_WGL
        ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
            ਜੇ (!WIN_GLES_ਤਿਆਰੀ_ਖਿੜਕੀ(_this, ਖਿੜਕੀ)) {
                WIN_Destroy_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
                ਵਾਪਸ false;
            }
            ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create GLES window surface (EGL support not configured)");
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_ES2

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
        ਜੇ (!WIN_GL_ਤਿਆਰੀ_ਖਿੜਕੀ(_this, ਖਿੜਕੀ)) {
            WIN_Destroy_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
            ਵਾਪਸ false;
        }
#ਨਹੀਂਤਾਂ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create GL window (WGL support not configured)");
#ਜੇ_ਅੰਤ
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    LPTSTR title = WIN_UTF8_ਮੰਜ਼ਿਲ_String(ਖਿੜਕੀ->title);
    ਸੈੱਟ_ਖਿੜਕੀ_ਪਾਠ(hwnd, title);
    SDL_free(title);
#ਜੇ_ਅੰਤ
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    HICON hicon = ਨਿਰਾ;
    BYTE *icon_bmp;
    ਪੂਰਨ icon_len, ਨਕਾਬ_len, ਪੰਕਤੀ_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool ਨਤੀਜਾ = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_ਸਮਾਂ_ASSERT(WIN_ਸੈੱਟ_ਖਿੜਕੀ_Icon_ਵਰਤਦਾ_BITMAPINFOHEADER_ਮੰਜ਼ਿਲ_prepare_an_ICONIMAGE, ਆਕਾਰ(BITMAPINFOHEADER) == 40);
    ਨਕਾਬ_len = (icon->h * (icon->w + 7) / 8);
    icon_len = ਆਕਾਰ(BITMAPINFOHEADER) + icon->h * icon->w * ਆਕਾਰ(Uint32) + ਨਕਾਬ_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ਜੇ (!icon_bmp) {
        ਵਾਪਸ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_ਮਾਪ = SDL_Swap32LE(ਆਕਾਰ(BITMAPINFOHEADER));
    bmi->bi_ਚੌੜਾਈ = SDL_Swap32LE(icon->w);
    bmi->bi_ਉਚਾਈ = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_ਮਾਪ_Image = SDL_Swap32LE(icon->h * icon->w * ਆਕਾਰ(Uint32));
    bmi->bi_XPels_ਪ੍ਰਤੀ_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_ਪ੍ਰਤੀ_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_ਵਰਤਿਆ = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[ਆਕਾਰ(BITMAPINFOHEADER)];
    ਪੰਕਤੀ_len = icon->w * ਆਕਾਰ(Uint32);
    y = icon->h;
    ਜਦੋਂ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, ਪੰਕਤੀ_len);
        dst += ਪੰਕਤੀ_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - ਨਕਾਬ_len, 0xFF, ਨਕਾਬ_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ਜੇ (!hicon) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SetWindowIcon() failed, error %08X", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)Get_ਆਖਰੀ_Error());
    }

    ਜੇ (ਅੰਕੜੇ->hicon) {
        DestroyIcon(ਅੰਕੜੇ->hicon);
    }
    ਅੰਕੜੇ->hicon = hicon;

    // Set the icon for the window
    Send_ਸੁਨੇਹਾ(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_ਸੁਨੇਹਾ(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ਵਾਪਸ ਨਤੀਜਾ;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_Unsupported();
#ਜੇ_ਅੰਤ
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਜੇ (!(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED))) {
            WIN_ConstrainPopup(ਖਿੜਕੀ, true);
            ਵਾਪਸ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ,
                                                 ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (!(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED))) {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ਨਹੀਂਤਾਂ {
        // Can't resize the window
        ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = false;
    }
}

bool WIN_Get_ਖਿੜਕੀ_Borders_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ)
{
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *ਸਿਖਰ = rcClient.ਸਿਖਰ;
    *ਖੱਬਾ = rcClient.ਖੱਬਾ;
    *bottom = rcClient.bottom;
    *ਸੱਜਾ = rcClient.ਸੱਜਾ;

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    RECT rcClient, rc_ਖਿੜਕੀ;
    ਬਿੰਦੂ_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ਜੇ (!GetClientRect(hwnd, &rcClient)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("GetClientRect() failed, error %08X", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)Get_ਆਖਰੀ_Error());
    }

    ਜੇ (!Get_ਖਿੜਕੀ_Rect(hwnd, &rc_ਖਿੜਕੀ)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("GetWindowRect() failed, error %08X", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)Get_ਆਖਰੀ_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_ਖਿੜਕੀ.ਸਿਖਰ;
    ptDiff.x = rc_ਖਿੜਕੀ.ਖੱਬਾ;

    ਜੇ (!Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &ptDiff)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("ScreenToClient() failed, error %08X", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)Get_ਆਖਰੀ_Error());
    }

    rc_ਖਿੜਕੀ.ਸਿਖਰ = ptDiff.y;
    rc_ਖਿੜਕੀ.ਖੱਬਾ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_ਖਿੜਕੀ.bottom;
    ptDiff.x = rc_ਖਿੜਕੀ.ਸੱਜਾ;

    ਜੇ (!Screen_ਮੰਜ਼ਿਲ_Client(hwnd, &ptDiff)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("ScreenToClient() failed, error %08X", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)Get_ਆਖਰੀ_Error());
    }

    rc_ਖਿੜਕੀ.bottom = ptDiff.y;
    rc_ਖਿੜਕੀ.ਸੱਜਾ = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *ਸਿਖਰ = rcClient.ਸਿਖਰ - rc_ਖਿੜਕੀ.ਸਿਖਰ;
    *ਖੱਬਾ = rcClient.ਖੱਬਾ - rc_ਖਿੜਕੀ.ਖੱਬਾ;
    *bottom = rc_ਖਿੜਕੀ.bottom - rcClient.bottom;
    *ਸੱਜਾ = rc_ਖਿੜਕੀ.ਸੱਜਾ - rcClient.ਸੱਜਾ;

    ਵਾਪਸ true;
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ਖਾਲੀ WIN_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    RECT rect;

    ਜੇ (GetClientRect(hwnd, &rect) && WIN_ਖਿੜਕੀ_Rect_Valid(&rect)) {
        *w = rect.ਸੱਜਾ;
        *h = rect.bottom;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->ਆਖਰੀ_pixel_w && ਖਿੜਕੀ->ਆਖਰੀ_pixel_h) {
        *w = ਖਿੜਕੀ->ਆਖਰੀ_pixel_w;
        *h = ਖਿੜਕੀ->ਆਖਰੀ_pixel_h;
    } ਨਹੀਂਤਾਂ {
        // Probably created minimized, use the restored size
        *w = ਖਿੜਕੀ->floating.w;
        *h = ਖਿੜਕੀ->floating.h;
    }
}

ਖਾਲੀ WIN_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ACTIVATE_WHEN_SHOWN, true);

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        // Update our position in case our parent moved while we were hidden
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position(_this, ਖਿੜਕੀ);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ਜੇ (ਖਿੜਕੀ->pending_flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS)) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_BORDERLESS;
            style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_ਨਕਾਬ;
            style |= Get_ਖਿੜਕੀ_Style(ਖਿੜਕੀ);
            ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE, style);
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_BORDERLESS;
        }
    }
    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);
    ਜੇ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    ਅੰਕੜੇ->showing_ਖਿੜਕੀ = true;
    ਜੇ (bActivate) {
        Show_ਖਿੜਕੀ(hwnd, SW_SHOW);
    } ਨਹੀਂਤਾਂ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, ਨਿਰਾ, 0, 0, 0, 0, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    ਅੰਕੜੇ->showing_ਖਿੜਕੀ = false;

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE) && bActivate) {
        WIN_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
    }
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Modal(_this, ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ WIN_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Modal(_this, ਖਿੜਕੀ, false);
    }

    Show_ਖਿੜਕੀ(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
        SDL_ਖਿੜਕੀ *new_focus;
        ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(ਖਿੜਕੀ, &new_focus);
        WIN_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
    }
}

ਖਾਲੀ WIN_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* If desired, raise the window more forcefully.
     * Technique taken from http://stackoverflow.com/questions/916259/ .
     * Specifically, http://stackoverflow.com/a/34414846 .
     *
     * The issue is that Microsoft has gone through a lot of trouble to make it
     * nearly impossible to programmatically move a window to the foreground,
     * for "security" reasons. Apparently, the following song-and-dance gets
     * around their objections. */
    bool bForce = SDL_GetHintBoolean(SDL_HINT_FORCE_RAISEWINDOW, false);
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = ਨਿਰਾ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    ਜੇ (bForce) {
        hCurWnd = Get_Foreground_ਖਿੜਕੀ();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_ਖਿੜਕੀ_Thread_Process_Id(hCurWnd, ਨਿਰਾ);
        Show_ਖਿੜਕੀ(hwnd, SW_RESTORE);
        Attach_Thread_ਨਿਵੇਸ਼(dwCurID, dwMyID, TRUE);
        ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ਜੇ (!SDL_ShouldAllowTopmost() || !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ)) {
            ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ਜੇ (bActivate) {
        ਸੈੱਟ_Foreground_ਖਿੜਕੀ(hwnd);
        ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
            WIN_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, ਖਿੜਕੀ->ਮਾਪਾ == SDL_GetKeyboardFocus());
        }
    } ਨਹੀਂਤਾਂ {
        ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, HWND_ਸਿਖਰ, 0, 0, 0, 0, ਅੰਕੜੇ->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ਜੇ (bForce) {
        Attach_Thread_ਨਿਵੇਸ਼(dwCurID, dwMyID, FALSE);
        ਸੈੱਟ_Focus(hwnd);
        ਸੈੱਟ_ਸਰਗਰਮ_ਖਿੜਕੀ(hwnd);
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ਖਾਲੀ WIN_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        HWND hwnd = ਅੰਕੜੇ->hwnd;
        ਅੰਕੜੇ->expected_resize = true;
        Show_ਖਿੜਕੀ(hwnd, SW_MAXIMIZE);
        ਅੰਕੜੇ->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ਜੇ (ਖਿੜਕੀ->max_w || ਖਿੜਕੀ->max_h) {
            ਪੂਰਨ fx, fy, fw, fh;

            ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->max_w ? SDL_min(ਖਿੜਕੀ->w, ਖਿੜਕੀ->max_w) : ਖਿੜਕੀ->windowed.w;
            ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->max_h ? SDL_min(ਖਿੜਕੀ->h, ਖਿੜਕੀ->max_h) : ਖਿੜਕੀ->windowed.h;
            WIN_Adjust_ਖਿੜਕੀ_Rect(ਖਿੜਕੀ, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            ਅੰਕੜੇ->expected_resize = true;
            ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, HWND_ਸਿਖਰ, fx, fy, fw, fh, ਅੰਕੜੇ->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            ਅੰਕੜੇ->expected_resize = false;
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->windowed_ਬਹੁਲਕ_was_maximized = true;
    }
}

ਖਾਲੀ WIN_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    HWND hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    Show_ਖਿੜਕੀ(hwnd, SW_MINIMIZE);
}

ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    DWORD style;

    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ਨਕਾਬ;
    style |= Get_ਖਿੜਕੀ_Style(ਖਿੜਕੀ);

    ਅੰਕੜੇ->ਵਿੱਚ_border_change = true;
    ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE, style);
    WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ, ਅੰਕੜੇ->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    ਅੰਕੜੇ->ਵਿੱਚ_border_change = false;
}

ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    DWORD style;

    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ਨਕਾਬ;
    style |= Get_ਖਿੜਕੀ_Style(ਖਿੜਕੀ);

    ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE, style);
}

ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ)
{
    WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

ਖਾਲੀ WIN_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਜੇ (!ਅੰਕੜੇ->showing_ਖਿੜਕੀ || ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED)) {
            HWND hwnd = ਅੰਕੜੇ->hwnd;
            ਅੰਕੜੇ->expected_resize = true;
            Show_ਖਿੜਕੀ(hwnd, SW_RESTORE);
            ਅੰਕੜੇ->expected_resize = false;
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->windowed_ਬਹੁਲਕ_was_maximized = false;
    }
}

ਸਥਿਰ ਖਾਲੀ WIN_Update_ਕੋਨਾ_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_ਖਿੜਕੀ_ਕੋਨਾ_PREFERENCE ਕੋਨਾ_Pref)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute(hwnd, DWMWA_ਖਿੜਕੀ_ਕੋਨਾ_PREFERENCE, &ਕੋਨਾ_Pref, ਆਕਾਰ(ਕੋਨਾ_Pref));
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_ਸੈੱਟ_ਖਿੜਕੀ_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, ਆਕਾਰ(colorRef));
    }
#ਜੇ_ਅੰਤ
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_ਨਤੀਜਾ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ ? ਅੰਕੜੇ->hwnd : ਨਿਰਾ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND ਸਿਖਰ;
    ਪੂਰਨ x, y;
    ਪੂਰਨ w, h;
    bool enterMaximized = false;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (ਪੂਰਨ)fullscreen);
#ਜੇ_ਅੰਤ

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && !fullscreen) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    ਜੇ (SDL_ShouldAllowTopmost() && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ)) {
        ਸਿਖਰ = HWND_TOPMOST;
    } ਨਹੀਂਤਾਂ {
        ਸਿਖਰ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_ਮਾਪ = ਆਕਾਰ(MONITORINFO);
    ਜੇ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_ਸੈੱਟ_Error("GetMonitorInfo failed");
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, fullscreen ? SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN : SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
    style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ਨਕਾਬ;
    style |= Get_ਖਿੜਕੀ_Style(ਖਿੜਕੀ);
    styleEx = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);

    ਜੇ (fullscreen) {
        x = minfo.rcMonitor.ਖੱਬਾ;
        y = minfo.rcMonitor.ਸਿਖਰ;
        w = minfo.rcMonitor.ਸੱਜਾ - minfo.rcMonitor.ਖੱਬਾ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.ਸਿਖਰ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ਜੇ (style & WS_MAXIMIZE) {
            ਅੰਕੜੇ->windowed_ਬਹੁਲਕ_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_ਕੋਨਾ_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ਨਹੀਂਤਾਂ {
        BOOL menu;

        WIN_Update_ਕੋਨਾ_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ਜੇ (ਅੰਕੜੇ->windowed_ਬਹੁਲਕ_was_maximized && !ਅੰਕੜੇ->ਵਿੱਚ_ਖਿੜਕੀ_deactivation) {
            enterMaximized = true;
            ਅੰਕੜੇ->disable_move_ਮਾਪ_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ਨਿਰਾ);
        WIN_Adjust_ਖਿੜਕੀ_Rect_With_Style(ਖਿੜਕੀ, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        ਅੰਕੜੇ->windowed_ਬਹੁਲਕ_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        ਜੇ (enterMaximized) {
            ਅਚਲ SDL_ਬਿੰਦੂ windowed_ਬਿੰਦੂ = { ਖਿੜਕੀ->windowed.x, ਖਿੜਕੀ->windowed.y };
            ਅਚਲ SDL_ਬਿੰਦੂ floating_ਬਿੰਦੂ = { ਖਿੜਕੀ->floating.x, ਖਿੜਕੀ->floating.y };
            ਅਚਲ SDL_DisplayID floating_display = SDL_Get_Display_For_ਬਿੰਦੂ(&floating_ਬਿੰਦੂ);
            ਅਚਲ SDL_DisplayID windowed_display = SDL_Get_Display_For_ਬਿੰਦੂ(&windowed_ਬਿੰਦੂ);

            ਜੇ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ਜੇ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ਨਹੀਂਤਾਂ {
                    x = bounds.x;
                }
                ਜੇ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ਨਹੀਂਤਾਂ {
                    y = bounds.y;
                }
            }
        }
    }

    /* Always reset the window to the base floating size before possibly re-applying the maximized state,
     * otherwise, the base floating size can seemingly be lost in some cases.
     */
    ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_STYLE, style);
    ਅੰਕੜੇ->expected_resize = true;
    ਸੈੱਟ_ਖਿੜਕੀ_Pos(hwnd, ਸਿਖਰ, x, y, w, h, ਅੰਕੜੇ->copybits_flag | SWP_NOACTIVATE);
    ਅੰਕੜੇ->expected_resize = false;
    ਅੰਕੜੇ->disable_move_ਮਾਪ_events = false;

    ਜੇ (enterMaximized) {
        WIN_Maximize_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (!fullscreen && ਅੰਕੜੇ && ਅੰਕੜੇ->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_ਸੁਨੇਹਾ(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_ਸੁਨੇਹਾ(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)ਅੰਕੜੇ->hicon);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (ਪੂਰਨ)fullscreen, x, y, w, h);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਖਾਲੀ WIN_Update_ਖਿੜਕੀ_ICCProfile(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool send_event)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);

    ਜੇ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
        ਜੇ (hdc) {
            WCHAR fileName[MAX_ਰਸਤਾ];
            DWORD file_Name_ਮਾਪ = SDL_arraysize(fileName);
            ਜੇ (GetICMProfileW(hdc, &file_Name_ਮਾਪ, fileName)) {
                // fileNameSize includes '\0' on return
                ਜੇ (!ਅੰਕੜੇ->ICMFileName ||
                    SDL_wcscmp(ਅੰਕੜੇ->ICMFileName, fileName) != 0) {
                    SDL_free(ਅੰਕੜੇ->ICMFileName);
                    ਅੰਕੜੇ->ICMFileName = SDL_wcsdup(fileName);
                    ਜੇ (send_event) {
                        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ICCPROF_ਬਦਲਿਆ, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

ਖਾਲੀ *WIN_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅੱਖਰ *filename_utf8;
    ਖਾਲੀ *icc_Profile_ਅੰਕੜੇ = ਨਿਰਾ;

    filename_utf8 = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W(ਅੰਕੜੇ->ICMFileName);
    ਜੇ (filename_utf8) {
        icc_Profile_ਅੰਕੜੇ = SDL_ਲੱਦੋ_File(filename_utf8, ਮਾਪ);
        ਜੇ (!icc_Profile_ਅੰਕੜੇ) {
            SDL_ਸੈੱਟ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ਵਾਪਸ icc_Profile_ਅੰਕੜੇ;
}

ਸਥਿਰ ਖਾਲੀ WIN_GrabKeyboard(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HMODULE module;

    ਜੇ (ਅੰਕੜੇ->keyboard_hook) {
        ਵਾਪਸ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ਜੇ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ਪਤਾ,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ਵਾਪਸ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ਜੇ (!GetKeyboardState(ਅੰਕੜੇ->videodata->pre_hook_ਕੁੰਜੀ_state)) {
        ਵਾਪਸ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    ਅੰਕੜੇ->keyboard_hook = ਸੈੱਟ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

ਖਾਲੀ WIN_UngrabKeyboard(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->keyboard_hook) {
        UnhookWindowsHookEx(ਅੰਕੜੇ->keyboard_hook);
        ਅੰਕੜੇ->keyboard_hook = ਨਿਰਾ;
    }
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    WIN_UpdateClipCursor(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    WIN_UpdateClipCursor(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    ਜੇ (grabbed) {
        WIN_GrabKeyboard(ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        WIN_UngrabKeyboard(ਖਿੜਕੀ);
    }

    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ਖਾਲੀ WIN_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    Cleanup_ਖਿੜਕੀ_ਅੰਕੜੇ(_this, ਖਿੜਕੀ);
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ਖਾਲੀ WIN_On_ਖਿੜਕੀ_Enter(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!ਅੰਕੜੇ || !ਅੰਕੜੇ->hwnd) {
        // The window wasn't fully initialized
        ਵਾਪਸ;
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ) {
        WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ, ਅੰਕੜੇ->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ਸਥਿਰ BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ਵਾਪਸ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_ਮੰਜ਼ਿਲ_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

ਖਾਲੀ WIN_Unclip_Cursor_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ) {
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    RECT rect;
    ਜੇ (GetClipCursor(&rect) && SDL_memcmp(&rect, &ਅੰਕੜੇ->cursor_clipped_rect, ਆਕਾਰ(rect)) == 0) {
        ClipCursor(ਨਿਰਾ);
        SDL_zero(ਅੰਕੜੇ->cursor_clipped_rect);
    }
}

ਖਾਲੀ WIN_UpdateClipCursor(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Video_ਅੰਕੜੇ *videodata = ਅੰਕੜੇ->videodata;
    ਜੇ (ਅੰਕੜੇ->ਵਿੱਚ_title_click || ਅੰਕੜੇ->focus_click_pending || ਅੰਕੜੇ->postpone_clipcursor) {
        ਵਾਪਸ;
    }

    SDL_Rect mouse_rect = ਖਿੜਕੀ->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS);
    bool win_is_grabbed = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED);
    bool win_ਵਿੱਚ_relmode = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ);
    bool cursor_confine = win_ਵਿੱਚ_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ਜੇ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ਜੇ (!GetClipCursor(&current)) {
            ਵਾਪਸ;
        }
        ਜੇ (videodevice && (
            current.ਖੱਬਾ != videodevice->desktop_bounds.x ||
            current.ਸਿਖਰ  != videodevice->desktop_bounds.y
        )) {
            ਬਿੰਦੂ_2 ਪਹਿਲਾ, ਦੂਜਾ;
            ਪਹਿਲਾ.x  = current.ਖੱਬਾ;
            ਪਹਿਲਾ.y  = current.ਸਿਖਰ;
            ਦੂਜਾ.x = current.ਸੱਜਾ  - 1;
            ਦੂਜਾ.y = current.bottom - 1;
            ਜੇ (!Pt_ਵਿੱਚ_Rect(&ਅੰਕੜੇ->cursor_clipped_rect, ਪਹਿਲਾ) ||
                !Pt_ਵਿੱਚ_Rect(&ਅੰਕੜੇ->cursor_clipped_rect, ਦੂਜਾ)) {
                ਵਾਪਸ;
            }
        }
        ClipCursor(ਨਿਰਾ);
        SDL_zero(ਅੰਕੜੇ->cursor_clipped_rect);
        ਵਾਪਸ;
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
    bool ਤਾਲਾ_ਮੰਜ਼ਿਲ_ctr = (mouse->relative_ਬਹੁਲਕ && mouse->relative_ਬਹੁਲਕ_center);

    RECT client;
    ਜੇ (!GetClientScreenRect(ਅੰਕੜੇ->hwnd, &client)) {
        ਵਾਪਸ;
    }

    RECT ਨਿਸ਼ਾਨਾ = client;
    ਜੇ (ਤਾਲਾ_ਮੰਜ਼ਿਲ_ctr) {
        LONG cx = (client.ਖੱਬਾ + client.ਸੱਜਾ ) / 2;
        LONG cy = (client.ਸਿਖਰ  + client.bottom) / 2;
        ਨਿਸ਼ਾਨਾ = ਅੰਕੜੇ->cursor_ctrlock_rect;
        ਨਿਸ਼ਾਨਾ.ਖੱਬਾ   += cx;
        ਨਿਸ਼ਾਨਾ.ਸੱਜਾ  += cx;
        ਨਿਸ਼ਾਨਾ.ਸਿਖਰ    += cy;
        ਨਿਸ਼ਾਨਾ.bottom += cy;
    } ਨਹੀਂਤਾਂ ਜੇ (win_mouse_rect) {
        RECT custom, overlap;
        custom.ਖੱਬਾ   = client.ਖੱਬਾ + mouse_rect.x;
        custom.ਸਿਖਰ    = client.ਸਿਖਰ  + mouse_rect.y;
        custom.ਸੱਜਾ  = client.ਖੱਬਾ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.ਸਿਖਰ  + mouse_rect.y + mouse_rect.h;
        ਜੇ (IntersectRect(&overlap, &client, &custom)) {
            ਨਿਸ਼ਾਨਾ = overlap;
        } ਨਹੀਂਤਾਂ ਜੇ (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
            ਵਾਪਸ;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ਜੇ (videodata->ਸੈੱਟ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_ਖਿੜਕੀ(ਅੰਕੜੇ->hwnd, MONITOR_DEFAULTTONEAREST);
            ਜੇ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ਜੇ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ਅਚਲ ਦਸ਼ਮਲਵ scale = (ਦਸ਼ਮਲਵ)hdpi_uint / (ਦਸ਼ਮਲਵ)USER_DEFAULT_SCREEN_DPI;
                    ਜੇ (scale != SDL_floorf(scale)) {
                        ਜੇ (ਨਿਸ਼ਾਨਾ.ਖੱਬਾ < ਨਿਸ਼ਾਨਾ.ਸੱਜਾ) {
                            ਨਿਸ਼ਾਨਾ.ਖੱਬਾ += 1;
                        }
                        ਜੇ (ਨਿਸ਼ਾਨਾ.ਸੱਜਾ > ਨਿਸ਼ਾਨਾ.ਖੱਬਾ) {
                            ਨਿਸ਼ਾਨਾ.ਸੱਜਾ -= 1;
                        }
                        ਜੇ (ਨਿਸ਼ਾਨਾ.ਸਿਖਰ < ਨਿਸ਼ਾਨਾ.bottom) {
                            ਨਿਸ਼ਾਨਾ.ਸਿਖਰ += 1;
                        }
                        ਜੇ (ਨਿਸ਼ਾਨਾ.bottom > ਨਿਸ਼ਾਨਾ.ਸਿਖਰ) {
                            ਨਿਸ਼ਾਨਾ.bottom -= 1;
                        }
                    }
                }
            }
            videodata->ਸੈੱਟ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ਜੇ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&ਨਿਸ਼ਾਨਾ, &client, ਆਕਾਰ(client)) &&
        ClipCursor(&ਨਿਸ਼ਾਨਾ)) {
        ਅੰਕੜੇ->cursor_clipped_rect = ਨਿਸ਼ਾਨਾ; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled)
{
    ਵਾਪਸ true; // just succeed, the real work is done elsewhere.
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity)
{
#ਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ਵਾਪਸ false;
#ਨਹੀਂਤਾਂ
    ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    ਅਚਲ LONG style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);

    ਜੇ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ਜੇ (style & WS_EX_LAYERED) {
            ਜੇ (ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetWindowLong()");
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ BYTE alpha = (BYTE)((ਪੂਰਨ)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ਜੇ (!(style & WS_EX_LAYERED)) {
            ਜੇ (ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetWindowLong()");
            }
        }

        ਜੇ (ਸੈੱਟ_Layered_ਖਿੜਕੀ_ਗੁਣ(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetLayeredWindowAttributes()");
        }
    }

    ਵਾਪਸ true;
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *SDLGetClipboardFormatName(UINT cf, ਅੱਖਰ *ਪਾਠ, ਪੂਰਨ len)
{
    ਚੋਣ (cf) {
    ਹਾਲਤ CF_ਪਾਠ:
        ਵਾਪਸ "CF_TEXT";
    ਹਾਲਤ CF_BITMAP:
        ਵਾਪਸ "CF_BITMAP";
    ਹਾਲਤ CF_METAFILEPICT:
        ਵਾਪਸ "CF_METAFILEPICT";
    ਹਾਲਤ CF_SYLK:
        ਵਾਪਸ "CF_SYLK";
    ਹਾਲਤ CF_DIF:
        ਵਾਪਸ "CF_DIF";
    ਹਾਲਤ CF_TIFF:
        ਵਾਪਸ "CF_TIFF";
    ਹਾਲਤ CF_OEMTEXT:
        ਵਾਪਸ "CF_OEMTEXT";
    ਹਾਲਤ CF_DIB:
        ਵਾਪਸ "CF_DIB";
    ਹਾਲਤ CF_PALETTE:
        ਵਾਪਸ "CF_PALETTE";
    ਹਾਲਤ CF_PENDATA:
        ਵਾਪਸ "CF_PENDATA";
    ਹਾਲਤ CF_RIFF:
        ਵਾਪਸ "CF_RIFF";
    ਹਾਲਤ CF_WAVE:
        ਵਾਪਸ "CF_WAVE";
    ਹਾਲਤ CF_UNICODETEXT:
        ਵਾਪਸ "CF_UNICODETEXT";
    ਹਾਲਤ CF_ENHMETAFILE:
        ਵਾਪਸ "CF_ENHMETAFILE";
    ਹਾਲਤ CF_HDROP:
        ਵਾਪਸ "CF_HDROP";
    ਹਾਲਤ CF_LOCALE:
        ਵਾਪਸ "CF_LOCALE";
    ਹਾਲਤ CF_DIBV5:
        ਵਾਪਸ "CF_DIBV5";
    ਹਾਲਤ CF_OWNERDISPLAY:
        ਵਾਪਸ "CF_OWNERDISPLAY";
    ਹਾਲਤ CF_DSPTEXT:
        ਵਾਪਸ "CF_DSPTEXT";
    ਹਾਲਤ CF_DSPBITMAP:
        ਵਾਪਸ "CF_DSPBITMAP";
    ਹਾਲਤ CF_DSPMETAFILEPICT:
        ਵਾਪਸ "CF_DSPMETAFILEPICT";
    ਹਾਲਤ CF_DSPENHMETAFILE:
        ਵਾਪਸ "CF_DSPENHMETAFILE";
    ਮੂਲ:
        ਜੇ (GetClipboardFormatNameA(cf, ਪਾਠ, len)) {
            ਵਾਪਸ ਪਾਠ;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }
}

ਸਥਿਰ STDMETHODIMP_(ULONG) SDLDrop_ਨਿਸ਼ਾਨਾ_ਜੋੜੋ_Ref(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ)
{
    ਵਾਪਸ ++ਨਿਸ਼ਾਨਾ->refcount;
}

ਸਥਿਰ STDMETHODIMP_(ULONG) SDLDrop_ਨਿਸ਼ਾਨਾ_Release(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ)
{
    --ਨਿਸ਼ਾਨਾ->refcount;
    ਜੇ (ਨਿਸ਼ਾਨਾ->refcount == 0) {
        SDL_free(ਨਿਸ਼ਾਨਾ);
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ ਨਿਸ਼ਾਨਾ->refcount;
}

ਸਥਿਰ STDMETHODIMP SDLDrop_ਨਿਸ਼ਾਨਾ_Query_Interface(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ, REFIID riid, PVOID *ppv)
{
    ਜੇ (ppv == ਨਿਰਾ) {
        ਵਾਪਸ E_INVALIDARG;
    }

    *ppv = ਨਿਰਾ;
    ਜੇ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_ਨਿਸ਼ਾਨਾ)) {
        *ppv = (ਖਾਲੀ *)ਨਿਸ਼ਾਨਾ;
    }
    ਜੇ (*ppv) {
        SDLDrop_ਨਿਸ਼ਾਨਾ_ਜੋੜੋ_Ref(ਨਿਸ਼ਾਨਾ);
        ਵਾਪਸ S_OK;
    }
    ਵਾਪਸ E_NOINTERFACE;
}

ਸਥਿਰ STDMETHODIMP SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Enter(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ,
                                            IDataObject *p_ਅੰਕੜੇ_Object, DWORD grf_ਕੁੰਜੀ_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ਬਿੰਦੂ_2 pnt = { pt.x, pt.y };
    ਜੇ (Screen_ਮੰਜ਼ਿਲ_Client(ਨਿਸ਼ਾਨਾ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, pnt.x, pnt.y);
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ਵਾਪਸ S_OK;
}

ਸਥਿਰ STDMETHODIMP SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Over(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ,
                                           DWORD grf_ਕੁੰਜੀ_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ਬਿੰਦੂ_2 pnt = { pt.x, pt.y };
    ਜੇ (Screen_ਮੰਜ਼ਿਲ_Client(ਨਿਸ਼ਾਨਾ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, pnt.x, pnt.y);
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ਵਾਪਸ S_OK;
}

ਸਥਿਰ STDMETHODIMP SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Leave(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In DragLeave");
    SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
    ਵਾਪਸ S_OK;
}

ਸਥਿਰ STDMETHODIMP SDLDrop_ਨਿਸ਼ਾਨਾ_Drop(SDLDrop_ਨਿਸ਼ਾਨਾ *ਨਿਸ਼ਾਨਾ,
                                       IDataObject *p_ਅੰਕੜੇ_Object, DWORD grf_ਕੁੰਜੀ_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    ਬਿੰਦੂ_2 pnt = { pt.x, pt.y };
    ਜੇ (Screen_ਮੰਜ਼ਿਲ_Client(ਨਿਸ਼ਾਨਾ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, pnt.x, pnt.y);
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_ਅੰਕੜੇ_Object->lpVtbl->EnumFormatEtc(p_ਅੰਕੜੇ_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ਜੇ (hres == S_OK) {
            FORMATETC fetc;
            ਜਦੋਂ (pEnumFormatEtc->lpVtbl->ਅਗਲਾ_3(pEnumFormatEtc, 1, &fetc, ਨਿਰਾ) == S_OK) {
                ਅੱਖਰ name[257] = { 0 };
                ਅਚਲ ਅੱਖਰ *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ਜੇ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ਨਹੀਂਤਾਂ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ਨਿਸ਼ਾਨਾ->format_file;
        fetc.ptd = ਨਿਰਾ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ਅਚਲ ਅੱਖਰ *format_mime = "text/uri-list";
        ਜੇ (SUCCEEDED(p_ਅੰਕੜੇ_Object->lpVtbl->Query_Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ਅੰਕੜੇ_Object->lpVtbl->Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ਜੇ (SUCCEEDED(hres)) {
                ਅਚਲ size_t bsize = Global_ਮਾਪ(med.hGlobal);
                ਅਚਲ ਖਾਲੀ *ਬਫਰ_2 = (ਖਾਲੀ *)Global_ਤਾਲਾ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, ਬਫਰ_2);
                ਜੇ (ਬਫਰ_2) {
                    ਅੱਖਰ *ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(bsize + ਆਕਾਰ(Uint32));
                    SDL_memcpy((Uint8 *)ਪਾਠ, ਬਫਰ_2, bsize);
                    SDL_memset((Uint8 *)ਪਾਠ + bsize, 0, ਆਕਾਰ(Uint32));
                    ਅੱਖਰ *saveptr = ਨਿਰਾ;
                    ਅੱਖਰ *token = SDL_strtok_r(ਪਾਠ, "\r\n", &saveptr);
                    ਜਦੋਂ (token != ਨਿਰਾ) {
                        ਜੇ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)SDL_strlen(token), (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, token);
                            SDL_SendDropFile(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, ਨਿਰਾ, token);
                        }
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    SDL_free(ਪਾਠ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
                ਵਾਪਸ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ਨਿਸ਼ਾਨਾ->format_ਪਾਠ;
        fetc.ptd = ਨਿਰਾ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ਅਚਲ ਅੱਖਰ *format_mime = "text/plain;charset=utf-8";
        ਜੇ (SUCCEEDED(p_ਅੰਕੜੇ_Object->lpVtbl->Query_Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ਅੰਕੜੇ_Object->lpVtbl->Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ਜੇ (SUCCEEDED(hres)) {
                ਅਚਲ size_t bsize = Global_ਮਾਪ(med.hGlobal);
                ਅਚਲ ਖਾਲੀ *ਬਫਰ_2 = (ਖਾਲੀ *)Global_ਤਾਲਾ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, ਬਫਰ_2);
                ਜੇ (ਬਫਰ_2) {
                    ਅੱਖਰ *ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(bsize + ਆਕਾਰ(Uint32));
                    SDL_memcpy((Uint8 *)ਪਾਠ, ਬਫਰ_2, bsize);
                    SDL_memset((Uint8 *)ਪਾਠ + bsize, 0, ਆਕਾਰ(Uint32));
                    ਅੱਖਰ *saveptr = ਨਿਰਾ;
                    ਅੱਖਰ *token = SDL_strtok_r(ਪਾਠ, "\r\n", &saveptr);
                    ਜਦੋਂ (token != ਨਿਰਾ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)SDL_strlen(token), (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, token);
                        SDL_Send_Drop_ਪਾਠ(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, (ਅੱਖਰ *)token);
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    SDL_free(ਪਾਠ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
                ਵਾਪਸ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ਨਿਰਾ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ਅਚਲ ਅੱਖਰ *format_mime = "CF_UNICODETEXT";
        ਜੇ (SUCCEEDED(p_ਅੰਕੜੇ_Object->lpVtbl->Query_Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ਅੰਕੜੇ_Object->lpVtbl->Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ਜੇ (SUCCEEDED(hres)) {
                ਅਚਲ size_t bsize = Global_ਮਾਪ(med.hGlobal);
                ਅਚਲ ਖਾਲੀ *ਬਫਰ_2 = (ਖਾਲੀ *)Global_ਤਾਲਾ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, ਬਫਰ_2);
                ਜੇ (ਬਫਰ_2) {
                    ਬਫਰ_2 = WIN_String_ਮੰਜ਼ਿਲ_UTF8_W((ਅਚਲ wchar_t *)ਬਫਰ_2);
                    ਜੇ (ਬਫਰ_2) {
                        ਅਚਲ size_t lbuffer = SDL_strlen((ਅਚਲ ਅੱਖਰ *)ਬਫਰ_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)lbuffer, ਬਫਰ_2);
                        ਅੱਖਰ *ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(lbuffer + ਆਕਾਰ(Uint32));
                        SDL_memcpy((Uint8 *)ਪਾਠ, ਬਫਰ_2, lbuffer);
                        SDL_memset((Uint8 *)ਪਾਠ + lbuffer, 0, ਆਕਾਰ(Uint32));
                        ਅੱਖਰ *saveptr = ਨਿਰਾ;
                        ਅੱਖਰ *token = SDL_strtok_r(ਪਾਠ, "\r\n", &saveptr);
                        ਜਦੋਂ (token != ਨਿਰਾ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)SDL_strlen(token), (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)lbuffer, token);
                            SDL_Send_Drop_ਪਾਠ(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, (ਅੱਖਰ *)token);
                            token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                        }
                        SDL_free(ਪਾਠ);
                        SDL_free((ਖਾਲੀ *)ਬਫਰ_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
                ਵਾਪਸ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_ਪਾਠ;
        fetc.ptd = ਨਿਰਾ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ਅਚਲ ਅੱਖਰ *format_mime = "CF_TEXT";
        ਜੇ (SUCCEEDED(p_ਅੰਕੜੇ_Object->lpVtbl->Query_Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ਅੰਕੜੇ_Object->lpVtbl->Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ਜੇ (SUCCEEDED(hres)) {
                ਅਚਲ size_t bsize = Global_ਮਾਪ(med.hGlobal);
                ਅਚਲ ਖਾਲੀ *ਬਫਰ_2 = (ਖਾਲੀ *)Global_ਤਾਲਾ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, ਬਫਰ_2);
                ਜੇ (ਬਫਰ_2) {
                    ਅੱਖਰ *ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(bsize + ਆਕਾਰ(Uint32));
                    SDL_memcpy((Uint8 *)ਪਾਠ, ਬਫਰ_2, bsize);
                    SDL_memset((Uint8 *)ਪਾਠ + bsize, 0, ਆਕਾਰ(Uint32));
                    ਅੱਖਰ *saveptr = ਨਿਰਾ;
                    ਅੱਖਰ *token = SDL_strtok_r(ਪਾਠ, "\r\n", &saveptr);
                    ਜਦੋਂ (token != ਨਿਰਾ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)SDL_strlen(token), (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, token);
                        SDL_Send_Drop_ਪਾਠ(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, (ਅੱਖਰ *)token);
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    SDL_free(ਪਾਠ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
                ਵਾਪਸ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ਨਿਰਾ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ਅਚਲ ਅੱਖਰ *format_mime = "CF_HDROP";
        ਜੇ (SUCCEEDED(p_ਅੰਕੜੇ_Object->lpVtbl->Query_Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ਅੰਕੜੇ_Object->lpVtbl->Get_ਅੰਕੜੇ(p_ਅੰਕੜੇ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ਜੇ (SUCCEEDED(hres)) {
                ਅਚਲ size_t bsize = Global_ਮਾਪ(med.hGlobal);
                HDROP drop = (HDROP)Global_ਤਾਲਾ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, drop);
                UINT ਗਿਣਤੀ_2 = DragQueryFile(drop, 0xFFFFFFFF, ਨਿਰਾ, 0);
                ਲਈ (UINT i = 0; i < ਗਿਣਤੀ_2; ++i) {
                    UINT ਮਾਪ = DragQueryFile(drop, i, ਨਿਰਾ, 0) + 1;
                    LPTSTR ਬਫਰ_2 = (LPTSTR)SDL_malloc(ਮਾਪ * ਆਕਾਰ(TCHAR));
                    ਜੇ (ਬਫਰ_2) {
                        ਜੇ (DragQueryFile(drop, i, ਬਫਰ_2, ਮਾਪ)) {
                            ਅੱਖਰ *file = WIN_String_ਮੰਜ਼ਿਲ_UTF8(ਬਫਰ_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)SDL_strlen(file), (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)bsize, file);
                            SDL_SendDropFile(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ, ਨਿਰਾ, file);
                            SDL_free(file);
                        }
                        SDL_free(ਬਫਰ_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
                ਵਾਪਸ S_OK;
            }
        }
    }

    SDL_SendDropComplete(ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ);
    ਵਾਪਸ S_OK;
}

ਸਥਿਰ ਖਾਲੀ *vt_Drop_ਨਿਸ਼ਾਨਾ[] = {
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Query_Interface),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_ਜੋੜੋ_Ref),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Release),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Enter),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Over),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Drag_Leave),
    (ਖਾਲੀ *)(SDLDrop_ਨਿਸ਼ਾਨਾ_Drop)
};

ਖਾਲੀ WIN_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->videodata->oleinitialized) {
        ਜੇ (accept && !ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ) {
            SDLDrop_ਨਿਸ਼ਾਨਾ *drop_ਨਿਸ਼ਾਨਾ = (SDLDrop_ਨਿਸ਼ਾਨਾ *)SDL_calloc(1, ਆਕਾਰ(SDLDrop_ਨਿਸ਼ਾਨਾ));
            ਜੇ (drop_ਨਿਸ਼ਾਨਾ != ਨਿਰਾ) {
                drop_ਨਿਸ਼ਾਨਾ->lpVtbl = vt_Drop_ਨਿਸ਼ਾਨਾ;
                drop_ਨਿਸ਼ਾਨਾ->ਖਿੜਕੀ = ਖਿੜਕੀ;
                drop_ਨਿਸ਼ਾਨਾ->hwnd = ਅੰਕੜੇ->hwnd;
                drop_ਨਿਸ਼ਾਨਾ->format_file = ਰਜਿਸਟਰ_Clipboard_Format_W(L"text/uri-list");
                drop_ਨਿਸ਼ਾਨਾ->format_ਪਾਠ = ਰਜਿਸਟਰ_Clipboard_Format_W(L"text/plain;charset=utf-8");
                ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ = drop_ਨਿਸ਼ਾਨਾ;
                SDLDrop_ਨਿਸ਼ਾਨਾ_ਜੋੜੋ_Ref(drop_ਨਿਸ਼ਾਨਾ);
                ਰਜਿਸਟਰ_Drag_Drop(ਅੰਕੜੇ->hwnd, (LPDROPTARGET)drop_ਨਿਸ਼ਾਨਾ);
                SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             ਖਿੜਕੀ->id);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (!accept && ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ) {
            RevokeDragDrop(ਅੰਕੜੇ->hwnd);
            SDLDrop_ਨਿਸ਼ਾਨਾ_Release(ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ);
            ਅੰਕੜੇ->drop_ਨਿਸ਼ਾਨਾ = ਨਿਰਾ;
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         ਖਿੜਕੀ->id);
        }
    } ਨਹੀਂਤਾਂ {
        DragAcceptFiles(ਅੰਕੜੇ->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     ਖਿੜਕੀ->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_ਮਾਪ = ਆਕਾਰ(desc);
    desc.hwnd = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    ਚੋਣ (operation) {
    ਹਾਲਤ SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_ਗਿਣਤੀ = 1;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ SDL_Unsupported();
    }

    Flash_ਖਿੜਕੀ_Ex(&desc);

    ਵਾਪਸ true;
}

bool WIN_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਜੇ (!ਅੰਕੜੇ->taskbar_button_created) {
        ਵਾਪਸ true;
    }

    ਜੇ (ਖਿੜਕੀ->ਤਰੱਕੀ_state == SDL_ਤਰੱਕੀ_STATE_NONE && !ਅੰਕੜੇ->videodata->taskbar_list) {
        ਵਾਪਸ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(ਖਿੜਕੀ);
    ਜੇ (!taskbar_list) {
        ਵਾਪਸ false;
    }

    TBPFLAG tbpFlags;
    ਚੋਣ (ਖਿੜਕੀ->ਤਰੱਕੀ_state) {
    ਹਾਲਤ SDL_ਤਰੱਕੀ_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ਤਰੱਕੀ_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ਤਰੱਕੀ_STATE_ਸਾਧਾਰਨ:
        tbpFlags = TBPF_ਸਾਧਾਰਨ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ਤਰੱਕੀ_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ਤਰੱਕੀ_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->ਸੈੱਟ_ਤਰੱਕੀ_State(taskbar_list, ਅੰਕੜੇ->hwnd, tbpFlags);
    ਜੇ (FAILED(ret)) {
        ਵਾਪਸ WIN_ਸੈੱਟ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ਜੇ (ਖਿੜਕੀ->ਤਰੱਕੀ_state >= SDL_ਤਰੱਕੀ_STATE_ਸਾਧਾਰਨ) {
        ret = taskbar_list->lpVtbl->ਸੈੱਟ_ਤਰੱਕੀ_ਮੁੱਲ(taskbar_list, ਅੰਕੜੇ->hwnd, (ULONGLONG)(ਖਿੜਕੀ->ਤਰੱਕੀ_ਮੁੱਲ * 10000.f), 10000);
        ਜੇ (FAILED(ret)) {
            ਵਾਪਸ WIN_ਸੈੱਟ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਬਿੰਦੂ_2 pt;

    pt.x = x;
    pt.y = y;
    Client_ਮੰਜ਼ਿਲ_Screen(ਅੰਕੜੇ->hwnd, &pt);
    Send_ਸੁਨੇਹਾ(ਅੰਕੜੇ->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable)
{
    ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        HWND hwnd = ਅੰਕੜੇ->hwnd;
        ਅਚਲ LONG style = Get_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ਜੇ (focusable) {
            ਜੇ (style & WS_EX_NOACTIVATE) {
                ਜੇ (ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetWindowLong()");
                }
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (!(style & WS_EX_NOACTIVATE)) {
                ਜੇ (ਸੈੱਟ_ਖਿੜਕੀ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetWindowLong()");
                }
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            ਜੇ (!focusable && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
                SDL_ਖਿੜਕੀ *new_focus;
                ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(ਖਿੜਕੀ, &new_focus);
                WIN_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
            } ਨਹੀਂਤਾਂ ਜੇ (focusable) {
                ਜੇ (SDL_ShouldFocusPopup(ਖਿੜਕੀ)) {
                    WIN_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
                }
            }
        }

        ਵਾਪਸ true;
    }

    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਬੱਚਾ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ LONG_PTR ਮਾਪਾ_hwnd = (LONG_PTR)(ਮਾਪਾ ? ਮਾਪਾ->ਅੰਦਰੂਨੀ->hwnd : ਨਿਰਾ);
    ਅਚਲ DWORD style = Get_ਖਿੜਕੀ_Long(ਬੱਚਾ_ਅੰਕੜੇ->hwnd, GWL_STYLE);

    ਜੇ (!(style & WS_ਬੱਚਾ)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        ਸੈੱਟ_ਖਿੜਕੀ_Long_Ptr(ਬੱਚਾ_ਅੰਕੜੇ->hwnd, GWLP_HWNDPARENT, ਮਾਪਾ_hwnd);
    } ਨਹੀਂਤਾਂ {
        ਸੈੱਟ_ਮਾਪਾ(ਬੱਚਾ_ਅੰਕੜੇ->hwnd, (HWND)ਮਾਪਾ_hwnd);
    }
#ਜੇ_ਅੰਤ /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal)
{
#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ਅਚਲ HWND ਮਾਪਾ_hwnd = ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->hwnd;

    ਜੇ (modal) {
        // Disable the parent window.
        Enable_ਖਿੜਕੀ(ਮਾਪਾ_hwnd, FALSE);
    } ਨਹੀਂਤਾਂ ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
        // Re-enable the parent window
        Enable_ਖਿੜਕੀ(ਮਾਪਾ_hwnd, TRUE);
    }
#ਜੇ_ਅੰਤ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS
