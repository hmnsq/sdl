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

#जर defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xtest.h"

स्थिर bool xtest_initialized = false;

शून्य X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#जर 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    पूर्णांक event, error;
    पूर्णांक opcode;

    जर (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        परत;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(शून्य)
{
    परत xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, दशांश x, दशांश y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    जर (!X11_XTestIsInitialized()) {
        परत false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    जर (!displaydata) {
        परत false;
    }

    पूर्णांक motion_x = (पूर्णांक)SDL_roundf(x);
    पूर्णांक motion_y = (पूर्णांक)SDL_roundf(y);
    जर (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    जर (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        परत false;
    }
    X11_XSync(display, False);

    परत true;
#अन्यथा
    परत false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
