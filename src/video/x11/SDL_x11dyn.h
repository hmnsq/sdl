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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_x11dyn_h_
#నిర్వచించు SDL_x11dyn_h_

#అన్తర్భావ <X11/Xlib.h>
#అన్తర్భావ <X11/Xutil.h>
#అన్తర్భావ <X11/Xatom.h>
#అన్తర్భావ <X11/Xresource.h>

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#అన్తర్భావ <X11/XKBlib.h>
#అయితే_ముగింపు

// Apparently some X11 systems can't include this multiple times...
#నిర్వచితం_కాకపోతే SDL_INCLUDED_XLIBINT_H
#నిర్వచించు SDL_INCLUDED_XLIBINT_H 1
#అన్తర్భావ <X11/Xlibint.h>
#అయితే_ముగింపు

#అన్తర్భావ <X11/Xproto.h>
#అన్తర్భావ <X11/extensions/Xext.h>

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
#అన్తర్భావ <sys/ipc.h>
#అన్తర్భావ <sys/shm.h>
#అన్తర్భావ <X11/extensions/XShm.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
#అన్తర్భావ <X11/Xcursor/Xcursor.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
#అన్తర్భావ <X11/extensions/Xdbe.h>
#అయితే_ముగింపు
#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#అన్తర్భావ <X11/extensions/XInput2.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
#అన్తర్భావ <X11/extensions/Xfixes.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
#అన్తర్భావ <X11/extensions/sync.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
#అన్తర్భావ <X11/extensions/Xrandr.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#అన్తర్భావ <X11/extensions/scrnsaver.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSHAPE
#అన్తర్భావ <X11/extensions/shape.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XTEST
#అన్తర్భావ <X11/extensions/XTest.h>
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

// evil function signatures...
రకనిర్వచనం Bool (*SDL_X11_XESet_Wire_గమ్యం_Event_Ret_Type)(Display *, XEvent *, xEvent *);
రకనిర్వచనం పూర్ణాంకం (*SDL_X11_XSynchronizeRetType)(Display *);
రకనిర్వచనం స్థితి_3 (*SDL_X11_XESet_Event_గమ్యం_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

బాహ్య bool SDL_X11_ఎక్కించు_Symbols(శూన్య);
బాహ్య శూన్య SDL_X11_UnloadSymbols(శూన్య);

// Declare all the function pointers and wrappers...
#నిర్వచించు SDL_X11_SYM(rc, fn, params) \
    రకనిర్వచనం rc(*SDL_DYNX11FN_##fn) params;     \
    బాహ్య SDL_DYNX11FN_##fn X11_##fn;
#అన్తర్భావ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#నిర్వచించు SDL_X11_MODULE(modname) బాహ్య పూర్ణాంకం SDL_X11_HAVE_##modname;
#అన్తర్భావ "SDL_x11sym.h"

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // !defined SDL_x11dyn_h_
