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

#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11)

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11xtest.h"

സ്ഥിതം bool xtest_initialized = false;

ശൂന്യം X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#എങ്കിൽ 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->internal->display;
    പൂർണ്ണസംഖ്യ event, error;
    പൂർണ്ണസംഖ്യ opcode;

    എങ്കിൽ (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        തിരികെ;
    }

    xtest_initialized = true;
#endif
}

bool X11_XTestIsInitialized(ശൂന്യം)
{
    തിരികെ xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    എങ്കിൽ (!X11_XTestIsInitialized()) {
        തിരികെ false;
    }

    Display *display = _this->internal->display;
    SDL_DisplayData *displaydata = window ? SDL_GetDisplayDriverDataForWindow(window) : SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());
    എങ്കിൽ (!displaydata) {
        തിരികെ false;
    }

    പൂർണ്ണസംഖ്യ motion_x = (പൂർണ്ണസംഖ്യ)SDL_roundf(x);
    പൂർണ്ണസംഖ്യ motion_y = (പൂർണ്ണസംഖ്യ)SDL_roundf(y);
    എങ്കിൽ (window) {
        motion_x += window->x;
        motion_y += window->y;
    }

    എങ്കിൽ (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        തിരികെ false;
    }
    X11_XSync(display, False);

    തിരികെ true;
#അല്ലെങ്കിൽ
    തിരികെ false;
#endif
}

#endif // SDL_VIDEO_DRIVER_X11
