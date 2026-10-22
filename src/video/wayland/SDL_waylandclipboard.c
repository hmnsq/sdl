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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "SDL_waylanddatamanager.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylandclipboard.h"
#समावेश "../SDL_clipboard_c.h"
#समावेश "../../events/SDL_events_c.h"

bool Wayland_Set_Clipboard_तथ्य(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->last_implicit_grab_seat;
    bool परिणाम = false;

    // If no implicit grab is available yet, just attach it to the first available seat.
    अगर (!seat && !WAYLAND_wl_list_empty(&video_तथ्य->seat_list)) {
        seat = wl_container_of(video_तथ्य->seat_list.अग्र, seat, link);
    }

    video_तथ्य->current_तथ्य_offer_seat = seat;

    अगर (seat && seat->तथ्य_device) {
        /* Clear references to the clipboard held by other seats, as they are about to become invalid.
         * For the target seat, the new source data is set before clearing the old source, as some
         * clipboard managers prefer this behavior.
         */
        SDL_WaylandSeat *s;
        wl_list_for_each (s, &video_तथ्य->seat_list, link) {
            अगर (s->तथ्य_device) {
                अगर (s != seat) {
                    Wayland_तथ्य_Source_Destroy(s->तथ्य_device->selection_source);
                    s->तथ्य_device->selection_source = शून्य;
                }

                Wayland_तथ्य_Offer_Destroy(s->तथ्य_device->selection_offer);
                s->तथ्य_device->selection_offer = शून्य;
            }
        }

        SDL_Wayland_तथ्य_Device *तथ्य_device = seat->तथ्य_device;

        अगर (_this->clipboard_callback && _this->clipboard_mime_types) {
            SDL_Wayland_तथ्य_Source *source = Wayland_तथ्य_Source_Create(video_तथ्य);
            Wayland_तथ्य_Source_Set_Callback(source, _this->clipboard_callback, _this->clipboard_cleanup, _this->clipboard_userdata, _this->clipboard_sequence);

            परिणाम = Wayland_तथ्य_Device_Set_Selection_Source(तथ्य_device, source, (स्थिर अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types);
            अगर (!परिणाम) {
                Wayland_तथ्य_Source_Destroy(source);
            }
        } अन्यथा {
            Wayland_तथ्य_Source_Destroy(तथ्य_device->selection_source);
            तथ्य_device->selection_source = शून्य;
            परिणाम = true;
        }
    }

    वापस परिणाम;
}

व्योम *Wayland_Get_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->current_तथ्य_offer_seat;
    व्योम *बफर_2 = शून्य;

    अगर (seat && seat->तथ्य_device) {
        SDL_Wayland_तथ्य_Device *तथ्य_device = seat->तथ्य_device;
        अगर (तथ्य_device->selection_source) {
            बफर_2 = SDL_Get_Internal_Clipboard_तथ्य(_this, mime_type, लंबाई);
        } अन्यथा अगर (Wayland_तथ्य_Offer_Has_MIME(तथ्य_device->selection_offer, mime_type)) {
            बफर_2 = Wayland_तथ्य_Offer_Receive(तथ्य_device->selection_offer, mime_type, लंबाई);
        }
    }

    वापस बफर_2;
}

bool Wayland_Has_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->current_तथ्य_offer_seat;
    bool परिणाम = false;

    अगर (seat && seat->तथ्य_device) {
        SDL_Wayland_तथ्य_Device *तथ्य_device = seat->तथ्य_device;
        अगर (तथ्य_device->selection_source) {
            परिणाम = SDL_Has_Internal_Clipboard_तथ्य(_this, mime_type);
        } अन्यथा {
            परिणाम = Wayland_तथ्य_Offer_Has_MIME(तथ्य_device->selection_offer, mime_type);
        }
    }
    वापस परिणाम;
}

अटल स्थिर अक्षर *स्थिर text_mime_types[] = {
    TEXT_MIME,
    "text/plain",
    "TEXT",
    "UTF8_STRING",
    "STRING"
};

स्थिर अक्षर *स्थिर *Wayland_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types)
{
    *अंक_mime_types = SDL_arraysize(text_mime_types);
    वापस text_mime_types;
}

bool Wayland_SetPrimarySelectionText(SDL_VideoDevice *_this, स्थिर अक्षर *text)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->last_implicit_grab_seat;
    bool परिणाम;

    // If no implicit grab is available yet, just attach it to the first available seat.
    अगर (!seat && !WAYLAND_wl_list_empty(&video_तथ्य->seat_list)) {
        seat = wl_container_of(video_तथ्य->seat_list.अग्र, seat, link);
    }

    video_तथ्य->current_primary_selection_seat = seat;

    अगर (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        अगर (text[0] != '\0') {
            SDL_WaylandPrimarySelectionSource *source = Wayland_PrimarySelectionSourceCreate(video_तथ्य);
            Wayland_PrimarySelectionSourceSetCallback(source, SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text));

            परिणाम = Wayland_PrimarySelectionDeviceSetSelection(primary_selection_device, source, text_mime_types, SDL_arraysize(text_mime_types));
            अगर (!परिणाम) {
                Wayland_PrimarySelectionSourceDestroy(source);
            }
        } अन्यथा {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
            seat->primary_selection_device->selection_source = शून्य;
            परिणाम = true;
        }
    } अन्यथा {
        परिणाम = SDL_SetError("Primary selection not supported");
    }
    वापस परिणाम;
}

अक्षर *Wayland_GetPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->current_primary_selection_seat;
    अक्षर *text = शून्य;
    माप_प्रकार लंबाई = 0;

    अगर (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        अगर (primary_selection_device->selection_source) {
            text = Wayland_Primary_Selection_Source_Get_तथ्य(primary_selection_device->selection_source, TEXT_MIME, &लंबाई);
        } अन्यथा {
            क्रम (माप_प्रकार i = 0; i < SDL_arraysize(text_mime_types); i++) {
                अगर (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, text_mime_types[i])) {
                    text = Wayland_PrimarySelectionOfferReceive(primary_selection_device->selection_offer, text_mime_types[i], &लंबाई);
                    अवरोध;
                }
            }
        }
    }

    अगर (!text) {
        text = SDL_strdup("");
    }

    वापस text;
}

bool Wayland_HasPrimarySelectionText(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;
    SDL_WaylandSeat *seat = video_तथ्य->current_primary_selection_seat;
    bool परिणाम = false;

    अगर (seat && seat->primary_selection_device) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = seat->primary_selection_device;
        अगर (primary_selection_device->selection_source) {
            परिणाम = true;
        } अन्यथा {
            माप_प्रकार mime_गिनती = 0;
            स्थिर अक्षर *स्थिर *mime_types = Wayland_GetTextMimeTypes(_this, &mime_गिनती);
            क्रम (माप_प्रकार i = 0; i < mime_गिनती; i++) {
                अगर (Wayland_PrimarySelectionOfferHasMIME(primary_selection_device->selection_offer, mime_types[i])) {
                    परिणाम = true;
                    अवरोध;
                }
            }
        }
    }
    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
