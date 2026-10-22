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

#నిర్వచితం_కాకపోతే SDL_x11clipboard_h_
#నిర్వచించు SDL_x11clipboard_h_

#అన్తర్భావ <X11/Xlib.h>

రకనిర్వచనం నిర్మాణం X11_Clipboard_దత్తాంశం {
    SDL_Clipboard_దత్తాంశం_Callback callback;
    శూన్య *userdata;
    స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types;
    size_t mime_లెక్క;
    Uint32 sequence;
} SDLX11_Clipboard_దత్తాంశం;

బాహ్య స్థిరరాశి అక్షరం *స్థిరరాశి *X11_Get_పాఠ్యం_Mime_Types(SDL_VideoDevice *_this, size_t *అంకె_mime_types);
బాహ్య bool X11_సమితి_Clipboard_దత్తాంశం(SDL_VideoDevice *_this);
బాహ్య శూన్య *X11_Get_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి);
బాహ్య bool X11_Has_Clipboard_దత్తాంశం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type);
బాహ్య bool X11_సమితి_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం);
బాహ్య అక్షరం *X11_Get_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this);
బాహ్య bool X11_Has_Primary_Selection_పాఠ్యం(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_QuitClipboard(SDL_VideoDevice *_this);
కిటికీ_2 Get_కిటికీ(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_x11clipboard_h_
