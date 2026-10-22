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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "SDL_riscosmessagebox.h"

#అన్తర్భావ <kernel.h>
#అన్తర్భావ <swis.h>

bool RISCOS_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    అక్షరం buttonstring[1024];
    పూర్ణాంకం i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->సందేశం, 252);
    regs.r[0] = (గుర్తులేని పూర్ణాంకం)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } లేకపోతే ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (గుర్తులేని పూర్ణాంకం)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    కొరకు (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].పాఠ్యం, 1024);
        ఒకవేళ (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (గుర్తులేని పూర్ణాంకం)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS
