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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#شامل <3ds.h>

#شامل "SDL_n3dsswkb.h"

ساکن SwkbdState sw_keyboard;
ساکن ثابت size_t بفر_سائز_3 = 256;

خالی N3DS_SwkbInit(خالی)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_معمول, 2, -1);
}

خالی N3DS_SwkbPoll(خالی)
{
    واپس;
}

خالی N3DS_SwkbQuit(خالی)
{
    واپس;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    واپس true;
}

bool N3_DS_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    حرف بفر_2[بفر_سائز_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_داخلہ_متن(&sw_keyboard, بفر_2, بفر_سائز_3);
    اگر (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_Send_Keyboard_متن(بفر_2);
    }
    واپس true;
}

bool N3_DS_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_N3DS
