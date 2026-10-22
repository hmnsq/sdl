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
#شامل "SDL_internal.h"

#شامل "SDL_clipboard_c.h"
#شامل "SDL_sysvideo.h"
#شامل "../events/SDL_events_c.h"
#شامل "../events/SDL_clipboardevents_c.h"

تهی SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    اگر (_this->clipboard_mime_types) {
        برای (size_t i = 0; i < _this->رقم_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = پوچ;
        _this->رقم_clipboard_mime_types = 0;
    }
}


تهی SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت;
    }

    اگر (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        بازگشت;
    }

    اگر (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = پوچ;
    _this->clipboard_cleanup = پوچ;
    _this->clipboard_userdata = پوچ;
}

bool SDL_SaveClipboardMimeTypes(ثابت نویسه *ثابت *mime_types, size_t رقم_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    اگر (mime_types && رقم_mime_types > 0) {
        size_t رقم_allocated = 0;

        _this->clipboard_mime_types = (نویسه **)SDL_malloc(رقم_mime_types * اندازه(نویسه *));
        اگر (_this->clipboard_mime_types) {
            برای (size_t i = 0; i < رقم_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                اگر (_this->clipboard_mime_types[i]) {
                    ++رقم_allocated;
                }
            }
        }
        اگر (رقم_allocated < رقم_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            بازگشت false;
        }
        _this->رقم_clipboard_mime_types = رقم_mime_types;
    }
    بازگشت true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, تهی *userdata, ثابت نویسه *ثابت *mime_types, size_t رقم_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    // Parameter validation
    اگر (!((callback && mime_types && رقم_mime_types > 0) ||
          (!callback && !mime_types && رقم_mime_types == 0))) {
        بازگشت SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    اگر (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    اگر (!SDL_SaveClipboardMimeTypes(mime_types, رقم_mime_types)) {
        SDL_ClearClipboardData();
        بازگشت false;
    }

    اگر (_this->SetClipboardData) {
        اگر (!_this->SetClipboardData(_this)) {
            بازگشت false;
        }
    } وگرنه اگر (_this->SetClipboardText) {
        نویسه *text = پوچ;
        size_t size;

        برای (size_t i = 0; i < رقم_mime_types; ++i) {
            ثابت نویسه *mime_type = _this->clipboard_mime_types[i];
            اگر (SDL_IsTextMimeType(mime_type)) {
                ثابت تهی *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                اگر (data) {
                    text = (نویسه *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    اگر (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        بازگشت false;
                    }
                    بشکن;
                }
            }
        }
        اگر (text) {
            SDL_free(text);
        } وگرنه {
            اگر (!_this->SetClipboardText(_this, "")) {
                بازگشت false;
            }
        }
    }

    نویسه **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, رقم_mime_types, true);
    اگر (!mime_types_copy) {
        بازگشت SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, رقم_mime_types);
    بازگشت true;
}

bool SDL_ClearClipboardData(تهی)
{
    بازگشت SDL_SetClipboardData(پوچ, پوچ, پوچ, پوچ, 0);
}

تهی *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type, size_t *size)
{
    تهی *data = پوچ;

    اگر (_this->clipboard_callback) {
        اگر (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            بازگشت پوچ;
        }

        ثابت تهی *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        اگر (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + اندازه(Uint32));
            اگر (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, اندازه(Uint32));
            } وگرنه {
                *size = 0;
            }
        }
    }
    بازگشت data;
}

تهی *SDL_GetClipboardData(ثابت نویسه *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        بازگشت پوچ;
    }
    اگر (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    اگر (_this->GetClipboardData) {
        بازگشت _this->GetClipboardData(_this, mime_type, size);
    } وگرنه اگر (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        نویسه *text = _this->GetClipboardText(_this);
        اگر (text) {
            اگر (*text == '\0') {
                SDL_free(text);
                text = پوچ;
            } وگرنه {
                *size = SDL_strlen(text);
            }
        }
        بازگشت text;
    } وگرنه {
        بازگشت SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ثابت نویسه *mime_type)
{
    size_t i;

    برای (i = 0; i < _this->رقم_clipboard_mime_types; ++i) {
        اگر (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            بازگشت true;
        }
    }
    بازگشت false;
}

bool SDL_HasClipboardData(ثابت نویسه *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        بازگشت SDL_InvalidParamError("mime_type");
    }

    اگر (_this->HasClipboardData) {
        بازگشت _this->HasClipboardData(_this, mime_type);
    } وگرنه اگر (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        بازگشت _this->HasClipboardText(_this);
    } وگرنه {
        بازگشت SDL_HasInternalClipboardData(_this, mime_type);
    }
}

نویسه **SDL_CopyClipboardMimeTypes(ثابت نویسه *ثابت *clipboard_mime_types, size_t رقم_mime_types, bool temporary)
{
    size_t allocSize = اندازه(نویسه *);
    برای (size_t i = 0; i < رقم_mime_types; i++) {
        allocSize += اندازه(نویسه *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    نویسه *ret;
    اگر (temporary)
        ret = (نویسه *)SDL_AllocateTemporaryMemory(allocSize);
    وگرنه
        ret = (نویسه *)SDL_malloc(allocSize);
    اگر (!ret) {
        بازگشت پوچ;
    }

    نویسه **result = (نویسه **)ret;
    ret += اندازه(نویسه *) * (رقم_mime_types + 1);

    برای (size_t i = 0; i < رقم_mime_types; i++) {
        result[i] = ret;

        ثابت نویسه *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        نویسه c;
        انجامبده {
            c = *ret++ = *mime_type++;
        } وقتی (c != '\0');
    }
    result[رقم_mime_types] = پوچ;

    بازگشت result;

}

نویسه **SDL_GetClipboardMimeTypes(size_t *رقم_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (رقم_mime_types) {
        *رقم_mime_types = 0;
    }

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }

    اگر (رقم_mime_types) {
        *رقم_mime_types = _this->رقم_clipboard_mime_types;
    }
    بازگشت SDL_CopyClipboardMimeTypes((ثابت نویسه **)_this->clipboard_mime_types, _this->رقم_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ثابت نویسه *mime_type)
{
    بازگشت (SDL_strncmp(mime_type, "text", 4) == 0);
}

ایستا ثابت نویسه *ثابت *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *رقم_mime_types)
{
    اگر (_this->GetTextMimeTypes) {
        بازگشت _this->GetTextMimeTypes(_this, رقم_mime_types);
    } وگرنه {
        ایستا ثابت نویسه *ثابت text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *رقم_mime_types = SDL_arraysize(text_mime_types);
        بازگشت text_mime_types;
    }
}

ثابت تهی * SDLCALL SDL_ClipboardTextCallback(تهی *userdata, ثابت نویسه *mime_type, size_t *size)
{
    نویسه *text = (نویسه *)userdata;
    اگر (text) {
        *size = SDL_strlen(text);
    } وگرنه {
        *size = 0;
    }
    بازگشت text;
}

bool SDL_SetClipboardText(ثابت نویسه *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t رقم_mime_types;
    ثابت نویسه *ثابت *text_mime_types;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    اگر (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &رقم_mime_types);

        بازگشت SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, رقم_mime_types);
    }
    بازگشت SDL_ClearClipboardData();
}

نویسه *SDL_GetClipboardText(تهی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, رقم_mime_types;
    ثابت نویسه *ثابت *text_mime_types;
    size_t length;
    نویسه *text = پوچ;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &رقم_mime_types);
    برای (i = 0; i < رقم_mime_types; ++i) {
        تهی *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        اگر (clipdata) {
            text = (نویسه *)clipdata;
            بشکن;
        }
    }

    اگر (!text) {
        text = SDL_strdup("");
    }
    بازگشت text;
}

bool SDL_HasClipboardText(تهی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, رقم_mime_types;
    ثابت نویسه *ثابت *text_mime_types;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &رقم_mime_types);
    برای (i = 0; i < رقم_mime_types; ++i) {
        اگر (SDL_HasClipboardData(text_mime_types[i])) {
            بازگشت true;
        }
    }
    بازگشت false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ثابت نویسه *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    اگر (!text) {
        text = "";
    }
    اگر (_this->SetPrimarySelectionText) {
        اگر (!_this->SetPrimarySelectionText(_this, text)) {
            بازگشت false;
        }
    } وگرنه {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    نویسه **mime_types = SDL_CopyClipboardMimeTypes((ثابت نویسه **)_this->clipboard_mime_types, _this->رقم_clipboard_mime_types, true);
    اگر (!mime_types) {
        بازگشت SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->رقم_clipboard_mime_types);
    بازگشت true;
}

نویسه *SDL_GetPrimarySelectionText(تهی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت SDL_strdup("");
    }

    اگر (_this->GetPrimarySelectionText) {
        بازگشت _this->GetPrimarySelectionText(_this);
    } وگرنه {
        ثابت نویسه *text = _this->primary_selection_text;
        اگر (!text) {
            text = "";
        }
        بازگشت SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(تهی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    اگر (_this->HasPrimarySelectionText) {
        بازگشت _this->HasPrimarySelectionText(_this);
    } وگرنه {
        اگر (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            بازگشت true;
        } وگرنه {
            بازگشت false;
        }
    }
}

