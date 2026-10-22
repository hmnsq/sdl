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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_PLATFORM_X11_KHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_X11_KHR 0x31D5
#ਜੇ_ਅੰਤ

// EGL implementation of SDL OpenGL support

ਖਾਲੀ X11_GLES_ਸੈੱਟ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    ਜੇ ((_this->gl_config.profile_ਨਕਾਬ != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_ਲੱਦੋ_Library = X11_GL_ਲੱਦੋ_Library;
        _this->GL_Get_Proc_ਪਤਾ = X11_GL_Get_Proc_ਪਤਾ;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
        _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = X11_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        ਵਾਪਸ X11_GL_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
#ਨਹੀਂਤਾਂ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL not configured with OpenGL/GLX support");
#ਜੇ_ਅੰਤ
    }

    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, (NativeDisplayType)ਅੰਕੜੇ->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, ਪੂਰਨ screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = ਨਿਰਾ;
    EGLint visual_id = 0;
    XVisualInfo vi_ਵਿੱਚ;
    ਪੂਰਨ ਬਾਹਰਲਾ_ਗਿਣਤੀ = 0;

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (_this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display,
                                            _this->egl_ਅੰਕੜੇ->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    ਜੇ (visual_id != 0) {
        vi_ਵਿੱਚ.screen = screen;
        vi_ਵਿੱਚ.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ਨਕਾਬ | VisualIDMask, &vi_ਵਿੱਚ, &ਬਾਹਰਲਾ_ਗਿਣਤੀ);
        ਜੇ (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            ਜੇ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = ਨਿਰਾ;
            }
        }
    }
    
    ਜੇ(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_ਵਿੱਚ.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_ਨਕਾਬ,
                                            &vi_ਵਿੱਚ, &ਬਾਹਰਲਾ_ਗਿਣਤੀ);

        // Return the first transparent Visual
        ਜੇ (transparent) {
            ਪੂਰਨ i;
            ਲਈ (i = 0; i < ਬਾਹਰਲਾ_ਗਿਣਤੀ; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_ਵਿੱਚ.screen = screen;
                    vi_ਵਿੱਚ.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ਨਕਾਬ | VisualIDMask, &vi_ਵਿੱਚ, &ਬਾਹਰਲਾ_ਗਿਣਤੀ);
                    ਵਾਪਸ egl_visualinfo;
                }
            }
        }
    }
    ਵਾਪਸ egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_GLContext context;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, ਅੰਕੜੇ->egl_surface);
    X11_XSync(display, False);

    ਵਾਪਸ context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਵਾਪਸ ਅੰਕੜੇ->egl_surface;
}

bool X11_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਅਚਲ bool ret = SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);                       \

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ਵਾਪਸ ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

