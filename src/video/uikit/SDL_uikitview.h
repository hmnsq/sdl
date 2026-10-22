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

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#ਨਹੀਂਤਾਂ
@interface SDL_uikitview : UIView
#ਜੇ_ਅੰਤ

- (instancetype)init_With_ਚੌਖਟਾ:(CGRect)ਚੌਖਟਾ;

- (ਖਾਲੀ)ਸੈੱਟ_SDLWindow:(SDL_ਖਿੜਕੀ *)ਖਿੜਕੀ;
- (SDL_ਖਿੜਕੀ *)getSDLWindow;

#ਜੇ !defined(SDL_PLATFORM_TVOS)
- (ਖਾਲੀ)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_ਉਪਲਬਧ(ios(13.0));

- (UIPointerRegion *)ਸੂਚਕ_Interaction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_ਉਪਲਬਧ(ios(13.4));
- (UIPointerStyle *)ਸੂਚਕ_Interaction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_ਉਪਲਬਧ(ios(13.4));
- (ਖਾਲੀ)ਅਸਿੱਧਾ_ਸੂਚਕ_Hovering:(UIHoverGestureRecognizer *)recognizer API_ਉਪਲਬਧ(ios(13.4));
#ਜੇ_ਅੰਤ

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (ਖਾਲੀ)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (ਖਾਲੀ)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (ਖਾਲੀ)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#ਜੇ !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#ਜੇ_ਅੰਤ

- (ਖਾਲੀ)ਸੁਰੱਖਿਅਤ_Area_Insets_Did_Change;

@ਸਿਰਾ
