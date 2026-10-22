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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../core/unix/SDL_appid.h"

#شامل "SDL_x11video.h"
#شامل "SDL_x11mouse.h"
#شامل "SDL_x11xinput2.h"
#شامل "SDL_x11xfixes.h"

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#شامل "SDL_x11opengles.h"
#اگر_ختم

#شامل "SDL_x11xsync.h"

#تعریف_کرو _NET_WM_STATE_REMOVE 0l
#تعریف_کرو NET_WM_STATE_جوڑو    1l

#تعریف_کرو CHECK_کھڑکی_ڈیٹا(کھڑکی)                                       \
    اگر (!کھڑکی) {                                                      \
        واپس SDL_سیٹ_Error("Invalid window");                          \
    }                                                                   \
    اگر (!کھڑکی->اندرونی_2) {                                          \
        واپس SDL_سیٹ_Error("Invalid window driver data");              \
    }

#تعریف_کرو CHECK_DISPLAY_ڈیٹا(display)                                     \
    اگر (!_display) {                                                    \
        واپس SDL_سیٹ_Error("Invalid display");                         \
    }                                                                   \
    اگر (!_display->اندرونی_2) {                                        \
        واپس SDL_سیٹ_Error("Invalid display driver data");             \
    }

ساکن Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    واپس ev->type == MapNotify && ev->xmap.کھڑکی == *((کھڑکی_2 *)win);
}
ساکن Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    واپس ev->type == UnmapNotify && ev->xunmap.کھڑکی == *((کھڑکی_2 *)win);
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

ساکن bool X11_CheckCurrentDesktop(ثابت حرف *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ثابت حرف *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    اگر (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        واپس true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    اگر (desktopVar && SDL_strcasestr(desktopVar, name)) {
        واپس true;
    }

    واپس false;
}

ساکن bool X11_Is_کھڑکی_Mapped(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    XWindow_اوصاف attr;

    X11_XGet_کھڑکی_اوصاف(videodata->display, ڈیٹا->xwindow, &attr);
    اگر (attr.map_state != IsUnmapped) {
        واپس true;
    } ورنہ {
        واپس false;
    }
}

ساکن bool X11_IsDisplayOk(Display *display)
{
    اگر (display->flags & XlibDisplayIOError) {
        واپس false;
    }
    واپس true;
}

#اگر 0
ساکن bool X11_IsActionAllowed(SDL_کھڑکی *کھڑکی, Atom action)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Atom _NET_WM_ALLOWED_ACTIONS = ڈیٹا->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = ڈیٹا->videodata->display;
    صحیح form;
    غیرعلامتی طویل remain;
    غیرعلامتی طویل len, i;
    Atom *list;
    bool ret = false;

    اگر (X11_XGet_کھڑکی_Property(display, ڈیٹا->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (غیرعلامتی حرف **)&list) == Success) {
        برائے (i=0; i<len; ++i) {
            اگر (list[i] == action) {
                ret = true;
                توڑو;
            }
        }
        X11_XFree(list);
    }
    واپس ret;
}
#اگر_ختم // 0

ساکن خالی X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخری_position_pending = کھڑکی->آخری_position_pending;
    ثابت bool آخری_سائز_pending = کھڑکی->آخری_سائز_pending;

    X11_Sync_کھڑکی(_this, کھڑکی);

    کھڑکی->آخری_position_pending = آخری_position_pending;
    کھڑکی->آخری_سائز_pending = آخری_سائز_pending;
}

