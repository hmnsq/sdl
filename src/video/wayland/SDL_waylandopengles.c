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

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#شامل "../../core/unix/SDL_poll.h"
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandopengles.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylandevents_c.h"

#شامل "xdg-shell-client-protocol.h"

#اگر_غیر_تعریف_شدہ EGL_PLATFORM_WAYLAND_KHR
#تعریف_کرو EGL_PLATFORM_WAYLAND_KHR 0x31D8
#اگر_ختم

// EGL implementation of SDL OpenGL ES support

خالی Wayland_GLES_سیٹ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ثابت bool نتیجہ = SDL_EGL_بھرو_Library(_this, راستہ, (NativeDisplayType)ڈیٹا->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(ڈیٹا->display);

    واپس نتیجہ;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, کھڑکی->اندرونی_2->egl_surface);
    WAYLAND_wl_display_flush(_this->اندرونی_2->display);

    واپس context;
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
bool Wayland_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    اگر (interval > 1) {
        interval = 1;
    } ورنہ اگر (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_ڈیٹا->egl_swapinterval = interval;
    _this->egl_ڈیٹا->egl_تبادلہ_Interval(_this->egl_ڈیٹا->egl_display, 0);
    واپس true;
}

bool Wayland_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    *interval =_this->egl_ڈیٹا->egl_swapinterval;
    واپس true;
}

bool Wayland_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    ثابت صحیح تبادلہ_interval = _this->egl_ڈیٹا->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    اگر (ڈیٹا->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN &&
        ڈیٹا->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا) {
        واپس true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    اگر (ڈیٹا->double_بفر) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        اگر (!_this->egl_ڈیٹا->egl_تبادلہ_Buffers(_this->egl_ڈیٹا->egl_display, ڈیٹا->egl_surface)) {
            واپس SDL_EGL_سیٹ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ڈیٹا->wayland_ڈیٹا->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    اگر (تبادلہ_interval != 0 && ڈیٹا->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
        ساخت wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ثابت Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_فی_دوسرا / 20);
        جب (SDL_GetAtomicInt(&ڈیٹا->تبادلہ_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            اگر (WAYLAND_wl_display_prepare_read_قطار(display, ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_قطار_pending(display, ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار);
                جاری;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            اگر (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                توڑو;
            }

            اگر (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                توڑو;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_قطار_pending(display, ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار);
        }
        SDL_سیٹ_Atomic_Int(&ڈیٹا->تبادلہ_interval_ready, 0);
    }

    اگر (!ڈیٹا->double_بفر) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        اگر (!_this->egl_ڈیٹا->egl_تبادلہ_Buffers(_this->egl_ڈیٹا->egl_display, ڈیٹا->egl_surface)) {
            واپس SDL_EGL_سیٹ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ڈیٹا->wayland_ڈیٹا->display);
    }

    واپس true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    bool نتیجہ;

    اگر (کھڑکی && context) {
        نتیجہ = SDL_EGL_MakeCurrent(_this, کھڑکی->اندرونی_2->egl_surface, context);
    } ورنہ {
        نتیجہ = SDL_EGL_MakeCurrent(_this, تہی, تہی);
    }

    WAYLAND_wl_display_flush(_this->اندرونی_2->display);

    _this->egl_ڈیٹا->egl_تبادلہ_Interval(_this->egl_ڈیٹا->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    واپس نتیجہ;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool نتیجہ = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->اندرونی_2->display);
    واپس نتیجہ;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *windowdata = کھڑکی->اندرونی_2;

    واپس windowdata->egl_surface;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
