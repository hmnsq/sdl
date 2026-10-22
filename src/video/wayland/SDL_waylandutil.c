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

#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandutil.h"
#شامل "xdg-activation-v1-client-protocol.h"

#شامل "../../notification/SDL_notification_c.h"

#تعریف_کرو WAYLAND_HANDLE_سابقہ "wayland:"

قسمتعریف ساخت Wayland_ActivationParams
{
    حرف **token;
    bool مکمل;
} Wayland_ActivationParams;

ساکن خالی handle_xdg_activation_مکمل(خالی *ڈیٹا, ساخت xdg_activation_token_v1 *xdg_activation_token_v1, ثابت حرف *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)ڈیٹا;
    *activation_params->token = SDL_strdup(token);
    activation_params->مکمل = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ساکن ثابت ساخت xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_مکمل
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, حرف **token, حرف **کھڑکی_id)
{
    اگر (!_this || !token) {
        واپس false;
    }

    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;

    SDL_WaylandSeat *seat = viddata->آخری_implicit_grab_seat;
    SDL_کھڑکی_ڈیٹا *focus = تہی;

    اگر (seat) {
        focus = seat->keyboard.focus;
        اگر (!focus) {
            focus = seat->اشارہ_گر_2.focus;
        }
    }

    ثابت حرف *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    اگر (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    اگر (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        اگر (!*token) {
            واپس false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } ورنہ اگر (viddata->activation_manager) {
        ساخت wl_surface *requesting_surface = focus ? focus->surface : تہی;
        Wayland_ActivationParams params = {
            .token = token,
            .مکمل = false
        };

        ساخت wl_event_قطار *activation_token_قطار = Wayland_Display_Create_قطار(viddata->display, "SDL Activation Token Generation Queue");

        ساخت wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_سیٹ_قطار(activation_manager_wrapper, activation_token_قطار);
        ساخت xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((ساخت xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_جوڑو_listener(activation_token, &xdg_activation_listener, &params);

        اگر (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_سیٹ_surface(activation_token, requesting_surface);
        }
        اگر (seat && seat->wl_seat) {
            xdg_activation_token_v1_سیٹ_serial(activation_token, seat->آخری_implicit_grab_serial, seat->wl_seat);
        }
        اگر (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_سیٹ_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        جب (!params.مکمل) {
            WAYLAND_wl_display_dispatch_قطار(viddata->display, activation_token_قطار);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_قطار_destroy(activation_token_قطار);

        اگر (!*token) {
            واپس false;
        }
    }

    اگر (focus && کھڑکی_id) {
        ثابت حرف *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, تہی);
        اگر (id) {
            ثابت size_t len = SDL_strlen(id) + حجم(WAYLAND_HANDLE_سابقہ) + 1;
            *کھڑکی_id = SDL_malloc(len);
            اگر (!*کھڑکی_id) {
                SDL_free(*token);
                *token = تہی;
                واپس false;
            }

            SDL_strlcpy(*کھڑکی_id, WAYLAND_HANDLE_سابقہ, len);
            SDL_strlcat(*کھڑکی_id, id, len);
        }
    }

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
