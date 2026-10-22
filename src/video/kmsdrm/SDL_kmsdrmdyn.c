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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_DYNAMIC_KMSDRM 0

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmdyn.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਖਾਲੀ *lib;
    ਅਚਲ ਅੱਖਰ *libname;
} kmsdrmdynlib;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ਨਿਰਾ
#ਜੇ_ਅੰਤ

ਸਥਿਰ kmsdrmdynlib kmsdrmlibs[] = {
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ਸਥਿਰ ਖਾਲੀ *KMSDRM_GetSym(ਅਚਲ ਅੱਖਰ *fnname, ਪੂਰਨ *pHasModule, bool required)
{
    ਪੂਰਨ i;
    ਖਾਲੀ *fn = ਨਿਰਾ;
    ਲਈ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ਜੇ (kmsdrmlibs[i].lib) {
            fn = SDL_ਲੱਦੋ_Function(kmsdrmlibs[i].lib, fnname);
            ਜੇ (fn) {
                ਰੋਕੋ;
            }
        }
    }

#ਜੇ DEBUG_DYNAMIC_KMSDRM
    ਜੇ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ਨਹੀਂਤਾਂ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#ਜੇ_ਅੰਤ

    ਜੇ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ਵਾਪਸ fn;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname)          ਪੂਰਨ SDL_KMSDRM_HAVE_##modname = 0;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmsym.h"

ਸਥਿਰ ਪੂਰਨ kmsdrm_ਲੱਦੋ_refcount = 0;

ਖਾਲੀ SDL_KMSDRM_UnloadSymbols(ਖਾਲੀ)
{
    // Don't actually unload if more than one module is using the libs...
    ਜੇ (kmsdrm_ਲੱਦੋ_refcount > 0) {
        ਜੇ (--kmsdrm_ਲੱਦੋ_refcount == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ਪੂਰਨ i;
#ਜੇ_ਅੰਤ

            // set all the function pointers to NULL.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmsym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ਲਈ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ਜੇ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ਨਿਰਾ;
                }
            }
#ਜੇ_ਅੰਤ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_ਲੱਦੋ_Symbols(ਖਾਲੀ)
{
    bool ਨਤੀਜਾ = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    ਜੇ (kmsdrm_ਲੱਦੋ_refcount++ == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        ਪੂਰਨ i;
        ਪੂਰਨ *thismod = ਨਿਰਾ;
        ਲਈ (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ਜੇ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_ਲੱਦੋ_Object(kmsdrmlibs[i].libname);
            }
        }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmsym.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmsym.h"

        ਜੇ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ਨਹੀਂਤਾਂ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            ਨਤੀਜਾ = false;
        }

#ਨਹੀਂਤਾਂ // no dynamic KMSDRM

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmsym.h"

#ਜੇ_ਅੰਤ
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_KMSDRM
