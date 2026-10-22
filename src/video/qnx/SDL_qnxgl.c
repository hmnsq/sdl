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

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "SDL_qnx.h"

#അന്തര്ഭാവ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
പൂർണ്ണസംഖ്യ QNX_ChooseFormat(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint buffer_bit_depth;
    EGLint alpha_bit_depth;

    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_BUFFER_SIZE, &buffer_bit_depth);
    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, egl_conf, EGL_ALPHA_SIZE, &alpha_bit_depth);

    തിരഞ്ഞെടുപ്പ് (buffer_bit_depth) {
        അവസ്ഥ 32:
            തിരികെ SCREEN_FORMAT_RGBX8888;
        അവസ്ഥ 24:
            തിരികെ SCREEN_FORMAT_RGB888;
        അവസ്ഥ 16:
            തിരഞ്ഞെടുപ്പ് (alpha_bit_depth) {
                അവസ്ഥ 4:
                    തിരികെ SCREEN_FORMAT_RGBX4444;
                അവസ്ഥ 1:
                    തിരികെ SCREEN_FORMAT_RGBA5551;
                സ്ഥിരസ്ഥിതി:
                    തിരികെ SCREEN_FORMAT_RGB565;
            }
        സ്ഥിരസ്ഥിതി:
            തിരികെ 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *egl_path)
{
    തിരികെ SDL_EGL_LoadLibrary(_this, egl_path, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    തിരികെ SDL_EGL_GetProcAddressInternal(_this, proc);
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

    തിരികെ context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    തിരികെ SDL_EGL_SetSwapInterval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval)
{
    തിരികെ SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    {
        എങ്കിൽ (impl->resize) {
            EGLSurface surface;

            എങ്കിൽ (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                തിരികെ false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
            എങ്കിൽ (surface == EGL_NO_SURFACE) {
                തിരികെ false;
            }
            SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, surface);

            എങ്കിൽ (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                തിരികെ false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    തിരികെ SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    തിരികെ SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
ശൂന്യം QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
