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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#অন্তর্ভাব <3ds.h>

#অন্তর্ভাব "SDL_n3dsswkb.h"

স্থির SwkbdState sw_keyboard;
স্থির ধ্রুব size_t BUFFER_SIZE = 256;

শূন্য N3DS_SwkbInit(শূন্য)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_NORMAL, 2, -1);
}

শূন্য N3DS_SwkbPoll(শূন্য)
{
    প্রত্যাগম;
}

শূন্য N3DS_SwkbQuit(শূন্য)
{
    প্রত্যাগম;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    প্রত্যাগম true;
}

bool N3_DS_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    বর্ণ buffer[BUFFER_SIZE];
    SwkbdButton button_pressed;
    button_pressed = swkbd_প্রবেশ_Text(&sw_keyboard, buffer, BUFFER_SIZE);
    যদি (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_SendKeyboardText(buffer);
    }
    প্রত্যাগম true;
}

bool N3_DS_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    প্রত্যাগম true;
}

#endif // SDL_VIDEO_DRIVER_N3DS
