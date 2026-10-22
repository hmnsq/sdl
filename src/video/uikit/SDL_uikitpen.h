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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_uikitpen_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_uikitpen_h_

#ಅನ್ತರ್ಭಾವ "SDL_uikitvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_uikitwindow.h"

ಬಾಹ್ಯ bool UIKit_InitPen(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_HandlePenMotion(SDL_uikitview *view, UITouch *pencil);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_HandlePenPress(SDL_uikitview *view, UITouch *pencil);
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_HandlePenRelease(SDL_uikitview *view, UITouch *pencil);

#ಆದರೆ !defined(SDL_PLATFORM_TVOS)
ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_HandlePenHover(SDL_uikitview *view, UIHoverGestureRecognizer *recognizer) API_ಲಭ್ಯ(ios(13.0));
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ ಶೂನ್ಯ UIKit_QuitPen(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_uikitpen_h_
