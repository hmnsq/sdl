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
    ຖ້າ (_this->clipboard_mime_types) {
        ສຳລັບ (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    ຖ້າ (!_this) {
        ສົ່ງຄືນ;
    }

    ຖ້າ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ສົ່ງຄືນ;
    }

    ຖ້າ (_this->clipboard_cleanup) {
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

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ຖ້າ (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (var_na **)SDL_malloc(num_mime_types * parimaa_na(var_na *));
        ຖ້າ (_this->clipboard_mime_types) {
            ສຳລັບ (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ຖ້າ (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        ຖ້າ (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ສົ່ງຄືນ false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    ສົ່ງຄືນ true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, void *userdata, const var_na *const *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    // Parameter validation
    ຖ້າ (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        ສົ່ງຄືນ SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    ຖ້າ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ຖ້າ (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        ສົ່ງຄືນ false;
    }

    ຖ້າ (_this->SetClipboardData) {
        ຖ້າ (!_this->SetClipboardData(_this)) {
            ສົ່ງຄືນ false;
        }
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (_this->SetClipboardText) {
        var_na *text = NULL;
        size_t size;

        ສຳລັບ (size_t i = 0; i < num_mime_types; ++i) {
            const var_na *mime_type = _this->clipboard_mime_types[i];
            ຖ້າ (SDL_IsTextMimeType(mime_type)) {
                const void *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                ຖ້າ (data) {
                    text = (var_na *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    ຖ້າ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ສົ່ງຄືນ false;
                    }
                    bha_nga;
                }
            }
        }
        ຖ້າ (text) {
            SDL_free(text);
        } ບໍ່ດັ່ງນັ້ນ {
            ຖ້າ (!_this->SetClipboardText(_this, "")) {
                ສົ່ງຄືນ false;
            }
        }
    }

    var_na **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    ຖ້າ (!mime_types_copy) {
        ສົ່ງຄືນ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    ສົ່ງຄືນ true;
}

bool SDL_ClearClipboardData(void)
{
    ສົ່ງຄືນ SDL_SetClipboardData(NULL, NULL, NULL, NULL, 0);
}

void *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type, size_t *size)
{
    void *data = NULL;

    ຖ້າ (_this->clipboard_callback) {
        ຖ້າ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ສົ່ງຄືນ NULL;
        }

        const void *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        ຖ້າ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + parimaa_na(Uint32));
            ຖ້າ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, parimaa_na(Uint32));
            } ບໍ່ດັ່ງນັ້ນ {
                *size = 0;
            }
        }
    }
    ສົ່ງຄືນ data;
}

void *SDL_GetClipboardData(const var_na *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    ຖ້າ (!_this) {
        SDL_UninitializedVideo();
        ສົ່ງຄືນ NULL;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ສົ່ງຄືນ NULL;
    }
    ຖ້າ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    ຖ້າ (_this->GetClipboardData) {
        ສົ່ງຄືນ _this->GetClipboardData(_this, mime_type, size);
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        var_na *text = _this->GetClipboardText(_this);
        ຖ້າ (text) {
            ຖ້າ (*text == '\0') {
                SDL_free(text);
                text = NULL;
            } ບໍ່ດັ່ງນັ້ນ {
                *size = SDL_strlen(text);
            }
        }
        ສົ່ງຄືນ text;
    } ບໍ່ດັ່ງນັ້ນ {
        ສົ່ງຄືນ SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, const var_na *mime_type)
{
    size_t i;

    ສຳລັບ (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        ຖ້າ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ສົ່ງຄືນ true;
        }
    }
    ສົ່ງຄືນ false;
}

bool SDL_HasClipboardData(const var_na *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ສົ່ງຄືນ SDL_InvalidParamError("mime_type");
    }

    ຖ້າ (_this->HasClipboardData) {
        ສົ່ງຄືນ _this->HasClipboardData(_this, mime_type);
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ສົ່ງຄືນ _this->HasClipboardText(_this);
    } ບໍ່ດັ່ງນັ້ນ {
        ສົ່ງຄືນ SDL_HasInternalClipboardData(_this, mime_type);
    }
}

var_na **SDL_CopyClipboardMimeTypes(const var_na *const *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = parimaa_na(var_na *);
    ສຳລັບ (size_t i = 0; i < num_mime_types; i++) {
        allocSize += parimaa_na(var_na *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    var_na *ret;
    ຖ້າ (temporary)
        ret = (var_na *)SDL_AllocateTemporaryMemory(allocSize);
    ບໍ່ດັ່ງນັ້ນ
        ret = (var_na *)SDL_malloc(allocSize);
    ຖ້າ (!ret) {
        ສົ່ງຄືນ NULL;
    }

    var_na **result = (var_na **)ret;
    ret += parimaa_na(var_na *) * (num_mime_types + 1);

    ສຳລັບ (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        const var_na *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        var_na c;
        do {
            c = *ret++ = *mime_type++;
        } ໃນຂະນະທີ່ (c != '\0');
    }
    result[num_mime_types] = NULL;

    ສົ່ງຄືນ result;

}

var_na **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (num_mime_types) {
        *num_mime_types = 0;
    }

    ຖ້າ (!_this) {
        SDL_UninitializedVideo();
        ສົ່ງຄືນ NULL;
    }

    ຖ້າ (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    ສົ່ງຄືນ SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(const var_na *mime_type)
{
    ສົ່ງຄືນ (SDL_strncmp(mime_type, "text", 4) == 0);
}

static const var_na *const *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    ຖ້າ (_this->GetTextMimeTypes) {
        ສົ່ງຄືນ _this->GetTextMimeTypes(_this, num_mime_types);
    } ບໍ່ດັ່ງນັ້ນ {
        static const var_na *const text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        ສົ່ງຄືນ text_mime_types;
    }
}

const void * SDLCALL SDL_ClipboardTextCallback(void *userdata, const var_na *mime_type, size_t *size)
{
    var_na *text = (var_na *)userdata;
    ຖ້າ (text) {
        *size = SDL_strlen(text);
    } ບໍ່ດັ່ງນັ້ນ {
        *size = 0;
    }
    ສົ່ງຄືນ text;
}

bool SDL_SetClipboardText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    const var_na *const *text_mime_types;

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    ຖ້າ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        ສົ່ງຄືນ SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    ສົ່ງຄືນ SDL_ClearClipboardData();
}

var_na *SDL_GetClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;
    size_t length;
    var_na *text = NULL;

    ຖ້າ (!_this) {
        SDL_UninitializedVideo();
        ສົ່ງຄືນ SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    ສຳລັບ (i = 0; i < num_mime_types; ++i) {
        void *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        ຖ້າ (clipdata) {
            text = (var_na *)clipdata;
            bha_nga;
        }
    }

    ຖ້າ (!text) {
        text = SDL_strdup("");
    }
    ສົ່ງຄືນ text;
}

bool SDL_HasClipboardText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    const var_na *const *text_mime_types;

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    ສຳລັບ (i = 0; i < num_mime_types; ++i) {
        ຖ້າ (SDL_HasClipboardData(text_mime_types[i])) {
            ສົ່ງຄືນ true;
        }
    }
    ສົ່ງຄືນ false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(const var_na *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    ຖ້າ (!text) {
        text = "";
    }
    ຖ້າ (_this->SetPrimarySelectionText) {
        ຖ້າ (!_this->SetPrimarySelectionText(_this, text)) {
            ສົ່ງຄືນ false;
        }
    } ບໍ່ດັ່ງນັ້ນ {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    var_na **mime_types = SDL_CopyClipboardMimeTypes((const var_na **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    ຖ້າ (!mime_types) {
        ສົ່ງຄືນ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    ສົ່ງຄືນ true;
}

var_na *SDL_GetPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (!_this) {
        SDL_UninitializedVideo();
        ສົ່ງຄືນ SDL_strdup("");
    }

    ຖ້າ (_this->GetPrimarySelectionText) {
        ສົ່ງຄືນ _this->GetPrimarySelectionText(_this);
    } ບໍ່ດັ່ງນັ້ນ {
        const var_na *text = _this->primary_selection_text;
        ຖ້າ (!text) {
            text = "";
        }
        ສົ່ງຄືນ SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(void)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ຖ້າ (!_this) {
        ສົ່ງຄືນ SDL_UninitializedVideo();
    }

    ຖ້າ (_this->HasPrimarySelectionText) {
        ສົ່ງຄືນ _this->HasPrimarySelectionText(_this);
    } ບໍ່ດັ່ງນັ້ນ {
        ຖ້າ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ສົ່ງຄືນ true;
        } ບໍ່ດັ່ງນັ້ນ {
            ສົ່ງຄືນ false;
        }
    }
}

