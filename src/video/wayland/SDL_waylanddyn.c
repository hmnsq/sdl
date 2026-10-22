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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#ಅನ್ತರ್ಭಾವ "SDL_waylanddyn.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_SharedObject *lib;
    ಧ್ರುವ ವರ್ಣ *libname;
    ಧ್ರುವ ವರ್ಣ *hint;
    bool hint_default;
} waylanddynlib;

ಸ್ಥಿರ waylanddynlib waylandlibs[] = {
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ರಿಕ್ತ, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ರಿಕ್ತ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ರಿಕ್ತ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ರಿಕ್ತ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ರಿಕ್ತ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, false }
};

ಸ್ಥಿರ ಶೂನ್ಯ *WAYLAND_GetSym(ಧ್ರುವ ವರ್ಣ *fnname, ಪೂರ್ಣಾಙ್ಕ *pHasModule, bool required)
{
    ಶೂನ್ಯ *fn = ರಿಕ್ತ;
    waylanddynlib *dynlib;
    ಪ್ರತಿ (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        ಯದಿ (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            ಯದಿ (fn) {
                ಭಙ್ಗ;
            }
        }
    }

#ಯದಿ DEBUG_DYNAMIC_WAYLAND
    ಯದಿ (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } ಅನ್ಯಥಾ {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    ಯದಿ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ಪ್ರತ್ಯಾಗಮ fn;
}

#ಅನ್ಯಥಾ

#ಅನ್ತರ್ಭಾವ <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         ಪೂರ್ಣಾಙ್ಕ SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ರಿಕ್ತ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ wayland_load_refcount = 0;

ಶೂನ್ಯ SDL_WAYLAND_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಯದಿ (wayland_load_refcount > 0) {
        ಯದಿ (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ಪೂರ್ಣಾಙ್ಕ i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ರಿಕ್ತ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ರಿಕ್ತ;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ಪ್ರತಿ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                ಯದಿ (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ರಿಕ್ತ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(ಶೂನ್ಯ)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    ಯದಿ (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        ಪೂರ್ಣಾಙ್ಕ i;
        ಪೂರ್ಣಾಙ್ಕ *thismod = ರಿಕ್ತ;
        ಪ್ರತಿ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            ಯದಿ (waylandlibs[i].libname) {
                ಯದಿ (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    ಅನುವರ್ತ;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

        ಯದಿ (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } ಅನ್ಯಥಾ {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#ಅನ್ಯಥಾ // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#endif
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
