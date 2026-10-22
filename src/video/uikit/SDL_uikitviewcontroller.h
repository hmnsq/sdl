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

#که_تعریف_شوی SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#تعریف_کړه SDLRootViewController GCEventViewController
#وإلا
#تعریف_کړه SDLRootViewController UIViewController
#د_که_پای

@interface SDLUIText_ډګر : UIText_ډګر
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@پای_ټکی

#که_تعریف_شوی SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_ډګر_Delegate>
#وإلا
@interface SDL_uikitviewcontroller : SDLRootViewController
#د_که_پای

@property(nonatomic, ټاکل) SDL_کړکۍ *کړکۍ;

- (instancetype)initWithSDLWindow:(SDL_کړکۍ *)کړکۍ_3;

- (فراغ)traitCollectionDidChange:(UITraitCollection *)پخوانی_Trait_Collection;

- (فراغ)سېټ_Animation_Callback:(صحيح)interval
                    callback:(فراغ (*)(فراغ *))callback
               callbackParam:(فراغ *)callbackParam;

- (فراغ)پیل_Animation;
- (فراغ)stopAnimation;

- (فراغ)doLoop:(CADisplayLink *)sender;

- (فراغ)بارول_View;
- (فراغ)viewDidLayoutSubviews;

#که_تعریف_شوی SDL_PLATFORM_VISIONOS
- (فراغ)initializeVisionOSCurvedUI;
#د_که_پای

#که_نه_تعریف_شوی SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_حالت_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_څنډه)preferred_Screen_څنډې_Deferring_System_Gestures;

@property(nonatomic, ټاکل) صحيح homeIndicatorHidden;
#د_که_پای

#که_تعریف_شوی SDL_IPHONE_KEYBOARD
- (bool)پیل_متن_ننوت_2;
- (bool)stop_متن_ننوت;
- (فراغ)initKeyboard;
- (فراغ)deinitKeyboard;

- (فراغ)keyboardWillShow:(NSNotification *)notification;
- (فراغ)keyboardDidShow:(NSNotification *)notification;
- (فراغ)keyboardWillHide:(NSNotification *)notification;
- (فراغ)keyboardDidHide:(NSNotification *)notification;

- (فراغ)updateKeyboard;

@property(nonatomic, ټاکل, getter=is_متن_ډګر_Focused) BOOL متن_ډګر_Focused;
@property(nonatomic, ټاکل) SDL_Rect متن_ننوت_Rect;
@property(nonatomic, ټاکل) صحيح keyboard_لوړوالی;
#د_که_پای

@پای_ټکی

#که_تعریف_شوی SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_پیل_متن_ننوت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
bool UIKit_Stop_متن_ننوت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
فراغ UIKit_سېټ_متن_ننوت_Properties(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
bool UIKit_Update_متن_ننوت_Area(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
#د_که_پای
