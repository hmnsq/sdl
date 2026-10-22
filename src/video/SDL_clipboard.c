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

خالی SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    اگر (_this->clipboard_mime_types) {
        برائے (size_t i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = تہی;
        _this->عدد_clipboard_mime_types = 0;
    }
}


خالی SDL_Cancel_Clipboard_ڈیٹا(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس;
    }

    اگر (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        واپس;
    }

    اگر (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = تہی;
    _this->clipboard_cleanup = تہی;
    _this->clipboard_userdata = تہی;
}

bool SDL_SaveClipboardMimeTypes(ثابت حرف *ثابت *mime_types, size_t عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    اگر (mime_types && عدد_mime_types > 0) {
        size_t عدد_allocated = 0;

        _this->clipboard_mime_types = (حرف **)SDL_malloc(عدد_mime_types * حجم(حرف *));
        اگر (_this->clipboard_mime_types) {
            برائے (size_t i = 0; i < عدد_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                اگر (_this->clipboard_mime_types[i]) {
                    ++عدد_allocated;
                }
            }
        }
        اگر (عدد_allocated < عدد_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            واپس false;
        }
        _this->عدد_clipboard_mime_types = عدد_mime_types;
    }
    واپس true;
}

bool SDL_سیٹ_Clipboard_ڈیٹا(SDL_Clipboard_ڈیٹا_Callback callback, SDL_ClipboardCleanupCallback cleanup, خالی *userdata, ثابت حرف *ثابت *mime_types, size_t عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    // Parameter validation
    اگر (!((callback && mime_types && عدد_mime_types > 0) ||
          (!callback && !mime_types && عدد_mime_types == 0))) {
        واپس SDL_سیٹ_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_ڈیٹا(0);

    ++_this->clipboard_sequence;
    اگر (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    اگر (!SDL_SaveClipboardMimeTypes(mime_types, عدد_mime_types)) {
        SDL_Clear_Clipboard_ڈیٹا();
        واپس false;
    }

    اگر (_this->سیٹ_Clipboard_ڈیٹا) {
        اگر (!_this->سیٹ_Clipboard_ڈیٹا(_this)) {
            واپس false;
        }
    } ورنہ اگر (_this->سیٹ_Clipboard_متن) {
        حرف *متن = تہی;
        size_t سائز;

        برائے (size_t i = 0; i < عدد_mime_types; ++i) {
            ثابت حرف *mime_type = _this->clipboard_mime_types[i];
            اگر (SDL_Is_متن_Mime_Type(mime_type)) {
                ثابت خالی *ڈیٹا = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &سائز);
                اگر (ڈیٹا) {
                    متن = (حرف *)SDL_malloc(سائز + 1);
                    SDL_memcpy(متن, ڈیٹا, سائز);
                    متن[سائز] = '\0';
                    اگر (!_this->سیٹ_Clipboard_متن(_this, متن)) {
                        SDL_free(متن);
                        واپس false;
                    }
                    توڑو;
                }
            }
        }
        اگر (متن) {
            SDL_free(متن);
        } ورنہ {
            اگر (!_this->سیٹ_Clipboard_متن(_this, "")) {
                واپس false;
            }
        }
    }

    حرف **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, عدد_mime_types, true);
    اگر (!mime_types_copy) {
        واپس SDL_سیٹ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, عدد_mime_types);
    واپس true;
}

bool SDL_Clear_Clipboard_ڈیٹا(خالی)
{
    واپس SDL_سیٹ_Clipboard_ڈیٹا(تہی, تہی, تہی, تہی, 0);
}

خالی *SDL_Get_اندرونی_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائز)
{
    خالی *ڈیٹا = تہی;

    اگر (_this->clipboard_callback) {
        اگر (!SDL_Has_اندرونی_Clipboard_ڈیٹا(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            واپس تہی;
        }

        ثابت خالی *provided_ڈیٹا = _this->clipboard_callback(_this->clipboard_userdata, mime_type, سائز);
        اگر (provided_ڈیٹا) {
            // Make a copy of it for the caller and guarantee null termination
            ڈیٹا = SDL_malloc(*سائز + حجم(Uint32));
            اگر (ڈیٹا) {
                SDL_memcpy(ڈیٹا, provided_ڈیٹا, *سائز);
                SDL_memset((Uint8 *)ڈیٹا + *سائز, 0, حجم(Uint32));
            } ورنہ {
                *سائز = 0;
            }
        }
    }
    واپس ڈیٹا;
}

خالی *SDL_Get_Clipboard_ڈیٹا(ثابت حرف *mime_type, size_t *سائز)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t غیر_مستعمل;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        واپس تہی;
    }
    اگر (!سائز) {
        سائز = &غیر_مستعمل;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *سائز = 0;

    اگر (_this->Get_Clipboard_ڈیٹا) {
        واپس _this->Get_Clipboard_ڈیٹا(_this, mime_type, سائز);
    } ورنہ اگر (_this->Get_Clipboard_متن && SDL_Is_متن_Mime_Type(mime_type)) {
        حرف *متن = _this->Get_Clipboard_متن(_this);
        اگر (متن) {
            اگر (*متن == '\0') {
                SDL_free(متن);
                متن = تہی;
            } ورنہ {
                *سائز = SDL_strlen(متن);
            }
        }
        واپس متن;
    } ورنہ {
        واپس SDL_Get_اندرونی_Clipboard_ڈیٹا(_this, mime_type, سائز);
    }
}

bool SDL_Has_اندرونی_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type)
{
    size_t i;

    برائے (i = 0; i < _this->عدد_clipboard_mime_types; ++i) {
        اگر (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            واپس true;
        }
    }
    واپس false;
}

bool SDL_Has_Clipboard_ڈیٹا(ثابت حرف *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        واپس SDL_InvalidParamError("mime_type");
    }

    اگر (_this->Has_Clipboard_ڈیٹا) {
        واپس _this->Has_Clipboard_ڈیٹا(_this, mime_type);
    } ورنہ اگر (_this->Has_Clipboard_متن && SDL_Is_متن_Mime_Type(mime_type)) {
        واپس _this->Has_Clipboard_متن(_this);
    } ورنہ {
        واپس SDL_Has_اندرونی_Clipboard_ڈیٹا(_this, mime_type);
    }
}

حرف **SDL_CopyClipboardMimeTypes(ثابت حرف *ثابت *clipboard_mime_types, size_t عدد_mime_types, bool temporary)
{
    size_t alloc_سائز = حجم(حرف *);
    برائے (size_t i = 0; i < عدد_mime_types; i++) {
        alloc_سائز += حجم(حرف *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    حرف *ret;
    اگر (temporary)
        ret = (حرف *)SDL_Allocate_Temporary_حافظہ(alloc_سائز);
    ورنہ
        ret = (حرف *)SDL_malloc(alloc_سائز);
    اگر (!ret) {
        واپس تہی;
    }

    حرف **نتیجہ = (حرف **)ret;
    ret += حجم(حرف *) * (عدد_mime_types + 1);

    برائے (size_t i = 0; i < عدد_mime_types; i++) {
        نتیجہ[i] = ret;

        ثابت حرف *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        حرف c;
        کرو {
            c = *ret++ = *mime_type++;
        } جب (c != '\0');
    }
    نتیجہ[عدد_mime_types] = تہی;

    واپس نتیجہ;

}

حرف **SDL_GetClipboardMimeTypes(size_t *عدد_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (عدد_mime_types) {
        *عدد_mime_types = 0;
    }

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }

    اگر (عدد_mime_types) {
        *عدد_mime_types = _this->عدد_clipboard_mime_types;
    }
    واپس SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_Is_متن_Mime_Type(ثابت حرف *mime_type)
{
    واپس (SDL_strncmp(mime_type, "text", 4) == 0);
}

ساکن ثابت حرف *ثابت *SDL_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types)
{
    اگر (_this->Get_متن_Mime_Types) {
        واپس _this->Get_متن_Mime_Types(_this, عدد_mime_types);
    } ورنہ {
        ساکن ثابت حرف *ثابت متن_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *عدد_mime_types = SDL_arraysize(متن_mime_types);
        واپس متن_mime_types;
    }
}

ثابت خالی * SDLCALL SDL_Clipboard_متن_Callback(خالی *userdata, ثابت حرف *mime_type, size_t *سائز)
{
    حرف *متن = (حرف *)userdata;
    اگر (متن) {
        *سائز = SDL_strlen(متن);
    } ورنہ {
        *سائز = 0;
    }
    واپس متن;
}

bool SDL_سیٹ_Clipboard_متن(ثابت حرف *متن)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    اگر (متن && *متن) {
        متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);

        واپس SDL_سیٹ_Clipboard_ڈیٹا(SDL_Clipboard_متن_Callback, SDL_free, SDL_strdup(متن), متن_mime_types, عدد_mime_types);
    }
    واپس SDL_Clear_Clipboard_ڈیٹا();
}

حرف *SDL_Get_Clipboard_متن(خالی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;
    size_t لمبائی;
    حرف *متن = تہی;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس SDL_strdup("");
    }

    متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);
    برائے (i = 0; i < عدد_mime_types; ++i) {
        خالی *clipdata = SDL_Get_Clipboard_ڈیٹا(متن_mime_types[i], &لمبائی);
        اگر (clipdata) {
            متن = (حرف *)clipdata;
            توڑو;
        }
    }

    اگر (!متن) {
        متن = SDL_strdup("");
    }
    واپس متن;
}

bool SDL_Has_Clipboard_متن(خالی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, عدد_mime_types;
    ثابت حرف *ثابت *متن_mime_types;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    متن_mime_types = SDL_Get_متن_Mime_Types(_this, &عدد_mime_types);
    برائے (i = 0; i < عدد_mime_types; ++i) {
        اگر (SDL_Has_Clipboard_ڈیٹا(متن_mime_types[i])) {
            واپس true;
        }
    }
    واپس false;
}

// Primary selection text

bool SDL_سیٹ_Primary_Selection_متن(ثابت حرف *متن)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    اگر (!متن) {
        متن = "";
    }
    اگر (_this->سیٹ_Primary_Selection_متن) {
        اگر (!_this->سیٹ_Primary_Selection_متن(_this, متن)) {
            واپس false;
        }
    } ورنہ {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = SDL_strdup(متن);
    }

    حرف **mime_types = SDL_CopyClipboardMimeTypes((ثابت حرف **)_this->clipboard_mime_types, _this->عدد_clipboard_mime_types, true);
    اگر (!mime_types) {
        واپس SDL_سیٹ_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->عدد_clipboard_mime_types);
    واپس true;
}

حرف *SDL_Get_Primary_Selection_متن(خالی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس SDL_strdup("");
    }

    اگر (_this->Get_Primary_Selection_متن) {
        واپس _this->Get_Primary_Selection_متن(_this);
    } ورنہ {
        ثابت حرف *متن = _this->primary_selection_متن;
        اگر (!متن) {
            متن = "";
        }
        واپس SDL_strdup(متن);
    }
}

bool SDL_Has_Primary_Selection_متن(خالی)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    اگر (_this->Has_Primary_Selection_متن) {
        واپس _this->Has_Primary_Selection_متن(_this);
    } ورنہ {
        اگر (_this->primary_selection_متن && _this->primary_selection_متن[0] != '\0') {
            واپس true;
        } ورنہ {
            واپس false;
        }
    }
}

