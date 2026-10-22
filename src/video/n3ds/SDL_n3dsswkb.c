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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ <3ds.h>

#ಅನ್ತರ್ಭಾವ "SDL_n3dsswkb.h"

ಸ್ಥಿರ SwkbdState sw_keyboard;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t ಬಫರ್_ಗಾತ್ರ_3 = 256;

ಶೂನ್ಯ N3DS_SwkbInit(ಶೂನ್ಯ)
{
    swkbdInit(&sw_keyboard, SWKBD_TYPE_ಸಾಮಾನ್ಯ, 2, -1);
}

ಶೂನ್ಯ N3DS_SwkbPoll(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ;
}

ಶೂನ್ಯ N3DS_SwkbQuit(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ;
}

bool N3DS_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ true;
}

bool N3_DS_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    ಅಕ್ಷರ ಬಫರ್_2[ಬಫರ್_ಗಾತ್ರ_3];
    SwkbdButton button_pressed;
    button_pressed = swkbd_ಒಳಹರಿವು_ಪಠ್ಯ(&sw_keyboard, ಬಫರ್_2, ಬಫರ್_ಗಾತ್ರ_3);
    ಆದರೆ (button_pressed == SWKBD_BUTTON_CONFIRM) {
        SDL_Send_Keyboard_ಪಠ್ಯ(ಬಫರ್_2);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool N3_DS_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_N3DS
