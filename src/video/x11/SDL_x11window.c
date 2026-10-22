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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

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

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#د_که_پای

#ضمن "SDL_x11xsync.h"

#تعریف_کړه _NET_WM_STATE_REMOVE 0l
#تعریف_کړه NET_WM_STATE_جمع_کړه    1l

#تعریف_کړه CHECK_کړکۍ_معلومات(کړکۍ)                                       \
    إذا (!کړکۍ) {                                                      \
        أرجع SDL_سېټ_Error("Invalid window");                          \
    }                                                                   \
    إذا (!کړکۍ->دننی) {                                          \
        أرجع SDL_سېټ_Error("Invalid window driver data");              \
    }

#تعریف_کړه CHECK_DISPLAY_معلومات(display)                                     \
    إذا (!_display) {                                                    \
        أرجع SDL_سېټ_Error("Invalid display");                         \
    }                                                                   \
    إذا (!_display->دننی) {                                        \
        أرجع SDL_سېټ_Error("Invalid display driver data");             \
    }

ساكن Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == MapNotify && ev->xmap.کړکۍ == *((کړکۍ_2 *)win);
}
ساكن Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == UnmapNotify && ev->xunmap.کړکۍ == *((کړکۍ_2 *)win);
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

ساكن bool X11_Is_کړکۍ_Mapped(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Video_معلومات *videodata = _this->دننی;
    XWindow_ځانګړتیاوې attr;

    X11_XGet_کړکۍ_ځانګړتیاوې(videodata->display, معلومات->xwindow, &attr);
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
ساكن bool X11_IsActionAllowed(SDL_کړکۍ *کړکۍ, Atom action)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Atom _NET_WM_ALLOWED_ACTIONS = معلومات->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = معلومات->videodata->display;
    صحيح form;
    بینښه اوږد remain;
    بینښه اوږد len, i;
    Atom *list;
    bool ret = false;

    إذا (X11_XGet_کړکۍ_Property(display, معلومات->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (بینښه حرف **)&list) == Success) {
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
#د_که_پای // 0

ساكن فراغ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool وروستی_position_pending = کړکۍ->وروستی_position_pending;
    ثابت bool وروستی_اندازه_pending = کړکۍ->وروستی_اندازه_pending;

    X11_Sync_کړکۍ(_this, کړکۍ);

    کړکۍ->وروستی_position_pending = وروستی_position_pending;
    کړکۍ->وروستی_اندازه_pending = وروستی_اندازه_pending;
}

فراغ X11_سېټ_Net_WMState(SDL_VideoDevice *_this, کړکۍ_2 xwindow, SDL_کړکۍ_Flags flags)
{
    SDL_Video_معلومات *videodata = _this->دننی;
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
    صحيح شمېر = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    إذا (flags & SDL_کړکۍ_ALWAYS_ON_سر) {
        atoms[شمېر++] = _NET_WM_STATE_ABOVE;
    }
    إذا (flags & SDL_کړکۍ_UTILITY) {
        atoms[شمېر++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[شمېر++] = _NET_WM_STATE_SKIP_PAGER;
    }
    إذا (flags & SDL_کړکۍ_ننوت_FOCUS) {
        atoms[شمېر++] = _NET_WM_STATE_FOCUSED;
    }
    إذا (flags & SDL_کړکۍ_MAXIMIZED) {
        atoms[شمېر++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[شمېر++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    إذا (flags & SDL_کړکۍ_FULLSCREEN) {
        atoms[شمېر++] = _NET_WM_STATE_FULLSCREEN;
    }
    إذا (flags & SDL_کړکۍ_MODAL) {
        atoms[شمېر++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(شمېر <= SDL_arraysize(atoms));

    إذا (شمېر > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace, (بینښه حرف *)atoms, شمېر);
    } وإلا {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ساكن فراغ X11_ConstrainPopup(SDL_کړکۍ *کړکۍ, bool output_منزل_pending)
{
    // Clamp popup windows to the output borders
    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        SDL_کړکۍ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = کړکۍ->وروستی_position_pending ? کړکۍ->pending.x : کړکۍ->floating.x;
        صحيح abs_y = کړکۍ->وروستی_position_pending ? کړکۍ->pending.y : کړکۍ->floating.y;
        صحيح دننه_واټن_x = 0, دننه_واټن_y = 0;

        إذا (کړکۍ->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = کړکۍ->پلار; SDL_کړکۍ_IS_POPUP(w); w = w->پلار) {
                دننه_واټن_x += w->x;
                دننه_واټن_y += w->y;
            }

            دننه_واټن_x += w->x;
            دننه_واټن_y += w->y;
            abs_x += دننه_واټن_x;
            abs_y += دننه_واټن_y;

            displayID = SDL_Get_Display_For_کړکۍ(w);

            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + کړکۍ->w > rect.x + rect.w) {
                abs_x -= (abs_x + کړکۍ->w) - (rect.x + rect.w);
            }
            إذا (abs_y + کړکۍ->h > rect.y + rect.h) {
                abs_y -= (abs_y + کړکۍ->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            کړکۍ->pending.x = abs_x - دننه_واټن_x;
            کړکۍ->pending.y = abs_y - دننه_واټن_y;
        } وإلا {
            کړکۍ->floating.x = کړکۍ->windowed.x = abs_x - دننه_واټن_x;
            کړکۍ->floating.y = کړکۍ->windowed.y = abs_y - دننه_واټن_y;
        }
    }
}

ساكن فراغ X11_سېټ_Keyboard_Focus(SDL_کړکۍ *کړکۍ, bool سېټ_فعال_focus)
{
    SDL_کړکۍ *toplevel = کړکۍ;

    // Find the toplevel parent
    طالما (SDL_کړکۍ_IS_POPUP(toplevel)) {
        toplevel = toplevel->پلار;
    }

    toplevel->keyboard_focus = کړکۍ;

    إذا (سېټ_فعال_focus && !کړکۍ->is_hiding && !کړکۍ->is_destroying) {
        SDL_سېټ_Keyboard_Focus(کړکۍ);
    }
}

SDL_کړکۍ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, کړکۍ_2 xwindow)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    صحيح actualFormat;
    بینښه اوږد i, عدد_توکي, بایټونه_After;
    بینښه حرف *property_ارزښت = عدم;
    اوږد max_اوږدتیا = 1024;
    SDL_کړکۍ_Flags flags = 0;

    إذا (X11_XGet_کړکۍ_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_اوږدتیا, False, XA_ATOM, &actualType,
                               &actualFormat, &عدد_توکي, &بایټونه_After,
                               &property_ارزښت) == Success) {
        Atom *atoms = (Atom *)property_ارزښت;
        صحيح maximized = 0;
        صحيح fullscreen = 0;

        لكل (i = 0; i < عدد_توکي; ++i) {
            إذا (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_OCCLUDED;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_کړکۍ_ننوت_FOCUS;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        إذا (fullscreen == 1) {
            flags |= SDL_کړکۍ_FULLSCREEN;
        } وإلا إذا (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN);
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
                flags |= (کړکۍ->flags & SDL_کړکۍ_MAXIMIZED);
            } وإلا {
                flags |= SDL_کړکۍ_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_ځانګړتیاوې attr;
            SDL_zero(attr);
            X11_XGet_کړکۍ_ځانګړتیاوې(videodata->display, xwindow, &attr);
            إذا (attr.map_state == IsUnmapped) {
                flags |= SDL_کړکۍ_HIDDEN;
            }
        }
        X11_XFree(property_ارزښت);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    أرجع flags;
}

ساكن bool تیاری_کړکۍ_معلومات(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, کړکۍ_2 w)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    SDL_کړکۍ_معلومات *معلومات;

    // Allocate the window data
    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }
    معلومات->videodata = videodata;
    معلومات->کړکۍ = کړکۍ;
    معلومات->xwindow = w;
    معلومات->موندنه_test_پایله = SDL_HITTEST_نورمال;

    X11_Create_ننوت_Context(معلومات);

    // Associate the data with the window

    إذا (videodata->numwindows >= videodata->windowlistlength) {
        SDL_کړکۍ_معلومات ** new_windowlist = (SDL_کړکۍ_معلومات **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * حجم(*videodata->windowlist));
        إذا (!new_windowlist) {
            اذهب error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_ځانګړتیاوې attrib;

        X11_XGet_کړکۍ_ځانګړتیاوې(معلومات->videodata->display, w, &attrib);
        إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ)) {
            کړکۍ->x = کړکۍ->windowed.x = کړکۍ->floating.x = attrib.x;
            کړکۍ->y = کړکۍ->windowed.y = کړکۍ->floating.y = attrib.y - معلومات->border_سر;
        }
        کړکۍ->w = کړکۍ->windowed.w = کړکۍ->floating.w = attrib.پلنوالی;
        کړکۍ->h = کړکۍ->windowed.h = کړکۍ->floating.h = attrib.لوړوالی;
        إذا (attrib.map_state != IsUnmapped) {
            کړکۍ->flags &= ~SDL_کړکۍ_HIDDEN;
        } وإلا {
            کړکۍ->flags |= SDL_کړکۍ_HIDDEN;
        }
        معلومات->visual = attrib.visual;
        معلومات->colormap = attrib.colormap;
    }

    کړکۍ->flags |= X11_GetNetWMState(_this, کړکۍ, w);

    {
        کړکۍ_2 Focal_کړکۍ;
        صحيح Revert_منزل = 0;
        X11_XGet_ننوت_Focus(معلومات->videodata->display, &Focal_کړکۍ, &Revert_منزل);
        إذا (Focal_کړکۍ == w) {
            کړکۍ->flags |= SDL_کړکۍ_ننوت_FOCUS;
        }

        إذا (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
            SDL_سېټ_Keyboard_Focus(معلومات->کړکۍ);
        }

        إذا (کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
        // Query the title from the existing window
        کړکۍ->title = X11_Get_کړکۍ_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_X11_DISPLAY_اشاره_ګر, معلومات->videodata->display);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_X11_SCREEN_شمېره, screen);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_X11_کړکۍ_شمېره, معلومات->xwindow);


#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    إذا ((کړکۍ->flags & SDL_کړکۍ_OPENGL) &&
        ((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_معلومات || X11_GL_UseEGL(_this))
#د_که_پای
    ) {
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        إذا (!_this->egl_معلومات) {
            اذهب error_cleanup;
        }

        // Create the GLES window surface
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)w);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            SDL_سېټ_Error("Could not create GLES window surface");
            اذهب error_cleanup;
        }
#وإلا
        SDL_سېټ_Error("Could not create GLES window surface (EGL support not configured)");
        اذهب error_cleanup;
#د_که_پای // SDL_VIDEO_OPENGL_EGL
    }
#د_که_پای

    // All done!
    کړکۍ->دننی = معلومات;
    videodata->windowlist[videodata->numwindows++] = معلومات;
    أرجع true;

error_cleanup:
    X11_Destroy_ننوت_Context(معلومات);
    SDL_free(معلومات);
    أرجع false;
}

ساكن فراغ تیاری_کړکۍ_ننوت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    اوږد fevent = 0;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    کړکۍ_2 xwindow = معلومات->xwindow;

#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8 && معلومات->ic) {
        X11_XGetICValues(معلومات->ic, XNFilterEvents, &fevent, عدم);
    }
#د_که_پای

    X11_Xinput2Select(_this, کړکۍ);

    {
        بینښه صحيح x11_keyboard_events = کلی_Press_ماسک | کلی_Release_ماسک;
        بینښه صحيح x11_اشاره_ګر_events = Button_Press_ماسک | Button_Release_ماسک | اشاره_ګر_Motion_ماسک;

        X11_Xinput2SelectMouseAndKeyboard(_this, کړکۍ);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        إذا (معلومات->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        إذا (معلومات->xinput2_mouse_enabled) {
            x11_اشاره_ګر_events = 0;
        }

        X11_XSelect_ننوت(معلومات->videodata->display, xwindow,
                         (Focus_Change_ماسک | Enter_کړکۍ_ماسک | Leave_کړکۍ_ماسک | Exposure_ماسک |
                          x11_keyboard_events | x11_اشاره_ګر_events |
                          Property_Change_ماسک | Structure_Notify_ماسک |
                          Keymap_State_ماسک | fevent));
    }
}

ساكن فراغ سېټ_کړکۍ_Bordered(Display *display, صحيح screen, کړکۍ_2 کړکۍ, bool border)
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
            بینښه اوږد flags;
            بینښه اوږد functions;
            بینښه اوږد decorations;
            اوږد ننوت_ډېرپېښ;
            بینښه اوږد حالت;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, کړکۍ, WM_HINTS, WM_HINTS, 32,
                            Prop_ډېرپېښ_Replace, (بینښه حرف *)&MWMHints,
                            حجم(MWMHints) / حجم(اوږد));
    } وإلا { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, کړکۍ, ریښه_کړکۍ(display, screen));
    }
}

bool X11_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    کړکۍ_2 w = (کړکۍ_2)SDL_Get_شمېره_Property(create_props, SDL_PROP_کړکۍ_CREATE_X11_کړکۍ_شمېره,
                (کړکۍ_2)SDL_Get_اشاره_ګر_Property(create_props, "sdl2-compat.external_window", عدم));
    إذا (w) {
        کړکۍ->flags |= SDL_کړکۍ_EXTERNAL;

        إذا (!تیاری_کړکۍ_معلومات(_this, کړکۍ, w)) {
            أرجع false;
        }

        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_کړکۍ_ننوت, true)) {
            تیاری_کړکۍ_ننوت(_this, کړکۍ);
        }
        أرجع true;
    }

    SDL_Video_معلومات *معلومات = _this->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    إذا (!displaydata) {
        أرجع SDL_سېټ_Error("Could not find display info");
    }

    ثابت bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ثابت bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (کړکۍ->flags & SDL_کړکۍ_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_کړکۍ_معلومات *windowdata;
    Display *display = معلومات->display;
    صحيح screen = displaydata->screen;
    Visual *visual;
    صحيح ژوروالی_2;
    XSet_کړکۍ_ځانګړتیاوې xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_کړکۍ_TYPE;
    Atom wintype;
    ثابت حرف *wintype_name = عدم;
    اوږد compositor = 1;
    Atom _NET_WM_PID;
    ثابت حرف *hint = عدم;
    صحيح win_x, win_y;
    bool undefined_position = false;

#إذا defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ثابت صحيح transparent = (کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) ? true : false;
    ثابت حرف *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_کړکۍ_VISUALID);
    ثابت حرف *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    إذا (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, کينډۍ;
        صحيح nvis;

        SDL_zero(کينډۍ);
        کينډۍ.visualid = SDL_strtol(forced_visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &کينډۍ, &nvis);
        إذا (vi) {
            visual = vi->visual;
            ژوروالی_2 = vi->ژوروالی_2;
            X11_XFree(vi);
        } وإلا {
            أرجع false;
        }
    } وإلا إذا ((کړکۍ->flags & SDL_کړکۍ_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = عدم;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        إذا (((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_معلومات || X11_GL_UseEGL(_this))
#د_که_پای
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } وإلا
#د_که_پای
        {
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#د_که_پای
        }

        إذا (!vinfo) {
            أرجع false;
        }
        visual = vinfo->visual;
        ژوروالی_2 = vinfo->ژوروالی_2;
        X11_XFree(vinfo);
    } وإلا
#د_که_پای
    {
        visual = displaydata->visual;
        ژوروالی_2 = displaydata->ژوروالی_2;
    }

    xattr.override_redirect = ((کړکۍ->flags & SDL_کړکۍ_TOOLTIP) || (کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    إذا (visual->class == مستقیم_Color) {
        XColor *colorcells;
        صحيح i;
        صحيح ncolors;
        صحيح rmax, gmax, bmax;
        صحيح rmask, gmask, bmask;
        صحيح rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, ریښه_کړکۍ(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        إذا (!xattr.colormap) {
            أرجع SDL_سېټ_Error("Could not create writable colormap");
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
        rmask = visual->red_ماسک;
        طالما (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_ماسک;
        طالما (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_ماسک;
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
            X11_XCreateColormap(display, ریښه_کړکۍ(display, screen),
                                visual, AllocNone);
    }

    إذا (کړکۍ->undefined_x && کړکۍ->undefined_y &&
        کړکۍ->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        X11_ConstrainPopup(کړکۍ, false);
    }
    SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ,
                                  کړکۍ->floating.x, کړکۍ->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_کړکۍ(display, ریښه_کړکۍ(display, screen),
                          win_x, win_y, کړکۍ->floating.w, کړکۍ->floating.h,
                          0, ژوروالی_2, ننوت_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    إذا (!w) {
        أرجع SDL_سېټ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    إذا (!(کړکۍ->pending_flags & SDL_کړکۍ_FULLSCREEN)) {
        سېټ_کړکۍ_Bordered(display, screen, w, !(کړکۍ->flags & SDL_کړکۍ_BORDERLESS));
    }

    sizehints = X11_XAlloc_اندازه_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
        sizehints->min_پلنوالی_2 = sizehints->max_پلنوالی_2 = کړکۍ->floating.w;
        sizehints->min_لوړوالی_2 = sizehints->max_لوړوالی_2 = کړکۍ->floating.h;
        sizehints->flags |= (PMax_اندازه | PMin_اندازه);
    }
    إذا (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->ننوت = !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE) ? True : False;
    wmhints->کړکۍ_ډله = معلومات->کړکۍ_ډله;
    wmhints->flags = ننوت_Hint | کړکۍ_ډله_Hint;

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
        اوږد pid = (اوږد)معلومات->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_ډېرپېښ_Replace,
                            (بینښه حرف *)&pid, 1);
    }

    // Set the window manager state
    X11_سېټ_Net_WMState(_this, w, کړکۍ->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_کړکۍ_TYPE);
    إذا (کړکۍ->flags & SDL_کړکۍ_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } وإلا إذا (hint && *hint) {
        wintype_name = hint;
    } وإلا {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_کړکۍ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_کړکۍ_TYPE, XA_ATOM, 32,
                        Prop_ډېرپېښ_Replace, (بینښه حرف *)&wintype, 1);
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_ډېرپېښ_Replace,
                            (بینښه حرف *)&compositor, 1);
    }

    {
        Atom protocols[4];
        صحيح proto_شمېر = 0;

        protocols[proto_شمېر++] = معلومات->atoms.WM_DELETE_کړکۍ; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_شمېر++] = معلومات->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
        إذا (use_resize_sync) {
            protocols[proto_شمېر++] = معلومات->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_شمېر <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_شمېر);
    }

    إذا (!تیاری_کړکۍ_معلومات(_this, کړکۍ, w)) {
        X11_XDestroy_کړکۍ(display, w);
        أرجع false;
    }
    windowdata = کړکۍ->دننی;

    // Set the parent if this is a non-popup window.
    إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ) && کړکۍ->پلار) {
        X11_XSetTransientForHint(display, w, کړکۍ->پلار->دننی->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(کړکۍ->pending_flags & SDL_کړکۍ_FULLSCREEN) &&
                                               !!(کړکۍ->flags & SDL_کړکۍ_BORDERLESS);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
    إذا (use_resize_sync) {
        X11_InitResizeSync(کړکۍ);
    }
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    إذا (کړکۍ->flags & SDL_کړکۍ_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_ننوت, 0, 0, region, Shape_سېټ);
        X11_XDestroyRegion(region);
    }
#د_که_پای

    تیاری_کړکۍ_ننوت(_this, کړکۍ);

    // For _ICC_PROFILE.
    X11_XSelect_ننوت(display, ریښه_کړکۍ(display, screen), Property_Change_ماسک);

    X11_XFlush(display);

    أرجع true;
}

حرف *X11_Get_کړکۍ_Title(SDL_VideoDevice *_this, کړکۍ_2 xwindow)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    Display *display = معلومات->display;
    صحيح حالت, real_format;
    Atom real_type;
    بینښه اوږد توکي_read, توکي_کیڼ;
    بینښه حرف *propdata;
    حرف *title = عدم;

    حالت = X11_XGet_کړکۍ_Property(display, xwindow, معلومات->atoms._NET_WM_NAME,
                                    0L, 8192L, False, معلومات->atoms.UTF8_STRING, &real_type, &real_format,
                                    &توکي_read, &توکي_کیڼ, &propdata);
    إذا (حالت == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(حرف *, propdata));
        X11_XFree(propdata);
    } وإلا {
        حالت = X11_XGet_کړکۍ_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &توکي_read, &توکي_کیڼ, &propdata);
        إذا (حالت == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(حرف *, propdata), توکي_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } وإلا {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    أرجع title;
}

فراغ X11_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    کړکۍ_2 xwindow = معلومات->xwindow;
    Display *display = معلومات->videodata->display;
    حرف *title = کړکۍ->title ? کړکۍ->title : "";

    SDL_X11_سېټ_کړکۍ_Title(display, xwindow, title);
}

ساكن bool caught_x11_error = false;
ساكن صحيح X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    أرجع 0;
}

ساكن فراغ X11_ExternalResizeMoveSync(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    بینښه صحيح ماشوم_شمېر;
    کړکۍ_2 ماشوم_Return_2, ریښه, پلار;
    کړکۍ_2 *children;
    XWindow_ځانګړتیاوې attrs;
    Uint64 timeout = 0;
    صحيح x, y;
    ثابت bool send_move = !!(معلومات->pending_operation & X11_PENDING_OP_MOVE);
    ثابت bool send_resize = !!(معلومات->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_ونه(display, معلومات->xwindow, &ریښه, &پلار, &children, &ماشوم_شمېر);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_منزل_NS(100);
    طالما (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_کړکۍ_ځانګړتیاوې(display, معلومات->xwindow, &attrs);
        X11_XTranslateCoordinates(display, پلار, Default_ریښه_کړکۍ(display),
                                  attrs.x, attrs.y, &x, &y, &ماشوم_Return_2);
        SDL_Global_منزل_Relative_For_کړکۍ(کړکۍ, x, y, &x, &y);

        إذا (!caught_x11_error) {
            إذا ((معلومات->pending_operation & X11_PENDING_OP_MOVE) && (x == معلومات->expected.x + معلومات->border_کیڼ && y == معلومات->expected.y + معلومات->border_سر)) {
                معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            إذا ((معلومات->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.پلنوالی == معلومات->expected.w && attrs.لوړوالی == معلومات->expected.h)) {
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
            معلومات->expected.w = attrs.پلنوالی;
            معلومات->expected.h = attrs.لوړوالی;
            اكسر;
        }

        SDL_Delay(10);
    }

    إذا (!caught_x11_error) {
        إذا (send_move) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, x, y);
        }
        إذا (send_resize) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, attrs.پلنوالی, attrs.لوړوالی);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ساكن bool X11_Sync_کړکۍ_Timeout(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, Uint64 param_timeout)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool پایله = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    إذا (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    طالما (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        إذا ((معلومات->pending_operation & X11_PENDING_OP_MOVE) && (کړکۍ->x == معلومات->expected.x + معلومات->border_کیڼ && کړکۍ->y == معلومات->expected.y + معلومات->border_سر)) {
            معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        إذا ((معلومات->pending_operation & X11_PENDING_OP_RESIZE) && (کړکۍ->w == معلومات->expected.w && کړکۍ->h == معلومات->expected.h)) {
            معلومات->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        إذا (معلومات->pending_operation == X11_PENDING_OP_NONE) {
            إذا (force_exit ||
                (کړکۍ->x == معلومات->expected.x + معلومات->border_کیڼ && کړکۍ->y == معلومات->expected.y + معلومات->border_سر &&
                 کړکۍ->w == معلومات->expected.w && کړکۍ->h == معلومات->expected.h)) {
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
            معلومات->expected.x = کړکۍ->x;
            معلومات->expected.y = کړکۍ->y;
            معلومات->expected.w = کړکۍ->w;
            معلومات->expected.h = کړکۍ->h;

            پایله = false;
            اكسر;
        }

        SDL_Delay(10);
    }

    معلومات->pending_operation = X11_PENDING_OP_NONE;

    إذا (!caught_x11_error) {
        X11_PumpEvents(_this);
    } وإلا {
        پایله = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    أرجع پایله;
}

bool X11_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_ICON = معلومات->videodata->atoms._NET_WM_ICON;
    صحيح (*prevHandler)(Display *, XErrorEvent *) = عدم;
    bool پایله = true;

    إذا (icon) {
        صحيح x, y;
        صحيح propsize;
        اوږد *propdata;
        Uint32 *src;
        اوږد *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * حجم(اوږد));

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
                            32, Prop_ډېرپېښ_Replace, (بینښه حرف *)propdata,
                            propsize);
        SDL_free(propdata);

        إذا (caught_x11_error) {
            پایله = SDL_سېټ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    إذا (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    أرجع پایله;
}

فراغ X11_Update_کړکۍ_Position(SDL_کړکۍ *کړکۍ, bool use_current_position)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    ثابت صحيح rel_x = use_current_position ? کړکۍ->x : کړکۍ->pending.x;
    ثابت صحيح rel_y = use_current_position ? کړکۍ->y : کړکۍ->pending.y;

    SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ,
                                  rel_x - معلومات->border_کیڼ, rel_y - معلومات->border_سر,
                                  &معلومات->expected.x, &معلومات->expected.y);

    // Attempt to move the window
    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        کړکۍ->دننی->pending_position = true;
    } وإلا {
        معلومات->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_کړکۍ(display, معلومات->xwindow, معلومات->expected.x, معلومات->expected.y);
    }
}

bool X11_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Sync any pending fullscreen or maximize events.
    إذا (کړکۍ->دننی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, کړکۍ);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    إذا (کړکۍ->flags & SDL_کړکۍ_MAXIMIZED) {
        إذا (کړکۍ->دننی->pending_operation & X11_PENDING_OP_RESTORE) {
            کړکۍ->دننی->pending_position = true;
        }
        أرجع true;
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
            X11_ConstrainPopup(کړکۍ, true);
        }
        X11_Update_کړکۍ_Position(کړکۍ, false);
    } وإلا {
        کړکۍ->دننی->fs_repositioned = true;
        SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    أرجع true;
}

فراغ X11_سېټ_کړکۍ_Min_Max(SDL_کړکۍ *کړکۍ, bool use_current)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
    اوږد hint_flags = 0;

    X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);

    إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_RESIZABLE) {
        إذا (معلومات->کړکۍ->min_w || معلومات->کړکۍ->min_h) {
            sizehints->flags |= PMin_اندازه;
            sizehints->min_پلنوالی_2 = معلومات->کړکۍ->min_w;
            sizehints->min_لوړوالی_2 = معلومات->کړکۍ->min_h;
        }
        إذا (معلومات->کړکۍ->max_w || معلومات->کړکۍ->max_h) {
            sizehints->flags |= PMax_اندازه;
            sizehints->max_پلنوالی_2 = معلومات->کړکۍ->max_w;
            sizehints->max_لوړوالی_2 = معلومات->کړکۍ->max_h;
        }
        إذا (معلومات->کړکۍ->min_aspect > 0.0f || معلومات->کړکۍ->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(معلومات->کړکۍ->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(معلومات->کړکۍ->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } وإلا {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_اندازه | PMax_اندازه;
        إذا (use_current) {
            sizehints->min_پلنوالی_2 = sizehints->max_پلنوالی_2 = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : معلومات->کړکۍ->floating.w;
            sizehints->min_لوړوالی_2 = sizehints->max_لوړوالی_2 = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : معلومات->کړکۍ->floating.h;
        } وإلا {
            sizehints->min_پلنوالی_2 = sizehints->max_پلنوالی_2 = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : معلومات->کړکۍ->windowed.w;
            sizehints->min_لوړوالی_2 = sizehints->max_لوړوالی_2 = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : معلومات->کړکۍ->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
    X11_XFree(sizehints);
}

فراغ X11_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->دننی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        X11_سېټ_کړکۍ_Min_Max(کړکۍ, true);
    }
}

فراغ X11_سېټ_کړکۍ_اعظمي_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->دننی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        X11_سېټ_کړکۍ_Min_Max(کړکۍ, true);
    }
}

