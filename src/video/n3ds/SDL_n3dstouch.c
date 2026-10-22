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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_N3DS

#ضمن <3ds.h>

#ضمن "../../events/SDL_touch_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کن N3DS_TOUCH_ID 1
#تعریف_کن N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#تعریف_کن TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_ارتفاع_BOTTOM - 1)
#تعریف_کن TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_عرض - 1)

فراغ N3DS_InitTouch(فراغ)
{
    SDL_جمع_کن_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_مستقیم, "Touchscreen");
}

فراغ N3DS_QuitTouch(فراغ)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

فراغ N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داخلی = (SDL_Video_داده *)_this->داخلی;
    touchPosition touch;
    SDL_پنجره *پنجره;
    SDL_VideoDisplay *display;
    ساكن bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(داخلی->touch_display);
    پنجره = display ? display->fullscreen_پنجره : عدم;

    إذا (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      پنجره,
                      pressed ? SDL_EVENT_FINGER_پایین : SDL_EVENT_FINGER_به_بالا,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } وإلا إذا (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            پنجره,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_N3DS
