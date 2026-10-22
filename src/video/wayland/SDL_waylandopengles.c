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

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#অন্তর্ভাব "../../core/unix/SDL_poll.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandopengles.h"
#অন্তর্ভাব "SDL_waylandwindow.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"

#অন্তর্ভাব "xdg-shell-client-protocol.h"

#ifndef EGL_PLATFORM_WAYLAND_KHR
#define EGL_PLATFORM_WAYLAND_KHR 0x31D8
#endif

// EGL implementation of SDL OpenGL ES support

শূন্য Wayland_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    ধ্রুবক bool ফলাফল = SDL_EGL_LoadLibrary(_this, path, (NativeDisplayType)তথ্য->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(তথ্য->display);

    ফেরত ফলাফল;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, window->internal->egl_surface);
    WAYLAND_wl_display_flush(_this->internal->display);

    ফেরত context;
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
bool Wayland_GLES_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    যদি (!_this->egl_তথ্য) {
        ফেরত SDL_SetError("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    যদি (interval > 1) {
        interval = 1;
    } অন্যথা যদি (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_তথ্য->egl_swapinterval = interval;
    _this->egl_তথ্য->eglSwapInterval(_this->egl_তথ্য->egl_display, 0);
    ফেরত true;
}

bool Wayland_GLES_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval)
{
    যদি (!_this->egl_তথ্য) {
        ফেরত SDL_SetError("EGL not initialized");
    }

    *interval =_this->egl_তথ্য->egl_swapinterval;
    ফেরত true;
}

bool Wayland_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    ধ্রুবক পূর্ণসংখ্যা swap_interval = _this->egl_তথ্য->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    যদি (তথ্য->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN &&
        তথ্য->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME) {
        ফেরত true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    যদি (তথ্য->double_বাফার) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        যদি (!_this->egl_তথ্য->eglSwapBuffers(_this->egl_তথ্য->egl_display, তথ্য->egl_surface)) {
            ফেরত SDL_EGL_SetError("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(তথ্য->wayland_তথ্য->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    যদি (swap_interval != 0 && তথ্য->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        SDL_Video_তথ্য *videodata = _this->internal;
        কাঠামো wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ধ্রুবক Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_PER_SECOND / 20);
        যখন (SDL_GetAtomicInt(&তথ্য->swap_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            যদি (WAYLAND_wl_display_prepare_read_queue(display, তথ্য->gles_swap_frame_event_queue) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_queue_pending(display, তথ্য->gles_swap_frame_event_queue);
                চালু;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            যদি (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                বিরতি;
            }

            যদি (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                বিরতি;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_queue_pending(display, তথ্য->gles_swap_frame_event_queue);
        }
        SDL_SetAtomicInt(&তথ্য->swap_interval_ready, 0);
    }

    যদি (!তথ্য->double_বাফার) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        যদি (!_this->egl_তথ্য->eglSwapBuffers(_this->egl_তথ্য->egl_display, তথ্য->egl_surface)) {
            ফেরত SDL_EGL_SetError("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(তথ্য->wayland_তথ্য->display);
    }

    ফেরত true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    bool ফলাফল;

    যদি (window && context) {
        ফলাফল = SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } অন্যথা {
        ফলাফল = SDL_EGL_MakeCurrent(_this, ফাঁকা, ফাঁকা);
    }

    WAYLAND_wl_display_flush(_this->internal->display);

    _this->egl_তথ্য->eglSwapInterval(_this->egl_তথ্য->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    ফেরত ফলাফল;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool ফলাফল = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->internal->display);
    ফেরত ফলাফল;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *windowdata = window->internal;

    ফেরত windowdata->egl_surface;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
