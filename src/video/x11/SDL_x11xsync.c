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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"

ਸਥਿਰ bool xsync_initialized = false;

ਸਥਿਰ ਪੂਰਨ query_xsync_ਸੰਸਕਰਣ(Display *display, ਪੂਰਨ major, ਪੂਰਨ minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    ਵਾਪਸ (major * 1000) + minor;
}

ਸਥਿਰ bool xsync_ਸੰਸਕਰਣ_atleast(ਅਚਲ ਪੂਰਨ ਸੰਸਕਰਣ, ਅਚਲ ਪੂਰਨ wantmajor, ਅਚਲ ਪੂਰਨ wantminor)
{
    ਵਾਪਸ ਸੰਸਕਰਣ >= ((wantmajor * 1000) + wantminor);
}

ਖਾਲੀ X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ =  _this->ਅੰਦਰੂਨੀ;

    ਪੂਰਨ ਸੰਸਕਰਣ = 0;
    ਪੂਰਨ event, error;
    ਪੂਰਨ sync_opcode;

    ਜੇ (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(ਅੰਕੜੇ->display, "SYNC", &sync_opcode, &event, &error)) {
        ਵਾਪਸ;
    }

    /* We need at least 5.0 for barriers. */
    ਸੰਸਕਰਣ = query_xsync_ਸੰਸਕਰਣ(ਅੰਕੜੇ->display, 5, 0);
    ਜੇ (!xsync_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 3, 0)) {
        ਵਾਪਸ; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(ਖਾਲੀ)
{
    ਵਾਪਸ xsync_initialized;
}

bool X11_InitResizeSync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_assert(ਖਿੜਕੀ != ਨਿਰਾ);
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom counter_prop = ਅੰਕੜੇ->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    ਜੇ (!X11_XsyncIsInitialized()){
        ਵਾਪਸ SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_ਮੁੱਲ){0, 0});
    ਅੰਕੜੇ->resize_counter = counter;
    ਅੰਕੜੇ->resize_id.lo = 0;
    ਅੰਕੜੇ->resize_id.hi = 0;
    ਅੰਕੜੇ->resize_ਵਿੱਚ_ਤਰੱਕੀ = false;

    ਜੇ (counter == None){
        ਵਾਪਸ SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, ਅੰਕੜੇ->xwindow, counter_prop, XA_CARDINAL, 32,
                        Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&counter_id, 1);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_ਪਦ_Resize_Sync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    Atom counter_prop = ਅੰਕੜੇ->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = ਅੰਕੜੇ->resize_counter;

    X11_XDeleteProperty(display, ਅੰਕੜੇ->xwindow, counter_prop);
    ਜੇ (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

ਖਾਲੀ X11_HandleSyncRequest(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, XClient_ਸੁਨੇਹਾ_Event *event)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->resize_id.lo = event->ਅੰਕੜੇ.l[2];
    ਅੰਕੜੇ->resize_id.hi = event->ਅੰਕੜੇ.l[3];
    ਅੰਕੜੇ->resize_ਵਿੱਚ_ਤਰੱਕੀ = false;
}

ਖਾਲੀ X11_HandleConfigure(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, XConfigureEvent *event)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->resize_id.lo || ਅੰਕੜੇ->resize_id.hi) {
        ਅੰਕੜੇ->resize_ਵਿੱਚ_ਤਰੱਕੀ = true;
    }
}

ਖਾਲੀ X11_HandlePresent(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    XSyncCounter counter = ਅੰਕੜੇ->resize_counter;

    ਜੇ ((counter == None) || (!ਅੰਕੜੇ->resize_ਵਿੱਚ_ਤਰੱਕੀ)) {
        ਵਾਪਸ;
    }

    X11_XSync_ਸੈੱਟ_Counter(display, counter, ਅੰਕੜੇ->resize_id);

    ਅੰਕੜੇ->resize_id.lo = 0;
    ਅੰਕੜੇ->resize_id.hi = 0;
    ਅੰਕੜੇ->resize_ਵਿੱਚ_ਤਰੱਕੀ = false;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
