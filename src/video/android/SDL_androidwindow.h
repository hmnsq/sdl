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

#నిర్వచితం_కాకపోతే SDL_androidwindow_h_
#నిర్వచించు SDL_androidwindow_h_

#అన్తర్భావ "../../core/android/SDL_android.h"
#అన్తర్భావ "../SDL_egl_c.h"

బాహ్య bool Android_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య Android_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_Fullscreen_ఫలితం Android_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య Android_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Android_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);

బాహ్య శూన్య Android_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_కిటికీ *Android_కిటికీ;

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    పూర్ణాంకం has_మార్పిడి_interval;  // Save/Restore the swap interval / vsync
    పూర్ణాంకం మార్పిడి_interval;
#అయితే_ముగింపు
    bool backup_పూర్తి;
    ANative_కిటికీ *native_కిటికీ;

};

#అయితే_ముగింపు // SDL_androidwindow_h_
