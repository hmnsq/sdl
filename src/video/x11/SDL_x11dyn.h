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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11dyn_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11dyn_h_

#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ <X11/Xutil.h>
#ಅನ್ತರ್ಭಾವ <X11/Xatom.h>
#ಅನ್ತರ್ಭಾವ <X11/Xresource.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ಅನ್ತರ್ಭಾವ <X11/XKBlib.h>
#ಆದರೆ_ಅಂತ್ಯ

// Apparently some X11 systems can't include this multiple times...
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_INCLUDED_XLIBINT_H
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_INCLUDED_XLIBINT_H 1
#ಅನ್ತರ್ಭಾವ <X11/Xlibint.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <X11/Xproto.h>
#ಅನ್ತರ್ಭಾವ <X11/extensions/Xext.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
#ಅನ್ತರ್ಭಾವ <sys/ipc.h>
#ಅನ್ತರ್ಭಾವ <sys/shm.h>
#ಅನ್ತರ್ಭಾವ <X11/extensions/XShm.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
#ಅನ್ತರ್ಭಾವ <X11/Xcursor/Xcursor.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
#ಅನ್ತರ್ಭಾವ <X11/extensions/Xdbe.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11_XINPUT2) || defined(SDL_VIDEO_DRIVER_X11_XFIXES)
#ಅನ್ತರ್ಭಾವ <X11/extensions/XInput2.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
#ಅನ್ತರ್ಭಾವ <X11/extensions/Xfixes.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
#ಅನ್ತರ್ಭಾವ <X11/extensions/sync.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
#ಅನ್ತರ್ಭಾವ <X11/extensions/Xrandr.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
#ಅನ್ತರ್ಭಾವ <X11/extensions/scrnsaver.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSHAPE
#ಅನ್ತರ್ಭಾವ <X11/extensions/shape.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XTEST
#ಅನ್ತರ್ಭಾವ <X11/extensions/XTest.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

// evil function signatures...
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Bool (*SDL_X11_XESet_Wire_ಗಮ್ಯ_Event_Ret_Type)(Display *, XEvent *, xEvent *);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*SDL_X11_XSynchronizeRetType)(Display *);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿತಿ_3 (*SDL_X11_XESet_Event_ಗಮ್ಯ_Wire_Ret_Type)(Display *, XEvent *, xEvent *);

ಬಾಹ್ಯ bool SDL_X11_ತುಂಬು_Symbols(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_X11_UnloadSymbols(ಶೂನ್ಯ);

// Declare all the function pointers and wrappers...
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params) \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ rc(*SDL_DYNX11FN_##fn) params;     \
    ಬಾಹ್ಯ SDL_DYNX11FN_##fn X11_##fn;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname) ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ SDL_X11_HAVE_##modname;
#ಅನ್ತರ್ಭಾವ "SDL_x11sym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // !defined SDL_x11dyn_h_
