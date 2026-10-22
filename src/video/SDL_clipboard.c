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

#अन्तर्भाव "SDL_clipboard_c.h"
#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "../events/SDL_events_c.h"
#अन्तर्भाव "../events/SDL_clipboardevents_c.h"

शून्य SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    यदि (_this->clipboard_mime_types) {
        प्रति (size_t i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = रिक्त;
        _this->अंक_clipboard_mime_types = 0;
    }
}


शून्य SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम;
    }

    यदि (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        प्रत्यागम;
    }

    यदि (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = रिक्त;
    _this->clipboard_cleanup = रिक्त;
    _this->clipboard_userdata = रिक्त;
}

bool SDL_SaveClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *mime_types, size_t अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    यदि (mime_types && अंक_mime_types > 0) {
        size_t अंक_allocated = 0;

        _this->clipboard_mime_types = (वर्ण **)SDL_malloc(अंक_mime_types * परिमाण(वर्ण *));
        यदि (_this->clipboard_mime_types) {
            प्रति (size_t i = 0; i < अंक_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                यदि (_this->clipboard_mime_types[i]) {
                    ++अंक_allocated;
                }
            }
        }
        यदि (अंक_allocated < अंक_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            प्रत्यागम false;
        }
        _this->अंक_clipboard_mime_types = अंक_mime_types;
    }
    प्रत्यागम true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, शून्य *userdata, ध्रुव वर्ण *ध्रुव *mime_types, size_t अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    // Parameter validation
    यदि (!((callback && mime_types && अंक_mime_types > 0) ||
          (!callback && !mime_types && अंक_mime_types == 0))) {
        प्रत्यागम SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    यदि (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    यदि (!SDL_SaveClipboardMimeTypes(mime_types, अंक_mime_types)) {
        SDL_ClearClipboardData();
        प्रत्यागम false;
    }

    यदि (_this->SetClipboardData) {
        यदि (!_this->SetClipboardData(_this)) {
            प्रत्यागम false;
        }
    } अन्यथा यदि (_this->SetClipboardText) {
        वर्ण *text = रिक्त;
        size_t size;

        प्रति (size_t i = 0; i < अंक_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];
            यदि (SDL_IsTextMimeType(mime_type)) {
                ध्रुव शून्य *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                यदि (data) {
                    text = (वर्ण *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    यदि (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        प्रत्यागम false;
                    }
                    भङ्ग;
                }
            }
        }
        यदि (text) {
            SDL_free(text);
        } अन्यथा {
            यदि (!_this->SetClipboardText(_this, "")) {
                प्रत्यागम false;
            }
        }
    }

    वर्ण **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अंक_mime_types, true);
    यदि (!mime_types_copy) {
        प्रत्यागम SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अंक_mime_types);
    प्रत्यागम true;
}

bool SDL_ClearClipboardData(शून्य)
{
    प्रत्यागम SDL_SetClipboardData(रिक्त, रिक्त, रिक्त, रिक्त, 0);
}

शून्य *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size)
{
    शून्य *data = रिक्त;

    यदि (_this->clipboard_callback) {
        यदि (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            प्रत्यागम रिक्त;
        }

        ध्रुव शून्य *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        यदि (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + परिमाण(Uint32));
            यदि (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, परिमाण(Uint32));
            } अन्यथा {
                *size = 0;
            }
        }
    }
    प्रत्यागम data;
}

