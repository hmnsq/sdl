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

স্থির পূর্ণসংখ্যা query_xsync_version(Display *display, পূর্ণসংখ্যা major, পূর্ণসংখ্যা minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    ফেরত (major * 1000) + minor;
}

স্থির bool xsync_version_atleast(ধ্রুবক পূর্ণসংখ্যা version, ধ্রুবক পূর্ণসংখ্যা wantmajor, ধ্রুবক পূর্ণসংখ্যা wantminor)
{
    ফেরত version >= ((wantmajor * 1000) + wantminor);
}

শূন্য X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য =  _this->internal;

    পূর্ণসংখ্যা version = 0;
    পূর্ণসংখ্যা event, error;
    পূর্ণসংখ্যা sync_opcode;

    যদি (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(তথ্য->display, "SYNC", &sync_opcode, &event, &error)) {
        ফেরত;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(তথ্য->display, 5, 0);
    যদি (!xsync_version_atleast(version, 3, 0)) {
        ফেরত; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(শূন্য)
{
    ফেরত xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != ফাঁকা);
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    Atom গণক_prop = তথ্য->videodata->atoms.NET_WM_SYNC_REQUEST_গণক;
    XSync_গণক গণক;
    CARD32 গণক_id;

    যদি (!X11_XsyncIsInitialized()){
        ফেরত SDL_Unsupported();
    }

    গণক = X11_XSync_Create_গণক(display, (XSync_মান){0, 0});
    তথ্য->resize_গণক = গণক;
    তথ্য->resize_id.lo = 0;
    তথ্য->resize_id.hi = 0;
    তথ্য->resize_in_progress = false;

    যদি (গণক == None){
        ফেরত SDL_Unsupported();
    }

    গণক_id = গণক;
    X11_XChangeProperty(display, তথ্য->xwindow, গণক_prop, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned অক্ষর *)&গণক_id, 1);

    ফেরত true;
}

শূন্য X11_TermResizeSync(SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    Atom গণক_prop = তথ্য->videodata->atoms.NET_WM_SYNC_REQUEST_গণক;
    XSync_গণক গণক = তথ্য->resize_গণক;

    X11_XDeleteProperty(display, তথ্য->xwindow, গণক_prop);
    যদি (গণক != None) {
        X11_XSync_Destroy_গণক(display, গণক);
    }
}

শূন্য X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    তথ্য->resize_id.lo = event->তথ্য.l[2];
    তথ্য->resize_id.hi = event->তথ্য.l[3];
    তথ্য->resize_in_progress = false;
}

শূন্য X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (তথ্য->resize_id.lo || তথ্য->resize_id.hi) {
        তথ্য->resize_in_progress = true;
    }
}

শূন্য X11_HandlePresent(SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    XSync_গণক গণক = তথ্য->resize_গণক;

    যদি ((গণক == None) || (!তথ্য->resize_in_progress)) {
        ফেরত;
    }

    X11_XSync_Set_গণক(display, গণক, তথ্য->resize_id);

    তথ্য->resize_id.lo = 0;
    তথ্য->resize_id.hi = 0;
    তথ্য->resize_in_progress = false;
}

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
