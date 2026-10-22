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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-activation-v1-client-protocol.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../notification/SDL_notification_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_HANDLE_ਅਗੇਤਰ "wayland:"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_ActivationParams
{
    ਅੱਖਰ **token;
    bool ਪੂਰਾ;
} Wayland_ActivationParams;

ਸਥਿਰ ਖਾਲੀ handle_xdg_activation_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_activation_token_v1 *xdg_activation_token_v1, ਅਚਲ ਅੱਖਰ *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)ਅੰਕੜੇ;
    *activation_params->token = SDL_strdup(token);
    activation_params->ਪੂਰਾ = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_ਪੂਰਾ
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, ਅੱਖਰ **token, ਅੱਖਰ **ਖਿੜਕੀ_id)
{
    ਜੇ (!_this || !token) {
        ਵਾਪਸ false;
    }

    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;

    SDL_WaylandSeat *seat = viddata->ਆਖਰੀ_implicit_grab_seat;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus = ਨਿਰਾ;

    ਜੇ (seat) {
        focus = seat->keyboard.focus;
        ਜੇ (!focus) {
            focus = seat->ਸੂਚਕ_2.focus;
        }
    }

    ਅਚਲ ਅੱਖਰ *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    ਜੇ (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    ਜੇ (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        ਜੇ (!*token) {
            ਵਾਪਸ false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } ਨਹੀਂਤਾਂ ਜੇ (viddata->activation_manager) {
        ਬਣਤਰ wl_surface *requesting_surface = focus ? focus->surface : ਨਿਰਾ;
        Wayland_ActivationParams params = {
            .token = token,
            .ਪੂਰਾ = false
        };

        ਬਣਤਰ wl_event_ਕਤਾਰ *activation_token_ਕਤਾਰ = Wayland_Display_Create_ਕਤਾਰ(viddata->display, "SDL Activation Token Generation Queue");

        ਬਣਤਰ wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ(activation_manager_wrapper, activation_token_ਕਤਾਰ);
        ਬਣਤਰ xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((ਬਣਤਰ xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_ਜੋੜੋ_listener(activation_token, &xdg_activation_listener, &params);

        ਜੇ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_ਸੈੱਟ_surface(activation_token, requesting_surface);
        }
        ਜੇ (seat && seat->wl_seat) {
            xdg_activation_token_v1_ਸੈੱਟ_serial(activation_token, seat->ਆਖਰੀ_implicit_grab_serial, seat->wl_seat);
        }
        ਜੇ (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_ਸੈੱਟ_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        ਜਦੋਂ (!params.ਪੂਰਾ) {
            WAYLAND_wl_display_dispatch_ਕਤਾਰ(viddata->display, activation_token_ਕਤਾਰ);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_ਕਤਾਰ_destroy(activation_token_ਕਤਾਰ);

        ਜੇ (!*token) {
            ਵਾਪਸ false;
        }
    }

    ਜੇ (focus && ਖਿੜਕੀ_id) {
        ਅਚਲ ਅੱਖਰ *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ਨਿਰਾ);
        ਜੇ (id) {
            ਅਚਲ size_t len = SDL_strlen(id) + ਆਕਾਰ(WAYLAND_HANDLE_ਅਗੇਤਰ) + 1;
            *ਖਿੜਕੀ_id = SDL_malloc(len);
            ਜੇ (!*ਖਿੜਕੀ_id) {
                SDL_free(*token);
                *token = ਨਿਰਾ;
                ਵਾਪਸ false;
            }

            SDL_strlcpy(*ਖਿੜਕੀ_id, WAYLAND_HANDLE_ਅਗੇਤਰ, len);
            SDL_strlcat(*ਖਿੜਕੀ_id, id, len);
        }
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
