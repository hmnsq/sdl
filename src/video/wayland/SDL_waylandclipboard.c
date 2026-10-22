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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "SDL_waylanddatamanager.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandclipboard.h"
#شامل "../SDL_clipboard_c.h"
#شامل "../../events/SDL_events_c.h"

bool Wayland_سیٹ_Clipboard_ڈیٹا(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->آخری_implicit_grab_seat;
    bool نتیجہ = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    اگر (!seat && !WAYLAND_wl_list_خالی_خانے(&video_ڈیٹا->seat_list)) {
        seat = wl_container_کا(video_ڈیٹا->seat_list.اگلا, seat, link);
    }

    video_ڈیٹا->current_ڈیٹا_offer_seat = seat;

    اگر (seat && seat->ڈیٹا_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_ڈیٹا->seat_list, link) {
            اگر (s->ڈیٹا_device) {
                اگر (s != seat) {
                    Wayland_ڈیٹا_ماخذ_Destroy(s->ڈیٹا_device->selection_ماخذ);
                    s->ڈیٹا_device->selection_ماخذ = تہی;
                }

                Wayland_ڈیٹا_Offer_Destroy(s->ڈیٹا_device->selection_offer);
                s->ڈیٹا_device->selection_offer = تہی;
            }
        }

        SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = seat->ڈیٹا_device;

        اگر (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_ڈیٹا_ماخذ *ماخذ = Wayland_ڈیٹا_ماخذ_Create(video_ڈیٹا);
            Wayland_ڈیٹا_ماخذ_سیٹ_Callback(ماخذ, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            نتیجہ = Wayland_ڈیٹا_Device_سیٹ_Selection_ماخذ(ڈیٹا_device, ماخذ, (ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types);
            اگر (!نتیجہ) {
                Wayland_ڈیٹا_ماخذ_Destroy(ماخذ);
            }
        } ورنہ {
            Wayland_ڈیٹا_ماخذ_Destroy(ڈیٹا_device->selection_ماخذ);
            ڈیٹا_device->selection_ماخذ = تہی;
            نتیجہ = true;
        }
    }

    واپس نتیجہ;
}

خالی *Wayland_Get_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *لمبائی)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->current_ڈیٹا_offer_seat;
    خالی *بفر_2 = تہی;

    اگر (seat && seat->ڈیٹا_device) {
        SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = seat->ڈیٹا_device;
        اگر (ڈیٹا_device->selection_ماخذ) {
            بفر_2 = SDL_Get_اندرونی_Clipboard_ڈیٹا(_this, mime_type, لمبائی);
        } ورنہ اگر (Wayland_ڈیٹا_Offer_Has_MIME(ڈیٹا_device->selection_offer, mime_type)) {
            بفر_2 = Wayland_ڈیٹا_Offer_Receive(ڈیٹا_device->selection_offer, mime_type, لمبائی);
        }
    }

    واپس بفر_2;
}

bool Wayland_Has_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->current_ڈیٹا_offer_seat;
    bool نتیجہ = false;

    اگر (seat && seat->ڈیٹا_device) {
        SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = seat->ڈیٹا_device;
        اگر (ڈیٹا_device->selection_ماخذ) {
            نتیجہ = SDL_Has_اندرونی_Clipboard_ڈیٹا(_this, mime_type);
        } ورنہ {
            نتیجہ = Wayland_ڈیٹا_Offer_Has_MIME(ڈیٹا_device->selection_offer, mime_type);
        }
    }
    واپس نتیجہ;
}

ساکن ثابت حرف *ثابت متن_mime_types[] = {
    متن_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ثابت حرف *ثابت *Wayland_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    *عدد_mime_types = SDL_arraysize(متن_mime_types);
    واپس متن_mime_types;
}

bool Wayland_سیٹ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->آخری_implicit_grab_seat;
    bool نتیجہ;

    // If no implicit grab is available yet, just attach it to the first available seat.
    اگر (!seat && !WAYLAND_wl_list_خالی_خانے(&video_ڈیٹا->seat_list)) {
        seat = wl_container_کا(video_ڈیٹا->seat_list.اگلا, seat, link);
    }

    video_ڈیٹا->current_primary_selection_seat = seat;

    اگر (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        اگر (متن[0] != '\0') {
            SDL_Wayland_Primary_Selection_ماخذ *ماخذ = Wayland_Primary_Selection_ماخذ_Create(video_ڈیٹا);
            Wayland_Primary_Selection_ماخذ_سیٹ_Callback(ماخذ, SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن));

            نتیجہ = Wayland_Primary_Selection_Device_سیٹ_Selection(primary_selection_device, ماخذ, متن_mime_types, SDL_arraysize(متن_mime_types));
            اگر (!نتیجہ) {
                Wayland_Primary_Selection_ماخذ_Destroy(ماخذ);
            }
        } ورنہ {
            Wayland_Primary_Selection_ماخذ_Destroy(seat->primary_selection_device->selection_ماخذ);
            seat->primary_selection_device->selection_ماخذ = تہی;
            نتیجہ = true;
        }
    } ورنہ {
        نتیجہ = SDL_سیٹ_Error("Primary selection not supported");
    }
    واپس نتیجہ;
}

حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->current_primary_selection_seat;
    حرف *متن = تہی;
    size_t لمبائی = 0;

    اگر (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        اگر (primary_selection_device->selection_ماخذ) {
            متن = Wayland_Primary_Selection_ماخذ_Get_ڈیٹا(primary_selection_device->selection_ماخذ, متن_MIME, &لمبائی);
        } ورنہ {
            برائے (size_t i = 0; i < SDL_arraysize(متن_mime_types); i++) {
                اگر (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, متن_mime_types[i])) {
                    متن = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, متن_mime_types[i], &لمبائی);
                    توڑو;
                }
            }
        }
    }

    اگر (!متن) {
        متن = SDL_strdup("");
    }

    واپس متن;
}

bool Wayland_Has_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat = video_ڈیٹا->current_primary_selection_seat;
    bool نتیجہ = false;

    اگر (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        اگر (primary_selection_device->selection_ماخذ) {
            نتیجہ = true;
        } ورنہ {
            size_t mime_گنتی = 0;
            ثابت حرف *ثابت *mime_types = Wayland_Get_متن_Mime_Types(_this, &mime_گنتی);
            برائے (size_t i = 0; i < mime_گنتی; i++) {
                اگر (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    نتیجہ = true;
                    توڑو;
                }
            }
        }
    }
    واپس نتیجہ;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
