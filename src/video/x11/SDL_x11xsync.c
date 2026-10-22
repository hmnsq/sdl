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

#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11xsync.h"

સ્થિર bool xsync_initialized = false;

સ્થિર પૂર્ણાંક query_xsync_version(Display *display, પૂર્ણાંક major, પૂર્ણાંક minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    પાછા (major * 1000) + minor;
}

સ્થિર bool xsync_version_atleast(અચલ પૂર્ણાંક version, અચલ પૂર્ણાંક wantmajor, અચલ પૂર્ણાંક wantminor)
{
    પાછા version >= ((wantmajor * 1000) + wantminor);
}

શૂન્ય X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_VideoData *data =  _this->internal;

    પૂર્ણાંક version = 0;
    પૂર્ણાંક event, error;
    પૂર્ણાંક sync_opcode;

    જો (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(data->display, "SYNC", &sync_opcode, &event, &error)) {
        પાછા;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(data->display, 5, 0);
    જો (!xsync_version_atleast(version, 3, 0)) {
        પાછા; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(શૂન્ય)
{
    પાછા xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != ખાલી);
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    જો (!X11_XsyncIsInitialized()){
        પાછા SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_કિંમત){0, 0});
    data->resize_counter = counter;
    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;

    જો (counter == None){
        પાછા SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, data->xwindow, counter_prop, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned અક્ષર *)&counter_id, 1);

    પાછા true;
}

શૂન્ય X11_TermResizeSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = data->resize_counter;

    X11_XDeleteProperty(display, data->xwindow, counter_prop);
    જો (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

શૂન્ય X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_WindowData *data = window->internal;

    data->resize_id.lo = event->data.l[2];
    data->resize_id.hi = event->data.l[3];
    data->resize_in_progress = false;
}

શૂન્ય X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_WindowData *data = window->internal;

    જો (data->resize_id.lo || data->resize_id.hi) {
        data->resize_in_progress = true;
    }
}

શૂન્ય X11_HandlePresent(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSyncCounter counter = data->resize_counter;

    જો ((counter == None) || (!data->resize_in_progress)) {
        પાછા;
    }

    X11_XSyncSetCounter(display, counter, data->resize_id);

    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
