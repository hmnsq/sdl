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

#અન્તર્ભાવ "../SDL_sysvideo.h"

#ifdef __OBJC__

#અન્તર્ભાવ <UIKit/UIKit.h>

@interface SDL_UIKitVideoData : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#ifdef SDL_PLATFORM_VISIONOS
બાહ્ય CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#નહીંતર
બાહ્ય CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#endif

બાહ્ય API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(શૂન્ય);

બાહ્ય શૂન્ય UIKit_SetGameControllerInteraction(bool enabled);
બાહ્ય શૂન્ય UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#જો !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
બાહ્ય UIInterfaceOrientation UIKit_GetInterfaceOrientation(શૂન્ય);
#endif

#endif // __OBJC__

બાહ્ય bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

બાહ્ય શૂન્ય UIKit_ForceUpdateHomeIndicator(શૂન્ય);

બાહ્ય bool UIKit_IsSystemVersionAtLeast(દ્વિગુણ version);

બાહ્ય SDL_SystemTheme UIKit_GetSystemTheme(શૂન્ય);

#endif // SDL_uikitvideo_h_
