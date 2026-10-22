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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/touch.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitatouch.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"

Sce_Touch_داده touch_old[SCE_TOUCH_پورت_MAX_رقم];
Sce_Touch_داده touch[SCE_TOUCH_پورت_MAX_رقم];

SDL_FRect area_info[SCE_TOUCH_پورت_MAX_رقم];

بنية
{
    عائم min;
    عائم range;
} force_info[SCE_TOUCH_پورت_MAX_رقم];

ساكن bool disableFrontPoll;
ساكن bool disable_پشت_Poll;

فراغ VITA_InitTouch(فراغ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_پشت_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_پشت_TOUCH, true);

    sce_Touch_مجموعه_Sampling_State(SCE_TOUCH_پورت_FRONT, SCE_TOUCH_SAMPLING_STATE_شروع);
    sce_Touch_مجموعه_Sampling_State(SCE_TOUCH_پورت_پشت, SCE_TOUCH_SAMPLING_STATE_شروع);
    sceTouchEnableTouchForce(SCE_TOUCH_پورت_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_پورت_پشت);

    لكل (صحيح پورت = 0; پورت < SCE_TOUCH_پورت_MAX_رقم; پورت++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(پورت, &panelinfo);

        area_info[پورت].x = (عائم)panelinfo.minAaX;
        area_info[پورت].y = (عائم)panelinfo.minAaY;
        area_info[پورت].w = (عائم)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[پورت].h = (عائم)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[پورت].min = (عائم)panelinfo.minForce;
        force_info[پورت].range = (عائم)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_جمع_کن_Touch(1, SDL_TOUCH_DEVICE_مستقیم, "Front");
    SDL_جمع_کن_Touch(2, SDL_TOUCH_DEVICE_غیرمستقیم_ABSOLUTE, "Back");
}

فراغ VITA_QuitTouch(فراغ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_پورت_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_پورت_پشت);
}

فراغ VITA_PollTouch(فراغ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    صحيح پورت;

    // We skip polling touch if no window is created
    إذا (!Vita_پنجره) {
        أرجع;
    }

    SDL_memcpy(touch_old, touch, حجم(touch_old));

    لكل (پورت = 0; پورت < SCE_TOUCH_پورت_MAX_رقم; پورت++) {
        /** Skip polling of Touch Device if hint is set **/
        إذا (((پورت == 0) && disableFrontPoll) || ((پورت == 1) && disable_پشت_Poll)) {
            استمر;
        }
        sceTouchPeek(پورت, &touch[پورت], 1);

        touch_id = (SDL_TouchID)(پورت + 1);

        إذا (touch[پورت].report_رقم > 0) {
            لكل (صحيح i = 0; i < touch[پورت].report_رقم; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                عائم x = 0;
                عائم y = 0;
                عائم force = (touch[پورت].report[i].force - force_info[پورت].min) / force_info[پورت].range;
                صحيح finger_پایین = 0;

                إذا (touch_old[پورت].report_رقم > 0) {
                    لكل (صحيح j = 0; j < touch_old[پورت].report_رقم; j++) {
                        إذا (touch[پورت].report[i].id == touch_old[پورت].report[j].id) {
                            finger_پایین = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[پورت].report[i].x, touch[پورت].report[i].y, پورت);
                finger_id = (SDL_FingerID)(touch[پورت].report[i].id + 1);

                // Skip if finger was already previously down
                إذا (!finger_پایین) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_پنجره, SDL_EVENT_FINGER_پایین, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_پنجره, x, y, force);
            }
        }

        // some fingers might have been let go
        إذا (touch_old[پورت].report_رقم > 0) {
            لكل (صحيح i = 0; i < touch_old[پورت].report_رقم; i++) {
                صحيح finger_به_بالا = 1;
                إذا (touch[پورت].report_رقم > 0) {
                    لكل (صحيح j = 0; j < touch[پورت].report_رقم; j++) {
                        إذا (touch[پورت].report[j].id == touch_old[پورت].report[i].id) {
                            finger_به_بالا = 0;
                        }
                    }
                }
                إذا (finger_به_بالا == 1) {
                    عائم x = 0;
                    عائم y = 0;
                    عائم force = (touch_old[پورت].report[i].force - force_info[پورت].min) / force_info[پورت].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[پورت].report[i].x, touch_old[پورت].report[i].y, پورت);
                    finger_id = (SDL_FingerID)(touch_old[پورت].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_پنجره, SDL_EVENT_FINGER_به_بالا, x, y, force);
                }
            }
        }
    }
}

فراغ VITA_ConvertTouchXYToSDLXY(عائم *sdl_x, عائم *sdl_y, صحيح vita_x, صحيح vita_y, صحيح پورت)
{
    عائم x, y;

    إذا (area_info[پورت].w <= 1) {
        x = 0.5f;
    } وإلا {
        x = (vita_x - area_info[پورت].x) / (area_info[پورت].w - 1);
    }
    إذا (area_info[پورت].h <= 1) {
        y = 0.5f;
    } وإلا {
        y = (vita_y - area_info[پورت].y) / (area_info[پورت].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#پایان_اگر // SDL_VIDEO_DRIVER_VITA
