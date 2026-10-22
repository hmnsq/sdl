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

#నిర్వచితం_కాకపోతే SDL_clipboard_c_h_
#నిర్వచించు SDL_clipboard_c_h_

#అన్తర్భావ "SDL_sysvideo.h"


// Return true if the mime type is valid clipboard text
బాహ్య bool SDL_Is_పాఠ్యం_Mime_Type(స్థిరరాశి అక్షరం *mime_type);

// Cancel the clipboard data callback, called internally for cleanup
బాహ్య శూన్య SDL_Cancel_Clipboard_దత్తాంశం(Uint32 sequence);

// Call the clipboard callback for application data
బాహ్య శూన్య *SDL_Get_అంతర్గత_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత);
బాహ్య bool SDL_Has_అంతర్గత_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type);

// General purpose clipboard text callback
స్థిరరాశి శూన్య * SDLCALL SDL_Clipboard_పాఠ్యం_Callback(శూన్య *userdata, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత);

bool SDL_SaveClipboardMimeTypes(స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types, size_t అంకె_mime_types);
శూన్య SDL_FreeClipboardMimeTypes(SDL_VideoDevice *_this);
అక్షరం **SDL_CopyClipboardMimeTypes(స్థిరరాశి అక్షరం *స్థిరరాశి *clipboard_mime_types, size_t అంకె_mime_types, bool temporary);

#అయితే_ముగింపు // SDL_clipboard_c_h_
