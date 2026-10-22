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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ "SDL_waylanddatamanager.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandclipboard.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_clipboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

bool Wayland_SetClipboardData(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ଯଦି (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_data_offer_seat = seat;

    ଯଦି (seat && seat->data_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_data->seat_list, link) {
            ଯଦି (s->data_device) {
                ଯଦି (s != seat) {
                    Wayland_DataSourceDestroy(s->data_device->selection_source);
                    s->data_device->selection_source = ଖାଲି;
                }

                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ଖାଲି;
            }
        }

        SDL_WaylandDataDevice *data_device = seat->data_device;

        ଯଦି (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_WaylandDataSource *source = Wayland_DataSourceCreate(video_data);
            Wayland_DataSourceSetCallback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            result = Wayland_DataDeviceSetSelectionSource(data_device, source, (ଅଚଳ ଅକ୍ଷର **)_this->clipboard_mime_types, _this->ଅଙ୍କ_clipboard_mime_types);
            ଯଦି (!result) {
                Wayland_DataSourceDestroy(source);
            }
        } ଅନ୍ୟଥା {
            Wayland_DataSourceDestroy(data_device->selection_source);
            data_device->selection_source = ଖାଲି;
            result = true;
        }
    }

    ଫେରନ୍ତୁ result;
}

ଶୂନ୍ୟ *Wayland_GetClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    ଶୂନ୍ୟ *buffer = ଖାଲି;

    ଯଦି (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        ଯଦି (data_device->selection_source) {
            buffer = SDL_GetInternalClipboardData(_this, mime_type, length);
        } ଅନ୍ୟଥା ଯଦି (Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type)) {
            buffer = Wayland_DataOfferReceive(data_device->selection_offer, mime_type, length);
        }
    }

    ଫେରନ୍ତୁ buffer;
}

bool Wayland_HasClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_data_offer_seat;
    bool result = false;

    ଯଦି (seat && seat->data_device) {
        SDL_WaylandDataDevice *data_device = seat->data_device;
        ଯଦି (data_device->selection_source) {
            result = SDL_HasInternalClipboardData(_this, mime_type);
        } ଅନ୍ୟଥା {
            result = Wayland_DataOfferHasMIME(data_device->selection_offer, mime_type);
        }
    }
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ଅଚଳ ଅକ୍ଷର *ଅଚଳ *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types)
{
    *ଅଙ୍କ_mime_types = SDL_arraysize(text_mime_types);
    ଫେରନ୍ତୁ text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->last_implicit_grab_seat;
    bool result;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ଯଦି (!seat && !WAYLAND_wl_list_empty(&video_data->seat_list)) {
        seat = wl_container_of(video_data->seat_list.next, seat, link);
    }

    video_data->current_primary_selection_seat = seat;

    ଯଦି (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ଯଦି (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_data);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            result = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            ଯଦି (!result) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } ଅନ୍ୟଥା {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = ଖାଲି;
            result = true;
        }
    } ଅନ୍ୟଥା {
        result = SDL_SetError("Primary selection not supported");
    }
    ଫେରନ୍ତୁ result;
}

ଅକ୍ଷର *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    ଅକ୍ଷର *text = ଖାଲି;
    size_t length = 0;

    ଯଦି (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ଯଦି (primary_selection_device->selection_source) {
            text = Wayland_PrimarySelectionSourceGetData(primary_selection_device->selection_source, TEXT_MIME, &length);
        } ଅନ୍ୟଥା {
            ପାଇଁ (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                ଯଦି (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &length);
                    ଭାଙ୍ଗ;
                }
            }
        }
    }

    ଯଦି (!text) {
        text = SDL_strdup("");
    }

    ଫେରନ୍ତୁ text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;
    SDL_WaylandSeat *seat = video_data->current_primary_selection_seat;
    bool result = false;

    ଯଦି (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ଯଦି (primary_selection_device->selection_source) {
            result = true;
        } ଅନ୍ୟଥା {
            size_t mime_ଗଣନା = 0;
            ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types = Wayland_GetTextMimeTypes(_this, &mime_ଗଣନା);
            ପାଇଁ (size_t i = 0; i < mime_ଗଣନା; i++) {
                ଯଦି (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    result = true;
                    ଭାଙ୍ଗ;
                }
            }
        }
    }
    ଫେରନ୍ତୁ result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
