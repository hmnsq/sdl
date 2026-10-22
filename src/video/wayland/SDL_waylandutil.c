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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandutil.h"
#ضمن "xdg-activation-v1-client-protocol.h"

#ضمن "../../notification/SDL_notification_c.h"

#تعریف_کړه WAYLAND_HANDLE_مختاړی "wayland:"

تعريفنوع بنية Wayland_ActivationParams
{
    حرف **token;
    bool بشپړ;
} Wayland_ActivationParams;

ساكن فراغ handle_xdg_activation_بشپړ(فراغ *معلومات, بنية xdg_activation_token_v1 *xdg_activation_token_v1, ثابت حرف *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)معلومات;
    *activation_params->token = SDL_strdup(token);
    activation_params->بشپړ = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_بشپړ
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, حرف **token, حرف **کړکۍ_id)
{
    إذا (!_this || !token) {
        أرجع false;
    }

    SDL_Video_معلومات *viddata = _this->دننی;

    SDL_WaylandSeat *seat = viddata->وروستی_implicit_grab_seat;
    SDL_کړکۍ_معلومات *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشاره_ګر_2.focus;
        }
    }

    ثابت حرف *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    إذا (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    إذا (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        إذا (!*token) {
            أرجع false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } وإلا إذا (viddata->activation_manager) {
        بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;
        Wayland_ActivationParams params = {
            .token = token,
            .بشپړ = false
        };

        بنية wl_event_کتار *activation_token_کتار = Wayland_Display_Create_کتار(viddata->display, "SDL Activation Token Generation Queue");

        بنية wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_سېټ_کتار(activation_manager_wrapper, activation_token_کتار);
        بنية xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((بنية xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_جمع_کړه_listener(activation_token, &xdg_activation_listener, &params);

        إذا (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_سېټ_surface(activation_token, requesting_surface);
        }
        إذا (seat && seat->wl_seat) {
            xdg_activation_token_v1_سېټ_serial(activation_token, seat->وروستی_implicit_grab_serial, seat->wl_seat);
        }
        إذا (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_سېټ_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        طالما (!params.بشپړ) {
            WAYLAND_wl_display_dispatch_کتار(viddata->display, activation_token_کتار);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_کتار_destroy(activation_token_کتار);

        إذا (!*token) {
            أرجع false;
        }
    }

    إذا (focus && کړکۍ_id) {
        ثابت حرف *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
        إذا (id) {
            ثابت size_t len = SDL_strlen(id) + حجم(WAYLAND_HANDLE_مختاړی) + 1;
            *کړکۍ_id = SDL_malloc(len);
            إذا (!*کړکۍ_id) {
                SDL_free(*token);
                *token = عدم;
                أرجع false;
            }

            SDL_strlcpy(*کړکۍ_id, WAYLAND_HANDLE_مختاړی, len);
            SDL_strlcat(*کړکۍ_id, id, len);
        }
    }

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND
