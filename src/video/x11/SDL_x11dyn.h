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

#ifndef SDL_x11dyn_h_
#define SDL_x11dyn_h_

#அந்தர்பாவ <X11/Xlib.h>
#அந்தர்பாவ <X11/Xutil.h>
#அந்தர்பாவ <X11/Xatom.h>
#அந்தர்பாவ <X11/Xresource.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#அந்தர்பாவ <X11/XKBlib.h>
#endif

// Apparently some X11 systems can't include this multiple times...
#ifndef SDL_INCLUDED_XLIBINT_H
#define SDL_INCLUDED_XLIBINT_H 1
#அந்தர்பாவ <X11/Xlibint.h>
#endif

#அந்தர்பாவ <X11/Xproto.h>
#அந்தர்பாவ <X11/extensions/Xext.h>

#ifndef NO_SHARED_MEMORY
#அந்தர்பாவ <sys/ipc.h>
#அந்தர்பாவ <sys/shm.h>
#அந்தர்பாவ <X11/extensions/XShm.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
#அந்தர்பாவ <X11/Xcursor/Xcursor.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
#அந்தர்பாவ <X11/extensions/Xdbe.h>
#endif
#எனில் defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#அந்தர்பாவ <X11/extensions/XInput2.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
#அந்தர்பாவ <X11/extensions/Xfixes.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
#அந்தர்பாவ <X11/extensions/sync.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#அந்தர்பாவ <X11/extensions/Xrandr.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#அந்தர்பாவ <X11/extensions/scrnsaver.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
#அந்தர்பாவ <X11/extensions/shape.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
#அந்தர்பாவ <X11/extensions/XTest.h>
#endif

#ifdef __cplusplus
வெளி "C" {
#endif

// evil function signatures...
வகைவரை Bool (*SDL_X11_XESetWireToEventRetType)(Display *, XEvent *, xEvent *);
வகைவரை முழு (*SDL_X11_XSynchronizeRetType)(Display *);
வகைவரை Status (*SDL_X11_XESetEventToWireRetType)(Display *, XEvent *, xEvent *);

வெளி bool SDL_X11_LoadSymbols(வெறுமை);
வெளி வெறுமை SDL_X11_UnloadSymbols(வெறுமை);

// Declare all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) \
    வகைவரை rc(*SDL_DYNX11FN_##fn) params;     \
    வெளி SDL_DYNX11FN_##fn X11_##fn;
#அந்தர்பாவ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) வெளி முழு SDL_X11_HAVE_##modname;
#அந்தர்பாவ "SDL_x11sym.h"

#ifdef __cplusplus
}
#endif

#endif // !defined SDL_x11dyn_h_
