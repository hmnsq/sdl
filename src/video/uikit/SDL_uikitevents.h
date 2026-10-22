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
#اگر_تعریف_نشده SDL_uikitevents_h_
#تعریف_کن SDL_uikitevents_h_

#import <UIKit/UIKit.h>

#ضمن "../SDL_sysvideo.h"

خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);

خارجي Uint64 UIKit_GetEventTimestamp(NSTimeInterval nsTimestamp);
خارجي فراغ UIKit_PumpEvents(SDL_VideoDevice *_this);

خارجي فراغ SDL_InitGCKeyboard(فراغ);
خارجي فراغ SDL_QuitGCKeyboard(فراغ);

خارجي فراغ SDL_InitGCMouse(فراغ);
خارجي bool SDL_GCMouse_Relative_نما(فراغ);
خارجي فراغ SDL_QuitGCMouse(فراغ);

#پایان_اگر // SDL_uikitevents_h_
