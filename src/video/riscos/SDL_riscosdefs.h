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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_riscosdefs_h_
#تعریف_کن SDL_riscosdefs_h_

تعريفنوع بنية sprite_area
{
    صحيح اندازه;  // +0
    صحيح شمار; // +4
    صحيح شروع; // +8
    صحيح انتها;   // +12
} sprite_area;

SDL_COMPILE_زمان_ASSERT(sprite_area, حجم(sprite_area) == 16);

تعريفنوع بنية sprite_سرآیند
{
    صحيح بعدی;         // +0
    حرف name[12];    // +4
    صحيح عرض;        // +16
    صحيح ارتفاع;       // +20
    صحيح اولی_بیت;    // +24
    صحيح آخرین_بیت;     // +28
    صحيح image_جابه_جایی_2; // +32
    صحيح ماسک_جابه_جایی;  // +36
    صحيح نما;         // +40
} sprite_سرآیند;

SDL_COMPILE_زمان_ASSERT(sprite_سرآیند, حجم(sprite_سرآیند) == 44);

#پایان_اگر // SDL_riscosdefs_h_
