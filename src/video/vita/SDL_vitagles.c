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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#define EGLCHK(stmt)                           \
    করো {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        যদি (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ফেরত ফাঁকা;                          \
        }                                      \
    } যখন (0)

শূন্য VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_Swap_তথ্য *তথ্য)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.renderTarget.colorFormat = তথ্য->colorFormat;
    commonDialogParam.renderTarget.surfaceType = তথ্য->surfaceType;
    commonDialogParam.renderTarget.color_Surface_তথ্য = তথ্য->color_Surface_তথ্য;
    commonDialogParam.renderTarget.depth_Surface_তথ্য = তথ্য->depth_Surface_তথ্য;
    commonDialogParam.renderTarget.width = তথ্য->width;
    commonDialogParam.renderTarget.height = তথ্য->height;
    commonDialogParam.renderTarget.strideInPixels = তথ্য->strideInPixels;
    commonDialogParam.displaySyncObject = তথ্য->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    ফেরত true;
}

SDL_FunctionPointer VITA_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    ফেরত eglGetProcAddress(proc);
}

শূন্য VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_তথ্য->display);
}

স্থির EGLint width = 960;
স্থির EGLint height = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{

    SDL_Window_তথ্য *wdata = window->internal;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint অঙ্ক_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC preSwapCallback;
    পূর্ণসংখ্যা i;

    ধ্রুবক EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, ফাঁকা, ফাঁকা));
    wdata->uses_gles = true;
    window->flags |= SDL_WINDOW_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_আকার;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_আকার;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_আকার;
    attribs[i++] = 8;
    attribs[i++] = EGL_DEPTH_আকার;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_আকার;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_আকার;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_BIT;

    attribs[i++] = EGL_NONE;

    EGLCHK(eglChooseConfig(display, attribs, &config, 1, &অঙ্ক_configs));

    যদি (অঙ্ক_configs == 0) {
        SDL_SetError("No valid EGL configs for requested mode");
        ফেরত ফাঁকা;
    }

    EGLCHK(surface = eglCreateWindowSurface(display, config, VITA_WINDOW_960X544, ফাঁকা));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_WIDTH, &width));
    EGLCHK(eglQuerySurface(display, surface, EGL_HEIGHT, &height));

    _this->gl_তথ্য->display = display;
    _this->gl_তথ্য->context = context;
    _this->gl_তথ্য->surface = surface;

    preSwapCallback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)eglGetProcAddress("eglPigletVitaSetPreSwapCallbackSCE");
    preSwapCallback(VITA_GLES_KeyboardCallback);

    ফেরত context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    যদি (!eglMakeCurrent(_this->gl_তথ্য->display, _this->gl_তথ্য->surface,
                        _this->gl_তথ্য->surface, _this->gl_তথ্য->context)) {
        ফেরত SDL_SetError("Unable to make EGL context current");
    }
    ফেরত true;
}

bool VITA_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    EGLBoolean status;
    status = eglSwapInterval(_this->gl_তথ্য->display, interval);
    যদি (status == EGL_TRUE) {
        // Return success to upper level
        _this->gl_তথ্য->swapinterval = interval;
        ফেরত true;
    }
    // Failed to set swap interval
    ফেরত SDL_SetError("Unable to set the EGL swap interval");
}

bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    *interval = _this->gl_তথ্য->swapinterval;
    ফেরত true;
}

bool VITA_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (!eglSwapBuffers(_this->gl_তথ্য->display, _this->gl_তথ্য->surface)) {
        ফেরত SDL_SetError("eglSwapBuffers() failed");
    }
    ফেরত true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_তথ্য *phdata = _this->internal;
    EGLBoolean status;

    যদি (phdata->egl_initialized != true) {
        ফেরত SDL_SetError("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    যদি (_this->gl_তথ্য->display != EGL_NO_DISPLAY) {
        যদি (context != EGL_NO_CONTEXT) {
            status = eglDestroyContext(_this->gl_তথ্য->display, context);
            যদি (status != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ফেরত SDL_SetError("VITA: OpenGL ES context destroy error");
            }
        }
    }

    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_VITA
