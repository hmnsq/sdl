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
#अगर_अघोषित SDL_uikitvideo_h_
#घोषणा SDL_uikitvideo_h_

#समावेश "../SDL_sysvideo.h"

#अगर_घोषित __OBJC__

#समावेश <UIKit/UIKit.h>

@interface SDL_UIKit_Video_तथ्य : NSObject

@property(nonatomic, assign) id pasteboardObserver;

@property(nonatomic, assign) bool setting_clipboard;

@end

#अगर_घोषित SDL_PLATFORM_VISIONOS
बाह्य CGRect UIKit_ComputeViewFrame(SDL_Window *window);
#अन्यथा
बाह्य CGRect UIKit_ComputeViewFrame(SDL_Window *window, UIScreen *screen);
#पूर्ण_अगर

बाह्य API_AVAILABLE(ios(13.0)) UIWindowScene *UIKit_GetActiveWindowScene(व्योम);

बाह्य व्योम UIKit_SetGameControllerInteraction(bool enabled);
बाह्य व्योम UIKit_SetViewGameControllerInteraction(UIView *view, bool enabled);

#अगर !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
बाह्य UIInterfaceOrientation UIKit_GetInterfaceOrientation(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर // __OBJC__

बाह्य bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

बाह्य व्योम UIKit_ForceUpdateHomeIndicator(व्योम);

बाह्य bool UIKit_IsSystemVersionAtLeast(द्विगुन version);

बाह्य SDL_SystemTheme UIKit_GetSystemTheme(व्योम);

#पूर्ण_अगर // SDL_uikitvideo_h_
