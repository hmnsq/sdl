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

#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

પ્રકારવ્યાખ્યા સંરચના SDL_WaylandDataDevice SDL_WaylandDataDevice;
પ્રકારવ્યાખ્યા સંરચના SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

પ્રકારવ્યાખ્યા સંરચના SDL_WaylandUserdata
{
    શૂન્ય *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના wl_data_offer *offer;
    સંરચના wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    સંરચના wl_callback *callback;
    પૂર્ણાંક read_fd;
} SDL_WaylandDataOffer;

પ્રકારવ્યાખ્યા સંરચના Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    અચલ અક્ષર *text_mime_type;
    સંરચના wl_callback *cleanup_callback;
    Wayland_JobID id;

    સંરચના wl_list link;
} Wayland_DropData;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના zwp_primary_selection_offer_v1 *offer;
    સંરચના wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

સંરચના SDL_WaylandDataDevice
{
    સંરચના wl_data_device *data_device;
    સંરચના SDL_WaylandSeat *seat;
    અક્ષર *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    અચલ અક્ષર *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    સંરચના wl_surface *dnd_surface;
    સંરચના wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

સંરચના SDL_WaylandPrimarySelectionDevice
{
    સંરચના zwp_primary_selection_device_v1 *primary_selection_device;
    સંરચના SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
બાહ્ય SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
બાહ્ય SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
બાહ્ય ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, અચલ અક્ષર *mime_type, પૂર્ણાંક fd);
બાહ્ય ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, અચલ અક્ષર *mime_type, પૂર્ણાંક fd);
બાહ્ય શૂન્ય Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, શૂન્ય *userdata, Uint32 sequence);
બાહ્ય શૂન્ય Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, શૂન્ય *userdata);
બાહ્ય શૂન્ય *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, અચલ અક્ષર *mime_type, size_t *length);
બાહ્ય શૂન્ય *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, અચલ અક્ષર *mime_type, size_t *length);
બાહ્ય શૂન્ય Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
બાહ્ય શૂન્ય Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
બાહ્ય bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type, અચલ સંરચના wl_callback_listener *completion_listener, શૂન્ય *userdata);
બાહ્ય શૂન્ય *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
બાહ્ય શૂન્ય *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type, size_t *length);
બાહ્ય શૂન્ય *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type, size_t *length);
બાહ્ય bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type);
બાહ્ય શૂન્ય Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
બાહ્ય bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type);
બાહ્ય bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type);
બાહ્ય bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type);
બાહ્ય શૂન્ય Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
બાહ્ય શૂન્ય Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
બાહ્ય bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, અચલ અક્ષર **mime_types, size_t mime_ગણતરી);
બાહ્ય bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, અચલ અક્ષર *અચલ *mime_types, size_t mime_ગણતરી);

#endif // SDL_waylanddatamanager_h_
