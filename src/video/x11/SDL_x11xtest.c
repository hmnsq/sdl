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

#यदि defined(SDL_VIDEO_DRIVER_X11)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xtest.h"

स्थिर bool xtest_initialized = false;

शून्य X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#यदि 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->आन्तरिकम्->display;
    पूर्णाङ्क event, error;
    पूर्णाङ्क opcode;

    यदि (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        प्रत्यागम;
    }

    xtest_initialized = true;
#यदि_अन्तः
}

bool X11_XTestIsInitialized(शून्य)
{
    प्रत्यागम xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न x, भिन्न y)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XTEST
    यदि (!X11_XTestIsInitialized()) {
        प्रत्यागम false;
    }

    Display *display = _this->आन्तरिकम्->display;
    SDL_Display_दत्त *displaydata = गवाक्षः ? SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः) : SDL_Get_Display_Driver_दत्त(SDL_GetPrimaryDisplay());
    यदि (!displaydata) {
        प्रत्यागम false;
    }

    पूर्णाङ्क motion_x = (पूर्णाङ्क)SDL_roundf(x);
    पूर्णाङ्क motion_y = (पूर्णाङ्क)SDL_roundf(y);
    यदि (गवाक्षः) {
        motion_x += गवाक्षः->x;
        motion_y += गवाक्षः->y;
    }

    यदि (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, CurrentTime)) {
        प्रत्यागम false;
    }
    X11_XSync(display, False);

    प्रत्यागम true;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
