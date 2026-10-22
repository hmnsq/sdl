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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <TypeConstants.h>

#અન્તર્ભાવ "SDL_BWin.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"

#ifdef __cplusplus
બાહ્ય "C" {
#endif

તાર્કિક HAIKU_SetClipboardText(SDL_VideoDevice *_this, અચલ અક્ષર *text)
{
    BMessage *clip = ખાલી;
    જો (be_clipboard->Lock()) {
        be_clipboard->Clear();
        જો ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            માટે (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    પાછા સાચું;
}

અક્ષર *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = ખાલી;
    અચલ અક્ષર *text = ખાલી;
    ssize_t length;
    અક્ષર *result;
    જો (be_clipboard->Lock()) {
        જો ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (અચલ શૂન્ય **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    જો (!text) {
        result = SDL_strdup("");
    } નહીંતર {
        // Copy the data and pass on to SDL
        result = (અક્ષર *)SDL_malloc((length + 1) * કદ(અક્ષર));
        SDL_strlcpy(result, text, length + 1);
    }

    પાછા result;
}

તાર્કિક HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    તાર્કિક result = ખોટું;
    અક્ષર *text = HAIKU_GetClipboardText(_this);
    જો (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    પાછા result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
