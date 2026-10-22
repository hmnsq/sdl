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
extern void Android_SetScreenResolution(целое surfaceWidth, целое surfaceHeight, целое deviceWidth, целое deviceHeight, float density, float rate);
extern void Android_SetScreenHDRHeadroom(float headroom);
extern void Android_SetFormat(целое format_wanted, целое format_got);
extern void Android_SetOrientation(SDL_DisplayOrientation orientation);
extern void Android_SendResize(SDL_Window *window);
extern void Android_SetWindowSafeAreaInsets(целое left, целое right, целое top, целое bottom);
extern void Android_SetDarkMode(bool enabled);

// Private display data

struct SDL_VideoData
{
    целое isPaused;
    целое isPausing;
};

extern целое Android_SurfaceWidth;
extern целое Android_SurfaceHeight;
extern float Android_ScreenDensity;
extern целое Android_SafeInsetLeft;
extern целое Android_SafeInsetRight;
extern целое Android_SafeInsetTop;
extern целое Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
