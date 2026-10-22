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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidpen.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_pen_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਥੱਲੇ   0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਉੱਪਰ     1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_CANCEL 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਸੂਚਕ_ਥੱਲੇ 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਸੂਚਕ_ਉੱਪਰ   6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_HOVER_ENTER  9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_HOVER_EXIT   10

ਖਾਲੀ Android_OnPen(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ pen_id_ਵਿੱਚ, SDL_PenDeviceType device_type, ਪੂਰਨ button, ਪੂਰਨ action, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, ਦਸ਼ਮਲਵ p)
{
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    // pointer index starts from zero.
    pen_id_ਵਿੱਚ++;

    SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle((ਖਾਲੀ *) (size_t) pen_id_ਵਿੱਚ);
    ਜੇ (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.ਅੰਕ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_ਜੋੜੋ_Pen_Device(0, ਨਿਰਾ, ਖਿੜਕੀ, &peninfo, (ਖਾਲੀ *) (size_t) pen_id_ਵਿੱਚ, true);
        ਜੇ (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_ਵਿੱਚ);
            ਵਾਪਸ;
        }
    }

    SDL_SendPenMotion(0, pen, ਖਿੜਕੀ, x, y);
    SDL_SendPenAxis(0, pen, ਖਿੜਕੀ, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ਨਿਵੇਸ਼_Flags current = SDL_Get_Pen_ਸਥਿਤੀ(pen, ਨਿਰਾ, 0);
    ਪੂਰਨ diff = current ^ button;
    ਜੇ (diff != 0) {
        ਲਈ (Uint8 i = 1; i <= 5; ++i) {
            Uint8 ਨਕਾਬ = (1 << i);
            ਜੇ (diff & ਨਕਾਬ) {
                SDL_SendPenButton(0, pen, ਖਿੜਕੀ, i, (button & ਨਕਾਬ) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    ਚੋਣ (action) {
    ਹਾਲਤ ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, ਖਿੜਕੀ, true, true);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_CANCEL:
    ਹਾਲਤ ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, ਖਿੜਕੀ, false, false);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_ਥੱਲੇ:
    ਹਾਲਤ ACTION_ਸੂਚਕ_ਥੱਲੇ:
        SDL_SendPenTouch(0, pen, ਖਿੜਕੀ, (button & SDL_PEN_ਨਿਵੇਸ਼_ERASER_TIP) != 0, true);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_ਉੱਪਰ:
    ਹਾਲਤ ACTION_ਸੂਚਕ_ਉੱਪਰ:
        SDL_SendPenTouch(0, pen, ਖਿੜਕੀ, (button & SDL_PEN_ਨਿਵੇਸ਼_ERASER_TIP) != 0, false);
        ਰੋਕੋ;

    ਮੂਲ:
        ਰੋਕੋ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID
