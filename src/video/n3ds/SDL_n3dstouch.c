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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ <3ds.h>

#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dstouch.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsvideo.h"

#ವ್ಯಾಖ್ಯಾನಿಸು N3DS_TOUCH_ID 1
#ವ್ಯಾಖ್ಯಾನಿಸು N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_ಎತ್ತರ_BOTTOM - 1)
#ವ್ಯಾಖ್ಯಾನಿಸು TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_ಅಗಲ - 1)

ಶೂನ್ಯ N3DS_InitTouch(ಶೂನ್ಯ)
{
    SDL_ಕೂಡಿಸು_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_ನೇರ, "Touchscreen");
}

ಶೂನ್ಯ N3DS_QuitTouch(ಶೂನ್ಯ)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

ಶೂನ್ಯ N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    touchPosition touch;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_VideoDisplay *display;
    ಸ್ಥಿರ bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(ಆಂತರಿಕ->touch_display);
    ಕಿಟಕಿ = display ? display->fullscreen_ಕಿಟಕಿ : ಖಾಲಿ;

    ಆದರೆ (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      ಕಿಟಕಿ,
                      pressed ? SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ : SDL_EVENT_FINGER_ಮೇಲೆ,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            ಕಿಟಕಿ,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_N3DS
