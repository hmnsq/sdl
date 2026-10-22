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

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11)

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xtest.h"

స్థిర bool xtest_initialized = false;

శూన్య X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#ఒకవేళ 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->అంతర్గత->display;
    పూర్ణాంకం event, error;
    పూర్ణాంకం opcode;

    ఒకవేళ (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        తిరిగి;
    }

    xtest_initialized = true;
#అయితే_ముగింపు
}

bool X11_XTestIsInitialized(శూన్య)
{
    తిరిగి xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XTEST
    ఒకవేళ (!X11_XTestIsInitialized()) {
        తిరిగి false;
    }

    Display *display = _this->అంతర్గత->display;
    SDL_Display_దత్తాంశం *displaydata = కిటికీ ? SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ) : SDL_Get_Display_Driver_దత్తాంశం(SDL_GetPrimaryDisplay());
    ఒకవేళ (!displaydata) {
        తిరిగి false;
    }

    పూర్ణాంకం motion_x = (పూర్ణాంకం)SDL_roundf(x);
    పూర్ణాంకం motion_y = (పూర్ణాంకం)SDL_roundf(y);
    ఒకవేళ (కిటికీ) {
        motion_x += కిటికీ->x;
        motion_y += కిటికీ->y;
    }

    ఒకవేళ (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, Current_సమయం)) {
        తిరిగి false;
    }
    X11_XSync(display, False);

    తిరిగి true;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
