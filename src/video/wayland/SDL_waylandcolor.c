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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "SDL_waylandcolor.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandwindow.h"
#అన్తర్భావ "color-management-v1-client-protocol.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"

రకనిర్వచనం నిర్మాణం Wayland_ColorInfoState
{
    నిర్మాణం wp_image_description_v1 *wp_image_description;
    నిర్మాణం wp_image_description_info_v1 *wp_image_description_info;
    నిర్మాణం wl_event_వరుస *వరుస;

    సంఘం
    {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2;
        SDL_Display_దత్తాంశం *display_దత్తాంశం;
    };

    గణన
    {
        WAYLAND_COLOR_OBJECT_TYPE_కిటికీ,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    పూర్ణాంకం icc_fd;
    Uint32 icc_కొలత;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

స్థిర శూన్య Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    ఒకవేళ (state) {
        ఒకవేళ (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = ఖాళీ;
        }
        ఒకవేళ (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = ఖాళీ;
        }
    }
}

శూన్య Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    ఒకవేళ (state) {
        Wayland_CancelColorInfoRequest(state);
        ఒకవేళ (state->వరుస) {
            WAYLAND_wl_event_వరుస_destroy(state->వరుస);
        }

        ఎంపిక (state->object_type) {
        స్థితి WAYLAND_COLOR_OBJECT_TYPE_కిటికీ:
            state->కిటికీ_దత్తాంశం_2->color_info_state = ఖాళీ;
            ఆపు;
        స్థితి WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_దత్తాంశం->color_info_state = ఖాళీ;
            ఆపు;
        }

        SDL_free(state);
    }
}

స్థిర శూన్య image_description_info_handle_పూర్తి(శూన్య *దత్తాంశం,
                                               నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)దత్తాంశం;
    Wayland_CancelColorInfoRequest(state);

    ఎంపిక (state->object_type) {
        స్థితి WAYLAND_COLOR_OBJECT_TYPE_కిటికీ:
        {
            SDL_సమితి_కిటికీ_HDRProperties(state->కిటికీ_దత్తాంశం_2->sdlwindow, &state->HDR, true);
            ఒకవేళ (state->icc_కొలత) {
                state->కిటికీ_దత్తాంశం_2->icc_fd = state->icc_fd;
                state->కిటికీ_దత్తాంశం_2->icc_కొలత = state->icc_కొలత;
                SDL_Send_కిటికీ_Event(state->కిటికీ_దత్తాంశం_2->sdlwindow, SDL_EVENT_కిటికీ_ICCPROF_మారింది, 0, 0);
            }
        } ఆపు;
        స్థితి WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_దత్తాంశం->HDR, &state->HDR);

            ఒకవేళ (state->display_దత్తాంశం->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_దత్తాంశం->display);
                ఒకవేళ (disp) {
                    SDL_సమితి_Display_HDRProperties(disp, &state->HDR);
                }
            } లేకపోతే {
                SDL_copyp(&state->display_దత్తాంశం->placeholder.HDR, &state->HDR);
            }
        } ఆపు;
    }
}

స్థిర శూన్య image_description_info_handle_icc_file(శూన్య *దత్తాంశం,
                                                   నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_కొలత)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)దత్తాంశం;

    state->icc_fd = icc;
    state->icc_కొలత = icc_కొలత;
}

