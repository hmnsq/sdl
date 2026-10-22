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
    如果 (_this->clipboard_mime_types) {
        为 (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    如果 (!_this) {
        返回;
    }

    如果 (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        返回;
    }

    如果 (_this->clipboard_cleanup) {
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

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    如果 (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (char **)SDL_malloc(num_mime_types * sizeof(char *));
        如果 (_this->clipboard_mime_types) {
            为 (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                如果 (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        如果 (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            返回 false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    返回 true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const char *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    // Parameter validation
    如果 (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        返回 SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    如果 (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    如果 (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        返回 false;
    }

    如果 (_this->SetClipboardData) {
        如果 (!_this->SetClipboardData(_this)) {
            返回 false;
        }
    } 否则 如果 (_this->SetClipboardText) {
        char *text = NULL;
        size_t size;

        为 (size_t i = 0; i < num_mime_types; ++i) {
            const char *mime_type = _this->clipboard_mime_types[i];
            如果 (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                如果 (data) {
                    text = (char *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    如果 (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        返回 false;
                    }
                    break;
                }
            }
        }
        如果 (text) {
            SDL_free(text);
        } 否则 {
            如果 (!_this->SetClipboardText(_this, "")) {
                返回 false;
            }
        }
    }

    char **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    如果 (!mime_types_copy) {
        返回 SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    返回 true;
}

bool SDL_ClearClipboardData(void)
{
    返回 SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type, size_t *size)
{
    void *data = NULL;

    如果 (_this->clipboard_callback) {
        如果 (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            返回 NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        如果 (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + sizeof(Uint32));
            如果 (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, sizeof(Uint32));
            } 否则 {
                *size = 0;
            }
        }
    }
    返回 data;
}

void *SDL_GetClipboardData(const char *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    如果 (!_this) {
        SDL_UninitializedVideo();
        返回 NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        返回 NULL;
    }
    如果 (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    如果 (_this->GetClipboardData) {
        返回 _this->GetClipboardData(_this, mime_type, size);
    } 否则 如果 (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        char *text = _this->GetClipboardText(_this);
        如果 (text) {
            如果 (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } 否则 {
                *size = SDL_strlen(text);
            }
        }
        返回 text;
    } 否则 {
        返回 SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const char *mime_type)
{
    size_t i;

    为 (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        如果 (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            返回 true;
        }
    }
    返回 false;
}

bool SDL_HasClipboardData(const char *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        返回 SDL_InvalidParamError("mime_type");
    }

    如果 (_this->HasClipboardData) {
        返回 _this->HasClipboardData(_this, mime_type);
    } 否则 如果 (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        返回 _this->HasClipboardText(_this);
    } 否则 {
        返回 SDL_HasInternalClipboardData(_this, mime_type);
    }
}

char **SDL_CopyClipboardMimeTypes(const char *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = sizeof(char *);
    为 (size_t i = 0; i < num_mime_types; i++) {
        allocSize += sizeof(char *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    char *ret;
    如果 (temporary)
        ret = (char *)SDL_AllocateTemporaryMemory(allocSize);
    否则
        ret = (char *)SDL_malloc(allocSize);
    如果 (!ret) {
        返回 NULL;
    }

    char **result = (char **)ret;
    ret += sizeof(char *) * (num_mime_types + 1);

    为 (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const char *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        char c;
        do {
            c = *ret++ = *mime_type++;
        } 当 (c != '\0');
    }
    result[num_mime_types] = NULL;

    返回 result;

}

char **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (num_mime_types) {
        *num_mime_types = 0;
    }

    如果 (!_this) {
        SDL_UninitializedVideo();
        返回 NULL;
    }

    如果 (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    返回 SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const char *mime_type)
{
    返回 (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const char *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    如果 (_this->GetTextMimeTypes) {
        返回 _this->GetTextMimeTypes(_this, num_mime_types);
    } 否则 {
        static const char *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        返回 text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const char *mime_type, size_t *size)
{
    char *text = (char *)userdata;
    如果 (text) {
        *size = SDL_strlen(text);
    } 否则 {
        *size = 0;
    }
    返回 text;
}

bool SDL_SetClipboardText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const char *const *text_mime_types;

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    如果 (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        返回 SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    返回 SDL_ClearClipboardData();
}

char *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;
    size_t length;
    char *text = NULL;

    如果 (!_this) {
        SDL_UninitializedVideo();
        返回 SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    为 (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        如果 (clipdata) {
            text = (char *)clipdata;
            break;
        }
    }

    如果 (!text) {
        text = SDL_strdup("");
    }
    返回 text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const char *const *text_mime_types;

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    为 (i = 0; i < num_mime_types; ++i) {
        如果 (SDL_HasClipboardData(text_mime_types[i])) {
            返回 true;
        }
    }
    返回 false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const char *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    如果 (!text) {
        text = "";
    }
    如果 (_this->SetPrimarySelectionText) {
        如果 (!_this->SetPrimarySelectionText(_this, text)) {
            返回 false;
        }
    } 否则 {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    char **mime_types = SDL_CopyClipboardMimeTypes((const char **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    如果 (!mime_types) {
        返回 SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    返回 true;
}

char *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (!_this) {
        SDL_UninitializedVideo();
        返回 SDL_strdup("");
    }

    如果 (_this->GetPrimarySelectionText) {
        返回 _this->GetPrimarySelectionText(_this);
    } 否则 {
        const char *text = _this->primary_selection_text;
        如果 (!text) {
            text = "";
        }
        返回 SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    如果 (!_this) {
        返回 SDL_UninitializedVideo();
    }

    如果 (_this->HasPrimarySelectionText) {
        返回 _this->HasPrimarySelectionText(_this);
    } 否则 {
        如果 (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            返回 true;
        } 否则 {
            返回 false;
        }
    }
}

