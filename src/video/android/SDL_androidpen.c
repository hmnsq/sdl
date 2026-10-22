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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ଅନ୍ତର୍ଭାଵ "SDL_androidpen.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_pen_c.h"
#ଅନ୍ତର୍ଭାଵ "../../core/android/SDL_android.h"

#define ACTION_DOWN   0
#define ACTION_UP     1
#define ACTION_CANCEL 3
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6
#define ACTION_HOVER_ENTER  9
#define ACTION_HOVER_EXIT   10

ଶୂନ୍ୟ Android_OnPen(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pen_id_in, SDL_PenDeviceType device_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା button, ପୂର୍ଣ୍ଣସଂଖ୍ୟା action, ଦଶମିକ x, ଦଶମିକ y, ଦଶମିକ p)
{
    ଯଦି (!window) {
        ଫେରନ୍ତୁ;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((ଶୂନ୍ୟ *) (size_t) pen_id_in);
    ଯଦି (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.ଅଙ୍କ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, ଖାଲି, window, &peninfo, (ଶୂନ୍ୟ *) (size_t) pen_id_in, true);
        ଯଦି (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            ଫେରନ୍ତୁ;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ନିବେଶ_Flags current = SDL_GetPenStatus(pen, ଖାଲି, 0);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା diff = current ^ button;
    ଯଦି (diff != 0) {
        ପାଇଁ (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            ଯଦି (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    ବାଛ (action) {
    ସ୍ଥିତି ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି ACTION_CANCEL:
    ସ୍ଥିତି ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି ACTION_DOWN:
    ସ୍ଥିତି ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_ନିବେଶ_ERASER_TIP) != 0, true);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି ACTION_UP:
    ସ୍ଥିତି ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_ନିବେଶ_ERASER_TIP) != 0, false);
        ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
