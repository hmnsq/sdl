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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/touch.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitatouch.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"

Sce_Touch_معلومات touch_old[SCE_TOUCH_پورٽ_MAX_انگ];
Sce_Touch_معلومات touch[SCE_TOUCH_پورٽ_MAX_انگ];

SDL_FRect area_info[SCE_TOUCH_پورٽ_MAX_انگ];

بنية
{
    عائم min;
    عائم range;
} force_info[SCE_TOUCH_پورٽ_MAX_انگ];

ساكن bool disableFrontPoll;
ساكن bool disable_پٺ_Poll;

فراغ VITA_InitTouch(فراغ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_پٺ_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_پٺ_TOUCH, true);

    sce_Touch_سيٽ_Sampling_State(SCE_TOUCH_پورٽ_FRONT, SCE_TOUCH_SAMPLING_STATE_شروعات);
    sce_Touch_سيٽ_Sampling_State(SCE_TOUCH_پورٽ_پٺ, SCE_TOUCH_SAMPLING_STATE_شروعات);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٽ_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٽ_پٺ);

    لكل (صحيح پورٽ = 0; پورٽ < SCE_TOUCH_پورٽ_MAX_انگ; پورٽ++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(پورٽ, &panelinfo);

        area_info[پورٽ].x = (عائم)panelinfo.minAaX;
        area_info[پورٽ].y = (عائم)panelinfo.minAaY;
        area_info[پورٽ].w = (عائم)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[پورٽ].h = (عائم)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[پورٽ].min = (عائم)panelinfo.minForce;
        force_info[پورٽ].range = (عائم)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_جوڙيو_Touch(1, SDL_TOUCH_DEVICE_سڌو, "Front");
    SDL_جوڙيو_Touch(2, SDL_TOUCH_DEVICE_اڻسڌو_ABSOLUTE, "Back");
}

فراغ VITA_QuitTouch(فراغ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_پورٽ_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_پورٽ_پٺ);
}

فراغ VITA_PollTouch(فراغ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    صحيح پورٽ;

    // We skip polling touch if no window is created
    إذا (!Vita_دري) {
        أرجع;
    }

    SDL_memcpy(touch_old, touch, حجم(touch_old));

    لكل (پورٽ = 0; پورٽ < SCE_TOUCH_پورٽ_MAX_انگ; پورٽ++) {
        /** Skip polling of Touch Device if hint is set **/
        إذا (((پورٽ == 0) && disableFrontPoll) || ((پورٽ == 1) && disable_پٺ_Poll)) {
            استمر;
        }
        sceTouchPeek(پورٽ, &touch[پورٽ], 1);

        touch_id = (SDL_TouchID)(پورٽ + 1);

        إذا (touch[پورٽ].report_انگ > 0) {
            لكل (صحيح i = 0; i < touch[پورٽ].report_انگ; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                عائم x = 0;
                عائم y = 0;
                عائم force = (touch[پورٽ].report[i].force - force_info[پورٽ].min) / force_info[پورٽ].range;
                صحيح finger_هيٺ_ڏانهن = 0;

                إذا (touch_old[پورٽ].report_انگ > 0) {
                    لكل (صحيح j = 0; j < touch_old[پورٽ].report_انگ; j++) {
                        إذا (touch[پورٽ].report[i].id == touch_old[پورٽ].report[j].id) {
                            finger_هيٺ_ڏانهن = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[پورٽ].report[i].x, touch[پورٽ].report[i].y, پورٽ);
                finger_id = (SDL_FingerID)(touch[پورٽ].report[i].id + 1);

                // Skip if finger was already previously down
                إذا (!finger_هيٺ_ڏانهن) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_دري, SDL_EVENT_FINGER_هيٺ_ڏانهن, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_دري, x, y, force);
            }
        }

        // some fingers might have been let go
        إذا (touch_old[پورٽ].report_انگ > 0) {
            لكل (صحيح i = 0; i < touch_old[پورٽ].report_انگ; i++) {
                صحيح finger_مٿي = 1;
                إذا (touch[پورٽ].report_انگ > 0) {
                    لكل (صحيح j = 0; j < touch[پورٽ].report_انگ; j++) {
                        إذا (touch[پورٽ].report[j].id == touch_old[پورٽ].report[i].id) {
                            finger_مٿي = 0;
                        }
                    }
                }
                إذا (finger_مٿي == 1) {
                    عائم x = 0;
                    عائم y = 0;
                    عائم force = (touch_old[پورٽ].report[i].force - force_info[پورٽ].min) / force_info[پورٽ].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[پورٽ].report[i].x, touch_old[پورٽ].report[i].y, پورٽ);
                    finger_id = (SDL_FingerID)(touch_old[پورٽ].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_دري, SDL_EVENT_FINGER_مٿي, x, y, force);
                }
            }
        }
    }
}

فراغ VITA_ConvertTouchXYToSDLXY(عائم *sdl_x, عائم *sdl_y, صحيح vita_x, صحيح vita_y, صحيح پورٽ)
{
    عائم x, y;

    إذا (area_info[پورٽ].w <= 1) {
        x = 0.5f;
    } وإلا {
        x = (vita_x - area_info[پورٽ].x) / (area_info[پورٽ].w - 1);
    }
    إذا (area_info[پورٽ].h <= 1) {
        y = 0.5f;
    } وإلا {
        y = (vita_y - area_info[پورٽ].y) / (area_info[پورٽ].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VITA
