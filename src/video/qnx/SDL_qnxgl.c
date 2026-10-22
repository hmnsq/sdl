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

#समावेश "SDL_internal.h"
#समावेश "SDL_qnx.h"

#समावेश "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
पूर्णांक QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint बफर_bit_depth;
    EGLint alpha_bit_depth;

    _this->egl_तथ्य->eglGetConfigAttrib(_this->egl_तथ्य->egl_display, egl_conf, EGL_बफर_आकार, &बफर_bit_depth);
    _this->egl_तथ्य->eglGetConfigAttrib(_this->egl_तथ्य->egl_display, egl_conf, EGL_ALPHA_आकार, &alpha_bit_depth);

    चयन (बफर_bit_depth) {
        हाल 32:
            वापस SCREEN_FORMAT_RGBX8888;
        हाल 24:
            वापस SCREEN_FORMAT_RGB888;
        हाल 16:
            चयन (alpha_bit_depth) {
                हाल 4:
                    वापस SCREEN_FORMAT_RGBX4444;
                हाल 1:
                    वापस SCREEN_FORMAT_RGBA5551;
                शेष:
                    वापस SCREEN_FORMAT_RGB565;
            }
        शेष:
            वापस 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *egl_path)
{
    वापस SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    वापस SDL_EGL_GetProcAddressInternal(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    वापस context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    वापस SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    वापस SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    {
        अगर (impl->resize) {
            EGLSurface surface;

            अगर (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                वापस false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            अगर (surface == EGL_NO_SURFACE) {
                वापस false;
            }
            SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, surface);

            अगर (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                वापस false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    वापस SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    वापस SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
व्योम QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
