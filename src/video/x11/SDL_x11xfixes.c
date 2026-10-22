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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xfixes.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"

స్థిర bool xfixes_initialized = true;
స్థిర పూర్ణాంకం xfixes_selection_notify_event = 0;

స్థిర పూర్ణాంకం query_xfixes_సంస్కరణ(Display *display, పూర్ణాంకం major, పూర్ణాంకం minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixes_Query_సంస్కరణ(display, &major, &minor);
    తిరిగి (major * 1000) + minor;
}

స్థిర bool xfixes_సంస్కరణ_atleast(స్థిరరాశి పూర్ణాంకం సంస్కరణ, స్థిరరాశి పూర్ణాంకం wantmajor, స్థిరరాశి పూర్ణాంకం wantminor)
{
    తిరిగి సంస్కరణ >= ((wantmajor * 1000) + wantminor);
}

శూన్య X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    పూర్ణాంకం సంస్కరణ = 0;
    పూర్ణాంకం event, error;
    పూర్ణాంకం fixes_opcode;

    Atom XA_CLIPBOARD = దత్తాంశం->atoms.CLIPBOARD;

    ఒకవేళ (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(దత్తాంశం->display, "XFIXES", &fixes_opcode, &event, &error)) {
        తిరిగి;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_ఆదానం(దత్తాంశం->display, Default_మూలం_కిటికీ(దత్తాంశం->display),
            XA_CLIPBOARD, XFixes_సమితి_Selection_Owner_Notify_ముసుగు);
    X11_XFixes_Select_Selection_ఆదానం(దత్తాంశం->display, Default_మూలం_కిటికీ(దత్తాంశం->display),
            XA_PRIMARY, XFixes_సమితి_Selection_Owner_Notify_ముసుగు);

    // We need at least 5.0 for barriers.
    సంస్కరణ = query_xfixes_సంస్కరణ(దత్తాంశం->display, 5, 0);
    ఒకవేళ (!xfixes_సంస్కరణ_atleast(సంస్కరణ, 5, 0)) {
        తిరిగి; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(శూన్య)
{
    తిరిగి xfixes_initialized;
}

పూర్ణాంకం X11_GetXFixesSelectionNotifyEvent(శూన్య)
{
    తిరిగి xfixes_selection_notify_event;
}

bool X11_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (SDL_Rect_ఖాళీలు(&కిటికీ->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, కిటికీ, ఖాళీ, 0);
    } లేకపోతే {
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
            X11_ConfineCursorWithFlags(_this, కిటికీ, &కిటికీ->mouse_rect, 0);
        } లేకపోతే {
            // Save the state for when we get focus again
            SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

            SDL_memcpy(&wdata->barrier_rect, &కిటికీ->mouse_rect, పరిమాణం(wdata->barrier_rect));

            wdata->సూచిక_barrier_చురుకైన = true;
        }
    }

    తిరిగి true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *wdata;

    ఒకవేళ (!X11_XfixesIsInitialized()) {
        తిరిగి SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    ఒకవేళ (దత్తాంశం->చురుకైన_cursor_confined_కిటికీ) {
        X11_Destroy_సూచిక_Barrier(_this, దత్తాంశం->చురుకైన_cursor_confined_కిటికీ);
    }

    SDL_assert(కిటికీ != ఖాళీ);
    wdata = కిటికీ->అంతర్గత;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    ఒకవేళ (rect) {
        పూర్ణాంకం x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_Get_కిటికీ_Position(కిటికీ, &bounds.x, &bounds.y);
        SDL_Get_కిటికీ_కొలత(కిటికీ, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        ఒకవేళ ((wdata->barrier_rect.x != rect->x) ||
            (wdata->barrier_rect.y != rect->y) ||
            (wdata->barrier_rect.w != rect->w) ||
            (wdata->barrier_rect.h != rect->h)) {
            wdata->barrier_rect = *rect;
        }

        // Use the display bounds to ensure the barriers don't have corner gaps
        SDL_GetDisplayBounds(SDL_Get_Display_For_కిటికీ(కిటికీ), &bounds);

        /** Create the left barrier */
        wdata->barrier[0] = X11_XFixes_Create_సూచిక_Barrier(దత్తాంశం->display, wdata->xwindow,
                                                           x1, bounds.y,
                                                           x1, bounds.y + bounds.h,
                                                           Barrier_ధనాత్మక_X,
                                                           0, ఖాళీ);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixes_Create_సూచిక_Barrier(దత్తాంశం->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, ఖాళీ);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixes_Create_సూచిక_Barrier(దత్తాంశం->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           Barrier_ధనాత్మక_Y,
                                                           0, ఖాళీ);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixes_Create_సూచిక_Barrier(దత్తాంశం->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, ఖాళీ);

        X11_XFlush(దత్తాంశం->display);

        // Lets remember current active confined window.
        దత్తాంశం->చురుకైన_cursor_confined_కిటికీ = కిటికీ;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->సూచిక_barrier_చురుకైన = true;
    } లేకపోతే {
        X11_Destroy_సూచిక_Barrier(_this, కిటికీ);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        ఒకవేళ (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->సూచిక_barrier_చురుకైన = false;
        }
    }
    తిరిగి true;
}

శూన్య X11_Destroy_సూచిక_Barrier(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    పూర్ణాంకం i;
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    ఒకవేళ (కిటికీ) {
        SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

        కొరకు (i = 0; i < 4; i++) {
            ఒకవేళ (wdata->barrier[i] > 0) {
                X11_XFixes_Destroy_సూచిక_Barrier(దత్తాంశం->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(దత్తాంశం->display);
    }
    దత్తాంశం->చురుకైన_cursor_confined_కిటికీ = ఖాళీ;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
