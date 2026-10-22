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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENHARMONY

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
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->clipboard_مجموعه) {
        داده->clipboard_مجموعه = false;  // this was us, ignore it.
        أرجع;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) داده->oh_pasteboard;
    SDL_assert(pasteboard != عدم);

    ثابت حرف *mimetype = "text/plain";
    إذا (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ثابت size_t slen = SDL_strlen(mimetype);
        ثابت size_t allocationsize = (slen + 1) + (حجم (حرف *) * 2);
        حرف **new_mime_types = SDL_Allocate_Temporary_حافظه(allocationsize);
        إذا (new_mime_types) {
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
    SDL_Video_داده *داده = _this->داخلی;

    داده->clipboard_مجموعه = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    داده->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    داده->oh_pasteboard_observer = observer;
    إذا (observer) {
        OH_Pasteboard_Observer_مجموعه_داده(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    إذا (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_داده_CHANGE, observer);
    }
}

فراغ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) داده->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) داده->oh_pasteboard;

    إذا (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_داده_CHANGE, observer);
    }

    إذا (observer) {
        OH_PasteboardObserver_Destroy(observer);
        داده->oh_pasteboard_observer = عدم;
    }

    إذا (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        داده->oh_pasteboard = عدم;
    }
}

ثابت حرف *ثابت *OPENHARMONY_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *رقم_mime_types)
{
    ساكن ثابت حرف *ثابت متن_mime_types[] = { "text/plain" };
    *رقم_mime_types = SDL_arraysize(متن_mime_types);
    أرجع متن_mime_types;
}

bool OPENHARMONY_مجموعه_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    SDL_Video_داده *داده = _this->داخلی;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) داده->oh_pasteboard;
    إذا (!pasteboard) {
        أرجع SDL_مجموعه_Error("Pasteboard not initialized");
    }

    OH_Uds_Plain_متن *udspt = OH_Uds_Plain_متن_Create();
    إذا (!udspt) {
        أرجع SDL_مجموعه_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_متن_مجموعه_Content(udspt, متن);

    OH_Udmf_رکورد *udmfrec = OH_Udmf_رکورد_Create();
    إذا (!udmfrec) {
        OH_Uds_Plain_متن_Destroy(udspt);
        أرجع SDL_مجموعه_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_رکورد_جمع_کن_Plain_متن(udmfrec, udspt);

    OH_Udmf_داده *udmfdata = OH_Udmf_داده_Create();
    إذا (!udmfdata) {
        OH_Udmf_رکورد_Destroy(udmfrec);
        OH_Uds_Plain_متن_Destroy(udspt);
        أرجع SDL_مجموعه_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_داده_جمع_کن_رکورد(udmfdata, udmfrec);

    داده->clipboard_مجموعه = true;
    ثابت PASTEBOARD_Err_کد rc = OH_Pasteboard_مجموعه_داده(pasteboard, udmfdata);

    OH_Udmf_داده_Destroy(udmfdata);
    OH_Udmf_رکورد_Destroy(udmfrec);
    OH_Uds_Plain_متن_Destroy(udspt);

    إذا (rc != ERR_OK) {
        داده->clipboard_مجموعه = true;
        أرجع SDL_مجموعه_Error("OH_Pasteboard_SetData failed: %d", (صحيح) rc);
    }
    أرجع true;
}

حرف *OPENHARMONY_Get_Clipboard_متن(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) داده->oh_pasteboard;
    إذا (!pasteboard) {
        SDL_مجموعه_Error("Pasteboard not initialized");
        أرجع عدم;
    }

    حرف *retval = عدم;
    إذا (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        صحيح rc = (صحيح) ERR_OK;
        OH_Udmf_داده *udmfdata = OH_Pasteboard_Get_داده(pasteboard, &rc);
        إذا (!udmfdata) {
            SDL_مجموعه_Error("Could not create OH_UdmfData instance %d", rc);
            أرجع عدم;
        }

        OH_Udmf_رکورد *udmfrec = OH_Udmf_داده_Get_رکورد(udmfdata, 0); // 0 == first record in udmfdata
        إذا (!udmfrec) {
            OH_Udmf_داده_Destroy(udmfdata);
            SDL_مجموعه_Error("Could not create OH_UdmfRecord instance");
            أرجع عدم;
        }

        OH_Uds_Plain_متن *udspt = OH_Uds_Plain_متن_Create();
        إذا (!udspt) {
            OH_Udmf_رکورد_Destroy(udmfrec);
            OH_Udmf_داده_Destroy(udmfdata);
            SDL_مجموعه_Error("Could not create OH_UdsPlainText instance");
            أرجع عدم;
        }

        OH_Udmf_رکورد_Get_Plain_متن(udmfrec, udspt);
        ثابت حرف *utf8 = OH_Uds_Plain_متن_Get_Content(udspt);
        إذا (!utf8) {
            SDL_مجموعه_Error("Could not get plaintext content");
        } وإلا {
            retval = SDL_strdup(utf8);
        }

        OH_Uds_Plain_متن_Destroy(udspt);
        OH_Udmf_رکورد_Destroy(udmfrec);
        OH_Udmf_داده_Destroy(udmfdata);
    }

    أرجع retval;
}

bool OPENHARMONY_Has_Clipboard_متن(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) داده->oh_pasteboard;
    إذا (!pasteboard) {
        أرجع SDL_مجموعه_Error("Pasteboard not initialized");
    }
    أرجع OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#پایان_اگر // SDL_VIDEO_DRIVER_OPENHARMONY
