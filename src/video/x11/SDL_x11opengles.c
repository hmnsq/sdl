/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11opengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11opengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_PLATFORM_X11_KHR
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_X11_KHR 0x31D5
#ಆದರೆ_ಅಂತ್ಯ

// EGL implementation of SDL OpenGL support

ಶೂನ್ಯ X11_GLES_ಗಣ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    ಆದರೆ ((_this->gl_config.profile_ಮುಖವಾಡ != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_ತುಂಬು_Library = X11_GL_ತುಂಬು_Library;
        _this->GL_Get_Proc_ವಿಳಾಸ = X11_GL_Get_Proc_ವಿಳಾಸ;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval = X11_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
        _this->GL_Get_ಅದಲುಬದಲು_Interval = X11_GL_Get_ಅದಲುಬದಲು_Interval;
        _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = X11_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        ಹಿಂತಿರುಗಿ X11_GL_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
#ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not configured with OpenGL/GLX support");
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, (NativeDisplayType)ದತ್ತಾಂಶ->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, ಪೂರ್ಣಾಂಕ screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = ಖಾಲಿ;
    EGLint visual_id = 0;
    XVisualInfo vi_ಒಳ;
    ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಎಣಿಕೆ = 0;

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                            _this->egl_ದತ್ತಾಂಶ->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    ಆದರೆ (visual_id != 0) {
        vi_ಒಳ.screen = screen;
        vi_ಒಳ.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ಮುಖವಾಡ | VisualIDMask, &vi_ಒಳ, &ಹೊರಹೋಗು_ಎಣಿಕೆ);
        ಆದರೆ (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            ಆದರೆ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = ಖಾಲಿ;
            }
        }
    }
    
    ಆದರೆ(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_ಒಳ.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_ಮುಖವಾಡ,
                                            &vi_ಒಳ, &ಹೊರಹೋಗು_ಎಣಿಕೆ);

        // Return the first transparent Visual
        ಆದರೆ (transparent) {
            ಪೂರ್ಣಾಂಕ i;
            ಗಾಗಿ (i = 0; i < ಹೊರಹೋಗು_ಎಣಿಕೆ; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_ಒಳ.screen = screen;
                    vi_ಒಳ.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ಮುಖವಾಡ | VisualIDMask, &vi_ಒಳ, &ಹೊರಹೋಗು_ಎಣಿಕೆ);
                    ಹಿಂತಿರುಗಿ egl_visualinfo;
                }
            }
        }
    }
    ಹಿಂತಿರುಗಿ egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_GLContext context;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, ದತ್ತಾಂಶ->egl_surface);
    X11_XSync(display, False);

    ಹಿಂತಿರುಗಿ context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->egl_surface;
}

bool X11_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಸ್ಥಿರಾಂಕ bool ret = SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);                       \

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ಹಿಂತಿರುಗಿ ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

