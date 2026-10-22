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
    إذا (_this->clipboard_mime_types) {
        لكل (size_t i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = عدم;
        _this->عدد_clipboard_mime_types = 0;
    }
}


فراغ SDL_Cancel_Clipboard_انکڑے(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع;
    }

    إذا (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        أرجع;
    }

    إذا (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = عدم;
    _this->clipboard_cleanup = عدم;
    _this->clipboard_userdata = عدم;
}

bool SDL_SaveClipboardMimeTypes(ثابت حرف *ثابت *mime_types, size_t عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    إذا (mime_types && عدد_mime_types > 0) {
        size_t عدد_allocated = 0;

        _this->clipboard_mime_types = (حرف **)SDL_malloc(عدد_mime_types * حجم(حرف *));
        إذا (_this->clipboard_mime_types) {
            لكل (size_t i = 0; i < عدد_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                إذا (_this->clipboard_mime_types[i]) {
                    ++عدد_allocated;
                }
            }
        }
        إذا (عدد_allocated < عدد_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            أرجع false;
        }
        _this->عدد_clipboard_mime_types = عدد_mime_types;
    }
    أرجع true;
}

bool SDL_سیٹ_Clipboard_انکڑے(SDL_Clipboard_انکڑے_Callback callback, SDL_ClipboardCleanupCallback cleanup, فراغ *userdata, ثابت حرف *ثابت *mime_types, size_t عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    // Parameter validation
    إذا (!((callback && mime_types && عدد_mime_types > 0) ||
          (!callback && !mime_types && عدد_mime_types == 0))) {
        أرجع SDL_سیٹ_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_انکڑے(0);

    ++_this->clipboard_sequence;
    إذا (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    إذا (!SDL_SaveClipboardMimeTypes(mime_types, عدد_mime_types)) {
        SDL_Clear_Clipboard_انکڑے();
        أرجع false;
    }

    إذا (_this->سیٹ_Clipboard_انکڑے) {
        إذا (!_this->سیٹ_Clipboard_انکڑے(_this)) {
            أرجع false;
        }
    } وإلا إذا (_this->سیٹ_Clipboard_متن) {
        حرف *متن = عدم;
        size_t ناپ;

        لكل (size_t i = 0; i < عدد_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];
            إذا (SDL_Is_متن_Mime_Type(mime_type)) {
                ثابت فراغ *انکڑے = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &ناپ);
                إذا (انکڑے) {
                    متن = (حرف *)SDL_malloc(ناپ + 1);
                    SDL_memcpy(متن, انکڑے, ناپ);
                    متن[ناپ] = '\0';
                    إذا (!_this->سیٹ_Clipboard_متن(_this, متن)) {
                        SDL_free(متن);
                        أرجع false;
                    }
                    اكسر;
                }
            }
        }
        إذا (متن) {
            SDL_free(متن);
        } وإلا {
            إذا (!_this->سیٹ_Clipboard_متن(_this, "")) {
                أرجع false;
            }
        }
    }

    حرف **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, عدد_mime_types, true);
    إذا (!mime_types_copy) {
        أرجع SDL_سیٹ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, عدد_mime_types);
    أرجع true;
}

bool SDL_Clear_Clipboard_انکڑے(فراغ)
{
    أرجع SDL_سیٹ_Clipboard_انکڑے(عدم, عدم, عدم, عدم, 0);
}

فراغ *SDL_Get_اندرونی_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *ناپ)
{
    فراغ *انکڑے = عدم;

    إذا (_this->clipboard_callback) {
        إذا (!SDL_Has_اندرونی_Clipboard_انکڑے(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            أرجع عدم;
        }

        ثابت فراغ *provided_انکڑے = _this->clipboard_callback(_this->clipboard_userdata, mime_type, ناپ);
        إذا (provided_انکڑے) {
            // Make a copy of it for the caller and guarantee null termination
            انکڑے = SDL_malloc(*ناپ + حجم(Uint32));
            إذا (انکڑے) {
                SDL_memcpy(انکڑے, provided_انکڑے, *ناپ);
                SDL_memset((Uint8 *)انکڑے + *ناپ, 0, حجم(Uint32));
            } وإلا {
                *ناپ = 0;
            }
        }
    }
    أرجع انکڑے;
}

فراغ *SDL_Get_Clipboard_انکڑے(ثابت حرف *mime_type, size_t *ناپ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t بن_ورتیا;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        أرجع عدم;
    }
    إذا (!ناپ) {
        ناپ = &بن_ورتیا;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *ناپ = 0;

    إذا (_this->Get_Clipboard_انکڑے) {
        أرجع _this->Get_Clipboard_انکڑے(_this, mime_type, ناپ);
    } وإلا إذا (_this->Get_Clipboard_متن && SDL_Is_متن_Mime_Type(mime_type)) {
        حرف *متن = _this->Get_Clipboard_متن(_this);
        إذا (متن) {
            إذا (*متن == '\0') {
                SDL_free(متن);
                متن = عدم;
            } وإلا {
                *ناپ = SDL_strlen(متن);
            }
        }
        أرجع متن;
    } وإلا {
        أرجع SDL_Get_اندرونی_Clipboard_انکڑے(_this, mime_type, ناپ);
    }
}

bool SDL_Has_اندرونی_Clipboard_انکڑے(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t i;

    لكل (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
        إذا (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            أرجع true;
        }
    }
    أرجع false;
}

bool SDL_Has_Clipboard_انکڑے(ثابت حرف *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        أرجع SDL_InvalidParamError("mime_type");
    }

    إذا (_this->Has_Clipboard_انکڑے) {
        أرجع _this->Has_Clipboard_انکڑے(_this, mime_type);
    } وإلا إذا (_this->Has_Clipboard_متن && SDL_Is_متن_Mime_Type(mime_type)) {
        أرجع _this->Has_Clipboard_متن(_this);
    } وإلا {
        أرجع SDL_Has_اندرونی_Clipboard_انکڑے(_this, mime_type);
    }
}

حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t عدد_mime_types, bool temporary)
{
    size_t alloc_ناپ = حجم(حرف *);
    لكل (size_t i = 0; i < عدد_mime_types; i++) {
        alloc_ناپ += حجم(حرف *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    حرف *ret;
    إذا (temporary)
        ret = (حرف *)SDL_Allocate_Temporary_حافظہ(alloc_ناپ);
    وإلا
        ret = (حرف *)SDL_malloc(alloc_ناپ);
    إذا (!ret) {
        أرجع عدم;
    }

    حرف **نتیجہ = (حرف **)ret;
    ret += حجم(حرف *) * (عدد_mime_types + 1);

    لكل (size_t i = 0; i < عدد_mime_types; i++) {
        نتیجہ[i] = ret;

        ثابت حرف *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        حرف c;
        افعل {
            c = *ret++ = *mime_type++;
        } طالما (c != '\0');
    }
    نتیجہ[عدد_mime_types] = عدم;

    أرجع نتیجہ;

}

حرف **SDL_GetClipboardMimeTypes(size_t *عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (عدد_mime_types) {
        *عدد_mime_types = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    إذا (عدد_mime_types) {
        *عدد_mime_types = _this->عدد_clipboard_mime_types;
    }
    أرجع SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_Is_متن_Mime_Type(ثابت حرف *mime_type)
{
    أرجع (SDL_strncmp(mime_type, "text", 4) == 0);
}

ساكن ثابت حرف *ثابت *SDL_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    إذا (_this->Get_متن_Mime_Types) {
        أرجع _this->Get_متن_Mime_Types(_this, عدد_mime_types);
    } وإلا {
        ساكن ثابت حرف *ثابت متن_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *عدد_mime_types = SDL_arraysize(متن_mime_types);
        أرجع متن_mime_types;
    }
}

ثابت فراغ * SDLCALL SDL_Clipboard_متن_Callback(فراغ *userdata, ثابت حرف *mime_type, size_t *ناپ)
{
    حرف *متن = (حرف *)userdata;
    إذا (متن) {
        *ناپ = SDL_strlen(متن);
    } وإلا {
        *ناپ = 0;
    }
    أرجع متن;
}

bool SDL_سیٹ_Clipboard_متن(ثابت حرف *متن)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (متن && *متن) {
        متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);

        أرجع SDL_سیٹ_Clipboard_انکڑے(SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن), متن_mime_types, عدد_mime_types);
    }
    أرجع SDL_Clear_Clipboard_انکڑے();
}

حرف *SDL_Get_Clipboard_متن(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;
    size_t لمائی;
    حرف *متن = عدم;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع SDL_strdup("");
    }

    متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);
    لكل (i = 0; i < عدد_mime_types; ++i) {
        فراغ *clipdata = SDL_Get_Clipboard_انکڑے(متن_mime_types[i], &لمائی);
        إذا (clipdata) {
            متن = (حرف *)clipdata;
            اكسر;
        }
    }

    إذا (!متن) {
        متن = SDL_strdup("");
    }
    أرجع متن;
}

bool SDL_Has_Clipboard_متن(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);
    لكل (i = 0; i < عدد_mime_types; ++i) {
        إذا (SDL_Has_Clipboard_انکڑے(متن_mime_types[i])) {
            أرجع true;
        }
    }
    أرجع false;
}

// Primary selection text

bool SDL_سیٹ_Primary_Selection_متن(ثابت حرف *متن)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (!متن) {
        متن = "";
    }
    إذا (_this->سیٹ_Primary_Selection_متن) {
        إذا (!_this->سیٹ_Primary_Selection_متن(_this, متن)) {
            أرجع false;
        }
    } وإلا {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = SDL_strdup(متن);
    }

    حرف **mime_types = SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types, true);
    إذا (!mime_types) {
        أرجع SDL_سیٹ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->عدد_clipboard_mime_types);
    أرجع true;
}

حرف *SDL_Get_Primary_Selection_متن(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع SDL_strdup("");
    }

    إذا (_this->Get_Primary_Selection_متن) {
        أرجع _this->Get_Primary_Selection_متن(_this);
    } وإلا {
        ثابت حرف *متن = _this->primary_selection_متن;
        إذا (!متن) {
            متن = "";
        }
        أرجع SDL_strdup(متن);
    }
}

bool SDL_Has_Primary_Selection_متن(فراغ)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (_this->Has_Primary_Selection_متن) {
        أرجع _this->Has_Primary_Selection_متن(_this);
    } وإلا {
        إذا (_this->primary_selection_متن && _this->primary_selection_متن[0] != '\0') {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
}

