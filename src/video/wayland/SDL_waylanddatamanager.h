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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylanddatamanager_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylanddatamanager_h_

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ಪಠ್ಯ_MIME            "text/plain;charset=utf-8"
#ವ್ಯಾಖ್ಯಾನಿಸು FILE_MIME            "text/uri-list"
#ವ್ಯಾಖ್ಯಾನಿಸು FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ದತ್ತಾಂಶ_ORIGIN_MIME "application/x-sdl3-source-id"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Wayland_ದತ್ತಾಂಶ_Device SDL_Wayland_ದತ್ತಾಂಶ_Device;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_WaylandUserdata
{
    ಶೂನ್ಯ *ದತ್ತಾಂಶ;
    Uint32 sequence;
} SDL_WaylandUserdata;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ;
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device;
    SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ zwp_primary_selection_ಮೂಲ_v1 *ಮೂಲ;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_Primary_Selection_ಮೂಲ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ wl_ದತ್ತಾಂಶ_offer *offer;
    ರಚನೆ wl_array mimes;
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device;

    // Callback data for queued receive.
    ರಚನೆ wl_callback *callback;
    ಪೂರ್ಣಾಂಕ read_fd;
} SDL_Wayland_ದತ್ತಾಂಶ_Offer;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_Drop_ದತ್ತಾಂಶ
{
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer;
    SDL_ಕಿಟಕಿ *dnd_ಕಿಟಕಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ_mime_type;
    ರಚನೆ wl_callback *cleanup_callback;
    Wayland_ಕೆಲಸ_ID id;

    ರಚನೆ wl_list link;
} Wayland_Drop_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ zwp_primary_selection_offer_v1 *offer;
    ರಚನೆ wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

ರಚನೆ SDL_Wayland_ದತ್ತಾಂಶ_Device
{
    ರಚನೆ wl_ದತ್ತಾಂಶ_device *ದತ್ತಾಂಶ_device;
    ರಚನೆ SDL_WaylandSeat *seat;
    ಅಕ್ಷರ *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *drag_offer;
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *selection_offer;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ_mime_type;
    bool has_mime_file;
    SDL_ಕಿಟಕಿ *dnd_ಕಿಟಕಿ;
    ರಚನೆ wl_surface *dnd_surface;
    ರಚನೆ wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *selection_ಮೂಲ;
};

ರಚನೆ SDL_WaylandPrimarySelectionDevice
{
    ರಚನೆ zwp_primary_selection_device_v1 *primary_selection_device;
    ರಚನೆ SDL_WaylandSeat *seat;

    SDL_Wayland_Primary_Selection_ಮೂಲ *selection_ಮೂಲ;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
ಬಾಹ್ಯ SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Create(SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ);
ಬಾಹ್ಯ SDL_Wayland_Primary_Selection_ಮೂಲ *Wayland_Primary_Selection_ಮೂಲ_Create(SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ssize_t Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Send(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಪೂರ್ಣಾಂಕ fd);
ಬಾಹ್ಯ ssize_t Wayland_Primary_Selection_ಮೂಲ_Send(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಪೂರ್ಣಾಂಕ fd);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_ಮೂಲ_ಗಣ_Callback(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata, Uint32 sequence);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Primary_Selection_ಮೂಲ_ಗಣ_Callback(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Get_ದತ್ತಾಂಶ(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_Primary_Selection_ಮೂಲ_Get_ದತ್ತಾಂಶ(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Primary_Selection_ಮೂಲ_Destroy(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ);

// Wayland Data / Primary Selection Offer - (Receiving)
ಬಾಹ್ಯ bool Wayland_ದತ್ತಾಂಶ_Offer_Request_ದತ್ತಾಂಶ_From_Self(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener *completion_listener, ಶೂನ್ಯ *userdata);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_Offer_Get_ದತ್ತಾಂಶ_From_Self(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_Offer_Receive(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ);
ಬಾಹ್ಯ bool Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_Offer(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device, SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer);
ಬಾಹ್ಯ bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
ಬಾಹ್ಯ bool Wayland_ದತ್ತಾಂಶ_Offer_ಕೂಡಿಸು_MIME(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
ಬಾಹ್ಯ bool Wayland_Primary_Selection_Offer_ಕೂಡಿಸು_MIME(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_Offer_Destroy(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
ಬಾಹ್ಯ bool Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_ಮೂಲ(SDL_Wayland_ದತ್ತಾಂಶ_Device *device, SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **mime_types, size_t mime_ಎಣಿಕೆ);
ಬಾಹ್ಯ bool Wayland_Primary_Selection_Device_ಗಣ_Selection(SDL_WaylandPrimarySelectionDevice *device, SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types, size_t mime_ಎಣಿಕೆ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylanddatamanager_h_
