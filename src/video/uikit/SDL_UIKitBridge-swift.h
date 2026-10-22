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
ਖਾਲੀ SDL_Vision_OS_Send_ਮਾਪ_ਬਦਲਿਆ(ਲੰਮਾ ਚੌੜਾਈ, ਲੰਮਾ ਉਚਾਈ);

// Called from Swift scene delegates to get the initial window settings
NSString *SDL_Vision_OS_Get_ਖਿੜਕੀ_Settings();

// Called from Swift scene delegates when window settings change
ਖਾਲੀ SDL_Vision_OS_Send_ਖਿੜਕੀ_Settings(NSString *settings);

// Called from Swift scene delegates when pointer mode changes
ਖਾਲੀ SDL_Vision_OS_Send_ਸੂਚਕ_ਬਹੁਲਕ(bool enabled);

// Called from Swift scene delegates when window settings are loaded
bool SDL_VisionOS_ShouldShowHeadroomUI();

// Called from Swift scene delegates when headroom changes
ਖਾਲੀ SDL_VisionOS_SendHeadroom(ਦਸ਼ਮਲਵ headroom);

// Called from Swift scene delegates when visionOS delivers a touch event
ਖਾਲੀ SDL_VisionOS_SendTouch(NSTimeInterval timestamp, SDL_FingerID fingerID, Uint32 eventType, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y);

// Called from Swift to register the RealityKit hosting object with the SDL window
ਖਾਲੀ SDL_Vision_OS_ਸੈੱਟ_ਖਿੜਕੀ_Reality_Kit_Hosting(id hosting);
