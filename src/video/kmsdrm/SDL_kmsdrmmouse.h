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

#నిర్వచితం_కాకపోతే SDL_KMSDRM_mouse_h_
#నిర్వచించు SDL_KMSDRM_mouse_h_

#అన్తర్భావ <gbm.h>

#నిర్వచించు MAX_CURSOR_W 512
#నిర్వచించు MAX_CURSOR_H 512

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    పూర్ణాంకం hot_x, hot_y;
    పూర్ణాంకం w, h;

    /* The buffer where we store the mouse bitmap ready to be used.
       We get it ready and filled in CreateCursor(), and copy it
       to a GBM BO in ShowCursor().*/
    uint32_t *బఫరు_2;
    size_t బఫరు_కొలత;
    size_t బఫరు_pitch;

};

బాహ్య శూన్య KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య శూన్య KMSDRM_QuitMouse(SDL_VideoDevice *_this);

బాహ్య bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display);
బాహ్య శూన్య KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య శూన్య KMSDRM_InitCursor(శూన్య);

#అయితే_ముగింపు // SDL_KMSDRM_mouse_h_
