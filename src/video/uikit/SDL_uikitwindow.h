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
#यदि_अपरिभाषितम् SDL_uikitwindow_h_
#परिभाषय SDL_uikitwindow_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#import "SDL_uikitvideo.h"
#import "SDL_uikitview.h"
#import "SDL_uikitviewcontroller.h"

बाह्य bool UIKit_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य UIKit_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य SDL_Fullscreen_परिणाम UIKit_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य UIKit_Update_Pointer_तालकम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य UIKit_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h);

बाह्य NSUInteger UIKit_GetSupportedOrientations(SDL_गवाक्षः *गवाक्षः);

#परिभाषय SDL_METALVIEW_चिह्नकम् 255

@class UIWindow;

@interface SDL_UIKit_गवाक्षः_दत्त : NSObject

@property(nonatomic, strong) UIWindow *uiwindow;
@property(nonatomic, strong) SDL_uikitviewcontroller *viewcontroller;

// Array of SDL_uikitviews owned by this window.
@property(nonatomic, copy) NSMutableArray *views;

#यदि_परिभाषितम् SDL_PLATFORM_VISIONOS
// Hosting controller for curved content mode (UIHostingController-based)
@property(nonatomic, strong) id curvedContentHosting;
@property(nonatomic, strong) NSString *settings;
#यदि_अन्तः

@अन्तः

#यदि_अन्तः // SDL_uikitwindow_h_
