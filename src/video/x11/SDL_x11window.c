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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_appid.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11mouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xfixes.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ "SDL_x11opengles.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

#ವ್ಯಾಖ್ಯಾನಿಸು _NET_WM_STATE_REMOVE 0l
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_STATE_ಕೂಡಿಸು    1l

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_ಕಿಟಕಿ_ದತ್ತಾಂಶ(ಕಿಟಕಿ)                                       \
    ಆದರೆ (!ಕಿಟಕಿ) {                                                      \
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid window");                          \
    }                                                                   \
    ಆದರೆ (!ಕಿಟಕಿ->ಆಂತರಿಕ) {                                          \
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid window driver data");              \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_DISPLAY_ದತ್ತಾಂಶ(display)                                     \
    ಆದರೆ (!_display) {                                                    \
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid display");                         \
    }                                                                   \
    ಆದರೆ (!_display->ಆಂತರಿಕ) {                                        \
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid display driver data");             \
    }

ಸ್ಥಿರ Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ಹಿಂತಿರುಗಿ ev->type == MapNotify && ev->xmap.ಕಿಟಕಿ == *((ಕಿಟಕಿ_2 *)win);
}
ಸ್ಥಿರ Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ಹಿಂತಿರುಗಿ ev->type == UnmapNotify && ev->xunmap.ಕಿಟಕಿ == *((ಕಿಟಕಿ_2 *)win);
}

/*
static Bool isConfigureNotify(Display *dpy, XEvent *ev, XPointer win)
{
    return ev->type == ConfigureNotify && ev->xconfigure.window == *((Window *)win);
}
static Bool X11_XIfEventTimeout(Display *display, XEvent *event_return, Bool (*predicate)(), XPointer arg, int timeoutMS)
{
    Uint64 start = SDL_GetTicks();

    while (!X11_XCheckIfEvent(display, event_return, predicate, arg)) {
        if (SDL_GetTicks() >= (start + timeoutMS)) {
            return False;
        }
    }
    return True;
}
*/

ಸ್ಥಿರ bool X11_CheckCurrentDesktop(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    ಆದರೆ (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    ಆದರೆ (desktopVar && SDL_strcasestr(desktopVar, name)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool X11_Is_ಕಿಟಕಿ_Mapped(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    XWindow_ಗುಣಲಕ್ಷಣಗಳು attr;

    X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(videodata->display, ದತ್ತಾಂಶ->xwindow, &attr);
    ಆದರೆ (attr.map_state != IsUnmapped) {
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }
}

ಸ್ಥಿರ bool X11_IsDisplayOk(Display *display)
{
    ಆದರೆ (display->flags & XlibDisplayIOError) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ 0
ಸ್ಥಿರ bool X11_IsActionAllowed(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, Atom action)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Atom _NET_WM_ALLOWED_ACTIONS = ದತ್ತಾಂಶ->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಪೂರ್ಣಾಂಕ form;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ remain;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ len, i;
    Atom *list;
    bool ret = false;

    ಆದರೆ (X11_XGet_ಕಿಟಕಿ_Property(display, ದತ್ತಾಂಶ->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **)&list) == Success) {
        ಗಾಗಿ (i=0; i<len; ++i) {
            ಆದರೆ (list[i] == action) {
                ret = true;
                ನಿಲ್ಲಿಸು;
            }
        }
        X11_XFree(list);
    }
    ಹಿಂತಿರುಗಿ ret;
}
#ಆದರೆ_ಅಂತ್ಯ // 0

ಸ್ಥಿರ ಶೂನ್ಯ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ಸ್ಥಿರಾಂಕ bool ಕೊನೆಯ_position_pending = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending;
    ಸ್ಥಿರಾಂಕ bool ಕೊನೆಯ_ಗಾತ್ರ_pending = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending;

    X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);

    ಕಿಟಕಿ->ಕೊನೆಯ_position_pending = ಕೊನೆಯ_position_pending;
    ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = ಕೊನೆಯ_ಗಾತ್ರ_pending;
}

ಶೂನ್ಯ X11_ಗಣ_Net_WMState(SDL_VideoDevice *_this, ಕಿಟಕಿ_2 xwindow, SDL_ಕಿಟಕಿ_Flags flags)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;
    // !!! FIXME: just dereference videodata below instead of copying to locals.
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    // Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom _NET_WM_STATE_ABOVE = videodata->atoms._NET_WM_STATE_ABOVE;
    Atom _NET_WM_STATE_SKIP_TASKBAR = videodata->atoms._NET_WM_STATE_SKIP_TASKBAR;
    Atom _NET_WM_STATE_SKIP_PAGER = videodata->atoms._NET_WM_STATE_SKIP_PAGER;
    Atom _NET_WM_STATE_MODAL = videodata->atoms._NET_WM_STATE_MODAL;
    Atom atoms[16];
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_ABOVE;
    }
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_UTILITY) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_SKIP_PAGER;
    }
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_FOCUSED;
    }
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MAXIMIZED) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_FULLSCREEN;
    }
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MODAL) {
        atoms[ಎಣಿಕೆ_2++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(ಎಣಿಕೆ_2 <= SDL_arraysize(atoms));

    ಆದರೆ (ಎಣಿಕೆ_2 > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)atoms, ಎಣಿಕೆ_2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ConstrainPopup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool output_ಗಮ್ಯ_pending)
{
    // Clamp popup windows to the output borders
    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        SDL_ಕಿಟಕಿ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ಪೂರ್ಣಾಂಕ abs_x = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->floating.x;
        ಪೂರ್ಣಾಂಕ abs_y = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->floating.y;
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

            displayID = SDL_Get_Display_For_ಕಿಟಕಿ(w);

            SDL_GetDisplayBounds(displayID, &rect);
            ಆದರೆ (abs_x + ಕಿಟಕಿ->w > rect.x + rect.w) {
                abs_x -= (abs_x + ಕಿಟಕಿ->w) - (rect.x + rect.w);
            }
            ಆದರೆ (abs_y + ಕಿಟಕಿ->h > rect.y + rect.h) {
                abs_y -= (abs_y + ಕಿಟಕಿ->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ಆದರೆ (output_ಗಮ್ಯ_pending) {
            ಕಿಟಕಿ->pending.x = abs_x - ಸ್ಥಾನಾಂತರ_x;
            ಕಿಟಕಿ->pending.y = abs_y - ಸ್ಥಾನಾಂತರ_y;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->floating.x = ಕಿಟಕಿ->windowed.x = abs_x - ಸ್ಥಾನಾಂತರ_x;
            ಕಿಟಕಿ->floating.y = ಕಿಟಕಿ->windowed.y = abs_y - ಸ್ಥಾನಾಂತರ_y;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ಗಣ_Keyboard_Focus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool ಗಣ_ಸಕ್ರಿಯ_focus)
{
    SDL_ಕಿಟಕಿ *toplevel = ಕಿಟಕಿ;

    // Find the toplevel parent
    ಆಗ (SDL_ಕಿಟಕಿ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ಪೋಷಕ;
    }

    toplevel->keyboard_focus = ಕಿಟಕಿ;

    ಆದರೆ (ಗಣ_ಸಕ್ರಿಯ_focus && !ಕಿಟಕಿ->is_hiding && !ಕಿಟಕಿ->is_destroying) {
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    }
}

SDL_ಕಿಟಕಿ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಕಿಟಕಿ_2 xwindow)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    ಪೂರ್ಣಾಂಕ actualFormat;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ i, ಅಂಕೆ_ವಸ್ತುಗಳು, ಬೈಟುಗಳು_After;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *property_ಮೌಲ್ಯ = ಖಾಲಿ;
    ದೀರ್ಘ max_ಉದ್ದಳತೆ = 1024;
    SDL_ಕಿಟಕಿ_Flags flags = 0;

    ಆದರೆ (X11_XGet_ಕಿಟಕಿ_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_ಉದ್ದಳತೆ, False, XA_ATOM, &actualType,
                               &actualFormat, &ಅಂಕೆ_ವಸ್ತುಗಳು, &ಬೈಟುಗಳು_After,
                               &property_ಮೌಲ್ಯ) == Success) {
        Atom *atoms = (Atom *)property_ಮೌಲ್ಯ;
        ಪೂರ್ಣಾಂಕ maximized = 0;
        ಪೂರ್ಣಾಂಕ fullscreen = 0;

        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_ವಸ್ತುಗಳು; ++i) {
            ಆದರೆ (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_OCCLUDED;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        ಆದರೆ (fullscreen == 1) {
            flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN);
        }

        ಆದರೆ (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            ಆದರೆ (fullscreen) {
                flags |= (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED);
            } ಇಲ್ಲದಿದ್ದರೆ {
                flags |= SDL_ಕಿಟಕಿ_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_ಗುಣಲಕ್ಷಣಗಳು attr;
            SDL_zero(attr);
            X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(videodata->display, xwindow, &attr);
            ಆದರೆ (attr.map_state == IsUnmapped) {
                flags |= SDL_ಕಿಟಕಿ_HIDDEN;
            }
        }
        X11_XFree(property_ಮೌಲ್ಯ);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    ಹಿಂತಿರುಗಿ flags;
}

ಸ್ಥಿರ bool ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಕಿಟಕಿ_2 w)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Allocate the window data
    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }
    ದತ್ತಾಂಶ->videodata = videodata;
    ದತ್ತಾಂಶ->ಕಿಟಕಿ = ಕಿಟಕಿ;
    ದತ್ತಾಂಶ->xwindow = w;
    ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ = SDL_HITTEST_ಸಾಮಾನ್ಯ;

    X11_Create_ಒಳಹರಿವು_Context(ದತ್ತಾಂಶ);

    // Associate the data with the window

    ಆದರೆ (videodata->numwindows >= videodata->windowlistlength) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ ** new_windowlist = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * ಗಾತ್ರ(*videodata->windowlist));
        ಆದರೆ (!new_windowlist) {
            ಹೋಗು error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_ಗುಣಲಕ್ಷಣಗಳು attrib;

        X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(ದತ್ತಾಂಶ->videodata->display, w, &attrib);
        ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
            ಕಿಟಕಿ->x = ಕಿಟಕಿ->windowed.x = ಕಿಟಕಿ->floating.x = attrib.x;
            ಕಿಟಕಿ->y = ಕಿಟಕಿ->windowed.y = ಕಿಟಕಿ->floating.y = attrib.y - ದತ್ತಾಂಶ->border_ತುದಿ;
        }
        ಕಿಟಕಿ->w = ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->floating.w = attrib.ಅಗಲ;
        ಕಿಟಕಿ->h = ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->floating.h = attrib.ಎತ್ತರ;
        ಆದರೆ (attrib.map_state != IsUnmapped) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_HIDDEN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_HIDDEN;
        }
        ದತ್ತಾಂಶ->visual = attrib.visual;
        ದತ್ತಾಂಶ->colormap = attrib.colormap;
    }

    ಕಿಟಕಿ->flags |= X11_GetNetWMState(_this, ಕಿಟಕಿ, w);

    {
        ಕಿಟಕಿ_2 Focal_ಕಿಟಕಿ;
        ಪೂರ್ಣಾಂಕ Revert_ಗಮ್ಯ = 0;
        X11_XGet_ಒಳಹರಿವು_Focus(ದತ್ತಾಂಶ->videodata->display, &Focal_ಕಿಟಕಿ, &Revert_ಗಮ್ಯ);
        ಆದರೆ (Focal_ಕಿಟಕಿ == w) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS;
        }

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
            SDL_ಗಣ_Keyboard_Focus(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
        }

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        // Query the title from the existing window
        ಕಿಟಕಿ->title = X11_Get_ಕಿಟಕಿ_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    ಪೂರ್ಣಾಂಕ screen = (displaydata ? displaydata->screen : 0);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_X11_DISPLAY_ಸೂಚಕ, ದತ್ತಾಂಶ->videodata->display);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_X11_SCREEN_ಸಂಖ್ಯೆ, screen);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_X11_ಕಿಟಕಿ_ಸಂಖ್ಯೆ, ದತ್ತಾಂಶ->xwindow);


#ಆದರೆ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) &&
        ((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_ದತ್ತಾಂಶ || X11_GL_UseEGL(_this))
#ಆದರೆ_ಅಂತ್ಯ
    ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
            ಹೋಗು error_cleanup;
        }

        // Create the GLES window surface
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)w);

        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            SDL_ಗಣ_Error("Could not create GLES window surface");
            ಹೋಗು error_cleanup;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        SDL_ಗಣ_Error("Could not create GLES window surface (EGL support not configured)");
        ಹೋಗು error_cleanup;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL
    }
#ಆದರೆ_ಅಂತ್ಯ

    // All done!
    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    videodata->windowlist[videodata->numwindows++] = ದತ್ತಾಂಶ;
    ಹಿಂತಿರುಗಿ true;

error_cleanup:
    X11_Destroy_ಒಳಹರಿವು_Context(ದತ್ತಾಂಶ);
    SDL_free(ದತ್ತಾಂಶ);
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ದೀರ್ಘ fevent = 0;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಕಿಟಕಿ_2 xwindow = ದತ್ತಾಂಶ->xwindow;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (SDL_X11_HAVE_UTF8 && ದತ್ತಾಂಶ->ic) {
        X11_XGetICValues(ದತ್ತಾಂಶ->ic, XNFilterEvents, &fevent, ಖಾಲಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_Xinput2Select(_this, ಕಿಟಕಿ);

    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x11_keyboard_events = ಕೀಲಿ_Press_ಮುಖವಾಡ | ಕೀಲಿ_Release_ಮುಖವಾಡ;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x11_ಸೂಚಕ_events = Button_Press_ಮುಖವಾಡ | Button_Release_ಮುಖವಾಡ | ಸೂಚಕ_Motion_ಮುಖವಾಡ;

        X11_Xinput2SelectMouseAndKeyboard(_this, ಕಿಟಕಿ);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_mouse_enabled) {
            x11_ಸೂಚಕ_events = 0;
        }

        X11_XSelect_ಒಳಹರಿವು(ದತ್ತಾಂಶ->videodata->display, xwindow,
                         (Focus_Change_ಮುಖವಾಡ | Enter_ಕಿಟಕಿ_ಮುಖವಾಡ | Leave_ಕಿಟಕಿ_ಮುಖವಾಡ | Exposure_ಮುಖವಾಡ |
                          x11_keyboard_events | x11_ಸೂಚಕ_events |
                          Property_Change_ಮುಖವಾಡ | Structure_Notify_ಮುಖವಾಡ |
                          Keymap_State_ಮುಖವಾಡ | fevent));
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_ಕಿಟಕಿ_Bordered(Display *display, ಪೂರ್ಣಾಂಕ screen, ಕಿಟಕಿ_2 ಕಿಟಕಿ, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    ಆದರೆ (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        ರಚನೆ
        {
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ flags;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ functions;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ decorations;
            ದೀರ್ಘ ಒಳಹರಿವು_ಬಹುಲಕ;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸ್ಥಿತಿ_2;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, ಕಿಟಕಿ, WM_HINTS, WM_HINTS, 32,
                            Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&MWMHints,
                            ಗಾತ್ರ(MWMHints) / ಗಾತ್ರ(ದೀರ್ಘ));
    } ಇಲ್ಲದಿದ್ದರೆ { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, ಕಿಟಕಿ, ಬೇರು_ಕಿಟಕಿ(display, screen));
    }
}

bool X11_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    ಕಿಟಕಿ_2 w = (ಕಿಟಕಿ_2)SDL_Get_ಸಂಖ್ಯೆ_Property(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_X11_ಕಿಟಕಿ_ಸಂಖ್ಯೆ,
                (ಕಿಟಕಿ_2)SDL_Get_ಸೂಚಕ_Property(create_props, "sdl2-compat.external_window", ಖಾಲಿ));
    ಆದರೆ (w) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_EXTERNAL;

        ಆದರೆ (!ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(_this, ಕಿಟಕಿ, w)) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_ಕಿಟಕಿ_ಒಳಹರಿವು, true)) {
            ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ಒಳಹರಿವು(_this, ಕಿಟಕಿ);
        }
        ಹಿಂತಿರುಗಿ true;
    }

    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಆದರೆ (!displaydata) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not find display info");
    }

    ಸ್ಥಿರಾಂಕ bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ಸ್ಥಿರಾಂಕ bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata;
    Display *display = ದತ್ತಾಂಶ->display;
    ಪೂರ್ಣಾಂಕ screen = displaydata->screen;
    Visual *visual;
    ಪೂರ್ಣಾಂಕ ಆಳ_2;
    XSet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_ಕಿಟಕಿ_TYPE;
    Atom wintype;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *wintype_name = ಖಾಲಿ;
    ದೀರ್ಘ compositor = 1;
    Atom _NET_WM_PID;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ win_x, win_y;
    bool undefined_position = false;

#ಆದರೆ defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ transparent = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) ? true : false;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_ಕಿಟಕಿ_VISUALID);
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    ಆದರೆ (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, ಮಾದರಿ;
        ಪೂರ್ಣಾಂಕ nvis;

        SDL_zero(ಮಾದರಿ);
        ಮಾದರಿ.visualid = SDL_strtol(forced_visual_id, ಖಾಲಿ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ಮಾದರಿ, &nvis);
        ಆದರೆ (vi) {
            visual = vi->visual;
            ಆಳ_2 = vi->ಆಳ_2;
            X11_XFree(vi);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = ಖಾಲಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (((_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_ದತ್ತಾಂಶ || X11_GL_UseEGL(_this))
#ಆದರೆ_ಅಂತ್ಯ
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#ಆದರೆ_ಅಂತ್ಯ
        }

        ಆದರೆ (!vinfo) {
            ಹಿಂತಿರುಗಿ false;
        }
        visual = vinfo->visual;
        ಆಳ_2 = vinfo->ಆಳ_2;
        X11_XFree(vinfo);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        visual = displaydata->visual;
        ಆಳ_2 = displaydata->ಆಳ_2;
    }

    xattr.override_redirect = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TOOLTIP) || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    ಆದರೆ (visual->class == ನೇರ_Color) {
        XColor *colorcells;
        ಪೂರ್ಣಾಂಕ i;
        ಪೂರ್ಣಾಂಕ ncolors;
        ಪೂರ್ಣಾಂಕ rmax, gmax, bmax;
        ಪೂರ್ಣಾಂಕ rmask, gmask, bmask;
        ಪೂರ್ಣಾಂಕ rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, ಬೇರು_ಕಿಟಕಿ(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        ಆದರೆ (!xattr.colormap) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * ಗಾತ್ರ(XColor));
        ಆದರೆ (!colorcells) {
            ಹಿಂತಿರುಗಿ false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_ಮುಖವಾಡ;
        ಆಗ (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_ಮುಖವಾಡ;
        ಆಗ (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_ಮುಖವಾಡ;
        ಆಗ (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        ಗಾಗಿ (i = 0; i < ncolors; i++) {
            Uint32 red = (rmax * i) / (ncolors - 1);
            Uint32 green = (gmax * i) / (ncolors - 1);
            Uint32 blue = (bmax * i) / (ncolors - 1);

            Uint32 rbits = (rmask * i) / (ncolors - 1);
            Uint32 gbits = (gmask * i) / (ncolors - 1);
            Uint32 bbits = (bmask * i) / (ncolors - 1);

            Uint32 pix =
                (rbits << rshift) | (gbits << gshift) | (bbits << bshift);

            colorcells[i].pixel = pix;

            colorcells[i].red = red;
            colorcells[i].green = green;
            colorcells[i].blue = blue;

            colorcells[i].flags = DoRed | DoGreen | DoBlue;
        }

        X11_XStoreColors(display, xattr.colormap, colorcells, ncolors);

        SDL_free(colorcells);
    } ಇಲ್ಲದಿದ್ದರೆ {
        xattr.colormap =
            X11_XCreateColormap(display, ಬೇರು_ಕಿಟಕಿ(display, screen),
                                visual, AllocNone);
    }

    ಆದರೆ (ಕಿಟಕಿ->undefined_x && ಕಿಟಕಿ->undefined_y &&
        ಕಿಟಕಿ->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        X11_ConstrainPopup(ಕಿಟಕಿ, false);
    }
    SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ,
                                  ಕಿಟಕಿ->floating.x, ಕಿಟಕಿ->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_ಕಿಟಕಿ(display, ಬೇರು_ಕಿಟಕಿ(display, screen),
                          win_x, win_y, ಕಿಟಕಿ->floating.w, ಕಿಟಕಿ->floating.h,
                          0, ಆಳ_2, ಒಳಹರಿವು_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    ಆದರೆ (!w) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    ಆದರೆ (!(ಕಿಟಕಿ->pending_flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಗಣ_ಕಿಟಕಿ_Bordered(display, screen, w, !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS));
    }

    sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
        sizehints->min_ಅಗಲ_2 = sizehints->max_ಅಗಲ_2 = ಕಿಟಕಿ->floating.w;
        sizehints->min_ಎತ್ತರ_2 = sizehints->max_ಎತ್ತರ_2 = ಕಿಟಕಿ->floating.h;
        sizehints->flags |= (PMax_ಗಾತ್ರ | PMin_ಗಾತ್ರ);
    }
    ಆದರೆ (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->ಒಳಹರಿವು = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE) ? True : False;
    wmhints->ಕಿಟಕಿ_ಗುಂಪು = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಗುಂಪು;
    wmhints->flags = ಒಳಹರಿವು_Hint | ಕಿಟಕಿ_ಗುಂಪು_Hint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (ಅಕ್ಷರ *)SDL_GetExeName();
    classhints->res_class = (ಅಕ್ಷರ *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    ಆದರೆ (ದತ್ತಾಂಶ->pid > 0) {
        ದೀರ್ಘ pid = (ದೀರ್ಘ)ದತ್ತಾಂಶ->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_ಬಹುಲಕ_Replace,
                            (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&pid, 1);
    }

    // Set the window manager state
    X11_ಗಣ_Net_WMState(_this, w, ಕಿಟಕಿ->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_ಕಿಟಕಿ_TYPE);
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hint && *hint) {
        wintype_name = hint;
    } ಇಲ್ಲದಿದ್ದರೆ {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_ಕಿಟಕಿ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_ಕಿಟಕಿ_TYPE, XA_ATOM, 32,
                        Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&wintype, 1);
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_ಬಹುಲಕ_Replace,
                            (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&compositor, 1);
    }

    {
        Atom protocols[4];
        ಪೂರ್ಣಾಂಕ proto_ಎಣಿಕೆ = 0;

        protocols[proto_ಎಣಿಕೆ++] = ದತ್ತಾಂಶ->atoms.WM_DELETE_ಕಿಟಕಿ; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_ಎಣಿಕೆ++] = ದತ್ತಾಂಶ->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
        ಆದರೆ (use_resize_sync) {
            protocols[proto_ಎಣಿಕೆ++] = ದತ್ತಾಂಶ->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_ಎಣಿಕೆ <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_ಎಣಿಕೆ);
    }

    ಆದರೆ (!ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ದತ್ತಾಂಶ(_this, ಕಿಟಕಿ, w)) {
        X11_XDestroy_ಕಿಟಕಿ(display, w);
        ಹಿಂತಿರುಗಿ false;
    }
    windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // Set the parent if this is a non-popup window.
    ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ) && ಕಿಟಕಿ->ಪೋಷಕ) {
        X11_XSetTransientForHint(display, w, ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(ಕಿಟಕಿ->pending_flags & SDL_ಕಿಟಕಿ_FULLSCREEN) &&
                                               !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    ಆದರೆ (use_resize_sync) {
        X11_InitResizeSync(ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_ಒಳಹರಿವು, 0, 0, region, Shape_ಗಣ);
        X11_XDestroyRegion(region);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಸಿದ್ಧತೆ_ಕಿಟಕಿ_ಒಳಹರಿವು(_this, ಕಿಟಕಿ);

    // For _ICC_PROFILE.
    X11_XSelect_ಒಳಹರಿವು(display, ಬೇರು_ಕಿಟಕಿ(display, screen), Property_Change_ಮುಖವಾಡ);

    X11_XFlush(display);

    ಹಿಂತಿರುಗಿ true;
}

ಅಕ್ಷರ *X11_Get_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, ಕಿಟಕಿ_2 xwindow)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->display;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2, real_format;
    Atom real_type;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read, ವಸ್ತುಗಳು_ಎಡ;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata;
    ಅಕ್ಷರ *title = ಖಾಲಿ;

    ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, xwindow, ದತ್ತಾಂಶ->atoms._NET_WM_NAME,
                                    0L, 8192L, False, ದತ್ತಾಂಶ->atoms.UTF8_STRING, &real_type, &real_format,
                                    &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(ಅಕ್ಷರ *, propdata));
        X11_XFree(propdata);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
        ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(ಅಕ್ಷರ *, propdata), ವಸ್ತುಗಳು_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    ಹಿಂತಿರುಗಿ title;
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಕಿಟಕಿ_2 xwindow = ದತ್ತಾಂಶ->xwindow;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಅಕ್ಷರ *title = ಕಿಟಕಿ->title ? ಕಿಟಕಿ->title : "";

    SDL_X11_ಗಣ_ಕಿಟಕಿ_Title(display, xwindow, title);
}

ಸ್ಥಿರ bool caught_x11_error = false;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ExternalResizeMoveSync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಪೂರ್ಣಾಂಕ (*prev_handler)(Display *, XErrorEvent *);
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮಗು_ಎಣಿಕೆ;
    ಕಿಟಕಿ_2 ಮಗು_Return_2, ಬೇರು, ಪೋಷಕ;
    ಕಿಟಕಿ_2 *children;
    XWindow_ಗುಣಲಕ್ಷಣಗಳು attrs;
    Uint64 timeout = 0;
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ bool send_move = !!(ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_MOVE);
    ಸ್ಥಿರಾಂಕ bool send_resize = !!(ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_ವೃಕ್ಷ(display, ದತ್ತಾಂಶ->xwindow, &ಬೇರು, &ಪೋಷಕ, &children, &ಮಗು_ಎಣಿಕೆ);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_ಗಮ್ಯ_NS(100);
    ಆಗ (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ದತ್ತಾಂಶ->xwindow, &attrs);
        X11_XTranslateCoordinates(display, ಪೋಷಕ, Default_ಬೇರು_ಕಿಟಕಿ(display),
                                  attrs.x, attrs.y, &x, &y, &ಮಗು_Return_2);
        SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(ಕಿಟಕಿ, x, y, &x, &y);

        ಆದರೆ (!caught_x11_error) {
            ಆದರೆ ((ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_MOVE) && (x == ದತ್ತಾಂಶ->expected.x + ದತ್ತಾಂಶ->border_ಎಡ && y == ದತ್ತಾಂಶ->expected.y + ದತ್ತಾಂಶ->border_ತುದಿ)) {
                ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            ಆದರೆ ((ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.ಅಗಲ == ದತ್ತಾಂಶ->expected.w && attrs.ಎತ್ತರ == ದತ್ತಾಂಶ->expected.h)) {
                ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            ಆದರೆ (ದತ್ತಾಂಶ->pending_operation == X11_PENDING_OP_NONE) {
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ದತ್ತಾಂಶ->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            ದತ್ತಾಂಶ->expected.x = x;
            ದತ್ತಾಂಶ->expected.y = y;
            ದತ್ತಾಂಶ->expected.w = attrs.ಅಗಲ;
            ದತ್ತಾಂಶ->expected.h = attrs.ಎತ್ತರ;
            ನಿಲ್ಲಿಸು;
        }

        SDL_Delay(10);
    }

    ಆದರೆ (!caught_x11_error) {
        ಆದರೆ (send_move) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, x, y);
        }
        ಆದರೆ (send_resize) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, attrs.ಅಗಲ, attrs.ಎತ್ತರ);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ಸ್ಥಿರ bool X11_Sync_ಕಿಟಕಿ_Timeout(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, Uint64 param_timeout)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಪೂರ್ಣಾಂಕ (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool ಫಲಿತಾಂಶ = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    ಆದರೆ (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    ಆಗ (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        ಆದರೆ ((ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_MOVE) && (ಕಿಟಕಿ->x == ದತ್ತಾಂಶ->expected.x + ದತ್ತಾಂಶ->border_ಎಡ && ಕಿಟಕಿ->y == ದತ್ತಾಂಶ->expected.y + ದತ್ತಾಂಶ->border_ತುದಿ)) {
            ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        ಆದರೆ ((ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_RESIZE) && (ಕಿಟಕಿ->w == ದತ್ತಾಂಶ->expected.w && ಕಿಟಕಿ->h == ದತ್ತಾಂಶ->expected.h)) {
            ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->pending_operation == X11_PENDING_OP_NONE) {
            ಆದರೆ (force_exit ||
                (ಕಿಟಕಿ->x == ದತ್ತಾಂಶ->expected.x + ದತ್ತಾಂಶ->border_ಎಡ && ಕಿಟಕಿ->y == ದತ್ತಾಂಶ->expected.y + ದತ್ತಾಂಶ->border_ತುದಿ &&
                 ಕಿಟಕಿ->w == ದತ್ತಾಂಶ->expected.w && ಕಿಟಕಿ->h == ದತ್ತಾಂಶ->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                ನಿಲ್ಲಿಸು;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        ಆದರೆ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ದತ್ತಾಂಶ->expected.x = ಕಿಟಕಿ->x;
            ದತ್ತಾಂಶ->expected.y = ಕಿಟಕಿ->y;
            ದತ್ತಾಂಶ->expected.w = ಕಿಟಕಿ->w;
            ದತ್ತಾಂಶ->expected.h = ಕಿಟಕಿ->h;

            ಫಲಿತಾಂಶ = false;
            ನಿಲ್ಲಿಸು;
        }

        SDL_Delay(10);
    }

    ದತ್ತಾಂಶ->pending_operation = X11_PENDING_OP_NONE;

    ಆದರೆ (!caught_x11_error) {
        X11_PumpEvents(_this);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool X11_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom _NET_WM_ICON = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_ICON;
    ಪೂರ್ಣಾಂಕ (*prevHandler)(Display *, XErrorEvent *) = ಖಾಲಿ;
    bool ಫಲಿತಾಂಶ = true;

    ಆದರೆ (icon) {
        ಪೂರ್ಣಾಂಕ x, y;
        ಪೂರ್ಣಾಂಕ propsize;
        ದೀರ್ಘ *propdata;
        Uint32 *src;
        ದೀರ್ಘ *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * ಗಾತ್ರ(ದೀರ್ಘ));

        ಆದರೆ (!propdata) {
            ಹಿಂತಿರುಗಿ false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        ಗಾಗಿ (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            ಗಾಗಿ (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, ದತ್ತಾಂಶ->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)propdata,
                            propsize);
        SDL_free(propdata);

        ಆದರೆ (caught_x11_error) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    ಆದರೆ (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ X11_Update_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool use_current_position)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rel_x = use_current_position ? ಕಿಟಕಿ->x : ಕಿಟಕಿ->pending.x;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rel_y = use_current_position ? ಕಿಟಕಿ->y : ಕಿಟಕಿ->pending.y;

    SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ,
                                  rel_x - ದತ್ತಾಂಶ->border_ಎಡ, rel_y - ದತ್ತಾಂಶ->border_ತುದಿ,
                                  &ದತ್ತಾಂಶ->expected.x, &ದತ್ತಾಂಶ->expected.y);

    // Attempt to move the window
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಕಿಟಕಿ->ಆಂತರಿಕ->pending_position = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->expected.x, ದತ್ತಾಂಶ->expected.y);
    }
}

bool X11_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Sync any pending fullscreen or maximize events.
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, ಕಿಟಕಿ);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED) {
        ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_RESTORE) {
            ಕಿಟಕಿ->ಆಂತರಿಕ->pending_position = true;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
            X11_ConstrainPopup(ಕಿಟಕಿ, true);
        }
        X11_Update_ಕಿಟಕಿ_Position(ಕಿಟಕಿ, false);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->ಆಂತರಿಕ->fs_repositioned = true;
        SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Min_Max(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool use_current)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
    ದೀರ್ಘ hint_flags = 0;

    X11_XGetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_ಗಾತ್ರ | PMax_ಗಾತ್ರ | PAspect);

    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) {
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_w || ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_h) {
            sizehints->flags |= PMin_ಗಾತ್ರ;
            sizehints->min_ಅಗಲ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_w;
            sizehints->min_ಎತ್ತರ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_h;
        }
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_w || ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_h) {
            sizehints->flags |= PMax_ಗಾತ್ರ;
            sizehints->max_ಅಗಲ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_w;
            sizehints->max_ಎತ್ತರ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_h;
        }
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect > 0.0f || ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(ದತ್ತಾಂಶ->ಕಿಟಕಿ->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(ದತ್ತಾಂಶ->ಕಿಟಕಿ->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_ಗಾತ್ರ | PMax_ಗಾತ್ರ;
        ಆದರೆ (use_current) {
            sizehints->min_ಅಗಲ_2 = sizehints->max_ಅಗಲ_2 = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ದತ್ತಾಂಶ->ಕಿಟಕಿ->floating.w;
            sizehints->min_ಎತ್ತರ_2 = sizehints->max_ಎತ್ತರ_2 = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ದತ್ತಾಂಶ->ಕಿಟಕಿ->floating.h;
        } ಇಲ್ಲದಿದ್ದರೆ {
            sizehints->min_ಅಗಲ_2 = sizehints->max_ಅಗಲ_2 = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ದತ್ತಾಂಶ->ಕಿಟಕಿ->windowed.w;
            sizehints->min_ಎತ್ತರ_2 = sizehints->max_ಎತ್ತರ_2 = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ದತ್ತಾಂಶ->ಕಿಟಕಿ->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints);
    X11_XFree(sizehints);
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, ಕಿಟಕಿ);
    }

    // Set the size as pending if the window is being restored.
    ಆದರೆ (ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        // New size will be set when the window is restored.
        ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_RESTORE) {
            ದತ್ತಾಂಶ->pending_ಗಾತ್ರ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Can't resize the window.
            ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = false;
        }
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
            ದೀರ್ಘ userhints;
            ಪೂರ್ಣಾಂಕ dest_x, dest_y;

            X11_XGetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints, &userhints);

            ದತ್ತಾಂಶ->expected.w = sizehints->min_ಅಗಲ_2 = sizehints->max_ಅಗಲ_2 = ಕಿಟಕಿ->pending.w;
            ದತ್ತಾಂಶ->expected.h = sizehints->min_ಎತ್ತರ_2 = sizehints->max_ಎತ್ತರ_2 = ಕಿಟಕಿ->pending.h;
            sizehints->flags |= PMin_ಗಾತ್ರ | PMax_ಗಾತ್ರ;
            ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints);

            /* From Pierre-Loup:
               WMs each have their little quirks with that.  When you change the
               size hints, they get a ConfigureNotify event with the
               WM_NORMAL_SIZE_HINTS Atom.  They all save the hints then, but they
               don't all resize the window right away to enforce the new hints.

               Some of them resize only after:
                - A user-initiated move or resize
                - A code-initiated move or resize
                - Hiding & showing window (Unmap & map)

               The following move & resize seems to help a lot of WMs that didn't
               properly update after the hints were changed. We don't do a
               hide/show, because there are supposedly subtle problems with doing so
               and transitioning from windowed to fullscreen in Unity.
             */
            X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ x = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->x;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->y;
            SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ,
                                          x - ದತ್ತಾಂಶ->border_ಎಡ,
                                          y - ದತ್ತಾಂಶ->border_ತುದಿ,
                                          &dest_x, &dest_y);
            X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, dest_x, dest_y);
            X11_XRaise_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow);

            X11_XFree(sizehints);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->expected.w = ಕಿಟಕಿ->pending.w;
        ದತ್ತಾಂಶ->expected.h = ಕಿಟಕಿ->pending.h;
        ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->expected.w, ದತ್ತಾಂಶ->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
    }
}

bool X11_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    *ಎಡ = ದತ್ತಾಂಶ->border_ಎಡ;
    *ಬಲ = ದತ್ತಾಂಶ->border_ಬಲ;
    *ತುದಿ = ದತ್ತಾಂಶ->border_ತುದಿ;
    *bottom = ದತ್ತಾಂಶ->border_bottom;

    ಹಿಂತಿರುಗಿ true;
}

bool X11_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom NET_WM_ಕಿಟಕಿ_OPACITY = ದತ್ತಾಂಶ->videodata->atoms.NET_WM_ಕಿಟಕಿ_OPACITY;

    ಆದರೆ (opacity == 1.0f) {
        X11_XDeleteProperty(display, ದತ್ತಾಂಶ->xwindow, NET_WM_ಕಿಟಕಿ_OPACITY);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ Uint32 FullyOpaque = 0xFFFFFFFF;
        ಸ್ಥಿರಾಂಕ ದೀರ್ಘ alpha = (ದೀರ್ಘ)((ದ್ವಿಗುಣ)opacity * (ದ್ವಿಗುಣ)FullyOpaque);
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->xwindow, NET_WM_ಕಿಟಕಿ_OPACITY, XA_CARDINAL, 32,
                            Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&alpha, 1);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool X11_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಪೋಷಕ_ದತ್ತಾಂಶ = ಪೋಷಕ ? ಪೋಷಕ->ಆಂತರಿಕ : ಖಾಲಿ;
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *display = video_ದತ್ತಾಂಶ->display;

    ಆದರೆ (ಪೋಷಕ_ದತ್ತಾಂಶ) {
        X11_XSetTransientForHint(display, ದತ್ತಾಂಶ->xwindow, ಪೋಷಕ_ದತ್ತಾಂಶ->xwindow);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XDeleteProperty(display, ದತ್ತಾಂಶ->xwindow, video_ದತ್ತಾಂಶ->atoms.WM_TRANSIENT_FOR);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool X11_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = video_ದತ್ತಾಂಶ->display;
    Uint32 flags = ಕಿಟಕಿ->flags;
    Atom _NET_WM_STATE = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_MODAL;

    ಆದರೆ (modal) {
        flags |= SDL_ಕಿಟಕಿ_MODAL;
    } ಇಲ್ಲದಿದ್ದರೆ {
        flags &= ~SDL_ಕಿಟಕಿ_MODAL;
        X11_XDeleteProperty(display, ದತ್ತಾಂಶ->xwindow, video_ದತ್ತಾಂಶ->atoms.WM_TRANSIENT_FOR);
    }

    ಆದರೆ (X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ಸಂದೇಶ;
        e.xclient.ಸಂದೇಶ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
        e.xclient.ದತ್ತಾಂಶ.l[0] = modal ? NET_WM_STATE_ಕೂಡಿಸು : _NET_WM_STATE_REMOVE;
        e.xclient.ದತ್ತಾಂಶ.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.ದತ್ತಾಂಶ.l[3] = 0l;

        X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                       Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_ಗಣ_Net_WMState(_this, ದತ್ತಾಂಶ->xwindow, flags);
    }

    X11_XFlush(display);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered)
{
    ಸ್ಥಿರಾಂಕ bool focused = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) != 0;
    ಸ್ಥಿರಾಂಕ bool visible = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) && !ಕಿಟಕಿ->is_hiding;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XEvent event;

    ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಗಣ_ಕಿಟಕಿ_Bordered(display, displaydata->screen, ದತ್ತಾಂಶ->xwindow, bordered);
        X11_XFlush(display);

        ಆದರೆ (visible) {
            XWindow_ಗುಣಲಕ್ಷಣಗಳು attr;
            ಮಾಡು {
                X11_XSync(display, False);
                X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ದತ್ತಾಂಶ->xwindow, &attr);
            } ಆಗ (attr.map_state != IsViewable);

            ಆದರೆ (focused) {
                X11_XSet_ಒಳಹರಿವು_Focus(display, ದತ್ತಾಂಶ->xwindow, Revert_ಗಮ್ಯ_ಪೋಷಕ, Current_ಸಮಯ);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&ದತ್ತಾಂಶ->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&ದತ್ತಾಂಶ->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_ಮೌಲ್ಯಗಳು(ದತ್ತಾಂಶ);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->floating.w, ಕಿಟಕಿ->floating.h);
        X11_XSync(display, False);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        ದತ್ತಾಂಶ->toggle_borders = true;
        ದತ್ತಾಂಶ->fullscreen_borders_forced_on = false;
    }
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom _NET_WM_STATE = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_ABOVE;

    ಆದರೆ (X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ಸಂದೇಶ;
        e.xclient.ಸಂದೇಶ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
        e.xclient.ದತ್ತಾಂಶ.l[0] =
            on_ತುದಿ ? NET_WM_STATE_ಕೂಡಿಸು : _NET_WM_STATE_REMOVE;
        e.xclient.ದತ್ತಾಂಶ.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.ದತ್ತಾಂಶ.l[3] = 0l;

        X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                       Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_ಗಣ_Net_WMState(_this, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->flags);
    }
    X11_XFlush(display);
}

ಶೂನ್ಯ X11_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ACTIVATE_WHEN_SHOWN, true);
    bool ಗಣ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    ಆದರೆ (ದತ್ತಾಂಶ->was_shown) {
        X11_PumpEvents(_this);
    }

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(ಕಿಟಕಿ, true);
        ದತ್ತಾಂಶ->pending_position = true;
        ಗಣ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (ಶೂನ್ಯ)bActivate;

    ಆದರೆ (!X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        X11_XMapRaised(display, ದತ್ತಾಂಶ->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&ದತ್ತಾಂಶ->xwindow);
        }
        X11_XFlush(display);
        ಗಣ_position = ದತ್ತಾಂಶ->pending_position ||
                       (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) && !ಕಿಟಕಿ->undefined_x && !ಕಿಟಕಿ->undefined_y);
    }

    ಆದರೆ (!ದತ್ತಾಂಶ->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_ಒಳಹರಿವು_Focus(display, ದತ್ತಾಂಶ->xwindow, Revert_ಗಮ್ಯ_None, Current_ಸಮಯ);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
        X11_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
    }

    // Get some valid border values, if we haven't received them yet
    ಆದರೆ (ದತ್ತಾಂಶ->border_ಎಡ == 0 && ದತ್ತಾಂಶ->border_ಬಲ == 0 && ದತ್ತಾಂಶ->border_ತುದಿ == 0 && ದತ್ತಾಂಶ->border_bottom == 0) {
        X11_Get_Border_ಮೌಲ್ಯಗಳು(ದತ್ತಾಂಶ);
    }

    ಆದರೆ (ಗಣ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ tx = (ದತ್ತಾಂಶ->pending_position ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->x) - (ದತ್ತಾಂಶ->was_shown ? 0 : ದತ್ತಾಂಶ->border_ಎಡ);
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ty = (ದತ್ತಾಂಶ->pending_position ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->y) - (ದತ್ತಾಂಶ->was_shown ? 0 : ದತ್ತಾಂಶ->border_ತುದಿ);
        ಪೂರ್ಣಾಂಕ x, y;

        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, tx, ty, &x, &y);

        ದತ್ತಾಂಶ->pending_position = false;
        X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags = X11_ಗಾತ್ರ_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
    ದತ್ತಾಂಶ->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    ಆದರೆ (ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.type) {
        ಪೂರ್ಣಾಂಕ x, y;
        SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.x, ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.y, &x, &y);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.ಅಗಲ, ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.ಎತ್ತರ);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, x, y);
    }
}

ಶೂನ್ಯ X11_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಪೂರ್ಣಾಂಕ screen = (displaydata ? displaydata->screen : 0);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ಸ್ಥಿರಾಂಕ bool is_mapped = X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ);
    X11_XWithdraw_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, screen);
    ಆದರೆ (is_mapped && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&ದತ್ತಾಂಶ->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
        SDL_ಕಿಟಕಿ *new_focus;
        ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(ಕಿಟಕಿ, &new_focus);
        X11_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ಸ್ಥಿರ bool X11_ಗಣ_ಕಿಟಕಿ_ಸಕ್ರಿಯ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_ದತ್ತಾಂಶ(ಕಿಟಕಿ);

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom NET_ಸಕ್ರಿಯ_ಕಿಟಕಿ = ದತ್ತಾಂಶ->videodata->atoms.NET_ಸಕ್ರಿಯ_ಕಿಟಕಿ;

    ಆದರೆ (X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_ಸಂದೇಶ;
        e.xclient.ಸಂದೇಶ_type = NET_ಸಕ್ರಿಯ_ಕಿಟಕಿ;
        e.xclient.format = 32;
        e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
        e.xclient.ದತ್ತಾಂಶ.l[0] = 1; // source indication. 1 = application
        e.xclient.ದತ್ತಾಂಶ.l[1] = ದತ್ತಾಂಶ->user_ಸಮಯ;
        e.xclient.ದತ್ತಾಂಶ.l[2] = 0;

        X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                       Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);

        X11_XFlush(display);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow);
    ಆದರೆ (bActivate) {
        X11_ಗಣ_ಕಿಟಕಿ_ಸಕ್ರಿಯ(_this, ಕಿಟಕಿ);
    }
    X11_XFlush(display);
}

ಸ್ಥಿರ bool X11_ಗಣ_ಕಿಟಕಿ_Maximized(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool maximized)
{
    CHECK_ಕಿಟಕಿ_ದತ್ತಾಂಶ(ಕಿಟಕಿ);

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom _NET_WM_STATE = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ಸಂದೇಶ;
        e.xclient.ಸಂದೇಶ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
        e.xclient.ದತ್ತಾಂಶ.l[0] =
            maximized ? NET_WM_STATE_ಕೂಡಿಸು : _NET_WM_STATE_REMOVE;
        e.xclient.ದತ್ತಾಂಶ.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.ದತ್ತಾಂಶ.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.ದತ್ತಾಂಶ.l[3] = 0l;

        ಆದರೆ (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            ದತ್ತಾಂಶ->expected.x = bounds.x + ದತ್ತಾಂಶ->border_ಎಡ;
            ದತ್ತಾಂಶ->expected.y = bounds.y + ದತ್ತಾಂಶ->border_ತುದಿ;
            ದತ್ತಾಂಶ->expected.w = bounds.w - (ದತ್ತಾಂಶ->border_ಎಡ + ದತ್ತಾಂಶ->border_ಬಲ);
            ದತ್ತಾಂಶ->expected.h = bounds.h - (ದತ್ತಾಂಶ->border_ತುದಿ + ದತ್ತಾಂಶ->border_bottom);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->expected.x = ಕಿಟಕಿ->floating.x;
            ದತ್ತಾಂಶ->expected.y = ಕಿಟಕಿ->floating.y;
            ದತ್ತಾಂಶ->expected.w = ಕಿಟಕಿ->floating.w;
            ದತ್ತಾಂಶ->expected.h = ಕಿಟಕಿ->floating.h;
        }

        X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                       Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_ಗಣ_Net_WMState(_this, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->flags);
    }
    X11_XFlush(display);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        ಕಿಟಕಿ->ಆಂತರಿಕ->ಕಿಟಕಿ_was_maximized = true;
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_ಗಣ_ಕಿಟಕಿ_Maximized(_this, ಕಿಟಕಿ, true);
    }
}

ಶೂನ್ಯ X11_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        SDL_Sync_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }

    ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MINIMIZE;
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_was_maximized = !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED);
    }
    X11_XIconify_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, displaydata->screen);
    X11_XFlush(display);
}

