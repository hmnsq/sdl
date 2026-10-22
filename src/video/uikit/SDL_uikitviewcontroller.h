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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#import <UIKit/UIKit.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDLRootViewController GCEventViewController
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDLRootViewController UIViewController
#ਜੇ_ਅੰਤ

@interface SDLUIText_ਖੇਤਰ : UIText_ਖੇਤਰ
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@ਸਿਰਾ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_ਖੇਤਰ_Delegate>
#ਨਹੀਂਤਾਂ
@interface SDL_uikitviewcontroller : SDLRootViewController
#ਜੇ_ਅੰਤ

@property(nonatomic, ਸੌਂਪੋ) SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

- (instancetype)initWithSDLWindow:(SDL_ਖਿੜਕੀ *)ਖਿੜਕੀ_3;

- (ਖਾਲੀ)traitCollectionDidChange:(UITraitCollection *)ਪਿਛਲਾ_Trait_Collection;

- (ਖਾਲੀ)ਸੈੱਟ_Animation_Callback:(ਪੂਰਨ)interval
                    callback:(ਖਾਲੀ (*)(ਖਾਲੀ *))callback
               callbackParam:(ਖਾਲੀ *)callbackParam;

- (ਖਾਲੀ)ਸ਼ੁਰੂ_Animation;
- (ਖਾਲੀ)stopAnimation;

- (ਖਾਲੀ)doLoop:(CADisplayLink *)sender;

- (ਖਾਲੀ)ਲੱਦੋ_View;
- (ਖਾਲੀ)viewDidLayoutSubviews;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_VISIONOS
- (ਖਾਲੀ)initializeVisionOSCurvedUI;
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_ਸਥਿਤੀ_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_ਕਿਨਾਰਾ)preferred_Screen_ਕਿਨਾਰੇ_Deferring_System_Gestures;

@property(nonatomic, ਸੌਂਪੋ) ਪੂਰਨ homeIndicatorHidden;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_IPHONE_KEYBOARD
- (bool)ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼_2;
- (bool)stop_ਪਾਠ_ਨਿਵੇਸ਼;
- (ਖਾਲੀ)initKeyboard;
- (ਖਾਲੀ)deinitKeyboard;

- (ਖਾਲੀ)keyboardWillShow:(NSNotification *)notification;
- (ਖਾਲੀ)keyboardDidShow:(NSNotification *)notification;
- (ਖਾਲੀ)keyboardWillHide:(NSNotification *)notification;
- (ਖਾਲੀ)keyboardDidHide:(NSNotification *)notification;

- (ਖਾਲੀ)updateKeyboard;

@property(nonatomic, ਸੌਂਪੋ, getter=is_ਪਾਠ_ਖੇਤਰ_Focused) BOOL ਪਾਠ_ਖੇਤਰ_Focused;
@property(nonatomic, ਸੌਂਪੋ) SDL_Rect ਪਾਠ_ਨਿਵੇਸ਼_Rect;
@property(nonatomic, ਸੌਂਪੋ) ਪੂਰਨ keyboard_ਉਚਾਈ;
#ਜੇ_ਅੰਤ

@ਸਿਰਾ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
bool UIKit_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਖਾਲੀ UIKit_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Properties(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
bool UIKit_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
