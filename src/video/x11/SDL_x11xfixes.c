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

#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XFIXES)

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11xfixes.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"

സ്ഥിതം bool xfixes_initialized = true;
സ്ഥിതം പൂർണ്ണസംഖ്യ xfixes_selection_notify_event = 0;

സ്ഥിതം പൂർണ്ണസംഖ്യ query_xfixes_version(Display *display, പൂർണ്ണസംഖ്യ major, പൂർണ്ണസംഖ്യ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XFixesQueryVersion(display, &major, &minor);
    തിരികെ (major * 1000) + minor;
}

സ്ഥിതം bool xfixes_version_atleast(സ്ഥിരം പൂർണ്ണസംഖ്യ version, സ്ഥിരം പൂർണ്ണസംഖ്യ wantmajor, സ്ഥിരം പൂർണ്ണസംഖ്യ wantminor)
{
    തിരികെ version >= ((wantmajor * 1000) + wantminor);
}

ശൂന്യം X11_InitXfixes(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    പൂർണ്ണസംഖ്യ version = 0;
    പൂർണ്ണസംഖ്യ event, error;
    പൂർണ്ണസംഖ്യ fixes_opcode;

    Atom XA_CLIPBOARD = data->atoms.CLIPBOARD;

    എങ്കിൽ (!SDL_X11_HAVE_XFIXES ||
        !X11_XQueryExtension(data->display, "XFIXES", &fixes_opcode, &event, &error)) {
        തിരികെ;
    }

    // Selection tracking is available in all versions of XFixes
    xfixes_selection_notify_event = event + XFixesSelectionNotify;
    X11_XFixes_Select_Selection_നിവേശം(data->display, Default_വേര്_Window(data->display),
            XA_CLIPBOARD, XFixesSetSelectionOwnerNotifyMask);
    X11_XFixes_Select_Selection_നിവേശം(data->display, Default_വേര്_Window(data->display),
            XA_PRIMARY, XFixesSetSelectionOwnerNotifyMask);

    // We need at least 5.0 for barriers.
    version = query_xfixes_version(data->display, 5, 0);
    എങ്കിൽ (!xfixes_version_atleast(version, 5, 0)) {
        തിരികെ; // X server does not support the version we want at all.
    }

    xfixes_initialized = 1;
}

bool X11_XfixesIsInitialized(ശൂന്യം)
{
    തിരികെ xfixes_initialized;
}

പൂർണ്ണസംഖ്യ X11_GetXFixesSelectionNotifyEvent(ശൂന്യം)
{
    തിരികെ xfixes_selection_notify_event;
}

bool X11_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (SDL_RectEmpty(&window->mouse_rect)) {
        X11_ConfineCursorWithFlags(_this, window, ശൂന്യ, 0);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
            X11_ConfineCursorWithFlags(_this, window, &window->mouse_rect, 0);
        } അല്ലെങ്കിൽ {
            // Save the state for when we get focus again
            SDL_WindowData *wdata = window->internal;

            SDL_memcpy(&wdata->barrier_rect, &window->mouse_rect, വലുപ്പം(wdata->barrier_rect));

            wdata->pointer_barrier_active = true;
        }
    }

    തിരികെ true;
}

bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rect, പൂർണ്ണസംഖ്യ flags)
{
    /* Yaakuro: For some reason Xfixes when confining inside a rect where the
     * edges exactly match, a rectangle the cursor 'slips' out of the barrier.
     * To prevent that the lines for the barriers will span the whole screen.
     */
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wdata;

    എങ്കിൽ (!X11_XfixesIsInitialized()) {
        തിരികെ SDL_Unsupported();
    }

    // If there is already a set of barriers active, disable them.
    എങ്കിൽ (data->active_cursor_confined_window) {
        X11_DestroyPointerBarrier(_this, data->active_cursor_confined_window);
    }

    SDL_assert(window != ശൂന്യ);
    wdata = window->internal;

    /* If user did not specify an area to confine, destroy the barrier that was/is assigned to
     * this window it was assigned */
    എങ്കിൽ (rect) {
        പൂർണ്ണസംഖ്യ x1, y1, x2, y2;
        SDL_Rect bounds;
        SDL_GetWindowPosition(window, &bounds.x, &bounds.y);
        SDL_GetWindowSize(window, &bounds.w, &bounds.h);

        /** Negative values are not allowed. Clip values relative to the specified window. */
        x1 = bounds.x + SDL_max(rect->x, 0);
        y1 = bounds.y + SDL_max(rect->y, 0);
        x2 = SDL_min(bounds.x + rect->x + rect->w, bounds.x + bounds.w);
        y2 = SDL_min(bounds.y + rect->y + rect->h, bounds.y + bounds.h);

        എങ്കിൽ ((wdata->barrier_rect.x != rect->x) ||
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
                                                           0, ശൂന്യ);
        /** Create the right barrier */
        wdata->barrier[1] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           x2, bounds.y,
                                                           x2, bounds.y + bounds.h,
                                                           BarrierNegativeX,
                                                           0, ശൂന്യ);
        /** Create the top barrier */
        wdata->barrier[2] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y1,
                                                           bounds.x + bounds.w, y1,
                                                           BarrierPositiveY,
                                                           0, ശൂന്യ);
        /** Create the bottom barrier */
        wdata->barrier[3] = X11_XFixesCreatePointerBarrier(data->display, wdata->xwindow,
                                                           bounds.x, y2,
                                                           bounds.x + bounds.w, y2,
                                                           BarrierNegativeY,
                                                           0, ശൂന്യ);

        X11_XFlush(data->display);

        // Lets remember current active confined window.
        data->active_cursor_confined_window = window;

        /* User activated the confinement for this window. We use this later to reactivate
         * the confinement if it got deactivated by FocusOut or UnmapNotify */
        wdata->pointer_barrier_active = true;
    } അല്ലെങ്കിൽ {
        X11_DestroyPointerBarrier(_this, window);

        // Only set barrier inactive when user specified NULL and not handled by focus out.
        എങ്കിൽ (flags != X11_BARRIER_HANDLED_BY_EVENT) {
            wdata->pointer_barrier_active = false;
        }
    }
    തിരികെ true;
}

ശൂന്യം X11_DestroyPointerBarrier(SDL_VideoDevice *_this, SDL_Window *window)
{
    പൂർണ്ണസംഖ്യ i;
    SDL_VideoData *data = _this->internal;
    എങ്കിൽ (window) {
        SDL_WindowData *wdata = window->internal;

        വേണ്ടി (i = 0; i < 4; i++) {
            എങ്കിൽ (wdata->barrier[i] > 0) {
                X11_XFixesDestroyPointerBarrier(data->display, wdata->barrier[i]);
                wdata->barrier[i] = 0;
            }
        }
        X11_XFlush(data->display);
    }
    data->active_cursor_confined_window = ശൂന്യ;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XFIXES
