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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#अन्तर्भाव <unistd.h>
#अन्तर्भाव <TypeConstants.h>

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

तार्किक HAIKU_समुच्चयः_Clipboard_Text(SDL_VideoDevice *_this, ध्रुव वर्ण *text)
{
    BMessage *clip = रिक्त;
    यदि (be_clipboard->तालकम्()) {
        be_clipboard->Clear();
        यदि ((clip = be_clipboard->दत्त_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_दीर्घता = 0;
            प्रति (; text[ascii_दीर्घता] != 0; ++ascii_दीर्घता) {}
            clip->सङ्कलय_दत्त("text/plain", B_MIME_TYPE, text, ascii_दीर्घता);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    प्रत्यागम सत्य;
}

वर्ण *HAIKU_GetClipboardText(SDL_VideoDevice *_this) {
    BMessage *clip = रिक्त;
    ध्रुव वर्ण *text = रिक्त;
    ssize_t दीर्घता;
    वर्ण *परिणाम;
    यदि (be_clipboard->तालकम्()) {
        यदि ((clip = be_clipboard->दत्त_3())) {
            // Presumably the string of characters is ascii-format
            clip->Find_दत्त("text/plain", B_MIME_TYPE, (ध्रुव शून्य **)&text,
                &दीर्घता);
        }
        be_clipboard->Unlock();
    }

    यदि (!text) {
        परिणाम = SDL_strdup("");
    } अन्यथा {
        // Copy the data and pass on to SDL
        परिणाम = (वर्ण *)SDL_malloc((दीर्घता + 1) * परिमाण(वर्ण));
        SDL_strlcpy(परिणाम, text, दीर्घता + 1);
    }

    प्रत्यागम परिणाम;
}

तार्किक HAIKU_HasClipboardText(SDL_VideoDevice *_this) {
    तार्किक परिणाम = असत्य;
    वर्ण *text = HAIKU_GetClipboardText(_this);
    यदि (text) {
        परिणाम = (text[0] != '\0');
        SDL_free(text);
    }
    प्रत्यागम परिणाम;
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU
