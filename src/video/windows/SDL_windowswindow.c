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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h"

#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_dropevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowskeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

// Dropfile support
#ಅನ್ತರ್ಭಾವ <shellapi.h>

#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))
#ಅನ್ತರ್ಭಾವ <shobjidl.h>
#ಆದರೆ_ಅಂತ್ಯ

// Windows CE compatibility
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SWP_NOCOPYBITS
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_NOCOPYBITS 0
#ಆದರೆ_ಅಂತ್ಯ

/* An undocumented message to create a popup system menu
 * - wParam is always 0
 * - lParam = MAKELONG(x, y) where x and y are the screen coordinates where the menu should be displayed
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WM_POPUPSYSTEMMENU
#ವ್ಯಾಖ್ಯಾನಿಸು WM_POPUPSYSTEMMENU 0x313
#ಆದರೆ_ಅಂತ್ಯ

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

#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_BASIC               (WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_FULLSCREEN          (WS_POPUP | WS_MINIMIZEBOX)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_BORDERLESS          (WS_POPUP | WS_MINIMIZEBOX)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_BORDERLESS_WINDOWED (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_ಸಾಮಾನ್ಯ              (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_RESIZABLE           (WS_THICKFRAME | WS_MAXIMIZEBOX)
#ವ್ಯಾಖ್ಯಾನಿಸು STYLE_ಮುಖವಾಡ                (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_ಸಾಮಾನ್ಯ | STYLE_RESIZABLE)

ಸ್ಥಿರ DWORD Get_ಕಿಟಕಿ_Style(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    DWORD style = 0;

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        style |= WS_POPUP;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        style |= STYLE_FULLSCREEN;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
            /* This behavior more closely matches other platform where the window is borderless
               but still interacts with the window manager (e.g. task bar shows above it, it can
               be resized to fit within usable desktop area, etc.)
             */
            ಆದರೆ (SDL_GetHintBoolean("SDL_BORDERLESS_WINDOWED_STYLE", true)) {
                style |= STYLE_BORDERLESS_WINDOWED;
            } ಇಲ್ಲದಿದ್ದರೆ {
                style |= STYLE_BORDERLESS;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            style |= STYLE_ಸಾಮಾನ್ಯ;
        }

        /* The WS_MAXIMIZEBOX style flag needs to be retained for as long as the window is maximized,
         * or restoration from minimized can fail, and leaving maximized can result in an odd size.
         */
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) {
            /* You can have a borderless resizable window, but Windows doesn't always draw it correctly,
               see https://bugzilla.libsdl.org/show_bug.cgi?id=4466
             */
            ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) ||
                SDL_GetHintBoolean("SDL_BORDERLESS_RESIZABLE_STYLE", true)) {
                style |= STYLE_RESIZABLE;
            }
        }

        ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ && ಕಿಟಕಿ->ಆಂತರಿಕ->force_ws_maximizebox) {
            /* Even if the resizable flag is cleared, WS_MAXIMIZEBOX is still needed as long
             * as the window is maximized, or de-maximizing or minimizing and restoring the
             * maximized window can result in the window disappearing or being the wrong size.
             */
            style |= WS_MAXIMIZEBOX;
        }

        // Need to set initialize minimize style, or when we call ShowWindow with WS_MINIMIZE it will activate a random window
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
            style |= WS_MINIMIZE;
        }
    }
    ಹಿಂತಿರುಗಿ style;
}

ಸ್ಥಿರ DWORD Get_ಕಿಟಕಿ_Style_Ex(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    DWORD style = 0;

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ) || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_UTILITY)) {
        style |= WS_EX_TOOLWINDOW;
    }
    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ) || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
        style |= WS_EX_NOACTIVATE;
    }
    ಹಿಂತಿರುಗಿ style;
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಸ್ಥಿರ ITaskbarList3 *GetTaskbarList(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_assert(ದತ್ತಾಂಶ->taskbar_button_created);
    ಆದರೆ (!ದತ್ತಾಂಶ->videodata->taskbar_list) {
        HRESULT ret = CoCreateInstance(&CLSID_TaskbarList, ಖಾಲಿ, CLSCTX_ALL, &IID_ITaskbarList3, (LPVOID *)&ದತ್ತಾಂಶ->videodata->taskbar_list);
        ಆದರೆ (FAILED(ret)) {
            WIN_ಗಣ_Error_From_HRESULT("Unable to create taskbar list", ret);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ITaskbarList3 *taskbarlist = ದತ್ತಾಂಶ->videodata->taskbar_list;
        ret = taskbarlist->lpVtbl->HrInit(taskbarlist);
        ಆದರೆ (FAILED(ret)) {
            taskbarlist->lpVtbl->Release(taskbarlist);
            ದತ್ತಾಂಶ->videodata->taskbar_list = ಖಾಲಿ;
            WIN_ಗಣ_Error_From_HRESULT("Unable to initialize taskbar list", ret);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }
    ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->videodata->taskbar_list;
}
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Returns arguments to pass to SetWindowPos - the window rect, including frame, in Windows coordinates.
 * Can be called before we have a HWND.
 */
ಸ್ಥಿರ bool WIN_Adjust_ಕಿಟಕಿ_Rect_With_Style(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, DWORD style, DWORD styleEx, BOOL menu, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y, ಪೂರ್ಣಾಂಕ *ಅಗಲ, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ, SDL_ಕಿಟಕಿ_Rect rect_type)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = SDL_GetVideoDevice() ? SDL_GetVideoDevice()->ಆಂತರಿಕ : ಖಾಲಿ;
    RECT rect;

    // Client rect, in points
    ಆಯ್ಕೆ (rect_type) {
    ಸ್ಥಿತಿ SDL_WINDOWRECT_CURRENT:
        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->x, ಕಿಟಕಿ->y, x, y);
        *ಅಗಲ = ಕಿಟಕಿ->w;
        *ಎತ್ತರ = ಕಿಟಕಿ->h;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WINDOWRECT_WINDOWED:
        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->windowed.x, ಕಿಟಕಿ->windowed.y, x, y);
        *ಅಗಲ = ಕಿಟಕಿ->windowed.w;
        *ಎತ್ತರ = ಕಿಟಕಿ->windowed.h;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WINDOWRECT_FLOATING:
        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.x, ಕಿಟಕಿ->floating.y, x, y);
        *ಅಗಲ = ಕಿಟಕಿ->floating.w;
        *ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WINDOWRECT_PENDING:
        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->pending.x, ಕಿಟಕಿ->pending.y, x, y);
        *ಅಗಲ = ಕಿಟಕಿ->pending.w;
        *ಎತ್ತರ = ಕಿಟಕಿ->pending.h;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Should never be here
        SDL_assert_release(false);
        *ಅಗಲ = 0;
        *ಎತ್ತರ = 0;
        ನಿಲ್ಲಿಸು;
    }

    /* Copy the client size in pixels into this rect structure,
       which we'll then adjust with AdjustWindowRectEx */
    rect.ಎಡ = 0;
    rect.ತುದಿ = 0;
    rect.ಬಲ = *ಅಗಲ;
    rect.bottom = *ಎತ್ತರ;

    /* borderless windows will have WM_NCCALCSIZE return 0 for the non-client area. When this happens, it looks like windows will send a resize message
       expanding the window client area to the previous window + chrome size, so shouldn't need to adjust the window size for the set styles.
     */
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) && !SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
        Adjust_ಕಿಟಕಿ_Rect_Ex(&rect, style, menu, 0);
#ಇಲ್ಲದಿದ್ದರೆ
        ಆದರೆ (WIN_Is_ಪ್ರತಿ_Monitor_V2_DPIAware(SDL_GetVideoDevice())) {
            /* With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of
               AdjustWindowRectEx. */
            ಆದರೆ (videodata) {
                UINT ಚೌಕಟ್ಟು_dpi;
                SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
                ಚೌಕಟ್ಟು_dpi = (ದತ್ತಾಂಶ && videodata->Get_Dpi_For_ಕಿಟಕಿ) ? videodata->Get_Dpi_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ->hwnd) : USER_DEFAULT_SCREEN_DPI;
                ಆದರೆ (videodata->Adjust_ಕಿಟಕಿ_Rect_Ex_For_Dpi(&rect, style, menu, styleEx, ಚೌಕಟ್ಟು_dpi) == 0) {
                    ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("AdjustWindowRectExForDpi()");
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (Adjust_ಕಿಟಕಿ_Rect_Ex(&rect, style, menu, styleEx) == 0) {
                ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("AdjustWindowRectEx()");
            }
        }
#ಆದರೆ_ಅಂತ್ಯ
    }

    // Final rect in Windows screen space, including the frame
    *x += rect.ಎಡ;
    *y += rect.ತುದಿ;
    *ಅಗಲ = (rect.ಬಲ - rect.ಎಡ);
    *ಎತ್ತರ = (rect.bottom - rect.ತುದಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
    SDL_Log("WIN_AdjustWindowRectWithStyle: in: %d, %d, %dx%d, returning: %d, %d, %dx%d, used dpi %d for frame calculation",
            (rect_type == SDL_WINDOWRECT_FLOATING ? ಕಿಟಕಿ->floating.x : rect_type == SDL_WINDOWRECT_WINDOWED ? ಕಿಟಕಿ->windowed.x : ಕಿಟಕಿ->x),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ಕಿಟಕಿ->floating.y : rect_type == SDL_WINDOWRECT_WINDOWED ? ಕಿಟಕಿ->windowed.y : ಕಿಟಕಿ->y),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ಕಿಟಕಿ->floating.w : rect_type == SDL_WINDOWRECT_WINDOWED ? ಕಿಟಕಿ->windowed.w : ಕಿಟಕಿ->w),
            (rect_type == SDL_WINDOWRECT_FLOATING ? ಕಿಟಕಿ->floating.h : rect_type == SDL_WINDOWRECT_WINDOWED ? ಕಿಟಕಿ->windowed.h : ಕಿಟಕಿ->h),
            *x, *y, *ಅಗಲ, *ಎತ್ತರ, ಚೌಕಟ್ಟು_dpi);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_Adjust_ಕಿಟಕಿ_Rect(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y, ಪೂರ್ಣಾಂಕ *ಅಗಲ, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ, SDL_ಕಿಟಕಿ_Rect rect_type)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
    styleEx = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ಇಲ್ಲದಿದ್ದರೆ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ WIN_Adjust_ಕಿಟಕಿ_Rect_With_Style(ಕಿಟಕಿ, style, styleEx, menu, x, y, ಅಗಲ, ಎತ್ತರ, rect_type);
}

bool WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT ಚೌಕಟ್ಟು_dpi)
{
    SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *videodata = videodevice ? videodevice->ಆಂತರಿಕ : ಖಾಲಿ;
    DWORD style, styleEx;
    BOOL menu;

    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
    styleEx = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    menu = FALSE;
#ಇಲ್ಲದಿದ್ದರೆ
    menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    Adjust_ಕಿಟಕಿ_Rect_Ex(lpRect, style, menu, styleEx);
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (WIN_Is_ಪ್ರತಿ_Monitor_V2_DPIAware(videodevice)) {
        // With per-monitor v2, the window border/titlebar size depend on the DPI, so we need to call AdjustWindowRectExForDpi instead of AdjustWindowRectEx.
        ಆದರೆ (!ಚೌಕಟ್ಟು_dpi) {
            ಚೌಕಟ್ಟು_dpi = videodata->Get_Dpi_For_ಕಿಟಕಿ ? videodata->Get_Dpi_For_ಕಿಟಕಿ(hwnd) : USER_DEFAULT_SCREEN_DPI;
        }
        ಆದರೆ (!videodata->Adjust_ಕಿಟಕಿ_Rect_Ex_For_Dpi(lpRect, style, menu, styleEx, ಚೌಕಟ್ಟು_dpi)) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("AdjustWindowRectExForDpi()");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!Adjust_ಕಿಟಕಿ_Rect_Ex(lpRect, style, menu, styleEx)) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("AdjustWindowRectEx()");
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, UINT flags, SDL_ಕಿಟಕಿ_Rect rect_type)
{
    SDL_ಕಿಟಕಿ *ಮಗು_ಕಿಟಕಿ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    HWND ತುದಿ;
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ w, h;
    bool ಫಲಿತಾಂಶ = true;

    // Figure out what the window area will be
    ಆದರೆ (SDL_ShouldAllowTopmost() && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ)) {
        ತುದಿ = HWND_TOPMOST;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ತುದಿ = HWND_NOTOPMOST;
    }

    WIN_Adjust_ಕಿಟಕಿ_Rect(ಕಿಟಕಿ, &x, &y, &w, &h, rect_type);

    ದತ್ತಾಂಶ->expected_resize = !(flags & SWP_NOSIZE);
    ಆದರೆ (ಗಣ_ಕಿಟಕಿ_Pos(hwnd, ತುದಿ, x, y, w, h, flags) == 0) {
        ಫಲಿತಾಂಶ = WIN_ಗಣ_Error("SetWindowPos()");
    }
    ದತ್ತಾಂಶ->expected_resize = false;

    // Update any child windows
    ಗಾಗಿ (ಮಗು_ಕಿಟಕಿ = ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; ಮಗು_ಕಿಟಕಿ; ಮಗು_ಕಿಟಕಿ = ಮಗು_ಕಿಟಕಿ->ಮುಂದಿನ_sibling) {
        ಆದರೆ (!ಮಗು_ಕಿಟಕಿ->ಆಂತರಿಕ) {
            // This child window is not yet fully initialized.
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (!WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಮಗು_ಕಿಟಕಿ, flags, SDL_WINDOWRECT_CURRENT)) {
            ಫಲಿತಾಂಶ = false;
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ SDL_ಕಿಟಕಿ_Erase_Background_ಬಹುಲಕ Get_Erase_Background_ಬಹುಲಕ_Hint(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_WINDOWS_ERASE_BACKGROUND_ಬಹುಲಕ);
    ಆದರೆ (!hint)
        ಹಿಂತಿರುಗಿ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ಆದರೆ (SDL_strstr(hint, "never"))
        ಹಿಂತಿರುಗಿ SDL_ERASEBACKGROUNDMODE_NEVER;

    ಆದರೆ (SDL_strstr(hint, "initial"))
        ಹಿಂತಿರುಗಿ SDL_ERASEBACKGROUNDMODE_INITIAL;

    ಆದರೆ (SDL_strstr(hint, "always"))
        ಹಿಂತಿರುಗಿ SDL_ERASEBACKGROUNDMODE_ALWAYS;

    ಪೂರ್ಣಾಂಕ ಬಹುಲಕ = SDL_GetStringInteger(hint, 1);
    ಆದರೆ (ಬಹುಲಕ < 0 || ಬಹುಲಕ > 2) {
        SDL_Log("GetEraseBackgroundModeHint: invalid value for SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE. Fallback to default");
        ಹಿಂತಿರುಗಿ SDL_ERASEBACKGROUNDMODE_INITIAL;
    }

    ಹಿಂತಿರುಗಿ (SDL_ಕಿಟಕಿ_Erase_Background_ಬಹುಲಕ)ಬಹುಲಕ;
}

ಸ್ಥಿರ bool ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, HWND hwnd, HWND ಪೋಷಕ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Allocate the window data
    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }
    ದತ್ತಾಂಶ->ಕಿಟಕಿ = ಕಿಟಕಿ;
    ದತ್ತಾಂಶ->hwnd = hwnd;
    ದತ್ತಾಂಶ->ಪೋಷಕ = ಪೋಷಕ;
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ದತ್ತಾಂಶ->hdc = (HDC)ದತ್ತಾಂಶ->hwnd;
#ಇಲ್ಲದಿದ್ದರೆ
    ದತ್ತಾಂಶ->hdc = GetDC(hwnd);
#ಆದರೆ_ಅಂತ್ಯ
    ದತ್ತಾಂಶ->hinstance = (HINSTANCE)Get_ಕಿಟಕಿ_Long_Ptr(hwnd, GWLP_HINSTANCE);
    ದತ್ತಾಂಶ->mouse_button_flags = (WPARAM)-1;
    ದತ್ತಾಂಶ->ಕೊನೆಯ_ಸೂಚಕ_update = (LPARAM)-1;
    ದತ್ತಾಂಶ->videodata = videodata;
    ದತ್ತಾಂಶ->initializing = true;
    ದತ್ತಾಂಶ->hint_erase_background_ಬಹುಲಕ = Get_Erase_Background_ಬಹುಲಕ_Hint();


    // WIN_WarpCursor() jitters by +1, and remote desktop warp wobble is +/- 1
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    LONG remote_desktop_adjustment = GetSystemMetrics(SM_REMOTESESSION) ? 2 : 0;
    ದತ್ತಾಂಶ->cursor_ctrlock_rect.ಎಡ   = 0 - remote_desktop_adjustment;
    ದತ್ತಾಂಶ->cursor_ctrlock_rect.ತುದಿ    = 0;
    ದತ್ತಾಂಶ->cursor_ctrlock_rect.ಬಲ  = 1 + remote_desktop_adjustment;
    ದತ್ತಾಂಶ->cursor_ctrlock_rect.bottom = 1;
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (SDL_GetHintBoolean("SDL_WINDOW_RETAIN_CONTENT", false)) {
        ದತ್ತಾಂಶ->copybits_flag = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->copybits_flag = SWP_NOCOPYBITS;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
    SDL_Log("SetupWindowData: initialized data->scaling_dpi to %d", ದತ್ತಾಂಶ->scaling_dpi);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Associate the data with the window
    ಆದರೆ (!ಗಣ_Prop(hwnd, ಪಠ್ಯ_2("SDL_WindowData"), ದತ್ತಾಂಶ)) {
        ReleaseDC(hwnd, ದತ್ತಾಂಶ->hdc);
        SDL_free(ದತ್ತಾಂಶ);
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetProp() failed");
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    // Set up the window proc function
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GWLP_WNDPROC
        ದತ್ತಾಂಶ->wndproc = (WNDPROC)Get_ಕಿಟಕಿ_Long_Ptr(hwnd, GWLP_WNDPROC);
        ಆದರೆ (ದತ್ತಾಂಶ->wndproc != WIN_ಕಿಟಕಿ_Proc) {
            ಗಣ_ಕಿಟಕಿ_Long_Ptr(hwnd, GWLP_WNDPROC, (LONG_PTR)WIN_ಕಿಟಕಿ_Proc);
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ದತ್ತಾಂಶ->wndproc = (WNDPROC)Get_ಕಿಟಕಿ_Long(hwnd, GWL_WNDPROC);
        ಆದರೆ (ದತ್ತಾಂಶ->wndproc != WIN_ಕಿಟಕಿ_Proc) {
            ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_WNDPROC, (LONG_PTR)WIN_ಕಿಟಕಿ_Proc);
        }
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ {
        // We set up our window proc function at window creation.
        // If someone has set hooks to modify it, leave it alone.
    }

    // Fill in the SDL window with the window state
    {
        DWORD style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
        ಆದರೆ (style & WS_VISIBLE) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_HIDDEN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_HIDDEN;
        }
        ಆದರೆ (style & WS_POPUP) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_BORDERLESS;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_BORDERLESS;
        }
        ಆದರೆ (style & WS_THICKFRAME) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_RESIZABLE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(style & WS_POPUP)) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_RESIZABLE;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WS_MAXIMIZE
        ಆದರೆ (style & WS_MAXIMIZE) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MAXIMIZED;
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MAXIMIZED;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WS_MINIMIZE
        ಆದರೆ (style & WS_MINIMIZE) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MINIMIZED;
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MINIMIZED;
        }
    }
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        RECT rect;
        ಆದರೆ (GetClientRect(hwnd, &rect) && WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
            ಪೂರ್ಣಾಂಕ w = rect.ಬಲ;
            ಪೂರ್ಣಾಂಕ h = rect.bottom;

            ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
                ಕಿಟಕಿ->floating.w = ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->w = w;
                ಕಿಟಕಿ->floating.h = ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->h = h;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಕಿಟಕಿ->windowed.w && ಕಿಟಕಿ->windowed.w != w) || (ಕಿಟಕಿ->windowed.h && ಕಿಟಕಿ->windowed.h != h)) {
                // We tried to create a window larger than the desktop and Windows didn't allow it.  Override!
                ಪೂರ್ಣಾಂಕ x, y;
                // Figure out what the window area will be
                WIN_Adjust_ಕಿಟಕಿ_Rect(ಕಿಟಕಿ, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);
                ದತ್ತಾಂಶ->expected_resize = true;
                ಗಣ_ಕಿಟಕಿ_Pos(hwnd, ಖಾಲಿ, x, y, w, h, ದತ್ತಾಂಶ->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
                ದತ್ತಾಂಶ->expected_resize = false;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ->w = w;
                ಕಿಟಕಿ->h = h;
            }
        }
    }
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        ಬಿಂದು_2 ಬಿಂದು;
        ಬಿಂದು.x = 0;
        ಬಿಂದು.y = 0;
        ಆದರೆ (Client_ಗಮ್ಯ_Screen(hwnd, &ಬಿಂದು)) {
            ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
                ಕಿಟಕಿ->floating.x = ಕಿಟಕಿ->windowed.x = ಬಿಂದು.x;
                ಕಿಟಕಿ->floating.y = ಕಿಟಕಿ->windowed.y = ಬಿಂದು.y;
            }
            ಕಿಟಕಿ->x = ಬಿಂದು.x;
            ಕಿಟಕಿ->y = ಬಿಂದು.y;
        }
    }

    WIN_Update_ಕಿಟಕಿ_ICCProfile(ಕಿಟಕಿ, false);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS;
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (GetFocus() == hwnd) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS;
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
        WIN_UpdateClipCursor(ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ) {
        WIN_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(_this, ಕಿಟಕಿ, true);
    } ಇಲ್ಲದಿದ್ದರೆ {
        WIN_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(_this, ಕಿಟಕಿ, false);
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // Enable multi-touch
    ಆದರೆ (videodata->ರಿಜಿಸ್ಟರ್_Touch_ಕಿಟಕಿ) {
        videodata->ರಿಜಿಸ್ಟರ್_Touch_ಕಿಟಕಿ(hwnd, (TWF_FINETOUCH | TWF_WANTPALM));
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ->ಪೋಷಕ && !ಕಿಟಕಿ->ಪೋಷಕ) {
        ದತ್ತಾಂಶ->destroy_ಪೋಷಕ_with_ಕಿಟಕಿ = true;
    }

    ದತ್ತಾಂಶ->initializing = false;

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        // Query the title from the existing window
        LPTSTR title;
        ಪೂರ್ಣಾಂಕ titleLen;
        bool isstack;

        titleLen = Get_ಕಿಟಕಿ_ಪಠ್ಯ_ಉದ್ದಳತೆ(hwnd);
        title = SDL_small_alloc(TCHAR, titleLen + 1, &isstack);
        ಆದರೆ (title) {
            titleLen = Get_ಕಿಟಕಿ_ಪಠ್ಯ(hwnd, title, titleLen + 1);
        } ಇಲ್ಲದಿದ್ದರೆ {
            titleLen = 0;
        }
        ಆದರೆ (titleLen > 0) {
            ಕಿಟಕಿ->title = WIN_String_ಗಮ್ಯ_UTF8(title);
        }
        ಆದರೆ (title) {
            SDL_small_free(title, isstack);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WIN32_HWND_ಸೂಚಕ, ದತ್ತಾಂಶ->hwnd);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WIN32_HDC_ಸೂಚಕ, ದತ್ತಾಂಶ->hdc);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WIN32_INSTANCE_ಸೂಚಕ, ದತ್ತಾಂಶ->hinstance);

    // All done!
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Cleanup_ಕಿಟಕಿ_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ) {
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ಆದರೆ (ದತ್ತಾಂಶ->drop_ಗುರಿ) {
            WIN_AcceptDragAndDrop(ಕಿಟಕಿ, false);
        }
        SDL_free(ದತ್ತಾಂಶ->ICMFileName);
        ಆದರೆ (ದತ್ತಾಂಶ->keyboard_hook) {
            UnhookWindowsHookEx(ದತ್ತಾಂಶ->keyboard_hook);
        }
        ಆದರೆ (ದತ್ತಾಂಶ->hicon) {
            DestroyIcon(ದತ್ತಾಂಶ->hicon);
        }
        ReleaseDC(ದತ್ತಾಂಶ->hwnd, ದತ್ತಾಂಶ->hdc);
        RemoveProp(ದತ್ತಾಂಶ->hwnd, ಪಠ್ಯ_2("SDL_WindowData"));
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
            Destroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->hwnd);
            ಆದರೆ (ದತ್ತಾಂಶ->destroy_ಪೋಷಕ_with_ಕಿಟಕಿ && ದತ್ತಾಂಶ->ಪೋಷಕ) {
                Destroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->ಪೋಷಕ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Restore any original event handler...
            ಆದರೆ (ದತ್ತಾಂಶ->wndproc) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GWLP_WNDPROC
                ಗಣ_ಕಿಟಕಿ_Long_Ptr(ದತ್ತಾಂಶ->hwnd, GWLP_WNDPROC,
                                 (LONG_PTR)ದತ್ತಾಂಶ->wndproc);
#ಇಲ್ಲದಿದ್ದರೆ
                ಗಣ_ಕಿಟಕಿ_Long(ದತ್ತಾಂಶ->hwnd, GWL_WNDPROC,
                              (LONG_PTR)ದತ್ತಾಂಶ->wndproc);
#ಆದರೆ_ಅಂತ್ಯ
            }
        }
        SDL_free(ದತ್ತಾಂಶ);
    }
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ConstrainPopup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool output_ಗಮ್ಯ_pending)
{
    // Possibly clamp popup windows to the output borders
    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        SDL_ಕಿಟಕಿ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ಪೂರ್ಣಾಂಕ abs_x = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->floating.x;
        ಪೂರ್ಣಾಂಕ abs_y = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->floating.y;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಗಲ = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->floating.w;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಎತ್ತರ = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->floating.h;
        ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_x = 0, ಸ್ಥಾನಾಂತರ_y = 0;

        ಆದರೆ (ಕಿಟಕಿ->constrain_popup) {
            // Calculate the total offset from the parents
            ಗಾಗಿ (w = ಕಿಟಕಿ->ಪೋಷಕ; SDL_ಕಿಟಕಿ_IS_POPUP(w); w = w->ಪೋಷಕ) {
                ಸ್ಥಾನಾಂತರ_x += w->x;
                ಸ್ಥಾನಾಂತರ_y += w->y;
            }

            ಸ್ಥಾನಾಂತರ_x += w->x;
            ಸ್ಥಾನಾಂತರ_y += w->y;
            abs_x += ಸ್ಥಾನಾಂತರ_x;
            abs_y += ಸ್ಥಾನಾಂತರ_y;

            // Constrain the popup window to the display of the toplevel parent
            displayID = SDL_Get_Display_For_ಕಿಟಕಿ(w);
            SDL_GetDisplayBounds(displayID, &rect);
            ಆದರೆ (abs_x + ಅಗಲ > rect.x + rect.w) {
                abs_x -= (abs_x + ಅಗಲ) - (rect.x + rect.w);
            }
            ಆದರೆ (abs_y + ಎತ್ತರ > rect.y + rect.h) {
                abs_y -= (abs_y + ಎತ್ತರ) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ಆದರೆ (output_ಗಮ್ಯ_pending) {
            ಕಿಟಕಿ->pending.x = abs_x - ಸ್ಥಾನಾಂತರ_x;
            ಕಿಟಕಿ->pending.y = abs_y - ಸ್ಥಾನಾಂತರ_y;
            ಕಿಟಕಿ->pending.w = ಅಗಲ;
            ಕಿಟಕಿ->pending.h = ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->floating.x = abs_x - ಸ್ಥಾನಾಂತರ_x;
            ಕಿಟಕಿ->floating.y = abs_y - ಸ್ಥಾನಾಂತರ_y;
            ಕಿಟಕಿ->floating.w = ಅಗಲ;
            ಕಿಟಕಿ->floating.h = ಎತ್ತರ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ಗಣ_Keyboard_Focus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool ಗಣ_ಸಕ್ರಿಯ_focus)
{
    SDL_ಕಿಟಕಿ *toplevel = ಕಿಟಕಿ;

    // Find the topmost parent
    ಆಗ (SDL_ಕಿಟಕಿ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ಪೋಷಕ;
    }

    toplevel->keyboard_focus = ಕಿಟಕಿ;

    ಆದರೆ (ಗಣ_ಸಕ್ರಿಯ_focus && !ಕಿಟಕಿ->is_hiding && !ಕಿಟಕಿ->is_destroying) {
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    }
}

bool WIN_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    HWND hwnd = (HWND)SDL_Get_ಸೂಚಕ_Property(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WIN32_HWND_ಸೂಚಕ, SDL_Get_ಸೂಚಕ_Property(create_props, "sdl2-compat.external_window", ಖಾಲಿ));
    HWND ಪೋಷಕ = ಖಾಲಿ;
    ಆದರೆ (hwnd) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_EXTERNAL;

        ಆದರೆ (!ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(_this, ಕಿಟಕಿ, hwnd, ಪೋಷಕ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        DWORD style = STYLE_BASIC;
        DWORD styleEx = 0;
        ಪೂರ್ಣಾಂಕ x, y;
        ಪೂರ್ಣಾಂಕ w, h;

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_UTILITY) {
            ಪೋಷಕ = Create_ಕಿಟಕಿ(SDL_Appname, ಪಠ್ಯ_2(""), STYLE_BASIC, 0, 0, 32, 32, ಖಾಲಿ, ಖಾಲಿ, SDL_Instance, ಖಾಲಿ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ) {
            ಪೋಷಕ = ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->hwnd;
        }

        style |= Get_ಕಿಟಕಿ_Style(ಕಿಟಕಿ);
        styleEx |= (DWORD)SDL_Get_ಸಂಖ್ಯೆ_Property(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WIN32_STYLE_EX_ಸಂಖ್ಯೆ, Get_ಕಿಟಕಿ_Style_Ex(ಕಿಟಕಿ));

        // Figure out what the window area will be
        WIN_ConstrainPopup(ಕಿಟಕಿ, false);
        WIN_Adjust_ಕಿಟಕಿ_Rect_With_Style(ಕಿಟಕಿ, style, styleEx, FALSE, &x, &y, &w, &h, SDL_WINDOWRECT_FLOATING);

        hwnd = Create_ಕಿಟಕಿ_Ex(styleEx, SDL_Appname, ಪಠ್ಯ_2(""), style,
                              x, y, w, h, ಪೋಷಕ, ಖಾಲಿ, SDL_Instance, ಖಾಲಿ);
        ಆದರೆ (!hwnd) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("Couldn't create window");
        }

        WIN_Update_Dark_ಬಹುಲಕ_For_HWND(hwnd);

        WIN_PumpEventsForHWND(_this, hwnd);

        ಆದರೆ (!ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(_this, ಕಿಟಕಿ, hwnd, ಪೋಷಕ)) {
            Destroy_ಕಿಟಕಿ(hwnd);
            ಆದರೆ (ಪೋಷಕ) {
                Destroy_ಕಿಟಕಿ(ಪೋಷಕ);
            }
            ಹಿಂತಿರುಗಿ false;
        }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        // Ensure that the IME isn't active on the new window until explicitly requested.
        WIN_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(_this, ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ

        // Inform Windows of the frame change so we can respond to WM_NCCALCSIZE
        ಗಣ_ಕಿಟಕಿ_Pos(hwnd, ಖಾಲಿ, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
            /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The
               window is already shown after this and windows with WS_MINIMIZE do not generate a WM_SHOWWINDOW. This
               means you can't currently create a window that is initially hidden and is minimized when shown.
            */
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_HIDDEN;
            Show_ಕಿಟಕಿ(hwnd, SW_SHOWMINNOACTIVE);
        }
    }

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs)
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) {
        ಆದರೆ (videodata->Dwm_Enable_Blur_Behind_ಕಿಟಕಿ) {
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
            videodata->Dwm_Enable_Blur_Behind_ಕಿಟಕಿ(hwnd, &bb);
            DeleteObject(rgn);
        }
    }

    HWND share_hwnd = (HWND)SDL_Get_ಸೂಚಕ_Property(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WIN32_PIXEL_FORMAT_HWND_ಸೂಚಕ, ಖಾಲಿ);
    ಆದರೆ (share_hwnd) {
        HDC hdc = GetDC(share_hwnd);
        ಪೂರ್ಣಾಂಕ pixel_format = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;

        SDL_zero(pfd);
        DescribePixelFormat(hdc, pixel_format, ಗಾತ್ರ(pfd), &pfd);
        ReleaseDC(share_hwnd, hdc);

        ಆದರೆ (!ಗಣ_Pixel_Format(ಕಿಟಕಿ->ಆಂತರಿಕ->hdc, pixel_format, &pfd)) {
            WIN_Destroy_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetPixelFormat()");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
            ಹಿಂತಿರುಗಿ true;
        }

        // The rest of this macro mess is for OpenGL or OpenGL ES windows
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_ES2
        ಆದರೆ ((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
             && (!_this->gl_ದತ್ತಾಂಶ || WIN_GL_UseEGL(_this))
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_WGL
        ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
            ಆದರೆ (!WIN_GLES_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(_this, ಕಿಟಕಿ)) {
                WIN_Destroy_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ false;
            }
            ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GLES window surface (EGL support not configured)");
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_ES2

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
        ಆದರೆ (!WIN_GL_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(_this, ಕಿಟಕಿ)) {
            WIN_Destroy_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
            ಹಿಂತಿರುಗಿ false;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GL window (WGL support not configured)");
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    LPTSTR title = WIN_UTF8_ಗಮ್ಯ_String(ಕಿಟಕಿ->title);
    ಗಣ_ಕಿಟಕಿ_ಪಠ್ಯ(hwnd, title);
    SDL_free(title);
#ಆದರೆ_ಅಂತ್ಯ
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    HICON hicon = ಖಾಲಿ;
    BYTE *icon_bmp;
    ಪೂರ್ಣಾಂಕ icon_len, ಮುಖವಾಡ_len, ಅಡ್ಡಸಾಲು_len, y;
    BITMAPINFOHEADER *bmi;
    Uint8 *dst;
    bool isstack;
    bool ಫಲಿತಾಂಶ = true;

    // Create temporary buffer for ICONIMAGE structure
    SDL_COMPILE_ಸಮಯ_ASSERT(WIN_ಗಣ_ಕಿಟಕಿ_Icon_ಬಳಸುತ್ತದೆ_BITMAPINFOHEADER_ಗಮ್ಯ_prepare_an_ICONIMAGE, ಗಾತ್ರ(BITMAPINFOHEADER) == 40);
    ಮುಖವಾಡ_len = (icon->h * (icon->w + 7) / 8);
    icon_len = ಗಾತ್ರ(BITMAPINFOHEADER) + icon->h * icon->w * ಗಾತ್ರ(Uint32) + ಮುಖವಾಡ_len;
    icon_bmp = SDL_small_alloc(BYTE, icon_len, &isstack);
    ಆದರೆ (!icon_bmp) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Write the BITMAPINFO header
    bmi = (BITMAPINFOHEADER *)icon_bmp;
    bmi->bi_ಗಾತ್ರ = SDL_Swap32LE(ಗಾತ್ರ(BITMAPINFOHEADER));
    bmi->bi_ಅಗಲ = SDL_Swap32LE(icon->w);
    bmi->bi_ಎತ್ತರ = SDL_Swap32LE(icon->h * 2);
    bmi->biPlanes = SDL_Swap16LE(1);
    bmi->bi_ಬಿಟ್_ಎಣಿಕೆ = SDL_Swap16LE(32);
    bmi->biCompression = SDL_Swap32LE(BI_RGB);
    bmi->bi_ಗಾತ್ರ_Image = SDL_Swap32LE(icon->h * icon->w * ಗಾತ್ರ(Uint32));
    bmi->bi_XPels_ಪ್ರತಿ_Meter = SDL_Swap32LE(0);
    bmi->bi_YPels_ಪ್ರತಿ_Meter = SDL_Swap32LE(0);
    bmi->bi_Clr_ಬಳಸಿದ = SDL_Swap32LE(0);
    bmi->biClrImportant = SDL_Swap32LE(0);

    // Write the pixels upside down into the bitmap buffer
    SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
    dst = &icon_bmp[ಗಾತ್ರ(BITMAPINFOHEADER)];
    ಅಡ್ಡಸಾಲು_len = icon->w * ಗಾತ್ರ(Uint32);
    y = icon->h;
    ಆಗ (y--) {
        Uint8 *src = (Uint8 *)icon->pixels + y * icon->pitch;
        SDL_memcpy(dst, src, ಅಡ್ಡಸಾಲು_len);
        dst += ಅಡ್ಡಸಾಲು_len;
    }

    // Write the mask
    SDL_memset(icon_bmp + icon_len - ಮುಖವಾಡ_len, 0xFF, ಮುಖವಾಡ_len);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);

    SDL_small_free(icon_bmp, isstack);

    ಆದರೆ (!hicon) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SetWindowIcon() failed, error %08X", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)Get_ಕೊನೆಯ_Error());
    }

    ಆದರೆ (ದತ್ತಾಂಶ->hicon) {
        DestroyIcon(ದತ್ತಾಂಶ->hicon);
    }
    ದತ್ತಾಂಶ->hicon = hicon;

    // Set the icon for the window
    Send_ಸಂದೇಶ(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);

    // Set the icon in the task manager (should we do this?)
    Send_ಸಂದೇಶ(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
#ಆದರೆ_ಅಂತ್ಯ
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    /* HighDPI support: removed SWP_NOSIZE. If the move results in a DPI change, we need to allow
     * the window to resize (e.g. AdjustWindowRectExForDpi frame sizes are different).
     */
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED))) {
            WIN_ConstrainPopup(ಕಿಟಕಿ, true);
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಕಿಟಕಿ,
                                                 ಕಿಟಕಿ->ಆಂತರಿಕ->copybits_flag | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE |
                                                 SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_ENTER, true);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (!(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED))) {
        WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಕಿಟಕಿ, ಕಿಟಕಿ->ಆಂತರಿಕ->copybits_flag | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_PENDING);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Can't resize the window
        ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = false;
    }
}

