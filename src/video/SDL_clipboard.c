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
    အကယ်၍ (_this->clipboard_mime_types) {
        အတွက် (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    အကယ်၍ (!_this) {
        ပြန်ပေး;
    }

    အကယ်၍ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ပြန်ပေး;
    }

    အကယ်၍ (_this->clipboard_cleanup) {
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

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    အကယ်၍ (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (var_na **)SDL_malloc(num_mime_types * parimaa_na(var_na *));
        အကယ်၍ (_this->clipboard_mime_types) {
            အတွက် (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                အကယ်၍ (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        အကယ်၍ (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ပြန်ပေး false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    ပြန်ပေး true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const var_na *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    // Parameter validation
    အကယ်၍ (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        ပြန်ပေး SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    အကယ်၍ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    အကယ်၍ (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        ပြန်ပေး false;
    }

    အကယ်၍ (_this->SetClipboardData) {
        အကယ်၍ (!_this->SetClipboardData(_this)) {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက အကယ်၍ (_this->SetClipboardText) {
        var_na *text = NULL;
        size_t size;

        အတွက် (size_t i = 0; i < num_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];
            အကယ်၍ (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                အကယ်၍ (data) {
                    text = (var_na *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    အကယ်၍ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ပြန်ပေး false;
                    }
                    bha_nga;
                }
            }
        }
        အကယ်၍ (text) {
            SDL_free(text);
        } မဟုတ်ပါက {
            အကယ်၍ (!_this->SetClipboardText(_this, "")) {
                ပြန်ပေး false;
            }
        }
    }

    var_na **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    အကယ်၍ (!mime_types_copy) {
        ပြန်ပေး SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    ပြန်ပေး true;
}

bool SDL_ClearClipboardData(void)
{
    ပြန်ပေး SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    အကယ်၍ (_this->clipboard_callback) {
        အကယ်၍ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ပြန်ပေး NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        အကယ်၍ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + parimaa_na(Uint32));
            အကယ်၍ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, parimaa_na(Uint32));
            } မဟုတ်ပါက {
                *size = 0;
            }
        }
    }
    ပြန်ပေး data;
}

void *SDL_GetClipboardData(const var_na *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ပြန်ပေး NULL;
    }
    အကယ်၍ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    အကယ်၍ (_this->GetClipboardData) {
        ပြန်ပေး _this->GetClipboardData(_this, mime_type, size);
    } မဟုတ်ပါက အကယ်၍ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        var_na *text = _this->GetClipboardText(_this);
        အကယ်၍ (text) {
            အကယ်၍ (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } မဟုတ်ပါက {
                *size = SDL_strlen(text);
            }
        }
        ပြန်ပေး text;
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    size_t i;

    အတွက် (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        အကယ်၍ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ပြန်ပေး true;
        }
    }
    ပြန်ပေး false;
}

bool SDL_HasClipboardData(const var_na *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ပြန်ပေး SDL_InvalidParamError("mime_type");
    }

    အကယ်၍ (_this->HasClipboardData) {
        ပြန်ပေး _this->HasClipboardData(_this, mime_type);
    } မဟုတ်ပါက အကယ်၍ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ပြန်ပေး _this->HasClipboardText(_this);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_HasInternalClipboardData(_this, mime_type);
    }
}

var_na **SDL_CopyClipboardMimeTypes(const var_na *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = parimaa_na(var_na *);
    အတွက် (size_t i = 0; i < num_mime_types; i++) {
        allocSize += parimaa_na(var_na *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    var_na *ret;
    အကယ်၍ (temporary)
        ret = (var_na *)SDL_AllocateTemporaryMemory(allocSize);
    မဟုတ်ပါက
        ret = (var_na *)SDL_malloc(allocSize);
    အကယ်၍ (!ret) {
        ပြန်ပေး NULL;
    }

    var_na **result = (var_na **)ret;
    ret += parimaa_na(var_na *) * (num_mime_types + 1);

    အတွက် (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const var_na *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        var_na c;
        do {
            c = *ret++ = *mime_type++;
        } နေစဉ် (c != '\0');
    }
    result[num_mime_types] = NULL;

    ပြန်ပေး result;

}

var_na **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (num_mime_types) {
        *num_mime_types = 0;
    }

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }

    အကယ်၍ (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    ပြန်ပေး SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const var_na *mime_type)
{
    ပြန်ပေး (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const var_na *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    အကယ်၍ (_this->GetTextMimeTypes) {
        ပြန်ပေး _this->GetTextMimeTypes(_this, num_mime_types);
    } မဟုတ်ပါက {
        static const var_na *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        ပြန်ပေး text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const var_na *mime_type, size_t *size)
{
    var_na *text = (var_na *)userdata;
    အကယ်၍ (text) {
        *size = SDL_strlen(text);
    } မဟုတ်ပါက {
        *size = 0;
    }
    ပြန်ပေး text;
}

bool SDL_SetClipboardText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const var_na *const *text_mime_types;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    အကယ်၍ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        ပြန်ပေး SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    ပြန်ပေး SDL_ClearClipboardData();
}

var_na *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;
    size_t length;
    var_na *text = NULL;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    အတွက် (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        အကယ်၍ (clipdata) {
            text = (var_na *)clipdata;
            bha_nga;
        }
    }

    အကယ်၍ (!text) {
        text = SDL_strdup("");
    }
    ပြန်ပေး text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    အတွက် (i = 0; i < num_mime_types; ++i) {
        အကယ်၍ (SDL_HasClipboardData(text_mime_types[i])) {
            ပြန်ပေး true;
        }
    }
    ပြန်ပေး false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    အကယ်၍ (!text) {
        text = "";
    }
    အကယ်၍ (_this->SetPrimarySelectionText) {
        အကယ်၍ (!_this->SetPrimarySelectionText(_this, text)) {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    var_na **mime_types = SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    အကယ်၍ (!mime_types) {
        ပြန်ပေး SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    ပြန်ပေး true;
}

var_na *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး SDL_strdup("");
    }

    အကယ်၍ (_this->GetPrimarySelectionText) {
        ပြန်ပေး _this->GetPrimarySelectionText(_this);
    } မဟုတ်ပါက {
        const var_na *text = _this->primary_selection_text;
        အကယ်၍ (!text) {
            text = "";
        }
        ပြန်ပေး SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    အကယ်၍ (_this->HasPrimarySelectionText) {
        ပြန်ပေး _this->HasPrimarySelectionText(_this);
    } မဟုတ်ပါက {
        အကယ်၍ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ပြန်ပေး true;
        } မဟုတ်ပါက {
            ပြန်ပေး false;
        }
    }
}

