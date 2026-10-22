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

#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_X11)

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11xtest.h"

স্থির bool xtest_initialized = false;

শূন্য X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#যদি 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    পূর্ণসংখ্যা event, error;
    পূর্ণসংখ্যা opcode;

    যদি (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        ফেরত;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(শূন্য)
{
    ফেরত xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, দশমিক x, দশমিক y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    যদি (!X11_XTestIsInitialized()) {
        ফেরত false;
    }

    Display *display = _this->internal->display;
    SDL_Display_তথ্য *displaydata = window ? SDL_Get_Display_Driver_তথ্য_For_Window(window) : SDL_Get_Display_Driver_তথ্য(SDL_GetPrimaryDisplay());
    যদি (!displaydata) {
        ফেরত false;
    }

    পূর্ণসংখ্যা motion_x = (পূর্ণসংখ্যা)SDL_roundf(x);
    পূর্ণসংখ্যা motion_y = (পূর্ণসংখ্যা)SDL_roundf(y);
    যদি (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    যদি (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        ফেরত false;
    }
    X11_XSync(display, False);

    ফেরত true;
#অন্যথা
    ফেরত false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
