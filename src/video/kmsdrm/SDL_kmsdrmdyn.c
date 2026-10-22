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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM

#घोषणा DEBUG_DYNAMIC_KMSDRM 0

#समावेश "SDL_kmsdrmdyn.h"

#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

प्रकार काष्ठा
{
    व्योम *lib;
    स्थिर अक्षर *libname;
} kmsdrmdynlib;

#अगर_अघोषित SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#घोषणा SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM शून्य
#पूर्ण_अगर

अटल kmsdrmdynlib kmsdrmlibs[] = {
    { शून्य, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { शून्य, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

अटल व्योम *KMSDRM_GetSym(स्थिर अक्षर *fnname, पूर्णांक *pHasModule, bool required)
{
    पूर्णांक i;
    व्योम *fn = शून्य;
    क्रम (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        अगर (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            अगर (fn) {
                अवरोध;
            }
        }
    }

#अगर DEBUG_DYNAMIC_KMSDRM
    अगर (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    अन्यथा
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#पूर्ण_अगर

    अगर (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    वापस fn;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#घोषणा SDL_KMSDRM_MODULE(modname)          पूर्णांक SDL_KMSDRM_HAVE_##modname = 0;
#घोषणा SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = शून्य;
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = शून्य;
#घोषणा SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = शून्य;
#समावेश "SDL_kmsdrmsym.h"

अटल पूर्णांक kmsdrm_load_refcount = 0;

व्योम SDL_KMSDRM_UnloadSymbols(व्योम)
{
    // Don't actually unload if more than one module is using the libs...
    अगर (kmsdrm_load_refcount > 0) {
        अगर (--kmsdrm_load_refcount == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            पूर्णांक i;
#पूर्ण_अगर

            // set all the function pointers to NULL.
#घोषणा SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#घोषणा SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = शून्य;
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = शून्य;
#घोषणा SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = शून्य;
#समावेश "SDL_kmsdrmsym.h"

#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            क्रम (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                अगर (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = शून्य;
                }
            }
#पूर्ण_अगर
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(व्योम)
{
    bool परिणाम = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    अगर (kmsdrm_load_refcount++ == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        पूर्णांक i;
        पूर्णांक *thismod = शून्य;
        क्रम (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            अगर (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#घोषणा SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#समावेश "SDL_kmsdrmsym.h"

#घोषणा SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#घोषणा SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#घोषणा SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#समावेश "SDL_kmsdrmsym.h"

        अगर ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic KMSDRM

#घोषणा SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#घोषणा SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#घोषणा SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#समावेश "SDL_kmsdrmsym.h"

#पूर्ण_अगर
    }

    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_KMSDRM
