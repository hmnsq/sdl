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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#شامل <unistd.h>
#شامل <TypeConstants.h>

#شامل "SDL_BWin.h"
#شامل "../SDL_sysvideo.h"

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

منطقی HAIKU_سیٹ_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    BMessage *clip = تہی;
    اگر (be_clipboard->تالا()) {
        be_clipboard->Clear();
        اگر ((clip = be_clipboard->ڈیٹا_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_لمبائی = 0;
            برائے (; متن[ascii_لمبائی] != 0; ++ascii_لمبائی) {}
            clip->جوڑو_ڈیٹا("text/plain", B_MIME_TYPE, متن, ascii_لمبائی);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    واپس سچ;
}

حرف *HAIKU_Get_Clipboard_متن(SDL_VideoDevice *_this) {
    BMessage *clip = تہی;
    ثابت حرف *متن = تہی;
    ssize_t لمبائی;
    حرف *نتیجہ;
    اگر (be_clipboard->تالا()) {
        اگر ((clip = be_clipboard->ڈیٹا_3())) {
            // Presumably the string of characters is ascii-format
            clip->ڈھونڈو_ڈیٹا("text/plain", B_MIME_TYPE, (ثابت خالی **)&متن,
                &لمبائی);
        }
        be_clipboard->Unlock();
    }

    اگر (!متن) {
        نتیجہ = SDL_strdup("");
    } ورنہ {
        // Copy the data and pass on to SDL
        نتیجہ = (حرف *)SDL_malloc((لمبائی + 1) * حجم(حرف));
        SDL_strlcpy(نتیجہ, متن, لمبائی + 1);
    }

    واپس نتیجہ;
}

منطقی HAIKU_Has_Clipboard_متن(SDL_VideoDevice *_this) {
    منطقی نتیجہ = جھوٹ;
    حرف *متن = HAIKU_Get_Clipboard_متن(_this);
    اگر (متن) {
        نتیجہ = (متن[0] != '\0');
        SDL_free(متن);
    }
    واپس نتیجہ;
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU
