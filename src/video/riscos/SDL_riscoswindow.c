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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

bool RISCOS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *انکڑے;

    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }
    انکڑے->کھڑکی = کھڑکی;

    SDL_سیٹ_Mouse_Focus(کھڑکی);

    // All done!
    کھڑکی->اندرونی = انکڑے;
    أرجع true;
}

فراغ RISCOS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی) {
        SDL_free(کھڑکی->اندرونی);
        کھڑکی->اندرونی = عدم;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_RISCOS
