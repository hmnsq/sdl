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

#यदि_अपरिभाषितम् SDL_x11modes_h_
#परिभाषय SDL_x11modes_h_

#अन्तर्भाव "SDL_x11settings.h"

संरचना SDL_Display_दत्त
{
    पूर्णाङ्क screen;
    Visual *visual;
    पूर्णाङ्क गभीरता_2;
    पूर्णाङ्क scanline_pad;
    पूर्णाङ्क x;
    पूर्णाङ्क y;

    Uint64 बहुलकम्_switch_deadline_ns;

    bool use_xrandr;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    वर्ण connector_name[16];
#यदि_अन्तः
};

संरचना SDL_Display_बहुलकम्_दत्त
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_बहुलकम्;
#अन्यथा
    पूर्णाङ्क अप्रयुक्तम्; // just so struct isn't empty.
#यदि_अन्तः
};

बाह्य bool X11_InitModes(SDL_VideoDevice *_this);
बाह्य bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool X11_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
बाह्य bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
बाह्य SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
बाह्य bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
बाह्य bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

बाह्य भिन्न X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
बाह्य भिन्न X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
बाह्य शून्य X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
बाह्य शून्य X11_HandleXRandREvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent);
#यदि_अन्तः

#यदि_अन्तः // SDL_x11modes_h_
