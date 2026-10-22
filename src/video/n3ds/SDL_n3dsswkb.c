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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#அந்தர்பாவ <3ds.h>

#அந்தர்பாவ "SDL_n3dsswkb.h"

நிலையான SwkbdState sw_keyboard;
நிலையான மாறிலி size_t BUFFER_SIZE = 256;

வெறுமை N3DS_SwkbInit(வெறுமை)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_NORMAL, 2, -1);
}

வெறுமை N3DS_SwkbPoll(வெறுமை)
{
    திரும்பு;
}

வெறுமை N3DS_SwkbQuit(வெறுமை)
{
    திரும்பு;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    திரும்பு true;
}

bool N3_DS_Start_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    எழுத்து buffer[BUFFER_SIZE];
    SwkbdButton button_pressed;
    button_pressed = swkbd_உள்ளீடு_Text(&sw_keyboard, buffer, BUFFER_SIZE);
    எனில் (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_SendKeyboardText(buffer);
    }
    திரும்பு true;
}

bool N3_DS_Stop_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window)
{
    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_N3DS
