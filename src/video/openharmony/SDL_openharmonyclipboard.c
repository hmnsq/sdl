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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#অন্তর্ভাব <database/pasteboard/oh_pasteboard.h>
#অন্তর্ভাব <database/pasteboard/oh_pasteboard_err_code.h>
#অন্তর্ভাব <database/udmf/udmf.h>
#অন্তর্ভাব <database/udmf/uds.h>

#অন্তর্ভাব "SDL_openharmonyvideo.h"
#অন্তর্ভাব "SDL_openharmonyclipboard.h"
#অন্তর্ভাব "../../core/openharmony/SDL_openharmony.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"

স্থির শূন্য PasteboardNotifyCallback(শূন্য *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ফাঁকা);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_তথ্য *তথ্য = _this->internal;

    যদি (তথ্য->clipboard_set) {
        তথ্য->clipboard_set = false;  // this was us, ignore it.
        ফেরত;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) তথ্য->oh_pasteboard;
    SDL_assert(pasteboard != ফাঁকা);

    ধ্রুবক অক্ষর *mimetype = "text/plain";
    যদি (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ধ্রুবক size_t slen = SDL_strlen(mimetype);
        ধ্রুবক size_t allocationsize = (slen + 1) + (আকার (অক্ষর *) * 2);
        অক্ষর **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        যদি (new_mime_types) {
            অক্ষর *ptr = (অক্ষর *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ফাঁকা;
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
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    তথ্য->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    তথ্য->oh_pasteboard_observer = observer;
    যদি (observer) {
        OH_Pasteboard_Observer_Set_তথ্য(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    যদি (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_তথ্য_CHANGE, observer);
    }
}

শূন্য OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) তথ্য->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) তথ্য->oh_pasteboard;

    যদি (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_তথ্য_CHANGE, observer);
    }

    যদি (observer) {
        OH_PasteboardObserver_Destroy(observer);
        তথ্য->oh_pasteboard_observer = ফাঁকা;
    }

    যদি (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        তথ্য->oh_pasteboard = ফাঁকা;
    }
}

ধ্রুবক অক্ষর *ধ্রুবক *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types)
{
    স্থির ধ্রুবক অক্ষর *ধ্রুবক text_mime_types[] = { "text/plain" };
    *অঙ্ক_mime_types = SDL_arraysize(text_mime_types);
    ফেরত text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) তথ্য->oh_pasteboard;
    যদি (!pasteboard) {
        ফেরত SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    যদি (!udspt) {
        ফেরত SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    যদি (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        ফেরত SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_Udmf_তথ্য *udmfdata = OH_Udmf_তথ্য_Create();
    যদি (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        ফেরত SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_Udmf_তথ্য_Add_Record(udmfdata, udmfrec);

    তথ্য->clipboard_set = true;
    ধ্রুবক PASTEBOARD_ErrCode rc = OH_Pasteboard_Set_তথ্য(pasteboard, udmfdata);

    OH_Udmf_তথ্য_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    যদি (rc != ERR_OK) {
        তথ্য->clipboard_set = true;
        ফেরত SDL_SetError("OH_Pasteboard_SetData failed: %d", (পূর্ণসংখ্যা) rc);
    }
    ফেরত true;
}

অক্ষর *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) তথ্য->oh_pasteboard;
    যদি (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        ফেরত ফাঁকা;
    }

    অক্ষর *retval = ফাঁকা;
    যদি (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        পূর্ণসংখ্যা rc = (পূর্ণসংখ্যা) ERR_OK;
        OH_Udmf_তথ্য *udmfdata = OH_Pasteboard_Get_তথ্য(pasteboard, &rc);
        যদি (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            ফেরত ফাঁকা;
        }

        OH_UdmfRecord *udmfrec = OH_Udmf_তথ্য_Get_Record(udmfdata, 0); // 0 == first record in udmfdata
        যদি (!udmfrec) {
            OH_Udmf_তথ্য_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            ফেরত ফাঁকা;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        যদি (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_Udmf_তথ্য_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            ফেরত ফাঁকা;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        ধ্রুবক অক্ষর *utf8 = OH_UdsPlainText_GetContent(udspt);
        যদি (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } অন্যথা {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_Udmf_তথ্য_Destroy(udmfdata);
    }

    ফেরত retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) তথ্য->oh_pasteboard;
    যদি (!pasteboard) {
        ফেরত SDL_SetError("Pasteboard not initialized");
    }
    ফেরত OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
