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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव "SDL_androidpen.h"
#अन्तर्भाव "../../events/SDL_pen_c.h"
#अन्तर्भाव "../../core/android/SDL_android.h"

#define ACTION_DOWN   0
#define ACTION_UP     1
#define ACTION_CANCEL 3
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6
#define ACTION_HOVER_ENTER  9
#define ACTION_HOVER_EXIT   10

शून्य Android_OnPen(SDL_Window *window, पूर्णाङ्क pen_id_in, SDL_PenDeviceType device_type, पूर्णाङ्क button, पूर्णाङ्क action, भिन्न x, भिन्न y, भिन्न p)
{
    यदि (!window) {
        प्रत्यागम;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (माप_प्रकार) pen_id_in);
    यदि (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.अंक_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, रिक्त, window, &peninfo, (शून्य *) (माप_प्रकार) pen_id_in, true);
        यदि (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            प्रत्यागम;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_निवेश_Flags current = SDL_GetPenStatus(pen, रिक्त, 0);
    पूर्णाङ्क diff = current ^ button;
    यदि (diff != 0) {
        प्रति (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            यदि (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    विकल्प (action) {
    पक्ष ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        भङ्ग;

    पक्ष ACTION_CANCEL:
    पक्ष ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        भङ्ग;

    पक्ष ACTION_DOWN:
    पक्ष ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_निवेश_ERASER_TIP) != 0, true);
        भङ्ग;

    पक्ष ACTION_UP:
    पक्ष ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_निवेश_ERASER_TIP) != 0, false);
        भङ्ग;

    स्वभाव:
        भङ्ग;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
