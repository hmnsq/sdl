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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "SDL_riscosmessagebox.h"

#अन्तर्भाव <kernel.h>
#अन्तर्भाव <swis.h>

bool RISCOS_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    वर्ण buttonstring[1024];
    पूर्णाङ्क i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->message, 252);
    regs.r[0] = (अचिन्हित पूर्णाङ्क)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    यदि (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } अन्यथा यदि (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (अचिन्हित पूर्णाङ्क)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    प्रति (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].text, 1024);
        यदि (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (अचिन्हित पूर्णाङ्क)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    प्रत्यागम true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS
