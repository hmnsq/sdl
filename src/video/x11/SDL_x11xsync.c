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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

ಸ್ಥಿರ bool xsync_initialized = false;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ query_xsync_version(Display *display, ಪೂರ್ಣಾಙ್ಕ major, ಪೂರ್ಣಾಙ್ಕ minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    ಪ್ರತ್ಯಾಗಮ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xsync_version_atleast(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ version, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantmajor, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantminor)
{
    ಪ್ರತ್ಯಾಗಮ version >= ((wantmajor * 1000) + wantminor);
}

ಶೂನ್ಯ X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_VideoData *data =  _this->internal;

    ಪೂರ್ಣಾಙ್ಕ version = 0;
    ಪೂರ್ಣಾಙ್ಕ event, error;
    ಪೂರ್ಣಾಙ್ಕ sync_opcode;

    ಯದಿ (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(data->display, "SYNC", &sync_opcode, &event, &error)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(data->display, 5, 0);
    ಯದಿ (!xsync_version_atleast(version, 3, 0)) {
        ಪ್ರತ್ಯಾಗಮ; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != ರಿಕ್ತ);
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    ಯದಿ (!X11_XsyncIsInitialized()){
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_ಮೌಲ್ಯ){0, 0});
    data->resize_counter = counter;
    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;

    ಯದಿ (counter == None){
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, data->xwindow, counter_prop, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned ವರ್ಣ *)&counter_id, 1);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ X11_TermResizeSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = data->resize_counter;

    X11_XDeleteProperty(display, data->xwindow, counter_prop);
    ಯದಿ (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

ಶೂನ್ಯ X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_WindowData *data = window->internal;

    data->resize_id.lo = event->data.l[2];
    data->resize_id.hi = event->data.l[3];
    data->resize_in_progress = false;
}

ಶೂನ್ಯ X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (data->resize_id.lo || data->resize_id.hi) {
        data->resize_in_progress = true;
    }
}

ಶೂನ್ಯ X11_HandlePresent(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSyncCounter counter = data->resize_counter;

    ಯದಿ ((counter == None) || (!data->resize_in_progress)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    X11_XSyncSetCounter(display, counter, data->resize_id);

    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
