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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11opengles.h"
#অন্তর্ভাব "SDL_x11opengl.h"
#অন্তর্ভাব "SDL_x11xsync.h"

#ifndef EGL_PLATFORM_X11_KHR
#define EGL_PLATFORM_X11_KHR 0x31D5
#endif

// EGL implementation of SDL OpenGL support

শূন্য X11_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    যদি ((_this->gl_config.profile_mask != SDL_GL_CONTEXT_PROFILE_ES) &&
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
        ফেরত X11_GL_LoadLibrary(_this, path);
#অন্যথা
        ফেরত SDL_SetError("SDL not configured with OpenGL/GLX support");
#endif
    }

    ফেরত SDL_EGL_LoadLibrary(_this, path, (NativeDisplayType)তথ্য->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, পূর্ণসংখ্যা screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = ফাঁকা;
    EGLint visual_id = 0;
    XVisualInfo vi_in;
    পূর্ণসংখ্যা out_গুনতি = 0;

    যদি (!_this->egl_তথ্য) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        ফেরত ফাঁকা;
    }

    যদি (_this->egl_তথ্য->eglGetConfigAttrib(_this->egl_তথ্য->egl_display,
                                            _this->egl_তথ্য->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    যদি (visual_id != 0) {
        vi_in.screen = screen;
        vi_in.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_গুনতি);
        যদি (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            যদি (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = ফাঁকা;
            }
        }
    }
    
    যদি(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_in.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            VisualScreenMask,
                                            &vi_in, &out_গুনতি);

        // Return the first transparent Visual
        যদি (transparent) {
            পূর্ণসংখ্যা i;
            জন্য (i = 0; i < out_গুনতি; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                যদি (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_in.screen = screen;
                    vi_in.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &vi_in, &out_গুনতি);
                    ফেরত egl_visualinfo;
                }
            }
        }
    }
    ফেরত egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext context;
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, তথ্য->egl_surface);
    X11_XSync(display, False);

    ফেরত context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    ফেরত তথ্য->egl_surface;
}

bool X11_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    ধ্রুবক bool ret = SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    ফেরত ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#endif // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

