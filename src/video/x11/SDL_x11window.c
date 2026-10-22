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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../core/unix/SDL_appid.h"

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11mouse.h"
#అన్తర్భావ "SDL_x11xinput2.h"
#అన్తర్భావ "SDL_x11xfixes.h"

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#అన్తర్భావ "SDL_x11opengles.h"
#అయితే_ముగింపు

#అన్తర్భావ "SDL_x11xsync.h"

#నిర్వచించు _NET_WM_STATE_REMOVE 0l
#నిర్వచించు NET_WM_STATE_కూడు    1l

#నిర్వచించు CHECK_కిటికీ_దత్తాంశం(కిటికీ)                                       \
    ఒకవేళ (!కిటికీ) {                                                      \
        తిరిగి SDL_సమితి_Error("Invalid window");                          \
    }                                                                   \
    ఒకవేళ (!కిటికీ->అంతర్గత) {                                          \
        తిరిగి SDL_సమితి_Error("Invalid window driver data");              \
    }

#నిర్వచించు CHECK_DISPLAY_దత్తాంశం(display)                                     \
    ఒకవేళ (!_display) {                                                    \
        తిరిగి SDL_సమితి_Error("Invalid display");                         \
    }                                                                   \
    ఒకవేళ (!_display->అంతర్గత) {                                        \
        తిరిగి SDL_సమితి_Error("Invalid display driver data");             \
    }

స్థిర Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    తిరిగి ev->type == MapNotify && ev->xmap.కిటికీ == *((కిటికీ_2 *)win);
}
స్థిర Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    తిరిగి ev->type == UnmapNotify && ev->xunmap.కిటికీ == *((కిటికీ_2 *)win);
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

స్థిర bool X11_CheckCurrentDesktop(స్థిరరాశి అక్షరం *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    స్థిరరాశి అక్షరం *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    ఒకవేళ (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        తిరిగి true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    ఒకవేళ (desktopVar && SDL_strcasestr(desktopVar, name)) {
        తిరిగి true;
    }

    తిరిగి false;
}

స్థిర bool X11_Is_కిటికీ_Mapped(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    XWindow_లక్షణాలు attr;

    X11_XGet_కిటికీ_లక్షణాలు(videodata->display, దత్తాంశం->xwindow, &attr);
    ఒకవేళ (attr.map_state != IsUnmapped) {
        తిరిగి true;
    } లేకపోతే {
        తిరిగి false;
    }
}

స్థిర bool X11_IsDisplayOk(Display *display)
{
    ఒకవేళ (display->flags & XlibDisplayIOError) {
        తిరిగి false;
    }
    తిరిగి true;
}

#ఒకవేళ 0
స్థిర bool X11_IsActionAllowed(SDL_కిటికీ *కిటికీ, Atom action)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Atom _NET_WM_ALLOWED_ACTIONS = దత్తాంశం->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = దత్తాంశం->videodata->display;
    పూర్ణాంకం form;
    గుర్తులేని దీర్ఘ remain;
    గుర్తులేని దీర్ఘ len, i;
    Atom *list;
    bool ret = false;

    ఒకవేళ (X11_XGet_కిటికీ_Property(display, దత్తాంశం->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (గుర్తులేని అక్షరం **)&list) == Success) {
        కొరకు (i=0; i<len; ++i) {
            ఒకవేళ (list[i] == action) {
                ret = true;
                ఆపు;
            }
        }
        X11_XFree(list);
    }
    తిరిగి ret;
}
#అయితే_ముగింపు // 0

స్థిర శూన్య X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    స్థిరరాశి bool చివరి_position_pending = కిటికీ->చివరి_position_pending;
    స్థిరరాశి bool చివరి_కొలత_pending = కిటికీ->చివరి_కొలత_pending;

    X11_Sync_కిటికీ(_this, కిటికీ);

    కిటికీ->చివరి_position_pending = చివరి_position_pending;
    కిటికీ->చివరి_కొలత_pending = చివరి_కొలత_pending;
}

శూన్య X11_సమితి_Net_WMState(SDL_VideoDevice *_this, కిటికీ_2 xwindow, SDL_కిటికీ_Flags flags)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
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
    పూర్ణాంకం లెక్క = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    ఒకవేళ (flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం) {
        atoms[లెక్క++] = _NET_WM_STATE_ABOVE;
    }
    ఒకవేళ (flags & SDL_కిటికీ_UTILITY) {
        atoms[లెక్క++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[లెక్క++] = _NET_WM_STATE_SKIP_PAGER;
    }
    ఒకవేళ (flags & SDL_కిటికీ_ఆదానం_FOCUS) {
        atoms[లెక్క++] = _NET_WM_STATE_FOCUSED;
    }
    ఒకవేళ (flags & SDL_కిటికీ_MAXIMIZED) {
        atoms[లెక్క++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[లెక్క++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    ఒకవేళ (flags & SDL_కిటికీ_FULLSCREEN) {
        atoms[లెక్క++] = _NET_WM_STATE_FULLSCREEN;
    }
    ఒకవేళ (flags & SDL_కిటికీ_MODAL) {
        atoms[లెక్క++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(లెక్క <= SDL_arraysize(atoms));

    ఒకవేళ (లెక్క > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)atoms, లెక్క);
    } లేకపోతే {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

స్థిర శూన్య X11_ConstrainPopup(SDL_కిటికీ *కిటికీ, bool output_గమ్యం_pending)
{
    // Clamp popup windows to the output borders
    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        SDL_కిటికీ *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        పూర్ణాంకం abs_x = కిటికీ->చివరి_position_pending ? కిటికీ->pending.x : కిటికీ->floating.x;
        పూర్ణాంకం abs_y = కిటికీ->చివరి_position_pending ? కిటికీ->pending.y : కిటికీ->floating.y;
        పూర్ణాంకం స్థానభ్రంశం_x = 0, స్థానభ్రంశం_y = 0;

        ఒకవేళ (కిటికీ->constrain_popup) {
            // Calculate the total offset from the parents
            కొరకు (w = కిటికీ->మాతృ; SDL_కిటికీ_IS_POPUP(w); w = w->మాతృ) {
                స్థానభ్రంశం_x += w->x;
                స్థానభ్రంశం_y += w->y;
            }

            స్థానభ్రంశం_x += w->x;
            స్థానభ్రంశం_y += w->y;
            abs_x += స్థానభ్రంశం_x;
            abs_y += స్థానభ్రంశం_y;

            displayID = SDL_Get_Display_For_కిటికీ(w);

            SDL_GetDisplayBounds(displayID, &rect);
            ఒకవేళ (abs_x + కిటికీ->w > rect.x + rect.w) {
                abs_x -= (abs_x + కిటికీ->w) - (rect.x + rect.w);
            }
            ఒకవేళ (abs_y + కిటికీ->h > rect.y + rect.h) {
                abs_y -= (abs_y + కిటికీ->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        ఒకవేళ (output_గమ్యం_pending) {
            కిటికీ->pending.x = abs_x - స్థానభ్రంశం_x;
            కిటికీ->pending.y = abs_y - స్థానభ్రంశం_y;
        } లేకపోతే {
            కిటికీ->floating.x = కిటికీ->windowed.x = abs_x - స్థానభ్రంశం_x;
            కిటికీ->floating.y = కిటికీ->windowed.y = abs_y - స్థానభ్రంశం_y;
        }
    }
}

స్థిర శూన్య X11_సమితి_Keyboard_Focus(SDL_కిటికీ *కిటికీ, bool సమితి_చురుకైన_focus)
{
    SDL_కిటికీ *toplevel = కిటికీ;

    // Find the toplevel parent
    అయితే (SDL_కిటికీ_IS_POPUP(toplevel)) {
        toplevel = toplevel->మాతృ;
    }

    toplevel->keyboard_focus = కిటికీ;

    ఒకవేళ (సమితి_చురుకైన_focus && !కిటికీ->is_hiding && !కిటికీ->is_destroying) {
        SDL_సమితి_Keyboard_Focus(కిటికీ);
    }
}

SDL_కిటికీ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, కిటికీ_2 xwindow)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    పూర్ణాంకం actualFormat;
    గుర్తులేని దీర్ఘ i, అంకె_వస్తువులు, బైట్లు_After;
    గుర్తులేని అక్షరం *property_విలువ = ఖాళీ;
    దీర్ఘ max_నిడివి = 1024;
    SDL_కిటికీ_Flags flags = 0;

    ఒకవేళ (X11_XGet_కిటికీ_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_నిడివి, False, XA_ATOM, &actualType,
                               &actualFormat, &అంకె_వస్తువులు, &బైట్లు_After,
                               &property_విలువ) == Success) {
        Atom *atoms = (Atom *)property_విలువ;
        పూర్ణాంకం maximized = 0;
        పూర్ణాంకం fullscreen = 0;

        కొరకు (i = 0; i < అంకె_వస్తువులు; ++i) {
            ఒకవేళ (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_OCCLUDED;
            } లేకపోతే ఒకవేళ (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_కిటికీ_ఆదానం_FOCUS;
            } లేకపోతే ఒకవేళ (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } లేకపోతే ఒకవేళ (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } లేకపోతే ఒకవేళ (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        ఒకవేళ (fullscreen == 1) {
            flags |= SDL_కిటికీ_FULLSCREEN;
        } లేకపోతే ఒకవేళ (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN);
        }

        ఒకవేళ (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            ఒకవేళ (fullscreen) {
                flags |= (కిటికీ->flags & SDL_కిటికీ_MAXIMIZED);
            } లేకపోతే {
                flags |= SDL_కిటికీ_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_లక్షణాలు attr;
            SDL_zero(attr);
            X11_XGet_కిటికీ_లక్షణాలు(videodata->display, xwindow, &attr);
            ఒకవేళ (attr.map_state == IsUnmapped) {
                flags |= SDL_కిటికీ_HIDDEN;
            }
        }
        X11_XFree(property_విలువ);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    తిరిగి flags;
}

స్థిర bool అమరిక_కిటికీ_దత్తాంశం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, కిటికీ_2 w)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    // Allocate the window data
    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }
    దత్తాంశం->videodata = videodata;
    దత్తాంశం->కిటికీ = కిటికీ;
    దత్తాంశం->xwindow = w;
    దత్తాంశం->తగిలింది_test_ఫలితం = SDL_HITTEST_సాధారణ;

    X11_Create_ఆదానం_Context(దత్తాంశం);

    // Associate the data with the window

    ఒకవేళ (videodata->numwindows >= videodata->windowlistlength) {
        SDL_కిటికీ_దత్తాంశం ** new_windowlist = (SDL_కిటికీ_దత్తాంశం **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * పరిమాణం(*videodata->windowlist));
        ఒకవేళ (!new_windowlist) {
            వెళ్ళు error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_లక్షణాలు attrib;

        X11_XGet_కిటికీ_లక్షణాలు(దత్తాంశం->videodata->display, w, &attrib);
        ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ)) {
            కిటికీ->x = కిటికీ->windowed.x = కిటికీ->floating.x = attrib.x;
            కిటికీ->y = కిటికీ->windowed.y = కిటికీ->floating.y = attrib.y - దత్తాంశం->border_శిఖరం;
        }
        కిటికీ->w = కిటికీ->windowed.w = కిటికీ->floating.w = attrib.వెడల్పు;
        కిటికీ->h = కిటికీ->windowed.h = కిటికీ->floating.h = attrib.ఎత్తు;
        ఒకవేళ (attrib.map_state != IsUnmapped) {
            కిటికీ->flags &= ~SDL_కిటికీ_HIDDEN;
        } లేకపోతే {
            కిటికీ->flags |= SDL_కిటికీ_HIDDEN;
        }
        దత్తాంశం->visual = attrib.visual;
        దత్తాంశం->colormap = attrib.colormap;
    }

    కిటికీ->flags |= X11_GetNetWMState(_this, కిటికీ, w);

    {
        కిటికీ_2 Focal_కిటికీ;
        పూర్ణాంకం Revert_గమ్యం = 0;
        X11_XGet_ఆదానం_Focus(దత్తాంశం->videodata->display, &Focal_కిటికీ, &Revert_గమ్యం);
        ఒకవేళ (Focal_కిటికీ == w) {
            కిటికీ->flags |= SDL_కిటికీ_ఆదానం_FOCUS;
        }

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
            SDL_సమితి_Keyboard_Focus(దత్తాంశం->కిటికీ);
        }

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
        // Query the title from the existing window
        కిటికీ->title = X11_Get_కిటికీ_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    పూర్ణాంకం screen = (displaydata ? displaydata->screen : 0);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_X11_DISPLAY_సూచిక, దత్తాంశం->videodata->display);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_X11_SCREEN_సంఖ్య, screen);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_X11_కిటికీ_సంఖ్య, దత్తాంశం->xwindow);


#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_OPENGL) &&
        ((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_దత్తాంశం || X11_GL_UseEGL(_this))
#అయితే_ముగింపు
    ) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (!_this->egl_దత్తాంశం) {
            వెళ్ళు error_cleanup;
        }

        // Create the GLES window surface
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)w);

        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            SDL_సమితి_Error("Could not create GLES window surface");
            వెళ్ళు error_cleanup;
        }
