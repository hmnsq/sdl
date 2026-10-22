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

#جيڪڏهن_وصف_نه_ٿيل SDL_cocoamodes_h_
#وصف_ڪريو SDL_cocoamodes_h_

بنية SDL_Display_معلومات
{
    CGDirectDisplayID display;
    SDL_Rect usable_bounds;
};

بنية SDL_Display_گهڻائي_معلومات
{
    CFMutableArrayRef modes;
};

خارجي فراغ Cocoa_InitModes(SDL_VideoDevice *_this);
خارجي فراغ Cocoa_UpdateDisplays(SDL_VideoDevice *_this);
خارجي bool Cocoa_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجي bool Cocoa_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجي bool Cocoa_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool Cocoa_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);
خارجي فراغ Cocoa_QuitModes(SDL_VideoDevice *_this);
خارجي SDL_VideoDisplay *Cocoa_ڳوليو_SDLDisplay_By_CGDirect_Display_ID(SDL_VideoDevice *_this, CGDirectDisplayID displayid);

#جيڪڏهن_پورو // SDL_cocoamodes_h_
