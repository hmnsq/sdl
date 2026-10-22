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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_PSP

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "SDL_pspvideo.h"
#అన్తర్భావ "SDL_pspgl_c.h"

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

bool PSP_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    తిరిగి true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_సూచిక PSP_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి egl_Get_Proc_చిరునామా(proc);
}

శూన్య PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_దత్తాంశం->display);
}

స్థిర EGLint వెడల్పు = 480;
స్థిర EGLint ఎత్తు = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{

    SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint అంకె_configs;
    పూర్ణాంకం i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, ఖాళీ, ఖాళీ));
    wdata->ఉపయోగిస్తుంది_gles = true;
    కిటికీ->flags |= SDL_కిటికీ_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_కొలత;
    attribs[i++] = _this->gl_config.red_కొలత;
    attribs[i++] = EGL_GREEN_కొలత;
    attribs[i++] = _this->gl_config.green_కొలత;
    attribs[i++] = EGL_BLUE_కొలత;
    attribs[i++] = _this->gl_config.blue_కొలత;
    attribs[i++] = EGL_లోతు_కొలత;
    attribs[i++] = _this->gl_config.లోతు_కొలత;

    ఒకవేళ (_this->gl_config.alpha_కొలత) {
        attribs[i++] = EGL_ALPHA_కొలత;
        attribs[i++] = _this->gl_config.alpha_కొలత;
    }
    ఒకవేళ (_this->gl_config.stencil_కొలత) {
        attribs[i++] = EGL_STENCIL_కొలత;
        attribs[i++] = _this->gl_config.stencil_కొలత;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_ఎంచుకో_Config(display, attribs, &config, 1, &అంకె_configs));

    ఒకవేళ (అంకె_configs == 0) {
        SDL_సమితి_Error("No valid EGL configs for requested mode");
        తిరిగి ఖాళీ;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_వెడల్పు, &వెడల్పు));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_ఎత్తు, &ఎత్తు));

    EGLCHK(context = eglCreateContext(display, config, ఖాళీ, ఖాళీ));
    EGLCHK(surface = egl_Create_కిటికీ_Surface(display, config, 0, ఖాళీ));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_దత్తాంశం->display = display;
    _this->gl_దత్తాంశం->context = context;
    _this->gl_దత్తాంశం->surface = surface;

    తిరిగి context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    ఒకవేళ (!eglMakeCurrent(_this->gl_దత్తాంశం->display, _this->gl_దత్తాంశం->surface,
                        _this->gl_దత్తాంశం->surface, _this->gl_దత్తాంశం->context)) {
        తిరిగి SDL_సమితి_Error("Unable to make EGL context current");
    }
    తిరిగి true;
}

bool PSP_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
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

bool PSP_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    *interval = _this->gl_దత్తాంశం->swapinterval;
    తిరిగి true;
}

bool PSP_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (!egl_మార్పిడి_Buffers(_this->gl_దత్తాంశం->display, _this->gl_దత్తాంశం->surface)) {
        తిరిగి SDL_సమితి_Error("eglSwapBuffers() failed");
    }
    తిరిగి true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *phdata = _this->అంతర్గత;
    EGLBoolean స్థితి_2;

    ఒకవేళ (phdata->egl_initialized != true) {
        తిరిగి SDL_సమితి_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    ఒకవేళ (_this->gl_దత్తాంశం->display != EGL_NO_DISPLAY) {
        ఒకవేళ (context != EGL_NO_CONTEXT) {
            స్థితి_2 = eglDestroyContext(_this->gl_దత్తాంశం->display, context);
            ఒకవేళ (స్థితి_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                తిరిగి SDL_సమితి_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_PSP
