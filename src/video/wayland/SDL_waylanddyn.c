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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#परिभाषय DEBUG_DYNAMIC_WAYLAND 0

#अन्तर्भाव "SDL_waylanddyn.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#यदि_अन्तः

प्रकारनिर्देश संरचना
{
    SDL_SharedObject *lib;
    ध्रुव वर्ण *libname;
    ध्रुव वर्ण *hint;
    bool hint_default;
} waylanddynlib;

स्थिर waylanddynlib waylandlibs[] = {
    { रिक्त, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, रिक्त, false },
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { रिक्त, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, रिक्त, false },
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { रिक्त, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, रिक्त, false },
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { रिक्त, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, रिक्त, false },
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { रिक्त, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#यदि_अन्तः
    { रिक्त, रिक्त, रिक्त, false }
};

स्थिर शून्य *WAYLAND_GetSym(ध्रुव वर्ण *fnname, पूर्णाङ्क *pHasModule, bool required)
{
    शून्य *fn = रिक्त;
    waylanddynlib *dynlib;
    प्रति (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        यदि (dynlib->lib) {
            fn = SDL_आरोपय_Function(dynlib->lib, fnname);
            यदि (fn) {
                भङ्ग;
            }
        }
    }

#यदि DEBUG_DYNAMIC_WAYLAND
    यदि (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } अन्यथा {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#यदि_अन्तः

    यदि (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    प्रत्यागम fn;
}

#अन्यथा

#अन्तर्भाव <wayland-egl.h>

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#परिभाषय SDL_WAYLAND_MODULE(modname)         पूर्णाङ्क SDL_WAYLAND_HAVE_##modname = 0;
#परिभाषय SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = रिक्त;
#परिभाषय SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = रिक्त;
#अन्तर्भाव "SDL_waylandsym.h"

स्थिर पूर्णाङ्क wayland_आरोपय_refcount = 0;

शून्य SDL_WAYLAND_UnloadSymbols(शून्य)
{
    // Don't actually unload if more than one module is using the libs...
    यदि (wayland_आरोपय_refcount > 0) {
        यदि (--wayland_आरोपय_refcount == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            पूर्णाङ्क i;
#यदि_अन्तः

            // set all the function pointers to NULL.
#परिभाषय SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#परिभाषय SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = रिक्त;
#परिभाषय SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = रिक्त;
#अन्तर्भाव "SDL_waylandsym.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            प्रति (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                यदि (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = रिक्त;
                }
            }
#यदि_अन्तः
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_आरोपय_Symbols(शून्य)
{
    bool परिणाम = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    यदि (wayland_आरोपय_refcount++ == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        पूर्णाङ्क i;
        पूर्णाङ्क *thismod = रिक्त;
        प्रति (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            यदि (waylandlibs[i].libname) {
                यदि (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    अनुवर्त;
                }
                waylandlibs[i].lib = SDL_आरोपय_Object(waylandlibs[i].libname);
            }
        }

#परिभाषय SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#अन्तर्भाव "SDL_waylandsym.h"

#परिभाषय SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#परिभाषय SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#परिभाषय SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#अन्तर्भाव "SDL_waylandsym.h"

        यदि (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic WAYLAND

#परिभाषय SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#परिभाषय SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#परिभाषय SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#अन्तर्भाव "SDL_waylandsym.h"

#यदि_अन्तः
    }

    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
