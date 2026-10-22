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
    जर (_this->clipboard_mime_types) {
        साठी (माप_प्रकार i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = रिक्त;
        _this->अंक_clipboard_mime_types = 0;
    }
}


शून्य SDL_CancelClipboardData(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत;
    }

    जर (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        परत;
    }

    जर (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = रिक्त;
    _this->clipboard_cleanup = रिक्त;
    _this->clipboard_userdata = रिक्त;
}

bool SDL_SaveClipboardMimeTypes(स्थिरांक अक्षर *स्थिरांक *mime_types, माप_प्रकार अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    जर (mime_types && अंक_mime_types > 0) {
        माप_प्रकार अंक_allocated = 0;

        _this->clipboard_mime_types = (अक्षर **)SDL_malloc(अंक_mime_types * आकार(अक्षर *));
        जर (_this->clipboard_mime_types) {
            साठी (माप_प्रकार i = 0; i < अंक_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                जर (_this->clipboard_mime_types[i]) {
                    ++अंक_allocated;
                }
            }
        }
        जर (अंक_allocated < अंक_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            परत false;
        }
        _this->अंक_clipboard_mime_types = अंक_mime_types;
    }
    परत true;
}

bool SDL_SetClipboardData(SDL_ClipboardDataCallback callback, SDL_ClipboardCleanupCallback cleanup, शून्य *userdata, स्थिरांक अक्षर *स्थिरांक *mime_types, माप_प्रकार अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    // Parameter validation
    जर (!((callback && mime_types && अंक_mime_types > 0) ||
          (!callback && !mime_types && अंक_mime_types == 0))) {
        परत SDL_SetError("Invalid parameters");
    }

    SDL_CancelClipboardData(0);

    ++_this->clipboard_sequence;
    जर (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    जर (!SDL_SaveClipboardMimeTypes(mime_types, अंक_mime_types)) {
        SDL_ClearClipboardData();
        परत false;
    }

    जर (_this->SetClipboardData) {
        जर (!_this->SetClipboardData(_this)) {
            परत false;
        }
    } अन्यथा जर (_this->SetClipboardText) {
        अक्षर *text = रिक्त;
        माप_प्रकार size;

        साठी (माप_प्रकार i = 0; i < अंक_mime_types; ++i) {
            स्थिरांक अक्षर *mime_type = _this->clipboard_mime_types[i];
            जर (SDL_IsTextMimeType(mime_type)) {
                स्थिरांक शून्य *data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &size);
                जर (data) {
                    text = (अक्षर *)SDL_malloc(size + 1);
                    SDL_memcpy(text, data, size);
                    text[size] = '\0';
                    जर (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        परत false;
                    }
                    थांबा;
                }
            }
        }
        जर (text) {
            SDL_free(text);
        } अन्यथा {
            जर (!_this->SetClipboardText(_this, "")) {
                परत false;
            }
        }
    }

    अक्षर **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अंक_mime_types, true);
    जर (!mime_types_copy) {
        परत SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अंक_mime_types);
    परत true;
}

bool SDL_ClearClipboardData(शून्य)
{
    परत SDL_SetClipboardData(रिक्त, रिक्त, रिक्त, रिक्त, 0);
}

शून्य *SDL_GetInternalClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type, माप_प्रकार *size)
{
    शून्य *data = रिक्त;

    जर (_this->clipboard_callback) {
        जर (!SDL_HasInternalClipboardData(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            परत रिक्त;
        }

        स्थिरांक शून्य *provided_data = _this->clipboard_callback(_this->clipboard_userdata, mime_type, size);
        जर (provided_data) {
            // Make a copy of it for the caller and guarantee null termination
            data = SDL_malloc(*size + आकार(Uint32));
            जर (data) {
                SDL_memcpy(data, provided_data, *size);
                SDL_memset((Uint8 *)data + *size, 0, आकार(Uint32));
            } अन्यथा {
                *size = 0;
            }
        }
    }
    परत data;
}

शून्य *SDL_GetClipboardData(स्थिरांक अक्षर *mime_type, माप_प्रकार *size)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार unused;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        परत रिक्त;
    }
    जर (!size) {
        size = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *size = 0;

    जर (_this->GetClipboardData) {
        परत _this->GetClipboardData(_this, mime_type, size);
    } अन्यथा जर (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        अक्षर *text = _this->GetClipboardText(_this);
        जर (text) {
            जर (*text == '\0') {
                SDL_free(text);
                text = रिक्त;
            } अन्यथा {
                *size = SDL_strlen(text);
            }
        }
        परत text;
    } अन्यथा {
        परत SDL_GetInternalClipboardData(_this, mime_type, size);
    }
}

bool SDL_HasInternalClipboardData(SDL_VideoDevice *_this, स्थिरांक अक्षर *mime_type)
{
    माप_प्रकार i;

    साठी (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
        जर (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            परत true;
        }
    }
    परत false;
}

bool SDL_HasClipboardData(स्थिरांक अक्षर *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        परत SDL_InvalidParamError("mime_type");
    }

    जर (_this->HasClipboardData) {
        परत _this->HasClipboardData(_this, mime_type);
    } अन्यथा जर (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        परत _this->HasClipboardText(_this);
    } अन्यथा {
        परत SDL_HasInternalClipboardData(_this, mime_type);
    }
}

अक्षर **SDL_CopyClipboardMimeTypes(स्थिरांक अक्षर *स्थिरांक *clipboard_mime_types, माप_प्रकार अंक_mime_types, bool temporary)
{
    माप_प्रकार allocSize = आकार(अक्षर *);
    साठी (माप_प्रकार i = 0; i < अंक_mime_types; i++) {
        allocSize += आकार(अक्षर *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    अक्षर *ret;
    जर (temporary)
        ret = (अक्षर *)SDL_AllocateTemporaryMemory(allocSize);
    अन्यथा
        ret = (अक्षर *)SDL_malloc(allocSize);
    जर (!ret) {
        परत रिक्त;
    }

    अक्षर **result = (अक्षर **)ret;
    ret += आकार(अक्षर *) * (अंक_mime_types + 1);

    साठी (माप_प्रकार i = 0; i < अंक_mime_types; i++) {
        result[i] = ret;

        स्थिरांक अक्षर *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        अक्षर c;
        करा {
            c = *ret++ = *mime_type++;
        } पर्यंत (c != '\0');
    }
    result[अंक_mime_types] = रिक्त;

    परत result;

}

अक्षर **SDL_GetClipboardMimeTypes(माप_प्रकार *अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (अंक_mime_types) {
        *अंक_mime_types = 0;
    }

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }

    जर (अंक_mime_types) {
        *अंक_mime_types = _this->अंक_clipboard_mime_types;
    }
    परत SDL_CopyClipboardMimeTypes((स्थिरांक अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(स्थिरांक अक्षर *mime_type)
{
    परत (SDL_strncmp(mime_type, "text", 4) == 0);
}

स्थिर स्थिरांक अक्षर *स्थिरांक *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types)
{
    जर (_this->GetTextMimeTypes) {
        परत _this->GetTextMimeTypes(_this, अंक_mime_types);
    } अन्यथा {
        स्थिर स्थिरांक अक्षर *स्थिरांक text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अंक_mime_types = SDL_arraysize(text_mime_types);
        परत text_mime_types;
    }
}

स्थिरांक शून्य * SDLCALL SDL_ClipboardTextCallback(शून्य *userdata, स्थिरांक अक्षर *mime_type, माप_प्रकार *size)
{
    अक्षर *text = (अक्षर *)userdata;
    जर (text) {
        *size = SDL_strlen(text);
    } अन्यथा {
        *size = 0;
    }
    परत text;
}

bool SDL_SetClipboardText(स्थिरांक अक्षर *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार अंक_mime_types;
    स्थिरांक अक्षर *स्थिरांक *text_mime_types;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    जर (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);

        परत SDL_SetClipboardData(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अंक_mime_types);
    }
    परत SDL_ClearClipboardData();
}

अक्षर *SDL_GetClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार i, अंक_mime_types;
    स्थिरांक अक्षर *स्थिरांक *text_mime_types;
    माप_प्रकार length;
    अक्षर *text = रिक्त;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    साठी (i = 0; i < अंक_mime_types; ++i) {
        शून्य *clipdata = SDL_GetClipboardData(text_mime_types[i], &length);
        जर (clipdata) {
            text = (अक्षर *)clipdata;
            थांबा;
        }
    }

    जर (!text) {
        text = SDL_strdup("");
    }
    परत text;
}

bool SDL_HasClipboardText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार i, अंक_mime_types;
    स्थिरांक अक्षर *स्थिरांक *text_mime_types;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    साठी (i = 0; i < अंक_mime_types; ++i) {
        जर (SDL_HasClipboardData(text_mime_types[i])) {
            परत true;
        }
    }
    परत false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(स्थिरांक अक्षर *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    जर (!text) {
        text = "";
    }
    जर (_this->SetPrimarySelectionText) {
        जर (!_this->SetPrimarySelectionText(_this, text)) {
            परत false;
        }
    } अन्यथा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    अक्षर **mime_types = SDL_CopyClipboardMimeTypes((स्थिरांक अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, true);
    जर (!mime_types) {
        परत SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अंक_clipboard_mime_types);
    परत true;
}

अक्षर *SDL_GetPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        SDL_UninitializedVideo();
        परत SDL_strdup("");
    }

    जर (_this->GetPrimarySelectionText) {
        परत _this->GetPrimarySelectionText(_this);
    } अन्यथा {
        स्थिरांक अक्षर *text = _this->primary_selection_text;
        जर (!text) {
            text = "";
        }
        परत SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(शून्य)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    जर (_this->HasPrimarySelectionText) {
        परत _this->HasPrimarySelectionText(_this);
    } अन्यथा {
        जर (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            परत true;
        } अन्यथा {
            परत false;
        }
    }
}

