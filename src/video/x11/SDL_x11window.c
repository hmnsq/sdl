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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_appid.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11mouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xfixes.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengles.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _NET_WM_STATE_REMOVE 0l
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_STATE_ਜੋੜੋ    1l

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_ਖਿੜਕੀ_ਅੰਕੜੇ(ਖਿੜਕੀ)                                       \
    ਜੇ (!ਖਿੜਕੀ) {                                                      \
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid window");                          \
    }                                                                   \
    ਜੇ (!ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {                                          \
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid window driver data");              \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_DISPLAY_ਅੰਕੜੇ(display)                                     \
    ਜੇ (!_display) {                                                    \
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid display");                         \
    }                                                                   \
    ਜੇ (!_display->ਅੰਦਰੂਨੀ) {                                        \
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid display driver data");             \
    }

ਸਥਿਰ Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ਵਾਪਸ ev->type == MapNotify && ev->xmap.ਖਿੜਕੀ == *((ਖਿੜਕੀ_2 *)win);
}
ਸਥਿਰ Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ਵਾਪਸ ev->type == UnmapNotify && ev->xunmap.ਖਿੜਕੀ == *((ਖਿੜਕੀ_2 *)win);
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

ਸਥਿਰ bool X11_CheckCurrentDesktop(ਅਚਲ ਅੱਖਰ *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ਅਚਲ ਅੱਖਰ *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    ਜੇ (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        ਵਾਪਸ true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    ਜੇ (desktopVar && SDL_strcasestr(desktopVar, name)) {
        ਵਾਪਸ true;
    }

    ਵਾਪਸ false;
}

ਸਥਿਰ bool X11_Is_ਖਿੜਕੀ_Mapped(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    XWindow_ਗੁਣ attr;

    X11_XGet_ਖਿੜਕੀ_ਗੁਣ(videodata->display, ਅੰਕੜੇ->xwindow, &attr);
    ਜੇ (attr.map_state != IsUnmapped) {
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }
}

ਸਥਿਰ bool X11_IsDisplayOk(Display *display)
{
    ਜੇ (display->flags & XlibDisplayIOError) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

#ਜੇ 0
ਸਥਿਰ bool X11_IsActionAllowed(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, Atom action)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Atom _NET_WM_ALLOWED_ACTIONS = ਅੰਕੜੇ->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਪੂਰਨ form;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ remain;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ len, i;
    Atom *list;
    bool ret = false;

    ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, ਅੰਕੜੇ->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **)&list) == Success) {
        ਲਈ (i=0; i<len; ++i) {
            ਜੇ (list[i] == action) {
                ret = true;
                ਰੋਕੋ;
            }
        }
        X11_XFree(list);
    }
    ਵਾਪਸ ret;
}
#ਜੇ_ਅੰਤ // 0

ਸਥਿਰ ਖਾਲੀ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ਅਚਲ bool ਆਖਰੀ_position_pending = ਖਿੜਕੀ->ਆਖਰੀ_position_pending;
    ਅਚਲ bool ਆਖਰੀ_ਮਾਪ_pending = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending;

    X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);

    ਖਿੜਕੀ->ਆਖਰੀ_position_pending = ਆਖਰੀ_position_pending;
    ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = ਆਖਰੀ_ਮਾਪ_pending;
}

ਖਾਲੀ X11_ਸੈੱਟ_Net_WMState(SDL_VideoDevice *_this, ਖਿੜਕੀ_2 xwindow, SDL_ਖਿੜਕੀ_Flags flags)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
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
    ਪੂਰਨ ਗਿਣਤੀ_2 = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    ਜੇ (flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_ABOVE;
    }
    ਜੇ (flags & SDL_ਖਿੜਕੀ_UTILITY) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_SKIP_PAGER;
    }
    ਜੇ (flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_FOCUSED;
    }
    ਜੇ (flags & SDL_ਖਿੜਕੀ_MAXIMIZED) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    ਜੇ (flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_FULLSCREEN;
    }
    ਜੇ (flags & SDL_ਖਿੜਕੀ_MODAL) {
        atoms[ਗਿਣਤੀ_2++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(ਗਿਣਤੀ_2 <= SDL_arraysize(atoms));

    ਜੇ (ਗਿਣਤੀ_2 > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)atoms, ਗਿਣਤੀ_2);
    } ਨਹੀਂਤਾਂ {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_ConstrainPopup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool output_ਮੰਜ਼ਿਲ_pending)
{
    // Clamp popup windows to the output borders
    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        SDL_ਖਿੜਕੀ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        ਪੂਰਨ abs_x = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->floating.x;
        ਪੂਰਨ abs_y = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->floating.y;
        ਪੂਰਨ ਵਿੱਥ_x = 0, ਵਿੱਥ_y = 0;

        ਜੇ (ਖਿੜਕੀ->constrain_popup) {
            // Calculate the total offset from the parents
            ਲਈ (w = ਖਿੜਕੀ->ਮਾਪਾ; SDL_ਖਿੜਕੀ_IS_POPUP(w); w = w->ਮਾਪਾ) {
                ਵਿੱਥ_x += w->x;
                ਵਿੱਥ_y += w->y;
            }

            ਵਿੱਥ_x += w->x;
            ਵਿੱਥ_y += w->y;
            abs_x += ਵਿੱਥ_x;
            abs_y += ਵਿੱਥ_y;

            displayID = SDL_Get_Display_For_ਖਿੜਕੀ(w);

            SDL_GetDisplayBounds(displayID, &rect);
            ਜੇ (abs_x + ਖਿੜਕੀ->w > rect.x + rect.w) {
                abs_x -= (abs_x + ਖਿੜਕੀ->w) - (rect.x + rect.w);
            }
            ਜੇ (abs_y + ਖਿੜਕੀ->h > rect.y + rect.h) {
                abs_y -= (abs_y + ਖਿੜਕੀ->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ਜੇ (output_ਮੰਜ਼ਿਲ_pending) {
            ਖਿੜਕੀ->pending.x = abs_x - ਵਿੱਥ_x;
            ਖਿੜਕੀ->pending.y = abs_y - ਵਿੱਥ_y;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->floating.x = ਖਿੜਕੀ->windowed.x = abs_x - ਵਿੱਥ_x;
            ਖਿੜਕੀ->floating.y = ਖਿੜਕੀ->windowed.y = abs_y - ਵਿੱਥ_y;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ X11_ਸੈੱਟ_Keyboard_Focus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool ਸੈੱਟ_ਸਰਗਰਮ_focus)
{
    SDL_ਖਿੜਕੀ *toplevel = ਖਿੜਕੀ;

    // Find the toplevel parent
    ਜਦੋਂ (SDL_ਖਿੜਕੀ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ਮਾਪਾ;
    }

    toplevel->keyboard_focus = ਖਿੜਕੀ;

    ਜੇ (ਸੈੱਟ_ਸਰਗਰਮ_focus && !ਖਿੜਕੀ->is_hiding && !ਖਿੜਕੀ->is_destroying) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    }
}

SDL_ਖਿੜਕੀ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਖਿੜਕੀ_2 xwindow)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    ਪੂਰਨ actualFormat;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ i, ਅੰਕ_ਚੀਜ਼ਾਂ, ਬਾਈਟਾਂ_After;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *property_ਮੁੱਲ = ਨਿਰਾ;
    ਲੰਮਾ max_ਲੰਮਾਈ = 1024;
    SDL_ਖਿੜਕੀ_Flags flags = 0;

    ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_ਲੰਮਾਈ, False, XA_ATOM, &actualType,
                               &actualFormat, &ਅੰਕ_ਚੀਜ਼ਾਂ, &ਬਾਈਟਾਂ_After,
                               &property_ਮੁੱਲ) == Success) {
        Atom *atoms = (Atom *)property_ਮੁੱਲ;
        ਪੂਰਨ maximized = 0;
        ਪੂਰਨ fullscreen = 0;

        ਲਈ (i = 0; i < ਅੰਕ_ਚੀਜ਼ਾਂ; ++i) {
            ਜੇ (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_OCCLUDED;
            } ਨਹੀਂਤਾਂ ਜੇ (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS;
            } ਨਹੀਂਤਾਂ ਜੇ (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } ਨਹੀਂਤਾਂ ਜੇ (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } ਨਹੀਂਤਾਂ ਜੇ (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        ਜੇ (fullscreen == 1) {
            flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;
        } ਨਹੀਂਤਾਂ ਜੇ (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN);
        }

        ਜੇ (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            ਜੇ (fullscreen) {
                flags |= (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED);
            } ਨਹੀਂਤਾਂ {
                flags |= SDL_ਖਿੜਕੀ_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_ਗੁਣ attr;
            SDL_zero(attr);
            X11_XGet_ਖਿੜਕੀ_ਗੁਣ(videodata->display, xwindow, &attr);
            ਜੇ (attr.map_state == IsUnmapped) {
                flags |= SDL_ਖਿੜਕੀ_HIDDEN;
            }
        }
        X11_XFree(property_ਮੁੱਲ);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    ਵਾਪਸ flags;
}

ਸਥਿਰ bool ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਖਿੜਕੀ_2 w)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Allocate the window data
    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    ਅੰਕੜੇ->videodata = videodata;
    ਅੰਕੜੇ->ਖਿੜਕੀ = ਖਿੜਕੀ;
    ਅੰਕੜੇ->xwindow = w;
    ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ = SDL_HITTEST_ਸਾਧਾਰਨ;

    X11_Create_ਨਿਵੇਸ਼_Context(ਅੰਕੜੇ);

    // Associate the data with the window

    ਜੇ (videodata->numwindows >= videodata->windowlistlength) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ ** new_windowlist = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * ਆਕਾਰ(*videodata->windowlist));
        ਜੇ (!new_windowlist) {
            ਜਾਓ error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_ਗੁਣ attrib;

        X11_XGet_ਖਿੜਕੀ_ਗੁਣ(ਅੰਕੜੇ->videodata->display, w, &attrib);
        ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
            ਖਿੜਕੀ->x = ਖਿੜਕੀ->windowed.x = ਖਿੜਕੀ->floating.x = attrib.x;
            ਖਿੜਕੀ->y = ਖਿੜਕੀ->windowed.y = ਖਿੜਕੀ->floating.y = attrib.y - ਅੰਕੜੇ->border_ਸਿਖਰ;
        }
        ਖਿੜਕੀ->w = ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->floating.w = attrib.ਚੌੜਾਈ;
        ਖਿੜਕੀ->h = ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->floating.h = attrib.ਉਚਾਈ;
        ਜੇ (attrib.map_state != IsUnmapped) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_HIDDEN;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_HIDDEN;
        }
        ਅੰਕੜੇ->visual = attrib.visual;
        ਅੰਕੜੇ->colormap = attrib.colormap;
    }

    ਖਿੜਕੀ->flags |= X11_GetNetWMState(_this, ਖਿੜਕੀ, w);

    {
        ਖਿੜਕੀ_2 Focal_ਖਿੜਕੀ;
        ਪੂਰਨ Revert_ਮੰਜ਼ਿਲ = 0;
        X11_XGet_ਨਿਵੇਸ਼_Focus(ਅੰਕੜੇ->videodata->display, &Focal_ਖਿੜਕੀ, &Revert_ਮੰਜ਼ਿਲ);
        ਜੇ (Focal_ਖਿੜਕੀ == w) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS;
        }

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
            SDL_ਸੈੱਟ_Keyboard_Focus(ਅੰਕੜੇ->ਖਿੜਕੀ);
        }

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        // Query the title from the existing window
        ਖਿੜਕੀ->title = X11_Get_ਖਿੜਕੀ_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    ਪੂਰਨ screen = (displaydata ? displaydata->screen : 0);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_X11_DISPLAY_ਸੂਚਕ, ਅੰਕੜੇ->videodata->display);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_X11_SCREEN_ਸੰਖਿਆ, screen);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_X11_ਖਿੜਕੀ_ਸੰਖਿਆ, ਅੰਕੜੇ->xwindow);


#ਜੇ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) &&
        ((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_ਅੰਕੜੇ || X11_GL_UseEGL(_this))
#ਜੇ_ਅੰਤ
    ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਜੇ (!_this->egl_ਅੰਕੜੇ) {
            ਜਾਓ error_cleanup;
        }

        // Create the GLES window surface
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)w);

        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            SDL_ਸੈੱਟ_Error("Could not create GLES window surface");
            ਜਾਓ error_cleanup;
        }
#ਨਹੀਂਤਾਂ
        SDL_ਸੈੱਟ_Error("Could not create GLES window surface (EGL support not configured)");
        ਜਾਓ error_cleanup;
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL
    }
#ਜੇ_ਅੰਤ

    // All done!
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    videodata->windowlist[videodata->numwindows++] = ਅੰਕੜੇ;
    ਵਾਪਸ true;

error_cleanup:
    X11_Destroy_ਨਿਵੇਸ਼_Context(ਅੰਕੜੇ);
    SDL_free(ਅੰਕੜੇ);
    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ ਤਿਆਰੀ_ਖਿੜਕੀ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਲੰਮਾ fevent = 0;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਖਿੜਕੀ_2 xwindow = ਅੰਕੜੇ->xwindow;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (SDL_X11_HAVE_UTF8 && ਅੰਕੜੇ->ic) {
        X11_XGetICValues(ਅੰਕੜੇ->ic, XNFilterEvents, &fevent, ਨਿਰਾ);
    }
#ਜੇ_ਅੰਤ

    X11_Xinput2Select(_this, ਖਿੜਕੀ);

    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x11_keyboard_events = ਕੁੰਜੀ_Press_ਨਕਾਬ | ਕੁੰਜੀ_Release_ਨਕਾਬ;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x11_ਸੂਚਕ_events = Button_Press_ਨਕਾਬ | Button_Release_ਨਕਾਬ | ਸੂਚਕ_Motion_ਨਕਾਬ;

        X11_Xinput2SelectMouseAndKeyboard(_this, ਖਿੜਕੀ);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        ਜੇ (ਅੰਕੜੇ->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        ਜੇ (ਅੰਕੜੇ->xinput2_mouse_enabled) {
            x11_ਸੂਚਕ_events = 0;
        }

        X11_XSelect_ਨਿਵੇਸ਼(ਅੰਕੜੇ->videodata->display, xwindow,
                         (Focus_Change_ਨਕਾਬ | Enter_ਖਿੜਕੀ_ਨਕਾਬ | Leave_ਖਿੜਕੀ_ਨਕਾਬ | Exposure_ਨਕਾਬ |
                          x11_keyboard_events | x11_ਸੂਚਕ_events |
                          Property_Change_ਨਕਾਬ | Structure_Notify_ਨਕਾਬ |
                          Keymap_State_ਨਕਾਬ | fevent));
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_ਖਿੜਕੀ_Bordered(Display *display, ਪੂਰਨ screen, ਖਿੜਕੀ_2 ਖਿੜਕੀ, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    ਜੇ (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        ਬਣਤਰ
        {
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ flags;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ functions;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ decorations;
            ਲੰਮਾ ਨਿਵੇਸ਼_ਬਹੁਲਕ;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਥਿਤੀ;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, ਖਿੜਕੀ, WM_HINTS, WM_HINTS, 32,
                            Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&MWMHints,
                            ਆਕਾਰ(MWMHints) / ਆਕਾਰ(ਲੰਮਾ));
    } ਨਹੀਂਤਾਂ { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, ਖਿੜਕੀ, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen));
    }
}

bool X11_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    ਖਿੜਕੀ_2 w = (ਖਿੜਕੀ_2)SDL_Get_ਸੰਖਿਆ_Property(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_X11_ਖਿੜਕੀ_ਸੰਖਿਆ,
                (ਖਿੜਕੀ_2)SDL_Get_ਸੂਚਕ_Property(create_props, "sdl2-compat.external_window", ਨਿਰਾ));
    ਜੇ (w) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_EXTERNAL;

        ਜੇ (!ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(_this, ਖਿੜਕੀ, w)) {
            ਵਾਪਸ false;
        }

        ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_ਖਿੜਕੀ_ਨਿਵੇਸ਼, true)) {
            ਤਿਆਰੀ_ਖਿੜਕੀ_ਨਿਵੇਸ਼(_this, ਖਿੜਕੀ);
        }
        ਵਾਪਸ true;
    }

    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਜੇ (!displaydata) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not find display info");
    }

    ਅਚਲ bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ਅਚਲ bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata;
    Display *display = ਅੰਕੜੇ->display;
    ਪੂਰਨ screen = displaydata->screen;
    Visual *visual;
    ਪੂਰਨ ਡੂੰਘਾਈ_2;
    XSet_ਖਿੜਕੀ_ਗੁਣ xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_ਖਿੜਕੀ_TYPE;
    Atom wintype;
    ਅਚਲ ਅੱਖਰ *wintype_name = ਨਿਰਾ;
    ਲੰਮਾ compositor = 1;
    Atom _NET_WM_PID;
    ਅਚਲ ਅੱਖਰ *hint = ਨਿਰਾ;
    ਪੂਰਨ win_x, win_y;
    bool undefined_position = false;

#ਜੇ defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ਅਚਲ ਪੂਰਨ transparent = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) ? true : false;
    ਅਚਲ ਅੱਖਰ *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_ਖਿੜਕੀ_VISUALID);
    ਅਚਲ ਅੱਖਰ *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    ਜੇ (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, ਸਾਂਚਾ;
        ਪੂਰਨ nvis;

        SDL_zero(ਸਾਂਚਾ);
        ਸਾਂਚਾ.visualid = SDL_strtol(forced_visual_id, ਨਿਰਾ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ਸਾਂਚਾ, &nvis);
        ਜੇ (vi) {
            visual = vi->visual;
            ਡੂੰਘਾਈ_2 = vi->ਡੂੰਘਾਈ_2;
            X11_XFree(vi);
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = ਨਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਜੇ (((_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_ਅੰਕੜੇ || X11_GL_UseEGL(_this))
#ਜੇ_ਅੰਤ
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#ਜੇ_ਅੰਤ
        }

        ਜੇ (!vinfo) {
            ਵਾਪਸ false;
        }
        visual = vinfo->visual;
        ਡੂੰਘਾਈ_2 = vinfo->ਡੂੰਘਾਈ_2;
        X11_XFree(vinfo);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        visual = displaydata->visual;
        ਡੂੰਘਾਈ_2 = displaydata->ਡੂੰਘਾਈ_2;
    }

    xattr.override_redirect = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TOOLTIP) || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    ਜੇ (visual->class == ਸਿੱਧਾ_Color) {
        XColor *colorcells;
        ਪੂਰਨ i;
        ਪੂਰਨ ncolors;
        ਪੂਰਨ rmax, gmax, bmax;
        ਪੂਰਨ rmask, gmask, bmask;
        ਪੂਰਨ rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        ਜੇ (!xattr.colormap) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * ਆਕਾਰ(XColor));
        ਜੇ (!colorcells) {
            ਵਾਪਸ false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_ਨਕਾਬ;
        ਜਦੋਂ (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_ਨਕਾਬ;
        ਜਦੋਂ (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_ਨਕਾਬ;
        ਜਦੋਂ (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        ਲਈ (i = 0; i < ncolors; i++) {
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
    } ਨਹੀਂਤਾਂ {
        xattr.colormap =
            X11_XCreateColormap(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen),
                                visual, AllocNone);
    }

    ਜੇ (ਖਿੜਕੀ->undefined_x && ਖਿੜਕੀ->undefined_y &&
        ਖਿੜਕੀ->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        X11_ConstrainPopup(ਖਿੜਕੀ, false);
    }
    SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ,
                                  ਖਿੜਕੀ->floating.x, ਖਿੜਕੀ->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_ਖਿੜਕੀ(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen),
                          win_x, win_y, ਖਿੜਕੀ->floating.w, ਖਿੜਕੀ->floating.h,
                          0, ਡੂੰਘਾਈ_2, ਨਿਵੇਸ਼_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    ਜੇ (!w) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    ਜੇ (!(ਖਿੜਕੀ->pending_flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਸੈੱਟ_ਖਿੜਕੀ_Bordered(display, screen, w, !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS));
    }

    sizehints = X11_XAlloc_ਮਾਪ_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
        sizehints->min_ਚੌੜਾਈ_2 = sizehints->max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->floating.w;
        sizehints->min_ਉਚਾਈ_2 = sizehints->max_ਉਚਾਈ_2 = ਖਿੜਕੀ->floating.h;
        sizehints->flags |= (PMax_ਮਾਪ | PMin_ਮਾਪ);
    }
    ਜੇ (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->ਨਿਵੇਸ਼ = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE) ? True : False;
    wmhints->ਖਿੜਕੀ_ਸਮੂਹ = ਅੰਕੜੇ->ਖਿੜਕੀ_ਸਮੂਹ;
    wmhints->flags = ਨਿਵੇਸ਼_Hint | ਖਿੜਕੀ_ਸਮੂਹ_Hint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (ਅੱਖਰ *)SDL_GetExeName();
    classhints->res_class = (ਅੱਖਰ *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    ਜੇ (ਅੰਕੜੇ->pid > 0) {
        ਲੰਮਾ pid = (ਲੰਮਾ)ਅੰਕੜੇ->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_ਬਹੁਲਕ_Replace,
                            (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&pid, 1);
    }

    // Set the window manager state
    X11_ਸੈੱਟ_Net_WMState(_this, w, ਖਿੜਕੀ->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_ਖਿੜਕੀ_TYPE);
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } ਨਹੀਂਤਾਂ ਜੇ (hint && *hint) {
        wintype_name = hint;
    } ਨਹੀਂਤਾਂ {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_ਖਿੜਕੀ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_ਖਿੜਕੀ_TYPE, XA_ATOM, 32,
                        Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&wintype, 1);
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_ਬਹੁਲਕ_Replace,
                            (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&compositor, 1);
    }

    {
        Atom protocols[4];
        ਪੂਰਨ proto_ਗਿਣਤੀ = 0;

        protocols[proto_ਗਿਣਤੀ++] = ਅੰਕੜੇ->atoms.WM_DELETE_ਖਿੜਕੀ; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_ਗਿਣਤੀ++] = ਅੰਕੜੇ->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
        ਜੇ (use_resize_sync) {
            protocols[proto_ਗਿਣਤੀ++] = ਅੰਕੜੇ->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_ਗਿਣਤੀ <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_ਗਿਣਤੀ);
    }

    ਜੇ (!ਤਿਆਰੀ_ਖਿੜਕੀ_ਅੰਕੜੇ(_this, ਖਿੜਕੀ, w)) {
        X11_XDestroy_ਖਿੜਕੀ(display, w);
        ਵਾਪਸ false;
    }
    windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // Set the parent if this is a non-popup window.
    ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ) && ਖਿੜਕੀ->ਮਾਪਾ) {
        X11_XSetTransientForHint(display, w, ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(ਖਿੜਕੀ->pending_flags & SDL_ਖਿੜਕੀ_FULLSCREEN) &&
                                               !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    ਜੇ (use_resize_sync) {
        X11_InitResizeSync(ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_ਨਿਵੇਸ਼, 0, 0, region, Shape_ਸੈੱਟ);
        X11_XDestroyRegion(region);
    }
#ਜੇ_ਅੰਤ

    ਤਿਆਰੀ_ਖਿੜਕੀ_ਨਿਵੇਸ਼(_this, ਖਿੜਕੀ);

    // For _ICC_PROFILE.
    X11_XSelect_ਨਿਵੇਸ਼(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, screen), Property_Change_ਨਕਾਬ);

    X11_XFlush(display);

    ਵਾਪਸ true;
}

ਅੱਖਰ *X11_Get_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, ਖਿੜਕੀ_2 xwindow)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->display;
    ਪੂਰਨ ਸਥਿਤੀ, real_format;
    Atom real_type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read, ਚੀਜ਼ਾਂ_ਖੱਬਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata;
    ਅੱਖਰ *title = ਨਿਰਾ;

    ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, xwindow, ਅੰਕੜੇ->atoms._NET_WM_NAME,
                                    0L, 8192L, False, ਅੰਕੜੇ->atoms.UTF8_STRING, &real_type, &real_format,
                                    &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
    ਜੇ (ਸਥਿਤੀ == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(ਅੱਖਰ *, propdata));
        X11_XFree(propdata);
    } ਨਹੀਂਤਾਂ {
        ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
        ਜੇ (ਸਥਿਤੀ == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(ਅੱਖਰ *, propdata), ਚੀਜ਼ਾਂ_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } ਨਹੀਂਤਾਂ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    ਵਾਪਸ title;
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਖਿੜਕੀ_2 xwindow = ਅੰਕੜੇ->xwindow;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਅੱਖਰ *title = ਖਿੜਕੀ->title ? ਖਿੜਕੀ->title : "";

    SDL_X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(display, xwindow, title);
}

ਸਥਿਰ bool caught_x11_error = false;
ਸਥਿਰ ਪੂਰਨ X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ X11_ExternalResizeMoveSync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਪੂਰਨ (*prev_handler)(Display *, XErrorEvent *);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬੱਚਾ_ਗਿਣਤੀ;
    ਖਿੜਕੀ_2 ਬੱਚਾ_Return_2, ਜੜ੍ਹ, ਮਾਪਾ;
    ਖਿੜਕੀ_2 *children;
    XWindow_ਗੁਣ attrs;
    Uint64 timeout = 0;
    ਪੂਰਨ x, y;
    ਅਚਲ bool send_move = !!(ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_MOVE);
    ਅਚਲ bool send_resize = !!(ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_ਰੁੱਖ(display, ਅੰਕੜੇ->xwindow, &ਜੜ੍ਹ, &ਮਾਪਾ, &children, &ਬੱਚਾ_ਗਿਣਤੀ);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_ਮੰਜ਼ਿਲ_NS(100);
    ਜਦੋਂ (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਅੰਕੜੇ->xwindow, &attrs);
        X11_XTranslateCoordinates(display, ਮਾਪਾ, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display),
                                  attrs.x, attrs.y, &x, &y, &ਬੱਚਾ_Return_2);
        SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(ਖਿੜਕੀ, x, y, &x, &y);

        ਜੇ (!caught_x11_error) {
            ਜੇ ((ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_MOVE) && (x == ਅੰਕੜੇ->expected.x + ਅੰਕੜੇ->border_ਖੱਬਾ && y == ਅੰਕੜੇ->expected.y + ਅੰਕੜੇ->border_ਸਿਖਰ)) {
                ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            ਜੇ ((ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.ਚੌੜਾਈ == ਅੰਕੜੇ->expected.w && attrs.ਉਚਾਈ == ਅੰਕੜੇ->expected.h)) {
                ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            ਜੇ (ਅੰਕੜੇ->pending_operation == X11_PENDING_OP_NONE) {
                ਰੋਕੋ;
            }
        }

        ਜੇ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ਅੰਕੜੇ->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            ਅੰਕੜੇ->expected.x = x;
            ਅੰਕੜੇ->expected.y = y;
            ਅੰਕੜੇ->expected.w = attrs.ਚੌੜਾਈ;
            ਅੰਕੜੇ->expected.h = attrs.ਉਚਾਈ;
            ਰੋਕੋ;
        }

        SDL_Delay(10);
    }

    ਜੇ (!caught_x11_error) {
        ਜੇ (send_move) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, x, y);
        }
        ਜੇ (send_resize) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, attrs.ਚੌੜਾਈ, attrs.ਉਚਾਈ);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ਸਥਿਰ bool X11_Sync_ਖਿੜਕੀ_Timeout(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, Uint64 param_timeout)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਪੂਰਨ (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool ਨਤੀਜਾ = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    ਜੇ (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    ਜਦੋਂ (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        ਜੇ ((ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_MOVE) && (ਖਿੜਕੀ->x == ਅੰਕੜੇ->expected.x + ਅੰਕੜੇ->border_ਖੱਬਾ && ਖਿੜਕੀ->y == ਅੰਕੜੇ->expected.y + ਅੰਕੜੇ->border_ਸਿਖਰ)) {
            ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        ਜੇ ((ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_RESIZE) && (ਖਿੜਕੀ->w == ਅੰਕੜੇ->expected.w && ਖਿੜਕੀ->h == ਅੰਕੜੇ->expected.h)) {
            ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        ਜੇ (ਅੰਕੜੇ->pending_operation == X11_PENDING_OP_NONE) {
            ਜੇ (force_exit ||
                (ਖਿੜਕੀ->x == ਅੰਕੜੇ->expected.x + ਅੰਕੜੇ->border_ਖੱਬਾ && ਖਿੜਕੀ->y == ਅੰਕੜੇ->expected.y + ਅੰਕੜੇ->border_ਸਿਖਰ &&
                 ਖਿੜਕੀ->w == ਅੰਕੜੇ->expected.w && ਖਿੜਕੀ->h == ਅੰਕੜੇ->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                ਰੋਕੋ;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        ਜੇ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ਅੰਕੜੇ->expected.x = ਖਿੜਕੀ->x;
            ਅੰਕੜੇ->expected.y = ਖਿੜਕੀ->y;
            ਅੰਕੜੇ->expected.w = ਖਿੜਕੀ->w;
            ਅੰਕੜੇ->expected.h = ਖਿੜਕੀ->h;

            ਨਤੀਜਾ = false;
            ਰੋਕੋ;
        }

        SDL_Delay(10);
    }

    ਅੰਕੜੇ->pending_operation = X11_PENDING_OP_NONE;

    ਜੇ (!caught_x11_error) {
        X11_PumpEvents(_this);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom _NET_WM_ICON = ਅੰਕੜੇ->videodata->atoms._NET_WM_ICON;
    ਪੂਰਨ (*prevHandler)(Display *, XErrorEvent *) = ਨਿਰਾ;
    bool ਨਤੀਜਾ = true;

    ਜੇ (icon) {
        ਪੂਰਨ x, y;
        ਪੂਰਨ propsize;
        ਲੰਮਾ *propdata;
        Uint32 *src;
        ਲੰਮਾ *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * ਆਕਾਰ(ਲੰਮਾ));

        ਜੇ (!propdata) {
            ਵਾਪਸ false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        ਲਈ (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            ਲਈ (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, ਅੰਕੜੇ->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)propdata,
                            propsize);
        SDL_free(propdata);

        ਜੇ (caught_x11_error) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    ਜੇ (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ X11_Update_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool use_current_position)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਅਚਲ ਪੂਰਨ rel_x = use_current_position ? ਖਿੜਕੀ->x : ਖਿੜਕੀ->pending.x;
    ਅਚਲ ਪੂਰਨ rel_y = use_current_position ? ਖਿੜਕੀ->y : ਖਿੜਕੀ->pending.y;

    SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ,
                                  rel_x - ਅੰਕੜੇ->border_ਖੱਬਾ, rel_y - ਅੰਕੜੇ->border_ਸਿਖਰ,
                                  &ਅੰਕੜੇ->expected.x, &ਅੰਕੜੇ->expected.y);

    // Attempt to move the window
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_position = true;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->expected.x, ਅੰਕੜੇ->expected.y);
    }
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Sync any pending fullscreen or maximize events.
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, ਖਿੜਕੀ);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED) {
        ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_RESTORE) {
            ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_position = true;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
            X11_ConstrainPopup(ਖਿੜਕੀ, true);
        }
        X11_Update_ਖਿੜਕੀ_Position(ਖਿੜਕੀ, false);
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->fs_repositioned = true;
        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool use_current)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_ਮਾਪ_Hints();
    ਲੰਮਾ hint_flags = 0;

    X11_XGetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_ਮਾਪ | PMax_ਮਾਪ | PAspect);

    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) {
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_w || ਅੰਕੜੇ->ਖਿੜਕੀ->min_h) {
            sizehints->flags |= PMin_ਮਾਪ;
            sizehints->min_ਚੌੜਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ->min_w;
            sizehints->min_ਉਚਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ->min_h;
        }
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->max_w || ਅੰਕੜੇ->ਖਿੜਕੀ->max_h) {
            sizehints->flags |= PMax_ਮਾਪ;
            sizehints->max_ਚੌੜਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ->max_w;
            sizehints->max_ਉਚਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ->max_h;
        }
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect > 0.0f || ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(ਅੰਕੜੇ->ਖਿੜਕੀ->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(ਅੰਕੜੇ->ਖਿੜਕੀ->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } ਨਹੀਂਤਾਂ {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_ਮਾਪ | PMax_ਮਾਪ;
        ਜੇ (use_current) {
            sizehints->min_ਚੌੜਾਈ_2 = sizehints->max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਅੰਕੜੇ->ਖਿੜਕੀ->floating.w;
            sizehints->min_ਉਚਾਈ_2 = sizehints->max_ਉਚਾਈ_2 = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਅੰਕੜੇ->ਖਿੜਕੀ->floating.h;
        } ਨਹੀਂਤਾਂ {
            sizehints->min_ਚੌੜਾਈ_2 = sizehints->max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਅੰਕੜੇ->ਖਿੜਕੀ->windowed.w;
            sizehints->min_ਉਚਾਈ_2 = sizehints->max_ਉਚਾਈ_2 = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਅੰਕੜੇ->ਖਿੜਕੀ->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints);
    X11_XFree(sizehints);
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    ਜੇ (ਅੰਕੜੇ->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, ਖਿੜਕੀ);
    }

    // Set the size as pending if the window is being restored.
    ਜੇ (ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        // New size will be set when the window is restored.
        ਜੇ (ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_RESTORE) {
            ਅੰਕੜੇ->pending_ਮਾਪ = true;
        } ਨਹੀਂਤਾਂ {
            // Can't resize the window.
            ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = false;
        }
        ਵਾਪਸ;
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_ਮਾਪ_Hints();
            ਲੰਮਾ userhints;
            ਪੂਰਨ dest_x, dest_y;

            X11_XGetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints, &userhints);

            ਅੰਕੜੇ->expected.w = sizehints->min_ਚੌੜਾਈ_2 = sizehints->max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->pending.w;
            ਅੰਕੜੇ->expected.h = sizehints->min_ਉਚਾਈ_2 = sizehints->max_ਉਚਾਈ_2 = ਖਿੜਕੀ->pending.h;
            sizehints->flags |= PMin_ਮਾਪ | PMax_ਮਾਪ;
            ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints);

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
            X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
            ਅਚਲ ਪੂਰਨ x = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->x;
            ਅਚਲ ਪੂਰਨ y = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->y;
            SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ,
                                          x - ਅੰਕੜੇ->border_ਖੱਬਾ,
                                          y - ਅੰਕੜੇ->border_ਸਿਖਰ,
                                          &dest_x, &dest_y);
            X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, dest_x, dest_y);
            X11_XRaise_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow);

            X11_XFree(sizehints);
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->expected.w = ਖਿੜਕੀ->pending.w;
        ਅੰਕੜੇ->expected.h = ਖਿੜਕੀ->pending.h;
        ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->expected.w, ਅੰਕੜੇ->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
    }
}

bool X11_Get_ਖਿੜਕੀ_Borders_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    *ਖੱਬਾ = ਅੰਕੜੇ->border_ਖੱਬਾ;
    *ਸੱਜਾ = ਅੰਕੜੇ->border_ਸੱਜਾ;
    *ਸਿਖਰ = ਅੰਕੜੇ->border_ਸਿਖਰ;
    *bottom = ਅੰਕੜੇ->border_bottom;

    ਵਾਪਸ true;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom NET_WM_ਖਿੜਕੀ_OPACITY = ਅੰਕੜੇ->videodata->atoms.NET_WM_ਖਿੜਕੀ_OPACITY;

    ਜੇ (opacity == 1.0f) {
        X11_XDeleteProperty(display, ਅੰਕੜੇ->xwindow, NET_WM_ਖਿੜਕੀ_OPACITY);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ Uint32 FullyOpaque = 0xFFFFFFFF;
        ਅਚਲ ਲੰਮਾ alpha = (ਲੰਮਾ)((ਦੁੱਗਣਾ)opacity * (ਦੁੱਗਣਾ)FullyOpaque);
        X11_XChangeProperty(display, ਅੰਕੜੇ->xwindow, NET_WM_ਖਿੜਕੀ_OPACITY, XA_CARDINAL, 32,
                            Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&alpha, 1);
    }

    ਵਾਪਸ true;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਮਾਪਾ_ਅੰਕੜੇ = ਮਾਪਾ ? ਮਾਪਾ->ਅੰਦਰੂਨੀ : ਨਿਰਾ;
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *display = video_ਅੰਕੜੇ->display;

    ਜੇ (ਮਾਪਾ_ਅੰਕੜੇ) {
        X11_XSetTransientForHint(display, ਅੰਕੜੇ->xwindow, ਮਾਪਾ_ਅੰਕੜੇ->xwindow);
    } ਨਹੀਂਤਾਂ {
        X11_XDeleteProperty(display, ਅੰਕੜੇ->xwindow, video_ਅੰਕੜੇ->atoms.WM_TRANSIENT_FOR);
    }

    ਵਾਪਸ true;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = video_ਅੰਕੜੇ->display;
    Uint32 flags = ਖਿੜਕੀ->flags;
    Atom _NET_WM_STATE = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_MODAL;

    ਜੇ (modal) {
        flags |= SDL_ਖਿੜਕੀ_MODAL;
    } ਨਹੀਂਤਾਂ {
        flags &= ~SDL_ਖਿੜਕੀ_MODAL;
        X11_XDeleteProperty(display, ਅੰਕੜੇ->xwindow, video_ਅੰਕੜੇ->atoms.WM_TRANSIENT_FOR);
    }

    ਜੇ (X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ਸੁਨੇਹਾ;
        e.xclient.ਸੁਨੇਹਾ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
        e.xclient.ਅੰਕੜੇ.l[0] = modal ? NET_WM_STATE_ਜੋੜੋ : _NET_WM_STATE_REMOVE;
        e.xclient.ਅੰਕੜੇ.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.ਅੰਕੜੇ.l[3] = 0l;

        X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                       Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);
    } ਨਹੀਂਤਾਂ {
        X11_ਸੈੱਟ_Net_WMState(_this, ਅੰਕੜੇ->xwindow, flags);
    }

    X11_XFlush(display);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered)
{
    ਅਚਲ bool focused = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) != 0;
    ਅਚਲ bool visible = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) && !ਖਿੜਕੀ->is_hiding;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;
    XEvent event;

    ਜੇ (ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਸੈੱਟ_ਖਿੜਕੀ_Bordered(display, displaydata->screen, ਅੰਕੜੇ->xwindow, bordered);
        X11_XFlush(display);

        ਜੇ (visible) {
            XWindow_ਗੁਣ attr;
            ਕਰੋ {
                X11_XSync(display, False);
                X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਅੰਕੜੇ->xwindow, &attr);
            } ਜਦੋਂ (attr.map_state != IsViewable);

            ਜੇ (focused) {
                X11_XSet_ਨਿਵੇਸ਼_Focus(display, ਅੰਕੜੇ->xwindow, Revert_ਮੰਜ਼ਿਲ_ਮਾਪਾ, Current_ਸਮਾਂ);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&ਅੰਕੜੇ->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&ਅੰਕੜੇ->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_ਮੁੱਲਾਂ(ਅੰਕੜੇ);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->floating.w, ਖਿੜਕੀ->floating.h);
        X11_XSync(display, False);
    } ਨਹੀਂਤਾਂ {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        ਅੰਕੜੇ->toggle_borders = true;
        ਅੰਕੜੇ->fullscreen_borders_forced_on = false;
    }
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom _NET_WM_STATE = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_ABOVE;

    ਜੇ (X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ਸੁਨੇਹਾ;
        e.xclient.ਸੁਨੇਹਾ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
        e.xclient.ਅੰਕੜੇ.l[0] =
            on_ਸਿਖਰ ? NET_WM_STATE_ਜੋੜੋ : _NET_WM_STATE_REMOVE;
        e.xclient.ਅੰਕੜੇ.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.ਅੰਕੜੇ.l[3] = 0l;

        X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                       Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);
    } ਨਹੀਂਤਾਂ {
        X11_ਸੈੱਟ_Net_WMState(_this, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->flags);
    }
    X11_XFlush(display);
}

ਖਾਲੀ X11_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ACTIVATE_WHEN_SHOWN, true);
    bool ਸੈੱਟ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    ਜੇ (ਅੰਕੜੇ->was_shown) {
        X11_PumpEvents(_this);
    }

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(ਖਿੜਕੀ, true);
        ਅੰਕੜੇ->pending_position = true;
        ਸੈੱਟ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (ਖਾਲੀ)bActivate;

    ਜੇ (!X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        X11_XMapRaised(display, ਅੰਕੜੇ->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&ਅੰਕੜੇ->xwindow);
        }
        X11_XFlush(display);
        ਸੈੱਟ_position = ਅੰਕੜੇ->pending_position ||
                       (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) && !ਖਿੜਕੀ->undefined_x && !ਖਿੜਕੀ->undefined_y);
    }

    ਜੇ (!ਅੰਕੜੇ->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_ਨਿਵੇਸ਼_Focus(display, ਅੰਕੜੇ->xwindow, Revert_ਮੰਜ਼ਿਲ_None, Current_ਸਮਾਂ);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
        X11_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
    }

    // Get some valid border values, if we haven't received them yet
    ਜੇ (ਅੰਕੜੇ->border_ਖੱਬਾ == 0 && ਅੰਕੜੇ->border_ਸੱਜਾ == 0 && ਅੰਕੜੇ->border_ਸਿਖਰ == 0 && ਅੰਕੜੇ->border_bottom == 0) {
        X11_Get_Border_ਮੁੱਲਾਂ(ਅੰਕੜੇ);
    }

    ਜੇ (ਸੈੱਟ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ਅਚਲ ਪੂਰਨ tx = (ਅੰਕੜੇ->pending_position ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->x) - (ਅੰਕੜੇ->was_shown ? 0 : ਅੰਕੜੇ->border_ਖੱਬਾ);
        ਅਚਲ ਪੂਰਨ ty = (ਅੰਕੜੇ->pending_position ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->y) - (ਅੰਕੜੇ->was_shown ? 0 : ਅੰਕੜੇ->border_ਸਿਖਰ);
        ਪੂਰਨ x, y;

        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, tx, ty, &x, &y);

        ਅੰਕੜੇ->pending_position = false;
        X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    ਅੰਕੜੇ->ਮਾਪ_move_event_flags = X11_ਮਾਪ_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    ਅੰਕੜੇ->ਮਾਪ_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
    ਅੰਕੜੇ->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    ਜੇ (ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.type) {
        ਪੂਰਨ x, y;
        SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.x, ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.y, &x, &y);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.ਚੌੜਾਈ, ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.ਉਚਾਈ);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, x, y);
    }
}

