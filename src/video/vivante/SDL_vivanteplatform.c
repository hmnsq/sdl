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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivanteplatform.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VIVANTE_PLATFORM_GENERIC

bool VIVANTE_ਤਿਆਰੀ_Platform(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

ਅੱਖਰ *VIVANTE_GetDisplayName(SDL_VideoDevice *_this)
{
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ VIVANTE_UpdateDisplayScale(SDL_VideoDevice *_this)
{
}

ਖਾਲੀ VIVANTE_CleanupPlatform(SDL_VideoDevice *_this)
{
}

#ਜੇ_ਅੰਤ // VIVANTE_PLATFORM_GENERIC

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VIVANTE
