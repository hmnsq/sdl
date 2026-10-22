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

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandopengles.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "SDL_waylandevents_c.h"

#ضمن "xdg-shell-client-protocol.h"

#جيڪڏهن_وصف_نه_ٿيل EGL_PLATFORM_WAYLAND_KHR
#وصف_ڪريو EGL_PLATFORM_WAYLAND_KHR 0x31D8
#جيڪڏهن_پورو

// EGL implementation of SDL OpenGL ES support

فراغ Wayland_GLES_سيٽ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    ثابت bool نتيجو = SDL_EGL_ڀريو_Library(_this, رستو, (NativeDisplayType)معلومات->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(معلومات->display);

    أرجع نتيجو;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, دري->اندروني->egl_surface);
    WAYLAND_wl_display_flush(_this->اندروني->display);

    أرجع context;
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
bool Wayland_GLES_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    إذا (!_this->egl_معلومات) {
        أرجع SDL_سيٽ_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    إذا (interval > 1) {
        interval = 1;
    } وإلا إذا (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_معلومات->egl_swapinterval = interval;
    _this->egl_معلومات->egl_مٽا_سٽا_Interval(_this->egl_معلومات->egl_display, 0);
    أرجع true;
}

bool Wayland_GLES_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    إذا (!_this->egl_معلومات) {
        أرجع SDL_سيٽ_Error("EGL not initialized");
    }

    *interval =_this->egl_معلومات->egl_swapinterval;
    أرجع true;
}

bool Wayland_GLES_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    ثابت صحيح مٽا_سٽا_interval = _this->egl_معلومات->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    إذا (معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN &&
        معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو) {
        أرجع true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    إذا (معلومات->double_بفر) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        إذا (!_this->egl_معلومات->egl_مٽا_سٽا_Buffers(_this->egl_معلومات->egl_display, معلومات->egl_surface)) {
            أرجع SDL_EGL_سيٽ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(معلومات->wayland_معلومات->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    إذا (مٽا_سٽا_interval != 0 && معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Video_معلومات *videodata = _this->اندروني;
        بنية wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ثابت Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_في_ٻيو / 20);
        طالما (SDL_GetAtomicInt(&معلومات->مٽا_سٽا_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            إذا (WAYLAND_wl_display_prepare_read_قطار(display, معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_قطار_pending(display, معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار);
                استمر;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            إذا (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                اكسر;
            }

            إذا (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                اكسر;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_قطار_pending(display, معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار);
        }
        SDL_سيٽ_Atomic_Int(&معلومات->مٽا_سٽا_interval_ready, 0);
    }

    إذا (!معلومات->double_بفر) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        إذا (!_this->egl_معلومات->egl_مٽا_سٽا_Buffers(_this->egl_معلومات->egl_display, معلومات->egl_surface)) {
            أرجع SDL_EGL_سيٽ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(معلومات->wayland_معلومات->display);
    }

    أرجع true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context)
{
    bool نتيجو;

    إذا (دري && context) {
        نتيجو = SDL_EGL_MakeCurrent(_this, دري->اندروني->egl_surface, context);
    } وإلا {
        نتيجو = SDL_EGL_MakeCurrent(_this, عدم, عدم);
    }

    WAYLAND_wl_display_flush(_this->اندروني->display);

    _this->egl_معلومات->egl_مٽا_سٽا_Interval(_this->egl_معلومات->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    أرجع نتيجو;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool نتيجو = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->اندروني->display);
    أرجع نتيجو;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *windowdata = دري->اندروني;

    أرجع windowdata->egl_surface;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
