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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

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

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "SDL_x11opengles.h"
#यदि_अन्तः

#अन्तर्भाव "SDL_x11xsync.h"

#परिभाषय _NET_WM_STATE_REMOVE 0l
#परिभाषय NET_WM_STATE_सङ्कलय    1l

#परिभाषय CHECK_गवाक्षः_दत्त(गवाक्षः)                                       \
    यदि (!गवाक्षः) {                                                      \
        प्रत्यागम SDL_समुच्चयः_Error("Invalid window");                          \
    }                                                                   \
    यदि (!गवाक्षः->आन्तरिकम्) {                                          \
        प्रत्यागम SDL_समुच्चयः_Error("Invalid window driver data");              \
    }

#परिभाषय CHECK_DISPLAY_दत्त(display)                                     \
    यदि (!_display) {                                                    \
        प्रत्यागम SDL_समुच्चयः_Error("Invalid display");                         \
    }                                                                   \
    यदि (!_display->आन्तरिकम्) {                                        \
        प्रत्यागम SDL_समुच्चयः_Error("Invalid display driver data");             \
    }

स्थिर Bool isMapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    प्रत्यागम ev->type == MapNotify && ev->xmap.गवाक्षः == *((गवाक्षः_2 *)win);
}
स्थिर Bool isUnmapNotify(Display *dpy, XEvent *ev, XPointer win) // NOLINT(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
{
    प्रत्यागम ev->type == UnmapNotify && ev->xunmap.गवाक्षः == *((गवाक्षः_2 *)win);
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
    यदि (desktopVar && SDL_strcasecmp(desktopVar, name) == 0) {
        प्रत्यागम true;
    }

    desktopVar = SDL_GetEnvironmentVariable(env, "XDG_CURRENT_DESKTOP");

    यदि (desktopVar && SDL_strcasestr(desktopVar, name)) {
        प्रत्यागम true;
    }

    प्रत्यागम false;
}

स्थिर bool X11_Is_गवाक्षः_Mapped(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    XWindow_गुणाः attr;

    X11_XGet_गवाक्षः_गुणाः(videodata->display, दत्त->xwindow, &attr);
    यदि (attr.map_state != IsUnmapped) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

स्थिर bool X11_IsDisplayOk(Display *display)
{
    यदि (display->flags & XlibDisplayIOError) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

#यदि 0
स्थिर bool X11_IsActionAllowed(SDL_गवाक्षः *गवाक्षः, Atom action)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Atom _NET_WM_ALLOWED_ACTIONS = दत्त->videodata->_NET_WM_ALLOWED_ACTIONS;
    Atom type;
    Display *display = दत्त->videodata->display;
    पूर्णाङ्क form;
    अचिह्नित दीर्घ remain;
    अचिह्नित दीर्घ len, i;
    Atom *list;
    bool ret = false;

    यदि (X11_XGet_गवाक्षः_Property(display, दत्त->xwindow, _NET_WM_ALLOWED_ACTIONS, 0, 1024, False, XA_ATOM, &type, &form, &len, &remain, (अचिह्नित वर्ण **)&list) == Success) {
        प्रति (i=0; i<len; ++i) {
            यदि (list[i] == action) {
                ret = true;
                भङ्ग;
            }
        }
        X11_XFree(list);
    }
    प्रत्यागम ret;
}
#यदि_अन्तः // 0

स्थिर शून्य X11_FlushPendingEvents(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ध्रुव bool चरमः_position_pending = गवाक्षः->चरमः_position_pending;
    ध्रुव bool चरमः_आकार_pending = गवाक्षः->चरमः_आकार_pending;

    X11_Sync_गवाक्षः(_this, गवाक्षः);

    गवाक्षः->चरमः_position_pending = चरमः_position_pending;
    गवाक्षः->चरमः_आकार_pending = चरमः_आकार_pending;
}

शून्य X11_समुच्चयः_Net_WMState(SDL_VideoDevice *_this, गवाक्षः_2 xwindow, SDL_गवाक्षः_Flags flags)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
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

    यदि (flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्) {
        atoms[गणनम्++] = _NET_WM_STATE_ABOVE;
    }
    यदि (flags & SDL_गवाक्षः_UTILITY) {
        atoms[गणनम्++] = _NET_WM_STATE_SKIP_TASKBAR;
        atoms[गणनम्++] = _NET_WM_STATE_SKIP_PAGER;
    }
    यदि (flags & SDL_गवाक्षः_निवेशः_FOCUS) {
        atoms[गणनम्++] = _NET_WM_STATE_FOCUSED;
    }
    यदि (flags & SDL_गवाक्षः_MAXIMIZED) {
        atoms[गणनम्++] = _NET_WM_STATE_MAXIMIZED_VERT;
        atoms[गणनम्++] = _NET_WM_STATE_MAXIMIZED_HORZ;
    }
    यदि (flags & SDL_गवाक्षः_FULLSCREEN) {
        atoms[गणनम्++] = _NET_WM_STATE_FULLSCREEN;
    }
    यदि (flags & SDL_गवाक्षः_MODAL) {
        atoms[गणनम्++] = _NET_WM_STATE_MODAL;
    }

    SDL_assert(गणनम् <= SDL_arraysize(atoms));

    यदि (गणनम् > 0) {
        X11_XChangeProperty(display, xwindow, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)atoms, गणनम्);
    } अन्यथा {
        X11_XDeleteProperty(display, xwindow, _NET_WM_STATE);
    }
}

स्थिर शून्य X11_ConstrainPopup(SDL_गवाक्षः *गवाक्षः, bool output_गन्तव्यम्_pending)
{
    // Clamp popup windows to the output borders
    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        SDL_गवाक्षः *w;
        SDL_DisplayID displayID;
        SDL_Rect rect;
        पूर्णाङ्क abs_x = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.x : गवाक्षः->floating.x;
        पूर्णाङ्क abs_y = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.y : गवाक्षः->floating.y;
        पूर्णाङ्क विस्थापनम्_x = 0, विस्थापनम्_y = 0;

        यदि (गवाक्षः->constrain_popup) {
            // Calculate the total offset from the parents
            प्रति (w = गवाक्षः->parent; SDL_गवाक्षः_IS_POPUP(w); w = w->parent) {
                विस्थापनम्_x += w->x;
                विस्थापनम्_y += w->y;
            }

            विस्थापनम्_x += w->x;
            विस्थापनम्_y += w->y;
            abs_x += विस्थापनम्_x;
            abs_y += विस्थापनम्_y;

            displayID = SDL_Get_Display_For_गवाक्षः(w);

            SDL_GetDisplayBounds(displayID, &rect);
            यदि (abs_x + गवाक्षः->w > rect.x + rect.w) {
                abs_x -= (abs_x + गवाक्षः->w) - (rect.x + rect.w);
            }
            यदि (abs_y + गवाक्षः->h > rect.y + rect.h) {
                abs_y -= (abs_y + गवाक्षः->h) - (rect.y + rect.h);
            }
            abs_x = SDL_max(abs_x, rect.x);
            abs_y = SDL_max(abs_y, rect.y);
        }

        यदि (output_गन्तव्यम्_pending) {
            गवाक्षः->pending.x = abs_x - विस्थापनम्_x;
            गवाक्षः->pending.y = abs_y - विस्थापनम्_y;
        } अन्यथा {
            गवाक्षः->floating.x = गवाक्षः->windowed.x = abs_x - विस्थापनम्_x;
            गवाक्षः->floating.y = गवाक्षः->windowed.y = abs_y - विस्थापनम्_y;
        }
    }
}

स्थिर शून्य X11_समुच्चयः_Keyboard_Focus(SDL_गवाक्षः *गवाक्षः, bool समुच्चयः_सक्रिय_focus)
{
    SDL_गवाक्षः *toplevel = गवाक्षः;

    // Find the toplevel parent
    यावत् (SDL_गवाक्षः_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = गवाक्षः;

    यदि (समुच्चयः_सक्रिय_focus && !गवाक्षः->is_hiding && !गवाक्षः->is_destroying) {
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    }
}

SDL_गवाक्षः_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, गवाक्षः_2 xwindow)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display = videodata->display;
    Atom _NET_WM_STATE = videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_HIDDEN = videodata->atoms._NET_WM_STATE_HIDDEN;
    Atom _NET_WM_STATE_FOCUSED = videodata->atoms._NET_WM_STATE_FOCUSED;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
    Atom _NET_WM_STATE_FULLSCREEN = videodata->atoms._NET_WM_STATE_FULLSCREEN;
    Atom actualType;
    पूर्णाङ्क actualFormat;
    अचिह्नित दीर्घ i, अङ्कः_वस्तूनि, अष्टकानि_After;
    अचिह्नित वर्ण *property_मानम् = रिक्त;
    दीर्घ max_दीर्घता = 1024;
    SDL_गवाक्षः_Flags flags = 0;

    यदि (X11_XGet_गवाक्षः_Property(display, xwindow, _NET_WM_STATE,
                               0l, max_दीर्घता, False, XA_ATOM, &actualType,
                               &actualFormat, &अङ्कः_वस्तूनि, &अष्टकानि_After,
                               &property_मानम्) == Success) {
        Atom *atoms = (Atom *)property_मानम्;
        पूर्णाङ्क maximized = 0;
        पूर्णाङ्क fullscreen = 0;

        प्रति (i = 0; i < अङ्कः_वस्तूनि; ++i) {
            यदि (atoms[i] == _NET_WM_STATE_HIDDEN) {
                flags |= SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_OCCLUDED;
            } अन्यथा यदि (atoms[i] == _NET_WM_STATE_FOCUSED) {
                flags |= SDL_गवाक्षः_निवेशः_FOCUS;
            } अन्यथा यदि (atoms[i] == _NET_WM_STATE_MAXIMIZED_VERT) {
                maximized |= 1;
            } अन्यथा यदि (atoms[i] == _NET_WM_STATE_MAXIMIZED_HORZ) {
                maximized |= 2;
            } अन्यथा यदि (atoms[i] == _NET_WM_STATE_FULLSCREEN) {
                fullscreen = 1;
            }
        }

        यदि (fullscreen == 1) {
            flags |= SDL_गवाक्षः_FULLSCREEN;
        } अन्यथा यदि (!videodata->net_wm) {
            // If there's no window manager, use whatever the window reports.
            flags |= (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN);
        }

        यदि (maximized == 3) {
            /* Fullscreen windows are maximized on some window managers,
               and this is functional behavior - if maximized is removed,
               the windows remain floating centered and not covering the
               rest of the desktop. So we just won't change the maximize
               state for fullscreen windows here, otherwise SDL would think
               we're always maximized when fullscreen and not restore the
               correct state when leaving fullscreen.
            */
            यदि (fullscreen) {
                flags |= (गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED);
            } अन्यथा {
                flags |= SDL_गवाक्षः_MAXIMIZED;
            }
        }

        /* If the window is unmapped, numItems will be zero and _NET_WM_STATE_HIDDEN
         * will not be set. Do an additional check to see if the window is unmapped
         * and mark it as SDL_WINDOW_HIDDEN if it is.
         */
        {
            XWindow_गुणाः attr;
            SDL_zero(attr);
            X11_XGet_गवाक्षः_गुणाः(videodata->display, xwindow, &attr);
            यदि (attr.map_state == IsUnmapped) {
                flags |= SDL_गवाक्षः_HIDDEN;
            }
        }
        X11_XFree(property_मानम्);
    }

    // FIXME, check the size hints for resizable
    // flags |= SDL_WINDOW_RESIZABLE;

    प्रत्यागम flags;
}

