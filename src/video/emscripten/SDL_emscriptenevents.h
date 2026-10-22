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

#جيڪڏهن_وصف_نه_ٿيل SDL_emscriptenevents_h_
#وصف_ڪريو SDL_emscriptenevents_h_

#ضمن "SDL_emscriptenvideo.h"

خارجي فراغ Emscripten_رجسٽر_Global_Event_Handlers(SDL_VideoDevice *device);
خارجي فراغ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device);
خارجي فراغ Emscripten_رجسٽر_Event_Handlers(SDL_دري_معلومات *معلومات);
خارجي فراغ Emscripten_UnregisterEventHandlers(SDL_دري_معلومات *معلومات);
خارجي EM_BOOL Emscripten_HandleCanvasResize(صحيح eventType, ثابت فراغ *reserved, فراغ *user_معلومات);

#جيڪڏهن_پورو // SDL_emscriptenevents_h_
