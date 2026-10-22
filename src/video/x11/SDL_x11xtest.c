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

#ಯದಿ defined(SDL_VIDEO_DRIVER_X11)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xtest.h"

ಸ್ಥಿರ bool xtest_initialized = false;

ಶೂನ್ಯ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#ಯದಿ 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    ಪೂರ್ಣಾಙ್ಕ event, error;
    ಪೂರ್ಣಾಙ್ಕ opcode;

    ಯದಿ (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    ಯದಿ (!X11_XTestIsInitialized()) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    ಯದಿ (!displaydata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪೂರ್ಣಾಙ್ಕ motion_x = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(x);
    ಪೂರ್ಣಾಙ್ಕ motion_y = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(y);
    ಯದಿ (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    ಯದಿ (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    X11_XSync(display, False);

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
