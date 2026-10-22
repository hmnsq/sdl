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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <TypeConstants.h>

#അന്തര്ഭാവ "SDL_BWin.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

തർക്കം HAIKU_SetClipboardText(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *text)
{
    BMessage *clip = ശൂന്യ;
    എങ്കിൽ (be_clipboard->Lock()) {
        be_clipboard->Clear();
        എങ്കിൽ ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            വേണ്ടി (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    തിരികെ സത്യം;
}

അക്ഷരം *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *text = ശൂന്യ;
    ssize_t length;
    അക്ഷരം *result;
    എങ്കിൽ (be_clipboard->Lock()) {
        എങ്കിൽ ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (സ്ഥിരം ശൂന്യം **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    എങ്കിൽ (!text) {
        result = SDL_strdup("");
    } അല്ലെങ്കിൽ {
        // Copy the data and pass on to SDL
        result = (അക്ഷരം *)SDL_malloc((length + 1) * വലുപ്പം(അക്ഷരം));
        SDL_strlcpy(result, text, length + 1);
    }

    തിരികെ result;
}

തർക്കം HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    തർക്കം result = അസത്യം;
    അക്ഷരം *text = HAIKU_GetClipboardText(_this);
    എങ്കിൽ (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    തിരികെ result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
