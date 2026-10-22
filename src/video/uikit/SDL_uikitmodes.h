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

#اگر_تعریف_نشده SDL_uikitmodes_h_
#تعریف_کن SDL_uikitmodes_h_

#ضمن "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_داده : NSObject

#اگر_تعریف_نشده SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#پایان_اگر

@انتها

@interface SDL_UIKit_Display_نما_داده : NSObject
#اگر_تعریف_نشده SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreen_نما *uiscreenmode;
#پایان_اگر

@انتها

#اگر_تعریف_نشده SDL_PLATFORM_VISIONOS
خارجي bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#پایان_اگر

خارجي bool UIKit_InitModes(SDL_VideoDevice *_this);
#اگر_تعریف_نشده SDL_PLATFORM_VISIONOS
خارجي bool UIKit_جمع_کن_Display(UIScreen *uiscreen, bool send_event);
خارجي فراغ UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#پایان_اگر
خارجي bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool UIKit_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
خارجي فراغ UIKit_QuitModes(SDL_VideoDevice *_this);
خارجي bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#اگر_تعریف_شده SDL_PLATFORM_VISIONOS
#تعریف_کن SDL_XR_SCREENWIDTH 1280
#تعریف_کن SDL_XR_SCREENHEIGHT 720
#پایان_اگر

#پایان_اگر // SDL_uikitmodes_h_
