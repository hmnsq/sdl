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
    ಆದರೆ (_this->clipboard_mime_types) {
        ಗಾಗಿ (size_t i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ಖಾಲಿ;
        _this->ಅಂಕೆ_clipboard_mime_types = 0;
    }
}


ಶೂನ್ಯ SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ಖಾಲಿ;
    _this->clipboard_cleanup = ಖಾಲಿ;
    _this->clipboard_userdata = ಖಾಲಿ;
}

bool SDL_SaveClipboardMimeTypes(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types, size_t ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ಆದರೆ (mime_types && ಅಂಕೆ_mime_types > 0) {
        size_t ಅಂಕೆ_allocated = 0;

        _this->clipboard_mime_types = (ಅಕ್ಷರ **)SDL_malloc(ಅಂಕೆ_mime_types * ಗಾತ್ರ(ಅಕ್ಷರ *));
        ಆದರೆ (_this->clipboard_mime_types) {
            ಗಾಗಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ಆದರೆ (_this->clipboard_mime_types[i]) {
                    ++ಅಂಕೆ_allocated;
                }
            }
        }
        ಆದರೆ (ಅಂಕೆ_allocated < ಅಂಕೆ_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ಹಿಂತಿರುಗಿ false;
        }
        _this->ಅಂಕೆ_clipboard_mime_types = ಅಂಕೆ_mime_types;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_Clipboard_ದತ್ತಾಂಶ_Callback callback, SDL_ClipboardCleanupCallback cleanup, ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types, size_t ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    // Parameter validation
    ಆದರೆ (!((callback && mime_types && ಅಂಕೆ_mime_types > 0) ||
          (!callback && !mime_types && ಅಂಕೆ_mime_types == 0))) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(0);

    ++_this->clipboard_sequence;
    ಆದರೆ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ಆದರೆ (!SDL_SaveClipboardMimeTypes(mime_types, ಅಂಕೆ_mime_types)) {
        SDL_Clear_Clipboard_ದತ್ತಾಂಶ();
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (_this->ಗಣ_Clipboard_ದತ್ತಾಂಶ) {
        ಆದರೆ (!_this->ಗಣ_Clipboard_ದತ್ತಾಂಶ(_this)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->ಗಣ_Clipboard_ಪಠ್ಯ) {
        ಅಕ್ಷರ *ಪಠ್ಯ = ಖಾಲಿ;
        size_t ಗಾತ್ರ_2;

        ಗಾಗಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; ++i) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = _this->clipboard_mime_types[i];
            ಆದರೆ (SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &ಗಾತ್ರ_2);
                ಆದರೆ (ದತ್ತಾಂಶ) {
                    ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(ಗಾತ್ರ_2 + 1);
                    SDL_memcpy(ಪಠ್ಯ, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
                    ಪಠ್ಯ[ಗಾತ್ರ_2] = '\0';
                    ಆದರೆ (!_this->ಗಣ_Clipboard_ಪಠ್ಯ(_this, ಪಠ್ಯ)) {
                        SDL_free(ಪಠ್ಯ);
                        ಹಿಂತಿರುಗಿ false;
                    }
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
        ಆದರೆ (ಪಠ್ಯ) {
            SDL_free(ಪಠ್ಯ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (!_this->ಗಣ_Clipboard_ಪಠ್ಯ(_this, "")) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
    }

    ಅಕ್ಷರ **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, ಅಂಕೆ_mime_types, true);
    ಆದರೆ (!mime_types_copy) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, ಅಂಕೆ_mime_types);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Clear_Clipboard_ದತ್ತಾಂಶ(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Clipboard_ದತ್ತಾಂಶ(ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, 0);
}

ಶೂನ್ಯ *SDL_Get_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ದತ್ತಾಂಶ = ಖಾಲಿ;

    ಆದರೆ (_this->clipboard_callback) {
        ಆದರೆ (!SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *provided_ದತ್ತಾಂಶ = _this->clipboard_callback(_this->clipboard_userdata, mime_type, ಗಾತ್ರ_2);
        ಆದರೆ (provided_ದತ್ತಾಂಶ) {
            // Make a copy of it for the caller and guarantee null termination
            ದತ್ತಾಂಶ = SDL_malloc(*ಗಾತ್ರ_2 + ಗಾತ್ರ(Uint32));
            ಆದರೆ (ದತ್ತಾಂಶ) {
                SDL_memcpy(ದತ್ತಾಂಶ, provided_ದತ್ತಾಂಶ, *ಗಾತ್ರ_2);
                SDL_memset((Uint8 *)ದತ್ತಾಂಶ + *ಗಾತ್ರ_2, 0, ಗಾತ್ರ(Uint32));
            } ಇಲ್ಲದಿದ್ದರೆ {
                *ಗಾತ್ರ_2 = 0;
            }
        }
    }
    ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ;
}

ಶೂನ್ಯ *SDL_Get_Clipboard_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ಬಳಸದ;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!ಗಾತ್ರ_2) {
        ಗಾತ್ರ_2 = &ಬಳಸದ;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *ಗಾತ್ರ_2 = 0;

    ಆದರೆ (_this->Get_Clipboard_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ _this->Get_Clipboard_ದತ್ತಾಂಶ(_this, mime_type, ಗಾತ್ರ_2);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->Get_Clipboard_ಪಠ್ಯ && SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
        ಅಕ್ಷರ *ಪಠ್ಯ = _this->Get_Clipboard_ಪಠ್ಯ(_this);
        ಆದರೆ (ಪಠ್ಯ) {
            ಆದರೆ (*ಪಠ್ಯ == '\0') {
                SDL_free(ಪಠ್ಯ);
                ಪಠ್ಯ = ಖಾಲಿ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                *ಗಾತ್ರ_2 = SDL_strlen(ಪಠ್ಯ);
            }
        }
        ಹಿಂತಿರುಗಿ ಪಠ್ಯ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Get_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type, ಗಾತ್ರ_2);
    }
}

bool SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    size_t i;

    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_clipboard_mime_types; ++i) {
        ಆದರೆ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

bool SDL_Has_Clipboard_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("mime_type");
    }

    ಆದರೆ (_this->Has_Clipboard_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ _this->Has_Clipboard_ದತ್ತಾಂಶ(_this, mime_type);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->Has_Clipboard_ಪಠ್ಯ && SDL_Is_ಪಠ್ಯ_Mime_Type(mime_type)) {
        ಹಿಂತಿರುಗಿ _this->Has_Clipboard_ಪಠ್ಯ(_this);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Has_ಆಂತರಿಕ_Clipboard_ದತ್ತಾಂಶ(_this, mime_type);
    }
}

ಅಕ್ಷರ **SDL_CopyClipboardMimeTypes(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *clipboard_mime_types, size_t ಅಂಕೆ_mime_types, bool temporary)
{
    size_t alloc_ಗಾತ್ರ = ಗಾತ್ರ(ಅಕ್ಷರ *);
    ಗಾಗಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; i++) {
        alloc_ಗಾತ್ರ += ಗಾತ್ರ(ಅಕ್ಷರ *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    ಅಕ್ಷರ *ret;
    ಆದರೆ (temporary)
        ret = (ಅಕ್ಷರ *)SDL_Allocate_Temporary_ಸ್ಮರಣೆ(alloc_ಗಾತ್ರ);
    ಇಲ್ಲದಿದ್ದರೆ
        ret = (ಅಕ್ಷರ *)SDL_malloc(alloc_ಗಾತ್ರ);
    ಆದರೆ (!ret) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಅಕ್ಷರ **ಫಲಿತಾಂಶ = (ಅಕ್ಷರ **)ret;
    ret += ಗಾತ್ರ(ಅಕ್ಷರ *) * (ಅಂಕೆ_mime_types + 1);

    ಗಾಗಿ (size_t i = 0; i < ಅಂಕೆ_mime_types; i++) {
        ಫಲಿತಾಂಶ[i] = ret;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        ಅಕ್ಷರ c;
        ಮಾಡು {
            c = *ret++ = *mime_type++;
        } ಆಗ (c != '\0');
    }
    ಫಲಿತಾಂಶ[ಅಂಕೆ_mime_types] = ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;

}

ಅಕ್ಷರ **SDL_GetClipboardMimeTypes(size_t *ಅಂಕೆ_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (ಅಂಕೆ_mime_types) {
        *ಅಂಕೆ_mime_types = 0;
    }

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (ಅಂಕೆ_mime_types) {
        *ಅಂಕೆ_mime_types = _this->ಅಂಕೆ_clipboard_mime_types;
    }
    ಹಿಂತಿರುಗಿ SDL_CopyClipboardMimeTypes((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_Is_ಪಠ್ಯ_Mime_Type(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಹಿಂತಿರುಗಿ (SDL_strncmp(mime_type, "text", 4) == 0);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *SDL_Get_ಪಠ್ಯ_Mime_Types(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types)
{
    ಆದರೆ (_this->Get_ಪಠ್ಯ_Mime_Types) {
        ಹಿಂತಿರುಗಿ _this->Get_ಪಠ್ಯ_Mime_Types(_this, ಅಂಕೆ_mime_types);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ ಪಠ್ಯ_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *ಅಂಕೆ_mime_types = SDL_arraysize(ಪಠ್ಯ_mime_types);
        ಹಿಂತಿರುಗಿ ಪಠ್ಯ_mime_types;
    }
}

ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * SDLCALL SDL_Clipboard_ಪಠ್ಯ_Callback(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2)
{
    ಅಕ್ಷರ *ಪಠ್ಯ = (ಅಕ್ಷರ *)userdata;
    ಆದರೆ (ಪಠ್ಯ) {
        *ಗಾತ್ರ_2 = SDL_strlen(ಪಠ್ಯ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *ಗಾತ್ರ_2 = 0;
    }
    ಹಿಂತಿರುಗಿ ಪಠ್ಯ;
}

bool SDL_ಗಣ_Clipboard_ಪಠ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t ಅಂಕೆ_mime_types;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *ಪಠ್ಯ_mime_types;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಆದರೆ (ಪಠ್ಯ && *ಪಠ್ಯ) {
        ಪಠ್ಯ_mime_types = SDL_Get_ಪಠ್ಯ_Mime_Types(_this, &ಅಂಕೆ_mime_types);

        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Clipboard_ದತ್ತಾಂಶ(SDL_Clipboard_ಪಠ್ಯ_Callback, SDL_free, SDL_strdup(ಪಠ್ಯ), ಪಠ್ಯ_mime_types, ಅಂಕೆ_mime_types);
    }
    ಹಿಂತಿರುಗಿ SDL_Clear_Clipboard_ದತ್ತಾಂಶ();
}

ಅಕ್ಷರ *SDL_Get_Clipboard_ಪಠ್ಯ(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ಅಂಕೆ_mime_types;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *ಪಠ್ಯ_mime_types;
    size_t ಉದ್ದಳತೆ;
    ಅಕ್ಷರ *ಪಠ್ಯ = ಖಾಲಿ;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ SDL_strdup("");
    }

    ಪಠ್ಯ_mime_types = SDL_Get_ಪಠ್ಯ_Mime_Types(_this, &ಅಂಕೆ_mime_types);
    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_mime_types; ++i) {
        ಶೂನ್ಯ *clipdata = SDL_Get_Clipboard_ದತ್ತಾಂಶ(ಪಠ್ಯ_mime_types[i], &ಉದ್ದಳತೆ);
        ಆದರೆ (clipdata) {
            ಪಠ್ಯ = (ಅಕ್ಷರ *)clipdata;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (!ಪಠ್ಯ) {
        ಪಠ್ಯ = SDL_strdup("");
    }
    ಹಿಂತಿರುಗಿ ಪಠ್ಯ;
}

bool SDL_Has_Clipboard_ಪಠ್ಯ(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, ಅಂಕೆ_mime_types;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *ಪಠ್ಯ_mime_types;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಪಠ್ಯ_mime_types = SDL_Get_ಪಠ್ಯ_Mime_Types(_this, &ಅಂಕೆ_mime_types);
    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_mime_types; ++i) {
        ಆದರೆ (SDL_Has_Clipboard_ದತ್ತಾಂಶ(ಪಠ್ಯ_mime_types[i])) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

// Primary selection text

bool SDL_ಗಣ_Primary_Selection_ಪಠ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಆದರೆ (!ಪಠ್ಯ) {
        ಪಠ್ಯ = "";
    }
    ಆದರೆ (_this->ಗಣ_Primary_Selection_ಪಠ್ಯ) {
        ಆದರೆ (!_this->ಗಣ_Primary_Selection_ಪಠ್ಯ(_this, ಪಠ್ಯ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_free(_this->primary_selection_ಪಠ್ಯ);
        _this->primary_selection_ಪಠ್ಯ = SDL_strdup(ಪಠ್ಯ);
    }

    ಅಕ್ಷರ **mime_types = SDL_CopyClipboardMimeTypes((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)_this->clipboard_mime_types, _this->ಅಂಕೆ_clipboard_mime_types, true);
    ಆದರೆ (!mime_types) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->ಅಂಕೆ_clipboard_mime_types);
    ಹಿಂತಿರುಗಿ true;
}

ಅಕ್ಷರ *SDL_Get_Primary_Selection_ಪಠ್ಯ(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ SDL_strdup("");
    }

    ಆದರೆ (_this->Get_Primary_Selection_ಪಠ್ಯ) {
        ಹಿಂತಿರುಗಿ _this->Get_Primary_Selection_ಪಠ್ಯ(_this);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ = _this->primary_selection_ಪಠ್ಯ;
        ಆದರೆ (!ಪಠ್ಯ) {
            ಪಠ್ಯ = "";
        }
        ಹಿಂತಿರುಗಿ SDL_strdup(ಪಠ್ಯ);
    }
}

bool SDL_Has_Primary_Selection_ಪಠ್ಯ(ಶೂನ್ಯ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಆದರೆ (_this->Has_Primary_Selection_ಪಠ್ಯ) {
        ಹಿಂತಿರುಗಿ _this->Has_Primary_Selection_ಪಠ್ಯ(_this);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (_this->primary_selection_ಪಠ್ಯ && _this->primary_selection_ಪಠ್ಯ[0] != '\0') {
            ಹಿಂತಿರುಗಿ true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ false;
        }
    }
}

