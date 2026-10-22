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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "SDL_waylanddatamanager.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylandclipboard.h"
#అన్తర్భావ "../SDL_clipboard_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

bool Wayland_సమితి_Clipboard_దత్తాంశం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->చివరి_implicit_grab_seat;
    bool ఫలితం = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ఒకవేళ (!seat && !WAYLAND_wl_list_ఖాళీలు(&video_దత్తాంశం->seat_list)) {
        seat = wl_container_యొక్క(video_దత్తాంశం->seat_list.తదుపరి, seat, link);
    }

    video_దత్తాంశం->current_దత్తాంశం_offer_seat = seat;

    ఒకవేళ (seat && seat->దత్తాంశం_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_దత్తాంశం->seat_list, link) {
            ఒకవేళ (s->దత్తాంశం_device) {
                ఒకవేళ (s != seat) {
                    Wayland_దత్తాంశం_ఆధారం_Destroy(s->దత్తాంశం_device->selection_ఆధారం);
                    s->దత్తాంశం_device->selection_ఆధారం = ఖాళీ;
                }

                Wayland_దత్తాంశం_Offer_Destroy(s->దత్తాంశం_device->selection_offer);
                s->దత్తాంశం_device->selection_offer = ఖాళీ;
            }
        }

        SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = seat->దత్తాంశం_device;

        ఒకవేళ (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం = Wayland_దత్తాంశం_ఆధారం_Create(video_దత్తాంశం);
            Wayland_దత్తాంశం_ఆధారం_సమితి_Callback(ఆధారం, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            ఫలితం = Wayland_దత్తాంశం_Device_సమితి_Selection_ఆధారం(దత్తాంశం_device, ఆధారం, (స్థిరరాశి అక్షరం **)_this->clipboard_mime_types, _this->అంకె_clipboard_mime_types);
            ఒకవేళ (!ఫలితం) {
                Wayland_దత్తాంశం_ఆధారం_Destroy(ఆధారం);
            }
        } లేకపోతే {
            Wayland_దత్తాంశం_ఆధారం_Destroy(దత్తాంశం_device->selection_ఆధారం);
            దత్తాంశం_device->selection_ఆధారం = ఖాళీ;
            ఫలితం = true;
        }
    }

    తిరిగి ఫలితం;
}

శూన్య *Wayland_Get_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->current_దత్తాంశం_offer_seat;
    శూన్య *బఫరు_2 = ఖాళీ;

    ఒకవేళ (seat && seat->దత్తాంశం_device) {
        SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = seat->దత్తాంశం_device;
        ఒకవేళ (దత్తాంశం_device->selection_ఆధారం) {
            బఫరు_2 = SDL_Get_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type, నిడివి);
        } లేకపోతే ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(దత్తాంశం_device->selection_offer, mime_type)) {
            బఫరు_2 = Wayland_దత్తాంశం_Offer_Receive(దత్తాంశం_device->selection_offer, mime_type, నిడివి);
        }
    }

    తిరిగి బఫరు_2;
}

bool Wayland_Has_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->current_దత్తాంశం_offer_seat;
    bool ఫలితం = false;

    ఒకవేళ (seat && seat->దత్తాంశం_device) {
        SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = seat->దత్తాంశం_device;
        ఒకవేళ (దత్తాంశం_device->selection_ఆధారం) {
            ఫలితం = SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type);
        } లేకపోతే {
            ఫలితం = Wayland_దత్తాంశం_Offer_Has_MIME(దత్తాంశం_device->selection_offer, mime_type);
        }
    }
    తిరిగి ఫలితం;
}

స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి పాఠ్యం_mime_types[] = {
    పాఠ్యం_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

స్థిరరాశి అక్షరం *స్థిరరాశి *Wayland_Get_పాఠ్యం_Mime_Types(SDL_VideoDevice *_this, size_t *అంకె_mime_types)
{
    *అంకె_mime_types = SDL_arraysize(పాఠ్యం_mime_types);
    తిరిగి పాఠ్యం_mime_types;
}

bool Wayland_సమితి_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->చివరి_implicit_grab_seat;
    bool ఫలితం;

    // If no implicit grab is available yet, just attach it to the first available seat.
    ఒకవేళ (!seat && !WAYLAND_wl_list_ఖాళీలు(&video_దత్తాంశం->seat_list)) {
        seat = wl_container_యొక్క(video_దత్తాంశం->seat_list.తదుపరి, seat, link);
    }

    video_దత్తాంశం->current_primary_selection_seat = seat;

    ఒకవేళ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ఒకవేళ (పాఠ్యం[0] != '\0') {
            SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం = Wayland_Primary_Selection_ఆధారం_Create(video_దత్తాంశం);
            Wayland_Primary_Selection_ఆధారం_సమితి_Callback(ఆధారం, SDL_Clipboard_పాఠ్యం_Callback, SDL_free, SDL_strdup(పాఠ్యం));

            ఫలితం = Wayland_Primary_Selection_Device_సమితి_Selection(primary_selection_device, ఆధారం, పాఠ్యం_mime_types, SDL_arraysize(పాఠ్యం_mime_types));
            ఒకవేళ (!ఫలితం) {
                Wayland_Primary_Selection_ఆధారం_Destroy(ఆధారం);
            }
        } లేకపోతే {
            Wayland_Primary_Selection_ఆధారం_Destroy(seat->primary_selection_device->selection_ఆధారం);
            seat->primary_selection_device->selection_ఆధారం = ఖాళీ;
            ఫలితం = true;
        }
    } లేకపోతే {
        ఫలితం = SDL_సమితి_Error("Primary selection not supported");
    }
    తిరిగి ఫలితం;
}

అక్షరం *Wayland_Get_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->current_primary_selection_seat;
    అక్షరం *పాఠ్యం = ఖాళీ;
    size_t నిడివి = 0;

    ఒకవేళ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ఒకవేళ (primary_selection_device->selection_ఆధారం) {
            పాఠ్యం = Wayland_Primary_Selection_ఆధారం_Get_దత్తాంశం(primary_selection_device->selection_ఆధారం, పాఠ్యం_MIME, &నిడివి);
        } లేకపోతే {
            కొరకు (size_t i = 0; i < SDL_arraysize(పాఠ్యం_mime_types); i++) {
                ఒకవేళ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, పాఠ్యం_mime_types[i])) {
                    పాఠ్యం = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, పాఠ్యం_mime_types[i], &నిడివి);
                    ఆపు;
                }
            }
        }
    }

    ఒకవేళ (!పాఠ్యం) {
        పాఠ్యం = SDL_strdup("");
    }

    తిరిగి పాఠ్యం;
}

bool Wayland_Has_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat = video_దత్తాంశం->current_primary_selection_seat;
    bool ఫలితం = false;

    ఒకవేళ (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        ఒకవేళ (primary_selection_device->selection_ఆధారం) {
            ఫలితం = true;
        } లేకపోతే {
            size_t mime_లెక్క = 0;
            స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types = Wayland_Get_పాఠ్యం_Mime_Types(_this, &mime_లెక్క);
            కొరకు (size_t i = 0; i < mime_లెక్క; i++) {
                ఒకవేళ (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    ఫలితం = true;
                    ఆపు;
                }
            }
        }
    }
    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
