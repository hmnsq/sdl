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
#ifndef SDL_uikitvideo_h_
#define SDL_uikitvideo_h_

#شامل "../SDL_sysvideo.h"

#ifdef __OBJC__

#شامل <UIKit/UIKit.h>

@interface SDL_UIKitVideoData : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#ifdef SDL_PLATFORM_VISIONOS
بیرونی CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#وگرنه
بیرونی CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#endif

بیرونی API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(تهی);

بیرونی تهی UIKit_SetGameControllerInteraction(bool enabled);
بیرونی تهی UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#اگر !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
بیرونی UIInterfaceOrientation UIKit_GetInterfaceOrientation(تهی);
#endif

#endif // __OBJC__

بیرونی bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

بیرونی تهی UIKit_ForceUpdateHomeIndicator(تهی);

بیرونی bool UIKit_IsSystemVersionAtLeast(دوگانه version);

بیرونی SDL_SystemTheme UIKit_GetSystemTheme(تهی);

#endif // SDL_uikitvideo_h_
