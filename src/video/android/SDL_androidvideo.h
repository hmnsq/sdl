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
#include "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#include "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
extern void Android_SetScreenResolution(පූර්ණ_සංඛ්‍යා surfaceWidth, පූර්ණ_සංඛ්‍යා surfaceHeight, පූර්ණ_සංඛ්‍යා deviceWidth, පූර්ණ_සංඛ්‍යා deviceHeight, float density, float rate);
extern void Android_SetScreenHDRHeadroom(float headroom);
extern void Android_SetFormat(පූර්ණ_සංඛ්‍යා format_wanted, පූර්ණ_සංඛ්‍යා format_got);
extern void Android_SetOrientation(SDL_DisplayOrientation orientation);
extern void Android_SendResize(SDL_Window *window);
extern void Android_SetWindowSafeAreaInsets(පූර්ණ_සංඛ්‍යා left, පූර්ණ_සංඛ්‍යා right, පූර්ණ_සංඛ්‍යා top, පූර්ණ_සංඛ්‍යා bottom);
extern void Android_SetDarkMode(bool enabled);

// Private display data

sa_nracanaa SDL_VideoData
{
    පූර්ණ_සංඛ්‍යා isPaused;
    පූර්ණ_සංඛ්‍යා isPausing;
};

extern පූර්ණ_සංඛ්‍යා Android_SurfaceWidth;
extern පූර්ණ_සංඛ්‍යා Android_SurfaceHeight;
extern float Android_ScreenDensity;
extern පූර්ණ_සංඛ්‍යා Android_SafeInsetLeft;
extern පූර්ණ_සංඛ්‍යා Android_SafeInsetRight;
extern පූර්ණ_සංඛ්‍යා Android_SafeInsetTop;
extern පූර්ණ_සංඛ්‍යා Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
