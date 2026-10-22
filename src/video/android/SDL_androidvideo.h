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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#அந்தர்பாவ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
வெளி வெறுமை Android_SetScreenResolution(முழு surfaceWidth, முழு surfaceHeight, முழு deviceWidth, முழு deviceHeight, தசம density, தசம rate);
வெளி வெறுமை Android_SetScreenHDRHeadroom(தசம headroom);
வெளி வெறுமை Android_SetFormat(முழு format_wanted, முழு format_got);
வெளி வெறுமை Android_SetOrientation(SDL_DisplayOrientation orientation);
வெளி வெறுமை Android_SendResize(SDL_Window *window);
வெளி வெறுமை Android_SetWindowSafeAreaInsets(முழு இடது, முழு வலது, முழு உச்சி, முழு bottom);
வெளி வெறுமை Android_SetDarkMode(bool enabled);

// Private display data

கட்டமைப்பு SDL_VideoData
{
    முழு isPaused;
    முழு isPausing;
};

வெளி முழு Android_SurfaceWidth;
வெளி முழு Android_SurfaceHeight;
வெளி தசம Android_ScreenDensity;
வெளி முழு Android_Safe_Inset_இடது;
வெளி முழு Android_Safe_Inset_வலது;
வெளி முழு Android_Safe_Inset_உச்சி;
வெளி முழு Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
