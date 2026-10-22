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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xtest.h"

ಸ್ಥಿರ bool xtest_initialized = false;

ಶೂನ್ಯ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#ಆದರೆ 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->ಆಂತರಿಕ->display;
    ಪೂರ್ಣಾಂಕ event, error;
    ಪೂರ್ಣಾಂಕ opcode;

    ಆದರೆ (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        ಹಿಂತಿರುಗಿ;
    }

    xtest_initialized = true;
#ಆದರೆ_ಅಂತ್ಯ
}

bool X11_XTestIsInitialized(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XTEST
    ಆದರೆ (!X11_XTestIsInitialized()) {
        ಹಿಂತಿರುಗಿ false;
    }

    Display *display = _this->ಆಂತರಿಕ->display;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = ಕಿಟಕಿ ? SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ) : SDL_Get_Display_Driver_ದತ್ತಾಂಶ(SDL_GetPrimaryDisplay());
    ಆದರೆ (!displaydata) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಪೂರ್ಣಾಂಕ motion_x = (ಪೂರ್ಣಾಂಕ)SDL_roundf(x);
    ಪೂರ್ಣಾಂಕ motion_y = (ಪೂರ್ಣಾಂಕ)SDL_roundf(y);
    ಆದರೆ (ಕಿಟಕಿ) {
        motion_x += ಕಿಟಕಿ->x;
        motion_y += ಕಿಟಕಿ->y;
    }

    ಆದರೆ (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, Current_ಸಮಯ)) {
        ಹಿಂತಿರುಗಿ false;
    }
    X11_XSync(display, False);

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
