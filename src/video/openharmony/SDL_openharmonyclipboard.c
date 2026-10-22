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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ଅନ୍ତର୍ଭାଵ <database/pasteboard/oh_pasteboard.h>
#ଅନ୍ତର୍ଭାଵ <database/pasteboard/oh_pasteboard_err_code.h>
#ଅନ୍ତର୍ଭାଵ <database/udmf/udmf.h>
#ଅନ୍ତର୍ଭାଵ <database/udmf/uds.h>

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyclipboard.h"
#ଅନ୍ତର୍ଭାଵ "../../core/openharmony/SDL_openharmony.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

ସ୍ଥିର ଶୂନ୍ୟ PasteboardNotifyCallback(ଶୂନ୍ୟ *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ଖାଲି);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    ଯଦି (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        ଫେରନ୍ତୁ;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != ଖାଲି);

    ଅଚଳ ଅକ୍ଷର *mimetype = "text/plain";
    ଯଦି (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ଅଚଳ size_t slen = SDL_strlen(mimetype);
        ଅଚଳ size_t allocationsize = (slen + 1) + (ଆକାର (ଅକ୍ଷର *) * 2);
        ଅକ୍ଷର **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        ଯଦି (new_mime_types) {
            ଅକ୍ଷର *ptr = (ଅକ୍ଷର *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ଖାଲି;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ PasteboardFinalizeCallback(ଶୂନ୍ୟ *userdata)
{
    // do nothing.
}

ଶୂନ୍ୟ OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    ଯଦି (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    ଯଦି (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

ଶୂନ୍ୟ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    ଯଦି (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    ଯଦି (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = ଖାଲି;
    }

    ଯଦି (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = ଖାଲି;
    }
}

ଅଚଳ ଅକ୍ଷର *ଅଚଳ *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types)
{
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ text_mime_types[] = { "text/plain" };
    *ଅଙ୍କ_mime_types = SDL_arraysize(text_mime_types);
    ଫେରନ୍ତୁ text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ଯଦି (!pasteboard) {
        ଫେରନ୍ତୁ SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    ଯଦି (!udspt) {
        ଫେରନ୍ତୁ SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    ଯଦି (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        ଫେରନ୍ତୁ SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    ଯଦି (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        ଫେରନ୍ତୁ SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ଅଚଳ PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    ଯଦି (rc != ERR_OK) {
        data->clipboard_set = true;
        ଫେରନ୍ତୁ SDL_SetError("OH_Pasteboard_SetData failed: %d", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) rc);
    }
    ଫେରନ୍ତୁ true;
}

ଅକ୍ଷର *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ଯଦି (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଅକ୍ଷର *retval = ଖାଲି;
    ଯଦି (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା rc = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        ଯଦି (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        ଯଦି (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            ଫେରନ୍ତୁ ଖାଲି;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        ଯଦି (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            ଫେରନ୍ତୁ ଖାଲି;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ଅଚଳ ଅକ୍ଷର *utf8 = OH_UdsPlainText_GetContent(udspt);
        ଯଦି (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } ଅନ୍ୟଥା {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    ଫେରନ୍ତୁ retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ଯଦି (!pasteboard) {
        ଫେରନ୍ତୁ SDL_SetError("Pasteboard not initialized");
    }
    ଫେରନ୍ତୁ OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
