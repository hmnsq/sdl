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

#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandutil.h"
#ಅನ್ತರ್ಭಾವ "xdg-activation-v1-client-protocol.h"

#ಅನ್ತರ್ಭಾವ "../../notification/SDL_notification_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_HANDLE_ಪೂರ್ವಪ್ರತ್ಯಯ "wayland:"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_ActivationParams
{
    ಅಕ್ಷರ **token;
    bool ಮುಗಿದ;
} Wayland_ActivationParams;

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_activation_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_activation_token_v1 *xdg_activation_token_v1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)ದತ್ತಾಂಶ;
    *activation_params->token = SDL_strdup(token);
    activation_params->ಮುಗಿದ = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_ಮುಗಿದ
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, ಅಕ್ಷರ **token, ಅಕ್ಷರ **ಕಿಟಕಿ_id)
{
    ಆದರೆ (!_this || !token) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;

    SDL_WaylandSeat *seat = viddata->ಕೊನೆಯ_implicit_grab_seat;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus = ಖಾಲಿ;

    ಆದರೆ (seat) {
        focus = seat->keyboard.focus;
        ಆದರೆ (!focus) {
            focus = seat->ಸೂಚಕ_2.focus;
        }
    }

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    ಆದರೆ (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    ಆದರೆ (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        ಆದರೆ (!*token) {
            ಹಿಂತಿರುಗಿ false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (viddata->activation_manager) {
        ರಚನೆ wl_surface *requesting_surface = focus ? focus->surface : ಖಾಲಿ;
        Wayland_ActivationParams params = {
            .token = token,
            .ಮುಗಿದ = false
        };

        ರಚನೆ wl_event_ಸರತಿ *activation_token_ಸರತಿ = Wayland_Display_Create_ಸರತಿ(viddata->display, "SDL Activation Token Generation Queue");

        ರಚನೆ wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_ಗಣ_ಸರತಿ(activation_manager_wrapper, activation_token_ಸರತಿ);
        ರಚನೆ xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((ರಚನೆ xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_ಕೂಡಿಸು_listener(activation_token, &xdg_activation_listener, &params);

        ಆದರೆ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_ಗಣ_surface(activation_token, requesting_surface);
        }
        ಆದರೆ (seat && seat->wl_seat) {
            xdg_activation_token_v1_ಗಣ_serial(activation_token, seat->ಕೊನೆಯ_implicit_grab_serial, seat->wl_seat);
        }
        ಆದರೆ (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_ಗಣ_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        ಆಗ (!params.ಮುಗಿದ) {
            WAYLAND_wl_display_dispatch_ಸರತಿ(viddata->display, activation_token_ಸರತಿ);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_ಸರತಿ_destroy(activation_token_ಸರತಿ);

        ಆದರೆ (!*token) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಆದರೆ (focus && ಕಿಟಕಿ_id) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ಖಾಲಿ);
        ಆದರೆ (id) {
            ಸ್ಥಿರಾಂಕ size_t len = SDL_strlen(id) + ಗಾತ್ರ(WAYLAND_HANDLE_ಪೂರ್ವಪ್ರತ್ಯಯ) + 1;
            *ಕಿಟಕಿ_id = SDL_malloc(len);
            ಆದರೆ (!*ಕಿಟಕಿ_id) {
                SDL_free(*token);
                *token = ಖಾಲಿ;
                ಹಿಂತಿರುಗಿ false;
            }

            SDL_strlcpy(*ಕಿಟಕಿ_id, WAYLAND_HANDLE_ಪೂರ್ವಪ್ರತ್ಯಯ, len);
            SDL_strlcat(*ಕಿಟಕಿ_id, id, len);
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
