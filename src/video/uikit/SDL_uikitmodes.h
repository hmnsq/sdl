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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_uikitmodes_h_
#నిర్వచించు SDL_uikitmodes_h_

#అన్తర్భావ "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_దత్తాంశం : NSObject

#నిర్వచితం_కాకపోతే SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#అయితే_ముగింపు

@చివర

@interface SDL_UIKit_Display_బహుళకం_దత్తాంశం : NSObject
#నిర్వచితం_కాకపోతే SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreen_బహుళకం *uiscreenmode;
#అయితే_ముగింపు

@చివర

#నిర్వచితం_కాకపోతే SDL_PLATFORM_VISIONOS
బాహ్య bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#అయితే_ముగింపు

బాహ్య bool UIKit_InitModes(SDL_VideoDevice *_this);
#నిర్వచితం_కాకపోతే SDL_PLATFORM_VISIONOS
బాహ్య bool UIKit_కూడు_Display(UIScreen *uiscreen, bool send_event);
బాహ్య శూన్య UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#అయితే_ముగింపు
బాహ్య bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool UIKit_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య UIKit_QuitModes(SDL_VideoDevice *_this);
బాహ్య bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#నిర్వచితమైతే SDL_PLATFORM_VISIONOS
#నిర్వచించు SDL_XR_SCREENWIDTH 1280
#నిర్వచించు SDL_XR_SCREENHEIGHT 720
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_uikitmodes_h_
