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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_androidwindow_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_androidwindow_h_

#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

ಬಾಹ್ಯ bool Android_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ Android_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);

ಬಾಹ್ಯ ಶೂನ್ಯ Android_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_ಕಿಟಕಿ *Android_ಕಿಟಕಿ;

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
    EGLContext egl_context; // We use this to preserve the context when losing focus
    ಪೂರ್ಣಾಂಕ has_ಅದಲುಬದಲು_interval;  // Save/Restore the swap interval / vsync
    ಪೂರ್ಣಾಂಕ ಅದಲುಬದಲು_interval;
#ಆದರೆ_ಅಂತ್ಯ
    bool backup_ಮುಗಿದ;
    ANative_ಕಿಟಕಿ *native_ಕಿಟಕಿ;

};

#ಆದರೆ_ಅಂತ್ಯ // SDL_androidwindow_h_
