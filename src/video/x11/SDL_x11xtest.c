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

#सचे defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xtest.h"

स्थिर bool xtest_initialized = false;

शून्य X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#सचे 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    पूर्णाङ्क event, error;
    पूर्णाङ्क opcode;

    सचे (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        पटिनिवत्त;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(शून्य)
{
    पटिनिवत्त xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, भिन्न x, भिन्न y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    सचे (!X11_XTestIsInitialized()) {
        पटिनिवत्त false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    सचे (!displaydata) {
        पटिनिवत्त false;
    }

    पूर्णाङ्क motion_x = (पूर्णाङ्क)SDL_roundf(x);
    पूर्णाङ्क motion_y = (पूर्णाङ्क)SDL_roundf(y);
    सचे (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    सचे (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        पटिनिवत्त false;
    }
    X11_XSync(display, False);

    पटिनिवत्त true;
#अञ्ञथा
    पटिनिवत्त false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
