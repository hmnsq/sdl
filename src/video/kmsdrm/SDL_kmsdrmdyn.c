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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#அந்தர்பாவ "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

வகைவரை கட்டமைப்பு
{
    வெறுமை *lib;
    மாறிலி எழுத்து *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM வெற்று
#endif

நிலையான kmsdrmdynlib kmsdrmlibs[] = {
    { வெற்று, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { வெற்று, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

நிலையான வெறுமை *KMSDRM_GetSym(மாறிலி எழுத்து *fnname, முழு *pHasModule, bool required)
{
    முழு i;
    வெறுமை *fn = வெற்று;
    க்கு (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        எனில் (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            எனில் (fn) {
                நிறுத்து;
            }
        }
    }

#எனில் DEBUG_DYNAMIC_KMSDRM
    எனில் (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    இல்லையெனில்
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    எனில் (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    திரும்பு fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          முழு SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = வெற்று;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = வெற்று;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = வெற்று;
#அந்தர்பாவ "SDL_kmsdrmsym.h"

நிலையான முழு kmsdrm_load_refcount = 0;

வெறுமை SDL_KMSDRM_UnloadSymbols(வெறுமை)
{
    // Don't actually unload if more than one module is using the libs...
    எனில் (kmsdrm_load_refcount > 0) {
        எனில் (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            முழு i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = வெற்று;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = வெற்று;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = வெற்று;
#அந்தர்பாவ "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            க்கு (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                எனில் (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = வெற்று;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(வெறுமை)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    எனில் (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        முழு i;
        முழு *thismod = வெற்று;
        க்கு (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            எனில் (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#அந்தர்பாவ "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#அந்தர்பாவ "SDL_kmsdrmsym.h"

        எனில் ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } இல்லையெனில் {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#இல்லையெனில் // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#அந்தர்பாவ "SDL_kmsdrmsym.h"

#endif
    }

    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
