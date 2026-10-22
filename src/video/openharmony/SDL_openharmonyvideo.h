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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_openharmonyvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_openharmonyvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
ਬਾਹਰੀ ਖਾਲੀ SDL_OpenHarmonyVideoSurfaceDestroyed(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_Open_Harmony_Video_Surface_ਬਦਲਿਆ(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_OpenHarmonyVideoSurfaceCreated(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ);

// Get the app's current native window.
ਬਾਹਰੀ ਖਾਲੀ SDL_Open_Harmony_Get_Native_ਖਿੜਕੀ_ਸੂਚਕ_ਸਾਰੇ(ਖਾਲੀ **xcomponent, ਖਾਲੀ **ਖਿੜਕੀ);

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    ਖਾਲੀ *oh_pasteboard;
    ਖਾਲੀ *oh_pasteboard_observer;
    bool clipboard_ਸੈੱਟ;

// !!! FIXME: Android stuff.
    ਪੂਰਨ isPaused;
    ਪੂਰਨ isPausing;
};

#ਜੇ_ਅੰਤ // SDL_openharmonyvideo_h_
