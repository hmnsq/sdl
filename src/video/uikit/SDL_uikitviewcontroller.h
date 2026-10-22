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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#import <UIKit/UIKit.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#ವ್ಯಾಖ್ಯಾನಿಸು SDLRootViewController GCEventViewController
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDLRootViewController UIViewController
#ಆದರೆ_ಅಂತ್ಯ

@interface SDLUIText_ಕ್ಷೇತ್ರ : UIText_ಕ್ಷೇತ್ರ
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_ಕ್ಷೇತ್ರ_Delegate>
#ಇಲ್ಲದಿದ್ದರೆ
@interface SDL_uikitviewcontroller : SDLRootViewController
#ಆದರೆ_ಅಂತ್ಯ

@property(nonatomic, ನಿಯೋಜಿಸು) SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

- (instancetype)initWithSDLWindow:(SDL_ಕಿಟಕಿ *)ಕಿಟಕಿ_3;

- (ಶೂನ್ಯ)traitCollectionDidChange:(UITraitCollection *)ಹಿಂದಿನ_Trait_Collection;

- (ಶೂನ್ಯ)ಗಣ_Animation_Callback:(ಪೂರ್ಣಾಂಕ)interval
                    callback:(ಶೂನ್ಯ (*)(ಶೂನ್ಯ *))callback
               callbackParam:(ಶೂನ್ಯ *)callbackParam;

- (ಶೂನ್ಯ)ಆರಂಭ_Animation;
- (ಶೂನ್ಯ)stopAnimation;

- (ಶೂನ್ಯ)doLoop:(CADisplayLink *)sender;

- (ಶೂನ್ಯ)ತುಂಬು_View;
- (ಶೂನ್ಯ)viewDidLayoutSubviews;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_VISIONOS
- (ಶೂನ್ಯ)initializeVisionOSCurvedUI;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_ಸ್ಥಿತಿ_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRect_ಅಂಚು)preferred_Screen_ಅಂಚುಗಳು_Deferring_System_Gestures;

@property(nonatomic, ನಿಯೋಜಿಸು) ಪೂರ್ಣಾಂಕ homeIndicatorHidden;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_IPHONE_KEYBOARD
- (bool)ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು_2;
- (bool)stop_ಪಠ್ಯ_ಒಳಹರಿವು;
- (ಶೂನ್ಯ)initKeyboard;
- (ಶೂನ್ಯ)deinitKeyboard;

- (ಶೂನ್ಯ)keyboardWillShow:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardDidShow:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardWillHide:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardDidHide:(NSNotification *)notification;

- (ಶೂನ್ಯ)updateKeyboard;

@property(nonatomic, ನಿಯೋಜಿಸು, getter=is_ಪಠ್ಯ_ಕ್ಷೇತ್ರ_Focused) BOOL ಪಠ್ಯ_ಕ್ಷೇತ್ರ_Focused;
@property(nonatomic, ನಿಯೋಜಿಸು) SDL_Rect ಪಠ್ಯ_ಒಳಹರಿವು_Rect;
@property(nonatomic, ನಿಯೋಜಿಸು) ಪೂರ್ಣಾಂಕ keyboard_ಎತ್ತರ;
#ಆದರೆ_ಅಂತ್ಯ

@ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
bool UIKit_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ UIKit_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Properties(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
bool UIKit_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
