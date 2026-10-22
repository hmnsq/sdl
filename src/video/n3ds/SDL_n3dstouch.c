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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_N3DS

#అన్తర్భావ <3ds.h>

#అన్తర్భావ "../../events/SDL_touch_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_n3dstouch.h"
#అన్తర్భావ "SDL_n3dsvideo.h"

#నిర్వచించు N3DS_TOUCH_ID 1
#నిర్వచించు N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#నిర్వచించు TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_ఎత్తు_BOTTOM - 1)
#నిర్వచించు TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_వెడల్పు - 1)

శూన్య N3DS_InitTouch(శూన్య)
{
    SDL_కూడు_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_ప్రత్యక్ష, "Touchscreen");
}

శూన్య N3DS_QuitTouch(శూన్య)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

శూన్య N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *అంతర్గత = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    touchPosition touch;
    SDL_కిటికీ *కిటికీ;
    SDL_VideoDisplay *display;
    స్థిర bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(అంతర్గత->touch_display);
    కిటికీ = display ? display->fullscreen_కిటికీ : ఖాళీ;

    ఒకవేళ (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      కిటికీ,
                      pressed ? SDL_EVENT_FINGER_కిందికి : SDL_EVENT_FINGER_పైకి,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } లేకపోతే ఒకవేళ (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            కిటికీ,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_N3DS
