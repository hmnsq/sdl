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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_VITA) && defined(SDL_VIDEO_VITA_PIB)
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "SDL_vitavideo.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#నిర్వచించు EGLCHK(stmt)                           \
    చేయి {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ఒకవేళ (err != EGL_SUCCESS) {              \
            SDL_సమితి_Error("EGL error %d", err); \
            తిరిగి ఖాళీ;                          \
        }                                      \
    } అయితే (0)

శూన్య VITA_GLES_KeyboardCallback(Sce_Piglet_Pre_మార్పిడి_దత్తాంశం *దత్తాంశం)
{
    SceCommonDialogUpdateParam commonDialogParam;
    SDL_zero(commonDialogParam);
    commonDialogParam.render_లక్ష్యం.colorFormat = దత్తాంశం->colorFormat;
    commonDialogParam.render_లక్ష్యం.surfaceType = దత్తాంశం->surfaceType;
    commonDialogParam.render_లక్ష్యం.color_Surface_దత్తాంశం = దత్తాంశం->color_Surface_దత్తాంశం;
    commonDialogParam.render_లక్ష్యం.లోతు_Surface_దత్తాంశం = దత్తాంశం->లోతు_Surface_దత్తాంశం;
    commonDialogParam.render_లక్ష్యం.వెడల్పు = దత్తాంశం->వెడల్పు;
    commonDialogParam.render_లక్ష్యం.ఎత్తు = దత్తాంశం->ఎత్తు;
    commonDialogParam.render_లక్ష్యం.stride_లోపల_Pixels = దత్తాంశం->stride_లోపల_Pixels;
    commonDialogParam.displaySyncObject = దత్తాంశం->displaySyncObject;

    sceCommonDialogUpdate(&commonDialogParam);
}

bool VITA_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    pibInit(PIB_SHACCCG | PIB_GET_PROC_ADDR_CORE);
    తిరిగి true;
}

SDL_Function_సూచిక VITA_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి egl_Get_Proc_చిరునామా(proc);
}

శూన్య VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_దత్తాంశం->display);
}

స్థిర EGLint వెడల్పు = 960;
స్థిర EGLint ఎత్తు = 544;

SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{

    SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint అంకె_configs;
    PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC pre_మార్పిడి_Callback;
    పూర్ణాంకం i;

    స్థిరరాశి EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_సంస్కరణ, 2,
        EGL_NONE
    };

    EGLCHK(display = eglGetDisplay(0));

    EGLCHK(eglInitialize(display, ఖాళీ, ఖాళీ));
    wdata->ఉపయోగిస్తుంది_gles = true;
    కిటికీ->flags |= SDL_కిటికీ_FULLSCREEN;

    EGLCHK(eglBindAPI(EGL_OPENGL_ES_API));

    i = 0;
    attribs[i++] = EGL_RED_కొలత;
    attribs[i++] = 8;
    attribs[i++] = EGL_GREEN_కొలత;
    attribs[i++] = 8;
    attribs[i++] = EGL_BLUE_కొలత;
    attribs[i++] = 8;
    attribs[i++] = EGL_లోతు_కొలత;
    attribs[i++] = 0;
    attribs[i++] = EGL_ALPHA_కొలత;
    attribs[i++] = 8;
    attribs[i++] = EGL_STENCIL_కొలత;
    attribs[i++] = 0;

    attribs[i++] = EGL_SURFACE_TYPE;
    attribs[i++] = 5;

    attribs[i++] = EGL_RENDERABLE_TYPE;
    attribs[i++] = EGL_OPENGL_ES2_బిట్టు;

    attribs[i++] = EGL_CONFORMANT;
    attribs[i++] = EGL_OPENGL_ES2_బిట్టు;

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ఎంచుకో_Config(display, attribs, &config, 1, &అంకె_configs));

    ఒకవేళ (అంకె_configs == 0) {
        SDL_సమితి_Error("No valid EGL configs for requested mode");
        తిరిగి ఖాళీ;
    }

    EGLCHK(surface = egl_Create_కిటికీ_Surface(display, config, VITA_కిటికీ_960_X544, ఖాళీ));

    EGLCHK(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs));

    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    EGLCHK(eglQuerySurface(display, surface, EGL_వెడల్పు, &వెడల్పు));
    EGLCHK(eglQuerySurface(display, surface, EGL_ఎత్తు, &ఎత్తు));

    _this->gl_దత్తాంశం->display = display;
    _this->gl_దత్తాంశం->context = context;
    _this->gl_దత్తాంశం->surface = surface;

    pre_మార్పిడి_Callback = (PFNEGLPIGLETVITASETPRESWAPCALLBACKSCEPROC)egl_Get_Proc_చిరునామా("eglPigletVitaSetPreSwapCallbackSCE");
    pre_మార్పిడి_Callback(VITA_GLES_KeyboardCallback);

    తిరిగి context;
}

bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    ఒకవేళ (!eglMakeCurrent(_this->gl_దత్తాంశం->display, _this->gl_దత్తాంశం->surface,
                        _this->gl_దత్తాంశం->surface, _this->gl_దత్తాంశం->context)) {
        తిరిగి SDL_సమితి_Error("Unable to make EGL context current");
    }
    తిరిగి true;
}

bool VITA_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    EGLBoolean స్థితి_2;
    స్థితి_2 = egl_మార్పిడి_Interval(_this->gl_దత్తాంశం->display, interval);
    ఒకవేళ (స్థితి_2 == EGL_TRUE) {
        // Return success to upper level
        _this->gl_దత్తాంశం->swapinterval = interval;
        తిరిగి true;
    }
    // Failed to set swap interval
    తిరిగి SDL_సమితి_Error("Unable to set the EGL swap interval");
}

bool VITA_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    *interval = _this->gl_దత్తాంశం->swapinterval;
    తిరిగి true;
}

bool VITA_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (!egl_మార్పిడి_Buffers(_this->gl_దత్తాంశం->display, _this->gl_దత్తాంశం->surface)) {
        తిరిగి SDL_సమితి_Error("eglSwapBuffers() failed");
    }
    తిరిగి true;
}

bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *phdata = _this->అంతర్గత;
    EGLBoolean స్థితి_2;

    ఒకవేళ (phdata->egl_initialized != true) {
        తిరిగి SDL_సమితి_Error("VITA: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ఒకవేళ (_this->gl_దత్తాంశం->display != EGL_NO_DISPLAY) {
        ఒకవేళ (context != EGL_NO_CONTEXT) {
            స్థితి_2 = eglDestroyContext(_this->gl_దత్తాంశం->display, context);
            ఒకవేళ (స్థితి_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                తిరిగి SDL_సమితి_Error("VITA: OpenGL ES context destroy error");
            }
        }
    }

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA
