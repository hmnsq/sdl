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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <TypeConstants.h>

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

ತಾರ್ಕಿಕ HAIKU_SetClipboardText(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text)
{
    BMessage *clip = ರಿಕ್ತ;
    ಯದಿ (be_clipboard->Lock()) {
        be_clipboard->Clear();
        ಯದಿ ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            ಪ್ರತಿ (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ವರ್ಣ *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = ರಿಕ್ತ;
    ಧ್ರುವ ವರ್ಣ *text = ರಿಕ್ತ;
    ssize_t length;
    ವರ್ಣ *result;
    ಯದಿ (be_clipboard->Lock()) {
        ಯದಿ ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (ಧ್ರುವ ಶೂನ್ಯ **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    ಯದಿ (!text) {
        result = SDL_strdup("");
    } ಅನ್ಯಥಾ {
        // Copy the data and pass on to SDL
        result = (ವರ್ಣ *)SDL_malloc((length + 1) * ಪರಿಮಾಣ(ವರ್ಣ));
        SDL_strlcpy(result, text, length + 1);
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

ತಾರ್ಕಿಕ HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    ತಾರ್ಕಿಕ result = ಅಸತ್ಯ;
    ವರ್ಣ *text = HAIKU_GetClipboardText(_this);
    ಯದಿ (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
