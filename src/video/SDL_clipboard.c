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
    जइ (_this->clipboard_mime_types) {
        प्रति (size_t i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = रिक्त;
        _this->अङ्कः_clipboard_mime_types = 0;
    }
}


शून्य SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम;
    }

    जइ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        प्रत्यागम;
    }

    जइ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = रिक्त;
    _this->clipboard_cleanup = रिक्त;
    _this->clipboard_userdata = रिक्त;
}

bool SDL_SaveClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    जइ (mime_types && अङ्कः_mime_types > 0) {
        size_t अङ्कः_allocated = 0;

        _this->clipboard_mime_types = (वर्ण **)SDL_malloc(अङ्कः_mime_types * परिमाण(वर्ण *));
        जइ (_this->clipboard_mime_types) {
            प्रति (size_t i = 0; i < अङ्कः_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                जइ (_this->clipboard_mime_types[i]) {
                    ++अङ्कः_allocated;
                }
            }
        }
        जइ (अङ्कः_allocated < अङ्कः_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            प्रत्यागम false;
        }
        _this->अङ्कः_clipboard_mime_types = अङ्कः_mime_types;
    }
    प्रत्यागम true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, शून्य *userdata, ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    // Parameter validation
    जइ (!((callback && mime_types && अङ्कः_mime_types > 0) ||
          (!callback && !mime_types && अङ्कः_mime_types == 0))) {
        प्रत्यागम SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    जइ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    जइ (!SDL_SaveClipboardMimeTypes(mime_types, अङ्कः_mime_types)) {
        SDL_ClearClipboardData();
        प्रत्यागम false;
    }

    जइ (_this->SetClipboardData) {
        जइ (!_this->SetClipboardData(_this)) {
            प्रत्यागम false;
        }
    } अण्णहा जइ (_this->SetClipboardText) {
        वर्ण *text = रिक्त;
        size_t size;

        प्रति (size_t i = 0; i < अङ्कः_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];
            जइ (SDL_IsTextMimeType(mime_type)) {
                ध्रुव शून्य *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                जइ (data) {
                    text = (वर्ण *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    जइ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        प्रत्यागम false;
                    }
                    भङ्ग;
                }
            }
        }
        जइ (text) {
            SDL_free(text);
        } अण्णहा {
            जइ (!_this->SetClipboardText(_this, "")) {
                प्रत्यागम false;
            }
        }
    }

    वर्ण **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अङ्कः_mime_types, true);
    जइ (!mime_types_copy) {
        प्रत्यागम SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अङ्कः_mime_types);
    प्रत्यागम true;
}

bool SDL_ClearClipboardData(शून्य)
{
    प्रत्यागम SDL_SetClipboardData(रिक्त, रिक्त, रिक्त, रिक्त, 0);
}

शून्य *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size)
{
    शून्य *data = रिक्त;

    जइ (_this->clipboard_callback) {
        जइ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            प्रत्यागम रिक्त;
        }

        ध्रुव शून्य *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        जइ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + परिमाण(Uint32));
            जइ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, परिमाण(Uint32));
            } अण्णहा {
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

    जइ (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        प्रत्यागम रिक्त;
    }
    जइ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    जइ (_this->GetClipboardData) {
        प्रत्यागम _this->GetClipboardData(_this, mime_type, size);
    } अण्णहा जइ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = _this->GetClipboardText(_this);
        जइ (text) {
            जइ (*text == '\0') {
                SDL_free(text);
                text = रिक्त;
            } अण्णहा {
                *size = SDL_strlen(text);
            }
        }
        प्रत्यागम text;
    } अण्णहा {
        प्रत्यागम SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    size_t i;

    प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
        जइ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

bool SDL_HasClipboardData(ध्रुव वर्ण *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        प्रत्यागम SDL_InvalidParamError("mime_type");
    }

    जइ (_this->HasClipboardData) {
        प्रत्यागम _this->HasClipboardData(_this, mime_type);
    } अण्णहा जइ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        प्रत्यागम _this->HasClipboardText(_this);
    } अण्णहा {
        प्रत्यागम SDL_HasInternalClipboardData(_this, mime_type);
    }
}

