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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylanddatamanager.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

bool Wayland_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->ਆਖਰੀ_implicit_grab_seat;
    bool ਨਤੀਜਾ = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ਜੇ (!seat && !WAYLAND_wl_list_ਖਾਲੀ_ਥਾਵਾਂ(&video_ਅੰਕੜੇ->seat_list)) {
        seat = wl_container_ਦਾ(video_ਅੰਕੜੇ->seat_list.ਅਗਲਾ, seat, link);
    }

    video_ਅੰਕੜੇ->current_ਅੰਕੜੇ_offer_seat = seat;

    ਜੇ (seat && seat->ਅੰਕੜੇ_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_ਅੰਕੜੇ->seat_list, link) {
            ਜੇ (s->ਅੰਕੜੇ_device) {
                ਜੇ (s != seat) {
                    Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(s->ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
                    s->ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਨਿਰਾ;
                }

                Wayland_ਅੰਕੜੇ_Offer_Destroy(s->ਅੰਕੜੇ_device->selection_offer);
                s->ਅੰਕੜੇ_device->selection_offer = ਨਿਰਾ;
            }
        }

        SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = seat->ਅੰਕੜੇ_device;

        ਜੇ (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ = Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Create(video_ਅੰਕੜੇ);
            Wayland_ਅੰਕੜੇ_ਸਰੋਤ_ਸੈੱਟ_Callback(ਸਰੋਤ, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            ਨਤੀਜਾ = Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_ਸਰੋਤ(ਅੰਕੜੇ_device, ਸਰੋਤ, (ਅਚਲ ਅੱਖਰ **)_this->clipboard_mime_types, _this->ਅੰਕ_clipboard_mime_types);
            ਜੇ (!ਨਤੀਜਾ) {
                Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਸਰੋਤ);
            }
        } ਨਹੀਂਤਾਂ {
            Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
            ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਨਿਰਾ;
            ਨਤੀਜਾ = true;
        }
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ *Wayland_Get_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->current_ਅੰਕੜੇ_offer_seat;
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;

    ਜੇ (seat && seat->ਅੰਕੜੇ_device) {
        SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = seat->ਅੰਕੜੇ_device;
        ਜੇ (ਅੰਕੜੇ_device->selection_ਸਰੋਤ) {
            ਬਫਰ_2 = SDL_Get_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type, ਲੰਮਾਈ);
        } ਨਹੀਂਤਾਂ ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(ਅੰਕੜੇ_device->selection_offer, mime_type)) {
            ਬਫਰ_2 = Wayland_ਅੰਕੜੇ_Offer_Receive(ਅੰਕੜੇ_device->selection_offer, mime_type, ਲੰਮਾਈ);
        }
    }

    ਵਾਪਸ ਬਫਰ_2;
}

bool Wayland_Has_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->current_ਅੰਕੜੇ_offer_seat;
    bool ਨਤੀਜਾ = false;

    ਜੇ (seat && seat->ਅੰਕੜੇ_device) {
        SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = seat->ਅੰਕੜੇ_device;
        ਜੇ (ਅੰਕੜੇ_device->selection_ਸਰੋਤ) {
            ਨਤੀਜਾ = SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type);
        } ਨਹੀਂਤਾਂ {
            ਨਤੀਜਾ = Wayland_ਅੰਕੜੇ_Offer_Has_MIME(ਅੰਕੜੇ_device->selection_offer, mime_type);
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ ਪਾਠ_mime_types[] = {
    ਪਾਠ_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ਅਚਲ ਅੱਖਰ *ਅਚਲ *Wayland_Get_ਪਾਠ_Mime_Types(SDL_VideoDevice *_this, size_t *ਅੰਕ_mime_types)
{
    *ਅੰਕ_mime_types = SDL_arraysize(ਪਾਠ_mime_types);
    ਵਾਪਸ ਪਾਠ_mime_types;
}

bool Wayland_ਸੈੱਟ_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->ਆਖਰੀ_implicit_grab_seat;
    bool ਨਤੀਜਾ;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ਜੇ (!seat && !WAYLAND_wl_list_ਖਾਲੀ_ਥਾਵਾਂ(&video_ਅੰਕੜੇ->seat_list)) {
        seat = wl_container_ਦਾ(video_ਅੰਕੜੇ->seat_list.ਅਗਲਾ, seat, link);
    }

    video_ਅੰਕੜੇ->current_primary_selection_seat = seat;

    ਜੇ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ਜੇ (ਪਾਠ[0] != '\0') {
            SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ = Wayland_Primary_Selection_ਸਰੋਤ_Create(video_ਅੰਕੜੇ);
            Wayland_Primary_Selection_ਸਰੋਤ_ਸੈੱਟ_Callback(ਸਰੋਤ, SDL_Clipboard_ਪਾਠ_Callback, SDL_free, SDL_strdup(ਪਾਠ));

            ਨਤੀਜਾ = Wayland_Primary_Selection_Device_ਸੈੱਟ_Selection(primary_selection_device, ਸਰੋਤ, ਪਾਠ_mime_types, SDL_arraysize(ਪਾਠ_mime_types));
            ਜੇ (!ਨਤੀਜਾ) {
                Wayland_Primary_Selection_ਸਰੋਤ_Destroy(ਸਰੋਤ);
            }
        } ਨਹੀਂਤਾਂ {
            Wayland_Primary_Selection_ਸਰੋਤ_Destroy(seat->primary_selection_device->selection_ਸਰੋਤ);
            seat->primary_selection_device->selection_ਸਰੋਤ = ਨਿਰਾ;
            ਨਤੀਜਾ = true;
        }
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Primary selection not supported");
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਅੱਖਰ *Wayland_Get_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->current_primary_selection_seat;
    ਅੱਖਰ *ਪਾਠ = ਨਿਰਾ;
    size_t ਲੰਮਾਈ = 0;

    ਜੇ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ਜੇ (primary_selection_device->selection_ਸਰੋਤ) {
            ਪਾਠ = Wayland_Primary_Selection_ਸਰੋਤ_Get_ਅੰਕੜੇ(primary_selection_device->selection_ਸਰੋਤ, ਪਾਠ_MIME, &ਲੰਮਾਈ);
        } ਨਹੀਂਤਾਂ {
            ਲਈ (size_t i = 0; i < SDL_arraysize(ਪਾਠ_mime_types); i++) {
                ਜੇ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, ਪਾਠ_mime_types[i])) {
                    ਪਾਠ = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, ਪਾਠ_mime_types[i], &ਲੰਮਾਈ);
                    ਰੋਕੋ;
                }
            }
        }
    }

    ਜੇ (!ਪਾਠ) {
        ਪਾਠ = SDL_strdup("");
    }

    ਵਾਪਸ ਪਾਠ;
}

bool Wayland_Has_Primary_Selection_ਪਾਠ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = video_ਅੰਕੜੇ->current_primary_selection_seat;
    bool ਨਤੀਜਾ = false;

    ਜੇ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ਜੇ (primary_selection_device->selection_ਸਰੋਤ) {
            ਨਤੀਜਾ = true;
        } ਨਹੀਂਤਾਂ {
            size_t mime_ਗਿਣਤੀ = 0;
            ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types = Wayland_Get_ਪਾਠ_Mime_Types(_this, &mime_ਗਿਣਤੀ);
            ਲਈ (size_t i = 0; i < mime_ਗਿਣਤੀ; i++) {
                ਜੇ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    ਨਤੀਜਾ = true;
                    ਰੋਕੋ;
                }
            }
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
