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

#यदि defined(SDL_VIDEO_DRIVER_OFFSCREEN) && defined(SDL_VIDEO_OPENGL_EGL)

#अन्तर्भाव "SDL_offscreenopengles.h"
#अन्तर्भाव "SDL_offscreenvideo.h"
#अन्तर्भाव "SDL_offscreenwindow.h"

// EGL implementation of SDL OpenGL support

bool OFFSCREEN_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    यदि (!SDL_EGL_आरोपय_Library_Only(_this, मार्गः)) {
        प्रत्यागम false;
    }

    /* driver_loaded gets incremented by SDL_GL_LoadLibrary when we return,
       but SDL_EGL_InitializeOffscreen checks that we're loaded before then,
       so temporarily bump it since we know that LoadLibraryOnly succeeded. */
    bool परिणाम;
    _this->gl_config.driver_loaded++;
    परिणाम = SDL_EGL_InitializeOffscreen(_this, 0);
    _this->gl_config.driver_loaded--;
    यदि (!परिणाम) {
        प्रत्यागम false;
    }

    यदि (!SDL_EGL_वृणु_Config(_this)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

SDL_GLContext OFFSCREEN_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *offscreen_गवाक्षः = गवाक्षः->आन्तरिकम्;

    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, offscreen_गवाक्षः->egl_surface);

    प्रत्यागम context;
}

bool OFFSCREEN_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    यदि (गवाक्षः) {
        EGLSurface egl_surface = गवाक्षः->आन्तरिकम्->egl_surface;
        प्रत्यागम SDL_EGL_MakeCurrent(_this, egl_surface, context);
    } अन्यथा {
        प्रत्यागम SDL_EGL_MakeCurrent(_this, रिक्त, रिक्त);
    }
}

bool OFFSCREEN_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *offscreen_wind = गवाक्षः->आन्तरिकम्;

    प्रत्यागम SDL_EGL_SwapBuffers(_this, offscreen_wind->egl_surface);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OFFSCREEN && SDL_VIDEO_OPENGL_EGL
