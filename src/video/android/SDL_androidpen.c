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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "SDL_androidpen.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#define ACTION_DOWN   0
#define ACTION_UP     1
#define ACTION_CANCEL 3
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6
#define ACTION_HOVER_ENTER  9
#define ACTION_HOVER_EXIT   10

ಶೂನ್ಯ Android_OnPen(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ pen_id_in, SDL_PenDeviceType device_type, ಪೂರ್ಣಾಙ್ಕ button, ಪೂರ್ಣಾಙ್ಕ action, ಭಿನ್ನ x, ಭಿನ್ನ y, ಭಿನ್ನ p)
{
    ಯದಿ (!window) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((ಶೂನ್ಯ *) (size_t) pen_id_in);
    ಯದಿ (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.ಅಂಕೆ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, ರಿಕ್ತ, window, &peninfo, (ಶೂನ್ಯ *) (size_t) pen_id_in, true);
        ಯದಿ (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            ಪ್ರತ್ಯಾಗಮ;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ಒಳಹರಿವು_Flags current = SDL_GetPenStatus(pen, ರಿಕ್ತ, 0);
    ಪೂರ್ಣಾಙ್ಕ diff = current ^ button;
    ಯದಿ (diff != 0) {
        ಪ್ರತಿ (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            ಯದಿ (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    ವಿಕಲ್ಪ (action) {
    ಪಕ್ಷ ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        ಭಙ್ಗ;

    ಪಕ್ಷ ACTION_CANCEL:
    ಪಕ್ಷ ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        ಭಙ್ಗ;

    ಪಕ್ಷ ACTION_DOWN:
    ಪಕ್ಷ ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_ಒಳಹರಿವು_ERASER_TIP) != 0, true);
        ಭಙ್ಗ;

    ಪಕ್ಷ ACTION_UP:
    ಪಕ್ಷ ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_ಒಳಹರಿವು_ERASER_TIP) != 0, false);
        ಭಙ್ಗ;

    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
