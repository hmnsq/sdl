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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

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

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#پایان_اگر

#ضمن "SDL_x11xsync.h"

#تعریف_کن _NET_WM_STATE_REMOVE 0l
#تعریف_کن NET_WM_STATE_جمع_کن    1l

#تعریف_کن CHECK_پنجره_داده(پنجره)                                       \
    إذا (!پنجره) {                                                      \
        أرجع SDL_مجموعه_Error("Invalid window");                          \
    }                                                                   \
    إذا (!پنجره->داخلی) {                                          \
        أرجع SDL_مجموعه_Error("Invalid window driver data");              \
    }

#تعریف_کن CHECK_DISPLAY_داده(display)                                     \
    إذا (!_display) {                                                    \
        أرجع SDL_مجموعه_Error("Invalid display");                         \
    }                                                                   \
    إذا (!_display->داخلی) {                                        \
        أرجع SDL_مجموعه_Error("Invalid display driver data");             \
    }

ساكن Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == MapNotify && ev->xmap.پنجره == *((پنجره_2 *)win);
}
ساكن Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == UnmapNotify && ev->xunmap.پنجره == *((پنجره_2 *)win);
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

ساكن bool X11_Is_پنجره_Mapped(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Video_داده *videodata = _this->داخلی;
    XWindow_صفات attr;

    X11_XGet_پنجره_صفات(videodata->display, داده->xwindow, &attr);
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
ساكن bool X11_IsActionAllowed(SDL_پنجره *پنجره, Atom action)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Atom _NET_WM_ALLOWED_ACTIONS = داده->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = داده->videodata->display;
    صحيح form;
    بیعلامت دراز remain;
    بیعلامت دراز len, i;
    Atom *list;
    bool ret = false;

    إذا (X11_XGet_پنجره_Property(display, داده->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (بیعلامت حرف **)&list) == Success) {
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
#پایان_اگر // 0

ساكن فراغ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخرین_position_pending = پنجره->آخرین_position_pending;
    ثابت bool آخرین_اندازه_pending = پنجره->آخرین_اندازه_pending;

    X11_Sync_پنجره(_this, پنجره);

    پنجره->آخرین_position_pending = آخرین_position_pending;
    پنجره->آخرین_اندازه_pending = آخرین_اندازه_pending;
}

فراغ X11_مجموعه_Net_WMState(SDL_VideoDevice *_this, پنجره_2 xwindow, SDL_پنجره_Flags flags)
{
    SDL_Video_داده *videodata = _this->داخلی;
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
    صحيح شمار = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    إذا (flags & SDL_پنجره_ALWAYS_ON_بالاترین) {
        atoms[شمار++] = _NET_WM_STATE_ABOVE;
    }
    إذا (flags & SDL_پنجره_UTILITY) {
        atoms[شمار++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[شمار++] = _NET_WM_STATE_SKIP_PAGER;
    }
    إذا (flags & SDL_پنجره_درون_داد_FOCUS) {
        atoms[شمار++] = _NET_WM_STATE_FOCUSED;
    }
    إذا (flags & SDL_پنجره_MAXIMIZED) {
        atoms[شمار++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[شمار++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    إذا (flags & SDL_پنجره_FULLSCREEN) {
        atoms[شمار++] = _NET_WM_STATE_FULLSCREEN;
    }
    إذا (flags & SDL_پنجره_MODAL) {
        atoms[شمار++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(شمار <= SDL_arraysize(atoms));

    إذا (شمار > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_نما_Replace, (بیعلامت حرف *)atoms, شمار);
    } وإلا {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ساكن فراغ X11_ConstrainPopup(SDL_پنجره *پنجره, bool output_مقصد_pending)
{
    // Clamp popup windows to the output borders
    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        SDL_پنجره *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = پنجره->آخرین_position_pending ? پنجره->pending.x : پنجره->floating.x;
        صحيح abs_y = پنجره->آخرین_position_pending ? پنجره->pending.y : پنجره->floating.y;
        صحيح جابه_جایی_x = 0, جابه_جایی_y = 0;

        إذا (پنجره->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = پنجره->والد; SDL_پنجره_IS_POPUP(w); w = w->والد) {
                جابه_جایی_x += w->x;
                جابه_جایی_y += w->y;
            }

            جابه_جایی_x += w->x;
            جابه_جایی_y += w->y;
            abs_x += جابه_جایی_x;
            abs_y += جابه_جایی_y;

            displayID = SDL_Get_Display_For_پنجره(w);

            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + پنجره->w > rect.x + rect.w) {
                abs_x -= (abs_x + پنجره->w) - (rect.x + rect.w);
            }
            إذا (abs_y + پنجره->h > rect.y + rect.h) {
                abs_y -= (abs_y + پنجره->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_مقصد_pending) {
            پنجره->pending.x = abs_x - جابه_جایی_x;
            پنجره->pending.y = abs_y - جابه_جایی_y;
        } وإلا {
            پنجره->floating.x = پنجره->windowed.x = abs_x - جابه_جایی_x;
            پنجره->floating.y = پنجره->windowed.y = abs_y - جابه_جایی_y;
        }
    }
}

ساكن فراغ X11_مجموعه_Keyboard_Focus(SDL_پنجره *پنجره, bool مجموعه_فعال_focus)
{
    SDL_پنجره *toplevel = پنجره;

    // Find the toplevel parent
    طالما (SDL_پنجره_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = پنجره;

    إذا (مجموعه_فعال_focus && !پنجره->is_hiding && !پنجره->is_destroying) {
        SDL_مجموعه_Keyboard_Focus(پنجره);
    }
}

SDL_پنجره_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_پنجره *پنجره, پنجره_2 xwindow)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    صحيح actualFormat;
    بیعلامت دراز i, رقم_اقلام, بایتها_After;
    بیعلامت حرف *property_مقدار = عدم;
    دراز max_درازی = 1024;
    SDL_پنجره_Flags flags = 0;

    إذا (X11_XGet_پنجره_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_درازی, False, XA_ATOM, &actualType,
                               &actualFormat, &رقم_اقلام, &بایتها_After,
                               &property_مقدار) == Success) {
        Atom *atoms = (Atom *)property_مقدار;
        صحيح maximized = 0;
        صحيح fullscreen = 0;

        لكل (i = 0; i < رقم_اقلام; ++i) {
            إذا (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_پنجره_MINIMIZED | SDL_پنجره_OCCLUDED;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_پنجره_درون_داد_FOCUS;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        إذا (fullscreen == 1) {
            flags |= SDL_پنجره_FULLSCREEN;
        } وإلا إذا (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (پنجره->flags & SDL_پنجره_FULLSCREEN);
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
                flags |= (پنجره->flags & SDL_پنجره_MAXIMIZED);
            } وإلا {
                flags |= SDL_پنجره_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_صفات attr;
            SDL_zero(attr);
            X11_XGet_پنجره_صفات(videodata->display, xwindow, &attr);
            إذا (attr.map_state == IsUnmapped) {
                flags |= SDL_پنجره_HIDDEN;
            }
        }
        X11_XFree(property_مقدار);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    أرجع flags;
}

ساكن bool راهاندازی_پنجره_داده(SDL_VideoDevice *_this, SDL_پنجره *پنجره, پنجره_2 w)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    SDL_پنجره_داده *داده;

    // Allocate the window data
    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        أرجع false;
    }
    داده->videodata = videodata;
    داده->پنجره = پنجره;
    داده->xwindow = w;
    داده->اصابت_test_نتیجه = SDL_HITTEST_نرمال;

    X11_Create_درون_داد_Context(داده);

    // Associate the data with the window

    إذا (videodata->numwindows >= videodata->windowlistlength) {
        SDL_پنجره_داده ** new_windowlist = (SDL_پنجره_داده **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * حجم(*videodata->windowlist));
        إذا (!new_windowlist) {
            اذهب error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_صفات attrib;

        X11_XGet_پنجره_صفات(داده->videodata->display, w, &attrib);
        إذا (!SDL_پنجره_IS_POPUP(پنجره)) {
            پنجره->x = پنجره->windowed.x = پنجره->floating.x = attrib.x;
            پنجره->y = پنجره->windowed.y = پنجره->floating.y = attrib.y - داده->border_بالاترین;
        }
        پنجره->w = پنجره->windowed.w = پنجره->floating.w = attrib.عرض;
        پنجره->h = پنجره->windowed.h = پنجره->floating.h = attrib.ارتفاع;
        إذا (attrib.map_state != IsUnmapped) {
            پنجره->flags &= ~SDL_پنجره_HIDDEN;
        } وإلا {
            پنجره->flags |= SDL_پنجره_HIDDEN;
        }
        داده->visual = attrib.visual;
        داده->colormap = attrib.colormap;
    }

    پنجره->flags |= X11_GetNetWMState(_this, پنجره, w);

    {
        پنجره_2 Focal_پنجره;
        صحيح Revert_مقصد = 0;
        X11_XGet_درون_داد_Focus(داده->videodata->display, &Focal_پنجره, &Revert_مقصد);
        إذا (Focal_پنجره == w) {
            پنجره->flags |= SDL_پنجره_درون_داد_FOCUS;
        }

        إذا (پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
            SDL_مجموعه_Keyboard_Focus(داده->پنجره);
        }

        إذا (پنجره->flags & SDL_پنجره_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
        // Query the title from the existing window
        پنجره->title = X11_Get_پنجره_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_X11_DISPLAY_اشاره_گر, داده->videodata->display);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_X11_SCREEN_عدد, screen);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_X11_پنجره_عدد, داده->xwindow);


#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    إذا ((پنجره->flags & SDL_پنجره_OPENGL) &&
        ((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_داده || X11_GL_UseEGL(_this))
#پایان_اگر
    ) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (!_this->egl_داده) {
            اذهب error_cleanup;
        }

        // Create the GLES window surface
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)w);

        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            SDL_مجموعه_Error("Could not create GLES window surface");
            اذهب error_cleanup;
        }
#وإلا
        SDL_مجموعه_Error("Could not create GLES window surface (EGL support not configured)");
        اذهب error_cleanup;
#پایان_اگر // SDL_VIDEO_OPENGL_EGL
    }
#پایان_اگر

    // All done!
    پنجره->داخلی = داده;
    videodata->windowlist[videodata->numwindows++] = داده;
    أرجع true;

error_cleanup:
    X11_Destroy_درون_داد_Context(داده);
    SDL_free(داده);
    أرجع false;
}

ساكن فراغ راهاندازی_پنجره_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    دراز fevent = 0;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    پنجره_2 xwindow = داده->xwindow;

#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8 && داده->ic) {
        X11_XGetICValues(داده->ic, XNFilterEvents, &fevent, عدم);
    }
#پایان_اگر

    X11_Xinput2Select(_this, پنجره);

    {
        بیعلامت صحيح x11_keyboard_events = کلید_Press_ماسک | کلید_Release_ماسک;
        بیعلامت صحيح x11_اشاره_گر_events = Button_Press_ماسک | Button_Release_ماسک | اشاره_گر_Motion_ماسک;

        X11_Xinput2SelectMouseAndKeyboard(_this, پنجره);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        إذا (داده->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        إذا (داده->xinput2_mouse_enabled) {
            x11_اشاره_گر_events = 0;
        }

        X11_XSelect_درون_داد(داده->videodata->display, xwindow,
                         (Focus_Change_ماسک | Enter_پنجره_ماسک | Leave_پنجره_ماسک | Exposure_ماسک |
                          x11_keyboard_events | x11_اشاره_گر_events |
                          Property_Change_ماسک | Structure_Notify_ماسک |
                          Keymap_State_ماسک | fevent));
    }
}

ساكن فراغ مجموعه_پنجره_Bordered(Display *display, صحيح screen, پنجره_2 پنجره, bool border)
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
            بیعلامت دراز flags;
            بیعلامت دراز functions;
            بیعلامت دراز decorations;
            دراز درون_داد_نما;
            بیعلامت دراز وضعیت;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, پنجره, WM_HINTS, WM_HINTS, 32,
                            Prop_نما_Replace, (بیعلامت حرف *)&MWMHints,
                            حجم(MWMHints) / حجم(دراز));
    } وإلا { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, پنجره, ریشه_پنجره(display, screen));
    }
}

bool X11_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    پنجره_2 w = (پنجره_2)SDL_Get_عدد_Property(create_props, SDL_PROP_پنجره_CREATE_X11_پنجره_عدد,
                (پنجره_2)SDL_Get_اشاره_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    إذا (w) {
        پنجره->flags |= SDL_پنجره_EXTERNAL;

        إذا (!راهاندازی_پنجره_داده(_this, پنجره, w)) {
            أرجع false;
        }

        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_پنجره_درون_داد, true)) {
            راهاندازی_پنجره_درون_داد(_this, پنجره);
        }
        أرجع true;
    }

    SDL_Video_داده *داده = _this->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    إذا (!displaydata) {
        أرجع SDL_مجموعه_Error("Could not find display info");
    }

    ثابت bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ثابت bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (پنجره->flags & SDL_پنجره_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_پنجره_داده *windowdata;
    Display *display = داده->display;
    صحيح screen = displaydata->screen;
    Visual *visual;
    صحيح عمق_2;
    XSet_پنجره_صفات xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_پنجره_TYPE;
    Atom wintype;
    ثابت حرف *wintype_name = عدم;
    دراز compositor = 1;
    Atom _NET_WM_PID;
    ثابت حرف *hint = عدم;
    صحيح win_x, win_y;
    bool undefined_position = false;

#إذا defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ثابت صحيح transparent = (پنجره->flags & SDL_پنجره_TRANSPARENT) ? true : false;
    ثابت حرف *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_پنجره_VISUALID);
    ثابت حرف *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    إذا (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, قالب;
        صحيح nvis;

        SDL_zero(قالب);
        قالب.visualid = SDL_strtol(forced_visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &قالب, &nvis);
        إذا (vi) {
            visual = vi->visual;
            عمق_2 = vi->عمق_2;
            X11_XFree(vi);
        } وإلا {
            أرجع false;
        }
    } وإلا إذا ((پنجره->flags & SDL_پنجره_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = عدم;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (((_this->gl_config.profile_ماسک == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_داده || X11_GL_UseEGL(_this))
#پایان_اگر
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } وإلا
#پایان_اگر
        {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#پایان_اگر
        }

        إذا (!vinfo) {
            أرجع false;
        }
        visual = vinfo->visual;
        عمق_2 = vinfo->عمق_2;
        X11_XFree(vinfo);
    } وإلا
#پایان_اگر
    {
        visual = displaydata->visual;
        عمق_2 = displaydata->عمق_2;
    }

    xattr.override_redirect = ((پنجره->flags & SDL_پنجره_TOOLTIP) || (پنجره->flags & SDL_پنجره_POPUP_MENU) || force_override_redirect) ? True : False;
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
            X11_XCreateColormap(display, ریشه_پنجره(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        إذا (!xattr.colormap) {
            أرجع SDL_مجموعه_Error("Could not create writable colormap");
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
            X11_XCreateColormap(display, ریشه_پنجره(display, screen),
                                visual, AllocNone);
    }

    إذا (پنجره->undefined_x && پنجره->undefined_y &&
        پنجره->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        X11_ConstrainPopup(پنجره, false);
    }
    SDL_Relative_مقصد_Global_For_پنجره(پنجره,
                                  پنجره->floating.x, پنجره->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_پنجره(display, ریشه_پنجره(display, screen),
                          win_x, win_y, پنجره->floating.w, پنجره->floating.h,
                          0, عمق_2, درون_داد_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    إذا (!w) {
        أرجع SDL_مجموعه_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    إذا (!(پنجره->pending_flags & SDL_پنجره_FULLSCREEN)) {
        مجموعه_پنجره_Bordered(display, screen, w, !(پنجره->flags & SDL_پنجره_BORDERLESS));
    }

    sizehints = X11_XAlloc_اندازه_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE)) {
        sizehints->min_عرض_2 = sizehints->max_عرض_2 = پنجره->floating.w;
        sizehints->min_ارتفاع_2 = sizehints->max_ارتفاع_2 = پنجره->floating.h;
        sizehints->flags |= (PMax_اندازه | PMin_اندازه);
    }
    إذا (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->درون_داد = !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE) ? True : False;
    wmhints->پنجره_گروه = داده->پنجره_گروه;
    wmhints->flags = درون_داد_Hint | پنجره_گروه_Hint;

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
    إذا (داده->pid > 0) {
        دراز pid = (دراز)داده->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_نما_Replace,
                            (بیعلامت حرف *)&pid, 1);
    }

    // Set the window manager state
    X11_مجموعه_Net_WMState(_this, w, پنجره->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_پنجره_TYPE);
    إذا (پنجره->flags & SDL_پنجره_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } وإلا إذا (پنجره->flags & SDL_پنجره_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } وإلا إذا (پنجره->flags & SDL_پنجره_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } وإلا إذا (hint && *hint) {
        wintype_name = hint;
    } وإلا {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_پنجره_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_پنجره_TYPE, XA_ATOM, 32,
                        Prop_نما_Replace, (بیعلامت حرف *)&wintype, 1);
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_نما_Replace,
                            (بیعلامت حرف *)&compositor, 1);
    }

    {
        Atom protocols[4];
        صحيح proto_شمار = 0;

        protocols[proto_شمار++] = داده->atoms.WM_DELETE_پنجره; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_شمار++] = داده->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
        إذا (use_resize_sync) {
            protocols[proto_شمار++] = داده->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_شمار <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_شمار);
    }

    إذا (!راهاندازی_پنجره_داده(_this, پنجره, w)) {
        X11_XDestroy_پنجره(display, w);
        أرجع false;
    }
    windowdata = پنجره->داخلی;

    // Set the parent if this is a non-popup window.
    إذا (!SDL_پنجره_IS_POPUP(پنجره) && پنجره->والد) {
        X11_XSetTransientForHint(display, w, پنجره->والد->داخلی->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(پنجره->pending_flags & SDL_پنجره_FULLSCREEN) &&
                                               !!(پنجره->flags & SDL_پنجره_BORDERLESS);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
    إذا (use_resize_sync) {
        X11_InitResizeSync(پنجره);
    }
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    إذا (پنجره->flags & SDL_پنجره_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_درون_داد, 0, 0, region, Shape_مجموعه);
        X11_XDestroyRegion(region);
    }
#پایان_اگر

    راهاندازی_پنجره_درون_داد(_this, پنجره);

    // For _ICC_PROFILE.
    X11_XSelect_درون_داد(display, ریشه_پنجره(display, screen), Property_Change_ماسک);

    X11_XFlush(display);

    أرجع true;
}

حرف *X11_Get_پنجره_Title(SDL_VideoDevice *_this, پنجره_2 xwindow)
{
    SDL_Video_داده *داده = _this->داخلی;
    Display *display = داده->display;
    صحيح وضعیت, real_format;
    Atom real_type;
    بیعلامت دراز اقلام_read, اقلام_چپ;
    بیعلامت حرف *propdata;
    حرف *title = عدم;

    وضعیت = X11_XGet_پنجره_Property(display, xwindow, داده->atoms._NET_WM_NAME,
                                    0L, 8192L, False, داده->atoms.UTF8_STRING, &real_type, &real_format,
                                    &اقلام_read, &اقلام_چپ, &propdata);
    إذا (وضعیت == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(حرف *, propdata));
        X11_XFree(propdata);
    } وإلا {
        وضعیت = X11_XGet_پنجره_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &اقلام_read, &اقلام_چپ, &propdata);
        إذا (وضعیت == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(حرف *, propdata), اقلام_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } وإلا {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    أرجع title;
}

فراغ X11_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    پنجره_2 xwindow = داده->xwindow;
    Display *display = داده->videodata->display;
    حرف *title = پنجره->title ? پنجره->title : "";

    SDL_X11_مجموعه_پنجره_Title(display, xwindow, title);
}

ساكن bool caught_x11_error = false;
ساكن صحيح X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    أرجع 0;
}

ساكن فراغ X11_ExternalResizeMoveSync(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    بیعلامت صحيح فرزند_شمار;
    پنجره_2 فرزند_Return_2, ریشه, والد;
    پنجره_2 *children;
    XWindow_صفات attrs;
    Uint64 timeout = 0;
    صحيح x, y;
    ثابت bool send_move = !!(داده->pending_operation & X11_PENDING_OP_MOVE);
    ثابت bool send_resize = !!(داده->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_درخت(display, داده->xwindow, &ریشه, &والد, &children, &فرزند_شمار);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_مقصد_NS(100);
    طالما (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_پنجره_صفات(display, داده->xwindow, &attrs);
        X11_XTranslateCoordinates(display, والد, Default_ریشه_پنجره(display),
                                  attrs.x, attrs.y, &x, &y, &فرزند_Return_2);
        SDL_Global_مقصد_Relative_For_پنجره(پنجره, x, y, &x, &y);

        إذا (!caught_x11_error) {
            إذا ((داده->pending_operation & X11_PENDING_OP_MOVE) && (x == داده->expected.x + داده->border_چپ && y == داده->expected.y + داده->border_بالاترین)) {
                داده->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            إذا ((داده->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.عرض == داده->expected.w && attrs.ارتفاع == داده->expected.h)) {
                داده->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            إذا (داده->pending_operation == X11_PENDING_OP_NONE) {
                اكسر;
            }
        }

        إذا (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            داده->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            داده->expected.x = x;
            داده->expected.y = y;
            داده->expected.w = attrs.عرض;
            داده->expected.h = attrs.ارتفاع;
            اكسر;
        }

        SDL_Delay(10);
    }

    إذا (!caught_x11_error) {
        إذا (send_move) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, x, y);
        }
        إذا (send_resize) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, attrs.عرض, attrs.ارتفاع);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ساكن bool X11_Sync_پنجره_Timeout(SDL_VideoDevice *_this, SDL_پنجره *پنجره, Uint64 param_timeout)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool نتیجه = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    إذا (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    طالما (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        إذا ((داده->pending_operation & X11_PENDING_OP_MOVE) && (پنجره->x == داده->expected.x + داده->border_چپ && پنجره->y == داده->expected.y + داده->border_بالاترین)) {
            داده->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        إذا ((داده->pending_operation & X11_PENDING_OP_RESIZE) && (پنجره->w == داده->expected.w && پنجره->h == داده->expected.h)) {
            داده->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        إذا (داده->pending_operation == X11_PENDING_OP_NONE) {
            إذا (force_exit ||
                (پنجره->x == داده->expected.x + داده->border_چپ && پنجره->y == داده->expected.y + داده->border_بالاترین &&
                 پنجره->w == داده->expected.w && پنجره->h == داده->expected.h)) {
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
            داده->expected.x = پنجره->x;
            داده->expected.y = پنجره->y;
            داده->expected.w = پنجره->w;
            داده->expected.h = پنجره->h;

            نتیجه = false;
            اكسر;
        }

        SDL_Delay(10);
    }

    داده->pending_operation = X11_PENDING_OP_NONE;

    إذا (!caught_x11_error) {
        X11_PumpEvents(_this);
    } وإلا {
        نتیجه = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    أرجع نتیجه;
}

bool X11_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    Atom _NET_WM_ICON = داده->videodata->atoms._NET_WM_ICON;
    صحيح (*prevHandler)(Display *, XErrorEvent *) = عدم;
    bool نتیجه = true;

    إذا (icon) {
        صحيح x, y;
        صحيح propsize;
        دراز *propdata;
        Uint32 *src;
        دراز *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * حجم(دراز));

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

        X11_XChangeProperty(display, داده->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_نما_Replace, (بیعلامت حرف *)propdata,
                            propsize);
        SDL_free(propdata);

        إذا (caught_x11_error) {
            نتیجه = SDL_مجموعه_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    إذا (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    أرجع نتیجه;
}

فراغ X11_Update_پنجره_Position(SDL_پنجره *پنجره, bool use_current_position)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    ثابت صحيح rel_x = use_current_position ? پنجره->x : پنجره->pending.x;
    ثابت صحيح rel_y = use_current_position ? پنجره->y : پنجره->pending.y;

    SDL_Relative_مقصد_Global_For_پنجره(پنجره,
                                  rel_x - داده->border_چپ, rel_y - داده->border_بالاترین,
                                  &داده->expected.x, &داده->expected.y);

    // Attempt to move the window
    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        پنجره->داخلی->pending_position = true;
    } وإلا {
        داده->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_پنجره(display, داده->xwindow, داده->expected.x, داده->expected.y);
    }
}

bool X11_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Sync any pending fullscreen or maximize events.
    إذا (پنجره->داخلی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, پنجره);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    إذا (پنجره->flags & SDL_پنجره_MAXIMIZED) {
        إذا (پنجره->داخلی->pending_operation & X11_PENDING_OP_RESTORE) {
            پنجره->داخلی->pending_position = true;
        }
        أرجع true;
    }

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        إذا (SDL_پنجره_IS_POPUP(پنجره)) {
            X11_ConstrainPopup(پنجره, true);
        }
        X11_Update_پنجره_Position(پنجره, false);
    } وإلا {
        پنجره->داخلی->fs_repositioned = true;
        SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    أرجع true;
}

فراغ X11_مجموعه_پنجره_Min_Max(SDL_پنجره *پنجره, bool use_current)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
    دراز hint_flags = 0;

    X11_XGetWMNormalHints(display, داده->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);

    إذا (داده->پنجره->flags & SDL_پنجره_RESIZABLE) {
        إذا (داده->پنجره->min_w || داده->پنجره->min_h) {
            sizehints->flags |= PMin_اندازه;
            sizehints->min_عرض_2 = داده->پنجره->min_w;
            sizehints->min_ارتفاع_2 = داده->پنجره->min_h;
        }
        إذا (داده->پنجره->max_w || داده->پنجره->max_h) {
            sizehints->flags |= PMax_اندازه;
            sizehints->max_عرض_2 = داده->پنجره->max_w;
            sizehints->max_ارتفاع_2 = داده->پنجره->max_h;
        }
        إذا (داده->پنجره->min_aspect > 0.0f || داده->پنجره->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(داده->پنجره->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(داده->پنجره->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } وإلا {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_اندازه | PMax_اندازه;
        إذا (use_current) {
            sizehints->min_عرض_2 = sizehints->max_عرض_2 = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : داده->پنجره->floating.w;
            sizehints->min_ارتفاع_2 = sizehints->max_ارتفاع_2 = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : داده->پنجره->floating.h;
        } وإلا {
            sizehints->min_عرض_2 = sizehints->max_عرض_2 = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : داده->پنجره->windowed.w;
            sizehints->min_ارتفاع_2 = sizehints->max_ارتفاع_2 = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : داده->پنجره->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, داده->xwindow, sizehints);
    X11_XFree(sizehints);
}

فراغ X11_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (پنجره->داخلی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_پنجره(_this, پنجره);
    }

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        X11_مجموعه_پنجره_Min_Max(پنجره, true);
    }
}

فراغ X11_مجموعه_پنجره_بیشینه_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (پنجره->داخلی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_پنجره(_this, پنجره);
    }

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        X11_مجموعه_پنجره_Min_Max(پنجره, true);
    }
}

فراغ X11_مجموعه_پنجره_Aspect_نسبت(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (پنجره->داخلی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_پنجره(_this, پنجره);
    }

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        X11_مجموعه_پنجره_Min_Max(پنجره, true);
    }
}

فراغ X11_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    إذا (داده->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, پنجره);
    }

    // Set the size as pending if the window is being restored.
    إذا (پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_FULLSCREEN)) {
        // New size will be set when the window is restored.
        إذا (داده->pending_operation & X11_PENDING_OP_RESTORE) {
            داده->pending_اندازه = true;
        } وإلا {
            // Can't resize the window.
            پنجره->آخرین_اندازه_pending = false;
        }
        أرجع;
    }

    إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE)) {
        إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            دراز userhints;
            صحيح dest_x, dest_y;

            X11_XGetWMNormalHints(display, داده->xwindow, sizehints, &userhints);

            داده->expected.w = sizehints->min_عرض_2 = sizehints->max_عرض_2 = پنجره->pending.w;
            داده->expected.h = sizehints->min_ارتفاع_2 = sizehints->max_ارتفاع_2 = پنجره->pending.h;
            sizehints->flags |= PMin_اندازه | PMax_اندازه;
            داده->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, داده->xwindow, sizehints);

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
            X11_XResize_پنجره(display, داده->xwindow, پنجره->pending.w, پنجره->pending.h);
            ثابت صحيح x = پنجره->آخرین_position_pending ? پنجره->pending.x : پنجره->x;
            ثابت صحيح y = پنجره->آخرین_position_pending ? پنجره->pending.y : پنجره->y;
            SDL_Relative_مقصد_Global_For_پنجره(پنجره,
                                          x - داده->border_چپ,
                                          y - داده->border_بالاترین,
                                          &dest_x, &dest_y);
            X11_XMove_پنجره(display, داده->xwindow, dest_x, dest_y);
            X11_XRaise_پنجره(display, داده->xwindow);

            X11_XFree(sizehints);
        }
    } وإلا {
        داده->expected.w = پنجره->pending.w;
        داده->expected.h = پنجره->pending.h;
        داده->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_پنجره(display, داده->xwindow, داده->expected.w, داده->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره->pending.w, پنجره->pending.h);
    }
}

bool X11_Get_پنجره_Borders_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *بالاترین, صحيح *چپ, صحيح *bottom, صحيح *راست)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    *چپ = داده->border_چپ;
    *راست = داده->border_راست;
    *بالاترین = داده->border_بالاترین;
    *bottom = داده->border_bottom;

    أرجع true;
}

bool X11_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    Atom NET_WM_پنجره_OPACITY = داده->videodata->atoms.NET_WM_پنجره_OPACITY;

    إذا (opacity == 1.0f) {
        X11_XDeleteProperty(display, داده->xwindow, NET_WM_پنجره_OPACITY);
    } وإلا {
        ثابت Uint32 FullyOpaque = 0xFFFFFFFF;
        ثابت دراز alpha = (دراز)((مزدوج)opacity * (مزدوج)FullyOpaque);
        X11_XChangeProperty(display, داده->xwindow, NET_WM_پنجره_OPACITY, XA_CARDINAL, 32,
                            Prop_نما_Replace, (بیعلامت حرف *)&alpha, 1);
    }

    أرجع true;
}

bool X11_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_پنجره_داده *والد_داده = والد ? والد->داخلی : عدم;
    SDL_Video_داده *video_داده = _this->داخلی;
    Display *display = video_داده->display;

    إذا (والد_داده) {
        X11_XSetTransientForHint(display, داده->xwindow, والد_داده->xwindow);
    } وإلا {
        X11_XDeleteProperty(display, داده->xwindow, video_داده->atoms.WM_TRANSIENT_FOR);
    }

    أرجع true;
}

bool X11_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = video_داده->display;
    Uint32 flags = پنجره->flags;
    Atom _NET_WM_STATE = داده->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = داده->videodata->atoms._NET_WM_STATE_MODAL;

    إذا (modal) {
        flags |= SDL_پنجره_MODAL;
    } وإلا {
        flags &= ~SDL_پنجره_MODAL;
        X11_XDeleteProperty(display, داده->xwindow, video_داده->atoms.WM_TRANSIENT_FOR);
    }

    إذا (X11_Is_پنجره_Mapped(_this, پنجره)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیام;
        e.xclient.پیام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.پنجره = داده->xwindow;
        e.xclient.داده.l[0] = modal ? NET_WM_STATE_جمع_کن : _NET_WM_STATE_REMOVE;
        e.xclient.داده.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.داده.l[3] = 0l;

        X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_مجموعه_Net_WMState(_this, داده->xwindow, flags);
    }

    X11_XFlush(display);

    أرجع true;
}

فراغ X11_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered)
{
    ثابت bool focused = (پنجره->flags & SDL_پنجره_درون_داد_FOCUS) != 0;
    ثابت bool visible = !(پنجره->flags & SDL_پنجره_HIDDEN) && !پنجره->is_hiding;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;
    XEvent event;

    إذا (داده->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_پنجره(_this, پنجره);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        مجموعه_پنجره_Bordered(display, displaydata->screen, داده->xwindow, bordered);
        X11_XFlush(display);

        إذا (visible) {
            XWindow_صفات attr;
            افعل {
                X11_XSync(display, False);
                X11_XGet_پنجره_صفات(display, داده->xwindow, &attr);
            } طالما (attr.map_state != IsViewable);

            إذا (focused) {
                X11_XSet_درون_داد_Focus(display, داده->xwindow, Revert_مقصد_والد, Current_زمان);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&داده->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&داده->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_مقادیر(داده);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_پنجره(display, داده->xwindow, پنجره->floating.w, پنجره->floating.h);
        X11_XSync(display, False);
    } وإلا {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        داده->toggle_borders = true;
        داده->fullscreen_borders_forced_on = false;
    }
}

فراغ X11_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_پنجره(_this, پنجره);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        X11_مجموعه_پنجره_Min_Max(پنجره, true);
    }
}

فراغ X11_مجموعه_پنجره_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool on_بالاترین)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;
    Atom _NET_WM_STATE = داده->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = داده->videodata->atoms._NET_WM_STATE_ABOVE;

    إذا (X11_Is_پنجره_Mapped(_this, پنجره)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیام;
        e.xclient.پیام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.پنجره = داده->xwindow;
        e.xclient.داده.l[0] =
            on_بالاترین ? NET_WM_STATE_جمع_کن : _NET_WM_STATE_REMOVE;
        e.xclient.داده.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.داده.l[3] = 0l;

        X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_مجموعه_Net_WMState(_this, داده->xwindow, پنجره->flags);
    }
    X11_XFlush(display);
}

