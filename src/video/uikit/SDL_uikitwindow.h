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
#अगर_अघोषित SDL_uikitwindow_h_
#घोषणा SDL_uikitwindow_h_

#समावेश "../SDL_sysvideo.h"
#import "SDL_uikitvideo.h"
#import "SDL_uikitview.h"
#import "SDL_uikitviewcontroller.h"

बाह्य bool UIKit_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम UIKit_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य SDL_Fullscreen_परिणाम UIKit_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य व्योम UIKit_UpdatePointerLock(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम UIKit_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h);

बाह्य NSUInteger UIKit_GetSupportedOrientations(SDL_Window *window);

#घोषणा SDL_METALVIEW_TAG 255

@class UIWindow;

@interface SDL_UIKit_Window_तथ्य : NSObject

@property(nonatomic, strong) UIWindow *uiwindow;
@property(nonatomic, strong) SDL_uikitviewcontroller *viewcontroller;

// Array of SDL_uikitviews owned by this window.
@property(nonatomic, copy) NSMutableArray *views;

#अगर_घोषित SDL_PLATFORM_VISIONOS
// Hosting controller for curved content mode (UIHostingController-based)
@property(nonatomic, strong) id curvedContentHosting;
@property(nonatomic, strong) NSString *settings;
#पूर्ण_अगर

@end

#पूर्ण_अगर // SDL_uikitwindow_h_
