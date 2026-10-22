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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাৱ <psp2/kernel/processmgr.h>
#অন্তর্ভাৱ <psp2/touch.h>

#অন্তর্ভাৱ "SDL_vitavideo.h"
#অন্তর্ভাৱ "SDL_vitatouch.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_অঙ্ক];
SceTouchData touch[SCE_TOUCH_PORT_MAX_অঙ্ক];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_অঙ্ক];

সংরচনা
{
    ভিন্ন min;
    ভিন্ন range;
} force_info[SCE_TOUCH_PORT_MAX_অঙ্ক];

স্থির bool disableFrontPoll;
স্থির bool disableBackPoll;

শূন্য VITA_InitTouch(শূন্য)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    বাবে (পূর্ণাঙ্ক port = 0; port < SCE_TOUCH_PORT_MAX_অঙ্ক; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (ভিন্ন)panelinfo.minAaX;
        area_info[port].y = (ভিন্ন)panelinfo.minAaY;
        area_info[port].w = (ভিন্ন)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (ভিন্ন)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (ভিন্ন)panelinfo.minForce;
        force_info[port].range = (ভিন্ন)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

শূন্য VITA_QuitTouch(শূন্য)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

শূন্য VITA_PollTouch(শূন্য)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    পূর্ণাঙ্ক port;

    // We skip polling touch if no window is created
    যদি (!Vita_Window) {
        ঘূৰাই;
    }

    SDL_memcpy(touch_old, touch, পরিমাণ(touch_old));

    বাবে (port = 0; port < SCE_TOUCH_PORT_MAX_অঙ্ক; port++) {
        /** Skip polling of Touch Device if hint is set **/
        যদি (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            অনুৱর্ত;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        যদি (touch[port].report_অঙ্ক > 0) {
            বাবে (পূর্ণাঙ্ক i = 0; i < touch[port].report_অঙ্ক; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                ভিন্ন x = 0;
                ভিন্ন y = 0;
                ভিন্ন force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                পূর্ণাঙ্ক finger_down = 0;

                যদি (touch_old[port].report_অঙ্ক > 0) {
                    বাবে (পূর্ণাঙ্ক j = 0; j < touch_old[port].report_অঙ্ক; j++) {
                        যদি (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                যদি (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        যদি (touch_old[port].report_অঙ্ক > 0) {
            বাবে (পূর্ণাঙ্ক i = 0; i < touch_old[port].report_অঙ্ক; i++) {
                পূর্ণাঙ্ক finger_up = 1;
                যদি (touch[port].report_অঙ্ক > 0) {
                    বাবে (পূর্ণাঙ্ক j = 0; j < touch[port].report_অঙ্ক; j++) {
                        যদি (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                যদি (finger_up == 1) {
                    ভিন্ন x = 0;
                    ভিন্ন y = 0;
                    ভিন্ন force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

শূন্য VITA_ConvertTouchXYToSDLXY(ভিন্ন *sdl_x, ভিন্ন *sdl_y, পূর্ণাঙ্ক vita_x, পূর্ণাঙ্ক vita_y, পূর্ণাঙ্ক port)
{
    ভিন্ন x, y;

    যদি (area_info[port].w <= 1) {
        x = 0.5f;
    } অন্যথা {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    যদি (area_info[port].h <= 1) {
        y = 0.5f;
    } অন্যথা {
        y = (vita_y - area_info[port].y) / (area_info[port].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#endif // SDL_VIDEO_DRIVER_VITA
