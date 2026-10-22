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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن <database/pasteboard/oh_pasteboard.h>
#ضمن <database/pasteboard/oh_pasteboard_err_code.h>
#ضمن <database/udmf/udmf.h>
#ضمن <database/udmf/uds.h>

#ضمن "SDL_openharmonyvideo.h"
#ضمن "SDL_openharmonyclipboard.h"
#ضمن "../../core/openharmony/SDL_openharmony.h"
#ضمن "../../events/SDL_events_c.h"

ساكن فراغ PasteboardNotifyCallback(فراغ *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != عدم);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    אם (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        החזר;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != عدم);

    ثابت حرف *mimetype = "text/plain";
    אם (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ثابت size_t slen = SDL_strlen(mimetype);
        ثابت size_t allocationsize = (slen + 1) + (حجم (حرف *) * 2);
        حرف **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        אם (new_mime_types) {
            حرف *ptr = (حرف *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = عدم;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ساكن فراغ PasteboardFinalizeCallback(فراغ *userdata)
{
    // do nothing.
}

فراغ OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    אם (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    אם (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

فراغ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    אם (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    אם (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = عدم;
    }

    אם (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = عدم;
    }
}

ثابت حرف *ثابت *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    ساكن ثابت حرف *ثابت text_mime_types[] = { "text/plain" };
    *num_mime_types = SDL_arraysize(text_mime_types);
    החזר text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ثابت حرف *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    אם (!pasteboard) {
        החזר SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    אם (!udspt) {
        החזר SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    אם (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        החזר SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    אם (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        החזר SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ثابت PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    אם (rc != ERR_OK) {
        data->clipboard_set = true;
        החזר SDL_SetError("OH_Pasteboard_SetData failed: %d", (صحيح) rc);
    }
    החזר true;
}

حرف *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    אם (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        החזר عدم;
    }

    حرف *retval = عدم;
    אם (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        صحيح rc = (صحيح) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        אם (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            החזר عدم;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        אם (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            החזר عدم;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        אם (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            החזר عدم;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ثابت حرف *utf8 = OH_UdsPlainText_GetContent(udspt);
        אם (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } אחרת {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    החזר retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    אם (!pasteboard) {
        החזר SDL_SetError("Pasteboard not initialized");
    }
    החזר OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