فراغ X11_سېټ_کړکۍ_Aspect_نسبت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->دننی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        X11_سېټ_کړکۍ_Min_Max(کړکۍ, true);
    }
}

فراغ X11_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    إذا (معلومات->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, کړکۍ);
    }

    // Set the size as pending if the window is being restored.
    إذا (کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_FULLSCREEN)) {
        // New size will be set when the window is restored.
        إذا (معلومات->pending_operation & X11_PENDING_OP_RESTORE) {
            معلومات->pending_اندازه = true;
        } وإلا {
            // Can't resize the window.
            کړکۍ->وروستی_اندازه_pending = false;
        }
        أرجع;
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            اوږد userhints;
            صحيح dest_x, dest_y;

            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &userhints);

            معلومات->expected.w = sizehints->min_پلنوالی_2 = sizehints->max_پلنوالی_2 = کړکۍ->pending.w;
            معلومات->expected.h = sizehints->min_لوړوالی_2 = sizehints->max_لوړوالی_2 = کړکۍ->pending.h;
            sizehints->flags |= PMin_اندازه | PMax_اندازه;
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
            X11_XResize_کړکۍ(display, معلومات->xwindow, کړکۍ->pending.w, کړکۍ->pending.h);
            ثابت صحيح x = کړکۍ->وروستی_position_pending ? کړکۍ->pending.x : کړکۍ->x;
            ثابت صحيح y = کړکۍ->وروستی_position_pending ? کړکۍ->pending.y : کړکۍ->y;
            SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ,
                                          x - معلومات->border_کیڼ,
                                          y - معلومات->border_سر,
                                          &dest_x, &dest_y);
            X11_XMove_کړکۍ(display, معلومات->xwindow, dest_x, dest_y);
            X11_XRaise_کړکۍ(display, معلومات->xwindow);

            X11_XFree(sizehints);
        }
    } وإلا {
        معلومات->expected.w = کړکۍ->pending.w;
        معلومات->expected.h = کړکۍ->pending.h;
        معلومات->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_کړکۍ(display, معلومات->xwindow, معلومات->expected.w, معلومات->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->pending.w, کړکۍ->pending.h);
    }
}

bool X11_Get_کړکۍ_Borders_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    *کیڼ = معلومات->border_کیڼ;
    *ښی = معلومات->border_ښی;
    *سر = معلومات->border_سر;
    *bottom = معلومات->border_bottom;

    أرجع true;
}

bool X11_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    Atom NET_WM_کړکۍ_OPACITY = معلومات->videodata->atoms.NET_WM_کړکۍ_OPACITY;

    إذا (opacity == 1.0f) {
        X11_XDeleteProperty(display, معلومات->xwindow, NET_WM_کړکۍ_OPACITY);
    } وإلا {
        ثابت Uint32 FullyOpaque = 0xFFFFFFFF;
        ثابت اوږد alpha = (اوږد)((مزدوج)opacity * (مزدوج)FullyOpaque);
        X11_XChangeProperty(display, معلومات->xwindow, NET_WM_کړکۍ_OPACITY, XA_CARDINAL, 32,
                            Prop_ډېرپېښ_Replace, (بینښه حرف *)&alpha, 1);
    }

    أرجع true;
}

bool X11_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_کړکۍ_معلومات *پلار_معلومات = پلار ? پلار->دننی : عدم;
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    Display *display = video_معلومات->display;

    إذا (پلار_معلومات) {
        X11_XSetTransientForHint(display, معلومات->xwindow, پلار_معلومات->xwindow);
    } وإلا {
        X11_XDeleteProperty(display, معلومات->xwindow, video_معلومات->atoms.WM_TRANSIENT_FOR);
    }

    أرجع true;
}

bool X11_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = video_معلومات->display;
    Uint32 flags = کړکۍ->flags;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = معلومات->videodata->atoms._NET_WM_STATE_MODAL;

    إذا (modal) {
        flags |= SDL_کړکۍ_MODAL;
    } وإلا {
        flags &= ~SDL_کړکۍ_MODAL;
        X11_XDeleteProperty(display, معلومات->xwindow, video_معلومات->atoms.WM_TRANSIENT_FOR);
    }

    إذا (X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کړکۍ = معلومات->xwindow;
        e.xclient.معلومات.l[0] = modal ? NET_WM_STATE_جمع_کړه : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_سېټ_Net_WMState(_this, معلومات->xwindow, flags);
    }

    X11_XFlush(display);

    أرجع true;
}

فراغ X11_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered)
{
    ثابت bool focused = (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) != 0;
    ثابت bool visible = !(کړکۍ->flags & SDL_کړکۍ_HIDDEN) && !کړکۍ->is_hiding;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;
    XEvent event;

    إذا (معلومات->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        سېټ_کړکۍ_Bordered(display, displaydata->screen, معلومات->xwindow, bordered);
        X11_XFlush(display);

        إذا (visible) {
            XWindow_ځانګړتیاوې attr;
            افعل {
                X11_XSync(display, False);
                X11_XGet_کړکۍ_ځانګړتیاوې(display, معلومات->xwindow, &attr);
            } طالما (attr.map_state != IsViewable);

            إذا (focused) {
                X11_XSet_ننوت_Focus(display, معلومات->xwindow, Revert_منزل_پلار, Current_وخت);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&معلومات->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&معلومات->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_ارزښتونه(معلومات);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_کړکۍ(display, معلومات->xwindow, کړکۍ->floating.w, کړکۍ->floating.h);
        X11_XSync(display, False);
    } وإلا {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        معلومات->toggle_borders = true;
        معلومات->fullscreen_borders_forced_on = false;
    }
}

فراغ X11_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        X11_سېټ_کړکۍ_Min_Max(کړکۍ, true);
    }
}

فراغ X11_سېټ_کړکۍ_Always_On_سر(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = معلومات->videodata->atoms._NET_WM_STATE_ABOVE;

    إذا (X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کړکۍ = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            on_سر ? NET_WM_STATE_جمع_کړه : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_سېټ_Net_WMState(_this, معلومات->xwindow, کړکۍ->flags);
    }
    X11_XFlush(display);
}

فراغ X11_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کړکۍ_ACTIVATE_WHEN_SHOWN, true);
    bool سېټ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    إذا (معلومات->was_shown) {
        X11_PumpEvents(_this);
    }

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(کړکۍ, true);
        معلومات->pending_position = true;
        سېټ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (فراغ)bActivate;

    إذا (!X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        X11_XMapRaised(display, معلومات->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&معلومات->xwindow);
        }
        X11_XFlush(display);
        سېټ_position = معلومات->pending_position ||
                       (!(کړکۍ->flags & SDL_کړکۍ_BORDERLESS) && !کړکۍ->undefined_x && !کړکۍ->undefined_y);
    }

    إذا (!معلومات->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_ننوت_Focus(display, معلومات->xwindow, Revert_منزل_None, Current_وخت);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
        X11_سېټ_Keyboard_Focus(کړکۍ, true);
    }

    // Get some valid border values, if we haven't received them yet
    إذا (معلومات->border_کیڼ == 0 && معلومات->border_ښی == 0 && معلومات->border_سر == 0 && معلومات->border_bottom == 0) {
        X11_Get_Border_ارزښتونه(معلومات);
    }

    إذا (سېټ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ثابت صحيح tx = (معلومات->pending_position ? کړکۍ->pending.x : کړکۍ->x) - (معلومات->was_shown ? 0 : معلومات->border_کیڼ);
        ثابت صحيح ty = (معلومات->pending_position ? کړکۍ->pending.y : کړکۍ->y) - (معلومات->was_shown ? 0 : معلومات->border_سر);
        صحيح x, y;

        SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, tx, ty, &x, &y);

        معلومات->pending_position = false;
        X11_XMove_کړکۍ(display, معلومات->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_کړکۍ(display, معلومات->xwindow, کړکۍ->w, کړکۍ->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    معلومات->اندازه_move_event_flags = X11_اندازه_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    معلومات->اندازه_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
    معلومات->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    إذا (معلومات->وروستی_xconfigure.type) {
        صحيح x, y;
        SDL_Global_منزل_Relative_For_کړکۍ(معلومات->کړکۍ, معلومات->وروستی_xconfigure.x, معلومات->وروستی_xconfigure.y, &x, &y);
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, معلومات->وروستی_xconfigure.پلنوالی, معلومات->وروستی_xconfigure.لوړوالی);
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, x, y);
    }
}

فراغ X11_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    Display *display = معلومات->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ثابت bool is_mapped = X11_Is_کړکۍ_Mapped(_this, کړکۍ);
    X11_XWithdraw_کړکۍ(display, معلومات->xwindow, screen);
    إذا (is_mapped && !(کړکۍ->flags & SDL_کړکۍ_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&معلومات->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
        SDL_کړکۍ *new_focus;
        ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(کړکۍ, &new_focus);
        X11_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ساكن bool X11_سېټ_کړکۍ_فعال(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_معلومات(کړکۍ);

    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;
    Atom NET_فعال_کړکۍ = معلومات->videodata->atoms.NET_فعال_کړکۍ;

    إذا (X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = NET_فعال_کړکۍ;
        e.xclient.format = 32;
        e.xclient.کړکۍ = معلومات->xwindow;
        e.xclient.معلومات.l[0] = 1; // source indication. 1 = application
        e.xclient.معلومات.l[1] = معلومات->user_وخت;
        e.xclient.معلومات.l[2] = 0;

        X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);

        X11_XFlush(display);
    }
    أرجع true;
}

فراغ X11_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کړکۍ_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_کړکۍ(display, معلومات->xwindow);
    إذا (bActivate) {
        X11_سېټ_کړکۍ_فعال(_this, کړکۍ);
    }
    X11_XFlush(display);
}

ساكن bool X11_سېټ_کړکۍ_Maximized(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool maximized)
{
    CHECK_کړکۍ_معلومات(کړکۍ);

    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        أرجع true;
    }

    إذا (X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کړکۍ = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            maximized ? NET_WM_STATE_جمع_کړه : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.معلومات.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.معلومات.l[3] = 0l;

        إذا (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کړکۍ(کړکۍ);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            معلومات->expected.x = bounds.x + معلومات->border_کیڼ;
            معلومات->expected.y = bounds.y + معلومات->border_سر;
            معلومات->expected.w = bounds.w - (معلومات->border_کیڼ + معلومات->border_ښی);
            معلومات->expected.h = bounds.h - (معلومات->border_سر + معلومات->border_bottom);
        } وإلا {
            معلومات->expected.x = کړکۍ->floating.x;
            معلومات->expected.y = کړکۍ->floating.y;
            معلومات->expected.w = کړکۍ->floating.w;
            معلومات->expected.h = کړکۍ->floating.h;
        }

        X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_سېټ_Net_WMState(_this, معلومات->xwindow, کړکۍ->flags);
    }
    X11_XFlush(display);

    أرجع true;
}

فراغ X11_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->دننی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کړکۍ(کړکۍ);
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        کړکۍ->دننی->کړکۍ_was_maximized = true;
        أرجع;
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        کړکۍ->دننی->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_سېټ_کړکۍ_Maximized(_this, کړکۍ, true);
    }
}

فراغ X11_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;

    إذا (معلومات->pending_operation & SDL_کړکۍ_FULLSCREEN) {
        SDL_Sync_کړکۍ(کړکۍ);
    }

    معلومات->pending_operation |= X11_PENDING_OP_MINIMIZE;
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        معلومات->کړکۍ_was_maximized = !!(کړکۍ->flags & SDL_کړکۍ_MAXIMIZED);
    }
    X11_XIconify_کړکۍ(display, معلومات->xwindow, displaydata->screen);
    X11_XFlush(display);
}

فراغ X11_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Don't restore the window the first time it is being shown.
    إذا (!کړکۍ->دننی->was_shown) {
        أرجع;
    }

    إذا (کړکۍ->دننی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کړکۍ(کړکۍ);
    }

    إذا ((کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && !(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        کړکۍ->دننی->کړکۍ_was_maximized = false;
        أرجع;
    }

    إذا (کړکۍ->flags & (SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_MAXIMIZED) ||
        (کړکۍ->دننی->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        کړکۍ->دننی->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ثابت bool maximize = !!(کړکۍ->flags & SDL_کړکۍ_MINIMIZED) && کړکۍ->دننی->کړکۍ_was_maximized;
    X11_سېټ_کړکۍ_Maximized(_this, کړکۍ, maximize);
    X11_Show_کړکۍ(_this, کړکۍ);
    X11_سېټ_کړکۍ_فعال(_this, کړکۍ);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ساكن SDL_Fullscreen_پایله X11_سېټ_کړکۍ_Fullscreen_له_لارې_WM(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = _display->دننی;
    Display *display = معلومات->videodata->display;
    Atom _NET_WM_STATE = معلومات->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = معلومات->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    إذا (!معلومات->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (X11_Is_کړکۍ_Mapped(_this, کړکۍ)) {
        XEvent e;

        // Flush any pending fullscreen events.
        إذا (معلومات->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_کړکۍ(_this, کړکۍ);
        }

        إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
            إذا (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                أرجع SDL_FULLSCREEN_FAILED;
            } وإلا إذا (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                أرجع SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        إذا (fullscreen && !(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            اوږد flags = 0;
            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);
            X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کړکۍ = معلومات->xwindow;
        e.xclient.معلومات.l[0] =
            fullscreen ? NET_WM_STATE_جمع_کړه : _NET_WM_STATE_REMOVE;
        e.xclient.معلومات.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.معلومات.l[3] = 0l;

        X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        إذا (((کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) != 0) != (fullscreen != 0)) {
            معلومات->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        إذا (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_کړکۍ_Position(کړکۍ);
            SDL_copyp(&معلومات->requested_fullscreen_ډېرپېښ, &کړکۍ->current_fullscreen_ډېرپېښ);
            إذا (fullscreen != !!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
                معلومات->کړکۍ_was_maximized = !!(کړکۍ->flags & SDL_کړکۍ_MAXIMIZED);
            }
            معلومات->expected.x = displaydata->x;
            معلومات->expected.y = displaydata->y;
            معلومات->expected.w = _display->current_ډېرپېښ->w;
            معلومات->expected.h = _display->current_ډېرپېښ->h;

            // Only move the window if it isn't already on the target display.
            إذا (!current || current != _display->id) {
                X11_XMove_کړکۍ(display, معلومات->xwindow, displaydata->x, displaydata->y);
                معلومات->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } وإلا {
            SDL_zero(معلومات->requested_fullscreen_ډېرپېښ);
            معلومات->pending_position = معلومات->fs_repositioned;
            معلومات->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_پیغام;
            e.xclient.پیغام_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.کړکۍ = معلومات->xwindow;
            إذا (معلومات->کړکۍ_was_maximized) {
                e.xclient.معلومات.l[0] = NET_WM_STATE_جمع_کړه;
            } وإلا {
                e.xclient.معلومات.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.معلومات.l[1] = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.معلومات.l[2] = معلومات->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.معلومات.l[3] = 0l;
            X11_XSendEvent(display, ریښه_کړکۍ(display, displaydata->screen), 0,
                           Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
        }
    } وإلا {
        SDL_کړکۍ_Flags flags;

        flags = کړکۍ->flags;
        إذا (fullscreen) {
            flags |= SDL_کړکۍ_FULLSCREEN;
        } وإلا {
            flags &= ~SDL_کړکۍ_FULLSCREEN;
        }
        X11_سېټ_Net_WMState(_this, معلومات->xwindow, flags);
    }

    إذا (معلومات->visual->class == مستقیم_Color) {
        إذا (fullscreen) {
            X11_XInstallColormap(display, معلومات->colormap);
        } وإلا {
            X11_XUninstallColormap(display, معلومات->colormap);
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

ساكن SDL_Fullscreen_پایله X11_سېټ_کړکۍ_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = _display->دننی;
    Display *display = معلومات->videodata->display;
    ثابت صحيح screen = displaydata->screen;

    إذا (!معلومات->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    إذا (معلومات->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_کړکۍ(_this, کړکۍ);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_کړکۍ_Event(کړکۍ, fullscreen ? SDL_EVENT_کړکۍ_ENTER_FULLSCREEN : SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
    إذا (fullscreen) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            اوږد flags = 0;
            X11_XGetWMNormalHints(display, معلومات->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);
            X11_XSetWMNormalHints(display, معلومات->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        سېټ_کړکۍ_Bordered(display, screen, معلومات->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        معلومات->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        معلومات->expected.x = rect.x;
        معلومات->expected.y = rect.y;
        معلومات->expected.w = rect.w;
        معلومات->expected.h = rect.h;
        X11_XMove_کړکۍ(display, معلومات->xwindow, rect.x, rect.y);
        X11_XResize_کړکۍ(display, معلومات->xwindow, rect.w, rect.h);
        X11_XRaise_کړکۍ(display, معلومات->xwindow);
    } وإلا {
        معلومات->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        معلومات->expected.x = کړکۍ->windowed.x;
        معلومات->expected.y = کړکۍ->windowed.y;
        معلومات->expected.w = کړکۍ->windowed.w;
        معلومات->expected.h = کړکۍ->windowed.h;
        X11_XResize_کړکۍ(display, معلومات->xwindow, کړکۍ->windowed.w, کړکۍ->windowed.h);
        X11_XMove_کړکۍ(display, معلومات->xwindow, کړکۍ->windowed.x, کړکۍ->windowed.y);

        سېټ_کړکۍ_Bordered(display, screen, معلومات->xwindow, (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) == 0);
        X11_سېټ_کړکۍ_Min_Max(معلومات->کړکۍ, false);
    }

    X11_XFlush(display);

    أرجع SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_پایله X11_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_کړکۍ_معلومات(کړکۍ);
    CHECK_DISPLAY_معلومات(_display);

    SDL_Video_معلومات *معلومات = _this->دننی;
    إذا (معلومات->net_wm) {
        أرجع X11_سېټ_کړکۍ_Fullscreen_له_لارې_WM(_this, کړکۍ, _display, fullscreen);
    }

    أرجع X11_سېټ_کړکۍ_Fullscreen_Legacy(_this, کړکۍ, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

تعريفنوع بنية
{
    بینښه حرف *معلومات;
    صحيح format, شمېر;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, کړکۍ_2 w, Atom prop)
{
    بینښه حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بینښه اوږد شمېر;
    بینښه اوږد بایټونه_کیڼ;
    صحيح بایټونه_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کړکۍ_Property(disp, w, prop, 0, بایټونه_fetch, False, AnyPropertyType, &type, &fmt, &شمېر, &بایټونه_کیڼ, &ret);
        بایټونه_fetch += بایټونه_کیڼ;
    } طالما (بایټونه_کیڼ != 0);

    p->معلومات = ret;
    p->format = fmt;
    p->شمېر = شمېر;
    p->type = type;
}

فراغ *X11_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    XWindow_ځانګړتیاوې ځانګړتیاوې;
    Atom icc_profile_atom;
    حرف icc_atom_string[حجم("_ICC_PROFILE_") + 12];
    فراغ *ret_icc_profile_معلومات = عدم;
    CARD8 *icc_profile_معلومات;
    صحيح real_format;
    بینښه اوږد real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_کړکۍ_ځانګړتیاوې(display, معلومات->xwindow, &ځانګړتیاوې);
    إذا (X11_XScreen_شمېره_د_Screen(ځانګړتیاوې.screen) > 0) {
        (فراغ)SDL_snprintf(icc_atom_string, حجم("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_شمېره_د_Screen(ځانګړتیاوې.screen));
    } وإلا {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", حجم("_ICC_PROFILE"));
    }
    X11_XGet_کړکۍ_ځانګړتیاوې(display, ریښه_کړکۍ_د_Screen(ځانګړتیاوې.screen), &ځانګړتیاوې);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    إذا (icc_profile_atom == None) {
        SDL_سېټ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    X11_ReadProperty(&atomProp, display, ریښه_کړکۍ_د_Screen(ځانګړتیاوې.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.شمېر;
    icc_profile_معلومات = atomProp.معلومات;
    إذا (real_format == None) {
        SDL_سېټ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    ret_icc_profile_معلومات = SDL_malloc(real_nitems);
    إذا (!ret_icc_profile_معلومات) {
        أرجع عدم;
    }

    SDL_memcpy(ret_icc_profile_معلومات, icc_profile_معلومات, real_nitems);
    *اندازه = real_nitems;
    X11_XFree(icc_profile_معلومات);

    أرجع ret_icc_profile_معلومات;
}

bool X11_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display;

    إذا (!معلومات) {
        أرجع SDL_سېټ_Error("Invalid window data");
    }
    معلومات->mouse_grabbed = false;
    معلومات->pending_grab = false;

    display = معلومات->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
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
        إذا (!معلومات->videodata->broken_اشاره_ګر_grab) {
            ثابت بینښه صحيح ماسک = Button_Press_ماسک | Button_Release_ماسک | اشاره_ګر_Motion_ماسک | Focus_Change_ماسک;
            صحيح attempts;
            صحيح پایله = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            لكل (attempts = 0; attempts < 100; attempts++) {
                پایله = X11_XGrab_اشاره_ګر(display, معلومات->xwindow, False, ماسک, Grab_ډېرپېښ_Async,
                                          Grab_ډېرپېښ_Async, معلومات->xwindow, None, Current_وخت);
                إذا (پایله == GrabSuccess) {
                    معلومات->mouse_grabbed = true;
                    اكسر;
                }
                SDL_Delay(50);
            }

            إذا (پایله != GrabSuccess) {
                معلومات->videodata->broken_اشاره_ګر_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, کړکۍ);

        // Raise the window if we grab the mouse
        X11_XRaise_کړکۍ(display, معلومات->xwindow);
    } وإلا {
        X11_XUngrab_اشاره_ګر(display, Current_وخت);

        X11_Xinput2UngrabTouch(_this, کړکۍ);
    }
    X11_XSync(display, False);

    إذا (!معلومات->videodata->broken_اشاره_ګر_grab) {
        أرجع true;
    } وإلا {
        أرجع SDL_سېټ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display;

    إذا (!معلومات) {
        أرجع SDL_سېټ_Error("Invalid window data");
    }

    display = معلومات->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
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
        إذا (_this->دننی->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            إذا (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_پیغام_Event client_پیغام;
                client_پیغام.type = Client_پیغام;
                client_پیغام.کړکۍ = معلومات->xwindow;
                client_پیغام.format = 32;
                client_پیغام.پیغام_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_پیغام.معلومات.l[0] = 1;
                client_پیغام.معلومات.l[1] = Current_وخت;

                X11_XSendEvent(display, Default_ریښه_کړکۍ(display), False, Substructure_Notify_ماسک | Substructure_Redirect_ماسک, (XEvent *)&client_پیغام);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, معلومات->xwindow, True, Grab_ډېرپېښ_Async,
                          Grab_ډېرپېښ_Async, Current_وخت);
    } وإلا {
        X11_XUngrabKeyboard(display, Current_وخت);
    }
    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات) {
        SDL_Video_معلومات *videodata = معلومات->videodata;
        Display *display = videodata->display;
        صحيح numwindows = videodata->numwindows;
        SDL_کړکۍ_معلومات **windowlist = videodata->windowlist;
        صحيح i;

        إذا (windowlist) {
            لكل (i = 0; i < numwindows; ++i) {
                إذا (windowlist[i] && (windowlist[i]->کړکۍ == کړکۍ)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = عدم;
                    videodata->numwindows--;
                    اكسر;
                }
            }
        }

        X11_Destroy_ننوت_Context(معلومات);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
        X11_غړی_Resize_Sync(کړکۍ);
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

        إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
            X11_XDestroy_کړکۍ(display, معلومات->xwindow);
            X11_XFlush(display);
        }
        SDL_free(معلومات);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        إذا (videodata->فعال_cursor_confined_کړکۍ == کړکۍ) {
            X11_Destroy_اشاره_ګر_Barrier(_this, کړکۍ);
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    کړکۍ->دننی = عدم;
}

bool X11_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

فراغ X11_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    Atom XdndAware = معلومات->videodata->atoms.XdndAware;

    إذا (accept) {
        Atom xdnd_نسخه = 5;
        X11_XChangeProperty(display, معلومات->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace, (بینښه حرف *)&xdnd_نسخه, 1);
    } وإلا {
        X11_XDeleteProperty(display, معلومات->xwindow, XdndAware);
    }
}

bool X11_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, معلومات->xwindow);
    إذا (!wmhints) {
        أرجع SDL_سېټ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    معلومات->flashing_کړکۍ = false;
    معلومات->flash_cancel_وخت = 0;

    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        // Taken care of above
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        إذا (!(کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            معلومات->flashing_کړکۍ = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            معلومات->flash_cancel_وخت = SDL_GetTicks() + 1000;
        }
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        إذا (!(کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            معلومات->flashing_کړکۍ = true;
        }
        اكسر;
    افتراضي:
        اكسر;
    }

    X11_XSetWMHints(display, معلومات->xwindow, wmhints);
    X11_XFree(wmhints);
    أرجع true;
}

bool SDL_X11_سېټ_کړکۍ_Title(Display *display, کړکۍ_2 xwindow, حرف *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    صحيح conv = X11_Xmb_متن_List_منزل_متن_Property(display, &title, 1, XTextStyle, &titleprop);
    حالت_2 حالت;

    إذا (X11_XSupportsLocale() != True) {
        أرجع SDL_سېټ_Error("Current locale not supported by X server, cannot continue.");
    }

    إذا (conv == 0) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.ارزښت);
        // we know this can't be a locale error as we checked X locale validity
    } وإلا إذا (conv < 0) {
        أرجع SDL_بهر_د_حافظه();
    } وإلا { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        أرجع true;
    }

#که_تعریف_شوی X_HAVE_UTF8_STRING
    حالت = X11_Xutf8_متن_List_منزل_متن_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    إذا (حالت == Success) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.ارزښت);
    } وإلا {
        أرجع SDL_سېټ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#د_که_پای

    X11_XFlush(display);
    أرجع true;
}

فراغ X11_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    Display *display = معلومات->videodata->display;
    کړکۍ_2 ریښه = ریښه_کړکۍ(display, displaydata->screen);
    XClient_پیغام_Event e;
    کړکۍ_2 ماشوم_Return_2;
    صحيح wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, معلومات->xwindow, ریښه, x, y, &wx, &wy, &ماشوم_Return_2);

    e.type = Client_پیغام;
    e.کړکۍ = معلومات->xwindow;
    e.پیغام_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.معلومات.l[0] = 0;  // GTK device ID (unused)
    e.معلومات.l[1] = wx; // X coordinate relative to root
    e.معلومات.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, ریښه, False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    إذا ((کړکۍ->flags & SDL_کړکۍ_EXTERNAL) &&
        (معلومات->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(کړکۍ);
            أرجع true;
    }

    ثابت Uint64 current_وخت = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns &&
            current_وخت < _this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns - current_وخت, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += کړکۍ->دننی->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_منزل_NS(1000) : SDL_MS_منزل_NS(100);

    أرجع X11_Sync_کړکۍ_Timeout(_this, کړکۍ, timeout);
}

bool X11_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable)
{
    إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
        Display *display = معلومات->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, معلومات->xwindow);
        إذا (!wmhints) {
            أرجع SDL_سېټ_Error("Couldn't get WM hints");
        }

        wmhints->ننوت = focusable ? True : False;
        wmhints->flags |= ننوت_Hint;

        X11_XSetWMHints(display, معلومات->xwindow, wmhints);
        X11_XFree(wmhints);
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
            إذا (!focusable && (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS)) {
                SDL_کړکۍ *new_focus;
                ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(کړکۍ, &new_focus);
                X11_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کړکۍ)) {
                    X11_سېټ_Keyboard_Focus(کړکۍ, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
