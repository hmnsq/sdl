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

#اگر_غیر_تعریف_شدہ SDL_x11dyn_h_
#تعریف_کرو SDL_x11dyn_h_

#شامل <X11/Xlib.h>
#شامل <X11/Xutil.h>
#شامل <X11/Xatom.h>
#شامل <X11/Xresource.h>

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#شامل <X11/XKBlib.h>
#اگر_ختم

// Apparently some X11 systems can't include this multiple times...
#اگر_غیر_تعریف_شدہ SDL_INCLUDED_XLIBINT_H
#تعریف_کرو SDL_INCLUDED_XLIBINT_H 1
#شامل <X11/Xlibint.h>
#اگر_ختم

#شامل <X11/Xproto.h>
#شامل <X11/extensions/Xext.h>

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
#شامل <sys/ipc.h>
#شامل <sys/shm.h>
#شامل <X11/extensions/XShm.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
#شامل <X11/Xcursor/Xcursor.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
#شامل <X11/extensions/Xdbe.h>
#اگر_ختم
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#شامل <X11/extensions/XInput2.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
#شامل <X11/extensions/Xfixes.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
#شامل <X11/extensions/sync.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
#شامل <X11/extensions/Xrandr.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#شامل <X11/extensions/scrnsaver.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
#شامل <X11/extensions/shape.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
#شامل <X11/extensions/XTest.h>
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

// evil function signatures...
قسمتعریف Bool (*SDL_X11_XESet_Wire_مقصد_Event_Ret_Type)(Display *, XEvent *, xEvent *);
قسمتعریف صحیح (*SDL_X11_XSynchronizeRetType)(Display *);
قسمتعریف حالت_3 (*SDL_X11_XESet_Event_مقصد_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

خارجی bool SDL_X11_بھرو_Symbols(خالی);
خارجی خالی SDL_X11_UnloadSymbols(خالی);

// Declare all the function pointers and wrappers...
#تعریف_کرو SDL_X11_SYM(rc, fn, params) \
    قسمتعریف rc(*SDL_DYNX11FN_##fn) params;     \
    خارجی SDL_DYNX11FN_##fn X11_##fn;
#شامل "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#تعریف_کرو SDL_X11_MODULE(modname) خارجی صحیح SDL_X11_HAVE_##modname;
#شامل "SDL_x11sym.h"

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // !defined SDL_x11dyn_h_
