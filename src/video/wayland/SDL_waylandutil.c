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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandutil.h"
#ಅನ್ತರ್ಭಾವ "xdg-activation-v1-client-protocol.h"

#ಅನ್ತರ್ಭಾವ "../../notification/SDL_notification_c.h"

#define WAYLAND_HANDLE_PREFIX "wayland:"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_ActivationParams
{
    ವರ್ಣ **token;
    bool done;
} Wayland_ActivationParams;

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_activation_done(ಶೂನ್ಯ *data, ಸಂರಚನಾ xdg_activation_token_v1 *xdg_activation_token_v1, ಧ್ರುವ ವರ್ಣ *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)data;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, ವರ್ಣ **token, ವರ್ಣ **window_id)
{
    ಯದಿ (!_this || !token) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_VideoData *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_WindowData *focus = ರಿಕ್ತ;

    ಯದಿ (seat) {
        focus = seat->keyboard.focus;
        ಯದಿ (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ಧ್ರುವ ವರ್ಣ *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    ಯದಿ (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    ಯದಿ (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        ಯದಿ (!*token) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } ಅನ್ಯಥಾ ಯದಿ (viddata->activation_manager) {
        ಸಂರಚನಾ wl_surface *requesting_surface = focus ? focus->surface : ರಿಕ್ತ;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        ಸಂರಚನಾ wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        ಸಂರಚನಾ wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        ಸಂರಚನಾ xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((ಸಂರಚನಾ xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_add_listener(activation_token, &xdg_activation_listener, &params);

        ಯದಿ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(activation_token, requesting_surface);
        }
        ಯದಿ (seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        ಯದಿ (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_set_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        ಯಾವತ್ (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        ಯದಿ (!*token) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಯದಿ (focus && window_id) {
        ಧ್ರುವ ವರ್ಣ *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ರಿಕ್ತ);
        ಯದಿ (id) {
            ಧ್ರುವ size_t len = SDL_strlen(id) + ಪರಿಮಾಣ(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            ಯದಿ (!*window_id) {
                SDL_free(*token);
                *token = ರಿಕ್ತ;
                ಪ್ರತ್ಯಾಗಮ false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
