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
#অন্তর্ভাৱ "SDL_internal.h"

#যদি SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "SDL_waylandvideo.h"
#অন্তর্ভাৱ "SDL_waylandevents_c.h"
#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    যদি (!internal->text_প্ৰবেশ_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    ঘূৰাই true;
}

শূন্য Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    যদি (!internal->text_প্ৰবেশ_manager) {
        SDL_IME_Quit();
    }
#endif
}

শূন্য Wayland_Seat_Update_Text_প্ৰবেশ(SDL_WaylandSeat *seat)
{
    যদি (seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ) {
        SDL_WindowData *focus = seat->keyboard.focus;

        যদি (focus && focus->text_প্ৰবেশ_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            যদি (!seat->text_প্ৰবেশ.enabled) {
                seat->text_প্ৰবেশ.enabled = true;
                zwp_text_প্ৰবেশ_v3_enable(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);

                // Now that it's enabled, set the input properties
                zwp_text_প্ৰবেশ_v3_set_content_type(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ, focus->text_প্ৰবেশ_props.hint, focus->text_প্ৰবেশ_props.purpose);
                যদি (!SDL_RectEmpty(&window->text_প্ৰবেশ_rect)) {
                    ধ্রুৱ SDL_Rect scaled_rect = {
                        (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_rect.x / focus->pointer_scale.x),
                        (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_rect.y / focus->pointer_scale.y),
                        (পূর্ণাঙ্ক)SDL_ceil(window->text_প্ৰবেশ_rect.w / focus->pointer_scale.x),
                        (পূর্ণাঙ্ক)SDL_ceil(window->text_প্ৰবেশ_rect.h / focus->pointer_scale.y)
                    };
                    ধ্রুৱ পূর্ণাঙ্ক scaled_cursor = (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_প্ৰবেশ.text_প্ৰবেশ_rect, &scaled_rect);
                    seat->text_প্ৰবেশ.text_প্ৰবেশ_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_প্ৰবেশ_v3_set_cursor_rectangle(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_প্ৰবেশ_v3_commit(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);

                যদি (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } অন্যথা {
            যদি (seat->text_প্ৰবেশ.enabled) {
                seat->text_প্ৰবেশ.enabled = false;
                SDL_zero(seat->text_প্ৰবেশ.text_প্ৰবেশ_rect);
                seat->text_প্ৰবেশ.text_প্ৰবেশ_cursor = 0;
                zwp_text_প্ৰবেশ_v3_disable(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);
                zwp_text_প্ৰবেশ_v3_commit(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);
            }

            যদি (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_প্ৰবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    যদি (display->text_প্ৰবেশ_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_প্ৰবেশ_props.hint = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_NONE;

        ৱিকল্প (SDL_Get_Text_প্ৰবেশ_Type(props)) {
        স্ৱভাৱ:
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_NORMAL;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_NAME;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_EMAIL;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SENSITIVE_DATA;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_প্ৰবেশ_props.hint |= (ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SENSITIVE_DATA);
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SENSITIVE_DATA;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_সংখ্যা;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_PIN;
            wind->text_প্ৰবেশ_props.hint |= (ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SENSITIVE_DATA);
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
            wind->text_প্ৰবেশ_props.purpose = ZWP_TEXT_প্ৰবেশ_V3_CONTENT_PURPOSE_PIN;
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SENSITIVE_DATA;
            ভঙ্গ;
        }

        ৱিকল্প (SDL_Get_Text_প্ৰবেশ_Capitalization(props)) {
        স্ৱভাৱ:
        পক্ষ SDL_CAPITALIZE_NONE:
            ভঙ্গ;
        পক্ষ SDL_CAPITALIZE_LETTERS:
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_UPPERCASE;
            ভঙ্গ;
        পক্ষ SDL_CAPITALIZE_শব্দগুলি:
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_TITLECASE;
            ভঙ্গ;
        পক্ষ SDL_CAPITALIZE_SENTENCES:
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            ভঙ্গ;
        }

        যদি (SDL_Get_Text_প্ৰবেশ_Autocorrect(props)) {
            wind->text_প্ৰবেশ_props.hint |= (ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_SPELLCHECK);
        }
        যদি (SDL_Get_Text_প্ৰবেশ_Multiline(props)) {
            wind->text_প্ৰবেশ_props.hint |= ZWP_TEXT_প্ৰবেশ_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_প্ৰবেশ_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            যদি (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_প্ৰবেশ(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    ঘূৰাই true;
}

bool Wayland_Stop_Text_প্ৰবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    যদি (display->text_প্ৰবেশ_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_প্ৰবেশ_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            যদি (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_প্ৰবেশ(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    অন্যথা {
        SDL_IME_Reset();
    }
#endif

    ঘূৰাই true;
}

bool Wayland_Update_Text_প্ৰবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    যদি (internal->text_প্ৰবেশ_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            যদি (seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ && seat->keyboard.focus == wind) {
                ধ্রুৱ SDL_Rect scaled_rect = {
                    (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_rect.x / wind->pointer_scale.x),
                    (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_rect.y / wind->pointer_scale.y),
                    (পূর্ণাঙ্ক)SDL_ceil(window->text_প্ৰবেশ_rect.w / wind->pointer_scale.x),
                    (পূর্ণাঙ্ক)SDL_ceil(window->text_প্ৰবেশ_rect.h / wind->pointer_scale.y)
                };
                ধ্রুৱ পূর্ণাঙ্ক scaled_cursor = (পূর্ণাঙ্ক)SDL_floor(window->text_প্ৰবেশ_cursor / wind->pointer_scale.x);

                যদি (!SDL_RectsEqual(&scaled_rect, &seat->text_প্ৰবেশ.text_প্ৰবেশ_rect) || scaled_cursor != seat->text_প্ৰবেশ.text_প্ৰবেশ_cursor) {
                    SDL_copyp(&seat->text_প্ৰবেশ.text_প্ৰবেশ_rect, &scaled_rect);
                    seat->text_প্ৰবেশ.text_প্ৰবেশ_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_প্ৰবেশ_v3_set_cursor_rectangle(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_প্ৰবেশ_v3_commit(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    অন্যথা {
        SDL_IME_Update_Text_প্ৰবেশ_Area(window);
    }
#endif
    ঘূৰাই true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_প্ৰবেশ_manager != রিক্ত);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        যদি (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            ভঙ্গ;
        }
    }

    ঘূৰাই !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
