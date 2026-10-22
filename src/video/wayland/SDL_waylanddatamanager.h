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

#جيڪڏهن_وصف_نه_ٿيل SDL_waylanddatamanager_h_
#وصف_ڪريو SDL_waylanddatamanager_h_

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"

#وصف_ڪريو متن_MIME            "text/plain;charset=utf-8"
#وصف_ڪريو FILE_MIME            "text/uri-list"
#وصف_ڪريو FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#وصف_ڪريو SDL_معلومات_ORIGIN_MIME "application/x-sdl3-source-id"

تعريفنوع بنية SDL_Wayland_معلومات_Device SDL_Wayland_معلومات_Device;
تعريفنوع بنية SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

تعريفنوع بنية SDL_WaylandUserdata
{
    فراغ *معلومات;
    Uint32 sequence;
} SDL_WaylandUserdata;

تعريفنوع بنية
{
    بنية wl_معلومات_ذريعو *ذريعو;
    SDL_Wayland_معلومات_Device *معلومات_device;
    SDL_Clipboard_معلومات_Callback معلومات_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_معلومات_ذريعو;

تعريفنوع بنية
{
    بنية zwp_primary_selection_ذريعو_v1 *ذريعو;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_معلومات_Callback معلومات_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_ذريعو;

تعريفنوع بنية
{
    بنية wl_معلومات_offer *offer;
    بنية wl_array mimes;
    SDL_Wayland_معلومات_Device *معلومات_device;

    // Callback data for queued receive.
    بنية wl_callback *callback;
    صحيح read_fd;
} SDL_Wayland_معلومات_Offer;

تعريفنوع بنية Wayland_Drop_معلومات
{
    SDL_Wayland_معلومات_Offer *offer;
    SDL_دري *dnd_دري;
    ثابت حرف *متن_mime_type;
    بنية wl_callback *cleanup_callback;
    Wayland_ڪم_ID id;

    بنية wl_list link;
} Wayland_Drop_معلومات;

تعريفنوع بنية
{
    بنية zwp_primary_selection_offer_v1 *offer;
    بنية wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

بنية SDL_Wayland_معلومات_Device
{
    بنية wl_معلومات_device *معلومات_device;
    بنية SDL_WaylandSeat *seat;
    حرف *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_معلومات_Offer *drag_offer;
    SDL_Wayland_معلومات_Offer *selection_offer;
    ثابت حرف *متن_mime_type;
    bool has_mime_file;
    SDL_دري *dnd_دري;
    بنية wl_surface *dnd_surface;
    بنية wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_معلومات_ذريعو *selection_ذريعو;
};

بنية SDL_WaylandPrimarySelectionDevice
{
    بنية zwp_primary_selection_device_v1 *primary_selection_device;
    بنية SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_ذريعو *selection_ذريعو;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
خارجي SDL_Wayland_معلومات_ذريعو *Wayland_معلومات_ذريعو_Create(SDL_Video_معلومات *video_معلومات);
خارجي SDL_Wayland_Primary_Selection_ذريعو *Wayland_Primary_Selection_ذريعو_Create(SDL_Video_معلومات *video_معلومات);
خارجي ssize_t Wayland_معلومات_ذريعو_Send(SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف *mime_type, صحيح fd);
خارجي ssize_t Wayland_Primary_Selection_ذريعو_Send(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, ثابت حرف *mime_type, صحيح fd);
خارجي فراغ Wayland_معلومات_ذريعو_سيٽ_Callback(SDL_Wayland_معلومات_ذريعو *ذريعو, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence);
خارجي فراغ Wayland_Primary_Selection_ذريعو_سيٽ_Callback(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata);
خارجي فراغ *Wayland_معلومات_ذريعو_Get_معلومات(SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف *mime_type, size_t *ڊيگهائي);
خارجي فراغ *Wayland_Primary_Selection_ذريعو_Get_معلومات(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, ثابت حرف *mime_type, size_t *ڊيگهائي);
خارجي فراغ Wayland_معلومات_ذريعو_Destroy(SDL_Wayland_معلومات_ذريعو *ذريعو);
خارجي فراغ Wayland_Primary_Selection_ذريعو_Destroy(SDL_Wayland_Primary_Selection_ذريعو *ذريعو);

// Wayland Data / Primary Selection Offer - (Receiving)
خارجي bool Wayland_معلومات_Offer_Request_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata);
خارجي فراغ *Wayland_معلومات_Offer_Get_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, size_t *ڊيگهائي);
خارجي فراغ *Wayland_معلومات_Offer_Receive(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, size_t *ڊيگهائي);
خارجي فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *ڊيگهائي);
خارجي bool Wayland_معلومات_Offer_Has_MIME(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_معلومات_Device_سيٽ_Selection_Offer(SDL_Wayland_معلومات_Device *معلومات_device, SDL_Wayland_معلومات_Offer *offer);
خارجي bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_معلومات_Offer_جوڙيو_MIME(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_Primary_Selection_Offer_جوڙيو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_معلومات_Offer_Destroy(SDL_Wayland_معلومات_Offer *offer);
خارجي فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
خارجي bool Wayland_معلومات_Device_سيٽ_Selection_ذريعو(SDL_Wayland_معلومات_Device *device, SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف **mime_types, size_t mime_ڳڻپ);
خارجي bool Wayland_Primary_Selection_Device_سيٽ_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_ذريعو *ذريعو, ثابت حرف *ثابت *mime_types, size_t mime_ڳڻپ);

#جيڪڏهن_پورو // SDL_waylanddatamanager_h_
