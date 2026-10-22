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

#که_نه_تعریف_شوی EGL_PLATFORM_X11_KHR
#تعریف_کړه EGL_PLATFORM_X11_KHR 0x31D5
#د_که_پای

// EGL implementation of SDL OpenGL support

فراغ X11_GLES_سېټ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    إذا ((_this->gl_config.profile_ماسک != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_بارول_Library = X11_GL_بارول_Library;
        _this->GL_Get_Proc_پته = X11_GL_Get_Proc_پته;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_سېټ_بدلون_Interval = X11_GL_سېټ_بدلون_Interval;
        _this->GL_Get_بدلون_Interval = X11_GL_Get_بدلون_Interval;
        _this->GL_بدلون_کړکۍ = X11_GL_بدلون_کړکۍ;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        أرجع X11_GL_بارول_Library(_this, لار);
#وإلا
        أرجع SDL_سېټ_Error("SDL not configured with OpenGL/GLX support");
#د_که_پای
    }

    أرجع SDL_EGL_بارول_Library(_this, لار, (NativeDisplayType)معلومات->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, صحيح screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = عدم;
    EGLint visual_id = 0;
    XVisualInfo vi_دننه;
    صحيح بهر_شمېر = 0;

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
        vi_دننه.screen = screen;
        vi_دننه.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ماسک | VisualIDMask, &vi_دننه, &بهر_شمېر);
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
        vi_دننه.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_ماسک,
                                            &vi_دننه, &بهر_شمېر);

        // Return the first transparent Visual
        إذا (transparent) {
            صحيح i;
            لكل (i = 0; i < بهر_شمېر; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                إذا (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_دننه.screen = screen;
                    vi_دننه.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ماسک | VisualIDMask, &vi_دننه, &بهر_شمېر);
                    أرجع egl_visualinfo;
                }
            }
        }
    }
    أرجع egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_GLContext context;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, معلومات->egl_surface);
    X11_XSync(display, False);

    أرجع context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    أرجع معلومات->egl_surface;
}

bool X11_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    ثابت bool ret = SDL_EGL_بدلون_Buffers(_this, کړکۍ->دننی->egl_surface);                       \

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(کړکۍ);
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

    أرجع ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#د_که_پای // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

