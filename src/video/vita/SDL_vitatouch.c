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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/touch.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitatouch.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"

Sce_Touch_انکڑے touch_old[SCE_TOUCH_پورٹ_MAX_عدد];
Sce_Touch_انکڑے touch[SCE_TOUCH_پورٹ_MAX_عدد];

SDL_FRect area_info[SCE_TOUCH_پورٹ_MAX_عدد];

بنية
{
    عائم min;
    عائم range;
} force_info[SCE_TOUCH_پورٹ_MAX_عدد];

ساكن bool disableFrontPoll;
ساكن bool disable_پٹھ_Poll;

فراغ VITA_InitTouch(فراغ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_پٹھ_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_پٹھ_TOUCH, true);

    sce_Touch_سیٹ_Sampling_State(SCE_TOUCH_پورٹ_FRONT, SCE_TOUCH_SAMPLING_STATE_شروع);
    sce_Touch_سیٹ_Sampling_State(SCE_TOUCH_پورٹ_پٹھ, SCE_TOUCH_SAMPLING_STATE_شروع);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٹ_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٹ_پٹھ);

    لكل (صحيح پورٹ = 0; پورٹ < SCE_TOUCH_پورٹ_MAX_عدد; پورٹ++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(پورٹ, &panelinfo);

        area_info[پورٹ].x = (عائم)panelinfo.minAaX;
        area_info[پورٹ].y = (عائم)panelinfo.minAaY;
        area_info[پورٹ].w = (عائم)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[پورٹ].h = (عائم)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[پورٹ].min = (عائم)panelinfo.minForce;
        force_info[پورٹ].range = (عائم)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_جوڑو_Touch(1, SDL_TOUCH_DEVICE_سدھا, "Front");
    SDL_جوڑو_Touch(2, SDL_TOUCH_DEVICE_اسدھا_ABSOLUTE, "Back");
}

فراغ VITA_QuitTouch(فراغ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_پورٹ_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_پورٹ_پٹھ);
}

فراغ VITA_PollTouch(فراغ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    صحيح پورٹ;

    // We skip polling touch if no window is created
    إذا (!Vita_کھڑکی) {
        أرجع;
    }

    SDL_memcpy(touch_old, touch, حجم(touch_old));

    لكل (پورٹ = 0; پورٹ < SCE_TOUCH_پورٹ_MAX_عدد; پورٹ++) {
        /** Skip polling of Touch Device if hint is set **/
        إذا (((پورٹ == 0) && disableFrontPoll) || ((پورٹ == 1) && disable_پٹھ_Poll)) {
            استمر;
        }
        sceTouchPeek(پورٹ, &touch[پورٹ], 1);

        touch_id = (SDL_TouchID)(پورٹ + 1);

        إذا (touch[پورٹ].report_عدد > 0) {
            لكل (صحيح i = 0; i < touch[پورٹ].report_عدد; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                عائم x = 0;
                عائم y = 0;
                عائم force = (touch[پورٹ].report[i].force - force_info[پورٹ].min) / force_info[پورٹ].range;
                صحيح finger_تھلے = 0;

                إذا (touch_old[پورٹ].report_عدد > 0) {
                    لكل (صحيح j = 0; j < touch_old[پورٹ].report_عدد; j++) {
                        إذا (touch[پورٹ].report[i].id == touch_old[پورٹ].report[j].id) {
                            finger_تھلے = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[پورٹ].report[i].x, touch[پورٹ].report[i].y, پورٹ);
                finger_id = (SDL_FingerID)(touch[پورٹ].report[i].id + 1);

                // Skip if finger was already previously down
                إذا (!finger_تھلے) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کھڑکی, SDL_EVENT_FINGER_تھلے, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_کھڑکی, x, y, force);
            }
        }

        // some fingers might have been let go
        إذا (touch_old[پورٹ].report_عدد > 0) {
            لكل (صحيح i = 0; i < touch_old[پورٹ].report_عدد; i++) {
                صحيح finger_اتے = 1;
                إذا (touch[پورٹ].report_عدد > 0) {
                    لكل (صحيح j = 0; j < touch[پورٹ].report_عدد; j++) {
                        إذا (touch[پورٹ].report[j].id == touch_old[پورٹ].report[i].id) {
                            finger_اتے = 0;
                        }
                    }
                }
                إذا (finger_اتے == 1) {
                    عائم x = 0;
                    عائم y = 0;
                    عائم force = (touch_old[پورٹ].report[i].force - force_info[پورٹ].min) / force_info[پورٹ].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[پورٹ].report[i].x, touch_old[پورٹ].report[i].y, پورٹ);
                    finger_id = (SDL_FingerID)(touch_old[پورٹ].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کھڑکی, SDL_EVENT_FINGER_اتے, x, y, force);
                }
            }
        }
    }
}

فراغ VITA_ConvertTouchXYToSDLXY(عائم *sdl_x, عائم *sdl_y, صحيح vita_x, صحيح vita_y, صحيح پورٹ)
{
    عائم x, y;

    إذا (area_info[پورٹ].w <= 1) {
        x = 0.5f;
    } وإلا {
        x = (vita_x - area_info[پورٹ].x) / (area_info[پورٹ].w - 1);
    }
    إذا (area_info[پورٹ].h <= 1) {
        y = 0.5f;
    } وإلا {
        y = (vita_y - area_info[پورٹ].y) / (area_info[پورٹ].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#جے_انت // SDL_VIDEO_DRIVER_VITA
