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
#ضمن "SDL_internal.h"

#import <UIKit/UIKit.h>

#ضمن "../SDL_sysvideo.h"

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#وصف_ڪريو SDLRootViewController GCEventViewController
#وإلا
#وصف_ڪريو SDLRootViewController UIViewController
#جيڪڏهن_پورو

@interface SDLUIText_ميدان : UIText_ميدان
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@پڇاڙي

#جيڪڏهن_وصف_ٿيل SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_ميدان_Delegate>
#وإلا
@interface SDL_uikitviewcontroller : SDLRootViewController
#جيڪڏهن_پورو

@property(nonatomic, سونپيو) SDL_دري *دري;

- (instancetype)initWithSDLWindow:(SDL_دري *)دري_3;

- (فراغ)traitCollectionDidChange:(UITraitCollection *)اڳيون_Trait_Collection;

- (فراغ)سيٽ_Animation_Callback:(صحيح)interval
                    callback:(فراغ (*)(فراغ *))callback
               callbackParam:(فراغ *)callbackParam;

- (فراغ)شروعات_Animation;
- (فراغ)stopAnimation;

- (فراغ)doLoop:(CADisplayLink *)sender;

- (فراغ)ڀريو_View;
- (فراغ)viewDidLayoutSubviews;

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_VISIONOS
- (فراغ)initializeVisionOSCurvedUI;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_حالت_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_ڪنارو)preferred_Screen_ڪنارا_Deferring_System_Gestures;

@property(nonatomic, سونپيو) صحيح homeIndicatorHidden;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_IPHONE_KEYBOARD
- (bool)شروعات_متن_داخلا_2;
- (bool)stop_متن_داخلا;
- (فراغ)initKeyboard;
- (فراغ)deinitKeyboard;

- (فراغ)keyboardWillShow:(NSNotification *)notification;
- (فراغ)keyboardDidShow:(NSNotification *)notification;
- (فراغ)keyboardWillHide:(NSNotification *)notification;
- (فراغ)keyboardDidHide:(NSNotification *)notification;

- (فراغ)updateKeyboard;

@property(nonatomic, سونپيو, getter=is_متن_ميدان_Focused) BOOL متن_ميدان_Focused;
@property(nonatomic, سونپيو) SDL_Rect متن_داخلا_Rect;
@property(nonatomic, سونپيو) صحيح keyboard_اوچائي;
#جيڪڏهن_پورو

@پڇاڙي

#جيڪڏهن_وصف_ٿيل SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
bool UIKit_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري);
فراغ UIKit_سيٽ_متن_داخلا_Properties(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
bool UIKit_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري);
#جيڪڏهن_پورو
