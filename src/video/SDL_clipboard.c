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
#include "SDL_internal.h"

#include "SDL_clipboard_c.h"
#include "SDL_sysvideo.h"
#include "../events/SDL_events_c.h"
#include "../events/SDL_clipboardevents_c.h"

void SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    nếu (_this->clipboard_mime_types) {
        cho (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = NULL;
        _this->num_clipboard_mime_types = 0;
    }
}


void SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về;
    }

    nếu (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        trả_về;
    }

    nếu (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = NULL;
    _this->clipboard_cleanup = NULL;
    _this->clipboard_userdata = NULL;
}

bool SDL_SaveClipboardMimeTypes(const char *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    nếu (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (char **)SDL_malloc(num_mime_types * sizeof(char *));
        nếu (_this->clipboard_mime_types) {
            cho (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                nếu (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        nếu (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            trả_về false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    trả_về true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const char *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    // Parameter validation
    nếu (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        trả_về SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    nếu (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    nếu (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        trả_về false;
    }

    nếu (_this->SetClipboardData) {
        nếu (!_this->SetClipboardData(_this)) {
            trả_về false;
        }
    } không_thì nếu (_this->SetClipboardText) {
        char *text = NULL;
        size_t size;

        cho (size_t i = 0; i < num_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];
            nếu (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                nếu (data) {
                    text = (char *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    nếu (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        trả_về false;
                    }
                    break;
                }
            }
        }
        nếu (text) {
            SDL_free(text);
        } không_thì {
            nếu (!_this->SetClipboardText(_this, "")) {
                trả_về false;
            }
        }
    }

    char **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    nếu (!mime_types_copy) {
        trả_về SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    trả_về true;
}

bool SDL_ClearClipboardData(void)
{
    trả_về SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    nếu (_this->clipboard_callback) {
        nếu (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            trả_về NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        nếu (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + sizeof(Uint32));
            nếu (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, sizeof(Uint32));
            } không_thì {
                *size = 0;
            }
        }
    }
    trả_về data;
}

void *SDL_GetClipboardData(const char *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    nếu (!_this) {
        SDL_UninitializedVideo();
        trả_về NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        trả_về NULL;
    }
    nếu (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    nếu (_this->GetClipboardData) {
        trả_về _this->GetClipboardData(_this, mime_type, size);
    } không_thì nếu (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        char *text = _this->GetClipboardText(_this);
        nếu (text) {
            nếu (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } không_thì {
                *size = SDL_strlen(text);
            }
        }
        trả_về text;
    } không_thì {
        trả_về SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    size_t i;

    cho (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        nếu (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            trả_về true;
        }
    }
    trả_về false;
}

bool SDL_HasClipboardData(const char *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        trả_về SDL_InvalidParamError("mime_type");
    }

    nếu (_this->HasClipboardData) {
        trả_về _this->HasClipboardData(_this, mime_type);
    } không_thì nếu (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        trả_về _this->HasClipboardText(_this);
    } không_thì {
        trả_về SDL_HasInternalClipboardData(_this, mime_type);
    }
}

char **SDL_CopyClipboardMimeTypes(const char *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = sizeof(char *);
    cho (size_t i = 0; i < num_mime_types; i++) {
        allocSize += sizeof(char *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    char *ret;
    nếu (temporary)
        ret = (char *)SDL_AllocateTemporaryMemory(allocSize);
    không_thì
        ret = (char *)SDL_malloc(allocSize);
    nếu (!ret) {
        trả_về NULL;
    }

    char **result = (char **)ret;
    ret += sizeof(char *) * (num_mime_types + 1);

    cho (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const char *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        char c;
        do {
            c = *ret++ = *mime_type++;
        } trong_khi (c != '\0');
    }
    result[num_mime_types] = NULL;

    trả_về result;

}

char **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (num_mime_types) {
        *num_mime_types = 0;
    }

    nếu (!_this) {
        SDL_UninitializedVideo();
        trả_về NULL;
    }

    nếu (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    trả_về SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const char *mime_type)
{
    trả_về (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const char *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    nếu (_this->GetTextMimeTypes) {
        trả_về _this->GetTextMimeTypes(_this, num_mime_types);
    } không_thì {
        static const char *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        trả_về text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const char *mime_type, size_t *size)
{
    char *text = (char *)userdata;
    nếu (text) {
        *size = SDL_strlen(text);
    } không_thì {
        *size = 0;
    }
    trả_về text;
}

bool SDL_SetClipboardText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const char *const *text_mime_types;

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    nếu (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        trả_về SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    trả_về SDL_ClearClipboardData();
}

char *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;
    size_t length;
    char *text = NULL;

    nếu (!_this) {
        SDL_UninitializedVideo();
        trả_về SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    cho (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        nếu (clipdata) {
            text = (char *)clipdata;
            break;
        }
    }

    nếu (!text) {
        text = SDL_strdup("");
    }
    trả_về text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    cho (i = 0; i < num_mime_types; ++i) {
        nếu (SDL_HasClipboardData(text_mime_types[i])) {
            trả_về true;
        }
    }
    trả_về false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    nếu (!text) {
        text = "";
    }
    nếu (_this->SetPrimarySelectionText) {
        nếu (!_this->SetPrimarySelectionText(_this, text)) {
            trả_về false;
        }
    } không_thì {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    char **mime_types = SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    nếu (!mime_types) {
        trả_về SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    trả_về true;
}

char *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        SDL_UninitializedVideo();
        trả_về SDL_strdup("");
    }

    nếu (_this->GetPrimarySelectionText) {
        trả_về _this->GetPrimarySelectionText(_this);
    } không_thì {
        const char *text = _this->primary_selection_text;
        nếu (!text) {
            text = "";
        }
        trả_về SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    nếu (!_this) {
        trả_về SDL_UninitializedVideo();
    }

    nếu (_this->HasPrimarySelectionText) {
        trả_về _this->HasPrimarySelectionText(_this);
    } không_thì {
        nếu (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            trả_về true;
        } không_thì {
            trả_về false;
        }
    }
}

