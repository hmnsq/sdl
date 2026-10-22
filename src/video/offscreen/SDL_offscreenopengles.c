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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "SDL_offscreenopengles.h"
#అన్తర్భావ "SDL_offscreenvideo.h"
#అన్తర్భావ "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    ఒకవేళ (!SDL_EGL_ఎక్కించు_Library_Only(_this, మార్గం)) {
        తిరిగి false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool ఫలితం;
    _this->gl_config.driver_loaded++;
    ఫలితం = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    ఒకవేళ (!ఫలితం) {
        తిరిగి false;
    }

    ఒకవేళ (!SDL_EGL_ఎంచుకో_Config(_this)) {
        తిరిగి false;
    }

    తిరిగి true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *offscreen_కిటికీ = కిటికీ->అంతర్గత;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_కిటికీ->egl_surface);

    తిరిగి context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    ఒకవేళ (కిటికీ) {
        EGLSurface egl_surface = కిటికీ->అంతర్గత->egl_surface;
        తిరిగి SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } లేకపోతే {
        తిరిగి SDL_EGL_MakeCurrent(_this, ఖాళీ, ఖాళీ);
    }
}

bool OFFSCREEN_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *offscreen_wind = కిటికీ->అంతర్గత;

    తిరిగి SDL_EGL_మార్పిడి_Buffers(_this, offscreen_wind->egl_surface);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
