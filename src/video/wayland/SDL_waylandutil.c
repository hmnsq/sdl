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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandutil.h"
#ضمن "xdg-activation-v1-client-protocol.h"

#ضمن "../../notification/SDL_notification_c.h"

#define WAYLAND_HANDLE_PREFIX "wayland:"

تعريفنوع بنية Wayland_ActivationParams
{
    حرف **token;
    bool done;
} Wayland_ActivationParams;

ساكن فراغ handle_xdg_activation_done(فراغ *data, بنية xdg_activation_token_v1 *xdg_activation_token_v1, ثابت حرف *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)data;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, حرف **token, حرف **window_id)
{
    𐤀𐤌 (!_this || !token) {
        أرجع false;
    }

    SDL_VideoData *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_WindowData *focus = عدم;

    𐤀𐤌 (seat) {
        focus = seat->keyboard.focus;
        𐤀𐤌 (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ثابت حرف *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    𐤀𐤌 (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    𐤀𐤌 (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        𐤀𐤌 (!*token) {
            أرجع false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } وإلا 𐤀𐤌 (viddata->activation_manager) {
        بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        بنية wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        بنية wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        بنية xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((بنية xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_add_listener(activation_token, &xdg_activation_listener, &params);

        𐤀𐤌 (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(activation_token, requesting_surface);
        }
        𐤀𐤌 (seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        𐤀𐤌 (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_set_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        طالما (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        𐤀𐤌 (!*token) {
            أرجع false;
        }
    }

    𐤀𐤌 (focus && window_id) {
        ثابت حرف *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
        𐤀𐤌 (id) {
            ثابت size_t len = SDL_strlen(id) + حجم(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            𐤀𐤌 (!*window_id) {
                SDL_free(*token);
                *token = عدم;
                أرجع false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
