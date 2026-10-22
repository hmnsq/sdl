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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#அந்தர்பாவ "SDL_waylanddyn.h"

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

வகைவரை கட்டமைப்பு
{
    SDL_SharedObject *lib;
    மாறிலி எழுத்து *libname;
    மாறிலி எழுத்து *hint;
    bool hint_default;
} waylanddynlib;

நிலையான waylanddynlib waylandlibs[] = {
    { வெற்று, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, வெற்று, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { வெற்று, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, வெற்று, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { வெற்று, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, வெற்று, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { வெற்று, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, வெற்று, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { வெற்று, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { வெற்று, வெற்று, வெற்று, false }
};

நிலையான வெறுமை *WAYLAND_GetSym(மாறிலி எழுத்து *fnname, முழு *pHasModule, bool required)
{
    வெறுமை *fn = வெற்று;
    waylanddynlib *dynlib;
    க்கு (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        எனில் (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            எனில் (fn) {
                நிறுத்து;
            }
        }
    }

#எனில் DEBUG_DYNAMIC_WAYLAND
    எனில் (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } இல்லையெனில் {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    எனில் (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    திரும்பு fn;
}

#இல்லையெனில்

#அந்தர்பாவ <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         முழு SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = வெற்று;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = வெற்று;
#அந்தர்பாவ "SDL_waylandsym.h"

நிலையான முழு wayland_load_refcount = 0;

வெறுமை SDL_WAYLAND_UnloadSymbols(வெறுமை)
{
    // Don't actually unload if more than one module is using the libs...
    எனில் (wayland_load_refcount > 0) {
        எனில் (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            முழு i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = வெற்று;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = வெற்று;
#அந்தர்பாவ "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            க்கு (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                எனில் (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = வெற்று;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(வெறுமை)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    எனில் (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        முழு i;
        முழு *thismod = வெற்று;
        க்கு (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            எனில் (waylandlibs[i].libname) {
                எனில் (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    தொடர்;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#அந்தர்பாவ "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#அந்தர்பாவ "SDL_waylandsym.h"

        எனில் (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } இல்லையெனில் {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#இல்லையெனில் // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#அந்தர்பாவ "SDL_waylandsym.h"

#endif
    }

    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
