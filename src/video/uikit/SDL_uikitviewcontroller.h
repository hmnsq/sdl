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

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#ಅನ್ಯಥಾ
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#ಅನ್ಯಥಾ
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (ಶೂನ್ಯ)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (ಶೂನ್ಯ)setAnimationCallback:(ಪೂರ್ಣಾಙ್ಕ)interval
                    callback:(ಶೂನ್ಯ (*)(ಶೂನ್ಯ *))callback
               callbackParam:(ಶೂನ್ಯ *)callbackParam;

- (ಶೂನ್ಯ)startAnimation;
- (ಶೂನ್ಯ)stopAnimation;

- (ಶೂನ್ಯ)doLoop:(CADisplayLink *)sender;

- (ಶೂನ್ಯ)loadView;
- (ಶೂನ್ಯ)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (ಶೂನ್ಯ)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) ಪೂರ್ಣಾಙ್ಕ homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_ಒಳಹರಿವು;
- (bool)stop_Text_ಒಳಹರಿವು;
- (ಶೂನ್ಯ)initKeyboard;
- (ಶೂನ್ಯ)deinitKeyboard;

- (ಶೂನ್ಯ)keyboardWillShow:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardDidShow:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardWillHide:(NSNotification *)notification;
- (ಶೂನ್ಯ)keyboardDidHide:(NSNotification *)notification;

- (ಶೂನ್ಯ)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_ಒಳಹರಿವು_Rect;
@property(nonatomic, assign) ಪೂರ್ಣಾಙ್ಕ keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window);
ಶೂನ್ಯ UIKit_Set_Text_ಒಳಹರಿವು_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
