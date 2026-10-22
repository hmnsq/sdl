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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ "SDL_waylanddatamanager.h"
#અન્તર્ભાવ "SDL_waylandevents_c.h"
#અન્તર્ભાવ "SDL_waylandclipboard.h"
#અન્તર્ભાવ "../SDL_clipboard_c.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"

bool Wayland_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    જો (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_data_offer_seat = seat;

    જો (seat && seat->data_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_data->seat_list, link) {
            જો (s->data_device) {
                જો (s != seat) {
                    Wayland_DataSourceDestroy(s->data_device->selection_source);
                    s->data_device->selection_source = ખાલી;
                }

                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ખાલી;
            }
        }

        SDL_WaylandDataDevice *data_device = seat->data_device;

        જો (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_WaylandDataSource *source = Wayland_DataSourceCreate(video_data);
            Wayland_DataSourceSetCallback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            result = Wayland_DataDeviceSetSelectionSource(data_device, source, (અચલ અક્ષર **)_this->clipboard_mime_types, _this->અંક_clipboard_mime_types);
            જો (!result) {
                Wayland_DataSourceDestroy(source);
            }
        } નહીંતર {
            Wayland_DataSourceDestroy(data_device->selection_source);
            data_device->selection_source = ખાલી;
            result = true;
        }
    }

    પાછા result;
}

શૂન્ય *Wayland_GetClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *length)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    શૂન્ય *buffer = ખાલી;

    જો (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        જો (data_device->selection_source) {
            buffer = SDL_GetInternalClipboardData(_this, mime_type, length);
        } નહીંતર જો (Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type)) {
            buffer = Wayland_DataOfferReceive(data_device->selection_offer, mime_type, length);
        }
    }

    પાછા buffer;
}

bool Wayland_HasClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    bool result = false;

    જો (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        જો (data_device->selection_source) {
            result = SDL_HasInternalClipboardData(_this, mime_type);
        } નહીંતર {
            result = Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type);
        }
    }
    પાછા result;
}

સ્થિર અચલ અક્ષર *અચલ text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

અચલ અક્ષર *અચલ *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *અંક_mime_types)
{
    *અંક_mime_types = SDL_arraysize(text_mime_types);
    પાછા text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, અચલ અક્ષર *text)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result;

    // If no implicit grab is available yet, just attach it to the first available seat.
    જો (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_primary_selection_seat = seat;

    જો (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        જો (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_data);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            result = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            જો (!result) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } નહીંતર {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = ખાલી;
            result = true;
        }
    } નહીંતર {
        result = SDL_SetError("Primary selection not supported");
    }
    પાછા result;
}

અક્ષર *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    અક્ષર *text = ખાલી;
    size_t length = 0;

    જો (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        જો (primary_selection_device->selection_source) {
            text = Wayland_PrimarySelectionSourceGetData(primary_selection_device->selection_source, TEXT_MIME, &length);
        } નહીંતર {
            માટે (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                જો (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &length);
                    તોડો;
                }
            }
        }
    }

    જો (!text) {
        text = SDL_strdup("");
    }

    પાછા text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    bool result = false;

    જો (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        જો (primary_selection_device->selection_source) {
            result = true;
        } નહીંતર {
            size_t mime_ગણતરી = 0;
            અચલ અક્ષર *અચલ *mime_types = Wayland_GetTextMimeTypes(_this, &mime_ગણતરી);
            માટે (size_t i = 0; i < mime_ગણતરી; i++) {
                જો (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    result = true;
                    તોડો;
                }
            }
        }
    }
    પાછા result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
