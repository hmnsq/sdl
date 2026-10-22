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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11opengles.h"
#అన్తర్భావ "SDL_x11opengl.h"
#అన్తర్భావ "SDL_x11xsync.h"

#నిర్వచితం_కాకపోతే EGL_PLATFORM_X11_KHR
#నిర్వచించు EGL_PLATFORM_X11_KHR 0x31D5
#అయితే_ముగింపు

// EGL implementation of SDL OpenGL support

శూన్య X11_GLES_సమితి_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_X11_KHR;
}

bool X11_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    // If the profile requested is not GL ES, switch over to X11_GL functions
    ఒకవేళ ((_this->gl_config.profile_ముసుగు != SDL_GL_CONTEXT_PROFILE_ES) &&
        !SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
        X11_GLES_UnloadLibrary(_this);
        _this->GL_ఎక్కించు_Library = X11_GL_ఎక్కించు_Library;
        _this->GL_Get_Proc_చిరునామా = X11_GL_Get_Proc_చిరునామా;
        _this->GL_UnloadLibrary = X11_GL_UnloadLibrary;
        _this->GL_CreateContext = X11_GL_CreateContext;
        _this->GL_MakeCurrent = X11_GL_MakeCurrent;
        _this->GL_సమితి_మార్పిడి_Interval = X11_GL_సమితి_మార్పిడి_Interval;
        _this->GL_Get_మార్పిడి_Interval = X11_GL_Get_మార్పిడి_Interval;
        _this->GL_మార్పిడి_కిటికీ = X11_GL_మార్పిడి_కిటికీ;
        _this->GL_DestroyContext = X11_GL_DestroyContext;
        తిరిగి X11_GL_ఎక్కించు_Library(_this, మార్గం);
#లేకపోతే
        తిరిగి SDL_సమితి_Error("SDL not configured with OpenGL/GLX support");
#అయితే_ముగింపు
    }

    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, (NativeDisplayType)దత్తాంశం->display);
}

XVisualInfo *X11_GLES_GetVisual(SDL_VideoDevice *_this, Display *display, పూర్ణాంకం screen, bool transparent)
{

    XVisualInfo *egl_visualinfo = ఖాళీ;
    EGLint visual_id = 0;
    XVisualInfo vi_లోపల;
    పూర్ణాంకం బహిర్గతం_లెక్క = 0;

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        // The EGL library wasn't loaded, SDL_GetError() should have info
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (_this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display,
                                            _this->egl_దత్తాంశం->egl_config,
                                            EGL_NATIVE_VISUAL_ID,
                                            &visual_id) == EGL_FALSE) {
        visual_id = 0;
    }
    ఒకవేళ (visual_id != 0) {
        vi_లోపల.screen = screen;
        vi_లోపల.visualid = visual_id;
        egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ముసుగు | VisualIDMask, &vi_లోపల, &బహిర్గతం_లెక్క);
        ఒకవేళ (transparent && egl_visualinfo) {
            Uint32 format = X11_GetPixelFormatFromVisualInfo(display, egl_visualinfo);
            ఒకవేళ (!SDL_ISPIXELFORMAT_ALPHA(format)) {
                // not transparent!
                X11_XFree(egl_visualinfo);
                egl_visualinfo = ఖాళీ;
            }
        }
    }
    
    ఒకవేళ(!egl_visualinfo) {
        // Use the default visual when all else fails
        vi_లోపల.screen = screen;
        egl_visualinfo = X11_XGetVisualInfo(display,
                                            Visual_Screen_ముసుగు,
                                            &vi_లోపల, &బహిర్గతం_లెక్క);

        // Return the first transparent Visual
        ఒకవేళ (transparent) {
            పూర్ణాంకం i;
            కొరకు (i = 0; i < బహిర్గతం_లెక్క; i++) {
                XVisualInfo *v = &egl_visualinfo[i];
                Uint32 format = X11_GetPixelFormatFromVisualInfo(display, v);
                ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) { // found!
                    // re-request it to have a copy that can be X11_XFree'ed later
                    vi_లోపల.screen = screen;
                    vi_లోపల.visualid = v->visualid;
                    X11_XFree(egl_visualinfo);
                    egl_visualinfo = X11_XGetVisualInfo(display, Visual_Screen_ముసుగు | VisualIDMask, &vi_లోపల, &బహిర్గతం_లెక్క);
                    తిరిగి egl_visualinfo;
                }
            }
        }
    }
    తిరిగి egl_visualinfo;
}

SDL_GLContext X11_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_GLContext context;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;

    X11_XSync(display, False);
    context = SDL_EGL_CreateContext(_this, దత్తాంశం->egl_surface);
    X11_XSync(display, False);

    తిరిగి context;
}

SDL_EGLSurface X11_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    తిరిగి దత్తాంశం->egl_surface;
}

bool X11_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    స్థిరరాశి bool ret = SDL_EGL_మార్పిడి_Buffers(_this, కిటికీ->అంతర్గత->egl_surface);                       \

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(కిటికీ);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

    తిరిగి ret;
}

SDL_EGL_MakeCurrent_impl(X11)

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11 && SDL_VIDEO_OPENGL_EGL

