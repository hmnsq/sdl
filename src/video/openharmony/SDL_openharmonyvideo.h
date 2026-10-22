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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_openharmonyvideo_h_
#నిర్వచించు SDL_openharmonyvideo_h_

#అన్తర్భావ "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
బాహ్య శూన్య SDL_OpenHarmonyVideoSurfaceDestroyed(శూన్య *component, శూన్య *కిటికీ);
బాహ్య శూన్య SDL_Open_Harmony_Video_Surface_మారింది(శూన్య *component, శూన్య *కిటికీ);
బాహ్య శూన్య SDL_OpenHarmonyVideoSurfaceCreated(శూన్య *component, శూన్య *కిటికీ);

// Get the app's current native window.
బాహ్య శూన్య SDL_Open_Harmony_Get_Native_కిటికీ_సూచికలు(శూన్య **xcomponent, శూన్య **కిటికీ);

నిర్మాణం SDL_Video_దత్తాంశం
{
    శూన్య *oh_pasteboard;
    శూన్య *oh_pasteboard_observer;
    bool clipboard_సమితి;

// !!! FIXME: Android stuff.
    పూర్ణాంకం isPaused;
    పూర్ణాంకం isPausing;
};

#అయితే_ముగింపు // SDL_openharmonyvideo_h_
