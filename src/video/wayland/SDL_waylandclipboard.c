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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

#ضمن "SDL_waylanddatamanager.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "../../events/SDL_events_c.h"

bool Wayland_مجموعه_Clipboard_داده(SDL_VideoDevice *_this)
{
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->آخرین_implicit_grab_seat;
    bool نتیجه = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالی(&video_داده->seat_list)) {
        seat = wl_container_از(video_داده->seat_list.بعدی, seat, link);
    }

    video_داده->current_داده_offer_seat = seat;

    إذا (seat && seat->داده_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_داده->seat_list, link) {
            إذا (s->داده_device) {
                إذا (s != seat) {
                    Wayland_داده_منبع_Destroy(s->داده_device->selection_منبع);
                    s->داده_device->selection_منبع = عدم;
                }

                Wayland_داده_Offer_Destroy(s->داده_device->selection_offer);
                s->داده_device->selection_offer = عدم;
            }
        }

        SDL_Wayland_داده_Device *داده_device = seat->داده_device;

        إذا (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_داده_منبع *منبع = Wayland_داده_منبع_Create(video_داده);
            Wayland_داده_منبع_مجموعه_Callback(منبع, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            نتیجه = Wayland_داده_Device_مجموعه_Selection_منبع(داده_device, منبع, (ثابت حرف **)_this->clipboard_mime_types, _this->رقم_clipboard_mime_types);
            إذا (!نتیجه) {
                Wayland_داده_منبع_Destroy(منبع);
            }
        } وإلا {
            Wayland_داده_منبع_Destroy(داده_device->selection_منبع);
            داده_device->selection_منبع = عدم;
            نتیجه = true;
        }
    }

    أرجع نتیجه;
}

فراغ *Wayland_Get_Clipboard_داده(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *درازی)
{
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->current_داده_offer_seat;
    فراغ *میانگیر_2 = عدم;

    إذا (seat && seat->داده_device) {
        SDL_Wayland_داده_Device *داده_device = seat->داده_device;
        إذا (داده_device->selection_منبع) {
            میانگیر_2 = SDL_Get_داخلی_Clipboard_داده(_this, mime_type, درازی);
        } وإلا إذا (Wayland_داده_Offer_Has_MIME(داده_device->selection_offer, mime_type)) {
            میانگیر_2 = Wayland_داده_Offer_Receive(داده_device->selection_offer, mime_type, درازی);
        }
    }

    أرجع میانگیر_2;
}

bool Wayland_Has_Clipboard_داده(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->current_داده_offer_seat;
    bool نتیجه = false;

    إذا (seat && seat->داده_device) {
        SDL_Wayland_داده_Device *داده_device = seat->داده_device;
        إذا (داده_device->selection_منبع) {
            نتیجه = SDL_Has_داخلی_Clipboard_داده(_this, mime_type);
        } وإلا {
            نتیجه = Wayland_داده_Offer_Has_MIME(داده_device->selection_offer, mime_type);
        }
    }
    أرجع نتیجه;
}

ساكن ثابت حرف *ثابت متن_mime_types[] = {
    متن_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

ثابت حرف *ثابت *Wayland_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *رقم_mime_types)
{
    *رقم_mime_types = SDL_arraysize(متن_mime_types);
    أرجع متن_mime_types;
}

bool Wayland_مجموعه_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->آخرین_implicit_grab_seat;
    bool نتیجه;

    // If no implicit grab is available yet, just attach it to the first available seat.
    إذا (!seat && !WAYLAND_wl_list_خالی(&video_داده->seat_list)) {
        seat = wl_container_از(video_داده->seat_list.بعدی, seat, link);
    }

    video_داده->current_primary_selection_seat = seat;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (متن[0] != '\0') {
            SDL_Wayland_Primary_Selection_منبع *منبع = Wayland_Primary_Selection_منبع_Create(video_داده);
            Wayland_Primary_Selection_منبع_مجموعه_Callback(منبع, SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن));

            نتیجه = Wayland_Primary_Selection_Device_مجموعه_Selection(primary_selection_device, منبع, متن_mime_types, SDL_arraysize(متن_mime_types));
            إذا (!نتیجه) {
                Wayland_Primary_Selection_منبع_Destroy(منبع);
            }
        } وإلا {
            Wayland_Primary_Selection_منبع_Destroy(seat->primary_selection_device->selection_منبع);
            seat->primary_selection_device->selection_منبع = عدم;
            نتیجه = true;
        }
    } وإلا {
        نتیجه = SDL_مجموعه_Error("Primary selection not supported");
    }
    أرجع نتیجه;
}

حرف *Wayland_Get_Primary_Selection_متن(SDL_VideoDevice *_this)
{
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->current_primary_selection_seat;
    حرف *متن = عدم;
    size_t درازی = 0;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_منبع) {
            متن = Wayland_Primary_Selection_منبع_Get_داده(primary_selection_device->selection_منبع, متن_MIME, &درازی);
        } وإلا {
            لكل (size_t i = 0; i < SDL_arraysize(متن_mime_types); i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, متن_mime_types[i])) {
                    متن = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, متن_mime_types[i], &درازی);
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
    SDL_Video_داده *video_داده = _this->داخلی;
    SDL_WaylandSeat *seat = video_داده->current_primary_selection_seat;
    bool نتیجه = false;

    إذا (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        إذا (primary_selection_device->selection_منبع) {
            نتیجه = true;
        } وإلا {
            size_t mime_شمار = 0;
            ثابت حرف *ثابت *mime_types = Wayland_Get_متن_Mime_Types(_this, &mime_شمار);
            لكل (size_t i = 0; i < mime_شمار; i++) {
                إذا (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    نتیجه = true;
                    اكسر;
                }
            }
        }
    }
    أرجع نتیجه;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND
