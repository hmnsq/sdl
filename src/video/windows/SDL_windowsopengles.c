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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsopengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ತುಂಬು_Library = WIN_GL_ತುಂಬು_Library;
        _this->GL_Get_Proc_ವಿಳಾಸ = WIN_GL_Get_Proc_ವಿಳಾಸ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval = WIN_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
        _this->GL_Get_ಅದಲುಬದಲು_Interval = WIN_GL_Get_ಅದಲುಬದಲು_Interval;
        _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = WIN_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ WIN_GL_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
#ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not configured with OpenGL/WGL support");
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಖಾಲಿ, EGL_DEFAULT_DISPLAY);
    }

    ಹಿಂತಿರುಗಿ true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_GLContext context;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
    ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ತುಂಬು_Library = WIN_GL_ತುಂಬು_Library;
        _this->GL_Get_Proc_ವಿಳಾಸ = WIN_GL_Get_Proc_ವಿಳಾಸ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval = WIN_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
        _this->GL_Get_ಅದಲುಬದಲು_Interval = WIN_GL_Get_ಅದಲುಬದಲು_Interval;
        _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = WIN_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ಖಾಲಿ;

        ಆದರೆ (!WIN_GL_ತುಂಬು_Library(_this, ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಹಿಂತಿರುಗಿ WIN_GL_CreateContext(_this, ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    context = SDL_EGL_CreateContext(_this, ದತ್ತಾಂಶ->egl_surface);
    ಹಿಂತಿರುಗಿ context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_ಅದಲುಬದಲು_ಕಿಟಕಿ_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_ಸಿದ್ಧತೆ_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // The current context is lost in here; save it and reset it.
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ *current_win = SDL_GL_Get_Current_ಕಿಟಕಿ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#ಆದರೆ 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (!SDL_EGL_ತುಂಬು_Library(_this, ಖಾಲಿ, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            ಹಿಂತಿರುಗಿ false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)windowdata->hwnd);

    ಆದರೆ (windowdata->egl_surface == EGL_NO_SURFACE) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GLES window surface");
    }

    ಹಿಂತಿರುಗಿ WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಹಿಂತಿರುಗಿ windowdata->egl_surface;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
