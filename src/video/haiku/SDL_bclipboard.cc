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

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#شامل <unistd.h>
#شامل <TypeConstants.h>

#شامل "SDL_BWin.h"
#شامل "../SDL_sysvideo.h"

#ifdef __cplusplus
بیرونی "C" {
#endif

منطقی HAIKU_SetClipboardText(SDL_VideoDevice *_this, ثابت نویسه *text)
{
    BMessage *clip = پوچ;
    اگر (be_clipboard->Lock()) {
        be_clipboard->Clear();
        اگر ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            برای (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    بازگشت درست;
}

نویسه *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = پوچ;
    ثابت نویسه *text = پوچ;
    ssize_t length;
    نویسه *result;
    اگر (be_clipboard->Lock()) {
        اگر ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (ثابت تهی **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    اگر (!text) {
        result = SDL_strdup("");
    } وگرنه {
        // Copy the data and pass on to SDL
        result = (نویسه *)SDL_malloc((length + 1) * اندازه(نویسه));
        SDL_strlcpy(result, text, length + 1);
    }

    بازگشت result;
}

منطقی HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    منطقی result = نادرست;
    نویسه *text = HAIKU_GetClipboardText(_this);
    اگر (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    بازگشت result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