ಶೂನ್ಯ X11_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Don't restore the window the first time it is being shown.
    ಆದರೆ (!ಕಿಟಕಿ->ಆಂತರಿಕ->was_shown) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        ಕಿಟಕಿ->ಆಂತರಿಕ->ಕಿಟಕಿ_was_maximized = false;
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_MAXIMIZED) ||
        (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ಸ್ಥಿರಾಂಕ bool maximize = !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) && ಕಿಟಕಿ->ಆಂತರಿಕ->ಕಿಟಕಿ_was_maximized;
    X11_ಗಣ_ಕಿಟಕಿ_Maximized(_this, ಕಿಟಕಿ, maximize);
    X11_Show_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    X11_ಗಣ_ಕಿಟಕಿ_ಸಕ್ರಿಯ(_this, ಕಿಟಕಿ);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ಸ್ಥಿರ SDL_Fullscreen_ಫಲಿತಾಂಶ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen_ಮೂಲಕ_WM(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = _display->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom _NET_WM_STATE = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    ಆದರೆ (!ದತ್ತಾಂಶ->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಆದರೆ (X11_Is_ಕಿಟಕಿ_Mapped(_this, ಕಿಟಕಿ)) {
        XEvent e;

        // Flush any pending fullscreen events.
        ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
        }

        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
            ಆದರೆ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        ಆದರೆ (fullscreen && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
            ದೀರ್ಘ flags = 0;
            X11_XGetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ಗಾತ್ರ | PMax_ಗಾತ್ರ | PAspect);
            X11_XSetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_ಸಂದೇಶ;
        e.xclient.ಸಂದೇಶ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
        e.xclient.ದತ್ತಾಂಶ.l[0] =
            fullscreen ? NET_WM_STATE_ಕೂಡಿಸು : _NET_WM_STATE_REMOVE;
        e.xclient.ದತ್ತಾಂಶ.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.ದತ್ತಾಂಶ.l[3] = 0l;

        X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                       Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        ಆದರೆ (((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) != 0) != (fullscreen != 0)) {
            ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        ಆದರೆ (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_ಕಿಟಕಿ_Position(ಕಿಟಕಿ);
            SDL_copyp(&ದತ್ತಾಂಶ->requested_fullscreen_ಬಹುಲಕ, &ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
            ಆದರೆ (fullscreen != !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
                ದತ್ತಾಂಶ->ಕಿಟಕಿ_was_maximized = !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED);
            }
            ದತ್ತಾಂಶ->expected.x = displaydata->x;
            ದತ್ತಾಂಶ->expected.y = displaydata->y;
            ದತ್ತಾಂಶ->expected.w = _display->current_ಬಹುಲಕ->w;
            ದತ್ತಾಂಶ->expected.h = _display->current_ಬಹುಲಕ->h;

            // Only move the window if it isn't already on the target display.
            ಆದರೆ (!current || current != _display->id) {
                X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, displaydata->x, displaydata->y);
                ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_zero(ದತ್ತಾಂಶ->requested_fullscreen_ಬಹುಲಕ);
            ದತ್ತಾಂಶ->pending_position = ದತ್ತಾಂಶ->fs_repositioned;
            ದತ್ತಾಂಶ->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_ಸಂದೇಶ;
            e.xclient.ಸಂದೇಶ_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
            ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ_was_maximized) {
                e.xclient.ದತ್ತಾಂಶ.l[0] = NET_WM_STATE_ಕೂಡಿಸು;
            } ಇಲ್ಲದಿದ್ದರೆ {
                e.xclient.ದತ್ತಾಂಶ.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.ದತ್ತಾಂಶ.l[1] = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.ದತ್ತಾಂಶ.l[2] = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.ದತ್ತಾಂಶ.l[3] = 0l;
            X11_XSendEvent(display, ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen), 0,
                           Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, &e);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಕಿಟಕಿ_Flags flags;

        flags = ಕಿಟಕಿ->flags;
        ಆದರೆ (fullscreen) {
            flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            flags &= ~SDL_ಕಿಟಕಿ_FULLSCREEN;
        }
        X11_ಗಣ_Net_WMState(_this, ದತ್ತಾಂಶ->xwindow, flags);
    }

    ಆದರೆ (ದತ್ತಾಂಶ->visual->class == ನೇರ_Color) {
        ಆದರೆ (fullscreen) {
            X11_XInstallColormap(display, ದತ್ತಾಂಶ->colormap);
        } ಇಲ್ಲದಿದ್ದರೆ {
            X11_XUninstallColormap(display, ದತ್ತಾಂಶ->colormap);
        }
    }

    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
}

ಸ್ಥಿರ SDL_Fullscreen_ಫಲಿತಾಂಶ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = _display->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screen = displaydata->screen;

    ಆದರೆ (!ದತ್ತಾಂಶ->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    ಆದರೆ (ದತ್ತಾಂಶ->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, fullscreen ? SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN : SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
    ಆದರೆ (fullscreen) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
            ದೀರ್ಘ flags = 0;
            X11_XGetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ಗಾತ್ರ | PMax_ಗಾತ್ರ | PAspect);
            X11_XSetWMNormalHints(display, ದತ್ತಾಂಶ->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        ಗಣ_ಕಿಟಕಿ_Bordered(display, screen, ದತ್ತಾಂಶ->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ದತ್ತಾಂಶ->expected.x = rect.x;
        ದತ್ತಾಂಶ->expected.y = rect.y;
        ದತ್ತಾಂಶ->expected.w = rect.w;
        ದತ್ತಾಂಶ->expected.h = rect.h;
        X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, rect.x, rect.y);
        X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, rect.w, rect.h);
        X11_XRaise_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ದತ್ತಾಂಶ->expected.x = ಕಿಟಕಿ->windowed.x;
        ದತ್ತಾಂಶ->expected.y = ಕಿಟಕಿ->windowed.y;
        ದತ್ತಾಂಶ->expected.w = ಕಿಟಕಿ->windowed.w;
        ದತ್ತಾಂಶ->expected.h = ಕಿಟಕಿ->windowed.h;
        X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->windowed.w, ಕಿಟಕಿ->windowed.h);
        X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ಕಿಟಕಿ->windowed.x, ಕಿಟಕಿ->windowed.y);

        ಗಣ_ಕಿಟಕಿ_Bordered(display, screen, ದತ್ತಾಂಶ->xwindow, (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) == 0);
        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ದತ್ತಾಂಶ->ಕಿಟಕಿ, false);
    }

    X11_XFlush(display);

    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_ಫಲಿತಾಂಶ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_ಕಿಟಕಿ_ದತ್ತಾಂಶ(ಕಿಟಕಿ);
    CHECK_DISPLAY_ದತ್ತಾಂಶ(_display);

    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->net_wm) {
        ಹಿಂತಿರುಗಿ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen_ಮೂಲಕ_WM(_this, ಕಿಟಕಿ, _display, fullscreen);
    }

    ಹಿಂತಿರುಗಿ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen_Legacy(_this, ಕಿಟಕಿ, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ format, ಎಣಿಕೆ_2;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ಸ್ಥಿರ ಶೂನ್ಯ X11_ReadProperty(SDL_x11Prop *p, Display *disp, ಕಿಟಕಿ_2 w, Atom prop)
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ret = ಖಾಲಿ;
    Atom type;
    ಪೂರ್ಣಾಂಕ fmt;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಎಣಿಕೆ_2;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_ಎಡ;
    ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_fetch = 0;

    ಮಾಡು {
        ಆದರೆ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_ಕಿಟಕಿ_Property(disp, w, prop, 0, ಬೈಟುಗಳು_fetch, False, AnyPropertyType, &type, &fmt, &ಎಣಿಕೆ_2, &ಬೈಟುಗಳು_ಎಡ, &ret);
        ಬೈಟುಗಳು_fetch += ಬೈಟುಗಳು_ಎಡ;
    } ಆಗ (ಬೈಟುಗಳು_ಎಡ != 0);

    p->ದತ್ತಾಂಶ = ret;
    p->format = fmt;
    p->ಎಣಿಕೆ_2 = ಎಣಿಕೆ_2;
    p->type = type;
}

ಶೂನ್ಯ *X11_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XWindow_ಗುಣಲಕ್ಷಣಗಳು ಗುಣಲಕ್ಷಣಗಳು;
    Atom icc_profile_atom;
    ಅಕ್ಷರ icc_atom_string[ಗಾತ್ರ("_ICC_PROFILE_") + 12];
    ಶೂನ್ಯ *ret_icc_profile_ದತ್ತಾಂಶ = ಖಾಲಿ;
    CARD8 *icc_profile_ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ real_format;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ದತ್ತಾಂಶ->xwindow, &ಗುಣಲಕ್ಷಣಗಳು);
    ಆದರೆ (X11_XScreen_ಸಂಖ್ಯೆ_ದ_Screen(ಗುಣಲಕ್ಷಣಗಳು.screen) > 0) {
        (ಶೂನ್ಯ)SDL_snprintf(icc_atom_string, ಗಾತ್ರ("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_ಸಂಖ್ಯೆ_ದ_Screen(ಗುಣಲಕ್ಷಣಗಳು.screen));
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", ಗಾತ್ರ("_ICC_PROFILE"));
    }
    X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ಬೇರು_ಕಿಟಕಿ_ದ_Screen(ಗುಣಲಕ್ಷಣಗಳು.screen), &ಗುಣಲಕ್ಷಣಗಳು);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    ಆದರೆ (icc_profile_atom == None) {
        SDL_ಗಣ_Error("Screen is not calibrated.");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    X11_ReadProperty(&atomProp, display, ಬೇರು_ಕಿಟಕಿ_ದ_Screen(ಗುಣಲಕ್ಷಣಗಳು.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.ಎಣಿಕೆ_2;
    icc_profile_ದತ್ತಾಂಶ = atomProp.ದತ್ತಾಂಶ;
    ಆದರೆ (real_format == None) {
        SDL_ಗಣ_Error("Screen is not calibrated.");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ret_icc_profile_ದತ್ತಾಂಶ = SDL_malloc(real_nitems);
    ಆದರೆ (!ret_icc_profile_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_memcpy(ret_icc_profile_ದತ್ತಾಂಶ, icc_profile_ದತ್ತಾಂಶ, real_nitems);
    *ಗಾತ್ರ_2 = real_nitems;
    X11_XFree(icc_profile_ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ ret_icc_profile_ದತ್ತಾಂಶ;
}

bool X11_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid window data");
    }
    ದತ್ತಾಂಶ->mouse_grabbed = false;
    ದತ್ತಾಂಶ->pending_grab = false;

    display = ದತ್ತಾಂಶ->videodata->display;

    ಆದರೆ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
            ಹಿಂತಿರುಗಿ true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_mouse_enabled && SDL_GetMouseState(ಖಾಲಿ, ಖಾಲಿ)) {
            ದತ್ತಾಂಶ->pending_grab = true;
            ಹಿಂತಿರುಗಿ true;
        }

        // Try to grab the mouse
        ಆದರೆ (!ದತ್ತಾಂಶ->videodata->broken_ಸೂಚಕ_grab) {
            ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = Button_Press_ಮುಖವಾಡ | Button_Release_ಮುಖವಾಡ | ಸೂಚಕ_Motion_ಮುಖವಾಡ | Focus_Change_ಮುಖವಾಡ;
            ಪೂರ್ಣಾಂಕ attempts;
            ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            ಗಾಗಿ (attempts = 0; attempts < 100; attempts++) {
                ಫಲಿತಾಂಶ = X11_XGrab_ಸೂಚಕ(display, ದತ್ತಾಂಶ->xwindow, False, ಮುಖವಾಡ, Grab_ಬಹುಲಕ_Async,
                                          Grab_ಬಹುಲಕ_Async, ದತ್ತಾಂಶ->xwindow, None, Current_ಸಮಯ);
                ಆದರೆ (ಫಲಿತಾಂಶ == GrabSuccess) {
                    ದತ್ತಾಂಶ->mouse_grabbed = true;
                    ನಿಲ್ಲಿಸು;
                }
                SDL_Delay(50);
            }

            ಆದರೆ (ಫಲಿತಾಂಶ != GrabSuccess) {
                ದತ್ತಾಂಶ->videodata->broken_ಸೂಚಕ_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, ಕಿಟಕಿ);

        // Raise the window if we grab the mouse
        X11_XRaise_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XUngrab_ಸೂಚಕ(display, Current_ಸಮಯ);

        X11_Xinput2UngrabTouch(_this, ಕಿಟಕಿ);
    }
    X11_XSync(display, False);

    ಆದರೆ (!ದತ್ತಾಂಶ->videodata->broken_ಸೂಚಕ_grab) {
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid window data");
    }

    display = ದತ್ತಾಂಶ->videodata->display;

    ಆದರೆ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
            ಹಿಂತಿರುಗಿ true;
        }

        /* GNOME needs the _XWAYLAND_MAY_GRAB_KEYBOARD message on XWayland:
         *
         * - message_type set to "_XWAYLAND_MAY_GRAB_KEYBOARD"
         * - window set to the xid of the window on which the grab is to be issued
         * - data.l[0] to a non-zero value
         *
         * The dconf setting `org/gnome/mutter/wayland/xwayland-allow-grabs` must be enabled as well.
         *
         * https://gitlab.gnome.org/GNOME/mutter/-/commit/5f132f39750f684c3732b4346dec810cd218d609
         */
        ಆದರೆ (_this->ಆಂತರಿಕ->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            ಆದರೆ (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_ಸಂದೇಶ_Event client_ಸಂದೇಶ;
                client_ಸಂದೇಶ.type = Client_ಸಂದೇಶ;
                client_ಸಂದೇಶ.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
                client_ಸಂದೇಶ.format = 32;
                client_ಸಂದೇಶ.ಸಂದೇಶ_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_ಸಂದೇಶ.ದತ್ತಾಂಶ.l[0] = 1;
                client_ಸಂದೇಶ.ದತ್ತಾಂಶ.l[1] = Current_ಸಮಯ;

                X11_XSendEvent(display, Default_ಬೇರು_ಕಿಟಕಿ(display), False, Substructure_Notify_ಮುಖವಾಡ | Substructure_Redirect_ಮುಖವಾಡ, (XEvent *)&client_ಸಂದೇಶ);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, ದತ್ತಾಂಶ->xwindow, True, Grab_ಬಹುಲಕ_Async,
                          Grab_ಬಹುಲಕ_Async, Current_ಸಮಯ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XUngrabKeyboard(display, Current_ಸಮಯ);
    }
    X11_XSync(display, False);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ) {
        SDL_Video_ದತ್ತಾಂಶ *videodata = ದತ್ತಾಂಶ->videodata;
        Display *display = videodata->display;
        ಪೂರ್ಣಾಂಕ numwindows = videodata->numwindows;
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ **windowlist = videodata->windowlist;
        ಪೂರ್ಣಾಂಕ i;

        ಆದರೆ (windowlist) {
            ಗಾಗಿ (i = 0; i < numwindows; ++i) {
                ಆದರೆ (windowlist[i] && (windowlist[i]->ಕಿಟಕಿ == ಕಿಟಕಿ)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = ಖಾಲಿ;
                    videodata->numwindows--;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }

        X11_Destroy_ಒಳಹರಿವು_Context(ದತ್ತಾಂಶ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_ಪದ_Resize_Sync(ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
            X11_XDestroy_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow);
            X11_XFlush(display);
        }
        SDL_free(ದತ್ತಾಂಶ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        ಆದರೆ (videodata->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ == ಕಿಟಕಿ) {
            X11_Destroy_ಸೂಚಕ_Barrier(_this, ಕಿಟಕಿ);
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

bool X11_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled)
{
    ಹಿಂತಿರುಗಿ true; // just succeed, the real work is done elsewhere.
}

ಶೂನ್ಯ X11_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom XdndAware = ದತ್ತಾಂಶ->videodata->atoms.XdndAware;

    ಆದರೆ (accept) {
        Atom xdnd_ಆವೃತ್ತಿ = 5;
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&xdnd_ಆವೃತ್ತಿ, 1);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XDeleteProperty(display, ದತ್ತಾಂಶ->xwindow, XdndAware);
    }
}

bool X11_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, ದತ್ತಾಂಶ->xwindow);
    ಆದರೆ (!wmhints) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    ದತ್ತಾಂಶ->flashing_ಕಿಟಕಿ = false;
    ದತ್ತಾಂಶ->flash_cancel_ಸಮಯ = 0;

    ಆಯ್ಕೆ (operation) {
    ಸ್ಥಿತಿ SDL_FLASH_CANCEL:
        // Taken care of above
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLASH_BRIEFLY:
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ದತ್ತಾಂಶ->flashing_ಕಿಟಕಿ = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            ದತ್ತಾಂಶ->flash_cancel_ಸಮಯ = SDL_GetTicks() + 1000;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_FLASH_UNTIL_FOCUSED:
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ದತ್ತಾಂಶ->flashing_ಕಿಟಕಿ = true;
        }
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    X11_XSetWMHints(display, ದತ್ತಾಂಶ->xwindow, wmhints);
    X11_XFree(wmhints);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_X11_ಗಣ_ಕಿಟಕಿ_Title(Display *display, ಕಿಟಕಿ_2 xwindow, ಅಕ್ಷರ *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    ಪೂರ್ಣಾಂಕ conv = X11_Xmb_ಪಠ್ಯ_List_ಗಮ್ಯ_ಪಠ್ಯ_Property(display, &title, 1, XTextStyle, &titleprop);
    ಸ್ಥಿತಿ_3 ಸ್ಥಿತಿ_2;

    ಆದರೆ (X11_XSupportsLocale() != True) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Current locale not supported by X server, cannot continue.");
    }

    ಆದರೆ (conv == 0) {
        X11_XSet_ಪಠ್ಯ_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.ಮೌಲ್ಯ);
        // we know this can't be a locale error as we checked X locale validity
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (conv < 0) {
        ಹಿಂತಿರುಗಿ SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
    } ಇಲ್ಲದಿದ್ದರೆ { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        ಹಿಂತಿರುಗಿ true;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಸ್ಥಿತಿ_2 = X11_Xutf8_ಪಠ್ಯ_List_ಗಮ್ಯ_ಪಠ್ಯ_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == Success) {
        X11_XSet_ಪಠ್ಯ_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.ಮೌಲ್ಯ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_XFlush(display);
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಕಿಟಕಿ_2 ಬೇರು = ಬೇರು_ಕಿಟಕಿ(display, displaydata->screen);
    XClient_ಸಂದೇಶ_Event e;
    ಕಿಟಕಿ_2 ಮಗು_Return_2;
    ಪೂರ್ಣಾಂಕ wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, ದತ್ತಾಂಶ->xwindow, ಬೇರು, x, y, &wx, &wy, &ಮಗು_Return_2);

    e.type = Client_ಸಂದೇಶ;
    e.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
    e.ಸಂದೇಶ_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.ದತ್ತಾಂಶ.l[0] = 0;  // GTK device ID (unused)
    e.ದತ್ತಾಂಶ.l[1] = wx; // X coordinate relative to root
    e.ದತ್ತಾಂಶ.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, ಬೇರು, False, Substructure_Redirect_ಮುಖವಾಡ | Substructure_Notify_ಮುಖವಾಡ, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) &&
        (ದತ್ತಾಂಶ->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(ಕಿಟಕಿ);
            ಹಿಂತಿರುಗಿ true;
    }

    ಸ್ಥಿರಾಂಕ Uint64 current_ಸಮಯ = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        ಆದರೆ (_this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns &&
            current_ಸಮಯ < _this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns - current_ಸಮಯ, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += ಕಿಟಕಿ->ಆಂತರಿಕ->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_ಗಮ್ಯ_NS(1000) : SDL_MS_ಗಮ್ಯ_NS(100);

    ಹಿಂತಿರುಗಿ X11_Sync_ಕಿಟಕಿ_Timeout(_this, ಕಿಟಕಿ, timeout);
}

bool X11_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable)
{
    ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        Display *display = ದತ್ತಾಂಶ->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, ದತ್ತಾಂಶ->xwindow);
        ಆದರೆ (!wmhints) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get WM hints");
        }

        wmhints->ಒಳಹರಿವು = focusable ? True : False;
        wmhints->flags |= ಒಳಹರಿವು_Hint;

        X11_XSetWMHints(display, ದತ್ತಾಂಶ->xwindow, wmhints);
        X11_XFree(wmhints);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            ಆದರೆ (!focusable && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
                SDL_ಕಿಟಕಿ *new_focus;
                ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(ಕಿಟಕಿ, &new_focus);
                X11_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (focusable) {
                ಆದರೆ (SDL_ShouldFocusPopup(ಕಿಟಕಿ)) {
                    X11_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
                }
            }
        }

        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
