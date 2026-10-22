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

#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xsync.h"

ساكن bool xsync_initialized = false;

ساكن صحيح query_xsync_نسخه(Display *display, صحيح major, صحيح minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xsync_نسخه_atleast(ثابت صحيح نسخه, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع نسخه >= ((wantmajor * 1000) + wantminor);
}

فراغ X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده =  _this->داخلی;

    صحيح نسخه = 0;
    صحيح event, error;
    صحيح sync_opcode;

    إذا (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(داده->display, "SYNC", &sync_opcode, &event, &error)) {
        أرجع;
    }

    /* We need at least 5.0 for barriers. */
    نسخه = query_xsync_نسخه(داده->display, 5, 0);
    إذا (!xsync_نسخه_atleast(نسخه, 3, 0)) {
        أرجع; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(فراغ)
{
    أرجع xsync_initialized;
}

bool X11_InitResizeSync(SDL_پنجره *پنجره)
{
    SDL_assert(پنجره != عدم);
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    Atom counter_prop = داده->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    إذا (!X11_XsyncIsInitialized()){
        أرجع SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_مقدار){0, 0});
    داده->resize_counter = counter;
    داده->resize_id.lo = 0;
    داده->resize_id.hi = 0;
    داده->resize_درون_پیشرفت = false;

    إذا (counter == None){
        أرجع SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, داده->xwindow, counter_prop, XA_CARDINAL, 32,
                        Prop_نما_Replace, (بیعلامت حرف *)&counter_id, 1);

    أرجع true;
}

فراغ X11_جمله_Resize_Sync(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    Atom counter_prop = داده->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = داده->resize_counter;

    X11_XDeleteProperty(display, داده->xwindow, counter_prop);
    إذا (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

فراغ X11_HandleSyncRequest(SDL_پنجره *پنجره, XClient_پیام_Event *event)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    داده->resize_id.lo = event->داده.l[2];
    داده->resize_id.hi = event->داده.l[3];
    داده->resize_درون_پیشرفت = false;
}

فراغ X11_HandleConfigure(SDL_پنجره *پنجره, XConfigureEvent *event)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده->resize_id.lo || داده->resize_id.hi) {
        داده->resize_درون_پیشرفت = true;
    }
}

فراغ X11_HandlePresent(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    XSyncCounter counter = داده->resize_counter;

    إذا ((counter == None) || (!داده->resize_درون_پیشرفت)) {
        أرجع;
    }

    X11_XSync_مجموعه_Counter(display, counter, داده->resize_id);

    داده->resize_id.lo = 0;
    داده->resize_id.hi = 0;
    داده->resize_درون_پیشرفت = false;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
