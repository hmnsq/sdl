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

#ਜੇ defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-shell-client-protocol.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_PLATFORM_WAYLAND_KHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_WAYLAND_KHR 0x31D8
#ਜੇ_ਅੰਤ

// EGL implementation of SDL OpenGL ES support

ਖਾਲੀ Wayland_GLES_ਸੈੱਟ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅਚਲ bool ਨਤੀਜਾ = SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, (NativeDisplayType)ਅੰਕੜੇ->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(ਅੰਕੜੇ->display);

    ਵਾਪਸ ਨਤੀਜਾ;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);
    WAYLAND_wl_display_flush(_this->ਅੰਦਰੂਨੀ->display);

    ਵਾਪਸ context;
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
bool Wayland_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    ਜੇ (interval > 1) {
        interval = 1;
    } ਨਹੀਂਤਾਂ ਜੇ (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_ਅੰਕੜੇ->egl_swapinterval = interval;
    _this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Interval(_this->egl_ਅੰਕੜੇ->egl_display, 0);
    ਵਾਪਸ true;
}

bool Wayland_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    *interval =_this->egl_ਅੰਕੜੇ->egl_swapinterval;
    ਵਾਪਸ true;
}

bool Wayland_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਪੂਰਨ ਅਦਲਾ_ਬਦਲੀ_interval = _this->egl_ਅੰਕੜੇ->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    ਜੇ (ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN &&
        ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ) {
        ਵਾਪਸ true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    ਜੇ (ਅੰਕੜੇ->double_ਬਫਰ) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ਜੇ (!_this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->egl_ਅੰਕੜੇ->egl_display, ਅੰਕੜੇ->egl_surface)) {
            ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    ਜੇ (ਅਦਲਾ_ਬਦਲੀ_interval != 0 && ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
        ਬਣਤਰ wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ਅਚਲ Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_ਪ੍ਰਤੀ_ਦੂਜਾ / 20);
        ਜਦੋਂ (SDL_GetAtomicInt(&ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            ਜੇ (WAYLAND_wl_display_prepare_read_ਕਤਾਰ(display, ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_ਕਤਾਰ_pending(display, ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
                ਜਾਰੀ;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            ਜੇ (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ਰੋਕੋ;
            }

            ਜੇ (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ਰੋਕੋ;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_ਕਤਾਰ_pending(display, ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
        }
        SDL_ਸੈੱਟ_Atomic_Int(&ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval_ready, 0);
    }

    ਜੇ (!ਅੰਕੜੇ->double_ਬਫਰ) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ਜੇ (!_this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->egl_ਅੰਕੜੇ->egl_display, ਅੰਕੜੇ->egl_surface)) {
            ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->display);
    }

    ਵਾਪਸ true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    bool ਨਤੀਜਾ;

    ਜੇ (ਖਿੜਕੀ && context) {
        ਨਤੀਜਾ = SDL_EGL_MakeCurrent(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface, context);
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = SDL_EGL_MakeCurrent(_this, ਨਿਰਾ, ਨਿਰਾ);
    }

    WAYLAND_wl_display_flush(_this->ਅੰਦਰੂਨੀ->display);

    _this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Interval(_this->egl_ਅੰਕੜੇ->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool ਨਤੀਜਾ = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->ਅੰਦਰੂਨੀ->display);
    ਵਾਪਸ ਨਤੀਜਾ;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਵਾਪਸ windowdata->egl_surface;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
