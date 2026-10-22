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

#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_X11)

#شامل "SDL_x11video.h"
#شامل "SDL_x11xtest.h"

ساکن bool xtest_initialized = false;

خالی X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#اگر 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->اندرونی_2->display;
    صحیح event, error;
    صحیح opcode;

    اگر (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        واپس;
    }

    xtest_initialized = true;
#اگر_ختم
}

bool X11_XTestIsInitialized(خالی)
{
    واپس xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری x, اعشاری y)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
    اگر (!X11_XTestIsInitialized()) {
        واپس false;
    }

    Display *display = _this->اندرونی_2->display;
    SDL_Display_ڈیٹا *displaydata = کھڑکی ? SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی) : SDL_Get_Display_Driver_ڈیٹا(SDL_GetPrimaryDisplay());
    اگر (!displaydata) {
        واپس false;
    }

    صحیح motion_x = (صحیح)SDL_roundf(x);
    صحیح motion_y = (صحیح)SDL_roundf(y);
    اگر (کھڑکی) {
        motion_x += کھڑکی->x;
        motion_y += کھڑکی->y;
    }

    اگر (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, Current_وقت)) {
        واپس false;
    }
    X11_XSync(display, False);

    واپس true;
#ورنہ
    واپس false;
#اگر_ختم
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
