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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_uikitmodes_h_
#घोषणा SDL_uikitmodes_h_

#समावेश "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_तथ्य : NSObject

#अगर_अघोषित SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#पूर्ण_अगर

@end

@interface SDL_UIKit_Display_Mode_तथ्य : NSObject
#अगर_अघोषित SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreenMode *uiscreenmode;
#पूर्ण_अगर

@end

#अगर_अघोषित SDL_PLATFORM_VISIONOS
बाह्य bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#पूर्ण_अगर

बाह्य bool UIKit_InitModes(SDL_VideoDevice *_this);
#अगर_अघोषित SDL_PLATFORM_VISIONOS
बाह्य bool UIKit_AddDisplay(UIScreen *uiscreen, bool send_event);
बाह्य व्योम UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#पूर्ण_अगर
बाह्य bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool UIKit_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य व्योम UIKit_QuitModes(SDL_VideoDevice *_this);
बाह्य bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#अगर_घोषित SDL_PLATFORM_VISIONOS
#घोषणा SDL_XR_SCREENWIDTH 1280
#घोषणा SDL_XR_SCREENHEIGHT 720
#पूर्ण_अगर

#पूर्ण_अगर // SDL_uikitmodes_h_
