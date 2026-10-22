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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_uikitpen_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_uikitpen_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_uikitvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_uikitwindow.h"

ਬਾਹਰੀ bool UIKit_InitPen(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ UIKit_HandlePenMotion(SDL_uikitview *view, UITouch *pencil);
ਬਾਹਰੀ ਖਾਲੀ UIKit_HandlePenPress(SDL_uikitview *view, UITouch *pencil);
ਬਾਹਰੀ ਖਾਲੀ UIKit_HandlePenRelease(SDL_uikitview *view, UITouch *pencil);

#ਜੇ !defined(SDL_PLATFORM_TVOS)
ਬਾਹਰੀ ਖਾਲੀ UIKit_HandlePenHover(SDL_uikitview *view, UIHoverGestureRecognizer *recognizer) API_ਉਪਲਬਧ(ios(13.0));
#ਜੇ_ਅੰਤ

ਬਾਹਰੀ ਖਾਲੀ UIKit_QuitPen(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_uikitpen_h_
