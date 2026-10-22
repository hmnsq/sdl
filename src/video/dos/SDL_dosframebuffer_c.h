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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_dosframebuffer_c_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_dosframebuffer_c_h_

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

ಬಾಹ್ಯ bool DOSVESA_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch);
ಬಾಹ್ಯ bool DOSVESA_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects);
ಬಾಹ್ಯ ಶೂನ್ಯ DOSVESA_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool DOSVESA_ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ vsync);
ಬಾಹ್ಯ bool DOSVESA_Get_ಕಿಟಕಿ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *vsync);
ಬಾಹ್ಯ ಶೂನ್ಯ DOSVESA_InvalidateCachedFramebuffer(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_dosframebuffer_c_h_
