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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>

#include "SDL_vitavideo.h"
#include "SDL_vitatouch.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_NUM];

sa_nracanaa
{
    float min;
    float range;
} force_info[SCE_TOUCH_PORT_MAX_NUM];

static bool disableFrontPoll;
static bool disableBackPoll;

void VITA_InitTouch(void)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    for (puur_naa_nka port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (float)panelinfo.minAaX;
        area_info[port].y = (float)panelinfo.minAaY;
        area_info[port].w = (float)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (float)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (float)panelinfo.minForce;
        force_info[port].range = (float)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

void VITA_QuitTouch(void)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

void VITA_PollTouch(void)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    puur_naa_nka port;

    // We skip polling touch if no window is created
    ᰀᰧ (!Vita_Window) {
        ᰀᰧᰌ;
    }

    SDL_memcpy(touch_old, touch, parimaa_na(touch_old));

    for (port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++) {
        /** Skip polling of Touch Device if hint is set **/
        ᰀᰧ (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            continue;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        ᰀᰧ (touch[port].reportNum > 0) {
            for (puur_naa_nka i = 0; i < touch[port].reportNum; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                float x = 0;
                float y = 0;
                float force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                puur_naa_nka finger_down = 0;

                ᰀᰧ (touch_old[port].reportNum > 0) {
                    for (puur_naa_nka j = 0; j < touch_old[port].reportNum; j++) {
                        ᰀᰧ (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                ᰀᰧ (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        ᰀᰧ (touch_old[port].reportNum > 0) {
            for (puur_naa_nka i = 0; i < touch_old[port].reportNum; i++) {
                puur_naa_nka finger_up = 1;
                ᰀᰧ (touch[port].reportNum > 0) {
                    for (puur_naa_nka j = 0; j < touch[port].reportNum; j++) {
                        ᰀᰧ (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                ᰀᰧ (finger_up == 1) {
                    float x = 0;
                    float y = 0;
                    float force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

void VITA_ConvertTouchXYToSDLXY(float *sdl_x, float *sdl_y, puur_naa_nka vita_x, puur_naa_nka vita_y, puur_naa_nka port)
{
    float x, y;

    ᰀᰧ (area_info[port].w <= 1) {
        x = 0.5f;
    } ᰀᰧᰀ {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    ᰀᰧ (area_info[port].h <= 1) {
        y = 0.5f;
    } ᰀᰧᰀ {
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
