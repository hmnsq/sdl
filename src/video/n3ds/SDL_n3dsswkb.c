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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#അന്തര്ഭാവ <3ds.h>

#അന്തര്ഭാവ "SDL_n3dsswkb.h"

സ്ഥിതം SwkbdState sw_keyboard;
സ്ഥിതം സ്ഥിരം size_t BUFFER_SIZE = 256;

ശൂന്യം N3DS_SwkbInit(ശൂന്യം)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_NORMAL, 2, -1);
}

ശൂന്യം N3DS_SwkbPoll(ശൂന്യം)
{
    തിരികെ;
}

ശൂന്യം N3DS_SwkbQuit(ശൂന്യം)
{
    തിരികെ;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    തിരികെ true;
}

bool N3_DS_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    അക്ഷരം buffer[BUFFER_SIZE];
    SwkbdButton button_pressed;
    button_pressed = swkbd_നിവേശം_Text(&sw_keyboard, buffer, BUFFER_SIZE);
    എങ്കിൽ (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_SendKeyboardText(buffer);
    }
    തിരികെ true;
}

bool N3_DS_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_N3DS
