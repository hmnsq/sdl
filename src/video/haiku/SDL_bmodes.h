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

#که_نه_تعریف_شوی SDL_BMODES_H
#تعریف_کړه SDL_BMODES_H

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

#ضمن "../SDL_sysvideo.h"

خارجي SDL_PixelFormat HAIKU_Color_Space_منزل_SDLPx_Format(uint32 colorspace);

خارجي bool HAIKU_InitModes(SDL_VideoDevice *_this);
خارجي فراغ HAIKU_QuitModes(SDL_VideoDevice *_this);
خارجي bool HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجي bool HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool HAIKU_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
