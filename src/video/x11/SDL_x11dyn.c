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

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"

#ಯದಿ DEBUG_DYNAMIC_X11
#ಅನ್ತರ್ಭಾವ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_SharedObject *lib;
    ಧ್ರುವ ವರ್ಣ *libname;
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
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ರಿಕ್ತ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#ಅನ್ಯಥಾ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ರಿಕ್ತ
#endif

ಸ್ಥಿರ x11dynlib x11libs[] = {
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ಸ್ಥಿರ ಶೂನ್ಯ *X11_GetSym(ಧ್ರುವ ವರ್ಣ *fnname, ಪೂರ್ಣಾಙ್ಕ *pHasModule)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಶೂನ್ಯ *fn = ರಿಕ್ತ;
    ಪ್ರತಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
        ಯದಿ (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            ಯದಿ (fn) {
                ಭಙ್ಗ;
            }
        }
    }

#ಯದಿ DEBUG_DYNAMIC_X11
    ಯದಿ (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } ಅನ್ಯಥಾ {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    ಯದಿ (!fn) {
        *pHasModule = 0; // kill this module.
    }

    ಪ್ರತ್ಯಾಗಮ fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) ಪೂರ್ಣಾಙ್ಕ SDL_X11_HAVE_##modname = 0;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ x11_load_refcount = 0;

ಶೂನ್ಯ SDL_X11_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಯದಿ (x11_load_refcount > 0) {
        ಯದಿ (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            ಪೂರ್ಣಾಙ್ಕ i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = ರಿಕ್ತ;
            X11_XGetICValues = ರಿಕ್ತ;
            X11_XSetICValues = ರಿಕ್ತ;
            X11_XVaCreateNestedList = ರಿಕ್ತ;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            ಪ್ರತಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
                ಯದಿ (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ರಿಕ್ತ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(ಶೂನ್ಯ)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    ಯದಿ (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        ಪೂರ್ಣಾಙ್ಕ i;
        ಪೂರ್ಣಾಙ್ಕ *thismod = ರಿಕ್ತ;
        ಪ್ರತಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
            ಯದಿ (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

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

        ಯದಿ (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } ಅನ್ಯಥಾ {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#ಅನ್ಯಥಾ // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_X11
