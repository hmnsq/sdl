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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#ضمن <3ds.h>

#ضمن "SDL_n3dsswkb.h"

ساكن SwkbdState sw_keyboard;
ساكن ثابت size_t BUFFER_SIZE = 256;

فراغ N3DS_SwkbInit(فراغ)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_NORMAL, 2, -1);
}

فراغ N3DS_SwkbPoll(فراغ)
{
    أرجع;
}

فراغ N3DS_SwkbQuit(فراغ)
{
    أرجع;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

bool N3_DS_Start_Text_تێخستن(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    حرف buffer[BUFFER_SIZE];
    SwkbdButton button_pressed;
    button_pressed = swkbd_تێخستن_Text(&sw_keyboard, buffer, BUFFER_SIZE);
    إذا (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_SendKeyboardText(buffer);
    }
    أرجع true;
}

bool N3_DS_Stop_Text_تێخستن(SDL_VideoDevice *_this, SDL_Window *window)
{
    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_N3DS
