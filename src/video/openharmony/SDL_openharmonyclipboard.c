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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY

#समावेश <database/pasteboard/oh_pasteboard.h>
#समावेश <database/pasteboard/oh_pasteboard_err_code.h>
#समावेश <database/udmf/udmf.h>
#समावेश <database/udmf/uds.h>

#समावेश "SDL_openharmonyvideo.h"
#समावेश "SDL_openharmonyclipboard.h"
#समावेश "../../core/openharmony/SDL_openharmony.h"
#समावेश "../../events/SDL_events_c.h"

अटल व्योम PasteboardNotifyCallback(व्योम *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != शून्य);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->clipboard_set) {
        तथ्य->clipboard_set = false;  // this was us, ignore it.
        वापस;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) तथ्य->oh_pasteboard;
    SDL_assert(pasteboard != शून्य);

    स्थिर अक्षर *mimetype = "text/plain";
    अगर (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        स्थिर माप_प्रकार slen = SDL_strlen(mimetype);
        स्थिर माप_प्रकार allocationsize = (slen + 1) + (माप (अक्षर *) * 2);
        अक्षर **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        अगर (new_mime_types) {
            अक्षर *ptr = (अक्षर *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = शून्य;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

अटल व्योम PasteboardFinalizeCallback(व्योम *userdata)
{
    // do nothing.
}

व्योम OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    तथ्य->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    तथ्य->oh_pasteboard_observer = observer;
    अगर (observer) {
        OH_Pasteboard_Observer_Set_तथ्य(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    अगर (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_तथ्य_CHANGE, observer);
    }
}

व्योम OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) तथ्य->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) तथ्य->oh_pasteboard;

    अगर (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_तथ्य_CHANGE, observer);
    }

    अगर (observer) {
        OH_PasteboardObserver_Destroy(observer);
        तथ्य->oh_pasteboard_observer = शून्य;
    }

    अगर (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        तथ्य->oh_pasteboard = शून्य;
    }
}

स्थिर अक्षर *स्थिर *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types)
{
    अटल स्थिर अक्षर *स्थिर text_mime_types[] = { "text/plain" };
    *अंक_mime_types = SDL_arraysize(text_mime_types);
    वापस text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, स्थिर अक्षर *text)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) तथ्य->oh_pasteboard;
    अगर (!pasteboard) {
        वापस SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    अगर (!udspt) {
        वापस SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    अगर (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        वापस SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_Udmf_तथ्य *udmfdata = OH_Udmf_तथ्य_Create();
    अगर (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        वापस SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_Udmf_तथ्य_Add_Record(udmfdata, udmfrec);

    तथ्य->clipboard_set = true;
    स्थिर PASTEBOARD_ErrCode rc = OH_Pasteboard_Set_तथ्य(pasteboard, udmfdata);

    OH_Udmf_तथ्य_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    अगर (rc != ERR_OK) {
        तथ्य->clipboard_set = true;
        वापस SDL_SetError("OH_Pasteboard_SetData failed: %d", (पूर्णांक) rc);
    }
    वापस true;
}

अक्षर *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) तथ्य->oh_pasteboard;
    अगर (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        वापस शून्य;
    }

    अक्षर *retval = शून्य;
    अगर (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        पूर्णांक rc = (पूर्णांक) ERR_OK;
        OH_Udmf_तथ्य *udmfdata = OH_Pasteboard_Get_तथ्य(pasteboard, &rc);
        अगर (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            वापस शून्य;
        }

        OH_UdmfRecord *udmfrec = OH_Udmf_तथ्य_Get_Record(udmfdata, 0); // 0 == first record in udmfdata
        अगर (!udmfrec) {
            OH_Udmf_तथ्य_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            वापस शून्य;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        अगर (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_Udmf_तथ्य_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            वापस शून्य;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        स्थिर अक्षर *utf8 = OH_UdsPlainText_GetContent(udspt);
        अगर (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } अन्यथा {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_Udmf_तथ्य_Destroy(udmfdata);
    }

    वापस retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) तथ्य->oh_pasteboard;
    अगर (!pasteboard) {
        वापस SDL_SetError("Pasteboard not initialized");
    }
    वापस OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENHARMONY
