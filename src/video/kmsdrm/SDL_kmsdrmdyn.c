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

#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM

#تعریف_کن DEBUG_DYNAMIC_KMSDRM 0

#ضمن "SDL_kmsdrmdyn.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_اولویت_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

تعريفنوع بنية
{
    فراغ *lib;
    ثابت حرف *libname;
} kmsdrmdynlib;

#اگر_تعریف_نشده SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#تعریف_کن SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM عدم
#پایان_اگر

ساكن kmsdrmdynlib kmsdrmlibs[] = {
    { عدم, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { عدم, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ساكن فراغ *KMSDRM_GetSym(ثابت حرف *fnname, صحيح *pHasModule, bool required)
{
    صحيح i;
    فراغ *fn = عدم;
    لكل (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        إذا (kmsdrmlibs[i].lib) {
            fn = SDL_بارگیری_Function(kmsdrmlibs[i].lib, fnname);
            إذا (fn) {
                اكسر;
            }
        }
    }

#إذا DEBUG_DYNAMIC_KMSDRM
    إذا (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    وإلا
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#پایان_اگر

    إذا (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    أرجع fn;
}

#پایان_اگر // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#تعریف_کن SDL_KMSDRM_MODULE(modname)          صحيح SDL_KMSDRM_HAVE_##modname = 0;
#تعریف_کن SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = عدم;
#تعریف_کن SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = عدم;
#تعریف_کن SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = عدم;
#ضمن "SDL_kmsdrmsym.h"

ساكن صحيح kmsdrm_بارگیری_refcount = 0;

فراغ SDL_KMSDRM_UnloadSymbols(فراغ)
{
    // Don't actually unload if more than one module is using the libs...
    إذا (kmsdrm_بارگیری_refcount > 0) {
        إذا (--kmsdrm_بارگیری_refcount == 0) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            صحيح i;
#پایان_اگر

            // set all the function pointers to NULL.
#تعریف_کن SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#تعریف_کن SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = عدم;
#تعریف_کن SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = عدم;
#تعریف_کن SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = عدم;
#ضمن "SDL_kmsdrmsym.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            لكل (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                إذا (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = عدم;
                }
            }
#پایان_اگر
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_بارگیری_Symbols(فراغ)
{
    bool نتیجه = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    إذا (kmsdrm_بارگیری_refcount++ == 0) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        صحيح i;
        صحيح *thismod = عدم;
        لكل (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            إذا (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_بارگیری_Object(kmsdrmlibs[i].libname);
            }
        }

#تعریف_کن SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#ضمن "SDL_kmsdrmsym.h"

#تعریف_کن SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#تعریف_کن SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#تعریف_کن SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#تعریف_کن SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#ضمن "SDL_kmsdrmsym.h"

        إذا ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } وإلا {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            نتیجه = false;
        }

#وإلا // no dynamic KMSDRM

#تعریف_کن SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#تعریف_کن SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#تعریف_کن SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#تعریف_کن SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#ضمن "SDL_kmsdrmsym.h"

#پایان_اگر
    }

    أرجع نتیجه;
}

#پایان_اگر // SDL_VIDEO_DRIVER_KMSDRM
