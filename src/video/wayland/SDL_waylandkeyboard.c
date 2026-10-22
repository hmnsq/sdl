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
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    اگر (!internal->text_درون_داد_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    بازگشت true;
}

تهی Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    اگر (!internal->text_درون_داد_manager) {
        SDL_IME_Quit();
    }
#endif
}

تهی Wayland_Seat_Update_Text_درون_داد(SDL_WaylandSeat *seat)
{
    اگر (seat->text_درون_داد.zwp_text_درون_داد) {
        SDL_WindowData *focus = seat->keyboard.focus;

        اگر (focus && focus->text_درون_داد_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            اگر (!seat->text_درون_داد.enabled) {
                seat->text_درون_داد.enabled = true;
                zwp_text_درون_داد_v3_enable(seat->text_درون_داد.zwp_text_درون_داد);

                // Now that it's enabled, set the input properties
                zwp_text_درون_داد_v3_set_content_type(seat->text_درون_داد.zwp_text_درون_داد, focus->text_درون_داد_props.hint, focus->text_درون_داد_props.purpose);
                اگر (!SDL_RectEmpty(&window->text_درون_داد_rect)) {
                    ثابت SDL_Rect scaled_rect = {
                        (صحیح)SDL_floor(window->text_درون_داد_rect.x / focus->pointer_scale.x),
                        (صحیح)SDL_floor(window->text_درون_داد_rect.y / focus->pointer_scale.y),
                        (صحیح)SDL_ceil(window->text_درون_داد_rect.w / focus->pointer_scale.x),
                        (صحیح)SDL_ceil(window->text_درون_داد_rect.h / focus->pointer_scale.y)
                    };
                    ثابت صحیح scaled_cursor = (صحیح)SDL_floor(window->text_درون_داد_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_درون_داد.text_درون_داد_rect, &scaled_rect);
                    seat->text_درون_داد.text_درون_داد_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_درون_داد_v3_set_cursor_rectangle(seat->text_درون_داد.zwp_text_درون_داد,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_درون_داد_v3_commit(seat->text_درون_داد.zwp_text_درون_داد);

                اگر (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } وگرنه {
            اگر (seat->text_درون_داد.enabled) {
                seat->text_درون_داد.enabled = false;
                SDL_zero(seat->text_درون_داد.text_درون_داد_rect);
                seat->text_درون_داد.text_درون_داد_cursor = 0;
                zwp_text_درون_داد_v3_disable(seat->text_درون_داد.zwp_text_درون_داد);
                zwp_text_درون_داد_v3_commit(seat->text_درون_داد.zwp_text_درون_داد);
            }

            اگر (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    اگر (display->text_درون_داد_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_درون_داد_props.hint = ZWP_TEXT_درون_داد_V3_CONTENT_HINT_NONE;

        انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
        پیشفرض:
        حالت SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_NORMAL;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_NAME;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_EMAIL;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SENSITIVE_DATA;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_درون_داد_props.hint |= (ZWP_TEXT_درون_داد_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SENSITIVE_DATA);
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SENSITIVE_DATA;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_عدد:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_عدد;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_PIN;
            wind->text_درون_داد_props.hint |= (ZWP_TEXT_درون_داد_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SENSITIVE_DATA);
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
            wind->text_درون_داد_props.purpose = ZWP_TEXT_درون_داد_V3_CONTENT_PURPOSE_PIN;
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SENSITIVE_DATA;
            بشکن;
        }

        انتخاب (SDL_Get_Text_درون_داد_Capitalization(props)) {
        پیشفرض:
        حالت SDL_CAPITALIZE_NONE:
            بشکن;
        حالت SDL_CAPITALIZE_LETTERS:
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_UPPERCASE;
            بشکن;
        حالت SDL_CAPITALIZE_واژگان:
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_TITLECASE;
            بشکن;
        حالت SDL_CAPITALIZE_SENTENCES:
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            بشکن;
        }

        اگر (SDL_Get_Text_درون_داد_Autocorrect(props)) {
            wind->text_درون_داد_props.hint |= (ZWP_TEXT_درون_داد_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_درون_داد_V3_CONTENT_HINT_SPELLCHECK);
        }
        اگر (SDL_Get_Text_درون_داد_Multiline(props)) {
            wind->text_درون_داد_props.hint |= ZWP_TEXT_درون_داد_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_درون_داد_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            اگر (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_درون_داد(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    بازگشت true;
}

bool Wayland_Stop_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    اگر (display->text_درون_داد_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_درون_داد_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            اگر (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_درون_داد(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    وگرنه {
        SDL_IME_Reset();
    }
#endif

    بازگشت true;
}

bool Wayland_Update_Text_درون_داد_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    اگر (internal->text_درون_داد_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            اگر (seat->text_درون_داد.zwp_text_درون_داد && seat->keyboard.focus == wind) {
                ثابت SDL_Rect scaled_rect = {
                    (صحیح)SDL_floor(window->text_درون_داد_rect.x / wind->pointer_scale.x),
                    (صحیح)SDL_floor(window->text_درون_داد_rect.y / wind->pointer_scale.y),
                    (صحیح)SDL_ceil(window->text_درون_داد_rect.w / wind->pointer_scale.x),
                    (صحیح)SDL_ceil(window->text_درون_داد_rect.h / wind->pointer_scale.y)
                };
                ثابت صحیح scaled_cursor = (صحیح)SDL_floor(window->text_درون_داد_cursor / wind->pointer_scale.x);

                اگر (!SDL_RectsEqual(&scaled_rect, &seat->text_درون_داد.text_درون_داد_rect) || scaled_cursor != seat->text_درون_داد.text_درون_داد_cursor) {
                    SDL_copyp(&seat->text_درون_داد.text_درون_داد_rect, &scaled_rect);
                    seat->text_درون_داد.text_درون_داد_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_درون_داد_v3_set_cursor_rectangle(seat->text_درون_داد.zwp_text_درون_داد,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_درون_داد_v3_commit(seat->text_درون_داد.zwp_text_درون_داد);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    وگرنه {
        SDL_IME_Update_Text_درون_داد_Area(window);
    }
#endif
    بازگشت true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_درون_داد_manager != پوچ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        اگر (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            بشکن;
        }
    }

    بازگشت !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
