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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ "SDL_waylanddatamanager.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"
#அந்தர்பாவ "SDL_waylandclipboard.h"
#அந்தர்பாவ "../SDL_clipboard_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

bool Wayland_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    எனில் (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_data_offer_seat = seat;

    எனில் (seat && seat->data_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_data->seat_list, link) {
            எனில் (s->data_device) {
                எனில் (s != seat) {
                    Wayland_DataSourceDestroy(s->data_device->selection_source);
                    s->data_device->selection_source = வெற்று;
                }

                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = வெற்று;
            }
        }

        SDL_WaylandDataDevice *data_device = seat->data_device;

        எனில் (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_WaylandDataSource *source = Wayland_DataSourceCreate(video_data);
            Wayland_DataSourceSetCallback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            result = Wayland_DataDeviceSetSelectionSource(data_device, source, (மாறிலி எழுத்து **)_this->clipboard_mime_types, _this->இலக்கம்_clipboard_mime_types);
            எனில் (!result) {
                Wayland_DataSourceDestroy(source);
            }
        } இல்லையெனில் {
            Wayland_DataSourceDestroy(data_device->selection_source);
            data_device->selection_source = வெற்று;
            result = true;
        }
    }

    திரும்பு result;
}

வெறுமை *Wayland_GetClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *length)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    வெறுமை *buffer = வெற்று;

    எனில் (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        எனில் (data_device->selection_source) {
            buffer = SDL_GetInternalClipboardData(_this, mime_type, length);
        } இல்லையெனில் எனில் (Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type)) {
            buffer = Wayland_DataOfferReceive(data_device->selection_offer, mime_type, length);
        }
    }

    திரும்பு buffer;
}

bool Wayland_HasClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    bool result = false;

    எனில் (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        எனில் (data_device->selection_source) {
            result = SDL_HasInternalClipboardData(_this, mime_type);
        } இல்லையெனில் {
            result = Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type);
        }
    }
    திரும்பு result;
}

நிலையான மாறிலி எழுத்து *மாறிலி text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

மாறிலி எழுத்து *மாறிலி *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *இலக்கம்_mime_types)
{
    *இலக்கம்_mime_types = SDL_arraysize(text_mime_types);
    திரும்பு text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, மாறிலி எழுத்து *text)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result;

    // If no implicit grab is available yet, just attach it to the first available seat.
    எனில் (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_primary_selection_seat = seat;

    எனில் (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        எனில் (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_data);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            result = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            எனில் (!result) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } இல்லையெனில் {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = வெற்று;
            result = true;
        }
    } இல்லையெனில் {
        result = SDL_SetError("Primary selection not supported");
    }
    திரும்பு result;
}

எழுத்து *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    எழுத்து *text = வெற்று;
    size_t length = 0;

    எனில் (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        எனில் (primary_selection_device->selection_source) {
            text = Wayland_PrimarySelectionSourceGetData(primary_selection_device->selection_source, TEXT_MIME, &length);
        } இல்லையெனில் {
            க்கு (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                எனில் (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &length);
                    நிறுத்து;
                }
            }
        }
    }

    எனில் (!text) {
        text = SDL_strdup("");
    }

    திரும்பு text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    bool result = false;

    எனில் (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        எனில் (primary_selection_device->selection_source) {
            result = true;
        } இல்லையெனில் {
            size_t mime_மொத்தம் = 0;
            மாறிலி எழுத்து *மாறிலி *mime_types = Wayland_GetTextMimeTypes(_this, &mime_மொத்தம்);
            க்கு (size_t i = 0; i < mime_மொத்தம்; i++) {
                எனில் (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    result = true;
                    நிறுத்து;
                }
            }
        }
    }
    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
