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

#ضمن "../SDL_sysvideo.h"

#𐡄𐡍 !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#وإلا
@interface SDL_uikitview : UIView
#endif

- (instancetype)initWithFrame:(CGRect)frame;

- (فراغ)setSDLWindow:(SDL_Window *)window;
- (SDL_Window *)getSDLWindow;

#𐡄𐡍 !defined(SDL_PLATFORM_TVOS)
- (فراغ)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.0));

- (UIPointerRegion *)pointerInteraction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_AVAILABLE(ios(13.4));
- (UIPointerStyle *)pointerInteraction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_AVAILABLE(ios(13.4));
- (فراغ)indirectPointerHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.4));
#endif

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (فراغ)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (فراغ)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (فراغ)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#𐡄𐡍 !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#endif

- (فراغ)safeAreaInsetsDidChange;

@end
