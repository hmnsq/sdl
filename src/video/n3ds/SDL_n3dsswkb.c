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

#अगर_घोषित SDL_VIDEO_DRIVER_N3DS

#समावेश <3ds.h>

#समावेश "SDL_n3dsswkb.h"

अटल SwkbdState sw_keyboard;
अटल स्थिर माप_प्रकार बफर_आकार_3 = 256;

व्योम N3DS_SwkbInit(व्योम)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_NORMAL, 2, -1);
}

व्योम N3DS_SwkbPoll(व्योम)
{
    वापस;
}

व्योम N3DS_SwkbQuit(व्योम)
{
    वापस;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    वापस true;
}

bool N3_DS_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    अक्षर बफर_2[बफर_आकार_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_निवेश_Text(&sw_keyboard, बफर_2, बफर_आकार_3);
    अगर (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_SendKeyboardText(बफर_2);
    }
    वापस true;
}

bool N3_DS_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_N3DS
