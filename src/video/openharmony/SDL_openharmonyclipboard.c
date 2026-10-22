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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY

#అన్తర్భావ <database/pasteboard/oh_pasteboard.h>
#అన్తర్భావ <database/pasteboard/oh_pasteboard_err_code.h>
#అన్తర్భావ <database/udmf/udmf.h>
#అన్తర్భావ <database/udmf/uds.h>

#అన్తర్భావ "SDL_openharmonyvideo.h"
#అన్తర్భావ "SDL_openharmonyclipboard.h"
#అన్తర్భావ "../../core/openharmony/SDL_openharmony.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

స్థిర శూన్య PasteboardNotifyCallback(శూన్య *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ఖాళీ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->clipboard_సమితి) {
        దత్తాంశం->clipboard_సమితి = false;  // this was us, ignore it.
        తిరిగి;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) దత్తాంశం->oh_pasteboard;
    SDL_assert(pasteboard != ఖాళీ);

    స్థిరరాశి అక్షరం *mimetype = "text/plain";
    ఒకవేళ (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        స్థిరరాశి size_t slen = SDL_strlen(mimetype);
        స్థిరరాశి size_t allocationsize = (slen + 1) + (పరిమాణం (అక్షరం *) * 2);
        అక్షరం **new_mime_types = SDL_Allocate_Temporary_జ్ఞాపకం(allocationsize);
        ఒకవేళ (new_mime_types) {
            అక్షరం *ptr = (అక్షరం *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ఖాళీ;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

స్థిర శూన్య PasteboardFinalizeCallback(శూన్య *userdata)
{
    // do nothing.
}

శూన్య OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->clipboard_సమితి = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    దత్తాంశం->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    దత్తాంశం->oh_pasteboard_observer = observer;
    ఒకవేళ (observer) {
        OH_Pasteboard_Observer_సమితి_దత్తాంశం(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    ఒకవేళ (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_దత్తాంశం_CHANGE, observer);
    }
}

శూన్య OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) దత్తాంశం->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) దత్తాంశం->oh_pasteboard;

    ఒకవేళ (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_దత్తాంశం_CHANGE, observer);
    }

    ఒకవేళ (observer) {
        OH_PasteboardObserver_Destroy(observer);
        దత్తాంశం->oh_pasteboard_observer = ఖాళీ;
    }

    ఒకవేళ (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        దత్తాంశం->oh_pasteboard = ఖాళీ;
    }
}

స్థిరరాశి అక్షరం *స్థిరరాశి *OPENHARMONY_Get_పాఠ్యం_Mime_Types(SDL_VideoDevice *_this, size_t *అంకె_mime_types)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి పాఠ్యం_mime_types[] = { "text/plain" };
    *అంకె_mime_types = SDL_arraysize(పాఠ్యం_mime_types);
    తిరిగి పాఠ్యం_mime_types;
}

bool OPENHARMONY_సమితి_Clipboard_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) దత్తాంశం->oh_pasteboard;
    ఒకవేళ (!pasteboard) {
        తిరిగి SDL_సమితి_Error("Pasteboard not initialized");
    }

    OH_Uds_Plain_పాఠ్యం *udspt = OH_Uds_Plain_పాఠ్యం_Create();
    ఒకవేళ (!udspt) {
        తిరిగి SDL_సమితి_Error("Could not create OH_UdsPlainText instance");
    }
    OH_Uds_Plain_పాఠ్యం_సమితి_Content(udspt, పాఠ్యం);

    OH_Udmf_రికార్డు *udmfrec = OH_Udmf_రికార్డు_Create();
    ఒకవేళ (!udmfrec) {
        OH_Uds_Plain_పాఠ్యం_Destroy(udspt);
        తిరిగి SDL_సమితి_Error("Could not create OH_UdmfRecord instance");
    }
    OH_Udmf_రికార్డు_కూడు_Plain_పాఠ్యం(udmfrec, udspt);

    OH_Udmf_దత్తాంశం *udmfdata = OH_Udmf_దత్తాంశం_Create();
    ఒకవేళ (!udmfdata) {
        OH_Udmf_రికార్డు_Destroy(udmfrec);
        OH_Uds_Plain_పాఠ్యం_Destroy(udspt);
        తిరిగి SDL_సమితి_Error("Could not create OH_UdmfData instance");
    }
    OH_Udmf_దత్తాంశం_కూడు_రికార్డు(udmfdata, udmfrec);

    దత్తాంశం->clipboard_సమితి = true;
    స్థిరరాశి PASTEBOARD_Err_సంకేతం rc = OH_Pasteboard_సమితి_దత్తాంశం(pasteboard, udmfdata);

    OH_Udmf_దత్తాంశం_Destroy(udmfdata);
    OH_Udmf_రికార్డు_Destroy(udmfrec);
    OH_Uds_Plain_పాఠ్యం_Destroy(udspt);

    ఒకవేళ (rc != ERR_OK) {
        దత్తాంశం->clipboard_సమితి = true;
        తిరిగి SDL_సమితి_Error("OH_Pasteboard_SetData failed: %d", (పూర్ణాంకం) rc);
    }
    తిరిగి true;
}

అక్షరం *OPENHARMONY_Get_Clipboard_పాఠ్యం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) దత్తాంశం->oh_pasteboard;
    ఒకవేళ (!pasteboard) {
        SDL_సమితి_Error("Pasteboard not initialized");
        తిరిగి ఖాళీ;
    }

    అక్షరం *retval = ఖాళీ;
    ఒకవేళ (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        పూర్ణాంకం rc = (పూర్ణాంకం) ERR_OK;
        OH_Udmf_దత్తాంశం *udmfdata = OH_Pasteboard_Get_దత్తాంశం(pasteboard, &rc);
        ఒకవేళ (!udmfdata) {
            SDL_సమితి_Error("Could not create OH_UdmfData instance %d", rc);
            తిరిగి ఖాళీ;
        }

        OH_Udmf_రికార్డు *udmfrec = OH_Udmf_దత్తాంశం_Get_రికార్డు(udmfdata, 0); // 0 == first record in udmfdata
        ఒకవేళ (!udmfrec) {
            OH_Udmf_దత్తాంశం_Destroy(udmfdata);
            SDL_సమితి_Error("Could not create OH_UdmfRecord instance");
            తిరిగి ఖాళీ;
        }

        OH_Uds_Plain_పాఠ్యం *udspt = OH_Uds_Plain_పాఠ్యం_Create();
        ఒకవేళ (!udspt) {
            OH_Udmf_రికార్డు_Destroy(udmfrec);
            OH_Udmf_దత్తాంశం_Destroy(udmfdata);
            SDL_సమితి_Error("Could not create OH_UdsPlainText instance");
            తిరిగి ఖాళీ;
        }

        OH_Udmf_రికార్డు_Get_Plain_పాఠ్యం(udmfrec, udspt);
        స్థిరరాశి అక్షరం *utf8 = OH_Uds_Plain_పాఠ్యం_Get_Content(udspt);
        ఒకవేళ (!utf8) {
            SDL_సమితి_Error("Could not get plaintext content");
        } లేకపోతే {
            retval = SDL_strdup(utf8);
        }

        OH_Uds_Plain_పాఠ్యం_Destroy(udspt);
        OH_Udmf_రికార్డు_Destroy(udmfrec);
        OH_Udmf_దత్తాంశం_Destroy(udmfdata);
    }

    తిరిగి retval;
}

bool OPENHARMONY_Has_Clipboard_పాఠ్యం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) దత్తాంశం->oh_pasteboard;
    ఒకవేళ (!pasteboard) {
        తిరిగి SDL_సమితి_Error("Pasteboard not initialized");
    }
    తిరిగి OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENHARMONY
