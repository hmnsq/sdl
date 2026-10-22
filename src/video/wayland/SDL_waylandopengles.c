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

#यदि defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandopengles.h"
#अन्तर्भाव "SDL_waylandwindow.h"
#अन्तर्भाव "SDL_waylandevents_c.h"

#अन्तर्भाव "xdg-shell-client-protocol.h"

#यदि_अपरिभाषितम् EGL_PLATFORM_WAYLAND_KHR
#परिभाषय EGL_PLATFORM_WAYLAND_KHR 0x31D8
#यदि_अन्तः

// EGL implementation of SDL OpenGL ES support

शून्य Wayland_GLES_समुच्चयः_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    ध्रुव bool परिणाम = SDL_EGL_आरोपय_Library(_this, मार्गः, (NativeDisplayType)दत्त->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(दत्त->display);

    प्रत्यागम परिणाम;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, गवाक्षः->आन्तरिकम्->egl_surface);
    WAYLAND_wl_display_flush(_this->आन्तरिकम्->display);

    प्रत्यागम context;
}

/* Wayland wants to tell you when to provide new frames, and if you have a non-zero
   swap interval, Mesa will block until a callback tells it to do so. On some
   compositors, they might decide that a minimized window _never_ gets a callback,
   which causes apps to hang during swapping forever. So we always set the official
   eglSwapInterval to zero to avoid blocking inside EGL, and manage this ourselves.
   If a swap blocks for too long waiting on a callback, we just go on, under the
   assumption the frame will be wasted, but this is better than freezing the app.
   I frown upon platforms that dictate this sort of control inversion (the callback
   is intended for _rendering_, not stalling until vsync), but we can work around
   this for now.  --ryan. */
/* Addendum: several recent APIs demand this sort of control inversion: Emscripten,
   libretro, Wayland, probably others...it feels like we're eventually going to have
   to give in with a future SDL API revision, since we can bend the other APIs to
   this style, but this style is much harder to bend the other way.  :/ */
bool Wayland_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    यदि (interval > 1) {
        interval = 1;
    } अन्यथा यदि (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_दत्त->egl_swapinterval = interval;
    _this->egl_दत्त->eglSwapInterval(_this->egl_दत्त->egl_display, 0);
    प्रत्यागम true;
}

bool Wayland_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    *interval =_this->egl_दत्त->egl_swapinterval;
    प्रत्यागम true;
}

bool Wayland_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    ध्रुव पूर्णाङ्क swap_interval = _this->egl_दत्त->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    यदि (दत्त->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN &&
        दत्त->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME) {
        प्रत्यागम true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    यदि (दत्त->double_बफर) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        यदि (!_this->egl_दत्त->eglSwapBuffers(_this->egl_दत्त->egl_display, दत्त->egl_surface)) {
            प्रत्यागम SDL_EGL_समुच्चयः_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(दत्त->wayland_दत्त->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    यदि (swap_interval != 0 && दत्त->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
        संरचना wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ध्रुव Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_प्रत्येकम्_SECOND / 20);
        यावत् (SDL_GetAtomicInt(&दत्त->swap_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            यदि (WAYLAND_wl_display_prepare_read_queue(display, दत्त->gles_swap_frame_event_queue) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_queue_pending(display, दत्त->gles_swap_frame_event_queue);
                अनुवर्त;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            यदि (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                भङ्ग;
            }

            यदि (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                भङ्ग;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_queue_pending(display, दत्त->gles_swap_frame_event_queue);
        }
        SDL_समुच्चयः_Atomic_Int(&दत्त->swap_interval_ready, 0);
    }

    यदि (!दत्त->double_बफर) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        यदि (!_this->egl_दत्त->eglSwapBuffers(_this->egl_दत्त->egl_display, दत्त->egl_surface)) {
            प्रत्यागम SDL_EGL_समुच्चयः_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(दत्त->wayland_दत्त->display);
    }

    प्रत्यागम true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    bool परिणाम;

    यदि (गवाक्षः && context) {
        परिणाम = SDL_EGL_MakeCurrent(_this, गवाक्षः->आन्तरिकम्->egl_surface, context);
    } अन्यथा {
        परिणाम = SDL_EGL_MakeCurrent(_this, रिक्त, रिक्त);
    }

    WAYLAND_wl_display_flush(_this->आन्तरिकम्->display);

    _this->egl_दत्त->eglSwapInterval(_this->egl_दत्त->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    प्रत्यागम परिणाम;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool परिणाम = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->आन्तरिकम्->display);
    प्रत्यागम परिणाम;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;

    प्रत्यागम windowdata->egl_surface;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
