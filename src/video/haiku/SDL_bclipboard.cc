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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <TypeConstants.h>

#அந்தர்பாவ "SDL_BWin.h"
#அந்தர்பாவ "../SDL_sysvideo.h"

#ifdef __cplusplus
வெளி "C" {
#endif

தருக்க HAIKU_SetClipboardText(SDL_VideoDevice *_this, மாறிலி எழுத்து *text)
{
    BMessage *clip = வெற்று;
    எனில் (be_clipboard->Lock()) {
        be_clipboard->Clear();
        எனில் ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            க்கு (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    திரும்பு உண்மை;
}

எழுத்து *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = வெற்று;
    மாறிலி எழுத்து *text = வெற்று;
    ssize_t length;
    எழுத்து *result;
    எனில் (be_clipboard->Lock()) {
        எனில் ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (மாறிலி வெறுமை **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    எனில் (!text) {
        result = SDL_strdup("");
    } இல்லையெனில் {
        // Copy the data and pass on to SDL
        result = (எழுத்து *)SDL_malloc((length + 1) * அளவு(எழுத்து));
        SDL_strlcpy(result, text, length + 1);
    }

    திரும்பு result;
}

தருக்க HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    தருக்க result = பொய்;
    எழுத்து *text = HAIKU_GetClipboardText(_this);
    எனில் (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    திரும்பு result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
