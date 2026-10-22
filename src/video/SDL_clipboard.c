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
    सचे (_this->clipboard_mime_types) {
        अत्थाय (size_t i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
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

    सचे (!_this) {
        पटिनिवत्त;
    }

    सचे (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        पटिनिवत्त;
    }

    सचे (_this->clipboard_cleanup) {
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

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    सचे (mime_types && अङ्कः_mime_types > 0) {
        size_t अङ्कः_allocated = 0;

        _this->clipboard_mime_types = (वर्ण **)SDL_malloc(अङ्कः_mime_types * परिमाण(वर्ण *));
        सचे (_this->clipboard_mime_types) {
            अत्थाय (size_t i = 0; i < अङ्कः_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                सचे (_this->clipboard_mime_types[i]) {
                    ++अङ्कः_allocated;
                }
            }
        }
        सचे (अङ्कः_allocated < अङ्कः_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            पटिनिवत्त false;
        }
        _this->अङ्कः_clipboard_mime_types = अङ्कः_mime_types;
    }
    पटिनिवत्त true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, शून्य *userdata, ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    // Parameter validation
    सचे (!((callback && mime_types && अङ्कः_mime_types > 0) ||
          (!callback && !mime_types && अङ्कः_mime_types == 0))) {
        पटिनिवत्त SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    सचे (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    सचे (!SDL_SaveClipboardMimeTypes(mime_types, अङ्कः_mime_types)) {
        SDL_ClearClipboardData();
        पटिनिवत्त false;
    }

    सचे (_this->SetClipboardData) {
        सचे (!_this->SetClipboardData(_this)) {
            पटिनिवत्त false;
        }
    } अञ्ञथा सचे (_this->SetClipboardText) {
        वर्ण *text = रिक्त;
        size_t size;

        अत्थाय (size_t i = 0; i < अङ्कः_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];
            सचे (SDL_IsTextMimeType(mime_type)) {
                ध्रुव शून्य *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                सचे (data) {
                    text = (वर्ण *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    सचे (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        पटिनिवत्त false;
                    }
                    भङ्ग;
                }
            }
        }
        सचे (text) {
            SDL_free(text);
        } अञ्ञथा {
            सचे (!_this->SetClipboardText(_this, "")) {
                पटिनिवत्त false;
            }
        }
    }

    वर्ण **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अङ्कः_mime_types, true);
    सचे (!mime_types_copy) {
        पटिनिवत्त SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अङ्कः_mime_types);
    पटिनिवत्त true;
}

bool SDL_ClearClipboardData(शून्य)
{
    पटिनिवत्त SDL_SetClipboardData(रिक्त, रिक्त, रिक्त, रिक्त, 0);
}

शून्य *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size)
{
    शून्य *data = रिक्त;

    सचे (_this->clipboard_callback) {
        सचे (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            पटिनिवत्त रिक्त;
        }

        ध्रुव शून्य *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        सचे (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + परिमाण(Uint32));
            सचे (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, परिमाण(Uint32));
            } अञ्ञथा {
                *size = 0;
            }
        }
    }
    पटिनिवत्त data;
}

शून्य *SDL_GetClipboardData(ध्रुव वर्ण *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        पटिनिवत्त रिक्त;
    }
    सचे (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    सचे (_this->GetClipboardData) {
        पटिनिवत्त _this->GetClipboardData(_this, mime_type, size);
    } अञ्ञथा सचे (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = _this->GetClipboardText(_this);
        सचे (text) {
            सचे (*text == '\0') {
                SDL_free(text);
                text = रिक्त;
            } अञ्ञथा {
                *size = SDL_strlen(text);
            }
        }
        पटिनिवत्त text;
    } अञ्ञथा {
        पटिनिवत्त SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    size_t i;

    अत्थाय (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
        सचे (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

bool SDL_HasClipboardData(ध्रुव वर्ण *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        पटिनिवत्त SDL_InvalidParamError("mime_type");
    }

    सचे (_this->HasClipboardData) {
        पटिनिवत्त _this->HasClipboardData(_this, mime_type);
    } अञ्ञथा सचे (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        पटिनिवत्त _this->HasClipboardText(_this);
    } अञ्ञथा {
        पटिनिवत्त SDL_HasInternalClipboardData(_this, mime_type);
    }
}

वर्ण **SDL_CopyClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *clipboard_mime_types, size_t अङ्कः_mime_types, bool temporary)
{
    size_t allocSize = परिमाण(वर्ण *);
    अत्थाय (size_t i = 0; i < अङ्कः_mime_types; i++) {
        allocSize += परिमाण(वर्ण *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    वर्ण *ret;
    सचे (temporary)
        ret = (वर्ण *)SDL_AllocateTemporaryMemory(allocSize);
    अञ्ञथा
        ret = (वर्ण *)SDL_malloc(allocSize);
    सचे (!ret) {
        पटिनिवत्त रिक्त;
    }

    वर्ण **result = (वर्ण **)ret;
    ret += परिमाण(वर्ण *) * (अङ्कः_mime_types + 1);

    अत्थाय (size_t i = 0; i < अङ्कः_mime_types; i++) {
        result[i] = ret;

        ध्रुव वर्ण *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        वर्ण c;
        करोहि {
            c = *ret++ = *mime_type++;
        } याव (c != '\0');
    }
    result[अङ्कः_mime_types] = रिक्त;

    पटिनिवत्त result;

}

वर्ण **SDL_GetClipboardMimeTypes(size_t *अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (अङ्कः_mime_types) {
        *अङ्कः_mime_types = 0;
    }

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }

    सचे (अङ्कः_mime_types) {
        *अङ्कः_mime_types = _this->अङ्कः_clipboard_mime_types;
    }
    पटिनिवत्त SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ध्रुव वर्ण *mime_type)
{
    पटिनिवत्त (SDL_strncmp(mime_type, "text", 4) == 0);
}

स्थिर ध्रुव वर्ण *ध्रुव *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types)
{
    सचे (_this->GetTextMimeTypes) {
        पटिनिवत्त _this->GetTextMimeTypes(_this, अङ्कः_mime_types);
    } अञ्ञथा {
        स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अङ्कः_mime_types = SDL_arraysize(text_mime_types);
        पटिनिवत्त text_mime_types;
    }
}

ध्रुव शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, ध्रुव वर्ण *mime_type, size_t *size)
{
    वर्ण *text = (वर्ण *)userdata;
    सचे (text) {
        *size = SDL_strlen(text);
    } अञ्ञथा {
        *size = 0;
    }
    पटिनिवत्त text;
}

bool SDL_SetClipboardText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    सचे (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);

        पटिनिवत्त SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अङ्कः_mime_types);
    }
    पटिनिवत्त SDL_ClearClipboardData();
}

वर्ण *SDL_GetClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;
    size_t length;
    वर्ण *text = रिक्त;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    अत्थाय (i = 0; i < अङ्कः_mime_types; ++i) {
        शून्य *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        सचे (clipdata) {
            text = (वर्ण *)clipdata;
            भङ्ग;
        }
    }

    सचे (!text) {
        text = SDL_strdup("");
    }
    पटिनिवत्त text;
}

bool SDL_HasClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    अत्थाय (i = 0; i < अङ्कः_mime_types; ++i) {
        सचे (SDL_HasClipboardData(text_mime_types[i])) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    सचे (!text) {
        text = "";
    }
    सचे (_this->SetPrimarySelectionText) {
        सचे (!_this->SetPrimarySelectionText(_this, text)) {
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    वर्ण **mime_types = SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, true);
    सचे (!mime_types) {
        पटिनिवत्त SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अङ्कः_clipboard_mime_types);
    पटिनिवत्त true;
}

वर्ण *SDL_GetPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त SDL_strdup("");
    }

    सचे (_this->GetPrimarySelectionText) {
        पटिनिवत्त _this->GetPrimarySelectionText(_this);
    } अञ्ञथा {
        ध्रुव वर्ण *text = _this->primary_selection_text;
        सचे (!text) {
            text = "";
        }
        पटिनिवत्त SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    सचे (_this->HasPrimarySelectionText) {
        पटिनिवत्त _this->HasPrimarySelectionText(_this);
    } अञ्ञथा {
        सचे (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            पटिनिवत्त true;
        } अञ्ञथा {
            पटिनिवत्त false;
        }
    }
}

