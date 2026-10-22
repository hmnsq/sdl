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

#যদি defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11xsync.h"

স্থির bool xsync_initialized = false;

স্থির পূর্ণাঙ্ক query_xsync_version(Display *display, পূর্ণাঙ্ক major, পূর্ণাঙ্ক minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    প্রত্যাগম (major * 1000) + minor;
}

স্থির bool xsync_version_atleast(ধ্রুব পূর্ণাঙ্ক version, ধ্রুব পূর্ণাঙ্ক wantmajor, ধ্রুব পূর্ণাঙ্ক wantminor)
{
    প্রত্যাগম version >= ((wantmajor * 1000) + wantminor);
}

শূন্য X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_VideoData *data =  _this->internal;

    পূর্ণাঙ্ক version = 0;
    পূর্ণাঙ্ক event, error;
    পূর্ণাঙ্ক sync_opcode;

    যদি (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(data->display, "SYNC", &sync_opcode, &event, &error)) {
        প্রত্যাগম;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(data->display, 5, 0);
    যদি (!xsync_version_atleast(version, 3, 0)) {
        প্রত্যাগম; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(শূন্য)
{
    প্রত্যাগম xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != রিক্ত);
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    যদি (!X11_XsyncIsInitialized()){
        প্রত্যাগম SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_মান){0, 0});
    data->resize_counter = counter;
    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;

    যদি (counter == None){
        প্রত্যাগম SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, data->xwindow, counter_prop, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned বর্ণ *)&counter_id, 1);

    প্রত্যাগম true;
}

শূন্য X11_TermResizeSync(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    Atom counter_prop = data->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = data->resize_counter;

    X11_XDeleteProperty(display, data->xwindow, counter_prop);
    যদি (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

শূন্য X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_WindowData *data = window->internal;

    data->resize_id.lo = event->data.l[2];
    data->resize_id.hi = event->data.l[3];
    data->resize_in_progress = false;
}

শূন্য X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_WindowData *data = window->internal;

    যদি (data->resize_id.lo || data->resize_id.hi) {
        data->resize_in_progress = true;
    }
}

শূন্য X11_HandlePresent(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XSyncCounter counter = data->resize_counter;

    যদি ((counter == None) || (!data->resize_in_progress)) {
        প্রত্যাগম;
    }

    X11_XSyncSetCounter(display, counter, data->resize_id);

    data->resize_id.lo = 0;
    data->resize_id.hi = 0;
    data->resize_in_progress = false;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
