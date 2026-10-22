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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#அந்தர்பாவ <psp2/kernel/processmgr.h>
#அந்தர்பாவ <psp2/touch.h>

#அந்தர்பாவ "SDL_vitavideo.h"
#அந்தர்பாவ "SDL_vitatouch.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_இலக்கம்];
SceTouchData touch[SCE_TOUCH_PORT_MAX_இலக்கம்];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_இலக்கம்];

கட்டமைப்பு
{
    தசம min;
    தசம range;
} force_info[SCE_TOUCH_PORT_MAX_இலக்கம்];

நிலையான bool disableFrontPoll;
நிலையான bool disableBackPoll;

வெறுமை VITA_InitTouch(வெறுமை)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    க்கு (முழு port = 0; port < SCE_TOUCH_PORT_MAX_இலக்கம்; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (தசம)panelinfo.minAaX;
        area_info[port].y = (தசம)panelinfo.minAaY;
        area_info[port].w = (தசம)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (தசம)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (தசம)panelinfo.minForce;
        force_info[port].range = (தசம)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

வெறுமை VITA_QuitTouch(வெறுமை)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

வெறுமை VITA_PollTouch(வெறுமை)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    முழு port;

    // We skip polling touch if no window is created
    எனில் (!Vita_Window) {
        திரும்பு;
    }

    SDL_memcpy(touch_old, touch, அளவு(touch_old));

    க்கு (port = 0; port < SCE_TOUCH_PORT_MAX_இலக்கம்; port++) {
        /** Skip polling of Touch Device if hint is set **/
        எனில் (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            தொடர்;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        எனில் (touch[port].report_இலக்கம் > 0) {
            க்கு (முழு i = 0; i < touch[port].report_இலக்கம்; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                தசம x = 0;
                தசம y = 0;
                தசம force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                முழு finger_down = 0;

                எனில் (touch_old[port].report_இலக்கம் > 0) {
                    க்கு (முழு j = 0; j < touch_old[port].report_இலக்கம்; j++) {
                        எனில் (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                எனில் (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        எனில் (touch_old[port].report_இலக்கம் > 0) {
            க்கு (முழு i = 0; i < touch_old[port].report_இலக்கம்; i++) {
                முழு finger_up = 1;
                எனில் (touch[port].report_இலக்கம் > 0) {
                    க்கு (முழு j = 0; j < touch[port].report_இலக்கம்; j++) {
                        எனில் (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                எனில் (finger_up == 1) {
                    தசம x = 0;
                    தசம y = 0;
                    தசம force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

வெறுமை VITA_ConvertTouchXYToSDLXY(தசம *sdl_x, தசம *sdl_y, முழு vita_x, முழு vita_y, முழு port)
{
    தசம x, y;

    எனில் (area_info[port].w <= 1) {
        x = 0.5f;
    } இல்லையெனில் {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    எனில் (area_info[port].h <= 1) {
        y = 0.5f;
    } இல்லையெனில் {
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
