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
#ضمن "SDL_internal.h"

#که_نه_تعریف_شوی SDL_x11dyn_h_
#تعریف_کړه SDL_x11dyn_h_

#ضمن <X11/Xlib.h>
#ضمن <X11/Xutil.h>
#ضمن <X11/Xatom.h>
#ضمن <X11/Xresource.h>

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#د_که_پای

// Apparently some X11 systems can't include this multiple times...
#که_نه_تعریف_شوی SDL_INCLUDED_XLIBINT_H
#تعریف_کړه SDL_INCLUDED_XLIBINT_H 1
#ضمن <X11/Xlibint.h>
#د_که_پای

#ضمن <X11/Xproto.h>
#ضمن <X11/extensions/Xext.h>

#که_نه_تعریف_شوی NO_SHARED_حافظه
#ضمن <sys/ipc.h>
#ضمن <sys/shm.h>
#ضمن <X11/extensions/XShm.h>
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XCURSOR
#ضمن <X11/Xcursor/Xcursor.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
#ضمن <X11/extensions/Xdbe.h>
#د_که_پای
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#ضمن <X11/extensions/XInput2.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
#ضمن <X11/extensions/Xfixes.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
#ضمن <X11/extensions/sync.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
#ضمن <X11/extensions/Xrandr.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#ضمن <X11/extensions/scrnsaver.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSHAPE
#ضمن <X11/extensions/shape.h>
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XTEST
#ضمن <X11/extensions/XTest.h>
#د_که_پای

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

// evil function signatures...
تعريفنوع Bool (*SDL_X11_XESet_Wire_منزل_Event_Ret_Type)(Display *, XEvent *, xEvent *);
تعريفنوع صحيح (*SDL_X11_XSynchronizeRetType)(Display *);
تعريفنوع حالت_2 (*SDL_X11_XESet_Event_منزل_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

خارجي bool SDL_X11_بارول_Symbols(فراغ);
خارجي فراغ SDL_X11_UnloadSymbols(فراغ);

// Declare all the function pointers and wrappers...
#تعریف_کړه SDL_X11_SYM(rc, fn, params) \
    تعريفنوع rc(*SDL_DYNX11FN_##fn) params;     \
    خارجي SDL_DYNX11FN_##fn X11_##fn;
#ضمن "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#تعریف_کړه SDL_X11_MODULE(modname) خارجي صحيح SDL_X11_HAVE_##modname;
#ضمن "SDL_x11sym.h"

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // !defined SDL_x11dyn_h_