वर्ण **SDL_CopyClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *clipboard_mime_types, size_t अङ्कः_mime_types, bool temporary)
{
    size_t allocSize = परिमाण(वर्ण *);
    प्रति (size_t i = 0; i < अङ्कः_mime_types; i++) {
        allocSize += परिमाण(वर्ण *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    वर्ण *ret;
    जइ (temporary)
        ret = (वर्ण *)SDL_AllocateTemporaryMemory(allocSize);
    अण्णहा
        ret = (वर्ण *)SDL_malloc(allocSize);
    जइ (!ret) {
        प्रत्यागम रिक्त;
    }

    वर्ण **result = (वर्ण **)ret;
    ret += परिमाण(वर्ण *) * (अङ्कः_mime_types + 1);

    प्रति (size_t i = 0; i < अङ्कः_mime_types; i++) {
        result[i] = ret;

        ध्रुव वर्ण *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        वर्ण c;
        करेहि {
            c = *ret++ = *mime_type++;
        } जाव (c != '\0');
    }
    result[अङ्कः_mime_types] = रिक्त;

    प्रत्यागम result;

}

वर्ण **SDL_GetClipboardMimeTypes(size_t *अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (अङ्कः_mime_types) {
        *अङ्कः_mime_types = 0;
    }

    जइ (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    जइ (अङ्कः_mime_types) {
        *अङ्कः_mime_types = _this->अङ्कः_clipboard_mime_types;
    }
    प्रत्यागम SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ध्रुव वर्ण *mime_type)
{
    प्रत्यागम (SDL_strncmp(mime_type, "text", 4) == 0);
}

स्थिर ध्रुव वर्ण *ध्रुव *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types)
{
    जइ (_this->GetTextMimeTypes) {
        प्रत्यागम _this->GetTextMimeTypes(_this, अङ्कः_mime_types);
    } अण्णहा {
        स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अङ्कः_mime_types = SDL_arraysize(text_mime_types);
        प्रत्यागम text_mime_types;
    }
}

ध्रुव शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, ध्रुव वर्ण *mime_type, size_t *size)
{
    वर्ण *text = (वर्ण *)userdata;
    जइ (text) {
        *size = SDL_strlen(text);
    } अण्णहा {
        *size = 0;
    }
    प्रत्यागम text;
}

bool SDL_SetClipboardText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    जइ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);

        प्रत्यागम SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अङ्कः_mime_types);
    }
    प्रत्यागम SDL_ClearClipboardData();
}

वर्ण *SDL_GetClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;
    size_t length;
    वर्ण *text = रिक्त;

    जइ (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    प्रति (i = 0; i < अङ्कः_mime_types; ++i) {
        शून्य *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        जइ (clipdata) {
            text = (वर्ण *)clipdata;
            भङ्ग;
        }
    }

    जइ (!text) {
        text = SDL_strdup("");
    }
    प्रत्यागम text;
}

bool SDL_HasClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    प्रति (i = 0; i < अङ्कः_mime_types; ++i) {
        जइ (SDL_HasClipboardData(text_mime_types[i])) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    जइ (!text) {
        text = "";
    }
    जइ (_this->SetPrimarySelectionText) {
        जइ (!_this->SetPrimarySelectionText(_this, text)) {
            प्रत्यागम false;
        }
    } अण्णहा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    वर्ण **mime_types = SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, true);
    जइ (!mime_types) {
        प्रत्यागम SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अङ्कः_clipboard_mime_types);
    प्रत्यागम true;
}

वर्ण *SDL_GetPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    जइ (_this->GetPrimarySelectionText) {
        प्रत्यागम _this->GetPrimarySelectionText(_this);
    } अण्णहा {
        ध्रुव वर्ण *text = _this->primary_selection_text;
        जइ (!text) {
            text = "";
        }
        प्रत्यागम SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जइ (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    जइ (_this->HasPrimarySelectionText) {
        प्रत्यागम _this->HasPrimarySelectionText(_this);
    } अण्णहा {
        जइ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            प्रत्यागम true;
        } अण्णहा {
            प्रत्यागम false;
        }
    }
}