خالی X11_سیٹ_Net_WMState(SDL_VideoDevice *_this, کھڑکی_2 xwindow, SDL_کھڑکی_Flags flags)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
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
    صحیح گنتی = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    اگر (flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) {
        atoms[گنتی++] = _NET_WM_STATE_ABOVE;
    }
    اگر (flags & SDL_کھڑکی_UTILITY) {
        atoms[گنتی++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[گنتی++] = _NET_WM_STATE_SKIP_PAGER;
    }
    اگر (flags & SDL_کھڑکی_داخلہ_FOCUS) {
        atoms[گنتی++] = _NET_WM_STATE_FOCUSED;
    }
    اگر (flags & SDL_کھڑکی_MAXIMIZED) {
        atoms[گنتی++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[گنتی++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    اگر (flags & SDL_کھڑکی_FULLSCREEN) {
        atoms[گنتی++] = _NET_WM_STATE_FULLSCREEN;
    }
    اگر (flags & SDL_کھڑکی_MODAL) {
        atoms[گنتی++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(گنتی <= SDL_arraysize(atoms));

    اگر (گنتی > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_منوال_Replace, (غیرعلامتی حرف *)atoms, گنتی);
    } ورنہ {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

ساکن خالی X11_ConstrainPopup(SDL_کھڑکی *کھڑکی, bool output_مقصد_pending)
{
    // Clamp popup windows to the output borders
    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        صحیح abs_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->floating.x;
        صحیح abs_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->floating.y;
        صحیح انحراف_x = 0, انحراف_y = 0;

        اگر (کھڑکی->constrain_popup) {
            // Calculate the total offset from the parents
            برائے (w = کھڑکی->والد; SDL_کھڑکی_IS_POPUP(w); w = w->والد) {
                انحراف_x += w->x;
                انحراف_y += w->y;
            }

            انحراف_x += w->x;
            انحراف_y += w->y;
            abs_x += انحراف_x;
            abs_y += انحراف_y;

            displayID = SDL_Get_Display_For_کھڑکی(w);

            SDL_GetDisplayBounds(displayID, &rect);
            اگر (abs_x + کھڑکی->w > rect.x + rect.w) {
                abs_x -= (abs_x + کھڑکی->w) - (rect.x + rect.w);
            }
            اگر (abs_y + کھڑکی->h > rect.y + rect.h) {
                abs_y -= (abs_y + کھڑکی->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        اگر (output_مقصد_pending) {
            کھڑکی->pending.x = abs_x - انحراف_x;
            کھڑکی->pending.y = abs_y - انحراف_y;
        } ورنہ {
            کھڑکی->floating.x = کھڑکی->windowed.x = abs_x - انحراف_x;
            کھڑکی->floating.y = کھڑکی->windowed.y = abs_y - انحراف_y;
        }
    }
}

ساکن خالی X11_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_فعال_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the toplevel parent
    جب (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = کھڑکی;

    اگر (سیٹ_فعال_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

SDL_کھڑکی_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 xwindow)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    صحیح actualFormat;
    غیرعلامتی طویل i, عدد_اشیاء, بائٹیں_After;
    غیرعلامتی حرف *property_قدر = تہی;
    طویل max_لمبائی = 1024;
    SDL_کھڑکی_Flags flags = 0;

    اگر (X11_XGet_کھڑکی_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_لمبائی, False, XA_ATOM, &actualType,
                               &actualFormat, &عدد_اشیاء, &بائٹیں_After,
                               &property_قدر) == Success) {
        Atom *atoms = (Atom *)property_قدر;
        صحیح maximized = 0;
        صحیح fullscreen = 0;

        برائے (i = 0; i < عدد_اشیاء; ++i) {
            اگر (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_OCCLUDED;
            } ورنہ اگر (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_کھڑکی_داخلہ_FOCUS;
            } ورنہ اگر (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } ورنہ اگر (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } ورنہ اگر (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        اگر (fullscreen == 1) {
            flags |= SDL_کھڑکی_FULLSCREEN;
        } ورنہ اگر (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN);
        }

        اگر (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            اگر (fullscreen) {
                flags |= (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
            } ورنہ {
                flags |= SDL_کھڑکی_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_اوصاف attr;
            SDL_zero(attr);
            X11_XGet_کھڑکی_اوصاف(videodata->display, xwindow, &attr);
            اگر (attr.map_state == IsUnmapped) {
                flags |= SDL_کھڑکی_HIDDEN;
            }
        }
        X11_XFree(property_قدر);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    واپس flags;
}

ساکن bool تیاری_کھڑکی_ڈیٹا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 w)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    // Allocate the window data
    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }
    ڈیٹا->videodata = videodata;
    ڈیٹا->کھڑکی = کھڑکی;
    ڈیٹا->xwindow = w;
    ڈیٹا->کامیابی_test_نتیجہ = SDL_HITTEST_معمول;

    X11_Create_داخلہ_Context(ڈیٹا);

    // Associate the data with the window

    اگر (videodata->numwindows >= videodata->windowlistlength) {
        SDL_کھڑکی_ڈیٹا ** new_windowlist = (SDL_کھڑکی_ڈیٹا **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * حجم(*videodata->windowlist));
        اگر (!new_windowlist) {
            جاؤ error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_اوصاف attrib;

        X11_XGet_کھڑکی_اوصاف(ڈیٹا->videodata->display, w, &attrib);
        اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            کھڑکی->x = کھڑکی->windowed.x = کھڑکی->floating.x = attrib.x;
            کھڑکی->y = کھڑکی->windowed.y = کھڑکی->floating.y = attrib.y - ڈیٹا->border_چوٹی;
        }
        کھڑکی->w = کھڑکی->windowed.w = کھڑکی->floating.w = attrib.چوڑائی;
        کھڑکی->h = کھڑکی->windowed.h = کھڑکی->floating.h = attrib.اونچائی;
        اگر (attrib.map_state != IsUnmapped) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        } ورنہ {
            کھڑکی->flags |= SDL_کھڑکی_HIDDEN;
        }
        ڈیٹا->visual = attrib.visual;
        ڈیٹا->colormap = attrib.colormap;
    }

    کھڑکی->flags |= X11_GetNetWMState(_this, کھڑکی, w);

    {
        کھڑکی_2 Focal_کھڑکی;
        صحیح Revert_مقصد = 0;
        X11_XGet_داخلہ_Focus(ڈیٹا->videodata->display, &Focal_کھڑکی, &Revert_مقصد);
        اگر (Focal_کھڑکی == w) {
            کھڑکی->flags |= SDL_کھڑکی_داخلہ_FOCUS;
        }

        اگر (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
            SDL_سیٹ_Keyboard_Focus(ڈیٹا->کھڑکی);
        }

        اگر (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Query the title from the existing window
        کھڑکی->title = X11_Get_کھڑکی_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    صحیح screen = (displaydata ? displaydata->screen : 0);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_X11_DISPLAY_اشارہ_گر, ڈیٹا->videodata->display);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_X11_SCREEN_نمبر, screen);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_X11_کھڑکی_نمبر, ڈیٹا->xwindow);


#اگر defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    اگر ((کھڑکی->flags & SDL_کھڑکی_OPENGL) &&
        ((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_ڈیٹا || X11_GL_UseEGL(_this))
#اگر_ختم
    ) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        اگر (!_this->egl_ڈیٹا) {
            جاؤ error_cleanup;
        }

        // Create the GLES window surface
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)w);

        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            SDL_سیٹ_Error("Could not create GLES window surface");
            جاؤ error_cleanup;
        }
#ورنہ
        SDL_سیٹ_Error("Could not create GLES window surface (EGL support not configured)");
        جاؤ error_cleanup;
#اگر_ختم // SDL_VIDEO_OPENGL_EGL
    }
#اگر_ختم

    // All done!
    کھڑکی->اندرونی_2 = ڈیٹا;
    videodata->windowlist[videodata->numwindows++] = ڈیٹا;
    واپس true;

error_cleanup:
    X11_Destroy_داخلہ_Context(ڈیٹا);
    SDL_free(ڈیٹا);
    واپس false;
}

ساکن خالی تیاری_کھڑکی_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    طویل fevent = 0;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    کھڑکی_2 xwindow = ڈیٹا->xwindow;

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (SDL_X11_HAVE_UTF8 && ڈیٹا->ic) {
        X11_XGetICValues(ڈیٹا->ic, XNFilterEvents, &fevent, تہی);
    }
#اگر_ختم

    X11_Xinput2Select(_this, کھڑکی);

    {
        غیرعلامتی صحیح x11_keyboard_events = کلید_Press_نقاب | کلید_Release_نقاب;
        غیرعلامتی صحیح x11_اشارہ_گر_events = Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب;

        X11_Xinput2SelectMouseAndKeyboard(_this, کھڑکی);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        اگر (ڈیٹا->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        اگر (ڈیٹا->xinput2_mouse_enabled) {
            x11_اشارہ_گر_events = 0;
        }

        X11_XSelect_داخلہ(ڈیٹا->videodata->display, xwindow,
                         (Focus_Change_نقاب | Enter_کھڑکی_نقاب | Leave_کھڑکی_نقاب | Exposure_نقاب |
                          x11_keyboard_events | x11_اشارہ_گر_events |
                          Property_Change_نقاب | Structure_Notify_نقاب |
                          Keymap_State_نقاب | fevent));
    }
}

ساکن خالی سیٹ_کھڑکی_Bordered(Display *display, صحیح screen, کھڑکی_2 کھڑکی, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    اگر (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        ساخت
        {
            غیرعلامتی طویل flags;
            غیرعلامتی طویل functions;
            غیرعلامتی طویل decorations;
            طویل داخلہ_منوال;
            غیرعلامتی طویل حالت_2;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, کھڑکی, WM_HINTS, WM_HINTS, 32,
                            Prop_منوال_Replace, (غیرعلامتی حرف *)&MWMHints,
                            حجم(MWMHints) / حجم(طویل));
    } ورنہ { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, کھڑکی, جڑ_کھڑکی(display, screen));
    }
}

bool X11_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    کھڑکی_2 w = (کھڑکی_2)SDL_Get_نمبر_Property(create_props, SDL_PROP_کھڑکی_CREATE_X11_کھڑکی_نمبر,
                (کھڑکی_2)SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", تہی));
    اگر (w) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;

        اگر (!تیاری_کھڑکی_ڈیٹا(_this, کھڑکی, w)) {
            واپس false;
        }

        اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_کھڑکی_داخلہ, true)) {
            تیاری_کھڑکی_داخلہ(_this, کھڑکی);
        }
        واپس true;
    }

    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    اگر (!displaydata) {
        واپس SDL_سیٹ_Error("Could not find display info");
    }

    ثابت bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ثابت bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (کھڑکی->flags & SDL_کھڑکی_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_کھڑکی_ڈیٹا *windowdata;
    Display *display = ڈیٹا->display;
    صحیح screen = displaydata->screen;
    Visual *visual;
    صحیح گہرائی_2;
    XSet_کھڑکی_اوصاف xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_کھڑکی_TYPE;
    Atom wintype;
    ثابت حرف *wintype_name = تہی;
    طویل compositor = 1;
    Atom _NET_WM_PID;
    ثابت حرف *hint = تہی;
    صحیح win_x, win_y;
    bool undefined_position = false;

#اگر defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ثابت صحیح transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;
    ثابت حرف *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_کھڑکی_VISUALID);
    ثابت حرف *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    اگر (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, سانچہ;
        صحیح nvis;

        SDL_zero(سانچہ);
        سانچہ.visualid = SDL_strtol(forced_visual_id, تہی, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &سانچہ, &nvis);
        اگر (vi) {
            visual = vi->visual;
            گہرائی_2 = vi->گہرائی_2;
            X11_XFree(vi);
        } ورنہ {
            واپس false;
        }
    } ورنہ اگر ((کھڑکی->flags & SDL_کھڑکی_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = تہی;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        اگر (((_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_ڈیٹا || X11_GL_UseEGL(_this))
#اگر_ختم
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } ورنہ
#اگر_ختم
        {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#اگر_ختم
        }

        اگر (!vinfo) {
            واپس false;
        }
        visual = vinfo->visual;
        گہرائی_2 = vinfo->گہرائی_2;
        X11_XFree(vinfo);
    } ورنہ
#اگر_ختم
    {
        visual = displaydata->visual;
        گہرائی_2 = displaydata->گہرائی_2;
    }

    xattr.override_redirect = ((کھڑکی->flags & SDL_کھڑکی_TOOLTIP) || (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    اگر (visual->class == براہ_راست_Color) {
        XColor *colorcells;
        صحیح i;
        صحیح ncolors;
        صحیح rmax, gmax, bmax;
        صحیح rmask, gmask, bmask;
        صحیح rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        اگر (!xattr.colormap) {
            واپس SDL_سیٹ_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * حجم(XColor));
        اگر (!colorcells) {
            واپس false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_نقاب;
        جب (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_نقاب;
        جب (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_نقاب;
        جب (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        برائے (i = 0; i < ncolors; i++) {
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
    } ورنہ {
        xattr.colormap =
            X11_XCreateColormap(display, جڑ_کھڑکی(display, screen),
                                visual, AllocNone);
    }

    اگر (کھڑکی->undefined_x && کھڑکی->undefined_y &&
        کھڑکی->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        X11_ConstrainPopup(کھڑکی, false);
    }
    SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی,
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
                          0, گہرائی_2, داخلہ_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    اگر (!w) {
        واپس SDL_سیٹ_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    اگر (!(کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN)) {
        سیٹ_کھڑکی_Bordered(display, screen, w, !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
    }

    sizehints = X11_XAlloc_سائز_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->floating.w;
        sizehints->min_اونچائی_2 = sizehints->max_اونچائی_2 = کھڑکی->floating.h;
        sizehints->flags |= (PMax_سائز | PMin_سائز);
    }
    اگر (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->داخلہ = !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE) ? True : False;
    wmhints->کھڑکی_گروہ = ڈیٹا->کھڑکی_گروہ;
    wmhints->flags = داخلہ_Hint | کھڑکی_گروہ_Hint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (حرف *)SDL_GetExeName();
    classhints->res_class = (حرف *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, تہی, تہی, تہی, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    اگر (ڈیٹا->pid > 0) {
        طویل pid = (طویل)ڈیٹا->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_منوال_Replace,
                            (غیرعلامتی حرف *)&pid, 1);
    }

    // Set the window manager state
    X11_سیٹ_Net_WMState(_this, w, کھڑکی->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_کھڑکی_TYPE);
    اگر (کھڑکی->flags & SDL_کھڑکی_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } ورنہ اگر (hint && *hint) {
        wintype_name = hint;
    } ورنہ {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                        Prop_منوال_Replace, (غیرعلامتی حرف *)&wintype, 1);
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_منوال_Replace,
                            (غیرعلامتی حرف *)&compositor, 1);
    }

    {
        Atom protocols[4];
        صحیح proto_گنتی = 0;

        protocols[proto_گنتی++] = ڈیٹا->atoms.WM_DELETE_کھڑکی; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_گنتی++] = ڈیٹا->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        اگر (use_resize_sync) {
            protocols[proto_گنتی++] = ڈیٹا->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_گنتی <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_گنتی);
    }

    اگر (!تیاری_کھڑکی_ڈیٹا(_this, کھڑکی, w)) {
        X11_XDestroy_کھڑکی(display, w);
        واپس false;
    }
    windowdata = کھڑکی->اندرونی_2;

    // Set the parent if this is a non-popup window.
    اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی) && کھڑکی->والد) {
        X11_XSetTransientForHint(display, w, کھڑکی->والد->اندرونی_2->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(کھڑکی->pending_flags & SDL_کھڑکی_FULLSCREEN) &&
                                               !!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    اگر (use_resize_sync) {
        X11_InitResizeSync(کھڑکی);
    }
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    اگر (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_داخلہ, 0, 0, region, Shape_سیٹ);
        X11_XDestroyRegion(region);
    }
#اگر_ختم

    تیاری_کھڑکی_داخلہ(_this, کھڑکی);

    // For _ICC_PROFILE.
    X11_XSelect_داخلہ(display, جڑ_کھڑکی(display, screen), Property_Change_نقاب);

    X11_XFlush(display);

    واپس true;
}

حرف *X11_Get_کھڑکی_Title(SDL_VideoDevice *_this, کھڑکی_2 xwindow)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Display *display = ڈیٹا->display;
    صحیح حالت_2, real_format;
    Atom real_type;
    غیرعلامتی طویل اشیاء_read, اشیاء_بایاں;
    غیرعلامتی حرف *propdata;
    حرف *title = تہی;

    حالت_2 = X11_XGet_کھڑکی_Property(display, xwindow, ڈیٹا->atoms._NET_WM_NAME,
                                    0L, 8192L, False, ڈیٹا->atoms.UTF8_STRING, &real_type, &real_format,
                                    &اشیاء_read, &اشیاء_بایاں, &propdata);
    اگر (حالت_2 == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(حرف *, propdata));
        X11_XFree(propdata);
    } ورنہ {
        حالت_2 = X11_XGet_کھڑکی_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &اشیاء_read, &اشیاء_بایاں, &propdata);
        اگر (حالت_2 == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(حرف *, propdata), اشیاء_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } ورنہ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    واپس title;
}

خالی X11_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    کھڑکی_2 xwindow = ڈیٹا->xwindow;
    Display *display = ڈیٹا->videodata->display;
    حرف *title = کھڑکی->title ? کھڑکی->title : "";

    SDL_X11_سیٹ_کھڑکی_Title(display, xwindow, title);
}

ساکن bool caught_x11_error = false;
ساکن صحیح X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    واپس 0;
}

ساکن خالی X11_ExternalResizeMoveSync(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    صحیح (*پچھلا_handler)(Display *, XErrorEvent *);
    غیرعلامتی صحیح بچہ_گنتی;
    کھڑکی_2 بچہ_Return_2, جڑ, والد;
    کھڑکی_2 *children;
    XWindow_اوصاف attrs;
    Uint64 timeout = 0;
    صحیح x, y;
    ثابت bool send_move = !!(ڈیٹا->pending_operation & X11_PENDING_OP_MOVE);
    ثابت bool send_resize = !!(ڈیٹا->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_درخت(display, ڈیٹا->xwindow, &جڑ, &والد, &children, &بچہ_گنتی);
    پچھلا_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_مقصد_NS(100);
    جب (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_کھڑکی_اوصاف(display, ڈیٹا->xwindow, &attrs);
        X11_XTranslateCoordinates(display, والد, Default_جڑ_کھڑکی(display),
                                  attrs.x, attrs.y, &x, &y, &بچہ_Return_2);
        SDL_Global_مقصد_Relative_For_کھڑکی(کھڑکی, x, y, &x, &y);

        اگر (!caught_x11_error) {
            اگر ((ڈیٹا->pending_operation & X11_PENDING_OP_MOVE) && (x == ڈیٹا->expected.x + ڈیٹا->border_بایاں && y == ڈیٹا->expected.y + ڈیٹا->border_چوٹی)) {
                ڈیٹا->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            اگر ((ڈیٹا->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.چوڑائی == ڈیٹا->expected.w && attrs.اونچائی == ڈیٹا->expected.h)) {
                ڈیٹا->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            اگر (ڈیٹا->pending_operation == X11_PENDING_OP_NONE) {
                توڑو;
            }
        }

        اگر (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ڈیٹا->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            ڈیٹا->expected.x = x;
            ڈیٹا->expected.y = y;
            ڈیٹا->expected.w = attrs.چوڑائی;
            ڈیٹا->expected.h = attrs.اونچائی;
            توڑو;
        }

        SDL_Delay(10);
    }

    اگر (!caught_x11_error) {
        اگر (send_move) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
        }
        اگر (send_resize) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, attrs.چوڑائی, attrs.اونچائی);
        }
    }

    X11_XSetErrorHandler(پچھلا_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
ساکن bool X11_Sync_کھڑکی_Timeout(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Uint64 param_timeout)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    صحیح (*پچھلا_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool نتیجہ = true;

    X11_XSync(display, False);
    پچھلا_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    اگر (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    جب (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        اگر ((ڈیٹا->pending_operation & X11_PENDING_OP_MOVE) && (کھڑکی->x == ڈیٹا->expected.x + ڈیٹا->border_بایاں && کھڑکی->y == ڈیٹا->expected.y + ڈیٹا->border_چوٹی)) {
            ڈیٹا->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        اگر ((ڈیٹا->pending_operation & X11_PENDING_OP_RESIZE) && (کھڑکی->w == ڈیٹا->expected.w && کھڑکی->h == ڈیٹا->expected.h)) {
            ڈیٹا->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        اگر (ڈیٹا->pending_operation == X11_PENDING_OP_NONE) {
            اگر (force_exit ||
                (کھڑکی->x == ڈیٹا->expected.x + ڈیٹا->border_بایاں && کھڑکی->y == ڈیٹا->expected.y + ڈیٹا->border_چوٹی &&
                 کھڑکی->w == ڈیٹا->expected.w && کھڑکی->h == ڈیٹا->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                توڑو;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        اگر (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            ڈیٹا->expected.x = کھڑکی->x;
            ڈیٹا->expected.y = کھڑکی->y;
            ڈیٹا->expected.w = کھڑکی->w;
            ڈیٹا->expected.h = کھڑکی->h;

            نتیجہ = false;
            توڑو;
        }

        SDL_Delay(10);
    }

    ڈیٹا->pending_operation = X11_PENDING_OP_NONE;

    اگر (!caught_x11_error) {
        X11_PumpEvents(_this);
    } ورنہ {
        نتیجہ = false;
    }

    X11_XSetErrorHandler(پچھلا_handler);
    caught_x11_error = false;

    واپس نتیجہ;
}

bool X11_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom _NET_WM_ICON = ڈیٹا->videodata->atoms._NET_WM_ICON;
    صحیح (*پچھلا_Handler)(Display *, XErrorEvent *) = تہی;
    bool نتیجہ = true;

    اگر (icon) {
        صحیح x, y;
        صحیح propsize;
        طویل *propdata;
        Uint32 *src;
        طویل *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * حجم(طویل));

        اگر (!propdata) {
            واپس false;
        }

        X11_XSync(display, False);
        پچھلا_Handler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        برائے (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            برائے (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, ڈیٹا->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_منوال_Replace, (غیرعلامتی حرف *)propdata,
                            propsize);
        SDL_free(propdata);

        اگر (caught_x11_error) {
            نتیجہ = SDL_سیٹ_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    اگر (پچھلا_Handler) {
        X11_XSetErrorHandler(پچھلا_Handler);
        caught_x11_error = false;
    }

    واپس نتیجہ;
}

خالی X11_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی, bool use_current_position)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    ثابت صحیح rel_x = use_current_position ? کھڑکی->x : کھڑکی->pending.x;
    ثابت صحیح rel_y = use_current_position ? کھڑکی->y : کھڑکی->pending.y;

    SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی,
                                  rel_x - ڈیٹا->border_بایاں, rel_y - ڈیٹا->border_چوٹی,
                                  &ڈیٹا->expected.x, &ڈیٹا->expected.y);

    // Attempt to move the window
    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->اندرونی_2->pending_position = true;
    } ورنہ {
        ڈیٹا->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_کھڑکی(display, ڈیٹا->xwindow, ڈیٹا->expected.x, ڈیٹا->expected.y);
    }
}

bool X11_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Sync any pending fullscreen or maximize events.
    اگر (کھڑکی->اندرونی_2->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, کھڑکی);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    اگر (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED) {
        اگر (کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_RESTORE) {
            کھڑکی->اندرونی_2->pending_position = true;
        }
        واپس true;
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            X11_ConstrainPopup(کھڑکی, true);
        }
        X11_Update_کھڑکی_Position(کھڑکی, false);
    } ورنہ {
        کھڑکی->اندرونی_2->fs_repositioned = true;
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    واپس true;
}

خالی X11_سیٹ_کھڑکی_Min_Max(SDL_کھڑکی *کھڑکی, bool use_current)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_سائز_Hints();
    طویل hint_flags = 0;

    X11_XGetWMNormalHints(display, ڈیٹا->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_سائز | PMax_سائز | PAspect);

    اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
        اگر (ڈیٹا->کھڑکی->min_w || ڈیٹا->کھڑکی->min_h) {
            sizehints->flags |= PMin_سائز;
            sizehints->min_چوڑائی_2 = ڈیٹا->کھڑکی->min_w;
            sizehints->min_اونچائی_2 = ڈیٹا->کھڑکی->min_h;
        }
        اگر (ڈیٹا->کھڑکی->max_w || ڈیٹا->کھڑکی->max_h) {
            sizehints->flags |= PMax_سائز;
            sizehints->max_چوڑائی_2 = ڈیٹا->کھڑکی->max_w;
            sizehints->max_اونچائی_2 = ڈیٹا->کھڑکی->max_h;
        }
        اگر (ڈیٹا->کھڑکی->min_aspect > 0.0f || ڈیٹا->کھڑکی->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(ڈیٹا->کھڑکی->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(ڈیٹا->کھڑکی->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } ورنہ {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_سائز | PMax_سائز;
        اگر (use_current) {
            sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : ڈیٹا->کھڑکی->floating.w;
            sizehints->min_اونچائی_2 = sizehints->max_اونچائی_2 = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : ڈیٹا->کھڑکی->floating.h;
        } ورنہ {
            sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : ڈیٹا->کھڑکی->windowed.w;
            sizehints->min_اونچائی_2 = sizehints->max_اونچائی_2 = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : ڈیٹا->کھڑکی->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, ڈیٹا->xwindow, sizehints);
    X11_XFree(sizehints);
}

خالی X11_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

خالی X11_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

خالی X11_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

خالی X11_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    اگر (ڈیٹا->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, کھڑکی);
    }

    // Set the size as pending if the window is being restored.
    اگر (کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN)) {
        // New size will be set when the window is restored.
        اگر (ڈیٹا->pending_operation & X11_PENDING_OP_RESTORE) {
            ڈیٹا->pending_سائز = true;
        } ورنہ {
            // Can't resize the window.
            کھڑکی->آخری_سائز_pending = false;
        }
        واپس;
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_سائز_Hints();
            طویل userhints;
            صحیح dest_x, dest_y;

            X11_XGetWMNormalHints(display, ڈیٹا->xwindow, sizehints, &userhints);

            ڈیٹا->expected.w = sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = کھڑکی->pending.w;
            ڈیٹا->expected.h = sizehints->min_اونچائی_2 = sizehints->max_اونچائی_2 = کھڑکی->pending.h;
            sizehints->flags |= PMin_سائز | PMax_سائز;
            ڈیٹا->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, ڈیٹا->xwindow, sizehints);

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
            X11_XResize_کھڑکی(display, ڈیٹا->xwindow, کھڑکی->pending.w, کھڑکی->pending.h);
            ثابت صحیح x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
            ثابت صحیح y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
            SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی,
                                          x - ڈیٹا->border_بایاں,
                                          y - ڈیٹا->border_چوٹی,
                                          &dest_x, &dest_y);
            X11_XMove_کھڑکی(display, ڈیٹا->xwindow, dest_x, dest_y);
            X11_XRaise_کھڑکی(display, ڈیٹا->xwindow);

            X11_XFree(sizehints);
        }
    } ورنہ {
        ڈیٹا->expected.w = کھڑکی->pending.w;
        ڈیٹا->expected.h = کھڑکی->pending.h;
        ڈیٹا->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_کھڑکی(display, ڈیٹا->xwindow, ڈیٹا->expected.w, ڈیٹا->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
    }
}

bool X11_Get_کھڑکی_Borders_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    *بایاں = ڈیٹا->border_بایاں;
    *دایاں = ڈیٹا->border_دایاں;
    *چوٹی = ڈیٹا->border_چوٹی;
    *bottom = ڈیٹا->border_bottom;

    واپس true;
}

bool X11_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom NET_WM_کھڑکی_OPACITY = ڈیٹا->videodata->atoms.NET_WM_کھڑکی_OPACITY;

    اگر (opacity == 1.0f) {
        X11_XDeleteProperty(display, ڈیٹا->xwindow, NET_WM_کھڑکی_OPACITY);
    } ورنہ {
        ثابت Uint32 FullyOpaque = 0xFFFFFFFF;
        ثابت طویل alpha = (طویل)((دوہرا)opacity * (دوہرا)FullyOpaque);
        X11_XChangeProperty(display, ڈیٹا->xwindow, NET_WM_کھڑکی_OPACITY, XA_CARDINAL, 32,
                            Prop_منوال_Replace, (غیرعلامتی حرف *)&alpha, 1);
    }

    واپس true;
}

bool X11_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *والد_ڈیٹا = والد ? والد->اندرونی_2 : تہی;
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    Display *display = video_ڈیٹا->display;

    اگر (والد_ڈیٹا) {
        X11_XSetTransientForHint(display, ڈیٹا->xwindow, والد_ڈیٹا->xwindow);
    } ورنہ {
        X11_XDeleteProperty(display, ڈیٹا->xwindow, video_ڈیٹا->atoms.WM_TRANSIENT_FOR);
    }

    واپس true;
}

bool X11_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = video_ڈیٹا->display;
    Uint32 flags = کھڑکی->flags;
    Atom _NET_WM_STATE = ڈیٹا->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = ڈیٹا->videodata->atoms._NET_WM_STATE_MODAL;

    اگر (modal) {
        flags |= SDL_کھڑکی_MODAL;
    } ورنہ {
        flags &= ~SDL_کھڑکی_MODAL;
        X11_XDeleteProperty(display, ڈیٹا->xwindow, video_ڈیٹا->atoms.WM_TRANSIENT_FOR);
    }

    اگر (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = ڈیٹا->xwindow;
        e.xclient.ڈیٹا.l[0] = modal ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.ڈیٹا.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.ڈیٹا.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } ورنہ {
        X11_سیٹ_Net_WMState(_this, ڈیٹا->xwindow, flags);
    }

    X11_XFlush(display);

    واپس true;
}

