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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "SDL_waylandcolor.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "color-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_ColorInfoState
{
    ರಚನೆ wp_image_description_v1 *wp_image_description;
    ರಚನೆ wp_image_description_info_v1 *wp_image_description_info;
    ರಚನೆ wl_event_ಸರತಿ *ಸರತಿ;

    ಒಕ್ಕೂಟ
    {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;
        SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ;
    };

    ಎಣಿಕೆ
    {
        WAYLAND_COLOR_OBJECT_TYPE_ಕಿಟಕಿ,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    ಪೂರ್ಣಾಂಕ icc_fd;
    Uint32 icc_ಗಾತ್ರ;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    ಆದರೆ (state) {
        ಆದರೆ (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = ಖಾಲಿ;
        }
        ಆದರೆ (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = ಖಾಲಿ;
        }
    }
}

ಶೂನ್ಯ Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    ಆದರೆ (state) {
        Wayland_CancelColorInfoRequest(state);
        ಆದರೆ (state->ಸರತಿ) {
            WAYLAND_wl_event_ಸರತಿ_destroy(state->ಸರತಿ);
        }

        ಆಯ್ಕೆ (state->object_type) {
        ಸ್ಥಿತಿ WAYLAND_COLOR_OBJECT_TYPE_ಕಿಟಕಿ:
            state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->color_info_state = ಖಾಲಿ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_ದತ್ತಾಂಶ->color_info_state = ಖಾಲಿ;
            ನಿಲ್ಲಿಸು;
        }

        SDL_free(state);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                               ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ದತ್ತಾಂಶ;
    Wayland_CancelColorInfoRequest(state);

    ಆಯ್ಕೆ (state->object_type) {
        ಸ್ಥಿತಿ WAYLAND_COLOR_OBJECT_TYPE_ಕಿಟಕಿ:
        {
            SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, &state->HDR, true);
            ಆದರೆ (state->icc_ಗಾತ್ರ) {
                state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->icc_fd = state->icc_fd;
                state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->icc_ಗಾತ್ರ = state->icc_ಗಾತ್ರ;
                SDL_Send_ಕಿಟಕಿ_Event(state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_ICCPROF_ಬದಲಾಯಿತು, 0, 0);
            }
        } ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_ದತ್ತಾಂಶ->HDR, &state->HDR);

            ಆದರೆ (state->display_ದತ್ತಾಂಶ->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_ದತ್ತಾಂಶ->display);
                ಆದರೆ (disp) {
                    SDL_ಗಣ_Display_HDRProperties(disp, &state->HDR);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_copyp(&state->display_ದತ್ತಾಂಶ->placeholder.HDR, &state->HDR);
            }
        } ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_icc_file(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                   ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_ಗಾತ್ರ)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ದತ್ತಾಂಶ;

    state->icc_fd = icc;
    state->icc_ಗಾತ್ರ = icc_ಗಾತ್ರ;
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_primaries(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                    ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_primaries_named(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                          ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_tf_power(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                   ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_tf_named(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                   ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_luminances(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                     ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ದತ್ತಾಂಶ;
    ಆದರೆ (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (ದಶಮಾಂಶ)max_lum / (ದಶಮಾಂಶ)reference_lum;
    } ಇಲ್ಲದಿದ್ದರೆ {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_ಗುರಿ_primaries(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                           ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_ಗುರಿ_luminance(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                           ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_ಗುರಿ_max_cll(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                         ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_info_handle_ಗುರಿ_max_fall(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                          ರಚನೆ wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_ಮುಗಿದ,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_ಗುರಿ_primaries,
    image_description_info_handle_ಗುರಿ_luminance,
    image_description_info_handle_ಗುರಿ_max_cll,
    image_description_info_handle_ಗುರಿ_max_fall
};

ಸ್ಥಿರ ಶೂನ್ಯ PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_ದತ್ತಾಂಶ *vid = SDL_GetVideoDevice()->ಆಂತರಿಕ;

    // Run the image description sequence to completion in its own queue.
    ಆಗ (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_ಸರತಿ(vid->display, state->ಸರತಿ);
    }

    Wayland_FreeColorInfoState(state);
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_handle_failed(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                            ರಚನೆ wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ_2)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ದತ್ತಾಂಶ;
    Wayland_CancelColorInfoRequest(state);

    ಆದರೆ (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_handle_ready2(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                            ರಚನೆ wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t ತಟಸ್ಥ_hi, uint32_t ತಟಸ್ಥ_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ದತ್ತಾಂಶ;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    ಆದರೆ (state->deferred_event_processing) {
        SDL_Video_ದತ್ತಾಂಶ *vid = SDL_GetVideoDevice()->ಆಂತರಿಕ;
        state->ಸರತಿ = Wayland_Display_Create_ಸರತಿ(vid->display, "SDL Color Management Queue");

        ರಚನೆ wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_ಗಣ_ಸರತಿ(image_desc_wrapper, state->ಸರತಿ);
        state->wp_image_description_info = wp_image_description_v1_get_information((ರಚನೆ wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } ಇಲ್ಲದಿದ್ದರೆ {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_ಕೂಡಿಸು_listener(state->wp_image_description_info, &image_description_info_listener, ದತ್ತಾಂಶ);

    ಆದರೆ (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ image_description_handle_ready(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                           ರಚನೆ wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t ತಟಸ್ಥ)
{
    image_description_handle_ready2(ದತ್ತಾಂಶ, wp_image_description_v1, 0, ತಟಸ್ಥ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

ಶೂನ್ಯ Wayland_Get_Color_Info_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, ಗಾತ್ರ(Wayland_ColorInfoState));

    ಆದರೆ (state) {
        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->color_info_state = state;
        state->ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_ಕಿಟಕಿ;
        state->deferred_event_processing = defer_event_processing;

        ಆದರೆ (!defer_event_processing) {
            state->ಸರತಿ = Wayland_Display_Create_ಸರತಿ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->wayland_ದತ್ತಾಂಶ->display, "SDL Color Management Queue");

            ರಚನೆ wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_ಗಣ_ಸರತಿ(surface_feedback_wrapper, state->ಸರತಿ);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((ರಚನೆ wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } ಇಲ್ಲದಿದ್ದರೆ {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_ಕೂಡಿಸು_listener(state->wp_image_description, &image_description_listener, state);

        ಆದರೆ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

ಶೂನ್ಯ Wayland_GetColorInfoForOutput(SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_ದತ್ತಾಂಶ->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, ಗಾತ್ರ(Wayland_ColorInfoState));

    ಆದರೆ (state) {
        display_ದತ್ತಾಂಶ->color_info_state = state;
        state->display_ದತ್ತಾಂಶ = display_ದತ್ತಾಂಶ;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        ಆದರೆ (!defer_event_processing) {
            state->ಸರತಿ = Wayland_Display_Create_ಸರತಿ(display_ದತ್ತಾಂಶ->videodata->display, "SDL Color Management Queue");

            ರಚನೆ wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_ದತ್ತಾಂಶ->wp_color_management_output);
            WAYLAND_wl_proxy_ಗಣ_ಸರತಿ(output_feedback_wrapper, state->ಸರತಿ);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((ರಚನೆ wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } ಇಲ್ಲದಿದ್ದರೆ {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_ದತ್ತಾಂಶ->wp_color_management_output);
        }
        wp_image_description_v1_ಕೂಡಿಸು_listener(state->wp_image_description, &image_description_listener, state);

        ಆದರೆ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
