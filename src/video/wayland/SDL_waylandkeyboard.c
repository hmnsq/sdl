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
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    إذا (!internal->text_كىرگۈزۈش_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    أرجع true;
}

فراغ Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    إذا (!internal->text_كىرگۈزۈش_manager) {
        SDL_IME_Quit();
    }
#endif
}

فراغ Wayland_Seat_Update_Text_كىرگۈزۈش(SDL_WaylandSeat *seat)
{
    إذا (seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش) {
        SDL_WindowData *focus = seat->keyboard.focus;

        إذا (focus && focus->text_كىرگۈزۈش_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            إذا (!seat->text_كىرگۈزۈش.enabled) {
                seat->text_كىرگۈزۈش.enabled = true;
                zwp_text_كىرگۈزۈش_v3_enable(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش);

                // Now that it's enabled, set the input properties
                zwp_text_كىرگۈزۈش_v3_set_content_type(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش, focus->text_كىرگۈزۈش_props.hint, focus->text_كىرگۈزۈش_props.purpose);
                إذا (!SDL_RectEmpty(&window->text_كىرگۈزۈش_rect)) {
                    ثابت SDL_Rect scaled_rect = {
                        (صحيح)SDL_floor(window->text_كىرگۈزۈش_rect.x / focus->pointer_scale.x),
                        (صحيح)SDL_floor(window->text_كىرگۈزۈش_rect.y / focus->pointer_scale.y),
                        (صحيح)SDL_ceil(window->text_كىرگۈزۈش_rect.w / focus->pointer_scale.x),
                        (صحيح)SDL_ceil(window->text_كىرگۈزۈش_rect.h / focus->pointer_scale.y)
                    };
                    ثابت صحيح scaled_cursor = (صحيح)SDL_floor(window->text_كىرگۈزۈش_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_كىرگۈزۈش.text_كىرگۈزۈش_rect, &scaled_rect);
                    seat->text_كىرگۈزۈش.text_كىرگۈزۈش_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_كىرگۈزۈش_v3_set_cursor_rectangle(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_كىرگۈزۈش_v3_commit(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش);

                إذا (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } وإلا {
            إذا (seat->text_كىرگۈزۈش.enabled) {
                seat->text_كىرگۈزۈش.enabled = false;
                SDL_zero(seat->text_كىرگۈزۈش.text_كىرگۈزۈش_rect);
                seat->text_كىرگۈزۈش.text_كىرگۈزۈش_cursor = 0;
                zwp_text_كىرگۈزۈش_v3_disable(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش);
                zwp_text_كىرگۈزۈش_v3_commit(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش);
            }

            إذا (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_كىرگۈزۈش(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    إذا (display->text_كىرگۈزۈش_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_كىرگۈزۈش_props.hint = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_NONE;

        بدل (SDL_Get_Text_كىرگۈزۈش_Type(props)) {
        افتراضي:
        حالة SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_NORMAL;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_NAME;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_EMAIL;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SENSITIVE_DATA;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_كىرگۈزۈش_props.hint |= (ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SENSITIVE_DATA);
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SENSITIVE_DATA;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_سان:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_سان;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_سان_PASSWORD_HIDDEN:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_PIN;
            wind->text_كىرگۈزۈش_props.hint |= (ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SENSITIVE_DATA);
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_سان_PASSWORD_VISIBLE:
            wind->text_كىرگۈزۈش_props.purpose = ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_PURPOSE_PIN;
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SENSITIVE_DATA;
            اكسر;
        }

        بدل (SDL_Get_Text_كىرگۈزۈش_Capitalization(props)) {
        افتراضي:
        حالة SDL_CAPITALIZE_NONE:
            اكسر;
        حالة SDL_CAPITALIZE_LETTERS:
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_UPPERCASE;
            اكسر;
        حالة SDL_CAPITALIZE_سۆزلەر:
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_TITLECASE;
            اكسر;
        حالة SDL_CAPITALIZE_SENTENCES:
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            اكسر;
        }

        إذا (SDL_Get_Text_كىرگۈزۈش_Autocorrect(props)) {
            wind->text_كىرگۈزۈش_props.hint |= (ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_SPELLCHECK);
        }
        إذا (SDL_Get_Text_كىرگۈزۈش_Multiline(props)) {
            wind->text_كىرگۈزۈش_props.hint |= ZWP_TEXT_كىرگۈزۈش_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_كىرگۈزۈش_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            إذا (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_كىرگۈزۈش(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    أرجع true;
}

bool Wayland_Stop_Text_كىرگۈزۈش(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    إذا (display->text_كىرگۈزۈش_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_كىرگۈزۈش_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            إذا (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_كىرگۈزۈش(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    وإلا {
        SDL_IME_Reset();
    }
#endif

    أرجع true;
}

bool Wayland_Update_Text_كىرگۈزۈش_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    إذا (internal->text_كىرگۈزۈش_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            إذا (seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش && seat->keyboard.focus == wind) {
                ثابت SDL_Rect scaled_rect = {
                    (صحيح)SDL_floor(window->text_كىرگۈزۈش_rect.x / wind->pointer_scale.x),
                    (صحيح)SDL_floor(window->text_كىرگۈزۈش_rect.y / wind->pointer_scale.y),
                    (صحيح)SDL_ceil(window->text_كىرگۈزۈش_rect.w / wind->pointer_scale.x),
                    (صحيح)SDL_ceil(window->text_كىرگۈزۈش_rect.h / wind->pointer_scale.y)
                };
                ثابت صحيح scaled_cursor = (صحيح)SDL_floor(window->text_كىرگۈزۈش_cursor / wind->pointer_scale.x);

                إذا (!SDL_RectsEqual(&scaled_rect, &seat->text_كىرگۈزۈش.text_كىرگۈزۈش_rect) || scaled_cursor != seat->text_كىرگۈزۈش.text_كىرگۈزۈش_cursor) {
                    SDL_copyp(&seat->text_كىرگۈزۈش.text_كىرگۈزۈش_rect, &scaled_rect);
                    seat->text_كىرگۈزۈش.text_كىرگۈزۈش_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_كىرگۈزۈش_v3_set_cursor_rectangle(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_كىرگۈزۈش_v3_commit(seat->text_كىرگۈزۈش.zwp_text_كىرگۈزۈش);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    وإلا {
        SDL_IME_Update_Text_كىرگۈزۈش_Area(window);
    }
#endif
    أرجع true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_كىرگۈزۈش_manager != عدم);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        إذا (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            اكسر;
        }
    }

    أرجع !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
