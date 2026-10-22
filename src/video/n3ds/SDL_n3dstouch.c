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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_N3DS

#ਅਨ੍ਤਰ੍ਭਾਵ <3ds.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dstouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsvideo.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N3DS_TOUCH_ID 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N3DS_TOUCH_FINGER 1

/*
  Factors used to convert touchscreen coordinates to
  SDL's 0-1 values. Note that the N3DS's screen is
  internally in a portrait disposition so the
  GSP_SCREEN constants are flipped.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHSCREEN_SCALE_X 1.0f / (GSP_SCREEN_ਉਚਾਈ_BOTTOM - 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOUCHSCREEN_SCALE_Y 1.0f / (GSP_SCREEN_ਚੌੜਾਈ - 1)

ਖਾਲੀ N3DS_InitTouch(ਖਾਲੀ)
{
    SDL_ਜੋੜੋ_Touch(N3DS_TOUCH_ID, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, "Touchscreen");
}

ਖਾਲੀ N3DS_QuitTouch(ਖਾਲੀ)
{
    SDL_DelTouch(N3DS_TOUCH_ID);
}

ਖਾਲੀ N3DS_PollTouch(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    touchPosition touch;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_VideoDisplay *display;
    ਸਥਿਰ bool was_pressed = false;
    bool pressed;
    hidTouchRead(&touch);
    pressed = (touch.px != 0 || touch.py != 0);

    display = SDL_GetVideoDisplay(ਅੰਦਰੂਨੀ->touch_display);
    ਖਿੜਕੀ = display ? display->fullscreen_ਖਿੜਕੀ : ਨਿਰਾ;

    ਜੇ (pressed != was_pressed) {
        was_pressed = pressed;
        SDL_SendTouch(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                      ਖਿੜਕੀ,
                      pressed ? SDL_EVENT_FINGER_ਥੱਲੇ : SDL_EVENT_FINGER_ਉੱਪਰ,
                      touch.px * TOUCHSCREEN_SCALE_X,
                      touch.py * TOUCHSCREEN_SCALE_Y,
                      pressed ? 1.0f : 0.0f);
    } ਨਹੀਂਤਾਂ ਜੇ (pressed) {
        SDL_SendTouchMotion(0, N3DS_TOUCH_ID, N3DS_TOUCH_FINGER,
                            ਖਿੜਕੀ,
                            touch.px * TOUCHSCREEN_SCALE_X,
                            touch.py * TOUCHSCREEN_SCALE_Y,
                            1.0f);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_N3DS
