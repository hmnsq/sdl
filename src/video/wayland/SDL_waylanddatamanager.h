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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylanddatamanager_h_
#define SDL_waylanddatamanager_h_

#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandwindow.h"

#define TEXT_MIME            "text/plain;charset=utf-8"
#define FILE_MIME            "text/uri-list"
#define FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#define SDL_তথ্য_ORIGIN_MIME "application/x-sdl3-source-id"

প্রকারলেখ কাঠামো SDL_Wayland_তথ্য_Device SDL_Wayland_তথ্য_Device;
প্রকারলেখ কাঠামো SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

প্রকারলেখ কাঠামো SDL_WaylandUserdata
{
    শূন্য *তথ্য;
    Uint32 sequence;
} SDL_WaylandUserdata;

প্রকারলেখ কাঠামো
{
    কাঠামো wl_তথ্য_source *source;
    SDL_Wayland_তথ্য_Device *তথ্য_device;
    SDL_Clipboard_তথ্য_Callback তথ্য_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_তথ্য_Source;

প্রকারলেখ কাঠামো
{
    কাঠামো zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_তথ্য_Callback তথ্য_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

প্রকারলেখ কাঠামো
{
    কাঠামো wl_তথ্য_offer *offer;
    কাঠামো wl_array mimes;
    SDL_Wayland_তথ্য_Device *তথ্য_device;

    // Callback data for queued receive.
    কাঠামো wl_callback *callback;
    পূর্ণসংখ্যা read_fd;
} SDL_Wayland_তথ্য_Offer;

প্রকারলেখ কাঠামো Wayland_Drop_তথ্য
{
    SDL_Wayland_তথ্য_Offer *offer;
    SDL_Window *dnd_window;
    ধ্রুবক অক্ষর *text_mime_type;
    কাঠামো wl_callback *cleanup_callback;
    Wayland_JobID id;

    কাঠামো wl_list link;
} Wayland_Drop_তথ্য;

প্রকারলেখ কাঠামো
{
    কাঠামো zwp_primary_selection_offer_v1 *offer;
    কাঠামো wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

কাঠামো SDL_Wayland_তথ্য_Device
{
    কাঠামো wl_তথ্য_device *তথ্য_device;
    কাঠামো SDL_WaylandSeat *seat;
    অক্ষর *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_তথ্য_Offer *drag_offer;
    SDL_Wayland_তথ্য_Offer *selection_offer;
    ধ্রুবক অক্ষর *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    কাঠামো wl_surface *dnd_surface;
    কাঠামো wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_তথ্য_Source *selection_source;
};

কাঠামো SDL_WaylandPrimarySelectionDevice
{
    কাঠামো zwp_primary_selection_device_v1 *primary_selection_device;
    কাঠামো SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
বাহ্যিক SDL_Wayland_তথ্য_Source *Wayland_তথ্য_Source_Create(SDL_Video_তথ্য *video_তথ্য);
বাহ্যিক SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_তথ্য *video_তথ্য);
বাহ্যিক ssize_t Wayland_তথ্য_Source_Send(SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর *mime_type, পূর্ণসংখ্যা fd);
বাহ্যিক ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ধ্রুবক অক্ষর *mime_type, পূর্ণসংখ্যা fd);
বাহ্যিক শূন্য Wayland_তথ্য_Source_Set_Callback(SDL_Wayland_তথ্য_Source *source, SDL_Clipboard_তথ্য_Callback তথ্য_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata, Uint32 sequence);
বাহ্যিক শূন্য Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_তথ্য_Callback তথ্য_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata);
বাহ্যিক শূন্য *Wayland_তথ্য_Source_Get_তথ্য(SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য);
বাহ্যিক শূন্য *Wayland_Primary_Selection_Source_Get_তথ্য(SDL_WaylandPrimarySelectionSource *source, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য);
বাহ্যিক শূন্য Wayland_তথ্য_Source_Destroy(SDL_Wayland_তথ্য_Source *source);
বাহ্যিক শূন্য Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
বাহ্যিক bool Wayland_তথ্য_Offer_Request_তথ্য_From_Self(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type, ধ্রুবক কাঠামো wl_callback_listener *completion_listener, শূন্য *userdata);
বাহ্যিক শূন্য *Wayland_তথ্য_Offer_Get_তথ্য_From_Self(SDL_Wayland_তথ্য_Offer *offer, size_t *দৈর্ঘ্য);
বাহ্যিক শূন্য *Wayland_তথ্য_Offer_Receive(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য);
বাহ্যিক শূন্য *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য);
বাহ্যিক bool Wayland_তথ্য_Offer_Has_MIME(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type);
বাহ্যিক শূন্য Wayland_তথ্য_Device_Set_Selection_Offer(SDL_Wayland_তথ্য_Device *তথ্য_device, SDL_Wayland_তথ্য_Offer *offer);
বাহ্যিক bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type);
বাহ্যিক bool Wayland_তথ্য_Offer_Add_MIME(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type);
বাহ্যিক bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type);
বাহ্যিক শূন্য Wayland_তথ্য_Offer_Destroy(SDL_Wayland_তথ্য_Offer *offer);
বাহ্যিক শূন্য Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
বাহ্যিক bool Wayland_তথ্য_Device_Set_Selection_Source(SDL_Wayland_তথ্য_Device *device, SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর **mime_types, size_t mime_গুনতি);
বাহ্যিক bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, ধ্রুবক অক্ষর *ধ্রুবক *mime_types, size_t mime_গুনতি);

#endif // SDL_waylanddatamanager_h_
