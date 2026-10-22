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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID

#समावेश "SDL_androidpen.h"
#समावेश "../../events/SDL_pen_c.h"
#समावेश "../../core/android/SDL_android.h"

#घोषणा ACTION_DOWN   0
#घोषणा ACTION_UP     1
#घोषणा ACTION_CANCEL 3
#घोषणा ACTION_POINTER_DOWN 5
#घोषणा ACTION_POINTER_UP   6
#घोषणा ACTION_HOVER_ENTER  9
#घोषणा ACTION_HOVER_EXIT   10

व्योम Android_OnPen(SDL_Window *window, पूर्णांक pen_id_in, SDL_PenDeviceType device_type, पूर्णांक button, पूर्णांक action, भग्न x, भग्न y, भग्न p)
{
    अगर (!window) {
        वापस;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((व्योम *) (माप_प्रकार) pen_id_in);
    अगर (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.अंक_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, शून्य, window, &peninfo, (व्योम *) (माप_प्रकार) pen_id_in, true);
        अगर (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            वापस;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_निवेश_Flags current = SDL_GetPenStatus(pen, शून्य, 0);
    पूर्णांक diff = current ^ button;
    अगर (diff != 0) {
        क्रम (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            अगर (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    चयन (action) {
    हाल ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        अवरोध;

    हाल ACTION_CANCEL:
    हाल ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        अवरोध;

    हाल ACTION_DOWN:
    हाल ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_निवेश_ERASER_TIP) != 0, true);
        अवरोध;

    हाल ACTION_UP:
    हाल ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_निवेश_ERASER_TIP) != 0, false);
        अवरोध;

    शेष:
        अवरोध;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_ANDROID
