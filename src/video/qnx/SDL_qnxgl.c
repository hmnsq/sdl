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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "SDL_qnx.h"

#అన్తర్భావ "../SDL_egl_c.h"

/**
 * Detertmines the pixel format to use based on the current display and EGL
 * configuration.
 */
పూర్ణాంకం QNX_ఎంచుకో_Format(SDL_VideoDevice *_this, EGLConfig egl_conf)
{
    EGLint బఫరు_బిట్టు_లోతు;
    EGLint alpha_బిట్టు_లోతు;

    _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, egl_conf, EGL_బఫరు_కొలత, &బఫరు_బిట్టు_లోతు);
    _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, egl_conf, EGL_ALPHA_కొలత, &alpha_బిట్టు_లోతు);

    ఎంపిక (బఫరు_బిట్టు_లోతు) {
        స్థితి 32:
            తిరిగి SCREEN_FORMAT_RGBX8888;
        స్థితి 24:
            తిరిగి SCREEN_FORMAT_RGB888;
        స్థితి 16:
            ఎంపిక (alpha_బిట్టు_లోతు) {
                స్థితి 4:
                    తిరిగి SCREEN_FORMAT_RGBX4444;
                స్థితి 1:
                    తిరిగి SCREEN_FORMAT_RGBA5551;
                అప్రమేయ:
                    తిరిగి SCREEN_FORMAT_RGB565;
            }
        అప్రమేయ:
            తిరిగి 0;
    }
}

/**
 * Initializes the EGL library.
 */
bool QNX_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *egl_మార్గం)
{
    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, egl_మార్గం, EGL_DEFAULT_DISPLAY);
}

/**
 * Finds the address of an EGL extension function.
 */
SDL_Function_సూచిక QNX_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి SDL_EGL_Get_Proc_చిరునామా_అంతర్గత(_this, proc);
}

/**
 * Associates the given window with the necessary EGL structures for drawing and
 * displaying content.
 */
SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    EGLContext      context;

    context = SDL_EGL_CreateContext(_this, impl->egl_surface);
    impl->context = context;

    తిరిగి context;
}

/**
 * Sets a new value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    తిరిగి SDL_EGL_సమితి_మార్పిడి_Interval(_this, interval);
}

/**
 * Gets the value for the number of frames to display before swapping buffers.
 */
bool QNX_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    తిరిగి SDL_EGL_Get_మార్పిడి_Interval(_this, interval);
}

/**
 * Swaps the EGL buffers associated with the given window
 */
bool QNX_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    {
        ఒకవేళ (impl->resize) {
            EGLSurface surface;

            ఒకవేళ (!SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, impl->context)) {
                తిరిగి false;
            }
            SDL_EGL_DestroySurface(_this, impl->egl_surface);

            surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)impl->కిటికీ);
            ఒకవేళ (surface == EGL_NO_SURFACE) {
                తిరిగి false;
            }
            SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_QNX_SURFACE_సూచిక, surface);

            ఒకవేళ (!SDL_EGL_MakeCurrent(_this, surface, impl->context)) {
                తిరిగి false;
            }

            impl->egl_surface = surface;
            impl->resize = false;
        }
    }

    తిరిగి SDL_EGL_మార్పిడి_Buffers(_this, impl->egl_surface);
}

/**
 * Destroys a context.
 */
bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    తిరిగి SDL_EGL_DestroyContext(_this, context);
}

/**
 * Terminates access to the EGL library.
 */
శూన్య QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}

SDL_EGL_MakeCurrent_impl(QNX)
