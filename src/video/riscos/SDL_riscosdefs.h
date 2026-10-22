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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_riscosdefs_h_
#define SDL_riscosdefs_h_

প্রকারনির্দেশ সংরচনা sprite_area
{
    পূর্ণাঙ্ক size;  // +0
    পূর্ণাঙ্ক গুনতি; // +4
    পূর্ণাঙ্ক start; // +8
    পূর্ণাঙ্ক end;   // +12
} sprite_area;

SDL_COMPILE_TIME_ASSERT(sprite_area, পরিমাণ(sprite_area) == 16);

প্রকারনির্দেশ সংরচনা sprite_header
{
    পূর্ণাঙ্ক next;         // +0
    ৱর্ণ name[12];    // +4
    পূর্ণাঙ্ক width;        // +16
    পূর্ণাঙ্ক height;       // +20
    পূর্ণাঙ্ক first_bit;    // +24
    পূর্ণাঙ্ক last_bit;     // +28
    পূর্ণাঙ্ক image_offset; // +32
    পূর্ণাঙ্ক mask_offset;  // +36
    পূর্ণাঙ্ক mode;         // +40
} sprite_header;

SDL_COMPILE_TIME_ASSERT(sprite_header, পরিমাণ(sprite_header) == 44);

#endif // SDL_riscosdefs_h_
