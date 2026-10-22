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

#ifndef SDL_x11dyn_h_
#define SDL_x11dyn_h_

#شامل <X11/Xlib.h>
#شامل <X11/Xutil.h>
#شامل <X11/Xatom.h>
#شامل <X11/Xresource.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#شامل <X11/XKBlib.h>
#endif

// Apparently some X11 systems can't include this multiple times...
#ifndef SDL_INCLUDED_XLIBINT_H
#define SDL_INCLUDED_XLIBINT_H 1
#شامل <X11/Xlibint.h>
#endif

#شامل <X11/Xproto.h>
#شامل <X11/extensions/Xext.h>

#ifndef NO_SHARED_MEMORY
#شامل <sys/ipc.h>
#شامل <sys/shm.h>
#شامل <X11/extensions/XShm.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
#شامل <X11/Xcursor/Xcursor.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
#شامل <X11/extensions/Xdbe.h>
#endif
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#شامل <X11/extensions/XInput2.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
#شامل <X11/extensions/Xfixes.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
#شامل <X11/extensions/sync.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#شامل <X11/extensions/Xrandr.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#شامل <X11/extensions/scrnsaver.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
#شامل <X11/extensions/shape.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
#شامل <X11/extensions/XTest.h>
#endif

#ifdef __cplusplus
بیرونی "C" {
#endif

// evil function signatures...
تعریفنوع Bool (*SDL_X11_XESetWireToEventRetType)(Display *, XEvent *, xEvent *);
تعریفنوع صحیح (*SDL_X11_XSynchronizeRetType)(Display *);
تعریفنوع Status (*SDL_X11_XESetEventToWireRetType)(Display *, XEvent *, xEvent *);

بیرونی bool SDL_X11_LoadSymbols(تهی);
بیرونی تهی SDL_X11_UnloadSymbols(تهی);

// Declare all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) \
    تعریفنوع rc(*SDL_DYNX11FN_##fn) params;     \
    بیرونی SDL_DYNX11FN_##fn X11_##fn;
#شامل "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) بیرونی صحیح SDL_X11_HAVE_##modname;
#شامل "SDL_x11sym.h"

#ifdef __cplusplus
}
#endif

#endif // !defined SDL_x11dyn_h_