bool WIN_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ)
{
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    RECT rcClient;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    GetClientRect(hwnd, &rcClient);

    *ತುದಿ = rcClient.ತುದಿ;
    *ಎಡ = rcClient.ಎಡ;
    *bottom = rcClient.bottom;
    *ಬಲ = rcClient.ಬಲ;

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ  // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    RECT rcClient, rc_ಕಿಟಕಿ;
    ಬಿಂದು_2 ptDiff;

    /* rcClient stores the size of the inner window, while rcWindow stores the outer size relative to the top-left
     * screen position; so the top/left values of rcClient are always {0,0} and bottom/right are {height,width} */
    ಆದರೆ (!GetClientRect(hwnd, &rcClient)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GetClientRect() failed, error %08X", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)Get_ಕೊನೆಯ_Error());
    }

    ಆದರೆ (!Get_ಕಿಟಕಿ_Rect(hwnd, &rc_ಕಿಟಕಿ)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("GetWindowRect() failed, error %08X", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)Get_ಕೊನೆಯ_Error());
    }

    /* convert the top/left values to make them relative to
     * the window; they will end up being slightly negative */
    ptDiff.y = rc_ಕಿಟಕಿ.ತುದಿ;
    ptDiff.x = rc_ಕಿಟಕಿ.ಎಡ;

    ಆದರೆ (!Screen_ಗಮ್ಯ_Client(hwnd, &ptDiff)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ScreenToClient() failed, error %08X", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)Get_ಕೊನೆಯ_Error());
    }

    rc_ಕಿಟಕಿ.ತುದಿ = ptDiff.y;
    rc_ಕಿಟಕಿ.ಎಡ = ptDiff.x;

    /* convert the bottom/right values to make them relative to the window,
     * these will be slightly bigger than the inner width/height */
    ptDiff.y = rc_ಕಿಟಕಿ.bottom;
    ptDiff.x = rc_ಕಿಟಕಿ.ಬಲ;

    ಆದರೆ (!Screen_ಗಮ್ಯ_Client(hwnd, &ptDiff)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ScreenToClient() failed, error %08X", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)Get_ಕೊನೆಯ_Error());
    }

    rc_ಕಿಟಕಿ.bottom = ptDiff.y;
    rc_ಕಿಟಕಿ.ಬಲ = ptDiff.x;

    /* Now that both the inner and outer rects use the same coordinate system we can subtract them to get the border size.
     * Keep in mind that the top/left coordinates of rcWindow are negative because the border lies slightly before {0,0},
     * so switch them around because SDL3 wants them in positive. */
    *ತುದಿ = rcClient.ತುದಿ - rc_ಕಿಟಕಿ.ತುದಿ;
    *ಎಡ = rcClient.ಎಡ - rc_ಕಿಟಕಿ.ಎಡ;
    *bottom = rc_ಕಿಟಕಿ.bottom - rcClient.bottom;
    *ಬಲ = rc_ಕಿಟಕಿ.ಬಲ - rcClient.ಬಲ;

    ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ಶೂನ್ಯ WIN_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    RECT rect;

    ಆದರೆ (GetClientRect(hwnd, &rect) && WIN_ಕಿಟಕಿ_Rect_Valid(&rect)) {
        *w = rect.ಬಲ;
        *h = rect.bottom;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->ಕೊನೆಯ_pixel_w && ಕಿಟಕಿ->ಕೊನೆಯ_pixel_h) {
        *w = ಕಿಟಕಿ->ಕೊನೆಯ_pixel_w;
        *h = ಕಿಟಕಿ->ಕೊನೆಯ_pixel_h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Probably created minimized, use the restored size
        *w = ಕಿಟಕಿ->floating.w;
        *h = ಕಿಟಕಿ->floating.h;
    }
}

ಶೂನ್ಯ WIN_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    DWORD style;

    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ACTIVATE_WHEN_SHOWN, true);

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        // Update our position in case our parent moved while we were hidden
        WIN_ಗಣ_ಕಿಟಕಿ_Position(_this, ಕಿಟಕಿ);
    }

    // If the window isn't borderless and will be fullscreen, use the borderless style to hide the initial borders.
    ಆದರೆ (ಕಿಟಕಿ->pending_flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS)) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_BORDERLESS;
            style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
            style &= ~STYLE_ಮುಖವಾಡ;
            style |= Get_ಕಿಟಕಿ_Style(ಕಿಟಕಿ);
            ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE, style);
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_BORDERLESS;
        }
    }
    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);
    ಆದರೆ (style & WS_EX_NOACTIVATE) {
        bActivate = false;
    }

    ದತ್ತಾಂಶ->showing_ಕಿಟಕಿ = true;
    ಆದರೆ (bActivate) {
        Show_ಕಿಟಕಿ(hwnd, SW_SHOW);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Use SetWindowPos instead of ShowWindow to avoid activating the parent window if this is a child window
        ಗಣ_ಕಿಟಕಿ_Pos(hwnd, ಖಾಲಿ, 0, 0, 0, 0, ಕಿಟಕಿ->ಆಂತರಿಕ->copybits_flag | SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
    ದತ್ತಾಂಶ->showing_ಕಿಟಕಿ = false;

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE) && bActivate) {
        WIN_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
    }
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        WIN_ಗಣ_ಕಿಟಕಿ_Modal(_this, ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ WIN_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        WIN_ಗಣ_ಕಿಟಕಿ_Modal(_this, ಕಿಟಕಿ, false);
    }

    Show_ಕಿಟಕಿ(hwnd, SW_HIDE);

    // Transfer keyboard focus back to the parent from a grabbing popup.
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
        SDL_ಕಿಟಕಿ *new_focus;
        ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(ಕಿಟಕಿ, &new_focus);
        WIN_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
    }
}

ಶೂನ್ಯ WIN_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    /* If desired, raise the window more forcefully.
     * Technique taken from http://stackoverflow.com/questions/916259/ .
     * Specifically, http://stackoverflow.com/a/34414846 .
     *
     * The issue is that Microsoft has gone through a lot of trouble to make it
     * nearly impossible to programmatically move a window to the foreground,
     * for "security" reasons. Apparently, the following song-and-dance gets
     * around their objections. */
    bool bForce = SDL_GetHintBoolean(SDL_HINT_FORCE_RAISEWINDOW, false);
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ACTIVATE_WHEN_RAISED, true);

    HWND hCurWnd = ಖಾಲಿ;
    DWORD dwMyID = 0u;
    DWORD dwCurID = 0u;

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    ಆದರೆ (bForce) {
        hCurWnd = Get_Foreground_ಕಿಟಕಿ();
        dwMyID = GetCurrentThreadId();
        dwCurID = Get_ಕಿಟಕಿ_Thread_Process_Id(hCurWnd, ಖಾಲಿ);
        Show_ಕಿಟಕಿ(hwnd, SW_RESTORE);
        Attach_Thread_ಒಳಹರಿವು(dwCurID, dwMyID, TRUE);
        ಗಣ_ಕಿಟಕಿ_Pos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        ಆದರೆ (!SDL_ShouldAllowTopmost() || !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ)) {
            ಗಣ_ಕಿಟಕಿ_Pos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
    }
    ಆದರೆ (bActivate) {
        ಗಣ_Foreground_ಕಿಟಕಿ(hwnd);
        ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
            WIN_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, ಕಿಟಕಿ->ಪೋಷಕ == SDL_GetKeyboardFocus());
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಣ_ಕಿಟಕಿ_Pos(hwnd, HWND_ತುದಿ, 0, 0, 0, 0, ದತ್ತಾಂಶ->copybits_flag | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
    ಆದರೆ (bForce) {
        Attach_Thread_ಒಳಹರಿವು(dwCurID, dwMyID, FALSE);
        ಗಣ_Focus(hwnd);
        ಗಣ_ಸಕ್ರಿಯ_ಕಿಟಕಿ(hwnd);
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

ಶೂನ್ಯ WIN_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        HWND hwnd = ದತ್ತಾಂಶ->hwnd;
        ದತ್ತಾಂಶ->expected_resize = true;
        Show_ಕಿಟಕಿ(hwnd, SW_MAXIMIZE);
        ದತ್ತಾಂಶ->expected_resize = false;

        /* Clamp the maximized window size to the max window size.
         * This is automatic if maximizing from the window controls.
         */
        ಆದರೆ (ಕಿಟಕಿ->max_w || ಕಿಟಕಿ->max_h) {
            ಪೂರ್ಣಾಂಕ fx, fy, fw, fh;

            ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->max_w ? SDL_min(ಕಿಟಕಿ->w, ಕಿಟಕಿ->max_w) : ಕಿಟಕಿ->windowed.w;
            ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->max_h ? SDL_min(ಕಿಟಕಿ->h, ಕಿಟಕಿ->max_h) : ಕಿಟಕಿ->windowed.h;
            WIN_Adjust_ಕಿಟಕಿ_Rect(ಕಿಟಕಿ, &fx, &fy, &fw, &fh, SDL_WINDOWRECT_WINDOWED);

            ದತ್ತಾಂಶ->expected_resize = true;
            ಗಣ_ಕಿಟಕಿ_Pos(hwnd, HWND_ತುದಿ, fx, fy, fw, fh, ದತ್ತಾಂಶ->copybits_flag | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            ದತ್ತಾಂಶ->expected_resize = false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->windowed_ಬಹುಲಕ_was_maximized = true;
    }
}

ಶೂನ್ಯ WIN_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    HWND hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    Show_ಕಿಟಕಿ(hwnd, SW_MINIMIZE);
}

ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    DWORD style;

    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ಮುಖವಾಡ;
    style |= Get_ಕಿಟಕಿ_Style(ಕಿಟಕಿ);

    ದತ್ತಾಂಶ->ಒಳ_border_change = true;
    ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE, style);
    WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಕಿಟಕಿ, ದತ್ತಾಂಶ->copybits_flag | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    ದತ್ತಾಂಶ->ಒಳ_border_change = false;
}

ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    DWORD style;

    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ಮುಖವಾಡ;
    style |= Get_ಕಿಟಕಿ_Style(ಕಿಟಕಿ);

    ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE, style);
}

ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ)
{
    WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಕಿಟಕಿ, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER, SDL_WINDOWRECT_CURRENT);
}

ಶೂನ್ಯ WIN_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಆದರೆ (!ದತ್ತಾಂಶ->showing_ಕಿಟಕಿ || ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED)) {
            HWND hwnd = ದತ್ತಾಂಶ->hwnd;
            ದತ್ತಾಂಶ->expected_resize = true;
            Show_ಕಿಟಕಿ(hwnd, SW_RESTORE);
            ದತ್ತಾಂಶ->expected_resize = false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->windowed_ಬಹುಲಕ_was_maximized = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_Update_ಮೂಲೆ_Rounding_For_HWND(SDL_VideoDevice *_this, HWND hwnd, DWM_ಕಿಟಕಿ_ಮೂಲೆ_PREFERENCE ಮೂಲೆ_Pref)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->Dwm_ಗಣ_ಕಿಟಕಿ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_ಗಣ_ಕಿಟಕಿ_Attribute(hwnd, DWMWA_ಕಿಟಕಿ_ಮೂಲೆ_PREFERENCE, &ಮೂಲೆ_Pref, ಗಾತ್ರ(ಮೂಲೆ_Pref));
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_UpdateBorderColorForHWND(SDL_VideoDevice *_this, HWND hwnd, COLORREF colorRef)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->Dwm_ಗಣ_ಕಿಟಕಿ_Attribute && WIN_IsWindows11OrGreater()) {
        videodata->Dwm_ಗಣ_ಕಿಟಕಿ_Attribute(hwnd, DWMWA_BORDER_COLOR, &colorRef, ಗಾತ್ರ(colorRef));
    }
#ಆದರೆ_ಅಂತ್ಯ
}

/**
 * Reconfigures the window to fill the given display, if fullscreen is true, otherwise restores the window.
 */
SDL_Fullscreen_ಫಲಿತಾಂಶ WIN_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ ? ದತ್ತಾಂಶ->hwnd : ಖಾಲಿ;
    MONITORINFO minfo;
    DWORD style, styleEx;
    HWND ತುದಿ;
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ w, h;
    bool enterMaximized = false;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d", (ಪೂರ್ಣಾಂಕ)fullscreen);
#ಆದರೆ_ಅಂತ್ಯ

    /* Early out if already not in fullscreen, or the styling on
     * external windows may end up being overridden.
     */
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && !fullscreen) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಆದರೆ (SDL_ShouldAllowTopmost() && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ)) {
        ತುದಿ = HWND_TOPMOST;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ತುದಿ = HWND_NOTOPMOST;
    }

    /* Use GetMonitorInfo instead of WIN_GetDisplayBounds because we want the
       monitor bounds in Windows coordinates (pixels) rather than SDL coordinates (points). */
    SDL_zero(minfo);
    minfo.cb_ಗಾತ್ರ = ಗಾತ್ರ(MONITORINFO);
    ಆದರೆ (!GetMonitorInfo(displaydata->MonitorHandle, &minfo)) {
        SDL_ಗಣ_Error("GetMonitorInfo failed");
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, fullscreen ? SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN : SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
    style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE);
    style &= ~STYLE_ಮುಖವಾಡ;
    style |= Get_ಕಿಟಕಿ_Style(ಕಿಟಕಿ);
    styleEx = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);

    ಆದರೆ (fullscreen) {
        x = minfo.rcMonitor.ಎಡ;
        y = minfo.rcMonitor.ತುದಿ;
        w = minfo.rcMonitor.ಬಲ - minfo.rcMonitor.ಎಡ;
        h = minfo.rcMonitor.bottom - minfo.rcMonitor.ತುದಿ;

        /* Unset the maximized flag.  This fixes
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215
        */
        ಆದರೆ (style & WS_MAXIMIZE) {
            ದತ್ತಾಂಶ->windowed_ಬಹುಲಕ_was_maximized = true;
            style &= ~WS_MAXIMIZE;
        }

        // Disable corner rounding & border color (Windows 11+) so the window fills the full screen
        WIN_Update_ಮೂಲೆ_Rounding_For_HWND(_this, hwnd, DWMWCP_DONOTROUND);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_NONE);
    } ಇಲ್ಲದಿದ್ದರೆ {
        BOOL menu;

        WIN_Update_ಮೂಲೆ_Rounding_For_HWND(_this, hwnd, DWMWCP_DEFAULT);
        WIN_UpdateBorderColorForHWND(_this, hwnd, DWMWA_COLOR_DEFAULT);

        /* Restore window-maximization state, as applicable.
           Special care is taken to *not* do this if and when we're
           alt-tab'ing away (to some other window; as indicated by
           in_window_deactivation), otherwise
           https://bugzilla.libsdl.org/show_bug.cgi?id=3215 can reproduce!
        */
        ಆದರೆ (ದತ್ತಾಂಶ->windowed_ಬಹುಲಕ_was_maximized && !ದತ್ತಾಂಶ->ಒಳ_ಕಿಟಕಿ_deactivation) {
            enterMaximized = true;
            ದತ್ತಾಂಶ->disable_move_ಗಾತ್ರ_events = true;
        }

        menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != ಖಾಲಿ);
        WIN_Adjust_ಕಿಟಕಿ_Rect_With_Style(ಕಿಟಕಿ, style, styleEx, menu,
                                      &x, &y,
                                      &w, &h,
                                      SDL_WINDOWRECT_FLOATING);
        ದತ್ತಾಂಶ->windowed_ಬಹುಲಕ_was_maximized = false;

        /* A window may have been maximized by dragging it to the top of another display, in which case the floating
         * position may be out-of-date. If the window is being restored to maximized, and the maximized and floating
         * position are on different displays, try to center the window on the maximized display for restoration, which
         * mimics native Windows behavior.
         */
        ಆದರೆ (enterMaximized) {
            ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು windowed_ಬಿಂದು = { ಕಿಟಕಿ->windowed.x, ಕಿಟಕಿ->windowed.y };
            ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು floating_ಬಿಂದು = { ಕಿಟಕಿ->floating.x, ಕಿಟಕಿ->floating.y };
            ಸ್ಥಿರಾಂಕ SDL_DisplayID floating_display = SDL_Get_Display_For_ಬಿಂದು(&floating_ಬಿಂದು);
            ಸ್ಥಿರಾಂಕ SDL_DisplayID windowed_display = SDL_Get_Display_For_ಬಿಂದು(&windowed_ಬಿಂದು);

            ಆದರೆ (floating_display != windowed_display) {
                SDL_Rect bounds;

                SDL_zero(bounds);
                SDL_GetDisplayUsableBounds(windowed_display, &bounds);
                ಆದರೆ (w < bounds.w) {
                    x = bounds.x + (bounds.w - w) / 2;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    x = bounds.x;
                }
                ಆದರೆ (h < bounds.h) {
                    y = bounds.y + (bounds.h - h) / 2;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    y = bounds.y;
                }
            }
        }
    }

    /* Always reset the window to the base floating size before possibly re-applying the maximized state,
     * otherwise, the base floating size can seemingly be lost in some cases.
     */
    ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_STYLE, style);
    ದತ್ತಾಂಶ->expected_resize = true;
    ಗಣ_ಕಿಟಕಿ_Pos(hwnd, ತುದಿ, x, y, w, h, ದತ್ತಾಂಶ->copybits_flag | SWP_NOACTIVATE);
    ದತ್ತಾಂಶ->expected_resize = false;
    ದತ್ತಾಂಶ->disable_move_ಗಾತ್ರ_events = false;

    ಆದರೆ (enterMaximized) {
        WIN_Maximize_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (!fullscreen && ದತ್ತಾಂಶ && ದತ್ತಾಂಶ->hicon) {
        // Reset the icon for the window when returning from fullscreen mode
        Send_ಸಂದೇಶ(hwnd, WM_SETICON, ICON_SMALL, 0);
        Send_ಸಂದೇಶ(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)ದತ್ತಾಂಶ->hicon);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HIGHDPI_DEBUG
    SDL_Log("WIN_SetWindowFullscreen: %d finished. Set window to %d,%d, %dx%d", (ಪೂರ್ಣಾಂಕ)fullscreen, x, y, w, h);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಶೂನ್ಯ WIN_Update_ಕಿಟಕಿ_ICCProfile(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool send_event)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);

    ಆದರೆ (displaydata) {
        HDC hdc = CreateDCW(displaydata->DeviceName, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);
        ಆದರೆ (hdc) {
            WCHAR fileName[MAX_ಮಾರ್ಗ];
            DWORD file_Name_ಗಾತ್ರ = SDL_arraysize(fileName);
            ಆದರೆ (GetICMProfileW(hdc, &file_Name_ಗಾತ್ರ, fileName)) {
                // fileNameSize includes '\0' on return
                ಆದರೆ (!ದತ್ತಾಂಶ->ICMFileName ||
                    SDL_wcscmp(ದತ್ತಾಂಶ->ICMFileName, fileName) != 0) {
                    SDL_free(ದತ್ತಾಂಶ->ICMFileName);
                    ದತ್ತಾಂಶ->ICMFileName = SDL_wcsdup(fileName);
                    ಆದರೆ (send_event) {
                        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ICCPROF_ಬದಲಾಯಿತು, 0, 0);
                    }
                }
            }
            DeleteDC(hdc);
        }
    }
}

ಶೂನ್ಯ *WIN_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಅಕ್ಷರ *filename_utf8;
    ಶೂನ್ಯ *icc_Profile_ದತ್ತಾಂಶ = ಖಾಲಿ;

    filename_utf8 = WIN_String_ಗಮ್ಯ_UTF8_W(ದತ್ತಾಂಶ->ICMFileName);
    ಆದರೆ (filename_utf8) {
        icc_Profile_ದತ್ತಾಂಶ = SDL_ತುಂಬು_File(filename_utf8, ಗಾತ್ರ_2);
        ಆದರೆ (!icc_Profile_ದತ್ತಾಂಶ) {
            SDL_ಗಣ_Error("Could not open ICC profile");
        }
        SDL_free(filename_utf8);
    }
    ಹಿಂತಿರುಗಿ icc_Profile_ದತ್ತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_GrabKeyboard(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HMODULE module;

    ಆದರೆ (ದತ್ತಾಂಶ->keyboard_hook) {
        ಹಿಂತಿರುಗಿ;
    }

    /* SetWindowsHookEx() needs to know which module contains the hook we
       want to install. This is complicated by the fact that SDL can be
       linked statically or dynamically. Fortunately XP and later provide
       this nice API that will go through the loaded modules and find the
       one containing our code.
    */
    ಆದರೆ (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT | GET_MODULE_HANDLE_EX_FLAG_FROM_ವಿಳಾಸ,
                           (LPTSTR)WIN_KeyboardHookProc,
                           &module)) {
        ಹಿಂತಿರುಗಿ;
    }

    // Capture a snapshot of the current keyboard state before the hook
    ಆದರೆ (!GetKeyboardState(ದತ್ತಾಂಶ->videodata->pre_hook_ಕೀಲಿ_state)) {
        ಹಿಂತಿರುಗಿ;
    }

    /* To grab the keyboard, we have to install a low-level keyboard hook to
       intercept keys that would normally be captured by the OS. Intercepting
       all key events on the system is rather invasive, but it's what Microsoft
       actually documents that you do to capture these.
    */
    ದತ್ತಾಂಶ->keyboard_hook = ಗಣ_Windows_Hook_Ex(WH_KEYBOARD_LL, WIN_KeyboardHookProc, module, 0);
}

ಶೂನ್ಯ WIN_UngrabKeyboard(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->keyboard_hook) {
        UnhookWindowsHookEx(ದತ್ತಾಂಶ->keyboard_hook);
        ದತ್ತಾಂಶ->keyboard_hook = ಖಾಲಿ;
    }
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    WIN_UpdateClipCursor(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    WIN_UpdateClipCursor(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    ಆದರೆ (grabbed) {
        WIN_GrabKeyboard(ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        WIN_UngrabKeyboard(ಕಿಟಕಿ);
    }

    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಶೂನ್ಯ WIN_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    Cleanup_ಕಿಟಕಿ_ದತ್ತಾಂಶ(_this, ಕಿಟಕಿ);
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
ಶೂನ್ಯ WIN_On_ಕಿಟಕಿ_Enter(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!ದತ್ತಾಂಶ || !ದತ್ತಾಂಶ->hwnd) {
        // The window wasn't fully initialized
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ) {
        WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(ಕಿಟಕಿ, ದತ್ತಾಂಶ->copybits_flag | SWP_NOSIZE | SWP_NOACTIVATE, SDL_WINDOWRECT_CURRENT);
    }
}

ಸ್ಥಿರ BOOL GetClientScreenRect(HWND hwnd, RECT *rect)
{
    ಹಿಂತಿರುಗಿ GetClientRect(hwnd, rect) &&             // RECT( left , top , right , bottom )
           Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT)rect) &&   // POINT( left , top )
           Client_ಗಮ್ಯ_Screen(hwnd, (LPPOINT)rect + 1); // POINT( right , bottom )
}

ಶೂನ್ಯ WIN_Unclip_Cursor_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ) {
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    RECT rect;
    ಆದರೆ (GetClipCursor(&rect) && SDL_memcmp(&rect, &ದತ್ತಾಂಶ->cursor_clipped_rect, ಗಾತ್ರ(rect)) == 0) {
        ClipCursor(ಖಾಲಿ);
        SDL_zero(ದತ್ತಾಂಶ->cursor_clipped_rect);
    }
}

