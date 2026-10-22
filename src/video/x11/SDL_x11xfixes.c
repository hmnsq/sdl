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

#অন্তর্ভাৱ "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#অন্তর্ভাৱ "SDL_x11video.h"
#অন্তর্ভাৱ "SDL_x11xfixes.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/SDL_touch_c.h"

স্থির bool xfixes_initialized = true;
স্থির পূর্ণাঙ্ক xfixes_selection_notify_event = 0;

স্থির পূর্ণাঙ্ক query_xfixes_version(Display *display, পূর্ণাঙ্ক major, পূর্ণাঙ্ক minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixesQueryVersion(display, &major, &minor);
    ঘূৰাই (major * 1000) + minor;
}

স্থির bool xfixes_version_atleast(ধ্রুৱ পূর্ণাঙ্ক version, ধ্রুৱ পূর্ণাঙ্ক wantmajor, ধ্রুৱ পূর্ণাঙ্ক wantminor)
{
    ঘূৰাই version >= ((wantmajor * 1000) + wantminor);
}

শূন্য X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    পূর্ণাঙ্ক version = 0;
    পূর্ণাঙ্ক event, error;
    পূর্ণাঙ্ক fixes_opcode;

    Atom XA_CLIPBOARD = data->atoms.CLIPBOARD;

    যদি (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(data->display, "XFIXES", &fixes_opcode, &event, &error)) {
        ঘূৰাই;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_প্ৰবেশ(data->display, Default_মূল_Window(data->display),
            XA_CLIPBOARD, XFixesSetSelectionOwnerNotifyMask);
    X11_XFixes_Select_Selection_প্ৰবেশ(data->display, Default_মূল_Window(data->display),
            XA_PRIMARY, XFixesSetSelectionOwnerNotifyMask);

    // We need at least 5.0 for barriers.
    version = query_xfixes_version(data->display, 5, 0);
    যদি (!xfixes_version_atleast(version, 5, 0)) {
        ঘূৰাই; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(শূন্য)
{
    ঘূৰাই xfixes_initialized;
}

পূর্ণাঙ্ক X11_GetXFixesSelectionNotifyEvent(শূন্য)
{
    ঘূৰাই xfixes_selection_notify_event;
}

bool X11_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (SDL_RectEmpty(&window->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, window, রিক্ত, 0);
    } অন্যথা {
        যদি (window->flags & SDL_WINDOW_প্ৰবেশ_FOCUS) {
            X11_ConfineCursorWithFlags(_this, window, &window->mouse_rect, 0);
        } অন্যথা {
            // Save the state for when we get focus again
            SDL_WindowData *wdata = window->internal;

            SDL_memcpy(&wdata->barrier_rect, &window->mouse_rect, পরিমাণ(wdata->barrier_rect));

            wdata->pointer_barrier_active = true;
        }
    }

    ঘূৰাই true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুৱ SDL_Rect *rect, পূর্ণাঙ্ক flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wdata;

    যদি (!X11_XfixesIsInitialized()) {
        ঘূৰাই SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    যদি (data->active_cursor_confined_window) {
        X11_DestroyPointerBarrier(_this, data->active_cursor_confined_window);
    }

    SDL_assert(window != রিক্ত);
    wdata = window->internal;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    যদি (rect) {
        পূর্ণাঙ্ক x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_GetWindowPosition(window, &bounds.x, &bounds.y);
        SDL_GetWindowSize(window, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        যদি ((wdata->barrier_rect.x != rect->x) ||
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
                                                           0, রিক্ত);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, রিক্ত);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           BarrierPositiveY,
                                                           0, রিক্ত);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, রিক্ত);

        X11_XFlush(data->display);

        // Lets remember current active confined window.
        data->active_cursor_confined_window = window;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->pointer_barrier_active = true;
    } অন্যথা {
        X11_DestroyPointerBarrier(_this, window);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        যদি (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->pointer_barrier_active = false;
        }
    }
    ঘূৰাই true;
}

শূন্য X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_Window *window)
{
    পূর্ণাঙ্ক i;
    SDL_VideoData *data = _this->internal;
    যদি (window) {
        SDL_WindowData *wdata = window->internal;

        বাবে (i = 0; i < 4; i++) {
            যদি (wdata->barrier[i] > 0) {
                X11_XFixesDestroyPointerBarrier(data->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(data->display);
    }
    data->active_cursor_confined_window = রিক্ত;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
