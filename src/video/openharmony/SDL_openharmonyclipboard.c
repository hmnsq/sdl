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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#অন্তর্ভাৱ <database/pasteboard/oh_pasteboard.h>
#অন্তর্ভাৱ <database/pasteboard/oh_pasteboard_err_code.h>
#অন্তর্ভাৱ <database/udmf/udmf.h>
#অন্তর্ভাৱ <database/udmf/uds.h>

#অন্তর্ভাৱ "SDL_openharmonyvideo.h"
#অন্তর্ভাৱ "SDL_openharmonyclipboard.h"
#অন্তর্ভাৱ "../../core/openharmony/SDL_openharmony.h"
#অন্তর্ভাৱ "../../events/SDL_events_c.h"

স্থির শূন্য PasteboardNotifyCallback(শূন্য *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != রিক্ত);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    যদি (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        ঘূৰাই;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != রিক্ত);

    ধ্রুৱ ৱর্ণ *mimetype = "text/plain";
    যদি (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ধ্রুৱ size_t slen = SDL_strlen(mimetype);
        ধ্রুৱ size_t allocationsize = (slen + 1) + (পরিমাণ (ৱর্ণ *) * 2);
        ৱর্ণ **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        যদি (new_mime_types) {
            ৱর্ণ *ptr = (ৱর্ণ *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = রিক্ত;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

স্থির শূন্য PasteboardFinalizeCallback(শূন্য *userdata)
{
    // do nothing.
}

শূন্য OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    যদি (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    যদি (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

শূন্য OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    যদি (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    যদি (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = রিক্ত;
    }

    যদি (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = রিক্ত;
    }
}

ধ্রুৱ ৱর্ণ *ধ্রুৱ *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types)
{
    স্থির ধ্রুৱ ৱর্ণ *ধ্রুৱ text_mime_types[] = { "text/plain" };
    *অঙ্ক_mime_types = SDL_arraysize(text_mime_types);
    ঘূৰাই text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    যদি (!pasteboard) {
        ঘূৰাই SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    যদি (!udspt) {
        ঘূৰাই SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    যদি (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        ঘূৰাই SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    যদি (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        ঘূৰাই SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ধ্রুৱ PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    যদি (rc != ERR_OK) {
        data->clipboard_set = true;
        ঘূৰাই SDL_SetError("OH_Pasteboard_SetData failed: %d", (পূর্ণাঙ্ক) rc);
    }
    ঘূৰাই true;
}

ৱর্ণ *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    যদি (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        ঘূৰাই রিক্ত;
    }

    ৱর্ণ *retval = রিক্ত;
    যদি (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        পূর্ণাঙ্ক rc = (পূর্ণাঙ্ক) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        যদি (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            ঘূৰাই রিক্ত;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        যদি (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            ঘূৰাই রিক্ত;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        যদি (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            ঘূৰাই রিক্ত;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ধ্রুৱ ৱর্ণ *utf8 = OH_UdsPlainText_GetContent(udspt);
        যদি (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } অন্যথা {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    ঘূৰাই retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    যদি (!pasteboard) {
        ঘূৰাই SDL_SetError("Pasteboard not initialized");
    }
    ঘূৰাই OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
