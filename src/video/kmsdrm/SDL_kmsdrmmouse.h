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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_KMSDRM_mouse_h_
#घोषणा SDL_KMSDRM_mouse_h_

#समावेश <gbm.h>

#घोषणा MAX_CURSOR_W 512
#घोषणा MAX_CURSOR_H 512

काष्ठा SDL_Cursor_तथ्य
{
    पूर्णांक hot_x, hot_y;
    पूर्णांक w, h;

    /* The buffer where we store the mouse bitmap ready to be used.
       We get it ready and filled in CreateCursor(), and copy it
       to a GBM BO in ShowCursor().*/
    uint32_t *बफर_2;
    माप_प्रकार बफर_आकार;
    माप_प्रकार बफर_pitch;

};

बाह्य व्योम KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य व्योम KMSDRM_QuitMouse(SDL_VideoDevice *_this);

बाह्य bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display);
बाह्य व्योम KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य व्योम KMSDRM_InitCursor(व्योम);

#पूर्ण_अगर // SDL_KMSDRM_mouse_h_
