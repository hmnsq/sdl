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

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscoswindow.h"

bool RISCOS_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    ਅੰਕੜੇ->ਖਿੜਕੀ = ਖਿੜਕੀ;

    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);

    // All done!
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਵਾਪਸ true;
}

ਖਾਲੀ RISCOS_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS
