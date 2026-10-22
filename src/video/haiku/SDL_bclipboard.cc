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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <TypeConstants.h>

#অন্তর্ভাব "SDL_BWin.h"
#অন্তর্ভাব "../SDL_sysvideo.h"

#ifdef __cplusplus
বাহ্যিক "C" {
#endif

যৌক্তিক HAIKU_SetClipboardText(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text)
{
    BMessage *clip = ফাঁকা;
    যদি (be_clipboard->Lock()) {
        be_clipboard->Clear();
        যদি ((clip = be_clipboard->তথ্য_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_দৈর্ঘ্য = 0;
            জন্য (; text[ascii_দৈর্ঘ্য] != 0; ++ascii_দৈর্ঘ্য) {}
            clip->Add_তথ্য("text/plain", B_MIME_TYPE, text, ascii_দৈর্ঘ্য);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ফেরত সত্য;
}

অক্ষর *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = ফাঁকা;
    ধ্রুবক অক্ষর *text = ফাঁকা;
    ssize_t দৈর্ঘ্য;
    অক্ষর *ফলাফল;
    যদি (be_clipboard->Lock()) {
        যদি ((clip = be_clipboard->তথ্য_3())) {
            // Presumably the string of characters is ascii-format
            clip->Find_তথ্য("text/plain", B_MIME_TYPE, (ধ্রুবক শূন্য **)&text,
                &দৈর্ঘ্য);
        }
        be_clipboard->Unlock();
    }

    যদি (!text) {
        ফলাফল = SDL_strdup("");
    } অন্যথা {
        // Copy the data and pass on to SDL
        ফলাফল = (অক্ষর *)SDL_malloc((দৈর্ঘ্য + 1) * আকার(অক্ষর));
        SDL_strlcpy(ফলাফল, text, দৈর্ঘ্য + 1);
    }

    ফেরত ফলাফল;
}

যৌক্তিক HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    যৌক্তিক ফলাফল = মিথ্যা;
    অক্ষর *text = HAIKU_GetClipboardText(_this);
    যদি (text) {
        ফলাফল = (text[0] != '\0');
        SDL_free(text);
    }
    ফেরত ফলাফল;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
