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

#جے_تعریف_شدہ SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#تعریف_کرو SDLRootViewController GCEventViewController
#وإلا
#تعریف_کرو SDLRootViewController UIViewController
#جے_انت

@interface SDLUIText_میدان : UIText_میدان
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@سرا

#جے_تعریف_شدہ SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_میدان_Delegate>
#وإلا
@interface SDL_uikitviewcontroller : SDLRootViewController
#جے_انت

@property(nonatomic, سونپو) SDL_کھڑکی *کھڑکی;

- (instancetype)initWithSDLWindow:(SDL_کھڑکی *)کھڑکی_3;

- (فراغ)traitCollectionDidChange:(UITraitCollection *)پچھلا_Trait_Collection;

- (فراغ)سیٹ_Animation_Callback:(صحيح)interval
                    callback:(فراغ (*)(فراغ *))callback
               callbackParam:(فراغ *)callbackParam;

- (فراغ)شروع_Animation;
- (فراغ)stopAnimation;

- (فراغ)doLoop:(CADisplayLink *)sender;

- (فراغ)لدو_View;
- (فراغ)viewDidLayoutSubviews;

#جے_تعریف_شدہ SDL_PLATFORM_VISIONOS
- (فراغ)initializeVisionOSCurvedUI;
#جے_انت

#جے_بنا_تعریف SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_حالت_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_کنارا)preferred_Screen_کنارے_Deferring_System_Gestures;

@property(nonatomic, سونپو) صحيح homeIndicatorHidden;
#جے_انت

#جے_تعریف_شدہ SDL_IPHONE_KEYBOARD
- (bool)شروع_متن_داخلہ_2;
- (bool)stop_متن_داخلہ;
- (فراغ)initKeyboard;
- (فراغ)deinitKeyboard;

- (فراغ)keyboardWillShow:(NSNotification *)notification;
- (فراغ)keyboardDidShow:(NSNotification *)notification;
- (فراغ)keyboardWillHide:(NSNotification *)notification;
- (فراغ)keyboardDidHide:(NSNotification *)notification;

- (فراغ)updateKeyboard;

@property(nonatomic, سونپو, getter=is_متن_میدان_Focused) BOOL متن_میدان_Focused;
@property(nonatomic, سونپو) SDL_Rect متن_داخلہ_Rect;
@property(nonatomic, سونپو) صحيح keyboard_اچائی;
#جے_انت

@سرا

#جے_تعریف_شدہ SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_شروع_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
bool UIKit_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
فراغ UIKit_سیٹ_متن_داخلہ_Properties(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
bool UIKit_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
#جے_انت
