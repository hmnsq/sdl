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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(SDL_VIDEO_OPENGL_EGL) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowsopengles.h"
#అన్తర్భావ "SDL_windowsopengl.h"
#అన్తర్భావ "SDL_windowswindow.h"

// EGL implementation of SDL OpenGL support

bool WIN_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{

    // If the profile requested is not GL ES, switch over to WIN_GL functions
    ఒకవేళ (_this->gl_config.profile_ముసుగు != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ఎక్కించు_Library = WIN_GL_ఎక్కించు_Library;
        _this->GL_Get_Proc_చిరునామా = WIN_GL_Get_Proc_చిరునామా;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_సమితి_మార్పిడి_Interval = WIN_GL_సమితి_మార్పిడి_Interval;
        _this->GL_Get_మార్పిడి_Interval = WIN_GL_Get_మార్పిడి_Interval;
        _this->GL_మార్పిడి_కిటికీ = WIN_GL_మార్పిడి_కిటికీ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ఖాళీ;
        తిరిగి WIN_GL_ఎక్కించు_Library(_this, మార్గం);
#లేకపోతే
        తిరిగి SDL_సమితి_Error("SDL not configured with OpenGL/WGL support");
#అయితే_ముగింపు
    }

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_EGL_ఎక్కించు_Library(_this, ఖాళీ, EGL_DEFAULT_DISPLAY);
    }

    తిరిగి true;
}

SDL_GLContext WIN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_GLContext context;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
    ఒకవేళ (_this->gl_config.profile_ముసుగు != SDL_GL_CONTEXT_PROFILE_ES &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
        // Switch to WGL based functions
        WIN_GLES_UnloadLibrary(_this);
        _this->GL_ఎక్కించు_Library = WIN_GL_ఎక్కించు_Library;
        _this->GL_Get_Proc_చిరునామా = WIN_GL_Get_Proc_చిరునామా;
        _this->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
        _this->GL_CreateContext = WIN_GL_CreateContext;
        _this->GL_MakeCurrent = WIN_GL_MakeCurrent;
        _this->GL_సమితి_మార్పిడి_Interval = WIN_GL_సమితి_మార్పిడి_Interval;
        _this->GL_Get_మార్పిడి_Interval = WIN_GL_Get_మార్పిడి_Interval;
        _this->GL_మార్పిడి_కిటికీ = WIN_GL_మార్పిడి_కిటికీ;
        _this->GL_DestroyContext = WIN_GL_DestroyContext;
        _this->GL_GetEGLSurface = ఖాళీ;

        ఒకవేళ (!WIN_GL_ఎక్కించు_Library(_this, ఖాళీ)) {
            తిరిగి ఖాళీ;
        }

        తిరిగి WIN_GL_CreateContext(_this, కిటికీ);
    }
#అయితే_ముగింపు

    context = SDL_EGL_CreateContext(_this, దత్తాంశం->egl_surface);
    తిరిగి context;
}

bool WIN_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    తిరిగి SDL_EGL_DestroyContext(_this, context);
}

/* *INDENT-OFF* */ // clang-format off
SDL_EGL_మార్పిడి_కిటికీ_impl(WIN)
SDL_EGL_MakeCurrent_impl(WIN)
/* *INDENT-ON* */ // clang-format on

bool WIN_GLES_అమరిక_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // The current context is lost in here; save it and reset it.
    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;
    SDL_కిటికీ *current_win = SDL_GL_Get_Current_కిటికీ();
    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();

    ఒకవేళ (!_this->egl_దత్తాంశం) {
// !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan.
#ఒకవేళ 0 // When hint SDL_HINT_OPENGL_ES_DRIVER is set to "1" (e.g. for ANGLE support), _this->gl_config.driver_loaded can be 1, while the below lines function.
        SDL_assert(!_this->gl_config.driver_loaded);
#అయితే_ముగింపు
        ఒకవేళ (!SDL_EGL_ఎక్కించు_Library(_this, ఖాళీ, EGL_DEFAULT_DISPLAY)) {
            SDL_EGL_UnloadLibrary(_this);
            తిరిగి false;
        }
        _this->gl_config.driver_loaded = 1;
    }

    // Create the GLES window surface
    windowdata->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)windowdata->hwnd);

    ఒకవేళ (windowdata->egl_surface == EGL_NO_SURFACE) {
        తిరిగి SDL_సమితి_Error("Could not create GLES window surface");
    }

    తిరిగి WIN_GLES_MakeCurrent(_this, current_win, current_ctx);
}

EGLSurface WIN_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;

    తిరిగి windowdata->egl_surface;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS && SDL_VIDEO_OPENGL_EGL
