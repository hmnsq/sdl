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
#ضمن "SDL_internal.h"

#إذا SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    SDL_Video_معلومات *اندروني = _this->اندروني;
    إذا (!اندروني->متن_داخلا_manager) {
        SDL_IME_Init();
    }
#جيڪڏهن_پورو
    SDL_سيٽ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    أرجع true;
}

فراغ Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    SDL_Video_معلومات *اندروني = _this->اندروني;
    إذا (!اندروني->متن_داخلا_manager) {
        SDL_IME_Quit();
    }
#جيڪڏهن_پورو
}

فراغ Wayland_Seat_Update_متن_داخلا(SDL_WaylandSeat *seat)
{
    إذا (seat->متن_داخلا.zwp_متن_داخلا) {
        SDL_دري_معلومات *focus = seat->keyboard.focus;

        إذا (focus && focus->متن_داخلا_props.سرگرم) {
            SDL_دري *دري = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            إذا (!seat->متن_داخلا.enabled) {
                seat->متن_داخلا.enabled = true;
                zwp_متن_داخلا_v3_enable(seat->متن_داخلا.zwp_متن_داخلا);

                // Now that it's enabled, set the input properties
                zwp_متن_داخلا_v3_سيٽ_content_type(seat->متن_داخلا.zwp_متن_داخلا, focus->متن_داخلا_props.hint, focus->متن_داخلا_props.purpose);
                إذا (!SDL_Rect_خالي_جايون(&دري->متن_داخلا_rect)) {
                    ثابت SDL_Rect scaled_rect = {
                        (صحيح)SDL_floor(دري->متن_داخلا_rect.x / focus->اشارو_scale.x),
                        (صحيح)SDL_floor(دري->متن_داخلا_rect.y / focus->اشارو_scale.y),
                        (صحيح)SDL_ceil(دري->متن_داخلا_rect.w / focus->اشارو_scale.x),
                        (صحيح)SDL_ceil(دري->متن_داخلا_rect.h / focus->اشارو_scale.y)
                    };
                    ثابت صحيح scaled_cursor = (صحيح)SDL_floor(دري->متن_داخلا_cursor / focus->اشارو_scale.x);

                    SDL_copyp(&seat->متن_داخلا.متن_داخلا_rect, &scaled_rect);
                    seat->متن_داخلا.متن_داخلا_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_متن_داخلا_v3_سيٽ_cursor_rectangle(seat->متن_داخلا.zwp_متن_داخلا,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_متن_داخلا_v3_commit(seat->متن_داخلا.zwp_متن_داخلا);

                إذا (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } وإلا {
            إذا (seat->متن_داخلا.enabled) {
                seat->متن_داخلا.enabled = false;
                SDL_zero(seat->متن_داخلا.متن_داخلا_rect);
                seat->متن_داخلا.متن_داخلا_cursor = 0;
                zwp_متن_داخلا_v3_disable(seat->متن_داخلا.zwp_متن_داخلا);
                zwp_متن_داخلا_v3_commit(seat->متن_داخلا.zwp_متن_داخلا);
            }

            إذا (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    SDL_Video_معلومات *display = _this->اندروني;

    إذا (display->متن_داخلا_manager) {
        SDL_دري_معلومات *wind = دري->اندروني;
        wind->متن_داخلا_props.hint = ZWP_متن_داخلا_V3_CONTENT_HINT_NONE;

        بدل (SDL_Get_متن_داخلا_Type(props)) {
        افتراضي:
        حالة SDL_TEXTINPUT_TYPE_متن:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_عام;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_متن_NAME:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_NAME;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_EMAIL;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_عام;
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_SENSITIVE_معلومات;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_PASSWORD;
            wind->متن_داخلا_props.hint |= (ZWP_متن_داخلا_V3_CONTENT_HINT_HIDDEN_متن | ZWP_متن_داخلا_V3_CONTENT_HINT_SENSITIVE_معلومات);
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_PASSWORD;
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_SENSITIVE_معلومات;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_عدد:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_عدد;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_PIN;
            wind->متن_داخلا_props.hint |= (ZWP_متن_داخلا_V3_CONTENT_HINT_HIDDEN_متن | ZWP_متن_داخلا_V3_CONTENT_HINT_SENSITIVE_معلومات);
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
            wind->متن_داخلا_props.purpose = ZWP_متن_داخلا_V3_CONTENT_PURPOSE_PIN;
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_SENSITIVE_معلومات;
            اكسر;
        }

        بدل (SDL_Get_متن_داخلا_Capitalization(props)) {
        افتراضي:
        حالة SDL_CAPITALIZE_NONE:
            اكسر;
        حالة SDL_CAPITALIZE_LETTERS:
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_UPPERCASE;
            اكسر;
        حالة SDL_CAPITALIZE_لفظ:
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_TITLECASE;
            اكسر;
        حالة SDL_CAPITALIZE_SENTENCES:
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            اكسر;
        }

        إذا (SDL_Get_متن_داخلا_Autocorrect(props)) {
            wind->متن_داخلا_props.hint |= (ZWP_متن_داخلا_V3_CONTENT_HINT_COMPLETION | ZWP_متن_داخلا_V3_CONTENT_HINT_SPELLCHECK);
        }
        إذا (SDL_Get_متن_داخلا_Multiline(props)) {
            wind->متن_داخلا_props.hint |= ZWP_متن_داخلا_V3_CONTENT_HINT_MULTILINE;
        }

        wind->متن_داخلا_props.سرگرم = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            إذا (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_متن_داخلا(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    أرجع true;
}

bool Wayland_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *display = _this->اندروني;

    إذا (display->متن_داخلا_manager) {
        SDL_WaylandSeat *seat;
        SDL_دري_معلومات *wind = دري->اندروني;
        wind->متن_داخلا_props.سرگرم = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            إذا (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_متن_داخلا(seat);
            }
        }
    }
#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    وإلا {
        SDL_IME_Reset();
    }
#جيڪڏهن_پورو

    أرجع true;
}

bool Wayland_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *اندروني = _this->اندروني;
    إذا (اندروني->متن_داخلا_manager) {
        SDL_WaylandSeat *seat;
        SDL_دري_معلومات *wind = دري->اندروني;

        wl_list_for_each (seat, &اندروني->seat_list, link) {
            إذا (seat->متن_داخلا.zwp_متن_داخلا && seat->keyboard.focus == wind) {
                ثابت SDL_Rect scaled_rect = {
                    (صحيح)SDL_floor(دري->متن_داخلا_rect.x / wind->اشارو_scale.x),
                    (صحيح)SDL_floor(دري->متن_داخلا_rect.y / wind->اشارو_scale.y),
                    (صحيح)SDL_ceil(دري->متن_داخلا_rect.w / wind->اشارو_scale.x),
                    (صحيح)SDL_ceil(دري->متن_داخلا_rect.h / wind->اشارو_scale.y)
                };
                ثابت صحيح scaled_cursor = (صحيح)SDL_floor(دري->متن_داخلا_cursor / wind->اشارو_scale.x);

                إذا (!SDL_RectsEqual(&scaled_rect, &seat->متن_داخلا.متن_داخلا_rect) || scaled_cursor != seat->متن_داخلا.متن_داخلا_cursor) {
                    SDL_copyp(&seat->متن_داخلا.متن_داخلا_rect, &scaled_rect);
                    seat->متن_داخلا.متن_داخلا_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_متن_داخلا_v3_سيٽ_cursor_rectangle(seat->متن_داخلا.zwp_متن_داخلا,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_متن_داخلا_v3_commit(seat->متن_داخلا.zwp_متن_داخلا);
                }
            }
        }
    }
#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    وإلا {
        SDL_IME_Update_متن_داخلا_Area(دري);
    }
#جيڪڏهن_پورو
    أرجع true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_معلومات *اندروني = _this->اندروني;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (اندروني->متن_داخلا_manager != عدم);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &اندروني->seat_list, link) {
        إذا (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            اكسر;
        }
    }

    أرجع !haskeyboard && hastextmanager;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND
