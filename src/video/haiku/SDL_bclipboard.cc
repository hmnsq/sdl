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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU

// BWindow based clipboard implementation

#అన్తర్భావ <unistd.h>
#అన్తర్భావ <TypeConstants.h>

#అన్తర్భావ "SDL_BWin.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

తార్కిక HAIKU_సమితి_Clipboard_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    BMessage *clip = ఖాళీ;
    ఒకవేళ (be_clipboard->తాళం()) {
        be_clipboard->Clear();
        ఒకవేళ ((clip = be_clipboard->దత్తాంశం_3())) {
            // Presumably the string of characters is ascii-format
            ssize_t ascii_నిడివి = 0;
            కొరకు (; పాఠ్యం[ascii_నిడివి] != 0; ++ascii_నిడివి) {}
            clip->కూడు_దత్తాంశం("text/plain", B_MIME_TYPE, పాఠ్యం, ascii_నిడివి);
            be_clipboard->Commit();
        }
        be_clipboard->Unlock();
    }
    తిరిగి నిజం;
}

అక్షరం *HAIKU_Get_Clipboard_పాఠ్యం(SDL_VideoDevice *_this) {
    BMessage *clip = ఖాళీ;
    స్థిరరాశి అక్షరం *పాఠ్యం = ఖాళీ;
    ssize_t నిడివి;
    అక్షరం *ఫలితం;
    ఒకవేళ (be_clipboard->తాళం()) {
        ఒకవేళ ((clip = be_clipboard->దత్తాంశం_3())) {
            // Presumably the string of characters is ascii-format
            clip->కనుగొను_దత్తాంశం("text/plain", B_MIME_TYPE, (స్థిరరాశి శూన్య **)&పాఠ్యం,
                &నిడివి);
        }
        be_clipboard->Unlock();
    }

    ఒకవేళ (!పాఠ్యం) {
        ఫలితం = SDL_strdup("");
    } లేకపోతే {
        // Copy the data and pass on to SDL
        ఫలితం = (అక్షరం *)SDL_malloc((నిడివి + 1) * పరిమాణం(అక్షరం));
        SDL_strlcpy(ఫలితం, పాఠ్యం, నిడివి + 1);
    }

    తిరిగి ఫలితం;
}

తార్కిక HAIKU_Has_Clipboard_పాఠ్యం(SDL_VideoDevice *_this) {
    తార్కిక ఫలితం = అబద్ధం;
    అక్షరం *పాఠ్యం = HAIKU_Get_Clipboard_పాఠ్యం(_this);
    ఒకవేళ (పాఠ్యం) {
        ఫలితం = (పాఠ్యం[0] != '\0');
        SDL_free(పాఠ్యం);
    }
    తిరిగి ఫలితం;
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU
