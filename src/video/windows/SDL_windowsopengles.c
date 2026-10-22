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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowsopengles.h"
#समावेश "SDL_windowsopengl.h"
#समावेश "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    अगर (_this->gl_config.profile_mask != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#अगर_घोषित SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_LoadLibrary = WIN_GL_LoadLibrary;
        _this->GL_GetProcAddress = WIN_GL_GetProcAddress;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
        _this->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
        _this->GL_SwapWindow = WIN_GL_SwapWindow;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = शून्य;
        वापस WIN_GL_LoadLibrary(_this, path);
#अन्यथा
        वापस SDL_SetError("SDL not configured with OpenGL/WGL support");
#पूर्ण_अगर
    }

    अगर (!_this->egl_तथ्य) {
        वापस SDL_EGL_LoadLibrary(_this, शून्य, EGL_DEFAULT_DISPLAY);
    }

    वापस true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext context;
    SDL_Window_तथ्य *तथ्य = window->internal;

#अगर_घोषित SDL_VIDEO_OPENGL_WGL
    अगर (_this->gl_config.profile_mask != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_LoadLibrary = WIN_GL_LoadLibrary;
        _this->GL_GetProcAddress = WIN_GL_GetProcAddress;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
        _this->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
        _this->GL_SwapWindow = WIN_GL_SwapWindow;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = शून्य;

        अगर (!WIN_GL_LoadLibrary(_this, शून्य)) {
            वापस शून्य;
        }

        वापस WIN_GL_CreateContext(_this, window);
    }
#पूर्ण_अगर

    context = SDL_EGL_CreateContext(_this, तथ्य->egl_surface);
    वापस context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    वापस SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_SwapWindow_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_SetupWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // The current context is lost in here; save it and reset it.
    SDL_Window_तथ्य *windowdata = window->internal;
    SDL_Window *current_win = SDL_GL_GetCurrentWindow();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    अगर (!_this->egl_तथ्य) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#अगर 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#पूर्ण_अगर
        अगर (!SDL_EGL_LoadLibrary(_this, शून्य, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            वापस false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)windowdata->hwnd);

    अगर (windowdata->egl_surface == EGL_NO_SURFACE) {
        वापस SDL_SetError("Could not create GLES window surface");
    }

    वापस WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *windowdata = window->internal;

    वापस windowdata->egl_surface;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
