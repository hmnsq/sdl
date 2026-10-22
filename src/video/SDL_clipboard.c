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
#ضمن "SDL_internal.h"

#ضمن "SDL_clipboard_c.h"
#ضمن "SDL_sysvideo.h"
#ضمن "../events/SDL_events_c.h"
#ضمن "../events/SDL_clipboardevents_c.h"

فراغ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    ܐܢ (_this->clipboard_mime_types) {
        لكل (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = عدم;
        _this->num_clipboard_mime_types = 0;
    }
}


فراغ SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ;
    }

    ܐܢ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ܦܢܐ;
    }

    ܐܢ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = عدم;
    _this->clipboard_cleanup = عدم;
    _this->clipboard_userdata = عدم;
}

bool SDL_SaveClipboardMimeTypes(ثابت حرف *ثابت *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ܐܢ (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (حرف **)SDL_malloc(num_mime_types * حجم(حرف *));
        ܐܢ (_this->clipboard_mime_types) {
            لكل (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ܐܢ (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        ܐܢ (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ܦܢܐ false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    ܦܢܐ true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, فراغ *userdata, ثابت حرف *ثابت *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    // Parameter validation
    ܐܢ (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        ܦܢܐ SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    ܐܢ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ܐܢ (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        ܦܢܐ false;
    }

    ܐܢ (_this->SetClipboardData) {
        ܐܢ (!_this->SetClipboardData(_this)) {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ ܐܢ (_this->SetClipboardText) {
        حرف *text = عدم;
        size_t size;

        لكل (size_t i = 0; i < num_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];
            ܐܢ (SDL_IsTextMimeType(mime_type)) {
                ثابت فراغ *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                ܐܢ (data) {
                    text = (حرف *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    ܐܢ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ܦܢܐ false;
                    }
                    اكسر;
                }
            }
        }
        ܐܢ (text) {
            SDL_free(text);
        } ܐܚܪܢܐ {
            ܐܢ (!_this->SetClipboardText(_this, "")) {
                ܦܢܐ false;
            }
        }
    }

    حرف **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    ܐܢ (!mime_types_copy) {
        ܦܢܐ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    ܦܢܐ true;
}

bool SDL_ClearClipboardData(فراغ)
{
    ܦܢܐ SDL_SetClipboardData(عدم, عدم, عدم, عدم, 0);
}

فراغ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *size)
{
    فراغ *data = عدم;

    ܐܢ (_this->clipboard_callback) {
        ܐܢ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ܦܢܐ عدم;
        }

        ثابت فراغ *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        ܐܢ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + حجم(Uint32));
            ܐܢ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, حجم(Uint32));
            } ܐܚܪܢܐ {
                *size = 0;
            }
        }
    }
    ܦܢܐ data;
}

فراغ *SDL_GetClipboardData(ثابت حرف *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ܦܢܐ عدم;
    }
    ܐܢ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    ܐܢ (_this->GetClipboardData) {
        ܦܢܐ _this->GetClipboardData(_this, mime_type, size);
    } ܐܚܪܢܐ ܐܢ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        حرف *text = _this->GetClipboardText(_this);
        ܐܢ (text) {
            ܐܢ (*text == '\0') {
                SDL_free(text);
                text = عدم;
            } ܐܚܪܢܐ {
                *size = SDL_strlen(text);
            }
        }
        ܦܢܐ text;
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t i;

    لكل (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        ܐܢ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ܦܢܐ true;
        }
    }
    ܦܢܐ false;
}

bool SDL_HasClipboardData(ثابت حرف *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ܦܢܐ SDL_InvalidParamError("mime_type");
    }

    ܐܢ (_this->HasClipboardData) {
        ܦܢܐ _this->HasClipboardData(_this, mime_type);
    } ܐܚܪܢܐ ܐܢ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ܦܢܐ _this->HasClipboardText(_this);
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_HasInternalClipboardData(_this, mime_type);
    }
}

حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = حجم(حرف *);
    لكل (size_t i = 0; i < num_mime_types; i++) {
        allocSize += حجم(حرف *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    حرف *ret;
    ܐܢ (temporary)
        ret = (حرف *)SDL_AllocateTemporaryMemory(allocSize);
    ܐܚܪܢܐ
        ret = (حرف *)SDL_malloc(allocSize);
    ܐܢ (!ret) {
        ܦܢܐ عدم;
    }

    حرف **result = (حرف **)ret;
    ret += حجم(حرف *) * (num_mime_types + 1);

    لكل (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        ثابت حرف *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        حرف c;
        ܥܒܕ {
            c = *ret++ = *mime_type++;
        } ܟܡܐ (c != '\0');
    }
    result[num_mime_types] = عدم;

    ܦܢܐ result;

}

حرف **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (num_mime_types) {
        *num_mime_types = 0;
    }

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }

    ܐܢ (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    ܦܢܐ SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ثابت حرف *mime_type)
{
    ܦܢܐ (SDL_strncmp(mime_type, "text", 4) == 0);
}

ساكن ثابت حرف *ثابت *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    ܐܢ (_this->GetTextMimeTypes) {
        ܦܢܐ _this->GetTextMimeTypes(_this, num_mime_types);
    } ܐܚܪܢܐ {
        ساكن ثابت حرف *ثابت text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        ܦܢܐ text_mime_types;
    }
}

ثابت فراغ * SDLCALL SDL_ClipboardTextCallback(فراغ *userdata, ثابت حرف *mime_type, size_t *size)
{
    حرف *text = (حرف *)userdata;
    ܐܢ (text) {
        *size = SDL_strlen(text);
    } ܐܚܪܢܐ {
        *size = 0;
    }
    ܦܢܐ text;
}

bool SDL_SetClipboardText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    ܐܢ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        ܦܢܐ SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    ܦܢܐ SDL_ClearClipboardData();
}

حرف *SDL_GetClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;
    size_t length;
    حرف *text = عدم;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    لكل (i = 0; i < num_mime_types; ++i) {
        فراغ *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        ܐܢ (clipdata) {
            text = (حرف *)clipdata;
            اكسر;
        }
    }

    ܐܢ (!text) {
        text = SDL_strdup("");
    }
    ܦܢܐ text;
}

bool SDL_HasClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    لكل (i = 0; i < num_mime_types; ++i) {
        ܐܢ (SDL_HasClipboardData(text_mime_types[i])) {
            ܦܢܐ true;
        }
    }
    ܦܢܐ false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    ܐܢ (!text) {
        text = "";
    }
    ܐܢ (_this->SetPrimarySelectionText) {
        ܐܢ (!_this->SetPrimarySelectionText(_this, text)) {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    حرف **mime_types = SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    ܐܢ (!mime_types) {
        ܦܢܐ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    ܦܢܐ true;
}

حرف *SDL_GetPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ SDL_strdup("");
    }

    ܐܢ (_this->GetPrimarySelectionText) {
        ܦܢܐ _this->GetPrimarySelectionText(_this);
    } ܐܚܪܢܐ {
        ثابت حرف *text = _this->primary_selection_text;
        ܐܢ (!text) {
            text = "";
        }
        ܦܢܐ SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    ܐܢ (_this->HasPrimarySelectionText) {
        ܦܢܐ _this->HasPrimarySelectionText(_this);
    } ܐܚܪܢܐ {
        ܐܢ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ܦܢܐ true;
        } ܐܚܪܢܐ {
            ܦܢܐ false;
        }
    }
}

