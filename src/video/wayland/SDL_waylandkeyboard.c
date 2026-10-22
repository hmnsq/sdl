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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "text-input-unstable-v3-client-protocol.h"

bool Wayland_InitKeyboard(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_USE_IME
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    ఒకవేళ (!అంతర్గత->పాఠ్యం_ఆదానం_manager) {
        SDL_IME_Init();
    }
#అయితే_ముగింపు
    SDL_సమితి_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    తిరిగి true;
}

శూన్య Wayland_QuitKeyboard(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_USE_IME
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    ఒకవేళ (!అంతర్గత->పాఠ్యం_ఆదానం_manager) {
        SDL_IME_Quit();
    }
#అయితే_ముగింపు
}

శూన్య Wayland_Seat_Update_పాఠ్యం_ఆదానం(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం) {
        SDL_కిటికీ_దత్తాంశం *focus = seat->keyboard.focus;

        ఒకవేళ (focus && focus->పాఠ్యం_ఆదానం_props.చురుకైన) {
            SDL_కిటికీ *కిటికీ = focus->sdlwindow;

            // Enabling will reset all state, so don't do it redundantly.
            ఒకవేళ (!seat->పాఠ్యం_ఆదానం.enabled) {
                seat->పాఠ్యం_ఆదానం.enabled = true;
                zwp_పాఠ్యం_ఆదానం_v3_enable(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);

                // Now that it's enabled, set the input properties
                zwp_పాఠ్యం_ఆదానం_v3_సమితి_content_type(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం, focus->పాఠ్యం_ఆదానం_props.hint, focus->పాఠ్యం_ఆదానం_props.purpose);
                ఒకవేళ (!SDL_Rect_ఖాళీలు(&కిటికీ->పాఠ్యం_ఆదానం_rect)) {
                    స్థిరరాశి SDL_Rect scaled_rect = {
                        (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_rect.x / focus->సూచిక_scale.x),
                        (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_rect.y / focus->సూచిక_scale.y),
                        (పూర్ణాంకం)SDL_ceil(కిటికీ->పాఠ్యం_ఆదానం_rect.w / focus->సూచిక_scale.x),
                        (పూర్ణాంకం)SDL_ceil(కిటికీ->పాఠ్యం_ఆదానం_rect.h / focus->సూచిక_scale.y)
                    };
                    స్థిరరాశి పూర్ణాంకం scaled_cursor = (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_cursor / focus->సూచిక_scale.x);

                    SDL_copyp(&seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_rect, &scaled_rect);
                    seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_పాఠ్యం_ఆదానం_v3_సమితి_cursor_rectangle(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                }
                zwp_పాఠ్యం_ఆదానం_v3_commit(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);

                ఒకవేళ (seat->keyboard.xkb.compose_state) {
                    // Reset compose state so composite and dead keys don't carry over
                    WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
                }
            }
        } లేకపోతే {
            ఒకవేళ (seat->పాఠ్యం_ఆదానం.enabled) {
                seat->పాఠ్యం_ఆదానం.enabled = false;
                SDL_zero(seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_rect);
                seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_cursor = 0;
                zwp_పాఠ్యం_ఆదానం_v3_disable(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);
                zwp_పాఠ్యం_ఆదానం_v3_commit(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);
            }

            ఒకవేళ (seat->keyboard.xkb.compose_state) {
                // Reset compose state so composite and dead keys don't carry over
                WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
            }
        }
    }
}

bool Wayland_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    SDL_Video_దత్తాంశం *display = _this->అంతర్గత;

    ఒకవేళ (display->పాఠ్యం_ఆదానం_manager) {
        SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
        wind->పాఠ్యం_ఆదానం_props.hint = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_NONE;

        ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
        అప్రమేయ:
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_సాధారణ;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_NAME:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_NAME;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_EMAIL:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_EMAIL;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_USERNAME:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_సాధారణ;
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SENSITIVE_దత్తాంశం;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_HIDDEN:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_PASSWORD;
            wind->పాఠ్యం_ఆదానం_props.hint |= (ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_HIDDEN_పాఠ్యం | ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SENSITIVE_దత్తాంశం);
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_VISIBLE:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_PASSWORD;
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SENSITIVE_దత్తాంశం;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_సంఖ్య;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_PIN;
            wind->పాఠ్యం_ఆదానం_props.hint |= (ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_HIDDEN_పాఠ్యం | ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SENSITIVE_దత్తాంశం);
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_VISIBLE:
            wind->పాఠ్యం_ఆదానం_props.purpose = ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_PURPOSE_PIN;
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SENSITIVE_దత్తాంశం;
            ఆపు;
        }

        ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Capitalization(props)) {
        అప్రమేయ:
        స్థితి SDL_CAPITALIZE_NONE:
            ఆపు;
        స్థితి SDL_CAPITALIZE_LETTERS:
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_UPPERCASE;
            ఆపు;
        స్థితి SDL_CAPITALIZE_పదాలు:
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_TITLECASE;
            ఆపు;
        స్థితి SDL_CAPITALIZE_SENTENCES:
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_AUTO_CAPITALIZATION;
            ఆపు;
        }

        ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Autocorrect(props)) {
            wind->పాఠ్యం_ఆదానం_props.hint |= (ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_COMPLETION | ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_SPELLCHECK);
        }
        ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Multiline(props)) {
            wind->పాఠ్యం_ఆదానం_props.hint |= ZWP_పాఠ్యం_ఆదానం_V3_CONTENT_HINT_MULTILINE;
        }

        wind->పాఠ్యం_ఆదానం_props.చురుకైన = true;

        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            ఒకవేళ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_పాఠ్యం_ఆదానం(seat);
            }
        }
    }

    /* Always return true, even if the text input protocol isn't supported, as basic
     * text can still be obtained from keysyms and the composition system.
     */
    తిరిగి true;
}

bool Wayland_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *display = _this->అంతర్గత;

    ఒకవేళ (display->పాఠ్యం_ఆదానం_manager) {
        SDL_WaylandSeat *seat;
        SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
        wind->పాఠ్యం_ఆదానం_props.చురుకైన = false;

        wl_list_for_each (seat, &display->seat_list, link) {
            ఒకవేళ (seat->keyboard.focus == wind) {
                Wayland_Seat_Update_పాఠ్యం_ఆదానం(seat);
            }
        }
    }
#నిర్వచితమైతే SDL_USE_IME
    లేకపోతే {
        SDL_IME_Reset();
    }
#అయితే_ముగింపు

    తిరిగి true;
}

bool Wayland_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    ఒకవేళ (అంతర్గత->పాఠ్యం_ఆదానం_manager) {
        SDL_WaylandSeat *seat;
        SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

        wl_list_for_each (seat, &అంతర్గత->seat_list, link) {
            ఒకవేళ (seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం && seat->keyboard.focus == wind) {
                స్థిరరాశి SDL_Rect scaled_rect = {
                    (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_rect.x / wind->సూచిక_scale.x),
                    (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_rect.y / wind->సూచిక_scale.y),
                    (పూర్ణాంకం)SDL_ceil(కిటికీ->పాఠ్యం_ఆదానం_rect.w / wind->సూచిక_scale.x),
                    (పూర్ణాంకం)SDL_ceil(కిటికీ->పాఠ్యం_ఆదానం_rect.h / wind->సూచిక_scale.y)
                };
                స్థిరరాశి పూర్ణాంకం scaled_cursor = (పూర్ణాంకం)SDL_floor(కిటికీ->పాఠ్యం_ఆదానం_cursor / wind->సూచిక_scale.x);

                ఒకవేళ (!SDL_RectsEqual(&scaled_rect, &seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_rect) || scaled_cursor != seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_cursor) {
                    SDL_copyp(&seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_rect, &scaled_rect);
                    seat->పాఠ్యం_ఆదానం.పాఠ్యం_ఆదానం_cursor = scaled_cursor;

                    // Clamp the x value so it doesn't run too far past the end of the text input area.
                    zwp_పాఠ్యం_ఆదానం_v3_సమితి_cursor_rectangle(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం,
                                                           SDL_min(scaled_rect.x + scaled_cursor, scaled_rect.x + scaled_rect.w),
                                                           scaled_rect.y,
                                                           1,
                                                           scaled_rect.h);
                    zwp_పాఠ్యం_ఆదానం_v3_commit(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);
                }
            }
        }
    }
#నిర్వచితమైతే SDL_USE_IME
    లేకపోతే {
        SDL_IME_Update_పాఠ్యం_ఆదానం_Area(కిటికీ);
    }
#అయితే_ముగింపు
    తిరిగి true;
}

bool Wayland_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    /* In reality, we just want to return true when the screen keyboard is the
     * _only_ way to get text input. So, in addition to checking for the text
     * input protocol, make sure we don't have any physical keyboards either.
     */
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    SDL_WaylandSeat *seat;
    bool hastextmanager = (అంతర్గత->పాఠ్యం_ఆదానం_manager != ఖాళీ);
    bool haskeyboard = false;

    // Check for at least one keyboard object on one seat.
    wl_list_for_each (seat, &అంతర్గత->seat_list, link) {
        ఒకవేళ (seat->keyboard.wl_keyboard) {
            haskeyboard = true;
            ఆపు;
        }
    }

    తిరిగి !haskeyboard && hastextmanager;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
