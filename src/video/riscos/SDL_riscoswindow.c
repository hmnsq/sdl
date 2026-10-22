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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_mouse_c.h"

#شامل "SDL_riscosvideo.h"
#شامل "SDL_riscoswindow.h"

bool RISCOS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }
    ڈیٹا->کھڑکی = کھڑکی;

    SDL_سیٹ_Mouse_Focus(کھڑکی);

    // All done!
    کھڑکی->اندرونی_2 = ڈیٹا;
    واپس true;
}

خالی RISCOS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2) {
        SDL_free(کھڑکی->اندرونی_2);
        کھڑکی->اندرونی_2 = تہی;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_RISCOS
