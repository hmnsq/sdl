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

#यदि_अपरिभाषितम् SDL_x11dyn_h_
#परिभाषय SDL_x11dyn_h_

#अन्तर्भाव <X11/Xlib.h>
#अन्तर्भाव <X11/Xutil.h>
#अन्तर्भाव <X11/Xatom.h>
#अन्तर्भाव <X11/Xresource.h>

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#अन्तर्भाव <X11/XKBlib.h>
#यदि_अन्तः

// Apparently some X11 systems can't include this multiple times...
#यदि_अपरिभाषितम् SDL_INCLUDED_XLIBINT_H
#परिभाषय SDL_INCLUDED_XLIBINT_H 1
#अन्तर्भाव <X11/Xlibint.h>
#यदि_अन्तः

#अन्तर्भाव <X11/Xproto.h>
#अन्तर्भाव <X11/extensions/Xext.h>

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
#अन्तर्भाव <sys/ipc.h>
#अन्तर्भाव <sys/shm.h>
#अन्तर्भाव <X11/extensions/XShm.h>
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
#अन्तर्भाव <X11/Xcursor/Xcursor.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
#अन्तर्भाव <X11/extensions/Xdbe.h>
#यदि_अन्तः
#यदि defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#अन्तर्भाव <X11/extensions/XInput2.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
#अन्तर्भाव <X11/extensions/Xfixes.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
#अन्तर्भाव <X11/extensions/sync.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
#अन्तर्भाव <X11/extensions/Xrandr.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#अन्तर्भाव <X11/extensions/scrnsaver.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSHAPE
#अन्तर्भाव <X11/extensions/shape.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XTEST
#अन्तर्भाव <X11/extensions/XTest.h>
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

// evil function signatures...
प्रकारनिर्देश Bool (*SDL_X11_XESet_Wire_गन्तव्यम्_Event_Ret_Type)(Display *, XEvent *, xEvent *);
प्रकारनिर्देश पूर्णाङ्क (*SDL_X11_XSynchronizeRetType)(Display *);
प्रकारनिर्देश स्थितिः_2 (*SDL_X11_XESet_Event_गन्तव्यम्_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

बाह्य bool SDL_X11_आरोपय_Symbols(शून्य);
बाह्य शून्य SDL_X11_UnloadSymbols(शून्य);

// Declare all the function pointers and wrappers...
#परिभाषय SDL_X11_SYM(rc, fn, params) \
    प्रकारनिर्देश rc(*SDL_DYNX11FN_##fn) params;     \
    बाह्य SDL_DYNX11FN_##fn X11_##fn;
#अन्तर्भाव "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#परिभाषय SDL_X11_MODULE(modname) बाह्य पूर्णाङ्क SDL_X11_HAVE_##modname;
#अन्तर्भाव "SDL_x11sym.h"

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // !defined SDL_x11dyn_h_
