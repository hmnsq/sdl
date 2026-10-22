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

#నిర్వచితం_కాకపోతే SDL_x11xfixes_h_
#నిర్వచించు SDL_x11xfixes_h_

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES

#నిర్వచించు X11_BARRIER_HANDLED_BY_EVENT 1

బాహ్య శూన్య X11_InitXfixes(SDL_VideoDevice *_this);
బాహ్య bool X11_XfixesIsInitialized(శూన్య);
బాహ్య bool X11_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_ConfineCursorWithFlags(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం flags);
బాహ్య శూన్య X11_Destroy_సూచిక_Barrier(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య పూర్ణాంకం X11_GetXFixesSelectionNotifyEvent(శూన్య);
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES

#అయితే_ముగింపు // SDL_x11xfixes_h_
