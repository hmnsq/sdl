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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsopengles.h"
#ضمن "SDL_windowsopengl.h"
#ضمن "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    إذا (_this->gl_config.profile_ماسک != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_بارگیری_Library = WIN_GL_بارگیری_Library;
        _this->GL_Get_Proc_آدرس = WIN_GL_Get_Proc_آدرس;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_مجموعه_جابجا_Interval = WIN_GL_مجموعه_جابجا_Interval;
        _this->GL_Get_جابجا_Interval = WIN_GL_Get_جابجا_Interval;
        _this->GL_جابجا_پنجره = WIN_GL_جابجا_پنجره;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = عدم;
        أرجع WIN_GL_بارگیری_Library(_this, مسیر);
#وإلا
        أرجع SDL_مجموعه_Error("SDL not configured with OpenGL/WGL support");
#پایان_اگر
    }

    إذا (!_this->egl_داده) {
        أرجع SDL_EGL_بارگیری_Library(_this, عدم, EGL_DEFAULT_DISPLAY);
    }

    أرجع true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_GLContext context;
    SDL_پنجره_داده *داده = پنجره->داخلی;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
    إذا (_this->gl_config.profile_ماسک != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_بارگیری_Library = WIN_GL_بارگیری_Library;
        _this->GL_Get_Proc_آدرس = WIN_GL_Get_Proc_آدرس;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_مجموعه_جابجا_Interval = WIN_GL_مجموعه_جابجا_Interval;
        _this->GL_Get_جابجا_Interval = WIN_GL_Get_جابجا_Interval;
        _this->GL_جابجا_پنجره = WIN_GL_جابجا_پنجره;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = عدم;

        إذا (!WIN_GL_بارگیری_Library(_this, عدم)) {
            أرجع عدم;
        }

        أرجع WIN_GL_CreateContext(_this, پنجره);
    }
#پایان_اگر

    context = SDL_EGL_CreateContext(_this, داده->egl_surface);
    أرجع context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    أرجع SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_جابجا_پنجره_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_راهاندازی_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // The current context is lost in here; save it and reset it.
    SDL_پنجره_داده *windowdata = پنجره->داخلی;
    SDL_پنجره *current_win = SDL_GL_Get_Current_پنجره();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    إذا (!_this->egl_داده) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#إذا 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#پایان_اگر
        إذا (!SDL_EGL_بارگیری_Library(_this, عدم, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            أرجع false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)windowdata->hwnd);

    إذا (windowdata->egl_surface == EGL_NO_SURFACE) {
        أرجع SDL_مجموعه_Error("Could not create GLES window surface");
    }

    أرجع WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *windowdata = پنجره->داخلی;

    أرجع windowdata->egl_surface;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
