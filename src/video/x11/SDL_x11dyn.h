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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_x11dyn_h_
#define SDL_x11dyn_h_

#અન્તર્ભાવ <X11/Xlib.h>
#અન્તર્ભાવ <X11/Xutil.h>
#અન્તર્ભાવ <X11/Xatom.h>
#અન્તર્ભાવ <X11/Xresource.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#અન્તર્ભાવ <X11/XKBlib.h>
#endif

// Apparently some X11 systems can't include this multiple times...
#ifndef SDL_INCLUDED_XLIBINT_H
#define SDL_INCLUDED_XLIBINT_H 1
#અન્તર્ભાવ <X11/Xlibint.h>
#endif

#અન્તર્ભાવ <X11/Xproto.h>
#અન્તર્ભાવ <X11/extensions/Xext.h>

#ifndef NO_SHARED_MEMORY
#અન્તર્ભાવ <sys/ipc.h>
#અન્તર્ભાવ <sys/shm.h>
#અન્તર્ભાવ <X11/extensions/XShm.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
#અન્તર્ભાવ <X11/Xcursor/Xcursor.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
#અન્તર્ભાવ <X11/extensions/Xdbe.h>
#endif
#જો defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#અન્તર્ભાવ <X11/extensions/XInput2.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
#અન્તર્ભાવ <X11/extensions/Xfixes.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
#અન્તર્ભાવ <X11/extensions/sync.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#અન્તર્ભાવ <X11/extensions/Xrandr.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#અન્તર્ભાવ <X11/extensions/scrnsaver.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
#અન્તર્ભાવ <X11/extensions/shape.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
#અન્તર્ભાવ <X11/extensions/XTest.h>
#endif

#ifdef __cplusplus
બાહ્ય "C" {
#endif

// evil function signatures...
પ્રકારવ્યાખ્યા Bool (*SDL_X11_XESetWireToEventRetType)(Display *, XEvent *, xEvent *);
પ્રકારવ્યાખ્યા પૂર્ણાંક (*SDL_X11_XSynchronizeRetType)(Display *);
પ્રકારવ્યાખ્યા Status (*SDL_X11_XESetEventToWireRetType)(Display *, XEvent *, xEvent *);

બાહ્ય bool SDL_X11_LoadSymbols(શૂન્ય);
બાહ્ય શૂન્ય SDL_X11_UnloadSymbols(શૂન્ય);

// Declare all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) \
    પ્રકારવ્યાખ્યા rc(*SDL_DYNX11FN_##fn) params;     \
    બાહ્ય SDL_DYNX11FN_##fn X11_##fn;
#અન્તર્ભાવ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) બાહ્ય પૂર્ણાંક SDL_X11_HAVE_##modname;
#અન્તર્ભાવ "SDL_x11sym.h"

#ifdef __cplusplus
}
#endif

#endif // !defined SDL_x11dyn_h_
