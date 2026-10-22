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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11opengles.h"
#अन्तर्भाव "SDL_x11opengl.h"
#अन्तर्भाव "SDL_x11xsync.h"

#यदि_अपरिभाषितम् EGL_PLATFORM_X11_KHR
#परिभाषय EGL_PLATFORM_X11_KHR 0x31D5
#यदि_अन्तः

// EGL implementation of SDL OpenGL support

शून्य X11_GLES_समुच्चयः_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    यदि ((_this->gl_config.profile_आवरणम् != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_आरोपय_Library = X11_GL_आरोपय_Library;
        _this->GL_Get_Proc_स्थानाङ्कः = X11_GL_Get_Proc_स्थानाङ्कः;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_समुच्चयः_Swap_Interval = X11_GL_समुच्चयः_Swap_Interval;
        _this->GL_GetSwapInterval = X11_GL_GetSwapInterval;
        _this->GL_Swap_गवाक्षः = X11_GL_Swap_गवाक्षः;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        प्रत्यागम X11_GL_आरोपय_Library(_this, मार्गः);
#अन्यथा
        प्रत्यागम SDL_समुच्चयः_Error("SDL not configured with OpenGL/GLX support");
#यदि_अन्तः
    }

    प्रत्यागम SDL_EGL_आरोपय_Library(_this, मार्गः, (NativeDisplayType)दत्त->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, पूर्णाङ्क screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = रिक्त;
    EGLint visual_id = 0;
    XVisualInfo vi_अन्तर्;
    पूर्णाङ्क बहिर्गमनम्_गणनम् = 0;

    यदि (!_this->egl_दत्त) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        प्रत्यागम रिक्त;
    }

    यदि (_this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display,
                                            _this->egl_दत्त->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    यदि (visual_id != 0) {
        vi_अन्तर्.screen = screen;
        vi_अन्तर्.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_आवरणम् | VisualIDMask, &vi_अन्तर्, &बहिर्गमनम्_गणनम्);
        यदि (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            यदि (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = रिक्त;
            }
        }
    }
    
    यदि(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_अन्तर्.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_आवरणम्,
                                            &vi_अन्तर्, &बहिर्गमनम्_गणनम्);

        // Return the first transparent Visual
        यदि (transparent) {
            पूर्णाङ्क i;
            प्रति (i = 0; i < बहिर्गमनम्_गणनम्; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                यदि (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_अन्तर्.screen = screen;
                    vi_अन्तर्.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_आवरणम् | VisualIDMask, &vi_अन्तर्, &बहिर्गमनम्_गणनम्);
                    प्रत्यागम egl_visualinfo;
                }
            }
        }
    }
    प्रत्यागम egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_GLContext context;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, दत्त->egl_surface);
    X11_XSync(display, False);

    प्रत्यागम context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    प्रत्यागम दत्त->egl_surface;
}

bool X11_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    ध्रुव bool ret = SDL_EGL_SwapBuffers(_this, गवाक्षः->आन्तरिकम्->egl_surface);                       \

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(गवाक्षः);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

    प्रत्यागम ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

