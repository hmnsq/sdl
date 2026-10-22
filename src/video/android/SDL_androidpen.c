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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#شامل "SDL_androidpen.h"
#شامل "../../events/SDL_pen_c.h"
#شامل "../../core/android/SDL_android.h"

#تعریف_کرو ACTION_نیچے_کو   0
#تعریف_کرو ACTION_اوپر     1
#تعریف_کرو ACTION_CANCEL 3
#تعریف_کرو ACTION_اشارہ_گر_نیچے_کو 5
#تعریف_کرو ACTION_اشارہ_گر_اوپر   6
#تعریف_کرو ACTION_HOVER_ENTER  9
#تعریف_کرو ACTION_HOVER_EXIT   10

خالی Android_OnPen(SDL_کھڑکی *کھڑکی, صحیح pen_id_اندر, SDL_PenDeviceType device_type, صحیح button, صحیح action, اعشاری x, اعشاری y, اعشاری p)
{
    اگر (!کھڑکی) {
        واپس;
    }

    // pointer index starts from zero.
    pen_id_اندر++;

    SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle((خالی *) (size_t) pen_id_اندر);
    اگر (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.عدد_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_جوڑو_Pen_Device(0, تہی, کھڑکی, &peninfo, (خالی *) (size_t) pen_id_اندر, true);
        اگر (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_اندر);
            واپس;
        }
    }

    SDL_SendPenMotion(0, pen, کھڑکی, x, y);
    SDL_SendPenAxis(0, pen, کھڑکی, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_داخلہ_Flags current = SDL_Get_Pen_حالت(pen, تہی, 0);
    صحیح diff = current ^ button;
    اگر (diff != 0) {
        برائے (Uint8 i = 1; i <= 5; ++i) {
            Uint8 نقاب = (1 << i);
            اگر (diff & نقاب) {
                SDL_SendPenButton(0, pen, کھڑکی, i, (button & نقاب) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    انتخاب (action) {
    حالت ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, کھڑکی, true, true);
        توڑو;

    حالت ACTION_CANCEL:
    حالت ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, کھڑکی, false, false);
        توڑو;

    حالت ACTION_نیچے_کو:
    حالت ACTION_اشارہ_گر_نیچے_کو:
        SDL_SendPenTouch(0, pen, کھڑکی, (button & SDL_PEN_داخلہ_ERASER_TIP) != 0, true);
        توڑو;

    حالت ACTION_اوپر:
    حالت ACTION_اشارہ_گر_اوپر:
        SDL_SendPenTouch(0, pen, کھڑکی, (button & SDL_PEN_داخلہ_ERASER_TIP) != 0, false);
        توڑو;

    طےشدہ:
        توڑو;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID
