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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../core/unix/SDL_appid.h"

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11mouse.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "SDL_x11xfixes.h"

#ifdef SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "SDL_x11opengles.h"
#endif

#अन्तर्भाव "SDL_x11xsync.h"

#define _NET_WM_STATE_REMOVE 0l
#define _NET_WM_STATE_ADD    1l

#define CHECK_WINDOW_DATA(window)                                       \
    सचे (!window) {                                                      \
        पटिनिवत्त SDL_SetError("Invalid window");                          \
    }                                                                   \
    सचे (!window->internal) {                                          \
        पटिनिवत्त SDL_SetError("Invalid window driver data");              \
    }

#define CHECK_DISPLAY_DATA(display)                                     \
    सचे (!_display) {                                                    \
        पटिनिवत्त SDL_SetError("Invalid display");                         \
    }                                                                   \
    सचे (!_display->internal) {                                        \
        पटिनिवत्त SDL_SetError("Invalid display driver data");             \
    }

स्थिर Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    पटिनिवत्त ev->type == MapNotify && ev->xmap.window == *((Window *)win);
}
स्थिर Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    पटिनिवत्त ev->type == UnmapNotify && ev->xunmap.window == *((Window *)win);
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

स्थिर bool X11_CheckCurrentDesktop(ध्रुव वर्ण *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ध्रुव वर्ण *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    सचे (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        पटिनिवत्त true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    सचे (desktopVar && SDL_strcasestr(desktopVar, name)) {
        पटिनिवत्त true;
    }

    पटिनिवत्त false;
}

स्थिर bool X11_IsWindowMapped(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_VideoData *videodata = _this->internal;
    XWindowAttributes attr;

    X11_XGetWindowAttributes(videodata->display, data->xwindow, &attr);
    सचे (attr.map_state != IsUnmapped) {
        पटिनिवत्त true;
    } अञ्ञथा {
        पटिनिवत्त false;
    }
}

स्थिर bool X11_IsDisplayOk(Display *display)
{
    सचे (display->flags & XlibDisplayIOError) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

#सचे 0
स्थिर bool X11_IsActionAllowed(SDL_Window *window, Atom action)
{
    SDL_WindowData *data = window->internal;
    Atom _NET_WM_ALLOWED_ACTIONS = data->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = data->videodata->display;
    पूर्णाङ्क form;
    unsigned long remain;
    unsigned long len, i;
    Atom *list;
    bool ret = false;

    सचे (X11_XGetWindowProperty(display, data->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (unsigned वर्ण **)&list) == Success) {
        अत्थाय (i=0; i<len; ++i) {
            सचे (list[i] == action) {
                ret = true;
                भङ्ग;
            }
        }
        X11_XFree(list);
    }
    पटिनिवत्त ret;
}
#endif // 0

स्थिर शून्य X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ध्रुव bool last_position_pending = window->last_position_pending;
    ध्रुव bool last_size_pending = window->last_size_pending;

    X11_SyncWindow(_this, window);

    window->last_position_pending = last_position_pending;
    window->last_size_pending = last_size_pending;
}

शून्य X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags)
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
    पूर्णाङ्क गणनम् = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    सचे (flags & SDL_WINDOW_ALWAYS_ON_शिखरम्) {
        atoms[गणनम्++] = _NET_WM_STATE_ABOVE;
    }
    सचे (flags & SDL_WINDOW_UTILITY) {
        atoms[गणनम्++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[गणनम्++] = _NET_WM_STATE_SKIP_PAGER;
    }
    सचे (flags & SDL_WINDOW_निवेशः_FOCUS) {
        atoms[गणनम्++] = _NET_WM_STATE_FOCUSED;
    }
    सचे (flags & SDL_WINDOW_MAXIMIZED) {
        atoms[गणनम्++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[गणनम्++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    सचे (flags & SDL_WINDOW_FULLSCREEN) {
        atoms[गणनम्++] = _NET_WM_STATE_FULLSCREEN;
    }
    सचे (flags & SDL_WINDOW_MODAL) {
        atoms[गणनम्++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(गणनम् <= SDL_arraysize(atoms));

    सचे (गणनम् > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned वर्ण *)atoms, गणनम्);
    } अञ्ञथा {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

स्थिर शून्य X11_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Clamp popup windows to the output borders
    सचे (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णाङ्क abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        पूर्णाङ्क abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        पूर्णाङ्क offset_x = 0, offset_y = 0;

        सचे (window->constrain_popup) {
            // Calculate the total offset from the parents
            अत्थाय (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
                offset_x += w->x;
                offset_y += w->y;
            }

            offset_x += w->x;
            offset_y += w->y;
            abs_x += offset_x;
            abs_y += offset_y;

            displayID = SDL_GetDisplayForWindow(w);

            SDL_GetDisplayBounds(displayID, &rect);
            सचे (abs_x + window->w > rect.x + rect.w) {
                abs_x -= (abs_x + window->w) - (rect.x + rect.w);
            }
            सचे (abs_y + window->h > rect.y + rect.h) {
                abs_y -= (abs_y + window->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        सचे (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
        } अञ्ञथा {
            window->floating.x = window->windowed.x = abs_x - offset_x;
            window->floating.y = window->windowed.y = abs_y - offset_y;
        }
    }
}

स्थिर शून्य X11_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    याव (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    सचे (set_active_focus && !window->is_hiding && !window->is_destroying) {
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
    पूर्णाङ्क actualFormat;
    unsigned long i, अङ्कः_वस्तूनि, bytesAfter;
    unsigned वर्ण *property_मानम् = रिक्त;
    long maxLength = 1024;
    SDL_WindowFlags flags = 0;

    सचे (X11_XGetWindowProperty(display, xwindow, _NET_WM_STATE,
                               0l, maxLength, False, XA_ATOM, &actualType,
                               &actualFormat, &अङ्कः_वस्तूनि, &bytesAfter,
                               &property_मानम्) == Success) {
        Atom *atoms = (Atom *)property_मानम्;
        पूर्णाङ्क maximized = 0;
        पूर्णाङ्क fullscreen = 0;

        अत्थाय (i = 0; i < अङ्कः_वस्तूनि; ++i) {
            सचे (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_WINDOW_MINIMIZED | SDL_WINDOW_OCCLUDED;
            } अञ्ञथा सचे (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_WINDOW_निवेशः_FOCUS;
            } अञ्ञथा सचे (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } अञ्ञथा सचे (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } अञ्ञथा सचे (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        सचे (fullscreen == 1) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } अञ्ञथा सचे (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (window->flags & SDL_WINDOW_FULLSCREEN);
        }

        सचे (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            सचे (fullscreen) {
                flags |= (window->flags & SDL_WINDOW_MAXIMIZED);
            } अञ्ञथा {
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
            सचे (attr.map_state == IsUnmapped) {
                flags |= SDL_WINDOW_HIDDEN;
            }
        }
        X11_XFree(property_मानम्);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    पटिनिवत्त flags;
}

स्थिर bool SetupWindowData(SDL_VideoDevice *_this, SDL_Window *window, Window w)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    SDL_WindowData *data;

    // Allocate the window data
    data = (SDL_WindowData *)SDL_calloc(1, परिमाण(*data));
    सचे (!data) {
        पटिनिवत्त false;
    }
    data->videodata = videodata;
    data->window = window;
    data->xwindow = w;
    data->hit_test_result = SDL_HITTEST_NORMAL;

    X11_Create_निवेशः_Context(data);

    // Associate the data with the window

    सचे (videodata->numwindows >= videodata->windowlistlength) {
        SDL_WindowData ** new_windowlist = (SDL_WindowData **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * परिमाण(*videodata->windowlist));
        सचे (!new_windowlist) {
            गच्छ error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindowAttributes attrib;

        X11_XGetWindowAttributes(data->videodata->display, w, &attrib);
        सचे (!SDL_WINDOW_IS_POPUP(window)) {
            window->x = window->windowed.x = window->floating.x = attrib.x;
            window->y = window->windowed.y = window->floating.y = attrib.y - data->border_शिखरम्;
        }
        window->w = window->windowed.w = window->floating.w = attrib.width;
        window->h = window->windowed.h = window->floating.h = attrib.height;
        सचे (attrib.map_state != IsUnmapped) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } अञ्ञथा {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        data->visual = attrib.visual;
        data->colormap = attrib.colormap;
    }

    window->flags |= X11_GetNetWMState(_this, window, w);

    {
        Window FocalWindow;
        पूर्णाङ्क RevertTo = 0;
        X11_XGet_निवेशः_Focus(data->videodata->display, &FocalWindow, &RevertTo);
        सचे (FocalWindow == w) {
            window->flags |= SDL_WINDOW_निवेशः_FOCUS;
        }

        सचे (window->flags & SDL_WINDOW_निवेशः_FOCUS) {
            SDL_SetKeyboardFocus(data->window);
        }

        सचे (window->flags & SDL_WINDOW_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    सचे (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        window->title = X11_GetWindowTitle(_this, w);
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    पूर्णाङ्क screen = (displaydata ? displaydata->screen : 0);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, data->videodata->display);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_X11_SCREEN_सङ्ख्या, screen);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_X11_WINDOW_सङ्ख्या, data->xwindow);


#सचे defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    सचे ((window->flags & SDL_WINDOW_OPENGL) &&
        ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_data || X11_GL_UseEGL(_this))
#endif
    ) {
#ifdef SDL_VIDEO_OPENGL_EGL
        सचे (!_this->egl_data) {
            गच्छ error_cleanup;
        }

        // Create the GLES window surface
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)w);

        सचे (data->egl_surface == EGL_NO_SURFACE) {
            SDL_SetError("Could not create GLES window surface");
            गच्छ error_cleanup;
        }
#अञ्ञथा
        SDL_SetError("Could not create GLES window surface (EGL support not configured)");
        गच्छ error_cleanup;
#endif // SDL_VIDEO_OPENGL_EGL
    }
#endif

    // All done!
    window->internal = data;
    videodata->windowlist[videodata->numwindows++] = data;
    पटिनिवत्त true;

error_cleanup:
    X11_Destroy_निवेशः_Context(data);
    SDL_free(data);
    पटिनिवत्त false;
}

स्थिर शून्य Setup_Window_निवेशः(SDL_VideoDevice *_this, SDL_Window *window)
{
    long fevent = 0;
    SDL_WindowData *data = window->internal;
    Window xwindow = data->xwindow;

#ifdef X_HAVE_UTF8_STRING
    सचे (SDL_X11_HAVE_UTF8 && data->ic) {
        X11_XGetICValues(data->ic, XNFilterEvents, &fevent, रिक्त);
    }
#endif

    X11_Xinput2Select(_this, window);

    {
        unsigned पूर्णाङ्क x11_keyboard_events = कुञ्चिका_Press_Mask | कुञ्चिका_Release_Mask;
        unsigned पूर्णाङ्क x11_pointer_events = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

        X11_Xinput2SelectMouseAndKeyboard(_this, window);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        सचे (data->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        सचे (data->xinput2_mouse_enabled) {
            x11_pointer_events = 0;
        }

        X11_XSelect_निवेशः(data->videodata->display, xwindow,
                         (FocusChangeMask | EnterWindowMask | LeaveWindowMask | ExposureMask |
                          x11_keyboard_events | x11_pointer_events |
                          PropertyChangeMask | StructureNotifyMask |
                          KeymapStateMask | fevent));
    }
}

स्थिर शून्य SetWindowBordered(Display *display, पूर्णाङ्क screen, Window window, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    सचे (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        संरचना
        {
            unsigned long flags;
            unsigned long functions;
            unsigned long decorations;
            long निवेशः_mode;
            unsigned long status;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, window, WM_HINTS, WM_HINTS, 32,
                            PropModeReplace, (unsigned वर्ण *)&MWMHints,
                            परिमाण(MWMHints) / परिमाण(long));
    } अञ्ञथा { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, window, मूलम्_Window(display, screen));
    }
}

bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    Window w = (Window)SDL_Get_सङ्ख्या_Property(create_props, SDL_PROP_WINDOW_CREATE_X11_WINDOW_सङ्ख्या,
                (Window)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    सचे (w) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        सचे (!SetupWindowData(_this, window, w)) {
            पटिनिवत्त false;
        }

        सचे (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_WINDOW_निवेशः, true)) {
            Setup_Window_निवेशः(_this, window);
        }
        पटिनिवत्त true;
    }

    SDL_VideoData *data = _this->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    सचे (!displaydata) {
        पटिनिवत्त SDL_SetError("Could not find display info");
    }

    ध्रुव bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ध्रुव bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (window->flags & SDL_WINDOW_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_WindowData *windowdata;
    Display *display = data->display;
    पूर्णाङ्क screen = displaydata->screen;
    Visual *visual;
    पूर्णाङ्क depth;
    XSetWindowAttributes xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom _NET_WM_WINDOW_TYPE;
    Atom wintype;
    ध्रुव वर्ण *wintype_name = रिक्त;
    long compositor = 1;
    Atom _NET_WM_PID;
    ध्रुव वर्ण *hint = रिक्त;
    पूर्णाङ्क win_x, win_y;
    bool undefined_position = false;

#सचे defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ध्रुव पूर्णाङ्क transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    ध्रुव वर्ण *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    ध्रुव वर्ण *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    सचे (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, template;
        पूर्णाङ्क nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(forced_visual_id, रिक्त, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        सचे (vi) {
            visual = vi->visual;
            depth = vi->depth;
            X11_XFree(vi);
        } अञ्ञथा {
            पटिनिवत्त false;
        }
    } अञ्ञथा सचे ((window->flags & SDL_WINDOW_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = रिक्त;

#ifdef SDL_VIDEO_OPENGL_EGL
        सचे (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_data || X11_GL_UseEGL(_this))
#endif
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } अञ्ञथा
#endif
        {
#ifdef SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#endif
        }

        सचे (!vinfo) {
            पटिनिवत्त false;
        }
        visual = vinfo->visual;
        depth = vinfo->depth;
        X11_XFree(vinfo);
    } अञ्ञथा
#endif
    {
        visual = displaydata->visual;
        depth = displaydata->depth;
    }

    xattr.override_redirect = ((window->flags & SDL_WINDOW_TOOLTIP) || (window->flags & SDL_WINDOW_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    सचे (visual->class == DirectColor) {
        XColor *colorcells;
        पूर्णाङ्क i;
        पूर्णाङ्क ncolors;
        पूर्णाङ्क rmax, gmax, bmax;
        पूर्णाङ्क rmask, gmask, bmask;
        पूर्णाङ्क rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, मूलम्_Window(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        सचे (!xattr.colormap) {
            पटिनिवत्त SDL_SetError("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * परिमाण(XColor));
        सचे (!colorcells) {
            पटिनिवत्त false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_mask;
        याव (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_mask;
        याव (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_mask;
        याव (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        अत्थाय (i = 0; i < ncolors; i++) {
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
    } अञ्ञथा {
        xattr.colormap =
            X11_XCreateColormap(display, मूलम्_Window(display, screen),
                                visual, AllocNone);
    }

    सचे (window->undefined_x && window->undefined_y &&
        window->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    सचे (SDL_WINDOW_IS_POPUP(window)) {
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
    w = X11_XCreateWindow(display, मूलम्_Window(display, screen),
                          win_x, win_y, window->floating.w, window->floating.h,
                          0, depth, निवेशः_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    सचे (!w) {
        पटिनिवत्त SDL_SetError("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    सचे (!(window->pending_flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, screen, w, !(window->flags & SDL_WINDOW_BORDERLESS));
    }

    sizehints = X11_XAllocSizeHints();
    // Setup the normal size hints
    sizehints->flags = 0;
    सचे (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        sizehints->min_width = sizehints->max_width = window->floating.w;
        sizehints->min_height = sizehints->max_height = window->floating.h;
        sizehints->flags |= (PMaxSize | PMinSize);
    }
    सचे (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->निवेशः = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) ? True : False;
    wmhints->window_group = data->window_group;
    wmhints->flags = निवेशः_Hint | WindowGroupHint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (वर्ण *)SDL_GetExeName();
    classhints->res_class = (वर्ण *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, रिक्त, रिक्त, रिक्त, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    सचे (data->pid > 0) {
        long pid = (long)data->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, PropModeReplace,
                            (unsigned वर्ण *)&pid, 1);
    }

    // Set the window manager state
    X11_SetNetWMState(_this, w, window->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_WINDOW_TYPE);
    सचे (window->flags & SDL_WINDOW_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } अञ्ञथा सचे (hint && *hint) {
        wintype_name = hint;
    } अञ्ञथा {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                        PropModeReplace, (unsigned वर्ण *)&wintype, 1);
    सचे (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            PropModeReplace,
                            (unsigned वर्ण *)&compositor, 1);
    }

    {
        Atom protocols[4];
        पूर्णाङ्क proto_गणनम् = 0;

        protocols[proto_गणनम्++] = data->atoms.WM_DELETE_WINDOW; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        सचे (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_गणनम्++] = data->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        सचे (use_resize_sync) {
            protocols[proto_गणनम्++] = data->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_गणनम् <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_गणनम्);
    }

    सचे (!SetupWindowData(_this, window, w)) {
        X11_XDestroyWindow(display, w);
        पटिनिवत्त false;
    }
    windowdata = window->internal;

    // Set the parent if this is a non-popup window.
    सचे (!SDL_WINDOW_IS_POPUP(window) && window->parent) {
        X11_XSetTransientForHint(display, w, window->parent->internal->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(window->pending_flags & SDL_WINDOW_FULLSCREEN) &&
                                               !!(window->flags & SDL_WINDOW_BORDERLESS);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    सचे (use_resize_sync) {
        X11_InitResizeSync(window);
    }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    सचे (window->flags & SDL_WINDOW_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_निवेशः, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
    }
#endif

    Setup_Window_निवेशः(_this, window);

    // For _ICC_PROFILE.
    X11_XSelect_निवेशः(display, मूलम्_Window(display, screen), PropertyChangeMask);

    X11_XFlush(display);

    पटिनिवत्त true;
}

वर्ण *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    पूर्णाङ्क status, real_format;
    Atom real_type;
    unsigned long वस्तूनि_read, वस्तूनि_वामः;
    unsigned वर्ण *propdata;
    वर्ण *title = रिक्त;

    status = X11_XGetWindowProperty(display, xwindow, data->atoms._NET_WM_NAME,
                                    0L, 8192L, False, data->atoms.UTF8_STRING, &real_type, &real_format,
                                    &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
    सचे (status == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(वर्ण *, propdata));
        X11_XFree(propdata);
    } अञ्ञथा {
        status = X11_XGetWindowProperty(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
        सचे (status == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(वर्ण *, propdata), वस्तूनि_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } अञ्ञथा {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    पटिनिवत्त title;
}

शून्य X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Window xwindow = data->xwindow;
    Display *display = data->videodata->display;
    वर्ण *title = window->title ? window->title : "";

    SDL_X11_SetWindowTitle(display, xwindow, title);
}

स्थिर bool caught_x11_error = false;
स्थिर पूर्णाङ्क X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    पटिनिवत्त 0;
}

स्थिर शून्य X11_ExternalResizeMoveSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    पूर्णाङ्क (*prev_handler)(Display *, XErrorEvent *);
    unsigned पूर्णाङ्क child_गणनम्;
    Window childReturn, मूलम्, parent;
    Window *children;
    XWindowAttributes attrs;
    Uint64 timeout = 0;
    पूर्णाङ्क x, y;
    ध्रुव bool send_move = !!(data->pending_operation & X11_PENDING_OP_MOVE);
    ध्रुव bool send_resize = !!(data->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_वृक्षः(display, data->xwindow, &मूलम्, &parent, &children, &child_गणनम्);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_TO_NS(100);
    याव (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGetWindowAttributes(display, data->xwindow, &attrs);
        X11_XTranslateCoordinates(display, parent, Default_मूलम्_Window(display),
                                  attrs.x, attrs.y, &x, &y, &childReturn);
        SDL_GlobalToRelativeForWindow(window, x, y, &x, &y);

        सचे (!caught_x11_error) {
            सचे ((data->pending_operation & X11_PENDING_OP_MOVE) && (x == data->expected.x + data->border_वामः && y == data->expected.y + data->border_शिखरम्)) {
                data->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            सचे ((data->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.width == data->expected.w && attrs.height == data->expected.h)) {
                data->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            सचे (data->pending_operation == X11_PENDING_OP_NONE) {
                भङ्ग;
            }
        }

        सचे (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            data->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            data->expected.x = x;
            data->expected.y = y;
            data->expected.w = attrs.width;
            data->expected.h = attrs.height;
            भङ्ग;
        }

        SDL_Delay(10);
    }

    सचे (!caught_x11_error) {
        सचे (send_move) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
        }
        सचे (send_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, attrs.width, attrs.height);
        }
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
स्थिर bool X11_SyncWindowTimeout(SDL_VideoDevice *_this, SDL_Window *window, Uint64 param_timeout)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    पूर्णाङ्क (*prev_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool result = true;

    X11_XSync(display, False);
    prev_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    सचे (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    याव (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        सचे ((data->pending_operation & X11_PENDING_OP_MOVE) && (window->x == data->expected.x + data->border_वामः && window->y == data->expected.y + data->border_शिखरम्)) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        सचे ((data->pending_operation & X11_PENDING_OP_RESIZE) && (window->w == data->expected.w && window->h == data->expected.h)) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        सचे (data->pending_operation == X11_PENDING_OP_NONE) {
            सचे (force_exit ||
                (window->x == data->expected.x + data->border_वामः && window->y == data->expected.y + data->border_शिखरम् &&
                 window->w == data->expected.w && window->h == data->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                भङ्ग;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        सचे (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            data->expected.x = window->x;
            data->expected.y = window->y;
            data->expected.w = window->w;
            data->expected.h = window->h;

            result = false;
            भङ्ग;
        }

        SDL_Delay(10);
    }

    data->pending_operation = X11_PENDING_OP_NONE;

    सचे (!caught_x11_error) {
        X11_PumpEvents(_this);
    } अञ्ञथा {
        result = false;
    }

    X11_XSetErrorHandler(prev_handler);
    caught_x11_error = false;

    पटिनिवत्त result;
}

bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_ICON = data->videodata->atoms._NET_WM_ICON;
    पूर्णाङ्क (*prevHandler)(Display *, XErrorEvent *) = रिक्त;
    bool result = true;

    सचे (icon) {
        पूर्णाङ्क x, y;
        पूर्णाङ्क propsize;
        long *propdata;
        Uint32 *src;
        long *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * परिमाण(long));

        सचे (!propdata) {
            पटिनिवत्त false;
        }

        X11_XSync(display, False);
        prevHandler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        अत्थाय (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            अत्थाय (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, data->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, PropModeReplace, (unsigned वर्ण *)propdata,
                            propsize);
        SDL_free(propdata);

        सचे (caught_x11_error) {
            result = SDL_SetError("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    सचे (prevHandler) {
        X11_XSetErrorHandler(prevHandler);
        caught_x11_error = false;
    }

    पटिनिवत्त result;
}

शून्य X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    ध्रुव पूर्णाङ्क rel_x = use_current_position ? window->x : window->pending.x;
    ध्रुव पूर्णाङ्क rel_y = use_current_position ? window->y : window->pending.y;

    SDL_RelativeToGlobalForWindow(window,
                                  rel_x - data->border_वामः, rel_y - data->border_शिखरम्,
                                  &data->expected.x, &data->expected.y);

    // Attempt to move the window
    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        window->internal->pending_position = true;
    } अञ्ञथा {
        data->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
    }
}

bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Sync any pending fullscreen or maximize events.
    सचे (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    सचे (window->flags & SDL_WINDOW_MAXIMIZED) {
        सचे (window->internal->pending_operation & X11_PENDING_OP_RESTORE) {
            window->internal->pending_position = true;
        }
        पटिनिवत्त true;
    }

    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        सचे (SDL_WINDOW_IS_POPUP(window)) {
            X11_ConstrainPopup(window, true);
        }
        X11_UpdateWindowPosition(window, false);
    } अञ्ञथा {
        window->internal->fs_repositioned = true;
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    पटिनिवत्त true;
}

शून्य X11_SetWindowMinMax(SDL_Window *window, bool use_current)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSizeHints *sizehints = X11_XAllocSizeHints();
    long hint_flags = 0;

    X11_XGetWMNormalHints(display, data->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMinSize | PMaxSize | PAspect);

    सचे (data->window->flags & SDL_WINDOW_RESIZABLE) {
        सचे (data->window->min_w || data->window->min_h) {
            sizehints->flags |= PMinSize;
            sizehints->min_width = data->window->min_w;
            sizehints->min_height = data->window->min_h;
        }
        सचे (data->window->max_w || data->window->max_h) {
            sizehints->flags |= PMaxSize;
            sizehints->max_width = data->window->max_w;
            sizehints->max_height = data->window->max_h;
        }
        सचे (data->window->min_aspect > 0.0f || data->window->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(data->window->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(data->window->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } अञ्ञथा {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMinSize | PMaxSize;
        सचे (use_current) {
            sizehints->min_width = sizehints->max_width = window->last_size_pending ? window->pending.w : data->window->floating.w;
            sizehints->min_height = sizehints->max_height = window->last_size_pending ? window->pending.h : data->window->floating.h;
        } अञ्ञथा {
            sizehints->min_width = sizehints->max_width = window->last_size_pending ? window->pending.w : data->window->windowed.w;
            sizehints->min_height = sizehints->max_height = window->last_size_pending ? window->pending.h : data->window->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, data->xwindow, sizehints);
    X11_XFree(sizehints);
}

शून्य X11_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

शून्य X11_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

शून्य X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

शून्य X11_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    सचे (data->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the size as pending if the window is being restored.
    सचे (window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN)) {
        // New size will be set when the window is restored.
        सचे (data->pending_operation & X11_PENDING_OP_RESTORE) {
            data->pending_size = true;
        } अञ्ञथा {
            // Can't resize the window.
            window->last_size_pending = false;
        }
        पटिनिवत्त;
    }

    सचे (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAllocSizeHints();
            long userhints;
            पूर्णाङ्क dest_x, dest_y;

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
            ध्रुव पूर्णाङ्क x = window->last_position_pending ? window->pending.x : window->x;
            ध्रुव पूर्णाङ्क y = window->last_position_pending ? window->pending.y : window->y;
            SDL_RelativeToGlobalForWindow(window,
                                          x - data->border_वामः,
                                          y - data->border_शिखरम्,
                                          &dest_x, &dest_y);
            X11_XMoveWindow(display, data->xwindow, dest_x, dest_y);
            X11_XRaiseWindow(display, data->xwindow);

            X11_XFree(sizehints);
        }
    } अञ्ञथा {
        data->expected.w = window->pending.w;
        data->expected.h = window->pending.h;
        data->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResizeWindow(display, data->xwindow, data->expected.w, data->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    सचे (window->flags & SDL_WINDOW_EXTERNAL) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

bool X11_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः)
{
    SDL_WindowData *data = window->internal;

    *वामः = data->border_वामः;
    *दक्षिणः = data->border_दक्षिणः;
    *शिखरम् = data->border_शिखरम्;
    *bottom = data->border_bottom;

    पटिनिवत्त true;
}

bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_WINDOW_OPACITY = data->videodata->atoms._NET_WM_WINDOW_OPACITY;

    सचे (opacity == 1.0f) {
        X11_XDeleteProperty(display, data->xwindow, _NET_WM_WINDOW_OPACITY);
    } अञ्ञथा {
        ध्रुव Uint32 FullyOpaque = 0xFFFFFFFF;
        ध्रुव long alpha = (long)((द्विगुण)opacity * (द्विगुण)FullyOpaque);
        X11_XChangeProperty(display, data->xwindow, _NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                            PropModeReplace, (unsigned वर्ण *)&alpha, 1);
    }

    पटिनिवत्त true;
}

bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
    SDL_WindowData *data = window->internal;
    SDL_WindowData *parent_data = parent ? parent->internal : रिक्त;
    SDL_VideoData *video_data = _this->internal;
    Display *display = video_data->display;

    सचे (parent_data) {
        X11_XSetTransientForHint(display, data->xwindow, parent_data->xwindow);
    } अञ्ञथा {
        X11_XDeleteProperty(display, data->xwindow, video_data->atoms.WM_TRANSIENT_FOR);
    }

    पटिनिवत्त true;
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

    सचे (modal) {
        flags |= SDL_WINDOW_MODAL;
    } अञ्ञथा {
        flags &= ~SDL_WINDOW_MODAL;
        X11_XDeleteProperty(display, data->xwindow, video_data->atoms.WM_TRANSIENT_FOR);
    }

    सचे (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] = modal ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.data.l[3] = 0l;

        X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अञ्ञथा {
        X11_SetNetWMState(_this, data->xwindow, flags);
    }

    X11_XFlush(display);

    पटिनिवत्त true;
}

शून्य X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    ध्रुव bool focused = (window->flags & SDL_WINDOW_निवेशः_FOCUS) != 0;
    ध्रुव bool visible = !(window->flags & SDL_WINDOW_HIDDEN) && !window->is_hiding;
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    XEvent event;

    सचे (data->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, displaydata->screen, data->xwindow, bordered);
        X11_XFlush(display);

        सचे (visible) {
            XWindowAttributes attr;
            करोहि {
                X11_XSync(display, False);
                X11_XGetWindowAttributes(display, data->xwindow, &attr);
            } याव (attr.map_state != IsViewable);

            सचे (focused) {
                X11_XSet_निवेशः_Focus(display, data->xwindow, RevertToParent, CurrentTime);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&data->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&data->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_मानानि(data);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResizeWindow(display, data->xwindow, window->floating.w, window->floating.h);
        X11_XSync(display, False);
    } अञ्ञथा {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        data->toggle_borders = true;
        data->fullscreen_borders_forced_on = false;
    }
}

शून्य X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *data = window->internal;

    सचे (data->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

शून्य X11_Set_Window_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_Window *window, bool on_शिखरम्)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = data->videodata->atoms._NET_WM_STATE_ABOVE;

    सचे (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = data->xwindow;
        e.xclient.data.l[0] =
            on_शिखरम् ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.data.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.data.l[3] = 0l;

        X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अञ्ञथा {
        X11_SetNetWMState(_this, data->xwindow, window->flags);
    }
    X11_XFlush(display);
}

शून्य X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);
    bool set_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    सचे (data->was_shown) {
        X11_PumpEvents(_this);
    }

    सचे (SDL_WINDOW_IS_POPUP(window)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(window, true);
        data->pending_position = true;
        set_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (शून्य)bActivate;

    सचे (!X11_IsWindowMapped(_this, window)) {
        X11_XMapRaised(display, data->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        सचे (!(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&data->xwindow);
        }
        X11_XFlush(display);
        set_position = data->pending_position ||
                       (!(window->flags & SDL_WINDOW_BORDERLESS) && !window->undefined_x && !window->undefined_y);
    }

    सचे (!data->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_निवेशः_Focus(display, data->xwindow, RevertToNone, CurrentTime);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    सचे ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        X11_SetKeyboardFocus(window, true);
    }

    // Get some valid border values, if we haven't received them yet
    सचे (data->border_वामः == 0 && data->border_दक्षिणः == 0 && data->border_शिखरम् == 0 && data->border_bottom == 0) {
        X11_Get_Border_मानानि(data);
    }

    सचे (set_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ध्रुव पूर्णाङ्क tx = (data->pending_position ? window->pending.x : window->x) - (data->was_shown ? 0 : data->border_वामः);
        ध्रुव पूर्णाङ्क ty = (data->pending_position ? window->pending.y : window->y) - (data->was_shown ? 0 : data->border_शिखरम्);
        पूर्णाङ्क x, y;

        SDL_RelativeToGlobalForWindow(window, tx, ty, &x, &y);

        data->pending_position = false;
        X11_XMoveWindow(display, data->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    सचे (!(window->flags & SDL_WINDOW_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
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
    सचे (data->last_xconfigure.type) {
        पूर्णाङ्क x, y;
        SDL_GlobalToRelativeForWindow(data->window, data->last_xconfigure.x, data->last_xconfigure.y, &x, &y);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, data->last_xconfigure.width, data->last_xconfigure.height);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
    }
}

शून्य X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    पूर्णाङ्क screen = (displaydata ? displaydata->screen : 0);
    Display *display = data->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ध्रुव bool is_mapped = X11_IsWindowMapped(_this, window);
    X11_XWithdrawWindow(display, data->xwindow, screen);
    सचे (is_mapped && !(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&data->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    सचे ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ध्रुव bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        X11_SetKeyboardFocus(new_focus, set_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

स्थिर bool X11_SetWindowActive(SDL_VideoDevice *_this, SDL_Window *window)
{
    CHECK_WINDOW_DATA(window);

    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_ACTIVE_WINDOW = data->videodata->atoms._NET_ACTIVE_WINDOW;

    सचे (X11_IsWindowMapped(_this, window)) {
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

        X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        X11_XFlush(display);
    }
    पटिनिवत्त true;
}

शून्य X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED, true);

    X11_XRaiseWindow(display, data->xwindow);
    सचे (bActivate) {
        X11_SetWindowActive(_this, window);
    }
    X11_XFlush(display);
}

स्थिर bool X11_SetWindowMaximized(SDL_VideoDevice *_this, SDL_Window *window, bool maximized)
{
    CHECK_WINDOW_DATA(window);

    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        पटिनिवत्त true;
    }

    सचे (X11_IsWindowMapped(_this, window)) {
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

        सचे (maximized) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            data->expected.x = bounds.x + data->border_वामः;
            data->expected.y = bounds.y + data->border_शिखरम्;
            data->expected.w = bounds.w - (data->border_वामः + data->border_दक्षिणः);
            data->expected.h = bounds.h - (data->border_शिखरम् + data->border_bottom);
        } अञ्ञथा {
            data->expected.x = window->floating.x;
            data->expected.y = window->floating.y;
            data->expected.w = window->floating.w;
            data->expected.h = window->floating.h;
        }

        X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अञ्ञथा {
        X11_SetNetWMState(_this, data->xwindow, window->flags);
    }
    X11_XFlush(display);

    पटिनिवत्त true;
}

शून्य X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    सचे (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        window->internal->window_was_maximized = true;
        पटिनिवत्त;
    }

    सचे (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        window->internal->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_SetWindowMaximized(_this, window, true);
    }
}

शून्य X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;

    सचे (data->pending_operation & SDL_WINDOW_FULLSCREEN) {
        SDL_SyncWindow(window);
    }

    data->pending_operation |= X11_PENDING_OP_MINIMIZE;
    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        data->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
    }
    X11_XIconifyWindow(display, data->xwindow, displaydata->screen);
    X11_XFlush(display);
}

शून्य X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Don't restore the window the first time it is being shown.
    सचे (!window->internal->was_shown) {
        पटिनिवत्त;
    }

    सचे (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    सचे ((window->flags & SDL_WINDOW_FULLSCREEN) && !(window->flags & SDL_WINDOW_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        window->internal->window_was_maximized = false;
        पटिनिवत्त;
    }

    सचे (window->flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED) ||
        (window->internal->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        window->internal->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ध्रुव bool maximize = !!(window->flags & SDL_WINDOW_MINIMIZED) && window->internal->window_was_maximized;
    X11_SetWindowMaximized(_this, window, maximize);
    X11_ShowWindow(_this, window);
    X11_SetWindowActive(_this, window);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
स्थिर SDL_FullscreenResult X11_SetWindowFullscreenViaWM(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = _display->internal;
    Display *display = data->videodata->display;
    Atom _NET_WM_STATE = data->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = data->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    सचे (!data->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        पटिनिवत्त SDL_FULLSCREEN_SUCCEEDED;
    }

    सचे (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // Flush any pending fullscreen events.
        सचे (data->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_SyncWindow(_this, window);
        }

        सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            सचे (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                पटिनिवत्त SDL_FULLSCREEN_FAILED;
            } अञ्ञथा सचे (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                पटिनिवत्त SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        सचे (fullscreen && !(window->flags & SDL_WINDOW_RESIZABLE)) {
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

        X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        सचे (((window->flags & SDL_WINDOW_FULLSCREEN) != 0) != (fullscreen != 0)) {
            data->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        सचे (fullscreen) {
            SDL_DisplayID current = SDL_GetDisplayForWindowPosition(window);
            SDL_copyp(&data->requested_fullscreen_mode, &window->current_fullscreen_mode);
            सचे (fullscreen != !!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                data->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
            }
            data->expected.x = displaydata->x;
            data->expected.y = displaydata->y;
            data->expected.w = _display->current_mode->w;
            data->expected.h = _display->current_mode->h;

            // Only move the window if it isn't already on the target display.
            सचे (!current || current != _display->id) {
                X11_XMoveWindow(display, data->xwindow, displaydata->x, displaydata->y);
                data->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } अञ्ञथा {
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
            सचे (data->window_was_maximized) {
                e.xclient.data.l[0] = _NET_WM_STATE_ADD;
            } अञ्ञथा {
                e.xclient.data.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.data.l[1] = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.data.l[2] = data->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.data.l[3] = 0l;
            X11_XSendEvent(display, मूलम्_Window(display, displaydata->screen), 0,
                           SubstructureNotifyMask | SubstructureRedirectMask, &e);
        }
    } अञ्ञथा {
        SDL_WindowFlags flags;

        flags = window->flags;
        सचे (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } अञ्ञथा {
            flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        X11_SetNetWMState(_this, data->xwindow, flags);
    }

    सचे (data->visual->class == DirectColor) {
        सचे (fullscreen) {
            X11_XInstallColormap(display, data->colormap);
        } अञ्ञथा {
            X11_XUninstallColormap(display, data->colormap);
        }
    }

    पटिनिवत्त SDL_FULLSCREEN_PENDING;
}

स्थिर SDL_FullscreenResult X11_SetWindowFullscreenLegacy(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = _display->internal;
    Display *display = data->videodata->display;
    ध्रुव पूर्णाङ्क screen = displaydata->screen;

    सचे (!data->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        पटिनिवत्त SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    सचे (data->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_SyncWindow(_this, window);
    }

    // No window manager? Just make the window the size of the display.
    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    सचे (fullscreen) {
        सचे (!(window->flags & SDL_WINDOW_RESIZABLE)) {
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
    } अञ्ञथा {
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

    पटिनिवत्त SDL_FULLSCREEN_PENDING;
}

SDL_FullscreenResult X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_WINDOW_DATA(window);
    CHECK_DISPLAY_DATA(_display);

    SDL_VideoData *data = _this->internal;
    सचे (data->net_wm) {
        पटिनिवत्त X11_SetWindowFullscreenViaWM(_this, window, _display, fullscreen);
    }

    पटिनिवत्त X11_SetWindowFullscreenLegacy(_this, window, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

प्रकारनिर्देश संरचना
{
    unsigned वर्ण *data;
    पूर्णाङ्क format, गणनम्;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
स्थिर शून्य X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned वर्ण *ret = रिक्त;
    Atom type;
    पूर्णाङ्क fmt;
    unsigned long गणनम्;
    unsigned long bytes_वामः;
    पूर्णाङ्क bytes_fetch = 0;

    करोहि {
        सचे (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &गणनम्, &bytes_वामः, &ret);
        bytes_fetch += bytes_वामः;
    } याव (bytes_वामः != 0);

    p->data = ret;
    p->format = fmt;
    p->गणनम् = गणनम्;
    p->type = type;
}

शून्य *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XWindowAttributes attributes;
    Atom icc_profile_atom;
    वर्ण icc_atom_string[परिमाण("_ICC_PROFILE_") + 12];
    शून्य *ret_icc_profile_data = रिक्त;
    CARD8 *icc_profile_data;
    पूर्णाङ्क real_format;
    unsigned long real_nitems;
    SDL_x11Prop atomProp;

    X11_XGetWindowAttributes(display, data->xwindow, &attributes);
    सचे (X11_XScreen_सङ्ख्या_Of_Screen(attributes.screen) > 0) {
        (शून्य)SDL_snprintf(icc_atom_string, परिमाण("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_सङ्ख्या_Of_Screen(attributes.screen));
    } अञ्ञथा {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", परिमाण("_ICC_PROFILE"));
    }
    X11_XGetWindowAttributes(display, मूलम्_Window_Of_Screen(attributes.screen), &attributes);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    सचे (icc_profile_atom == None) {
        SDL_SetError("Screen is not calibrated.");
        पटिनिवत्त रिक्त;
    }

    X11_ReadProperty(&atomProp, display, मूलम्_Window_Of_Screen(attributes.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.गणनम्;
    icc_profile_data = atomProp.data;
    सचे (real_format == None) {
        SDL_SetError("Screen is not calibrated.");
        पटिनिवत्त रिक्त;
    }

    ret_icc_profile_data = SDL_malloc(real_nitems);
    सचे (!ret_icc_profile_data) {
        पटिनिवत्त रिक्त;
    }

    SDL_memcpy(ret_icc_profile_data, icc_profile_data, real_nitems);
    *size = real_nitems;
    X11_XFree(icc_profile_data);

    पटिनिवत्त ret_icc_profile_data;
}

bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    सचे (!data) {
        पटिनिवत्त SDL_SetError("Invalid window data");
    }
    data->mouse_grabbed = false;
    data->pending_grab = false;

    display = data->videodata->display;

    सचे (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        सचे (window->flags & SDL_WINDOW_HIDDEN) {
            पटिनिवत्त true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        सचे (data->xinput2_mouse_enabled && SDL_GetMouseState(रिक्त, रिक्त)) {
            data->pending_grab = true;
            पटिनिवत्त true;
        }

        // Try to grab the mouse
        सचे (!data->videodata->broken_pointer_grab) {
            ध्रुव unsigned पूर्णाङ्क mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            पूर्णाङ्क attempts;
            पूर्णाङ्क result = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            अत्थाय (attempts = 0; attempts < 100; attempts++) {
                result = X11_XGrabPointer(display, data->xwindow, False, mask, GrabModeAsync,
                                          GrabModeAsync, data->xwindow, None, CurrentTime);
                सचे (result == GrabSuccess) {
                    data->mouse_grabbed = true;
                    भङ्ग;
                }
                SDL_Delay(50);
            }

            सचे (result != GrabSuccess) {
                data->videodata->broken_pointer_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, window);

        // Raise the window if we grab the mouse
        X11_XRaiseWindow(display, data->xwindow);
    } अञ्ञथा {
        X11_XUngrabPointer(display, CurrentTime);

        X11_Xinput2UngrabTouch(_this, window);
    }
    X11_XSync(display, False);

    सचे (!data->videodata->broken_pointer_grab) {
        पटिनिवत्त true;
    } अञ्ञथा {
        पटिनिवत्त SDL_SetError("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    सचे (!data) {
        पटिनिवत्त SDL_SetError("Invalid window data");
    }

    display = data->videodata->display;

    सचे (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        सचे (window->flags & SDL_WINDOW_HIDDEN) {
            पटिनिवत्त true;
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
        सचे (_this->internal->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            सचे (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClientMessageEvent client_message;
                client_message.type = ClientMessage;
                client_message.window = data->xwindow;
                client_message.format = 32;
                client_message.message_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_message.data.l[0] = 1;
                client_message.data.l[1] = CurrentTime;

                X11_XSendEvent(display, Default_मूलम्_Window(display), False, SubstructureNotifyMask | SubstructureRedirectMask, (XEvent *)&client_message);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, data->xwindow, True, GrabModeAsync,
                          GrabModeAsync, CurrentTime);
    } अञ्ञथा {
        X11_XUngrabKeyboard(display, CurrentTime);
    }
    X11_XSync(display, False);

    पटिनिवत्त true;
}

शून्य X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    सचे (data) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        पूर्णाङ्क numwindows = videodata->numwindows;
        SDL_WindowData **windowlist = videodata->windowlist;
        पूर्णाङ्क i;

        सचे (windowlist) {
            अत्थाय (i = 0; i < numwindows; ++i) {
                सचे (windowlist[i] && (windowlist[i]->window == window)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = रिक्त;
                    videodata->numwindows--;
                    भङ्ग;
                }
            }
        }

        X11_Destroy_निवेशः_Context(data);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_TermResizeSync(window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        सचे (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            X11_XDestroyWindow(display, data->xwindow);
            X11_XFlush(display);
        }
        SDL_free(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        सचे (videodata->active_cursor_confined_window == window) {
            X11_DestroyPointerBarrier(_this, window);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    window->internal = रिक्त;
}

bool X11_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    पटिनिवत्त true; // just succeed, the real work is done elsewhere.
}

शून्य X11_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom XdndAware = data->videodata->atoms.XdndAware;

    सचे (accept) {
        Atom xdnd_version = 5;
        X11_XChangeProperty(display, data->xwindow, XdndAware, XA_ATOM, 32,
                            PropModeReplace, (unsigned वर्ण *)&xdnd_version, 1);
    } अञ्ञथा {
        X11_XDeleteProperty(display, data->xwindow, XdndAware);
    }
}

bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, data->xwindow);
    सचे (!wmhints) {
        पटिनिवत्त SDL_SetError("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    data->flashing_window = false;
    data->flash_cancel_time = 0;

    विकल्प (operation) {
    पक्ष SDL_FLASH_CANCEL:
        // Taken care of above
        भङ्ग;
    पक्ष SDL_FLASH_BRIEFLY:
        सचे (!(window->flags & SDL_WINDOW_निवेशः_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            data->flashing_window = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            data->flash_cancel_time = SDL_GetTicks() + 1000;
        }
        भङ्ग;
    पक्ष SDL_FLASH_UNTIL_FOCUSED:
        सचे (!(window->flags & SDL_WINDOW_निवेशः_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            data->flashing_window = true;
        }
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }

    X11_XSetWMHints(display, data->xwindow, wmhints);
    X11_XFree(wmhints);
    पटिनिवत्त true;
}

bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, वर्ण *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    पूर्णाङ्क conv = X11_XmbTextListToTextProperty(display, &title, 1, XTextStyle, &titleprop);
    Status status;

    सचे (X11_XSupportsLocale() != True) {
        पटिनिवत्त SDL_SetError("Current locale not supported by X server, cannot continue.");
    }

    सचे (conv == 0) {
        X11_XSetTextProperty(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.मानम्);
        // we know this can't be a locale error as we checked X locale validity
    } अञ्ञथा सचे (conv < 0) {
        पटिनिवत्त SDL_OutOfMemory();
    } अञ्ञथा { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        पटिनिवत्त true;
    }

#ifdef X_HAVE_UTF8_STRING
    status = X11_Xutf8TextListToTextProperty(display, &title, 1, XUTF8StringStyle, &titleprop);
    सचे (status == Success) {
        X11_XSetTextProperty(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.मानम्);
    } अञ्ञथा {
        पटिनिवत्त SDL_SetError("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#endif

    X11_XFlush(display);
    पटिनिवत्त true;
}

शून्य X11_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_WindowData *data = window->internal;
    SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(window);
    Display *display = data->videodata->display;
    Window मूलम् = मूलम्_Window(display, displaydata->screen);
    XClientMessageEvent e;
    Window childReturn;
    पूर्णाङ्क wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, data->xwindow, मूलम्, x, y, &wx, &wy, &childReturn);

    e.type = ClientMessage;
    e.window = data->xwindow;
    e.message_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.data.l[0] = 0;  // GTK device ID (unused)
    e.data.l[1] = wx; // X coordinate relative to root
    e.data.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, मूलम्, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    सचे ((window->flags & SDL_WINDOW_EXTERNAL) &&
        (data->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(window);
            पटिनिवत्त true;
    }

    ध्रुव Uint64 current_time = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    अत्थाय (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        सचे (_this->displays[i]->internal->mode_switch_deadline_ns &&
            current_time < _this->displays[i]->internal->mode_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->internal->mode_switch_deadline_ns - current_time, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += window->internal->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_TO_NS(1000) : SDL_MS_TO_NS(100);

    पटिनिवत्त X11_SyncWindowTimeout(_this, window, timeout);
}

bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    सचे (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_WindowData *data = window->internal;
        Display *display = data->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, data->xwindow);
        सचे (!wmhints) {
            पटिनिवत्त SDL_SetError("Couldn't get WM hints");
        }

        wmhints->निवेशः = focusable ? True : False;
        wmhints->flags |= निवेशः_Hint;

        X11_XSetWMHints(display, data->xwindow, wmhints);
        X11_XFree(wmhints);
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_POPUP_MENU) {
        सचे (!(window->flags & SDL_WINDOW_HIDDEN)) {
            सचे (!focusable && (window->flags & SDL_WINDOW_निवेशः_FOCUS)) {
                SDL_Window *new_focus;
                ध्रुव bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                X11_SetKeyboardFocus(new_focus, set_focus);
            } अञ्ञथा सचे (focusable) {
                सचे (SDL_ShouldFocusPopup(window)) {
                    X11_SetKeyboardFocus(window, true);
                }
            }
        }

        पटिनिवत्त true;
    }

    पटिनिवत्त true;
}

#endif // SDL_VIDEO_DRIVER_X11
