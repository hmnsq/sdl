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

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

تعریفنوع ساختار SDL_WaylandDataDevice SDL_WaylandDataDevice;
تعریفنوع ساختار SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

تعریفنوع ساختار SDL_WaylandUserdata
{
    تهی *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

تعریفنوع ساختار
{
    ساختار wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

تعریفنوع ساختار
{
    ساختار zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

تعریفنوع ساختار
{
    ساختار wl_data_offer *offer;
    ساختار wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    ساختار wl_callback *callback;
    صحیح read_fd;
} SDL_WaylandDataOffer;

تعریفنوع ساختار Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ثابت نویسه *text_mime_type;
    ساختار wl_callback *cleanup_callback;
    Wayland_JobID id;

    ساختار wl_list link;
} Wayland_DropData;

تعریفنوع ساختار
{
    ساختار zwp_primary_selection_offer_v1 *offer;
    ساختار wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ساختار SDL_WaylandDataDevice
{
    ساختار wl_data_device *data_device;
    ساختار SDL_WaylandSeat *seat;
    نویسه *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ثابت نویسه *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    ساختار wl_surface *dnd_surface;
    ساختار wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

ساختار SDL_WaylandPrimarySelectionDevice
{
    ساختار zwp_primary_selection_device_v1 *primary_selection_device;
    ساختار SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
بیرونی SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
بیرونی SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
بیرونی ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ثابت نویسه *mime_type, صحیح fd);
بیرونی ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ثابت نویسه *mime_type, صحیح fd);
بیرونی تهی Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, تهی *userdata, Uint32 sequence);
بیرونی تهی Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, تهی *userdata);
بیرونی تهی *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ثابت نویسه *mime_type, size_t *length);
بیرونی تهی *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ثابت نویسه *mime_type, size_t *length);
بیرونی تهی Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
بیرونی تهی Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
بیرونی bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type, ثابت ساختار wl_callback_listener *completion_listener, تهی *userdata);
بیرونی تهی *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
بیرونی تهی *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type, size_t *length);
بیرونی تهی *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type, size_t *length);
بیرونی bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type);
بیرونی تهی Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
بیرونی bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type);
بیرونی bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type);
بیرونی bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type);
بیرونی تهی Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
بیرونی تهی Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
بیرونی bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ثابت نویسه **mime_types, size_t mime_شمار);
بیرونی bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ثابت نویسه *ثابت *mime_types, size_t mime_شمار);

#endif // SDL_waylanddatamanager_h_
