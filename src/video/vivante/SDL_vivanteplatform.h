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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_vivanteplatform_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_vivanteplatform_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE

#ಅನ್ತರ್ಭಾವ "SDL_vivantevideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CAVIUM
#ವ್ಯಾಖ್ಯಾನಿಸು VIVANTE_PLATFORM_CAVIUM
#ಅಥವಾಆದರೆ defined(MARVELL)
#ವ್ಯಾಖ್ಯಾನಿಸು VIVANTE_PLATFORM_MARVELL
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VIVANTE_PLATFORM_GENERIC
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ bool VIVANTE_ಸಿದ್ಧತೆ_Platform(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಅಕ್ಷರ *VIVANTE_GetDisplayName(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ VIVANTE_CleanupPlatform(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VIVANTE

#ಆದರೆ_ಅಂತ್ಯ // SDL_vivanteplatform_h_