فراغ X11_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_پنجره_ACTIVATE_WHEN_SHOWN, true);
    bool مجموعه_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    إذا (داده->was_shown) {
        X11_PumpEvents(_this);
    }

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(پنجره, true);
        داده->pending_position = true;
        مجموعه_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (فراغ)bActivate;

    إذا (!X11_Is_پنجره_Mapped(_this, پنجره)) {
        X11_XMapRaised(display, داده->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&داده->xwindow);
        }
        X11_XFlush(display);
        مجموعه_position = داده->pending_position ||
                       (!(پنجره->flags & SDL_پنجره_BORDERLESS) && !پنجره->undefined_x && !پنجره->undefined_y);
    }

    إذا (!داده->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_درون_داد_Focus(display, داده->xwindow, Revert_مقصد_None, Current_زمان);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
        X11_مجموعه_Keyboard_Focus(پنجره, true);
    }

    // Get some valid border values, if we haven't received them yet
    إذا (داده->border_چپ == 0 && داده->border_راست == 0 && داده->border_بالاترین == 0 && داده->border_bottom == 0) {
        X11_Get_Border_مقادیر(داده);
    }

    إذا (مجموعه_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ثابت صحيح tx = (داده->pending_position ? پنجره->pending.x : پنجره->x) - (داده->was_shown ? 0 : داده->border_چپ);
        ثابت صحيح ty = (داده->pending_position ? پنجره->pending.y : پنجره->y) - (داده->was_shown ? 0 : داده->border_بالاترین);
        صحيح x, y;

        SDL_Relative_مقصد_Global_For_پنجره(پنجره, tx, ty, &x, &y);

        داده->pending_position = false;
        X11_XMove_پنجره(display, داده->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_پنجره(display, داده->xwindow, پنجره->w, پنجره->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    داده->اندازه_move_event_flags = X11_اندازه_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    داده->اندازه_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
    داده->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    إذا (داده->آخرین_xconfigure.type) {
        صحيح x, y;
        SDL_Global_مقصد_Relative_For_پنجره(داده->پنجره, داده->آخرین_xconfigure.x, داده->آخرین_xconfigure.y, &x, &y);
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, داده->آخرین_xconfigure.عرض, داده->آخرین_xconfigure.ارتفاع);
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, x, y);
    }
}

فراغ X11_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    Display *display = داده->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ثابت bool is_mapped = X11_Is_پنجره_Mapped(_this, پنجره);
    X11_XWithdraw_پنجره(display, داده->xwindow, screen);
    إذا (is_mapped && !(پنجره->flags & SDL_پنجره_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&داده->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
        SDL_پنجره *new_focus;
        ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(پنجره, &new_focus);
        X11_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ساكن bool X11_مجموعه_پنجره_فعال(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    CHECK_پنجره_داده(پنجره);

    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;
    Atom NET_فعال_پنجره = داده->videodata->atoms.NET_فعال_پنجره;

    إذا (X11_Is_پنجره_Mapped(_this, پنجره)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_پیام;
        e.xclient.پیام_type = NET_فعال_پنجره;
        e.xclient.format = 32;
        e.xclient.پنجره = داده->xwindow;
        e.xclient.داده.l[0] = 1; // source indication. 1 = application
        e.xclient.داده.l[1] = داده->user_زمان;
        e.xclient.داده.l[2] = 0;

        X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);

        X11_XFlush(display);
    }
    أرجع true;
}

فراغ X11_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_پنجره_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_پنجره(display, داده->xwindow);
    إذا (bActivate) {
        X11_مجموعه_پنجره_فعال(_this, پنجره);
    }
    X11_XFlush(display);
}

ساكن bool X11_مجموعه_پنجره_Maximized(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool maximized)
{
    CHECK_پنجره_داده(پنجره);

    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;
    Atom _NET_WM_STATE = داده->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = داده->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = داده->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        أرجع true;
    }

    إذا (X11_Is_پنجره_Mapped(_this, پنجره)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیام;
        e.xclient.پیام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.پنجره = داده->xwindow;
        e.xclient.داده.l[0] =
            maximized ? NET_WM_STATE_جمع_کن : _NET_WM_STATE_REMOVE;
        e.xclient.داده.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.داده.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.داده.l[3] = 0l;

        إذا (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_پنجره(پنجره);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            داده->expected.x = bounds.x + داده->border_چپ;
            داده->expected.y = bounds.y + داده->border_بالاترین;
            داده->expected.w = bounds.w - (داده->border_چپ + داده->border_راست);
            داده->expected.h = bounds.h - (داده->border_بالاترین + داده->border_bottom);
        } وإلا {
            داده->expected.x = پنجره->floating.x;
            داده->expected.y = پنجره->floating.y;
            داده->expected.w = پنجره->floating.w;
            داده->expected.h = پنجره->floating.h;
        }

        X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
    } وإلا {
        X11_مجموعه_Net_WMState(_this, داده->xwindow, پنجره->flags);
    }
    X11_XFlush(display);

    أرجع true;
}

فراغ X11_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (پنجره->داخلی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_پنجره(پنجره);
    }

    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        پنجره->داخلی->پنجره_was_maximized = true;
        أرجع;
    }

    إذا (!(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        پنجره->داخلی->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_مجموعه_پنجره_Maximized(_this, پنجره, true);
    }
}

فراغ X11_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;

    إذا (داده->pending_operation & SDL_پنجره_FULLSCREEN) {
        SDL_Sync_پنجره(پنجره);
    }

    داده->pending_operation |= X11_PENDING_OP_MINIMIZE;
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        داده->پنجره_was_maximized = !!(پنجره->flags & SDL_پنجره_MAXIMIZED);
    }
    X11_XIconify_پنجره(display, داده->xwindow, displaydata->screen);
    X11_XFlush(display);
}

فراغ X11_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Don't restore the window the first time it is being shown.
    إذا (!پنجره->داخلی->was_shown) {
        أرجع;
    }

    إذا (پنجره->داخلی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_پنجره(پنجره);
    }

    إذا ((پنجره->flags & SDL_پنجره_FULLSCREEN) && !(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        پنجره->داخلی->پنجره_was_maximized = false;
        أرجع;
    }

    إذا (پنجره->flags & (SDL_پنجره_MINIMIZED | SDL_پنجره_MAXIMIZED) ||
        (پنجره->داخلی->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        پنجره->داخلی->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ثابت bool maximize = !!(پنجره->flags & SDL_پنجره_MINIMIZED) && پنجره->داخلی->پنجره_was_maximized;
    X11_مجموعه_پنجره_Maximized(_this, پنجره, maximize);
    X11_Show_پنجره(_this, پنجره);
    X11_مجموعه_پنجره_فعال(_this, پنجره);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ساكن SDL_Fullscreen_نتیجه X11_مجموعه_پنجره_Fullscreen_از_طریق_WM(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = _display->داخلی;
    Display *display = داده->videodata->display;
    Atom _NET_WM_STATE = داده->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = داده->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    إذا (!داده->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (X11_Is_پنجره_Mapped(_this, پنجره)) {
        XEvent e;

        // Flush any pending fullscreen events.
        إذا (داده->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_پنجره(_this, پنجره);
        }

        إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
            إذا (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                أرجع SDL_FULLSCREEN_FAILED;
            } وإلا إذا (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                أرجع SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        إذا (fullscreen && !(پنجره->flags & SDL_پنجره_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            دراز flags = 0;
            X11_XGetWMNormalHints(display, داده->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);
            X11_XSetWMNormalHints(display, داده->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_پیام;
        e.xclient.پیام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.پنجره = داده->xwindow;
        e.xclient.داده.l[0] =
            fullscreen ? NET_WM_STATE_جمع_کن : _NET_WM_STATE_REMOVE;
        e.xclient.داده.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.داده.l[3] = 0l;

        X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                       Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        إذا (((پنجره->flags & SDL_پنجره_FULLSCREEN) != 0) != (fullscreen != 0)) {
            داده->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        إذا (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_پنجره_Position(پنجره);
            SDL_copyp(&داده->requested_fullscreen_نما, &پنجره->current_fullscreen_نما);
            إذا (fullscreen != !!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
                داده->پنجره_was_maximized = !!(پنجره->flags & SDL_پنجره_MAXIMIZED);
            }
            داده->expected.x = displaydata->x;
            داده->expected.y = displaydata->y;
            داده->expected.w = _display->current_نما->w;
            داده->expected.h = _display->current_نما->h;

            // Only move the window if it isn't already on the target display.
            إذا (!current || current != _display->id) {
                X11_XMove_پنجره(display, داده->xwindow, displaydata->x, displaydata->y);
                داده->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } وإلا {
            SDL_zero(داده->requested_fullscreen_نما);
            داده->pending_position = داده->fs_repositioned;
            داده->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_پیام;
            e.xclient.پیام_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.پنجره = داده->xwindow;
            إذا (داده->پنجره_was_maximized) {
                e.xclient.داده.l[0] = NET_WM_STATE_جمع_کن;
            } وإلا {
                e.xclient.داده.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.داده.l[1] = داده->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.داده.l[2] = داده->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.داده.l[3] = 0l;
            X11_XSendEvent(display, ریشه_پنجره(display, displaydata->screen), 0,
                           Substructure_Notify_ماسک | Substructure_Redirect_ماسک, &e);
        }
    } وإلا {
        SDL_پنجره_Flags flags;

        flags = پنجره->flags;
        إذا (fullscreen) {
            flags |= SDL_پنجره_FULLSCREEN;
        } وإلا {
            flags &= ~SDL_پنجره_FULLSCREEN;
        }
        X11_مجموعه_Net_WMState(_this, داده->xwindow, flags);
    }

    إذا (داده->visual->class == مستقیم_Color) {
        إذا (fullscreen) {
            X11_XInstallColormap(display, داده->colormap);
        } وإلا {
            X11_XUninstallColormap(display, داده->colormap);
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

ساكن SDL_Fullscreen_نتیجه X11_مجموعه_پنجره_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = _display->داخلی;
    Display *display = داده->videodata->display;
    ثابت صحيح screen = displaydata->screen;

    إذا (!داده->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    إذا (داده->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_پنجره(_this, پنجره);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_پنجره_Event(پنجره, fullscreen ? SDL_EVENT_پنجره_ENTER_FULLSCREEN : SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
    إذا (fullscreen) {
        إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_اندازه_Hints();
            دراز flags = 0;
            X11_XGetWMNormalHints(display, داده->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_اندازه | PMax_اندازه | PAspect);
            X11_XSetWMNormalHints(display, داده->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        مجموعه_پنجره_Bordered(display, screen, داده->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        داده->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        داده->expected.x = rect.x;
        داده->expected.y = rect.y;
        داده->expected.w = rect.w;
        داده->expected.h = rect.h;
        X11_XMove_پنجره(display, داده->xwindow, rect.x, rect.y);
        X11_XResize_پنجره(display, داده->xwindow, rect.w, rect.h);
        X11_XRaise_پنجره(display, داده->xwindow);
    } وإلا {
        داده->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        داده->expected.x = پنجره->windowed.x;
        داده->expected.y = پنجره->windowed.y;
        داده->expected.w = پنجره->windowed.w;
        داده->expected.h = پنجره->windowed.h;
        X11_XResize_پنجره(display, داده->xwindow, پنجره->windowed.w, پنجره->windowed.h);
        X11_XMove_پنجره(display, داده->xwindow, پنجره->windowed.x, پنجره->windowed.y);

        مجموعه_پنجره_Bordered(display, screen, داده->xwindow, (پنجره->flags & SDL_پنجره_BORDERLESS) == 0);
        X11_مجموعه_پنجره_Min_Max(داده->پنجره, false);
    }

    X11_XFlush(display);

    أرجع SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_نتیجه X11_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_پنجره_داده(پنجره);
    CHECK_DISPLAY_داده(_display);

    SDL_Video_داده *داده = _this->داخلی;
    إذا (داده->net_wm) {
        أرجع X11_مجموعه_پنجره_Fullscreen_از_طریق_WM(_this, پنجره, _display, fullscreen);
    }

    أرجع X11_مجموعه_پنجره_Fullscreen_Legacy(_this, پنجره, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

تعريفنوع بنية
{
    بیعلامت حرف *داده;
    صحيح format, شمار;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, پنجره_2 w, Atom prop)
{
    بیعلامت حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بیعلامت دراز شمار;
    بیعلامت دراز بایتها_چپ;
    صحيح بایتها_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_پنجره_Property(disp, w, prop, 0, بایتها_fetch, False, AnyPropertyType, &type, &fmt, &شمار, &بایتها_چپ, &ret);
        بایتها_fetch += بایتها_چپ;
    } طالما (بایتها_چپ != 0);

    p->داده = ret;
    p->format = fmt;
    p->شمار = شمار;
    p->type = type;
}

فراغ *X11_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    XWindow_صفات صفات;
    Atom icc_profile_atom;
    حرف icc_atom_string[حجم("_ICC_PROFILE_") + 12];
    فراغ *ret_icc_profile_داده = عدم;
    CARD8 *icc_profile_داده;
    صحيح real_format;
    بیعلامت دراز real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_پنجره_صفات(display, داده->xwindow, &صفات);
    إذا (X11_XScreen_عدد_از_Screen(صفات.screen) > 0) {
        (فراغ)SDL_snprintf(icc_atom_string, حجم("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_عدد_از_Screen(صفات.screen));
    } وإلا {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", حجم("_ICC_PROFILE"));
    }
    X11_XGet_پنجره_صفات(display, ریشه_پنجره_از_Screen(صفات.screen), &صفات);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    إذا (icc_profile_atom == None) {
        SDL_مجموعه_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    X11_ReadProperty(&atomProp, display, ریشه_پنجره_از_Screen(صفات.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.شمار;
    icc_profile_داده = atomProp.داده;
    إذا (real_format == None) {
        SDL_مجموعه_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    ret_icc_profile_داده = SDL_malloc(real_nitems);
    إذا (!ret_icc_profile_داده) {
        أرجع عدم;
    }

    SDL_memcpy(ret_icc_profile_داده, icc_profile_داده, real_nitems);
    *اندازه = real_nitems;
    X11_XFree(icc_profile_داده);

    أرجع ret_icc_profile_داده;
}

bool X11_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display;

    إذا (!داده) {
        أرجع SDL_مجموعه_Error("Invalid window data");
    }
    داده->mouse_grabbed = false;
    داده->pending_grab = false;

    display = داده->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
            أرجع true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        إذا (داده->xinput2_mouse_enabled && SDL_GetMouseState(عدم, عدم)) {
            داده->pending_grab = true;
            أرجع true;
        }

        // Try to grab the mouse
        إذا (!داده->videodata->broken_اشاره_گر_grab) {
            ثابت بیعلامت صحيح ماسک = Button_Press_ماسک | Button_Release_ماسک | اشاره_گر_Motion_ماسک | Focus_Change_ماسک;
            صحيح attempts;
            صحيح نتیجه = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            لكل (attempts = 0; attempts < 100; attempts++) {
                نتیجه = X11_XGrab_اشاره_گر(display, داده->xwindow, False, ماسک, Grab_نما_Async,
                                          Grab_نما_Async, داده->xwindow, None, Current_زمان);
                إذا (نتیجه == GrabSuccess) {
                    داده->mouse_grabbed = true;
                    اكسر;
                }
                SDL_Delay(50);
            }

            إذا (نتیجه != GrabSuccess) {
                داده->videodata->broken_اشاره_گر_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, پنجره);

        // Raise the window if we grab the mouse
        X11_XRaise_پنجره(display, داده->xwindow);
    } وإلا {
        X11_XUngrab_اشاره_گر(display, Current_زمان);

        X11_Xinput2UngrabTouch(_this, پنجره);
    }
    X11_XSync(display, False);

    إذا (!داده->videodata->broken_اشاره_گر_grab) {
        أرجع true;
    } وإلا {
        أرجع SDL_مجموعه_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_مجموعه_پنجره_Keyboard_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display;

    إذا (!داده) {
        أرجع SDL_مجموعه_Error("Invalid window data");
    }

    display = داده->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
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
        إذا (_this->داخلی->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            إذا (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_پیام_Event client_پیام;
                client_پیام.type = Client_پیام;
                client_پیام.پنجره = داده->xwindow;
                client_پیام.format = 32;
                client_پیام.پیام_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_پیام.داده.l[0] = 1;
                client_پیام.داده.l[1] = Current_زمان;

                X11_XSendEvent(display, Default_ریشه_پنجره(display), False, Substructure_Notify_ماسک | Substructure_Redirect_ماسک, (XEvent *)&client_پیام);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, داده->xwindow, True, Grab_نما_Async,
                          Grab_نما_Async, Current_زمان);
    } وإلا {
        X11_XUngrabKeyboard(display, Current_زمان);
    }
    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده) {
        SDL_Video_داده *videodata = داده->videodata;
        Display *display = videodata->display;
        صحيح numwindows = videodata->numwindows;
        SDL_پنجره_داده **windowlist = videodata->windowlist;
        صحيح i;

        إذا (windowlist) {
            لكل (i = 0; i < numwindows; ++i) {
                إذا (windowlist[i] && (windowlist[i]->پنجره == پنجره)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = عدم;
                    videodata->numwindows--;
                    اكسر;
                }
            }
        }

        X11_Destroy_درون_داد_Context(داده);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
        X11_جمله_Resize_Sync(پنجره);
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */

        إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
            X11_XDestroy_پنجره(display, داده->xwindow);
            X11_XFlush(display);
        }
        SDL_free(داده);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        إذا (videodata->فعال_cursor_confined_پنجره == پنجره) {
            X11_Destroy_اشاره_گر_Barrier(_this, پنجره);
        }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    پنجره->داخلی = عدم;
}

bool X11_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

فراغ X11_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    Atom XdndAware = داده->videodata->atoms.XdndAware;

    إذا (accept) {
        Atom xdnd_نسخه = 5;
        X11_XChangeProperty(display, داده->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_نما_Replace, (بیعلامت حرف *)&xdnd_نسخه, 1);
    } وإلا {
        X11_XDeleteProperty(display, داده->xwindow, XdndAware);
    }
}

bool X11_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, داده->xwindow);
    إذا (!wmhints) {
        أرجع SDL_مجموعه_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    داده->flashing_پنجره = false;
    داده->flash_cancel_زمان = 0;

    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        // Taken care of above
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        إذا (!(پنجره->flags & SDL_پنجره_درون_داد_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            داده->flashing_پنجره = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            داده->flash_cancel_زمان = SDL_GetTicks() + 1000;
        }
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        إذا (!(پنجره->flags & SDL_پنجره_درون_داد_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            داده->flashing_پنجره = true;
        }
        اكسر;
    افتراضي:
        اكسر;
    }

    X11_XSetWMHints(display, داده->xwindow, wmhints);
    X11_XFree(wmhints);
    أرجع true;
}

bool SDL_X11_مجموعه_پنجره_Title(Display *display, پنجره_2 xwindow, حرف *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    صحيح conv = X11_Xmb_متن_List_مقصد_متن_Property(display, &title, 1, XTextStyle, &titleprop);
    وضعیت_2 وضعیت;

    إذا (X11_XSupportsLocale() != True) {
        أرجع SDL_مجموعه_Error("Current locale not supported by X server, cannot continue.");
    }

    إذا (conv == 0) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.مقدار);
        // we know this can't be a locale error as we checked X locale validity
    } وإلا إذا (conv < 0) {
        أرجع SDL_بیرون_از_حافظه();
    } وإلا { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        أرجع true;
    }

#اگر_تعریف_شده X_HAVE_UTF8_STRING
    وضعیت = X11_Xutf8_متن_List_مقصد_متن_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    إذا (وضعیت == Success) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.مقدار);
    } وإلا {
        أرجع SDL_مجموعه_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#پایان_اگر

    X11_XFlush(display);
    أرجع true;
}

فراغ X11_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    Display *display = داده->videodata->display;
    پنجره_2 ریشه = ریشه_پنجره(display, displaydata->screen);
    XClient_پیام_Event e;
    پنجره_2 فرزند_Return_2;
    صحيح wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, داده->xwindow, ریشه, x, y, &wx, &wy, &فرزند_Return_2);

    e.type = Client_پیام;
    e.پنجره = داده->xwindow;
    e.پیام_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.داده.l[0] = 0;  // GTK device ID (unused)
    e.داده.l[1] = wx; // X coordinate relative to root
    e.داده.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, ریشه, False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    إذا ((پنجره->flags & SDL_پنجره_EXTERNAL) &&
        (داده->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(پنجره);
            أرجع true;
    }

    ثابت Uint64 current_زمان = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
        إذا (_this->displays[i]->داخلی->نما_switch_deadline_ns &&
            current_زمان < _this->displays[i]->داخلی->نما_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->داخلی->نما_switch_deadline_ns - current_زمان, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += پنجره->داخلی->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_مقصد_NS(1000) : SDL_MS_مقصد_NS(100);

    أرجع X11_Sync_پنجره_Timeout(_this, پنجره, timeout);
}

bool X11_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable)
{
    إذا (!SDL_پنجره_IS_POPUP(پنجره)) {
        SDL_پنجره_داده *داده = پنجره->داخلی;
        Display *display = داده->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, داده->xwindow);
        إذا (!wmhints) {
            أرجع SDL_مجموعه_Error("Couldn't get WM hints");
        }

        wmhints->درون_داد = focusable ? True : False;
        wmhints->flags |= درون_داد_Hint;

        X11_XSetWMHints(display, داده->xwindow, wmhints);
        X11_XFree(wmhints);
    } وإلا إذا (پنجره->flags & SDL_پنجره_POPUP_MENU) {
        إذا (!(پنجره->flags & SDL_پنجره_HIDDEN)) {
            إذا (!focusable && (پنجره->flags & SDL_پنجره_درون_داد_FOCUS)) {
                SDL_پنجره *new_focus;
                ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(پنجره, &new_focus);
                X11_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(پنجره)) {
                    X11_مجموعه_Keyboard_Focus(پنجره, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
