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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_pixels_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../core/unix/SDL_appid.h"

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11mouse.h"
#অন্তর্ভাব "SDL_x11xinput2.h"
#অন্তর্ভাব "SDL_x11xfixes.h"

#ifdef SDL_VIDEO_OPENGL_EGL
#অন্তর্ভাব "SDL_x11opengles.h"
#endif

#অন্তর্ভাব "SDL_x11xsync.h"

#define _NET_WM_STATE_REMOVE 0l
#define _NET_WM_STATE_ADD    1l

#define CHECK_WINDOW_তথ্য(window)                                       \
    যদি (!window) {                                                      \
        ফেরত SDL_SetError("Invalid window");                          \
    }                                                                   \
    যদি (!window->internal) {                                          \
        ফেরত SDL_SetError("Invalid window driver data");              \
    }

#define CHECK_DISPLAY_তথ্য(display)                                     \
    যদি (!_display) {                                                    \
        ফেরত SDL_SetError("Invalid display");                         \
    }                                                                   \
    যদি (!_display->internal) {                                        \
        ফেরত SDL_SetError("Invalid display driver data");             \
    }

স্থির Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ফেরত ev->type == MapNotify && ev->xmap.window == *((Window *)win);
}
স্থির Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    ফেরত ev->type == UnmapNotify && ev->xunmap.window == *((Window *)win);
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

স্থির bool X11_CheckCurrentDesktop(ধ্রুবক অক্ষর *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    ধ্রুবক অক্ষর *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    যদি (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        ফেরত true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    যদি (desktopVar && SDL_strcasestr(desktopVar, name)) {
        ফেরত true;
    }

    ফেরত false;
}

স্থির bool X11_IsWindowMapped(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Video_তথ্য *videodata = _this->internal;
    XWindowAttributes attr;

    X11_XGetWindowAttributes(videodata->display, তথ্য->xwindow, &attr);
    যদি (attr.map_state != IsUnmapped) {
        ফেরত true;
    } অন্যথা {
        ফেরত false;
    }
}

স্থির bool X11_IsDisplayOk(Display *display)
{
    যদি (display->flags & XlibDisplayIOError) {
        ফেরত false;
    }
    ফেরত true;
}

#যদি 0
স্থির bool X11_IsActionAllowed(SDL_Window *window, Atom action)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Atom _NET_WM_ALLOWED_ACTIONS = তথ্য->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = তথ্য->videodata->display;
    পূর্ণসংখ্যা form;
    unsigned long remain;
    unsigned long len, i;
    Atom *list;
    bool ret = false;

    যদি (X11_XGetWindowProperty(display, তথ্য->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (unsigned অক্ষর **)&list) == Success) {
        জন্য (i=0; i<len; ++i) {
            যদি (list[i] == action) {
                ret = true;
                বিরতি;
            }
        }
        X11_XFree(list);
    }
    ফেরত ret;
}
#endif // 0

স্থির শূন্য X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ধ্রুবক bool last_position_pending = window->last_position_pending;
    ধ্রুবক bool last_আকার_pending = window->last_আকার_pending;

    X11_SyncWindow(_this, window);

    window->last_position_pending = last_position_pending;
    window->last_আকার_pending = last_আকার_pending;
}

শূন্য X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags)
{
    SDL_Video_তথ্য *videodata = _this->internal;
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
    পূর্ণসংখ্যা গুনতি = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    যদি (flags & SDL_WINDOW_ALWAYS_ON_শীর্ষ) {
        atoms[গুনতি++] = _NET_WM_STATE_ABOVE;
    }
    যদি (flags & SDL_WINDOW_UTILITY) {
        atoms[গুনতি++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[গুনতি++] = _NET_WM_STATE_SKIP_PAGER;
    }
    যদি (flags & SDL_WINDOW_প্রবেশ_FOCUS) {
        atoms[গুনতি++] = _NET_WM_STATE_FOCUSED;
    }
    যদি (flags & SDL_WINDOW_MAXIMIZED) {
        atoms[গুনতি++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[গুনতি++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    যদি (flags & SDL_WINDOW_FULLSCREEN) {
        atoms[গুনতি++] = _NET_WM_STATE_FULLSCREEN;
    }
    যদি (flags & SDL_WINDOW_MODAL) {
        atoms[গুনতি++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(গুনতি <= SDL_arraysize(atoms));

    যদি (গুনতি > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned অক্ষর *)atoms, গুনতি);
    } অন্যথা {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

স্থির শূন্য X11_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Clamp popup windows to the output borders
    যদি (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        পূর্ণসংখ্যা abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        পূর্ণসংখ্যা abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        পূর্ণসংখ্যা offset_x = 0, offset_y = 0;

        যদি (window->constrain_popup) {
            // Calculate the total offset from the parents
            জন্য (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
                offset_x += w->x;
                offset_y += w->y;
            }

            offset_x += w->x;
            offset_y += w->y;
            abs_x += offset_x;
            abs_y += offset_y;

            displayID = SDL_GetDisplayForWindow(w);

            SDL_GetDisplayBounds(displayID, &rect);
            যদি (abs_x + window->w > rect.x + rect.w) {
                abs_x -= (abs_x + window->w) - (rect.x + rect.w);
            }
            যদি (abs_y + window->h > rect.y + rect.h) {
                abs_y -= (abs_y + window->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        যদি (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
        } অন্যথা {
            window->floating.x = window->windowed.x = abs_x - offset_x;
            window->floating.y = window->windowed.y = abs_y - offset_y;
        }
    }
}

স্থির শূন্য X11_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    যখন (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    যদি (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

SDL_WindowFlags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_Window *window, Window xwindow)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    পূর্ণসংখ্যা actualFormat;
    unsigned long i, অঙ্ক_বস্তুসমূহ, bytesAfter;
    unsigned অক্ষর *property_মান = ফাঁকা;
    long max_দৈর্ঘ্য = 1024;
    SDL_WindowFlags flags = 0;

    যদি (X11_XGetWindowProperty(display, xwindow, _NET_WM_STATE,
                               0l, max_দৈর্ঘ্য, False, XA_ATOM, &actualType,
                               &actualFormat, &অঙ্ক_বস্তুসমূহ, &bytesAfter,
                               &property_মান) == Success) {
        Atom *atoms = (Atom *)property_মান;
        পূর্ণসংখ্যা maximized = 0;
        পূর্ণসংখ্যা fullscreen = 0;

        জন্য (i = 0; i < অঙ্ক_বস্তুসমূহ; ++i) {
            যদি (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_WINDOW_MINIMIZED | SDL_WINDOW_OCCLUDED;
            } অন্যথা যদি (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_WINDOW_প্রবেশ_FOCUS;
            } অন্যথা যদি (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } অন্যথা যদি (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } অন্যথা যদি (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        যদি (fullscreen == 1) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } অন্যথা যদি (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (window->flags & SDL_WINDOW_FULLSCREEN);
        }

        যদি (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            যদি (fullscreen) {
                flags |= (window->flags & SDL_WINDOW_MAXIMIZED);
            } অন্যথা {
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
            যদি (attr.map_state == IsUnmapped) {
                flags |= SDL_WINDOW_HIDDEN;
            }
        }
        X11_XFree(property_মান);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    ফেরত flags;
}

স্থির bool Setup_Window_তথ্য(SDL_VideoDevice *_this, SDL_Window *window, Window w)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    SDL_Window_তথ্য *তথ্য;

    // Allocate the window data
    তথ্য = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
    যদি (!তথ্য) {
        ফেরত false;
    }
    তথ্য->videodata = videodata;
    তথ্য->window = window;
    তথ্য->xwindow = w;
    তথ্য->hit_test_ফলাফল = SDL_HITTEST_NORMAL;

    X11_Create_প্রবেশ_Context(তথ্য);

    // Associate the data with the window

    যদি (videodata->numwindows >= videodata->windowlistlength) {
        SDL_Window_তথ্য ** new_windowlist = (SDL_Window_তথ্য **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * আকার(*videodata->windowlist));
        যদি (!new_windowlist) {
            যাও error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindowAttributes attrib;

        X11_XGetWindowAttributes(তথ্য->videodata->display, w, &attrib);
        যদি (!SDL_WINDOW_IS_POPUP(window)) {
            window->x = window->windowed.x = window->floating.x = attrib.x;
            window->y = window->windowed.y = window->floating.y = attrib.y - তথ্য->border_শীর্ষ;
        }
        window->w = window->windowed.w = window->floating.w = attrib.width;
        window->h = window->windowed.h = window->floating.h = attrib.height;
        যদি (attrib.map_state != IsUnmapped) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } অন্যথা {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        তথ্য->visual = attrib.visual;
        তথ্য->colormap = attrib.colormap;
    }

    window->flags |= X11_GetNetWMState(_this, window, w);

    {
        Window FocalWindow;
        পূর্ণসংখ্যা RevertTo = 0;
        X11_XGet_প্রবেশ_Focus(তথ্য->videodata->display, &FocalWindow, &RevertTo);
        যদি (FocalWindow == w) {
            window->flags |= SDL_WINDOW_প্রবেশ_FOCUS;
        }

        যদি (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
            SDL_SetKeyboardFocus(তথ্য->window);
        }

        যদি (window->flags & SDL_WINDOW_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        window->title = X11_GetWindowTitle(_this, w);
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    পূর্ণসংখ্যা screen = (displaydata ? displaydata->screen : 0);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, তথ্য->videodata->display);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_X11_SCREEN_সংখ্যা, screen);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_X11_WINDOW_সংখ্যা, তথ্য->xwindow);


#যদি defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    যদি ((window->flags & SDL_WINDOW_OPENGL) &&
        ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_তথ্য || X11_GL_UseEGL(_this))
#endif
    ) {
#ifdef SDL_VIDEO_OPENGL_EGL
        যদি (!_this->egl_তথ্য) {
            যাও error_cleanup;
        }

        // Create the GLES window surface
        তথ্য->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)w);

        যদি (তথ্য->egl_surface == EGL_NO_SURFACE) {
            SDL_SetError("Could not create GLES window surface");
            যাও error_cleanup;
        }
#অন্যথা
        SDL_SetError("Could not create GLES window surface (EGL support not configured)");
        যাও error_cleanup;
#endif // SDL_VIDEO_OPENGL_EGL
    }
#endif

    // All done!
    window->internal = তথ্য;
    videodata->windowlist[videodata->numwindows++] = তথ্য;
    ফেরত true;

error_cleanup:
    X11_Destroy_প্রবেশ_Context(তথ্য);
    SDL_free(তথ্য);
    ফেরত false;
}

স্থির শূন্য Setup_Window_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    long fevent = 0;
    SDL_Window_তথ্য *তথ্য = window->internal;
    Window xwindow = তথ্য->xwindow;

#ifdef X_HAVE_UTF8_STRING
    যদি (SDL_X11_HAVE_UTF8 && তথ্য->ic) {
        X11_XGetICValues(তথ্য->ic, XNFilterEvents, &fevent, ফাঁকা);
    }
#endif

    X11_Xinput2Select(_this, window);

    {
        unsigned পূর্ণসংখ্যা x11_keyboard_events = চাবি_Press_Mask | চাবি_Release_Mask;
        unsigned পূর্ণসংখ্যা x11_pointer_events = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

        X11_Xinput2SelectMouseAndKeyboard(_this, window);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        যদি (তথ্য->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        যদি (তথ্য->xinput2_mouse_enabled) {
            x11_pointer_events = 0;
        }

        X11_XSelect_প্রবেশ(তথ্য->videodata->display, xwindow,
                         (FocusChangeMask | EnterWindowMask | LeaveWindowMask | ExposureMask |
                          x11_keyboard_events | x11_pointer_events |
                          PropertyChangeMask | StructureNotifyMask |
                          KeymapStateMask | fevent));
    }
}

স্থির শূন্য SetWindowBordered(Display *display, পূর্ণসংখ্যা screen, Window window, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    যদি (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        কাঠামো
        {
            unsigned long flags;
            unsigned long functions;
            unsigned long decorations;
            long প্রবেশ_mode;
            unsigned long status;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, window, WM_HINTS, WM_HINTS, 32,
                            PropModeReplace, (unsigned অক্ষর *)&MWMHints,
                            আকার(MWMHints) / আকার(long));
    } অন্যথা { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, window, মূল_Window(display, screen));
    }
}

bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    Window w = (Window)SDL_Get_সংখ্যা_Property(create_props, SDL_PROP_WINDOW_CREATE_X11_WINDOW_সংখ্যা,
                (Window)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", ফাঁকা));
    যদি (w) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        যদি (!Setup_Window_তথ্য(_this, window, w)) {
            ফেরত false;
        }

        যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_WINDOW_প্রবেশ, true)) {
            Setup_Window_প্রবেশ(_this, window);
        }
        ফেরত true;
    }

    SDL_Video_তথ্য *তথ্য = _this->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    যদি (!displaydata) {
        ফেরত SDL_SetError("Could not find display info");
    }

    ধ্রুবক bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ধ্রুবক bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (window->flags & SDL_WINDOW_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_Window_তথ্য *windowdata;
    Display *display = তথ্য->display;
    পূর্ণসংখ্যা screen = displaydata->screen;
    Visual *visual;
    পূর্ণসংখ্যা depth;
    XSetWindowAttributes xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom _NET_WM_WINDOW_TYPE;
    Atom wintype;
    ধ্রুবক অক্ষর *wintype_name = ফাঁকা;
    long compositor = 1;
    Atom _NET_WM_PID;
    ধ্রুবক অক্ষর *hint = ফাঁকা;
    পূর্ণসংখ্যা win_x, win_y;
    bool undefined_position = false;

#যদি defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ধ্রুবক পূর্ণসংখ্যা transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    ধ্রুবক অক্ষর *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    ধ্রুবক অক্ষর *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    যদি (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, template;
        পূর্ণসংখ্যা nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(forced_visual_id, ফাঁকা, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        যদি (vi) {
            visual = vi->visual;
            depth = vi->depth;
            X11_XFree(vi);
        } অন্যথা {
            ফেরত false;
        }
    } অন্যথা যদি ((window->flags & SDL_WINDOW_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = ফাঁকা;

#ifdef SDL_VIDEO_OPENGL_EGL
        যদি (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#ifdef SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_তথ্য || X11_GL_UseEGL(_this))
#endif
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } অন্যথা
#endif
        {
#ifdef SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#endif
        }

        যদি (!vinfo) {
            ফেরত false;
        }
        visual = vinfo->visual;
        depth = vinfo->depth;
        X11_XFree(vinfo);
    } অন্যথা
#endif
    {
        visual = displaydata->visual;
        depth = displaydata->depth;
    }

    xattr.override_redirect = ((window->flags & SDL_WINDOW_TOOLTIP) || (window->flags & SDL_WINDOW_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    যদি (visual->class == DirectColor) {
        XColor *colorcells;
        পূর্ণসংখ্যা i;
        পূর্ণসংখ্যা ncolors;
        পূর্ণসংখ্যা rmax, gmax, bmax;
        পূর্ণসংখ্যা rmask, gmask, bmask;
        পূর্ণসংখ্যা rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, মূল_Window(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        যদি (!xattr.colormap) {
            ফেরত SDL_SetError("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * আকার(XColor));
        যদি (!colorcells) {
            ফেরত false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_mask;
        যখন (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_mask;
        যখন (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_mask;
        যখন (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        জন্য (i = 0; i < ncolors; i++) {
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
    } অন্যথা {
        xattr.colormap =
            X11_XCreateColormap(display, মূল_Window(display, screen),
                                visual, AllocNone);
    }

    যদি (window->undefined_x && window->undefined_y &&
        window->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    যদি (SDL_WINDOW_IS_POPUP(window)) {
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
    w = X11_XCreateWindow(display, মূল_Window(display, screen),
                          win_x, win_y, window->floating.w, window->floating.h,
                          0, depth, প্রবেশ_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    যদি (!w) {
        ফেরত SDL_SetError("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    যদি (!(window->pending_flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, screen, w, !(window->flags & SDL_WINDOW_BORDERLESS));
    }

    sizehints = X11_XAlloc_আকার_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        sizehints->min_width = sizehints->max_width = window->floating.w;
        sizehints->min_height = sizehints->max_height = window->floating.h;
        sizehints->flags |= (PMax_আকার | PMin_আকার);
    }
    যদি (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->প্রবেশ = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) ? True : False;
    wmhints->window_group = তথ্য->window_group;
    wmhints->flags = প্রবেশ_Hint | WindowGroupHint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (অক্ষর *)SDL_GetExeName();
    classhints->res_class = (অক্ষর *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, ফাঁকা, ফাঁকা, ফাঁকা, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    যদি (তথ্য->pid > 0) {
        long pid = (long)তথ্য->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, PropModeReplace,
                            (unsigned অক্ষর *)&pid, 1);
    }

    // Set the window manager state
    X11_SetNetWMState(_this, w, window->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_WINDOW_TYPE);
    যদি (window->flags & SDL_WINDOW_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } অন্যথা যদি (window->flags & SDL_WINDOW_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } অন্যথা যদি (window->flags & SDL_WINDOW_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } অন্যথা যদি (hint && *hint) {
        wintype_name = hint;
    } অন্যথা {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                        PropModeReplace, (unsigned অক্ষর *)&wintype, 1);
    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            PropModeReplace,
                            (unsigned অক্ষর *)&compositor, 1);
    }

    {
        Atom protocols[4];
        পূর্ণসংখ্যা proto_গুনতি = 0;

        protocols[proto_গুনতি++] = তথ্য->atoms.WM_DELETE_WINDOW; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_গুনতি++] = তথ্য->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        যদি (use_resize_sync) {
            protocols[proto_গুনতি++] = তথ্য->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_গুনতি <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_গুনতি);
    }

    যদি (!Setup_Window_তথ্য(_this, window, w)) {
        X11_XDestroyWindow(display, w);
        ফেরত false;
    }
    windowdata = window->internal;

    // Set the parent if this is a non-popup window.
    যদি (!SDL_WINDOW_IS_POPUP(window) && window->parent) {
        X11_XSetTransientForHint(display, w, window->parent->internal->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(window->pending_flags & SDL_WINDOW_FULLSCREEN) &&
                                               !!(window->flags & SDL_WINDOW_BORDERLESS);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    যদি (use_resize_sync) {
        X11_InitResizeSync(window);
    }
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    যদি (window->flags & SDL_WINDOW_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_প্রবেশ, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
    }
#endif

    Setup_Window_প্রবেশ(_this, window);

    // For _ICC_PROFILE.
    X11_XSelect_প্রবেশ(display, মূল_Window(display, screen), PropertyChangeMask);

    X11_XFlush(display);

    ফেরত true;
}

অক্ষর *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    Display *display = তথ্য->display;
    পূর্ণসংখ্যা status, real_format;
    Atom real_type;
    unsigned long বস্তুসমূহ_read, বস্তুসমূহ_বাম;
    unsigned অক্ষর *propdata;
    অক্ষর *title = ফাঁকা;

    status = X11_XGetWindowProperty(display, xwindow, তথ্য->atoms._NET_WM_NAME,
                                    0L, 8192L, False, তথ্য->atoms.UTF8_STRING, &real_type, &real_format,
                                    &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
    যদি (status == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(অক্ষর *, propdata));
        X11_XFree(propdata);
    } অন্যথা {
        status = X11_XGetWindowProperty(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
        যদি (status == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(অক্ষর *, propdata), বস্তুসমূহ_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } অন্যথা {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    ফেরত title;
}

শূন্য X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Window xwindow = তথ্য->xwindow;
    Display *display = তথ্য->videodata->display;
    অক্ষর *title = window->title ? window->title : "";

    SDL_X11_SetWindowTitle(display, xwindow, title);
}

স্থির bool caught_x11_error = false;
স্থির পূর্ণসংখ্যা X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    ফেরত 0;
}

স্থির শূন্য X11_ExternalResizeMoveSync(SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    পূর্ণসংখ্যা (*পূর্ব_handler)(Display *, XErrorEvent *);
    unsigned পূর্ণসংখ্যা child_গুনতি;
    Window childReturn, মূল, parent;
    Window *children;
    XWindowAttributes attrs;
    Uint64 timeout = 0;
    পূর্ণসংখ্যা x, y;
    ধ্রুবক bool send_move = !!(তথ্য->pending_operation & X11_PENDING_OP_MOVE);
    ধ্রুবক bool send_resize = !!(তথ্য->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_বৃক্ষ(display, তথ্য->xwindow, &মূল, &parent, &children, &child_গুনতি);
    পূর্ব_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_TO_NS(100);
    যখন (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGetWindowAttributes(display, তথ্য->xwindow, &attrs);
        X11_XTranslateCoordinates(display, parent, Default_মূল_Window(display),
                                  attrs.x, attrs.y, &x, &y, &childReturn);
        SDL_GlobalToRelativeForWindow(window, x, y, &x, &y);

        যদি (!caught_x11_error) {
            যদি ((তথ্য->pending_operation & X11_PENDING_OP_MOVE) && (x == তথ্য->expected.x + তথ্য->border_বাম && y == তথ্য->expected.y + তথ্য->border_শীর্ষ)) {
                তথ্য->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            যদি ((তথ্য->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.width == তথ্য->expected.w && attrs.height == তথ্য->expected.h)) {
                তথ্য->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            যদি (তথ্য->pending_operation == X11_PENDING_OP_NONE) {
                বিরতি;
            }
        }

        যদি (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            তথ্য->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            তথ্য->expected.x = x;
            তথ্য->expected.y = y;
            তথ্য->expected.w = attrs.width;
            তথ্য->expected.h = attrs.height;
            বিরতি;
        }

        SDL_Delay(10);
    }

    যদি (!caught_x11_error) {
        যদি (send_move) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
        }
        যদি (send_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, attrs.width, attrs.height);
        }
    }

    X11_XSetErrorHandler(পূর্ব_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
স্থির bool X11_SyncWindowTimeout(SDL_VideoDevice *_this, SDL_Window *window, Uint64 param_timeout)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    পূর্ণসংখ্যা (*পূর্ব_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool ফলাফল = true;

    X11_XSync(display, False);
    পূর্ব_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    যদি (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    যখন (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        যদি ((তথ্য->pending_operation & X11_PENDING_OP_MOVE) && (window->x == তথ্য->expected.x + তথ্য->border_বাম && window->y == তথ্য->expected.y + তথ্য->border_শীর্ষ)) {
            তথ্য->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        যদি ((তথ্য->pending_operation & X11_PENDING_OP_RESIZE) && (window->w == তথ্য->expected.w && window->h == তথ্য->expected.h)) {
            তথ্য->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        যদি (তথ্য->pending_operation == X11_PENDING_OP_NONE) {
            যদি (force_exit ||
                (window->x == তথ্য->expected.x + তথ্য->border_বাম && window->y == তথ্য->expected.y + তথ্য->border_শীর্ষ &&
                 window->w == তথ্য->expected.w && window->h == তথ্য->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                বিরতি;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        যদি (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            তথ্য->expected.x = window->x;
            তথ্য->expected.y = window->y;
            তথ্য->expected.w = window->w;
            তথ্য->expected.h = window->h;

            ফলাফল = false;
            বিরতি;
        }

        SDL_Delay(10);
    }

    তথ্য->pending_operation = X11_PENDING_OP_NONE;

    যদি (!caught_x11_error) {
        X11_PumpEvents(_this);
    } অন্যথা {
        ফলাফল = false;
    }

    X11_XSetErrorHandler(পূর্ব_handler);
    caught_x11_error = false;

    ফেরত ফলাফল;
}

bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    Atom _NET_WM_ICON = তথ্য->videodata->atoms._NET_WM_ICON;
    পূর্ণসংখ্যা (*পূর্ব_Handler)(Display *, XErrorEvent *) = ফাঁকা;
    bool ফলাফল = true;

    যদি (icon) {
        পূর্ণসংখ্যা x, y;
        পূর্ণসংখ্যা propsize;
        long *propdata;
        Uint32 *src;
        long *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * আকার(long));

        যদি (!propdata) {
            ফেরত false;
        }

        X11_XSync(display, False);
        পূর্ব_Handler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        জন্য (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            জন্য (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, তথ্য->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, PropModeReplace, (unsigned অক্ষর *)propdata,
                            propsize);
        SDL_free(propdata);

        যদি (caught_x11_error) {
            ফলাফল = SDL_SetError("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    যদি (পূর্ব_Handler) {
        X11_XSetErrorHandler(পূর্ব_Handler);
        caught_x11_error = false;
    }

    ফেরত ফলাফল;
}

শূন্য X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    ধ্রুবক পূর্ণসংখ্যা rel_x = use_current_position ? window->x : window->pending.x;
    ধ্রুবক পূর্ণসংখ্যা rel_y = use_current_position ? window->y : window->pending.y;

    SDL_RelativeToGlobalForWindow(window,
                                  rel_x - তথ্য->border_বাম, rel_y - তথ্য->border_শীর্ষ,
                                  &তথ্য->expected.x, &তথ্য->expected.y);

    // Attempt to move the window
    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->internal->pending_position = true;
    } অন্যথা {
        তথ্য->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMoveWindow(display, তথ্য->xwindow, তথ্য->expected.x, তথ্য->expected.y);
    }
}

bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Sync any pending fullscreen or maximize events.
    যদি (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    যদি (window->flags & SDL_WINDOW_MAXIMIZED) {
        যদি (window->internal->pending_operation & X11_PENDING_OP_RESTORE) {
            window->internal->pending_position = true;
        }
        ফেরত true;
    }

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        যদি (SDL_WINDOW_IS_POPUP(window)) {
            X11_ConstrainPopup(window, true);
        }
        X11_UpdateWindowPosition(window, false);
    } অন্যথা {
        window->internal->fs_repositioned = true;
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    ফেরত true;
}

শূন্য X11_SetWindowMinMax(SDL_Window *window, bool use_current)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_আকার_Hints();
    long hint_flags = 0;

    X11_XGetWMNormalHints(display, তথ্য->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_আকার | PMax_আকার | PAspect);

    যদি (তথ্য->window->flags & SDL_WINDOW_RESIZABLE) {
        যদি (তথ্য->window->min_w || তথ্য->window->min_h) {
            sizehints->flags |= PMin_আকার;
            sizehints->min_width = তথ্য->window->min_w;
            sizehints->min_height = তথ্য->window->min_h;
        }
        যদি (তথ্য->window->max_w || তথ্য->window->max_h) {
            sizehints->flags |= PMax_আকার;
            sizehints->max_width = তথ্য->window->max_w;
            sizehints->max_height = তথ্য->window->max_h;
        }
        যদি (তথ্য->window->min_aspect > 0.0f || তথ্য->window->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(তথ্য->window->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(তথ্য->window->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } অন্যথা {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_আকার | PMax_আকার;
        যদি (use_current) {
            sizehints->min_width = sizehints->max_width = window->last_আকার_pending ? window->pending.w : তথ্য->window->floating.w;
            sizehints->min_height = sizehints->max_height = window->last_আকার_pending ? window->pending.h : তথ্য->window->floating.h;
        } অন্যথা {
            sizehints->min_width = sizehints->max_width = window->last_আকার_pending ? window->pending.w : তথ্য->window->windowed.w;
            sizehints->min_height = sizehints->max_height = window->last_আকার_pending ? window->pending.h : তথ্য->window->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, তথ্য->xwindow, sizehints);
    X11_XFree(sizehints);
}

শূন্য X11_Set_Window_Minimum_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

শূন্য X11_Set_Window_Maximum_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

শূন্য X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

শূন্য X11_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    যদি (তথ্য->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the size as pending if the window is being restored.
    যদি (window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN)) {
        // New size will be set when the window is restored.
        যদি (তথ্য->pending_operation & X11_PENDING_OP_RESTORE) {
            তথ্য->pending_আকার = true;
        } অন্যথা {
            // Can't resize the window.
            window->last_আকার_pending = false;
        }
        ফেরত;
    }

    যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_আকার_Hints();
            long userhints;
            পূর্ণসংখ্যা dest_x, dest_y;

            X11_XGetWMNormalHints(display, তথ্য->xwindow, sizehints, &userhints);

            তথ্য->expected.w = sizehints->min_width = sizehints->max_width = window->pending.w;
            তথ্য->expected.h = sizehints->min_height = sizehints->max_height = window->pending.h;
            sizehints->flags |= PMin_আকার | PMax_আকার;
            তথ্য->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, তথ্য->xwindow, sizehints);

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
            X11_XResizeWindow(display, তথ্য->xwindow, window->pending.w, window->pending.h);
            ধ্রুবক পূর্ণসংখ্যা x = window->last_position_pending ? window->pending.x : window->x;
            ধ্রুবক পূর্ণসংখ্যা y = window->last_position_pending ? window->pending.y : window->y;
            SDL_RelativeToGlobalForWindow(window,
                                          x - তথ্য->border_বাম,
                                          y - তথ্য->border_শীর্ষ,
                                          &dest_x, &dest_y);
            X11_XMoveWindow(display, তথ্য->xwindow, dest_x, dest_y);
            X11_XRaiseWindow(display, তথ্য->xwindow);

            X11_XFree(sizehints);
        }
    } অন্যথা {
        তথ্য->expected.w = window->pending.w;
        তথ্য->expected.h = window->pending.h;
        তথ্য->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResizeWindow(display, তথ্য->xwindow, তথ্য->expected.w, তথ্য->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

bool X11_Get_Window_Borders_আকার(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *শীর্ষ, পূর্ণসংখ্যা *বাম, পূর্ণসংখ্যা *bottom, পূর্ণসংখ্যা *ডান)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    *বাম = তথ্য->border_বাম;
    *ডান = তথ্য->border_ডান;
    *শীর্ষ = তথ্য->border_শীর্ষ;
    *bottom = তথ্য->border_bottom;

    ফেরত true;
}

bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, দশমিক opacity)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    Atom _NET_WM_WINDOW_OPACITY = তথ্য->videodata->atoms._NET_WM_WINDOW_OPACITY;

    যদি (opacity == 1.0f) {
        X11_XDeleteProperty(display, তথ্য->xwindow, _NET_WM_WINDOW_OPACITY);
    } অন্যথা {
        ধ্রুবক Uint32 FullyOpaque = 0xFFFFFFFF;
        ধ্রুবক long alpha = (long)((দ্বিগুণ)opacity * (দ্বিগুণ)FullyOpaque);
        X11_XChangeProperty(display, তথ্য->xwindow, _NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                            PropModeReplace, (unsigned অক্ষর *)&alpha, 1);
    }

    ফেরত true;
}

bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Window_তথ্য *parent_তথ্য = parent ? parent->internal : ফাঁকা;
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    Display *display = video_তথ্য->display;

    যদি (parent_তথ্য) {
        X11_XSetTransientForHint(display, তথ্য->xwindow, parent_তথ্য->xwindow);
    } অন্যথা {
        X11_XDeleteProperty(display, তথ্য->xwindow, video_তথ্য->atoms.WM_TRANSIENT_FOR);
    }

    ফেরত true;
}

bool X11_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = video_তথ্য->display;
    Uint32 flags = window->flags;
    Atom _NET_WM_STATE = তথ্য->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = তথ্য->videodata->atoms._NET_WM_STATE_MODAL;

    যদি (modal) {
        flags |= SDL_WINDOW_MODAL;
    } অন্যথা {
        flags &= ~SDL_WINDOW_MODAL;
        X11_XDeleteProperty(display, তথ্য->xwindow, video_তথ্য->atoms.WM_TRANSIENT_FOR);
    }

    যদি (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = তথ্য->xwindow;
        e.xclient.তথ্য.l[0] = modal ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.তথ্য.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.তথ্য.l[3] = 0l;

        X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } অন্যথা {
        X11_SetNetWMState(_this, তথ্য->xwindow, flags);
    }

    X11_XFlush(display);

    ফেরত true;
}

শূন্য X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    ধ্রুবক bool focused = (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) != 0;
    ধ্রুবক bool visible = !(window->flags & SDL_WINDOW_HIDDEN) && !window->is_hiding;
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;
    XEvent event;

    যদি (তথ্য->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, displaydata->screen, তথ্য->xwindow, bordered);
        X11_XFlush(display);

        যদি (visible) {
            XWindowAttributes attr;
            করো {
                X11_XSync(display, False);
                X11_XGetWindowAttributes(display, তথ্য->xwindow, &attr);
            } যখন (attr.map_state != IsViewable);

            যদি (focused) {
                X11_XSet_প্রবেশ_Focus(display, তথ্য->xwindow, RevertToParent, CurrentTime);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&তথ্য->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&তথ্য->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_মানসমূহ(তথ্য);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResizeWindow(display, তথ্য->xwindow, window->floating.w, window->floating.h);
        X11_XSync(display, False);
    } অন্যথা {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        তথ্য->toggle_borders = true;
        তথ্য->fullscreen_borders_forced_on = false;
    }
}

শূন্য X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (তথ্য->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

শূন্য X11_Set_Window_Always_On_শীর্ষ(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীর্ষ)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;
    Atom _NET_WM_STATE = তথ্য->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = তথ্য->videodata->atoms._NET_WM_STATE_ABOVE;

    যদি (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = তথ্য->xwindow;
        e.xclient.তথ্য.l[0] =
            on_শীর্ষ ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.তথ্য.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.তথ্য.l[3] = 0l;

        X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } অন্যথা {
        X11_SetNetWMState(_this, তথ্য->xwindow, window->flags);
    }
    X11_XFlush(display);
}

শূন্য X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);
    bool set_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    যদি (তথ্য->was_shown) {
        X11_PumpEvents(_this);
    }

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(window, true);
        তথ্য->pending_position = true;
        set_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (শূন্য)bActivate;

    যদি (!X11_IsWindowMapped(_this, window)) {
        X11_XMapRaised(display, তথ্য->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        যদি (!(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&তথ্য->xwindow);
        }
        X11_XFlush(display);
        set_position = তথ্য->pending_position ||
                       (!(window->flags & SDL_WINDOW_BORDERLESS) && !window->undefined_x && !window->undefined_y);
    }

    যদি (!তথ্য->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_প্রবেশ_Focus(display, তথ্য->xwindow, RevertToNone, CurrentTime);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        X11_SetKeyboardFocus(window, true);
    }

    // Get some valid border values, if we haven't received them yet
    যদি (তথ্য->border_বাম == 0 && তথ্য->border_ডান == 0 && তথ্য->border_শীর্ষ == 0 && তথ্য->border_bottom == 0) {
        X11_Get_Border_মানসমূহ(তথ্য);
    }

    যদি (set_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ধ্রুবক পূর্ণসংখ্যা tx = (তথ্য->pending_position ? window->pending.x : window->x) - (তথ্য->was_shown ? 0 : তথ্য->border_বাম);
        ধ্রুবক পূর্ণসংখ্যা ty = (তথ্য->pending_position ? window->pending.y : window->y) - (তথ্য->was_shown ? 0 : তথ্য->border_শীর্ষ);
        পূর্ণসংখ্যা x, y;

        SDL_RelativeToGlobalForWindow(window, tx, ty, &x, &y);

        তথ্য->pending_position = false;
        X11_XMoveWindow(display, তথ্য->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    যদি (!(window->flags & SDL_WINDOW_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResizeWindow(display, তথ্য->xwindow, window->w, window->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    তথ্য->আকার_move_event_flags = X11_আকার_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    তথ্য->আকার_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    তথ্য->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    যদি (তথ্য->last_xconfigure.type) {
        পূর্ণসংখ্যা x, y;
        SDL_GlobalToRelativeForWindow(তথ্য->window, তথ্য->last_xconfigure.x, তথ্য->last_xconfigure.y, &x, &y);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, তথ্য->last_xconfigure.width, তথ্য->last_xconfigure.height);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
    }
}

শূন্য X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    পূর্ণসংখ্যা screen = (displaydata ? displaydata->screen : 0);
    Display *display = তথ্য->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ধ্রুবক bool is_mapped = X11_IsWindowMapped(_this, window);
    X11_XWithdrawWindow(display, তথ্য->xwindow, screen);
    যদি (is_mapped && !(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&তথ্য->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ধ্রুবক bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        X11_SetKeyboardFocus(new_focus, set_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

স্থির bool X11_SetWindowActive(SDL_VideoDevice *_this, SDL_Window *window)
{
    CHECK_WINDOW_তথ্য(window);

    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;
    Atom _NET_ACTIVE_WINDOW = তথ্য->videodata->atoms._NET_ACTIVE_WINDOW;

    যদি (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_ACTIVE_WINDOW;
        e.xclient.format = 32;
        e.xclient.window = তথ্য->xwindow;
        e.xclient.তথ্য.l[0] = 1; // source indication. 1 = application
        e.xclient.তথ্য.l[1] = তথ্য->user_time;
        e.xclient.তথ্য.l[2] = 0;

        X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        X11_XFlush(display);
    }
    ফেরত true;
}

শূন্য X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED, true);

    X11_XRaiseWindow(display, তথ্য->xwindow);
    যদি (bActivate) {
        X11_SetWindowActive(_this, window);
    }
    X11_XFlush(display);
}

স্থির bool X11_SetWindowMaximized(SDL_VideoDevice *_this, SDL_Window *window, bool maximized)
{
    CHECK_WINDOW_তথ্য(window);

    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;
    Atom _NET_WM_STATE = তথ্য->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = তথ্য->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = তথ্য->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        ফেরত true;
    }

    যদি (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = তথ্য->xwindow;
        e.xclient.তথ্য.l[0] =
            maximized ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.তথ্য.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.তথ্য.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.তথ্য.l[3] = 0l;

        যদি (maximized) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            তথ্য->expected.x = bounds.x + তথ্য->border_বাম;
            তথ্য->expected.y = bounds.y + তথ্য->border_শীর্ষ;
            তথ্য->expected.w = bounds.w - (তথ্য->border_বাম + তথ্য->border_ডান);
            তথ্য->expected.h = bounds.h - (তথ্য->border_শীর্ষ + তথ্য->border_bottom);
        } অন্যথা {
            তথ্য->expected.x = window->floating.x;
            তথ্য->expected.y = window->floating.y;
            তথ্য->expected.w = window->floating.w;
            তথ্য->expected.h = window->floating.h;
        }

        X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } অন্যথা {
        X11_SetNetWMState(_this, তথ্য->xwindow, window->flags);
    }
    X11_XFlush(display);

    ফেরত true;
}

শূন্য X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        window->internal->window_was_maximized = true;
        ফেরত;
    }

    যদি (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        window->internal->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_SetWindowMaximized(_this, window, true);
    }
}

শূন্য X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;

    যদি (তথ্য->pending_operation & SDL_WINDOW_FULLSCREEN) {
        SDL_SyncWindow(window);
    }

    তথ্য->pending_operation |= X11_PENDING_OP_MINIMIZE;
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        তথ্য->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
    }
    X11_XIconifyWindow(display, তথ্য->xwindow, displaydata->screen);
    X11_XFlush(display);
}

শূন্য X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Don't restore the window the first time it is being shown.
    যদি (!window->internal->was_shown) {
        ফেরত;
    }

    যদি (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    যদি ((window->flags & SDL_WINDOW_FULLSCREEN) && !(window->flags & SDL_WINDOW_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        window->internal->window_was_maximized = false;
        ফেরত;
    }

    যদি (window->flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED) ||
        (window->internal->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        window->internal->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ধ্রুবক bool maximize = !!(window->flags & SDL_WINDOW_MINIMIZED) && window->internal->window_was_maximized;
    X11_SetWindowMaximized(_this, window, maximize);
    X11_ShowWindow(_this, window);
    X11_SetWindowActive(_this, window);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
স্থির SDL_Fullscreen_ফলাফল X11_SetWindowFullscreenViaWM(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = _display->internal;
    Display *display = তথ্য->videodata->display;
    Atom _NET_WM_STATE = তথ্য->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = তথ্য->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    যদি (!তথ্য->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ফেরত SDL_FULLSCREEN_SUCCEEDED;
    }

    যদি (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // Flush any pending fullscreen events.
        যদি (তথ্য->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_SyncWindow(_this, window);
        }

        যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            যদি (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                ফেরত SDL_FULLSCREEN_FAILED;
            } অন্যথা যদি (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                ফেরত SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        যদি (fullscreen && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_আকার_Hints();
            long flags = 0;
            X11_XGetWMNormalHints(display, তথ্য->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_আকার | PMax_আকার | PAspect);
            X11_XSetWMNormalHints(display, তথ্য->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = তথ্য->xwindow;
        e.xclient.তথ্য.l[0] =
            fullscreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.তথ্য.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.তথ্য.l[3] = 0l;

        X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        যদি (((window->flags & SDL_WINDOW_FULLSCREEN) != 0) != (fullscreen != 0)) {
            তথ্য->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        যদি (fullscreen) {
            SDL_DisplayID current = SDL_GetDisplayForWindowPosition(window);
            SDL_copyp(&তথ্য->requested_fullscreen_mode, &window->current_fullscreen_mode);
            যদি (fullscreen != !!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                তথ্য->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
            }
            তথ্য->expected.x = displaydata->x;
            তথ্য->expected.y = displaydata->y;
            তথ্য->expected.w = _display->current_mode->w;
            তথ্য->expected.h = _display->current_mode->h;

            // Only move the window if it isn't already on the target display.
            যদি (!current || current != _display->id) {
                X11_XMoveWindow(display, তথ্য->xwindow, displaydata->x, displaydata->y);
                তথ্য->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } অন্যথা {
            SDL_zero(তথ্য->requested_fullscreen_mode);
            তথ্য->pending_position = তথ্য->fs_repositioned;
            তথ্য->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = ClientMessage;
            e.xclient.message_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.window = তথ্য->xwindow;
            যদি (তথ্য->window_was_maximized) {
                e.xclient.তথ্য.l[0] = _NET_WM_STATE_ADD;
            } অন্যথা {
                e.xclient.তথ্য.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.তথ্য.l[1] = তথ্য->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.তথ্য.l[2] = তথ্য->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.তথ্য.l[3] = 0l;
            X11_XSendEvent(display, মূল_Window(display, displaydata->screen), 0,
                           SubstructureNotifyMask | SubstructureRedirectMask, &e);
        }
    } অন্যথা {
        SDL_WindowFlags flags;

        flags = window->flags;
        যদি (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } অন্যথা {
            flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        X11_SetNetWMState(_this, তথ্য->xwindow, flags);
    }

    যদি (তথ্য->visual->class == DirectColor) {
        যদি (fullscreen) {
            X11_XInstallColormap(display, তথ্য->colormap);
        } অন্যথা {
            X11_XUninstallColormap(display, তথ্য->colormap);
        }
    }

    ফেরত SDL_FULLSCREEN_PENDING;
}

স্থির SDL_Fullscreen_ফলাফল X11_SetWindowFullscreenLegacy(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = _display->internal;
    Display *display = তথ্য->videodata->display;
    ধ্রুবক পূর্ণসংখ্যা screen = displaydata->screen;

    যদি (!তথ্য->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ফেরত SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    যদি (তথ্য->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_SyncWindow(_this, window);
    }

    // No window manager? Just make the window the size of the display.
    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    যদি (fullscreen) {
        যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_আকার_Hints();
            long flags = 0;
            X11_XGetWMNormalHints(display, তথ্য->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_আকার | PMax_আকার | PAspect);
            X11_XSetWMNormalHints(display, তথ্য->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SetWindowBordered(display, screen, তথ্য->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        তথ্য->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        তথ্য->expected.x = rect.x;
        তথ্য->expected.y = rect.y;
        তথ্য->expected.w = rect.w;
        তথ্য->expected.h = rect.h;
        X11_XMoveWindow(display, তথ্য->xwindow, rect.x, rect.y);
        X11_XResizeWindow(display, তথ্য->xwindow, rect.w, rect.h);
        X11_XRaiseWindow(display, তথ্য->xwindow);
    } অন্যথা {
        তথ্য->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        তথ্য->expected.x = window->windowed.x;
        তথ্য->expected.y = window->windowed.y;
        তথ্য->expected.w = window->windowed.w;
        তথ্য->expected.h = window->windowed.h;
        X11_XResizeWindow(display, তথ্য->xwindow, window->windowed.w, window->windowed.h);
        X11_XMoveWindow(display, তথ্য->xwindow, window->windowed.x, window->windowed.y);

        SetWindowBordered(display, screen, তথ্য->xwindow, (window->flags & SDL_WINDOW_BORDERLESS) == 0);
        X11_SetWindowMinMax(তথ্য->window, false);
    }

    X11_XFlush(display);

    ফেরত SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_ফলাফল X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_WINDOW_তথ্য(window);
    CHECK_DISPLAY_তথ্য(_display);

    SDL_Video_তথ্য *তথ্য = _this->internal;
    যদি (তথ্য->net_wm) {
        ফেরত X11_SetWindowFullscreenViaWM(_this, window, _display, fullscreen);
    }

    ফেরত X11_SetWindowFullscreenLegacy(_this, window, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

প্রকারলেখ কাঠামো
{
    unsigned অক্ষর *তথ্য;
    পূর্ণসংখ্যা format, গুনতি;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
স্থির শূন্য X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned অক্ষর *ret = ফাঁকা;
    Atom type;
    পূর্ণসংখ্যা fmt;
    unsigned long গুনতি;
    unsigned long bytes_বাম;
    পূর্ণসংখ্যা bytes_fetch = 0;

    করো {
        যদি (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &গুনতি, &bytes_বাম, &ret);
        bytes_fetch += bytes_বাম;
    } যখন (bytes_বাম != 0);

    p->তথ্য = ret;
    p->format = fmt;
    p->গুনতি = গুনতি;
    p->type = type;
}

শূন্য *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *আকার_2)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    XWindowAttributes attributes;
    Atom icc_profile_atom;
    অক্ষর icc_atom_string[আকার("_ICC_PROFILE_") + 12];
    শূন্য *ret_icc_profile_তথ্য = ফাঁকা;
    CARD8 *icc_profile_তথ্য;
    পূর্ণসংখ্যা real_format;
    unsigned long real_nitems;
    SDL_x11Prop atomProp;

    X11_XGetWindowAttributes(display, তথ্য->xwindow, &attributes);
    যদি (X11_XScreen_সংখ্যা_Of_Screen(attributes.screen) > 0) {
        (শূন্য)SDL_snprintf(icc_atom_string, আকার("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_সংখ্যা_Of_Screen(attributes.screen));
    } অন্যথা {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", আকার("_ICC_PROFILE"));
    }
    X11_XGetWindowAttributes(display, মূল_Window_Of_Screen(attributes.screen), &attributes);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    যদি (icc_profile_atom == None) {
        SDL_SetError("Screen is not calibrated.");
        ফেরত ফাঁকা;
    }

    X11_ReadProperty(&atomProp, display, মূল_Window_Of_Screen(attributes.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.গুনতি;
    icc_profile_তথ্য = atomProp.তথ্য;
    যদি (real_format == None) {
        SDL_SetError("Screen is not calibrated.");
        ফেরত ফাঁকা;
    }

    ret_icc_profile_তথ্য = SDL_malloc(real_nitems);
    যদি (!ret_icc_profile_তথ্য) {
        ফেরত ফাঁকা;
    }

    SDL_memcpy(ret_icc_profile_তথ্য, icc_profile_তথ্য, real_nitems);
    *আকার_2 = real_nitems;
    X11_XFree(icc_profile_তথ্য);

    ফেরত ret_icc_profile_তথ্য;
}

bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display;

    যদি (!তথ্য) {
        ফেরত SDL_SetError("Invalid window data");
    }
    তথ্য->mouse_grabbed = false;
    তথ্য->pending_grab = false;

    display = তথ্য->videodata->display;

    যদি (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        যদি (window->flags & SDL_WINDOW_HIDDEN) {
            ফেরত true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        যদি (তথ্য->xinput2_mouse_enabled && SDL_GetMouseState(ফাঁকা, ফাঁকা)) {
            তথ্য->pending_grab = true;
            ফেরত true;
        }

        // Try to grab the mouse
        যদি (!তথ্য->videodata->broken_pointer_grab) {
            ধ্রুবক unsigned পূর্ণসংখ্যা mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            পূর্ণসংখ্যা attempts;
            পূর্ণসংখ্যা ফলাফল = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            জন্য (attempts = 0; attempts < 100; attempts++) {
                ফলাফল = X11_XGrabPointer(display, তথ্য->xwindow, False, mask, GrabModeAsync,
                                          GrabModeAsync, তথ্য->xwindow, None, CurrentTime);
                যদি (ফলাফল == GrabSuccess) {
                    তথ্য->mouse_grabbed = true;
                    বিরতি;
                }
                SDL_Delay(50);
            }

            যদি (ফলাফল != GrabSuccess) {
                তথ্য->videodata->broken_pointer_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, window);

        // Raise the window if we grab the mouse
        X11_XRaiseWindow(display, তথ্য->xwindow);
    } অন্যথা {
        X11_XUngrabPointer(display, CurrentTime);

        X11_Xinput2UngrabTouch(_this, window);
    }
    X11_XSync(display, False);

    যদি (!তথ্য->videodata->broken_pointer_grab) {
        ফেরত true;
    } অন্যথা {
        ফেরত SDL_SetError("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display;

    যদি (!তথ্য) {
        ফেরত SDL_SetError("Invalid window data");
    }

    display = তথ্য->videodata->display;

    যদি (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        যদি (window->flags & SDL_WINDOW_HIDDEN) {
            ফেরত true;
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
        যদি (_this->internal->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            যদি (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClientMessageEvent client_message;
                client_message.type = ClientMessage;
                client_message.window = তথ্য->xwindow;
                client_message.format = 32;
                client_message.message_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_message.তথ্য.l[0] = 1;
                client_message.তথ্য.l[1] = CurrentTime;

                X11_XSendEvent(display, Default_মূল_Window(display), False, SubstructureNotifyMask | SubstructureRedirectMask, (XEvent *)&client_message);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, তথ্য->xwindow, True, GrabModeAsync,
                          GrabModeAsync, CurrentTime);
    } অন্যথা {
        X11_XUngrabKeyboard(display, CurrentTime);
    }
    X11_XSync(display, False);

    ফেরত true;
}

শূন্য X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (তথ্য) {
        SDL_Video_তথ্য *videodata = তথ্য->videodata;
        Display *display = videodata->display;
        পূর্ণসংখ্যা numwindows = videodata->numwindows;
        SDL_Window_তথ্য **windowlist = videodata->windowlist;
        পূর্ণসংখ্যা i;

        যদি (windowlist) {
            জন্য (i = 0; i < numwindows; ++i) {
                যদি (windowlist[i] && (windowlist[i]->window == window)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = ফাঁকা;
                    videodata->numwindows--;
                    বিরতি;
                }
            }
        }

        X11_Destroy_প্রবেশ_Context(তথ্য);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_TermResizeSync(window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

        যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            X11_XDestroyWindow(display, তথ্য->xwindow);
            X11_XFlush(display);
        }
        SDL_free(তথ্য);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        যদি (videodata->active_cursor_confined_window == window) {
            X11_DestroyPointerBarrier(_this, window);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    window->internal = ফাঁকা;
}

bool X11_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    ফেরত true; // just succeed, the real work is done elsewhere.
}

শূন্য X11_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    Atom XdndAware = তথ্য->videodata->atoms.XdndAware;

    যদি (accept) {
        Atom xdnd_version = 5;
        X11_XChangeProperty(display, তথ্য->xwindow, XdndAware, XA_ATOM, 32,
                            PropModeReplace, (unsigned অক্ষর *)&xdnd_version, 1);
    } অন্যথা {
        X11_XDeleteProperty(display, তথ্য->xwindow, XdndAware);
    }
}

bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, তথ্য->xwindow);
    যদি (!wmhints) {
        ফেরত SDL_SetError("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    তথ্য->flashing_window = false;
    তথ্য->flash_cancel_time = 0;

    নির্বাচন (operation) {
    ক্ষেত্র SDL_FLASH_CANCEL:
        // Taken care of above
        বিরতি;
    ক্ষেত্র SDL_FLASH_BRIEFLY:
        যদি (!(window->flags & SDL_WINDOW_প্রবেশ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            তথ্য->flashing_window = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            তথ্য->flash_cancel_time = SDL_GetTicks() + 1000;
        }
        বিরতি;
    ক্ষেত্র SDL_FLASH_UNTIL_FOCUSED:
        যদি (!(window->flags & SDL_WINDOW_প্রবেশ_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            তথ্য->flashing_window = true;
        }
        বিরতি;
    পূর্বনির্ধারিত:
        বিরতি;
    }

    X11_XSetWMHints(display, তথ্য->xwindow, wmhints);
    X11_XFree(wmhints);
    ফেরত true;
}

bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, অক্ষর *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    পূর্ণসংখ্যা conv = X11_XmbTextListToTextProperty(display, &title, 1, XTextStyle, &titleprop);
    Status status;

    যদি (X11_XSupportsLocale() != True) {
        ফেরত SDL_SetError("Current locale not supported by X server, cannot continue.");
    }

    যদি (conv == 0) {
        X11_XSetTextProperty(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.মান);
        // we know this can't be a locale error as we checked X locale validity
    } অন্যথা যদি (conv < 0) {
        ফেরত SDL_OutOfMemory();
    } অন্যথা { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        ফেরত true;
    }

#ifdef X_HAVE_UTF8_STRING
    status = X11_Xutf8TextListToTextProperty(display, &title, 1, XUTF8StringStyle, &titleprop);
    যদি (status == Success) {
        X11_XSetTextProperty(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.মান);
    } অন্যথা {
        ফেরত SDL_SetError("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#endif

    X11_XFlush(display);
    ফেরত true;
}

শূন্য X11_ShowWindowSystemMenu(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    Display *display = তথ্য->videodata->display;
    Window মূল = মূল_Window(display, displaydata->screen);
    XClientMessageEvent e;
    Window childReturn;
    পূর্ণসংখ্যা wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, তথ্য->xwindow, মূল, x, y, &wx, &wy, &childReturn);

    e.type = ClientMessage;
    e.window = তথ্য->xwindow;
    e.message_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.তথ্য.l[0] = 0;  // GTK device ID (unused)
    e.তথ্য.l[1] = wx; // X coordinate relative to root
    e.তথ্য.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, মূল, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    যদি ((window->flags & SDL_WINDOW_EXTERNAL) &&
        (তথ্য->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(window);
            ফেরত true;
    }

    ধ্রুবক Uint64 current_time = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; ++i) {
        যদি (_this->displays[i]->internal->mode_switch_deadline_ns &&
            current_time < _this->displays[i]->internal->mode_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->internal->mode_switch_deadline_ns - current_time, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += window->internal->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_TO_NS(1000) : SDL_MS_TO_NS(100);

    ফেরত X11_SyncWindowTimeout(_this, window, timeout);
}

bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    যদি (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window_তথ্য *তথ্য = window->internal;
        Display *display = তথ্য->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, তথ্য->xwindow);
        যদি (!wmhints) {
            ফেরত SDL_SetError("Couldn't get WM hints");
        }

        wmhints->প্রবেশ = focusable ? True : False;
        wmhints->flags |= প্রবেশ_Hint;

        X11_XSetWMHints(display, তথ্য->xwindow, wmhints);
        X11_XFree(wmhints);
    } অন্যথা যদি (window->flags & SDL_WINDOW_POPUP_MENU) {
        যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
            যদি (!focusable && (window->flags & SDL_WINDOW_প্রবেশ_FOCUS)) {
                SDL_Window *new_focus;
                ধ্রুবক bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                X11_SetKeyboardFocus(new_focus, set_focus);
            } অন্যথা যদি (focusable) {
                যদি (SDL_ShouldFocusPopup(window)) {
                    X11_SetKeyboardFocus(window, true);
                }
            }
        }

        ফেরত true;
    }

    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_X11
