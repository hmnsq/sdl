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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../events/SDL_clipboardevents_c.h"

ਖਾਲੀ SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    ਜੇ (_this->clipboard_mime_types) {
        ਲਈ (size_t i = 0; i < _this->ਅੰਕ_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ਨਿਰਾ;
        _this->ਅੰਕ_clipboard_mime_types = 0;
    }
}


ਖਾਲੀ SDL_Cancel_Clipboard_ਅੰਕੜੇ(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ;
    }

    ਜੇ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ਵਾਪਸ;
    }

    ਜੇ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ਨਿਰਾ;
    _this->clipboard_cleanup = ਨਿਰਾ;
    _this->clipboard_userdata = ਨਿਰਾ;
}

bool SDL_SaveClipboardMimeTypes(ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t ਅੰਕ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ਜੇ (mime_types && ਅੰਕ_mime_types > 0) {
        size_t ਅੰਕ_allocated = 0;

        _this->clipboard_mime_types = (ਅੱਖਰ **)SDL_malloc(ਅੰਕ_mime_types * ਆਕਾਰ(ਅੱਖਰ *));
        ਜੇ (_this->clipboard_mime_types) {
            ਲਈ (size_t i = 0; i < ਅੰਕ_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ਜੇ (_this->clipboard_mime_types[i]) {
                    ++ਅੰਕ_allocated;
                }
            }
        }
        ਜੇ (ਅੰਕ_allocated < ਅੰਕ_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ਵਾਪਸ false;
        }
        _this->ਅੰਕ_clipboard_mime_types = ਅੰਕ_mime_types;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(SDL_Clipboard_ਅੰਕੜੇ_Callback callback, SDL_ClipboardCleanupCallback cleanup, ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t ਅੰਕ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    // Parameter validation
    ਜੇ (!((callback && mime_types && ਅੰਕ_mime_types > 0) ||
          (!callback && !mime_types && ਅੰਕ_mime_types == 0))) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_ਅੰਕੜੇ(0);

    ++_this->clipboard_sequence;
    ਜੇ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ਜੇ (!SDL_SaveClipboardMimeTypes(mime_types, ਅੰਕ_mime_types)) {
        SDL_Clear_Clipboard_ਅੰਕੜੇ();
        ਵਾਪਸ false;
    }

    ਜੇ (_this->ਸੈੱਟ_Clipboard_ਅੰਕੜੇ) {
        ਜੇ (!_this->ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(_this)) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (_this->ਸੈੱਟ_Clipboard_ਪਾਠ) {
        ਅੱਖਰ *ਪਾਠ = ਨਿਰਾ;
        size_t ਮਾਪ;

        ਲਈ (size_t i = 0; i < ਅੰਕ_mime_types; ++i) {
            ਅਚਲ ਅੱਖਰ *mime_type = _this->clipboard_mime_types[i];
            ਜੇ (SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
                ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &ਮਾਪ);
                ਜੇ (ਅੰਕੜੇ) {
                    ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(ਮਾਪ + 1);
                    SDL_memcpy(ਪਾਠ, ਅੰਕੜੇ, ਮਾਪ);
                    ਪਾਠ[ਮਾਪ] = '\0';
                    ਜੇ (!_this->ਸੈੱਟ_Clipboard_ਪਾਠ(_this, ਪਾਠ)) {
                        SDL_free(ਪਾਠ);
                        ਵਾਪਸ false;
                    }
                    ਰੋਕੋ;
                }
            }
        }
        ਜੇ (ਪਾਠ) {
            SDL_free(ਪਾਠ);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (!_this->ਸੈੱਟ_Clipboard_ਪਾਠ(_this, "")) {
                ਵਾਪਸ false;
            }
        }
    }

    ਅੱਖਰ **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, ਅੰਕ_mime_types, true);
    ਜੇ (!mime_types_copy) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, ਅੰਕ_mime_types);
    ਵਾਪਸ true;
}

bool SDL_Clear_Clipboard_ਅੰਕੜੇ(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, 0);
}

ਖਾਲੀ *SDL_Get_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ)
{
    ਖਾਲੀ *ਅੰਕੜੇ = ਨਿਰਾ;

    ਜੇ (_this->clipboard_callback) {
        ਜੇ (!SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਅਚਲ ਖਾਲੀ *provided_ਅੰਕੜੇ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, ਮਾਪ);
        ਜੇ (provided_ਅੰਕੜੇ) {
            // Make a copy of it for the caller and guarantee null termination
            ਅੰਕੜੇ = SDL_malloc(*ਮਾਪ + ਆਕਾਰ(Uint32));
            ਜੇ (ਅੰਕੜੇ) {
                SDL_memcpy(ਅੰਕੜੇ, provided_ਅੰਕੜੇ, *ਮਾਪ);
                SDL_memset((Uint8 *)ਅੰਕੜੇ + *ਮਾਪ, 0, ਆਕਾਰ(Uint32));
            } ਨਹੀਂਤਾਂ {
                *ਮਾਪ = 0;
            }
        }
    }
    ਵਾਪਸ ਅੰਕੜੇ;
}

ਖਾਲੀ *SDL_Get_Clipboard_ਅੰਕੜੇ(ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ਅਣਵਰਤਿਆ;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!ਮਾਪ) {
        ਮਾਪ = &ਅਣਵਰਤਿਆ;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *ਮਾਪ = 0;

    ਜੇ (_this->Get_Clipboard_ਅੰਕੜੇ) {
        ਵਾਪਸ _this->Get_Clipboard_ਅੰਕੜੇ(_this, mime_type, ਮਾਪ);
    } ਨਹੀਂਤਾਂ ਜੇ (_this->Get_Clipboard_ਪਾਠ && SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
        ਅੱਖਰ *ਪਾਠ = _this->Get_Clipboard_ਪਾਠ(_this);
        ਜੇ (ਪਾਠ) {
            ਜੇ (*ਪਾਠ == '\0') {
                SDL_free(ਪਾਠ);
                ਪਾਠ = ਨਿਰਾ;
            } ਨਹੀਂਤਾਂ {
                *ਮਾਪ = SDL_strlen(ਪਾਠ);
            }
        }
        ਵਾਪਸ ਪਾਠ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Get_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type, ਮਾਪ);
    }
}

bool SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type)
{
    size_t i;

    ਲਈ (i = 0; i < _this->ਅੰਕ_clipboard_mime_types; ++i) {
        ਜੇ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

bool SDL_Has_Clipboard_ਅੰਕੜੇ(ਅਚਲ ਅੱਖਰ *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ਵਾਪਸ SDL_InvalidParamError("mime_type");
    }

    ਜੇ (_this->Has_Clipboard_ਅੰਕੜੇ) {
        ਵਾਪਸ _this->Has_Clipboard_ਅੰਕੜੇ(_this, mime_type);
    } ਨਹੀਂਤਾਂ ਜੇ (_this->Has_Clipboard_ਪਾਠ && SDL_Is_ਪਾਠ_Mime_Type(mime_type)) {
        ਵਾਪਸ _this->Has_Clipboard_ਪਾਠ(_this);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Has_ਅੰਦਰੂਨੀ_Clipboard_ਅੰਕੜੇ(_this, mime_type);
    }
}

ਅੱਖਰ **SDL_CopyClipboardMimeTypes(ਅਚਲ ਅੱਖਰ *ਅਚਲ *clipboard_mime_types, size_t ਅੰਕ_mime_types, bool temporary)
{
    size_t alloc_ਮਾਪ = ਆਕਾਰ(ਅੱਖਰ *);
    ਲਈ (size_t i = 0; i < ਅੰਕ_mime_types; i++) {
        alloc_ਮਾਪ += ਆਕਾਰ(ਅੱਖਰ *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    ਅੱਖਰ *ret;
    ਜੇ (temporary)
        ret = (ਅੱਖਰ *)SDL_Allocate_Temporary_ਸਮ੍ਰਿਤੀ(alloc_ਮਾਪ);
    ਨਹੀਂਤਾਂ
        ret = (ਅੱਖਰ *)SDL_malloc(alloc_ਮਾਪ);
    ਜੇ (!ret) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੱਖਰ **ਨਤੀਜਾ = (ਅੱਖਰ **)ret;
    ret += ਆਕਾਰ(ਅੱਖਰ *) * (ਅੰਕ_mime_types + 1);

    ਲਈ (size_t i = 0; i < ਅੰਕ_mime_types; i++) {
        ਨਤੀਜਾ[i] = ret;

        ਅਚਲ ਅੱਖਰ *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        ਅੱਖਰ c;
        ਕਰੋ {
            c = *ret++ = *mime_type++;
        } ਜਦੋਂ (c != '\0');
    }
    ਨਤੀਜਾ[ਅੰਕ_mime_types] = ਨਿਰਾ;

    ਵਾਪਸ ਨਤੀਜਾ;

}

ਅੱਖਰ **SDL_GetClipboardMimeTypes(size_t *ਅੰਕ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (ਅੰਕ_mime_types) {
        *ਅੰਕ_mime_types = 0;
    }

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕ_mime_types) {
        *ਅੰਕ_mime_types = _this->ਅੰਕ_clipboard_mime_types;
    }
    ਵਾਪਸ SDL_CopyClipboardMimeTypes((ਅਚਲ ਅੱਖਰ **)_this->clipboard_mime_types, _this->ਅੰਕ_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_Is_ਪਾਠ_Mime_Type(ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਵਾਪਸ (SDL_strncmp(mime_type, "text", 4) == 0);
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ *SDL_Get_ਪਾਠ_Mime_Types(SDL_VideoDevice *_this, size_t *ਅੰਕ_mime_types)
{
    ਜੇ (_this->Get_ਪਾਠ_Mime_Types) {
        ਵਾਪਸ _this->Get_ਪਾਠ_Mime_Types(_this, ਅੰਕ_mime_types);
    } ਨਹੀਂਤਾਂ {
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ ਪਾਠ_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *ਅੰਕ_mime_types = SDL_arraysize(ਪਾਠ_mime_types);
        ਵਾਪਸ ਪਾਠ_mime_types;
    }
}

ਅਚਲ ਖਾਲੀ * SDLCALL SDL_Clipboard_ਪਾਠ_Callback(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ)
{
    ਅੱਖਰ *ਪਾਠ = (ਅੱਖਰ *)userdata;
    ਜੇ (ਪਾਠ) {
        *ਮਾਪ = SDL_strlen(ਪਾਠ);
    } ਨਹੀਂਤਾਂ {
        *ਮਾਪ = 0;
    }
    ਵਾਪਸ ਪਾਠ;
}

bool SDL_ਸੈੱਟ_Clipboard_ਪਾਠ(ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ਅੰਕ_mime_types;
    ਅਚਲ ਅੱਖਰ *ਅਚਲ *ਪਾਠ_mime_types;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਜੇ (ਪਾਠ && *ਪਾਠ) {
        ਪਾਠ_mime_types = SDL_Get_ਪਾਠ_Mime_Types(_this, &ਅੰਕ_mime_types);

        ਵਾਪਸ SDL_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ(SDL_Clipboard_ਪਾਠ_Callback, SDL_free, SDL_strdup(ਪਾਠ), ਪਾਠ_mime_types, ਅੰਕ_mime_types);
    }
    ਵਾਪਸ SDL_Clear_Clipboard_ਅੰਕੜੇ();
}

ਅੱਖਰ *SDL_Get_Clipboard_ਪਾਠ(ਖਾਲੀ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ਅੰਕ_mime_types;
    ਅਚਲ ਅੱਖਰ *ਅਚਲ *ਪਾਠ_mime_types;
    size_t ਲੰਮਾਈ;
    ਅੱਖਰ *ਪਾਠ = ਨਿਰਾ;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ SDL_strdup("");
    }

    ਪਾਠ_mime_types = SDL_Get_ਪਾਠ_Mime_Types(_this, &ਅੰਕ_mime_types);
    ਲਈ (i = 0; i < ਅੰਕ_mime_types; ++i) {
        ਖਾਲੀ *clipdata = SDL_Get_Clipboard_ਅੰਕੜੇ(ਪਾਠ_mime_types[i], &ਲੰਮਾਈ);
        ਜੇ (clipdata) {
            ਪਾਠ = (ਅੱਖਰ *)clipdata;
            ਰੋਕੋ;
        }
    }

    ਜੇ (!ਪਾਠ) {
        ਪਾਠ = SDL_strdup("");
    }
    ਵਾਪਸ ਪਾਠ;
}

bool SDL_Has_Clipboard_ਪਾਠ(ਖਾਲੀ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ਅੰਕ_mime_types;
    ਅਚਲ ਅੱਖਰ *ਅਚਲ *ਪਾਠ_mime_types;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਪਾਠ_mime_types = SDL_Get_ਪਾਠ_Mime_Types(_this, &ਅੰਕ_mime_types);
    ਲਈ (i = 0; i < ਅੰਕ_mime_types; ++i) {
        ਜੇ (SDL_Has_Clipboard_ਅੰਕੜੇ(ਪਾਠ_mime_types[i])) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

// Primary selection text

bool SDL_ਸੈੱਟ_Primary_Selection_ਪਾਠ(ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਜੇ (!ਪਾਠ) {
        ਪਾਠ = "";
    }
    ਜੇ (_this->ਸੈੱਟ_Primary_Selection_ਪਾਠ) {
        ਜੇ (!_this->ਸੈੱਟ_Primary_Selection_ਪਾਠ(_this, ਪਾਠ)) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        SDL_free(_this->primary_selection_ਪਾਠ);
        _this->primary_selection_ਪਾਠ = SDL_strdup(ਪਾਠ);
    }

    ਅੱਖਰ **mime_types = SDL_CopyClipboardMimeTypes((ਅਚਲ ਅੱਖਰ **)_this->clipboard_mime_types, _this->ਅੰਕ_clipboard_mime_types, true);
    ਜੇ (!mime_types) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->ਅੰਕ_clipboard_mime_types);
    ਵਾਪਸ true;
}

ਅੱਖਰ *SDL_Get_Primary_Selection_ਪਾਠ(ਖਾਲੀ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ SDL_strdup("");
    }

    ਜੇ (_this->Get_Primary_Selection_ਪਾਠ) {
        ਵਾਪਸ _this->Get_Primary_Selection_ਪਾਠ(_this);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਅੱਖਰ *ਪਾਠ = _this->primary_selection_ਪਾਠ;
        ਜੇ (!ਪਾਠ) {
            ਪਾਠ = "";
        }
        ਵਾਪਸ SDL_strdup(ਪਾਠ);
    }
}

bool SDL_Has_Primary_Selection_ਪਾਠ(ਖਾਲੀ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਜੇ (_this->Has_Primary_Selection_ਪਾਠ) {
        ਵਾਪਸ _this->Has_Primary_Selection_ਪਾਠ(_this);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (_this->primary_selection_ਪਾਠ && _this->primary_selection_ਪਾਠ[0] != '\0') {
            ਵਾਪਸ true;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ false;
        }
    }
}

