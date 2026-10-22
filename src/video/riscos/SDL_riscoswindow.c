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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscoswindow.h"

bool RISCOS_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *दत्त;

    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }
    दत्त->गवाक्षः = गवाक्षः;

    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);

    // All done!
    गवाक्षः->आन्तरिकम् = दत्त;
    प्रत्यागम true;
}

शून्य RISCOS_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्) {
        SDL_free(गवाक्षः->आन्तरिकम्);
        गवाक्षः->आन्तरिकम् = रिक्त;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_RISCOS
