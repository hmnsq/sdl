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

#اگر_تعریف_شده SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#تعریف_کن SDLRootViewController GCEventViewController
#وإلا
#تعریف_کن SDLRootViewController UIViewController
#پایان_اگر

@interface SDLUIText_فیلد : UIText_فیلد
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@انتها

#اگر_تعریف_شده SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_فیلد_Delegate>
#وإلا
@interface SDL_uikitviewcontroller : SDLRootViewController
#پایان_اگر

@property(nonatomic, تخصیص_بده) SDL_پنجره *پنجره;

- (instancetype)initWithSDLWindow:(SDL_پنجره *)پنجره_3;

- (فراغ)traitCollectionDidChange:(UITraitCollection *)قبلی_Trait_Collection;

- (فراغ)مجموعه_Animation_Callback:(صحيح)interval
                    callback:(فراغ (*)(فراغ *))callback
               callbackParam:(فراغ *)callbackParam;

- (فراغ)شروع_Animation;
- (فراغ)stopAnimation;

- (فراغ)doLoop:(CADisplayLink *)sender;

- (فراغ)بارگیری_View;
- (فراغ)viewDidLayoutSubviews;

#اگر_تعریف_شده SDL_PLATFORM_VISIONOS
- (فراغ)initializeVisionOSCurvedUI;
#پایان_اگر

#اگر_تعریف_نشده SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_وضعیت_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_یال)preferred_Screen_یالها_Deferring_System_Gestures;

@property(nonatomic, تخصیص_بده) صحيح homeIndicatorHidden;
#پایان_اگر

#اگر_تعریف_شده SDL_IPHONE_KEYBOARD
- (bool)شروع_متن_درون_داد_2;
- (bool)stop_متن_درون_داد;
- (فراغ)initKeyboard;
- (فراغ)deinitKeyboard;

- (فراغ)keyboardWillShow:(NSNotification *)notification;
- (فراغ)keyboardDidShow:(NSNotification *)notification;
- (فراغ)keyboardWillHide:(NSNotification *)notification;
- (فراغ)keyboardDidHide:(NSNotification *)notification;

- (فراغ)updateKeyboard;

@property(nonatomic, تخصیص_بده, getter=is_متن_فیلد_Focused) BOOL متن_فیلد_Focused;
@property(nonatomic, تخصیص_بده) SDL_Rect متن_درون_داد_Rect;
@property(nonatomic, تخصیص_بده) صحيح keyboard_ارتفاع;
#پایان_اگر

@انتها

#اگر_تعریف_شده SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_شروع_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
bool UIKit_Stop_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
فراغ UIKit_مجموعه_متن_درون_داد_Properties(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
bool UIKit_Update_متن_درون_داد_Area(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
#پایان_اگر
