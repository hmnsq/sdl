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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetScreenResolution(ಪೂರ್ಣಾಙ್ಕ surfaceWidth, ಪೂರ್ಣಾಙ್ಕ surfaceHeight, ಪೂರ್ಣಾಙ್ಕ deviceWidth, ಪೂರ್ಣಾಙ್ಕ deviceHeight, ಭಿನ್ನ density, ಭಿನ್ನ rate);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetScreenHDRHeadroom(ಭಿನ್ನ headroom);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetFormat(ಪೂರ್ಣಾಙ್ಕ format_wanted, ಪೂರ್ಣಾಙ್ಕ format_got);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetOrientation(SDL_DisplayOrientation orientation);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SendResize(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetWindowSafeAreaInsets(ಪೂರ್ಣಾಙ್ಕ ಎಡ, ಪೂರ್ಣಾಙ್ಕ ಬಲ, ಪೂರ್ಣಾಙ್ಕ ತುದಿ, ಪೂರ್ಣಾಙ್ಕ bottom);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_SetDarkMode(bool enabled);

// Private display data

ಸಂರಚನಾ SDL_VideoData
{
    ಪೂರ್ಣಾಙ್ಕ isPaused;
    ಪೂರ್ಣಾಙ್ಕ isPausing;
};

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_SurfaceWidth;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_SurfaceHeight;
ಬಾಹ್ಯ ಭಿನ್ನ Android_ScreenDensity;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_Safe_Inset_ಎಡ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_Safe_Inset_ಬಲ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_Safe_Inset_ತುದಿ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
