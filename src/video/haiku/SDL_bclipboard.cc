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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#अन्तर्भाव <unistd.h>
#अन्तर्भाव <TypeConstants.h>

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#ifdef __cplusplus
बाह्य "C" {
#endif

तार्किक HAIKU_SetClipboardText(SDL_VideoDevice *_this, अचर वर्ण *text)
{
    BMessage *clip = रिक्त;
    यदि (be_clipboard->Lock()) {
        be_clipboard->Clear();
        यदि ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            ssize_t asciiLength = 0;
            लागि (; text[asciiLength] != 0; ++asciiLength) {}
            clip->AddData("text/plain", B_MIME_TYPE, text, asciiLength);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    फर्काऊ सत्य;
}

वर्ण *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = रिक्त;
    अचर वर्ण *text = रिक्त;
    ssize_t length;
    वर्ण *result;
    यदि (be_clipboard->Lock()) {
        यदि ((clip = be_clipboard->Data())) {
            // Presumably the string of characters is ascii-format
            clip->FindData("text/plain", B_MIME_TYPE, (अचर शून्य **)&text,
                &length);
        }
        be_clipboard->Unlock();
    }

    यदि (!text) {
        result = SDL_strdup("");
    } अन्यथा {
        // Copy the data and pass on to SDL
        result = (वर्ण *)SDL_malloc((length + 1) * परिमाण(वर्ण));
        SDL_strlcpy(result, text, length + 1);
    }

    फर्काऊ result;
}

तार्किक HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    तार्किक result = असत्य;
    वर्ण *text = HAIKU_GetClipboardText(_this);
    यदि (text) {
        result = (text[0] != '\0');
        SDL_free(text);
    }
    फर्काऊ result;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
