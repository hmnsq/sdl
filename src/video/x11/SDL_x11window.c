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

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../core/unix/SDL_appid.h"

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11mouse.h"
#അന്തര്ഭാവ "SDL_x11xinput2.h"
#അന്തര്ഭാവ "SDL_x11xfixes.h"

#ifdef SDL_VIDEO_OPENGL_EGL
#അന്തര്ഭാവ "SDL_x11opengles.h"
#endif

#അന്തര്ഭാവ "SDL_x11xsync.h"

#define _NET_WM_STATE_REMOVE 0l
#define _NET_WM_STATE_ADD    1l

#define CHECK_WINDOW_DATA(window)                                       \
    എങ്കിൽ (!window) {                                                      \
        തിരികെ SDL_SetError("Invalid window");                          \
    }                                                                   \
    എങ്കിൽ (!window->internal) {                                          \
        തിരികെ SDL_SetError("Invalid window driver data");              \
    }

#define CHECK_DISPLAY_DATA(display)                                     \
    എങ്കിൽ (!_display) {                                                    \
        തിരികെ SDL_SetError("Invalid display");                         \
    }                                                                   \
    എങ്കിൽ (!_display->internal) {                                        \
        തിരികെ SDL_SetError("Invalid display driver data");             \
    }

സ്ഥിതം Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    തിരികെ ev->type == MapNotify && ev->xmap.window == *((Window *)win);
}
സ്ഥിതം Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    തിരികെ ev->type == UnmapNotify && ev->xunmap.window == *((Window *)win);
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

സ്ഥിതം bool X11_CheckCurrentDesktop(സ്ഥിരം അക്ഷരം *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    സ്ഥിരം അക്ഷരം *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    എങ്കിൽ (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        തിരികെ true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    എങ്കിൽ (desktopVar && SDL_strcasestr(desktopVar, name)) {
        തിരികെ true;
    }

    തിരികെ false;
}

സ്ഥിതം bool X11_IsWindowMapped(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = _this->internal;
    XWindowAttributes attr;

    X11_XGetWindowAttributes(videodata->display, data->xwindow, &attr);
    എങ്കിൽ (attr.map_state != IsUnmapped) {
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        തിരികെ false;
    }
}

സ്ഥിതം bool X11_IsDisplayOk(Display *display)
{
    എങ്കിൽ (display->flags & XlibDisplayIOError) {
        തിരികെ false;
    }
    തിരികെ true;
}

#എങ്കിൽ 0
സ്ഥിതം bool X11_IsActionAllowed(SDL_Window *window, Atom action)
{
    SDL_WindowData *data = window->internal;
    Atom _NET_WM_ALLOWED_ACTIONS = data->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = data->videodata->display;
    പൂർണ്ണസംഖ്യ form;
    unsigned long remain;
    unsigned long len, i;
    Atom *list;
    bool ret = false;

    എങ്കിൽ (X11_XGetWindowProperty(display, data->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (unsigned അക്ഷരം **)&list) == Success) {
        വേണ്ടി (i=0; i<len; ++i) {
            എങ്കിൽ (list[i] == action) {
                ret = true;
                നിർത്തുക;
            }
        }
        X11_XFree(list);
    }
    തിരികെ ret;
}
#endif // 0

സ്ഥിതം ശൂന്യം X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    സ്ഥിരം bool last_position_pending = window->last_position_pending;
    സ്ഥിരം bool last_size_pending = window->last_size_pending;

    X11_SyncWindow(_this, window);

    window->last_position_pending = last_position_pending;
    window->last_size_pending = last_size_pending;
}

