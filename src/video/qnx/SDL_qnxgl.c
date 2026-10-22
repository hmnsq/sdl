/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#شامل "SDL_qnx.h"

#شامل "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
صحیح QNX_انتخاب_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint بفر_ثنائی_ہندسہ_گہرائی;
    EGLint alpha_ثنائی_ہندسہ_گہرائی;

    _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, egl_conf, EGL_بفر_سائز, &بفر_ثنائی_ہندسہ_گہرائی);
    _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, egl_conf, EGL_ALPHA_سائز, &alpha_ثنائی_ہندسہ_گہرائی);

    انتخاب (بفر_ثنائی_ہندسہ_گہرائی) {
        حالت 32:
            واپس SCREEN_FORMAT_RGBX8888;
        حالت 24:
            واپس SCREEN_FORMAT_RGB888;
        حالت 16:
            انتخاب (alpha_ثنائی_ہندسہ_گہرائی) {
                حالت 4:
                    واپس SCREEN_FORMAT_RGBX4444;
                حالت 1:
                    واپس SCREEN_FORMAT_RGBA5551;
                طےشدہ:
                    واپس SCREEN_FORMAT_RGB565;
            }
        طےشدہ:
            واپس 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_راستہ)
{
    واپس SDL_EGL_بھرو_Library(_this, egl_راستہ, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_اشارہ_گر QNX_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس SDL_EGL_Get_Proc_پتہ_اندرونی(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    واپس context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    واپس SDL_EGL_سیٹ_تبادلہ_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    واپس SDL_EGL_Get_تبادلہ_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    {
        اگر (impl->resize) {
            EGLSurface surface;

            اگر (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                واپس false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)impl->کھڑکی);
            اگر (surface == EGL_NO_SURFACE) {
                واپس false;
            }
            SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_SURFACE_اشارہ_گر, surface);

            اگر (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                واپس false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    واپس SDL_EGL_تبادلہ_Buffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    واپس SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
خالی QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
