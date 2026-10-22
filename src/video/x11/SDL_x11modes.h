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

#अगर_अघोषित SDL_x11modes_h_
#घोषणा SDL_x11modes_h_

#समावेश "SDL_x11settings.h"

काष्ठा SDL_Display_तथ्य
{
    पूर्णांक screen;
    Visual *visual;
    पूर्णांक depth;
    पूर्णांक scanline_pad;
    पूर्णांक x;
    पूर्णांक y;

    Uint64 mode_switch_deadline_ns;

    bool use_xrandr;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    अक्षर connector_name[16];
#पूर्ण_अगर
};

काष्ठा SDL_Display_Mode_तथ्य
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_mode;
#अन्यथा
    पूर्णांक unused; // just so struct isn't empty.
#पूर्ण_अगर
};

बाह्य bool X11_InitModes(SDL_VideoDevice *_this);
बाह्य bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य व्योम X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
बाह्य bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
बाह्य SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
बाह्य bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
बाह्य bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

बाह्य भग्न X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
बाह्य भग्न X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
बाह्य व्योम X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
बाह्य व्योम X11_HandleXRandREvent(SDL_VideoDevice *_this, स्थिर XEvent *xevent);
#पूर्ण_अगर

#पूर्ण_अगर // SDL_x11modes_h_
