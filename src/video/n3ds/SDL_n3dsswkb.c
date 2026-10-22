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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_N3DS

#ضمن <3ds.h>

#ضمن "SDL_n3dsswkb.h"

ساكن SwkbdState sw_keyboard;
ساكن ثابت size_t میانگیر_اندازه_3 = 256;

فراغ N3DS_SwkbInit(فراغ)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_نرمال, 2, -1);
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

bool N3_DS_شروع_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    حرف میانگیر_2[میانگیر_اندازه_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_درون_داد_متن(&sw_keyboard, میانگیر_2, میانگیر_اندازه_3);
    إذا (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_Send_Keyboard_متن(میانگیر_2);
    }
    أرجع true;
}

bool N3_DS_Stop_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_N3DS
