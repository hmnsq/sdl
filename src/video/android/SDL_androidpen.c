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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID

#అన్తర్భావ "SDL_androidpen.h"
#అన్తర్భావ "../../events/SDL_pen_c.h"
#అన్తర్భావ "../../core/android/SDL_android.h"

#నిర్వచించు ACTION_కిందికి   0
#నిర్వచించు ACTION_పైకి     1
#నిర్వచించు ACTION_CANCEL 3
#నిర్వచించు ACTION_సూచిక_కిందికి 5
#నిర్వచించు ACTION_సూచిక_పైకి   6
#నిర్వచించు ACTION_HOVER_ENTER  9
#నిర్వచించు ACTION_HOVER_EXIT   10

శూన్య Android_OnPen(SDL_కిటికీ *కిటికీ, పూర్ణాంకం pen_id_లోపల, SDL_PenDeviceType device_type, పూర్ణాంకం button, పూర్ణాంకం action, దశాంశం x, దశాంశం y, దశాంశం p)
{
    ఒకవేళ (!కిటికీ) {
        తిరిగి;
    }

    // pointer index starts from zero.
    pen_id_లోపల++;

    SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle((శూన్య *) (size_t) pen_id_లోపల);
    ఒకవేళ (!pen) {
        // TODO: Query JNI for pen device info
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.అంకె_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        peninfo.device_type = device_type;
        pen = SDL_కూడు_Pen_Device(0, ఖాళీ, కిటికీ, &peninfo, (శూన్య *) (size_t) pen_id_లోపల, true);
        ఒకవేళ (!pen) {
            SDL_Log("error: can't add a pen device %d", pen_id_లోపల);
            తిరిగి;
        }
    }

    SDL_SendPenMotion(0, pen, కిటికీ, x, y);
    SDL_SendPenAxis(0, pen, కిటికీ, SDL_PEN_AXIS_PRESSURE, p);
    // TODO: add more axis

    SDL_Pen_ఆదానం_Flags current = SDL_Get_Pen_స్థితి(pen, ఖాళీ, 0);
    పూర్ణాంకం diff = current ^ button;
    ఒకవేళ (diff != 0) {
        కొరకు (Uint8 i = 1; i <= 5; ++i) {
            Uint8 ముసుగు = (1 << i);
            ఒకవేళ (diff & ముసుగు) {
                SDL_SendPenButton(0, pen, కిటికీ, i, (button & ముసుగు) != 0);
            }
        }
    }

    // button contains DOWN/ERASER_TIP on DOWN/UP regardless of pressed state, use action to distinguish
    // we don't compare tip flags above because MotionEvent.getButtonState doesn't return stylus tip/eraser state.
    ఎంపిక (action) {
    స్థితి ACTION_HOVER_ENTER:
        SDL_SendPenProximity(0, pen, కిటికీ, true, true);
        ఆపు;

    స్థితి ACTION_CANCEL:
    స్థితి ACTION_HOVER_EXIT:  // strictly speaking, this can mean both "proximity out" and "left the View" but close enough.
        SDL_SendPenProximity(0, pen, కిటికీ, false, false);
        ఆపు;

    స్థితి ACTION_కిందికి:
    స్థితి ACTION_సూచిక_కిందికి:
        SDL_SendPenTouch(0, pen, కిటికీ, (button & SDL_PEN_ఆదానం_ERASER_TIP) != 0, true);
        ఆపు;

    స్థితి ACTION_పైకి:
    స్థితి ACTION_సూచిక_పైకి:
        SDL_SendPenTouch(0, pen, కిటికీ, (button & SDL_PEN_ఆదానం_ERASER_TIP) != 0, false);
        ఆపు;

    అప్రమేయ:
        ఆపు;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