خالی X11_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    ثابت bool focused = (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) != 0;
    ثابت bool visible = !(کھڑکی->flags & SDL_کھڑکی_HIDDEN) && !کھڑکی->is_hiding;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;
    XEvent event;

    اگر (ڈیٹا->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        سیٹ_کھڑکی_Bordered(display, displaydata->screen, ڈیٹا->xwindow, bordered);
        X11_XFlush(display);

        اگر (visible) {
            XWindow_اوصاف attr;
            کرو {
                X11_XSync(display, False);
                X11_XGet_کھڑکی_اوصاف(display, ڈیٹا->xwindow, &attr);
            } جب (attr.map_state != IsViewable);

            اگر (focused) {
                X11_XSet_داخلہ_Focus(display, ڈیٹا->xwindow, Revert_مقصد_والد, Current_وقت);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&ڈیٹا->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&ڈیٹا->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_اقدار(ڈیٹا);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_کھڑکی(display, ڈیٹا->xwindow, کھڑکی->floating.w, کھڑکی->floating.h);
        X11_XSync(display, False);
    } ورنہ {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        ڈیٹا->toggle_borders = true;
        ڈیٹا->fullscreen_borders_forced_on = false;
    }
}

خالی X11_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        X11_سیٹ_کھڑکی_Min_Max(کھڑکی, true);
    }
}

خالی X11_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;
    Atom _NET_WM_STATE = ڈیٹا->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = ڈیٹا->videodata->atoms._NET_WM_STATE_ABOVE;

    اگر (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = ڈیٹا->xwindow;
        e.xclient.ڈیٹا.l[0] =
            on_چوٹی ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.ڈیٹا.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.ڈیٹا.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } ورنہ {
        X11_سیٹ_Net_WMState(_this, ڈیٹا->xwindow, کھڑکی->flags);
    }
    X11_XFlush(display);
}

خالی X11_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true);
    bool سیٹ_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    اگر (ڈیٹا->was_shown) {
        X11_PumpEvents(_this);
    }

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(کھڑکی, true);
        ڈیٹا->pending_position = true;
        سیٹ_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (خالی)bActivate;

    اگر (!X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        X11_XMapRaised(display, ڈیٹا->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&ڈیٹا->xwindow);
        }
        X11_XFlush(display);
        سیٹ_position = ڈیٹا->pending_position ||
                       (!(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) && !کھڑکی->undefined_x && !کھڑکی->undefined_y);
    }

    اگر (!ڈیٹا->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_داخلہ_Focus(display, ڈیٹا->xwindow, Revert_مقصد_None, Current_وقت);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        X11_سیٹ_Keyboard_Focus(کھڑکی, true);
    }

    // Get some valid border values, if we haven't received them yet
    اگر (ڈیٹا->border_بایاں == 0 && ڈیٹا->border_دایاں == 0 && ڈیٹا->border_چوٹی == 0 && ڈیٹا->border_bottom == 0) {
        X11_Get_Border_اقدار(ڈیٹا);
    }

    اگر (سیٹ_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ثابت صحیح tx = (ڈیٹا->pending_position ? کھڑکی->pending.x : کھڑکی->x) - (ڈیٹا->was_shown ? 0 : ڈیٹا->border_بایاں);
        ثابت صحیح ty = (ڈیٹا->pending_position ? کھڑکی->pending.y : کھڑکی->y) - (ڈیٹا->was_shown ? 0 : ڈیٹا->border_چوٹی);
        صحیح x, y;

        SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, tx, ty, &x, &y);

        ڈیٹا->pending_position = false;
        X11_XMove_کھڑکی(display, ڈیٹا->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_کھڑکی(display, ڈیٹا->xwindow, کھڑکی->w, کھڑکی->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    ڈیٹا->سائز_move_event_flags = X11_سائز_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    ڈیٹا->سائز_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    ڈیٹا->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    اگر (ڈیٹا->آخری_xconfigure.type) {
        صحیح x, y;
        SDL_Global_مقصد_Relative_For_کھڑکی(ڈیٹا->کھڑکی, ڈیٹا->آخری_xconfigure.x, ڈیٹا->آخری_xconfigure.y, &x, &y);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, ڈیٹا->آخری_xconfigure.چوڑائی, ڈیٹا->آخری_xconfigure.اونچائی);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);
    }
}

