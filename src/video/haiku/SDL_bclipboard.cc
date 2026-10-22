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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <TypeConstants.h>

#ଅନ୍ତର୍ଭାଵ "SDL_BWin.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

ତାର୍କିକ HAIKU_SetClipboardText(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text)
{
    BMessage *clip = ଖାଲି;
    ଯଦି (be_clipboard->Lock()) {
        be_clipboard->Clear();
        ଯଦି ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            ପାଇଁ (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଅକ୍ଷର *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = ଖାଲି;
    ଅଚଳ ଅକ୍ଷର *text = ଖାଲି;
    ssize_t length;
    ଅକ୍ଷର *result;
    ଯଦି (be_clipboard->Lock()) {
        ଯଦି ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (ଅଚଳ ଶୂନ୍ୟ **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    ଯଦି (!text) {
        result = SDL_strdup("");
    } ଅନ୍ୟଥା {
        // Copy the data and pass on to SDL
        result = (ଅକ୍ଷର *)SDL_malloc((length + 1) * ଆକାର(ଅକ୍ଷର));
        SDL_strlcpy(result, text, length + 1);
    }

    ଫେରନ୍ତୁ result;
}

ତାର୍କିକ HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    ତାର୍କିକ result = ମିଥ୍ୟା;
    ଅକ୍ଷର *text = HAIKU_GetClipboardText(_this);
    ଯଦି (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    ଫେରନ୍ତୁ result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
