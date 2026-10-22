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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11dyn_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11dyn_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xutil.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xatom.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xresource.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/XKBlib.h>
#ਜੇ_ਅੰਤ

// Apparently some X11 systems can't include this multiple times...
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_INCLUDED_XLIBINT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_INCLUDED_XLIBINT_H 1
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlibint.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xproto.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/Xext.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/ipc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/shm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/XShm.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xcursor/Xcursor.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/Xdbe.h>
#ਜੇ_ਅੰਤ
#ਜੇ defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/XInput2.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/Xfixes.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/sync.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/Xrandr.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/scrnsaver.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSHAPE
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/shape.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XTEST
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/extensions/XTest.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

// evil function signatures...
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Bool (*SDL_X11_XESet_Wire_ਮੰਜ਼ਿਲ_Event_Ret_Type)(Display *, XEvent *, xEvent *);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ (*SDL_X11_XSynchronizeRetType)(Display *);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸਥਿਤੀ_2 (*SDL_X11_XESet_Event_ਮੰਜ਼ਿਲ_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

ਬਾਹਰੀ bool SDL_X11_ਲੱਦੋ_Symbols(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_X11_UnloadSymbols(ਖਾਲੀ);

// Declare all the function pointers and wrappers...
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_SYM(rc, fn, params) \
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ rc(*SDL_DYNX11FN_##fn) params;     \
    ਬਾਹਰੀ SDL_DYNX11FN_##fn X11_##fn;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_X11_MODULE(modname) ਬਾਹਰੀ ਪੂਰਨ SDL_X11_HAVE_##modname;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11sym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // !defined SDL_x11dyn_h_
