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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#അന്തര്ഭാവ <database/pasteboard/oh_pasteboard.h>
#അന്തര്ഭാവ <database/pasteboard/oh_pasteboard_err_code.h>
#അന്തര്ഭാവ <database/udmf/udmf.h>
#അന്തര്ഭാവ <database/udmf/uds.h>

#അന്തര്ഭാവ "SDL_openharmonyvideo.h"
#അന്തര്ഭാവ "SDL_openharmonyclipboard.h"
#അന്തര്ഭാവ "../../core/openharmony/SDL_openharmony.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"

സ്ഥിതം ശൂന്യം PasteboardNotifyCallback(ശൂന്യം *userdata, Pasteboard_NotifyType type)
{
    SDL_assert(userdata != ശൂന്യ);
    SDL_VideoDevice *_this = (SDL_VideoDevice *) userdata;
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->clipboard_set) {
        data->clipboard_set = false;  // this was us, ignore it.
        തിരികെ;
    }

    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    SDL_assert(pasteboard != ശൂന്യ);

    സ്ഥിരം അക്ഷരം *mimetype = "text/plain";
    എങ്കിൽ (OH_Pasteboard_HasType(pasteboard, mimetype)) {
        സ്ഥിരം size_t slen = SDL_strlen(mimetype);
        സ്ഥിരം size_t allocationsize = (slen + 1) + (വലുപ്പം (അക്ഷരം *) * 2);
        അക്ഷരം **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
        എങ്കിൽ (new_mime_types) {
            അക്ഷരം *ptr = (അക്ഷരം *)(new_mime_types + 2);
            SDL_strlcpy(ptr, mimetype, slen + 1);
            new_mime_types[0] = ptr;
            new_mime_types[1] = ശൂന്യ;
            SDL_SendClipboardUpdate(false, new_mime_types, 1);
        }
    }
}

സ്ഥിതം ശൂന്യം PasteboardFinalizeCallback(ശൂന്യം *userdata)
{
    // do nothing.
}

ശൂന്യം OPENHARMONY_InitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->clipboard_set = false;

    OH_Pasteboard *pasteboard = OH_Pasteboard_Create();
    data->oh_pasteboard = pasteboard;

    OH_PasteboardObserver *observer = OH_PasteboardObserver_Create();
    data->oh_pasteboard_observer = observer;
    എങ്കിൽ (observer) {
        OH_PasteboardObserver_SetData(observer, _this, PasteboardNotifyCallback, PasteboardFinalizeCallback);
    }

    എങ്കിൽ (pasteboard && observer) {
        OH_Pasteboard_Subscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }
}

ശൂന്യം OPENHARMONY_QuitClipboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    OH_PasteboardObserver *observer = (OH_PasteboardObserver *) data->oh_pasteboard_observer;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;

    എങ്കിൽ (observer && pasteboard) {
        OH_Pasteboard_Unsubscribe(pasteboard, NOTIFY_LOCAL_DATA_CHANGE, observer);
    }

    എങ്കിൽ (observer) {
        OH_PasteboardObserver_Destroy(observer);
        data->oh_pasteboard_observer = ശൂന്യ;
    }

    എങ്കിൽ (pasteboard) {
        OH_Pasteboard_Destroy(pasteboard);
        data->oh_pasteboard = ശൂന്യ;
    }
}

സ്ഥിരം അക്ഷരം *സ്ഥിരം *OPENHARMONY_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *അക്കം_mime_types)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം text_mime_types[] = { "text/plain" };
    *അക്കം_mime_types = SDL_arraysize(text_mime_types);
    തിരികെ text_mime_types;
}

bool OPENHARMONY_SetClipboardText(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *text)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    എങ്കിൽ (!pasteboard) {
        തിരികെ SDL_SetError("Pasteboard not initialized");
    }

    OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
    എങ്കിൽ (!udspt) {
        തിരികെ SDL_SetError("Could not create OH_UdsPlainText instance");
    }
    OH_UdsPlainText_SetContent(udspt, text);

    OH_UdmfRecord *udmfrec = OH_UdmfRecord_Create();
    എങ്കിൽ (!udmfrec) {
        OH_UdsPlainText_Destroy(udspt);
        തിരികെ SDL_SetError("Could not create OH_UdmfRecord instance");
    }
    OH_UdmfRecord_AddPlainText(udmfrec, udspt);

    OH_UdmfData *udmfdata = OH_UdmfData_Create();
    എങ്കിൽ (!udmfdata) {
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdsPlainText_Destroy(udspt);
        തിരികെ SDL_SetError("Could not create OH_UdmfData instance");
    }
    OH_UdmfData_AddRecord(udmfdata, udmfrec);

    data->clipboard_set = true;
    സ്ഥിരം PASTEBOARD_ErrCode rc = OH_Pasteboard_SetData(pasteboard, udmfdata);

    OH_UdmfData_Destroy(udmfdata);
    OH_UdmfRecord_Destroy(udmfrec);
    OH_UdsPlainText_Destroy(udspt);

    എങ്കിൽ (rc != ERR_OK) {
        data->clipboard_set = true;
        തിരികെ SDL_SetError("OH_Pasteboard_SetData failed: %d", (പൂർണ്ണസംഖ്യ) rc);
    }
    തിരികെ true;
}

അക്ഷരം *OPENHARMONY_GetClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    എങ്കിൽ (!pasteboard) {
        SDL_SetError("Pasteboard not initialized");
        തിരികെ ശൂന്യ;
    }

    അക്ഷരം *retval = ശൂന്യ;
    എങ്കിൽ (OH_Pasteboard_HasType(pasteboard, "text/plain")) {
        പൂർണ്ണസംഖ്യ rc = (പൂർണ്ണസംഖ്യ) ERR_OK;
        OH_UdmfData *udmfdata = OH_Pasteboard_GetData(pasteboard, &rc);
        എങ്കിൽ (!udmfdata) {
            SDL_SetError("Could not create OH_UdmfData instance %d", rc);
            തിരികെ ശൂന്യ;
        }

        OH_UdmfRecord *udmfrec = OH_UdmfData_GetRecord(udmfdata, 0); // 0 == first record in udmfdata
        എങ്കിൽ (!udmfrec) {
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdmfRecord instance");
            തിരികെ ശൂന്യ;
        }

        OH_UdsPlainText *udspt = OH_UdsPlainText_Create();
        എങ്കിൽ (!udspt) {
            OH_UdmfRecord_Destroy(udmfrec);
            OH_UdmfData_Destroy(udmfdata);
            SDL_SetError("Could not create OH_UdsPlainText instance");
            തിരികെ ശൂന്യ;
        }

        OH_UdmfRecord_GetPlainText(udmfrec, udspt);
        സ്ഥിരം അക്ഷരം *utf8 = OH_UdsPlainText_GetContent(udspt);
        എങ്കിൽ (!utf8) {
            SDL_SetError("Could not get plaintext content");
        } അല്ലെങ്കിൽ {
            retval = SDL_strdup(utf8);
        }

        OH_UdsPlainText_Destroy(udspt);
        OH_UdmfRecord_Destroy(udmfrec);
        OH_UdmfData_Destroy(udmfdata);
    }

    തിരികെ retval;
}

bool OPENHARMONY_HasClipboardText(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    OH_Pasteboard *pasteboard = (OH_Pasteboard *) data->oh_pasteboard;
    എങ്കിൽ (!pasteboard) {
        തിരികെ SDL_SetError("Pasteboard not initialized");
    }
    തിരികെ OH_Pasteboard_HasType(pasteboard, "text/plain");
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
