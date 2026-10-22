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

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

تعريفنوع بنية sprite_area
{
    صحيح size;  // +0
    صحيح کيراءن; // +4
    صحيح start; // +8
    صحيح end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, حجم(sprite_area) == 16);

تعريفنوع بنية sprite_header
{
    صحيح next;         // +0
    حرف name[12];    // +4
    صحيح width;        // +16
    صحيح height;       // +20
    صحيح first_bit;    // +24
    صحيح last_bit;     // +28
    صحيح image_offset; // +32
    صحيح mask_offset;  // +36
    صحيح mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, حجم(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
