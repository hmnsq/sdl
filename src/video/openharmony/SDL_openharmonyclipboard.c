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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#અન્તર્ભાવ <database/pasteboard/oh_pasteboard.h>
#અન્તર્ભાવ <database/pasteboard/oh_pasteboard_err_code.h>
#અન્તર્ભાવ <database/udmf/udmf.h>
#અન્તર્ભાવ <database/udmf/uds.h>

#અન્તર્ભાવ "SDL_openharmonyvideo.h"
#અન્તર્ભાવ "SDL_openharmonyclipboard.h"
#અન્તર્ભાવ "../../core/openharmony/SDL_openharmony.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"

સ્થિર શૂન્ય PasteboardNotifyCallback(શૂન્ય *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ખાલી);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    જો (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        પાછા;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != ખાલી);

    અચલ અક્ષર *mimetype = "text/plain";
    જો (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        અચલ size_t slen = SDL_strlen(mimetype);
        અચલ size_t allocationsize = (slen + 1) + (કદ (અક્ષર *) * 2);
        અક્ષર **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        જો (new_mime_types) {
            અક્ષર *ptr = (અક્ષર *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ખાલી;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

સ્થિર શૂન્ય PasteboardFinalizeCallback(શૂન્ય *userdata)
{
    // do nothing.
}

શૂન્ય OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    જો (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    જો (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

શૂન્ય OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    જો (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    જો (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = ખાલી;
    }

    જો (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = ખાલી;
    }
}

અચલ અક્ષર *અચલ *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *અંક_mime_types)
{
    સ્થિર અચલ અક્ષર *અચલ text_mime_types[] = { "text/plain" };
    *અંક_mime_types = SDL_arraysize(text_mime_types);
    પાછા text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, અચલ અક્ષર *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    જો (!pasteboard) {
        પાછા SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    જો (!udspt) {
        પાછા SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    જો (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        પાછા SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    જો (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        પાછા SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    અચલ PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    જો (rc != ERR_OK) {
        data->clipboard_set = true;
        પાછા SDL_SetError("OH_Pasteboard_SetData failed: %d", (પૂર્ણાંક) rc);
    }
    પાછા true;
}

અક્ષર *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    જો (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        પાછા ખાલી;
    }

    અક્ષર *retval = ખાલી;
    જો (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        પૂર્ણાંક rc = (પૂર્ણાંક) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        જો (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            પાછા ખાલી;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        જો (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            પાછા ખાલી;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        જો (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            પાછા ખાલી;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        અચલ અક્ષર *utf8 = OH_UdsPlainText_GetContent(udspt);
        જો (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } નહીંતર {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    પાછા retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    જો (!pasteboard) {
        પાછા SDL_SetError("Pasteboard not initialized");
    }
    પાછા OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
