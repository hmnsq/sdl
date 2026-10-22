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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_qnx.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
ਪੂਰਨ QNX_ਚੁਣੋ_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ;
    EGLint alpha_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ;

    _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, egl_conf, EGL_ਬਫਰ_ਮਾਪ, &ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ);
    _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, egl_conf, EGL_ALPHA_ਮਾਪ, &alpha_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ);

    ਚੋਣ (ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ) {
        ਹਾਲਤ 32:
            ਵਾਪਸ SCREEN_FORMAT_RGBX8888;
        ਹਾਲਤ 24:
            ਵਾਪਸ SCREEN_FORMAT_RGB888;
        ਹਾਲਤ 16:
            ਚੋਣ (alpha_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ) {
                ਹਾਲਤ 4:
                    ਵਾਪਸ SCREEN_FORMAT_RGBX4444;
                ਹਾਲਤ 1:
                    ਵਾਪਸ SCREEN_FORMAT_RGBA5551;
                ਮੂਲ:
                    ਵਾਪਸ SCREEN_FORMAT_RGB565;
            }
        ਮੂਲ:
            ਵਾਪਸ 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *egl_ਰਸਤਾ)
{
    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, egl_ਰਸਤਾ, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_ਸੂਚਕ QNX_GLES_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਵਾਪਸ SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    ਵਾਪਸ context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    ਵਾਪਸ SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਵਾਪਸ SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    {
        ਜੇ (impl->resize) {
            EGLSurface surface;

            ਜੇ (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                ਵਾਪਸ false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)impl->ਖਿੜਕੀ);
            ਜੇ (surface == EGL_NO_SURFACE) {
                ਵਾਪਸ false;
            }
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_QNX_SURFACE_ਸੂਚਕ, surface);

            ਜੇ (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                ਵਾਪਸ false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    ਵਾਪਸ SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ਵਾਪਸ SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
ਖਾਲੀ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
