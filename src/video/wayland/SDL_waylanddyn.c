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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#నిర్వచించు DEBUG_DYNAMIC_WAYLAND 0

#అన్తర్భావ "SDL_waylanddyn.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం
{
    SDL_SharedObject *lib;
    స్థిరరాశి అక్షరం *libname;
    స్థిరరాశి అక్షరం *hint;
    bool hint_default;
} waylanddynlib;

స్థిర waylanddynlib waylandlibs[] = {
    { ఖాళీ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ఖాళీ, false },
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ఖాళీ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ఖాళీ, false },
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ఖాళీ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ఖాళీ, false },
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ఖాళీ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ఖాళీ, false },
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ఖాళీ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#అయితే_ముగింపు
    { ఖాళీ, ఖాళీ, ఖాళీ, false }
};

స్థిర శూన్య *WAYLAND_GetSym(స్థిరరాశి అక్షరం *fnname, పూర్ణాంకం *pHasModule, bool required)
{
    శూన్య *fn = ఖాళీ;
    waylanddynlib *dynlib;
    కొరకు (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        ఒకవేళ (dynlib->lib) {
            fn = SDL_ఎక్కించు_Function(dynlib->lib, fnname);
            ఒకవేళ (fn) {
                ఆపు;
            }
        }
    }

#ఒకవేళ DEBUG_DYNAMIC_WAYLAND
    ఒకవేళ (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } లేకపోతే {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#అయితే_ముగింపు

    ఒకవేళ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    తిరిగి fn;
}

#లేకపోతే

#అన్తర్భావ <wayland-egl.h>

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#నిర్వచించు SDL_WAYLAND_MODULE(modname)         పూర్ణాంకం SDL_WAYLAND_HAVE_##modname = 0;
#నిర్వచించు SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ఖాళీ;
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ఖాళీ;
#అన్తర్భావ "SDL_waylandsym.h"

స్థిర పూర్ణాంకం wayland_ఎక్కించు_refcount = 0;

శూన్య SDL_WAYLAND_UnloadSymbols(శూన్య)
{
    // Don't actually unload if more than one module is using the libs...
    ఒకవేళ (wayland_ఎక్కించు_refcount > 0) {
        ఒకవేళ (--wayland_ఎక్కించు_refcount == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            పూర్ణాంకం i;
#అయితే_ముగింపు

            // set all the function pointers to NULL.
#నిర్వచించు SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#నిర్వచించు SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ఖాళీ;
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ఖాళీ;
#అన్తర్భావ "SDL_waylandsym.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            కొరకు (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                ఒకవేళ (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ఖాళీ;
                }
            }
#అయితే_ముగింపు
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_ఎక్కించు_Symbols(శూన్య)
{
    bool ఫలితం = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    ఒకవేళ (wayland_ఎక్కించు_refcount++ == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        పూర్ణాంకం i;
        పూర్ణాంకం *thismod = ఖాళీ;
        కొరకు (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            ఒకవేళ (waylandlibs[i].libname) {
                ఒకవేళ (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    కొనసాగు;
                }
                waylandlibs[i].lib = SDL_ఎక్కించు_Object(waylandlibs[i].libname);
            }
        }

#నిర్వచించు SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#అన్తర్భావ "SDL_waylandsym.h"

#నిర్వచించు SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#నిర్వచించు SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#అన్తర్భావ "SDL_waylandsym.h"

        ఒకవేళ (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } లేకపోతే {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            ఫలితం = false;
        }

#లేకపోతే // no dynamic WAYLAND

#నిర్వచించు SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#నిర్వచించు SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#అన్తర్భావ "SDL_waylandsym.h"

#అయితే_ముగింపు
    }

    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
