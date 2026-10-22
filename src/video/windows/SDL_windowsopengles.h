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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_winopengles_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_winopengles_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

// OpenGLES functions
#ವ್ಯಾಖ್ಯಾನಿಸು WIN_GLES_GetAttribute    SDL_EGL_GetAttribute
#ವ್ಯಾಖ್ಯಾನಿಸು WIN_GLES_Get_Proc_ವಿಳಾಸ  SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು WIN_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ವ್ಯಾಖ್ಯಾನಿಸು WIN_GLES_Get_ಅದಲುಬದಲು_Interval SDL_EGL_Get_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು WIN_GLES_ಗಣ_ಅದಲುಬದಲು_Interval SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval

ಬಾಹ್ಯ bool WIN_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context);
ಬಾಹ್ಯ bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ bool WIN_GLES_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL

#ಆದರೆ_ಅಂತ್ಯ // SDL_winopengles_h_
