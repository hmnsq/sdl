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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#تعریف_کرو DEBUG_DYNAMIC_WAYLAND 0

#شامل "SDL_waylanddyn.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#اگر_ختم

قسمتعریف ساخت
{
    SDL_SharedObject *lib;
    ثابت حرف *libname;
    ثابت حرف *hint;
    bool hint_default;
} waylanddynlib;

ساکن waylanddynlib waylandlibs[] = {
    { تہی, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, تہی, false },
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { تہی, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, تہی, false },
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { تہی, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, تہی, false },
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { تہی, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, تہی, false },
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { تہی, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#اگر_ختم
    { تہی, تہی, تہی, false }
};

ساکن خالی *WAYLAND_GetSym(ثابت حرف *fnname, صحیح *pHasModule, bool required)
{
    خالی *fn = تہی;
    waylanddynlib *dynlib;
    برائے (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        اگر (dynlib->lib) {
            fn = SDL_بھرو_Function(dynlib->lib, fnname);
            اگر (fn) {
                توڑو;
            }
        }
    }

#اگر DEBUG_DYNAMIC_WAYLAND
    اگر (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } ورنہ {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#اگر_ختم

    اگر (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    واپس fn;
}

#ورنہ

#شامل <wayland-egl.h>

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#تعریف_کرو SDL_WAYLAND_MODULE(modname)         صحیح SDL_WAYLAND_HAVE_##modname = 0;
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = تہی;
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = تہی;
#شامل "SDL_waylandsym.h"

ساکن صحیح wayland_بھرو_refcount = 0;

خالی SDL_WAYLAND_UnloadSymbols(خالی)
{
    // Don't actually unload if more than one module is using the libs...
    اگر (wayland_بھرو_refcount > 0) {
        اگر (--wayland_بھرو_refcount == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            صحیح i;
#اگر_ختم

            // set all the function pointers to NULL.
#تعریف_کرو SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = تہی;
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = تہی;
#شامل "SDL_waylandsym.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            برائے (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                اگر (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = تہی;
                }
            }
#اگر_ختم
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_بھرو_Symbols(خالی)
{
    bool نتیجہ = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    اگر (wayland_بھرو_refcount++ == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        صحیح i;
        صحیح *thismod = تہی;
        برائے (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            اگر (waylandlibs[i].libname) {
                اگر (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    جاری;
                }
                waylandlibs[i].lib = SDL_بھرو_Object(waylandlibs[i].libname);
            }
        }

#تعریف_کرو SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#شامل "SDL_waylandsym.h"

#تعریف_کرو SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#شامل "SDL_waylandsym.h"

        اگر (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } ورنہ {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            نتیجہ = false;
        }

#ورنہ // no dynamic WAYLAND

#تعریف_کرو SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#شامل "SDL_waylandsym.h"

#اگر_ختم
    }

    واپس نتیجہ;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
