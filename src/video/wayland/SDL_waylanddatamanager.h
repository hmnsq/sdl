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

#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#অন্তর্ভাৱ "SDL_waylandvideo.h"
#অন্তর্ভাৱ "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_DATA_ORIGIN_MIME "application/x-sdl3-source-id"

প্রকারনির্দেশ সংরচনা SDL_WaylandDataDevice SDL_WaylandDataDevice;
প্রকারনির্দেশ সংরচনা SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

প্রকারনির্দেশ সংরচনা SDL_WaylandUserdata
{
    শূন্য *data;
    Uint32 sequence;
} SDL_WaylandUserdata;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা wl_data_source *source;
    SDL_WaylandDataDevice *data_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandDataSource;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_ClipboardDataCallback data_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা wl_data_offer *offer;
    সংরচনা wl_array mimes;
    SDL_WaylandDataDevice *data_device;

    // Callback data for queued receive.
    সংরচনা wl_callback *callback;
    পূর্ণাঙ্ক read_fd;
} SDL_WaylandDataOffer;

প্রকারনির্দেশ সংরচনা Wayland_DropData
{
    SDL_WaylandDataOffer *offer;
    SDL_Window *dnd_window;
    ধ্রুৱ ৱর্ণ *text_mime_type;
    সংরচনা wl_callback *cleanup_callback;
    Wayland_JobID id;

    সংরচনা wl_list link;
} Wayland_DropData;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা zwp_primary_selection_offer_v1 *offer;
    সংরচনা wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

সংরচনা SDL_WaylandDataDevice
{
    সংরচনা wl_data_device *data_device;
    সংরচনা SDL_WaylandSeat *seat;
    ৱর্ণ *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_WaylandDataOffer *drag_offer;
    SDL_WaylandDataOffer *selection_offer;
    ধ্রুৱ ৱর্ণ *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    সংরচনা wl_surface *dnd_surface;
    সংরচনা wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_WaylandDataSource *selection_source;
};

সংরচনা SDL_WaylandPrimarySelectionDevice
{
    সংরচনা zwp_primary_selection_device_v1 *primary_selection_device;
    সংরচনা SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
বাহ্য SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data);
বাহ্য SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data);
বাহ্য ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ধ্রুৱ ৱর্ণ *mime_type, পূর্ণাঙ্ক fd);
বাহ্য ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ধ্রুৱ ৱর্ণ *mime_type, পূর্ণাঙ্ক fd);
বাহ্য শূন্য Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata, Uint32 sequence);
বাহ্য শূন্য Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata);
বাহ্য শূন্য *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ধ্রুৱ ৱর্ণ *mime_type, size_t *length);
বাহ্য শূন্য *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ধ্রুৱ ৱর্ণ *mime_type, size_t *length);
বাহ্য শূন্য Wayland_DataSourceDestroy(SDL_WaylandDataSource *source);
বাহ্য শূন্য Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
বাহ্য bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ধ্রুৱ ৱর্ণ *mime_type, ধ্রুৱ সংরচনা wl_callback_listener *completion_listener, শূন্য *userdata);
বাহ্য শূন্য *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length);
বাহ্য শূন্য *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ধ্রুৱ ৱর্ণ *mime_type, size_t *length);
বাহ্য শূন্য *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুৱ ৱর্ণ *mime_type, size_t *length);
বাহ্য bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ধ্রুৱ ৱর্ণ *mime_type);
বাহ্য শূন্য Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer);
বাহ্য bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুৱ ৱর্ণ *mime_type);
বাহ্য bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ধ্রুৱ ৱর্ণ *mime_type);
বাহ্য bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুৱ ৱর্ণ *mime_type);
বাহ্য শূন্য Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer);
বাহ্য শূন্য Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
বাহ্য bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *device, SDL_WaylandDataSource *source, ধ্রুৱ ৱর্ণ **mime_types, size_t mime_গুনতি);
বাহ্য bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ধ্রুৱ ৱর্ণ *ধ্রুৱ *mime_types, size_t mime_গুনতি);

#endif // SDL_waylanddatamanager_h_
