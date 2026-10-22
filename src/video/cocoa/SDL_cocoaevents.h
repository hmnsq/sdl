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

#که_نه_تعریف_شوی SDL_cocoaevents_h_
#تعریف_کړه SDL_cocoaevents_h_

خارجي فراغ Cocoa_ثبتوونکی_App(فراغ);
خارجي Uint64 Cocoa_GetEventTimestamp(NSTimeInterval nsTimestamp);
خارجي فراغ Cocoa_PumpEvents(SDL_VideoDevice *_this);
خارجي صحيح Cocoa_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
خارجي فراغ Cocoa_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_SuspendScreenSaver(SDL_VideoDevice *_this);

#د_که_پای // SDL_cocoaevents_h_
