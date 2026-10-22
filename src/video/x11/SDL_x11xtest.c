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

#include "SDL_internal.h"

#如果 defined(SDL_VIDEO_DRIVER_X11)

#include "SDL_x11video.h"
#include "SDL_x11xtest.h"

static bool xtest_initialized = false;

void X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#如果 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    整数 event, error;
    整数 opcode;

    如果 (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        返回;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(void)
{
    返回 xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, float x, float y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    如果 (!X11_XTestIsInitialized()) {
        返回 false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    如果 (!displaydata) {
        返回 false;
    }

    整数 motion_x = (整数)SDL_roundf(x);
    整数 motion_y = (整数)SDL_roundf(y);
    如果 (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    如果 (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        返回 false;
    }
    X11_XSync(display, False);

    返回 true;
#否则
    返回 false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
