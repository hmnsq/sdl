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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব "SDL_waylandcolor.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandwindow.h"
#অন্তর্ভাব "color-management-v1-client-protocol.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"

প্রকারনির্দেশ সংরচনা Wayland_ColorInfoState
{
    সংরচনা wp_image_description_v1 *wp_image_description;
    সংরচনা wp_image_description_info_v1 *wp_image_description_info;
    সংরচনা wl_event_queue *queue;

    সঙ্ঘ
    {
        SDL_WindowData *window_data;
        SDL_DisplayData *display_data;
    };

    গণনা
    {
        WAYLAND_COLOR_OBJECT_TYPE_WINDOW,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    পূর্ণাঙ্ক icc_fd;
    Uint32 icc_size;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

স্থির শূন্য Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    যদি (state) {
        যদি (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = রিক্ত;
        }
        যদি (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = রিক্ত;
        }
    }
}

শূন্য Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    যদি (state) {
        Wayland_CancelColorInfoRequest(state);
        যদি (state->queue) {
            WAYLAND_wl_event_queue_destroy(state->queue);
        }

        বিকল্প (state->object_type) {
        পক্ষ WAYLAND_COLOR_OBJECT_TYPE_WINDOW:
            state->window_data->color_info_state = রিক্ত;
            ভঙ্গ;
        পক্ষ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_data->color_info_state = রিক্ত;
            ভঙ্গ;
        }

        SDL_free(state);
    }
}

স্থির শূন্য image_description_info_handle_done(শূন্য *data,
                                               সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)data;
    Wayland_CancelColorInfoRequest(state);

    বিকল্প (state->object_type) {
        পক্ষ WAYLAND_COLOR_OBJECT_TYPE_WINDOW:
        {
            SDL_SetWindowHDRProperties(state->window_data->sdlwindow, &state->HDR, true);
            যদি (state->icc_size) {
                state->window_data->icc_fd = state->icc_fd;
                state->window_data->icc_size = state->icc_size;
                SDL_SendWindowEvent(state->window_data->sdlwindow, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
            }
        } ভঙ্গ;
        পক্ষ WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_data->HDR, &state->HDR);

            যদি (state->display_data->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_data->display);
                যদি (disp) {
                    SDL_SetDisplayHDRProperties(disp, &state->HDR);
                }
            } অন্যথা {
                SDL_copyp(&state->display_data->placeholder.HDR, &state->HDR);
            }
        } ভঙ্গ;
    }
}

স্থির শূন্য image_description_info_handle_icc_file(শূন্য *data,
                                                   সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_size)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)data;

    state->icc_fd = icc;
    state->icc_size = icc_size;
}

স্থির শূন্য image_description_info_handle_primaries(শূন্য *data,
                                                    সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_primaries_named(শূন্য *data,
                                                          সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_tf_power(শূন্য *data,
                                                   সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_tf_named(শূন্য *data,
                                                   সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_luminances(শূন্য *data,
                                                     সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)data;
    যদি (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (ভিন্ন)max_lum / (ভিন্ন)reference_lum;
    } অন্যথা {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

স্থির শূন্য image_description_info_handle_target_primaries(শূন্য *data,
                                                           সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_target_luminance(শূন্য *data,
                                                           সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_target_max_cll(শূন্য *data,
                                                         সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

স্থির শূন্য image_description_info_handle_target_max_fall(শূন্য *data,
                                                          সংরচনা wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

স্থির ধ্রুব সংরচনা wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_done,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_target_primaries,
    image_description_info_handle_target_luminance,
    image_description_info_handle_target_max_cll,
    image_description_info_handle_target_max_fall
};

স্থির শূন্য PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_VideoData *vid = SDL_GetVideoDevice()->internal;

    // Run the image description sequence to completion in its own queue.
    যাবত্ (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_queue(vid->display, state->queue);
    }

    Wayland_FreeColorInfoState(state);
}

স্থির শূন্য image_description_handle_failed(শূন্য *data,
                                            সংরচনা wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            ধ্রুব বর্ণ *বার্তা)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)data;
    Wayland_CancelColorInfoRequest(state);

    যদি (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

স্থির শূন্য image_description_handle_ready2(শূন্য *data,
                                            সংরচনা wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t identity_hi, uint32_t identity_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)data;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    যদি (state->deferred_event_processing) {
        SDL_VideoData *vid = SDL_GetVideoDevice()->internal;
        state->queue = Wayland_DisplayCreateQueue(vid->display, "SDL Color Management Queue");

        সংরচনা wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_set_queue(image_desc_wrapper, state->queue);
        state->wp_image_description_info = wp_image_description_v1_get_information((সংরচনা wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } অন্যথা {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_add_listener(state->wp_image_description_info, &image_description_info_listener, data);

    যদি (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

স্থির শূন্য image_description_handle_ready(শূন্য *data,
                                           সংরচনা wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t identity)
{
    image_description_handle_ready2(data, wp_image_description_v1, 0, identity);
}

স্থির ধ্রুব সংরচনা wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

শূন্য Wayland_GetColorInfoForWindow(SDL_WindowData *window_data, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(window_data->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, পরিমাণ(Wayland_ColorInfoState));

    যদি (state) {
        window_data->color_info_state = state;
        state->window_data = window_data;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_WINDOW;
        state->deferred_event_processing = defer_event_processing;

        যদি (!defer_event_processing) {
            state->queue = Wayland_DisplayCreateQueue(window_data->waylandData->display, "SDL Color Management Queue");

            সংরচনা wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(window_data->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_set_queue(surface_feedback_wrapper, state->queue);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((সংরচনা wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } অন্যথা {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(window_data->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_add_listener(state->wp_image_description, &image_description_listener, state);

        যদি (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

শূন্য Wayland_GetColorInfoForOutput(SDL_DisplayData *display_data, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_data->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, পরিমাণ(Wayland_ColorInfoState));

    যদি (state) {
        display_data->color_info_state = state;
        state->display_data = display_data;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        যদি (!defer_event_processing) {
            state->queue = Wayland_DisplayCreateQueue(display_data->videodata->display, "SDL Color Management Queue");

            সংরচনা wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_data->wp_color_management_output);
            WAYLAND_wl_proxy_set_queue(output_feedback_wrapper, state->queue);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((সংরচনা wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } অন্যথা {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_data->wp_color_management_output);
        }
        wp_image_description_v1_add_listener(state->wp_image_description, &image_description_listener, state);

        যদি (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
