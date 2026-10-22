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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା sprite_area
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;  // +0
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2; // +4
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା start; // +8
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, ଆକାର(sprite_area) == 16);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା sprite_header
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା next;         // +0
    ଅକ୍ଷର name[12];    // +4
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;        // +16
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;       // +20
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା first_bit;    // +24
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_bit;     // +28
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା image_offset; // +32
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask_offset;  // +36
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, ଆକାର(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