స్థిర శూన్య image_description_info_handle_primaries(శూన్య *దత్తాంశం,
                                                    నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_primaries_named(శూన్య *దత్తాంశం,
                                                          నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_tf_power(శూన్య *దత్తాంశం,
                                                   నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_tf_named(శూన్య *దత్తాంశం,
                                                   నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_luminances(శూన్య *దత్తాంశం,
                                                     నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)దత్తాంశం;
    ఒకవేళ (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (దశాంశం)max_lum / (దశాంశం)reference_lum;
    } లేకపోతే {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

స్థిర శూన్య image_description_info_handle_లక్ష్యం_primaries(శూన్య *దత్తాంశం,
                                                           నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_లక్ష్యం_luminance(శూన్య *దత్తాంశం,
                                                           నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_లక్ష్యం_max_cll(శూన్య *దత్తాంశం,
                                                         నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

స్థిర శూన్య image_description_info_handle_లక్ష్యం_max_fall(శూన్య *దత్తాంశం,
                                                          నిర్మాణం wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

స్థిర స్థిరరాశి నిర్మాణం wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_పూర్తి,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_లక్ష్యం_primaries,
    image_description_info_handle_లక్ష్యం_luminance,
    image_description_info_handle_లక్ష్యం_max_cll,
    image_description_info_handle_లక్ష్యం_max_fall
};

స్థిర శూన్య PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_దత్తాంశం *vid = SDL_GetVideoDevice()->అంతర్గత;

    // Run the image description sequence to completion in its own queue.
    అయితే (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_వరుస(vid->display, state->వరుస);
    }

    Wayland_FreeColorInfoState(state);
}

స్థిర శూన్య image_description_handle_failed(శూన్య *దత్తాంశం,
                                            నిర్మాణం wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            స్థిరరాశి అక్షరం *సందేశం_2)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)దత్తాంశం;
    Wayland_CancelColorInfoRequest(state);

    ఒకవేళ (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

స్థిర శూన్య image_description_handle_ready2(శూన్య *దత్తాంశం,
                                            నిర్మాణం wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t తటస్థం_hi, uint32_t తటస్థం_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)దత్తాంశం;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    ఒకవేళ (state->deferred_event_processing) {
        SDL_Video_దత్తాంశం *vid = SDL_GetVideoDevice()->అంతర్గత;
        state->వరుస = Wayland_Display_Create_వరుస(vid->display, "SDL Color Management Queue");

        నిర్మాణం wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_సమితి_వరుస(image_desc_wrapper, state->వరుస);
        state->wp_image_description_info = wp_image_description_v1_get_information((నిర్మాణం wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } లేకపోతే {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_కూడు_listener(state->wp_image_description_info, &image_description_info_listener, దత్తాంశం);

    ఒకవేళ (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

స్థిర శూన్య image_description_handle_ready(శూన్య *దత్తాంశం,
                                           నిర్మాణం wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t తటస్థం)
{
    image_description_handle_ready2(దత్తాంశం, wp_image_description_v1, 0, తటస్థం);
}

స్థిర స్థిరరాశి నిర్మాణం wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

శూన్య Wayland_Get_Color_Info_For_కిటికీ(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(కిటికీ_దత్తాంశం_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, పరిమాణం(Wayland_ColorInfoState));

    ఒకవేళ (state) {
        కిటికీ_దత్తాంశం_2->color_info_state = state;
        state->కిటికీ_దత్తాంశం_2 = కిటికీ_దత్తాంశం_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_కిటికీ;
        state->deferred_event_processing = defer_event_processing;

        ఒకవేళ (!defer_event_processing) {
            state->వరుస = Wayland_Display_Create_వరుస(కిటికీ_దత్తాంశం_2->wayland_దత్తాంశం->display, "SDL Color Management Queue");

            నిర్మాణం wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(కిటికీ_దత్తాంశం_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_సమితి_వరుస(surface_feedback_wrapper, state->వరుస);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((నిర్మాణం wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } లేకపోతే {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(కిటికీ_దత్తాంశం_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_కూడు_listener(state->wp_image_description, &image_description_listener, state);

        ఒకవేళ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

శూన్య Wayland_GetColorInfoForOutput(SDL_Display_దత్తాంశం *display_దత్తాంశం, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_దత్తాంశం->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, పరిమాణం(Wayland_ColorInfoState));

    ఒకవేళ (state) {
        display_దత్తాంశం->color_info_state = state;
        state->display_దత్తాంశం = display_దత్తాంశం;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        ఒకవేళ (!defer_event_processing) {
            state->వరుస = Wayland_Display_Create_వరుస(display_దత్తాంశం->videodata->display, "SDL Color Management Queue");

            నిర్మాణం wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_దత్తాంశం->wp_color_management_output);
            WAYLAND_wl_proxy_సమితి_వరుస(output_feedback_wrapper, state->వరుస);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((నిర్మాణం wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } లేకపోతే {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_దత్తాంశం->wp_color_management_output);
        }
        wp_image_description_v1_కూడు_listener(state->wp_image_description, &image_description_listener, state);

        ఒకవేళ (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
