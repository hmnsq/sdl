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

#که_نه_تعریف_شوی SDL_kmsdrmdyn_h_
#تعریف_کړه SDL_kmsdrmdyn_h_

#ضمن "SDL_internal.h"

#ضمن <xf86drm.h>
#ضمن <xf86drmMode.h>
#ضمن <gbm.h>

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

خارجي bool SDL_KMSDRM_بارول_Symbols(فراغ);
خارجي فراغ SDL_KMSDRM_UnloadSymbols(فراغ);

// Declare all the function pointers and wrappers...
#تعریف_کړه SDL_KMSDRM_SYM(rc, fn, params)        \
    تعريفنوع rc(*SDL_DYNKMSDRMFN_##fn) params; \
    خارجي SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#تعریف_کړه SDL_KMSDRM_SYM_CONST(type, name)    \
    تعريفنوع type SDL_DYNKMSDRMCONST_##name; \
    خارجي SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#تعریف_کړه SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    تعريفنوع rc(*SDL_DYNKMSDRMFN_##fn) params; \
    خارجي SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#ضمن "SDL_kmsdrmsym.h"

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_kmsdrmdyn_h_
