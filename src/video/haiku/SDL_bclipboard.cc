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

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#समावेश <unistd.h>
#समावेश <TypeConstants.h>

#समावेश "SDL_BWin.h"
#समावेश "../SDL_sysvideo.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

bool HAIKU_SetClipboardText(SDL_VideoDevice *_this, स्थिर अक्षर *text)
{
    BMessage *clip = शून्य;
    अगर (be_clipboard->Lock()) {
        be_clipboard->Clear();
        अगर ((clip = be_clipboard->तथ्य_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_लंबाई = 0;
            क्रम (; text[ascii_लंबाई] != 0; ++ascii_लंबाई) {}
            clip->Add_तथ्य("text/plain", B_MIME_TYPE, text, ascii_लंबाई);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    वापस true;
}

अक्षर *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = शून्य;
    स्थिर अक्षर *text = शून्य;
    ssize_t लंबाई;
    अक्षर *परिणाम;
    अगर (be_clipboard->Lock()) {
        अगर ((clip = be_clipboard->तथ्य_3())) {
            // Presumably the string of characters is ascii-format
            clip->Find_तथ्य("text/plain", B_MIME_TYPE, (स्थिर व्योम **)&text,
                &लंबाई);
        }
        be_clipboard->Unlock();
    }

    अगर (!text) {
        परिणाम = SDL_strdup("");
    } अन्यथा {
        // Copy the data and pass on to SDL
        परिणाम = (अक्षर *)SDL_malloc((लंबाई + 1) * माप(अक्षर));
        SDL_strlcpy(परिणाम, text, लंबाई + 1);
    }

    वापस परिणाम;
}

bool HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    bool परिणाम = false;
    अक्षर *text = HAIKU_GetClipboardText(_this);
    अगर (text) {
        परिणाम = (text[0] != '\0');
        SDL_free(text);
    }
    वापस परिणाम;
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU
