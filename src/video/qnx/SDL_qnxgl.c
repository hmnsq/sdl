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
صحيح QNX_ټاکنه_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint بفر_بټ_ژوروالی;
    EGLint alpha_بټ_ژوروالی;

    _this->egl_معلومات->eglGetConfigAttrib(_this->egl_معلومات->egl_display, egl_conf, EGL_بفر_اندازه, &بفر_بټ_ژوروالی);
    _this->egl_معلومات->eglGetConfigAttrib(_this->egl_معلومات->egl_display, egl_conf, EGL_ALPHA_اندازه, &alpha_بټ_ژوروالی);

    بدل (بفر_بټ_ژوروالی) {
        حالة 32:
            أرجع SCREEN_FORMAT_RGBX8888;
        حالة 24:
            أرجع SCREEN_FORMAT_RGB888;
        حالة 16:
            بدل (alpha_بټ_ژوروالی) {
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
bool QNX_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *egl_لار)
{
    أرجع SDL_EGL_بارول_Library(_this, egl_لار, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_اشاره_ګر QNX_GLES_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_پته_دننی(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    أرجع context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    أرجع SDL_EGL_سېټ_بدلون_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    أرجع SDL_EGL_Get_بدلون_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    {
        إذا (impl->resize) {
            EGLSurface surface;

            إذا (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                أرجع false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)impl->کړکۍ);
            إذا (surface == EGL_NO_SURFACE) {
                أرجع false;
            }
            SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_QNX_SURFACE_اشاره_ګر, surface);

            إذا (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                أرجع false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    أرجع SDL_EGL_بدلون_Buffers(_this, impl->egl_surface);
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
