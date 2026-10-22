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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_clipboard_c.h"
#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "../events/SDL_events_c.h"
#అన్తర్భావ "../events/SDL_clipboardevents_c.h"

శూన్య SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->clipboard_mime_types) {
        కొరకు (size_t i = 0; i < _this->అంకె_clipboard_mime_types; ++i) {
            SDL_free(_this->clipboard_mime_types[i]);
        }
        SDL_free(_this->clipboard_mime_types);
        _this->clipboard_mime_types = ఖాళీ;
        _this->అంకె_clipboard_mime_types = 0;
    }
}


శూన్య SDL_Cancel_Clipboard_దత్తాంశం(Uint32 sequence)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి;
    }

    ఒకవేళ (sequence && sequence != _this->clipboard_sequence) {
        // This clipboard data was already canceled
        తిరిగి;
    }

    ఒకవేళ (_this->clipboard_cleanup) {
        _this->clipboard_cleanup(_this->clipboard_userdata);
    }

    SDL_FreeClipboardMimeTypes(_this);

    _this->clipboard_callback = ఖాళీ;
    _this->clipboard_cleanup = ఖాళీ;
    _this->clipboard_userdata = ఖాళీ;
}

bool SDL_SaveClipboardMimeTypes(స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types, size_t అంకె_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    SDL_FreeClipboardMimeTypes(_this);

    ఒకవేళ (mime_types && అంకె_mime_types > 0) {
        size_t అంకె_allocated = 0;

        _this->clipboard_mime_types = (అక్షరం **)SDL_malloc(అంకె_mime_types * పరిమాణం(అక్షరం *));
        ఒకవేళ (_this->clipboard_mime_types) {
            కొరకు (size_t i = 0; i < అంకె_mime_types; ++i) {
                _this->clipboard_mime_types[i] = SDL_strdup(mime_types[i]);
                ఒకవేళ (_this->clipboard_mime_types[i]) {
                    ++అంకె_allocated;
                }
            }
        }
        ఒకవేళ (అంకె_allocated < అంకె_mime_types) {
            SDL_FreeClipboardMimeTypes(_this);
            తిరిగి false;
        }
        _this->అంకె_clipboard_mime_types = అంకె_mime_types;
    }
    తిరిగి true;
}

bool SDL_సమితి_Clipboard_దత్తాంశం(SDL_Clipboard_దత్తాంశం_Callback callback, SDL_ClipboardCleanupCallback cleanup, శూన్య *userdata, స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types, size_t అంకె_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    // Parameter validation
    ఒకవేళ (!((callback && mime_types && అంకె_mime_types > 0) ||
          (!callback && !mime_types && అంకె_mime_types == 0))) {
        తిరిగి SDL_సమితి_Error("Invalid parameters");
    }

    SDL_Cancel_Clipboard_దత్తాంశం(0);

    ++_this->clipboard_sequence;
    ఒకవేళ (!_this->clipboard_sequence) {
        _this->clipboard_sequence = 1;
    }
    _this->clipboard_callback = callback;
    _this->clipboard_cleanup = cleanup;
    _this->clipboard_userdata = userdata;

    ఒకవేళ (!SDL_SaveClipboardMimeTypes(mime_types, అంకె_mime_types)) {
        SDL_Clear_Clipboard_దత్తాంశం();
        తిరిగి false;
    }

    ఒకవేళ (_this->సమితి_Clipboard_దత్తాంశం) {
        ఒకవేళ (!_this->సమితి_Clipboard_దత్తాంశం(_this)) {
            తిరిగి false;
        }
    } లేకపోతే ఒకవేళ (_this->సమితి_Clipboard_పాఠ్యం) {
        అక్షరం *పాఠ్యం = ఖాళీ;
        size_t కొలత;

        కొరకు (size_t i = 0; i < అంకె_mime_types; ++i) {
            స్థిరరాశి అక్షరం *mime_type = _this->clipboard_mime_types[i];
            ఒకవేళ (SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
                స్థిరరాశి శూన్య *దత్తాంశం = _this->clipboard_callback(_this->clipboard_userdata, mime_type, &కొలత);
                ఒకవేళ (దత్తాంశం) {
                    పాఠ్యం = (అక్షరం *)SDL_malloc(కొలత + 1);
                    SDL_memcpy(పాఠ్యం, దత్తాంశం, కొలత);
                    పాఠ్యం[కొలత] = '\0';
                    ఒకవేళ (!_this->సమితి_Clipboard_పాఠ్యం(_this, పాఠ్యం)) {
                        SDL_free(పాఠ్యం);
                        తిరిగి false;
                    }
                    ఆపు;
                }
            }
        }
        ఒకవేళ (పాఠ్యం) {
            SDL_free(పాఠ్యం);
        } లేకపోతే {
            ఒకవేళ (!_this->సమితి_Clipboard_పాఠ్యం(_this, "")) {
                తిరిగి false;
            }
        }
    }

    అక్షరం **mime_types_copy = SDL_CopyClipboardMimeTypes(mime_types, అంకె_mime_types, true);
    ఒకవేళ (!mime_types_copy) {
        తిరిగి SDL_సమితి_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types_copy, అంకె_mime_types);
    తిరిగి true;
}

