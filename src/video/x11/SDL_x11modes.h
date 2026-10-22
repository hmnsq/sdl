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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_x11modes_h_
#define SDL_x11modes_h_

#અન્તર્ભાવ "SDL_x11settings.h"

સંરચના SDL_DisplayData
{
    પૂર્ણાંક screen;
    Visual *visual;
    પૂર્ણાંક depth;
    પૂર્ણાંક scanline_pad;
    પૂર્ણાંક x;
    પૂર્ણાંક y;

    Uint64 mode_switch_deadline_ns;

    bool use_xrandr;

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    અક્ષર connector_name[16];
#endif
};

સંરચના SDL_DisplayModeData
{
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_mode;
#નહીંતર
    પૂર્ણાંક unused; // just so struct isn't empty.
#endif
};

બાહ્ય bool X11_InitModes(SDL_VideoDevice *_this);
બાહ્ય bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
બાહ્ય bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
બાહ્ય શૂન્ય X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
બાહ્ય bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
બાહ્ય SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
બાહ્ય bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
બાહ્ય bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

બાહ્ય દશાંશ X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
બાહ્ય દશાંશ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
બાહ્ય શૂન્ય X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
બાહ્ય શૂન્ય X11_HandleXRandREvent(SDL_VideoDevice *_this, અચલ XEvent *xevent);
#endif

#endif // SDL_x11modes_h_
