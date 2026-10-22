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

#অন্তর্ভাৱ "SDL_internal.h"
#অন্তর্ভাৱ "SDL_qnx.h"

#অন্তর্ভাৱ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
পূর্ণাঙ্ক QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint buffer_bit_depth;
    EGLint alpha_bit_depth;

    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_BUFFER_SIZE, &buffer_bit_depth);
    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_ALPHA_SIZE, &alpha_bit_depth);

    ৱিকল্প (buffer_bit_depth) {
        পক্ষ 32:
            ঘূৰাই SCREEN_FORMAT_RGBX8888;
        পক্ষ 24:
            ঘূৰাই SCREEN_FORMAT_RGB888;
        পক্ষ 16:
            ৱিকল্প (alpha_bit_depth) {
                পক্ষ 4:
                    ঘূৰাই SCREEN_FORMAT_RGBX4444;
                পক্ষ 1:
                    ঘূৰাই SCREEN_FORMAT_RGBA5551;
                স্ৱভাৱ:
                    ঘূৰাই SCREEN_FORMAT_RGB565;
            }
        স্ৱভাৱ:
            ঘূৰাই 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *egl_path)
{
    ঘূৰাই SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *proc)
{
    ঘূৰাই SDL_EGL_GetProcAddressInternal(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    ঘূৰাই context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval)
{
    ঘূৰাই SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval)
{
    ঘূৰাই SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    {
        যদি (impl->resize) {
            EGLSurface surface;

            যদি (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                ঘূৰাই false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            যদি (surface == EGL_NO_SURFACE) {
                ঘূৰাই false;
            }
            SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, surface);

            যদি (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                ঘূৰাই false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    ঘূৰাই SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ঘূৰাই SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
শূন্য QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
