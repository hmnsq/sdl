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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11opengles.h"
#ضمن "SDL_x11opengl.h"
#ضمن "SDL_x11xsync.h"

#جيڪڏهن_وصف_نه_ٿيل EGL_PLATFORM_X11_KHR
#وصف_ڪريو EGL_PLATFORM_X11_KHR 0x31D5
#جيڪڏهن_پورو

// EGL implementation of SDL OpenGL support

فراغ X11_GLES_سيٽ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    إذا ((_this->gl_config.profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_ڀريو_Library = X11_GL_ڀريو_Library;
        _this->GL_Get_Proc_پتو = X11_GL_Get_Proc_پتو;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_سيٽ_مٽا_سٽا_Interval = X11_GL_سيٽ_مٽا_سٽا_Interval;
        _this->GL_Get_مٽا_سٽا_Interval = X11_GL_Get_مٽا_سٽا_Interval;
        _this->GL_مٽا_سٽا_دري = X11_GL_مٽا_سٽا_دري;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        أرجع X11_GL_ڀريو_Library(_this, رستو);
#وإلا
        أرجع SDL_سيٽ_Error("SDL not configured with OpenGL/GLX support");
#جيڪڏهن_پورو
    }

    أرجع SDL_EGL_ڀريو_Library(_this, رستو, (NativeDisplayType)معلومات->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, صحيح screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = عدم;
    EGLint visual_id = 0;
    XVisualInfo vi_اندريون;
    صحيح ٻاهريون_ڳڻپ = 0;

    إذا (!_this->egl_معلومات) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        أرجع عدم;
    }

    إذا (_this->egl_معلومات->eglGetConfigAttrib(_this->egl_معلومات->egl_display,
                                            _this->egl_معلومات->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    إذا (visual_id != 0) {
        vi_اندريون.screen = screen;
        vi_اندريون.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_اندريون, &ٻاهريون_ڳڻپ);
        إذا (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            إذا (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = عدم;
            }
        }
    }
    
    إذا(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_اندريون.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_نقاب,
                                            &vi_اندريون, &ٻاهريون_ڳڻپ);

        // Return the first transparent Visual
        إذا (transparent) {
            صحيح i;
            لكل (i = 0; i < ٻاهريون_ڳڻپ; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_اندريون.screen = screen;
                    vi_اندريون.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_اندريون, &ٻاهريون_ڳڻپ);
                    أرجع egl_visualinfo;
                }
            }
        }
    }
    أرجع egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_GLContext context;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, معلومات->egl_surface);
    X11_XSync(display, False);

    أرجع context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    أرجع معلومات->egl_surface;
}

bool X11_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    ثابت bool ret = SDL_EGL_مٽا_سٽا_Buffers(_this, دري->اندروني->egl_surface);                       \

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(دري);
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

    أرجع ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

