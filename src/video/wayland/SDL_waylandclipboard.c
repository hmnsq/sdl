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

#अन्तर्भाव "SDL_waylanddatamanager.h"
#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylandclipboard.h"
#अन्तर्भाव "../SDL_clipboard_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

bool Wayland_समुच्चयः_Clipboard_दत्त(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->चरमः_implicit_grab_seat;
    bool परिणाम = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    यदि (!seat && !WAYLAND_wl_list_रिक्तानि(&video_दत्त->seat_list)) {
        seat = wl_container_सम्बन्धि(video_दत्त->seat_list.अग्र, seat, link);
    }

    video_दत्त->current_दत्त_offer_seat = seat;

    यदि (seat && seat->दत्त_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_दत्त->seat_list, link) {
            यदि (s->दत्त_device) {
                यदि (s != seat) {
                    Wayland_दत्त_Source_Destroy(s->दत्त_device->selection_source);
                    s->दत्त_device->selection_source = रिक्त;
                }

                Wayland_दत्त_Offer_Destroy(s->दत्त_device->selection_offer);
                s->दत्त_device->selection_offer = रिक्त;
            }
        }

        SDL_Wayland_दत्त_Device *दत्त_device = seat->दत्त_device;

        यदि (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_दत्त_Source *source = Wayland_दत्त_Source_Create(video_दत्त);
            Wayland_दत्त_Source_समुच्चयः_Callback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            परिणाम = Wayland_दत्त_Device_समुच्चयः_Selection_Source(दत्त_device, source, (ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types);
            यदि (!परिणाम) {
                Wayland_दत्त_Source_Destroy(source);
            }
        } अन्यथा {
            Wayland_दत्त_Source_Destroy(दत्त_device->selection_source);
            दत्त_device->selection_source = रिक्त;
            परिणाम = true;
        }
    }

    प्रत्यागम परिणाम;
}

शून्य *Wayland_Get_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *दीर्घता)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->current_दत्त_offer_seat;
    शून्य *बफर_2 = रिक्त;

    यदि (seat && seat->दत्त_device) {
        SDL_Wayland_दत्त_Device *दत्त_device = seat->दत्त_device;
        यदि (दत्त_device->selection_source) {
            बफर_2 = SDL_Get_आन्तरिकम्_Clipboard_दत्त(_this, mime_type, दीर्घता);
        } अन्यथा यदि (Wayland_दत्त_Offer_Has_MIME(दत्त_device->selection_offer, mime_type)) {
            बफर_2 = Wayland_दत्त_Offer_Receive(दत्त_device->selection_offer, mime_type, दीर्घता);
        }
    }

    प्रत्यागम बफर_2;
}

bool Wayland_Has_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->current_दत्त_offer_seat;
    bool परिणाम = false;

    यदि (seat && seat->दत्त_device) {
        SDL_Wayland_दत्त_Device *दत्त_device = seat->दत्त_device;
        यदि (दत्त_device->selection_source) {
            परिणाम = SDL_Has_आन्तरिकम्_Clipboard_दत्त(_this, mime_type);
        } अन्यथा {
            परिणाम = Wayland_दत्त_Offer_Has_MIME(दत्त_device->selection_offer, mime_type);
        }
    }
    प्रत्यागम परिणाम;
}

स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ध्रुव वर्ण *ध्रुव *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types)
{
    *अङ्कः_mime_types = SDL_arraysize(text_mime_types);
    प्रत्यागम text_mime_types;
}

bool Wayland_समुच्चयः_Primary_Selection_Text(SDL_VideoDevice *_this, ध्रुव वर्ण *text)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->चरमः_implicit_grab_seat;
    bool परिणाम;

    // If no implicit grab is available yet, just attach it to the first available seat.
    यदि (!seat && !WAYLAND_wl_list_रिक्तानि(&video_दत्त->seat_list)) {
        seat = wl_container_सम्बन्धि(video_दत्त->seat_list.अग्र, seat, link);
    }

    video_दत्त->current_primary_selection_seat = seat;

    यदि (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        यदि (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_दत्त);
            Wayland_Primary_Selection_Source_समुच्चयः_Callback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            परिणाम = Wayland_Primary_Selection_Device_समुच्चयः_Selection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            यदि (!परिणाम) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } अन्यथा {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = रिक्त;
            परिणाम = true;
        }
    } अन्यथा {
        परिणाम = SDL_समुच्चयः_Error("Primary selection not supported");
    }
    प्रत्यागम परिणाम;
}

वर्ण *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->current_primary_selection_seat;
    वर्ण *text = रिक्त;
    size_t दीर्घता = 0;

    यदि (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        यदि (primary_selection_device->selection_source) {
            text = Wayland_Primary_Selection_Source_Get_दत्त(primary_selection_device->selection_source, TEXT_MIME, &दीर्घता);
        } अन्यथा {
            प्रति (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                यदि (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &दीर्घता);
                    भङ्ग;
                }
            }
        }
    }

    यदि (!text) {
        text = SDL_strdup("");
    }

    प्रत्यागम text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat = video_दत्त->current_primary_selection_seat;
    bool परिणाम = false;

    यदि (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        यदि (primary_selection_device->selection_source) {
            परिणाम = true;
        } अन्यथा {
            size_t mime_गणनम् = 0;
            ध्रुव वर्ण *ध्रुव *mime_types = Wayland_GetTextMimeTypes(_this, &mime_गणनम्);
            प्रति (size_t i = 0; i < mime_गणनम्; i++) {
                यदि (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    परिणाम = true;
                    भङ्ग;
                }
            }
        }
    }
    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
