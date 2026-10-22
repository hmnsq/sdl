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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY

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
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->clipboard_समुच्चयः) {
        दत्त->clipboard_समुच्चयः = false;  // this was us, ignore it.
        प्रत्यागम;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) दत्त->oh_pasteboard;
    SDL_assert(pasteboard != रिक्त);

    ध्रुव वर्ण *mimetype = "text/plain";
    यदि (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ध्रुव size_t slen = SDL_strlen(mimetype);
        ध्रुव size_t allocationsize = (slen + 1) + (परिमाण (वर्ण *) * 2);
        वर्ण **new_mime_types = SDL_Allocate_Temporary_स्मृतिः(allocationsize);
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
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->clipboard_समुच्चयः = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    दत्त->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    दत्त->oh_pasteboard_observer = observer;
    यदि (observer) {
        OH_Pasteboard_Observer_समुच्चयः_दत्त(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    यदि (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_दत्त_CHANGE, observer);
    }
}

शून्य OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) दत्त->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) दत्त->oh_pasteboard;

    यदि (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_दत्त_CHANGE, observer);
    }

    यदि (observer) {
        OH_PasteboardObserver_Destroy(observer);
        दत्त->oh_pasteboard_observer = रिक्त;
    }

    यदि (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        दत्त->oh_pasteboard = रिक्त;
    }
}

ध्रुव वर्ण *ध्रुव *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types)
{
    स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = { "text/plain" };
    *अङ्कः_mime_types = SDL_arraysize(text_mime_types);
    प्रत्यागम text_mime_types;
}

bool OPENHARMONY_समुच्चयः_Clipboard_Text(SDL_VideoDevice *_this, ध्रुव वर्ण *text)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) दत्त->oh_pasteboard;
    यदि (!pasteboard) {
        प्रत्यागम SDL_समुच्चयः_Error("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    यदि (!udspt) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_Text_समुच्चयः_Content(udspt, text);

    OH_Udmf_लेखः *udmfrec = OH_Udmf_लेखः_Create();
    यदि (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        प्रत्यागम SDL_समुच्चयः_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_लेखः_सङ्कलय_Plain_Text(udmfrec, udspt);

    OH_Udmf_दत्त *udmfdata = OH_Udmf_दत्त_Create();
    यदि (!udmfdata) {
        OH_Udmf_लेखः_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        प्रत्यागम SDL_समुच्चयः_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_दत्त_सङ्कलय_लेखः(udmfdata, udmfrec);

    दत्त->clipboard_समुच्चयः = true;
    ध्रुव PASTEBOARD_Err_संहिता rc = OH_Pasteboard_समुच्चयः_दत्त(pasteboard, udmfdata);

    OH_Udmf_दत्त_Destroy(udmfdata);
    OH_Udmf_लेखः_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    यदि (rc != ERR_OK) {
        दत्त->clipboard_समुच्चयः = true;
        प्रत्यागम SDL_समुच्चयः_Error("OH_Pasteboard_SetData failed: %d", (पूर्णाङ्क) rc);
    }
    प्रत्यागम true;
}

वर्ण *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) दत्त->oh_pasteboard;
    यदि (!pasteboard) {
        SDL_समुच्चयः_Error("Pasteboard not initialized");
        प्रत्यागम रिक्त;
    }

    वर्ण *retval = रिक्त;
    यदि (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        पूर्णाङ्क rc = (पूर्णाङ्क) ERR_OK;
        OH_Udmf_दत्त *udmfdata = OH_Pasteboard_Get_दत्त(pasteboard, &rc);
        यदि (!udmfdata) {
            SDL_समुच्चयः_Error("Could not create OH_UdmfData instance %d", rc);
            प्रत्यागम रिक्त;
        }

        OH_Udmf_लेखः *udmfrec = OH_Udmf_दत्त_Get_लेखः(udmfdata, 0); // 0 == first record in udmfdata
        यदि (!udmfrec) {
            OH_Udmf_दत्त_Destroy(udmfdata);
            SDL_समुच्चयः_Error("Could not create OH_UdmfRecord instance");
            प्रत्यागम रिक्त;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        यदि (!udspt) {
            OH_Udmf_लेखः_Destroy(udmfrec);
            OH_Udmf_दत्त_Destroy(udmfdata);
            SDL_समुच्चयः_Error("Could not create OH_UdsPlainText instance");
            प्रत्यागम रिक्त;
        }

        OH_Udmf_लेखः_Get_Plain_Text(udmfrec, udspt);
        ध्रुव वर्ण *utf8 = OH_UdsPlainText_GetContent(udspt);
        यदि (!utf8) {
            SDL_समुच्चयः_Error("Could not get plaintext content");
        } अन्यथा {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_Udmf_लेखः_Destroy(udmfrec);
        OH_Udmf_दत्त_Destroy(udmfdata);
    }

    प्रत्यागम retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) दत्त->oh_pasteboard;
    यदि (!pasteboard) {
        प्रत्यागम SDL_समुच्चयः_Error("Pasteboard not initialized");
    }
    प्रत्यागम OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OPENHARMONY