ಶೂನ್ಯ WIN_UpdateClipCursor(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Video_ದತ್ತಾಂಶ *videodata = ದತ್ತಾಂಶ->videodata;
    ಆದರೆ (ದತ್ತಾಂಶ->ಒಳ_title_click || ದತ್ತಾಂಶ->focus_click_pending || ದತ್ತಾಂಶ->postpone_clipcursor) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Rect mouse_rect = ಕಿಟಕಿ->mouse_rect;
    bool win_mouse_rect = (mouse_rect.w > 0 && mouse_rect.h > 0);
    bool win_have_focus = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS);
    bool win_is_grabbed = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED);
    bool win_ಒಳ_relmode = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ);
    bool cursor_confine = win_ಒಳ_relmode || win_is_grabbed || win_mouse_rect;

    // This is verbatim translation of the old logic,
    // but I don't quite get what it's trying to do.
    // A clean-room implementation according to MSDN
    // documentation of GetClipCursor is provided in
    // a commented-out block below.
    ಆದರೆ (!win_have_focus || !cursor_confine) {
        SDL_VideoDevice *videodevice = SDL_GetVideoDevice();
        RECT current;
        ಆದರೆ (!GetClipCursor(&current)) {
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (videodevice && (
            current.ಎಡ != videodevice->desktop_bounds.x ||
            current.ತುದಿ  != videodevice->desktop_bounds.y
        )) {
            ಬಿಂದು_2 ಮೊದಲ, ಎರಡನೇ;
            ಮೊದಲ.x  = current.ಎಡ;
            ಮೊದಲ.y  = current.ತುದಿ;
            ಎರಡನೇ.x = current.ಬಲ  - 1;
            ಎರಡನೇ.y = current.bottom - 1;
            ಆದರೆ (!Pt_ಒಳ_Rect(&ದತ್ತಾಂಶ->cursor_clipped_rect, ಮೊದಲ) ||
                !Pt_ಒಳ_Rect(&ದತ್ತಾಂಶ->cursor_clipped_rect, ಎರಡನೇ)) {
                ಹಿಂತಿರುಗಿ;
            }
        }
        ClipCursor(ಖಾಲಿ);
        SDL_zero(ದತ್ತಾಂಶ->cursor_clipped_rect);
        ಹಿಂತಿರುಗಿ;
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
    bool ಬೀಗ_ಗಮ್ಯ_ctr = (mouse->relative_ಬಹುಲಕ && mouse->relative_ಬಹುಲಕ_center);

    RECT client;
    ಆದರೆ (!GetClientScreenRect(ದತ್ತಾಂಶ->hwnd, &client)) {
        ಹಿಂತಿರುಗಿ;
    }

    RECT ಗುರಿ = client;
    ಆದರೆ (ಬೀಗ_ಗಮ್ಯ_ctr) {
        LONG cx = (client.ಎಡ + client.ಬಲ ) / 2;
        LONG cy = (client.ತುದಿ  + client.bottom) / 2;
        ಗುರಿ = ದತ್ತಾಂಶ->cursor_ctrlock_rect;
        ಗುರಿ.ಎಡ   += cx;
        ಗುರಿ.ಬಲ  += cx;
        ಗುರಿ.ತುದಿ    += cy;
        ಗುರಿ.bottom += cy;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (win_mouse_rect) {
        RECT custom, overlap;
        custom.ಎಡ   = client.ಎಡ + mouse_rect.x;
        custom.ತುದಿ    = client.ತುದಿ  + mouse_rect.y;
        custom.ಬಲ  = client.ಎಡ + mouse_rect.x + mouse_rect.w;
        custom.bottom = client.ತುದಿ  + mouse_rect.y + mouse_rect.h;
        ಆದರೆ (IntersectRect(&overlap, &client, &custom)) {
            ಗುರಿ = overlap;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!win_is_grabbed) {
            WIN_Unclip_Cursor_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
            ಹಿಂತಿರುಗಿ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (videodata->dpi_unaware_context_declared) {
        /* Windows has a rounding bug when a DPI unaware context and fractional scale value
         * are used that will cause the cursor coordinates to jitter across a confining edge
         * while dragging along it, which can cause spurious pointer enter/leave events when the
         * clip rect matches the window bounds. Move the sides of the clip rect in by 1 in each
         * dimension to prevent rapid focus switching when the cursor is at the window edge.
         *
         * NOTE: Remove or bypass this if Microsoft ever fixes the issue.
         */

        // Temporarily set the thread to per-monitor awareness v2 to get the display DPI.
        ಆದರೆ (videodata->ಗಣ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2)) {
            HMONITOR hmon = Monitor_From_ಕಿಟಕಿ(ದತ್ತಾಂಶ->hwnd, MONITOR_DEFAULTTONEAREST);
            ಆದರೆ (hmon) {
                UINT hdpi_uint, vdpi_uint;
                ಆದರೆ (videodata->GetDpiForMonitor(hmon, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
                    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ scale = (ದಶಮಾಂಶ)hdpi_uint / (ದಶಮಾಂಶ)USER_DEFAULT_SCREEN_DPI;
                    ಆದರೆ (scale != SDL_floorf(scale)) {
                        ಆದರೆ (ಗುರಿ.ಎಡ < ಗುರಿ.ಬಲ) {
                            ಗುರಿ.ಎಡ += 1;
                        }
                        ಆದರೆ (ಗುರಿ.ಬಲ > ಗುರಿ.ಎಡ) {
                            ಗುರಿ.ಬಲ -= 1;
                        }
                        ಆದರೆ (ಗುರಿ.ತುದಿ < ಗುರಿ.bottom) {
                            ಗುರಿ.ತುದಿ += 1;
                        }
                        ಆದರೆ (ಗುರಿ.bottom > ಗುರಿ.ತುದಿ) {
                            ಗುರಿ.bottom -= 1;
                        }
                    }
                }
            }
            videodata->ಗಣ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_UNAWARE);
        }
    }

    ಆದರೆ (GetClipCursor(&client) &&
        0 != SDL_memcmp(&ಗುರಿ, &client, ಗಾತ್ರ(client)) &&
        ClipCursor(&ಗುರಿ)) {
        ದತ್ತಾಂಶ->cursor_clipped_rect = ಗುರಿ; // ClipCursor may fail if rect beyond screen
    }
}

bool WIN_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled)
{
    ಹಿಂತಿರುಗಿ true; // just succeed, the real work is done elsewhere.
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity)
{
#ಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)
    ಹಿಂತಿರುಗಿ false;
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    ಸ್ಥಿರಾಂಕ LONG style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);

    ಆದರೆ (opacity == 1.0f) {
        // want it fully opaque, just mark it unlayered if necessary.
        ಆದರೆ (style & WS_EX_LAYERED) {
            ಆದರೆ (ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_LAYERED) == 0) {
                ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetWindowLong()");
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ BYTE alpha = (BYTE)((ಪೂರ್ಣಾಂಕ)(opacity * 255.0f));
        // want it transparent, mark it layered if necessary.
        ಆದರೆ (!(style & WS_EX_LAYERED)) {
            ಆದರೆ (ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED) == 0) {
                ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetWindowLong()");
            }
        }

        ಆದರೆ (ಗಣ_Layered_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(hwnd, 0, alpha, LWA_ALPHA) == 0) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetLayeredWindowAttributes()");
        }
    }

    ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
}

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDLGetClipboardFormatName(UINT cf, ಅಕ್ಷರ *ಪಠ್ಯ, ಪೂರ್ಣಾಂಕ len)
{
    ಆಯ್ಕೆ (cf) {
    ಸ್ಥಿತಿ CF_ಪಠ್ಯ:
        ಹಿಂತಿರುಗಿ "CF_TEXT";
    ಸ್ಥಿತಿ CF_BITMAP:
        ಹಿಂತಿರುಗಿ "CF_BITMAP";
    ಸ್ಥಿತಿ CF_METAFILEPICT:
        ಹಿಂತಿರುಗಿ "CF_METAFILEPICT";
    ಸ್ಥಿತಿ CF_SYLK:
        ಹಿಂತಿರುಗಿ "CF_SYLK";
    ಸ್ಥಿತಿ CF_DIF:
        ಹಿಂತಿರುಗಿ "CF_DIF";
    ಸ್ಥಿತಿ CF_TIFF:
        ಹಿಂತಿರುಗಿ "CF_TIFF";
    ಸ್ಥಿತಿ CF_OEMTEXT:
        ಹಿಂತಿರುಗಿ "CF_OEMTEXT";
    ಸ್ಥಿತಿ CF_DIB:
        ಹಿಂತಿರುಗಿ "CF_DIB";
    ಸ್ಥಿತಿ CF_PALETTE:
        ಹಿಂತಿರುಗಿ "CF_PALETTE";
    ಸ್ಥಿತಿ CF_PENDATA:
        ಹಿಂತಿರುಗಿ "CF_PENDATA";
    ಸ್ಥಿತಿ CF_RIFF:
        ಹಿಂತಿರುಗಿ "CF_RIFF";
    ಸ್ಥಿತಿ CF_WAVE:
        ಹಿಂತಿರುಗಿ "CF_WAVE";
    ಸ್ಥಿತಿ CF_UNICODETEXT:
        ಹಿಂತಿರುಗಿ "CF_UNICODETEXT";
    ಸ್ಥಿತಿ CF_ENHMETAFILE:
        ಹಿಂತಿರುಗಿ "CF_ENHMETAFILE";
    ಸ್ಥಿತಿ CF_HDROP:
        ಹಿಂತಿರುಗಿ "CF_HDROP";
    ಸ್ಥಿತಿ CF_LOCALE:
        ಹಿಂತಿರುಗಿ "CF_LOCALE";
    ಸ್ಥಿತಿ CF_DIBV5:
        ಹಿಂತಿರುಗಿ "CF_DIBV5";
    ಸ್ಥಿತಿ CF_OWNERDISPLAY:
        ಹಿಂತಿರುಗಿ "CF_OWNERDISPLAY";
    ಸ್ಥಿತಿ CF_DSPTEXT:
        ಹಿಂತಿರುಗಿ "CF_DSPTEXT";
    ಸ್ಥಿತಿ CF_DSPBITMAP:
        ಹಿಂತಿರುಗಿ "CF_DSPBITMAP";
    ಸ್ಥಿತಿ CF_DSPMETAFILEPICT:
        ಹಿಂತಿರುಗಿ "CF_DSPMETAFILEPICT";
    ಸ್ಥಿತಿ CF_DSPENHMETAFILE:
        ಹಿಂತಿರುಗಿ "CF_DSPENHMETAFILE";
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಆದರೆ (GetClipboardFormatNameA(cf, ಪಠ್ಯ, len)) {
            ಹಿಂತಿರುಗಿ ಪಠ್ಯ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }
}

ಸ್ಥಿರ STDMETHODIMP_(ULONG) SDLDrop_ಗುರಿ_ಕೂಡಿಸು_Ref(SDLDrop_ಗುರಿ *ಗುರಿ)
{
    ಹಿಂತಿರುಗಿ ++ಗುರಿ->refcount;
}

ಸ್ಥಿರ STDMETHODIMP_(ULONG) SDLDrop_ಗುರಿ_Release(SDLDrop_ಗುರಿ *ಗುರಿ)
{
    --ಗುರಿ->refcount;
    ಆದರೆ (ಗುರಿ->refcount == 0) {
        SDL_free(ಗುರಿ);
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ ಗುರಿ->refcount;
}

ಸ್ಥಿರ STDMETHODIMP SDLDrop_ಗುರಿ_Query_Interface(SDLDrop_ಗುರಿ *ಗುರಿ, REFIID riid, PVOID *ppv)
{
    ಆದರೆ (ppv == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ E_INVALIDARG;
    }

    *ppv = ಖಾಲಿ;
    ಆದರೆ (WIN_IsEqualIID(riid, &IID_IUnknown) ||
        WIN_IsEqualIID(riid, &IID_IDrop_ಗುರಿ)) {
        *ppv = (ಶೂನ್ಯ *)ಗುರಿ;
    }
    ಆದರೆ (*ppv) {
        SDLDrop_ಗುರಿ_ಕೂಡಿಸು_Ref(ಗುರಿ);
        ಹಿಂತಿರುಗಿ S_OK;
    }
    ಹಿಂತಿರುಗಿ E_NOINTERFACE;
}

ಸ್ಥಿರ STDMETHODIMP SDLDrop_ಗುರಿ_Drag_Enter(SDLDrop_ಗುರಿ *ಗುರಿ,
                                            IDataObject *p_ದತ್ತಾಂಶ_Object, DWORD grf_ಕೀಲಿ_State,
                                            POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ಬಿಂದು_2 pnt = { pt.x, pt.y };
    ಆದರೆ (Screen_ಗಮ್ಯ_Client(ಗುರಿ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ಗುರಿ->ಕಿಟಕಿ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ಗುರಿ->ಕಿಟಕಿ, pnt.x, pnt.y);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragEnter at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ಹಿಂತಿರುಗಿ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDrop_ಗುರಿ_Drag_Over(SDLDrop_ಗುರಿ *ಗುರಿ,
                                           DWORD grf_ಕೀಲಿ_State,
                                           POINTL pt, DWORD *pdwEffect)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y);
    *pdwEffect = DROPEFFECT_COPY;
    ಬಿಂದು_2 pnt = { pt.x, pt.y };
    ಆದರೆ (Screen_ಗಮ್ಯ_Client(ಗುರಿ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ಗುರಿ->ಕಿಟಕಿ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ಗುರಿ->ಕಿಟಕಿ, pnt.x, pnt.y);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In DragOver at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }
    ಹಿಂತಿರುಗಿ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDrop_ಗುರಿ_Drag_Leave(SDLDrop_ಗುರಿ *ಗುರಿ)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In DragLeave");
    SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ S_OK;
}

ಸ್ಥಿರ STDMETHODIMP SDLDrop_ಗುರಿ_Drop(SDLDrop_ಗುರಿ *ಗುರಿ,
                                       IDataObject *p_ದತ್ತಾಂಶ_Object, DWORD grf_ಕೀಲಿ_State,
                                       POINTL pt, DWORD *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    ಬಿಂದು_2 pnt = { pt.x, pt.y };
    ಆದರೆ (Screen_ಗಮ್ಯ_Client(ಗುರಿ->hwnd, &pnt)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => window %u at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG, pt.x, pt.y, ಗುರಿ->ಕಿಟಕಿ->id, pnt.x, pnt.y);
        SDL_SendDropPosition(ಗುರಿ->ಕಿಟಕಿ, pnt.x, pnt.y);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop at %" SDL_PRIdSLONG ", %" SDL_PRIdSLONG " => nil, nil", pt.x, pt.y);
    }

    {
        IEnumFORMATETC *pEnumFormatEtc;
        HRESULT hres;
        hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->EnumFormatEtc(p_ದತ್ತಾಂಶ_Object, DATADIR_GET, &pEnumFormatEtc);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Drop for EnumFormatEtc, HRESULT is %08" SDL_PRIxSLONG, hres);
        ಆದರೆ (hres == S_OK) {
            FORMATETC fetc;
            ಆಗ (pEnumFormatEtc->lpVtbl->ಮುಂದಿನ_3(pEnumFormatEtc, 1, &fetc, ಖಾಲಿ) == S_OK) {
                ಅಕ್ಷರ name[257] = { 0 };
                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cfnm = SDLGetClipboardFormatName(fetc.cfFormat, name, 256);
                ಆದರೆ (cfnm) {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                 ". In Drop, Supported format is %08x, '%s'", fetc.cfFormat, cfnm);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                 ". In Drop, Supported format is %08x, Predefined", fetc.cfFormat);
                }
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ಗುರಿ->format_file;
        fetc.ptd = ಖಾಲಿ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format_mime = "text/uri-list";
        ಆದರೆ (SUCCEEDED(p_ದತ್ತಾಂಶ_Object->lpVtbl->Query_Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಆದರೆ (SUCCEEDED(hres)) {
                ಸ್ಥಿರಾಂಕ size_t bsize = Global_ಗಾತ್ರ(med.hGlobal);
                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2 = (ಶೂನ್ಯ *)Global_ಬೀಗ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, ಬಫರ್_2);
                ಆದರೆ (ಬಫರ್_2) {
                    ಅಕ್ಷರ *ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(bsize + ಗಾತ್ರ(Uint32));
                    SDL_memcpy((Uint8 *)ಪಠ್ಯ, ಬಫರ್_2, bsize);
                    SDL_memset((Uint8 *)ಪಠ್ಯ + bsize, 0, ಗಾತ್ರ(Uint32));
                    ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                    ಅಕ್ಷರ *token = SDL_strtok_r(ಪಠ್ಯ, "\r\n", &saveptr);
                    ಆಗ (token != ಖಾಲಿ) {
                        ಆದರೆ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)SDL_strlen(token), (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, token);
                            SDL_SendDropFile(ಗುರಿ->ಕಿಟಕಿ, ಖಾಲಿ, token);
                        }
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    SDL_free(ಪಠ್ಯ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = ಗುರಿ->format_ಪಠ್ಯ;
        fetc.ptd = ಖಾಲಿ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format_mime = "text/plain;charset=utf-8";
        ಆದರೆ (SUCCEEDED(p_ದತ್ತಾಂಶ_Object->lpVtbl->Query_Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಆದರೆ (SUCCEEDED(hres)) {
                ಸ್ಥಿರಾಂಕ size_t bsize = Global_ಗಾತ್ರ(med.hGlobal);
                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2 = (ಶೂನ್ಯ *)Global_ಬೀಗ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, ಬಫರ್_2);
                ಆದರೆ (ಬಫರ್_2) {
                    ಅಕ್ಷರ *ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(bsize + ಗಾತ್ರ(Uint32));
                    SDL_memcpy((Uint8 *)ಪಠ್ಯ, ಬಫರ್_2, bsize);
                    SDL_memset((Uint8 *)ಪಠ್ಯ + bsize, 0, ಗಾತ್ರ(Uint32));
                    ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                    ಅಕ್ಷರ *token = SDL_strtok_r(ಪಠ್ಯ, "\r\n", &saveptr);
                    ಆಗ (token != ಖಾಲಿ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)SDL_strlen(token), (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, token);
                        SDL_Send_Drop_ಪಠ್ಯ(ಗುರಿ->ಕಿಟಕಿ, (ಅಕ್ಷರ *)token);
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    SDL_free(ಪಠ್ಯ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_UNICODETEXT;
        fetc.ptd = ಖಾಲಿ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format_mime = "CF_UNICODETEXT";
        ಆದರೆ (SUCCEEDED(p_ದತ್ತಾಂಶ_Object->lpVtbl->Query_Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಆದರೆ (SUCCEEDED(hres)) {
                ಸ್ಥಿರಾಂಕ size_t bsize = Global_ಗಾತ್ರ(med.hGlobal);
                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2 = (ಶೂನ್ಯ *)Global_ಬೀಗ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, ಬಫರ್_2);
                ಆದರೆ (ಬಫರ್_2) {
                    ಬಫರ್_2 = WIN_String_ಗಮ್ಯ_UTF8_W((ಸ್ಥಿರಾಂಕ wchar_t *)ಬಫರ್_2);
                    ಆದರೆ (ಬಫರ್_2) {
                        ಸ್ಥಿರಾಂಕ size_t lbuffer = SDL_strlen((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ಬಫರ್_2);
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text for StringToUTF8, format %08x '%s', memory (%lu) %p",
                                     fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)lbuffer, ಬಫರ್_2);
                        ಅಕ್ಷರ *ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(lbuffer + ಗಾತ್ರ(Uint32));
                        SDL_memcpy((Uint8 *)ಪಠ್ಯ, ಬಫರ್_2, lbuffer);
                        SDL_memset((Uint8 *)ಪಠ್ಯ + lbuffer, 0, ಗಾತ್ರ(Uint32));
                        ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                        ಅಕ್ಷರ *token = SDL_strtok_r(ಪಠ್ಯ, "\r\n", &saveptr);
                        ಆಗ (token != ಖಾಲಿ) {
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop Text, text (%lu of %lu) '%s'",
                                         (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)SDL_strlen(token), (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)lbuffer, token);
                            SDL_Send_Drop_ಪಠ್ಯ(ಗುರಿ->ಕಿಟಕಿ, (ಅಕ್ಷರ *)token);
                            token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                        }
                        SDL_free(ಪಠ್ಯ);
                        SDL_free((ಶೂನ್ಯ *)ಬಫರ್_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_ಪಠ್ಯ;
        fetc.ptd = ಖಾಲಿ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format_mime = "CF_TEXT";
        ಆದರೆ (SUCCEEDED(p_ದತ್ತಾಂಶ_Object->lpVtbl->Query_Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop Text for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಆದರೆ (SUCCEEDED(hres)) {
                ಸ್ಥಿರಾಂಕ size_t bsize = Global_ಗಾತ್ರ(med.hGlobal);
                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2 = (ಶೂನ್ಯ *)Global_ಬೀಗ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop Text for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, ಬಫರ್_2);
                ಆದರೆ (ಬಫರ್_2) {
                    ಅಕ್ಷರ *ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(bsize + ಗಾತ್ರ(Uint32));
                    SDL_memcpy((Uint8 *)ಪಠ್ಯ, ಬಫರ್_2, bsize);
                    SDL_memset((Uint8 *)ಪಠ್ಯ + bsize, 0, ಗಾತ್ರ(Uint32));
                    ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                    ಅಕ್ಷರ *token = SDL_strtok_r(ಪಠ್ಯ, "\r\n", &saveptr);
                    ಆಗ (token != ಖಾಲಿ) {
                        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                     ". In Drop Text, text (%lu of %lu) '%s'",
                                     (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)SDL_strlen(token), (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, token);
                        SDL_Send_Drop_ಪಠ್ಯ(ಗುರಿ->ಕಿಟಕಿ, (ಅಕ್ಷರ *)token);
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    SDL_free(ಪಠ್ಯ);
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ S_OK;
            }
        }
    }

    {
        FORMATETC fetc;
        fetc.cfFormat = CF_HDROP;
        fetc.ptd = ಖಾಲಿ;
        fetc.dwAspect = DVASPECT_CONTENT;
        fetc.lindex = -1;
        fetc.tymed = TYMED_HGLOBAL;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format_mime = "CF_HDROP";
        ಆದರೆ (SUCCEEDED(p_ದತ್ತಾಂಶ_Object->lpVtbl->Query_Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc))) {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for QueryGetData, format %08x '%s', success",
                         fetc.cfFormat, format_mime);
            STGMEDIUM med;
            HRESULT hres = p_ದತ್ತಾಂಶ_Object->lpVtbl->Get_ದತ್ತಾಂಶ(p_ದತ್ತಾಂಶ_Object, &fetc, &med);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Drop File for      GetData, format %08x '%s', HRESULT is %08" SDL_PRIxSLONG,
                         fetc.cfFormat, format_mime, hres);
            ಆದರೆ (SUCCEEDED(hres)) {
                ಸ್ಥಿರಾಂಕ size_t bsize = Global_ಗಾತ್ರ(med.hGlobal);
                HDROP drop = (HDROP)Global_ಬೀಗ(med.hGlobal);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Drop File for   GlobalLock, format %08x '%s', memory (%lu) %p",
                             fetc.cfFormat, format_mime, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, drop);
                UINT ಎಣಿಕೆ_2 = DragQueryFile(drop, 0xFFFFFFFF, ಖಾಲಿ, 0);
                ಗಾಗಿ (UINT i = 0; i < ಎಣಿಕೆ_2; ++i) {
                    UINT ಗಾತ್ರ_2 = DragQueryFile(drop, i, ಖಾಲಿ, 0) + 1;
                    LPTSTR ಬಫರ್_2 = (LPTSTR)SDL_malloc(ಗಾತ್ರ_2 * ಗಾತ್ರ(TCHAR));
                    ಆದರೆ (ಬಫರ್_2) {
                        ಆದರೆ (DragQueryFile(drop, i, ಬಫರ್_2, ಗಾತ್ರ_2)) {
                            ಅಕ್ಷರ *file = WIN_String_ಗಮ್ಯ_UTF8(ಬಫರ್_2);
                            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                                         ". In Drop File, file (%lu of %lu) '%s'",
                                         (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)SDL_strlen(file), (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)bsize, file);
                            SDL_SendDropFile(ಗುರಿ->ಕಿಟಕಿ, ಖಾಲಿ, file);
                            SDL_free(file);
                        }
                        SDL_free(ಬಫರ್_2);
                    }
                }
                GlobalUnlock(med.hGlobal);
                ReleaseStgMedium(&med);
                SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ S_OK;
            }
        }
    }

    SDL_SendDropComplete(ಗುರಿ->ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ S_OK;
}

ಸ್ಥಿರ ಶೂನ್ಯ *vt_Drop_ಗುರಿ[] = {
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Query_Interface),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_ಕೂಡಿಸು_Ref),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Release),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Drag_Enter),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Drag_Over),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Drag_Leave),
    (ಶೂನ್ಯ *)(SDLDrop_ಗುರಿ_Drop)
};

ಶೂನ್ಯ WIN_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->videodata->oleinitialized) {
        ಆದರೆ (accept && !ದತ್ತಾಂಶ->drop_ಗುರಿ) {
            SDLDrop_ಗುರಿ *drop_ಗುರಿ = (SDLDrop_ಗುರಿ *)SDL_calloc(1, ಗಾತ್ರ(SDLDrop_ಗುರಿ));
            ಆದರೆ (drop_ಗುರಿ != ಖಾಲಿ) {
                drop_ಗುರಿ->lpVtbl = vt_Drop_ಗುರಿ;
                drop_ಗುರಿ->ಕಿಟಕಿ = ಕಿಟಕಿ;
                drop_ಗುರಿ->hwnd = ದತ್ತಾಂಶ->hwnd;
                drop_ಗುರಿ->format_file = ರಿಜಿಸ್ಟರ್_Clipboard_Format_W(L"text/uri-list");
                drop_ಗುರಿ->format_ಪಠ್ಯ = ರಿಜಿಸ್ಟರ್_Clipboard_Format_W(L"text/plain;charset=utf-8");
                ದತ್ತಾಂಶ->drop_ಗುರಿ = drop_ಗುರಿ;
                SDLDrop_ಗುರಿ_ಕೂಡಿಸು_Ref(drop_ಗುರಿ);
                ರಿಜಿಸ್ಟರ್_Drag_Drop(ದತ್ತಾಂಶ->hwnd, (LPDROPTARGET)drop_ಗುರಿ);
                SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                             ". In Accept Drag and Drop, window %u, enabled Full OLE IDropTarget",
                             ಕಿಟಕಿ->id);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!accept && ದತ್ತಾಂಶ->drop_ಗುರಿ) {
            RevokeDragDrop(ದತ್ತಾಂಶ->hwnd);
            SDLDrop_ಗುರಿ_Release(ದತ್ತಾಂಶ->drop_ಗುರಿ);
            ದತ್ತಾಂಶ->drop_ಗುರಿ = ಖಾಲಿ;
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In Accept Drag and Drop, window %u, disabled Full OLE IDropTarget",
                         ಕಿಟಕಿ->id);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        DragAcceptFiles(ದತ್ತಾಂಶ->hwnd, accept ? TRUE : FALSE);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In Accept Drag and Drop, window %u, %s Fallback WM_DROPFILES",
                     ಕಿಟಕಿ->id, (accept ? "enabled" : "disabled"));
    }
}

