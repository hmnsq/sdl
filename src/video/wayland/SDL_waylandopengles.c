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

#எனில் defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_windowevents_c.h"
#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandopengles.h"
#அந்தர்பாவ "SDL_waylandwindow.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"

#அந்தர்பாவ "xdg-shell-client-protocol.h"

#ifndef EGL_PLATFORM_WAYLAND_KHR
#define EGL_PLATFORM_WAYLAND_KHR 0x31D8
#endif

// EGL implementation of SDL OpenGL ES support

வெறுமை Wayland_GLES_SetDefaultProfileConfig(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    SDL_VideoData *data = _this->internal;

    மாறிலி bool result = SDL_EGL_LoadLibrary(_this, path, (NativeDisplayType)data->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(data->display);

    திரும்பு result;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, window->internal->egl_surface);
    WAYLAND_wl_display_flush(_this->internal->display);

    திரும்பு context;
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
bool Wayland_GLES_SetSwapInterval(SDL_VideoDevice *_this, முழு interval)
{
    எனில் (!_this->egl_data) {
        திரும்பு SDL_SetError("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    எனில் (interval > 1) {
        interval = 1;
    } இல்லையெனில் எனில் (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_data->egl_swapinterval = interval;
    _this->egl_data->eglSwapInterval(_this->egl_data->egl_display, 0);
    திரும்பு true;
}

bool Wayland_GLES_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval)
{
    எனில் (!_this->egl_data) {
        திரும்பு SDL_SetError("EGL not initialized");
    }

    *interval =_this->egl_data->egl_swapinterval;
    திரும்பு true;
}

bool Wayland_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    மாறிலி முழு swap_interval = _this->egl_data->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    எனில் (data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN &&
        data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME) {
        திரும்பு true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    எனில் (data->double_buffer) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        எனில் (!_this->egl_data->eglSwapBuffers(_this->egl_data->egl_display, data->egl_surface)) {
            திரும்பு SDL_EGL_SetError("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(data->waylandData->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    எனில் (swap_interval != 0 && data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        SDL_VideoData *videodata = _this->internal;
        கட்டமைப்பு wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        மாறிலி Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_PER_SECOND / 20);
        போது (SDL_GetAtomicInt(&data->swap_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            எனில் (WAYLAND_wl_display_prepare_read_queue(display, data->gles_swap_frame_event_queue) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_queue_pending(display, data->gles_swap_frame_event_queue);
                தொடர்;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            எனில் (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                நிறுத்து;
            }

            எனில் (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                நிறுத்து;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_queue_pending(display, data->gles_swap_frame_event_queue);
        }
        SDL_SetAtomicInt(&data->swap_interval_ready, 0);
    }

    எனில் (!data->double_buffer) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        எனில் (!_this->egl_data->eglSwapBuffers(_this->egl_data->egl_display, data->egl_surface)) {
            திரும்பு SDL_EGL_SetError("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(data->waylandData->display);
    }

    திரும்பு true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)
{
    bool result;

    எனில் (window && context) {
        result = SDL_EGL_MakeCurrent(_this, window->internal->egl_surface, context);
    } இல்லையெனில் {
        result = SDL_EGL_MakeCurrent(_this, வெற்று, வெற்று);
    }

    WAYLAND_wl_display_flush(_this->internal->display);

    _this->egl_data->eglSwapInterval(_this->egl_data->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    திரும்பு result;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool result = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->internal->display);
    திரும்பு result;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

    திரும்பு windowdata->egl_surface;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
