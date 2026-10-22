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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ଅନ୍ତର୍ଭାଵ "SDL_riscosmessagebox.h"

#ଅନ୍ତର୍ଭାଵ <kernel.h>
#ଅନ୍ତର୍ଭାଵ <swis.h>

bool RISCOS_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    ଅକ୍ଷର buttonstring[1024];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->message, 252);
    regs.r[0] = (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    ଯଦି (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } ଅନ୍ୟଥା ଯଦି (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    ପାଇଁ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].text, 1024);
        ଯଦି (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    ଫେରନ୍ତୁ true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS
