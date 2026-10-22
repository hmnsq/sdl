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

#నిర్వచితం_కాకపోతే SDL_offscreenwindow_h
#నిర్వచించు SDL_offscreenwindow_h

#అన్తర్భావ "SDL_offscreenvideo.h"

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_కిటికీ *sdl_కిటికీ;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#అయితే_ముగింపు
};

బాహ్య bool OFFSCREEN_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య OFFSCREEN_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య OFFSCREEN_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు // SDL_offscreenwindow_h
