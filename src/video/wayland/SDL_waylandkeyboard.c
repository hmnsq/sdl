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
#شامل "SDL_internal.h"

#اگر SDL_VIDEO_DRIVER_WAYLAND

#شامل "../SDL_sysvideo.h"
#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandevents_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_USE_IME
    SDL_Video_ڈیٹا *اندرونی_2 = _this->اندرونی_2;
    اگر (!اندرونی_2->متن_داخلہ_manager) {
        SDL_IME_Init();
    }
#اگر_ختم
    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    واپس true;
}

خالی Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_USE_IME
    SDL_Video_ڈیٹا *اندرونی_2 = _this->اندرونی_2;
    اگر (!اندرونی_2->متن_داخلہ_manager) {
        SDL_IME_Quit();
    }
#اگر_ختم
}

خالی Wayland_Seat_Update_متن_داخلہ(SDL_WaylandSeat *seat)
{
    اگر (seat->متن_داخلہ.zwp_متن_داخلہ) {
        SDL_کھڑکی_ڈیٹا *focus = seat->keyboard.focus;

        اگر (focus && focus->متن_داخلہ_props.فعال) {
            SDL_کھڑکی *کھڑکی = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            اگر (!seat->متن_داخلہ.enabled) {
                seat->متن_داخلہ.enabled = true;
                zwp_متن_داخلہ_v3_enable(seat->متن_داخلہ.zwp_متن_داخلہ);

                // Now that it's enabled, set the input properties
                zwp_متن_داخلہ_v3_سیٹ_content_type(seat->متن_داخلہ.zwp_متن_داخلہ, focus->متن_داخلہ_props.hint, focus->متن_داخلہ_props.purpose);
                اگر (!SDL_Rect_خالی_خانے(&کھڑکی->متن_داخلہ_rect)) {
                    ثابت SDL_Rect scaled_rect = {
                        (صحیح)SDL_floor(کھڑکی->متن_داخلہ_rect.x / focus->اشارہ_گر_scale.x),
                        (صحیح)SDL_floor(کھڑکی->متن_داخلہ_rect.y / focus->اشارہ_گر_scale.y),
                        (صحیح)SDL_ceil(کھڑکی->متن_داخلہ_rect.w / focus->اشارہ_گر_scale.x),
                        (صحیح)SDL_ceil(کھڑکی->متن_داخلہ_rect.h / focus->اشارہ_گر_scale.y)
                    };
                    ثابت صحیح scaled_cursor = (صحیح)SDL_floor(کھڑکی->متن_داخلہ_cursor / focus->اشارہ_گر_scale.x);

                    SDL_copyp(&seat->متن_داخلہ.متن_داخلہ_rect, &scaled_rect);
                    seat->متن_داخلہ.متن_داخلہ_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_متن_داخلہ_v3_سیٹ_cursor_rectangle(seat->متن_داخلہ.zwp_متن_داخلہ,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_متن_داخلہ_v3_commit(seat->متن_داخلہ.zwp_متن_داخلہ);

                اگر (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } ورنہ {
            اگر (seat->متن_داخلہ.enabled) {
                seat->متن_داخلہ.enabled = false;
                SDL_zero(seat->متن_داخلہ.متن_داخلہ_rect);
                seat->متن_داخلہ.متن_داخلہ_cursor = 0;
                zwp_متن_داخلہ_v3_disable(seat->متن_داخلہ.zwp_متن_داخلہ);
                zwp_متن_داخلہ_v3_commit(seat->متن_داخلہ.zwp_متن_داخلہ);
            }

            اگر (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_ڈیٹا *display = _this->اندرونی_2;

    اگر (display->متن_داخلہ_manager) {
        SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
        wind->متن_داخلہ_props.hint = ZWP_متن_داخلہ_V3_CONTENT_HINT_NONE;

        انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
        طےشدہ:
        حالت SDL_TEXTINPUT_TYPE_متن:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_معمول;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_متن_NAME:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_NAME;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_متن_EMAIL:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_EMAIL;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_متن_USERNAME:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_معمول;
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_SENSITIVE_ڈیٹا;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_PASSWORD;
            wind->متن_داخلہ_props.hint |= (ZWP_متن_داخلہ_V3_CONTENT_HINT_HIDDEN_متن | ZWP_متن_داخلہ_V3_CONTENT_HINT_SENSITIVE_ڈیٹا);
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_PASSWORD;
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_SENSITIVE_ڈیٹا;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_نمبر:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_نمبر;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_PIN;
            wind->متن_داخلہ_props.hint |= (ZWP_متن_داخلہ_V3_CONTENT_HINT_HIDDEN_متن | ZWP_متن_داخلہ_V3_CONTENT_HINT_SENSITIVE_ڈیٹا);
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
            wind->متن_داخلہ_props.purpose = ZWP_متن_داخلہ_V3_CONTENT_PURPOSE_PIN;
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_SENSITIVE_ڈیٹا;
            توڑو;
        }

        انتخاب (SDL_Get_متن_داخلہ_Capitalization(props)) {
        طےشدہ:
        حالت SDL_CAPITALIZE_NONE:
            توڑو;
        حالت SDL_CAPITALIZE_LETTERS:
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_UPPERCASE;
            توڑو;
        حالت SDL_CAPITALIZE_الفاظ:
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_TITLECASE;
            توڑو;
        حالت SDL_CAPITALIZE_SENTENCES:
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            توڑو;
        }

        اگر (SDL_Get_متن_داخلہ_Autocorrect(props)) {
            wind->متن_داخلہ_props.hint |= (ZWP_متن_داخلہ_V3_CONTENT_HINT_COMPLETION | ZWP_متن_داخلہ_V3_CONTENT_HINT_SPELLCHECK);
        }
        اگر (SDL_Get_متن_داخلہ_Multiline(props)) {
            wind->متن_داخلہ_props.hint |= ZWP_متن_داخلہ_V3_CONTENT_HINT_MULTILINE;
        }

        wind->متن_داخلہ_props.فعال = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            اگر (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_متن_داخلہ(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    واپس true;
}

bool Wayland_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *display = _this->اندرونی_2;

    اگر (display->متن_داخلہ_manager) {
        SDL_WaylandSeat *seat;
        SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
        wind->متن_داخلہ_props.فعال = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            اگر (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_متن_داخلہ(seat);
            }
        }
    }
#اگر_تعریف_شدہ SDL_USE_IME
    ورنہ {
        SDL_IME_Reset();
    }
#اگر_ختم

    واپس true;
}

bool Wayland_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *اندرونی_2 = _this->اندرونی_2;
    اگر (اندرونی_2->متن_داخلہ_manager) {
        SDL_WaylandSeat *seat;
        SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

        wl_list_for_each (seat, &اندرونی_2->seat_list, link) {
            اگر (seat->متن_داخلہ.zwp_متن_داخلہ && seat->keyboard.focus == wind) {
                ثابت SDL_Rect scaled_rect = {
                    (صحیح)SDL_floor(کھڑکی->متن_داخلہ_rect.x / wind->اشارہ_گر_scale.x),
                    (صحیح)SDL_floor(کھڑکی->متن_داخلہ_rect.y / wind->اشارہ_گر_scale.y),
                    (صحیح)SDL_ceil(کھڑکی->متن_داخلہ_rect.w / wind->اشارہ_گر_scale.x),
                    (صحیح)SDL_ceil(کھڑکی->متن_داخلہ_rect.h / wind->اشارہ_گر_scale.y)
                };
                ثابت صحیح scaled_cursor = (صحیح)SDL_floor(کھڑکی->متن_داخلہ_cursor / wind->اشارہ_گر_scale.x);

                اگر (!SDL_RectsEqual(&scaled_rect, &seat->متن_داخلہ.متن_داخلہ_rect) || scaled_cursor != seat->متن_داخلہ.متن_داخلہ_cursor) {
                    SDL_copyp(&seat->متن_داخلہ.متن_داخلہ_rect, &scaled_rect);
                    seat->متن_داخلہ.متن_داخلہ_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_متن_داخلہ_v3_سیٹ_cursor_rectangle(seat->متن_داخلہ.zwp_متن_داخلہ,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_متن_داخلہ_v3_commit(seat->متن_داخلہ.zwp_متن_داخلہ);
                }
            }
        }
    }
#اگر_تعریف_شدہ SDL_USE_IME
    ورنہ {
        SDL_IME_Update_متن_داخلہ_Area(کھڑکی);
    }
#اگر_ختم
    واپس true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_ڈیٹا *اندرونی_2 = _this->اندرونی_2;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (اندرونی_2->متن_داخلہ_manager != تہی);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &اندرونی_2->seat_list, link) {
        اگر (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            توڑو;
        }
    }

    واپس !haskeyboard && hastextmanager;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
