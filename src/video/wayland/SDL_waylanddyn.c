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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#ଅନ୍ତର୍ଭାଵ "SDL_waylanddyn.h"

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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_SharedObject *lib;
    ଅଚଳ ଅକ୍ଷର *libname;
    ଅଚଳ ଅକ୍ଷର *hint;
    bool hint_default;
} waylanddynlib;

ସ୍ଥିର waylanddynlib waylandlibs[] = {
    { ଖାଲି, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ଖାଲି, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ଖାଲି, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ଖାଲି, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ଖାଲି, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ଖାଲି, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ଖାଲି, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ଖାଲି, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ଖାଲି, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { ଖାଲି, ଖାଲି, ଖାଲି, false }
};

ସ୍ଥିର ଶୂନ୍ୟ *WAYLAND_GetSym(ଅଚଳ ଅକ୍ଷର *fnname, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pHasModule, bool required)
{
    ଶୂନ୍ୟ *fn = ଖାଲି;
    waylanddynlib *dynlib;
    ପାଇଁ (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        ଯଦି (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            ଯଦି (fn) {
                ଭାଙ୍ଗ;
            }
        }
    }

#ଯଦି DEBUG_DYNAMIC_WAYLAND
    ଯଦି (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } ଅନ୍ୟଥା {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    ଯଦି (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ଫେରନ୍ତୁ fn;
}

#ଅନ୍ୟଥା

#ଅନ୍ତର୍ଭାଵ <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ଖାଲି;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_waylandsym.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା wayland_load_refcount = 0;

ଶୂନ୍ୟ SDL_WAYLAND_UnloadSymbols(ଶୂନ୍ୟ)
{
    // Don't actually unload if more than one module is using the libs...
    ଯଦି (wayland_load_refcount > 0) {
        ଯଦି (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ଖାଲି;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ପାଇଁ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                ଯଦି (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ଖାଲି;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(ଶୂନ୍ୟ)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    ଯଦି (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା *thismod = ଖାଲି;
        ପାଇଁ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            ଯଦି (waylandlibs[i].libname) {
                ଯଦି (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    ଜାରି;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ଅନ୍ତର୍ଭାଵ "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#ଅନ୍ତର୍ଭାଵ "SDL_waylandsym.h"

        ଯଦି (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } ଅନ୍ୟଥା {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#ଅନ୍ୟଥା // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#ଅନ୍ତର୍ଭାଵ "SDL_waylandsym.h"

#endif
    }

    ଫେରନ୍ତୁ result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
