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

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#அந்தர்பாவ "SDL_x11dyn.h"

#எனில் DEBUG_DYNAMIC_X11
#அந்தர்பாவ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

வகைவரை கட்டமைப்பு
{
    SDL_SharedObject *lib;
    மாறிலி எழுத்து *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS வெற்று
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#இல்லையெனில்
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST வெற்று
#endif

நிலையான x11dynlib x11libs[] = {
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { வெற்று, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

நிலையான வெறுமை *X11_GetSym(மாறிலி எழுத்து *fnname, முழு *pHasModule)
{
    முழு i;
    வெறுமை *fn = வெற்று;
    க்கு (i = 0; i < SDL_arraysize(x11libs); i++) {
        எனில் (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            எனில் (fn) {
                நிறுத்து;
            }
        }
    }

#எனில் DEBUG_DYNAMIC_X11
    எனில் (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } இல்லையெனில் {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    எனில் (!fn) {
        *pHasModule = 0; // kill this module.
    }

    திரும்பு fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = வெற்று;
#அந்தர்பாவ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) முழு SDL_X11_HAVE_##modname = 0;
#அந்தர்பாவ "SDL_x11sym.h"

நிலையான முழு x11_load_refcount = 0;

வெறுமை SDL_X11_UnloadSymbols(வெறுமை)
{
    // Don't actually unload if more than one module is using the libs...
    எனில் (x11_load_refcount > 0) {
        எனில் (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            முழு i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = வெற்று;
#அந்தர்பாவ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = வெற்று;
            X11_XGetICValues = வெற்று;
            X11_XSetICValues = வெற்று;
            X11_XVaCreateNestedList = வெற்று;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            க்கு (i = 0; i < SDL_arraysize(x11libs); i++) {
                எனில் (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = வெற்று;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(வெறுமை)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    எனில் (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        முழு i;
        முழு *thismod = வெற்று;
        க்கு (i = 0; i < SDL_arraysize(x11libs); i++) {
            எனில் (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#அந்தர்பாவ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#அந்தர்பாவ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#endif

        எனில் (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } இல்லையெனில் {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#இல்லையெனில் // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#அந்தர்பாவ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_X11
