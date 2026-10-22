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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLCHK(stmt)                           \
    ਕਰੋ {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ਜੇ (err != EGL_SUCCESS) {              \
            SDL_ਸੈੱਟ_Error("EGL error %d", err); \
            ਵਾਪਸ ਨਿਰਾ;                          \
        }                                      \
    } ਜਦੋਂ (0)

ਖਾਲੀ VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_ਅਦਲਾ_ਬਦਲੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.colorFormat = ਅੰਕੜੇ->colorFormat;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.surfaceType = ਅੰਕੜੇ->surfaceType;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.color_Surface_ਅੰਕੜੇ = ਅੰਕੜੇ->color_Surface_ਅੰਕੜੇ;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.ਡੂੰਘਾਈ_Surface_ਅੰਕੜੇ = ਅੰਕੜੇ->ਡੂੰਘਾਈ_Surface_ਅੰਕੜੇ;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.ਚੌੜਾਈ = ਅੰਕੜੇ->ਚੌੜਾਈ;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.ਉਚਾਈ = ਅੰਕੜੇ->ਉਚਾਈ;
    commonDialogParam.render_ਨਿਸ਼ਾਨਾ.stride_ਵਿੱਚ_Pixels = ਅੰਕੜੇ->stride_ਵਿੱਚ_Pixels;
    commonDialogParam.displaySyncObject = ਅੰਕੜੇ->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    ਵਾਪਸ true;
}

SDL_Function_ਸੂਚਕ VITA_GLES_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਵਾਪਸ egl_Get_Proc_ਪਤਾ(proc);
}

ਖਾਲੀ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ਅੰਕੜੇ->display);
}

ਸਥਿਰ EGLint ਚੌੜਾਈ = 960;
ਸਥਿਰ EGLint ਉਚਾਈ = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint ਅੰਕ_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_ਅਦਲਾ_ਬਦਲੀ_Callback;
    ਪੂਰਨ i;

    ਅਚਲ EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_ਸੰਸਕਰਣ, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, ਨਿਰਾ, ਨਿਰਾ));
    wdata->ਵਰਤਦਾ_gles = true;
    ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_ਮਾਪ;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_ਮਾਪ;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_ਮਾਪ;
    attribs[i++] = 8;
    attribs[i++] = EGL_ਡੂੰਘਾਈ_ਮਾਪ;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_ਮਾਪ;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_ਮਾਪ;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_ਦੋਆਧਾਰੀ_ਅੰਕ;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_ਦੋਆਧਾਰੀ_ਅੰਕ;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ਚੁਣੋ_Config(display, attribs, &config, 1, &ਅੰਕ_configs));

    ਜੇ (ਅੰਕ_configs == 0) {
        SDL_ਸੈੱਟ_Error("No valid EGL configs for requested mode");
        ਵਾਪਸ ਨਿਰਾ;
    }

    EGLCHK(surface = egl_Create_ਖਿੜਕੀ_Surface(display, config, VITA_ਖਿੜਕੀ_960_X544, ਨਿਰਾ));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_ਚੌੜਾਈ, &ਚੌੜਾਈ));
    EGLCHK(eglQuerySurface(display, surface, EGL_ਉਚਾਈ, &ਉਚਾਈ));

    _this->gl_ਅੰਕੜੇ->display = display;
    _this->gl_ਅੰਕੜੇ->context = context;
    _this->gl_ਅੰਕੜੇ->surface = surface;

    pre_ਅਦਲਾ_ਬਦਲੀ_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_ਪਤਾ("eglPigletVitaSetPreSwapCallbackSCE");
    pre_ਅਦਲਾ_ਬਦਲੀ_Callback(VITA_GLES_KeyboardCallback);

    ਵਾਪਸ context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    ਜੇ (!eglMakeCurrent(_this->gl_ਅੰਕੜੇ->display, _this->gl_ਅੰਕੜੇ->surface,
                        _this->gl_ਅੰਕੜੇ->surface, _this->gl_ਅੰਕੜੇ->context)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to make EGL context current");
    }
    ਵਾਪਸ true;
}

bool VITA_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    EGLBoolean ਸਥਿਤੀ;
    ਸਥਿਤੀ = egl_ਅਦਲਾ_ਬਦਲੀ_Interval(_this->gl_ਅੰਕੜੇ->display, interval);
    ਜੇ (ਸਥਿਤੀ == EGL_TRUE) {
        // Return success to upper level
        _this->gl_ਅੰਕੜੇ->swapinterval = interval;
        ਵਾਪਸ true;
    }
    // Failed to set swap interval
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    *interval = _this->gl_ਅੰਕੜੇ->swapinterval;
    ਵਾਪਸ true;
}

bool VITA_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (!egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->gl_ਅੰਕੜੇ->display, _this->gl_ਅੰਕੜੇ->surface)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglSwapBuffers() failed");
    }
    ਵਾਪਸ true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *phdata = _this->ਅੰਦਰੂਨੀ;
    EGLBoolean ਸਥਿਤੀ;

    ਜੇ (phdata->egl_initialized != true) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ਜੇ (_this->gl_ਅੰਕੜੇ->display != EGL_NO_DISPLAY) {
        ਜੇ (context != EGL_NO_CONTEXT) {
            ਸਥਿਤੀ = eglDestroyContext(_this->gl_ਅੰਕੜੇ->display, context);
            ਜੇ (ਸਥਿਤੀ != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA
