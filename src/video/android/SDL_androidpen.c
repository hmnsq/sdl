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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "SDL_androidpen.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಕೆಳಕ್ಕೆ   0
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಮೇಲೆ     1
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_CANCEL 3
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಸೂಚಕ_ಕೆಳಕ್ಕೆ 5
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಸೂಚಕ_ಮೇಲೆ   6
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_HOVER_ENTER  9
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_HOVER_EXIT   10

ಶೂನ್ಯ Android_OnPen(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ pen_id_ಒಳ, SDL_PenDeviceType device_type, ಪೂರ್ಣಾಂಕ button, ಪೂರ್ಣಾಂಕ action, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, ದಶಮಾಂಶ p)
{
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    // pointer index starts from zero.
    pen_id_ಒಳ++;

    SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle((ಶೂನ್ಯ *) (size_t) pen_id_ಒಳ);
    ಆದರೆ (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.ಅಂಕೆ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_ಕೂಡಿಸು_Pen_Device(0, ಖಾಲಿ, ಕಿಟಕಿ, &peninfo, (ಶೂನ್ಯ *) (size_t) pen_id_ಒಳ, true);
        ಆದರೆ (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_ಒಳ);
            ಹಿಂತಿರುಗಿ;
        }
    }

    SDL_SendPenMotion(0, pen, ಕಿಟಕಿ, x, y);
    SDL_SendPenAxis(0, pen, ಕಿಟಕಿ, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ಒಳಹರಿವು_Flags current = SDL_Get_Pen_ಸ್ಥಿತಿ(pen, ಖಾಲಿ, 0);
    ಪೂರ್ಣಾಂಕ diff = current ^ button;
    ಆದರೆ (diff != 0) {
        ಗಾಗಿ (Uint8 i = 1; i <= 5; ++i) {
            Uint8 ಮುಖವಾಡ = (1 << i);
            ಆದರೆ (diff & ಮುಖವಾಡ) {
                SDL_SendPenButton(0, pen, ಕಿಟಕಿ, i, (button & ಮುಖವಾಡ) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    ಆಯ್ಕೆ (action) {
    ಸ್ಥಿತಿ ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, ಕಿಟಕಿ, true, true);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_CANCEL:
    ಸ್ಥಿತಿ ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, ಕಿಟಕಿ, false, false);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_ಕೆಳಕ್ಕೆ:
    ಸ್ಥಿತಿ ACTION_ಸೂಚಕ_ಕೆಳಕ್ಕೆ:
        SDL_SendPenTouch(0, pen, ಕಿಟಕಿ, (button & SDL_PEN_ಒಳಹರಿವು_ERASER_TIP) != 0, true);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_ಮೇಲೆ:
    ಸ್ಥಿತಿ ACTION_ಸೂಚಕ_ಮೇಲೆ:
        SDL_SendPenTouch(0, pen, ಕಿಟಕಿ, (button & SDL_PEN_ಒಳಹರಿವು_ERASER_TIP) != 0, false);
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
