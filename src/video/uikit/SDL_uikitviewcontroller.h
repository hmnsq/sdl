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
#شامل "SDL_internal.h"

#import <UIKit/UIKit.h>

#شامل "../SDL_sysvideo.h"

#اگر_تعریف_شدہ SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#تعریف_کرو SDLRootViewController GCEventViewController
#ورنہ
#تعریف_کرو SDLRootViewController UIViewController
#اگر_ختم

@interface SDLUIText_میدان : UIText_میدان
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@انتہا

#اگر_تعریف_شدہ SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_میدان_Delegate>
#ورنہ
@interface SDL_uikitviewcontroller : SDLRootViewController
#اگر_ختم

@property(nonatomic, تفویض) SDL_کھڑکی *کھڑکی;

- (instancetype)initWithSDLWindow:(SDL_کھڑکی *)کھڑکی_3;

- (خالی)traitCollectionDidChange:(UITraitCollection *)پچھلا_Trait_Collection;

- (خالی)سیٹ_Animation_Callback:(صحیح)interval
                    callback:(خالی (*)(خالی *))callback
               callbackParam:(خالی *)callbackParam;

- (خالی)آغاز_Animation;
- (خالی)stopAnimation;

- (خالی)doLoop:(CADisplayLink *)sender;

- (خالی)بھرو_View;
- (خالی)viewDidLayoutSubviews;

#اگر_تعریف_شدہ SDL_PLATFORM_VISIONOS
- (خالی)initializeVisionOSCurvedUI;
#اگر_ختم

#اگر_غیر_تعریف_شدہ SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_حالت_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_کنارہ)preferred_Screen_کنارے_Deferring_System_Gestures;

@property(nonatomic, تفویض) صحیح homeIndicatorHidden;
#اگر_ختم

#اگر_تعریف_شدہ SDL_IPHONE_KEYBOARD
- (bool)آغاز_متن_داخلہ_2;
- (bool)stop_متن_داخلہ;
- (خالی)initKeyboard;
- (خالی)deinitKeyboard;

- (خالی)keyboardWillShow:(NSNotification *)notification;
- (خالی)keyboardDidShow:(NSNotification *)notification;
- (خالی)keyboardWillHide:(NSNotification *)notification;
- (خالی)keyboardDidHide:(NSNotification *)notification;

- (خالی)updateKeyboard;

@property(nonatomic, تفویض, getter=is_متن_میدان_Focused) BOOL متن_میدان_Focused;
@property(nonatomic, تفویض) SDL_Rect متن_داخلہ_Rect;
@property(nonatomic, تفویض) صحیح keyboard_اونچائی;
#اگر_ختم

@انتہا

#اگر_تعریف_شدہ SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
bool UIKit_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خالی UIKit_سیٹ_متن_داخلہ_Properties(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
bool UIKit_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
#اگر_ختم
