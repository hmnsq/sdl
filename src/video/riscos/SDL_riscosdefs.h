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

#که_نه_تعریف_شوی SDL_riscosdefs_h_
#تعریف_کړه SDL_riscosdefs_h_

تعريفنوع بنية sprite_area
{
    صحيح اندازه;  // +0
    صحيح شمېر; // +4
    صحيح پیل; // +8
    صحيح پای_ټکی;   // +12
} sprite_area;

SDL_COMPILE_وخت_ASSERT(sprite_area, حجم(sprite_area) == 16);

تعريفنوع بنية sprite_سرلیک
{
    صحيح بل;         // +0
    حرف name[12];    // +4
    صحيح پلنوالی;        // +16
    صحيح لوړوالی;       // +20
    صحيح لومړی_بټ;    // +24
    صحيح وروستی_بټ;     // +28
    صحيح image_دننه_واټن_2; // +32
    صحيح ماسک_دننه_واټن;  // +36
    صحيح ډېرپېښ;         // +40
} sprite_سرلیک;

SDL_COMPILE_وخت_ASSERT(sprite_سرلیک, حجم(sprite_سرلیک) == 44);

#د_که_پای // SDL_riscosdefs_h_
