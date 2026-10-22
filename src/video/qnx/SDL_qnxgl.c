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

#ضمن "SDL_internal.h"
#ضمن "SDL_qnx.h"

#ضمن "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
صحيح QNX_چنو_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint بفر_ثنائی_ہندسہ_ڈونگھائی;
    EGLint alpha_ثنائی_ہندسہ_ڈونگھائی;

    _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, egl_conf, EGL_بفر_ناپ, &بفر_ثنائی_ہندسہ_ڈونگھائی);
    _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, egl_conf, EGL_ALPHA_ناپ, &alpha_ثنائی_ہندسہ_ڈونگھائی);

    بدل (بفر_ثنائی_ہندسہ_ڈونگھائی) {
        حالة 32:
            أرجع SCREEN_FORMAT_RGBX8888;
        حالة 24:
            أرجع SCREEN_FORMAT_RGB888;
        حالة 16:
            بدل (alpha_ثنائی_ہندسہ_ڈونگھائی) {
                حالة 4:
                    أرجع SCREEN_FORMAT_RGBX4444;
                حالة 1:
                    أرجع SCREEN_FORMAT_RGBA5551;
                افتراضي:
                    أرجع SCREEN_FORMAT_RGB565;
            }
        افتراضي:
            أرجع 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_رستہ)
{
    أرجع SDL_EGL_لدو_Library(_this, egl_رستہ, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_اشارہ_گر QNX_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_پتہ_اندرونی(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    أرجع context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    أرجع SDL_EGL_سیٹ_وٹاندرا_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    أرجع SDL_EGL_Get_وٹاندرا_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    {
        إذا (impl->resize) {
            EGLSurface surface;

            إذا (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                أرجع false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)impl->کھڑکی);
            إذا (surface == EGL_NO_SURFACE) {
                أرجع false;
            }
            SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_SURFACE_اشارہ_گر, surface);

            إذا (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                أرجع false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    أرجع SDL_EGL_وٹاندرا_Buffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    أرجع SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
فراغ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
