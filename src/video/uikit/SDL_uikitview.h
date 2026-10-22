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

#അന്തര്ഭാവ "../SDL_sysvideo.h"

#എങ്കിൽ !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#അല്ലെങ്കിൽ
@interface SDL_uikitview : UIView
#endif

- (instancetype)initWithFrame:(CGRect)frame;

- (ശൂന്യം)setSDLWindow:(SDL_Window *)window;
- (SDL_Window *)getSDLWindow;

#എങ്കിൽ !defined(SDL_PLATFORM_TVOS)
- (ശൂന്യം)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.0));

- (UIPointerRegion *)pointerInteraction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_AVAILABLE(ios(13.4));
- (UIPointerStyle *)pointerInteraction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_AVAILABLE(ios(13.4));
- (ശൂന്യം)indirectPointerHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.4));
#endif

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (ശൂന്യം)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (ശൂന്യം)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (ശൂന്യം)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#എങ്കിൽ !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#endif

- (ശൂന്യം)safeAreaInsetsDidChange;

@end
