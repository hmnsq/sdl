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
    𐡄𐡍 (_this->clipboard_mime_types) {
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

    𐡄𐡍 (!_this) {
        أرجع;
    }

    𐡄𐡍 (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        أرجع;
    }

    𐡄𐡍 (_this->clipboard_cleanup) {
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

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    𐡄𐡍 (mime_types && num_mime_types > 0) {
        size_t num_allocated = 0;

        _this->clipboard_mime_types = (حرف **)SDL_malloc(num_mime_types * حجم(حرف *));
        𐡄𐡍 (_this->clipboard_mime_types) {
            لكل (size_t i = 0; i < num_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                𐡄𐡍 (_this->clipboard_mime_types[i]) {
                    ++num_allocated;
                }
            }
        }
        𐡄𐡍 (num_allocated < num_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            أرجع false;
        }
        _this->num_clipboard_mime_types = num_mime_types;
    }
    أرجع true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, فراغ *userdata, ثابت حرف *ثابت *mime_types, size_t num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    // Parameter validation
    𐡄𐡍 (!((callback && mime_types && num_mime_types > 0) ||
          (!callback && !mime_types && num_mime_types == 0))) {
        أرجع SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    𐡄𐡍 (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    𐡄𐡍 (!SDL_SaveClipboardMimeTypes(mime_types, num_mime_types)) {
        SDL_ClearClipboardData();
        أرجع false;
    }

    𐡄𐡍 (_this->SetClipboardData) {
        𐡄𐡍 (!_this->SetClipboardData(_this)) {
            أرجع false;
        }
    } وإلا 𐡄𐡍 (_this->SetClipboardText) {
        حرف *text = عدم;
        size_t size;

        لكل (size_t i = 0; i < num_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];
            𐡄𐡍 (SDL_IsTextMimeType(mime_type)) {
                ثابت فراغ *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                𐡄𐡍 (data) {
                    text = (حرف *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    𐡄𐡍 (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        أرجع false;
                    }
                    اكسر;
                }
            }
        }
        𐡄𐡍 (text) {
            SDL_free(text);
        } وإلا {
            𐡄𐡍 (!_this->SetClipboardText(_this, "")) {
                أرجع false;
            }
        }
    }

    حرف **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, num_mime_types, true);
    𐡄𐡍 (!mime_types_copy) {
        أرجع SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, num_mime_types);
    أرجع true;
}

bool SDL_ClearClipboardData(فراغ)
{
    أرجع SDL_SetClipboardData(عدم, عدم, عدم, عدم, 0);
}

فراغ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *size)
{
    فراغ *data = عدم;

    𐡄𐡍 (_this->clipboard_callback) {
        𐡄𐡍 (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            أرجع عدم;
        }

        ثابت فراغ *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        𐡄𐡍 (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + حجم(Uint32));
            𐡄𐡍 (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, حجم(Uint32));
            } وإلا {
                *size = 0;
            }
        }
    }
    أرجع data;
}

فراغ *SDL_GetClipboardData(ثابت حرف *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    𐡄𐡍 (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        أرجع عدم;
    }
    𐡄𐡍 (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    𐡄𐡍 (_this->GetClipboardData) {
        أرجع _this->GetClipboardData(_this, mime_type, size);
    } وإلا 𐡄𐡍 (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        حرف *text = _this->GetClipboardText(_this);
        𐡄𐡍 (text) {
            𐡄𐡍 (*text == '\0') {
                SDL_free(text);
                text = عدم;
            } وإلا {
                *size = SDL_strlen(text);
            }
        }
        أرجع text;
    } وإلا {
        أرجع SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t i;

    لكل (i = 0; i < _this->num_clipboard_mime_types; ++i) {
        𐡄𐡍 (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            أرجع true;
        }
    }
    أرجع false;
}

bool SDL_HasClipboardData(ثابت حرف *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        أرجع SDL_InvalidParamError("mime_type");
    }

    𐡄𐡍 (_this->HasClipboardData) {
        أرجع _this->HasClipboardData(_this, mime_type);
    } وإلا 𐡄𐡍 (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        أرجع _this->HasClipboardText(_this);
    } وإلا {
        أرجع SDL_HasInternalClipboardData(_this, mime_type);
    }
}

حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t num_mime_types, bool temporary)
{
    size_t allocSize = حجم(حرف *);
    لكل (size_t i = 0; i < num_mime_types; i++) {
        allocSize += حجم(حرف *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    حرف *ret;
    𐡄𐡍 (temporary)
        ret = (حرف *)SDL_AllocateTemporaryMemory(allocSize);
    وإلا
        ret = (حرف *)SDL_malloc(allocSize);
    𐡄𐡍 (!ret) {
        أرجع عدم;
    }

    حرف **result = (حرف **)ret;
    ret += حجم(حرف *) * (num_mime_types + 1);

    لكل (size_t i = 0; i < num_mime_types; i++) {
        result[i] = ret;

        ثابت حرف *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        حرف c;
        𐡏𐡁𐡃 {
            c = *ret++ = *mime_type++;
        } طالما (c != '\0');
    }
    result[num_mime_types] = عدم;

    أرجع result;

}

حرف **SDL_GetClipboardMimeTypes(size_t *num_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (num_mime_types) {
        *num_mime_types = 0;
    }

    𐡄𐡍 (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    𐡄𐡍 (num_mime_types) {
        *num_mime_types = _this->num_clipboard_mime_types;
    }
    أرجع SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ثابت حرف *mime_type)
{
    أرجع (SDL_strncmp(mime_type, "text", 4) == 0);
}

ساكن ثابت حرف *ثابت *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *num_mime_types)
{
    𐡄𐡍 (_this->GetTextMimeTypes) {
        أرجع _this->GetTextMimeTypes(_this, num_mime_types);
    } وإلا {
        ساكن ثابت حرف *ثابت text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *num_mime_types = SDL_arraysize(text_mime_types);
        أرجع text_mime_types;
    }
}

ثابت فراغ * SDLCALL SDL_ClipboardTextCallback(فراغ *userdata, ثابت حرف *mime_type, size_t *size)
{
    حرف *text = (حرف *)userdata;
    𐡄𐡍 (text) {
        *size = SDL_strlen(text);
    } وإلا {
        *size = 0;
    }
    أرجع text;
}

bool SDL_SetClipboardText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    𐡄𐡍 (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);

        أرجع SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, num_mime_types);
    }
    أرجع SDL_ClearClipboardData();
}

حرف *SDL_GetClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;
    size_t length;
    حرف *text = عدم;

    𐡄𐡍 (!_this) {
        SDL_UninitializedVideo();
        أرجع SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    لكل (i = 0; i < num_mime_types; ++i) {
        فراغ *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        𐡄𐡍 (clipdata) {
            text = (حرف *)clipdata;
            اكسر;
        }
    }

    𐡄𐡍 (!text) {
        text = SDL_strdup("");
    }
    أرجع text;
}

bool SDL_HasClipboardText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, num_mime_types;
    ثابت حرف *ثابت *text_mime_types;

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &num_mime_types);
    لكل (i = 0; i < num_mime_types; ++i) {
        𐡄𐡍 (SDL_HasClipboardData(text_mime_types[i])) {
            أرجع true;
        }
    }
    أرجع false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ثابت حرف *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    𐡄𐡍 (!text) {
        text = "";
    }
    𐡄𐡍 (_this->SetPrimarySelectionText) {
        𐡄𐡍 (!_this->SetPrimarySelectionText(_this, text)) {
            أرجع false;
        }
    } وإلا {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    حرف **mime_types = SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->num_clipboard_mime_types, true);
    𐡄𐡍 (!mime_types) {
        أرجع SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->num_clipboard_mime_types);
    أرجع true;
}

حرف *SDL_GetPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (!_this) {
        SDL_UninitializedVideo();
        أرجع SDL_strdup("");
    }

    𐡄𐡍 (_this->GetPrimarySelectionText) {
        أرجع _this->GetPrimarySelectionText(_this);
    } وإلا {
        ثابت حرف *text = _this->primary_selection_text;
        𐡄𐡍 (!text) {
            text = "";
        }
        أرجع SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    𐡄𐡍 (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    𐡄𐡍 (_this->HasPrimarySelectionText) {
        أرجع _this->HasPrimarySelectionText(_this);
    } وإلا {
        𐡄𐡍 (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
}

