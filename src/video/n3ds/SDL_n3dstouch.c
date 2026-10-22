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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#شامل <3ds.h>

#شامل "../../events/SDL_touch_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_n3dstouch.h"
#شامل "SDL_n3dsvideo.h"

#تعریف_کرو N3DS_TOUCH_ID 1
#تعریف_کرو N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#تعریف_کرو TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_اونچائی_BOTTOM - 1)
#تعریف_کرو TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_چوڑائی - 1)

خالی N3DS_InitTouch(خالی)
{
    SDL_جوڑو_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_براہ_راست, "Touchscreen");
}

خالی N3DS_QuitTouch(خالی)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

خالی N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *اندرونی_2 = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    touchPosition touch;
    SDL_کھڑکی *کھڑکی;
    SDL_VideoDisplay *display;
    ساکن bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(اندرونی_2->touch_display);
    کھڑکی = display ? display->fullscreen_کھڑکی : تہی;

    اگر (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      کھڑکی,
                      pressed ? SDL_EVENT_FINGER_نیچے_کو : SDL_EVENT_FINGER_اوپر,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } ورنہ اگر (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            کھڑکی,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_N3DS
