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

#यदि defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#परिभाषय EGLCHK(stmt)                           \
    कुरु {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        यदि (err != EGL_SUCCESS) {              \
            SDL_समुच्चयः_Error("EGL error %d", err); \
            प्रत्यागम रिक्त;                          \
        }                                      \
    } यावत् (0)

शून्य VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_Swap_दत्त *दत्त)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.renderTarget.colorFormat = दत्त->colorFormat;
    commonDialogParam.renderTarget.surfaceType = दत्त->surfaceType;
    commonDialogParam.renderTarget.color_Surface_दत्त = दत्त->color_Surface_दत्त;
    commonDialogParam.renderTarget.गभीरता_Surface_दत्त = दत्त->गभीरता_Surface_दत्त;
    commonDialogParam.renderTarget.विस्तारः = दत्त->विस्तारः;
    commonDialogParam.renderTarget.height = दत्त->height;
    commonDialogParam.renderTarget.stride_अन्तर्_Pixels = दत्त->stride_अन्तर्_Pixels;
    commonDialogParam.displaySyncObject = दत्त->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    प्रत्यागम true;
}

SDL_FunctionPointer VITA_GLES_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    प्रत्यागम egl_Get_Proc_स्थानाङ्कः(proc);
}

शून्य VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_दत्त->display);
}

स्थिर EGLint विस्तारः = 960;
स्थिर EGLint height = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{

    SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint अङ्कः_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC preSwapCallback;
    पूर्णाङ्क i;

    ध्रुव EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_संस्करणम्, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, रिक्त, रिक्त));
    wdata->उपयुङ्क्ते_gles = true;
    गवाक्षः->flags |= SDL_गवाक्षः_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_आकार;
    attribs[i++] = 8;
    attribs[i++] = EGL_गभीरता_आकार;
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

    EGLCHK(egl_वृणु_Config(display, attribs, &config, 1, &अङ्कः_configs));

    यदि (अङ्कः_configs == 0) {
        SDL_समुच्चयः_Error("No valid EGL configs for requested mode");
        प्रत्यागम रिक्त;
    }

    EGLCHK(surface = egl_Create_गवाक्षः_Surface(display, config, VITA_गवाक्षः_960_X544, रिक्त));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_विस्तारः, &विस्तारः));
    EGLCHK(eglQuerySurface(display, surface, EGL_HEIGHT, &height));

    _this->gl_दत्त->display = display;
    _this->gl_दत्त->context = context;
    _this->gl_दत्त->surface = surface;

    preSwapCallback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_स्थानाङ्कः("eglPigletVitaSetPreSwapCallbackSCE");
    preSwapCallback(VITA_GLES_KeyboardCallback);

    प्रत्यागम context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    यदि (!eglMakeCurrent(_this->gl_दत्त->display, _this->gl_दत्त->surface,
                        _this->gl_दत्त->surface, _this->gl_दत्त->context)) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to make EGL context current");
    }
    प्रत्यागम true;
}

bool VITA_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    EGLBoolean स्थितिः;
    स्थितिः = eglSwapInterval(_this->gl_दत्त->display, interval);
    यदि (स्थितिः == EGL_TRUE) {
        // Return success to upper level
        _this->gl_दत्त->swapinterval = interval;
        प्रत्यागम true;
    }
    // Failed to set swap interval
    प्रत्यागम SDL_समुच्चयः_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    *interval = _this->gl_दत्त->swapinterval;
    प्रत्यागम true;
}

bool VITA_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (!eglSwapBuffers(_this->gl_दत्त->display, _this->gl_दत्त->surface)) {
        प्रत्यागम SDL_समुच्चयः_Error("eglSwapBuffers() failed");
    }
    प्रत्यागम true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_दत्त *phdata = _this->आन्तरिकम्;
    EGLBoolean स्थितिः;

    यदि (phdata->egl_initialized != true) {
        प्रत्यागम SDL_समुच्चयः_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    यदि (_this->gl_दत्त->display != EGL_NO_DISPLAY) {
        यदि (context != EGL_NO_CONTEXT) {
            स्थितिः = eglDestroyContext(_this->gl_दत्त->display, context);
            यदि (स्थितिः != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                प्रत्यागम SDL_समुच्चयः_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA
