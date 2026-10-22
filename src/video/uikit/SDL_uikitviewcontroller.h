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
#अन्तर्भाव "SDL_internal.h"

#import <UIKit/UIKit.h>

#अन्तर्भाव "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#अण्णहा
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#अण्णहा
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (शून्य)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (शून्य)setAnimationCallback:(पूर्णाङ्क)interval
                    callback:(शून्य (*)(शून्य *))callback
               callbackParam:(शून्य *)callbackParam;

- (शून्य)startAnimation;
- (शून्य)stopAnimation;

- (शून्य)doLoop:(CADisplayLink *)sender;

- (शून्य)loadView;
- (शून्य)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (शून्य)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) पूर्णाङ्क homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_निवेशः;
- (bool)stop_Text_निवेशः;
- (शून्य)initKeyboard;
- (शून्य)deinitKeyboard;

- (शून्य)keyboardWillShow:(NSNotification *)notification;
- (शून्य)keyboardDidShow:(NSNotification *)notification;
- (शून्य)keyboardWillHide:(NSNotification *)notification;
- (शून्य)keyboardDidHide:(NSNotification *)notification;

- (शून्य)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_निवेशः_Rect;
@property(nonatomic, assign) पूर्णाङ्क keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window);
शून्य UIKit_Set_Text_निवेशः_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
