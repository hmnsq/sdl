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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#شامل <database/pasteboard/oh_pasteboard.h>
#شامل <database/pasteboard/oh_pasteboard_err_code.h>
#شامل <database/udmf/udmf.h>
#شامل <database/udmf/uds.h>

#شامل "SDL_openharmonyvideo.h"
#شامل "SDL_openharmonyclipboard.h"
#شامل "../../core/openharmony/SDL_openharmony.h"
#شامل "../../events/SDL_events_c.h"

ایستا تهی PasteboardNotifyCallback(تهی *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != پوچ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    اگر (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        بازگشت;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != پوچ);

    ثابت نویسه *mimetype = "text/plain";
    اگر (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ثابت size_t slen = SDL_strlen(mimetype);
        ثابت size_t allocationsize = (slen + 1) + (اندازه (نویسه *) * 2);
        نویسه **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        اگر (new_mime_types) {
            نویسه *ptr = (نویسه *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = پوچ;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ایستا تهی PasteboardFinalizeCallback(تهی *userdata)
{
    // do nothing.
}

تهی OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    اگر (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    اگر (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

تهی OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    اگر (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    اگر (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = پوچ;
    }

    اگر (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = پوچ;
    }
}

ثابت نویسه *ثابت *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *رقم_mime_types)
{
    ایستا ثابت نویسه *ثابت text_mime_types[] = { "text/plain" };
    *رقم_mime_types = SDL_arraysize(text_mime_types);
    بازگشت text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ثابت نویسه *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    اگر (!pasteboard) {
        بازگشت SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    اگر (!udspt) {
        بازگشت SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    اگر (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        بازگشت SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    اگر (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        بازگشت SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ثابت PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    اگر (rc != ERR_OK) {
        data->clipboard_set = true;
        بازگشت SDL_SetError("OH_Pasteboard_SetData failed: %d", (صحیح) rc);
    }
    بازگشت true;
}

نویسه *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    اگر (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        بازگشت پوچ;
    }

    نویسه *retval = پوچ;
    اگر (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        صحیح rc = (صحیح) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        اگر (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            بازگشت پوچ;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        اگر (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            بازگشت پوچ;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        اگر (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            بازگشت پوچ;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ثابت نویسه *utf8 = OH_UdsPlainText_GetContent(udspt);
        اگر (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } وگرنه {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    بازگشت retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    اگر (!pasteboard) {
        بازگشت SDL_SetError("Pasteboard not initialized");
    }
    بازگشت OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
