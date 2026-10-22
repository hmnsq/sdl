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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

வகைவரை கட்டமைப்பு sprite_area
{
    முழு size;  // +0
    முழு மொத்தம்; // +4
    முழு start; // +8
    முழு end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, அளவு(sprite_area) == 16);

வகைவரை கட்டமைப்பு sprite_header
{
    முழு next;         // +0
    எழுத்து name[12];    // +4
    முழு width;        // +16
    முழு height;       // +20
    முழு first_bit;    // +24
    முழு last_bit;     // +28
    முழு image_offset; // +32
    முழு mask_offset;  // +36
    முழு mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, அளவு(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
