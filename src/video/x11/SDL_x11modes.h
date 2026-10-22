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

#اگر_تعریف_نشده SDL_x11modes_h_
#تعریف_کن SDL_x11modes_h_

#ضمن "SDL_x11settings.h"

بنية SDL_Display_داده
{
    صحيح screen;
    Visual *visual;
    صحيح عمق_2;
    صحيح scanline_pad;
    صحيح x;
    صحيح y;

    Uint64 نما_switch_deadline_ns;

    bool use_xrandr;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    حرف connector_name[16];
#پایان_اگر
};

بنية SDL_Display_نما_داده
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_نما;
#وإلا
    صحيح استفادهنشده; // just so struct isn't empty.
#پایان_اگر
};

خارجي bool X11_InitModes(SDL_VideoDevice *_this);
خارجي bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool X11_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
خارجي فراغ X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
خارجي bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
خارجي SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
خارجي bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
خارجي bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

خارجي عائم X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
خارجي عائم X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
خارجي فراغ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
خارجي فراغ X11_HandleXRandREvent(SDL_VideoDevice *_this, ثابت XEvent *xevent);
#پایان_اگر

#پایان_اگر // SDL_x11modes_h_
