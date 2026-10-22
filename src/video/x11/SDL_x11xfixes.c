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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xfixes.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

ಸ್ಥಿರ bool xfixes_initialized = true;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ xfixes_selection_notify_event = 0;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ query_xfixes_ಆವೃತ್ತಿ(Display *display, ಪೂರ್ಣಾಂಕ major, ಪೂರ್ಣಾಂಕ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_ಆವೃತ್ತಿ(display, &major, &minor);
    ಹಿಂತಿರುಗಿ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xfixes_ಆವೃತ್ತಿ_atleast(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantmajor, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantminor)
{
    ಹಿಂತಿರುಗಿ ಆವೃತ್ತಿ >= ((wantmajor * 1000) + wantminor);
}

ಶೂನ್ಯ X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ = 0;
    ಪೂರ್ಣಾಂಕ event, error;
    ಪೂರ್ಣಾಂಕ fixes_opcode;

    Atom XA_CLIPBOARD = ದತ್ತಾಂಶ->atoms.CLIPBOARD;

    ಆದರೆ (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(ದತ್ತಾಂಶ->display, "XFIXES", &fixes_opcode, &event, &error)) {
        ಹಿಂತಿರುಗಿ;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_ಒಳಹರಿವು(ದತ್ತಾಂಶ->display, Default_ಬೇರು_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display),
            XA_CLIPBOARD, XFixes_ಗಣ_Selection_Owner_Notify_ಮುಖವಾಡ);
    X11_XFixes_Select_Selection_ಒಳಹರಿವು(ದತ್ತಾಂಶ->display, Default_ಬೇರು_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display),
            XA_PRIMARY, XFixes_ಗಣ_Selection_Owner_Notify_ಮುಖವಾಡ);

    // We need at least 5.0 for barriers.
    ಆವೃತ್ತಿ = query_xfixes_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->display, 5, 0);
    ಆದರೆ (!xfixes_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 5, 0)) {
        ಹಿಂತಿರುಗಿ; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ xfixes_initialized;
}

ಪೂರ್ಣಾಂಕ X11_GetXFixesSelectionNotifyEvent(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ xfixes_selection_notify_event;
}

bool X11_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, ಕಿಟಕಿ, ಖಾಲಿ, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
            X11_ConfineCursorWithFlags(_this, ಕಿಟಕಿ, &ಕಿಟಕಿ->mouse_rect, 0);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Save the state for when we get focus again
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

            SDL_memcpy(&wdata->barrier_rect, &ಕಿಟಕಿ->mouse_rect, ಗಾತ್ರ(wdata->barrier_rect));

            wdata->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ = true;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, ಪೂರ್ಣಾಂಕ flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata;

    ಆದರೆ (!X11_XfixesIsInitialized()) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    ಆದರೆ (ದತ್ತಾಂಶ->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ) {
        X11_Destroy_ಸೂಚಕ_Barrier(_this, ದತ್ತಾಂಶ->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ);
    }

    SDL_assert(ಕಿಟಕಿ != ಖಾಲಿ);
    wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    ಆದರೆ (rect) {
        ಪೂರ್ಣಾಂಕ x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_ಕಿಟಕಿ_Position(ಕಿಟಕಿ, &bounds.x, &bounds.y);
        SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        ಆದರೆ ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixes_Create_ಸೂಚಕ_Barrier(ದತ್ತಾಂಶ->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_ಧನಾತ್ಮಕ_X,
                                                           0, ಖಾಲಿ);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixes_Create_ಸೂಚಕ_Barrier(ದತ್ತಾಂಶ->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, ಖಾಲಿ);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixes_Create_ಸೂಚಕ_Barrier(ದತ್ತಾಂಶ->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_ಧನಾತ್ಮಕ_Y,
                                                           0, ಖಾಲಿ);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixes_Create_ಸೂಚಕ_Barrier(ದತ್ತಾಂಶ->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, ಖಾಲಿ);

        X11_XFlush(ದತ್ತಾಂಶ->display);

        // Lets remember current active confined window.
        ದತ್ತಾಂಶ->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ = ಕಿಟಕಿ;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_Destroy_ಸೂಚಕ_Barrier(_this, ಕಿಟಕಿ);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        ಆದರೆ (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ = false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Destroy_ಸೂಚಕ_Barrier(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಪೂರ್ಣಾಂಕ i;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಆದರೆ (ಕಿಟಕಿ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಗಾಗಿ (i = 0; i < 4; i++) {
            ಆದರೆ (wdata->barrier[i] > 0) {
                X11_XFixes_Destroy_ಸೂಚಕ_Barrier(ದತ್ತಾಂಶ->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(ದತ್ತಾಂಶ->display);
    }
    ದತ್ತಾಂಶ->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ = ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