خالی X11_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    صحیح screen = (displaydata ? displaydata->screen : 0);
    Display *display = ڈیٹا->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ثابت bool is_mapped = X11_Is_کھڑکی_Mapped(_this, کھڑکی);
    X11_XWithdraw_کھڑکی(display, ڈیٹا->xwindow, screen);
    اگر (is_mapped && !(کھڑکی->flags & SDL_کھڑکی_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&ڈیٹا->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
        X11_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

ساکن bool X11_سیٹ_کھڑکی_فعال(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_ڈیٹا(کھڑکی);

    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;
    Atom NET_فعال_کھڑکی = ڈیٹا->videodata->atoms.NET_فعال_کھڑکی;

    اگر (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = NET_فعال_کھڑکی;
        e.xclient.format = 32;
        e.xclient.کھڑکی = ڈیٹا->xwindow;
        e.xclient.ڈیٹا.l[0] = 1; // source indication. 1 = application
        e.xclient.ڈیٹا.l[1] = ڈیٹا->user_وقت;
        e.xclient.ڈیٹا.l[2] = 0;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        X11_XFlush(display);
    }
    واپس true;
}

خالی X11_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_کھڑکی(display, ڈیٹا->xwindow);
    اگر (bActivate) {
        X11_سیٹ_کھڑکی_فعال(_this, کھڑکی);
    }
    X11_XFlush(display);
}

ساکن bool X11_سیٹ_کھڑکی_Maximized(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool maximized)
{
    CHECK_کھڑکی_ڈیٹا(کھڑکی);

    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;
    Atom _NET_WM_STATE = ڈیٹا->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = ڈیٹا->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = ڈیٹا->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        واپس true;
    }

    اگر (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = ڈیٹا->xwindow;
        e.xclient.ڈیٹا.l[0] =
            maximized ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.ڈیٹا.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.ڈیٹا.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.ڈیٹا.l[3] = 0l;

        اگر (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی(کھڑکی);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            ڈیٹا->expected.x = bounds.x + ڈیٹا->border_بایاں;
            ڈیٹا->expected.y = bounds.y + ڈیٹا->border_چوٹی;
            ڈیٹا->expected.w = bounds.w - (ڈیٹا->border_بایاں + ڈیٹا->border_دایاں);
            ڈیٹا->expected.h = bounds.h - (ڈیٹا->border_چوٹی + ڈیٹا->border_bottom);
        } ورنہ {
            ڈیٹا->expected.x = کھڑکی->floating.x;
            ڈیٹا->expected.y = کھڑکی->floating.y;
            ڈیٹا->expected.w = کھڑکی->floating.w;
            ڈیٹا->expected.h = کھڑکی->floating.h;
        }

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
    } ورنہ {
        X11_سیٹ_Net_WMState(_this, ڈیٹا->xwindow, کھڑکی->flags);
    }
    X11_XFlush(display);

    واپس true;
}

خالی X11_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        کھڑکی->اندرونی_2->کھڑکی_was_maximized = true;
        واپس;
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        کھڑکی->اندرونی_2->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_سیٹ_کھڑکی_Maximized(_this, کھڑکی, true);
    }
}

خالی X11_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;

    اگر (ڈیٹا->pending_operation & SDL_کھڑکی_FULLSCREEN) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    ڈیٹا->pending_operation |= X11_PENDING_OP_MINIMIZE;
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        ڈیٹا->کھڑکی_was_maximized = !!(کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
    }
    X11_XIconify_کھڑکی(display, ڈیٹا->xwindow, displaydata->screen);
    X11_XFlush(display);
}

خالی X11_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Don't restore the window the first time it is being shown.
    اگر (!کھڑکی->اندرونی_2->was_shown) {
        واپس;
    }

    اگر (کھڑکی->اندرونی_2->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }

    اگر ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        کھڑکی->اندرونی_2->کھڑکی_was_maximized = false;
        واپس;
    }

    اگر (کھڑکی->flags & (SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED) ||
        (کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        کھڑکی->اندرونی_2->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ثابت bool maximize = !!(کھڑکی->flags & SDL_کھڑکی_MINIMIZED) && کھڑکی->اندرونی_2->کھڑکی_was_maximized;
    X11_سیٹ_کھڑکی_Maximized(_this, کھڑکی, maximize);
    X11_Show_کھڑکی(_this, کھڑکی);
    X11_سیٹ_کھڑکی_فعال(_this, کھڑکی);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
ساکن SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen_بذریعہ_WM(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = _display->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom _NET_WM_STATE = ڈیٹا->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = ڈیٹا->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    اگر (!ڈیٹا->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (X11_Is_کھڑکی_Mapped(_this, کھڑکی)) {
        XEvent e;

        // Flush any pending fullscreen events.
        اگر (ڈیٹا->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_کھڑکی(_this, کھڑکی);
        }

        اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            اگر (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                واپس SDL_FULLSCREEN_FAILED;
            } ورنہ اگر (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                واپس SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        اگر (fullscreen && !(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_سائز_Hints();
            طویل flags = 0;
            X11_XGetWMNormalHints(display, ڈیٹا->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_سائز | PMax_سائز | PAspect);
            X11_XSetWMNormalHints(display, ڈیٹا->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_پیغام;
        e.xclient.پیغام_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.کھڑکی = ڈیٹا->xwindow;
        e.xclient.ڈیٹا.l[0] =
            fullscreen ? NET_WM_STATE_جوڑو : _NET_WM_STATE_REMOVE;
        e.xclient.ڈیٹا.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.ڈیٹا.l[3] = 0l;

        X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                       Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        اگر (((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) != 0) != (fullscreen != 0)) {
            ڈیٹا->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        اگر (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
            SDL_copyp(&ڈیٹا->requested_fullscreen_منوال, &کھڑکی->current_fullscreen_منوال);
            اگر (fullscreen != !!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                ڈیٹا->کھڑکی_was_maximized = !!(کھڑکی->flags & SDL_کھڑکی_MAXIMIZED);
            }
            ڈیٹا->expected.x = displaydata->x;
            ڈیٹا->expected.y = displaydata->y;
            ڈیٹا->expected.w = _display->current_منوال->w;
            ڈیٹا->expected.h = _display->current_منوال->h;

            // Only move the window if it isn't already on the target display.
            اگر (!current || current != _display->id) {
                X11_XMove_کھڑکی(display, ڈیٹا->xwindow, displaydata->x, displaydata->y);
                ڈیٹا->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } ورنہ {
            SDL_zero(ڈیٹا->requested_fullscreen_منوال);
            ڈیٹا->pending_position = ڈیٹا->fs_repositioned;
            ڈیٹا->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_پیغام;
            e.xclient.پیغام_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.کھڑکی = ڈیٹا->xwindow;
            اگر (ڈیٹا->کھڑکی_was_maximized) {
                e.xclient.ڈیٹا.l[0] = NET_WM_STATE_جوڑو;
            } ورنہ {
                e.xclient.ڈیٹا.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.ڈیٹا.l[1] = ڈیٹا->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.ڈیٹا.l[2] = ڈیٹا->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.ڈیٹا.l[3] = 0l;
            X11_XSendEvent(display, جڑ_کھڑکی(display, displaydata->screen), 0,
                           Substructure_Notify_نقاب | Substructure_Redirect_نقاب, &e);
        }
    } ورنہ {
        SDL_کھڑکی_Flags flags;

        flags = کھڑکی->flags;
        اگر (fullscreen) {
            flags |= SDL_کھڑکی_FULLSCREEN;
        } ورنہ {
            flags &= ~SDL_کھڑکی_FULLSCREEN;
        }
        X11_سیٹ_Net_WMState(_this, ڈیٹا->xwindow, flags);
    }

    اگر (ڈیٹا->visual->class == براہ_راست_Color) {
        اگر (fullscreen) {
            X11_XInstallColormap(display, ڈیٹا->colormap);
        } ورنہ {
            X11_XUninstallColormap(display, ڈیٹا->colormap);
        }
    }

    واپس SDL_FULLSCREEN_PENDING;
}

ساکن SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = _display->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    ثابت صحیح screen = displaydata->screen;

    اگر (!ڈیٹا->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    اگر (ڈیٹا->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_کھڑکی(_this, کھڑکی);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
    اگر (fullscreen) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_سائز_Hints();
            طویل flags = 0;
            X11_XGetWMNormalHints(display, ڈیٹا->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_سائز | PMax_سائز | PAspect);
            X11_XSetWMNormalHints(display, ڈیٹا->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        سیٹ_کھڑکی_Bordered(display, screen, ڈیٹا->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        ڈیٹا->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ڈیٹا->expected.x = rect.x;
        ڈیٹا->expected.y = rect.y;
        ڈیٹا->expected.w = rect.w;
        ڈیٹا->expected.h = rect.h;
        X11_XMove_کھڑکی(display, ڈیٹا->xwindow, rect.x, rect.y);
        X11_XResize_کھڑکی(display, ڈیٹا->xwindow, rect.w, rect.h);
        X11_XRaise_کھڑکی(display, ڈیٹا->xwindow);
    } ورنہ {
        ڈیٹا->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        ڈیٹا->expected.x = کھڑکی->windowed.x;
        ڈیٹا->expected.y = کھڑکی->windowed.y;
        ڈیٹا->expected.w = کھڑکی->windowed.w;
        ڈیٹا->expected.h = کھڑکی->windowed.h;
        X11_XResize_کھڑکی(display, ڈیٹا->xwindow, کھڑکی->windowed.w, کھڑکی->windowed.h);
        X11_XMove_کھڑکی(display, ڈیٹا->xwindow, کھڑکی->windowed.x, کھڑکی->windowed.y);

        سیٹ_کھڑکی_Bordered(display, screen, ڈیٹا->xwindow, (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) == 0);
        X11_سیٹ_کھڑکی_Min_Max(ڈیٹا->کھڑکی, false);
    }

    X11_XFlush(display);

    واپس SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_کھڑکی_ڈیٹا(کھڑکی);
    CHECK_DISPLAY_ڈیٹا(_display);

    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (ڈیٹا->net_wm) {
        واپس X11_سیٹ_کھڑکی_Fullscreen_بذریعہ_WM(_this, کھڑکی, _display, fullscreen);
    }

    واپس X11_سیٹ_کھڑکی_Fullscreen_Legacy(_this, کھڑکی, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

قسمتعریف ساخت
{
    غیرعلامتی حرف *ڈیٹا;
    صحیح format, گنتی;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساکن خالی X11_ReadProperty(SDL_x11Prop *p, Display *disp, کھڑکی_2 w, Atom prop)
{
    غیرعلامتی حرف *ret = تہی;
    Atom type;
    صحیح fmt;
    غیرعلامتی طویل گنتی;
    غیرعلامتی طویل بائٹیں_بایاں;
    صحیح بائٹیں_fetch = 0;

    کرو {
        اگر (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کھڑکی_Property(disp, w, prop, 0, بائٹیں_fetch, False, AnyPropertyType, &type, &fmt, &گنتی, &بائٹیں_بایاں, &ret);
        بائٹیں_fetch += بائٹیں_بایاں;
    } جب (بائٹیں_بایاں != 0);

    p->ڈیٹا = ret;
    p->format = fmt;
    p->گنتی = گنتی;
    p->type = type;
}

خالی *X11_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    XWindow_اوصاف اوصاف;
    Atom icc_profile_atom;
    حرف icc_atom_string[حجم("_ICC_PROFILE_") + 12];
    خالی *ret_icc_profile_ڈیٹا = تہی;
    CARD8 *icc_profile_ڈیٹا;
    صحیح real_format;
    غیرعلامتی طویل real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_کھڑکی_اوصاف(display, ڈیٹا->xwindow, &اوصاف);
    اگر (X11_XScreen_نمبر_کا_Screen(اوصاف.screen) > 0) {
        (خالی)SDL_snprintf(icc_atom_string, حجم("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_نمبر_کا_Screen(اوصاف.screen));
    } ورنہ {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", حجم("_ICC_PROFILE"));
    }
    X11_XGet_کھڑکی_اوصاف(display, جڑ_کھڑکی_کا_Screen(اوصاف.screen), &اوصاف);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    اگر (icc_profile_atom == None) {
        SDL_سیٹ_Error("Screen is not calibrated.");
        واپس تہی;
    }

    X11_ReadProperty(&atomProp, display, جڑ_کھڑکی_کا_Screen(اوصاف.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.گنتی;
    icc_profile_ڈیٹا = atomProp.ڈیٹا;
    اگر (real_format == None) {
        SDL_سیٹ_Error("Screen is not calibrated.");
        واپس تہی;
    }

    ret_icc_profile_ڈیٹا = SDL_malloc(real_nitems);
    اگر (!ret_icc_profile_ڈیٹا) {
        واپس تہی;
    }

    SDL_memcpy(ret_icc_profile_ڈیٹا, icc_profile_ڈیٹا, real_nitems);
    *سائز = real_nitems;
    X11_XFree(icc_profile_ڈیٹا);

    واپس ret_icc_profile_ڈیٹا;
}

bool X11_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display;

    اگر (!ڈیٹا) {
        واپس SDL_سیٹ_Error("Invalid window data");
    }
    ڈیٹا->mouse_grabbed = false;
    ڈیٹا->pending_grab = false;

    display = ڈیٹا->videodata->display;

    اگر (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
            واپس true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        اگر (ڈیٹا->xinput2_mouse_enabled && SDL_GetMouseState(تہی, تہی)) {
            ڈیٹا->pending_grab = true;
            واپس true;
        }

        // Try to grab the mouse
        اگر (!ڈیٹا->videodata->broken_اشارہ_گر_grab) {
            ثابت غیرعلامتی صحیح نقاب = Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب | Focus_Change_نقاب;
            صحیح attempts;
            صحیح نتیجہ = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            برائے (attempts = 0; attempts < 100; attempts++) {
                نتیجہ = X11_XGrab_اشارہ_گر(display, ڈیٹا->xwindow, False, نقاب, Grab_منوال_Async,
                                          Grab_منوال_Async, ڈیٹا->xwindow, None, Current_وقت);
                اگر (نتیجہ == GrabSuccess) {
                    ڈیٹا->mouse_grabbed = true;
                    توڑو;
                }
                SDL_Delay(50);
            }

            اگر (نتیجہ != GrabSuccess) {
                ڈیٹا->videodata->broken_اشارہ_گر_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, کھڑکی);

        // Raise the window if we grab the mouse
        X11_XRaise_کھڑکی(display, ڈیٹا->xwindow);
    } ورنہ {
        X11_XUngrab_اشارہ_گر(display, Current_وقت);

        X11_Xinput2UngrabTouch(_this, کھڑکی);
    }
    X11_XSync(display, False);

    اگر (!ڈیٹا->videodata->broken_اشارہ_گر_grab) {
        واپس true;
    } ورنہ {
        واپس SDL_سیٹ_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display;

    اگر (!ڈیٹا) {
        واپس SDL_سیٹ_Error("Invalid window data");
    }

    display = ڈیٹا->videodata->display;

    اگر (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
            واپس true;
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
        اگر (_this->اندرونی_2->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            اگر (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_پیغام_Event client_پیغام;
                client_پیغام.type = Client_پیغام;
                client_پیغام.کھڑکی = ڈیٹا->xwindow;
                client_پیغام.format = 32;
                client_پیغام.پیغام_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_پیغام.ڈیٹا.l[0] = 1;
                client_پیغام.ڈیٹا.l[1] = Current_وقت;

                X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Notify_نقاب | Substructure_Redirect_نقاب, (XEvent *)&client_پیغام);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, ڈیٹا->xwindow, True, Grab_منوال_Async,
                          Grab_منوال_Async, Current_وقت);
    } ورنہ {
        X11_XUngrabKeyboard(display, Current_وقت);
    }
    X11_XSync(display, False);

    واپس true;
}

خالی X11_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا) {
        SDL_Video_ڈیٹا *videodata = ڈیٹا->videodata;
        Display *display = videodata->display;
        صحیح numwindows = videodata->numwindows;
        SDL_کھڑکی_ڈیٹا **windowlist = videodata->windowlist;
        صحیح i;

        اگر (windowlist) {
            برائے (i = 0; i < numwindows; ++i) {
                اگر (windowlist[i] && (windowlist[i]->کھڑکی == کھڑکی)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = تہی;
                    videodata->numwindows--;
                    توڑو;
                }
            }
        }

        X11_Destroy_داخلہ_Context(ڈیٹا);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_رکن_Resize_Sync(کھڑکی);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

        اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            X11_XDestroy_کھڑکی(display, ڈیٹا->xwindow);
            X11_XFlush(display);
        }
        SDL_free(ڈیٹا);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        اگر (videodata->فعال_cursor_confined_کھڑکی == کھڑکی) {
            X11_Destroy_اشارہ_گر_Barrier(_this, کھڑکی);
        }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    کھڑکی->اندرونی_2 = تہی;
}

bool X11_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    واپس true; // just succeed, the real work is done elsewhere.
}

خالی X11_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom XdndAware = ڈیٹا->videodata->atoms.XdndAware;

    اگر (accept) {
        Atom xdnd_نسخہ = 5;
        X11_XChangeProperty(display, ڈیٹا->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_منوال_Replace, (غیرعلامتی حرف *)&xdnd_نسخہ, 1);
    } ورنہ {
        X11_XDeleteProperty(display, ڈیٹا->xwindow, XdndAware);
    }
}

bool X11_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, ڈیٹا->xwindow);
    اگر (!wmhints) {
        واپس SDL_سیٹ_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    ڈیٹا->flashing_کھڑکی = false;
    ڈیٹا->flash_cancel_وقت = 0;

    انتخاب (operation) {
    حالت SDL_FLASH_CANCEL:
        // Taken care of above
        توڑو;
    حالت SDL_FLASH_BRIEFLY:
        اگر (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ڈیٹا->flashing_کھڑکی = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            ڈیٹا->flash_cancel_وقت = SDL_GetTicks() + 1000;
        }
        توڑو;
    حالت SDL_FLASH_UNTIL_FOCUSED:
        اگر (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            ڈیٹا->flashing_کھڑکی = true;
        }
        توڑو;
    طےشدہ:
        توڑو;
    }

    X11_XSetWMHints(display, ڈیٹا->xwindow, wmhints);
    X11_XFree(wmhints);
    واپس true;
}

bool SDL_X11_سیٹ_کھڑکی_Title(Display *display, کھڑکی_2 xwindow, حرف *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    صحیح conv = X11_Xmb_متن_List_مقصد_متن_Property(display, &title, 1, XTextStyle, &titleprop);
    حالت_3 حالت_2;

    اگر (X11_XSupportsLocale() != True) {
        واپس SDL_سیٹ_Error("Current locale not supported by X server, cannot continue.");
    }

    اگر (conv == 0) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.قدر);
        // we know this can't be a locale error as we checked X locale validity
    } ورنہ اگر (conv < 0) {
        واپس SDL_برآمد_کا_حافظہ();
    } ورنہ { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        واپس true;
    }

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    حالت_2 = X11_Xutf8_متن_List_مقصد_متن_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    اگر (حالت_2 == Success) {
        X11_XSet_متن_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.قدر);
    } ورنہ {
        واپس SDL_سیٹ_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#اگر_ختم

    X11_XFlush(display);
    واپس true;
}

خالی X11_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    Display *display = ڈیٹا->videodata->display;
    کھڑکی_2 جڑ = جڑ_کھڑکی(display, displaydata->screen);
    XClient_پیغام_Event e;
    کھڑکی_2 بچہ_Return_2;
    صحیح wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, ڈیٹا->xwindow, جڑ, x, y, &wx, &wy, &بچہ_Return_2);

    e.type = Client_پیغام;
    e.کھڑکی = ڈیٹا->xwindow;
    e.پیغام_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.ڈیٹا.l[0] = 0;  // GTK device ID (unused)
    e.ڈیٹا.l[1] = wx; // X coordinate relative to root
    e.ڈیٹا.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, جڑ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    اگر ((کھڑکی->flags & SDL_کھڑکی_EXTERNAL) &&
        (ڈیٹا->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(کھڑکی);
            واپس true;
    }

    ثابت Uint64 current_وقت = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
        اگر (_this->displays[i]->اندرونی_2->منوال_switch_deadline_ns &&
            current_وقت < _this->displays[i]->اندرونی_2->منوال_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->اندرونی_2->منوال_switch_deadline_ns - current_وقت, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += کھڑکی->اندرونی_2->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_مقصد_NS(1000) : SDL_MS_مقصد_NS(100);

    واپس X11_Sync_کھڑکی_Timeout(_this, کھڑکی, timeout);
}

bool X11_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        Display *display = ڈیٹا->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, ڈیٹا->xwindow);
        اگر (!wmhints) {
            واپس SDL_سیٹ_Error("Couldn't get WM hints");
        }

        wmhints->داخلہ = focusable ? True : False;
        wmhints->flags |= داخلہ_Hint;

        X11_XSetWMHints(display, ڈیٹا->xwindow, wmhints);
        X11_XFree(wmhints);
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            اگر (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                X11_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } ورنہ اگر (focusable) {
                اگر (SDL_ShouldFocusPopup(کھڑکی)) {
                    X11_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        واپس true;
    }

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
