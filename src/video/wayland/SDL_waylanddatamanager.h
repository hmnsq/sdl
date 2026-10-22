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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylanddatamanager_h_
#घोषणा SDL_waylanddatamanager_h_

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandwindow.h"

#घोषणा TEXT_MIME            "text/plain;charset=utf-8"
#घोषणा FILE_MIME            "text/uri-list"
#घोषणा FILE_PORTAL_MIME     "application/vnd.portal.filetransfer"
#घोषणा SDL_तथ्य_ORIGIN_MIME "application/x-sdl3-source-id"

प्रकार काष्ठा SDL_Wayland_तथ्य_Device SDL_Wayland_तथ्य_Device;
प्रकार काष्ठा SDL_WaylandPrimarySelectionDevice SDL_WaylandPrimarySelectionDevice;

प्रकार काष्ठा SDL_WaylandUserdata
{
    व्योम *तथ्य;
    Uint32 sequence;
} SDL_WaylandUserdata;

प्रकार काष्ठा
{
    काष्ठा wl_तथ्य_source *source;
    SDL_Wayland_तथ्य_Device *तथ्य_device;
    SDL_Clipboard_तथ्य_Callback तथ्य_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_Wayland_तथ्य_Source;

प्रकार काष्ठा
{
    काष्ठा zwp_primary_selection_source_v1 *source;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    SDL_Clipboard_तथ्य_Callback तथ्य_callback;
    SDL_ClipboardCleanupCallback cleanup_callback;
    SDL_WaylandUserdata userdata;
} SDL_WaylandPrimarySelectionSource;

प्रकार काष्ठा
{
    काष्ठा wl_तथ्य_offer *offer;
    काष्ठा wl_array mimes;
    SDL_Wayland_तथ्य_Device *तथ्य_device;

    // Callback data for queued receive.
    काष्ठा wl_callback *callback;
    पूर्णांक read_fd;
} SDL_Wayland_तथ्य_Offer;

प्रकार काष्ठा Wayland_Drop_तथ्य
{
    SDL_Wayland_तथ्य_Offer *offer;
    SDL_Window *dnd_window;
    स्थिर अक्षर *text_mime_type;
    काष्ठा wl_callback *cleanup_callback;
    Wayland_JobID id;

    काष्ठा wl_list link;
} Wayland_Drop_तथ्य;

प्रकार काष्ठा
{
    काष्ठा zwp_primary_selection_offer_v1 *offer;
    काष्ठा wl_array mimes;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
} SDL_WaylandPrimarySelectionOffer;

काष्ठा SDL_Wayland_तथ्य_Device
{
    काष्ठा wl_तथ्य_device *तथ्य_device;
    काष्ठा SDL_WaylandSeat *seat;
    अक्षर *id_str;

    // Drag and Drop
    uint32_t drag_serial;
    SDL_Wayland_तथ्य_Offer *drag_offer;
    SDL_Wayland_तथ्य_Offer *selection_offer;
    स्थिर अक्षर *text_mime_type;
    bool has_mime_file;
    SDL_Window *dnd_window;
    काष्ठा wl_surface *dnd_surface;
    काष्ठा wl_list pending_drops;

    // Clipboard and Primary Selection
    SDL_Wayland_तथ्य_Source *selection_source;
};

काष्ठा SDL_WaylandPrimarySelectionDevice
{
    काष्ठा zwp_primary_selection_device_v1 *primary_selection_device;
    काष्ठा SDL_WaylandSeat *seat;

    SDL_WaylandPrimarySelectionSource *selection_source;
    SDL_WaylandPrimarySelectionOffer *selection_offer;
};

// Wayland Data Source / Primary Selection Source - (Sending)
बाह्य SDL_Wayland_तथ्य_Source *Wayland_तथ्य_Source_Create(SDL_Video_तथ्य *video_तथ्य);
बाह्य SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_तथ्य *video_तथ्य);
बाह्य ssize_t Wayland_तथ्य_Source_Send(SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर *mime_type, पूर्णांक fd);
बाह्य ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, स्थिर अक्षर *mime_type, पूर्णांक fd);
बाह्य व्योम Wayland_तथ्य_Source_Set_Callback(SDL_Wayland_तथ्य_Source *source, SDL_Clipboard_तथ्य_Callback तथ्य_callback, SDL_ClipboardCleanupCallback cleanup_callback, व्योम *userdata, Uint32 sequence);
बाह्य व्योम Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_तथ्य_Callback तथ्य_callback, SDL_ClipboardCleanupCallback cleanup_callback, व्योम *userdata);
बाह्य व्योम *Wayland_तथ्य_Source_Get_तथ्य(SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई);
बाह्य व्योम *Wayland_Primary_Selection_Source_Get_तथ्य(SDL_WaylandPrimarySelectionSource *source, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई);
बाह्य व्योम Wayland_तथ्य_Source_Destroy(SDL_Wayland_तथ्य_Source *source);
बाह्य व्योम Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source);

// Wayland Data / Primary Selection Offer - (Receiving)
बाह्य bool Wayland_तथ्य_Offer_Request_तथ्य_From_Self(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type, स्थिर काष्ठा wl_callback_listener *completion_listener, व्योम *userdata);
बाह्य व्योम *Wayland_तथ्य_Offer_Get_तथ्य_From_Self(SDL_Wayland_तथ्य_Offer *offer, माप_प्रकार *लंबाई);
बाह्य व्योम *Wayland_तथ्य_Offer_Receive(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई);
बाह्य व्योम *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई);
बाह्य bool Wayland_तथ्य_Offer_Has_MIME(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type);
बाह्य व्योम Wayland_तथ्य_Device_Set_Selection_Offer(SDL_Wayland_तथ्य_Device *तथ्य_device, SDL_Wayland_तथ्य_Offer *offer);
बाह्य bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type);
बाह्य bool Wayland_तथ्य_Offer_Add_MIME(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type);
बाह्य bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type);
बाह्य व्योम Wayland_तथ्य_Offer_Destroy(SDL_Wayland_तथ्य_Offer *offer);
बाह्य व्योम Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer);

// Clipboard / Primary Selection
बाह्य bool Wayland_तथ्य_Device_Set_Selection_Source(SDL_Wayland_तथ्य_Device *device, SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर **mime_types, माप_प्रकार mime_गिनती);
बाह्य bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *device, SDL_WaylandPrimarySelectionSource *source, स्थिर अक्षर *स्थिर *mime_types, माप_प्रकार mime_गिनती);

#पूर्ण_अगर // SDL_waylanddatamanager_h_
