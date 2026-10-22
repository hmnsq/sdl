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

#ಅನ್ತರ್ಭಾವ "SDL_waylanddatamanager.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandclipboard.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

bool Wayland_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->ಕೊನೆಯ_implicit_grab_seat;
    bool ಫಲಿತಾಂಶ = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ಆದರೆ (!seat && !WAYLAND_wl_list_ಖಾಲಿಗಳು(&video_ದತ್ತಾಂಶ->seat_list)) {
        seat = wl_container_ದ(video_ದತ್ತಾಂಶ->seat_list.ಮುಂದಿನ, seat, link);
    }

    video_ದತ್ತಾಂಶ->current_ದತ್ತಾಂಶ_offer_seat = seat;

    ಆದರೆ (seat && seat->ದತ್ತಾಂಶ_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_ದತ್ತಾಂಶ->seat_list, link) {
            ಆದರೆ (s->ದತ್ತಾಂಶ_device) {
                ಆದರೆ (s != seat) {
                    Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(s->ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
                    s->ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಖಾಲಿ;
                }

                Wayland_ದತ್ತಾಂಶ_Offer_Destroy(s->ದತ್ತಾಂಶ_device->selection_offer);
                s->ದತ್ತಾಂಶ_device->selection_offer = ಖಾಲಿ;
            }
        }

        SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = seat->ದತ್ತಾಂಶ_device;

        ಆದರೆ (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ = Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Create(video_ದತ್ತಾಂಶ);
            Wayland_ದತ್ತಾಂಶ_ಮೂಲ_ಗಣ_Callback(ಮೂಲ, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            ಫಲಿತಾಂಶ = Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_ಮೂಲ(ದತ್ತಾಂಶ_device, ಮೂಲ, (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types);
            ಆದರೆ (!ಫಲಿತಾಂಶ) {
                Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ಮೂಲ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
            ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಖಾಲಿ;
            ಫಲಿತಾಂಶ = true;
        }
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ *Wayland_Get_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->current_ದತ್ತಾಂಶ_offer_seat;
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;

    ಆದರೆ (seat && seat->ದತ್ತಾಂಶ_device) {
        SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = seat->ದತ್ತಾಂಶ_device;
        ಆದರೆ (ದತ್ತಾಂಶ_device->selection_ಮೂಲ) {
            ಬಫರ್_2 = SDL_Get_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type, ಉದ್ದಳತೆ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(ದತ್ತಾಂಶ_device->selection_offer, mime_type)) {
            ಬಫರ್_2 = Wayland_ದತ್ತಾಂಶ_Offer_Receive(ದತ್ತಾಂಶ_device->selection_offer, mime_type, ಉದ್ದಳತೆ);
        }
    }

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

bool Wayland_Has_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->current_ದತ್ತಾಂಶ_offer_seat;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (seat && seat->ದತ್ತಾಂಶ_device) {
        SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = seat->ದತ್ತಾಂಶ_device;
        ಆದರೆ (ದತ್ತಾಂಶ_device->selection_ಮೂಲ) {
            ಫಲಿತಾಂಶ = SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಫಲಿತಾಂಶ = Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(ದತ್ತಾಂಶ_device->selection_offer, mime_type);
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ ಪಠ್ಯ_mime_types[] = {
    ಪಠ್ಯ_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *Wayland_Get_ಪಠ್ಯ_Mime_Types(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    *ಅಂಕೆ_mime_types = SDL_arraysize(ಪಠ್ಯ_mime_types);
    ಹಿಂತಿರುಗಿ ಪಠ್ಯ_mime_types;
}

bool Wayland_ಗಣ_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->ಕೊನೆಯ_implicit_grab_seat;
    bool ಫಲಿತಾಂಶ;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ಆದರೆ (!seat && !WAYLAND_wl_list_ಖಾಲಿಗಳು(&video_ದತ್ತಾಂಶ->seat_list)) {
        seat = wl_container_ದ(video_ದತ್ತಾಂಶ->seat_list.ಮುಂದಿನ, seat, link);
    }

    video_ದತ್ತಾಂಶ->current_primary_selection_seat = seat;

    ಆದರೆ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಆದರೆ (ಪಠ್ಯ[0] != '\0') {
            SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ = Wayland_Primary_Selection_ಮೂಲ_Create(video_ದತ್ತಾಂಶ);
            Wayland_Primary_Selection_ಮೂಲ_ಗಣ_Callback(ಮೂಲ, SDL_Clipboard_ಪಠ್ಯ_Callback, SDL_free, SDL_strdup(ಪಠ್ಯ));

            ಫಲಿತಾಂಶ = Wayland_Primary_Selection_Device_ಗಣ_Selection(primary_selection_device, ಮೂಲ, ಪಠ್ಯ_mime_types, SDL_arraysize(ಪಠ್ಯ_mime_types));
            ಆದರೆ (!ಫಲಿತಾಂಶ) {
                Wayland_Primary_Selection_ಮೂಲ_Destroy(ಮೂಲ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_Primary_Selection_ಮೂಲ_Destroy(seat->primary_selection_device->selection_ಮೂಲ);
            seat->primary_selection_device->selection_ಮೂಲ = ಖಾಲಿ;
            ಫಲಿತಾಂಶ = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Primary selection not supported");
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಅಕ್ಷರ *Wayland_Get_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->current_primary_selection_seat;
    ಅಕ್ಷರ *ಪಠ್ಯ = ಖಾಲಿ;
    size_t ಉದ್ದಳತೆ = 0;

    ಆದರೆ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಆದರೆ (primary_selection_device->selection_ಮೂಲ) {
            ಪಠ್ಯ = Wayland_Primary_Selection_ಮೂಲ_Get_ದತ್ತಾಂಶ(primary_selection_device->selection_ಮೂಲ, ಪಠ್ಯ_MIME, &ಉದ್ದಳತೆ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಾಗಿ (size_t i = 0; i < SDL_arraysize(ಪಠ್ಯ_mime_types); i++) {
                ಆದರೆ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, ಪಠ್ಯ_mime_types[i])) {
                    ಪಠ್ಯ = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, ಪಠ್ಯ_mime_types[i], &ಉದ್ದಳತೆ);
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }

    ಆದರೆ (!ಪಠ್ಯ) {
        ಪಠ್ಯ = SDL_strdup("");
    }

    ಹಿಂತಿರುಗಿ ಪಠ್ಯ;
}

bool Wayland_Has_Primary_Selection_ಪಠ್ಯ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = video_ದತ್ತಾಂಶ->current_primary_selection_seat;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಆದರೆ (primary_selection_device->selection_ಮೂಲ) {
            ಫಲಿತಾಂಶ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            size_t mime_ಎಣಿಕೆ = 0;
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types = Wayland_Get_ಪಠ್ಯ_Mime_Types(_this, &mime_ಎಣಿಕೆ);
            ಗಾಗಿ (size_t i = 0; i < mime_ಎಣಿಕೆ; i++) {
                ಆದರೆ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    ಫಲಿತಾಂಶ = true;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
