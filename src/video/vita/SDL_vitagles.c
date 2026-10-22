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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    செய் {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        எனில் (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            திரும்பு வெற்று;                          \
        }                                      \
    } போது (0)

வெறுமை VITA_GLES_KeyboardCallback(ScePigletPreSwapData *data)
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

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    திரும்பு true;
}

SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc)
{
    திரும்பு eglGetProcAddress(proc);
}

வெறுமை VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_data->display);
}

நிலையான EGLint width = 960;
நிலையான EGLint height = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_WindowData *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint இலக்கம்_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC preSwapCallback;
    முழு i;

    மாறிலி EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, வெற்று, வெற்று));
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

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &இலக்கம்_configs));

    எனில் (இலக்கம்_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        திரும்பு வெற்று;
    }

    EGLCHK(surface = eglCreateWindowSurface(display, config, VITA_WINDOW_960X544, வெற்று));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_WIDTH, &width));
    EGLCHK(eglQuerySurface(display, surface, EGL_HEIGHT, &height));

    _this->gl_data->display = display;
    _this->gl_data->context = context;
    _this->gl_data->surface = surface;

    preSwapCallback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)eglGetProcAddress("eglPigletVitaSetPreSwapCallbackSCE");
    preSwapCallback(VITA_GLES_KeyboardCallback);

    திரும்பு context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    எனில் (!eglMakeCurrent(_this->gl_data->display, _this->gl_data->surface,
                        _this->gl_data->surface, _this->gl_data->context)) {
        திரும்பு SDL_SetError("Unable to make EGL context current");
    }
    திரும்பு true;
}

bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, முழு interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_data->display, interval);
    எனில் (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_data->swapinterval = interval;
        திரும்பு true;
    }
    // Failed to set swap interval
    திரும்பு SDL_SetError("Unable to set the EGL swap interval");
}

bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval)
{
    *interval = _this->gl_data->swapinterval;
    திரும்பு true;
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    எனில் (!eglSwapBuffers(_this->gl_data->display, _this->gl_data->surface)) {
        திரும்பு SDL_SetError("eglSwapBuffers() failed");
    }
    திரும்பு true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *phdata = _this->internal;
    EGLBoolean status;

    எனில் (phdata->egl_initialized != true) {
        திரும்பு SDL_SetError("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    எனில் (_this->gl_data->display != EGL_NO_DISPLAY) {
        எனில் (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_data->display, context);
            எனில் (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                திரும்பு SDL_SetError("VITA: OpenGL ES context destroy error");
            }
        }
    }

    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_VITA
