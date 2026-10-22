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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetScreenResolution(ପୂର୍ଣ୍ଣସଂଖ୍ୟା surfaceWidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା surfaceHeight, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceWidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceHeight, ଦଶମିକ density, ଦଶମିକ rate);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetScreenHDRHeadroom(ଦଶମିକ headroom);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetFormat(ପୂର୍ଣ୍ଣସଂଖ୍ୟା format_wanted, ପୂର୍ଣ୍ଣସଂଖ୍ୟା format_got);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetOrientation(SDL_DisplayOrientation orientation);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SendResize(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetWindowSafeAreaInsets(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bottom);
ବାହ୍ୟ ଶୂନ୍ୟ Android_SetDarkMode(bool enabled);

// Private display data

ସଂରଚନା SDL_VideoData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା isPaused;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା isPausing;
};

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_SurfaceWidth;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_SurfaceHeight;
ବାହ୍ୟ ଦଶମିକ Android_ScreenDensity;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_Safe_Inset_ବାମ;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_Safe_Inset_ଡାହାଣ;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_Safe_Inset_ଶୀର୍ଷ;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
