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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_windowsmouse_h_
#నిర్వచించు SDL_windowsmouse_h_

బాహ్య DWORD SDL_చివరి_warp_సమయం;
బాహ్య HCURSOR SDL_cursor;

బాహ్య శూన్య WIN_InitMouse(SDL_VideoDevice *_this);
బాహ్య శూన్య WIN_QuitMouse(SDL_VideoDevice *_this);
బాహ్య శూన్య WIN_సమితి_Cursor_Pos(పూర్ణాంకం x, పూర్ణాంకం y);
బాహ్య శూన్య WIN_UpdateMouseSystemScale(శూన్య);

#అయితే_ముగింపు // SDL_windowsmouse_h_
