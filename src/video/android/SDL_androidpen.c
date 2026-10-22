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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव "SDL_androidpen.h"
#अन्तर्भाव "../../events/SDL_pen_c.h"
#अन्तर्भाव "../../core/android/SDL_android.h"

#परिभाषय ACTION_अधस्तात्   0
#परिभाषय ACTION_ऊर्ध्वम्     1
#परिभाषय ACTION_CANCEL 3
#परिभाषय ACTION_POINTER_अधस्तात् 5
#परिभाषय ACTION_POINTER_ऊर्ध्वम्   6
#परिभाषय ACTION_HOVER_ENTER  9
#परिभाषय ACTION_HOVER_EXIT   10

शून्य Android_OnPen(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क pen_id_अन्तर्, SDL_PenDeviceType device_type, पूर्णाङ्क button, पूर्णाङ्क action, भिन्न x, भिन्न y, भिन्न p)
{
    यदि (!गवाक्षः) {
        प्रत्यागम;
    }

    // pointer index starts from zero.
    pen_id_अन्तर्++;

    SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) pen_id_अन्तर्);
    यदि (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.अङ्कः_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_सङ्कलय_Pen_Device(0, रिक्त, गवाक्षः, &peninfo, (शून्य *) (size_t) pen_id_अन्तर्, true);
        यदि (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_अन्तर्);
            प्रत्यागम;
        }
    }

    SDL_SendPenMotion(0, pen, गवाक्षः, x, y);
    SDL_SendPenAxis(0, pen, गवाक्षः, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_निवेशः_Flags current = SDL_Get_Pen_स्थितिः(pen, रिक्त, 0);
    पूर्णाङ्क diff = current ^ button;
    यदि (diff != 0) {
        प्रति (Uint8 i = 1; i <= 5; ++i) {
            Uint8 आवरणम् = (1 << i);
            यदि (diff & आवरणम्) {
                SDL_SendPenButton(0, pen, गवाक्षः, i, (button & आवरणम्) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    विकल्प (action) {
    पक्ष ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, गवाक्षः, true, true);
        भङ्ग;

    पक्ष ACTION_CANCEL:
    पक्ष ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, गवाक्षः, false, false);
        भङ्ग;

    पक्ष ACTION_अधस्तात्:
    पक्ष ACTION_POINTER_अधस्तात्:
        SDL_SendPenTouch(0, pen, गवाक्षः, (button & SDL_PEN_निवेशः_ERASER_TIP) != 0, true);
        भङ्ग;

    पक्ष ACTION_ऊर्ध्वम्:
    पक्ष ACTION_POINTER_ऊर्ध्वम्:
        SDL_SendPenTouch(0, pen, गवाक्षः, (button & SDL_PEN_निवेशः_ERASER_TIP) != 0, false);
        भङ्ग;

    स्वभाव:
        भङ्ग;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_ANDROID
