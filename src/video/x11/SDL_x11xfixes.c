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

#यदि defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xfixes.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

स्थिर bool xfixes_initialized = true;
स्थिर पूर्णाङ्क xfixes_selection_notify_event = 0;

स्थिर पूर्णाङ्क query_xfixes_संस्करणम्(Display *display, पूर्णाङ्क major, पूर्णाङ्क minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_संस्करणम्(display, &major, &minor);
    प्रत्यागम (major * 1000) + minor;
}

स्थिर bool xfixes_संस्करणम्_atleast(ध्रुव पूर्णाङ्क संस्करणम्, ध्रुव पूर्णाङ्क wantmajor, ध्रुव पूर्णाङ्क wantminor)
{
    प्रत्यागम संस्करणम् >= ((wantmajor * 1000) + wantminor);
}

शून्य X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    पूर्णाङ्क संस्करणम् = 0;
    पूर्णाङ्क event, error;
    पूर्णाङ्क fixes_opcode;

    Atom XA_CLIPBOARD = दत्त->atoms.CLIPBOARD;

    यदि (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(दत्त->display, "XFIXES", &fixes_opcode, &event, &error)) {
        प्रत्यागम;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_निवेशः(दत्त->display, Default_मूलम्_गवाक्षः(दत्त->display),
            XA_CLIPBOARD, XFixes_समुच्चयः_Selection_Owner_Notify_आवरणम्);
    X11_XFixes_Select_Selection_निवेशः(दत्त->display, Default_मूलम्_गवाक्षः(दत्त->display),
            XA_PRIMARY, XFixes_समुच्चयः_Selection_Owner_Notify_आवरणम्);

    // We need at least 5.0 for barriers.
    संस्करणम् = query_xfixes_संस्करणम्(दत्त->display, 5, 0);
    यदि (!xfixes_संस्करणम्_atleast(संस्करणम्, 5, 0)) {
        प्रत्यागम; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(शून्य)
{
    प्रत्यागम xfixes_initialized;
}

पूर्णाङ्क X11_GetXFixesSelectionNotifyEvent(शून्य)
{
    प्रत्यागम xfixes_selection_notify_event;
}

bool X11_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (SDL_Rect_रिक्तानि(&गवाक्षः->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, गवाक्षः, रिक्त, 0);
    } अन्यथा {
        यदि (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
            X11_ConfineCursorWithFlags(_this, गवाक्षः, &गवाक्षः->mouse_rect, 0);
        } अन्यथा {
            // Save the state for when we get focus again
            SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

            SDL_memcpy(&wdata->barrier_rect, &गवाक्षः->mouse_rect, परिमाण(wdata->barrier_rect));

            wdata->pointer_barrier_सक्रिय = true;
        }
    }

    प्रत्यागम true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rect, पूर्णाङ्क flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *wdata;

    यदि (!X11_XfixesIsInitialized()) {
        प्रत्यागम SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    यदि (दत्त->सक्रिय_cursor_confined_गवाक्षः) {
        X11_DestroyPointerBarrier(_this, दत्त->सक्रिय_cursor_confined_गवाक्षः);
    }

    SDL_assert(गवाक्षः != रिक्त);
    wdata = गवाक्षः->आन्तरिकम्;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    यदि (rect) {
        पूर्णाङ्क x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_गवाक्षः_Position(गवाक्षः, &bounds.x, &bounds.y);
        SDL_Get_गवाक्षः_आकार(गवाक्षः, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        यदि ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_गवाक्षः(गवाक्षः), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixesCreatePointerBarrier(दत्त->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_धनात्मकम्_X,
                                                           0, रिक्त);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixesCreatePointerBarrier(दत्त->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, रिक्त);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixesCreatePointerBarrier(दत्त->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_धनात्मकम्_Y,
                                                           0, रिक्त);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixesCreatePointerBarrier(दत्त->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, रिक्त);

        X11_XFlush(दत्त->display);

        // Lets remember current active confined window.
        दत्त->सक्रिय_cursor_confined_गवाक्षः = गवाक्षः;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->pointer_barrier_सक्रिय = true;
    } अन्यथा {
        X11_DestroyPointerBarrier(_this, गवाक्षः);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        यदि (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->pointer_barrier_सक्रिय = false;
        }
    }
    प्रत्यागम true;
}

शून्य X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    पूर्णाङ्क i;
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    यदि (गवाक्षः) {
        SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

        प्रति (i = 0; i < 4; i++) {
            यदि (wdata->barrier[i] > 0) {
                X11_XFixesDestroyPointerBarrier(दत्त->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(दत्त->display);
    }
    दत्त->सक्रिय_cursor_confined_गवाक्षः = रिक्त;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
