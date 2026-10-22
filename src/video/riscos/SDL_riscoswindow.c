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

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscoswindow.h"

bool RISCOS_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }
    దత్తాంశం->కిటికీ = కిటికీ;

    SDL_సమితి_Mouse_Focus(కిటికీ);

    // All done!
    కిటికీ->అంతర్గత = దత్తాంశం;
    తిరిగి true;
}

శూన్య RISCOS_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత) {
        SDL_free(కిటికీ->అంతర్గత);
        కిటికీ->అంతర్గత = ఖాళీ;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS
