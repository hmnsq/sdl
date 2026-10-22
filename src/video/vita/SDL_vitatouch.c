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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#അന്തര്ഭാവ <psp2/kernel/processmgr.h>
#അന്തര്ഭാവ <psp2/touch.h>

#അന്തര്ഭാവ "SDL_vitavideo.h"
#അന്തര്ഭാവ "SDL_vitatouch.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_അക്കം];
SceTouchData touch[SCE_TOUCH_PORT_MAX_അക്കം];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_അക്കം];

ഘടന
{
    ദശാംശം min;
    ദശാംശം range;
} force_info[SCE_TOUCH_PORT_MAX_അക്കം];

സ്ഥിതം bool disableFrontPoll;
സ്ഥിതം bool disableBackPoll;

ശൂന്യം VITA_InitTouch(ശൂന്യം)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    വേണ്ടി (പൂർണ്ണസംഖ്യ port = 0; port < SCE_TOUCH_PORT_MAX_അക്കം; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (ദശാംശം)panelinfo.minAaX;
        area_info[port].y = (ദശാംശം)panelinfo.minAaY;
        area_info[port].w = (ദശാംശം)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (ദശാംശം)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (ദശാംശം)panelinfo.minForce;
        force_info[port].range = (ദശാംശം)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

ശൂന്യം VITA_QuitTouch(ശൂന്യം)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

ശൂന്യം VITA_PollTouch(ശൂന്യം)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    പൂർണ്ണസംഖ്യ port;

    // We skip polling touch if no window is created
    എങ്കിൽ (!Vita_Window) {
        തിരികെ;
    }

    SDL_memcpy(touch_old, touch, വലുപ്പം(touch_old));

    വേണ്ടി (port = 0; port < SCE_TOUCH_PORT_MAX_അക്കം; port++) {
        /** Skip polling of Touch Device if hint is set **/
        എങ്കിൽ (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            തുടരുക;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        എങ്കിൽ (touch[port].report_അക്കം > 0) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < touch[port].report_അക്കം; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                ദശാംശം x = 0;
                ദശാംശം y = 0;
                ദശാംശം force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                പൂർണ്ണസംഖ്യ finger_down = 0;

                എങ്കിൽ (touch_old[port].report_അക്കം > 0) {
                    വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < touch_old[port].report_അക്കം; j++) {
                        എങ്കിൽ (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                എങ്കിൽ (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        എങ്കിൽ (touch_old[port].report_അക്കം > 0) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < touch_old[port].report_അക്കം; i++) {
                പൂർണ്ണസംഖ്യ finger_up = 1;
                എങ്കിൽ (touch[port].report_അക്കം > 0) {
                    വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < touch[port].report_അക്കം; j++) {
                        എങ്കിൽ (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                എങ്കിൽ (finger_up == 1) {
                    ദശാംശം x = 0;
                    ദശാംശം y = 0;
                    ദശാംശം force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

ശൂന്യം VITA_ConvertTouchXYToSDLXY(ദശാംശം *sdl_x, ദശാംശം *sdl_y, പൂർണ്ണസംഖ്യ vita_x, പൂർണ്ണസംഖ്യ vita_y, പൂർണ്ണസംഖ്യ port)
{
    ദശാംശം x, y;

    എങ്കിൽ (area_info[port].w <= 1) {
        x = 0.5f;
    } അല്ലെങ്കിൽ {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    എങ്കിൽ (area_info[port].h <= 1) {
        y = 0.5f;
    } അല്ലെങ്കിൽ {
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
