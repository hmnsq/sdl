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

প্রকারনির্দেশ সংরচনা Wayland_ActivationParams
{
    বর্ণ **token;
    bool done;
} Wayland_ActivationParams;

স্থির শূন্য handle_xdg_activation_done(শূন্য *data, সংরচনা xdg_activation_token_v1 *xdg_activation_token_v1, ধ্রুব বর্ণ *token)
{
    Wayland_ActivationParams *activation_params = (Wayland_ActivationParams *)data;
    *activation_params->token = SDL_strdup(token);
    activation_params->done = true;

    xdg_activation_token_v1_destroy(xdg_activation_token_v1);
}

স্থির ধ্রুব সংরচনা xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
};

bool Wayland_GetActivationTokenForExport(SDL_VideoDevice *_this, বর্ণ **token, বর্ণ **window_id)
{
    যদি (!_this || !token) {
        প্রত্যাগম false;
    }

    SDL_VideoData *viddata = _this->internal;

    SDL_WaylandSeat *seat = viddata->last_implicit_grab_seat;
    SDL_WindowData *focus = রিক্ত;

    যদি (seat) {
        focus = seat->keyboard.focus;
        যদি (!focus) {
            focus = seat->pointer.focus;
        }
    }

    ধ্রুব বর্ণ *xdg_activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
    যদি (!xdg_activation_token) {
        xdg_activation_token = SDL_GetNotificationActivationToken();
    }
    যদি (xdg_activation_token) {
        *token = SDL_strdup(xdg_activation_token);
        যদি (!*token) {
            প্রত্যাগম false;
        }

        // Unset the envvar after claiming the token.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    } অন্যথা যদি (viddata->activation_manager) {
        সংরচনা wl_surface *requesting_surface = focus ? focus->surface : রিক্ত;
        Wayland_ActivationParams params = {
            .token = token,
            .done = false
        };

        সংরচনা wl_event_queue *activation_token_queue = Wayland_DisplayCreateQueue(viddata->display, "SDL Activation Token Generation Queue");

        সংরচনা wl_proxy *activation_manager_wrapper = WAYLAND_wl_proxy_create_wrapper(viddata->activation_manager);
        WAYLAND_wl_proxy_set_queue(activation_manager_wrapper, activation_token_queue);
        সংরচনা xdg_activation_token_v1 *activation_token = xdg_activation_v1_get_activation_token((সংরচনা xdg_activation_v1 *)activation_manager_wrapper);
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

        যাবত্ (!params.done) {
            WAYLAND_wl_display_dispatch_queue(viddata->display, activation_token_queue);
        }
        WAYLAND_wl_proxy_wrapper_destroy(activation_manager_wrapper);
        WAYLAND_wl_event_queue_destroy(activation_token_queue);

        যদি (!*token) {
            প্রত্যাগম false;
        }
    }

    যদি (focus && window_id) {
        ধ্রুব বর্ণ *id = SDL_GetStringProperty(focus->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, রিক্ত);
        যদি (id) {
            ধ্রুব size_t len = SDL_strlen(id) + পরিমাণ(WAYLAND_HANDLE_PREFIX) + 1;
            *window_id = SDL_malloc(len);
            যদি (!*window_id) {
                SDL_free(*token);
                *token = রিক্ত;
                প্রত্যাগম false;
            }

            SDL_strlcpy(*window_id, WAYLAND_HANDLE_PREFIX, len);
            SDL_strlcat(*window_id, id, len);
        }
    }

    প্রত্যাগম true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
