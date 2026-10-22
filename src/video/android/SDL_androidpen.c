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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#અન્તર્ભાવ "SDL_androidpen.h"
#અન્તર્ભાવ "../../events/SDL_pen_c.h"
#અન્તર્ભાવ "../../core/android/SDL_android.h"

#define ACTION_DOWN   0
#define ACTION_UP     1
#define ACTION_CANCEL 3
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6
#define ACTION_HOVER_ENTER  9
#define ACTION_HOVER_EXIT   10

શૂન્ય Android_OnPen(SDL_Window *window, પૂર્ણાંક pen_id_in, SDL_PenDeviceType device_type, પૂર્ણાંક button, પૂર્ણાંક action, દશાંશ x, દશાંશ y, દશાંશ p)
{
    જો (!window) {
        પાછા;
    }

    // pointer index starts from zero.
    pen_id_in++;

    SDL_PenID pen = SDL_FindPenByHandle((શૂન્ય *) (size_t) pen_id_in);
    જો (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.અંક_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_AddPenDevice(0, ખાલી, window, &peninfo, (શૂન્ય *) (size_t) pen_id_in, true);
        જો (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_in);
            પાછા;
        }
    }

    SDL_SendPenMotion(0, pen, window, x, y);
    SDL_SendPenAxis(0, pen, window, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_આગત_Flags current = SDL_GetPenStatus(pen, ખાલી, 0);
    પૂર્ણાંક diff = current ^ button;
    જો (diff != 0) {
        માટે (Uint8 i = 1; i <= 5; ++i) {
            Uint8 mask = (1 << i);
            જો (diff & mask) {
                SDL_SendPenButton(0, pen, window, i, (button & mask) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    પસંદગી (action) {
    સ્થિતિ ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, window, true, true);
        તોડો;

    સ્થિતિ ACTION_CANCEL:
    સ્થિતિ ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, window, false, false);
        તોડો;

    સ્થિતિ ACTION_DOWN:
    સ્થિતિ ACTION_POINTER_DOWN:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_આગત_ERASER_TIP) != 0, true);
        તોડો;

    સ્થિતિ ACTION_UP:
    સ્થિતિ ACTION_POINTER_UP:
        SDL_SendPenTouch(0, pen, window, (button & SDL_PEN_આગત_ERASER_TIP) != 0, false);
        તોડો;

    મૂળભૂત:
        તોડો;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
