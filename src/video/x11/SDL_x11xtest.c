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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_X11)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xtest.h"

ਸਥਿਰ bool xtest_initialized = false;

ਖਾਲੀ X11_InitXTest(SDL_VideoDevice *_this)
{
// This is currently disabled since it doesn't appear to work on XWayland
#ਜੇ 0//def SDL_VIDEO_DRIVER_X11_XTEST
    Display *display = _this->ਅੰਦਰੂਨੀ->display;
    ਪੂਰਨ event, error;
    ਪੂਰਨ opcode;

    ਜੇ (!SDL_X11_HAVE_XTEST ||
        !X11_XQueryExtension(display, "XTEST", &opcode, &event, &error)) {
        ਵਾਪਸ;
    }

    xtest_initialized = true;
#ਜੇ_ਅੰਤ
}

bool X11_XTestIsInitialized(ਖਾਲੀ)
{
    ਵਾਪਸ xtest_initialized;
}

bool X11_WarpMouseXTest(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XTEST
    ਜੇ (!X11_XTestIsInitialized()) {
        ਵਾਪਸ false;
    }

    Display *display = _this->ਅੰਦਰੂਨੀ->display;
    SDL_Display_ਅੰਕੜੇ *displaydata = ਖਿੜਕੀ ? SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ) : SDL_Get_Display_Driver_ਅੰਕੜੇ(SDL_GetPrimaryDisplay());
    ਜੇ (!displaydata) {
        ਵਾਪਸ false;
    }

    ਪੂਰਨ motion_x = (ਪੂਰਨ)SDL_roundf(x);
    ਪੂਰਨ motion_y = (ਪੂਰਨ)SDL_roundf(y);
    ਜੇ (ਖਿੜਕੀ) {
        motion_x += ਖਿੜਕੀ->x;
        motion_y += ਖਿੜਕੀ->y;
    }

    ਜੇ (!X11_XTestFakeMotionEvent(display, displaydata->screen, motion_x, motion_y, Current_ਸਮਾਂ)) {
        ਵਾਪਸ false;
    }
    X11_XSync(display, False);

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
