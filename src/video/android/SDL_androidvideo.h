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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
बाह्य शून्य Android_SetScreenResolution(पूर्णाङ्क surfaceWidth, पूर्णाङ्क surfaceHeight, पूर्णाङ्क deviceWidth, पूर्णाङ्क deviceHeight, भिन्न density, भिन्न rate);
बाह्य शून्य Android_SetScreenHDRHeadroom(भिन्न headroom);
बाह्य शून्य Android_SetFormat(पूर्णाङ्क format_wanted, पूर्णाङ्क format_got);
बाह्य शून्य Android_SetOrientation(SDL_DisplayOrientation orientation);
बाह्य शून्य Android_SendResize(SDL_Window *window);
बाह्य शून्य Android_SetWindowSafeAreaInsets(पूर्णाङ्क डावा, पूर्णाङ्क उजवा, पूर्णाङ्क शीर्ष, पूर्णाङ्क bottom);
बाह्य शून्य Android_SetDarkMode(bool enabled);

// Private display data

संरचना SDL_VideoData
{
    पूर्णाङ्क isPaused;
    पूर्णाङ्क isPausing;
};

बाह्य पूर्णाङ्क Android_SurfaceWidth;
बाह्य पूर्णाङ्क Android_SurfaceHeight;
बाह्य भिन्न Android_ScreenDensity;
बाह्य पूर्णाङ्क Android_Safe_Inset_डावा;
बाह्य पूर्णाङ्क Android_Safe_Inset_उजवा;
बाह्य पूर्णाङ्क Android_Safe_Inset_शीर्ष;
बाह्य पूर्णाङ्क Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
