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
        জন্য (size_t i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ফাঁকা;
        _this->অঙ্ক_clipboard_mime_types = 0;
    }
}


শূন্য SDL_Cancel_Clipboard_তথ্য(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত;
    }

    যদি (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        ফেরত;
    }

    যদি (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ফাঁকা;
    _this->clipboard_cleanup = ফাঁকা;
    _this->clipboard_userdata = ফাঁকা;
}

bool SDL_SaveClipboardMimeTypes(ধ্রুবক অক্ষর *ধ্রুবক *mime_types, size_t অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    যদি (mime_types && অঙ্ক_mime_types > 0) {
        size_t অঙ্ক_allocated = 0;

        _this->clipboard_mime_types = (অক্ষর **)SDL_malloc(অঙ্ক_mime_types * আকার(অক্ষর *));
        যদি (_this->clipboard_mime_types) {
            জন্য (size_t i = 0; i < অঙ্ক_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                যদি (_this->clipboard_mime_types[i]) {
                    ++অঙ্ক_allocated;
                }
            }
        }
        যদি (অঙ্ক_allocated < অঙ্ক_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            ফেরত false;
        }
        _this->অঙ্ক_clipboard_mime_types = অঙ্ক_mime_types;
    }
    ফেরত true;
}

bool SDL_Set_Clipboard_তথ্য(SDL_Clipboard_তথ্য_Callback callback, SDL_ClipboardCleanupCallback cleanup, শূন্য *userdata, ধ্রুবক অক্ষর *ধ্রুবক *mime_types, size_t অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    // Parameter validation
    যদি (!((callback && mime_types && অঙ্ক_mime_types > 0) ||
          (!callback && !mime_types && অঙ্ক_mime_types == 0))) {
        ফেরত SDL_SetError("Invalid parameters");
    }

    SDL_Cancel_Clipboard_তথ্য(0);

    ++_this->clipboard_sequence;
    যদি (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    যদি (!SDL_SaveClipboardMimeTypes(mime_types, অঙ্ক_mime_types)) {
        SDL_Clear_Clipboard_তথ্য();
        ফেরত false;
    }

    যদি (_this->Set_Clipboard_তথ্য) {
        যদি (!_this->Set_Clipboard_তথ্য(_this)) {
            ফেরত false;
        }
    } অন্যথা যদি (_this->SetClipboardText) {
        অক্ষর *text = ফাঁকা;
        size_t আকার_2;

        জন্য (size_t i = 0; i < অঙ্ক_mime_types; ++i) {
            ধ্রুবক অক্ষর *mime_type = _this->clipboard_mime_types[i];
            যদি (SDL_IsTextMimeType(mime_type)) {
                ধ্রুবক শূন্য *তথ্য = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &আকার_2);
                যদি (তথ্য) {
                    text = (অক্ষর *)SDL_malloc(আকার_2 + 1);
                    SDL_memcpy(text, তথ্য, আকার_2);
                    text[আকার_2] = '\0';
                    যদি (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        ফেরত false;
                    }
                    বিরতি;
                }
            }
        }
        যদি (text) {
            SDL_free(text);
        } অন্যথা {
            যদি (!_this->SetClipboardText(_this, "")) {
                ফেরত false;
            }
        }
    }

    অক্ষর **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, অঙ্ক_mime_types, true);
    যদি (!mime_types_copy) {
        ফেরত SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, অঙ্ক_mime_types);
    ফেরত true;
}

bool SDL_Clear_Clipboard_তথ্য(শূন্য)
{
    ফেরত SDL_Set_Clipboard_তথ্য(ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা, 0);
}

শূন্য *SDL_Get_Internal_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type, size_t *আকার_2)
{
    শূন্য *তথ্য = ফাঁকা;

    যদি (_this->clipboard_callback) {
        যদি (!SDL_Has_Internal_Clipboard_তথ্য(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            ফেরত ফাঁকা;
        }

        ধ্রুবক শূন্য *provided_তথ্য = _this->clipboard_callback(_this->clipboard_userdata, mime_type, আকার_2);
        যদি (provided_তথ্য) {
            // Make a copy of it for the caller and guarantee null termination
            তথ্য = SDL_malloc(*আকার_2 + আকার(Uint32));
            যদি (তথ্য) {
                SDL_memcpy(তথ্য, provided_তথ্য, *আকার_2);
                SDL_memset((Uint8 *)তথ্য + *আকার_2, 0, আকার(Uint32));
            } অন্যথা {
                *আকার_2 = 0;
            }
        }
    }
    ফেরত তথ্য;
}

শূন্য *SDL_Get_Clipboard_তথ্য(ধ্রুবক অক্ষর *mime_type, size_t *আকার_2)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t unused;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        ফেরত ফাঁকা;
    }
    যদি (!আকার_2) {
        আকার_2 = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *আকার_2 = 0;

    যদি (_this->Get_Clipboard_তথ্য) {
        ফেরত _this->Get_Clipboard_তথ্য(_this, mime_type, আকার_2);
    } অন্যথা যদি (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        অক্ষর *text = _this->GetClipboardText(_this);
        যদি (text) {
            যদি (*text == '\0') {
                SDL_free(text);
                text = ফাঁকা;
            } অন্যথা {
                *আকার_2 = SDL_strlen(text);
            }
        }
        ফেরত text;
    } অন্যথা {
        ফেরত SDL_Get_Internal_Clipboard_তথ্য(_this, mime_type, আকার_2);
    }
}

bool SDL_Has_Internal_Clipboard_তথ্য(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type)
{
    size_t i;

    জন্য (i = 0; i < _this->অঙ্ক_clipboard_mime_types; ++i) {
        যদি (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            ফেরত true;
        }
    }
    ফেরত false;
}

bool SDL_Has_Clipboard_তথ্য(ধ্রুবক অক্ষর *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        ফেরত SDL_InvalidParamError("mime_type");
    }

    যদি (_this->Has_Clipboard_তথ্য) {
        ফেরত _this->Has_Clipboard_তথ্য(_this, mime_type);
    } অন্যথা যদি (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        ফেরত _this->HasClipboardText(_this);
    } অন্যথা {
        ফেরত SDL_Has_Internal_Clipboard_তথ্য(_this, mime_type);
    }
}

অক্ষর **SDL_CopyClipboardMimeTypes(ধ্রুবক অক্ষর *ধ্রুবক *clipboard_mime_types, size_t অঙ্ক_mime_types, bool temporary)
{
    size_t alloc_আকার = আকার(অক্ষর *);
    জন্য (size_t i = 0; i < অঙ্ক_mime_types; i++) {
        alloc_আকার += আকার(অক্ষর *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    অক্ষর *ret;
    যদি (temporary)
        ret = (অক্ষর *)SDL_AllocateTemporaryMemory(alloc_আকার);
    অন্যথা
        ret = (অক্ষর *)SDL_malloc(alloc_আকার);
    যদি (!ret) {
        ফেরত ফাঁকা;
    }

    অক্ষর **ফলাফল = (অক্ষর **)ret;
    ret += আকার(অক্ষর *) * (অঙ্ক_mime_types + 1);

    জন্য (size_t i = 0; i < অঙ্ক_mime_types; i++) {
        ফলাফল[i] = ret;

        ধ্রুবক অক্ষর *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        অক্ষর c;
        করো {
            c = *ret++ = *mime_type++;
        } যখন (c != '\0');
    }
    ফলাফল[অঙ্ক_mime_types] = ফাঁকা;

    ফেরত ফলাফল;

}

অক্ষর **SDL_GetClipboardMimeTypes(size_t *অঙ্ক_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (অঙ্ক_mime_types) {
        *অঙ্ক_mime_types = 0;
    }

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }

    যদি (অঙ্ক_mime_types) {
        *অঙ্ক_mime_types = _this->অঙ্ক_clipboard_mime_types;
    }
    ফেরত SDL_CopyClipboardMimeTypes((ধ্রুবক অক্ষর **)_this->clipboard_mime_types, _this->অঙ্ক_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ধ্রুবক অক্ষর *mime_type)
{
    ফেরত (SDL_strncmp(mime_type, "text", 4) == 0);
}

স্থির ধ্রুবক অক্ষর *ধ্রুবক *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types)
{
    যদি (_this->GetTextMimeTypes) {
        ফেরত _this->GetTextMimeTypes(_this, অঙ্ক_mime_types);
    } অন্যথা {
        স্থির ধ্রুবক অক্ষর *ধ্রুবক text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *অঙ্ক_mime_types = SDL_arraysize(text_mime_types);
        ফেরত text_mime_types;
    }
}

ধ্রুবক শূন্য * SDLCALL SDL_ClipboardTextCallback(শূন্য *userdata, ধ্রুবক অক্ষর *mime_type, size_t *আকার_2)
{
    অক্ষর *text = (অক্ষর *)userdata;
    যদি (text) {
        *আকার_2 = SDL_strlen(text);
    } অন্যথা {
        *আকার_2 = 0;
    }
    ফেরত text;
}

bool SDL_SetClipboardText(ধ্রুবক অক্ষর *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t অঙ্ক_mime_types;
    ধ্রুবক অক্ষর *ধ্রুবক *text_mime_types;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    যদি (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);

        ফেরত SDL_Set_Clipboard_তথ্য(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, অঙ্ক_mime_types);
    }
    ফেরত SDL_Clear_Clipboard_তথ্য();
}

অক্ষর *SDL_GetClipboardText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, অঙ্ক_mime_types;
    ধ্রুবক অক্ষর *ধ্রুবক *text_mime_types;
    size_t দৈর্ঘ্য;
    অক্ষর *text = ফাঁকা;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);
    জন্য (i = 0; i < অঙ্ক_mime_types; ++i) {
        শূন্য *clipdata = SDL_Get_Clipboard_তথ্য(text_mime_types[i], &দৈর্ঘ্য);
        যদি (clipdata) {
            text = (অক্ষর *)clipdata;
            বিরতি;
        }
    }

    যদি (!text) {
        text = SDL_strdup("");
    }
    ফেরত text;
}

bool SDL_HasClipboardText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, অঙ্ক_mime_types;
    ধ্রুবক অক্ষর *ধ্রুবক *text_mime_types;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &অঙ্ক_mime_types);
    জন্য (i = 0; i < অঙ্ক_mime_types; ++i) {
        যদি (SDL_Has_Clipboard_তথ্য(text_mime_types[i])) {
            ফেরত true;
        }
    }
    ফেরত false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(ধ্রুবক অক্ষর *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    যদি (!text) {
        text = "";
    }
    যদি (_this->SetPrimarySelectionText) {
        যদি (!_this->SetPrimarySelectionText(_this, text)) {
            ফেরত false;
        }
    } অন্যথা {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    অক্ষর **mime_types = SDL_CopyClipboardMimeTypes((ধ্রুবক অক্ষর **)_this->clipboard_mime_types, _this->অঙ্ক_clipboard_mime_types, true);
    যদি (!mime_types) {
        ফেরত SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->অঙ্ক_clipboard_mime_types);
    ফেরত true;
}

অক্ষর *SDL_GetPrimarySelectionText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত SDL_strdup("");
    }

    যদি (_this->GetPrimarySelectionText) {
        ফেরত _this->GetPrimarySelectionText(_this);
    } অন্যথা {
        ধ্রুবক অক্ষর *text = _this->primary_selection_text;
        যদি (!text) {
            text = "";
        }
        ফেরত SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(শূন্য)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    যদি (_this->HasPrimarySelectionText) {
        ফেরত _this->HasPrimarySelectionText(_this);
    } অন্যথা {
        যদি (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            ফেরত true;
        } অন্যথা {
            ফেরত false;
        }
    }
}