bool SDL_Clear_Clipboard_దత్తాంశం(శూన్య)
{
    తిరిగి SDL_సమితి_Clipboard_దత్తాంశం(ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, 0);
}

శూన్య *SDL_Get_అంతర్గత_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత)
{
    శూన్య *దత్తాంశం = ఖాళీ;

    ఒకవేళ (_this->clipboard_callback) {
        ఒకవేళ (!SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type)) {
            // The callback hasn't advertised that it can handle this mime type
            తిరిగి ఖాళీ;
        }

        స్థిరరాశి శూన్య *provided_దత్తాంశం = _this->clipboard_callback(_this->clipboard_userdata, mime_type, కొలత);
        ఒకవేళ (provided_దత్తాంశం) {
            // Make a copy of it for the caller and guarantee null termination
            దత్తాంశం = SDL_malloc(*కొలత + పరిమాణం(Uint32));
            ఒకవేళ (దత్తాంశం) {
                SDL_memcpy(దత్తాంశం, provided_దత్తాంశం, *కొలత);
                SDL_memset((Uint8 *)దత్తాంశం + *కొలత, 0, పరిమాణం(Uint32));
            } లేకపోతే {
                *కొలత = 0;
            }
        }
    }
    తిరిగి దత్తాంశం;
}

శూన్య *SDL_Get_Clipboard_దత్తాంశం(స్థిరరాశి అక్షరం *mime_type, size_t *కొలత)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t వాడని;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }

    CHECK_PARAM(!mime_type) {
        SDL_InvalidParamError("mime_type");
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!కొలత) {
        కొలత = &వాడని;
    }

    // Initialize size to empty, so implementations don't have to worry about it
    *కొలత = 0;

    ఒకవేళ (_this->Get_Clipboard_దత్తాంశం) {
        తిరిగి _this->Get_Clipboard_దత్తాంశం(_this, mime_type, కొలత);
    } లేకపోతే ఒకవేళ (_this->Get_Clipboard_పాఠ్యం && SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
        అక్షరం *పాఠ్యం = _this->Get_Clipboard_పాఠ్యం(_this);
        ఒకవేళ (పాఠ్యం) {
            ఒకవేళ (*పాఠ్యం == '\0') {
                SDL_free(పాఠ్యం);
                పాఠ్యం = ఖాళీ;
            } లేకపోతే {
                *కొలత = SDL_strlen(పాఠ్యం);
            }
        }
        తిరిగి పాఠ్యం;
    } లేకపోతే {
        తిరిగి SDL_Get_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type, కొలత);
    }
}

bool SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type)
{
    size_t i;

    కొరకు (i = 0; i < _this->అంకె_clipboard_mime_types; ++i) {
        ఒకవేళ (SDL_strcmp(mime_type, _this->clipboard_mime_types[i]) == 0) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

bool SDL_Has_Clipboard_దత్తాంశం(స్థిరరాశి అక్షరం *mime_type)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    CHECK_PARAM(!mime_type) {
        తిరిగి SDL_InvalidParamError("mime_type");
    }

    ఒకవేళ (_this->Has_Clipboard_దత్తాంశం) {
        తిరిగి _this->Has_Clipboard_దత్తాంశం(_this, mime_type);
    } లేకపోతే ఒకవేళ (_this->Has_Clipboard_పాఠ్యం && SDL_Is_పాఠ్యం_Mime_Type(mime_type)) {
        తిరిగి _this->Has_Clipboard_పాఠ్యం(_this);
    } లేకపోతే {
        తిరిగి SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(_this, mime_type);
    }
}

అక్షరం **SDL_CopyClipboardMimeTypes(స్థిరరాశి అక్షరం *స్థిరరాశి *clipboard_mime_types, size_t అంకె_mime_types, bool temporary)
{
    size_t alloc_కొలత = పరిమాణం(అక్షరం *);
    కొరకు (size_t i = 0; i < అంకె_mime_types; i++) {
        alloc_కొలత += పరిమాణం(అక్షరం *) + SDL_strlen(clipboard_mime_types[i]) + 1;
    }

    అక్షరం *ret;
    ఒకవేళ (temporary)
        ret = (అక్షరం *)SDL_Allocate_Temporary_జ్ఞాపకం(alloc_కొలత);
    లేకపోతే
        ret = (అక్షరం *)SDL_malloc(alloc_కొలత);
    ఒకవేళ (!ret) {
        తిరిగి ఖాళీ;
    }

    అక్షరం **ఫలితం = (అక్షరం **)ret;
    ret += పరిమాణం(అక్షరం *) * (అంకె_mime_types + 1);

    కొరకు (size_t i = 0; i < అంకె_mime_types; i++) {
        ఫలితం[i] = ret;

        స్థిరరాశి అక్షరం *mime_type = clipboard_mime_types[i];
        // Copy the whole string including the terminating null char
        అక్షరం c;
        చేయి {
            c = *ret++ = *mime_type++;
        } అయితే (c != '\0');
    }
    ఫలితం[అంకె_mime_types] = ఖాళీ;

    తిరిగి ఫలితం;

}

అక్షరం **SDL_GetClipboardMimeTypes(size_t *అంకె_mime_types)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (అంకె_mime_types) {
        *అంకె_mime_types = 0;
    }

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (అంకె_mime_types) {
        *అంకె_mime_types = _this->అంకె_clipboard_mime_types;
    }
    తిరిగి SDL_CopyClipboardMimeTypes((స్థిరరాశి అక్షరం **)_this->clipboard_mime_types, _this->అంకె_clipboard_mime_types, false);
}

// Clipboard text

bool SDL_Is_పాఠ్యం_Mime_Type(స్థిరరాశి అక్షరం *mime_type)
{
    తిరిగి (SDL_strncmp(mime_type, "text", 4) == 0);
}

స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి *SDL_Get_పాఠ్యం_Mime_Types(SDL_VideoDevice *_this, size_t *అంకె_mime_types)
{
    ఒకవేళ (_this->Get_పాఠ్యం_Mime_Types) {
        తిరిగి _this->Get_పాఠ్యం_Mime_Types(_this, అంకె_mime_types);
    } లేకపోతే {
        స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి పాఠ్యం_mime_types[] = {
            "text/plain;charset=utf-8"
        };

        *అంకె_mime_types = SDL_arraysize(పాఠ్యం_mime_types);
        తిరిగి పాఠ్యం_mime_types;
    }
}

స్థిరరాశి శూన్య * SDLCALL SDL_Clipboard_పాఠ్యం_Callback(శూన్య *userdata, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత)
{
    అక్షరం *పాఠ్యం = (అక్షరం *)userdata;
    ఒకవేళ (పాఠ్యం) {
        *కొలత = SDL_strlen(పాఠ్యం);
    } లేకపోతే {
        *కొలత = 0;
    }
    తిరిగి పాఠ్యం;
}

bool SDL_సమితి_Clipboard_పాఠ్యం(స్థిరరాశి అక్షరం *పాఠ్యం)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t అంకె_mime_types;
    స్థిరరాశి అక్షరం *స్థిరరాశి *పాఠ్యం_mime_types;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    ఒకవేళ (పాఠ్యం && *పాఠ్యం) {
        పాఠ్యం_mime_types = SDL_Get_పాఠ్యం_Mime_Types(_this, &అంకె_mime_types);

        తిరిగి SDL_సమితి_Clipboard_దత్తాంశం(SDL_Clipboard_పాఠ్యం_Callback, SDL_free, SDL_strdup(పాఠ్యం), పాఠ్యం_mime_types, అంకె_mime_types);
    }
    తిరిగి SDL_Clear_Clipboard_దత్తాంశం();
}

అక్షరం *SDL_Get_Clipboard_పాఠ్యం(శూన్య)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, అంకె_mime_types;
    స్థిరరాశి అక్షరం *స్థిరరాశి *పాఠ్యం_mime_types;
    size_t నిడివి;
    అక్షరం *పాఠ్యం = ఖాళీ;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి SDL_strdup("");
    }

    పాఠ్యం_mime_types = SDL_Get_పాఠ్యం_Mime_Types(_this, &అంకె_mime_types);
    కొరకు (i = 0; i < అంకె_mime_types; ++i) {
        శూన్య *clipdata = SDL_Get_Clipboard_దత్తాంశం(పాఠ్యం_mime_types[i], &నిడివి);
        ఒకవేళ (clipdata) {
            పాఠ్యం = (అక్షరం *)clipdata;
            ఆపు;
        }
    }

    ఒకవేళ (!పాఠ్యం) {
        పాఠ్యం = SDL_strdup("");
    }
    తిరిగి పాఠ్యం;
}

bool SDL_Has_Clipboard_పాఠ్యం(శూన్య)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    size_t i, అంకె_mime_types;
    స్థిరరాశి అక్షరం *స్థిరరాశి *పాఠ్యం_mime_types;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    పాఠ్యం_mime_types = SDL_Get_పాఠ్యం_Mime_Types(_this, &అంకె_mime_types);
    కొరకు (i = 0; i < అంకె_mime_types; ++i) {
        ఒకవేళ (SDL_Has_Clipboard_దత్తాంశం(పాఠ్యం_mime_types[i])) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

// Primary selection text

bool SDL_సమితి_Primary_Selection_పాఠ్యం(స్థిరరాశి అక్షరం *పాఠ్యం)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    ఒకవేళ (!పాఠ్యం) {
        పాఠ్యం = "";
    }
    ఒకవేళ (_this->సమితి_Primary_Selection_పాఠ్యం) {
        ఒకవేళ (!_this->సమితి_Primary_Selection_పాఠ్యం(_this, పాఠ్యం)) {
            తిరిగి false;
        }
    } లేకపోతే {
        SDL_free(_this->primary_selection_పాఠ్యం);
        _this->primary_selection_పాఠ్యం = SDL_strdup(పాఠ్యం);
    }

    అక్షరం **mime_types = SDL_CopyClipboardMimeTypes((స్థిరరాశి అక్షరం **)_this->clipboard_mime_types, _this->అంకె_clipboard_mime_types, true);
    ఒకవేళ (!mime_types) {
        తిరిగి SDL_సమితి_Error("unable to copy current mime types");
	}
    SDL_SendClipboardUpdate(true, mime_types, _this->అంకె_clipboard_mime_types);
    తిరిగి true;
}

అక్షరం *SDL_Get_Primary_Selection_పాఠ్యం(శూన్య)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి SDL_strdup("");
    }

    ఒకవేళ (_this->Get_Primary_Selection_పాఠ్యం) {
        తిరిగి _this->Get_Primary_Selection_పాఠ్యం(_this);
    } లేకపోతే {
        స్థిరరాశి అక్షరం *పాఠ్యం = _this->primary_selection_పాఠ్యం;
        ఒకవేళ (!పాఠ్యం) {
            పాఠ్యం = "";
        }
        తిరిగి SDL_strdup(పాఠ్యం);
    }
}

bool SDL_Has_Primary_Selection_పాఠ్యం(శూన్య)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    ఒకవేళ (_this->Has_Primary_Selection_పాఠ్యం) {
        తిరిగి _this->Has_Primary_Selection_పాఠ్యం(_this);
    } లేకపోతే {
        ఒకవేళ (_this->primary_selection_పాఠ్యం && _this->primary_selection_పాఠ్యం[0] != '\0') {
            తిరిగి true;
        } లేకపోతే {
            తిరిగి false;
        }
    }
}

