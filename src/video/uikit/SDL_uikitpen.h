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

#నిర్వచితం_కాకపోతే SDL_uikitpen_h_
#నిర్వచించు SDL_uikitpen_h_

#అన్తర్భావ "SDL_uikitvideo.h"
#అన్తర్భావ "SDL_uikitwindow.h"

బాహ్య bool UIKit_InitPen(SDL_VideoDevice *_this);
బాహ్య శూన్య UIKit_HandlePenMotion(SDL_uikitview *view, UITouch *pencil);
బాహ్య శూన్య UIKit_HandlePenPress(SDL_uikitview *view, UITouch *pencil);
బాహ్య శూన్య UIKit_HandlePenRelease(SDL_uikitview *view, UITouch *pencil);

#ఒకవేళ !defined(SDL_PLATFORM_TVOS)
బాహ్య శూన్య UIKit_HandlePenHover(SDL_uikitview *view, UIHoverGestureRecognizer *recognizer) API_అందుబాటు(ios(13.0));
#అయితే_ముగింపు

బాహ్య శూన్య UIKit_QuitPen(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_uikitpen_h_
