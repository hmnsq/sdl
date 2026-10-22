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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandutil.h"
#شامل "xdg-activation-v1-client-protocol.h"

#شامل "../../notification/SDL_notification_c.h"

#define WAYLAND_HANDLE_PREFIX "wayland:"

تعریفنوع ساختار Wayland_ActivationParams
{
    نویسه **token;
    bool done;
} Wayland_ActivationParams;

ایستا تهی handle_xdg_activation_done(تهی *data, ساختار xdg_activation_token_v1 *xdg_activation_token_v1, ثابت نویسه *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)data;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ایستا ثابت ساختار xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, نویسه **token, نویسه **window_id)
{
    اگر (!_this || !token) {
        بازگشت false;
    }

    SDL_VideoData *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_WindowData *focus = پوچ;

    اگر (seat) {
        focus = seat->keyboard.focus;
        اگر (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ثابت نویسه *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    اگر (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    اگر (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        اگر (!*token) {
            بازگشت false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } وگرنه اگر (viddata->activation_manager) {
        ساختار wl_surface *requesting_surface = focus ? focus->surface : پوچ;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        ساختار wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        ساختار wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        ساختار xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((ساختار xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_add_listener(activation_token, &xdg_activation_listener, &params);

        اگر (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(activation_token, requesting_surface);
        }
        اگر (seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        اگر (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_set_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        وقتی (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        اگر (!*token) {
            بازگشت false;
        }
    }

    اگر (focus && window_id) {
        ثابت نویسه *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, پوچ);
        اگر (id) {
            ثابت size_t len = SDL_strlen(id) + اندازه(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            اگر (!*window_id) {
                SDL_free(*token);
                *token = پوچ;
                بازگشت false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    بازگشت true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
