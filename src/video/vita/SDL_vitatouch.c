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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/processmgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/touch.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitatouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"

Sce_Touch_ਅੰਕੜੇ touch_old[SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ];
Sce_Touch_ਅੰਕੜੇ touch[SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ];

SDL_FRect area_info[SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ];

ਬਣਤਰ
{
    ਦਸ਼ਮਲਵ min;
    ਦਸ਼ਮਲਵ range;
} force_info[SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ];

ਸਥਿਰ bool disableFrontPoll;
ਸਥਿਰ bool disable_ਪਿੱਠ_Poll;

ਖਾਲੀ VITA_InitTouch(ਖਾਲੀ)
{
    disableFrontPoll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_FRONT_TOUCH, true);
    disable_ਪਿੱਠ_Poll = !SDL_GetHintBoolean(SDL_HINT_VITA_ENABLE_ਪਿੱਠ_TOUCH, true);

    sce_Touch_ਸੈੱਟ_Sampling_State(SCE_TOUCH_ਪੋਰਟ_FRONT, SCE_TOUCH_SAMPLING_STATE_ਸ਼ੁਰੂ);
    sce_Touch_ਸੈੱਟ_Sampling_State(SCE_TOUCH_ਪੋਰਟ_ਪਿੱਠ, SCE_TOUCH_SAMPLING_STATE_ਸ਼ੁਰੂ);
    sceTouchEnableTouchForce(SCE_TOUCH_ਪੋਰਟ_FRONT);
    sceTouchEnableTouchForce(SCE_TOUCH_ਪੋਰਟ_ਪਿੱਠ);

    ਲਈ (ਪੂਰਨ ਪੋਰਟ = 0; ਪੋਰਟ < SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ; ਪੋਰਟ++) {
        SceTouchPanelInfo panelinfo;
        sceTouchGetPanelInfo(ਪੋਰਟ, &panelinfo);

        area_info[ਪੋਰਟ].x = (ਦਸ਼ਮਲਵ)panelinfo.minAaX;
        area_info[ਪੋਰਟ].y = (ਦਸ਼ਮਲਵ)panelinfo.minAaY;
        area_info[ਪੋਰਟ].w = (ਦਸ਼ਮਲਵ)(panelinfo.maxAaX - panelinfo.minAaX);
        area_info[ਪੋਰਟ].h = (ਦਸ਼ਮਲਵ)(panelinfo.maxAaY - panelinfo.minAaY);

        force_info[ਪੋਰਟ].min = (ਦਸ਼ਮਲਵ)panelinfo.minForce;
        force_info[ਪੋਰਟ].range = (ਦਸ਼ਮਲਵ)(panelinfo.maxForce - panelinfo.minForce);
    }

    // Support passing both front and back touch devices in events
    SDL_ਜੋੜੋ_Touch(1, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, "Front");
    SDL_ਜੋੜੋ_Touch(2, SDL_TOUCH_DEVICE_ਅਸਿੱਧਾ_ABSOLUTE, "Back");
}

ਖਾਲੀ VITA_QuitTouch(ਖਾਲੀ)
{
    sceTouchDisableTouchForce(SCE_TOUCH_ਪੋਰਟ_FRONT);
    sceTouchDisableTouchForce(SCE_TOUCH_ਪੋਰਟ_ਪਿੱਠ);
}

ਖਾਲੀ VITA_PollTouch(ਖਾਲੀ)
{
    SDL_TouchID touch_id;
    SDL_FingerID finger_id;
    ਪੂਰਨ ਪੋਰਟ;

    // We skip polling touch if no window is created
    ਜੇ (!Vita_ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    SDL_memcpy(touch_old, touch, ਆਕਾਰ(touch_old));

    ਲਈ (ਪੋਰਟ = 0; ਪੋਰਟ < SCE_TOUCH_ਪੋਰਟ_MAX_ਅੰਕ; ਪੋਰਟ++) {
        /** Skip polling of Touch Device if hint is set **/
        ਜੇ (((ਪੋਰਟ == 0) && disableFrontPoll) || ((ਪੋਰਟ == 1) && disable_ਪਿੱਠ_Poll)) {
            ਜਾਰੀ;
        }
        sceTouchPeek(ਪੋਰਟ, &touch[ਪੋਰਟ], 1);

        touch_id = (SDL_TouchID)(ਪੋਰਟ + 1);

        ਜੇ (touch[ਪੋਰਟ].report_ਅੰਕ > 0) {
            ਲਈ (ਪੂਰਨ i = 0; i < touch[ਪੋਰਟ].report_ਅੰਕ; i++) {
                // adjust coordinates and forces to return normalized values
                // for the front, screen area is used as a reference (for direct touch)
                // e.g. touch_x = 1.0 corresponds to screen_x = 960
                // for the back panel, the active touch area is used as reference
                ਦਸ਼ਮਲਵ x = 0;
                ਦਸ਼ਮਲਵ y = 0;
                ਦਸ਼ਮਲਵ force = (touch[ਪੋਰਟ].report[i].force - force_info[ਪੋਰਟ].min) / force_info[ਪੋਰਟ].range;
                ਪੂਰਨ finger_ਥੱਲੇ = 0;

                ਜੇ (touch_old[ਪੋਰਟ].report_ਅੰਕ > 0) {
                    ਲਈ (ਪੂਰਨ j = 0; j < touch_old[ਪੋਰਟ].report_ਅੰਕ; j++) {
                        ਜੇ (touch[ਪੋਰਟ].report[i].id == touch_old[ਪੋਰਟ].report[j].id) {
                            finger_ਥੱਲੇ = 1;
                        }
                    }
                }

                VITA_ConvertTouchXYToSDLXY(&x, &y, touch[ਪੋਰਟ].report[i].x, touch[ਪੋਰਟ].report[i].y, ਪੋਰਟ);
                finger_id = (SDL_FingerID)(touch[ਪੋਰਟ].report[i].id + 1);

                // Skip if finger was already previously down
                ਜੇ (!finger_ਥੱਲੇ) {
                    // Send an initial touch
                    SDL_SendTouch(0, touch_id, finger_id, Vita_ਖਿੜਕੀ, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, force);
                }

                // Always send the motion
                SDL_SendTouchMotion(0, touch_id, finger_id, Vita_ਖਿੜਕੀ, x, y, force);
            }
        }

        // some fingers might have been let go
        ਜੇ (touch_old[ਪੋਰਟ].report_ਅੰਕ > 0) {
            ਲਈ (ਪੂਰਨ i = 0; i < touch_old[ਪੋਰਟ].report_ਅੰਕ; i++) {
                ਪੂਰਨ finger_ਉੱਪਰ = 1;
                ਜੇ (touch[ਪੋਰਟ].report_ਅੰਕ > 0) {
                    ਲਈ (ਪੂਰਨ j = 0; j < touch[ਪੋਰਟ].report_ਅੰਕ; j++) {
                        ਜੇ (touch[ਪੋਰਟ].report[j].id == touch_old[ਪੋਰਟ].report[i].id) {
                            finger_ਉੱਪਰ = 0;
                        }
                    }
                }
                ਜੇ (finger_ਉੱਪਰ == 1) {
                    ਦਸ਼ਮਲਵ x = 0;
                    ਦਸ਼ਮਲਵ y = 0;
                    ਦਸ਼ਮਲਵ force = (touch_old[ਪੋਰਟ].report[i].force - force_info[ਪੋਰਟ].min) / force_info[ਪੋਰਟ].range;
                    VITA_ConvertTouchXYToSDLXY(&x, &y, touch_old[ਪੋਰਟ].report[i].x, touch_old[ਪੋਰਟ].report[i].y, ਪੋਰਟ);
                    finger_id = (SDL_FingerID)(touch_old[ਪੋਰਟ].report[i].id + 1);
                    // Finger released from screen
                    SDL_SendTouch(0, touch_id, finger_id, Vita_ਖਿੜਕੀ, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, force);
                }
            }
        }
    }
}

ਖਾਲੀ VITA_ConvertTouchXYToSDLXY(ਦਸ਼ਮਲਵ *sdl_x, ਦਸ਼ਮਲਵ *sdl_y, ਪੂਰਨ vita_x, ਪੂਰਨ vita_y, ਪੂਰਨ ਪੋਰਟ)
{
    ਦਸ਼ਮਲਵ x, y;

    ਜੇ (area_info[ਪੋਰਟ].w <= 1) {
        x = 0.5f;
    } ਨਹੀਂਤਾਂ {
        x = (vita_x - area_info[ਪੋਰਟ].x) / (area_info[ਪੋਰਟ].w - 1);
    }
    ਜੇ (area_info[ਪੋਰਟ].h <= 1) {
        y = 0.5f;
    } ਨਹੀਂਤਾਂ {
        y = (vita_y - area_info[ਪੋਰਟ].y) / (area_info[ਪੋਰਟ].h - 1);
    }

    x = SDL_max(x, 0.0f);
    x = SDL_min(x, 1.0f);

    y = SDL_max(y, 0.0f);
    y = SDL_min(y, 1.0f);

    *sdl_x = x;
    *sdl_y = y;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA
