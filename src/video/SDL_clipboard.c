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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_clipboard_c.h"
#അന്തര്ഭാവ "SDL_sysvideo.h"
#അന്തര്ഭാവ "../events/SDL_events_c.h"
#അന്തര്ഭാവ "../events/SDL_clipboardevents_c.h"

ശൂന്യം SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->clipboard_mime_types) {
        വേണ്ടി (size_t i = 0; i < _this->അക്കം_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ശൂന്യ;
        _this->അക്കം_clipboard_mime_types = 0;
    }
}


ശൂന്യം SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ;
    }

    എങ്കിൽ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        തിരികെ;
    }

    എങ്കിൽ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ശൂന്യ;
    _this->clipboard_cleanup = ശൂന്യ;
    _this->clipboard_userdata = ശൂന്യ;
}

bool SDL_SaveClipboardMimeTypes(സ്ഥിരം അക്ഷരം *സ്ഥിരം *mime_types, size_t അക്കം_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    എങ്കിൽ (mime_types && അക്കം_mime_types > 0) {
        size_t അക്കം_allocated = 0;

        _this->clipboard_mime_types = (അക്ഷരം **)SDL_malloc(അക്കം_mime_types * വലുപ്പം(അക്ഷരം *));
        എങ്കിൽ (_this->clipboard_mime_types) {
            വേണ്ടി (size_t i = 0; i < അക്കം_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                എങ്കിൽ (_this->clipboard_mime_types[i]) {
                    ++അക്കം_allocated;
                }
            }
        }
        എങ്കിൽ (അക്കം_allocated < അക്കം_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            തിരികെ false;
        }
        _this->അക്കം_clipboard_mime_types = അക്കം_mime_types;
    }
    തിരികെ true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *സ്ഥിരം *mime_types, size_t അക്കം_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    // Parameter validation
    എങ്കിൽ (!((callback && mime_types && അക്കം_mime_types > 0) ||
          (!callback && !mime_types && അക്കം_mime_types == 0))) {
        തിരികെ SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    എങ്കിൽ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    എങ്കിൽ (!SDL_SaveClipboardMimeTypes(mime_types, അക്കം_mime_types)) {
        SDL_ClearClipboardData();
        തിരികെ false;
    }

    എങ്കിൽ (_this->SetClipboardData) {
        എങ്കിൽ (!_this->SetClipboardData(_this)) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->SetClipboardText) {
        അക്ഷരം *text = ശൂന്യ;
        size_t size;

        വേണ്ടി (size_t i = 0; i < അക്കം_mime_types; ++i) {
            സ്ഥിരം അക്ഷരം *mime_type = _this->clipboard_mime_types[i];
            എങ്കിൽ (SDL_IsTextMimeType(mime_type)) {
                സ്ഥിരം ശൂന്യം *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                എങ്കിൽ (data) {
                    text = (അക്ഷരം *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    എങ്കിൽ (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        തിരികെ false;
                    }
                    നിർത്തുക;
                }
            }
        }
        എങ്കിൽ (text) {
            SDL_free(text);
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (!_this->SetClipboardText(_this, "")) {
                തിരികെ false;
            }
        }
    }

    അക്ഷരം **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, അക്കം_mime_types, true);
    എങ്കിൽ (!mime_types_copy) {
        തിരികെ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, അക്കം_mime_types);
    തിരികെ true;
}

bool SDL_ClearClipboardData(ശൂന്യം)
{
    തിരികെ SDL_SetClipboardData(ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, 0);
}

ശൂന്യം *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type, size_t *size)
{
    ശൂന്യം *data = ശൂന്യ;

    എങ്കിൽ (_this->clipboard_callback) {
        എങ്കിൽ (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            തിരികെ ശൂന്യ;
        }

        സ്ഥിരം ശൂന്യം *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        എങ്കിൽ (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + വലുപ്പം(Uint32));
            എങ്കിൽ (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, വലുപ്പം(Uint32));
            } അല്ലെങ്കിൽ {
                *size = 0;
            }
        }
    }
    തിരികെ data;
}

ശൂന്യം *SDL_GetClipboardData(സ്ഥിരം അക്ഷരം *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    എങ്കിൽ (_this->GetClipboardData) {
        തിരികെ _this->GetClipboardData(_this, mime_type, size);
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        അക്ഷരം *text = _this->GetClipboardText(_this);
        എങ്കിൽ (text) {
            എങ്കിൽ (*text == '\0') {
                SDL_free(text);
                text = ശൂന്യ;
            } അല്ലെങ്കിൽ {
                *size = SDL_strlen(text);
            }
        }
        തിരികെ text;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type)
{
    size_t i;

    വേണ്ടി (i = 0; i < _this->അക്കം_clipboard_mime_types; ++i) {
        എങ്കിൽ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

bool SDL_HasClipboardData(സ്ഥിരം അക്ഷരം *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        തിരികെ SDL_InvalidParamError("mime_type");
    }

    എങ്കിൽ (_this->HasClipboardData) {
        തിരികെ _this->HasClipboardData(_this, mime_type);
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        തിരികെ _this->HasClipboardText(_this);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_HasInternalClipboardData(_this, mime_type);
    }
}

അക്ഷരം **SDL_CopyClipboardMimeTypes(സ്ഥിരം അക്ഷരം *സ്ഥിരം *clipboard_mime_types, size_t അക്കം_mime_types, bool temporary)
{
    size_t allocSize = വലുപ്പം(അക്ഷരം *);
    വേണ്ടി (size_t i = 0; i < അക്കം_mime_types; i++) {
        allocSize += വലുപ്പം(അക്ഷരം *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    അക്ഷരം *ret;
    എങ്കിൽ (temporary)
        ret = (അക്ഷരം *)SDL_AllocateTemporaryMemory(allocSize);
    അല്ലെങ്കിൽ
        ret = (അക്ഷരം *)SDL_malloc(allocSize);
    എങ്കിൽ (!ret) {
        തിരികെ ശൂന്യ;
    }

    അക്ഷരം **result = (അക്ഷരം **)ret;
    ret += വലുപ്പം(അക്ഷരം *) * (അക്കം_mime_types + 1);

    വേണ്ടി (size_t i = 0; i < അക്കം_mime_types; i++) {
        result[i] = ret;

        സ്ഥിരം അക്ഷരം *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        അക്ഷരം c;
        ചെയ്യുക {
            c = *ret++ = *mime_type++;
        } ആകുമ്പോൾ (c != '\0');
    }
    result[അക്കം_mime_types] = ശൂന്യ;

    തിരികെ result;

}

അക്ഷരം **SDL_GetClipboardMimeTypes(size_t *അക്കം_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (അക്കം_mime_types) {
        *അക്കം_mime_types = 0;
    }

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (അക്കം_mime_types) {
        *അക്കം_mime_types = _this->അക്കം_clipboard_mime_types;
    }
    തിരികെ SDL_CopyClipboardMimeTypes((സ്ഥിരം അക്ഷരം **)_this->clipboard_mime_types, _this->അക്കം_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(സ്ഥിരം അക്ഷരം *mime_type)
{
    തിരികെ (SDL_strncmp(mime_type, "text", 4) == 0);
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *അക്കം_mime_types)
{
    എങ്കിൽ (_this->GetTextMimeTypes) {
        തിരികെ _this->GetTextMimeTypes(_this, അക്കം_mime_types);
    } അല്ലെങ്കിൽ {
        സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *അക്കം_mime_types = SDL_arraysize(text_mime_types);
        തിരികെ text_mime_types;
    }
}

സ്ഥിരം ശൂന്യം * SDLCALL SDL_ClipboardTextCallback(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *mime_type, size_t *size)
{
    അക്ഷരം *text = (അക്ഷരം *)userdata;
    എങ്കിൽ (text) {
        *size = SDL_strlen(text);
    } അല്ലെങ്കിൽ {
        *size = 0;
    }
    തിരികെ text;
}

bool SDL_SetClipboardText(സ്ഥിരം അക്ഷരം *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t അക്കം_mime_types;
    സ്ഥിരം അക്ഷരം *സ്ഥിരം *text_mime_types;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    എങ്കിൽ (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &അക്കം_mime_types);

        തിരികെ SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, അക്കം_mime_types);
    }
    തിരികെ SDL_ClearClipboardData();
}

അക്ഷരം *SDL_GetClipboardText(ശൂന്യം)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, അക്കം_mime_types;
    സ്ഥിരം അക്ഷരം *സ്ഥിരം *text_mime_types;
    size_t length;
    അക്ഷരം *text = ശൂന്യ;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &അക്കം_mime_types);
    വേണ്ടി (i = 0; i < അക്കം_mime_types; ++i) {
        ശൂന്യം *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        എങ്കിൽ (clipdata) {
            text = (അക്ഷരം *)clipdata;
            നിർത്തുക;
        }
    }

    എങ്കിൽ (!text) {
        text = SDL_strdup("");
    }
    തിരികെ text;
}

bool SDL_HasClipboardText(ശൂന്യം)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, അക്കം_mime_types;
    സ്ഥിരം അക്ഷരം *സ്ഥിരം *text_mime_types;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &അക്കം_mime_types);
    വേണ്ടി (i = 0; i < അക്കം_mime_types; ++i) {
        എങ്കിൽ (SDL_HasClipboardData(text_mime_types[i])) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(സ്ഥിരം അക്ഷരം *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    എങ്കിൽ (!text) {
        text = "";
    }
    എങ്കിൽ (_this->SetPrimarySelectionText) {
        എങ്കിൽ (!_this->SetPrimarySelectionText(_this, text)) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    അക്ഷരം **mime_types = SDL_CopyClipboardMimeTypes((സ്ഥിരം അക്ഷരം **)_this->clipboard_mime_types, _this->അക്കം_clipboard_mime_types, true);
    എങ്കിൽ (!mime_types) {
        തിരികെ SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->അക്കം_clipboard_mime_types);
    തിരികെ true;
}

അക്ഷരം *SDL_GetPrimarySelectionText(ശൂന്യം)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ SDL_strdup("");
    }

    എങ്കിൽ (_this->GetPrimarySelectionText) {
        തിരികെ _this->GetPrimarySelectionText(_this);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം അക്ഷരം *text = _this->primary_selection_text;
        എങ്കിൽ (!text) {
            text = "";
        }
        തിരികെ SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(ശൂന്യം)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    എങ്കിൽ (_this->HasPrimarySelectionText) {
        തിരികെ _this->HasPrimarySelectionText(_this);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            തിരികെ true;
        } അല്ലെങ്കിൽ {
            തിരികെ false;
        }
    }
}

