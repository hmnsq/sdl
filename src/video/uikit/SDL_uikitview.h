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

#समावेश "../SDL_sysvideo.h"

#अगर !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#अन्यथा
@interface SDL_uikitview : UIView
#पूर्ण_अगर

- (instancetype)initWithFrame:(CGRect)frame;

- (व्योम)setSDLWindow:(SDL_Window *)window;
- (SDL_Window *)getSDLWindow;

#अगर !defined(SDL_PLATFORM_TVOS)
- (व्योम)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.0));

- (UIPointerRegion *)pointerInteraction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_AVAILABLE(ios(13.4));
- (UIPointerStyle *)pointerInteraction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_AVAILABLE(ios(13.4));
- (व्योम)indirectPointerHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.4));
#पूर्ण_अगर

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (व्योम)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (व्योम)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (व्योम)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#अगर !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#पूर्ण_अगर

- (व्योम)safeAreaInsetsDidChange;

@end
