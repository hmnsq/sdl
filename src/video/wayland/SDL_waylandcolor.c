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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "SDL_waylandcolor.h"
#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"
#شامل "color-management-v1-client-protocol.h"
#شامل "../../events/SDL_windowevents_c.h"

قسمتعریف ساخت Wayland_ColorInfoState
{
    ساخت wp_image_description_v1 *wp_image_description;
    ساخت wp_image_description_info_v1 *wp_image_description_info;
    ساخت wl_event_قطار *قطار;

    اتحاد
    {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2;
        SDL_Display_ڈیٹا *display_ڈیٹا;
    };

    شمار
    {
        WAYLAND_COLOR_OBJECT_TYPE_کھڑکی,
        WAYLAND_COLOR_OBJECT_TYPE_DISPLAY
    } object_type;

    SDL_HDROutputProperties HDR;

    // The ICC fd is only valid if the size is non-zero.
    صحیح icc_fd;
    Uint32 icc_سائز;

    bool deferred_event_processing;
} Wayland_ColorInfoState;

ساکن خالی Wayland_CancelColorInfoRequest(Wayland_ColorInfoState *state)
{
    اگر (state) {
        اگر (state->wp_image_description_info) {
            wp_image_description_info_v1_destroy(state->wp_image_description_info);
            state->wp_image_description_info = تہی;
        }
        اگر (state->wp_image_description) {
            wp_image_description_v1_destroy(state->wp_image_description);
            state->wp_image_description = تہی;
        }
    }
}

خالی Wayland_FreeColorInfoState(Wayland_ColorInfoState *state)
{
    اگر (state) {
        Wayland_CancelColorInfoRequest(state);
        اگر (state->قطار) {
            WAYLAND_wl_event_قطار_destroy(state->قطار);
        }

        انتخاب (state->object_type) {
        حالت WAYLAND_COLOR_OBJECT_TYPE_کھڑکی:
            state->کھڑکی_ڈیٹا_2->color_info_state = تہی;
            توڑو;
        حالت WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
            state->display_ڈیٹا->color_info_state = تہی;
            توڑو;
        }

        SDL_free(state);
    }
}

ساکن خالی image_description_info_handle_مکمل(خالی *ڈیٹا,
                                               ساخت wp_image_description_info_v1 *wp_image_description_info_v1)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ڈیٹا;
    Wayland_CancelColorInfoRequest(state);

    انتخاب (state->object_type) {
        حالت WAYLAND_COLOR_OBJECT_TYPE_کھڑکی:
        {
            SDL_سیٹ_کھڑکی_HDRProperties(state->کھڑکی_ڈیٹا_2->sdlwindow, &state->HDR, true);
            اگر (state->icc_سائز) {
                state->کھڑکی_ڈیٹا_2->icc_fd = state->icc_fd;
                state->کھڑکی_ڈیٹا_2->icc_سائز = state->icc_سائز;
                SDL_Send_کھڑکی_Event(state->کھڑکی_ڈیٹا_2->sdlwindow, SDL_EVENT_کھڑکی_ICCPROF_بدلا, 0, 0);
            }
        } توڑو;
        حالت WAYLAND_COLOR_OBJECT_TYPE_DISPLAY:
        {
            SDL_copyp(&state->display_ڈیٹا->HDR, &state->HDR);

            اگر (state->display_ڈیٹا->display) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(state->display_ڈیٹا->display);
                اگر (disp) {
                    SDL_سیٹ_Display_HDRProperties(disp, &state->HDR);
                }
            } ورنہ {
                SDL_copyp(&state->display_ڈیٹا->placeholder.HDR, &state->HDR);
            }
        } توڑو;
    }
}

ساکن خالی image_description_info_handle_icc_file(خالی *ڈیٹا,
                                                   ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   int32_t icc, uint32_t icc_سائز)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ڈیٹا;

    state->icc_fd = icc;
    state->icc_سائز = icc_سائز;
}

ساکن خالی image_description_info_handle_primaries(خالی *ڈیٹا,
                                                    ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                    int32_t r_x, int32_t r_y,
                                                    int32_t g_x, int32_t g_y,
                                                    int32_t b_x, int32_t b_y,
                                                    int32_t w_x, int32_t w_y)
{
    // NOP
}

ساکن خالی image_description_info_handle_primaries_named(خالی *ڈیٹا,
                                                          ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t primaries)
{
    // NOP
}

ساکن خالی image_description_info_handle_tf_power(خالی *ڈیٹا,
                                                   ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t eexp)
{
    // NOP
}

ساکن خالی image_description_info_handle_tf_named(خالی *ڈیٹا,
                                                   ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                   uint32_t tf)
{
    // NOP
}

ساکن خالی image_description_info_handle_luminances(خالی *ڈیٹا,
                                                     ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                     uint32_t min_lum,
                                                     uint32_t max_lum,
                                                     uint32_t reference_lum)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ڈیٹا;
    اگر (max_lum > reference_lum && reference_lum > 0) {
        state->HDR.HDR_headroom = (اعشاری)max_lum / (اعشاری)reference_lum;
    } ورنہ {
        state->HDR.HDR_headroom = 1.0f;
    }
    state->HDR.SDR_white_level = 1.0f;
}

ساکن خالی image_description_info_handle_ہدف_primaries(خالی *ڈیٹا,
                                                           ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           int32_t r_x, int32_t r_y,
                                                           int32_t g_x, int32_t g_y,
                                                           int32_t b_x, int32_t b_y,
                                                           int32_t w_x, int32_t w_y)
{
    // NOP
}

ساکن خالی image_description_info_handle_ہدف_luminance(خالی *ڈیٹا,
                                                           ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                           uint32_t min_lum,
                                                           uint32_t max_lum)
{
    // NOP
}

ساکن خالی image_description_info_handle_ہدف_max_cll(خالی *ڈیٹا,
                                                         ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                         uint32_t max_cll)
{
    // NOP
}

ساکن خالی image_description_info_handle_ہدف_max_fall(خالی *ڈیٹا,
                                                          ساخت wp_image_description_info_v1 *wp_image_description_info_v1,
                                                          uint32_t max_fall)
{
    // NOP
}

ساکن ثابت ساخت wp_image_description_info_v1_listener image_description_info_listener = {
    image_description_info_handle_مکمل,
    image_description_info_handle_icc_file,
    image_description_info_handle_primaries,
    image_description_info_handle_primaries_named,
    image_description_info_handle_tf_power,
    image_description_info_handle_tf_named,
    image_description_info_handle_luminances,
    image_description_info_handle_ہدف_primaries,
    image_description_info_handle_ہدف_luminance,
    image_description_info_handle_ہدف_max_cll,
    image_description_info_handle_ہدف_max_fall
};

ساکن خالی PumpColorspaceEvents(Wayland_ColorInfoState *state)
{
    SDL_Video_ڈیٹا *vid = SDL_GetVideoDevice()->اندرونی_2;

    // Run the image description sequence to completion in its own queue.
    جب (state->wp_image_description) {
        WAYLAND_wl_display_dispatch_قطار(vid->display, state->قطار);
    }

    Wayland_FreeColorInfoState(state);
}

ساکن خالی image_description_handle_failed(خالی *ڈیٹا,
                                            ساخت wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t cause,
                                            ثابت حرف *پیغام_2)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ڈیٹا;
    Wayland_CancelColorInfoRequest(state);

    اگر (state->deferred_event_processing) {
        Wayland_FreeColorInfoState(state);
    }
}

ساکن خالی image_description_handle_ready2(خالی *ڈیٹا,
                                            ساخت wp_image_description_v1 *wp_image_description_v1,
                                            uint32_t شناختی_عنصر_hi, uint32_t شناختی_عنصر_lo)
{
    Wayland_ColorInfoState *state = (Wayland_ColorInfoState *)ڈیٹا;

    /* If event processing was deferred, then the image description is on the default queue.
     * Otherwise, it will inherit the queue from the image description object.
     */
    اگر (state->deferred_event_processing) {
        SDL_Video_ڈیٹا *vid = SDL_GetVideoDevice()->اندرونی_2;
        state->قطار = Wayland_Display_Create_قطار(vid->display, "SDL Color Management Queue");

        ساخت wl_proxy *image_desc_wrapper = WAYLAND_wl_proxy_create_wrapper(state->wp_image_description);
        WAYLAND_wl_proxy_سیٹ_قطار(image_desc_wrapper, state->قطار);
        state->wp_image_description_info = wp_image_description_v1_get_information((ساخت wp_image_description_v1 *)image_desc_wrapper);
        WAYLAND_wl_proxy_wrapper_destroy(image_desc_wrapper);
    } ورنہ {
        state->wp_image_description_info = wp_image_description_v1_get_information(state->wp_image_description);
    }
    wp_image_description_info_v1_جوڑو_listener(state->wp_image_description_info, &image_description_info_listener, ڈیٹا);

    اگر (state->deferred_event_processing) {
        PumpColorspaceEvents(state);
    }
}

ساکن خالی image_description_handle_ready(خالی *ڈیٹا,
                                           ساخت wp_image_description_v1 *wp_image_description_v1,
                                           uint32_t شناختی_عنصر)
{
    image_description_handle_ready2(ڈیٹا, wp_image_description_v1, 0, شناختی_عنصر);
}

ساکن ثابت ساخت wp_image_description_v1_listener image_description_listener = {
    image_description_handle_failed,
    image_description_handle_ready,
    image_description_handle_ready2
};

خالی Wayland_Get_Color_Info_For_کھڑکی(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(کھڑکی_ڈیٹا_2->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, حجم(Wayland_ColorInfoState));

    اگر (state) {
        کھڑکی_ڈیٹا_2->color_info_state = state;
        state->کھڑکی_ڈیٹا_2 = کھڑکی_ڈیٹا_2;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_کھڑکی;
        state->deferred_event_processing = defer_event_processing;

        اگر (!defer_event_processing) {
            state->قطار = Wayland_Display_Create_قطار(کھڑکی_ڈیٹا_2->wayland_ڈیٹا->display, "SDL Color Management Queue");

            ساخت wl_proxy *surface_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(کھڑکی_ڈیٹا_2->wp_color_management_surface_feedback);
            WAYLAND_wl_proxy_سیٹ_قطار(surface_feedback_wrapper, state->قطار);
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred((ساخت wp_color_management_surface_feedback_v1 *)surface_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(surface_feedback_wrapper);
        } ورنہ {
            state->wp_image_description = wp_color_management_surface_feedback_v1_get_preferred(کھڑکی_ڈیٹا_2->wp_color_management_surface_feedback);
        }
        wp_image_description_v1_جوڑو_listener(state->wp_image_description, &image_description_listener, state);

        اگر (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

خالی Wayland_GetColorInfoForOutput(SDL_Display_ڈیٹا *display_ڈیٹا, bool defer_event_processing)
{
    // Cancel any pending request, as it is out-of-date.
    Wayland_FreeColorInfoState(display_ڈیٹا->color_info_state);
    Wayland_ColorInfoState *state = SDL_calloc(1, حجم(Wayland_ColorInfoState));

    اگر (state) {
        display_ڈیٹا->color_info_state = state;
        state->display_ڈیٹا = display_ڈیٹا;
        state->object_type = WAYLAND_COLOR_OBJECT_TYPE_DISPLAY;
        state->deferred_event_processing = defer_event_processing;

        اگر (!defer_event_processing) {
            state->قطار = Wayland_Display_Create_قطار(display_ڈیٹا->videodata->display, "SDL Color Management Queue");

            ساخت wl_proxy *output_feedback_wrapper = WAYLAND_wl_proxy_create_wrapper(display_ڈیٹا->wp_color_management_output);
            WAYLAND_wl_proxy_سیٹ_قطار(output_feedback_wrapper, state->قطار);
            state->wp_image_description = wp_color_management_output_v1_get_image_description((ساخت wp_color_management_output_v1 *)output_feedback_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(output_feedback_wrapper);
        } ورنہ {
            state->wp_image_description = wp_color_management_output_v1_get_image_description(display_ڈیٹا->wp_color_management_output);
        }
        wp_image_description_v1_جوڑو_listener(state->wp_image_description, &image_description_listener, state);

        اگر (!defer_event_processing) {
            PumpColorspaceEvents(state);
        }
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
