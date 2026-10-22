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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_KMSDRM_mouse_h_
#define SDL_KMSDRM_mouse_h_

#ଅନ୍ତର୍ଭାଵ <gbm.h>

#define MAX_CURSOR_W 512
#define MAX_CURSOR_H 512

ସଂରଚନା SDL_CursorData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, hot_y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    /* The buffer where we store the mouse bitmap ready to be used.
       We get it ready and filled in CreateCursor(), and copy it
       to a GBM BO in ShowCursor().*/
    uint32_t *buffer;
    size_t buffer_size;
    size_t buffer_pitch;

};

ବାହ୍ୟ ଶୂନ୍ୟ KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ KMSDRM_QuitMouse(SDL_VideoDevice *_this);

ବାହ୍ୟ bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ KMSDRM_InitCursor(ଶୂନ୍ୟ);

#endif // SDL_KMSDRM_mouse_h_
