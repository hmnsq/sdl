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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    કરો {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        જો (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            પાછા ખાલી;                          \
        }                                      \
    } જ્યારે (0)

શૂન્ય VITA_GLES_KeyboardCallback(ScePigletPreSwapData *data)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.renderTarget.colorFormat = data->colorFormat;
    commonDialogParam.renderTarget.surfaceType = data->surfaceType;
    commonDialogParam.renderTarget.colorSurfaceData = data->colorSurfaceData;
    commonDialogParam.renderTarget.depthSurfaceData = data->depthSurfaceData;
    commonDialogParam.renderTarget.width = data->width;
    commonDialogParam.renderTarget.height = data->height;
    commonDialogParam.renderTarget.strideInPixels = data->strideInPixels;
    commonDialogParam.displaySyncObject = data->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    પાછા true;
}

SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc)
{
    પાછા eglGetProcAddress(proc);
}

શૂન્ય VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

સ્થિર EGLint width = 960;
સ્થિર EGLint height = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint અંક_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC preSwapCallback;
    પૂર્ણાંક i;

    અચલ EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, ખાલી, ખાલી));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_SIZE;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_SIZE;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_SIZE;
    attribs[i++] = 8;
    attribs[i++] = EGL_DEPTH_SIZE;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_SIZE;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_SIZE;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &અંક_configs));

    જો (અંક_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        પાછા ખાલી;
    }

    EGLCHK(surface = eglCreateWindowSurface(display, config, VITA_WINDOW_960X544, ખાલી));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_WIDTH, &width));
    EGLCHK(eglQuerySurface(display, surface, EGL_HEIGHT, &height));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    preSwapCallback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)eglGetProcAddress("eglPigletVitaSetPreSwapCallbackSCE");
    preSwapCallback(VITA_GLES_KeyboardCallback);

    પાછા context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    જો (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        પાછા SDL_SetError("Unable to make EGL context current");
    }
    પાછા true;
}

bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    જો (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        પાછા true;
    }
    // Failed to set swap interval
    પાછા SDL_SetError("Unable to set the EGL swap interval");
}

bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક *interval)
{
    *interval = _this->gl_data->swapinterval;
    પાછા true;
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    જો (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        પાછા SDL_SetError("eglSwapBuffers() failed");
    }
    પાછા true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    જો (phdata->egl_initialized != true) {
        પાછા SDL_SetError("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    જો (_this->gl_data->display != EGL_NO_DISPLAY) {
        જો (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            જો (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                પાછા SDL_SetError("VITA: OpenGL ES context destroy error");
            }
        }
    }

    પાછા true;
}

#endif // SDL_VIDEO_DRIVER_VITA
