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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(SDL_VIDEO_OPENGL_EGL)

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"

#ಅನ್ತರ್ಭಾವ "xdg-shell-client-protocol.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_PLATFORM_WAYLAND_KHR
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_WAYLAND_KHR 0x31D8
#ಆದರೆ_ಅಂತ್ಯ

// EGL implementation of SDL OpenGL ES support

ಶೂನ್ಯ Wayland_GLES_ಗಣ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    _this->gl_config.egl_platform = EGL_PLATFORM_WAYLAND_KHR;
}

bool Wayland_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಸ್ಥಿರಾಂಕ bool ಫಲಿತಾಂಶ = SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, (NativeDisplayType)ದತ್ತಾಂಶ->display);

    Wayland_PumpEvents(_this);
    WAYLAND_wl_display_flush(ದತ್ತಾಂಶ->display);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

SDL_GLContext Wayland_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_GLContext context;
    context = SDL_EGL_CreateContext(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);
    WAYLAND_wl_display_flush(_this->ಆಂತರಿಕ->display);

    ಹಿಂತಿರುಗಿ context;
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
bool Wayland_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    /* technically, this is _all_ adaptive vsync (-1), because we can't
       actually wait for the _next_ vsync if you set 1, but things that
       request 1 probably won't care _that_ much. I hope. No matter what
       you do, though, you never see tearing on Wayland. */
    ಆದರೆ (interval > 1) {
        interval = 1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (interval < -1) {
        interval = -1;
    }

    // !!! FIXME: technically, this should be per-context, right?
    _this->egl_ದತ್ತಾಂಶ->egl_swapinterval = interval;
    _this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Interval(_this->egl_ದತ್ತಾಂಶ->egl_display, 0);
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    *interval =_this->egl_ದತ್ತಾಂಶ->egl_swapinterval;
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅದಲುಬದಲು_interval = _this->egl_ದತ್ತಾಂಶ->egl_swapinterval;

    /* For windows that we know are hidden, skip swaps entirely, if we don't do
     * this compositors will intentionally stall us indefinitely and there's no
     * way for an end user to show the window, unlike other situations (i.e.
     * the window is minimized, behind another window, etc.).
     *
     * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout.
     * -flibit
     */
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN &&
        ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು) {
        ಹಿಂತಿರುಗಿ true;
    }

    /* By default, we wait for the Wayland frame callback and then issue the pageflip (eglSwapBuffers),
     * but if we want low latency (double buffer scheme), we issue the pageflip and then wait
     * immediately for the Wayland frame callback.
     */
    ಆದರೆ (ದತ್ತಾಂಶ->double_ಬಫರ್) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, ದತ್ತಾಂಶ->egl_surface)) {
            ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->display);
    }

    // Control swap interval ourselves. See comments on Wayland_GLES_SetSwapInterval
    ಆದರೆ (ಅದಲುಬದಲು_interval != 0 && ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
        ರಚನೆ wl_display *display = videodata->display;
        // 20hz, so we'll progress even if throttled to zero.
        ಸ್ಥಿರಾಂಕ Uint64 max_wait = SDL_GetTicksNS() + (SDL_NS_ಪ್ರತಿ_ಎರಡನೇ / 20);
        ಆಗ (SDL_GetAtomicInt(&ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_ready) == 0) {
            Uint64 now;

            WAYLAND_wl_display_flush(display);

            /* wl_display_prepare_read_queue() will return false if the event queue is not empty.
             * If the event queue is empty, it will prepare us for our SDL_IOReady() call. */
            ಆದರೆ (WAYLAND_wl_display_prepare_read_ಸರತಿ(display, ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ) != 0) {
                // We have some pending events. Check if the frame callback happened.
                WAYLAND_wl_display_dispatch_ಸರತಿ_pending(display, ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
                ಮುಂದುವರಿ;
            }

            // Beyond this point, we must either call wl_display_cancel_read() or wl_display_read_events()

            now = SDL_GetTicksNS();
            ಆದರೆ (now >= max_wait) {
                // Timeout expired. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_READ, max_wait - now) <= 0) {
                // Error or timeout expired without any events for us. Cancel the read.
                WAYLAND_wl_display_cancel_read(display);
                ನಿಲ್ಲಿಸು;
            }

            // We have events. Read and dispatch them.
            WAYLAND_wl_display_read_events(display);
            WAYLAND_wl_display_dispatch_ಸರತಿ_pending(display, ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
        }
        SDL_ಗಣ_Atomic_Int(&ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval_ready, 0);
    }

    ಆದರೆ (!ದತ್ತಾಂಶ->double_ಬಫರ್) {
        // Feed the frame to Wayland. This will set it so the wl_surface_frame callback can fire again.
        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, ದತ್ತಾಂಶ->egl_surface)) {
            ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
        }

        WAYLAND_wl_display_flush(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->display);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    bool ಫಲಿತಾಂಶ;

    ಆದರೆ (ಕಿಟಕಿ && context) {
        ಫಲಿತಾಂಶ = SDL_EGL_MakeCurrent(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface, context);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = SDL_EGL_MakeCurrent(_this, ಖಾಲಿ, ಖಾಲಿ);
    }

    WAYLAND_wl_display_flush(_this->ಆಂತರಿಕ->display);

    _this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Interval(_this->egl_ದತ್ತಾಂಶ->egl_display, 0); // see comments on Wayland_GLES_SetSwapInterval.

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool Wayland_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    bool ಫಲಿತಾಂಶ = SDL_EGL_DestroyContext(_this, context);
    WAYLAND_wl_display_flush(_this->ಆಂತರಿಕ->display);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

EGLSurface Wayland_GLES_GetEGLSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಹಿಂತಿರುಗಿ windowdata->egl_surface;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND && SDL_VIDEO_OPENGL_EGL
