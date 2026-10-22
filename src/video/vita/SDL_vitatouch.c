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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव <psp2/touch.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitatouch.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

SceTouchData touch_old[SCE_TOUCH_PORT_MAX_अङ्क];
SceTouchData touch[SCE_TOUCH_PORT_MAX_अङ्क];

SDL_FRect area_info[SCE_TOUCH_PORT_MAX_अङ्क];

संरचना
{
    भिन्न min;
    भिन्न range;
} force_info[SCE_TOUCH_PORT_MAX_अङ्क];

स्थिर bool disableFrontPoll;
स्थिर bool disableBackPoll;

शून्य VITA_InitTouch(शून्य)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disableBackPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_BACK_TOUCH, true);

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);

    लागि (पूर्णाङ्क port = 0; port < SCE_TOUCH_PORT_MAX_अङ्क; port++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(port, &panelinfo);

        area_info[port].x = (भिन्न)panelinfo.minAaX;
        area_info[port].y = (भिन्न)panelinfo.minAaY;
        area_info[port].w = (भिन्न)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[port].h = (भिन्न)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[port].min = (भिन्न)panelinfo.minForce;
        force_info[port].range = (भिन्न)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_AddTouch(1, SDL_TOUCH_DEVICE_DIRECT, "Front");
    SDL_AddTouch(2, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, "Back");
}

शून्य VITA_QuitTouch(शून्य)
{
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_PORT_BACK);
}

शून्य VITA_PollTouch(शून्य)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    पूर्णाङ्क port;

    // We skip polling touch if no window is created
    यदि (!Vita_Window) {
        फर्काऊ;
    }

    SDL_memcpy(touch_old, touch, परिमाण(touch_old));

    लागि (port = 0; port < SCE_TOUCH_PORT_MAX_अङ्क; port++) {
        /** Skip polling of Touch Device if hint is set **/
        यदि (((port == 0) && disableFrontPoll) || ((port == 1) && disableBackPoll)) {
            जारी;
        }
        sceTouchPeek(port, &touch[port], 1);

        touch_id = (SDL_TouchID)(port + 1);

        यदि (touch[port].report_अङ्क > 0) {
            लागि (पूर्णाङ्क i = 0; i < touch[port].report_अङ्क; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                भिन्न x = 0;
                भिन्न y = 0;
                भिन्न force = (touch[port].report[i].force - force_info[port].min) / force_info[port].range;
                पूर्णाङ्क finger_down = 0;

                यदि (touch_old[port].report_अङ्क > 0) {
                    लागि (पूर्णाङ्क j = 0; j < touch_old[port].report_अङ्क; j++) {
                        यदि (touch[port].report[i].id == touch_old[port].report[j].id) {
                            finger_down = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[port].report[i].x, touch[port].report[i].y, port);
                finger_id = (SDL_FingerID)(touch[port].report[i].id + 1);

                // Skip if finger was already previously down
                यदि (!finger_down) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_DOWN, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_Window, x, y, force);
            }
        }

        // some fingers might have been let go
        यदि (touch_old[port].report_अङ्क > 0) {
            लागि (पूर्णाङ्क i = 0; i < touch_old[port].report_अङ्क; i++) {
                पूर्णाङ्क finger_up = 1;
                यदि (touch[port].report_अङ्क > 0) {
                    लागि (पूर्णाङ्क j = 0; j < touch[port].report_अङ्क; j++) {
                        यदि (touch[port].report[j].id == touch_old[port].report[i].id) {
                            finger_up = 0;
                        }
                    }
                }
                यदि (finger_up == 1) {
                    भिन्न x = 0;
                    भिन्न y = 0;
                    भिन्न force = (touch_old[port].report[i].force - force_info[port].min) / force_info[port].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[port].report[i].x, touch_old[port].report[i].y, port);
                    finger_id = (SDL_FingerID)(touch_old[port].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_Window, SDL_EVENT_FINGER_UP, x, y, force);
                }
            }
        }
    }
}

शून्य VITA_ConvertTouchXYToSDLXY(भिन्न *sdl_x, भिन्न *sdl_y, पूर्णाङ्क vita_x, पूर्णाङ्क vita_y, पूर्णाङ्क port)
{
    भिन्न x, y;

    यदि (area_info[port].w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = (vita_x - area_info[port].x) / (area_info[port].w - 1);
    }
    यदि (area_info[port].h <= 1) {
        y = 0.5f;
    } अन्यथा {
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