शून्य *SDL_GetClipboardData(ध्रुव वर्ण *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        प्रत्यागम रिक्त;
    }
    यदि (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    यदि (_this->GetClipboardData) {
        प्रत्यागम _this->GetClipboardData(_this, mime_type, size);
    } अन्यथा यदि (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = _this->GetClipboardText(_this);
        यदि (text) {
            यदि (*text == '\0') {
                SDL_free(text);
                text = रिक्त;
            } अन्यथा {
                *size = SDL_strlen(text);
            }
        }
        प्रत्यागम text;
    } अन्यथा {
        प्रत्यागम SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    size_t i;

    प्रति (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
        यदि (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

bool SDL_HasClipboardData(ध्रुव वर्ण *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        प्रत्यागम SDL_InvalidParamError("mime_type");
    }

    यदि (_this->HasClipboardData) {
        प्रत्यागम _this->HasClipboardData(_this, mime_type);
    } अन्यथा यदि (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        प्रत्यागम _this->HasClipboardText(_this);
    } अन्यथा {
        प्रत्यागम SDL_HasInternalClipboardData(_this, mime_type);
    }
}

वर्ण **SDL_CopyClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *clipboard_mime_types, size_t अंक_mime_types, bool temporary)
{
    size_t allocSize = परिमाण(वर्ण *);
    प्रति (size_t i = 0; i < अंक_mime_types; i++) {
        allocSize += परिमाण(वर्ण *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    वर्ण *ret;
    यदि (temporary)
        ret = (वर्ण *)SDL_AllocateTemporaryMemory(allocSize);
    अन्यथा
        ret = (वर्ण *)SDL_malloc(allocSize);
    यदि (!ret) {
        प्रत्यागम रिक्त;
    }

    वर्ण **result = (वर्ण **)ret;
    ret += परिमाण(वर्ण *) * (अंक_mime_types + 1);

    प्रति (size_t i = 0; i < अंक_mime_types; i++) {
        result[i] = ret;

        ध्रुव वर्ण *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        वर्ण c;
        कुरु {
            c = *ret++ = *mime_type++;
        } यावत् (c != '\0');
    }
    result[अंक_mime_types] = रिक्त;

    प्रत्यागम result;

}

वर्ण **SDL_GetClipboardMimeTypes(size_t *अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (अंक_mime_types) {
        *अंक_mime_types = 0;
    }

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    यदि (अंक_mime_types) {
        *अंक_mime_types = _this->अंक_clipboard_mime_types;
    }
    प्रत्यागम SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ध्रुव वर्ण *mime_type)
{
    प्रत्यागम (SDL_strncmp(mime_type, "text", 4) == 0);
}

स्थिर ध्रुव वर्ण *ध्रुव *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अंक_mime_types)
{
    यदि (_this->GetTextMimeTypes) {
        प्रत्यागम _this->GetTextMimeTypes(_this, अंक_mime_types);
    } अन्यथा {
        स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अंक_mime_types = SDL_arraysize(text_mime_types);
        प्रत्यागम text_mime_types;
    }
}

ध्रुव शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, ध्रुव वर्ण *mime_type, size_t *size)
{
    वर्ण *text = (वर्ण *)userdata;
    यदि (text) {
        *size = SDL_strlen(text);
    } अन्यथा {
        *size = 0;
    }
    प्रत्यागम text;
}

bool SDL_SetClipboardText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t अंक_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);

        प्रत्यागम SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अंक_mime_types);
    }
    प्रत्यागम SDL_ClearClipboardData();
}

वर्ण *SDL_GetClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अंक_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;
    size_t length;
    वर्ण *text = रिक्त;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    प्रति (i = 0; i < अंक_mime_types; ++i) {
        शून्य *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        यदि (clipdata) {
            text = (वर्ण *)clipdata;
            भङ्ग;
        }
    }

    यदि (!text) {
        text = SDL_strdup("");
    }
    प्रत्यागम text;
}

bool SDL_HasClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अंक_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    प्रति (i = 0; i < अंक_mime_types; ++i) {
        यदि (SDL_HasClipboardData(text_mime_types[i])) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (!text) {
        text = "";
    }
    यदि (_this->SetPrimarySelectionText) {
        यदि (!_this->SetPrimarySelectionText(_this, text)) {
            प्रत्यागम false;
        }
    } अन्यथा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    वर्ण **mime_types = SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, true);
    यदि (!mime_types) {
        प्रत्यागम SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अंक_clipboard_mime_types);
    प्रत्यागम true;
}

वर्ण *SDL_GetPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    यदि (_this->GetPrimarySelectionText) {
        प्रत्यागम _this->GetPrimarySelectionText(_this);
    } अन्यथा {
        ध्रुव वर्ण *text = _this->primary_selection_text;
        यदि (!text) {
            text = "";
        }
        प्रत्यागम SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (_this->HasPrimarySelectionText) {
        प्रत्यागम _this->HasPrimarySelectionText(_this);
    } अन्यथा {
        यदि (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            प्रत्यागम true;
        } अन्यथा {
            प्रत्यागम false;
        }
    }
}

