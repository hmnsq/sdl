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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

#شامل <database/pasteboard/oh_pasteboard.h>
#شامل <database/pasteboard/oh_pasteboard_err_code.h>
#شامل <database/udmf/udmf.h>
#شامل <database/udmf/uds.h>

#شامل "SDL_openharmonyvideo.h"
#شامل "SDL_openharmonyclipboard.h"
#شامل "../../core/openharmony/SDL_openharmony.h"
#شامل "../../events/SDL_events_c.h"

ساکن خالی PasteboardNotifyCallback(خالی *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != تہی);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->clipboard_سیٹ) {
        ڈیٹا->clipboard_سیٹ = false;  // this was us, ignore it.
        واپس;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ڈیٹا->oh_pasteboard;
    SDL_assert(pasteboard != تہی);

    ثابت حرف *mimetype = "text/plain";
    اگر (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ثابت size_t slen = SDL_strlen(mimetype);
        ثابت size_t allocationsize = (slen + 1) + (حجم (حرف *) * 2);
        حرف **new_mime_types = SDL_Allocate_Temporary_حافظہ(allocationsize);
        اگر (new_mime_types) {
            حرف *ptr = (حرف *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = تہی;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ساکن خالی PasteboardFinalizeCallback(خالی *userdata)
{
    // do nothing.
}

خالی OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->clipboard_سیٹ = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    ڈیٹا->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    ڈیٹا->oh_pasteboard_observer = observer;
    اگر (observer) {
        OH_Pasteboard_Observer_سیٹ_ڈیٹا(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    اگر (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_ڈیٹا_CHANGE, observer);
    }
}

خالی OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) ڈیٹا->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ڈیٹا->oh_pasteboard;

    اگر (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_ڈیٹا_CHANGE, observer);
    }

    اگر (observer) {
        OH_PasteboardObserver_Destroy(observer);
        ڈیٹا->oh_pasteboard_observer = تہی;
    }

    اگر (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        ڈیٹا->oh_pasteboard = تہی;
    }
}

ثابت حرف *ثابت *OPENHARMONY_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    ساکن ثابت حرف *ثابت متن_mime_types[] = { "text/plain" };
    *عدد_mime_types = SDL_arraysize(متن_mime_types);
    واپس متن_mime_types;
}

bool OPENHARMONY_سیٹ_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ڈیٹا->oh_pasteboard;
    اگر (!pasteboard) {
        واپس SDL_سیٹ_Error("Pasteboard not initialized");
    }

    OH_Uds_Plain_متن *udspt = OH_Uds_Plain_متن_Create();
    اگر (!udspt) {
        واپس SDL_سیٹ_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_متن_سیٹ_Content(udspt, متن);

    OH_Udmf_ریکارڈ *udmfrec = OH_Udmf_ریکارڈ_Create();
    اگر (!udmfrec) {
        OH_Uds_Plain_متن_Destroy(udspt);
        واپس SDL_سیٹ_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_ریکارڈ_جوڑو_Plain_متن(udmfrec, udspt);

    OH_Udmf_ڈیٹا *udmfdata = OH_Udmf_ڈیٹا_Create();
    اگر (!udmfdata) {
        OH_Udmf_ریکارڈ_Destroy(udmfrec);
        OH_Uds_Plain_متن_Destroy(udspt);
        واپس SDL_سیٹ_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_ڈیٹا_جوڑو_ریکارڈ(udmfdata, udmfrec);

    ڈیٹا->clipboard_سیٹ = true;
    ثابت PASTEBOARD_Err_رمز rc = OH_Pasteboard_سیٹ_ڈیٹا(pasteboard, udmfdata);

    OH_Udmf_ڈیٹا_Destroy(udmfdata);
    OH_Udmf_ریکارڈ_Destroy(udmfrec);
    OH_Uds_Plain_متن_Destroy(udspt);

    اگر (rc != ERR_OK) {
        ڈیٹا->clipboard_سیٹ = true;
        واپس SDL_سیٹ_Error("OH_Pasteboard_SetData failed: %d", (صحیح) rc);
    }
    واپس true;
}

حرف *OPENHARMONY_Get_Clipboard_متن(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ڈیٹا->oh_pasteboard;
    اگر (!pasteboard) {
        SDL_سیٹ_Error("Pasteboard not initialized");
        واپس تہی;
    }

    حرف *retval = تہی;
    اگر (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        صحیح rc = (صحیح) ERR_OK;
        OH_Udmf_ڈیٹا *udmfdata = OH_Pasteboard_Get_ڈیٹا(pasteboard, &rc);
        اگر (!udmfdata) {
            SDL_سیٹ_Error("Could not create OH_UdmfData instance %d", rc);
            واپس تہی;
        }

        OH_Udmf_ریکارڈ *udmfrec = OH_Udmf_ڈیٹا_Get_ریکارڈ(udmfdata, 0); // 0 == first record in udmfdata
        اگر (!udmfrec) {
            OH_Udmf_ڈیٹا_Destroy(udmfdata);
            SDL_سیٹ_Error("Could not create OH_UdmfRecord instance");
            واپس تہی;
        }

        OH_Uds_Plain_متن *udspt = OH_Uds_Plain_متن_Create();
        اگر (!udspt) {
            OH_Udmf_ریکارڈ_Destroy(udmfrec);
            OH_Udmf_ڈیٹا_Destroy(udmfdata);
            SDL_سیٹ_Error("Could not create OH_UdsPlainText instance");
            واپس تہی;
        }

        OH_Udmf_ریکارڈ_Get_Plain_متن(udmfrec, udspt);
        ثابت حرف *utf8 = OH_Uds_Plain_متن_Get_Content(udspt);
        اگر (!utf8) {
            SDL_سیٹ_Error("Could not get plaintext content");
        } ورنہ {
            retval = SDL_strdup(utf8);
        }

        OH_Uds_Plain_متن_Destroy(udspt);
        OH_Udmf_ریکارڈ_Destroy(udmfrec);
        OH_Udmf_ڈیٹا_Destroy(udmfdata);
    }

    واپس retval;
}

bool OPENHARMONY_Has_Clipboard_متن(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ڈیٹا->oh_pasteboard;
    اگر (!pasteboard) {
        واپس SDL_سیٹ_Error("Pasteboard not initialized");
    }
    واپس OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#اگر_ختم // SDL_VIDEO_DRIVER_OPENHARMONY
