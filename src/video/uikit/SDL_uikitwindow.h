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
#اگر_غیر_تعریف_شدہ SDL_uikitwindow_h_
#تعریف_کرو SDL_uikitwindow_h_

#شامل "../SDL_sysvideo.h"
#import "SDL_uikitvideo.h"
#import "SDL_uikitview.h"
#import "SDL_uikitviewcontroller.h"

خارجی bool UIKit_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی UIKit_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجی SDL_Fullscreen_نتیجہ UIKit_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجی خالی UIKit_Update_اشارہ_گر_تالا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی UIKit_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h);

خارجی NSUInteger UIKit_GetSupportedOrientations(SDL_کھڑکی *کھڑکی);

#تعریف_کرو SDL_METALVIEW_لیبل 255

@class UIWindow;

@interface SDL_UIKit_کھڑکی_ڈیٹا : NSObject

@property(nonatomic, strong) UIWindow *uiwindow;
@property(nonatomic, strong) SDL_uikitviewcontroller *viewcontroller;

// Array of SDL_uikitviews owned by this window.
@property(nonatomic, copy) NSMutableArray *views;

#اگر_تعریف_شدہ SDL_PLATFORM_VISIONOS
// Hosting controller for curved content mode (UIHostingController-based)
@property(nonatomic, strong) id curvedContentHosting;
@property(nonatomic, strong) NSString *settings;
#اگر_ختم

@انتہا

#اگر_ختم // SDL_uikitwindow_h_
