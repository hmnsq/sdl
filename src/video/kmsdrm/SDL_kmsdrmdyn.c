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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM

#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_DYNAMIC_KMSDRM 0

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಶೂನ್ಯ *lib;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *libname;
} kmsdrmdynlib;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ kmsdrmdynlib kmsdrmlibs[] = {
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ಸ್ಥಿರ ಶೂನ್ಯ *KMSDRM_GetSym(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fnname, ಪೂರ್ಣಾಂಕ *pHasModule, bool required)
{
    ಪೂರ್ಣಾಂಕ i;
    ಶೂನ್ಯ *fn = ಖಾಲಿ;
    ಗಾಗಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ಆದರೆ (kmsdrmlibs[i].lib) {
            fn = SDL_ತುಂಬು_Function(kmsdrmlibs[i].lib, fnname);
            ಆದರೆ (fn) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

#ಆದರೆ DEBUG_DYNAMIC_KMSDRM
    ಆದರೆ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ಇಲ್ಲದಿದ್ದರೆ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ಹಿಂತಿರುಗಿ fn;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname)          ಪೂರ್ಣಾಂಕ SDL_KMSDRM_HAVE_##modname = 0;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ kmsdrm_ತುಂಬು_refcount = 0;

ಶೂನ್ಯ SDL_KMSDRM_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಆದರೆ (kmsdrm_ತುಂಬು_refcount > 0) {
        ಆದರೆ (--kmsdrm_ತುಂಬು_refcount == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ಪೂರ್ಣಾಂಕ i;
#ಆದರೆ_ಅಂತ್ಯ

            // set all the function pointers to NULL.
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ಗಾಗಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ಆದರೆ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ಖಾಲಿ;
                }
            }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_ತುಂಬು_Symbols(ಶೂನ್ಯ)
{
    bool ಫಲಿತಾಂಶ = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    ಆದರೆ (kmsdrm_ತುಂಬು_refcount++ == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        ಪೂರ್ಣಾಂಕ i;
        ಪೂರ್ಣಾಂಕ *thismod = ಖಾಲಿ;
        ಗಾಗಿ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ಆದರೆ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_ತುಂಬು_Object(kmsdrmlibs[i].libname);
            }
        }

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

        ಆದರೆ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ಇಲ್ಲದಿದ್ದರೆ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            ಫಲಿತಾಂಶ = false;
        }

#ಇಲ್ಲದಿದ್ದರೆ // no dynamic KMSDRM

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmsym.h"

#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM
