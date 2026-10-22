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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#شامل "SDL_x11video.h"
#شامل "SDL_x11opengles.h"
#شامل "SDL_x11opengl.h"
#شامل "SDL_x11xsync.h"

#اگر_غیر_تعریف_شدہ EGL_PLATFORM_X11_KHR
#تعریف_کرو EGL_PLATFORM_X11_KHR 0x31D5
#اگر_ختم

// EGL implementation of SDL OpenGL support

خالی X11_GLES_سیٹ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    اگر ((_this->gl_config.profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_بھرو_Library = X11_GL_بھرو_Library;
        _this->GL_Get_Proc_پتہ = X11_GL_Get_Proc_پتہ;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_سیٹ_تبادلہ_Interval = X11_GL_سیٹ_تبادلہ_Interval;
        _this->GL_Get_تبادلہ_Interval = X11_GL_Get_تبادلہ_Interval;
        _this->GL_تبادلہ_کھڑکی = X11_GL_تبادلہ_کھڑکی;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        واپس X11_GL_بھرو_Library(_this, راستہ);
#ورنہ
        واپس SDL_سیٹ_Error("SDL not configured with OpenGL/GLX support");
#اگر_ختم
    }

    واپس SDL_EGL_بھرو_Library(_this, راستہ, (NativeDisplayType)ڈیٹا->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, صحیح screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = تہی;
    EGLint visual_id = 0;
    XVisualInfo vi_اندر;
    صحیح برآمد_گنتی = 0;

    اگر (!_this->egl_ڈیٹا) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        واپس تہی;
    }

    اگر (_this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display,
                                            _this->egl_ڈیٹا->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    اگر (visual_id != 0) {
        vi_اندر.screen = screen;
        vi_اندر.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_اندر, &برآمد_گنتی);
        اگر (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            اگر (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = تہی;
            }
        }
    }
    
    اگر(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_اندر.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_نقاب,
                                            &vi_اندر, &برآمد_گنتی);

        // Return the first transparent Visual
        اگر (transparent) {
            صحیح i;
            برائے (i = 0; i < برآمد_گنتی; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                اگر (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_اندر.screen = screen;
                    vi_اندر.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_نقاب | VisualIDMask, &vi_اندر, &برآمد_گنتی);
                    واپس egl_visualinfo;
                }
            }
        }
    }
    واپس egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext context;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, ڈیٹا->egl_surface);
    X11_XSync(display, False);

    واپس context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    واپس ڈیٹا->egl_surface;
}

bool X11_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    ثابت bool ret = SDL_EGL_تبادلہ_Buffers(_this, کھڑکی->اندرونی_2->egl_surface);                       \

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(کھڑکی);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

    واپس ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#اگر_ختم // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

