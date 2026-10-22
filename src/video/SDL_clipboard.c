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
    ако (_this->clipboard_mime_types) {
        за (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    ако (!_this) {
        върни;
    }

    ако (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        върни;
    }

    ако (_this->clipboard_cleanup) {
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

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ако (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (char **)SDL_malloc(num_mime_types * sizeof(char *));
        ако (_this->clipboard_mime_types) {
            за (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ако (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        ако (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            върни false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    върни true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const char *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    // Parameter validation
    ако (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        върни SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    ако (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ако (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        върни false;
    }

    ако (_this->SetClipboardData) {
        ако (!_this->SetClipboardData(_this)) {
            върни false;
        }
    } иначе ако (_this->SetClipboardText) {
        char *text = NULL;
        size_t size;

        за (size_t i = 0; i < num_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];
            ако (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                ако (data) {
                    text = (char *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    ако (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        върни false;
                    }
                    break;
                }
            }
        }
        ако (text) {
            SDL_free(text);
        } иначе {
            ако (!_this->SetClipboardText(_this, "")) {
                върни false;
            }
        }
    }

    char **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    ако (!mime_types_copy) {
        върни SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    върни true;
}

bool SDL_ClearClipboardData(void)
{
    върни SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    ако (_this->clipboard_callback) {
        ако (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            върни NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        ако (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + sizeof(Uint32));
            ако (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, sizeof(Uint32));
            } иначе {
                *size = 0;
            }
        }
    }
    върни data;
}

void *SDL_GetClipboardData(const char *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    ако (!_this) {
        SDL_UninitializedVideo();
        върни NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        върни NULL;
    }
    ако (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    ако (_this->GetClipboardData) {
        върни _this->GetClipboardData(_this, mime_type, size);
    } иначе ако (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        char *text = _this->GetClipboardText(_this);
        ако (text) {
            ако (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } иначе {
                *size = SDL_strlen(text);
            }
        }
        върни text;
    } иначе {
        върни SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    size_t i;

    за (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        ако (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            върни true;
        }
    }
    върни false;
}

bool SDL_HasClipboardData(const char *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        върни SDL_InvalidParamError("mime_type");
    }

    ако (_this->HasClipboardData) {
        върни _this->HasClipboardData(_this, mime_type);
    } иначе ако (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        върни _this->HasClipboardText(_this);
    } иначе {
        върни SDL_HasInternalClipboardData(_this, mime_type);
    }
}

char **SDL_CopyClipboardMimeTypes(const char *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = sizeof(char *);
    за (size_t i = 0; i < num_mime_types; i++) {
        allocSize += sizeof(char *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    char *ret;
    ако (temporary)
        ret = (char *)SDL_AllocateTemporaryMemory(allocSize);
    иначе
        ret = (char *)SDL_malloc(allocSize);
    ако (!ret) {
        върни NULL;
    }

    char **result = (char **)ret;
    ret += sizeof(char *) * (num_mime_types + 1);

    за (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const char *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        char c;
        do {
            c = *ret++ = *mime_type++;
        } докато (c != '\0');
    }
    result[num_mime_types] = NULL;

    върни result;

}

char **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (num_mime_types) {
        *num_mime_types = 0;
    }

    ако (!_this) {
        SDL_UninitializedVideo();
        върни NULL;
    }

    ако (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    върни SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const char *mime_type)
{
    върни (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const char *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    ако (_this->GetTextMimeTypes) {
        върни _this->GetTextMimeTypes(_this, num_mime_types);
    } иначе {
        static const char *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        върни text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const char *mime_type, size_t *size)
{
    char *text = (char *)userdata;
    ако (text) {
        *size = SDL_strlen(text);
    } иначе {
        *size = 0;
    }
    върни text;
}

bool SDL_SetClipboardText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const char *const *text_mime_types;

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    ако (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        върни SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    върни SDL_ClearClipboardData();
}

char *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;
    size_t length;
    char *text = NULL;

    ако (!_this) {
        SDL_UninitializedVideo();
        върни SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    за (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        ако (clipdata) {
            text = (char *)clipdata;
            break;
        }
    }

    ако (!text) {
        text = SDL_strdup("");
    }
    върни text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    за (i = 0; i < num_mime_types; ++i) {
        ако (SDL_HasClipboardData(text_mime_types[i])) {
            върни true;
        }
    }
    върни false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    ако (!text) {
        text = "";
    }
    ако (_this->SetPrimarySelectionText) {
        ако (!_this->SetPrimarySelectionText(_this, text)) {
            върни false;
        }
    } иначе {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    char **mime_types = SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    ако (!mime_types) {
        върни SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    върни true;
}

char *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (!_this) {
        SDL_UninitializedVideo();
        върни SDL_strdup("");
    }

    ако (_this->GetPrimarySelectionText) {
        върни _this->GetPrimarySelectionText(_this);
    } иначе {
        const char *text = _this->primary_selection_text;
        ако (!text) {
            text = "";
        }
        върни SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ако (!_this) {
        върни SDL_UninitializedVideo();
    }

    ако (_this->HasPrimarySelectionText) {
        върни _this->HasPrimarySelectionText(_this);
    } иначе {
        ако (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            върни true;
        } иначе {
            върни false;
        }
    }
}

