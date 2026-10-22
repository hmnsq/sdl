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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsopengles.h"
#شامل "SDL_windowsopengl.h"
#شامل "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    اگر (_this->gl_config.profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_بھرو_Library = WIN_GL_بھرو_Library;
        _this->GL_Get_Proc_پتہ = WIN_GL_Get_Proc_پتہ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_سیٹ_تبادلہ_Interval = WIN_GL_سیٹ_تبادلہ_Interval;
        _this->GL_Get_تبادلہ_Interval = WIN_GL_Get_تبادلہ_Interval;
        _this->GL_تبادلہ_کھڑکی = WIN_GL_تبادلہ_کھڑکی;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = تہی;
        واپس WIN_GL_بھرو_Library(_this, راستہ);
#ورنہ
        واپس SDL_سیٹ_Error("SDL not configured with OpenGL/WGL support");
#اگر_ختم
    }

    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_EGL_بھرو_Library(_this, تہی, EGL_DEFAULT_DISPLAY);
    }

    واپس true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext context;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    اگر (_this->gl_config.profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_بھرو_Library = WIN_GL_بھرو_Library;
        _this->GL_Get_Proc_پتہ = WIN_GL_Get_Proc_پتہ;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_سیٹ_تبادلہ_Interval = WIN_GL_سیٹ_تبادلہ_Interval;
        _this->GL_Get_تبادلہ_Interval = WIN_GL_Get_تبادلہ_Interval;
        _this->GL_تبادلہ_کھڑکی = WIN_GL_تبادلہ_کھڑکی;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = تہی;

        اگر (!WIN_GL_بھرو_Library(_this, تہی)) {
            واپس تہی;
        }

        واپس WIN_GL_CreateContext(_this, کھڑکی);
    }
#اگر_ختم

    context = SDL_EGL_CreateContext(_this, ڈیٹا->egl_surface);
    واپس context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    واپس SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_تبادلہ_کھڑکی_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_تیاری_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // The current context is lost in here; save it and reset it.
    SDL_کھڑکی_ڈیٹا *windowdata = کھڑکی->اندرونی_2;
    SDL_کھڑکی *current_win = SDL_GL_Get_Current_کھڑکی();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    اگر (!_this->egl_ڈیٹا) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#اگر 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#اگر_ختم
        اگر (!SDL_EGL_بھرو_Library(_this, تہی, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            واپس false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)windowdata->hwnd);

    اگر (windowdata->egl_surface == EGL_NO_SURFACE) {
        واپس SDL_سیٹ_Error("Could not create GLES window surface");
    }

    واپس WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *windowdata = کھڑکی->اندرونی_2;

    واپس windowdata->egl_surface;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
