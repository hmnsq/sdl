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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_x11modes_h_
#define SDL_x11modes_h_

#அந்தர்பாவ "SDL_x11settings.h"

கட்டமைப்பு SDL_DisplayData
{
    முழு screen;
    Visual *visual;
    முழு depth;
    முழு scanline_pad;
    முழு x;
    முழு y;

    Uint64 mode_switch_deadline_ns;

    bool use_xrandr;

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    எழுத்து connector_name[16];
#endif
};

கட்டமைப்பு SDL_DisplayModeData
{
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_mode;
#இல்லையெனில்
    முழு unused; // just so struct isn't empty.
#endif
};

வெளி bool X11_InitModes(SDL_VideoDevice *_this);
வெளி bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
வெளி bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
வெளி வெறுமை X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
வெளி bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
வெளி SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
வெளி bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
வெளி bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

வெளி தசம X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
வெளி தசம X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
வெளி வெறுமை X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
வெளி வெறுமை X11_HandleXRandREvent(SDL_VideoDevice *_this, மாறிலி XEvent *xevent);
#endif

#endif // SDL_x11modes_h_
