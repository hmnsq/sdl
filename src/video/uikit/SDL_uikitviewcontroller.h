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
#அந்தர்பாவ "SDL_internal.h"

#import <UIKit/UIKit.h>

#அந்தர்பாவ "../SDL_sysvideo.h"

#ifdef SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#define SDLRootViewController GCEventViewController
#இல்லையெனில்
#define SDLRootViewController UIViewController
#endif

@interface SDLUITextField : UITextField
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@end

#ifdef SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UITextFieldDelegate>
#இல்லையெனில்
@interface SDL_uikitviewcontroller : SDLRootViewController
#endif

@property(nonatomic, assign) SDL_Window *window;

- (instancetype)initWithSDLWindow:(SDL_Window *)_window;

- (வெறுமை)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (வெறுமை)setAnimationCallback:(முழு)interval
                    callback:(வெறுமை (*)(வெறுமை *))callback
               callbackParam:(வெறுமை *)callbackParam;

- (வெறுமை)startAnimation;
- (வெறுமை)stopAnimation;

- (வெறுமை)doLoop:(CADisplayLink *)sender;

- (வெறுமை)loadView;
- (வெறுமை)viewDidLayoutSubviews;

#ifdef SDL_PLATFORM_VISIONOS
- (வெறுமை)initializeVisionOSCurvedUI;
#endif

#ifndef SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefersStatusBarHidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures;

@property(nonatomic, assign) முழு homeIndicatorHidden;
#endif

#ifdef SDL_IPHONE_KEYBOARD
- (bool)start_Text_உள்ளீடு;
- (bool)stop_Text_உள்ளீடு;
- (வெறுமை)initKeyboard;
- (வெறுமை)deinitKeyboard;

- (வெறுமை)keyboardWillShow:(NSNotification *)notification;
- (வெறுமை)keyboardDidShow:(NSNotification *)notification;
- (வெறுமை)keyboardWillHide:(NSNotification *)notification;
- (வெறுமை)keyboardDidHide:(NSNotification *)notification;

- (வெறுமை)updateKeyboard;

@property(nonatomic, assign, getter=isTextFieldFocused) BOOL textFieldFocused;
@property(nonatomic, assign) SDL_Rect text_உள்ளீடு_Rect;
@property(nonatomic, assign) முழு keyboardHeight;
#endif

@end

#ifdef SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Stop_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window);
வெறுமை UIKit_Set_Text_உள்ளீடு_Properties(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
bool UIKit_Update_Text_உள்ளீடு_Area(SDL_VideoDevice *_this, SDL_Window *window);
#endif
