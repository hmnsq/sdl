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
#অন্তর্ভাব "SDL_internal.h"

#import <UIKit/UIKit.h>

#অন্তর্ভাব "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#অন্যথা
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#অন্যথা
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (শূন্য)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (শূন্য)setAnimationCallback:(পূর্ণসংখ্যা)interval
                    callback:(শূন্য (*)(শূন্য *))callback
               callbackParam:(শূন্য *)callbackParam;

- (শূন্য)startAnimation;
- (শূন্য)stopAnimation;

- (শূন্য)doLoop:(CADisplayLink *)sender;

- (শূন্য)loadView;
- (শূন্য)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (শূন্য)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) পূর্ণসংখ্যা homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_প্রবেশ;
- (bool)stop_Text_প্রবেশ;
- (শূন্য)initKeyboard;
- (শূন্য)deinitKeyboard;

- (শূন্য)keyboardWillShow:(NSNotification *)notification;
- (শূন্য)keyboardDidShow:(NSNotification *)notification;
- (শূন্য)keyboardWillHide:(NSNotification *)notification;
- (শূন্য)keyboardDidHide:(NSNotification *)notification;

- (শূন্য)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_প্রবেশ_Rect;
@property(nonatomic, assign) পূর্ণসংখ্যা keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window);
শূন্য UIKit_Set_Text_প্রবেশ_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
