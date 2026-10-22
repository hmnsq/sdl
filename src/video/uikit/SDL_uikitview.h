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

#અન્તર્ભાવ "../SDL_sysvideo.h"

#જો !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#નહીંતર
@interface SDL_uikitview : UIView
#endif

- (instancetype)initWithFrame:(CGRect)frame;

- (શૂન્ય)setSDLWindow:(SDL_Window *)window;
- (SDL_Window *)getSDLWindow;

#જો !defined(SDL_PLATFORM_TVOS)
- (શૂન્ય)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.0));

- (UIPointerRegion *)pointerInteraction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_AVAILABLE(ios(13.4));
- (UIPointerStyle *)pointerInteraction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_AVAILABLE(ios(13.4));
- (શૂન્ય)indirectPointerHovering:(UIHoverGestureRecognizer *)recognizer API_AVAILABLE(ios(13.4));
#endif

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (શૂન્ય)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (શૂન્ય)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (શૂન્ય)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#જો !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#endif

- (શૂન્ય)safeAreaInsetsDidChange;

@end
