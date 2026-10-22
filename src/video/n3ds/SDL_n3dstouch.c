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

#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_N3DS

#ضمن <3ds.h>

#ضمن "../../events/SDL_touch_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#وصف_ڪريو N3DS_TOUCH_ID 1
#وصف_ڪريو N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#وصف_ڪريو TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_اوچائي_BOTTOM - 1)
#وصف_ڪريو TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_ويڪر - 1)

فراغ N3DS_InitTouch(فراغ)
{
    SDL_جوڙيو_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_سڌو, "Touchscreen");
}

فراغ N3DS_QuitTouch(فراغ)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

فراغ N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *اندروني = (SDL_Video_معلومات *)_this->اندروني;
    touchPosition touch;
    SDL_دري *دري;
    SDL_VideoDisplay *display;
    ساكن bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(اندروني->touch_display);
    دري = display ? display->fullscreen_دري : عدم;

    إذا (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      دري,
                      pressed ? SDL_EVENT_FINGER_هيٺ_ڏانهن : SDL_EVENT_FINGER_مٿي,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } وإلا إذا (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            دري,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_N3DS
