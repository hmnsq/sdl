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
#समावेश "SDL_internal.h"

#import <UIKit/UIKit.h>

#समावेश "../SDL_sysvideo.h"

#अगर_घोषित SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#घोषणा SDLRootViewController GCEventViewController
#अन्यथा
#घोषणा SDLRootViewController UIViewController
#पूर्ण_अगर

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#अगर_घोषित SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#अन्यथा
@interface SDL_uikitviewcontroller : SDLRootViewController
#पूर्ण_अगर

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (व्योम)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (व्योम)setAnimationCallback:(पूर्णांक)interval
                    callback:(व्योम (*)(व्योम *))callback
               callbackParam:(व्योम *)callbackParam;

- (व्योम)startAnimation;
- (व्योम)stopAnimation;

- (व्योम)doLoop:(CADisplayLink *)sender;

- (व्योम)loadView;
- (व्योम)viewDidLayoutSubviews;

#अगर_घोषित SDL_PLATFORM_VISIONOS
- (व्योम)initializeVisionOSCurvedUI;
#पूर्ण_अगर

#अगर_अघोषित SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) पूर्णांक homeIndicatorHidden;
#पूर्ण_अगर

#अगर_घोषित SDL_IPHONE_KEYBOARD
- (bool)start_Text_निवेश;
- (bool)stop_Text_निवेश;
- (व्योम)initKeyboard;
- (व्योम)deinitKeyboard;

- (व्योम)keyboardWillShow:(NSNotification *)notification;
- (व्योम)keyboardDidShow:(NSNotification *)notification;
- (व्योम)keyboardWillHide:(NSNotification *)notification;
- (व्योम)keyboardDidHide:(NSNotification *)notification;

- (व्योम)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_निवेश_Rect;
@property(nonatomic, assign) पूर्णांक keyboardHeight;
#पूर्ण_अगर

@end

#अगर_घोषित SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window);
व्योम UIKit_Set_Text_निवेश_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window);
#पूर्ण_अगर
