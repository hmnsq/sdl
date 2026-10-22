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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylanddatamanager_h_
#నిర్వచించు SDL_waylanddatamanager_h_

#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandwindow.h"

#నిర్వచించు పాఠ్యం_MIME            "text/plain;charset=utf-8"
#నిర్వచించు FILE_MIME            "text/uri-list"
#నిర్వచించు FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#నిర్వచించు SDL_దత్తాంశం_ORIGIN_MIME "application/x-sdl3-source-id"

రకనిర్వచనం నిర్మాణం SDL_Wayland_దత్తాంశం_Device SDL_Wayland_దత్తాంశం_Device;
రకనిర్వచనం నిర్మాణం SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

రకనిర్వచనం నిర్మాణం SDL_WaylandUserdata
{
    శూన్య *దత్తాంశం;
    Uint32 sequence;
} SDL_WaylandUserdata;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం wl_దత్తాంశం_ఆధారం *ఆధారం;
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device;
    SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_దత్తాంశం_ఆధారం;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం zwp_primary_selection_ఆధారం_v1 *ఆధారం;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_ఆధారం;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం wl_దత్తాంశం_offer *offer;
    నిర్మాణం wl_array mimes;
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device;

    // Callback data for queued receive.
    నిర్మాణం wl_callback *callback;
    పూర్ణాంకం read_fd;
} SDL_Wayland_దత్తాంశం_Offer;

రకనిర్వచనం నిర్మాణం Wayland_Drop_దత్తాంశం
{
    SDL_Wayland_దత్తాంశం_Offer *offer;
    SDL_కిటికీ *dnd_కిటికీ;
    స్థిరరాశి అక్షరం *పాఠ్యం_mime_type;
    నిర్మాణం wl_callback *cleanup_callback;
    Wayland_పని_ID id;

    నిర్మాణం wl_list link;
} Wayland_Drop_దత్తాంశం;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం zwp_primary_selection_offer_v1 *offer;
    నిర్మాణం wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

నిర్మాణం SDL_Wayland_దత్తాంశం_Device
{
    నిర్మాణం wl_దత్తాంశం_device *దత్తాంశం_device;
    నిర్మాణం SDL_WaylandSeat *seat;
    అక్షరం *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_దత్తాంశం_Offer *drag_offer;
    SDL_Wayland_దత్తాంశం_Offer *selection_offer;
    స్థిరరాశి అక్షరం *పాఠ్యం_mime_type;
    bool has_mime_file;
    SDL_కిటికీ *dnd_కిటికీ;
    నిర్మాణం wl_surface *dnd_surface;
    నిర్మాణం wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_దత్తాంశం_ఆధారం *selection_ఆధారం;
};

నిర్మాణం SDL_WaylandPrimarySelectionDevice
{
    నిర్మాణం zwp_primary_selection_device_v1 *primary_selection_device;
    నిర్మాణం SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_ఆధారం *selection_ఆధారం;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
బాహ్య SDL_Wayland_దత్తాంశం_ఆధారం *Wayland_దత్తాంశం_ఆధారం_Create(SDL_Video_దత్తాంశం *video_దత్తాంశం);
బాహ్య SDL_Wayland_Primary_Selection_ఆధారం *Wayland_Primary_Selection_ఆధారం_Create(SDL_Video_దత్తాంశం *video_దత్తాంశం);
బాహ్య ssize_t Wayland_దత్తాంశం_ఆధారం_Send(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, పూర్ణాంకం fd);
బాహ్య ssize_t Wayland_Primary_Selection_ఆధారం_Send(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, పూర్ణాంకం fd);
బాహ్య శూన్య Wayland_దత్తాంశం_ఆధారం_సమితి_Callback(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback, SDL_ClipboardCleanupCallback cleanup_callback, శూన్య *userdata, Uint32 sequence);
బాహ్య శూన్య Wayland_Primary_Selection_ఆధారం_సమితి_Callback(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback, SDL_ClipboardCleanupCallback cleanup_callback, శూన్య *userdata);
బాహ్య శూన్య *Wayland_దత్తాంశం_ఆధారం_Get_దత్తాంశం(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి);
బాహ్య శూన్య *Wayland_Primary_Selection_ఆధారం_Get_దత్తాంశం(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి);
బాహ్య శూన్య Wayland_దత్తాంశం_ఆధారం_Destroy(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం);
బాహ్య శూన్య Wayland_Primary_Selection_ఆధారం_Destroy(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం);

// Wayland Data / Primary Selection Offer - (Receiving)
బాహ్య bool Wayland_దత్తాంశం_Offer_Request_దత్తాంశం_From_Self(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type, స్థిరరాశి నిర్మాణం wl_callback_listener *completion_listener, శూన్య *userdata);
బాహ్య శూన్య *Wayland_దత్తాంశం_Offer_Get_దత్తాంశం_From_Self(SDL_Wayland_దత్తాంశం_Offer *offer, size_t *నిడివి);
బాహ్య శూన్య *Wayland_దత్తాంశం_Offer_Receive(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి);
బాహ్య శూన్య *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి);
బాహ్య bool Wayland_దత్తాంశం_Offer_Has_MIME(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type);
బాహ్య శూన్య Wayland_దత్తాంశం_Device_సమితి_Selection_Offer(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device, SDL_Wayland_దత్తాంశం_Offer *offer);
బాహ్య bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type);
బాహ్య bool Wayland_దత్తాంశం_Offer_కూడు_MIME(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type);
బాహ్య bool Wayland_Primary_Selection_Offer_కూడు_MIME(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type);
బాహ్య శూన్య Wayland_దత్తాంశం_Offer_Destroy(SDL_Wayland_దత్తాంశం_Offer *offer);
బాహ్య శూన్య Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
బాహ్య bool Wayland_దత్తాంశం_Device_సమితి_Selection_ఆధారం(SDL_Wayland_దత్తాంశం_Device *device, SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం **mime_types, size_t mime_లెక్క);
బాహ్య bool Wayland_Primary_Selection_Device_సమితి_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types, size_t mime_లెక్క);

#అయితే_ముగింపు // SDL_waylanddatamanager_h_
