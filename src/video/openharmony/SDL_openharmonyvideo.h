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

#ifndef SDL_openharmonyvideo_h_
#define SDL_openharmonyvideo_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceDestroyed(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceChanged(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceCreated(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window);

// Get the app's current native window.
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OpenHarmonyGetNativeWindowPointers(ଶୂନ୍ୟ **xcomponent, ଶୂନ୍ୟ **window);

ସଂରଚନା SDL_VideoData
{
    ଶୂନ୍ୟ *oh_pasteboard;
    ଶୂନ୍ୟ *oh_pasteboard_observer;
    bool clipboard_set;

// !!! FIXME: Android stuff.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା isPaused;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା isPausing;
};

#endif // SDL_openharmonyvideo_h_
