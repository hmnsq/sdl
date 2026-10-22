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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ <psp2/touch.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitatouch.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

Sce_Touch_ದತ್ತಾಂಶ touch_old[SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ];
Sce_Touch_ದತ್ತಾಂಶ touch[SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ];

SDL_FRect area_info[SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ];

ರಚನೆ
{
    ದಶಮಾಂಶ min;
    ದಶಮಾಂಶ range;
} force_info[SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ];

ಸ್ಥಿರ bool disableFrontPoll;
ಸ್ಥಿರ bool disable_ಹಿಂಭಾಗ_Poll;

ಶೂನ್ಯ VITA_InitTouch(ಶೂನ್ಯ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_ಹಿಂಭಾಗ_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_ಹಿಂಭಾಗ_TOUCH, true);

    sce_Touch_ಗಣ_Sampling_State(SCE_TOUCH_ಪೋರ್ಟ್_FRONT, SCE_TOUCH_SAMPLING_STATE_ಆರಂಭ);
    sce_Touch_ಗಣ_Sampling_State(SCE_TOUCH_ಪೋರ್ಟ್_ಹಿಂಭಾಗ, SCE_TOUCH_SAMPLING_STATE_ಆರಂಭ);
    sceTouchEnableTouchForce(SCE_TOUCH_ಪೋರ್ಟ್_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_ಪೋರ್ಟ್_ಹಿಂಭಾಗ);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಪೋರ್ಟ್ = 0; ಪೋರ್ಟ್ < SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ; ಪೋರ್ಟ್++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(ಪೋರ್ಟ್, &panelinfo);

        area_info[ಪೋರ್ಟ್].x = (ದಶಮಾಂಶ)panelinfo.minAaX;
        area_info[ಪೋರ್ಟ್].y = (ದಶಮಾಂಶ)panelinfo.minAaY;
        area_info[ಪೋರ್ಟ್].w = (ದಶಮಾಂಶ)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[ಪೋರ್ಟ್].h = (ದಶಮಾಂಶ)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[ಪೋರ್ಟ್].min = (ದಶಮಾಂಶ)panelinfo.minForce;
        force_info[ಪೋರ್ಟ್].range = (ದಶಮಾಂಶ)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_ಕೂಡಿಸು_Touch(1, SDL_TOUCH_DEVICE_ನೇರ, "Front");
    SDL_ಕೂಡಿಸು_Touch(2, SDL_TOUCH_DEVICE_ಪರೋಕ್ಷ_ABSOLUTE, "Back");
}

ಶೂನ್ಯ VITA_QuitTouch(ಶೂನ್ಯ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_ಪೋರ್ಟ್_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_ಪೋರ್ಟ್_ಹಿಂಭಾಗ);
}

ಶೂನ್ಯ VITA_PollTouch(ಶೂನ್ಯ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    ಪೂರ್ಣಾಂಕ ಪೋರ್ಟ್;

    // We skip polling touch if no window is created
    ಆದರೆ (!Vita_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_memcpy(touch_old, touch, ಗಾತ್ರ(touch_old));

    ಗಾಗಿ (ಪೋರ್ಟ್ = 0; ಪೋರ್ಟ್ < SCE_TOUCH_ಪೋರ್ಟ್_MAX_ಅಂಕೆ; ಪೋರ್ಟ್++) {
        /** Skip polling of Touch Device if hint is set **/
        ಆದರೆ (((ಪೋರ್ಟ್ == 0) && disableFrontPoll) || ((ಪೋರ್ಟ್ == 1) && disable_ಹಿಂಭಾಗ_Poll)) {
            ಮುಂದುವರಿ;
        }
        sceTouchPeek(ಪೋರ್ಟ್, &touch[ಪೋರ್ಟ್], 1);

        touch_id = (SDL_TouchID)(ಪೋರ್ಟ್ + 1);

        ಆದರೆ (touch[ಪೋರ್ಟ್].report_ಅಂಕೆ > 0) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < touch[ಪೋರ್ಟ್].report_ಅಂಕೆ; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                ದಶಮಾಂಶ x = 0;
                ದಶಮಾಂಶ y = 0;
                ದಶಮಾಂಶ force = (touch[ಪೋರ್ಟ್].report[i].force - force_info[ಪೋರ್ಟ್].min) / force_info[ಪೋರ್ಟ್].range;
                ಪೂರ್ಣಾಂಕ finger_ಕೆಳಕ್ಕೆ = 0;

                ಆದರೆ (touch_old[ಪೋರ್ಟ್].report_ಅಂಕೆ > 0) {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < touch_old[ಪೋರ್ಟ್].report_ಅಂಕೆ; j++) {
                        ಆದರೆ (touch[ಪೋರ್ಟ್].report[i].id == touch_old[ಪೋರ್ಟ್].report[j].id) {
                            finger_ಕೆಳಕ್ಕೆ = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[ಪೋರ್ಟ್].report[i].x, touch[ಪೋರ್ಟ್].report[i].y, ಪೋರ್ಟ್);
                finger_id = (SDL_FingerID)(touch[ಪೋರ್ಟ್].report[i].id + 1);

                // Skip if finger was already previously down
                ಆದರೆ (!finger_ಕೆಳಕ್ಕೆ) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_ಕಿಟಕಿ, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_ಕಿಟಕಿ, x, y, force);
            }
        }

        // some fingers might have been let go
        ಆದರೆ (touch_old[ಪೋರ್ಟ್].report_ಅಂಕೆ > 0) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < touch_old[ಪೋರ್ಟ್].report_ಅಂಕೆ; i++) {
                ಪೂರ್ಣಾಂಕ finger_ಮೇಲೆ = 1;
                ಆದರೆ (touch[ಪೋರ್ಟ್].report_ಅಂಕೆ > 0) {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < touch[ಪೋರ್ಟ್].report_ಅಂಕೆ; j++) {
                        ಆದರೆ (touch[ಪೋರ್ಟ್].report[j].id == touch_old[ಪೋರ್ಟ್].report[i].id) {
                            finger_ಮೇಲೆ = 0;
                        }
                    }
                }
                ಆದರೆ (finger_ಮೇಲೆ == 1) {
                    ದಶಮಾಂಶ x = 0;
                    ದಶಮಾಂಶ y = 0;
                    ದಶಮಾಂಶ force = (touch_old[ಪೋರ್ಟ್].report[i].force - force_info[ಪೋರ್ಟ್].min) / force_info[ಪೋರ್ಟ್].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[ಪೋರ್ಟ್].report[i].x, touch_old[ಪೋರ್ಟ್].report[i].y, ಪೋರ್ಟ್);
                    finger_id = (SDL_FingerID)(touch_old[ಪೋರ್ಟ್].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_ಕಿಟಕಿ, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, force);
                }
            }
        }
    }
}

ಶೂನ್ಯ VITA_ConvertTouchXYToSDLXY(ದಶಮಾಂಶ *sdl_x, ದಶಮಾಂಶ *sdl_y, ಪೂರ್ಣಾಂಕ vita_x, ಪೂರ್ಣಾಂಕ vita_y, ಪೂರ್ಣಾಂಕ ಪೋರ್ಟ್)
{
    ದಶಮಾಂಶ x, y;

    ಆದರೆ (area_info[ಪೋರ್ಟ್].w <= 1) {
        x = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        x = (vita_x - area_info[ಪೋರ್ಟ್].x) / (area_info[ಪೋರ್ಟ್].w - 1);
    }
    ಆದರೆ (area_info[ಪೋರ್ಟ್].h <= 1) {
        y = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        y = (vita_y - area_info[ಪೋರ್ಟ್].y) / (area_info[ಪೋರ್ಟ್].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA
