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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#अन्तर्भाव "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

प्रकारव्याख्या संरचना
{
    शून्य *lib;
    स्थिरांक अक्षर *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM रिक्त
#endif

स्थिर kmsdrmdynlib kmsdrmlibs[] = {
    { रिक्त, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { रिक्त, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

स्थिर शून्य *KMSDRM_GetSym(स्थिरांक अक्षर *fnname, पूर्णांक *pHasModule, bool required)
{
    पूर्णांक i;
    शून्य *fn = रिक्त;
    साठी (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        जर (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            जर (fn) {
                थांबा;
            }
        }
    }

#जर DEBUG_DYNAMIC_KMSDRM
    जर (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    अन्यथा
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    जर (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    परत fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          पूर्णांक SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = रिक्त;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = रिक्त;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = रिक्त;
#अन्तर्भाव "SDL_kmsdrmsym.h"

स्थिर पूर्णांक kmsdrm_load_refcount = 0;

शून्य SDL_KMSDRM_UnloadSymbols(शून्य)
{
    // Don't actually unload if more than one module is using the libs...
    जर (kmsdrm_load_refcount > 0) {
        जर (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            पूर्णांक i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = रिक्त;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = रिक्त;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = रिक्त;
#अन्तर्भाव "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            साठी (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                जर (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = रिक्त;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(शून्य)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    जर (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        पूर्णांक i;
        पूर्णांक *thismod = रिक्त;
        साठी (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            जर (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#अन्तर्भाव "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#अन्तर्भाव "SDL_kmsdrmsym.h"

        जर ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#अन्यथा // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#अन्तर्भाव "SDL_kmsdrmsym.h"

#endif
    }

    परत result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
