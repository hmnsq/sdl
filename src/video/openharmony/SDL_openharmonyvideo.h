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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_openharmonyvideo_h_
#घोषणा SDL_openharmonyvideo_h_

#समावेश "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
बाह्य व्योम SDL_OpenHarmonyVideoSurfaceDestroyed(व्योम *component, व्योम *window);
बाह्य व्योम SDL_OpenHarmonyVideoSurfaceChanged(व्योम *component, व्योम *window);
बाह्य व्योम SDL_OpenHarmonyVideoSurfaceCreated(व्योम *component, व्योम *window);

// Get the app's current native window.
बाह्य व्योम SDL_OpenHarmonyGetNativeWindowPointers(व्योम **xcomponent, व्योम **window);

काष्ठा SDL_Video_तथ्य
{
    व्योम *oh_pasteboard;
    व्योम *oh_pasteboard_observer;
    bool clipboard_set;

// !!! FIXME: Android stuff.
    पूर्णांक isPaused;
    पूर्णांक isPausing;
};

#पूर्ण_अगर // SDL_openharmonyvideo_h_
