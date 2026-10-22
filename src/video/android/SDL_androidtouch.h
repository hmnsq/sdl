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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_androidvideo.h"

বাহ্যিক শূন্য Android_InitTouch(শূন্য);
বাহ্যিক শূন্য Android_QuitTouch(শূন্য);
বাহ্যিক শূন্য Android_OnTouch(SDL_Window *window, পূর্ণসংখ্যা touch_device_id_in, পূর্ণসংখ্যা pointer_finger_id_in, পূর্ণসংখ্যা action, দশমিক x, দশমিক y, দশমিক p);
বাহ্যিক SDL_TouchID Android_ConvertJavaTouchID(পূর্ণসংখ্যা touchID);
