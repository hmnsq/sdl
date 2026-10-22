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

#जर defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xsync.h"

स्थिर bool xsync_initialized = false;

स्थिर पूर्णांक query_xsync_version(Display *display, पूर्णांक major, पूर्णांक minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    परत (major * 1000) + minor;
}

स्थिर bool xsync_version_atleast(स्थिरांक पूर्णांक version, स्थिरांक पूर्णांक wantmajor, स्थिरांक पूर्णांक wantminor)
{
    परत version >= ((wantmajor * 1000) + wantminor);
}

शून्य X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_VideoData *data =  _this->internal;

    पूर्णांक version = 0;
    पूर्णांक event, error;
    पूर्णांक sync_opcode;

    जर (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(data->display, "SYNC", &sync_opcode, &event, &error)) {
        परत;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(data->display, 5, 0);
    जर (!xsync_version_atleast(version, 3, 0)) {
        परत; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(शून्य)
{
    परत xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != रिक्त);
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    जर (!X11_XsyncIsInitialized()){
        परत SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_मूल्य){0, 0});
    data->resize_counter = counter;
    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;

    जर (counter == None){
        परत SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, data->xwindow, counter_prop, XA_CARDINAL, 32,
                        PropModeReplace, (अचिन्हित अक्षर *)&counter_id, 1);

    परत true;
}

शून्य X11_TermResizeSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = data->resize_counter;

    X11_XDeleteProperty(display, data->xwindow, counter_prop);
    जर (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

शून्य X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_WindowData *data = window->internal;

    data->resize_id.lo = event->data.l[2];
    data->resize_id.hi = event->data.l[3];
    data->resize_in_progress = false;
}

शून्य X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_WindowData *data = window->internal;

    जर (data->resize_id.lo || data->resize_id.hi) {
        data->resize_in_progress = true;
    }
}

शून्य X11_HandlePresent(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSyncCounter counter = data->resize_counter;

    जर ((counter == None) || (!data->resize_in_progress)) {
        परत;
    }

    X11_XSyncSetCounter(display, counter, data->resize_id);

    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
