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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "SDL_waylandevents_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    എങ്കിൽ (!internal->text_നിവേശം_manager) {
        SDL_IME_Init();
    }
#endif
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    തിരികെ true;
}

ശൂന്യം Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#ifdef SDL_USE_IME
    SDL_VideoData *internal = _this->internal;
    എങ്കിൽ (!internal->text_നിവേശം_manager) {
        SDL_IME_Quit();
    }
#endif
}

ശൂന്യം Wayland_Seat_Update_Text_നിവേശം(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->text_നിവേശം.zwp_text_നിവേശം) {
        SDL_WindowData *focus = seat->keyboard.focus;

        എങ്കിൽ (focus && focus->text_നിവേശം_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            എങ്കിൽ (!seat->text_നിവേശം.enabled) {
                seat->text_നിവേശം.enabled = true;
                zwp_text_നിവേശം_v3_enable(seat->text_നിവേശം.zwp_text_നിവേശം);

                // Now that it's enabled, set the input properties
                zwp_text_നിവേശം_v3_set_content_type(seat->text_നിവേശം.zwp_text_നിവേശം, focus->text_നിവേശം_props.hint, focus->text_നിവേശം_props.purpose);
                എങ്കിൽ (!SDL_RectEmpty(&window->text_നിവേശം_rect)) {
                    സ്ഥിരം SDL_Rect scaled_rect = {
                        (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_rect.x / focus->pointer_scale.x),
                        (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_rect.y / focus->pointer_scale.y),
                        (പൂർണ്ണസംഖ്യ)SDL_ceil(window->text_നിവേശം_rect.w / focus->pointer_scale.x),
                        (പൂർണ്ണസംഖ്യ)SDL_ceil(window->text_നിവേശം_rect.h / focus->pointer_scale.y)
                    };
                    സ്ഥിരം പൂർണ്ണസംഖ്യ scaled_cursor = (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_നിവേശം.text_നിവേശം_rect, &scaled_rect);
                    seat->text_നിവേശം.text_നിവേശം_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_നിവേശം_v3_set_cursor_rectangle(seat->text_നിവേശം.zwp_text_നിവേശം,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_നിവേശം_v3_commit(seat->text_നിവേശം.zwp_text_നിവേശം);

                എങ്കിൽ (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (seat->text_നിവേശം.enabled) {
                seat->text_നിവേശം.enabled = false;
                SDL_zero(seat->text_നിവേശം.text_നിവേശം_rect);
                seat->text_നിവേശം.text_നിവേശം_cursor = 0;
                zwp_text_നിവേശം_v3_disable(seat->text_നിവേശം.zwp_text_നിവേശം);
                zwp_text_നിവേശം_v3_commit(seat->text_നിവേശം.zwp_text_നിവേശം);
            }

            എങ്കിൽ (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *display = _this->internal;

    എങ്കിൽ (display->text_നിവേശം_manager) {
        SDL_WindowData *wind = window->internal;
        wind->text_നിവേശം_props.hint = ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_NONE;

        തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
        സ്ഥിരസ്ഥിതി:
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_NORMAL;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_NAME;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_EMAIL;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SENSITIVE_DATA;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_നിവേശം_props.hint |= (ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SENSITIVE_DATA);
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SENSITIVE_DATA;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_സംഖ്യ;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_HIDDEN:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_PIN;
            wind->text_നിവേശം_props.hint |= (ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SENSITIVE_DATA);
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_VISIBLE:
            wind->text_നിവേശം_props.purpose = ZWP_TEXT_നിവേശം_V3_CONTENT_PURPOSE_PIN;
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SENSITIVE_DATA;
            നിർത്തുക;
        }

        തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Capitalization(props)) {
        സ്ഥിരസ്ഥിതി:
        അവസ്ഥ SDL_CAPITALIZE_NONE:
            നിർത്തുക;
        അവസ്ഥ SDL_CAPITALIZE_LETTERS:
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_UPPERCASE;
            നിർത്തുക;
        അവസ്ഥ SDL_CAPITALIZE_വാക്കുകൾ:
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_TITLECASE;
            നിർത്തുക;
        അവസ്ഥ SDL_CAPITALIZE_SENTENCES:
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            നിർത്തുക;
        }

        എങ്കിൽ (SDL_Get_Text_നിവേശം_Autocorrect(props)) {
            wind->text_നിവേശം_props.hint |= (ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_SPELLCHECK);
        }
        എങ്കിൽ (SDL_Get_Text_നിവേശം_Multiline(props)) {
            wind->text_നിവേശം_props.hint |= ZWP_TEXT_നിവേശം_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_നിവേശം_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            എങ്കിൽ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_നിവേശം(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    തിരികെ true;
}

bool Wayland_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *display = _this->internal;

    എങ്കിൽ (display->text_നിവേശം_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;
        wind->text_നിവേശം_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            എങ്കിൽ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_നിവേശം(seat);
            }
        }
    }
#ifdef SDL_USE_IME
    അല്ലെങ്കിൽ {
        SDL_IME_Reset();
    }
#endif

    തിരികെ true;
}

bool Wayland_Update_Text_നിവേശം_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *internal = _this->internal;
    എങ്കിൽ (internal->text_നിവേശം_manager) {
        SDL_WaylandSeat *seat;
        SDL_WindowData *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            എങ്കിൽ (seat->text_നിവേശം.zwp_text_നിവേശം && seat->keyboard.focus == wind) {
                സ്ഥിരം SDL_Rect scaled_rect = {
                    (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_rect.x / wind->pointer_scale.x),
                    (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_rect.y / wind->pointer_scale.y),
                    (പൂർണ്ണസംഖ്യ)SDL_ceil(window->text_നിവേശം_rect.w / wind->pointer_scale.x),
                    (പൂർണ്ണസംഖ്യ)SDL_ceil(window->text_നിവേശം_rect.h / wind->pointer_scale.y)
                };
                സ്ഥിരം പൂർണ്ണസംഖ്യ scaled_cursor = (പൂർണ്ണസംഖ്യ)SDL_floor(window->text_നിവേശം_cursor / wind->pointer_scale.x);

                എങ്കിൽ (!SDL_RectsEqual(&scaled_rect, &seat->text_നിവേശം.text_നിവേശം_rect) || scaled_cursor != seat->text_നിവേശം.text_നിവേശം_cursor) {
                    SDL_copyp(&seat->text_നിവേശം.text_നിവേശം_rect, &scaled_rect);
                    seat->text_നിവേശം.text_നിവേശം_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_നിവേശം_v3_set_cursor_rectangle(seat->text_നിവേശം.zwp_text_നിവേശം,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_നിവേശം_v3_commit(seat->text_നിവേശം.zwp_text_നിവേശം);
                }
            }
        }
    }
#ifdef SDL_USE_IME
    അല്ലെങ്കിൽ {
        SDL_IME_Update_Text_നിവേശം_Area(window);
    }
#endif
    തിരികെ true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_VideoData *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_നിവേശം_manager != ശൂന്യ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        എങ്കിൽ (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            നിർത്തുക;
        }
    }

    തിരികെ !haskeyboard && hastextmanager;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
