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
#समावेश "SDL_internal.h"

#अगर SDL_VIDEO_DRIVER_WAYLAND

#समावेश "../SDL_sysvideo.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_USE_IME
    SDL_Video_तथ्य *internal = _this->internal;
    अगर (!internal->text_निवेश_manager) {
        SDL_IME_Init();
    }
#पूर्ण_अगर
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    वापस true;
}

व्योम Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_USE_IME
    SDL_Video_तथ्य *internal = _this->internal;
    अगर (!internal->text_निवेश_manager) {
        SDL_IME_Quit();
    }
#पूर्ण_अगर
}

व्योम Wayland_Seat_Update_Text_निवेश(SDL_WaylandSeat *seat)
{
    अगर (seat->text_निवेश.zwp_text_निवेश) {
        SDL_Window_तथ्य *focus = seat->keyboard.focus;

        अगर (focus && focus->text_निवेश_props.active) {
            SDL_Window *window = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            अगर (!seat->text_निवेश.enabled) {
                seat->text_निवेश.enabled = true;
                zwp_text_निवेश_v3_enable(seat->text_निवेश.zwp_text_निवेश);

                // Now that it's enabled, set the input properties
                zwp_text_निवेश_v3_set_content_type(seat->text_निवेश.zwp_text_निवेश, focus->text_निवेश_props.hint, focus->text_निवेश_props.purpose);
                अगर (!SDL_RectEmpty(&window->text_निवेश_rect)) {
                    स्थिर SDL_Rect scaled_rect = {
                        (पूर्णांक)SDL_floor(window->text_निवेश_rect.x / focus->pointer_scale.x),
                        (पूर्णांक)SDL_floor(window->text_निवेश_rect.y / focus->pointer_scale.y),
                        (पूर्णांक)SDL_ceil(window->text_निवेश_rect.w / focus->pointer_scale.x),
                        (पूर्णांक)SDL_ceil(window->text_निवेश_rect.h / focus->pointer_scale.y)
                    };
                    स्थिर पूर्णांक scaled_cursor = (पूर्णांक)SDL_floor(window->text_निवेश_cursor / focus->pointer_scale.x);

                    SDL_copyp(&seat->text_निवेश.text_निवेश_rect, &scaled_rect);
                    seat->text_निवेश.text_निवेश_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_निवेश_v3_set_cursor_rectangle(seat->text_निवेश.zwp_text_निवेश,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_text_निवेश_v3_commit(seat->text_निवेश.zwp_text_निवेश);

                अगर (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } अन्यथा {
            अगर (seat->text_निवेश.enabled) {
                seat->text_निवेश.enabled = false;
                SDL_zero(seat->text_निवेश.text_निवेश_rect);
                seat->text_निवेश.text_निवेश_cursor = 0;
                zwp_text_निवेश_v3_disable(seat->text_निवेश.zwp_text_निवेश);
                zwp_text_निवेश_v3_commit(seat->text_निवेश.zwp_text_निवेश);
            }

            अगर (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_तथ्य *display = _this->internal;

    अगर (display->text_निवेश_manager) {
        SDL_Window_तथ्य *wind = window->internal;
        wind->text_निवेश_props.hint = ZWP_TEXT_निवेश_V3_CONTENT_HINT_NONE;

        चयन (SDL_Get_Text_निवेश_Type(props)) {
        शेष:
        हाल SDL_TEXTINPUT_TYPE_TEXT:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_NORMAL;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_TEXT_NAME:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_NAME;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_EMAIL;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_NORMAL;
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_SENSITIVE_तथ्य;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_निवेश_props.hint |= (ZWP_TEXT_निवेश_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_निवेश_V3_CONTENT_HINT_SENSITIVE_तथ्य);
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_PASSWORD;
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_SENSITIVE_तथ्य;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_संख्या:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_संख्या;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_PIN;
            wind->text_निवेश_props.hint |= (ZWP_TEXT_निवेश_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_निवेश_V3_CONTENT_HINT_SENSITIVE_तथ्य);
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
            wind->text_निवेश_props.purpose = ZWP_TEXT_निवेश_V3_CONTENT_PURPOSE_PIN;
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_SENSITIVE_तथ्य;
            अवरोध;
        }

        चयन (SDL_Get_Text_निवेश_Capitalization(props)) {
        शेष:
        हाल SDL_CAPITALIZE_NONE:
            अवरोध;
        हाल SDL_CAPITALIZE_LETTERS:
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_UPPERCASE;
            अवरोध;
        हाल SDL_CAPITALIZE_शब्दगण:
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_TITLECASE;
            अवरोध;
        हाल SDL_CAPITALIZE_SENTENCES:
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            अवरोध;
        }

        अगर (SDL_Get_Text_निवेश_Autocorrect(props)) {
            wind->text_निवेश_props.hint |= (ZWP_TEXT_निवेश_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_निवेश_V3_CONTENT_HINT_SPELLCHECK);
        }
        अगर (SDL_Get_Text_निवेश_Multiline(props)) {
            wind->text_निवेश_props.hint |= ZWP_TEXT_निवेश_V3_CONTENT_HINT_MULTILINE;
        }

        wind->text_निवेश_props.active = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            अगर (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_निवेश(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    वापस true;
}

bool Wayland_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *display = _this->internal;

    अगर (display->text_निवेश_manager) {
        SDL_WaylandSeat *seat;
        SDL_Window_तथ्य *wind = window->internal;
        wind->text_निवेश_props.active = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            अगर (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_Text_निवेश(seat);
            }
        }
    }
#अगर_घोषित SDL_USE_IME
    अन्यथा {
        SDL_IME_Reset();
    }
#पूर्ण_अगर

    वापस true;
}

bool Wayland_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *internal = _this->internal;
    अगर (internal->text_निवेश_manager) {
        SDL_WaylandSeat *seat;
        SDL_Window_तथ्य *wind = window->internal;

        wl_list_for_each (seat, &internal->seat_list, link) {
            अगर (seat->text_निवेश.zwp_text_निवेश && seat->keyboard.focus == wind) {
                स्थिर SDL_Rect scaled_rect = {
                    (पूर्णांक)SDL_floor(window->text_निवेश_rect.x / wind->pointer_scale.x),
                    (पूर्णांक)SDL_floor(window->text_निवेश_rect.y / wind->pointer_scale.y),
                    (पूर्णांक)SDL_ceil(window->text_निवेश_rect.w / wind->pointer_scale.x),
                    (पूर्णांक)SDL_ceil(window->text_निवेश_rect.h / wind->pointer_scale.y)
                };
                स्थिर पूर्णांक scaled_cursor = (पूर्णांक)SDL_floor(window->text_निवेश_cursor / wind->pointer_scale.x);

                अगर (!SDL_RectsEqual(&scaled_rect, &seat->text_निवेश.text_निवेश_rect) || scaled_cursor != seat->text_निवेश.text_निवेश_cursor) {
                    SDL_copyp(&seat->text_निवेश.text_निवेश_rect, &scaled_rect);
                    seat->text_निवेश.text_निवेश_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_text_निवेश_v3_set_cursor_rectangle(seat->text_निवेश.zwp_text_निवेश,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_text_निवेश_v3_commit(seat->text_निवेश.zwp_text_निवेश);
                }
            }
        }
    }
#अगर_घोषित SDL_USE_IME
    अन्यथा {
        SDL_IME_Update_Text_निवेश_Area(window);
    }
#पूर्ण_अगर
    वापस true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_तथ्य *internal = _this->internal;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (internal->text_निवेश_manager != शून्य);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &internal->seat_list, link) {
        अगर (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            अवरोध;
        }
    }

    वापस !haskeyboard && hastextmanager;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
