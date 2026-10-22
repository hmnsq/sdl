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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_WaylandDataDevice SDL_WaylandDataDevice;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_WaylandUserdata
{
    ଶୂନ୍ୟ *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା wl_data_offer *offer;
    ସଂରଚନା wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    ସଂରଚନା wl_callback *callback;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_fd;
} SDL_WaylandDataOffer;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ଅଚଳ ଅକ୍ଷର *text_mime_type;
    ସଂରଚନା wl_callback *cleanup_callback;
    Wayland_JobID id;

    ସଂରଚନା wl_list link;
} Wayland_DropData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା zwp_primary_selection_offer_v1 *offer;
    ସଂରଚନା wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ସଂରଚନା SDL_WaylandDataDevice
{
    ସଂରଚନା wl_data_device *data_device;
    ସଂରଚନା SDL_WaylandSeat *seat;
    ଅକ୍ଷର *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ଅଚଳ ଅକ୍ଷର *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    ସଂରଚନା wl_surface *dnd_surface;
    ସଂରଚନା wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

ସଂରଚନା SDL_WaylandPrimarySelectionDevice
{
    ସଂରଚନା zwp_primary_selection_device_v1 *primary_selection_device;
    ସଂରଚନା SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
ବାହ୍ୟ SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
ବାହ୍ୟ SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
ବାହ୍ୟ ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd);
ବାହ୍ୟ ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ଶୂନ୍ୟ *userdata, Uint32 sequence);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ଶୂନ୍ୟ *userdata);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
ବାହ୍ୟ bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, ଅଚଳ ସଂରଚନା wl_callback_listener *completion_listener, ଶୂନ୍ୟ *userdata);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length);
ବାହ୍ୟ bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
ବାହ୍ୟ bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type);
ବାହ୍ୟ bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type);
ବାହ୍ୟ bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
ବାହ୍ୟ bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର **mime_types, size_t mime_ଗଣନା);
ବାହ୍ୟ bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types, size_t mime_ଗଣନା);

#endif // SDL_waylanddatamanager_h_
