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

#अगर defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#घोषणा EGLCHK(stmt)                           \
    करो {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        अगर (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            वापस शून्य;                          \
        }                                      \
    } जबतक (0)

व्योम VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_Swap_तथ्य *तथ्य)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.renderTarget.colorFormat = तथ्य->colorFormat;
    commonDialogParam.renderTarget.surfaceType = तथ्य->surfaceType;
    commonDialogParam.renderTarget.color_Surface_तथ्य = तथ्य->color_Surface_तथ्य;
    commonDialogParam.renderTarget.depth_Surface_तथ्य = तथ्य->depth_Surface_तथ्य;
    commonDialogParam.renderTarget.width = तथ्य->width;
    commonDialogParam.renderTarget.height = तथ्य->height;
    commonDialogParam.renderTarget.strideInPixels = तथ्य->strideInPixels;
    commonDialogParam.displaySyncObject = तथ्य->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    वापस true;
}

SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    वापस eglGetProcAddress(proc);
}

व्योम VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_तथ्य->display);
}

अटल EGLint width = 960;
अटल EGLint height = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_Window_तथ्य *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint अंक_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC preSwapCallback;
    पूर्णांक i;

    स्थिर EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, शून्य, शून्य));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_DEPTH_आकार;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_आकार;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &अंक_configs));

    अगर (अंक_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        वापस शून्य;
    }

    EGLCHK(surface = eglCreateWindowSurface(display, config, VITA_WINDOW_960X544, शून्य));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_WIDTH, &width));
    EGLCHK(eglQuerySurface(display, surface, EGL_HEIGHT, &height));

    _this->gl_तथ्य->display = display;
    _this->gl_तथ्य->context = context;
    _this->gl_तथ्य->surface = surface;

    preSwapCallback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)eglGetProcAddress("eglPigletVitaSetPreSwapCallbackSCE");
    preSwapCallback(VITA_GLES_KeyboardCallback);

    वापस context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    अगर (!eglMakeCurrent(_this->gl_तथ्य->display, _this->gl_तथ्य->surface,
                        _this->gl_तथ्य->surface, _this->gl_तथ्य->context)) {
        वापस SDL_SetError("Unable to make EGL context current");
    }
    वापस true;
}

bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_तथ्य->display, interval);
    अगर (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_तथ्य->swapinterval = interval;
        वापस true;
    }
    // Failed to set swap interval
    वापस SDL_SetError("Unable to set the EGL swap interval");
}

bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    *interval = _this->gl_तथ्य->swapinterval;
    वापस true;
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (!eglSwapBuffers(_this->gl_तथ्य->display, _this->gl_तथ्य->surface)) {
        वापस SDL_SetError("eglSwapBuffers() failed");
    }
    वापस true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_तथ्य *phdata = _this->internal;
    EGLBoolean status;

    अगर (phdata->egl_initialized != true) {
        वापस SDL_SetError("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    अगर (_this->gl_तथ्य->display != EGL_NO_DISPLAY) {
        अगर (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_तथ्य->display, context);
            अगर (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                वापस SDL_SetError("VITA: OpenGL ES context destroy error");
            }
        }
    }

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA
