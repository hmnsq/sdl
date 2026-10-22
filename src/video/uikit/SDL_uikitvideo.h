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
#నిర్వచితం_కాకపోతే SDL_uikitvideo_h_
#నిర్వచించు SDL_uikitvideo_h_

#అన్తర్భావ "../SDL_sysvideo.h"

#నిర్వచితమైతే __OBJC__

#అన్తర్భావ <UIKit/UIKit.h>

@interface SDL_UIKit_Video_దత్తాంశం : NSObject

@property(nonatomic, కేటాయించు) id pasteboardObserver;

@property(nonatomic, కేటాయించు) bool setting_clipboard;

@చివర

#నిర్వచితమైతే SDL_PLATFORM_VISIONOS
బాహ్య CGRect UIKit_Compute_View_చట్రం(SDL_కిటికీ *కిటికీ);
#లేకపోతే
బాహ్య CGRect UIKit_Compute_View_చట్రం(SDL_కిటికీ *కిటికీ, UIScreen *screen);
#అయితే_ముగింపు

బాహ్య API_అందుబాటు(ios(13.0)) UIWindowScene *UIKit_Get_చురుకైన_కిటికీ_Scene(శూన్య);

బాహ్య శూన్య UIKit_సమితి_Game_Controller_Interaction(bool enabled);
బాహ్య శూన్య UIKit_సమితి_View_Game_Controller_Interaction(UIView *view, bool enabled);

#ఒకవేళ !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
బాహ్య UIInterfaceOrientation UIKit_GetInterfaceOrientation(శూన్య);
#అయితే_ముగింపు

#అయితే_ముగింపు // __OBJC__

బాహ్య bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

బాహ్య శూన్య UIKit_ForceUpdateHomeIndicator(శూన్య);

బాహ్య bool UIKit_Is_System_సంస్కరణ_At_కనిష్ఠ(ద్విగుణ సంస్కరణ);

బాహ్య SDL_SystemTheme UIKit_GetSystemTheme(శూన్య);

#అయితే_ముగింపు // SDL_uikitvideo_h_
