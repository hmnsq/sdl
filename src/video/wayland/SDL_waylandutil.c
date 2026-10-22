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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandutil.h"
#ضمن "xdg-activation-v1-client-protocol.h"

#ضمن "../../notification/SDL_notification_c.h"

#تعریف_کن WAYLAND_HANDLE_پیشوند "wayland:"

تعريفنوع بنية Wayland_ActivationParams
{
    حرف **token;
    bool انجامشده;
} Wayland_ActivationParams;

ساكن فراغ handle_xdg_activation_انجامشده(فراغ *داده, بنية xdg_activation_token_v1 *xdg_activation_token_v1, ثابت حرف *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)داده;
    *activation_params->token = SDL_strdup(token);
    activation_params->انجامشده = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_انجامشده
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, حرف **token, حرف **پنجره_id)
{
    إذا (!_this || !token) {
        أرجع false;
    }

    SDL_Video_داده *viddata = _this->داخلی;

    SDL_WaylandSeat *seat = viddata->آخرین_implicit_grab_seat;
    SDL_پنجره_داده *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشاره_گر_2.focus;
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
            .انجامشده = false
        };

        بنية wl_event_صف *activation_token_صف = Wayland_Display_Create_صف(viddata->display, "SDL Activation Token Generation Queue");

        بنية wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_مجموعه_صف(activation_manager_wrapper, activation_token_صف);
        بنية xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((بنية xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_جمع_کن_listener(activation_token, &xdg_activation_listener, &params);

        إذا (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_مجموعه_surface(activation_token, requesting_surface);
        }
        إذا (seat && seat->wl_seat) {
            xdg_activation_token_v1_مجموعه_serial(activation_token, seat->آخرین_implicit_grab_serial, seat->wl_seat);
        }
        إذا (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_مجموعه_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        طالما (!params.انجامشده) {
            WAYLAND_wl_display_dispatch_صف(viddata->display, activation_token_صف);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_صف_destroy(activation_token_صف);

        إذا (!*token) {
            أرجع false;
        }
    }

    إذا (focus && پنجره_id) {
        ثابت حرف *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
        إذا (id) {
            ثابت size_t len = SDL_strlen(id) + حجم(WAYLAND_HANDLE_پیشوند) + 1;
            *پنجره_id = SDL_malloc(len);
            إذا (!*پنجره_id) {
                SDL_free(*token);
                *token = عدم;
                أرجع false;
            }

            SDL_strlcpy(*پنجره_id, WAYLAND_HANDLE_پیشوند, len);
            SDL_strlcat(*پنجره_id, id, len);
        }
    }

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND
