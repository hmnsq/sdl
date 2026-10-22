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

#অন্তর্ভাব "SDL_waylanddatamanager.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"
#অন্তর্ভাব "SDL_waylandclipboard.h"
#অন্তর্ভাব "../SDL_clipboard_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"

bool Wayland_Set_Clipboard_তথ্য(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->last_implicit_grab_seat;
    bool ফলাফল = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    যদি (!seat && !WAYLAND_wl_list_empty(&video_তথ্য->seat_list)) {
        seat = wl_container_of(video_তথ্য->seat_list.পরবর্তী, seat, link);
    }

    video_তথ্য->current_তথ্য_offer_seat = seat;

    যদি (seat && seat->তথ্য_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_তথ্য->seat_list, link) {
            যদি (s->তথ্য_device) {
                যদি (s != seat) {
                    Wayland_তথ্য_Source_Destroy(s->তথ্য_device->selection_source);
                    s->তথ্য_device->selection_source = ফাঁকা;
                }

                Wayland_তথ্য_Offer_Destroy(s->তথ্য_device->selection_offer);
                s->তথ্য_device->selection_offer = ফাঁকা;
            }
        }

        SDL_Wayland_তথ্য_Device *তথ্য_device = seat->তথ্য_device;

        যদি (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_তথ্য_Source *source = Wayland_তথ্য_Source_Create(video_তথ্য);
            Wayland_তথ্য_Source_Set_Callback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            ফলাফল = Wayland_তথ্য_Device_Set_Selection_Source(তথ্য_device, source, (ধ্রুবক অক্ষর **)_this->clipboard_mime_types, _this->অঙ্ক_clipboard_mime_types);
            যদি (!ফলাফল) {
                Wayland_তথ্য_Source_Destroy(source);
            }
        } অন্যথা {
            Wayland_তথ্য_Source_Destroy(তথ্য_device->selection_source);
            তথ্য_device->selection_source = ফাঁকা;
            ফলাফল = true;
        }
    }

    ফেরত ফলাফল;
}

শূন্য *Wayland_Get_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->current_তথ্য_offer_seat;
    শূন্য *বাফার_2 = ফাঁকা;

    যদি (seat && seat->তথ্য_device) {
        SDL_Wayland_তথ্য_Device *তথ্য_device = seat->তথ্য_device;
        যদি (তথ্য_device->selection_source) {
            বাফার_2 = SDL_Get_Internal_Clipboard_তথ্য(_this, mime_type, দৈর্ঘ্য);
        } অন্যথা যদি (Wayland_তথ্য_Offer_Has_MIME(তথ্য_device->selection_offer, mime_type)) {
            বাফার_2 = Wayland_তথ্য_Offer_Receive(তথ্য_device->selection_offer, mime_type, দৈর্ঘ্য);
        }
    }

    ফেরত বাফার_2;
}

bool Wayland_Has_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->current_তথ্য_offer_seat;
    bool ফলাফল = false;

    যদি (seat && seat->তথ্য_device) {
        SDL_Wayland_তথ্য_Device *তথ্য_device = seat->তথ্য_device;
        যদি (তথ্য_device->selection_source) {
            ফলাফল = SDL_Has_Internal_Clipboard_তথ্য(_this, mime_type);
        } অন্যথা {
            ফলাফল = Wayland_তথ্য_Offer_Has_MIME(তথ্য_device->selection_offer, mime_type);
        }
    }
    ফেরত ফলাফল;
}

স্থির ধ্রুবক অক্ষর *ধ্রুবক text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ধ্রুবক অক্ষর *ধ্রুবক *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types)
{
    *অঙ্ক_mime_types = SDL_arraysize(text_mime_types);
    ফেরত text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->last_implicit_grab_seat;
    bool ফলাফল;

    // If no implicit grab is available yet, just attach it to the first available seat.
    যদি (!seat && !WAYLAND_wl_list_empty(&video_তথ্য->seat_list)) {
        seat = wl_container_of(video_তথ্য->seat_list.পরবর্তী, seat, link);
    }

    video_তথ্য->current_primary_selection_seat = seat;

    যদি (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        যদি (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_তথ্য);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            ফলাফল = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            যদি (!ফলাফল) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } অন্যথা {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = ফাঁকা;
            ফলাফল = true;
        }
    } অন্যথা {
        ফলাফল = SDL_SetError("Primary selection not supported");
    }
    ফেরত ফলাফল;
}

অক্ষর *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->current_primary_selection_seat;
    অক্ষর *text = ফাঁকা;
    size_t দৈর্ঘ্য = 0;

    যদি (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        যদি (primary_selection_device->selection_source) {
            text = Wayland_Primary_Selection_Source_Get_তথ্য(primary_selection_device->selection_source, TEXT_MIME, &দৈর্ঘ্য);
        } অন্যথা {
            জন্য (size_t i = 0; i < SDL_arraysize(text_mime_types); i++) {
                যদি (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &দৈর্ঘ্য);
                    বিরতি;
                }
            }
        }
    }

    যদি (!text) {
        text = SDL_strdup("");
    }

    ফেরত text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;
    SDL_WaylandSeat *seat = video_তথ্য->current_primary_selection_seat;
    bool ফলাফল = false;

    যদি (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        যদি (primary_selection_device->selection_source) {
            ফলাফল = true;
        } অন্যথা {
            size_t mime_গুনতি = 0;
            ধ্রুবক অক্ষর *ধ্রুবক *mime_types = Wayland_GetTextMimeTypes(_this, &mime_গুনতি);
            জন্য (size_t i = 0; i < mime_গুনতি; i++) {
                যদি (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    ফলাফল = true;
                    বিরতি;
                }
            }
        }
    }
    ফেরত ফলাফল;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
