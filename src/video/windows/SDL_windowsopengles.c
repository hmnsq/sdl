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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    ਜੇ (_this->gl_config.profile_ਨਕਾਬ != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ਲੱਦੋ_Library = WIN_GL_ਲੱਦੋ_Library;
        _this->GL_Get_Proc_ਪਤਾ = WIN_GL_Get_Proc_ਪਤਾ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = WIN_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ਨਿਰਾ;
        ਵਾਪਸ WIN_GL_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
#ਨਹੀਂਤਾਂ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not configured with OpenGL/WGL support");
#ਜੇ_ਅੰਤ
    }

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਨਿਰਾ, EGL_DEFAULT_DISPLAY);
    }

    ਵਾਪਸ true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_GLContext context;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
    ਜੇ (_this->gl_config.profile_ਨਕਾਬ != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ਲੱਦੋ_Library = WIN_GL_ਲੱਦੋ_Library;
        _this->GL_Get_Proc_ਪਤਾ = WIN_GL_Get_Proc_ਪਤਾ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = WIN_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = WIN_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ਨਿਰਾ;

        ਜੇ (!WIN_GL_ਲੱਦੋ_Library(_this, ਨਿਰਾ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਵਾਪਸ WIN_GL_CreateContext(_this, ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ

    context = SDL_EGL_CreateContext(_this, ਅੰਕੜੇ->egl_surface);
    ਵਾਪਸ context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ਵਾਪਸ SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_ਤਿਆਰੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // The current context is lost in here; save it and reset it.
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ *current_win = SDL_GL_Get_Current_ਖਿੜਕੀ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#ਜੇ 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#ਜੇ_ਅੰਤ
        ਜੇ (!SDL_EGL_ਲੱਦੋ_Library(_this, ਨਿਰਾ, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            ਵਾਪਸ false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)windowdata->hwnd);

    ਜੇ (windowdata->egl_surface == EGL_NO_SURFACE) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create GLES window surface");
    }

    ਵਾਪਸ WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਵਾਪਸ windowdata->egl_surface;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
