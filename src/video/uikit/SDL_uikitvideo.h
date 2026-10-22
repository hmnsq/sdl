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
#اگر_تعریف_نشده SDL_uikitvideo_h_
#تعریف_کن SDL_uikitvideo_h_

#ضمن "../SDL_sysvideo.h"

#اگر_تعریف_شده __OBJC__

#ضمن <UIKit/UIKit.h>

@interface SDL_UIKit_Video_داده : NSObject

@property(nonatomic, تخصیص_بده) id pasteboardObserver;

@property(nonatomic, تخصیص_بده) bool setting_clipboard;

@انتها

#اگر_تعریف_شده SDL_PLATFORM_VISIONOS
خارجي CGRect UIKit_Compute_View_قاب(SDL_پنجره *پنجره);
#وإلا
خارجي CGRect UIKit_Compute_View_قاب(SDL_پنجره *پنجره, UIScreen *screen);
#پایان_اگر

خارجي API_موجود(ios(13.0)) UIWindowScene *UIKit_Get_فعال_پنجره_Scene(فراغ);

خارجي فراغ UIKit_مجموعه_Game_Controller_Interaction(bool enabled);
خارجي فراغ UIKit_مجموعه_View_Game_Controller_Interaction(UIView *view, bool enabled);

#إذا !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
خارجي UIInterfaceOrientation UIKit_GetInterfaceOrientation(فراغ);
#پایان_اگر

#پایان_اگر // __OBJC__

خارجي bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

خارجي فراغ UIKit_ForceUpdateHomeIndicator(فراغ);

خارجي bool UIKit_Is_System_نسخه_At_کمترین(مزدوج نسخه);

خارجي SDL_SystemTheme UIKit_GetSystemTheme(فراغ);

#پایان_اگر // SDL_uikitvideo_h_
