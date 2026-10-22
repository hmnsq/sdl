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

#ਜੇ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xfixes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"

ਸਥਿਰ bool xfixes_initialized = true;
ਸਥਿਰ ਪੂਰਨ xfixes_selection_notify_event = 0;

ਸਥਿਰ ਪੂਰਨ query_xfixes_ਸੰਸਕਰਣ(Display *display, ਪੂਰਨ major, ਪੂਰਨ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_ਸੰਸਕਰਣ(display, &major, &minor);
    ਵਾਪਸ (major * 1000) + minor;
}

ਸਥਿਰ bool xfixes_ਸੰਸਕਰਣ_atleast(ਅਚਲ ਪੂਰਨ ਸੰਸਕਰਣ, ਅਚਲ ਪੂਰਨ wantmajor, ਅਚਲ ਪੂਰਨ wantminor)
{
    ਵਾਪਸ ਸੰਸਕਰਣ >= ((wantmajor * 1000) + wantminor);
}

ਖਾਲੀ X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਪੂਰਨ ਸੰਸਕਰਣ = 0;
    ਪੂਰਨ event, error;
    ਪੂਰਨ fixes_opcode;

    Atom XA_CLIPBOARD = ਅੰਕੜੇ->atoms.CLIPBOARD;

    ਜੇ (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(ਅੰਕੜੇ->display, "XFIXES", &fixes_opcode, &event, &error)) {
        ਵਾਪਸ;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_ਨਿਵੇਸ਼(ਅੰਕੜੇ->display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(ਅੰਕੜੇ->display),
            XA_CLIPBOARD, XFixes_ਸੈੱਟ_Selection_Owner_Notify_ਨਕਾਬ);
    X11_XFixes_Select_Selection_ਨਿਵੇਸ਼(ਅੰਕੜੇ->display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(ਅੰਕੜੇ->display),
            XA_PRIMARY, XFixes_ਸੈੱਟ_Selection_Owner_Notify_ਨਕਾਬ);

    // We need at least 5.0 for barriers.
    ਸੰਸਕਰਣ = query_xfixes_ਸੰਸਕਰਣ(ਅੰਕੜੇ->display, 5, 0);
    ਜੇ (!xfixes_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 5, 0)) {
        ਵਾਪਸ; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(ਖਾਲੀ)
{
    ਵਾਪਸ xfixes_initialized;
}

ਪੂਰਨ X11_GetXFixesSelectionNotifyEvent(ਖਾਲੀ)
{
    ਵਾਪਸ xfixes_selection_notify_event;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, ਖਿੜਕੀ, ਨਿਰਾ, 0);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
            X11_ConfineCursorWithFlags(_this, ਖਿੜਕੀ, &ਖਿੜਕੀ->mouse_rect, 0);
        } ਨਹੀਂਤਾਂ {
            // Save the state for when we get focus again
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

            SDL_memcpy(&wdata->barrier_rect, &ਖਿੜਕੀ->mouse_rect, ਆਕਾਰ(wdata->barrier_rect));

            wdata->ਸੂਚਕ_barrier_ਸਰਗਰਮ = true;
        }
    }

    ਵਾਪਸ true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rect, ਪੂਰਨ flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata;

    ਜੇ (!X11_XfixesIsInitialized()) {
        ਵਾਪਸ SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    ਜੇ (ਅੰਕੜੇ->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ) {
        X11_Destroy_ਸੂਚਕ_Barrier(_this, ਅੰਕੜੇ->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ);
    }

    SDL_assert(ਖਿੜਕੀ != ਨਿਰਾ);
    wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    ਜੇ (rect) {
        ਪੂਰਨ x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_ਖਿੜਕੀ_Position(ਖਿੜਕੀ, &bounds.x, &bounds.y);
        SDL_Get_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        ਜੇ ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixes_Create_ਸੂਚਕ_Barrier(ਅੰਕੜੇ->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_ਸਕਾਰਾਤਮਕ_X,
                                                           0, ਨਿਰਾ);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixes_Create_ਸੂਚਕ_Barrier(ਅੰਕੜੇ->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, ਨਿਰਾ);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixes_Create_ਸੂਚਕ_Barrier(ਅੰਕੜੇ->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_ਸਕਾਰਾਤਮਕ_Y,
                                                           0, ਨਿਰਾ);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixes_Create_ਸੂਚਕ_Barrier(ਅੰਕੜੇ->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, ਨਿਰਾ);

        X11_XFlush(ਅੰਕੜੇ->display);

        // Lets remember current active confined window.
        ਅੰਕੜੇ->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ = ਖਿੜਕੀ;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->ਸੂਚਕ_barrier_ਸਰਗਰਮ = true;
    } ਨਹੀਂਤਾਂ {
        X11_Destroy_ਸੂਚਕ_Barrier(_this, ਖਿੜਕੀ);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        ਜੇ (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->ਸੂਚਕ_barrier_ਸਰਗਰਮ = false;
        }
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Destroy_ਸੂਚਕ_Barrier(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਪੂਰਨ i;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਖਿੜਕੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        ਲਈ (i = 0; i < 4; i++) {
            ਜੇ (wdata->barrier[i] > 0) {
                X11_XFixes_Destroy_ਸੂਚਕ_Barrier(ਅੰਕੜੇ->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(ਅੰਕੜੇ->display);
    }
    ਅੰਕੜੇ->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
