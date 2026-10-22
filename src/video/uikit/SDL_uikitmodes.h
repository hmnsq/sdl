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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_uikitmodes_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_uikitmodes_h_

#ಅನ್ತರ್ಭಾವ "SDL_uikitvideo.h"

@interface SDL_UIKit_Display_ದತ್ತಾಂಶ : NSObject

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_VISIONOS
- (instancetype)initWithScreen:(UIScreen *)screen;
@property(nonatomic, strong) UIScreen *uiscreen;
#ಆದರೆ_ಅಂತ್ಯ

@ಕೊನೆ

@interface SDL_UIKit_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ : NSObject
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_VISIONOS
@property(nonatomic, strong) UIScreen_ಬಹುಲಕ *uiscreenmode;
#ಆದರೆ_ಅಂತ್ಯ

@ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_VISIONOS
ಬಾಹ್ಯ bool UIKit_IsDisplayLandscape(UIScreen *uiscreen);
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ bool UIKit_InitModes(SDL_VideoDevice *_this);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_VISIONOS
ಬಾಹ್ಯ bool UIKit_ಕೂಡಿಸು_Display(UIScreen *uiscreen, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_DelDisplay(UIScreen *uiscreen, bool send_event);
#ಆದರೆ_ಅಂತ್ಯ
ಬಾಹ್ಯ bool UIKit_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool UIKit_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_QuitModes(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool UIKit_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

// because visionOS does not have a screen
// we create a fake display to maintain compatibility.
// By default, a window measures 1280x720 pt.
// https://developer.apple.com/design/human-interface-guidelines/windows#visionOS
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_VISIONOS
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XR_SCREENWIDTH 1280
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XR_SCREENHEIGHT 720
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_uikitmodes_h_
