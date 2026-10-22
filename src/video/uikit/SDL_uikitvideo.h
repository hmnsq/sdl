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
#اگر_غیر_تعریف_شدہ SDL_uikitvideo_h_
#تعریف_کرو SDL_uikitvideo_h_

#شامل "../SDL_sysvideo.h"

#اگر_تعریف_شدہ __OBJC__

#شامل <UIKit/UIKit.h>

@interface SDL_UIKit_Video_ڈیٹا : NSObject

@property(nonatomic, تفویض) id pasteboardObserver;

@property(nonatomic, تفویض) bool setting_clipboard;

@انتہا

#اگر_تعریف_شدہ SDL_PLATFORM_VISIONOS
خارجی CGRect UIKit_Compute_View_چوکھٹا(SDL_کھڑکی *کھڑکی);
#ورنہ
خارجی CGRect UIKit_Compute_View_چوکھٹا(SDL_کھڑکی *کھڑکی, UIScreen *screen);
#اگر_ختم

خارجی API_دستیاب(ios(13.0)) UIWindowScene *UIKit_Get_فعال_کھڑکی_Scene(خالی);

خارجی خالی UIKit_سیٹ_Game_Controller_Interaction(bool enabled);
خارجی خالی UIKit_سیٹ_View_Game_Controller_Interaction(UIView *view, bool enabled);

#اگر !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
خارجی UIInterfaceOrientation UIKit_GetInterfaceOrientation(خالی);
#اگر_ختم

#اگر_ختم // __OBJC__

خارجی bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

خارجی خالی UIKit_ForceUpdateHomeIndicator(خالی);

خارجی bool UIKit_Is_System_نسخہ_At_کم_سے_کم(دوہرا نسخہ);

خارجی SDL_SystemTheme UIKit_GetSystemTheme(خالی);

#اگر_ختم // SDL_uikitvideo_h_
