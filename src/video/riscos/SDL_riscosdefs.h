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

#جے_بنا_تعریف SDL_riscosdefs_h_
#تعریف_کرو SDL_riscosdefs_h_

تعريفنوع بنية sprite_area
{
    صحيح ناپ;  // +0
    صحيح گنتی; // +4
    صحيح شروع; // +8
    صحيح سرا;   // +12
} sprite_area;

SDL_COMPILE_ویلا_ASSERT(sprite_area, حجم(sprite_area) == 16);

تعريفنوع بنية sprite_سرخی
{
    صحيح اگلا;         // +0
    حرف name[12];    // +4
    صحيح چوڑائی;        // +16
    صحيح اچائی;       // +20
    صحيح پہلا_ثنائی_ہندسہ;    // +24
    صحيح آخری_ثنائی_ہندسہ;     // +28
    صحيح image_وتھ_2; // +32
    صحيح نقاب_وتھ;  // +36
    صحيح منوال;         // +40
} sprite_سرخی;

SDL_COMPILE_ویلا_ASSERT(sprite_سرخی, حجم(sprite_سرخی) == 44);

#جے_انت // SDL_riscosdefs_h_
