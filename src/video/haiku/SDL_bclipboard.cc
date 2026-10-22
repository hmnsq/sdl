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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <TypeConstants.h>

#অন্তর্ভাৱ "SDL_BWin.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"

#ifdef __cplusplus
বাহ্য "C" {
#endif

তার্কিক HAIKU_SetClipboardText(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *text)
{
    BMessage *clip = রিক্ত;
    যদি (be_clipboard->Lock()) {
        be_clipboard->Clear();
        যদি ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            বাবে (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    ঘূৰাই সঁচা;
}

ৱর্ণ *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = রিক্ত;
    ধ্রুৱ ৱর্ণ *text = রিক্ত;
    ssize_t length;
    ৱর্ণ *result;
    যদি (be_clipboard->Lock()) {
        যদি ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (ধ্রুৱ শূন্য **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    যদি (!text) {
        result = SDL_strdup("");
    } অন্যথা {
        // Copy the data and pass on to SDL
        result = (ৱর্ণ *)SDL_malloc((length + 1) * পরিমাণ(ৱর্ণ));
        SDL_strlcpy(result, text, length + 1);
    }

    ঘূৰাই result;
}

তার্কিক HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    তার্কিক result = মিছা;
    ৱর্ণ *text = HAIKU_GetClipboardText(_this);
    যদি (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    ঘূৰাই result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
