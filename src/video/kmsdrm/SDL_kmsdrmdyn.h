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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_kmsdrmdyn_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_kmsdrmdyn_h_

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ <xf86drm.h>
#ಅನ್ತರ್ಭಾವ <xf86drmMode.h>
#ಅನ್ತರ್ಭಾವ <gbm.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ bool SDL_KMSDRM_ತುಂಬು_Symbols(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_KMSDRM_UnloadSymbols(ಶೂನ್ಯ);

// Declare all the function pointers and wrappers...
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc, fn, params)        \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ rc(*SDL_DYNKMSDRMFN_##fn) params; \
    ಬಾಹ್ಯ SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)    \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ type SDL_DYNKMSDRMCONST_##name; \
    ಬಾಹ್ಯ SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ rc(*SDL_DYNKMSDRMFN_##fn) params; \
    ಬಾಹ್ಯ SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_kmsdrmdyn_h_
