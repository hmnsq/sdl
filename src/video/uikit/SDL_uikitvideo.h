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
#جے_بنا_تعریف SDL_uikitvideo_h_
#تعریف_کرو SDL_uikitvideo_h_

#ضمن "../SDL_sysvideo.h"

#جے_تعریف_شدہ __OBJC__

#ضمن <UIKit/UIKit.h>

@interface SDL_UIKit_Video_انکڑے : NSObject

@property(nonatomic, سونپو) id pasteboardObserver;

@property(nonatomic, سونپو) bool setting_clipboard;

@سرا

#جے_تعریف_شدہ SDL_PLATFORM_VISIONOS
خارجي CGRect UIKit_Compute_View_چوکھٹا(SDL_کھڑکی *کھڑکی);
#وإلا
خارجي CGRect UIKit_Compute_View_چوکھٹا(SDL_کھڑکی *کھڑکی, UIScreen *screen);
#جے_انت

خارجي API_دستیاب(ios(13.0)) UIWindowScene *UIKit_Get_سرگرم_کھڑکی_Scene(فراغ);

خارجي فراغ UIKit_سیٹ_Game_Controller_Interaction(bool enabled);
خارجي فراغ UIKit_سیٹ_View_Game_Controller_Interaction(UIView *view, bool enabled);

#إذا !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
خارجي UIInterfaceOrientation UIKit_GetInterfaceOrientation(فراغ);
#جے_انت

#جے_انت // __OBJC__

خارجي bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

خارجي فراغ UIKit_ForceUpdateHomeIndicator(فراغ);

خارجي bool UIKit_Is_System_نسخہ_At_گھٹ_توں_گھٹ(مزدوج نسخہ);

خارجي SDL_SystemTheme UIKit_GetSystemTheme(فراغ);

#جے_انت // SDL_uikitvideo_h_
