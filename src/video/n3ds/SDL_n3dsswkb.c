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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_N3DS

#ਅਨ੍ਤਰ੍ਭਾਵ <3ds.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsswkb.h"

ਸਥਿਰ SwkbdState sw_keyboard;
ਸਥਿਰ ਅਚਲ size_t ਬਫਰ_ਮਾਪ_3 = 256;

ਖਾਲੀ N3DS_SwkbInit(ਖਾਲੀ)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_ਸਾਧਾਰਨ, 2, -1);
}

ਖਾਲੀ N3DS_SwkbPoll(ਖਾਲੀ)
{
    ਵਾਪਸ;
}

ਖਾਲੀ N3DS_SwkbQuit(ਖਾਲੀ)
{
    ਵਾਪਸ;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

bool N3_DS_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    ਅੱਖਰ ਬਫਰ_2[ਬਫਰ_ਮਾਪ_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_ਨਿਵੇਸ਼_ਪਾਠ(&sw_keyboard, ਬਫਰ_2, ਬਫਰ_ਮਾਪ_3);
    ਜੇ (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_Send_Keyboard_ਪਾਠ(ਬਫਰ_2);
    }
    ਵਾਪਸ true;
}

bool N3_DS_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_N3DS
