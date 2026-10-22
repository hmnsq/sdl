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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_openharmonyvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_openharmonyvideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// these are fired from XComponent callbacks registered in src/core/openharmony/SDL_openharmony.c
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OpenHarmonyVideoSurfaceDestroyed(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Open_Harmony_Video_Surface_ಬದಲಾಯಿತು(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OpenHarmonyVideoSurfaceCreated(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);

// Get the app's current native window.
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Open_Harmony_Get_Native_ಕಿಟಕಿ_ಸೂಚಕಗಳು(ಶೂನ್ಯ **xcomponent, ಶೂನ್ಯ **ಕಿಟಕಿ);

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    ಶೂನ್ಯ *oh_pasteboard;
    ಶೂನ್ಯ *oh_pasteboard_observer;
    bool clipboard_ಗಣ;

// !!! FIXME: Android stuff.
    ಪೂರ್ಣಾಂಕ isPaused;
    ಪೂರ್ಣಾಂಕ isPausing;
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_openharmonyvideo_h_
