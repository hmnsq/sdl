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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandshmbuffer_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandshmbuffer_h_

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_SHMPool Wayland_SHMPool;

ಬಾಹ್ಯ Wayland_SHMPool *Wayland_AllocSHMPool(ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2);
ಬಾಹ್ಯ ರಚನೆ wl_ಬಫರ್ *Wayland_Alloc_ಬಫರ್_From_Pool(Wayland_SHMPool *shmPool, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಶೂನ್ಯ **ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool);

ಬಾಹ್ಯ ರಚನೆ wl_ಬಫರ್ *Wayland_Create_Single_Pixel_ಬಫರ್(Uint32 r, Uint32 g, Uint32 b, Uint32 a);

#ಆದರೆ_ಅಂತ್ಯ
