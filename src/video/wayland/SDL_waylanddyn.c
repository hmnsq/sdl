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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#অন্তর্ভাৱ "SDL_waylanddyn.h"

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

প্রকারনির্দেশ সংরচনা
{
    SDL_SharedObject *lib;
    ধ্রুৱ ৱর্ণ *libname;
    ধ্রুৱ ৱর্ণ *hint;
    bool hint_default;
} waylanddynlib;

স্থির waylanddynlib waylandlibs[] = {
    { রিক্ত, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, রিক্ত, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { রিক্ত, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, রিক্ত, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { রিক্ত, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, রিক্ত, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { রিক্ত, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, রিক্ত, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { রিক্ত, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { রিক্ত, রিক্ত, রিক্ত, false }
};

স্থির শূন্য *WAYLAND_GetSym(ধ্রুৱ ৱর্ণ *fnname, পূর্ণাঙ্ক *pHasModule, bool required)
{
    শূন্য *fn = রিক্ত;
    waylanddynlib *dynlib;
    বাবে (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        যদি (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            যদি (fn) {
                ভঙ্গ;
            }
        }
    }

#যদি DEBUG_DYNAMIC_WAYLAND
    যদি (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } অন্যথা {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    যদি (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ঘূৰাই fn;
}

#অন্যথা

#অন্তর্ভাৱ <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         পূর্ণাঙ্ক SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = রিক্ত;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_waylandsym.h"

স্থির পূর্ণাঙ্ক wayland_load_refcount = 0;

শূন্য SDL_WAYLAND_UnloadSymbols(শূন্য)
{
    // Don't actually unload if more than one module is using the libs...
    যদি (wayland_load_refcount > 0) {
        যদি (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            পূর্ণাঙ্ক i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = রিক্ত;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            বাবে (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                যদি (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = রিক্ত;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(শূন্য)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    যদি (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        পূর্ণাঙ্ক i;
        পূর্ণাঙ্ক *thismod = রিক্ত;
        বাবে (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            যদি (waylandlibs[i].libname) {
                যদি (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    অনুৱর্ত;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#অন্তর্ভাৱ "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#অন্তর্ভাৱ "SDL_waylandsym.h"

        যদি (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } অন্যথা {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#অন্যথা // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#অন্তর্ভাৱ "SDL_waylandsym.h"

#endif
    }

    ঘূৰাই result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
