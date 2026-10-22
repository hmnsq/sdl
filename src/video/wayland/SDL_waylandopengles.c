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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandopengles.h"
#అన్తర్భావ "SDL_waylandwindow.h"
#అన్తర్భావ "SDL_waylandevents_c.h"

#అన్తర్భావ "xdg-shell-client-protocol.h"

#నిర్వచితం_కాకపోతే EGL_PLATFORM_WAYLAND_KHR
#నిర్వచించు EGL_PLATFORM_WAYLAND_KHR 0x31D8
#అయితే_ముగింపు

// EGL implementation of SDL OpenGL ES support

శూన్య Wayland_GLES_సమితి_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    స్థిరరాశి bool ఫలితం = SDL_EGL_ఎక్కించు_Library(_this, మార్గం, (NativeDisplayType)దత్తాంశం->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(దత్తాంశం->display);

    తిరిగి ఫలితం;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, కిటికీ->అంతర్గత->egl_surface);
    WAYLAND_wl_display_flush(_this->అంతర్గత->display);

    తిరిగి context;
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
bool Wayland_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    ఒకవేళ (interval > 1) {
        interval = 1;
    } లేకపోతే ఒకవేళ (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_దత్తాంశం->egl_swapinterval = interval;
    _this->egl_దత్తాంశం->egl_మార్పిడి_Interval(_this->egl_దత్తాంశం->egl_display, 0);
    తిరిగి true;
}

bool Wayland_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    *interval =_this->egl_దత్తాంశం->egl_swapinterval;
    తిరిగి true;
}

bool Wayland_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    స్థిరరాశి పూర్ణాంకం మార్పిడి_interval = _this->egl_దత్తాంశం->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    ఒకవేళ (దత్తాంశం->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_SHOWN &&
        దత్తాంశం->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం) {
        తిరిగి true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    ఒకవేళ (దత్తాంశం->double_బఫరు) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ఒకవేళ (!_this->egl_దత్తాంశం->egl_మార్పిడి_Buffers(_this->egl_దత్తాంశం->egl_display, దత్తాంశం->egl_surface)) {
            తిరిగి SDL_EGL_సమితి_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(దత్తాంశం->wayland_దత్తాంశం->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    ఒకవేళ (మార్పిడి_interval != 0 && దత్తాంశం->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
        నిర్మాణం wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        స్థిరరాశి Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_చొప్పున_రెండవ / 20);
        అయితే (SDL_GetAtomicInt(&దత్తాంశం->మార్పిడి_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            ఒకవేళ (WAYLAND_wl_display_prepare_read_వరుస(display, దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_వరుస_pending(display, దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస);
                కొనసాగు;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            ఒకవేళ (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ఆపు;
            }

            ఒకవేళ (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ఆపు;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_వరుస_pending(display, దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస);
        }
        SDL_సమితి_Atomic_Int(&దత్తాంశం->మార్పిడి_interval_ready, 0);
    }

    ఒకవేళ (!దత్తాంశం->double_బఫరు) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ఒకవేళ (!_this->egl_దత్తాంశం->egl_మార్పిడి_Buffers(_this->egl_దత్తాంశం->egl_display, దత్తాంశం->egl_surface)) {
            తిరిగి SDL_EGL_సమితి_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(దత్తాంశం->wayland_దత్తాంశం->display);
    }

    తిరిగి true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    bool ఫలితం;

    ఒకవేళ (కిటికీ && context) {
        ఫలితం = SDL_EGL_MakeCurrent(_this, కిటికీ->అంతర్గత->egl_surface, context);
    } లేకపోతే {
        ఫలితం = SDL_EGL_MakeCurrent(_this, ఖాళీ, ఖాళీ);
    }

    WAYLAND_wl_display_flush(_this->అంతర్గత->display);

    _this->egl_దత్తాంశం->egl_మార్పిడి_Interval(_this->egl_దత్తాంశం->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    తిరిగి ఫలితం;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool ఫలితం = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->అంతర్గత->display);
    తిరిగి ఫలితం;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;

    తిరిగి windowdata->egl_surface;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