ശൂന്യം X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags)
{
    SDL_VideoData *videodata = _this->internal;
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
    പൂർണ്ണസംഖ്യ എണ്ണം = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    എങ്കിൽ (flags & SDL_WINDOW_ALWAYS_ON_മുകൾ) {
        atoms[എണ്ണം++] = _NET_WM_STATE_ABOVE;
    }
    എങ്കിൽ (flags & SDL_WINDOW_UTILITY) {
        atoms[എണ്ണം++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[എണ്ണം++] = _NET_WM_STATE_SKIP_PAGER;
    }
    എങ്കിൽ (flags & SDL_WINDOW_നിവേശം_FOCUS) {
        atoms[എണ്ണം++] = _NET_WM_STATE_FOCUSED;
    }
    എങ്കിൽ (flags & SDL_WINDOW_MAXIMIZED) {
        atoms[എണ്ണം++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[എണ്ണം++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    എങ്കിൽ (flags & SDL_WINDOW_FULLSCREEN) {
        atoms[എണ്ണം++] = _NET_WM_STATE_FULLSCREEN;
    }
    എങ്കിൽ (flags & SDL_WINDOW_MODAL) {
        atoms[എണ്ണം++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(എണ്ണം <= SDL_arraysize(atoms));

    എങ്കിൽ (എണ്ണം > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned അക്ഷരം *)atoms, എണ്ണം);
    } അല്ലെങ്കിൽ {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

സ്ഥിതം ശൂന്യം X11_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Clamp popup windows to the output borders
    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        പൂർണ്ണസംഖ്യ abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        പൂർണ്ണസംഖ്യ abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        പൂർണ്ണസംഖ്യ offset_x = 0, offset_y = 0;

        എങ്കിൽ (window->constrain_popup) {
            // Calculate the total offset from the parents
            വേണ്ടി (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
                offset_x += w->x;
                offset_y += w->y;
            }

            offset_x += w->x;
            offset_y += w->y;
            abs_x += offset_x;
            abs_y += offset_y;

            displayID = SDL_GetDisplayForWindow(w);

            SDL_GetDisplayBounds(displayID, &rect);
            എങ്കിൽ (abs_x + window->w > rect.x + rect.w) {
                abs_x -= (abs_x + window->w) - (rect.x + rect.w);
            }
            എങ്കിൽ (abs_y + window->h > rect.y + rect.h) {
                abs_y -= (abs_y + window->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        എങ്കിൽ (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
        } അല്ലെങ്കിൽ {
            window->floating.x = window->windowed.x = abs_x - offset_x;
            window->floating.y = window->windowed.y = abs_y - offset_y;
        }
    }
}

സ്ഥിതം ശൂന്യം X11_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    ആകുമ്പോൾ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    എങ്കിൽ (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

SDL_WindowFlags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_Window *window, Window xwindow)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    പൂർണ്ണസംഖ്യ actualFormat;
    unsigned long i, അക്കം_ഇനങ്ങൾ, bytesAfter;
    unsigned അക്ഷരം *property_മൂല്യം = ശൂന്യ;
    long maxLength = 1024;
    SDL_WindowFlags flags = 0;

    എങ്കിൽ (X11_XGetWindowProperty(display, xwindow, _NET_WM_STATE,
                               0l, maxLength, False, XA_ATOM, &actualType,
                               &actualFormat, &അക്കം_ഇനങ്ങൾ, &bytesAfter,
                               &property_മൂല്യം) == Success) {
        Atom *atoms = (Atom *)property_മൂല്യം;
        പൂർണ്ണസംഖ്യ maximized = 0;
        പൂർണ്ണസംഖ്യ fullscreen = 0;

        വേണ്ടി (i = 0; i < അക്കം_ഇനങ്ങൾ; ++i) {
            എങ്കിൽ (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_WINDOW_MINIMIZED | SDL_WINDOW_OCCLUDED;
            } അല്ലെങ്കിൽ എങ്കിൽ (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_WINDOW_നിവേശം_FOCUS;
            } അല്ലെങ്കിൽ എങ്കിൽ (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } അല്ലെങ്കിൽ എങ്കിൽ (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } അല്ലെങ്കിൽ എങ്കിൽ (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        എങ്കിൽ (fullscreen == 1) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } അല്ലെങ്കിൽ എങ്കിൽ (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (window->flags & SDL_WINDOW_FULLSCREEN);
        }

        എങ്കിൽ (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            എങ്കിൽ (fullscreen) {
                flags |= (window->flags & SDL_WINDOW_MAXIMIZED);
            } അല്ലെങ്കിൽ {
                flags |= SDL_WINDOW_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindowAttributes attr;
            SDL_zero(attr);
            X11_XGetWindowAttributes(videodata->display, xwindow, &attr);
            എങ്കിൽ (attr.map_state == IsUnmapped) {
                flags |= SDL_WINDOW_HIDDEN;
            }
        }
        X11_XFree(property_മൂല്യം);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    തിരികെ flags;
}

സ്ഥിതം bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, Window w)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(*data));
    എങ്കിൽ (!data) {
        തിരികെ false;
    }
    data->videodata = videodata;
    data->window = window;
    data->xwindow = w;
    data->hit_test_result = SDL_HITTEST_NORMAL;

    X11_Create_നിവേശം_Context(data);

    // Associate the data with the window

    എങ്കിൽ (videodata->numwindows >= videodata->windowlistlength) {
        SDL_WindowData ** new_windowlist = (SDL_WindowData **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * വലുപ്പം(*videodata->windowlist));
        എങ്കിൽ (!new_windowlist) {
            പോകുക error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindowAttributes attrib;

        X11_XGetWindowAttributes(data->videodata->display, w, &attrib);
        എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window)) {
            window->x = window->windowed.x = window->floating.x = attrib.x;
            window->y = window->windowed.y = window->floating.y = attrib.y - data->border_മുകൾ;
        }
        window->w = window->windowed.w = window->floating.w = attrib.width;
        window->h = window->windowed.h = window->floating.h = attrib.height;
        എങ്കിൽ (attrib.map_state != IsUnmapped) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } അല്ലെങ്കിൽ {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        data->visual = attrib.visual;
        data->colormap = attrib.colormap;
    }

    window->flags |= X11_GetNetWMState(_this, window, w);

    {
        Window FocalWindow;
        പൂർണ്ണസംഖ്യ RevertTo = 0;
        X11_XGet_നിവേശം_Focus(data->videodata->display, &FocalWindow, &RevertTo);
        എങ്കിൽ (FocalWindow == w) {
            window->flags |= SDL_WINDOW_നിവേശം_FOCUS;
        }

        എങ്കിൽ (window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
            SDL_SetKeyboardFocus(data->window);
        }

        എങ്കിൽ (window->flags & SDL_WINDOW_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        window->title = X11_GetWindowTitle(_this, w);
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    പൂർണ്ണസംഖ്യ screen = (displaydata ? displaydata->screen : 0);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, data->videodata->display);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_X11_SCREEN_സംഖ്യ, screen);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_X11_WINDOW_സംഖ്യ, data->xwindow);


#എങ്കിൽ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    എങ്കിൽ ((window->flags & SDL_WINDOW_OPENGL) &&
        ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_data || X11_GL_UseEGL(_this))
#endif
    ) {
#ifdef SDL_VIDEO_OPENGL_EGL
        എങ്കിൽ (!_this->egl_data) {
            പോകുക error_cleanup;
        }

        // Create the GLES window surface
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)w);

        എങ്കിൽ (data->egl_surface == EGL_NO_SURFACE) {
            SDL_SetError("Could not create GLES window surface");
            പോകുക error_cleanup;
        }
#അല്ലെങ്കിൽ
        SDL_SetError("Could not create GLES window surface (EGL support not configured)");
        പോകുക error_cleanup;
#endif // SDL_VIDEO_OPENGL_EGL
    }
#endif

    // All done!
    window->internal = data;
    videodata->windowlist[videodata->numwindows++] = data;
    തിരികെ true;

error_cleanup:
    X11_Destroy_നിവേശം_Context(data);
    SDL_free(data);
    തിരികെ false;
}

സ്ഥിതം ശൂന്യം Setup_Window_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    long fevent = 0;
    SDL_WindowData *data = window->internal;
    Window xwindow = data->xwindow;

#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (SDL_X11_HAVE_UTF8 && data->ic) {
        X11_XGetICValues(data->ic, XNFilterEvents, &fevent, ശൂന്യ);
    }
#endif

    X11_Xinput2Select(_this, window);

    {
        unsigned പൂർണ്ണസംഖ്യ x11_keyboard_events = താക്കോൽ_Press_Mask | താക്കോൽ_Release_Mask;
        unsigned പൂർണ്ണസംഖ്യ x11_pointer_events = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

        X11_Xinput2SelectMouseAndKeyboard(_this, window);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        എങ്കിൽ (data->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        എങ്കിൽ (data->xinput2_mouse_enabled) {
            x11_pointer_events = 0;
        }

        X11_XSelect_നിവേശം(data->videodata->display, xwindow,
                         (FocusChangeMask | EnterWindowMask | LeaveWindowMask | ExposureMask |
                          x11_keyboard_events | x11_pointer_events |
                          PropertyChangeMask | StructureNotifyMask |
                          KeymapStateMask | fevent));
    }
}

സ്ഥിതം ശൂന്യം SetWindowBordered(Display *display, പൂർണ്ണസംഖ്യ screen, Window window, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    എങ്കിൽ (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        ഘടന
        {
            unsigned long flags;
            unsigned long functions;
            unsigned long decorations;
            long നിവേശം_mode;
            unsigned long status;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, window, WM_HINTS, WM_HINTS, 32,
                            PropModeReplace, (unsigned അക്ഷരം *)&MWMHints,
                            വലുപ്പം(MWMHints) / വലുപ്പം(long));
    } അല്ലെങ്കിൽ { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, window, വേര്_Window(display, screen));
    }
}

bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    Window w = (Window)SDL_Get_സംഖ്യ_Property(create_props, SDL_PROP_WINDOW_CREATE_X11_WINDOW_സംഖ്യ,
                (Window)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", ശൂന്യ));
    എങ്കിൽ (w) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        എങ്കിൽ (!SetupWindowData(_this, window, w)) {
            തിരികെ false;
        }

        എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_WINDOW_നിവേശം, true)) {
            Setup_Window_നിവേശം(_this, window);
        }
        തിരികെ true;
    }

    SDL_VideoData *data = _this->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    എങ്കിൽ (!displaydata) {
        തിരികെ SDL_SetError("Could not find display info");
    }

    സ്ഥിരം bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    സ്ഥിരം bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (window->flags & SDL_WINDOW_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_WindowData *windowdata;
    Display *display = data->display;
    പൂർണ്ണസംഖ്യ screen = displaydata->screen;
    Visual *visual;
    പൂർണ്ണസംഖ്യ depth;
    XSetWindowAttributes xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom _NET_WM_WINDOW_TYPE;
    Atom wintype;
    സ്ഥിരം അക്ഷരം *wintype_name = ശൂന്യ;
    long compositor = 1;
    Atom _NET_WM_PID;
    സ്ഥിരം അക്ഷരം *hint = ശൂന്യ;
    പൂർണ്ണസംഖ്യ win_x, win_y;
    bool undefined_position = false;

#എങ്കിൽ defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    സ്ഥിരം പൂർണ്ണസംഖ്യ transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    സ്ഥിരം അക്ഷരം *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    സ്ഥിരം അക്ഷരം *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    എങ്കിൽ (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, template;
        പൂർണ്ണസംഖ്യ nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(forced_visual_id, ശൂന്യ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        എങ്കിൽ (vi) {
            visual = vi->visual;
            depth = vi->depth;
            X11_XFree(vi);
        } അല്ലെങ്കിൽ {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ ((window->flags & SDL_WINDOW_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = ശൂന്യ;

#ifdef SDL_VIDEO_OPENGL_EGL
        എങ്കിൽ (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_data || X11_GL_UseEGL(_this))
#endif
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } അല്ലെങ്കിൽ
#endif
        {
#ifdef SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#endif
        }

        എങ്കിൽ (!vinfo) {
            തിരികെ false;
        }
        visual = vinfo->visual;
        depth = vinfo->depth;
        X11_XFree(vinfo);
    } അല്ലെങ്കിൽ
#endif
    {
        visual = displaydata->visual;
        depth = displaydata->depth;
    }

    xattr.override_redirect = ((window->flags & SDL_WINDOW_TOOLTIP) || (window->flags & SDL_WINDOW_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    എങ്കിൽ (visual->class == DirectColor) {
        XColor *colorcells;
        പൂർണ്ണസംഖ്യ i;
        പൂർണ്ണസംഖ്യ ncolors;
        പൂർണ്ണസംഖ്യ rmax, gmax, bmax;
        പൂർണ്ണസംഖ്യ rmask, gmask, bmask;
        പൂർണ്ണസംഖ്യ rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, വേര്_Window(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        എങ്കിൽ (!xattr.colormap) {
            തിരികെ SDL_SetError("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * വലുപ്പം(XColor));
        എങ്കിൽ (!colorcells) {
            തിരികെ false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_mask;
        ആകുമ്പോൾ (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_mask;
        ആകുമ്പോൾ (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_mask;
        ആകുമ്പോൾ (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        വേണ്ടി (i = 0; i < ncolors; i++) {
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
    } അല്ലെങ്കിൽ {
        xattr.colormap =
            X11_XCreateColormap(display, വേര്_Window(display, screen),
                                visual, AllocNone);
    }

    എങ്കിൽ (window->undefined_x && window->undefined_y &&
        window->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        X11_ConstrainPopup(window, false);
    }
    SDL_RelativeToGlobalForWindow(window,
                                  window->floating.x, window->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreateWindow(display, വേര്_Window(display, screen),
                          win_x, win_y, window->floating.w, window->floating.h,
                          0, depth, നിവേശം_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    എങ്കിൽ (!w) {
        തിരികെ SDL_SetError("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    എങ്കിൽ (!(window->pending_flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, screen, w, !(window->flags & SDL_WINDOW_BORDERLESS));
    }

    sizehints = X11_XAllocSizeHints();
    // Setup the normal size hints
    sizehints->flags = 0;
    എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        sizehints->min_width = sizehints->max_width = window->floating.w;
        sizehints->min_height = sizehints->max_height = window->floating.h;
        sizehints->flags |= (PMaxSize | PMinSize);
    }
    എങ്കിൽ (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->നിവേശം = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) ? True : False;
    wmhints->window_group = data->window_group;
    wmhints->flags = നിവേശം_Hint | WindowGroupHint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (അക്ഷരം *)SDL_GetExeName();
    classhints->res_class = (അക്ഷരം *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, ശൂന്യ, ശൂന്യ, ശൂന്യ, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    എങ്കിൽ (data->pid > 0) {
        long pid = (long)data->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, PropModeReplace,
                            (unsigned അക്ഷരം *)&pid, 1);
    }

    // Set the window manager state
    X11_SetNetWMState(_this, w, window->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_WINDOW_TYPE);
    എങ്കിൽ (window->flags & SDL_WINDOW_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } അല്ലെങ്കിൽ എങ്കിൽ (hint && *hint) {
        wintype_name = hint;
    } അല്ലെങ്കിൽ {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                        PropModeReplace, (unsigned അക്ഷരം *)&wintype, 1);
    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            PropModeReplace,
                            (unsigned അക്ഷരം *)&compositor, 1);
    }

    {
        Atom protocols[4];
        പൂർണ്ണസംഖ്യ proto_എണ്ണം = 0;

        protocols[proto_എണ്ണം++] = data->atoms.WM_DELETE_WINDOW; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_എണ്ണം++] = data->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        എങ്കിൽ (use_resize_sync) {
            protocols[proto_എണ്ണം++] = data->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_എണ്ണം <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_എണ്ണം);
    }

    എങ്കിൽ (!SetupWindowData(_this, window, w)) {
        X11_XDestroyWindow(display, w);
        തിരികെ false;
    }
    windowdata = window->internal;

    // Set the parent if this is a non-popup window.
    എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window) && window->parent) {
        X11_XSetTransientForHint(display, w, window->parent->internal->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(window->pending_flags & SDL_WINDOW_FULLSCREEN) &&
                                               !!(window->flags & SDL_WINDOW_BORDERLESS);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    എങ്കിൽ (use_resize_sync) {
        X11_InitResizeSync(window);
    }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    എങ്കിൽ (window->flags & SDL_WINDOW_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_നിവേശം, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
    }
#endif

    Setup_Window_നിവേശം(_this, window);

    // For _ICC_PROFILE.
    X11_XSelect_നിവേശം(display, വേര്_Window(display, screen), PropertyChangeMask);

    X11_XFlush(display);

    തിരികെ true;
}

അക്ഷരം *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    പൂർണ്ണസംഖ്യ status, real_format;
    Atom real_type;
    unsigned long ഇനങ്ങൾ_read, ഇനങ്ങൾ_ഇടത്;
    unsigned അക്ഷരം *propdata;
    അക്ഷരം *title = ശൂന്യ;

    status = X11_XGetWindowProperty(display, xwindow, data->atoms._NET_WM_NAME,
                                    0L, 8192L, False, data->atoms.UTF8_STRING, &real_type, &real_format,
                                    &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
    എങ്കിൽ (status == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(അക്ഷരം *, propdata));
        X11_XFree(propdata);
    } അല്ലെങ്കിൽ {
        status = X11_XGetWindowProperty(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
        എങ്കിൽ (status == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(അക്ഷരം *, propdata), ഇനങ്ങൾ_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } അല്ലെങ്കിൽ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    തിരികെ title;
}

ശൂന്യം X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Window xwindow = data->xwindow;
    Display *display = data->videodata->display;
    അക്ഷരം *title = window->title ? window->title : "";

    SDL_X11_SetWindowTitle(display, xwindow, title);
}

സ്ഥിതം bool caught_x11_error = false;
സ്ഥിതം പൂർണ്ണസംഖ്യ X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം X11_ExternalResizeMoveSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    പൂർണ്ണസംഖ്യ (*prev_handler)(Display *, XErrorEvent *);
    unsigned പൂർണ്ണസംഖ്യ child_എണ്ണം;
    Window childReturn, വേര്, parent;
    Window *children;
    XWindowAttributes attrs;
    Uint64 timeout = 0;
    പൂർണ്ണസംഖ്യ x, y;
    സ്ഥിരം bool send_move = !!(data->pending_operation & X11_PENDING_OP_MOVE);
    സ്ഥിരം bool send_resize = !!(data->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_വൃക്ഷം(display, data->xwindow, &വേര്, &parent, &children, &child_എണ്ണം);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_TO_NS(100);
    ആകുമ്പോൾ (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGetWindowAttributes(display, data->xwindow, &attrs);
        X11_XTranslateCoordinates(display, parent, Default_വേര്_Window(display),
                                  attrs.x, attrs.y, &x, &y, &childReturn);
        SDL_GlobalToRelativeForWindow(window, x, y, &x, &y);

        എങ്കിൽ (!caught_x11_error) {
            എങ്കിൽ ((data->pending_operation & X11_PENDING_OP_MOVE) && (x == data->expected.x + data->border_ഇടത് && y == data->expected.y + data->border_മുകൾ)) {
                data->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            എങ്കിൽ ((data->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.width == data->expected.w && attrs.height == data->expected.h)) {
                data->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            എങ്കിൽ (data->pending_operation == X11_PENDING_OP_NONE) {
                നിർത്തുക;
            }
        }

        എങ്കിൽ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            data->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            data->expected.x = x;
            data->expected.y = y;
            data->expected.w = attrs.width;
            data->expected.h = attrs.height;
            നിർത്തുക;
        }

        SDL_Delay(10);
    }

    എങ്കിൽ (!caught_x11_error) {
        എങ്കിൽ (send_move) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
        }
        എങ്കിൽ (send_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, attrs.width, attrs.height);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
സ്ഥിതം bool X11_SyncWindowTimeout(SDL_VideoDevice *_this, SDL_Window *window, Uint64 param_timeout)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    പൂർണ്ണസംഖ്യ (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool result = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    എങ്കിൽ (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    ആകുമ്പോൾ (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        എങ്കിൽ ((data->pending_operation & X11_PENDING_OP_MOVE) && (window->x == data->expected.x + data->border_ഇടത് && window->y == data->expected.y + data->border_മുകൾ)) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        എങ്കിൽ ((data->pending_operation & X11_PENDING_OP_RESIZE) && (window->w == data->expected.w && window->h == data->expected.h)) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        എങ്കിൽ (data->pending_operation == X11_PENDING_OP_NONE) {
            എങ്കിൽ (force_exit ||
                (window->x == data->expected.x + data->border_ഇടത് && window->y == data->expected.y + data->border_മുകൾ &&
                 window->w == data->expected.w && window->h == data->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                നിർത്തുക;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        എങ്കിൽ (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            data->expected.x = window->x;
            data->expected.y = window->y;
            data->expected.w = window->w;
            data->expected.h = window->h;

            result = false;
            നിർത്തുക;
        }

        SDL_Delay(10);
    }

    data->pending_operation = X11_PENDING_OP_NONE;

    എങ്കിൽ (!caught_x11_error) {
        X11_PumpEvents(_this);
    } അല്ലെങ്കിൽ {
        result = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    തിരികെ result;
}

bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_ICON = data->videodata->atoms._NET_WM_ICON;
    പൂർണ്ണസംഖ്യ (*prevHandler)(Display *, XErrorEvent *) = ശൂന്യ;
    bool result = true;

    എങ്കിൽ (icon) {
        പൂർണ്ണസംഖ്യ x, y;
        പൂർണ്ണസംഖ്യ propsize;
        long *propdata;
        Uint32 *src;
        long *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * വലുപ്പം(long));

        എങ്കിൽ (!propdata) {
            തിരികെ false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        വേണ്ടി (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            വേണ്ടി (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, data->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, PropModeReplace, (unsigned അക്ഷരം *)propdata,
                            propsize);
        SDL_free(propdata);

        എങ്കിൽ (caught_x11_error) {
            result = SDL_SetError("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    എങ്കിൽ (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    തിരികെ result;
}

ശൂന്യം X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ rel_x = use_current_position ? window->x : window->pending.x;
    സ്ഥിരം പൂർണ്ണസംഖ്യ rel_y = use_current_position ? window->y : window->pending.y;

    SDL_RelativeToGlobalForWindow(window,
                                  rel_x - data->border_ഇടത്, rel_y - data->border_മുകൾ,
                                  &data->expected.x, &data->expected.y);

    // Attempt to move the window
    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        window->internal->pending_position = true;
    } അല്ലെങ്കിൽ {
        data->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
    }
}

bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Sync any pending fullscreen or maximize events.
    എങ്കിൽ (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    എങ്കിൽ (window->flags & SDL_WINDOW_MAXIMIZED) {
        എങ്കിൽ (window->internal->pending_operation & X11_PENDING_OP_RESTORE) {
            window->internal->pending_position = true;
        }
        തിരികെ true;
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
            X11_ConstrainPopup(window, true);
        }
        X11_UpdateWindowPosition(window, false);
    } അല്ലെങ്കിൽ {
        window->internal->fs_repositioned = true;
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    തിരികെ true;
}

ശൂന്യം X11_SetWindowMinMax(SDL_Window *window, bool use_current)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSizeHints *sizehints = X11_XAllocSizeHints();
    long hint_flags = 0;

    X11_XGetWMNormalHints(display, data->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMinSize | PMaxSize | PAspect);

    എങ്കിൽ (data->window->flags & SDL_WINDOW_RESIZABLE) {
        എങ്കിൽ (data->window->min_w || data->window->min_h) {
            sizehints->flags |= PMinSize;
            sizehints->min_width = data->window->min_w;
            sizehints->min_height = data->window->min_h;
        }
        എങ്കിൽ (data->window->max_w || data->window->max_h) {
            sizehints->flags |= PMaxSize;
            sizehints->max_width = data->window->max_w;
            sizehints->max_height = data->window->max_h;
        }
        എങ്കിൽ (data->window->min_aspect > 0.0f || data->window->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(data->window->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(data->window->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } അല്ലെങ്കിൽ {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMinSize | PMaxSize;
        എങ്കിൽ (use_current) {
            sizehints->min_width = sizehints->max_width = window->last_size_pending ? window->pending.w : data->window->floating.w;
            sizehints->min_height = sizehints->max_height = window->last_size_pending ? window->pending.h : data->window->floating.h;
        } അല്ലെങ്കിൽ {
            sizehints->min_width = sizehints->max_width = window->last_size_pending ? window->pending.w : data->window->windowed.w;
            sizehints->min_height = sizehints->max_height = window->last_size_pending ? window->pending.h : data->window->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, data->xwindow, sizehints);
    X11_XFree(sizehints);
}

ശൂന്യം X11_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

ശൂന്യം X11_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

ശൂന്യം X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

ശൂന്യം X11_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    എങ്കിൽ (data->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the size as pending if the window is being restored.
    എങ്കിൽ (window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN)) {
        // New size will be set when the window is restored.
        എങ്കിൽ (data->pending_operation & X11_PENDING_OP_RESTORE) {
            data->pending_size = true;
        } അല്ലെങ്കിൽ {
            // Can't resize the window.
            window->last_size_pending = false;
        }
        തിരികെ;
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAllocSizeHints();
            long userhints;
            പൂർണ്ണസംഖ്യ dest_x, dest_y;

            X11_XGetWMNormalHints(display, data->xwindow, sizehints, &userhints);

            data->expected.w = sizehints->min_width = sizehints->max_width = window->pending.w;
            data->expected.h = sizehints->min_height = sizehints->max_height = window->pending.h;
            sizehints->flags |= PMinSize | PMaxSize;
            data->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, data->xwindow, sizehints);

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
            X11_XResizeWindow(display, data->xwindow, window->pending.w, window->pending.h);
            സ്ഥിരം പൂർണ്ണസംഖ്യ x = window->last_position_pending ? window->pending.x : window->x;
            സ്ഥിരം പൂർണ്ണസംഖ്യ y = window->last_position_pending ? window->pending.y : window->y;
            SDL_RelativeToGlobalForWindow(window,
                                          x - data->border_ഇടത്,
                                          y - data->border_മുകൾ,
                                          &dest_x, &dest_y);
            X11_XMoveWindow(display, data->xwindow, dest_x, dest_y);
            X11_XRaiseWindow(display, data->xwindow);

            X11_XFree(sizehints);
        }
    } അല്ലെങ്കിൽ {
        data->expected.w = window->pending.w;
        data->expected.h = window->pending.h;
        data->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResizeWindow(display, data->xwindow, data->expected.w, data->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

bool X11_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *മുകൾ, പൂർണ്ണസംഖ്യ *ഇടത്, പൂർണ്ണസംഖ്യ *bottom, പൂർണ്ണസംഖ്യ *വലത്)
{
    SDL_WindowData *data = window->internal;

    *ഇടത് = data->border_ഇടത്;
    *വലത് = data->border_വലത്;
    *മുകൾ = data->border_മുകൾ;
    *bottom = data->border_bottom;

    തിരികെ true;
}

bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം opacity)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_WINDOW_OPACITY = data->videodata->atoms._NET_WM_WINDOW_OPACITY;

    എങ്കിൽ (opacity == 1.0f) {
        X11_XDeleteProperty(display, data->xwindow, _NET_WM_WINDOW_OPACITY);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം Uint32 FullyOpaque = 0xFFFFFFFF;
        സ്ഥിരം long alpha = (long)((ഇരട്ട)opacity * (ഇരട്ട)FullyOpaque);
        X11_XChangeProperty(display, data->xwindow, _NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                            PropModeReplace, (unsigned അക്ഷരം *)&alpha, 1);
    }

    തിരികെ true;
}

bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
    SDL_WindowData *data = window->internal;
    SDL_WindowData *parent_data = parent ? parent->internal : ശൂന്യ;
    SDL_VideoData *video_data = _this->internal;
    Display *display = video_data->display;

    എങ്കിൽ (parent_data) {
        X11_XSetTransientForHint(display, data->xwindow, parent_data->xwindow);
    } അല്ലെങ്കിൽ {
        X11_XDeleteProperty(display, data->xwindow, video_data->atoms.WM_TRANSIENT_FOR);
    }

    തിരികെ true;
}

bool X11_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *video_data = _this->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = video_data->display;
    Uint32 flags = window->flags;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = data->videodata->atoms._NET_WM_STATE_MODAL;

    എങ്കിൽ (modal) {
        flags |= SDL_WINDOW_MODAL;
    } അല്ലെങ്കിൽ {
        flags &= ~SDL_WINDOW_MODAL;
        X11_XDeleteProperty(display, data->xwindow, video_data->atoms.WM_TRANSIENT_FOR);
    }

    എങ്കിൽ (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] = modal ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.data.l[3] = 0l;

        X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } അല്ലെങ്കിൽ {
        X11_SetNetWMState(_this, data->xwindow, flags);
    }

    X11_XFlush(display);

    തിരികെ true;
}

ശൂന്യം X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    സ്ഥിരം bool focused = (window->flags & SDL_WINDOW_നിവേശം_FOCUS) != 0;
    സ്ഥിരം bool visible = !(window->flags & SDL_WINDOW_HIDDEN) && !window->is_hiding;
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    XEvent event;

    എങ്കിൽ (data->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, displaydata->screen, data->xwindow, bordered);
        X11_XFlush(display);

        എങ്കിൽ (visible) {
            XWindowAttributes attr;
            ചെയ്യുക {
                X11_XSync(display, False);
                X11_XGetWindowAttributes(display, data->xwindow, &attr);
            } ആകുമ്പോൾ (attr.map_state != IsViewable);

            എങ്കിൽ (focused) {
                X11_XSet_നിവേശം_Focus(display, data->xwindow, RevertToParent, CurrentTime);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&data->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&data->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_മൂല്യങ്ങൾ(data);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResizeWindow(display, data->xwindow, window->floating.w, window->floating.h);
        X11_XSync(display, False);
    } അല്ലെങ്കിൽ {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        data->toggle_borders = true;
        data->fullscreen_borders_forced_on = false;
    }
}

ശൂന്യം X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

ശൂന്യം X11_Set_Window_Always_On_മുകൾ(SDL_VideoDevice *_this, SDL_Window *window, bool on_മുകൾ)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = data->videodata->atoms._NET_WM_STATE_ABOVE;

    എങ്കിൽ (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] =
            on_മുകൾ ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.data.l[3] = 0l;

        X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } അല്ലെങ്കിൽ {
        X11_SetNetWMState(_this, data->xwindow, window->flags);
    }
    X11_XFlush(display);
}

ശൂന്യം X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);
    bool set_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    എങ്കിൽ (data->was_shown) {
        X11_PumpEvents(_this);
    }

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(window, true);
        data->pending_position = true;
        set_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (ശൂന്യം)bActivate;

    എങ്കിൽ (!X11_IsWindowMapped(_this, window)) {
        X11_XMapRaised(display, data->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&data->xwindow);
        }
        X11_XFlush(display);
        set_position = data->pending_position ||
                       (!(window->flags & SDL_WINDOW_BORDERLESS) && !window->undefined_x && !window->undefined_y);
    }

    എങ്കിൽ (!data->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_നിവേശം_Focus(display, data->xwindow, RevertToNone, CurrentTime);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    എങ്കിൽ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        X11_SetKeyboardFocus(window, true);
    }

    // Get some valid border values, if we haven't received them yet
    എങ്കിൽ (data->border_ഇടത് == 0 && data->border_വലത് == 0 && data->border_മുകൾ == 0 && data->border_bottom == 0) {
        X11_Get_Border_മൂല്യങ്ങൾ(data);
    }

    എങ്കിൽ (set_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        സ്ഥിരം പൂർണ്ണസംഖ്യ tx = (data->pending_position ? window->pending.x : window->x) - (data->was_shown ? 0 : data->border_ഇടത്);
        സ്ഥിരം പൂർണ്ണസംഖ്യ ty = (data->pending_position ? window->pending.y : window->y) - (data->was_shown ? 0 : data->border_മുകൾ);
        പൂർണ്ണസംഖ്യ x, y;

        SDL_RelativeToGlobalForWindow(window, tx, ty, &x, &y);

        data->pending_position = false;
        X11_XMoveWindow(display, data->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResizeWindow(display, data->xwindow, window->w, window->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    data->size_move_event_flags = X11_SIZE_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    data->size_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    എങ്കിൽ (data->last_xconfigure.type) {
        പൂർണ്ണസംഖ്യ x, y;
        SDL_GlobalToRelativeForWindow(data->window, data->last_xconfigure.x, data->last_xconfigure.y, &x, &y);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, data->last_xconfigure.width, data->last_xconfigure.height);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
    }
}

ശൂന്യം X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    പൂർണ്ണസംഖ്യ screen = (displaydata ? displaydata->screen : 0);
    Display *display = data->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    സ്ഥിരം bool is_mapped = X11_IsWindowMapped(_this, window);
    X11_XWithdrawWindow(display, data->xwindow, screen);
    എങ്കിൽ (is_mapped && !(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&data->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    എങ്കിൽ ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        സ്ഥിരം bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        X11_SetKeyboardFocus(new_focus, set_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

സ്ഥിതം bool X11_SetWindowActive(SDL_VideoDevice *_this, SDL_Window *window)
{
    CHECK_WINDOW_DATA(window);

    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_ACTIVE_WINDOW = data->videodata->atoms._NET_ACTIVE_WINDOW;

    എങ്കിൽ (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_ACTIVE_WINDOW;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] = 1; // source indication. 1 = application
        e.xclient.data.l[1] = data->user_time;
        e.xclient.data.l[2] = 0;

        X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        X11_XFlush(display);
    }
    തിരികെ true;
}

ശൂന്യം X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED, true);

    X11_XRaiseWindow(display, data->xwindow);
    എങ്കിൽ (bActivate) {
        X11_SetWindowActive(_this, window);
    }
    X11_XFlush(display);
}

സ്ഥിതം bool X11_SetWindowMaximized(SDL_VideoDevice *_this, SDL_Window *window, bool maximized)
{
    CHECK_WINDOW_DATA(window);

    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        തിരികെ true;
    }

    എങ്കിൽ (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] =
            maximized ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.data.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.data.l[3] = 0l;

        എങ്കിൽ (maximized) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            data->expected.x = bounds.x + data->border_ഇടത്;
            data->expected.y = bounds.y + data->border_മുകൾ;
            data->expected.w = bounds.w - (data->border_ഇടത് + data->border_വലത്);
            data->expected.h = bounds.h - (data->border_മുകൾ + data->border_bottom);
        } അല്ലെങ്കിൽ {
            data->expected.x = window->floating.x;
            data->expected.y = window->floating.y;
            data->expected.w = window->floating.w;
            data->expected.h = window->floating.h;
        }

        X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } അല്ലെങ്കിൽ {
        X11_SetNetWMState(_this, data->xwindow, window->flags);
    }
    X11_XFlush(display);

    തിരികെ true;
}

ശൂന്യം X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        window->internal->window_was_maximized = true;
        തിരികെ;
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        window->internal->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_SetWindowMaximized(_this, window, true);
    }
}

ശൂന്യം X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;

    എങ്കിൽ (data->pending_operation & SDL_WINDOW_FULLSCREEN) {
        SDL_SyncWindow(window);
    }

    data->pending_operation |= X11_PENDING_OP_MINIMIZE;
    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        data->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
    }
    X11_XIconifyWindow(display, data->xwindow, displaydata->screen);
    X11_XFlush(display);
}

ശൂന്യം X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Don't restore the window the first time it is being shown.
    എങ്കിൽ (!window->internal->was_shown) {
        തിരികെ;
    }

    എങ്കിൽ (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    എങ്കിൽ ((window->flags & SDL_WINDOW_FULLSCREEN) && !(window->flags & SDL_WINDOW_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        window->internal->window_was_maximized = false;
        തിരികെ;
    }

    എങ്കിൽ (window->flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED) ||
        (window->internal->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        window->internal->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    സ്ഥിരം bool maximize = !!(window->flags & SDL_WINDOW_MINIMIZED) && window->internal->window_was_maximized;
    X11_SetWindowMaximized(_this, window, maximize);
    X11_ShowWindow(_this, window);
    X11_SetWindowActive(_this, window);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
സ്ഥിതം SDL_FullscreenResult X11_SetWindowFullscreenViaWM(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = _display->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = data->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    എങ്കിൽ (!data->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        തിരികെ SDL_FULLSCREEN_SUCCEEDED;
    }

    എങ്കിൽ (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // Flush any pending fullscreen events.
        എങ്കിൽ (data->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_SyncWindow(_this, window);
        }

        എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            എങ്കിൽ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                തിരികെ SDL_FULLSCREEN_FAILED;
            } അല്ലെങ്കിൽ എങ്കിൽ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                തിരികെ SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        എങ്കിൽ (fullscreen && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAllocSizeHints();
            long flags = 0;
            X11_XGetWMNormalHints(display, data->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMinSize | PMaxSize | PAspect);
            X11_XSetWMNormalHints(display, data->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] =
            fullscreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.data.l[3] = 0l;

        X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        എങ്കിൽ (((window->flags & SDL_WINDOW_FULLSCREEN) != 0) != (fullscreen != 0)) {
            data->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        എങ്കിൽ (fullscreen) {
            SDL_DisplayID current = SDL_GetDisplayForWindowPosition(window);
            SDL_copyp(&data->requested_fullscreen_mode, &window->current_fullscreen_mode);
            എങ്കിൽ (fullscreen != !!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
            }
            data->expected.x = displaydata->x;
            data->expected.y = displaydata->y;
            data->expected.w = _display->current_mode->w;
            data->expected.h = _display->current_mode->h;

            // Only move the window if it isn't already on the target display.
            എങ്കിൽ (!current || current != _display->id) {
                X11_XMoveWindow(display, data->xwindow, displaydata->x, displaydata->y);
                data->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } അല്ലെങ്കിൽ {
            SDL_zero(data->requested_fullscreen_mode);
            data->pending_position = data->fs_repositioned;
            data->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = ClientMessage;
            e.xclient.message_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.window = data->xwindow;
            എങ്കിൽ (data->window_was_maximized) {
                e.xclient.data.l[0] = _NET_WM_STATE_ADD;
            } അല്ലെങ്കിൽ {
                e.xclient.data.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.data.l[1] = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.data.l[2] = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.data.l[3] = 0l;
            X11_XSendEvent(display, വേര്_Window(display, displaydata->screen), 0,
                           SubstructureNotifyMask | SubstructureRedirectMask, &e);
        }
    } അല്ലെങ്കിൽ {
        SDL_WindowFlags flags;

        flags = window->flags;
        എങ്കിൽ (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } അല്ലെങ്കിൽ {
            flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        X11_SetNetWMState(_this, data->xwindow, flags);
    }

    എങ്കിൽ (data->visual->class == DirectColor) {
        എങ്കിൽ (fullscreen) {
            X11_XInstallColormap(display, data->colormap);
        } അല്ലെങ്കിൽ {
            X11_XUninstallColormap(display, data->colormap);
        }
    }

    തിരികെ SDL_FULLSCREEN_PENDING;
}

സ്ഥിതം SDL_FullscreenResult X11_SetWindowFullscreenLegacy(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = _display->internal;
    Display *display = data->videodata->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ screen = displaydata->screen;

    എങ്കിൽ (!data->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        തിരികെ SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    എങ്കിൽ (data->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_SyncWindow(_this, window);
    }

    // No window manager? Just make the window the size of the display.
    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    എങ്കിൽ (fullscreen) {
        എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAllocSizeHints();
            long flags = 0;
            X11_XGetWMNormalHints(display, data->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMinSize | PMaxSize | PAspect);
            X11_XSetWMNormalHints(display, data->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SetWindowBordered(display, screen, data->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        data->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        data->expected.x = rect.x;
        data->expected.y = rect.y;
        data->expected.w = rect.w;
        data->expected.h = rect.h;
        X11_XMoveWindow(display, data->xwindow, rect.x, rect.y);
        X11_XResizeWindow(display, data->xwindow, rect.w, rect.h);
        X11_XRaiseWindow(display, data->xwindow);
    } അല്ലെങ്കിൽ {
        data->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        data->expected.x = window->windowed.x;
        data->expected.y = window->windowed.y;
        data->expected.w = window->windowed.w;
        data->expected.h = window->windowed.h;
        X11_XResizeWindow(display, data->xwindow, window->windowed.w, window->windowed.h);
        X11_XMoveWindow(display, data->xwindow, window->windowed.x, window->windowed.y);

        SetWindowBordered(display, screen, data->xwindow, (window->flags & SDL_WINDOW_BORDERLESS) == 0);
        X11_SetWindowMinMax(data->window, false);
    }

    X11_XFlush(display);

    തിരികെ SDL_FULLSCREEN_PENDING;
}

SDL_FullscreenResult X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_WINDOW_DATA(window);
    CHECK_DISPLAY_DATA(_display);

    SDL_VideoData *data = _this->internal;
    എങ്കിൽ (data->net_wm) {
        തിരികെ X11_SetWindowFullscreenViaWM(_this, window, _display, fullscreen);
    }

    തിരികെ X11_SetWindowFullscreenLegacy(_this, window, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

തരനിർവചനം ഘടന
{
    unsigned അക്ഷരം *data;
    പൂർണ്ണസംഖ്യ format, എണ്ണം;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
സ്ഥിതം ശൂന്യം X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned അക്ഷരം *ret = ശൂന്യ;
    Atom type;
    പൂർണ്ണസംഖ്യ fmt;
    unsigned long എണ്ണം;
    unsigned long bytes_ഇടത്;
    പൂർണ്ണസംഖ്യ bytes_fetch = 0;

    ചെയ്യുക {
        എങ്കിൽ (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &എണ്ണം, &bytes_ഇടത്, &ret);
        bytes_fetch += bytes_ഇടത്;
    } ആകുമ്പോൾ (bytes_ഇടത് != 0);

    p->data = ret;
    p->format = fmt;
    p->എണ്ണം = എണ്ണം;
    p->type = type;
}

ശൂന്യം *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XWindowAttributes attributes;
    Atom icc_profile_atom;
    അക്ഷരം icc_atom_string[വലുപ്പം("_ICC_PROFILE_") + 12];
    ശൂന്യം *ret_icc_profile_data = ശൂന്യ;
    CARD8 *icc_profile_data;
    പൂർണ്ണസംഖ്യ real_format;
    unsigned long real_nitems;
    SDL_x11Prop atomProp;

    X11_XGetWindowAttributes(display, data->xwindow, &attributes);
    എങ്കിൽ (X11_XScreen_സംഖ്യ_Of_Screen(attributes.screen) > 0) {
        (ശൂന്യം)SDL_snprintf(icc_atom_string, വലുപ്പം("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_സംഖ്യ_Of_Screen(attributes.screen));
    } അല്ലെങ്കിൽ {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", വലുപ്പം("_ICC_PROFILE"));
    }
    X11_XGetWindowAttributes(display, വേര്_Window_Of_Screen(attributes.screen), &attributes);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    എങ്കിൽ (icc_profile_atom == None) {
        SDL_SetError("Screen is not calibrated.");
        തിരികെ ശൂന്യ;
    }

    X11_ReadProperty(&atomProp, display, വേര്_Window_Of_Screen(attributes.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.എണ്ണം;
    icc_profile_data = atomProp.data;
    എങ്കിൽ (real_format == None) {
        SDL_SetError("Screen is not calibrated.");
        തിരികെ ശൂന്യ;
    }

    ret_icc_profile_data = SDL_malloc(real_nitems);
    എങ്കിൽ (!ret_icc_profile_data) {
        തിരികെ ശൂന്യ;
    }

    SDL_memcpy(ret_icc_profile_data, icc_profile_data, real_nitems);
    *size = real_nitems;
    X11_XFree(icc_profile_data);

    തിരികെ ret_icc_profile_data;
}

bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    എങ്കിൽ (!data) {
        തിരികെ SDL_SetError("Invalid window data");
    }
    data->mouse_grabbed = false;
    data->pending_grab = false;

    display = data->videodata->display;

    എങ്കിൽ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
            തിരികെ true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        എങ്കിൽ (data->xinput2_mouse_enabled && SDL_GetMouseState(ശൂന്യ, ശൂന്യ)) {
            data->pending_grab = true;
            തിരികെ true;
        }

        // Try to grab the mouse
        എങ്കിൽ (!data->videodata->broken_pointer_grab) {
            സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            പൂർണ്ണസംഖ്യ attempts;
            പൂർണ്ണസംഖ്യ result = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            വേണ്ടി (attempts = 0; attempts < 100; attempts++) {
                result = X11_XGrabPointer(display, data->xwindow, False, mask, GrabModeAsync,
                                          GrabModeAsync, data->xwindow, None, CurrentTime);
                എങ്കിൽ (result == GrabSuccess) {
                    data->mouse_grabbed = true;
                    നിർത്തുക;
                }
                SDL_Delay(50);
            }

            എങ്കിൽ (result != GrabSuccess) {
                data->videodata->broken_pointer_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, window);

        // Raise the window if we grab the mouse
        X11_XRaiseWindow(display, data->xwindow);
    } അല്ലെങ്കിൽ {
        X11_XUngrabPointer(display, CurrentTime);

        X11_Xinput2UngrabTouch(_this, window);
    }
    X11_XSync(display, False);

    എങ്കിൽ (!data->videodata->broken_pointer_grab) {
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    എങ്കിൽ (!data) {
        തിരികെ SDL_SetError("Invalid window data");
    }

    display = data->videodata->display;

    എങ്കിൽ (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
            തിരികെ true;
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
        എങ്കിൽ (_this->internal->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            എങ്കിൽ (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClientMessageEvent client_message;
                client_message.type = ClientMessage;
                client_message.window = data->xwindow;
                client_message.format = 32;
                client_message.message_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_message.data.l[0] = 1;
                client_message.data.l[1] = CurrentTime;

                X11_XSendEvent(display, Default_വേര്_Window(display), False, SubstructureNotifyMask | SubstructureRedirectMask, (XEvent *)&client_message);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, data->xwindow, True, GrabModeAsync,
                          GrabModeAsync, CurrentTime);
    } അല്ലെങ്കിൽ {
        X11_XUngrabKeyboard(display, CurrentTime);
    }
    X11_XSync(display, False);

    തിരികെ true;
}

ശൂന്യം X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        പൂർണ്ണസംഖ്യ numwindows = videodata->numwindows;
        SDL_WindowData **windowlist = videodata->windowlist;
        പൂർണ്ണസംഖ്യ i;

        എങ്കിൽ (windowlist) {
            വേണ്ടി (i = 0; i < numwindows; ++i) {
                എങ്കിൽ (windowlist[i] && (windowlist[i]->window == window)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = ശൂന്യ;
                    videodata->numwindows--;
                    നിർത്തുക;
                }
            }
        }

        X11_Destroy_നിവേശം_Context(data);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_TermResizeSync(window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            X11_XDestroyWindow(display, data->xwindow);
            X11_XFlush(display);
        }
        SDL_free(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        എങ്കിൽ (videodata->active_cursor_confined_window == window) {
            X11_DestroyPointerBarrier(_this, window);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    window->internal = ശൂന്യ;
}

bool X11_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    തിരികെ true; // just succeed, the real work is done elsewhere.
}

ശൂന്യം X11_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom XdndAware = data->videodata->atoms.XdndAware;

    എങ്കിൽ (accept) {
        Atom xdnd_version = 5;
        X11_XChangeProperty(display, data->xwindow, XdndAware, XA_ATOM, 32,
                            PropModeReplace, (unsigned അക്ഷരം *)&xdnd_version, 1);
    } അല്ലെങ്കിൽ {
        X11_XDeleteProperty(display, data->xwindow, XdndAware);
    }
}

bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, data->xwindow);
    എങ്കിൽ (!wmhints) {
        തിരികെ SDL_SetError("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    data->flashing_window = false;
    data->flash_cancel_time = 0;

    തിരഞ്ഞെടുപ്പ് (operation) {
    അവസ്ഥ SDL_FLASH_CANCEL:
        // Taken care of above
        നിർത്തുക;
    അവസ്ഥ SDL_FLASH_BRIEFLY:
        എങ്കിൽ (!(window->flags & SDL_WINDOW_നിവേശം_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            data->flashing_window = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            data->flash_cancel_time = SDL_GetTicks() + 1000;
        }
        നിർത്തുക;
    അവസ്ഥ SDL_FLASH_UNTIL_FOCUSED:
        എങ്കിൽ (!(window->flags & SDL_WINDOW_നിവേശം_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            data->flashing_window = true;
        }
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }

    X11_XSetWMHints(display, data->xwindow, wmhints);
    X11_XFree(wmhints);
    തിരികെ true;
}

bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, അക്ഷരം *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    പൂർണ്ണസംഖ്യ conv = X11_XmbTextListToTextProperty(display, &title, 1, XTextStyle, &titleprop);
    Status status;

    എങ്കിൽ (X11_XSupportsLocale() != True) {
        തിരികെ SDL_SetError("Current locale not supported by X server, cannot continue.");
    }

    എങ്കിൽ (conv == 0) {
        X11_XSetTextProperty(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.മൂല്യം);
        // we know this can't be a locale error as we checked X locale validity
    } അല്ലെങ്കിൽ എങ്കിൽ (conv < 0) {
        തിരികെ SDL_OutOfMemory();
    } അല്ലെങ്കിൽ { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        തിരികെ true;
    }

#ifdef X_HAVE_UTF8_STRING
    status = X11_Xutf8TextListToTextProperty(display, &title, 1, XUTF8StringStyle, &titleprop);
    എങ്കിൽ (status == Success) {
        X11_XSetTextProperty(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.മൂല്യം);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#endif

    X11_XFlush(display);
    തിരികെ true;
}

ശൂന്യം X11_ShowWindowSystemMenu(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Window വേര് = വേര്_Window(display, displaydata->screen);
    XClientMessageEvent e;
    Window childReturn;
    പൂർണ്ണസംഖ്യ wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, data->xwindow, വേര്, x, y, &wx, &wy, &childReturn);

    e.type = ClientMessage;
    e.window = data->xwindow;
    e.message_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.data.l[0] = 0;  // GTK device ID (unused)
    e.data.l[1] = wx; // X coordinate relative to root
    e.data.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, വേര്, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    എങ്കിൽ ((window->flags & SDL_WINDOW_EXTERNAL) &&
        (data->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(window);
            തിരികെ true;
    }

    സ്ഥിരം Uint64 current_time = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
        എങ്കിൽ (_this->displays[i]->internal->mode_switch_deadline_ns &&
            current_time < _this->displays[i]->internal->mode_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->internal->mode_switch_deadline_ns - current_time, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += window->internal->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_TO_NS(1000) : SDL_MS_TO_NS(100);

    തിരികെ X11_SyncWindowTimeout(_this, window, timeout);
}

bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        Display *display = data->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, data->xwindow);
        എങ്കിൽ (!wmhints) {
            തിരികെ SDL_SetError("Couldn't get WM hints");
        }

        wmhints->നിവേശം = focusable ? True : False;
        wmhints->flags |= നിവേശം_Hint;

        X11_XSetWMHints(display, data->xwindow, wmhints);
        X11_XFree(wmhints);
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_POPUP_MENU) {
        എങ്കിൽ (!(window->flags & SDL_WINDOW_HIDDEN)) {
            എങ്കിൽ (!focusable && (window->flags & SDL_WINDOW_നിവേശം_FOCUS)) {
                SDL_Window *new_focus;
                സ്ഥിരം bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                X11_SetKeyboardFocus(new_focus, set_focus);
            } അല്ലെങ്കിൽ എങ്കിൽ (focusable) {
                എങ്കിൽ (SDL_ShouldFocusPopup(window)) {
                    X11_SetKeyboardFocus(window, true);
                }
            }
        }

        തിരികെ true;
    }

    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_X11
