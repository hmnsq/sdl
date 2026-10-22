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

#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11xsync.h"

अटल bool xsync_initialized = false;

अटल पूर्णांक query_xsync_version(Display *display, पूर्णांक major, पूर्णांक minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    वापस (major * 1000) + minor;
}

अटल bool xsync_version_atleast(स्थिर पूर्णांक version, स्थिर पूर्णांक wantmajor, स्थिर पूर्णांक wantminor)
{
    वापस version >= ((wantmajor * 1000) + wantminor);
}

व्योम X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य =  _this->internal;

    पूर्णांक version = 0;
    पूर्णांक event, error;
    पूर्णांक sync_opcode;

    अगर (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(तथ्य->display, "SYNC", &sync_opcode, &event, &error)) {
        वापस;
    }

    /* We need at least 5.0 for barriers. */
    version = query_xsync_version(तथ्य->display, 5, 0);
    अगर (!xsync_version_atleast(version, 3, 0)) {
        वापस; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(व्योम)
{
    वापस xsync_initialized;
}

bool X11_InitResizeSync(SDL_Window *window)
{
    SDL_assert(window != शून्य);
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    Atom गणक_prop = तथ्य->videodata->atoms.NET_WM_SYNC_REQUEST_गणक;
    XSync_गणक गणक;
    CARD32 गणक_id;

    अगर (!X11_XsyncIsInitialized()){
        वापस SDL_Unsupported();
    }

    गणक = X11_XSync_Create_गणक(display, (XSync_मूल्य){0, 0});
    तथ्य->resize_गणक = गणक;
    तथ्य->resize_id.lo = 0;
    तथ्य->resize_id.hi = 0;
    तथ्य->resize_in_progress = false;

    अगर (गणक == None){
        वापस SDL_Unsupported();
    }

    गणक_id = गणक;
    X11_XChangeProperty(display, तथ्य->xwindow, गणक_prop, XA_CARDINAL, 32,
                        PropModeReplace, (अचिन्हित अक्षर *)&गणक_id, 1);

    वापस true;
}

व्योम X11_TermResizeSync(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    Atom गणक_prop = तथ्य->videodata->atoms.NET_WM_SYNC_REQUEST_गणक;
    XSync_गणक गणक = तथ्य->resize_गणक;

    X11_XDeleteProperty(display, तथ्य->xwindow, गणक_prop);
    अगर (गणक != None) {
        X11_XSync_Destroy_गणक(display, गणक);
    }
}

व्योम X11_HandleSyncRequest(SDL_Window *window, XClientMessageEvent *event)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    तथ्य->resize_id.lo = event->तथ्य.l[2];
    तथ्य->resize_id.hi = event->तथ्य.l[3];
    तथ्य->resize_in_progress = false;
}

व्योम X11_HandleConfigure(SDL_Window *window, XConfigureEvent *event)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य->resize_id.lo || तथ्य->resize_id.hi) {
        तथ्य->resize_in_progress = true;
    }
}

व्योम X11_HandlePresent(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    XSync_गणक गणक = तथ्य->resize_गणक;

    अगर ((गणक == None) || (!तथ्य->resize_in_progress)) {
        वापस;
    }

    X11_XSync_Set_गणक(display, गणक, तथ्य->resize_id);

    तथ्य->resize_id.lo = 0;
    तथ्य->resize_id.hi = 0;
    तथ्य->resize_in_progress = false;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
