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

#include "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#include "SDL_waylandvideo.h"
#include "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

typedef sa_nracanaa SDL_WaylandDataDevice SDL_WaylandDataDevice;
typedef sa_nracanaa SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

typedef sa_nracanaa SDL_WaylandUserdata
{
    void *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

typedef sa_nracanaa
{
    sa_nracanaa wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

typedef sa_nracanaa
{
    sa_nracanaa zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

typedef sa_nracanaa
{
    sa_nracanaa wl_data_offer *offer;
    sa_nracanaa wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    sa_nracanaa wl_callback *callback;
    จำนวนเต็ม read_fd;
} SDL_WaylandDataOffer;

typedef sa_nracanaa Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    const var_na *text_mime_type;
    sa_nracanaa wl_callback *cleanup_callback;
    Wayland_JobID id;

    sa_nracanaa wl_list link;
} Wayland_DropData;

typedef sa_nracanaa
{
    sa_nracanaa zwp_primary_selection_offer_v1 *offer;
    sa_nracanaa wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

sa_nracanaa SDL_WaylandDataDevice
{
    sa_nracanaa wl_data_device *data_device;
    sa_nracanaa SDL_WaylandSeat *seat;
    var_na *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    const var_na *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    sa_nracanaa wl_surface *dnd_surface;
    sa_nracanaa wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

sa_nracanaa SDL_WaylandPrimarySelectionDevice
{
    sa_nracanaa zwp_primary_selection_device_v1 *primary_selection_device;
    sa_nracanaa SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
extern SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
extern SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
extern ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, const var_na *mime_type, จำนวนเต็ม fd);
extern ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, const var_na *mime_type, จำนวนเต็ม fd);
extern void Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata, Uint32 sequence);
extern void Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata);
extern void *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, const var_na *mime_type, size_t *length);
extern void *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, const var_na *mime_type, size_t *length);
extern void Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
extern void Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
extern bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, const var_na *mime_type, const sa_nracanaa wl_callback_listener *completion_listener, void *userdata);
extern void *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
extern void *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, const var_na *mime_type, size_t *length);
extern void *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type, size_t *length);
extern bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, const var_na *mime_type);
extern void Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
extern bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type);
extern bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, const var_na *mime_type);
extern bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type);
extern void Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
extern void Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
extern bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, const var_na **mime_types, size_t mime_count);
extern bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, const var_na *const *mime_types, size_t mime_count);

#endif // SDL_waylanddatamanager_h_
