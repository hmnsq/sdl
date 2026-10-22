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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylandutil.h"
#అన్తర్భావ "xdg-activation-v1-client-protocol.h"

#అన్తర్భావ "../../notification/SDL_notification_c.h"

#నిర్వచించు WAYLAND_HANDLE_ఉపసర్గ "wayland:"

రకనిర్వచనం నిర్మాణం Wayland_ActivationParams
{
    అక్షరం **token;
    bool పూర్తి;
} Wayland_ActivationParams;

స్థిర శూన్య handle_xdg_activation_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం xdg_activation_token_v1 *xdg_activation_token_v1, స్థిరరాశి అక్షరం *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)దత్తాంశం;
    *activation_params->token = SDL_strdup(token);
    activation_params->పూర్తి = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

స్థిర స్థిరరాశి నిర్మాణం xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_పూర్తి
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, అక్షరం **token, అక్షరం **కిటికీ_id)
{
    ఒకవేళ (!_this || !token) {
        తిరిగి false;
    }

    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;

    SDL_WaylandSeat *seat = viddata->చివరి_implicit_grab_seat;
    SDL_కిటికీ_దత్తాంశం *focus = ఖాళీ;

    ఒకవేళ (seat) {
        focus = seat->keyboard.focus;
        ఒకవేళ (!focus) {
            focus = seat->సూచిక_2.focus;
        }
    }

    స్థిరరాశి అక్షరం *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    ఒకవేళ (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    ఒకవేళ (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        ఒకవేళ (!*token) {
            తిరిగి false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } లేకపోతే ఒకవేళ (viddata->activation_manager) {
        నిర్మాణం wl_surface *requesting_surface = focus ? focus->surface : ఖాళీ;
        Wayland_ActivationParams params = {
            .token = token,
            .పూర్తి = false
        };

        నిర్మాణం wl_event_వరుస *activation_token_వరుస = Wayland_Display_Create_వరుస(viddata->display, "SDL Activation Token Generation Queue");

        నిర్మాణం wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_సమితి_వరుస(activation_manager_wrapper, activation_token_వరుస);
        నిర్మాణం xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((నిర్మాణం xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_కూడు_listener(activation_token, &xdg_activation_listener, &params);

        ఒకవేళ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_సమితి_surface(activation_token, requesting_surface);
        }
        ఒకవేళ (seat && seat->wl_seat) {
            xdg_activation_token_v1_సమితి_serial(activation_token, seat->చివరి_implicit_grab_serial, seat->wl_seat);
        }
        ఒకవేళ (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_సమితి_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        అయితే (!params.పూర్తి) {
            WAYLAND_wl_display_dispatch_వరుస(viddata->display, activation_token_వరుస);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_వరుస_destroy(activation_token_వరుస);

        ఒకవేళ (!*token) {
            తిరిగి false;
        }
    }

    ఒకవేళ (focus && కిటికీ_id) {
        స్థిరరాశి అక్షరం *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ఖాళీ);
        ఒకవేళ (id) {
            స్థిరరాశి size_t len = SDL_strlen(id) + పరిమాణం(WAYLAND_HANDLE_ఉపసర్గ) + 1;
            *కిటికీ_id = SDL_malloc(len);
            ఒకవేళ (!*కిటికీ_id) {
                SDL_free(*token);
                *token = ఖాళీ;
                తిరిగి false;
            }

            SDL_strlcpy(*కిటికీ_id, WAYLAND_HANDLE_ఉపసర్గ, len);
            SDL_strlcat(*కిటికీ_id, id, len);
        }
    }

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