#లేకపోతే
        SDL_సమితి_Error("Could not create GLES window surface (EGL support not configured)");
        వెళ్ళు error_cleanup;
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_EGL
    }
#అయితే_ముగింపు

    // All done!
    కిటికీ->అంతర్గత = దత్తాంశం;
    videodata->windowlist[videodata->numwindows++] = దత్తాంశం;
    తిరిగి true;

error_cleanup:
    X11_Destroy_ఆదానం_Context(దత్తాంశం);
    SDL_free(దత్తాంశం);
    తిరిగి false;
}

స్థిర శూన్య అమరిక_కిటికీ_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    దీర్ఘ fevent = 0;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    కిటికీ_2 xwindow = దత్తాంశం->xwindow;

#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (SDL_X11_HAVE_UTF8 && దత్తాంశం->ic) {
        X11_XGetICValues(దత్తాంశం->ic, XNFilterEvents, &fevent, ఖాళీ);
    }
#అయితే_ముగింపు

    X11_Xinput2Select(_this, కిటికీ);

    {
        గుర్తులేని పూర్ణాంకం x11_keyboard_events = కీలకం_Press_ముసుగు | కీలకం_Release_ముసుగు;
        గుర్తులేని పూర్ణాంకం x11_సూచిక_events = Button_Press_ముసుగు | Button_Release_ముసుగు | సూచిక_Motion_ముసుగు;

        X11_Xinput2SelectMouseAndKeyboard(_this, కిటికీ);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        ఒకవేళ (దత్తాంశం->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        ఒకవేళ (దత్తాంశం->xinput2_mouse_enabled) {
            x11_సూచిక_events = 0;
        }

        X11_XSelect_ఆదానం(దత్తాంశం->videodata->display, xwindow,
                         (Focus_Change_ముసుగు | Enter_కిటికీ_ముసుగు | Leave_కిటికీ_ముసుగు | Exposure_ముసుగు |
                          x11_keyboard_events | x11_సూచిక_events |
                          Property_Change_ముసుగు | Structure_Notify_ముసుగు |
                          Keymap_State_ముసుగు | fevent));
    }
}

స్థిర శూన్య సమితి_కిటికీ_Bordered(Display *display, పూర్ణాంకం screen, కిటికీ_2 కిటికీ, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    ఒకవేళ (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        నిర్మాణం
        {
            గుర్తులేని దీర్ఘ flags;
            గుర్తులేని దీర్ఘ functions;
            గుర్తులేని దీర్ఘ decorations;
            దీర్ఘ ఆదానం_బహుళకం;
            గుర్తులేని దీర్ఘ స్థితి_2;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, కిటికీ, WM_HINTS, WM_HINTS, 32,
                            Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)&MWMHints,
                            పరిమాణం(MWMHints) / పరిమాణం(దీర్ఘ));
    } లేకపోతే { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, కిటికీ, మూలం_కిటికీ(display, screen));
    }
}

bool X11_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    కిటికీ_2 w = (కిటికీ_2)SDL_Get_సంఖ్య_Property(create_props, SDL_PROP_కిటికీ_CREATE_X11_కిటికీ_సంఖ్య,
                (కిటికీ_2)SDL_Get_సూచిక_Property(create_props, "sdl2-compat.external_window", ఖాళీ));
    ఒకవేళ (w) {
        కిటికీ->flags |= SDL_కిటికీ_EXTERNAL;

        ఒకవేళ (!అమరిక_కిటికీ_దత్తాంశం(_this, కిటికీ, w)) {
            తిరిగి false;
        }

        ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_కిటికీ_ఆదానం, true)) {
            అమరిక_కిటికీ_ఆదానం(_this, కిటికీ);
        }
        తిరిగి true;
    }

    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    ఒకవేళ (!displaydata) {
        తిరిగి SDL_సమితి_Error("Could not find display info");
    }

    స్థిరరాశి bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    స్థిరరాశి bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (కిటికీ->flags & SDL_కిటికీ_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_కిటికీ_దత్తాంశం *windowdata;
    Display *display = దత్తాంశం->display;
    పూర్ణాంకం screen = displaydata->screen;
    Visual *visual;
    పూర్ణాంకం లోతు_2;
    XSet_కిటికీ_లక్షణాలు xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_కిటికీ_TYPE;
    Atom wintype;
    స్థిరరాశి అక్షరం *wintype_name = ఖాళీ;
    దీర్ఘ compositor = 1;
    Atom _NET_WM_PID;
    స్థిరరాశి అక్షరం *hint = ఖాళీ;
    పూర్ణాంకం win_x, win_y;
    bool undefined_position = false;

#ఒకవేళ defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    స్థిరరాశి పూర్ణాంకం transparent = (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) ? true : false;
    స్థిరరాశి అక్షరం *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_కిటికీ_VISUALID);
    స్థిరరాశి అక్షరం *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    ఒకవేళ (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, మూస;
        పూర్ణాంకం nvis;

        SDL_zero(మూస);
        మూస.visualid = SDL_strtol(forced_visual_id, ఖాళీ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &మూస, &nvis);
        ఒకవేళ (vi) {
            visual = vi->visual;
            లోతు_2 = vi->లోతు_2;
            X11_XFree(vi);
        } లేకపోతే {
            తిరిగి false;
        }
    } లేకపోతే ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = ఖాళీ;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (((_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_దత్తాంశం || X11_GL_UseEGL(_this))
#అయితే_ముగింపు
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } లేకపోతే
#అయితే_ముగింపు
        {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#అయితే_ముగింపు
        }

        ఒకవేళ (!vinfo) {
            తిరిగి false;
        }
        visual = vinfo->visual;
        లోతు_2 = vinfo->లోతు_2;
        X11_XFree(vinfo);
    } లేకపోతే
#అయితే_ముగింపు
    {
        visual = displaydata->visual;
        లోతు_2 = displaydata->లోతు_2;
    }

    xattr.override_redirect = ((కిటికీ->flags & SDL_కిటికీ_TOOLTIP) || (కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    ఒకవేళ (visual->class == ప్రత్యక్ష_Color) {
        XColor *colorcells;
        పూర్ణాంకం i;
        పూర్ణాంకం ncolors;
        పూర్ణాంకం rmax, gmax, bmax;
        పూర్ణాంకం rmask, gmask, bmask;
        పూర్ణాంకం rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, మూలం_కిటికీ(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        ఒకవేళ (!xattr.colormap) {
            తిరిగి SDL_సమితి_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * పరిమాణం(XColor));
        ఒకవేళ (!colorcells) {
            తిరిగి false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_ముసుగు;
        అయితే (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_ముసుగు;
        అయితే (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_ముసుగు;
        అయితే (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        కొరకు (i = 0; i < ncolors; i++) {
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
    } లేకపోతే {
        xattr.colormap =
            X11_XCreateColormap(display, మూలం_కిటికీ(display, screen),
                                visual, AllocNone);
    }

    ఒకవేళ (కిటికీ->undefined_x && కిటికీ->undefined_y &&
        కిటికీ->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        X11_ConstrainPopup(కిటికీ, false);
    }
    SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ,
                                  కిటికీ->floating.x, కిటికీ->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_కిటికీ(display, మూలం_కిటికీ(display, screen),
                          win_x, win_y, కిటికీ->floating.w, కిటికీ->floating.h,
                          0, లోతు_2, ఆదానం_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    ఒకవేళ (!w) {
        తిరిగి SDL_సమితి_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    ఒకవేళ (!(కిటికీ->pending_flags & SDL_కిటికీ_FULLSCREEN)) {
        సమితి_కిటికీ_Bordered(display, screen, w, !(కిటికీ->flags & SDL_కిటికీ_BORDERLESS));
    }

    sizehints = X11_XAlloc_కొలత_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
        sizehints->min_వెడల్పు_2 = sizehints->max_వెడల్పు_2 = కిటికీ->floating.w;
        sizehints->min_ఎత్తు_2 = sizehints->max_ఎత్తు_2 = కిటికీ->floating.h;
        sizehints->flags |= (PMax_కొలత | PMin_కొలత);
    }
    ఒకవేళ (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->ఆదానం = !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE) ? True : False;
    wmhints->కిటికీ_సమూహం = దత్తాంశం->కిటికీ_సమూహం;
    wmhints->flags = ఆదానం_Hint | కిటికీ_సమూహం_Hint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (అక్షరం *)SDL_GetExeName();
    classhints->res_class = (అక్షరం *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, ఖాళీ, ఖాళీ, ఖాళీ, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    ఒకవేళ (దత్తాంశం->pid > 0) {
        దీర్ఘ pid = (దీర్ఘ)దత్తాంశం->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_బహుళకం_Replace,
                            (గుర్తులేని అక్షరం *)&pid, 1);
    }

    // Set the window manager state
    X11_సమితి_Net_WMState(_this, w, కిటికీ->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_కిటికీ_TYPE);
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } లేకపోతే ఒకవేళ (hint && *hint) {
        wintype_name = hint;
    } లేకపోతే {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_కిటికీ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_కిటికీ_TYPE, XA_ATOM, 32,
                        Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)&wintype, 1);
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_బహుళకం_Replace,
                            (గుర్తులేని అక్షరం *)&compositor, 1);
    }

    {
        Atom protocols[4];
        పూర్ణాంకం proto_లెక్క = 0;

        protocols[proto_లెక్క++] = దత్తాంశం->atoms.WM_DELETE_కిటికీ; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_లెక్క++] = దత్తాంశం->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
        ఒకవేళ (use_resize_sync) {
            protocols[proto_లెక్క++] = దత్తాంశం->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_లెక్క <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_లెక్క);
    }

    ఒకవేళ (!అమరిక_కిటికీ_దత్తాంశం(_this, కిటికీ, w)) {
        X11_XDestroy_కిటికీ(display, w);
        తిరిగి false;
    }
    windowdata = కిటికీ->అంతర్గత;

    // Set the parent if this is a non-popup window.
    ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ) && కిటికీ->మాతృ) {
        X11_XSetTransientForHint(display, w, కిటికీ->మాతృ->అంతర్గత->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(కిటికీ->pending_flags & SDL_కిటికీ_FULLSCREEN) &&
                                               !!(కిటికీ->flags & SDL_కిటికీ_BORDERLESS);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    ఒకవేళ (use_resize_sync) {
        X11_InitResizeSync(కిటికీ);
    }
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_ఆదానం, 0, 0, region, Shape_సమితి);
        X11_XDestroyRegion(region);
    }
#అయితే_ముగింపు

    అమరిక_కిటికీ_ఆదానం(_this, కిటికీ);

    // For _ICC_PROFILE.
    X11_XSelect_ఆదానం(display, మూలం_కిటికీ(display, screen), Property_Change_ముసుగు);

    X11_XFlush(display);

    తిరిగి true;
}

అక్షరం *X11_Get_కిటికీ_Title(SDL_VideoDevice *_this, కిటికీ_2 xwindow)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *display = దత్తాంశం->display;
    పూర్ణాంకం స్థితి_2, real_format;
    Atom real_type;
    గుర్తులేని దీర్ఘ వస్తువులు_read, వస్తువులు_ఎడమ;
    గుర్తులేని అక్షరం *propdata;
    అక్షరం *title = ఖాళీ;

    స్థితి_2 = X11_XGet_కిటికీ_Property(display, xwindow, దత్తాంశం->atoms._NET_WM_NAME,
                                    0L, 8192L, False, దత్తాంశం->atoms.UTF8_STRING, &real_type, &real_format,
                                    &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
    ఒకవేళ (స్థితి_2 == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(అక్షరం *, propdata));
        X11_XFree(propdata);
    } లేకపోతే {
        స్థితి_2 = X11_XGet_కిటికీ_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
        ఒకవేళ (స్థితి_2 == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(అక్షరం *, propdata), వస్తువులు_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } లేకపోతే {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    తిరిగి title;
}

శూన్య X11_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    కిటికీ_2 xwindow = దత్తాంశం->xwindow;
    Display *display = దత్తాంశం->videodata->display;
    అక్షరం *title = కిటికీ->title ? కిటికీ->title : "";

    SDL_X11_సమితి_కిటికీ_Title(display, xwindow, title);
}

స్థిర bool caught_x11_error = false;
స్థిర పూర్ణాంకం X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    తిరిగి 0;
}

స్థిర శూన్య X11_ExternalResizeMoveSync(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    పూర్ణాంకం (*prev_handler)(Display *, XErrorEvent *);
    గుర్తులేని పూర్ణాంకం బిడ్డ_లెక్క;
    కిటికీ_2 బిడ్డ_Return_2, మూలం, మాతృ;
    కిటికీ_2 *children;
    XWindow_లక్షణాలు attrs;
    Uint64 timeout = 0;
    పూర్ణాంకం x, y;
    స్థిరరాశి bool send_move = !!(దత్తాంశం->pending_operation & X11_PENDING_OP_MOVE);
    స్థిరరాశి bool send_resize = !!(దత్తాంశం->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_వృక్షం(display, దత్తాంశం->xwindow, &మూలం, &మాతృ, &children, &బిడ్డ_లెక్క);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_గమ్యం_NS(100);
    అయితే (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_కిటికీ_లక్షణాలు(display, దత్తాంశం->xwindow, &attrs);
        X11_XTranslateCoordinates(display, మాతృ, Default_మూలం_కిటికీ(display),
                                  attrs.x, attrs.y, &x, &y, &బిడ్డ_Return_2);
        SDL_Global_గమ్యం_Relative_For_కిటికీ(కిటికీ, x, y, &x, &y);

        ఒకవేళ (!caught_x11_error) {
            ఒకవేళ ((దత్తాంశం->pending_operation & X11_PENDING_OP_MOVE) && (x == దత్తాంశం->expected.x + దత్తాంశం->border_ఎడమ && y == దత్తాంశం->expected.y + దత్తాంశం->border_శిఖరం)) {
                దత్తాంశం->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            ఒకవేళ ((దత్తాంశం->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.వెడల్పు == దత్తాంశం->expected.w && attrs.ఎత్తు == దత్తాంశం->expected.h)) {
                దత్తాంశం->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            ఒకవేళ (దత్తాంశం->pending_operation == X11_PENDING_OP_NONE) {
                ఆపు;
            }
        }

        ఒకవేళ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            దత్తాంశం->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            దత్తాంశం->expected.x = x;
            దత్తాంశం->expected.y = y;
            దత్తాంశం->expected.w = attrs.వెడల్పు;
            దత్తాంశం->expected.h = attrs.ఎత్తు;
            ఆపు;
        }

        SDL_Delay(10);
    }

    ఒకవేళ (!caught_x11_error) {
        ఒకవేళ (send_move) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, x, y);
        }
        ఒకవేళ (send_resize) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, attrs.వెడల్పు, attrs.ఎత్తు);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
స్థిర bool X11_Sync_కిటికీ_Timeout(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, Uint64 param_timeout)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    పూర్ణాంకం (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool ఫలితం = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    ఒకవేళ (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    అయితే (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        ఒకవేళ ((దత్తాంశం->pending_operation & X11_PENDING_OP_MOVE) && (కిటికీ->x == దత్తాంశం->expected.x + దత్తాంశం->border_ఎడమ && కిటికీ->y == దత్తాంశం->expected.y + దత్తాంశం->border_శిఖరం)) {
            దత్తాంశం->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        ఒకవేళ ((దత్తాంశం->pending_operation & X11_PENDING_OP_RESIZE) && (కిటికీ->w == దత్తాంశం->expected.w && కిటికీ->h == దత్తాంశం->expected.h)) {
            దత్తాంశం->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        ఒకవేళ (దత్తాంశం->pending_operation == X11_PENDING_OP_NONE) {
            ఒకవేళ (force_exit ||
                (కిటికీ->x == దత్తాంశం->expected.x + దత్తాంశం->border_ఎడమ && కిటికీ->y == దత్తాంశం->expected.y + దత్తాంశం->border_శిఖరం &&
                 కిటికీ->w == దత్తాంశం->expected.w && కిటికీ->h == దత్తాంశం->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                ఆపు;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        ఒకవేళ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            దత్తాంశం->expected.x = కిటికీ->x;
            దత్తాంశం->expected.y = కిటికీ->y;
            దత్తాంశం->expected.w = కిటికీ->w;
            దత్తాంశం->expected.h = కిటికీ->h;

            ఫలితం = false;
            ఆపు;
        }

        SDL_Delay(10);
    }

    దత్తాంశం->pending_operation = X11_PENDING_OP_NONE;

    ఒకవేళ (!caught_x11_error) {
        X11_PumpEvents(_this);
    } లేకపోతే {
        ఫలితం = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    తిరిగి ఫలితం;
}

bool X11_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom _NET_WM_ICON = దత్తాంశం->videodata->atoms._NET_WM_ICON;
    పూర్ణాంకం (*prevHandler)(Display *, XErrorEvent *) = ఖాళీ;
    bool ఫలితం = true;

    ఒకవేళ (icon) {
        పూర్ణాంకం x, y;
        పూర్ణాంకం propsize;
        దీర్ఘ *propdata;
        Uint32 *src;
        దీర్ఘ *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * పరిమాణం(దీర్ఘ));

        ఒకవేళ (!propdata) {
            తిరిగి false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        కొరకు (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            కొరకు (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, దత్తాంశం->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)propdata,
                            propsize);
        SDL_free(propdata);

        ఒకవేళ (caught_x11_error) {
            ఫలితం = SDL_సమితి_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    ఒకవేళ (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    తిరిగి ఫలితం;
}

శూన్య X11_Update_కిటికీ_Position(SDL_కిటికీ *కిటికీ, bool use_current_position)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    స్థిరరాశి పూర్ణాంకం rel_x = use_current_position ? కిటికీ->x : కిటికీ->pending.x;
    స్థిరరాశి పూర్ణాంకం rel_y = use_current_position ? కిటికీ->y : కిటికీ->pending.y;

    SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ,
                                  rel_x - దత్తాంశం->border_ఎడమ, rel_y - దత్తాంశం->border_శిఖరం,
                                  &దత్తాంశం->expected.x, &దత్తాంశం->expected.y);

    // Attempt to move the window
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        కిటికీ->అంతర్గత->pending_position = true;
    } లేకపోతే {
        దత్తాంశం->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, దత్తాంశం->expected.x, దత్తాంశం->expected.y);
    }
}

bool X11_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Sync any pending fullscreen or maximize events.
    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, కిటికీ);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MAXIMIZED) {
        ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_RESTORE) {
            కిటికీ->అంతర్గత->pending_position = true;
        }
        తిరిగి true;
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
            X11_ConstrainPopup(కిటికీ, true);
        }
        X11_Update_కిటికీ_Position(కిటికీ, false);
    } లేకపోతే {
        కిటికీ->అంతర్గత->fs_repositioned = true;
        SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    తిరిగి true;
}

శూన్య X11_సమితి_కిటికీ_Min_Max(SDL_కిటికీ *కిటికీ, bool use_current)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_కొలత_Hints();
    దీర్ఘ hint_flags = 0;

    X11_XGetWMNormalHints(display, దత్తాంశం->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_కొలత | PMax_కొలత | PAspect);

    ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_RESIZABLE) {
        ఒకవేళ (దత్తాంశం->కిటికీ->min_w || దత్తాంశం->కిటికీ->min_h) {
            sizehints->flags |= PMin_కొలత;
            sizehints->min_వెడల్పు_2 = దత్తాంశం->కిటికీ->min_w;
            sizehints->min_ఎత్తు_2 = దత్తాంశం->కిటికీ->min_h;
        }
        ఒకవేళ (దత్తాంశం->కిటికీ->max_w || దత్తాంశం->కిటికీ->max_h) {
            sizehints->flags |= PMax_కొలత;
            sizehints->max_వెడల్పు_2 = దత్తాంశం->కిటికీ->max_w;
            sizehints->max_ఎత్తు_2 = దత్తాంశం->కిటికీ->max_h;
        }
        ఒకవేళ (దత్తాంశం->కిటికీ->min_aspect > 0.0f || దత్తాంశం->కిటికీ->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(దత్తాంశం->కిటికీ->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(దత్తాంశం->కిటికీ->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } లేకపోతే {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_కొలత | PMax_కొలత;
        ఒకవేళ (use_current) {
            sizehints->min_వెడల్పు_2 = sizehints->max_వెడల్పు_2 = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : దత్తాంశం->కిటికీ->floating.w;
            sizehints->min_ఎత్తు_2 = sizehints->max_ఎత్తు_2 = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : దత్తాంశం->కిటికీ->floating.h;
        } లేకపోతే {
            sizehints->min_వెడల్పు_2 = sizehints->max_వెడల్పు_2 = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : దత్తాంశం->కిటికీ->windowed.w;
            sizehints->min_ఎత్తు_2 = sizehints->max_ఎత్తు_2 = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : దత్తాంశం->కిటికీ->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, దత్తాంశం->xwindow, sizehints);
    X11_XFree(sizehints);
}

శూన్య X11_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        X11_సమితి_కిటికీ_Min_Max(కిటికీ, true);
    }
}

శూన్య X11_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        X11_సమితి_కిటికీ_Min_Max(కిటికీ, true);
    }
}

శూన్య X11_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        X11_సమితి_కిటికీ_Min_Max(కిటికీ, true);
    }
}

శూన్య X11_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    ఒకవేళ (దత్తాంశం->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, కిటికీ);
    }

    // Set the size as pending if the window is being restored.
    ఒకవేళ (కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_FULLSCREEN)) {
        // New size will be set when the window is restored.
        ఒకవేళ (దత్తాంశం->pending_operation & X11_PENDING_OP_RESTORE) {
            దత్తాంశం->pending_కొలత = true;
        } లేకపోతే {
            // Can't resize the window.
            కిటికీ->చివరి_కొలత_pending = false;
        }
        తిరిగి;
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_కొలత_Hints();
            దీర్ఘ userhints;
            పూర్ణాంకం dest_x, dest_y;

            X11_XGetWMNormalHints(display, దత్తాంశం->xwindow, sizehints, &userhints);

            దత్తాంశం->expected.w = sizehints->min_వెడల్పు_2 = sizehints->max_వెడల్పు_2 = కిటికీ->pending.w;
            దత్తాంశం->expected.h = sizehints->min_ఎత్తు_2 = sizehints->max_ఎత్తు_2 = కిటికీ->pending.h;
            sizehints->flags |= PMin_కొలత | PMax_కొలత;
            దత్తాంశం->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, దత్తాంశం->xwindow, sizehints);

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
            X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, కిటికీ->pending.w, కిటికీ->pending.h);
            స్థిరరాశి పూర్ణాంకం x = కిటికీ->చివరి_position_pending ? కిటికీ->pending.x : కిటికీ->x;
            స్థిరరాశి పూర్ణాంకం y = కిటికీ->చివరి_position_pending ? కిటికీ->pending.y : కిటికీ->y;
            SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ,
                                          x - దత్తాంశం->border_ఎడమ,
                                          y - దత్తాంశం->border_శిఖరం,
                                          &dest_x, &dest_y);
            X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, dest_x, dest_y);
            X11_XRaise_కిటికీ(display, దత్తాంశం->xwindow);

            X11_XFree(sizehints);
        }
    } లేకపోతే {
        దత్తాంశం->expected.w = కిటికీ->pending.w;
        దత్తాంశం->expected.h = కిటికీ->pending.h;
        దత్తాంశం->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, దత్తాంశం->expected.w, దత్తాంశం->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->pending.w, కిటికీ->pending.h);
    }
}

bool X11_Get_కిటికీ_Borders_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    *ఎడమ = దత్తాంశం->border_ఎడమ;
    *కుడి = దత్తాంశం->border_కుడి;
    *శిఖరం = దత్తాంశం->border_శిఖరం;
    *bottom = దత్తాంశం->border_bottom;

    తిరిగి true;
}

bool X11_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom NET_WM_కిటికీ_OPACITY = దత్తాంశం->videodata->atoms.NET_WM_కిటికీ_OPACITY;

    ఒకవేళ (opacity == 1.0f) {
        X11_XDeleteProperty(display, దత్తాంశం->xwindow, NET_WM_కిటికీ_OPACITY);
    } లేకపోతే {
        స్థిరరాశి Uint32 FullyOpaque = 0xFFFFFFFF;
        స్థిరరాశి దీర్ఘ alpha = (దీర్ఘ)((ద్విగుణ)opacity * (ద్విగుణ)FullyOpaque);
        X11_XChangeProperty(display, దత్తాంశం->xwindow, NET_WM_కిటికీ_OPACITY, XA_CARDINAL, 32,
                            Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)&alpha, 1);
    }

    తిరిగి true;
}

bool X11_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *మాతృ_దత్తాంశం = మాతృ ? మాతృ->అంతర్గత : ఖాళీ;
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    Display *display = video_దత్తాంశం->display;

    ఒకవేళ (మాతృ_దత్తాంశం) {
        X11_XSetTransientForHint(display, దత్తాంశం->xwindow, మాతృ_దత్తాంశం->xwindow);
    } లేకపోతే {
        X11_XDeleteProperty(display, దత్తాంశం->xwindow, video_దత్తాంశం->atoms.WM_TRANSIENT_FOR);
    }

    తిరిగి true;
}

bool X11_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = video_దత్తాంశం->display;
    Uint32 flags = కిటికీ->flags;
    Atom _NET_WM_STATE = దత్తాంశం->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = దత్తాంశం->videodata->atoms._NET_WM_STATE_MODAL;

    ఒకవేళ (modal) {
        flags |= SDL_కిటికీ_MODAL;
    } లేకపోతే {
        flags &= ~SDL_కిటికీ_MODAL;
        X11_XDeleteProperty(display, దత్తాంశం->xwindow, video_దత్తాంశం->atoms.WM_TRANSIENT_FOR);
    }

    ఒకవేళ (X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_సందేశం;
        e.xclient.సందేశం_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.కిటికీ = దత్తాంశం->xwindow;
        e.xclient.దత్తాంశం.l[0] = modal ? NET_WM_STATE_కూడు : _NET_WM_STATE_REMOVE;
        e.xclient.దత్తాంశం.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.దత్తాంశం.l[3] = 0l;

        X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                       Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);
    } లేకపోతే {
        X11_సమితి_Net_WMState(_this, దత్తాంశం->xwindow, flags);
    }

    X11_XFlush(display);

    తిరిగి true;
}

శూన్య X11_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered)
{
    స్థిరరాశి bool focused = (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) != 0;
    స్థిరరాశి bool visible = !(కిటికీ->flags & SDL_కిటికీ_HIDDEN) && !కిటికీ->is_hiding;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;
    XEvent event;

    ఒకవేళ (దత్తాంశం->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        సమితి_కిటికీ_Bordered(display, displaydata->screen, దత్తాంశం->xwindow, bordered);
        X11_XFlush(display);

        ఒకవేళ (visible) {
            XWindow_లక్షణాలు attr;
            చేయి {
                X11_XSync(display, False);
                X11_XGet_కిటికీ_లక్షణాలు(display, దత్తాంశం->xwindow, &attr);
            } అయితే (attr.map_state != IsViewable);

            ఒకవేళ (focused) {
                X11_XSet_ఆదానం_Focus(display, దత్తాంశం->xwindow, Revert_గమ్యం_మాతృ, Current_సమయం);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&దత్తాంశం->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&దత్తాంశం->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_విలువలు(దత్తాంశం);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, కిటికీ->floating.w, కిటికీ->floating.h);
        X11_XSync(display, False);
    } లేకపోతే {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        దత్తాంశం->toggle_borders = true;
        దత్తాంశం->fullscreen_borders_forced_on = false;
    }
}

శూన్య X11_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        X11_సమితి_కిటికీ_Min_Max(కిటికీ, true);
    }
}

శూన్య X11_సమితి_కిటికీ_Always_On_శిఖరం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;
    Atom _NET_WM_STATE = దత్తాంశం->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = దత్తాంశం->videodata->atoms._NET_WM_STATE_ABOVE;

    ఒకవేళ (X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_సందేశం;
        e.xclient.సందేశం_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.కిటికీ = దత్తాంశం->xwindow;
        e.xclient.దత్తాంశం.l[0] =
            on_శిఖరం ? NET_WM_STATE_కూడు : _NET_WM_STATE_REMOVE;
        e.xclient.దత్తాంశం.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.దత్తాంశం.l[3] = 0l;

        X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                       Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);
    } లేకపోతే {
        X11_సమితి_Net_WMState(_this, దత్తాంశం->xwindow, కిటికీ->flags);
    }
    X11_XFlush(display);
}

శూన్య X11_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_కిటికీ_ACTIVATE_WHEN_SHOWN, true);
    bool సమితి_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    ఒకవేళ (దత్తాంశం->was_shown) {
        X11_PumpEvents(_this);
    }

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(కిటికీ, true);
        దత్తాంశం->pending_position = true;
        సమితి_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (శూన్య)bActivate;

    ఒకవేళ (!X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        X11_XMapRaised(display, దత్తాంశం->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&దత్తాంశం->xwindow);
        }
        X11_XFlush(display);
        సమితి_position = దత్తాంశం->pending_position ||
                       (!(కిటికీ->flags & SDL_కిటికీ_BORDERLESS) && !కిటికీ->undefined_x && !కిటికీ->undefined_y);
    }

    ఒకవేళ (!దత్తాంశం->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_ఆదానం_Focus(display, దత్తాంశం->xwindow, Revert_గమ్యం_None, Current_సమయం);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
        X11_సమితి_Keyboard_Focus(కిటికీ, true);
    }

    // Get some valid border values, if we haven't received them yet
    ఒకవేళ (దత్తాంశం->border_ఎడమ == 0 && దత్తాంశం->border_కుడి == 0 && దత్తాంశం->border_శిఖరం == 0 && దత్తాంశం->border_bottom == 0) {
        X11_Get_Border_విలువలు(దత్తాంశం);
    }

    ఒకవేళ (సమితి_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        స్థిరరాశి పూర్ణాంకం tx = (దత్తాంశం->pending_position ? కిటికీ->pending.x : కిటికీ->x) - (దత్తాంశం->was_shown ? 0 : దత్తాంశం->border_ఎడమ);
        స్థిరరాశి పూర్ణాంకం ty = (దత్తాంశం->pending_position ? కిటికీ->pending.y : కిటికీ->y) - (దత్తాంశం->was_shown ? 0 : దత్తాంశం->border_శిఖరం);
        పూర్ణాంకం x, y;

        SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, tx, ty, &x, &y);

        దత్తాంశం->pending_position = false;
        X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, కిటికీ->w, కిటికీ->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    దత్తాంశం->కొలత_move_event_flags = X11_కొలత_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    దత్తాంశం->కొలత_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
    దత్తాంశం->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    ఒకవేళ (దత్తాంశం->చివరి_xconfigure.type) {
        పూర్ణాంకం x, y;
        SDL_Global_గమ్యం_Relative_For_కిటికీ(దత్తాంశం->కిటికీ, దత్తాంశం->చివరి_xconfigure.x, దత్తాంశం->చివరి_xconfigure.y, &x, &y);
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, దత్తాంశం->చివరి_xconfigure.వెడల్పు, దత్తాంశం->చివరి_xconfigure.ఎత్తు);
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, x, y);
    }
}

శూన్య X11_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    పూర్ణాంకం screen = (displaydata ? displaydata->screen : 0);
    Display *display = దత్తాంశం->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    స్థిరరాశి bool is_mapped = X11_Is_కిటికీ_Mapped(_this, కిటికీ);
    X11_XWithdraw_కిటికీ(display, దత్తాంశం->xwindow, screen);
    ఒకవేళ (is_mapped && !(కిటికీ->flags & SDL_కిటికీ_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&దత్తాంశం->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
        SDL_కిటికీ *new_focus;
        స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(కిటికీ, &new_focus);
        X11_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

స్థిర bool X11_సమితి_కిటికీ_చురుకైన(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_దత్తాంశం(కిటికీ);

    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;
    Atom NET_చురుకైన_కిటికీ = దత్తాంశం->videodata->atoms.NET_చురుకైన_కిటికీ;

    ఒకవేళ (X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_సందేశం;
        e.xclient.సందేశం_type = NET_చురుకైన_కిటికీ;
        e.xclient.format = 32;
        e.xclient.కిటికీ = దత్తాంశం->xwindow;
        e.xclient.దత్తాంశం.l[0] = 1; // source indication. 1 = application
        e.xclient.దత్తాంశం.l[1] = దత్తాంశం->user_సమయం;
        e.xclient.దత్తాంశం.l[2] = 0;

        X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                       Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);

        X11_XFlush(display);
    }
    తిరిగి true;
}

శూన్య X11_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_కిటికీ_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_కిటికీ(display, దత్తాంశం->xwindow);
    ఒకవేళ (bActivate) {
        X11_సమితి_కిటికీ_చురుకైన(_this, కిటికీ);
    }
    X11_XFlush(display);
}

స్థిర bool X11_సమితి_కిటికీ_Maximized(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool maximized)
{
    CHECK_కిటికీ_దత్తాంశం(కిటికీ);

    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;
    Atom _NET_WM_STATE = దత్తాంశం->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = దత్తాంశం->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = దత్తాంశం->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        తిరిగి true;
    }

    ఒకవేళ (X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_సందేశం;
        e.xclient.సందేశం_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.కిటికీ = దత్తాంశం->xwindow;
        e.xclient.దత్తాంశం.l[0] =
            maximized ? NET_WM_STATE_కూడు : _NET_WM_STATE_REMOVE;
        e.xclient.దత్తాంశం.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.దత్తాంశం.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.దత్తాంశం.l[3] = 0l;

        ఒకవేళ (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_కిటికీ(కిటికీ);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            దత్తాంశం->expected.x = bounds.x + దత్తాంశం->border_ఎడమ;
            దత్తాంశం->expected.y = bounds.y + దత్తాంశం->border_శిఖరం;
            దత్తాంశం->expected.w = bounds.w - (దత్తాంశం->border_ఎడమ + దత్తాంశం->border_కుడి);
            దత్తాంశం->expected.h = bounds.h - (దత్తాంశం->border_శిఖరం + దత్తాంశం->border_bottom);
        } లేకపోతే {
            దత్తాంశం->expected.x = కిటికీ->floating.x;
            దత్తాంశం->expected.y = కిటికీ->floating.y;
            దత్తాంశం->expected.w = కిటికీ->floating.w;
            దత్తాంశం->expected.h = కిటికీ->floating.h;
        }

        X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                       Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);
    } లేకపోతే {
        X11_సమితి_Net_WMState(_this, దత్తాంశం->xwindow, కిటికీ->flags);
    }
    X11_XFlush(display);

    తిరిగి true;
}

శూన్య X11_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_కిటికీ(కిటికీ);
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        కిటికీ->అంతర్గత->కిటికీ_was_maximized = true;
        తిరిగి;
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        కిటికీ->అంతర్గత->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_సమితి_కిటికీ_Maximized(_this, కిటికీ, true);
    }
}

శూన్య X11_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;

    ఒకవేళ (దత్తాంశం->pending_operation & SDL_కిటికీ_FULLSCREEN) {
        SDL_Sync_కిటికీ(కిటికీ);
    }

    దత్తాంశం->pending_operation |= X11_PENDING_OP_MINIMIZE;
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        దత్తాంశం->కిటికీ_was_maximized = !!(కిటికీ->flags & SDL_కిటికీ_MAXIMIZED);
    }
    X11_XIconify_కిటికీ(display, దత్తాంశం->xwindow, displaydata->screen);
    X11_XFlush(display);
}

శూన్య X11_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Don't restore the window the first time it is being shown.
    ఒకవేళ (!కిటికీ->అంతర్గత->was_shown) {
        తిరిగి;
    }

    ఒకవేళ (కిటికీ->అంతర్గత->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_కిటికీ(కిటికీ);
    }

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && !(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        కిటికీ->అంతర్గత->కిటికీ_was_maximized = false;
        తిరిగి;
    }

    ఒకవేళ (కిటికీ->flags & (SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_MAXIMIZED) ||
        (కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        కిటికీ->అంతర్గత->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    స్థిరరాశి bool maximize = !!(కిటికీ->flags & SDL_కిటికీ_MINIMIZED) && కిటికీ->అంతర్గత->కిటికీ_was_maximized;
    X11_సమితి_కిటికీ_Maximized(_this, కిటికీ, maximize);
    X11_Show_కిటికీ(_this, కిటికీ);
    X11_సమితి_కిటికీ_చురుకైన(_this, కిటికీ);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
స్థిర SDL_Fullscreen_ఫలితం X11_సమితి_కిటికీ_Fullscreen_ద్వారా_WM(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = _display->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom _NET_WM_STATE = దత్తాంశం->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = దత్తాంశం->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    ఒకవేళ (!దత్తాంశం->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    ఒకవేళ (X11_Is_కిటికీ_Mapped(_this, కిటికీ)) {
        XEvent e;

        // Flush any pending fullscreen events.
        ఒకవేళ (దత్తాంశం->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_కిటికీ(_this, కిటికీ);
        }

        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
            ఒకవేళ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                తిరిగి SDL_FULLSCREEN_FAILED;
            } లేకపోతే ఒకవేళ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                తిరిగి SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        ఒకవేళ (fullscreen && !(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_కొలత_Hints();
            దీర్ఘ flags = 0;
            X11_XGetWMNormalHints(display, దత్తాంశం->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_కొలత | PMax_కొలత | PAspect);
            X11_XSetWMNormalHints(display, దత్తాంశం->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_సందేశం;
        e.xclient.సందేశం_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.కిటికీ = దత్తాంశం->xwindow;
        e.xclient.దత్తాంశం.l[0] =
            fullscreen ? NET_WM_STATE_కూడు : _NET_WM_STATE_REMOVE;
        e.xclient.దత్తాంశం.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.దత్తాంశం.l[3] = 0l;

        X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                       Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        ఒకవేళ (((కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) != 0) != (fullscreen != 0)) {
            దత్తాంశం->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        ఒకవేళ (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_కిటికీ_Position(కిటికీ);
            SDL_copyp(&దత్తాంశం->requested_fullscreen_బహుళకం, &కిటికీ->current_fullscreen_బహుళకం);
            ఒకవేళ (fullscreen != !!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
                దత్తాంశం->కిటికీ_was_maximized = !!(కిటికీ->flags & SDL_కిటికీ_MAXIMIZED);
            }
            దత్తాంశం->expected.x = displaydata->x;
            దత్తాంశం->expected.y = displaydata->y;
            దత్తాంశం->expected.w = _display->current_బహుళకం->w;
            దత్తాంశం->expected.h = _display->current_బహుళకం->h;

            // Only move the window if it isn't already on the target display.
            ఒకవేళ (!current || current != _display->id) {
                X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, displaydata->x, displaydata->y);
                దత్తాంశం->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } లేకపోతే {
            SDL_zero(దత్తాంశం->requested_fullscreen_బహుళకం);
            దత్తాంశం->pending_position = దత్తాంశం->fs_repositioned;
            దత్తాంశం->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_సందేశం;
            e.xclient.సందేశం_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.కిటికీ = దత్తాంశం->xwindow;
            ఒకవేళ (దత్తాంశం->కిటికీ_was_maximized) {
                e.xclient.దత్తాంశం.l[0] = NET_WM_STATE_కూడు;
            } లేకపోతే {
                e.xclient.దత్తాంశం.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.దత్తాంశం.l[1] = దత్తాంశం->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.దత్తాంశం.l[2] = దత్తాంశం->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.దత్తాంశం.l[3] = 0l;
            X11_XSendEvent(display, మూలం_కిటికీ(display, displaydata->screen), 0,
                           Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, &e);
        }
    } లేకపోతే {
        SDL_కిటికీ_Flags flags;

        flags = కిటికీ->flags;
        ఒకవేళ (fullscreen) {
            flags |= SDL_కిటికీ_FULLSCREEN;
        } లేకపోతే {
            flags &= ~SDL_కిటికీ_FULLSCREEN;
        }
        X11_సమితి_Net_WMState(_this, దత్తాంశం->xwindow, flags);
    }

    ఒకవేళ (దత్తాంశం->visual->class == ప్రత్యక్ష_Color) {
        ఒకవేళ (fullscreen) {
            X11_XInstallColormap(display, దత్తాంశం->colormap);
        } లేకపోతే {
            X11_XUninstallColormap(display, దత్తాంశం->colormap);
        }
    }

    తిరిగి SDL_FULLSCREEN_PENDING;
}

స్థిర SDL_Fullscreen_ఫలితం X11_సమితి_కిటికీ_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = _display->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    స్థిరరాశి పూర్ణాంకం screen = displaydata->screen;

    ఒకవేళ (!దత్తాంశం->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    ఒకవేళ (దత్తాంశం->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_కిటికీ(_this, కిటికీ);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_కిటికీ_Event(కిటికీ, fullscreen ? SDL_EVENT_కిటికీ_ENTER_FULLSCREEN : SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
    ఒకవేళ (fullscreen) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_కొలత_Hints();
            దీర్ఘ flags = 0;
            X11_XGetWMNormalHints(display, దత్తాంశం->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_కొలత | PMax_కొలత | PAspect);
            X11_XSetWMNormalHints(display, దత్తాంశం->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        సమితి_కిటికీ_Bordered(display, screen, దత్తాంశం->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        దత్తాంశం->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        దత్తాంశం->expected.x = rect.x;
        దత్తాంశం->expected.y = rect.y;
        దత్తాంశం->expected.w = rect.w;
        దత్తాంశం->expected.h = rect.h;
        X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, rect.x, rect.y);
        X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, rect.w, rect.h);
        X11_XRaise_కిటికీ(display, దత్తాంశం->xwindow);
    } లేకపోతే {
        దత్తాంశం->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        దత్తాంశం->expected.x = కిటికీ->windowed.x;
        దత్తాంశం->expected.y = కిటికీ->windowed.y;
        దత్తాంశం->expected.w = కిటికీ->windowed.w;
        దత్తాంశం->expected.h = కిటికీ->windowed.h;
        X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, కిటికీ->windowed.w, కిటికీ->windowed.h);
        X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, కిటికీ->windowed.x, కిటికీ->windowed.y);

        సమితి_కిటికీ_Bordered(display, screen, దత్తాంశం->xwindow, (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) == 0);
        X11_సమితి_కిటికీ_Min_Max(దత్తాంశం->కిటికీ, false);
    }

    X11_XFlush(display);

    తిరిగి SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_ఫలితం X11_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_కిటికీ_దత్తాంశం(కిటికీ);
    CHECK_DISPLAY_దత్తాంశం(_display);

    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    ఒకవేళ (దత్తాంశం->net_wm) {
        తిరిగి X11_సమితి_కిటికీ_Fullscreen_ద్వారా_WM(_this, కిటికీ, _display, fullscreen);
    }

    తిరిగి X11_సమితి_కిటికీ_Fullscreen_Legacy(_this, కిటికీ, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

రకనిర్వచనం నిర్మాణం
{
    గుర్తులేని అక్షరం *దత్తాంశం;
    పూర్ణాంకం format, లెక్క;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
స్థిర శూన్య X11_ReadProperty(SDL_x11Prop *p, Display *disp, కిటికీ_2 w, Atom prop)
{
    గుర్తులేని అక్షరం *ret = ఖాళీ;
    Atom type;
    పూర్ణాంకం fmt;
    గుర్తులేని దీర్ఘ లెక్క;
    గుర్తులేని దీర్ఘ బైట్లు_ఎడమ;
    పూర్ణాంకం బైట్లు_fetch = 0;

    చేయి {
        ఒకవేళ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_కిటికీ_Property(disp, w, prop, 0, బైట్లు_fetch, False, AnyPropertyType, &type, &fmt, &లెక్క, &బైట్లు_ఎడమ, &ret);
        బైట్లు_fetch += బైట్లు_ఎడమ;
    } అయితే (బైట్లు_ఎడమ != 0);

    p->దత్తాంశం = ret;
    p->format = fmt;
    p->లెక్క = లెక్క;
    p->type = type;
}

శూన్య *X11_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    XWindow_లక్షణాలు లక్షణాలు;
    Atom icc_profile_atom;
    అక్షరం icc_atom_string[పరిమాణం("_ICC_PROFILE_") + 12];
    శూన్య *ret_icc_profile_దత్తాంశం = ఖాళీ;
    CARD8 *icc_profile_దత్తాంశం;
    పూర్ణాంకం real_format;
    గుర్తులేని దీర్ఘ real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_కిటికీ_లక్షణాలు(display, దత్తాంశం->xwindow, &లక్షణాలు);
    ఒకవేళ (X11_XScreen_సంఖ్య_యొక్క_Screen(లక్షణాలు.screen) > 0) {
        (శూన్య)SDL_snprintf(icc_atom_string, పరిమాణం("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_సంఖ్య_యొక్క_Screen(లక్షణాలు.screen));
    } లేకపోతే {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", పరిమాణం("_ICC_PROFILE"));
    }
    X11_XGet_కిటికీ_లక్షణాలు(display, మూలం_కిటికీ_యొక్క_Screen(లక్షణాలు.screen), &లక్షణాలు);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    ఒకవేళ (icc_profile_atom == None) {
        SDL_సమితి_Error("Screen is not calibrated.");
        తిరిగి ఖాళీ;
    }

    X11_ReadProperty(&atomProp, display, మూలం_కిటికీ_యొక్క_Screen(లక్షణాలు.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.లెక్క;
    icc_profile_దత్తాంశం = atomProp.దత్తాంశం;
    ఒకవేళ (real_format == None) {
        SDL_సమితి_Error("Screen is not calibrated.");
        తిరిగి ఖాళీ;
    }

    ret_icc_profile_దత్తాంశం = SDL_malloc(real_nitems);
    ఒకవేళ (!ret_icc_profile_దత్తాంశం) {
        తిరిగి ఖాళీ;
    }

    SDL_memcpy(ret_icc_profile_దత్తాంశం, icc_profile_దత్తాంశం, real_nitems);
    *కొలత = real_nitems;
    X11_XFree(icc_profile_దత్తాంశం);

    తిరిగి ret_icc_profile_దత్తాంశం;
}

bool X11_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display;

    ఒకవేళ (!దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("Invalid window data");
    }
    దత్తాంశం->mouse_grabbed = false;
    దత్తాంశం->pending_grab = false;

    display = దత్తాంశం->videodata->display;

    ఒకవేళ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
            తిరిగి true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        ఒకవేళ (దత్తాంశం->xinput2_mouse_enabled && SDL_GetMouseState(ఖాళీ, ఖాళీ)) {
            దత్తాంశం->pending_grab = true;
            తిరిగి true;
        }

        // Try to grab the mouse
        ఒకవేళ (!దత్తాంశం->videodata->broken_సూచిక_grab) {
            స్థిరరాశి గుర్తులేని పూర్ణాంకం ముసుగు = Button_Press_ముసుగు | Button_Release_ముసుగు | సూచిక_Motion_ముసుగు | Focus_Change_ముసుగు;
            పూర్ణాంకం attempts;
            పూర్ణాంకం ఫలితం = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            కొరకు (attempts = 0; attempts < 100; attempts++) {
                ఫలితం = X11_XGrab_సూచిక(display, దత్తాంశం->xwindow, False, ముసుగు, Grab_బహుళకం_Async,
                                          Grab_బహుళకం_Async, దత్తాంశం->xwindow, None, Current_సమయం);
                ఒకవేళ (ఫలితం == GrabSuccess) {
                    దత్తాంశం->mouse_grabbed = true;
                    ఆపు;
                }
                SDL_Delay(50);
            }

            ఒకవేళ (ఫలితం != GrabSuccess) {
                దత్తాంశం->videodata->broken_సూచిక_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, కిటికీ);

        // Raise the window if we grab the mouse
        X11_XRaise_కిటికీ(display, దత్తాంశం->xwindow);
    } లేకపోతే {
        X11_XUngrab_సూచిక(display, Current_సమయం);

        X11_Xinput2UngrabTouch(_this, కిటికీ);
    }
    X11_XSync(display, False);

    ఒకవేళ (!దత్తాంశం->videodata->broken_సూచిక_grab) {
        తిరిగి true;
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display;

    ఒకవేళ (!దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("Invalid window data");
    }

    display = దత్తాంశం->videodata->display;

    ఒకవేళ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
            తిరిగి true;
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
        ఒకవేళ (_this->అంతర్గత->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            ఒకవేళ (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_సందేశం_Event client_సందేశం;
                client_సందేశం.type = Client_సందేశం;
                client_సందేశం.కిటికీ = దత్తాంశం->xwindow;
                client_సందేశం.format = 32;
                client_సందేశం.సందేశం_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_సందేశం.దత్తాంశం.l[0] = 1;
                client_సందేశం.దత్తాంశం.l[1] = Current_సమయం;

                X11_XSendEvent(display, Default_మూలం_కిటికీ(display), False, Substructure_Notify_ముసుగు | Substructure_Redirect_ముసుగు, (XEvent *)&client_సందేశం);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, దత్తాంశం->xwindow, True, Grab_బహుళకం_Async,
                          Grab_బహుళకం_Async, Current_సమయం);
    } లేకపోతే {
        X11_XUngrabKeyboard(display, Current_సమయం);
    }
    X11_XSync(display, False);

    తిరిగి true;
}

శూన్య X11_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం) {
        SDL_Video_దత్తాంశం *videodata = దత్తాంశం->videodata;
        Display *display = videodata->display;
        పూర్ణాంకం numwindows = videodata->numwindows;
        SDL_కిటికీ_దత్తాంశం **windowlist = videodata->windowlist;
        పూర్ణాంకం i;

        ఒకవేళ (windowlist) {
            కొరకు (i = 0; i < numwindows; ++i) {
                ఒకవేళ (windowlist[i] && (windowlist[i]->కిటికీ == కిటికీ)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = ఖాళీ;
                    videodata->numwindows--;
                    ఆపు;
                }
            }
        }

        X11_Destroy_ఆదానం_Context(దత్తాంశం);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
        X11_పదం_Resize_Sync(కిటికీ);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
            X11_XDestroy_కిటికీ(display, దత్తాంశం->xwindow);
            X11_XFlush(display);
        }
        SDL_free(దత్తాంశం);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        ఒకవేళ (videodata->చురుకైన_cursor_confined_కిటికీ == కిటికీ) {
            X11_Destroy_సూచిక_Barrier(_this, కిటికీ);
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    కిటికీ->అంతర్గత = ఖాళీ;
}

bool X11_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled)
{
    తిరిగి true; // just succeed, the real work is done elsewhere.
}

శూన్య X11_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom XdndAware = దత్తాంశం->videodata->atoms.XdndAware;

    ఒకవేళ (accept) {
        Atom xdnd_సంస్కరణ = 5;
        X11_XChangeProperty(display, దత్తాంశం->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)&xdnd_సంస్కరణ, 1);
    } లేకపోతే {
        X11_XDeleteProperty(display, దత్తాంశం->xwindow, XdndAware);
    }
}

bool X11_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, దత్తాంశం->xwindow);
    ఒకవేళ (!wmhints) {
        తిరిగి SDL_సమితి_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    దత్తాంశం->flashing_కిటికీ = false;
    దత్తాంశం->flash_cancel_సమయం = 0;

    ఎంపిక (operation) {
    స్థితి SDL_FLASH_CANCEL:
        // Taken care of above
        ఆపు;
    స్థితి SDL_FLASH_BRIEFLY:
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            దత్తాంశం->flashing_కిటికీ = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            దత్తాంశం->flash_cancel_సమయం = SDL_GetTicks() + 1000;
        }
        ఆపు;
    స్థితి SDL_FLASH_UNTIL_FOCUSED:
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            దత్తాంశం->flashing_కిటికీ = true;
        }
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }

    X11_XSetWMHints(display, దత్తాంశం->xwindow, wmhints);
    X11_XFree(wmhints);
    తిరిగి true;
}

bool SDL_X11_సమితి_కిటికీ_Title(Display *display, కిటికీ_2 xwindow, అక్షరం *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    పూర్ణాంకం conv = X11_Xmb_పాఠ్యం_List_గమ్యం_పాఠ్యం_Property(display, &title, 1, XTextStyle, &titleprop);
    స్థితి_3 స్థితి_2;

    ఒకవేళ (X11_XSupportsLocale() != True) {
        తిరిగి SDL_సమితి_Error("Current locale not supported by X server, cannot continue.");
    }

    ఒకవేళ (conv == 0) {
        X11_XSet_పాఠ్యం_Property(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.విలువ);
        // we know this can't be a locale error as we checked X locale validity
    } లేకపోతే ఒకవేళ (conv < 0) {
        తిరిగి SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
    } లేకపోతే { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        తిరిగి true;
    }

#నిర్వచితమైతే X_HAVE_UTF8_STRING
    స్థితి_2 = X11_Xutf8_పాఠ్యం_List_గమ్యం_పాఠ్యం_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    ఒకవేళ (స్థితి_2 == Success) {
        X11_XSet_పాఠ్యం_Property(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.విలువ);
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#అయితే_ముగింపు

    X11_XFlush(display);
    తిరిగి true;
}

శూన్య X11_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    Display *display = దత్తాంశం->videodata->display;
    కిటికీ_2 మూలం = మూలం_కిటికీ(display, displaydata->screen);
    XClient_సందేశం_Event e;
    కిటికీ_2 బిడ్డ_Return_2;
    పూర్ణాంకం wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, దత్తాంశం->xwindow, మూలం, x, y, &wx, &wy, &బిడ్డ_Return_2);

    e.type = Client_సందేశం;
    e.కిటికీ = దత్తాంశం->xwindow;
    e.సందేశం_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.దత్తాంశం.l[0] = 0;  // GTK device ID (unused)
    e.దత్తాంశం.l[1] = wx; // X coordinate relative to root
    e.దత్తాంశం.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, మూలం, False, Substructure_Redirect_ముసుగు | Substructure_Notify_ముసుగు, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_EXTERNAL) &&
        (దత్తాంశం->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(కిటికీ);
            తిరిగి true;
    }

    స్థిరరాశి Uint64 current_సమయం = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
        ఒకవేళ (_this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns &&
            current_సమయం < _this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns - current_సమయం, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += కిటికీ->అంతర్గత->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_గమ్యం_NS(1000) : SDL_MS_గమ్యం_NS(100);

    తిరిగి X11_Sync_కిటికీ_Timeout(_this, కిటికీ, timeout);
}

bool X11_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable)
{
    ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        Display *display = దత్తాంశం->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, దత్తాంశం->xwindow);
        ఒకవేళ (!wmhints) {
            తిరిగి SDL_సమితి_Error("Couldn't get WM hints");
        }

        wmhints->ఆదానం = focusable ? True : False;
        wmhints->flags |= ఆదానం_Hint;

        X11_XSetWMHints(display, దత్తాంశం->xwindow, wmhints);
        X11_XFree(wmhints);
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
            ఒకవేళ (!focusable && (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
                SDL_కిటికీ *new_focus;
                స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(కిటికీ, &new_focus);
                X11_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
            } లేకపోతే ఒకవేళ (focusable) {
                ఒకవేళ (SDL_ShouldFocusPopup(కిటికీ)) {
                    X11_సమితి_Keyboard_Focus(కిటికీ, true);
                }
            }
        }

        తిరిగి true;
    }

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