स्थिर bool सज्जता_गवाक्षः_दत्त(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, गवाक्षः_2 w)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    SDL_गवाक्षः_दत्त *दत्त;

    // Allocate the window data
    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }
    दत्त->videodata = videodata;
    दत्त->गवाक्षः = गवाक्षः;
    दत्त->xwindow = w;
    दत्त->लब्धम्_test_परिणाम = SDL_HITTEST_प्रसामान्यम्;

    X11_Create_निवेशः_Context(दत्त);

    // Associate the data with the window

    यदि (videodata->numwindows >= videodata->windowlistlength) {
        SDL_गवाक्षः_दत्त ** new_windowlist = (SDL_गवाक्षः_दत्त **)SDL_realloc(videodata->windowlist, (videodata->numwindows + 1) * परिमाण(*videodata->windowlist));
        यदि (!new_windowlist) {
            गच्छ error_cleanup;
        }
        videodata->windowlistlength++;
        videodata->windowlist = new_windowlist;
    }

    // Fill in the SDL window with the window data
    {
        XWindow_गुणाः attrib;

        X11_XGet_गवाक्षः_गुणाः(दत्त->videodata->display, w, &attrib);
        यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
            गवाक्षः->x = गवाक्षः->windowed.x = गवाक्षः->floating.x = attrib.x;
            गवाक्षः->y = गवाक्षः->windowed.y = गवाक्षः->floating.y = attrib.y - दत्त->border_शिखरम्;
        }
        गवाक्षः->w = गवाक्षः->windowed.w = गवाक्षः->floating.w = attrib.विस्तारः;
        गवाक्षः->h = गवाक्षः->windowed.h = गवाक्षः->floating.h = attrib.height;
        यदि (attrib.map_state != IsUnmapped) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_HIDDEN;
        } अन्यथा {
            गवाक्षः->flags |= SDL_गवाक्षः_HIDDEN;
        }
        दत्त->visual = attrib.visual;
        दत्त->colormap = attrib.colormap;
    }

    गवाक्षः->flags |= X11_GetNetWMState(_this, गवाक्षः, w);

    {
        गवाक्षः_2 Focal_गवाक्षः;
        पूर्णाङ्क Revert_गन्तव्यम् = 0;
        X11_XGet_निवेशः_Focus(दत्त->videodata->display, &Focal_गवाक्षः, &Revert_गन्तव्यम्);
        यदि (Focal_गवाक्षः == w) {
            गवाक्षः->flags |= SDL_गवाक्षः_निवेशः_FOCUS;
        }

        यदि (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
            SDL_समुच्चयः_Keyboard_Focus(दत्त->गवाक्षः);
        }

        यदि (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED) {
            // Tell x11 to clip mouse
        }
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
        // Query the title from the existing window
        गवाक्षः->title = X11_Get_गवाक्षः_Title(_this, w);
    }

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    पूर्णाङ्क screen = (displaydata ? displaydata->screen : 0);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_X11_DISPLAY_POINTER, दत्त->videodata->display);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_X11_SCREEN_सङ्ख्या, screen);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_X11_गवाक्षः_सङ्ख्या, दत्त->xwindow);


#यदि defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2) || defined(SDL_VIDEO_OPENGL_EGL)
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_OPENGL) &&
        ((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) ||
         SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
        && (!_this->gl_दत्त || X11_GL_UseEGL(_this))
#यदि_अन्तः
    ) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (!_this->egl_दत्त) {
            गच्छ error_cleanup;
        }

        // Create the GLES window surface
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)w);

        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            SDL_समुच्चयः_Error("Could not create GLES window surface");
            गच्छ error_cleanup;
        }
#अन्यथा
        SDL_समुच्चयः_Error("Could not create GLES window surface (EGL support not configured)");
        गच्छ error_cleanup;
#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL
    }
#यदि_अन्तः

    // All done!
    गवाक्षः->आन्तरिकम् = दत्त;
    videodata->windowlist[videodata->numwindows++] = दत्त;
    प्रत्यागम true;

error_cleanup:
    X11_Destroy_निवेशः_Context(दत्त);
    SDL_free(दत्त);
    प्रत्यागम false;
}

स्थिर शून्य सज्जता_गवाक्षः_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    दीर्घ fevent = 0;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    गवाक्षः_2 xwindow = दत्त->xwindow;

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (SDL_X11_HAVE_UTF8 && दत्त->ic) {
        X11_XGetICValues(दत्त->ic, XNFilterEvents, &fevent, रिक्त);
    }
#यदि_अन्तः

    X11_Xinput2Select(_this, गवाक्षः);

    {
        अचिह्नित पूर्णाङ्क x11_keyboard_events = कुञ्चिका_Press_आवरणम् | कुञ्चिका_Release_आवरणम्;
        अचिह्नित पूर्णाङ्क x11_pointer_events = Button_Press_आवरणम् | Button_Release_आवरणम् | Pointer_Motion_आवरणम्;

        X11_Xinput2SelectMouseAndKeyboard(_this, गवाक्षः);

        // If XInput2 can handle pointer and keyboard events, we don't track them here
        यदि (दत्त->xinput2_keyboard_enabled) {
            x11_keyboard_events = 0;
        }
        यदि (दत्त->xinput2_mouse_enabled) {
            x11_pointer_events = 0;
        }

        X11_XSelect_निवेशः(दत्त->videodata->display, xwindow,
                         (Focus_Change_आवरणम् | Enter_गवाक्षः_आवरणम् | Leave_गवाक्षः_आवरणम् | Exposure_आवरणम् |
                          x11_keyboard_events | x11_pointer_events |
                          Property_Change_आवरणम् | Structure_Notify_आवरणम् |
                          Keymap_State_आवरणम् | fevent));
    }
}

स्थिर शून्य समुच्चयः_गवाक्षः_Bordered(Display *display, पूर्णाङ्क screen, गवाक्षः_2 गवाक्षः, bool border)
{
    /*
     * this code used to check for KWM_WIN_DECORATION, but KDE hasn't
     *  supported it for years and years. It now respects _MOTIF_WM_HINTS.
     *  Gnome is similar: just use the Motif atom.
     */

    Atom WM_HINTS = X11_XInternAtom(display, "_MOTIF_WM_HINTS", True);
    यदि (WM_HINTS != None) {
        // Hints used by Motif compliant window managers
        संरचना
        {
            अचिह्नित दीर्घ flags;
            अचिह्नित दीर्घ functions;
            अचिह्नित दीर्घ decorations;
            दीर्घ निवेशः_बहुलकम्;
            अचिह्नित दीर्घ स्थितिः;
        } MWMHints = {
            (1L << 1), 0, border ? 1 : 0, 0, 0
        };

        X11_XChangeProperty(display, गवाक्षः, WM_HINTS, WM_HINTS, 32,
                            Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)&MWMHints,
                            परिमाण(MWMHints) / परिमाण(दीर्घ));
    } अन्यथा { // set the transient hints instead, if necessary
        X11_XSetTransientForHint(display, गवाक्षः, मूलम्_गवाक्षः(display, screen));
    }
}

bool X11_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    गवाक्षः_2 w = (गवाक्षः_2)SDL_Get_सङ्ख्या_Property(create_props, SDL_PROP_गवाक्षः_CREATE_X11_गवाक्षः_सङ्ख्या,
                (गवाक्षः_2)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    यदि (w) {
        गवाक्षः->flags |= SDL_गवाक्षः_EXTERNAL;

        यदि (!सज्जता_गवाक्षः_दत्त(_this, गवाक्षः, w)) {
            प्रत्यागम false;
        }

        यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_EXTERNAL_गवाक्षः_निवेशः, true)) {
            सज्जता_गवाक्षः_निवेशः(_this, गवाक्षः);
        }
        प्रत्यागम true;
    }

    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    यदि (!displaydata) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not find display info");
    }

    ध्रुव bool force_override_redirect = SDL_GetHintBoolean(SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT, false);
    ध्रुव bool use_resize_sync = SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_ENABLE_XSYNC_EXT, false) &&
                                 (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) != 0; // Doesn't work well with Vulkan
    SDL_गवाक्षः_दत्त *windowdata;
    Display *display = दत्त->display;
    पूर्णाङ्क screen = displaydata->screen;
    Visual *visual;
    पूर्णाङ्क गभीरता_2;
    XSet_गवाक्षः_गुणाः xattr;
    XSizeHints *sizehints;
    XWMHints *wmhints;
    XClassHint *classhints;
    Atom _NET_WM_BYPASS_COMPOSITOR;
    Atom NET_WM_गवाक्षः_TYPE;
    Atom wintype;
    ध्रुव वर्ण *wintype_name = रिक्त;
    दीर्घ compositor = 1;
    Atom _NET_WM_PID;
    ध्रुव वर्ण *hint = रिक्त;
    पूर्णाङ्क win_x, win_y;
    bool undefined_position = false;

#यदि defined(SDL_VIDEO_OPENGL_GLX) || defined(SDL_VIDEO_OPENGL_EGL)
    ध्रुव पूर्णाङ्क transparent = (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) ? true : false;
    ध्रुव वर्ण *forced_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_गवाक्षः_VISUALID);
    ध्रुव वर्ण *display_visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);

    यदि (forced_visual_id && *forced_visual_id) {
        XVisualInfo *vi, प्रतिरूपम्;
        पूर्णाङ्क nvis;

        SDL_zero(प्रतिरूपम्);
        प्रतिरूपम्.visualid = SDL_strtol(forced_visual_id, रिक्त, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &प्रतिरूपम्, &nvis);
        यदि (vi) {
            visual = vi->visual;
            गभीरता_2 = vi->गभीरता_2;
            X11_XFree(vi);
        } अन्यथा {
            प्रत्यागम false;
        }
    } अन्यथा यदि ((गवाक्षः->flags & SDL_गवाक्षः_OPENGL) &&
               (!display_visual_id || !*display_visual_id)) {
        XVisualInfo *vinfo = रिक्त;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (((_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) ||
             SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false))
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
            && (!_this->gl_दत्त || X11_GL_UseEGL(_this))
#यदि_अन्तः
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen, transparent);
        } अन्यथा
#यदि_अन्तः
        {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen, transparent);
#यदि_अन्तः
        }

        यदि (!vinfo) {
            प्रत्यागम false;
        }
        visual = vinfo->visual;
        गभीरता_2 = vinfo->गभीरता_2;
        X11_XFree(vinfo);
    } अन्यथा
#यदि_अन्तः
    {
        visual = displaydata->visual;
        गभीरता_2 = displaydata->गभीरता_2;
    }

    xattr.override_redirect = ((गवाक्षः->flags & SDL_गवाक्षः_TOOLTIP) || (गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) || force_override_redirect) ? True : False;
    xattr.backing_store = NotUseful;
    xattr.background_pixmap = None;
    xattr.border_pixel = 0;

    यदि (visual->class == प्रत्यक्षम्_Color) {
        XColor *colorcells;
        पूर्णाङ्क i;
        पूर्णाङ्क ncolors;
        पूर्णाङ्क rmax, gmax, bmax;
        पूर्णाङ्क rmask, gmask, bmask;
        पूर्णाङ्क rshift, gshift, bshift;

        xattr.colormap =
            X11_XCreateColormap(display, मूलम्_गवाक्षः(display, screen),
                                visual, AllocAll);

        // If we can't create a colormap, then we must die
        यदि (!xattr.colormap) {
            प्रत्यागम SDL_समुच्चयः_Error("Could not create writable colormap");
        }

        // OK, we got a colormap, now fill it in as best as we can
        colorcells = SDL_malloc(visual->map_entries * परिमाण(XColor));
        यदि (!colorcells) {
            प्रत्यागम false;
        }
        ncolors = visual->map_entries;
        rmax = 0xffff;
        gmax = 0xffff;
        bmax = 0xffff;

        rshift = 0;
        rmask = visual->red_आवरणम्;
        यावत् (0 == (rmask & 1)) {
            rshift++;
            rmask >>= 1;
        }

        gshift = 0;
        gmask = visual->green_आवरणम्;
        यावत् (0 == (gmask & 1)) {
            gshift++;
            gmask >>= 1;
        }

        bshift = 0;
        bmask = visual->blue_आवरणम्;
        यावत् (0 == (bmask & 1)) {
            bshift++;
            bmask >>= 1;
        }

        // build the color table pixel values
        प्रति (i = 0; i < ncolors; i++) {
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
            X11_XCreateColormap(display, मूलम्_गवाक्षः(display, screen),
                                visual, AllocNone);
    }

    यदि (गवाक्षः->undefined_x && गवाक्षः->undefined_y &&
        गवाक्षः->displayID == SDL_GetPrimaryDisplay()) {
        undefined_position = true;
    }

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        X11_ConstrainPopup(गवाक्षः, false);
    }
    SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः,
                                  गवाक्षः->floating.x, गवाक्षः->floating.y,
                                  &win_x, &win_y);

    /* Always create this with the window->floating.* fields; if we're creating a windowed mode window,
     * that's fine. If we're creating a maximized or fullscreen window, the window manager will want to
     * know these values so it can use them if we go _back_ to the base floating windowed mode. SDL manages
     * migration to fullscreen after CreateSDLWindow returns, which will put all the SDL_Window fields and
     * system state as expected.
     */
    w = X11_XCreate_गवाक्षः(display, मूलम्_गवाक्षः(display, screen),
                          win_x, win_y, गवाक्षः->floating.w, गवाक्षः->floating.h,
                          0, गभीरता_2, निवेशः_Output, visual,
                          (CWOverrideRedirect | CWBackPixmap | CWBorderPixel |
                           CWBackingStore | CWColormap),
                          &xattr);
    यदि (!w) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create window");
    }

    /* Don't set the borderless flag if we're about to go fullscreen.
     * This prevents the window manager from moving a full-screen borderless
     * window to a different display before we actually go fullscreen.
     */
    यदि (!(गवाक्षः->pending_flags & SDL_गवाक्षः_FULLSCREEN)) {
        समुच्चयः_गवाक्षः_Bordered(display, screen, w, !(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS));
    }

    sizehints = X11_XAlloc_आकार_Hints();
    // Setup the normal size hints
    sizehints->flags = 0;
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
        sizehints->min_विस्तारः_2 = sizehints->max_विस्तारः_2 = गवाक्षः->floating.w;
        sizehints->min_height = sizehints->max_height = गवाक्षः->floating.h;
        sizehints->flags |= (PMax_आकार | PMin_आकार);
    }
    यदि (!undefined_position) {
        sizehints->x = win_x;
        sizehints->y = win_y;
        sizehints->flags |= USPosition;
    }

    // Setup the input hints so we get keyboard input
    wmhints = X11_XAllocWMHints();
    wmhints->निवेशः = !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE) ? True : False;
    wmhints->गवाक्षः_गणः = दत्त->गवाक्षः_गणः;
    wmhints->flags = निवेशः_Hint | गवाक्षः_गणः_Hint;

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
    यदि (दत्त->pid > 0) {
        दीर्घ pid = (दीर्घ)दत्त->pid;
        _NET_WM_PID = X11_XInternAtom(display, "_NET_WM_PID", False);
        X11_XChangeProperty(display, w, _NET_WM_PID, XA_CARDINAL, 32, Prop_बहुलकम्_Replace,
                            (अचिह्नित वर्ण *)&pid, 1);
    }

    // Set the window manager state
    X11_समुच्चयः_Net_WMState(_this, w, गवाक्षः->flags);

    compositor = 2; // don't disable compositing except for "normal" windows
    hint = SDL_GetHint(SDL_HINT_X11_गवाक्षः_TYPE);
    यदि (गवाक्षः->flags & SDL_गवाक्षः_UTILITY) {
        wintype_name = "_NET_WM_WINDOW_TYPE_UTILITY";
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_TOOLTIP) {
        wintype_name = "_NET_WM_WINDOW_TYPE_TOOLTIP";
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) {
        wintype_name = "_NET_WM_WINDOW_TYPE_POPUP_MENU";
    } अन्यथा यदि (hint && *hint) {
        wintype_name = hint;
    } अन्यथा {
        wintype_name = "_NET_WM_WINDOW_TYPE_NORMAL";
        compositor = 1; // disable compositing for "normal" windows
    }

    // Let the window manager know what type of window we are.
    NET_WM_गवाक्षः_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    wintype = X11_XInternAtom(display, wintype_name, False);
    X11_XChangeProperty(display, w, NET_WM_गवाक्षः_TYPE, XA_ATOM, 32,
                        Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)&wintype, 1);
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, true)) {
        _NET_WM_BYPASS_COMPOSITOR = X11_XInternAtom(display, "_NET_WM_BYPASS_COMPOSITOR", False);
        X11_XChangeProperty(display, w, _NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            Prop_बहुलकम्_Replace,
                            (अचिह्नित वर्ण *)&compositor, 1);
    }

    {
        Atom protocols[4];
        पूर्णाङ्क proto_गणनम् = 0;

        protocols[proto_गणनम्++] = दत्त->atoms.WM_DELETE_गवाक्षः; // Allow window to be deleted by the WM

        // Default to using ping if there is no hint
        यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NET_WM_PING, true)) {
            protocols[proto_गणनम्++] = दत्त->atoms._NET_WM_PING; // Respond so WM knows we're alive
        }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
        यदि (use_resize_sync) {
            protocols[proto_गणनम्++] = दत्त->atoms._NET_WM_SYNC_REQUEST; /* Respond after completing resize */
        }
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

        SDL_assert(proto_गणनम् <= SDL_arraysize(protocols));

        X11_XSetWMProtocols(display, w, protocols, proto_गणनम्);
    }

    यदि (!सज्जता_गवाक्षः_दत्त(_this, गवाक्षः, w)) {
        X11_XDestroy_गवाक्षः(display, w);
        प्रत्यागम false;
    }
    windowdata = गवाक्षः->आन्तरिकम्;

    // Set the parent if this is a non-popup window.
    यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः) && गवाक्षः->parent) {
        X11_XSetTransientForHint(display, w, गवाक्षः->parent->आन्तरिकम्->xwindow);
    }

    // Set the flag if the borders were forced on when creating a fullscreen window for later removal.
    windowdata->fullscreen_borders_forced_on = !!(गवाक्षः->pending_flags & SDL_गवाक्षः_FULLSCREEN) &&
                                               !!(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    यदि (use_resize_sync) {
        X11_InitResizeSync(गवाक्षः);
    }
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSHAPE
    // Tooltips do not receive input
    यदि (गवाक्षः->flags & SDL_गवाक्षः_TOOLTIP) {
        Region region = X11_XCreateRegion();
        X11_XShapeCombineRegion(display, w, Shape_निवेशः, 0, 0, region, Shape_समुच्चयः);
        X11_XDestroyRegion(region);
    }
#यदि_अन्तः

    सज्जता_गवाक्षः_निवेशः(_this, गवाक्षः);

    // For _ICC_PROFILE.
    X11_XSelect_निवेशः(display, मूलम्_गवाक्षः(display, screen), Property_Change_आवरणम्);

    X11_XFlush(display);

    प्रत्यागम true;
}

वर्ण *X11_Get_गवाक्षः_Title(SDL_VideoDevice *_this, गवाक्षः_2 xwindow)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *display = दत्त->display;
    पूर्णाङ्क स्थितिः, real_format;
    Atom real_type;
    अचिह्नित दीर्घ वस्तूनि_read, वस्तूनि_वामः;
    अचिह्नित वर्ण *propdata;
    वर्ण *title = रिक्त;

    स्थितिः = X11_XGet_गवाक्षः_Property(display, xwindow, दत्त->atoms._NET_WM_NAME,
                                    0L, 8192L, False, दत्त->atoms.UTF8_STRING, &real_type, &real_format,
                                    &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
    यदि (स्थितिः == Success && propdata) {
        title = SDL_strdup(SDL_static_cast(वर्ण *, propdata));
        X11_XFree(propdata);
    } अन्यथा {
        स्थितिः = X11_XGet_गवाक्षः_Property(display, xwindow, XA_WM_NAME,
                                        0L, 8192L, False, XA_STRING, &real_type, &real_format,
                                        &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
        यदि (स्थितिः == Success && propdata) {
            title = SDL_iconv_string("UTF-8", "", SDL_static_cast(वर्ण *, propdata), वस्तूनि_read + 1);
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to convert WM_NAME title expecting UTF8! Title: %s", title);
            X11_XFree(propdata);
        } अन्यथा {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not get any window title response from Xorg, returning empty string!");
            title = SDL_strdup("");
        }
    }
    प्रत्यागम title;
}

शून्य X11_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    गवाक्षः_2 xwindow = दत्त->xwindow;
    Display *display = दत्त->videodata->display;
    वर्ण *title = गवाक्षः->title ? गवाक्षः->title : "";

    SDL_X11_समुच्चयः_गवाक्षः_Title(display, xwindow, title);
}

स्थिर bool caught_x11_error = false;
स्थिर पूर्णाङ्क X11_CatchAnyError(Display *d, XErrorEvent *e)
{
    /* this may happen during tumultuous times when we are polling anyhow,
        so just note we had an error and return control. */
    caught_x11_error = true;
    प्रत्यागम 0;
}

स्थिर शून्य X11_ExternalResizeMoveSync(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    पूर्णाङ्क (*पूर्व_handler)(Display *, XErrorEvent *);
    अचिह्नित पूर्णाङ्क child_गणनम्;
    गवाक्षः_2 childReturn, मूलम्, parent;
    गवाक्षः_2 *children;
    XWindow_गुणाः attrs;
    Uint64 timeout = 0;
    पूर्णाङ्क x, y;
    ध्रुव bool send_move = !!(दत्त->pending_operation & X11_PENDING_OP_MOVE);
    ध्रुव bool send_resize = !!(दत्त->pending_operation & X11_PENDING_OP_RESIZE);

    X11_XSync(display, False);
    X11_XQuery_वृक्षः(display, दत्त->xwindow, &मूलम्, &parent, &children, &child_गणनम्);
    पूर्व_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    /* Wait a brief time to see if the window manager decided to let the move or resize happen.
     * If the window changes at all, even to an unexpected value, we break out.
     */
    timeout = SDL_GetTicksNS() + SDL_MS_गन्तव्यम्_NS(100);
    यावत् (true) {
        caught_x11_error = false;
        X11_XSync(display, False);
        X11_XGet_गवाक्षः_गुणाः(display, दत्त->xwindow, &attrs);
        X11_XTranslateCoordinates(display, parent, Default_मूलम्_गवाक्षः(display),
                                  attrs.x, attrs.y, &x, &y, &childReturn);
        SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(गवाक्षः, x, y, &x, &y);

        यदि (!caught_x11_error) {
            यदि ((दत्त->pending_operation & X11_PENDING_OP_MOVE) && (x == दत्त->expected.x + दत्त->border_वामः && y == दत्त->expected.y + दत्त->border_शिखरम्)) {
                दत्त->pending_operation &= ~X11_PENDING_OP_MOVE;
            }
            यदि ((दत्त->pending_operation & X11_PENDING_OP_RESIZE) && (attrs.विस्तारः == दत्त->expected.w && attrs.height == दत्त->expected.h)) {
                दत्त->pending_operation &= ~X11_PENDING_OP_RESIZE;
            }

            यदि (दत्त->pending_operation == X11_PENDING_OP_NONE) {
                भङ्ग;
            }
        }

        यदि (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            दत्त->pending_operation &= ~(X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE);
            दत्त->expected.x = x;
            दत्त->expected.y = y;
            दत्त->expected.w = attrs.विस्तारः;
            दत्त->expected.h = attrs.height;
            भङ्ग;
        }

        SDL_Delay(10);
    }

    यदि (!caught_x11_error) {
        यदि (send_move) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, x, y);
        }
        यदि (send_resize) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, attrs.विस्तारः, attrs.height);
        }
    }

    X11_XSetErrorHandler(पूर्व_handler);
    caught_x11_error = false;
}

/* Wait a brief time, or not, to see if the window manager decided to move/resize the window.
 * Send MOVED and RESIZED window events */
स्थिर bool X11_Sync_गवाक्षः_Timeout(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, Uint64 param_timeout)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    पूर्णाङ्क (*पूर्व_handler)(Display *, XErrorEvent *);
    Uint64 timeout = 0;
    bool force_exit = false;
    bool परिणाम = true;

    X11_XSync(display, False);
    पूर्व_handler = X11_XSetErrorHandler(X11_CatchAnyError);

    यदि (param_timeout) {
        timeout = SDL_GetTicksNS() + param_timeout;
    }

    यावत् (true) {
        X11_XSync(display, False);
        X11_PumpEvents(_this);

        यदि ((दत्त->pending_operation & X11_PENDING_OP_MOVE) && (गवाक्षः->x == दत्त->expected.x + दत्त->border_वामः && गवाक्षः->y == दत्त->expected.y + दत्त->border_शिखरम्)) {
            दत्त->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        यदि ((दत्त->pending_operation & X11_PENDING_OP_RESIZE) && (गवाक्षः->w == दत्त->expected.w && गवाक्षः->h == दत्त->expected.h)) {
            दत्त->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }

        यदि (दत्त->pending_operation == X11_PENDING_OP_NONE) {
            यदि (force_exit ||
                (गवाक्षः->x == दत्त->expected.x + दत्त->border_वामः && गवाक्षः->y == दत्त->expected.y + दत्त->border_शिखरम् &&
                 गवाक्षः->w == दत्त->expected.w && गवाक्षः->h == दत्त->expected.h)) {
                // The window is in the expected state and nothing is pending. Done.
                भङ्ग;
            }

            /* No operations are pending, but the window still isn't in the expected state.
             * Try one more time before exiting.
             */
            force_exit = true;
        }

        यदि (SDL_GetTicksNS() >= timeout) {
            // Timed out without the expected values. Update the requested data so future sync calls won't block.
            दत्त->expected.x = गवाक्षः->x;
            दत्त->expected.y = गवाक्षः->y;
            दत्त->expected.w = गवाक्षः->w;
            दत्त->expected.h = गवाक्षः->h;

            परिणाम = false;
            भङ्ग;
        }

        SDL_Delay(10);
    }

    दत्त->pending_operation = X11_PENDING_OP_NONE;

    यदि (!caught_x11_error) {
        X11_PumpEvents(_this);
    } अन्यथा {
        परिणाम = false;
    }

    X11_XSetErrorHandler(पूर्व_handler);
    caught_x11_error = false;

    प्रत्यागम परिणाम;
}

bool X11_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom _NET_WM_ICON = दत्त->videodata->atoms._NET_WM_ICON;
    पूर्णाङ्क (*पूर्व_Handler)(Display *, XErrorEvent *) = रिक्त;
    bool परिणाम = true;

    यदि (icon) {
        पूर्णाङ्क x, y;
        पूर्णाङ्क propsize;
        दीर्घ *propdata;
        Uint32 *src;
        दीर्घ *dst;

        // Set the _NET_WM_ICON property
        SDL_assert(icon->format == SDL_PIXELFORMAT_ARGB8888);
        propsize = 2 + (icon->w * icon->h);
        propdata = SDL_malloc(propsize * परिमाण(दीर्घ));

        यदि (!propdata) {
            प्रत्यागम false;
        }

        X11_XSync(display, False);
        पूर्व_Handler = X11_XSetErrorHandler(X11_CatchAnyError);

        propdata[0] = icon->w;
        propdata[1] = icon->h;
        dst = &propdata[2];

        प्रति (y = 0; y < icon->h; ++y) {
            src = (Uint32 *)((Uint8 *)icon->pixels + y * icon->pitch);
            प्रति (x = 0; x < icon->w; ++x) {
                *dst++ = *src++;
            }
        }

        X11_XChangeProperty(display, दत्त->xwindow, _NET_WM_ICON, XA_CARDINAL,
                            32, Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)propdata,
                            propsize);
        SDL_free(propdata);

        यदि (caught_x11_error) {
            परिणाम = SDL_समुच्चयः_Error("An error occurred while trying to set the window's icon");
        }
    }

    X11_XFlush(display);

    यदि (पूर्व_Handler) {
        X11_XSetErrorHandler(पूर्व_Handler);
        caught_x11_error = false;
    }

    प्रत्यागम परिणाम;
}

शून्य X11_Update_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः, bool use_current_position)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    ध्रुव पूर्णाङ्क rel_x = use_current_position ? गवाक्षः->x : गवाक्षः->pending.x;
    ध्रुव पूर्णाङ्क rel_y = use_current_position ? गवाक्षः->y : गवाक्षः->pending.y;

    SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः,
                                  rel_x - दत्त->border_वामः, rel_y - दत्त->border_शिखरम्,
                                  &दत्त->expected.x, &दत्त->expected.y);

    // Attempt to move the window
    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        गवाक्षः->आन्तरिकम्->pending_position = true;
    } अन्यथा {
        दत्त->pending_operation |= X11_PENDING_OP_MOVE;
        X11_XMove_गवाक्षः(display, दत्त->xwindow, दत्त->expected.x, दत्त->expected.y);
    }
}

bool X11_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Sync any pending fullscreen or maximize events.
    यदि (गवाक्षः->आन्तरिकम्->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE)) {
        X11_FlushPendingEvents(_this, गवाक्षः);
    }

    // Set the position as pending if the window is maximized with a restore pending.
    यदि (गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED) {
        यदि (गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_RESTORE) {
            गवाक्षः->आन्तरिकम्->pending_position = true;
        }
        प्रत्यागम true;
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
            X11_ConstrainPopup(गवाक्षः, true);
        }
        X11_Update_गवाक्षः_Position(गवाक्षः, false);
    } अन्यथा {
        गवाक्षः->आन्तरिकम्->fs_repositioned = true;
        SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_UPDATE, true);
    }
    प्रत्यागम true;
}

शून्य X11_समुच्चयः_गवाक्षः_Min_Max(SDL_गवाक्षः *गवाक्षः, bool use_current)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
    दीर्घ hint_flags = 0;

    X11_XGetWMNormalHints(display, दत्त->xwindow, sizehints, &hint_flags);
    sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);

    यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) {
        यदि (दत्त->गवाक्षः->min_w || दत्त->गवाक्षः->min_h) {
            sizehints->flags |= PMin_आकार;
            sizehints->min_विस्तारः_2 = दत्त->गवाक्षः->min_w;
            sizehints->min_height = दत्त->गवाक्षः->min_h;
        }
        यदि (दत्त->गवाक्षः->max_w || दत्त->गवाक्षः->max_h) {
            sizehints->flags |= PMax_आकार;
            sizehints->max_विस्तारः_2 = दत्त->गवाक्षः->max_w;
            sizehints->max_height = दत्त->गवाक्षः->max_h;
        }
        यदि (दत्त->गवाक्षः->min_aspect > 0.0f || दत्त->गवाक्षः->max_aspect > 0.0f) {
            sizehints->flags |= PAspect;
            SDL_CalculateFraction(दत्त->गवाक्षः->min_aspect, &sizehints->min_aspect.x, &sizehints->min_aspect.y);
            SDL_CalculateFraction(दत्त->गवाक्षः->max_aspect, &sizehints->max_aspect.x, &sizehints->max_aspect.y);
        }
    } अन्यथा {
        // Set the min/max to the same values to make the window non-resizable
        sizehints->flags |= PMin_आकार | PMax_आकार;
        यदि (use_current) {
            sizehints->min_विस्तारः_2 = sizehints->max_विस्तारः_2 = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : दत्त->गवाक्षः->floating.w;
            sizehints->min_height = sizehints->max_height = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : दत्त->गवाक्षः->floating.h;
        } अन्यथा {
            sizehints->min_विस्तारः_2 = sizehints->max_विस्तारः_2 = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : दत्त->गवाक्षः->windowed.w;
            sizehints->min_height = sizehints->max_height = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : दत्त->गवाक्षः->windowed.h;
        }
    }

    X11_XSetWMNormalHints(display, दत्त->xwindow, sizehints);
    X11_XFree(sizehints);
}

शून्य X11_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        X11_समुच्चयः_गवाक्षः_Min_Max(गवाक्षः, true);
    }
}

शून्य X11_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        X11_समुच्चयः_गवाक्षः_Min_Max(गवाक्षः, true);
    }
}

शून्य X11_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        X11_समुच्चयः_गवाक्षः_Min_Max(गवाक्षः, true);
    }
}

शून्य X11_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;

    /* Wait for pending maximize and fullscreen operations to complete, as these windows
     * don't get size changes.
     */
    यदि (दत्त->pending_operation & (X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_FULLSCREEN)) {
        X11_FlushPendingEvents(_this, गवाक्षः);
    }

    // Set the size as pending if the window is being restored.
    यदि (गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_FULLSCREEN)) {
        // New size will be set when the window is restored.
        यदि (दत्त->pending_operation & X11_PENDING_OP_RESTORE) {
            दत्त->pending_आकार = true;
        } अन्यथा {
            // Can't resize the window.
            गवाक्षः->चरमः_आकार_pending = false;
        }
        प्रत्यागम;
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
            /* Apparently, if the X11 Window is set to a 'non-resizable' window, you cannot resize it using the X11_XResizeWindow, thus
             * we must set the size hints to adjust the window size.
             */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ userhints;
            पूर्णाङ्क dest_x, dest_y;

            X11_XGetWMNormalHints(display, दत्त->xwindow, sizehints, &userhints);

            दत्त->expected.w = sizehints->min_विस्तारः_2 = sizehints->max_विस्तारः_2 = गवाक्षः->pending.w;
            दत्त->expected.h = sizehints->min_height = sizehints->max_height = गवाक्षः->pending.h;
            sizehints->flags |= PMin_आकार | PMax_आकार;
            दत्त->pending_operation |= X11_PENDING_OP_RESIZE;

            X11_XSetWMNormalHints(display, दत्त->xwindow, sizehints);

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
            X11_XResize_गवाक्षः(display, दत्त->xwindow, गवाक्षः->pending.w, गवाक्षः->pending.h);
            ध्रुव पूर्णाङ्क x = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.x : गवाक्षः->x;
            ध्रुव पूर्णाङ्क y = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.y : गवाक्षः->y;
            SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः,
                                          x - दत्त->border_वामः,
                                          y - दत्त->border_शिखरम्,
                                          &dest_x, &dest_y);
            X11_XMove_गवाक्षः(display, दत्त->xwindow, dest_x, dest_y);
            X11_XRaise_गवाक्षः(display, दत्त->xwindow);

            X11_XFree(sizehints);
        }
    } अन्यथा {
        दत्त->expected.w = गवाक्षः->pending.w;
        दत्त->expected.h = गवाक्षः->pending.h;
        दत्त->pending_operation |= X11_PENDING_OP_RESIZE;
        X11_XResize_गवाक्षः(display, दत्त->xwindow, दत्त->expected.w, दत्त->expected.h);
    }

    /* External windows may call this to update the renderer size, but not pump SDL events,
     * so the size event needs to be synthesized for external windows. If it is wrong, the
     * true size will be sent if/when events are processed.
     */
    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः->pending.w, गवाक्षः->pending.h);
    }
}

bool X11_Get_गवाक्षः_Borders_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    *वामः = दत्त->border_वामः;
    *दक्षिणः = दत्त->border_दक्षिणः;
    *शिखरम् = दत्त->border_शिखरम्;
    *bottom = दत्त->border_bottom;

    प्रत्यागम true;
}

bool X11_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom NET_WM_गवाक्षः_OPACITY = दत्त->videodata->atoms.NET_WM_गवाक्षः_OPACITY;

    यदि (opacity == 1.0f) {
        X11_XDeleteProperty(display, दत्त->xwindow, NET_WM_गवाक्षः_OPACITY);
    } अन्यथा {
        ध्रुव Uint32 FullyOpaque = 0xFFFFFFFF;
        ध्रुव दीर्घ alpha = (दीर्घ)((द्विगुण)opacity * (द्विगुण)FullyOpaque);
        X11_XChangeProperty(display, दत्त->xwindow, NET_WM_गवाक्षः_OPACITY, XA_CARDINAL, 32,
                            Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)&alpha, 1);
    }

    प्रत्यागम true;
}

bool X11_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *parent_दत्त = parent ? parent->आन्तरिकम् : रिक्त;
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    Display *display = video_दत्त->display;

    यदि (parent_दत्त) {
        X11_XSetTransientForHint(display, दत्त->xwindow, parent_दत्त->xwindow);
    } अन्यथा {
        X11_XDeleteProperty(display, दत्त->xwindow, video_दत्त->atoms.WM_TRANSIENT_FOR);
    }

    प्रत्यागम true;
}

bool X11_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = video_दत्त->display;
    Uint32 flags = गवाक्षः->flags;
    Atom _NET_WM_STATE = दत्त->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MODAL = दत्त->videodata->atoms._NET_WM_STATE_MODAL;

    यदि (modal) {
        flags |= SDL_गवाक्षः_MODAL;
    } अन्यथा {
        flags &= ~SDL_गवाक्षः_MODAL;
        X11_XDeleteProperty(display, दत्त->xwindow, video_दत्त->atoms.WM_TRANSIENT_FOR);
    }

    यदि (X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_सन्देशः;
        e.xclient.सन्देशः_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.गवाक्षः = दत्त->xwindow;
        e.xclient.दत्त.l[0] = modal ? NET_WM_STATE_सङ्कलय : _NET_WM_STATE_REMOVE;
        e.xclient.दत्त.l[1] = _NET_WM_STATE_MODAL;
        e.xclient.दत्त.l[3] = 0l;

        X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                       Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);
    } अन्यथा {
        X11_समुच्चयः_Net_WMState(_this, दत्त->xwindow, flags);
    }

    X11_XFlush(display);

    प्रत्यागम true;
}

शून्य X11_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered)
{
    ध्रुव bool focused = (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) != 0;
    ध्रुव bool visible = !(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) && !गवाक्षः->is_hiding;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;
    XEvent event;

    यदि (दत्त->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        समुच्चयः_गवाक्षः_Bordered(display, displaydata->screen, दत्त->xwindow, bordered);
        X11_XFlush(display);

        यदि (visible) {
            XWindow_गुणाः attr;
            कुरु {
                X11_XSync(display, False);
                X11_XGet_गवाक्षः_गुणाः(display, दत्त->xwindow, &attr);
            } यावत् (attr.map_state != IsViewable);

            यदि (focused) {
                X11_XSet_निवेशः_Focus(display, दत्त->xwindow, Revert_गन्तव्यम्_Parent, CurrentTime);
            }
        }

        // make sure these don't make it to the real event queue if they fired here.
        X11_XSync(display, False);
        X11_XCheckIfEvent(display, &event, &isUnmapNotify, (XPointer)&दत्त->xwindow);
        X11_XCheckIfEvent(display, &event, &isMapNotify, (XPointer)&दत्त->xwindow);

        // Turning the borders off doesn't send an extent event, so they must be cleared here.
        X11_Get_Border_मानानि(दत्त);

        // Make sure the window manager didn't resize our window for the difference.
        X11_XResize_गवाक्षः(display, दत्त->xwindow, गवाक्षः->floating.w, गवाक्षः->floating.h);
        X11_XSync(display, False);
    } अन्यथा {
        // If fullscreen, set a flag to toggle the borders when returning to windowed mode.
        दत्त->toggle_borders = true;
        दत्त->fullscreen_borders_forced_on = false;
    }
}

शून्य X11_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त->pending_operation & X11_PENDING_OP_FULLSCREEN) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    // If the window is fullscreen, the resize capability will be set/cleared when it is returned to windowed mode.
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        X11_समुच्चयः_गवाक्षः_Min_Max(गवाक्षः, true);
    }
}

शून्य X11_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;
    Atom _NET_WM_STATE = दत्त->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_ABOVE = दत्त->videodata->atoms._NET_WM_STATE_ABOVE;

    यदि (X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_सन्देशः;
        e.xclient.सन्देशः_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.गवाक्षः = दत्त->xwindow;
        e.xclient.दत्त.l[0] =
            on_शिखरम् ? NET_WM_STATE_सङ्कलय : _NET_WM_STATE_REMOVE;
        e.xclient.दत्त.l[1] = _NET_WM_STATE_ABOVE;
        e.xclient.दत्त.l[3] = 0l;

        X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                       Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);
    } अन्यथा {
        X11_समुच्चयः_Net_WMState(_this, दत्त->xwindow, गवाक्षः->flags);
    }
    X11_XFlush(display);
}

शून्य X11_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ACTIVATE_WHEN_SHOWN, true);
    bool समुच्चयः_position = false;
    XEvent event;

    // If the window was previously shown, pump events to avoid possible positioning issues.
    यदि (दत्त->was_shown) {
        X11_PumpEvents(_this);
    }

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        // Update the position in case the parent moved while we were hidden
        X11_ConstrainPopup(गवाक्षः, true);
        दत्त->pending_position = true;
        समुच्चयः_position = true;
    }

    /* Whether XMapRaised focuses the window is based on the window type and it is
     * wm specific. There isn't much we can do here */
    (शून्य)bActivate;

    यदि (!X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        X11_XMapRaised(display, दत्त->xwindow);
        /* Blocking wait for "MapNotify" event.
         * We use X11_XIfEvent because pXWindowEvent takes a mask rather than a type,
         * and XCheckTypedWindowEvent doesn't block */
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) && X11_IsDisplayOk(display)) {
            X11_XIfEvent(display, &event, &isMapNotify, (XPointer)&दत्त->xwindow);
        }
        X11_XFlush(display);
        समुच्चयः_position = दत्त->pending_position ||
                       (!(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) && !गवाक्षः->undefined_x && !गवाक्षः->undefined_y);
    }

    यदि (!दत्त->videodata->net_wm) {
        // no WM means no FocusIn event, which confuses us. Force it.
        X11_XSync(display, False);
        X11_XSet_निवेशः_Focus(display, दत्त->xwindow, Revert_गन्तव्यम्_None, CurrentTime);
        X11_XFlush(display);
    }

    // Grabbing popup menus get keyboard focus.
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
        X11_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
    }

    // Get some valid border values, if we haven't received them yet
    यदि (दत्त->border_वामः == 0 && दत्त->border_दक्षिणः == 0 && दत्त->border_शिखरम् == 0 && दत्त->border_bottom == 0) {
        X11_Get_Border_मानानि(दत्त);
    }

    यदि (समुच्चयः_position) {
        // Apply the window position, accounting for offsets due to the borders appearing, but only when initially mapping.
        ध्रुव पूर्णाङ्क tx = (दत्त->pending_position ? गवाक्षः->pending.x : गवाक्षः->x) - (दत्त->was_shown ? 0 : दत्त->border_वामः);
        ध्रुव पूर्णाङ्क ty = (दत्त->pending_position ? गवाक्षः->pending.y : गवाक्षः->y) - (दत्त->was_shown ? 0 : दत्त->border_शिखरम्);
        पूर्णाङ्क x, y;

        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, tx, ty, &x, &y);

        दत्त->pending_position = false;
        X11_XMove_गवाक्षः(display, दत्त->xwindow, x, y);
    }

    /* XMonad ignores size hints and shrinks the client area to overlay borders on fixed-size windows,
     * even if no borders were requested, resulting in the window client area being smaller than
     * requested. Calling XResizeWindow after mapping seems to fix it, even though resizing fixed-size
     * windows in this manner doesn't work on any other window manager.
     */
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) && X11_CheckCurrentDesktop("xmonad")) {
        X11_XResize_गवाक्षः(display, दत्त->xwindow, गवाक्षः->w, गवाक्षः->h);
    }

    /* Some window managers can send garbage coordinates while mapping the window, so don't emit size and position
     * events during the initial configure events.
     */
    दत्त->आकार_move_event_flags = X11_आकार_MOVE_EVENTS_DISABLE;
    X11_XSync(display, False);
    X11_PumpEvents(_this);
    दत्त->आकार_move_event_flags = 0;

    /* A MapNotify or PropertyNotify may not have arrived, so ensure that the shown event is dispatched
     * to apply pending state before clearing the flag.
     */
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
    दत्त->was_shown = true;

    // If a configure event was received (type is non-zero), send the final window size and coordinates.
    यदि (दत्त->चरमः_xconfigure.type) {
        पूर्णाङ्क x, y;
        SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(दत्त->गवाक्षः, दत्त->चरमः_xconfigure.x, दत्त->चरमः_xconfigure.y, &x, &y);
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, दत्त->चरमः_xconfigure.विस्तारः, दत्त->चरमः_xconfigure.height);
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, x, y);
    }
}

शून्य X11_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    पूर्णाङ्क screen = (displaydata ? displaydata->screen : 0);
    Display *display = दत्त->videodata->display;
    XEvent event;

    /* Some window managers will mark minimized or offscreen windows as unmapped, so we
     * must not block while waiting for an UnmapNotify event that will never arrive.
     */
    ध्रुव bool is_mapped = X11_Is_गवाक्षः_Mapped(_this, गवाक्षः);
    X11_XWithdraw_गवाक्षः(display, दत्त->xwindow, screen);
    यदि (is_mapped && !(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) && X11_IsDisplayOk(display)) {
        // Blocking wait for "UnmapNotify" event.
        X11_XIfEvent(display, &event, &isUnmapNotify, (XPointer)&दत्त->xwindow);
    }
    X11_XFlush(display);

    // Transfer keyboard focus back to the parent
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
        SDL_गवाक्षः *new_focus;
        ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(गवाक्षः, &new_focus);
        X11_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
    }

    X11_XSync(display, False);
    X11_PumpEvents(_this);
}

स्थिर bool X11_समुच्चयः_गवाक्षः_सक्रिय(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_दत्त(गवाक्षः);

    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;
    Atom NET_सक्रिय_गवाक्षः = दत्त->videodata->atoms.NET_सक्रिय_गवाक्षः;

    यदि (X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        XEvent e;

        // printf("SDL Window %p: sending _NET_ACTIVE_WINDOW with timestamp %lu\n", window, data->user_time);

        SDL_zero(e);
        e.xany.type = Client_सन्देशः;
        e.xclient.सन्देशः_type = NET_सक्रिय_गवाक्षः;
        e.xclient.format = 32;
        e.xclient.गवाक्षः = दत्त->xwindow;
        e.xclient.दत्त.l[0] = 1; // source indication. 1 = application
        e.xclient.दत्त.l[1] = दत्त->user_time;
        e.xclient.दत्त.l[2] = 0;

        X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                       Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);

        X11_XFlush(display);
    }
    प्रत्यागम true;
}

शून्य X11_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    bool bActivate = SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ACTIVATE_WHEN_RAISED, true);

    X11_XRaise_गवाक्षः(display, दत्त->xwindow);
    यदि (bActivate) {
        X11_समुच्चयः_गवाक्षः_सक्रिय(_this, गवाक्षः);
    }
    X11_XFlush(display);
}

स्थिर bool X11_समुच्चयः_गवाक्षः_Maximized(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool maximized)
{
    CHECK_गवाक्षः_दत्त(गवाक्षः);

    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;
    Atom _NET_WM_STATE = दत्त->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = दत्त->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = दत्त->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;

    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        /* Fullscreen windows are maximized on some window managers,
           and this is functional behavior, so don't remove that state
           now, we'll take care of it when we leave fullscreen mode.
         */
        प्रत्यागम true;
    }

    यदि (X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        XEvent e;

        SDL_zero(e);
        e.xany.type = Client_सन्देशः;
        e.xclient.सन्देशः_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.गवाक्षः = दत्त->xwindow;
        e.xclient.दत्त.l[0] =
            maximized ? NET_WM_STATE_सङ्कलय : _NET_WM_STATE_REMOVE;
        e.xclient.दत्त.l[1] = _NET_WM_STATE_MAXIMIZED_VERT;
        e.xclient.दत्त.l[2] = _NET_WM_STATE_MAXIMIZED_HORZ;
        e.xclient.दत्त.l[3] = 0l;

        यदि (maximized) {
            SDL_DisplayID displayID = SDL_Get_Display_For_गवाक्षः(गवाक्षः);
            SDL_Rect bounds;

            SDL_zero(bounds);
            SDL_GetDisplayUsableBounds(displayID, &bounds);

            दत्त->expected.x = bounds.x + दत्त->border_वामः;
            दत्त->expected.y = bounds.y + दत्त->border_शिखरम्;
            दत्त->expected.w = bounds.w - (दत्त->border_वामः + दत्त->border_दक्षिणः);
            दत्त->expected.h = bounds.h - (दत्त->border_शिखरम् + दत्त->border_bottom);
        } अन्यथा {
            दत्त->expected.x = गवाक्षः->floating.x;
            दत्त->expected.y = गवाक्षः->floating.y;
            दत्त->expected.w = गवाक्षः->floating.w;
            दत्त->expected.h = गवाक्षः->floating.h;
        }

        X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                       Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);
    } अन्यथा {
        X11_समुच्चयः_Net_WMState(_this, दत्त->xwindow, गवाक्षः->flags);
    }
    X11_XFlush(display);

    प्रत्यागम true;
}

शून्य X11_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_गवाक्षः(गवाक्षः);
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        // If fullscreen, just toggle the restored state.
        गवाक्षः->आन्तरिकम्->गवाक्षः_was_maximized = true;
        प्रत्यागम;
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        गवाक्षः->आन्तरिकम्->pending_operation |= X11_PENDING_OP_MAXIMIZE;
        X11_समुच्चयः_गवाक्षः_Maximized(_this, गवाक्षः, true);
    }
}

शून्य X11_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;

    यदि (दत्त->pending_operation & SDL_गवाक्षः_FULLSCREEN) {
        SDL_Sync_गवाक्षः(गवाक्षः);
    }

    दत्त->pending_operation |= X11_PENDING_OP_MINIMIZE;
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        दत्त->गवाक्षः_was_maximized = !!(गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED);
    }
    X11_XIconify_गवाक्षः(display, दत्त->xwindow, displaydata->screen);
    X11_XFlush(display);
}

शून्य X11_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Don't restore the window the first time it is being shown.
    यदि (!गवाक्षः->आन्तरिकम्->was_shown) {
        प्रत्यागम;
    }

    यदि (गवाक्षः->आन्तरिकम्->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MINIMIZE)) {
        SDL_Sync_गवाक्षः(गवाक्षः);
    }

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && !(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        // If fullscreen and not minimized, just toggle the restored state.
        गवाक्षः->आन्तरिकम्->गवाक्षः_was_maximized = false;
        प्रत्यागम;
    }

    यदि (गवाक्षः->flags & (SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_MAXIMIZED) ||
        (गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_MINIMIZE)) {
        गवाक्षः->आन्तरिकम्->pending_operation |= X11_PENDING_OP_RESTORE;
    }

    // If the window was minimized while maximized, restore as maximized.
    ध्रुव bool maximize = !!(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) && गवाक्षः->आन्तरिकम्->गवाक्षः_was_maximized;
    X11_समुच्चयः_गवाक्षः_Maximized(_this, गवाक्षः, maximize);
    X11_Show_गवाक्षः(_this, गवाक्षः);
    X11_समुच्चयः_गवाक्षः_सक्रिय(_this, गवाक्षः);
}

// This asks the Window Manager to handle fullscreen for us. This is the modern way.
स्थिर SDL_Fullscreen_परिणाम X11_समुच्चयः_गवाक्षः_Fullscreen_द्वारा_WM(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = _display->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom _NET_WM_STATE = दत्त->videodata->atoms._NET_WM_STATE;
    Atom _NET_WM_STATE_FULLSCREEN = दत्त->videodata->atoms._NET_WM_STATE_FULLSCREEN;

    यदि (!दत्त->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (X11_Is_गवाक्षः_Mapped(_this, गवाक्षः)) {
        XEvent e;

        // Flush any pending fullscreen events.
        यदि (दत्त->pending_operation & (X11_PENDING_OP_FULLSCREEN | X11_PENDING_OP_MAXIMIZE | X11_PENDING_OP_MOVE)) {
            X11_Sync_गवाक्षः(_this, गवाक्षः);
        }

        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
            यदि (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
                // Request was out of date; set -1 to signal the video core to undo a mode switch.
                प्रत्यागम SDL_FULLSCREEN_FAILED;
            } अन्यथा यदि (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
                // Nothing to do.
                प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
            }
        }

        यदि (fullscreen && !(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
               can be resized to the fullscreen resolution (or reset so we're not resizable again) */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ flags = 0;
            X11_XGetWMNormalHints(display, दत्त->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);
            X11_XSetWMNormalHints(display, दत्त->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        SDL_zero(e);
        e.xany.type = Client_सन्देशः;
        e.xclient.सन्देशः_type = _NET_WM_STATE;
        e.xclient.format = 32;
        e.xclient.गवाक्षः = दत्त->xwindow;
        e.xclient.दत्त.l[0] =
            fullscreen ? NET_WM_STATE_सङ्कलय : _NET_WM_STATE_REMOVE;
        e.xclient.दत्त.l[1] = _NET_WM_STATE_FULLSCREEN;
        e.xclient.दत्त.l[3] = 0l;

        X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                       Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);

        // Only set the pending flag if the fullscreen state actually changed.
        यदि (((गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) != 0) != (fullscreen != 0)) {
            दत्त->pending_operation |= X11_PENDING_OP_FULLSCREEN;
        }

        // Set the position so the window will be on the target display
        यदि (fullscreen) {
            SDL_DisplayID current = SDL_Get_Display_For_गवाक्षः_Position(गवाक्षः);
            SDL_copyp(&दत्त->requested_fullscreen_बहुलकम्, &गवाक्षः->current_fullscreen_बहुलकम्);
            यदि (fullscreen != !!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
                दत्त->गवाक्षः_was_maximized = !!(गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED);
            }
            दत्त->expected.x = displaydata->x;
            दत्त->expected.y = displaydata->y;
            दत्त->expected.w = _display->current_बहुलकम्->w;
            दत्त->expected.h = _display->current_बहुलकम्->h;

            // Only move the window if it isn't already on the target display.
            यदि (!current || current != _display->id) {
                X11_XMove_गवाक्षः(display, दत्त->xwindow, displaydata->x, displaydata->y);
                दत्त->pending_operation |= X11_PENDING_OP_MOVE;
            }
        } अन्यथा {
            SDL_zero(दत्त->requested_fullscreen_बहुलकम्);
            दत्त->pending_position = दत्त->fs_repositioned;
            दत्त->fs_repositioned = false;

            /* Fullscreen windows sometimes end up being marked maximized by
             * window managers. Force it back to how we expect it to be.
             */
            SDL_zero(e);
            e.xany.type = Client_सन्देशः;
            e.xclient.सन्देशः_type = _NET_WM_STATE;
            e.xclient.format = 32;
            e.xclient.गवाक्षः = दत्त->xwindow;
            यदि (दत्त->गवाक्षः_was_maximized) {
                e.xclient.दत्त.l[0] = NET_WM_STATE_सङ्कलय;
            } अन्यथा {
                e.xclient.दत्त.l[0] = _NET_WM_STATE_REMOVE;
            }
            e.xclient.दत्त.l[1] = दत्त->videodata->atoms._NET_WM_STATE_MAXIMIZED_VERT;
            e.xclient.दत्त.l[2] = दत्त->videodata->atoms._NET_WM_STATE_MAXIMIZED_HORZ;
            e.xclient.दत्त.l[3] = 0l;
            X11_XSendEvent(display, मूलम्_गवाक्षः(display, displaydata->screen), 0,
                           Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, &e);
        }
    } अन्यथा {
        SDL_गवाक्षः_Flags flags;

        flags = गवाक्षः->flags;
        यदि (fullscreen) {
            flags |= SDL_गवाक्षः_FULLSCREEN;
        } अन्यथा {
            flags &= ~SDL_गवाक्षः_FULLSCREEN;
        }
        X11_समुच्चयः_Net_WMState(_this, दत्त->xwindow, flags);
    }

    यदि (दत्त->visual->class == प्रत्यक्षम्_Color) {
        यदि (fullscreen) {
            X11_XInstallColormap(display, दत्त->colormap);
        } अन्यथा {
            X11_XUninstallColormap(display, दत्त->colormap);
        }
    }

    प्रत्यागम SDL_FULLSCREEN_PENDING;
}

स्थिर SDL_Fullscreen_परिणाम X11_समुच्चयः_गवाक्षः_Fullscreen_Legacy(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *_display, bool fullscreen)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = _display->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    ध्रुव पूर्णाङ्क screen = displaydata->screen;

    यदि (!दत्त->was_shown && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    // Flush any pending fullscreen events.
    यदि (दत्त->pending_operation & (X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) {
        X11_Sync_गवाक्षः(_this, गवाक्षः);
    }

    // No window manager? Just make the window the size of the display.
    SDL_Send_गवाक्षः_Event(गवाक्षः, fullscreen ? SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN : SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
    यदि (fullscreen) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
            /* Compiz refuses fullscreen toggle if we're not resizable, so update the hints so we
             * can be resized to the fullscreen resolution (or reset so we're not resizable again).
             */
            XSizeHints *sizehints = X11_XAlloc_आकार_Hints();
            दीर्घ flags = 0;
            X11_XGetWMNormalHints(display, दत्त->xwindow, sizehints, &flags);
            // we are going fullscreen so turn the flags off
            sizehints->flags &= ~(PMin_आकार | PMax_आकार | PAspect);
            X11_XSetWMNormalHints(display, दत्त->xwindow, sizehints);
            X11_XFree(sizehints);
        }

        समुच्चयः_गवाक्षः_Bordered(display, screen, दत्त->xwindow, false);

        SDL_Rect rect;
        X11_GetDisplayBounds(_this, _display, &rect);

        दत्त->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        दत्त->expected.x = rect.x;
        दत्त->expected.y = rect.y;
        दत्त->expected.w = rect.w;
        दत्त->expected.h = rect.h;
        X11_XMove_गवाक्षः(display, दत्त->xwindow, rect.x, rect.y);
        X11_XResize_गवाक्षः(display, दत्त->xwindow, rect.w, rect.h);
        X11_XRaise_गवाक्षः(display, दत्त->xwindow);
    } अन्यथा {
        दत्त->pending_operation |= X11_PENDING_OP_MOVE | X11_PENDING_OP_RESIZE;
        दत्त->expected.x = गवाक्षः->windowed.x;
        दत्त->expected.y = गवाक्षः->windowed.y;
        दत्त->expected.w = गवाक्षः->windowed.w;
        दत्त->expected.h = गवाक्षः->windowed.h;
        X11_XResize_गवाक्षः(display, दत्त->xwindow, गवाक्षः->windowed.w, गवाक्षः->windowed.h);
        X11_XMove_गवाक्षः(display, दत्त->xwindow, गवाक्षः->windowed.x, गवाक्षः->windowed.y);

        समुच्चयः_गवाक्षः_Bordered(display, screen, दत्त->xwindow, (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) == 0);
        X11_समुच्चयः_गवाक्षः_Min_Max(दत्त->गवाक्षः, false);
    }

    X11_XFlush(display);

    प्रत्यागम SDL_FULLSCREEN_PENDING;
}

SDL_Fullscreen_परिणाम X11_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen)
{
    CHECK_गवाक्षः_दत्त(गवाक्षः);
    CHECK_DISPLAY_दत्त(_display);

    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    यदि (दत्त->net_wm) {
        प्रत्यागम X11_समुच्चयः_गवाक्षः_Fullscreen_द्वारा_WM(_this, गवाक्षः, _display, fullscreen);
    }

    प्रत्यागम X11_समुच्चयः_गवाक्षः_Fullscreen_Legacy(_this, गवाक्षः, _display, fullscreen != SDL_FULLSCREEN_OP_LEAVE);
}

प्रकारनिर्देश संरचना
{
    अचिह्नित वर्ण *दत्त;
    पूर्णाङ्क format, गणनम्;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
स्थिर शून्य X11_ReadProperty(SDL_x11Prop *p, Display *disp, गवाक्षः_2 w, Atom prop)
{
    अचिह्नित वर्ण *ret = रिक्त;
    Atom type;
    पूर्णाङ्क fmt;
    अचिह्नित दीर्घ गणनम्;
    अचिह्नित दीर्घ अष्टकानि_वामः;
    पूर्णाङ्क अष्टकानि_fetch = 0;

    कुरु {
        यदि (ret) {
            X11_XFree(ret);
        }
        X11_XGet_गवाक्षः_Property(disp, w, prop, 0, अष्टकानि_fetch, False, AnyPropertyType, &type, &fmt, &गणनम्, &अष्टकानि_वामः, &ret);
        अष्टकानि_fetch += अष्टकानि_वामः;
    } यावत् (अष्टकानि_वामः != 0);

    p->दत्त = ret;
    p->format = fmt;
    p->गणनम् = गणनम्;
    p->type = type;
}

शून्य *X11_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    XWindow_गुणाः गुणाः;
    Atom icc_profile_atom;
    वर्ण icc_atom_string[परिमाण("_ICC_PROFILE_") + 12];
    शून्य *ret_icc_profile_दत्त = रिक्त;
    CARD8 *icc_profile_दत्त;
    पूर्णाङ्क real_format;
    अचिह्नित दीर्घ real_nitems;
    SDL_x11Prop atomProp;

    X11_XGet_गवाक्षः_गुणाः(display, दत्त->xwindow, &गुणाः);
    यदि (X11_XScreen_सङ्ख्या_सम्बन्धि_Screen(गुणाः.screen) > 0) {
        (शून्य)SDL_snprintf(icc_atom_string, परिमाण("_ICC_PROFILE_") + 12, "%s%d", "_ICC_PROFILE_", X11_XScreen_सङ्ख्या_सम्बन्धि_Screen(गुणाः.screen));
    } अन्यथा {
        SDL_strlcpy(icc_atom_string, "_ICC_PROFILE", परिमाण("_ICC_PROFILE"));
    }
    X11_XGet_गवाक्षः_गुणाः(display, मूलम्_गवाक्षः_सम्बन्धि_Screen(गुणाः.screen), &गुणाः);

    icc_profile_atom = X11_XInternAtom(display, icc_atom_string, True);
    यदि (icc_profile_atom == None) {
        SDL_समुच्चयः_Error("Screen is not calibrated.");
        प्रत्यागम रिक्त;
    }

    X11_ReadProperty(&atomProp, display, मूलम्_गवाक्षः_सम्बन्धि_Screen(गुणाः.screen), icc_profile_atom);
    real_format = atomProp.format;
    real_nitems = atomProp.गणनम्;
    icc_profile_दत्त = atomProp.दत्त;
    यदि (real_format == None) {
        SDL_समुच्चयः_Error("Screen is not calibrated.");
        प्रत्यागम रिक्त;
    }

    ret_icc_profile_दत्त = SDL_malloc(real_nitems);
    यदि (!ret_icc_profile_दत्त) {
        प्रत्यागम रिक्त;
    }

    SDL_memcpy(ret_icc_profile_दत्त, icc_profile_दत्त, real_nitems);
    *आकार = real_nitems;
    X11_XFree(icc_profile_दत्त);

    प्रत्यागम ret_icc_profile_दत्त;
}

bool X11_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display;

    यदि (!दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid window data");
    }
    दत्त->mouse_grabbed = false;
    दत्त->pending_grab = false;

    display = दत्त->videodata->display;

    यदि (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
            प्रत्यागम true;
        }

        /* If XInput2 is enabled, it will grab the pointer on button presses,
         * which results in XGrabPointer returning AlreadyGrabbed. If buttons
         * are currently pressed, clear any existing grabs before attempting
         * the confinement grab.
         */
        यदि (दत्त->xinput2_mouse_enabled && SDL_GetMouseState(रिक्त, रिक्त)) {
            दत्त->pending_grab = true;
            प्रत्यागम true;
        }

        // Try to grab the mouse
        यदि (!दत्त->videodata->broken_pointer_grab) {
            ध्रुव अचिह्नित पूर्णाङ्क आवरणम् = Button_Press_आवरणम् | Button_Release_आवरणम् | Pointer_Motion_आवरणम् | Focus_Change_आवरणम्;
            पूर्णाङ्क attempts;
            पूर्णाङ्क परिणाम = 0;

            // Try for up to 5000ms (5s) to grab. If it still fails, stop trying.
            प्रति (attempts = 0; attempts < 100; attempts++) {
                परिणाम = X11_XGrabPointer(display, दत्त->xwindow, False, आवरणम्, Grab_बहुलकम्_Async,
                                          Grab_बहुलकम्_Async, दत्त->xwindow, None, CurrentTime);
                यदि (परिणाम == GrabSuccess) {
                    दत्त->mouse_grabbed = true;
                    भङ्ग;
                }
                SDL_Delay(50);
            }

            यदि (परिणाम != GrabSuccess) {
                दत्त->videodata->broken_pointer_grab = true; // don't try again.
            }
        }

        X11_Xinput2GrabTouch(_this, गवाक्षः);

        // Raise the window if we grab the mouse
        X11_XRaise_गवाक्षः(display, दत्त->xwindow);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);

        X11_Xinput2UngrabTouch(_this, गवाक्षः);
    }
    X11_XSync(display, False);

    यदि (!दत्त->videodata->broken_pointer_grab) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("The X server refused to let us grab the mouse. You might experience input bugs.");
    }
}

