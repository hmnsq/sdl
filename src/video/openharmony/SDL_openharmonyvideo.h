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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_openharmonyvideo_h_
#تعریف_کن SDL_openharmonyvideo_h_

#ضمن "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
خارجي فراغ SDL_OpenHarmonyVideoSurfaceDestroyed(فراغ *component, فراغ *پنجره);
خارجي فراغ SDL_Open_Harmony_Video_Surface_تغییریافته(فراغ *component, فراغ *پنجره);
خارجي فراغ SDL_OpenHarmonyVideoSurfaceCreated(فراغ *component, فراغ *پنجره);

// Get the app's current native window.
خارجي فراغ SDL_Open_Harmony_Get_Native_پنجره_اشارهگرها(فراغ **xcomponent, فراغ **پنجره);

بنية SDL_Video_داده
{
    فراغ *oh_pasteboard;
    فراغ *oh_pasteboard_observer;
    bool clipboard_مجموعه;

// !!! FIXME: Android stuff.
    صحيح isPaused;
    صحيح isPausing;
};

#پایان_اگر // SDL_openharmonyvideo_h_
