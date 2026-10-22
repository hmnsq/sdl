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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../core/unix/SDL_appid.h"

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11mouse.h"
#समावेश "SDL_x11xinput2.h"
#समावेश "SDL_x11xfixes.h"

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#समावेश "SDL_x11opengles.h"
#पूर्ण_अगर

#समावेश "SDL_x11xsync.h"

#घोषणा _NET_WM_STATE_REMOVE 0l
#घोषणा _NET_WM_STATE_ADD    1l

#घोषणा CHECK_WINDOW_तथ्य(window)                                       \
    अगर (!window) {                                                      \
        वापस SDL_SetError("Invalid window");                          \
    }                                                                   \
    अगर (!window->internal) {                                          \
        वापस SDL_SetError("Invalid window driver data");              \
    }

#घोषणा CHECK_DISPLAY_तथ्य(display)                                     \
    अगर (!_display) {                                                    \
        वापस SDL_SetError("Invalid display");                         \
    }                                                                   \
    अगर (!_display->internal) {                                        \
        वापस SDL_SetError("Invalid display driver data");             \
    }

अटल Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    वापस ev->type == MapNotify && ev->xmap.window == *((Window *)win);
}
अटल Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    वापस ev->type == UnmapNotify && ev->xunmap.window == *((Window *)win);
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

अटल bool X11_CheckCurrentDesktop(स्थिर अक्षर *name)
{
    SDL_Environment *env = SDL_GetEnvironment();
    स्थिर अक्षर *desktopVar = SDL_GetEnvironmentVariable(env, "DESKTOP_SESSION");
    अगर (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        वापस true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    अगर (desktopVar && SDL_strcasestr(desktopVar, name)) {
        वापस true;
    }

    वापस false;
}

अटल bool X11_IsWindowMapped(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Video_तथ्य *videodata = _this->internal;
    XWindowAttributes attr;

    X11_XGetWindowAttributes(videodata->display, तथ्य->xwindow, &attr);
    अगर (attr.map_state != IsUnmapped) {
        वापस true;
    } अन्यथा {
        वापस false;
    }
}

अटल bool X11_IsDisplayOk(Display *display)
{
    अगर (display->flags & XlibDisplayIOError) {
        वापस false;
    }
    वापस true;
}

#अगर 0
अटल bool X11_IsActionAllowed(SDL_Window *window, Atom action)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Atom _NET_WM_ALLOWED_ACTIONS = तथ्य->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = तथ्य->videodata->display;
    पूर्णांक form;
    अचिन्हित दीर्घ remain;
    अचिन्हित दीर्घ len, i;
    Atom *list;
    bool ret = false;

    अगर (X11_XGetWindowProperty(display, तथ्य->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (अचिन्हित अक्षर **)&list) == Success) {
        क्रम (i=0; i<len; ++i) {
            अगर (list[i] == action) {
                ret = true;
                अवरोध;
            }
        }
        X11_XFree(list);
    }
    वापस ret;
}
#पूर्ण_अगर // 0

अटल व्योम X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    स्थिर bool last_position_pending = window->last_position_pending;
    स्थिर bool last_आकार_pending = window->last_आकार_pending;

    X11_SyncWindow(_this, window);

    window->last_position_pending = last_position_pending;
    window->last_आकार_pending = last_आकार_pending;
}

व्योम X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags)
{
    SDL_Video_तथ्य *videodata = _this->internal;
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
    पूर्णांक गिनती = 0;

    /* The window manager sets this property, we shouldn't set it.
       If we did, this would indicate to the window manager that we don't
       actually want to be mapped during X11_XMapRaised(), which would be bad.
     *
    if ((flags & SDL_WINDOW_HIDDEN) != 0) {
        atoms[count++] = _NET_WM_STATE_HIDDEN;
    }
    */

    अगर (flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) {
        atoms[गिनती++] = _NET_WM_STATE_ABOVE;
    }
    अगर (flags & SDL_WINDOW_UTILITY) {
        atoms[गिनती++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[गिनती++] = _NET_WM_STATE_SKIP_PAGER;
    }
    अगर (flags & SDL_WINDOW_निवेश_FOCUS) {
        atoms[गिनती++] = _NET_WM_STATE_FOCUSED;
    }
    अगर (flags & SDL_WINDOW_MAXIMIZED) {
        atoms[गिनती++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[गिनती++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    अगर (flags & SDL_WINDOW_FULLSCREEN) {
        atoms[गिनती++] = _NET_WM_STATE_FULLSCREEN;
    }
    अगर (flags & SDL_WINDOW_MODAL) {
        atoms[गिनती++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(गिनती <= SDL_arraysize(atoms));

    अगर (गिनती > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (अचिन्हित अक्षर *)atoms, गिनती);
    } अन्यथा {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

अटल व्योम X11_ConstrainPopup(SDL_Window *window, bool output_to_pending)
{
    // Clamp popup windows to the output borders
    अगर (SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णांक abs_x = window->last_position_pending ? window->pending.x : window->floating.x;
        पूर्णांक abs_y = window->last_position_pending ? window->pending.y : window->floating.y;
        पूर्णांक offset_x = 0, offset_y = 0;

        अगर (window->constrain_popup) {
            // Calculate the total offset from the parents
            क्रम (w = window->parent; SDL_WINDOW_IS_POPUP(w); w = w->parent) {
                offset_x += w->x;
                offset_y += w->y;
            }

            offset_x += w->x;
            offset_y += w->y;
            abs_x += offset_x;
            abs_y += offset_y;

            displayID = SDL_GetDisplayForWindow(w);

            SDL_GetDisplayBounds(displayID, &rect);
            अगर (abs_x + window->w > rect.x + rect.w) {
                abs_x -= (abs_x + window->w) - (rect.x + rect.w);
            }
            अगर (abs_y + window->h > rect.y + rect.h) {
                abs_y -= (abs_y + window->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        अगर (output_to_pending) {
            window->pending.x = abs_x - offset_x;
            window->pending.y = abs_y - offset_y;
        } अन्यथा {
            window->floating.x = window->windowed.x = abs_x - offset_x;
            window->floating.y = window->windowed.y = abs_y - offset_y;
        }
    }
}

अटल व्योम X11_SetKeyboardFocus(SDL_Window *window, bool set_active_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    जबतक (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    अगर (set_active_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

SDL_WindowFlags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_Window *window, Window xwindow)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    पूर्णांक actualFormat;
    अचिन्हित दीर्घ i, अंक_वस्तुएँ, bytesAfter;
    अचिन्हित अक्षर *property_मूल्य = शून्य;
    दीर्घ max_लंबाई = 1024;
    SDL_WindowFlags flags = 0;

    अगर (X11_XGetWindowProperty(display, xwindow, _NET_WM_STATE,
                               0l, max_लंबाई, False, XA_ATOM, &actualType,
                               &actualFormat, &अंक_वस्तुएँ, &bytesAfter,
                               &property_मूल्य) == Success) {
        Atom *atoms = (Atom *)property_मूल्य;
        पूर्णांक maximized = 0;
        पूर्णांक fullscreen = 0;

        क्रम (i = 0; i < अंक_वस्तुएँ; ++i) {
            अगर (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_WINDOW_MINIMIZED | SDL_WINDOW_OCCLUDED;
            } अन्यथा अगर (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_WINDOW_निवेश_FOCUS;
            } अन्यथा अगर (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } अन्यथा अगर (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } अन्यथा अगर (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        अगर (fullscreen == 1) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } अन्यथा अगर (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (window->flags & SDL_WINDOW_FULLSCREEN);
        }

        अगर (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            अगर (fullscreen) {
                flags |= (window->flags & SDL_WINDOW_MAXIMIZED);
            } अन्यथा {
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
            अगर (attr.map_state == IsUnmapped) {
                flags |= SDL_WINDOW_HIDDEN;
            }
        }
        X11_XFree(property_मूल्य);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    वापस flags;
}

अटल bool Setup_Window_तथ्य(SDL_VideoDevice *_this, SDL_Window *window, Window w)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    SDL_Window_तथ्य *तथ्य;

    // Allocate the window data
    तथ्य = (SDL_Window_तथ्य *)SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }
    तथ्य->videodata = videodata;
    तथ्य->window = window;
    तथ्य->xwindow = w;
    तथ्य->hit_test_परिणाम = SDL_HITTEST_NORMAL;

    X11_Create_निवेश_Context(तथ्य);

    // Associate the data with the window

    अगर (videodata->numwindows >= videodata->windowlistlength) {
        SDL_Window_तथ्य ** new_windowlist = (SDL_Window_तथ्य **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * माप(*videodata->windowlist));
        अगर (!new_windowlist) {
            जाओ error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindowAttributes attrib;

        X11_XGetWindowAttributes(तथ्य->videodata->display, w, &attrib);
        अगर (!SDL_WINDOW_IS_POPUP(window)) {
            window->x = window->windowed.x = window->floating.x = attrib.x;
            window->y = window->windowed.y = window->floating.y = attrib.y - तथ्य->border_शीर्ष;
        }
        window->w = window->windowed.w = window->floating.w = attrib.width;
        window->h = window->windowed.h = window->floating.h = attrib.height;
        अगर (attrib.map_state != IsUnmapped) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        } अन्यथा {
            window->flags |= SDL_WINDOW_HIDDEN;
        }
        तथ्य->visual = attrib.visual;
        तथ्य->colormap = attrib.colormap;
    }

    window->flags |= X11_GetNetWMState(_this, window, w);

    {
        Window FocalWindow;
        पूर्णांक RevertTo = 0;
        X11_XGet_निवेश_Focus(तथ्य->videodata->display, &FocalWindow, &RevertTo);
        अगर (FocalWindow == w) {
            window->flags |= SDL_WINDOW_निवेश_FOCUS;
        }

        अगर (window->flags & SDL_WINDOW_निवेश_FOCUS) {
            SDL_SetKeyboardFocus(तथ्य->window);
        }

        अगर (window->flags & SDL_WINDOW_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Query the title from the existing window
        window->title = X11_GetWindowTitle(_this, w);
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    पूर्णांक screen = (displaydata ? displaydata->screen : 0);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, तथ्य->videodata->display);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_X11_SCREEN_संख्या, screen);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_X11_WINDOW_संख्या, तथ्य->xwindow);


#अगर defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    अगर ((window->flags & SDL_WINDOW_OPENGL) &&
        ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#अगर_घोषित SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_तथ्य || X11_GL_UseEGL(_this))
#पूर्ण_अगर
    ) {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        अगर (!_this->egl_तथ्य) {
            जाओ error_cleanup;
        }

        // Create the GLES window surface
        तथ्य->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)w);

        अगर (तथ्य->egl_surface == EGL_NO_SURFACE) {
            SDL_SetError("Could not create GLES window surface");
            जाओ error_cleanup;
        }
#अन्यथा
        SDL_SetError("Could not create GLES window surface (EGL support not configured)");
        जाओ error_cleanup;
#पूर्ण_अगर // SDL_VIDEO_OPENGL_EGL
    }
#पूर्ण_अगर

    // All done!
    window->internal = तथ्य;
    videodata->windowlist[videodata->numwindows++] = तथ्य;
    वापस true;

error_cleanup:
    X11_Destroy_निवेश_Context(तथ्य);
    SDL_free(तथ्य);
    वापस false;
}

अटल व्योम Setup_Window_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    दीर्घ fevent = 0;
    SDL_Window_तथ्य *तथ्य = window->internal;
    Window xwindow = तथ्य->xwindow;

#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (SDL_X11_HAVE_UTF8 && तथ्य->ic) {
        X11_XGetICValues(तथ्य->ic, XNFilterEvents, &fevent, शून्य);
    }
#पूर्ण_अगर

    X11_Xinput2Select(_this, window);

    {
        अचिन्हित पूर्णांक x11_keyboard_events = कुंजी_Press_Mask | कुंजी_Release_Mask;
        अचिन्हित पूर्णांक x11_pointer_events = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

        X11_Xinput2SelectMouseAndKeyboard(_this, window);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        अगर (तथ्य->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        अगर (तथ्य->xinput2_mouse_enabled) {
            x11_pointer_events = 0;
        }

        X11_XSelect_निवेश(तथ्य->videodata->display, xwindow,
                         (FocusChangeMask | EnterWindowMask | LeaveWindowMask | ExposureMask |
                          x11_keyboard_events | x11_pointer_events |
                          PropertyChangeMask | StructureNotifyMask |
                          KeymapStateMask | fevent));
    }
}

अटल व्योम SetWindowBordered(Display *display, पूर्णांक screen, Window window, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    अगर (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        काष्ठा
        {
            अचिन्हित दीर्घ flags;
            अचिन्हित दीर्घ functions;
            अचिन्हित दीर्घ decorations;
            दीर्घ निवेश_mode;
            अचिन्हित दीर्घ status;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, window, WM_HINTS, WM_HINTS, 32,
                            PropModeReplace, (अचिन्हित अक्षर *)&MWMHints,
                            माप(MWMHints) / माप(दीर्घ));
    } अन्यथा { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, window, मूल_Window(display, screen));
    }
}

bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    Window w = (Window)SDL_Get_संख्या_Property(create_props, SDL_PROP_WINDOW_CREATE_X11_WINDOW_संख्या,
                (Window)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", शून्य));
    अगर (w) {
        window->flags |= SDL_WINDOW_EXTERNAL;

        अगर (!Setup_Window_तथ्य(_this, window, w)) {
            वापस false;
        }

        अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_WINDOW_निवेश, true)) {
            Setup_Window_निवेश(_this, window);
        }
        वापस true;
    }

    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    अगर (!displaydata) {
        वापस SDL_SetError("Could not find display info");
    }

    स्थिर bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    स्थिर bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (window->flags & SDL_WINDOW_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_Window_तथ्य *windowdata;
    Display *display = तथ्य->display;
    पूर्णांक screen = displaydata->screen;
    Visual *visual;
    पूर्णांक depth;
    XSetWindowAttributes xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom _NET_WM_WINDOW_TYPE;
    Atom wintype;
    स्थिर अक्षर *wintype_name = शून्य;
    दीर्घ compositor = 1;
    Atom _NET_WM_PID;
    स्थिर अक्षर *hint = शून्य;
    पूर्णांक win_x, win_y;
    bool undefined_position = false;

#अगर defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    स्थिर पूर्णांक transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    स्थिर अक्षर *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_WINDOW_VISUALID);
    स्थिर अक्षर *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    अगर (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, ढाँचा;
        पूर्णांक nvis;

        SDL_zero(ढाँचा);
        ढाँचा.visualid = SDL_strtol(forced_visual_id, शून्य, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ढाँचा, &nvis);
        अगर (vi) {
            visual = vi->visual;
            depth = vi->depth;
            X11_XFree(vi);
        } अन्यथा {
            वापस false;
        }
    } अन्यथा अगर ((window->flags & SDL_WINDOW_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = शून्य;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        अगर (((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#अगर_घोषित SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_तथ्य || X11_GL_UseEGL(_this))
#पूर्ण_अगर
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } अन्यथा
#पूर्ण_अगर
        {
#अगर_घोषित SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#पूर्ण_अगर
        }

        अगर (!vinfo) {
            वापस false;
        }
        visual = vinfo->visual;
        depth = vinfo->depth;
        X11_XFree(vinfo);
    } अन्यथा
#पूर्ण_अगर
    {
        visual = displaydata->visual;
        depth = displaydata->depth;
    }

    xattr.override_redirect = ((window->flags & SDL_WINDOW_TOOLTIP) || (window->flags & SDL_WINDOW_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    अगर (visual->class == DirectColor) {
        XColor *colorcells;
        पूर्णांक i;
        पूर्णांक ncolors;
        पूर्णांक rmax, gmax, bmax;
        पूर्णांक rmask, gmask, bmask;
        पूर्णांक rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, मूल_Window(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        अगर (!xattr.colormap) {
            वापस SDL_SetError("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * माप(XColor));
        अगर (!colorcells) {
            वापस false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_mask;
        जबतक (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_mask;
        जबतक (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_mask;
        जबतक (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        क्रम (i = 0; i < ncolors; i++) {
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
    } अन्यथा {
        xattr.colormap =
            X11_XCreateColormap(display, मूल_Window(display, screen),
                                visual, AllocNone);
    }

    अगर (window->undefined_x && window->undefined_y &&
        window->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    अगर (SDL_WINDOW_IS_POPUP(window)) {
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
    w = X11_XCreateWindow(display, मूल_Window(display, screen),
                          win_x, win_y, window->floating.w, window->floating.h,
                          0, depth, निवेश_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    अगर (!w) {
        वापस SDL_SetError("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    अगर (!(window->pending_flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, screen, w, !(window->flags & SDL_WINDOW_BORDERLESS));
    }

    sizehints = X11_XAlloc_आकार_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    अगर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        sizehints->min_width = sizehints->max_width = window->floating.w;
        sizehints->min_height = sizehints->max_height = window->floating.h;
        sizehints->flags |= (PMax_आकार | PMin_आकार);
    }
    अगर (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->निवेश = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE) ? True : False;
    wmhints->window_group = तथ्य->window_group;
    wmhints->flags = निवेश_Hint | WindowGroupHint;

    // Setup the class hints so we can get an icon (AfterStep)
    classhints = X11_XAllocClassHint();
    classhints->res_name = (अक्षर *)SDL_GetExeName();
    classhints->res_class = (अक्षर *)SDL_GetAppID();

    // Set the size, input and class hints, and define WM_CLIENT_MACHINE and WM_LOCALE_NAME
    X11_XSetWMProperties(display, w, शून्य, शून्य, शून्य, 0, sizehints, wmhints, classhints);

    X11_XFree(sizehints);
    X11_XFree(wmhints);
    X11_XFree(classhints);
    // Set the PID related to the window for the given hostname, if possible
    अगर (तथ्य->pid > 0) {
        दीर्घ pid = (दीर्घ)तथ्य->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, PropModeReplace,
                            (अचिन्हित अक्षर *)&pid, 1);
    }

    // Set the window manager state
    X11_SetNetWMState(_this, w, window->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_WINDOW_TYPE);
    अगर (window->flags & SDL_WINDOW_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } अन्यथा अगर (window->flags & SDL_WINDOW_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } अन्यथा अगर (window->flags & SDL_WINDOW_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } अन्यथा अगर (hint && *hint) {
        wintype_name = hint;
    } अन्यथा {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                        PropModeReplace, (अचिन्हित अक्षर *)&wintype, 1);
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            PropModeReplace,
                            (अचिन्हित अक्षर *)&compositor, 1);
    }

    {
        Atom protocols[4];
        पूर्णांक proto_गिनती = 0;

        protocols[proto_गिनती++] = तथ्य->atoms.WM_DELETE_WINDOW; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_गिनती++] = तथ्य->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
        अगर (use_resize_sync) {
            protocols[proto_गिनती++] = तथ्य->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_गिनती <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_गिनती);
    }

    अगर (!Setup_Window_तथ्य(_this, window, w)) {
        X11_XDestroyWindow(display, w);
        वापस false;
    }
    windowdata = window->internal;

    // Set the parent if this is a non-popup window.
    अगर (!SDL_WINDOW_IS_POPUP(window) && window->parent) {
        X11_XSetTransientForHint(display, w, window->parent->internal->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(window->pending_flags & SDL_WINDOW_FULLSCREEN) &&
                                               !!(window->flags & SDL_WINDOW_BORDERLESS);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
    अगर (use_resize_sync) {
        X11_InitResizeSync(window);
    }
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    अगर (window->flags & SDL_WINDOW_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_निवेश, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
    }
#पूर्ण_अगर

    Setup_Window_निवेश(_this, window);

    // For _ICC_PROFILE.
    X11_XSelect_निवेश(display, मूल_Window(display, screen), PropertyChangeMask);

    X11_XFlush(display);

    वापस true;
}

अक्षर *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Display *display = तथ्य->display;
    पूर्णांक status, real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुएँ_read, वस्तुएँ_बायाँ;
    अचिन्हित अक्षर *propdata;
    अक्षर *title = शून्य;

    status = X11_XGetWindowProperty(display, xwindow, तथ्य->atoms._NET_WM_NAME,
                                    0L, 8192L, False, तथ्य->atoms.UTF8_STRING, &real_type, &real_format,
                                    &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
    अगर (status == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(अक्षर *, propdata));
        X11_XFree(propdata);
    } अन्यथा {
        status = X11_XGetWindowProperty(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
        अगर (status == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(अक्षर *, propdata), वस्तुएँ_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } अन्यथा {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    वापस title;
}

व्योम X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Window xwindow = तथ्य->xwindow;
    Display *display = तथ्य->videodata->display;
    अक्षर *title = window->title ? window->title : "";

    SDL_X11_SetWindowTitle(display, xwindow, title);
}

अटल bool caught_x11_error = false;
अटल पूर्णांक X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    वापस 0;
}

अटल व्योम X11_ExternalResizeMoveSync(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    पूर्णांक (*पूर्व_handler)(Display *, XErrorEvent *);
    अचिन्हित पूर्णांक child_गिनती;
    Window childReturn, मूल, parent;
    Window *children;
    XWindowAttributes attrs;
    Uint64 timeout = 0;
    पूर्णांक x, y;
    स्थिर bool send_move = !!(तथ्य->pending_operation & X11_PENDING_OP_MOVE);
    स्थिर bool send_resize = !!(तथ्य->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_वृक्ष(display, तथ्य->xwindow, &मूल, &parent, &children, &child_गिनती);
    पूर्व_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_TO_NS(100);
    जबतक (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGetWindowAttributes(display, तथ्य->xwindow, &attrs);
        X11_XTranslateCoordinates(display, parent, Default_मूल_Window(display),
                                  attrs.x, attrs.y, &x, &y, &childReturn);
        SDL_GlobalToRelativeForWindow(window, x, y, &x, &y);

        अगर (!caught_x11_error) {
            अगर ((तथ्य->pending_operation & X11_PENDING_OP_MOVE) && (x == तथ्य->expected.x + तथ्य->border_बायाँ && y == तथ्य->expected.y + तथ्य->border_शीर्ष)) {
                तथ्य->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            अगर ((तथ्य->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.width == तथ्य->expected.w && attrs.height == तथ्य->expected.h)) {
                तथ्य->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            अगर (तथ्य->pending_operation == X11_PENDING_OP_NONE) {
                अवरोध;
            }
        }

        अगर (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            तथ्य->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            तथ्य->expected.x = x;
            तथ्य->expected.y = y;
            तथ्य->expected.w = attrs.width;
            तथ्य->expected.h = attrs.height;
            अवरोध;
        }

        SDL_Delay(10);
    }

    अगर (!caught_x11_error) {
        अगर (send_move) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
        }
        अगर (send_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, attrs.width, attrs.height);
        }
    }

    X11_XSetErrorHandler(पूर्व_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
अटल bool X11_SyncWindowTimeout(SDL_VideoDevice *_this, SDL_Window *window, Uint64 param_timeout)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    पूर्णांक (*पूर्व_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool परिणाम = true;

    X11_XSync(display, False);
    पूर्व_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    अगर (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    जबतक (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        अगर ((तथ्य->pending_operation & X11_PENDING_OP_MOVE) && (window->x == तथ्य->expected.x + तथ्य->border_बायाँ && window->y == तथ्य->expected.y + तथ्य->border_शीर्ष)) {
            तथ्य->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        अगर ((तथ्य->pending_operation & X11_PENDING_OP_RESIZE) && (window->w == तथ्य->expected.w && window->h == तथ्य->expected.h)) {
            तथ्य->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        अगर (तथ्य->pending_operation == X11_PENDING_OP_NONE) {
            अगर (force_exit ||
                (window->x == तथ्य->expected.x + तथ्य->border_बायाँ && window->y == तथ्य->expected.y + तथ्य->border_शीर्ष &&
                 window->w == तथ्य->expected.w && window->h == तथ्य->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                अवरोध;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        अगर (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            तथ्य->expected.x = window->x;
            तथ्य->expected.y = window->y;
            तथ्य->expected.w = window->w;
            तथ्य->expected.h = window->h;

            परिणाम = false;
            अवरोध;
        }

        SDL_Delay(10);
    }

    तथ्य->pending_operation = X11_PENDING_OP_NONE;

    अगर (!caught_x11_error) {
        X11_PumpEvents(_this);
    } अन्यथा {
        परिणाम = false;
    }

    X11_XSetErrorHandler(पूर्व_handler);
    caught_x11_error = false;

    वापस परिणाम;
}

bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    Atom _NET_WM_ICON = तथ्य->videodata->atoms._NET_WM_ICON;
    पूर्णांक (*पूर्व_Handler)(Display *, XErrorEvent *) = शून्य;
    bool परिणाम = true;

    अगर (icon) {
        पूर्णांक x, y;
        पूर्णांक propsize;
        दीर्घ *propdata;
        Uint32 *src;
        दीर्घ *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * माप(दीर्घ));

        अगर (!propdata) {
            वापस false;
        }

        X11_XSync(display, False);
        पूर्व_Handler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        क्रम (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            क्रम (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, तथ्य->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, PropModeReplace, (अचिन्हित अक्षर *)propdata,
                            propsize);
        SDL_free(propdata);

        अगर (caught_x11_error) {
            परिणाम = SDL_SetError("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    अगर (पूर्व_Handler) {
        X11_XSetErrorHandler(पूर्व_Handler);
        caught_x11_error = false;
    }

    वापस परिणाम;
}

व्योम X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    स्थिर पूर्णांक rel_x = use_current_position ? window->x : window->pending.x;
    स्थिर पूर्णांक rel_y = use_current_position ? window->y : window->pending.y;

    SDL_RelativeToGlobalForWindow(window,
                                  rel_x - तथ्य->border_बायाँ, rel_y - तथ्य->border_शीर्ष,
                                  &तथ्य->expected.x, &तथ्य->expected.y);

    // Attempt to move the window
    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        window->internal->pending_position = true;
    } अन्यथा {
        तथ्य->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMoveWindow(display, तथ्य->xwindow, तथ्य->expected.x, तथ्य->expected.y);
    }
}

bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Sync any pending fullscreen or maximize events.
    अगर (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    अगर (window->flags & SDL_WINDOW_MAXIMIZED) {
        अगर (window->internal->pending_operation & X11_PENDING_OP_RESTORE) {
            window->internal->pending_position = true;
        }
        वापस true;
    }

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        अगर (SDL_WINDOW_IS_POPUP(window)) {
            X11_ConstrainPopup(window, true);
        }
        X11_UpdateWindowPosition(window, false);
    } अन्यथा {
        window->internal->fs_repositioned = true;
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    वापस true;
}

व्योम X11_SetWindowMinMax(SDL_Window *window, bool use_current)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
    दीर्घ hint_flags = 0;

    X11_XGetWMNormalHints(display, तथ्य->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);

    अगर (तथ्य->window->flags & SDL_WINDOW_RESIZABLE) {
        अगर (तथ्य->window->min_w || तथ्य->window->min_h) {
            sizehints->flags |= PMin_आकार;
            sizehints->min_width = तथ्य->window->min_w;
            sizehints->min_height = तथ्य->window->min_h;
        }
        अगर (तथ्य->window->max_w || तथ्य->window->max_h) {
            sizehints->flags |= PMax_आकार;
            sizehints->max_width = तथ्य->window->max_w;
            sizehints->max_height = तथ्य->window->max_h;
        }
        अगर (तथ्य->window->min_aspect > 0.0f || तथ्य->window->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(तथ्य->window->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(तथ्य->window->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } अन्यथा {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_आकार | PMax_आकार;
        अगर (use_current) {
            sizehints->min_width = sizehints->max_width = window->last_आकार_pending ? window->pending.w : तथ्य->window->floating.w;
            sizehints->min_height = sizehints->max_height = window->last_आकार_pending ? window->pending.h : तथ्य->window->floating.h;
        } अन्यथा {
            sizehints->min_width = sizehints->max_width = window->last_आकार_pending ? window->pending.w : तथ्य->window->windowed.w;
            sizehints->min_height = sizehints->max_height = window->last_आकार_pending ? window->pending.h : तथ्य->window->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, तथ्य->xwindow, sizehints);
    X11_XFree(sizehints);
}

व्योम X11_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

व्योम X11_Set_Window_Maximum_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

व्योम X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (window->internal->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

व्योम X11_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    अगर (तथ्य->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, window);
    }

    // Set the size as pending if the window is being restored.
    अगर (window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN)) {
        // New size will be set when the window is restored.
        अगर (तथ्य->pending_operation & X11_PENDING_OP_RESTORE) {
            तथ्य->pending_आकार = true;
        } अन्यथा {
            // Can't resize the window.
            window->last_आकार_pending = false;
        }
        वापस;
    }

    अगर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ userhints;
            पूर्णांक dest_x, dest_y;

            X11_XGetWMNormalHints(display, तथ्य->xwindow, sizehints, &userhints);

            तथ्य->expected.w = sizehints->min_width = sizehints->max_width = window->pending.w;
            तथ्य->expected.h = sizehints->min_height = sizehints->max_height = window->pending.h;
            sizehints->flags |= PMin_आकार | PMax_आकार;
            तथ्य->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, तथ्य->xwindow, sizehints);

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
            X11_XResizeWindow(display, तथ्य->xwindow, window->pending.w, window->pending.h);
            स्थिर पूर्णांक x = window->last_position_pending ? window->pending.x : window->x;
            स्थिर पूर्णांक y = window->last_position_pending ? window->pending.y : window->y;
            SDL_RelativeToGlobalForWindow(window,
                                          x - तथ्य->border_बायाँ,
                                          y - तथ्य->border_शीर्ष,
                                          &dest_x, &dest_y);
            X11_XMoveWindow(display, तथ्य->xwindow, dest_x, dest_y);
            X11_XRaiseWindow(display, तथ्य->xwindow);

            X11_XFree(sizehints);
        }
    } अन्यथा {
        तथ्य->expected.w = window->pending.w;
        तथ्य->expected.h = window->pending.h;
        तथ्य->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResizeWindow(display, तथ्य->xwindow, तथ्य->expected.w, तथ्य->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

bool X11_Get_Window_Borders_आकार(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *बायाँ, पूर्णांक *bottom, पूर्णांक *दायाँ)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    *बायाँ = तथ्य->border_बायाँ;
    *दायाँ = तथ्य->border_दायाँ;
    *शीर्ष = तथ्य->border_शीर्ष;
    *bottom = तथ्य->border_bottom;

    वापस true;
}

bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    Atom _NET_WM_WINDOW_OPACITY = तथ्य->videodata->atoms._NET_WM_WINDOW_OPACITY;

    अगर (opacity == 1.0f) {
        X11_XDeleteProperty(display, तथ्य->xwindow, _NET_WM_WINDOW_OPACITY);
    } अन्यथा {
        स्थिर Uint32 FullyOpaque = 0xFFFFFFFF;
        स्थिर दीर्घ alpha = (दीर्घ)((द्विगुन)opacity * (द्विगुन)FullyOpaque);
        X11_XChangeProperty(display, तथ्य->xwindow, _NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                            PropModeReplace, (अचिन्हित अक्षर *)&alpha, 1);
    }

    वापस true;
}

bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Window_तथ्य *parent_तथ्य = parent ? parent->internal : शून्य;
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    Display *display = video_तथ्य->display;

    अगर (parent_तथ्य) {
        X11_XSetTransientForHint(display, तथ्य->xwindow, parent_तथ्य->xwindow);
    } अन्यथा {
        X11_XDeleteProperty(display, तथ्य->xwindow, video_तथ्य->atoms.WM_TRANSIENT_FOR);
    }

    वापस true;
}

bool X11_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = video_तथ्य->display;
    Uint32 flags = window->flags;
    Atom _NET_WM_STATE = तथ्य->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = तथ्य->videodata->atoms._NET_WM_STATE_MODAL;

    अगर (modal) {
        flags |= SDL_WINDOW_MODAL;
    } अन्यथा {
        flags &= ~SDL_WINDOW_MODAL;
        X11_XDeleteProperty(display, तथ्य->xwindow, video_तथ्य->atoms.WM_TRANSIENT_FOR);
    }

    अगर (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = तथ्य->xwindow;
        e.xclient.तथ्य.l[0] = modal ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.तथ्य.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.तथ्य.l[3] = 0l;

        X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अन्यथा {
        X11_SetNetWMState(_this, तथ्य->xwindow, flags);
    }

    X11_XFlush(display);

    वापस true;
}

व्योम X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    स्थिर bool focused = (window->flags & SDL_WINDOW_निवेश_FOCUS) != 0;
    स्थिर bool visible = !(window->flags & SDL_WINDOW_HIDDEN) && !window->is_hiding;
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;
    XEvent event;

    अगर (तथ्य->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        SetWindowBordered(display, displaydata->screen, तथ्य->xwindow, bordered);
        X11_XFlush(display);

        अगर (visible) {
            XWindowAttributes attr;
            करो {
                X11_XSync(display, False);
                X11_XGetWindowAttributes(display, तथ्य->xwindow, &attr);
            } जबतक (attr.map_state != IsViewable);

            अगर (focused) {
                X11_XSet_निवेश_Focus(display, तथ्य->xwindow, RevertToParent, CurrentTime);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&तथ्य->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&तथ्य->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_मूल्यावली(तथ्य);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResizeWindow(display, तथ्य->xwindow, window->floating.w, window->floating.h);
        X11_XSync(display, False);
    } अन्यथा {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        तथ्य->toggle_borders = true;
        तथ्य->fullscreen_borders_forced_on = false;
    }
}

व्योम X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_SyncWindow(_this, window);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        X11_SetWindowMinMax(window, true);
    }
}

व्योम X11_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;
    Atom _NET_WM_STATE = तथ्य->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = तथ्य->videodata->atoms._NET_WM_STATE_ABOVE;

    अगर (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = तथ्य->xwindow;
        e.xclient.तथ्य.l[0] =
            on_शीर्ष ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.तथ्य.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.तथ्य.l[3] = 0l;

        X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अन्यथा {
        X11_SetNetWMState(_this, तथ्य->xwindow, window->flags);
    }
    X11_XFlush(display);
}

व्योम X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true);
    bool set_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    अगर (तथ्य->was_shown) {
        X11_PumpEvents(_this);
    }

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(window, true);
        तथ्य->pending_position = true;
        set_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (व्योम)bActivate;

    अगर (!X11_IsWindowMapped(_this, window)) {
        X11_XMapRaised(display, तथ्य->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        अगर (!(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&तथ्य->xwindow);
        }
        X11_XFlush(display);
        set_position = तथ्य->pending_position ||
                       (!(window->flags & SDL_WINDOW_BORDERLESS) && !window->undefined_x && !window->undefined_y);
    }

    अगर (!तथ्य->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_निवेश_Focus(display, तथ्य->xwindow, RevertToNone, CurrentTime);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        X11_SetKeyboardFocus(window, true);
    }

    // Get some valid border values, if we haven't received them yet
    अगर (तथ्य->border_बायाँ == 0 && तथ्य->border_दायाँ == 0 && तथ्य->border_शीर्ष == 0 && तथ्य->border_bottom == 0) {
        X11_Get_Border_मूल्यावली(तथ्य);
    }

    अगर (set_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        स्थिर पूर्णांक tx = (तथ्य->pending_position ? window->pending.x : window->x) - (तथ्य->was_shown ? 0 : तथ्य->border_बायाँ);
        स्थिर पूर्णांक ty = (तथ्य->pending_position ? window->pending.y : window->y) - (तथ्य->was_shown ? 0 : तथ्य->border_शीर्ष);
        पूर्णांक x, y;

        SDL_RelativeToGlobalForWindow(window, tx, ty, &x, &y);

        तथ्य->pending_position = false;
        X11_XMoveWindow(display, तथ्य->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    अगर (!(window->flags & SDL_WINDOW_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResizeWindow(display, तथ्य->xwindow, window->w, window->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    तथ्य->आकार_move_event_flags = X11_आकार_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    तथ्य->आकार_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    तथ्य->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    अगर (तथ्य->last_xconfigure.type) {
        पूर्णांक x, y;
        SDL_GlobalToRelativeForWindow(तथ्य->window, तथ्य->last_xconfigure.x, तथ्य->last_xconfigure.y, &x, &y);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, तथ्य->last_xconfigure.width, तथ्य->last_xconfigure.height);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, x, y);
    }
}

व्योम X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    पूर्णांक screen = (displaydata ? displaydata->screen : 0);
    Display *display = तथ्य->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    स्थिर bool is_mapped = X11_IsWindowMapped(_this, window);
    X11_XWithdrawWindow(display, तथ्य->xwindow, screen);
    अगर (is_mapped && !(window->flags & SDL_WINDOW_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&तथ्य->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
        X11_SetKeyboardFocus(new_focus, set_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

अटल bool X11_SetWindowActive(SDL_VideoDevice *_this, SDL_Window *window)
{
    CHECK_WINDOW_तथ्य(window);

    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;
    Atom _NET_ACTIVE_WINDOW = तथ्य->videodata->atoms._NET_ACTIVE_WINDOW;

    अगर (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_ACTIVE_WINDOW;
        e.xclient.format = 32;
        e.xclient.window = तथ्य->xwindow;
        e.xclient.तथ्य.l[0] = 1; // source indication. 1 = application
        e.xclient.तथ्य.l[1] = तथ्य->user_time;
        e.xclient.तथ्य.l[2] = 0;

        X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        X11_XFlush(display);
    }
    वापस true;
}

व्योम X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED, true);

    X11_XRaiseWindow(display, तथ्य->xwindow);
    अगर (bActivate) {
        X11_SetWindowActive(_this, window);
    }
    X11_XFlush(display);
}

अटल bool X11_SetWindowMaximized(SDL_VideoDevice *_this, SDL_Window *window, bool maximized)
{
    CHECK_WINDOW_तथ्य(window);

    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;
    Atom _NET_WM_STATE = तथ्य->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = तथ्य->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = तथ्य->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        वापस true;
    }

    अगर (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = तथ्य->xwindow;
        e.xclient.तथ्य.l[0] =
            maximized ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.तथ्य.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.तथ्य.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.तथ्य.l[3] = 0l;

        अगर (maximized) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            तथ्य->expected.x = bounds.x + तथ्य->border_बायाँ;
            तथ्य->expected.y = bounds.y + तथ्य->border_शीर्ष;
            तथ्य->expected.w = bounds.w - (तथ्य->border_बायाँ + तथ्य->border_दायाँ);
            तथ्य->expected.h = bounds.h - (तथ्य->border_शीर्ष + तथ्य->border_bottom);
        } अन्यथा {
            तथ्य->expected.x = window->floating.x;
            तथ्य->expected.y = window->floating.y;
            तथ्य->expected.w = window->floating.w;
            तथ्य->expected.h = window->floating.h;
        }

        X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);
    } अन्यथा {
        X11_SetNetWMState(_this, तथ्य->xwindow, window->flags);
    }
    X11_XFlush(display);

    वापस true;
}

व्योम X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        window->internal->window_was_maximized = true;
        वापस;
    }

    अगर (!(window->flags & SDL_WINDOW_MINIMIZED)) {
        window->internal->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_SetWindowMaximized(_this, window, true);
    }
}

व्योम X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;

    अगर (तथ्य->pending_operation & SDL_WINDOW_FULLSCREEN) {
        SDL_SyncWindow(window);
    }

    तथ्य->pending_operation |= X11_PENDING_OP_MINIMIZE;
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
        तथ्य->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
    }
    X11_XIconifyWindow(display, तथ्य->xwindow, displaydata->screen);
    X11_XFlush(display);
}

व्योम X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Don't restore the window the first time it is being shown.
    अगर (!window->internal->was_shown) {
        वापस;
    }

    अगर (window->internal->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_SyncWindow(window);
    }

    अगर ((window->flags & SDL_WINDOW_FULLSCREEN) && !(window->flags & SDL_WINDOW_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        window->internal->window_was_maximized = false;
        वापस;
    }

    अगर (window->flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED) ||
        (window->internal->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        window->internal->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    स्थिर bool maximize = !!(window->flags & SDL_WINDOW_MINIMIZED) && window->internal->window_was_maximized;
    X11_SetWindowMaximized(_this, window, maximize);
    X11_ShowWindow(_this, window);
    X11_SetWindowActive(_this, window);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
अटल SDL_Fullscreen_परिणाम X11_SetWindowFullscreenViaWM(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = _display->internal;
    Display *display = तथ्य->videodata->display;
    Atom _NET_WM_STATE = तथ्य->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = तथ्य->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    अगर (!तथ्य->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    अगर (X11_IsWindowMapped(_this, window)) {
        XEvent e;

        // Flush any pending fullscreen events.
        अगर (तथ्य->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_SyncWindow(_this, window);
        }

        अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            अगर (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                वापस SDL_FULLSCREEN_FAILED;
            } अन्यथा अगर (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                वापस SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        अगर (fullscreen && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ flags = 0;
            X11_XGetWMNormalHints(display, तथ्य->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);
            X11_XSetWMNormalHints(display, तथ्य->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = ClientMessage;
        e.xclient.message_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.window = तथ्य->xwindow;
        e.xclient.तथ्य.l[0] =
            fullscreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
        e.xclient.तथ्य.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.तथ्य.l[3] = 0l;

        X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                       SubstructureNotifyMask | SubstructureRedirectMask, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        अगर (((window->flags & SDL_WINDOW_FULLSCREEN) != 0) != (fullscreen != 0)) {
            तथ्य->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        अगर (fullscreen) {
            SDL_DisplayID current = SDL_GetDisplayForWindowPosition(window);
            SDL_copyp(&तथ्य->requested_fullscreen_mode, &window->current_fullscreen_mode);
            अगर (fullscreen != !!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                तथ्य->window_was_maximized = !!(window->flags & SDL_WINDOW_MAXIMIZED);
            }
            तथ्य->expected.x = displaydata->x;
            तथ्य->expected.y = displaydata->y;
            तथ्य->expected.w = _display->current_mode->w;
            तथ्य->expected.h = _display->current_mode->h;

            // Only move the window if it isn't already on the target display.
            अगर (!current || current != _display->id) {
                X11_XMoveWindow(display, तथ्य->xwindow, displaydata->x, displaydata->y);
                तथ्य->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } अन्यथा {
            SDL_zero(तथ्य->requested_fullscreen_mode);
            तथ्य->pending_position = तथ्य->fs_repositioned;
            तथ्य->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = ClientMessage;
            e.xclient.message_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.window = तथ्य->xwindow;
            अगर (तथ्य->window_was_maximized) {
                e.xclient.तथ्य.l[0] = _NET_WM_STATE_ADD;
            } अन्यथा {
                e.xclient.तथ्य.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.तथ्य.l[1] = तथ्य->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.तथ्य.l[2] = तथ्य->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.तथ्य.l[3] = 0l;
            X11_XSendEvent(display, मूल_Window(display, displaydata->screen), 0,
                           SubstructureNotifyMask | SubstructureRedirectMask, &e);
        }
    } अन्यथा {
        SDL_WindowFlags flags;

        flags = window->flags;
        अगर (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } अन्यथा {
            flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        X11_SetNetWMState(_this, तथ्य->xwindow, flags);
    }

    अगर (तथ्य->visual->class == DirectColor) {
        अगर (fullscreen) {
            X11_XInstallColormap(display, तथ्य->colormap);
        } अन्यथा {
            X11_XUninstallColormap(display, तथ्य->colormap);
        }
    }

    वापस SDL_FULLSCREEN_PENDING;
}

अटल SDL_Fullscreen_परिणाम X11_SetWindowFullscreenLegacy(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = _display->internal;
    Display *display = तथ्य->videodata->display;
    स्थिर पूर्णांक screen = displaydata->screen;

    अगर (!तथ्य->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    अगर (तथ्य->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_SyncWindow(_this, window);
    }

    // No window manager? Just make the window the size of the display.
    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    अगर (fullscreen) {
        अगर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ flags = 0;
            X11_XGetWMNormalHints(display, तथ्य->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);
            X11_XSetWMNormalHints(display, तथ्य->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SetWindowBordered(display, screen, तथ्य->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        तथ्य->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        तथ्य->expected.x = rect.x;
        तथ्य->expected.y = rect.y;
        तथ्य->expected.w = rect.w;
        तथ्य->expected.h = rect.h;
        X11_XMoveWindow(display, तथ्य->xwindow, rect.x, rect.y);
        X11_XResizeWindow(display, तथ्य->xwindow, rect.w, rect.h);
        X11_XRaiseWindow(display, तथ्य->xwindow);
    } अन्यथा {
        तथ्य->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        तथ्य->expected.x = window->windowed.x;
        तथ्य->expected.y = window->windowed.y;
        तथ्य->expected.w = window->windowed.w;
        तथ्य->expected.h = window->windowed.h;
        X11_XResizeWindow(display, तथ्य->xwindow, window->windowed.w, window->windowed.h);
        X11_XMoveWindow(display, तथ्य->xwindow, window->windowed.x, window->windowed.y);

        SetWindowBordered(display, screen, तथ्य->xwindow, (window->flags & SDL_WINDOW_BORDERLESS) == 0);
        X11_SetWindowMinMax(तथ्य->window, false);
    }

    X11_XFlush(display);

    वापस SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_परिणाम X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_WINDOW_तथ्य(window);
    CHECK_DISPLAY_तथ्य(_display);

    SDL_Video_तथ्य *तथ्य = _this->internal;
    अगर (तथ्य->net_wm) {
        वापस X11_SetWindowFullscreenViaWM(_this, window, _display, fullscreen);
    }

    वापस X11_SetWindowFullscreenLegacy(_this, window, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

प्रकार काष्ठा
{
    अचिन्हित अक्षर *तथ्य;
    पूर्णांक format, गिनती;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
अटल व्योम X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    अचिन्हित अक्षर *ret = शून्य;
    Atom type;
    पूर्णांक fmt;
    अचिन्हित दीर्घ गिनती;
    अचिन्हित दीर्घ bytes_बायाँ;
    पूर्णांक bytes_fetch = 0;

    करो {
        अगर (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &गिनती, &bytes_बायाँ, &ret);
        bytes_fetch += bytes_बायाँ;
    } जबतक (bytes_बायाँ != 0);

    p->तथ्य = ret;
    p->format = fmt;
    p->गिनती = गिनती;
    p->type = type;
}

व्योम *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    XWindowAttributes attributes;
    Atom icc_profile_atom;
    अक्षर icc_atom_string[माप("_ICC_PROFILE_") + 12];
    व्योम *ret_icc_profile_तथ्य = शून्य;
    CARD8 *icc_profile_तथ्य;
    पूर्णांक real_format;
    अचिन्हित दीर्घ real_nitems;
    SDL_x11Prop atomProp;

    X11_XGetWindowAttributes(display, तथ्य->xwindow, &attributes);
    अगर (X11_XScreen_संख्या_Of_Screen(attributes.screen) > 0) {
        (व्योम)SDL_snprintf(icc_atom_string, माप("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_संख्या_Of_Screen(attributes.screen));
    } अन्यथा {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", माप("_ICC_PROFILE"));
    }
    X11_XGetWindowAttributes(display, मूल_Window_Of_Screen(attributes.screen), &attributes);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    अगर (icc_profile_atom == None) {
        SDL_SetError("Screen is not calibrated.");
        वापस शून्य;
    }

    X11_ReadProperty(&atomProp, display, मूल_Window_Of_Screen(attributes.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.गिनती;
    icc_profile_तथ्य = atomProp.तथ्य;
    अगर (real_format == None) {
        SDL_SetError("Screen is not calibrated.");
        वापस शून्य;
    }

    ret_icc_profile_तथ्य = SDL_malloc(real_nitems);
    अगर (!ret_icc_profile_तथ्य) {
        वापस शून्य;
    }

    SDL_memcpy(ret_icc_profile_तथ्य, icc_profile_तथ्य, real_nitems);
    *आकार = real_nitems;
    X11_XFree(icc_profile_तथ्य);

    वापस ret_icc_profile_तथ्य;
}

bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display;

    अगर (!तथ्य) {
        वापस SDL_SetError("Invalid window data");
    }
    तथ्य->mouse_grabbed = false;
    तथ्य->pending_grab = false;

    display = तथ्य->videodata->display;

    अगर (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        अगर (window->flags & SDL_WINDOW_HIDDEN) {
            वापस true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        अगर (तथ्य->xinput2_mouse_enabled && SDL_GetMouseState(शून्य, शून्य)) {
            तथ्य->pending_grab = true;
            वापस true;
        }

        // Try to grab the mouse
        अगर (!तथ्य->videodata->broken_pointer_grab) {
            स्थिर अचिन्हित पूर्णांक mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            पूर्णांक attempts;
            पूर्णांक परिणाम = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            क्रम (attempts = 0; attempts < 100; attempts++) {
                परिणाम = X11_XGrabPointer(display, तथ्य->xwindow, False, mask, GrabModeAsync,
                                          GrabModeAsync, तथ्य->xwindow, None, CurrentTime);
                अगर (परिणाम == GrabSuccess) {
                    तथ्य->mouse_grabbed = true;
                    अवरोध;
                }
                SDL_Delay(50);
            }

            अगर (परिणाम != GrabSuccess) {
                तथ्य->videodata->broken_pointer_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, window);

        // Raise the window if we grab the mouse
        X11_XRaiseWindow(display, तथ्य->xwindow);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);

        X11_Xinput2UngrabTouch(_this, window);
    }
    X11_XSync(display, False);

    अगर (!तथ्य->videodata->broken_pointer_grab) {
        वापस true;
    } अन्यथा {
        वापस SDL_SetError("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display;

    अगर (!तथ्य) {
        वापस SDL_SetError("Invalid window data");
    }

    display = तथ्य->videodata->display;

    अगर (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        अगर (window->flags & SDL_WINDOW_HIDDEN) {
            वापस true;
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
        अगर (_this->internal->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            अगर (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClientMessageEvent client_message;
                client_message.type = ClientMessage;
                client_message.window = तथ्य->xwindow;
                client_message.format = 32;
                client_message.message_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_message.तथ्य.l[0] = 1;
                client_message.तथ्य.l[1] = CurrentTime;

                X11_XSendEvent(display, Default_मूल_Window(display), False, SubstructureNotifyMask | SubstructureRedirectMask, (XEvent *)&client_message);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, तथ्य->xwindow, True, GrabModeAsync,
                          GrabModeAsync, CurrentTime);
    } अन्यथा {
        X11_XUngrabKeyboard(display, CurrentTime);
    }
    X11_XSync(display, False);

    वापस true;
}

व्योम X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य) {
        SDL_Video_तथ्य *videodata = तथ्य->videodata;
        Display *display = videodata->display;
        पूर्णांक numwindows = videodata->numwindows;
        SDL_Window_तथ्य **windowlist = videodata->windowlist;
        पूर्णांक i;

        अगर (windowlist) {
            क्रम (i = 0; i < numwindows; ++i) {
                अगर (windowlist[i] && (windowlist[i]->window == window)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = शून्य;
                    videodata->numwindows--;
                    अवरोध;
                }
            }
        }

        X11_Destroy_निवेश_Context(तथ्य);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
        X11_TermResizeSync(window);
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

        अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            X11_XDestroyWindow(display, तथ्य->xwindow);
            X11_XFlush(display);
        }
        SDL_free(तथ्य);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        अगर (videodata->active_cursor_confined_window == window) {
            X11_DestroyPointerBarrier(_this, window);
        }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    window->internal = शून्य;
}

bool X11_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    वापस true; // just succeed, the real work is done elsewhere.
}

व्योम X11_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    Atom XdndAware = तथ्य->videodata->atoms.XdndAware;

    अगर (accept) {
        Atom xdnd_version = 5;
        X11_XChangeProperty(display, तथ्य->xwindow, XdndAware, XA_ATOM, 32,
                            PropModeReplace, (अचिन्हित अक्षर *)&xdnd_version, 1);
    } अन्यथा {
        X11_XDeleteProperty(display, तथ्य->xwindow, XdndAware);
    }
}

bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, तथ्य->xwindow);
    अगर (!wmhints) {
        वापस SDL_SetError("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    तथ्य->flashing_window = false;
    तथ्य->flash_cancel_time = 0;

    चयन (operation) {
    हाल SDL_FLASH_CANCEL:
        // Taken care of above
        अवरोध;
    हाल SDL_FLASH_BRIEFLY:
        अगर (!(window->flags & SDL_WINDOW_निवेश_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            तथ्य->flashing_window = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            तथ्य->flash_cancel_time = SDL_GetTicks() + 1000;
        }
        अवरोध;
    हाल SDL_FLASH_UNTIL_FOCUSED:
        अगर (!(window->flags & SDL_WINDOW_निवेश_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            तथ्य->flashing_window = true;
        }
        अवरोध;
    शेष:
        अवरोध;
    }

    X11_XSetWMHints(display, तथ्य->xwindow, wmhints);
    X11_XFree(wmhints);
    वापस true;
}

bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, अक्षर *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    पूर्णांक conv = X11_XmbTextListToTextProperty(display, &title, 1, XTextStyle, &titleprop);
    Status status;

    अगर (X11_XSupportsLocale() != True) {
        वापस SDL_SetError("Current locale not supported by X server, cannot continue.");
    }

    अगर (conv == 0) {
        X11_XSetTextProperty(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.मूल्य);
        // we know this can't be a locale error as we checked X locale validity
    } अन्यथा अगर (conv < 0) {
        वापस SDL_OutOfMemory();
    } अन्यथा { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        वापस true;
    }

#अगर_घोषित X_HAVE_UTF8_STRING
    status = X11_Xutf8TextListToTextProperty(display, &title, 1, XUTF8StringStyle, &titleprop);
    अगर (status == Success) {
        X11_XSetTextProperty(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.मूल्य);
    } अन्यथा {
        वापस SDL_SetError("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#पूर्ण_अगर

    X11_XFlush(display);
    वापस true;
}

व्योम X11_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    Display *display = तथ्य->videodata->display;
    Window मूल = मूल_Window(display, displaydata->screen);
    XClientMessageEvent e;
    Window childReturn;
    पूर्णांक wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, तथ्य->xwindow, मूल, x, y, &wx, &wy, &childReturn);

    e.type = ClientMessage;
    e.window = तथ्य->xwindow;
    e.message_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.तथ्य.l[0] = 0;  // GTK device ID (unused)
    e.तथ्य.l[1] = wx; // X coordinate relative to root
    e.तथ्य.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, मूल, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    अगर ((window->flags & SDL_WINDOW_EXTERNAL) &&
        (तथ्य->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(window);
            वापस true;
    }

    स्थिर Uint64 current_time = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        अगर (_this->displays[i]->internal->mode_switch_deadline_ns &&
            current_time < _this->displays[i]->internal->mode_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->internal->mode_switch_deadline_ns - current_time, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += window->internal->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_TO_NS(1000) : SDL_MS_TO_NS(100);

    वापस X11_SyncWindowTimeout(_this, window, timeout);
}

bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    अगर (!SDL_WINDOW_IS_POPUP(window)) {
        SDL_Window_तथ्य *तथ्य = window->internal;
        Display *display = तथ्य->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, तथ्य->xwindow);
        अगर (!wmhints) {
            वापस SDL_SetError("Couldn't get WM hints");
        }

        wmhints->निवेश = focusable ? True : False;
        wmhints->flags |= निवेश_Hint;

        X11_XSetWMHints(display, तथ्य->xwindow, wmhints);
        X11_XFree(wmhints);
    } अन्यथा अगर (window->flags & SDL_WINDOW_POPUP_MENU) {
        अगर (!(window->flags & SDL_WINDOW_HIDDEN)) {
            अगर (!focusable && (window->flags & SDL_WINDOW_निवेश_FOCUS)) {
                SDL_Window *new_focus;
                स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                X11_SetKeyboardFocus(new_focus, set_focus);
            } अन्यथा अगर (focusable) {
                अगर (SDL_ShouldFocusPopup(window)) {
                    X11_SetKeyboardFocus(window, true);
                }
            }
        }

        वापस true;
    }

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
