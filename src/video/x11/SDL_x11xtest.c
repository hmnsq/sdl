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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_X11)

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xtest.h"

ସ୍ଥିର bool xtest_initialized = false;

ଶୂନ୍ୟ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#ଯଦି 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା event, error;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା opcode;

    ଯଦି (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        ଫେରନ୍ତୁ;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ x, ଦଶମିକ y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    ଯଦି (!X11_XTestIsInitialized()) {
        ଫେରନ୍ତୁ false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    ଯଦି (!displaydata) {
        ଫେରନ୍ତୁ false;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା motion_x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(x);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା motion_y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(y);
    ଯଦି (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    ଯଦି (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        ଫେରନ୍ତୁ false;
    }
    X11_XSync(display, False);

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
