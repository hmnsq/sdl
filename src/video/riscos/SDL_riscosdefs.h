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

typedef struct sprite_area
{
    цео size;  // +0
    цео count; // +4
    цео start; // +8
    цео end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, sizeof(sprite_area) == 16);

typedef struct sprite_header
{
    цео next;         // +0
    char name[12];    // +4
    цео width;        // +16
    цео height;       // +20
    цео first_bit;    // +24
    цео last_bit;     // +28
    цео image_offset; // +32
    цео mask_offset;  // +36
    цео mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, sizeof(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
