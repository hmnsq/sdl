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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_riscosdefs_h_
#تعریف_کرو SDL_riscosdefs_h_

قسمتعریف ساخت sprite_area
{
    صحیح سائز;  // +0
    صحیح گنتی; // +4
    صحیح آغاز; // +8
    صحیح انتہا;   // +12
} sprite_area;

SDL_COMPILE_وقت_ASSERT(sprite_area, حجم(sprite_area) == 16);

قسمتعریف ساخت sprite_سرخی
{
    صحیح اگلا;         // +0
    حرف name[12];    // +4
    صحیح چوڑائی;        // +16
    صحیح اونچائی;       // +20
    صحیح پہلا_ثنائی_ہندسہ;    // +24
    صحیح آخری_ثنائی_ہندسہ;     // +28
    صحیح image_انحراف_2; // +32
    صحیح نقاب_انحراف;  // +36
    صحیح منوال;         // +40
} sprite_سرخی;

SDL_COMPILE_وقت_ASSERT(sprite_سرخی, حجم(sprite_سرخی) == 44);

#اگر_ختم // SDL_riscosdefs_h_
