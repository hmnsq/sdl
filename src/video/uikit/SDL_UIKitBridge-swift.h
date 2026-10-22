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
#import "SDL_uikitviewcontroller.h"

// Called from Swift scene delegates when window size changes
శూన్య SDL_Vision_OS_Send_కొలత_మారింది(దీర్ఘ వెడల్పు, దీర్ఘ ఎత్తు);

// Called from Swift scene delegates to get the initial window settings
NSString *SDL_Vision_OS_Get_కిటికీ_Settings();

// Called from Swift scene delegates when window settings change
శూన్య SDL_Vision_OS_Send_కిటికీ_Settings(NSString *settings);

// Called from Swift scene delegates when pointer mode changes
శూన్య SDL_Vision_OS_Send_సూచిక_బహుళకం(bool enabled);

// Called from Swift scene delegates when window settings are loaded
bool SDL_VisionOS_ShouldShowHeadroomUI();

// Called from Swift scene delegates when headroom changes
శూన్య SDL_VisionOS_SendHeadroom(దశాంశం headroom);

// Called from Swift scene delegates when visionOS delivers a touch event
శూన్య SDL_VisionOS_SendTouch(NSTimeInterval timestamp, SDL_FingerID fingerID, Uint32 eventType, దశాంశం x, దశాంశం y);

// Called from Swift to register the RealityKit hosting object with the SDL window
శూన్య SDL_Vision_OS_సమితి_కిటికీ_Reality_Kit_Hosting(id hosting);
