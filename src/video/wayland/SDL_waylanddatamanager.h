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

#اگر_غیر_تعریف_شدہ SDL_waylanddatamanager_h_
#تعریف_کرو SDL_waylanddatamanager_h_

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"

#تعریف_کرو متن_MIME            "text/plain;charset=utf-8"
#تعریف_کرو FILE_MIME            "text/uri-list"
#تعریف_کرو FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#تعریف_کرو SDL_ڈیٹا_ORIGIN_MIME "application/x-sdl3-source-id"

قسمتعریف ساخت SDL_Wayland_ڈیٹا_Device SDL_Wayland_ڈیٹا_Device;
قسمتعریف ساخت SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

قسمتعریف ساخت SDL_WaylandUserdata
{
    خالی *ڈیٹا;
    Uint32 sequence;
} SDL_WaylandUserdata;

قسمتعریف ساخت
{
    ساخت wl_ڈیٹا_ماخذ *ماخذ;
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device;
    SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_ڈیٹا_ماخذ;

قسمتعریف ساخت
{
    ساخت zwp_primary_selection_ماخذ_v1 *ماخذ;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_ماخذ;

قسمتعریف ساخت
{
    ساخت wl_ڈیٹا_offer *offer;
    ساخت wl_array mimes;
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device;

    // Callback data for queued receive.
    ساخت wl_callback *callback;
    صحیح read_fd;
} SDL_Wayland_ڈیٹا_Offer;

قسمتعریف ساخت Wayland_Drop_ڈیٹا
{
    SDL_Wayland_ڈیٹا_Offer *offer;
    SDL_کھڑکی *dnd_کھڑکی;
    ثابت حرف *متن_mime_type;
    ساخت wl_callback *cleanup_callback;
    Wayland_کام_ID id;

    ساخت wl_list link;
} Wayland_Drop_ڈیٹا;

قسمتعریف ساخت
{
    ساخت zwp_primary_selection_offer_v1 *offer;
    ساخت wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ساخت SDL_Wayland_ڈیٹا_Device
{
    ساخت wl_ڈیٹا_device *ڈیٹا_device;
    ساخت SDL_WaylandSeat *seat;
    حرف *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_ڈیٹا_Offer *drag_offer;
    SDL_Wayland_ڈیٹا_Offer *selection_offer;
    ثابت حرف *متن_mime_type;
    bool has_mime_file;
    SDL_کھڑکی *dnd_کھڑکی;
    ساخت wl_surface *dnd_surface;
    ساخت wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_ڈیٹا_ماخذ *selection_ماخذ;
};

ساخت SDL_WaylandPrimarySelectionDevice
{
    ساخت zwp_primary_selection_device_v1 *primary_selection_device;
    ساخت SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_ماخذ *selection_ماخذ;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
خارجی SDL_Wayland_ڈیٹا_ماخذ *Wayland_ڈیٹا_ماخذ_Create(SDL_Video_ڈیٹا *video_ڈیٹا);
خارجی SDL_Wayland_Primary_Selection_ماخذ *Wayland_Primary_Selection_ماخذ_Create(SDL_Video_ڈیٹا *video_ڈیٹا);
خارجی ssize_t Wayland_ڈیٹا_ماخذ_Send(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف *mime_type, صحیح fd);
خارجی ssize_t Wayland_Primary_Selection_ماخذ_Send(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, ثابت حرف *mime_type, صحیح fd);
خارجی خالی Wayland_ڈیٹا_ماخذ_سیٹ_Callback(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback, SDL_ClipboardCleanupCallback cleanup_callback, خالی *userdata, Uint32 sequence);
خارجی خالی Wayland_Primary_Selection_ماخذ_سیٹ_Callback(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback, SDL_ClipboardCleanupCallback cleanup_callback, خالی *userdata);
خارجی خالی *Wayland_ڈیٹا_ماخذ_Get_ڈیٹا(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف *mime_type, size_t *لمبائی);
خارجی خالی *Wayland_Primary_Selection_ماخذ_Get_ڈیٹا(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, ثابت حرف *mime_type, size_t *لمبائی);
خارجی خالی Wayland_ڈیٹا_ماخذ_Destroy(SDL_Wayland_ڈیٹا_ماخذ *ماخذ);
خارجی خالی Wayland_Primary_Selection_ماخذ_Destroy(SDL_Wayland_Primary_Selection_ماخذ *ماخذ);

// Wayland Data / Primary Selection Offer - (Receiving)
خارجی bool Wayland_ڈیٹا_Offer_Request_ڈیٹا_From_Self(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type, ثابت ساخت wl_callback_listener *completion_listener, خالی *userdata);
خارجی خالی *Wayland_ڈیٹا_Offer_Get_ڈیٹا_From_Self(SDL_Wayland_ڈیٹا_Offer *offer, size_t *لمبائی);
خارجی خالی *Wayland_ڈیٹا_Offer_Receive(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type, size_t *لمبائی);
خارجی خالی *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *لمبائی);
خارجی bool Wayland_ڈیٹا_Offer_Has_MIME(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type);
خارجی خالی Wayland_ڈیٹا_Device_سیٹ_Selection_Offer(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device, SDL_Wayland_ڈیٹا_Offer *offer);
خارجی bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجی bool Wayland_ڈیٹا_Offer_جوڑو_MIME(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type);
خارجی bool Wayland_Primary_Selection_Offer_جوڑو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجی خالی Wayland_ڈیٹا_Offer_Destroy(SDL_Wayland_ڈیٹا_Offer *offer);
خارجی خالی Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
خارجی bool Wayland_ڈیٹا_Device_سیٹ_Selection_ماخذ(SDL_Wayland_ڈیٹا_Device *device, SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف **mime_types, size_t mime_گنتی);
خارجی bool Wayland_Primary_Selection_Device_سیٹ_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_ماخذ *ماخذ, ثابت حرف *ثابت *mime_types, size_t mime_گنتی);

#اگر_ختم // SDL_waylanddatamanager_h_
