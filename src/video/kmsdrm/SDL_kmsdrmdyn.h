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

#اگر_غیر_تعریف_شدہ SDL_kmsdrmdyn_h_
#تعریف_کرو SDL_kmsdrmdyn_h_

#شامل "SDL_internal.h"

#شامل <xf86drm.h>
#شامل <xf86drmMode.h>
#شامل <gbm.h>

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

خارجی bool SDL_KMSDRM_بھرو_Symbols(خالی);
خارجی خالی SDL_KMSDRM_UnloadSymbols(خالی);

// Declare all the function pointers and wrappers...
#تعریف_کرو SDL_KMSDRM_SYM(rc, fn, params)        \
    قسمتعریف rc(*SDL_DYNKMSDRMFN_##fn) params; \
    خارجی SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#تعریف_کرو SDL_KMSDRM_SYM_CONST(type, name)    \
    قسمتعریف type SDL_DYNKMSDRMCONST_##name; \
    خارجی SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#تعریف_کرو SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    قسمتعریف rc(*SDL_DYNKMSDRMFN_##fn) params; \
    خارجی SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#شامل "SDL_kmsdrmsym.h"

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_kmsdrmdyn_h_
