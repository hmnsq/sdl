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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ଶୂନ୍ୟ *lib;
    ଅଚଳ ଅକ୍ଷର *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ଖାଲି
#endif

ସ୍ଥିର kmsdrmdynlib kmsdrmlibs[] = {
    { ଖାଲି, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ଖାଲି, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ସ୍ଥିର ଶୂନ୍ୟ *KMSDRM_GetSym(ଅଚଳ ଅକ୍ଷର *fnname, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pHasModule, bool required)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଶୂନ୍ୟ *fn = ଖାଲି;
    ପାଇଁ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ଯଦି (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            ଯଦି (fn) {
                ଭାଙ୍ଗ;
            }
        }
    }

#ଯଦି DEBUG_DYNAMIC_KMSDRM
    ଯଦି (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ଅନ୍ୟଥା
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    ଯଦି (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ଫେରନ୍ତୁ fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ଖାଲି;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ଖାଲି;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmsym.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା kmsdrm_load_refcount = 0;

ଶୂନ୍ୟ SDL_KMSDRM_UnloadSymbols(ଶୂନ୍ୟ)
{
    // Don't actually unload if more than one module is using the libs...
    ଯଦି (kmsdrm_load_refcount > 0) {
        ଯଦି (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ଖାଲି;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ଖାଲି;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ପାଇଁ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ଯଦି (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ଖାଲି;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(ଶୂନ୍ୟ)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    ଯଦି (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା *thismod = ଖାଲି;
        ପାଇଁ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ଯଦି (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmsym.h"

        ଯଦି ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ଅନ୍ୟଥା {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#ଅନ୍ୟଥା // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#ଅନ୍ତର୍ଭାଵ "SDL_kmsdrmsym.h"

#endif
    }

    ଫେରନ୍ତୁ result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
