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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"
#ଅନ୍ତର୍ଭାଵ "SDL_qnx.h"

#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint buffer_bit_depth;
    EGLint alpha_bit_depth;

    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_BUFFER_SIZE, &buffer_bit_depth);
    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_ALPHA_SIZE, &alpha_bit_depth);

    ବାଛ (buffer_bit_depth) {
        ସ୍ଥିତି 32:
            ଫେରନ୍ତୁ SCREEN_FORMAT_RGBX8888;
        ସ୍ଥିତି 24:
            ଫେରନ୍ତୁ SCREEN_FORMAT_RGB888;
        ସ୍ଥିତି 16:
            ବାଛ (alpha_bit_depth) {
                ସ୍ଥିତି 4:
                    ଫେରନ୍ତୁ SCREEN_FORMAT_RGBX4444;
                ସ୍ଥିତି 1:
                    ଫେରନ୍ତୁ SCREEN_FORMAT_RGBA5551;
                ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                    ଫେରନ୍ତୁ SCREEN_FORMAT_RGB565;
            }
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *egl_path)
{
    ଫେରନ୍ତୁ SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc)
{
    ଫେରନ୍ତୁ SDL_EGL_GetProcAddressInternal(_this, proc);
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

    ଫେରନ୍ତୁ context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    ଫେରନ୍ତୁ SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval)
{
    ଫେରନ୍ତୁ SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    {
        ଯଦି (impl->resize) {
            EGLSurface surface;

            ଯଦି (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                ଫେରନ୍ତୁ false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            ଯଦି (surface == EGL_NO_SURFACE) {
                ଫେରନ୍ତୁ false;
            }
            SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, surface);

            ଯଦି (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                ଫେରନ୍ତୁ false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    ଫେରନ୍ତୁ SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    ଫେରନ୍ତୁ SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
ଶୂନ୍ୟ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
