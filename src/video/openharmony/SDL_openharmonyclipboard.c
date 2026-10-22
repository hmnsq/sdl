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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

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
    SDL_assert(userdata != ಖಾಲಿ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->clipboard_ಗಣ) {
        ದತ್ತಾಂಶ->clipboard_ಗಣ = false;  // this was us, ignore it.
        ಹಿಂತಿರುಗಿ;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ದತ್ತಾಂಶ->oh_pasteboard;
    SDL_assert(pasteboard != ಖಾಲಿ);

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mimetype = "text/plain";
    ಆದರೆ (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        ಸ್ಥಿರಾಂಕ size_t slen = SDL_strlen(mimetype);
        ಸ್ಥಿರಾಂಕ size_t allocationsize = (slen + 1) + (ಗಾತ್ರ (ಅಕ್ಷರ *) * 2);
        ಅಕ್ಷರ **new_mime_types = SDL_Allocate_Temporary_ಸ್ಮರಣೆ(allocationsize);
        ಆದರೆ (new_mime_types) {
            ಅಕ್ಷರ *ptr = (ಅಕ್ಷರ *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ಖಾಲಿ;
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
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->clipboard_ಗಣ = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    ದತ್ತಾಂಶ->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    ದತ್ತಾಂಶ->oh_pasteboard_observer = observer;
    ಆದರೆ (observer) {
        OH_Pasteboard_Observer_ಗಣ_ದತ್ತಾಂಶ(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    ಆದರೆ (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_ದತ್ತಾಂಶ_CHANGE, observer);
    }
}

ಶೂನ್ಯ OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) ದತ್ತಾಂಶ->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ದತ್ತಾಂಶ->oh_pasteboard;

    ಆದರೆ (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_ದತ್ತಾಂಶ_CHANGE, observer);
    }

    ಆದರೆ (observer) {
        OH_PasteboardObserver_Destroy(observer);
        ದತ್ತಾಂಶ->oh_pasteboard_observer = ಖಾಲಿ;
    }

    ಆದರೆ (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        ದತ್ತಾಂಶ->oh_pasteboard = ಖಾಲಿ;
    }
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *OPENHARMONY_Get_ಪಠ್ಯ_Mime_Types(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ ಪಠ್ಯ_mime_types[] = { "text/plain" };
    *ಅಂಕೆ_mime_types = SDL_arraysize(ಪಠ್ಯ_mime_types);
    ಹಿಂತಿರುಗಿ ಪಠ್ಯ_mime_types;
}

bool OPENHARMONY_ಗಣ_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ದತ್ತಾಂಶ->oh_pasteboard;
    ಆದರೆ (!pasteboard) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Pasteboard not initialized");
    }

    OH_Uds_Plain_ಪಠ್ಯ *udspt = OH_Uds_Plain_ಪಠ್ಯ_Create();
    ಆದರೆ (!udspt) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_ಪಠ್ಯ_ಗಣ_Content(udspt, ಪಠ್ಯ);

    OH_Udmf_ದಾಖಲೆ *udmfrec = OH_Udmf_ದಾಖಲೆ_Create();
    ಆದರೆ (!udmfrec) {
        OH_Uds_Plain_ಪಠ್ಯ_Destroy(udspt);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_ದಾಖಲೆ_ಕೂಡಿಸು_Plain_ಪಠ್ಯ(udmfrec, udspt);

    OH_Udmf_ದತ್ತಾಂಶ *udmfdata = OH_Udmf_ದತ್ತಾಂಶ_Create();
    ಆದರೆ (!udmfdata) {
        OH_Udmf_ದಾಖಲೆ_Destroy(udmfrec);
        OH_Uds_Plain_ಪಠ್ಯ_Destroy(udspt);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_ದತ್ತಾಂಶ_ಕೂಡಿಸು_ದಾಖಲೆ(udmfdata, udmfrec);

    ದತ್ತಾಂಶ->clipboard_ಗಣ = true;
    ಸ್ಥಿರಾಂಕ PASTEBOARD_Err_ಸಂಕೇತ rc = OH_Pasteboard_ಗಣ_ದತ್ತಾಂಶ(pasteboard, udmfdata);

    OH_Udmf_ದತ್ತಾಂಶ_Destroy(udmfdata);
    OH_Udmf_ದಾಖಲೆ_Destroy(udmfrec);
    OH_Uds_Plain_ಪಠ್ಯ_Destroy(udspt);

    ಆದರೆ (rc != ERR_OK) {
        ದತ್ತಾಂಶ->clipboard_ಗಣ = true;
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OH_Pasteboard_SetData failed: %d", (ಪೂರ್ಣಾಂಕ) rc);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಅಕ್ಷರ *OPENHARMONY_Get_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ದತ್ತಾಂಶ->oh_pasteboard;
    ಆದರೆ (!pasteboard) {
        SDL_ಗಣ_Error("Pasteboard not initialized");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಅಕ್ಷರ *retval = ಖಾಲಿ;
    ಆದರೆ (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        ಪೂರ್ಣಾಂಕ rc = (ಪೂರ್ಣಾಂಕ) ERR_OK;
        OH_Udmf_ದತ್ತಾಂಶ *udmfdata = OH_Pasteboard_Get_ದತ್ತಾಂಶ(pasteboard, &rc);
        ಆದರೆ (!udmfdata) {
            SDL_ಗಣ_Error("Could not create OH_UdmfData instance %d", rc);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        OH_Udmf_ದಾಖಲೆ *udmfrec = OH_Udmf_ದತ್ತಾಂಶ_Get_ದಾಖಲೆ(udmfdata, 0); // 0 == first record in udmfdata
        ಆದರೆ (!udmfrec) {
            OH_Udmf_ದತ್ತಾಂಶ_Destroy(udmfdata);
            SDL_ಗಣ_Error("Could not create OH_UdmfRecord instance");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        OH_Uds_Plain_ಪಠ್ಯ *udspt = OH_Uds_Plain_ಪಠ್ಯ_Create();
        ಆದರೆ (!udspt) {
            OH_Udmf_ದಾಖಲೆ_Destroy(udmfrec);
            OH_Udmf_ದತ್ತಾಂಶ_Destroy(udmfdata);
            SDL_ಗಣ_Error("Could not create OH_UdsPlainText instance");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        OH_Udmf_ದಾಖಲೆ_Get_Plain_ಪಠ್ಯ(udmfrec, udspt);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *utf8 = OH_Uds_Plain_ಪಠ್ಯ_Get_Content(udspt);
        ಆದರೆ (!utf8) {
            SDL_ಗಣ_Error("Could not get plaintext content");
        } ಇಲ್ಲದಿದ್ದರೆ {
            retval = SDL_strdup(utf8);
        }

        OH_Uds_Plain_ಪಠ್ಯ_Destroy(udspt);
        OH_Udmf_ದಾಖಲೆ_Destroy(udmfrec);
        OH_Udmf_ದತ್ತಾಂಶ_Destroy(udmfdata);
    }

    ಹಿಂತಿರುಗಿ retval;
}

bool OPENHARMONY_Has_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) ದತ್ತಾಂಶ->oh_pasteboard;
    ಆದರೆ (!pasteboard) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Pasteboard not initialized");
    }
    ಹಿಂತಿರುಗಿ OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENHARMONY
