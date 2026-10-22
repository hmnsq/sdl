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
#समावेश "SDL_internal.h"

#समावेश "SDL_clipboard_c.h"
#समावेश "SDL_sysvideo.h"
#समावेश "../events/SDL_events_c.h"
#समावेश "../events/SDL_clipboardevents_c.h"

व्योम SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    अगर (_this->clipboard_mime_types) {
        क्रम (माप_प्रकार i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = शून्य;
        _this->अंक_clipboard_mime_types = 0;
    }
}


व्योम SDL_Cancel_Clipboard_तथ्य(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस;
    }

    अगर (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        वापस;
    }

    अगर (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = शून्य;
    _this->clipboard_cleanup = शून्य;
    _this->clipboard_userdata = शून्य;
}

bool SDL_SaveClipboardMimeTypes(स्थिर अक्षर *स्थिर *mime_types, माप_प्रकार अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    अगर (mime_types && अंक_mime_types > 0) {
        माप_प्रकार अंक_allocated = 0;

        _this->clipboard_mime_types = (अक्षर **)SDL_malloc(अंक_mime_types * माप(अक्षर *));
        अगर (_this->clipboard_mime_types) {
            क्रम (माप_प्रकार i = 0; i < अंक_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                अगर (_this->clipboard_mime_types[i]) {
                    ++अंक_allocated;
                }
            }
        }
        अगर (अंक_allocated < अंक_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            वापस false;
        }
        _this->अंक_clipboard_mime_types = अंक_mime_types;
    }
    वापस true;
}

bool SDL_Set_Clipboard_तथ्य(SDL_Clipboard_तथ्य_Callback callback, SDL_ClipboardCleanupCallback cleanup, व्योम *userdata, स्थिर अक्षर *स्थिर *mime_types, माप_प्रकार अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    // Parameter validation
    अगर (!((callback && mime_types && अंक_mime_types > 0) ||
          (!callback && !mime_types && अंक_mime_types == 0))) {
        वापस SDL_SetError("Invalid parameters");
    }

    SDL_Cancel_Clipboard_तथ्य(0);

    ++_this->clipboard_sequence;
    अगर (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    अगर (!SDL_SaveClipboardMimeTypes(mime_types, अंक_mime_types)) {
        SDL_Clear_Clipboard_तथ्य();
        वापस false;
    }

    अगर (_this->Set_Clipboard_तथ्य) {
        अगर (!_this->Set_Clipboard_तथ्य(_this)) {
            वापस false;
        }
    } अन्यथा अगर (_this->SetClipboardText) {
        अक्षर *text = शून्य;
        माप_प्रकार आकार;

        क्रम (माप_प्रकार i = 0; i < अंक_mime_types; ++i) {
            स्थिर अक्षर *mime_type = _this->clipboard_mime_types[i];
            अगर (SDL_IsTextMimeType(mime_type)) {
                स्थिर व्योम *तथ्य = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &आकार);
                अगर (तथ्य) {
                    text = (अक्षर *)SDL_malloc(आकार + 1);
                    SDL_memcpy(text, तथ्य, आकार);
                    text[आकार] = '\0';
                    अगर (!_this->SetClipboardText(_this, text)) {
                        SDL_free(text);
                        वापस false;
                    }
                    अवरोध;
                }
            }
        }
        अगर (text) {
            SDL_free(text);
        } अन्यथा {
            अगर (!_this->SetClipboardText(_this, "")) {
                वापस false;
            }
        }
    }

    अक्षर **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, अंक_mime_types, true);
    अगर (!mime_types_copy) {
        वापस SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, अंक_mime_types);
    वापस true;
}

bool SDL_Clear_Clipboard_तथ्य(व्योम)
{
    वापस SDL_Set_Clipboard_तथ्य(शून्य, शून्य, शून्य, शून्य, 0);
}

व्योम *SDL_Get_Internal_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *आकार)
{
    व्योम *तथ्य = शून्य;

    अगर (_this->clipboard_callback) {
        अगर (!SDL_Has_Internal_Clipboard_तथ्य(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            वापस शून्य;
        }

        स्थिर व्योम *provided_तथ्य = _this->clipboard_callback(_this->clipboard_userdata, mime_type, आकार);
        अगर (provided_तथ्य) {
            // Make a copy of it for the caller and guarantee null termination
            तथ्य = SDL_malloc(*आकार + माप(Uint32));
            अगर (तथ्य) {
                SDL_memcpy(तथ्य, provided_तथ्य, *आकार);
                SDL_memset((Uint8 *)तथ्य + *आकार, 0, माप(Uint32));
            } अन्यथा {
                *आकार = 0;
            }
        }
    }
    वापस तथ्य;
}

व्योम *SDL_Get_Clipboard_तथ्य(स्थिर अक्षर *mime_type, माप_प्रकार *आकार)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार unused;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        वापस शून्य;
    }
    अगर (!आकार) {
        आकार = &unused;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *आकार = 0;

    अगर (_this->Get_Clipboard_तथ्य) {
        वापस _this->Get_Clipboard_तथ्य(_this, mime_type, आकार);
    } अन्यथा अगर (_this->GetClipboardText && SDL_IsTextMimeType(mime_type)) {
        अक्षर *text = _this->GetClipboardText(_this);
        अगर (text) {
            अगर (*text == '\0') {
                SDL_free(text);
                text = शून्य;
            } अन्यथा {
                *आकार = SDL_strlen(text);
            }
        }
        वापस text;
    } अन्यथा {
        वापस SDL_Get_Internal_Clipboard_तथ्य(_this, mime_type, आकार);
    }
}

bool SDL_Has_Internal_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type)
{
    माप_प्रकार i;

    क्रम (i = 0; i < _this->अंक_clipboard_mime_types; ++i) {
        अगर (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            वापस true;
        }
    }
    वापस false;
}

bool SDL_Has_Clipboard_तथ्य(स्थिर अक्षर *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        वापस SDL_InvalidParamError("mime_type");
    }

    अगर (_this->Has_Clipboard_तथ्य) {
        वापस _this->Has_Clipboard_तथ्य(_this, mime_type);
    } अन्यथा अगर (_this->HasClipboardText && SDL_IsTextMimeType(mime_type)) {
        वापस _this->HasClipboardText(_this);
    } अन्यथा {
        वापस SDL_Has_Internal_Clipboard_तथ्य(_this, mime_type);
    }
}

अक्षर **SDL_CopyClipboardMimeTypes(स्थिर अक्षर *स्थिर *clipboard_mime_types, माप_प्रकार अंक_mime_types, bool temporary)
{
    माप_प्रकार alloc_आकार = माप(अक्षर *);
    क्रम (माप_प्रकार i = 0; i < अंक_mime_types; i++) {
        alloc_आकार += माप(अक्षर *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    अक्षर *ret;
    अगर (temporary)
        ret = (अक्षर *)SDL_AllocateTemporaryMemory(alloc_आकार);
    अन्यथा
        ret = (अक्षर *)SDL_malloc(alloc_आकार);
    अगर (!ret) {
        वापस शून्य;
    }

    अक्षर **परिणाम = (अक्षर **)ret;
    ret += माप(अक्षर *) * (अंक_mime_types + 1);

    क्रम (माप_प्रकार i = 0; i < अंक_mime_types; i++) {
        परिणाम[i] = ret;

        स्थिर अक्षर *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        अक्षर c;
        करो {
            c = *ret++ = *mime_type++;
        } जबतक (c != '\0');
    }
    परिणाम[अंक_mime_types] = शून्य;

    वापस परिणाम;

}

अक्षर **SDL_GetClipboardMimeTypes(माप_प्रकार *अंक_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (अंक_mime_types) {
        *अंक_mime_types = 0;
    }

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }

    अगर (अंक_mime_types) {
        *अंक_mime_types = _this->अंक_clipboard_mime_types;
    }
    वापस SDL_CopyClipboardMimeTypes((स्थिर अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_IsTextMimeType(स्थिर अक्षर *mime_type)
{
    वापस (SDL_strncmp(mime_type, "text", 4) == 0);
}

अटल स्थिर अक्षर *स्थिर *SDL_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types)
{
    अगर (_this->GetTextMimeTypes) {
        वापस _this->GetTextMimeTypes(_this, अंक_mime_types);
    } अन्यथा {
        अटल स्थिर अक्षर *स्थिर text_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *अंक_mime_types = SDL_arraysize(text_mime_types);
        वापस text_mime_types;
    }
}

स्थिर व्योम * SDLCALL SDL_ClipboardTextCallback(व्योम *userdata, स्थिर अक्षर *mime_type, माप_प्रकार *आकार)
{
    अक्षर *text = (अक्षर *)userdata;
    अगर (text) {
        *आकार = SDL_strlen(text);
    } अन्यथा {
        *आकार = 0;
    }
    वापस text;
}

bool SDL_SetClipboardText(स्थिर अक्षर *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार अंक_mime_types;
    स्थिर अक्षर *स्थिर *text_mime_types;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    अगर (text && *text) {
        text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);

        वापस SDL_Set_Clipboard_तथ्य(SDL_ClipboardTextCallback, SDL_free, SDL_strdup(text), text_mime_types, अंक_mime_types);
    }
    वापस SDL_Clear_Clipboard_तथ्य();
}

अक्षर *SDL_GetClipboardText(व्योम)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार i, अंक_mime_types;
    स्थिर अक्षर *स्थिर *text_mime_types;
    माप_प्रकार लंबाई;
    अक्षर *text = शून्य;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस SDL_strdup("");
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    क्रम (i = 0; i < अंक_mime_types; ++i) {
        व्योम *clipdata = SDL_Get_Clipboard_तथ्य(text_mime_types[i], &लंबाई);
        अगर (clipdata) {
            text = (अक्षर *)clipdata;
            अवरोध;
        }
    }

    अगर (!text) {
        text = SDL_strdup("");
    }
    वापस text;
}

bool SDL_HasClipboardText(व्योम)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    माप_प्रकार i, अंक_mime_types;
    स्थिर अक्षर *स्थिर *text_mime_types;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    text_mime_types = SDL_GetTextMimeTypes(_this, &अंक_mime_types);
    क्रम (i = 0; i < अंक_mime_types; ++i) {
        अगर (SDL_Has_Clipboard_तथ्य(text_mime_types[i])) {
            वापस true;
        }
    }
    वापस false;
}

// Primary selection text

bool SDL_SetPrimarySelectionText(स्थिर अक्षर *text)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    अगर (!text) {
        text = "";
    }
    अगर (_this->SetPrimarySelectionText) {
        अगर (!_this->SetPrimarySelectionText(_this, text)) {
            वापस false;
        }
    } अन्यथा {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = SDL_strdup(text);
    }

    अक्षर **mime_types = SDL_CopyClipboardMimeTypes((स्थिर अक्षर **)_this->clipboard_mime_types, _this->अंक_clipboard_mime_types, true);
    अगर (!mime_types) {
        वापस SDL_SetError("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->अंक_clipboard_mime_types);
    वापस true;
}

अक्षर *SDL_GetPrimarySelectionText(व्योम)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस SDL_strdup("");
    }

    अगर (_this->GetPrimarySelectionText) {
        वापस _this->GetPrimarySelectionText(_this);
    } अन्यथा {
        स्थिर अक्षर *text = _this->primary_selection_text;
        अगर (!text) {
            text = "";
        }
        वापस SDL_strdup(text);
    }
}

bool SDL_HasPrimarySelectionText(व्योम)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    अगर (_this->HasPrimarySelectionText) {
        वापस _this->HasPrimarySelectionText(_this);
    } अन्यथा {
        अगर (_this->primary_selection_text && _this->primary_selection_text[0] != '\0') {
            वापस true;
        } अन्यथा {
            वापस false;
        }
    }
}

