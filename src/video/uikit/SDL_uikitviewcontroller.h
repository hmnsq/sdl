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
#അന്തര്ഭാവ "SDL_internal.h"

#import <UIKit/UIKit.h>

#അന്തര്ഭാവ "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#അല്ലെങ്കിൽ
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#അല്ലെങ്കിൽ
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (ശൂന്യം)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (ശൂന്യം)setAnimationCallback:(പൂർണ്ണസംഖ്യ)interval
                    callback:(ശൂന്യം (*)(ശൂന്യം *))callback
               callbackParam:(ശൂന്യം *)callbackParam;

- (ശൂന്യം)startAnimation;
- (ശൂന്യം)stopAnimation;

- (ശൂന്യം)doLoop:(CADisplayLink *)sender;

- (ശൂന്യം)loadView;
- (ശൂന്യം)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (ശൂന്യം)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) പൂർണ്ണസംഖ്യ homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_നിവേശം;
- (bool)stop_Text_നിവേശം;
- (ശൂന്യം)initKeyboard;
- (ശൂന്യം)deinitKeyboard;

- (ശൂന്യം)keyboardWillShow:(NSNotification *)notification;
- (ശൂന്യം)keyboardDidShow:(NSNotification *)notification;
- (ശൂന്യം)keyboardWillHide:(NSNotification *)notification;
- (ശൂന്യം)keyboardDidHide:(NSNotification *)notification;

- (ശൂന്യം)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_നിവേശം_Rect;
@property(nonatomic, assign) പൂർണ്ണസംഖ്യ keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window);
ശൂന്യം UIKit_Set_Text_നിവേശം_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_നിവേശം_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
