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

#اگر_غیر_تعریف_شدہ SDL_x11modes_h_
#تعریف_کرو SDL_x11modes_h_

#شامل "SDL_x11settings.h"

ساخت SDL_Display_ڈیٹا
{
    صحیح screen;
    Visual *visual;
    صحیح گہرائی_2;
    صحیح scanline_pad;
    صحیح x;
    صحیح y;

    Uint64 منوال_switch_deadline_ns;

    bool use_xrandr;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    حرف connector_name[16];
#اگر_ختم
};

ساخت SDL_Display_منوال_ڈیٹا
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_منوال;
#ورنہ
    صحیح غیر_مستعمل; // just so struct isn't empty.
#اگر_ختم
};

خارجی bool X11_InitModes(SDL_VideoDevice *_this);
خارجی bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool X11_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجی خالی X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
خارجی bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
خارجی SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
خارجی bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
خارجی bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

خارجی اعشاری X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
خارجی اعشاری X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
خارجی خالی X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
خارجی خالی X11_HandleXRandREvent(SDL_VideoDevice *_this, ثابت XEvent *xevent);
#اگر_ختم

#اگر_ختم // SDL_x11modes_h_
