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
#అన్తర్భావ "SDL_internal.h"

#import <UIKit/UIKit.h>

#అన్తర్భావ "../SDL_sysvideo.h"

#నిర్వచితమైతే SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#నిర్వచించు SDLRootViewController GCEventViewController
#లేకపోతే
#నిర్వచించు SDLRootViewController UIViewController
#అయితే_ముగింపు

@interface SDLUIText_క్షేత్రం : UIText_క్షేత్రం
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@చివర

#నిర్వచితమైతే SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_క్షేత్రం_Delegate>
#లేకపోతే
@interface SDL_uikitviewcontroller : SDLRootViewController
#అయితే_ముగింపు

@property(nonatomic, కేటాయించు) SDL_కిటికీ *కిటికీ;

- (instancetype)initWithSDLWindow:(SDL_కిటికీ *)కిటికీ_3;

- (శూన్య)traitCollectionDidChange:(UITraitCollection *)మునుపటి_Trait_Collection;

- (శూన్య)సమితి_Animation_Callback:(పూర్ణాంకం)interval
                    callback:(శూన్య (*)(శూన్య *))callback
               callbackParam:(శూన్య *)callbackParam;

- (శూన్య)ప్రారంభం_Animation;
- (శూన్య)stopAnimation;

- (శూన్య)doLoop:(CADisplayLink *)sender;

- (శూన్య)ఎక్కించు_View;
- (శూన్య)viewDidLayoutSubviews;

#నిర్వచితమైతే SDL_PLATFORM_VISIONOS
- (శూన్య)initializeVisionOSCurvedUI;
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_స్థితి_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_అంచు)preferred_Screen_అంచులు_Deferring_System_Gestures;

@property(nonatomic, కేటాయించు) పూర్ణాంకం homeIndicatorHidden;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_IPHONE_KEYBOARD
- (bool)ప్రారంభం_పాఠ్యం_ఆదానం_2;
- (bool)stop_పాఠ్యం_ఆదానం;
- (శూన్య)initKeyboard;
- (శూన్య)deinitKeyboard;

- (శూన్య)keyboardWillShow:(NSNotification *)notification;
- (శూన్య)keyboardDidShow:(NSNotification *)notification;
- (శూన్య)keyboardWillHide:(NSNotification *)notification;
- (శూన్య)keyboardDidHide:(NSNotification *)notification;

- (శూన్య)updateKeyboard;

@property(nonatomic, కేటాయించు, getter=is_పాఠ్యం_క్షేత్రం_Focused) BOOL పాఠ్యం_క్షేత్రం_Focused;
@property(nonatomic, కేటాయించు) SDL_Rect పాఠ్యం_ఆదానం_Rect;
@property(nonatomic, కేటాయించు) పూర్ణాంకం keyboard_ఎత్తు;
#అయితే_ముగింపు

@చివర

#నిర్వచితమైతే SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
bool UIKit_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
శూన్య UIKit_సమితి_పాఠ్యం_ఆదానం_Properties(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
bool UIKit_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
#అయితే_ముగింపు
