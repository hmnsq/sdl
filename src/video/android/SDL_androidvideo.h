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

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#অন্তর্ভাব "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
বাহ্যিক শূন্য Android_SetScreenResolution(পূর্ণসংখ্যা surfaceWidth, পূর্ণসংখ্যা surfaceHeight, পূর্ণসংখ্যা deviceWidth, পূর্ণসংখ্যা deviceHeight, দশমিক density, দশমিক rate);
বাহ্যিক শূন্য Android_SetScreenHDRHeadroom(দশমিক headroom);
বাহ্যিক শূন্য Android_SetFormat(পূর্ণসংখ্যা format_wanted, পূর্ণসংখ্যা format_got);
বাহ্যিক শূন্য Android_SetOrientation(SDL_DisplayOrientation orientation);
বাহ্যিক শূন্য Android_SendResize(SDL_Window *window);
বাহ্যিক শূন্য Android_SetWindowSafeAreaInsets(পূর্ণসংখ্যা বাম, পূর্ণসংখ্যা ডান, পূর্ণসংখ্যা শীর্ষ, পূর্ণসংখ্যা bottom);
বাহ্যিক শূন্য Android_SetDarkMode(bool enabled);

// Private display data

কাঠামো SDL_Video_তথ্য
{
    পূর্ণসংখ্যা isPaused;
    পূর্ণসংখ্যা isPausing;
};

বাহ্যিক পূর্ণসংখ্যা Android_SurfaceWidth;
বাহ্যিক পূর্ণসংখ্যা Android_SurfaceHeight;
বাহ্যিক দশমিক Android_ScreenDensity;
বাহ্যিক পূর্ণসংখ্যা Android_Safe_Inset_বাম;
বাহ্যিক পূর্ণসংখ্যা Android_Safe_Inset_ডান;
বাহ্যিক পূর্ণসংখ্যা Android_Safe_Inset_শীর্ষ;
বাহ্যিক পূর্ণসংখ্যা Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
