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
বাহ্য শূন্য Android_SetScreenResolution(পূর্ণাঙ্ক surfaceWidth, পূর্ণাঙ্ক surfaceHeight, পূর্ণাঙ্ক deviceWidth, পূর্ণাঙ্ক deviceHeight, ভিন্ন density, ভিন্ন rate);
বাহ্য শূন্য Android_SetScreenHDRHeadroom(ভিন্ন headroom);
বাহ্য শূন্য Android_SetFormat(পূর্ণাঙ্ক format_wanted, পূর্ণাঙ্ক format_got);
বাহ্য শূন্য Android_SetOrientation(SDL_DisplayOrientation orientation);
বাহ্য শূন্য Android_SendResize(SDL_Window *window);
বাহ্য শূন্য Android_SetWindowSafeAreaInsets(পূর্ণাঙ্ক বাম, পূর্ণাঙ্ক ডান, পূর্ণাঙ্ক শীর্ষ, পূর্ণাঙ্ক bottom);
বাহ্য শূন্য Android_SetDarkMode(bool enabled);

// Private display data

সংরচনা SDL_VideoData
{
    পূর্ণাঙ্ক isPaused;
    পূর্ণাঙ্ক isPausing;
};

বাহ্য পূর্ণাঙ্ক Android_SurfaceWidth;
বাহ্য পূর্ণাঙ্ক Android_SurfaceHeight;
বাহ্য ভিন্ন Android_ScreenDensity;
বাহ্য পূর্ণাঙ্ক Android_Safe_Inset_বাম;
বাহ্য পূর্ণাঙ্ক Android_Safe_Inset_ডান;
বাহ্য পূর্ণাঙ্ক Android_Safe_Inset_শীর্ষ;
বাহ্য পূর্ণাঙ্ক Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
