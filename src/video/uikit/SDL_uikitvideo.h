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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_uikitvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_uikitvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__

#ਅਨ੍ਤਰ੍ਭਾਵ <UIKit/UIKit.h>

@interface SDL_UIKit_Video_ਅੰਕੜੇ : NSObject

@property(nonatomic, ਸੌਂਪੋ) id pasteboardObserver;

@property(nonatomic, ਸੌਂਪੋ) bool setting_clipboard;

@ਸਿਰਾ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_VISIONOS
ਬਾਹਰੀ CGRect UIKit_Compute_View_ਚੌਖਟਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ CGRect UIKit_Compute_View_ਚੌਖਟਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, UIScreen *screen);
#ਜੇ_ਅੰਤ

ਬਾਹਰੀ API_ਉਪਲਬਧ(ios(13.0)) UIWindowScene *UIKit_Get_ਸਰਗਰਮ_ਖਿੜਕੀ_Scene(ਖਾਲੀ);

ਬਾਹਰੀ ਖਾਲੀ UIKit_ਸੈੱਟ_Game_Controller_Interaction(bool enabled);
ਬਾਹਰੀ ਖਾਲੀ UIKit_ਸੈੱਟ_View_Game_Controller_Interaction(UIView *view, bool enabled);

#ਜੇ !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
ਬਾਹਰੀ UIInterfaceOrientation UIKit_GetInterfaceOrientation(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // __OBJC__

ਬਾਹਰੀ bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

ਬਾਹਰੀ ਖਾਲੀ UIKit_ForceUpdateHomeIndicator(ਖਾਲੀ);

ਬਾਹਰੀ bool UIKit_Is_System_ਸੰਸਕਰਣ_At_ਘੱਟ_ਤੋਂ_ਘੱਟ(ਦੁੱਗਣਾ ਸੰਸਕਰਣ);

ਬਾਹਰੀ SDL_SystemTheme UIKit_GetSystemTheme(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_uikitvideo_h_
