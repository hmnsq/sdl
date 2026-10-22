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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#تعریف_کرو DEBUG_DYNAMIC_X11 0

#شامل "SDL_x11dyn.h"

#اگر DEBUG_DYNAMIC_X11
#شامل <stdio.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC

قسمتعریف ساخت
{
    SDL_SharedObject *lib;
    ثابت حرف *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS تہی
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ترجیح_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#ورنہ
#تعریف_کرو SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST تہی
#اگر_ختم

ساکن x11dynlib x11libs[] = {
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { تہی, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ساکن خالی *X11_GetSym(ثابت حرف *fnname, صحیح *pHasModule)
{
    صحیح i;
    خالی *fn = تہی;
    برائے (i = 0; i < SDL_arraysize(x11libs); i++) {
        اگر (x11libs[i].lib) {
            fn = SDL_بھرو_Function(x11libs[i].lib, fnname);
            اگر (fn) {
                توڑو;
            }
        }
    }

#اگر DEBUG_DYNAMIC_X11
    اگر (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } ورنہ {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#اگر_ختم

    اگر (!fn) {
        *pHasModule = 0; // kill this module.
    }

    واپس fn;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#تعریف_کرو SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = تہی;
#شامل "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#تعریف_کرو SDL_X11_MODULE(modname) صحیح SDL_X11_HAVE_##modname = 0;
#شامل "SDL_x11sym.h"

ساکن صحیح x11_بھرو_refcount = 0;

خالی SDL_X11_UnloadSymbols(خالی)
{
    // Don't actually unload if more than one module is using the libs...
    اگر (x11_بھرو_refcount > 0) {
        اگر (--x11_بھرو_refcount == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC
            صحیح i;
#اگر_ختم

            // set all the function pointers to NULL.
#تعریف_کرو SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#تعریف_کرو SDL_X11_SYM(rc, fn, params) X11_##fn = تہی;
#شامل "SDL_x11sym.h"

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
            X11_XCreateIC = تہی;
            X11_XGetICValues = تہی;
            X11_XSetICValues = تہی;
            X11_XVaCreateNestedList = تہی;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC
            برائے (i = 0; i < SDL_arraysize(x11libs); i++) {
                اگر (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = تہی;
                }
            }
#اگر_ختم
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_بھرو_Symbols(خالی)
{
    bool نتیجہ = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    اگر (x11_بھرو_refcount++ == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_DYNAMIC
        صحیح i;
        صحیح *thismod = تہی;
        برائے (i = 0; i < SDL_arraysize(x11libs); i++) {
            اگر (x11libs[i].libname) {
                x11libs[i].lib = SDL_بھرو_Object(x11libs[i].libname);
            }
        }

#تعریف_کرو SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#شامل "SDL_x11sym.h"

#تعریف_کرو SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#تعریف_کرو SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#شامل "SDL_x11sym.h"

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#اگر_ختم

        اگر (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } ورنہ {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            نتیجہ = false;
        }

#ورنہ // no dynamic X11

#تعریف_کرو SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#تعریف_کرو SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#شامل "SDL_x11sym.h"

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#اگر_ختم
#اگر_ختم
    }

    واپس نتیجہ;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
