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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव <psp2/touch.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitatouch.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

Sce_Touch_दत्त touch_old[SCE_TOUCH_पत्तनम्_MAX_अङ्कः];
Sce_Touch_दत्त touch[SCE_TOUCH_पत्तनम्_MAX_अङ्कः];

SDL_FRect area_info[SCE_TOUCH_पत्तनम्_MAX_अङ्कः];

संरचना
{
    भिन्न min;
    भिन्न range;
} force_info[SCE_TOUCH_पत्तनम्_MAX_अङ्कः];

स्थिर bool disableFrontPoll;
स्थिर bool disable_पृष्ठभागः_Poll;

शून्य VITA_InitTouch(शून्य)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_पृष्ठभागः_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_पृष्ठभागः_TOUCH, true);

    sce_Touch_समुच्चयः_Sampling_State(SCE_TOUCH_पत्तनम्_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sce_Touch_समुच्चयः_Sampling_State(SCE_TOUCH_पत्तनम्_पृष्ठभागः, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_पत्तनम्_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_पत्तनम्_पृष्ठभागः);

    प्रति (पूर्णाङ्क पत्तनम् = 0; पत्तनम् < SCE_TOUCH_पत्तनम्_MAX_अङ्कः; पत्तनम्++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(पत्तनम्, &panelinfo);

        area_info[पत्तनम्].x = (भिन्न)panelinfo.minAaX;
        area_info[पत्तनम्].y = (भिन्न)panelinfo.minAaY;
        area_info[पत्तनम्].w = (भिन्न)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[पत्तनम्].h = (भिन्न)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[पत्तनम्].min = (भिन्न)panelinfo.minForce;
        force_info[पत्तनम्].range = (भिन्न)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_सङ्कलय_Touch(1, SDL_TOUCH_DEVICE_प्रत्यक्षम्, "Front");
    SDL_सङ्कलय_Touch(2, SDL_TOUCH_DEVICE_परोक्षम्_ABSOLUTE, "Back");
}

शून्य VITA_QuitTouch(शून्य)
{
    sceTouchDisableTouchForce(SCE_TOUCH_पत्तनम्_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_पत्तनम्_पृष्ठभागः);
}

शून्य VITA_PollTouch(शून्य)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    पूर्णाङ्क पत्तनम्;

    // We skip polling touch if no window is created
    यदि (!Vita_गवाक्षः) {
        प्रत्यागम;
    }

    SDL_memcpy(touch_old, touch, परिमाण(touch_old));

    प्रति (पत्तनम् = 0; पत्तनम् < SCE_TOUCH_पत्तनम्_MAX_अङ्कः; पत्तनम्++) {
        /** Skip polling of Touch Device if hint is set **/
        यदि (((पत्तनम् == 0) && disableFrontPoll) || ((पत्तनम् == 1) && disable_पृष्ठभागः_Poll)) {
            अनुवर्त;
        }
        sceTouchPeek(पत्तनम्, &touch[पत्तनम्], 1);

        touch_id = (SDL_TouchID)(पत्तनम् + 1);

        यदि (touch[पत्तनम्].report_अङ्कः > 0) {
            प्रति (पूर्णाङ्क i = 0; i < touch[पत्तनम्].report_अङ्कः; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                भिन्न x = 0;
                भिन्न y = 0;
                भिन्न force = (touch[पत्तनम्].report[i].force - force_info[पत्तनम्].min) / force_info[पत्तनम्].range;
                पूर्णाङ्क finger_अधस्तात् = 0;

                यदि (touch_old[पत्तनम्].report_अङ्कः > 0) {
                    प्रति (पूर्णाङ्क j = 0; j < touch_old[पत्तनम्].report_अङ्कः; j++) {
                        यदि (touch[पत्तनम्].report[i].id == touch_old[पत्तनम्].report[j].id) {
                            finger_अधस्तात् = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[पत्तनम्].report[i].x, touch[पत्तनम्].report[i].y, पत्तनम्);
                finger_id = (SDL_FingerID)(touch[पत्तनम्].report[i].id + 1);

                // Skip if finger was already previously down
                यदि (!finger_अधस्तात्) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_गवाक्षः, SDL_EVENT_FINGER_अधस्तात्, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_गवाक्षः, x, y, force);
            }
        }

        // some fingers might have been let go
        यदि (touch_old[पत्तनम्].report_अङ्कः > 0) {
            प्रति (पूर्णाङ्क i = 0; i < touch_old[पत्तनम्].report_अङ्कः; i++) {
                पूर्णाङ्क finger_ऊर्ध्वम् = 1;
                यदि (touch[पत्तनम्].report_अङ्कः > 0) {
                    प्रति (पूर्णाङ्क j = 0; j < touch[पत्तनम्].report_अङ्कः; j++) {
                        यदि (touch[पत्तनम्].report[j].id == touch_old[पत्तनम्].report[i].id) {
                            finger_ऊर्ध्वम् = 0;
                        }
                    }
                }
                यदि (finger_ऊर्ध्वम् == 1) {
                    भिन्न x = 0;
                    भिन्न y = 0;
                    भिन्न force = (touch_old[पत्तनम्].report[i].force - force_info[पत्तनम्].min) / force_info[पत्तनम्].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[पत्तनम्].report[i].x, touch_old[पत्तनम्].report[i].y, पत्तनम्);
                    finger_id = (SDL_FingerID)(touch_old[पत्तनम्].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_गवाक्षः, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, force);
                }
            }
        }
    }
}

शून्य VITA_ConvertTouchXYToSDLXY(भिन्न *sdl_x, भिन्न *sdl_y, पूर्णाङ्क vita_x, पूर्णाङ्क vita_y, पूर्णाङ्क पत्तनम्)
{
    भिन्न x, y;

    यदि (area_info[पत्तनम्].w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = (vita_x - area_info[पत्तनम्].x) / (area_info[पत्तनम्].w - 1);
    }
    यदि (area_info[पत्तनम्].h <= 1) {
        y = 0.5f;
    } अन्यथा {
        y = (vita_y - area_info[पत्तनम्].y) / (area_info[पत्तनम्].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA
