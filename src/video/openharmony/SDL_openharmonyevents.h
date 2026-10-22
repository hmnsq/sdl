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

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// src/core/openharmony/SDL_openharmony.c calls these when it gets events from the system.
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OpenHarmonyDispatchTouchEvent(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OpenHarmonyDispatchMouseEvent(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Open_Harmony_Dispatch_ಕೀಲಿ_Event(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OpenHarmonyDispatchUIInputEvent(ಶೂನ್ಯ *component, ಶೂನ್ಯ *event, int32_t type);

ಬಾಹ್ಯ ಶೂನ್ಯ OPENHARMONY_InitEvents(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ OPENHARMONY_PumpEvents(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ OPENHARMONY_QuitEvents(ಶೂನ್ಯ);
