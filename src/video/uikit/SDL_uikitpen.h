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

#ifndef SDL_uikitpen_h_
#define SDL_uikitpen_h_

#अन्तर्भाव "SDL_uikitvideo.h"
#अन्तर्भाव "SDL_uikitwindow.h"

बाह्य bool UIKit_InitPen(SDL_VideoDevice *_this);
बाह्य शून्य UIKit_HandlePenMotion(SDL_uikitview *view, UITouch *pencil);
बाह्य शून्य UIKit_HandlePenPress(SDL_uikitview *view, UITouch *pencil);
बाह्य शून्य UIKit_HandlePenRelease(SDL_uikitview *view, UITouch *pencil);

#सचे !defined(SDL_PLATFORM_TVOS)
बाह्य शून्य UIKit_HandlePenHover(SDL_uikitview *view, UIHoverGestureRecognizer *recognizer) API_AVAILABLE(ios(13.0));
#endif

बाह्य शून्य UIKit_QuitPen(SDL_VideoDevice *_this);

#endif // SDL_uikitpen_h_
