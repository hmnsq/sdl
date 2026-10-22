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
    אם (_this->clipboard_mime_types) {
        עבור (size_t i = 0; i < _this->num_clipboard_mime_types; ++i) {
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

    אם (!_this) {
        החזר;
    }

    אם (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        החזר;
    }

    אם (_this->clipboard_cleanup) {
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

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    אם (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (حرف **)SDL_malloc(num_mime_types * حجم(حرف *));
        אם (_this->clipboard_mime_types) {
            עבור (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                אם (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        אם (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            החזר false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    החזר true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, فراغ *userdata, ثابت حرف *ثابت *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    // Parameter validation
    אם (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        החזר SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    אם (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    אם (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        החזר false;
    }

    אם (_this->SetClipboardData) {
        אם (!_this->SetClipboardData(_this)) {
            החזר false;
        }
    } אחרת אם (_this->SetClipboardText) {
        حرف *text = عدم;
        size_t size;

        עבור (size_t i = 0; i < num_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];
            אם (SDL_IsTextMimeType(mime_type)) {
                ثابت فراغ *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                אם (data) {
                    text = (حرف *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    אם (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        החזר false;
                    }
                    اكسر;
                }
            }
        }
        אם (text) {
            SDL_free(text);
        } אחרת {
            אם (!_this->SetClipboardText(_this, "")) {
                החזר false;
            }
        }
    }

    حرف **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    אם (!mime_types_copy) {
        החזר SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    החזר true;
}

bool SDL_ClearClipboardData(فراغ)
{
    החזר SDL_SetClipboardData(عدم, عدم, عدم, عدم, 0);
}

فراغ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *size)
{
    فراغ *data = عدم;

    אם (_this->clipboard_callback) {
        אם (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            החזר عدم;
        }

        ثابت فراغ *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        אם (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + حجم(Uint32));
            אם (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, حجم(Uint32));
            } אחרת {
                *size = 0;
            }
        }
    }
    החזר data;
}

فراغ *SDL_GetClipboardData(ثابت حرف *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        החזר عدم;
    }
    אם (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    אם (_this->GetClipboardData) {
        החזר _this->GetClipboardData(_this, mime_type, size);
    } אחרת אם (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        حرف *text = _this->GetClipboardText(_this);
        אם (text) {
            אם (*text == '\0') {
                SDL_free(text);
                text = عدم;
            } אחרת {
                *size = SDL_strlen(text);
            }
        }
        החזר text;
    } אחרת {
        החזר SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t i;

    עבור (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        אם (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            החזר true;
        }
    }
    החזר false;
}

bool SDL_HasClipboardData(ثابت حرف *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        החזר SDL_InvalidParamError("mime_type");
    }

    אם (_this->HasClipboardData) {
        החזר _this->HasClipboardData(_this, mime_type);
    } אחרת אם (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        החזר _this->HasClipboardText(_this);
    } אחרת {
        החזר SDL_HasInternalClipboardData(_this, mime_type);
    }
}

حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = حجم(حرف *);
    עבור (size_t i = 0; i < num_mime_types; i++) {
        allocSize += حجم(حرف *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    حرف *ret;
    אם (temporary)
        ret = (حرف *)SDL_AllocateTemporaryMemory(allocSize);
    אחרת
        ret = (حرف *)SDL_malloc(allocSize);
    אם (!ret) {
        החזר عدم;
    }

    حرف **result = (حرف **)ret;
    ret += حجم(حرف *) * (num_mime_types + 1);

    עבור (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        ثابت حرف *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        حرف c;
        עשה {
            c = *ret++ = *mime_type++;
        } כלעוד (c != '\0');
    }
    result[num_mime_types] = عدم;

    החזר result;

}

حرف **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (num_mime_types) {
        *num_mime_types = 0;
    }

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }

    אם (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    החזר SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ثابت حرف *mime_type)
{
    החזר (SDL_strncmp(mime_type, "text", 4) == 0);
}

ساكن ثابت حرف *ثابت *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    אם (_this->GetTextMimeTypes) {
        החזר _this->GetTextMimeTypes(_this, num_mime_types);
    } אחרת {
        ساكن ثابت حرف *ثابت text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        החזר text_mime_types;
    }
}

ثابت فراغ * SDLCALL SDL_ClipboardTextCallback(فراغ *userdata, ثابت حرف *mime_type, size_t *size)
{
    حرف *text = (حرف *)userdata;
    אם (text) {
        *size = SDL_strlen(text);
    } אחרת {
        *size = 0;
    }
    החזר text;
}

bool SDL_SetClipboardText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    אם (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        החזר SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    החזר SDL_ClearClipboardData();
}

حرف *SDL_GetClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;
    size_t length;
    حرف *text = عدم;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    עבור (i = 0; i < num_mime_types; ++i) {
        فراغ *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        אם (clipdata) {
            text = (حرف *)clipdata;
            اكسر;
        }
    }

    אם (!text) {
        text = SDL_strdup("");
    }
    החזר text;
}

bool SDL_HasClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    עבור (i = 0; i < num_mime_types; ++i) {
        אם (SDL_HasClipboardData(text_mime_types[i])) {
            החזר true;
        }
    }
    החזר false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    אם (!text) {
        text = "";
    }
    אם (_this->SetPrimarySelectionText) {
        אם (!_this->SetPrimarySelectionText(_this, text)) {
            החזר false;
        }
    } אחרת {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    حرف **mime_types = SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    אם (!mime_types) {
        החזר SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    החזר true;
}

حرف *SDL_GetPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר SDL_strdup("");
    }

    אם (_this->GetPrimarySelectionText) {
        החזר _this->GetPrimarySelectionText(_this);
    } אחרת {
        ثابت حرف *text = _this->primary_selection_text;
        אם (!text) {
            text = "";
        }
        החזר SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    אם (_this->HasPrimarySelectionText) {
        החזר _this->HasPrimarySelectionText(_this);
    } אחרת {
        אם (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            החזר true;
        } אחרת {
            החזר false;
        }
    }
}

