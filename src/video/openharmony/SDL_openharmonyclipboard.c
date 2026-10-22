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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#अन्तर्भाव <database/pasteboard/oh_pasteboard.h>
#अन्तर्भाव <database/pasteboard/oh_pasteboard_err_code.h>
#अन्तर्भाव <database/udmf/udmf.h>
#अन्तर्भाव <database/udmf/uds.h>

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonyclipboard.h"
#अन्तर्भाव "../../core/openharmony/SDL_openharmony.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

स्थिर शून्य PasteboardNotifyCallback(शून्य *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != रिक्त);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    यदि (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        प्रत्यागम;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != रिक्त);

    ध्रुव वर्ण *mimetype = "text/plain";
    यदि (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ध्रुव size_t slen = SDL_strlen(mimetype);
        ध्रुव size_t allocationsize = (slen + 1) + (परिमाण (वर्ण *) * 2);
        वर्ण **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        यदि (new_mime_types) {
            वर्ण *ptr = (वर्ण *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = रिक्त;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

स्थिर शून्य PasteboardFinalizeCallback(शून्य *userdata)
{
    // do nothing.
}

शून्य OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    यदि (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    यदि (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

शून्य OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    यदि (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    यदि (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = रिक्त;
    }

    यदि (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = रिक्त;
    }
}

ध्रुव वर्ण *ध्रुव *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अंक_mime_types)
{
    स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = { "text/plain" };
    *अंक_mime_types = SDL_arraysize(text_mime_types);
    प्रत्यागम text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ध्रुव वर्ण *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    यदि (!pasteboard) {
        प्रत्यागम SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    यदि (!udspt) {
        प्रत्यागम SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    यदि (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        प्रत्यागम SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    यदि (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        प्रत्यागम SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ध्रुव PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    यदि (rc != ERR_OK) {
        data->clipboard_set = true;
        प्रत्यागम SDL_SetError("OH_Pasteboard_SetData failed: %d", (पूर्णाङ्क) rc);
    }
    प्रत्यागम true;
}

वर्ण *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    यदि (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        प्रत्यागम रिक्त;
    }

    वर्ण *retval = रिक्त;
    यदि (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        पूर्णाङ्क rc = (पूर्णाङ्क) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        यदि (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            प्रत्यागम रिक्त;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        यदि (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            प्रत्यागम रिक्त;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        यदि (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            प्रत्यागम रिक्त;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ध्रुव वर्ण *utf8 = OH_UdsPlainText_GetContent(udspt);
        यदि (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } अन्यथा {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    प्रत्यागम retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    यदि (!pasteboard) {
        प्रत्यागम SDL_SetError("Pasteboard not initialized");
    }
    प्रत्यागम OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
