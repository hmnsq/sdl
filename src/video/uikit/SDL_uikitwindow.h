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
#నిర్వచితం_కాకపోతే SDL_uikitwindow_h_
#నిర్వచించు SDL_uikitwindow_h_

#అన్తర్భావ "../SDL_sysvideo.h"
#import "SDL_uikitvideo.h"
#import "SDL_uikitview.h"
#import "SDL_uikitviewcontroller.h"

బాహ్య bool UIKit_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య UIKit_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య SDL_Fullscreen_ఫలితం UIKit_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య UIKit_Update_సూచిక_తాళం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య UIKit_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h);

బాహ్య NSUInteger UIKit_GetSupportedOrientations(SDL_కిటికీ *కిటికీ);

#నిర్వచించు SDL_METALVIEW_ట్యాగ్ 255

@class UIWindow;

@interface SDL_UIKit_కిటికీ_దత్తాంశం : NSObject

@property(nonatomic, strong) UIWindow *uiwindow;
@property(nonatomic, strong) SDL_uikitviewcontroller *viewcontroller;

// Array of SDL_uikitviews owned by this window.
@property(nonatomic, copy) NSMutableArray *views;

#నిర్వచితమైతే SDL_PLATFORM_VISIONOS
// Hosting controller for curved content mode (UIHostingController-based)
@property(nonatomic, strong) id curvedContentHosting;
@property(nonatomic, strong) NSString *settings;
#అయితే_ముగింపు

@చివర

#అయితే_ముగింపు // SDL_uikitwindow_h_
