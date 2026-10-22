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

#import <UIKit/UIKit.h>

#شامل "../SDL_sysvideo.h"

#اگر !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#ورنہ
@interface SDL_uikitview : UIView
#اگر_ختم

- (instancetype)init_With_چوکھٹا:(CGRect)چوکھٹا;

- (خالی)سیٹ_SDLWindow:(SDL_کھڑکی *)کھڑکی;
- (SDL_کھڑکی *)getSDLWindow;

#اگر !defined(SDL_PLATFORM_TVOS)
- (خالی)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_دستیاب(ios(13.0));

- (UIPointerRegion *)اشارہ_گر_Interaction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_دستیاب(ios(13.4));
- (UIPointerStyle *)اشارہ_گر_Interaction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_دستیاب(ios(13.4));
- (خالی)بالواسطہ_اشارہ_گر_Hovering:(UIHoverGestureRecognizer *)recognizer API_دستیاب(ios(13.4));
#اگر_ختم

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (خالی)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (خالی)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (خالی)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#اگر !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#اگر_ختم

- (خالی)محفوظ_Area_Insets_Did_Change;

@انتہا
