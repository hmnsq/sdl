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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <TypeConstants.h>

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ತಾರ್ಕಿಕ HAIKU_ಗಣ_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    BMessage *clip = ಖಾಲಿ;
    ಆದರೆ (be_clipboard->ಬೀಗ()) {
        be_clipboard->Clear();
        ಆದರೆ ((clip = be_clipboard->ದತ್ತಾಂಶ_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_ಉದ್ದಳತೆ = 0;
            ಗಾಗಿ (; ಪಠ್ಯ[ascii_ಉದ್ದಳತೆ] != 0; ++ascii_ಉದ್ದಳತೆ) {}
            clip->ಕೂಡಿಸು_ದತ್ತಾಂಶ("text/plain", B_MIME_TYPE, ಪಠ್ಯ, ascii_ಉದ್ದಳತೆ);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಅಕ್ಷರ *HAIKU_Get_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this) {
    BMessage *clip = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ = ಖಾಲಿ;
    ssize_t ಉದ್ದಳತೆ;
    ಅಕ್ಷರ *ಫಲಿತಾಂಶ;
    ಆದರೆ (be_clipboard->ಬೀಗ()) {
        ಆದರೆ ((clip = be_clipboard->ದತ್ತಾಂಶ_3())) {
            // Presumably the string of characters is ascii-format
            clip->ಕಂಡುಹಿಡಿ_ದತ್ತಾಂಶ("text/plain", B_MIME_TYPE, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ **)&ಪಠ್ಯ,
                &ಉದ್ದಳತೆ);
        }
        be_clipboard->Unlock();
    }

    ಆದರೆ (!ಪಠ್ಯ) {
        ಫಲಿತಾಂಶ = SDL_strdup("");
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Copy the data and pass on to SDL
        ಫಲಿತಾಂಶ = (ಅಕ್ಷರ *)SDL_malloc((ಉದ್ದಳತೆ + 1) * ಗಾತ್ರ(ಅಕ್ಷರ));
        SDL_strlcpy(ಫಲಿತಾಂಶ, ಪಠ್ಯ, ಉದ್ದಳತೆ + 1);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ತಾರ್ಕಿಕ HAIKU_Has_Clipboard_ಪಠ್ಯ(SDL_VideoDevice *_this) {
    ತಾರ್ಕಿಕ ಫಲಿತಾಂಶ = ಸುಳ್ಳು;
    ಅಕ್ಷರ *ಪಠ್ಯ = HAIKU_Get_Clipboard_ಪಠ್ಯ(_this);
    ಆದರೆ (ಪಠ್ಯ) {
        ಫಲಿತಾಂಶ = (ಪಠ್ಯ[0] != '\0');
        SDL_free(ಪಠ್ಯ);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU
