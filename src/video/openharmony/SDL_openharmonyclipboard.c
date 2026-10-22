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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY

#ਅਨ੍ਤਰ੍ਭਾਵ <database/pasteboard/oh_pasteboard.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <database/pasteboard/oh_pasteboard_err_code.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <database/udmf/udmf.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <database/udmf/uds.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openharmony/SDL_openharmony.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

ਸਥਿਰ ਖਾਲੀ PasteboardNotifyCallback(ਖਾਲੀ *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ਨਿਰਾ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->clipboard_ਸੈੱਟ) {
        ਅੰਕੜੇ->clipboard_ਸੈੱਟ = false;  // this was us, ignore it.
        ਵਾਪਸ;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ਅੰਕੜੇ->oh_pasteboard;
    SDL_assert(pasteboard != ਨਿਰਾ);

    ਅਚਲ ਅੱਖਰ *mimetype = "text/plain";
    ਜੇ (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ਅਚਲ size_t slen = SDL_strlen(mimetype);
        ਅਚਲ size_t allocationsize = (slen + 1) + (ਆਕਾਰ (ਅੱਖਰ *) * 2);
        ਅੱਖਰ **new_mime_types = SDL_Allocate_Temporary_ਸਮ੍ਰਿਤੀ(allocationsize);
        ਜੇ (new_mime_types) {
            ਅੱਖਰ *ptr = (ਅੱਖਰ *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ਨਿਰਾ;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ PasteboardFinalizeCallback(ਖਾਲੀ *userdata)
{
    // do nothing.
}

ਖਾਲੀ OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->clipboard_ਸੈੱਟ = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    ਅੰਕੜੇ->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    ਅੰਕੜੇ->oh_pasteboard_observer = observer;
    ਜੇ (observer) {
        OH_Pasteboard_Observer_ਸੈੱਟ_ਅੰਕੜੇ(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    ਜੇ (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_ਅੰਕੜੇ_CHANGE, observer);
    }
}

ਖਾਲੀ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) ਅੰਕੜੇ->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ਅੰਕੜੇ->oh_pasteboard;

    ਜੇ (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_ਅੰਕੜੇ_CHANGE, observer);
    }

    ਜੇ (observer) {
        OH_PasteboardObserver_Destroy(observer);
        ਅੰਕੜੇ->oh_pasteboard_observer = ਨਿਰਾ;
    }

    ਜੇ (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        ਅੰਕੜੇ->oh_pasteboard = ਨਿਰਾ;
    }
}

ਅਚਲ ਅੱਖਰ *ਅਚਲ *OPENHARMONY_Get_ਪਾਠ_Mime_Types(SDL_VideoDevice *_this, size_t *ਅੰਕ_mime_types)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ ਪਾਠ_mime_types[] = { "text/plain" };
    *ਅੰਕ_mime_types = SDL_arraysize(ਪਾਠ_mime_types);
    ਵਾਪਸ ਪਾਠ_mime_types;
}

bool OPENHARMONY_ਸੈੱਟ_Clipboard_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ਅੰਕੜੇ->oh_pasteboard;
    ਜੇ (!pasteboard) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Pasteboard not initialized");
    }

    OH_Uds_Plain_ਪਾਠ *udspt = OH_Uds_Plain_ਪਾਠ_Create();
    ਜੇ (!udspt) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_ਪਾਠ_ਸੈੱਟ_Content(udspt, ਪਾਠ);

    OH_Udmf_ਰਿਕਾਰਡ *udmfrec = OH_Udmf_ਰਿਕਾਰਡ_Create();
    ਜੇ (!udmfrec) {
        OH_Uds_Plain_ਪਾਠ_Destroy(udspt);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_ਰਿਕਾਰਡ_ਜੋੜੋ_Plain_ਪਾਠ(udmfrec, udspt);

    OH_Udmf_ਅੰਕੜੇ *udmfdata = OH_Udmf_ਅੰਕੜੇ_Create();
    ਜੇ (!udmfdata) {
        OH_Udmf_ਰਿਕਾਰਡ_Destroy(udmfrec);
        OH_Uds_Plain_ਪਾਠ_Destroy(udspt);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_ਅੰਕੜੇ_ਜੋੜੋ_ਰਿਕਾਰਡ(udmfdata, udmfrec);

    ਅੰਕੜੇ->clipboard_ਸੈੱਟ = true;
    ਅਚਲ PASTEBOARD_Err_ਕੋਡ rc = OH_Pasteboard_ਸੈੱਟ_ਅੰਕੜੇ(pasteboard, udmfdata);

    OH_Udmf_ਅੰਕੜੇ_Destroy(udmfdata);
    OH_Udmf_ਰਿਕਾਰਡ_Destroy(udmfrec);
    OH_Uds_Plain_ਪਾਠ_Destroy(udspt);

    ਜੇ (rc != ERR_OK) {
        ਅੰਕੜੇ->clipboard_ਸੈੱਟ = true;
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OH_Pasteboard_SetData failed: %d", (ਪੂਰਨ) rc);
    }
    ਵਾਪਸ true;
}

ਅੱਖਰ *OPENHARMONY_Get_Clipboard_ਪਾਠ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ਅੰਕੜੇ->oh_pasteboard;
    ਜੇ (!pasteboard) {
        SDL_ਸੈੱਟ_Error("Pasteboard not initialized");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੱਖਰ *retval = ਨਿਰਾ;
    ਜੇ (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        ਪੂਰਨ rc = (ਪੂਰਨ) ERR_OK;
        OH_Udmf_ਅੰਕੜੇ *udmfdata = OH_Pasteboard_Get_ਅੰਕੜੇ(pasteboard, &rc);
        ਜੇ (!udmfdata) {
            SDL_ਸੈੱਟ_Error("Could not create OH_UdmfData instance %d", rc);
            ਵਾਪਸ ਨਿਰਾ;
        }

        OH_Udmf_ਰਿਕਾਰਡ *udmfrec = OH_Udmf_ਅੰਕੜੇ_Get_ਰਿਕਾਰਡ(udmfdata, 0); // 0 == first record in udmfdata
        ਜੇ (!udmfrec) {
            OH_Udmf_ਅੰਕੜੇ_Destroy(udmfdata);
            SDL_ਸੈੱਟ_Error("Could not create OH_UdmfRecord instance");
            ਵਾਪਸ ਨਿਰਾ;
        }

        OH_Uds_Plain_ਪਾਠ *udspt = OH_Uds_Plain_ਪਾਠ_Create();
        ਜੇ (!udspt) {
            OH_Udmf_ਰਿਕਾਰਡ_Destroy(udmfrec);
            OH_Udmf_ਅੰਕੜੇ_Destroy(udmfdata);
            SDL_ਸੈੱਟ_Error("Could not create OH_UdsPlainText instance");
            ਵਾਪਸ ਨਿਰਾ;
        }

        OH_Udmf_ਰਿਕਾਰਡ_Get_Plain_ਪਾਠ(udmfrec, udspt);
        ਅਚਲ ਅੱਖਰ *utf8 = OH_Uds_Plain_ਪਾਠ_Get_Content(udspt);
        ਜੇ (!utf8) {
            SDL_ਸੈੱਟ_Error("Could not get plaintext content");
        } ਨਹੀਂਤਾਂ {
            retval = SDL_strdup(utf8);
        }

        OH_Uds_Plain_ਪਾਠ_Destroy(udspt);
        OH_Udmf_ਰਿਕਾਰਡ_Destroy(udmfrec);
        OH_Udmf_ਅੰਕੜੇ_Destroy(udmfdata);
    }

    ਵਾਪਸ retval;
}

bool OPENHARMONY_Has_Clipboard_ਪਾਠ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ਅੰਕੜੇ->oh_pasteboard;
    ਜੇ (!pasteboard) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Pasteboard not initialized");
    }
    ਵਾਪਸ OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENHARMONY
