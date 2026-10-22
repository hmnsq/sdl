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

#నిర్వచితం_కాకపోతే SDL_vitatouch_h
#నిర్వచించు SDL_vitatouch_h

#అన్తర్భావ "SDL_internal.h"

// Touch functions
బాహ్య శూన్య VITA_InitTouch(శూన్య);
బాహ్య శూన్య VITA_QuitTouch(శూన్య);
బాహ్య శూన్య VITA_PollTouch(శూన్య);
శూన్య VITA_ConvertTouchXYToSDLXY(దశాంశం *sdl_x, దశాంశం *sdl_y, పూర్ణాంకం vita_x, పూర్ణాంకం vita_y, పూర్ణాంకం పోర్టు);

#అయితే_ముగింపు // SDL_vitatouch_h
