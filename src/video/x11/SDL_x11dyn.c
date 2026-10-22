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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_DYNAMIC_X11 0

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11dyn.h"

#ਜੇ DEBUG_DYNAMIC_X11
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_SharedObject *lib;
    ਅਚਲ ਅੱਖਰ *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ਨਿਰਾ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ਨਿਰਾ
#ਜੇ_ਅੰਤ

ਸਥਿਰ x11dynlib x11libs[] = {
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ਸਥਿਰ ਖਾਲੀ *X11_GetSym(ਅਚਲ ਅੱਖਰ *fnname, ਪੂਰਨ *pHasModule)
{
    ਪੂਰਨ i;
    ਖਾਲੀ *fn = ਨਿਰਾ;
    ਲਈ (i = 0; i < SDL_arraysize(x11libs); i++) {
        ਜੇ (x11libs[i].lib) {
            fn = SDL_ਲੱਦੋ_Function(x11libs[i].lib, fnname);
            ਜੇ (fn) {
                ਰੋਕੋ;
            }
        }
    }

#ਜੇ DEBUG_DYNAMIC_X11
    ਜੇ (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } ਨਹੀਂਤਾਂ {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!fn) {
        *pHasModule = 0; // kill this module.
    }

    ਵਾਪਸ fn;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname) ਪੂਰਨ SDL_X11_HAVE_##modname = 0;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

ਸਥਿਰ ਪੂਰਨ x11_ਲੱਦੋ_refcount = 0;

ਖਾਲੀ SDL_X11_UnloadSymbols(ਖਾਲੀ)
{
    // Don't actually unload if more than one module is using the libs...
    ਜੇ (x11_ਲੱਦੋ_refcount > 0) {
        ਜੇ (--x11_ਲੱਦੋ_refcount == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC
            ਪੂਰਨ i;
#ਜੇ_ਅੰਤ

            // set all the function pointers to NULL.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params) X11_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
            X11_XCreateIC = ਨਿਰਾ;
            X11_XGetICValues = ਨਿਰਾ;
            X11_XSetICValues = ਨਿਰਾ;
            X11_XVaCreateNestedList = ਨਿਰਾ;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC
            ਲਈ (i = 0; i < SDL_arraysize(x11libs); i++) {
                ਜੇ (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ਨਿਰਾ;
                }
            }
#ਜੇ_ਅੰਤ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_ਲੱਦੋ_Symbols(ਖਾਲੀ)
{
    bool ਨਤੀਜਾ = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    ਜੇ (x11_ਲੱਦੋ_refcount++ == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_DYNAMIC
        ਪੂਰਨ i;
        ਪੂਰਨ *thismod = ਨਿਰਾ;
        ਲਈ (i = 0; i < SDL_arraysize(x11libs); i++) {
            ਜੇ (x11libs[i].libname) {
                x11libs[i].lib = SDL_ਲੱਦੋ_Object(x11libs[i].libname);
            }
        }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#ਜੇ_ਅੰਤ

        ਜੇ (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } ਨਹੀਂਤਾਂ {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            ਨਤੀਜਾ = false;
        }

#ਨਹੀਂਤਾਂ // no dynamic X11

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