ਖਾਲੀ X11_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਪੂਰਨ screen = (displaydata ? displaydata->screen : 0);
    Display *display = ਅੰਕੜੇ->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ਅਚਲ bool is_mapped = X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ);
    X11_XWithdraw_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, screen);
    ਜੇ (is_mapped && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&ਅੰਕੜੇ->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
        SDL_ਖਿੜਕੀ *new_focus;
        ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(ਖਿੜਕੀ, &new_focus);
        X11_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ਸਥਿਰ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_ਸਰਗਰਮ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_ਅੰਕੜੇ(ਖਿੜਕੀ);

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom NET_ਸਰਗਰਮ_ਖਿੜਕੀ = ਅੰਕੜੇ->videodata->atoms.NET_ਸਰਗਰਮ_ਖਿੜਕੀ;

    ਜੇ (X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_ਸੁਨੇਹਾ;
        e.xclient.ਸੁਨੇਹਾ_type = NET_ਸਰਗਰਮ_ਖਿੜਕੀ;
        e.xclient.format = 32;
        e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
        e.xclient.ਅੰਕੜੇ.l[0] = 1; // source indication. 1 = application
        e.xclient.ਅੰਕੜੇ.l[1] = ਅੰਕੜੇ->user_ਸਮਾਂ;
        e.xclient.ਅੰਕੜੇ.l[2] = 0;

        X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                       Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);

        X11_XFlush(display);
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow);
    ਜੇ (bActivate) {
        X11_ਸੈੱਟ_ਖਿੜਕੀ_ਸਰਗਰਮ(_this, ਖਿੜਕੀ);
    }
    X11_XFlush(display);
}

ਸਥਿਰ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Maximized(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool maximized)
{
    CHECK_ਖਿੜਕੀ_ਅੰਕੜੇ(ਖਿੜਕੀ);

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom _NET_WM_STATE = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        ਵਾਪਸ true;
    }

    ਜੇ (X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_ਸੁਨੇਹਾ;
        e.xclient.ਸੁਨੇਹਾ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
        e.xclient.ਅੰਕੜੇ.l[0] =
            maximized ? NET_WM_STATE_ਜੋੜੋ : _NET_WM_STATE_REMOVE;
        e.xclient.ਅੰਕੜੇ.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.ਅੰਕੜੇ.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.ਅੰਕੜੇ.l[3] = 0l;

        ਜੇ (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            ਅੰਕੜੇ->expected.x = bounds.x + ਅੰਕੜੇ->border_ਖੱਬਾ;
            ਅੰਕੜੇ->expected.y = bounds.y + ਅੰਕੜੇ->border_ਸਿਖਰ;
            ਅੰਕੜੇ->expected.w = bounds.w - (ਅੰਕੜੇ->border_ਖੱਬਾ + ਅੰਕੜੇ->border_ਸੱਜਾ);
            ਅੰਕੜੇ->expected.h = bounds.h - (ਅੰਕੜੇ->border_ਸਿਖਰ + ਅੰਕੜੇ->border_bottom);
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->expected.x = ਖਿੜਕੀ->floating.x;
            ਅੰਕੜੇ->expected.y = ਖਿੜਕੀ->floating.y;
            ਅੰਕੜੇ->expected.w = ਖਿੜਕੀ->floating.w;
            ਅੰਕੜੇ->expected.h = ਖਿੜਕੀ->floating.h;
        }

        X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                       Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);
    } ਨਹੀਂਤਾਂ {
        X11_ਸੈੱਟ_Net_WMState(_this, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->flags);
    }
    X11_XFlush(display);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->ਖਿੜਕੀ_was_maximized = true;
        ਵਾਪਸ;
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Maximized(_this, ਖਿੜਕੀ, true);
    }
}

ਖਾਲੀ X11_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;

    ਜੇ (ਅੰਕੜੇ->pending_operation & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        SDL_Sync_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }

    ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MINIMIZE;
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਅੰਕੜੇ->ਖਿੜਕੀ_was_maximized = !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED);
    }
    X11_XIconify_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, displaydata->screen);
    X11_XFlush(display);
}

