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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoamodes_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoamodes_h_

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    CGDirectDisplayID display;
    SDL_Rect usable_bounds;
};

ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
    CFMutableArrayRef modes;
};

ਬਾਹਰੀ ਖਾਲੀ Cocoa_InitModes(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_UpdateDisplays(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool Cocoa_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ਬਾਹਰੀ bool Cocoa_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ਬਾਹਰੀ bool Cocoa_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_QuitModes(SDL_VideoDevice *_this);
ਬਾਹਰੀ SDL_VideoDisplay *Cocoa_ਲੱਭੋ_SDLDisplay_By_CGDirect_Display_ID(SDL_VideoDevice *_this, CGDirectDisplayID displayid);

#ਜੇ_ਅੰਤ // SDL_cocoamodes_h_
