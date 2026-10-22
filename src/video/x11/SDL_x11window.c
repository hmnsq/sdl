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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../core/unix/SDL_appid.h"

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11mouse.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11xfixes.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#جيڪڏهن_پورو

#ضمن "SDL_x11xsync.h"

#وصف_ڪريو _NET_WM_STATE_REMOVE 0l
#وصف_ڪريو NET_WM_STATE_جوڙيو    1l

#وصف_ڪريو CHECK_دري_معلومات(دري)                                       \
    إذا (!دري) {                                                      \
        أرجع SDL_سيٽ_Error("Invalid window");                          \
    }                                                                   \
    إذا (!دري->اندروني) {                                          \
        أرجع SDL_سيٽ_Error("Invalid window driver data");              \
    }

#وصف_ڪريو CHECK_DISPLAY_معلومات(display)                                     \
    إذا (!_display) {                                                    \
        أرجع SDL_سيٽ_Error("Invalid display");                         \
    }                                                                   \
    إذا (!_display->اندروني) {                                        \
        أرجع SDL_سيٽ_Error("Invalid display driver data");             \
    }

ساكن Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == MapNotify && ev->xmap.دري == *((دري_2 *)win);
}
ساكن Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == UnmapNotify && ev->xunmap.دري == *((دري_2 *)win);
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

ساكن bool X11_CheckCurrentDesktop(ثابت حرف *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ثابت حرف *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    إذا (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        أرجع true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    إذا (desktopVar && SDL_strcasestr(desktopVar, name)) {
        أرجع true;
    }

    أرجع false;
}

ساكن bool X11_Is_دري_Mapped(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Video_معلومات *videodata = _this->اندروني;
    XWindow_خاصيتون attr;

    X11_XGet_دري_خاصيتون(videodata->display, معلومات->xwindow, &attr);
    إذا (attr.map_state != IsUnmapped) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

ساكن bool X11_IsDisplayOk(Display *display)
{
    إذا (display->flags & XlibDisplayIOError) {
        أرجع false;
    }
    أرجع true;
}

#إذا 0
ساكن bool X11_IsActionAllowed(SDL_دري *دري, Atom action)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Atom _NET_WM_ALLOWED_ACTIONS = معلومات->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = معلومات->videodata->display;
    صحيح form;
    بنانشان ڊگهو remain;
    بنانشان ڊگهو len, i;
    Atom *list;
    bool ret = false;

    إذا (X11_XGet_دري_Property(display, معلومات->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (بنانشان حرف **)&list) == Success) {
        لكل (i=0; i<len; ++i) {
            إذا (list[i] == action) {
                ret = true;
                اكسر;
            }
        }
        X11_XFree(list);
    }
    أرجع ret;
}
#جيڪڏهن_پورو // 0

ساكن فراغ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخري_position_pending = دري->آخري_position_pending;
    ثابت bool آخري_سائيز_pending = دري->آخري_سائيز_pending;

    X11_Sync_دري(_this, دري);

    دري->آخري_position_pending = آخري_position_pending;
    دري->آخري_سائيز_pending = آخري_سائيز_pending;
}

فراغ X11_سيٽ_Net_WMState(SDL_VideoDevice *_this, دري_2 xwindow, SDL_دري_Flags flags)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
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
    صحيح ڳڻپ = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    إذا (flags & SDL_دري_ALWAYS_ON_چوٽي) {
        atoms[ڳڻپ++] = _NET_WM_STATE_ABOVE;
    }
    إذا (flags & SDL_دري_UTILITY) {
        atoms[ڳڻپ++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[ڳڻپ++] = _NET_WM_STATE_SKIP_PAGER;
    }
    إذا (flags & SDL_دري_داخلا_FOCUS) {
        atoms[ڳڻپ++] = _NET_WM_STATE_FOCUSED;
    }
    إذا (flags & SDL_دري_MAXIMIZED) {
        atoms[ڳڻپ++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[ڳڻپ++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    إذا (flags & SDL_دري_FULLSCREEN) {
        atoms[ڳڻپ++] = _NET_WM_STATE_FULLSCREEN;
    }
    إذا (flags & SDL_دري_MODAL) {
        atoms[ڳڻپ++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(ڳڻپ <= SDL_arraysize(atoms));

    إذا (ڳڻپ > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_گهڻائي_Replace, (بنانشان حرف *)atoms, ڳڻپ);
    } وإلا {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ساكن فراغ X11_ConstrainPopup(SDL_دري *دري, bool output_منزل_pending)
{
    // Clamp popup windows to the output borders
    إذا (SDL_دري_IS_POPUP(دري)) {
        SDL_دري *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = دري->آخري_position_pending ? دري->pending.x : دري->floating.x;
        صحيح abs_y = دري->آخري_position_pending ? دري->pending.y : دري->floating.y;
        صحيح وٿي_x = 0, وٿي_y = 0;

        إذا (دري->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = دري->والد; SDL_دري_IS_POPUP(w); w = w->والد) {
                وٿي_x += w->x;
                وٿي_y += w->y;
            }

            وٿي_x += w->x;
            وٿي_y += w->y;
            abs_x += وٿي_x;
            abs_y += وٿي_y;

            displayID = SDL_Get_Display_For_دري(w);

            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + دري->w > rect.x + rect.w) {
                abs_x -= (abs_x + دري->w) - (rect.x + rect.w);
            }
            إذا (abs_y + دري->h > rect.y + rect.h) {
                abs_y -= (abs_y + دري->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            دري->pending.x = abs_x - وٿي_x;
            دري->pending.y = abs_y - وٿي_y;
        } وإلا {
            دري->floating.x = دري->windowed.x = abs_x - وٿي_x;
            دري->floating.y = دري->windowed.y = abs_y - وٿي_y;
        }
    }
}

ساكن فراغ X11_سيٽ_Keyboard_Focus(SDL_دري *دري, bool سيٽ_سرگرم_focus)
{
    SDL_دري *toplevel = دري;

    // Find the toplevel parent
    طالما (SDL_دري_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = دري;

    إذا (سيٽ_سرگرم_focus && !دري->is_hiding && !دري->is_destroying) {
        SDL_سيٽ_Keyboard_Focus(دري);
    }
}

SDL_دري_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_دري *دري, دري_2 xwindow)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    صحيح actualFormat;
    بنانشان ڊگهو i, انگ_شيون, بائيٽون_After;
    بنانشان حرف *property_قدر = عدم;
    ڊگهو max_ڊيگهائي = 1024;
    SDL_دري_Flags flags = 0;

    إذا (X11_XGet_دري_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_ڊيگهائي, False, XA_ATOM, &actualType,
                               &actualFormat, &انگ_شيون, &بائيٽون_After,
                               &property_قدر) == Success) {
        Atom *atoms = (Atom *)property_قدر;
        صحيح maximized = 0;
        صحيح fullscreen = 0;

        لكل (i = 0; i < انگ_شيون; ++i) {
            إذا (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_دري_MINIMIZED | SDL_دري_OCCLUDED;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_دري_داخلا_FOCUS;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        إذا (fullscreen == 1) {
            flags |= SDL_دري_FULLSCREEN;
        } وإلا إذا (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (دري->flags & SDL_دري_FULLSCREEN);
        }

        إذا (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            إذا (fullscreen) {
                flags |= (دري->flags & SDL_دري_MAXIMIZED);
            } وإلا {
                flags |= SDL_دري_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_خاصيتون attr;
            SDL_zero(attr);
            X11_XGet_دري_خاصيتون(videodata->display, xwindow, &attr);
            إذا (attr.map_state == IsUnmapped) {
                flags |= SDL_دري_HIDDEN;
            }
        }
        X11_XFree(property_قدر);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    أرجع flags;
}

ساكن bool تياري_دري_معلومات(SDL_VideoDevice *_this, SDL_دري *دري, دري_2 w)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    SDL_دري_معلومات *معلومات;

    // Allocate the window data
    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }
    معلومات->videodata = videodata;
    معلومات->دري = دري;
    معلومات->xwindow = w;
    معلومات->ڪاميابي_test_نتيجو = SDL_HITTEST_عام;

    X11_Create_داخلا_Context(معلومات);

    // Associate the data with the window

    إذا (videodata->numwindows >= videodata->windowlistlength) {
        SDL_دري_معلومات ** new_windowlist = (SDL_دري_معلومات **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * حجم(*videodata->windowlist));
        إذا (!new_windowlist) {
            اذهب error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_خاصيتون attrib;

        X11_XGet_دري_خاصيتون(معلومات->videodata->display, w, &attrib);
        إذا (!SDL_دري_IS_POPUP(دري)) {
            دري->x = دري->windowed.x = دري->floating.x = attrib.x;
            دري->y = دري->windowed.y = دري->floating.y = attrib.y - معلومات->border_چوٽي;
        }
        دري->w = دري->windowed.w = دري->floating.w = attrib.ويڪر;
        دري->h = دري->windowed.h = دري->floating.h = attrib.اوچائي;
        إذا (attrib.map_state != IsUnmapped) {
            دري->flags &= ~SDL_دري_HIDDEN;
        } وإلا {
            دري->flags |= SDL_دري_HIDDEN;
        }
        معلومات->visual = attrib.visual;
        معلومات->colormap = attrib.colormap;
    }

    دري->flags |= X11_GetNetWMState(_this, دري, w);

    {
        دري_2 Focal_دري;
        صحيح Revert_منزل = 0;
        X11_XGet_داخلا_Focus(معلومات->videodata->display, &Focal_دري, &Revert_منزل);
        إذا (Focal_دري == w) {
            دري->flags |= SDL_دري_داخلا_FOCUS;
        }

        إذا (دري->flags & SDL_دري_داخلا_FOCUS) {
            SDL_سيٽ_Keyboard_Focus(معلومات->دري);
        }

        إذا (دري->flags & SDL_دري_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    إذا (دري->flags & SDL_دري_EXTERNAL) {
        // Query the title from the existing window
        دري->title = X11_Get_دري_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_X11_DISPLAY_اشارو, معلومات->videodata->display);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_X11_SCREEN_عدد, screen);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_X11_دري_عدد, معلومات->xwindow);


#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    إذا ((دري->flags & SDL_دري_OPENGL) &&
        ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_معلومات || X11_GL_UseEGL(_this))
#جيڪڏهن_پورو
    ) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (!_this->egl_معلومات) {
            اذهب error_cleanup;
        }

        // Create the GLES window surface
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)w);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            SDL_سيٽ_Error("Could not create GLES window surface");
            اذهب error_cleanup;
        }
#وإلا
        SDL_سيٽ_Error("Could not create GLES window surface (EGL support not configured)");
        اذهب error_cleanup;
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_EGL
    }
#جيڪڏهن_پورو

    // All done!
    دري->اندروني = معلومات;
    videodata->windowlist[videodata->numwindows++] = معلومات;
    أرجع true;

error_cleanup:
    X11_Destroy_داخلا_Context(معلومات);
    SDL_free(معلومات);
    أرجع false;
}

ساكن فراغ تياري_دري_داخلا(SDL_VideoDevice *_this, SDL_دري *دري)
{
    ڊگهو fevent = 0;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    دري_2 xwindow = معلومات->xwindow;

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8 && معلومات->ic) {
        X11_XGetICValues(معلومات->ic, XNFilterEvents, &fevent, عدم);
    }
#جيڪڏهن_پورو

    X11_Xinput2Select(_this, دري);

    {
        بنانشان صحيح x11_keyboard_events = ڪنجي_Press_نقاب | ڪنجي_Release_نقاب;
        بنانشان صحيح x11_اشارو_events = Button_Press_نقاب | Button_Release_نقاب | اشارو_Motion_نقاب;

        X11_Xinput2SelectMouseAndKeyboard(_this, دري);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        إذا (معلومات->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        إذا (معلومات->xinput2_mouse_enabled) {
            x11_اشارو_events = 0;
        }

        X11_XSelect_داخلا(معلومات->videodata->display, xwindow,
                         (Focus_Change_نقاب | Enter_دري_نقاب | Leave_دري_نقاب | Exposure_نقاب |
                          x11_keyboard_events | x11_اشارو_events |
                          Property_Change_نقاب | Structure_Notify_نقاب |
                          Keymap_State_نقاب | fevent));
    }
}

ساكن فراغ سيٽ_دري_Bordered(Display *display, صحيح screen, دري_2 دري, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    إذا (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        بنية
        {
            بنانشان ڊگهو flags;
            بنانشان ڊگهو functions;
            بنانشان ڊگهو decorations;
            ڊگهو داخلا_گهڻائي;
            بنانشان ڊگهو حالت;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, دري, WM_HINTS, WM_HINTS, 32,
                            Prop_گهڻائي_Replace, (بنانشان حرف *)&MWMHints,
                            حجم(MWMHints) / حجم(ڊگهو));
    } وإلا { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, دري, پاڙ_دري(display, screen));
    }
}

bool X11_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    دري_2 w = (دري_2)SDL_Get_عدد_Property(create_props, SDL_PROP_دري_CREATE_X11_دري_عدد,
                (دري_2)SDL_Get_اشارو_Property(create_props, "sdl2-compat.external_window", عدم));
    إذا (w) {
        دري->flags |= SDL_دري_EXTERNAL;

        إذا (!تياري_دري_معلومات(_this, دري, w)) {
            أرجع false;
        }

        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_دري_داخلا, true)) {
            تياري_دري_داخلا(_this, دري);
        }
        أرجع true;
    }

    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    إذا (!displaydata) {
        أرجع SDL_سيٽ_Error("Could not find display info");
    }

    ثابت bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ثابت bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (دري->flags & SDL_دري_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_دري_معلومات *windowdata;
    Display *display = معلومات->display;
    صحيح screen = displaydata->screen;
    Visual *visual;
    صحيح اونهائي_2;
    XSet_دري_خاصيتون xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_دري_TYPE;
    Atom wintype;
    ثابت حرف *wintype_name = عدم;
    ڊگهو compositor = 1;
    Atom _NET_WM_PID;
    ثابت حرف *hint = عدم;
    صحيح win_x, win_y;
    bool undefined_position = false;

#إذا defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ثابت صحيح transparent = (دري->flags & SDL_دري_TRANSPARENT) ? true : false;
    ثابت حرف *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_دري_VISUALID);
    ثابت حرف *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    إذا (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, سانچو;
        صحيح nvis;

        SDL_zero(سانچو);
        سانچو.visualid = SDL_strtol(forced_visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &سانچو, &nvis);
        إذا (vi) {
            visual = vi->visual;
            اونهائي_2 = vi->اونهائي_2;
            X11_XFree(vi);
        } وإلا {
            أرجع false;
        }
    } وإلا إذا ((دري->flags & SDL_دري_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = عدم;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_معلومات || X11_GL_UseEGL(_this))
#جيڪڏهن_پورو
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } وإلا
#جيڪڏهن_پورو
        {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#جيڪڏهن_پورو
        }

        إذا (!vinfo) {
            أرجع false;
        }
        visual = vinfo->visual;
        اونهائي_2 = vinfo->اونهائي_2;
        X11_XFree(vinfo);
    } وإلا
#جيڪڏهن_پورو
    {
        visual = displaydata->visual;
        اونهائي_2 = displaydata->اونهائي_2;
    }

    xattr.override_redirect = ((دري->flags & SDL_دري_TOOLTIP) || (دري->flags & SDL_دري_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    إذا (visual->class == سڌو_Color) {
        XColor *colorcells;
        صحيح i;
        صحيح ncolors;
        صحيح rmax, gmax, bmax;
        صحيح rmask, gmask, bmask;
        صحيح rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, پاڙ_دري(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        إذا (!xattr.colormap) {
            أرجع SDL_سيٽ_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * حجم(XColor));
        إذا (!colorcells) {
            أرجع false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_نقاب;
        طالما (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_نقاب;
        طالما (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_نقاب;
        طالما (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        لكل (i = 0; i < ncolors; i++) {
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
    } وإلا {
        xattr.colormap =
            X11_XCreateColormap(display, پاڙ_دري(display, screen),
                                visual, AllocNone);
    }

    إذا (دري->undefined_x && دري->undefined_y &&
        دري->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    إذا (SDL_دري_IS_POPUP(دري)) {
        X11_ConstrainPopup(دري, false);
    }
    SDL_Relative_منزل_Global_For_دري(دري,
                                  دري->floating.x, دري->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_دري(display, پاڙ_دري(display, screen),
                          win_x, win_y, دري->floating.w, دري->floating.h,
                          0, اونهائي_2, داخلا_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    إذا (!w) {
        أرجع SDL_سيٽ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    إذا (!(دري->pending_flags & SDL_دري_FULLSCREEN)) {
        سيٽ_دري_Bordered(display, screen, w, !(دري->flags & SDL_دري_BORDERLESS));
    }

    sizehints = X11_XAlloc_سائيز_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    إذا (!(دري->flags & SDL_دري_RESIZABLE)) {
        sizehints->min_ويڪر_2 = sizehints->max_ويڪر_2 = دري->floating.w;
        sizehints->min_اوچائي_2 = sizehints->max_اوچائي_2 = دري->floating.h;
        sizehints->flags |= (PMax_سائيز | PMin_سائيز);
    }
    إذا (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->داخلا_2 = !(دري->flags & SDL_دري_NOT_FOCUSABLE) ? True : False;
    wmhints->دري_گروهه = معلومات->دري_گروهه;
    wmhints->flags = داخلا_Hint | دري_گروهه_Hint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (حرف *)SDL_GetExeName();
    classhints->res_class = (حرف *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, عدم, عدم, عدم, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    إذا (معلومات->pid > 0) {
        ڊگهو pid = (ڊگهو)معلومات->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_گهڻائي_Replace,
                            (بنانشان حرف *)&pid, 1);
    }

    // Set the window manager state
    X11_سيٽ_Net_WMState(_this, w, دري->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_دري_TYPE);
    إذا (دري->flags & SDL_دري_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } وإلا إذا (دري->flags & SDL_دري_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } وإلا إذا (دري->flags & SDL_دري_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } وإلا إذا (hint && *hint) {
        wintype_name = hint;
    } وإلا {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_دري_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_دري_TYPE, XA_ATOM, 32,
                        Prop_گهڻائي_Replace, (بنانشان حرف *)&wintype, 1);
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_گهڻائي_Replace,
                            (بنانشان حرف *)&compositor, 1);
    }

    {
        Atom protocols[4];
        صحيح proto_ڳڻپ = 0;

        protocols[proto_ڳڻپ++] = معلومات->atoms.WM_DELETE_دري; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_ڳڻپ++] = معلومات->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
        إذا (use_resize_sync) {
            protocols[proto_ڳڻپ++] = معلومات->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_ڳڻپ <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_ڳڻپ);
    }

    إذا (!تياري_دري_معلومات(_this, دري, w)) {
        X11_XDestroy_دري(display, w);
        أرجع false;
    }
    windowdata = دري->اندروني;

    // Set the parent if this is a non-popup window.
    إذا (!SDL_دري_IS_POPUP(دري) && دري->والد) {
        X11_XSetTransientForHint(display, w, دري->والد->اندروني->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(دري->pending_flags & SDL_دري_FULLSCREEN) &&
                                               !!(دري->flags & SDL_دري_BORDERLESS);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
    إذا (use_resize_sync) {
        X11_InitResizeSync(دري);
    }
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    إذا (دري->flags & SDL_دري_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_داخلا, 0, 0, region, Shape_سيٽ);
        X11_XDestroyRegion(region);
    }
#جيڪڏهن_پورو

    تياري_دري_داخلا(_this, دري);

    // For _ICC_PROFILE.
    X11_XSelect_داخلا(display, پاڙ_دري(display, screen), Property_Change_نقاب);

    X11_XFlush(display);

    أرجع true;
}

حرف *X11_Get_دري_Title(SDL_VideoDevice *_this, دري_2 xwindow)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    Display *display = معلومات->display;
    صحيح حالت, real_format;
    Atom real_type;
    بنانشان ڊگهو شيون_read, شيون_کاٻو;
    بنانشان حرف *propdata;
    حرف *title = عدم;

    حالت = X11_XGet_دري_Property(display, xwindow, معلومات->atoms._NET_WM_NAME,
                                    0L, 8192L, False, معلومات->atoms.UTF8_STRING, &real_type, &real_format,
                                    &شيون_read, &شيون_کاٻو, &propdata);
    إذا (حالت == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(حرف *, propdata));
        X11_XFree(propdata);
    } وإلا {
        حالت = X11_XGet_دري_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &شيون_read, &شيون_کاٻو, &propdata);
        إذا (حالت == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(حرف *, propdata), شيون_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } وإلا {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    أرجع title;
}

فراغ X11_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    دري_2 xwindow = معلومات->xwindow;
    Display *display = معلومات->videodata->display;
    حرف *title = دري->title ? دري->title : "";

    SDL_X11_سيٽ_دري_Title(display, xwindow, title);
}

ساكن bool caught_x11_error = false;
ساكن صحيح X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    أرجع 0;
}

ساكن فراغ X11_ExternalResizeMoveSync(SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    بنانشان صحيح ٻار_ڳڻپ;
    دري_2 ٻار_Return_2, پاڙ, والد;
    دري_2 *children;
    XWindow_خاصيتون attrs;
    Uint64 timeout = 0;
    صحيح x, y;
    ثابت bool send_move = !!(معلومات->pending_operation & X11_PENDING_OP_MOVE);
    ثابت bool send_resize = !!(معلومات->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_وڻ(display, معلومات->xwindow, &پاڙ, &والد, &children, &ٻار_ڳڻپ);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_منزل_NS(100);
    طالما (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_دري_خاصيتون(display, معلومات->xwindow, &attrs);
        X11_XTranslateCoordinates(display, والد, Default_پاڙ_دري(display),
                                  attrs.x, attrs.y, &x, &y, &ٻار_Return_2);
        SDL_Global_منزل_Relative_For_دري(دري, x, y, &x, &y);

        إذا (!caught_x11_error) {
            إذا ((معلومات->pending_operation & X11_PENDING_OP_MOVE) && (x == معلومات->expected.x + معلومات->border_کاٻو && y == معلومات->expected.y + معلومات->border_چوٽي)) {
                معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            إذا ((معلومات->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.ويڪر == معلومات->expected.w && attrs.اوچائي == معلومات->expected.h)) {
                معلومات->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            إذا (معلومات->pending_operation == X11_PENDING_OP_NONE) {
                اكسر;
            }
        }

        إذا (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            معلومات->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            معلومات->expected.x = x;
            معلومات->expected.y = y;
            معلومات->expected.w = attrs.ويڪر;
            معلومات->expected.h = attrs.اوچائي;
            اكسر;
        }

        SDL_Delay(10);
    }

    إذا (!caught_x11_error) {
        إذا (send_move) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, x, y);
        }
        إذا (send_resize) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, attrs.ويڪر, attrs.اوچائي);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ساكن bool X11_Sync_دري_Timeout(SDL_VideoDevice *_this, SDL_دري *دري, Uint64 param_timeout)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool نتيجو = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    إذا (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    طالما (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        إذا ((معلومات->pending_operation & X11_PENDING_OP_MOVE) && (دري->x == معلومات->expected.x + معلومات->border_کاٻو && دري->y == معلومات->expected.y + معلومات->border_چوٽي)) {
            معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        إذا ((معلومات->pending_operation & X11_PENDING_OP_RESIZE) && (دري->w == معلومات->expected.w && دري->h == معلومات->expected.h)) {
            معلومات->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        إذا (معلومات->pending_operation == X11_PENDING_OP_NONE) {
            إذا (force_exit ||
                (دري->x == معلومات->expected.x + معلومات->border_کاٻو && دري->y == معلومات->expected.y + معلومات->border_چوٽي &&
                 دري->w == معلومات->expected.w && دري->h == معلومات->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                اكسر;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        إذا (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            معلومات->expected.x = دري->x;
            معلومات->expected.y = دري->y;
            معلومات->expected.w = دري->w;
            معلومات->expected.h = دري->h;

            نتيجو = false;
            اكسر;
        }

        SDL_Delay(10);
    }

    معلومات->pending_operation = X11_PENDING_OP_NONE;

    إذا (!caught_x11_error) {
        X11_PumpEvents(_this);
    } وإلا {
        نتيجو = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    أرجع نتيجو;
}

bool X11_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_ICON = معلومات->videodata->atoms._NET_WM_ICON;
    صحيح (*prevHandler)(Display *, XErrorEvent *) = عدم;
    bool نتيجو = true;

    إذا (icon) {
        صحيح x, y;
        صحيح propsize;
        ڊگهو *propdata;
        Uint32 *src;
        ڊگهو *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * حجم(ڊگهو));

        إذا (!propdata) {
            أرجع false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        لكل (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            لكل (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, معلومات->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_گهڻائي_Replace, (بنانشان حرف *)propdata,
                            propsize);
        SDL_free(propdata);

        إذا (caught_x11_error) {
            نتيجو = SDL_سيٽ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    إذا (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    أرجع نتيجو;
}

فراغ X11_Update_دري_Position(SDL_دري *دري, bool use_current_position)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    ثابت صحيح rel_x = use_current_position ? دري->x : دري->pending.x;
    ثابت صحيح rel_y = use_current_position ? دري->y : دري->pending.y;

    SDL_Relative_منزل_Global_For_دري(دري,
                                  rel_x - معلومات->border_کاٻو, rel_y - معلومات->border_چوٽي,
                                  &معلومات->expected.x, &معلومات->expected.y);

    // Attempt to move the window
    إذا (دري->flags & SDL_دري_HIDDEN) {
        دري->اندروني->pending_position = true;
    } وإلا {
        معلومات->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_دري(display, معلومات->xwindow, معلومات->expected.x, معلومات->expected.y);
    }
}

bool X11_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Sync any pending fullscreen or maximize events.
    إذا (دري->اندروني->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, دري);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    إذا (دري->flags & SDL_دري_MAXIMIZED) {
        إذا (دري->اندروني->pending_operation & X11_PENDING_OP_RESTORE) {
            دري->اندروني->pending_position = true;
        }
        أرجع true;
    }

    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        إذا (SDL_دري_IS_POPUP(دري)) {
            X11_ConstrainPopup(دري, true);
        }
        X11_Update_دري_Position(دري, false);
    } وإلا {
        دري->اندروني->fs_repositioned = true;
        SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    أرجع true;
}

فراغ X11_سيٽ_دري_Min_Max(SDL_دري *دري, bool use_current)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_سائيز_Hints();
    ڊگهو hint_flags = 0;

    X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_سائيز | PMax_سائيز | PAspect);

    إذا (معلومات->دري->flags & SDL_دري_RESIZABLE) {
        إذا (معلومات->دري->min_w || معلومات->دري->min_h) {
            sizehints->flags |= PMin_سائيز;
            sizehints->min_ويڪر_2 = معلومات->دري->min_w;
            sizehints->min_اوچائي_2 = معلومات->دري->min_h;
        }
        إذا (معلومات->دري->max_w || معلومات->دري->max_h) {
            sizehints->flags |= PMax_سائيز;
            sizehints->max_ويڪر_2 = معلومات->دري->max_w;
            sizehints->max_اوچائي_2 = معلومات->دري->max_h;
        }
        إذا (معلومات->دري->min_aspect > 0.0f || معلومات->دري->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(معلومات->دري->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(معلومات->دري->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } وإلا {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_سائيز | PMax_سائيز;
        إذا (use_current) {
            sizehints->min_ويڪر_2 = sizehints->max_ويڪر_2 = دري->آخري_سائيز_pending ? دري->pending.w : معلومات->دري->floating.w;
            sizehints->min_اوچائي_2 = sizehints->max_اوچائي_2 = دري->آخري_سائيز_pending ? دري->pending.h : معلومات->دري->floating.h;
        } وإلا {
            sizehints->min_ويڪر_2 = sizehints->max_ويڪر_2 = دري->آخري_سائيز_pending ? دري->pending.w : معلومات->دري->windowed.w;
            sizehints->min_اوچائي_2 = sizehints->max_اوچائي_2 = دري->آخري_سائيز_pending ? دري->pending.h : معلومات->دري->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
    X11_XFree(sizehints);
}

فراغ X11_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (دري->اندروني->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_دري(_this, دري);
    }

    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        X11_سيٽ_دري_Min_Max(دري, true);
    }
}

فراغ X11_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (دري->اندروني->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_دري(_this, دري);
    }

    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        X11_سيٽ_دري_Min_Max(دري, true);
    }
}

فراغ X11_سيٽ_دري_Aspect_تناسب(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (دري->اندروني->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_دري(_this, دري);
    }

    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        X11_سيٽ_دري_Min_Max(دري, true);
    }
}

فراغ X11_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    إذا (معلومات->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, دري);
    }

    // Set the size as pending if the window is being restored.
    إذا (دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_FULLSCREEN)) {
        // New size will be set when the window is restored.
        إذا (معلومات->pending_operation & X11_PENDING_OP_RESTORE) {
            معلومات->pending_سائيز = true;
        } وإلا {
            // Can't resize the window.
            دري->آخري_سائيز_pending = false;
        }
        أرجع;
    }

    إذا (!(دري->flags & SDL_دري_RESIZABLE)) {
        إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_سائيز_Hints();
            ڊگهو userhints;
            صحيح dest_x, dest_y;

            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &userhints);

            معلومات->expected.w = sizehints->min_ويڪر_2 = sizehints->max_ويڪر_2 = دري->pending.w;
            معلومات->expected.h = sizehints->min_اوچائي_2 = sizehints->max_اوچائي_2 = دري->pending.h;
            sizehints->flags |= PMin_سائيز | PMax_سائيز;
            معلومات->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);

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
            X11_XResize_دري(display, معلومات->xwindow, دري->pending.w, دري->pending.h);
            ثابت صحيح x = دري->آخري_position_pending ? دري->pending.x : دري->x;
            ثابت صحيح y = دري->آخري_position_pending ? دري->pending.y : دري->y;
            SDL_Relative_منزل_Global_For_دري(دري,
                                          x - معلومات->border_کاٻو,
                                          y - معلومات->border_چوٽي,
                                          &dest_x, &dest_y);
            X11_XMove_دري(display, معلومات->xwindow, dest_x, dest_y);
            X11_XRaise_دري(display, معلومات->xwindow);

            X11_XFree(sizehints);
        }
    } وإلا {
        معلومات->expected.w = دري->pending.w;
        معلومات->expected.h = دري->pending.h;
        معلومات->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_دري(display, معلومات->xwindow, معلومات->expected.w, معلومات->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    إذا (دري->flags & SDL_دري_EXTERNAL) {
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, دري->pending.w, دري->pending.h);
    }
}

bool X11_Get_دري_Borders_سائيز(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    *کاٻو = معلومات->border_کاٻو;
    *ساڄو = معلومات->border_ساڄو;
    *چوٽي = معلومات->border_چوٽي;
    *bottom = معلومات->border_bottom;

    أرجع true;
}

bool X11_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    Atom NET_WM_دري_OPACITY = معلومات->videodata->atoms.NET_WM_دري_OPACITY;

    إذا (opacity == 1.0f) {
        X11_XDeleteProperty(display, معلومات->xwindow, NET_WM_دري_OPACITY);
    } وإلا {
        ثابت Uint32 FullyOpaque = 0xFFFFFFFF;
        ثابت ڊگهو alpha = (ڊگهو)((مزدوج)opacity * (مزدوج)FullyOpaque);
        X11_XChangeProperty(display, معلومات->xwindow, NET_WM_دري_OPACITY, XA_CARDINAL, 32,
                            Prop_گهڻائي_Replace, (بنانشان حرف *)&alpha, 1);
    }

    أرجع true;
}

bool X11_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_دري_معلومات *والد_معلومات = والد ? والد->اندروني : عدم;
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    Display *display = video_معلومات->display;

    إذا (والد_معلومات) {
        X11_XSetTransientForHint(display, معلومات->xwindow, والد_معلومات->xwindow);
    } وإلا {
        X11_XDeleteProperty(display, معلومات->xwindow, video_معلومات->atoms.WM_TRANSIENT_FOR);
    }

    أرجع true;
}

bool X11_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = video_معلومات->display;
    Uint32 flags = دري->flags;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = معلومات->videodata->atoms._NET_WM_STATE_MODAL;

    إذا (modal) {
        flags |= SDL_دري_MODAL;
    } وإلا {
        flags &= ~SDL_دري_MODAL;
        X11_XDeleteProperty(display, معلومات->xwindow, video_معلومات->atoms.WM_TRANSIENT_FOR);
    }

    إذا (X11_Is_دري_Mapped(_this, دري)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پيغام;
        e.xclient.پيغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.دري = معلومات->xwindow;
        e.xclient.معلومات.l[0] = modal ? NET_WM_STATE_جوڙيو : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سيٽ_Net_WMState(_this, معلومات->xwindow, flags);
    }

    X11_XFlush(display);

    أرجع true;
}

فراغ X11_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered)
{
    ثابت bool focused = (دري->flags & SDL_دري_داخلا_FOCUS) != 0;
    ثابت bool visible = !(دري->flags & SDL_دري_HIDDEN) && !دري->is_hiding;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;
    XEvent event;

    إذا (معلومات->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_دري(_this, دري);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        سيٽ_دري_Bordered(display, displaydata->screen, معلومات->xwindow, bordered);
        X11_XFlush(display);

        إذا (visible) {
            XWindow_خاصيتون attr;
            افعل {
                X11_XSync(display, False);
                X11_XGet_دري_خاصيتون(display, معلومات->xwindow, &attr);
            } طالما (attr.map_state != IsViewable);

            إذا (focused) {
                X11_XSet_داخلا_Focus(display, معلومات->xwindow, Revert_منزل_والد, Current_وقت);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&معلومات->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&معلومات->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_قدرون(معلومات);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_دري(display, معلومات->xwindow, دري->floating.w, دري->floating.h);
        X11_XSync(display, False);
    } وإلا {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        معلومات->toggle_borders = true;
        معلومات->fullscreen_borders_forced_on = false;
    }
}

فراغ X11_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_دري(_this, دري);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        X11_سيٽ_دري_Min_Max(دري, true);
    }
}

فراغ X11_سيٽ_دري_Always_On_چوٽي(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = معلومات->videodata->atoms._NET_WM_STATE_ABOVE;

    إذا (X11_Is_دري_Mapped(_this, دري)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پيغام;
        e.xclient.پيغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.دري = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            on_چوٽي ? NET_WM_STATE_جوڙيو : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سيٽ_Net_WMState(_this, معلومات->xwindow, دري->flags);
    }
    X11_XFlush(display);
}

فراغ X11_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_دري_ACTIVATE_WHEN_SHOWN, true);
    bool سيٽ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    إذا (معلومات->was_shown) {
        X11_PumpEvents(_this);
    }

    إذا (SDL_دري_IS_POPUP(دري)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(دري, true);
        معلومات->pending_position = true;
        سيٽ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (فراغ)bActivate;

    إذا (!X11_Is_دري_Mapped(_this, دري)) {
        X11_XMapRaised(display, معلومات->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        إذا (!(دري->flags & SDL_دري_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&معلومات->xwindow);
        }
        X11_XFlush(display);
        سيٽ_position = معلومات->pending_position ||
                       (!(دري->flags & SDL_دري_BORDERLESS) && !دري->undefined_x && !دري->undefined_y);
    }

    إذا (!معلومات->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_داخلا_Focus(display, معلومات->xwindow, Revert_منزل_None, Current_وقت);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE)) {
        X11_سيٽ_Keyboard_Focus(دري, true);
    }

    // Get some valid border values, if we haven't received them yet
    إذا (معلومات->border_کاٻو == 0 && معلومات->border_ساڄو == 0 && معلومات->border_چوٽي == 0 && معلومات->border_bottom == 0) {
        X11_Get_Border_قدرون(معلومات);
    }

    إذا (سيٽ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ثابت صحيح tx = (معلومات->pending_position ? دري->pending.x : دري->x) - (معلومات->was_shown ? 0 : معلومات->border_کاٻو);
        ثابت صحيح ty = (معلومات->pending_position ? دري->pending.y : دري->y) - (معلومات->was_shown ? 0 : معلومات->border_چوٽي);
        صحيح x, y;

        SDL_Relative_منزل_Global_For_دري(دري, tx, ty, &x, &y);

        معلومات->pending_position = false;
        X11_XMove_دري(display, معلومات->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    إذا (!(دري->flags & SDL_دري_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_دري(display, معلومات->xwindow, دري->w, دري->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    معلومات->سائيز_move_event_flags = X11_سائيز_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    معلومات->سائيز_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_SHOWN, 0, 0);
    معلومات->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    إذا (معلومات->آخري_xconfigure.type) {
        صحيح x, y;
        SDL_Global_منزل_Relative_For_دري(معلومات->دري, معلومات->آخري_xconfigure.x, معلومات->آخري_xconfigure.y, &x, &y);
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, معلومات->آخري_xconfigure.ويڪر, معلومات->آخري_xconfigure.اوچائي);
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, x, y);
    }
}

فراغ X11_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    Display *display = معلومات->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ثابت bool is_mapped = X11_Is_دري_Mapped(_this, دري);
    X11_XWithdraw_دري(display, معلومات->xwindow, screen);
    إذا (is_mapped && !(دري->flags & SDL_دري_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&معلومات->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE)) {
        SDL_دري *new_focus;
        ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(دري, &new_focus);
        X11_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ساكن bool X11_سيٽ_دري_سرگرم(SDL_VideoDevice *_this, SDL_دري *دري)
{
    CHECK_دري_معلومات(دري);

    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;
    Atom NET_سرگرم_دري = معلومات->videodata->atoms.NET_سرگرم_دري;

    إذا (X11_Is_دري_Mapped(_this, دري)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_پيغام;
        e.xclient.پيغام_type = NET_سرگرم_دري;
        e.xclient.format = 32;
        e.xclient.دري = معلومات->xwindow;
        e.xclient.معلومات.l[0] = 1; // source indication. 1 = application
        e.xclient.معلومات.l[1] = معلومات->user_وقت;
        e.xclient.معلومات.l[2] = 0;

        X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        X11_XFlush(display);
    }
    أرجع true;
}

فراغ X11_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_دري_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_دري(display, معلومات->xwindow);
    إذا (bActivate) {
        X11_سيٽ_دري_سرگرم(_this, دري);
    }
    X11_XFlush(display);
}

ساكن bool X11_سيٽ_دري_Maximized(SDL_VideoDevice *_this, SDL_دري *دري, bool maximized)
{
    CHECK_دري_معلومات(دري);

    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        أرجع true;
    }

    إذا (X11_Is_دري_Mapped(_this, دري)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پيغام;
        e.xclient.پيغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.دري = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            maximized ? NET_WM_STATE_جوڙيو : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.معلومات.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.معلومات.l[3] = 0l;

        إذا (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_دري(دري);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            معلومات->expected.x = bounds.x + معلومات->border_کاٻو;
            معلومات->expected.y = bounds.y + معلومات->border_چوٽي;
            معلومات->expected.w = bounds.w - (معلومات->border_کاٻو + معلومات->border_ساڄو);
            معلومات->expected.h = bounds.h - (معلومات->border_چوٽي + معلومات->border_bottom);
        } وإلا {
            معلومات->expected.x = دري->floating.x;
            معلومات->expected.y = دري->floating.y;
            معلومات->expected.w = دري->floating.w;
            معلومات->expected.h = دري->floating.h;
        }

        X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سيٽ_Net_WMState(_this, معلومات->xwindow, دري->flags);
    }
    X11_XFlush(display);

    أرجع true;
}

فراغ X11_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (دري->اندروني->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_دري(دري);
    }

    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        دري->اندروني->دري_was_maximized = true;
        أرجع;
    }

    إذا (!(دري->flags & SDL_دري_MINIMIZED)) {
        دري->اندروني->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_سيٽ_دري_Maximized(_this, دري, true);
    }
}

فراغ X11_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;

    إذا (معلومات->pending_operation & SDL_دري_FULLSCREEN) {
        SDL_Sync_دري(دري);
    }

    معلومات->pending_operation |= X11_PENDING_OP_MINIMIZE;
    إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
        معلومات->دري_was_maximized = !!(دري->flags & SDL_دري_MAXIMIZED);
    }
    X11_XIconify_دري(display, معلومات->xwindow, displaydata->screen);
    X11_XFlush(display);
}

فراغ X11_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Don't restore the window the first time it is being shown.
    إذا (!دري->اندروني->was_shown) {
        أرجع;
    }

    إذا (دري->اندروني->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_دري(دري);
    }

    إذا ((دري->flags & SDL_دري_FULLSCREEN) && !(دري->flags & SDL_دري_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        دري->اندروني->دري_was_maximized = false;
        أرجع;
    }

    إذا (دري->flags & (SDL_دري_MINIMIZED | SDL_دري_MAXIMIZED) ||
        (دري->اندروني->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        دري->اندروني->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ثابت bool maximize = !!(دري->flags & SDL_دري_MINIMIZED) && دري->اندروني->دري_was_maximized;
    X11_سيٽ_دري_Maximized(_this, دري, maximize);
    X11_Show_دري(_this, دري);
    X11_سيٽ_دري_سرگرم(_this, دري);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ساكن SDL_Fullscreen_نتيجو X11_سيٽ_دري_Fullscreen_ذريعي_WM(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = _display->اندروني;
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = معلومات->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    إذا (!معلومات->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (X11_Is_دري_Mapped(_this, دري)) {
        XEvent e;

        // Flush any pending fullscreen events.
        إذا (معلومات->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_دري(_this, دري);
        }

        إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
            إذا (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                أرجع SDL_FULLSCREEN_FAILED;
            } وإلا إذا (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                أرجع SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        إذا (fullscreen && !(دري->flags & SDL_دري_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_سائيز_Hints();
            ڊگهو flags = 0;
            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_سائيز | PMax_سائيز | PAspect);
            X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_پيغام;
        e.xclient.پيغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.دري = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            fullscreen ? NET_WM_STATE_جوڙيو : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        إذا (((دري->flags & SDL_دري_FULLSCREEN) != 0) != (fullscreen != 0)) {
            معلومات->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        إذا (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_دري_Position(دري);
            SDL_copyp(&معلومات->requested_fullscreen_گهڻائي, &دري->current_fullscreen_گهڻائي);
            إذا (fullscreen != !!(دري->flags & SDL_دري_FULLSCREEN)) {
                معلومات->دري_was_maximized = !!(دري->flags & SDL_دري_MAXIMIZED);
            }
            معلومات->expected.x = displaydata->x;
            معلومات->expected.y = displaydata->y;
            معلومات->expected.w = _display->current_گهڻائي->w;
            معلومات->expected.h = _display->current_گهڻائي->h;

            // Only move the window if it isn't already on the target display.
            إذا (!current || current != _display->id) {
                X11_XMove_دري(display, معلومات->xwindow, displaydata->x, displaydata->y);
                معلومات->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } وإلا {
            SDL_zero(معلومات->requested_fullscreen_گهڻائي);
            معلومات->pending_position = معلومات->fs_repositioned;
            معلومات->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_پيغام;
            e.xclient.پيغام_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.دري = معلومات->xwindow;
            إذا (معلومات->دري_was_maximized) {
                e.xclient.معلومات.l[0] = NET_WM_STATE_جوڙيو;
            } وإلا {
                e.xclient.معلومات.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.معلومات.l[1] = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.معلومات.l[2] = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.معلومات.l[3] = 0l;
            X11_XSendEvent(display, پاڙ_دري(display, displaydata->screen), 0,
                           Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
        }
    } وإلا {
        SDL_دري_Flags flags;

        flags = دري->flags;
        إذا (fullscreen) {
            flags |= SDL_دري_FULLSCREEN;
        } وإلا {
            flags &= ~SDL_دري_FULLSCREEN;
        }
        X11_سيٽ_Net_WMState(_this, معلومات->xwindow, flags);
    }

    إذا (معلومات->visual->class == سڌو_Color) {
        إذا (fullscreen) {
            X11_XInstallColormap(display, معلومات->colormap);
        } وإلا {
            X11_XUninstallColormap(display, معلومات->colormap);
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

ساكن SDL_Fullscreen_نتيجو X11_سيٽ_دري_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = _display->اندروني;
    Display *display = معلومات->videodata->display;
    ثابت صحيح screen = displaydata->screen;

    إذا (!معلومات->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    إذا (معلومات->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_دري(_this, دري);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_دري_Event(دري, fullscreen ? SDL_EVENT_دري_ENTER_FULLSCREEN : SDL_EVENT_دري_LEAVE_FULLSCREEN, 0, 0);
    إذا (fullscreen) {
        إذا (!(دري->flags & SDL_دري_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_سائيز_Hints();
            ڊگهو flags = 0;
            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_سائيز | PMax_سائيز | PAspect);
            X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        سيٽ_دري_Bordered(display, screen, معلومات->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        معلومات->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        معلومات->expected.x = rect.x;
        معلومات->expected.y = rect.y;
        معلومات->expected.w = rect.w;
        معلومات->expected.h = rect.h;
        X11_XMove_دري(display, معلومات->xwindow, rect.x, rect.y);
        X11_XResize_دري(display, معلومات->xwindow, rect.w, rect.h);
        X11_XRaise_دري(display, معلومات->xwindow);
    } وإلا {
        معلومات->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        معلومات->expected.x = دري->windowed.x;
        معلومات->expected.y = دري->windowed.y;
        معلومات->expected.w = دري->windowed.w;
        معلومات->expected.h = دري->windowed.h;
        X11_XResize_دري(display, معلومات->xwindow, دري->windowed.w, دري->windowed.h);
        X11_XMove_دري(display, معلومات->xwindow, دري->windowed.x, دري->windowed.y);

        سيٽ_دري_Bordered(display, screen, معلومات->xwindow, (دري->flags & SDL_دري_BORDERLESS) == 0);
        X11_سيٽ_دري_Min_Max(معلومات->دري, false);
    }

    X11_XFlush(display);

    أرجع SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_نتيجو X11_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_دري_معلومات(دري);
    CHECK_DISPLAY_معلومات(_display);

    SDL_Video_معلومات *معلومات = _this->اندروني;
    إذا (معلومات->net_wm) {
        أرجع X11_سيٽ_دري_Fullscreen_ذريعي_WM(_this, دري, _display, fullscreen);
    }

    أرجع X11_سيٽ_دري_Fullscreen_Legacy(_this, دري, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

تعريفنوع بنية
{
    بنانشان حرف *معلومات;
    صحيح format, ڳڻپ;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, دري_2 w, Atom prop)
{
    بنانشان حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بنانشان ڊگهو ڳڻپ;
    بنانشان ڊگهو بائيٽون_کاٻو;
    صحيح بائيٽون_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_دري_Property(disp, w, prop, 0, بائيٽون_fetch, False, AnyPropertyType, &type, &fmt, &ڳڻپ, &بائيٽون_کاٻو, &ret);
        بائيٽون_fetch += بائيٽون_کاٻو;
    } طالما (بائيٽون_کاٻو != 0);

    p->معلومات = ret;
    p->format = fmt;
    p->ڳڻپ = ڳڻپ;
    p->type = type;
}

فراغ *X11_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    XWindow_خاصيتون خاصيتون;
    Atom icc_profile_atom;
    حرف icc_atom_string[حجم("_ICC_PROFILE_") + 12];
    فراغ *ret_icc_profile_معلومات = عدم;
    CARD8 *icc_profile_معلومات;
    صحيح real_format;
    بنانشان ڊگهو real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_دري_خاصيتون(display, معلومات->xwindow, &خاصيتون);
    إذا (X11_XScreen_عدد_جو_Screen(خاصيتون.screen) > 0) {
        (فراغ)SDL_snprintf(icc_atom_string, حجم("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_عدد_جو_Screen(خاصيتون.screen));
    } وإلا {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", حجم("_ICC_PROFILE"));
    }
    X11_XGet_دري_خاصيتون(display, پاڙ_دري_جو_Screen(خاصيتون.screen), &خاصيتون);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    إذا (icc_profile_atom == None) {
        SDL_سيٽ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    X11_ReadProperty(&atomProp, display, پاڙ_دري_جو_Screen(خاصيتون.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.ڳڻپ;
    icc_profile_معلومات = atomProp.معلومات;
    إذا (real_format == None) {
        SDL_سيٽ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    ret_icc_profile_معلومات = SDL_malloc(real_nitems);
    إذا (!ret_icc_profile_معلومات) {
        أرجع عدم;
    }

    SDL_memcpy(ret_icc_profile_معلومات, icc_profile_معلومات, real_nitems);
    *سائيز = real_nitems;
    X11_XFree(icc_profile_معلومات);

    أرجع ret_icc_profile_معلومات;
}

bool X11_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display;

    إذا (!معلومات) {
        أرجع SDL_سيٽ_Error("Invalid window data");
    }
    معلومات->mouse_grabbed = false;
    معلومات->pending_grab = false;

    display = معلومات->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (دري->flags & SDL_دري_HIDDEN) {
            أرجع true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        إذا (معلومات->xinput2_mouse_enabled && SDL_GetMouseState(عدم, عدم)) {
            معلومات->pending_grab = true;
            أرجع true;
        }

        // Try to grab the mouse
        إذا (!معلومات->videodata->broken_اشارو_grab) {
            ثابت بنانشان صحيح نقاب = Button_Press_نقاب | Button_Release_نقاب | اشارو_Motion_نقاب | Focus_Change_نقاب;
            صحيح attempts;
            صحيح نتيجو = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            لكل (attempts = 0; attempts < 100; attempts++) {
                نتيجو = X11_XGrab_اشارو(display, معلومات->xwindow, False, نقاب, Grab_گهڻائي_Async,
                                          Grab_گهڻائي_Async, معلومات->xwindow, None, Current_وقت);
                إذا (نتيجو == GrabSuccess) {
                    معلومات->mouse_grabbed = true;
                    اكسر;
                }
                SDL_Delay(50);
            }

            إذا (نتيجو != GrabSuccess) {
                معلومات->videodata->broken_اشارو_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, دري);

        // Raise the window if we grab the mouse
        X11_XRaise_دري(display, معلومات->xwindow);
    } وإلا {
        X11_XUngrab_اشارو(display, Current_وقت);

        X11_Xinput2UngrabTouch(_this, دري);
    }
    X11_XSync(display, False);

    إذا (!معلومات->videodata->broken_اشارو_grab) {
        أرجع true;
    } وإلا {
        أرجع SDL_سيٽ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display;

    إذا (!معلومات) {
        أرجع SDL_سيٽ_Error("Invalid window data");
    }

    display = معلومات->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (دري->flags & SDL_دري_HIDDEN) {
            أرجع true;
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
        إذا (_this->اندروني->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            إذا (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_پيغام_Event client_پيغام;
                client_پيغام.type = Client_پيغام;
                client_پيغام.دري = معلومات->xwindow;
                client_پيغام.format = 32;
                client_پيغام.پيغام_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_پيغام.معلومات.l[0] = 1;
                client_پيغام.معلومات.l[1] = Current_وقت;

                X11_XSendEvent(display, Default_پاڙ_دري(display), False, Substructure_Notify_نقاب | Substructure_Redirect_نقاب, (XEvent *)&client_پيغام);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, معلومات->xwindow, True, Grab_گهڻائي_Async,
                          Grab_گهڻائي_Async, Current_وقت);
    } وإلا {
        X11_XUngrabKeyboard(display, Current_وقت);
    }
    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات) {
        SDL_Video_معلومات *videodata = معلومات->videodata;
        Display *display = videodata->display;
        صحيح numwindows = videodata->numwindows;
        SDL_دري_معلومات **windowlist = videodata->windowlist;
        صحيح i;

        إذا (windowlist) {
            لكل (i = 0; i < numwindows; ++i) {
                إذا (windowlist[i] && (windowlist[i]->دري == دري)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = عدم;
                    videodata->numwindows--;
                    اكسر;
                }
            }
        }

        X11_Destroy_داخلا_Context(معلومات);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
        X11_رڪن_Resize_Sync(دري);
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

        إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
            X11_XDestroy_دري(display, معلومات->xwindow);
            X11_XFlush(display);
        }
        SDL_free(معلومات);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        إذا (videodata->سرگرم_cursor_confined_دري == دري) {
            X11_Destroy_اشارو_Barrier(_this, دري);
        }
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    دري->اندروني = عدم;
}

bool X11_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

فراغ X11_AcceptDragAndDrop(SDL_دري *دري, bool accept)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    Atom XdndAware = معلومات->videodata->atoms.XdndAware;

    إذا (accept) {
        Atom xdnd_نسخو = 5;
        X11_XChangeProperty(display, معلومات->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_گهڻائي_Replace, (بنانشان حرف *)&xdnd_نسخو, 1);
    } وإلا {
        X11_XDeleteProperty(display, معلومات->xwindow, XdndAware);
    }
}

bool X11_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, معلومات->xwindow);
    إذا (!wmhints) {
        أرجع SDL_سيٽ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    معلومات->flashing_دري = false;
    معلومات->flash_cancel_وقت = 0;

    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        // Taken care of above
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        إذا (!(دري->flags & SDL_دري_داخلا_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            معلومات->flashing_دري = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            معلومات->flash_cancel_وقت = SDL_GetTicks() + 1000;
        }
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        إذا (!(دري->flags & SDL_دري_داخلا_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            معلومات->flashing_دري = true;
        }
        اكسر;
    افتراضي:
        اكسر;
    }

    X11_XSetWMHints(display, معلومات->xwindow, wmhints);
    X11_XFree(wmhints);
    أرجع true;
}

bool SDL_X11_سيٽ_دري_Title(Display *display, دري_2 xwindow, حرف *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    صحيح conv = X11_Xmb_متن_List_منزل_متن_Property(display, &title, 1, XTextStyle, &titleprop);
    حالت_2 حالت;

    إذا (X11_XSupportsLocale() != True) {
        أرجع SDL_سيٽ_Error("Current locale not supported by X server, cannot continue.");
    }

    إذا (conv == 0) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.قدر);
        // we know this can't be a locale error as we checked X locale validity
    } وإلا إذا (conv < 0) {
        أرجع SDL_ٻاهريون_جو_يادگيري();
    } وإلا { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        أرجع true;
    }

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    حالت = X11_Xutf8_متن_List_منزل_متن_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    إذا (حالت == Success) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.قدر);
    } وإلا {
        أرجع SDL_سيٽ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#جيڪڏهن_پورو

    X11_XFlush(display);
    أرجع true;
}

فراغ X11_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    Display *display = معلومات->videodata->display;
    دري_2 پاڙ = پاڙ_دري(display, displaydata->screen);
    XClient_پيغام_Event e;
    دري_2 ٻار_Return_2;
    صحيح wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, معلومات->xwindow, پاڙ, x, y, &wx, &wy, &ٻار_Return_2);

    e.type = Client_پيغام;
    e.دري = معلومات->xwindow;
    e.پيغام_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.معلومات.l[0] = 0;  // GTK device ID (unused)
    e.معلومات.l[1] = wx; // X coordinate relative to root
    e.معلومات.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, پاڙ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    إذا ((دري->flags & SDL_دري_EXTERNAL) &&
        (معلومات->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(دري);
            أرجع true;
    }

    ثابت Uint64 current_وقت = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
        إذا (_this->displays[i]->اندروني->گهڻائي_switch_deadline_ns &&
            current_وقت < _this->displays[i]->اندروني->گهڻائي_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->اندروني->گهڻائي_switch_deadline_ns - current_وقت, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += دري->اندروني->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_منزل_NS(1000) : SDL_MS_منزل_NS(100);

    أرجع X11_Sync_دري_Timeout(_this, دري, timeout);
}

bool X11_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable)
{
    إذا (!SDL_دري_IS_POPUP(دري)) {
        SDL_دري_معلومات *معلومات = دري->اندروني;
        Display *display = معلومات->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, معلومات->xwindow);
        إذا (!wmhints) {
            أرجع SDL_سيٽ_Error("Couldn't get WM hints");
        }

        wmhints->داخلا_2 = focusable ? True : False;
        wmhints->flags |= داخلا_Hint;

        X11_XSetWMHints(display, معلومات->xwindow, wmhints);
        X11_XFree(wmhints);
    } وإلا إذا (دري->flags & SDL_دري_POPUP_MENU) {
        إذا (!(دري->flags & SDL_دري_HIDDEN)) {
            إذا (!focusable && (دري->flags & SDL_دري_داخلا_FOCUS)) {
                SDL_دري *new_focus;
                ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(دري, &new_focus);
                X11_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(دري)) {
                    X11_سيٽ_Keyboard_Focus(دري, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
