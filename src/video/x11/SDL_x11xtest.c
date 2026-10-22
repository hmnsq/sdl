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

#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_X11)

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11xtest.h"

நிலையான bool xtest_initialized = false;

வெறுமை X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#எனில் 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    முழு event, error;
    முழு opcode;

    எனில் (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        திரும்பு;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(வெறுமை)
{
    திரும்பு xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, தசம x, தசம y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    எனில் (!X11_XTestIsInitialized()) {
        திரும்பு false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    எனில் (!displaydata) {
        திரும்பு false;
    }

    முழு motion_x = (முழு)SDL_roundf(x);
    முழு motion_y = (முழு)SDL_roundf(y);
    எனில் (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    எனில் (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        திரும்பு false;
    }
    X11_XSync(display, False);

    திரும்பு true;
#இல்லையெனில்
    திரும்பு false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
