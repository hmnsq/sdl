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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_x11modes_h_
#నిర్వచించు SDL_x11modes_h_

#అన్తర్భావ "SDL_x11settings.h"

నిర్మాణం SDL_Display_దత్తాంశం
{
    పూర్ణాంకం screen;
    Visual *visual;
    పూర్ణాంకం లోతు_2;
    పూర్ణాంకం scanline_pad;
    పూర్ణాంకం x;
    పూర్ణాంకం y;

    Uint64 బహుళకం_switch_deadline_ns;

    bool use_xrandr;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    అక్షరం connector_name[16];
#అయితే_ముగింపు
};

నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_బహుళకం;
#లేకపోతే
    పూర్ణాంకం వాడని; // just so struct isn't empty.
#అయితే_ముగింపు
};

బాహ్య bool X11_InitModes(SDL_VideoDevice *_this);
బాహ్య bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool X11_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
బాహ్య bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
బాహ్య SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
బాహ్య bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
బాహ్య bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

బాహ్య దశాంశం X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
బాహ్య దశాంశం X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
బాహ్య శూన్య X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
బాహ్య శూన్య X11_HandleXRandREvent(SDL_VideoDevice *_this, స్థిరరాశి XEvent *xevent);
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_x11modes_h_
