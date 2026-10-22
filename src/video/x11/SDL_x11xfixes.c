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

#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#شامل "SDL_x11video.h"
#شامل "SDL_x11xfixes.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_touch_c.h"

ساکن bool xfixes_initialized = true;
ساکن صحیح xfixes_selection_notify_event = 0;

ساکن صحیح query_xfixes_نسخہ(Display *display, صحیح major, صحیح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_نسخہ(display, &major, &minor);
    واپس (major * 1000) + minor;
}

ساکن bool xfixes_نسخہ_atleast(ثابت صحیح نسخہ, ثابت صحیح wantmajor, ثابت صحیح wantminor)
{
    واپس نسخہ >= ((wantmajor * 1000) + wantminor);
}

خالی X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    صحیح نسخہ = 0;
    صحیح event, error;
    صحیح fixes_opcode;

    Atom XA_CLIPBOARD = ڈیٹا->atoms.CLIPBOARD;

    اگر (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(ڈیٹا->display, "XFIXES", &fixes_opcode, &event, &error)) {
        واپس;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_داخلہ(ڈیٹا->display, Default_جڑ_کھڑکی(ڈیٹا->display),
            XA_CLIPBOARD, XFixes_سیٹ_Selection_Owner_Notify_نقاب);
    X11_XFixes_Select_Selection_داخلہ(ڈیٹا->display, Default_جڑ_کھڑکی(ڈیٹا->display),
            XA_PRIMARY, XFixes_سیٹ_Selection_Owner_Notify_نقاب);

    // We need at least 5.0 for barriers.
    نسخہ = query_xfixes_نسخہ(ڈیٹا->display, 5, 0);
    اگر (!xfixes_نسخہ_atleast(نسخہ, 5, 0)) {
        واپس; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(خالی)
{
    واپس xfixes_initialized;
}

صحیح X11_GetXFixesSelectionNotifyEvent(خالی)
{
    واپس xfixes_selection_notify_event;
}

bool X11_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (SDL_Rect_خالی_خانے(&کھڑکی->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, کھڑکی, تہی, 0);
    } ورنہ {
        اگر (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            X11_ConfineCursorWithFlags(_this, کھڑکی, &کھڑکی->mouse_rect, 0);
        } ورنہ {
            // Save the state for when we get focus again
            SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

            SDL_memcpy(&wdata->barrier_rect, &کھڑکی->mouse_rect, حجم(wdata->barrier_rect));

            wdata->اشارہ_گر_barrier_فعال = true;
        }
    }

    واپس true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect, صحیح flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *wdata;

    اگر (!X11_XfixesIsInitialized()) {
        واپس SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    اگر (ڈیٹا->فعال_cursor_confined_کھڑکی) {
        X11_Destroy_اشارہ_گر_Barrier(_this, ڈیٹا->فعال_cursor_confined_کھڑکی);
    }

    SDL_assert(کھڑکی != تہی);
    wdata = کھڑکی->اندرونی_2;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    اگر (rect) {
        صحیح x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_کھڑکی_Position(کھڑکی, &bounds.x, &bounds.y);
        SDL_Get_کھڑکی_سائز(کھڑکی, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        اگر ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_کھڑکی(کھڑکی), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixes_Create_اشارہ_گر_Barrier(ڈیٹا->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_مثبت_X,
                                                           0, تہی);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixes_Create_اشارہ_گر_Barrier(ڈیٹا->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, تہی);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixes_Create_اشارہ_گر_Barrier(ڈیٹا->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_مثبت_Y,
                                                           0, تہی);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixes_Create_اشارہ_گر_Barrier(ڈیٹا->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, تہی);

        X11_XFlush(ڈیٹا->display);

        // Lets remember current active confined window.
        ڈیٹا->فعال_cursor_confined_کھڑکی = کھڑکی;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->اشارہ_گر_barrier_فعال = true;
    } ورنہ {
        X11_Destroy_اشارہ_گر_Barrier(_this, کھڑکی);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        اگر (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->اشارہ_گر_barrier_فعال = false;
        }
    }
    واپس true;
}

خالی X11_Destroy_اشارہ_گر_Barrier(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    صحیح i;
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (کھڑکی) {
        SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

        برائے (i = 0; i < 4; i++) {
            اگر (wdata->barrier[i] > 0) {
                X11_XFixes_Destroy_اشارہ_گر_Barrier(ڈیٹا->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(ڈیٹا->display);
    }
    ڈیٹا->فعال_cursor_confined_کھڑکی = تہی;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
