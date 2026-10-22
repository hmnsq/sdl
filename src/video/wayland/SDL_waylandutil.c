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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব "SDL_waylandevents_c.h"
#অন্তর্ভাব "SDL_waylandutil.h"
#অন্তর্ভাব "xdg-activation-v1-client-protocol.h"

#অন্তর্ভাব "../../notification/SDL_notification_c.h"

#define WAYLAND_HANDLE_PREFIX "wayland:"

প্রকারলেখ কাঠামো Wayland_ActivationParams
{
    অক্ষর **token;
    bool done;
} Wayland_ActivationParams;

স্থির শূন্য handle_xdg_activation_done(শূন্য *তথ্য, কাঠামো xdg_activation_token_v1 *xdg_activation_token_v1, ধ্রুবক অক্ষর *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)তথ্য;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

স্থির ধ্রুবক কাঠামো xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, অক্ষর **token, অক্ষর **window_id)
{
    যদি (!_this || !token) {
        ফেরত false;
    }

    SDL_Video_তথ্য *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_Window_তথ্য *focus = ফাঁকা;

    যদি (seat) {
        focus = seat->keyboard.focus;
        যদি (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ধ্রুবক অক্ষর *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    যদি (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    যদি (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        যদি (!*token) {
            ফেরত false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } অন্যথা যদি (viddata->activation_manager) {
        কাঠামো wl_surface *requesting_surface = focus ? focus->surface : ফাঁকা;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        কাঠামো wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        কাঠামো wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        কাঠামো xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((কাঠামো xdg_activation_v1 *)activation_manager_wrapper);
        xdg_activation_token_v1_add_listener(activation_token, &xdg_activation_listener, &params);

        যদি (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(activation_token, requesting_surface);
        }
        যদি (seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        যদি (focus && focus->app_id) {
            // Set the app ID for external use.
            xdg_activation_token_v1_set_app_id(activation_token, focus->app_id);
        }
        xdg_activation_token_v1_commit(activation_token);

        যখন (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        যদি (!*token) {
            ফেরত false;
        }
    }

    যদি (focus && window_id) {
        ধ্রুবক অক্ষর *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ফাঁকা);
        যদি (id) {
            ধ্রুবক size_t len = SDL_strlen(id) + আকার(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            যদি (!*window_id) {
                SDL_free(*token);
                *token = ফাঁকা;
                ফেরত false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
