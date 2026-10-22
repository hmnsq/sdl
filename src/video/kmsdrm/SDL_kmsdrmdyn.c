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

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಶೂನ್ಯ *lib;
    ಧ್ರುವ ವರ್ಣ *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ರಿಕ್ತ
#endif

ಸ್ಥಿರ kmsdrmdynlib kmsdrmlibs[] = {
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ಸ್ಥಿರ ಶೂನ್ಯ *KMSDRM_GetSym(ಧ್ರುವ ವರ್ಣ *fnname, ಪೂರ್ಣಾಙ್ಕ *pHasModule, bool required)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಶೂನ್ಯ *fn = ರಿಕ್ತ;
    ಪ್ರತಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ಯದಿ (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            ಯದಿ (fn) {
                ಭಙ್ಗ;
            }
        }
    }

#ಯದಿ DEBUG_DYNAMIC_KMSDRM
    ಯದಿ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ಅನ್ಯಥಾ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    ಯದಿ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ಪ್ರತ್ಯಾಗಮ fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          ಪೂರ್ಣಾಙ್ಕ SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ರಿಕ್ತ;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ರಿಕ್ತ;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ kmsdrm_load_refcount = 0;

ಶೂನ್ಯ SDL_KMSDRM_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಯದಿ (kmsdrm_load_refcount > 0) {
        ಯದಿ (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ಪೂರ್ಣಾಙ್ಕ i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ರಿಕ್ತ;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ರಿಕ್ತ;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ಪ್ರತಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ಯದಿ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ರಿಕ್ತ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(ಶೂನ್ಯ)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    ಯದಿ (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        ಪೂರ್ಣಾಙ್ಕ i;
        ಪೂರ್ಣಾಙ್ಕ *thismod = ರಿಕ್ತ;
        ಪ್ರತಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ಯದಿ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

        ಯದಿ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ಅನ್ಯಥಾ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#ಅನ್ಯಥಾ // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#endif
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
