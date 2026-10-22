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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosmessagebox.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <kernel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <swis.h>

bool RISCOS_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    _kernel_swi_regs regs;
    _kernel_oserror error;
    ਅੱਖਰ buttonstring[1024];
    ਪੂਰਨ i;

    error.errnum = 0;
    SDL_strlcpy(error.errmess, messageboxdata->ਸੁਨੇਹਾ, 252);
    regs.r[0] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)&error;

    regs.r[1] = (1 << 8) | (1 << 4);
    ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        regs.r[1] |= (1 << 9);
    } ਨਹੀਂਤਾਂ ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        regs.r[1] |= (2 << 9);
    }

    regs.r[2] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)messageboxdata->title;
    regs.r[3] = 0;
    regs.r[4] = 0;

    SDL_strlcpy(buttonstring, "", 1024);
    ਲਈ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_strlcat(buttonstring, messageboxdata->buttons[i].ਪਾਠ, 1024);
        ਜੇ (i + 1 < messageboxdata->numbuttons) {
            SDL_strlcat(buttonstring, ",", 1024);
        }
    }
    regs.r[5] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)buttonstring;

    _kernel_swi(Wimp_ReportError, &regs, &regs);

    *buttonID = (regs.r[1] == 0) ? -1 : messageboxdata->buttons[regs.r[1] - 3].buttonID;
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS
