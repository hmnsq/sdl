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
#include "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

typedef sa_nracanaa sprite_area
{
    puur_naa_nka size;  // +0
    puur_naa_nka count; // +4
    puur_naa_nka start; // +8
    puur_naa_nka end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, parimaa_na(sprite_area) == 16);

typedef sa_nracanaa sprite_header
{
    puur_naa_nka next;         // +0
    var_na name[12];    // +4
    puur_naa_nka width;        // +16
    puur_naa_nka height;       // +20
    puur_naa_nka first_bit;    // +24
    puur_naa_nka last_bit;     // +28
    puur_naa_nka image_offset; // +32
    puur_naa_nka mask_offset;  // +36
    puur_naa_nka mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, parimaa_na(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
