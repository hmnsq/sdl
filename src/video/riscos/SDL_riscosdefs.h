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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

प्रकारनिर्देश संरचना sprite_area
{
    पूर्णाङ्क size;  // +0
    पूर्णाङ्क मोजणी; // +4
    पूर्णाङ्क start; // +8
    पूर्णाङ्क end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, परिमाण(sprite_area) == 16);

प्रकारनिर्देश संरचना sprite_header
{
    पूर्णाङ्क next;         // +0
    वर्ण name[12];    // +4
    पूर्णाङ्क width;        // +16
    पूर्णाङ्क height;       // +20
    पूर्णाङ्क first_bit;    // +24
    पूर्णाङ्क last_bit;     // +28
    पूर्णाङ्क image_offset; // +32
    पूर्णाङ्क mask_offset;  // +36
    पूर्णाङ्क mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, परिमाण(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
