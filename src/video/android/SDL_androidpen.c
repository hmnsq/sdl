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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#அந்தர்பாவ "SDL_androidpen.h"
#அந்தர்பாவ "../../events/SDL_pen_c.h"
#அந்தர்பாவ "../../core/android/SDL_android.h"

#define ACTION_DOWN   0
#define ACTION_UP     1
#define ACTION_CANCEL 3
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6
#define ACTION_HOVER_ENTER  9
#define ACTION_HOVER_EXIT   10

வெறுமை Android_OnPen(SDL_Window *window, முழு pen_id_in, SDL_PenDeviceType device_type, முழு button, முழு action, தசம x, தசம y, தசம p)
{
    எனில் (!window) {
        திரும்பு;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((வெறுமை *) (size_t) pen_id_in);
    எனில் (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.இலக்கம்_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, வெற்று, window, &peninfo, (வெறுமை *) (size_t) pen_id_in, true);
        எனில் (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            திரும்பு;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_உள்ளீடு_Flags current = SDL_GetPenStatus(pen, வெற்று, 0);
    முழு diff = current ^ button;
    எனில் (diff != 0) {
        க்கு (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            எனில் (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    தேர்வு (action) {
    நிலை ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        நிறுத்து;

    நிலை ACTION_CANCEL:
    நிலை ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        நிறுத்து;

    நிலை ACTION_DOWN:
    நிலை ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_உள்ளீடு_ERASER_TIP) != 0, true);
        நிறுத்து;

    நிலை ACTION_UP:
    நிலை ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_உள்ளீடு_ERASER_TIP) != 0, false);
        நிறுத்து;

    இயல்பு:
        நிறுத்து;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
