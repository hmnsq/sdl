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

#אם defined(SDL_VIDEO_DRIVER_X11)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xtest.h"

ساكن bool xtest_initialized = false;

فراغ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#אם 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    صحيح event, error;
    صحيح opcode;

    אם (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        החזר;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(فراغ)
{
    החזר xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, عائم x, عائم y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    אם (!X11_XTestIsInitialized()) {
        החזר false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    אם (!displaydata) {
        החזר false;
    }

    صحيح motion_x = (صحيح)SDL_roundf(x);
    صحيح motion_y = (صحيح)SDL_roundf(y);
    אם (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    אם (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        החזר false;
    }
    X11_XSync(display, False);

    החזר true;
#אחרת
    החזר false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
