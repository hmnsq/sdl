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

#اگر_غیر_تعریف_شدہ SDL_vitatouch_h
#تعریف_کرو SDL_vitatouch_h

#شامل "SDL_internal.h"

// Touch functions
خارجی خالی VITA_InitTouch(خالی);
خارجی خالی VITA_QuitTouch(خالی);
خارجی خالی VITA_PollTouch(خالی);
خالی VITA_ConvertTouchXYToSDLXY(اعشاری *sdl_x, اعشاری *sdl_y, صحیح vita_x, صحیح vita_y, صحیح پورٹ);

#اگر_ختم // SDL_vitatouch_h
