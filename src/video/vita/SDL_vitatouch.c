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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#شامل <psp2/kernel/processmgr.h>
#شامل <psp2/touch.h>

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitatouch.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_touch_c.h"

Sce_Touch_ڈیٹا touch_old[SCE_TOUCH_پورٹ_MAX_عدد];
Sce_Touch_ڈیٹا touch[SCE_TOUCH_پورٹ_MAX_عدد];

SDL_FRect area_info[SCE_TOUCH_پورٹ_MAX_عدد];

ساخت
{
    اعشاری min;
    اعشاری range;
} force_info[SCE_TOUCH_پورٹ_MAX_عدد];

ساکن bool disableFrontPoll;
ساکن bool disable_عقب_Poll;

خالی VITA_InitTouch(خالی)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_عقب_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_عقب_TOUCH, true);

    sce_Touch_سیٹ_Sampling_State(SCE_TOUCH_پورٹ_FRONT, SCE_TOUCH_SAMPLING_STATE_آغاز);
    sce_Touch_سیٹ_Sampling_State(SCE_TOUCH_پورٹ_عقب, SCE_TOUCH_SAMPLING_STATE_آغاز);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٹ_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_پورٹ_عقب);

    برائے (صحیح پورٹ = 0; پورٹ < SCE_TOUCH_پورٹ_MAX_عدد; پورٹ++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(پورٹ, &panelinfo);

        area_info[پورٹ].x = (اعشاری)panelinfo.minAaX;
        area_info[پورٹ].y = (اعشاری)panelinfo.minAaY;
        area_info[پورٹ].w = (اعشاری)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[پورٹ].h = (اعشاری)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[پورٹ].min = (اعشاری)panelinfo.minForce;
        force_info[پورٹ].range = (اعشاری)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_جوڑو_Touch(1, SDL_TOUCH_DEVICE_براہ_راست, "Front");
    SDL_جوڑو_Touch(2, SDL_TOUCH_DEVICE_بالواسطہ_ABSOLUTE, "Back");
}

خالی VITA_QuitTouch(خالی)
{
    sceTouchDisableTouchForce(SCE_TOUCH_پورٹ_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_پورٹ_عقب);
}

خالی VITA_PollTouch(خالی)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    صحیح پورٹ;

    // We skip polling touch if no window is created
    اگر (!Vita_کھڑکی) {
        واپس;
    }

    SDL_memcpy(touch_old, touch, حجم(touch_old));

    برائے (پورٹ = 0; پورٹ < SCE_TOUCH_پورٹ_MAX_عدد; پورٹ++) {
        /** Skip polling of Touch Device if hint is set **/
        اگر (((پورٹ == 0) && disableFrontPoll) || ((پورٹ == 1) && disable_عقب_Poll)) {
            جاری;
        }
        sceTouchPeek(پورٹ, &touch[پورٹ], 1);

        touch_id = (SDL_TouchID)(پورٹ + 1);

        اگر (touch[پورٹ].report_عدد > 0) {
            برائے (صحیح i = 0; i < touch[پورٹ].report_عدد; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                اعشاری x = 0;
                اعشاری y = 0;
                اعشاری force = (touch[پورٹ].report[i].force - force_info[پورٹ].min) / force_info[پورٹ].range;
                صحیح finger_نیچے_کو = 0;

                اگر (touch_old[پورٹ].report_عدد > 0) {
                    برائے (صحیح j = 0; j < touch_old[پورٹ].report_عدد; j++) {
                        اگر (touch[پورٹ].report[i].id == touch_old[پورٹ].report[j].id) {
                            finger_نیچے_کو = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[پورٹ].report[i].x, touch[پورٹ].report[i].y, پورٹ);
                finger_id = (SDL_FingerID)(touch[پورٹ].report[i].id + 1);

                // Skip if finger was already previously down
                اگر (!finger_نیچے_کو) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کھڑکی, SDL_EVENT_FINGER_نیچے_کو, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_کھڑکی, x, y, force);
            }
        }

        // some fingers might have been let go
        اگر (touch_old[پورٹ].report_عدد > 0) {
            برائے (صحیح i = 0; i < touch_old[پورٹ].report_عدد; i++) {
                صحیح finger_اوپر = 1;
                اگر (touch[پورٹ].report_عدد > 0) {
                    برائے (صحیح j = 0; j < touch[پورٹ].report_عدد; j++) {
                        اگر (touch[پورٹ].report[j].id == touch_old[پورٹ].report[i].id) {
                            finger_اوپر = 0;
                        }
                    }
                }
                اگر (finger_اوپر == 1) {
                    اعشاری x = 0;
                    اعشاری y = 0;
                    اعشاری force = (touch_old[پورٹ].report[i].force - force_info[پورٹ].min) / force_info[پورٹ].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[پورٹ].report[i].x, touch_old[پورٹ].report[i].y, پورٹ);
                    finger_id = (SDL_FingerID)(touch_old[پورٹ].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_کھڑکی, SDL_EVENT_FINGER_اوپر, x, y, force);
                }
            }
        }
    }
}

خالی VITA_ConvertTouchXYToSDLXY(اعشاری *sdl_x, اعشاری *sdl_y, صحیح vita_x, صحیح vita_y, صحیح پورٹ)
{
    اعشاری x, y;

    اگر (area_info[پورٹ].w <= 1) {
        x = 0.5f;
    } ورنہ {
        x = (vita_x - area_info[پورٹ].x) / (area_info[پورٹ].w - 1);
    }
    اگر (area_info[پورٹ].h <= 1) {
        y = 0.5f;
    } ورنہ {
        y = (vita_y - area_info[پورٹ].y) / (area_info[پورٹ].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA
