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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

തരനിർവചനം ഘടന sprite_area
{
    പൂർണ്ണസംഖ്യ size;  // +0
    പൂർണ്ണസംഖ്യ എണ്ണം; // +4
    പൂർണ്ണസംഖ്യ start; // +8
    പൂർണ്ണസംഖ്യ end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, വലുപ്പം(sprite_area) == 16);

തരനിർവചനം ഘടന sprite_header
{
    പൂർണ്ണസംഖ്യ next;         // +0
    അക്ഷരം name[12];    // +4
    പൂർണ്ണസംഖ്യ width;        // +16
    പൂർണ്ണസംഖ്യ height;       // +20
    പൂർണ്ണസംഖ്യ first_bit;    // +24
    പൂർണ്ണസംഖ്യ last_bit;     // +28
    പൂർണ്ണസംഖ്യ image_offset; // +32
    പൂർണ്ണസംഖ്യ mask_offset;  // +36
    പൂർണ്ണസംഖ്യ mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, വലുപ്പം(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
