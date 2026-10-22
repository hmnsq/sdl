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

#𐤀𐤌 defined(SDL_VIDEO_DRIVER_X11)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xtest.h"

ساكن bool xtest_initialized = false;

فراغ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#𐤀𐤌 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    صحيح event, error;
    صحيح opcode;

    𐤀𐤌 (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        أرجع;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(فراغ)
{
    أرجع xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, عائم x, عائم y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    𐤀𐤌 (!X11_XTestIsInitialized()) {
        أرجع false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    𐤀𐤌 (!displaydata) {
        أرجع false;
    }

    صحيح motion_x = (صحيح)SDL_roundf(x);
    صحيح motion_y = (صحيح)SDL_roundf(y);
    𐤀𐤌 (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    𐤀𐤌 (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        أرجع false;
    }
    X11_XSync(display, False);

    أرجع true;
#وإلا
    أرجع false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
