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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#അന്തര്ഭാവ "SDL_riscosmessagebox.h"

#അന്തര്ഭാവ <kernel.h>
#അന്തര്ഭാവ <swis.h>

bool RISCOS_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    അക്ഷരം buttonstring[1024];
    പൂർണ്ണസംഖ്യ i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->message, 252);
    regs.r[0] = (unsigned പൂർണ്ണസംഖ്യ)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    എങ്കിൽ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } അല്ലെങ്കിൽ എങ്കിൽ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (unsigned പൂർണ്ണസംഖ്യ)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    വേണ്ടി (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].text, 1024);
        എങ്കിൽ (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (unsigned പൂർണ്ണസംഖ്യ)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS
