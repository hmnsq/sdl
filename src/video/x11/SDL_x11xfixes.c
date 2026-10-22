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

#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xfixes.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"

ساكن bool xfixes_initialized = true;
ساكن صحيح xfixes_selection_notify_event = 0;

ساكن صحيح query_xfixes_نسخہ(Display *display, صحيح major, صحيح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_نسخہ(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xfixes_نسخہ_atleast(ثابت صحيح نسخہ, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع نسخہ >= ((wantmajor * 1000) + wantminor);
}

فراغ X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    صحيح نسخہ = 0;
    صحيح event, error;
    صحيح fixes_opcode;

    Atom XA_CLIPBOARD = انکڑے->atoms.CLIPBOARD;

    إذا (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(انکڑے->display, "XFIXES", &fixes_opcode, &event, &error)) {
        أرجع;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_داخلہ(انکڑے->display, Default_جڑ_کھڑکی(انکڑے->display),
            XA_CLIPBOARD, XFixes_سیٹ_Selection_Owner_Notify_نقاب);
    X11_XFixes_Select_Selection_داخلہ(انکڑے->display, Default_جڑ_کھڑکی(انکڑے->display),
            XA_PRIMARY, XFixes_سیٹ_Selection_Owner_Notify_نقاب);

    // We need at least 5.0 for barriers.
    نسخہ = query_xfixes_نسخہ(انکڑے->display, 5, 0);
    إذا (!xfixes_نسخہ_atleast(نسخہ, 5, 0)) {
        أرجع; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(فراغ)
{
    أرجع xfixes_initialized;
}

صحيح X11_GetXFixesSelectionNotifyEvent(فراغ)
{
    أرجع xfixes_selection_notify_event;
}

bool X11_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (SDL_Rect_خالی_تھاواں(&کھڑکی->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, کھڑکی, عدم, 0);
    } وإلا {
        إذا (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            X11_ConfineCursorWithFlags(_this, کھڑکی, &کھڑکی->mouse_rect, 0);
        } وإلا {
            // Save the state for when we get focus again
            SDL_کھڑکی_انکڑے *wdata = کھڑکی->اندرونی;

            SDL_memcpy(&wdata->barrier_rect, &کھڑکی->mouse_rect, حجم(wdata->barrier_rect));

            wdata->اشارہ_گر_barrier_سرگرم = true;
        }
    }

    أرجع true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect, صحيح flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_کھڑکی_انکڑے *wdata;

    إذا (!X11_XfixesIsInitialized()) {
        أرجع SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    إذا (انکڑے->سرگرم_cursor_confined_کھڑکی) {
        X11_Destroy_اشارہ_گر_Barrier(_this, انکڑے->سرگرم_cursor_confined_کھڑکی);
    }

    SDL_assert(کھڑکی != عدم);
    wdata = کھڑکی->اندرونی;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    إذا (rect) {
        صحيح x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_کھڑکی_Position(کھڑکی, &bounds.x, &bounds.y);
        SDL_Get_کھڑکی_ناپ(کھڑکی, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        إذا ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_کھڑکی(کھڑکی), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixes_Create_اشارہ_گر_Barrier(انکڑے->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_مثبت_X,
                                                           0, عدم);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixes_Create_اشارہ_گر_Barrier(انکڑے->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, عدم);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixes_Create_اشارہ_گر_Barrier(انکڑے->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_مثبت_Y,
                                                           0, عدم);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixes_Create_اشارہ_گر_Barrier(انکڑے->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, عدم);

        X11_XFlush(انکڑے->display);

        // Lets remember current active confined window.
        انکڑے->سرگرم_cursor_confined_کھڑکی = کھڑکی;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->اشارہ_گر_barrier_سرگرم = true;
    } وإلا {
        X11_Destroy_اشارہ_گر_Barrier(_this, کھڑکی);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        إذا (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->اشارہ_گر_barrier_سرگرم = false;
        }
    }
    أرجع true;
}

فراغ X11_Destroy_اشارہ_گر_Barrier(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    صحيح i;
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    إذا (کھڑکی) {
        SDL_کھڑکی_انکڑے *wdata = کھڑکی->اندرونی;

        لكل (i = 0; i < 4; i++) {
            إذا (wdata->barrier[i] > 0) {
                X11_XFixes_Destroy_اشارہ_گر_Barrier(انکڑے->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(انکڑے->display);
    }
    انکڑے->سرگرم_cursor_confined_کھڑکی = عدم;
}

#جے_انت // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
