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

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "SDL_qnx.h"

#अन्तर्भाव "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
पूर्णाङ्क QNX_वृणु_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint बफर_bit_गभीरता;
    EGLint alpha_bit_गभीरता;

    _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, egl_conf, EGL_बफर_आकार, &बफर_bit_गभीरता);
    _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, egl_conf, EGL_ALPHA_आकार, &alpha_bit_गभीरता);

    विकल्प (बफर_bit_गभीरता) {
        पक्ष 32:
            प्रत्यागम SCREEN_FORMAT_RGBX8888;
        पक्ष 24:
            प्रत्यागम SCREEN_FORMAT_RGB888;
        पक्ष 16:
            विकल्प (alpha_bit_गभीरता) {
                पक्ष 4:
                    प्रत्यागम SCREEN_FORMAT_RGBX4444;
                पक्ष 1:
                    प्रत्यागम SCREEN_FORMAT_RGBA5551;
                स्वभाव:
                    प्रत्यागम SCREEN_FORMAT_RGB565;
            }
        स्वभाव:
            प्रत्यागम 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_मार्गः)
{
    प्रत्यागम SDL_EGL_आरोपय_Library(_this, egl_मार्गः, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_FunctionPointer QNX_GLES_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    प्रत्यागम SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    प्रत्यागम context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    प्रत्यागम SDL_EGL_समुच्चयः_Swap_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    प्रत्यागम SDL_EGL_GetSwapInterval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    {
        यदि (impl->resize) {
            EGLSurface surface;

            यदि (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                प्रत्यागम false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)impl->गवाक्षः);
            यदि (surface == EGL_NO_SURFACE) {
                प्रत्यागम false;
            }
            SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_QNX_SURFACE_POINTER, surface);

            यदि (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                प्रत्यागम false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    प्रत्यागम SDL_EGL_SwapBuffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    प्रत्यागम SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
शून्य QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
