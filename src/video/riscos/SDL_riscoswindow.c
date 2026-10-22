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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

bool RISCOS_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *معلومات;

    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }
    معلومات->دري = دري;

    SDL_سيٽ_Mouse_Focus(دري);

    // All done!
    دري->اندروني = معلومات;
    أرجع true;
}

فراغ RISCOS_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (دري->اندروني) {
        SDL_free(دري->اندروني);
        دري->اندروني = عدم;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_RISCOS
