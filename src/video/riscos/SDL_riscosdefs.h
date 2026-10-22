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

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

تعریفنوع ساختار sprite_area
{
    صحیح size;  // +0
    صحیح شمار; // +4
    صحیح start; // +8
    صحیح end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, اندازه(sprite_area) == 16);

تعریفنوع ساختار sprite_header
{
    صحیح next;         // +0
    نویسه name[12];    // +4
    صحیح width;        // +16
    صحیح height;       // +20
    صحیح first_bit;    // +24
    صحیح last_bit;     // +28
    صحیح image_offset; // +32
    صحیح mask_offset;  // +36
    صحیح mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, اندازه(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
