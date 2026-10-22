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

#ಯದಿ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xfixes.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

ಸ್ಥಿರ bool xfixes_initialized = true;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ xfixes_selection_notify_event = 0;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ query_xfixes_version(Display *display, ಪೂರ್ಣಾಙ್ಕ major, ಪೂರ್ಣಾಙ್ಕ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixesQueryVersion(display, &major, &minor);
    ಪ್ರತ್ಯಾಗಮ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xfixes_version_atleast(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ version, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantmajor, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantminor)
{
    ಪ್ರತ್ಯಾಗಮ version >= ((wantmajor * 1000) + wantminor);
}

ಶೂನ್ಯ X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    ಪೂರ್ಣಾಙ್ಕ version = 0;
    ಪೂರ್ಣಾಙ್ಕ event, error;
    ಪೂರ್ಣಾಙ್ಕ fixes_opcode;

    Atom XA_CLIPBOARD = data->atoms.CLIPBOARD;

    ಯದಿ (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(data->display, "XFIXES", &fixes_opcode, &event, &error)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_ಒಳಹರಿವು(data->display, Default_ಬೇರು_Window(data->display),
            XA_CLIPBOARD, XFixesSetSelectionOwnerNotifyMask);
    X11_XFixes_Select_Selection_ಒಳಹರಿವು(data->display, Default_ಬೇರು_Window(data->display),
            XA_PRIMARY, XFixesSetSelectionOwnerNotifyMask);

    // We need at least 5.0 for barriers.
    version = query_xfixes_version(data->display, 5, 0);
    ಯದಿ (!xfixes_version_atleast(version, 5, 0)) {
        ಪ್ರತ್ಯಾಗಮ; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ xfixes_initialized;
}

ಪೂರ್ಣಾಙ್ಕ X11_GetXFixesSelectionNotifyEvent(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ xfixes_selection_notify_event;
}

bool X11_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಯದಿ (SDL_RectEmpty(&window->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, window, ರಿಕ್ತ, 0);
    } ಅನ್ಯಥಾ {
        ಯದಿ (window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) {
            X11_ConfineCursorWithFlags(_this, window, &window->mouse_rect, 0);
        } ಅನ್ಯಥಾ {
            // Save the state for when we get focus again
            SDL_WindowData *wdata = window->internal;

            SDL_memcpy(&wdata->barrier_rect, &window->mouse_rect, ಪರಿಮಾಣ(wdata->barrier_rect));

            wdata->pointer_barrier_active = true;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rect, ಪೂರ್ಣಾಙ್ಕ flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wdata;

    ಯದಿ (!X11_XfixesIsInitialized()) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    ಯದಿ (data->active_cursor_confined_window) {
        X11_DestroyPointerBarrier(_this, data->active_cursor_confined_window);
    }

    SDL_assert(window != ರಿಕ್ತ);
    wdata = window->internal;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    ಯದಿ (rect) {
        ಪೂರ್ಣಾಙ್ಕ x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_GetWindowPosition(window, &bounds.x, &bounds.y);
        SDL_GetWindowSize(window, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        ಯದಿ ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_GetDisplayForWindow(window), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           BarrierPositiveX,
                                                           0, ರಿಕ್ತ);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, ರಿಕ್ತ);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           BarrierPositiveY,
                                                           0, ರಿಕ್ತ);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, ರಿಕ್ತ);

        X11_XFlush(data->display);

        // Lets remember current active confined window.
        data->active_cursor_confined_window = window;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->pointer_barrier_active = true;
    } ಅನ್ಯಥಾ {
        X11_DestroyPointerBarrier(_this, window);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        ಯದಿ (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->pointer_barrier_active = false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    SDL_VideoData *data = _this->internal;
    ಯದಿ (window) {
        SDL_WindowData *wdata = window->internal;

        ಪ್ರತಿ (i = 0; i < 4; i++) {
            ಯದಿ (wdata->barrier[i] > 0) {
                X11_XFixesDestroyPointerBarrier(data->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(data->display);
    }
    data->active_cursor_confined_window = ರಿಕ್ತ;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