bool WIN_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation)
{
    FLASHWINFO desc;

    SDL_zero(desc);
    desc.cb_ಗಾತ್ರ = ಗಾತ್ರ(desc);
    desc.hwnd = ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    ಆಯ್ಕೆ (operation) {
    ಸ್ಥಿತಿ SDL_FLASH_CANCEL:
        desc.dwFlags = FLASHW_STOP;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLASH_BRIEFLY:
        desc.dwFlags = FLASHW_TRAY;
        desc.u_ಎಣಿಕೆ = 1;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLASH_UNTIL_FOCUSED:
        desc.dwFlags = (FLASHW_TRAY | FLASHW_TIMERNOFG);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    Flash_ಕಿಟಕಿ_Ex(&desc);

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಆದರೆ (!ದತ್ತಾಂಶ->taskbar_button_created) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (ಕಿಟಕಿ->ಪ್ರಗತಿ_state == SDL_ಪ್ರಗತಿ_STATE_NONE && !ದತ್ತಾಂಶ->videodata->taskbar_list) {
        ಹಿಂತಿರುಗಿ true;
    }

    ITaskbarList3 *taskbar_list = GetTaskbarList(ಕಿಟಕಿ);
    ಆದರೆ (!taskbar_list) {
        ಹಿಂತಿರುಗಿ false;
    }

    TBPFLAG tbpFlags;
    ಆಯ್ಕೆ (ಕಿಟಕಿ->ಪ್ರಗತಿ_state) {
    ಸ್ಥಿತಿ SDL_ಪ್ರಗತಿ_STATE_NONE:
        tbpFlags = TBPF_NOPROGRESS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ಪ್ರಗತಿ_STATE_INDETERMINATE:
        tbpFlags = TBPF_INDETERMINATE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ಪ್ರಗತಿ_STATE_ಸಾಮಾನ್ಯ:
        tbpFlags = TBPF_ಸಾಮಾನ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ಪ್ರಗತಿ_STATE_PAUSED:
        tbpFlags = TBPF_PAUSED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ಪ್ರಗತಿ_STATE_ERROR:
        tbpFlags = TBPF_ERROR;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Parameter 'state' is not supported");
    }

    HRESULT ret = taskbar_list->lpVtbl->ಗಣ_ಪ್ರಗತಿ_State(taskbar_list, ದತ್ತಾಂಶ->hwnd, tbpFlags);
    ಆದರೆ (FAILED(ret)) {
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error_From_HRESULT("ITaskbarList3::SetProgressState()", ret);
    }

    ಆದರೆ (ಕಿಟಕಿ->ಪ್ರಗತಿ_state >= SDL_ಪ್ರಗತಿ_STATE_ಸಾಮಾನ್ಯ) {
        ret = taskbar_list->lpVtbl->ಗಣ_ಪ್ರಗತಿ_ಮೌಲ್ಯ(taskbar_list, ದತ್ತಾಂಶ->hwnd, (ULONGLONG)(ಕಿಟಕಿ->ಪ್ರಗತಿ_ಮೌಲ್ಯ * 10000.f), 10000);
        ಆದರೆ (FAILED(ret)) {
            ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error_From_HRESULT("ITaskbarList3::SetProgressValue()", ret);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಬಿಂದು_2 pt;

    pt.x = x;
    pt.y = y;
    Client_ಗಮ್ಯ_Screen(ದತ್ತಾಂಶ->hwnd, &pt);
    Send_ಸಂದೇಶ(ದತ್ತಾಂಶ->hwnd, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable)
{
    ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        HWND hwnd = ದತ್ತಾಂಶ->hwnd;
        ಸ್ಥಿರಾಂಕ LONG style = Get_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE);

        SDL_assert(style != 0);

        ಆದರೆ (focusable) {
            ಆದರೆ (style & WS_EX_NOACTIVATE) {
                ಆದರೆ (ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE, style & ~WS_EX_NOACTIVATE) == 0) {
                    ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetWindowLong()");
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (!(style & WS_EX_NOACTIVATE)) {
                ಆದರೆ (ಗಣ_ಕಿಟಕಿ_Long(hwnd, GWL_EXSTYLE, style | WS_EX_NOACTIVATE) == 0) {
                    ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetWindowLong()");
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            ಆದರೆ (!focusable && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
                SDL_ಕಿಟಕಿ *new_focus;
                ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(ಕಿಟಕಿ, &new_focus);
                WIN_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (focusable) {
                ಆದರೆ (SDL_ShouldFocusPopup(ಕಿಟಕಿ)) {
                    WIN_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
                }
            }
        }

        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

bool WIN_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಮಗು_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ LONG_PTR ಪೋಷಕ_hwnd = (LONG_PTR)(ಪೋಷಕ ? ಪೋಷಕ->ಆಂತರಿಕ->hwnd : ಖಾಲಿ);
    ಸ್ಥಿರಾಂಕ DWORD style = Get_ಕಿಟಕಿ_Long(ಮಗು_ದತ್ತಾಂಶ->hwnd, GWL_STYLE);

    ಆದರೆ (!(style & WS_ಮಗು)) {
        /* Despite the name, this changes the *owner* of a toplevel window, not
         * the parent of a child window.
         *
         * https://devblogs.microsoft.com/oldnewthing/20100315-00/?p=14613
         */
        ಗಣ_ಕಿಟಕಿ_Long_Ptr(ಮಗು_ದತ್ತಾಂಶ->hwnd, GWLP_HWNDPARENT, ಪೋಷಕ_hwnd);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಣ_ಪೋಷಕ(ಮಗು_ದತ್ತಾಂಶ->hwnd, (HWND)ಪೋಷಕ_hwnd);
    }
#ಆದರೆ_ಅಂತ್ಯ /*!defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)*/

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal)
{
#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)
    ಸ್ಥಿರಾಂಕ HWND ಪೋಷಕ_hwnd = ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->hwnd;

    ಆದರೆ (modal) {
        // Disable the parent window.
        Enable_ಕಿಟಕಿ(ಪೋಷಕ_hwnd, FALSE);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
        // Re-enable the parent window
        Enable_ಕಿಟಕಿ(ಪೋಷಕ_hwnd, TRUE);
    }
#ಆದರೆ_ಅಂತ್ಯ // !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS
