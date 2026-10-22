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

#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylandcolor.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "color-management-v1-client-protocol.h"
#ضمن "../../events/SDL_windowevents_c.h"

تعريفنوع بنية Wayland_ColorInfoState
{
    بنية wp_image_description_v1 *wp_image_description;
    بنية wp_image_description_info_v1 *wp_image_description_info;
    بنية wl_event_قطار *قطار;

    اتحاد
    {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2;
        SDL_Display_انکڑے *display_انکڑے;
    };

    تعداد
    {
        WAYLAND_COLOR_OBJECT_TYPE_کھڑکی,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    صحيح icc_fd;
    Uint32 icc_ناپ;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

ساكن فراغ Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    إذا (state) {
        إذا (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = عدم;
        }
        إذا (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = عدم;
        }
    }
}

فراغ Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    إذا (state) {
        Wayland_CancelColorInfoRequest(state);
        إذا (state->قطار) {
            WAYLAND_wl_event_قطار_destroy(state->قطار);
        }

        بدل (state->object_type) {
        حالة WAYLAND_COLOR_OBJECT_TYPE_کھڑکی:
            state->کھڑکی_انکڑے_2->color_info_state = عدم;
            اكسر;
        حالة WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_انکڑے->color_info_state = عدم;
            اكسر;
        }

        SDL_free(state);
    }
}

ساكن فراغ image_description_info_handle_پورا(فراغ *انکڑے,
                                               بنية wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)انکڑے;
    Wayland_CancelColorInfoRequest(state);

    بدل (state->object_type) {
        حالة WAYLAND_COLOR_OBJECT_TYPE_کھڑکی:
        {
            SDL_سیٹ_کھڑکی_HDRProperties(state->کھڑکی_انکڑے_2->sdlwindow, &state->HDR, true);
            إذا (state->icc_ناپ) {
                state->کھڑکی_انکڑے_2->icc_fd = state->icc_fd;
                state->کھڑکی_انکڑے_2->icc_ناپ = state->icc_ناپ;
                SDL_Send_کھڑکی_Event(state->کھڑکی_انکڑے_2->sdlwindow, SDL_EVENT_کھڑکی_ICCPROF_بدلیا, 0, 0);
            }
        } اكسر;
        حالة WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_انکڑے->HDR, &state->HDR);

            إذا (state->display_انکڑے->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_انکڑے->display);
                إذا (disp) {
                    SDL_سیٹ_Display_HDRProperties(disp, &state->HDR);
                }
            } وإلا {
                SDL_copyp(&state->display_انکڑے->placeholder.HDR, &state->HDR);
            }
        } اكسر;
    }
}

ساكن فراغ image_description_info_handle_icc_file(فراغ *انکڑے,
                                                   بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_ناپ)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)انکڑے;

    state->icc_fd = icc;
    state->icc_ناپ = icc_ناپ;
}

ساكن فراغ image_description_info_handle_primaries(فراغ *انکڑے,
                                                    بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

ساكن فراغ image_description_info_handle_primaries_named(فراغ *انکڑے,
                                                          بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

ساكن فراغ image_description_info_handle_tf_power(فراغ *انکڑے,
                                                   بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

ساكن فراغ image_description_info_handle_tf_named(فراغ *انکڑے,
                                                   بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

ساكن فراغ image_description_info_handle_luminances(فراغ *انکڑے,
                                                     بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)انکڑے;
    إذا (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (عائم)max_lum / (عائم)reference_lum;
    } وإلا {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

ساكن فراغ image_description_info_handle_نشانہ_primaries(فراغ *انکڑے,
                                                           بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

ساكن فراغ image_description_info_handle_نشانہ_luminance(فراغ *انکڑے,
                                                           بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

ساكن فراغ image_description_info_handle_نشانہ_max_cll(فراغ *انکڑے,
                                                         بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

ساكن فراغ image_description_info_handle_نشانہ_max_fall(فراغ *انکڑے,
                                                          بنية wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

ساكن ثابت بنية wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_پورا,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_نشانہ_primaries,
    image_description_info_handle_نشانہ_luminance,
    image_description_info_handle_نشانہ_max_cll,
    image_description_info_handle_نشانہ_max_fall
};

ساكن فراغ PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_انکڑے *vid = SDL_GetVideoDevice()->اندرونی;

    // Run the image description sequence to completion in its own queue.
    طالما (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_قطار(vid->display, state->قطار);
    }

    Wayland_FreeColorInfoState(state);
}

ساكن فراغ image_description_handle_failed(فراغ *انکڑے,
                                            بنية wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            ثابت حرف *پیغام)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)انکڑے;
    Wayland_CancelColorInfoRequest(state);

    إذا (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

ساكن فراغ image_description_handle_ready2(فراغ *انکڑے,
                                            بنية wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t پچھان_تت_hi, uint32_t پچھان_تت_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)انکڑے;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    إذا (state->deferred_event_processing) {
        SDL_Video_انکڑے *vid = SDL_GetVideoDevice()->اندرونی;
        state->قطار = Wayland_Display_Create_قطار(vid->display, "SDL Color Management Queue");

        بنية wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_سیٹ_قطار(image_desc_wrapper, state->قطار);
        state->wp_image_description_info = wp_image_description_v1_get_information((بنية wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } وإلا {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_جوڑو_listener(state->wp_image_description_info, &image_description_info_listener, انکڑے);

    إذا (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

ساكن فراغ image_description_handle_ready(فراغ *انکڑے,
                                           بنية wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t پچھان_تت)
{
    image_description_handle_ready2(انکڑے, wp_image_description_v1, 0, پچھان_تت);
}

ساكن ثابت بنية wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

فراغ Wayland_Get_Color_Info_For_کھڑکی(SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(کھڑکی_انکڑے_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, حجم(Wayland_ColorInfoState));

    إذا (state) {
        کھڑکی_انکڑے_2->color_info_state = state;
        state->کھڑکی_انکڑے_2 = کھڑکی_انکڑے_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_کھڑکی;
        state->deferred_event_processing = defer_event_processing;

        إذا (!defer_event_processing) {
            state->قطار = Wayland_Display_Create_قطار(کھڑکی_انکڑے_2->wayland_انکڑے->display, "SDL Color Management Queue");

            بنية wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(کھڑکی_انکڑے_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_سیٹ_قطار(surface_feedback_wrapper, state->قطار);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((بنية wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } وإلا {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(کھڑکی_انکڑے_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_جوڑو_listener(state->wp_image_description, &image_description_listener, state);

        إذا (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

فراغ Wayland_GetColorInfoForOutput(SDL_Display_انکڑے *display_انکڑے, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_انکڑے->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, حجم(Wayland_ColorInfoState));

    إذا (state) {
        display_انکڑے->color_info_state = state;
        state->display_انکڑے = display_انکڑے;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        إذا (!defer_event_processing) {
            state->قطار = Wayland_Display_Create_قطار(display_انکڑے->videodata->display, "SDL Color Management Queue");

            بنية wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_انکڑے->wp_color_management_output);
            WAYLAND_wl_proxy_سیٹ_قطار(output_feedback_wrapper, state->قطار);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((بنية wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } وإلا {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_انکڑے->wp_color_management_output);
        }
        wp_image_description_v1_جوڑو_listener(state->wp_image_description, &image_description_listener, state);

        إذا (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND
