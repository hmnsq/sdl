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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11modes_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11modes_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    ਪੂਰਨ screen;
    Visual *visual;
    ਪੂਰਨ ਡੂੰਘਾਈ_2;
    ਪੂਰਨ scanline_pad;
    ਪੂਰਨ x;
    ਪੂਰਨ y;

    Uint64 ਬਹੁਲਕ_switch_deadline_ns;

    bool use_xrandr;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    RROutput xrandr_output;
    ਅੱਖਰ connector_name[16];
#ਜੇ_ਅੰਤ
};

ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    RRMode xrandr_ਬਹੁਲਕ;
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ ਅਣਵਰਤਿਆ; // just so struct isn't empty.
#ਜੇ_ਅੰਤ
};

ਬਾਹਰੀ bool X11_InitModes(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ ਖਾਲੀ X11_QuitModes(SDL_VideoDevice *_this);

// Some utility functions for working with visuals
ਬਾਹਰੀ bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo);
ਬਾਹਰੀ SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo);
ਬਾਹਰੀ bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);
ਬਾਹਰੀ bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect);

ਬਾਹਰੀ ਦਸ਼ਮਲਵ X11_GetGlobalContentScale(Display *display, XSettingsClient *client);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
ਬਾਹਰੀ ਖਾਲੀ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy);
ਬਾਹਰੀ ਖਾਲੀ X11_HandleXRandREvent(SDL_VideoDevice *_this, ਅਚਲ XEvent *xevent);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_x11modes_h_
