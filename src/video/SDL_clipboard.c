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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_clipboard_c.h"
#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "../events/SDL_events_c.h"
#அந்தர்பாவ "../events/SDL_clipboardevents_c.h"

வெறுமை SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    எனில் (_this->clipboard_mime_types) {
        க்கு (size_t i = 0; i < _this->இலக்கம்_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = வெற்று;
        _this->இலக்கம்_clipboard_mime_types = 0;
    }
}


வெறுமை SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு;
    }

    எனில் (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        திரும்பு;
    }

    எனில் (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = வெற்று;
    _this->clipboard_cleanup = வெற்று;
    _this->clipboard_userdata = வெற்று;
}

bool SDL_SaveClipboardMimeTypes(மாறிலி எழுத்து *மாறிலி *mime_types, size_t இலக்கம்_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    எனில் (mime_types && இலக்கம்_mime_types > 0) {
        size_t இலக்கம்_allocated = 0;

        _this->clipboard_mime_types = (எழுத்து **)SDL_malloc(இலக்கம்_mime_types * அளவு(எழுத்து *));
        எனில் (_this->clipboard_mime_types) {
            க்கு (size_t i = 0; i < இலக்கம்_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                எனில் (_this->clipboard_mime_types[i]) {
                    ++இலக்கம்_allocated;
                }
            }
        }
        எனில் (இலக்கம்_allocated < இலக்கம்_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            திரும்பு false;
        }
        _this->இலக்கம்_clipboard_mime_types = இலக்கம்_mime_types;
    }
    திரும்பு true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, வெறுமை *userdata, மாறிலி எழுத்து *மாறிலி *mime_types, size_t இலக்கம்_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    // Parameter validation
    எனில் (!((callback && mime_types && இலக்கம்_mime_types > 0) ||
          (!callback && !mime_types && இலக்கம்_mime_types == 0))) {
        திரும்பு SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    எனில் (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    எனில் (!SDL_SaveClipboardMimeTypes(mime_types, இலக்கம்_mime_types)) {
        SDL_ClearClipboardData();
        திரும்பு false;
    }

    எனில் (_this->SetClipboardData) {
        எனில் (!_this->SetClipboardData(_this)) {
            திரும்பு false;
        }
    } இல்லையெனில் எனில் (_this->SetClipboardText) {
        எழுத்து *text = வெற்று;
        size_t size;

        க்கு (size_t i = 0; i < இலக்கம்_mime_types; ++i) {
            மாறிலி எழுத்து *mime_type = _this->clipboard_mime_types[i];
            எனில் (SDL_IsTextMimeType(mime_type)) {
                மாறிலி வெறுமை *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                எனில் (data) {
                    text = (எழுத்து *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    எனில் (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        திரும்பு false;
                    }
                    நிறுத்து;
                }
            }
        }
        எனில் (text) {
            SDL_free(text);
        } இல்லையெனில் {
            எனில் (!_this->SetClipboardText(_this, "")) {
                திரும்பு false;
            }
        }
    }

    எழுத்து **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, இலக்கம்_mime_types, true);
    எனில் (!mime_types_copy) {
        திரும்பு SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, இலக்கம்_mime_types);
    திரும்பு true;
}

bool SDL_ClearClipboardData(வெறுமை)
{
    திரும்பு SDL_SetClipboardData(வெற்று, வெற்று, வெற்று, வெற்று, 0);
}

வெறுமை *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *size)
{
    வெறுமை *data = வெற்று;

    எனில் (_this->clipboard_callback) {
        எனில் (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            திரும்பு வெற்று;
        }

        மாறிலி வெறுமை *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        எனில் (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + அளவு(Uint32));
            எனில் (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, அளவு(Uint32));
            } இல்லையெனில் {
                *size = 0;
            }
        }
    }
    திரும்பு data;
}

வெறுமை *SDL_GetClipboardData(மாறிலி எழுத்து *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        திரும்பு வெற்று;
    }
    எனில் (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    எனில் (_this->GetClipboardData) {
        திரும்பு _this->GetClipboardData(_this, mime_type, size);
    } இல்லையெனில் எனில் (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        எழுத்து *text = _this->GetClipboardText(_this);
        எனில் (text) {
            எனில் (*text == '\0') {
                SDL_free(text);
                text = வெற்று;
            } இல்லையெனில் {
                *size = SDL_strlen(text);
            }
        }
        திரும்பு text;
    } இல்லையெனில் {
        திரும்பு SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type)
{
    size_t i;

    க்கு (i = 0; i < _this->இலக்கம்_clipboard_mime_types; ++i) {
        எனில் (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

bool SDL_HasClipboardData(மாறிலி எழுத்து *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        திரும்பு SDL_InvalidParamError("mime_type");
    }

    எனில் (_this->HasClipboardData) {
        திரும்பு _this->HasClipboardData(_this, mime_type);
    } இல்லையெனில் எனில் (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        திரும்பு _this->HasClipboardText(_this);
    } இல்லையெனில் {
        திரும்பு SDL_HasInternalClipboardData(_this, mime_type);
    }
}

எழுத்து **SDL_CopyClipboardMimeTypes(மாறிலி எழுத்து *மாறிலி *clipboard_mime_types, size_t இலக்கம்_mime_types, bool temporary)
{
    size_t allocSize = அளவு(எழுத்து *);
    க்கு (size_t i = 0; i < இலக்கம்_mime_types; i++) {
        allocSize += அளவு(எழுத்து *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    எழுத்து *ret;
    எனில் (temporary)
        ret = (எழுத்து *)SDL_AllocateTemporaryMemory(allocSize);
    இல்லையெனில்
        ret = (எழுத்து *)SDL_malloc(allocSize);
    எனில் (!ret) {
        திரும்பு வெற்று;
    }

    எழுத்து **result = (எழுத்து **)ret;
    ret += அளவு(எழுத்து *) * (இலக்கம்_mime_types + 1);

    க்கு (size_t i = 0; i < இலக்கம்_mime_types; i++) {
        result[i] = ret;

        மாறிலி எழுத்து *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        எழுத்து c;
        செய் {
            c = *ret++ = *mime_type++;
        } போது (c != '\0');
    }
    result[இலக்கம்_mime_types] = வெற்று;

    திரும்பு result;

}

எழுத்து **SDL_GetClipboardMimeTypes(size_t *இலக்கம்_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (இலக்கம்_mime_types) {
        *இலக்கம்_mime_types = 0;
    }

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }

    எனில் (இலக்கம்_mime_types) {
        *இலக்கம்_mime_types = _this->இலக்கம்_clipboard_mime_types;
    }
    திரும்பு SDL_CopyClipboardMimeTypes((மாறிலி எழுத்து **)_this->clipboard_mime_types, _this->இலக்கம்_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(மாறிலி எழுத்து *mime_type)
{
    திரும்பு (SDL_strncmp(mime_type, "text", 4) == 0);
}

நிலையான மாறிலி எழுத்து *மாறிலி *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *இலக்கம்_mime_types)
{
    எனில் (_this->GetTextMimeTypes) {
        திரும்பு _this->GetTextMimeTypes(_this, இலக்கம்_mime_types);
    } இல்லையெனில் {
        நிலையான மாறிலி எழுத்து *மாறிலி text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *இலக்கம்_mime_types = SDL_arraysize(text_mime_types);
        திரும்பு text_mime_types;
    }
}

மாறிலி வெறுமை * SDLCALL SDL_ClipboardTextCallback(வெறுமை *userdata, மாறிலி எழுத்து *mime_type, size_t *size)
{
    எழுத்து *text = (எழுத்து *)userdata;
    எனில் (text) {
        *size = SDL_strlen(text);
    } இல்லையெனில் {
        *size = 0;
    }
    திரும்பு text;
}

bool SDL_SetClipboardText(மாறிலி எழுத்து *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t இலக்கம்_mime_types;
    மாறிலி எழுத்து *மாறிலி *text_mime_types;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    எனில் (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &இலக்கம்_mime_types);

        திரும்பு SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, இலக்கம்_mime_types);
    }
    திரும்பு SDL_ClearClipboardData();
}

எழுத்து *SDL_GetClipboardText(வெறுமை)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, இலக்கம்_mime_types;
    மாறிலி எழுத்து *மாறிலி *text_mime_types;
    size_t length;
    எழுத்து *text = வெற்று;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &இலக்கம்_mime_types);
    க்கு (i = 0; i < இலக்கம்_mime_types; ++i) {
        வெறுமை *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        எனில் (clipdata) {
            text = (எழுத்து *)clipdata;
            நிறுத்து;
        }
    }

    எனில் (!text) {
        text = SDL_strdup("");
    }
    திரும்பு text;
}

bool SDL_HasClipboardText(வெறுமை)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, இலக்கம்_mime_types;
    மாறிலி எழுத்து *மாறிலி *text_mime_types;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &இலக்கம்_mime_types);
    க்கு (i = 0; i < இலக்கம்_mime_types; ++i) {
        எனில் (SDL_HasClipboardData(text_mime_types[i])) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(மாறிலி எழுத்து *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    எனில் (!text) {
        text = "";
    }
    எனில் (_this->SetPrimarySelectionText) {
        எனில் (!_this->SetPrimarySelectionText(_this, text)) {
            திரும்பு false;
        }
    } இல்லையெனில் {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    எழுத்து **mime_types = SDL_CopyClipboardMimeTypes((மாறிலி எழுத்து **)_this->clipboard_mime_types, _this->இலக்கம்_clipboard_mime_types, true);
    எனில் (!mime_types) {
        திரும்பு SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->இலக்கம்_clipboard_mime_types);
    திரும்பு true;
}

எழுத்து *SDL_GetPrimarySelectionText(வெறுமை)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு SDL_strdup("");
    }

    எனில் (_this->GetPrimarySelectionText) {
        திரும்பு _this->GetPrimarySelectionText(_this);
    } இல்லையெனில் {
        மாறிலி எழுத்து *text = _this->primary_selection_text;
        எனில் (!text) {
            text = "";
        }
        திரும்பு SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(வெறுமை)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    எனில் (_this->HasPrimarySelectionText) {
        திரும்பு _this->HasPrimarySelectionText(_this);
    } இல்லையெனில் {
        எனில் (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            திரும்பு true;
        } இல்லையெனில் {
            திரும்பு false;
        }
    }
}

