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

#ಯದಿ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    ಯದಿ (!internal->text_ಒಳಹರಿವು_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    ಯದಿ (!internal->text_ಒಳಹರಿವು_manager) {
        SDL_IME_Quit();
    }
#endif
}

ಶೂನ್ಯ Wayland_Seat_Update_Text_ಒಳಹರಿವು(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು) {
        SDL_WindowData *focus = seat->keyboard.focus;

        ಯದಿ (focus && focus->text_ಒಳಹರಿವು_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            ಯದಿ (!seat->text_ಒಳಹರಿವು.enabled) {
                seat->text_ಒಳಹರಿವು.enabled = true;
                zwp_text_ಒಳಹರಿವು_v3_enable(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);

                // Now that it's enabled, set the input properties
                zwp_text_ಒಳಹರಿವು_v3_set_content_type(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು, focus->text_ಒಳಹರಿವು_props.hint, focus->text_ಒಳಹರಿವು_props.purpose);
                ಯದಿ (!SDL_RectEmpty(&window->text_ಒಳಹರಿವು_rect)) {
                    ಧ್ರುವ SDL_Rect scaled_rect = {
                        (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_rect.x / focus->pointer_scale.x),
                        (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_rect.y / focus->pointer_scale.y),
                        (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->text_ಒಳಹರಿವು_rect.w / focus->pointer_scale.x),
                        (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->text_ಒಳಹರಿವು_rect.h / focus->pointer_scale.y)
                    };
                    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ scaled_cursor = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_rect, &scaled_rect);
                    seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_ಒಳಹರಿವು_v3_set_cursor_rectangle(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_ಒಳಹರಿವು_v3_commit(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);

                ಯದಿ (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (seat->text_ಒಳಹರಿವು.enabled) {
                seat->text_ಒಳಹರಿವು.enabled = false;
                SDL_zero(seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_rect);
                seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_cursor = 0;
                zwp_text_ಒಳಹರಿವು_v3_disable(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);
                zwp_text_ಒಳಹರಿವು_v3_commit(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);
            }

            ಯದಿ (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    ಯದಿ (display->text_ಒಳಹರಿವು_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_ಒಳಹರಿವು_props.hint = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_NONE;

        ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
        ಸ್ವಭಾವ:
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_NORMAL;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_NAME;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_EMAIL;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_DATA;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_ಒಳಹರಿವು_props.hint |= (ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_DATA);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_DATA;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_ಸಂಖ್ಯೆ;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PIN;
            wind->text_ಒಳಹರಿವು_props.hint |= (ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_DATA);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
            wind->text_ಒಳಹರಿವು_props.purpose = ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_PURPOSE_PIN;
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SENSITIVE_DATA;
            ಭಙ್ಗ;
        }

        ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Capitalization(props)) {
        ಸ್ವಭಾವ:
        ಪಕ್ಷ SDL_CAPITALIZE_NONE:
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_CAPITALIZE_LETTERS:
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_UPPERCASE;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_CAPITALIZE_ಪದಗಳು:
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_TITLECASE;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_CAPITALIZE_SENTENCES:
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            ಭಙ್ಗ;
        }

        ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Autocorrect(props)) {
            wind->text_ಒಳಹರಿವು_props.hint |= (ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_SPELLCHECK);
        }
        ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Multiline(props)) {
            wind->text_ಒಳಹರಿವು_props.hint |= ZWP_TEXT_ಒಳಹರಿವು_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_ಒಳಹರಿವು_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            ಯದಿ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_ಒಳಹರಿವು(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    ಪ್ರತ್ಯಾಗಮ true;
}

bool Wayland_Stop_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    ಯದಿ (display->text_ಒಳಹರಿವು_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_ಒಳಹರಿವು_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            ಯದಿ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_ಒಳಹರಿವು(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    ಅನ್ಯಥಾ {
        SDL_IME_Reset();
    }
#endif

    ಪ್ರತ್ಯಾಗಮ true;
}

bool Wayland_Update_Text_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    ಯದಿ (internal->text_ಒಳಹರಿವು_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            ಯದಿ (seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು && seat->keyboard.focus == wind) {
                ಧ್ರುವ SDL_Rect scaled_rect = {
                    (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_rect.x / wind->pointer_scale.x),
                    (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_rect.y / wind->pointer_scale.y),
                    (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->text_ಒಳಹರಿವು_rect.w / wind->pointer_scale.x),
                    (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->text_ಒಳಹರಿವು_rect.h / wind->pointer_scale.y)
                };
                ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ scaled_cursor = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->text_ಒಳಹರಿವು_cursor / wind->pointer_scale.x);

                ಯದಿ (!SDL_RectsEqual(&scaled_rect, &seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_rect) || scaled_cursor != seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_cursor) {
                    SDL_copyp(&seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_rect, &scaled_rect);
                    seat->text_ಒಳಹರಿವು.text_ಒಳಹರಿವು_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_ಒಳಹರಿವು_v3_set_cursor_rectangle(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_ಒಳಹರಿವು_v3_commit(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    ಅನ್ಯಥಾ {
        SDL_IME_Update_Text_ಒಳಹರಿವು_Area(window);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_ಒಳಹರಿವು_manager != ರಿಕ್ತ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        ಯದಿ (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            ಭಙ್ಗ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
