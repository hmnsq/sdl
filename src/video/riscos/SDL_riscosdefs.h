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

प्रकारव्याख्या संरचना sprite_area
{
    पूर्णांक size;  // +0
    पूर्णांक मोजणी; // +4
    पूर्णांक start; // +8
    पूर्णांक end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, आकार(sprite_area) == 16);

प्रकारव्याख्या संरचना sprite_header
{
    पूर्णांक next;         // +0
    अक्षर name[12];    // +4
    पूर्णांक width;        // +16
    पूर्णांक height;       // +20
    पूर्णांक first_bit;    // +24
    पूर्णांक last_bit;     // +28
    पूर्णांक image_offset; // +32
    पूर्णांक mask_offset;  // +36
    पूर्णांक mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, आकार(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
