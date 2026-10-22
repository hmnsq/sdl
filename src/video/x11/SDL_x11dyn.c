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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_DYNAMIC_X11 0

#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"

#ಆದರೆ DEBUG_DYNAMIC_X11
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_SharedObject *lib;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ x11dynlib x11libs[] = {
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ಸ್ಥಿರ ಶೂನ್ಯ *X11_GetSym(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fnname, ಪೂರ್ಣಾಂಕ *pHasModule)
{
    ಪೂರ್ಣಾಂಕ i;
    ಶೂನ್ಯ *fn = ಖಾಲಿ;
    ಗಾಗಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
        ಆದರೆ (x11libs[i].lib) {
            fn = SDL_ತುಂಬು_Function(x11libs[i].lib, fnname);
            ಆದರೆ (fn) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

#ಆದರೆ DEBUG_DYNAMIC_X11
    ಆದರೆ (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!fn) {
        *pHasModule = 0; // kill this module.
    }

    ಹಿಂತಿರುಗಿ fn;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname) ಪೂರ್ಣಾಂಕ SDL_X11_HAVE_##modname = 0;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ x11_ತುಂಬು_refcount = 0;

ಶೂನ್ಯ SDL_X11_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಆದರೆ (x11_ತುಂಬು_refcount > 0) {
        ಆದರೆ (--x11_ತುಂಬು_refcount == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC
            ಪೂರ್ಣಾಂಕ i;
#ಆದರೆ_ಅಂತ್ಯ

            // set all the function pointers to NULL.
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params) X11_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
            X11_XCreateIC = ಖಾಲಿ;
            X11_XGetICValues = ಖಾಲಿ;
            X11_XSetICValues = ಖಾಲಿ;
            X11_XVaCreateNestedList = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC
            ಗಾಗಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
                ಆದರೆ (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ಖಾಲಿ;
                }
            }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_ತುಂಬು_Symbols(ಶೂನ್ಯ)
{
    bool ಫಲಿತಾಂಶ = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    ಆದರೆ (x11_ತುಂಬು_refcount++ == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_DYNAMIC
        ಪೂರ್ಣಾಂಕ i;
        ಪೂರ್ಣಾಂಕ *thismod = ಖಾಲಿ;
        ಗಾಗಿ (i = 0; i < SDL_arraysize(x11libs); i++) {
            ಆದರೆ (x11libs[i].libname) {
                x11libs[i].lib = SDL_ತುಂಬು_Object(x11libs[i].libname);
            }
        }

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } ಇಲ್ಲದಿದ್ದರೆ {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            ಫಲಿತಾಂಶ = false;
        }

#ಇಲ್ಲದಿದ್ದರೆ // no dynamic X11

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
