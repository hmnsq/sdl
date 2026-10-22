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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylanddatamanager.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"

bool Wayland_سیٹ_Clipboard_انکڑے(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->آخری_implicit_grab_seat;
    bool نتیجہ = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالی_تھاواں(&video_انکڑے->seat_list)) {
        seat = wl_container_دا(video_انکڑے->seat_list.اگلا, seat, link);
    }

    video_انکڑے->current_انکڑے_offer_seat = seat;

    إذا (seat && seat->انکڑے_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_انکڑے->seat_list, link) {
            إذا (s->انکڑے_device) {
                إذا (s != seat) {
                    Wayland_انکڑے_سروت_Destroy(s->انکڑے_device->selection_سروت);
                    s->انکڑے_device->selection_سروت = عدم;
                }

                Wayland_انکڑے_Offer_Destroy(s->انکڑے_device->selection_offer);
                s->انکڑے_device->selection_offer = عدم;
            }
        }

        SDL_Wayland_انکڑے_Device *انکڑے_device = seat->انکڑے_device;

        إذا (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_انکڑے_سروت *سروت = Wayland_انکڑے_سروت_Create(video_انکڑے);
            Wayland_انکڑے_سروت_سیٹ_Callback(سروت, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            نتیجہ = Wayland_انکڑے_Device_سیٹ_Selection_سروت(انکڑے_device, سروت, (ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types);
            إذا (!نتیجہ) {
                Wayland_انکڑے_سروت_Destroy(سروت);
            }
        } وإلا {
            Wayland_انکڑے_سروت_Destroy(انکڑے_device->selection_سروت);
            انکڑے_device->selection_سروت = عدم;
            نتیجہ = true;
        }
    }

    أرجع نتیجہ;
}

فراغ *Wayland_Get_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *لمائی)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->current_انکڑے_offer_seat;
    فراغ *بفر_2 = عدم;

    إذا (seat && seat->انکڑے_device) {
        SDL_Wayland_انکڑے_Device *انکڑے_device = seat->انکڑے_device;
        إذا (انکڑے_device->selection_سروت) {
            بفر_2 = SDL_Get_اندرونی_Clipboard_انکڑے(_this, mime_type, لمائی);
        } وإلا إذا (Wayland_انکڑے_Offer_Has_MIME(انکڑے_device->selection_offer, mime_type)) {
            بفر_2 = Wayland_انکڑے_Offer_Receive(انکڑے_device->selection_offer, mime_type, لمائی);
        }
    }

    أرجع بفر_2;
}

bool Wayland_Has_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->current_انکڑے_offer_seat;
    bool نتیجہ = false;

    إذا (seat && seat->انکڑے_device) {
        SDL_Wayland_انکڑے_Device *انکڑے_device = seat->انکڑے_device;
        إذا (انکڑے_device->selection_سروت) {
            نتیجہ = SDL_Has_اندرونی_Clipboard_انکڑے(_this, mime_type);
        } وإلا {
            نتیجہ = Wayland_انکڑے_Offer_Has_MIME(انکڑے_device->selection_offer, mime_type);
        }
    }
    أرجع نتیجہ;
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

bool Wayland_سیٹ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->آخری_implicit_grab_seat;
    bool نتیجہ;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالی_تھاواں(&video_انکڑے->seat_list)) {
        seat = wl_container_دا(video_انکڑے->seat_list.اگلا, seat, link);
    }

    video_انکڑے->current_primary_selection_seat = seat;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (متن[0] != '\0') {
            SDL_Wayland_Primary_Selection_سروت *سروت = Wayland_Primary_Selection_سروت_Create(video_انکڑے);
            Wayland_Primary_Selection_سروت_سیٹ_Callback(سروت, SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن));

            نتیجہ = Wayland_Primary_Selection_Device_سیٹ_Selection(primary_selection_device, سروت, متن_mime_types, SDL_arraysize(متن_mime_types));
            إذا (!نتیجہ) {
                Wayland_Primary_Selection_سروت_Destroy(سروت);
            }
        } وإلا {
            Wayland_Primary_Selection_سروت_Destroy(seat->primary_selection_device->selection_سروت);
            seat->primary_selection_device->selection_سروت = عدم;
            نتیجہ = true;
        }
    } وإلا {
        نتیجہ = SDL_سیٹ_Error("Primary selection not supported");
    }
    أرجع نتیجہ;
}

حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->current_primary_selection_seat;
    حرف *متن = عدم;
    size_t لمائی = 0;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_سروت) {
            متن = Wayland_Primary_Selection_سروت_Get_انکڑے(primary_selection_device->selection_سروت, متن_MIME, &لمائی);
        } وإلا {
            لكل (size_t i = 0; i < SDL_arraysize(متن_mime_types); i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, متن_mime_types[i])) {
                    متن = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, متن_mime_types[i], &لمائی);
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
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat = video_انکڑے->current_primary_selection_seat;
    bool نتیجہ = false;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_سروت) {
            نتیجہ = true;
        } وإلا {
            size_t mime_گنتی = 0;
            ثابت حرف *ثابت *mime_types = Wayland_Get_متن_Mime_Types(_this, &mime_گنتی);
            لكل (size_t i = 0; i < mime_گنتی; i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    نتیجہ = true;
                    اكسر;
                }
            }
        }
    }
    أرجع نتیجہ;
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND
