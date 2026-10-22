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
#அந்தர்பாவ "SDL_internal.h"

#எனில் SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    எனில் (!internal->text_உள்ளீடு_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    திரும்பு true;
}

வெறுமை Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    எனில் (!internal->text_உள்ளீடு_manager) {
        SDL_IME_Quit();
    }
#endif
}

வெறுமை Wayland_Seat_Update_Text_உள்ளீடு(SDL_WaylandSeat *seat)
{
    எனில் (seat->text_உள்ளீடு.zwp_text_உள்ளீடு) {
        SDL_WindowData *focus = seat->keyboard.focus;

        எனில் (focus && focus->text_உள்ளீடு_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            எனில் (!seat->text_உள்ளீடு.enabled) {
                seat->text_உள்ளீடு.enabled = true;
                zwp_text_உள்ளீடு_v3_enable(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);

                // Now that it's enabled, set the input properties
                zwp_text_உள்ளீடு_v3_set_content_type(seat->text_உள்ளீடு.zwp_text_உள்ளீடு, focus->text_உள்ளீடு_props.hint, focus->text_உள்ளீடு_props.purpose);
                எனில் (!SDL_RectEmpty(&window->text_உள்ளீடு_rect)) {
                    மாறிலி SDL_Rect scaled_rect = {
                        (முழு)SDL_floor(window->text_உள்ளீடு_rect.x / focus->pointer_scale.x),
                        (முழு)SDL_floor(window->text_உள்ளீடு_rect.y / focus->pointer_scale.y),
                        (முழு)SDL_ceil(window->text_உள்ளீடு_rect.w / focus->pointer_scale.x),
                        (முழு)SDL_ceil(window->text_உள்ளீடு_rect.h / focus->pointer_scale.y)
                    };
                    மாறிலி முழு scaled_cursor = (முழு)SDL_floor(window->text_உள்ளீடு_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_உள்ளீடு.text_உள்ளீடு_rect, &scaled_rect);
                    seat->text_உள்ளீடு.text_உள்ளீடு_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_உள்ளீடு_v3_set_cursor_rectangle(seat->text_உள்ளீடு.zwp_text_உள்ளீடு,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_உள்ளீடு_v3_commit(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);

                எனில் (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } இல்லையெனில் {
            எனில் (seat->text_உள்ளீடு.enabled) {
                seat->text_உள்ளீடு.enabled = false;
                SDL_zero(seat->text_உள்ளீடு.text_உள்ளீடு_rect);
                seat->text_உள்ளீடு.text_உள்ளீடு_cursor = 0;
                zwp_text_உள்ளீடு_v3_disable(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);
                zwp_text_உள்ளீடு_v3_commit(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);
            }

            எனில் (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    எனில் (display->text_உள்ளீடு_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_உள்ளீடு_props.hint = ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_NONE;

        தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
        இயல்பு:
        நிலை SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_NORMAL;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_NAME;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_EMAIL;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SENSITIVE_DATA;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_உள்ளீடு_props.hint |= (ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SENSITIVE_DATA);
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SENSITIVE_DATA;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_எண்:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_எண்;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_HIDDEN:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_PIN;
            wind->text_உள்ளீடு_props.hint |= (ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SENSITIVE_DATA);
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_VISIBLE:
            wind->text_உள்ளீடு_props.purpose = ZWP_TEXT_உள்ளீடு_V3_CONTENT_PURPOSE_PIN;
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SENSITIVE_DATA;
            நிறுத்து;
        }

        தேர்வு (SDL_Get_Text_உள்ளீடு_Capitalization(props)) {
        இயல்பு:
        நிலை SDL_CAPITALIZE_NONE:
            நிறுத்து;
        நிலை SDL_CAPITALIZE_LETTERS:
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_UPPERCASE;
            நிறுத்து;
        நிலை SDL_CAPITALIZE_சொற்கள்:
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_TITLECASE;
            நிறுத்து;
        நிலை SDL_CAPITALIZE_SENTENCES:
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            நிறுத்து;
        }

        எனில் (SDL_Get_Text_உள்ளீடு_Autocorrect(props)) {
            wind->text_உள்ளீடு_props.hint |= (ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_SPELLCHECK);
        }
        எனில் (SDL_Get_Text_உள்ளீடு_Multiline(props)) {
            wind->text_உள்ளீடு_props.hint |= ZWP_TEXT_உள்ளீடு_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_உள்ளீடு_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            எனில் (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_உள்ளீடு(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    திரும்பு true;
}

bool Wayland_Stop_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    எனில் (display->text_உள்ளீடு_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_உள்ளீடு_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            எனில் (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_உள்ளீடு(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    இல்லையெனில் {
        SDL_IME_Reset();
    }
#endif

    திரும்பு true;
}

bool Wayland_Update_Text_உள்ளீடு_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    எனில் (internal->text_உள்ளீடு_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            எனில் (seat->text_உள்ளீடு.zwp_text_உள்ளீடு && seat->keyboard.focus == wind) {
                மாறிலி SDL_Rect scaled_rect = {
                    (முழு)SDL_floor(window->text_உள்ளீடு_rect.x / wind->pointer_scale.x),
                    (முழு)SDL_floor(window->text_உள்ளீடு_rect.y / wind->pointer_scale.y),
                    (முழு)SDL_ceil(window->text_உள்ளீடு_rect.w / wind->pointer_scale.x),
                    (முழு)SDL_ceil(window->text_உள்ளீடு_rect.h / wind->pointer_scale.y)
                };
                மாறிலி முழு scaled_cursor = (முழு)SDL_floor(window->text_உள்ளீடு_cursor / wind->pointer_scale.x);

                எனில் (!SDL_RectsEqual(&scaled_rect, &seat->text_உள்ளீடு.text_உள்ளீடு_rect) || scaled_cursor != seat->text_உள்ளீடு.text_உள்ளீடு_cursor) {
                    SDL_copyp(&seat->text_உள்ளீடு.text_உள்ளீடு_rect, &scaled_rect);
                    seat->text_உள்ளீடு.text_உள்ளீடு_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_உள்ளீடு_v3_set_cursor_rectangle(seat->text_உள்ளீடு.zwp_text_உள்ளீடு,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_உள்ளீடு_v3_commit(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    இல்லையெனில் {
        SDL_IME_Update_Text_உள்ளீடு_Area(window);
    }
#endif
    திரும்பு true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_உள்ளீடு_manager != வெற்று);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        எனில் (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            நிறுத்து;
        }
    }

    திரும்பு !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
