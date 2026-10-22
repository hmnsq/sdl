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

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

تعريفنوع بنية SDL_WaylandDataDevice SDL_WaylandDataDevice;
تعريفنوع بنية SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

تعريفنوع بنية SDL_WaylandUserdata
{
    فراغ *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

تعريفنوع بنية
{
    بنية wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

تعريفنوع بنية
{
    بنية zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

تعريفنوع بنية
{
    بنية wl_data_offer *offer;
    بنية wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    بنية wl_callback *callback;
    صحيح read_fd;
} SDL_WaylandDataOffer;

تعريفنوع بنية Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ثابت حرف *text_mime_type;
    بنية wl_callback *cleanup_callback;
    Wayland_JobID id;

    بنية wl_list link;
} Wayland_DropData;

تعريفنوع بنية
{
    بنية zwp_primary_selection_offer_v1 *offer;
    بنية wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

بنية SDL_WaylandDataDevice
{
    بنية wl_data_device *data_device;
    بنية SDL_WaylandSeat *seat;
    حرف *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ثابت حرف *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    بنية wl_surface *dnd_surface;
    بنية wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

بنية SDL_WaylandPrimarySelectionDevice
{
    بنية zwp_primary_selection_device_v1 *primary_selection_device;
    بنية SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
خارجي SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
خارجي SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
خارجي ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ثابت حرف *mime_type, صحيح fd);
خارجي ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ثابت حرف *mime_type, صحيح fd);
خارجي فراغ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence);
خارجي فراغ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata);
خارجي فراغ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ثابت حرف *mime_type, size_t *length);
خارجي فراغ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ثابت حرف *mime_type, size_t *length);
خارجي فراغ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
خارجي فراغ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
خارجي bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata);
خارجي فراغ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
خارجي فراغ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type, size_t *length);
خارجي فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *length);
خارجي bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
خارجي bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
خارجي فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
خارجي bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ثابت حرف **mime_types, size_t mime_تعداد);
خارجي bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ثابت حرف *ثابت *mime_types, size_t mime_تعداد);

#endif // SDL_waylanddatamanager_h_
