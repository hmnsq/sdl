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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ಅನ್ತರ್ಭಾವ <database/pasteboard/oh_pasteboard.h>
#ಅನ್ತರ್ಭಾವ <database/pasteboard/oh_pasteboard_err_code.h>
#ಅನ್ತರ್ಭಾವ <database/udmf/udmf.h>
#ಅನ್ತರ್ಭಾವ <database/udmf/uds.h>

#ಅನ್ತರ್ಭಾವ "SDL_openharmonyvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyclipboard.h"
#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

ಸ್ಥಿರ ಶೂನ್ಯ PasteboardNotifyCallback(ಶೂನ್ಯ *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ರಿಕ್ತ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    ಯದಿ (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        ಪ್ರತ್ಯಾಗಮ;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != ರಿಕ್ತ);

    ಧ್ರುವ ವರ್ಣ *mimetype = "text/plain";
    ಯದಿ (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ಧ್ರುವ size_t slen = SDL_strlen(mimetype);
        ಧ್ರುವ size_t allocationsize = (slen + 1) + (ಪರಿಮಾಣ (ವರ್ಣ *) * 2);
        ವರ್ಣ **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        ಯದಿ (new_mime_types) {
            ವರ್ಣ *ptr = (ವರ್ಣ *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ರಿಕ್ತ;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ PasteboardFinalizeCallback(ಶೂನ್ಯ *userdata)
{
    // do nothing.
}

ಶೂನ್ಯ OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    ಯದಿ (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    ಯದಿ (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

ಶೂನ್ಯ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    ಯದಿ (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    ಯದಿ (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = ರಿಕ್ತ;
    }

    ಯದಿ (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = ರಿಕ್ತ;
    }
}

ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ text_mime_types[] = { "text/plain" };
    *ಅಂಕೆ_mime_types = SDL_arraysize(text_mime_types);
    ಪ್ರತ್ಯಾಗಮ text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ಯದಿ (!pasteboard) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    ಯದಿ (!udspt) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    ಯದಿ (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    ಯದಿ (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    ಧ್ರುವ PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    ಯದಿ (rc != ERR_OK) {
        data->clipboard_set = true;
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OH_Pasteboard_SetData failed: %d", (ಪೂರ್ಣಾಙ್ಕ) rc);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ವರ್ಣ *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ಯದಿ (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ವರ್ಣ *retval = ರಿಕ್ತ;
    ಯದಿ (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        ಪೂರ್ಣಾಙ್ಕ rc = (ಪೂರ್ಣಾಙ್ಕ) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        ಯದಿ (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        ಯದಿ (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        ಯದಿ (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ಧ್ರುವ ವರ್ಣ *utf8 = OH_UdsPlainText_GetContent(udspt);
        ಯದಿ (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } ಅನ್ಯಥಾ {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    ಪ್ರತ್ಯಾಗಮ retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    ಯದಿ (!pasteboard) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Pasteboard not initialized");
    }
    ಪ್ರತ್ಯಾಗಮ OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
