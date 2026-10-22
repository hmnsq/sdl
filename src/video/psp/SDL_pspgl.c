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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

#شامل <stdlib.h>
#شامل <string.h>

#شامل "SDL_pspvideo.h"
#شامل "SDL_pspgl_c.h"

/*****************************************************************************/
// SDL OpenGL/OpenGL ES functions
/*****************************************************************************/
#تعریف_کرو EGLCHK(stmt)                           \
    کرو {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        اگر (err != EGL_SUCCESS) {              \
            SDL_سیٹ_Error("EGL error %d", err); \
            واپس تہی;                          \
        }                                      \
    } جب (0)

bool PSP_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    واپس true;
}

/* pspgl doesn't provide this call, so stub it out since SDL requires it.
#define GLSTUB(func,params) void func params {}

GLSTUB(glOrtho,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                    GLdouble zNear, GLdouble zFar))
*/
SDL_Function_اشارہ_گر PSP_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس egl_Get_Proc_پتہ(proc);
}

خالی PSP_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    eglTerminate(_this->gl_ڈیٹا->display);
}

ساکن EGLint چوڑائی = 480;
ساکن EGLint اونچائی = 272;

SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{

    SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

    EGLint attribs[32];
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint عدد_configs;
    صحیح i;

    // EGL init taken from glutCreateWindow() in PSPGL's glut.c.
    EGLCHK(display = eglGetDisplay(0));
    EGLCHK(eglInitialize(display, تہی, تہی));
    wdata->استعمال_کرتا_gles = true;
    کھڑکی->flags |= SDL_کھڑکی_FULLSCREEN;

    // Setup the config based on SDL's current values.
    i = 0;
    attribs[i++] = EGL_RED_سائز;
    attribs[i++] = _this->gl_config.red_سائز;
    attribs[i++] = EGL_GREEN_سائز;
    attribs[i++] = _this->gl_config.green_سائز;
    attribs[i++] = EGL_BLUE_سائز;
    attribs[i++] = _this->gl_config.blue_سائز;
    attribs[i++] = EGL_گہرائی_سائز;
    attribs[i++] = _this->gl_config.گہرائی_سائز;

    اگر (_this->gl_config.alpha_سائز) {
        attribs[i++] = EGL_ALPHA_سائز;
        attribs[i++] = _this->gl_config.alpha_سائز;
    }
    اگر (_this->gl_config.stencil_سائز) {
        attribs[i++] = EGL_STENCIL_سائز;
        attribs[i++] = _this->gl_config.stencil_سائز;
    }

    attribs[i++] = EGL_NONE;

    EGLCHK(egl_انتخاب_Config(display, attribs, &config, 1, &عدد_configs));

    اگر (عدد_configs == 0) {
        SDL_سیٹ_Error("No valid EGL configs for requested mode");
        واپس تہی;
    }

    EGLCHK(eglGetConfigAttrib(display, config, EGL_چوڑائی, &چوڑائی));
    EGLCHK(eglGetConfigAttrib(display, config, EGL_اونچائی, &اونچائی));

    EGLCHK(context = eglCreateContext(display, config, تہی, تہی));
    EGLCHK(surface = egl_Create_کھڑکی_Surface(display, config, 0, تہی));
    EGLCHK(eglMakeCurrent(display, surface, surface, context));

    _this->gl_ڈیٹا->display = display;
    _this->gl_ڈیٹا->context = context;
    _this->gl_ڈیٹا->surface = surface;

    واپس context;
}

bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    اگر (!eglMakeCurrent(_this->gl_ڈیٹا->display, _this->gl_ڈیٹا->surface,
                        _this->gl_ڈیٹا->surface, _this->gl_ڈیٹا->context)) {
        واپس SDL_سیٹ_Error("Unable to make EGL context current");
    }
    واپس true;
}

bool PSP_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    EGLBoolean حالت_2;
    حالت_2 = egl_تبادلہ_Interval(_this->gl_ڈیٹا->display, interval);
    اگر (حالت_2 == EGL_TRUE) {
        // Return success to upper level
        _this->gl_ڈیٹا->swapinterval = interval;
        واپس true;
    }
    // Failed to set swap interval
    واپس SDL_سیٹ_Error("Unable to set the EGL swap interval");
}

bool PSP_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    *interval = _this->gl_ڈیٹا->swapinterval;
    واپس true;
}

bool PSP_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (!egl_تبادلہ_Buffers(_this->gl_ڈیٹا->display, _this->gl_ڈیٹا->surface)) {
        واپس SDL_سیٹ_Error("eglSwapBuffers() failed");
    }
    واپس true;
}

bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *phdata = _this->اندرونی_2;
    EGLBoolean حالت_2;

    اگر (phdata->egl_initialized != true) {
        واپس SDL_سیٹ_Error("PSP: GLES initialization failed, no OpenGL ES support");
    }

    // Check if OpenGL ES connection has been initialized
    اگر (_this->gl_ڈیٹا->display != EGL_NO_DISPLAY) {
        اگر (context != EGL_NO_CONTEXT) {
            حالت_2 = eglDestroyContext(_this->gl_ڈیٹا->display, context);
            اگر (حالت_2 != EGL_TRUE) {
                // Error during OpenGL ES context destroying
                واپس SDL_سیٹ_Error("PSP: OpenGL ES context destroy error");
            }
        }
    }
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_PSP
