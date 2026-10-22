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

#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#شامل "SDL_x11video.h"
#شامل "SDL_x11xsync.h"

ساکن bool xsync_initialized = false;

ساکن صحیح query_xsync_نسخہ(Display *display, صحیح major, صحیح minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    واپس (major * 1000) + minor;
}

ساکن bool xsync_نسخہ_atleast(ثابت صحیح نسخہ, ثابت صحیح wantmajor, ثابت صحیح wantminor)
{
    واپس نسخہ >= ((wantmajor * 1000) + wantminor);
}

خالی X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا =  _this->اندرونی_2;

    صحیح نسخہ = 0;
    صحیح event, error;
    صحیح sync_opcode;

    اگر (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(ڈیٹا->display, "SYNC", &sync_opcode, &event, &error)) {
        واپس;
    }

    /* We need at least 5.0 for barriers. */
    نسخہ = query_xsync_نسخہ(ڈیٹا->display, 5, 0);
    اگر (!xsync_نسخہ_atleast(نسخہ, 3, 0)) {
        واپس; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(خالی)
{
    واپس xsync_initialized;
}

bool X11_InitResizeSync(SDL_کھڑکی *کھڑکی)
{
    SDL_assert(کھڑکی != تہی);
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom شمار_prop = ڈیٹا->videodata->atoms.NET_WM_SYNC_REQUEST_شمار;
    XSync_شمار شمار_2;
    CARD32 شمار_id;

    اگر (!X11_XsyncIsInitialized()){
        واپس SDL_Unsupported();
    }

    شمار_2 = X11_XSync_Create_شمار(display, (XSync_قدر){0, 0});
    ڈیٹا->resize_شمار = شمار_2;
    ڈیٹا->resize_id.lo = 0;
    ڈیٹا->resize_id.hi = 0;
    ڈیٹا->resize_اندر_پیش_رفت = false;

    اگر (شمار_2 == None){
        واپس SDL_Unsupported();
    }

    شمار_id = شمار_2;
    X11_XChangeProperty(display, ڈیٹا->xwindow, شمار_prop, XA_CARDINAL, 32,
                        Prop_منوال_Replace, (غیرعلامتی حرف *)&شمار_id, 1);

    واپس true;
}

خالی X11_رکن_Resize_Sync(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    Atom شمار_prop = ڈیٹا->videodata->atoms.NET_WM_SYNC_REQUEST_شمار;
    XSync_شمار شمار_2 = ڈیٹا->resize_شمار;

    X11_XDeleteProperty(display, ڈیٹا->xwindow, شمار_prop);
    اگر (شمار_2 != None) {
        X11_XSync_Destroy_شمار(display, شمار_2);
    }
}

خالی X11_HandleSyncRequest(SDL_کھڑکی *کھڑکی, XClient_پیغام_Event *event)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    ڈیٹا->resize_id.lo = event->ڈیٹا.l[2];
    ڈیٹا->resize_id.hi = event->ڈیٹا.l[3];
    ڈیٹا->resize_اندر_پیش_رفت = false;
}

خالی X11_HandleConfigure(SDL_کھڑکی *کھڑکی, XConfigureEvent *event)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا->resize_id.lo || ڈیٹا->resize_id.hi) {
        ڈیٹا->resize_اندر_پیش_رفت = true;
    }
}

خالی X11_HandlePresent(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    XSync_شمار شمار_2 = ڈیٹا->resize_شمار;

    اگر ((شمار_2 == None) || (!ڈیٹا->resize_اندر_پیش_رفت)) {
        واپس;
    }

    X11_XSync_سیٹ_شمار(display, شمار_2, ڈیٹا->resize_id);

    ڈیٹا->resize_id.lo = 0;
    ڈیٹا->resize_id.hi = 0;
    ڈیٹا->resize_اندر_پیش_رفت = false;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
