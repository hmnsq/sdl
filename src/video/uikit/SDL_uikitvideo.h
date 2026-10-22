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

#অন্তর্ভাব "../SDL_sysvideo.h"

#ifdef __OBJC__

#অন্তর্ভাব <UIKit/UIKit.h>

@interface SDL_UIKit_Video_তথ্য : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#ifdef SDL_PLATFORM_VISIONOS
বাহ্যিক CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#অন্যথা
বাহ্যিক CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#endif

বাহ্যিক API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(শূন্য);

বাহ্যিক শূন্য UIKit_SetGameControllerInteraction(bool enabled);
বাহ্যিক শূন্য UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#যদি !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
বাহ্যিক UIInterfaceOrientation UIKit_GetInterfaceOrientation(শূন্য);
#endif

#endif // __OBJC__

বাহ্যিক bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

বাহ্যিক শূন্য UIKit_ForceUpdateHomeIndicator(শূন্য);

বাহ্যিক bool UIKit_IsSystemVersionAtLeast(দ্বিগুণ version);

বাহ্যিক SDL_SystemTheme UIKit_GetSystemTheme(শূন্য);

#endif // SDL_uikitvideo_h_
