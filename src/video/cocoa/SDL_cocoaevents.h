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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoaevents_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoaevents_h_

ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਰਜਿਸਟਰ_App(ਖਾਲੀ);
ਬਾਹਰੀ Uint64 Cocoa_GetEventTimestamp(NSTimeInterval nsTimestamp);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_PumpEvents(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਪੂਰਨ Cocoa_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_SuspendScreenSaver(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_cocoaevents_h_
