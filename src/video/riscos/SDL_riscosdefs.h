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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ sprite_area
{
    ಪೂರ್ಣಾಙ್ಕ size;  // +0
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ; // +4
    ಪೂರ್ಣಾಙ್ಕ start; // +8
    ಪೂರ್ಣಾಙ್ಕ end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, ಪರಿಮಾಣ(sprite_area) == 16);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ sprite_header
{
    ಪೂರ್ಣಾಙ್ಕ next;         // +0
    ವರ್ಣ name[12];    // +4
    ಪೂರ್ಣಾಙ್ಕ width;        // +16
    ಪೂರ್ಣಾಙ್ಕ height;       // +20
    ಪೂರ್ಣಾಙ್ಕ first_bit;    // +24
    ಪೂರ್ಣಾಙ್ಕ last_bit;     // +28
    ಪೂರ್ಣಾಙ್ಕ image_offset; // +32
    ಪೂರ್ಣಾಙ್ಕ mask_offset;  // +36
    ಪೂರ್ಣಾಙ್ಕ mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, ಪರಿಮಾಣ(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
