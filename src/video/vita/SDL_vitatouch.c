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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ଅନ୍ତର୍ଭାଵ <psp2/kernel/processmgr.h>
#ଅନ୍ତର୍ଭାଵ <psp2/touch.h>

#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitatouch.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_ଅଙ୍କ];
SceTouchData touch[SCE_TOUCH_PORT_MAX_ଅଙ୍କ];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_ଅଙ୍କ];

ସଂରଚନା
{
    ଦଶମିକ min;
    ଦଶମିକ range;
} force_info[SCE_TOUCH_PORT_MAX_ଅଙ୍କ];

ସ୍ଥିର bool disableFrontPoll;
ସ୍ଥିର bool disableBackPoll;

ଶୂନ୍ୟ VITA_InitTouch(ଶୂନ୍ୟ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା port = 0; port < SCE_TOUCH_PORT_MAX_ଅଙ୍କ; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (ଦଶମିକ)panelinfo.minAaX;
        area_info[port].y = (ଦଶମିକ)panelinfo.minAaY;
        area_info[port].w = (ଦଶମିକ)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (ଦଶମିକ)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (ଦଶମିକ)panelinfo.minForce;
        force_info[port].range = (ଦଶମିକ)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

ଶୂନ୍ୟ VITA_QuitTouch(ଶୂନ୍ୟ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

ଶୂନ୍ୟ VITA_PollTouch(ଶୂନ୍ୟ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା port;

    // We skip polling touch if no window is created
    ଯଦି (!Vita_Window) {
        ଫେରନ୍ତୁ;
    }

    SDL_memcpy(touch_old, touch, ଆକାର(touch_old));

    ପାଇଁ (port = 0; port < SCE_TOUCH_PORT_MAX_ଅଙ୍କ; port++) {
        /** Skip polling of Touch Device if hint is set **/
        ଯଦି (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            ଜାରି;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        ଯଦି (touch[port].report_ଅଙ୍କ > 0) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < touch[port].report_ଅଙ୍କ; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                ଦଶମିକ x = 0;
                ଦଶମିକ y = 0;
                ଦଶମିକ force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା finger_down = 0;

                ଯଦି (touch_old[port].report_ଅଙ୍କ > 0) {
                    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < touch_old[port].report_ଅଙ୍କ; j++) {
                        ଯଦି (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                ଯଦି (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        ଯଦି (touch_old[port].report_ଅଙ୍କ > 0) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < touch_old[port].report_ଅଙ୍କ; i++) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା finger_up = 1;
                ଯଦି (touch[port].report_ଅଙ୍କ > 0) {
                    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < touch[port].report_ଅଙ୍କ; j++) {
                        ଯଦି (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                ଯଦି (finger_up == 1) {
                    ଦଶମିକ x = 0;
                    ଦଶମିକ y = 0;
                    ଦଶମିକ force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

ଶୂନ୍ୟ VITA_ConvertTouchXYToSDLXY(ଦଶମିକ *sdl_x, ଦଶମିକ *sdl_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vita_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vita_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା port)
{
    ଦଶମିକ x, y;

    ଯଦି (area_info[port].w <= 1) {
        x = 0.5f;
    } ଅନ୍ୟଥା {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    ଯଦି (area_info[port].h <= 1) {
        y = 0.5f;
    } ଅନ୍ୟଥା {
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
