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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandDataDevice SDL_WaylandDataDevice;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandUserdata
{
    ಶೂನ್ಯ *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ wl_data_offer *offer;
    ಸಂರಚನಾ wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    ಸಂರಚನಾ wl_callback *callback;
    ಪೂರ್ಣಾಙ್ಕ read_fd;
} SDL_WaylandDataOffer;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ಧ್ರುವ ವರ್ಣ *text_mime_type;
    ಸಂರಚನಾ wl_callback *cleanup_callback;
    Wayland_JobID id;

    ಸಂರಚನಾ wl_list link;
} Wayland_DropData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ zwp_primary_selection_offer_v1 *offer;
    ಸಂರಚನಾ wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ಸಂರಚನಾ SDL_WaylandDataDevice
{
    ಸಂರಚನಾ wl_data_device *data_device;
    ಸಂರಚನಾ SDL_WaylandSeat *seat;
    ವರ್ಣ *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ಧ್ರುವ ವರ್ಣ *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    ಸಂರಚನಾ wl_surface *dnd_surface;
    ಸಂರಚನಾ wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

ಸಂರಚನಾ SDL_WaylandPrimarySelectionDevice
{
    ಸಂರಚನಾ zwp_primary_selection_device_v1 *primary_selection_device;
    ಸಂರಚನಾ SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
ಬಾಹ್ಯ SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
ಬಾಹ್ಯ SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
ಬಾಹ್ಯ ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, ಪೂರ್ಣಾಙ್ಕ fd);
ಬಾಹ್ಯ ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, ಪೂರ್ಣಾಙ್ಕ fd);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata, Uint32 sequence);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
ಬಾಹ್ಯ bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener *completion_listener, ಶೂನ್ಯ *userdata);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length);
ಬಾಹ್ಯ bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
ಬಾಹ್ಯ bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type);
ಬಾಹ್ಯ bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type);
ಬಾಹ್ಯ bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
ಬಾಹ್ಯ bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ **mime_types, size_t mime_ಎಣಿಕೆ);
ಬಾಹ್ಯ bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t mime_ಎಣಿಕೆ);

#endif // SDL_waylanddatamanager_h_
