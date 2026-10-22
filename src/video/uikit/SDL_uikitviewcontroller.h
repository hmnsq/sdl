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
#અન્તર્ભાવ "SDL_internal.h"

#import <UIKit/UIKit.h>

#અન્તર્ભાવ "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#નહીંતર
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#નહીંતર
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (શૂન્ય)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (શૂન્ય)setAnimationCallback:(પૂર્ણાંક)interval
                    callback:(શૂન્ય (*)(શૂન્ય *))callback
               callbackParam:(શૂન્ય *)callbackParam;

- (શૂન્ય)startAnimation;
- (શૂન્ય)stopAnimation;

- (શૂન્ય)doLoop:(CADisplayLink *)sender;

- (શૂન્ય)loadView;
- (શૂન્ય)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (શૂન્ય)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) પૂર્ણાંક homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_આગત;
- (bool)stop_Text_આગત;
- (શૂન્ય)initKeyboard;
- (શૂન્ય)deinitKeyboard;

- (શૂન્ય)keyboardWillShow:(NSNotification *)notification;
- (શૂન્ય)keyboardDidShow:(NSNotification *)notification;
- (શૂન્ય)keyboardWillHide:(NSNotification *)notification;
- (શૂન્ય)keyboardDidHide:(NSNotification *)notification;

- (શૂન્ય)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_આગત_Rect;
@property(nonatomic, assign) પૂર્ણાંક keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window);
શૂન્ય UIKit_Set_Text_આગત_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_આગત_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
