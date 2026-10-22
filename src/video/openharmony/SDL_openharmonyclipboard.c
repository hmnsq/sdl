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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#அந்தர்பாவ <database/pasteboard/oh_pasteboard.h>
#அந்தர்பாவ <database/pasteboard/oh_pasteboard_err_code.h>
#அந்தர்பாவ <database/udmf/udmf.h>
#அந்தர்பாவ <database/udmf/uds.h>

#அந்தர்பாவ "SDL_openharmonyvideo.h"
#அந்தர்பாவ "SDL_openharmonyclipboard.h"
#அந்தர்பாவ "../../core/openharmony/SDL_openharmony.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

நிலையான வெறுமை PasteboardNotifyCallback(வெறுமை *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != வெற்று);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    எனில் (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        திரும்பு;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != வெற்று);

    மாறிலி எழுத்து *mimetype = "text/plain";
    எனில் (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        மாறிலி size_t slen = SDL_strlen(mimetype);
        மாறிலி size_t allocationsize = (slen + 1) + (அளவு (எழுத்து *) * 2);
        எழுத்து **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        எனில் (new_mime_types) {
            எழுத்து *ptr = (எழுத்து *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = வெற்று;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

நிலையான வெறுமை PasteboardFinalizeCallback(வெறுமை *userdata)
{
    // do nothing.
}

வெறுமை OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    எனில் (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    எனில் (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

வெறுமை OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    எனில் (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    எனில் (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = வெற்று;
    }

    எனில் (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = வெற்று;
    }
}

மாறிலி எழுத்து *மாறிலி *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *இலக்கம்_mime_types)
{
    நிலையான மாறிலி எழுத்து *மாறிலி text_mime_types[] = { "text/plain" };
    *இலக்கம்_mime_types = SDL_arraysize(text_mime_types);
    திரும்பு text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, மாறிலி எழுத்து *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    எனில் (!pasteboard) {
        திரும்பு SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    எனில் (!udspt) {
        திரும்பு SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    எனில் (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        திரும்பு SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    எனில் (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        திரும்பு SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    மாறிலி PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    எனில் (rc != ERR_OK) {
        data->clipboard_set = true;
        திரும்பு SDL_SetError("OH_Pasteboard_SetData failed: %d", (முழு) rc);
    }
    திரும்பு true;
}

எழுத்து *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    எனில் (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        திரும்பு வெற்று;
    }

    எழுத்து *retval = வெற்று;
    எனில் (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        முழு rc = (முழு) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        எனில் (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            திரும்பு வெற்று;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        எனில் (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            திரும்பு வெற்று;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        எனில் (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            திரும்பு வெற்று;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        மாறிலி எழுத்து *utf8 = OH_UdsPlainText_GetContent(udspt);
        எனில் (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } இல்லையெனில் {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    திரும்பு retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    எனில் (!pasteboard) {
        திரும்பு SDL_SetError("Pasteboard not initialized");
    }
    திரும்பு OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
