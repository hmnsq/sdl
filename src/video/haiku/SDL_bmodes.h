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

#اگر_غیر_تعریف_شدہ SDL_BMODES_H
#تعریف_کرو SDL_BMODES_H

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

#شامل "../SDL_sysvideo.h"

خارجی SDL_PixelFormat HAIKU_Color_Space_مقصد_SDLPx_Format(uint32 colorspace);

خارجی bool HAIKU_InitModes(SDL_VideoDevice *_this);
خارجی خالی HAIKU_QuitModes(SDL_VideoDevice *_this);
خارجی bool HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
خارجی bool HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool HAIKU_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
