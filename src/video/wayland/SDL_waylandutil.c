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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylandutil.h"
#समावेश "xdg-activation-v1-client-protocol.h"

#समावेश "../../notification/SDL_notification_c.h"

#घोषणा WAYLAND_HANDLE_PREFIX "wayland:"

प्रकार काष्ठा Wayland_ActivationParams
{
    अक्षर **token;
    bool done;
} Wayland_ActivationParams;

अटल व्योम handle_xdg_activation_done(व्योम *तथ्य, काष्ठा xdg_activation_token_v1 *xdg_activation_token_v1, स्थिर अक्षर *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)तथ्य;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

अटल स्थिर काष्ठा xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, अक्षर **token, अक्षर **window_id)
{
    अगर (!_this || !token) {
        वापस false;
    }

    SDL_Video_तथ्य *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_Window_तथ्य *focus = शून्य;

    अगर (seat) {
        focus = seat->keyboard.focus;
        अगर (!focus) {
            focus = seat->pointer.focus;
        }
    }

    स्थिर अक्षर *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    अगर (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    अगर (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        अगर (!*token) {
            वापस false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } अन्यथा अगर (viddata->activation_manager) {
        काष्ठा wl_surface *requesting_surface = focus ? focus->surface : शून्य;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        काष्ठा wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        काष्ठा wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        काष्ठा xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((काष्ठा xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_add_listener(activation_token, &xdg_activation_listener, &params);

        अगर (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(activation_token, requesting_surface);
        }
        अगर (seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        अगर (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_set_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        जबतक (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        अगर (!*token) {
            वापस false;
        }
    }

    अगर (focus && window_id) {
        स्थिर अक्षर *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, शून्य);
        अगर (id) {
            स्थिर माप_प्रकार len = SDL_strlen(id) + माप(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            अगर (!*window_id) {
                SDL_free(*token);
                *token = शून्य;
                वापस false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
