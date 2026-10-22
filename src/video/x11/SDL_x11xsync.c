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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

ಸ್ಥಿರ bool xsync_initialized = false;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ query_xsync_ಆವೃತ್ತಿ(Display *display, ಪೂರ್ಣಾಂಕ major, ಪೂರ್ಣಾಂಕ minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    ಹಿಂತಿರುಗಿ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xsync_ಆವೃತ್ತಿ_atleast(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantmajor, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantminor)
{
    ಹಿಂತಿರುಗಿ ಆವೃತ್ತಿ >= ((wantmajor * 1000) + wantminor);
}

ಶೂನ್ಯ X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ =  _this->ಆಂತರಿಕ;

    ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ = 0;
    ಪೂರ್ಣಾಂಕ event, error;
    ಪೂರ್ಣಾಂಕ sync_opcode;

    ಆದರೆ (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(ದತ್ತಾಂಶ->display, "SYNC", &sync_opcode, &event, &error)) {
        ಹಿಂತಿರುಗಿ;
    }

    /* We need at least 5.0 for barriers. */
    ಆವೃತ್ತಿ = query_xsync_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->display, 5, 0);
    ಆದರೆ (!xsync_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 3, 0)) {
        ಹಿಂತಿರುಗಿ; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ xsync_initialized;
}

bool X11_InitResizeSync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_assert(ಕಿಟಕಿ != ಖಾಲಿ);
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom counter_prop = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    ಆದರೆ (!X11_XsyncIsInitialized()){
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_ಮೌಲ್ಯ){0, 0});
    ದತ್ತಾಂಶ->resize_counter = counter;
    ದತ್ತಾಂಶ->resize_id.lo = 0;
    ದತ್ತಾಂಶ->resize_id.hi = 0;
    ದತ್ತಾಂಶ->resize_ಒಳ_ಪ್ರಗತಿ = false;

    ಆದರೆ (counter == None){
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, ದತ್ತಾಂಶ->xwindow, counter_prop, XA_CARDINAL, 32,
                        Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&counter_id, 1);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_ಪದ_Resize_Sync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    Atom counter_prop = ದತ್ತಾಂಶ->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = ದತ್ತಾಂಶ->resize_counter;

    X11_XDeleteProperty(display, ದತ್ತಾಂಶ->xwindow, counter_prop);
    ಆದರೆ (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

ಶೂನ್ಯ X11_HandleSyncRequest(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, XClient_ಸಂದೇಶ_Event *event)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->resize_id.lo = event->ದತ್ತಾಂಶ.l[2];
    ದತ್ತಾಂಶ->resize_id.hi = event->ದತ್ತಾಂಶ.l[3];
    ದತ್ತಾಂಶ->resize_ಒಳ_ಪ್ರಗತಿ = false;
}

ಶೂನ್ಯ X11_HandleConfigure(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, XConfigureEvent *event)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->resize_id.lo || ದತ್ತಾಂಶ->resize_id.hi) {
        ದತ್ತಾಂಶ->resize_ಒಳ_ಪ್ರಗತಿ = true;
    }
}

ಶೂನ್ಯ X11_HandlePresent(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XSyncCounter counter = ದತ್ತಾಂಶ->resize_counter;

    ಆದರೆ ((counter == None) || (!ದತ್ತಾಂಶ->resize_ಒಳ_ಪ್ರಗತಿ)) {
        ಹಿಂತಿರುಗಿ;
    }

    X11_XSync_ಗಣ_Counter(display, counter, ದತ್ತಾಂಶ->resize_id);

    ದತ್ತಾಂಶ->resize_id.lo = 0;
    ದತ್ತಾಂಶ->resize_id.hi = 0;
    ದತ್ತಾಂಶ->resize_ಒಳ_ಪ್ರಗತಿ = false;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
