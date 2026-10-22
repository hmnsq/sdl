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

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ifdef __OBJC__

#ಅನ್ತರ್ಭಾವ <UIKit/UIKit.h>

@interface SDL_UIKitVideoData : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#ifdef SDL_PLATFORM_VISIONOS
ಬಾಹ್ಯ CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#ಅನ್ಯಥಾ
ಬಾಹ್ಯ CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#endif

ಬಾಹ್ಯ API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_SetGameControllerInteraction(bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#ಯದಿ !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
ಬಾಹ್ಯ UIInterfaceOrientation UIKit_GetInterfaceOrientation(ಶೂನ್ಯ);
#endif

#endif // __OBJC__

ಬಾಹ್ಯ bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_ForceUpdateHomeIndicator(ಶೂನ್ಯ);

ಬಾಹ್ಯ bool UIKit_IsSystemVersionAtLeast(ದ್ವಿಗುಣ version);

ಬಾಹ್ಯ SDL_SystemTheme UIKit_GetSystemTheme(ಶೂನ್ಯ);

#endif // SDL_uikitvideo_h_
