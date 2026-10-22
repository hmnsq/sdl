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
#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidpen.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../core/android/SDL_android.h"

#تعریف_کړه ACTION_ښکته   0
#تعریف_کړه ACTION_پورته     1
#تعریف_کړه ACTION_CANCEL 3
#تعریف_کړه ACTION_اشاره_ګر_ښکته 5
#تعریف_کړه ACTION_اشاره_ګر_پورته   6
#تعریف_کړه ACTION_HOVER_ENTER  9
#تعریف_کړه ACTION_HOVER_EXIT   10

فراغ Android_OnPen(SDL_کړکۍ *کړکۍ, صحيح pen_id_دننه, SDL_PenDeviceType device_type, صحيح button, صحيح action, عائم x, عائم y, عائم p)
{
    إذا (!کړکۍ) {
        أرجع;
    }

    // pointer index starts from zero.
    pen_id_دننه++;

    SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle((فراغ *) (size_t) pen_id_دننه);
    إذا (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.عدد_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_جمع_کړه_Pen_Device(0, عدم, کړکۍ, &peninfo, (فراغ *) (size_t) pen_id_دننه, true);
        إذا (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_دننه);
            أرجع;
        }
    }

    SDL_SendPenMotion(0, pen, کړکۍ, x, y);
    SDL_SendPenAxis(0, pen, کړکۍ, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ننوت_Flags current = SDL_Get_Pen_حالت(pen, عدم, 0);
    صحيح diff = current ^ button;
    إذا (diff != 0) {
        لكل (Uint8 i = 1; i <= 5; ++i) {
            Uint8 ماسک = (1 << i);
            إذا (diff & ماسک) {
                SDL_SendPenButton(0, pen, کړکۍ, i, (button & ماسک) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    بدل (action) {
    حالة ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, کړکۍ, true, true);
        اكسر;

    حالة ACTION_CANCEL:
    حالة ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, کړکۍ, false, false);
        اكسر;

    حالة ACTION_ښکته:
    حالة ACTION_اشاره_ګر_ښکته:
        SDL_SendPenTouch(0, pen, کړکۍ, (button & SDL_PEN_ننوت_ERASER_TIP) != 0, true);
        اكسر;

    حالة ACTION_پورته:
    حالة ACTION_اشاره_ګر_پورته:
        SDL_SendPenTouch(0, pen, کړکۍ, (button & SDL_PEN_ننوت_ERASER_TIP) != 0, false);
        اكسر;

    افتراضي:
        اكسر;
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_ANDROID
