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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11modes_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11modes_h_

#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ screen;
    Visual *visual;
    ಪೂರ್ಣಾಂಕ ಆಳ_2;
    ಪೂರ್ಣಾಂಕ scanline_pad;
    ಪೂರ್ಣಾಂಕ x;
    ಪೂರ್ಣಾಂಕ y;

    Uint64 ಬಹುಲಕ_switch_deadline_ns;

    bool use_xrandr;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    ಅಕ್ಷರ connector_name[16];
#ಆದರೆ_ಅಂತ್ಯ
};

ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_ಬಹುಲಕ;
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ ಬಳಸದ; // just so struct isn't empty.
#ಆದರೆ_ಅಂತ್ಯ
};

ಬಾಹ್ಯ bool X11_InitModes(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool X11_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
ಬಾಹ್ಯ bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
ಬಾಹ್ಯ SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
ಬಾಹ್ಯ bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
ಬಾಹ್ಯ bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

ಬಾಹ್ಯ ದಶಮಾಂಶ X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
ಬಾಹ್ಯ ದಶಮಾಂಶ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
ಬಾಹ್ಯ ಶೂನ್ಯ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_HandleXRandREvent(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XEvent *xevent);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11modes_h_
