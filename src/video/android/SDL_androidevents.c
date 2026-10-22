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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#அந்தர்பாவ "SDL_androidevents.h"
#அந்தர்பாவ "SDL_androidkeyboard.h"
#அந்தர்பாவ "SDL_androidwindow.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

#அந்தர்பாவ "../../audio/aaudio/SDL_aaudio.h"
#அந்தர்பாவ "../../audio/openslES/SDL_openslES.h"


#ifdef SDL_VIDEO_OPENGL_EGL
நிலையான வெறுமை android_egl_context_restore(SDL_Window *window)
{
    எனில் (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_WindowData *data = window->internal;
        SDL_GL_MakeCurrent(window, வெற்று);
        எனில் (!SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context)) {
            // The context is no longer valid, create a new one
            data->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_தள்ளு_Event(&event);
        }
        data->backup_done = false;

        SDL_GL_SetSwapInterval(data->swap_interval);
    }
}

நிலையான வெறுமை android_egl_context_backup(SDL_Window *window)
{
    எனில் (window && (window->flags & SDL_WINDOW_OPENGL)) {
        முழு interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_WindowData *data = window->internal;
        data->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        எனில் (SDL_GL_GetSwapInterval(&interval)) {
            data->has_swap_interval = 1;
            data->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, வெற்று);
        data->backup_done = true;
    }
}
#endif

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
நிலையான bool Android_EventsInitialized;
நிலையான bool Android_BlockOnPause = true;
நிலையான bool Android_Paused;
நிலையான bool Android_PausedAudio;
நிலையான bool Android_Destroyed;

வெறுமை Android_InitEvents(வெறுமை)
{
    எனில் (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

நிலையான வெறுமை Android_PauseAudio(வெறுமை)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

நிலையான வெறுமை Android_ResumeAudio(வெறுமை)
{
    எனில் (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

நிலையான வெறுமை Android_OnPause(வெறுமை)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    எனில் (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

நிலையான வெறுமை Android_OnResume(வெறுமை)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ifdef SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    எனில் (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    SDL_OnApplicationDidEnterForeground();
}

நிலையான வெறுமை Android_On_கீழ்_Memory(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_கீழ்_MEMORY);
}

நிலையான வெறுமை Android_OnDestroy(வெறுமை)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

நிலையான வெறுமை Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    தேர்வு (event) {
    நிலை SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        நிறுத்து;
    நிலை SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        நிறுத்து;
    நிலை SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        நிறுத்து;
    நிலை SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_கீழ்_Memory();
        நிறுத்து;
    நிலை SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        நிறுத்து;
    இயல்பு:
        நிறுத்து;
    }
}

நிலையான Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    எனில் (Android_Paused) {
        எனில் (Android_BlockOnPause) {
            timeoutNS = -1;
        } இல்லையெனில் எனில் (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    திரும்பு timeoutNS;
}

வெறுமை Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    போது (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        தேர்வு (event) {
        நிலை SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            நிறுத்து;
        நிலை SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            நிறுத்து;
        நிலை SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }
    }
}

bool Android_WaitActiveAndLockActivity(வெறுமை)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    போது (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    போது (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    எனில் (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        திரும்பு false;
    }

    Android_LockActivityMutex();
    திரும்பு true;
}

வெறுமை Android_QuitEvents(வெறுமை)
{
    Android_EventsInitialized = false;
}

#இல்லையெனில்

#அந்தர்பாவ "../../core/android/SDL_android.h"

வெறுமை Android_InitEvents(வெறுமை)
{
}

வெறுமை Android_PumpEvents(Sint64 timeoutNS)
{
    (வெறுமை)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(வெறுமை)
{
    Android_LockActivityMutex();
    திரும்பு true;
}

வெறுமை Android_QuitEvents(வெறுமை)
{
}

#endif // SDL_VIDEO_DRIVER_ANDROID
