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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

પ્રકારવ્યાખ્યા સંરચના sprite_area
{
    પૂર્ણાંક size;  // +0
    પૂર્ણાંક ગણતરી; // +4
    પૂર્ણાંક start; // +8
    પૂર્ણાંક end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, કદ(sprite_area) == 16);

પ્રકારવ્યાખ્યા સંરચના sprite_header
{
    પૂર્ણાંક next;         // +0
    અક્ષર name[12];    // +4
    પૂર્ણાંક width;        // +16
    પૂર્ણાંક height;       // +20
    પૂર્ણાંક first_bit;    // +24
    પૂર્ણાંક last_bit;     // +28
    પૂર્ણાંક image_offset; // +32
    પૂર્ણાંક mask_offset;  // +36
    પૂર્ણાંક mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, કદ(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
