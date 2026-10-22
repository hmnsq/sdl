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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_uikitevents_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_uikitevents_h_

#import <UIKit/UIKit.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateLifecycleObserver(ಶೂನ್ಯ);

ಬಾಹ್ಯ Uint64 UIKit_GetEventTimestamp(NSTimeInterval nsTimestamp);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_PumpEvents(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_InitGCKeyboard(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_QuitGCKeyboard(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_InitGCMouse(ಶೂನ್ಯ);
ಬಾಹ್ಯ bool SDL_GCMouse_Relative_ಬಹುಲಕ(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_QuitGCMouse(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_uikitevents_h_
