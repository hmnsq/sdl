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
    གལ་ཏེ (_this->clipboard_mime_types) {
        ཆེད་དུ (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    གལ་ཏེ (!_this) {
        ཕྱིར;
    }

    གལ་ཏེ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ཕྱིར;
    }

    གལ་ཏེ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = NULL;
    _this->clipboard_cleanup = NULL;
    _this->clipboard_userdata = NULL;
}

bool SDL_SaveClipboardMimeTypes(const var_na *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    གལ་ཏེ (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (var_na **)SDL_malloc(num_mime_types * parimaa_na(var_na *));
        གལ་ཏེ (_this->clipboard_mime_types) {
            ཆེད་དུ (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                གལ་ཏེ (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        གལ་ཏེ (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ཕྱིར false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    ཕྱིར true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const var_na *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    // Parameter validation
    གལ་ཏེ (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        ཕྱིར SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    གལ་ཏེ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    གལ་ཏེ (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        ཕྱིར false;
    }

    གལ་ཏེ (_this->SetClipboardData) {
        གལ་ཏེ (!_this->SetClipboardData(_this)) {
            ཕྱིར false;
        }
    } དེ་མིན གལ་ཏེ (_this->SetClipboardText) {
        var_na *text = NULL;
        size_t size;

        ཆེད་དུ (size_t i = 0; i < num_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];
            གལ་ཏེ (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                གལ་ཏེ (data) {
                    text = (var_na *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    གལ་ཏེ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ཕྱིར false;
                    }
                    bha_nga;
                }
            }
        }
        གལ་ཏེ (text) {
            SDL_free(text);
        } དེ་མིན {
            གལ་ཏེ (!_this->SetClipboardText(_this, "")) {
                ཕྱིར false;
            }
        }
    }

    var_na **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    གལ་ཏེ (!mime_types_copy) {
        ཕྱིར SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    ཕྱིར true;
}

bool SDL_ClearClipboardData(void)
{
    ཕྱིར SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    གལ་ཏེ (_this->clipboard_callback) {
        གལ་ཏེ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ཕྱིར NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        གལ་ཏེ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + parimaa_na(Uint32));
            གལ་ཏེ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, parimaa_na(Uint32));
            } དེ་མིན {
                *size = 0;
            }
        }
    }
    ཕྱིར data;
}

void *SDL_GetClipboardData(const var_na *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    གལ་ཏེ (!_this) {
        SDL_UninitializedVideo();
        ཕྱིར NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ཕྱིར NULL;
    }
    གལ་ཏེ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    གལ་ཏེ (_this->GetClipboardData) {
        ཕྱིར _this->GetClipboardData(_this, mime_type, size);
    } དེ་མིན གལ་ཏེ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        var_na *text = _this->GetClipboardText(_this);
        གལ་ཏེ (text) {
            གལ་ཏེ (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } དེ་མིན {
                *size = SDL_strlen(text);
            }
        }
        ཕྱིར text;
    } དེ་མིན {
        ཕྱིར SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    size_t i;

    ཆེད་དུ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        གལ་ཏེ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ཕྱིར true;
        }
    }
    ཕྱིར false;
}

bool SDL_HasClipboardData(const var_na *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ཕྱིར SDL_InvalidParamError("mime_type");
    }

    གལ་ཏེ (_this->HasClipboardData) {
        ཕྱིར _this->HasClipboardData(_this, mime_type);
    } དེ་མིན གལ་ཏེ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ཕྱིར _this->HasClipboardText(_this);
    } དེ་མིན {
        ཕྱིར SDL_HasInternalClipboardData(_this, mime_type);
    }
}

var_na **SDL_CopyClipboardMimeTypes(const var_na *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = parimaa_na(var_na *);
    ཆེད་དུ (size_t i = 0; i < num_mime_types; i++) {
        allocSize += parimaa_na(var_na *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    var_na *ret;
    གལ་ཏེ (temporary)
        ret = (var_na *)SDL_AllocateTemporaryMemory(allocSize);
    དེ་མིན
        ret = (var_na *)SDL_malloc(allocSize);
    གལ་ཏེ (!ret) {
        ཕྱིར NULL;
    }

    var_na **result = (var_na **)ret;
    ret += parimaa_na(var_na *) * (num_mime_types + 1);

    ཆེད་དུ (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const var_na *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        var_na c;
        do {
            c = *ret++ = *mime_type++;
        } སྐབས (c != '\0');
    }
    result[num_mime_types] = NULL;

    ཕྱིར result;

}

var_na **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (num_mime_types) {
        *num_mime_types = 0;
    }

    གལ་ཏེ (!_this) {
        SDL_UninitializedVideo();
        ཕྱིར NULL;
    }

    གལ་ཏེ (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    ཕྱིར SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const var_na *mime_type)
{
    ཕྱིར (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const var_na *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    གལ་ཏེ (_this->GetTextMimeTypes) {
        ཕྱིར _this->GetTextMimeTypes(_this, num_mime_types);
    } དེ་མིན {
        static const var_na *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        ཕྱིར text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const var_na *mime_type, size_t *size)
{
    var_na *text = (var_na *)userdata;
    གལ་ཏེ (text) {
        *size = SDL_strlen(text);
    } དེ་མིན {
        *size = 0;
    }
    ཕྱིར text;
}

bool SDL_SetClipboardText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const var_na *const *text_mime_types;

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    གལ་ཏེ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        ཕྱིར SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    ཕྱིར SDL_ClearClipboardData();
}

var_na *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;
    size_t length;
    var_na *text = NULL;

    གལ་ཏེ (!_this) {
        SDL_UninitializedVideo();
        ཕྱིར SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    ཆེད་དུ (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        གལ་ཏེ (clipdata) {
            text = (var_na *)clipdata;
            bha_nga;
        }
    }

    གལ་ཏེ (!text) {
        text = SDL_strdup("");
    }
    ཕྱིར text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    ཆེད་དུ (i = 0; i < num_mime_types; ++i) {
        གལ་ཏེ (SDL_HasClipboardData(text_mime_types[i])) {
            ཕྱིར true;
        }
    }
    ཕྱིར false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    གལ་ཏེ (!text) {
        text = "";
    }
    གལ་ཏེ (_this->SetPrimarySelectionText) {
        གལ་ཏེ (!_this->SetPrimarySelectionText(_this, text)) {
            ཕྱིར false;
        }
    } དེ་མིན {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    var_na **mime_types = SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    གལ་ཏེ (!mime_types) {
        ཕྱིར SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    ཕྱིར true;
}

var_na *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        SDL_UninitializedVideo();
        ཕྱིར SDL_strdup("");
    }

    གལ་ཏེ (_this->GetPrimarySelectionText) {
        ཕྱིར _this->GetPrimarySelectionText(_this);
    } དེ་མིན {
        const var_na *text = _this->primary_selection_text;
        གལ་ཏེ (!text) {
            text = "";
        }
        ཕྱིར SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    གལ་ཏེ (!_this) {
        ཕྱིར SDL_UninitializedVideo();
    }

    གལ་ཏེ (_this->HasPrimarySelectionText) {
        ཕྱིར _this->HasPrimarySelectionText(_this);
    } དེ་མིན {
        གལ་ཏེ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ཕྱིར true;
        } དེ་མིན {
            ཕྱིར false;
        }
    }
}

