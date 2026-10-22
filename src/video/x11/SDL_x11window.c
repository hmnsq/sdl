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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

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

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#جے_انت

#ضمن "SDL_x11xsync.h"

#تعریف_کرو _NET_WM_STATE_REMOVE 0l
#تعریف_کرو NET_WM_STATE_جوڑو    1l

#تعریف_کرو CHECK_کھڑکی_انکڑے(کھڑکی)                                       \
    إذا (!کھڑکی) {                                                      \
        أرجع SDL_سیٹ_Error("Invalid window");                          \
    }                                                                   \
    إذا (!کھڑکی->اندرونی) {                                          \
        أرجع SDL_سیٹ_Error("Invalid window driver data");              \
    }

#تعریف_کرو CHECK_DISPLAY_انکڑے(display)                                     \
    إذا (!_display) {                                                    \
        أرجع SDL_سیٹ_Error("Invalid display");                         \
    }                                                                   \
    إذا (!_display->اندرونی) {                                        \
        أرجع SDL_سیٹ_Error("Invalid display driver data");             \
    }

ساكن Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == MapNotify && ev->xmap.کھڑکی == *((کھڑکی_2 *)win);
}
ساكن Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    أرجع ev->type == UnmapNotify && ev->xunmap.کھڑکی == *((کھڑکی_2 *)win);
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

ساكن bool X11_Is_کھڑکی_Mapped(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    XWindow_گن attr;

    X11_XGet_کھڑکی_گن(videodata->display, انکڑے->xwindow, &attr);
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
ساكن bool X11_IsActionAllowed(SDL_کھڑکی *کھڑکی, Atom action)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Atom _NET_WM_ALLOWED_ACTIONS = انکڑے->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = انکڑے->videodata->display;
    صحيح form;
    بنانشانی لما remain;
    بنانشانی لما len, i;
    Atom *list;
    bool ret = false;

    إذا (X11_XGet_کھڑکی_Property(display, انکڑے->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (بنانشانی حرف **)&list) == Success) {
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
#جے_انت // 0

ساكن فراغ X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخری_position_pending = کھڑکی->آخری_position_pending;
    ثابت bool آخری_ناپ_pending = کھڑکی->آخری_ناپ_pending;

    X11_Sync_کھڑکی(_this, کھڑکی);

    کھڑکی->آخری_position_pending = آخری_position_pending;
    کھڑکی->آخری_ناپ_pending = آخری_ناپ_pending;
}

فراغ X11_سیٹ_Net_WMState(SDL_VideoDevice *_this, کھڑکی_2 xwindow, SDL_کھڑکی_Flags flags)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
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
    صحيح گنتی = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    إذا (flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        atoms[گنتی++] = _NET_WM_STATE_ABOVE;
    }
    إذا (flags & SDL_کھڑکی_UTILITY) {
        atoms[گنتی++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[گنتی++] = _NET_WM_STATE_SKIP_PAGER;
    }
    إذا (flags & SDL_کھڑکی_داخلہ_FOCUS) {
        atoms[گنتی++] = _NET_WM_STATE_FOCUSED;
    }
    إذا (flags & SDL_کھڑکی_MAXIMIZED) {
        atoms[گنتی++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[گنتی++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    إذا (flags & SDL_کھڑکی_FULLSCREEN) {
        atoms[گنتی++] = _NET_WM_STATE_FULLSCREEN;
    }
    إذا (flags & SDL_کھڑکی_MODAL) {
        atoms[گنتی++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(گنتی <= SDL_arraysize(atoms));

    إذا (گنتی > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_منوال_Replace, (بنانشانی حرف *)atoms, گنتی);
    } وإلا {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ساكن فراغ X11_ConstrainPopup(SDL_کھڑکی *کھڑکی, bool output_منزل_pending)
{
    // Clamp popup windows to the output borders
    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحيح abs_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->floating.x;
        صحيح abs_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->floating.y;
        صحيح وتھ_x = 0, وتھ_y = 0;

        إذا (کھڑکی->constrain_popup) {
            // Calculate the total offset from the parents
            لكل (w = کھڑکی->ماپا; SDL_کھڑکی_IS_POPUP(w); w = w->ماپا) {
                وتھ_x += w->x;
                وتھ_y += w->y;
            }

            وتھ_x += w->x;
            وتھ_y += w->y;
            abs_x += وتھ_x;
            abs_y += وتھ_y;

            displayID = SDL_Get_Display_For_کھڑکی(w);

            SDL_GetDisplayBounds(displayID, &rect);
            إذا (abs_x + کھڑکی->w > rect.x + rect.w) {
                abs_x -= (abs_x + کھڑکی->w) - (rect.x + rect.w);
            }
            إذا (abs_y + کھڑکی->h > rect.y + rect.h) {
                abs_y -= (abs_y + کھڑکی->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        إذا (output_منزل_pending) {
            کھڑکی->pending.x = abs_x - وتھ_x;
            کھڑکی->pending.y = abs_y - وتھ_y;
        } وإلا {
            کھڑکی->floating.x = کھڑکی->windowed.x = abs_x - وتھ_x;
            کھڑکی->floating.y = کھڑکی->windowed.y = abs_y - وتھ_y;
        }
    }
}

ساكن فراغ X11_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_سرگرم_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the toplevel parent
    طالما (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->ماپا;
    }

    toplevel->keyboard_focus = کھڑکی;

    إذا (سیٹ_سرگرم_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

SDL_کھڑکی_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 xwindow)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    صحيح actualFormat;
    بنانشانی لما i, عدد_اشیاء, بائٹاں_After;
    بنانشانی حرف *property_قدر = عدم;
    لما max_لمائی = 1024;
    SDL_کھڑکی_Flags flags = 0;

    إذا (X11_XGet_کھڑکی_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_لمائی, False, XA_ATOM, &actualType,
                               &actualFormat, &عدد_اشیاء, &بائٹاں_After,
                               &property_قدر) == Success) {
        Atom *atoms = (Atom *)property_قدر;
        صحيح maximized = 0;
        صحيح fullscreen = 0;

        لكل (i = 0; i < عدد_اشیاء; ++i) {
            إذا (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_OCCLUDED;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_کھڑکی_داخلہ_FOCUS;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } وإلا إذا (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        إذا (fullscreen == 1) {
            flags |= SDL_کھڑکی_FULLSCREEN;
        } وإلا إذا (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN);
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
                flags |= (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
            } وإلا {
                flags |= SDL_کھڑکی_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_گن attr;
            SDL_zero(attr);
            X11_XGet_کھڑکی_گن(videodata->display, xwindow, &attr);
            إذا (attr.map_state == IsUnmapped) {
                flags |= SDL_کھڑکی_HIDDEN;
            }
        }
        X11_XFree(property_قدر);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    أرجع flags;
}

ساكن bool تیاری_کھڑکی_انکڑے(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 w)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    SDL_کھڑکی_انکڑے *انکڑے;

    // Allocate the window data
    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }
    انکڑے->videodata = videodata;
    انکڑے->کھڑکی = کھڑکی;
    انکڑے->xwindow = w;
    انکڑے->کامیابی_test_نتیجہ = SDL_HITTEST_عام;

    X11_Create_داخلہ_Context(انکڑے);

    // Associate the data with the window

    إذا (videodata->numwindows >= videodata->windowlistlength) {
        SDL_کھڑکی_انکڑے ** new_windowlist = (SDL_کھڑکی_انکڑے **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * حجم(*videodata->windowlist));
        إذا (!new_windowlist) {
            اذهب error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_گن attrib;

        X11_XGet_کھڑکی_گن(انکڑے->videodata->display, w, &attrib);
        إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            کھڑکی->x = کھڑکی->windowed.x = کھڑکی->floating.x = attrib.x;
            کھڑکی->y = کھڑکی->windowed.y = کھڑکی->floating.y = attrib.y - انکڑے->border_چوٹی;
        }
        کھڑکی->w = کھڑکی->windowed.w = کھڑکی->floating.w = attrib.چوڑائی;
        کھڑکی->h = کھڑکی->windowed.h = کھڑکی->floating.h = attrib.اچائی;
        إذا (attrib.map_state != IsUnmapped) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        } وإلا {
            کھڑکی->flags |= SDL_کھڑکی_HIDDEN;
        }
        انکڑے->visual = attrib.visual;
        انکڑے->colormap = attrib.colormap;
    }

    کھڑکی->flags |= X11_GetNetWMState(_this, کھڑکی, w);

    {
        کھڑکی_2 Focal_کھڑکی;
        صحيح Revert_منزل = 0;
        X11_XGet_داخلہ_Focus(انکڑے->videodata->display, &Focal_کھڑکی, &Revert_منزل);
        إذا (Focal_کھڑکی == w) {
            کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
        }

        إذا (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            SDL_سیٹ_Keyboard_Focus(انکڑے->کھڑکی);
        }

        إذا (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Query the title from the existing window
        کھڑکی->title = X11_Get_کھڑکی_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_X11_DISPLAY_اشارہ_گر, انکڑے->videodata->display);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_X11_SCREEN_نمبر, screen);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_X11_کھڑکی_نمبر, انکڑے->xwindow);


#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    إذا ((کھڑکی->flags & SDL_کھڑکی_OPENGL) &&
        ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_انکڑے || X11_GL_UseEGL(_this))
#جے_انت
    ) {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (!_this->egl_انکڑے) {
            اذهب error_cleanup;
        }

        // Create the GLES window surface
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)w);

        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            SDL_سیٹ_Error("Could not create GLES window surface");
            اذهب error_cleanup;
        }
#وإلا
        SDL_سیٹ_Error("Could not create GLES window surface (EGL support not configured)");
        اذهب error_cleanup;
#جے_انت // SDL_VIDEO_OPENGL_EGL
    }
#جے_انت

    // All done!
    کھڑکی->اندرونی = انکڑے;
    videodata->windowlist[videodata->numwindows++] = انکڑے;
    أرجع true;

error_cleanup:
    X11_Destroy_داخلہ_Context(انکڑے);
    SDL_free(انکڑے);
    أرجع false;
}

ساكن فراغ تیاری_کھڑکی_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    لما fevent = 0;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    کھڑکی_2 xwindow = انکڑے->xwindow;

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8 && انکڑے->ic) {
        X11_XGetICValues(انکڑے->ic, XNFilterEvents, &fevent, عدم);
    }
#جے_انت

    X11_Xinput2Select(_this, کھڑکی);

    {
        بنانشانی صحيح x11_keyboard_events = کلید_Press_نقاب | کلید_Release_نقاب;
        بنانشانی صحيح x11_اشارہ_گر_events = Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب;

        X11_Xinput2SelectMouseAndKeyboard(_this, کھڑکی);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        إذا (انکڑے->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        إذا (انکڑے->xinput2_mouse_enabled) {
            x11_اشارہ_گر_events = 0;
        }

        X11_XSelect_داخلہ(انکڑے->videodata->display, xwindow,
                         (Focus_Change_نقاب | Enter_کھڑکی_نقاب | Leave_کھڑکی_نقاب | Exposure_نقاب |
                          x11_keyboard_events | x11_اشارہ_گر_events |
                          Property_Change_نقاب | Structure_Notify_نقاب |
                          Keymap_State_نقاب | fevent));
    }
}

ساكن فراغ سیٹ_کھڑکی_Bordered(Display *display, صحيح screen, کھڑکی_2 کھڑکی, bool border)
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
            بنانشانی لما flags;
            بنانشانی لما functions;
            بنانشانی لما decorations;
            لما داخلہ_منوال;
            بنانشانی لما حالت;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, کھڑکی, WM_HINTS, WM_HINTS, 32,
                            Prop_منوال_Replace, (بنانشانی حرف *)&MWMHints,
                            حجم(MWMHints) / حجم(لما));
    } وإلا { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, کھڑکی, جڑ_کھڑکی(display, screen));
    }
}

bool X11_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    کھڑکی_2 w = (کھڑکی_2)SDL_Get_نمبر_Property(create_props, SDL_PROP_کھڑکی_CREATE_X11_کھڑکی_نمبر,
                (کھڑکی_2)SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    إذا (w) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;

        إذا (!تیاری_کھڑکی_انکڑے(_this, کھڑکی, w)) {
            أرجع false;
        }

        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_کھڑکی_داخلہ, true)) {
            تیاری_کھڑکی_داخلہ(_this, کھڑکی);
        }
        أرجع true;
    }

    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    إذا (!displaydata) {
        أرجع SDL_سیٹ_Error("Could not find display info");
    }

    ثابت bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ثابت bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (کھڑکی->flags & SDL_کھڑکی_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_کھڑکی_انکڑے *windowdata;
    Display *display = انکڑے->display;
    صحيح screen = displaydata->screen;
    Visual *visual;
    صحيح ڈونگھائی_2;
    XSet_کھڑکی_گن xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_کھڑکی_TYPE;
    Atom wintype;
    ثابت حرف *wintype_name = عدم;
    لما compositor = 1;
    Atom _NET_WM_PID;
    ثابت حرف *hint = عدم;
    صحيح win_x, win_y;
    bool undefined_position = false;

#إذا defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ثابت صحيح transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;
    ثابت حرف *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_کھڑکی_VISUALID);
    ثابت حرف *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    إذا (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, سانچا;
        صحيح nvis;

        SDL_zero(سانچا);
        سانچا.visualid = SDL_strtol(forced_visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &سانچا, &nvis);
        إذا (vi) {
            visual = vi->visual;
            ڈونگھائی_2 = vi->ڈونگھائی_2;
            X11_XFree(vi);
        } وإلا {
            أرجع false;
        }
    } وإلا إذا ((کھڑکی->flags & SDL_کھڑکی_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = عدم;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_انکڑے || X11_GL_UseEGL(_this))
#جے_انت
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } وإلا
#جے_انت
        {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#جے_انت
        }

        إذا (!vinfo) {
            أرجع false;
        }
        visual = vinfo->visual;
        ڈونگھائی_2 = vinfo->ڈونگھائی_2;
        X11_XFree(vinfo);
    } وإلا
#جے_انت
    {
        visual = displaydata->visual;
        ڈونگھائی_2 = displaydata->ڈونگھائی_2;
    }

    xattr.override_redirect = ((کھڑکی->flags & SDL_کھڑکی_TOOLTIP) || (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    إذا (visual->class == سدھا_Color) {
        XColor *colorcells;
        صحيح i;
        صحيح ncolors;
        صحيح rmax, gmax, bmax;
        صحيح rmask, gmask, bmask;
        صحيح rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        إذا (!xattr.colormap) {
            أرجع SDL_سیٹ_Error("Could not create writable colormap");
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
            X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                visual, AllocNone);
    }

    إذا (کھڑکی->undefined_x && کھڑکی->undefined_y &&
        کھڑکی->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        X11_ConstrainPopup(کھڑکی, false);
    }
    SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی,
                                  کھڑکی->floating.x, کھڑکی->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_کھڑکی(display, جڑ_کھڑکی(display, screen),
                          win_x, win_y, کھڑکی->floating.w, کھڑکی->floating.h,
                          0, ڈونگھائی_2, داخلہ_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    إذا (!w) {
        أرجع SDL_سیٹ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    إذا (!(کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN)) {
        سیٹ_کھڑکی_Bordered(display, screen, w, !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
    }

    sizehints = X11_XAlloc_ناپ_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->floating.w;
        sizehints->min_اچائی_2 = sizehints->max_اچائی_2 = کھڑکی->floating.h;
        sizehints->flags |= (PMax_ناپ | PMin_ناپ);
    }
    إذا (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->داخلہ = !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE) ? True : False;
    wmhints->کھڑکی_گروہ = انکڑے->کھڑکی_گروہ;
    wmhints->flags = داخلہ_Hint | کھڑکی_گروہ_Hint;

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
    إذا (انکڑے->pid > 0) {
        لما pid = (لما)انکڑے->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_منوال_Replace,
                            (بنانشانی حرف *)&pid, 1);
    }

    // Set the window manager state
    X11_سیٹ_Net_WMState(_this, w, کھڑکی->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_کھڑکی_TYPE);
    إذا (کھڑکی->flags & SDL_کھڑکی_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } وإلا إذا (hint && *hint) {
        wintype_name = hint;
    } وإلا {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                        Prop_منوال_Replace, (بنانشانی حرف *)&wintype, 1);
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_منوال_Replace,
                            (بنانشانی حرف *)&compositor, 1);
    }

    {
        Atom protocols[4];
        صحيح proto_گنتی = 0;

        protocols[proto_گنتی++] = انکڑے->atoms.WM_DELETE_کھڑکی; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_گنتی++] = انکڑے->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        إذا (use_resize_sync) {
            protocols[proto_گنتی++] = انکڑے->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_گنتی <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_گنتی);
    }

    إذا (!تیاری_کھڑکی_انکڑے(_this, کھڑکی, w)) {
        X11_XDestroy_کھڑکی(display, w);
        أرجع false;
    }
    windowdata = کھڑکی->اندرونی;

    // Set the parent if this is a non-popup window.
    إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی) && کھڑکی->ماپا) {
        X11_XSetTransientForHint(display, w, کھڑکی->ماپا->اندرونی->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN) &&
                                               !!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    إذا (use_resize_sync) {
        X11_InitResizeSync(کھڑکی);
    }
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    إذا (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_داخلہ, 0, 0, region, Shape_سیٹ);
        X11_XDestroyRegion(region);
    }
#جے_انت

    تیاری_کھڑکی_داخلہ(_this, کھڑکی);

    // For _ICC_PROFILE.
    X11_XSelect_داخلہ(display, جڑ_کھڑکی(display, screen), Property_Change_نقاب);

    X11_XFlush(display);

    أرجع true;
}

حرف *X11_Get_کھڑکی_Title(SDL_VideoDevice *_this, کھڑکی_2 xwindow)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    Display *display = انکڑے->display;
    صحيح حالت, real_format;
    Atom real_type;
    بنانشانی لما اشیاء_read, اشیاء_بایاں;
    بنانشانی حرف *propdata;
    حرف *title = عدم;

    حالت = X11_XGet_کھڑکی_Property(display, xwindow, انکڑے->atoms._NET_WM_NAME,
                                    0L, 8192L, False, انکڑے->atoms.UTF8_STRING, &real_type, &real_format,
                                    &اشیاء_read, &اشیاء_بایاں, &propdata);
    إذا (حالت == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(حرف *, propdata));
        X11_XFree(propdata);
    } وإلا {
        حالت = X11_XGet_کھڑکی_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &اشیاء_read, &اشیاء_بایاں, &propdata);
        إذا (حالت == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(حرف *, propdata), اشیاء_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } وإلا {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    أرجع title;
}

فراغ X11_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    کھڑکی_2 xwindow = انکڑے->xwindow;
    Display *display = انکڑے->videodata->display;
    حرف *title = کھڑکی->title ? کھڑکی->title : "";

    SDL_X11_سیٹ_کھڑکی_Title(display, xwindow, title);
}

ساكن bool caught_x11_error = false;
ساكن صحيح X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    أرجع 0;
}

ساكن فراغ X11_ExternalResizeMoveSync(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    بنانشانی صحيح بچہ_گنتی;
    کھڑکی_2 بچہ_Return_2, جڑ, ماپا;
    کھڑکی_2 *children;
    XWindow_گن attrs;
    Uint64 timeout = 0;
    صحيح x, y;
    ثابت bool send_move = !!(انکڑے->pending_operation & X11_PENDING_OP_MOVE);
    ثابت bool send_resize = !!(انکڑے->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_درخت(display, انکڑے->xwindow, &جڑ, &ماپا, &children, &بچہ_گنتی);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_منزل_NS(100);
    طالما (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_کھڑکی_گن(display, انکڑے->xwindow, &attrs);
        X11_XTranslateCoordinates(display, ماپا, Default_جڑ_کھڑکی(display),
                                  attrs.x, attrs.y, &x, &y, &بچہ_Return_2);
        SDL_Global_منزل_Relative_For_کھڑکی(کھڑکی, x, y, &x, &y);

        إذا (!caught_x11_error) {
            إذا ((انکڑے->pending_operation & X11_PENDING_OP_MOVE) && (x == انکڑے->expected.x + انکڑے->border_بایاں && y == انکڑے->expected.y + انکڑے->border_چوٹی)) {
                انکڑے->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            إذا ((انکڑے->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.چوڑائی == انکڑے->expected.w && attrs.اچائی == انکڑے->expected.h)) {
                انکڑے->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            إذا (انکڑے->pending_operation == X11_PENDING_OP_NONE) {
                اكسر;
            }
        }

        إذا (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            انکڑے->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            انکڑے->expected.x = x;
            انکڑے->expected.y = y;
            انکڑے->expected.w = attrs.چوڑائی;
            انکڑے->expected.h = attrs.اچائی;
            اكسر;
        }

        SDL_Delay(10);
    }

    إذا (!caught_x11_error) {
        إذا (send_move) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
        }
        إذا (send_resize) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, attrs.چوڑائی, attrs.اچائی);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ساكن bool X11_Sync_کھڑکی_Timeout(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Uint64 param_timeout)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    صحيح (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool نتیجہ = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    إذا (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    طالما (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        إذا ((انکڑے->pending_operation & X11_PENDING_OP_MOVE) && (کھڑکی->x == انکڑے->expected.x + انکڑے->border_بایاں && کھڑکی->y == انکڑے->expected.y + انکڑے->border_چوٹی)) {
            انکڑے->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        إذا ((انکڑے->pending_operation & X11_PENDING_OP_RESIZE) && (کھڑکی->w == انکڑے->expected.w && کھڑکی->h == انکڑے->expected.h)) {
            انکڑے->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        إذا (انکڑے->pending_operation == X11_PENDING_OP_NONE) {
            إذا (force_exit ||
                (کھڑکی->x == انکڑے->expected.x + انکڑے->border_بایاں && کھڑکی->y == انکڑے->expected.y + انکڑے->border_چوٹی &&
                 کھڑکی->w == انکڑے->expected.w && کھڑکی->h == انکڑے->expected.h)) {
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
            انکڑے->expected.x = کھڑکی->x;
            انکڑے->expected.y = کھڑکی->y;
            انکڑے->expected.w = کھڑکی->w;
            انکڑے->expected.h = کھڑکی->h;

            نتیجہ = false;
            اكسر;
        }

        SDL_Delay(10);
    }

    انکڑے->pending_operation = X11_PENDING_OP_NONE;

    إذا (!caught_x11_error) {
        X11_PumpEvents(_this);
    } وإلا {
        نتیجہ = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    أرجع نتیجہ;
}

bool X11_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom _NET_WM_ICON = انکڑے->videodata->atoms._NET_WM_ICON;
    صحيح (*prevHandler)(Display *, XErrorEvent *) = عدم;
    bool نتیجہ = true;

    إذا (icon) {
        صحيح x, y;
        صحيح propsize;
        لما *propdata;
        Uint32 *src;
        لما *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * حجم(لما));

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

        X11_XChangeProperty(display, انکڑے->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_منوال_Replace, (بنانشانی حرف *)propdata,
                            propsize);
        SDL_free(propdata);

        إذا (caught_x11_error) {
            نتیجہ = SDL_سیٹ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    إذا (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    أرجع نتیجہ;
}

فراغ X11_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی, bool use_current_position)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    ثابت صحيح rel_x = use_current_position ? کھڑکی->x : کھڑکی->pending.x;
    ثابت صحيح rel_y = use_current_position ? کھڑکی->y : کھڑکی->pending.y;

    SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی,
                                  rel_x - انکڑے->border_بایاں, rel_y - انکڑے->border_چوٹی,
                                  &انکڑے->expected.x, &انکڑے->expected.y);

    // Attempt to move the window
    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->اندرونی->pending_position = true;
    } وإلا {
        انکڑے->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_کھڑکی(display, انکڑے->xwindow, انکڑے->expected.x, انکڑے->expected.y);
    }
}

bool X11_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Sync any pending fullscreen or maximize events.
    إذا (کھڑکی->اندرونی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, کھڑکی);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    إذا (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED) {
        إذا (کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_RESTORE) {
            کھڑکی->اندرونی->pending_position = true;
        }
        أرجع true;
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            X11_ConstrainPopup(کھڑکی, true);
        }
        X11_Update_کھڑکی_Position(کھڑکی, false);
    } وإلا {
        کھڑکی->اندرونی->fs_repositioned = true;
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    أرجع true;
}

فراغ X11_سیٹ_کھڑکی_Min_Max(SDL_کھڑکی *کھڑکی, bool use_current)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_ناپ_Hints();
    لما hint_flags = 0;

    X11_XGetWMNormalHints(display, انکڑے->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_ناپ | PMax_ناپ | PAspect);

    إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
        إذا (انکڑے->کھڑکی->min_w || انکڑے->کھڑکی->min_h) {
            sizehints->flags |= PMin_ناپ;
            sizehints->min_چوڑائی_2 = انکڑے->کھڑکی->min_w;
            sizehints->min_اچائی_2 = انکڑے->کھڑکی->min_h;
        }
        إذا (انکڑے->کھڑکی->max_w || انکڑے->کھڑکی->max_h) {
            sizehints->flags |= PMax_ناپ;
            sizehints->max_چوڑائی_2 = انکڑے->کھڑکی->max_w;
            sizehints->max_اچائی_2 = انکڑے->کھڑکی->max_h;
        }
        إذا (انکڑے->کھڑکی->min_aspect > 0.0f || انکڑے->کھڑکی->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(انکڑے->کھڑکی->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(انکڑے->کھڑکی->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } وإلا {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_ناپ | PMax_ناپ;
        إذا (use_current) {
            sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : انکڑے->کھڑکی->floating.w;
            sizehints->min_اچائی_2 = sizehints->max_اچائی_2 = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : انکڑے->کھڑکی->floating.h;
        } وإلا {
            sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : انکڑے->کھڑکی->windowed.w;
            sizehints->min_اچائی_2 = sizehints->max_اچائی_2 = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : انکڑے->کھڑکی->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, انکڑے->xwindow, sizehints);
    X11_XFree(sizehints);
}

فراغ X11_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

فراغ X11_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

فراغ X11_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

فراغ X11_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    إذا (انکڑے->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, کھڑکی);
    }

    // Set the size as pending if the window is being restored.
    إذا (کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN)) {
        // New size will be set when the window is restored.
        إذا (انکڑے->pending_operation & X11_PENDING_OP_RESTORE) {
            انکڑے->pending_ناپ = true;
        } وإلا {
            // Can't resize the window.
            کھڑکی->آخری_ناپ_pending = false;
        }
        أرجع;
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_ناپ_Hints();
            لما userhints;
            صحيح dest_x, dest_y;

            X11_XGetWMNormalHints(display, انکڑے->xwindow, sizehints, &userhints);

            انکڑے->expected.w = sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->pending.w;
            انکڑے->expected.h = sizehints->min_اچائی_2 = sizehints->max_اچائی_2 = کھڑکی->pending.h;
            sizehints->flags |= PMin_ناپ | PMax_ناپ;
            انکڑے->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, انکڑے->xwindow, sizehints);

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
            X11_XResize_کھڑکی(display, انکڑے->xwindow, کھڑکی->pending.w, کھڑکی->pending.h);
            ثابت صحيح x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
            ثابت صحيح y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
            SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی,
                                          x - انکڑے->border_بایاں,
                                          y - انکڑے->border_چوٹی,
                                          &dest_x, &dest_y);
            X11_XMove_کھڑکی(display, انکڑے->xwindow, dest_x, dest_y);
            X11_XRaise_کھڑکی(display, انکڑے->xwindow);

            X11_XFree(sizehints);
        }
    } وإلا {
        انکڑے->expected.w = کھڑکی->pending.w;
        انکڑے->expected.h = کھڑکی->pending.h;
        انکڑے->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_کھڑکی(display, انکڑے->xwindow, انکڑے->expected.w, انکڑے->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
    }
}

bool X11_Get_کھڑکی_Borders_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    *بایاں = انکڑے->border_بایاں;
    *دایاں = انکڑے->border_دایاں;
    *چوٹی = انکڑے->border_چوٹی;
    *bottom = انکڑے->border_bottom;

    أرجع true;
}

