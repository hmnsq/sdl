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

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "SDL_waylandcolor.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandwindow.h"
#समावेश "color-management-v1-client-protocol.h"
#समावेश "../../events/SDL_windowevents_c.h"

प्रकार काष्ठा Wayland_ColorInfoState
{
    काष्ठा wp_image_description_v1 *wp_image_description;
    काष्ठा wp_image_description_info_v1 *wp_image_description_info;
    काष्ठा wl_event_queue *queue;

    जोड़
    {
        SDL_Window_तथ्य *window_तथ्य_2;
        SDL_Display_तथ्य *display_तथ्य;
    };

    क्रमागत
    {
        WAYLAND_COLOR_OBJECT_TYPE_WINDOW,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    पूर्णांक icc_fd;
    Uint32 icc_आकार;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

अटल व्योम Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    अगर (state) {
        अगर (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = शून्य;
        }
        अगर (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = शून्य;
        }
    }
}

व्योम Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    अगर (state) {
        Wayland_CancelColorInfoRequest(state);
        अगर (state->queue) {
            WAYLAND_wl_event_queue_destroy(state->queue);
        }

        चयन (state->object_type) {
        हाल WAYLAND_COLOR_OBJECT_TYPE_WINDOW:
            state->window_तथ्य_2->color_info_state = शून्य;
            अवरोध;
        हाल WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_तथ्य->color_info_state = शून्य;
            अवरोध;
        }

        SDL_free(state);
    }
}

अटल व्योम image_description_info_handle_done(व्योम *तथ्य,
                                               काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)तथ्य;
    Wayland_CancelColorInfoRequest(state);

    चयन (state->object_type) {
        हाल WAYLAND_COLOR_OBJECT_TYPE_WINDOW:
        {
            SDL_SetWindowHDRProperties(state->window_तथ्य_2->sdlwindow, &state->HDR, true);
            अगर (state->icc_आकार) {
                state->window_तथ्य_2->icc_fd = state->icc_fd;
                state->window_तथ्य_2->icc_आकार = state->icc_आकार;
                SDL_SendWindowEvent(state->window_तथ्य_2->sdlwindow, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
            }
        } अवरोध;
        हाल WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_तथ्य->HDR, &state->HDR);

            अगर (state->display_तथ्य->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_तथ्य->display);
                अगर (disp) {
                    SDL_SetDisplayHDRProperties(disp, &state->HDR);
                }
            } अन्यथा {
                SDL_copyp(&state->display_तथ्य->placeholder.HDR, &state->HDR);
            }
        } अवरोध;
    }
}

अटल व्योम image_description_info_handle_icc_file(व्योम *तथ्य,
                                                   काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_आकार)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)तथ्य;

    state->icc_fd = icc;
    state->icc_आकार = icc_आकार;
}

अटल व्योम image_description_info_handle_primaries(व्योम *तथ्य,
                                                    काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

अटल व्योम image_description_info_handle_primaries_named(व्योम *तथ्य,
                                                          काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

अटल व्योम image_description_info_handle_tf_power(व्योम *तथ्य,
                                                   काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

अटल व्योम image_description_info_handle_tf_named(व्योम *तथ्य,
                                                   काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

अटल व्योम image_description_info_handle_luminances(व्योम *तथ्य,
                                                     काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)तथ्य;
    अगर (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (भग्न)max_lum / (भग्न)reference_lum;
    } अन्यथा {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

अटल व्योम image_description_info_handle_target_primaries(व्योम *तथ्य,
                                                           काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

अटल व्योम image_description_info_handle_target_luminance(व्योम *तथ्य,
                                                           काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

अटल व्योम image_description_info_handle_target_max_cll(व्योम *तथ्य,
                                                         काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

अटल व्योम image_description_info_handle_target_max_fall(व्योम *तथ्य,
                                                          काष्ठा wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

अटल स्थिर काष्ठा wp_image_description_info_v1_listener image_description_info_listener = {
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

अटल व्योम PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_तथ्य *vid = SDL_GetVideoDevice()->internal;

    // Run the image description sequence to completion in its own queue.
    जबतक (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_queue(vid->display, state->queue);
    }

    Wayland_FreeColorInfoState(state);
}

अटल व्योम image_description_handle_failed(व्योम *तथ्य,
                                            काष्ठा wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            स्थिर अक्षर *संदेश)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)तथ्य;
    Wayland_CancelColorInfoRequest(state);

    अगर (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

अटल व्योम image_description_handle_ready2(व्योम *तथ्य,
                                            काष्ठा wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t identity_hi, uint32_t identity_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)तथ्य;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    अगर (state->deferred_event_processing) {
        SDL_Video_तथ्य *vid = SDL_GetVideoDevice()->internal;
        state->queue = Wayland_DisplayCreateQueue(vid->display, "SDL Color Management Queue");

        काष्ठा wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_set_queue(image_desc_wrapper, state->queue);
        state->wp_image_description_info = wp_image_description_v1_get_information((काष्ठा wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } अन्यथा {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_add_listener(state->wp_image_description_info, &image_description_info_listener, तथ्य);

    अगर (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

अटल व्योम image_description_handle_ready(व्योम *तथ्य,
                                           काष्ठा wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t identity)
{
    image_description_handle_ready2(तथ्य, wp_image_description_v1, 0, identity);
}

अटल स्थिर काष्ठा wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

व्योम Wayland_GetColorInfoForWindow(SDL_Window_तथ्य *window_तथ्य_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(window_तथ्य_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, माप(Wayland_ColorInfoState));

    अगर (state) {
        window_तथ्य_2->color_info_state = state;
        state->window_तथ्य_2 = window_तथ्य_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_WINDOW;
        state->deferred_event_processing = defer_event_processing;

        अगर (!defer_event_processing) {
            state->queue = Wayland_DisplayCreateQueue(window_तथ्य_2->wayland_तथ्य->display, "SDL Color Management Queue");

            काष्ठा wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(window_तथ्य_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_set_queue(surface_feedback_wrapper, state->queue);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((काष्ठा wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } अन्यथा {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(window_तथ्य_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_add_listener(state->wp_image_description, &image_description_listener, state);

        अगर (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

व्योम Wayland_GetColorInfoForOutput(SDL_Display_तथ्य *display_तथ्य, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_तथ्य->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, माप(Wayland_ColorInfoState));

    अगर (state) {
        display_तथ्य->color_info_state = state;
        state->display_तथ्य = display_तथ्य;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        अगर (!defer_event_processing) {
            state->queue = Wayland_DisplayCreateQueue(display_तथ्य->videodata->display, "SDL Color Management Queue");

            काष्ठा wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_तथ्य->wp_color_management_output);
            WAYLAND_wl_proxy_set_queue(output_feedback_wrapper, state->queue);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((काष्ठा wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } अन्यथा {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_तथ्य->wp_color_management_output);
        }
        wp_image_description_v1_add_listener(state->wp_image_description, &image_description_listener, state);

        अगर (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
