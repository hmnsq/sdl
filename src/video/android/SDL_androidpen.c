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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidpen.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../core/android/SDL_android.h"

#وصف_ڪريو ACTION_هيٺ_ڏانهن   0
#وصف_ڪريو ACTION_مٿي     1
#وصف_ڪريو ACTION_CANCEL 3
#وصف_ڪريو ACTION_اشارو_هيٺ_ڏانهن 5
#وصف_ڪريو ACTION_اشارو_مٿي   6
#وصف_ڪريو ACTION_HOVER_ENTER  9
#وصف_ڪريو ACTION_HOVER_EXIT   10

فراغ Android_OnPen(SDL_دري *دري, صحيح pen_id_اندريون, SDL_PenDeviceType device_type, صحيح button, صحيح action, عائم x, عائم y, عائم p)
{
    إذا (!دري) {
        أرجع;
    }

    // pointer index starts from zero.
    pen_id_اندريون++;

    SDL_PenID pen = SDL_ڳوليو_Pen_By_Handle((فراغ *) (size_t) pen_id_اندريون);
    إذا (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.انگ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_جوڙيو_Pen_Device(0, عدم, دري, &peninfo, (فراغ *) (size_t) pen_id_اندريون, true);
        إذا (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_اندريون);
            أرجع;
        }
    }

    SDL_SendPenMotion(0, pen, دري, x, y);
    SDL_SendPenAxis(0, pen, دري, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_داخلا_Flags current = SDL_Get_Pen_حالت(pen, عدم, 0);
    صحيح diff = current ^ button;
    إذا (diff != 0) {
        لكل (Uint8 i = 1; i <= 5; ++i) {
            Uint8 نقاب = (1 << i);
            إذا (diff & نقاب) {
                SDL_SendPenButton(0, pen, دري, i, (button & نقاب) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    بدل (action) {
    حالة ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, دري, true, true);
        اكسر;

    حالة ACTION_CANCEL:
    حالة ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, دري, false, false);
        اكسر;

    حالة ACTION_هيٺ_ڏانهن:
    حالة ACTION_اشارو_هيٺ_ڏانهن:
        SDL_SendPenTouch(0, pen, دري, (button & SDL_PEN_داخلا_ERASER_TIP) != 0, true);
        اكسر;

    حالة ACTION_مٿي:
    حالة ACTION_اشارو_مٿي:
        SDL_SendPenTouch(0, pen, دري, (button & SDL_PEN_داخلا_ERASER_TIP) != 0, false);
        اكسر;

    افتراضي:
        اكسر;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_ANDROID
