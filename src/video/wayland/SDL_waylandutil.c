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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylandutil.h"
#अन्तर्भाव "xdg-activation-v1-client-protocol.h"

#अन्तर्भाव "../../notification/SDL_notification_c.h"

#परिभाषय WAYLAND_HANDLE_उपसर्गः "wayland:"

प्रकारनिर्देश संरचना Wayland_ActivationParams
{
    वर्ण **token;
    bool समाप्तम्;
} Wayland_ActivationParams;

स्थिर शून्य handle_xdg_activation_समाप्तम्(शून्य *दत्त, संरचना xdg_activation_token_v1 *xdg_activation_token_v1, ध्रुव वर्ण *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)दत्त;
    *activation_params->token = SDL_strdup(token);
    activation_params->समाप्तम् = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

स्थिर ध्रुव संरचना xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_समाप्तम्
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, वर्ण **token, वर्ण **गवाक्षः_id)
{
    यदि (!_this || !token) {
        प्रत्यागम false;
    }

    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;

    SDL_WaylandSeat *seat = viddata->चरमः_implicit_grab_seat;
    SDL_गवाक्षः_दत्त *focus = रिक्त;

    यदि (seat) {
        focus = seat->keyboard.focus;
        यदि (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ध्रुव वर्ण *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    यदि (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    यदि (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        यदि (!*token) {
            प्रत्यागम false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } अन्यथा यदि (viddata->activation_manager) {
        संरचना wl_surface *requesting_surface = focus ? focus->surface : रिक्त;
        Wayland_ActivationParams params = {
            .token = token,
            .समाप्तम् = false
        };

        संरचना wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        संरचना wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_समुच्चयः_queue(activation_manager_wrapper, activation_token_queue);
        संरचना xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((संरचना xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_सङ्कलय_listener(activation_token, &xdg_activation_listener, &params);

        यदि (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_समुच्चयः_surface(activation_token, requesting_surface);
        }
        यदि (seat && seat->wl_seat) {
            xdg_activation_token_v1_समुच्चयः_serial(activation_token, seat->चरमः_implicit_grab_serial, seat->wl_seat);
        }
        यदि (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_समुच्चयः_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        यावत् (!params.समाप्तम्) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        यदि (!*token) {
            प्रत्यागम false;
        }
    }

    यदि (focus && गवाक्षः_id) {
        ध्रुव वर्ण *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, रिक्त);
        यदि (id) {
            ध्रुव size_t len = SDL_strlen(id) + परिमाण(WAYLAND_HANDLE_उपसर्गः) + 1;
            *गवाक्षः_id = SDL_malloc(len);
            यदि (!*गवाक्षः_id) {
                SDL_free(*token);
                *token = रिक्त;
                प्रत्यागम false;
            }

            SDL_strlcpy(*गवाक्षः_id, WAYLAND_HANDLE_उपसर्गः, len);
            SDL_strlcat(*गवाक्षः_id, id, len);
        }
    }

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
