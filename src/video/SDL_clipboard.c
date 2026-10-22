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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_clipboard_c.h"
#અન્તર્ભાવ "SDL_sysvideo.h"
#અન્તર્ભાવ "../events/SDL_events_c.h"
#અન્તર્ભાવ "../events/SDL_clipboardevents_c.h"

શૂન્ય SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    જો (_this->clipboard_mime_types) {
        માટે (size_t i = 0; i < _this->અંક_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ખાલી;
        _this->અંક_clipboard_mime_types = 0;
    }
}


શૂન્ય SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા;
    }

    જો (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        પાછા;
    }

    જો (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ખાલી;
    _this->clipboard_cleanup = ખાલી;
    _this->clipboard_userdata = ખાલી;
}

bool SDL_SaveClipboardMimeTypes(અચલ અક્ષર *અચલ *mime_types, size_t અંક_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    જો (mime_types && અંક_mime_types > 0) {
        size_t અંક_allocated = 0;

        _this->clipboard_mime_types = (અક્ષર **)SDL_malloc(અંક_mime_types * કદ(અક્ષર *));
        જો (_this->clipboard_mime_types) {
            માટે (size_t i = 0; i < અંક_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                જો (_this->clipboard_mime_types[i]) {
                    ++અંક_allocated;
                }
            }
        }
        જો (અંક_allocated < અંક_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            પાછા false;
        }
        _this->અંક_clipboard_mime_types = અંક_mime_types;
    }
    પાછા true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, શૂન્ય *userdata, અચલ અક્ષર *અચલ *mime_types, size_t અંક_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    // Parameter validation
    જો (!((callback && mime_types && અંક_mime_types > 0) ||
          (!callback && !mime_types && અંક_mime_types == 0))) {
        પાછા SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    જો (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    જો (!SDL_SaveClipboardMimeTypes(mime_types, અંક_mime_types)) {
        SDL_ClearClipboardData();
        પાછા false;
    }

    જો (_this->SetClipboardData) {
        જો (!_this->SetClipboardData(_this)) {
            પાછા false;
        }
    } નહીંતર જો (_this->SetClipboardText) {
        અક્ષર *text = ખાલી;
        size_t size;

        માટે (size_t i = 0; i < અંક_mime_types; ++i) {
            અચલ અક્ષર *mime_type = _this->clipboard_mime_types[i];
            જો (SDL_IsTextMimeType(mime_type)) {
                અચલ શૂન્ય *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                જો (data) {
                    text = (અક્ષર *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    જો (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        પાછા false;
                    }
                    તોડો;
                }
            }
        }
        જો (text) {
            SDL_free(text);
        } નહીંતર {
            જો (!_this->SetClipboardText(_this, "")) {
                પાછા false;
            }
        }
    }

    અક્ષર **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, અંક_mime_types, true);
    જો (!mime_types_copy) {
        પાછા SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, અંક_mime_types);
    પાછા true;
}

bool SDL_ClearClipboardData(શૂન્ય)
{
    પાછા SDL_SetClipboardData(ખાલી, ખાલી, ખાલી, ખાલી, 0);
}

શૂન્ય *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *size)
{
    શૂન્ય *data = ખાલી;

    જો (_this->clipboard_callback) {
        જો (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            પાછા ખાલી;
        }

        અચલ શૂન્ય *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        જો (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + કદ(Uint32));
            જો (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, કદ(Uint32));
            } નહીંતર {
                *size = 0;
            }
        }
    }
    પાછા data;
}

શૂન્ય *SDL_GetClipboardData(અચલ અક્ષર *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        પાછા ખાલી;
    }
    જો (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    જો (_this->GetClipboardData) {
        પાછા _this->GetClipboardData(_this, mime_type, size);
    } નહીંતર જો (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        અક્ષર *text = _this->GetClipboardText(_this);
        જો (text) {
            જો (*text == '\0') {
                SDL_free(text);
                text = ખાલી;
            } નહીંતર {
                *size = SDL_strlen(text);
            }
        }
        પાછા text;
    } નહીંતર {
        પાછા SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type)
{
    size_t i;

    માટે (i = 0; i < _this->અંક_clipboard_mime_types; ++i) {
        જો (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            પાછા true;
        }
    }
    પાછા false;
}

bool SDL_HasClipboardData(અચલ અક્ષર *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        પાછા SDL_InvalidParamError("mime_type");
    }

    જો (_this->HasClipboardData) {
        પાછા _this->HasClipboardData(_this, mime_type);
    } નહીંતર જો (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        પાછા _this->HasClipboardText(_this);
    } નહીંતર {
        પાછા SDL_HasInternalClipboardData(_this, mime_type);
    }
}

