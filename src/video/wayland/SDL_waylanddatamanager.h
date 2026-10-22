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

#اگر_تعریف_نشده SDL_waylanddatamanager_h_
#تعریف_کن SDL_waylanddatamanager_h_

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"

#تعریف_کن متن_MIME            "text/plain;charset=utf-8"
#تعریف_کن FILE_MIME            "text/uri-list"
#تعریف_کن FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#تعریف_کن SDL_داده_ORIGIN_MIME "application/x-sdl3-source-id"

تعريفنوع بنية SDL_Wayland_داده_Device SDL_Wayland_داده_Device;
تعريفنوع بنية SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

تعريفنوع بنية SDL_WaylandUserdata
{
    فراغ *داده;
    Uint32 sequence;
} SDL_WaylandUserdata;

تعريفنوع بنية
{
    بنية wl_داده_منبع *منبع;
    SDL_Wayland_داده_Device *داده_device;
    SDL_Clipboard_داده_Callback داده_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_داده_منبع;

تعريفنوع بنية
{
    بنية zwp_primary_selection_منبع_v1 *منبع;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_داده_Callback داده_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_منبع;

تعريفنوع بنية
{
    بنية wl_داده_offer *offer;
    بنية wl_array mimes;
    SDL_Wayland_داده_Device *داده_device;

    // Callback data for queued receive.
    بنية wl_callback *callback;
    صحيح read_fd;
} SDL_Wayland_داده_Offer;

تعريفنوع بنية Wayland_Drop_داده
{
    SDL_Wayland_داده_Offer *offer;
    SDL_پنجره *dnd_پنجره;
    ثابت حرف *متن_mime_type;
    بنية wl_callback *cleanup_callback;
    Wayland_کار_ID id;

    بنية wl_list link;
} Wayland_Drop_داده;

تعريفنوع بنية
{
    بنية zwp_primary_selection_offer_v1 *offer;
    بنية wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

بنية SDL_Wayland_داده_Device
{
    بنية wl_داده_device *داده_device;
    بنية SDL_WaylandSeat *seat;
    حرف *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_داده_Offer *drag_offer;
    SDL_Wayland_داده_Offer *selection_offer;
    ثابت حرف *متن_mime_type;
    bool has_mime_file;
    SDL_پنجره *dnd_پنجره;
    بنية wl_surface *dnd_surface;
    بنية wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_داده_منبع *selection_منبع;
};

بنية SDL_WaylandPrimarySelectionDevice
{
    بنية zwp_primary_selection_device_v1 *primary_selection_device;
    بنية SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_منبع *selection_منبع;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
خارجي SDL_Wayland_داده_منبع *Wayland_داده_منبع_Create(SDL_Video_داده *video_داده);
خارجي SDL_Wayland_Primary_Selection_منبع *Wayland_Primary_Selection_منبع_Create(SDL_Video_داده *video_داده);
خارجي ssize_t Wayland_داده_منبع_Send(SDL_Wayland_داده_منبع *منبع, ثابت حرف *mime_type, صحيح fd);
خارجي ssize_t Wayland_Primary_Selection_منبع_Send(SDL_Wayland_Primary_Selection_منبع *منبع, ثابت حرف *mime_type, صحيح fd);
خارجي فراغ Wayland_داده_منبع_مجموعه_Callback(SDL_Wayland_داده_منبع *منبع, SDL_Clipboard_داده_Callback داده_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence);
خارجي فراغ Wayland_Primary_Selection_منبع_مجموعه_Callback(SDL_Wayland_Primary_Selection_منبع *منبع, SDL_Clipboard_داده_Callback داده_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata);
خارجي فراغ *Wayland_داده_منبع_Get_داده(SDL_Wayland_داده_منبع *منبع, ثابت حرف *mime_type, size_t *درازی);
خارجي فراغ *Wayland_Primary_Selection_منبع_Get_داده(SDL_Wayland_Primary_Selection_منبع *منبع, ثابت حرف *mime_type, size_t *درازی);
خارجي فراغ Wayland_داده_منبع_Destroy(SDL_Wayland_داده_منبع *منبع);
خارجي فراغ Wayland_Primary_Selection_منبع_Destroy(SDL_Wayland_Primary_Selection_منبع *منبع);

// Wayland Data / Primary Selection Offer - (Receiving)
خارجي bool Wayland_داده_Offer_Request_داده_From_Self(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata);
خارجي فراغ *Wayland_داده_Offer_Get_داده_From_Self(SDL_Wayland_داده_Offer *offer, size_t *درازی);
خارجي فراغ *Wayland_داده_Offer_Receive(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type, size_t *درازی);
خارجي فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *درازی);
خارجي bool Wayland_داده_Offer_Has_MIME(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_داده_Device_مجموعه_Selection_Offer(SDL_Wayland_داده_Device *داده_device, SDL_Wayland_داده_Offer *offer);
خارجي bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_داده_Offer_جمع_کن_MIME(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_Primary_Selection_Offer_جمع_کن_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_داده_Offer_Destroy(SDL_Wayland_داده_Offer *offer);
خارجي فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
خارجي bool Wayland_داده_Device_مجموعه_Selection_منبع(SDL_Wayland_داده_Device *device, SDL_Wayland_داده_منبع *منبع, ثابت حرف **mime_types, size_t mime_شمار);
خارجي bool Wayland_Primary_Selection_Device_مجموعه_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_منبع *منبع, ثابت حرف *ثابت *mime_types, size_t mime_شمار);

#پایان_اگر // SDL_waylanddatamanager_h_
