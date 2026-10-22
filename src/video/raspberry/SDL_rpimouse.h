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

#اگر_تعریف_نشده SDL_RPI_mouse_h_
#تعریف_کن SDL_RPI_mouse_h_

#ضمن "../SDL_sysvideo.h"

بنية SDL_Cursor_داده
{
    DISPMANX_RESOURCE_HANDLE_T resource;
    DISPMANX_ELEMENT_HANDLE_T element;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

#تعریف_کن SDL_RPI_CURSORDATA(curs) RPI_Cursor_داده *curdata = (RPI_Cursor_داده *)((curs) ? (curs)->داخلی : عدم)

خارجي فراغ RPI_InitMouse(SDL_VideoDevice *_this);
خارجي فراغ RPI_QuitMouse(SDL_VideoDevice *_this);

#پایان_اگر // SDL_RPI_mouse_h_
