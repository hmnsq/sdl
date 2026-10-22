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

#ਜੇ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!ਅੰਦਰੂਨੀ->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        SDL_IME_Init();
    }
#ਜੇ_ਅੰਤ
    SDL_ਸੈੱਟ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!ਅੰਦਰੂਨੀ->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        SDL_IME_Quit();
    }
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ Wayland_Seat_Update_ਪਾਠ_ਨਿਵੇਸ਼(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus = seat->keyboard.focus;

        ਜੇ (focus && focus->ਪਾਠ_ਨਿਵੇਸ਼_props.ਸਰਗਰਮ) {
            SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            ਜੇ (!seat->ਪਾਠ_ਨਿਵੇਸ਼.enabled) {
                seat->ਪਾਠ_ਨਿਵੇਸ਼.enabled = true;
                zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_enable(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);

                // Now that it's enabled, set the input properties
                zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_ਸੈੱਟ_content_type(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼, focus->ਪਾਠ_ਨਿਵੇਸ਼_props.hint, focus->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose);
                ਜੇ (!SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect)) {
                    ਅਚਲ SDL_Rect scaled_rect = {
                        (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.x / focus->ਸੂਚਕ_scale.x),
                        (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.y / focus->ਸੂਚਕ_scale.y),
                        (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.w / focus->ਸੂਚਕ_scale.x),
                        (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.h / focus->ਸੂਚਕ_scale.y)
                    };
                    ਅਚਲ ਪੂਰਨ scaled_cursor = (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor / focus->ਸੂਚਕ_scale.x);

                    SDL_copyp(&seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_rect, &scaled_rect);
                    seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_ਸੈੱਟ_cursor_rectangle(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_commit(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);

                ਜੇ (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (seat->ਪਾਠ_ਨਿਵੇਸ਼.enabled) {
                seat->ਪਾਠ_ਨਿਵੇਸ਼.enabled = false;
                SDL_zero(seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_rect);
                seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_cursor = 0;
                zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_disable(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);
                zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_commit(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);
            }

            ਜੇ (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    SDL_Video_ਅੰਕੜੇ *display = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (display->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_NONE;

        ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
        ਮੂਲ:
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_ਸਾਧਾਰਨ;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_NAME:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_NAME;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_EMAIL:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_EMAIL;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_USERNAME:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_ਸਾਧਾਰਨ;
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SENSITIVE_ਅੰਕੜੇ;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_HIDDEN:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_PASSWORD;
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= (ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_HIDDEN_ਪਾਠ | ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SENSITIVE_ਅੰਕੜੇ);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_VISIBLE:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_PASSWORD;
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SENSITIVE_ਅੰਕੜੇ;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_ਸੰਖਿਆ;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_PIN;
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= (ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_HIDDEN_ਪਾਠ | ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SENSITIVE_ਅੰਕੜੇ);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_VISIBLE:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.purpose = ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_PURPOSE_PIN;
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SENSITIVE_ਅੰਕੜੇ;
            ਰੋਕੋ;
        }

        ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Capitalization(props)) {
        ਮੂਲ:
        ਹਾਲਤ SDL_CAPITALIZE_NONE:
            ਰੋਕੋ;
        ਹਾਲਤ SDL_CAPITALIZE_LETTERS:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_UPPERCASE;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_CAPITALIZE_ਸ਼ਬਦ:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_TITLECASE;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_CAPITALIZE_SENTENCES:
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            ਰੋਕੋ;
        }

        ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Autocorrect(props)) {
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= (ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_COMPLETION | ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_SPELLCHECK);
        }
        ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(props)) {
            wind->ਪਾਠ_ਨਿਵੇਸ਼_props.hint |= ZWP_ਪਾਠ_ਨਿਵੇਸ਼_V3_CONTENT_HINT_MULTILINE;
        }

        wind->ਪਾਠ_ਨਿਵੇਸ਼_props.ਸਰਗਰਮ = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            ਜੇ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_ਪਾਠ_ਨਿਵੇਸ਼(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    ਵਾਪਸ true;
}

bool Wayland_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *display = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (display->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        SDL_WaylandSeat *seat;
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        wind->ਪਾਠ_ਨਿਵੇਸ਼_props.ਸਰਗਰਮ = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            ਜੇ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_ਪਾਠ_ਨਿਵੇਸ਼(seat);
            }
        }
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    ਨਹੀਂਤਾਂ {
        SDL_IME_Reset();
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

bool Wayland_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਦਰੂਨੀ->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        SDL_WaylandSeat *seat;
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        wl_list_for_each (seat, &ਅੰਦਰੂਨੀ->seat_list, link) {
            ਜੇ (seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼ && seat->keyboard.focus == wind) {
                ਅਚਲ SDL_Rect scaled_rect = {
                    (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.x / wind->ਸੂਚਕ_scale.x),
                    (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.y / wind->ਸੂਚਕ_scale.y),
                    (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.w / wind->ਸੂਚਕ_scale.x),
                    (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.h / wind->ਸੂਚਕ_scale.y)
                };
                ਅਚਲ ਪੂਰਨ scaled_cursor = (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor / wind->ਸੂਚਕ_scale.x);

                ਜੇ (!SDL_RectsEqual(&scaled_rect, &seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_rect) || scaled_cursor != seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_cursor) {
                    SDL_copyp(&seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_rect, &scaled_rect);
                    seat->ਪਾਠ_ਨਿਵੇਸ਼.ਪਾਠ_ਨਿਵੇਸ਼_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_ਸੈੱਟ_cursor_rectangle(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_commit(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);
                }
            }
        }
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    ਨਹੀਂਤਾਂ {
        SDL_IME_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (ਅੰਦਰੂਨੀ->ਪਾਠ_ਨਿਵੇਸ਼_manager != ਨਿਰਾ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &ਅੰਦਰੂਨੀ->seat_list, link) {
        ਜੇ (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            ਰੋਕੋ;
        }
    }

    ਵਾਪਸ !haskeyboard && hastextmanager;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
