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

#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

തരനിർവചനം ഘടന SDL_WaylandDataDevice SDL_WaylandDataDevice;
തരനിർവചനം ഘടന SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

തരനിർവചനം ഘടന SDL_WaylandUserdata
{
    ശൂന്യം *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

തരനിർവചനം ഘടന
{
    ഘടന wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

തരനിർവചനം ഘടന
{
    ഘടന zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

തരനിർവചനം ഘടന
{
    ഘടന wl_data_offer *offer;
    ഘടന wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    ഘടന wl_callback *callback;
    പൂർണ്ണസംഖ്യ read_fd;
} SDL_WaylandDataOffer;

തരനിർവചനം ഘടന Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    സ്ഥിരം അക്ഷരം *text_mime_type;
    ഘടന wl_callback *cleanup_callback;
    Wayland_JobID id;

    ഘടന wl_list link;
} Wayland_DropData;

തരനിർവചനം ഘടന
{
    ഘടന zwp_primary_selection_offer_v1 *offer;
    ഘടന wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ഘടന SDL_WaylandDataDevice
{
    ഘടന wl_data_device *data_device;
    ഘടന SDL_WaylandSeat *seat;
    അക്ഷരം *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    സ്ഥിരം അക്ഷരം *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    ഘടന wl_surface *dnd_surface;
    ഘടന wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

ഘടന SDL_WaylandPrimarySelectionDevice
{
    ഘടന zwp_primary_selection_device_v1 *primary_selection_device;
    ഘടന SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
ബാഹ്യ SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
ബാഹ്യ SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
ബാഹ്യ ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം *mime_type, പൂർണ്ണസംഖ്യ fd);
ബാഹ്യ ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, സ്ഥിരം അക്ഷരം *mime_type, പൂർണ്ണസംഖ്യ fd);
ബാഹ്യ ശൂന്യം Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ശൂന്യം *userdata, Uint32 sequence);
ബാഹ്യ ശൂന്യം Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ശൂന്യം *userdata);
ബാഹ്യ ശൂന്യം *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം *mime_type, size_t *length);
ബാഹ്യ ശൂന്യം *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, സ്ഥിരം അക്ഷരം *mime_type, size_t *length);
ബാഹ്യ ശൂന്യം Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
ബാഹ്യ ശൂന്യം Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
ബാഹ്യ bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, സ്ഥിരം ഘടന wl_callback_listener *completion_listener, ശൂന്യം *userdata);
ബാഹ്യ ശൂന്യം *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
ബാഹ്യ ശൂന്യം *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, size_t *length);
ബാഹ്യ ശൂന്യം *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, size_t *length);
ബാഹ്യ bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type);
ബാഹ്യ ശൂന്യം Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
ബാഹ്യ bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type);
ബാഹ്യ bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type);
ബാഹ്യ bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type);
ബാഹ്യ ശൂന്യം Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
ബാഹ്യ ശൂന്യം Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
ബാഹ്യ bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം **mime_types, size_t mime_എണ്ണം);
ബാഹ്യ bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, സ്ഥിരം അക്ഷരം *സ്ഥിരം *mime_types, size_t mime_എണ്ണം);

#endif // SDL_waylanddatamanager_h_
