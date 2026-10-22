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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_clipboard_c.h"
#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "../events/SDL_events_c.h"
#अन्तर्भाव "../events/SDL_clipboardevents_c.h"

शून्य SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    यदि (_this->clipboard_mime_types) {
        प्रति (size_t i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = रिक्त;
        _this->अङ्कः_clipboard_mime_types = 0;
    }
}


शून्य SDL_Cancel_Clipboard_दत्त(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम;
    }

    यदि (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        प्रत्यागम;
    }

    यदि (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = रिक्त;
    _this->clipboard_cleanup = रिक्त;
    _this->clipboard_userdata = रिक्त;
}

bool SDL_SaveClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    यदि (mime_types && अङ्कः_mime_types > 0) {
        size_t अङ्कः_allocated = 0;

        _this->clipboard_mime_types = (वर्ण **)SDL_malloc(अङ्कः_mime_types * परिमाण(वर्ण *));
        यदि (_this->clipboard_mime_types) {
            प्रति (size_t i = 0; i < अङ्कः_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                यदि (_this->clipboard_mime_types[i]) {
                    ++अङ्कः_allocated;
                }
            }
        }
        यदि (अङ्कः_allocated < अङ्कः_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            प्रत्यागम false;
        }
        _this->अङ्कः_clipboard_mime_types = अङ्कः_mime_types;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_Clipboard_दत्त(SDL_Clipboard_दत्त_Callback callback, SDL_ClipboardCleanupCallback cleanup, शून्य *userdata, ध्रुव वर्ण *ध्रुव *mime_types, size_t अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    // Parameter validation
    यदि (!((callback && mime_types && अङ्कः_mime_types > 0) ||
          (!callback && !mime_types && अङ्कः_mime_types == 0))) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_दत्त(0);

    ++_this->clipboard_sequence;
    यदि (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    यदि (!SDL_SaveClipboardMimeTypes(mime_types, अङ्कः_mime_types)) {
        SDL_Clear_Clipboard_दत्त();
        प्रत्यागम false;
    }

    यदि (_this->समुच्चयः_Clipboard_दत्त) {
        यदि (!_this->समुच्चयः_Clipboard_दत्त(_this)) {
            प्रत्यागम false;
        }
    } अन्यथा यदि (_this->समुच्चयः_Clipboard_Text) {
        वर्ण *text = रिक्त;
        size_t आकार;

        प्रति (size_t i = 0; i < अङ्कः_mime_types; ++i) {
            ध्रुव वर्ण *mime_type = _this->clipboard_mime_types[i];
            यदि (SDL_IsTextMimeType(mime_type)) {
                ध्रुव शून्य *दत्त = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &आकार);
                यदि (दत्त) {
                    text = (वर्ण *)SDL_malloc(आकार + 1);
                    SDL_memcpy(text, दत्त, आकार);
                    text[आकार] = '\0';
                    यदि (!_this->समुच्चयः_Clipboard_Text(_this, text)) {
                        SDL_free(text);
                        प्रत्यागम false;
                    }
                    भङ्ग;
                }
            }
        }
        यदि (text) {
            SDL_free(text);
        } अन्यथा {
            यदि (!_this->समुच्चयः_Clipboard_Text(_this, "")) {
                प्रत्यागम false;
            }
        }
    }

    वर्ण **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अङ्कः_mime_types, true);
    यदि (!mime_types_copy) {
        प्रत्यागम SDL_समुच्चयः_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अङ्कः_mime_types);
    प्रत्यागम true;
}

bool SDL_Clear_Clipboard_दत्त(शून्य)
{
    प्रत्यागम SDL_समुच्चयः_Clipboard_दत्त(रिक्त, रिक्त, रिक्त, रिक्त, 0);
}

शून्य *SDL_Get_आन्तरिकम्_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *आकार)
{
    शून्य *दत्त = रिक्त;

    यदि (_this->clipboard_callback) {
        यदि (!SDL_Has_आन्तरिकम्_Clipboard_दत्त(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            प्रत्यागम रिक्त;
        }

        ध्रुव शून्य *provided_दत्त = _this->clipboard_callback(_this->clipboard_userdata, mime_type, आकार);
        यदि (provided_दत्त) {
            // Make a copy of it for the caller and guarantee null termination
            दत्त = SDL_malloc(*आकार + परिमाण(Uint32));
            यदि (दत्त) {
                SDL_memcpy(दत्त, provided_दत्त, *आकार);
                SDL_memset((Uint8 *)दत्त + *आकार, 0, परिमाण(Uint32));
            } अन्यथा {
                *आकार = 0;
            }
        }
    }
    प्रत्यागम दत्त;
}

शून्य *SDL_Get_Clipboard_दत्त(ध्रुव वर्ण *mime_type, size_t *आकार)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t अप्रयुक्तम्;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        प्रत्यागम रिक्त;
    }
    यदि (!आकार) {
        आकार = &अप्रयुक्तम्;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *आकार = 0;

    यदि (_this->Get_Clipboard_दत्त) {
        प्रत्यागम _this->Get_Clipboard_दत्त(_this, mime_type, आकार);
    } अन्यथा यदि (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        वर्ण *text = _this->GetClipboardText(_this);
        यदि (text) {
            यदि (*text == '\0') {
                SDL_free(text);
                text = रिक्त;
            } अन्यथा {
                *आकार = SDL_strlen(text);
            }
        }
        प्रत्यागम text;
    } अन्यथा {
        प्रत्यागम SDL_Get_आन्तरिकम्_Clipboard_दत्त(_this, mime_type, आकार);
    }
}

bool SDL_Has_आन्तरिकम्_Clipboard_दत्त(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type)
{
    size_t i;

    प्रति (i = 0; i < _this->अङ्कः_clipboard_mime_types; ++i) {
        यदि (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

bool SDL_Has_Clipboard_दत्त(ध्रुव वर्ण *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        प्रत्यागम SDL_InvalidParamError("mime_type");
    }

    यदि (_this->Has_Clipboard_दत्त) {
        प्रत्यागम _this->Has_Clipboard_दत्त(_this, mime_type);
    } अन्यथा यदि (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        प्रत्यागम _this->HasClipboardText(_this);
    } अन्यथा {
        प्रत्यागम SDL_Has_आन्तरिकम्_Clipboard_दत्त(_this, mime_type);
    }
}

वर्ण **SDL_CopyClipboardMimeTypes(ध्रुव वर्ण *ध्रुव *clipboard_mime_types, size_t अङ्कः_mime_types, bool temporary)
{
    size_t alloc_आकार = परिमाण(वर्ण *);
    प्रति (size_t i = 0; i < अङ्कः_mime_types; i++) {
        alloc_आकार += परिमाण(वर्ण *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    वर्ण *ret;
    यदि (temporary)
        ret = (वर्ण *)SDL_Allocate_Temporary_स्मृतिः(alloc_आकार);
    अन्यथा
        ret = (वर्ण *)SDL_malloc(alloc_आकार);
    यदि (!ret) {
        प्रत्यागम रिक्त;
    }

    वर्ण **परिणाम = (वर्ण **)ret;
    ret += परिमाण(वर्ण *) * (अङ्कः_mime_types + 1);

    प्रति (size_t i = 0; i < अङ्कः_mime_types; i++) {
        परिणाम[i] = ret;

        ध्रुव वर्ण *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        वर्ण c;
        कुरु {
            c = *ret++ = *mime_type++;
        } यावत् (c != '\0');
    }
    परिणाम[अङ्कः_mime_types] = रिक्त;

    प्रत्यागम परिणाम;

}

वर्ण **SDL_GetClipboardMimeTypes(size_t *अङ्कः_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (अङ्कः_mime_types) {
        *अङ्कः_mime_types = 0;
    }

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    यदि (अङ्कः_mime_types) {
        *अङ्कः_mime_types = _this->अङ्कः_clipboard_mime_types;
    }
    प्रत्यागम SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(ध्रुव वर्ण *mime_type)
{
    प्रत्यागम (SDL_strncmp(mime_type, "text", 4) == 0);
}

स्थिर ध्रुव वर्ण *ध्रुव *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types)
{
    यदि (_this->GetTextMimeTypes) {
        प्रत्यागम _this->GetTextMimeTypes(_this, अङ्कः_mime_types);
    } अन्यथा {
        स्थिर ध्रुव वर्ण *ध्रुव text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अङ्कः_mime_types = SDL_arraysize(text_mime_types);
        प्रत्यागम text_mime_types;
    }
}

ध्रुव शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, ध्रुव वर्ण *mime_type, size_t *आकार)
{
    वर्ण *text = (वर्ण *)userdata;
    यदि (text) {
        *आकार = SDL_strlen(text);
    } अन्यथा {
        *आकार = 0;
    }
    प्रत्यागम text;
}

bool SDL_समुच्चयः_Clipboard_Text(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);

        प्रत्यागम SDL_समुच्चयः_Clipboard_दत्त(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अङ्कः_mime_types);
    }
    प्रत्यागम SDL_Clear_Clipboard_दत्त();
}

वर्ण *SDL_GetClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;
    size_t दीर्घता;
    वर्ण *text = रिक्त;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    प्रति (i = 0; i < अङ्कः_mime_types; ++i) {
        शून्य *clipdata = SDL_Get_Clipboard_दत्त(text_mime_types[i], &दीर्घता);
        यदि (clipdata) {
            text = (वर्ण *)clipdata;
            भङ्ग;
        }
    }

    यदि (!text) {
        text = SDL_strdup("");
    }
    प्रत्यागम text;
}

bool SDL_HasClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, अङ्कः_mime_types;
    ध्रुव वर्ण *ध्रुव *text_mime_types;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अङ्कः_mime_types);
    प्रति (i = 0; i < अङ्कः_mime_types; ++i) {
        यदि (SDL_Has_Clipboard_दत्त(text_mime_types[i])) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

// Primary selection text

bool SDL_समुच्चयः_Primary_Selection_Text(ध्रुव वर्ण *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (!text) {
        text = "";
    }
    यदि (_this->समुच्चयः_Primary_Selection_Text) {
        यदि (!_this->समुच्चयः_Primary_Selection_Text(_this, text)) {
            प्रत्यागम false;
        }
    } अन्यथा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    वर्ण **mime_types = SDL_CopyClipboardMimeTypes((ध्रुव वर्ण **)_this->clipboard_mime_types, _this->अङ्कः_clipboard_mime_types, true);
    यदि (!mime_types) {
        प्रत्यागम SDL_समुच्चयः_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अङ्कः_clipboard_mime_types);
    प्रत्यागम true;
}

वर्ण *SDL_GetPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम SDL_strdup("");
    }

    यदि (_this->GetPrimarySelectionText) {
        प्रत्यागम _this->GetPrimarySelectionText(_this);
    } अन्यथा {
        ध्रुव वर्ण *text = _this->primary_selection_text;
        यदि (!text) {
            text = "";
        }
        प्रत्यागम SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (_this->HasPrimarySelectionText) {
        प्रत्यागम _this->HasPrimarySelectionText(_this);
    } अन्यथा {
        यदि (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            प्रत्यागम true;
        } अन्यथा {
            प्रत्यागम false;
        }
    }
}

