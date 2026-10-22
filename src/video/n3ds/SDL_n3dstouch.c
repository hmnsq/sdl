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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_N3DS

#अन्तर्भाव <3ds.h>

#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_n3dstouch.h"
#अन्तर्भाव "SDL_n3dsvideo.h"

#परिभाषय N3DS_TOUCH_ID 1
#परिभाषय N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#परिभाषय TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_HEIGHT_BOTTOM - 1)
#परिभाषय TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_विस्तारः - 1)

शून्य N3DS_InitTouch(शून्य)
{
    SDL_सङ्कलय_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_प्रत्यक्षम्, "Touchscreen");
}

शून्य N3DS_QuitTouch(शून्य)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

शून्य N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *आन्तरिकम् = (SDL_Video_दत्त *)_this->आन्तरिकम्;
    touchPosition touch;
    SDL_गवाक्षः *गवाक्षः;
    SDL_VideoDisplay *display;
    स्थिर bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(आन्तरिकम्->touch_display);
    गवाक्षः = display ? display->fullscreen_गवाक्षः : रिक्त;

    यदि (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      गवाक्षः,
                      pressed ? SDL_EVENT_FINGER_अधस्तात् : SDL_EVENT_FINGER_ऊर्ध्वम्,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } अन्यथा यदि (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            गवाक्षः,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_N3DS
