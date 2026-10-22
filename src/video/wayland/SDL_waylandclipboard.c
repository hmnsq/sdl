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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylanddatamanager.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"

bool Wayland_سېټ_Clipboard_معلومات(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->وروستی_implicit_grab_seat;
    bool پایله = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_تشه(&video_معلومات->seat_list)) {
        seat = wl_container_د(video_معلومات->seat_list.بل, seat, link);
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
                    Wayland_معلومات_سرچینه_Destroy(s->معلومات_device->selection_سرچینه);
                    s->معلومات_device->selection_سرچینه = عدم;
                }

                Wayland_معلومات_Offer_Destroy(s->معلومات_device->selection_offer);
                s->معلومات_device->selection_offer = عدم;
            }
        }

        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;

        إذا (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_معلومات_سرچینه *سرچینه = Wayland_معلومات_سرچینه_Create(video_معلومات);
            Wayland_معلومات_سرچینه_سېټ_Callback(سرچینه, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            پایله = Wayland_معلومات_Device_سېټ_Selection_سرچینه(معلومات_device, سرچینه, (ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types);
            إذا (!پایله) {
                Wayland_معلومات_سرچینه_Destroy(سرچینه);
            }
        } وإلا {
            Wayland_معلومات_سرچینه_Destroy(معلومات_device->selection_سرچینه);
            معلومات_device->selection_سرچینه = عدم;
            پایله = true;
        }
    }

    أرجع پایله;
}

فراغ *Wayland_Get_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *اوږدتیا)
{
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->current_معلومات_offer_seat;
    فراغ *بفر_2 = عدم;

    إذا (seat && seat->معلومات_device) {
        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;
        إذا (معلومات_device->selection_سرچینه) {
            بفر_2 = SDL_Get_دننی_Clipboard_معلومات(_this, mime_type, اوږدتیا);
        } وإلا إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->selection_offer, mime_type)) {
            بفر_2 = Wayland_معلومات_Offer_Receive(معلومات_device->selection_offer, mime_type, اوږدتیا);
        }
    }

    أرجع بفر_2;
}

bool Wayland_Has_Clipboard_معلومات(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->current_معلومات_offer_seat;
    bool پایله = false;

    إذا (seat && seat->معلومات_device) {
        SDL_Wayland_معلومات_Device *معلومات_device = seat->معلومات_device;
        إذا (معلومات_device->selection_سرچینه) {
            پایله = SDL_Has_دننی_Clipboard_معلومات(_this, mime_type);
        } وإلا {
            پایله = Wayland_معلومات_Offer_Has_MIME(معلومات_device->selection_offer, mime_type);
        }
    }
    أرجع پایله;
}

ساكن ثابت حرف *ثابت متن_mime_types[] = {
    متن_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ثابت حرف *ثابت *Wayland_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    *عدد_mime_types = SDL_arraysize(متن_mime_types);
    أرجع متن_mime_types;
}

bool Wayland_سېټ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->وروستی_implicit_grab_seat;
    bool پایله;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_تشه(&video_معلومات->seat_list)) {
        seat = wl_container_د(video_معلومات->seat_list.بل, seat, link);
    }

    video_معلومات->current_primary_selection_seat = seat;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (متن[0] != '\0') {
            SDL_Wayland_Primary_Selection_سرچینه *سرچینه = Wayland_Primary_Selection_سرچینه_Create(video_معلومات);
            Wayland_Primary_Selection_سرچینه_سېټ_Callback(سرچینه, SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن));

            پایله = Wayland_Primary_Selection_Device_سېټ_Selection(primary_selection_device, سرچینه, متن_mime_types, SDL_arraysize(متن_mime_types));
            إذا (!پایله) {
                Wayland_Primary_Selection_سرچینه_Destroy(سرچینه);
            }
        } وإلا {
            Wayland_Primary_Selection_سرچینه_Destroy(seat->primary_selection_device->selection_سرچینه);
            seat->primary_selection_device->selection_سرچینه = عدم;
            پایله = true;
        }
    } وإلا {
        پایله = SDL_سېټ_Error("Primary selection not supported");
    }
    أرجع پایله;
}

حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->current_primary_selection_seat;
    حرف *متن = عدم;
    size_t اوږدتیا = 0;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_سرچینه) {
            متن = Wayland_Primary_Selection_سرچینه_Get_معلومات(primary_selection_device->selection_سرچینه, متن_MIME, &اوږدتیا);
        } وإلا {
            لكل (size_t i = 0; i < SDL_arraysize(متن_mime_types); i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, متن_mime_types[i])) {
                    متن = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, متن_mime_types[i], &اوږدتیا);
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
    SDL_Video_معلومات *video_معلومات = _this->دننی;
    SDL_WaylandSeat *seat = video_معلومات->current_primary_selection_seat;
    bool پایله = false;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_سرچینه) {
            پایله = true;
        } وإلا {
            size_t mime_شمېر = 0;
            ثابت حرف *ثابت *mime_types = Wayland_Get_متن_Mime_Types(_this, &mime_شمېر);
            لكل (size_t i = 0; i < mime_شمېر; i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    پایله = true;
                    اكسر;
                }
            }
        }
    }
    أرجع پایله;
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND
