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

#यदि_परिभाषितम् SDL_PLATFORM_TVOS
#import <GameController/GameController.h>
#परिभाषय SDLRootViewController GCEventViewController
#अन्यथा
#परिभाषय SDLRootViewController UIViewController
#यदि_अन्तः

@interface SDLUIText_क्षेत्रम् : UIText_क्षेत्रम्
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender;
@अन्तः

#यदि_परिभाषितम् SDL_IPHONE_KEYBOARD
@interface SDL_uikitviewcontroller : SDLRootViewController <UIText_क्षेत्रम्_Delegate>
#अन्यथा
@interface SDL_uikitviewcontroller : SDLRootViewController
#यदि_अन्तः

@property(nonatomic, नियोजय) SDL_गवाक्षः *गवाक्षः;

- (instancetype)initWithSDLWindow:(SDL_गवाक्षः *)गवाक्षः_3;

- (शून्य)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

- (शून्य)समुच्चयः_Animation_Callback:(पूर्णाङ्क)interval
                    callback:(शून्य (*)(शून्य *))callback
               callbackParam:(शून्य *)callbackParam;

- (शून्य)startAnimation;
- (शून्य)stopAnimation;

- (शून्य)doLoop:(CADisplayLink *)sender;

- (शून्य)आरोपय_View;
- (शून्य)viewDidLayoutSubviews;

#यदि_परिभाषितम् SDL_PLATFORM_VISIONOS
- (शून्य)initializeVisionOSCurvedUI;
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_PLATFORM_TVOS
- (NSUInteger)supportedInterfaceOrientations;
- (BOOL)prefers_स्थितिः_Bar_Hidden;
- (BOOL)prefersHomeIndicatorAutoHidden;
- (UIRectEdge)preferred_Screen_धाराः_Deferring_System_Gestures;

@property(nonatomic, नियोजय) पूर्णाङ्क homeIndicatorHidden;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_IPHONE_KEYBOARD
- (bool)start_Text_निवेशः;
- (bool)stop_Text_निवेशः;
- (शून्य)initKeyboard;
- (शून्य)deinitKeyboard;

- (शून्य)keyboardWillShow:(NSNotification *)notification;
- (शून्य)keyboardDidShow:(NSNotification *)notification;
- (शून्य)keyboardWillHide:(NSNotification *)notification;
- (शून्य)keyboardDidHide:(NSNotification *)notification;

- (शून्य)updateKeyboard;

@property(nonatomic, नियोजय, getter=is_Text_क्षेत्रम्_Focused) BOOL text_क्षेत्रम्_Focused;
@property(nonatomic, नियोजय) SDL_Rect text_निवेशः_Rect;
@property(nonatomic, नियोजय) पूर्णाङ्क keyboardHeight;
#यदि_अन्तः

@अन्तः

#यदि_परिभाषितम् SDL_IPHONE_KEYBOARD
bool UIKit_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
bool UIKit_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);
bool UIKit_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य UIKit_समुच्चयः_Text_निवेशः_Properties(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);
bool UIKit_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
#यदि_अन्तः
