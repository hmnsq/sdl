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

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಆದರೆ !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#ಇಲ್ಲದಿದ್ದರೆ
@interface SDL_uikitview : UIView
#ಆದರೆ_ಅಂತ್ಯ

- (instancetype)init_With_ಚೌಕಟ್ಟು:(CGRect)ಚೌಕಟ್ಟು;

- (ಶೂನ್ಯ)ಗಣ_SDLWindow:(SDL_ಕಿಟಕಿ *)ಕಿಟಕಿ;
- (SDL_ಕಿಟಕಿ *)getSDLWindow;

#ಆದರೆ !defined(SDL_PLATFORM_TVOS)
- (ಶೂನ್ಯ)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_ಲಭ್ಯ(ios(13.0));

- (UIPointerRegion *)ಸೂಚಕ_Interaction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_ಲಭ್ಯ(ios(13.4));
- (UIPointerStyle *)ಸೂಚಕ_Interaction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_ಲಭ್ಯ(ios(13.4));
- (ಶೂನ್ಯ)ಪರೋಕ್ಷ_ಸೂಚಕ_Hovering:(UIHoverGestureRecognizer *)recognizer API_ಲಭ್ಯ(ios(13.4));
#ಆದರೆ_ಅಂತ್ಯ

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (ಶೂನ್ಯ)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (ಶೂನ್ಯ)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (ಶೂನ್ಯ)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#ಆದರೆ !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#ಆದರೆ_ಅಂತ್ಯ

- (ಶೂನ್ಯ)ಸುರಕ್ಷಿತ_Area_Insets_Did_Change;

@ಕೊನೆ