bool X11_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display;

    यदि (!दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid window data");
    }

    display = दत्त->videodata->display;

    यदि (grabbed) {
        /* If the window is unmapped, XGrab calls return GrabNotViewable,
           so when we get a MapNotify later, we'll try to update the grab as
           appropriate. */
        यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
            प्रत्यागम true;
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
        यदि (_this->आन्तरिकम्->is_xwayland) {
            Atom _XWAYLAND_MAY_GRAB_ATOM = X11_XInternAtom(display, "_XWAYLAND_MAY_GRAB_KEYBOARD", False);

            यदि (_XWAYLAND_MAY_GRAB_ATOM != None) {
                XClient_सन्देशः_Event client_सन्देशः;
                client_सन्देशः.type = Client_सन्देशः;
                client_सन्देशः.गवाक्षः = दत्त->xwindow;
                client_सन्देशः.format = 32;
                client_सन्देशः.सन्देशः_type = _XWAYLAND_MAY_GRAB_ATOM;
                client_सन्देशः.दत्त.l[0] = 1;
                client_सन्देशः.दत्त.l[1] = CurrentTime;

                X11_XSendEvent(display, Default_मूलम्_गवाक्षः(display), False, Substructure_Notify_आवरणम् | Substructure_Redirect_आवरणम्, (XEvent *)&client_सन्देशः);
                X11_XFlush(display);
            }
        }

        X11_XGrabKeyboard(display, दत्त->xwindow, True, Grab_बहुलकम्_Async,
                          Grab_बहुलकम्_Async, CurrentTime);
    } अन्यथा {
        X11_XUngrabKeyboard(display, CurrentTime);
    }
    X11_XSync(display, False);

    प्रत्यागम true;
}

शून्य X11_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त) {
        SDL_Video_दत्त *videodata = दत्त->videodata;
        Display *display = videodata->display;
        पूर्णाङ्क numwindows = videodata->numwindows;
        SDL_गवाक्षः_दत्त **windowlist = videodata->windowlist;
        पूर्णाङ्क i;

        यदि (windowlist) {
            प्रति (i = 0; i < numwindows; ++i) {
                यदि (windowlist[i] && (windowlist[i]->गवाक्षः == गवाक्षः)) {
                    windowlist[i] = windowlist[numwindows - 1];
                    windowlist[numwindows - 1] = रिक्त;
                    videodata->numwindows--;
                    भङ्ग;
                }
            }
        }

        X11_Destroy_निवेशः_Context(दत्त);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
        X11_पदांशः_Resize_Sync(गवाक्षः);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
            X11_XDestroy_गवाक्षः(display, दत्त->xwindow);
            X11_XFlush(display);
        }
        SDL_free(दत्त);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
        // If the pointer barriers are active for this, deactivate it.
        यदि (videodata->सक्रिय_cursor_confined_गवाक्षः == गवाक्षः) {
            X11_DestroyPointerBarrier(_this, गवाक्षः);
        }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
    }
    गवाक्षः->आन्तरिकम् = रिक्त;
}

bool X11_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled)
{
    प्रत्यागम true; // just succeed, the real work is done elsewhere.
}

शून्य X11_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom XdndAware = दत्त->videodata->atoms.XdndAware;

    यदि (accept) {
        Atom xdnd_संस्करणम् = 5;
        X11_XChangeProperty(display, दत्त->xwindow, XdndAware, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)&xdnd_संस्करणम्, 1);
    } अन्यथा {
        X11_XDeleteProperty(display, दत्त->xwindow, XdndAware);
    }
}

bool X11_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    XWMHints *wmhints;

    wmhints = X11_XGetWMHints(display, दत्त->xwindow);
    यदि (!wmhints) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't get WM hints");
    }

    wmhints->flags &= ~XUrgencyHint;
    दत्त->flashing_गवाक्षः = false;
    दत्त->flash_cancel_time = 0;

    विकल्प (operation) {
    पक्ष SDL_FLASH_CANCEL:
        // Taken care of above
        भङ्ग;
    पक्ष SDL_FLASH_BRIEFLY:
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            दत्त->flashing_गवाक्षः = true;
            // On Ubuntu 21.04 this causes a dialog to pop up, so leave it up for a full second so users can see it
            दत्त->flash_cancel_time = SDL_GetTicks() + 1000;
        }
        भङ्ग;
    पक्ष SDL_FLASH_UNTIL_FOCUSED:
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
            wmhints->flags |= XUrgencyHint;
            दत्त->flashing_गवाक्षः = true;
        }
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }

    X11_XSetWMHints(display, दत्त->xwindow, wmhints);
    X11_XFree(wmhints);
    प्रत्यागम true;
}

bool SDL_X11_समुच्चयः_गवाक्षः_Title(Display *display, गवाक्षः_2 xwindow, वर्ण *title)
{
    Atom _NET_WM_NAME = X11_XInternAtom(display, "_NET_WM_NAME", False);
    XTextProperty titleprop;
    पूर्णाङ्क conv = X11_Xmb_Text_List_गन्तव्यम्_Text_Property(display, &title, 1, XTextStyle, &titleprop);
    स्थितिः_2 स्थितिः;

    यदि (X11_XSupportsLocale() != True) {
        प्रत्यागम SDL_समुच्चयः_Error("Current locale not supported by X server, cannot continue.");
    }

    यदि (conv == 0) {
        X11_XSetTextProperty(display, xwindow, &titleprop, XA_WM_NAME);
        X11_XFree(titleprop.मानम्);
        // we know this can't be a locale error as we checked X locale validity
    } अन्यथा यदि (conv < 0) {
        प्रत्यागम SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
    } अन्यथा { // conv > 0
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "%d characters were not convertible to the current locale!", conv);
        प्रत्यागम true;
    }

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    स्थितिः = X11_Xutf8_Text_List_गन्तव्यम्_Text_Property(display, &title, 1, XUTF8StringStyle, &titleprop);
    यदि (स्थितिः == Success) {
        X11_XSetTextProperty(display, xwindow, &titleprop, _NET_WM_NAME);
        X11_XFree(titleprop.मानम्);
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to convert title to UTF8! Bad encoding, or bad Xorg encoding? Window title: «%s»", title);
    }
#यदि_अन्तः

    X11_XFlush(display);
    प्रत्यागम true;
}

शून्य X11_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    Display *display = दत्त->videodata->display;
    गवाक्षः_2 मूलम् = मूलम्_गवाक्षः(display, displaydata->screen);
    XClient_सन्देशः_Event e;
    गवाक्षः_2 childReturn;
    पूर्णाङ्क wx, wy;

    SDL_zero(e);
    X11_XTranslateCoordinates(display, दत्त->xwindow, मूलम्, x, y, &wx, &wy, &childReturn);

    e.type = Client_सन्देशः;
    e.गवाक्षः = दत्त->xwindow;
    e.सन्देशः_type = X11_XInternAtom(display, "_GTK_SHOW_WINDOW_MENU", 0);
    e.दत्त.l[0] = 0;  // GTK device ID (unused)
    e.दत्त.l[1] = wx; // X coordinate relative to root
    e.दत्त.l[2] = wy; // Y coordinate relative to root
    e.format = 32;

    X11_XSendEvent(display, मूलम्, False, Substructure_Redirect_आवरणम् | Substructure_Notify_आवरणम्, (XEvent *)&e);
    X11_XFlush(display);
}

bool X11_Sync_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    // If the window is external and has only a pending resize or move event, use the special external sync path to avoid processing events.
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) &&
        (दत्त->pending_operation & ~(X11_PENDING_OP_RESIZE | X11_PENDING_OP_MOVE)) == X11_PENDING_OP_NONE) {
            X11_ExternalResizeMoveSync(गवाक्षः);
            प्रत्यागम true;
    }

    ध्रुव Uint64 current_time = SDL_GetTicksNS();
    Uint64 timeout = 0;

    // Allow time for any pending mode switches to complete.
    प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        यदि (_this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns &&
            current_time < _this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns) {
            timeout = SDL_max(_this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns - current_time, timeout);
        }
    }

    /* 100ms is fine for most cases, but, for some reason, maximizing
     * a window can take a very long time.
     */
    timeout += गवाक्षः->आन्तरिकम्->pending_operation & X11_PENDING_OP_MAXIMIZE ? SDL_MS_गन्तव्यम्_NS(1000) : SDL_MS_गन्तव्यम्_NS(100);

    प्रत्यागम X11_Sync_गवाक्षः_Timeout(_this, गवाक्षः, timeout);
}

bool X11_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable)
{
    यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        Display *display = दत्त->videodata->display;
        XWMHints *wmhints;

        wmhints = X11_XGetWMHints(display, दत्त->xwindow);
        यदि (!wmhints) {
            प्रत्यागम SDL_समुच्चयः_Error("Couldn't get WM hints");
        }

        wmhints->निवेशः = focusable ? True : False;
        wmhints->flags |= निवेशः_Hint;

        X11_XSetWMHints(display, दत्त->xwindow, wmhints);
        X11_XFree(wmhints);
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
            यदि (!focusable && (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
                SDL_गवाक्षः *new_focus;
                ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(गवाक्षः, &new_focus);
                X11_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
            } अन्यथा यदि (focusable) {
                यदि (SDL_ShouldFocusPopup(गवाक्षः)) {
                    X11_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
                }
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
