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

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#अन्तर्भाव "SDL_x11dyn.h"

#सचे DEBUG_DYNAMIC_X11
#अन्तर्भाव <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

प्रकारनिर्देश संरचना
{
    SDL_SharedObject *lib;
    ध्रुव वर्ण *libname;
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
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS रिक्त
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#अञ्ञथा
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST रिक्त
#endif

स्थिर x11dynlib x11libs[] = {
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

स्थिर शून्य *X11_GetSym(ध्रुव वर्ण *fnname, पूर्णाङ्क *pHasModule)
{
    पूर्णाङ्क i;
    शून्य *fn = रिक्त;
    अत्थाय (i = 0; i < SDL_arraysize(x11libs); i++) {
        सचे (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            सचे (fn) {
                भङ्ग;
            }
        }
    }

#सचे DEBUG_DYNAMIC_X11
    सचे (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } अञ्ञथा {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    सचे (!fn) {
        *pHasModule = 0; // kill this module.
    }

    पटिनिवत्त fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = रिक्त;
#अन्तर्भाव "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) पूर्णाङ्क SDL_X11_HAVE_##modname = 0;
#अन्तर्भाव "SDL_x11sym.h"

स्थिर पूर्णाङ्क x11_load_refcount = 0;

शून्य SDL_X11_UnloadSymbols(शून्य)
{
    // Don't actually unload if more than one module is using the libs...
    सचे (x11_load_refcount > 0) {
        सचे (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            पूर्णाङ्क i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = रिक्त;
#अन्तर्भाव "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = रिक्त;
            X11_XGetICValues = रिक्त;
            X11_XSetICValues = रिक्त;
            X11_XVaCreateNestedList = रिक्त;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            अत्थाय (i = 0; i < SDL_arraysize(x11libs); i++) {
                सचे (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = रिक्त;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(शून्य)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    सचे (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        पूर्णाङ्क i;
        पूर्णाङ्क *thismod = रिक्त;
        अत्थाय (i = 0; i < SDL_arraysize(x11libs); i++) {
            सचे (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#अन्तर्भाव "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#अन्तर्भाव "SDL_x11sym.h"

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

        सचे (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } अञ्ञथा {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#अञ्ञथा // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#अन्तर्भाव "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    पटिनिवत्त result;
}

#endif // SDL_VIDEO_DRIVER_X11
