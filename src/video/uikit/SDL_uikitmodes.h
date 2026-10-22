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
#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_uikitmodes_h_
#تعریف_کرو SDL_uikitmodes_h_

#ضمن "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_انکڑے : NSObject

#جے_بنا_تعریف SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#جے_انت

@سرا

@interface SDL_UIKit_Display_منوال_انکڑے : NSObject
#جے_بنا_تعریف SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreen_منوال *uiscreenmode;
#جے_انت

@سرا

#جے_بنا_تعریف SDL_PLATFORM_VISIONOS
خارجي bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#جے_انت

خارجي bool UIKit_InitModes(SDL_VideoDevice *_this);
#جے_بنا_تعریف SDL_PLATFORM_VISIONOS
خارجي bool UIKit_جوڑو_Display(UIScreen *uiscreen, bool send_event);
خارجي فراغ UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#جے_انت
خارجي bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool UIKit_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجي فراغ UIKit_QuitModes(SDL_VideoDevice *_this);
خارجي bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#جے_تعریف_شدہ SDL_PLATFORM_VISIONOS
#تعریف_کرو SDL_XR_SCREENWIDTH 1280
#تعریف_کرو SDL_XR_SCREENHEIGHT 720
#جے_انت

#جے_انت // SDL_uikitmodes_h_
