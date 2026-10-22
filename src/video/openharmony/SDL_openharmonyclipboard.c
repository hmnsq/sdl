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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#include <database/pasteboard/oh_pasteboard.h>
#include <database/pasteboard/oh_pasteboard_err_code.h>
#include <database/udmf/udmf.h>
#include <database/udmf/uds.h>

#include "SDL_openharmonyvideo.h"
#include "SDL_openharmonyclipboard.h"
#include "../../core/openharmony/SDL_openharmony.h"
#include "../../events/SDL_events_c.h"

static void PasteboardNotifyCallback(void *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != NULL);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    nếu (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        trả_về;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != NULL);

    const char *mimetype = "text/plain";
    nếu (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        const size_t slen = SDL_strlen(mimetype);
        const size_t allocationsize = (slen + 1) + (sizeof (char *) * 2);
        char **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        nếu (new_mime_types) {
            char *ptr = (char *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = NULL;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

static void PasteboardFinalizeCallback(void *userdata)
{
    // do nothing.
}

void OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    nếu (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    nếu (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

void OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    nếu (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    nếu (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = NULL;
    }

    nếu (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = NULL;
    }
}

const char *const *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    static const char *const text_mime_types[] = { "text/plain" };
    *num_mime_types = SDL_arraysize(text_mime_types);
    trả_về text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, const char *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    nếu (!pasteboard) {
        trả_về SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    nếu (!udspt) {
        trả_về SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    nếu (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        trả_về SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    nếu (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        trả_về SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    const PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    nếu (rc != ERR_OK) {
        data->clipboard_set = true;
        trả_về SDL_SetError("OH_Pasteboard_SetData failed: %d", (số_nguyên) rc);
    }
    trả_về true;
}

char *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    nếu (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        trả_về NULL;
    }

    char *retval = NULL;
    nếu (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        số_nguyên rc = (số_nguyên) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        nếu (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            trả_về NULL;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        nếu (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            trả_về NULL;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        nếu (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            trả_về NULL;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        const char *utf8 = OH_UdsPlainText_GetContent(udspt);
        nếu (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } không_thì {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    trả_về retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    nếu (!pasteboard) {
        trả_về SDL_SetError("Pasteboard not initialized");
    }
    trả_về OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
