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

#నిర్వచితం_కాకపోతే SDL_emscriptenevents_h_
#నిర్వచించు SDL_emscriptenevents_h_

#అన్తర్భావ "SDL_emscriptenvideo.h"

బాహ్య శూన్య Emscripten_రిజిస్టరు_Global_Event_Handlers(SDL_VideoDevice *device);
బాహ్య శూన్య Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device);
బాహ్య శూన్య Emscripten_రిజిస్టరు_Event_Handlers(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య Emscripten_UnregisterEventHandlers(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య EM_BOOL Emscripten_HandleCanvasResize(పూర్ణాంకం eventType, స్థిరరాశి శూన్య *reserved, శూన్య *user_దత్తాంశం);

#అయితే_ముగింపు // SDL_emscriptenevents_h_
