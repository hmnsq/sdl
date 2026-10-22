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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "SDL_qnx.h"

#অন্তর্ভাব "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
পূর্ণসংখ্যা QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint বাফার_bit_depth;
    EGLint alpha_bit_depth;

    _this->egl_তথ্য->eglGetConfigAttrib(_this->egl_তথ্য->egl_display, egl_conf, EGL_বাফার_আকার, &বাফার_bit_depth);
    _this->egl_তথ্য->eglGetConfigAttrib(_this->egl_তথ্য->egl_display, egl_conf, EGL_ALPHA_আকার, &alpha_bit_depth);

    নির্বাচন (বাফার_bit_depth) {
        ক্ষেত্র 32:
            ফেরত SCREEN_FORMAT_RGBX8888;
        ক্ষেত্র 24:
            ফেরত SCREEN_FORMAT_RGB888;
        ক্ষেত্র 16:
            নির্বাচন (alpha_bit_depth) {
                ক্ষেত্র 4:
                    ফেরত SCREEN_FORMAT_RGBX4444;
                ক্ষেত্র 1:
                    ফেরত SCREEN_FORMAT_RGBA5551;
                পূর্বনির্ধারিত:
                    ফেরত SCREEN_FORMAT_RGB565;
            }
        পূর্বনির্ধারিত:
            ফেরত 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *egl_path)
{
    ফেরত SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    ফেরত SDL_EGL_GetProcAddressInternal(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    ফেরত context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    ফেরত SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    ফেরত SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    {
        যদি (impl->resize) {
            EGLSurface surface;

            যদি (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                ফেরত false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            যদি (surface == EGL_NO_SURFACE) {
                ফেরত false;
            }
            SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, surface);

            যদি (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                ফেরত false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    ফেরত SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ফেরত SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
শূন্য QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