અક્ષર **SDL_CopyClipboardMimeTypes(અચલ અક્ષર *અચલ *clipboard_mime_types, size_t અંક_mime_types, bool temporary)
{
    size_t allocSize = કદ(અક્ષર *);
    માટે (size_t i = 0; i < અંક_mime_types; i++) {
        allocSize += કદ(અક્ષર *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    અક્ષર *ret;
    જો (temporary)
        ret = (અક્ષર *)SDL_AllocateTemporaryMemory(allocSize);
    નહીંતર
        ret = (અક્ષર *)SDL_malloc(allocSize);
    જો (!ret) {
        પાછા ખાલી;
    }

    અક્ષર **result = (અક્ષર **)ret;
    ret += કદ(અક્ષર *) * (અંક_mime_types + 1);

    માટે (size_t i = 0; i < અંક_mime_types; i++) {
        result[i] = ret;

        અચલ અક્ષર *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        અક્ષર c;
        કરો {
            c = *ret++ = *mime_type++;
        } જ્યારે (c != '\0');
    }
    result[અંક_mime_types] = ખાલી;

    પાછા result;

}

અક્ષર **SDL_GetClipboardMimeTypes(size_t *અંક_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (અંક_mime_types) {
        *અંક_mime_types = 0;
    }

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }

    જો (અંક_mime_types) {
        *અંક_mime_types = _this->અંક_clipboard_mime_types;
    }
    પાછા SDL_CopyClipboardMimeTypes((અચલ અક્ષર **)_this->clipboard_mime_types, _this->અંક_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(અચલ અક્ષર *mime_type)
{
    પાછા (SDL_strncmp(mime_type, "text", 4) == 0);
}

સ્થિર અચલ અક્ષર *અચલ *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *અંક_mime_types)
{
    જો (_this->GetTextMimeTypes) {
        પાછા _this->GetTextMimeTypes(_this, અંક_mime_types);
    } નહીંતર {
        સ્થિર અચલ અક્ષર *અચલ text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *અંક_mime_types = SDL_arraysize(text_mime_types);
        પાછા text_mime_types;
    }
}

અચલ શૂન્ય * SDLCALL SDL_ClipboardTextCallback(શૂન્ય *userdata, અચલ અક્ષર *mime_type, size_t *size)
{
    અક્ષર *text = (અક્ષર *)userdata;
    જો (text) {
        *size = SDL_strlen(text);
    } નહીંતર {
        *size = 0;
    }
    પાછા text;
}

bool SDL_SetClipboardText(અચલ અક્ષર *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t અંક_mime_types;
    અચલ અક્ષર *અચલ *text_mime_types;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    જો (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &અંક_mime_types);

        પાછા SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, અંક_mime_types);
    }
    પાછા SDL_ClearClipboardData();
}

અક્ષર *SDL_GetClipboardText(શૂન્ય)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, અંક_mime_types;
    અચલ અક્ષર *અચલ *text_mime_types;
    size_t length;
    અક્ષર *text = ખાલી;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &અંક_mime_types);
    માટે (i = 0; i < અંક_mime_types; ++i) {
        શૂન્ય *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        જો (clipdata) {
            text = (અક્ષર *)clipdata;
            તોડો;
        }
    }

    જો (!text) {
        text = SDL_strdup("");
    }
    પાછા text;
}

bool SDL_HasClipboardText(શૂન્ય)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, અંક_mime_types;
    અચલ અક્ષર *અચલ *text_mime_types;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &અંક_mime_types);
    માટે (i = 0; i < અંક_mime_types; ++i) {
        જો (SDL_HasClipboardData(text_mime_types[i])) {
            પાછા true;
        }
    }
    પાછા false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(અચલ અક્ષર *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    જો (!text) {
        text = "";
    }
    જો (_this->SetPrimarySelectionText) {
        જો (!_this->SetPrimarySelectionText(_this, text)) {
            પાછા false;
        }
    } નહીંતર {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    અક્ષર **mime_types = SDL_CopyClipboardMimeTypes((અચલ અક્ષર **)_this->clipboard_mime_types, _this->અંક_clipboard_mime_types, true);
    જો (!mime_types) {
        પાછા SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->અંક_clipboard_mime_types);
    પાછા true;
}

અક્ષર *SDL_GetPrimarySelectionText(શૂન્ય)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા SDL_strdup("");
    }

    જો (_this->GetPrimarySelectionText) {
        પાછા _this->GetPrimarySelectionText(_this);
    } નહીંતર {
        અચલ અક્ષર *text = _this->primary_selection_text;
        જો (!text) {
            text = "";
        }
        પાછા SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(શૂન્ય)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    જો (_this->HasPrimarySelectionText) {
        પાછા _this->HasPrimarySelectionText(_this);
    } નહીંતર {
        જો (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            પાછા true;
        } નહીંતર {
            પાછા false;
        }
    }
}

