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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11dyn_h_
#घोषणा SDL_x11dyn_h_

#समावेश <X11/Xlib.h>
#समावेश <X11/Xutil.h>
#समावेश <X11/Xatom.h>
#समावेश <X11/Xresource.h>

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#समावेश <X11/XKBlib.h>
#पूर्ण_अगर

// Apparently some X11 systems can't include this multiple times...
#अगर_अघोषित SDL_INCLUDED_XLIBINT_H
#घोषणा SDL_INCLUDED_XLIBINT_H 1
#समावेश <X11/Xlibint.h>
#पूर्ण_अगर

#समावेश <X11/Xproto.h>
#समावेश <X11/extensions/Xext.h>

#अगर_अघोषित NO_SHARED_MEMORY
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <X11/extensions/XShm.h>
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
#समावेश <X11/Xcursor/Xcursor.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
#समावेश <X11/extensions/Xdbe.h>
#पूर्ण_अगर
#अगर defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#समावेश <X11/extensions/XInput2.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
#समावेश <X11/extensions/Xfixes.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
#समावेश <X11/extensions/sync.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
#समावेश <X11/extensions/Xrandr.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#समावेश <X11/extensions/scrnsaver.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSHAPE
#समावेश <X11/extensions/shape.h>
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XTEST
#समावेश <X11/extensions/XTest.h>
#पूर्ण_अगर

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

// evil function signatures...
प्रकार Bool (*SDL_X11_XESetWireToEventRetType)(Display *, XEvent *, xEvent *);
प्रकार पूर्णांक (*SDL_X11_XSynchronizeRetType)(Display *);
प्रकार Status (*SDL_X11_XESetEventToWireRetType)(Display *, XEvent *, xEvent *);

बाह्य bool SDL_X11_LoadSymbols(व्योम);
बाह्य व्योम SDL_X11_UnloadSymbols(व्योम);

// Declare all the function pointers and wrappers...
#घोषणा SDL_X11_SYM(rc, fn, params) \
    प्रकार rc(*SDL_DYNX11FN_##fn) params;     \
    बाह्य SDL_DYNX11FN_##fn X11_##fn;
#समावेश "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#घोषणा SDL_X11_MODULE(modname) बाह्य पूर्णांक SDL_X11_HAVE_##modname;
#समावेश "SDL_x11sym.h"

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // !defined SDL_x11dyn_h_
