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
#यदि_अपरिभाषितम् SDL_uikitvideo_h_
#परिभाषय SDL_uikitvideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"

#यदि_परिभाषितम् __OBJC__

#अन्तर्भाव <UIKit/UIKit.h>

@interface SDL_UIKit_Video_दत्त : NSObject

@property(nonatomic, नियोजय) id pasteboardObserver;

@property(nonatomic, नियोजय) bool setting_clipboard;

@अन्तः

#यदि_परिभाषितम् SDL_PLATFORM_VISIONOS
बाह्य CGRect UIKit_ComputeViewFrame(SDL_गवाक्षः *गवाक्षः);
#अन्यथा
बाह्य CGRect UIKit_ComputeViewFrame(SDL_गवाक्षः *गवाक्षः, UIScreen *screen);
#यदि_अन्तः

बाह्य API_उपलब्धम्(ios(13.0)) UIWindowScene *UIKit_Get_सक्रिय_गवाक्षः_Scene(शून्य);

बाह्य शून्य UIKit_समुच्चयः_Game_Controller_Interaction(bool enabled);
बाह्य शून्य UIKit_समुच्चयः_View_Game_Controller_Interaction(UIView *view, bool enabled);

#यदि !defined(SDL_PLATFORM_TVOS) && !defined(SDL_PLATFORM_VISIONOS)
बाह्य UIInterfaceOrientation UIKit_GetInterfaceOrientation(शून्य);
#यदि_अन्तः

#यदि_अन्तः // __OBJC__

बाह्य bool UIKit_SuspendScreenSaver(SDL_VideoDevice *_this);

बाह्य शून्य UIKit_ForceUpdateHomeIndicator(शून्य);

बाह्य bool UIKit_Is_System_संस्करणम्_At_न्यूनतमम्(द्विगुण संस्करणम्);

बाह्य SDL_SystemTheme UIKit_GetSystemTheme(शून्य);

#यदि_अन्तः // SDL_uikitvideo_h_
