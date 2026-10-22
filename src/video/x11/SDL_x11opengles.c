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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11opengles.h"
#அந்தர்பாவ "SDL_x11opengl.h"
#அந்தர்பாவ "SDL_x11xsync.h"

#ifndef EGL_PLATFORM_X11_KHR
#define EGL_PLATFORM_X11_KHR 0x31D5
#endif

// EGL implementation of SDL OpenGL support

வெறுமை X11_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    SDL_VideoData *data = _this->internal;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    எனில் ((_this->gl_config.profile_mask != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ifdef SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_LoadLibrary = X11_GL_LoadLibrary;
        _this->GL_GetProcAddress = X11_GL_GetProcAddress;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_SetSwapInterval = X11_GL_SetSwapInterval;
        _this->GL_GetSwapInterval = X11_GL_GetSwapInterval;
        _this->GL_SwapWindow = X11_GL_SwapWindow;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        திரும்பு X11_GL_LoadLibrary(_this, path);
#இல்லையெனில்
        திரும்பு SDL_SetError("SDL not configured with OpenGL/GLX support");
#endif
    }

    திரும்பு SDL_EGL_LoadLibrary(_this, path, (NativeDisplayType)data->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, முழு screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = வெற்று;
    EGLint visual_id = 0;
    XVisualInfo vi_in;
    முழு out_மொத்தம் = 0;

    எனில் (!_this->egl_data) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        திரும்பு வெற்று;
    }

    எனில் (_this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display,
                                            _this->egl_data->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    எனில் (visual_id != 0) {
        vi_in.screen = screen;
        vi_in.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_மொத்தம்);
        எனில் (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            எனில் (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = வெற்று;
            }
        }
    }
    
    எனில்(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_in.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            VisualScreenMask,
                                            &vi_in, &out_மொத்தம்);

        // Return the first transparent Visual
        எனில் (transparent) {
            முழு i;
            க்கு (i = 0; i < out_மொத்தம்; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                எனில் (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_in.screen = screen;
                    vi_in.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_மொத்தம்);
                    திரும்பு egl_visualinfo;
                }
            }
        }
    }
    திரும்பு egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext context;
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, data->egl_surface);
    X11_XSync(display, False);

    திரும்பு context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    திரும்பு data->egl_surface;
}

bool X11_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    மாறிலி bool ret = SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    திரும்பு ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