bool X11_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom NET_WM_کھڑکی_OPACITY = انکڑے->videodata->atoms.NET_WM_کھڑکی_OPACITY;

    إذا (opacity == 1.0f) {
        X11_XDeleteProperty(display, انکڑے->xwindow, NET_WM_کھڑکی_OPACITY);
    } وإلا {
        ثابت Uint32 FullyOpaque = 0xFFFFFFFF;
        ثابت لما alpha = (لما)((مزدوج)opacity * (مزدوج)FullyOpaque);
        X11_XChangeProperty(display, انکڑے->xwindow, NET_WM_کھڑکی_OPACITY, XA_CARDINAL, 32,
                            Prop_منوال_Replace, (بنانشانی حرف *)&alpha, 1);
    }

    أرجع true;
}

bool X11_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_کھڑکی_انکڑے *ماپا_انکڑے = ماپا ? ماپا->اندرونی : عدم;
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    Display *display = video_انکڑے->display;

    إذا (ماپا_انکڑے) {
        X11_XSetTransientForHint(display, انکڑے->xwindow, ماپا_انکڑے->xwindow);
    } وإلا {
        X11_XDeleteProperty(display, انکڑے->xwindow, video_انکڑے->atoms.WM_TRANSIENT_FOR);
    }

    أرجع true;
}

bool X11_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = video_انکڑے->display;
    Uint32 flags = کھڑکی->flags;
    Atom _NET_WM_STATE = انکڑے->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = انکڑے->videodata->atoms._NET_WM_STATE_MODAL;

    إذا (modal) {
        flags |= SDL_کھڑکی_MODAL;
    } وإلا {
        flags &= ~SDL_کھڑکی_MODAL;
        X11_XDeleteProperty(display, انکڑے->xwindow, video_انکڑے->atoms.WM_TRANSIENT_FOR);
    }

    إذا (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_سنیہا;
        e.xclient.سنیہا_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = انکڑے->xwindow;
        e.xclient.انکڑے.l[0] = modal ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.انکڑے.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.انکڑے.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سیٹ_Net_WMState(_this, انکڑے->xwindow, flags);
    }

    X11_XFlush(display);

    أرجع true;
}

فراغ X11_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    ثابت bool focused = (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) != 0;
    ثابت bool visible = !(کھڑکی->flags & SDL_کھڑکی_HIDDEN) && !کھڑکی->is_hiding;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;
    XEvent event;

    إذا (انکڑے->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        سیٹ_کھڑکی_Bordered(display, displaydata->screen, انکڑے->xwindow, bordered);
        X11_XFlush(display);

        إذا (visible) {
            XWindow_گن attr;
            افعل {
                X11_XSync(display, False);
                X11_XGet_کھڑکی_گن(display, انکڑے->xwindow, &attr);
            } طالما (attr.map_state != IsViewable);

            إذا (focused) {
                X11_XSet_داخلہ_Focus(display, انکڑے->xwindow, Revert_منزل_ماپا, Current_ویلا);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&انکڑے->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&انکڑے->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_اقدار(انکڑے);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_کھڑکی(display, انکڑے->xwindow, کھڑکی->floating.w, کھڑکی->floating.h);
        X11_XSync(display, False);
    } وإلا {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        انکڑے->toggle_borders = true;
        انکڑے->fullscreen_borders_forced_on = false;
    }
}

فراغ X11_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

فراغ X11_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;
    Atom _NET_WM_STATE = انکڑے->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = انکڑے->videodata->atoms._NET_WM_STATE_ABOVE;

    إذا (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_سنیہا;
        e.xclient.سنیہا_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = انکڑے->xwindow;
        e.xclient.انکڑے.l[0] =
            on_چوٹی ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.انکڑے.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.انکڑے.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سیٹ_Net_WMState(_this, انکڑے->xwindow, کھڑکی->flags);
    }
    X11_XFlush(display);
}

فراغ X11_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true);
    bool سیٹ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    إذا (انکڑے->was_shown) {
        X11_PumpEvents(_this);
    }

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(کھڑکی, true);
        انکڑے->pending_position = true;
        سیٹ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (فراغ)bActivate;

    إذا (!X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        X11_XMapRaised(display, انکڑے->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&انکڑے->xwindow);
        }
        X11_XFlush(display);
        سیٹ_position = انکڑے->pending_position ||
                       (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !کھڑکی->undefined_x && !کھڑکی->undefined_y);
    }

    إذا (!انکڑے->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_داخلہ_Focus(display, انکڑے->xwindow, Revert_منزل_None, Current_ویلا);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        X11_سیٹ_Keyboard_Focus(کھڑکی, true);
    }

    // Get some valid border values, if we haven't received them yet
    إذا (انکڑے->border_بایاں == 0 && انکڑے->border_دایاں == 0 && انکڑے->border_چوٹی == 0 && انکڑے->border_bottom == 0) {
        X11_Get_Border_اقدار(انکڑے);
    }

    إذا (سیٹ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ثابت صحيح tx = (انکڑے->pending_position ? کھڑکی->pending.x : کھڑکی->x) - (انکڑے->was_shown ? 0 : انکڑے->border_بایاں);
        ثابت صحيح ty = (انکڑے->pending_position ? کھڑکی->pending.y : کھڑکی->y) - (انکڑے->was_shown ? 0 : انکڑے->border_چوٹی);
        صحيح x, y;

        SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, tx, ty, &x, &y);

        انکڑے->pending_position = false;
        X11_XMove_کھڑکی(display, انکڑے->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_کھڑکی(display, انکڑے->xwindow, کھڑکی->w, کھڑکی->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    انکڑے->ناپ_move_event_flags = X11_ناپ_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    انکڑے->ناپ_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    انکڑے->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    إذا (انکڑے->آخری_xconfigure.type) {
        صحيح x, y;
        SDL_Global_منزل_Relative_For_کھڑکی(انکڑے->کھڑکی, انکڑے->آخری_xconfigure.x, انکڑے->آخری_xconfigure.y, &x, &y);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, انکڑے->آخری_xconfigure.چوڑائی, انکڑے->آخری_xconfigure.اچائی);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
    }
}

فراغ X11_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    صحيح screen = (displaydata ? displaydata->screen : 0);
    Display *display = انکڑے->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ثابت bool is_mapped = X11_Is_کھڑکی_Mapped(_this, کھڑکی);
    X11_XWithdraw_کھڑکی(display, انکڑے->xwindow, screen);
    إذا (is_mapped && !(کھڑکی->flags & SDL_کھڑکی_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&انکڑے->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
        X11_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ساكن bool X11_سیٹ_کھڑکی_سرگرم(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_انکڑے(کھڑکی);

    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;
    Atom NET_سرگرم_کھڑکی = انکڑے->videodata->atoms.NET_سرگرم_کھڑکی;

    إذا (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_سنیہا;
        e.xclient.سنیہا_type = NET_سرگرم_کھڑکی;
        e.xclient.format = 32;
        e.xclient.کھڑکی = انکڑے->xwindow;
        e.xclient.انکڑے.l[0] = 1; // source indication. 1 = application
        e.xclient.انکڑے.l[1] = انکڑے->user_ویلا;
        e.xclient.انکڑے.l[2] = 0;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        X11_XFlush(display);
    }
    أرجع true;
}

فراغ X11_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_کھڑکی(display, انکڑے->xwindow);
    إذا (bActivate) {
        X11_سیٹ_کھڑکی_سرگرم(_this, کھڑکی);
    }
    X11_XFlush(display);
}

ساكن bool X11_سیٹ_کھڑکی_Maximized(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool maximized)
{
    CHECK_کھڑکی_انکڑے(کھڑکی);

    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;
    Atom _NET_WM_STATE = انکڑے->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = انکڑے->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = انکڑے->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        أرجع true;
    }

    إذا (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_سنیہا;
        e.xclient.سنیہا_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = انکڑے->xwindow;
        e.xclient.انکڑے.l[0] =
            maximized ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.انکڑے.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.انکڑے.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.انکڑے.l[3] = 0l;

        إذا (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی(کھڑکی);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            انکڑے->expected.x = bounds.x + انکڑے->border_بایاں;
            انکڑے->expected.y = bounds.y + انکڑے->border_چوٹی;
            انکڑے->expected.w = bounds.w - (انکڑے->border_بایاں + انکڑے->border_دایاں);
            انکڑے->expected.h = bounds.h - (انکڑے->border_چوٹی + انکڑے->border_bottom);
        } وإلا {
            انکڑے->expected.x = کھڑکی->floating.x;
            انکڑے->expected.y = کھڑکی->floating.y;
            انکڑے->expected.w = کھڑکی->floating.w;
            انکڑے->expected.h = کھڑکی->floating.h;
        }

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } وإلا {
        X11_سیٹ_Net_WMState(_this, انکڑے->xwindow, کھڑکی->flags);
    }
    X11_XFlush(display);

    أرجع true;
}

فراغ X11_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        کھڑکی->اندرونی->کھڑکی_was_maximized = true;
        أرجع;
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        کھڑکی->اندرونی->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_سیٹ_کھڑکی_Maximized(_this, کھڑکی, true);
    }
}

فراغ X11_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;

    إذا (انکڑے->pending_operation & SDL_کھڑکی_FULLSCREEN) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    انکڑے->pending_operation |= X11_PENDING_OP_MINIMIZE;
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        انکڑے->کھڑکی_was_maximized = !!(کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
    }
    X11_XIconify_کھڑکی(display, انکڑے->xwindow, displaydata->screen);
    X11_XFlush(display);
}

فراغ X11_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Don't restore the window the first time it is being shown.
    إذا (!کھڑکی->اندرونی->was_shown) {
        أرجع;
    }

    إذا (کھڑکی->اندرونی->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    إذا ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        کھڑکی->اندرونی->کھڑکی_was_maximized = false;
        أرجع;
    }

    إذا (کھڑکی->flags & (SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED) ||
        (کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        کھڑکی->اندرونی->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ثابت bool maximize = !!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED) && کھڑکی->اندرونی->کھڑکی_was_maximized;
    X11_سیٹ_کھڑکی_Maximized(_this, کھڑکی, maximize);
    X11_Show_کھڑکی(_this, کھڑکی);
    X11_سیٹ_کھڑکی_سرگرم(_this, کھڑکی);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ساكن SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen_راہیں_WM(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = _display->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom _NET_WM_STATE = انکڑے->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = انکڑے->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    إذا (!انکڑے->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        // Flush any pending fullscreen events.
        إذا (انکڑے->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_کھڑکی(_this, کھڑکی);
        }

        إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            إذا (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                أرجع SDL_FULLSCREEN_FAILED;
            } وإلا إذا (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                أرجع SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        إذا (fullscreen && !(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_ناپ_Hints();
            لما flags = 0;
            X11_XGetWMNormalHints(display, انکڑے->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ناپ | PMax_ناپ | PAspect);
            X11_XSetWMNormalHints(display, انکڑے->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_سنیہا;
        e.xclient.سنیہا_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = انکڑے->xwindow;
        e.xclient.انکڑے.l[0] =
            fullscreen ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.انکڑے.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.انکڑے.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        إذا (((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) != 0) != (fullscreen != 0)) {
            انکڑے->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        إذا (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
            SDL_copyp(&انکڑے->requested_fullscreen_منوال, &کھڑکی->current_fullscreen_منوال);
            إذا (fullscreen != !!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                انکڑے->کھڑکی_was_maximized = !!(کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
            }
            انکڑے->expected.x = displaydata->x;
            انکڑے->expected.y = displaydata->y;
            انکڑے->expected.w = _display->current_منوال->w;
            انکڑے->expected.h = _display->current_منوال->h;

            // Only move the window if it isn't already on the target display.
            إذا (!current || current != _display->id) {
                X11_XMove_کھڑکی(display, انکڑے->xwindow, displaydata->x, displaydata->y);
                انکڑے->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } وإلا {
            SDL_zero(انکڑے->requested_fullscreen_منوال);
            انکڑے->pending_position = انکڑے->fs_repositioned;
            انکڑے->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_سنیہا;
            e.xclient.سنیہا_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.کھڑکی = انکڑے->xwindow;
            إذا (انکڑے->کھڑکی_was_maximized) {
                e.xclient.انکڑے.l[0] = NET_WM_STATE_جوڑو;
            } وإلا {
                e.xclient.انکڑے.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.انکڑے.l[1] = انکڑے->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.انکڑے.l[2] = انکڑے->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.انکڑے.l[3] = 0l;
            X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                           Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
        }
    } وإلا {
        SDL_کھڑکی_Flags flags;

        flags = کھڑکی->flags;
        إذا (fullscreen) {
            flags |= SDL_کھڑکی_FULLSCREEN;
        } وإلا {
            flags &= ~SDL_کھڑکی_FULLSCREEN;
        }
        X11_سیٹ_Net_WMState(_this, انکڑے->xwindow, flags);
    }

    إذا (انکڑے->visual->class == سدھا_Color) {
        إذا (fullscreen) {
            X11_XInstallColormap(display, انکڑے->colormap);
        } وإلا {
            X11_XUninstallColormap(display, انکڑے->colormap);
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

ساكن SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = _display->اندرونی;
    Display *display = انکڑے->videodata->display;
    ثابت صحيح screen = displaydata->screen;

    إذا (!انکڑے->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    إذا (انکڑے->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
    إذا (fullscreen) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_ناپ_Hints();
            لما flags = 0;
            X11_XGetWMNormalHints(display, انکڑے->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_ناپ | PMax_ناپ | PAspect);
            X11_XSetWMNormalHints(display, انکڑے->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        سیٹ_کھڑکی_Bordered(display, screen, انکڑے->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        انکڑے->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        انکڑے->expected.x = rect.x;
        انکڑے->expected.y = rect.y;
        انکڑے->expected.w = rect.w;
        انکڑے->expected.h = rect.h;
        X11_XMove_کھڑکی(display, انکڑے->xwindow, rect.x, rect.y);
        X11_XResize_کھڑکی(display, انکڑے->xwindow, rect.w, rect.h);
        X11_XRaise_کھڑکی(display, انکڑے->xwindow);
    } وإلا {
        انکڑے->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        انکڑے->expected.x = کھڑکی->windowed.x;
        انکڑے->expected.y = کھڑکی->windowed.y;
        انکڑے->expected.w = کھڑکی->windowed.w;
        انکڑے->expected.h = کھڑکی->windowed.h;
        X11_XResize_کھڑکی(display, انکڑے->xwindow, کھڑکی->windowed.w, کھڑکی->windowed.h);
        X11_XMove_کھڑکی(display, انکڑے->xwindow, کھڑکی->windowed.x, کھڑکی->windowed.y);

        سیٹ_کھڑکی_Bordered(display, screen, انکڑے->xwindow, (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) == 0);
        X11_سیٹ_کھڑکی_Min_Max(انکڑے->کھڑکی, false);
    }

    X11_XFlush(display);

    أرجع SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_کھڑکی_انکڑے(کھڑکی);
    CHECK_DISPLAY_انکڑے(_display);

    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    إذا (انکڑے->net_wm) {
        أرجع X11_سیٹ_کھڑکی_Fullscreen_راہیں_WM(_this, کھڑکی, _display, fullscreen);
    }

    أرجع X11_سیٹ_کھڑکی_Fullscreen_Legacy(_this, کھڑکی, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

تعريفنوع بنية
{
    بنانشانی حرف *انکڑے;
    صحيح format, گنتی;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, کھڑکی_2 w, Atom prop)
{
    بنانشانی حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بنانشانی لما گنتی;
    بنانشانی لما بائٹاں_بایاں;
    صحيح بائٹاں_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کھڑکی_Property(disp, w, prop, 0, بائٹاں_fetch, False, AnyPropertyType, &type, &fmt, &گنتی, &بائٹاں_بایاں, &ret);
        بائٹاں_fetch += بائٹاں_بایاں;
    } طالما (بائٹاں_بایاں != 0);

    p->انکڑے = ret;
    p->format = fmt;
    p->گنتی = گنتی;
    p->type = type;
}

فراغ *X11_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    XWindow_گن گن;
    Atom icc_profile_atom;
    حرف icc_atom_string[حجم("_ICC_PROFILE_") + 12];
    فراغ *ret_icc_profile_انکڑے = عدم;
    CARD8 *icc_profile_انکڑے;
    صحيح real_format;
    بنانشانی لما real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_کھڑکی_گن(display, انکڑے->xwindow, &گن);
    إذا (X11_XScreen_نمبر_دا_Screen(گن.screen) > 0) {
        (فراغ)SDL_snprintf(icc_atom_string, حجم("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_نمبر_دا_Screen(گن.screen));
    } وإلا {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", حجم("_ICC_PROFILE"));
    }
    X11_XGet_کھڑکی_گن(display, جڑ_کھڑکی_دا_Screen(گن.screen), &گن);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    إذا (icc_profile_atom == None) {
        SDL_سیٹ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    X11_ReadProperty(&atomProp, display, جڑ_کھڑکی_دا_Screen(گن.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.گنتی;
    icc_profile_انکڑے = atomProp.انکڑے;
    إذا (real_format == None) {
        SDL_سیٹ_Error("Screen is not calibrated.");
        أرجع عدم;
    }

    ret_icc_profile_انکڑے = SDL_malloc(real_nitems);
    إذا (!ret_icc_profile_انکڑے) {
        أرجع عدم;
    }

    SDL_memcpy(ret_icc_profile_انکڑے, icc_profile_انکڑے, real_nitems);
    *ناپ = real_nitems;
    X11_XFree(icc_profile_انکڑے);

    أرجع ret_icc_profile_انکڑے;
}

bool X11_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display;

    إذا (!انکڑے) {
        أرجع SDL_سیٹ_Error("Invalid window data");
    }
    انکڑے->mouse_grabbed = false;
    انکڑے->pending_grab = false;

    display = انکڑے->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
            أرجع true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        إذا (انکڑے->xinput2_mouse_enabled && SDL_GetMouseState(عدم, عدم)) {
            انکڑے->pending_grab = true;
            أرجع true;
        }

        // Try to grab the mouse
        إذا (!انکڑے->videodata->broken_اشارہ_گر_grab) {
            ثابت بنانشانی صحيح نقاب = Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب | Focus_Change_نقاب;
            صحيح attempts;
            صحيح نتیجہ = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            لكل (attempts = 0; attempts < 100; attempts++) {
                نتیجہ = X11_XGrab_اشارہ_گر(display, انکڑے->xwindow, False, نقاب, Grab_منوال_Async,
                                          Grab_منوال_Async, انکڑے->xwindow, None, Current_ویلا);
                إذا (نتیجہ == GrabSuccess) {
                    انکڑے->mouse_grabbed = true;
                    اكسر;
                }
                SDL_Delay(50);
            }

            إذا (نتیجہ != GrabSuccess) {
                انکڑے->videodata->broken_اشارہ_گر_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, کھڑکی);

        // Raise the window if we grab the mouse
        X11_XRaise_کھڑکی(display, انکڑے->xwindow);
    } وإلا {
        X11_XUngrab_اشارہ_گر(display, Current_ویلا);

        X11_Xinput2UngrabTouch(_this, کھڑکی);
    }
    X11_XSync(display, False);

    إذا (!انکڑے->videodata->broken_اشارہ_گر_grab) {
        أرجع true;
    } وإلا {
        أرجع SDL_سیٹ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display;

    إذا (!انکڑے) {
        أرجع SDL_سیٹ_Error("Invalid window data");
    }

    display = انکڑے->videodata->display;

    إذا (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
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
        إذا (_this->اندرونی->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            إذا (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_سنیہا_Event client_سنیہا;
                client_سنیہا.type = Client_سنیہا;
                client_سنیہا.کھڑکی = انکڑے->xwindow;
                client_سنیہا.format = 32;
                client_سنیہا.سنیہا_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_سنیہا.انکڑے.l[0] = 1;
                client_سنیہا.انکڑے.l[1] = Current_ویلا;

                X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Notify_نقاب | Substructure_Redirect_نقاب, (XEvent *)&client_سنیہا);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, انکڑے->xwindow, True, Grab_منوال_Async,
                          Grab_منوال_Async, Current_ویلا);
    } وإلا {
        X11_XUngrabKeyboard(display, Current_ویلا);
    }
    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے) {
        SDL_Video_انکڑے *videodata = انکڑے->videodata;
        Display *display = videodata->display;
        صحيح numwindows = videodata->numwindows;
        SDL_کھڑکی_انکڑے **windowlist = videodata->windowlist;
        صحيح i;

        إذا (windowlist) {
            لكل (i = 0; i < numwindows; ++i) {
                إذا (windowlist[i] && (windowlist[i]->کھڑکی == کھڑکی)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = عدم;
                    videodata->numwindows--;
                    اكسر;
                }
            }
        }

        X11_Destroy_داخلہ_Context(انکڑے);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_رکن_Resize_Sync(کھڑکی);
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

        إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            X11_XDestroy_کھڑکی(display, انکڑے->xwindow);
            X11_XFlush(display);
        }
        SDL_free(انکڑے);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        إذا (videodata->سرگرم_cursor_confined_کھڑکی == کھڑکی) {
            X11_Destroy_اشارہ_گر_Barrier(_this, کھڑکی);
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    کھڑکی->اندرونی = عدم;
}

bool X11_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

فراغ X11_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom XdndAware = انکڑے->videodata->atoms.XdndAware;

    إذا (accept) {
        Atom xdnd_نسخہ = 5;
        X11_XChangeProperty(display, انکڑے->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_منوال_Replace, (بنانشانی حرف *)&xdnd_نسخہ, 1);
    } وإلا {
        X11_XDeleteProperty(display, انکڑے->xwindow, XdndAware);
    }
}

bool X11_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, انکڑے->xwindow);
    إذا (!wmhints) {
        أرجع SDL_سیٹ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    انکڑے->flashing_کھڑکی = false;
    انکڑے->flash_cancel_ویلا = 0;

    بدل (operation) {
    حالة SDL_FLASH_CANCEL:
        // Taken care of above
        اكسر;
    حالة SDL_FLASH_BRIEFLY:
        إذا (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            انکڑے->flashing_کھڑکی = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            انکڑے->flash_cancel_ویلا = SDL_GetTicks() + 1000;
        }
        اكسر;
    حالة SDL_FLASH_UNTIL_FOCUSED:
        إذا (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            انکڑے->flashing_کھڑکی = true;
        }
        اكسر;
    افتراضي:
        اكسر;
    }

    X11_XSetWMHints(display, انکڑے->xwindow, wmhints);
    X11_XFree(wmhints);
    أرجع true;
}

bool SDL_X11_سیٹ_کھڑکی_Title(Display *display, کھڑکی_2 xwindow, حرف *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    صحيح conv = X11_Xmb_متن_List_منزل_متن_Property(display, &title, 1, XTextStyle, &titleprop);
    حالت_2 حالت;

    إذا (X11_XSupportsLocale() != True) {
        أرجع SDL_سیٹ_Error("Current locale not supported by X server, cannot continue.");
    }

    إذا (conv == 0) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.قدر);
        // we know this can't be a locale error as we checked X locale validity
    } وإلا إذا (conv < 0) {
        أرجع SDL_باہرلا_دا_حافظہ();
    } وإلا { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        أرجع true;
    }

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    حالت = X11_Xutf8_متن_List_منزل_متن_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    إذا (حالت == Success) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.قدر);
    } وإلا {
        أرجع SDL_سیٹ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#جے_انت

    X11_XFlush(display);
    أرجع true;
}

فراغ X11_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    Display *display = انکڑے->videodata->display;
    کھڑکی_2 جڑ = جڑ_کھڑکی(display, displaydata->screen);
    XClient_سنیہا_Event e;
    کھڑکی_2 بچہ_Return_2;
    صحيح wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, انکڑے->xwindow, جڑ, x, y, &wx, &wy, &بچہ_Return_2);

    e.type = Client_سنیہا;
    e.کھڑکی = انکڑے->xwindow;
    e.سنیہا_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.انکڑے.l[0] = 0;  // GTK device ID (unused)
    e.انکڑے.l[1] = wx; // X coordinate relative to root
    e.انکڑے.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, جڑ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    إذا ((کھڑکی->flags & SDL_کھڑکی_EXTERNAL) &&
        (انکڑے->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(کھڑکی);
            أرجع true;
    }

    ثابت Uint64 current_ویلا = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->اندرونی->منوال_switch_deadline_ns &&
            current_ویلا < _this->displays[i]->اندرونی->منوال_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->اندرونی->منوال_switch_deadline_ns - current_ویلا, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += کھڑکی->اندرونی->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_منزل_NS(1000) : SDL_MS_منزل_NS(100);

    أرجع X11_Sync_کھڑکی_Timeout(_this, کھڑکی, timeout);
}

bool X11_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
        Display *display = انکڑے->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, انکڑے->xwindow);
        إذا (!wmhints) {
            أرجع SDL_سیٹ_Error("Couldn't get WM hints");
        }

        wmhints->داخلہ = focusable ? True : False;
        wmhints->flags |= داخلہ_Hint;

        X11_XSetWMHints(display, انکڑے->xwindow, wmhints);
        X11_XFree(wmhints);
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            إذا (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                X11_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کھڑکی)) {
                    X11_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        أرجع true;
    }

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_X11
