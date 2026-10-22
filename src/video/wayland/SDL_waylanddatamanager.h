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

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

प्रकारनिर्देश संरचना SDL_WaylandDataDevice SDL_WaylandDataDevice;
प्रकारनिर्देश संरचना SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

प्रकारनिर्देश संरचना SDL_WaylandUserdata
{
    शून्य *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

प्रकारनिर्देश संरचना
{
    संरचना wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

प्रकारनिर्देश संरचना
{
    संरचना zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

प्रकारनिर्देश संरचना
{
    संरचना wl_data_offer *offer;
    संरचना wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    संरचना wl_callback *callback;
    पूर्णाङ्क read_fd;
} SDL_WaylandDataOffer;

प्रकारनिर्देश संरचना Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ध्रुव वर्ण *text_mime_type;
    संरचना wl_callback *cleanup_callback;
    Wayland_JobID id;

    संरचना wl_list link;
} Wayland_DropData;

प्रकारनिर्देश संरचना
{
    संरचना zwp_primary_selection_offer_v1 *offer;
    संरचना wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

संरचना SDL_WaylandDataDevice
{
    संरचना wl_data_device *data_device;
    संरचना SDL_WaylandSeat *seat;
    वर्ण *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ध्रुव वर्ण *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    संरचना wl_surface *dnd_surface;
    संरचना wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

संरचना SDL_WaylandPrimarySelectionDevice
{
    संरचना zwp_primary_selection_device_v1 *primary_selection_device;
    संरचना SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
बाह्य SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
बाह्य SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
बाह्य ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd);
बाह्य ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd);
बाह्य शून्य Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata, Uint32 sequence);
बाह्य शून्य Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata);
बाह्य शून्य *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ध्रुव वर्ण *mime_type, size_t *length);
बाह्य शून्य *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, size_t *length);
बाह्य शून्य Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
बाह्य शून्य Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
बाह्य bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type, ध्रुव संरचना wl_callback_listener *completion_listener, शून्य *userdata);
बाह्य शून्य *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
बाह्य शून्य *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type, size_t *length);
बाह्य शून्य *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type, size_t *length);
बाह्य bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य शून्य Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
बाह्य bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type);
बाह्य शून्य Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
बाह्य शून्य Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
बाह्य bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ध्रुव वर्ण **mime_types, size_t mime_गिनती);
बाह्य bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *ध्रुव *mime_types, size_t mime_गिनती);

#endif // SDL_waylanddatamanager_h_
