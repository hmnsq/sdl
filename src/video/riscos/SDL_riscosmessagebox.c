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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "SDL_riscosmessagebox.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>
#ಅನ್ತರ್ಭಾವ <swis.h>

bool RISCOS_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    ಅಕ್ಷರ buttonstring[1024];
    ಪೂರ್ಣಾಂಕ i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->ಸಂದೇಶ, 252);
    regs.r[0] = (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].ಪಠ್ಯ, 1024);
        ಆದರೆ (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS
