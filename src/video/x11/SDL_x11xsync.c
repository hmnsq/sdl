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

ساكن صحيح query_xsync_نسخہ(Display *display, صحيح major, صحيح minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xsync_نسخہ_atleast(ثابت صحيح نسخہ, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع نسخہ >= ((wantmajor * 1000) + wantminor);
}

فراغ X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے =  _this->اندرونی;

    صحيح نسخہ = 0;
    صحيح event, error;
    صحيح sync_opcode;

    إذا (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(انکڑے->display, "SYNC", &sync_opcode, &event, &error)) {
        أرجع;
    }

    /* We need at least 5.0 for barriers. */
    نسخہ = query_xsync_نسخہ(انکڑے->display, 5, 0);
    إذا (!xsync_نسخہ_atleast(نسخہ, 3, 0)) {
        أرجع; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(فراغ)
{
    أرجع xsync_initialized;
}

bool X11_InitResizeSync(SDL_کھڑکی *کھڑکی)
{
    SDL_assert(کھڑکی != عدم);
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom counter_prop = انکڑے->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter;
    CARD32 counter_id;

    إذا (!X11_XsyncIsInitialized()){
        أرجع SDL_Unsupported();
    }

    counter = X11_XSyncCreateCounter(display, (XSync_قدر){0, 0});
    انکڑے->resize_counter = counter;
    انکڑے->resize_id.lo = 0;
    انکڑے->resize_id.hi = 0;
    انکڑے->resize_وچ_ترقی = false;

    إذا (counter == None){
        أرجع SDL_Unsupported();
    }

    counter_id = counter;
    X11_XChangeProperty(display, انکڑے->xwindow, counter_prop, XA_CARDINAL, 32,
                        Prop_منوال_Replace, (بنانشانی حرف *)&counter_id, 1);

    أرجع true;
}

فراغ X11_رکن_Resize_Sync(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    Atom counter_prop = انکڑے->videodata->atoms._NET_WM_SYNC_REQUEST_COUNTER;
    XSyncCounter counter = انکڑے->resize_counter;

    X11_XDeleteProperty(display, انکڑے->xwindow, counter_prop);
    إذا (counter != None) {
        X11_XSyncDestroyCounter(display, counter);
    }
}

فراغ X11_HandleSyncRequest(SDL_کھڑکی *کھڑکی, XClient_سنیہا_Event *event)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    انکڑے->resize_id.lo = event->انکڑے.l[2];
    انکڑے->resize_id.hi = event->انکڑے.l[3];
    انکڑے->resize_وچ_ترقی = false;
}

فراغ X11_HandleConfigure(SDL_کھڑکی *کھڑکی, XConfigureEvent *event)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے->resize_id.lo || انکڑے->resize_id.hi) {
        انکڑے->resize_وچ_ترقی = true;
    }
}

فراغ X11_HandlePresent(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    XSyncCounter counter = انکڑے->resize_counter;

    إذا ((counter == None) || (!انکڑے->resize_وچ_ترقی)) {
        أرجع;
    }

    X11_XSync_سیٹ_Counter(display, counter, انکڑے->resize_id);

    انکڑے->resize_id.lo = 0;
    انکڑے->resize_id.hi = 0;
    انکڑے->resize_وچ_ترقی = false;
}

#جے_انت // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
