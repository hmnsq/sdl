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

#ಆದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    ಆದರೆ (!ಆಂತರಿಕ->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        SDL_IME_Init();
    }
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಗಣ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    ಆದರೆ (!ಆಂತರಿಕ->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        SDL_IME_Quit();
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ Wayland_Seat_Update_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus = seat->keyboard.focus;

        ಆದರೆ (focus && focus->ಪಠ್ಯ_ಒಳಹರಿವು_props.ಸಕ್ರಿಯ) {
            SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            ಆದರೆ (!seat->ಪಠ್ಯ_ಒಳಹರಿವು.enabled) {
                seat->ಪಠ್ಯ_ಒಳಹರಿವು.enabled = true;
                zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_enable(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);

                // Now that it's enabled, set the input properties
                zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_ಗಣ_content_type(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು, focus->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint, focus->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose);
                ಆದರೆ (!SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect)) {
                    ಸ್ಥಿರಾಂಕ SDL_Rect scaled_rect = {
                        (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.x / focus->ಸೂಚಕ_scale.x),
                        (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.y / focus->ಸೂಚಕ_scale.y),
                        (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.w / focus->ಸೂಚಕ_scale.x),
                        (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.h / focus->ಸೂಚಕ_scale.y)
                    };
                    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ scaled_cursor = (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor / focus->ಸೂಚಕ_scale.x);

                    SDL_copyp(&seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_rect, &scaled_rect);
                    seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_ಗಣ_cursor_rectangle(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_commit(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);

                ಆದರೆ (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (seat->ಪಠ್ಯ_ಒಳಹರಿವು.enabled) {
                seat->ಪಠ್ಯ_ಒಳಹರಿವು.enabled = false;
                SDL_zero(seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_rect);
                seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_cursor = 0;
                zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_disable(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);
                zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_commit(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);
            }

            ಆದರೆ (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    SDL_Video_ದತ್ತಾಂಶ *display = _this->ಆಂತರಿಕ;

    ಆದರೆ (display->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
        wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_NONE;

        ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
        ಪೂರ್ವನಿಯೋಜಿತ:
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_ಸಾಮಾನ್ಯ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_NAME:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_NAME;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_EMAIL:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_EMAIL;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_USERNAME:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_ಸಾಮಾನ್ಯ;
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_ದತ್ತಾಂಶ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_HIDDEN:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PASSWORD;
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= (ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_HIDDEN_ಪಠ್ಯ | ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_ದತ್ತಾಂಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_VISIBLE:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PASSWORD;
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_ದತ್ತಾಂಶ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_ಸಂಖ್ಯೆ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PIN;
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= (ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_HIDDEN_ಪಠ್ಯ | ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_ದತ್ತಾಂಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.purpose = ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PIN;
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_ದತ್ತಾಂಶ;
            ನಿಲ್ಲಿಸು;
        }

        ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Capitalization(props)) {
        ಪೂರ್ವನಿಯೋಜಿತ:
        ಸ್ಥಿತಿ SDL_CAPITALIZE_NONE:
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_CAPITALIZE_LETTERS:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_UPPERCASE;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_CAPITALIZE_ಪದಗಳು:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_TITLECASE;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_CAPITALIZE_SENTENCES:
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Autocorrect(props)) {
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= (ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_COMPLETION | ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_SPELLCHECK);
        }
        ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(props)) {
            wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.hint |= ZWP_ಪಠ್ಯ_ಒಳಹರಿವು_V3_CONTENT_HINT_MULTILINE;
        }

        wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.ಸಕ್ರಿಯ = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            ಆದರೆ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_ಪಠ್ಯ_ಒಳಹರಿವು(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *display = _this->ಆಂತರಿಕ;

    ಆದರೆ (display->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        SDL_WaylandSeat *seat;
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
        wind->ಪಠ್ಯ_ಒಳಹರಿವು_props.ಸಕ್ರಿಯ = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            ಆದರೆ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_ಪಠ್ಯ_ಒಳಹರಿವು(seat);
            }
        }
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    ಇಲ್ಲದಿದ್ದರೆ {
        SDL_IME_Reset();
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    ಆದರೆ (ಆಂತರಿಕ->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        SDL_WaylandSeat *seat;
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

        wl_list_for_each (seat, &ಆಂತರಿಕ->seat_list, link) {
            ಆದರೆ (seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು && seat->keyboard.focus == wind) {
                ಸ್ಥಿರಾಂಕ SDL_Rect scaled_rect = {
                    (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.x / wind->ಸೂಚಕ_scale.x),
                    (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.y / wind->ಸೂಚಕ_scale.y),
                    (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.w / wind->ಸೂಚಕ_scale.x),
                    (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.h / wind->ಸೂಚಕ_scale.y)
                };
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ scaled_cursor = (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor / wind->ಸೂಚಕ_scale.x);

                ಆದರೆ (!SDL_RectsEqual(&scaled_rect, &seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_rect) || scaled_cursor != seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_cursor) {
                    SDL_copyp(&seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_rect, &scaled_rect);
                    seat->ಪಠ್ಯ_ಒಳಹರಿವು.ಪಠ್ಯ_ಒಳಹರಿವು_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_ಗಣ_cursor_rectangle(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_commit(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);
                }
            }
        }
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    ಇಲ್ಲದಿದ್ದರೆ {
        SDL_IME_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (ಆಂತರಿಕ->ಪಠ್ಯ_ಒಳಹರಿವು_manager != ಖಾಲಿ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &ಆಂತರಿಕ->seat_list, link) {
        ಆದರೆ (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಹಿಂತಿರುಗಿ !haskeyboard && hastextmanager;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
