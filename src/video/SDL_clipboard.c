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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../events/SDL_clipboardevents_c.h"

ಶೂನ್ಯ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    ಯದಿ (_this->clipboard_mime_types) {
        ಪ್ರತಿ (size_t i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ರಿಕ್ತ;
        _this->ಅಂಕೆ_clipboard_mime_types = 0;
    }
}


ಶೂನ್ಯ SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ರಿಕ್ತ;
    _this->clipboard_cleanup = ರಿಕ್ತ;
    _this->clipboard_userdata = ರಿಕ್ತ;
}

bool SDL_SaveClipboardMimeTypes(ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ಯದಿ (mime_types && ಅಂಕೆ_mime_types > 0) {
        size_t ಅಂಕೆ_allocated = 0;

        _this->clipboard_mime_types = (ವರ್ಣ **)SDL_malloc(ಅಂಕೆ_mime_types * ಪರಿಮಾಣ(ವರ್ಣ *));
        ಯದಿ (_this->clipboard_mime_types) {
            ಪ್ರತಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ಯದಿ (_this->clipboard_mime_types[i]) {
                    ++ಅಂಕೆ_allocated;
                }
            }
        }
        ಯದಿ (ಅಂಕೆ_allocated < ಅಂಕೆ_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ಪ್ರತ್ಯಾಗಮ false;
        }
        _this->ಅಂಕೆ_clipboard_mime_types = ಅಂಕೆ_mime_types;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    // Parameter validation
    ಯದಿ (!((callback && mime_types && ಅಂಕೆ_mime_types > 0) ||
          (!callback && !mime_types && ಅಂಕೆ_mime_types == 0))) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    ಯದಿ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ಯದಿ (!SDL_SaveClipboardMimeTypes(mime_types, ಅಂಕೆ_mime_types)) {
        SDL_ClearClipboardData();
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (_this->SetClipboardData) {
        ಯದಿ (!_this->SetClipboardData(_this)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ ಯದಿ (_this->SetClipboardText) {
        ವರ್ಣ *text = ರಿಕ್ತ;
        size_t size;

        ಪ್ರತಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; ++i) {
            ಧ್ರುವ ವರ್ಣ *mime_type = _this->clipboard_mime_types[i];
            ಯದಿ (SDL_IsTextMimeType(mime_type)) {
                ಧ್ರುವ ಶೂನ್ಯ *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                ಯದಿ (data) {
                    text = (ವರ್ಣ *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    ಯದಿ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ಪ್ರತ್ಯಾಗಮ false;
                    }
                    ಭಙ್ಗ;
                }
            }
        }
        ಯದಿ (text) {
            SDL_free(text);
        } ಅನ್ಯಥಾ {
            ಯದಿ (!_this->SetClipboardText(_this, "")) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
    }

    ವರ್ಣ **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, ಅಂಕೆ_mime_types, true);
    ಯದಿ (!mime_types_copy) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, ಅಂಕೆ_mime_types);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ClearClipboardData(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ SDL_SetClipboardData(ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, 0);
}

ಶೂನ್ಯ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size)
{
    ಶೂನ್ಯ *data = ರಿಕ್ತ;

    ಯದಿ (_this->clipboard_callback) {
        ಯದಿ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        ಧ್ರುವ ಶೂನ್ಯ *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        ಯದಿ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + ಪರಿಮಾಣ(Uint32));
            ಯದಿ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, ಪರಿಮಾಣ(Uint32));
            } ಅನ್ಯಥಾ {
                *size = 0;
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ data;
}

ಶೂನ್ಯ *SDL_GetClipboardData(ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    ಯದಿ (_this->GetClipboardData) {
        ಪ್ರತ್ಯಾಗಮ _this->GetClipboardData(_this, mime_type, size);
    } ಅನ್ಯಥಾ ಯದಿ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        ವರ್ಣ *text = _this->GetClipboardText(_this);
        ಯದಿ (text) {
            ಯದಿ (*text == '\0') {
                SDL_free(text);
                text = ರಿಕ್ತ;
            } ಅನ್ಯಥಾ {
                *size = SDL_strlen(text);
            }
        }
        ಪ್ರತ್ಯಾಗಮ text;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    size_t i;

    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
        ಯದಿ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool SDL_HasClipboardData(ಧ್ರುವ ವರ್ಣ *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("mime_type");
    }

    ಯದಿ (_this->HasClipboardData) {
        ಪ್ರತ್ಯಾಗಮ _this->HasClipboardData(_this, mime_type);
    } ಅನ್ಯಥಾ ಯದಿ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ಪ್ರತ್ಯಾಗಮ _this->HasClipboardText(_this);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_HasInternalClipboardData(_this, mime_type);
    }
}

ವರ್ಣ **SDL_CopyClipboardMimeTypes(ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *clipboard_mime_types, size_t ಅಂಕೆ_mime_types, bool temporary)
{
    size_t allocSize = ಪರಿಮಾಣ(ವರ್ಣ *);
    ಪ್ರತಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; i++) {
        allocSize += ಪರಿಮಾಣ(ವರ್ಣ *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    ವರ್ಣ *ret;
    ಯದಿ (temporary)
        ret = (ವರ್ಣ *)SDL_AllocateTemporaryMemory(allocSize);
    ಅನ್ಯಥಾ
        ret = (ವರ್ಣ *)SDL_malloc(allocSize);
    ಯದಿ (!ret) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ವರ್ಣ **result = (ವರ್ಣ **)ret;
    ret += ಪರಿಮಾಣ(ವರ್ಣ *) * (ಅಂಕೆ_mime_types + 1);

    ಪ್ರತಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; i++) {
        result[i] = ret;

        ಧ್ರುವ ವರ್ಣ *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        ವರ್ಣ c;
        ಕುರು {
            c = *ret++ = *mime_type++;
        } ಯಾವತ್ (c != '\0');
    }
    result[ಅಂಕೆ_mime_types] = ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ result;

}

ವರ್ಣ **SDL_GetClipboardMimeTypes(size_t *ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (ಅಂಕೆ_mime_types) {
        *ಅಂಕೆ_mime_types = 0;
    }

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (ಅಂಕೆ_mime_types) {
        *ಅಂಕೆ_mime_types = _this->ಅಂಕೆ_clipboard_mime_types;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_CopyClipboardMimeTypes((ಧ್ರುವ ವರ್ಣ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_strncmp(mime_type, "text", 4) == 0);
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    ಯದಿ (_this->GetTextMimeTypes) {
        ಪ್ರತ್ಯಾಗಮ _this->GetTextMimeTypes(_this, ಅಂಕೆ_mime_types);
    } ಅನ್ಯಥಾ {
        ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *ಅಂಕೆ_mime_types = SDL_arraysize(text_mime_types);
        ಪ್ರತ್ಯಾಗಮ text_mime_types;
    }
}

ಧ್ರುವ ಶೂನ್ಯ * SDLCALL SDL_ClipboardTextCallback(ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size)
{
    ವರ್ಣ *text = (ವರ್ಣ *)userdata;
    ಯದಿ (text) {
        *size = SDL_strlen(text);
    } ಅನ್ಯಥಾ {
        *size = 0;
    }
    ಪ್ರತ್ಯಾಗಮ text;
}

bool SDL_SetClipboardText(ಧ್ರುವ ವರ್ಣ *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ಅಂಕೆ_mime_types;
    ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *text_mime_types;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    ಯದಿ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &ಅಂಕೆ_mime_types);

        ಪ್ರತ್ಯಾಗಮ SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, ಅಂಕೆ_mime_types);
    }
    ಪ್ರತ್ಯಾಗಮ SDL_ClearClipboardData();
}

ವರ್ಣ *SDL_GetClipboardText(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ಅಂಕೆ_mime_types;
    ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *text_mime_types;
    size_t length;
    ವರ್ಣ *text = ರಿಕ್ತ;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &ಅಂಕೆ_mime_types);
    ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_mime_types; ++i) {
        ಶೂನ್ಯ *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        ಯದಿ (clipdata) {
            text = (ವರ್ಣ *)clipdata;
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (!text) {
        text = SDL_strdup("");
    }
    ಪ್ರತ್ಯಾಗಮ text;
}

bool SDL_HasClipboardText(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ಅಂಕೆ_mime_types;
    ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *text_mime_types;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &ಅಂಕೆ_mime_types);
    ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_mime_types; ++i) {
        ಯದಿ (SDL_HasClipboardData(text_mime_types[i])) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ಧ್ರುವ ವರ್ಣ *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    ಯದಿ (!text) {
        text = "";
    }
    ಯದಿ (_this->SetPrimarySelectionText) {
        ಯದಿ (!_this->SetPrimarySelectionText(_this, text)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    ವರ್ಣ **mime_types = SDL_CopyClipboardMimeTypes((ಧ್ರುವ ವರ್ಣ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types, true);
    ಯದಿ (!mime_types) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->ಅಂಕೆ_clipboard_mime_types);
    ಪ್ರತ್ಯಾಗಮ true;
}

ವರ್ಣ *SDL_GetPrimarySelectionText(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ SDL_strdup("");
    }

    ಯದಿ (_this->GetPrimarySelectionText) {
        ಪ್ರತ್ಯಾಗಮ _this->GetPrimarySelectionText(_this);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ ವರ್ಣ *text = _this->primary_selection_text;
        ಯದಿ (!text) {
            text = "";
        }
        ಪ್ರತ್ಯಾಗಮ SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    ಯದಿ (_this->HasPrimarySelectionText) {
        ಪ್ರತ್ಯಾಗಮ _this->HasPrimarySelectionText(_this);
    } ಅನ್ಯಥಾ {
        ಯದಿ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ಪ್ರತ್ಯಾಗಮ true;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
}

