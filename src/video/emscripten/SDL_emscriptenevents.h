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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_emscriptenevents_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_emscriptenevents_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenvideo.h"

ਬਾਹਰੀ ਖਾਲੀ Emscripten_ਰਜਿਸਟਰ_Global_Event_Handlers(SDL_VideoDevice *device);
ਬਾਹਰੀ ਖਾਲੀ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device);
ਬਾਹਰੀ ਖਾਲੀ Emscripten_ਰਜਿਸਟਰ_Event_Handlers(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ Emscripten_UnregisterEventHandlers(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ EM_BOOL Emscripten_HandleCanvasResize(ਪੂਰਨ eventType, ਅਚਲ ਖਾਲੀ *reserved, ਖਾਲੀ *user_ਅੰਕੜੇ);

#ਜੇ_ਅੰਤ // SDL_emscriptenevents_h_
