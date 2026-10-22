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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#شامل "SDL_x11dyn.h"

#اگر DEBUG_DYNAMIC_X11
#شامل <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

تعریفنوع ساختار
{
    SDL_SharedObject *lib;
    ثابت نویسه *libname;
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
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS پوچ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#وگرنه
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST پوچ
#endif

ایستا x11dynlib x11libs[] = {
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { پوچ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ایستا تهی *X11_GetSym(ثابت نویسه *fnname, صحیح *pHasModule)
{
    صحیح i;
    تهی *fn = پوچ;
    برای (i = 0; i < SDL_arraysize(x11libs); i++) {
        اگر (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            اگر (fn) {
                بشکن;
            }
        }
    }

#اگر DEBUG_DYNAMIC_X11
    اگر (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } وگرنه {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    اگر (!fn) {
        *pHasModule = 0; // kill this module.
    }

    بازگشت fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = پوچ;
#شامل "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) صحیح SDL_X11_HAVE_##modname = 0;
#شامل "SDL_x11sym.h"

ایستا صحیح x11_load_refcount = 0;

تهی SDL_X11_UnloadSymbols(تهی)
{
    // Don't actually unload if more than one module is using the libs...
    اگر (x11_load_refcount > 0) {
        اگر (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            صحیح i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = پوچ;
#شامل "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = پوچ;
            X11_XGetICValues = پوچ;
            X11_XSetICValues = پوچ;
            X11_XVaCreateNestedList = پوچ;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            برای (i = 0; i < SDL_arraysize(x11libs); i++) {
                اگر (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = پوچ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(تهی)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    اگر (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        صحیح i;
        صحیح *thismod = پوچ;
        برای (i = 0; i < SDL_arraysize(x11libs); i++) {
            اگر (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#شامل "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#شامل "SDL_x11sym.h"

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

        اگر (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } وگرنه {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#وگرنه // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#شامل "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    بازگشت result;
}

#endif // SDL_VIDEO_DRIVER_X11
