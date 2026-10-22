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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#import <UIKit/UIKit.h>

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#ଅନ୍ୟଥା
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#ଅନ୍ୟଥା
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (ଶୂନ୍ୟ)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (ଶୂନ୍ୟ)setAnimationCallback:(ପୂର୍ଣ୍ଣସଂଖ୍ୟା)interval
                    callback:(ଶୂନ୍ୟ (*)(ଶୂନ୍ୟ *))callback
               callbackParam:(ଶୂନ୍ୟ *)callbackParam;

- (ଶୂନ୍ୟ)startAnimation;
- (ଶୂନ୍ୟ)stopAnimation;

- (ଶୂନ୍ୟ)doLoop:(CADisplayLink *)sender;

- (ଶୂନ୍ୟ)loadView;
- (ଶୂନ୍ୟ)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (ଶୂନ୍ୟ)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) ପୂର୍ଣ୍ଣସଂଖ୍ୟା homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_ନିବେଶ;
- (bool)stop_Text_ନିବେଶ;
- (ଶୂନ୍ୟ)initKeyboard;
- (ଶୂନ୍ୟ)deinitKeyboard;

- (ଶୂନ୍ୟ)keyboardWillShow:(NSNotification *)notification;
- (ଶୂନ୍ୟ)keyboardDidShow:(NSNotification *)notification;
- (ଶୂନ୍ୟ)keyboardWillHide:(NSNotification *)notification;
- (ଶୂନ୍ୟ)keyboardDidHide:(NSNotification *)notification;

- (ଶୂନ୍ୟ)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_ନିବେଶ_Rect;
@property(nonatomic, assign) ପୂର୍ଣ୍ଣସଂଖ୍ୟା keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window);
ଶୂନ୍ୟ UIKit_Set_Text_ନିବେଶ_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_ନିବେଶ_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
