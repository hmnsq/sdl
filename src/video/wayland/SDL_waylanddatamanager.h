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

#यदि_अपरिभाषितम् SDL_waylanddatamanager_h_
#परिभाषय SDL_waylanddatamanager_h_

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandwindow.h"

#परिभाषय TEXT_MIME            "text/plain;charset=utf-8"
#परिभाषय FILE_MIME            "text/uri-list"
#परिभाषय FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#परिभाषय SDL_दत्त_ORIGIN_MIME "application/x-sdl3-source-id"

प्रकारनिर्देश संरचना SDL_Wayland_दत्त_Device SDL_Wayland_दत्त_Device;
प्रकारनिर्देश संरचना SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

प्रकारनिर्देश संरचना SDL_WaylandUserdata
{
    शून्य *दत्त;
    Uint32 sequence;
} SDL_WaylandUserdata;

प्रकारनिर्देश संरचना
{
    संरचना wl_दत्त_source *source;
    SDL_Wayland_दत्त_Device *दत्त_device;
    SDL_Clipboard_दत्त_Callback दत्त_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_दत्त_Source;

प्रकारनिर्देश संरचना
{
    संरचना zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_दत्त_Callback दत्त_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

प्रकारनिर्देश संरचना
{
    संरचना wl_दत्त_offer *offer;
    संरचना wl_array mimes;
    SDL_Wayland_दत्त_Device *दत्त_device;

    // Callback data for queued receive.
    संरचना wl_callback *callback;
    पूर्णाङ्क read_fd;
} SDL_Wayland_दत्त_Offer;

प्रकारनिर्देश संरचना Wayland_Drop_दत्त
{
    SDL_Wayland_दत्त_Offer *offer;
    SDL_गवाक्षः *dnd_गवाक्षः;
    ध्रुव वर्ण *text_mime_type;
    संरचना wl_callback *cleanup_callback;
    Wayland_JobID id;

    संरचना wl_list link;
} Wayland_Drop_दत्त;

प्रकारनिर्देश संरचना
{
    संरचना zwp_primary_selection_offer_v1 *offer;
    संरचना wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

संरचना SDL_Wayland_दत्त_Device
{
    संरचना wl_दत्त_device *दत्त_device;
    संरचना SDL_WaylandSeat *seat;
    वर्ण *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_दत्त_Offer *drag_offer;
    SDL_Wayland_दत्त_Offer *selection_offer;
    ध्रुव वर्ण *text_mime_type;
    bool has_mime_file;
    SDL_गवाक्षः *dnd_गवाक्षः;
    संरचना wl_surface *dnd_surface;
    संरचना wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_दत्त_Source *selection_source;
};

संरचना SDL_WaylandPrimarySelectionDevice
{
    संरचना zwp_primary_selection_device_v1 *primary_selection_device;
    संरचना SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
बाह्य SDL_Wayland_दत्त_Source *Wayland_दत्त_Source_Create(SDL_Video_दत्त *video_दत्त);
बाह्य SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_दत्त *video_दत्त);
बाह्य ssize_t Wayland_दत्त_Source_Send(SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd);
बाह्य ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd);
बाह्य शून्य Wayland_दत्त_Source_समुच्चयः_Callback(SDL_Wayland_दत्त_Source *source, SDL_Clipboard_दत्त_Callback दत्त_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata, Uint32 sequence);
बाह्य शून्य Wayland_Primary_Selection_Source_समुच्चयः_Callback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_दत्त_Callback दत्त_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata);
बाह्य शून्य *Wayland_दत्त_Source_Get_दत्त(SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण *mime_type, size_t *दीर्घता);
बाह्य शून्य *Wayland_Primary_Selection_Source_Get_दत्त(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, size_t *दीर्घता);
बाह्य शून्य Wayland_दत्त_Source_Destroy(SDL_Wayland_दत्त_Source *source);
बाह्य शून्य Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
बाह्य bool Wayland_दत्त_Offer_Request_दत्त_From_Self(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type, ध्रुव संरचना wl_callback_listener *completion_listener, शून्य *userdata);
बाह्य शून्य *Wayland_दत्त_Offer_Get_दत्त_From_Self(SDL_Wayland_दत्त_Offer *offer, size_t *दीर्घता);
बाह्य शून्य *Wayland_दत्त_Offer_Receive(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type, size_t *दीर्घता);
बाह्य शून्य *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type, size_t *दीर्घता);
बाह्य bool Wayland_दत्त_Offer_Has_MIME(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type);
बाह्य शून्य Wayland_दत्त_Device_समुच्चयः_Selection_Offer(SDL_Wayland_दत्त_Device *दत्त_device, SDL_Wayland_दत्त_Offer *offer);
बाह्य bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य bool Wayland_दत्त_Offer_सङ्कलय_MIME(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type);
बाह्य bool Wayland_Primary_Selection_Offer_सङ्कलय_MIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य शून्य Wayland_दत्त_Offer_Destroy(SDL_Wayland_दत्त_Offer *offer);
बाह्य शून्य Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
बाह्य bool Wayland_दत्त_Device_समुच्चयः_Selection_Source(SDL_Wayland_दत्त_Device *device, SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण **mime_types, size_t mime_गणनम्);
बाह्य bool Wayland_Primary_Selection_Device_समुच्चयः_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *ध्रुव *mime_types, size_t mime_गणनम्);

#यदि_अन्तः // SDL_waylanddatamanager_h_
