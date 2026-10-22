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

#که_تعریف_شوی SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/touch.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitatouch.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"

Sce_Touch_معلومات touch_old[SCE_TOUCH_پورټ_MAX_عدد];
Sce_Touch_معلومات touch[SCE_TOUCH_پورټ_MAX_عدد];

SDL_FRect area_info[SCE_TOUCH_پورټ_MAX_عدد];

بنية
{
    عائم min;
    عائم range;
} force_info[SCE_TOUCH_پورټ_MAX_عدد];

ساكن bool disableFrontPoll;
ساكن bool disable_شا_Poll;

فراغ VITA_InitTouch(فراغ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_شا_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_شا_TOUCH, true);

    sce_Touch_سېټ_Sampling_State(SCE_TOUCH_پورټ_FRONT, SCE_TOUCH_SAMPLING_STATE_پیل);
    sce_Touch_سېټ_Sampling_State(SCE_TOUCH_پورټ_شا, SCE_TOUCH_SAMPLING_STATE_پیل);
    sceTouchEnableTouchForce(SCE_TOUCH_پورټ_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_پورټ_شا);

    لكل (صحيح پورټ = 0; پورټ < SCE_TOUCH_پورټ_MAX_عدد; پورټ++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(پورټ, &panelinfo);

        area_info[پورټ].x = (عائم)panelinfo.minAaX;
        area_info[پورټ].y = (عائم)panelinfo.minAaY;
        area_info[پورټ].w = (عائم)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[پورټ].h = (عائم)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[پورټ].min = (عائم)panelinfo.minForce;
        force_info[پورټ].range = (عائم)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_جمع_کړه_Touch(1, SDL_TOUCH_DEVICE_مستقیم, "Front");
    SDL_جمع_کړه_Touch(2, SDL_TOUCH_DEVICE_غیرمستقیم_ABSOLUTE, "Back");
}

فراغ VITA_QuitTouch(فراغ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_پورټ_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_پورټ_شا);
}

فراغ VITA_PollTouch(فراغ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    صحيح پورټ;

    // We skip polling touch if no window is created
    إذا (!Vita_کړکۍ) {
        أرجع;
    }

    SDL_memcpy(touch_old, touch, حجم(touch_old));

    لكل (پورټ = 0; پورټ < SCE_TOUCH_پورټ_MAX_عدد; پورټ++) {
        /** Skip polling of Touch Device if hint is set **/
        إذا (((پورټ == 0) && disableFrontPoll) || ((پورټ == 1) && disable_شا_Poll)) {
            استمر;
        }
        sceTouchPeek(پورټ, &touch[پورټ], 1);

        touch_id = (SDL_TouchID)(پورټ + 1);

        إذا (touch[پورټ].report_عدد > 0) {
            لكل (صحيح i = 0; i < touch[پورټ].report_عدد; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                عائم x = 0;
                عائم y = 0;
                عائم force = (touch[پورټ].report[i].force - force_info[پورټ].min) / force_info[پورټ].range;
                صحيح finger_ښکته = 0;

                إذا (touch_old[پورټ].report_عدد > 0) {
                    لكل (صحيح j = 0; j < touch_old[پورټ].report_عدد; j++) {
                        إذا (touch[پورټ].report[i].id == touch_old[پورټ].report[j].id) {
                            finger_ښکته = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[پورټ].report[i].x, touch[پورټ].report[i].y, پورټ);
                finger_id = (SDL_FingerID)(touch[پورټ].report[i].id + 1);

                // Skip if finger was already previously down
                إذا (!finger_ښکته) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کړکۍ, SDL_EVENT_FINGER_ښکته, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_کړکۍ, x, y, force);
            }
        }

        // some fingers might have been let go
        إذا (touch_old[پورټ].report_عدد > 0) {
            لكل (صحيح i = 0; i < touch_old[پورټ].report_عدد; i++) {
                صحيح finger_پورته = 1;
                إذا (touch[پورټ].report_عدد > 0) {
                    لكل (صحيح j = 0; j < touch[پورټ].report_عدد; j++) {
                        إذا (touch[پورټ].report[j].id == touch_old[پورټ].report[i].id) {
                            finger_پورته = 0;
                        }
                    }
                }
                إذا (finger_پورته == 1) {
                    عائم x = 0;
                    عائم y = 0;
                    عائم force = (touch_old[پورټ].report[i].force - force_info[پورټ].min) / force_info[پورټ].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[پورټ].report[i].x, touch_old[پورټ].report[i].y, پورټ);
                    finger_id = (SDL_FingerID)(touch_old[پورټ].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کړکۍ, SDL_EVENT_FINGER_پورته, x, y, force);
                }
            }
        }
    }
}

فراغ VITA_ConvertTouchXYToSDLXY(عائم *sdl_x, عائم *sdl_y, صحيح vita_x, صحيح vita_y, صحيح پورټ)
{
    عائم x, y;

    إذا (area_info[پورټ].w <= 1) {
        x = 0.5f;
    } وإلا {
        x = (vita_x - area_info[پورټ].x) / (area_info[پورټ].w - 1);
    }
    إذا (area_info[پورټ].h <= 1) {
        y = 0.5f;
    } وإلا {
        y = (vita_y - area_info[پورټ].y) / (area_info[پورټ].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#د_که_پای // SDL_VIDEO_DRIVER_VITA
