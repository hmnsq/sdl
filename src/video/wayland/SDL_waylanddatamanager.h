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

#جے_بنا_تعریف SDL_waylanddatamanager_h_
#تعریف_کرو SDL_waylanddatamanager_h_

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"

#تعریف_کرو متن_MIME            "text/plain;charset=utf-8"
#تعریف_کرو FILE_MIME            "text/uri-list"
#تعریف_کرو FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#تعریف_کرو SDL_انکڑے_ORIGIN_MIME "application/x-sdl3-source-id"

تعريفنوع بنية SDL_Wayland_انکڑے_Device SDL_Wayland_انکڑے_Device;
تعريفنوع بنية SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

تعريفنوع بنية SDL_WaylandUserdata
{
    فراغ *انکڑے;
    Uint32 sequence;
} SDL_WaylandUserdata;

تعريفنوع بنية
{
    بنية wl_انکڑے_سروت *سروت;
    SDL_Wayland_انکڑے_Device *انکڑے_device;
    SDL_Clipboard_انکڑے_Callback انکڑے_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_انکڑے_سروت;

تعريفنوع بنية
{
    بنية zwp_primary_selection_سروت_v1 *سروت;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_انکڑے_Callback انکڑے_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_سروت;

تعريفنوع بنية
{
    بنية wl_انکڑے_offer *offer;
    بنية wl_array mimes;
    SDL_Wayland_انکڑے_Device *انکڑے_device;

    // Callback data for queued receive.
    بنية wl_callback *callback;
    صحيح read_fd;
} SDL_Wayland_انکڑے_Offer;

تعريفنوع بنية Wayland_Drop_انکڑے
{
    SDL_Wayland_انکڑے_Offer *offer;
    SDL_کھڑکی *dnd_کھڑکی;
    ثابت حرف *متن_mime_type;
    بنية wl_callback *cleanup_callback;
    Wayland_کم_ID id;

    بنية wl_list link;
} Wayland_Drop_انکڑے;

تعريفنوع بنية
{
    بنية zwp_primary_selection_offer_v1 *offer;
    بنية wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

بنية SDL_Wayland_انکڑے_Device
{
    بنية wl_انکڑے_device *انکڑے_device;
    بنية SDL_WaylandSeat *seat;
    حرف *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_انکڑے_Offer *drag_offer;
    SDL_Wayland_انکڑے_Offer *selection_offer;
    ثابت حرف *متن_mime_type;
    bool has_mime_file;
    SDL_کھڑکی *dnd_کھڑکی;
    بنية wl_surface *dnd_surface;
    بنية wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_انکڑے_سروت *selection_سروت;
};

بنية SDL_WaylandPrimarySelectionDevice
{
    بنية zwp_primary_selection_device_v1 *primary_selection_device;
    بنية SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_سروت *selection_سروت;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
خارجي SDL_Wayland_انکڑے_سروت *Wayland_انکڑے_سروت_Create(SDL_Video_انکڑے *video_انکڑے);
خارجي SDL_Wayland_Primary_Selection_سروت *Wayland_Primary_Selection_سروت_Create(SDL_Video_انکڑے *video_انکڑے);
خارجي ssize_t Wayland_انکڑے_سروت_Send(SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف *mime_type, صحيح fd);
خارجي ssize_t Wayland_Primary_Selection_سروت_Send(SDL_Wayland_Primary_Selection_سروت *سروت, ثابت حرف *mime_type, صحيح fd);
خارجي فراغ Wayland_انکڑے_سروت_سیٹ_Callback(SDL_Wayland_انکڑے_سروت *سروت, SDL_Clipboard_انکڑے_Callback انکڑے_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence);
خارجي فراغ Wayland_Primary_Selection_سروت_سیٹ_Callback(SDL_Wayland_Primary_Selection_سروت *سروت, SDL_Clipboard_انکڑے_Callback انکڑے_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata);
خارجي فراغ *Wayland_انکڑے_سروت_Get_انکڑے(SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف *mime_type, size_t *لمائی);
خارجي فراغ *Wayland_Primary_Selection_سروت_Get_انکڑے(SDL_Wayland_Primary_Selection_سروت *سروت, ثابت حرف *mime_type, size_t *لمائی);
خارجي فراغ Wayland_انکڑے_سروت_Destroy(SDL_Wayland_انکڑے_سروت *سروت);
خارجي فراغ Wayland_Primary_Selection_سروت_Destroy(SDL_Wayland_Primary_Selection_سروت *سروت);

// Wayland Data / Primary Selection Offer - (Receiving)
خارجي bool Wayland_انکڑے_Offer_Request_انکڑے_From_Self(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata);
خارجي فراغ *Wayland_انکڑے_Offer_Get_انکڑے_From_Self(SDL_Wayland_انکڑے_Offer *offer, size_t *لمائی);
خارجي فراغ *Wayland_انکڑے_Offer_Receive(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type, size_t *لمائی);
خارجي فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *لمائی);
خارجي bool Wayland_انکڑے_Offer_Has_MIME(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_انکڑے_Device_سیٹ_Selection_Offer(SDL_Wayland_انکڑے_Device *انکڑے_device, SDL_Wayland_انکڑے_Offer *offer);
خارجي bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_انکڑے_Offer_جوڑو_MIME(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type);
خارجي bool Wayland_Primary_Selection_Offer_جوڑو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type);
خارجي فراغ Wayland_انکڑے_Offer_Destroy(SDL_Wayland_انکڑے_Offer *offer);
خارجي فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
خارجي bool Wayland_انکڑے_Device_سیٹ_Selection_سروت(SDL_Wayland_انکڑے_Device *device, SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف **mime_types, size_t mime_گنتی);
خارجي bool Wayland_Primary_Selection_Device_سیٹ_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_سروت *سروت, ثابت حرف *ثابت *mime_types, size_t mime_گنتی);

#جے_انت // SDL_waylanddatamanager_h_
