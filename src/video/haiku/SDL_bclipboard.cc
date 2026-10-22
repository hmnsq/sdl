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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <TypeConstants.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_Clipboard_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    BMessage *clip = ਨਿਰਾ;
    ਜੇ (be_clipboard->ਤਾਲਾ()) {
        be_clipboard->Clear();
        ਜੇ ((clip = be_clipboard->ਅੰਕੜੇ_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_ਲੰਮਾਈ = 0;
            ਲਈ (; ਪਾਠ[ascii_ਲੰਮਾਈ] != 0; ++ascii_ਲੰਮਾਈ) {}
            clip->ਜੋੜੋ_ਅੰਕੜੇ("text/plain", B_MIME_TYPE, ਪਾਠ, ascii_ਲੰਮਾਈ);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ਵਾਪਸ ਸੱਚ;
}

ਅੱਖਰ *HAIKU_Get_Clipboard_ਪਾਠ(SDL_VideoDevice *_this) {
    BMessage *clip = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *ਪਾਠ = ਨਿਰਾ;
    ssize_t ਲੰਮਾਈ;
    ਅੱਖਰ *ਨਤੀਜਾ;
    ਜੇ (be_clipboard->ਤਾਲਾ()) {
        ਜੇ ((clip = be_clipboard->ਅੰਕੜੇ_3())) {
            // Presumably the string of characters is ascii-format
            clip->ਲੱਭੋ_ਅੰਕੜੇ("text/plain", B_MIME_TYPE, (ਅਚਲ ਖਾਲੀ **)&ਪਾਠ,
                &ਲੰਮਾਈ);
        }
        be_clipboard->Unlock();
    }

    ਜੇ (!ਪਾਠ) {
        ਨਤੀਜਾ = SDL_strdup("");
    } ਨਹੀਂਤਾਂ {
        // Copy the data and pass on to SDL
        ਨਤੀਜਾ = (ਅੱਖਰ *)SDL_malloc((ਲੰਮਾਈ + 1) * ਆਕਾਰ(ਅੱਖਰ));
        SDL_strlcpy(ਨਤੀਜਾ, ਪਾਠ, ਲੰਮਾਈ + 1);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਤਾਰਕਿਕ HAIKU_Has_Clipboard_ਪਾਠ(SDL_VideoDevice *_this) {
    ਤਾਰਕਿਕ ਨਤੀਜਾ = ਝੂਠ;
    ਅੱਖਰ *ਪਾਠ = HAIKU_Get_Clipboard_ਪਾਠ(_this);
    ਜੇ (ਪਾਠ) {
        ਨਤੀਜਾ = (ਪਾਠ[0] != '\0');
        SDL_free(ਪਾਠ);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU
