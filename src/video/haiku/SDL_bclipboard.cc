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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#ضمن <unistd.h>
#ضمن <TypeConstants.h>

#ضمن "SDL_BWin.h"
#ضمن "../SDL_sysvideo.h"

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

منطقي HAIKU_مجموعه_Clipboard_متن(SDL_VideoDevice *_this, ثابت حرف *متن)
{
    BMessage *clip = عدم;
    إذا (be_clipboard->قفل()) {
        be_clipboard->Clear();
        إذا ((clip = be_clipboard->داده_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_درازی = 0;
            لكل (; متن[ascii_درازی] != 0; ++ascii_درازی) {}
            clip->جمع_کن_داده("text/plain", B_MIME_TYPE, متن, ascii_درازی);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    أرجع درست;
}

حرف *HAIKU_Get_Clipboard_متن(SDL_VideoDevice *_this) {
    BMessage *clip = عدم;
    ثابت حرف *متن = عدم;
    ssize_t درازی;
    حرف *نتیجه;
    إذا (be_clipboard->قفل()) {
        إذا ((clip = be_clipboard->داده_3())) {
            // Presumably the string of characters is ascii-format
            clip->پیدا_کن_داده("text/plain", B_MIME_TYPE, (ثابت فراغ **)&متن,
                &درازی);
        }
        be_clipboard->Unlock();
    }

    إذا (!متن) {
        نتیجه = SDL_strdup("");
    } وإلا {
        // Copy the data and pass on to SDL
        نتیجه = (حرف *)SDL_malloc((درازی + 1) * حجم(حرف));
        SDL_strlcpy(نتیجه, متن, درازی + 1);
    }

    أرجع نتیجه;
}

منطقي HAIKU_Has_Clipboard_متن(SDL_VideoDevice *_this) {
    منطقي نتیجه = خطأ;
    حرف *متن = HAIKU_Get_Clipboard_متن(_this);
    إذا (متن) {
        نتیجه = (متن[0] != '\0');
        SDL_free(متن);
    }
    أرجع نتیجه;
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU
