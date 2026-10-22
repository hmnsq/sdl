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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylanddatamanager.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"

bool Wayland_سيٽ_Clipboard_معلومات(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->آخري_implicit_grab_seat;
    bool نتيجو = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالي_جايون(&video_معلومات->seat_list)) {
        seat = wl_container_جو(video_معلومات->seat_list.ايندڙ, seat, link);
    }

    video_معلومات->current_معلومات_offer_seat = seat;

    إذا (seat && seat->معلومات_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_معلومات->seat_list, link) {
            إذا (s->معلومات_device) {
                إذا (s != seat) {
                    Wayland_معلومات_ذريعو_Destroy(s->معلومات_device->selection_ذريعو);
                    s->معلومات_device->selection_ذريعو = عدم;
                }

                Wayland_معلومات_Offer_Destroy(s->معلومات_device->selection_offer);
                s->معلومات_device->selection_offer = عدم;
            }
        }

        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;

        إذا (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_معلومات_ذريعو *ذريعو = Wayland_معلومات_ذريعو_Create(video_معلومات);
            Wayland_معلومات_ذريعو_سيٽ_Callback(ذريعو, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            نتيجو = Wayland_معلومات_Device_سيٽ_Selection_ذريعو(معلومات_device, ذريعو, (ثابت حرف **)_this->clipboard_mime_types, _this->انگ_clipboard_mime_types);
            إذا (!نتيجو) {
                Wayland_معلومات_ذريعو_Destroy(ذريعو);
            }
        } وإلا {
            Wayland_معلومات_ذريعو_Destroy(معلومات_device->selection_ذريعو);
            معلومات_device->selection_ذريعو = عدم;
            نتيجو = true;
        }
    }

    أرجع نتيجو;
}

فراغ *Wayland_Get_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->current_معلومات_offer_seat;
    فراغ *بفر_2 = عدم;

    إذا (seat && seat->معلومات_device) {
        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;
        إذا (معلومات_device->selection_ذريعو) {
            بفر_2 = SDL_Get_اندروني_Clipboard_معلومات(_this, mime_type, ڊيگهائي);
        } وإلا إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->selection_offer, mime_type)) {
            بفر_2 = Wayland_معلومات_Offer_Receive(معلومات_device->selection_offer, mime_type, ڊيگهائي);
        }
    }

    أرجع بفر_2;
}

bool Wayland_Has_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->current_معلومات_offer_seat;
    bool نتيجو = false;

    إذا (seat && seat->معلومات_device) {
        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;
        إذا (معلومات_device->selection_ذريعو) {
            نتيجو = SDL_Has_اندروني_Clipboard_معلومات(_this, mime_type);
        } وإلا {
            نتيجو = Wayland_معلومات_Offer_Has_MIME(معلومات_device->selection_offer, mime_type);
        }
    }
    أرجع نتيجو;
}

ساكن ثابت حرف *ثابت متن_mime_types[] = {
    متن_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ثابت حرف *ثابت *Wayland_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *انگ_mime_types)
{
    *انگ_mime_types = SDL_arraysize(متن_mime_types);
    أرجع متن_mime_types;
}

bool Wayland_سيٽ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->آخري_implicit_grab_seat;
    bool نتيجو;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالي_جايون(&video_معلومات->seat_list)) {
        seat = wl_container_جو(video_معلومات->seat_list.ايندڙ, seat, link);
    }

    video_معلومات->current_primary_selection_seat = seat;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (متن[0] != '\0') {
            SDL_Wayland_Primary_Selection_ذريعو *ذريعو = Wayland_Primary_Selection_ذريعو_Create(video_معلومات);
            Wayland_Primary_Selection_ذريعو_سيٽ_Callback(ذريعو, SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن));

            نتيجو = Wayland_Primary_Selection_Device_سيٽ_Selection(primary_selection_device, ذريعو, متن_mime_types, SDL_arraysize(متن_mime_types));
            إذا (!نتيجو) {
                Wayland_Primary_Selection_ذريعو_Destroy(ذريعو);
            }
        } وإلا {
            Wayland_Primary_Selection_ذريعو_Destroy(seat->primary_selection_device->selection_ذريعو);
            seat->primary_selection_device->selection_ذريعو = عدم;
            نتيجو = true;
        }
    } وإلا {
        نتيجو = SDL_سيٽ_Error("Primary selection not supported");
    }
    أرجع نتيجو;
}

حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->current_primary_selection_seat;
    حرف *متن = عدم;
    size_t ڊيگهائي = 0;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_ذريعو) {
            متن = Wayland_Primary_Selection_ذريعو_Get_معلومات(primary_selection_device->selection_ذريعو, متن_MIME, &ڊيگهائي);
        } وإلا {
            لكل (size_t i = 0; i < SDL_arraysize(متن_mime_types); i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, متن_mime_types[i])) {
                    متن = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, متن_mime_types[i], &ڊيگهائي);
                    اكسر;
                }
            }
        }
    }

    إذا (!متن) {
        متن = SDL_strdup("");
    }

    أرجع متن;
}

bool Wayland_Has_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;
    SDL_WaylandSeat *seat = video_معلومات->current_primary_selection_seat;
    bool نتيجو = false;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_ذريعو) {
            نتيجو = true;
        } وإلا {
            size_t mime_ڳڻپ = 0;
            ثابت حرف *ثابت *mime_types = Wayland_Get_متن_Mime_Types(_this, &mime_ڳڻپ);
            لكل (size_t i = 0; i < mime_ڳڻپ; i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    نتيجو = true;
                    اكسر;
                }
            }
        }
    }
    أرجع نتيجو;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND
