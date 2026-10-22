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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_clipboard_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../events/SDL_clipboardevents_c.h"

ଶୂନ୍ୟ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    ଯଦି (_this->clipboard_mime_types) {
        ପାଇଁ (size_t i = 0; i < _this->ଅଙ୍କ_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ଖାଲି;
        _this->ଅଙ୍କ_clipboard_mime_types = 0;
    }
}


ଶୂନ୍ୟ SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ;
    }

    ଯଦି (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ଫେରନ୍ତୁ;
    }

    ଯଦି (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ଖାଲି;
    _this->clipboard_cleanup = ଖାଲି;
    _this->clipboard_userdata = ଖାଲି;
}

bool SDL_SaveClipboardMimeTypes(ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types, size_t ଅଙ୍କ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ଯଦି (mime_types && ଅଙ୍କ_mime_types > 0) {
        size_t ଅଙ୍କ_allocated = 0;

        _this->clipboard_mime_types = (ଅକ୍ଷର **)SDL_malloc(ଅଙ୍କ_mime_types * ଆକାର(ଅକ୍ଷର *));
        ଯଦି (_this->clipboard_mime_types) {
            ପାଇଁ (size_t i = 0; i < ଅଙ୍କ_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ଯଦି (_this->clipboard_mime_types[i]) {
                    ++ଅଙ୍କ_allocated;
                }
            }
        }
        ଯଦି (ଅଙ୍କ_allocated < ଅଙ୍କ_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ଫେରନ୍ତୁ false;
        }
        _this->ଅଙ୍କ_clipboard_mime_types = ଅଙ୍କ_mime_types;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, ଶୂନ୍ୟ *userdata, ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types, size_t ଅଙ୍କ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    // Parameter validation
    ଯଦି (!((callback && mime_types && ଅଙ୍କ_mime_types > 0) ||
          (!callback && !mime_types && ଅଙ୍କ_mime_types == 0))) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    ଯଦି (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ଯଦି (!SDL_SaveClipboardMimeTypes(mime_types, ଅଙ୍କ_mime_types)) {
        SDL_ClearClipboardData();
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (_this->SetClipboardData) {
        ଯଦି (!_this->SetClipboardData(_this)) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା ଯଦି (_this->SetClipboardText) {
        ଅକ୍ଷର *text = ଖାଲି;
        size_t size;

        ପାଇଁ (size_t i = 0; i < ଅଙ୍କ_mime_types; ++i) {
            ଅଚଳ ଅକ୍ଷର *mime_type = _this->clipboard_mime_types[i];
            ଯଦି (SDL_IsTextMimeType(mime_type)) {
                ଅଚଳ ଶୂନ୍ୟ *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                ଯଦି (data) {
                    text = (ଅକ୍ଷର *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    ଯଦି (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ଫେରନ୍ତୁ false;
                    }
                    ଭାଙ୍ଗ;
                }
            }
        }
        ଯଦି (text) {
            SDL_free(text);
        } ଅନ୍ୟଥା {
            ଯଦି (!_this->SetClipboardText(_this, "")) {
                ଫେରନ୍ତୁ false;
            }
        }
    }

    ଅକ୍ଷର **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, ଅଙ୍କ_mime_types, true);
    ଯଦି (!mime_types_copy) {
        ଫେରନ୍ତୁ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, ଅଙ୍କ_mime_types);
    ଫେରନ୍ତୁ true;
}

bool SDL_ClearClipboardData(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ SDL_SetClipboardData(ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, 0);
}

ଶୂନ୍ୟ *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *size)
{
    ଶୂନ୍ୟ *data = ଖାଲି;

    ଯଦି (_this->clipboard_callback) {
        ଯଦି (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ଫେରନ୍ତୁ ଖାଲି;
        }

        ଅଚଳ ଶୂନ୍ୟ *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        ଯଦି (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + ଆକାର(Uint32));
            ଯଦି (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, ଆକାର(Uint32));
            } ଅନ୍ୟଥା {
                *size = 0;
            }
        }
    }
    ଫେରନ୍ତୁ data;
}

ଶୂନ୍ୟ *SDL_GetClipboardData(ଅଚଳ ଅକ୍ଷର *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    ଯଦି (_this->GetClipboardData) {
        ଫେରନ୍ତୁ _this->GetClipboardData(_this, mime_type, size);
    } ଅନ୍ୟଥା ଯଦି (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        ଅକ୍ଷର *text = _this->GetClipboardText(_this);
        ଯଦି (text) {
            ଯଦି (*text == '\0') {
                SDL_free(text);
                text = ଖାଲି;
            } ଅନ୍ୟଥା {
                *size = SDL_strlen(text);
            }
        }
        ଫେରନ୍ତୁ text;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    size_t i;

    ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_clipboard_mime_types; ++i) {
        ଯଦି (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

bool SDL_HasClipboardData(ଅଚଳ ଅକ୍ଷର *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("mime_type");
    }

    ଯଦି (_this->HasClipboardData) {
        ଫେରନ୍ତୁ _this->HasClipboardData(_this, mime_type);
    } ଅନ୍ୟଥା ଯଦି (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ଫେରନ୍ତୁ _this->HasClipboardText(_this);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_HasInternalClipboardData(_this, mime_type);
    }
}

ଅକ୍ଷର **SDL_CopyClipboardMimeTypes(ଅଚଳ ଅକ୍ଷର *ଅଚଳ *clipboard_mime_types, size_t ଅଙ୍କ_mime_types, bool temporary)
{
    size_t allocSize = ଆକାର(ଅକ୍ଷର *);
    ପାଇଁ (size_t i = 0; i < ଅଙ୍କ_mime_types; i++) {
        allocSize += ଆକାର(ଅକ୍ଷର *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    ଅକ୍ଷର *ret;
    ଯଦି (temporary)
        ret = (ଅକ୍ଷର *)SDL_AllocateTemporaryMemory(allocSize);
    ଅନ୍ୟଥା
        ret = (ଅକ୍ଷର *)SDL_malloc(allocSize);
    ଯଦି (!ret) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଅକ୍ଷର **result = (ଅକ୍ଷର **)ret;
    ret += ଆକାର(ଅକ୍ଷର *) * (ଅଙ୍କ_mime_types + 1);

    ପାଇଁ (size_t i = 0; i < ଅଙ୍କ_mime_types; i++) {
        result[i] = ret;

        ଅଚଳ ଅକ୍ଷର *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        ଅକ୍ଷର c;
        କର {
            c = *ret++ = *mime_type++;
        } ଯେତେବେଳେ (c != '\0');
    }
    result[ଅଙ୍କ_mime_types] = ଖାଲି;

    ଫେରନ୍ତୁ result;

}

ଅକ୍ଷର **SDL_GetClipboardMimeTypes(size_t *ଅଙ୍କ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (ଅଙ୍କ_mime_types) {
        *ଅଙ୍କ_mime_types = 0;
    }

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (ଅଙ୍କ_mime_types) {
        *ଅଙ୍କ_mime_types = _this->ଅଙ୍କ_clipboard_mime_types;
    }
    ଫେରନ୍ତୁ SDL_CopyClipboardMimeTypes((ଅଚଳ ଅକ୍ଷର **)_this->clipboard_mime_types, _this->ଅଙ୍କ_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଫେରନ୍ତୁ (SDL_strncmp(mime_type, "text", 4) == 0);
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types)
{
    ଯଦି (_this->GetTextMimeTypes) {
        ଫେରନ୍ତୁ _this->GetTextMimeTypes(_this, ଅଙ୍କ_mime_types);
    } ଅନ୍ୟଥା {
        ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *ଅଙ୍କ_mime_types = SDL_arraysize(text_mime_types);
        ଫେରନ୍ତୁ text_mime_types;
    }
}

ଅଚଳ ଶୂନ୍ୟ * SDLCALL SDL_ClipboardTextCallback(ଶୂନ୍ୟ *userdata, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *size)
{
    ଅକ୍ଷର *text = (ଅକ୍ଷର *)userdata;
    ଯଦି (text) {
        *size = SDL_strlen(text);
    } ଅନ୍ୟଥା {
        *size = 0;
    }
    ଫେରନ୍ତୁ text;
}

bool SDL_SetClipboardText(ଅଚଳ ଅକ୍ଷର *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ଅଙ୍କ_mime_types;
    ଅଚଳ ଅକ୍ଷର *ଅଚଳ *text_mime_types;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    ଯଦି (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &ଅଙ୍କ_mime_types);

        ଫେରନ୍ତୁ SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, ଅଙ୍କ_mime_types);
    }
    ଫେରନ୍ତୁ SDL_ClearClipboardData();
}

ଅକ୍ଷର *SDL_GetClipboardText(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ଅଙ୍କ_mime_types;
    ଅଚଳ ଅକ୍ଷର *ଅଚଳ *text_mime_types;
    size_t length;
    ଅକ୍ଷର *text = ଖାଲି;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &ଅଙ୍କ_mime_types);
    ପାଇଁ (i = 0; i < ଅଙ୍କ_mime_types; ++i) {
        ଶୂନ୍ୟ *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        ଯଦି (clipdata) {
            text = (ଅକ୍ଷର *)clipdata;
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (!text) {
        text = SDL_strdup("");
    }
    ଫେରନ୍ତୁ text;
}

bool SDL_HasClipboardText(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ଅଙ୍କ_mime_types;
    ଅଚଳ ଅକ୍ଷର *ଅଚଳ *text_mime_types;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &ଅଙ୍କ_mime_types);
    ପାଇଁ (i = 0; i < ଅଙ୍କ_mime_types; ++i) {
        ଯଦି (SDL_HasClipboardData(text_mime_types[i])) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ଅଚଳ ଅକ୍ଷର *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    ଯଦି (!text) {
        text = "";
    }
    ଯଦି (_this->SetPrimarySelectionText) {
        ଯଦି (!_this->SetPrimarySelectionText(_this, text)) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    ଅକ୍ଷର **mime_types = SDL_CopyClipboardMimeTypes((ଅଚଳ ଅକ୍ଷର **)_this->clipboard_mime_types, _this->ଅଙ୍କ_clipboard_mime_types, true);
    ଯଦି (!mime_types) {
        ଫେରନ୍ତୁ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->ଅଙ୍କ_clipboard_mime_types);
    ଫେରନ୍ତୁ true;
}

ଅକ୍ଷର *SDL_GetPrimarySelectionText(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ SDL_strdup("");
    }

    ଯଦି (_this->GetPrimarySelectionText) {
        ଫେରନ୍ତୁ _this->GetPrimarySelectionText(_this);
    } ଅନ୍ୟଥା {
        ଅଚଳ ଅକ୍ଷର *text = _this->primary_selection_text;
        ଯଦି (!text) {
            text = "";
        }
        ଫେରନ୍ତୁ SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    ଯଦି (_this->HasPrimarySelectionText) {
        ଫେରନ୍ତୁ _this->HasPrimarySelectionText(_this);
    } ଅନ୍ୟଥା {
        ଯଦି (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ଫେରନ୍ତୁ true;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ false;
        }
    }
}

