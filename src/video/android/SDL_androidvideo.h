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
#شامل "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#شامل "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
بیرونی تهی Android_SetScreenResolution(صحیح surfaceWidth, صحیح surfaceHeight, صحیح deviceWidth, صحیح deviceHeight, اعشاری density, اعشاری rate);
بیرونی تهی Android_SetScreenHDRHeadroom(اعشاری headroom);
بیرونی تهی Android_SetFormat(صحیح format_wanted, صحیح format_got);
بیرونی تهی Android_SetOrientation(SDL_DisplayOrientation orientation);
بیرونی تهی Android_SendResize(SDL_Window *window);
بیرونی تهی Android_SetWindowSafeAreaInsets(صحیح چپ, صحیح راست, صحیح بالاترین, صحیح bottom);
بیرونی تهی Android_SetDarkMode(bool enabled);

// Private display data

ساختار SDL_VideoData
{
    صحیح isPaused;
    صحیح isPausing;
};

بیرونی صحیح Android_SurfaceWidth;
بیرونی صحیح Android_SurfaceHeight;
بیرونی اعشاری Android_ScreenDensity;
بیرونی صحیح Android_Safe_Inset_چپ;
بیرونی صحیح Android_Safe_Inset_راست;
بیرونی صحیح Android_Safe_Inset_بالاترین;
بیرونی صحیح Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
