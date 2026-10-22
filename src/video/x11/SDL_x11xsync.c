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

#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_DRIVER_X11_XSYNC)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xsync.h"

स्थिर bool xsync_initialized = false;

स्थिर पूर्णाङ्क query_xsync_संस्करणम्(Display *display, पूर्णाङ्क major, पूर्णाङ्क minor)
{
    /* We don't care if this fails, so long as it sets major/minor on it's way out the door. */
    X11_XSyncInitialize(display, &major, &minor);
    प्रत्यागम (major * 1000) + minor;
}

स्थिर bool xsync_संस्करणम्_atleast(ध्रुव पूर्णाङ्क संस्करणम्, ध्रुव पूर्णाङ्क wantmajor, ध्रुव पूर्णाङ्क wantminor)
{
    प्रत्यागम संस्करणम् >= ((wantmajor * 1000) + wantminor);
}

शून्य X11_InitXsync(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त =  _this->आन्तरिकम्;

    पूर्णाङ्क संस्करणम् = 0;
    पूर्णाङ्क event, error;
    पूर्णाङ्क sync_opcode;

    यदि (!SDL_X11_HAVE_XSYNC ||
        !X11_XQueryExtension(दत्त->display, "SYNC", &sync_opcode, &event, &error)) {
        प्रत्यागम;
    }

    /* We need at least 5.0 for barriers. */
    संस्करणम् = query_xsync_संस्करणम्(दत्त->display, 5, 0);
    यदि (!xsync_संस्करणम्_atleast(संस्करणम्, 3, 0)) {
        प्रत्यागम; /* X server does not support the version we want at all. */
    }

    xsync_initialized = true;
}

bool X11_XsyncIsInitialized(शून्य)
{
    प्रत्यागम xsync_initialized;
}

bool X11_InitResizeSync(SDL_गवाक्षः *गवाक्षः)
{
    SDL_assert(गवाक्षः != रिक्त);
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom गणक_prop = दत्त->videodata->atoms.NET_WM_SYNC_REQUEST_गणक;
    XSync_गणक गणक;
    CARD32 गणक_id;

    यदि (!X11_XsyncIsInitialized()){
        प्रत्यागम SDL_Unsupported();
    }

    गणक = X11_XSync_Create_गणक(display, (XSync_मानम्){0, 0});
    दत्त->resize_गणक = गणक;
    दत्त->resize_id.lo = 0;
    दत्त->resize_id.hi = 0;
    दत्त->resize_अन्तर्_प्रगतिः = false;

    यदि (गणक == None){
        प्रत्यागम SDL_Unsupported();
    }

    गणक_id = गणक;
    X11_XChangeProperty(display, दत्त->xwindow, गणक_prop, XA_CARDINAL, 32,
                        Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)&गणक_id, 1);

    प्रत्यागम true;
}

शून्य X11_पदांशः_Resize_Sync(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    Atom गणक_prop = दत्त->videodata->atoms.NET_WM_SYNC_REQUEST_गणक;
    XSync_गणक गणक = दत्त->resize_गणक;

    X11_XDeleteProperty(display, दत्त->xwindow, गणक_prop);
    यदि (गणक != None) {
        X11_XSync_Destroy_गणक(display, गणक);
    }
}

शून्य X11_HandleSyncRequest(SDL_गवाक्षः *गवाक्षः, XClient_सन्देशः_Event *event)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    दत्त->resize_id.lo = event->दत्त.l[2];
    दत्त->resize_id.hi = event->दत्त.l[3];
    दत्त->resize_अन्तर्_प्रगतिः = false;
}

शून्य X11_HandleConfigure(SDL_गवाक्षः *गवाक्षः, XConfigureEvent *event)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त->resize_id.lo || दत्त->resize_id.hi) {
        दत्त->resize_अन्तर्_प्रगतिः = true;
    }
}

शून्य X11_HandlePresent(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    XSync_गणक गणक = दत्त->resize_गणक;

    यदि ((गणक == None) || (!दत्त->resize_अन्तर्_प्रगतिः)) {
        प्रत्यागम;
    }

    X11_XSync_समुच्चयः_गणक(display, गणक, दत्त->resize_id);

    दत्त->resize_id.lo = 0;
    दत्त->resize_id.hi = 0;
    दत्त->resize_अन्तर्_प्रगतिः = false;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_DRIVER_X11_XSYNC
