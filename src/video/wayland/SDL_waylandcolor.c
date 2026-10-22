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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandcolor.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "color-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_ColorInfoState
{
    ਬਣਤਰ wp_image_description_v1 *wp_image_description;
    ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info;
    ਬਣਤਰ wl_event_ਕਤਾਰ *ਕਤਾਰ;

    ਸੰਘ
    {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2;
        SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ;
    };

    ਗਿਣਤੀ
    {
        WAYLAND_COLOR_OBJECT_TYPE_ਖਿੜਕੀ,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    ਪੂਰਨ icc_fd;
    Uint32 icc_ਮਾਪ;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

ਸਥਿਰ ਖਾਲੀ Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    ਜੇ (state) {
        ਜੇ (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = ਨਿਰਾ;
        }
        ਜੇ (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = ਨਿਰਾ;
        }
    }
}

ਖਾਲੀ Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    ਜੇ (state) {
        Wayland_CancelColorInfoRequest(state);
        ਜੇ (state->ਕਤਾਰ) {
            WAYLAND_wl_event_ਕਤਾਰ_destroy(state->ਕਤਾਰ);
        }

        ਚੋਣ (state->object_type) {
        ਹਾਲਤ WAYLAND_COLOR_OBJECT_TYPE_ਖਿੜਕੀ:
            state->ਖਿੜਕੀ_ਅੰਕੜੇ_2->color_info_state = ਨਿਰਾ;
            ਰੋਕੋ;
        ਹਾਲਤ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_ਅੰਕੜੇ->color_info_state = ਨਿਰਾ;
            ਰੋਕੋ;
        }

        SDL_free(state);
    }
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ,
                                               ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ਅੰਕੜੇ;
    Wayland_CancelColorInfoRequest(state);

    ਚੋਣ (state->object_type) {
        ਹਾਲਤ WAYLAND_COLOR_OBJECT_TYPE_ਖਿੜਕੀ:
        {
            SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(state->ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, &state->HDR, true);
            ਜੇ (state->icc_ਮਾਪ) {
                state->ਖਿੜਕੀ_ਅੰਕੜੇ_2->icc_fd = state->icc_fd;
                state->ਖਿੜਕੀ_ਅੰਕੜੇ_2->icc_ਮਾਪ = state->icc_ਮਾਪ;
                SDL_Send_ਖਿੜਕੀ_Event(state->ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_ICCPROF_ਬਦਲਿਆ, 0, 0);
            }
        } ਰੋਕੋ;
        ਹਾਲਤ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_ਅੰਕੜੇ->HDR, &state->HDR);

            ਜੇ (state->display_ਅੰਕੜੇ->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_ਅੰਕੜੇ->display);
                ਜੇ (disp) {
                    SDL_ਸੈੱਟ_Display_HDRProperties(disp, &state->HDR);
                }
            } ਨਹੀਂਤਾਂ {
                SDL_copyp(&state->display_ਅੰਕੜੇ->placeholder.HDR, &state->HDR);
            }
        } ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_icc_file(ਖਾਲੀ *ਅੰਕੜੇ,
                                                   ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_ਮਾਪ)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ਅੰਕੜੇ;

    state->icc_fd = icc;
    state->icc_ਮਾਪ = icc_ਮਾਪ;
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_primaries(ਖਾਲੀ *ਅੰਕੜੇ,
                                                    ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_primaries_named(ਖਾਲੀ *ਅੰਕੜੇ,
                                                          ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_tf_power(ਖਾਲੀ *ਅੰਕੜੇ,
                                                   ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_tf_named(ਖਾਲੀ *ਅੰਕੜੇ,
                                                   ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_luminances(ਖਾਲੀ *ਅੰਕੜੇ,
                                                     ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ਅੰਕੜੇ;
    ਜੇ (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (ਦਸ਼ਮਲਵ)max_lum / (ਦਸ਼ਮਲਵ)reference_lum;
    } ਨਹੀਂਤਾਂ {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_ਨਿਸ਼ਾਨਾ_primaries(ਖਾਲੀ *ਅੰਕੜੇ,
                                                           ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_ਨਿਸ਼ਾਨਾ_luminance(ਖਾਲੀ *ਅੰਕੜੇ,
                                                           ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_ਨਿਸ਼ਾਨਾ_max_cll(ਖਾਲੀ *ਅੰਕੜੇ,
                                                         ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ image_description_info_handle_ਨਿਸ਼ਾਨਾ_max_fall(ਖਾਲੀ *ਅੰਕੜੇ,
                                                          ਬਣਤਰ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_ਪੂਰਾ,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_ਨਿਸ਼ਾਨਾ_primaries,
    image_description_info_handle_ਨਿਸ਼ਾਨਾ_luminance,
    image_description_info_handle_ਨਿਸ਼ਾਨਾ_max_cll,
    image_description_info_handle_ਨਿਸ਼ਾਨਾ_max_fall
};

ਸਥਿਰ ਖਾਲੀ PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_ਅੰਕੜੇ *vid = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;

    // Run the image description sequence to completion in its own queue.
    ਜਦੋਂ (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_ਕਤਾਰ(vid->display, state->ਕਤਾਰ);
    }

    Wayland_FreeColorInfoState(state);
}

ਸਥਿਰ ਖਾਲੀ image_description_handle_failed(ਖਾਲੀ *ਅੰਕੜੇ,
                                            ਬਣਤਰ wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ_2)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ਅੰਕੜੇ;
    Wayland_CancelColorInfoRequest(state);

    ਜੇ (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

ਸਥਿਰ ਖਾਲੀ image_description_handle_ready2(ਖਾਲੀ *ਅੰਕੜੇ,
                                            ਬਣਤਰ wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t ਪਛਾਣ_ਤੱਤ_hi, uint32_t ਪਛਾਣ_ਤੱਤ_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ਅੰਕੜੇ;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    ਜੇ (state->deferred_event_processing) {
        SDL_Video_ਅੰਕੜੇ *vid = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
        state->ਕਤਾਰ = Wayland_Display_Create_ਕਤਾਰ(vid->display, "SDL Color Management Queue");

        ਬਣਤਰ wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ(image_desc_wrapper, state->ਕਤਾਰ);
        state->wp_image_description_info = wp_image_description_v1_get_information((ਬਣਤਰ wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } ਨਹੀਂਤਾਂ {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_ਜੋੜੋ_listener(state->wp_image_description_info, &image_description_info_listener, ਅੰਕੜੇ);

    ਜੇ (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

ਸਥਿਰ ਖਾਲੀ image_description_handle_ready(ਖਾਲੀ *ਅੰਕੜੇ,
                                           ਬਣਤਰ wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t ਪਛਾਣ_ਤੱਤ)
{
    image_description_handle_ready2(ਅੰਕੜੇ, wp_image_description_v1, 0, ਪਛਾਣ_ਤੱਤ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

ਖਾਲੀ Wayland_Get_Color_Info_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(ਖਿੜਕੀ_ਅੰਕੜੇ_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, ਆਕਾਰ(Wayland_ColorInfoState));

    ਜੇ (state) {
        ਖਿੜਕੀ_ਅੰਕੜੇ_2->color_info_state = state;
        state->ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਖਿੜਕੀ_ਅੰਕੜੇ_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_ਖਿੜਕੀ;
        state->deferred_event_processing = defer_event_processing;

        ਜੇ (!defer_event_processing) {
            state->ਕਤਾਰ = Wayland_Display_Create_ਕਤਾਰ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->wayland_ਅੰਕੜੇ->display, "SDL Color Management Queue");

            ਬਣਤਰ wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(ਖਿੜਕੀ_ਅੰਕੜੇ_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ(surface_feedback_wrapper, state->ਕਤਾਰ);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((ਬਣਤਰ wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } ਨਹੀਂਤਾਂ {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(ਖਿੜਕੀ_ਅੰਕੜੇ_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_ਜੋੜੋ_listener(state->wp_image_description, &image_description_listener, state);

        ਜੇ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

ਖਾਲੀ Wayland_GetColorInfoForOutput(SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_ਅੰਕੜੇ->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, ਆਕਾਰ(Wayland_ColorInfoState));

    ਜੇ (state) {
        display_ਅੰਕੜੇ->color_info_state = state;
        state->display_ਅੰਕੜੇ = display_ਅੰਕੜੇ;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        ਜੇ (!defer_event_processing) {
            state->ਕਤਾਰ = Wayland_Display_Create_ਕਤਾਰ(display_ਅੰਕੜੇ->videodata->display, "SDL Color Management Queue");

            ਬਣਤਰ wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_ਅੰਕੜੇ->wp_color_management_output);
            WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ(output_feedback_wrapper, state->ਕਤਾਰ);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((ਬਣਤਰ wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } ਨਹੀਂਤਾਂ {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_ਅੰਕੜੇ->wp_color_management_output);
        }
        wp_image_description_v1_ਜੋੜੋ_listener(state->wp_image_description, &image_description_listener, state);

        ਜੇ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
