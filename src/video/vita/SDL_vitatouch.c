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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#અન્તર્ભાવ <psp2/kernel/processmgr.h>
#અન્તર્ભાવ <psp2/touch.h>

#અન્તર્ભાવ "SDL_vitavideo.h"
#અન્તર્ભાવ "SDL_vitatouch.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_અંક];
SceTouchData touch[SCE_TOUCH_PORT_MAX_અંક];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_અંક];

સંરચના
{
    દશાંશ min;
    દશાંશ range;
} force_info[SCE_TOUCH_PORT_MAX_અંક];

સ્થિર bool disableFrontPoll;
સ્થિર bool disableBackPoll;

શૂન્ય VITA_InitTouch(શૂન્ય)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    માટે (પૂર્ણાંક port = 0; port < SCE_TOUCH_PORT_MAX_અંક; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (દશાંશ)panelinfo.minAaX;
        area_info[port].y = (દશાંશ)panelinfo.minAaY;
        area_info[port].w = (દશાંશ)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (દશાંશ)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (દશાંશ)panelinfo.minForce;
        force_info[port].range = (દશાંશ)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

શૂન્ય VITA_QuitTouch(શૂન્ય)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

શૂન્ય VITA_PollTouch(શૂન્ય)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    પૂર્ણાંક port;

    // We skip polling touch if no window is created
    જો (!Vita_Window) {
        પાછા;
    }

    SDL_memcpy(touch_old, touch, કદ(touch_old));

    માટે (port = 0; port < SCE_TOUCH_PORT_MAX_અંક; port++) {
        /** Skip polling of Touch Device if hint is set **/
        જો (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            ચાલુ;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        જો (touch[port].report_અંક > 0) {
            માટે (પૂર્ણાંક i = 0; i < touch[port].report_અંક; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                દશાંશ x = 0;
                દશાંશ y = 0;
                દશાંશ force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                પૂર્ણાંક finger_down = 0;

                જો (touch_old[port].report_અંક > 0) {
                    માટે (પૂર્ણાંક j = 0; j < touch_old[port].report_અંક; j++) {
                        જો (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                જો (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        જો (touch_old[port].report_અંક > 0) {
            માટે (પૂર્ણાંક i = 0; i < touch_old[port].report_અંક; i++) {
                પૂર્ણાંક finger_up = 1;
                જો (touch[port].report_અંક > 0) {
                    માટે (પૂર્ણાંક j = 0; j < touch[port].report_અંક; j++) {
                        જો (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                જો (finger_up == 1) {
                    દશાંશ x = 0;
                    દશાંશ y = 0;
                    દશાંશ force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

શૂન્ય VITA_ConvertTouchXYToSDLXY(દશાંશ *sdl_x, દશાંશ *sdl_y, પૂર્ણાંક vita_x, પૂર્ણાંક vita_y, પૂર્ણાંક port)
{
    દશાંશ x, y;

    જો (area_info[port].w <= 1) {
        x = 0.5f;
    } નહીંતર {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    જો (area_info[port].h <= 1) {
        y = 0.5f;
    } નહીંતર {
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
