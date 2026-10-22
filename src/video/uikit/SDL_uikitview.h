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

#అన్తర్భావ "../SDL_sysvideo.h"

#ఒకవేళ !defined(SDL_PLATFORM_TVOS)
@interface SDL_uikitview : UIView <UIPointerInteractionDelegate>
#లేకపోతే
@interface SDL_uikitview : UIView
#అయితే_ముగింపు

- (instancetype)init_With_చట్రం:(CGRect)చట్రం;

- (శూన్య)సమితి_SDLWindow:(SDL_కిటికీ *)కిటికీ;
- (SDL_కిటికీ *)getSDLWindow;

#ఒకవేళ !defined(SDL_PLATFORM_TVOS)
- (శూన్య)pencilHovering:(UIHoverGestureRecognizer *)recognizer API_అందుబాటు(ios(13.0));

- (UIPointerRegion *)సూచిక_Interaction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion API_అందుబాటు(ios(13.4));
- (UIPointerStyle *)సూచిక_Interaction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region API_అందుబాటు(ios(13.4));
- (శూన్య)పరోక్ష_సూచిక_Hovering:(UIHoverGestureRecognizer *)recognizer API_అందుబాటు(ios(13.4));
#అయితే_ముగింపు

- (CGPoint)touchLocation:(UITouch *)touch shouldNormalize:(BOOL)normalize;
- (శూన్య)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (శూన్య)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (శూన్య)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
#ఒకవేళ !defined(SDL_PLATFORM_TVOS)
- (IBAction)sdlPinchGesture:(UIPinchGestureRecognizer *)sender;
#అయితే_ముగింపు

- (శూన్య)సురక్షిత_Area_Insets_Did_Change;

@చివర
