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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylanddatamanager_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylanddatamanager_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਠ_MIME            "text/plain;charset=utf-8"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FILE_MIME            "text/uri-list"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਅੰਕੜੇ_ORIGIN_MIME "application/x-sdl3-source-id"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Wayland_ਅੰਕੜੇ_Device SDL_Wayland_ਅੰਕੜੇ_Device;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_WaylandUserdata
{
    ਖਾਲੀ *ਅੰਕੜੇ;
    Uint32 sequence;
} SDL_WaylandUserdata;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ;
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device;
    SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ zwp_primary_selection_ਸਰੋਤ_v1 *ਸਰੋਤ;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_ਸਰੋਤ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ wl_ਅੰਕੜੇ_offer *offer;
    ਬਣਤਰ wl_array mimes;
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device;

    // Callback data for queued receive.
    ਬਣਤਰ wl_callback *callback;
    ਪੂਰਨ read_fd;
} SDL_Wayland_ਅੰਕੜੇ_Offer;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_Drop_ਅੰਕੜੇ
{
    SDL_Wayland_ਅੰਕੜੇ_Offer *offer;
    SDL_ਖਿੜਕੀ *dnd_ਖਿੜਕੀ;
    ਅਚਲ ਅੱਖਰ *ਪਾਠ_mime_type;
    ਬਣਤਰ wl_callback *cleanup_callback;
    Wayland_ਕੰਮ_ID id;

    ਬਣਤਰ wl_list link;
} Wayland_Drop_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ zwp_primary_selection_offer_v1 *offer;
    ਬਣਤਰ wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ਬਣਤਰ SDL_Wayland_ਅੰਕੜੇ_Device
{
    ਬਣਤਰ wl_ਅੰਕੜੇ_device *ਅੰਕੜੇ_device;
    ਬਣਤਰ SDL_WaylandSeat *seat;
    ਅੱਖਰ *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_ਅੰਕੜੇ_Offer *drag_offer;
    SDL_Wayland_ਅੰਕੜੇ_Offer *selection_offer;
    ਅਚਲ ਅੱਖਰ *ਪਾਠ_mime_type;
    bool has_mime_file;
    SDL_ਖਿੜਕੀ *dnd_ਖਿੜਕੀ;
    ਬਣਤਰ wl_surface *dnd_surface;
    ਬਣਤਰ wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *selection_ਸਰੋਤ;
};

ਬਣਤਰ SDL_WaylandPrimarySelectionDevice
{
    ਬਣਤਰ zwp_primary_selection_device_v1 *primary_selection_device;
    ਬਣਤਰ SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_ਸਰੋਤ *selection_ਸਰੋਤ;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
ਬਾਹਰੀ SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Create(SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ);
ਬਾਹਰੀ SDL_Wayland_Primary_Selection_ਸਰੋਤ *Wayland_Primary_Selection_ਸਰੋਤ_Create(SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ);
ਬਾਹਰੀ ssize_t Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Send(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, ਪੂਰਨ fd);
ਬਾਹਰੀ ssize_t Wayland_Primary_Selection_ਸਰੋਤ_Send(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, ਪੂਰਨ fd);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਅੰਕੜੇ_ਸਰੋਤ_ਸੈੱਟ_Callback(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ਖਾਲੀ *userdata, Uint32 sequence);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Primary_Selection_ਸਰੋਤ_ਸੈੱਟ_Callback(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ਖਾਲੀ *userdata);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Get_ਅੰਕੜੇ(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_Primary_Selection_ਸਰੋਤ_Get_ਅੰਕੜੇ(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Primary_Selection_ਸਰੋਤ_Destroy(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ);

// Wayland Data / Primary Selection Offer - (Receiving)
ਬਾਹਰੀ bool Wayland_ਅੰਕੜੇ_Offer_Request_ਅੰਕੜੇ_From_Self(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type, ਅਚਲ ਬਣਤਰ wl_callback_listener *completion_listener, ਖਾਲੀ *userdata);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_ਅੰਕੜੇ_Offer_Get_ਅੰਕੜੇ_From_Self(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, size_t *ਲੰਮਾਈ);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_ਅੰਕੜੇ_Offer_Receive(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ);
ਬਾਹਰੀ bool Wayland_ਅੰਕੜੇ_Offer_Has_MIME(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_Offer(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device, SDL_Wayland_ਅੰਕੜੇ_Offer *offer);
ਬਾਹਰੀ bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type);
ਬਾਹਰੀ bool Wayland_ਅੰਕੜੇ_Offer_ਜੋੜੋ_MIME(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type);
ਬਾਹਰੀ bool Wayland_Primary_Selection_Offer_ਜੋੜੋ_MIME(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਅੰਕੜੇ_Offer_Destroy(SDL_Wayland_ਅੰਕੜੇ_Offer *offer);
ਬਾਹਰੀ ਖਾਲੀ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
ਬਾਹਰੀ bool Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_ਸਰੋਤ(SDL_Wayland_ਅੰਕੜੇ_Device *device, SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ **mime_types, size_t mime_ਗਿਣਤੀ);
ਬਾਹਰੀ bool Wayland_Primary_Selection_Device_ਸੈੱਟ_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t mime_ਗਿਣਤੀ);

#ਜੇ_ਅੰਤ // SDL_waylanddatamanager_h_
