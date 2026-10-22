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

#अन्तर्भाव "../SDL_sysvideo.h"

#ifdef __OBJC__

#अन्तर्भाव <UIKit/UIKit.h>

@interface SDL_UIKitVideoData : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#ifdef SDL_PLATFORM_VISIONOS
बाह्य CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#अण्णहा
बाह्य CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#endif

बाह्य API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(शून्य);

बाह्य शून्य UIKit_SetGameControllerInteraction(bool enabled);
बाह्य शून्य UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#जइ !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
बाह्य UIInterfaceOrientation UIKit_GetInterfaceOrientation(शून्य);
#endif

#endif // __OBJC__

बाह्य bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

बाह्य शून्य UIKit_ForceUpdateHomeIndicator(शून्य);

बाह्य bool UIKit_IsSystemVersionAtLeast(द्विगुण version);

बाह्य SDL_SystemTheme UIKit_GetSystemTheme(शून्य);

#endif // SDL_uikitvideo_h_