ਖਾਲੀ X11_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Don't restore the window the first time it is being shown.
    ਜੇ (!ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->was_shown) {
        ਵਾਪਸ;
    }

    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->ਖਿੜਕੀ_was_maximized = false;
        ਵਾਪਸ;
    }

    ਜੇ (ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_MAXIMIZED) ||
        (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ਅਚਲ bool maximize = !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->ਖਿੜਕੀ_was_maximized;
    X11_ਸੈੱਟ_ਖਿੜਕੀ_Maximized(_this, ਖਿੜਕੀ, maximize);
    X11_Show_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    X11_ਸੈੱਟ_ਖਿੜਕੀ_ਸਰਗਰਮ(_this, ਖਿੜਕੀ);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ਸਥਿਰ SDL_Fullscreen_ਨਤੀਜਾ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_ਰਾਹੀਂ_WM(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = _display->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom _NET_WM_STATE = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    ਜੇ (!ਅੰਕੜੇ->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    ਜੇ (X11_Is_ਖਿੜਕੀ_Mapped(_this, ਖਿੜਕੀ)) {
        XEvent e;

        // Flush any pending fullscreen events.
        ਜੇ (ਅੰਕੜੇ->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
        }

        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
            ਜੇ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                ਵਾਪਸ SDL_FULLSCREEN_FAILED;
            } ਨਹੀਂਤਾਂ ਜੇ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        ਜੇ (fullscreen && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_ਮਾਪ_Hints();
            ਲੰਮਾ flags = 0;
            X11_XGetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ਮਾਪ | PMax_ਮਾਪ | PAspect);
            X11_XSetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_ਸੁਨੇਹਾ;
        e.xclient.ਸੁਨੇਹਾ_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
        e.xclient.ਅੰਕੜੇ.l[0] =
            fullscreen ? NET_WM_STATE_ਜੋੜੋ : _NET_WM_STATE_REMOVE;
        e.xclient.ਅੰਕੜੇ.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.ਅੰਕੜੇ.l[3] = 0l;

        X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                       Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        ਜੇ (((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) != 0) != (fullscreen != 0)) {
            ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        ਜੇ (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_ਖਿੜਕੀ_Position(ਖਿੜਕੀ);
            SDL_copyp(&ਅੰਕੜੇ->requested_fullscreen_ਬਹੁਲਕ, &ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
            ਜੇ (fullscreen != !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
                ਅੰਕੜੇ->ਖਿੜਕੀ_was_maximized = !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED);
            }
            ਅੰਕੜੇ->expected.x = displaydata->x;
            ਅੰਕੜੇ->expected.y = displaydata->y;
            ਅੰਕੜੇ->expected.w = _display->current_ਬਹੁਲਕ->w;
            ਅੰਕੜੇ->expected.h = _display->current_ਬਹੁਲਕ->h;

            // Only move the window if it isn't already on the target display.
            ਜੇ (!current || current != _display->id) {
                X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, displaydata->x, displaydata->y);
                ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } ਨਹੀਂਤਾਂ {
            SDL_zero(ਅੰਕੜੇ->requested_fullscreen_ਬਹੁਲਕ);
            ਅੰਕੜੇ->pending_position = ਅੰਕੜੇ->fs_repositioned;
            ਅੰਕੜੇ->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_ਸੁਨੇਹਾ;
            e.xclient.ਸੁਨੇਹਾ_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
            ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ_was_maximized) {
                e.xclient.ਅੰਕੜੇ.l[0] = NET_WM_STATE_ਜੋੜੋ;
            } ਨਹੀਂਤਾਂ {
                e.xclient.ਅੰਕੜੇ.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.ਅੰਕੜੇ.l[1] = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.ਅੰਕੜੇ.l[2] = ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.ਅੰਕੜੇ.l[3] = 0l;
            X11_XSendEvent(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen), 0,
                           Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, &e);
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ਖਿੜਕੀ_Flags flags;

        flags = ਖਿੜਕੀ->flags;
        ਜੇ (fullscreen) {
            flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;
        } ਨਹੀਂਤਾਂ {
            flags &= ~SDL_ਖਿੜਕੀ_FULLSCREEN;
        }
        X11_ਸੈੱਟ_Net_WMState(_this, ਅੰਕੜੇ->xwindow, flags);
    }

    ਜੇ (ਅੰਕੜੇ->visual->class == ਸਿੱਧਾ_Color) {
        ਜੇ (fullscreen) {
            X11_XInstallColormap(display, ਅੰਕੜੇ->colormap);
        } ਨਹੀਂਤਾਂ {
            X11_XUninstallColormap(display, ਅੰਕੜੇ->colormap);
        }
    }

    ਵਾਪਸ SDL_FULLSCREEN_PENDING;
}

ਸਥਿਰ SDL_Fullscreen_ਨਤੀਜਾ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = _display->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਅਚਲ ਪੂਰਨ screen = displaydata->screen;

    ਜੇ (!ਅੰਕੜੇ->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    ਜੇ (ਅੰਕੜੇ->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, fullscreen ? SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN : SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
    ਜੇ (fullscreen) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_ਮਾਪ_Hints();
            ਲੰਮਾ flags = 0;
            X11_XGetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ਮਾਪ | PMax_ਮਾਪ | PAspect);
            X11_XSetWMNormalHints(display, ਅੰਕੜੇ->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        ਸੈੱਟ_ਖਿੜਕੀ_Bordered(display, screen, ਅੰਕੜੇ->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ਅੰਕੜੇ->expected.x = rect.x;
        ਅੰਕੜੇ->expected.y = rect.y;
        ਅੰਕੜੇ->expected.w = rect.w;
        ਅੰਕੜੇ->expected.h = rect.h;
        X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, rect.x, rect.y);
        X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, rect.w, rect.h);
        X11_XRaise_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow);
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ਅੰਕੜੇ->expected.x = ਖਿੜਕੀ->windowed.x;
        ਅੰਕੜੇ->expected.y = ਖਿੜਕੀ->windowed.y;
        ਅੰਕੜੇ->expected.w = ਖਿੜਕੀ->windowed.w;
        ਅੰਕੜੇ->expected.h = ਖਿੜਕੀ->windowed.h;
        X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->windowed.w, ਖਿੜਕੀ->windowed.h);
        X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਖਿੜਕੀ->windowed.x, ਖਿੜਕੀ->windowed.y);

        ਸੈੱਟ_ਖਿੜਕੀ_Bordered(display, screen, ਅੰਕੜੇ->xwindow, (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) == 0);
        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਅੰਕੜੇ->ਖਿੜਕੀ, false);
    }

    X11_XFlush(display);

    ਵਾਪਸ SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_ਨਤੀਜਾ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_ਖਿੜਕੀ_ਅੰਕੜੇ(ਖਿੜਕੀ);
    CHECK_DISPLAY_ਅੰਕੜੇ(_display);

    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->net_wm) {
        ਵਾਪਸ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_ਰਾਹੀਂ_WM(_this, ਖਿੜਕੀ, _display, fullscreen);
    }

    ਵਾਪਸ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_Legacy(_this, ਖਿੜਕੀ, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ;
    ਪੂਰਨ format, ਗਿਣਤੀ_2;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ਸਥਿਰ ਖਾਲੀ X11_ReadProperty(SDL_x11Prop *p, Display *disp, ਖਿੜਕੀ_2 w, Atom prop)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ret = ਨਿਰਾ;
    Atom type;
    ਪੂਰਨ fmt;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਗਿਣਤੀ_2;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_ਖੱਬਾ;
    ਪੂਰਨ ਬਾਈਟਾਂ_fetch = 0;

    ਕਰੋ {
        ਜੇ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_ਖਿੜਕੀ_Property(disp, w, prop, 0, ਬਾਈਟਾਂ_fetch, False, AnyPropertyType, &type, &fmt, &ਗਿਣਤੀ_2, &ਬਾਈਟਾਂ_ਖੱਬਾ, &ret);
        ਬਾਈਟਾਂ_fetch += ਬਾਈਟਾਂ_ਖੱਬਾ;
    } ਜਦੋਂ (ਬਾਈਟਾਂ_ਖੱਬਾ != 0);

    p->ਅੰਕੜੇ = ret;
    p->format = fmt;
    p->ਗਿਣਤੀ_2 = ਗਿਣਤੀ_2;
    p->type = type;
}

ਖਾਲੀ *X11_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    XWindow_ਗੁਣ ਗੁਣ;
    Atom icc_profile_atom;
    ਅੱਖਰ icc_atom_string[ਆਕਾਰ("_ICC_PROFILE_") + 12];
    ਖਾਲੀ *ret_icc_profile_ਅੰਕੜੇ = ਨਿਰਾ;
    CARD8 *icc_profile_ਅੰਕੜੇ;
    ਪੂਰਨ real_format;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਅੰਕੜੇ->xwindow, &ਗੁਣ);
    ਜੇ (X11_XScreen_ਸੰਖਿਆ_ਦਾ_Screen(ਗੁਣ.screen) > 0) {
        (ਖਾਲੀ)SDL_snprintf(icc_atom_string, ਆਕਾਰ("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_ਸੰਖਿਆ_ਦਾ_Screen(ਗੁਣ.screen));
    } ਨਹੀਂਤਾਂ {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", ਆਕਾਰ("_ICC_PROFILE"));
    }
    X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਜੜ੍ਹ_ਖਿੜਕੀ_ਦਾ_Screen(ਗੁਣ.screen), &ਗੁਣ);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    ਜੇ (icc_profile_atom == None) {
        SDL_ਸੈੱਟ_Error("Screen is not calibrated.");
        ਵਾਪਸ ਨਿਰਾ;
    }

    X11_ReadProperty(&atomProp, display, ਜੜ੍ਹ_ਖਿੜਕੀ_ਦਾ_Screen(ਗੁਣ.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.ਗਿਣਤੀ_2;
    icc_profile_ਅੰਕੜੇ = atomProp.ਅੰਕੜੇ;
    ਜੇ (real_format == None) {
        SDL_ਸੈੱਟ_Error("Screen is not calibrated.");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ret_icc_profile_ਅੰਕੜੇ = SDL_malloc(real_nitems);
    ਜੇ (!ret_icc_profile_ਅੰਕੜੇ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_memcpy(ret_icc_profile_ਅੰਕੜੇ, icc_profile_ਅੰਕੜੇ, real_nitems);
    *ਮਾਪ = real_nitems;
    X11_XFree(icc_profile_ਅੰਕੜੇ);

    ਵਾਪਸ ret_icc_profile_ਅੰਕੜੇ;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display;

    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid window data");
    }
    ਅੰਕੜੇ->mouse_grabbed = false;
    ਅੰਕੜੇ->pending_grab = false;

    display = ਅੰਕੜੇ->videodata->display;

    ਜੇ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
            ਵਾਪਸ true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        ਜੇ (ਅੰਕੜੇ->xinput2_mouse_enabled && SDL_GetMouseState(ਨਿਰਾ, ਨਿਰਾ)) {
            ਅੰਕੜੇ->pending_grab = true;
            ਵਾਪਸ true;
        }

        // Try to grab the mouse
        ਜੇ (!ਅੰਕੜੇ->videodata->broken_ਸੂਚਕ_grab) {
            ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਕਾਬ = Button_Press_ਨਕਾਬ | Button_Release_ਨਕਾਬ | ਸੂਚਕ_Motion_ਨਕਾਬ | Focus_Change_ਨਕਾਬ;
            ਪੂਰਨ attempts;
            ਪੂਰਨ ਨਤੀਜਾ = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            ਲਈ (attempts = 0; attempts < 100; attempts++) {
                ਨਤੀਜਾ = X11_XGrab_ਸੂਚਕ(display, ਅੰਕੜੇ->xwindow, False, ਨਕਾਬ, Grab_ਬਹੁਲਕ_Async,
                                          Grab_ਬਹੁਲਕ_Async, ਅੰਕੜੇ->xwindow, None, Current_ਸਮਾਂ);
                ਜੇ (ਨਤੀਜਾ == GrabSuccess) {
                    ਅੰਕੜੇ->mouse_grabbed = true;
                    ਰੋਕੋ;
                }
                SDL_Delay(50);
            }

            ਜੇ (ਨਤੀਜਾ != GrabSuccess) {
                ਅੰਕੜੇ->videodata->broken_ਸੂਚਕ_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, ਖਿੜਕੀ);

        // Raise the window if we grab the mouse
        X11_XRaise_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow);
    } ਨਹੀਂਤਾਂ {
        X11_XUngrab_ਸੂਚਕ(display, Current_ਸਮਾਂ);

        X11_Xinput2UngrabTouch(_this, ਖਿੜਕੀ);
    }
    X11_XSync(display, False);

    ਜੇ (!ਅੰਕੜੇ->videodata->broken_ਸੂਚਕ_grab) {
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display;

    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid window data");
    }

    display = ਅੰਕੜੇ->videodata->display;

    ਜੇ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
            ਵਾਪਸ true;
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
        ਜੇ (_this->ਅੰਦਰੂਨੀ->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            ਜੇ (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_ਸੁਨੇਹਾ_Event client_ਸੁਨੇਹਾ;
                client_ਸੁਨੇਹਾ.type = Client_ਸੁਨੇਹਾ;
                client_ਸੁਨੇਹਾ.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
                client_ਸੁਨੇਹਾ.format = 32;
                client_ਸੁਨੇਹਾ.ਸੁਨੇਹਾ_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_ਸੁਨੇਹਾ.ਅੰਕੜੇ.l[0] = 1;
                client_ਸੁਨੇਹਾ.ਅੰਕੜੇ.l[1] = Current_ਸਮਾਂ;

                X11_XSendEvent(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display), False, Substructure_Notify_ਨਕਾਬ | Substructure_Redirect_ਨਕਾਬ, (XEvent *)&client_ਸੁਨੇਹਾ);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, ਅੰਕੜੇ->xwindow, True, Grab_ਬਹੁਲਕ_Async,
                          Grab_ਬਹੁਲਕ_Async, Current_ਸਮਾਂ);
    } ਨਹੀਂਤਾਂ {
        X11_XUngrabKeyboard(display, Current_ਸਮਾਂ);
    }
    X11_XSync(display, False);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ) {
        SDL_Video_ਅੰਕੜੇ *videodata = ਅੰਕੜੇ->videodata;
        Display *display = videodata->display;
        ਪੂਰਨ numwindows = videodata->numwindows;
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ **windowlist = videodata->windowlist;
        ਪੂਰਨ i;

        ਜੇ (windowlist) {
            ਲਈ (i = 0; i < numwindows; ++i) {
                ਜੇ (windowlist[i] && (windowlist[i]->ਖਿੜਕੀ == ਖਿੜਕੀ)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = ਨਿਰਾ;
                    videodata->numwindows--;
                    ਰੋਕੋ;
                }
            }
        }

        X11_Destroy_ਨਿਵੇਸ਼_Context(ਅੰਕੜੇ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_ਪਦ_Resize_Sync(ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
            X11_XDestroy_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow);
            X11_XFlush(display);
        }
        SDL_free(ਅੰਕੜੇ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        ਜੇ (videodata->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ == ਖਿੜਕੀ) {
            X11_Destroy_ਸੂਚਕ_Barrier(_this, ਖਿੜਕੀ);
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled)
{
    ਵਾਪਸ true; // just succeed, the real work is done elsewhere.
}

ਖਾਲੀ X11_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom XdndAware = ਅੰਕੜੇ->videodata->atoms.XdndAware;

    ਜੇ (accept) {
        Atom xdnd_ਸੰਸਕਰਣ = 5;
        X11_XChangeProperty(display, ਅੰਕੜੇ->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&xdnd_ਸੰਸਕਰਣ, 1);
    } ਨਹੀਂਤਾਂ {
        X11_XDeleteProperty(display, ਅੰਕੜੇ->xwindow, XdndAware);
    }
}

bool X11_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, ਅੰਕੜੇ->xwindow);
    ਜੇ (!wmhints) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    ਅੰਕੜੇ->flashing_ਖਿੜਕੀ = false;
    ਅੰਕੜੇ->flash_cancel_ਸਮਾਂ = 0;

    ਚੋਣ (operation) {
    ਹਾਲਤ SDL_FLASH_CANCEL:
        // Taken care of above
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLASH_BRIEFLY:
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ਅੰਕੜੇ->flashing_ਖਿੜਕੀ = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            ਅੰਕੜੇ->flash_cancel_ਸਮਾਂ = SDL_GetTicks() + 1000;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SDL_FLASH_UNTIL_FOCUSED:
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ਅੰਕੜੇ->flashing_ਖਿੜਕੀ = true;
        }
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }

    X11_XSetWMHints(display, ਅੰਕੜੇ->xwindow, wmhints);
    X11_XFree(wmhints);
    ਵਾਪਸ true;
}

bool SDL_X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(Display *display, ਖਿੜਕੀ_2 xwindow, ਅੱਖਰ *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    ਪੂਰਨ conv = X11_Xmb_ਪਾਠ_List_ਮੰਜ਼ਿਲ_ਪਾਠ_Property(display, &title, 1, XTextStyle, &titleprop);
    ਸਥਿਤੀ_2 ਸਥਿਤੀ;

    ਜੇ (X11_XSupportsLocale() != True) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Current locale not supported by X server, cannot continue.");
    }

    ਜੇ (conv == 0) {
        X11_XSet_ਪਾਠ_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.ਮੁੱਲ);
        // we know this can't be a locale error as we checked X locale validity
    } ਨਹੀਂਤਾਂ ਜੇ (conv < 0) {
        ਵਾਪਸ SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
    } ਨਹੀਂਤਾਂ { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        ਵਾਪਸ true;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਸਥਿਤੀ = X11_Xutf8_ਪਾਠ_List_ਮੰਜ਼ਿਲ_ਪਾਠ_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    ਜੇ (ਸਥਿਤੀ == Success) {
        X11_XSet_ਪਾਠ_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.ਮੁੱਲ);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#ਜੇ_ਅੰਤ

    X11_XFlush(display);
    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਖਿੜਕੀ_2 ਜੜ੍ਹ = ਜੜ੍ਹ_ਖਿੜਕੀ(display, displaydata->screen);
    XClient_ਸੁਨੇਹਾ_Event e;
    ਖਿੜਕੀ_2 ਬੱਚਾ_Return_2;
    ਪੂਰਨ wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, ਅੰਕੜੇ->xwindow, ਜੜ੍ਹ, x, y, &wx, &wy, &ਬੱਚਾ_Return_2);

    e.type = Client_ਸੁਨੇਹਾ;
    e.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
    e.ਸੁਨੇਹਾ_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.ਅੰਕੜੇ.l[0] = 0;  // GTK device ID (unused)
    e.ਅੰਕੜੇ.l[1] = wx; // X coordinate relative to root
    e.ਅੰਕੜੇ.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, ਜੜ੍ਹ, False, Substructure_Redirect_ਨਕਾਬ | Substructure_Notify_ਨਕਾਬ, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) &&
        (ਅੰਕੜੇ->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(ਖਿੜਕੀ);
            ਵਾਪਸ true;
    }

    ਅਚਲ Uint64 current_ਸਮਾਂ = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
        ਜੇ (_this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns &&
            current_ਸਮਾਂ < _this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns - current_ਸਮਾਂ, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_ਮੰਜ਼ਿਲ_NS(1000) : SDL_MS_ਮੰਜ਼ਿਲ_NS(100);

    ਵਾਪਸ X11_Sync_ਖਿੜਕੀ_Timeout(_this, ਖਿੜਕੀ, timeout);
}

bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable)
{
    ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        Display *display = ਅੰਕੜੇ->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, ਅੰਕੜੇ->xwindow);
        ਜੇ (!wmhints) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get WM hints");
        }

        wmhints->ਨਿਵੇਸ਼ = focusable ? True : False;
        wmhints->flags |= ਨਿਵੇਸ਼_Hint;

        X11_XSetWMHints(display, ਅੰਕੜੇ->xwindow, wmhints);
        X11_XFree(wmhints);
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            ਜੇ (!focusable && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
                SDL_ਖਿੜਕੀ *new_focus;
                ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(ਖਿੜਕੀ, &new_focus);
                X11_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
            } ਨਹੀਂਤਾਂ ਜੇ (focusable) {
                ਜੇ (SDL_ShouldFocusPopup(ਖਿੜਕੀ)) {
                    X11_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
                }
            }
        }

        ਵਾਪਸ true;
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
