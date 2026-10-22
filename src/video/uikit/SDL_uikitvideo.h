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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_uikitvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_uikitvideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__

#ಅನ್ತರ್ಭಾವ <UIKit/UIKit.h>

@interface SDL_UIKit_Video_ದತ್ತಾಂಶ : NSObject

@property(nonatomic, ನಿಯೋಜಿಸು) id pasteboardObserver;

@property(nonatomic, ನಿಯೋಜಿಸು) bool setting_clipboard;

@ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_VISIONOS
ಬಾಹ್ಯ CGRect UIKit_Compute_View_ಚೌಕಟ್ಟು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ CGRect UIKit_Compute_View_ಚೌಕಟ್ಟು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, UIScreen *screen);
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ API_ಲಭ್ಯ(ios(13.0)) UIWindowScene *UIKit_Get_ಸಕ್ರಿಯ_ಕಿಟಕಿ_Scene(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_ಗಣ_Game_Controller_Interaction(bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_ಗಣ_View_Game_Controller_Interaction(UIView *view, bool enabled);

#ಆದರೆ !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
ಬಾಹ್ಯ UIInterfaceOrientation UIKit_GetInterfaceOrientation(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // __OBJC__

ಬಾಹ್ಯ bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_ForceUpdateHomeIndicator(ಶೂನ್ಯ);

ಬಾಹ್ಯ bool UIKit_Is_System_ಆವೃತ್ತಿ_At_ಕನಿಷ್ಠ(ದ್ವಿಗುಣ ಆವೃತ್ತಿ);

ಬಾಹ್ಯ SDL_SystemTheme UIKit_GetSystemTheme(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_uikitvideo_h_
