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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_pspgl_c_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_pspgl_c_h_

#ಅನ್ತರ್ಭಾವ <GLES/egl.h>
#ಅನ್ತರ್ಭಾವ <GLES/gl.h>

#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_ದತ್ತಾಂಶ;

ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ PSP_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context);
ಬಾಹ್ಯ ಶೂನ್ಯ PSP_GL_ಅದಲುಬದಲು_Buffers(SDL_VideoDevice *_this);

ಬಾಹ್ಯ bool PSP_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ಬಾಹ್ಯ bool PSP_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ ಶೂನ್ಯ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool PSP_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool PSP_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);

#ಆದರೆ_ಅಂತ್ಯ // SDL_pspgl_c_h_
