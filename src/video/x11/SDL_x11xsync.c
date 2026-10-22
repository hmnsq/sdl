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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xsync.h"

స్థిర bool xsync_initialized = false;

స్థిర పూర్ణాంకం query_xsync_సంస్కరణ(Display *display, పూర్ణాంకం major, పూర్ణాంకం minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    తిరిగి (major * 1000) + minor;
}

స్థిర bool xsync_సంస్కరణ_atleast(స్థిరరాశి పూర్ణాంకం సంస్కరణ, స్థిరరాశి పూర్ణాంకం wantmajor, స్థిరరాశి పూర్ణాంకం wantminor)
{
    తిరిగి సంస్కరణ >= ((wantmajor * 1000) + wantminor);
}

శూన్య X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం =  _this->అంతర్గత;

    పూర్ణాంకం సంస్కరణ = 0;
    పూర్ణాంకం event, error;
    పూర్ణాంకం sync_opcode;

    ఒకవేళ (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(దత్తాంశం->display, "SYNC", &sync_opcode, &event, &error)) {
        తిరిగి;
    }

    /* We need at least 5.0 for barriers. */
    సంస్కరణ = query_xsync_సంస్కరణ(దత్తాంశం->display, 5, 0);
    ఒకవేళ (!xsync_సంస్కరణ_atleast(సంస్కరణ, 3, 0)) {
        తిరిగి; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(శూన్య)
{
    తిరిగి xsync_initialized;
}

bool X11_InitResizeSync(SDL_కిటికీ *కిటికీ)
{
    SDL_assert(కిటికీ != ఖాళీ);
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom counter_prop = దత్తాంశం->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    ఒకవేళ (!X11_XsyncIsInitialized()){
        తిరిగి SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_విలువ){0, 0});
    దత్తాంశం->resize_counter = counter;
    దత్తాంశం->resize_id.lo = 0;
    దత్తాంశం->resize_id.hi = 0;
    దత్తాంశం->resize_లోపల_పురోగతి = false;

    ఒకవేళ (counter == None){
        తిరిగి SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, దత్తాంశం->xwindow, counter_prop, XA_CARDINAL, 32,
                        Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)&counter_id, 1);

    తిరిగి true;
}

శూన్య X11_పదం_Resize_Sync(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    Atom counter_prop = దత్తాంశం->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = దత్తాంశం->resize_counter;

    X11_XDeleteProperty(display, దత్తాంశం->xwindow, counter_prop);
    ఒకవేళ (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

శూన్య X11_HandleSyncRequest(SDL_కిటికీ *కిటికీ, XClient_సందేశం_Event *event)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    దత్తాంశం->resize_id.lo = event->దత్తాంశం.l[2];
    దత్తాంశం->resize_id.hi = event->దత్తాంశం.l[3];
    దత్తాంశం->resize_లోపల_పురోగతి = false;
}

శూన్య X11_HandleConfigure(SDL_కిటికీ *కిటికీ, XConfigureEvent *event)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం->resize_id.lo || దత్తాంశం->resize_id.hi) {
        దత్తాంశం->resize_లోపల_పురోగతి = true;
    }
}

శూన్య X11_HandlePresent(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    XSyncCounter counter = దత్తాంశం->resize_counter;

    ఒకవేళ ((counter == None) || (!దత్తాంశం->resize_లోపల_పురోగతి)) {
        తిరిగి;
    }

    X11_XSync_సమితి_Counter(display, counter, దత్తాంశం->resize_id);

    దత్తాంశం->resize_id.lo = 0;
    దత్తాంశం->resize_id.hi = 0;
    దత్తాంశం->resize_లోపల_పురోగతి = false;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
