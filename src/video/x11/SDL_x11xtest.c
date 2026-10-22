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

#إذا defined(SDL_VIDEO_DRIVER_X11)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xtest.h"

ساكن bool xtest_initialized = false;

فراغ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#إذا 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->اندروني->display;
    صحيح event, error;
    صحيح opcode;

    إذا (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        أرجع;
    }

    xtest_initialized = true;
#جيڪڏهن_پورو
}

bool X11_XTestIsInitialized(فراغ)
{
    أرجع xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_دري *دري, عائم x, عائم y)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XTEST
    إذا (!X11_XTestIsInitialized()) {
        أرجع false;
    }

    Display *display = _this->اندروني->display;
    SDL_Display_معلومات *displaydata = دري ? SDL_Get_Display_Driver_معلومات_For_دري(دري) : SDL_Get_Display_Driver_معلومات(SDL_GetPrimaryDisplay());
    إذا (!displaydata) {
        أرجع false;
    }

    صحيح motion_x = (صحيح)SDL_roundf(x);
    صحيح motion_y = (صحيح)SDL_roundf(y);
    إذا (دري) {
        motion_x += دري->x;
        motion_y += دري->y;
    }

    إذا (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, Current_وقت)) {
        أرجع false;
    }
    X11_XSync(display, False);

    أرجع true;
#وإلا
    أرجع false;
#جيڪڏهن_پورو
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
