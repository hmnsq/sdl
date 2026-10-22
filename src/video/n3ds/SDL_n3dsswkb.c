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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_N3DS

#అన్తర్భావ <3ds.h>

#అన్తర్భావ "SDL_n3dsswkb.h"

స్థిర SwkbdState sw_keyboard;
స్థిర స్థిరరాశి size_t బఫరు_కొలత_3 = 256;

శూన్య N3DS_SwkbInit(శూన్య)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_సాధారణ, 2, -1);
}

శూన్య N3DS_SwkbPoll(శూన్య)
{
    తిరిగి;
}

శూన్య N3DS_SwkbQuit(శూన్య)
{
    తిరిగి;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    తిరిగి true;
}

bool N3_DS_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    అక్షరం బఫరు_2[బఫరు_కొలత_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_ఆదానం_పాఠ్యం(&sw_keyboard, బఫరు_2, బఫరు_కొలత_3);
    ఒకవేళ (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_Send_Keyboard_పాఠ్యం(బఫరు_2);
    }
    తిరిగి true;
}

bool N3_DS_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_N3DS
