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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "SDL_waylanddatamanager.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandclipboard.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

bool Wayland_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ಯದಿ (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_data_offer_seat = seat;

    ಯದಿ (seat && seat->data_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_data->seat_list, link) {
            ಯದಿ (s->data_device) {
                ಯದಿ (s != seat) {
                    Wayland_DataSourceDestroy(s->data_device->selection_source);
                    s->data_device->selection_source = ರಿಕ್ತ;
                }

                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ರಿಕ್ತ;
            }
        }

        SDL_WaylandDataDevice *data_device = seat->data_device;

        ಯದಿ (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_WaylandDataSource *source = Wayland_DataSourceCreate(video_data);
            Wayland_DataSourceSetCallback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            result = Wayland_DataDeviceSetSelectionSource(data_device, source, (ಧ್ರುವ ವರ್ಣ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types);
            ಯದಿ (!result) {
                Wayland_DataSourceDestroy(source);
            }
        } ಅನ್ಯಥಾ {
            Wayland_DataSourceDestroy(data_device->selection_source);
            data_device->selection_source = ರಿಕ್ತ;
            result = true;
        }
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

ಶೂನ್ಯ *Wayland_GetClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;

    ಯದಿ (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        ಯದಿ (data_device->selection_source) {
            buffer = SDL_GetInternalClipboardData(_this, mime_type, length);
        } ಅನ್ಯಥಾ ಯದಿ (Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type)) {
            buffer = Wayland_DataOfferReceive(data_device->selection_offer, mime_type, length);
        }
    }

    ಪ್ರತ್ಯಾಗಮ buffer;
}

bool Wayland_HasClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    bool result = false;

    ಯದಿ (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        ಯದಿ (data_device->selection_source) {
            result = SDL_HasInternalClipboardData(_this, mime_type);
        } ಅನ್ಯಥಾ {
            result = Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type);
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    *ಅಂಕೆ_mime_types = SDL_arraysize(text_mime_types);
    ಪ್ರತ್ಯಾಗಮ text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ಯದಿ (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_primary_selection_seat = seat;

    ಯದಿ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಯದಿ (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_data);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            result = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            ಯದಿ (!result) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } ಅನ್ಯಥಾ {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = ರಿಕ್ತ;
            result = true;
        }
    } ಅನ್ಯಥಾ {
        result = SDL_SetError("Primary selection not supported");
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ವರ್ಣ *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    ವರ್ಣ *text = ರಿಕ್ತ;
    size_t length = 0;

    ಯದಿ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಯದಿ (primary_selection_device->selection_source) {
            text = Wayland_PrimarySelectionSourceGetData(primary_selection_device->selection_source, TEXT_MIME, &length);
        } ಅನ್ಯಥಾ {
            ಪ್ರತಿ (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                ಯದಿ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &length);
                    ಭಙ್ಗ;
                }
            }
        }
    }

    ಯದಿ (!text) {
        text = SDL_strdup("");
    }

    ಪ್ರತ್ಯಾಗಮ text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    bool result = false;

    ಯದಿ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ಯದಿ (primary_selection_device->selection_source) {
            result = true;
        } ಅನ್ಯಥಾ {
            size_t mime_ಎಣಿಕೆ = 0;
            ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types = Wayland_GetTextMimeTypes(_this, &mime_ಎಣಿಕೆ);
            ಪ್ರತಿ (size_t i = 0; i < mime_ಎಣಿಕೆ; i++) {
                ಯದಿ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    result = true;
                    ಭಙ್ಗ;
                }
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
