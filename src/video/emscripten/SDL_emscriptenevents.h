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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_emscriptenevents_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_emscriptenevents_h_

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"

ಬಾಹ್ಯ ಶೂನ್ಯ Emscripten_ರಿಜಿಸ್ಟರ್_Global_Event_Handlers(SDL_VideoDevice *device);
ಬಾಹ್ಯ ಶೂನ್ಯ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device);
ಬಾಹ್ಯ ಶೂನ್ಯ Emscripten_ರಿಜಿಸ್ಟರ್_Event_Handlers(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Emscripten_UnregisterEventHandlers(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ EM_BOOL Emscripten_HandleCanvasResize(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *reserved, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_emscriptenevents_h_
