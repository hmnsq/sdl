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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_uikitmodes_h_
#परिभाषय SDL_uikitmodes_h_

#अन्तर्भाव "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_दत्त : NSObject

#यदि_अपरिभाषितम् SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#यदि_अन्तः

@अन्तः

@interface SDL_UIKit_Display_बहुलकम्_दत्त : NSObject
#यदि_अपरिभाषितम् SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreen_बहुलकम् *uiscreenmode;
#यदि_अन्तः

@अन्तः

#यदि_अपरिभाषितम् SDL_PLATFORM_VISIONOS
बाह्य bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#यदि_अन्तः

बाह्य bool UIKit_InitModes(SDL_VideoDevice *_this);
#यदि_अपरिभाषितम् SDL_PLATFORM_VISIONOS
बाह्य bool UIKit_सङ्कलय_Display(UIScreen *uiscreen, bool send_event);
बाह्य शून्य UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#यदि_अन्तः
बाह्य bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool UIKit_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य UIKit_QuitModes(SDL_VideoDevice *_this);
बाह्य bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#यदि_परिभाषितम् SDL_PLATFORM_VISIONOS
#परिभाषय SDL_XR_SCREENWIDTH 1280
#परिभाषय SDL_XR_SCREENHEIGHT 720
#यदि_अन्तः

#यदि_अन्तः // SDL_uikitmodes_h_
