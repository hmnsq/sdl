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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_clipboard_c.h"
#অন্তর্ভাব "SDL_sysvideo.h"
#অন্তর্ভাব "../events/SDL_events_c.h"
#অন্তর্ভাব "../events/SDL_clipboardevents_c.h"

শূন্য SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    যদি (_this->clipboard_mime_types) {
        প্রতি (size_t i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = রিক্ত;
        _this->অঙ্ক_clipboard_mime_types = 0;
    }
}


শূন্য SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম;
    }

    যদি (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        প্রত্যাগম;
    }

    যদি (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = রিক্ত;
    _this->clipboard_cleanup = রিক্ত;
    _this->clipboard_userdata = রিক্ত;
}

bool SDL_SaveClipboardMimeTypes(ধ্রুব বর্ণ *ধ্রুব *mime_types, size_t অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    যদি (mime_types && অঙ্ক_mime_types > 0) {
        size_t অঙ্ক_allocated = 0;

        _this->clipboard_mime_types = (বর্ণ **)SDL_malloc(অঙ্ক_mime_types * পরিমাণ(বর্ণ *));
        যদি (_this->clipboard_mime_types) {
            প্রতি (size_t i = 0; i < অঙ্ক_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                যদি (_this->clipboard_mime_types[i]) {
                    ++অঙ্ক_allocated;
                }
            }
        }
        যদি (অঙ্ক_allocated < অঙ্ক_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            প্রত্যাগম false;
        }
        _this->অঙ্ক_clipboard_mime_types = অঙ্ক_mime_types;
    }
    প্রত্যাগম true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, শূন্য *userdata, ধ্রুব বর্ণ *ধ্রুব *mime_types, size_t অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    // Parameter validation
    যদি (!((callback && mime_types && অঙ্ক_mime_types > 0) ||
          (!callback && !mime_types && অঙ্ক_mime_types == 0))) {
        প্রত্যাগম SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    যদি (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    যদি (!SDL_SaveClipboardMimeTypes(mime_types, অঙ্ক_mime_types)) {
        SDL_ClearClipboardData();
        প্রত্যাগম false;
    }

    যদি (_this->SetClipboardData) {
        যদি (!_this->SetClipboardData(_this)) {
            প্রত্যাগম false;
        }
    } অন্যথা যদি (_this->SetClipboardText) {
        বর্ণ *text = রিক্ত;
        size_t size;

        প্রতি (size_t i = 0; i < অঙ্ক_mime_types; ++i) {
            ধ্রুব বর্ণ *mime_type = _this->clipboard_mime_types[i];
            যদি (SDL_IsTextMimeType(mime_type)) {
                ধ্রুব শূন্য *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                যদি (data) {
                    text = (বর্ণ *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    যদি (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        প্রত্যাগম false;
                    }
                    ভঙ্গ;
                }
            }
        }
        যদি (text) {
            SDL_free(text);
        } অন্যথা {
            যদি (!_this->SetClipboardText(_this, "")) {
                প্রত্যাগম false;
            }
        }
    }

    বর্ণ **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, অঙ্ক_mime_types, true);
    যদি (!mime_types_copy) {
        প্রত্যাগম SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, অঙ্ক_mime_types);
    প্রত্যাগম true;
}

bool SDL_ClearClipboardData(শূন্য)
{
    প্রত্যাগম SDL_SetClipboardData(রিক্ত, রিক্ত, রিক্ত, রিক্ত, 0);
}

শূন্য *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type, size_t *size)
{
    শূন্য *data = রিক্ত;

    যদি (_this->clipboard_callback) {
        যদি (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            প্রত্যাগম রিক্ত;
        }

        ধ্রুব শূন্য *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        যদি (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + পরিমাণ(Uint32));
            যদি (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, পরিমাণ(Uint32));
            } অন্যথা {
                *size = 0;
            }
        }
    }
    প্রত্যাগম data;
}

শূন্য *SDL_GetClipboardData(ধ্রুব বর্ণ *mime_type, size_t *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        প্রত্যাগম রিক্ত;
    }
    যদি (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    যদি (_this->GetClipboardData) {
        প্রত্যাগম _this->GetClipboardData(_this, mime_type, size);
    } অন্যথা যদি (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        বর্ণ *text = _this->GetClipboardText(_this);
        যদি (text) {
            যদি (*text == '\0') {
                SDL_free(text);
                text = রিক্ত;
            } অন্যথা {
                *size = SDL_strlen(text);
            }
        }
        প্রত্যাগম text;
    } অন্যথা {
        প্রত্যাগম SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, ধ্রুব বর্ণ *mime_type)
{
    size_t i;

    প্রতি (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
        যদি (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম false;
}

bool SDL_HasClipboardData(ধ্রুব বর্ণ *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        প্রত্যাগম SDL_InvalidParamError("mime_type");
    }

    যদি (_this->HasClipboardData) {
        প্রত্যাগম _this->HasClipboardData(_this, mime_type);
    } অন্যথা যদি (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        প্রত্যাগম _this->HasClipboardText(_this);
    } অন্যথা {
        প্রত্যাগম SDL_HasInternalClipboardData(_this, mime_type);
    }
}

বর্ণ **SDL_CopyClipboardMimeTypes(ধ্রুব বর্ণ *ধ্রুব *clipboard_mime_types, size_t অঙ্ক_mime_types, bool temporary)
{
    size_t allocSize = পরিমাণ(বর্ণ *);
    প্রতি (size_t i = 0; i < অঙ্ক_mime_types; i++) {
        allocSize += পরিমাণ(বর্ণ *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    বর্ণ *ret;
    যদি (temporary)
        ret = (বর্ণ *)SDL_AllocateTemporaryMemory(allocSize);
    অন্যথা
        ret = (বর্ণ *)SDL_malloc(allocSize);
    যদি (!ret) {
        প্রত্যাগম রিক্ত;
    }

    বর্ণ **result = (বর্ণ **)ret;
    ret += পরিমাণ(বর্ণ *) * (অঙ্ক_mime_types + 1);

    প্রতি (size_t i = 0; i < অঙ্ক_mime_types; i++) {
        result[i] = ret;

        ধ্রুব বর্ণ *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        বর্ণ c;
        কুরু {
            c = *ret++ = *mime_type++;
        } যাবত্ (c != '\0');
    }
    result[অঙ্ক_mime_types] = রিক্ত;

    প্রত্যাগম result;

}

বর্ণ **SDL_GetClipboardMimeTypes(size_t *অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (অঙ্ক_mime_types) {
        *অঙ্ক_mime_types = 0;
    }

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }

    যদি (অঙ্ক_mime_types) {
        *অঙ্ক_mime_types = _this->অঙ্ক_clipboard_mime_types;
    }
    প্রত্যাগম SDL_CopyClipboardMimeTypes((ধ্রুব বর্ণ **)_this->clipboard_mime_types, _this->অঙ্ক_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ধ্রুব বর্ণ *mime_type)
{
    প্রত্যাগম (SDL_strncmp(mime_type, "text", 4) == 0);
}

স্থির ধ্রুব বর্ণ *ধ্রুব *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types)
{
    যদি (_this->GetTextMimeTypes) {
        প্রত্যাগম _this->GetTextMimeTypes(_this, অঙ্ক_mime_types);
    } অন্যথা {
        স্থির ধ্রুব বর্ণ *ধ্রুব text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *অঙ্ক_mime_types = SDL_arraysize(text_mime_types);
        প্রত্যাগম text_mime_types;
    }
}

ধ্রুব শূন্য * SDLCALL SDL_ClipboardTextCallback(শূন্য *userdata, ধ্রুব বর্ণ *mime_type, size_t *size)
{
    বর্ণ *text = (বর্ণ *)userdata;
    যদি (text) {
        *size = SDL_strlen(text);
    } অন্যথা {
        *size = 0;
    }
    প্রত্যাগম text;
}

bool SDL_SetClipboardText(ধ্রুব বর্ণ *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t অঙ্ক_mime_types;
    ধ্রুব বর্ণ *ধ্রুব *text_mime_types;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    যদি (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);

        প্রত্যাগম SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, অঙ্ক_mime_types);
    }
    প্রত্যাগম SDL_ClearClipboardData();
}

বর্ণ *SDL_GetClipboardText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, অঙ্ক_mime_types;
    ধ্রুব বর্ণ *ধ্রুব *text_mime_types;
    size_t length;
    বর্ণ *text = রিক্ত;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);
    প্রতি (i = 0; i < অঙ্ক_mime_types; ++i) {
        শূন্য *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        যদি (clipdata) {
            text = (বর্ণ *)clipdata;
            ভঙ্গ;
        }
    }

    যদি (!text) {
        text = SDL_strdup("");
    }
    প্রত্যাগম text;
}

bool SDL_HasClipboardText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, অঙ্ক_mime_types;
    ধ্রুব বর্ণ *ধ্রুব *text_mime_types;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);
    প্রতি (i = 0; i < অঙ্ক_mime_types; ++i) {
        যদি (SDL_HasClipboardData(text_mime_types[i])) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ধ্রুব বর্ণ *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    যদি (!text) {
        text = "";
    }
    যদি (_this->SetPrimarySelectionText) {
        যদি (!_this->SetPrimarySelectionText(_this, text)) {
            প্রত্যাগম false;
        }
    } অন্যথা {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    বর্ণ **mime_types = SDL_CopyClipboardMimeTypes((ধ্রুব বর্ণ **)_this->clipboard_mime_types, _this->অঙ্ক_clipboard_mime_types, true);
    যদি (!mime_types) {
        প্রত্যাগম SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->অঙ্ক_clipboard_mime_types);
    প্রত্যাগম true;
}

বর্ণ *SDL_GetPrimarySelectionText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম SDL_strdup("");
    }

    যদি (_this->GetPrimarySelectionText) {
        প্রত্যাগম _this->GetPrimarySelectionText(_this);
    } অন্যথা {
        ধ্রুব বর্ণ *text = _this->primary_selection_text;
        যদি (!text) {
            text = "";
        }
        প্রত্যাগম SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    যদি (_this->HasPrimarySelectionText) {
        প্রত্যাগম _this->HasPrimarySelectionText(_this);
    } অন্যথা {
        যদি (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            প্রত্যাগম true;
        } অন্যথা {
            প্রত্যাগম false;
        }
    }
}

