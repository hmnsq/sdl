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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

#అన్తర్భావ <psp2/kernel/processmgr.h>
#అన్తర్భావ <psp2/touch.h>

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "SDL_vitatouch.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"

Sce_Touch_దత్తాంశం touch_old[SCE_TOUCH_పోర్టు_MAX_అంకె];
Sce_Touch_దత్తాంశం touch[SCE_TOUCH_పోర్టు_MAX_అంకె];

SDL_FRect area_info[SCE_TOUCH_పోర్టు_MAX_అంకె];

నిర్మాణం
{
    దశాంశం min;
    దశాంశం range;
} force_info[SCE_TOUCH_పోర్టు_MAX_అంకె];

స్థిర bool disableFrontPoll;
స్థిర bool disable_వెనుక_Poll;

శూన్య VITA_InitTouch(శూన్య)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_వెనుక_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_వెనుక_TOUCH, true);

    sce_Touch_సమితి_Sampling_State(SCE_TOUCH_పోర్టు_FRONT, SCE_TOUCH_SAMPLING_STATE_ప్రారంభం);
    sce_Touch_సమితి_Sampling_State(SCE_TOUCH_పోర్టు_వెనుక, SCE_TOUCH_SAMPLING_STATE_ప్రారంభం);
    sceTouchEnableTouchForce(SCE_TOUCH_పోర్టు_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_పోర్టు_వెనుక);

    కొరకు (పూర్ణాంకం పోర్టు = 0; పోర్టు < SCE_TOUCH_పోర్టు_MAX_అంకె; పోర్టు++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(పోర్టు, &panelinfo);

        area_info[పోర్టు].x = (దశాంశం)panelinfo.minAaX;
        area_info[పోర్టు].y = (దశాంశం)panelinfo.minAaY;
        area_info[పోర్టు].w = (దశాంశం)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[పోర్టు].h = (దశాంశం)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[పోర్టు].min = (దశాంశం)panelinfo.minForce;
        force_info[పోర్టు].range = (దశాంశం)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_కూడు_Touch(1, SDL_TOUCH_DEVICE_ప్రత్యక్ష, "Front");
    SDL_కూడు_Touch(2, SDL_TOUCH_DEVICE_పరోక్ష_ABSOLUTE, "Back");
}

శూన్య VITA_QuitTouch(శూన్య)
{
    sceTouchDisableTouchForce(SCE_TOUCH_పోర్టు_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_పోర్టు_వెనుక);
}

శూన్య VITA_PollTouch(శూన్య)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    పూర్ణాంకం పోర్టు;

    // We skip polling touch if no window is created
    ఒకవేళ (!Vita_కిటికీ) {
        తిరిగి;
    }

    SDL_memcpy(touch_old, touch, పరిమాణం(touch_old));

    కొరకు (పోర్టు = 0; పోర్టు < SCE_TOUCH_పోర్టు_MAX_అంకె; పోర్టు++) {
        /** Skip polling of Touch Device if hint is set **/
        ఒకవేళ (((పోర్టు == 0) && disableFrontPoll) || ((పోర్టు == 1) && disable_వెనుక_Poll)) {
            కొనసాగు;
        }
        sceTouchPeek(పోర్టు, &touch[పోర్టు], 1);

        touch_id = (SDL_TouchID)(పోర్టు + 1);

        ఒకవేళ (touch[పోర్టు].report_అంకె > 0) {
            కొరకు (పూర్ణాంకం i = 0; i < touch[పోర్టు].report_అంకె; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                దశాంశం x = 0;
                దశాంశం y = 0;
                దశాంశం force = (touch[పోర్టు].report[i].force - force_info[పోర్టు].min) / force_info[పోర్టు].range;
                పూర్ణాంకం finger_కిందికి = 0;

                ఒకవేళ (touch_old[పోర్టు].report_అంకె > 0) {
                    కొరకు (పూర్ణాంకం j = 0; j < touch_old[పోర్టు].report_అంకె; j++) {
                        ఒకవేళ (touch[పోర్టు].report[i].id == touch_old[పోర్టు].report[j].id) {
                            finger_కిందికి = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[పోర్టు].report[i].x, touch[పోర్టు].report[i].y, పోర్టు);
                finger_id = (SDL_FingerID)(touch[పోర్టు].report[i].id + 1);

                // Skip if finger was already previously down
                ఒకవేళ (!finger_కిందికి) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_కిటికీ, SDL_EVENT_FINGER_కిందికి, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_కిటికీ, x, y, force);
            }
        }

        // some fingers might have been let go
        ఒకవేళ (touch_old[పోర్టు].report_అంకె > 0) {
            కొరకు (పూర్ణాంకం i = 0; i < touch_old[పోర్టు].report_అంకె; i++) {
                పూర్ణాంకం finger_పైకి = 1;
                ఒకవేళ (touch[పోర్టు].report_అంకె > 0) {
                    కొరకు (పూర్ణాంకం j = 0; j < touch[పోర్టు].report_అంకె; j++) {
                        ఒకవేళ (touch[పోర్టు].report[j].id == touch_old[పోర్టు].report[i].id) {
                            finger_పైకి = 0;
                        }
                    }
                }
                ఒకవేళ (finger_పైకి == 1) {
                    దశాంశం x = 0;
                    దశాంశం y = 0;
                    దశాంశం force = (touch_old[పోర్టు].report[i].force - force_info[పోర్టు].min) / force_info[పోర్టు].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[పోర్టు].report[i].x, touch_old[పోర్టు].report[i].y, పోర్టు);
                    finger_id = (SDL_FingerID)(touch_old[పోర్టు].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_కిటికీ, SDL_EVENT_FINGER_పైకి, x, y, force);
                }
            }
        }
    }
}

శూన్య VITA_ConvertTouchXYToSDLXY(దశాంశం *sdl_x, దశాంశం *sdl_y, పూర్ణాంకం vita_x, పూర్ణాంకం vita_y, పూర్ణాంకం పోర్టు)
{
    దశాంశం x, y;

    ఒకవేళ (area_info[పోర్టు].w <= 1) {
        x = 0.5f;
    } లేకపోతే {
        x = (vita_x - area_info[పోర్టు].x) / (area_info[పోర్టు].w - 1);
    }
    ఒకవేళ (area_info[పోర్టు].h <= 1) {
        y = 0.5f;
    } లేకపోతే {
        y = (vita_y - area_info[పోర్టు].y) / (area_info[పోర్టు].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA
