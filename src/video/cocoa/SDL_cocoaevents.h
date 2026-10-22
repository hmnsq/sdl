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

#నిర్వచితం_కాకపోతే SDL_cocoaevents_h_
#నిర్వచించు SDL_cocoaevents_h_

బాహ్య శూన్య Cocoa_రిజిస్టరు_App(శూన్య);
బాహ్య Uint64 Cocoa_GetEventTimestamp(NSTimeInterval nsTimestamp);
బాహ్య శూన్య Cocoa_PumpEvents(SDL_VideoDevice *_this);
బాహ్య పూర్ణాంకం Cocoa_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
బాహ్య శూన్య Cocoa_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_SuspendScreenSaver(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_cocoaevents_h_
