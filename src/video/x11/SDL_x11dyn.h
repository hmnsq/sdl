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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_x11dyn_h_
#define SDL_x11dyn_h_

#অন্তর্ভাব <X11/Xlib.h>
#অন্তর্ভাব <X11/Xutil.h>
#অন্তর্ভাব <X11/Xatom.h>
#অন্তর্ভাব <X11/Xresource.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#অন্তর্ভাব <X11/XKBlib.h>
#endif

// Apparently some X11 systems can't include this multiple times...
#ifndef SDL_INCLUDED_XLIBINT_H
#define SDL_INCLUDED_XLIBINT_H 1
#অন্তর্ভাব <X11/Xlibint.h>
#endif

#অন্তর্ভাব <X11/Xproto.h>
#অন্তর্ভাব <X11/extensions/Xext.h>

#ifndef NO_SHARED_MEMORY
#অন্তর্ভাব <sys/ipc.h>
#অন্তর্ভাব <sys/shm.h>
#অন্তর্ভাব <X11/extensions/XShm.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
#অন্তর্ভাব <X11/Xcursor/Xcursor.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
#অন্তর্ভাব <X11/extensions/Xdbe.h>
#endif
#যদি defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#অন্তর্ভাব <X11/extensions/XInput2.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
#অন্তর্ভাব <X11/extensions/Xfixes.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
#অন্তর্ভাব <X11/extensions/sync.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#অন্তর্ভাব <X11/extensions/Xrandr.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#অন্তর্ভাব <X11/extensions/scrnsaver.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
#অন্তর্ভাব <X11/extensions/shape.h>
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
#অন্তর্ভাব <X11/extensions/XTest.h>
#endif

#ifdef __cplusplus
বাহ্য "C" {
#endif

// evil function signatures...
প্রকারনির্দেশ Bool (*SDL_X11_XESetWireToEventRetType)(Display *, XEvent *, xEvent *);
প্রকারনির্দেশ পূর্ণাঙ্ক (*SDL_X11_XSynchronizeRetType)(Display *);
প্রকারনির্দেশ Status (*SDL_X11_XESetEventToWireRetType)(Display *, XEvent *, xEvent *);

বাহ্য bool SDL_X11_LoadSymbols(শূন্য);
বাহ্য শূন্য SDL_X11_UnloadSymbols(শূন্য);

// Declare all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) \
    প্রকারনির্দেশ rc(*SDL_DYNX11FN_##fn) params;     \
    বাহ্য SDL_DYNX11FN_##fn X11_##fn;
#অন্তর্ভাব "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) বাহ্য পূর্ণাঙ্ক SDL_X11_HAVE_##modname;
#অন্তর্ভাব "SDL_x11sym.h"

#ifdef __cplusplus
}
#endif

#endif // !defined SDL_x11dyn_h_
