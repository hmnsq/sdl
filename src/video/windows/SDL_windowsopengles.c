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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowsopengles.h"
#अन्तर्भाव "SDL_windowsopengl.h"
#अन्तर्भाव "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    यदि (_this->gl_config.profile_आवरणम् != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_आरोपय_Library = WIN_GL_आरोपय_Library;
        _this->GL_Get_Proc_स्थानाङ्कः = WIN_GL_Get_Proc_स्थानाङ्कः;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_समुच्चयः_Swap_Interval = WIN_GL_समुच्चयः_Swap_Interval;
        _this->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
        _this->GL_Swap_गवाक्षः = WIN_GL_Swap_गवाक्षः;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = रिक्त;
        प्रत्यागम WIN_GL_आरोपय_Library(_this, मार्गः);
#अन्यथा
        प्रत्यागम SDL_समुच्चयः_Error("SDL not configured with OpenGL/WGL support");
#यदि_अन्तः
    }

    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_EGL_आरोपय_Library(_this, रिक्त, EGL_DEFAULT_DISPLAY);
    }

    प्रत्यागम true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_GLContext context;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_WGL
    यदि (_this->gl_config.profile_आवरणम् != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_आरोपय_Library = WIN_GL_आरोपय_Library;
        _this->GL_Get_Proc_स्थानाङ्कः = WIN_GL_Get_Proc_स्थानाङ्कः;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_समुच्चयः_Swap_Interval = WIN_GL_समुच्चयः_Swap_Interval;
        _this->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
        _this->GL_Swap_गवाक्षः = WIN_GL_Swap_गवाक्षः;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = रिक्त;

        यदि (!WIN_GL_आरोपय_Library(_this, रिक्त)) {
            प्रत्यागम रिक्त;
        }

        प्रत्यागम WIN_GL_CreateContext(_this, गवाक्षः);
    }
#यदि_अन्तः

    context = SDL_EGL_CreateContext(_this, दत्त->egl_surface);
    प्रत्यागम context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    प्रत्यागम SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_Swap_गवाक्षः_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_सज्जता_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // The current context is lost in here; save it and reset it.
    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;
    SDL_गवाक्षः *current_win = SDL_GL_Get_Current_गवाक्षः();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    यदि (!_this->egl_दत्त) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#यदि 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#यदि_अन्तः
        यदि (!SDL_EGL_आरोपय_Library(_this, रिक्त, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            प्रत्यागम false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)windowdata->hwnd);

    यदि (windowdata->egl_surface == EGL_NO_SURFACE) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not create GLES window surface");
    }

    प्रत्यागम WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;

    प्रत्यागम windowdata->egl_surface;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
